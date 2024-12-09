/*
 * button.c
 *
 *  Created on: Nov 3, 2024
 *      Author: Fung
 */

#include "button.h"

int button_flag[3] = {0,0,0};
int keyReg0[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int keyReg1[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int keyReg2[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int keyReg3[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int TimeForKeyPress[3] = {200,200,200};


int isButtonPressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}
void subKeyProcess(int index){
	button_flag[index] = 1;
}

void getKeyInput(){
	for(int i = 0; i < 3; i++){
		keyReg0[i] = keyReg1[i];
		keyReg1[i] = keyReg2[i];
		switch(i){
		case 0:
			keyReg2[i] = HAL_GPIO_ReadPin(BUTTON0_GPIO_Port,BUTTON0_Pin);
			break;
		case 1:
			keyReg2[i] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port,BUTTON1_Pin);
			break;
		case 2:
			keyReg2[i] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port,BUTTON2_Pin);
			break;
		}
		if((keyReg0[i] == keyReg1[i]) && (keyReg1[i] == keyReg2[i])){
			if(keyReg3[i] != keyReg2[i]){
				keyReg3[i] = keyReg2[i];
				if(keyReg2[i] == PRESSED_STATE){
					subKeyProcess(i);
					TimeForKeyPress[i] = 200;
				}
			}
			else{
				TimeForKeyPress[i]--;
				if(TimeForKeyPress[i] == 0){
					keyReg3[i] = NORMAL_STATE;
				}
			}
		}
	}
}
