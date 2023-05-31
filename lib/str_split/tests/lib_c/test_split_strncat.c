/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** test_split_strncat.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "str_split.h"

void redirect_all_stdout(void);

Test (str_split, test_split_strncat_1) {
    char *str = split_strdup("yooh");

    str[0] = '\0';
    split_strncat(str, "yeau", 3);
    cr_assert_str_eq(str, "yea");
    free(str);
}

Test (str_split, test_split_strncat_2) {
    char *str = split_strdup("yooh");

    str[0] = '\0';
    split_strncat(str, "yeah", 50);
    cr_assert_str_eq(str, "yeah");
    free(str);
}
