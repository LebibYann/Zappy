/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_strcat.c
*/

#include "str_split_lib_c.h"

char *split_strcat(char *dest, char const *src)
{
    return (split_strcpy(&dest[split_strlen(dest)], src));
}
