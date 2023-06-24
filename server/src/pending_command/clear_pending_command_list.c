/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** clear_pending_command_list
*/

#include "zappy_pending_command.h"

void clear_pending_command_list(pending_command_t *cmd_list, int size)
{
    for (int i = 0; i < size; ++i) {
        zp_server_ai_clear_protocol_struct(&(cmd_list->command));
        cmd_list->start_time.tv_sec = 0;
        cmd_list->start_time.tv_nsec = 0;
        cmd_list->tick_to_wait = 0;
    }
}
