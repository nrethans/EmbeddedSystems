/*
 *    Global.h
 *
 *  Created on: Aug 27, 2024
 *      Author: NickRethans
 */

#ifndef Global
#define Global

/*
 * ========= Header Files ==============
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/SHA2.h>
#include <ti/drivers/Timer.h>

#include "ti_drivers_config.h"


/*
 * ========== Global Definitions =======
 */
#define Assignment "4"
#define Version "4"
#define SubVersion "0"
#define MsgBufferSize 100
#define MsgPrintBufferSize 80

/*
 * ========== Structures ===============
 */

typedef struct Error{
    uint16_t InvalidCMD;
    uint16_t InputOverflow;
    uint16_t InvalidAddress;
    uint16_t InvalidGPIOPin;
    uint16_t InvalidGPIOAction;
} Error;

typedef struct GPIO_Val {
    uint8_t GPIO_LED0;
    uint8_t GPIO_LED1;
    uint8_t GPIO_LED2;
    uint8_t GPIO_LED3;
    uint8_t GPIO_AUDIO_PWR;
    uint8_t GPIO_MIC_PWR;
    uint8_t GPIO_SW1;
    uint8_t GPIO_SW2;
} GPIO_Val;

typedef struct Timer1{
    Timer_Handle Handle;
    uint32_t     Period;

} Timer1;

typedef struct Glob {
    int32_t      GlobHead;
    UART_Handle  uart;
    GPIO_Val     GPIO_Val;
    Error        Error;
    Timer1       Timer1;
    char         MsgBuff[MsgBufferSize];
    int          index;
    int          iterate;
    int32_t      GlobTail;
} Glob;

/*
 * ========== Initializers ============
 */

void GlobInit(Glob *global);

extern Glob global;

void Error_Init();

void UART_Init();

void Timer1CallBack(Timer_Handle handle, int_fast16_t status);

void Timer_Init();


/*
 * =============== SubString Functions ========
 */

bool MatchSubString(const char *msg1, const char *msg2);

char* NextSubString(char *msg, bool Print);

/*
 * =============== Initial Parser =============
 */

void MsgParser();

/*
 * ========== First Layer Parser Functions & Messages =========
 */

void HelpParse();

void AboutMsg();

void ClearMsg();

void PrintMsg();

void MemRead();

void GPIOParse();

void GPIOParse();

void InvalidMsg();

/*
 * ========== Second Layer Parser Functions & Messages ========
 */

void HelpHelpMsg();

void HelpAboutMsg();

void HelpPrintMsg();

void HelpClearMsg();

void HelpMemrMsg();

void HelpGPIOMsg();

void HelpErrorMsg();

/*
 * ========== UART =====================
 */

void UART_Write_Protected(char* input);

void UART_Input_Handler(char input);

#endif

