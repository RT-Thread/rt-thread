/**
  ******************************************************************************
  * @file               ft32f0xx_crc.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of CRC computation unit peripheral:
  *                 + Configuration of the CRC computation unit
  *                 + CRC computation of one/many 32-bit data
  *               + CRC Independent register (IDR) access
  * @version            V1.0.0
  * @data                   2021-07-01
    ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_crc.h"

/**
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRC_DeInit(void)
{
  /* Set DR register to reset value */
  CRC->DR = 0xFFFFFFFF;

  /* Reset IDR register */
  CRC->IDR = 0x00;

  /* Set INIT register to reset value */
  CRC->INIT = 0xFFFFFFFF;

  /* Reset the CRC calculation unit */
  CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Resets the CRC calculation unit and sets INIT register content in DR register.
  * @param  None
  * @retval None
  */
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR |= CRC_CR_RESET;
}

/**
  * @brief  Selects the polynomial size. This function is only applicable for
  *         FT32F072 devices.
  * @param  CRC_PolSize: Specifies the polynomial size.
  *         This parameter can be:
  *          @arg CRC_PolSize_7: 7-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_8: 8-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_16: 16-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_32: 32-bit polynomial for CRC calculation
  * @retval None
  */
//void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize)
//{
//  uint32_t tmpcr = 0;

//  /* Check the parameter */
//  assert_param(IS_CRC_POL_SIZE(CRC_PolSize));

//  /* Get CR register value */
//  tmpcr = CRC->CR;

//  /* Reset POL_SIZE bits */
//  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_POLSIZE);
//  /* Set the polynomial size */
//  tmpcr |= (uint32_t)CRC_PolSize;

//  /* Write to CR register */
//  CRC->CR = (uint32_t)tmpcr;
//}

/**
  * @brief  Selects the reverse operation to be performed on input data.
  * @param  CRC_ReverseInputData: Specifies the reverse operation on input data.
  *          This parameter can be:
  *            @arg CRC_ReverseInputData_No: No reverse operation is performed
  *            @arg CRC_ReverseInputData_8bits: reverse operation performed on 8 bits
  *            @arg CRC_ReverseInputData_16bits: reverse operation performed on 16 bits
  *            @arg CRC_ReverseInputData_32bits: reverse operation performed on 32 bits
  * @retval None
  */
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_REVERSE_INPUT_DATA(CRC_ReverseInputData));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset REV_IN bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_REV_IN);
  /* Set the reverse operation */
  tmpcr |= (uint32_t)CRC_ReverseInputData;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}

/**
  * @brief  Enables or disable the reverse operation on output data.
  *         The reverse operation on output data is performed on 32-bit.
  * @param  NewState: new state of the reverse operation on output data.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRC_ReverseOutputDataCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable reverse operation on output data */
    CRC->CR |= CRC_CR_REV_OUT;
  }
  else
  {
    /* Disable reverse operation on output data */
    CRC->CR &= (uint32_t)~((uint32_t)CRC_CR_REV_OUT);
  }
}

/**
  * @brief  Initializes the INIT register.
  * @note   After resetting CRC calculation unit, CRC_InitValue is stored in DR register
  * @param  CRC_InitValue: Programmable initial CRC value
  * @retval None
  */
void CRC_SetInitRegister(uint32_t CRC_InitValue)
{
  CRC->INIT = CRC_InitValue;
}

/**
  * @brief  Initializes the polynomail coefficients. This function is only
  *         applicable for FT32F072 devices.
  * @param  CRC_Pol: Polynomial to be used for CRC calculation.
  * @retval None
  */
void CRC_SetPolynomial(uint32_t CRC_Pol)
{
 // CRC->POL = CRC_Pol;
}

/**
  * @}
  */

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRC_Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t CRC_Data)
{
  CRC->DR = CRC_Data;

  return (CRC->DR);
}

/**
  * @brief  Computes the 16-bit CRC of a given 16-bit data.
  * @param  CRC_Data: data half-word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data)
{
  *(uint16_t*)(CRC_BASE) = (uint16_t) CRC_Data;

  return (CRC->DR);
}

/**
  * @brief  Computes the 8-bit CRC of a given 8-bit data.
  * @param  CRC_Data: 8-bit data to compute its CRC
  * @retval 8-bit CRC
  */
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data)
{
  *(uint8_t*)(CRC_BASE) = (uint8_t) CRC_Data;

  return (CRC->DR);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;

  for(index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }
  return (CRC->DR);
}

/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @retval 32-bit CRC
  */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DR);
}

/**
  * @}
  */
/**
  * @brief  Stores an 8-bit data in the Independent Data(ID) register.
  * @param  CRC_IDValue: 8-bit value to be stored in the ID register
  * @retval None
  */
void CRC_SetIDRegister(uint8_t CRC_IDValue)
{
  CRC->IDR = CRC_IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @param  None
  * @retval 8-bit value of the ID register
  */
uint8_t CRC_GetIDRegister(void)
{
  return (uint8_t)(CRC->IDR);
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

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
