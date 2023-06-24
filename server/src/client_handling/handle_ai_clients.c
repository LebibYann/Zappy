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

    zp_server_ai_init_protocol_struct(&command);
    while (get_pending_command(client, &command, server->frequency)) {
        zp_server_ai_send_basic_package(&(client->data), RESPONSE_OK);
        zp_server_ai_clear_protocol_struct(&command);
    }
}
