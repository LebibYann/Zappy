/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_remove.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_remove_1) {
    char **split = split_str("Hello World !", ' ');
    split_remove(&split, 1);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "!");
    cr_assert_eq(split[2], NULL);
    split_free(split);
}

Test (str_split, test_split_remove_2) {
    char **split = split_str("Hello World !", ' ');
    split_remove(&split, 20);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_remove_3) {
    char **split = split_str("Hello World !", ' ');
    split_remove(&split, -1);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_eq(split[2], NULL);
    split_free(split);
}

Test (str_split, test_split_remove_4) {
    char **split = split_str("Hello World !", ' ');
    split_remove(&split, -20);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}
