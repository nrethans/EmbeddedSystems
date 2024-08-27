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
 *  ======== uartecho.c ========
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"


/*
 * ======== Functions ==========
 */

/* Message Parser Function */
void MsgParser(UART_Handle uart, char *Msg){
    //Messages
    char Help[]  = "\n\r\n========================\r\n -help -> provides list of functions\r\n -about -> provides developer and version info\r\n========================\r\n";
    char About[] = "\n\r\n========================\r\n"
                       " Developer: Nicholas Rethans\r\n"
                       " Assignment #: 1\r\n"
                       " Version 1.0 \r\n"
                       " Time: " __TIME__ "  Date: " __DATE__ "\r\n"
                       "========================\r\n";
    char InvalidCMD[] = "\nInvalid Command...\r\n";

    //Message Parsing
    if(strcasecmp(Msg,"-help")==0)
        UART_write(uart,Help,sizeof(Help));
    else if(strcasecmp(Msg,"-about")==0)
        UART_write(uart,About,sizeof(About));
    else
        UART_write(uart,InvalidCMD,sizeof(InvalidCMD));
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    char        input;
    char MsgBuff[100];
    int index = 0;
    int iterate;
    const char  echoPrompt[] = "Echoing characters:\r\n";
    const char  MsgBuffOverflowErr[] = "\nMessage buffer overflow error: Do no exceed 100 Characters\n";
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

    UART_write(uart, echoPrompt, sizeof(echoPrompt));
    /* Loop forever echoing */
    while (1) {
        UART_read(uart, &input, 1);
        if(index < sizeof(MsgBuff)-1){
            if(input == '\r'||input == '\n'){
                MsgBuff[index++]='\0';
                MsgParser(uart,MsgBuff);
                for(iterate = 0; iterate < index; iterate++)
                    MsgBuff[iterate]='\xbe';
                index = 0;
            }
            else if(input == 127)
                MsgBuff[--index]='\xbe';
            else
                MsgBuff[index++]=input;
        }
        else{
            for(iterate = 0; iterate < 100; iterate++)
                MsgBuff[iterate]='\xbe';
            index = 0;
            UART_write(uart, MsgBuffOverflowErr, sizeof(MsgBuffOverflowErr));
        }
        UART_write(uart, &input, 1);
    }
}





