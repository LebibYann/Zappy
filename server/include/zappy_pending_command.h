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

pending_command_t *new_pending_command(void);

void init_pending_command(pending_command_t *pending_cmd);

void clear_pending_command(pending_command_t *pending_cmd);

void delete_pending_command(pending_command_t *pending_cmd);

void empty_pending_list(struct pending_command_list_s *pending_list);

bool add_command_to_pending_list(struct pending_command_list_s *pending_list,
t_zp_ai_to_serv_data *command, int tick_to_wait);

bool get_ready_command_from_pending_list(
struct pending_command_list_s *pending_list,
t_zp_ai_to_serv_data *command, int frequency);

void convert_tick_to_time(struct timespec *timing, int tick, int frequency);

void add_timespec(struct timespec *dest, const struct timespec *src);
