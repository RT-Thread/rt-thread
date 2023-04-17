/*
  ******************************************************************************
  * @file    HAL_EFlash_EX.h
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of EFlash extention module
  ******************************************************************************
*/
#ifndef __HAL_EFlash_EX_H__
#define __HAL_EFlash_EX_H__

#include "stdint.h"

/* HAL_EFlash_Return_To_Boot */
void HAL_EFlash_Return_to_Boot(void);

/* HAL_EFlash_Init_Para */
void HAL_EFlash_Init_Para(uint32_t fu32_freq);

/* HAL_EFlash_ErasePage_EX */
void HAL_EFlash_ErasePage_EX(uint32_t fu32_Addr);

/* HAL_EFlash_Program_Word_EX */
void HAL_EFlash_Program_Word_EX(uint32_t fu32_Addr, uint32_t fu32_Data);

#endif
