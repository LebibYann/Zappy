/*
** EPITECH PROJECT, 2022
** STR_SPLIT LIB
** File description:
** split_memcpy.c
*/

#include "str_split_lib_c.h"

void *split_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    char *cdest = dest;
    const char *csrc = src;

    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
    return (cdest);
}
