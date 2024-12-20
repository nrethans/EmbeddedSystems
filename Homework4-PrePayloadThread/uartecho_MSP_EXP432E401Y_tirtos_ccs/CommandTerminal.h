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

/*
 * =========== First Layer Parser Functions & Messages =======
 */
void HelpParse();

void AboutMsg();

void ClearMsg();

void PrintMsg();

void MemRead();

void GPIOParse();

void GPIOParse();

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

#endif /* COMMANDTERMINAL_H_ */
