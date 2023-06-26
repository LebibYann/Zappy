/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_ai_clients
*/

#include "zappy_server.h"

static int get_resource_type(char *str)
{
    if (str == NULL)
        return -1;
    if (!strncmp(str, "food", 4))
        return FOOD;
    if (!strncmp(str, "linemate", 8))
        return LINEMATE;
    if (!strncmp(str, "deraumere", 9))
        return DERAUMERE;
    if (!strncmp(str, "sibur", 5))
        return SIBUR;
    if (!strncmp(str, "mendiane", 8))
        return MENDIANE;
    if (!strncmp(str, "phiras", 6))
        return PHIRAS;
    if (!strncmp(str, "thystame", 8))
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
        case ZP_FORK:           lay_egg(&server->map.tiles[client->pos.y][client->pos.x], client); break;
        case ZP_EJECT:          eject(&server->map, client); break;
        case ZP_TAKE_OBJ:       take_object(&server->map.tiles[client->pos.y][client->pos.x], client, get_resource_type(command.str)); break;
        case ZP_SET_OBJ:        set_object_down(&server->map.tiles[client->pos.y][client->pos.x], client, get_resource_type(command.str)); break;
        case ZP_INCANTATION:    start_incantation(&server->map.tiles[client->pos.y][client->pos.x], client); break;
        default:                break;
        }
        zp_server_ai_clear_protocol_struct(&command);
    }
}

void complete_ai_incantation(server_t *server)
{
    client_t *client = NULL;

    LIST_FOREACH(client, &server->client_list, other_clients)
        if (client->category == CATEGORY_AI && client->incantation == true)
            complete_incantation(&server->map.tiles[client->pos.x][client->pos.y], client, server->frequency);
}

void food_time_ai(server_t *server)
{
    client_t *client = NULL;
    struct timespec now;
    double elapsed_time;

    LIST_FOREACH(client, &server->client_list, other_clients) {
        timespec_get(&now, TIME_UTC);
        elapsed_time = (now.tv_sec - client->last_meal.tv_sec)
            + ((double) (now.tv_nsec - client->last_meal.tv_nsec)) / 1e9;
        if (client->category == CATEGORY_AI && elapsed_time >= (126.0 / server->frequency)) {
            client->dead = (client->inventory[FOOD] <= 0);
            (client->dead) ? 0: client->inventory[FOOD]--;
            timespec_get(&(client->last_meal), TIME_UTC);
        }
    }
}
