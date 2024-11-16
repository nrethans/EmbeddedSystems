/*
 *  InitialHandler.h
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */
#ifndef INITIALHANDLER_H_
#define INITIALHANDLER_H_

#include "Global.h"

void MsgParser();

void UART_Write_Protected(char* input);

void UART_Input_Handler(char input);

#endif /* INITIALHANDLER_H_ */
