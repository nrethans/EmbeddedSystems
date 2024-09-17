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
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/gates/GateSwi.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <pthread.h>

#include "ti_drivers_config.h"


/*
 * ========== Global Definitions =======
 */
#define Assignment "4"
#define Version "4"
#define SubVersion "0"
#define MsgBufferSize 100
#define MsgPrintBufferSize 112 //80 for PuTTY width & 32 for \r\n (each is 1 byte)
#define MsgBreaker "\r\n================================================================================\r\n"
#define MsgQueueLen 32
#define MsgQueueMsgLen 320


extern Semaphore_Handle semaphore1;


extern GateSwi_Handle gateSwi0;
extern GateSwi_Handle gateSwi1;

extern Task_Handle task0;
extern Task_Handle task1;

extern Swi_Handle swi0;
extern Swi_Handle swi1;
extern Swi_Handle swi2;

/*
 * ========== Structures ===============
 */

typedef struct Error{
    uint16_t InvalidCMD;
    uint16_t InputOverflow;
    uint16_t InvalidAddress;
    uint16_t InvalidGPIOPin;
    uint16_t InvalidGPIOAction;
    uint16_t QueueOverflow;
} Error;

typedef struct Timer1{
    Timer_Handle Handle;
    uint32_t     Period;
} Timer1;

typedef struct MsgQueue{
    int32_t Write;
    int32_t Read;
    char    MsgQueue[MsgQueueLen][MsgQueueMsgLen];
}MsgQueue;

typedef struct MsgInput{
    char    MsgBuff[MsgBufferSize];
    int32_t index;
}MsgInput;

typedef struct Bios{
    Semaphore_Handle QueueSemaphore;
    GateSwi_Handle   PayloadGate;
} Bios;

typedef struct Callbacks{
    char Callback0[MsgBufferSize];
    char Callback1[MsgBufferSize];
    char Callback2[MsgBufferSize];
    char Callback3[MsgBufferSize];
    int32_t Callback0Rep;
    int32_t Callback1Rep;
    int32_t Callback2Rep;
    int32_t Callback3Rep;
} Callbacks;

typedef struct Glob {
    int32_t      GlobHead;
    UART_Handle  uart;
    Error        Error;
    Timer1       Timer1;
    MsgInput     MsgInput;
    MsgQueue     MsgQueue;
    Bios         Bios;
    Callbacks    Callbacks;
    int32_t      GlobTail;
} Glob;

/*
 * ========== Threads =================
 */

void UART_Thread();

void Payload_Thread();

/*
 * ========== Inter-Thread Functions ==
 */

void AddPayload(char *payload);

/*
 * ========== Initializers ============
 */

void GlobInit(Glob *global);

extern Glob global;

void UART_Init();

void Timer_Init();

/*
 * ========== Callbacks ================
 */

void Timer1CallBack();

void GPIO_SW1_Callback();

void GPIO_SW2_Callback();

/*
 * ========== SWI ======================
 */

void SW1_Swi();

void SW2_Swi();

void Timer0Swi();

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

void ErrorMsg();

void GPIOParse();

void TimerParse();

void CallbackParse();

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

