/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strncpy.c
*/

#include "str_split_lib_c.h"

char *split_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    if (i < n)
        dest[i] = '\0';
    return (dest);
}
