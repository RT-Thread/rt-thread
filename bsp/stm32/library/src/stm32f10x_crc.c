/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_crc.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the CRC firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_crc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* CR register bit mask */
#define CR_RESET_Set    ((u32)0x00000001)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : CRC_ResetDR
* Description    : Resets the CRC Data register (DR).
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR = CR_RESET_Set;
}

/*******************************************************************************
* Function Name  : CRC_CalcCRC
* Description    : Computes the 32-bit CRC of a given data word(32-bit).
* Input          : - Data: data word(32-bit) to compute its CRC
* Output         : None
* Return         : 32-bit CRC
*******************************************************************************/
u32 CRC_CalcCRC(u32 Data)
{
  CRC->DR = Data;
  
  return (CRC->DR);
}

/*******************************************************************************
* Function Name  : CRC_CalcBlockCRC
* Description    : Computes the 32-bit CRC of a given buffer of data word(32-bit).
* Input          : - pBuffer: pointer to the buffer containing the data to be 
*                    computed
*                  - BufferLength: length of the buffer to be computed					
* Output         : None
* Return         : 32-bit CRC
*******************************************************************************/
u32 CRC_CalcBlockCRC(u32 pBuffer[], u32 BufferLength)
{
  u32 index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }

  return (CRC->DR);
}

/*******************************************************************************
* Function Name  : CRC_GetCRC
* Description    : Returns the current CRC value.
* Input          : None
* Output         : None
* Return         : 32-bit CRC
*******************************************************************************/
u32 CRC_GetCRC(void)
{
  return (CRC->DR);
}

/*******************************************************************************
* Function Name  : CRC_SetIDRegister
* Description    : Stores a 8-bit data in the Independent Data(ID) register.
* Input          : - IDValue: 8-bit value to be stored in the ID register 					
* Output         : None
* Return         : None
*******************************************************************************/
void CRC_SetIDRegister(u8 IDValue)
{
  CRC->IDR = IDValue;
}

/*******************************************************************************
* Function Name  : CRC_GetIDRegister
* Description    : Returns the 8-bit data stored in the Independent Data(ID) register
* Input          : None
* Output         : None
* Return         : 8-bit value of the ID register 
*******************************************************************************/
u8 CRC_GetIDRegister(void)
{
  return (CRC->IDR);
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
