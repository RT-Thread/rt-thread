/***********************************************************************f
 * Filename    : hrng.h
 * Description : hrng header file
 * Author(s)   : cc  
 * version     : V1.0
 * Modify date : 2021-03-24
 ***********************************************************************/

#ifndef __HRNG_H__
#define __HRNG_H__

#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function Name  : HAL_HRNG_Initial
* Description    : initial hrng module
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void HAL_HRNG_Initial(void);

/*********************************************************************************
* Function Name  : HAL_HRNG_GetHrng_8
* Description    : get 8bit random number
* Input          : None
* Output         : None
* Return         : 8 bit random number
*********************************************************************************/
UINT8 HAL_HRNG_GetHrng_8(void);

/*********************************************************************************
* Function Name  : HAL_HRNG_GetHrng_32
* Description    : get 32bit random number
* Input          : None
* Output         : None
* Return         : 32 bit random number
*********************************************************************************/
UINT32 HAL_HRNG_GetHrng_32(void);

/*********************************************************************************
* Function Name  : HAL_HRNG_GetHrng
* Description    : get random number
* Input          : byte_len :  the byte length of random number
* Output         : *hdata   :  the start address of random number
* Return         : 0: hrng data is ok; 1: hrng data is bad
*********************************************************************************/
UINT8 HAL_HRNG_GetHrng(UINT8 *hdata, UINT32 byte_len);

#endif



