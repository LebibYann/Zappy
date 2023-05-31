/*
** EPITECH PROJECT, 2022
** MINI PRINTF
** File description:
** my_printf_test_no_format.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
