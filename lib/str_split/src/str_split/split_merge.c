/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_merge.c
*/

#include "str_split.h"

static void write_into_char(char *target, size_t *i, char *src)
{
    size_t k = 0;

    while (src[k] != '\0') {
        target[*i] = src[k];
        k++;
        (*i)++;
    }
}

static size_t get_char_len(char **splitted, char *separation, ssize_t merge_len)
{
    size_t bytes = 0;
    ssize_t str_count = 0;

    while ((str_count < merge_len || merge_len == -1) &&
    splitted[str_count] != NULL) {
        bytes += split_strlen(splitted[str_count]);
        str_count++;
    }
    if (str_count > 0 && separation != NULL)
        bytes += split_strlen(separation) * (str_count - 1);
    return (bytes);
}

char *split_merge(char **splitted, char *separation, ssize_t merge_len)
{
    char *merge;
    size_t i = 0;
    size_t k = 0;
    size_t bytes;

    if (splitted == NULL)
        return (NULL);
    bytes = get_char_len(splitted, separation, merge_len);
    merge = malloc(bytes + 1);
    merge[bytes] = '\0';
    while (i < bytes) {
        write_into_char(merge, &i, splitted[k]);
        if (i < bytes && separation != NULL)
            write_into_char(merge, &i, separation);
        k++;
    }
    return (merge);
}
