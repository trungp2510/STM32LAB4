/*
 * traffic_light.c
 *
 *  Created on: Nov 7, 2024
 *      Author: Fung
 */

#include "traffic_light.h"

void clear_traffic_light(){
	HAL_GPIO_WritePin(RED_NS_GPIO_Port, RED_NS_Pin, RESET);
	HAL_GPIO_WritePin(RED_EW_GPIO_Port, RED_EW_Pin, RESET);
	HAL_GPIO_WritePin(YELLOW_NS_GPIO_Port, YELLOW_NS_Pin, RESET);
	HAL_GPIO_WritePin(YELLOW_EW_GPIO_Port, YELLOW_EW_Pin, RESET);
	HAL_GPIO_WritePin(GREEN_NS_GPIO_Port, GREEN_NS_Pin, RESET);
	HAL_GPIO_WritePin(GREEN_EW_GPIO_Port, GREEN_EW_Pin, RESET);
}
void onRed_NS(){
	HAL_GPIO_WritePin(RED_NS_GPIO_Port, RED_NS_Pin, SET);
}
void onYellow_NS(){
	HAL_GPIO_WritePin(YELLOW_NS_GPIO_Port, YELLOW_NS_Pin, SET);
}
void onGreen_NS(){
	HAL_GPIO_WritePin(GREEN_NS_GPIO_Port, GREEN_NS_Pin, SET);
}
void onRed_EW(){
	HAL_GPIO_WritePin(RED_EW_GPIO_Port, RED_EW_Pin, SET);
}
void onYellow_EW(){
	HAL_GPIO_WritePin(YELLOW_EW_GPIO_Port, YELLOW_EW_Pin, SET);
}
void onGreen_EW(){
	HAL_GPIO_WritePin(GREEN_EW_GPIO_Port, GREEN_EW_Pin, SET);
}

void time(){
	if(timer4_flag == 1){
		setTimer4(100);
		duration_led_NS--;
		duration_led_EW--;
	}
}
