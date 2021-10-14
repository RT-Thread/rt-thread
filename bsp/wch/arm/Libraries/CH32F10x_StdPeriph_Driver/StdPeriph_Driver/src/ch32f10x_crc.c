/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_crc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file provides all the CRC firmware functions. 
*******************************************************************************/ 
#include "ch32f10x_crc.h"


/*******************************************************************************
* Function Name  : CRC_ResetDR
* Description    : Resets the CRC Data register (DR). 
* Input          : None
* Return         : None
*******************************************************************************/
void CRC_ResetDR(void)
{
  CRC->CTLR = CRC_CTLR_RESET;
}

/*******************************************************************************
* Function Name  : CRC_CalcCRC
* Description    : Computes the 32-bit CRC of a given data word(32-bit). 
* Input          : Data: data word(32-bit) to compute its CRC.
* Return         : 32-bit CRC.
*******************************************************************************/
uint32_t CRC_CalcCRC(uint32_t Data)
{
  CRC->DATAR = Data;
  
  return (CRC->DATAR);
}

/*******************************************************************************
* Function Name  : CRC_CalcBlockCRC
* Description    : Computes the 32-bit CRC of a given buffer of data word(32-bit).
* Input          : pBuffer: pointer to the buffer containing the data to be computed.
*                  BufferLength: length of the buffer to be computed.		
* Return         : 32-bit CRC.
*******************************************************************************/
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    CRC->DATAR = pBuffer[index];
  }
	
  return (CRC->DATAR);
}

/*******************************************************************************
* Function Name  : CRC_GetCRC
* Description    : Returns the current CRC value.
* Input          : None
* Return         : 32-bit CRC.
*******************************************************************************/
uint32_t CRC_GetCRC(void)
{
  return (CRC->IDATAR);
}

/*******************************************************************************
* Function Name  : CRC_SetIDRegister
* Description    : Stores a 8-bit data in the Independent Data(ID) register.
* Input          : IDValue: 8-bit value to be stored in the ID register. 	
* Return         : None
*******************************************************************************/
void CRC_SetIDRegister(uint8_t IDValue)
{
  CRC->IDATAR = IDValue;
}

/*******************************************************************************
* Function Name  : CRC_GetIDRegister
* Description    : Returns the 8-bit data stored in the Independent Data(ID) register.
* Input          : None 	
* Return         : 8-bit value of the ID register.
*******************************************************************************/
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDATAR);
}








