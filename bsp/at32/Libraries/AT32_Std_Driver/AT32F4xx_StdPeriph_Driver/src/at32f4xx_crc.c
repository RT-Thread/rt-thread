/**
 **************************************************************************
 * File Name    : at32f4xx_crc.c
 * Description  : at32f4xx CRC source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_crc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC
  * @brief CRC driver modules
  * @{
  */

/** @defgroup CRC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup CRC_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup CRC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup CRC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup CRC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup CRC_Private_Functions
  * @{
  */

/**
  * @brief  Resets the CRC Data register (DR).
  * @param  None
  * @retval None
  */
void CRC_ResetDT(void)
{
  /* Reset CRC generator */
  CRC->CTRL = CRC_CTRL_RST;
}

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalculateCRC(uint32_t Data)
{
  CRC->DT = Data;

  return (CRC->DT);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalculateBlkCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;

  for(index = 0; index < BufferLength; index++)
  {
    CRC->DT = pBuffer[index];
  }

  return (CRC->DT);
}

/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @retval 32-bit CRC
  */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DT);
}

/**
  * @brief  Stores a 8-bit data in the Independent Data(ID) register.
  * @param  IDValue: 8-bit value to be stored in the ID register
  * @retval None
  */
void CRC_SetIDTReg(uint8_t IDValue)
{
  CRC->IDT = IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @param  None
  * @retval 8-bit value of the ID register
  */
uint8_t CRC_GetIDTReg(void)
{
  return (CRC->IDT);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


