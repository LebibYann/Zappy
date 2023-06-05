/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zappy_struct
*/

#pragma once

#define BUF_SIZE 8192

typedef enum e_zp_command {
    // AI
    ZP_FORWARD,
    ZP_RIGHT,
    ZP_LEFT,
    ZP_LOOK,
    ZP_INVENTORY,
    ZP_BROADCAST,
    ZP_CONNECT_NBR,
    ZP_FORK,
    ZP_EJECT,
    ZP_DEAD,
    ZP_TAKE_OBJ,
    ZP_SET_OBJ,
    ZP_INCANTATION,

    // GUI
    ZP_MSZ,
    ZP_BCT,
    ZP_MCT,
    ZP_TNA,
    ZP_PPO,
    ZP_PLV,
    ZP_PIN,
    ZP_PEX,
    ZP_PBC,
    ZP_PIC,
    ZP_PIE,
    ZP_PFK,
    ZP_PDR,
    ZP_PGT,
    ZP_PDI,
    ZP_ENW,
    ZP_EBO,
    ZP_EDI,
    ZP_SGT,
    ZP_SST,
    ZP_SEG,
    ZP_SMG,
    ZP_SUC,
    ZP_SBP,
    ZP_TOTAL_CMD
} t_zp_command;
