/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** vision
*/

#include "zappy_server.h"

static tile_t *get_tiles(map_t *map, client_t *player, int dx, int dy)
{
    tile_t *fov = malloc(sizeof(tile_t) * GET_FOV_SIZE(player->level));
    int i = 0;

    if (!fov)
        return NULL;

    for (int depth = 0; depth <= player->level; depth++) {
        for (int width = -depth; width <= depth; width++) {
            int y = player->pos.y + dy * ((dx != dy) ? depth : width);
            int x = player->pos.x + dy * ((dx != dy) ? width : depth);
            y = (y < 0) ? map->h + y : y;
            x = (x < 0) ? map->w + x : x;
            fov[i] = map->tiles[y % map->h][x % map->w];
            i++;
        }
    }

    return fov;
}

static tile_t *look_orientation(map_t *map, client_t *player)
{
    switch (player->orientation) {
    case NORTH:
        return get_tiles(map, player, 1, -1);
        break;
    case EAST:
        return get_tiles(map, player, 1, 1);
        break;
    case SOUTH:
        return get_tiles(map, player, -1, 1);
        break;
    case WEST:
        return get_tiles(map, player, -1, -1);
        break;
    default:
        return NULL;
        break;
    }
}

static char *resource_str(int resource)
{
    switch (resource) {
    case FOOD:
        return "food";
    case LINEMATE:
        return "linemate";
    case DERAUMERE:
        return "deraumere";
    case SIBUR:
        return "sibur";
    case MENDIANE:
        return "mendiane";
    case PHIRAS:
        return "phiras";
    case THYSTAME:
        return "thystame";
    default:
        return NULL;
    }
}

static void write_looked_item(client_t *player, tile_t *tile)
{
    for (int resource = 0; resource < RESOURCES_COUNT; resource++) {
        for (int j = 0; j < tile->resources[resource]; j++) {
            zp_write_data(&(player->data), " ", 1);
            zp_write_data(&(player->data), resource_str(resource),
            strlen(resource_str(resource)));
        }
    }
}

void look_around(map_t *map, client_t *player)
{
    tile_t *tiles = look_orientation(map, player);
    int nb_tiles = GET_FOV_SIZE(player->level);

    zp_write_data(&(player->data), "[", 1);
    for (int i = 0; i < nb_tiles; i++) {
        if (i != 0)
            zp_write_data(&(player->data), ",", 1);
        write_looked_item(player, &tiles[i]);
        for (player_list_t *players = tiles[i].players; players; players = players->next) {
            zp_write_data(&(player->data), " player", 7);
        }
    }
    zp_write_data(&(player->data), " ]\n", 3);
    zp_exchange_data(&(player->data), HANDLE_IGNORE, HANDLE_NO_WAIT);
}
