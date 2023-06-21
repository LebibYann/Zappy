/*
** EPITECH PROJECT, 2023
** ai
** File description:
** strIsInt
*/

#include "CheckFunction.hpp"

bool strIsInt(const std::string &str)
{
    size_t i = 0;

    for (; i < str.length() && (str[i] == '-' || str[i] == '+'); ++i);
    if (i >= str.length())
        return (false);
    for (; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return (false);
    }
    return (strIsDigit(&(str.c_str())[i]));
}
