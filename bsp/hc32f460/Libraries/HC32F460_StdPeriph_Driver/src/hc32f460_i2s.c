/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_i2s.c
 **
 ** A detailed description is available at
 ** @link I2sGroup Inter-IC Sound Bus description @endlink
 **
 **   - 2018-10-28  CDT  First version for Device Driver Library of I2S.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_i2s.h"
#include "hc32f460_utility.h"

#if (DDL_I2S_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup I2sGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*!< Parameter valid check for I2S register pointer */
#define IS_VALID_I2S_REG(x)                                                    \
(   (M4_I2S1 == (x))                       ||                                  \
    (M4_I2S2 == (x))                       ||                                  \
    (M4_I2S3 == (x))                       ||                                  \
    (M4_I2S4 == (x)))

/*!< Parameter valid check for I2S function */
#define IS_VALID_I2S_FUNCTION(x)                                               \
(   (TxEn == (x))                           ||                                 \
    (TxIntEn == (x))                        ||                                 \
    (RxEn == (x))                           ||                                 \
    (RxIntEn == (x))                        ||                                 \
    (ErrIntEn == (x)))

/*!< Parameter valid check for I2S status bits */
#define IS_VALID_I2S_STATUS(x)                                                 \
(   (TxBufAlarmFlag == (x))                 ||                                 \
    (RxBufAlarmFlag == (x))                 ||                                 \
    (TxBufEmptFlag == (x))                  ||                                 \
    (TxBufFullFlag == (x))                  ||                                 \
    (RxBufEmptFlag == (x))                  ||                                 \
    (RxBufFullFlag == (x)))

/*!< Parameter valid check for I2S error flag */
#define IS_VALID_I2S_ERR_FLAG(x)                                               \
(   (ClrTxErrFlag == (x))                  ||                                  \
    (ClrRxErrFlag == (x)))

/*!< Parameter valid check for I2S mode */
#define IS_VALID_I2S_MODE(x)                                                   \
(   (I2sMaster == (x))                      ||                                 \
    (I2sSlave == (x)))

/*!< Parameter valid check for I2S full duplex mode */
#define IS_VALID_I2S_DUPLEX_MODE(x)                                            \
(   (I2s_HalfDuplex == (x))                 ||                                 \
    (I2s_FullDuplex == (x)))

/*!< Parameter valid check for I2S standard */
#define IS_VALID_I2S_STANDARD(x)                                               \
(   (Std_Philips == (x))                    ||                                 \
    (Std_MSBJust == (x))                    ||                                 \
    (Std_LSBJust == (x))                    ||                                 \
    (Std_PCM == (x)))

/*!< Parameter valid check for I2S data length */
#define IS_VALID_I2S_DATA_LEN(x)                                               \
(   (I2s_DataLen_16Bit == (x))              ||                                 \
    (I2s_DataLen_24Bit == (x))              ||                                 \
    (I2s_DataLen_32Bit == (x)))

/*!< Parameter valid check for I2S channel data length */
#define IS_VALID_I2S_CHANNEL_LEN(x)                                            \
(   (I2s_ChLen_16Bit == (x))                ||                                 \
    (I2s_ChLen_32Bit == (x)))

/*!< Parameter valid check for I2S MCK output config */
#define IS_VALID_I2S_MCKOUT(x)                                                 \
(   (Disable == (x))                        ||                                 \
    (Enable == (x)))

/*!< Parameter valid check for I2S EXCK config */
#define IS_VALID_I2S_EXCK(x)                                                   \
(   (Disable == (x))                        ||                                 \
    (Enable == (x)))

/*!< Parameter valid check for I2S audio frequecy */
#define IS_I2S_AUDIO_FREQ(FREQ)                                                \
(   (((FREQ) >= I2S_AudioFreq_8k) && ((FREQ) <= I2S_AudioFreq_192k))  ||       \
    ((FREQ) == I2S_AudioFreq_Default))

/*! I2S registers reset value */
#define I2S_REG_CTRL_RESET_VALUE                (0x00002200ul)

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
 *******************************************************************************
 ** \brief I2S function command
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \param [in] enFunc              I2S function
 ** \arg Refer @ref en_i2s_func_t
 ** \param [in] enNewState          New status
 ** \arg Refer @ref en_functional_state_t
 **
 ** \retval None
 **
 ******************************************************************************/
void I2S_FuncCmd(M4_I2S_TypeDef* pstcI2sReg, en_i2s_func_t enFunc,
                 en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));
    DDL_ASSERT(IS_VALID_I2S_FUNCTION(enFunc));

    if(Enable == enNewState)
    {
        if(0ul == (pstcI2sReg->CTRL & (1ul << enFunc)))
        {
            pstcI2sReg->CTRL |= (1ul << enFunc);
        }
    }
    else
    {
        if(0ul != (pstcI2sReg->CTRL & (1ul << enFunc)))
        {
            pstcI2sReg->CTRL &= ~(1ul << (uint8_t)enFunc);
        }
    }
}

/**
 *******************************************************************************
 ** \brief Get I2S status bit
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \param [in] enStd               I2S status bit
 ** \arg Refer @ref en_i2s_std_t
 **
 ** \retval Set                     flag is set
 ** \retval Reset                   flag is reset
 **
 ******************************************************************************/
en_flag_status_t I2S_GetStatus(M4_I2S_TypeDef* pstcI2sReg, en_i2s_std_t enStd)
{
    en_flag_status_t enRet = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));
    DDL_ASSERT(IS_VALID_I2S_STATUS(enStd));

    if (0ul != ((uint32_t)(pstcI2sReg->SR & (1ul << (uint8_t)enStd))))
    {
        enRet = Set;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief Clear I2S error flag
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \param [in] enErrFlag           I2S Error flag
 ** \arg Refer @ref en_i2s_err_flag_t
 **
 ** \retval None
 **
 ******************************************************************************/
void I2S_ClrErrFlag(M4_I2S_TypeDef* pstcI2sReg, en_i2s_err_flag_t enErrFlag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));
    DDL_ASSERT(IS_VALID_I2S_ERR_FLAG(enErrFlag));

    pstcI2sReg->ER |= (1ul << (uint8_t)enErrFlag);
}

/**
 *******************************************************************************
 ** \brief Get I2S error flag
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \param [in] enErrFlag           I2S Error flag
 ** \arg Refer @ref en_i2s_err_flag_t
 **
 ** \retval Set                     flag is set
 ** \retval Reset                   flag is reset
 **
 ******************************************************************************/
en_flag_status_t I2S_GetErrFlag(M4_I2S_TypeDef* pstcI2sReg,
                                en_i2s_err_flag_t enErrFlag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));
    DDL_ASSERT(IS_VALID_I2S_ERR_FLAG(enErrFlag));

    return (en_flag_status_t)((uint32_t)(pstcI2sReg->ER | (1ul << (uint8_t)enErrFlag)));
}

/**
 *******************************************************************************
 ** \brief Write data to I2s data send register
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \param [in] u32Data             Data to be send
 **
 ** \retval None
 **
 ******************************************************************************/
void I2S_SendData(M4_I2S_TypeDef* pstcI2sReg, uint32_t u32Data)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));

    pstcI2sReg->TXBUF = u32Data;
}

/**
 *******************************************************************************
 ** \brief Read data from I2s data receive register
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 **
 ** \retval uint32_t The data read out
 **
 ******************************************************************************/
uint32_t I2S_RevData(const M4_I2S_TypeDef* pstcI2sReg)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));

    return pstcI2sReg->RXBUF;
}

/**
 *******************************************************************************
 ** \brief Initialize I2S module
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \arg M4_I2S1                    I2s channel 1
 ** \arg M4_I2S2                    I2s channel 2
 ** \arg M4_I2S3                    I2s channel 3
 ** \arg M4_I2S4                    I2s channel 4
 ** \param [in] pstcI2sCfg          Pointer to I2S configuration structure
 **
 ** \retval Ok                      Initialize successfully done
 **
 ******************************************************************************/
en_result_t I2s_Init(M4_I2S_TypeDef* pstcI2sReg, const stc_i2s_config_t* pstcI2sCfg)
{
    uint32_t i2sclk = 0ul, tmp=0ul;
    uint8_t u8ChanelDataBit,u8ChanMul;
    uint16_t i2sdiv, i2sodd;
    stc_i2s_cfgr_field_t stcCFGR_Tmp = {0};
    stc_i2s_ctrl_field_t stcCTRL_Tmp = {0};
    en_result_t enRes = Ok;
    uint32_t u32AdrTmp = 0ul;

    if((NULL == pstcI2sReg)||(NULL == pstcI2sCfg))
    {
        enRes = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));
        DDL_ASSERT(IS_VALID_I2S_MODE(pstcI2sCfg->enMode));
        DDL_ASSERT(IS_VALID_I2S_DUPLEX_MODE(pstcI2sCfg->enFullDuplexMode));
        DDL_ASSERT(IS_VALID_I2S_STANDARD(pstcI2sCfg->enStandrad));
        DDL_ASSERT(IS_VALID_I2S_DATA_LEN(pstcI2sCfg->enDataBits));
        DDL_ASSERT(IS_VALID_I2S_CHANNEL_LEN(pstcI2sCfg->enChanelLen));
        DDL_ASSERT(IS_VALID_I2S_MCKOUT(pstcI2sCfg->enMcoOutEn));
        DDL_ASSERT(IS_VALID_I2S_EXCK(pstcI2sCfg->enExckEn));
        DDL_ASSERT(IS_I2S_AUDIO_FREQ(pstcI2sCfg->u32AudioFreq));

        /* Set config register to default value*/
        pstcI2sReg->CTRL = I2S_REG_CTRL_RESET_VALUE;
        /* Clear status register*/
        pstcI2sReg->ER_f.TXERR = 1ul;
        pstcI2sReg->ER_f.RXERR = 1ul;

        //*(uint32_t*)&stcCTRL_Tmp = pstcI2sReg->CTRL;
        u32AdrTmp = (uint32_t)&stcCTRL_Tmp;
        *(uint32_t*)u32AdrTmp = pstcI2sReg->CTRL;

        /* ---- config I2s clock source----  */
        if(Enable == pstcI2sCfg->enExckEn)
        {
            /* Set external clock as I2S clock source */
            stcCTRL_Tmp.CLKSEL = 1ul;
            stcCTRL_Tmp.I2SPLLSEL = 0ul;
            /* Set the I2S clock to the external clock  value */
            i2sclk = I2S_EXTERNAL_CLOCK_VAL;
        }
        else
        {
            /* Set internal clock as I2S clock source */
            stcCTRL_Tmp.CLKSEL = 0ul;
            stcCTRL_Tmp.I2SPLLSEL = 1ul;
            /* Get i2s clock internal frequency */
            i2sclk = pstcI2sCfg->u32I2sInterClkFreq;
        }
        /* config audio sampple rate */
        if(I2s_ChLen_16Bit == pstcI2sCfg->enChanelLen)
        {
            u8ChanelDataBit = 16u;
            u8ChanMul = 8u;
        }
        else
        {
            u8ChanelDataBit = 32u;
            u8ChanMul = 4u;
        }

        /*config I2S clock*/
        if(true == pstcI2sCfg->enMcoOutEn)
        {
            /* MCLK output is enabled */
            tmp = i2sclk/(pstcI2sCfg->u32AudioFreq * u8ChanelDataBit * 2ul * u8ChanMul);
        }
        else
        {
            /* MCLK output is disabled */
            tmp = i2sclk/(pstcI2sCfg->u32AudioFreq * u8ChanelDataBit * 2ul);
        }
        i2sodd = (uint16_t)(tmp & 0x0001ul);
        i2sdiv = (uint16_t)((tmp - (uint32_t)i2sodd) / 2ul);

        /* Test if the divider is 1 or 0 or greater than 0xFF */
        if ((i2sdiv < 2u) || (i2sdiv > 0xFFu))
        {
            /* Set the default values */
            i2sdiv = 2u;
            i2sodd = 0u;
        }

        /* Write I2SPR register */
        pstcI2sReg->PR_f.I2SDIV = (uint8_t)i2sdiv;

        /* Config and write I2S_CFGR */
        stcCFGR_Tmp.CHLEN = pstcI2sCfg->enChanelLen;
        stcCFGR_Tmp.DATLEN = pstcI2sCfg->enDataBits;
        stcCFGR_Tmp.I2SSTD = pstcI2sCfg->enStandrad;
        stcCFGR_Tmp.PCMSYNC = PCM_SYNC_FRAME;
        pstcI2sReg->CFGR_f = stcCFGR_Tmp;

        /* Config CTRL register */
        stcCTRL_Tmp.WMS = pstcI2sCfg->enMode;
        stcCTRL_Tmp.DUPLEX = pstcI2sCfg->enFullDuplexMode;
        if(I2sMaster == pstcI2sCfg->enMode)
        {
            stcCTRL_Tmp.CKOE = 1u;
            stcCTRL_Tmp.LRCKOE = 1u;
        }
        stcCTRL_Tmp.SDOE = 1u;
        stcCTRL_Tmp.MCKOE = pstcI2sCfg->enMcoOutEn;
        stcCTRL_Tmp.ODD = (uint8_t)i2sodd;
        stcCTRL_Tmp.RXBIRQWL = RXBUF_IRQ_WL;
        stcCTRL_Tmp.TXBIRQWL = TXBUF_IRQ_WL;
        //pstcI2sReg->CTRL = *(uint32_t*)&stcCTRL_Tmp;
        u32AdrTmp = (uint32_t)&stcCTRL_Tmp;
        pstcI2sReg->CTRL = *(uint32_t*)u32AdrTmp;
    }
    return enRes;
}

/**
 *******************************************************************************
 ** \brief De-Initialize I2S module
 **
 ** \param [in] pstcI2sReg          Pointer to I2S register
 ** \arg M4_I2S1                    I2s channel 1
 ** \arg M4_I2S2                    I2s channel 2
 ** \arg M4_I2S3                    I2s channel 3
 ** \arg M4_I2S4                    I2s channel 4
 **
 ** \retval Ok                      Process successfully done
 **
 ******************************************************************************/
en_result_t I2s_DeInit(M4_I2S_TypeDef* pstcI2sReg)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_I2S_REG(pstcI2sReg));

    /* Set config register to default value*/
    pstcI2sReg->CTRL = I2S_REG_CTRL_RESET_VALUE;
    /* Clear status register*/
    pstcI2sReg->ER_f.TXERR = 1u;
    pstcI2sReg->ER_f.RXERR = 1u;

    return Ok;
}

//@} // I2sGroup

#endif /* DDL_I2S_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
