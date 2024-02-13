/*! \file itra_calc.c
 * \brief Route planner with ITRA-score calculation
 * \author Levente Kovacs (F5UHYT)
 * \version 4.2
 * \date 2023-12-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "debugmalloc.h"

#define BUFFER_SIZE 1024
#define RADIUS_OF_EARTH 6371.0

#define ERR_COLOR "\033[1;31m"   /**<Red color ANSI escape code for stderr outputs */
#define WARN_COLOR "\033[1;33m"  /**<Yellow color ANSI escape code for user warnings */
#define GREEN_COLOR "\033[1;32m" /**<Green color ANSI escape code for signaling correct operation */
#define INPUT_COLOR "\033[1;36m" /**<Cyan color ANSI escape code for asking for user input */
#define INFO_COLOR "\033[1m"     /**<Bold style ANSI escape code for all other outputs */
#define RESET_COLOR "\033[0m"    /**<ANSI escape code to reset terminal color to default */

struct _edges_list;

/*! \struct coordinates
 * \brief Coordinates definition
 */
typedef struct
{
    double lat, lon, el;
} coordinates;

/*! \struct point
 * \brief Point definition
 */
typedef struct
{
    size_t id;            /*!<Contains unique id for point (useful for debugging)*/
    coordinates location; /*!<Contains unique id for point (useful for debugging)*/
    double itra;          /*!<Contains ITRA-score for path from defined start point*/

    int visited;                  /*!<Contains bool information for if a point has been visited in the algorithm*/
    struct _edges_list *edges_in; /*!<List of edges coming in to a node of the graph*/
    double dist;                  /*!<Distance from defined starting point for Dijkstra*/
} point;

/*! \struct point_list
 * \brief List for points (nodes)
 */
typedef struct _point_list
{
    point point;
    struct _point_list *next;
} point_list;

/*! \struct edge
 * \brief Edge definition
 */
typedef struct
{
    point_list *from;      /*!<Pointer to the origin point*/
    double dist, up, down; /*!<Data containing the length, up and down level of the path between the two points*/
} edge;

/*! \struct edges_list
 * \brief Edges in a linked list coming into a certain node (Used by Dijkstra)
 */
typedef struct _edges_list
{
    edge edge;
    struct _edges_list *next;
} edges_list;

/*! \fn void destroy_edges(edges_list **head);
 * \brief Frees up linked list of edges.
 * \param head: Double pointer to head of the linked list.
 * \return Void (sets *head to NULL)
 */
void destroy_edges(edges_list **head)
{
    edges_list *curelem = *head, *next;

    while (curelem != NULL)
    {
        next = curelem->next;
        free(curelem);
        curelem = next;
    }
    *head = NULL;
}

/*! \fn void destroy_points(point_list **head);
 * \brief Frees up linked list of points (with sentinel).
 * \param head: Double pointer to sentinel of the linked list.
 * \return Void (sets *head to NULL)
 */
void destroy_points(point_list **head)
{
    if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        return;
    }

    point_list *curelem = *head, *next;

    while (curelem != NULL)
    {
        destroy_edges(&(curelem->point.edges_in));
        next = curelem->next;
        free(curelem);
        curelem = next;
    }
    *head = NULL;
}

/*! \fn point_list *is_in_list(point_list *head, point_list *to_find);
 * \brief Looks up if a point_list element is already in the linked list.
 * \param head: Pointer to sentinel of the linked list.
 * \param to_find: Pointer to a point_list element. This is the element to find in the list.
 * \return Pointer to the element with the same coordinates in the list. NULL if no match was found.
 */
point_list *is_in_list(point_list *head, point_list *to_find)
{
    point_list *curelem = head;

    while (curelem != NULL)
    {
        if (curelem->point.location.lat == to_find->point.location.lat && curelem->point.location.lon == to_find->point.location.lon && curelem != to_find)
        {
            return curelem;
        }
        curelem = curelem->next;
    }

    return NULL;
}

/*! \fn point_list void order_merged_edges(point_list *to_merge, point_list *merge_with, point_list *head);
 * \brief Fixes incorrect references to a just merged point from edges.
 *
 * If a merge was done by order_list this function looks through the list and swaps the from field of all the edges,
 * where the merged point appeaared.
 *
 * \param to_merge: This is the pointer to the point element which was just merged by order_list.
 * \param merge_with: This is the pointer to the point element with which to_merge was merged.
 * \param head: Pointer to sentinel of the linked list.
 * \return Void.
 */
void order_merged_edges(point_list *to_merge, point_list *merge_with, point_list *head)
{
    head = head->next;

    while (head != NULL)
    {
        edges_list *edge_in = head->point.edges_in;

        while (edge_in != NULL)
        {
            if (edge_in->edge.from == to_merge)
                edge_in->edge.from = merge_with;
            edge_in = edge_in->next;
        }

        head = head->next;
    }
}

/*! \fn edges_list *get_last_edge(edges_list *head);
 * \brief Looks up last element in an edges_list.
 * \param head: Pointer to head of the linked list.
 * \return Pointer to the last element.
 */
edges_list *get_last_edge(edges_list *head)
{
    while (head != NULL && head->next != NULL)
        head = head->next;

    return head;
}

/*! \fn int order_list(point_list *head);
 * \brief Merge two elements in the list if they represent the same location.
 *
 * If the coordinates of the last element in point_list occur twice in the list, the function merges the two points together
 * by stitching the edge_in lists together and correcting the incorrect references from other edges originating from the
 * to_merge point with the function order_merged_edges.
 *
 * \param head: Pointer to sentinel of the linked list.
 * \return Status indication: 1 if a merge has occured, 0 if not.
 */
int order_list(point_list *head)
{
    point_list *to_merge = head, *lastelem;

    /* Seek to the last two elements in the list */
    while (to_merge->next != NULL)
    {
        lastelem = to_merge;
        to_merge = to_merge->next;
    }

    point_list *merge_with = is_in_list(head, to_merge);
    if (merge_with == NULL)
        return 0;

    /* Stitch to_merge edges_in in front of merge_with edges_in */
    edges_list *temp;
    temp = merge_with->point.edges_in;
    merge_with->point.edges_in = to_merge->point.edges_in;

    edges_list *lastedge = get_last_edge(to_merge->point.edges_in);

    if (to_merge->point.edges_in == NULL)
        merge_with->point.edges_in = temp;
    else
    {
        merge_with->point.edges_in = to_merge->point.edges_in;
        lastedge->next = temp;
    }

    /* Rewrite all edges where from is to_merge to merge_with */
    order_merged_edges(to_merge, merge_with, head);

    /* Pop to_merge */
    lastelem->next = NULL;
    free(to_merge);

    /* Return 1 (succesful merge) */
    return 1;
}

/*! \fn double toRadians(double degree);
 * \brief Convert degrees to radians.
 * \param degree: Angle in degrees.
 * \return Angle in radians.
 */
double toRadians(double degree)
{
    return degree * (3.14 / 180.0);
}

/*! \fn double calculateDistance(double lat1, double lon1, double lat2, double lon2);
 * \brief Calculates the distance between two coordinates.
 * \return Distance in km.
 */
double calculateDistance(double lat1, double lon1, double lat2, double lon2)
{
    /* Convert latitude and longitude from degrees to radians */
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    /* Calculate differences in coordinates */
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    /* Calculate distance */
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = RADIUS_OF_EARTH * c;

    return distance;
}

/*! \fn int get_elevation(point_list *to_get, FILE *track);
 * \brief Look up elevation for point_list to_get in FILE track.
 * \param to_get: Pointer to the point.
 * \param track: Track .gpx extension xml file. Has coordinates and elevation data.
 * \warning track.gpx must have elevation data and must contain the correct gps location information.
 * \return Status indication: 0 if elevation was acquired succesfully, 1 otherwise.
 */
int get_elevation(point_list *to_get, FILE *track)
{
    /* Rewind to the start of track and set up lat lon el */
    rewind(track);
    double lat, lon, el;

    while (!feof(track))
    {
        char buffer[BUFFER_SIZE];

        /* Read line-by line until lat and lon corresponding to to_get are found */
        fgets(buffer, BUFFER_SIZE, track);
        if (strstr(buffer, "lat") != NULL)
        {
            sscanf(strstr(buffer, "lat"), "lat=\"%lf\" lon=\"%lf\"", &lat, &lon);

            /* If correct point is found, read next line which contains elevation data */
            if (lat == to_get->point.location.lat && lon == to_get->point.location.lon)
            {
                fgets(buffer, BUFFER_SIZE, track);
                sscanf(strstr(buffer, "<ele>"), "<ele>%lf", &el);
                to_get->point.location.el = el;
                return 0;
            }
        }
    }
    return 1;
}

/*! \fn int add_edge_in(point_list *to, point_list *from, point_list *head, FILE *track);
 * \brief Add edges from and to neighbouring intersections (points, nodes).
 * \param to: Pointer to the current point (with no edges_in).
 * \param from: Pointer to the already existing point coming before the current point.
 * \param head: Pointer to the sentinel of the linked list of points.
 * \param track: Track .gpx extension xml file. Has coordinates and elevation data.
 * \warning track.gpx must must contain the correct gps location information (from and to coordinates).
 * \return Status indication: -1 if no edges could be added, 0 if an error occured, 1 in case of success.
 */
int add_edge_in(point_list *to, point_list *from, point_list *head, FILE *track)
{
    /* Set up edges_in as empty list */
    to->point.edges_in = NULL;

    rewind(track);

    /* Seek to point from (point list *from is the previous element is the list of points, which is either the previously
    read point from the route file, or a point read from another route file. In the latter case, track won't contain the
    origin point and function will keep edges_in as empty list and return -1) */

    char buffer[BUFFER_SIZE];
    double lat, lon, el;
    while (1)
    {
        /* Read line by line until node is found*/
        fgets(buffer, BUFFER_SIZE, track);
        sscanf(strstr(buffer, "lat"), "lat=\"%lf\" lon=\"%lf\"", &lat, &lon);

        /* If node is from break */
        if (lat == from->point.location.lat && lon == from->point.location.lon)
            break;

        /* If to or EOF is reached, there is no from in track file (return -1) */

        if ((lat == to->point.location.lat && lon == to->point.location.lon && is_in_list(head, to) == to) || feof(track))
            return -1;
    }

    double dist = 0, up = 0, down = 0, latprev = from->point.location.lat, lonprev = from->point.location.lon, prevel = from->point.location.el;
    while (1)
    {
        /* Read line by line until node is found*/
        fgets(buffer, BUFFER_SIZE, track);
        sscanf(strstr(buffer, "lat"), "lat=\"%lf\" lon=\"%lf\"", &lat, &lon);

        /* If node is to break */
        if (lat == to->point.location.lat && lon == to->point.location.lon)
        {
            /* Add distance and elevation from last point to currently read point to dist and up or down */
            dist += calculateDistance(latprev, lonprev, lat, lon);

            /* Read and add elevation */
            fgets(buffer, BUFFER_SIZE, track);
            sscanf(strstr(buffer, "<ele>"), "<ele>%lf", &el);
            if (el > prevel)
                up += el - prevel;
            else
                down += el - prevel;
            break;
        }

        /* If EOF is reached, there is no to in track file */
        if (feof(track))
        {
            fprintf(stderr, ERR_COLOR "\nError add_edge_in: Couldn't find lat %f lon %f in track file " RESET_COLOR, to->point.location.lat, to->point.location.lon);
            return 0;
        }

        /* Add distance and elevation from last point to currently read point to dist and up or down */
        dist += calculateDistance(latprev, lonprev, lat, lon);
        /* Read and add elevation */
        sscanf(strstr(buffer, "<ele>"), "<ele>%lf", &el);
        if (el > prevel)
            up += el - prevel;
        else
            down += prevel - el;

        /* Set prevs to currents */
        prevel = el;
        lonprev = lon;
        latprev = lat;
    }

    /* Create edge_in and set values, stitch in edges_in list */
    edges_list *edge_in = malloc(sizeof(edges_list));
    if (edge_in == NULL)
    {
        fprintf(stderr, ERR_COLOR "\nError add_edge_in: Couldn't allocate memory" RESET_COLOR);
        return 0;
    }

    edge_in->edge.dist = dist;
    edge_in->edge.up = up;
    edge_in->edge.down = down;
    edge_in->edge.from = from;
    edge_in->next = NULL;
    to->point.edges_in = edge_in;

    /* Create edge in other direction */

    edges_list *edge_in_rev = malloc(sizeof(edges_list));
    if (edge_in_rev == NULL)
    {
        fprintf(stderr, ERR_COLOR "\nError add_edge_in: Couldn't allocate memory" RESET_COLOR);
        return 0;
    }

    edge_in_rev->edge.dist = dist;
    edge_in_rev->edge.down = up;
    edge_in_rev->edge.up = down;
    edge_in_rev->edge.from = to;

    edges_list *temp;
    temp = from->point.edges_in;
    from->point.edges_in = edge_in_rev;
    edge_in_rev->next = temp;

    /* Success, return 1*/
    return 1;
}

/*! \fn int read_nodes_from_route(point_list *head, FILE *route, FILE *track, size_t *idcnt);
 * \brief Reads nodes from corresponding route file.
 * \param head: Pointer to the sentinel of the linked list of points.
 * \param route: Route .gpx extension xml file. Has coordinates of intersections (and some more BUT not all points).
 * \param track: Track .gpx extension xml file. Has coordinates and elevation data.
 * \param track: Track .gpx extension xml file. Has coordinates and elevation data.
 * \param idcnt: Counter for assigning id to newly read points in point_list.
 * \warning track.gpx must must contain the correct gps location information.
 * \warning route.gpx must must contain the correct gps location information.
 * \return The number of nodes read from the current file (useful for debugging).
 * \note Return value 0 indicates that no nodes were read, hence an error must have occured.
 */
int read_nodes_from_route(point_list *head, FILE *route, FILE *track, size_t *idcnt)
{
    int nodes_read = 0;
    char buffer[BUFFER_SIZE];
    double lat, lon;
    point_list *lastelem = head, *curelem;

    /* Seek to the end of point_list */
    while (lastelem->next != NULL)
        lastelem = lastelem->next;

    while (1)
    {
        if (feof(route))
        {
            return nodes_read;
        }

        /* Read from file line-by-line until a node is found */
        fgets(buffer, BUFFER_SIZE, route);
        if (sscanf(buffer, "<rtept lat=\"%lf\" lon=\"%lf\"", &lat, &lon) == 2)
        {
            curelem = malloc(sizeof(point_list));
            if (curelem == NULL)
            {
                fprintf(stderr, ERR_COLOR "\nError read_nodes_from_route: Couldn't allocate a point" RESET_COLOR);
                return 0;
            }

            /* Set id */
            curelem->point.id = *idcnt;
            (*idcnt)++;

            /* Set nodes data to read data (lat, lon) */
            curelem->point.location.lat = lat;
            curelem->point.location.lon = lon;
            if (get_elevation(curelem, track))
            {
                fprintf(stderr, ERR_COLOR "\nError read_nodes_from_route: Couldn't get elevation for point #%lld" RESET_COLOR, *(idcnt--));
                free(curelem);
                return 0;
            }

            /* Stitch in list (keep lastelem for add_edges_in) */
            lastelem->next = curelem;
            curelem->next = NULL;

            /* Setup edges_in list */
            curelem->point.edges_in = NULL;

            /* Set ITRA & distance for Dijkstra*/
            curelem->point.itra = 0;
            curelem->point.dist = -1.0;
            curelem->point.visited = 0;

            /* Set return value */
            nodes_read++;

            if (!add_edge_in(curelem, lastelem, head, track))
                return 0;

            /* Order list (if curelem was alreadyy read, merge the two elements) */
            if (order_list(head))
                (*idcnt)--;
            else
                /* Set lastelem to curelem */
                lastelem = curelem;
        }
    }
}

/*! \fn point_list *read_points(const char **files, size_t number_routes);
 * \brief Main function responsible for creating map.
 *
 * Reads points into a sentinel guarded linked list of point_list. Responsible for opening files,
 * creating node points (getting location and elevation data for them).
 *
 * \param files: Pointer to an array of strings containing route and file names in pairs.
 * \param number_routes: The number of trails user provided with .gpx files. Since each route
 * requires two files (route.gpx and track.gpx), number_routes is the number of files / 2.
 *
 * \warning route.gpx and track.gpx files must follow in this exact order.
 * \warning Each route.gpx must have a corresponding track.gpx!
 * \warning Strings containing the file names must contain .gpx extension too!
 * \warning track.gpx must must contain the correct gps location information.
 * \warning route.gpx must must contain the correct gps location information.
 * \return Head pointer for sentinel-guarded linked list of all nodes of the graph (points on the map).
 * \note Returns NULL if error occured.
 */
point_list *read_points(const char **files, size_t number_routes)
{
    if (number_routes == 0)
    {
        fprintf(stderr, ERR_COLOR "\nError read_points: No files specified" RESET_COLOR);
        return NULL;
    }

    /* Setting up sentinel to list*/
    point_list *head = malloc(sizeof(point_list));
    if (head == NULL)
    {
        fprintf(stderr, ERR_COLOR "\nError read_points: Couldn't allocate points head" RESET_COLOR);
        return NULL;
    }

    head->point.edges_in = NULL;
    head->next = NULL;

    FILE *route, *track;

    /* Setting up linked list of points */
    size_t idcnt = 0;
    for (size_t i = 0; i < number_routes * 2;)
    {
        /* Opening route and track file */

        printf(WARN_COLOR "\nReading: %s ... " RESET_COLOR, files[i]);
        route = fopen(files[i], "r");
        if (route == NULL)
        {
            fprintf(stderr, ERR_COLOR "\nError read_points: Couldn't open file %s" RESET_COLOR, files[i]);
            if (strstr(files[i], ".gpx") == NULL)
                fprintf(stderr, ERR_COLOR "\nError read_points: %s doesn't have .gpx extension." RESET_COLOR, files[i]);
            destroy_points(&head);
            return head;
        }
        printf(GREEN_COLOR "done" RESET_COLOR);
        i++;

        printf(WARN_COLOR "\nReading: %s ... " RESET_COLOR, files[i]);
        track = fopen(files[i], "r");
        if (track == NULL)
        {
            fprintf(stderr, ERR_COLOR "\nError read_points: Couldn't open file %s" RESET_COLOR, files[i]);
            if (strstr(files[i], ".gpx") == NULL)
                fprintf(stderr, ERR_COLOR "\nError read_points: %s doesn't have .gpx extension." RESET_COLOR, files[i]);
            destroy_points(&head);
            fclose(route);
            return head;
        }
        printf(GREEN_COLOR "done" RESET_COLOR);
        i++;

        /* Stitching nodes from route file in node list */
        if (!read_nodes_from_route(head, route, track, &idcnt))
        {
            fclose(track);
            fclose(route);
            destroy_points(&head);
            fprintf(stderr, ERR_COLOR "\nError read_points: read_nodes_from_route failed with files %s, %s" RESET_COLOR, files[i - 2], files[i - 1]);
            return NULL;
        }

        fclose(track);
        fclose(route);
    }
    return head;
}

/*! \fn point_list *nearest_point(point point, point_list *head);
 * \brief Looks up nearest point in the graph (on the map) to the provided point.
 *
 * Gets distance to all points in list and returns a pointer to the nearest one.
 * \sa calculateDistance(double lat1, double lon1, double lat2, double lon2)
 *
 * \param point: Point struct containing coordinates.
 * \param head: Pointer to the sentinel of the linked list of points.
 *
 * \return Pointer to nearest point in list (NULL if error occured).
 * \note Notifies user if selected point is more than 1 km away from the nearest point it found.
 */
point_list *nearest_point(point point, point_list *head)
{
    if (head == NULL || head->next == NULL)
    {
        fprintf(stderr, ERR_COLOR "\nError nearest_point: List is empty" RESET_COLOR);
        return NULL;
    }

    point_list *nearest = head->next, *curelem = head->next;
    double mindist = calculateDistance(point.location.lat, point.location.lon, curelem->point.location.lat, curelem->point.location.lon);

    /* Search for nearest point */
    while (curelem != NULL)
    {
        double curdist = calculateDistance(point.location.lat, point.location.lon, curelem->point.location.lat, curelem->point.location.lon);

        if (curdist < mindist)
        {
            mindist = curdist;
            nearest = curelem;
        }

        curelem = curelem->next;
    }

    /* Warn user if selected point is further than 1km from nearest map point */
    if (mindist > 1)
    {
        printf(WARN_COLOR "\nWarning: Selected point is %.1f km from nearest trail intersection!\n"
                          "Do you want to proceed? (y/n)\n" RESET_COLOR,
               mindist);
        char ans;
        fseek(stdin, 0, SEEK_END);
        scanf("%c", &ans);
        if (ans != 'y' && ans != 'Y')
            return NULL;
    }

    return nearest;
}

/*! \fn size_t count_points(point_list *head);
 * \brief Counts number of points in linked list.
 * \param head: Pointer to the sentinel of the linked list of points.
 * \return Number of points.
 */
size_t count_points(point_list *head)
{
    size_t count = 0;
    head = head->next;

    while (head != NULL)
    {
        head = head->next;
        count++;
    }

    return count;
}

/*! \fn double calculate_itra(double origin_itra, edge edge);
 * \brief Calculate ITRA-score for a path consisting of a path to a previous point
 * and an edge from the previous point to the current point.
 * \param origin_itra: ITRA-score of the path from the starting point to the previous point.
 * \param edge: edge from previous point to current point containing distance, up and down level information.
 * \return ITRA-score of the path from start to the current point.
 */
double calculate_itra(double origin_itra, edge edge)
{
    return origin_itra + (edge.dist + (edge.up - edge.down) / 100.0);
}

/*! \fn void improve_dist(point_list *point);
 * \brief Tries to improve on the shortest distance of given point along all of its edges.
 *
 * Looks through each edge in edges_in and tries, if the distance coming along that edge would be smaller than
 * the current distance.
 *
 * \param point: The point in question.
 * \return Void
 */
void improve_dist(point_list *point)
{
    edges_list *edge_in = point->point.edges_in;

    /* Try to improve dist with each edge in */
    while (edge_in != NULL)
    {
        /*
        If the distance of the point reached from the currently checked edge in is less than the current distance
        (edge_in->edge.from->point.dist + edge_in->edge.dist < point->point.dist)
            OR
            the points distance is infinity (point->point.dist < 0)

        AND
        the distance of the point which the edge originates from is nor infinity (edge_in->edge.from->point.dist >= 0)
         */
        if ((point->point.dist < 0 || edge_in->edge.from->point.dist + edge_in->edge.dist < point->point.dist) && edge_in->edge.from->point.dist >= 0)
        {
            /* Set distance and itra to the itra and distance of the route from origin point along the edge to the current point */
            point->point.dist = edge_in->edge.from->point.dist + edge_in->edge.dist;
            point->point.itra = calculate_itra(edge_in->edge.from->point.itra, edge_in->edge);
        }

        edge_in = edge_in->next;
    }
}

/*! \fn void set_smallest_visited(point_list *head);
 * \brief Sets point_list->point.visited 1 for the point with the smallest distance from start which is not visited yet.
 * \param head: Pointer to the sentinel of the linked list of points.
 * \return Void
 */
void set_smallest_visited(point_list *head)
{
    head = head->next;
    point_list *smallest = NULL;

    /* Search for smallest distance point */
    while (head != NULL)
    {
        /* IF
                    smallest has been not set yet (smallest == NULL)
                    OR
                    the distance of the current point is smaller than the current smallest distance (head->point.dist < smallest->point.dist)
                AND
                the points distance is not infinity (represented by -1) (head->point.dist > 0)
            AND
            point is not visited (head->point.visited == 0)
         */
        if (((smallest == NULL || head->point.dist < smallest->point.dist) && head->point.dist > 0) && head->point.visited == 0)
            smallest = head;
        head = head->next;
    }

    /* If smallest was actually found set visited 1 */
    if (smallest != NULL)
        smallest->point.visited = 1;
}

/*! \fn void find_shortest_path(point_list *root, point_list *points_head);
 * \brief Main function responsible for Dijkstra and finding shortest path.
 *
 * Finds shortest path for all points in an already existing graph (map) for a given starting point.
 *
 * \param root: Pointer to a point which is considered the root. All distances will be calculated from this point.
 * \param points_head: Pointer to the sentinel of the linked list of points.
 * \return Void.
 */
void find_shortest_path(point_list *root, point_list *points_head)
{
    /* Set up root for Dijkstra */
    root->point.dist = 0;
    root->point.visited = 1;

    /* Set up break condition values */
    size_t number_visited = 1;
    size_t number_points = count_points(points_head);

    /* Run Dijkstra up until all points are visited */
    while (number_visited <= number_points)
    {
        point_list *curelem = points_head->next;

        /* In each iteration try to improve distance for all points */
        while (curelem != NULL)
        {
            if (curelem->point.visited == 0)
            {
                improve_dist(curelem);
            }
            curelem = curelem->next;
        }

        /* Set point with the smallest distance visited */
        set_smallest_visited(points_head);
        number_visited++;
    }
}

/*! \fn int print_route(point start_user, point dest_user, point_list *map_head);
 * \brief Main function responsible for planning and printing route.
 *
 * Gets nearest points on map to user specified points (nearest_point), calls Dijkstra (find_shortest_path),
 * prints route (distance and ITRA) and frees up memory (destroy_points)
 *
 * \param start_user: Point containing coordinates of start point specified by user.
 * \param dest_user: Point containing coordinates of destination point specified by user.
 * \param map_head: Pointer to the sentinel of the linked list of points.
 * \return Status indication: 0 if planning was succesfull, 1 otherwise.
 */
int print_route(point start_user, point dest_user, point_list *map_head)
{
    /* Get nearest point on map to user selected points */
    point_list *start = nearest_point(start_user, map_head);
    point_list *dest = nearest_point(dest_user, map_head);

    /* Error handling */
    if (start == NULL || dest == NULL)
    {
        start == NULL ? fprintf(stderr, ERR_COLOR "Error print_route: Couldnt find start lat=%f lon=%f" RESET_COLOR,
                                start_user.location.lat, start_user.location.lon)
                      : fprintf(stderr, ERR_COLOR "Error print_route: Couldnt find destination lat=%f lon=%f" RESET_COLOR,
                                start_user.location.lat, start_user.location.lon);
        destroy_points(&map_head);
        return 1;
    }

    /* Printing info */
    printf(INFO_COLOR
           "\nPlanning...\n\n"
           "From:\n"
           "\tlat=%f\n"
           "\tlon=%f\n\n"
           "To:\n"
           "\tlat=%f\n"
           "\tlon=%f\n" RESET_COLOR,
           start->point.location.lat, start->point.location.lon, dest->point.location.lat, dest->point.location.lon);

    /* Run Dijkstra */
    find_shortest_path(start, map_head);

    /* If after Dijkstra dest dist is <0 (inf is represented by -1) */
    if (dest->point.dist < 0)
    {
        fprintf(stderr, ERR_COLOR
                "\nError print_route: find_shortest path couldn't find a route. Are all of the trails connected to eachother?" RESET_COLOR);

        printf("\n---------------------------------------------------------------------------------------------------\n" ERR_COLOR
               "\nPlanning failed. Unable to find path between start and destination points." RESET_COLOR);

        destroy_points(&map_head);
        return 1;
    }

    /* Print results */
    printf(INFO_COLOR
           "\nTotal distance: %.2f km (+ %.2f km to nearest path intersection)"
           "\nITRA-score (distance + elevation diff. / 100): %.2f\n\n\n\n" RESET_COLOR,
           dest->point.dist, calculateDistance(start_user.location.lat, start_user.location.lon,
           start->point.location.lat, start->point.location.lon), dest->point.itra);

    /* Free memory (nono leak nono) */
    destroy_points(&(map_head));
    return 0;
}

/*! \fn int main(int argc, char const *argv[]);
 * \brief Main function. Responsible for: runtime parameters error handling, displaying user info,
 * getting user input for map files and planning parameters, calling read_points and print_route,
 * displaying help information.
 *
 * First main checks running parameters, then calls read_points. If map was built succesfully it displays
 * status message and asks for input on start and destination. If input was successful it calls print_route.
 * If --h flag is provided or error occurs, it displays help message.
 *
 * \param argc: Standard C run argument count.
 * \param argv: Standard C pointer to run argument strings.
 * \warning Run arguments should always be according to specifications.
 * \return Status indication: 0 if no runtime errors were encountered, 1 otherwise (if help was displayed).
 */
int main(int argc, char const *argv[])
{

    /* No input files */
    if (argc < 2)
    {
        fprintf(stderr, ERR_COLOR "\nError main: No input files specified!" RESET_COLOR);
        goto help;
    }

    /* --h flag */
    if (!strcmp(argv[1], "--h"))
        goto help;

    /* argc - 1 is odd: 2 files per trail! */
    if ((argc - 1) % 2 != 0)
    {
        fprintf(stderr, ERR_COLOR "\nError main: Number of specified files is odd! (One (or more) files are missing)" RESET_COLOR);
        goto help;
    }

    /* Build map */
    point_list *map = read_points(&(argv[1]), (argc - 1) / 2);
    if (map == NULL)
        goto help;

    /* Create user specified start end dest points */
    point start, dest;

    printf(GREEN_COLOR "\nMap created succesfully!\n\n" RESET_COLOR
               INPUT_COLOR "Please provide start end end point to your route! "
                       "(Lat. and Lon. separated by any whitespace character(s)):\n\n" RESET_COLOR);

    printf(INPUT_COLOR "Start coordinates:\n" RESET_COLOR);
    if (scanf("%lf %lf", &start.location.lat, &start.location.lon) != 2)
    {
        fprintf(stderr, ERR_COLOR "\nError main: Couldn't read start coordinates" RESET_COLOR);
        destroy_points(&map);
        goto help;
    }

    printf(INPUT_COLOR "\n\nDestination coordinates:\n" RESET_COLOR);
    if (scanf("%lf %lf", &dest.location.lat, &dest.location.lon) != 2)
    {
        fprintf(stderr, ERR_COLOR "\nError main: Couldn't read dest coordinates" RESET_COLOR);
        destroy_points(&map);
        goto help;
    }

    /* Plan route and print it */
    if (print_route(start, dest, map))
    {
        fprintf(stderr, ERR_COLOR "\nError main: print_route has terminated with exit code 1" RESET_COLOR);
        goto help;
    }

    return 0;

/* Help message */
help:

    printf(WARN_COLOR "\n\n---------------------------------------------------------------------------------------------------"
                      "\nUsage help:\n\n"
                      "\tDisplay help message: <program_name> --h\n\n"
                      "\tCreate map from track and route .gpx files:\n"
                      "\t\t<program_name> <route1>.gpx <ele-track1>.gpx <route2>.gpx <ele-track2>.gpx ...\n"
                      "\t\tPlease make sure each route file has a corresponding ele-track file!\n\n"
                      "\tIf creation of map was succesfull the program will ask for input of start and end points\n"
                      "\t\tExpected coordinate input format: Decimal coordinates (with decimal point).\n"
                      "\t\tLatitude and longitude should be separated with any whitespace character\n"
                      "\t\t\tExample: 48.0976397 20.7301719\n\n\n" RESET_COLOR);
    return 1;
}