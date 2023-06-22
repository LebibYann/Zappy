/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_server_ai_receive_package
*/

#include "c_zappy_protocol_server_ai.h"

static char *get_second_parameter(char *line)
{
    size_t i = 0;
    size_t k = 0;

    while (line[i] == ' ' && line[i] != '\0' && line[i] != '\n')
        ++i;
    while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
        ++i;
    while (line[i] == ' ' && line[i] != '\0' && line[i] != '\n')
        ++i;
    if (line[i] == '\0' || line[i] == '\n')
        return (NULL);
    while (line[i + k] != '\0' && line[i + k] != '\n')
        ++k;
    return (strndup(&line[i], k));
}

static enum e_zp_command get_command_type(char *line)
{
    char *cmd = strtok(line, " ");

    for (size_t i = ZP_AI_START_CMD; i < ZP_TOTAL_AI_CMD; ++i) {
        if (strcmp(cmd, AI_CLI_COMMANDS->name) == 0) {
            free(cmd);
            return (i);
        }
    }
    free(cmd);
    return (ZP_END);
}

bool zp_server_ai_receive_package(t_zp_pending_data *zp_pending_d,
t_zp_ai_to_serv_data *zp_ais_data)
{
    char *line;

    if ((line = zp_getline_pending_data(zp_pending_d)) == NULL)
        return (false);
    zp_server_ai_clear_protocol_struct(zp_ais_data);
    zp_ais_data->cmd_type = get_command_type(line);
    if (zp_ais_data->cmd_type == ZP_END) {
        zp_server_ai_send_basic_package(zp_pending_d, RESPONSE_KO);
        free(line);
        return (false);
    }
    zp_ais_data->str = get_second_parameter(line);
    free(line);
    return (true);
}
