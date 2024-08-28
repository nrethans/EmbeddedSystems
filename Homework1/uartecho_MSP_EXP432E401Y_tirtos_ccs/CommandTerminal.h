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
void HelpMsg(UART_Handle uart);

void AboutMsg(UART_Handle uart);

void ClearMsg(UART_Handle uart);

void InvalidMsg(UART_Handle uart);

void MsgParser(UART_Handle uart, char *Msg);

#endif /* COMMANDTERMINAL_H_ */
