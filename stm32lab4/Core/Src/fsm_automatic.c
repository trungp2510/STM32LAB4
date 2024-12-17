/*
 * fsm_automatic.c
 *
 *  Created on: Nov 5, 2024
 *      Author: Fung
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	if(timer3_flag == 1){
	setTimer3(10);
	update7SEG(index_led);
	index_led = (index_led + 1) % 4;
	}
	switch(status){
		case INIT:
			duration_led_NS = red_duration;
			duration_led_EW = green_duration;
			status = AUTO_RED_NS_GREEN_EW;
			setTimer1(green_duration*100);
			break;
		case AUTO_RED_NS_GREEN_EW:
			UpdateDisplayDownBuffer(duration_led_NS);
			UpdateDisplayUpBuffer(duration_led_EW);
			onRed_NS();
			onGreen_EW();
			time();
			if(timer1_flag == 1){
				setTimer1(yellow_duration*100);
				duration_led_NS = red_duration - green_duration;
				duration_led_EW = yellow_duration;
				status = AUTO_RED_NS_YELLOW_EW;
				clear_traffic_light();

			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				status = MAN_MODE;
			}
			break;
		case AUTO_RED_NS_YELLOW_EW:
			UpdateDisplayDownBuffer(duration_led_NS);
			UpdateDisplayUpBuffer(duration_led_EW);
			onRed_NS();
			onYellow_EW();
			time();
			if(timer1_flag == 1){
				setTimer1(green_duration*100);
				duration_led_NS = green_duration;
				duration_led_EW = red_duration;
				clear_traffic_light();
				status = AUTO_GREEN_NS_RED_EW;

			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				status = MAN_MODE;
			}
			break;
		case AUTO_GREEN_NS_RED_EW:
			UpdateDisplayDownBuffer(duration_led_NS);
			UpdateDisplayUpBuffer(duration_led_EW);
			onGreen_NS();
			onRed_EW();
			time();
			if(timer1_flag == 1){
				setTimer1(yellow_duration*100);
				duration_led_NS = yellow_duration;
				duration_led_EW = red_duration - green_duration;
				clear_traffic_light();
				status = AUTO_YELLOW_NS_RED_EW;
			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				status = MAN_MODE;
			}
			break;
		case AUTO_YELLOW_NS_RED_EW:
			UpdateDisplayDownBuffer(duration_led_NS);
			UpdateDisplayUpBuffer(duration_led_EW);
			onYellow_NS();
			onRed_EW();
			time();
			if(timer1_flag == 1){
				setTimer1(green_duration*100);
				duration_led_NS = red_duration;
				duration_led_EW = green_duration;
				clear_traffic_light();
				status = AUTO_RED_NS_GREEN_EW;
			}
			if(isButtonPressed(0) == 1){
				clear_traffic_light();
				status = MAN_MODE;
			}
			break;
		default:
			break;
	}
}
