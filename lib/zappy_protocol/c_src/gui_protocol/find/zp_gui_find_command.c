/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_find_command
*/

#include "c_zappy_protocol_gui.h"

const t_zp_gui_pair *zp_gui_find_command(char *cmd_line)
{
    char *cmd_name = strtok(cmd_line, " ");

    if (cmd_name == NULL)
        return (NULL);
    for (size_t i = 0; GUI_PAIR[i].cmd_type != ZP_END; ++i) {
        if (strcmp(cmd_name, GUI_PAIR[i].cmd_name) == 0) {
            free(cmd_name);
            return (&GUI_PAIR[i]);
        }
    }
    free(cmd_name);
    return (NULL);
}
