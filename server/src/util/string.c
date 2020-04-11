/*
** EPITECH PROJECT, 2020
** server
** File description:
** string.c
*/

#include "string.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

char *string_trim(const char *str)
{
    size_t size = strlen(str);
    size_t from = 0;
    int to = size - 1;

    for (size_t len = strlen(str); (isspace(str[from])) && (from < len);
         ++from, --size)
        ;
    for (; (isspace(str[to])) && (to >= 0); --to, --size)
        ;

    char *trim = malloc(sizeof(char) * (size + 1));

    if (trim == NULL)
        return (NULL);

    for (size_t i = 0, j = from; i < size; ++i, ++j)
        trim[i] = str[j];

    trim[size] = '\0';

    return trim;
}

char *string_unique(const char *str)
{
    size_t size = strlen(str);

    for (size_t i = 0, len = strlen(str); i < len; ++i)
        if (isspace(str[i]) && isspace(str[i + 1]))
            size -= 1;

    char *unique = malloc(sizeof(char) * (size + 1));

    if (unique == NULL)
        return (NULL);

    for (size_t i = 0, j = 1; i < size; ++i, ++j) {
        while (isspace(str[j]) && isspace(str[j + 1]))
            j += 1;
        unique[i] = str[j];
    }

    unique[size] = '\0';

    return unique;
}