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
 * ========== Initializers =======
 */

void GlobInit(Glob *global);

void Error_Init();

void UART_Init();
/*
 * ========== UART_Write_Protected =====
 */

void UART_Write_Protected(char* input);

/*
 * ========== UART_Input_Handler =======
 */

void UART_Input_Handler(char input);

#endif /* INFRASTRUCTURE_H */
