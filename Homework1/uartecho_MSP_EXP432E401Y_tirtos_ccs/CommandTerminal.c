/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * =============== Parser and Messages ========
 */

void HelpMsg(UART_Handle uart) {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  " -help  -> provides list of functions\r\n");
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  " -about -> provides developer and version info\r\n");
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  " -clear -> clears the terminal");
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(uart, MsgBuffer);
}

void AboutMsg(UART_Handle uart) {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  " Developer: Nicholas Rethans\r\n");
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  " Assignment #: 1 \r\n");
    UART_Write_Protected(uart, MsgBuffer);
    sprintf(MsgBuffer,                 " Version %s.%s \r\n", Version, SubVersion);
    UART_Write_Protected(uart, MsgBuffer);
    sprintf(MsgBuffer,                 " Time: %s  Date: %s", __TIME__, __DATE__);
    UART_Write_Protected(uart, MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(uart, MsgBuffer);
}

void ClearMsg(UART_Handle uart){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                 "\033c");
    UART_write(uart, MsgBuffer,sizeof(MsgBuffer));
}

void InvalidMsg(UART_Handle uart) {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                     "\r\nInvalid Command\r\n");
    UART_Write_Protected(uart, MsgBuffer);
}

void MsgParser(UART_Handle uart, char *msg) {

    if        (strcasecmp(msg, "-help" ) == 0) {
        HelpMsg   (uart);
    } else if (strcasecmp(msg, "-about") == 0) {
        AboutMsg  (uart);
    } else if (strcasecmp(msg, "-clear") == 0) {
        ClearMsg  (uart);
    } else {
        InvalidMsg(uart);
    }
}
