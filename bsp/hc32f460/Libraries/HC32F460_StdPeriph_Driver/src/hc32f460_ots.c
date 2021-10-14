/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_ots.c
 **
 ** A detailed description is available at
 ** @link OtsGroup Ots description @endlink
 **
 **   - 2018-10-26  CDT First version for Device Driver Library of Ots.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_ots.h"
#include "hc32f460_utility.h"

#if (DDL_OTS_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup OtsGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! Parameter validity check for OTS auto off configuration value. */
#define IS_OTS_AUTO_OFF(EN)                                                     \
(   ((EN) == OtsAutoOff_Disable)                ||                              \
    ((EN) == OtsAutoOff_Enable))

/*! Parameter validity check for OTS interrupt enable/disable. */
#define IS_OTS_IE(IE)                                                           \
(   ((IE) == OtsInt_Disable)                    ||                              \
    ((IE) == OtsInt_Enable))

/*! Parameter validity check for OTS clock selection configuration value. */
#define IS_OTS_CLK_SEL(CLK)                                                     \
(   ((CLK) == OtsClkSel_Xtal)                   ||                              \
    ((CLK) == OtsClkSel_Hrc))

/*! Parameter validity check for OTS trigger source event . */
#define IS_OTS_TRIG_SRC_EVENT(x)                                               \
(   (((x) >= EVT_PORT_EIRQ0) && ((x) <= EVT_PORT_EIRQ15))           ||         \
    (((x) >= EVT_DMA1_TC0) && ((x) <= EVT_DMA2_BTC3))               ||         \
    (((x) >= EVT_EFM_OPTEND) && ((x) <= EVT_USBFS_SOF))             ||         \
    (((x) >= EVT_DCU1) && ((x) <= EVT_DCU4))                        ||         \
    (((x) >= EVT_TMR01_GCMA) && ((x) <= EVT_TMR02_GCMB))            ||         \
    (((x) >= EVT_RTC_ALM) && ((x) <= EVT_RTC_PRD))                  ||         \
    (((x) >= EVT_TMR61_GCMA) && ((x) <= EVT_TMR61_GUDF))            ||         \
    (((x) >= EVT_TMR61_SCMA) && ((x) <= EVT_TMR61_SCMB))            ||         \
    (((x) >= EVT_TMR62_GCMA) && ((x) <= EVT_TMR62_GUDF))            ||         \
    (((x) >= EVT_TMR62_SCMA) && ((x) <= EVT_TMR62_SCMB))            ||         \
    (((x) >= EVT_TMR63_GCMA) && ((x) <= EVT_TMR63_GUDF))            ||         \
    (((x) >= EVT_TMR63_SCMA) && ((x) <= EVT_TMR63_SCMB))            ||         \
    (((x) >= EVT_TMRA1_OVF) && ((x) <= EVT_TMRA5_CMP))              ||         \
    (((x) >= EVT_TMRA6_OVF) && ((x) <= EVT_TMRA6_CMP))              ||         \
    (((x) >= EVT_USART1_EI) && ((x) <= EVT_USART4_RTO))             ||         \
    (((x) >= EVT_SPI1_SPRI) && ((x) <= EVT_AOS_STRG))               ||         \
    (((x) >= EVT_TMR41_SCMUH) && ((x) <= EVT_TMR42_SCMWL))          ||         \
    (((x) >= EVT_TMR43_SCMUH) && ((x) <= EVT_TMR43_SCMWL))          ||         \
    (((x) >= EVT_EVENT_PORT1)  && ((x) <= EVT_EVENT_PORT4))         ||         \
    (((x) >= EVT_I2S1_TXIRQOUT)  && ((x) <= EVT_I2S1_RXIRQOUT))     ||         \
    (((x) >= EVT_I2S2_TXIRQOUT)  && ((x) <= EVT_I2S2_RXIRQOUT))     ||         \
    (((x) >= EVT_I2S3_TXIRQOUT)  && ((x) <= EVT_I2S3_RXIRQOUT))     ||         \
    (((x) >= EVT_I2S4_TXIRQOUT)  && ((x) <= EVT_I2S4_RXIRQOUT))     ||         \
    (((x) >= EVT_ACMP1)  && ((x) <= EVT_ACMP3))                     ||         \
    (((x) >= EVT_I2C1_RXI) && ((x) <= EVT_I2C3_EEI))                ||         \
    (((x) >= EVT_PVD_PVD1) && ((x) <= EVT_OTS))                     ||         \
    ((x)  == EVT_WDT_REFUDF)                                        ||         \
    (((x) >= EVT_ADC1_EOCA) && ((x) <= EVT_TRNG_END))               ||         \
    (((x) >= EVT_SDIOC1_DMAR) && ((x) <= EVT_SDIOC1_DMAW))          ||         \
    (((x) >= EVT_SDIOC2_DMAR) && ((x) <= EVT_SDIOC2_DMAW))          ||         \
    ((x) == EVT_MAX))

/*! Parameter validity check for OTS common trigger. */
#define IS_OTS_COM_TRIGGER(x)                                                   \
(   ((x) == OtsComTrigger_1)                    ||                              \
    ((x) == OtsComTrigger_2)                    ||                              \
    ((x) == OtsComTrigger_1_2))

#define EXPERIMENT_COUNT                ((uint8_t)10)


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static float32_t m_f32SlopeK  = 0.0f;
static float32_t m_f32OffsetM = 0.0f;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
 /**
 *******************************************************************************
 ** \brief Initializes the OTS.
 **
 ** \param [in] pstcInit                See @ref stc_ots_init_t for details.
 **
 ** \retval Ok                          No error occurred.
 ** \retval ErrorInvalidParameter       Parameter error.
 **
 ******************************************************************************/
en_result_t OTS_Init(const stc_ots_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        DDL_ASSERT(IS_OTS_AUTO_OFF(pstcInit->enAutoOff));
        DDL_ASSERT(IS_OTS_CLK_SEL(pstcInit->enClkSel));

        /* Stop ots sampling. */
        bM4_OTS_CTL_OTSST = 0u;
        /* Disable OTS interrupt default. */
        bM4_OTS_CTL_OTSIE = OtsInt_Disable;

        bM4_OTS_CTL_TSSTP = pstcInit->enAutoOff;
        bM4_OTS_CTL_OTSCK = pstcInit->enClkSel;
        m_f32SlopeK       = pstcInit->f32SlopeK;
        m_f32OffsetM      = pstcInit->f32OffsetM;

        enRet = Ok;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Deinitializes the TRNG.
 **
 ** \param  None.
 **
 ** \retval None.
 **
 ******************************************************************************/
void OTS_DeInit(void)
{
    /* Stop ots sampling. */
    bM4_OTS_CTL_OTSST = 0u;

    /* Set the value of all registers to the reset value. */
    M4_OTS->CTL = 0u;
    M4_OTS->DR1 = 0u;
    M4_OTS->DR2 = 0u;
    M4_OTS->ECR = 0u;
}

/**
 *******************************************************************************
 ** \brief  Get temperature via normal mode.
 **
 ** \param  [out] pf32Temp              The address to store the temperature value.
 **
 ** \param  [in]  u32Timeout            Timeout value.
 **
 ** \retval Ok                          No error occurred.
 ** \retval ErrorTimeout                OTS works timeout.
 ** \retval ErrorInvalidParameter       Parameter error.
 **
 ******************************************************************************/
en_result_t OTS_Polling(float32_t *pf32Temp, uint32_t u32Timeout)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pf32Temp != NULL)
    {
        enRet = ErrorTimeout;

        OTS_Start();
        do
        {
            if (bM4_OTS_CTL_OTSST == 0ul)
            {
                *pf32Temp = OTS_CalculateTemp();
                enRet = Ok;
                break;
            }
        } while (u32Timeout-- != 0ul);
        OTS_Stop();
    }

    return enRet;
}
/**
 *******************************************************************************
 ** \brief  Enable or disable OTS interrupt.
 **
 ** \param  [in] enState                Enable or disable OTS interrupt.
 **
 ** \retval None.
 **
 ******************************************************************************/
void OTS_IntCmd(en_functional_state_t enState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enState));

    bM4_OTS_CTL_OTSIE = (uint32_t)enState;
}

/**
 *******************************************************************************
 ** \brief  Set OTS AOS trigger source.
 **
 ** \param  [in] enEvent                See @ref en_event_src_t for details.
 **
 ** \retval None.
 **
 ******************************************************************************/
void OTS_SetTriggerSrc(en_event_src_t enEvent)
{
    uint32_t u32OtrTrg = M4_AOS->OTS_TRG;

    DDL_ASSERT(IS_OTS_TRIG_SRC_EVENT(enEvent) && (EVT_OTS != enEvent));

    u32OtrTrg &= ~0x1FFul;
    u32OtrTrg |= enEvent;

    M4_AOS->OTS_TRG = u32OtrTrg;
}

/**
 *******************************************************************************
 ** \brief Enable or disable OTS common trigger.
 **
 ** \param [in] enComTrigger            OTS common trigger selection. See @ref en_ots_com_trigger_t for details.
 **
 ** \param [in] enState                 Enable or disable the specified common trigger.
 **
 ** \retval None.
 **
 ******************************************************************************/
void OTS_ComTriggerCmd(en_ots_com_trigger_t enComTrigger, en_functional_state_t enState)
{
    uint32_t u32ComTrig = enComTrigger;

    DDL_ASSERT(IS_OTS_COM_TRIGGER(enComTrigger));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enState));

    u32ComTrig <<= 30u;

    if (enState == Enable)
    {
        M4_AOS->OTS_TRG |= u32ComTrig;
    }
    else
    {
        M4_AOS->OTS_TRG &= ~u32ComTrig;
    }
}

/**
*******************************************************************************
** \brief  OTS scaling experiment. If you want to get a more accurate temperature value,
**         you need to do a calibration experiment.
**
** \param  [out] pu16Dr1                Address to store OTS data register 1.
**
** \param  [out] pu16Dr2                Address to store OTS data register 2.
**
** \param  [out] pu16Ecr                Address to store OTS error compensation register.
**
** \param  [out] pf32A                  Address to store parameter A(for calibration experiments).
**
** \param  [in] u32Timeout              Timeout value.
**
** \retval Ok                           No error occurred.
** \retval ErrorTimeout                 OTS works timeout.
** \retval ErrorInvalidParameter        Parameter error.
******************************************************************************/
en_result_t OTS_ScalingExperiment(uint16_t *pu16Dr1, uint16_t *pu16Dr2, \
                                  uint16_t *pu16Ecr, float32_t *pf32A,  \
                                  uint32_t u32Timeout)
{
    float32_t f32Dr1;
    float32_t f32Dr2;
    float32_t f32Ecr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pu16Dr1) && (NULL != pu16Dr2) && \
        (NULL != pu16Ecr) && (NULL != pf32A))
    {
        enRet = ErrorTimeout;
        OTS_Start();
        do
        {
            if (bM4_OTS_CTL_OTSST == 0ul)
            {
                enRet = Ok;
                break;
            }
        } while (u32Timeout-- != 0ul);
        OTS_Stop();

        if (enRet == Ok)
        {
            *pu16Dr1 = M4_OTS->DR1;
            *pu16Dr2 = M4_OTS->DR2;

            f32Dr1 = (float32_t)(*pu16Dr1);
            f32Dr2 = (float32_t)(*pu16Dr2);

            if (bM4_OTS_CTL_OTSCK == OtsClkSel_Hrc)
            {
                *pu16Ecr = M4_OTS->ECR;
                f32Ecr   = (float32_t)(*pu16Ecr);
            }
            else
            {
                *pu16Ecr = 1U;
                f32Ecr   = 1.0f;
            }

            if ((*pu16Dr1 != 0U) && (*pu16Dr2 != 0U) && (*pu16Ecr != 0U))
            {
                *pf32A = ((1.0f / f32Dr1) - (1.0f / f32Dr2)) * f32Ecr;
            }
        }
    }

    return enRet;
}


/**
*******************************************************************************
** \brief  Calculate the value of temperature.
**
** \retval A float32_t type value of temperature value.
******************************************************************************/
float OTS_CalculateTemp(void)
{
    float32_t f32Ret = 0.0f;
    uint16_t u16Dr1  = M4_OTS->DR1;
    uint16_t u16Dr2  = M4_OTS->DR2;
    uint16_t u16Ecr  = M4_OTS->ECR;
    float32_t f32Dr1 = (float32_t)u16Dr1;
    float32_t f32Dr2 = (float32_t)u16Dr2;
    float32_t f32Ecr = (float32_t)u16Ecr;

    if (bM4_OTS_CTL_OTSCK == OtsClkSel_Xtal)
    {
        f32Ecr = 1.0f;
    }

    if ((u16Dr1 != 0U) && (u16Dr2 != 0U) && (u16Ecr != 0U))
    {
        f32Ret = m_f32SlopeK * ((1.0f / f32Dr1) - (1.0f / f32Dr2)) * f32Ecr + m_f32OffsetM;
    }

    return f32Ret;
}

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

//@} // OtsGroup

#endif /* DDL_OTS_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
