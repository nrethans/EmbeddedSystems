/*
 * CommandTerminal.h
 *
 *  Created on: Aug 28, 2024
 *      Author: NickRethans
 */

#ifndef COMMANDTERMINAL_H_
#define COMMANDTERMINAL_H_

#include "Global.h"

/*
 * =========== Threads ===========
 */

void UART_Thread();

void UART7_Thread();

void Payload_Thread();

/*
 * =========== Inter-Thread Functions ========================
 */

void AddPayload(char *payload);

/*
 * =========== First Layer Parser Functions & Messages =======
 */
void HelpParse();

void AboutMsg();

void ClearMsg();

void PrintMsg();

void MemRead();

void GPIOParse(char *ch);

void ErrorParse();

void TimerParse(char *ch);

void CallbackParse(char *ch);

void TickerParser(char *ch);

void RegParse(char *ch);

void ScriptsParse(char *ch);

void IfParse();

void UARTParse();

void SineParse(char *ch);

void InvalidMsg();

/*
 * =============== SubString Functions ========
 */

bool MatchSubString(const char *msg1, const char *msg2);

char* NextSubString(char *msg, bool Print);

/*
 * =============== Initial Parser ========
 */

void MsgParser();

/*
 * ========== Second Layer Parser Functions & Messages ========
 */

void HelpHelpMsg();

void HelpAboutMsg();

void HelpPrintMsg();

void HelpClearMsg();

void HelpMemrMsg();

void HelpGPIOMsg();

void HelpErrorMsg();

void HelpTimerMsg();

void HelpCallbackMsg();

void HelpTickerMsg();

void HelpRegMsg();

void HelpScriptMsg();

void HelpIfMsg();

void HelpUARTMsg();

void HelpSineMsg();

#endif /* COMMANDTERMINAL_H_ */
