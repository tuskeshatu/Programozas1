#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

typedef struct henger
{
    double radius, height;
} cylinder;

cylinder read_cylinder(void)
{
    cylinder cyl;

    scanf("%lf %lf", &cyl.radius, &cyl.height);

    return cyl;
}

double cylinder_volume(cylinder cyl)
{
    return cyl.radius * cyl.radius * M_PI * cyl.height;
}

int main(void)
{
    cylinder curcyl, cylarr[10];

    for (int i = 0; i < 10; i++)
    {
        cylarr[i] = read_cylinder();
    }
    
    for (int i = 0; i < 10; i++)
    {
        printf("%.2f ", cylinder_volume(cylarr[9-i]));
    }

    return 0;
}