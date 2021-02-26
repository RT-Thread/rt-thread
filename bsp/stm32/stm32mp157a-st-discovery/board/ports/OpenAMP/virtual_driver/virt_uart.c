/**
  ******************************************************************************
  * @file    virt_uart.c
  * @author  MCD Application Team
  * @brief   UART HAL module driver.
  *          This file provides firmware functions to manage an rpmsg endpoint
  *          from user application
  *
  *
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
  [..]
    The VIRTUAL UART driver can be used as follows:
    (#) Initialize the Virtual UART by calling the VIRT_UART_Init() API.
        (++) create an endpoint. listener on the OpenAMP-rpmsg channel is now enabled.
        Receive data  is now possible if user registers a callback to this VIRTUAL UART instance
        by calling in providing a callback function when a message is received from
        remote processor (VIRT_UART_read_cb)
        OpenAMP MW deals with memory allocation/free and signal events
    (#) Transmit data on the created rpmsg channel by calling the VIRT_UART_Transmit()
    (#) Receive data in calling VIRT_UART_RegisterCallback to register user callback


  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "virt_uart.h"
#include "metal/utilities.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* this string will be sent to remote processor */
#define RPMSG_SERVICE_NAME              "rpmsg-tty-channel"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static int VIRT_UART_read_cb(struct rpmsg_endpoint *ept, void *data,
			    size_t len, uint32_t src, void *priv)
{
  VIRT_UART_HandleTypeDef *huart = metal_container_of(ept, VIRT_UART_HandleTypeDef, ept);
  (void)src;

  huart->pRxBuffPtr = data;
  huart->RxXferSize = len;
  if (huart->RxCpltCallback != NULL) {
    huart->RxCpltCallback(huart);
  }

  return 0;
}

VIRT_UART_StatusTypeDef VIRT_UART_Init(VIRT_UART_HandleTypeDef *huart)
{

  int status;

  /* Create a endpoint for rmpsg communication */

  status = OPENAMP_create_endpoint(&huart->ept, RPMSG_SERVICE_NAME, RPMSG_ADDR_ANY,
		  	  	  	  	  	  	   VIRT_UART_read_cb, NULL);

  if(status < 0) {
    return VIRT_UART_ERROR;
  }

  return VIRT_UART_OK;
}

VIRT_UART_StatusTypeDef VIRT_UART_DeInit (VIRT_UART_HandleTypeDef *huart)
{
  OPENAMP_destroy_ept(&huart->ept);

  return VIRT_UART_OK;
}

VIRT_UART_StatusTypeDef VIRT_UART_RegisterCallback(VIRT_UART_HandleTypeDef *huart,
                                                   VIRT_UART_CallbackIDTypeDef CallbackID,
                                                   void (* pCallback)(VIRT_UART_HandleTypeDef *_huart))
{
  VIRT_UART_StatusTypeDef status = VIRT_UART_OK;

  switch (CallbackID)
  {
  case VIRT_UART_RXCPLT_CB_ID :
    huart->RxCpltCallback = pCallback;
    break;

  default :
   /* Return error status */
    status =  VIRT_UART_ERROR;
    break;
  }
  return status;
}

VIRT_UART_StatusTypeDef VIRT_UART_Transmit(VIRT_UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
	int res;

	if (Size > (RPMSG_BUFFER_SIZE-16))
	  return VIRT_UART_ERROR;

	res = OPENAMP_send(&huart->ept, pData, Size);
	if (res <0) {
		return VIRT_UART_ERROR;
	}

	return VIRT_UART_OK;
}
