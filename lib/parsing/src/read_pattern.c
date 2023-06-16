/*
** EPITECH PROJECT, 2022
** read_pattern
** File description:
** The string reads the string until he
** corresponds to the pattern in parameters.
*/

#include "parsing.h"

bool read_pattern(char *str, int *i, const char *pattern)
{
    int start = *i;

    for (; pattern[*i - start] != '\0'; *i = *i + 1)
        if (pattern[*i - start] != str[*i]){
            *i = start;
            return (false);
        }
    return (true);
}
