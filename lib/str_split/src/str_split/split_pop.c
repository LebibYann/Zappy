/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_pop.c
*/

#include "str_split.h"

char *split_pop(char ***split, ssize_t pos)
{
    char *pop = NULL;
    ssize_t n = split_len(*split);

    if (pos >= n || pos < -n)
        return (NULL);
    if (pos < 0)
        pos = n + pos;
    pop = (*split)[pos];
    for (; pos < n; pos++)
        (*split)[pos] = (*split)[pos + 1];
    *split = split_realloc(*split, (n + 1) * sizeof(char*), n * sizeof(char*));
    return (pop);
}
