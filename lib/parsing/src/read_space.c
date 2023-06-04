/*
** EPITECH PROJECT, 2022
** read_space
** File description:
** The function read the spaces until find another character.
*/

#include "parsing.h"

int read_space(char *str, int *i)
{
    int start;

    start = *i;
    for (; str[*i] == ' ' || str[*i] == '\t'; *i = *i + 1);
    if (start == *i)
        return (0);
    return (*i - start);
}
