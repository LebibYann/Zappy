/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strncat.c
*/

#include "str_split_lib_c.h"

char *split_strncat(char *dest, char const *src, size_t n)
{
    size_t i = 0;

    dest = &dest[split_strnlen(dest, n)];
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return (dest);
}
