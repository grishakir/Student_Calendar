#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../Headers/DateTime.h"
#include "../Headers/Auxiliary.h"




Date setDate(char* inputStr)
{
/*Date setDate(char* inputStr) - принимает на вход строку,
 * которую выводит в форматной
 * строке <<Enter \%s date in DD/MM/YYYY format:>>.
 * Запрашивает у пользователя дату,
 * проверяет ее корректность и возвращает структуру Date с
 * введенными пользователем данными */
    Date date;
    char tmp[20];
    int i, isCorrect, day, month, year;
    while (1)
    {
        isCorrect = 1;
        printf("Enter %s date in DD/MM/YYYY format: ", inputStr);
        gets(tmp);
        if (strlen(tmp) == 10 && tmp[2] == '/' && tmp[5] == '/')
        {
            for (i = 0; i < 10; i++)
            {
                if (i != 2 && i != 5)
                {
                    if (!isdigit(tmp[i]))
                    {
                        isCorrect = 0;
                        break;
                    }
                }

            }

            if (isCorrect)
            {
                day = fromCharToInt(tmp[0]) * 10 + fromCharToInt(tmp[1]);
                month = fromCharToInt(tmp[3]) * 10 + fromCharToInt(tmp[4]);
                year = fromCharToInt(tmp[6])* 1000 +
                        fromCharToInt(tmp[7]) * 100 +
                        fromCharToInt(tmp[8]) * 10 + fromCharToInt(tmp[9]);
                isCorrect = checkDateCorrection(day, month, year);
            }
        } else
            isCorrect = 0;

        if (isCorrect)
            break;
        printf("Incorrect input!\n");
   }


    date.day = day;
    date.month = month;
    date.year = year;
    date.dayOfWeek = getDayOfWeek(day, month, year);
    return date;
}

Time setTime(char* inputStr)
{
/*  принимает на вход строку, которую выводит в форматной строке
 * <<Enter \%s time in HH/MM format:>>. Запрашивает у пользователя время,
 * проверяет его корректность и возвращает структуру Time
 * с введенными пользователем данными */
    Time time;
    char tmp[20];
    int isCorrect, hour, min;
    while (1) {
        isCorrect = 1;
        printf("Enter %s time in HH/MM format: ", inputStr);
        gets(tmp);

        if (tmp[2] == '/' && isdigit(tmp[0]) && isdigit(tmp[1])
        && isdigit(tmp[3]) && isdigit(tmp[4]) && strlen(tmp) == 5)
        {
            hour = fromCharToInt(tmp[0]) * 10 + fromCharToInt(tmp[1]);
            min = fromCharToInt(tmp[3]) * 10 + fromCharToInt(tmp[4]);

            if (hour > 23 || hour < 0 || min > 59 || min < 0)
            {
                isCorrect = 0;
            }
        }
        else
        {
            isCorrect = 0;
        }

        if (isCorrect)
        {
            break;
        }
        else
        {
            printf("Incorrect input!");
        }
    }

    time.min = min;
    time.hour = hour;
    return time;
}

int checkDateCorrection(int day, int month, int year)
{
    /* принимает на вход значения дня, месяца и года.
     * Проверяет их корректность.
     * Возвращает 1, если дата корректна и 0, если нет 1. */
    int maxCorrectDay;

    if (year < MIN_CORRECT_YEAR || year > MAX_CORRECT_YEAR)
    {
        return 0;
    }

    if (month < DT_JANUARY || month > DT_DECEMBER)
    {
        return 0;
    }

    if (month == DT_APRIL || month == DT_JUNE || month == DT_SEPTEMBER ||
    month == DT_NOVEMBER)
    {
        maxCorrectDay = 30;
    }
    else if (month != DT_FEBRUARY)
    {
        maxCorrectDay = 31;
    }
    else
    {
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        {
            maxCorrectDay = 29;
        }
        else
        {
            maxCorrectDay = 28;
        }
    }

    if (day < 1 || day > maxCorrectDay)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int getDayOfWeek(int day, int month, int year)
{
/* возвращает номер деня недели, по введенному дню */
    int a;
    a = (14 - month) / 12;
    year = year - a;
    month = month + 12 * a - 2;
    switch ((day + (31 * month) / 12 + year +
        year / 4 - year / 100 + year / 400) % 7)
    {
        case 0:
            return DT_SUNDAY;
        case 1:
            return DT_MONDAY;
        case 2:
            return DT_TUESDAY;
        case 3:
            return DT_WEDNESDAY;
        case 4:
            return DT_THURSDAY;
        case 5:
            return DT_FRIDAY;
        default:
            return DT_SATURDAY;
    }
}

int dateLessEq(Date first, Date second)
{
/* принимает 2 даты. Возвращает 1, если
 * 1я дата меньше или равна 2й, иначе 0 */
    if (first.year < second.year)
        return 1;
    else if (first.year > second.year)
        return 0;
    else if (first.year == second.year)
    {
        if (first.month < second.month)
            return 1;
        else if (first.month > second.month)
            return 0;
        else if (first.month == second.month)
        {
            if (first.day <= second.day)
                return 1;
            else return 0;
        }
    }
    return 0;
}

int timeMore(Time first, Time second)
{
/* принимает 2 времени. Возвращает 1,
 * если 1е время больше 2го, иначе 0 */
    if (first.hour > second.hour)
        return 1;
    else if (first.hour < second.hour)
        return 0;
    else if (first.hour == second.hour)
    {
        if (first.min > second.min)
            return 1;
        else
            return 0;
    }
    return 0;
}

char* getDayOfWeekName(int dayOfWeek)
{
/* принимает на вход номер дня недели, возвращает строку с его назвванием */
    switch (dayOfWeek)
    {
        case 0:
            return "Monday";
        case 1:
            return "Tuesday";
        case 2:
            return "Wednesday";
        case 3:
            return "Thursday";
        case 4:
            return "Friday";
        case 5:
            return "Saturday";
        case 6:
            return "Sunday";
        default:
            return "";
    }
}

int getNumOfDays(Date first, Date second)
{
    /* принимает на вход 2 даты. Возвращает количество дней между ними */
    Date tmpDate;
    int numOfDays = 0;

    if (!dateLessEq(first, second))
    {
        tmpDate = first;
        first = second;
        second = tmpDate;
    }

    tmpDate = second;

    if (second.year - first.year > 1)
    {
        tmpDate.year = second.year - 1;
        while (tmpDate.year != first.year)
        {
            numOfDays += 365 + (tmpDate.year % 400 == 0 ||
                    (tmpDate.year % 100 != 0 &&
                    tmpDate.year % 4 == 0) ? 1 : 0);
            tmpDate.year--;
        }
    }

    while (second.month != first.month || second.year != first.year
        || second.day != first.day)
    {
        if (second.day > 0)
        {
            numOfDays++;
            second.day--;
        }
        else
        {
            if (second.month == 1)
            {
                second.year--;
                second.month = 12;
                second.day = DT_NUM_DAYS_DECEMBER;
            }
            else
            {
                second.month--;
                switch (second.month) {
                    case DT_JANUARY:
                        second.day = DT_NUM_DAYS_JANUARY;
                        break;
                    case DT_FEBRUARY:
                        second.day = 28 + (second.year % 400 == 0 ||
                                (second.year % 100 != 0 &&
                                second.year % 4 == 0) ? 1 : 0);
                        break;
                    case DT_MARCH:
                        second.day = DT_NUM_DAYS_MARCH;
                        break;
                    case DT_APRIL:
                        second.day = DT_NUM_DAYS_APRIL;
                        break;
                    case DT_MAY:
                        second.day = DT_NUM_DAYS_MAY;
                        break;
                    case DT_JUNE:
                        second.day = DT_NUM_DAYS_JUNE;
                        break;
                    case DT_AUGUST:
                        second.day = DT_NUM_DAYS_AUGUST;
                        break;
                    case DT_SEPTEMBER:
                        second.day = DT_NUM_DAYS_SEPTEMBER;
                        break;
                    case DT_OCTOBER:
                        second.day = DT_NUM_DAYS_OCTOBER;
                        break;
                    case DT_NOVEMBER:
                        second.day = DT_NUM_DAYS_NOVEMBER;
                        break;
                    case DT_JULY:
                        second.day = DT_NUM_DAYS_JULY;
                        break;
                    default:
                        break;
                }

            }
        }
    }

    return numOfDays;
}

int getNumOfWeek(Date date)
{
/* принимает на вход дату.
 * Возвращает номер недели по учебному плану,
 * в которую эта дата входит */
    int firstSeptemberDayOfWeek, numOfDays;
    Date firstDayOfFirstWeek;

    if (date.month >= 9) {
        firstSeptemberDayOfWeek = getDayOfWeek(01, 9, date.year);
        firstDayOfFirstWeek.year = date.year;
    }
    else
    {
        firstSeptemberDayOfWeek = getDayOfWeek(01, 9, date.year - 1);
        firstDayOfFirstWeek.year = date.year - 1;
    }

    if (firstSeptemberDayOfWeek == 5) {
        firstDayOfFirstWeek.month = 9;
        firstDayOfFirstWeek.day = 3;
    }
    else if (firstSeptemberDayOfWeek == 6)
    {
        firstDayOfFirstWeek.month = 9;
        firstDayOfFirstWeek.day = 2;
    }
    else if (firstSeptemberDayOfWeek == 0)
    {
        firstDayOfFirstWeek.month = 9;
        firstDayOfFirstWeek.day = 1;
    }
    else if (firstSeptemberDayOfWeek == 1)
    {
        firstDayOfFirstWeek.month = 8;
        firstDayOfFirstWeek.day = 31;
    }
    else if (firstSeptemberDayOfWeek == 2)
    {
        firstDayOfFirstWeek.month = 8;
        firstDayOfFirstWeek.day = 30;
    }
    else if (firstSeptemberDayOfWeek == 3)
    {
        firstDayOfFirstWeek.month = 8;
        firstDayOfFirstWeek.day = 29;
    }
    else if (firstSeptemberDayOfWeek == 4)
    {
        firstDayOfFirstWeek.month = 8;
        firstDayOfFirstWeek.day = 28;
    }



    return (getNumOfDays(firstDayOfFirstWeek, date)/7 + 1);
}

void shiftDateDown(Date *date)
{
/* принимает на вход указатель на Date.
 * Смещает дату на 1 день вниз по календарю */
    int maxCorrectDay;
    (*date).day++;

    if ((*date).month == DT_APRIL || (*date).month == DT_JUNE
    || (*date).month == DT_SEPTEMBER || (*date).month == DT_NOVEMBER)
    {
        maxCorrectDay = 30;
    }
    else if ((*date).month != DT_FEBRUARY)
    {
        maxCorrectDay = 31;
    }
    else
    {
        if ((*date).year % 400 == 0 ||
        ((*date).year % 100 != 0 && (*date).year % 4 == 0))
        {
            maxCorrectDay = 29;
        }
        else
        {
            maxCorrectDay = 28;
        }
    }

    if ((*date).day > maxCorrectDay)
    {
        (*date).month++;
        (*date).day -= maxCorrectDay;
    }

    if ((*date).month > 12)
    {
        (*date).month -= 12;
        (*date).year++;
    }

    (*date).dayOfWeek = getDayOfWeek((*date).day,
                                     (*date).month, (*date).year);
}

void shiftDateUp(Date *date)
{
/* принимает на вход указатель на Date.
 * Смещает дату на 1 день верх по календарю */
    int maxCorrectDay, previousMonth = (*date).month - 1;
    int yearOfPreviousMonth = (*date).year - (previousMonth > 0 ? 0 : 1);
    previousMonth = (previousMonth > 0 ? previousMonth : 12);
    (*date).day--;

    if ((*date).day > 0)
    {
        (*date).dayOfWeek = getDayOfWeek(
                (*date).day,
                (*date).month,
                (*date).year);
        return;
    }

    if (previousMonth  == DT_APRIL || previousMonth == DT_JUNE
    || previousMonth == DT_SEPTEMBER || previousMonth == DT_NOVEMBER)
    {
        maxCorrectDay = 30;
    }
    else if (previousMonth != DT_FEBRUARY)
    {
        maxCorrectDay = 31;
    }
    else
    {
        if (yearOfPreviousMonth % 400 == 0 ||
        (yearOfPreviousMonth % 100 != 0 && yearOfPreviousMonth % 4 == 0))
        {
            maxCorrectDay = 29;
        }
        else
        {
            maxCorrectDay = 28;
        }
    }

    if ((*date).day < 1)
    {
        (*date).month--;
        (*date).day += maxCorrectDay;
    }
    else
    {
        (*date).dayOfWeek = getDayOfWeek(
                (*date).day,
                (*date).month,
                (*date).year);
        return;
    }

    if ((*date).month < 1)
    {
        (*date).month += 12;
        (*date).year--;
    }

    (*date).dayOfWeek = getDayOfWeek(
            (*date).day,
            (*date).month,
            (*date).year);
}