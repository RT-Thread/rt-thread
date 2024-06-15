/**
 *******************************************************************************
 * @file  hc32_ll_interrupts.c
 * @brief This file provides firmware functions to manage the Interrupt Controller
 *        (INTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Delete comment code
   2023-01-15       CDT             Add macro-definition: EIRQFR_REG/NMIENR_REG/INTWKEN_REG
   2023-06-30       CDT             IRQxxx_Handler add __DSB for Arm Errata 838869
   2023-09-30       CDT             Modify micro define EIRQCFR_REG and EIRQFR_REG base RM
                                    Remove space line
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
#define IRQ_NUM_MAX             (128U)
#define IRQn_MIN                (INT000_IRQn)
#define IRQn_MAX                (INT127_IRQn)
#define IRQn_OFFSET             (0U)
#define EXTINT_CH_NUM_MAX       (16U)
#define EIRQCFR_REG             (CM_INTC->EIFCR)
#define EIRQFR_REG              (CM_INTC->EIFR)
#define NMIENR_REG              (CM_INTC->NMIENR)
#define NMICFR_REG              (CM_INTC->NMICFR)
#define INTSEL_REG              (uint32_t)(&CM_INTC->SEL0)
#define INTWKEN_REG             (CM_INTC->WUPEN)
#define INTSEL_RST_VALUE        (0x1FFUL)
#define IRQ_GRP_MOD             (32UL)
#define IRQ_GRP_NUM             (6UL)
#define IRQ_GRP_LOW             (32UL)
#define IRQ_GRP_HIGH            (37UL)
#define IRQ_GRP_BASE            (32UL)

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
        /* IRQ032~127 whether out of range */
        if ((((((uint32_t)pstcIrqSignConfig->enIntSrc / IRQ_GRP_MOD) * IRQ_GRP_NUM + IRQ_GRP_LOW) >             \
              (uint32_t)pstcIrqSignConfig->enIRQn)                                                    ||        \
             ((((uint32_t)pstcIrqSignConfig->enIntSrc / IRQ_GRP_MOD) * IRQ_GRP_NUM + IRQ_GRP_HIGH) <            \
              (uint32_t)pstcIrqSignConfig->enIRQn))                                                   &&        \
            ((uint32_t)pstcIrqSignConfig->enIRQn >= IRQ_GRP_BASE)) {
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
    stcIrqSignConfig.enIntSrc = (en_int_src_t)(__CLZ(__RBIT(u32Ch)));
    /* Callback function */
    stcIrqSignConfig.pfnCallback = pfnCallback;
    (void)INTC_IrqSignIn(&stcIrqSignConfig);

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
                EIRQCRVal |= pstcExtIntInit->u32FilterB;
                WRITE_REG32(CM_INTC->NOCCR, pstcExtIntInit->u32FilterBClock);
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
 * @brief  Interrupt No.016 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ016_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT016_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.017 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ017_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT017_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.018 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ018_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT018_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.019 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ019_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT019_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.020 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ020_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT020_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.021 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ021_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT021_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.022 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ022_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT022_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.023 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ023_Handler(void)
{
    m_apfnIrqHandler[(uint32_t)INT023_IRQn - IRQn_OFFSET]();
    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.024 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ024_Handler(void)
{
    m_apfnIrqHandler[INT024_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.025 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ025_Handler(void)
{
    m_apfnIrqHandler[INT025_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.026 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ026_Handler(void)
{
    m_apfnIrqHandler[INT026_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.027 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ027_Handler(void)
{
    m_apfnIrqHandler[INT027_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.028 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ028_Handler(void)
{
    m_apfnIrqHandler[INT028_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.029 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ029_Handler(void)
{
    m_apfnIrqHandler[INT029_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.030 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ030_Handler(void)
{
    m_apfnIrqHandler[INT030_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.031 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ031_Handler(void)
{
    m_apfnIrqHandler[INT031_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.032 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ032_Handler(void)
{
    m_apfnIrqHandler[INT032_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.033 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ033_Handler(void)
{
    m_apfnIrqHandler[INT033_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.034 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ034_Handler(void)
{
    m_apfnIrqHandler[INT034_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.035 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ035_Handler(void)
{
    m_apfnIrqHandler[INT035_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.036 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ036_Handler(void)
{
    m_apfnIrqHandler[INT036_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.037 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ037_Handler(void)
{
    m_apfnIrqHandler[INT037_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.038 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ038_Handler(void)
{
    m_apfnIrqHandler[INT038_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.039 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ039_Handler(void)
{
    m_apfnIrqHandler[INT039_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.040 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ040_Handler(void)
{
    m_apfnIrqHandler[INT040_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.041 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ041_Handler(void)
{
    m_apfnIrqHandler[INT041_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.042 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ042_Handler(void)
{
    m_apfnIrqHandler[INT042_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.043 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ043_Handler(void)
{
    m_apfnIrqHandler[INT043_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.044 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ044_Handler(void)
{
    m_apfnIrqHandler[INT044_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.045 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ045_Handler(void)
{
    m_apfnIrqHandler[INT045_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.046 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ046_Handler(void)
{
    m_apfnIrqHandler[INT046_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.047 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ047_Handler(void)
{
    m_apfnIrqHandler[INT047_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.048 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ048_Handler(void)
{
    m_apfnIrqHandler[INT048_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.049 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ049_Handler(void)
{
    m_apfnIrqHandler[INT049_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.050 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ050_Handler(void)
{
    m_apfnIrqHandler[INT050_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.051 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ051_Handler(void)
{
    m_apfnIrqHandler[INT051_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.052 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ052_Handler(void)
{
    m_apfnIrqHandler[INT052_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.053 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ053_Handler(void)
{
    m_apfnIrqHandler[INT053_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.054 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ054_Handler(void)
{
    m_apfnIrqHandler[INT054_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.055 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ055_Handler(void)
{
    m_apfnIrqHandler[INT055_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.056 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ056_Handler(void)
{
    m_apfnIrqHandler[INT056_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.057 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ057_Handler(void)
{
    m_apfnIrqHandler[INT057_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.058 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ058_Handler(void)
{
    m_apfnIrqHandler[INT058_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.059 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ059_Handler(void)
{
    m_apfnIrqHandler[INT059_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.060 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ060_Handler(void)
{
    m_apfnIrqHandler[INT060_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.061 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ061_Handler(void)
{
    m_apfnIrqHandler[INT061_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.062 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ062_Handler(void)
{
    m_apfnIrqHandler[INT062_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.063 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ063_Handler(void)
{
    m_apfnIrqHandler[INT063_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.064 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ064_Handler(void)
{
    m_apfnIrqHandler[INT064_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.065 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ065_Handler(void)
{
    m_apfnIrqHandler[INT065_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.066 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ066_Handler(void)
{
    m_apfnIrqHandler[INT066_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.067 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ067_Handler(void)
{
    m_apfnIrqHandler[INT067_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.068 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ068_Handler(void)
{
    m_apfnIrqHandler[INT068_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.069 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ069_Handler(void)
{
    m_apfnIrqHandler[INT069_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.070 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ070_Handler(void)
{
    m_apfnIrqHandler[INT070_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.071 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ071_Handler(void)
{
    m_apfnIrqHandler[INT071_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.072 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ072_Handler(void)
{
    m_apfnIrqHandler[INT072_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.073 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ073_Handler(void)
{
    m_apfnIrqHandler[INT073_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.074 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ074_Handler(void)
{
    m_apfnIrqHandler[INT074_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.075 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ075_Handler(void)
{
    m_apfnIrqHandler[INT075_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.076 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ076_Handler(void)
{
    m_apfnIrqHandler[INT076_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.077 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ077_Handler(void)
{
    m_apfnIrqHandler[INT077_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.078 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ078_Handler(void)
{
    m_apfnIrqHandler[INT078_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.079 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ079_Handler(void)
{
    m_apfnIrqHandler[INT079_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.080 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ080_Handler(void)
{
    m_apfnIrqHandler[INT080_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.081 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ081_Handler(void)
{
    m_apfnIrqHandler[INT081_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.082 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ082_Handler(void)
{
    m_apfnIrqHandler[INT082_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.083 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ083_Handler(void)
{
    m_apfnIrqHandler[INT083_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.084 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ084_Handler(void)
{
    m_apfnIrqHandler[INT084_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.085 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ085_Handler(void)
{
    m_apfnIrqHandler[INT085_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.086 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ086_Handler(void)
{
    m_apfnIrqHandler[INT086_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.087 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ087_Handler(void)
{
    m_apfnIrqHandler[INT087_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.088 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ088_Handler(void)
{
    m_apfnIrqHandler[INT088_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.089 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ089_Handler(void)
{
    m_apfnIrqHandler[INT089_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.090 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ090_Handler(void)
{
    m_apfnIrqHandler[INT090_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.091 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ091_Handler(void)
{
    m_apfnIrqHandler[INT091_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.092 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ092_Handler(void)
{
    m_apfnIrqHandler[INT092_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.093 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ093_Handler(void)
{
    m_apfnIrqHandler[INT093_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.094 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ094_Handler(void)
{
    m_apfnIrqHandler[INT094_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.095 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ095_Handler(void)
{
    m_apfnIrqHandler[INT095_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.096 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ096_Handler(void)
{
    m_apfnIrqHandler[INT096_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.097 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ097_Handler(void)
{
    m_apfnIrqHandler[INT097_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.098 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ098_Handler(void)
{
    m_apfnIrqHandler[INT098_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.099 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ099_Handler(void)
{
    m_apfnIrqHandler[INT099_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.100 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ100_Handler(void)
{
    m_apfnIrqHandler[INT100_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.101 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ101_Handler(void)
{
    m_apfnIrqHandler[INT101_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.102 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ102_Handler(void)
{
    m_apfnIrqHandler[INT102_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.103 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ103_Handler(void)
{
    m_apfnIrqHandler[INT103_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.104 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ104_Handler(void)
{
    m_apfnIrqHandler[INT104_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.105 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ105_Handler(void)
{
    m_apfnIrqHandler[INT105_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.106 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ106_Handler(void)
{
    m_apfnIrqHandler[INT106_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.107 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ107_Handler(void)
{
    m_apfnIrqHandler[INT107_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.108 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ108_Handler(void)
{
    m_apfnIrqHandler[INT108_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.109 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ109_Handler(void)
{
    m_apfnIrqHandler[INT109_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.110 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ110_Handler(void)
{
    m_apfnIrqHandler[INT110_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.111 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ111_Handler(void)
{
    m_apfnIrqHandler[INT111_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.112 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ112_Handler(void)
{
    m_apfnIrqHandler[INT112_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.113 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ113_Handler(void)
{
    m_apfnIrqHandler[INT113_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.114 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ114_Handler(void)
{
    m_apfnIrqHandler[INT114_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.115 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ115_Handler(void)
{
    m_apfnIrqHandler[INT115_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.116 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ116_Handler(void)
{
    m_apfnIrqHandler[INT116_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.117 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ117_Handler(void)
{
    m_apfnIrqHandler[INT117_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.118 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ118_Handler(void)
{
    m_apfnIrqHandler[INT118_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.119 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ119_Handler(void)
{
    m_apfnIrqHandler[INT119_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.120 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ120_Handler(void)
{
    m_apfnIrqHandler[INT120_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.121 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ121_Handler(void)
{
    m_apfnIrqHandler[INT121_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.122 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ122_Handler(void)
{
    m_apfnIrqHandler[INT122_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.123 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ123_Handler(void)
{
    m_apfnIrqHandler[INT123_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.124 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ124_Handler(void)
{
    m_apfnIrqHandler[INT124_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.125 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ125_Handler(void)
{
    m_apfnIrqHandler[INT125_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.126 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ126_Handler(void)
{
    m_apfnIrqHandler[INT126_IRQn]();

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.127 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ127_Handler(void)
{
    m_apfnIrqHandler[INT127_IRQn]();

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
