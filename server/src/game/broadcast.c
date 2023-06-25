/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** broadcast
*/

#include "zappy_server.h"

static void send_message_on_tile(tile_t *tile, position_t origin, char *message)
{
    player_list_t *players = tile->players;

    while (players) {
        sprintf(message, "message %d %d, %s\n", origin.x, origin.y, message);
        zp_server_ai_send_package(&players->client->data, message);
        players = players->next;
    }
}

static int sound_transmission(client_t *sender, client_t *recever)
{
    position_t vector = {sender->pos.x - recever->pos.x,
    sender->pos.x - recever->pos.y};

    if (vector.x == 0 && vector.y > 0)
        return (TOP);
    if (vector.x < 0 && vector.y > 0)
        return (TOP_LEFT);
    if (vector.x < 0 && vector.y == 0)
        return (LEFT);
    if (vector.x < 0 && vector.y < 0)
        return (BOTTOM_LEFT);
    if (vector.x == 0 && vector.y < 0)
        return (BOTTOM);
    if (vector.x > 0 && vector.y < 0)
        return (BOTTOM_RIGHT);
    if (vector.x > 0 && vector.y == 0)
        return (RIGHT);
    if (vector.x > 0 && vector.y > 0)
        return (TOP_RIGHT);
    return (CENTER);
}

static void adjust_direction(client_t *client, int *direction)
{
    if (*direction == 0)
        return;
    for (size_t i = 0; i < client->orientation; i++){
        *direction = *direction - 1;
        if (*direction == 0)
            *direction = 8;
    }
}

void broadcast(server_t *server, client_t *player, char *message)
{
    client_t *client;
    int direction;
    char response[1024];

    LIST_FOREACH(client, &server->client_list, other_clients){
        if (client->category == CATEGORY_AI && client != player){
            direction = sound_transmission(player, client);
            adjust_direction(client, &direction);
            sprintf(response, "message %d, %s\n", direction, message);
            zp_server_ai_send_package(&client->data, message);
        }
    };
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}
