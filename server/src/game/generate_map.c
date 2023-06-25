/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** generate_map
*/

#include "zappy_server.h"

void generate_resource(map_t *map, int resource)
{
    int x, y;

    for (int i = 0; i < map->w * map->h * resource_densities[resource]; i++) {
        x = rand() % map->w;
        y = rand() % map->h;

        map->tiles[y][x].resources[resource] += 1;
    }
}

void generate_map(map_t *map)
{
    for (int resource = 0; resource < RESOURCES_COUNT; resource++)
        generate_resource(map, resource);
}

void allocate_map(map_t *map)
{
    map->tiles = malloc(sizeof(tile_t *) * map->h);

    if (!map->tiles)
        return;

    for (int i = 0; i < map->h; i++) {
        map->tiles[i] = calloc(map->w, sizeof(tile_t));
        if (!map->tiles[i])
            return;
        for (int j = 0; j < map->w; j++) {
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
