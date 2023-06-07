/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_single_str_parser
*/

#include "c_zappy_protocol_gui.h"

int zp_gui_single_str_parser(char *cmd_line, t_zp_gui_protocol *pkg)
{
    char *param = strtok(cmd_line, " ");

    if (param == NULL)
        return (-1);
    free(param);
    zp_gui_clear_protocol_struct(pkg);
    if ((param = strtok(NULL, " ")) != NULL)
        pkg->str = param;
    return (0);
}
