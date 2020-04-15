/*
** EPITECH PROJECT, 2020
** server
** File description:
** file.h
*/

#ifndef SERVER_SRC_UTIL_FILE_H
#define SERVER_SRC_UTIL_FILE_H

#include <stdbool.h>

bool dir_exists(const char *path);
bool file_exists(const char *path);
char *path(const char *format, ...);

#endif // SERVER_SRC_UTIL_FILE_H
