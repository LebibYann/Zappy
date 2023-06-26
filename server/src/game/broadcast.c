/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** broadcast
*/

#include "zappy_server.h"

static void determine_distance(position_t *vector, map_t *map,
client_t *sender, client_t *recever)
{
    vector->x = sender->pos.x - recever->pos.x;
    vector->y = sender->pos.y - recever->pos.y;
    if (map->w - abs(vector->x) < abs(vector->x))
        vector->x *= -1;
    if (map->h - abs(vector->y) < abs(vector->y))
        vector->y *= -1;
}

static int sound_transmission(client_t *sender, client_t *recever)
{
    position_t vector;

    determine_distance(&vector, &(sender->server->map), sender, recever);
    if (vector.x == 0 && vector.y < 0)
        return (TOP);
    if (vector.x < 0 && vector.y < 0)
        return (TOP_LEFT);
    if (vector.x < 0 && vector.y == 0)
        return (LEFT);
    if (vector.x < 0 && vector.y > 0)
        return (BOTTOM_LEFT);
    if (vector.x == 0 && vector.y > 0)
        return (BOTTOM);
    if (vector.x > 0 && vector.y > 0)
        return (BOTTOM_RIGHT);
    if (vector.x > 0 && vector.y == 0)
        return (RIGHT);
    if (vector.x > 0 && vector.y < 0)
        return (TOP_RIGHT);
    return (CENTER);
}

static void adjust_direction(client_t *client, int *direction)
{
    if (*direction == 0)
        return;
    for (int i = 0; i < client->orientation; i++){
        *direction += 2;
        if (*direction == 9)
            *direction = 1;
        if (*direction > 9)
            *direction = 2;
    }
}

void broadcast(server_t *server, client_t *player, const char *message)
{
    client_t *client;
    int direction;
    char response[32];

    LIST_FOREACH(client, &server->client_list, other_clients){
        if (client->category == CATEGORY_AI && client != player){
            direction = sound_transmission(player, client);
            adjust_direction(client, &direction);
            sprintf(response, "message %d, ", direction);
            zp_write_data(&(client->data), response, strlen(response));
            zp_write_data(&(client->data), message, strlen(message));
            zp_write_data(&(client->data), "\n", 1);
            zp_exchange_data(&(client->data), HANDLE_IGNORE, HANDLE_NO_WAIT);
        }
    };
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
}
