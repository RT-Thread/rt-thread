/**
  ******************************************************************************
  * @file    log.c
  * @author  MCD Application Team
  * @brief   Ressource table
  *
  *   This file provides services for logging
  *
  ******************************************************************************
  *
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  *
  ******************************************************************************
  */
/** @addtogroup LOG
  * @{
  */

/** @addtogroup STM32MP1xx_log
  * @{
  */

/** @addtogroup STM32MP1xx_Log_Private_Includes
  * @{
  */
#include "openamp_log.h"
/**
  * @}
  */

/** @addtogroup STM32MP1xx_Log_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32MP1xx_Log_Private_Defines
  * @{
  */

/**
  * @}
  */

#if defined (__LOG_TRACE_IO_)
char system_log_buf[SYSTEM_TRACE_BUF_SZ];

__weak void log_buff(int ch)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
 static int offset = 0;

	if (offset + 1 >= SYSTEM_TRACE_BUF_SZ)
		offset = 0;

	system_log_buf[offset] = ch;
	system_log_buf[offset++ + 1] = '\0';
}

#endif

#if defined ( __CC_ARM) || (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define PUTCHAR_PROTOTYPE int stdout_putchar(int ch)
#elif __GNUC__
/* With GCC/RAISONANCE, small log_info (option LD Linker->Libraries->Small log_info
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __attribute__(( weak )) __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int __attribute__(( weak )) fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#if defined (__LOG_UART_IO_) || defined (__LOG_TRACE_IO_)
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
#if defined (__LOG_UART_IO_)
extern UART_HandleTypeDef huart;
  HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
#endif
#if defined (__LOG_TRACE_IO_)
	log_buff(ch);
#endif
	return ch;
}
#else
/* No printf output */
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
