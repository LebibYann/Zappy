/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** delete_client_struct
*/

#include "zappy_client.h"

void delete_client_struct(client_t *client)
{
    clear_client_struct(client);
    free(client);
}
