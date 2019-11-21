/**
  ******************************************************************************
  * @file    md_uart.c
  * @brief   ES32F0271 UART Source File.
  *
  * @version V1.00.01
  * @date    04/12/2018
  * @author  Eastsoft AE Team
  * @note    UART Public Functions
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "system_es32f027x.h"
#include "md_uart.h"

/** @addtogroup Micro_Driver
  * @{
  */

/** @defgroup UART UART
  * @brief UART micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------*/

/* Public functions -----------------------------------------------------------*/

/** @defgroup UART_PUB_FUNC UART Public Functions
  * @brief UART Public Functions
  * @{
  */
/**
  * @brief  Set UART1 baudrate.
  * @param  UARTx UART Instance.
  * @param  Baudrate
  * @retval None.
  */
void md_uart_set_baudrate(UART_TypeDef *UARTx, uint32_t baudrate)
{
  uint32_t brr;
  brr = ((SystemFrequency_APBClk + (baudrate >> 1)) / baudrate);
  md_uart_set_brr(UARTx, brr);
}

/**
  * @brief  UART Initialization
  * @param  UART Init Structure
  * @retval None
  */
void md_uart_init(UART_TypeDef *UARTx, md_uart_init_typedef *UART_InitStruct)
{
  /* Check the UART_InitStruct */
  assert_param((UART_InitStruct != NULL));

  md_uart_set_baudrate(UARTx, MD_UART_BAUDRATE_115200);
  md_uart_disable_lcon_txen(UARTx);
  md_uart_disable_lcon_rxen(UARTx);
  md_uart_set_lcon_dls(UARTx, UART_InitStruct->DataWidth);
  md_uart_set_lcon_stop(UARTx, UART_InitStruct->StopBits);
  md_uart_set_lcon_ps(UARTx, UART_InitStruct->Parity);
  md_uart_enable_lcon_pe(UARTx);
  md_uart_set_fcon_tfrst(UARTx);
  md_uart_set_fcon_rfrst(UARTx);
  md_uart_enable_lcon_txen(UARTx);
  md_uart_enable_lcon_rxen(UARTx);
}

/**
  * @brief  UART1 send character
  * @param  Character
  * @retval None
  */
void md_uart_send(UART_TypeDef *UARTx, uint8_t ch)
{
  while (md_uart_is_active_flag_stat_tffull(UARTx)); // Tx FIFO full

  md_uart_send_txbuf(UART1, ch);                    // Sent byte
}

/**
  * @brief  UART1 receive character.
  * @param  UART_TypeDef *UARTx.
  * @retval unsigned char.
  */
uint8_t md_uart_recv(UART_TypeDef *UARTx)
{
  while (md_uart_is_active_flag_stat_rfempty(UART1));           // Rx FIFO empty

  return (md_uart_get_rxbuf(UART1));
}

/**
  * @brief  Get UARTx baudrate.
  * @param  UART_TypeDef *UARTx.
  * @retval Baudrate.
  */
uint32_t md_uart_get_baudrate(UART_TypeDef *UARTx)
{
  uint32_t brr, baudrate;

  brr = md_uart_get_brr(UARTx);
  baudrate = SystemFrequency_APBClk / brr;
  return baudrate;
}


/**
  * @} UART_PUB_FUNC UART Public Functions
  */

/**
  * @} UART
  */

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
