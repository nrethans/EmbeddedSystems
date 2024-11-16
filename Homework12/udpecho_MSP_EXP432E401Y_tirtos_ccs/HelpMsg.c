/*
 *  HelpMsg.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"



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



void HelpRegMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -reg\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists and configures 32 available registers\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg -clear will reset all ticker configurations\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg <num> will display register value\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Reg Configuration:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : -reg <DST> <OP> <SRC A> <SRC B>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Addressing Modes:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : <0-31>       -   Register addressing\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : #<0-31>      -   Immediate Addressing\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : #x<0-31>     -   Hexadecimal immediate\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : @0x<Address> -   Direct addressing\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : @<0-31>      -   Indirect addressing\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Operators: \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : = -> Set  |   x -> Exchange \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : + -> Add  |  ++ -> Increment\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : - -> Sub  |  -- -> Decrement\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : ' -> NOT  |  &  -> AND\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : | -> OR   |  _| -> NOR\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : x|-> XOR  |  \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : > -> Max  |  <  -> MIN\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : * -> MUL  |  /  -> DIV\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : % -> Remainder\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}



void HelpScriptMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -script\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Lists and configures scripts (0-63)\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Secondary arg -clear will reset all script configurations\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Ticker Configuration:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : -script <script num> <operation> <payload>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : Operation Modes:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : x -> Executes Script:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : r -> Reads Script:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "              : w -> Write Script:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}



void HelpIfMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -if\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Conditional for scripts\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                If Argument:\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                -if A OP B ? -script <#> x : -script <#> x\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                Condition Args \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                ->    Immediate : #<Num>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                ->     Register : <Num>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                Operations:  \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                -> Greater Than : >\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                ->    Less Than : <\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                ->        Equal : =\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}



void HelpUARTMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -uart\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Sends payload via UART7\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                TX -> PC5\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                RX -> PC4\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                **NOTE** \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                Make sure to connect common ground if\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                communicating with separate devices.\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}



void HelpSineMsg(){
    char MsgBuffer[MsgPrintBufferSize] = {'\0'};
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Command     : -sine\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Description : Plays pure sinewave from 0 - 3999Hz\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                Uses SPI3: SCLK -> PQ0 : MOSI -> PQ2 : SS -> PQ1 \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                Syntax: -sine <0-3999>\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                **NOTE** \r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                sine 0 stops sound\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "                Uses Timer1\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, "  Location    : CommandTerminal.c\r\n");
    UART_Write_Protected(MsgBuffer);
    strcpy(MsgBuffer, MsgBreaker);
    UART_Write_Protected(MsgBuffer);
}
