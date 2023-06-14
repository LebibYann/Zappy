/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-valentin1.maurel
** File description:
** write_in_custom_fd
*/

#include "custom_fd.h"

void write_in_custom_fd(t_custom_fd *c_fd, void *buf, size_t size)
{
    c_fd->buf = (char*) realloc(c_fd->buf, c_fd->size + size);
    memcpy(&c_fd->buf[c_fd->size], buf, size);
    c_fd->size += size;
}
