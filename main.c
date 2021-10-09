#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Headers/DateTime.h"
#include "Headers/SubjectLesson.h"
#include "Headers/Auxiliary.h"
#include "Headers/Saves.h"
#include "Headers/CLine.h"

#pragma once
FILE* _LOG_FILE;

void printSubjects(Subject *subjects, int subjectsQuantity);

void printScheduleOnDay(Subject *subjects, int subjectsQuantity, Date date);

void scheduleMenu();

int settingMenu(Subject **subjects, int *subjectsQuantity);

void printScheduleOnWeek(int numOfWeek, Subject *subjects,
                         int subjectsQuantity);

int main(int argc, char* argv[]) {
    /* Главное меню*/
    char default_file_name[70] = "saving.dat";
    char default_file_saving[70] = "saving.dat";
    const time_t start_program = time(NULL);
    struct tm *calendar_time = localtime(&start_program);
    strftime(_LOG_FILE_NAME, 40, "%Ha%Ma%Sa%da%ma%Y.log", calendar_time);

    if (argc > 1) {
        if (!strcmp(argv[1], "-c"))
        {
            if (argc > 3)
            {
                printIncorrectInput();
            }
            printf("%s - configure file name\n", argv[2]);
        }
        else if (!strcmp(argv[1], "-d"))
        {
            if (argc > 2)
            {
                printIncorrectInput();
            }
            else
            {
                _FULL_DIALOG_TO_LOG_KEY = 1;
            }
        }
        else if (!strcmp(argv[1], "-f"))
        {
            if (argc > 3)
            {
                printIncorrectInput();
            }
            else
            {
                strcpy(default_file_name, argv[2]);
            }
        }
        else if (!strcmp(argv[1], "-h"))
        {
            if (argc > 2)
            {
                printIncorrectInput();
            }
            else
            {
                print_command_line_info();
            }
        }
        else if (!strcmp(argv[1], "-i"))
        {
            if (argc > 2)
            {
                printIncorrectInput();
            }
            else
            {
                printf("Kirsanov Grigorii Romanovich, M8O-110B-20\n");
                printf("Kartashov Eduard Mikhailovich, 813 department, MAI\n");
            }
        }
        else if (!strcmp(argv[1], "-m"))
        {
            if (argc > 2)
            {
                printIncorrectInput();
            }
            else
            {
                printf("Interactive nod ON\n");
            }
        }
        else if (!strcmp(argv[1], "-o"))
        {
            if (argc > 3)
            {
                printIncorrectInput();
            }
            else
            {
                strcpy(default_file_saving, argv[2]);
            }
        }
        else if (!strcmp(argv[1], "-s"))
        {
            if (argc > 2)
            {
                printIncorrectInput();
            }
            else
            {
                _QUIET_WORK_KEY = 1;
            }
        }
        else if (!strcmp(argv[1], "-t"))
        {
            if (argc > 2)
            {
                printIncorrectInput();
            }
        }
        else
            printIncorrectInput();
    }

    int subjectsQuantity = 0, flagNormalExit = 1;

    Subject *subjects = (Subject*)malloc(2 * sizeof(Subject));
    FILE* savingFile = fopen(default_file_name,"w");
    FILE* log = fopen(_LOG_FILE_NAME,"w");
    _LOG_FILE = log;

    int isUseSavingFile = 0;
    char input[20];

    if (savingFile != NULL)
    {
        printf("Save file detected!\n");
        printf("Do you want to use it?\n");
        isUseSavingFile = yesOrNo();
        fclose(savingFile);

        if (isUseSavingFile)
        {
            if (loadSavingFile(&subjects,&subjectsQuantity, default_file_name))
            {
                printf("Loading Error\n");
            }
        }
    }

    if (subjectsQuantity == 0)
    {
        subjects[0] = createSubject();
        subjectsQuantity++;
        system("cls");
    }

    while (1)
    {
        printf("Main menu:\n");
        printf("Enter the item of menu\n");
        printf("1. Subjects\n");
        printf("2. Schedule\n");
        printf("3. Settings\n");
        printf("E for exit\n");
        gets(input);
        if (strlen(input) == 1 && (input[0] >= '1' &&
            input[0] <= '3' || input[0] == 'E'))
        {
            switch (input[0])
            {
                case '1':
                    system("cls");
                    printSubjects(subjects, subjectsQuantity);
                    printf("For return to menu enter something:");
                    gets(input);
                    system("cls");
                    continue;
                case '2':
                    scheduleMenu(subjects, subjectsQuantity);
                    system("cls");
                    continue;
                case '3':
                    if (settingMenu(&subjects, &subjectsQuantity))
                    {
                        remove("saving.dat");
                        free(subjects);
                        flagNormalExit = 0;
                        input[0] = 'E';
                        break;
                    }
                    system("cls");
                    continue;
            }
            if (input[0] == 'E') {
                break;
            }
        }
        system("cls");
        printIncorrectInput();
    }
    if (flagNormalExit) {
        if (saving(subjects, subjectsQuantity, default_file_saving)) {
            system("cls");
            printf("Saving Error. Exit without saving...");
        }
    }
    if (!_QUIET_WORK_KEY)
    {
        _NUM_OF_WORK_THINGS = subjectsQuantity;
        const time_t end_program = time(NULL);
        //int UserID = getuid();
        print_to_log_file(start_program, end_program, 0, _NUM_OF_WORK_THINGS, _NUM_OF_ERRORS, 0);
    }
    free(subjects);
    return 0;
}

void printScheduleOnDay(Subject *subjects, int subjectsQuantity, Date date)
{
/* Принимает на вход массив с дисциплинами,
 * их количество и дату, на которую требуется вывести расписание.
 * Создает расписание на заданную дату,
 * сортирует занятия по времени начала и выводит их на экран. */
    int typeOfWeek = (getNumOfWeek(date)) % 2;
    int i;
    int lessonsQuantity = 0;
    Lesson *lessonsOnThisDay = (Lesson*)malloc(sizeof(Lesson));
    printf("%d/%d/%d %s\n", date.day, date.month, date.year,
           getDayOfWeekName(date.dayOfWeek));
    for (i = 0; i < subjectsQuantity; i++)
    {
        if (dateLessEq(date, subjects[i].lectures.endDate)
        && dateLessEq(subjects[i].lectures.startDate, date)
            && (subjects[i].lectures.frequency == 2 ||
            subjects[i].lectures.frequency  == typeOfWeek)
            && subjects[i].lectures.startDate.dayOfWeek == date.dayOfWeek)
        {
            lessonsQuantity++;
            lessonsOnThisDay = (Lesson *)realloc(
                    lessonsOnThisDay, lessonsQuantity*sizeof(Lesson));
            lessonsOnThisDay[lessonsQuantity-1] = subjects[i].lectures;
        }

        if (dateLessEq(date, subjects[i].practices.endDate)
        && dateLessEq(subjects[i].practices.startDate, date)
            && (subjects[i].practices.frequency == 2
            || subjects[i].practices.frequency  == typeOfWeek)
            && subjects[i].practices.startDate.dayOfWeek == date.dayOfWeek)
        {
            lessonsQuantity++;
            lessonsOnThisDay = (Lesson*)realloc(
                    lessonsOnThisDay, lessonsQuantity*sizeof(Lesson));
            lessonsOnThisDay[lessonsQuantity-1] = subjects[i].practices;
        }

        if (dateLessEq(date, subjects[i].laboratories.endDate)
        && dateLessEq(subjects[i].laboratories.startDate, date)
            && (subjects[i].laboratories.frequency == 2
            || subjects[i].laboratories.frequency  == typeOfWeek)
            && subjects[i].laboratories.startDate.dayOfWeek ==
                            date.dayOfWeek)
        {
            lessonsQuantity++;
            lessonsOnThisDay = (Lesson*)realloc(
                    lessonsOnThisDay, lessonsQuantity*sizeof(Lesson));
            lessonsOnThisDay[lessonsQuantity-1] = subjects[i].laboratories;
        }
    }

    sortLessons(lessonsOnThisDay, lessonsQuantity);

    for (i = 0; i < lessonsQuantity; i++)
    {
        printf("==================================\n");
        printLesson(lessonsOnThisDay[i]);
        printf("==================================\n");
    }
}

void printSubjects(Subject *subjects, int subjectsQuantity) {
/* принимает на вход массив дисциплин и их количество.
 * Если количество дисциплин > 0, то выводит их названия,
 * иначе выводит сообщение, что дисциплины не обнаружены.*/
    int i;
    if (subjectsQuantity != 0)
    {
        for (i = 0; i < subjectsQuantity; i++)
        {
            printf("%d. %s\n", i + 1, subjects[i].name);
        }
    } else printf("There is no subjects\n");
}

int settingMenu(Subject **subjects, int *subjectsQuantity)
{
/*меню настроек. Принимает указатель на массив с дисциплинами
 * и указатель на их количиство.
 * Вызывает функции связанные с изменением этих данных.*/
    char tmp[200];
    int numTmp;
    system("cls");
    while (1)
    {
        printf("Settings menu:\n");
        printf("Enter the item of menu\n");
        printf("1. Add new subject\n");
        printf("2. Edit subject/lesson\n");
        printf("3. Delete subject\n");
        printf("4. Delete all information\n");
        printf("E for return to main menu\n");
        gets(tmp);
        if (strlen(tmp) == 1 && (tmp[0] == '1' ||tmp[0] == '2'
        || tmp[0] == '3' || tmp[0] == 'E' || tmp[0] == '4'))
        {
            system("cls");
            switch (tmp[0])
            {
                case '1':
                    (*subjectsQuantity)++;
                    *subjects = (Subject*)realloc(
                            *subjects, sizeof(Subject) * *subjectsQuantity);
                    (*subjects)[*subjectsQuantity - 1] = createSubject();
                    return 0;
                case '2':
                    while (1)
                    {
                        if (*subjectsQuantity == 0)
                        {
                            printf("There is no subjects\n");
                            break;
                        }
                        printSubjects(*subjects, *subjectsQuantity);
                        printf("Enter number of subject for edit:");

                        gets(tmp);
                        numTmp = atoi(tmp);

                        if (isNum(tmp) &&
                        (numTmp <= *subjectsQuantity && numTmp >= 1)){
                            editSubject(&(*subjects)[numTmp - 1]);
                            return 0;
                        }
                        else {
                            system("cls");
                            printIncorrectInput();
                        }
                    }

                case '3':
                    while (1)
                    {
                        printSubjects(*subjects, *subjectsQuantity);
                        printf("Enter number of subject for delete:\n");
                        gets(tmp);
                        if (isNum(tmp) &&
                        isNum(tmp) <= *subjectsQuantity && isNum(tmp)  >= 1)
                        {
                            numTmp = atoi(tmp);
                            printf("Are you really want to delete %s?\n",
                                   (*subjects[numTmp - 1]).name);
                            if (yesOrNo())
                            {
                                for (int i = (numTmp - 1);
                                i < *subjectsQuantity - 1; i ++)
                                    (*subjects)[i] = (*subjects)[i + 1];
                                *subjects = realloc(*subjects,
                                                    (--*subjectsQuantity) *
                                                    sizeof(Subject));
                                if (!(*subjectsQuantity))
                                {
                                    *subjects[*subjectsQuantity] =
                                            createSubject();
                                    (*subjectsQuantity) =
                                            (*subjectsQuantity) + 1;
                                }
                                return 0;
                            }
                            else
                                return 0;
                        }
                        else
                            {
                            system("cls");
                            printIncorrectInput();
                            continue;
                            }
                    }
                    return 0;
                case '4':
                    return 1;
                case 'E':
                    return 0;
            }
        }
        system("cls");
        printIncorrectInput();
    }
}

void scheduleMenu(Subject *subjects, int subjectsQuantity)
{
/* меню вывода расписания.
 * Принимает на вход массив дисциплин и их количество.
 * Вызывает функции связанные с печатью расписания*/
    char tmp[20];
    system("cls");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date today, date;
    today.day = tm.tm_mday;
    today.month = tm.tm_mon + 1;
    today.year = tm.tm_year + 1900;
    today.dayOfWeek = getDayOfWeek(today.day, today.month, today.year);

    while (1) {
        printf("Schedule menu:\n");
        printf("Enter the item of menu\n");
        printf("1. Today\n");
        printf("2. This week\n");
        printf("3. Last week\n");
        printf("4. Next week\n");
        printf("5. Certain day\n");
        printf("6. Certain week\n");
        printf("7. Session\n");
        printf("8. By subject\n");
        printf("E for return to main menu\n");
        gets(tmp);

        if (strlen(tmp) == 1 && (fromCharToInt(tmp[0]) >= 1
        && fromCharToInt(tmp[0]) <= 8 || tmp[0] == 'E'))
        {
            switch (tmp[0])
            {
                case '1':
                    system("cls");
                    printScheduleOnDay(subjects, subjectsQuantity, today);
                    printf("For exit enter something");
                    getchar();
                    continue;
                case '2':
                    system("cls");
                    printScheduleOnWeek(getNumOfWeek(today),
                                        subjects, subjectsQuantity);
                    printf("For exit enter something");
                    getchar();
                    system("cls");
                    continue;
                case '3':
                    system("cls");
                    printScheduleOnWeek(
                            getNumOfWeek(today) - 1, subjects,
                            subjectsQuantity);
                    printf("For exit enter something");
                    getchar();
                    system("cls");
                    continue;
                case '4':
                    system("cls");
                    printScheduleOnWeek(
                            getNumOfWeek(today) + 1,
                            subjects, subjectsQuantity);
                    printf("For exit enter something");
                    getchar();
                    system("cls");
                    continue;
                case '5':
                    system("cls");
                    date = setDate("");
                    system("cls");
                    printScheduleOnDay(subjects,
                                       subjectsQuantity, date);
                    printf("For exit enter something");
                    getchar();
                    system("cls");
                    continue;
                case '6':
                    system("cls");
                    printf("Enter num of week (1..50)\n");

                    while (1)
                    {
                        gets(tmp);
                        if (isNum(tmp) &&
                        atoi(tmp) >= 1 && atoi(tmp) <= 50)
                        {
                            break;
                        }
                        else
                            printIncorrectInput();
                    }

                    system("cls");
                    printScheduleOnWeek(atoi(tmp),
                                        subjects, subjectsQuantity);
                    printf("For exit enter something");
                    getchar();
                    system("cls");
                    continue;
                case '7':
                    system("cls");
                    printf("Session info\n");
                    for (int i = 0; i < subjectsQuantity; i++) {
                        printf("%d. %s (%s)\n",
                               i + 1, subjects[i].name,
                               subjects[i].controlType);
                        printf("%d/%d/%d %s\n",
                               subjects[i].controlDate.day,
                               subjects[i].controlDate.month,
                               subjects[i].controlDate.year,
                               getDayOfWeekName(
                                       subjects[i].controlDate
                                       .dayOfWeek));
                    }
                    printf("For exit enter something");
                    getchar();

                    system("cls");
                    continue;
                case '8':
                    while (1)
                    {
                        printSubjects(subjects, subjectsQuantity);
                        printf("Enter number of subject for print info:");

                        gets(tmp);
                        int numTmp = atoi(tmp);

                        if (isNum(tmp) &&
                        (numTmp <= subjectsQuantity
                        && numTmp >= 1)) {
                            system("cls");
                            numTmp--;
                            printf("%s (%s)\n",
                                   subjects[numTmp].name,
                                   subjects[numTmp].controlType);
                            printf("%d/%d/%d %s\n",
                                   subjects[numTmp].controlDate.day,
                                   subjects[numTmp].controlDate.month,
                                   subjects[numTmp].controlDate.year,
                                   getDayOfWeekName(subjects[numTmp].
                                   controlDate.dayOfWeek));

                            if (subjects[numTmp].lectures.form != 0) {
                                printLesson(subjects[numTmp].lectures);
                            }

                            if (subjects[numTmp].practices.form != 0) {
                                printLesson(subjects[numTmp].practices);
                            }

                            if (subjects[numTmp].laboratories.form != 0) {
                                printLesson(subjects[numTmp].laboratories);
                            }
                        }
                        else
                        {
                            system("cls");
                            printIncorrectInput();
                        }

                        printf("For exit enter something");
                        getchar();
                        system("cls");
                        break;
                    }
                    continue;
                case 'E':
                    return;

            }
        }
        else
        {
            system("cls");
            printIncorrectInput();
            continue;
        }
    }
}

void printScheduleOnWeek(int numOfWeek,
                         Subject *subjects,
                         int subjectsQuantity)
{
/*принимает значение номера недели по учебному плану, для текущего учебного,
 * массив дисциплин и их количество. Печатает расписание на неделю*/
    Date firstDayOfWeek, lastDayOfWeek;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("=============================\n");
    printf("            %-2d WEEK\n", numOfWeek);
    printf("=============================\n");

    firstDayOfWeek.day = 1;
    firstDayOfWeek.month = 9;
    firstDayOfWeek.year = (tm.tm_year -
            (tm.tm_mon < 9 ? 1 : 0)) + 1900;

    while (getNumOfWeek(firstDayOfWeek) != numOfWeek)
    {
        shiftDateDown(&firstDayOfWeek);
    }

    lastDayOfWeek = firstDayOfWeek;

    while (getNumOfWeek(lastDayOfWeek) == numOfWeek)
    {
        shiftDateDown(&lastDayOfWeek);
    }

    while (firstDayOfWeek.day != lastDayOfWeek.day
    || firstDayOfWeek.month != lastDayOfWeek.month
    || firstDayOfWeek.year != lastDayOfWeek.year)
    {
        printScheduleOnDay(subjects, subjectsQuantity,
                           firstDayOfWeek);
        shiftDateDown(&firstDayOfWeek);
    }
}