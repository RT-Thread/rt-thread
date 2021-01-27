/**
  **************************************************************************************
  * @file    type.h
  * @brief   Common types and macros.
  * @data    12/21/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __TYPES_H__
#define __TYPES_H__

//*****************************************************************************
//
// Macros for hardware access.
//
//*****************************************************************************
#define HWREG(x)                                                              \
  (*((volatile uint32_t *)(x)))
#define HWREGH(x)                                                             \
  (*((volatile uint16_t *)(x)))
#define HWREGB(x)                                                             \
  (*((volatile uint8_t *)(x)))
#define HWREGBITW(x, b)                                                       \
  HWREG(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                     \
        (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
  HWREGH(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
         (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
  HWREGB(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
         (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))


#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics Co., Ltd. *** END OF FILE ****/
