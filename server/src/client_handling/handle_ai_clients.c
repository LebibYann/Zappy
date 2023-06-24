/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_ai_clients
*/

#include "zappy_server.h"


void handle_ai_clients(server_t *server, client_t *client)
{
    t_zp_ai_to_serv_data command;

    while (get_pending_command(client, &command, server->frequency)) {
        printf("%d\n", command.cmd_type);
        zp_server_ai_clear_protocol_struct(&command);
    }
}
