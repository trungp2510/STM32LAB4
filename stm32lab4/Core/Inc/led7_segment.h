/*
 * led7_segment.h
 *
 *  Created on: Nov 5, 2024
 *      Author: Fung
 */

#ifndef INC_LED7_SEGMENT_H_
#define INC_LED7_SEGMENT_H_

#include "main.h"
#include "global.h"


void display7SEG(int num);
void update7SEG(int index);
void UpdateDisplayDownBuffer(int display1);
void UpdateDisplayUpBuffer(int display2);
#endif /* INC_LED7_SEGMENT_H_ */
