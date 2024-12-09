/*
 * fsm_setting.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Fung
 */

#include "fsm_setting.h"


void fsm_setting_run(){
	switch(status){
	case MAN_RED:
		UpdateDisplayDownBuffer(mode_led);
		if(isButtonPressed(1) == 1){
			temp_red++;
			if(temp_red >= 100){
				temp_red = red_duration;
			}
			UpdateDisplayUpBuffer(temp_red);
		}
		if(isButtonPressed(2) == 1){
			red_duration = temp_red;
			green_duration = red_duration - yellow_duration;
			UpdateDisplayUpBuffer(red_duration);
		}
		break;
	case MAN_YELLOW:
		UpdateDisplayDownBuffer(mode_led);
		if(isButtonPressed(1) == 1){
			temp_yellow++;
			if(temp_yellow >= 100){
				temp_yellow = yellow_duration;
			}
			UpdateDisplayUpBuffer(temp_yellow);
		}
		if(isButtonPressed(2) == 1){
			UpdateDisplayUpBuffer(temp_yellow);
			yellow_duration = temp_yellow;
			red_duration = yellow_duration + green_duration;
			UpdateDisplayUpBuffer(yellow_duration);
		}
		break;
	case MAN_GREEN:
		UpdateDisplayDownBuffer(mode_led);
		if(isButtonPressed(1) == 1){
			temp_green++;
			if(temp_green >= 100){
			temp_green = green_duration;
			}
			UpdateDisplayUpBuffer(temp_green);
		}
		if(isButtonPressed(2) == 1){
			green_duration = temp_green;
			red_duration = green_duration + yellow_duration;
			UpdateDisplayUpBuffer(green_duration);
		}
		break;
	default:
		break;
	}
}
