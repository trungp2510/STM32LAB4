/*
 * global.h
 *
 *  Created on: Nov 5, 2024
 *      Author: Fung
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"

#define INIT					1
#define AUTO_RED_NS_GREEN_EW 	2
#define AUTO_RED_NS_YELLOW_EW 	3
#define AUTO_GREEN_NS_RED_EW	4
#define AUTO_YELLOW_NS_RED_EW	5

#define MAN_MODE 	11
#define MAN_RED 	12
#define MAN_YELLOW	13
#define MAN_GREEN	14

extern int status;

extern int red_duration;
extern int yellow_duration;
extern int green_duration;

extern int temp_red;
extern int temp_yellow;
extern int temp_green;

extern int duration_led_NS;
extern int duration_led_EW;

extern int mode_led;

extern int index_led;
extern int led_buffer [4];

#endif /* INC_GLOBAL_H_ */
