/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** delete_pending_command
*/

#include "zappy_pending_command.h"

void delete_pending_command(pending_command_t *pending_cmd)
{
    clear_pending_command(pending_cmd);
    free(pending_cmd);
}
