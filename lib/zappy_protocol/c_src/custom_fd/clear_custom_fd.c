/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-valentin1.maurel
** File description:
** clear_custom_fd
*/

#include "custom_fd.h"

void clear_custom_fd(t_custom_fd *c_fd)
{
    c_fd->size = 0;
    if (c_fd->buf != NULL) {
        free(c_fd->buf);
        c_fd->buf = NULL;
    }
}
