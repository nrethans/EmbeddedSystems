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
 * =========== Parser Functions =======
 */
void HelpMsg();

void AboutMsg();

void ClearMsg();

void PrintMsg();

void InvalidMsg();

bool MatchSubString(const char *msg1, const char *msg2);

void MsgParser(char *msg);

#endif /* COMMANDTERMINAL_H_ */
