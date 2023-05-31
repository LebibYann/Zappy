/*
** EPITECH PROJECT, 2022
** MY_LS
** File description:
** split_remove.c
*/

#include "str_split.h"

void split_remove(char ***split, ssize_t pos)
{
    char *pop = split_pop(split, pos);

    if (pop != NULL)
        free(pop);
}
