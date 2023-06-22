/*
** EPITECH PROJECT, 2023
** server
** File description:
** clock_delay
*/

#include "clock.h"

void clock_delay(const struct timespec *timing, double frequency)
{

    double tick_delay;
    struct timespec offset;
    struct timespec timing2;

    if (frequency <= 0)
        return;
    tick_delay = 1 / frequency;
    offset.tv_sec = tick_delay;
    offset.tv_nsec = 1e9 * (tick_delay - ((double) offset.tv_sec));
    clock_gettime(CLOCK_REALTIME, &timing2);
    offset.tv_sec -= timing2.tv_sec - timing->tv_sec;
    offset.tv_nsec -= timing2.tv_nsec - timing->tv_nsec;
    nanosleep(&offset, NULL);
}
