/*
 *  Initializers.h
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#ifndef INITIALIZERS_H_
#define INITIALIZERS_H_

#include "Global.h"

void GlobInit(Glob *global);

extern Glob global;

void ADCBuf_Init();

void SPI_Init();

void UART_Init();

void Timer_Init();

#endif /* INITIALIZERS_H_ */
