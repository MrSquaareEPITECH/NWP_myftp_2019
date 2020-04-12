/*
** EPITECH PROJECT, 2020
** server
** File description:
** message.h
*/

#ifndef SERVER_SRC_UTIL_MESSAGE_H
#define SERVER_SRC_UTIL_MESSAGE_H

static const char * const MESSAGE_SUCCESS = "200 Success.";
static const char * const MESSAGE_WELCOME = "220 Welcome.";
static const char * const MESSAGE_QUIT = "221 Goodbye.";
static const char * const MESSAGE_PASV = "227 Passive (%s).";
static const char * const MESSAGE_STOR_OPEN = "150 Open data connection.";
static const char * const MESSAGE_STOR_CLOSE = "226 Close data connection.";
static const char * const MESSAGE_RETR_OPEN = "226 Close data connection.";
static const char * const MESSAGE_RETR_CLOSE = "226 Close data connection.";

#endif // SERVER_SRC_UTIL_MESSAGE_H
