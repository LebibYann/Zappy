/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** new_client_struct
*/

#include "zappy_client.h"

client_t *new_client_struct(int fd)
{
    client_t *client = malloc(sizeof(*client));

    init_client_struct(client, fd);
    return (client);
}
