/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** empty_pending_list
*/

#include "zappy_pending_command.h"

void empty_pending_list(struct pending_command_list_s *pending_list)
{
    pending_command_t *pending_cmd;

    while (!LIST_EMPTY(pending_list)) {
        pending_cmd = LIST_FIRST(pending_list);
        LIST_REMOVE(pending_cmd, other_commands);
        delete_pending_command(pending_cmd);
    }
}
