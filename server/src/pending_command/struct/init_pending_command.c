/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** init_pending_command_list
*/

#include "zappy_pending_command.h"

void init_pending_command(pending_command_t *pending_cmd)
{
    zp_server_ai_init_protocol_struct(&(pending_cmd->command));
    pending_cmd->start_time.tv_sec = 0;
    pending_cmd->start_time.tv_nsec = 0;
    pending_cmd->tick_to_wait = 0;
}
