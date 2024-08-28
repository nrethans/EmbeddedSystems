#include "Global.h"
/*
 * ========== Global Initializer =======
 */

void GlobInit(Glob *global, UART_Handle uart) {
    global->GlobHead = 0x5a5a5a5a;
    global->uart = uart;
    global->GlobTail = 0x5a5a5a5a;
}
