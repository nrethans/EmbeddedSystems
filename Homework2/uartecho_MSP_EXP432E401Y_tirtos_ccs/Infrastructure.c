/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * ========== Global Initializer =======
 */

void GlobInit(Glob *global) {
    global->GlobHead = 0x5a5a5a5a;
    memset(global->MsgBuff, '\0', sizeof(global->MsgBuff));
    global->index = 0;
    global->iterate = 0;
    global->GlobTail = 0x5a5a5a5a;
}

/*
 * ========== UART Write Protected =====
 */

void UART_Write_Protected(char* input) {
    int length = 0;
    length = strlen(input);
    UART_write(global.uart, input, length);
}

/*
 * ========== UART_Input_Handler =======
 */

void UART_Input_Handler(char input) {

    char MsgBuffOverflowErr[] = "\r\nMessage buffer overflow error: Do not exceed 100 Characters\r\n";

    if (global.index < sizeof(global.MsgBuff) - 1) {
        if (input == '\r' || input == '\n') {
            global.MsgBuff[global.index] = '\0';
            global.index += 1;
            MsgParser(global.MsgBuff);

            for (global.iterate = 0; global.iterate < global.index; (global.iterate)++) {
                global.MsgBuff[global.iterate] = '\0';
            }
            global.index = 0;

        } else if (input == 127 || input == '\b') {
            if (global.index != 0) {
                (global.index)--;
            }
        } else {
            if (input != 24 && input != 25 && input != 26 && input != 27) {
                global.MsgBuff[global.index] = input;
                (global.index)++;
            }
        }
    } else {
        // Buffer overflow
        for (global.iterate = 0; global.iterate < MsgBufferSize; (global.iterate)++) {
            global.MsgBuff[global.iterate] = '\0';
        }
        global.index = 0;
        UART_Write_Protected(MsgBuffOverflowErr);
    }
}

/*
 * ========== UART_Init ==============
 */

void UART_Init(){

    UART_Params uartParams;
    UART_init();
    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    global.uart = UART_open(CONFIG_UART_0, &uartParams);

    /* Global Initialization */
    GlobInit(&global);

    if (global.uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
}


