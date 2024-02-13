\page dev_guide Developer guide
\tableofcontents

# Representing a map

## .gpx files

In my implementation a map consists of one or multiple trails put together. To accurately store a trail you basically
need to store a bunch of gps coordinates with elevation data. This is commonly done using the .gpx file extension, which
is mainly used by sports trackers to represent a path, which the recorder travelled along. .gpx files are xml based, so
it is easily readable as a text file. 

### Route type .gpx

There are multiple formats that a .gpx file can take. One of them is the route format. The route scheme is optimised to give directions. This means that it only has the intersections (in some cases other points of interest) marked in it, without elevation data. This comes in handy, as the program only has to store the intersections in memory, which can drastically reduce memory usage.

### Track type .gpx

Track .gpx files hold every recorded gps point with elevation data along a path. This is needed in order to calculate the distance and the climb and descent of the trail in between intersections.

In my program I represent maps as a graph which has nodes where the route.gpx files have records (basically intersections) and
the nodes (points of intersections on the map) have edges running with the corresponding distance and elevation data.

## Reading points into a graph

The route and track files are provided as arguments for the program.

### Storing points as nodes

I store the graph as a linked list of nodes (with a front sentinel). Each node has a pointer to a linked list in it, which contains the
edges coming into the node (see: point_list and edges_list). The way data is read from the route and track files is that the program reads the route file, finds a node then looks up the edge between the previous node and the current node. This is accomplished with the read_points() and 
the read_nodes_from_route() functions. This works because of the sequential nature of the .gpx files the previous node in the list is always neighbouring the currently read node, so add_edges_in() can add in edges based only the sequence of elements in the list.

\note In order to have a trail, which one can traverse in both directions there is a need to add edges in the reverse direction, when an edge is added.

### Merging nodes

The program also needs to merge points in case of an intersection or a circle path. Firstly the point is read normaly, it has its edges added in
and then the order_list() function merges the two points. This means that the lastly read point will be merged with the one proceeding it
in the list; their edges_in list will be stitched together, the point id will continue to count as if the currently read point never existed
and the order_merged_edges() function will go through the list to make sure that the edges referring to the merged node are now referring to
the correct node.

Rinse and repeat for all files and all of the trails are now stored in a list as a graph.

# Searching for shortest path from start point

In my implementation I decided to use a slightly modified version of the Dijkstra-algorithm. It is a very efficient algorithm, since
we are only looking for the distances in our graph from a certain root node.

## Defining root and destination node

The task is quite simple: get the nodes in the graph, which are closest to the coordinates specified by the user (nearest_point()).

## The Dijkstra-algorithm

The first step is to initialize the algorithm by setting all of the points distances to infinity and make them unvisited. Luckily this is
accomplished during the map creation phase. The find_shortest_path() function only needs to set the root visited and its distance
to 0 and is ready to go.

The algorithm basically has 2 steps:

<ol>
    <li>Go through every unvisited point and try to improve its distance (improve_dist())</li>
    <li>Make the closest (smallest distance) point which is not visited visited (set_smallest_visited())</li>
</ol>

When all of the points are visited, the algorithm is done.

At every improvement the ITRA-score is also adjusted accordingly.

# Output results

When the algorithm finished calculating the shortest distances it outputs to the user the destination nodes distance and ITRA-score.

# Shortcomings

## Planning phase

Though reading and storing only the records of the map outlined in the route files is easy on memory usage it has a downside too.
The program is only able to plan from stored node to stored node so if there is a long trail section without any intersections (records
in the route.gpx), one cannot plan accurately. This can also effect the accuracy of the planning because if someone wants to go not from
intersection to intersection, rather from the middle of a trail to a middle of another trail, the planning will occur from nearest intersection to
nearest intersection.

## Computing efficiency

I acknowledge, that calculating the distance from the root for every point even if there is only one point of interest is a huge
waste of computational power but still, the Dijkstra-algorithm is quite efficient in comparison to other counterparts.

It would also be more efficient to store a graph with edge lists but due to lack of time and knowledge/skills this was not implemented.

## Safety

This code is memory safe according to my tests and debugmalloc.h. The destroy_points() and destroy_edges() functions cover the normal and error cases too. Though the code is memory safe scanf-s and the fgets to buffer give way to easy exploits but since there should be no sensitive data involved, no files open to write and only gps coordinates to deal with, this should be no problemo.

# Errors compiling

\warning **You may get an error when compiling with gcc!**

```console
gcc itra_calc.c -Wall -Werror -o itra_calc.exe
```

This error is caused by debugmalloc.h. To get **itra_calc.c** to compile remove the *-Werror* flag.