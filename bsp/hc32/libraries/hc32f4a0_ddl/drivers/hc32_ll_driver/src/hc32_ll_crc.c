/**
 *******************************************************************************
 * @file  hc32_ll_crc.c
 * @brief This file provides firmware functions to manage the Cyclic Redundancy
 *        Check(CRC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_crc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_CRC CRC
 * @brief Cyclic Redundancy Check Driver Library
 * @{
 */

#if (LL_CRC_ENABLE == DDL_ON)

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
 * @defgroup CRC_Check_Parameters_Validity CRC Check Parameters Validity
 * @{
 */
/*! Parameter validity check for CRC protocol. */
#define IS_CRC_PROTOCOL(x)                                                     \
(   ((x) == CRC_CRC16)                  ||                                     \
    ((x) == CRC_CRC32))

/*! Parameter validity check for CRC data width. */
#define IS_CRC_DATA_WIDTH(x)                                                   \
(   ((x) == CRC_DATA_WIDTH_8BIT)        ||                                     \
    ((x) == CRC_DATA_WIDTH_16BIT)       ||                                     \
    ((x) == CRC_DATA_WIDTH_32BIT))

/**
 * @}
 */

/**
 * @defgroup CRC_Registers_Reset_Value_definition CRC Registers Reset Value
 * @{
 */
#define CRC_CR_RST_VALUE                (0x0001UL)
/**
 * @}
 */

/**
 * @defgroup CRC_DATA_Bit_Width CRC Data Bit Width
 * @{
 */
#define CRC_DATA_WIDTH_8BIT             (1U)
#define CRC_DATA_WIDTH_16BIT            (2U)
#define CRC_DATA_WIDTH_32BIT            (4U)
/**
 * @}
 */

/**
 * @defgroup CRC_Register_Address CRC Register Address
 * @{
 */
#define CRC_DATA_ADDR                   ((uint32_t)(&CM_CRC->DAT0))
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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CRC_Local_Functions CRC Local Functions
 * @{
 */

/**
 * @brief  Calculate the CRC value of a 8-bit data buffer.
 * @param  [in] au8Data                 Pointer to the input data buffer.
 * @param  [in] u32Len                  The length(counted in byte) of the data to be calculated.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       The au8Data value is NULL or u32Len value is 0.
 */
static int32_t CRC_WriteData8(const uint8_t au8Data[], uint32_t u32Len)
{
    uint32_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    const uint32_t u32DataAddr = CRC_DATA_ADDR;

    if ((au8Data != NULL) && (u32Len != 0UL)) {
        for (i = 0UL; i < u32Len; i++) {
            RW_MEM8(u32DataAddr) = au8Data[i];
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Calculate the CRC value of a 16-bit data buffer.
 * @param  [in] au16Data                Pointer to the input data buffer.
 * @param  [in] u32Len                  The length(counted in half-word) of the data to be calculated.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       The au16Data value is NULL or u32Len value is 0.
 */
static int32_t CRC_WriteData16(const uint16_t au16Data[], uint32_t u32Len)
{
    uint32_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    const uint32_t u32DataAddr = CRC_DATA_ADDR;

    if ((au16Data != NULL) && (u32Len != 0UL)) {
        for (i = 0UL; i < u32Len; i++) {
            RW_MEM16(u32DataAddr) = au16Data[i];
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Calculate the CRC value of a 32-bit data buffer.
 * @param  [in] au32Data                Pointer to the input data buffer.
 * @param  [in] u32Len                  The length(counted in word) of the data to be calculated.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       The au32Data value is NULL or u32Len value is 0.
 */
static int32_t CRC_WriteData32(const uint32_t au32Data[], uint32_t u32Len)
{
    uint32_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    const uint32_t u32DataAddr = CRC_DATA_ADDR;

    if ((au32Data != NULL) && (u32Len != 0UL)) {
        for (i = 0UL; i < u32Len; i++) {
            RW_MEM32(u32DataAddr) = au32Data[i];
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Calculate the CRC value and start with the previously calculated CRC as initial value.
 * @param  [in] u8DataWidth             Bit width of the data.
 *         This parameter can be one of the macros group @ref CRC_DATA_Bit_Width
 *           @arg CRC_DATA_WIDTH_8BIT:  8  Bit
 *           @arg CRC_DATA_WIDTH_16BIT: 16 Bit
 *           @arg CRC_DATA_WIDTH_32BIT: 32 Bit
 * @param  [in] pvData                  Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in bytes or half word or word, depending on
 *                                      the bit width) of the data to be calculated.
 * @retval The CRC value.
 * @note   The function fetch data in byte or half word or word depending on the data bit width(the parameter u8DataWidth).
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
static uint32_t CRC_Accumulate(uint8_t u8DataWidth, const void *pvData, uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((pvData != NULL) && (u32Len != 0UL)) {
        DDL_ASSERT(IS_CRC_DATA_WIDTH(u8DataWidth));

        /* Write data */
        if (CRC_DATA_WIDTH_32BIT == u8DataWidth) {
            (void)CRC_WriteData32((const uint32_t *)pvData, u32Len);
        } else if (CRC_DATA_WIDTH_16BIT == u8DataWidth) {
            (void)CRC_WriteData16((const uint16_t *)pvData, u32Len);
        } else {
            (void)CRC_WriteData8((const uint8_t *)pvData, u32Len);
        }

        /* Get checksum */
        if (READ_REG32_BIT(CM_CRC->CR, CRC_CR_CR) == CRC_CRC32) {
            u32CrcValue = READ_REG32(CM_CRC->RESLT);
        } else {
            u32CrcValue = (READ_REG16(CM_CRC->RESLT) & CRC16_INIT_VALUE);
        }
    }

    return u32CrcValue;
}

/**
 * @brief  Calculate the CRC value and start with the specified initial value(u32InitValue).
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] u8DataWidth             Bit width of the data.
 *         This parameter can be one of the following values:
 *           @arg CRC_DATA_WIDTH_8BIT:  8  Bit
 *           @arg CRC_DATA_WIDTH_16BIT: 16 Bit
 *           @arg CRC_DATA_WIDTH_32BIT: 32 Bit
 * @param  [in] pvData                  Pointer to the buffer containing the data to be computed.
 * @param  [in] u32Len                  The length(counted in bytes or half word or word, depending on
 *                                      the bit width) of the data to be computed.
 * @retval The CRC value.
 * @note   The function fetch data in byte or half word or word depending on the data bit width(the parameter u8DataWidth).
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
static uint32_t CRC_Calculate(uint32_t u32InitValue, uint8_t u8DataWidth, const void *pvData, uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((pvData != NULL) && (u32Len != 0UL)) {
        /* Set initial value */
        if (READ_REG32_BIT(CM_CRC->CR, CRC_CR_CR) == CRC_CRC32) {
            WRITE_REG32(CM_CRC->RESLT, u32InitValue);
        } else {
            WRITE_REG16(CM_CRC->RESLT, (u32InitValue & CRC16_INIT_VALUE));
        }

        u32CrcValue = CRC_Accumulate(u8DataWidth, pvData, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Check the CRC calculating result with the expected value.
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] u8DataWidth             Bit width of the data.
 *         This parameter can be one of the following values:
 *           @arg CRC_DATA_WIDTH_8BIT:  8  Bit
 *           @arg CRC_DATA_WIDTH_16BIT: 16 Bit
 *           @arg CRC_DATA_WIDTH_32BIT: 32 Bit
 * @param  [in] pvData                  Pointer to the buffer containing the data to be computed.
 * @param  [in] u32Len                  The length(counted in byte) of the data to be calculated.
 * @param  [in] u32ExpectValue          The expected CRC value to be checked.
 * @retval An @ref en_flag_status_t enumeration type value.
 * @note   The upper 16 bit of CRC result value and the expected value are ignored when using CRC16
 */
static en_flag_status_t CRC_CheckData(uint32_t u32InitValue, uint8_t u8DataWidth,
                                      const void *pvData, uint32_t u32Len, uint32_t u32ExpectValue)
{
    en_flag_status_t enStatus = RESET;

    if ((pvData != NULL) && (u32Len != 0UL)) {
        (void)CRC_Calculate(u32InitValue, u8DataWidth, pvData, u32Len);

        if (READ_REG32_BIT(CM_CRC->CR, CRC_CR_CR) == CRC_CRC32) {
            (void)CRC_WriteData32(&u32ExpectValue, 1UL);
        } else {
            (void)CRC_WriteData16((uint16_t *)((void *)&u32ExpectValue), 1UL);
        }

        enStatus = CRC_GetResultStatus();
    }

    return enStatus;
}
/**
 * @}
 */

/**
 * @defgroup CRC_Global_Functions CRC Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_crc_init_t to default values.
 * @param  [out] pstcCrcInit            Pointer to a @ref stc_crc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcCrcInit value is NULL.
 */
int32_t CRC_StructInit(stc_crc_init_t *pstcCrcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcCrcInit) {
        pstcCrcInit->u32Protocol = CRC_CRC16;
        pstcCrcInit->u32InitValue = CRC16_INIT_VALUE;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize the CRC.
 * @param  [in] pstcCrcInit             Pointer to a @ref stc_crc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcCrcInit value is NULL.
 */
int32_t CRC_Init(const stc_crc_init_t *pstcCrcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcCrcInit) {
        DDL_ASSERT(IS_CRC_PROTOCOL(pstcCrcInit->u32Protocol));
        CRC_DeInit();

        MODIFY_REG32(CM_CRC->CR, CRC_CRC32, pstcCrcInit->u32Protocol);

        /* Set initial value */
        if (CRC_CRC32 == pstcCrcInit->u32Protocol) {
            WRITE_REG32(CM_CRC->RESLT, pstcCrcInit->u32InitValue);
        } else {
            WRITE_REG16(CM_CRC->RESLT, pstcCrcInit->u32InitValue);
        }

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  De-initialize the CRC.
 * @param  None
 * @retval None
 */
void CRC_DeInit(void)
{
    WRITE_REG32(CM_CRC->CR, CRC_CR_RST_VALUE);
}

/**
 * @brief  Get status of the CRC operation result.
 * @param  None
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CRC_GetResultStatus(void)
{
    uint32_t u32Status;

    u32Status = READ_REG32_BIT(CM_CRC->CR, CRC_CR_FLAG);

    return (u32Status > 0UL) ? SET : RESET;
}

/**
 * @brief  Calculate the CRC value and start with the previously calculated CRC as initial value.
 * @param  [in] au8Data                 Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in bytes) of the data to be calculated.
 * @retval The CRC value.
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
uint32_t CRC_AccumulateData8(const uint8_t au8Data[], uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((au8Data != NULL) && (u32Len != 0UL)) {
        u32CrcValue = CRC_Accumulate(CRC_DATA_WIDTH_8BIT, au8Data, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Calculate the CRC value and start with the previously calculated CRC as initial value.
 * @param  [in] au16Data                Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in half-word) of the data to be calculated.
 * @retval The CRC value.
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
uint32_t CRC_AccumulateData16(const uint16_t au16Data[], uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((au16Data != NULL) && (u32Len != 0UL)) {
        u32CrcValue = CRC_Accumulate(CRC_DATA_WIDTH_16BIT, au16Data, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Calculate the CRC value and start with the previously calculated CRC as initial value.
 * @param  [in] au32Data                Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in word) of the data to be calculated.
 * @retval The CRC value.
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
uint32_t CRC_AccumulateData32(const uint32_t au32Data[], uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((au32Data != NULL) && (u32Len != 0UL)) {
        u32CrcValue = CRC_Accumulate(CRC_DATA_WIDTH_32BIT, au32Data, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Calculate the CRC value and start with the specified initial value(u32InitValue).
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] au8Data                 Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in byte) of the data to be calculated.
 * @retval The CRC value.
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
uint32_t CRC_CalculateData8(uint32_t u32InitValue, const uint8_t au8Data[], uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((au8Data != NULL) && (u32Len != 0UL)) {
        u32CrcValue = CRC_Calculate(u32InitValue, CRC_DATA_WIDTH_8BIT, au8Data, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Calculate the CRC value and start with the specified initial value(u32InitValue).
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] au16Data                Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in half-word) of the data to be calculated.
 * @retval The CRC value.
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
uint32_t CRC_CalculateData16(uint32_t u32InitValue, const uint16_t au16Data[], uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((au16Data != NULL) && (u32Len != 0UL)) {
        u32CrcValue = CRC_Calculate(u32InitValue, CRC_DATA_WIDTH_16BIT, au16Data, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Calculate the CRC value and start with the specified initial value(u32InitValue).
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] au32Data                Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in word) of the data to be calculated.
 * @retval The CRC value.
 * @note   The upper 16 bit of CRC result value is ignored when using CRC16
 */
uint32_t CRC_CalculateData32(uint32_t u32InitValue, const uint32_t au32Data[], uint32_t u32Len)
{
    uint32_t u32CrcValue = 0UL;

    if ((au32Data != NULL) && (u32Len != 0UL)) {
        u32CrcValue = CRC_Calculate(u32InitValue, CRC_DATA_WIDTH_32BIT, au32Data, u32Len);
    }

    return u32CrcValue;
}

/**
 * @brief  Check the CRC calculating result with the expected value.
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] au8Data                 Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in byte) of the data to be calculated.
 * @param  [in] u32ExpectValue          The expected CRC value to be checked.
 * @retval An @ref en_flag_status_t enumeration type value.
 * @note   The upper 16 bit of CRC result value and the expected value are ignored when using CRC16
 */
en_flag_status_t CRC_CheckData8(uint32_t u32InitValue, const uint8_t au8Data[],
                                uint32_t u32Len, uint32_t u32ExpectValue)
{
    en_flag_status_t enStatus = RESET;

    if ((au8Data != NULL) && (u32Len != 0UL)) {
        enStatus = CRC_CheckData(u32InitValue, CRC_DATA_WIDTH_8BIT, au8Data, u32Len, u32ExpectValue);
    }

    return enStatus;
}

/**
 * @brief  Check the CRC calculating result with the expected value.
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] au16Data                Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in half-word) of the data to be calculated.
 * @param  [in] u32ExpectValue          The expected CRC value to be checked.
 * @retval An @ref en_flag_status_t enumeration type value.
 * @note   The upper 16 bit of CRC result value and the expected value are ignored when using CRC16
 */
en_flag_status_t CRC_CheckData16(uint32_t u32InitValue, const uint16_t au16Data[],
                                 uint32_t u32Len, uint32_t u32ExpectValue)
{
    en_flag_status_t enStatus = RESET;

    if ((au16Data != NULL) && (u32Len != 0UL)) {
        enStatus = CRC_CheckData(u32InitValue, CRC_DATA_WIDTH_16BIT, au16Data, u32Len, u32ExpectValue);
    }

    return enStatus;
}

/**
 * @brief  Check the CRC calculating result with the expected value.
 * @param  [in] u32InitValue            The CRC initialization value which is the valid bits same as
 *                                      the bits of CRC Protocol.
 * @param  [in] au32Data                Pointer to the buffer containing the data to be calculated.
 * @param  [in] u32Len                  The length(counted in word) of the data to be calculated.
 * @param  [in] u32ExpectValue          The expected CRC value to be checked.
 * @retval An @ref en_flag_status_t enumeration type value.
 * @note   The upper 16 bit of CRC result value and the expected value are ignored when using CRC16
 */
en_flag_status_t CRC_CheckData32(uint32_t u32InitValue, const uint32_t au32Data[],
                                 uint32_t u32Len, uint32_t u32ExpectValue)
{
    en_flag_status_t enStatus = RESET;

    if ((au32Data != NULL) && (u32Len != 0UL)) {
        enStatus = CRC_CheckData(u32InitValue, CRC_DATA_WIDTH_32BIT, au32Data, u32Len, u32ExpectValue);
    }

    return enStatus;
}

/**
 * @}
 */

#endif /* LL_CRC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
