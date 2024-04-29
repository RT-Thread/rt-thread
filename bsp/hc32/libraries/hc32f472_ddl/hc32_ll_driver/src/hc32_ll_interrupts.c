/**
 *******************************************************************************
 * @file  hc32_ll_interrupts.c
 * @brief This file provides firmware functions to manage the Interrupt Controller
 *        (INTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             IRQxxx_Handler add __DSB for Arm Errata 838869
   2023-09-30       CDT             Remove space line
   2023-12-15       CDT             Add API INTC_GetIntSrcState()
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "hc32_ll_interrupts.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_INTERRUPTS INTERRUPTS
 * @brief INTC Driver Library
 * @{
 */

#if (LL_INTERRUPTS_ENABLE == DDL_ON)

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
#define IRQ_NUM_MAX             (16U)
#define IRQn_MIN                (INT000_IRQn)
#define IRQn_MAX                (INT015_IRQn)
#define IRQn_OFFSET             (0U)
#define EXTINT_CH_NUM_MAX       (16U)
#define EIRQCFR_REG             (CM_INTC->EIFCR)
#define EIRQFR_REG              (CM_INTC->EIFR)
#define NMIENR_REG              (CM_INTC->NMIER)
#define NMICFR_REG              (CM_INTC->NMIFCR)
#define INTSEL_REG              (uint32_t)(&CM_INTC->INTSEL0)
#define INTWKEN_REG             (CM_INTC->WKEN)
#define INTSEL_RST_VALUE        (0x1FFUL)
#define INTEN_REG_MOD           (32U)

/**
 * @defgroup INTC_Check_Parameters_Validity INTC Check Parameters Validity
 * @{
 */
/*! Parameter validity check for wakeup source from stop mode. */
#define IS_INTC_WKUP_SRC(src)                                                   \
(   ((src) != 0x00UL)                           &&                              \
    (((src) | INTC_WUPEN_ALL) == INTC_WUPEN_ALL))

/*! Parameter validity check for event index. */
#define IS_INTC_EVT(event)                                                      \
(   ((event) != 0x00UL)                         &&                              \
    (((event) | INTC_EVT_ALL) == INTC_EVT_ALL))

/*! Parameter validity check for interrupt index. */
#define IS_INTC_INT(it)                                                         \
(   ((it) != 0x00UL)                            &&                              \
    (((it) | INTC_INT_ALL) == INTC_INT_ALL))

/*! Parameter validity check for software interrupt index. */
#define IS_INTC_SWI(swi)                                                        \
(   ((swi) != 0x00UL)                           &&                              \
    (((swi) | SWINT_ALL) == SWINT_ALL))

/*! Parameter validity check for NMI trigger source. */
#define IS_NMI_SRC(src)                                                         \
(   ((src) != 0x00UL)                           &&                              \
    (((src) | NMI_SRC_ALL) == NMI_SRC_ALL))

/*! Parameter validity check for EXTINT filter A function. */
#define IS_EXTINT_FAE(fae)                                                      \
(   ((fae) == EXTINT_FILTER_OFF)                ||                              \
    ((fae) == EXTINT_FILTER_ON))

/*! Parameter validity check for EXTINT filter A clock division. */
#define IS_EXTINT_FACLK(faclk)                                                  \
(   ((faclk) == EXTINT_FCLK_DIV1)               ||                              \
    ((faclk) == EXTINT_FCLK_DIV8)               ||                              \
    ((faclk) == EXTINT_FCLK_DIV32)              ||                              \
    ((faclk) == EXTINT_FCLK_DIV64))

/*! Parameter validity check for EXTINT filter B function. */
#define IS_NMI_EXTINT_FBE(fbe)                                                  \
(   ((fbe) == NMI_EXTINT_FILTER_B_OFF)          ||                              \
    ((fbe) == NMI_EXTINT_FILTER_B_ON))

/*! Parameter validity check for EXTINT filter B time. */
#define IS_NMI_EXTINT_FBTIME(fbtime)                                            \
(   ((fbtime) == NMI_EXTINT_FCLK_B_500NS)       ||                              \
    ((fbtime) == NMI_EXTINT_FCLK_B_1US)         ||                              \
    ((fbtime) == NMI_EXTINT_FCLK_B_2US)         ||                              \
    ((fbtime) == NMI_EXTINT_FCLK_B_4US))

/*! Parameter validity check for EXTINT trigger edge. */
#define IS_EXTINT_TRIG(trigger)                                                 \
(   ((trigger) == EXTINT_TRIG_LOW)              ||                              \
    ((trigger) == EXTINT_TRIG_RISING)           ||                              \
    ((trigger) == EXTINT_TRIG_FALLING)          ||                              \
    ((trigger) == EXTINT_TRIG_BOTH))

/*! Parameter validity check for EXTINT channel. */
#define IS_EXTINT_CH(ch)                                                        \
(   ((ch) != 0x00UL)                            &&                              \
    (((ch) | EXTINT_CH_ALL) == EXTINT_CH_ALL))

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
 * @defgroup INTC_Local_Variable INTC Local Variable
 * @{
 */
static func_ptr_t m_apfnIrqHandler[IRQ_NUM_MAX] = {NULL};
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
 *   @arg  enIRQn: can be any value from IRQn_MIN ~ IRQn_MAX for different product
 *   @arg  pfnCallback: Callback function
 * @retval int32_t:
 *           - LL_OK: IRQ register successfully
 *           - LL_ERR_INVD_PARAM: IRQ No. and Peripheral Int source are not match; NULL pointer.
 *           - LL_ERR_UNINIT: Specified IRQ entry was signed before.
 */
int32_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig)
{
    __IO uint32_t *INTC_SELx;
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcIrqSignConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(pstcIrqSignConfig->enIntSrc <= INT_SRC_MAX);
        if (pstcIrqSignConfig->enIRQn > INT015_IRQn) {
            i32Ret = LL_ERR_INVD_PARAM;
        }

        else {
            INTC_SELx = (__IO uint32_t *)(INTSEL_REG + (4U * (uint32_t)(pstcIrqSignConfig->enIRQn)));
            /* for MISRAC2004-12.4 */
            if (INTSEL_RST_VALUE == ((*INTC_SELx) & INTSEL_RST_VALUE)) {
                WRITE_REG32(*INTC_SELx, pstcIrqSignConfig->enIntSrc);
                m_apfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
            } else if ((uint32_t)(pstcIrqSignConfig->enIntSrc) == ((*INTC_SELx) & INTSEL_RST_VALUE)) {
                m_apfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
            } else {
                i32Ret = LL_ERR_UNINIT;
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  IRQ sign out function
 * @param  [in] enIRQn: can be any value from IRQn_MIN ~ IRQn_MAX for different product
 * @retval int32_t:
 *           - LL_OK: IRQ sign out successfully
 *           - LL_ERR_INVD_PARAM: IRQ No. is out of range
 */
int32_t INTC_IrqSignOut(IRQn_Type enIRQn)
{
    __IO uint32_t *INTC_SELx;
    int32_t i32Ret = LL_OK;

    if ((enIRQn < IRQn_MIN) || (enIRQn > IRQn_MAX)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        INTC_SELx = (__IO uint32_t *)(INTSEL_REG + (4UL * (uint32_t)enIRQn));
        WRITE_REG32(*INTC_SELx, INTSEL_RST_VALUE);
        m_apfnIrqHandler[(uint8_t)enIRQn - IRQn_OFFSET] = NULL;
    }
    return i32Ret;
}

/**
 * @brief  Stop mode wake-up source configure
 * @param  [in] u32WakeupSrc: Wake-up source, @ref INTC_Stop_Wakeup_Source_Sel for details
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void INTC_WakeupSrcCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_WKUP_SRC(u32WakeupSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(INTWKEN_REG, u32WakeupSrc);
    } else {
        CLR_REG32_BIT(INTWKEN_REG, u32WakeupSrc);
    }
}

/**
 * @brief  Event or Interrupt output configure
 * @param  [in] u32Event: Event index, @ref INTC_Event_Channel_Sel for details
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_EVT(u32Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_INTC->EVTER, u32Event);
    } else {
        CLR_REG32_BIT(CM_INTC->EVTER, u32Event);
    }
}

/**
 * @brief  Interrupt function configure
 * @param  [in] u32Int: Interrupt index, @ref INT_Channel_Sel for details
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_INT(u32Int));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_INTC->IER, u32Int);
    } else {
        CLR_REG32_BIT(CM_INTC->IER, u32Int);
    }
}

/**
 * @brief  Software Interrupt initialize function
 * @param  [in] u32Ch: Software Interrupt channel, @ref SWINT_Channel_Sel for details
 * @param  [in] pfnCallback: Callback function
 * @param  [in] u32Priority: Software interrupt priority
 * @retval None
 */
void INTC_SWIntInit(uint32_t u32Ch, const func_ptr_t pfnCallback, uint32_t u32Priority)
{
    stc_irq_signin_config_t stcIrqSignConfig;

    stcIrqSignConfig.enIRQn = (IRQn_Type)(__CLZ(__RBIT(u32Ch)));
    (void)(pfnCallback);

    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, u32Priority);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}

/**
 * @brief  Software Interrupt function configure
 * @param  [in] u32SWInt: Software Interrupt channel, @ref SWINT_Channel_Sel for details
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void INTC_SWIntCmd(uint32_t u32SWInt, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_SWI(u32SWInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_INTC->SWIER, u32SWInt);
    } else {
        CLR_REG32_BIT(CM_INTC->SWIER, u32SWInt);
    }
}

/**
 * @brief  Initialize NMI. Fill each pstcNmiInit with default value
 * @param  [in] pstcNmiInit: Pointer to a stc_nmi_init_t structure that
 *                             contains configuration information.
 * @retval int32_t:
 *           - LL_OK: NMI structure initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t NMI_StructInit(stc_nmi_init_t *pstcNmiInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcNmiInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Configure to default value */
        pstcNmiInit->u32Src        = 0UL;
    }
    return i32Ret;
}

/**
 * @brief  Initialize NMI.
 * @param  [in] pstcNmiInit: Pointer to a pstcNmiInit structure that
 *                             contains configuration information.
 * @retval int32_t:
 *           - LL_OK: NMI initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t NMI_Init(const stc_nmi_init_t *pstcNmiInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcNmiInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Parameter validity checking */
        DDL_ASSERT(IS_NMI_SRC(pstcNmiInit->u32Src));
        /* Clear all NMI trigger source before set */
        WRITE_REG32(NMICFR_REG, NMI_SRC_ALL);

        /* NMI trigger source configure */
        WRITE_REG32(NMIENR_REG, pstcNmiInit->u32Src);

    }
    return i32Ret;
}

/**
 * @brief  Get NMI trigger source
 * @param  [in] u32Src: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t NMI_GetNmiStatus(uint32_t u32Src)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32Src));

    return (((READ_REG32(CM_INTC->NMIFR) & u32Src)) != 0UL) ? SET : RESET;
}

/**
 * @brief  Set NMI trigger source
 * @param  [in] u32Src: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void NMI_NmiSrcCmd(uint32_t u32Src, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32Src));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(NMIENR_REG, u32Src);
    } else {
        CLR_REG32_BIT(NMIENR_REG, u32Src);
    }
}

/**
 * @brief  Clear specified NMI trigger source
 * @param  [in] u32Src: NMI trigger source, @ref NMI_TriggerSrc_Sel for diff. MCU in details
 * @retval None
 */
void NMI_ClearNmiStatus(uint32_t u32Src)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32Src));

    SET_REG32_BIT(NMICFR_REG, u32Src);
}

/**
 * @brief  Initialize External interrupt.
 * @param  [in] u32Ch: ExtInt channel.
 * @param  [in] pstcExtIntInit: Pointer to a stc_extint_init_t structure that
 *                             contains configuration information.
 * @retval int32_t:
 *           - LL_OK:  EXTINT initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t EXTINT_Init(uint32_t u32Ch, const stc_extint_init_t *pstcExtIntInit)
{
    uint8_t u8ExtIntPos;
    int32_t i32Ret = LL_OK;
    uint32_t EIRQCRVal;
    __IO uint32_t *EIRQCRx;

    /* Check if pointer is NULL */
    if (NULL == pstcExtIntInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Parameter validity checking */
        DDL_ASSERT(IS_EXTINT_CH(u32Ch));
        DDL_ASSERT(IS_EXTINT_FAE(pstcExtIntInit->u32Filter));
        DDL_ASSERT(IS_EXTINT_FACLK(pstcExtIntInit->u32FilterClock));
        DDL_ASSERT(IS_EXTINT_TRIG(pstcExtIntInit->u32Edge));
        DDL_ASSERT(IS_NMI_EXTINT_FBE(pstcExtIntInit->u32FilterB));
        DDL_ASSERT(IS_NMI_EXTINT_FBTIME(pstcExtIntInit->u32FilterBClock));
        for (u8ExtIntPos = 0U; u8ExtIntPos < EXTINT_CH_NUM_MAX; u8ExtIntPos++) {
            if (0UL != (u32Ch & (1UL << u8ExtIntPos))) {
                EIRQCRVal = pstcExtIntInit->u32Filter | pstcExtIntInit->u32FilterClock  |   \
                            pstcExtIntInit->u32Edge;
                EIRQCRVal |= (pstcExtIntInit->u32FilterB | pstcExtIntInit->u32FilterBClock);
                EIRQCRx = (__IO uint32_t *)((uint32_t)&CM_INTC->EIRQCR0 + 4UL * u8ExtIntPos);
                WRITE_REG32(*EIRQCRx, EIRQCRVal);
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  Initialize ExtInt. Fill each pstcExtIntInit with default value
 * @param  [in] pstcExtIntInit: Pointer to a stc_extint_init_t structure
 *                              that contains configuration information.
 * @retval int32_t:
 *           - LL_OK: EXTINT structure initialize successful
 *           - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t EXTINT_StructInit(stc_extint_init_t *pstcExtIntInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcExtIntInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Configure to default value */
        pstcExtIntInit->u32Filter      = EXTINT_FILTER_OFF;
        pstcExtIntInit->u32FilterClock = EXTINT_FCLK_DIV1;
        pstcExtIntInit->u32Edge        = EXTINT_TRIG_FALLING;
        pstcExtIntInit->u32FilterB      = NMI_EXTINT_FILTER_B_OFF;
        pstcExtIntInit->u32FilterBClock = NMI_EXTINT_FCLK_B_500NS;
    }
    return i32Ret;
}

/**
 * @brief  Clear specified External interrupt trigger source
 * @param  [in] u32ExtIntCh: External interrupt channel, @ref EXTINT_Channel_Sel for details
 * @retval None
 */
void EXTINT_ClearExtIntStatus(uint32_t u32ExtIntCh)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXTINT_CH(u32ExtIntCh));

    SET_REG32_BIT(EIRQCFR_REG, u32ExtIntCh);
}

/**
 * @brief  Get specified External interrupt trigger source
 * @param  [in] u32ExtIntCh: External interrupt channel, @ref EXTINT_Channel_Sel for details
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EXTINT_GetExtIntStatus(uint32_t u32ExtIntCh)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXTINT_CH(u32ExtIntCh));

    return ((READ_REG16(EIRQFR_REG) & u32ExtIntCh) != 0U) ? SET : RESET;
}

/**
 * @brief  Interrupt source interrupt function configure
 * @param  [in] enIntSrc: Interrupt source, can be any value @ref en_int_src_t
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void INTC_IntSrcCmd(en_int_src_t enIntSrc, en_functional_state_t enNewState)
{
    __IO uint32_t *INTENx;

    /* Parameter validity checking */
    DDL_ASSERT(enIntSrc <= INT_SRC_MAX);
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    INTENx = (__IO uint32_t *)((uint32_t)&CM_INTC->INTEN0 + 4UL * ((uint32_t)enIntSrc / INTEN_REG_MOD));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(*INTENx, 1UL << ((uint32_t)enIntSrc & 0x1FU));
    } else {
        CLR_REG32_BIT(*INTENx, 1UL << ((uint32_t)enIntSrc & 0x1FU));
    }
}

/**
 * @brief  Get interrupt source interrupt status
 * @param  [in] enIntSrc: Interrupt source, can be any value @ref en_int_src_t
 * @retval An @ref en_functional_state_t enumeration type value.
 */
en_functional_state_t INTC_GetIntSrcState(en_int_src_t enIntSrc)
{
    __IO uint32_t *INTENx;

    /* Parameter validity checking */
    DDL_ASSERT(enIntSrc <= INT_SRC_MAX);

    INTENx = (__IO uint32_t *)((uint32_t)&CM_INTC->INTEN0 + 4UL * ((uint32_t)enIntSrc / INTEN_REG_MOD));

    return ((*INTENx & (1UL << ((uint32_t)enIntSrc & 0x1FU))) != 0UL) ? ENABLE : DISABLE;
}

/**
 * @brief  Interrupt No.000 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ000_Handler(void)
{
    m_apfnIrqHandler[INT000_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.001 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ001_Handler(void)
{
    m_apfnIrqHandler[INT001_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.002 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ002_Handler(void)
{
    m_apfnIrqHandler[INT002_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.003 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ003_Handler(void)
{
    m_apfnIrqHandler[INT003_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.004 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ004_Handler(void)
{
    m_apfnIrqHandler[INT004_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.005 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ005_Handler(void)
{
    m_apfnIrqHandler[INT005_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.006 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ006_Handler(void)
{
    m_apfnIrqHandler[INT006_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.007 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ007_Handler(void)
{
    m_apfnIrqHandler[INT007_IRQn]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.008 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ008_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT008_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.009 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ009_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT009_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.010 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ010_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT010_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.011 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ011_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT011_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.012 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ012_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT012_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.013 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ013_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT013_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.014 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ014_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT014_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.015 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ015_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT015_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @}
 */

#endif /* LL_INTERRUPTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
