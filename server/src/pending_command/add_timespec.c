/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** add_timespec
*/

#include "zappy_pending_command.h"

void add_timespec(struct timespec *dest, const struct timespec *src)
{
    dest->tv_sec += src->tv_sec;
    dest->tv_nsec += src->tv_nsec;
    while (dest->tv_nsec > 1e9) {
        ++(dest->tv_sec);
        dest->tv_nsec -= 1e9;
    }
}
