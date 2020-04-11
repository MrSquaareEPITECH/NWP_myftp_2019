/*
** EPITECH PROJECT, 2020
** server
** File description:
** string.c
*/

#include "string.h"

#include <stdlib.h>
#include <string.h>

char *string_crlf(const char *str)
{
    char *find = strstr(str, "\r\n");

    if (find)
        *find = '\0';

    return (find);
}

char **string_split(const char *str, const char *delim)
{
    char *dup = strdup(str);
    size_t size = 0;

    for (const char *token = strtok(dup, delim); token;
         ++size, token = strtok(NULL, delim))
        ;

    free(dup);

    char **array = malloc(sizeof(char *) * (size + 1));

    if (array == NULL)
        return NULL;

    dup = strdup(str);

    if (dup == NULL)
        return NULL;

    size_t i = 0;

    for (const char *token = strtok(dup, delim); i < size;
         ++i, token = strtok(NULL, delim)) {
        array[i] = strdup(token);
    }

    array[size] = NULL;

    free(dup);

    return array;
}
