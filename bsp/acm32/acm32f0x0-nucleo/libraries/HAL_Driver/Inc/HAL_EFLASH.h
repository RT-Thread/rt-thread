/*
  ******************************************************************************
  * @file    HAL_EFlash.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of EFlash HAL module.
  ******************************************************************************
*/
#ifndef __HAL_EFlash_H__
#define __HAL_EFlash_H__

#include "ACM32Fxx_HAL.h"

#define EFLASH_PAGE_SIZE    (512UL)

#define HAL_EFLASH_READ_WORD(Addr)        (*(volatile uint32_t *)(Addr))    // Read By Word
#define HAL_EFLASH_READ_HALFWORD(Addr)    (*(volatile uint16_t *)(Addr))    // Read By Half Word
#define HAL_EFLASH_READ_BYTE(Addr)        (*(volatile uint8_t *)(Addr))     // Read By Byte

/********************  Bit definition for EFC_CTRL register  ******************/
#define EFC_CTRL_CHIP_ERASE_MODE        (1 << 2)
#define EFC_CTRL_PAGE_ERASE_MODE        (1 << 1)
#define EFC_CTRL_PROGRAM_MODE           (1 << 0)

#define EFLASH_RD_WAIT_POS   7
/********************  Bit definition for EFC_STATUS register  ***************/
#define EFC_STATUS_EFLASH_RDY           (1 << 0)

#define SET_EFC_RD_WAIT(wait)     {EFC->CTRL   = (EFC->CTRL & ~(0x1F << 7)) | (wait << 7);}

/* Exported functions --------------------------------------------------------*/

/* HAL_EFlash_Init */
void HAL_EFlash_Init(uint32_t fu32_freq);
/* HAL_EFlash_ErasePage */
bool HAL_EFlash_ErasePage(uint32_t fu32_Addr);

/* HAL_EFlash_Program_Word */
bool HAL_EFlash_Program_Word(uint32_t fu32_Addr, uint32_t fu32_Data);

#endif
