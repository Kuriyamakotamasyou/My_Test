/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "stdio.h"
#include "fatfs.h"
#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for LEDTASK */
osThreadId_t LEDTASKHandle;
const osThreadAttr_t LEDTASK_attributes = {
  .name = "LEDTASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SD_TASK */
osThreadId_t SD_TASKHandle;
const osThreadAttr_t SD_TASK_attributes = {
  .name = "SD_TASK",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LedTask(void *argument);
void sdCardUpdata(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LEDTASK */
  LEDTASKHandle = osThreadNew(LedTask, NULL, &LEDTASK_attributes);

  /* creation of SD_TASK */
  SD_TASKHandle = osThreadNew(sdCardUpdata, NULL, &SD_TASK_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_LedTask */
/**
  * @brief  Function implementing the LEDTASK thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LedTask */
void LedTask(void *argument)
{
  /* USER CODE BEGIN LedTask */
	uint8_t status = 0;
  /* Infinite loop */
  for(;;)
  {
	  
	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  printf("Running\r\n");
//	  if(status == 0){
//		uint8_t text[20];
//		sprintf((char *)&text, "What we use, what");
//		LCD_ShowString(4, 20, ST7735Ctx.Width, 16, 16, text);
//	
//		sprintf((char *)&text, "increases the price");
//		LCD_ShowString(4, 40, ST7735Ctx.Width, 16, 16, text);
//		  
//	  }
//	  else
//		  ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, ST7735Ctx.Width,ST7735Ctx.Height, BLACK);
//	  status = !status;
    osDelay(500);
  }
  /* USER CODE END LedTask */
}

/* USER CODE BEGIN Header_sdCardUpdata */
/**
* @brief Function implementing the SD_TASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sdCardUpdata */
void sdCardUpdata(void *argument)
{
  /* USER CODE BEGIN sdCardUpdata */
  /* Infinite loop */
  for(;;)
  {
//	  test();
    osDelay(1000);
  }
  /* USER CODE END sdCardUpdata */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

