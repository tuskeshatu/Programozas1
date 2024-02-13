#include <stdio.h>
#include <math.h>

double calcmovetime(int startx, int starty, int endx, int endy)
{
    int distx, disty;
    double movetime;

    /*calculate distances*/
    distx = abs(endx - startx);
    disty = abs(endy - starty);

    /*bigger distance defines time needed for movement*/
    if (distx > disty)
        movetime = (double)distx / 5000;
    else
        movetime = (double)disty / 5000;

    return movetime;
}

int main(void)
{
    double assemblytime = 0;

    int tapeusage[5] = {0}, curpoz[2] = {0}, targetpoz[2], curtape, curhead;

    char command;

    while (scanf("%c", &command) != EOF)
    {

        /* load command */
        if (command == 'L')
        {
            scanf("%d %d", &curtape, &curhead);

            /* do pick-up */
            tapeusage[curtape - 1]++;

            targetpoz[0] = -500;
            targetpoz[1] = 300 * curtape;

            /*calculate time needed to move to pick-up point and add to total*/
            assemblytime = assemblytime + calcmovetime(curpoz[0], curpoz[1], targetpoz[0], targetpoz[1]) + 0.1;

            curpoz[0] = targetpoz[0];
            curpoz[1] = targetpoz[1];
        }

        /* place command */
        if (command == 'P')
        {
            scanf("%d %d %d", &targetpoz[0], &targetpoz[1], &curhead);

            /* do place */

            /*calculate time needed to move to pick-up point and add to total*/
            assemblytime = assemblytime + calcmovetime(curpoz[0], curpoz[1], targetpoz[0], targetpoz[1]) + 0.1;

            curpoz[0] = targetpoz[0];
            curpoz[1] = targetpoz[1];
        }
    }

    printf("Assembly time: %.2f s\nPart usage", assemblytime);
    for (int i = 0; i < 5; i++)
    {
        printf("\n\tTape %d: %d", i + 1, tapeusage[i]);
    }

    return 0;
}
