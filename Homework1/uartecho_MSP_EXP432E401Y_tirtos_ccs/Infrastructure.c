/*
 *  CommandTerminal.c
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#include "Global.h"

/*
 * ========== Global Initializer =======
 */

void GlobInit(Glob *global, UART_Handle uart) {
    global->GlobHead = 0x5a5a5a5a;
    global->uart = uart;
    global->GlobTail = 0x5a5a5a5a;
}
/*
 * ========== UART Write Protected =====
 */
void UART_Write_Protected(UART_Handle uart, char* input) {
    int length = 0;
    length = strlen(input);
    UART_write(uart, input, length);
}

