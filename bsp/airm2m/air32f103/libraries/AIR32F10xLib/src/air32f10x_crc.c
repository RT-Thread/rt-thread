/* Includes ------------------------------------------------------------------*/
#include "air32f10x_crc.h"

/**
  * @brief  Resets the CRC Data register (DR).
  * @param  None
  * @retval None
  */
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t Data)
{
  CRC->DR = Data;

  return (CRC->DR);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t Type,uint32_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0;

    if (Type == CRC_16_IBM || Type == CRC_16_MAXIM || Type == CRC_16_USB || Type == CRC_16_MODBUS || \
        Type == CRC_16_CCITT || Type == CRC_16_CCITT_FALSE || Type == CRC_16_X25 || Type == CRC_16_XMODEM )
    {
        switch (Type)
        {
            case CRC_16_IBM:
                CRC->INI =  CRC_INIT_VALUE_0;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR =  (CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET) & (~XOR_OUT_SEL_SET) & ~POLY_SEL_SET & ~TYPE_SEL_SET;

                break;

            case CRC_16_MAXIM:
                CRC->INI = CRC_INIT_VALUE_0;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = (CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET | XOR_OUT_SEL_SET) & ~POLY_SEL_SET & ~TYPE_SEL_SET;
                break;

            case CRC_16_USB:
                CRC->INI = CRC16_INIT_VALUE_FF;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = (CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET | XOR_OUT_SEL_SET) & ~POLY_SEL_SET & ~TYPE_SEL_SET;
                break;

            case CRC_16_MODBUS:
                CRC->INI = CRC16_INIT_VALUE_FF;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = (CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET) & (~XOR_OUT_SEL_SET) & ~POLY_SEL_SET & ~TYPE_SEL_SET;
                break;

            case CRC_16_CCITT:
                CRC->INI = CRC_INIT_VALUE_0;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = (((CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET) & (~XOR_OUT_SEL_SET)) | POLY_SEL_SET) & ~TYPE_SEL_SET;
                break;

            case CRC_16_CCITT_FALSE:
                CRC->INI = CRC16_INIT_VALUE_FF;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = ((((CRC->CSR & ~REV_OUT_SEL_SET) & ~REV_IN_SEL_SET) & ~XOR_OUT_SEL_SET) | POLY_SEL_SET) & ~TYPE_SEL_SET;
                break;

            case CRC_16_X25:
                CRC->INI = CRC16_INIT_VALUE_FF;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = (CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET | XOR_OUT_SEL_SET | POLY_SEL_SET) & ~TYPE_SEL_SET;
                break;

            case CRC_16_XMODEM:
                CRC->INI = CRC_INIT_VALUE_0;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = ((((CRC->CSR & ~REV_OUT_SEL_SET) & ~REV_IN_SEL_SET) & ~XOR_OUT_SEL_SET) | POLY_SEL_SET) & ~TYPE_SEL_SET;
                break;

            default:
                break;
        }

        for(index = 0; index < BufferLength; index++)
        {
            CRC->DR = pBuffer[index];
        }
        return (CRC->DR & 0xFFFF);
    }
    else if(Type == CRC_32 || Type == CRC_32_MPEG_2)
    {
        switch (Type)
        {
            case CRC_32:
                CRC->INI = CRC32_INIT_VALUE_FF;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = CRC->CSR | REV_OUT_SEL_SET | REV_IN_SEL_SET | XOR_OUT_SEL_SET | TYPE_SEL_SET;
                break;

            case CRC_32_MPEG_2:
                CRC->INI = CRC32_INIT_VALUE_FF;
                CRC->CR = CRC_CR_RESET;
                CRC->CSR = (((CRC->CSR & ~REV_OUT_SEL_SET) & ~REV_IN_SEL_SET) & ~XOR_OUT_SEL_SET) | TYPE_SEL_SET ;
                break;

            default:
                break;
        }
        for(index = 0; index < BufferLength; index++)
        {
            CRC->DR = pBuffer[index];
        }
        return (CRC->DR);
    }
    else
    {
        return 0;
    }
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
  * @brief  Stores a 8-bit data in the Independent Data(ID) register.
  * @param  IDValue: 8-bit value to be stored in the ID register
  * @retval None
  */
void CRC_SetIDRegister(uint8_t IDValue)
{
  CRC->IDR = IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @param  None
  * @retval 8-bit value of the ID register
  */
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDR);
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
