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
#include <stdbool.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "ti_drivers_config.h"

/*
 * ========== Global Definitions =======
 */

#define Version "1"
#define SubVersion "3"
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

void GlobInit(Glob *global);

extern Glob global;

/*
 * ========== Parser Functions =========
 */

void HelpMsg();

void AboutMsg();

void ClearMsg();

void PrintMsg();

void InvalidMsg();

bool MatchSubString(const char *msg1, const char *msg2);

void MsgParser(char *msg);

/*
 * ========== UART_Write_Protected =====
 */

void UART_Write_Protected(char* input);

/*
 * ========== UART_Input_Handler =======
 */

void UART_Input_Handler(char input);

/*
 * ========== UART_Init ==============
 */

void UART_Init();

#endif

