/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-valentin1.maurel
** File description:
** read_in_custom_fd
*/

#include "custom_fd.h"

size_t read_in_custom_fd(t_custom_fd *c_fd, void *buf, size_t size)
{
    size_t dumped_size = (size > c_fd->size) ? c_fd->size : size;

    memcpy(buf, c_fd->buf, dumped_size);
    if (dumped_size == c_fd->size) {
        clear_custom_fd(c_fd);
    } else {
        c_fd->size -= dumped_size;
        memmove(c_fd->buf, &(c_fd->buf)[dumped_size], c_fd->size);
        c_fd->buf = realloc(c_fd->buf, c_fd->size);
    }
    return (dumped_size);
}
