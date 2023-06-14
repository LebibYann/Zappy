/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** zp_gui_default_generator
*/

#include "c_zappy_protocol_gui.h"

char *zp_gui_default_generator(const t_zp_gui_pair *pair,
va_list *args, enum e_sender sender)
{
    size_t full_size;
    char *buf = strdup(pair->cmd_name);
    char *buf2;

    for (int i = 0; i < pair->nbr_param[sender]; ++i) {
        full_size = strlen(buf) + 17;
        buf = (char*) realloc(buf, full_size);
        buf2 = (char*) malloc(full_size);
        strcat(buf, " %d");
        sprintf(buf2, buf, va_arg(*args, int));
        strcpy(buf, buf2);
        free(buf2);
    }
    buf = (char*) realloc(buf, strlen(buf) + 2);
    strcat(buf, "\n");
    return (buf);
}
