/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** incantations
*/

#include "zappy_server.h"
#include "zappy_incantations.h"

static void remove_stone(tile_t *tile, int level)
{
    for (int stone = 1; stone < RESOURCES_COUNT; stone++)
        tile->resources[stone] -= INCANTATIONS[level - 1].prerequisites[stone];
}

static void elevate_player(client_t *player)
{
    char response[32];

    (player->level)++;
    sprintf(response, "Current level: %d\n", player->level);
    zp_write_data(&(player->data), response, strlen(response));
    zp_gui_send_package(&(player->server->gui_update_data), SERVER_SENT, ZP_PLV,
    player->data.fd, player->level);
}

static void send_incantation_result(tile_t *tile, client_t *player)
{
    client_t *client = NULL;
    int bond = player->incantation_bond;
    bool incantation_status = verify_incantation(tile, player);

    LIST_FOREACH(client, &(player->server->client_list), other_clients) {
        if (client->category == CATEGORY_AI &&
        client->incantation_bond == bond) {
            client->incantation_bond = 0;
            if (incantation_status)
                elevate_player(client);
            else
                zp_server_ai_send_basic_package(&(client->data), RESPONSE_KO);
        }
    }
}

void start_incantation(tile_t *tile, client_t *player)
{
    int i = 1;
    client_t *client = NULL;
    timespec_get(&player->incantation_start, TIME_UTC);
    player->incantation = true;
    if (player->incantation_bond != 0 || !verify_incantation(tile, player)) {
        zp_server_ai_send_basic_package(&(player->data), RESPONSE_KO);
        return;
    }
    player->incantation_bond = rand();
    player->incantation_bond += (player->incantation_bond == 0);
    for (player_list_t *list = tile->players; list &&
    i < INCANTATIONS[player->level - 1].prerequisites[0]; list = list->next) {
        client = list->client;
        if (client->incantation_bond == 0 && client->level == player->level) {
            client->incantation_bond = player->incantation_bond;
            ++i;
            zp_server_ai_send_package(&(client->data), "Elevation underway\n");
        }
    }
    zp_server_ai_send_package(&player->data, "Elevation underway\n");
}

void complete_incantation(tile_t *tile, client_t *player, int frequency)
{
    int initial_level = player->level;
    struct timespec now;
    double elapsed_time;

    timespec_get(&now, TIME_UTC);
    elapsed_time = (now.tv_sec - player->incantation_start.tv_sec)
        + ((double) (now.tv_nsec - player->incantation_start.tv_nsec)) / 1e9;
    if (elapsed_time < (300 / frequency))
        return;
    player->incantation = false;
    send_incantation_result(tile, player);
    if (initial_level < player->level)
        remove_stone(tile, initial_level);
}
