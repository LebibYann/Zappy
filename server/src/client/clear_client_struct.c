/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** clear_client_struct
*/

#include "zappy_client.h"

void clear_client_struct(client_t *client)
{
    close(client->data.fd);
    zp_clear_pending_data_struct(&(client->data));
    memset(client, 0, sizeof(*client));
    client->category = CATEGORY_UNKNOWN;
}
