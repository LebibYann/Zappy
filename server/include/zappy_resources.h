/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_resources
*/

#pragma once

#define RESOURCES_COUNT 7

#define FOOD_DENSITY 0.5
#define LINEMATE_DENSITY 0.3
#define DERAUMERE_DENSITY 0.15
#define SIBUR_DENSITY 0.1
#define MENDIANE_DENSITY 0.1
#define PHIRAS_DENSITY 0.08
#define THYSTAME_DENSITY 0.05

static const double resource_densities[RESOURCES_COUNT] = {
    FOOD_DENSITY,
    LINEMATE_DENSITY,
    DERAUMERE_DENSITY,
    SIBUR_DENSITY,
    MENDIANE_DENSITY,
    PHIRAS_DENSITY,
    THYSTAME_DENSITY
};

enum resources_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

struct map_s;

void initialize_map(struct map_s *map, int w, int h);

void allocate_map(struct map_s *map);

void generate_map(struct map_s *map);

void generate_resource(struct map_s *map, int resource);
