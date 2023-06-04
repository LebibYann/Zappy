/*
** EPITECH PROJECT, 2022
** read_string
** File description:
** The function reads the string until finding a token.
*/

#include "parsing.h"

static bool is_token(char c, char *tokens)
{
    int i;

    if (c == '\0')
        return (true);
    for (i = 0; tokens[i] != '\0'; i++)
        if (tokens[i] == c)
            return (true);
    return (false);
}

int read_string(char *str, int *i, char **word, char *tokens)
{
    int start;

    start = *i;
    for (; !is_token(str[*i], tokens); *i = *i + 1);
    if (*i - start == 0)
        return (0);
    if ((*word = malloc((*i - start + 1) * sizeof(char))) == NULL)
        return (-1);
    for (*i = start; !is_token(str[*i], tokens); *i = *i + 1)
        (*word)[*i - start] = str[*i];
    (*word)[*i - start] = '\0';
    return (*i - start);
}
