#include "usDelay.h"
#include "tim.h"

void Delay_us(uint32_t time_us){

    uint16_t  differ = 0xffff - time_us - 5;
    //设置定时器2的技术初始值
  __HAL_TIM_SetCounter(&htim6, differ);
  //开启定时器
  HAL_TIM_Base_Start(&htim6);

  while(differ < (0xffff - 5)){
        differ = __HAL_TIM_GetCounter(&htim6);
    };
 //关闭定时器
  HAL_TIM_Base_Stop(&htim6);
}
