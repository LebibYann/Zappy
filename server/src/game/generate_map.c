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

void generate_map(tile_t **map, int width, int height, int *resources)
{
    for (int i = resources[FOOD]; i < width * height * FOOD_DENSITY; i++)
        generate_food(map, width, height);
    for (int i = resources[LINEMATE]; i < width * height * LINEMATE_DENSITY; i++)
        generate_linemate(map, width, height);
    for (int i = resources[DERAUMERE]; i < width * height * DERAUMERE_DENSITY; i++)
        generate_deraumere(map, width, height);
    for (int i = resources[SIBUR]; i < width * height * SIBUR_DENSITY; i++)
        generate_sibur(map, width, height);
    for (int i = resources[MENDIANE]; i < width * height * MENDIANE_DENSITY; i++)
        generate_mendiane(map, width, height);
    for (int i = resources[PHIRAS]; i < width * height * PHIRAS_DENSITY; i++)
        generate_phiras(map, width, height);
    for (int i = resources[THYSTAME]; i < width * height * THYSTAME_DENSITY; i++)
        generate_thystame(map, width, height);
}

tile_t **initialize_map(int width, int height)
{
    tile_t **map = malloc(sizeof(tile_t *) * height);

    if (!map)
        return (NULL);

    for (int i = 0; i < height; i++) {
        map[i] = malloc(sizeof(tile_t) * width);
        if (!map[i])
            return (NULL);
        for (int j = 0; j < width; j++) {
            map[i][j].food = 0;
            map[i][j].linemate = 0;
            map[i][j].deraumere = 0;
            map[i][j].sibur = 0;
            map[i][j].mendiane = 0;
            map[i][j].phiras = 0;
            map[i][j].thystame = 0;
        }
    }
    return (map);

}
