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
#include <math.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/ADCBuf.h>
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

#define Assignment "13"
#define Version "13"
#define SubVersion "1"
#define MsgBufferSize 100
#define MsgPrintBufferSize 112 //80 for PuTTY width & 32 for \r\n (each is 1 byte)
#define MsgBreaker "--------------------------------------------------------------------------------\r\n"
#define MsgQueueLen 32
#define MsgQueueMsgLen 320
#define NUM_REGS 32
#define NUM_SCRIPTS 64
#define DATABLOCKSIZE 128
#define DATADELAY 8
#define TXBUFCOUNT 2
#define NetQueueLen 32
#define NetQueueSize 320
#define REG_DIAL1 0
#define REG_DIAL2 1
#define DEFAULTPORT 1000

/*
 * ========== Global Externs ============
 */

extern Semaphore_Handle semaphore1;
extern Semaphore_Handle semaphore2;
extern Semaphore_Handle semaphore3;
extern GateSwi_Handle gateSwi0;
extern GateSwi_Handle gateSwi1;
extern GateSwi_Handle gateSwi2;
extern Task_Handle task0; //UART_Thread
extern Task_Handle task1; //Payload Thread
extern Task_Handle task2; //Task AAA
extern Task_Handle task3; //UART Thread
extern Task_Handle task4; //ADC Stream
extern Swi_Handle swi0;
extern Swi_Handle swi1;
extern Swi_Handle swi2;
extern Swi_Handle swi3;
extern Swi_Handle swi4;

/*
 * ========== Structures ================
 */

typedef enum {
    INVALID_CMD = 0,
    INPUT_OVFLW,
    MEMR_ERR,
    GPIO_ERR,
    Q_OVFLW,
    CBACK_ERR,
    TICKER_ERR,
    TIMER_ERR,
    REG_ERR,
    DIV_ZERO,
    KILL_SW,
    EMPTY_PAYLOAD,
    SCRIPT_ERR,
    IF_ERR,
    SINE_ERR,
    VOICE_ERR,
    AUDIO_ERR,
    STREAM_ERR,
    NETWORK_ERR,
    NUM_ERRORS
} ERR_Enum;

typedef struct Error{
    uint16_t Count [NUM_ERRORS];                          //Number of times each error
    char     Labels[NUM_ERRORS][MsgPrintBufferSize];
} Error;

typedef struct Timer1{
    Timer_Handle Handle;
    uint32_t     Period;
} Timer1;

typedef struct Timer2{
    Timer_Handle Handle;
    uint32_t     Period;
} Timer2;

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
    Semaphore_Handle ADCSemaphore;
    Semaphore_Handle NetSemaphore;
    GateSwi_Handle   PayloadGate;
    GateSwi_Handle   CallbackGate;
    GateSwi_Handle   NetworkGate;
    Task_Handle      InputTask;
    Task_Handle      PayloadTask;
    Task_Handle      AAATask;
    Task_Handle      UART7;
    Task_Handle      ADCStream;
    Swi_Handle       Timer1SWI;
    Swi_Handle       SW1SWI;
    Swi_Handle       SW2SWI;
    Swi_Handle       Timer2SWI;
    Swi_Handle       ADCSWI;
} Bios;

typedef enum {
    CALLBACK_0 = 0,
    CALLBACK_1,
    CALLBACK_2,
    CALLBACK_3,
    NUM_CALLBACKS
} CallbackEnum;

typedef struct Callbacks {
    char Callback[NUM_CALLBACKS][MsgBufferSize];
    int32_t CallbackRep[NUM_CALLBACKS];
} Callbacks;

typedef enum {
    TICKER_0 = 0,
    TICKER_1,
    TICKER_2,
    TICKER_3,
    TICKER_4,
    TICKER_5,
    TICKER_6,
    TICKER_7,
    TICKER_8,
    TICKER_9,
    TICKER_10,
    TICKER_11,
    TICKER_12,
    TICKER_13,
    TICKER_14,
    TICKER_15,
    NUM_TICKERS
} TickerEnum;

typedef struct Tickers{
    int32_t TickerDelay[NUM_TICKERS];
    int32_t TickerDelayShadow[NUM_TICKERS];
    int32_t TickerPeriod[NUM_TICKERS];
    int32_t TickerPeriodShadow[NUM_TICKERS];
    int32_t TickerRepetitions[NUM_TICKERS];
    char    TickerPayload[NUM_TICKERS][MsgBufferSize];
} Tickers;

typedef struct Regs{
    int32_t Reg[NUM_REGS];
} Regs;

typedef struct Scripts{
    char    Script[NUM_SCRIPTS][MsgBufferSize];
    int32_t ScriptIndex;
} Scripts;

typedef struct LUTCtrl{
    double  lutDelta;
    double  lutPosition;
} LUTCtrl;

typedef struct ADCBuf{
    ADCBuf_Params params;
    ADCBuf_Handle Handle;
} ADCBuf;

typedef struct ADCBufControl{
    ADCBuf_Conversion conversion;
    uint16_t *RX_Completed;
    uint32_t converting;
    uint32_t ping_count;
    uint32_t pong_count;
    uint16_t RX_Ping[DATABLOCKSIZE];
    uint16_t RX_Pong[DATABLOCKSIZE];
} ADCBufControl;

typedef struct TXBufControl{
    uint16_t *TX_Completed;
    int32_t  TX_index;
    int32_t  TX_correction;
    uint32_t TX_delay;
    uint32_t TX_sample_count;
    uint16_t TX_Ping[DATABLOCKSIZE];
    uint16_t TX_Pong[DATABLOCKSIZE];
} TXBufControl;

typedef struct NetOutQ{
    int32_t payloadWriting, payloadReading;
    char    payloads[NetQueueLen][NetQueueSize];
    int32_t binaryCount[320];
} NetOutQ;

typedef struct Discoveries{
    uint32_t IP_address;
} Discoveries;

typedef struct Glob {
    int32_t       GlobHead;

    UART_Handle   uart;
    Error         Error;
    Timer1        Timer1;
    Timer2        Timer2;
    MsgInput      MsgInput;
    MsgQueue      MsgQueue;
    Bios          Bios;
    Callbacks     Callbacks;
    Tickers       Tickers;
    Regs          Regs;
    Scripts       Scripts;
    UART_Handle   uart7;
    SPI_Handle    SPI_3;
    LUTCtrl       LUTCtrl;
    ADCBuf        ADCBuf;
    ADCBufControl ADCBufCtrl;
    TXBufControl  TXBufCtrl[TXBUFCOUNT];
    NetOutQ       NetOutQ;
    Discoveries   Discoveries[32];
    uint32_t      Multicast;
    int32_t       GlobTail;
} Glob;

/*
 * ========== Initializers ============
 */

void GlobInit(Glob *global);

extern Glob global;

void ADCBuf_Init();

void SPI_Init();

void UART_Init();

void Timer_Init();

/*
 * ========== Threads =================
 */

void UART_Thread();

void UART7_Thread();

void Payload_Thread();

void TaskAAA();

void ADCStream();

/*
 * ========== Callbacks ================
 */

void ADCBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion, void *buffer, uint32_t channel, int_fast16_t status);

void Timer0CallBack();

void Timer1CallBack();

void GPIO_SW1_Callback();

void GPIO_SW2_Callback();

/*
 * =============== SWIs ======================
 */

void ADC_Swi();

void SW1_Swi();

void SW2_Swi();

void Timer0Swi();

void Timer1Swi();

/*
 * =============== Helper Functions ========
 */

bool MatchSubString(const char *msg1, const char *msg2);

char* NextSubString(char *msg, bool Print);

/*
 * =============== Initial Parser and UART Handler =============
 */

void MsgParser();

void UART_Write_Protected(char* input);

void UART_Input_Handler(char input);

/*
 * ========== Interface Functions =============
 */

void HelpParse();

void AboutMsg();

void ClearMsg();

void InvalidMsg();

void PrintMsg();

void MemRead();

void AddError(ERR_Enum Type, char* Msg);

void ErrorMsg();

void GPIOParse(char *ch);

void TimerParse(char *ch);

void AddPayload(char *payload);

void CallbackParse(char *ch);

void TickerParser(char *ch);

void RegParse(char *ch);

void ScriptsParse(char *ch);

void IfParse();

void SineParse(char *ch);

void VoiceParse(char *ch);

void AudioParse();

void StreamParse(char *ch);

void ClearAudioBuffers();

void ParseNetUDP(char *ch, int32_t binaryCount);

/*
 * ========== Help Messages ============
 */

void HelpHelpMsg();

void HelpAboutMsg();

void HelpPrintMsg();

void HelpClearMsg();

void HelpMemrMsg();

void HelpGPIOMsg();

void HelpErrorMsg();

void HelpTimerMsg();

void HelpCallbackMsg();

void HelpTickerMsg();

void HelpRegMsg();

void HelpScriptMsg();

void HelpIfMsg();

void HelpUARTMsg();

void HelpSineMsg();

void HelpNetUDPMsg();

#endif

