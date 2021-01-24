/**
 *******************************************************************************
 * @file  hc32f4a0_hash.c
 * @brief This file provides firmware functions to manage the HASH
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb          First version
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
#include "hc32f4a0_hash.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_HASH HASH
 * @brief HASH Driver Library
 * @{
 */

#if (DDL_HASH_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HASH_Local_Macros HASH Local Macros
 * @{
 */
#define HASH_TIMEOUT                  (6000U)

#define HASH_INT_MASK                 (HASH_INT_GROUP | HASH_INT_ALL)

#define HASH_FLAG_MASK                (HASH_FLAG_START | HASH_FLAG_BUSY | \
                                       HASH_FLAG_CYC_END | HASH_FLAG_HMAC_END)

#define HASH_CLR_FLAG_MASK            (HASH_FLAG_CYC_END | HASH_FLAG_HMAC_END)
/**
 * @defgroup HASH_Check_Parameters_Validity HASH Check Parameters Validity
 * @{
 */
#define IS_VALID_MODE(x)                                                       \
(   ((x) == HASH_MODE_SHA_256)                              ||                 \
    ((x) == HASH_MODE_HMAC))

#define IS_VALID_KEY_LEN(x)                                                    \
(   ((x) == HASH_KEY_LEN_LONG)                              ||                 \
    ((x) == HASH_KEY_LEN_SHORT))

#define IS_VALID_INT_CMD(x)               (((x) | HASH_INT_MASK) == HASH_INT_MASK)

#define IS_VALID_FLAG(x)                  (((x) | HASH_FLAG_MASK) == HASH_FLAG_MASK)

#define IS_VALID_MSG_GRP(x)                                                    \
(   ((x) == HASH_MSG_GRP_FIRST)                             ||                 \
    ((x) == HASH_MSG_GRP_END)                               ||                 \
    ((x) == HASH_MSG_GRP_ONLY_ONE))

#define IS_VALID_FLAG_CLR(x)                                                   \
(   ((x) != 0x0UL)                                          &&                 \
    (((x) | HASH_CLR_FLAG_MASK) == HASH_CLR_FLAG_MASK))

#define IS_VALID_COM_TRIG(x)                                                   \
(   ((x) != 0x0UL)                                          &&                 \
    (((x) | HASH_COM_TRIG_MASk) == HASH_COM_TRIG_MASk))

#define IS_VALID_TRG_REG_SEL(x)                                                \
(   ((x) == HASH_TRIG_REG_BLKCOM)                           ||                 \
    ((x) == HASH_TRIG_REG_TRNCOM))

#define IS_VALID_TRG_SRC_SEL(x)                                                \
(   ((x) == HASH_TRG_SRC_DMA1_BTC0)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC1)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC2)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC3)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC4)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC5)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC6)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_BTC7)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC0)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC1)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC2)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC3)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC4)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC5)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC6)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA1_TC7)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC0)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC1)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC2)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC3)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC4)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC5)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC6)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_BTC7)                         ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC0)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC1)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC2)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC3)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC4)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC5)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC6)                          ||                 \
    ((x) == HASH_TRG_SRC_DMA2_TC7))
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
static void HASH_WriteData(uint8_t u8Data[]);
static en_result_t HASH_Fill_Calc_Data(const uint8_t au8Data[], uint32_t u32DataSize);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup HASH_Global_Functions HASH Global Functions
 * @{
 */

/**
 * @brief  HASH calculate.
 * @param  [in] pvSrcData           Pointer to the source data buffer
 * @param  [in] u32SrcDataSize      Length of the input buffer in bytes
 * @param  [out] au8MsgDigest       Buffer of the digest. The size must be 32 bytes
 * @retval Ok: Success
 *         ErrorBufferFull: Filling Error
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t HASH_Calculate(const void *pvSrcData,
                           uint32_t u32SrcDataSize,
                           uint8_t au8MsgDigest[])
{
    en_result_t   enRet = ErrorInvalidParameter;
    if((pvSrcData != NULL)    &&
       (u32SrcDataSize != 0UL)  &&
       (au8MsgDigest != NULL))
    {
        /* Set HMAC Mode */

        (void)HASH_SetMode(HASH_MODE_SHA_256);
        if(HASH_Fill_Calc_Data(pvSrcData, u32SrcDataSize) == Ok)
        {
            /* Get the message digest result */
            HASH_GetResult(au8MsgDigest);
            enRet = Ok;
        }
        else
        {
            enRet = ErrorBufferFull;
        }
    }
    return enRet;
}

/**
 * @brief  HMAC calculate.
 * @param  [in] pvSrcData           Pointer to the source data buffer
 * @param  [in] u32SrcDataSize      Length of the input buffer in bytes
 * @param  [in] au8Key              Buffer of the secret key
 * @param  [in] u32KeyLength        Length of the input secret key in bytes
 * @param  [out] au8MsgDigest       Buffer of the digest data buffer. The size must be 32 bytes
 * @retval Ok: Success
 *         Error: Filling Error
 *         ErrorInvalidParameter: Parameter error
 *         ErrorTimeout: Process timeout
 */
en_result_t HMAC_Calculate(const void *pvSrcData,
                           uint32_t u32SrcDataSize,
                           const uint8_t au8Key[],
                           uint32_t u32KeyLength,
                           uint8_t au8MsgDigest[])
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32TimeCount = 0UL;
    uint8_t  u8FillBuffer[HASH_GROUP_LEN] = {0UL};
    if ((pvSrcData != NULL)    &&
       (u32SrcDataSize != 0UL) &&
       (au8Key != NULL)        &&
       (u32KeyLength != 0UL)   &&
       (au8MsgDigest != NULL))
    {
        enRet = Ok;
        /* Set HMAC Mode */
        (void)HASH_SetMode(HASH_MODE_HMAC);
        if (u32KeyLength > HASH_GROUP_LEN)
        {
            SET_REG32_BIT(M4_HASH->CR, HASH_CR_LKEY);
            /* Write the key to the data register */
            (void)HASH_Fill_Calc_Data(au8Key, u32KeyLength);
        }
        else
        {
            (void)memcpy(u8FillBuffer, &au8Key[0U], u32KeyLength);
            /* Write the key to the data register */
            HASH_WriteData(u8FillBuffer);
            /* Set first group. */
            SET_REG32_BIT(M4_HASH->CR, HASH_CR_FST_GRP);
            /* Set last group. */
            SET_REG32_BIT(M4_HASH->CR, HASH_CR_KMSG_END);
            /* Start hash calculating. */
            SET_REG32_BIT(M4_HASH->CR, HASH_CR_START);
            /* Wait for operation completion */
            while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_BUSY))
            {
                if(u32TimeCount++ > HASH_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
        }
        /* Clear operation completion flag */
        CLEAR_REG32_BIT(M4_HASH->CR, HASH_CR_CYC_END);
        if (enRet == Ok)
        {
            u32TimeCount =0UL;
            /* Write the message to the data register */
            if (HASH_Fill_Calc_Data(pvSrcData, u32SrcDataSize) == Ok)
            {
                while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_HMAC_END) == 0UL)
                {
                    if (u32TimeCount++ > HASH_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                if (enRet == Ok)
                {
                    /* Clear operation completion flag */
                    CLEAR_REG32_BIT(M4_HASH->CR, HASH_CR_CYC_END);
                    CLEAR_REG32_BIT(M4_HASH->CR, HASH_CR_HMAC_END);
                    /* Get the message digest result */
                    HASH_GetResult(au8MsgDigest);
                }
            }
        }
    }
    return enRet;
}

/**
 * @brief  Start HASH.
 * @param  None
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
en_result_t HASH_Start(void)
{
    en_result_t enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    /* Wait for the HASH to stop */
    while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
    {
        if (u32TimeCount++ > HASH_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        /* Start hash calculating. */
        SET_REG32_BIT(M4_HASH->CR, HASH_CR_START);
    }
    return enRet;
}

/**
 * @brief  Enable or Disable HASH interrupt.
 * @param  [in] u32HashInt              Specifies the HASH interrupt to check.
 *  This parameter can be following values:
 *   @arg  HASH_INT_GROUP:              A set of data operations complete interrupt
 *   @arg  HASH_INT_ALL:                All data operations complete interrupt
 * @param  [in] enNewState              The new state of specified interrupt.
 *  This parameter can be: Enable or Disable.
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
en_result_t HASH_IntCmd(uint32_t u32HashInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_INT_CMD(u32HashInt));
    en_result_t enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    /* Wait for the HASH to stop */
    while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
    {
        if(u32TimeCount++ > HASH_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        if (enNewState == Enable)
        {
            SET_REG32_BIT(M4_HASH->CR, u32HashInt);
        }
        else
        {
            CLEAR_REG32_BIT(M4_HASH->CR, u32HashInt);
        }
    }
    return enRet;
}

/**
 * @brief  Set mode for the HASH
 * @param  [in] u32HashMode       HASH mode selection
 *  This parameter can be one of the following values:
 *   @arg  HASH_MODE_SHA_256:     SHA_256 Operating mode
 *   @arg  HASH_MODE_HMAC:        HMAC Operating mode
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
en_result_t HASH_SetMode(uint32_t u32HashMode)
{
    DDL_ASSERT(IS_VALID_MODE(u32HashMode));
    en_result_t enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    /* Wait for the HASH to stop */
    while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
    {
        if (u32TimeCount++ > HASH_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        MODIFY_REG32(M4_HASH->CR, HASH_CR_MODE, u32HashMode);
    }
    return enRet;
}

/**
 * @brief  Get HASH status
 * @param  [in] u32HashFlag           Specifies the flag to query.
 *   @arg  HASH_FLAG_START:            Operation in progress
 *   @arg  HASH_FLAG_BUSY:             Operation in progress
 *   @arg  HASH_FLAG_CYC_END:          key or message operation completed
 *   @arg  HASH_FLAG_HMAC_END:         HMAC operation completed
 * @retval Set: Flag is set
 *         Reset: Flag is reset
 */
en_flag_status_t HASH_GetStatus(uint32_t u32HashFlag)
{
    en_flag_status_t enRet;
    DDL_ASSERT(IS_VALID_FLAG(u32HashFlag));

    enRet = (READ_REG32_BIT(M4_HASH->CR, u32HashFlag) ? Set :Reset);
    return enRet;
}

/**
 * @brief  Set HASH key length
 * @param  [in] u32KeyLen             Key length.
 *  This parameter can be a value of the following:
 *   @arg  HASH_KEY_LEN_LONG:         Key length > 64 Bytes
 *   @arg  HASH_KEY_LEN_SHORT:        Key length <= 64 Bytes
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
en_result_t HASH_SetKeyLength(uint32_t u32KeyLen)
{
    DDL_ASSERT(IS_VALID_KEY_LEN(u32KeyLen));
    en_result_t enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    /* Wait for the HASH to stop */
    while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
    {
        if (u32TimeCount++ > HASH_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        MODIFY_REG32(M4_HASH->CR, HASH_CR_LKEY, u32KeyLen);
    }
    return enRet;
}

/**
 * @brief  Clear HASH status
 * @param  [in] u32ClearFlag          Specifies the flag to clear.
 *  This parameter can be a value of the following:
 *   @arg  HASH_FLAG_CYC_END:         Clear the key or message operation completed flag
 *   @arg  HASH_FLAG_HMAC_END:        Clear the HMAC operation completed flag
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
en_result_t HASH_ClearStatus(uint32_t u32ClearFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    DDL_ASSERT(IS_VALID_FLAG_CLR(u32ClearFlag));

    /* Wait for the HASH to stop */
    while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
    {
        if (u32TimeCount++ > HASH_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        CLEAR_REG32_BIT(M4_HASH->CR, u32ClearFlag);
    }
    return enRet;
}

/**
 * @brief  Set trigger source for HASH
 * @param  [in] enSrc                   Specifies the Event as trigger source.
 *  This parameter can be a value of the following:
 *   @arg  HASH_TRG_SRC_DMA1_BTC0:      Select the DMA1 channel_0 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC1:      Select the DMA1 channel_1 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC2:      Select the DMA1 channel_2 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC3:      Select the DMA1 channel_3 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC4:      Select the DMA1 channel_4 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC5:      Select the DMA1 channel_5 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC6:      Select the DMA1 channel_6 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_BTC7:      Select the DMA1 channel_7 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC0:       Select the DMA1 channel_0 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC1:       Select the DMA1 channel_1 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC2:       Select the DMA1 channel_2 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC3:       Select the DMA1 channel_3 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC4:       Select the DMA1 channel_4 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC5:       Select the DMA1 channel_5 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC6:       Select the DMA1 channel_6 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA1_TC7:       Select the DMA1 channel_7 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC0:      Select the DMA2 channel_0 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC1:      Select the DMA2 channel_1 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC2:      Select the DMA2 channel_2 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC3:      Select the DMA2 channel_3 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC4:      Select the DMA2 channel_4 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC5:      Select the DMA2 channel_5 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC6:      Select the DMA2 channel_6 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_BTC7:      Select the DMA2 channel_7 block transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC0:       Select the DMA2 channel_0 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC1:       Select the DMA2 channel_1 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC2:       Select the DMA2 channel_2 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC3:       Select the DMA2 channel_3 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC4:       Select the DMA2 channel_4 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC5:       Select the DMA2 channel_5 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC6:       Select the DMA2 channel_6 transfer complete as trigger source
 *   @arg  HASH_TRG_SRC_DMA2_TC7:       Select the DMA2 channel_7 transfer complete as trigger source
 * @retval None
 */
void HASH_SetTriggerSrc(en_event_src_t enSrc)
{
    DDL_ASSERT(IS_VALID_TRG_SRC_SEL(enSrc));

    if(((enSrc >= HASH_TRG_SRC_DMA1_TC0) && (enSrc <= HASH_TRG_SRC_DMA1_TC7)) ||  \
       ((enSrc >= HASH_TRG_SRC_DMA2_TC0) && (enSrc <= HASH_TRG_SRC_DMA2_TC7)))
    {
        MODIFY_REG32(M4_AOS->HASH_ITRGSELA, AOS_HASH_ITRGSELA_TRGSEL, enSrc);
    }
    else
    {
        MODIFY_REG32(M4_AOS->HASH_ITRGSELB, AOS_HASH_ITRGSELB_TRGSEL, enSrc);
    }
}

/**
 * @brief  Enable or Disable common trigger source for HASH
 * @param  [in] u8TrigReg           HASH common trigger source select.
 *         This parameter can be a value of @ref HASH_Common_Trigger_Reg_Sel
 *   @arg  HASH_TRIG_REG_BLKCOM:    DMA block transfer complete register.
 *   @arg  HASH_TRID_REG_TRNCOM:    DMA transfer complete register
 * @param  [in] u32ComTrig          Common trigger event enable bit mask.
 *         This parameter can be value of @ref HASH_Common_Trigger_Sel
 *   @arg  HASH_COM_TRIG1:          Common trigger source 1.
 *   @arg  HASH_COM_TRIG2:          Common trigger source 2.
 * @param  [in] enNewState          Disable or Enable the function
 * @retval None
 */
void HASH_ComTriggerCmd(uint8_t u8TrigReg, uint32_t u32ComTrig,
                        en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TRG_REG_SEL(u8TrigReg));
    DDL_ASSERT(IS_VALID_COM_TRIG(u32ComTrig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    __IO uint32_t *HASH_ITRGSELx = (__IO uint32_t *)((uint32_t)&M4_AOS->HASH_ITRGSELA +  4UL * u8TrigReg);

    if (enNewState == Enable)
    {
        SET_REG32_BIT(*HASH_ITRGSELx, u32ComTrig);
    }
    else
    {
        CLEAR_REG32_BIT(*HASH_ITRGSELx, u32ComTrig);
    }
}

/**
 * @brief  Set the group of messages.
 * @param  [in] u32MsgGroup       First group or Last group of messages.
 *  This parameter can be a value of the following:
 *   @arg  HASH_MSG_GRP_FIRST:    The first group of messages or keys
 *   @arg  HASH_MSG_GRP_END:      The last group of messages or keys
 *   @arg  HASH_MSG_GRP_ONLY_ONE: Only one set of message or key
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
en_result_t HASH_MsgGrpConfig(uint32_t u32MsgGroup)
{
    DDL_ASSERT(IS_VALID_MSG_GRP(u32MsgGroup));
    en_result_t enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    /* Wait for the HASH to stop */
    while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
    {
        if (u32TimeCount++ > HASH_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        SET_REG32_BIT(M4_HASH->CR, u32MsgGroup);
    }
    return enRet;
}

/**
 * @brief  Provides the message digest result.
 * @param  [out] au8MsgDigest       Buffer for message digest.
 * @retval None
 */
void HASH_GetResult(uint8_t au8MsgDigest[])
{
    uint8_t  i;
    uint32_t u32Temp1;
    uint32_t u32HashHr = (uint32_t)(&M4_HASH->HR7);
    uint32_t u32DigestHr = (uint32_t)(&au8MsgDigest[0U]);
    for (i = 0U; i < 8U; i++)
    {
        u32Temp1 = __REV(RW_MEM32(u32HashHr));
        *(uint32_t *)(u32DigestHr) = u32Temp1;
        u32HashHr += 4U;
        u32DigestHr += 4U;
    }
}

/**
 * @brief  HASH Filling data
 * @param  [in] au8Data              The source data buffer
 * @param  [in] u32DataSize          Length of the input buffer in bytes
 * @retval Ok: Success
 *         ErrorTimeout: Process timeout
 */
static en_result_t HASH_Fill_Calc_Data(const uint8_t au8Data[], uint32_t u32DataSize)
{
    en_result_t enRet = Ok;
    uint8_t  au8FillBuffer[HASH_GROUP_LEN];
    uint8_t  u8FirstGroup = 0U;
    uint8_t  u8LastGroup = 0U;
    uint8_t  u8FillFlag = 0U;
    uint32_t u32TimeCount = 0UL;
    uint32_t u32GroupCount = 0UL;
    uint32_t u32BitLenHi;
    uint32_t u32BitLenLo;
    uint32_t u32Index;
    u32BitLenHi    = (u32DataSize >> 29UL) & 0x7UL;
    u32BitLenLo    = (u32DataSize << 3UL);
    while(u32DataSize > 0UL)
    {
        /* Wait for the HASH to stop */
        while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_START))
        {
            if(u32TimeCount++ > HASH_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        if (enRet == Ok)
        {
            u32Index = u32GroupCount * HASH_GROUP_LEN;
            if((u32DataSize >= HASH_GROUP_LEN))
            {
                (void)memset(au8FillBuffer, 0, HASH_GROUP_LEN);
                (void)memcpy(au8FillBuffer, &au8Data[u32Index], HASH_GROUP_LEN);
                HASH_WriteData(au8FillBuffer);
                u32GroupCount++;
                u32DataSize -= HASH_GROUP_LEN;
            }
            else
            {
                (void)memset(au8FillBuffer, 0, HASH_GROUP_LEN);
                if(u32DataSize >= LAST_GROUP_MAX_LEN)
                {
                    if(u8FillFlag == 0U)
                    {
                        (void)memcpy(au8FillBuffer, &au8Data[u32Index], u32DataSize);
                        au8FillBuffer[u32DataSize] = 0x80U;
                        u8FillFlag = 1U;
                    }
                    else
                    {
                        u32DataSize = 0UL;
                    }
                }
                else
                {
                    (void)memcpy(au8FillBuffer, &au8Data[u32Index], u32DataSize);
                    au8FillBuffer[u32DataSize] = 0x80U;
                    u32DataSize = 0UL;
                }
                if(0U == u32DataSize)
                {
                    au8FillBuffer[63U] = (uint8_t)(u32BitLenLo);
                    au8FillBuffer[62U] = (uint8_t)(u32BitLenLo >> 8U);
                    au8FillBuffer[61U] = (uint8_t)(u32BitLenLo >> 16U);
                    au8FillBuffer[60U] = (uint8_t)(u32BitLenLo >> 24U);
                    au8FillBuffer[59U] = (uint8_t)(u32BitLenHi);
                    au8FillBuffer[58U] = (uint8_t)(u32BitLenHi >> 8U);
                    au8FillBuffer[57U] = (uint8_t)(u32BitLenHi >> 16U);
                    au8FillBuffer[56U] = (uint8_t)(u32BitLenHi >> 24U);
                    u8LastGroup = 1U;
                }
                HASH_WriteData(au8FillBuffer);
            }
            /* check if first group */
            if (0U == u8FirstGroup)
            {
                u8FirstGroup = 1U;
                /* Set first group. */
                SET_REG32_BIT(M4_HASH->CR, HASH_CR_FST_GRP);
            }
            /* check if last group */
            if (1U == u8LastGroup)
            {
                u8LastGroup = 0U;
                /* Set last group. */
                SET_REG32_BIT(M4_HASH->CR, HASH_CR_KMSG_END);
            }
            /* Start hash calculating. */
            SET_REG32_BIT(M4_HASH->CR, HASH_CR_START);
            /* Wait for operation completion */
            while(READ_REG32_BIT(M4_HASH->CR, HASH_CR_BUSY))
            {
                if(u32TimeCount++ > HASH_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
        }
    }
    return enRet;
}

/**
 * @brief  Writes the input buffer in data register.
 * @param  [in] au8Data       The buffer for source data
 * @retval None
 */
static void HASH_WriteData(uint8_t au8Data[])
{
    uint8_t  i;
    uint32_t u32Temp1;
    uint32_t u32HashDr = (uint32_t)&(M4_HASH->DR15);

    for (i = 0U; i < 16U; i++)
    {
        u32Temp1 = __REV(RW_MEM32(&au8Data[i*4U]));
        RW_MEM32(u32HashDr) = u32Temp1;
        u32HashDr += 4U;
    }
}

/**
 * @}
 */

#endif /* DDL_HASH_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
