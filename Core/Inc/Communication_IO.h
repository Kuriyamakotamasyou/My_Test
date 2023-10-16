#ifndef __COMMUNICATION_IO_H
#define __COMMUNICATION_IO_H

#include "stm32h7xx_hal.h"
//#include "tim.h"

#define DATA_A_TX_H_H	LL_GPIO_SetOutputPin(Data_A_TX_H_GPIO_Port, Data_A_TX_H_Pin)
#define DATA_A_TX_H_L	LL_GPIO_ResetOutputPin(Data_A_TX_H_GPIO_Port, Data_A_TX_H_Pin)

#define DATA_A_TX_L_H	LL_GPIO_SetOutputPin(Data_A_TX_L_GPIO_Port, Data_A_TX_L_Pin)
#define DATA_A_TX_L_L	LL_GPIO_ResetOutputPin(Data_A_TX_L_GPIO_Port, Data_A_TX_L_Pin)

typedef struct {
	uint8_t OriginalData;
	uint8_t FourBit_H;
	uint8_t FourBit_L;
	uint8_t H_Cnt;
	uint8_t L_Cnt;
}SendDataStruct_t;

SendDataStruct_t* getSendDataStruct(void);
void My_DCAC_Send(uint8_t Data);

#endif
