/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** get_ready_command_from_pending_list
*/

#include "zappy_pending_command.h"

static bool is_command_ready(pending_command_t *pending_cmd,
t_zp_ai_to_serv_data *command, int frequency)
{
    struct timespec current_tm;
    struct timespec end_tm;

    timespec_get(&current_tm, TIME_UTC);
    convert_tick_to_time(&end_tm, pending_cmd->tick_to_wait, frequency);
    add_timespec(&end_tm, &(pending_cmd->start_time));
    if (current_tm.tv_sec > end_tm.tv_sec ||
    (current_tm.tv_sec == end_tm.tv_sec &&
    current_tm.tv_nsec >= end_tm.tv_nsec)) {
        *command = pending_cmd->command;
        return (true);
    }
    return (false);
}

bool get_ready_command_from_pending_list(
struct pending_command_list_s *pending_list,
t_zp_ai_to_serv_data *command, int frequency)
{
    pending_command_t *pending_cmd;

    if (LIST_EMPTY(pending_list))
        return (false);
    pending_cmd = LIST_FIRST(pending_list);
    if (pending_cmd->start_time.tv_sec < 0)
        timespec_get(&(pending_cmd->start_time), TIME_UTC);
    if (is_command_ready(pending_cmd, command, frequency)) {
        LIST_REMOVE(pending_cmd, other_commands);
        free(pending_cmd);
        return (true);
    }
    return (false);
}
