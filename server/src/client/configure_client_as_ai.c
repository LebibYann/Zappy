/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** configure_client_as_ai
*/

#include "zappy_client.h"
#include "zappy_pending_command.h"

void configure_client_as_ai(client_t *client, const char *team)
{
    client->category = CATEGORY_AI;
    client->level = 1;
    client->inventory[ELEM_FOOD] = 10;
    client->team = team;
}
