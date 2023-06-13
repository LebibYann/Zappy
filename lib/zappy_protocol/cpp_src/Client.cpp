/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(std::string adress, int port) : _fd(-1), _adress(NULL), _port(-1), _connected(false)
{
    Connect(adress, port);
}

Client::~Client()
{
    Disconnect();
}

bool Client::Connect(std::string adress, int port)
{
    if (_connected)
        Disconnect();
    if ((_fd = create_client(adress.c_str(), port)) == -1)
        return (false);
    _connected = true;
    _adress = adress;
    _port = port;
    return (true);
}

void Client::Disconnect()
{
    if (!_connected)
        return;
    close(_fd);
    _fd = -1;
    _adress = nullptr;
    _port = -1;
    _connected = false;
}

int Client::FD() const
{
    return (_fd);
}

const char *Client::Adress() const
{
    return (_adress.c_str());
}

int Client::Port() const
{
    return (_port);
}

bool Client::Connected() const
{
    return (_connected);
}