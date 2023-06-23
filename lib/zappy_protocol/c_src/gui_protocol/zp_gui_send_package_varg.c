/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_gui_send_package_varg
*/

#include "c_zappy_protocol_gui.h"

bool zp_gui_send_package_varg(t_zp_pending_data *pdata, enum e_sender sender,
enum e_zp_command cmd_type, va_list *args)
{
    char *data;
    const t_zp_gui_pair *pair = zp_gui_find_command_from_type(cmd_type);

    if (pair == NULL)
        return (false);
    data = pair->gui_generator_func(pair, args, sender);
    zp_write_data(pdata, data, strlen(data));
    free(data);
    zp_exchange_data(pdata, HANDLE_IGNORE, HANDLE_NO_WAIT);
    return (true);
}
