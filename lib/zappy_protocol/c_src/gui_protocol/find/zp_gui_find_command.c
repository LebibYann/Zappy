/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_find_command
*/

#include "c_zappy_protocol_gui.h"

const t_zp_gui_pair *zp_gui_find_command(char *cmd_line)
{
    size_t cmd_line_size;

    for (size_t i = 0; GUI_PAIR[i].cmd_type != ZP_END; ++i) {
        cmd_line_size = strlen(GUI_PAIR[i].cmd_name);
        if (strncmp(cmd_line, GUI_PAIR[i].cmd_name, cmd_line_size) == 0)
            return (&GUI_PAIR[i]);
    }
    return (NULL);
}
