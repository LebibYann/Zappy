/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** str_split_lib_c.h
*/

#pragma once

#include <stdlib.h>

char *split_strdup(char const *src);

char *split_strndup(char const *src, size_t size);

size_t split_strlen(char const *str);

size_t split_strnlen(char const *str, size_t n);

char *split_strcpy(char *dest, char const *src);

char *split_strncpy(char *dest, char const *src, int n);

char *split_strcat(char *dest, char const *src);

char *split_strncat(char *dest, char const *src, size_t n);

void *split_memcpy(void *restrict dest, const void *restrict src, size_t n);

void *split_realloc(void *ptr, size_t old_size, size_t size);
