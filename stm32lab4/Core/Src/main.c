/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#ifdef SCH_REPORT_ERRORS
#define Error_port PORTA
#endif
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
 	 }
 sTask;
 // MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS	40
#define NO_TASK_ID		0
sTask SCH_tasks_G[SCH_MAX_TASKS];
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
IWDG_HandleTypeDef hiwdg;
static uint32_t counter_for_watchdog = 0;
voidMX_IWDG_Init(void){
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
	hiwdg.Init.Reload = 4095;
	if (HAL_IWDG_Init(&hiwdg) !=HAL_OK) {
		Error_Handler();
	}
}
voidWatchdog_Refresh(void){
	HAL_IWDG_Refresh(&hiwdg);
}

unsigned char Is_Watchdog_Reset(void){
	if(counter_for_watchdog > 3){
		return 1;
	}
	return 0;
	}

voidWatchdog_Counting(void){
	counter_for_watchdog++;
}
void Reset_Watchdog_Counting(void){
	counter_for_watchdog = 0;
}

unsigned char SCH_Delete_Task(const tByte TASK_INDEX){
	unsigned char Return_code;
	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
		// No task at this location ...
		//
		// Set the global error variable
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK
		// ... also return an error code
		Return_code = RETURN_ERROR;
	} else {
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX]. Delay = 0;
	SCH_tasks_G[TASK_INDEX]. Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code; // return status
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
void SCH_Go_To_Sleep() {
}
void SCH_Init(void) {
	unsigned char i ;
	for (i = 0; i <SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
// Reset the global error variable
// − SCH_Delete_Task() will generate an error code,
// (because the task array is empty)
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
				SCH_tasks_G[Index].Delay −= 1;
			}
		}
	}
}
unsigned char SCH_Add_Task(void (* pFunction) (), unsigned int DELAY, unsigned int PERIOD){
	unsigned char Index = 0;
	// First find a gap in the array (if there is one)
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	 // Have we reached the end of the list?
	 if (Index ==SCH_MAX_TASKS){
		 // Task list is full
		 // Set the global error variable
		 Error_code_G=ERROR_SCH_TOO_MANY_TASKS;
		 // Also return an error code
		 return SCH_MAX_TASKS;
	 }
	 // If we’re here, there is a space in the task array
	 SCH_tasks_G[Index].pTask = pFunction;
	 SCH_tasks_G[Index].Delay =DELAY;
	 SCH_tasks_G[Index].Period =PERIOD;
	 SCH_tasks_G[Index].RunMe= 0;
	 // return position of task (to allow later deletion)
	 return Index;
}
void SCH_Dispatch_Tasks(void){
	unsigned char Index;
	// Dispatches (runs) the next task (if one is ready)
	for (Index = 0; Index <SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].RunMe> 0) {
			(*SCH_tasks_G[Index].pTask)(); // Run the task
			SCH_tasks_G[Index].RunMe −= 1; // Reset / reduceRunMe flag
			// Periodic tasks will automatically run again
			// − if this is a ’one shot’ task, remove it from the array
			if (SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
}
// Report system status
SCH_Report_Status();
// The scheduler enters idlemode at this point
SCH_Go_To_Sleep();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
