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
 * =========== First Layer Parser Functions & Messages =======
 */
void HelpMsg();

void AboutMsg();

void ClearMsg();

void PrintMsg();

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


#endif /* COMMANDTERMINAL_H_ */
