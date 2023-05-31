/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_strncpy.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

void redirect_all_stdout(void);

Test (str_split, test_split_strncpy_1) {
    char *str = split_strdup("yooh");

    split_strncpy(str, "yeau", 3);
    cr_assert_str_eq(str, "yeah");
    free(str);
}

Test (str_split, test_split_strncpy_2) {
    char *str = split_strdup("ouch");

    split_strncpy(str, "yeah", 50);
    cr_assert_str_eq(str, "yeah");
    free(str);
}
