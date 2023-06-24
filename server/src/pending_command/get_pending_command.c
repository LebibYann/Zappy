/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** get_pending_command
*/

#include "zappy_pending_command.h"

static bool receive_last_package(
client_t *client, t_zp_ai_to_serv_data *command)
{
    size_t i = 0;

    if (!zp_server_ai_receive_package(&(client->data), command))
        return (false);
    for (; i < ZP_TOTAL_AI_CMD; ++i) {
        if (command->cmd_type == AI_CLI_COMMANDS[i].id)
            break;
    }
    if (add_command_to_pending_list(
    &(client->pending_list), command, AI_CLI_COMMANDS[i].tick))
        zp_server_ai_clear_protocol_struct(command);
    return (false);
}

bool get_pending_command(client_t *client, t_zp_ai_to_serv_data *command,
int frequency)
{
    if (receive_last_package(client, command))
        return (true);
    return (get_ready_command_from_pending_list(
        &(client->pending_list), command, frequency));
}
