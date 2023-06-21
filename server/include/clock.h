/*
** EPITECH PROJECT, 2023
** server
** File description:
** clock
*/

#pragma once

#include <time.h>
#include <sys/time.h>

/**
 ** @brief This function let you indicate when the time measurement starts.
 ** It usually needs to be put at the start of a loop.
 **
 ** @param timing
 */
void clock_start(struct timespec *timing);

void clock_delay(const struct timespec *timing, double frequency);
