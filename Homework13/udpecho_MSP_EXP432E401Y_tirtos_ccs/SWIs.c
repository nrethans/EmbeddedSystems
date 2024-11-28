/*
 *  SWIs.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



void ADC_Swi() {

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
