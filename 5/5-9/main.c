#include <stdio.h>

static char daytab[2][13] =
    {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
static short year_day_number[2] = {365, 366};
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if(month < 1 || month > 12)
    {
        printf("Month must be from 1 to 12\n");
        return -1;
    }
    else if(day < 1 || day > *(*(daytab + leap) + month))
    {
        printf("%d month's day must be %d to %d\n", month, 1, *(*(daytab + leap) + month));
        return -1;
    }
    for (i = 1; i < month; i++)
        day += *(*(daytab + leap) + i);
    return day;
}
/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    if(pmonth == NULL || pday == NULL)
    {
        printf("pmonth or pday is point NULL\n");
        return;
    }
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if(yearday < 1 || yearday > *(year_day_number + leap))
    {
        printf("In %d year, yearday must be %d to %d", year, 1, *(year_day_number + leap));
        return;
    }
    for (i = 1; yearday > *(*(daytab + leap) + i); i++)
        yearday -= *(*(daytab + leap) + i);
    *pmonth = i;
    *pday = yearday;
}

int main(void)
{
    int month, day;
    int day_in_year = day_of_year(2020, 1, 29);
    printf("%d\n", day_in_year);
    month_day(2020, 29, &month, &day);
    printf("%d,%d\n", month, day);
}