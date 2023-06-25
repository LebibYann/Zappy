/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** handle_unknown_clients
*/

#include "zappy_server.h"

static void send_gui_init(server_t *server, client_t *client)
{
    client_t *ai = NULL;
    int *items;
    t_zp_pending_data *pdata = &(client->data);

    zp_gui_send_package(pdata, SERVER_SENT,
        ZP_MSZ, server->map.w, server->map.h);
    zp_gui_send_package(pdata, SERVER_SENT, ZP_SGT, server->frequency);
    for (int y = 0; y < server->map.h && server->map.tiles != NULL; ++y) {
        for (int x = 0; x < server->map.w; ++x) {
            items = server->map.tiles[y][x].resources;
            zp_gui_send_package(pdata, SERVER_SENT, ZP_BCT, x, y,
                items[LINEMATE], items[DERAUMERE], items[SIBUR],
                items[MENDIANE], items[PHIRAS], items[THYSTAME]);
        }
    }
    for (size_t i = 0; server->teams[i] != NULL; ++i)
        zp_gui_send_package(pdata, SERVER_SENT, ZP_TNA, server->teams[i]);
    LIST_FOREACH(ai, &client->server->client_list, other_clients){
        if (ai->category == CATEGORY_AI)
            zp_gui_send_package(&client->data, SERVER_SENT,
            ZP_PNW, ai->fd, ai->pos.x, ai->pos.y,
            ai->orientation, ai->level, ai->team);
    }
}

static bool is_a_team_name_match(server_t *server, client_t *client, char *line,
size_t *team_position_in_list)
{
    for (size_t i = 0; server->teams[i] != NULL; ++i) {
        if (strcmp(line, server->teams[i]) == 0) {
            *team_position_in_list = i;
            return (true);
        }
    }
    zp_server_ai_send_basic_package(&(client->data), RESPONSE_KO);
    return (false);
}

static void send_valid_team_package(server_t *server, client_t *client)
{
    size_t i = 0;
    char tmp_buf[128];
    int count = get_client_count_in_team(client->team, &server->client_list);

    for (; server->teams[i] != NULL; ++i) {
        if (strcmp(client->team, server->teams[i]) == 0)
            break;
    }
    count = server->max_team_cli[i] - count;
    sprintf(tmp_buf, "%d\n%d %d\n", count, server->map.w, server->map.h);
    zp_write_data(&(client->data), tmp_buf, strlen(tmp_buf));
    zp_exchange_data(&(client->data), HANDLE_IGNORE, HANDLE_NO_WAIT);
}

static bool check_ai_team(server_t *server, client_t *client, char *line)
{
    size_t i = 0;
    int client_in_this_team;

    if (!is_a_team_name_match(server, client, line, &i))
        return (false);
    client_in_this_team = get_client_count_in_team(line, &server->client_list);
    if (client_in_this_team >= server->max_team_cli[i]) {
        zp_server_ai_send_basic_package(&(client->data), RESPONSE_KO);
        return (false);
    }
    configure_client_as_ai(client, server->teams[i]);
    return (true);
}

void handle_unknown_clients(server_t *server, client_t *client)
{
    char *line;

    zp_exchange_data(&(client->data), HANDLE_NO_WAIT, HANDLE_IGNORE);
    if ((line = zp_getline_pending_data(&(client->data))) == NULL)
        return;
    if (strcmp(line, "GRAPHIC\n") == 0) {
        free(line);
        configure_client_as_gui(client);
        send_gui_init(server, client);
        return;
    }
    line[strlen(line) - 1] = '\0';
    if (check_ai_team(server, client, line))
        send_valid_team_package(server, client);
    free(line);
}
