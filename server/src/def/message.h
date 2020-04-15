/*
** EPITECH PROJECT, 2020
** server
** File description:
** message.h
*/

#ifndef SERVER_SRC_DEF_MESSAGE_H
#define SERVER_SRC_DEF_MESSAGE_H

static const char* const MESSAGE_SUCCESS = "200 Command success.\n";
static const char* const MESSAGE_HELP = "214 Command list:\n";
static const char* const MESSAGE_HELP_COMMAND = "214 Command:\n";
static const char* const MESSAGE_HELP_END = "\n214 Help end.\n";
static const char* const MESSAGE_WELCOME = "220 Welcome.\n";
static const char* const MESSAGE_QUIT = "221 Goodbye.\n";
static const char* const MESSAGE_PASV = "227 Passive mode (%s).\n";
static const char* const MESSAGE_CONNECTION_OPEN =
    "150 Open data connection.\n";
static const char* const MESSAGE_CONNECTION_CLOSE =
    "226 Close data connection.\n";
static const char* const MESSAGE_LOGIN = "230 Login success.\n";
static const char* const MESSAGE_FILE_OK = "250 File OK.\n";
static const char* const MESSAGE_PWD = "257 \"%s\".\n";
static const char* const MESSAGE_PASSWORD = "331 Login with PASS.\n";
static const char* const MESSAGE_UNKNOWN_MODE = "425 Unknown mode.\n";
static const char* const MESSAGE_ERROR_UNKNOWN = "500 Unknown command.\n";
static const char* const MESSAGE_ERROR_ARGUMENTS = "501 Wrong arguments.\n";
static const char* const MESSAGE_ERROR_LOGIN_USER = "503 Login with USER.\n";
static const char* const MESSAGE_ERROR_LOGIN = "530 Login error.\n";
static const char* const MESSAGE_ERROR_LOGIN_GUEST = "530 Guest.\n";
static const char* const MESSAGE_ERROR_LOGIN_MANDATORY =
    "530 Login with USER and PASS.\n";
static const char* const MESSAGE_ERROR_FILE_UNAVAILABLE =
    "550 Unavailable file.\n";

#endif // SERVER_SRC_DEF_MESSAGE_H
