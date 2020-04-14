/*
** EPITECH PROJECT, 2020
** server
** File description:
** args.h
*/

#ifndef SERVER_SRC_UTIL_ARGS_H
#define SERVER_SRC_UTIL_ARGS_H

char **args_create(const char *str, const char *delim);
int args_count(char **args);
void args_delete(char **args);

#endif // SERVER_SRC_UTIL_ARGS_H
