#pragma once
#include <stdio.h>
#include "SubjectLesson.h"

int loadSavingFile(Subject ** subjectsReturn, int *subjectsQuantity, char* file_name);

int saving(Subject *subjects, int subjectQuantity, char* file_name);