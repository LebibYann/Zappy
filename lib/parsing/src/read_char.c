/*
** EPITECH PROJECT, 2022
** read_char
** File description:
** The function reads the character in parameters
** until find another characters.
*/

#include "parsing.h"

int read_char(char *str, int *i, char c)
{
    int start;

    start = *i;
    for (; str[*i] == c; *i = *i + 1);
    return (*i - start);
}
