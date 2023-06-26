/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** movement
*/

#include "zappy_server.h"

static void move_orientation(map_t *map, client_t *player)
{
    switch (player->orientation) {
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
    default:
        break;
    }
    if (player->pos.x < 0)
        player->pos.x = map->w - 1;
    if (player->pos.y < 0)
        player->pos.y = map->h - 1;
}

void forward(map_t *map, client_t *player)
{
    tile_t *tile;

    tile = &map->tiles[player->pos.y][player->pos.x];
    remove_player_on_tile(tile, player);

    move_orientation(map, player);

    tile = &map->tiles[player->pos.y][player->pos.x];
    add_player_on_tile(tile, player);
    zp_server_ai_send_basic_package(&player->data, RESPONSE_OK);
    zp_gui_send_package(&(player->server->gui_update_data), SERVER_SENT, ZP_PPO,
    player->data.fd, player->pos.x, player->pos.y, player->orientation);
}
