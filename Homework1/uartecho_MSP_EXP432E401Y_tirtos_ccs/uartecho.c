/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * TO-DO
 * - Move terminal UART input interpreter into TerminalFunctions
 * - Create none case sensitive string comparison and nested function parsing
 * - Implement Glob struct and constructor
 * - Implement faster parser with switch and string hashing function
 * - change invalid message to Message ___ not understood
 * - make one header file with function declarations and define magic numbers but create the functions body in a seperate c file which includes the one header
 *
 */

/*
 *  ======== uartecho.c ========
 */

#include <Global.h>

/*
 *  ======== mainThread ===========
 */
void *mainThread(void *arg0)
{
    char        input;
    char MsgBuff[MsgBufferSize]={'\0'};
    int index = 0;
    int iterate;
    char  MsgBuffOverflowErr[] = "\r\nMessage buffer overflow error: Do no exceed 100 Characters\r\n";
    UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    /* Loop forever echoing */
    while (1) {
        UART_read(uart, &input, 1);
        if(index < sizeof(MsgBuff)-1){
            if(input == '\r'||input == '\n'){
                MsgBuff[index++]='\0';
                MsgParser(uart,MsgBuff);
                for(iterate = 0; iterate < index; iterate++){
                    MsgBuff[iterate]='\0';
                }
                index = 0;
            }
            else if(input == 127 || input == '\b'){
                if(index!=0){
                    index--;
                }
            }
            else{
                if(input != 24 && input != 25 && input != 26 && input != 27)
                    MsgBuff[index++]=input;
            }
        }
        else{
            for(iterate = 0; iterate < MsgBufferSize; iterate++){
                MsgBuff[iterate]='\0';
            }
            index = 0;
            UART_Write_Protected(uart, MsgBuffOverflowErr);
        }
        if(input != 24 && input != 25 && input != 26 && input != 27){
            UART_write(uart, &input, 1);
        }
    }
}





