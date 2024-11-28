/*
 *  Callbacks.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



void ADCBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion, void *buffer, uint32_t channel, int_fast16_t status){
    if(buffer != global.ADCBufCtrl.RX_Ping && buffer != global.ADCBufCtrl.RX_Pong){
        Swi_post(global.Bios.ADCSWI);
        return;
    }
    global.ADCBufCtrl.RX_Completed = buffer;
    Semaphore_post(global.Bios.ADCSemaphore);
}



void Timer0CallBack(){
    if(MatchSubString(global.Callbacks.Callback[0],"-sine")){
        SineParse(global.Callbacks.Callback[0]);
    }
    else if(MatchSubString(global.Callbacks.Callback[0],"-audio")){
        AudioParse();
    }
    else{
        Swi_post(swi0);
    }
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
