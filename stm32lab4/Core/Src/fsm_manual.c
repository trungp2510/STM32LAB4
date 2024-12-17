/*
 * fsm_manual.c
 *
 *  Created on: Nov 5, 2024
 *      Author: Fung
 */

#include "fsm_manual.h"

int first_access = 0;
void fsm_manual_run(){
	switch(status){
		case MAN_MODE:
			status = MAN_RED;
			setTimer2(25);
		case MAN_RED:
			mode_led = 1;
			UpdateDisplayDownBuffer(mode_led);
			if(first_access == 0){
				UpdateDisplayUpBuffer(red_duration);
				first_access = 1;
				temp_red = red_duration;
			}
			if(timer2_flag == 1){
				setTimer2(25);
				HAL_GPIO_TogglePin(RED_NS_GPIO_Port, RED_NS_Pin);
				HAL_GPIO_TogglePin(RED_EW_GPIO_Port, RED_EW_Pin);
			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				setTimer2(25);
				first_access = 0;
				status = MAN_YELLOW;
			}
			break;
		case MAN_YELLOW:
			mode_led = 2;
			UpdateDisplayDownBuffer(mode_led);
			if(first_access == 0){
				UpdateDisplayUpBuffer(yellow_duration);
				first_access = 1;
				temp_yellow = yellow_duration;
			}
			if(timer2_flag == 1){
				setTimer2(25);
				HAL_GPIO_TogglePin(YELLOW_NS_GPIO_Port, YELLOW_NS_Pin);
				HAL_GPIO_TogglePin(YELLOW_EW_GPIO_Port, YELLOW_EW_Pin);
			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				setTimer2(25);
				first_access = 0;
				status = MAN_GREEN;
			}
			break;
		case MAN_GREEN:
			mode_led = 3;
			UpdateDisplayDownBuffer(mode_led);
			if(first_access == 0){
				UpdateDisplayUpBuffer(green_duration);
				first_access = 1;
				temp_green = green_duration;
			}
			if(timer2_flag == 1){
				setTimer2(25);
				HAL_GPIO_TogglePin(GREEN_NS_GPIO_Port, GREEN_NS_Pin);
				HAL_GPIO_TogglePin(GREEN_EW_GPIO_Port, GREEN_EW_Pin);
			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				first_access = 0;
				status = INIT;
			}
			break;
		default:
			break;
	}
}
