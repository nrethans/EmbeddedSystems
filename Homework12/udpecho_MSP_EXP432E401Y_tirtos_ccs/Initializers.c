/*
 *  Initializers.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



void GlobInit(Glob *global) {
    global->GlobHead                  = 0x5a5a5a5a;

    global->MsgInput.index            = 0;
    memset(global->MsgInput.MsgBuff, '\0', sizeof(global->MsgInput.MsgBuff));

    global->MsgQueue.Write            = 0;
    global->MsgQueue.Read             = 0;
    memset(global->MsgQueue.MsgQueue,       '\0',sizeof(global->MsgQueue.MsgQueue));
    memset(global->Callbacks.CallbackRep,     0, sizeof(global->Callbacks.CallbackRep));
    memset(global->Callbacks.Callback,      '\0', sizeof(global->Callbacks.Callback));
    memset(global->Tickers.TickerDelay,       0, sizeof(global->Tickers.TickerPayload));
    memset(global->Tickers.TickerPeriod,      0, sizeof(global->Tickers.TickerPeriod));
    memset(global->Tickers.TickerRepetitions, 0, sizeof(global->Tickers.TickerRepetitions));
    memset(global->Tickers.TickerPayload,   '\0', sizeof(global->Tickers.TickerPayload));

    memset(global->Regs.Reg, 0, sizeof(global->Regs.Reg));

    global->Error.InvalidCMD          = 0;
    global->Error.InputOverflow       = 0;
    global->Error.InvalidAddress      = 0;
    global->Error.InvalidGPIOPin      = 0;
    global->Error.InvalidGPIOAction   = 0;
    global->Error.QueueOverflow       =
    global->Error.InvalidCallbackAction = 0;
    global->Error.InvalidTickerAction = 0;
    global->Error.InvalidTimerAction  = 0;
    global->Error.InvalidRegAction    = 0;
    global->Error.DivisionByZero      = 0;

    global->Bios.QueueSemaphore       = semaphore1;
    global->Bios.ADCSemaphore         = semaphore2;
    global->Bios.PayloadGate          = gateSwi0;
    global->Bios.CallbackGate         = gateSwi1;
    global->Bios.InputTask            = task0;
    global->Bios.PayloadTask          = task1;
    global->Bios.AAATask              = task2;
    global->Bios.UART7                = task3;
    global->Bios.ADCStream            = task4;
    global->Bios.Timer1SWI            = swi0;
    global->Bios.SW1SWI               = swi1;
    global->Bios.SW2SWI               = swi2;
    global->Bios.Timer2SWI            = swi3;
    global->Bios.ADCSWI               = swi4;
    memset(global->Scripts.Script, '\0', sizeof(global->Scripts.Script));
    global->Scripts.ScriptIndex = 0;

//  Debug
    strcpy(global->Scripts.Script[0],"-if 0 < 1 ? -script 2 x : -script 4 x");
    strcpy(global->Scripts.Script[1],"-if #2 > #8 ? -script 2 x : -script 4 x");
    strcpy(global->Scripts.Script[2],"-print script 2 exe");
    strcpy(global->Scripts.Script[4],"-print script 4 exe");
    strcpy(global->Scripts.Script[30],"-gpio 0 t");
    strcpy(global->Scripts.Script[31],"-gpio 1 t");
    strcpy(global->Scripts.Script[32],"-gpio 2 t");
    strcpy(global->Scripts.Script[33],"-gpio 3 t");
    strcpy(global->Scripts.Script[40],"-ticker 0 100 1 1 -gpio 0 t");
    strcpy(global->Scripts.Script[41],"-ticker 1 150 1 1 -gpio 1 t");
    strcpy(global->Scripts.Script[42],"-ticker 2 200 1 1 -gpio 2 t");
    strcpy(global->Scripts.Script[43],"-ticker 3 250 1 1 -gpio 3 t");

    strcpy(global->Scripts.Script[45],"-ticker 0 0 100 -1 -sine 131");
    strcpy(global->Scripts.Script[46],"-ticker 0 150 1000 -1 -sine 294");
    strcpy(global->Scripts.Script[47],"-ticker 0 300 1000 -1 -sine 311");
    strcpy(global->Scripts.Script[48],"-ticker 0 450 1000 -1 -sine 349");
    strcpy(global->Scripts.Script[49],"-ticker 0 600 1000 -1 -sine 392");
    strcpy(global->Scripts.Script[50],"-ticker 0 750 1000 -1 -sine 440");
    strcpy(global->Scripts.Script[51],"-ticker 0 900 1000 -1 -sine 466");


    global->LUTCtrl.lutDelta          = 0;
    global->LUTCtrl.lutPosition       = 0;


    global->ADCBufCtrl.converting = 0;
    global->ADCBufCtrl.ping_count = 0;
    global->ADCBufCtrl.pong_count = 0;

    global->TXBufCtrl[0].TX_delay = 8;
    global->TXBufCtrl[1].TX_delay = 8;

    global->GlobTail                  = 0x5a5a5a5a;
}



void ADCBuf_Init(){
    ADCBuf_init();

    ADCBuf_Params_init(&global.ADCBuf.params);
    global.ADCBuf.params.returnMode = ADCBuf_RETURN_MODE_CALLBACK;
    global.ADCBuf.params.recurrenceMode = ADCBuf_RECURRENCE_MODE_CONTINUOUS;

    global.ADCBuf.params.callbackFxn = ADCBufCallback;
    global.ADCBuf.params.samplingFrequency = 8000;
    global.ADCBuf.Handle = ADCBuf_open(CONFIG_ADCBUF_0, &global.ADCBuf.params);
    if(global.ADCBuf.Handle == NULL){
        while(1);
    }

    global.ADCBufCtrl.conversion.adcChannel = ADCBUF_CHANNEL_0;
    global.ADCBufCtrl.conversion.arg = NULL;
    global.ADCBufCtrl.conversion.sampleBuffer = global.ADCBufCtrl.RX_Ping;
    global.ADCBufCtrl.conversion.sampleBufferTwo = global.ADCBufCtrl.RX_Pong;
    global.ADCBufCtrl.conversion.samplesRequestedCount = DATABLOCKSIZE;
}



void SPI_Init(){
    SPI_init();
    SPI_Handle      spi;
    SPI_Params      spiParams;
    SPI_Params_init(&spiParams);
    spiParams.dataSize = 16;
    spiParams.frameFormat = SPI_POL0_PHA1;

    spi = SPI_open(CONFIG_SPI_0, &spiParams);

    if (spi == NULL) {
        while (1);  // SPI_open() failed
    }

    global.SPI_3 = spi;
}



void UART_Init(){

    UART_Params uartParams;
    UART_init();

    //Main UART
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    global.uart = UART_open(CONFIG_UART_0, &uartParams);

    if (global.uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    //UART7
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;
    uartParams.readEcho = UART_ECHO_OFF;

    global.uart7 = UART_open(CONFIG_UART_1, &uartParams);

    if (global.uart7 == NULL) {
        /* UART_open() failed */
        while (1);
    }
}



void Timer_Init(){

    Timer_init();
    Timer_Handle handle;
    Timer_Params params;

    Timer_Params_init(&params);
    params.periodUnits   = Timer_PERIOD_US; //Time specified in microseconds
    params.period        = 1000000;
    params.timerMode     = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = Timer0CallBack;
    handle = Timer_open(CONFIG_TIMER_0, &params);
    if(handle == NULL){
        //Timer_open() failed
        while(1);
    }
    if(Timer_start(handle) == Timer_STATUS_ERROR){
        //Timer_start() failed
        while(1);
    }
    Timer_stop(handle);
    //Timer_stop(handle);
    global.Timer1.Period = params.period;
    global.Timer1.Handle = handle;

    //--------------------------------------------------------------------------//

    Timer_Handle handle2;
    Timer_Params params2;
    Timer_Params_init(&params2);
    params2.periodUnits   = Timer_PERIOD_US;
    params2.period        = 10000;
    params2.timerMode     = Timer_CONTINUOUS_CALLBACK;
    params2.timerCallback = Timer1CallBack;
    handle2 = Timer_open(CONFIG_TIMER_1, &params2);
    if(handle2 == NULL){
        //Timer_open() failed
        while(1);
    }
    if(Timer_start(handle2) == Timer_STATUS_ERROR){
        //Timer_start() failed
        while(1);
    }
//    Timer_stop(handle2);
    global.Timer2.Period = params2.period;
    global.Timer2.Handle = handle2;
}
