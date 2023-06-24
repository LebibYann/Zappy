/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** convert_tick_to_time
*/

#include "zappy_pending_command.h"

void convert_tick_to_time(struct timespec *timing, int tick, int frequency)
{
    double tick_delay;

    if (frequency <= 0)
        return;
    tick_delay = ((double) tick) * (1 / ((double) frequency));
    timing->tv_sec = tick_delay;
    timing->tv_nsec = (tick_delay - ((double) timing->tv_sec)) * 1e9;
}
