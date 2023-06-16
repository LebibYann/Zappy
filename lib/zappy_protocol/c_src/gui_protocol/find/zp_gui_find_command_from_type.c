/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_find_command_from_type
*/

#include "c_zappy_protocol_gui.h"

const t_zp_gui_pair *zp_gui_find_command_from_type(enum e_zp_command cmd_type)
{
    for (size_t i = 0; GUI_PAIR[i].cmd_type != ZP_END; ++i) {
        if (GUI_PAIR[i].cmd_type == cmd_type)
            return (&GUI_PAIR[i]);
    }
    return (NULL);
}
