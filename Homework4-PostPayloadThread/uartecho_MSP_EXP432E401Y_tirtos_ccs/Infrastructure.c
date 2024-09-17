/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * ========== Initializers =======
 */

void GlobInit(Glob *global) {
    global->GlobHead                = 0x5a5a5a5a;
    memset(global->MsgInput.MsgBuff, '\0', sizeof(global->MsgInput.MsgBuff));
    global->MsgInput.index          = 0;
    global->MsgQueue.Write          = 0;
    global->MsgQueue.Read           = 0;
    global->Callbacks.Callback0Rep  = 0;
    global->Callbacks.Callback1Rep  = 0;
    global->Callbacks.Callback2Rep  = 0;
    global->Callbacks.Callback3Rep  = 0;
    global->Error.InvalidCMD        = 0;
    global->Error.InputOverflow     = 0;
    global->Error.InvalidAddress    = 0;
    global->Error.InvalidGPIOPin    = 0;
    global->Error.InvalidGPIOAction = 0;
    memset(global->MsgQueue.MsgQueue, '\0',sizeof(global->MsgQueue.MsgQueue));
    global->GlobTail                = 0x5a5a5a5a;
}

void UART_Init(){

    UART_Params uartParams;
    UART_init();

    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    global.uart = UART_open(CONFIG_UART_0, &uartParams);

//    GlobInit(&global);

    if (global.uart == NULL) {
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
    params.timerCallback = Timer1CallBack;
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
}

/*
 * ========== Callbacks ================
 */

void Timer1CallBack(){
    Swi_post(swi0);
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

void Timer0Swi(){
    if        (global.Callbacks.Callback0Rep == -1){
        AddPayload(global.Callbacks.Callback0);
    } else if (global.Callbacks.Callback0Rep > 0  ){
        AddPayload(global.Callbacks.Callback0);
        global.Callbacks.Callback0Rep--;
    } else {
        Timer_stop(global.Timer1.Handle);
    }
}

void SW1_Swi(){
    if(global.Callbacks.Callback1Rep == -1){
        AddPayload(global.Callbacks.Callback1);
    }
    if(global.Callbacks.Callback1Rep > 0  ){
        AddPayload(global.Callbacks.Callback1);
        global.Callbacks.Callback1Rep--;
    }
}

void SW2_Swi(){
    if(global.Callbacks.Callback2Rep == -1){
        AddPayload(global.Callbacks.Callback2);
    }
    if(global.Callbacks.Callback2Rep > 0  ){
        AddPayload(global.Callbacks.Callback2);
        global.Callbacks.Callback2Rep--;
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

    if (global.MsgInput.index < sizeof(global.MsgInput.MsgBuff) - 1) {
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
//        UART_Write_Protected(MsgBuffer);
        AddPayload(MsgBuffer);
    }
}





