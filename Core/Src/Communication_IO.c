#include "Communication_IO.h"
#include "gpio.h"

SendDataStruct_t SendDataStruct;
SendDataStruct_t* getSendDataStruct(void){
	return &SendDataStruct;
}

void SegmentData(SendDataStruct_t* Struct, uint8_t Data){
	Struct->FourBit_H = (Data & 0xF0) >> 4;
	Struct->FourBit_L = (Data & 0x0F);
}

void My_DCAC_Send(uint8_t Data){
	getSendDataStruct()->OriginalData = Data;
	SegmentData(getSendDataStruct(), getSendDataStruct()->OriginalData);
	
}
