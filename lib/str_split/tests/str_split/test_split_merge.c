/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_merge.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

Test (str_split, test_split_merge_1) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_merge(split, " ", -1);
    cr_assert_str_eq(str, "Hello World !");
    split_free(split);
    free(str);
}

Test (str_split, test_split_merge_2) {
    char **split = malloc(sizeof(char*));

    split[0] = NULL;
    char *str = split_merge(split, "yes!", -1);
    cr_assert_str_eq(str, "");
    split_free(split);
    free(str);
}

Test (str_split, test_split_merge_3) {
    char *str = split_merge(NULL, "yes!", -1);
    cr_assert_eq(str, NULL);
}

Test (str_split, test_split_merge_4) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_merge(split, "", -1);
    cr_assert_str_eq(str, "HelloWorld!");
    split_free(split);
    free(str);
}

Test (str_split, test_split_merge_5) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_merge(split, NULL, -1);
    cr_assert_str_eq(str, "HelloWorld!");
    split_free(split);
    free(str);
}


Test (str_split, test_split_merge_6) {
    char **split = split_str("Hello World !", ' ');
    char *str = split_merge(split, NULL, 2);
    cr_assert_str_eq(str, "HelloWorld");
    split_free(split);
    free(str);
}
