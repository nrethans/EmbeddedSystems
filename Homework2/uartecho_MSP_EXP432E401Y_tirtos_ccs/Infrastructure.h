/*
 * Infrastructure.h
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include "Global.h"

/*
 * ========== Global Initializer =======
 */

void GlobInit(Glob *global, UART_Handle uart);

/*
 * ========== UART_Write_Protected =====
 */

void UART_Write_Protected(UART_Handle uart, char* input);

/*
 * ========== UART_Input_Handler =======
 */

void UART_Input_Handler(Glob *global, char input);

#endif /* INFRASTRUCTURE_H */
