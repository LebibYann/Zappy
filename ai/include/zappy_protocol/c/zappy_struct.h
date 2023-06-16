/*
** EPITECH PROJECT, 2023
** zappy_protocol
** File description:
** zappy_struct
*/

#pragma once

#include "custom_fd.h"

#define BUFSIZE 8192

typedef struct s_zp_pending_data {
    int fd;
    bool disconnected;
    t_custom_fd c_rfd;
    t_custom_fd c_wfd;
} t_zp_pending_data;

typedef struct s_coords {
    int x;
    int y;
    int l;
} t_coords;

typedef enum e_zp_command {
    ZP_END = -1,
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
    ZP_GRAPHIC,
    ZP_MSZ,
    ZP_BCT,
    ZP_MCT,
    ZP_TNA,
    ZP_PNW,
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

typedef struct s_zp_ai_to_serv_data {
    enum e_zp_command cmd_type;
    char *str;
} t_zp_ai_to_serv_data;

typedef struct s_zp_gui_protocol {
    enum e_zp_command cmd_type;
    int nbr_args;
    int *args;
    char *str;
} t_zp_gui_protocol;

#define TOTAL_ELEVATION 8

typedef enum e_elemOnTile {
    ELEM_PLAYER,
    ELEM_FOOD,
    ELEM_LINEMATE,
    ELEM_DERAUMERE,
    ELEM_SIBUR,
    ELEM_MENDIANE,
    ELEM_PHIRAS,
    ELEM_THYSTAME,
    TOTAL_ELEM_ON_TILE
} t_elemOnTile;

static const int
ELEVATION_REQUIREMENT[TOTAL_ELEVATION][TOTAL_ELEM_ON_TILE] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0},
    {2, 0, 1, 1, 1, 0, 0, 0},
    {2, 0, 2, 0, 1, 0, 2, 0},
    {4, 0, 1, 1, 2, 0, 1, 0},
    {4, 0, 1, 2, 1, 3, 0, 0},
    {6, 0, 1, 2, 3, 0, 1, 0},
    {6, 0, 2, 2, 2, 2, 2, 4}
};

typedef struct s_inventoryPair {
    const char *item_name;
    enum e_elemOnTile item_type;
} t_inventoryPair;

/* The player doesn't exist in the inventory,
it's here only to avoid potential bug */
static const t_inventoryPair
INVENTORY_PAIR[TOTAL_ELEM_ON_TILE] = {
    {"player", ELEM_PLAYER},
    {"food", ELEM_FOOD},
    {"linemate", ELEM_LINEMATE},
    {"deraumere", ELEM_DERAUMERE},
    {"sibur", ELEM_SIBUR},
    {"mendiane", ELEM_MENDIANE},
    {"phiras", ELEM_PHIRAS},
    {"thystame", ELEM_THYSTAME},
};
