#include <stdio.h>

#define TRUCK_CAP 2.0

int main (void)
{
    double debris, truckload = 0.0;

    while(scanf("%lf", &debris) != EOF)
    {
        if (truckload + debris > TRUCK_CAP)
        {
            printf("%.3f ", TRUCK_CAP - truckload);
            truckload = debris;
        }
        else
            truckload += debris;
    }

    printf("%.3f", TRUCK_CAP - truckload);

    return 0;
}