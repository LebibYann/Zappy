/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_dup.c
*/

#include "str_split.h"

char **split_dup(char **split)
{
    size_t i;
    size_t len = split_len(split);
    char **split_copy;

    i = 0;
    split_copy = malloc((len + 1) * sizeof(char*));
    while (i < len) {
        split_copy[i] = split_strdup(split[i]);
        i++;
    }
    split_copy[i] = NULL;
    return (split_copy);
}
