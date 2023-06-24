/*
** EPITECH PROJECT, 2023
** server
** File description:
** zappy_pending_command
*/

#pragma once

#include <time.h>

#include "c_zappy_protocol.h"
#include "zappy_pending_command_struct.h"
#include "zappy_client.h"

bool get_pending_command(client_t *client, t_zp_ai_to_serv_data *command,
int frequency);

void init_pending_command_list(pending_command_t *cmd_list, int size);

void clear_pending_command_list(pending_command_t *cmd_list, int size);

bool add_command_to_pending_list(pending_command_t *pending_list,
t_zp_ai_to_serv_data *command, int tick_to_wait);

bool get_ready_command_from_pending_list(pending_command_t *pending_list,
t_zp_ai_to_serv_data *command, int frequency);

void convert_tick_to_time(struct timespec *timing, int tick, int frequency);

void add_timespec(struct timespec *dest, const struct timespec *src);
