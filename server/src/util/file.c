/*
** EPITECH PROJECT, 2020
** server
** File description:
** file.c
*/

#include "file.h"

#include <sys/stat.h>

bool dir_exists(const char *path)
{
    struct stat file_s;

    if (stat(path, &file_s))
        return (false);
    if (!S_ISDIR(file_s.st_mode))
        return (false);
    return (true);
}

bool file_exists(const char *path)
{
    struct stat file_s;

    if (stat(path, &file_s))
        return (false);
    if (!S_ISREG(file_s.st_mode))
        return (false);
    return (true);
}