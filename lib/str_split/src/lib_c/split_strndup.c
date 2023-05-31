/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strdup.c
*/

#include "str_split_lib_c.h"

char *split_strndup(char const *src, size_t size)
{
    char *new_str;
    int len = split_strnlen(src, size) + 1;

    new_str = malloc(len);
    new_str[0] = '\0';
    split_strncat(new_str, src, size);
    return (new_str);
}
