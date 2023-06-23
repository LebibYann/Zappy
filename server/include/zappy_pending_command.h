/*
** EPITECH PROJECT, 2023
** server
** File description:
** zappy_pending_command
*/

#pragma once

#include <time.h>

#include "c_zappy_protocol.h"

typedef struct pending_command_s {
    t_zp_ai_to_serv_data command;
    struct timeval start_time;
    int tick_to_wait;
} pending_command_t;

