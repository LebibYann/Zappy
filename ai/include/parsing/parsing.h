/*
** EPITECH PROJECT, 2023
** parsing
** File description:
** The header contains the protype of all the parsing functions.
*/

#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

int read_space(char *str, int *i);
int read_char(char *str, int *i, char c);
int read_string(char *str, int *i, char **word, char *tokens);
bool read_pattern(char *str, int *i, const char *pattern);
int read_number(char *str, int *i, int *number);
