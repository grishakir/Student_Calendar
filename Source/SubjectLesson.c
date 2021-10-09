#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Headers/SubjectLesson.h"
#include "../Headers/Auxiliary.h"

Subject createSubject()
{
/* создает дисциплину, запрашивает все данные
 * по ней у пользователя.Возвращает полученную
 * структуру */
    Subject subject;
    char subjectName[70];
    char subjectControlType[70];
    Date subjectControlDate;
    Lesson subjectLectures, subjectPractices, subjectLaboratories;
    printf("Enter subject name: ");
    gets(subjectName);

    strcpy(subjectControlType, setControlType());
    subjectControlDate = setDate("control");
    subjectLectures = setLesson(1, subjectName);
    subjectPractices = setLesson(2, subjectName);
    subjectLaboratories = setLesson(3, subjectName);

    strcpy(subject.name, subjectName);
    strcpy(subject.controlType, subjectControlType);
    subject.controlDate = subjectControlDate;
    subject.lectures = subjectLectures;
    subject.practices = subjectPractices;
    subject.laboratories = subjectLaboratories;

    return subject;

}

char* setControlType()
{
/* запрашивает тип контроля  у пользователя
 * и возвращает его навание в виде строки */
    char controlType[30], tmp[20];
    while (1)
    {
        printf("Type of control:\n");
        printf("1 - credit\n");
        printf("2 - credit with an assessment\n");
        printf("3 - rating\n");
        printf("4 - exam\n");
        gets(tmp);

        if (strlen(tmp) == 1 &&
        isdigit(tmp[0]) && (tmp[0] - '0') >= 1
        && (tmp[0] - '0') <= 4)
        {
            switch (tmp[0]) {
                case '1':
                    return "credit";
                case '2':
                    return "credit with assessment";
                case '3':
                    return "rating";
                case '4':
                    return "exam";
            }
        }

        printIncorrectInput();
    }
}

Lesson setLesson(int lessonType, char lessonName[70])
{
/*  принимает название дисциплины и тип занятия.
 * Создает структуру Lesson и запрашивает у пользователя данные по ней.
 * Возвращает занятие с установленными данными */
    Lesson lesson;
    Time lessonStartTime, lessonEndTime;
    char lessonLocation[70], lessonTeacher[70];
    int lessonForm, lessonExistence, lessonFrequency;
    Date lessonStartDate, lessonEndDate;

    switch (lessonType)
    {
        case 1:
            printf("Information about Lectures:\n");
            break;
        case 2:
            printf("Information about Practices:\n");
            break;
        case 3:
            printf("Information about Laboratories:\n");
            break;
        default:
            break;
    }

    printf("Have you got this type of lesson in this subject?\n");
    lessonExistence = yesOrNo();

    if (lessonExistence)
    {
        lessonStartDate = setDate("start lesson");
        lessonEndDate = setDate("end lesson");
        lessonStartTime = setTime("start lesson");
        lessonEndTime = setTime("end lesson");
        lessonForm = setLessonForm();
        lessonFrequency = setLessonFrequency();
        printf("Enter location of the lesson"
               " (teacher's e-mail for distant lessons)\n");
        gets(lessonLocation);

        printf("Enter teacher's name\n");
        gets(lessonTeacher);

        strcpy(lesson.name, lessonName);
        lesson.startTime = lessonStartTime;
        lesson.endTime = lessonEndTime;
        lesson.frequency = lessonFrequency;
        lesson.form = lessonForm;
        lesson.type = lessonType;
        lesson.startDate = lessonStartDate;
        lesson.endDate = lessonEndDate;
        strcpy(lesson.location, lessonLocation);
        strcpy(lesson.teacher, lessonTeacher);
        return lesson;
    }

    lessonStartDate.day = 0;
    lessonStartDate.month = 0;
    lessonStartDate.year = 0;
    lessonStartDate.dayOfWeek = 0;
    lessonEndDate.day = 0;
    lessonEndDate.month = 0;
    lessonEndDate.year = 0;
    lessonEndDate.dayOfWeek = 0;
    lessonStartTime.hour = 0;
    lessonStartTime.min = 0;
    lessonEndTime.hour = 0;
    lessonEndTime.min = 0;

    lesson.startDate = lessonStartDate;
    lesson.endDate = lessonEndDate;
    lesson.startTime = lessonStartTime;
    lesson.endTime = lessonEndTime;
    lesson.frequency = 0;
    lesson.form = 0;
    lesson.type = lessonType;
    strcpy(lesson.name, lessonName);
    strcpy(lesson.location, "0");
    strcpy(lesson.teacher, "0");
    return lesson;
}

int setLessonForm()
{
/* запрашивает у пользователя форму
 * проведения урока и возвращает номер формы */
    char tmp[20];
    int lessonForm;
    while (1)
    {
        printf("Choose form of lesson:\n");
        printf("1. Face-to-face\n");
        printf("2. Distant\n");
        gets(tmp);

        if (strlen(tmp) == 1 && (tmp[0] == '1' || tmp[0] == '2'))
        {
            lessonForm = fromCharToInt(tmp[0]);
            return lessonForm;
        }

        printIncorrectInput();
    }
}

int setLessonFrequency()
{
/* запрашивает у пользователя частоту
 * проведения занятия и возвращает номер частоты; */
    char tmp[20];
    while (1)
    {
        printf("Choose frequency of the lesson:\n");
        printf("1. Even week\n");
        printf("2. Odd week\n");
        printf("3. Every week\n");
        gets(tmp);

        if (strlen(tmp) == 1 &&
        fromCharToInt(tmp[0]) >= 1
        && fromCharToInt(tmp[0]) <= 3)
        {
            return fromCharToInt(tmp[0] - 1);
        }

        printIncorrectInput();
    }
}

void sortLessons(Lesson *lessons, int lessonsQuantity)
{
/* принимает на вход массив с уроками и
 * сортирует их по возрастанию времени начала */
    int i, j;
    Lesson tmpLesson;

    for (i = 1; i < lessonsQuantity; i++)
    {
        for (j = 0; j < lessonsQuantity - 1; j++)
        {
            if (timeMore(lessons[j].startTime,
                         lessons[j+1].startTime))
            {
                tmpLesson = lessons[j];
                lessons[j] = lessons[j+1];
                lessons[j+1] = tmpLesson;
            }
        }
    }
}

char* getLessonTypeName(int type)
{
/* принимает номер типа занятия. Возвращает строку с названием типа */
    switch (type) {
        case 1:
            return "Lecture";
        case 2:
            return "Practice";
        case 3:
            return "Laboratory";
        default:
            return NULL;
    }
}

char* getFormOfLessonName(int form)
{
/* принимает номер формы проведения занятия.
 * Возвращает строку с названием */
    switch (form) {
        case 1:
            return "Person";
        case 2:
            return "Distant";
        default:
            return NULL;
    }
}

void printLesson(Lesson lesson)
{
/* принимает урок и печатает по нему данные */
    printf("%s(%s) (%s)\n",
           lesson.name,
           getLessonTypeName(lesson.type),
           getNameOfTypeOfFrequency(lesson.frequency));
    printf("%d.%d - %d.%d (%s) %s\n",
           lesson.startTime.hour,
           lesson.startTime.min,
           lesson.endTime.hour,
           lesson.endTime.min,
           getFormOfLessonName(lesson.form),
           lesson.location);
    printf("%s\n", lesson.teacher);
}

void editSubject(Subject *subject)
{
/* принимает указатель на дисциплину. Изменяет ее.  */
    int j = 1, menuItem;
    char tmp[10], longTmp[40];
    while (1) {
        j = 1;
        printf("For edit enter number of item\n");
        printf("%d. Name: %s\n", j,
               (*subject).name);
        j++;
        printf("%d. Control type: %s\n", j,
               (*subject).controlType);
        j++;
        printf("%d. Control date: %d/%d/%d\n", j,
               (*subject).controlDate.day,
               (*subject).controlDate.month,
               (*subject).controlDate.year);
        j++;
        printf("%d. ", j);

        if ((*subject).lectures.form != 0) {
            printLesson((*subject).lectures);
        } else {
            printf("Lectures doesn't set\n");
        }

        j++;
        printf("%d. ", j);

        if ((*subject).practices.form != 0) {
            printLesson((*subject).practices);
        } else {
            printf("Practices doesn't set\n");
        }

        j++;
        printf("%d. ", j);

        if ((*subject).laboratories.form != 0) {
            printLesson((*subject).practices);
        } else {
            printf("Laboratories doesn't set\n");
        }

        j++;
        printf("%d. Exit", j);

        gets(tmp);

        if (isNum(tmp) && (isNum(tmp) >= 1 && isNum(tmp) <= j))
        {
            menuItem = isNum(tmp);
            if (menuItem == 1)
            {
                printf("Enter new subject name:\n");
                gets(longTmp);
                strcpy((*subject).name, longTmp);
            }
            else if (menuItem == 2)
            {
                strcpy((*subject).controlType, setControlType());
            }
            else if (menuItem == 3)
            {
                (*subject).controlDate = setDate("control");
            }
            else if (menuItem == 4)
            {
                (*subject).lectures = setLesson(1, (*subject).name);
            }
            else if (menuItem == 5)
            {
                (*subject).practices = setLesson(2, (*subject).name);
            }
            else if (menuItem == 6)
            {
                (*subject).laboratories = setLesson(3, (*subject).name);
            }
            else if (menuItem == 7)
            {
                return;
            }
        }
        else
        {
            system("cls");
            printIncorrectInput();
            continue;
        }

        return;
    }
}

char* getNameOfTypeOfFrequency (int frequency)
{
/* принимает номер частоты занятия
 * . Возвращает строку с названием */
    if (frequency == 0)
        return "Even week";

    if (frequency == 1)
        return "Odd week";

    return "Every week";

}