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
 * ========== AAA Thread =========
 */

void TaskAAA();

/*
 * ========== Initializers =======
 */

void GlobInit(Glob *global);

void UART_Init();

void Timer_Init();

/*
 * ========== Callbacks ================
 */

void Timer0CallBack();

void Timer1CallBack();

void GPIO_SW1_Callback();

void GPIO_SW2_Callback();

/*
 * ========== SWI ======================
 */

void SW1_Swi();

void SW2_Swi();

void Timer0Swi();

void Timer1Swi();

/*
 * ========== UART_Write_Protected =====
 */

void UART_Write_Protected(char* input);

/*
 * ========== UART_Input_Handler =======
 */

void UART_Input_Handler(char input);

#endif /* INFRASTRUCTURE_H */
