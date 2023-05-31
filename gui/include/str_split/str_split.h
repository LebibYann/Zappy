/*
** EPITECH PROJECT, 2022
** STR_SPLIT_LIB
** File description:
** strsplit.h
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "str_split_lib_c.h"

/**
 * @brief Free a (char**)
 *
 * @param splitted The (char**) you want to free.
 * Must have NULL terminator at his end
 */
void split_free(char **splitted);


/**
 * @brief Print in STDOUT the (char**) given in splitted
 *
 * @param splitted The (char**) you want to print.
 * @param separator Between each occurrence of the (char**),
 * you will be able to add an intermediary str of your choice.
 */
void split_print(char **splitted, char *separator);


/**
 * @brief Takes a (char**) and give back his length.
 *
 * @param split (char**) with a NULL pointer as terminator.
 * @return size_t len of the splitted str.
 */
size_t split_len(char **split);


/**
 * @brief To add a (char*) in a (char**) variable.
 *
 * @param split The adress of the (char**) you want to use as target.
 * @param new_char The new element you want to add in the (char**).
 * The function will copy the (char*) given in this parameter.
 * @param pos The postition it will be added,
 * -1 means to add it at the end of the (char**).
 *
 * @return true on success,
 * false on failure. (On failure the split var will be not modified).
 */
bool split_insert(char	***split, char *new_char, ssize_t pos);


/*
** @brief Remove an element of the (char**) and return it
**
** @param split The adress of the (char**) you want to use as target.
** @param pos Position of the element.
** @return char*
*/
char *split_pop(char ***split, ssize_t pos);

/**
 * @brief To remove a (char*) from a (char**) variable.
 *
 * @param split The adress of the (char**) you want to use as target.
 * @param pos The postition of the element you want to remove.
 * -1 means to remove the last occurence of the (char**).
 *
 * @return true on success, false on failure.
 */
void split_remove(char ***split, ssize_t pos);


/**
 * @brief Split a (char*) element with a given parser.
 * The parser is not kept in the (char**).
 * The (char**) is ended with a NULL pointer.
 *
 * @param str The (char*) you want to split.
 * @param parser To indicate which character trigger a split in the (char**)
 *
 * @return char** on success,
 * NULL if the memory allocation went wrong.
 */
char **split_str(char *str, char parser);


/**
 * @brief Takes a (char**) and merge it into a single (char*).
 * The separation parameter is added between each element of the (char**)
 * except at the start and the end.
 *
 * @param splitted The source (char**).
 * @param separation What you want to add between two element of the (char**)
 * @param merge_len How many element of the (char**) you want to merge,
 * -1 means all.
 *
 * @return char* on success,
 * NULL if the memory allocation went wrong.
 */
char *split_merge(char **splitted, char *separation, ssize_t merge_len);


/**
 * @brief Create a copy of the given split
 * and return the pointer of this copy.
 *
 * @param split the (char**) you want to copy.
 *
 * @return char** A copy on success,
 * NULL on failure.
 */
char **split_dup(char**split);


/**
** @brief Create a copy of the given split until reach n or NULL,
** and return the pointer of this copy.
**
** @param split The (char**) you want to copy.
** @param n The len you want to copy
** @return char**
*/
char **split_ndup(char **split, size_t n);


/**
** @brief Takes a (char**) and return its length
** or n if (char**) is longer than n.
**
** @param split (char**) with a NULL pointer as terminator.
** @param n The max size you want
** @return size_t
*/
size_t split_nlen(char **split, size_t n);
