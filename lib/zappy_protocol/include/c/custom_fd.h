/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-valentin1.maurel
** File description:
** custom_fd
*/

#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct s_custom_fd {
    size_t size;
    char *buf;
} t_custom_fd;

/**
 ** @brief Initialize the content size to 0 and buf to NULL.
 **
 ** @param c_fd
 */
void init_custom_fd(t_custom_fd *c_fd);

/**
 ** @brief Free buf and set it to NULL, and set size back to 0.
 **
 ** @param c_fd
 */
void clear_custom_fd(t_custom_fd *c_fd);

/**
 ** @brief Works as the syscall write work,
 ** it realloc the custom fd buf and copy buf in it,
 ** and increment the custom fd size by the size parameter.
 **
 ** @param c_fd
 ** @param buf
 ** @param size
 */
void write_in_custom_fd(t_custom_fd *c_fd, void *buf, size_t size);

/**
 ** @brief Works as the syscall read works,
 ** it removes from the buffer the bytes readed and return this size,
 ** and decrement the custom fd size by the size of the return.
 **
 ** @param c_fd
 ** @param buf
 ** @param size
 */
size_t read_in_custom_fd(t_custom_fd *c_fd, void *buf, size_t size);

/**
 ** @brief Return an allocated and initialized custom fd structure.
 **
 ** @return t_custom_fd*
 */
t_custom_fd *new_custom_fd(void);

/**
 ** @brief Free an allocated custom fd and it's buf if not NULL.
 **
 ** @return t_custom_fd*
 */
void delete_custom_fd(t_custom_fd *c_fd);

/**
 ** @brief Works as a getline return NULL even if there's content,
 ** this function only returns something if it can find a \\n or a \\0.
 **
 ** @param c_fd
 ** @return char*
 */
char *getline_in_custom_fd(t_custom_fd *c_fd);
