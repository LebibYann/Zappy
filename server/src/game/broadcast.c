/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** broadcast
*/

#include "zappy_server.h"

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
    for (int i = 0; i < client->orientation; i++){
        *direction = *direction - 1;
        if (*direction == 0)
            *direction = 8;
    }
}

void broadcast(server_t *server, client_t *player, const char *message)
{
    client_t *client;
    int direction;
    char response[1024];

    LIST_FOREACH(client, &server->client_list, other_clients){
        if (client->category == CATEGORY_AI && client != player){
            direction = sound_transmission(player, client);
            adjust_direction(client, &direction);
            sprintf(response, "message %d, %s\n", direction, message);
            zp_server_ai_send_package(&client->data, response);
        }
    };
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}
