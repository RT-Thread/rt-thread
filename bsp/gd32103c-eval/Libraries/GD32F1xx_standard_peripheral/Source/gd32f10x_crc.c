/**
  ******************************************************************************
  * @brief   CRC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_crc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup CRC
  * @brief CRC driver modules
  * @{
  */

/** @defgroup CRC_Private_Functions
  * @{
  */

/**
  * @brief  Reset CRC DTR register to the value of 0xFFFFFFFF.
  * @param  None
  * @retval None
  */
void CRC_ResetDTR(void)
{
    CRC->CTLR = CRC_CTLR_RESET;
}

/**
  * @brief  Compute the 32-bit CRC value of a 32-bit data.
  * @param  CRC_data: data to compute its CRC value
  * @retval 32-bit CRC value
  */
uint32_t CRC_CalcSingleData(uint32_t CRC_data)
{
    CRC->DTR = CRC_data;

    return (CRC->DTR);
}

/**
  * @brief  Compute the 32-bit CRC value of a 32-bit data array.
  * @param  pbuffer[]: pointer to the data array
  * @param  buffer_length: length of the data array
  * @retval 32-bit CRC value
  */
uint32_t CRC_CalcDataFlow(uint32_t pbuffer[], uint32_t buffer_length)
{
    uint32_t index = 0;

    for (index = 0; index < buffer_length; index++) {
        CRC->DTR = pbuffer[index];
    }
    return (CRC->DTR);
}

/**
  * @brief  Read current CRC value.
  * @param  None
  * @retval 32-bit CRC value
  */
uint32_t CRC_ReadDTR(void)
{
    return (CRC->DTR);
}

/**
  * @brief  Write an 8-bit data in FDTR.
  * @param  CRC_fdtr: 8-bit data to write
  * @retval None
  */
void CRC_WriteFDTR(uint8_t CRC_fdtr)
{
    CRC->FDTR = CRC_fdtr;
}

/**
  * @brief  Read the 8-bit data stored in FDTR
  * @param  None
  * @retval 8-bit data
  */
uint8_t CRC_ReadFDTR(void)
{
    return (CRC->FDTR);
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
