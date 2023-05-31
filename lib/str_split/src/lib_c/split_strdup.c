/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strdup.c
*/

#include "str_split_lib_c.h"

char *split_strdup(char const *src)
{
    char *new_str;
    int len = split_strlen(src) + 1;

    new_str = malloc(len);
    new_str[0] = '\0';
    split_strcat(new_str, src);
    return (new_str);
}
