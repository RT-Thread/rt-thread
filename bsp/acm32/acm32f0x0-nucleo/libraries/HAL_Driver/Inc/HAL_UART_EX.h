/*
  ******************************************************************************
  * @file    HAL_UART_EX.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of UART EX HAL module.
  ******************************************************************************
*/
#ifndef __HAL_UART_EX_H__
#define __HAL_UART_EX_H__

#include "ACM32Fxx_HAL.h"

/****************  Bit definition for UART IE register  ***********************/
#define UART_EX_IE_BCNTI                    BIT12
#define UART_EX_IE_LBDI                     BIT11

/****************  Bit definition for UART RIS register  ***********************/
#define UART_EX_RIS_BCNTI                   BIT12
#define UART_EX_RIS_LBDI                    BIT11

/****************  Bit definition for UART BCNT register  ***********************/
#define UART_EX_BCNT_START                   BIT8
#define UART_EX_BCNT_VALUE_POS              (0U)
#define UART_EX_BCNT_VALUE_MASK             (0xFFU)

/****************  Definition of LIN BUS VERSION  ***********************/
#define UART_LIN_V1D3         0    //Lin bus version 1.3
#define UART_LIN_V2DX         1    //Lin bus version 2.0/2.1/2.2

void HAL_UART_LIN_Master_Transmit(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t Lin_Id, uint8_t *pData, uint8_t Size);
void HAL_UART_LIN_Slave_Transmit(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t Lin_Id, uint8_t *pData, uint8_t Size);
uint8_t HAL_UART_LIN_Master_Receive(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t Lin_Id, uint8_t *pData, uint32_t Timeout);
uint8_t HAL_UART_LIN_Slave_Receive(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t *pData, uint32_t Timeout);

#endif
