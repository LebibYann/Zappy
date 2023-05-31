/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_realloc.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

void redirect_all_stdout(void);

Test (str_split, test_split_realloc_1) {
    char *str = NULL;

    str = split_realloc(str, 0, 1);
    str[0] = 'a';
    free(str);
}

Test (str_split, test_split_realloc_2) {
    char *str = split_strdup("yo");

    str = split_realloc(str, 3, 4);
    str[2] = 'o';
    str[3] = '\0';
    free(str);
}
