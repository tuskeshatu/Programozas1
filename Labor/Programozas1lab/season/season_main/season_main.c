#include <stdio.h>

#include <stdio.h>

enum season
{
    SPRING,
    SUMMER,
    AUTUMN,
    WINTER
};

void print_season(enum season season)
{
    switch (season)
    {
    case SPRING:
        printf("spring");
        break;

    case SUMMER:
        printf("summer");
        break;

    case AUTUMN:
        printf("autumn");
        break;

    case WINTER:
        printf("winter");
        break;
    }
}

enum season month2season(int month)
{
    switch (month)
    {
    case 1:
        return WINTER;
    case 2:
        return WINTER;
    case 3:
        return SPRING;
    case 4:
        return SPRING;
    case 5:
        return SPRING;
    case 6:
        return SUMMER;
    case 7:
        return SUMMER;
    case 8:
        return SUMMER;
    case 9:
        return AUTUMN;
    case 10:
        return AUTUMN;
    case 11:
        return AUTUMN;
    case 12:
        return WINTER;
    }
}

int main(void)
{

    int curmonth;
    while (scanf("%d", &curmonth) == 1)
    {
        print_season(month2season(curmonth));
        printf(" ");
    }
    
    return 0;
}