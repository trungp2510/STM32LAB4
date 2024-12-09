/*
 * global.c
 *
 *  Created on: Nov 5, 2024
 *      Author: Fung
 */


#include "global.h"

int status = 0;

int red_duration = 5;
int yellow_duration = 2;
int green_duration = 3;

int temp_red = 5;
int temp_yellow = 2;
int temp_green = 3;

int duration_led_NS = 5;
int duration_led_EW = 3;
int mode_led = 1;

int index_led = 0;
int led_buffer [4] = {1, 2, 3, 4};
