/*
** EPITECH PROJECT, 2023
** ai
** File description:
** strIsNum
*/

#include "CheckFunction.hpp"

bool strIsNum(std::string str)
{
    size_t i = 0;
    bool point_passed = false;

    for (; i < str.length() && (str[i] == '-' || str[i] == '+'); ++i);
    if (i >= str.length())
        return (false);
    while (i < str.length()) {
        if (!point_passed && str[i] == '.') {
            ++i;
            point_passed = true;
        }
        if (!isdigit(str[i]))
            return (false);
        ++i;
    }
    return (true);
}
