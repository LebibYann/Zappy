/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** generate_map
*/

#include "zappy_server.h"

void generate_resource(tile_t **map, int w, int h, int resource)
{
    int x, y;

    for (int i = 0; i < w * h * resource_densities[resource]; i++) {
        x = rand() % w;
        y = rand() % h;

        map[y][x].resources[resource] += 1;
    }
}

void generate_map(tile_t **map, int w, int h)
{
    for (int resource = 0; resource < RESOURCES_COUNT; resource++)
        generate_resource(map, w, h, resource);
}

tile_t **initialize_map(int w, int h)
{
    tile_t **map = malloc(sizeof(tile_t *) * h);

    if (!map)
        return (NULL);

    for (int i = 0; i < h; i++) {
        map[i] = calloc(w, sizeof(tile_t));
        if (!map[i])
            return (NULL);
    }
    return (map);
}
