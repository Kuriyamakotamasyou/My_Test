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

void DCAC_InnerSend(SendDataStruct_t* Struct){
	uint8_t index = 0;
	Struct->H_Cnt = 0;
	Struct->L_Cnt = 0;
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
}

void My_DCAC_Send(uint8_t Data){
	getSendDataStruct()->OriginalData = Data;
	SegmentData(getSendDataStruct(), getSendDataStruct()->OriginalData);
	DCAC_InnerSend(getSendDataStruct());
}


