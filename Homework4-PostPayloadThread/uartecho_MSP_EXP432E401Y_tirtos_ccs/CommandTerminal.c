/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * =============== UART Thread ===============
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

    if(!payload || payload[0] == 0){
        return; //Empty payload
    }

    gatekey = GateSwi_enter(global.Bios.PayloadGate);
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
    GateSwi_leave(global.Bios.PayloadGate, gatekey);
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
        if        (MatchSubString(SubStrPtr, "-help" ) || MatchSubString(SubStrPtr,"help" )){
             HelpHelpMsg();
        } else if (MatchSubString(SubStrPtr,"-about" ) || MatchSubString(SubStrPtr,"about")){
            HelpAboutMsg();
        } else if (MatchSubString(SubStrPtr,"-print" ) || MatchSubString(SubStrPtr,"print")){
            HelpPrintMsg();
        } else if (MatchSubString(SubStrPtr,"-clear" ) || MatchSubString(SubStrPtr,"clear")){
            HelpClearMsg();
        } else if (MatchSubString(SubStrPtr, "-memr" ) || MatchSubString(SubStrPtr,"memr" )){
             HelpMemrMsg();
        } else if (MatchSubString(SubStrPtr, "-gpio" ) || MatchSubString(SubStrPtr,"gpio" )){
             HelpGPIOMsg();
        } else if (MatchSubString(SubStrPtr, "-error") || MatchSubString(SubStrPtr,"error")){
            HelpErrorMsg();
        } else {
            InvalidMsg();
        }

    } else {
        strcpy(MsgBuffer, MsgBreaker);
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -help\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Provides list of function descriptions\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -about\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Provides developer and version info\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -print\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Prints message after -print\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -clear\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Clears the terminal\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -memr\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Prints memory address values\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -gpio\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Interfaces with GPIO pins\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Command     : -error\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "              : Prints number of error occurrences\r\n\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "  Note        : Type -help <command> for more information\r\n");
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
    sprintf(MsgBuffer,                 " Assignment #: %s \r\n", Assignment);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Version %s.%s \r\n", Version, SubVersion);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Time: %s  Date: %s", __TIME__, __DATE__);
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
        sprintf(MsgBuffer,"       GPIO SW2: %hhu",     GPIO_read(CONFIG_GPIO_SW2      ));
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
    } else if (isdigit(*StrBuffPTR)){
        ErrorNum = *StrBuffPTR - '0';
        switch(ErrorNum){
            case 0: {
                sprintf(MsgBuffer,       "\r\nError %d (InvalidCMD): %u\r\n", ErrorNum, global.Error.InvalidCMD);
                break;
            }
            case 1: {
                sprintf(MsgBuffer,    "\r\nError %d (InputOverflow): %u\r\n", ErrorNum, global.Error.InputOverflow);
                break;
            }
            case 2: {
                sprintf(MsgBuffer,   "\r\nError %d (InvalidAddress): %u\r\n", ErrorNum, global.Error.InvalidAddress);
                break;
            }
            case 3: {
                sprintf(MsgBuffer,   "\r\nError %d (InvalidGPIOPin): %u\r\n", ErrorNum, global.Error.InvalidGPIOPin);
                break;
            }
            case 4: {
                sprintf(MsgBuffer,"\r\nError %d (InvalidGPIOAction): %u\r\n-", ErrorNum, global.Error.InvalidGPIOAction);
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
    sprintf(MsgBuffer,"(0) Invalid Command    : %hhu\r\n",global.Error.InvalidCMD);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(1) Input Overflow     : %hhu\r\n",global.Error.InputOverflow);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(2) Invaild Address    : %hhu\r\n",global.Error.InvalidAddress);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(3) Invalid GPIO Pin   : %hhu\r\n",global.Error.InvalidGPIOPin);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"(4) Invalid GPIO Action: %hhu",global.Error.InvalidGPIOAction);
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
    }
}


void CallbackParse() {
    // Format: -callback <callback num> <repetitions> <payload>
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    char *StrBuffPTR;
    int32_t index;
    int32_t CallbackNum = -1;
    int32_t Repetitions = -1;
    index = global.MsgQueue.Read;

    StrBuffPTR = NextSubString(global.MsgQueue.MsgQueue[index], false);

    if (StrBuffPTR == NULL) {
        sprintf(MsgBuffer, MsgBreaker);
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer, "Callbacks:\r\n");
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer, "Callback 0: %d, %s\r\n", global.Callbacks.Callback0Rep, global.Callbacks.Callback0);
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer, "Callback 1: %d, %s\r\n", global.Callbacks.Callback1Rep, global.Callbacks.Callback1);
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer, "Callback 2: %d, %s\r\n", global.Callbacks.Callback2Rep, global.Callbacks.Callback2);
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer, "Callback 3: %d, %s", global.Callbacks.Callback3Rep, global.Callbacks.Callback3);
        UART_Write_Protected(MsgBuffer);
        sprintf(MsgBuffer, MsgBreaker);
        UART_Write_Protected(MsgBuffer);
        return;
    }

    CallbackNum = strtol(StrBuffPTR, NULL, 10);

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (StrBuffPTR == NULL) {
        // Missing repetitions error
        strcpy(MsgBuffer, "\r\nMissing number of repetitions\r\n");
        UART_Write_Protected(MsgBuffer);
        return;
    }

    Repetitions = strtol(StrBuffPTR, NULL, 10);

    StrBuffPTR = NextSubString(StrBuffPTR, false);
    if (StrBuffPTR == NULL) {
        strcpy(MsgBuffer, "\r\nMissing Payload\r\n");
        UART_Write_Protected(MsgBuffer);
        return;
    }

    switch (CallbackNum) {
        case 0:  // Timer Callback
            strcpy(global.Callbacks.Callback0, StrBuffPTR);
            global.Callbacks.Callback0Rep = Repetitions;
            break;
        case 1:  // SW1 Callback
            strcpy(global.Callbacks.Callback1, StrBuffPTR);
            global.Callbacks.Callback1Rep = Repetitions;
            break;
        case 2:  // SW2 Callback
            strcpy(global.Callbacks.Callback2, StrBuffPTR);
            global.Callbacks.Callback2Rep = Repetitions;
            break;
        case 3:  // Script Callback
            strcpy(global.Callbacks.Callback3, StrBuffPTR);
            global.Callbacks.Callback3Rep = Repetitions;
            break;
        default:
            // Invalid callback number error
            strcpy(MsgBuffer, "\r\nInvalid callback number\r\n");
            UART_Write_Protected(MsgBuffer);
    }
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
    strcpy(MsgBuffer, "              : Secondary arg (0-4) will return specified error\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 0: Invalid CMD\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 1: InputOverflow\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 2: Invalid Addr \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 3: Invalid GPIO Pin\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 4: Invalid Action\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}
