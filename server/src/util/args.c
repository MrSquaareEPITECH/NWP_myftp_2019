/*
** EPITECH PROJECT, 2020
** server
** File description:
** args.c
*/

#include "args.h"

#include <stdlib.h>
#include <string.h>

static size_t args_create_size(const char *str, const char *delim)
{
    size_t size = 0;
    char *dup = strdup(str);

    for (const char *token = strtok(dup, delim); token;
        ++size, token = strtok(NULL, delim)) ;
    free(dup);
    return (size);
}

char **args_create(const char *str, const char *delim)
{
    size_t size = args_create_size(str, delim);
    char **array = malloc(sizeof(char *) * (size + 1));

    if (array == NULL)
        return NULL;

    char *dup = strdup(str);
    size_t i = 0;

    for (const char *token = strtok(dup, delim); i < size;
        ++i, token = strtok(NULL, delim))
        array[i] = strdup(token);

    array[size] = NULL;
    free(dup);
    return array;
}

int args_count(char **args)
{
    size_t size = 0;

    for (; args[size]; ++size) ;
    return (size);
}

void args_delete(char **args)
{
    for (size_t i = 0; args[i]; ++i)
        free(args[i]);
    free(args);
}