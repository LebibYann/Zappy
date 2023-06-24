/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zappy_incantations
*/

#pragma once

#include "zappy_resources.h"

typedef struct incantations_s {
    int level;
    int prerequisites[RESOURCES_COUNT];
}   incantations_t;

static const incantations_t INCANTATIONS[] = {
    {1, {1, 1, 0, 0, 0, 0, 0}},
    {2, {2, 1, 1, 1, 0, 0, 0}},
    {3, {2, 2, 0, 1, 0, 2, 0}},
    {4, {4, 1, 1, 2, 0, 1, 0}},
    {5, {4, 1, 2, 1, 3, 0, 0}},
    {6, {6, 1, 2, 3, 0, 1, 0}},
    {7, {6, 2, 2, 2, 2, 2, 1}}
};
