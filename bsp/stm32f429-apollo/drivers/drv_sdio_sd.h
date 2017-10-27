#ifndef _SDMMC_SDCARD_H
#define _SDMMC_SDCARD_H
#include <rtthread.h>
#include <board.h>
#include "stm32f4xx.h"
#include <rtdevice.h>


#define SD_TIMEOUT ((uint32_t)100000000)            //超时时间

#define SD_DMA_MODE    		0	//1：DMA模式，0：查询模式   

extern SD_HandleTypeDef        SDCARD_Handler;     //SD卡句柄
extern HAL_SD_CardInfoTypedef  SDCardInfo;         //SD卡信息结构体

rt_uint8_t SD_Init(void);
rt_uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypedef *cardinfo);

#endif
