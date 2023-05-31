/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_print.c
*/

#include "str_split.h"

void split_print(char **splitted, char *separator)
{
    size_t i = 0;

    while (splitted != NULL && splitted[i] != NULL) {
        write(STDOUT_FILENO, splitted[i], split_strlen(splitted[i]));
        if (splitted[i + 1] != NULL)
            write(STDOUT_FILENO, separator, split_strlen(separator));
        ++i;
    }
    write(STDOUT_FILENO, "\n", 1);
}
