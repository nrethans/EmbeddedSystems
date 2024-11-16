/*
 *  Interface.h
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */
#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Global.h"

void HelpParse();

void AboutMsg();

void InvalidMsg();

void ClearMsg();

void PrintMsg();

void MemRead();

void ErrorMsg();

void GPIOParse(char *ch);

void TimerParse(char *ch);

void CallbackParse(char *ch);

void AddPayload(char *payload);

void TickerParser(char *ch);

void RegParse(char *ch);

void ScriptsParse(char *ch);

void IfParse();

void UARTParse();

void SineParse(char *ch);

void VoiceParse(char *ch);

void AudioParse();

void StreamParse(char *ch);

void ClearAudioBuffers();


#endif /* INTERFACE_H_ */
