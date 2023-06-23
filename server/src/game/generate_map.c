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

map_t *initialize_map(int w, int h)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return (NULL);

    map->w = w;
    map->h = h;
    map->tiles = malloc(sizeof(tile_t *) * h);

    for (int i = 0; i < h; i++) {
        map->tiles[i] = calloc(w, sizeof(tile_t));
        if (!map->tiles[i])
            return (NULL);
    }
    return (map);
}
