/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** get_ready_command_from_pending_list
*/

#include "zappy_pending_command.h"

static bool is_command_ready(pending_command_t *pending_list,
t_zp_ai_to_serv_data *command,
struct timespec *current_time, struct timespec *end_time)
{
    if (pending_list->command.cmd_type != ZP_END &&
    (current_time->tv_sec > end_time->tv_sec ||
    (current_time->tv_sec == end_time->tv_sec &&
    current_time->tv_nsec >= end_time->tv_nsec))) {
        *command = pending_list->command;
        pending_list->tick_to_wait = 0;
        pending_list->start_time.tv_sec = 0;
        pending_list->start_time.tv_nsec = 0;
        pending_list->command.cmd_type = ZP_END;
        pending_list->command.str = NULL;
        return (true);
    }
    return (false);
}

bool get_ready_command_from_pending_list(pending_command_t *pending_list,
t_zp_ai_to_serv_data *command, int frequency)
{
    struct timespec current_tm;
    struct timespec end_tm;

    timespec_get(&current_tm, TIME_UTC);
    for (size_t i = 0; i < MAX_PENDING_COMMAND; ++i) {
        convert_tick_to_time(&end_tm, pending_list[i].tick_to_wait, frequency);
        add_timespec(&end_tm, &(pending_list[i].start_time));
        if (is_command_ready(pending_list, command, &current_tm, &end_tm))
            return (true);
    }
    return (false);
}
