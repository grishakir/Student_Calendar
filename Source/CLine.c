#pragma once

#include "../Headers/CLine.h"
#include <stdio.h>
#include <time.h>

int _NUM_OF_WORK_THINGS = 0;
int _NUM_OF_ERRORS = 0;
int _FULL_DIALOG_TO_LOG_KEY = 0;
int _QUIET_WORK_KEY = 0;
char _LOG_FILE_NAME[40];
FILE* _LOG_FILE;

void print_to_log_file(time_t program_start, time_t program_end, int UserID,
                       int num_of_work_things, int num_of_errors, int exit_code) {

    struct tm *calendar_time = localtime(&program_start);
    char str_time[40] = {0};

    strftime(str_time, 40, "%H:%M:%S:%d:%m:%Y", calendar_time);
    fprintf(_LOG_FILE, "ts:%s\n", str_time);

    fprintf(_LOG_FILE, "idu:%d\n", UserID);

    fprintf(_LOG_FILE, "nw:%d\n", num_of_work_things);

    fprintf(_LOG_FILE, "ne:%d\n", num_of_errors);

    calendar_time = localtime(&program_end);
    strftime(str_time, 40, "%H:%M:%S:%d:%m:%Y", calendar_time);
    fprintf(_LOG_FILE, "te:%s\n", str_time);

    fprintf(_LOG_FILE, "ec:%d\n", exit_code);
    fclose(_LOG_FILE);
}




void print_command_line_info() {
    printf("-c - launch with the specified configuration file.\n");
    printf("-d - record dialog to .log file.\n");
    printf( "-f - use special saving file\n");
    printf("-h - command line arguments help\n");
    printf("-i - print author and control info\n");
    printf("-m - interactive mod ON\n");
    printf("-o - use new name of saving file\n");
    printf("-s - silent mode\n");
    printf("-t - don't delete temp files\n");
}
