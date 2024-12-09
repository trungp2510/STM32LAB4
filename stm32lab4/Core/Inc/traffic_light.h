/*
 * traffic.light.h
 *
 *  Created on: Nov 7, 2024
 *      Author: Fung
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "global.h"
#include "main.h"
#include "software_timer.h"

void clear_traffic_light();
void onRed_NS();
void onYellow_NS();
void onGreen_NS();
void onRed_EW();
void onYellow_EW();
void onGreen_EW();
void time();
#endif /* INC_TRAFFIC_LIGHT_H_ */
