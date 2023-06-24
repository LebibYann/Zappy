/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** new_pending_command
*/

#include "zappy_pending_command.h"

pending_command_t *new_pending_command(void)
{
    pending_command_t *pending_cmd = malloc(sizeof(*pending_cmd));

    init_pending_command(pending_cmd);
    return (pending_cmd);
}
