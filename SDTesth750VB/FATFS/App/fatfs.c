/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
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
#include "fatfs.h"

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

/* USER CODE BEGIN Variables */
#include "usart.h"
#include "stdio.h"
/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

  /* USER CODE BEGIN Init */
  /* additional user code for init */
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */
void test(void){
	UINT bw;
	
	uint8_t status;
	uint8_t text[] = "stm32H750VBT6_SDCardTest";
	
	status = f_mount(&SDFatFS, (const TCHAR*)SDPath, 0);
	if(status == FR_OK)
		printf("mount_success\r\n");
	
	status = f_open(&SDFile,"stm32Test.txt", FA_OPEN_ALWAYS | FA_OPEN_APPEND | FA_WRITE);
	if(status == FR_OK)
		printf("open_success\r\n");
	status = f_write(&SDFile, text, 25, &bw);
	if(status == FR_OK)
		printf("write_success\r\n");
	status = f_close(&SDFile);
	if(status == FR_OK)
		printf("close_success\r\n");
	
}
/* USER CODE END Application */
