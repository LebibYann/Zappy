/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zp_gui_int_end_str_generator
*/

#include "c_zappy_protocol_gui.h"

static char *append_end_str(char *buf, char *str)
{
    buf = realloc(buf, strlen(buf) + strlen(str) + 2);
    strcat(buf, str);
    strcat(buf, "\n");
    return (buf);
}

char *zp_gui_int_end_str_generator(const t_zp_gui_pair *pair,
va_list *args, enum e_sender sender)
{
    size_t full_size;
    char *buf = strdup(pair->cmd_name);
    char *buf2;

    for (int i = 0; i < pair->nbr_param[sender]; ++i) {
        full_size = strlen(buf) + 17;
        buf = realloc(buf, full_size);
        buf2 = malloc(full_size);
        strcat(buf, " %d");
        sprintf(buf2, buf, va_arg(*args, int));
        strcpy(buf, buf2);
        free(buf2);
    }
    return (append_end_str(buf, va_arg(*args, char*)));
}
