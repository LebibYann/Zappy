/*
** EPITECH PROJECT, 2022
** DAY08
** File description:
** my_strndup
*/

#include "str_split_lib_c.h"

void *split_realloc(void *ptr, size_t old_size, size_t size)
{
    char *new_ptr;
    size_t ptr_size = old_size;

    new_ptr = malloc(size);
    if (ptr != NULL) {
        split_memcpy(new_ptr, ptr, (ptr_size < size) ? old_size : size);
        free(ptr);
    }
    return (new_ptr);
}
