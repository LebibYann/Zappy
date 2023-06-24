/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-ethan.nguyen
** File description:
** ZappyProtocolGUI
*/

#include "ZappyProtocolGUI.hpp"

ZappyProtocolGUI::ZappyProtocolGUI(int fd) :
ZappyProtocol::ZappyProtocol(fd)
{
}

ZappyProtocolGUI::~ZappyProtocolGUI()
{
    ZappyProtocol::~ZappyProtocol();
}

bool ZappyProtocolGUI::sendPackage(enum e_zp_command cmd_type, ...)
{
    bool out;
    va_list args;

    va_start(args, cmd_type);
    out = zp_gui_send_package_varg(&(this->_data), CLIENT_SENT, cmd_type, &args);
    va_end(args);
    return (out);
}

int ZappyProtocolGUI::receivePackage(t_zp_guiProtocol &pkg, bool wait)
{
    int out;
    t_zp_gui_protocol cPkg;

    zp_gui_init_protocol_struct(&cPkg);
    out = zp_gui_receive_package(&(this->_data), &cPkg, SERVER_SENT, wait);
    if (out < 0) {
        zp_gui_clear_protocol_struct(&cPkg);
        return (out);
    }
    pkg.cmdType = cPkg.cmd_type;
    pkg.args.resize(cPkg.nbr_args);
    for (int i = 0; i < cPkg.nbr_args; ++i)
        pkg.args[i] = cPkg.args[i];
    if (!(pkg.noString = (cPkg.str == NULL)))
        pkg.str = cPkg.str;
    zp_gui_clear_protocol_struct(&cPkg);
    return (out);
}