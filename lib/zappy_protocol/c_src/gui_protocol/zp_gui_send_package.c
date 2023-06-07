/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_gui_send_package
*/

#include "c_zappy_protocol_gui.h"

bool zp_gui_send_package(t_zp_pending_data *pdata, enum e_sender sender,
enum e_zp_command cmd_type, ...)
{
    char *data;
    va_list args;
    const t_zp_gui_pair *pair = zp_gui_find_command_from_type(cmd_type);

    if (pair == NULL)
        return (false);
    va_start(args, cmd_type);
    data = pair->gui_generator_func(pair, &args, sender);
    va_end(args);
    zp_write_data(pdata, data, strlen(data));
    free(data);
    return (true);
}
