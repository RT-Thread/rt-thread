/**
 *******************************************************************************
 * @file  hc32f4a0_crc.c
 * @brief This file provides firmware functions to manage the Cyclic Redundancy
 *        Check(CRC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb            First version
   2020-07-21       Heqb            Fixed a bug for CRC_Check function
   2020-08-11       Heqb            Modify macro definition name IS_CRC_PROCOTOL
                                    to IS_CRC_PROTOCOL
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_crc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CRC CRC
 * @brief Cyclic Redundancy Check Driver Library
 * @{
 */

#if (DDL_CRC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CRC_Local_Macros CRC Local Macros
 * @{
 */

/**
 * @defgroup CRC_Check_Parameters_Validity CRC check parameters validity
 * @{
 */
#define IS_CRC_PROTOCOL(x)                                                     \
(   ((x) == CRC_CRC16)                      ||                                 \
    ((x) == CRC_CRC32))

#define IS_CRC_BIT_WIDTH(x)                                                    \
(   ((x) == CRC_BW_8)                       ||                                 \
    ((x) == CRC_BW_16)                      ||                                 \
    ((x) == CRC_BW_32))

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @defgroup CRC_Local_Functions CRC Local Functions
 * @{
 */
static void CRC_8BitWrite(const uint8_t au8Data[], uint32_t u32Length);
static void CRC_16BitWrite(const uint16_t au16Data[], uint32_t u32Length);
static void CRC_32BitWrite(const uint32_t au32Data[], uint32_t u32Length);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CRC_Global_Functions CRC Global Functions
 * @{
 */

/**
 * @brief  CRC16 calculation.
 * @param  [in] u32CrcProtocol        CRC protocol control bit.
 *                                    This parameter can be a value of @ref CRC_Protocol_Control_Bit
 * @param  [in] pvData                Pointer to the buffer containing the data to be computed.
 * @param  [in] u32InitVal            Initialize the CRC calculation.
 * @param  [in] u32Length             The length(countted in bytes or half word or word, depending on
 *                                    the bit width) of the data to be computed.
 * @param  [in] u8BitWidth            Bit width of the data.
 *   @arg  CRC_BW_8:                  8  Bit.
 *   @arg  CRC_BW_16:                 16 Bit.
 *   @arg  CRC_BW_32:                 32 Bit.
 * @retval CRC checksum.
 */
uint32_t CRC_Calculate(uint32_t u32CrcProtocol,
                       const void *pvData,
                       uint32_t u32InitVal,
                       uint32_t u32Length,
                       uint8_t u8BitWidth)
{
    uint32_t u32CheckSum = 0UL;

    if ((pvData != NULL) && (u32Length != 0U))
    {
        DDL_ASSERT(IS_CRC_PROTOCOL(u32CrcProtocol));
        DDL_ASSERT(IS_CRC_BIT_WIDTH(u8BitWidth));
        /* Set operation mode (CRC16 or CRC32) */
        WRITE_REG32(M4_CRC->CR, u32CrcProtocol);
        /* Set initial value */
        if (u32CrcProtocol == CRC_CRC32)
        {
            WRITE_REG32(M4_CRC->RESLT, u32InitVal);
        }
        else
        {
            WRITE_REG16(M4_CRC->RESLT, u32InitVal);
        }
        /* Write data */
        if (u8BitWidth == CRC_BW_8)
        {
            CRC_8BitWrite(pvData, u32Length);
        }
        else if (u8BitWidth == CRC_BW_16)
        {
            CRC_16BitWrite(pvData, u32Length);
        }
        else
        {
            CRC_32BitWrite(pvData, u32Length);
        }
        /* Get checksum */
        if (u32CrcProtocol == CRC_CRC32)
        {
            u32CheckSum = READ_REG32(M4_CRC->RESLT);
        }
        else
        {
            u32CheckSum = READ_REG16(M4_CRC->RESLT);
        }
    }
      return u32CheckSum;
}

/**
 * @brief  CRC check.
 * @param  [in] u32CrcProtocol        CRC protocol control bit.
 *                                    This parameter can be a value of @ref CRC_Protocol_Control_Bit
 * @param  [in] u32CheckSum           The checksum of the data pointed by pointer pvData.
 * @param  [in] pvData                Pointer to the buffer containing the data to be checked.
 * @param  [in] u32InitVal            Initialize the CRC calculation.
 * @param  [in] u32Length             The length(countted in bytes or half word or word, depending on
 *                                    the bit width) of the data to be computed.
 * @param  [in] u8BitWidth            Bit width of the data.
 *   @arg  CRC_BW_8:                  8  Bit.
 *   @arg  CRC_BW_16:                 16 Bit.
 *   @arg  CRC_BW_32:                 32 Bit.
 * @retval A en_flag_status_t value.
 *   @arg  Set:                    CRC checks successfully.
 *   @arg  Reset:                  CRC checks unsuccessfully.
 */
en_flag_status_t CRC_Check(uint32_t u32CrcProtocol,
                           uint32_t u32CheckSum,
                           const void *pvData,
                           uint32_t u32InitVal,
                           uint32_t u32Length,
                           uint8_t u8BitWidth)
{
    en_flag_status_t enFlag = Reset;
    uint32_t u32DataAddr = (uint32_t)&M4_CRC->DAT0;
    DDL_ASSERT(IS_CRC_PROTOCOL(u32CrcProtocol));
    DDL_ASSERT(IS_CRC_BIT_WIDTH(u8BitWidth));
    if ((pvData != NULL) && (u32Length != 0UL))
    {
        /* Set operation mode (CRC16 or CRC32) */
        WRITE_REG32(M4_CRC->CR, u32CrcProtocol);
        /* Set initial value */
        if (u32CrcProtocol == CRC_CRC32)
        {
            WRITE_REG32(M4_CRC->RESLT, u32InitVal);
        }
        else
        {
            WRITE_REG16(M4_CRC->RESLT, u32InitVal);
        }
        /* Write data */
        if (u8BitWidth == CRC_BW_8)
        {
            CRC_8BitWrite(pvData, u32Length);
        }
        else if (u8BitWidth == CRC_BW_16)
        {
            CRC_16BitWrite(pvData, u32Length);
        }
        else
        {
            CRC_32BitWrite(pvData, u32Length);
        }
        /* Write checksum */
        if (u32CrcProtocol == CRC_CRC32)
        {
            RW_MEM32(u32DataAddr) = u32CheckSum;
        }
        else
        {

            RW_MEM16(u32DataAddr) = (uint16_t)u32CheckSum;
        }
        /* Get flag */
        if (READ_REG32_BIT(M4_CRC->CR, CRC_CR_FLAG) != 0UL)
        {
            enFlag = Set;
        }
    }
    return enFlag;
}

/**
 * @}
 */

/**
 * @addtogroup CRC_Local_Functions CRC Local Functions
 * @{
 */

/**
 * @brief  Write CRC data register in bytes.
 * @param  [in]  au8Data            The buffer for writing.
 * @param  [in]  u32Length          The length of data the in bytes.
 * @retval None
 */
static void CRC_8BitWrite(const uint8_t au8Data[], uint32_t u32Length)
{
    uint32_t i;
    const uint32_t u32DataAddr = (uint32_t)(&M4_CRC->DAT0);
    for (i = 0UL; i < u32Length; i++)
    {
        RW_MEM8(u32DataAddr) = au8Data[i];

    }
}

/**
 * @brief  Write CRC data register in half words.
 * @param  [in]  au16Data           The buffer for writing.
 * @param  [in]  u32Length          The length of the data in half words.
 * @retval None
 */
static void CRC_16BitWrite(const uint16_t au16Data[], uint32_t u32Length)
{
    uint32_t i;
    const uint32_t u32DataAddr = (uint32_t)(&M4_CRC->DAT0);
    for (i = 0UL; i < u32Length; i++)
    {
        RW_MEM16(u32DataAddr) = au16Data[i];
    }
}

/**
 * @brief  Write CRC data register in words.
 * @param  [in]  au32Data           The buffer for writing.
 * @param  [in]  u32Length          The length of the data in words.
 * @retval None
 */
static void CRC_32BitWrite(const uint32_t au32Data[], uint32_t u32Length)
{
    uint32_t i;
    const uint32_t u32DataAddr = (uint32_t)(&M4_CRC->DAT0);
    for (i = 0UL; i < u32Length; i++)
    {
        RW_MEM32(u32DataAddr) = au32Data[i];
    }
}

/**
 * @}
 */

#endif /* DDL_CRC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
