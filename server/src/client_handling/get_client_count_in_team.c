/*
** EPITECH PROJECT, 2023
** server
** File description:
** get_client_count_in_team
*/

#include "zappy_server.h"

int get_client_count_in_team(const char *team,
struct client_list_s *client_list)
{
    int count = 0;
    client_t *client;

    LIST_FOREACH(client, client_list, other_clients) {
        count += (client->category == CATEGORY_AI &&
            strcmp(client->team, team) == 0);
    }
    return (count);
}
