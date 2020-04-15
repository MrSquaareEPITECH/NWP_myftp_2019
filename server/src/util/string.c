/*
** EPITECH PROJECT, 2020
** server
** File description:
** string.c
*/

#include "string.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_brk(char *str)
{
    char *find = strstr(str, "\r\n");

    if (!find)
        find = strstr(str, "\n");
    if (find)
        *find = '\0';
    return (find);
}

int string_count(const char *str, char c)
{
    int count = 0;

    for (size_t i = 0, len = strlen(str); i < len;
        ++i, count += (str[i] == c)) ;
    return (count);
}

char *string_format(const char *format, ...)
{
    va_list variadic;

    va_start(variadic, format);

    int len = vsnprintf(NULL, 0, format, variadic);
    char *message = malloc(sizeof(char) * (len + 1));

    va_end(variadic);
    va_start(variadic, format);
    memset(message, 0, sizeof(char) * (len + 1));
    vsprintf(message, format, variadic);
    va_end(variadic);
    return message;
}

char *string_find_r(char *str, char c)
{
    for (int i = strlen(str) - 1; i >= 0; --i)
        if (str[i] == c)
            return (&str[i]);
    return (str);
}