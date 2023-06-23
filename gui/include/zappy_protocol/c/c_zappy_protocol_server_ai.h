/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** c_zappy_protocol_server_ai
*/

#pragma once

#include "zappy_struct.h"
#include "c_zappy_protocol.h"

typedef struct aiCommand_s {
    enum e_zp_command id;
    const char *name;
    int tick;
} aiCommand_t;

typedef enum AIResponse_e {
    RESPONSE_DISCONNECTION = -2,
    RESPONSE_NOTHING,
    RESPONSE_OK,
    RESPONSE_KO,
    RESPONSE_DEAD,
    RESPONSE_MESSAGE,
    RESPONSE_EJECT,
    RESPONSE_OTHER,
    RESPONSE_TOTAL
} AIResponse_t;

extern const aiCommand_t AI_CLI_COMMANDS[];

#ifdef __cplusplus
extern "C" {
#endif

/**
 ** @brief This function let you easily send back basic response such as:
 ** ok ko dead. All other kind of response will be ignored by the function
 **
 ** @param zp_pending_d
 ** @param response
 */
void zp_server_ai_send_basic_package(t_zp_pending_data *zp_pending_d,
enum AIResponse_e response);

/**
 ** @brief
 **
 ** @param zp_pending_d
 ** @param zp_ais_data
 ** @return true
 ** @return false
 */
bool zp_server_ai_receive_package(t_zp_pending_data *zp_pending_d,
t_zp_ai_to_serv_data *zp_ais_data);

void zp_server_ai_clear_protocol_struct(t_zp_ai_to_serv_data *zp_ais_data);

void zp_server_ai_delete_protocol_struct(t_zp_ai_to_serv_data *zp_ais_data);

void zp_server_ai_init_protocol_struct(t_zp_ai_to_serv_data *zp_ais_data);

t_zp_ai_to_serv_data *zp_server_ai_new_protocol_struct(void);

#ifdef __cplusplus
}
#endif
