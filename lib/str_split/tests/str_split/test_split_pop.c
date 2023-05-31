/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_pop.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_pop_1) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_pop(&split, 1);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "!");
    cr_assert_eq(split[2], NULL);
    cr_assert_str_eq(str, "World");
    split_free(split);
    free(str);
}

Test (str_split, test_split_pop_2) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_pop(&split, 20);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    cr_assert_eq(str, NULL);
    split_free(split);
}

Test (str_split, test_split_pop_3) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_pop(&split, -1);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_eq(split[2], NULL);
    cr_assert_str_eq(str, "!");
    split_free(split);
}

Test (str_split, test_split_pop_4) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_pop(&split, -20);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    cr_assert_eq(str, NULL);
    split_free(split);
}
