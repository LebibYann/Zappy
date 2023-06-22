/*
** EPITECH PROJECT, 2023
** server
** File description:
** clock_start
*/

#include "clock.h"

void clock_start(struct timespec *timing)
{
    clock_gettime(CLOCK_REALTIME, timing);
}
