/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_insert.c
*/

#include "str_split.h"

static void apply_insert(char **split, char ***new_split,
char *new_char_copy, ssize_t pos)
{
    size_t k = 0;
    ssize_t i = 0;
    ssize_t len = split_len(split) + 1;

    pos = (pos == -1) ? (len - 1) : (pos);
    while (i < len) {
        if (i == pos) {
            (*new_split)[i] = new_char_copy;
            i++;
        }
        (*new_split)[i] = split[k];
        i++;
        k++;
    }
}

bool split_insert(char ***split, char *new_char, ssize_t pos)
{
    size_t len = split_len(*split) + 1;
    char **new_split = malloc((len + 1) * sizeof(char *));
    char *new_char_copy = split_strdup(new_char);

    new_split[len] = NULL;
    if (*split != NULL) {
        apply_insert(*split, &new_split, new_char_copy, pos);
        free(*split);
    } else
        new_split[0] = new_char_copy;
    (*split) = new_split;
    return (true);
}
