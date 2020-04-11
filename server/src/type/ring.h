/*
** EPITECH PROJECT, 2020
** server
** File description:
** ring.h
*/

#include <stddef.h>
#include <stdint.h>

#ifndef SERVER_SRC_TYPE_RING_H
#define SERVER_SRC_TYPE_RING_H

#include "def/size.h"

typedef struct ring_s ring_t;

struct ring_s {
    char buffer[SIZE_RING];
    uint8_t index_r;
    uint8_t index_w;
};

#endif // SERVER_SRC_TYPE_RING_H
