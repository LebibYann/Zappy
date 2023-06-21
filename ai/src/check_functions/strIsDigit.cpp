/*
** EPITECH PROJECT, 2023
** ai
** File description:
** strIsDigit
*/

#include "CheckFunction.hpp"

bool strIsDigit(const std::string &str)
{
    for (size_t i = 0; i < strlen(str.c_str()); ++i) {
        if (!isdigit(str[i]))
            return (false);
    }
    return (true);
}
