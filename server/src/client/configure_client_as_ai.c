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
    memset(client->inventory, 0, sizeof(int) * 7);
    client->inventory[FOOD] = 10;
    client->team = team;
    add_player_on_tile(&client->server->map.tiles[client->pos.y][client->pos.x],
    client);
    timespec_get(&(client->last_meal), TIME_UTC);
    zp_gui_send_package(&(client->server->gui_update_data), SERVER_SENT,
        ZP_PNW, client->data.fd, client->pos.x, client->pos.y,
        client->orientation, client->level, client->team);
}
