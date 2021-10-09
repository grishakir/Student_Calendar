#pragma once
#include <time.h>
#include <stdio.h>
void print_command_line_info();
void print_to_log_file(time_t program_start, time_t program_end, int UserID,
                       int num_of_work_things, int num_of_errors, int exit_code);

extern int _NUM_OF_WORK_THINGS;
extern int _NUM_OF_ERRORS;
extern int _FULL_DIALOG_TO_LOG_KEY;
extern int _QUIET_WORK_KEY;
extern char _LOG_FILE_NAME[40];
extern FILE* _LOG_FILE;
