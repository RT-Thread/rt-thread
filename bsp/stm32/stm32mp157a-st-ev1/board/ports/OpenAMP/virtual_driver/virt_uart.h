/**
  ******************************************************************************
  * @file    virt_uart.h
  * @author  MCD Application Team
  * @brief   Header file of UART VIRT module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VIRT_UART_H
#define __VIRT_UART_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "openamp.h"

/* Exported structures --------------------------------------------------------*/
typedef struct __VIRT_UART_HandleTypeDef
{
  struct rpmsg_endpoint ept;          /*!< rpmsg endpoint                             */
  struct rpmsg_virtio_device *rvdev;  /*< pointer to the rpmsg virtio device          */
  uint8_t              *pRxBuffPtr;   /*!< Pointer to VIRTUAL UART Rx transfer Buffer */
  uint16_t              RxXferSize;   /*!< VIRTUAL UART Rx Transfer size              */
  void    (* RxCpltCallback)( struct __VIRT_UART_HandleTypeDef * hppp);    /*!< RX CPLT callback    */
}VIRT_UART_HandleTypeDef;


typedef enum
{
  VIRT_UART_OK       = 0x00U,
  VIRT_UART_ERROR    = 0x01U,
  VIRT_UART_BUSY     = 0x02U,
  VIRT_UART_TIMEOUT  = 0x03U
} VIRT_UART_StatusTypeDef;


typedef enum
{
  VIRT_UART_RXCPLT_CB_ID          = 0x00U,    /*!< PPP event 1 callback ID     */
}VIRT_UART_CallbackIDTypeDef;


/* Exported functions --------------------------------------------------------*/
/* Initialization and de-initialization functions  ****************************/
VIRT_UART_StatusTypeDef VIRT_UART_Init(VIRT_UART_HandleTypeDef *huart);
VIRT_UART_StatusTypeDef VIRT_UART_DeInit (VIRT_UART_HandleTypeDef *huart);
VIRT_UART_StatusTypeDef VIRT_UART_RegisterCallback(VIRT_UART_HandleTypeDef *huart,
                                                   VIRT_UART_CallbackIDTypeDef CallbackID,
                                                   void (* pCallback)(VIRT_UART_HandleTypeDef *_huart));

/* IO operation functions *****************************************************/
VIRT_UART_StatusTypeDef VIRT_UART_Transmit(VIRT_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);


#ifdef __cplusplus
}
#endif

#endif /* __VIRT_UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
