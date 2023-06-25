/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** connect_nbr
*/

#include "zappy_server.h"

void connect_nbr(server_t *sever, client_t *player, char *team)
{
    char response[16];
    int i;

    for (i = 0; strcmp(team, sever->teams[i]) != 0; i++);

    sprintf(response, "%d\n", sever->max_team_cli[i] -
        get_client_count_in_team(team, &sever->client_list));
    zp_server_ai_send_package(&player->data, response);
}
