#pragma once
#define MIN_CORRECT_YEAR 2020
#define MAX_CORRECT_YEAR 2021

#define DT_JANUARY 1
#define DT_FEBRUARY 2
#define DT_MARCH 3
#define DT_APRIL 4
#define DT_MAY 5
#define DT_JUNE 6
#define DT_JULY 7
#define DT_AUGUST 8
#define DT_SEPTEMBER 9
#define DT_OCTOBER 10
#define DT_NOVEMBER 11
#define DT_DECEMBER 12

#define DT_MONDAY 0
#define DT_TUESDAY 1
#define DT_WEDNESDAY 2
#define DT_THURSDAY 3
#define DT_FRIDAY 4
#define DT_SATURDAY 5
#define DT_SUNDAY 6


#define DT_NUM_DAYS_JANUARY 31
#define DT_NUM_DAYS_MARCH 31
#define DT_NUM_DAYS_APRIL 30
#define DT_NUM_DAYS_MAY 31
#define DT_NUM_DAYS_JUNE 30
#define DT_NUM_DAYS_JULY 31
#define DT_NUM_DAYS_AUGUST 31
#define DT_NUM_DAYS_SEPTEMBER 30
#define DT_NUM_DAYS_OCTOBER 31
#define DT_NUM_DAYS_NOVEMBER 30
#define DT_NUM_DAYS_DECEMBER 31

typedef struct Date
{
    int day;
    int month;
    int year;
    int dayOfWeek;
} Date;

typedef struct Time
{
    int hour;
    int min;
} Time;

Date setDate(char* inputStr);

int checkDateCorrection(int day, int month, int year);

int getDayOfWeek(int day, int month, int year);

Time setTime(char* inputStr);

int dateLessEq(Date first, Date second);

int timeMore(Time first, Time second);

char* getDayOfWeekName(int dayOfWeek);

int getNumOfDays(Date first, Date second);

int getNumOfWeek(Date date);

void shiftDateDown(Date *date);

void shiftDateUp(Date *date);