/*
 * Global.h
 *
 *  Created on: Aug 27, 2024
 *      Author: NickRethans
 */
#ifndef Global
#define Global

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include "ti_drivers_config.h"

/*
 * ========== Global Definitions =======
 */

#define Version "1.0"
#define MsgBufferSize 100

/*
 * ========== Global Variables =========
 */

typedef struct Glob {
    int32_t     GlobHead;
    UART_Handle uart;
    int32_t     GlobTail;
} Glob;

/*
 * ========== Global Initializer =======
 */

void GlobInit(Glob *global, UART_Handle uart) {
    global->GlobHead = 0x5a5a5a5a;
    global->uart = uart;
    global->GlobTail = 0x5a5a5a5a;
}

#endif

