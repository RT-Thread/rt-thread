/**
 *******************************************************************************
 * @file  hc32f4a0_i2s.c
 * @brief This file provides firmware functions to manage the Inter IC Sound Bus
 *        (I2S).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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
#include "hc32f4a0_i2s.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_I2S I2S
 * @brief Inter IC Sound Bus Driver Library
 * @{
 */

#if (DDL_I2S_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup I2S_Local_Macros I2S Local Macros
 * @{
 */

/* I2S CTRL register Mask */
#define I2S_CTRL_CLEAR_MASK             (I2S_CTRL_WMS      | I2S_CTRL_ODD      | I2S_CTRL_MCKOE     | \
                                         I2S_CTRL_TXBIRQWL | I2S_CTRL_RXBIRQWL | I2S_CTRL_I2SPLLSEL | \
                                         I2S_CTRL_SDOE     | I2S_CTRL_LRCKOE   | I2S_CTRL_CKOE      | \
                                         I2S_CTRL_DUPLEX   | I2S_CTRL_CLKSEL)

/**
 * @defgroup I2S_Check_Parameters_Validity I2S Check Parameters Validity
 * @{
 */
#define IS_I2S_UNIT(x)                                                         \
(   ((x) == M4_I2S1)                            ||                             \
    ((x) == M4_I2S2)                            ||                             \
    ((x) == M4_I2S3)                            ||                             \
    ((x) == M4_I2S4))

#define IS_I2S_CLK_SRC(x)                                                      \
(   ((x) == I2S_CLK_SRC_PLL)                    ||                             \
    ((x) == I2S_CLK_SRC_EXT))

#define IS_I2S_MD(x)                                                           \
(   ((x) == I2S_MD_MASTER)                      ||                             \
    ((x) == I2S_MD_SLAVE))

#define IS_I2S_COM_PROTOCOL(x)                                                 \
(   ((x) == I2S_COM_PROTOCOL_PHILLIPS)          ||                             \
    ((x) == I2S_COM_PROTOCOL_MSB)               ||                             \
    ((x) == I2S_COM_PROTOCOL_LSB)               ||                             \
    ((x) == I2S_COM_PROTOCOL_PCM_SHORT)         ||                             \
    ((x) == I2S_COM_PROTOCOL_PCM_LONG))

#define IS_I2S_TRANS_MD(x)                                                     \
(   ((x) == I2S_TRANS_MD_HALF_DUPLEX_RX)        ||                             \
    ((x) == I2S_TRANS_MD_HALF_DUPLEX_TX)        ||                             \
    ((x) == I2S_TRANS_MD_FULL_DUPLEX))

#define IS_I2S_AUDIO_FREQ(x)                                                   \
(   ((x) == I2S_AUDIO_FREQ_DEFAULT)             ||                             \
    (((x) >= I2S_AUDIO_FREQ_8K) && ((x) <= I2S_AUDIO_FREQ_192K)))

#define IS_I2S_CH_LEN(x)                                                       \
(   ((x) == I2S_CH_LEN_16BIT)                   ||                             \
    ((x) == I2S_CH_LEN_32BIT))

#define IS_I2S_DATA_LEN(x)                                                     \
(   ((x) == I2S_DATA_LEN_16BIT)                 ||                             \
    ((x) == I2S_DATA_LEN_24BIT)                 ||                             \
    ((x) == I2S_DATA_LEN_32BIT))

#define IS_I2S_MCK_OUTPUT(x)                                                   \
(   ((x) == I2S_MCK_OUTPUT_DISABLE)             ||                             \
    ((x) == I2S_MCK_OUTPUT_ENABLE))

#define IS_I2S_TRANS_LVL(x)                                                    \
(   ((x) == I2S_TRANS_LVL0)                     ||                             \
    ((x) == I2S_TRANS_LVL1)                     ||                             \
    ((x) == I2S_TRANS_LVL2)                     ||                             \
    ((x) == I2S_TRANS_LVL3)                     ||                             \
    ((x) == I2S_TRANS_LVL4))

#define IS_I2S_RECEIVE_LVL(x)                                                  \
(   ((x) == I2S_RECEIVE_LVL0)                   ||                             \
    ((x) == I2S_RECEIVE_LVL1)                   ||                             \
    ((x) == I2S_RECEIVE_LVL2)                   ||                             \
    ((x) == I2S_RECEIVE_LVL3)                   ||                             \
    ((x) == I2S_RECEIVE_LVL4))

#define IS_I2S_FUNC(x)                                                         \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_FUNC_ALL) == I2S_FUNC_ALL))

#define IS_I2S_RST_TYPE(x)                                                     \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_RST_TYPE_ALL) == I2S_RST_TYPE_ALL))

#define IS_I2S_INT(x)                                                          \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_INT_ALL) == I2S_INT_ALL))

#define IS_I2S_FLAG(x)                                                         \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_FLAG_ALL) == I2S_FLAG_ALL))

#define IS_I2S_CLR_FLAG(x)                                                     \
(   ((x) != 0U)                                 &&                             \
    (((x) | I2S_CLR_FLAG_ALL) == I2S_CLR_FLAG_ALL))

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
static uint32_t I2S_GetClockFreq(const M4_I2S_TypeDef *I2Sx);
static en_result_t I2S_WaitStatus(const M4_I2S_TypeDef *I2Sx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup I2S_Global_Functions I2S Global Functions
 * @{
 */

/**
 * @brief  De-Initialize I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @retval None
 */
void I2S_DeInit(M4_I2S_TypeDef *I2Sx)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));

    /* Reset all registers of I2S */
    WRITE_REG32(I2Sx->CTRL,  0x00004400UL);
    WRITE_REG32(I2Sx->ER,    0x00000003UL);
    WRITE_REG32(I2Sx->CFGR,  0x00000000UL);
    WRITE_REG32(I2Sx->PR,    0x00000002UL);
    SET_REG32_BIT(I2Sx->CTRL, I2S_RST_TYPE_ALL);
    CLEAR_REG32_BIT(I2Sx->CTRL, I2S_RST_TYPE_ALL);
}

/**
 * @brief  Initialize I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] pstcI2sInit             Pointer to a @ref stc_i2s_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 *           - Error: Initialize failed
 */
en_result_t I2S_Init(M4_I2S_TypeDef *I2Sx, const stc_i2s_init_t *pstcI2sInit)
{
    en_result_t enRet  = Ok;
    uint32_t u32I2sClk;
    uint32_t u32Temp;
    uint32_t u32I2sDiv = 2UL;
    uint32_t u32I2sOdd = 0UL;
    uint32_t u32ChLen;

    if (NULL == pstcI2sInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2S_UNIT(I2Sx));
        DDL_ASSERT(IS_I2S_CLK_SRC(pstcI2sInit->u32ClockSrc));
        DDL_ASSERT(IS_I2S_MD(pstcI2sInit->u32Mode));
        DDL_ASSERT(IS_I2S_COM_PROTOCOL(pstcI2sInit->u32ComProtocol));
        DDL_ASSERT(IS_I2S_TRANS_MD(pstcI2sInit->u32TransMode));
        DDL_ASSERT(IS_I2S_AUDIO_FREQ(pstcI2sInit->u32AudioFreq));
        DDL_ASSERT(IS_I2S_CH_LEN(pstcI2sInit->u32ChLen));
        DDL_ASSERT(IS_I2S_DATA_LEN(pstcI2sInit->u32DataLen));
        DDL_ASSERT(IS_I2S_MCK_OUTPUT(pstcI2sInit->u32MCKOutput));
        DDL_ASSERT(IS_I2S_TRANS_LVL(pstcI2sInit->u32TransFIFOLevel));
        DDL_ASSERT(IS_I2S_RECEIVE_LVL(pstcI2sInit->u32ReceiveFIFOLevel));

        if (I2S_AUDIO_FREQ_DEFAULT != pstcI2sInit->u32AudioFreq)
        {
            /* Get I2S source Clock frequency */
            if (I2S_CLK_SRC_EXT == pstcI2sInit->u32ClockSrc)
            {
                /* If an external I2S clock has to be used, this define
                   should be set in the ddl_config.h file */
                u32I2sClk = I2S_EXT_CLK_FREQ;
            }
            else
            {
                u32I2sClk = I2S_GetClockFreq(I2Sx);
            }

            /* The actual frequency division value is calculated according to the output state of MCK */
            if (I2S_CH_LEN_16BIT != pstcI2sInit->u32ChLen)
            {
                u32ChLen = 32UL;
            }
            else
            {
                u32ChLen = 16UL;
            }

            if (I2S_MCK_OUTPUT_ENABLE == pstcI2sInit->u32MCKOutput)
            {
                if (I2S_CH_LEN_16BIT != pstcI2sInit->u32ChLen)
                {
                    u32Temp = (((u32I2sClk / (u32ChLen*2U * 4U)) * 10U) / pstcI2sInit->u32AudioFreq) + 5U;
                }
                else
                {
                    u32Temp = (((u32I2sClk / (u32ChLen*2U * 8U)) * 10U) / pstcI2sInit->u32AudioFreq) + 5U;
                }
            }
            else
            {
                u32Temp = (((u32I2sClk / (u32ChLen*2U)) * 10U) / pstcI2sInit->u32AudioFreq) + 5U;
            }
            u32Temp   = u32Temp / 10U;
            u32I2sOdd = u32Temp & 0x01U;
            u32I2sDiv = (u32Temp - u32I2sOdd) / 2U;
        }

        if ((u32I2sDiv < 2U) || (u32I2sDiv > 0xFFU))
        {
            /* Set the default values */
            u32I2sOdd = 0U;
            u32I2sDiv = 2U;
            enRet     = Error;
        }

        u32Temp = pstcI2sInit->u32ClockSrc         | pstcI2sInit->u32Mode           |
                  pstcI2sInit->u32ComProtocol      | pstcI2sInit->u32TransMode      |
                  pstcI2sInit->u32ChLen            | pstcI2sInit->u32DataLen        |
                  pstcI2sInit->u32MCKOutput        | pstcI2sInit->u32TransFIFOLevel |
                  pstcI2sInit->u32ReceiveFIFOLevel | (u32I2sOdd << I2S_CTRL_ODD_POS);
        if (I2S_MD_MASTER == pstcI2sInit->u32Mode)
        {
            u32Temp |= (I2S_CTRL_CKOE | I2S_CTRL_LRCKOE);
        }
        /* Set I2S_CFGR register */
        WRITE_REG32(I2Sx->CFGR, (pstcI2sInit->u32ComProtocol | pstcI2sInit->u32ChLen | pstcI2sInit->u32DataLen));
        /* set I2S_PR register */
        WRITE_REG32(I2Sx->PR, u32I2sDiv);
        /* Set I2S_CTRL register */
        MODIFY_REG32(I2Sx->CTRL, I2S_CTRL_CLEAR_MASK, u32Temp);
    }

    return enRet;
}

/**
 * @brief  Fills each stc_i2s_init_t member with default value.
 * @param  [out] pstcI2sInit            Pointer to a @ref stc_i2s_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: stc_i2s_init_t member initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t I2S_StructInit(stc_i2s_init_t *pstcI2sInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcI2sInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcI2sInit->u32ClockSrc         = I2S_CLK_SRC_PLL;
        pstcI2sInit->u32Mode             = I2S_MD_MASTER;
        pstcI2sInit->u32ComProtocol      = I2S_COM_PROTOCOL_PHILLIPS;
        pstcI2sInit->u32TransMode        = I2S_TRANS_MD_HALF_DUPLEX_RX;
        pstcI2sInit->u32AudioFreq        = I2S_AUDIO_FREQ_DEFAULT;
        pstcI2sInit->u32ChLen            = I2S_CH_LEN_16BIT;
        pstcI2sInit->u32DataLen          = I2S_DATA_LEN_16BIT;
        pstcI2sInit->u32MCKOutput        = I2S_MCK_OUTPUT_DISABLE;
        pstcI2sInit->u32TransFIFOLevel   = I2S_TRANS_LVL2;
        pstcI2sInit->u32ReceiveFIFOLevel = I2S_RECEIVE_LVL2;
    }

    return enRet;
}

/**
 * @brief  Set the software reset of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32ResetType            Software reset type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_RST_TYPE_SW:      I2S software reset
 *           @arg I2S_RST_TYPE_CODEC:   Reset codec of I2S
 *           @arg I2S_RST_TYPE_FIFO:    Reset FIFO of I2S
 *           @arg I2S_RST_TYPE_ALL:     All of the above
 * @retval None
 */
void I2S_SetSWReset(M4_I2S_TypeDef *I2Sx, uint32_t u32ResetType)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_RST_TYPE(u32ResetType));

    SET_REG32_BIT(I2Sx->CTRL, u32ResetType);
    CLEAR_REG32_BIT(I2Sx->CTRL, u32ResetType);
}

/**
 * @brief  Set the transfer mode for the I2S communication.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Mode                 Transfer mode
 *         This parameter can be one of the following values:
 *           @arg I2S_TRANS_MD_HALF_DUPLEX_RX:  Receive only and half duplex mode
 *           @arg I2S_TRANS_MD_HALF_DUPLEX_TX:  Send only and half duplex mode
 *           @arg I2S_TRANS_MD_FULL_DUPLEX:     Full duplex mode
 * @retval None
 */
void I2S_SetTransMode(M4_I2S_TypeDef *I2Sx, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_TRANS_MD(u32Mode));

    MODIFY_REG32(I2Sx->CTRL, (I2S_CTRL_DUPLEX | I2S_CTRL_SDOE), u32Mode);
}

/**
 * @brief  Set the transfer FIFO level of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Level                Transfer FIFO level
 *         This parameter can be one of the following values:
 *           @arg I2S_TRANS_LVL0:       Transfer FIFO level is 0
 *           @arg I2S_TRANS_LVL1:       Transfer FIFO level is 1
 *           @arg I2S_TRANS_LVL2:       Transfer FIFO level is 2
 *           @arg I2S_TRANS_LVL3:       Transfer FIFO level is 3
 *           @arg I2S_TRANS_LVL4:       Transfer FIFO level is 4
 * @retval None
 */
void I2S_SetTransFIFOLevel(M4_I2S_TypeDef *I2Sx, uint32_t u32Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_TRANS_LVL(u32Level));

    MODIFY_REG32(I2Sx->CTRL, I2S_CTRL_TXBIRQWL, u32Level);
}

/**
 * @brief  Set the receive FIFO level of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Level                Receive FIFO level
 *         This parameter can be one of the following values:
 *           @arg I2S_RECEIVE_LVL0:     Receive FIFO level is 0
 *           @arg I2S_RECEIVE_LVL1:     Receive FIFO level is 1
 *           @arg I2S_RECEIVE_LVL2:     Receive FIFO level is 2
 *           @arg I2S_RECEIVE_LVL3:     Receive FIFO level is 3
 *           @arg I2S_RECEIVE_LVL4:     Receive FIFO level is 4
 * @retval None
 */
void I2S_SetReceiveFIFOLevel(M4_I2S_TypeDef *I2Sx, uint32_t u32Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_RECEIVE_LVL(u32Level));

    MODIFY_REG32(I2Sx->CTRL, I2S_CTRL_RXBIRQWL, u32Level);
}

/**
 * @brief  Set the communication protocol of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Protocol             Communication protocol
 *         This parameter can be one of the following values:
 *           @arg I2S_COM_PROTOCOL_PHILLIPS:    Phillips protocol
 *           @arg I2S_COM_PROTOCOL_MSB:         MSB justified protocol
 *           @arg I2S_COM_PROTOCOL_LSB:         LSB justified protocol
 *           @arg I2S_COM_PROTOCOL_PCM_SHORT:   PCM short-frame protocol
 *           @arg I2S_COM_PROTOCOL_PCM_LONG:    PCM long-frame protocol
 * @retval None
 */
void I2S_SetComProtocol(M4_I2S_TypeDef *I2Sx, uint32_t u32Protocol)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_COM_PROTOCOL(u32Protocol));

    MODIFY_REG32(I2Sx->CFGR, (I2S_CFGR_I2SSTD | I2S_CFGR_PCMSYNC), u32Protocol);
}

/**
 * @brief  Set the audio frequency for the I2S communication.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Freq                 Audio frequency
 *         This parameter can be 'I2S_AUDIO_FREQ_DEFAULT' or between
 *         'I2S_AUDIO_FREQ_8K' and 'I2S_AUDIO_FREQ_192K':
 *           @arg I2S_AUDIO_FREQ_192K:          FS = 192000Hz
 *           @arg I2S_AUDIO_FREQ_8K:            FS = 8000Hz
 *           @arg I2S_AUDIO_FREQ_DEFAULT
 * @retval An en_result_t enumeration value:
 *           - Ok: Set success
 *           - Error: Set failed
 */
en_result_t I2S_SetAudioFreq(M4_I2S_TypeDef *I2Sx, uint32_t u32Freq)
{
    en_result_t enRet  = Ok;
    uint32_t u32I2sClk;
    uint32_t u32Temp;
    uint32_t u32I2sDiv = 2UL;
    uint32_t u32I2sOdd = 0UL;
    uint32_t u32ChLen;

    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_AUDIO_FREQ(u32Freq));

    if (I2S_AUDIO_FREQ_DEFAULT != u32Freq)
    {
        /* Get I2S source Clock frequency */
        if (I2S_CLK_SRC_EXT == READ_REG32_BIT(I2Sx->CTRL, I2S_CTRL_CLKSEL))
        {
            /* If an external I2S clock has to be used, this define
                should be set in the ddl_config.h file */
            u32I2sClk = I2S_EXT_CLK_FREQ;
        }
        else
        {
            u32I2sClk = I2S_GetClockFreq(I2Sx);
        }

        /* The actual frequency division value is calculated according to the output state of MCK */
        if (I2S_CH_LEN_16BIT != READ_REG32_BIT(I2Sx->CFGR, I2S_CFGR_CHLEN))
        {
            u32ChLen = 32UL;
        }
        else
        {
            u32ChLen = 16UL;
        }

        if (I2S_MCK_OUTPUT_ENABLE == READ_REG32_BIT(I2Sx->CTRL, I2S_CTRL_MCKOE))
        {
            if (I2S_CH_LEN_16BIT != READ_REG32_BIT(I2Sx->CFGR, I2S_CFGR_CHLEN))
            {
                u32Temp = (((u32I2sClk / (u32ChLen*2U * 4U)) * 10U) / u32Freq) + 5U;
            }
            else
            {
                u32Temp = (((u32I2sClk / (u32ChLen*2U * 8U)) * 10U) / u32Freq) + 5U;
            }
        }
        else
        {
            u32Temp = (((u32I2sClk / (u32ChLen*2U)) * 10U) / u32Freq) + 5U;
        }
        u32Temp   = u32Temp / 10U;
        u32I2sOdd = u32Temp & 0x01U;
        u32I2sDiv = (u32Temp - u32I2sOdd) / 2U;
    }

    if ((u32I2sDiv < 2U) || (u32I2sDiv > 0xFFU))
    {
        enRet = Error;
    }
    else
    {
        /* Set clock division */
        WRITE_REG32(I2Sx->PR, u32I2sDiv);
        MODIFY_REG32(I2Sx->CTRL, I2S_CTRL_ODD, (u32I2sOdd << I2S_CTRL_ODD_POS));
    }

    return enRet;
}

/**
 * @brief  Enable or disable MCK clock output.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void I2S_MCKOutputCmd(M4_I2S_TypeDef *I2Sx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(I2Sx->CTRL, I2S_CTRL_MCKOE);
    }
    else
    {
        CLEAR_REG32_BIT(I2Sx->CTRL, I2S_CTRL_MCKOE);
    }
}

/**
 * @brief  Enable or disable the function of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Func                 I2S function
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_FUNC_TXE:         Transfer function
 *           @arg I2S_FUNC_RXE:         Receive function
 *           @arg I2S_FUNC_ALL:         All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void I2S_FuncCmd(M4_I2S_TypeDef* I2Sx, uint32_t u32Func, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_FUNC(u32Func));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(I2Sx->CTRL, u32Func);
    }
    else
    {
        CLEAR_REG32_BIT(I2Sx->CTRL, u32Func);
    }
}

/**
 * @brief  I2S send data.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Data                 Send data
 * @retval None
 */
void I2S_WriteData(M4_I2S_TypeDef *I2Sx, uint32_t u32Data)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));

    WRITE_REG32(I2Sx->TXBUF, u32Data);
}

/**
 * @brief  I2S receive data.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @retval uint32_t                     Receive data
 */
uint32_t I2S_ReadData(const M4_I2S_TypeDef *I2Sx)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));

    return READ_REG32(I2Sx->RXBUF);
}

/**
 * @brief  I2S transmit data in polling mode.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] pvTxBuf                 The pointer to data transmitted buffer
 * @param  [in] u32Len                  Data length
 * @param  [in] u32Timeout              Transfer timeout(ms)
 * @retval An en_result_t enumeration value:
 *           - Ok: Transmit data success
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: Transmission timeout
 */
en_result_t I2S_Trans(M4_I2S_TypeDef *I2Sx, const void *pvTxBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    en_result_t enRet = Ok;
    uint32_t i;
    uint32_t u32DataWidth;

    if ((NULL == pvTxBuf) || (0UL == u32Len))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2S_UNIT(I2Sx));

        u32DataWidth = READ_REG32_BIT(I2Sx->CFGR, I2S_CFGR_DATLEN);
        if (((I2S_DATA_LEN_16BIT == u32DataWidth) && IS_ADDRESS_ALIGN_HALFWORD(pvTxBuf)) ||
            (IS_ADDRESS_ALIGN_WORD(pvTxBuf)))
        {
            for (i = 0UL; i < u32Len; i++)
            {
                enRet = I2S_WaitStatus(I2Sx, I2S_FLAG_TX_FULL, Reset, u32Timeout);
                if (Ok != enRet)
                {
                    break;
                }

                if (I2S_DATA_LEN_16BIT == u32DataWidth)
                {
                    WRITE_REG32(I2Sx->TXBUF, ((const uint16_t *)pvTxBuf)[i]);
                }
                else
                {
                    WRITE_REG32(I2Sx->TXBUF, ((const uint32_t *)pvTxBuf)[i]);
                }
            }
        }
        else
        {
            enRet = ErrorInvalidParameter;
        }
    }

    return enRet;
}

/**
 * @brief  I2S receive data in polling mode.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] pvRxBuf                 The pointer to data received buffer
 * @param  [in] u32Len                  Data length
 * @param  [in] u32Timeout              Transfer timeout(ms)
 * @retval An en_result_t enumeration value:
 *           - Ok: Receive data success
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: Transmission timeout
 */
en_result_t I2S_Receive(const M4_I2S_TypeDef *I2Sx, void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    en_result_t enRet = Ok;
    uint32_t i;
    uint32_t u32DataWidth;
    uint32_t u32Temp;

    if ((NULL == pvRxBuf) || (0UL == u32Len))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2S_UNIT(I2Sx));

        u32DataWidth = READ_REG32_BIT(I2Sx->CFGR, I2S_CFGR_DATLEN);
        if (((I2S_DATA_LEN_16BIT == u32DataWidth) && IS_ADDRESS_ALIGN_HALFWORD(pvRxBuf)) ||
            (IS_ADDRESS_ALIGN_WORD(pvRxBuf)))
        {
            for (i = 0UL; i < u32Len; i++)
            {
                enRet = I2S_WaitStatus(I2Sx, I2S_FLAG_RX_EMPTY, Reset, u32Timeout);
                if (Ok != enRet)
                {
                    break;
                }

                u32Temp = READ_REG32(I2Sx->RXBUF);
                if (I2S_DATA_LEN_16BIT == u32DataWidth)
                {
                    ((uint16_t *)pvRxBuf)[i] = (uint16_t)(u32Temp & 0xFFFFUL);
                }
                else if (I2S_DATA_LEN_24BIT == u32DataWidth)
                {
                    ((uint32_t *)pvRxBuf)[i] = u32Temp & 0xFFFFFFUL;
                }
                else
                {
                    ((uint32_t *)pvRxBuf)[i] = u32Temp;
                }
            }
        }
        else
        {
            enRet = ErrorInvalidParameter;
        }
    }

    return enRet;
}

/**
 * @brief  I2S transmit and receive data in polling mode.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] pvTxBuf                 The pointer to data transmitted buffer
 * @param  [in] pvRxBuf                 The pointer to data received buffer
 * @param  [in] u32Len                  Data length
 * @param  [in] u32Timeout              Transfer timeout(ms)
 * @retval An en_result_t enumeration value:
 *           - Ok: Receive data success
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: Transmission timeout
 */
en_result_t I2S_TransReceive(M4_I2S_TypeDef *I2Sx, const void *pvTxBuf, void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    en_result_t enRet;
    uint32_t u32TxCnt = 0U;
    uint32_t u32RxCnt = 0U;
    uint32_t u32DataWidth;
    uint32_t u32Temp;
    uint8_t u8BreakFlag = 0U;

    if ((NULL == pvTxBuf) || (NULL == pvRxBuf) || (0UL == u32Len))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_I2S_UNIT(I2Sx));

        u32DataWidth = READ_REG32_BIT(I2Sx->CFGR, I2S_CFGR_DATLEN);
        if (((I2S_DATA_LEN_16BIT == u32DataWidth) && IS_ADDRESS_ALIGN_HALFWORD(pvTxBuf) && IS_ADDRESS_ALIGN_HALFWORD(pvRxBuf)) ||
            (IS_ADDRESS_ALIGN_WORD(pvTxBuf) && IS_ADDRESS_ALIGN_WORD(pvRxBuf)))
        {
            enRet = I2S_WaitStatus(I2Sx, I2S_FLAG_TX_FULL, Reset, u32Timeout);
            if (Ok == enRet)
            {
                /* Preload data */
                if (I2S_DATA_LEN_16BIT == u32DataWidth)
                {
                    WRITE_REG32(I2Sx->TXBUF, ((const uint16_t *)pvTxBuf)[u32TxCnt]);
                }
                else
                {
                    WRITE_REG32(I2Sx->TXBUF, ((const uint32_t *)pvTxBuf)[u32TxCnt]);
                }
                u32TxCnt++;

                for (;;)
                {
                    /* Transmit data */
                    if (u32TxCnt < u32Len)
                    {
                        enRet = I2S_WaitStatus(I2Sx, I2S_FLAG_TX_FULL, Reset, u32Timeout);
                        if (Ok != enRet)
                        {
                            u8BreakFlag = 1U;
                        }
                        else
                        {
                            if (I2S_DATA_LEN_16BIT == u32DataWidth)
                            {
                                WRITE_REG32(I2Sx->TXBUF, ((const uint16_t *)pvTxBuf)[u32TxCnt]);
                            }
                            else
                            {
                                WRITE_REG32(I2Sx->TXBUF, ((const uint32_t *)pvTxBuf)[u32TxCnt]);
                            }
                            u32TxCnt++;
                        }
                    }
                    /* Receive data */
                    if ((1U != u8BreakFlag) && (u32RxCnt < u32Len))
                    {
                        enRet = I2S_WaitStatus(I2Sx, I2S_FLAG_RX_EMPTY, Reset, u32Timeout);
                        if (Ok != enRet)
                        {
                            u8BreakFlag = 1U;
                        }
                        else
                        {
                            u32Temp = READ_REG32(I2Sx->RXBUF);
                            if (I2S_DATA_LEN_16BIT == u32DataWidth)
                            {
                                ((uint16_t *)pvRxBuf)[u32RxCnt] = (uint16_t)(u32Temp & 0xFFFFUL);
                            }
                            else if (I2S_DATA_LEN_24BIT == u32DataWidth)
                            {
                                ((uint32_t *)pvRxBuf)[u32RxCnt] = u32Temp & 0xFFFFFFUL;
                            }
                            else
                            {
                                ((uint32_t *)pvRxBuf)[u32RxCnt] = u32Temp;
                            }
                            u32RxCnt++;
                        }
                    }

                    /* Complete the transmission */
                    if ((1U == u8BreakFlag) || ((u32Len == u32TxCnt) && (u32Len == u32RxCnt)))
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            enRet = ErrorInvalidParameter;
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable specified I2S interrupt.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32IntType              Interrupt type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_INT_TX:           Transfer interrupt
 *           @arg I2S_INT_RX:           Receive interrupt
 *           @arg I2S_INT_ERR:          Communication error interrupt
 *           @arg I2S_INT_ALL:          All of the above
 * @param  [in] enNewState              The function new state
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void I2S_IntCmd(M4_I2S_TypeDef *I2Sx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(I2Sx->CTRL, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(I2Sx->CTRL, u32IntType);
    }
}

/**
 * @brief  Get I2S flag status.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Flag                 I2S flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_FLAG_TX_ALARM:    Transfer buffer alarm flag
 *           @arg I2S_FLAG_RX_ALARM:    Receive buffer alarm flag
 *           @arg I2S_FLAG_TX_EMPTY:    Transfer buffer empty flag
 *           @arg I2S_FLAG_TX_FULL:     Transfer buffer full flag
 *           @arg I2S_FLAG_RX_EMPTY:    Receive buffer empty flag
 *           @arg I2S_FLAG_RX_FULL:     Receive buffer full flag
 *           @arg I2S_FLAG_TX_ERR:      Transfer overflow or underflow flag
 *           @arg I2S_FLAG_RX_ERR:      Receive overflow flag
 *           @arg I2S_FLAG_ALL:         All of the above
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t I2S_GetStatus(const M4_I2S_TypeDef *I2Sx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;
    uint32_t u32NormalFlag;
    uint32_t u32ErrorFlag;

    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_FLAG(u32Flag));

    u32NormalFlag = u32Flag & 0xFFFFUL;
    u32ErrorFlag  = u32Flag >> 16U;
    if (0UL != u32NormalFlag)
    {
        if (0UL != (READ_REG32_BIT(I2Sx->SR, u32NormalFlag)))
        {
            enFlagSta = Set;
        }
    }
    if ((Reset == enFlagSta) && (0UL != u32ErrorFlag))
    {
        if (0UL != (READ_REG32_BIT(I2Sx->ER, u32ErrorFlag)))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear I2S flag.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Flag                 I2S flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg I2S_FLAG_TX_ERR:      Transfer overflow or underflow flag
 *           @arg I2S_FLAG_RX_ERR:      Receive overflow flag
 *           @arg I2S_CLR_FLAG_ALL:     All of the above
 * @retval None
 */
void I2S_ClearStatus(M4_I2S_TypeDef *I2Sx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_I2S_UNIT(I2Sx));
    DDL_ASSERT(IS_I2S_CLR_FLAG(u32Flag));

    CLEAR_REG32_BIT(I2Sx->ER, u32Flag);
}

/**
 * @brief  Get I2S clock frequency.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @retval uint32_t                     The I2S clock frequency
 */
static uint32_t I2S_GetClockFreq(const M4_I2S_TypeDef *I2Sx)
{
    uint32_t u32ClockShift;
    uint16_t u32ClockSrc;
    uint32_t u32ClockFreq;
    uint32_t u32PllP;
    uint32_t u32PllQ;
    uint32_t u32PllR;
    uint32_t u32PllN;
    uint32_t u32PllM;
    uint32_t u32PllIn;
    uint32_t u32Temp;

    /* Get the offset of the I2S clock source in CMU_I2SCKSEL */
    if (M4_I2S1 == I2Sx)
    {
        u32ClockShift = CMU_I2SCKSEL_I2S1CKSEL_POS;
    }
    else if (M4_I2S2 == I2Sx)
    {
        u32ClockShift = CMU_I2SCKSEL_I2S2CKSEL_POS;
    }
    else if (M4_I2S3 == I2Sx)
    {
        u32ClockShift = CMU_I2SCKSEL_I2S3CKSEL_POS;
    }
    else if (M4_I2S4 == I2Sx)
    {
        u32ClockShift = CMU_I2SCKSEL_I2S4CKSEL_POS;
    }
    else
    {
        u32ClockShift = 0UL;
    }

    u32ClockSrc = (READ_REG16(M4_CMU->I2SCKSEL) >> u32ClockShift) & CMU_I2SCKSEL_I2S1CKSEL;
    if (0UL != READ_REG32_BIT(M4_CMU->PLLHCFGR, CMU_PLLHCFGR_PLLSRC))
    {
        u32PllIn = HRC_VALUE;
    }
    else
    {
        u32PllIn = XTAL_VALUE;
    }
    /* Calculate the clock frequency */
    switch(u32ClockSrc)
    {
        case 0x00U:  /* PCLK1 */
            u32ClockFreq = SystemCoreClock >> ((READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
            break;
        case 0x08U:  /* PLLHQ */
            u32Temp = READ_REG32(M4_CMU->PLLHCFGR);
            u32PllM = (u32Temp >> CMU_PLLHCFGR_PLLHM_POS) & 0x03UL;
            u32PllN = (u32Temp >> CMU_PLLHCFGR_PLLHN_POS) & 0xFFUL;
            u32PllQ = (u32Temp >> CMU_PLLHCFGR_PLLHQ_POS) & 0x0FUL;
            u32ClockFreq = ((u32PllIn / (u32PllM + 1UL)) * (u32PllN + 1UL)) / (u32PllQ + 1UL);
            break;
        case 0x09U:  /* PLLHR */
            u32Temp = READ_REG32(M4_CMU->PLLHCFGR);
            u32PllM = (u32Temp >> CMU_PLLHCFGR_PLLHM_POS) & 0x03UL;
            u32PllN = (u32Temp >> CMU_PLLHCFGR_PLLHN_POS) & 0xFFUL;
            u32PllR = (u32Temp >> CMU_PLLHCFGR_PLLHR_POS) & 0x0FUL;
            u32ClockFreq = ((u32PllIn / (u32PllM + 1UL)) * (u32PllN + 1UL)) / (u32PllR + 1UL);
            break;
        case 0x0AU:  /* PLLAP */
            u32Temp = READ_REG32(M4_CMU->PLLACFGR);
            u32PllM = (u32Temp >> CMU_PLLACFGR_PLLAM_POS) & 0x1FUL;
            u32PllN = (u32Temp >> CMU_PLLACFGR_PLLAN_POS) & 0x1FFUL;
            u32PllP = (u32Temp >> CMU_PLLACFGR_PLLAP_POS) & 0x0FUL;
            u32ClockFreq = ((u32PllIn / (u32PllM + 1UL)) * (u32PllN + 1UL)) / (u32PllP + 1UL);
            break;
        case 0x0BU:  /* PLLAQ */
            u32Temp = READ_REG32(M4_CMU->PLLACFGR);
            u32PllM = (u32Temp >> CMU_PLLACFGR_PLLAM_POS) & 0x1FUL;
            u32PllN = (u32Temp >> CMU_PLLACFGR_PLLAN_POS) & 0x1FFUL;
            u32PllQ = (u32Temp >> CMU_PLLACFGR_PLLAQ_POS) & 0x0FUL;
            u32ClockFreq = ((u32PllIn / (u32PllM + 1UL)) * (u32PllN + 1UL)) / (u32PllQ + 1UL);
            break;
        case 0x0CU:  /* PLLAR */
            u32Temp = READ_REG32(M4_CMU->PLLACFGR);
            u32PllM = (u32Temp >> CMU_PLLACFGR_PLLAM_POS) & 0x1FUL;
            u32PllN = (u32Temp >> CMU_PLLACFGR_PLLAN_POS) & 0x1FFUL;
            u32PllR = (u32Temp >> CMU_PLLACFGR_PLLAR_POS) & 0x0FUL;
            u32ClockFreq = ((u32PllIn / (u32PllM + 1UL)) * (u32PllN + 1UL)) / (u32PllR + 1UL);
            break;
        default:
            u32ClockFreq = 0UL;
            break;
    }

    return u32ClockFreq;
}

/**
 * @brief  Wait for the flag status of I2S.
 * @param  [in] I2Sx                    Pointer to I2S instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_I2S1:              I2S unit 1 instance register base
 *           @arg M4_I2S2:              I2S unit 2 instance register base
 *           @arg M4_I2S3:              I2S unit 3 instance register base
 *           @arg M4_I2S4:              I2S unit 4 instance register base
 * @param  [in] u32Flag                 I2S flag type
 *         This parameter can be one of the following values:
 *           @arg I2S_FLAG_TX_ALARM:    Transfer buffer alarm flag
 *           @arg I2S_FLAG_RX_ALARM:    Receive buffer alarm flag
 *           @arg I2S_FLAG_TX_EMPTY:    Transfer buffer empty flag
 *           @arg I2S_FLAG_TX_FULL:     Transfer buffer full flag
 *           @arg I2S_FLAG_RX_EMPTY:    Receive buffer empty flag
 *           @arg I2S_FLAG_RX_FULL:     Receive buffer full flag
 *           @arg I2S_FLAG_TX_ERR:      Transfer overflow or underflow flag
 *           @arg I2S_FLAG_RX_ERR:      Receive overflow flag
 * @param  [in] enStatus                The flag status
 *         This parameter can be one of the following values:
 *         @arg Set:                    Wait for the flag to set
 *         @arg Reset:                  Wait for the flag to reset
 * @param  [in] u32Timeout              Wait the flag timeout(ms)
 * @retval An en_result_t enumeration value:
 *           - Ok: Wait status success
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t I2S_WaitStatus(const M4_I2S_TypeDef *I2Sx, uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout)
{
    en_result_t enRet  = Ok;
    __IO uint32_t u32Count;

    /* Waiting for the flag status to change to the enStatus */
    u32Count = u32Timeout * (HCLK_VALUE / 20000UL);
    while (enStatus != I2S_GetStatus(I2Sx, u32Flag))
    {
        if (u32Count == 0UL)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_I2S_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
