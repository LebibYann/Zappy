/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** generate_map
*/

#include "zappy_server.h"
#include "zappy_resources.h"

void generate_resource(server_t *server, map_t *map, int resource)
{
    int x, y;

    for (int i = 0; server->resource_count[resource] <
    map->w * map->h * resource_densities[resource]; i++) {
        x = rand() % map->w;
        y = rand() % map->h;

        map->tiles[y][x].resources[resource] += 1;
        ++(server->resource_count[resource]);
        send_tile(&(server->gui_update_data), x, y, map->tiles[y][x].resources);
    }
}

void generate_map(server_t *server)
{
    for (int resource = 0; resource < RESOURCES_COUNT; resource++)
        generate_resource(server, &server->map, resource);
}

void allocate_map(map_t *map)
{
    map->tiles = calloc(map->h, sizeof(tile_t *));

    if (!map->tiles)
        return;

    for (int i = 0; i < map->h; i++) {
        map->tiles[i] = calloc(map->w, sizeof(tile_t));
        if (!map->tiles[i])
            return;
        for (int j = 0; j < map->w; j++) {
            memset(map->tiles[i][j].resources, 0, sizeof(int) * 7);
            map->tiles[i][j].players = NULL;
            map->tiles[i][j].eggs = NULL;
        }
    }
}

void initialize_map(map_t *map, int w, int h)
{
    map->w = w;
    map->h = h;
    map->tiles = NULL;
}
