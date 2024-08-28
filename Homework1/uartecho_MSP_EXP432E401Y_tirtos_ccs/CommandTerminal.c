#include "Global.h"
/* Message Parser & Message Functions */

void HelpMsg(UART_Handle uart) {
    char ParsedMsgBuffer[64] = {0};

    sprintf(ParsedMsgBuffer,                 "\r\n========================================\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof("\r\n========================================\r\n"));

    sprintf(ParsedMsgBuffer,                 " -help  -> provides list of functions\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof(" -help  -> provides list of functions\r\n"));

    sprintf(ParsedMsgBuffer,                 " -about -> provides developer and version info\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof(" -about -> provides developer and version info\r\n"));

    sprintf(ParsedMsgBuffer,                 "========================================\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof("========================================\r\n"));
}

void AboutMsg(UART_Handle uart) {
    char ParsedMsgBuffer[64] = {0};

    sprintf(ParsedMsgBuffer,                 "\r\n======================\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof("\r\n======================\r\n"));

    sprintf(ParsedMsgBuffer,                 " Developer: Nicholas Rethans\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof(" Developer: Nicholas Rethans\r\n"));

    sprintf(ParsedMsgBuffer,                 " Assignment #: 1 \r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof(" Assignment #: 1 \r\n"));

    sprintf(ParsedMsgBuffer,                 " Version 1.1 \r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof(" Version 1.1 \r\n"));

    sprintf(ParsedMsgBuffer,                 " Time: %s  Date: %s\r\n", __TIME__, __DATE__);
    UART_write(uart, ParsedMsgBuffer, sizeof(" Time: %s  Date: %s\r\n")+22);

    sprintf(ParsedMsgBuffer,                 "======================\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof("======================\r\n"));
}

void ClearMsg(UART_Handle uart){
    char ParsedMsgBuffer[64] = {0};
    sprintf(ParsedMsgBuffer,                 "\033c");
    UART_write(uart, ParsedMsgBuffer, sizeof("\033c"));
}

void InvalidMsg(UART_Handle uart) {
    char ParsedMsgBuffer[64] = {0};

    sprintf(ParsedMsgBuffer,                 "\nInvalid Command...\r\n");
    UART_write(uart, ParsedMsgBuffer, sizeof("\nInvalid Command...\r\n"));
}

void MsgParser(UART_Handle uart, char *Msg) {

    if        (strcasecmp(Msg, "-help" ) == 0) {
        HelpMsg   (uart);
    } else if (strcasecmp(Msg, "-about") == 0) {
        AboutMsg  (uart);
    } else if (strcasecmp(Msg, "-clear") == 0) {
        ClearMsg  (uart);
    } else {
        InvalidMsg(uart);
    }
}
