/**
 *******************************************************************************
 * @file  hc32f4a0_interrupts.c
 * @brief This file provides firmware functions to manage the Interrupt Controller
 *        (INTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-08-25       Zhangxl         Modify for MISRAC2012-8.4, 8.6, 10.1
   2020-09-09       Zhangxl         Merge EFM0/1 share IRQ handler
   2020-10-30       Zhangxl         Revise I2C TxEmpty & Complete share IRQ handler entry
   2020-11-15       Zhangxl         SPII flag judgment for share IRQ.
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
#include "hc32f4a0_interrupts.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_INTERRUPTS INTERRUPTS
 * @brief INTC Driver Library
 * @{
 */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup INTC_Local_Macros INTC Local Macros
 * @{
 */
/**
 * @brief   Maximum IRQ handler number
 */
#define IRQ_NUM_MAX         (128U)

/**
 * @brief   Wakeup event enable mask
 */
#define INTC_WUPEN_MASK                                                         \
            (INTC_WUPEN_EIRQWUEN    | INTC_WUPEN_SWDTWUEN           |           \
             INTC_WUPEN_PVD1WUEN    | INTC_WUPEN_PVD2WUEN           |           \
             INTC_WUPEN_CMPWUEN     | INTC_WUPEN_WKTMWUEN           |           \
             INTC_WUPEN_RTCALMWUEN  | INTC_WUPEN_RTCPRDWUEN         |           \
             INTC_WUPEN_TMR0GCMWUEN | INTC_WUPEN_TMR2GCMWUEN        |           \
             INTC_WUPEN_TMR2OVFWUEN | INTC_WUPEN_RXWUEN             |           \
             INTC_WUPEN_USHWUEN     | INTC_WUPEN_USFWUEN            |           \
             INTC_WUPEN_ETHWUEN)

/**
 * @}
 */

/**
 * @defgroup INTC_Check_Parameters_Validity INTC Check Parameters Validity
 * @{
 */
/*! Parameter validity check for wakeup source from stop mode. */
#define IS_INTC_WKUP_SRC(src)                                                   \
(   ((src) != 0x00UL)                           &&                              \
    (((src) | INTC_WUPEN_MASK) == INTC_WUPEN_MASK))

/*! Parameter validity check for event index. */
#define IS_INTC_EVENT(event)        ((event) != 0x00UL)

/*! Parameter validity check for interrupt index. */
#define IS_INTC_INT(it)             ((it) != 0x00UL)

/*! Parameter validity check for software interrupt index. */
#define IS_INTC_SWI(swi)            ((swi) != 0x00UL)

/*! Parameter validity check for NMI trigger source. */
#define IS_NMI_SRC(src)                                                         \
(   ((src) != 0x00UL)                           &&                              \
    (((src) | NMI_SRC_MASK) == NMI_SRC_MASK))

/*! Parameter validity check for EXINT filter A function. */
#define IS_EXINT_FAE(fae)                                                       \
(   ((fae) == EXINT_FILTER_A_OFF)               ||                              \
    ((fae) == EXINT_FILTER_A_ON))

/*! Parameter validity check for EXINT filter A clock division. */
#define IS_EXINT_FACLK(faclk)                                                    \
(   ((faclk) == EXINT_FACLK_HCLK_DIV1)          ||                              \
    ((faclk) == EXINT_FACLK_HCLK_DIV8)          ||                              \
    ((faclk) == EXINT_FACLK_HCLK_DIV32)         ||                              \
    ((faclk) == EXINT_FACLK_HCLK_DIV64))

/*! Parameter validity check for EXINT filter B function. */
#define IS_EXINT_FBE(fbe)                                                       \
(   ((fbe) == EXINT_FILTER_B_OFF)               ||                              \
    ((fbe) == EXINT_FILTER_B_ON))

/*! Parameter validity check for EXINT filter B time. */
#define IS_EXINT_FBTIME(fbtime)                                                  \
(   ((fbtime) == EXINT_FBTIM_500NS)             ||                              \
    ((fbtime) == EXINT_FBTIM_1US)               ||                              \
    ((fbtime) == EXINT_FBTIM_2US)               ||                              \
    ((fbtime) == EXINT_FBTIM_4US))


/*! Parameter validity check for EXINT trigger edge. */
#define IS_EXINT_TRIGGER(trigger)                                               \
(   ((trigger) == EXINT_TRIGGER_LOW)            ||                              \
    ((trigger) == EXINT_TRIGGER_RISING)         ||                              \
    ((trigger) == EXINT_TRIGGER_FALLING)        ||                              \
    ((trigger) == EXINT_TRIGGER_BOTH))

/*! Parameter validity check for EXINT channel. */
#define IS_EXINT_CH(ch)                                                         \
(   ((ch) != 0x00UL)                            &&                              \
    (((ch) | EXINT_CH_MASK) == EXINT_CH_MASK))

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
 * @defgroup INTC_Local_Variable INTC Local Variable
 * @{
 */
static func_ptr_t m_apfnIrqHandler[IRQ_NUM_MAX] = {NULL};
static func_ptr_t m_pfnNmiCallback;
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
 * @defgroup INTC_Global_Functions INTC Global Functions
 * @{
 */
/**
 * @brief  IRQ sign in function
 * @param  [in] pstcIrqSignConfig: pointer of IRQ registration structure
 *   @arg  enIntSrc: can be any value @ref en_int_src_t
 *   @arg  enIRQn: can be any value from Int000_IRQn ~ Int127_IRQn @ref IRQn_Type
 *   @arg  pfnCallback: Callback function
 * @retval Ok: IRQ register successfully
 *         ErrorInvalidParameter: IRQ No. and Peripheral Int source are not match;
 *                                NULL pointer.
 *         ErrorUninitialized: Specified IRQ entry was signed before.
 */
en_result_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig)
{
    __IO uint32_t *INTC_SELx;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcIrqSignConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* IRQ032~127 whether out of range */
        if ((((((uint32_t)pstcIrqSignConfig->enIntSrc / 0x20UL) * 6UL + 0x20UL) > (uint32_t)pstcIrqSignConfig->enIRQn) || \
             ((((uint32_t)pstcIrqSignConfig->enIntSrc / 0x20UL) * 6UL + 0x25U) < (uint32_t)pstcIrqSignConfig->enIRQn))&& \
             ((uint32_t)pstcIrqSignConfig->enIRQn >= 0x20UL))
        {
            enRet = ErrorInvalidParameter;
        }
        else
        {
            INTC_SELx = (__IO uint32_t *)((uint32_t)(&M4_INTC->SEL0) + (4U * (uint32_t)pstcIrqSignConfig->enIRQn));
            /* for MISRAC2004-12.4 */
            if (0x1FFUL == ((*INTC_SELx) & 0x1FFUL))
            {
                WRITE_REG32(*INTC_SELx, pstcIrqSignConfig->enIntSrc);
                m_apfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
            }
            else if ((uint32_t)(pstcIrqSignConfig->enIntSrc) == ((*INTC_SELx) & 0x1FFUL))
            {
                WRITE_REG32(*INTC_SELx, pstcIrqSignConfig->enIntSrc);
                m_apfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
            }
            else
            {
                enRet = ErrorUninitialized;
            }
        }
    }
    return enRet;
}

/**
 * @brief  IRQ sign out function
 * @param  [in] enIRQn: can be any value from Int000_IRQn ~ Int127_IRQn @ref IRQn_Type
 * @retval Ok: IRQ sign out successfully
 *         ErrorInvalidParameter: IRQ No. is out of range
 */
en_result_t INTC_IrqSignOut(IRQn_Type enIRQn)
{
    __IO uint32_t *INTC_SELx;
    en_result_t enRet = Ok;

    if ((enIRQn < Int000_IRQn) || (enIRQn > Int127_IRQn))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        INTC_SELx = (__IO uint32_t *)((uint32_t)(&M4_INTC->SEL0) + (4UL * (uint32_t)enIRQn));
        WRITE_REG32(*INTC_SELx, 0x1FFUL);
        m_apfnIrqHandler[enIRQn] = NULL;
    }
    return enRet;
}

/**
 * @brief  Share IRQ configure
 * @param  [in] enIntSrc: Peripheral interrupt source @ref en_int_src_t
 * @param  [in] enNewState:
 *   @arg  Enable: Enable corresponding peripheral interrupt in share IRQ handler
 *   @arg  Disable: Disable corresponding peripheral interrupt in share IRQ handler
 * @retval Ok: Share IRQ configure successfully
 */
en_result_t INTC_ShareIrqCmd(en_int_src_t enIntSrc, en_functional_state_t enNewState)
{
    __IO uint32_t *INTC_VSSELx;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    INTC_VSSELx = (__IO uint32_t *)(((uint32_t)&M4_INTC->VSSEL128) + (4U * ((uint32_t)enIntSrc / 0x20U)));
    if (Enable == enNewState)
    {
        SET_REG32_BIT(*INTC_VSSELx, (uint32_t)(1UL << ((uint32_t)enIntSrc & 0x1FUL)));
    }
    else
    {
        CLEAR_REG32_BIT(*INTC_VSSELx, (1UL << ((uint32_t)enIntSrc & 0x1FUL)));
    }
    return Ok;
}

/**
 * @brief  Stop mode wake-up source configure
 * @param  [in] u32WakeupSrc: Wake-up source
 *   @arg  INTC_WUPEN_EIRQWUEN
 *   @arg  INTC_WUPEN_EIRQWUEN_0
 *   @arg  INTC_WUPEN_EIRQWUEN_1
 *   @arg  INTC_WUPEN_EIRQWUEN_2
 *   @arg  INTC_WUPEN_EIRQWUEN_3
 *   @arg  INTC_WUPEN_EIRQWUEN_4
 *   @arg  INTC_WUPEN_EIRQWUEN_5
 *   @arg  INTC_WUPEN_EIRQWUEN_6
 *   @arg  INTC_WUPEN_EIRQWUEN_7
 *   @arg  INTC_WUPEN_EIRQWUEN_8
 *   @arg  INTC_WUPEN_EIRQWUEN_9
 *   @arg  INTC_WUPEN_EIRQWUEN_10
 *   @arg  INTC_WUPEN_EIRQWUEN_11
 *   @arg  INTC_WUPEN_EIRQWUEN_12
 *   @arg  INTC_WUPEN_EIRQWUEN_13
 *   @arg  INTC_WUPEN_EIRQWUEN_14
 *   @arg  INTC_WUPEN_EIRQWUEN_15
 *   @arg  INTC_WUPEN_SWDTWUEN
 *   @arg  INTC_WUPEN_PVD1WUEN
 *   @arg  INTC_WUPEN_PVD2WUEN
 *   @arg  INTC_WUPEN_CMPWUEN
 *   @arg  INTC_WUPEN_WKTMWUEN
 *   @arg  INTC_WUPEN_RTCALMWUEN
 *   @arg  INTC_WUPEN_RTCPRDWUEN
 *   @arg  INTC_WUPEN_TMR0GCMWUEN
 *   @arg  INTC_WUPEN_TMR2GCMWUEN
 *   @arg  INTC_WUPEN_TMR2OVFWUEN
 *   @arg  INTC_WUPEN_RXWEN
 *   @arg  INTC_WUPEN_USHWUEN
 *   @arg  INTC_WUPEN_USFWUEN
 *   @arg  INTC_WUPEN_ETHWUEN
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding wake up source
 *   @arg  Disable: Disable corresponding wake up source
 * @retval None
 */
void INTC_WakeupSrcCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_WKUP_SRC(u32WakeupSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->WUPEN, u32WakeupSrc);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->WUPEN, u32WakeupSrc);
    }
}

/**
 * @brief  Event or Interrupt output configure
 * @param  [in] u32Event: Event index
 *   @arg  INTC_EVTER_EVTE0
 *   @arg  INTC_EVTER_EVTE1
 *   @arg  INTC_EVTER_EVTE2
 *   @arg  INTC_EVTER_EVTE3
 *   @arg  INTC_EVTER_EVTE4
 *   @arg  INTC_EVTER_EVTE5
 *   @arg  INTC_EVTER_EVTE6
 *   @arg  INTC_EVTER_EVTE7
 *   @arg  INTC_EVTER_EVTE8
 *   @arg  INTC_EVTER_EVTE9
 *   @arg  INTC_EVTER_EVTE10
 *   @arg  INTC_EVTER_EVTE11
 *   @arg  INTC_EVTER_EVTE12
 *   @arg  INTC_EVTER_EVTE13
 *   @arg  INTC_EVTER_EVTE14
 *   @arg  INTC_EVTER_EVTE15
 *   @arg  INTC_EVTER_EVTE16
 *   @arg  INTC_EVTER_EVTE17
 *   @arg  INTC_EVTER_EVTE18
 *   @arg  INTC_EVTER_EVTE19
 *   @arg  INTC_EVTER_EVTE20
 *   @arg  INTC_EVTER_EVTE21
 *   @arg  INTC_EVTER_EVTE22
 *   @arg  INTC_EVTER_EVTE23
 *   @arg  INTC_EVTER_EVTE24
 *   @arg  INTC_EVTER_EVTE25
 *   @arg  INTC_EVTER_EVTE26
 *   @arg  INTC_EVTER_EVTE27
 *   @arg  INTC_EVTER_EVTE28
 *   @arg  INTC_EVTER_EVTE29
 *   @arg  INTC_EVTER_EVTE30
 *   @arg  INTC_EVTER_EVTE31
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding event to NVIC
 *   @arg  Disable: Disable corresponding event but interrupt to NVIC
 * @retval None
 */
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_EVENT(u32Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->EVTER, u32Event);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->EVTER, u32Event);
    }
}

/**
 * @brief  Interrupt function configure
 * @param  [in] u32Int: Interrupt index
 *   @arg  INTC_IER_IER0
 *   @arg  INTC_IER_IER1
 *   @arg  INTC_IER_IER2
 *   @arg  INTC_IER_IER3
 *   @arg  INTC_IER_IER4
 *   @arg  INTC_IER_IER5
 *   @arg  INTC_IER_IER6
 *   @arg  INTC_IER_IER7
 *   @arg  INTC_IER_IER8
 *   @arg  INTC_IER_IER9
 *   @arg  INTC_IER_IER10
 *   @arg  INTC_IER_IER11
 *   @arg  INTC_IER_IER12
 *   @arg  INTC_IER_IER13
 *   @arg  INTC_IER_IER14
 *   @arg  INTC_IER_IER15
 *   @arg  INTC_IER_IER16
 *   @arg  INTC_IER_IER17
 *   @arg  INTC_IER_IER18
 *   @arg  INTC_IER_IER19
 *   @arg  INTC_IER_IER20
 *   @arg  INTC_IER_IER21
 *   @arg  INTC_IER_IER22
 *   @arg  INTC_IER_IER23
 *   @arg  INTC_IER_IER24
 *   @arg  INTC_IER_IER25
 *   @arg  INTC_IER_IER26
 *   @arg  INTC_IER_IER27
 *   @arg  INTC_IER_IER28
 *   @arg  INTC_IER_IER29
 *   @arg  INTC_IER_IER30
 *   @arg  INTC_IER_IER31
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding interrupt to NVIC
 *   @arg  Disable: Disable corresponding interrupt to NVIC
 * @retval None
 */
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_INT(u32Int));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->IER, u32Int);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->IER, u32Int);
    }
}

/**
 * @brief  Software Interrupt function configure
 * @param  [in] u32SWI: Software Interrupt index
 *   @arg  INTC_SWIER_SWIE0
 *   @arg  INTC_SWIER_SWIE1
 *   @arg  INTC_SWIER_SWIE2
 *   @arg  INTC_SWIER_SWIE3
 *   @arg  INTC_SWIER_SWIE4
 *   @arg  INTC_SWIER_SWIE5
 *   @arg  INTC_SWIER_SWIE6
 *   @arg  INTC_SWIER_SWIE7
 *   @arg  INTC_SWIER_SWIE8
 *   @arg  INTC_SWIER_SWIE9
 *   @arg  INTC_SWIER_SWIE10
 *   @arg  INTC_SWIER_SWIE11
 *   @arg  INTC_SWIER_SWIE12
 *   @arg  INTC_SWIER_SWIE13
 *   @arg  INTC_SWIER_SWIE14
 *   @arg  INTC_SWIER_SWIE15
 *   @arg  INTC_SWIER_SWIE16
 *   @arg  INTC_SWIER_SWIE17
 *   @arg  INTC_SWIER_SWIE18
 *   @arg  INTC_SWIER_SWIE19
 *   @arg  INTC_SWIER_SWIE20
 *   @arg  INTC_SWIER_SWIE21
 *   @arg  INTC_SWIER_SWIE22
 *   @arg  INTC_SWIER_SWIE23
 *   @arg  INTC_SWIER_SWIE24
 *   @arg  INTC_SWIER_SWIE25
 *   @arg  INTC_SWIER_SWIE26
 *   @arg  INTC_SWIER_SWIE27
 *   @arg  INTC_SWIER_SWIE28
 *   @arg  INTC_SWIER_SWIE29
 *   @arg  INTC_SWIER_SWIE30
 *   @arg  INTC_SWIER_SWIE31
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding software interrupt
 *   @arg  Disable: Disable corresponding software interrupt
 * @retval None
 */
void INTC_SWICmd(uint32_t u32SWI, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_SWI(u32SWI));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->SWIER, u32SWI);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->SWIER, u32SWI);
    }
}

/**
 * @brief  Initialize NMI. Fill each pstcNmiInit with default value
 * @param  [in] pstcNmiInit: Pointer to a stc_nmi_init_t structure that
 *                             contains configuration information.
 * @retval Ok: NMI structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t NMI_StructInit(stc_nmi_init_t *pstcNmiInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcNmiInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcNmiInit->u32NmiSrc        = 0UL;
        pstcNmiInit->pfnNmiCallback   = NULL;
    }
    return enRet;
}

/**
 * @brief  Initialize NMI.
 * @param  [in] pstcNmiInit: Pointer to a pstcNmiInit structure that
 *                             contains configuration information.
 * @retval Ok: NMI initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t NMI_Init(const stc_nmi_init_t *pstcNmiInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if ((NULL == pstcNmiInit) || (NULL == pstcNmiInit->pfnNmiCallback))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_NMI_SRC(pstcNmiInit->u32NmiSrc));

        /* Clear all NMI trigger source before set */
        WRITE_REG32(M4_INTC->NMICFR, INTC_NMICLR_MASK);

        /* NMI trigger source configure */
        WRITE_REG32(M4_INTC->NMIENR, pstcNmiInit->u32NmiSrc);

        /* NMI callback function configure */
        m_pfnNmiCallback = pstcNmiInit->pfnNmiCallback;
    }
    return enRet;
}

/**
 * @brief  Get NMI trigger source
 * @param  [in] u32NmiSrc: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_PVD1
 *   @arg  NMI_SRC_PVD2
 *   @arg  NMI_SRC_XTAL
 *   @arg  NMI_SRC_SRAM_PARITY
 *   @arg  NMI_SRC_SRAM_ECC
 *   @arg  NMI_SRC_BUS_ERR
 *   @arg  NMI_SRC_WDT
 * @retval Set: NMI is triggered by corresponding source
 *         Reset: NMI is not triggered by corresponding source
 */
en_flag_status_t NMI_GetNmiSrc(uint32_t u32NmiSrc)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32NmiSrc));

    return (((READ_REG32(M4_INTC->NMIFR) & u32NmiSrc)) != 0UL) ? Set : Reset;
}

/**
 * @brief  Set NMI trigger source
 * @param  [in] u32NmiSrc: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_PVD1
 *   @arg  NMI_SRC_PVD2
 *   @arg  NMI_SRC_XTAL
 *   @arg  NMI_SRC_SRAM_PARITY
 *   @arg  NMI_SRC_SRAM_ECC
 *   @arg  NMI_SRC_BUS_ERR
 *   @arg  NMI_SRC_WDT
 * @retval None
 */
void NMI_SetNmiSrc(uint32_t u32NmiSrc)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32NmiSrc));

    WRITE_REG32(M4_INTC->NMIENR, u32NmiSrc);
}

/**
 * @brief  Clear specified NMI trigger source
 * @param  [in] u32NmiSrc: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_PVD1
 *   @arg  NMI_SRC_PVD2
 *   @arg  NMI_SRC_XTAL
 *   @arg  NMI_SRC_SRAM_PARITY
 *   @arg  NMI_SRC_SRAM_ECC
 *   @arg  NMI_SRC_BUS_ERR
 *   @arg  NMI_SRC_WDT
 * @retval None
 */
void NMI_ClrNmiSrc(uint32_t u32NmiSrc)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32NmiSrc));

    SET_REG32_BIT(M4_INTC->NMICFR, u32NmiSrc);
}

/**
 * @brief  NMI IRQ handler
 * @param  None
 * @retval None
 */
void NMI_IrqHandler(void)
{
    if (NULL != m_pfnNmiCallback)
    {
        m_pfnNmiCallback();
    }
}

/**
 * @brief  Initialize External interrupt.
 * @param  [in] pstcExIntInit: Pointer to a stc_exint_init_t structure that
 *                             contains configuration information.
 * @retval Ok:  EXINT initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t EXINT_Init(const stc_exint_init_t *pstcExIntInit)
{
    uint8_t u8ExIntPos;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcExIntInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_EXINT_FAE(pstcExIntInit->u32ExIntFAE));
        DDL_ASSERT(IS_EXINT_FACLK(pstcExIntInit->u32ExIntFAClk));
        DDL_ASSERT(IS_EXINT_FBE(pstcExIntInit->u32ExIntFBE));
        DDL_ASSERT(IS_EXINT_FBTIME(pstcExIntInit->u32ExIntFBTime));
        DDL_ASSERT(IS_EXINT_TRIGGER(pstcExIntInit->u32ExIntLvl));
        DDL_ASSERT(IS_EXINT_CH(pstcExIntInit->u32ExIntCh));

        for (u8ExIntPos = 0U; u8ExIntPos < 16U; u8ExIntPos++)
        {
            if ((pstcExIntInit->u32ExIntCh & (1UL << u8ExIntPos)) != 0U)
            {
                WRITE_REG32(*(uint32_t *)((uint32_t)(&M4_INTC->EIRQCR0) + 4UL*u8ExIntPos),  \
                          (pstcExIntInit->u32ExIntFAE         |                           \
                           pstcExIntInit->u32ExIntFAClk       |                           \
                           pstcExIntInit->u32ExIntFBE         |                           \
                           pstcExIntInit->u32ExIntLvl));
                WRITE_REG32(M4_INTC->NOCCR, pstcExIntInit->u32ExIntFBTime);
            }
        }
    }
    return enRet;
}

/**
 * @brief  Initialize ExInt. Fill each pstcExIntInit with default value
 * @param  [in] pstcExIntInit: Pointer to a stc_exint_init_t structure
 *                              that contains configuration information.
 * @retval Ok: EXINT structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t EXINT_StructInit(stc_exint_init_t *pstcExIntInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcExIntInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcExIntInit->u32ExIntCh     = (uint32_t)0UL;
        pstcExIntInit->u32ExIntFAE    = EXINT_FILTER_A_OFF;
        pstcExIntInit->u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV1;
        pstcExIntInit->u32ExIntFBE    = EXINT_FILTER_B_OFF;
        pstcExIntInit->u32ExIntFBTime = EXINT_FBTIM_500NS;
        pstcExIntInit->u32ExIntLvl    = EXINT_TRIGGER_FALLING;
    }
    return enRet;
}

/**
 * @brief  Clear specified External interrupt trigger source
 * @param  [in] u32ExIntCh: External interrupt channel, @ref EXINT_Channel_Sel for details
 *   @arg  EXINT_CH00
 *   @arg  EXINT_CH01
 *   @arg  EXINT_CH02
 *   @arg  EXINT_CH03
 *   @arg  EXINT_CH04
 *   @arg  EXINT_CH05
 *   @arg  EXINT_CH06
 *   @arg  EXINT_CH07
 *   @arg  EXINT_CH08
 *   @arg  EXINT_CH09
 *   @arg  EXINT_CH10
 *   @arg  EXINT_CH11
 *   @arg  EXINT_CH12
 *   @arg  EXINT_CH13
 *   @arg  EXINT_CH14
 *   @arg  EXINT_CH15
 * @retval None
 */
void EXINT_ClrExIntSrc(uint32_t u32ExIntCh)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXINT_CH(u32ExIntCh));

    SET_REG32_BIT(M4_INTC->EICFR, u32ExIntCh);
}

/**
 * @brief  Get specified External interrupt trigger source
 * @param  [in] u32ExIntCh: External interrupt channel, @ref EXINT_Channel_Sel for details
 *   @arg  EXINT_CH00
 *   @arg  EXINT_CH01
 *   @arg  EXINT_CH02
 *   @arg  EXINT_CH03
 *   @arg  EXINT_CH04
 *   @arg  EXINT_CH05
 *   @arg  EXINT_CH06
 *   @arg  EXINT_CH07
 *   @arg  EXINT_CH08
 *   @arg  EXINT_CH09
 *   @arg  EXINT_CH10
 *   @arg  EXINT_CH11
 *   @arg  EXINT_CH12
 *   @arg  EXINT_CH13
 *   @arg  EXINT_CH14
 *   @arg  EXINT_CH15
 * @retval Set: Specified channel of external interrupt is triggered
 *         Reset: Specified channel of external interrupt is not triggered
 */
en_flag_status_t EXINT_GetExIntSrc(uint32_t u32ExIntCh)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXINT_CH(u32ExIntCh));

    return ((READ_REG16(M4_INTC->EIFR) & u32ExIntCh) != 0U) ? Set : Reset;
}

/**
 * @brief  NMI IRQ handler
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
    NMI_IrqHandler();
}

/**
 * @brief  Hard Fault IRQ handler
 * @param  None
 * @retval None
 */
__WEAKDEF void HardFault_Handler(void)
{
    HardFault_IrqHandler();
}

/**
 * @brief  Mem manage fault IRQ handler
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    MemManage_IrqHandler();
}

/**
 * @brief  Bus fault IRQ handler
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    BusFault_IrqHandler();
}

/**
 * @brief  Usage fault IRQ handler
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    UsageFault_IrqHandler();
}

/**
 * @brief  SVCall IRQ handler
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
    SVC_IrqHandler();
}

/**
 * @brief  Debbug monitor IRQ handler
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
    DebugMon_IrqHandler();
}

/**
 * @brief  PendSV IRQ handler
 * @param  None
 * @retval None
 */
__WEAKDEF void PendSV_Handler(void)
{
    PendSV_IrqHandler();
}

/**
 * @brief  SysTick IRQ handler
 * @param  None
 * @retval None
 */
__WEAKDEF void SysTick_Handler(void)
{
    SysTick_IrqHandler();
}

/**
 * @brief  Interrupt No.000 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ000_Handler(void)
{
    m_apfnIrqHandler[Int000_IRQn]();
}

/**
 * @brief  Interrupt No.001 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ001_Handler(void)
{
    m_apfnIrqHandler[Int001_IRQn]();
}

/**
 * @brief  Interrupt No.002 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ002_Handler(void)
{
    m_apfnIrqHandler[Int002_IRQn]();
}

/**
 * @brief  Interrupt No.003 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ003_Handler(void)
{
    m_apfnIrqHandler[Int003_IRQn]();
}

/**
 * @brief  Interrupt No.004 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ004_Handler(void)
{
    m_apfnIrqHandler[Int004_IRQn]();
}

/**
 * @brief  Interrupt No.005 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ005_Handler(void)
{
    m_apfnIrqHandler[Int005_IRQn]();
}

/**
 * @brief  Interrupt No.006 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ006_Handler(void)
{
    m_apfnIrqHandler[Int006_IRQn]();
}

/**
 * @brief  Interrupt No.007 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ007_Handler(void)
{
    m_apfnIrqHandler[Int007_IRQn]();
}

/**
 * @brief  Interrupt No.008 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ008_Handler(void)
{
    m_apfnIrqHandler[Int008_IRQn]();
}

/**
 * @brief  Interrupt No.009 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ009_Handler(void)
{
    m_apfnIrqHandler[Int009_IRQn]();
}

/**
 * @brief  Interrupt No.010 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ010_Handler(void)
{
    m_apfnIrqHandler[Int010_IRQn]();
}


/**
 * @brief  Interrupt No.011 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ011_Handler(void)
{
    m_apfnIrqHandler[Int011_IRQn]();
}

/**
 * @brief  Interrupt No.012 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ012_Handler(void)
{
    m_apfnIrqHandler[Int012_IRQn]();
}

/**
 * @brief  Interrupt No.013 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ013_Handler(void)
{
    m_apfnIrqHandler[Int013_IRQn]();
}

/**
 * @brief  Interrupt No.014 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ014_Handler(void)
{
    m_apfnIrqHandler[Int014_IRQn]();
}

/**
 * @brief  Interrupt No.015 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ015_Handler(void)
{
    m_apfnIrqHandler[Int015_IRQn]();
}

/**
 * @brief  Interrupt No.016 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ016_Handler(void)
{
    m_apfnIrqHandler[Int016_IRQn]();
}

/**
 * @brief  Interrupt No.017 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ017_Handler(void)
{
    m_apfnIrqHandler[Int017_IRQn]();
}

/**
 * @brief  Interrupt No.018 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ018_Handler(void)
{
    m_apfnIrqHandler[Int018_IRQn]();
}

/**
 * @brief  Interrupt No.019 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ019_Handler(void)
{
    m_apfnIrqHandler[Int019_IRQn]();
}

/**
 * @brief  Interrupt No.020 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ020_Handler(void)
{
    m_apfnIrqHandler[Int020_IRQn]();
}

/**
 * @brief  Interrupt No.021 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ021_Handler(void)
{
    m_apfnIrqHandler[Int021_IRQn]();
}

/**
 * @brief  Interrupt No.022 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ022_Handler(void)
{
    m_apfnIrqHandler[Int022_IRQn]();
}

/**
 * @brief  Interrupt No.023 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ023_Handler(void)
{
    m_apfnIrqHandler[Int023_IRQn]();
}

/**
 * @brief  Interrupt No.024 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ024_Handler(void)
{
    m_apfnIrqHandler[Int024_IRQn]();
}

/**
 * @brief  Interrupt No.025 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ025_Handler(void)
{
    m_apfnIrqHandler[Int025_IRQn]();
}

/**
 * @brief  Interrupt No.026 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ026_Handler(void)
{
    m_apfnIrqHandler[Int026_IRQn]();
}

/**
 * @brief  Interrupt No.027 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ027_Handler(void)
{
    m_apfnIrqHandler[Int027_IRQn]();
}

/**
 * @brief  Interrupt No.028 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ028_Handler(void)
{
    m_apfnIrqHandler[Int028_IRQn]();
}

/**
 * @brief  Interrupt No.029 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ029_Handler(void)
{
    m_apfnIrqHandler[Int029_IRQn]();
}

/**
 * @brief  Interrupt No.030 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ030_Handler(void)
{
    m_apfnIrqHandler[Int030_IRQn]();
}

/**
 * @brief  Interrupt No.031 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ031_Handler(void)
{
    m_apfnIrqHandler[Int031_IRQn]();
}

/**
 * @brief  Interrupt No.032 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ032_Handler(void)
{
    m_apfnIrqHandler[Int032_IRQn]();
}

/**
 * @brief  Interrupt No.033 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ033_Handler(void)
{
    m_apfnIrqHandler[Int033_IRQn]();
}

/**
 * @brief  Interrupt No.034 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ034_Handler(void)
{
    m_apfnIrqHandler[Int034_IRQn]();
}

/**
 * @brief  Interrupt No.035 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ035_Handler(void)
{
    m_apfnIrqHandler[Int035_IRQn]();
}

/**
 * @brief  Interrupt No.036 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ036_Handler(void)
{
    m_apfnIrqHandler[Int036_IRQn]();
}

/**
 * @brief  Interrupt No.037 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ037_Handler(void)
{
    m_apfnIrqHandler[Int037_IRQn]();
}

/**
 * @brief  Interrupt No.038 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ038_Handler(void)
{
    m_apfnIrqHandler[Int038_IRQn]();
}

/**
 * @brief  Interrupt No.039 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ039_Handler(void)
{
    m_apfnIrqHandler[Int039_IRQn]();
}

/**
 * @brief  Interrupt No.040 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ040_Handler(void)
{
    m_apfnIrqHandler[Int040_IRQn]();
}

/**
 * @brief  Interrupt No.041 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ041_Handler(void)
{
    m_apfnIrqHandler[Int041_IRQn]();
}

/**
 * @brief  Interrupt No.042 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ042_Handler(void)
{
    m_apfnIrqHandler[Int042_IRQn]();
}

/**
 * @brief  Interrupt No.043 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ043_Handler(void)
{
    m_apfnIrqHandler[Int043_IRQn]();
}

/**
 * @brief  Interrupt No.044 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ044_Handler(void)
{
    m_apfnIrqHandler[Int044_IRQn]();
}

/**
 * @brief  Interrupt No.045 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ045_Handler(void)
{
    m_apfnIrqHandler[Int045_IRQn]();
}

/**
 * @brief  Interrupt No.046 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ046_Handler(void)
{
    m_apfnIrqHandler[Int046_IRQn]();
}

/**
 * @brief  Interrupt No.047 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ047_Handler(void)
{
    m_apfnIrqHandler[Int047_IRQn]();
}

/**
 * @brief  Interrupt No.048 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ048_Handler(void)
{
    m_apfnIrqHandler[Int048_IRQn]();
}

/**
 * @brief  Interrupt No.049 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ049_Handler(void)
{
    m_apfnIrqHandler[Int049_IRQn]();
}

/**
 * @brief  Interrupt No.050 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ050_Handler(void)
{
    m_apfnIrqHandler[Int050_IRQn]();
}

/**
 * @brief  Interrupt No.051 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ051_Handler(void)
{
    m_apfnIrqHandler[Int051_IRQn]();
}

/**
 * @brief  Interrupt No.052 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ052_Handler(void)
{
    m_apfnIrqHandler[Int052_IRQn]();
}

/**
 * @brief  Interrupt No.053 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ053_Handler(void)
{
    m_apfnIrqHandler[Int053_IRQn]();
}

/**
 * @brief  Interrupt No.054 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ054_Handler(void)
{
    m_apfnIrqHandler[Int054_IRQn]();
}

/**
 * @brief  Interrupt No.055 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ055_Handler(void)
{
    m_apfnIrqHandler[Int055_IRQn]();
}

/**
 * @brief  Interrupt No.056 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ056_Handler(void)
{
    m_apfnIrqHandler[Int056_IRQn]();
}

/**
 * @brief  Interrupt No.057 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ057_Handler(void)
{
    m_apfnIrqHandler[Int057_IRQn]();
}

/**
 * @brief  Interrupt No.058 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ058_Handler(void)
{
    m_apfnIrqHandler[Int058_IRQn]();
}

/**
 * @brief  Interrupt No.059 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ059_Handler(void)
{
    m_apfnIrqHandler[Int059_IRQn]();
}

/**
 * @brief  Interrupt No.060 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ060_Handler(void)
{
    m_apfnIrqHandler[Int060_IRQn]();
}

/**
 * @brief  Interrupt No.061 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ061_Handler(void)
{
    m_apfnIrqHandler[Int061_IRQn]();
}

/**
 * @brief  Interrupt No.062 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ062_Handler(void)
{
    m_apfnIrqHandler[Int062_IRQn]();
}

/**
 * @brief  Interrupt No.063 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ063_Handler(void)
{
    m_apfnIrqHandler[Int063_IRQn]();
}

/**
 * @brief  Interrupt No.064 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ064_Handler(void)
{
    m_apfnIrqHandler[Int064_IRQn]();
}

/**
 * @brief  Interrupt No.065 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ065_Handler(void)
{
    m_apfnIrqHandler[Int065_IRQn]();
}

/**
 * @brief  Interrupt No.066 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ066_Handler(void)
{
    m_apfnIrqHandler[Int066_IRQn]();
}

/**
 * @brief  Interrupt No.067 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ067_Handler(void)
{
    m_apfnIrqHandler[Int067_IRQn]();
}

/**
 * @brief  Interrupt No.068 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ068_Handler(void)
{
    m_apfnIrqHandler[Int068_IRQn]();
}

/**
 * @brief  Interrupt No.069 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ069_Handler(void)
{
    m_apfnIrqHandler[Int069_IRQn]();
}

/**
 * @brief  Interrupt No.070 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ070_Handler(void)
{
    m_apfnIrqHandler[Int070_IRQn]();
}

/**
 * @brief  Interrupt No.071 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ071_Handler(void)
{
    m_apfnIrqHandler[Int071_IRQn]();
}

/**
 * @brief  Interrupt No.072 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ072_Handler(void)
{
    m_apfnIrqHandler[Int072_IRQn]();
}

/**
 * @brief  Interrupt No.073 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ073_Handler(void)
{
    m_apfnIrqHandler[Int073_IRQn]();
}

/**
 * @brief  Interrupt No.074 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ074_Handler(void)
{
    m_apfnIrqHandler[Int074_IRQn]();
}

/**
 * @brief  Interrupt No.075 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ075_Handler(void)
{
    m_apfnIrqHandler[Int075_IRQn]();
}

/**
 * @brief  Interrupt No.076 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ076_Handler(void)
{
    m_apfnIrqHandler[Int076_IRQn]();
}

/**
 * @brief  Interrupt No.077 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ077_Handler(void)
{
    m_apfnIrqHandler[Int077_IRQn]();
}

/**
 * @brief  Interrupt No.078 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ078_Handler(void)
{
    m_apfnIrqHandler[Int078_IRQn]();
}

/**
 * @brief  Interrupt No.079 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ079_Handler(void)
{
    m_apfnIrqHandler[Int079_IRQn]();
}

/**
 * @brief  Interrupt No.080 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ080_Handler(void)
{
    m_apfnIrqHandler[Int080_IRQn]();
}

/**
 * @brief  Interrupt No.081 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ081_Handler(void)
{
    m_apfnIrqHandler[Int081_IRQn]();
}

/**
 * @brief  Interrupt No.082 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ082_Handler(void)
{
    m_apfnIrqHandler[Int082_IRQn]();
}

/**
 * @brief  Interrupt No.083 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ083_Handler(void)
{
    m_apfnIrqHandler[Int083_IRQn]();
}

/**
 * @brief  Interrupt No.084 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ084_Handler(void)
{
    m_apfnIrqHandler[Int084_IRQn]();
}

/**
 * @brief  Interrupt No.085 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ085_Handler(void)
{
    m_apfnIrqHandler[Int085_IRQn]();
}

/**
 * @brief  Interrupt No.086 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ086_Handler(void)
{
    m_apfnIrqHandler[Int086_IRQn]();
}

/**
 * @brief  Interrupt No.087 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ087_Handler(void)
{
    m_apfnIrqHandler[Int087_IRQn]();
}

/**
 * @brief  Interrupt No.088 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ088_Handler(void)
{
    m_apfnIrqHandler[Int088_IRQn]();
}

/**
 * @brief  Interrupt No.089 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ089_Handler(void)
{
    m_apfnIrqHandler[Int089_IRQn]();
}

/**
 * @brief  Interrupt No.090 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ090_Handler(void)
{
    m_apfnIrqHandler[Int090_IRQn]();
}

/**
 * @brief  Interrupt No.091 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ091_Handler(void)
{
    m_apfnIrqHandler[Int091_IRQn]();
}

/**
 * @brief  Interrupt No.092 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ092_Handler(void)
{
    m_apfnIrqHandler[Int092_IRQn]();
}

/**
 * @brief  Interrupt No.093 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ093_Handler(void)
{
    m_apfnIrqHandler[Int093_IRQn]();
}

/**
 * @brief  Interrupt No.094 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ094_Handler(void)
{
    m_apfnIrqHandler[Int094_IRQn]();
}

/**
 * @brief  Interrupt No.095 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ095_Handler(void)
{
    m_apfnIrqHandler[Int095_IRQn]();
}

/**
 * @brief  Interrupt No.096 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ096_Handler(void)
{
    m_apfnIrqHandler[Int096_IRQn]();
}

/**
 * @brief  Interrupt No.097 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ097_Handler(void)
{
    m_apfnIrqHandler[Int097_IRQn]();
}

/**
 * @brief  Interrupt No.098 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ098_Handler(void)
{
    m_apfnIrqHandler[Int098_IRQn]();
}

/**
 * @brief  Interrupt No.099 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ099_Handler(void)
{
    m_apfnIrqHandler[Int099_IRQn]();
}

/**
 * @brief  Interrupt No.100 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ100_Handler(void)
{
    m_apfnIrqHandler[Int100_IRQn]();
}

/**
 * @brief  Interrupt No.101 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ101_Handler(void)
{
    m_apfnIrqHandler[Int101_IRQn]();
}

/**
 * @brief  Interrupt No.102 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ102_Handler(void)
{
    m_apfnIrqHandler[Int102_IRQn]();
}

/**
 * @brief  Interrupt No.103 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ103_Handler(void)
{
    m_apfnIrqHandler[Int103_IRQn]();
}

/**
 * @brief  Interrupt No.104 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ104_Handler(void)
{
    m_apfnIrqHandler[Int104_IRQn]();
}

/**
 * @brief  Interrupt No.105 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ105_Handler(void)
{
    m_apfnIrqHandler[Int105_IRQn]();
}

/**
 * @brief  Interrupt No.106 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ106_Handler(void)
{
    m_apfnIrqHandler[Int106_IRQn]();
}

/**
 * @brief  Interrupt No.107 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ107_Handler(void)
{
    m_apfnIrqHandler[Int107_IRQn]();
}

/**
 * @brief  Interrupt No.108 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ108_Handler(void)
{
    m_apfnIrqHandler[Int108_IRQn]();
}

/**
 * @brief  Interrupt No.109 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ109_Handler(void)
{
    m_apfnIrqHandler[Int109_IRQn]();
}

/**
 * @brief  Interrupt No.110 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ110_Handler(void)
{
    m_apfnIrqHandler[Int110_IRQn]();
}

/**
 * @brief  Interrupt No.111 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ111_Handler(void)
{
    m_apfnIrqHandler[Int111_IRQn]();
}

/**
 * @brief  Interrupt No.112 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ112_Handler(void)
{
    m_apfnIrqHandler[Int112_IRQn]();
}

/**
 * @brief  Interrupt No.113 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ113_Handler(void)
{
    m_apfnIrqHandler[Int113_IRQn]();
}

/**
 * @brief  Interrupt No.114 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ114_Handler(void)
{
    m_apfnIrqHandler[Int114_IRQn]();
}

/**
 * @brief  Interrupt No.115 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ115_Handler(void)
{
    m_apfnIrqHandler[Int115_IRQn]();
}

/**
 * @brief  Interrupt No.116 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ116_Handler(void)
{
    m_apfnIrqHandler[Int116_IRQn]();
}

/**
 * @brief  Interrupt No.117 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ117_Handler(void)
{
    m_apfnIrqHandler[Int117_IRQn]();
}

/**
 * @brief  Interrupt No.118 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ118_Handler(void)
{
    m_apfnIrqHandler[Int118_IRQn]();
}

/**
 * @brief  Interrupt No.119 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ119_Handler(void)
{
    m_apfnIrqHandler[Int119_IRQn]();
}

/**
 * @brief  Interrupt No.120 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ120_Handler(void)
{
    m_apfnIrqHandler[Int120_IRQn]();
}

/**
 * @brief  Interrupt No.121 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ121_Handler(void)
{
    m_apfnIrqHandler[Int121_IRQn]();
}

/**
 * @brief  Interrupt No.122 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ122_Handler(void)
{
    m_apfnIrqHandler[Int122_IRQn]();
}

/**
 * @brief  Interrupt No.123 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ123_Handler(void)
{
    m_apfnIrqHandler[Int123_IRQn]();
}

/**
 * @brief  Interrupt No.124 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ124_Handler(void)
{
    m_apfnIrqHandler[Int124_IRQn]();
}

/**
 * @brief  Interrupt No.125 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ125_Handler(void)
{
    m_apfnIrqHandler[Int125_IRQn]();
}

/**
 * @brief  Interrupt No.126 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ126_Handler(void)
{
    m_apfnIrqHandler[Int126_IRQn]();
}

/**
 * @brief  Interrupt No.127 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ127_Handler(void)
{
    m_apfnIrqHandler[Int127_IRQn]();
}

/**
 * @brief  Interrupt No.128 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ128_Handler(void)
{
    const uint32_t VSSEL128 = M4_INTC->VSSEL128;

    /* external interrupt 00 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR0) && (0UL != (VSSEL128 & BIT_MASK_00)))
    {
        EXTINT_00_IrqHandler();
    }
    /* external interrupt 01 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR1) && (0UL != (VSSEL128 & BIT_MASK_01)))
    {
        EXTINT_01_IrqHandler();
    }
    /* external interrupt 02 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR2) && (0UL != (VSSEL128 & BIT_MASK_02)))
    {
        EXTINT_02_IrqHandler();
    }
    /* external interrupt 03 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR3) && (0UL != (VSSEL128 & BIT_MASK_03)))
    {
        EXTINT_03_IrqHandler();
    }
    /* external interrupt 04 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR4) && (0UL != (VSSEL128 & BIT_MASK_04)))
    {
        EXTINT_04_IrqHandler();
    }
    /* external interrupt 05 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR5) && (0UL != (VSSEL128 & BIT_MASK_05)))
    {
        EXTINT_05_IrqHandler();
    }
    /* external interrupt 06 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR6) && (0UL != (VSSEL128 & BIT_MASK_06)))
    {
        EXTINT_06_IrqHandler();
    }
    /* external interrupt 07 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR7) && (0UL != (VSSEL128 & BIT_MASK_07)))
    {
        EXTINT_07_IrqHandler();
    }
    /* external interrupt 08 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR8) && (0UL != (VSSEL128 & BIT_MASK_08)))
    {
        EXTINT_08_IrqHandler();
    }
    /* external interrupt 09 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR9) && (0UL != (VSSEL128 & BIT_MASK_09)))
    {
        EXTINT_09_IrqHandler();
    }
    /* external interrupt 10 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR10) && (0UL != (VSSEL128 & BIT_MASK_10)))
    {
        EXTINT_10_IrqHandler();
    }
    /* external interrupt 11 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR11) && (0UL != (VSSEL128 & BIT_MASK_11)))
    {
        EXTINT_11_IrqHandler();
    }
    /* external interrupt 12 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR12) && (0UL != (VSSEL128 & BIT_MASK_12)))
    {
        EXTINT_12_IrqHandler();
    }
    /* external interrupt 13 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR13) && (0UL != (VSSEL128 & BIT_MASK_13)))
    {
        EXTINT_13_IrqHandler();
    }
    /* external interrupt 14 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR14) && (0UL != (VSSEL128 & BIT_MASK_14)))
    {
        EXTINT_14_IrqHandler();
    }
    /* external interrupt 15 */
    if ((1UL == bM4_INTC->EIFR_b.EIFR15) && (0UL != (VSSEL128 & BIT_MASK_15)))
    {
        EXTINT_15_IrqHandler();
    }
}

/**
 * @brief  Interrupt No.129 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ129_Handler(void)
{
    const uint32_t VSSEL129 = M4_INTC->VSSEL129;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* DMA1 Ch.0 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL0_b.IE)
    {
        /* DMA1 Ch.0 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC0)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC0) && (0UL != (VSSEL129 & BIT_MASK_00)))
            {
                DMA_1_Tc0_IrqHandler();
            }
        }
        /* DMA1 ch.0 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC0)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC0) && (0UL != (VSSEL129 & BIT_MASK_08)))
            {
                DMA_1_Btc0_IrqHandler();
            }
        }
        /* DMA1 ch.0 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_00 | BIT_MASK_16);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_00 | BIT_MASK_16));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err0_IrqHandler();
        }
    }
    /* DMA1 Ch.1 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL1_b.IE)
    {
        /* DMA1 Ch.1 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC1)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC1) && (0UL != (VSSEL129 & BIT_MASK_01)))
            {
                DMA_1_Tc1_IrqHandler();
            }
        }
        /* DMA1 ch.1 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC1)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC1) && (0UL != (VSSEL129 & BIT_MASK_09)))
            {
                DMA_1_Btc1_IrqHandler();
            }
        }
        /* DMA1 ch.1 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_01 | BIT_MASK_17);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_01 | BIT_MASK_17));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err1_IrqHandler();
        }
    }
    /* DMA1 Ch.2 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL2_b.IE)
    {
        /* DMA1 Ch.2 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC2)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC2) && (0UL != (VSSEL129 & BIT_MASK_02)))
            {
                DMA_1_Tc2_IrqHandler();
            }
        }
        /* DMA1 ch.2 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC2)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC2) && (0UL != (VSSEL129 & BIT_MASK_10)))
            {
                DMA_1_Btc2_IrqHandler();
            }
        }
        /* DMA1 ch.2 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_02 | BIT_MASK_18);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_02 | BIT_MASK_18));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err2_IrqHandler();
        }
    }
    /* DMA1 Ch.3 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL3_b.IE)
    {
        /* DMA1 Ch.3 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC3)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC3) && (0UL != (VSSEL129 & BIT_MASK_03)))
            {
                DMA_1_Tc3_IrqHandler();
            }
        }
        /* DMA1 ch.3 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC3)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC3) && (0UL != (VSSEL129 & BIT_MASK_11)))
            {
                DMA_1_Btc3_IrqHandler();
            }
        }
        /* DMA1 ch.3 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_03 | BIT_MASK_19);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_03 | BIT_MASK_19));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err3_IrqHandler();
        }
    }
    /* DMA1 Ch.4 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL4_b.IE)
    {
        /* DMA1 Ch.4 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC4)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC4) && (0UL != (VSSEL129 & BIT_MASK_04)))
            {
                DMA_1_Tc4_IrqHandler();
            }
        }
        /* DMA1 ch.4 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC4)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC4) && (0UL != (VSSEL129 & BIT_MASK_12)))
            {
                DMA_1_Btc4_IrqHandler();
            }
        }
        /* DMA1 ch.4 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_04 | BIT_MASK_20);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_04 | BIT_MASK_20));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err4_IrqHandler();
        }
    }
    /* DMA1 Ch.5 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL5_b.IE)
    {
        /* DMA1 Ch.5 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC5)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC5) && (0UL != (VSSEL129 & BIT_MASK_05)))
            {
                DMA_1_Tc5_IrqHandler();
            }
        }
        /* DMA1 ch.5 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC5)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC5) && (0UL != (VSSEL129 & BIT_MASK_13)))
            {
                DMA_1_Btc5_IrqHandler();
            }
        }
        /* DMA1 ch.5 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_05 | BIT_MASK_21);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_05 | BIT_MASK_21));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err5_IrqHandler();
        }
    }
    /* DMA1 Ch.6 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL6_b.IE)
    {
        /* DMA1 Ch.6 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC6)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC6) && (0UL != (VSSEL129 & BIT_MASK_06)))
            {
                DMA_1_Tc6_IrqHandler();
            }
        }
        /* DMA1 ch.6 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC6)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC6) && (0UL != (VSSEL129 & BIT_MASK_14)))
            {
                DMA_1_Btc6_IrqHandler();
            }
        }
        /* DMA1 ch.6 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_06 | BIT_MASK_22);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_06 | BIT_MASK_22));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err6_IrqHandler();
        }
    }
    /* DMA1 Ch.7 interrupt enabled */
    if (1UL == bM4_DMA1->CHCTL7_b.IE)
    {
        /* DMA1 Ch.7 Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKTC7)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.TC7) && (0UL != (VSSEL129 & BIT_MASK_07)))
            {
                DMA_1_Tc7_IrqHandler();
            }
        }
        /* DMA1 ch.7 Block Tx completed */
        if (0UL == bM4_DMA1->INTMASK1_b.MSKBTC7)
        {
            if ((1UL == bM4_DMA1->INTSTAT1_b.BTC7) && (0UL != (VSSEL129 & BIT_MASK_15)))
            {
                DMA_1_Btc7_IrqHandler();
            }
        }
        /* DMA1 ch.7 Transfer/Request Error */
        u32Tmp1 = M4_DMA1->INTSTAT0 & (BIT_MASK_07 | BIT_MASK_22);
        u32Tmp2 = (uint32_t)(~(M4_DMA1->INTMASK0) & (BIT_MASK_07 | BIT_MASK_22));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16)))
        {
            DMA_1_Err7_IrqHandler();
        }
    }
    /* EFM error */
    if (0UL != bM4_EFM->FITE_b.PEERRITE)
    {
        /* EFM program/erase/protect/otp error */
        u32Tmp1 = M4_EFM->FSR & (EFM_FSR_PRTWERR0 | EFM_FSR_PGSZERR0 | EFM_FSR_MISMTCH0 |   \
                                 EFM_FSR_PRTWERR1 | EFM_FSR_PGSZERR1 | EFM_FSR_MISMTCH1 |   \
                                 EFM_FSR_OTPWERR0);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_17)))
        {
            EFM_PgmEraseErr_IrqHandler();
        }
    }
    /* EFM read collision */
    if (0UL != bM4_EFM->FITE_b.COLERRITE)
    {
        /* EFM read collision */
        u32Tmp1 = M4_EFM->FSR & (EFM_FSR_COLERR0 | EFM_FSR_COLERR1);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_18)))
        {
            EFM_ColErr_IrqHandler();
        }
    }
    /* EFM operate end */
    if (0UL != bM4_EFM->FITE_b.OPTENDITE)
    {
        /* EFM operate end */
        u32Tmp1 = M4_EFM->FSR & (EFM_FSR_OPTEND0 | EFM_FSR_OPTEND1);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_19)))
        {
            EFM_OpEnd_IrqHandler();
        }
    }
    /* QSPI access error */
    u32Tmp1 = M4_QSPI->SR & QSPI_SR_RAER;
    if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_22)))
    {
        QSPI_Err_IrqHandler();
    }
    /*DCU1 */
    u32Tmp1 = M4_DCU1->INTEVTSEL;
    u32Tmp2 = M4_DCU1->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_23)))
    {
        DCU_1_IrqHandler();
    }
    /*DCU2 */
    u32Tmp1 = M4_DCU2->INTEVTSEL;
    u32Tmp2 = M4_DCU2->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_24)))
    {
        DCU_2_IrqHandler();
    }
    /*DCU3 */
    u32Tmp1 = M4_DCU3->INTEVTSEL;
    u32Tmp2 = M4_DCU3->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_25)))
    {
        DCU_3_IrqHandler();
    }
    /*DCU4 */
    u32Tmp1 = M4_DCU4->INTEVTSEL;
    u32Tmp2 = M4_DCU4->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_26)))
    {
        DCU_4_IrqHandler();
    }
    /*DCU5 */
    u32Tmp1 = M4_DCU5->INTEVTSEL;
    u32Tmp2 = M4_DCU5->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_27)))
    {
        DCU_5_IrqHandler();
    }
    /*DCU6 */
    u32Tmp1 = M4_DCU6->INTEVTSEL;
    u32Tmp2 = M4_DCU6->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_28)))
    {
        DCU_6_IrqHandler();
    }
    /*DCU7 */
    u32Tmp1 = M4_DCU7->INTEVTSEL;
    u32Tmp2 = M4_DCU7->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_29)))
    {
        DCU_7_IrqHandler();
    }
    /*DCU8 */
    u32Tmp1 = M4_DCU8->INTEVTSEL;
    u32Tmp2 = M4_DCU8->FLAG;
    if ((0UL != ((u32Tmp1) & (u32Tmp2) & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_30)))
    {
        DCU_8_IrqHandler();
    }
}

/**
 * @brief  Interrupt No.130 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ130_Handler(void)
{
    const uint32_t VSSEL130 = M4_INTC->VSSEL130;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* MAU square */
    if (0UL != (VSSEL130 & BIT_MASK_19))
    {
        MAU_Sqrt_IrqHandler();
    }
    else
    {
        /* DMA2 Ch.0 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL0_b.IE)
        {
            /* DMA2 Ch.0 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC0)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC0) && (0UL != (VSSEL130 & BIT_MASK_00)))
                {
                    DMA_2_Tc0_IrqHandler();
                }
            }
            /* DMA2 ch.0 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC0)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC0) && (0UL != (VSSEL130 & BIT_MASK_08)))
                {
                    DMA_2_Btc0_IrqHandler();
                }
            }
            /* DMA2 ch.0 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_00 | BIT_MASK_16);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_00 | BIT_MASK_16));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err0_IrqHandler();
            }
        }
        /* DMA2 Ch.1 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL1_b.IE)
        {
            /* DMA2 Ch.1 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC1)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC1) && (0UL != (VSSEL130 & BIT_MASK_01)))
                {
                    DMA_2_Tc1_IrqHandler();
                }
            }
            /* DMA2 ch.1 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC1)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC1) && (0UL != (VSSEL130 & BIT_MASK_09)))
                {
                    DMA_2_Btc1_IrqHandler();
                }
            }
            /* DMA2 ch.1 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_01 | BIT_MASK_17);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_01 | BIT_MASK_17));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err1_IrqHandler();
            }
        }
        /* DMA2 Ch.2 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL2_b.IE)
        {
            /* DMA2 Ch.2 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC2)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC2) && (0UL != (VSSEL130 & BIT_MASK_02)))
                {
                    DMA_2_Tc2_IrqHandler();
                }
            }
            /* DMA2 ch.2 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC2)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC2) && (0UL != (VSSEL130 & BIT_MASK_10)))
                {
                    DMA_2_Btc2_IrqHandler();
                }
            }
            /* DMA2 ch.2 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_02 | BIT_MASK_18);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_02 | BIT_MASK_18));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err2_IrqHandler();
            }
        }
        /* DMA2 Ch.3 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL3_b.IE)
        {
            /* DMA2 Ch.3 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC3)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC3) && (0UL != (VSSEL130 & BIT_MASK_03)))
                {
                    DMA_2_Tc3_IrqHandler();
                }
            }
            /* DMA2 ch.3 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC3)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC3) && (0UL != (VSSEL130 & BIT_MASK_11)))
                {
                    DMA_2_Btc3_IrqHandler();
                }
            }
            /* DMA2 ch.3 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_03 | BIT_MASK_19);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_03 | BIT_MASK_19));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err3_IrqHandler();
            }
        }
        /* DMA2 Ch.4 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL4_b.IE)
        {
            /* DMA2 Ch.4 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC4)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC4) && (0UL != (VSSEL130 & BIT_MASK_04)))
                {
                    DMA_2_Tc4_IrqHandler();
                }
            }
            /* DMA2 ch.4 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC4)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC4) && (0UL != (VSSEL130 & BIT_MASK_12)))
                {
                    DMA_2_Btc4_IrqHandler();
                }
            }
            /* DMA2 ch.4 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_04 | BIT_MASK_20);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_04 | BIT_MASK_20));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err4_IrqHandler();
            }
        }
        /* DMA2 Ch.5 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL5_b.IE)
        {
            /* DMA2 Ch.5 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC5)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC5) && (0UL != (VSSEL130 & BIT_MASK_05)))
                {
                    DMA_2_Tc5_IrqHandler();
                }
            }
            /* DMA2 ch.5 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC5)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC5) && (0UL != (VSSEL130 & BIT_MASK_13)))
                {
                    DMA_2_Btc5_IrqHandler();
                }
            }
            /* DMA2 ch.5 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_05 | BIT_MASK_21);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_05 | BIT_MASK_21));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err5_IrqHandler();
            }
        }
        /* DMA2 Ch.6 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL6_b.IE)
        {
            /* DMA2 Ch.6 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC6)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC6) && (0UL != (VSSEL130 & BIT_MASK_06)))
                {
                    DMA_2_Tc6_IrqHandler();
                }
            }
            /* DMA2 ch.6 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC6)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC6) && (0UL != (VSSEL130 & BIT_MASK_14)))
                {
                    DMA_2_Btc6_IrqHandler();
                }
            }
            /* DMA2 ch.6 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_06 | BIT_MASK_22);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_06 | BIT_MASK_22));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err6_IrqHandler();
            }
        }
        /* DMA2 Ch.7 interrupt enabled */
        if (1UL == bM4_DMA2->CHCTL7_b.IE)
        {
            /* DMA2 Ch.7 Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKTC7)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.TC7) && (0UL != (VSSEL130 & BIT_MASK_07)))
                {
                    DMA_2_Tc7_IrqHandler();
                }
            }
            /* DMA2 ch.7 Block Tx completed */
            if (0UL == bM4_DMA2->INTMASK1_b.MSKBTC7)
            {
                if ((1UL == bM4_DMA2->INTSTAT1_b.BTC7) && (0UL != (VSSEL130 & BIT_MASK_15)))
                {
                    DMA_2_Btc7_IrqHandler();
                }
            }
            /* DMA2 ch.7 Transfer/Request Error */
            u32Tmp1 = M4_DMA2->INTSTAT0 & (BIT_MASK_07 | BIT_MASK_22);
            u32Tmp2 = (uint32_t)(~(M4_DMA2->INTMASK0) & (BIT_MASK_07 | BIT_MASK_22));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16)))
            {
                DMA_2_Err7_IrqHandler();
            }
        }
        /* DVP frame start */
        if (1UL == bM4_DVP->IER_b.FSIEN)
        {
            if ((1UL == bM4_DVP->STR_b.FSF) && (0UL != (VSSEL130 & BIT_MASK_20)))
            {
                DVP_FrameStart_IrqHandler();
            }
        }
        /* DVP line start */
        if (1UL == bM4_DVP->IER_b.LSIEN)
        {
            if ((1UL == bM4_DVP->STR_b.LSF) && (0UL != (VSSEL130 & BIT_MASK_21)))
            {
                DVP_LineStart_IrqHandler();
            }
        }
        /* DVP line end */
        if (1UL == bM4_DVP->IER_b.LEIEN)
        {
            if ((1UL == bM4_DVP->STR_b.LEF) && (0UL != (VSSEL130 & BIT_MASK_22)))
            {
                DVP_LineEnd_IrqHandler();
            }
        }
        /* DVP frame end */
        if (1UL == bM4_DVP->IER_b.FEIEN)
        {
            if ((1UL == bM4_DVP->STR_b.FEF) && (0UL != (VSSEL130 & BIT_MASK_23)))
            {
                DVP_FrameEnd_IrqHandler();
            }
        }
        /* DVP software sync err */
        if (1UL == bM4_DVP->IER_b.SQUERIEN)
        {
            if ((1UL == bM4_DVP->STR_b.SQUERF) && (0UL != (VSSEL130 & BIT_MASK_24)))
            {
                DVP_SwSyncErr_IrqHandler();
            }
        }
        /* DVP fifo overfolw err */
        if (1UL == bM4_DVP->IER_b.FIFOERIEN)
        {
            if ((1UL == bM4_DVP->STR_b.FIFOERF) && (0UL != (VSSEL130 & BIT_MASK_25)))
            {
                DVP_FifoErr_IrqHandler();
            }
        }
        /* FMAC 1 */
        if (1UL == bM4_FMAC1->IER_b.INTEN)
        {
            if ((1UL == bM4_FMAC1->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_27)))
            {
                FMAC_1_IrqHandler();
            }
        }
        /* FMAC 2 */
        if (1UL == bM4_FMAC2->IER_b.INTEN)
        {
            if ((1UL == bM4_FMAC2->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_28)))
            {
                FMAC_2_IrqHandler();
            }
        }
        /* FMAC 3 */
        if (1UL == bM4_FMAC3->IER_b.INTEN)
        {
            if ((1UL == bM4_FMAC3->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_29)))
            {
                FMAC_3_IrqHandler();
            }
        }
        /* FMAC 4 */
        if (1UL == bM4_FMAC4->IER_b.INTEN)
        {
            if ((1UL == bM4_FMAC4->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_30)))
            {
                FMAC_4_IrqHandler();
            }
        }
    }
}

/**
 * @brief  Interrupt No.131 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ131_Handler(void)
{
    const uint32_t VSSEL131 = M4_INTC->VSSEL131;
    uint32_t u32Tmp1;

    /* Timer0 unit1, Ch.A compare match */
    if (1UL == bM4_TMR0_1->BCONR_b.INTENA)
    {
        if ((1UL ==bM4_TMR0_1->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_00)))
        {
            TMR0_1_CmpA_IrqHandler();
        }
    }
    /* Timer0 unit1, Ch.B compare match */
    if (1UL == bM4_TMR0_1->BCONR_b.INTENB)
    {
        if ((1UL ==bM4_TMR0_1->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_01)))
        {
            TMR0_1_CmpB_IrqHandler();
        }
    }
    /* Timer0 unit2, Ch.A compare match */
    if (1UL == bM4_TMR0_2->BCONR_b.INTENA)
    {
        if ((1UL ==bM4_TMR0_2->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_02)))
        {
            TMR0_2_CmpA_IrqHandler();
        }
    }
    /* Timer0 unit2, Ch.B compare match */
    if (1UL == bM4_TMR0_2->BCONR_b.INTENB)
    {
        if ((1UL ==bM4_TMR0_2->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_03)))
        {
            TMR0_2_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.A compare match */
    if (1UL == bM4_TMR2_1->ICONR_b.CMENA)
    {
        if ((1UL == bM4_TMR2_1->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_04)))
        {
            TMR2_1_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.B compare match */
    if (1UL == bM4_TMR2_1->ICONR_b.CMENB)
    {
        if ((1UL == bM4_TMR2_1->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_05)))
        {
            TMR2_1_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.A overflow */
    if (1UL == bM4_TMR2_1->ICONR_b.OVENA)
    {
        if ((1UL == bM4_TMR2_1->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_06)))
        {
            TMR2_1_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.B overflow */
    if (1UL == bM4_TMR2_1->ICONR_b.OVENB)
    {
        if ((1UL == bM4_TMR2_1->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_07)))
        {
            TMR2_1_OvfB_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.A compare match */
    if (1UL == bM4_TMR2_2->ICONR_b.CMENA)
    {
        if ((1UL == bM4_TMR2_2->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_08)))
        {
            TMR2_2_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.B compare match */
    if (1UL == bM4_TMR2_2->ICONR_b.CMENB)
    {
        if ((1UL == bM4_TMR2_2->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_09)))
        {
            TMR2_2_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.A overflow */
    if (1UL == bM4_TMR2_2->ICONR_b.OVENA)
    {
        if ((1UL == bM4_TMR2_2->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_10)))
        {
            TMR2_2_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.B overflow */
    if (1UL == bM4_TMR2_2->ICONR_b.OVENB)
    {
        if ((1UL == bM4_TMR2_2->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_11)))
        {
            TMR2_2_OvfB_IrqHandler();
        }
    }
        /* Timer2 unit3, Ch.A compare match */
    if (1UL == bM4_TMR2_3->ICONR_b.CMENA)
    {
        if ((1UL == bM4_TMR2_3->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_12)))
        {
            TMR2_3_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.B compare match */
    if (1UL == bM4_TMR2_3->ICONR_b.CMENB)
    {
        if ((1UL == bM4_TMR2_3->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_13)))
        {
            TMR2_3_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.A overflow */
    if (1UL == bM4_TMR2_3->ICONR_b.OVENA)
    {
        if ((1UL == bM4_TMR2_3->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_14)))
        {
            TMR2_3_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.B overflow */
    if (1UL == bM4_TMR2_3->ICONR_b.OVENB)
    {
        if ((1UL == bM4_TMR2_3->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_15)))
        {
            TMR2_3_OvfB_IrqHandler();
        }
    }
        /* Timer2 unit4, Ch.A compare match */
    if (1UL == bM4_TMR2_4->ICONR_b.CMENA)
    {
        if ((1UL == bM4_TMR2_4->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_16)))
        {
            TMR2_4_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.B compare match */
    if (1UL == bM4_TMR2_4->ICONR_b.CMENB)
    {
        if ((1UL == bM4_TMR2_4->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_17)))
        {
            TMR2_4_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.A overflow */
    if (1UL == bM4_TMR2_4->ICONR_b.OVENA)
    {
        if ((1UL == bM4_TMR2_4->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_18)))
        {
            TMR2_4_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.B overflow */
    if (1UL == bM4_TMR2_4->ICONR_b.OVENB)
    {
        if ((1UL == bM4_TMR2_4->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_19)))
        {
            TMR2_4_OvfB_IrqHandler();
        }
    }
    /* RTC time stamp 0 */
    if (1UL == bM4_RTC->TPCR0_b.TPIE0)
    {
        if ((1UL == bM4_RTC->TPSR_b.TPF0) && (0UL != (VSSEL131 & BIT_MASK_24)))
        {
            RTC_TimeStamp0_IrqHandler();
        }
    }
    /* RTC time stamp 1 */
    if (1UL == bM4_RTC->TPCR1_b.TPIE1)
    {
        if ((1UL == bM4_RTC->TPSR_b.TPF1) && (0UL != (VSSEL131 & BIT_MASK_24)))
        {
            RTC_TimeStamp1_IrqHandler();
        }
    }
    /* RTC alarm */
    if (1UL == bM4_RTC->CR2_b.ALMIE)
    {
        if ((1UL == bM4_RTC->CR2_b.ALMF) && (0UL != (VSSEL131 & BIT_MASK_25)))
        {
            RTC_Alarm_IrqHandler();
        }
    }
    /* RTC period */
    if (1UL == bM4_RTC->CR2_b.PRDIE)
    {
        if ((1UL == bM4_RTC->CR2_b.PRDF) && (0UL != (VSSEL131 & BIT_MASK_26)))
        {
            RTC_Period_IrqHandler();
        }
    }
    /* XTAL stop */
    if (1UL == bM4_CMU->XTALSTDCR_b.XTALSTDIE)
    {
        if ((1UL == bM4_CMU->XTALSTDSR_b.XTALSTDF) && (0UL != (VSSEL131 & BIT_MASK_29)))
        {
            CLK_XtalStop_IrqHandler();
        }
    }
    /* Wakeup timer overflow */
    if (1UL == bM4_PWC->WKTC2_b.WKTCE)
    {
        if ((1UL == bM4_PWC->WKTC2_b.WKOVF) && (0UL != (VSSEL131 & BIT_MASK_30)))
        {
            PWC_WakeupTimer_IrqHandler();
        }
    }
    /* SWDT underflow or refresh error */
    u32Tmp1 = M4_SWDT->SR & (SWDT_SR_UDF | SWDT_SR_REF);
    if ((0UL != u32Tmp1) && (0UL != (VSSEL131 & BIT_MASK_31)))
    {
        SWDT_IrqHandler();
    }
}

/**
 * @brief  Interrupt No.132 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ132_Handler(void)
{
    const uint32_t VSSEL132 = M4_INTC->VSSEL132;

    /* Timer6 Ch.1 general compare match A */
    if (1UL == bM4_TMR6_1->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMAF) && (0UL != (VSSEL132 & BIT_MASK_00)))
        {
            TMR6_1_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.1 general compare match B */
    if (1UL == bM4_TMR6_1->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMBF) && (0UL != (VSSEL132 & BIT_MASK_01)))
        {
            TMR6_1_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.1 general compare match C */
    if (1UL == bM4_TMR6_1->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMCF) && (0UL != (VSSEL132 & BIT_MASK_02)))
        {
            TMR6_1_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.1 general compare match D */
    if (1UL == bM4_TMR6_1->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMDF) && (0UL != (VSSEL132 & BIT_MASK_03)))
        {
            TMR6_1_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.1 general compare match E */
    if (1UL == bM4_TMR6_1->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMEF) && (0UL != (VSSEL132 & BIT_MASK_04)))
        {
            TMR6_1_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.1 general compare match F */
    if (1UL == bM4_TMR6_1->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMFF) && (0UL != (VSSEL132 & BIT_MASK_05)))
        {
            TMR6_1_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.1 overflow*/
    if (1UL == bM4_TMR6_1->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.OVFF) && (0UL != (VSSEL132 & BIT_MASK_06)))
        {
            TMR6_1_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.1 underflow*/
    if (1UL == bM4_TMR6_1->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.UDFF) && (0UL != (VSSEL132 & BIT_MASK_07)))
        {
            TMR6_1_GUdf_IrqHandler();
        }
    }
    /* Timer4 Ch.1 U phase higher compare match */
    if (1UL == bM4_TMR4_1->OCSRU_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_1->OCSRU_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_08)))
        {
            TMR4_1_GCmpUH_IrqHandler();
        }
    }
    /* Timer4 Ch.1 U phase lower compare match */
    if (1UL == bM4_TMR4_1->OCSRU_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_1->OCSRU_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_09)))
        {
            TMR4_1_GCmpUL_IrqHandler();
        }
    }
    /* Timer4 Ch.1 V phase higher compare match */
    if (1UL == bM4_TMR4_1->OCSRV_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_1->OCSRV_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_10)))
        {
            TMR4_1_GCmpVH_IrqHandler();
        }
    }
    /* Timer4 Ch.1 V phase lower compare match */
    if (1UL == bM4_TMR4_1->OCSRV_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_1->OCSRV_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_11)))
        {
            TMR4_1_GCmpVL_IrqHandler();
        }
    }
    /* Timer4 Ch.1 W phase higher compare match */
    if (1UL == bM4_TMR4_1->OCSRW_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_1->OCSRW_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_12)))
        {
            TMR4_1_GCmpWH_IrqHandler();
        }
    }
    /* Timer4 Ch.1 W phase lower compare match */
    if (1UL == bM4_TMR4_1->OCSRW_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_1->OCSRW_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_13)))
        {
            TMR4_1_GCmpWL_IrqHandler();
        }
    }
    /* Timer4 Ch.1 overflow */
    if (1UL == bM4_TMR4_1->CCSR_b.IRQPEN)
    {
        if ((1UL == bM4_TMR4_1->CCSR_b.IRQPF) && (0UL != (VSSEL132 & BIT_MASK_14)))
        {
            TMR4_1_Ovf_IrqHandler();
        }
    }
    /* Timer4 Ch.1 underflow */
    if (1UL == bM4_TMR4_1->CCSR_b.IRQZEN)
    {
        if ((1UL == bM4_TMR4_1->CCSR_b.IRQZF) && (0UL != (VSSEL132 & BIT_MASK_15)))
        {
            TMR4_1_Udf_IrqHandler();
        }
    }
    /* Timer6 Ch.2 general compare match A */
    if (1UL == bM4_TMR6_2->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMAF) && (0UL != (VSSEL132 & BIT_MASK_16)))
        {
            TMR6_2_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.2 general compare match B */
    if (1UL == bM4_TMR6_2->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMBF) && (0UL != (VSSEL132 & BIT_MASK_17)))
        {
            TMR6_2_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.2 general compare match C */
    if (1UL == bM4_TMR6_2->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMCF) && (0UL != (VSSEL132 & BIT_MASK_18)))
        {
            TMR6_2_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.2 general compare match D */
    if (1UL == bM4_TMR6_2->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMDF) && (0UL != (VSSEL132 & BIT_MASK_19)))
        {
            TMR6_2_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.2 general compare match E */
    if (1UL == bM4_TMR6_2->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMEF) && (0UL != (VSSEL132 & BIT_MASK_20)))
        {
            TMR6_2_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.2 general compare match F */
    if (1UL == bM4_TMR6_2->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMFF) && (0UL != (VSSEL132 & BIT_MASK_21)))
        {
            TMR6_2_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.2 overflow*/
    if (1UL == bM4_TMR6_2->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.OVFF) && (0UL != (VSSEL132 & BIT_MASK_22)))
        {
            TMR6_2_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.2 underflow*/
    if (1UL == bM4_TMR6_2->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.UDFF) && (0UL != (VSSEL132 & BIT_MASK_23)))
        {
            TMR6_2_GUdf_IrqHandler();
        }
    }
    /* Timer4 Ch.2 U phase higher compare match */
    if (1UL == bM4_TMR4_2->OCSRU_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_2->OCSRU_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_24)))
        {
            TMR4_2_GCmpUH_IrqHandler();
        }
    }
    /* Timer4 Ch.2 U phase lower compare match */
    if (1UL == bM4_TMR4_2->OCSRU_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_2->OCSRU_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_25)))
        {
            TMR4_2_GCmpUL_IrqHandler();
        }
    }
    /* Timer4 Ch.2 V phase higher compare match */
    if (1UL == bM4_TMR4_2->OCSRV_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_2->OCSRV_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_26)))
        {
            TMR4_2_GCmpVH_IrqHandler();
        }
    }
    /* Timer4 Ch.2 V phase lower compare match */
    if (1UL == bM4_TMR4_2->OCSRV_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_2->OCSRV_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_27)))
        {
            TMR4_2_GCmpVL_IrqHandler();
        }
    }
    /* Timer4 Ch.2 W phase higher compare match */
    if (1UL == bM4_TMR4_2->OCSRW_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_2->OCSRW_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_28)))
        {
            TMR4_2_GCmpWH_IrqHandler();
        }
    }
    /* Timer4 Ch.2 W phase lower compare match */
    if (1UL == bM4_TMR4_2->OCSRW_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_2->OCSRW_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_29)))
        {
            TMR4_2_GCmpWL_IrqHandler();
        }
    }
    /* Timer4 Ch.2 overflow */
    if (1UL == bM4_TMR4_2->CCSR_b.IRQPEN)
    {
        if ((1UL == bM4_TMR4_2->CCSR_b.IRQPF) && (0UL != (VSSEL132 & BIT_MASK_30)))
        {
            TMR4_2_Ovf_IrqHandler();
        }
    }
    /* Timer4 Ch.2 underflow */
    if (1UL == bM4_TMR4_2->CCSR_b.IRQZEN)
    {
        if ((1UL == bM4_TMR4_2->CCSR_b.IRQZF) && (0UL != (VSSEL132 & BIT_MASK_31)))
        {
            TMR4_2_Udf_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.133 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ133_Handler(void)
{
    const uint32_t VSSEL133 = M4_INTC->VSSEL133;

    /* Timer6 Ch.3 general compare match A */
    if (1UL == bM4_TMR6_3->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMAF) && (0UL != (VSSEL133 & BIT_MASK_00)))
        {
            TMR6_3_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.3 general compare match B */
    if (1UL == bM4_TMR6_3->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMBF) && (0UL != (VSSEL133 & BIT_MASK_01)))
        {
            TMR6_3_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.3 general compare match C */
    if (1UL == bM4_TMR6_3->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMCF) && (0UL != (VSSEL133 & BIT_MASK_02)))
        {
            TMR6_3_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.3 general compare match D */
    if (1UL == bM4_TMR6_3->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMDF) && (0UL != (VSSEL133 & BIT_MASK_03)))
        {
            TMR6_3_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.3 general compare match E */
    if (1UL == bM4_TMR6_3->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMEF) && (0UL != (VSSEL133 & BIT_MASK_04)))
        {
            TMR6_3_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.3 general compare match F */
    if (1UL == bM4_TMR6_3->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMFF) && (0UL != (VSSEL133 & BIT_MASK_05)))
        {
            TMR6_3_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.3 overflow*/
    if (1UL == bM4_TMR6_3->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.OVFF) && (0UL != (VSSEL133 & BIT_MASK_06)))
        {
            TMR6_3_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.3 underflow*/
    if (1UL == bM4_TMR6_3->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.UDFF) && (0UL != (VSSEL133 & BIT_MASK_07)))
        {
            TMR6_3_GUdf_IrqHandler();
        }
    }
    /* Timer4 Ch.3 U phase higher compare match */
    if (1UL == bM4_TMR4_3->OCSRU_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_3->OCSRU_b.OCFH) && (0UL != (VSSEL133 & BIT_MASK_08)))
        {
            TMR4_3_GCmpUH_IrqHandler();
        }
    }
    /* Timer4 Ch.3 U phase lower compare match */
    if (1UL == bM4_TMR4_3->OCSRU_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_3->OCSRU_b.OCFL) && (0UL != (VSSEL133 & BIT_MASK_09)))
        {
            TMR4_3_GCmpUL_IrqHandler();
        }
    }
    /* Timer4 Ch.3 V phase higher compare match */
    if (1UL == bM4_TMR4_3->OCSRV_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_3->OCSRV_b.OCFH) && (0UL != (VSSEL133 & BIT_MASK_10)))
        {
            TMR4_3_GCmpVH_IrqHandler();
        }
    }
    /* Timer4 Ch.3 V phase lower compare match */
    if (1UL == bM4_TMR4_3->OCSRV_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_3->OCSRV_b.OCFL) && (0UL != (VSSEL133 & BIT_MASK_11)))
        {
            TMR4_3_GCmpVL_IrqHandler();
        }
    }
    /* Timer4 Ch.3 W phase higher compare match */
    if (1UL == bM4_TMR4_3->OCSRW_b.OCIEH)
    {
        if ((1UL == bM4_TMR4_3->OCSRW_b.OCFH) && (0UL != (VSSEL133 & BIT_MASK_12)))
        {
            TMR4_3_GCmpWH_IrqHandler();
        }
    }
    /* Timer4 Ch.3 W phase lower compare match */
    if (1UL == bM4_TMR4_3->OCSRW_b.OCIEL)
    {
        if ((1UL == bM4_TMR4_3->OCSRW_b.OCFL) && (0UL != (VSSEL133 & BIT_MASK_13)))
        {
            TMR4_3_GCmpWL_IrqHandler();
        }
    }
    /* Timer4 Ch.3 overflow */
    if (1UL == bM4_TMR4_3->CCSR_b.IRQPEN)
    {
        if ((1UL == bM4_TMR4_3->CCSR_b.IRQPF) && (0UL != (VSSEL133 & BIT_MASK_14)))
        {
            TMR4_3_Ovf_IrqHandler();
        }
    }
    /* Timer4 Ch.3 underflow */
    if (1UL == bM4_TMR4_3->CCSR_b.IRQZEN)
    {
        if ((1UL == bM4_TMR4_3->CCSR_b.IRQZF) && (0UL != (VSSEL133 & BIT_MASK_15)))
        {
            TMR4_3_Udf_IrqHandler();
        }
    }
    /* Timer6 Ch.1 dead time */
    if (1UL == bM4_TMR6_1->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.DTEF) && (0UL != (VSSEL133 & BIT_MASK_16)))
        {
            TMR6_1_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.1 specified up compare match A*/
    if (1UL == bM4_TMR6_1->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMSAUF) && (0UL != (VSSEL133 & BIT_MASK_19)))
        {
            TMR6_1_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.1 specified down compare match A*/
    if (1UL == bM4_TMR6_1->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMSADF) && (0UL != (VSSEL133 & BIT_MASK_19)))
        {
            TMR6_1_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.1 specified up compare match B*/
    if (1UL == bM4_TMR6_1->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMSBUF) && (0UL != (VSSEL133 & BIT_MASK_20)))
        {
            TMR6_1_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.1 specified down compare match B*/
    if (1UL == bM4_TMR6_1->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_1->STFLR_b.CMSBDF) && (0UL != (VSSEL133 & BIT_MASK_20)))
        {
            TMR6_1_SCmpDownB_IrqHandler();
        }
    }
    /* Timer4 Ch.1 U phase reload */
    if (0UL == bM4_TMR4_1->RCSR_b.RTIDU)
    {
        if ((1UL == bM4_TMR4_1->RCSR_b.RTIFU) && (0UL != (VSSEL133 & BIT_MASK_21)))
        {
            TMR4_1_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Ch.1 V phase reload */
    if (0UL == bM4_TMR4_1->RCSR_b.RTIDV)
    {
        if ((1UL == bM4_TMR4_1->RCSR_b.RTIFV) && (0UL != (VSSEL133 & BIT_MASK_22)))
        {
            TMR4_1_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Ch.1 W phase reload */
    if (0UL == bM4_TMR4_1->RCSR_b.RTIDW)
    {
        if ((1UL == bM4_TMR4_1->RCSR_b.RTIFW) && (0UL != (VSSEL133 & BIT_MASK_23)))
        {
            TMR4_1_ReloadU_IrqHandler();
        }
    }
    /* Timer6 Ch.2 dead time */
    if (1UL == bM4_TMR6_2->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.DTEF) && (0UL != (VSSEL133 & BIT_MASK_24)))
        {
            TMR6_2_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.2 specified up compare match A*/
    if (1UL == bM4_TMR6_2->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMSAUF) && (0UL != (VSSEL133 & BIT_MASK_27)))
        {
            TMR6_2_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.2 specified down compare match A*/
    if (1UL == bM4_TMR6_2->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMSADF) && (0UL != (VSSEL133 & BIT_MASK_27)))
        {
            TMR6_2_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.2 specified up compare match B*/
    if (1UL == bM4_TMR6_2->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMSBUF) && (0UL != (VSSEL133 & BIT_MASK_28)))
        {
            TMR6_2_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.2 specified down compare match B*/
    if (1UL == bM4_TMR6_2->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_2->STFLR_b.CMSBDF) && (0UL != (VSSEL133 & BIT_MASK_28)))
        {
            TMR6_2_SCmpDownB_IrqHandler();
        }
    }
    /* Timer4 Ch.2 U phase reload */
    if (0UL == bM4_TMR4_2->RCSR_b.RTIDU)
    {
        if ((1UL == bM4_TMR4_2->RCSR_b.RTIFU) && (0UL != (VSSEL133 & BIT_MASK_29)))
        {
            TMR4_2_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Ch.2 V phase reload */
    if (0UL == bM4_TMR4_2->RCSR_b.RTIDV)
    {
        if ((1UL == bM4_TMR4_2->RCSR_b.RTIFV) && (0UL != (VSSEL133 & BIT_MASK_30)))
        {
            TMR4_2_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Ch.2 W phase reload */
    if (0UL == bM4_TMR4_2->RCSR_b.RTIDW)
    {
        if ((1UL == bM4_TMR4_2->RCSR_b.RTIFW) && (0UL != (VSSEL133 & BIT_MASK_31)))
        {
            TMR4_2_ReloadU_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.134 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ134_Handler(void)
{
    const uint32_t VSSEL134 = M4_INTC->VSSEL134;

    /* Timer6 Ch.3 dead time */
    if (1UL == bM4_TMR6_3->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.DTEF) && (0UL != (VSSEL134 & BIT_MASK_00)))
        {
            TMR6_3_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.3 specified up compare match A*/
    if (1UL == bM4_TMR6_3->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMSAUF) && (0UL != (VSSEL134 & BIT_MASK_03)))
        {
            TMR6_3_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.3 specified down compare match A*/
    if (1UL == bM4_TMR6_3->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMSADF) && (0UL != (VSSEL134 & BIT_MASK_03)))
        {
            TMR6_3_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.3 specified up compare match B*/
    if (1UL == bM4_TMR6_3->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMSBUF) && (0UL != (VSSEL134 & BIT_MASK_04)))
        {
            TMR6_3_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.3 specified down compare match B*/
    if (1UL == bM4_TMR6_3->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_3->STFLR_b.CMSBDF) && (0UL != (VSSEL134 & BIT_MASK_04)))
        {
            TMR6_3_SCmpDownB_IrqHandler();
        }
    }
    /* Timer4 Ch.3 U phase reload */
    if (0UL == bM4_TMR4_3->RCSR_b.RTIDU)
    {
        if ((1UL == bM4_TMR4_3->RCSR_b.RTIFU) && (0UL != (VSSEL134 & BIT_MASK_05)))
        {
            TMR4_3_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Ch.3 V phase reload */
    if (0UL == bM4_TMR4_3->RCSR_b.RTIDV)
    {
        if ((1UL == bM4_TMR4_3->RCSR_b.RTIFV) && (0UL != (VSSEL134 & BIT_MASK_06)))
        {
            TMR4_3_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Ch.3 W phase reload */
    if (0UL == bM4_TMR4_3->RCSR_b.RTIDW)
    {
        if ((1UL == bM4_TMR4_3->RCSR_b.RTIFW) && (0UL != (VSSEL134 & BIT_MASK_07)))
        {
            TMR4_3_ReloadU_IrqHandler();
        }
    }
    /* Timer6 Ch.4 general compare match A */
    if (1UL == bM4_TMR6_4->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMAF) && (0UL != (VSSEL134 & BIT_MASK_16)))
        {
            TMR6_4_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.4 general compare match B */
    if (1UL == bM4_TMR6_4->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMBF) && (0UL != (VSSEL134 & BIT_MASK_17)))
        {
            TMR6_4_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.4 general compare match C */
    if (1UL == bM4_TMR6_4->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMCF) && (0UL != (VSSEL134 & BIT_MASK_18)))
        {
            TMR6_4_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.4 general compare match D */
    if (1UL == bM4_TMR6_4->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMDF) && (0UL != (VSSEL134 & BIT_MASK_19)))
        {
            TMR6_4_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.4 general compare match E */
    if (1UL == bM4_TMR6_4->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMEF) && (0UL != (VSSEL134 & BIT_MASK_20)))
        {
            TMR6_4_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.4 general compare match F */
    if (1UL == bM4_TMR6_4->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMFF) && (0UL != (VSSEL134 & BIT_MASK_21)))
        {
            TMR6_4_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.4 overflow*/
    if (1UL == bM4_TMR6_4->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.OVFF) && (0UL != (VSSEL134 & BIT_MASK_22)))
        {
            TMR6_4_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.4 underflow*/
    if (1UL == bM4_TMR6_4->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.UDFF) && (0UL != (VSSEL134 & BIT_MASK_23)))
        {
            TMR6_4_GUdf_IrqHandler();
        }
    }
    /* Timer6 Ch.4 dead time */
    if (1UL == bM4_TMR6_4->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.DTEF) && (0UL != (VSSEL134 & BIT_MASK_24)))
        {
            TMR6_4_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.4 specified up compare match A*/
    if (1UL == bM4_TMR6_4->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMSAUF) && (0UL != (VSSEL134 & BIT_MASK_27)))
        {
            TMR6_4_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.4 specified down compare match A*/
    if (1UL == bM4_TMR6_4->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMSADF) && (0UL != (VSSEL134 & BIT_MASK_27)))
        {
            TMR6_4_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.4 specified up compare match B*/
    if (1UL == bM4_TMR6_4->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMSBUF) && (0UL != (VSSEL134 & BIT_MASK_28)))
        {
            TMR6_4_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.4 specified down compare match B*/
    if (1UL == bM4_TMR6_4->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_4->STFLR_b.CMSBDF) && (0UL != (VSSEL134 & BIT_MASK_28)))
        {
            TMR6_4_SCmpDownB_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.135 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ135_Handler(void)
{
    const uint32_t VSSEL135 = M4_INTC->VSSEL135;

    /* Timer6 Ch.5 general compare match A */
    if (1UL == bM4_TMR6_5->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMAF) && (0UL != (VSSEL135 & BIT_MASK_00)))
        {
            TMR6_5_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.5 general compare match B */
    if (1UL == bM4_TMR6_5->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMBF) && (0UL != (VSSEL135 & BIT_MASK_01)))
        {
            TMR6_5_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.5 general compare match C */
    if (1UL == bM4_TMR6_5->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMCF) && (0UL != (VSSEL135 & BIT_MASK_02)))
        {
            TMR6_5_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.5 general compare match D */
    if (1UL == bM4_TMR6_5->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMDF) && (0UL != (VSSEL135 & BIT_MASK_03)))
        {
            TMR6_5_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.5 general compare match E */
    if (1UL == bM4_TMR6_5->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMEF) && (0UL != (VSSEL135 & BIT_MASK_04)))
        {
            TMR6_5_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.5 general compare match F */
    if (1UL == bM4_TMR6_5->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMFF) && (0UL != (VSSEL135 & BIT_MASK_05)))
        {
            TMR6_5_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.5 overflow*/
    if (1UL == bM4_TMR6_5->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_06)))
        {
            TMR6_5_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.5 underflow*/
    if (1UL == bM4_TMR6_5->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_07)))
        {
            TMR6_5_GUdf_IrqHandler();
        }
    }
    /* Timer6 Ch.5 dead time */
    if (1UL == bM4_TMR6_5->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.DTEF) && (0UL != (VSSEL135 & BIT_MASK_08)))
        {
            TMR6_5_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.5 specified up compare match A*/
    if (1UL == bM4_TMR6_5->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMSAUF) && (0UL != (VSSEL135 & BIT_MASK_11)))
        {
            TMR6_5_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.5 specified down compare match A*/
    if (1UL == bM4_TMR6_5->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMSADF) && (0UL != (VSSEL135 & BIT_MASK_11)))
        {
            TMR6_5_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.5 specified up compare match B*/
    if (1UL == bM4_TMR6_5->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMSBUF) && (0UL != (VSSEL135 & BIT_MASK_12)))
        {
            TMR6_5_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.5 specified down compare match B*/
    if (1UL == bM4_TMR6_5->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_5->STFLR_b.CMSBDF) && (0UL != (VSSEL135 & BIT_MASK_12)))
        {
            TMR6_5_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Ch.1 overflow */
    if (1UL == bM4_TMRA_1->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_1->BCSTR_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_13)))
        {
            TMRA_1_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.1 underflow */
    if (1UL == bM4_TMRA_1->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_1->BCSTR_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_14)))
        {
            TMRA_1_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.1 compare match 1 */
    if (1UL == bM4_TMRA_1->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_1->STFLR_b.CMPF1) && (0UL != (VSSEL135 & BIT_MASK_15)))
        {
            TMRA_1_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.1 compare match 2 */
    if (1UL == bM4_TMRA_1->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_1->STFLR_b.CMPF2) && (0UL != (VSSEL135 & BIT_MASK_15)))
        {
            TMRA_1_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.1 compare match 3 */
    if (1UL == bM4_TMRA_1->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_1->STFLR_b.CMPF3) && (0UL != (VSSEL135 & BIT_MASK_15)))
        {
            TMRA_1_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.1 compare match 4 */
    if (1UL == bM4_TMRA_1->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_1->STFLR_b.CMPF4) && (0UL != (VSSEL135 & BIT_MASK_15)))
        {
            TMRA_1_Cmp4_IrqHandler();
        }
    }
    /* Timer6 Ch.6 general compare match A */
    if (1UL == bM4_TMR6_6->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMAF) && (0UL != (VSSEL135 & BIT_MASK_16)))
        {
            TMR6_6_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.6 general compare match B */
    if (1UL == bM4_TMR6_6->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMBF) && (0UL != (VSSEL135 & BIT_MASK_17)))
        {
            TMR6_6_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.6 general compare match C */
    if (1UL == bM4_TMR6_6->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMCF) && (0UL != (VSSEL135 & BIT_MASK_18)))
        {
            TMR6_6_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.6 general compare match D */
    if (1UL == bM4_TMR6_6->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMDF) && (0UL != (VSSEL135 & BIT_MASK_19)))
        {
            TMR6_6_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.6 general compare match E */
    if (1UL == bM4_TMR6_6->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMEF) && (0UL != (VSSEL135 & BIT_MASK_20)))
        {
            TMR6_6_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.6 general compare match F */
    if (1UL == bM4_TMR6_6->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMFF) && (0UL != (VSSEL135 & BIT_MASK_21)))
        {
            TMR6_6_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.6 overflow*/
    if (1UL == bM4_TMR6_6->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_22)))
        {
            TMR6_6_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.6 underflow*/
    if (1UL == bM4_TMR6_6->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_23)))
        {
            TMR6_6_GUdf_IrqHandler();
        }
    }
    /* Timer6 Ch.6 dead time */
    if (1UL == bM4_TMR6_6->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.DTEF) && (0UL != (VSSEL135 & BIT_MASK_24)))
        {
            TMR6_6_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.6 specified up compare match A*/
    if (1UL == bM4_TMR6_6->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMSAUF) && (0UL != (VSSEL135 & BIT_MASK_27)))
        {
            TMR6_6_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.6 specified down compare match A*/
    if (1UL == bM4_TMR6_6->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMSADF) && (0UL != (VSSEL135 & BIT_MASK_27)))
        {
            TMR6_6_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.6 specified up compare match B*/
    if (1UL == bM4_TMR6_6->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMSBUF) && (0UL != (VSSEL135 & BIT_MASK_28)))
        {
            TMR6_6_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.6 specified down compare match B*/
    if (1UL == bM4_TMR6_6->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_6->STFLR_b.CMSBDF) && (0UL != (VSSEL135 & BIT_MASK_28)))
        {
            TMR6_6_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Ch.2 overflow */
    if (1UL == bM4_TMRA_2->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_2->BCSTR_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_29)))
        {
            TMRA_2_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.2 underflow */
    if (1UL == bM4_TMRA_2->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_2->BCSTR_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_30)))
        {
            TMRA_2_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.2 compare match 1 */
    if (1UL == bM4_TMRA_2->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_2->STFLR_b.CMPF1) && (0UL != (VSSEL135 & BIT_MASK_31)))
        {
            TMRA_2_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.2 compare match 2 */
    if (1UL == bM4_TMRA_2->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_2->STFLR_b.CMPF2) && (0UL != (VSSEL135 & BIT_MASK_31)))
        {
            TMRA_2_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.2 compare match 3 */
    if (1UL == bM4_TMRA_2->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_2->STFLR_b.CMPF3) && (0UL != (VSSEL135 & BIT_MASK_31)))
        {
            TMRA_2_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.2 compare match 4 */
    if (1UL == bM4_TMRA_2->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_2->STFLR_b.CMPF4) && (0UL != (VSSEL135 & BIT_MASK_31)))
        {
            TMRA_2_Cmp4_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.136 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ136_Handler(void)
{
    const uint32_t VSSEL136 = M4_INTC->VSSEL136;

    /* Timer6 Ch.7 general compare match A */
    if (1UL == bM4_TMR6_7->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMAF) && (0UL != (VSSEL136 & BIT_MASK_00)))
        {
            TMR6_7_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.7 general compare match B */
    if (1UL == bM4_TMR6_7->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMBF) && (0UL != (VSSEL136 & BIT_MASK_01)))
        {
            TMR6_7_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.7 general compare match C */
    if (1UL == bM4_TMR6_7->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMCF) && (0UL != (VSSEL136 & BIT_MASK_02)))
        {
            TMR6_7_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.7 general compare match D */
    if (1UL == bM4_TMR6_7->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMDF) && (0UL != (VSSEL136 & BIT_MASK_03)))
        {
            TMR6_7_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.7 general compare match E */
    if (1UL == bM4_TMR6_7->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMEF) && (0UL != (VSSEL136 & BIT_MASK_04)))
        {
            TMR6_7_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.7 general compare match F */
    if (1UL == bM4_TMR6_7->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMFF) && (0UL != (VSSEL136 & BIT_MASK_05)))
        {
            TMR6_7_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.7 overflow*/
    if (1UL == bM4_TMR6_7->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_06)))
        {
            TMR6_7_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.7 underflow*/
    if (1UL == bM4_TMR6_7->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_07)))
        {
            TMR6_7_GUdf_IrqHandler();
        }
    }
    /* Timer6 Ch.7 dead time */
    if (1UL == bM4_TMR6_7->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.DTEF) && (0UL != (VSSEL136 & BIT_MASK_08)))
        {
            TMR6_7_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.7 specified up compare match A*/
    if (1UL == bM4_TMR6_7->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMSAUF) && (0UL != (VSSEL136 & BIT_MASK_11)))
        {
            TMR6_7_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.7 specified down compare match A*/
    if (1UL == bM4_TMR6_7->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMSADF) && (0UL != (VSSEL136 & BIT_MASK_11)))
        {
            TMR6_7_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.7 specified up compare match B*/
    if (1UL == bM4_TMR6_7->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMSBUF) && (0UL != (VSSEL136 & BIT_MASK_12)))
        {
            TMR6_7_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.7 specified down compare match B*/
    if (1UL == bM4_TMR6_7->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_7->STFLR_b.CMSBDF) && (0UL != (VSSEL136 & BIT_MASK_12)))
        {
            TMR6_7_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Ch.3 overflow */
    if (1UL == bM4_TMRA_3->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_3->BCSTR_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_13)))
        {
            TMRA_3_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.3 underflow */
    if (1UL == bM4_TMRA_3->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_3->BCSTR_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_14)))
        {
            TMRA_3_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.3 compare match 1 */
    if (1UL == bM4_TMRA_3->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_3->STFLR_b.CMPF1) && (0UL != (VSSEL136 & BIT_MASK_15)))
        {
            TMRA_3_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.3 compare match 2 */
    if (1UL == bM4_TMRA_3->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_3->STFLR_b.CMPF2) && (0UL != (VSSEL136 & BIT_MASK_15)))
        {
            TMRA_3_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.3 compare match 3 */
    if (1UL == bM4_TMRA_3->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_3->STFLR_b.CMPF3) && (0UL != (VSSEL136 & BIT_MASK_15)))
        {
            TMRA_3_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.3 compare match 4 */
    if (1UL == bM4_TMRA_3->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_3->STFLR_b.CMPF4) && (0UL != (VSSEL136 & BIT_MASK_15)))
        {
            TMRA_3_Cmp4_IrqHandler();
        }
    }
    /* Timer6 Ch.8 general compare match A */
    if (1UL == bM4_TMR6_8->ICONR_b.INTENA)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMAF) && (0UL != (VSSEL136 & BIT_MASK_16)))
        {
            TMR6_8_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Ch.8 general compare match B */
    if (1UL == bM4_TMR6_8->ICONR_b.INTENB)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMBF) && (0UL != (VSSEL136 & BIT_MASK_17)))
        {
            TMR6_8_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Ch.8 general compare match C */
    if (1UL == bM4_TMR6_8->ICONR_b.INTENC)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMCF) && (0UL != (VSSEL136 & BIT_MASK_18)))
        {
            TMR6_8_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Ch.8 general compare match D */
    if (1UL == bM4_TMR6_8->ICONR_b.INTEND)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMDF) && (0UL != (VSSEL136 & BIT_MASK_19)))
        {
            TMR6_8_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Ch.8 general compare match E */
    if (1UL == bM4_TMR6_8->ICONR_b.INTENE)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMEF) && (0UL != (VSSEL136 & BIT_MASK_20)))
        {
            TMR6_8_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Ch.8 general compare match F */
    if (1UL == bM4_TMR6_8->ICONR_b.INTENF)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMFF) && (0UL != (VSSEL136 & BIT_MASK_21)))
        {
            TMR6_8_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Ch.8 overflow*/
    if (1UL == bM4_TMR6_8->ICONR_b.INTENOVF)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_22)))
        {
            TMR6_8_GOvf_IrqHandler();
        }
    }
    /* Timer6 Ch.8 underflow*/
    if (1UL == bM4_TMR6_8->ICONR_b.INTENUDF)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_23)))
        {
            TMR6_8_GUdf_IrqHandler();
        }
    }
    /* Timer6 Ch.8 dead time */
    if (1UL == bM4_TMR6_8->ICONR_b.INTENDTE)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.DTEF) && (0UL != (VSSEL136 & BIT_MASK_24)))
        {
            TMR6_8_Gdte_IrqHandler();
        }
    }
    /* Timer6 Ch.8 specified up compare match A*/
    if (1UL == bM4_TMR6_8->ICONR_b.INTENSAU)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMSAUF) && (0UL != (VSSEL136 & BIT_MASK_27)))
        {
            TMR6_8_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Ch.8 specified down compare match A*/
    if (1UL == bM4_TMR6_8->ICONR_b.INTENSAD)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMSADF) && (0UL != (VSSEL136 & BIT_MASK_27)))
        {
            TMR6_8_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Ch.8 specified up compare match B*/
    if (1UL == bM4_TMR6_8->ICONR_b.INTENSBU)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMSBUF) && (0UL != (VSSEL136 & BIT_MASK_28)))
        {
            TMR6_8_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Ch.8 specified down compare match B*/
    if (1UL == bM4_TMR6_8->ICONR_b.INTENSBD)
    {
        if ((1UL == bM4_TMR6_8->STFLR_b.CMSBDF) && (0UL != (VSSEL136 & BIT_MASK_28)))
        {
            TMR6_8_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Ch.4 overflow */
    if (1UL == bM4_TMRA_4->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_4->BCSTR_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_29)))
        {
            TMRA_4_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.4 underflow */
    if (1UL == bM4_TMRA_4->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_4->BCSTR_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_30)))
        {
            TMRA_4_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.4 compare match 1 */
    if (1UL == bM4_TMRA_4->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_4->STFLR_b.CMPF1) && (0UL != (VSSEL136 & BIT_MASK_31)))
        {
            TMRA_4_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.4 compare match 2 */
    if (1UL == bM4_TMRA_4->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_4->STFLR_b.CMPF2) && (0UL != (VSSEL136 & BIT_MASK_31)))
        {
            TMRA_4_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.4 compare match 3 */
    if (1UL == bM4_TMRA_4->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_4->STFLR_b.CMPF3) && (0UL != (VSSEL136 & BIT_MASK_31)))
        {
            TMRA_4_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.4 compare match 4 */
    if (1UL == bM4_TMRA_4->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_4->STFLR_b.CMPF4) && (0UL != (VSSEL136 & BIT_MASK_31)))
        {
            TMRA_4_Cmp4_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.137 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ137_Handler(void)
{
    const uint32_t VSSEL137 = M4_INTC->VSSEL137;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* EMB0 */
    u32Tmp1 = M4_EMB0->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB0->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_00)))
    {
        EMB_GR0_IrqHandler();
    }
    /* EMB1 */
    u32Tmp1 = M4_EMB1->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB1->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_01)))
    {
        EMB_GR1_IrqHandler();
    }
    /* EMB2 */
    u32Tmp1 = M4_EMB2->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB2->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_02)))
    {
        EMB_GR2_IrqHandler();
    }
    /* EMB3 */
    u32Tmp1 = M4_EMB3->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB3->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_03)))
    {
        EMB_GR3_IrqHandler();
    }
    /* EMB4 */
    u32Tmp1 = M4_EMB4->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB4->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_04)))
    {
        EMB_GR4_IrqHandler();
    }
    /* EMB5 */
    u32Tmp1 = M4_EMB5->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB5->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_05)))
    {
        EMB_GR5_IrqHandler();
    }
    /* EMB6 */
    u32Tmp1 = M4_EMB6->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = M4_EMB6->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_06)))
    {
        EMB_GR6_IrqHandler();
    }
    /* USB HS EP1 out */

    /* USB HS EP1 in */

    /* USB HS global */

    /* USB HS wakeup */

    if (1UL == bM4_USART1->CR1_b.RIE)
    {
        /* USART Ch.1 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART1->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_12)))
        {
            USART_1_RxErr_IrqHandler();
        }
        /* USART Ch.1 Rx end */
        if ((1UL == bM4_USART1->SR_b.RXNE) && (0UL != (VSSEL137 & BIT_MASK_13)))
        {
            USART_1_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.1 Tx buffer empty */
    if (1UL == bM4_USART1->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART1->SR_b.TXE) && (0UL != (VSSEL137 & BIT_MASK_14)))
        {
            USART_1_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.1 Tx end */
    if (1UL == bM4_USART1->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART1->SR_b.TC) && (0UL != (VSSEL137 & BIT_MASK_15)))
        {
            USART_1_TxEnd_IrqHandler();
        }
    }
    /* USART Ch.1 Tx timeout */
    if (1UL == bM4_USART1->CR1_b.RTOIE)
    {
        if ((1UL == bM4_USART1->SR_b.RTOF) && (0UL != (VSSEL137 & BIT_MASK_16)))
        {
            USART_1_RxTO_IrqHandler();
        }
    }
    if (1UL == bM4_USART2->CR1_b.RIE)
    {
        /* USART Ch.2 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART2->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_17)))
        {
            USART_2_RxErr_IrqHandler();
        }
        /* USART Ch.2 Rx end */
        if ((1UL == bM4_USART2->SR_b.RXNE) && (0UL != (VSSEL137 & BIT_MASK_18)))
        {
            USART_2_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.2 Tx buffer empty */
    if (1UL == bM4_USART2->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART2->SR_b.TXE) && (0UL != (VSSEL137 & BIT_MASK_19)))
        {
            USART_2_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.2 Tx end */
    if (1UL == bM4_USART2->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART2->SR_b.TC) && (0UL != (VSSEL137 & BIT_MASK_20)))
        {
            USART_2_TxEnd_IrqHandler();
        }
    }
    /* USART Ch.2 Tx timeout */
    if (1UL == bM4_USART2->CR1_b.RTOIE)
    {
        if ((1UL == bM4_USART2->SR_b.RTOF) && (0UL != (VSSEL137 & BIT_MASK_21)))
        {
            USART_2_RxTO_IrqHandler();
        }
    }
    /* SPI Ch.1 Rx end */
    if (1UL == bM4_SPI1->CR1_b.RXIE)
    {
        if ((1UL == bM4_SPI1->SR_b.RDFF) && (0UL != (VSSEL137 & BIT_MASK_22)))
        {
            SPI_1_RxEnd_IrqHandler();
        }
    }
    /* SPI Ch.1 Tx buffer empty */
    if (1UL == bM4_SPI1->CR1_b.TXIE)
    {
        if ((1UL == bM4_SPI1->SR_b.TDEF) && (0UL != (VSSEL137 & BIT_MASK_23)))
        {
            SPI_1_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.1 Bus idle */
    if (1UL == bM4_SPI1->CR1_b.IDIE)
    {
        if ((0UL == bM4_SPI1->SR_b.IDLNF) && (0UL != (VSSEL137 & BIT_MASK_24)))
        {
            SPI_1_Idle_IrqHandler();
        }
    }
    /* SPI Ch.1 parity/overflow/underflow/mode error */
    if (1UL == bM4_SPI1->CR1_b.EIE)
    {
        u32Tmp1 = M4_SPI1->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_25)))
        {
            SPI_1_Err_IrqHandler();
        }
    }
    /* SPI Ch.2 Rx end */
    if (1UL == bM4_SPI2->CR1_b.RXIE)
    {
        if ((1UL == bM4_SPI2->SR_b.RDFF) && (0UL != (VSSEL137 & BIT_MASK_27)))
        {
            SPI_2_RxEnd_IrqHandler();
        }
    }
    /* SPI Ch.2 Tx buffer empty */
    if (1UL == bM4_SPI2->CR1_b.TXIE)
    {
        if ((1UL == bM4_SPI2->SR_b.TDEF) && (0UL != (VSSEL137 & BIT_MASK_28)))
        {
            SPI_2_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.2 Bus idle */
    if (1UL == bM4_SPI2->CR1_b.IDIE)
    {
        if ((0UL == bM4_SPI2->SR_b.IDLNF) && (0UL != (VSSEL137 & BIT_MASK_29)))
        {
            SPI_2_Idle_IrqHandler();
        }
    }
    /* SPI Ch.2 parity/overflow/underflow/mode error */
    if (1UL == bM4_SPI2->CR1_b.EIE)
    {
        u32Tmp1 = M4_SPI2->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_30)))
        {
            SPI_2_Err_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.138 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ138_Handler(void)
{
    const uint32_t VSSEL138 = M4_INTC->VSSEL138;
    uint32_t u32Tmp1;
    uint8_t RTIF;
    uint8_t RTIE;
    uint8_t ERRINT;
    uint8_t TTCFG;

    /* TimerA Ch.5 overflow */
    if (1UL == bM4_TMRA_5->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_5->BCSTR_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_00)))
        {
            TMRA_5_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.5 underflow */
    if (1UL == bM4_TMRA_5->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_5->BCSTR_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_01)))
        {
            TMRA_5_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.5 compare match 1 */
    if (1UL == bM4_TMRA_5->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_5->STFLR_b.CMPF1) && (0UL != (VSSEL138 & BIT_MASK_02)))
        {
            TMRA_5_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.5 compare match 2 */
    if (1UL == bM4_TMRA_5->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_5->STFLR_b.CMPF2) && (0UL != (VSSEL138 & BIT_MASK_02)))
        {
            TMRA_5_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.5 compare match 3 */
    if (1UL == bM4_TMRA_5->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_5->STFLR_b.CMPF3) && (0UL != (VSSEL138 & BIT_MASK_02)))
        {
            TMRA_5_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.5 compare match 4 */
    if (1UL == bM4_TMRA_5->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_5->STFLR_b.CMPF4) && (0UL != (VSSEL138 & BIT_MASK_02)))
        {
            TMRA_5_Cmp4_IrqHandler();
        }
    }
    /* TimerA Ch.6 overflow */
    if (1UL == bM4_TMRA_6->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_6->BCSTR_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_03)))
        {
            TMRA_6_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.6 underflow */
    if (1UL == bM4_TMRA_6->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_6->BCSTR_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_04)))
        {
            TMRA_6_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.6 compare match 1 */
    if (1UL == bM4_TMRA_6->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_6->STFLR_b.CMPF1) && (0UL != (VSSEL138 & BIT_MASK_05)))
        {
            TMRA_6_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.6 compare match 2 */
    if (1UL == bM4_TMRA_6->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_6->STFLR_b.CMPF2) && (0UL != (VSSEL138 & BIT_MASK_05)))
        {
            TMRA_6_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.6 compare match 3 */
    if (1UL == bM4_TMRA_6->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_6->STFLR_b.CMPF3) && (0UL != (VSSEL138 & BIT_MASK_05)))
        {
            TMRA_6_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.6 compare match 4 */
    if (1UL == bM4_TMRA_6->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_6->STFLR_b.CMPF4) && (0UL != (VSSEL138 & BIT_MASK_05)))
        {
            TMRA_6_Cmp4_IrqHandler();
        }
    }
    /* TimerA Ch.7 overflow */
    if (1UL == bM4_TMRA_7->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_7->BCSTR_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_06)))
        {
            TMRA_7_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.7 underflow */
    if (1UL == bM4_TMRA_7->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_7->BCSTR_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_07)))
        {
            TMRA_7_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.7 compare match 1 */
    if (1UL == bM4_TMRA_7->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_7->STFLR_b.CMPF1) && (0UL != (VSSEL138 & BIT_MASK_08)))
        {
            TMRA_7_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.7 compare match 2 */
    if (1UL == bM4_TMRA_7->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_7->STFLR_b.CMPF2) && (0UL != (VSSEL138 & BIT_MASK_08)))
        {
            TMRA_7_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.7 compare match 3 */
    if (1UL == bM4_TMRA_7->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_7->STFLR_b.CMPF3) && (0UL != (VSSEL138 & BIT_MASK_08)))
        {
            TMRA_7_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.7 compare match 4 */
    if (1UL == bM4_TMRA_7->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_7->STFLR_b.CMPF4) && (0UL != (VSSEL138 & BIT_MASK_08)))
        {
            TMRA_7_Cmp4_IrqHandler();
        }
    }
    /* TimerA Ch.8 overflow */
    if (1UL == bM4_TMRA_8->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_8->BCSTR_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_09)))
        {
            TMRA_8_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.8 underflow */
    if (1UL == bM4_TMRA_8->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_8->BCSTR_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_10)))
        {
            TMRA_8_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.8 compare match 1 */
    if (1UL == bM4_TMRA_8->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_8->STFLR_b.CMPF1) && (0UL != (VSSEL138 & BIT_MASK_11)))
        {
            TMRA_8_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.8 compare match 2 */
    if (1UL == bM4_TMRA_8->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_8->STFLR_b.CMPF2) && (0UL != (VSSEL138 & BIT_MASK_11)))
        {
            TMRA_8_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.8 compare match 3 */
    if (1UL == bM4_TMRA_8->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_8->STFLR_b.CMPF3) && (0UL != (VSSEL138 & BIT_MASK_11)))
        {
            TMRA_8_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.8 compare match 4 */
    if (1UL == bM4_TMRA_8->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_8->STFLR_b.CMPF4) && (0UL != (VSSEL138 & BIT_MASK_11)))
        {
            TMRA_8_Cmp4_IrqHandler();
        }
    }
    if (1UL == bM4_USART3->CR1_b.RIE)
    {
        /* USART Ch.3 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART3->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_12)))
        {
            USART_3_RxErr_IrqHandler();
        }
        /* USART Ch.3 Rx end */
        if ((1UL == bM4_USART3->SR_b.RXNE) && (0UL != (VSSEL138 & BIT_MASK_13)))
        {
            USART_3_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.3 Tx buffer empty */
    if (1UL == bM4_USART3->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART3->SR_b.TXE) && (0UL != (VSSEL138 & BIT_MASK_14)))
        {
            USART_3_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.3 Tx end */
    if (1UL == bM4_USART3->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART3->SR_b.TC) && (0UL != (VSSEL138 & BIT_MASK_15)))
        {
            USART_3_TxEnd_IrqHandler();
        }
    }
    if (1UL == bM4_USART4->CR1_b.RIE)
    {
        /* USART Ch.4 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART4->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_16)))
        {
            USART_4_RxErr_IrqHandler();
        }
        /* USART Ch.4 Rx end */
        if ((1UL == bM4_USART4->SR_b.RXNE) && (0UL != (VSSEL138 & BIT_MASK_17)))
        {
            USART_4_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.4 Tx buffer empty */
    if (1UL == bM4_USART4->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART4->SR_b.TXE) && (0UL != (VSSEL138 & BIT_MASK_18)))
        {
            USART_4_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.4 Tx end */
    if (1UL == bM4_USART4->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART4->SR_b.TC) && (0UL != (VSSEL138 & BIT_MASK_19)))
        {
            USART_4_TxEnd_IrqHandler();
        }
    }
    /* CAN Ch.1 */
    if (0UL != (0UL != (VSSEL138 & BIT_MASK_20)))
    {
        RTIF = M4_CAN1->RTIF;
        RTIE = M4_CAN1->RTIE;
        ERRINT = M4_CAN1->ERRINT;
        TTCFG = M4_CAN1->TTCFG;
        if ((0U != (TTCFG & CAN_TTCFG_TEIF))        ||                          \
            (0U != (RTIF & CAN_RTIF_AIF))           ||                          \
            (0U != (RTIF & RTIE & 0xFEU))           ||                          \
            ((0U != (ERRINT & CAN_ERRINT_BEIE))     &&                          \
             (0U != (ERRINT & CAN_ERRINT_BEIF)))    ||                          \
            ((0U != (ERRINT & CAN_ERRINT_ALIE))     &&                          \
             (0U != (ERRINT & CAN_ERRINT_ALIF)))    ||                          \
            ((0U != (ERRINT & CAN_ERRINT_EPIE))     &&                          \
             (0U != (ERRINT & CAN_ERRINT_EPIF)))    ||                          \
            ((0U != (TTCFG & CAN_TTCFG_TTIE))       &&                          \
             (0U != (TTCFG & CAN_TTCFG_TTIF)))      ||                          \
            ((0U != (TTCFG & CAN_TTCFG_WTIE))       &&                          \
             (0U != (TTCFG & CAN_TTCFG_WTIF))))
            {
                CAN_1_IrqHandler();
            }
    }
    /* CAN Ch.2 */
    if (0UL != (0UL != (VSSEL138 & BIT_MASK_21)))
    {
        RTIF = M4_CAN2->RTIF;
        RTIE = M4_CAN2->RTIE;
        ERRINT = M4_CAN2->ERRINT;
        TTCFG = M4_CAN2->TTCFG;
        if ((0U != (TTCFG & CAN_TTCFG_TEIF))        ||                          \
            (0U != (RTIF & CAN_RTIF_AIF))           ||                          \
            (0U != (RTIF & RTIE & 0xFEU))           ||                          \
            ((0U != (ERRINT & CAN_ERRINT_BEIE))     &&                          \
             (0U != (ERRINT & CAN_ERRINT_BEIF)))    ||                          \
            ((0U != (ERRINT & CAN_ERRINT_ALIE))     &&                          \
             (0U != (ERRINT & CAN_ERRINT_ALIF)))    ||                          \
            ((0U != (ERRINT & CAN_ERRINT_EPIE))     &&                          \
             (0U != (ERRINT & CAN_ERRINT_EPIF)))    ||                          \
            ((0U != (TTCFG & CAN_TTCFG_TTIE))       &&                          \
             (0U != (TTCFG & CAN_TTCFG_TTIF)))      ||                          \
            ((0U != (TTCFG & CAN_TTCFG_WTIE))       &&                          \
             (0U != (TTCFG & CAN_TTCFG_WTIF))))
            {
                CAN_2_IrqHandler();
            }
    }
    /* SPI Ch.3 Rx end */
    if (1UL == bM4_SPI3->CR1_b.RXIE)
    {
        if ((1UL == bM4_SPI3->SR_b.RDFF) && (0UL != (VSSEL138 & BIT_MASK_22)))
        {
            SPI_3_RxEnd_IrqHandler();
        }
    }
    /* SPI Ch.3 Tx buffer empty */
    if (1UL == bM4_SPI3->CR1_b.TXIE)
    {
        if ((1UL == bM4_SPI3->SR_b.TDEF) && (0UL != (VSSEL138 & BIT_MASK_23)))
        {
            SPI_3_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.3 Bus idle */
    if (1UL == bM4_SPI3->CR1_b.IDIE)
    {
        if ((0UL == bM4_SPI3->SR_b.IDLNF) && (0UL != (VSSEL138 & BIT_MASK_24)))
        {
            SPI_3_Idle_IrqHandler();
        }
    }
    /* SPI Ch.3 parity/overflow/underflow/mode error */
    if (1UL == bM4_SPI3->CR1_b.EIE)
    {
        u32Tmp1 = M4_SPI3->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_25)))
        {
            SPI_3_Err_IrqHandler();
        }
    }
    /* SPI Ch.4 Rx end */
    if (1UL == bM4_SPI4->CR1_b.RXIE)
    {
        if ((1UL == bM4_SPI4->SR_b.RDFF) && (0UL != (VSSEL138 & BIT_MASK_27)))
        {
            SPI_4_RxEnd_IrqHandler();
        }
    }
    /* SPI Ch.4 Tx buffer empty */
    if (1UL == bM4_SPI4->CR1_b.TXIE)
    {
        if ((1UL == bM4_SPI4->SR_b.TDEF) && (0UL != (VSSEL138 & BIT_MASK_28)))
        {
            SPI_4_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.4 Bus idle */
    if (1UL == bM4_SPI4->CR1_b.IDIE)
    {
        if ((0UL == bM4_SPI4->SR_b.IDLNF) && (0UL != (VSSEL138 & BIT_MASK_29)))
        {
            SPI_4_Idle_IrqHandler();
        }
    }
    /* SPI Ch.4 parity/overflow/underflow/mode error */
    if (1UL == bM4_SPI4->CR1_b.EIE)
    {
        u32Tmp1 = M4_SPI4->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_30)))
        {
            SPI_4_Err_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.139 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ139_Handler(void)
{
    const uint32_t VSSEL139 = M4_INTC->VSSEL139;
    uint32_t u32Tmp1;

    /* TimerA Ch.9 overflow */
    if (1UL == bM4_TMRA_9->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_9->BCSTR_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_00)))
        {
            TMRA_9_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.9 underflow */
    if (1UL == bM4_TMRA_9->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_9->BCSTR_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_01)))
        {
            TMRA_9_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.9 compare match 1 */
    if (1UL == bM4_TMRA_9->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_9->STFLR_b.CMPF1) && (0UL != (VSSEL139 & BIT_MASK_02)))
        {
            TMRA_9_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.9 compare match 2 */
    if (1UL == bM4_TMRA_9->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_9->STFLR_b.CMPF2) && (0UL != (VSSEL139 & BIT_MASK_02)))
        {
            TMRA_9_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.9 compare match 3 */
    if (1UL == bM4_TMRA_9->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_9->STFLR_b.CMPF3) && (0UL != (VSSEL139 & BIT_MASK_02)))
        {
            TMRA_9_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.9 compare match 4 */
    if (1UL == bM4_TMRA_9->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_9->STFLR_b.CMPF4) && (0UL != (VSSEL139 & BIT_MASK_02)))
        {
            TMRA_9_Cmp4_IrqHandler();
        }
    }
    /* TimerA Ch.10 overflow */
    if (1UL == bM4_TMRA_10->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_10->BCSTR_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_03)))
        {
            TMRA_10_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.10 underflow */
    if (1UL == bM4_TMRA_10->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_10->BCSTR_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_04)))
        {
            TMRA_10_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.10 compare match 1 */
    if (1UL == bM4_TMRA_10->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_10->STFLR_b.CMPF1) && (0UL != (VSSEL139 & BIT_MASK_05)))
        {
            TMRA_10_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.10 compare match 2 */
    if (1UL == bM4_TMRA_10->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_10->STFLR_b.CMPF2) && (0UL != (VSSEL139 & BIT_MASK_05)))
        {
            TMRA_10_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.10 compare match 3 */
    if (1UL == bM4_TMRA_10->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_10->STFLR_b.CMPF3) && (0UL != (VSSEL139 & BIT_MASK_05)))
        {
            TMRA_10_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.10 compare match 4 */
    if (1UL == bM4_TMRA_10->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_10->STFLR_b.CMPF4) && (0UL != (VSSEL139 & BIT_MASK_05)))
        {
            TMRA_10_Cmp4_IrqHandler();
        }
    }
    /* TimerA Ch.11 overflow */
    if (1UL == bM4_TMRA_11->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_11->BCSTR_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_06)))
        {
            TMRA_11_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.11 underflow */
    if (1UL == bM4_TMRA_11->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_11->BCSTR_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_07)))
        {
            TMRA_11_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.11 compare match 1 */
    if (1UL == bM4_TMRA_11->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_11->STFLR_b.CMPF1) && (0UL != (VSSEL139 & BIT_MASK_08)))
        {
            TMRA_11_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.11 compare match 2 */
    if (1UL == bM4_TMRA_11->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_11->STFLR_b.CMPF2) && (0UL != (VSSEL139 & BIT_MASK_08)))
        {
            TMRA_11_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.11 compare match 3 */
    if (1UL == bM4_TMRA_11->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_11->STFLR_b.CMPF3) && (0UL != (VSSEL139 & BIT_MASK_08)))
        {
            TMRA_11_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.11 compare match 4 */
    if (1UL == bM4_TMRA_11->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_11->STFLR_b.CMPF4) && (0UL != (VSSEL139 & BIT_MASK_08)))
        {
            TMRA_11_Cmp4_IrqHandler();
        }
    }
    /* TimerA Ch.12 overflow */
    if (1UL == bM4_TMRA_12->BCSTR_b.ITENOVF)
    {
        if ((1UL == bM4_TMRA_12->BCSTR_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_09)))
        {
            TMRA_12_Ovf_IrqHandler();
        }
    }
    /* TimerA Ch.12 underflow */
    if (1UL == bM4_TMRA_12->BCSTR_b.ITENUDF)
    {
        if ((1UL == bM4_TMRA_12->BCSTR_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_10)))
        {
            TMRA_12_Udf_IrqHandler();
        }
    }
    /* TimerA Ch.12 compare match 1 */
    if (1UL == bM4_TMRA_12->ICONR_b.ITEN1)
    {
        if ((1UL == bM4_TMRA_12->STFLR_b.CMPF1) && (0UL != (VSSEL139 & BIT_MASK_11)))
        {
            TMRA_12_Cmp1_IrqHandler();
        }
    }
    /* TimerA Ch.12 compare match 2 */
    if (1UL == bM4_TMRA_12->ICONR_b.ITEN2)
    {
        if ((1UL == bM4_TMRA_12->STFLR_b.CMPF2) && (0UL != (VSSEL139 & BIT_MASK_11)))
        {
            TMRA_12_Cmp2_IrqHandler();
        }
    }
    /* TimerA Ch.12 compare match 3 */
    if (1UL == bM4_TMRA_12->ICONR_b.ITEN3)
    {
        if ((1UL == bM4_TMRA_12->STFLR_b.CMPF3) && (0UL != (VSSEL139 & BIT_MASK_11)))
        {
            TMRA_12_Cmp3_IrqHandler();
        }
    }
    /* TimerA Ch.12 compare match 4 */
    if (1UL == bM4_TMRA_12->ICONR_b.ITEN4)
    {
        if ((1UL == bM4_TMRA_12->STFLR_b.CMPF4) && (0UL != (VSSEL139 & BIT_MASK_11)))
        {
            TMRA_12_Cmp4_IrqHandler();
        }
    }
    /* USART Ch.5 LIN bus break */
    if (1UL == bM4_USART5->CR2_b.LBDIE)
    {
        if ((1UL == bM4_USART5->SR_b.LBD) && (0UL != (VSSEL139 & BIT_MASK_12)))
        {
            USART_5_LinBreakField_IrqHandler();
        }
    }
    /* USART Ch.5 LIN bus wakeup */
    if (1UL == bM4_USART5->CR2_b.WKUPE)
    {
        if ((1UL == bM4_USART5->SR_b.WKUP) && (0UL != (VSSEL139 & BIT_MASK_12)))
        {
            USART_5_LinWakeup_IrqHandler();
        }
    }
    if (1UL == bM4_USART5->CR1_b.RIE)
    {
        /* USART Ch.5 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART5->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_13)))
        {
            USART_5_RxErr_IrqHandler();
        }
        /* USART Ch.5 Rx end */
        if ((1UL == bM4_USART5->SR_b.RXNE) && (0UL != (VSSEL139 & BIT_MASK_14)))
        {
            USART_5_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.5 Tx buffer empty */
    if (1UL == bM4_USART5->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART5->SR_b.TXE) && (0UL != (VSSEL139 & BIT_MASK_15)))
        {
            USART_5_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.5 Tx end */
    if (1UL == bM4_USART5->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART5->SR_b.TC) && (0UL != (VSSEL139 & BIT_MASK_16)))
        {
            USART_5_TxEnd_IrqHandler();
        }
    }
    if (1UL == bM4_USART6->CR1_b.RIE)
    {
        /* USART Ch.6 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART6->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_17)))
        {
            USART_6_RxErr_IrqHandler();
        }
        /* USART Ch.6 Rx end */
        if ((1UL == bM4_USART6->SR_b.RXNE) && (0UL != (VSSEL139 & BIT_MASK_18)))
        {
            USART_6_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.6 Tx buffer empty */
    if (1UL == bM4_USART6->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART6->SR_b.TXE) && (0UL != (VSSEL139 & BIT_MASK_19)))
        {
            USART_6_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.6 Tx end */
    if (1UL == bM4_USART6->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART6->SR_b.TC) && (0UL != (VSSEL139 & BIT_MASK_20)))
        {
            USART_6_TxEnd_IrqHandler();
        }
    }
    /* USART Ch.6 Tx timeout */
    if (1UL == bM4_USART6->CR1_b.RTOIE)
    {
        if ((1UL == bM4_USART6->SR_b.RTOF) && (0UL != (VSSEL139 & BIT_MASK_21)))
        {
            USART_6_RxTO_IrqHandler();
        }
    }
    /* SPI Ch.5 Rx end */
    if (1UL == bM4_SPI5->CR1_b.RXIE)
    {
        if ((1UL == bM4_SPI5->SR_b.RDFF) && (0UL != (VSSEL139 & BIT_MASK_22)))
        {
            SPI_5_RxEnd_IrqHandler();
        }
    }
    /* SPI Ch.5 Tx buffer empty */
    if (1UL == bM4_SPI5->CR1_b.TXIE)
    {
        if ((1UL == bM4_SPI5->SR_b.TDEF) && (0UL != (VSSEL139 & BIT_MASK_23)))
        {
            SPI_5_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.5 Bus idle */
    if (1UL == bM4_SPI5->CR1_b.IDIE)
    {
        if ((0UL == bM4_SPI5->SR_b.IDLNF) && (0UL != (VSSEL139 & BIT_MASK_24)))
        {
            SPI_5_Idle_IrqHandler();
        }
    }
    /* SPI Ch.5 parity/overflow/underflow/mode error */
    if (1UL == bM4_SPI5->CR1_b.EIE)
    {
        u32Tmp1 = M4_SPI5->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_25)))
        {
            SPI_5_Err_IrqHandler();
        }
    }
    /* SPI Ch.6 Rx end */
    if (1UL == bM4_SPI6->CR1_b.RXIE)
    {
        if ((1UL == bM4_SPI6->SR_b.RDFF) && (0UL != (VSSEL139 & BIT_MASK_27)))
        {
            SPI_6_RxEnd_IrqHandler();
        }
    }
    /* SPI Ch.6 Tx buffer empty */
    if (1UL == bM4_SPI6->CR1_b.TXIE)
    {
        if ((1UL == bM4_SPI6->SR_b.TDEF) && (0UL != (VSSEL139 & BIT_MASK_28)))
        {
            SPI_6_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.6 Bus idle */
    if (1UL == bM4_SPI6->CR1_b.IDIE)
    {
        if ((0UL == bM4_SPI6->SR_b.IDLNF) && (0UL != (VSSEL139 & BIT_MASK_29)))
        {
            SPI_6_Idle_IrqHandler();
        }
    }
    /* SPI Ch.6 parity/overflow/underflow/mode error */
    if (1UL == bM4_SPI6->CR1_b.EIE)
    {
        u32Tmp1 = M4_SPI6->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_30)))
        {
            SPI_6_Err_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.140 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ140_Handler(void)
{
    const uint32_t VSSEL140 = M4_INTC->VSSEL140;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    uint16_t NORINTST;
    uint16_t NORINTSGEN;
    uint16_t ERRINTSGEN;
    uint32_t MMC_REVSTSR;
    uint32_t MMC_TRSSTSR;
    uint32_t MMC_RITCTLR;
    uint32_t MMC_TITCTLR;
    uint32_t DMA_DMASTSR;
    uint32_t DMA_INTENAR;
    uint32_t PTP_INTE;
    uint32_t PMT_INTMASK;
    uint32_t PMT_INTSTSR;
    uint32_t PTP_INTMASK;
    uint32_t PTP_INTSTSR;

    /* I2S Ch.1 Tx */
    if (1UL == bM4_I2S1->CTRL_b.TXIE)
    {
        if ((1UL == bM4_I2S1->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_00)))
        {
            I2S_1_Tx_IrqHandler();
        }
    }
    /* I2S Ch.1 Rx */
    if (1UL == bM4_I2S1->CTRL_b.RXIE)
    {
        if ((1UL == bM4_I2S1->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_01)))
        {
            I2S_1_Rx_IrqHandler();
        }
    }
    /* I2S Ch.1 Error */
    if (1UL == bM4_I2S1->CTRL_b.EIE)
    {
        u32Tmp1 = M4_I2S1->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_02)))
        {
            I2S_1_Err_IrqHandler();
        }
    }
    /* I2S Ch.2 Tx */
    if (1UL == bM4_I2S2->CTRL_b.TXIE)
    {
        if ((1UL == bM4_I2S2->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_03)))
        {
            I2S_2_Tx_IrqHandler();
        }
    }
    /* I2S Ch.2 Rx */
    if (1UL == bM4_I2S2->CTRL_b.RXIE)
    {
        if ((1UL == bM4_I2S2->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_04)))
        {
            I2S_2_Rx_IrqHandler();
        }
    }
    /* I2S Ch.2 Error */
    if (1UL == bM4_I2S2->CTRL_b.EIE)
    {
        u32Tmp1 = M4_I2S2->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_05)))
        {
            I2S_2_Err_IrqHandler();
        }
    }
    if (1UL == bM4_USART7->CR1_b.RIE)
    {
        /* USART Ch.7 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART7->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_06)))
        {
            USART_7_RxErr_IrqHandler();
        }
        /* USART Ch.7 Rx end */
        if ((1UL == bM4_USART7->SR_b.RXNE) && (0UL != (VSSEL140 & BIT_MASK_07)))
        {
            USART_7_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.7 Tx buffer empty */
    if (1UL == bM4_USART7->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART7->SR_b.TXE) && (0UL != (VSSEL140 & BIT_MASK_08)))
        {
            USART_7_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.7 Tx end */
    if (1UL == bM4_USART7->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART7->SR_b.TC) && (0UL != (VSSEL140 & BIT_MASK_09)))
        {
            USART_7_TxEnd_IrqHandler();
        }
    }
    /* USART Ch.7 Tx timeout */
    if (1UL == bM4_USART7->CR1_b.RTOIE)
    {
        if ((1UL == bM4_USART7->SR_b.RTOF) && (0UL != (VSSEL140 & BIT_MASK_10)))
        {
            USART_7_RxTO_IrqHandler();
        }
    }
    if (1UL == bM4_USART8->CR1_b.RIE)
    {
        /* USART Ch.8 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART8->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_11)))
        {
            USART_8_RxErr_IrqHandler();
        }
        /* USART Ch.8 Rx end */
        if ((1UL == bM4_USART8->SR_b.RXNE) && (0UL != (VSSEL140 & BIT_MASK_12)))
        {
            USART_8_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.8 Tx buffer empty */
    if (1UL == bM4_USART8->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART8->SR_b.TXE) && (0UL != (VSSEL140 & BIT_MASK_13)))
        {
            USART_8_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.8 Tx end */
    if (1UL == bM4_USART8->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART8->SR_b.TC) && (0UL != (VSSEL140 & BIT_MASK_14)))
        {
            USART_8_TxEnd_IrqHandler();
        }
    }
    /* USB FS global interrupt */
    if (1UL == bM4_USBFS->GAHBCFG_b.GLBLINTRMSK)
    {
        u32Tmp1 = M4_USBFS->GINTMSK & 0xF77CFCFBUL;
        u32Tmp2 = M4_USBFS->GINTSTS & 0xF77CFCFBUL;
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL140 & BIT_MASK_15)))
        {
            USBFS_Global_IrqHandler();
        }
    }
    /* SDIO unit 1 */
    if (0UL != (VSSEL140 & BIT_MASK_20))
    {
        NORINTST = M4_SDIOC1->NORINTST & (SDIOC_NORINTST_CINT | SDIOC_NORINTST_CRM | SDIOC_NORINTST_CIST |  \
                                          SDIOC_NORINTST_BRR  | SDIOC_NORINTST_BWR | SDIOC_NORINTST_BGE  |  \
                                          SDIOC_NORINTST_TC   | SDIOC_NORINTST_CC);
        NORINTSGEN = M4_SDIOC1->NORINTSGEN & (SDIOC_NORINTSTEN_CINTEN | SDIOC_NORINTSTEN_CRMEN |    \
                                              SDIOC_NORINTSTEN_CISTEN | SDIOC_NORINTSTEN_BRREN |    \
                                              SDIOC_NORINTSTEN_BWREN  | SDIOC_NORINTSTEN_BGEEN |    \
                                              SDIOC_NORINTSTEN_TCEN   | SDIOC_NORINTSTEN_CCEN);
        ERRINTSGEN = M4_SDIOC1->ERRINTSGEN & (SDIOC_ERRINTSTEN_ACEEN | SDIOC_ERRINTSTEN_DEBEEN |    \
                                              SDIOC_ERRINTSTEN_DCEEN | SDIOC_ERRINTSTEN_DTOEEN |    \
                                              SDIOC_ERRINTSTEN_CIEEN | SDIOC_ERRINTSTEN_CEBEEN |    \
                                              SDIOC_ERRINTSTEN_CCEEN | SDIOC_ERRINTSTEN_CTOEEN);
        if (0U != (NORINTST & NORINTSGEN))
        {
            SDIOC_1_Normal_IrqHandler();
        }
        if ((1UL == bM4_SDIOC1->NORINTST_b.EI) && (0U != ERRINTSGEN))
        {
            SDIOC_1_Error_IrqHandler();
        }
    }
    /* SDIO unit 2 */
    if (0UL != (VSSEL140 & BIT_MASK_23))
    {
        NORINTST = M4_SDIOC2->NORINTST & (SDIOC_NORINTST_CINT | SDIOC_NORINTST_CRM | SDIOC_NORINTST_CIST |  \
                                          SDIOC_NORINTST_BRR  | SDIOC_NORINTST_BWR | SDIOC_NORINTST_BGE  |  \
                                          SDIOC_NORINTST_TC   | SDIOC_NORINTST_CC);
        NORINTSGEN = M4_SDIOC2->NORINTSGEN & (SDIOC_NORINTSTEN_CINTEN | SDIOC_NORINTSTEN_CRMEN |    \
                                              SDIOC_NORINTSTEN_CISTEN | SDIOC_NORINTSTEN_BRREN |    \
                                              SDIOC_NORINTSTEN_BWREN  | SDIOC_NORINTSTEN_BGEEN |    \
                                              SDIOC_NORINTSTEN_TCEN   | SDIOC_NORINTSTEN_CCEN);
        ERRINTSGEN = M4_SDIOC2->ERRINTSGEN & (SDIOC_ERRINTSTEN_ACEEN | SDIOC_ERRINTSTEN_DEBEEN |    \
                                              SDIOC_ERRINTSTEN_DCEEN | SDIOC_ERRINTSTEN_DTOEEN |    \
                                              SDIOC_ERRINTSTEN_CIEEN | SDIOC_ERRINTSTEN_CEBEEN |    \
                                              SDIOC_ERRINTSTEN_CCEEN | SDIOC_ERRINTSTEN_CTOEEN);
        if (0U != (NORINTST & NORINTSGEN))
        {
            SDIOC_2_Normal_IrqHandler();
        }
        if ((1UL == bM4_SDIOC2->NORINTST_b.EI) && (0U != ERRINTSGEN))
        {
            SDIOC_2_Error_IrqHandler();
        }
    }
    /* Ethernat global */
    MMC_REVSTSR = M4_ETH->MMC_REVSTSR & (ETH_MMC_REVSTSR_RXOEIS | ETH_MMC_REVSTSR_RXLEIS |  \
                                         ETH_MMC_REVSTSR_RXUGIS | ETH_MMC_REVSTSR_RXREIS |  \
                                         ETH_MMC_REVSTSR_RXAEIS | ETH_MMC_REVSTSR_RXCEIS |  \
                                         ETH_MMC_REVSTSR_RXMGIS | ETH_MMC_REVSTSR_RXBGIS);
    MMC_TRSSTSR = M4_ETH->MMC_TRSSTSR & (ETH_MMC_TRSSTSR_TXEDEIS| ETH_MMC_TRSSTSR_TXUGIS |  \
                                         ETH_MMC_TRSSTSR_TXCAEIS| ETH_MMC_TRSSTSR_TXECEIS|  \
                                         ETH_MMC_TRSSTSR_TXLCEIS| ETH_MMC_TRSSTSR_TXDEEIS|  \
                                         ETH_MMC_TRSSTSR_TXMGIS | ETH_MMC_TRSSTSR_TXBGIS);
    MMC_RITCTLR = M4_ETH->MMC_RITCTLR & (ETH_MMC_RITCTLR_RXBGIM | ETH_MMC_RITCTLR_RXMGIM |  \
                                         ETH_MMC_RITCTLR_RXCEIM | ETH_MMC_RITCTLR_RXAEIM |  \
                                         ETH_MMC_RITCTLR_RXREIM | ETH_MMC_RITCTLR_RXUGIM |  \
                                         ETH_MMC_RITCTLR_RXLEIM | ETH_MMC_RITCTLR_RXOEIM);
    MMC_TITCTLR = M4_ETH->MMC_TITCTLR & (ETH_MMC_TITCTLR_TXBGIM | ETH_MMC_TITCTLR_TXMGIM |  \
                                         ETH_MMC_TITCTLR_TXDEEIM| ETH_MMC_TITCTLR_TXLCEIM|  \
                                         ETH_MMC_TITCTLR_TXECEIM| ETH_MMC_TITCTLR_TXCAEIM|  \
                                         ETH_MMC_TITCTLR_TXUGIM | ETH_MMC_TITCTLR_TXEDEIM);
    PMT_INTMASK = bM4_ETH->MAC_INTMSKR_b.PMTIM;
    PMT_INTSTSR  = bM4_ETH->MAC_INTSTSR_b.PMTIS;
    PTP_INTMASK = bM4_ETH->MAC_INTMSKR_b.TSPIM;
    PTP_INTSTSR  = bM4_ETH->MAC_INTSTSR_b.TSPIS;
    PTP_INTE    = bM4_ETH->PTP_TSPCTLR_b.TSPINT;

    DMA_DMASTSR = M4_ETH->DMA_DMASTSR & (ETH_DMA_DMASTSR_AIS | ETH_DMA_DMASTSR_NIS);
    DMA_INTENAR = M4_ETH->DMA_INTENAR & (ETH_DMA_INTENAR_AIE | ETH_DMA_INTENAR_NIE);
    if (0UL != (VSSEL140 & BIT_MASK_28))
    {
        if ((0UL != (MMC_REVSTSR & (~MMC_RITCTLR))) ||                          \
            (0UL != (MMC_TRSSTSR & (~MMC_TITCTLR))) ||                          \
            (0UL != (PMT_INTSTSR & (~PMT_INTMASK))) ||                          \
            (0UL != (PTP_INTSTSR & (~PTP_INTMASK) & PTP_INTE)) ||               \
            (0UL != (DMA_DMASTSR & DMA_INTENAR)))
        {
            ETH_Global_IrqHandler();
        }
    }

    /* Ethernat wakeup */
    if (0UL == bM4_ETH->MAC_INTMSKR_b.PMTIM)
    {
        if ((1UL == bM4_ETH->MAC_INTSTSR_b.PMTIS) && (0UL != (VSSEL140 & BIT_MASK_29)))
        {
            ETH_Wakeup_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.141 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ141_Handler(void)
{
    const uint32_t VSSEL141 = M4_INTC->VSSEL141;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* I2S Ch.3 Tx */
    if (1UL == bM4_I2S3->CTRL_b.TXIE)
    {
        if ((1UL == bM4_I2S3->SR_b.TXBA) && (0UL != (VSSEL141 & BIT_MASK_00)))
        {
            I2S_3_Tx_IrqHandler();
        }
    }
    /* I2S Ch.3 Rx */
    if (1UL == bM4_I2S3->CTRL_b.RXIE)
    {
        if ((1UL == bM4_I2S3->SR_b.RXBA) && (0UL != (VSSEL141 & BIT_MASK_01)))
        {
            I2S_3_Rx_IrqHandler();
        }
    }
    /* I2S Ch.3 Error */
    if (1UL == bM4_I2S3->CTRL_b.EIE)
    {
        u32Tmp1 = M4_I2S3->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_02)))
        {
            I2S_3_Err_IrqHandler();
        }
    }
    /* I2S Ch.4 Tx */
    if (1UL == bM4_I2S4->CTRL_b.TXIE)
    {
        if ((1UL == bM4_I2S4->SR_b.TXBA) && (0UL != (VSSEL141 & BIT_MASK_03)))
        {
            I2S_4_Tx_IrqHandler();
        }
    }
    /* I2S Ch.4 Rx */
    if (1UL == bM4_I2S4->CTRL_b.RXIE)
    {
        if ((1UL == bM4_I2S4->SR_b.RXBA) && (0UL != (VSSEL141 & BIT_MASK_04)))
        {
            I2S_4_Rx_IrqHandler();
        }
    }
    /* I2S Ch.4 Error */
    if (1UL == bM4_I2S4->CTRL_b.EIE)
    {
        u32Tmp1 = M4_I2S4->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_05)))
        {
            I2S_4_Err_IrqHandler();
        }
    }
    if (1UL == bM4_USART9->CR1_b.RIE)
    {
        /* USART Ch.9 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART9->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_06)))
        {
            USART_9_RxErr_IrqHandler();
        }
        /* USART Ch.9 Rx end */
        if ((1UL == bM4_USART9->SR_b.RXNE) && (0UL != (VSSEL141 & BIT_MASK_07)))
        {
            USART_9_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.9 Tx buffer empty */
    if (1UL == bM4_USART9->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART9->SR_b.TXE) && (0UL != (VSSEL141 & BIT_MASK_08)))
        {
            USART_9_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.9 Tx end */
    if (1UL == bM4_USART9->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART9->SR_b.TC) && (0UL != (VSSEL141 & BIT_MASK_09)))
        {
            USART_9_TxEnd_IrqHandler();
        }
    }
    /* USART Ch.10 LIN bus break */
    if (1UL == bM4_USART10->CR2_b.LBDIE)
    {
        if ((1UL == bM4_USART10->SR_b.LBD) && (0UL != (VSSEL141 & BIT_MASK_10)))
        {
            USART_10_LinBreakField_IrqHandler();
        }
    }
    /* USART Ch.10 LIN bus wakeup */
    if (1UL == bM4_USART10->CR2_b.WKUPE)
    {
        if ((1UL == bM4_USART10->SR_b.WKUP) && (0UL != (VSSEL141 & BIT_MASK_10)))
        {
            USART_10_LinWakeup_IrqHandler();
        }
    }
    if (1UL == bM4_USART10->CR1_b.RIE)
    {
        /* USART Ch.10 Rx ORE/FE/PE error */
        u32Tmp1 = M4_USART10->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_11)))
        {
            USART_10_RxErr_IrqHandler();
        }
        /* USART Ch.10 Rx end */
        if ((1UL == bM4_USART10->SR_b.RXNE) && (0UL != (VSSEL141 & BIT_MASK_12)))
        {
            USART_10_RxEnd_IrqHandler();
        }
    }
    /* USART Ch.10 Tx buffer empty */
    if (1UL == bM4_USART10->CR1_b.TXEIE)
    {
        if ((1UL == bM4_USART10->SR_b.TXE) && (0UL != (VSSEL141 & BIT_MASK_13)))
        {
            USART_10_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.10 Tx end */
    if (1UL == bM4_USART10->CR1_b.TCIE)
    {
        if ((1UL == bM4_USART10->SR_b.TC) && (0UL != (VSSEL141 & BIT_MASK_14)))
        {
            USART_10_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.1 Rx end */
    if (1UL == bM4_I2C1->CR2_b.RFULLIE)
    {
        if ((1UL == bM4_I2C1->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_16)))
        {
            I2C_1_RxEnd_IrqHandler();
        }
    }
    /* I2C Ch.1 Tx buffer empty */
    if (1UL == bM4_I2C1->CR2_b.TEMPTYIE)
    {
        if ((1UL == bM4_I2C1->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_17)))
        {
            I2C_1_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.1 Tx end */
    if (1UL == bM4_I2C1->CR2_b.TENDIE)
    {
        if ((1UL == bM4_I2C1->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_18)))
        {
            I2C_1_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.1 Error */
    u32Tmp1 = M4_I2C1->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = M4_I2C1->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_19)))
    {
        I2C_1_Err_IrqHandler();
    }
    /* I2C Ch.2 Rx end */
    if (1UL == bM4_I2C2->CR2_b.RFULLIE)
    {
        if ((1UL == bM4_I2C2->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_20)))
        {
            I2C_2_RxEnd_IrqHandler();
        }
    }
    /* I2C Ch.2 Tx buffer empty */
    if (1UL == bM4_I2C2->CR2_b.TEMPTYIE)
    {
        if ((1UL == bM4_I2C2->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_21)))
        {
            I2C_2_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.2 Tx end */
    if (1UL == bM4_I2C2->CR2_b.TENDIE)
    {
        if ((1UL == bM4_I2C2->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_22)))
        {
            I2C_2_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.2 Error */
    u32Tmp1 = M4_I2C2->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = M4_I2C2->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_23)))
    {
        I2C_2_Err_IrqHandler();
    }
    /* I2C Ch.3 Rx end */
    if (1UL == bM4_I2C3->CR2_b.RFULLIE)
    {
        if ((1UL == bM4_I2C3->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_24)))
        {
            I2C_3_RxEnd_IrqHandler();
        }
    }
    /* I2C Ch.3 Tx buffer empty */
    if (1UL == bM4_I2C3->CR2_b.TEMPTYIE)
    {
        if ((1UL == bM4_I2C3->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_25)))
        {
            I2C_3_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.3 Tx end */
    if (1UL == bM4_I2C3->CR2_b.TENDIE)
    {
        if ((1UL == bM4_I2C3->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_26)))
        {
            I2C_3_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.3 Error */
    u32Tmp1 = M4_I2C3->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = M4_I2C3->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_27)))
    {
        I2C_3_Err_IrqHandler();
    }
}

/**
 * @brief  Interrupt No.142 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ142_Handler(void)
{
    const uint32_t VSSEL142 = M4_INTC->VSSEL142;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* I2C Ch.4 Rx end */
    if (1UL == bM4_I2C4->CR2_b.RFULLIE)
    {
        if ((1UL == bM4_I2C4->SR_b.RFULLF) && (0UL != (VSSEL142 & BIT_MASK_00)))
        {
            I2C_4_RxEnd_IrqHandler();
        }
    }
    /* I2C Ch.4 Tx buffer empty */
    if (1UL == bM4_I2C4->CR2_b.TEMPTYIE)
    {
        if ((1UL == bM4_I2C4->SR_b.TEMPTYF) && (0UL != (VSSEL142 & BIT_MASK_01)))
        {
            I2C_4_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.4 Tx end */
    if (1UL == bM4_I2C4->CR2_b.TENDIE)
    {
        if ((1UL == bM4_I2C4->SR_b.TENDF) && (0UL != (VSSEL142 & BIT_MASK_02)))
        {
            I2C_4_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.4 Error */
    u32Tmp1 = M4_I2C4->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = M4_I2C4->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL142 & BIT_MASK_03)))
    {
        I2C_4_Err_IrqHandler();
    }
    /* I2C Ch.5 Rx end */
    if (1UL == bM4_I2C5->CR2_b.RFULLIE)
    {
        if ((1UL == bM4_I2C5->SR_b.RFULLF) && (0UL != (VSSEL142 & BIT_MASK_04)))
        {
            I2C_5_RxEnd_IrqHandler();
        }
    }
    /* I2C Ch.5 Tx buffer empty */
    if (1UL == bM4_I2C5->CR2_b.TEMPTYIE)
    {
        if ((1UL == bM4_I2C5->SR_b.TEMPTYF) && (0UL != (VSSEL142 & BIT_MASK_05)))
        {
            I2C_5_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.5 Tx end */
    if (1UL == bM4_I2C5->CR2_b.TENDIE)
    {
        if ((1UL == bM4_I2C5->SR_b.TENDF) && (0UL != (VSSEL142 & BIT_MASK_06)))
        {
            I2C_5_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.5 Error */
    u32Tmp1 = M4_I2C5->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = M4_I2C5->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL142 & BIT_MASK_07)))
    {
        I2C_5_Err_IrqHandler();
    }
    /* I2C Ch.6 Rx end */
    if (1UL == bM4_I2C6->CR2_b.RFULLIE)
    {
        if ((1UL == bM4_I2C6->SR_b.RFULLF) && (0UL != (VSSEL142 & BIT_MASK_08)))
        {
            I2C_6_RxEnd_IrqHandler();
        }
    }
    /* I2C Ch.6 Tx buffer empty */
    if (1UL == bM4_I2C6->CR2_b.TEMPTYIE)
    {
        if ((1UL == bM4_I2C6->SR_b.TEMPTYF) && (0UL != (VSSEL142 & BIT_MASK_09)))
        {
            I2C_6_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.6 Tx end */
    if (1UL == bM4_I2C6->CR2_b.TENDIE)
    {
        if ((1UL == bM4_I2C6->SR_b.TENDF) && (0UL != (VSSEL142 & BIT_MASK_10)))
        {
            I2C_6_TxEnd_IrqHandler();
        }
    }
    /* I2C Ch.6 Error */
    u32Tmp1 = M4_I2C6->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = M4_I2C6->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL142 & BIT_MASK_11)))
    {
        I2C_6_Err_IrqHandler();
    }
    /* PVD Ch.1 */
    if (1UL == bM4_PWC->PVDCR1_b.PVD1IRE)
    {
        if ((1UL ==bM4_PWC->PVDDSR_b.PVD1DETFLG) && (0UL != (VSSEL142 & BIT_MASK_13)))
        {
            PWC_Pvd1_IrqHandler();
        }
    }
    /* PVD Ch.2 */
    if (1UL == bM4_PWC->PVDCR1_b.PVD2IRE)
    {
        if ((1UL ==bM4_PWC->PVDDSR_b.PVD2DETFLG) && (0UL != (VSSEL142 & BIT_MASK_14)))
        {
            PWC_Pvd2_IrqHandler();
        }
    }
    /* FCM error */
    if (1UL == bM4_FCM->RIER_b.ERRIE)
    {
        if ((1UL == bM4_FCM->SR_b.ERRF) && (0UL != (VSSEL142 & BIT_MASK_16)))
        {
            FCM_Err_IrqHandler();
        }
    }
    /* FCM end */
    if (1UL == bM4_FCM->RIER_b.MENDIE)
    {
        if ((1UL == bM4_FCM->SR_b.MENDF) && (0UL != (VSSEL142 & BIT_MASK_17)))
        {
            FCM_End_IrqHandler();
        }
    }
    /* FCM overflow */
    if (1UL == bM4_FCM->RIER_b.OVFIE)
    {
        if ((1UL == bM4_FCM->SR_b.OVF) && (0UL != (VSSEL142 & BIT_MASK_18)))
        {
            FCM_Ovf_IrqHandler();
        }
    }
    /* WDT underflow or refresh error */
    u32Tmp1 = M4_WDT->SR & (WDT_SR_UDF | WDT_SR_REF);
    if ((0UL != u32Tmp1) && (0UL != (VSSEL142 & BIT_MASK_19)))
    {
        WDT_IrqHandler();
    }
    /* CTC overflow or underflow error */
    if (1UL == bM4_CTC->CR1_b.ERRIE)
    {
        /* underflow */
        if ((1UL == bM4_CTC->STR_b.TRMUDF) && (0UL != (VSSEL142 & BIT_MASK_20)))
        {
            CTC_Udf_IrqHandler();
        }
        /* overflow */
        if ((1UL == bM4_CTC->STR_b.TRMOVF) && (0UL != (VSSEL142 & BIT_MASK_20)))
        {
            CTC_Ovf_IrqHandler();
        }
    }
}

/**
 * @brief  Interrupt No.143 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ143_Handler(void)
{
    const uint32_t VSSEL143 = M4_INTC->VSSEL143;
    uint32_t u32Tmp1;

    /* ADC unit1 sequence A */
    if (1UL == bM4_ADC1->ICR_b.EOCAIEN)
    {
        if ((1UL == bM4_ADC1->ISR_b.EOCAF) && (0UL != (VSSEL143 & BIT_MASK_00)))
        {
            ADC_1_SeqA_IrqHandler();
        }
    }
    /* ADC unit1 sequence B */
    if (1UL == bM4_ADC1->ICR_b.EOCBIEN)
    {
        if ((1UL == bM4_ADC1->ISR_b.EOCBF) && (0UL != (VSSEL143 & BIT_MASK_01)))
        {
            ADC_1_SeqB_IrqHandler();
        }
    }
    /* ADC unit1 window 0 compare */
    if (1UL == bM4_ADC1->AWDCR_b.AWD0IEN)
    {
        if ((1UL == bM4_ADC1->AWDSR_b.AWD0F) && (0UL != (VSSEL143 & BIT_MASK_02)))
        {
            ADC_1_Cmp0_IrqHandler();
        }
    }
    /* ADC unit1 window 1 compare */
    if (1UL == bM4_ADC1->AWDCR_b.AWD1IEN)
    {
        /* independence use */
        u32Tmp1 = (uint16_t)(M4_ADC1->AWDCR & ADC_AWDCR_AWDCM);
        if ((1UL == bM4_ADC1->AWDSR_b.AWD1F) && (0UL == u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_03)))
        {
            ADC_1_Cmp1Ind_IrqHandler();
        }
        /* combination use */
        if ((1UL == bM4_ADC1->AWDSR_b.AWDCMF) && (0UL != u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_03)))
        {
            ADC_1_Cmp1Comb_IrqHandler();
        }
    }
    /* ADC unit2 sequence A */
    if (1UL == bM4_ADC2->ICR_b.EOCAIEN)
    {
        if ((1UL == bM4_ADC2->ISR_b.EOCAF) && (0UL != (VSSEL143 & BIT_MASK_04)))
        {
            ADC_2_SeqA_IrqHandler();
        }
    }
    /* ADC unit2 sequence B */
    if (1UL == bM4_ADC2->ICR_b.EOCBIEN)
    {
        if ((1UL == bM4_ADC2->ISR_b.EOCBF) && (0UL != (VSSEL143 & BIT_MASK_05)))
        {
            ADC_2_SeqB_IrqHandler();
        }
    }
    /* ADC unit2 window 0 compare */
    if (1UL == bM4_ADC2->AWDCR_b.AWD0IEN)
    {
        if ((1UL == bM4_ADC2->AWDSR_b.AWD0F) && (0UL != (VSSEL143 & BIT_MASK_06)))
        {
            ADC_2_Cmp0_IrqHandler();
        }
    }
    /* ADC unit2 window 1 compare */
    if (1UL == bM4_ADC2->AWDCR_b.AWD1IEN)
    {
        /* independence use */
        u32Tmp1 = ((uint16_t)(M4_ADC2->AWDCR & ADC_AWDCR_AWDCM));
        if ((1UL == bM4_ADC2->AWDSR_b.AWD1F) && (0UL == u32Tmp1) && (0UL != (0UL != (VSSEL143 & BIT_MASK_07))))
        {
            ADC_2_Cmp1Ind_IrqHandler();
        }
        /* combination use */
        if ((1UL == bM4_ADC2->AWDSR_b.AWDCMF) && (0UL != u32Tmp1) && (0UL != (0UL != (VSSEL143 & BIT_MASK_07))))
        {
            ADC_2_Cmp1Comb_IrqHandler();
        }
    }
    /* ADC unit3 sequence A */
    if (1UL == bM4_ADC3->ICR_b.EOCAIEN)
    {
        if ((1UL == bM4_ADC3->ISR_b.EOCAF) && (0UL != (VSSEL143 & BIT_MASK_04)))
        {
            ADC_3_SeqA_IrqHandler();
        }
    }
    /* ADC unit3 sequence B */
    if (1UL == bM4_ADC3->ICR_b.EOCBIEN)
    {
        if ((1UL == bM4_ADC3->ISR_b.EOCBF) && (0UL != (VSSEL143 & BIT_MASK_08)))
        {
            ADC_3_SeqB_IrqHandler();
        }
    }
    /* ADC unit3 window 0 compare */
    if (1UL == bM4_ADC3->AWDCR_b.AWD0IEN)
    {
        if ((1UL == bM4_ADC3->AWDSR_b.AWD0F) && (0UL != (VSSEL143 & BIT_MASK_09)))
        {
            ADC_3_Cmp0_IrqHandler();
        }
    }
    /* ADC unit3 window 1 compare */
    if (1UL == bM4_ADC3->AWDCR_b.AWD1IEN)
    {
        /* independence use */
        u32Tmp1 = (uint16_t)(M4_ADC3->AWDCR & ADC_AWDCR_AWDCM);
        if ((1UL == bM4_ADC3->AWDSR_b.AWD1F) && (0UL == u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_10)))
        {
            ADC_3_Cmp1Ind_IrqHandler();
        }
        /* combination use */
        if ((1UL == bM4_ADC3->AWDSR_b.AWDCMF) && (0UL != u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_10)))
        {
            ADC_3_Cmp1Comb_IrqHandler();
        }
    }
    if (0UL != (VSSEL143 & BIT_MASK_16))
    {
        if (0UL != (M4_NFC->IRSR & (NFC_IRSR_RBRS | NFC_IRSR_ECCERS |           \
                    NFC_IRSR_ECCCRS | NFC_IRSR_ECCECRS | NFC_IRSR_ECCEURS)))
        {
            NFC_IrqHandler();
        }
    }
}
/**
 * @}
 */

/**
 * @defgroup INTC_Weakdef_Prototypes INTC weak function prototypes
 * @{
 */
__WEAKDEF void HardFault_IrqHandler(void)
{
}
__WEAKDEF void MemManage_IrqHandler(void)
{
}
__WEAKDEF void BusFault_IrqHandler(void)
{
}
__WEAKDEF void UsageFault_IrqHandler(void)
{
}
__WEAKDEF void SVC_IrqHandler(void)
{
}
__WEAKDEF void DebugMon_IrqHandler(void)
{
}
__WEAKDEF void PendSV_IrqHandler(void)
{
}
__WEAKDEF void SysTick_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_00_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_01_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_02_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_03_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_04_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_05_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_06_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_07_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_08_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_09_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_10_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_11_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_12_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_13_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_14_IrqHandler(void)
{
}
__WEAKDEF void EXTINT_15_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc0_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc1_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc2_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc3_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc4_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc5_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc6_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Tc7_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc0_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc1_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc2_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc3_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc4_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc5_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc6_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Btc7_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err0_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err1_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err2_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err3_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err4_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err5_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err6_IrqHandler(void)
{
}
__WEAKDEF void DMA_1_Err7_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc0_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc1_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc2_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc3_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc4_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc5_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc6_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Tc7_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc0_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc1_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc2_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc3_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc4_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc5_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc6_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Btc7_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err0_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err1_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err2_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err3_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err4_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err5_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err6_IrqHandler(void)
{
}
__WEAKDEF void DMA_2_Err7_IrqHandler(void)
{
}
__WEAKDEF void EFM_PgmEraseErr_IrqHandler(void)
{
}
__WEAKDEF void EFM_ColErr_IrqHandler(void)
{
}
__WEAKDEF void EFM_OpEnd_IrqHandler(void)
{
}
__WEAKDEF void QSPI_Err_IrqHandler(void)
{
}
__WEAKDEF void MAU_Sqrt_IrqHandler(void)
{
}
__WEAKDEF void DVP_FrameStart_IrqHandler(void)
{
}
__WEAKDEF void DVP_FrameEnd_IrqHandler(void)
{
}
__WEAKDEF void DVP_LineStart_IrqHandler(void)
{
}
__WEAKDEF void DVP_LineEnd_IrqHandler(void)
{
}
__WEAKDEF void DVP_SwSyncErr_IrqHandler(void)
{
}
__WEAKDEF void DVP_FifoErr_IrqHandler(void)
{
}
__WEAKDEF void FMAC_1_IrqHandler(void)
{
}
__WEAKDEF void FMAC_2_IrqHandler(void)
{
}
__WEAKDEF void FMAC_3_IrqHandler(void)
{
}
__WEAKDEF void FMAC_4_IrqHandler(void)
{
}
__WEAKDEF void DCU_1_IrqHandler(void)
{
}
__WEAKDEF void DCU_2_IrqHandler(void)
{
}
__WEAKDEF void DCU_3_IrqHandler(void)
{
}
__WEAKDEF void DCU_4_IrqHandler(void)
{
}
__WEAKDEF void DCU_5_IrqHandler(void)
{
}
__WEAKDEF void DCU_6_IrqHandler(void)
{
}
__WEAKDEF void DCU_7_IrqHandler(void)
{
}
__WEAKDEF void DCU_8_IrqHandler(void)
{
}
__WEAKDEF void TMR0_1_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR0_1_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR0_2_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR0_2_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_OvfB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_OvfB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_OvfB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_OvfB_IrqHandler(void)
{
}
__WEAKDEF void RTC_TimeStamp0_IrqHandler(void)
{
}
__WEAKDEF void RTC_TimeStamp1_IrqHandler(void)
{
}
__WEAKDEF void RTC_Alarm_IrqHandler(void)
{
}
__WEAKDEF void RTC_Period_IrqHandler(void)
{
}
__WEAKDEF void CLK_XtalStop_IrqHandler(void)
{
}
__WEAKDEF void SWDT_IrqHandler(void)
{
}
__WEAKDEF void WDT_IrqHandler(void)
{
}
__WEAKDEF void PWC_WakeupTimer_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Cmp2_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Cmp3_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Cmp4_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR0_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR1_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR2_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR3_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR4_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR5_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR6_IrqHandler(void)
{
}
__WEAKDEF void USART_1_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_1_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_1_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_1_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART_2_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_2_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_2_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_2_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART_3_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_3_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_3_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_4_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_4_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_4_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_5_LinBreakField_IrqHandler(void)
{
}
__WEAKDEF void USART_5_LinWakeup_IrqHandler(void)
{
}
__WEAKDEF void USART_5_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_5_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_5_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_5_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_6_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_6_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_6_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_6_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_6_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART_7_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_7_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_7_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_7_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_7_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART_8_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_8_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_8_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_8_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_9_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_9_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_9_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_9_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_10_LinBreakField_IrqHandler(void)
{
}
__WEAKDEF void USART_10_LinWakeup_IrqHandler(void)
{
}
__WEAKDEF void USART_10_RxErr_IrqHandler(void)
{
}
__WEAKDEF void USART_10_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void USART_10_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART_10_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_1_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_1_Err_IrqHandler(void)
{
}
__WEAKDEF void SPI_1_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI_2_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_2_Err_IrqHandler(void)
{
}
__WEAKDEF void SPI_2_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI_3_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_3_Err_IrqHandler(void)
{
}
__WEAKDEF void SPI_3_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI_4_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_4_Err_IrqHandler(void)
{
}
__WEAKDEF void SPI_4_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI_5_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_5_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_5_Err_IrqHandler(void)
{
}
__WEAKDEF void SPI_5_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI_6_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void SPI_6_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI_6_Err_IrqHandler(void)
{
}
__WEAKDEF void SPI_6_Idle_IrqHandler(void)
{
}
__WEAKDEF void CAN_1_IrqHandler(void)
{
}
__WEAKDEF void CAN_2_IrqHandler(void)
{
}
__WEAKDEF void I2S_1_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S_1_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S_1_Err_IrqHandler(void)
{
}
__WEAKDEF void I2S_2_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S_2_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S_2_Err_IrqHandler(void)
{
}
__WEAKDEF void I2S_3_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S_3_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S_3_Err_IrqHandler(void)
{
}
__WEAKDEF void I2S_4_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S_4_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S_4_Err_IrqHandler(void)
{
}
__WEAKDEF void USBFS_Global_IrqHandler(void)
{
}
__WEAKDEF void SDIOC_1_Normal_IrqHandler(void)
{
}
__WEAKDEF void SDIOC_1_Error_IrqHandler(void)
{
}
__WEAKDEF void SDIOC_2_Normal_IrqHandler(void)
{
}
__WEAKDEF void SDIOC_2_Error_IrqHandler(void)
{
}
__WEAKDEF void ETH_Global_IrqHandler(void)
{
}
__WEAKDEF void ETH_Wakeup_IrqHandler(void)
{
}
__WEAKDEF void I2C_1_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_1_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_1_Err_IrqHandler(void)
{
}
__WEAKDEF void I2C_2_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_2_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_2_Err_IrqHandler(void)
{
}
__WEAKDEF void I2C_3_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_3_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_3_Err_IrqHandler(void)
{
}
__WEAKDEF void I2C_4_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_4_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_4_Err_IrqHandler(void)
{
}
__WEAKDEF void I2C_5_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_5_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_5_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_5_Err_IrqHandler(void)
{
}
__WEAKDEF void I2C_6_RxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_6_TxEnd_IrqHandler(void)
{
}
__WEAKDEF void I2C_6_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C_6_Err_IrqHandler(void)
{
}

__WEAKDEF void PWC_Pvd1_IrqHandler(void)
{
}
__WEAKDEF void PWC_Pvd2_IrqHandler(void)
{
}
__WEAKDEF void FCM_Err_IrqHandler(void)
{
}
__WEAKDEF void FCM_End_IrqHandler(void)
{
}
__WEAKDEF void FCM_Ovf_IrqHandler(void)
{
}
__WEAKDEF void CTC_Udf_IrqHandler(void)
{
}
__WEAKDEF void CTC_Ovf_IrqHandler(void)
{
}
__WEAKDEF void ADC_1_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC_1_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC_1_Cmp0_IrqHandler(void)
{
}
__WEAKDEF void ADC_1_Cmp1Ind_IrqHandler(void)
{
}
__WEAKDEF void ADC_1_Cmp1Comb_IrqHandler(void)
{
}
__WEAKDEF void ADC_2_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC_2_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC_2_Cmp0_IrqHandler(void)
{
}
__WEAKDEF void ADC_2_Cmp1Ind_IrqHandler(void)
{
}
__WEAKDEF void ADC_2_Cmp1Comb_IrqHandler(void)
{
}
__WEAKDEF extern void ADC_3_SeqA_IrqHandler(void)
{
}
__WEAKDEF extern void ADC_3_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC_3_Cmp0_IrqHandler(void)
{
}
__WEAKDEF void ADC_3_Cmp1Ind_IrqHandler(void)
{
}
__WEAKDEF void ADC_3_Cmp1Comb_IrqHandler(void)
{
}
__WEAKDEF void NFC_IrqHandler(void)
{
}
/**
 * @}
 */

#endif /* DDL_INTERRUPTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
