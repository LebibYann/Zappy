/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_client_struct
*/

#pragma once

#include <sys/queue.h>

#include "zappy_struct.h"

#define MAX_PENDING_COMMAND 10

typedef struct pending_command_s {
    t_zp_ai_to_serv_data command;
    struct timespec start_time;
    int tick_to_wait;
    LIST_ENTRY(pending_command_s) other_commands;
} pending_command_t;

LIST_HEAD(pending_command_list_s, pending_command_s);
