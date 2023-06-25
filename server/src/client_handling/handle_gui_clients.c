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
    zp_exchange_data(&(client->data), HANDLE_NO_WAIT, HANDLE_IGNORE);
    while ((ret = zp_gui_receive_package(&(client->data), &command, CLIENT_SENT, false)) == 0) {
        switch (command.cmd_type) {
        case ZP_PPO:            player_position(command); break;
        case ZP_RIGHT:          turn_right(client); break;
        case ZP_LEFT:           turn_left(client); break;
        case ZP_LOOK:           look_around(&server->map, client); break;
        case ZP_INVENTORY:      inventory(client); break;
        case ZP_BROADCAST:      broadcast(server, client, command.str); break;
        case ZP_CONNECT_NBR:    connect_nbr(server, client); break;
        case ZP_EJECT:          eject(&server->map, client); break;
        case ZP_TAKE_OBJ:       take_object(&server->map.tiles[client->pos.x][client->pos.y], client, get_resource_type(command.str)); break;
        case ZP_SET_OBJ:        set_object_down(&server->map.tiles[client->pos.x][client->pos.y], client, get_resource_type(command.str)); break;
        case ZP_INCANTATION:    start_incantation(&server->map.tiles[client->pos.x][client->pos.y], client); break;
        default:                break;
        }
        zp_gui_clear_protocol_struct(&command);
    }
}
