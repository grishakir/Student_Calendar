
#pragma once
#include "DateTime.h"

typedef struct
{
    char name[70];
    Time startTime;
    Time endTime;
    Date startDate;
    Date endDate;
    int type;
    int form;
    int frequency;
    char location[70];
    char teacher[70];
} Lesson;

typedef struct
{
    char name[70];
    char controlType[70];
    Date controlDate;
    Lesson lectures;
    Lesson practices;
    Lesson laboratories;
} Subject;

Lesson setLesson(int lessonType, char lessonName[70]);

char* setControlType();

Subject createSubject();

int setLessonForm();

int setLessonFrequency();

void printLesson(Lesson lesson);

void editSubject(Subject *subject);

void sortLessons(Lesson *lessons, int lessonsQuantity);

char* getLessonTypeName(int type);

char* getFormOfLessonName(int form);

char* getNameOfTypeOfFrequency (int frequency);