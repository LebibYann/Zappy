/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_nlen.c
*/

#include "str_split.h"

size_t split_nlen(char **split, size_t n)
{
    size_t len = 0;

    if (split == NULL)
        return (0);
    while (split[len] != NULL && len < n)
        len++;
    return (len);
}
