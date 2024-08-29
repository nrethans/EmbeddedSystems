/*
 *    Global.h
 *
 *  Created on: Aug 27, 2024
 *      Author: NickRethans
 */

#ifndef Global
#define Global

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "ti_drivers_config.h"

/*
 * ========== Global Definitions =======
 */

#define Version "1"
#define SubVersion "2"
#define MsgBufferSize 100
#define MsgPrintBufferSize 80

/*
 * ========== Global Variables =========
 */

typedef struct Glob {
    int32_t     GlobHead;
    UART_Handle uart;
    char        MsgBuff[MsgBufferSize];
    int         index;
    int         iterate;
    int32_t     GlobTail;
} Glob;

/*
 * ========== Global Initializer =======
 */

void GlobInit(Glob *global, UART_Handle uart);

/*
 * ========== Parser Functions =========
 */

void HelpMsg(UART_Handle uart);

void AboutMsg(UART_Handle uart);

void ClearMsg(UART_Handle uart);

void InvalidMsg(UART_Handle uart);

void MsgParser(UART_Handle uart, char *msg);

/*
 * ========== UART_Write_Protected =====
 */

void UART_Write_Protected(UART_Handle uart, char* input);

/*
 * ========== UART_Input_Handler =======
 */

void UART_Input_Handler(Glob *global, char input);

#endif

