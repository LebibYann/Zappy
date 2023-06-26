/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_gui_clients
*/

#include "zappy_server.h"


void handle_gui_clients(server_t *server, client_t *client)
{
    t_zp_gui_protocol command;
    int ret;

    zp_gui_init_protocol_struct(&command);
    while ((ret = zp_gui_receive_package(&(client->data), &command, CLIENT_SENT, false)) == 0) {
        switch (command.cmd_type) {
        case ZP_MCT:
            send_map(&(server->gui_update_data), &(server->map));
            break;
        case ZP_BCT:
            send_tile(&(server->gui_update_data),
            command.args[0], command.args[1],
            server->map.tiles[command.args[0]][command.args[1]].resources);
            break;
        case ZP_PPO:
            zp_gui_send_package(&(server->gui_update_data), SERVER_SENT, ZP_PPO,
            client->data.fd, client->pos.x, client->pos.y, client->orientation);
            break;
        default:
            break;
        }
        zp_gui_clear_protocol_struct(&command);
    }
}

void update_map(server_t *server)
{
    client_t *client = NULL;

    LIST_FOREACH(client, &server->client_list, other_clients)
        if (client->category == CATEGORY_GUI) {
            // map_content(server, client);
        }
}

void update_player_level(server_t *server, client_t *ai)
{
    client_t *client = NULL;

    LIST_FOREACH(client, &server->client_list, other_clients) {
        if (client->category == CATEGORY_GUI) {
            player_level(server, client, ai->data.fd);
        }
    }
}

// void update_player_position(server_t *server, client_t *ai)
// {
//     client_t *client = NULL;

//     LIST_FOREACH(client, &server->client_list, other_clients) {
//         if (client->category == CATEGORY_GUI) {
//             player_position(server, client, ai->fd);
//         }
//     }
// }
