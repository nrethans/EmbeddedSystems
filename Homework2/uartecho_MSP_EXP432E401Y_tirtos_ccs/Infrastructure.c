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

void UART_Write_Protected(UART_Handle uart, char* input) {
    int length = 0;
    length = strlen(input);
    UART_write(uart, input, length);
}
/*
 * ========== UART_Input_Handler =======
 */
void UART_Input_Handler(Glob *global, char input) {
    // Use the MsgBuff, index, and iterate from the Glob structure
    char *MsgBuff = global->MsgBuff;
    int *index = &global->index;
    int *iterate = &global->iterate;

    char MsgBuffOverflowErr[] = "\r\nMessage buffer overflow error: Do not exceed 100 Characters\r\n";

    if (*index < sizeof(global->MsgBuff) - 1) {
        if (input == '\r' || input == '\n') {
            MsgBuff[*index] = '\0';  // Null-terminate the buffer
            *index += 1;  // Increment index after null-termination

            MsgParser(global->uart, MsgBuff);

            // Clear the buffer and reset index
            for (*iterate = 0; *iterate < *index; (*iterate)++) {
                MsgBuff[*iterate] = '\0';
            }
            *index = 0;
        } else if (input == 127 || input == '\b') {
            if (*index != 0) {
                (*index)--;
            }
        } else {
            if (input != 24 && input != 25 && input != 26 && input != 27) {
                MsgBuff[*index] = input;
                (*index)++;
            }
        }
    } else {
        // Buffer overflow
        for (*iterate = 0; *iterate < MsgBufferSize; (*iterate)++) {
            MsgBuff[*iterate] = '\0';
        }
        *index = 0;
        UART_Write_Protected(global->uart, MsgBuffOverflowErr);
    }
}


