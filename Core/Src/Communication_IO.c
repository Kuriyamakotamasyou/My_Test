#include "Communication_IO.h"
#include "gpio.h"
#include "usDelay.h"


SendDataStruct_t SendDataStruct;
SendDataStruct_t* getSendDataStruct(void){
	return &SendDataStruct;
}

void SegmentData(SendDataStruct_t* Struct, uint8_t Data){
	Struct->FourBit_H = (Data & 0xF0) >> 4;
	Struct->FourBit_L = (Data & 0x0F);
}

void DataCheck(SendDataStruct_t* Struct){
	if(Struct->FourBit_H == 0x00 || Struct->FourBit_L == 0x00){
		Struct->DCACTransferStatus.SendIncZeroStatus = INCZERO;
	}
	else
		Struct->DCACTransferStatus.SendIncZeroStatus = DISINCZERO;
}

void IncZeroDataProcess(SendDataStruct_t* Data_Struct){
	Data_Struct->FourBit_H += INCZEROADD;
	Data_Struct->FourBit_L += INCZEROADD;
}

void NonZeroDataPhaseCharSend(void){
	uint8_t index = 0;
	/*****************数据段发送起始*********************/
	getSendDataStruct()->DCACTransferStatus.DataPhaseStatus = PHASEDOING;
	getSendDataStruct()->H_Cnt = 0;
	getSendDataStruct()->L_Cnt = 0;
	
	getSendDataStruct()->LenthForData = getSendDataStruct()->FourBit_H + getSendDataStruct()->FourBit_L;
	
	for(index = 0; index < getSendDataStruct()->LenthForData; index++){
		if(getSendDataStruct()->H_Cnt < getSendDataStruct()->FourBit_H){
			getSendDataStruct()->DCACTransferStatus.DataHigh4BitTransferStatus = PHASEDOING;
			getSendDataStruct()->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
			DATA_A_TX_H_H;
			Delay_us(10);
			DATA_A_TX_H_L;
			Delay_us(10);
			getSendDataStruct()->H_Cnt++;
		}
		else if(getSendDataStruct()->L_Cnt < getSendDataStruct()->FourBit_L){
			getSendDataStruct()->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
			getSendDataStruct()->DCACTransferStatus.DataLow4BitTransferStatus = PHASEDOING;
			DATA_A_TX_L_H;
			Delay_us(10);
			DATA_A_TX_L_L;
			Delay_us(10);
			getSendDataStruct()->L_Cnt++;
		}
	}
	getSendDataStruct()->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
	getSendDataStruct()->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
	getSendDataStruct()->DCACTransferStatus.DataPhaseStatus = PHASESTOP;
	/************************数据段结束************************/
}

void IncZeroDataPhaseCharSend(void){
	uint8_t index = 0;
	
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	/*****************0x11发送***************************/
	for(index = 0; index < INCZEROLENTH; index++){
		DATA_A_TX_H_H;
		DATA_A_TX_L_L;
		Delay_us(10);
		DATA_A_TX_H_L;
		DATA_A_TX_L_H;
		Delay_us(10);
	}
	/*****************0x11发送结束***********************/
	
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	IncZeroDataProcess(getSendDataStruct());
	
	/*****************数据段发送起始*********************/
	getSendDataStruct()->DCACTransferStatus.DataPhaseStatus = PHASEDOING;
	getSendDataStruct()->H_Cnt = 0;
	getSendDataStruct()->L_Cnt = 0;
	
	getSendDataStruct()->LenthForData = getSendDataStruct()->FourBit_H + getSendDataStruct()->FourBit_L;
	
	for(index = 0; index < getSendDataStruct()->LenthForData; index++){
		if(getSendDataStruct()->H_Cnt < getSendDataStruct()->FourBit_H){
			getSendDataStruct()->DCACTransferStatus.DataHigh4BitTransferStatus = PHASEDOING;
			getSendDataStruct()->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
			DATA_A_TX_H_H;
			Delay_us(10);
			DATA_A_TX_H_L;
			Delay_us(10);
			getSendDataStruct()->H_Cnt++;
		}
		else if(getSendDataStruct()->L_Cnt < getSendDataStruct()->FourBit_L){
			getSendDataStruct()->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
			getSendDataStruct()->DCACTransferStatus.DataLow4BitTransferStatus = PHASEDOING;
			DATA_A_TX_L_H;
			Delay_us(10);
			DATA_A_TX_L_L;
			Delay_us(10);
			getSendDataStruct()->L_Cnt++;
		}
	}
	getSendDataStruct()->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
	getSendDataStruct()->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
	getSendDataStruct()->DCACTransferStatus.DataPhaseStatus = PHASESTOP;
	/************************数据段结束************************/
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
}

void DataPhaseSendChar(uint8_t Data){
	uint8_t index = 0;
	
	getSendDataStruct()->OriginalData = Data;
	SegmentData(getSendDataStruct(), getSendDataStruct()->OriginalData);
	
	DataCheck(getSendDataStruct());
	
	switch(getSendDataStruct()->DCACTransferStatus.SendIncZeroStatus){
		case DISINCZERO:{
			NonZeroDataPhaseCharSend();
		}break;
		case INCZERO:{
			IncZeroDataPhaseCharSend();
		}break;
	}
}

void NonZeroSendData(SendDataStruct_t* Data_Struct){
	uint8_t index = 0;
	
	/*****************数据段发送起始*********************/
	Data_Struct->DCACTransferStatus.DataPhaseStatus = PHASEDOING;
	Data_Struct->H_Cnt = 0;
	Data_Struct->L_Cnt = 0;
	
	Data_Struct->LenthForData = Data_Struct->FourBit_H + Data_Struct->FourBit_L;
	
	for(index = 0; index < Data_Struct->LenthForData; index++){
		if(Data_Struct->H_Cnt < Data_Struct->FourBit_H){
			Data_Struct->DCACTransferStatus.DataHigh4BitTransferStatus = PHASEDOING;
			Data_Struct->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
			DATA_A_TX_H_H;
			Delay_us(10);
			DATA_A_TX_H_L;
			Delay_us(10);
			Data_Struct->H_Cnt++;
		}
		else if(Data_Struct->L_Cnt < Data_Struct->FourBit_L){
			Data_Struct->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
			Data_Struct->DCACTransferStatus.DataLow4BitTransferStatus = PHASEDOING;
			DATA_A_TX_L_H;
			Delay_us(10);
			DATA_A_TX_L_L;
			Delay_us(10);
			Data_Struct->L_Cnt++;
		}
	}
	Data_Struct->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
	Data_Struct->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
	Data_Struct->DCACTransferStatus.DataPhaseStatus = PHASESTOP;
	/************************数据段结束************************/
	
	/************************终止位起始************************/
	Data_Struct->DCACTransferStatus.EndCodePhaseStatus = PHASEDOING;
	
	for(index = 0; index < LENTH_FOR_END_CODE; index++){
		DATA_A_TX_H_H;
		DATA_A_TX_L_L;
		Delay_us(10);
		DATA_A_TX_H_L;
		DATA_A_TX_L_H;
		Delay_us(10);
	}
	/************************终止位结束************************/
}



void IncZeroSendData(SendDataStruct_t* Data_Struct){
	uint8_t index = 0;
	
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	/*****************0x11发送***************************/
	for(index = 0; index < INCZEROLENTH; index++){
		DATA_A_TX_H_H;
		DATA_A_TX_L_L;
		Delay_us(10);
		DATA_A_TX_H_L;
		DATA_A_TX_L_H;
		Delay_us(10);
	}
	/*****************0x11发送结束***********************/
	
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	IncZeroDataProcess(Data_Struct);
	
	/*****************数据段发送起始*********************/
	Data_Struct->DCACTransferStatus.DataPhaseStatus = PHASEDOING;
	Data_Struct->H_Cnt = 0;
	Data_Struct->L_Cnt = 0;
	
	Data_Struct->LenthForData = Data_Struct->FourBit_H + Data_Struct->FourBit_L;
	
	for(index = 0; index < Data_Struct->LenthForData; index++){
		if(Data_Struct->H_Cnt < Data_Struct->FourBit_H){
			Data_Struct->DCACTransferStatus.DataHigh4BitTransferStatus = PHASEDOING;
			Data_Struct->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
			DATA_A_TX_H_H;
			Delay_us(10);
			DATA_A_TX_H_L;
			Delay_us(10);
			Data_Struct->H_Cnt++;
		}
		else if(Data_Struct->L_Cnt < Data_Struct->FourBit_L){
			Data_Struct->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
			Data_Struct->DCACTransferStatus.DataLow4BitTransferStatus = PHASEDOING;
			DATA_A_TX_L_H;
			Delay_us(10);
			DATA_A_TX_L_L;
			Delay_us(10);
			Data_Struct->L_Cnt++;
		}
	}
	Data_Struct->DCACTransferStatus.DataHigh4BitTransferStatus = PHASESTOP;
	Data_Struct->DCACTransferStatus.DataLow4BitTransferStatus = PHASESTOP;
	Data_Struct->DCACTransferStatus.DataPhaseStatus = PHASESTOP;
	/************************数据段结束************************/
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	
	/************************终止位起始************************/
	Data_Struct->DCACTransferStatus.EndCodePhaseStatus = PHASEDOING;
	
	for(index = 0; index < LENTH_FOR_END_CODE; index++){
		DATA_A_TX_H_H;
		DATA_A_TX_L_L;
		Delay_us(10);
		DATA_A_TX_H_L;
		DATA_A_TX_L_H;
		Delay_us(10);
	}
	/************************终止位结束************************/
}

void DCACNetSendString(uint8_t* pData, uint8_t Lenth){
	uint8_t index = 0;
	
	for(index = 0; index < Lenth; index++){
		DataPhaseSendChar(*(pData++));
	}
	
	/************************终止位起始************************/
	for(index = 0; index < LENTH_FOR_END_CODE; index++){
		DATA_A_TX_H_H;
		DATA_A_TX_L_L;
		Delay_us(10);
		DATA_A_TX_H_L;
		DATA_A_TX_L_H;
		Delay_us(10);
	}
	/************************终止位结束************************/
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
}

void DCAC_InnerSend(SendDataStruct_t* Struct){
	DataCheck(Struct);
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	switch(Struct->DCACTransferStatus.SendIncZeroStatus){
		case DISINCZERO:{
			NonZeroSendData(Struct);
		}break;
		case INCZERO:{
			IncZeroSendData(Struct);
		}break;
	}
	DATA_A_TX_H_L;
	DATA_A_TX_L_L;
	/*
	for(index = 0 ; index < ((Struct->FourBit_H > Struct->FourBit_L) ? Struct->FourBit_H : Struct->FourBit_L); index++){
		if(Struct->H_Cnt < Struct->FourBit_H && Struct->L_Cnt < Struct->FourBit_L){
			DATA_A_TX_H_H;
			DATA_A_TX_L_H;
			Delay_us(10);
			DATA_A_TX_H_L;
			DATA_A_TX_L_L;
			Delay_us(10);
			Struct->H_Cnt++;
			Struct->L_Cnt++;
		}
		else if(Struct->H_Cnt < Struct->FourBit_H && Struct->L_Cnt >= Struct->FourBit_L){
			DATA_A_TX_H_H;
			Delay_us(10);
			DATA_A_TX_H_L;
			Delay_us(10);
			Struct->H_Cnt++;
		}
		else if(Struct->H_Cnt >= Struct->FourBit_H && Struct->L_Cnt < Struct->FourBit_L){
			DATA_A_TX_L_H;
			Delay_us(10);
			DATA_A_TX_L_L;
			Delay_us(10);
			Struct->L_Cnt++;
		}
	}
	*/
}

void My_DCAC_Send(uint8_t Data){
	getSendDataStruct()->OriginalData = Data;
	SegmentData(getSendDataStruct(), getSendDataStruct()->OriginalData);
	DCAC_InnerSend(getSendDataStruct());
}

void My_DCAC_SendString(uint8_t* Data){
	
}


