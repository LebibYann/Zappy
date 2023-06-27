/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** eject
*/

#include "zappy_server.h"

static tile_t *get_target_tile(map_t *map, client_t *player)
{
    switch (player->orientation) {
    case NORTH:
        return &map->tiles[player->pos.y - 1][player->pos.x];
        break;
    case EAST:
        return &map->tiles[player->pos.y][player->pos.x + 1];
        break;
    case SOUTH:
        return &map->tiles[player->pos.y + 1][player->pos.x];
        break;
    case WEST:
        return &map->tiles[player->pos.y][player->pos.x - 1];
        break;
    default:
        return NULL;
        break;
    }
}

static void update_orientation(map_t *map, client_t *player,
enum orientation_e orientation)
{
    switch (orientation) {
    case NORTH:
        player->pos.y = (player->pos.y - 1) % map->h;
        break;
    case EAST:
        player->pos.x = (player->pos.x + 1) % map->w;
        break;
    case SOUTH:
        player->pos.y = (player->pos.y + 1) % map->h;
        break;
    case WEST:
        player->pos.x = (player->pos.x - 1) % map->w;
        break;
    }
    if (player->pos.x < 0)
        player->pos.x = map->w - 1;
    if (player->pos.y < 0)
        player->pos.y = map->h - 1;
}

static void send_eject_response(client_t *player,
enum orientation_e orientation)
{
    switch (orientation) {
    case NORTH:
        zp_server_ai_send_package(&player->data, "eject: NORTH\n");
        break;
    case EAST:
        zp_server_ai_send_package(&player->data, "eject: EAST\n");
        break;
    case SOUTH:
        zp_server_ai_send_package(&player->data, "eject: SOUTH\n");
        break;
    case WEST:
        zp_server_ai_send_package(&player->data, "eject: WEST\n");
        break;
    default:
        break;
    }
}

void eject(map_t *map, client_t *player)
{
    bool success = false;
    tile_t *tile = &map->tiles[player->pos.y][player->pos.x];
    tile_t *target_tile = get_target_tile(map, player);

    for (player_list_t *tmp = tile->players; tmp; tmp = tmp->next) {
        if (tmp->client != player) {
            success = true;
            update_orientation(map, tmp->client, player->orientation);
            remove_player_on_tile(tile, tmp->client);
            add_player_on_tile(target_tile, tmp->client);
            send_eject_response(tmp->client, player->orientation);
        }
    }
    if (success) {
        zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
        send_map(&(player->server->gui_update_data), &(player->server->map));
    } else
        zp_server_ai_send_basic_package(&player->data, RESPONSE_KO);
    zp_gui_send_package(&player->data, SERVER_SENT, ZP_PPO, player->data.fd,
    player->pos.x, player->pos.y, player->orientation);
}
