/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2024
 *      Author: Fung
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
unsigned char Error_code_G = 0;

uint8_t SCH_Delete_Task(uint32_t TASK_INDEX){
 	unsigned char Return_code;
 	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
 		// No task at this location ...
 		//
 		// Set the global error variable
 		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
 		// ... also return an error code
 		Return_code = RETURN_ERROR;
 	} else {
 		Return_code = RETURN_NORMAL;
 	}
 	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
 	SCH_tasks_G[TASK_INDEX].Delay = 0;
 	SCH_tasks_G[TASK_INDEX].Period = 0;
 	SCH_tasks_G[TASK_INDEX].RunMe = 0;
 	return Return_code;
 }
void Watchdog_init(void){
 	//TODO
 }

 void Timer_init(void){
 	//TODO
 }

 void SCH_Go_To_Sleep(void){
 	//TODO
 }

void SCH_Init(void) {
 	unsigned char i ;
 	for (i = 0; i <SCH_MAX_TASKS; i++) {
 		SCH_Delete_Task(i);
 	}
 	Error_code_G = 0;
 	Timer_init();
 	Watchdog_init();
 }
void SCH_Update(void){
 	unsigned char Index;
 	//NOTE: calculations are in *TICKS* (not milliseconds)
 	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
 		// Check if there is a task at this location
 		if (SCH_tasks_G[Index].pTask){
 			if (SCH_tasks_G[Index].Delay == 0) {
 				// The task is due to run
 				// Inc. the ’RunMe’ flag
 				SCH_tasks_G[Index].RunMe+= 1;
 				if (SCH_tasks_G[Index].Period) {
 					// Schedule periodic tasks to run again
 					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
 				}
 			} else {
 				// Not yet ready to run: just decrement the delay
 				SCH_tasks_G[Index].Delay --;
 			}
 		}
 	}
 }

void SCH_Dispatch_Tasks(void){
 	unsigned char Index;
 	// Dispatches (runs) the next task (if one is ready)
 	for (Index = 0; Index <SCH_MAX_TASKS; Index++){
 		if (SCH_tasks_G[Index].RunMe> 0) {
 			(*SCH_tasks_G[Index].pTask)(); // Run the task
 			SCH_tasks_G[Index].RunMe--; // Reset / reduceRunMe flag
 			// Periodic tasks will automatically run again
 			// − if this is a ’one shot’ task, remove it from the array
 			if (SCH_tasks_G[Index].Period == 0){
 				SCH_Delete_Task(Index);
 			}
 		}
 }
 }


 void SCH_Report_Status(void) {
 	#ifdef SCH_REPORT_ERRORS
 	//ONLYAPPLIES IFWEAREREPORTINGERRORS
 	// Check for a new error code
 	if (Error_code_G != Last_error_code_G) {
 		// Negative logic onLEDs assumed
 		Error_port = 255 − Error_code_G;
 		Last_error_code_G= Error_code_G;
 		if (Error_code_G != 0){
 			Error_tick_count_G= 60000;
 		} else {
 			Error_tick_count_G= 0;
 		}
 	} else {
 		if (Error_tick_count_G != 0){
 			if (−−Error_tick_count_G== 0) {
 				Error_code_G= 0; // Reset error code
 			}
 		}
 	}
 #endif
 }

 uint32_t SCH_Add_Task(void (* pFunction) (), uint32_t DELAY, uint32_t PERIOD){
 	unsigned char Index = 0;
 	// First find a gap in the array (if there is one)
 	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
 		Index++;
 	}
 	 // Have we reached the end of the list?
 	 if (Index ==SCH_MAX_TASKS){
 		 // Task list is full
 		 // Set the global error variable
 		 Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
 		 // Also return an error code
 		 return SCH_MAX_TASKS;
 	 }
 	 // If we’re here, there is a space in the task array
 	 SCH_tasks_G[Index].pTask = pFunction;
 	 SCH_tasks_G[Index].Delay = DELAY / TICK;
 	 SCH_tasks_G[Index].Period = PERIOD / TICK;
 	 SCH_tasks_G[Index].RunMe= 0;
 	 // return position of task (to allow later deletion)
 	 return Index;
 }

