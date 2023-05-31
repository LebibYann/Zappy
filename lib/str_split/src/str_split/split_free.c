/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_free.c
*/

#include "str_split.h"

void split_free(char **splitted)
{
    size_t i;

    if (splitted == NULL)
        return;
    i = 0;
    while (splitted[i] != NULL) {
        free(splitted[i]);
        ++i;
    }
    free(splitted);
}
