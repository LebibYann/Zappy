/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** getline_in_custom_fd
*/

#include "custom_fd.h"

char *getline_in_custom_fd(t_custom_fd *c_fd)
{
    size_t i = 0;
    char *line;

    for (i = 0; i < c_fd->size &&
    c_fd->buf[i] != '\n' && c_fd->buf[i] != '\0'; ++i);
    if (i >= c_fd->size)
        return (NULL);
    line = malloc((i + 1) * sizeof(char));
    read_in_custom_fd(c_fd, line, i + 1);
    return (line);
}
