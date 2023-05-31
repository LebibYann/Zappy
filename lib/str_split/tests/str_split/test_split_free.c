/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_delete.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_delete_1) {
    split_free(NULL);
}

Test (str_split, test_split_delete_2) {
    char **split = split_str("Hello World !", ' ');
    split_free(split);
}

Test (str_split, test_split_delete_3) {
    char **split = malloc(sizeof(char*));

    split[0] = NULL;
    split_free(split);
}
