/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_dup.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_dup_1) {
    char **split = split_str("Hello World !", ' ');
    char **split_2 = split_dup(split);
    cr_assert_str_eq(split[0], split_2[0]);
    cr_assert_str_eq(split[1], split_2[1]);
    cr_assert_str_eq(split[2], split_2[2]);
    cr_assert_eq(split[3], split_2[3]);
    split_free(split);
    split_free(split_2);
}

Test (str_split, test_split_dup_2) {
    char **split = split_dup(NULL);
    cr_assert_eq(split[0], NULL);
    split_free(split);
}
