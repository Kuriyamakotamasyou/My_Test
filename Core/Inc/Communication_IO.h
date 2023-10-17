#ifndef __COMMUNICATION_IO_H
#define __COMMUNICATION_IO_H

#include "stm32h7xx_hal.h"
//#include "tim.h"

#define DATA_A_TX_H_H	LL_GPIO_SetOutputPin(Data_A_TX_H_GPIO_Port, Data_A_TX_H_Pin)
#define DATA_A_TX_H_L	LL_GPIO_ResetOutputPin(Data_A_TX_H_GPIO_Port, Data_A_TX_H_Pin)

#define DATA_A_TX_L_H	LL_GPIO_SetOutputPin(Data_A_TX_L_GPIO_Port, Data_A_TX_L_Pin)
#define DATA_A_TX_L_L	LL_GPIO_ResetOutputPin(Data_A_TX_L_GPIO_Port, Data_A_TX_L_Pin)

#define LENTH_FOR_END_CODE	3	
#define INCZEROLENTH		1
#define INCZEROADD			2

#define PHASESTOP	0
#define PHASEDOING	1

enum {
	DISINCZERO = 0,
	INCZERO
};

typedef struct {
	uint8_t SendIncZeroStatus;
	uint8_t DataPhaseStatus;
	uint8_t EndCodePhaseStatus;
	uint8_t DataHigh4BitTransferStatus;
	uint8_t DataLow4BitTransferStatus;
}DCACTransferStatus_t;

typedef struct {
	uint8_t OriginalData;
	uint8_t FourBit_H;
	uint8_t FourBit_L;
	uint8_t H_Cnt;
	uint8_t L_Cnt;
	
	uint8_t LenthForData;
	uint8_t EndCodeCnt;
	
	
	DCACTransferStatus_t DCACTransferStatus;
}SendDataStruct_t;

SendDataStruct_t* getSendDataStruct(void);
void DataPhaseSendChar(uint8_t Data);
void My_DCAC_Send(uint8_t Data);
void DCACNetSendString(uint8_t* pData, uint8_t Lenth);

#endif
