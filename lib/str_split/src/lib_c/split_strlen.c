/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strlen.c
*/

#include "str_split_lib_c.h"

size_t split_strlen(char const *str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;
    return (len);
}
