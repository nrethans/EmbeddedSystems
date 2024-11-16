/*
 *  InitialHandler.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



void MsgParser() {
    char    *payload;
    char    MsgBuffer[MsgBufferSize];
    int32_t index;

    index   = global.MsgQueue.Read;
    payload = global.MsgQueue.MsgQueue[index];

    if        (MatchSubString(payload, "-help"    )) {
         HelpParse();
    } else if (MatchSubString(payload, "-about"   )) {
          AboutMsg();
    } else if (MatchSubString(payload, "-clear"   )) {
          ClearMsg();
    } else if (MatchSubString(payload, "-print"   )) {
          PrintMsg();
    } else if (MatchSubString(payload, "-memr"    )) {
           MemRead();
    } else if (MatchSubString(payload, "-gpio"    )) {
          char *ch = NULL;
          GPIOParse(ch);
    } else if (MatchSubString(payload, "-error"   )) {
          ErrorMsg();
    } else if (MatchSubString(payload, "-timer"   )) {
          char *ch = NULL;
          TimerParse(ch);
    } else if (MatchSubString(payload, "-callback")) {
          char *ch = NULL;
          CallbackParse(ch);
    } else if (MatchSubString(payload, "-ticker"  )) {
          char *ch = NULL;
          TickerParse(ch);
    } else if (MatchSubString(payload, "-reg"     )) {
          char *ch = NULL;
          RegParse(ch);
    } else if (MatchSubString(payload, "-script"  )) {
          char *ch = NULL;
          ScriptsParse(ch);
    } else if (MatchSubString(payload, "-rem"     )) {
          //-rem comment
    } else if (MatchSubString(payload, "-if"      )) {
          IfParse();
    } else if (MatchSubString(payload, "-uart"    )) {
          UARTParse();
    } else if (MatchSubString(payload, "-sine"    )) {
          char *ch = NULL;
          SineParse(ch);
    } else if (MatchSubString(payload, "-stream"  )) {
        char *ch = NULL;
        StreamParse(ch);
    } else if (MatchSubString(payload, "\r\n"     )) {
          strcpy(MsgBuffer, "\r\n");
          UART_Write_Protected(MsgBuffer);
    } else {
          InvalidMsg();
    }
}



void UART_Write_Protected(char* input) {
    int length = 0;
    length = strlen(input);
    UART_write(global.uart, input, length);
}



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
        memset(global.Scripts.Script, '\0', sizeof(global.Scripts.Script));
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
