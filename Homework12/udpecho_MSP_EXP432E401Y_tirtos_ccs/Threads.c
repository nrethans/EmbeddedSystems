/*
 *  Threads.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



void UART_Thread(){ //Priority 4
    char  input;

    if    (global.Bios.PayloadGate == NULL){
        while(1); //Failed to create WriteGate Swi
    }

    while (1){
        UART_read(global.uart, &input, 1);
        UART_write(global.uart, &input, 1);
        UART_Input_Handler(input);
    }
}



void UART7_Thread(){ //Priority 3
    char input;

    if   (global.Bios.PayloadGate == NULL){
        while(1); //Failed to create WriteGate Swi
    }

    while(1){
        UART_read(global.uart7, &input, 1);
        UART_Input_Handler(input);
    }
}



void Payload_Thread(){
    int32_t  nextindex;
    int32_t  index;
    uint32_t gatekey;

    while(1){
        Semaphore_pend(global.Bios.QueueSemaphore, BIOS_WAIT_FOREVER); //global.Bios.QueueSemaphore

        index = global.MsgQueue.Read;

        MsgParser();

        gatekey = GateSwi_enter(global.Bios.PayloadGate);
        nextindex = index + 1;
        if(nextindex >= MsgQueueLen){
            nextindex = 0;
        }
        global.MsgQueue.Read = nextindex;
        GateSwi_leave(global.Bios.PayloadGate, gatekey);
    }
}



void ADCStream() {
    uint16_t *source;
    char longload[sizeof(uint16_t)*DATABLOCKSIZE+MsgQueueMsgLen];
    int32_t dest_choice;
    int32_t hdrlen;
    bool local = true;

    while(1){
        Semaphore_pend(global.Bios.ADCSemaphore, BIOS_WAIT_FOREVER);

        if(global.ADCBufCtrl.RX_Completed == global.ADCBufCtrl.RX_Ping){
            source = global.ADCBufCtrl.RX_Completed;
            dest_choice = 0;
            global.ADCBufCtrl.ping_count++;
        }
        else if(global.ADCBufCtrl.RX_Completed == global.ADCBufCtrl.RX_Pong){
            source = global.ADCBufCtrl.RX_Completed;
            dest_choice = 1;
            global.ADCBufCtrl.pong_count++;
        }
        else{
            AddPayload("-print RX_Ping and RX_Pong not completed, lost pointer");
            return;
        }
        //Eventually add net packaging here

        if(local == true){
            sprintf(longload, "-voice %d 128  ", dest_choice);
            hdrlen = strlen(longload)+1;
            memcpy(&longload[hdrlen], source, sizeof(uint16_t)*DATABLOCKSIZE);
            VoiceParse(longload);
        }
    }
}



void TaskAAA(){
    GPIO_init();
    GPIO_enableInt(CONFIG_GPIO_SW1);
    GPIO_enableInt(CONFIG_GPIO_SW2);
    UART_Init();
    GlobInit(&global);
//    SPI_init();
    SPI_Init();
//    ADCBuf_init();
    ADCBuf_Init();
    Timer_Init();
    ClearMsg();
    AboutMsg();
}

