/*
** EPITECH PROJECT, 2023
** server
** File description:
** init_client_struct
*/

#include "zappy_client.h"

void init_client_struct(client_t *client, int fd)
{
    memset(client, 0, sizeof(*client));
    zp_init_pending_data_struct(&(client->data), fd);
    client->fd = fd;
    client->category = CATEGORY_UNKNOWN;
    LIST_INIT(&(client->pending_list));
}
