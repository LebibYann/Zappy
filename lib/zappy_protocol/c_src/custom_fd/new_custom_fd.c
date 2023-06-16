/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-valentin1.maurel
** File description:
** new_custom_fd
*/

#include "custom_fd.h"

t_custom_fd *new_custom_fd(void)
{
    t_custom_fd *c_fd = (t_custom_fd*) malloc(sizeof(t_custom_fd));

    init_custom_fd(c_fd);
    return (c_fd);
}
