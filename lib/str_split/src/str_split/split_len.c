/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_len.c
*/

#include "str_split.h"

size_t split_len(char **split)
{
    size_t len;

    if (split == NULL)
        return (0);
    len = 0;
    while (split[len] != NULL)
        len++;
    return (len);
}
