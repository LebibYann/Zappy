/*
** EPITECH PROJECT, 2022
** DAY04 TASK03
** File description:
** TASK03 my_strlen
*/

#include "str_split_lib_c.h"

size_t split_strnlen(char const *str, size_t n)
{
    size_t len = 0;

    while (len < n && str[len] != '\0')
        len++;
    return (len);
}
