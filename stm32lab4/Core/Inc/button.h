/*
 * button.h
 *
 *  Created on: Nov 3, 2024
 *      Author: Fung
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

extern int button_flag[3];
void subKeyProcess(int index);
int isButtonPressed(int index);
void getKeyInput();

#endif /* INC_BUTTON_H_ */
