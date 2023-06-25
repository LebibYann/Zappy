/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_ai_clients
*/

#include "zappy_server.h"

static int get_resource_type(char *str)
{
    if (!strcmp(str, "food"))
        return FOOD;
    if (!strcmp(str, "linemate"))
        return LINEMATE;
    if (!strcmp(str, "deraumere"))
        return DERAUMERE;
    if (!strcmp(str, "sibur"))
        return SIBUR;
    if (!strcmp(str, "mendiane"))
        return MENDIANE;
    if (!strcmp(str, "phiras"))
        return PHIRAS;
    if (!strcmp(str, "thystame"))
        return THYSTAME;
    return -1;
}

void handle_ai_clients(server_t *server, client_t *client)
{
    t_zp_ai_to_serv_data command;

    zp_server_ai_init_protocol_struct(&command);
    while (get_pending_command(client, &command, server->frequency)) {
        switch (command.cmd_type) {
        case ZP_FORWARD:        forward(&server->map, client); break;
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
        zp_server_ai_clear_protocol_struct(&command);
    }
}
