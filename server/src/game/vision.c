/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** vision
*/

#include "zappy_server.h"

static int get_fov_size(int player_level)
{
    player_level++;
    return player_level * player_level;
}

static tile_t *get_tiles(map_t *map, client_t *player, int dx, int dy)
{
    tile_t *fov = malloc(sizeof(tile_t) * get_fov_size(player->level));
    int i = 0;

    if (!fov)
        return NULL;

    for (int depth = 0; depth < player->level; depth++) {
        for (int width = -depth; width <= depth; width++) {
            int y = player->pos.y + dy * ((dx != dy) ? depth : width);
            int x = player->pos.x + dy * ((dx != dy) ? width : depth);
            fov[i++] = map->tiles[y][x];
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

void look_around(map_t *map, client_t *player)
{
    tile_t *tiles = look_orientation(map, player);
    int nb_tiles = get_fov_size(player->level);
    char *response = strdup("[");

    for (int i = 0; i < nb_tiles; i++) {
        for (int resource = 0; resource < RESOURCES_COUNT; resource++) {
            for (int j = 0; j < tiles[i].resources[resource]; j++) {
                response = realloc(response, strlen(response) + strlen(resource_str(resource) + 2));
                response = strcat(response, resource_str(resource));
                response = strcat(response, " ");
            }
        }
    }
    response = realloc(response, strlen(response) + 3);
    response = strcat(response, "]\n");

    zp_server_ai_send_package(&player->data, response);
}
