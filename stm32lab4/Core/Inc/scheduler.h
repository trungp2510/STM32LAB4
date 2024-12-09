/*
 * scheduler.h
 *
 *  Created on: Nov 24, 2024
 *      Author: Fung
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#ifdef SCH_REPORT_ERRORS
#define Error_port PORTA
#endif
#define SCH_MAX_TASKS	40
#define NO_TASK_ID		0
#define ERROR_SCH_CANNOT_DELETE_TASK 	50
#define RETURN_ERROR					51
#define RETURN_NORMAL					52
#define ERROR_SCH_TOO_MANY_TASKS		53
#include "main.h"
#include <stdint.h>

typedef struct {
	 void ( * pTask)(void) ;
	 // Delay (ticks) until the function will (next) be run
	 uint32_t Delay;
	 // Interval (ticks) between subsequent runs.
	 uint32_t Period;
	 // Incremented (by scheduler) when task is due to execute
	 uint8_t RunMe;
	 //This is a hint to solve the question below.
	 uint32_t TaskID;
 	 } sTasks;

#endif /* INC_SCHEDULER_H_ */
