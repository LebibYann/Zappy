/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_str.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_str_1) {
    char **split = split_str("Hello World !", ' ');

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_str_2) {
    char **split = split_str("   Hello   World !   ", ' ');

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_str_3) {
    char **split = split_str("", ' ');

    cr_assert_eq(split[0], NULL);
    split_free(split);
}

Test (str_split, test_split_str_4) {
    char **split = split_str("   Hello   World !   ", 'o');

    cr_assert_str_eq(split[0], "   Hell");
    cr_assert_str_eq(split[1], "   W");
    cr_assert_str_eq(split[2], "rld !   ");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_str_5) {
    char **split = split_str("Hello World!", 'q');

    cr_assert_str_eq(split[0], "Hello World!");
    cr_assert_eq(split[1], NULL);
    split_free(split);
}
