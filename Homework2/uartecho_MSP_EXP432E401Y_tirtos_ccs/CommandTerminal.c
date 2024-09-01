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
 * =============== First Layer Parser Functions & Messages ========
 */

void HelpMsg() {
    char *SubStrPtr;
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    SubStrPtr = NextSubString(global.MsgBuff, false);
    if (SubStrPtr != NULL){
        if        (MatchSubString(SubStrPtr,"-help") || MatchSubString(SubStrPtr,"help")){
            HelpHelpMsg();
        } else if (MatchSubString(SubStrPtr,"-about") || MatchSubString(SubStrPtr,"about")){
            HelpAboutMsg();
        } else if (MatchSubString(SubStrPtr,"-print") || MatchSubString(SubStrPtr,"print")){
            HelpPrintMsg();
        } else if (MatchSubString(SubStrPtr,"-clear") || MatchSubString(SubStrPtr,"clear")){
            HelpClearMsg();
        } else {
            InvalidMsg();
        }

    } else {
        strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer,                  " -help  -> provides list of function descriptions\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer,                  " -about -> provides developer and version info\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer,                  " -print -> prints message after -print \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer,                  " -clear -> clears the terminal");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
        UART_Write_Protected(MsgBuffer);
    }
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
    strcpy(MsgBuffer,                          "\n\n\r");
    strcat(MsgBuffer,NextSubString(global.MsgBuff,true));
    strcat(MsgBuffer,                            "\n\r");
    UART_Write_Protected(MsgBuffer);
}

void InvalidMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    global.MsgBuff[15] = '\0';
    strcpy(MsgBuffer,  "\r\nInvalid Command: ");
    strcat(MsgBuffer,           global.MsgBuff);
    strcat(MsgBuffer,                   "\r\n");
    UART_Write_Protected(MsgBuffer);
}

/*
 * =============== SubString Functions ========
 */

/* MatchSubString compares msg2 with the first substring pointed to by msg1 */

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

/* NextSubString moves a pointer to the next substring in a string */

char* NextSubString(char *msg, bool Print){
    char *index;
    if(msg == NULL){
        return NULL;
    }
    index = strchr(msg, ' ');
    if(!index){
        return NULL;
    }
    if(!Print){
        while(*index == ' '){
            index++;
        }
    } else {
        if(*index == ' '){
            index++;
        }
    }
    if(!*index){
        return NULL;
    }
    return index;
}

/*
 * =============== Initial Parser ========
 */

void MsgParser() {


    if        (MatchSubString(global.MsgBuff, "-help" )) {
           HelpMsg();
    } else if (MatchSubString(global.MsgBuff, "-about")) {
          AboutMsg();
    } else if (MatchSubString(global.MsgBuff, "-clear")) {
          ClearMsg();
    } else if (MatchSubString(global.MsgBuff, "-print")) {
          PrintMsg();
    } else {
        InvalidMsg();
    }
}

/*
 * ========== Second Layer Parser Functions & Messages ========
 */

void HelpHelpMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "   -help -> provides list of function descriptions \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "Location -> CommandTerminal.c");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpAboutMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "   -about -> provides developer and version info \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Location -> CommandTerminal.c");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpPrintMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "   -print -> prints message after -print \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Location -> CommandTerminal.c");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpClearMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "   -clear -> clears the terminal \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Location -> CommandTerminal.c");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}


