/*
 *  Interface.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"
#include "sinlut14.h"



void HelpParse()
{
    char    *StrBuffPTR;
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int32_t index;

    index = global.MsgQueue.Read;
    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);
    if (StrBuffPTR != NULL)
        if (MatchSubString(StrBuffPTR,          "-help") || MatchSubString(StrBuffPTR, "help")    )
            HelpHelpMsg();
        else if (MatchSubString(StrBuffPTR,    "-about") || MatchSubString(StrBuffPTR, "about")   )
            HelpAboutMsg();
        else if (MatchSubString(StrBuffPTR,    "-print") || MatchSubString(StrBuffPTR, "print")   )
            HelpPrintMsg();
        else if (MatchSubString(StrBuffPTR,    "-clear") || MatchSubString(StrBuffPTR, "clear")   )
            HelpClearMsg();
        else if (MatchSubString(StrBuffPTR,     "-memr") || MatchSubString(StrBuffPTR, "memr")    )
            HelpMemrMsg();
        else if (MatchSubString(StrBuffPTR,     "-gpio") || MatchSubString(StrBuffPTR, "gpio")    )
            HelpGPIOMsg();
        else if (MatchSubString(StrBuffPTR,    "-error") || MatchSubString(StrBuffPTR, "error")   )
            HelpErrorMsg();
        else if (MatchSubString(StrBuffPTR,    "-timer") || MatchSubString(StrBuffPTR, "timer")   )
            HelpTimerMsg();
        else if (MatchSubString(StrBuffPTR, "-callback") || MatchSubString(StrBuffPTR, "callback"))
            HelpCallbackMsg();
        else if (MatchSubString(StrBuffPTR,   "-ticker") || MatchSubString(StrBuffPTR, "ticker")  )
            HelpTickerMsg();
        else if (MatchSubString(StrBuffPTR,      "-reg") || MatchSubString(StrBuffPTR, "reg")     )
            HelpRegMsg();
        else if (MatchSubString(StrBuffPTR,   "-script") || MatchSubString(StrBuffPTR, "script")  )
            HelpScriptMsg();
        else if (MatchSubString(StrBuffPTR,       "-if") || MatchSubString(StrBuffPTR, "if")      )
            HelpIfMsg();
        else if (MatchSubString(StrBuffPTR,     "-uart") || MatchSubString(StrBuffPTR, "uart")    )
            HelpUARTMsg();
        else if (MatchSubString(StrBuffPTR,     "-sine") || MatchSubString(StrBuffPTR, "sine")    )
            HelpSineMsg();
        else if (MatchSubString(StrBuffPTR,   "-netudp") || MatchSubString(StrBuffPTR, "netudp")  )
            HelpNetUDPMsg();
        else
            InvalidMsg();
    else
    {
        strcpy(MsgBuffer, MsgBreaker);
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -help\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Provides list of function descriptions\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -about\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Provides developer and version info\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -print\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Prints message after -print\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -clear\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Clears the terminal\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -memr\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Prints memory address values\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -gpio\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Interfaces with GPIO pins\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -error\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Prints number of error occurrences\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -timer\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Lists timer period and configures hardware timers\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -callback\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Lists and configures callbacks \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -ticker\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Lists and configures tickers \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -reg \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Lists and configures 32 available registers \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -script \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Lists and configures 64 available scripts \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -if \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : If condition for executing scripts \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -uart \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Sends payload across UART7 TX: PC5 RX: PC4 \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -sine \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Plays pure sine wave from 1 - 3999Hz\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -audio \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Plays samples from TX Buffers\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -stream \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Starts local audio\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -netudp \r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Transmits UDP messages over IP\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  **Note**    : Type -help <command> for more information\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, MsgBreaker);
        UART_Write_Protected(MsgBuffer);
    }
}




void AboutMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Developer: Nicholas Rethans\r\n");
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Assignment #%s \r\n", Assignment);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Version %s.%s \r\n", Version, SubVersion);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Time: %s  Date: %s\r\n", __TIME__, __DATE__);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}



void InvalidMsg(){
    uint16_t index = 0;
    index = global.MsgQueue.Read;
    global.MsgQueue.MsgQueue[index][15] = '\0';
    AddError(INVALID_CMD, "Bad Command Check -help");
}



void ClearMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer,"\033c");
    UART_write(global.uart, MsgBuffer,sizeof(MsgBuffer));
}



void PrintMsg(){
    int32_t index;
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    index = global.MsgQueue.Read;
    sprintf(MsgBuffer, "%s \r\n",NextSubString(global.MsgQueue.MsgQueue[index],true));
    UART_Write_Protected(MsgBuffer);
}



void MemRead()
{
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *addressPTR;
    char    *MsgBuffPTR;
    int32_t value;
    int32_t address;
    int32_t index;

    index = global.MsgQueue.Read;
    MsgBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);
    if(MsgBuffPTR == NULL)
        address = 0;
    else
        address = strtoul(MsgBuffPTR, &addressPTR, 16);
    address = address & 0xFFFFFFF0;
    if((address >= 0x00100000 && address < 20000000) || (address >= 0x20040000))
        goto BadAddress;

    strcpy(MsgBuffer, "\r\n Memory Read: \r\n");
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer, "| %#010x | %#010x | %#010x | %#010x |\r\n", address + 0xC, address + 0x8, address + 0x4, address + 0x0);
    UART_Write_Protected(MsgBuffer);
    value = *(int32_t*)(address + 0xC);
    sprintf(MsgBuffer, "| %#010x | ", value);
    UART_Write_Protected(MsgBuffer);

    value = *(int32_t*)(address + 0x8);
    sprintf(MsgBuffer, "%#010x | ", value);
    UART_Write_Protected(MsgBuffer);

    value = *(int32_t*)(address + 0x4);
    sprintf(MsgBuffer, "%#010x | ", value);
    UART_Write_Protected(MsgBuffer);

    value = *(int32_t*)(address + 0x0);
    sprintf(MsgBuffer, "%#010x | \r\n", value);
    UART_Write_Protected(MsgBuffer);

    return;
BadAddress:
    AddError(MEMR_ERR, "Invalid Address");
    strcpy(MsgBuffer, "\r\n0x00100000 <= Address < 0x20000000 or Address >= 0x20040000\r\n");
    UART_Write_Protected(MsgBuffer);
}

void AddError(ERR_Enum Type, char* Msg){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    global.Error.Count[Type]++;
    sprintf(MsgBuffer,"-print \033[31m%s %s -Count: %d\033[0m", global.Error.Labels[Type], Msg, global.Error.Count[Type]);
    AddPayload(MsgBuffer);
}

void ErrorMsg(){
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    int     ErrorNum = -1;
    int32_t index;

    index = global.MsgQueue.Read;
    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if(MatchSubString(StrBuffPTR, "clear") || MatchSubString(StrBuffPTR, "-clear"))
        memset(global.Error.Count, 0, sizeof(global.Error.Count));
    else if(isdigit(*StrBuffPTR))
    {
        ErrorNum = strtol(StrBuffPTR, NULL, 10);
        sprintf(MsgBuffer, "%s count: %d", global.Error.Labels[ErrorNum], global.Error.Count[ErrorNum]);
        UART_Write_Protected(MsgBuffer);
        return;
    }
    else{
        UART_Write_Protected(MsgBreaker);
        for(index = 0; index < NUM_ERRORS; index++){
            sprintf(MsgBuffer, "%s count: %d\r\n", global.Error.Labels[index], global.Error.Count[index]);
            UART_Write_Protected(MsgBuffer);
        }
        UART_Write_Protected(MsgBreaker);
    }
}



void GPIOParse(char *ch) {
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *MsgBuffPTR;
    int     GPIO_Num = -1;
    int32_t index;

    index = global.MsgQueue.Read;
    if(ch != NULL){
        MsgBuffPTR = NextSubString(ch,false);
    } else {
        MsgBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);
    }
    if(MsgBuffPTR != NULL){
        if(isdigit(*MsgBuffPTR)){
            GPIO_Num = *MsgBuffPTR - '0';
            if(GPIO_Num > 6 || GPIO_Num < 0){
                AddError(GPIO_ERR, "Invalid Pin Number");
                return;
            }
        } else {
            AddError(GPIO_ERR, "Invalid Pin Number");
            return;
        }
    }

    MsgBuffPTR = NextSubString(MsgBuffPTR,false);

    if(GPIO_Num <= 5 && GPIO_Num != -1) {
        if        (MatchSubString(MsgBuffPTR,"r")) {
            sprintf(MsgBuffer, "\r\nGPIO %d: %hhu\r\n", GPIO_Num, GPIO_read(GPIO_Num));
            UART_Write_Protected(MsgBuffer);

        } else if (MatchSubString(MsgBuffPTR,"w")) {

            MsgBuffPTR = NextSubString(MsgBuffPTR,false);

            if    (MatchSubString(MsgBuffPTR,"1")) {
                GPIO_write(GPIO_Num,1);
            } else if (MatchSubString(MsgBuffPTR,"0")) {
                GPIO_write(GPIO_Num,0);
            } else{
                AddError(GPIO_ERR, "Specify Write Value");
            }
            return;

        } else if (MatchSubString(MsgBuffPTR,"t")) {

            if(GPIO_read(GPIO_Num)==0){
                GPIO_write(GPIO_Num,1);
            } else {
                GPIO_write(GPIO_Num,0);
            }
            return;

        } else
            AddError(GPIO_ERR, "Invalid GPIO Action");
    } else if (GPIO_Num == 6 || GPIO_Num == 7) {

        if        (MatchSubString(MsgBuffPTR,"r"))
        {
            sprintf(MsgBuffer, "\r\nGPIO SW%d: %hhu\r\n", GPIO_Num-5, GPIO_read(GPIO_Num));
            UART_Write_Protected(MsgBuffer);
        }
        else if (MatchSubString(MsgBuffPTR,"w"))
            AddError(GPIO_ERR, "Cannot Write to Switch");
        else if (MatchSubString(MsgBuffPTR,"t"))
            AddError(GPIO_ERR, "Cannot Toggle Switch");
        else
            AddError(GPIO_ERR, "Invalid GPIO Action");
    }
    else
    {
        strcpy (MsgBuffer,MsgBreaker);
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"      GPIO LED0: %hhu\r\n", GPIO_read(CONFIG_GPIO_LED0     ));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"      GPIO LED1: %hhu\r\n", GPIO_read(CONFIG_GPIO_LED1     ));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"      GPIO LED2: %hhu\r\n", GPIO_read(CONFIG_GPIO_LED2     ));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"      GPIO LED3: %hhu\r\n", GPIO_read(CONFIG_GPIO_LED3     ));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer," GPIO AUDIO PWR: %hhu\r\n", GPIO_read(CONFIG_GPIO_AUDIO_PWR));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"   GPIO MIC PWR: %hhu\r\n", GPIO_read(CONFIG_GPIO_MIC_PWR  ));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"       GPIO SW1: %hhu\r\n", GPIO_read(CONFIG_GPIO_SW1      ));
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer,"       GPIO SW2: %hhu\r\n", GPIO_read(CONFIG_GPIO_SW2      ));
        UART_Write_Protected(MsgBuffer);
        strcpy (MsgBuffer,MsgBreaker);
        UART_Write_Protected(MsgBuffer);
    }
}



void TimerParse(char *ch){
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    int32_t TimerNum;
    int32_t index;

    index = global.MsgQueue.Read;
    if (ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if(StrBuffPTR == NULL){
        sprintf(MsgBuffer, "Timer Period: %d\r\n", global.Timer1.Period);
        UART_Write_Protected(MsgBuffer);
        return;
    }

    TimerNum = strtol(StrBuffPTR, NULL, 10);

    if (TimerNum >= 0) {
        if (TimerNum == 0)
            Timer_stop(global.Timer1.Handle);
        else if (TimerNum == 1)
            Timer_start(global.Timer1.Handle);
        else if (TimerNum >= 2 && TimerNum <= 100)
            AddError(TIMER_ERR, "Timer period must be > 100");
        else {
            // Set timer period (us)
            Timer_setPeriod(global.Timer1.Handle, Timer_PERIOD_US, TimerNum);
            global.Timer1.Period = TimerNum;
            sprintf(MsgBuffer, "Timer period set to: %d\r\n", global.Timer1.Period);
            UART_Write_Protected(MsgBuffer);
        }
    } else
        AddError(TIMER_ERR, "Timer Period must be > 0");
}

void CallbackParse(char *ch) {
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    int32_t index = global.MsgQueue.Read;
    int32_t CallbackNum = -1;
    int32_t Repetitions = -1;
    int     i;

    if (ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if (!StrBuffPTR) {
        UART_Write_Protected(MsgBreaker);
        for(i = 0; i < NUM_CALLBACKS; i++){
            sprintf(MsgBuffer, "Callback %d: REP:%3d, FUNC:%s\r\n", i, global.Callbacks.CallbackRep[i], global.Callbacks.Callback[i]);
            UART_Write_Protected(MsgBuffer);
        }
        UART_Write_Protected(MsgBreaker);
        return;
    }

    if(MatchSubString(StrBuffPTR, "clear") || MatchSubString(StrBuffPTR, "-clear")){
        global.Callbacks.CallbackRep[0]  = 0;
        global.Callbacks.CallbackRep[1]  = 0;
        global.Callbacks.CallbackRep[2]  = 0;
        global.Callbacks.CallbackRep[3]  = 0;
        for(i = 0; i < NUM_CALLBACKS; i++){
            memset(global.Callbacks.Callback[i], '\0', sizeof(global.Callbacks.Callback[i]));
        }
        strcpy(MsgBuffer, "Callbacks Cleared\r\n");
        UART_Write_Protected(MsgBuffer);
        return;
    }

    CallbackNum = strtol(StrBuffPTR, NULL, 10);
    if (CallbackNum < 0 || CallbackNum >= NUM_CALLBACKS) {
        AddError(CBACK_ERR, "Invalid Callback Num");
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (!StrBuffPTR) {
        sprintf(MsgBuffer, "Callback %d: REP:%d: FUNC:%s\r\n", CallbackNum, global.Callbacks.CallbackRep[CallbackNum], global.Callbacks.Callback[CallbackNum]);
        UART_Write_Protected(MsgBuffer);
        return;
    }

    Repetitions = strtol(StrBuffPTR, NULL, 10);
    StrBuffPTR = NextSubString(StrBuffPTR, false);

    if (!StrBuffPTR) {
        AddError(CBACK_ERR, "Missing Payload");
        return;
    }

    strcpy(global.Callbacks.Callback[CallbackNum], StrBuffPTR);
    global.Callbacks.CallbackRep[CallbackNum] = Repetitions;
    sprintf(MsgBuffer, "\r\nCallback %1d: %3d, %s\r\n", CallbackNum, global.Callbacks.CallbackRep[CallbackNum], global.Callbacks.Callback[CallbackNum]);
    UART_Write_Protected(MsgBuffer);
}



void AddPayload(char *payload){
    int32_t  writeindex = global.MsgQueue.Write;
    int32_t  nextindex;
    uint32_t gatekey;

    ti_sysbios_BIOS_ThreadType tType;
    tType = BIOS_getThreadType();

    if(!payload || payload[0] == 0){
        return; //Empty payload
    }

    if(tType != ti_sysbios_BIOS_ThreadType_Hwi){
        gatekey = GateSwi_enter(global.Bios.PayloadGate);
    }
    nextindex = writeindex+1;
    if(nextindex >= MsgQueueLen){
        nextindex = 0;
    }
    if(nextindex == global.MsgQueue.Read){
        GateSwi_leave(global.Bios.PayloadGate, gatekey);
        AddError(Q_OVFLW, "Queue Overflow");
    } else {
        strcpy(global.MsgQueue.MsgQueue[writeindex], payload);
        global.MsgQueue.Write = nextindex;
    }
    if (tType != ti_sysbios_BIOS_ThreadType_Hwi){
        GateSwi_leave(global.Bios.PayloadGate, gatekey);
    }
    Semaphore_post(global.Bios.QueueSemaphore);
}



void TickerParse(char *ch){
//  <ticker num> <delay> <period> <count> <payload>
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    int32_t index = global.MsgQueue.Read;
    int32_t TickerNum = -1;
    int32_t TickerDelay = -1;
    int32_t TickerPeriod = -1;
    int32_t TickerCount = -1;
    int     i;

    if (ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if (!StrBuffPTR){
        UART_Write_Protected(MsgBreaker);
        for(i = 0; i < NUM_TICKERS; i++){
            sprintf(MsgBuffer, "Ticker %2d: D:%4d, PRD:%4d, REP:%4d, FUNC:%s\r\n", i, global.Tickers.TickerDelay[i],global.Tickers.TickerPeriod[i],global.Tickers.TickerRepetitions[i],global.Tickers.TickerPayload[i]);
            UART_Write_Protected(MsgBuffer);
        }
        UART_Write_Protected(MsgBreaker);
        return;
    }

    if (MatchSubString(StrBuffPTR, "-clear") || MatchSubString(StrBuffPTR, "clear")){
        for(i = 0; i < NUM_TICKERS; i++){
            global.Tickers.TickerDelay[i]       = 0;
            global.Tickers.TickerPeriod[i]      = 0;
            global.Tickers.TickerRepetitions[i] = 0;
            memset(global.Tickers.TickerPayload[i], '\0', sizeof(global.Tickers.TickerPayload[i]));
        }
        return;
    }

    TickerNum = strtol(StrBuffPTR, NULL, 10);
    if (TickerNum < 0 || TickerNum >= NUM_TICKERS+1) {
        AddError(TICKER_ERR, "Invalid Ticker Number");
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (!StrBuffPTR) {
        sprintf(MsgBuffer, "\r\nTicker %2d: D:%4d, PRD:%4d, REP:%4d, FUNC:%s\r\n", TickerNum, global.Tickers.TickerDelay[TickerNum],global.Tickers.TickerPeriod[TickerNum],global.Tickers.TickerRepetitions[TickerNum],global.Tickers.TickerPayload[TickerNum]);
        AddError(TICKER_ERR, "Invalid Ticker Action");
        return;
    }

    TickerDelay = strtol(StrBuffPTR, NULL, 10);
    if (TickerDelay < 0) {
        AddError(TICKER_ERR, "Invalid Ticker Delay");
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    TickerPeriod = strtol(StrBuffPTR, NULL, 10);
    if (TickerPeriod < 0) {
        AddError(TICKER_ERR, "Invalid Ticker Period");
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    TickerCount = strtol(StrBuffPTR, NULL, 10);
    if (TickerCount < -1) {
        AddError(TICKER_ERR, " Invalid Ticker Repetitions");
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (!StrBuffPTR) {
        AddError(TICKER_ERR, "Missing Payload");
        return;
    }

    if (TickerNum == 16){
        for(i = 15; i > -1; i--){
            if(global.Tickers.TickerRepetitions[i]==0){
                TickerNum=i;
                break;
            }
        }
    }

    global.Tickers.TickerDelay[TickerNum] = TickerDelay;
    global.Tickers.TickerDelayShadow[TickerNum] = TickerDelay;
    global.Tickers.TickerPeriod[TickerNum] = TickerPeriod;
    global.Tickers.TickerPeriodShadow[TickerNum] = TickerPeriod;
    global.Tickers.TickerRepetitions[TickerNum] = TickerCount;
    strcpy(global.Tickers.TickerPayload[TickerNum], StrBuffPTR);
    sprintf(MsgBuffer, "\r\nTicker %2d: D:%4d, PRD:%4d, REP:%4d, FUNC:%s\r\n\r\n", TickerNum, global.Tickers.TickerDelay[TickerNum],global.Tickers.TickerPeriod[TickerNum],global.Tickers.TickerRepetitions[TickerNum],global.Tickers.TickerPayload[TickerNum]);
    UART_Write_Protected(MsgBuffer);
}



void RegParse(char *ch){
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    char    *OperatorPTR;
    int32_t index = global.MsgQueue.Read;
    int32_t DestNum = -1;
    int32_t SourceA = -1;
    int16_t Atype = 0;
    uint32_t Aval = 0;
    int32_t SourceB = -1;
    int16_t Btype = 0;
    uint32_t Bval = 0;
    int32_t OperatorNum = 0;
    int     i;

    /*
     * -reg <DST> <OP> <SRCA> <SRCB>
     *  Operations:
     *  = -> Set  (From Register), x -> Exchange
     *  + -> add                 , ++ -> increment, - -> subtract, -- -> decrement
     *  ` -> NOT                 , & -> AND       , | -> OR      , _| -> NOR      , x| -> XOR
     *  * -> Multiply            , / -> Division  , % -> Remainder
     *  > -> Max                 , < -> Min
     *
     *                           Types:0 (normal)
     *  # Immediate                    1
     *  #x hexadecimal immediate       2
     *  @ direct memory addressing     3
     *
     */

    if (ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if (!StrBuffPTR){
        UART_Write_Protected(MsgBreaker);
        for(i = 0; i < NUM_REGS/2; i++){
            sprintf(MsgBuffer, "Reg %2d: %9u | (0x%08x)  |  Reg %2d: %9u | (0x%08x)\r\n", 
                i, global.Regs.Reg[i], global.Regs.Reg[i], 
                i+16, global.Regs.Reg[i+16], global.Regs.Reg[i+16]);
            UART_Write_Protected(MsgBuffer);
        }
        UART_Write_Protected(MsgBreaker);
        return;
    }
    if (MatchSubString(StrBuffPTR, "-clear") || MatchSubString(StrBuffPTR, "clear")){
        memset(global.Regs.Reg, 0, sizeof(global.Regs.Reg));
        return;
    }
    //Destination
    if(*StrBuffPTR == '#' || *StrBuffPTR == '@'){
        AddError(REG_ERR, "Invalid Destination Addressing Type");
        return;
    }
    DestNum = strtoul(StrBuffPTR, NULL, 10);
    if (DestNum < 0 || DestNum >= NUM_REGS) {
        AddError(REG_ERR, "Invalid Register Num");
        return;
    }
    //Operator
    StrBuffPTR = NextSubString(StrBuffPTR, false);
    OperatorPTR = StrBuffPTR;

    //Source A addressing parsing
    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if(*StrBuffPTR == '#'){
        StrBuffPTR++;
        if(*StrBuffPTR == 'x'){
            //Set to hexadecimal immediate
            Atype = 2;
        }
        else{
            //Set to immediate
            Atype = 1;
        }
        StrBuffPTR--;
    } else if(*StrBuffPTR == '@'){
        //Set to direct addressing
        Atype = 3;
    } else {
        Atype = 0;
    }
    switch(Atype){
        case 0:{
            //Register Addressing
            SourceA = strtoul(StrBuffPTR, NULL, 10);
            Aval = SourceA;
            if (Aval < 0 || Aval >= NUM_REGS) {
                AddError(REG_ERR, "Invalid Register Number");
                return;
            }
            Aval = global.Regs.Reg[Aval];
            break;
        }
        case 1:{
            StrBuffPTR++;
            Aval = strtoul(StrBuffPTR, NULL, 10);
            break;
        }
        case 2:{
            StrBuffPTR += 2;
            Aval = strtoul(StrBuffPTR, NULL, 16);
            break;
        }
        case 3:{
            StrBuffPTR++;
            if (*StrBuffPTR == '0' && (*(StrBuffPTR + 1) == 'x' || *(StrBuffPTR + 1) == 'X')) {
                Aval = strtoul(StrBuffPTR, NULL, 16);
            } else if(isdigit(*StrBuffPTR)) {
                int16_t reg = strtoul(StrBuffPTR, NULL, 10);
                if(reg >= NUM_REGS || reg < 0){
                    AddError(REG_ERR, "Invalid Register");
                    return;
                }
                Aval = global.Regs.Reg[reg];
            }
            if ((Aval >= 0x00100000 && Aval < 20000000) || (Aval >= 0x20040000)){
                AddError(REG_ERR, "Invalid Memory Address");
                return;
            }
            uint32_t *DirectAddress = (uint32_t *)Aval;
            Aval = *DirectAddress;
            break;
        }
        default:{
            AddError(REG_ERR, "Invalid Addressing Type");
            return;
        }
    }

    //Source B
    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if(*StrBuffPTR == '#'){
        StrBuffPTR++;
        if(*StrBuffPTR == 'x'){
            //Set to hexadecimal immediate
            Btype = 2;
        }
        else{
            //Set to immediate
            Btype = 1;
        }
        StrBuffPTR--;
    } else if(*StrBuffPTR == '@'){
        //Set to direct addressing
        Btype = 3;
    } else {
        Btype = 0;
    }

    switch(Btype){
        case 0:{
            //Register Addressing
            SourceB = strtoul(StrBuffPTR, NULL, 10);
            Bval = SourceB;
            if (Bval < 0 || Bval >= NUM_REGS) {
                AddError(REG_ERR, "Invalid Register Number");
                return;
            }
            Bval = global.Regs.Reg[Bval];
            break;
        }
        case 1:{
            StrBuffPTR++;
            Bval = strtoul(StrBuffPTR, NULL, 10);
            break;
        }
        case 2:{
            StrBuffPTR += 2;
            Bval = strtoul(StrBuffPTR, NULL, 16);
            break;
        }
        case 3:{
            StrBuffPTR++;
            if (*StrBuffPTR == '0' && (*(StrBuffPTR + 1) == 'x' || *(StrBuffPTR + 1) == 'X')) {
                Bval = strtoul(StrBuffPTR, NULL, 16);
            } else if(isdigit(*StrBuffPTR)) {
                int16_t reg = strtoul(StrBuffPTR, NULL, 10);
                if(reg >= NUM_REGS || reg < 0){
                    AddError(REG_ERR, "Invalid Register");
                    return;
                }
                Bval = global.Regs.Reg[reg];
            }

            if ((Bval >= 0x00100000 && Bval < 20000000) || (Bval >= 0x20040000)) {
                AddError(REG_ERR, "Invalid Memory Address");
                return;
            }
            uint32_t *DirectAddress = (uint32_t *)Aval;
            Bval = *DirectAddress;
            break;
        }
        default:{
            AddError(REG_ERR, "Invalid Addressing Type");
            return;
        }
    }

    //Operator Parsing
    while(*OperatorPTR != ' ' && *OperatorPTR != '\0'){
        OperatorNum += *OperatorPTR;
        OperatorPTR++;
    }
    if(OperatorNum == 0){
        goto Print;
    }
    switch (OperatorNum) {
        case 61: { // "=" Move
            global.Regs.Reg[DestNum] = Aval;
            break;
        }
        case 120: { // "x" Exchange
            uint32_t temp = global.Regs.Reg[DestNum];
            global.Regs.Reg[DestNum] = global.Regs.Reg[SourceA];
            global.Regs.Reg[SourceA] = temp;
            break;
        }
        case 43: { // "+" Addition
            global.Regs.Reg[DestNum] = Aval + Bval;
            break;
        }
        case 86: { // "V" (assuming "++")
            global.Regs.Reg[DestNum]++;
            break;
        }
        case 45: { // "-" Subtraction
            global.Regs.Reg[DestNum] = Aval - Bval;
            break;
        }
        case 90: { // "Z" (assuming "--")
            global.Regs.Reg[DestNum]--;
            break;
        }
        case 42: { // "*" Multiplication
            global.Regs.Reg[DestNum] = Aval * Bval;
            break;
        }
        case 47: { // "/" Division
            if (Bval == 0) {
                AddError(DIV_ZERO, "Division By Zero");
                return;
            }
            global.Regs.Reg[DestNum] = Aval / Bval;
            break;
        }
        case 37: { // "%" Remainder
            if (Bval == 0) {
                AddError(DIV_ZERO, "Division By Zero");
                return;
            }
            global.Regs.Reg[DestNum] = Aval % Bval;
            break;
        }
        case 124: { // "|" OR
            global.Regs.Reg[DestNum] = Aval | Bval;
            break;
        }
        case 38: { // "&" AND
            global.Regs.Reg[DestNum] = Aval & Bval;
            break;
        }
        case 244: { // "x|" XOR
            global.Regs.Reg[DestNum] = Aval ^ Bval;
            break;
        }
        case 126: { // "~" NOT (Unary operation)
            global.Regs.Reg[DestNum] = ~Aval;
            break;
        }
        case 219: { // "_|" NOR
            global.Regs.Reg[DestNum] = ~(Aval | Bval);
            break;
        }
        case 62: { // ">" Max
            global.Regs.Reg[DestNum] = (Aval > Bval) ? Aval : Bval;
            break;
        }
        case 60: { // "<" Min
            global.Regs.Reg[DestNum] = (Aval < Bval) ? Aval : Bval;
            break;
        }
        default: {
            AddError(REG_ERR, "Invalid Operator");
            return;
        }
    }
    Print:
    sprintf(MsgBuffer, "Reg %2d: %9u | (0x%08x)\r\n", DestNum, global.Regs.Reg[DestNum], global.Regs.Reg[DestNum]);
    UART_Write_Protected(MsgBuffer);
}



void ScriptsParse(char *ch){
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    int32_t index = global.MsgQueue.Read;
    int     i;

    /*
    * x -> Executes Script | r -> Read Script | w -> Write Script
    */

    if (ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if (!StrBuffPTR){
        UART_Write_Protected(MsgBreaker);
        for(i = 0; i < NUM_SCRIPTS; i++){
            sprintf(MsgBuffer, "Script %2d: %s\r\n", i, global.Scripts.Script[i]);
            UART_Write_Protected(MsgBuffer);
        }
        UART_Write_Protected(MsgBreaker);
        return;
    }
    if (MatchSubString(StrBuffPTR, "-clear") || MatchSubString(StrBuffPTR, "clear")){
        memset(global.Scripts.Script, '\0', sizeof(global.Scripts.Script));
        return;
    }

    //Script Num
    int16_t ScriptNum = strtol(StrBuffPTR, NULL, 10);
    if (ScriptNum >= NUM_SCRIPTS || ScriptNum < 0){
        AddError(SCRIPT_ERR, "Invalid Script Number");
        return;
    }
    StrBuffPTR = NextSubString(StrBuffPTR, false);
    //Script Actions
    if       (tolower(*StrBuffPTR) == 'x'){
        char *ScriptPTR = global.Scripts.Script[ScriptNum];
        while(*ScriptPTR != '\0' && !(ScriptNum>=64)){
            if(Semaphore_getCount(global.Bios.QueueSemaphore)>=16){
                sprintf(MsgBuffer,"-script %d x",ScriptNum);
                AddPayload(MsgBuffer);
                return;
            }
            if(MatchSubString(ScriptPTR, "-if")){
                strcpy(MsgBuffer, ScriptPTR);
                AddPayload(MsgBuffer);
                break;
            }
            strcpy(MsgBuffer, ScriptPTR);
            AddPayload(MsgBuffer);
            ScriptNum++;
            ScriptPTR = global.Scripts.Script[ScriptNum];
        }
        return;
    } else if(tolower(*StrBuffPTR) == 'r'){
        sprintf(MsgBuffer, "Script %2d: %s\r\n", ScriptNum, global.Scripts.Script[ScriptNum]);
        UART_Write_Protected(MsgBuffer);
        return;
    } else if(tolower(*StrBuffPTR) == 'w'){
        StrBuffPTR = NextSubString(StrBuffPTR, false);
        strcpy(global.Scripts.Script[ScriptNum],StrBuffPTR);
        //Script Print
        sprintf(MsgBuffer, "Script %2d: %s\r\n", ScriptNum, global.Scripts.Script[ScriptNum]);
        UART_Write_Protected(MsgBuffer);
        return;
    } else {
        AddError(SCRIPT_ERR, "Invalid Script Action");
        return;
    }

}




void IfParse(){
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    int32_t index = global.MsgQueue.Read;

/*
 *  Syntax: if RegA COND RegB ? DESTT : DESTF
 *  CONDs: > = <
 */

    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);
    if(!StrBuffPTR){
        strcpy(MsgBuffer, "No conditions supplied\r\n");
        UART_Write_Protected(MsgBuffer);
    }
    //Condition parsing
    int32_t Aval = 0;
    if(*StrBuffPTR == '#'){
        StrBuffPTR++;
        Aval = strtol(StrBuffPTR, NULL, 10);
    } else if (isdigit(*StrBuffPTR)){
        Aval = strtol(StrBuffPTR, NULL, 10);
        Aval = global.Regs.Reg[Aval];
    } else {
        AddError(IF_ERR, "No Condition Specified");
        return;
    }
    int16_t CondType = -1;
    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if(*StrBuffPTR == '>'){
        CondType = 1;
    } else if(*StrBuffPTR == '<'){
        CondType = 2;
    } else if(*StrBuffPTR == '='){
        CondType = 3;
    } else {
        AddError(IF_ERR, "No Operator Specified");
        return;
    }

    int32_t Bval = 0;
    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if(*StrBuffPTR == '#'){
        StrBuffPTR++;
        Bval = strtol(StrBuffPTR, NULL, 10);
    } else if (isdigit(*StrBuffPTR)){
        Bval = strtol(StrBuffPTR, NULL, 10);
        Bval = global.Regs.Reg[Bval];
    } else {
        AddError(IF_ERR, "No Condition Specified");
        return;
    }

    switch(CondType){
        case 1:{// >
            if(Aval > Bval)
                CondType = 1;
            else
                CondType = 0;
            break;
        }
        case 2:{// <
            if(Aval < Bval)
                CondType = 1;
            else
                CondType = 0;
            break;
        }
        case 3:{// =
            if(Aval == Bval)
                CondType = 1;
            else
                CondType = 0;
            break;
        }
        default:{
            //Things Cond Type didnt get set (This shouldnt happen because the cond-type else statement
            return;
        }
    }

    switch(CondType){
        case 0:{
            while(*StrBuffPTR != '-' && *StrBuffPTR != '\0'){
                StrBuffPTR = NextSubString(StrBuffPTR, false);
            }
            StrBuffPTR = NextSubString(StrBuffPTR, false);
            while(*StrBuffPTR != '-' && *StrBuffPTR != '\0'){
                StrBuffPTR = NextSubString(StrBuffPTR, false);
            }
            if(*StrBuffPTR != '-'){
                AddError(IF_ERR, "Invalid Payload");
                return;
            }
            int32_t index = 0;
            while(*StrBuffPTR != '\0'){
                MsgBuffer[index] = *StrBuffPTR;
                index++;
                StrBuffPTR++;
            }
            AddPayload(MsgBuffer);
            break;
        }
        case 1:{
            while(*StrBuffPTR != '-' && *StrBuffPTR != '\0'){
                StrBuffPTR = NextSubString(StrBuffPTR, false);
                if(*StrBuffPTR == ':'){
                    AddError(IF_ERR, "Invalid Payload");
                    return;
                }
            }
            int32_t index = 0;
            while(*StrBuffPTR != ':' && *StrBuffPTR != '\0'){
                MsgBuffer[index] = *StrBuffPTR;
                index++;
                StrBuffPTR++;
            }
            AddPayload(MsgBuffer);
            break;
        }
    }
}



void UARTParse(){
    char    MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char    *StrBuffPTR;
    char    ch = '\r';
    int32_t index;
    int     length;

    index = global.MsgQueue.Read;
    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);
    strcpy(MsgBuffer, StrBuffPTR);
    strncat(MsgBuffer, &ch, 1);
    length = strlen(MsgBuffer);
    UART_write(global.uart7, MsgBuffer, length);
}



void SineParse(char *ch){
    SPI_Transaction spiTransaction;
    bool            transferOK;
    char            *StrBuffPTR;
    double          frequency;
    uint16_t        lowerIndex;
    uint16_t        upperIndex;
    double          lowerWeight;
    double          upperWeight;
    double          answer;
    uint16_t        outval;

    int32_t index = global.MsgQueue.Read;

    if (ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if(global.Timer1.Period != 125){
        TimerParse("-timer 125");
    }
    if(StrBuffPTR && StrBuffPTR[0] != 0 && global.Timer1.Period > 0){
        if(isdigit(*StrBuffPTR) == 0){
            AddError(SINE_ERR, "Missing Frequency Value");
            return;
        }
        frequency = atoi(StrBuffPTR);
        global.LUTCtrl.lutDelta = (double) frequency * (double) LUT_SIZE * (double) global.Timer1.Period/1000000.0;
    }

    if(global.LUTCtrl.lutDelta >= LUT_SIZE/2){
        global.LUTCtrl.lutDelta = 0;
        AddError(SINE_ERR, "Nyquist Violation");
        TimerParse("-timer 0");
        return;
    }
    if(global.LUTCtrl.lutDelta <= 0){
        global.LUTCtrl.lutDelta = 0;
        if(global.Timer1.Period > 0){
            TimerParse("-timer 0");
            CallbackParse("-callback 0 0");
        }
        AddPayload("-print Timer 0 is off");
        return;
    }
    if(StrBuffPTR){
        GPIOParse("-gpio 4 w 0");
        CallbackParse("-callback 0 -1 -sine");
        TimerParse("-timer 1");
        return;
    }

    lowerIndex = (uint32_t) global.LUTCtrl.lutPosition;
    upperIndex = lowerIndex + 1;
    upperWeight = global.LUTCtrl.lutPosition - (double) lowerIndex;
    lowerWeight = 1 - upperWeight;
    answer = (double) sinlut14[lowerIndex] * (double) lowerWeight + (double) sinlut14[upperIndex] * (double) upperWeight;
    outval = round(answer);

    spiTransaction.count = 1;
    spiTransaction.txBuf = (void *) &outval;
    spiTransaction.rxBuf = (void *) NULL;
    transferOK = SPI_transfer(global.SPI_3, &spiTransaction);
    if(!transferOK){
        UART_Write_Protected("SPI Transfer ERROR");
    }

    global.LUTCtrl.lutPosition += global.LUTCtrl.lutDelta;
    while(global.LUTCtrl.lutPosition >= (double) LUT_SIZE){
        global.LUTCtrl.lutPosition -= (double) LUT_SIZE;
    }

}



void VoiceParse(char *ch){
//
//    -VoiceParse
//    move 128 samples from message buffer to TX ping/pong MsgBufferSize
//    knows local vs long distance by -reg contents
//    makes -VoiceParse
//    or
//    makes -netudp -VoiceParse
//    local and long distance have same number of memcpy
//
    int32_t dest_choice;
    int32_t bufflen;
    int32_t TX01;
    int32_t current;
    uint16_t  *dest;
    char    *StrBuffPTR;
//    char posbuf[100];
    static int32_t last[2] = {-2, -2};
    static int32_t lastlast[2] = {-4, -4};

    StrBuffPTR = NextSubString(ch,true);

    if(!StrBuffPTR)
        return;

    dest_choice = atoi(StrBuffPTR);

    StrBuffPTR = NextSubString(StrBuffPTR, true);

    bufflen = atoi(StrBuffPTR);

    if(bufflen != DATABLOCKSIZE){
        AddError(VOICE_ERR, "Blocksize Error");
        return;
    }
    StrBuffPTR++;
    StrBuffPTR++;
    StrBuffPTR++;
    StrBuffPTR++;
    StrBuffPTR++;
    StrBuffPTR++;

    if(dest_choice == 0){
        TX01 = 0;
        dest = global.TXBufCtrl[TX01].TX_Ping;
    }
    else if(dest_choice == 1){
        TX01 = 0;
        dest = global.TXBufCtrl[TX01].TX_Pong;
    }
    else if(dest_choice == 2){
        TX01 = 1;
        dest = global.TXBufCtrl[TX01].TX_Ping;
    }
    else if(dest_choice == 3){
        TX01 = 1;
        dest = global.TXBufCtrl[TX01].TX_Pong;
    }
    else{
        AddError(VOICE_ERR, "Destination Choice Error");
        return;
    }

    memcpy(dest, StrBuffPTR, sizeof(uint16_t)*DATABLOCKSIZE);

    if(global.TXBufCtrl[TX01].TX_Completed == NULL)
    {
        global.TXBufCtrl[TX01].TX_Completed = dest;
        global.TXBufCtrl[TX01].TX_index = 0;
    }

    current = global.TXBufCtrl[TX01].TX_index;
    if(last[TX01] != current && lastlast[TX01] != current)
    {
        lastlast[TX01] = last[TX01];
        last[TX01] = current;
        if(current >= DATABLOCKSIZE - DATADELAY + 4){
            global.TXBufCtrl[TX01].TX_correction = -1;
        }
        else if( current <= DATABLOCKSIZE - DATADELAY - 4){
            global.TXBufCtrl[TX01].TX_correction = +1;
        }
    }
}



void AudioParse(){
    /**
     * Parses audio data and sends it via SPI.
     *
     * This function iterates through the global TX buffer control structure, 
     * processes the audio data, and sends the processed data via SPI. 
     * It handles delays, index corrections, and buffer switching between 
     * Ping and Pong buffers. If the SPI transfer fails, the function enters 
     * an infinite loop.
     */

    SPI_Transaction spiTransaction;
    bool transferOK;
    int32_t i;
    uint16_t outval = 0;

    for(i = 0; i < TXBUFCOUNT; i++){
        if(global.TXBufCtrl[i].TX_Completed != NULL){
            if(global.TXBufCtrl[i].TX_index >= 0){
                if(global.TXBufCtrl[i].TX_delay > 0){
                    global.TXBufCtrl[i].TX_delay--;
                    return;
                }
                outval += global.TXBufCtrl[i].TX_Completed[global.TXBufCtrl[i].TX_index++];

                global.TXBufCtrl[i].TX_index += global.TXBufCtrl[i].TX_correction;
                global.TXBufCtrl[i].TX_correction = 0;

                if(global.TXBufCtrl[i].TX_index >= DATABLOCKSIZE){
                    global.TXBufCtrl[i].TX_index = 0;
                    if(global.TXBufCtrl[i].TX_Completed == global.TXBufCtrl[i].TX_Ping){
                        global.TXBufCtrl[i].TX_Completed = global.TXBufCtrl[i].TX_Pong;
                    }
                    else{
                        global.TXBufCtrl[i].TX_Completed = global.TXBufCtrl[i].TX_Ping;
                    }
                }
            }
        }
    }
    spiTransaction.count = 1;
    spiTransaction.txBuf = (void *) &outval;
    spiTransaction.rxBuf = (void *) NULL;
    transferOK = SPI_transfer(global.SPI_3, &spiTransaction);
    if(!transferOK){
        while(1);
    }
}




void StreamParse(char *ch){
    /**
     * Parses the input stream and controls the ADC buffer conversion state.
     *
     * This function processes the input character stream to determine the desired
     * ADC buffer conversion state (0, 1, or 2). It updates the global ADC buffer
     * control structure based on the parsed intent and manages the state transitions
     * including starting, stopping, and configuring the ADC buffer and related components.
     *
     * param ch Pointer to the input character stream. If NULL, the function uses
     *          the message from the global message queue.
     */
    char *StrBuffPTR;
    uint32_t intent;
    uint32_t i;

    uint32_t index = global.MsgQueue.Read;

    if(ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    if(!StrBuffPTR){
        switch(global.ADCBufCtrl.converting){
            case 0: {
                intent = 1;
                break;
            }
            case 1: {
                intent = 2;
                break;
            }
            case 2: {
                intent = 0;
                break;
            }
        }
    }
    else{
        switch(*StrBuffPTR){
            case '2':{
                intent = 2;
                break;
            }
            case '1':
            case 't':{
                intent = 1;
                break;
            }
            case '0':
            case 'f':{
                intent = 0;
                break;
            }
        }
    }
    if(intent == global.ADCBufCtrl.converting){
        return;
    }

    if(intent == 0){
        if(global.ADCBufCtrl.converting == 2){
            if(ADCBuf_convertCancel(global.ADCBuf.Handle) != ADCBuf_STATUS_SUCCESS){
                AddError(STREAM_ERR, "ADCBuf Status Wrong");
            }
            global.ADCBufCtrl.converting = 0;
            if(global.LUTCtrl.lutDelta > 0.0){
                SineParse("-sine 0");
            }
            CallbackParse("-callback 0 0");
            TimerParse("-timer 0");
            global.ADCBufCtrl.RX_Completed = NULL;
            for(i = 0; i < TXBUFCOUNT; i++){
                global.TXBufCtrl[i].TX_Completed = NULL;
                global.TXBufCtrl[i].TX_index = -1;
            }
        }
    }
    else if (intent == 1 && global.ADCBufCtrl.converting == 0){
        GPIOParse("-gpio 4 w 0");
        GPIOParse("-gpio 5 w 1");
        CallbackParse("-callback 0 -1 -audio");
        TimerParse("-timer 125");
        TimerParse("-timer 1");
        global.ADCBufCtrl.converting = 1;
        TickerParse("-ticker 16 50 0 1 -stream 2");
        ClearAudioBuffers();
    }
    else if(intent == 2 && global.ADCBufCtrl.converting == 1){
        if(ADCBuf_convert(global.ADCBuf.Handle, &global.ADCBufCtrl.conversion, 1) != ADCBuf_STATUS_SUCCESS){
            AddError(STREAM_ERR, "ADCBuf Status Wrong");
        }
        else{
            global.ADCBufCtrl.converting = 2;
            global.ADCBufCtrl.RX_Completed = NULL;
            for(i = 0; i < TXBUFCOUNT; i++){
                global.TXBufCtrl[i].TX_Completed = NULL;
                global.TXBufCtrl[i].TX_index = -1;
                global.TXBufCtrl[i].TX_delay = DATADELAY;
                global.TXBufCtrl[i].TX_correction = 0;
            }
        }
    }

}



void ClearAudioBuffers(){
    int i = 0;
    int j = 0;
    for(i = 0; i < DATABLOCKSIZE; i++){
        global.ADCBufCtrl.RX_Ping[i] = 0;
        global.ADCBufCtrl.RX_Pong[i] = 0;
    }
    for(i = 0; i < TXBUFCOUNT; i++){
        for(j = 0; j < DATABLOCKSIZE; j++){
            global.TXBufCtrl[i].TX_Ping[j] = 0;
            global.TXBufCtrl[i].TX_Pong[j] = 0;
        }
    }
}



void ParseNetUDP(char *ch, int32_t binaryCount){
    char *StrBuffPTR;
    int32_t  payloadnext;
    uint32_t gateKey;
    int32_t index = global.MsgQueue.Read;

    if(ch != NULL)
        StrBuffPTR = NextSubString(ch,false);
    else
        StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);

    gateKey = GateSwi_enter(global.Bios.NetworkGate);
    payloadnext = global.NetOutQ.payloadWriting + 1;
    if(payloadnext >= NetQueueLen)
        payloadnext = 0;
    if(payloadnext == global.NetOutQ.payloadReading){
        GateSwi_leave(global.Bios.NetworkGate, gateKey);
        AddError(NETWORK_ERR, "Network Queue Overflow");
        return;
    }

    memcpy(global.NetOutQ.payloads[global.NetOutQ.payloadWriting], StrBuffPTR, strlen(StrBuffPTR) + binaryCount + 1);
    global.NetOutQ.binaryCount[global.NetOutQ.payloadWriting] = binaryCount;
    global.NetOutQ.payloadWriting = payloadnext;
    GateSwi_leave(global.Bios.NetworkGate, gateKey);
    Semaphore_post(global.Bios.NetSemaphore);

}

void MsgParser() {
    char    *payload;
    char    MsgBuffer[MsgBufferSize];
    int32_t index;
    char *ch = NULL;
    index   = global.MsgQueue.Read;
    payload = global.MsgQueue.MsgQueue[index];

      if      (MatchSubString(payload, "-help"    ))
         HelpParse();
      else if (MatchSubString(payload, "-about"   ))
          AboutMsg();
      else if (MatchSubString(payload, "-clear"   ))
          ClearMsg();
      else if (MatchSubString(payload, "-print"   ))
          PrintMsg();
      else if (MatchSubString(payload, "-memr"    ))
           MemRead();
      else if (MatchSubString(payload, "-gpio"    ))
          GPIOParse(ch);
      else if (MatchSubString(payload, "-error"   ))
          ErrorMsg();
      else if (MatchSubString(payload, "-timer"   ))
          TimerParse(ch);
      else if (MatchSubString(payload, "-callback"))
          CallbackParse(ch);
      else if (MatchSubString(payload, "-ticker"  ))
          TickerParse(ch);
      else if (MatchSubString(payload, "-reg"     ))
          RegParse(ch);
      else if (MatchSubString(payload, "-script"  ))
          ScriptsParse(ch);
      else if (MatchSubString(payload, "-rem"     ))
          PrintMsg();
      else if (MatchSubString(payload, "-if"      ))
          IfParse();
      else if (MatchSubString(payload, "-uart"    ))
          UARTParse();
      else if (MatchSubString(payload, "-sine"    ))
          SineParse(ch);
      else if (MatchSubString(payload, "-stream"  ))
        StreamParse(ch);
      else if (MatchSubString(payload, "-netudp"  ))
        ParseNetUDP(ch,0);
      else if (MatchSubString(payload, "\r\n"     )) {
          strcpy(MsgBuffer, "\r\n");
          UART_Write_Protected(MsgBuffer);
    } else
          InvalidMsg();
}
