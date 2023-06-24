/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** c_zappy_protocol_gui
*/

#pragma once

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#include "zappy_struct.h"
#include "c_zappy_protocol.h"

typedef enum e_sender {
    SERVER_SENT,
    CLIENT_SENT,
    TOTAL_SENDER
} t_sender;

typedef struct s_zp_gui_pair {
    enum e_zp_command cmd_type;
    const char *cmd_name;
    int nbr_param[TOTAL_SENDER];
    int (*gui_parser_func)(char *cmd_line, t_zp_gui_protocol *pkg);
    char *(*gui_generator_func)(const struct s_zp_gui_pair *pair,
        va_list *args, enum e_sender sender);
} t_zp_gui_pair;

extern const t_zp_gui_pair GUI_PAIR[];

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ** @brief You should call zp_exchange_data() after using this function.
 ** Transform the cmd_type and ... (command arguments)
 ** into a correctly formed command ready to be sent.
 ** (use zp_exchange_data() to send it)
 **
 ** @param pdata
 ** @param sender From where you send it.
 ** @param cmd_type
 ** @param ... The arguments of the command
 ** @return true on sucess false if the cmd_type is invalid.
 */
bool zp_gui_send_package(t_zp_pending_data *pdata, enum e_sender sender,
enum e_zp_command cmd_type, ...);

/**
 ** @brief You should call zp_exchange_data() after using this function.
 ** Transform the cmd_type and args
 ** into a correctly formed command ready to be sent.
 ** (use zp_exchange_data() to send it)
 **
 ** @param pdata
 ** @param sender From where you send it.
 ** @param cmd_type
 ** @param ... The arguments of the command
 ** @return true on sucess false if the cmd_type is invalid.
 */
bool zp_gui_send_package_varg(t_zp_pending_data *pdata, enum e_sender sender,
enum e_zp_command cmd_type, va_list *args);

/**
 ** @brief You should call zp_exchange_data() before using this function.
 ** Parse the data of the received command if there's one.
 **
 ** @param pdata
 ** @param pkg
 ** @param expected_sender Who must have sent it to you.
 ** @return int 0 on success, -1 if no data has been received,
 ** -2 if the command receive is unknown, -3 if parameters are invalid.
 */
int zp_gui_receive_package(t_zp_pending_data *pdata, t_zp_gui_protocol *pkg,
enum e_sender expected_sender, bool wait);


// Struct

void zp_gui_clear_protocol_struct(t_zp_gui_protocol *gui_protocol);

void zp_gui_init_protocol_struct(t_zp_gui_protocol *gui_protocol);

t_zp_gui_protocol *zp_gui_new_protocol_struct(void);

void zp_gui_delete_protocol_struct(t_zp_gui_protocol *gui_protocol);


// Find

const t_zp_gui_pair *zp_gui_find_command(char *cmd_line);

const t_zp_gui_pair *zp_gui_find_command_from_type(enum e_zp_command cmd_type);


// Parsers

int zp_gui_default_parser(char *cmd_line, t_zp_gui_protocol *pkg);

int zp_gui_int_end_str_parser(char *cmd_line, t_zp_gui_protocol *pkg);

int zp_gui_single_str_parser(char *cmd_line, t_zp_gui_protocol *pkg);


// Generators

char *zp_gui_default_generator(const t_zp_gui_pair *pair,
va_list *args, enum e_sender sender);

char *zp_gui_int_end_str_generator(const t_zp_gui_pair *pair,
va_list *args, enum e_sender sender);

#ifdef __cplusplus
}
#endif
