/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_insert.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_insert_1) {
    char **split = split_str("World !", ' ');
    split_insert(&split, "Hello", 0);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_insert_2) {
    char **split = split_str("Hello !", ' ');
    split_insert(&split, "World", 1);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_insert_3) {
    char **split = split_str("Hello World", ' ');
    split_insert(&split, "!", -1);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_str_eq(split[2], "!");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_insert_4) {
    char **split = split_str("Hello World", ' ');
    split_insert(&split, "!", -100);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_insert_5) {
    char **split = split_str("Hello World", ' ');
    split_insert(&split, "!", 100);

    cr_assert_str_eq(split[0], "Hello");
    cr_assert_str_eq(split[1], "World");
    cr_assert_eq(split[3], NULL);
    split_free(split);
}

Test (str_split, test_split_insert_6) {
    char **split = NULL;

    split_insert(&split, "!", 0);
    cr_assert_str_eq(split[0], "!");
    cr_assert_eq(split[1], NULL);
    split_free(split);
}
