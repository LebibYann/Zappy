/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** generate_map
*/

#include "zappy_server.h"

void generate_food(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].food += 1;
}

void generate_linemate(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].linemate += 1;
}

void generate_deraumere(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].deraumere += 1;
}

void generate_sibur(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].sibur += 1;
}

void generate_mendiane(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].mendiane += 1;
}

void generate_phiras(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].phiras += 1;
}

void generate_thystame(tile_t **map, int w, int h)
{
    int x = rand() % w;
    int y = rand() % h;

    map[y][x].thystame += 1;
}

void generate_map(tile_t **map, int w, int h, int *resources)
{
    for (int i = resources[FOOD]; i < w * h * FOOD_DENSITY; i++)
        generate_food(map, w, h);
    for (int i = resources[LINEMATE]; i < w * h * LINEMATE_DENSITY; i++)
        generate_linemate(map, w, h);
    for (int i = resources[DERAUMERE]; i < w * h * DERAUMERE_DENSITY; i++)
        generate_deraumere(map, w, h);
    for (int i = resources[SIBUR]; i < w * h * SIBUR_DENSITY; i++)
        generate_sibur(map, w, h);
    for (int i = resources[MENDIANE]; i < w * h * MENDIANE_DENSITY; i++)
        generate_mendiane(map, w, h);
    for (int i = resources[PHIRAS]; i < w * h * PHIRAS_DENSITY; i++)
        generate_phiras(map, w, h);
    for (int i = resources[THYSTAME]; i < w * h * THYSTAME_DENSITY; i++)
        generate_thystame(map, w, h);
}

tile_t **initialize_map(int w, int h)
{
    tile_t **map = malloc(sizeof(tile_t *) * h);

    if (!map)
        return (NULL);

    for (int i = 0; i < h; i++) {
        map[i] = malloc(sizeof(tile_t) * w);
        if (!map[i])
            return (NULL);
        for (int j = 0; j < w; j++) {
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
