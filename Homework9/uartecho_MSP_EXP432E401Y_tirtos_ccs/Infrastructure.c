/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * ========== AAA Thread =========
 */

void TaskAAA(){
    GPIO_init();
    GPIO_enableInt(CONFIG_GPIO_SW1);
    GPIO_enableInt(CONFIG_GPIO_SW2);
    UART_Init();
    GlobInit(&global);
    Timer_Init();
    ClearMsg();
    AboutMsg();
}

/*
 * ========== Initializers =======
 */

void GlobInit(Glob *global) {
    global->GlobHead                  = 0x5a5a5a5a;

    global->MsgInput.index            = 0;
    memset(global->MsgInput.MsgBuff, '\0', sizeof(global->MsgInput.MsgBuff));

    global->MsgQueue.Write            = 0;
    global->MsgQueue.Read             = 0;
    memset(global->MsgQueue.MsgQueue, '\0',sizeof(global->MsgQueue.MsgQueue));
    memset(global->Callbacks.CallbackRep, 0, sizeof(global->Callbacks.CallbackRep));
    memset(global->Callbacks.Callback, '\0', sizeof(global->Callbacks.Callback));
    memset(global->Tickers.TickerDelay, 0, sizeof(global->Tickers.TickerPayload));
    memset(global->Tickers.TickerPeriod, 0, sizeof(global->Tickers.TickerPeriod));
    memset(global->Tickers.TickerRepetitions, 0, sizeof(global->Tickers.TickerRepetitions));
    memset(global->Tickers.TickerPayload, '\0', sizeof(global->Tickers.TickerPayload));

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
    global->Bios.PayloadGate          = gateSwi0;
    global->Bios.CallbackGate         = gateSwi1;
    global->Bios.InputTask            = task0;
    global->Bios.PayloadTask          = task1;
    global->Bios.AAATask              = task2;
    global->Bios.Timer1SWI            = swi0;
    global->Bios.SW1SWI               = swi1;
    global->Bios.SW2SWI               = swi2;
    global->Bios.Timer2SWI            = swi3;
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

    global->GlobTail                  = 0x5a5a5a5a;
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

/*
 * ========== Callbacks ================
 */

void Timer0CallBack(){
    Swi_post(swi0);
}

void Timer1CallBack(){
    Swi_post(swi3);
}

void GPIO_SW1_Callback(){
    Swi_post(swi1);
}

void GPIO_SW2_Callback(){
    Swi_post(swi2);
}

/*
 * ========== SWI ======================
 */

void Timer0Swi() {
    int32_t gatekey;
    ti_sysbios_BIOS_ThreadType tType;
    tType = BIOS_getThreadType();
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        gatekey = GateSwi_enter(global.Bios.CallbackGate);
    }
    if (global.Callbacks.CallbackRep[CALLBACK_0] == -1) {
        AddPayload(global.Callbacks.Callback[CALLBACK_0]);
    } else if (global.Callbacks.CallbackRep[CALLBACK_0] > 0) {
        AddPayload(global.Callbacks.Callback[CALLBACK_0]);
        global.Callbacks.CallbackRep[CALLBACK_0]--;
    } else {
        Timer_stop(global.Timer1.Handle);
    }
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        GateSwi_leave(global.Bios.CallbackGate,gatekey);
    }
}

void Timer1Swi(){
    int i;
    int32_t gatekey;
    ti_sysbios_BIOS_ThreadType tType;
    tType = BIOS_getThreadType();
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        gatekey = GateSwi_enter(global.Bios.CallbackGate);
    }

    for(i = 0; i < NUM_TICKERS; i++){
        //check count
        if(global.Tickers.TickerRepetitions[i] <= 0 && global.Tickers.TickerRepetitions[i] != -1)
            continue;
        //check delay
        if(global.Tickers.TickerDelayShadow[i] > 0){
            global.Tickers.TickerDelayShadow[i]--;
            continue;
        }
        //check period
        else if(global.Tickers.TickerPeriodShadow[i] <= 0){
            global.Tickers.TickerPeriodShadow[i] = global.Tickers.TickerPeriod[i];
            if(global.Tickers.TickerRepetitions[i] != -1)
                global.Tickers.TickerRepetitions[i]--;
            AddPayload(global.Tickers.TickerPayload[i]);
        }
        else{
            global.Tickers.TickerPeriodShadow[i]--;
        }
    }

    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        GateSwi_leave(global.Bios.CallbackGate,gatekey);
    }
}

void SW1_Swi() {
    int32_t gatekey;
    ti_sysbios_BIOS_ThreadType tType;
    tType = BIOS_getThreadType();
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        gatekey = GateSwi_enter(global.Bios.CallbackGate);
    }
    if (global.Callbacks.CallbackRep[CALLBACK_1] == -1) {
        AddPayload(global.Callbacks.Callback[CALLBACK_1]);
    } else if (global.Callbacks.CallbackRep[CALLBACK_1] > 0) {
        AddPayload(global.Callbacks.Callback[CALLBACK_1]);
        global.Callbacks.CallbackRep[CALLBACK_1]--;
    }
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        GateSwi_leave(global.Bios.CallbackGate,gatekey);
    }
}

void SW2_Swi() {
    int32_t gatekey;
    ti_sysbios_BIOS_ThreadType tType;
    tType = BIOS_getThreadType();
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
            gatekey = GateSwi_enter(global.Bios.CallbackGate);
    }
    if (global.Callbacks.CallbackRep[CALLBACK_2] == -1) {
        AddPayload(global.Callbacks.Callback[CALLBACK_2]);
    } else if (global.Callbacks.CallbackRep[CALLBACK_2] > 0) {
        AddPayload(global.Callbacks.Callback[CALLBACK_2]);
        global.Callbacks.CallbackRep[CALLBACK_2]--;
    }
    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
            GateSwi_leave(global.Bios.CallbackGate,gatekey);
    }
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

    char MsgBuffer[MsgBufferSize];
    int32_t iterate = 0;
    if (input == '~'){
        int i;
        for(i = 0; i < NUM_CALLBACKS; i++){
            memset(global.Callbacks.Callback[i], '\0', sizeof(global.Callbacks.Callback[i]));
        }
        for(i = 0; i < NUM_TICKERS; i++){
            global.Tickers.TickerDelay[i]       = 0;
            global.Tickers.TickerPeriod[i]      = 0;
            global.Tickers.TickerRepetitions[i] = 0;
            memset(global.Tickers.TickerPayload[i], '\0', sizeof(global.Tickers.TickerPayload[i]));
        }
        AddPayload("-print Kill Switch Activated");
    }
    else if(global.MsgInput.index < sizeof(global.MsgInput.MsgBuff) - 1) {
        if (input == '\r' || input == '\n') {
            global.MsgInput.MsgBuff[global.MsgInput.index] = '\0';
            global.MsgInput.index += 1;
            strcpy(MsgBuffer, "\r\n");
            AddPayload(MsgBuffer);
            AddPayload(global.MsgInput.MsgBuff);

            for(iterate = 0; iterate < global.MsgInput.index; iterate++) {
                global.MsgInput.MsgBuff[iterate] = '\0';
            }
            global.MsgInput.index = 0;

        } else if (input == 127 || input == '\b') {
            if (global.MsgInput.index != 0) {
                global.MsgInput.index--;
            }
        } else {
            if (input != 24 && input != 25 && input != 26 && input != 27) {
                global.MsgInput.MsgBuff[global.MsgInput.index] = input;
                global.MsgInput.index++;
            }
        }
    } else {
        // Buffer overflow
        for (iterate = 0; iterate < MsgBufferSize; (iterate)++) {
            global.MsgInput.MsgBuff[iterate] = '\0';
        }
        global.MsgInput.index = 0;
        global.Error.InputOverflow++;
        strcpy(MsgBuffer, "\r\nMessage buffer overflow error: Do not exceed 100 Characters\r\n");
        AddPayload(MsgBuffer);
    }
}





