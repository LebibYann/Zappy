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

    for (int i = 0; i < height; i++) {
        map[i] = malloc(sizeof(tile_t) * width);
        for (int j = 0; j < width; j++) {
            map[i][j].food = rand() % 10;
            map[i][j].linemate = rand() % 10;
            map[i][j].deraumere = rand() % 10;
            map[i][j].sibur = rand() % 10;
            map[i][j].mendiane = rand() % 10;
            map[i][j].phiras = rand() % 10;
            map[i][j].thystame = rand() % 10;
        }
    }
    return (map);
}
