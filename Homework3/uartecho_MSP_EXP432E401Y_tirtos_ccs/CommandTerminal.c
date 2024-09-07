/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * =============== Main Thread ===============
 */

void *mainThread(void *arg0)
{
    char  input;
    GPIO_init();
    UART_Init();
    Error_Init();
    while (1) {
        UART_read(global.uart, &input, 1);
        UART_Input_Handler(input);
        if(input != 24 && input != 25 && input != 26 && input != 27){
            UART_write(global.uart, &input, 1);
        }
    }
}

/*
 * =============== First Layer Parser Functions & Messages ========
 */

void HelpParse() {
    char *SubStrPtr;
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    SubStrPtr = NextSubString(global.MsgBuff, false);
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
//        strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " -help  -> provides list of function descriptions\r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " -about -> provides developer and version info\r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " -print -> prints message after -print \r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " -clear -> clears the terminal\r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " -memr  -> prints memory address values\r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " -gpio  -> interfaces with GPIO pins\r\n");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  " Type -help <command> for more information");
//        UART_Write_Protected(MsgBuffer);
//        strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
//        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "\r\n====================================================================\r\n");
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
        strcpy(MsgBuffer, "  Note        : Type -help <command> for more information\r\n");
        UART_Write_Protected(MsgBuffer);
        strcpy(MsgBuffer, "====================================================================\r\n");
        UART_Write_Protected(MsgBuffer);
    }
}

void AboutMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  " Developer: Nicholas Rethans\r\n");
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Assignment #: %s \r\n", Assignment);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Version %s.%s \r\n", Version, SubVersion);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,                 " Time: %s  Date: %s", __TIME__, __DATE__);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer,                  "\r\n======================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void ClearMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy(MsgBuffer,"\033c");
    UART_write(global.uart, MsgBuffer,sizeof(MsgBuffer));
}

void PrintMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer,                          "\n\n\r");
    strcat(MsgBuffer,NextSubString(global.MsgBuff,true));
    strcat(MsgBuffer,                          "\n\n\r");
    UART_Write_Protected(MsgBuffer);
}

void MemRead(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int32_t value;
    int32_t address;
    char *addressPTR;
    char *MsgBuffPTR;

    MsgBuffPTR = NextSubString(global.MsgBuff,false);
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
    strcpy(MsgBuffer,"\r\n0x00100000<Address<0x20000000 or Address>0x20040000\r\n");
    UART_Write_Protected(MsgBuffer);
}

void GPIOParse() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    int GPIO_Num = -1;
    char *MsgBuffPTR;
    MsgBuffPTR = NextSubString(global.MsgBuff,false);

    if(isdigit(*MsgBuffPTR)){
        GPIO_Num = *MsgBuffPTR - '0';
    }

    MsgBuffPTR = NextSubString(MsgBuffPTR,false);

    switch(GPIO_Num){
        case 0: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO 0: %hhu\r\n", global.GPIO_Val.GPIO_LED0);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO 0: %hhu\r\n", global.GPIO_Val.GPIO_LED0);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"w")) {
                global.GPIO_Val.GPIO_LED0 = 1;
                GPIO_write(CONFIG_GPIO_LED0,1);
                goto PrintDone;
            } else if (MatchSubString(MsgBuffPTR,"t")) {
                if(global.GPIO_Val.GPIO_LED0==0){
                    GPIO_write(CONFIG_GPIO_LED0,1);
                    global.GPIO_Val.GPIO_LED0 = 1;
                } else {
                    GPIO_write(CONFIG_GPIO_LED0,0);
                    global.GPIO_Val.GPIO_LED0 = 0;
                }
                goto PrintDone;
            } else {
                strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            break;
        }
        case 1: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO 1: %hhu\r\n", global.GPIO_Val.GPIO_LED1);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_LED1 = GPIO_read(CONFIG_GPIO_LED1);
                sprintf(MsgBuffer, "\r\nGPIO 1: %hhu\r\n", global.GPIO_Val.GPIO_LED1);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"w")) {
                global.GPIO_Val.GPIO_LED1 = 1;
                GPIO_write(CONFIG_GPIO_LED1,1);
                goto PrintDone;

            } else if (MatchSubString(MsgBuffPTR,"t")) {
                if(global.GPIO_Val.GPIO_LED1==0){
                    GPIO_write(CONFIG_GPIO_LED1,1);
                    global.GPIO_Val.GPIO_LED1 = 1;
                } else {
                    GPIO_write(CONFIG_GPIO_LED1,0);
                    global.GPIO_Val.GPIO_LED1 = 0;
                }
                goto PrintDone;

            } else {
                strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            break;
        }
        case 2: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO 2: %hhu\r\n", global.GPIO_Val.GPIO_LED2);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_LED2 = GPIO_read(CONFIG_GPIO_LED2);
                sprintf(MsgBuffer, "\r\nGPIO 2: %hhu\r\n", global.GPIO_Val.GPIO_LED2);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"w")) {
                global.GPIO_Val.GPIO_LED2 = 1;
                GPIO_write(CONFIG_GPIO_LED2,1);
                goto PrintDone;

            } else if (MatchSubString(MsgBuffPTR,"t")) {
                if(global.GPIO_Val.GPIO_LED2==0){
                    GPIO_write(CONFIG_GPIO_LED2,1);
                    global.GPIO_Val.GPIO_LED2 = 1;
                } else {
                    GPIO_write(CONFIG_GPIO_LED2,0);
                    global.GPIO_Val.GPIO_LED2 = 0;
                }
                goto PrintDone;

            } else {
                strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            break;
        }
        case 3: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO 3: %hhu\r\n", global.GPIO_Val.GPIO_LED3);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_LED3 = GPIO_read(CONFIG_GPIO_LED3);
                sprintf(MsgBuffer, "\r\nGPIO 3: %hhu\r\n", global.GPIO_Val.GPIO_LED3);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"w")) {
                global.GPIO_Val.GPIO_LED3 = 1;
                GPIO_write(CONFIG_GPIO_LED3,1);
                goto PrintDone;

            } else if (MatchSubString(MsgBuffPTR,"t")) {
                if(global.GPIO_Val.GPIO_LED3==0){
                    GPIO_write(CONFIG_GPIO_LED3,1);
                    global.GPIO_Val.GPIO_LED3 = 1;
                } else {
                    GPIO_write(CONFIG_GPIO_LED3,0);
                    global.GPIO_Val.GPIO_LED3 = 0;
                }
                goto PrintDone;

            } else {
                strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            break;
        }
        case 4: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO AUDIO PWR: %hhu\r\n", global.GPIO_Val.GPIO_AUDIO_PWR);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_AUDIO_PWR = GPIO_read(CONFIG_GPIO_AUDIO_PWR);
                sprintf(MsgBuffer, "\r\nGPIO AUDIO PWR: %hhu\r\n", global.GPIO_Val.GPIO_AUDIO_PWR);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"w")) {
                global.GPIO_Val.GPIO_AUDIO_PWR = 1;
                GPIO_write(CONFIG_GPIO_AUDIO_PWR,1);
                goto PrintDone;

            } else if (MatchSubString(MsgBuffPTR,"t")) {
                if(global.GPIO_Val.GPIO_AUDIO_PWR==0){
                    GPIO_write(CONFIG_GPIO_AUDIO_PWR,1);
                    global.GPIO_Val.GPIO_AUDIO_PWR = 1;
                } else {
                    GPIO_write(CONFIG_GPIO_AUDIO_PWR,0);
                    global.GPIO_Val.GPIO_AUDIO_PWR = 0;
                }
                goto PrintDone;

            } else {
                strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            break;
        }
        case 5: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
                sprintf(MsgBuffer, "\r\nGPIO MIC PWR: %hhu\r\n", global.GPIO_Val.GPIO_MIC_PWR);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_MIC_PWR = GPIO_read(CONFIG_GPIO_MIC_PWR);
                sprintf(MsgBuffer, "\r\nGPIO MIC PWR: %hhu\r\n", global.GPIO_Val.GPIO_MIC_PWR);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"w")) {
                global.GPIO_Val.GPIO_MIC_PWR = 1;
                GPIO_write(CONFIG_GPIO_MIC_PWR,1);
                goto PrintDone;

            } else if (MatchSubString(MsgBuffPTR,"t")) {
                if(global.GPIO_Val.GPIO_MIC_PWR==0){
                    GPIO_write(CONFIG_GPIO_MIC_PWR,1);
                    global.GPIO_Val.GPIO_MIC_PWR = 1;
                } else {
                    GPIO_write(CONFIG_GPIO_MIC_PWR,0);
                    global.GPIO_Val.GPIO_MIC_PWR = 0;
                }
                goto PrintDone;

            } else {
                strcpy(MsgBuffer,  "\r\nInvalid GPIO Action\r\n");
                UART_Write_Protected(MsgBuffer);
                global.Error.InvalidGPIOAction++;
            }
            break;
        }
        case 6: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_SW1 = GPIO_read(CONFIG_GPIO_SW2);
                sprintf(MsgBuffer, "\r\nGPIO SW1: %hhu\r\n", global.GPIO_Val.GPIO_SW1);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_SW1 = GPIO_read(CONFIG_GPIO_SW2);
                sprintf(MsgBuffer, "\r\nGPIO SW1: %hhu\r\n", global.GPIO_Val.GPIO_SW1);
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
            break;
        }
        case 7: {
            if        (*MsgBuffPTR == NULL)            {
                global.GPIO_Val.GPIO_SW2 = GPIO_read(CONFIG_GPIO_SW1);
                sprintf(MsgBuffer, "\r\nGPIO SW2: %hhu\r\n", global.GPIO_Val.GPIO_SW2);
                UART_Write_Protected(MsgBuffer);

            } else if (MatchSubString(MsgBuffPTR,"r")) {
                global.GPIO_Val.GPIO_SW2 = GPIO_read(CONFIG_GPIO_SW1);
                sprintf(MsgBuffer, "\r\nGPIO SW2: %hhu\r\n", global.GPIO_Val.GPIO_SW2);
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
            break;
        }
        case -1: {
            global.GPIO_Val.GPIO_LED0 = GPIO_read(CONFIG_GPIO_LED0);
            sprintf(MsgBuffer, "\r\nGPIO 0: %hhu\r\n", global.GPIO_Val.GPIO_LED0);

            strcpy (MsgBuffer,"\r\n==========================================\r\n");
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"      GPIO LED0: %hhu\r\n", global.GPIO_Val.GPIO_LED0   );
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"      GPIO LED1: %hhu\r\n", global.GPIO_Val.GPIO_LED1   );
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"      GPIO LED2: %hhu\r\n", global.GPIO_Val.GPIO_LED2   );
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"      GPIO LED3: %hhu\r\n", global.GPIO_Val.GPIO_LED3   );
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer," GPIO AUDIO PWR: %hhu\r\n", global.GPIO_Val.GPIO_AUDIO_PWR);
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"   GPIO MIC PWR: %hhu\r\n", global.GPIO_Val.GPIO_MIC_PWR);
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"       GPIO SW1: %hhu\r\n", global.GPIO_Val.GPIO_SW1);
            UART_Write_Protected(MsgBuffer);
            sprintf(MsgBuffer,"       GPIO SW2: %hhu", global.GPIO_Val.GPIO_SW2);
            UART_Write_Protected(MsgBuffer);
            strcpy (MsgBuffer,"\r\n==========================================\r\n");
            UART_Write_Protected(MsgBuffer);
            break;
        }
        default: {
            global.Error.InvalidGPIOPin++;
            strcpy (MsgBuffer,"\r\nInvalid Pin Number\r\n");
            UART_Write_Protected(MsgBuffer);
        }
    }
    PrintDone:
    strcpy(MsgBuffer, "\r\n");
    UART_Write_Protected(MsgBuffer);
}

void ErrorMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};

    strcpy (MsgBuffer,"\r\n==========================================\r\n");
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"Invalid Command    : %hhu\r\n",global.Error.InvalidCMD);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"Input Overflow     : %hhu\r\n",global.Error.InputOverflow);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"Invaild Address    : %hhu\r\n",global.Error.InvalidAddress);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"Invalid GPIO Pin   : %hhu\r\n",global.Error.InvalidGPIOPin);
    UART_Write_Protected(MsgBuffer);
    sprintf(MsgBuffer,"Invalid GPIO Action: %hhu",global.Error.InvalidGPIOAction);
    UART_Write_Protected(MsgBuffer);
    strcpy (MsgBuffer,"\r\n==========================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void InvalidMsg() {
    global.Error.InvalidCMD++;
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    global.MsgBuff[15] = '\0';
    strcpy(MsgBuffer,  "\r\nInvalid Command: ");
    strcat(MsgBuffer,           global.MsgBuff);
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


    if        (MatchSubString(global.MsgBuff, "-help" )) {
         HelpParse();
    } else if (MatchSubString(global.MsgBuff, "-about")) {
          AboutMsg();
    } else if (MatchSubString(global.MsgBuff, "-clear")) {
          ClearMsg();
    } else if (MatchSubString(global.MsgBuff, "-print")) {
          PrintMsg();
    } else if (MatchSubString(global.MsgBuff, "-memr" )) {
           MemRead();
    } else if (MatchSubString(global.MsgBuff, "-gpio" )) {
         GPIOParse();
    } else if (MatchSubString(global.MsgBuff, "-error" )) {
          ErrorMsg();
    } else {
        InvalidMsg();
    }
}

/*
 * ========== Second Layer Parser Functions & Messages ========
 */


void HelpHelpMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -help\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Provides list of function descriptions\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpAboutMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -about\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Provides developer and version info\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpPrintMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -print\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Prints message after -print\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpClearMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -clear\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Clears the terminal\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpMemrMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command       : -memr\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description   : Prints memory address values\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location      : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Invalid Range : 0x00100000 < Address < 0x20000000 or Address > 0x20040000\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpGPIOMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -gpio <pin> <action>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Interacts with GPIO pins\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Pinout      : 0: LED0       1: LED1       2: LED2       3: LED3\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : 4: AUDIO PWR  5: MIC PWR    6: SW1*       7: SW2*\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Actions     : r: read, w: write, t: toggle\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Notes       : * SW1 & SW2 are read-only\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : -gpio (without arguments) prints list of GPIO values\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : GPIO values are ghosted in global.GPIO_Val\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}

void HelpErrorMsg() {
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, "\r\n==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -error\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists number of errors since last reset\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : [Location information missing]\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "==============================================================================\r\n");
    UART_Write_Protected(MsgBuffer);
}
