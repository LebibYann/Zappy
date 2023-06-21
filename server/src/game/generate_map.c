/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** generate_map
*/

#include "zappy_server.h"

void generate_food(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].food += 1;
}

void generate_linemate(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].linemate += 1;
}

void generate_deraumere(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].deraumere += 1;
}

void generate_sibur(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].sibur += 1;
}

void generate_mendiane(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].mendiane += 1;
}

void generate_phiras(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].phiras += 1;
}

void generate_thystame(tile_t **map, int width, int height)
{
    int x = rand() % width;
    int y = rand() % height;

    map[y][x].thystame += 1;
}

tile_t **generate_map(int width, int height)
{
    tile_t **map = malloc(sizeof(tile_t *) * height);

    if (!map)
        return (NULL);

    for (int i = 0; i < width * height * FOOD_DENSITY; i++)
        generate_food(map, width, height);
    for (int i = 0; i < width * height * LINEMATE_DENSITY; i++)
        generate_linemate(map, width, height);
    for (int i = 0; i < width * height * DERAUMERE_DENSITY; i++)
        generate_deraumere(map, width, height);
    for (int i = 0; i < width * height * SIBUR_DENSITY; i++)
        generate_sibur(map, width, height);
    for (int i = 0; i < width * height * MENDIANE_DENSITY; i++)
        generate_mendiane(map, width, height);
    for (int i = 0; i < width * height * PHIRAS_DENSITY; i++)
        generate_phiras(map, width, height);
    for (int i = 0; i < width * height * THYSTAME_DENSITY; i++)
        generate_thystame(map, width, height);

    return (map);
}
