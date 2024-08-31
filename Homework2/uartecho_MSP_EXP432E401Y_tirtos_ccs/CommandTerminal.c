/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * =============== Main Thread ===============
 */

void *mainThread(void *arg0)
{
    char        input;

    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
    UART_Init();

    while (1) {
        UART_read(global.uart, &input, 1);

        UART_Input_Handler(input);

        if(input != 24 && input != 25 && input != 26 && input != 27){
            UART_write(global.uart, &input, 1);
        }
    }
}

/*
 * =============== Parser and Messages ========
 */

void HelpMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " -help  -> provides list of functions\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " -about -> provides developer and version info\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " -clear -> clears the terminal");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void AboutMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Developer: Nicholas Rethans\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Assignment #: 1 \r\n");
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Version %s.%s \r\n", Version, SubVersion);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Time: %s  Date: %s", __TIME__, __DATE__);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void ClearMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,"\033c");
    UART_write(global.uart, MsgBuffer,sizeof(MsgBuffer));
}

void PrintMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
}

void InvalidMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                     "\r\nInvalid Command\r\n");
    UART_Write_Protected(MsgBuffer);
}

bool MatchSubString(const char *msg1, const char *msg2) {
    while (*msg1 != '\0' && *msg2 != '\0' && *msg1 != ' ' && *msg2 != ' ') {
        if (*msg1 != *msg2) {
            return false;
        }
        msg1++;
        msg2++;
    }
    return *msg2 == '\0';
}

void MsgParser(char *msg) {
    if        (MatchSubString(msg, "-help" )) {
           HelpMsg();
    } else if (MatchSubString(msg, "-about")) {
          AboutMsg();
    } else if (MatchSubString(msg, "-clear")) {
          ClearMsg();
    } else if (MatchSubString(msg, "-print")) {
          PrintMsg();
    } else {
        InvalidMsg();
    }
}

