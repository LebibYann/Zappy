/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Client
*/

#pragma once

#include "client.h"

#include <string>

class Client {
    public:
        Client(std::string adress, int port);
        ~Client();

        bool Connect(std::string adress, int port);
        void Disconnect();

        int FD() const;
        const char *Adress() const;
        int Port() const;
        bool Connected() const;
    private:
        int _fd;
        std::string _adress;
        int _port;
        bool _connected;
};
