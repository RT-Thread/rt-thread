/***********************************************************************
 * Copyright (c)  2008 - 2016, Shanghai AisinoChip Co.,Ltd .
 * All rights reserved.
 * Filename    : HAL_HRNG.h
 * Description : hrng header file
 * Author(s)   : Eric
 * version     : V1.0
 * Modify date : 2021-03-24
 ***********************************************************************/
#ifndef __HAL_HRNG_H__
#define __HAL_HRNG_H__
#include "ACM32Fxx_HAL.h"


/*********************************************************************************
* Function Name  : HAL_HRNG_Initial
* Description    : intial hrng module
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void HAL_HRNG_Initial(void);

/*********************************************************************************
* Function Name  : HAL_HRNG_Source_Disable
* Description    : disable hrng source
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void HAL_HRNG_Source_Disable(void);

/*********************************************************************************
* Function Name  : HAL_HRNG_GetHrng
* Description    : get random number
* Input          : byte_len :  the byte length of random number
* Output         : *hdata   :  the start address of random number the size must be 16bytes
* Return         : 0: hrng data is ok; 1: hrng data is bad
*********************************************************************************/
UINT8 HAL_HRNG_GetHrng(UINT8 *hdata, UINT32 byte_len);

#endif



