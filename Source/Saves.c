#pragma once

#include <stdlib.h>
#include <string.h>
#include "../Headers/Saves.h"
#include "../Headers/Auxiliary.h"
#include "../Headers/DateTime.h"

int loadSavingFile(Subject ** subjectsReturn, int *subjectsQuantity, char* default_file_name)
{
/* принимает на вход указатель на указатель на массив и указатель
 * на количество дисциплин. Заполняет массив и записывает
 * количество дисциплин по указанномым адресам.
 * Возвращает 1 в случае ошибок доступа к файлу
 * загрузки и 0, в случае успешного завершения загрузки */
    Subject *subjects;
    FILE *file = fopen(default_file_name, "r");
    if (file == NULL)
        return 1;
    int k, i, c;
    char tmp[200];
    fscanf(file, "%d;", subjectsQuantity);
    fgetc(file);
    subjects = (Subject*)malloc(*subjectsQuantity * sizeof(Subject));

    for (k = 0; k < *subjectsQuantity; k++)
    {
        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].name, tmp);

        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].controlType, tmp);

        fscanf(file, "%d", &(subjects[k].controlDate.day));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].controlDate.month));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].controlDate.year));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].controlDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].lectures.startTime.hour));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.startTime.min));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.endTime.hour));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.endTime.min));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].lectures.startDate.day));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.startDate.month));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.startDate.year));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.startDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].lectures.endDate.day));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.endDate.month));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.endDate.year));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].lectures.endDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].lectures.type));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].lectures.form));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].lectures.frequency));
        fgetc(file);

        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].lectures.location, tmp);

        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].lectures.teacher, tmp);

        fscanf(file,"%d" ,&(subjects[k].practices.startTime.hour));
        fgetc(file);
        fscanf(file,"%d" ,&(subjects[k].practices.startTime.min));
        fgetc(file);
        fscanf(file,"%d" , &(subjects[k].practices.endTime.hour));
        fgetc(file);
        fscanf(file,"%d" , &(subjects[k].practices.endTime.min));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].practices.startDate.day));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].practices.startDate.month));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].practices.startDate.year));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].practices.startDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d",&(subjects[k].practices.endDate.day));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].practices.endDate.month));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].practices.endDate.year));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].practices.endDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].practices.type));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].practices.form));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].practices.frequency));
        fgetc(file);


        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].practices.location, tmp);

        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].practices.teacher, tmp);


        fscanf(file,"%d" ,&(subjects[k].laboratories.startTime.hour));
        fgetc(file);
        fscanf(file,"%d" ,&(subjects[k].laboratories.startTime.min));
        fgetc(file);
        fscanf(file,"%d" , &(subjects[k].laboratories.endTime.hour));
        fgetc(file);
        fscanf(file,"%d" , &(subjects[k].laboratories.endTime.min));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].laboratories.startDate.day));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].laboratories.startDate.month));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].laboratories.startDate.year));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].laboratories.startDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d",&(subjects[k].laboratories.endDate.day));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].laboratories.endDate.month));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].laboratories.endDate.year));
        fgetc(file);
        fscanf(file, "%d",&(subjects[k].laboratories.endDate.dayOfWeek));
        fgetc(file);

        fscanf(file, "%d", &(subjects[k].laboratories.type));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].laboratories.form));
        fgetc(file);
        fscanf(file, "%d", &(subjects[k].laboratories.frequency));
        fgetc(file);

        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].laboratories.location, tmp);

        i = 0;
        do{
            c = getc(file);
            if (c != '\n')
                tmp[i] = c;
            i++;
        } while (c != '\n');
        tmp[i-1] = '\0';
        strcpy(subjects[k].laboratories.teacher, tmp);


        strcpy(subjects[k].laboratories.name, subjects[k].name);
        strcpy(subjects[k].lectures.name, subjects[k].name);
        strcpy(subjects[k].practices.name, subjects[k].name);

    }
    fclose(file);
    *subjectsReturn = subjects;
    return 0;
}

int saving(Subject *subjects, int subjectQuantity, char* file_name)
{
/* принимает массив с дисциплинами и их количество.
 * Сохраняет все данные в файл file_name.
 * Возвращает 1 в случае ошибок доступа к файлу сохранения и 0,
 * в случае успешного завершения сохранения. */
    FILE* savingFile = fopen(file_name,"w");
    if (savingFile == NULL)
    {
        return 1;
    }
    int i;
    fprintf(savingFile, "%d\n", subjectQuantity);

    for (i = 0; i < subjectQuantity; i++)
    {
        fprintf(savingFile,"%s\n", subjects[i].name);
        fprintf(savingFile,"%s\n", subjects[i].controlType);
        fprintf(savingFile,"%d\n%d\n%d\n%d\n",
                subjects[i].controlDate.day,
                subjects[i].controlDate.month,
                subjects[i].controlDate.year,
                subjects[i].controlDate.dayOfWeek);
        fprintf(savingFile,"%d\n%d\n%d\n%d\n",
                subjects[i].lectures.startTime.hour,
                subjects[i].lectures.startTime.min,
                subjects[i].lectures.endTime.hour,
                subjects[i].lectures.endTime.min);
        fprintf(savingFile, "%d\n%d\n%d\n%d\n",
                subjects[i].lectures.startDate.day,
                subjects[i].lectures.startDate.month,
                subjects[i].lectures.startDate.year,
                subjects[i].lectures.startDate.dayOfWeek);
        fprintf(savingFile, "%d\n%d\n%d\n%d\n",
                subjects[i].lectures.endDate.day,
                subjects[i].lectures.endDate.month,
                subjects[i].lectures.endDate.year,
                subjects[i].lectures.endDate.dayOfWeek);
        fprintf(savingFile, "%d\n%d\n%d\n",
                subjects[i].lectures.type,
                subjects[i].lectures.form,
                subjects[i].lectures.frequency);
        fprintf(savingFile, "%s\n%s\n",
                subjects[i].lectures.location,
                subjects[i].lectures.teacher);

        fprintf(savingFile,"%d\n%d\n%d\n%d\n",
                subjects[i].practices.startTime.hour,
                subjects[i].practices.startTime.min,
                subjects[i].practices.endTime.hour,
                subjects[i].practices.endTime.min);
        fprintf(savingFile, "%d\n%d\n%d\n%d\n",
                subjects[i].practices.startDate.day,
                subjects[i].practices.startDate.month,
                subjects[i].practices.startDate.year,
                subjects[i].practices.startDate.dayOfWeek);
        fprintf(savingFile, "%d\n%d\n%d\n%d\n",
                subjects[i].practices.endDate.day,
                subjects[i].practices.endDate.month,
                subjects[i].practices.endDate.year,
                subjects[i].practices.endDate.dayOfWeek);
        fprintf(savingFile, "%d\n%d\n%d\n",
                subjects[i].practices.type,
                subjects[i].practices.form,
                subjects[i].practices.frequency);
        fprintf(savingFile, "%s\n%s\n",
                subjects[i].practices.location,
                subjects[i].practices.teacher);

        fprintf(savingFile,"%d\n%d\n%d\n%d\n",
                subjects[i].laboratories.startTime.hour,
                subjects[i].laboratories.startTime.min,
                subjects[i].laboratories.endTime.hour,
                subjects[i].laboratories.endTime.min);
        fprintf(savingFile, "%d\n%d\n%d\n%d\n",
                subjects[i].laboratories.startDate.day,
                subjects[i].laboratories.startDate.month,
                subjects[i].laboratories.startDate.year,
                subjects[i].laboratories.startDate.dayOfWeek);
        fprintf(savingFile, "%d\n%d\n%d\n%d\n",
                subjects[i].laboratories.endDate.day,
                subjects[i].laboratories.endDate.month,
                subjects[i].laboratories.endDate.year,
                subjects[i].laboratories.endDate.dayOfWeek);
        fprintf(savingFile, "%d\n%d\n%d\n",
                subjects[i].laboratories.type,
                subjects[i].laboratories.form,
                subjects[i].laboratories.frequency);
        fprintf(savingFile, "%s\n%s\n",
                subjects[i].laboratories.location,
                subjects[i].laboratories.teacher);

    }

    fclose(savingFile);
    return 0;
}
