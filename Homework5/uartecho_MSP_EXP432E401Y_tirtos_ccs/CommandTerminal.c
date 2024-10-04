/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



/*
 * =============== UART Thread =========================
 */
void UART_Thread() //Priority 4
{
    char  input;

    if(global.Bios.PayloadGate == NULL){
        while(1); //Failed to create WriteGate Swi
    }

    while (1) {
        UART_read(global.uart, &input, 1);
        UART_write(global.uart, &input, 1);
        UART_Input_Handler(input);
    }
}

/*
 * =============== AddPayload ============================
 */

void AddPayload(char *payload){
    int32_t writeindex = global.MsgQueue.Write;
    int32_t nextindex;
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
        global.Error.QueueOverflow++;
    } else {
        strcpy(global.MsgQueue.MsgQueue[writeindex], payload);
        global.MsgQueue.Write = nextindex;
    }
    if (tType != ti_sysbios_BIOS_ThreadType_Hwi){
        GateSwi_leave(global.Bios.PayloadGate, gatekey);
    }
    Semaphore_post(global.Bios.QueueSemaphore);
}

/*
 * =============== Payload Thread ========================
 */

void Payload_Thread(){
    int32_t nextindex;
    int32_t index;
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

/*
 * =============== SWI ============================================
 */



/*
 * =============== First Layer Parser Functions & Messages ========
 */

void HelpParse() {
    char *SubStrPtr;
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int32_t index;

    index = global.MsgQueue.Read;

    SubStrPtr = NextSubString(global.MsgQueue.MsgQueue[index], false);
    if (SubStrPtr != NULL){
        if        (MatchSubString(SubStrPtr,    "-help" ) || MatchSubString(SubStrPtr,"help" )){
             HelpHelpMsg();
        } else if (MatchSubString(SubStrPtr,   "-about" ) || MatchSubString(SubStrPtr,"about")){
            HelpAboutMsg();
        } else if (MatchSubString(SubStrPtr,   "-print" ) || MatchSubString(SubStrPtr,"print")){
            HelpPrintMsg();
        } else if (MatchSubString(SubStrPtr,   "-clear" ) || MatchSubString(SubStrPtr,"clear")){
            HelpClearMsg();
        } else if (MatchSubString(SubStrPtr,    "-memr" ) || MatchSubString(SubStrPtr,"memr" )){
             HelpMemrMsg();
        } else if (MatchSubString(SubStrPtr,    "-gpio" ) || MatchSubString(SubStrPtr,"gpio" )){
             HelpGPIOMsg();
        } else if (MatchSubString(SubStrPtr,    "-error") || MatchSubString(SubStrPtr,"error")){
            HelpErrorMsg();
        } else if (MatchSubString(SubStrPtr,    "-timer") || MatchSubString(SubStrPtr,"timer")){
            HelpTimerMsg();
        } else if (MatchSubString(SubStrPtr, "-callback") || MatchSubString(SubStrPtr,"callback")){
            HelpCallbackMsg();
        } else if (MatchSubString(SubStrPtr,   "-ticker") || MatchSubString(SubStrPtr,"ticker")){
            HelpTickerMsg();
        } else {
            InvalidMsg();
        }

    } else {
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
        strcpy(MsgBuffer, "  **Note**    : Type -help <command> for more information\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, MsgBreaker);
        UART_Write_Protected(MsgBuffer);
    }
}

void AboutMsg() {
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

void ClearMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,"\033c");
    UART_write(global.uart, MsgBuffer,sizeof(MsgBuffer));
}

void PrintMsg(){
    int32_t index;
    index = global.MsgQueue.Read;

    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer,                          "\n\r");
    strcat(MsgBuffer,NextSubString(global.MsgQueue.MsgQueue[index],true));
    strcat(MsgBuffer,                          "\n\r");
    UART_Write_Protected(MsgBuffer);
}

void MemRead(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int32_t value;
    int32_t address;
    char *addressPTR;
    char *MsgBuffPTR;
    int32_t index;
    index = global.MsgQueue.Read;

    MsgBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);
    if(MsgBuffPTR == NULL){
        address = 0;
    } else {
        address = strtoul(MsgBuffPTR, &addressPTR, 16);
    }
    address = address & 0xFFFFFFF0;
    if((address >= 0x00100000 && address < 20000000) || (address >= 0x20040000)){
        goto BadAddress;
    }

    strcpy(MsgBuffer, "\r\n Memory Read: \r\n");
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer, "| %#010x | %#010x | %#010x | %#010x |\r\n",address+0xC,address+0x8,address+0x4,address+0x0);
    UART_Write_Protected(MsgBuffer);
    value = *(int32_t*) (address + 0xC);
    sprintf(MsgBuffer,"| %#010x | ",value);
    UART_Write_Protected(MsgBuffer);

    value = *(int32_t*) (address + 0x8);
    sprintf(MsgBuffer,"%#010x | ",value);
    UART_Write_Protected(MsgBuffer);

    value = *(int32_t*) (address + 0x4);
    sprintf(MsgBuffer,"%#010x | ",value);
    UART_Write_Protected(MsgBuffer);

    value = *(int32_t*) (address + 0x0);
    sprintf(MsgBuffer,"%#010x | \r\n",value);
    UART_Write_Protected(MsgBuffer);

    return;
    BadAddress:
    global.Error.InvalidAddress++;
    strcpy(MsgBuffer,"\r\nInvalid address, cannot be:");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,"\r\n0x00100000 <= Address < 0x20000000 or Address >= 0x20040000\r\n");
    UART_Write_Protected(MsgBuffer);
}

void GPIOParse() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int GPIO_Num = -1;
    char *MsgBuffPTR;
    int32_t index;
    index = global.MsgQueue.Read;

    MsgBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);
    if(MsgBuffPTR != NULL){
        if(isdigit(*MsgBuffPTR)){
            GPIO_Num = *MsgBuffPTR - '0';
        } else {
            strcpy(MsgBuffer, "\r\nSpecify Pin Number\r\n");
            UART_Write_Protected(MsgBuffer);
            global.Error.InvalidGPIOPin++;
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

            if        (MatchSubString(MsgBuffPTR,"1")) {
                GPIO_write(GPIO_Num,1);
            } else if (MatchSubString(MsgBuffPTR,"0")) {
                GPIO_write(GPIO_Num,0);
            } else{
                strcpy(MsgBuffer,  "\r\nSpecify Write Val\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            return;
        } else if (MatchSubString(MsgBuffPTR,"t")) {
            if(GPIO_read(GPIO_Num)==0){
                GPIO_write(GPIO_Num,1);
            } else {
                GPIO_write(GPIO_Num,0);
            }
            return;
        } else {
            strcpy(MsgBuffer,  "\r\nSpecify GPIO Action\r\n");
            UART_Write_Protected(MsgBuffer);
            global.Error.InvalidGPIOAction++;
        }
    } else if (GPIO_Num == 6 || GPIO_Num == 7) {

        if        (MatchSubString(MsgBuffPTR,"r")) {
            sprintf(MsgBuffer, "\r\nGPIO SW%d: %hhu\r\n", GPIO_Num-5, GPIO_read(GPIO_Num));
            UART_Write_Protected(MsgBuffer);

        } else if (MatchSubString(MsgBuffPTR,"w")) {
            strcpy(MsgBuffer, "\r\nCannot Write to Switch\r\n");
            UART_Write_Protected(MsgBuffer);
            global.Error.InvalidGPIOAction++;

        } else if (MatchSubString(MsgBuffPTR,"t")) {
            strcpy(MsgBuffer, "\r\nCannot Toggle Switch\r\n");
            UART_Write_Protected(MsgBuffer);
            global.Error.InvalidGPIOAction++;

        } else {
            strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
            UART_Write_Protected(MsgBuffer);
            global.Error.InvalidGPIOAction++;
        }
    } else {
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

void ErrorMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char *StrBuffPTR;
    int ErrorNum = -1;
    int32_t index;
    index = global.MsgQueue.Read;

    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index],false);
    if(MatchSubString(StrBuffPTR, "clear") || MatchSubString(StrBuffPTR, "-clear")){
        global.Error.InvalidCMD        = 0;
        global.Error.InputOverflow     = 0;
        global.Error.InvalidAddress    = 0;
        global.Error.InvalidGPIOPin    = 0;
        global.Error.InvalidGPIOAction = 0;
        global.Error.QueueOverflow     = 0;
        global.Error.InvalidCallbackAction = 0;
        global.Error.InvalidTickerAction = 0;
        global.Error.InvalidTimerAction= 0;

    } else if (isdigit(*StrBuffPTR)){
        ErrorNum = *StrBuffPTR - '0';
        switch(ErrorNum){
            case 0: {
                sprintf(MsgBuffer,"(0) Invalid Command         : %hhu\r\n",global.Error.InvalidCMD);
                break;
            }
            case 1: {
                sprintf(MsgBuffer,"(1) Input Overflow          : %hhu\r\n",global.Error.InputOverflow);
                break;
            }
            case 2: {
                sprintf(MsgBuffer,"(2) Invaild Address         : %hhu\r\n",global.Error.InvalidAddress);
                break;
            }
            case 3: {
                sprintf(MsgBuffer,"(3) Invalid GPIO Pin        : %hhu\r\n",global.Error.InvalidGPIOPin);
                break;
            }
            case 4: {
                sprintf(MsgBuffer,"(4) Invalid GPIO Action     : %hhu\r\n",global.Error.InvalidGPIOAction);
                break;
            }
            case 5: {
                sprintf(MsgBuffer,"(5) Queue Overflow          : %hhu\r\n",global.Error.QueueOverflow);
                break;
            }
            case 6: {
                sprintf(MsgBuffer,"(6) Invalid Callback Action : %hhu\r\n",global.Error.InvalidCallbackAction);
                break;
            }
            case 7: {
                sprintf(MsgBuffer,"(7) Invalid Ticker Action   : %hhu\r\n",global.Error.InvalidTickerAction);
                break;
            }
            case 8: {
                sprintf(MsgBuffer,"(8) Invalid  TimerAction    : %hhu\r\n",global.Error.InvalidTimerAction);
                break;
            }
            default: {
                sprintf(MsgBuffer,"\r\nError: Invalid error number\r\n");
                break;
            }
        }
        UART_Write_Protected(MsgBuffer);
        return;
    }
    strcpy (MsgBuffer,MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(0) Invalid Command       : %hhu\r\n",global.Error.InvalidCMD);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(1) Input Overflow        : %hhu\r\n",global.Error.InputOverflow);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(2) Invaild Address       : %hhu\r\n",global.Error.InvalidAddress);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(3) Invalid GPIO Pin      : %hhu\r\n",global.Error.InvalidGPIOPin);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(4) Invalid GPIO Action   : %hhu\r\n",global.Error.InvalidGPIOAction);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(5) Queue Overflow        : %hhu\r\n",global.Error.QueueOverflow);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(6) InvalidCallbackAction : %hhu\r\n",global.Error.InvalidCallbackAction);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(7) InvalidTickerAction   : %hhu\r\n",global.Error.InvalidTickerAction);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(8) InvalidTimerAction    : %hhu\r\n",global.Error.InvalidTimerAction);
    UART_Write_Protected(MsgBuffer);
    strcpy (MsgBuffer,MsgBreaker);
    UART_Write_Protected(MsgBuffer);

}

void TimerParse(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char *StrBuffPTR;
    int32_t TimerNum;
    int32_t index;
    index = global.MsgQueue.Read;

    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);
    if(StrBuffPTR == NULL){
        sprintf(MsgBuffer, "Timer Period: %d\r\n", global.Timer1.Period);
        UART_Write_Protected(MsgBuffer);
        return;
    }

    TimerNum = strtol(StrBuffPTR, NULL, 10);

    if (TimerNum >= 0) {
        if (TimerNum == 0) {
            // Stop timer
            Timer_stop(global.Timer1.Handle);
        } else if (TimerNum == 1) {
            // Start timer
            Timer_start(global.Timer1.Handle);
        } else if (TimerNum >= 2 && TimerNum <= 100) {
            // Period value too low
            strcpy(MsgBuffer, "Timer period must be > 100\r\n");
            UART_Write_Protected(MsgBuffer);
            global.Error.InvalidTimerAction++;
        } else {
            // Set timer period (us)
            Timer_setPeriod(global.Timer1.Handle, Timer_PERIOD_US, TimerNum);
            global.Timer1.Period = TimerNum;
            sprintf(MsgBuffer, "Timer period set to: %d\r\n", global.Timer1.Period);
            UART_Write_Protected(MsgBuffer);
        }
    } else {
        strcpy(MsgBuffer, "Period must be greater than 0");
        UART_Write_Protected(MsgBuffer);
        global.Error.InvalidTimerAction++;
    }
}

void CallbackParse() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char *StrBuffPTR;
    int32_t index = global.MsgQueue.Read;
    int32_t CallbackNum = -1;
    int32_t Repetitions = -1;
    int i;

    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);

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
        UART_Write_Protected("\r\nInvalid Callback Num\r\n");
        global.Error.InvalidCallbackAction++;
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
        UART_Write_Protected("\r\nMissing Payload\r\n");
        global.Error.InvalidCallbackAction++;
        return;
    }

    strcpy(global.Callbacks.Callback[CallbackNum], StrBuffPTR);
    global.Callbacks.CallbackRep[CallbackNum] = Repetitions;
    sprintf(MsgBuffer, "\r\nCallback %1d: %3d, %s\r\n", CallbackNum, global.Callbacks.CallbackRep[CallbackNum], global.Callbacks.Callback[CallbackNum]);
    UART_Write_Protected(MsgBuffer);
}

void TickerParse(){
//    <ticker num> <delay> <period> <count> <payload>
//  Add the num 16 source
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char *StrBuffPTR;
    int32_t index = global.MsgQueue.Read;
    int32_t TickerNum = -1;
    int32_t TickerDelay = -1;
    int32_t TickerPeriod = -1;
    int32_t TickerCount = -1;
    int i;

    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);
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
    if (TickerNum < 0 || TickerNum >= NUM_TICKERS) {
        UART_Write_Protected("\r\nInvalid Ticker Num\r\n");
        global.Error.InvalidTickerAction++;
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (!StrBuffPTR) {
        sprintf(MsgBuffer, "\r\nTicker %2d: D:%4d, PRD:%4d, REP:%4d, FUNC:%s\r\n", TickerNum, global.Tickers.TickerDelay[TickerNum],global.Tickers.TickerPeriod[TickerNum],global.Tickers.TickerRepetitions[TickerNum],global.Tickers.TickerPayload[TickerNum]);
        UART_Write_Protected(MsgBuffer);
        global.Error.InvalidTickerAction++;
        return;
    }

    TickerDelay = strtol(StrBuffPTR, NULL, 10);
    if (TickerDelay < 0) {
        UART_Write_Protected("\r\nInvalid Ticker Delay\r\n");
        global.Error.InvalidTickerAction++;
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    TickerPeriod = strtol(StrBuffPTR, NULL, 10);
    if (TickerPeriod < 0) {
        UART_Write_Protected("\r\nInvalid Ticker Period\r\n");
        global.Error.InvalidTickerAction++;
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    TickerCount = strtol(StrBuffPTR, NULL, 10);
    if (TickerCount < -1) {
        UART_Write_Protected("\r\nInvalid Ticker Repetitions\r\n");
        global.Error.InvalidTickerAction++;
        return;
    }

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (!StrBuffPTR) {
        UART_Write_Protected("\r\nMissing Payload\r\n");
        global.Error.InvalidTickerAction++;
        return;
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

void InvalidMsg() {
    global.Error.InvalidCMD++;
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int32_t index;
    index = global.MsgQueue.Read;

    global.MsgQueue.MsgQueue[index][15] = '\0';
    strcpy(MsgBuffer,  "\r\nInvalid Command: ");
    strcat(MsgBuffer,           global.MsgInput.MsgBuff);
    strcat(MsgBuffer,                   "\r\n");
    UART_Write_Protected(MsgBuffer);
}

/*
 * =============== SubString Functions ========
 */

/* MatchSubString compares msg2 with the first substring pointed to by msg1 */

bool MatchSubString(const char *msg1, const char *msg2) {
    while (*msg1 != '\0' && *msg2 != '\0' && *msg1 != ' ' && *msg2 != ' ') {
        if (*msg1 != *msg2) {
            return false;
        }
        msg1++;
        msg2++;
    }
    return *msg2 == '\0';
}

/* NextSubString moves a pointer to the next substring in a string */

char* NextSubString(char *msg, bool Print){
    char *index;
    if(msg == NULL){
        return NULL;
    }
    index = strchr(msg, ' ');
    if(!index){
        return NULL;
    }
    if(!Print){
        while(*index == ' '){
            index++;
        }
    } else {
        if(*index == ' '){
            index++;
        }
    }
    if(!*index){
        return NULL;
    }
    return index;
}

/*
 * =============== Initial Parser ========
 */

void MsgParser() {
    int32_t index;
    char *payload;
    char MsgBuffer[MsgBufferSize];
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
         GPIOParse();
    } else if (MatchSubString(payload, "-error"   )) {
          ErrorMsg();
    } else if (MatchSubString(payload, "-timer"   )) {
          TimerParse();
    } else if (MatchSubString(payload, "-callback")) {
          CallbackParse();
    } else if (MatchSubString(payload, "-ticker"  )) {
           TickerParse();
    } else if (MatchSubString(payload, "\r\n"     )) {
          strcpy(MsgBuffer, "\r\n");
          UART_Write_Protected(MsgBuffer);
    } else {
          InvalidMsg();
    }
}

/*
 * ========== Second Layer Parser Functions & Messages ========
 */


void HelpHelpMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -help\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Provides list of function descriptions\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpAboutMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -about\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Provides developer and version info\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpPrintMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -print\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Prints message after -print\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpClearMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -clear\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Clears the terminal\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpMemrMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command       : -memr\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description   : Prints memory address values\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location      : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Invalid Range : 0x00100000 < Address < 0x20000000 or Address > 0x20040000\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpGPIOMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -gpio <pin> <action>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Interacts with GPIO pins\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Pinout      : 0: LED0");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 1: LED1\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 2: LED2\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 3: LED3\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 4: AUDIO PWR\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 5: MIC PWR\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 6: SW1*\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 7: SW2*\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Actions     : r: read, w: write, t: toggle\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Notes       : * SW1 & SW2 are read-only & active low (pullup res) \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : -gpio (without arguments) prints list of GPIO values\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpErrorMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -error\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists number of errors since last reset\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Secondary arg -clear will reset error count\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg (0-8) will return specified error\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 0: Invalid CMD\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 1: InputOverflow\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 2: Invalid Address \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 3: Invalid GPIO Pin\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 4: Invalid GPIO Action\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 5: Queue Overflow\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 6: Invalid Callback Action\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 7: Invalid Ticker Action\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 8: Invalid Timer Action\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpTimerMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -timer\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists timer periods and configures hardware timers\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Secondary arg '0' will stop timer\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Secondary arg '1' will start timer\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg 101+ will set timer period in microseconds\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpCallbackMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -callback\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists and configures callbacks\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg -clear will reset all callback configurations\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Kill switch clears all tickers\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Callback Configuration:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : -callback <callback num> <repetitions> <payload>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : **Note:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : repetitions = -1 sets infinite repetitions\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Callback 0 is tied to timer1\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Callback 1 is tied to SW1\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Callback 2 is tied to SW2\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Callback 3 is not configured\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}

void HelpTickerMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -ticker\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists and configures ticker\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg -clear will reset all ticker configurations\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : ~ Kill switch clears all tickers\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Ticker Configuration:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : -callback <ticker num> <delay> <period> <repetitions> <payload>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}
