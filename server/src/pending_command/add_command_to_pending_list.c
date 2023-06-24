/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** add_command_to_pending_list
*/

#include "zappy_pending_command.h"

bool add_command_to_pending_list(pending_command_t *pending_list,
t_zp_ai_to_serv_data *command, int tick_to_wait)
{
    for (size_t i = 0; i < MAX_PENDING_COMMAND; ++i) {
        if (pending_list[i].command.cmd_type == ZP_END) {
            pending_list[i].command = *command;
            timespec_get(&(pending_list[i].start_time), TIME_UTC);
            pending_list[i].tick_to_wait = tick_to_wait;
            return (true);
        }
    }
    return (false);
}
