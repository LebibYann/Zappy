/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_print.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

void redirect_all_stdout(void);

Test (str_split, test_split_print_1, .init = redirect_all_stdout) {
    char **split = split_str("Hello World !", ' ');

    split_print(split, " ");
    cr_assert_stdout_eq_str("Hello World !\n");
    split_free(split);
}

Test (str_split, test_split_print_2, .init = redirect_all_stdout) {
    split_print(NULL, " ");
    cr_assert_stdout_eq_str("\n");
}

Test (str_split, test_split_print_3, .init = redirect_all_stdout) {
    char **split = split_str("Hello World !", ' ');

    split_print(split, "Yes!");
    cr_assert_stdout_eq_str("HelloYes!WorldYes!!\n");
    split_free(split);
}
