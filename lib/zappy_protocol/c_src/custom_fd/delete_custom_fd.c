/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-valentin1.maurel
** File description:
** delete_custom_fd
*/

#include "custom_fd.h"

void delete_custom_fd(t_custom_fd *c_fd)
{
    if (c_fd == NULL)
        return;
    clear_custom_fd(c_fd);
    free(c_fd);
}
