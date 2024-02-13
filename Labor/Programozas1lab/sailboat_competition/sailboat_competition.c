#include <math.h>

typedef struct
{
    double x, y;
} point;

typedef struct
{
    int hour, minute, second;
} time;

typedef struct
{
    point position;
    time interval;
} record;

int in_seconds(time time)
{
    return time.hour * 3600 + time.minute * 60 + time.second;
}

double distance(point pos1, point pos2)
{
    return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

double average_speed(record recs[], int size_recs)
{
    double totaldist = 0, totaltime = 0;
    for (int i = 1; i < size_recs; i++)
    {
        totaldist += distance(recs[i].position, recs[i - 1].position);
        totaltime += in_seconds(recs[i].interval);
    }
    return totaldist / totaltime;
}