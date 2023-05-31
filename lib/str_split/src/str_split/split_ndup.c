/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_ndup.c
*/

#include "str_split.h"

char **split_ndup(char **split, size_t n)
{
    size_t i = 0;
    char **split_copy = malloc((split_nlen(split, n) + 1) * sizeof(char*));

    if (split_copy == NULL)
        return (NULL);
    while (split[i] != NULL && i < n) {
        split_copy[i] = split_strdup(split[i]);
        i++;
    }
    split_copy[i] = NULL;
    return (split_copy);
}
