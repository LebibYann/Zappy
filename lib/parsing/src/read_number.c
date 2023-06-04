/*
** EPITECH PROJECT, 2022
** read_number
** File description:
** The function read the number in the string
** until find a no numerical character.
*/

#include "parsing.h"

int read_number(char *str, int *i, int *number)
{
    int start;
    bool sign = (str[*i] != '-');

    *number = 0;
    start = *i;
    if (str[*i] == '-' || str[*i] == '+')
        *i = *i + 1;
    for (; str[*i] >= '0' && str[*i] <= '9'; *i = *i + 1){
        if ((-214748364 - *number == 0 && str[*i] > 8 - sign)
            || (-214748364 - *number > 0)){
            *number = (-2147483648 + sign);
        } else
            *number = (*number * 10) - (str[*i] - '0');
    }
    if (sign)
        *number = *number * -1;
    return (*i - start);
}
