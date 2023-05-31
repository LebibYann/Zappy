/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strcpy.c
*/

#include "str_split_lib_c.h"

char *split_strcpy(char *dest, char const *src)
{
    int i;

    i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (&dest[0]);
}
