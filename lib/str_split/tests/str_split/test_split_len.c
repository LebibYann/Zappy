/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_len.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_len_1) {
    cr_assert_eq(split_len(NULL), 0);
}

Test (str_split, test_split_len_2) {
    char **split = split_str("Hello World !", ' ');
    cr_assert_eq(split_len(split), 3);
}

Test (str_split, test_split_len_3) {
    char **split = malloc(sizeof(char*));

    split[0] = NULL;
    cr_assert_eq(split_len(split), 0);
}
