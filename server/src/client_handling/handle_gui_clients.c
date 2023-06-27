/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_gui_clients
*/

#include "zappy_server.h"

static void handle_received_gui_command(server_t *server, client_t *client,
t_zp_gui_protocol *command)
{
    switch (command->cmd_type) {
    case ZP_MCT:
        send_map(&(server->gui_update_data), &(server->map));
        break;
    case ZP_BCT:
        send_tile(&(server->gui_update_data),
        command->args[0], command->args[1],
        server->map.tiles[command->args[0]][command->args[1]].resources);
        break;
    case ZP_PPO:
        zp_gui_send_package(&(server->gui_update_data), SERVER_SENT, ZP_PPO,
        client->data.fd, client->pos.x, client->pos.y, client->orientation);
        break;
    default:
        break;
    }
}


void handle_gui_clients(server_t *server, client_t *client)
{
    t_zp_gui_protocol command;

    zp_gui_init_protocol_struct(&command);
    zp_exchange_data(&(client->data), HANDLE_IGNORE, HANDLE_NO_WAIT);
    while (zp_gui_receive_package(&(client->data), &command,
    CLIENT_SENT, false) == 0) {
        handle_received_gui_command(server, client, &command);
        zp_gui_clear_protocol_struct(&command);
    }
}
