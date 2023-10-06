#include "FileManage.h"
#include "stdio.h"
#include "stdlib.h"


uint8_t ResByte;

FRESULT SdCardLoad(void){
	ResByte = f_mount(&SDFatFS, (const TCHAR*)SDPath, 0);
	return ResByte;
}

FRESULT SdCardOpen_MkFile(uint8_t* FileName){
	ResByte = f_open(&SDFile, FileName, FA_OPEN_ALWAYS | FA_OPEN_APPEND | FA_WRITE);
	return ResByte;
}
