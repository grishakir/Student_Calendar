cmake_minimum_required(VERSION 3.17)
project(StudentSchedule C)

set(CMAKE_C_STANDARD 99)

add_executable(StudentSchedule main.c Source/SubjectLesson.c Headers/SubjectLesson.h Source/DateTime.c Headers/DateTime.h Source/Auxiliary.c Headers/Auxiliary.h Source/Saves.c Headers/Saves.h Source/CLine.c Headers/CLine.h)