/*
 *  Callbacks.h
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */
#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include "Global.h"

void ADCBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion, void *buffer, uint32_t channel, int_fast16_t status);

void Timer0CallBack();

void Timer1CallBack();

void GPIO_SW1_Callback();

void GPIO_SW2_Callback();

#endif /* CALLBACKS_H_ */
