/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** configure_client_as_ai
*/

#include "zappy_server.h"
#include "zappy_client.h"
#include "zappy_pending_command.h"

void configure_client_as_ai(client_t *client, const char *team)
{
    client->category = CATEGORY_AI;
    client->level = 1;
    client->inventory[FOOD] = 10;
    client->inventory[LINEMATE] = 0;
    client->inventory[DERAUMERE] = 0;
    client->inventory[SIBUR] = 0;
    client->inventory[MENDIANE] = 0;
    client->inventory[PHIRAS] = 0;
    client->inventory[THYSTAME] = 0;
    client->team = team;
    add_player_on_tile(&client->server->map.tiles[client->pos.y][client->pos.x], client);
    timespec_get(&(client->last_meal), TIME_UTC);
    player_info(client->server, client);
}
