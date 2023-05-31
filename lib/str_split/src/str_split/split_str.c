/*
** EPITECH PROJECT, 2022
** MY_LS
** File description:
** split_str.c
*/

#include "str_split.h"


static size_t count_bloc(char *str, char parser)
{
    bool detect;
    size_t i;
    size_t occurence;

    i = 0;
    detect = true;
    occurence = 1;
    while (str[i] != '\0') {
        if (str[i] == parser)
            detect = true;
        if (str[i] != parser && detect) {
            detect = false;
            occurence++;
        }
        i++;
    }
    return (occurence);
}

static char *get_element(char *str, char parser, size_t *k)
{
    char *element;
    size_t start;

    while (str[*k] == parser)
        (*k)++;
    start = *k;
    while (str[*k] != parser && str[*k] != '\0')
        (*k)++;
    element = split_strndup(&str[start], (*k) - start);
    return (element);
}

char **split_str(char *str, char parser)
{
    char **splitted;
    size_t k = 0;
    size_t bloc_count = count_bloc(str, parser);

    splitted = malloc(sizeof(char *) * bloc_count);
    bloc_count--;
    splitted[bloc_count] = NULL;
    for (size_t i = 0; i < bloc_count; i++)
        splitted[i] = get_element(str, parser, &k);
    return (splitted);
}
