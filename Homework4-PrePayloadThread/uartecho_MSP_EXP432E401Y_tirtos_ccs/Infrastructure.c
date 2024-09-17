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
    memset(global->MsgBuff, '\0', sizeof(global->MsgBuff));
    global->GlobHead = 0x5a5a5a5a;
    global->index = 0;
    global->iterate = 0;
    global->GlobTail = 0x5a5a5a5a;
}

void Error_Init(){
    global.Error.InvalidCMD        = 0;
    global.Error.InputOverflow     = 0;
    global.Error.InvalidAddress    = 0;
    global.Error.InvalidGPIOPin    = 0;
    global.Error.InvalidGPIOAction = 0;
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

    GlobInit(&global);

    if (global.uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
}

void Timer1CallBack(Timer_Handle handle, int_fast16_t status){

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
    //Timer_stop(handle);
    global.Timer1.Period = params.period;
    global.Timer1.Handle = handle;
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

    char MsgBuffOverflowErr[] = "\r\nMessage buffer overflow error: Do not exceed 100 Characters\r\n";

    if (global.index < sizeof(global.MsgBuff) - 1) {
        if (input == '\r' || input == '\n') {
            global.MsgBuff[global.index] = '\0';
            global.index += 1;
            MsgParser(global.MsgBuff);

            for (global.iterate = 0; global.iterate < global.index; (global.iterate)++) {
                global.MsgBuff[global.iterate] = '\0';
            }
            global.index = 0;

        } else if (input == 127 || input == '\b') {
            if (global.index != 0) {
                (global.index)--;
            }
        } else {
            if (input != 24 && input != 25 && input != 26 && input != 27) {
                global.MsgBuff[global.index] = input;
                (global.index)++;
            }
        }
    } else {
        // Buffer overflow
        for (global.iterate = 0; global.iterate < MsgBufferSize; (global.iterate)++) {
            global.MsgBuff[global.iterate] = '\0';
        }
        global.index = 0;
        global.Error.InputOverflow++;
        UART_Write_Protected(MsgBuffOverflowErr);
    }
}





