/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** add_command_to_pending_list
*/

#include "zappy_pending_command.h"

bool add_command_to_pending_list(struct pending_command_list_s *pending_list,
t_zp_ai_to_serv_data *command, int tick_to_wait)
{
    size_t count = 0;
    pending_command_t *pending_cmd = NULL;
    pending_command_t *next_pending_cmd;
    pending_command_t *new_pending_cmd;

    LIST_FOREACH(next_pending_cmd, pending_list, other_commands) {
        pending_cmd = next_pending_cmd;
        ++count;
        if (count >= MAX_PENDING_COMMAND)
            return (false);
    }
    new_pending_cmd = new_pending_command();
    memcpy(&(new_pending_cmd->command), command, sizeof(*command));
    new_pending_cmd->tick_to_wait = tick_to_wait;
    new_pending_cmd->start_time.tv_sec = -1;
    if (LIST_EMPTY(pending_list))
        LIST_INSERT_HEAD(pending_list, new_pending_cmd, other_commands);
    else
        LIST_INSERT_AFTER(pending_cmd, new_pending_cmd, other_commands);
    return (true);
}
