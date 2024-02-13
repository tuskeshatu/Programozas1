#include <stdio.h>

typedef struct time
{
    int hour, min, sec;
} time;

int time2sec(time time)
{
    return time.hour * 3600 + time.min * 60 + time.sec;
}

time sec2time(int totalsec)
{
    time time;

    while (totalsec < 0)
    {
        totalsec = 86400 + totalsec;
    }

    if (totalsec >= 86400)
        totalsec = totalsec % 86400;

    time.hour = totalsec / 3600;
    time.min = (totalsec - time.hour * 3600) / 60;
    time.sec = totalsec - time.hour * 3600 - time.min * 60;

    return time;
}

time timeplus(time time1, time time2)
{
    return sec2time(time2sec(time1) + time2sec(time2));
}

int timecmp(time time1, time time2)
{
    return time2sec(time1) - time2sec(time2);
}

int main(void)
{
    time t1 = {2, 5, 0};
    int d = time2sec(t1);      // 7500
    time t2 = sec2time(6002);  // 1:40:02
    time t3 = sec2time(86401); // 23:59:59
    return 0;
}