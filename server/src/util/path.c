/*
** EPITECH PROJECT, 2020
** server
** File description:
** file.c
*/

#include "path.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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

char *path_real(const char *relative)
{
    char current[PATH_MAX];

    memset(current, 0, PATH_MAX);
    getcwd(current, PATH_MAX);
    chdir(relative);

    char *real = malloc(sizeof(char) * PATH_MAX);

    memset(real, 0, PATH_MAX);
    getcwd(real, PATH_MAX);
    chdir(current);

    return (real);
}