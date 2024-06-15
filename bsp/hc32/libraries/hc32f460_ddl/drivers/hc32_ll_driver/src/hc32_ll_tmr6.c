/**
 *******************************************************************************
 * @file  hc32_ll_tmr6.c
 * @brief This file provides firmware functions to manage the TMR6(TMR6).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Define variable in the beginning of the function
   2023-01-15       CDT             Modify structure stc_timer6_init_t to stc_tmr6_init_t
                                    Modify API TMR6_SetFilterClockDiv()
   2023-06-30       CDT             Modify typo
                                    Delete union in stc_tmr6_init_t structure
                                    Modify API TMR6_GetCountDir()
   2023-09-30       CDT             Modify API TMR6_Init()
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
#include "hc32_ll_tmr6.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_TMR6 TMR6
 * @brief TMR6 Driver Library
 * @{
 */

#if (LL_TMR6_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR6_Local_Macros TMR6 Local Macros
 * @{
 */

/* Timer6 registers reset value */
#define TMR6_REG_RST_VALUE_U32              (0xFFFFFFFFUL)
#define TMR6_REG_RST_VALUE_U16              (0xFFFFU)
#define TMR6_REG_GCONR_RST_VALUE            (0x00000100UL)

/* Define for BCONR register configuration */
#define BCONR_FUNC_CMD_MASK                 (0x01UL)
#define BCONR_GEN_CFG_MASK                  (0x00000002UL)
#define BCONR_GEN_CFG_CHB_OFS               (0x02UL)
#define BCONR_PERIOD_CFG_MASK               (0x00000002UL)
#define BCONR_PERIOD_CFG_OFS                (0x08UL)
#define BCONR_SPECIAL_CFG_MASK              (0x00000032UL)
#define BCONR_SPECIAL_CFG_CHA_OFS           (0x10UL)
#define BCONR_SPECIAL_CFG_TRIG_CHA_OFS      (0x12UL)
#define BCONR_SPECIAL_CFG_CHB_OFS           (0x18UL)
#define BCONR_SPECIAL_CFG_TRIG_CHB_OFS      (0x1AUL)

/* Define mask value for PWM output configuration for  register */
#define PCONR_REG_CHB_SHIFT                 (16U)
#define PCONR_REG_CHA_OUTPUT_CFG_MASK       (0x000000FFUL)
#define PCONR_REG_CHB_OUTPUT_CFG_MASK       (PCONR_REG_CHA_OUTPUT_CFG_MASK << PCONR_REG_CHB_SHIFT)
#define PCONR_REG_POLARITY_START_STOP_MASK  (0x01UL)
#define PCONR_REG_POLARITY_MASK             (0x03UL)

/* Define mask value for GCONR register */
#define TMR6_INIT_MASK                      (TMR6_GCONR_DIR | TMR6_GCONR_MODE | TMR6_GCONR_CKDIV)
#define TMR6_ZMASK_CFG_MASK                 (TMR6_GCONR_ZMSKVAL | TMR6_GCONR_ZMSKPOS | TMR6_GCONR_ZMSKREV)

/**
 * @defgroup TMR6_Check_Param_Validity TMR6 Check Parameters Validity
 * @{
 */

/*! Parameter valid check for normal timer6 unit */
#define IS_VALID_TMR6_UNIT(x)                                                  \
(   ((x) == CM_TMR6_1)                          ||                             \
    ((x) == CM_TMR6_2)                          ||                             \
    ((x) == CM_TMR6_3))

/*! Parameter valid check for timer6 count source */
#define IS_TMR6_CNT_SRC(x)                                                     \
(   ((x) == TMR6_CNT_SRC_SW)                    ||                             \
    ((x) == TMR6_CNT_SRC_HW))

/*! Parameter valid check for interrupt source configuration */
#define IS_VALID_IRQ(x)                                                        \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_INT_ALL) == TMR6_INT_ALL))

/*! Parameter valid check for status bit read */
#define IS_VALID_GET_FLAG(x)                                                   \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_FLAG_ALL) == TMR6_FLAG_ALL))

/*! Parameter valid check for status bit clear */
#define IS_VALID_CLR_FLAG(x)                                                   \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_FLAG_CLR_ALL) == TMR6_FLAG_CLR_ALL))

/*! Parameter valid check for period register */
#define IS_VALID_PERIOD_REG(x)                                                 \
(   (x) <= TMR6_PERIOD_REG_C)

/*! Parameter valid check for general compare register */
#define IS_VALID_CMP_REG(x)                                                    \
(   (x) <= TMR6_CMP_REG_F)

/*! Parameter valid check for general/special compare channel */
#define IS_VALID_CNT_CH(x)                                                     \
(   ((x) == TMR6_CH_A)                          ||                             \
    ((x) == TMR6_CH_B))

/*! Parameter valid check for buffer function number */
#define IS_VALID_BUF_NUM(x)                                                    \
(   ((x) == TMR6_BUF_SINGLE)                    ||                             \
    ((x) == TMR6_BUF_DUAL))

/*! Parameter valid check for buffer transfer timer configuration */
#define IS_VALID_BUF_TRANS_TRIG(x)                                             \
(   ((x) == TMR6_BUF_TRANS_INVD)                ||                             \
    ((x) == TMR6_BUF_TRANS_OVF)                 ||                             \
    ((x) == TMR6_BUF_TRANS_UDF)                 ||                             \
    ((x) == TMR6_BUF_TRANS_OVF_UDF))

/*! Parameter valid check for count condition for valid period function */
#define IS_VALID_PERIOD_CNT_COND(x)                                            \
(   ((x) == TMR6_VALID_PERIOD_INVD)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT_COND_VALLEY)  ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT_COND_PEAK)    ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT_COND_VALLEY_PEAK))

/*! Parameter valid check for count condition for valid period count */
#define IS_VALID_PERIOD_CNT(x)                                                 \
(   ((x) == TMR6_VALID_PERIOD_CNT_INVD)         ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT1)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT2)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT3)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT4)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT5)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT6)             ||                             \
    ((x) == TMR6_VALID_PERIOD_CNT7))

/*! Parameter valid check for count register data range */
#define IS_VALID_REG_RANGE_U16(x)               ((x) <= 0xFFFFUL)

/*! Parameter valid check for dead time register */
#define IS_VALID_DEADTIME_REG(x)                                               \
(   ((x) == TMR6_DEADTIME_REG_UP_A)             ||                             \
    ((x) == TMR6_DEADTIME_REG_DOWN_A)           ||                             \
    ((x) == TMR6_DEADTIME_REG_UP_B)             ||                             \
    ((x) == TMR6_DEADTIME_REG_DOWN_B))

/*! Parameter valid check for pin */
#define IS_VALID_PIN(x)                                                        \
(   ((x) == TMR6_IO_PWMA)                       ||                             \
    ((x) == TMR6_IO_PWMB)                       ||                             \
    ((x) == TMR6_INPUT_TRIGA)                   ||                             \
    ((x) == TMR6_INPUT_TRIGB))

/*! Parameter valid check for input pin filter clock */
#define IS_VALID_FILTER_CLK(x)                                                 \
(   ((x) == TMR6_FILTER_CLK_DIV1)               ||                             \
    ((x) == TMR6_FILTER_CLK_DIV4)               ||                             \
    ((x) == TMR6_FILTER_CLK_DIV16)              ||                             \
    ((x) == TMR6_FILTER_CLK_DIV64))

/*! Parameter valid check for PWM pin status */
#define IS_VALID_PWM_POLARITY(x)                                               \
(   ((x) == TMR6_PWM_LOW)                       ||                             \
    ((x) == TMR6_PWM_HIGH)                      ||                             \
    ((x) == TMR6_PWM_HOLD)                      ||                             \
    ((x) == TMR6_PWM_INVT))

/*! Parameter valid check for start stop hold for PWM output pin */
#define IS_VALID_PWM_START_STOP_HOLD(x)                                        \
(   ((x) == TMR6_PWM_START_STOP_HOLD)           ||                             \
    ((x) == TMR6_PWM_START_STOP_CHANGE))

/*! Parameter valid check for force PWM output pin */

/*! Parameter valid check for PWM pin status for count start and stop */
#define IS_VALID_PWM_POLARITY_START_STOP(x)                                    \
(   ((x) == TMR6_PWM_LOW)                       ||                             \
    ((x) == TMR6_PWM_HIGH))

#define IS_VALID_CNT_STAT(x)                                                   \
(   ((x) == TMR6_STAT_START)                    ||                             \
    ((x) == TMR6_STAT_STOP)                     ||                             \
    ((x) == TMR6_STAT_MATCH_CMP)                ||                             \
    ((x) == TMR6_STAT_MATCH_PERIOD))

/*! Parameter valid check for pin mode */
#define IS_VALID_PIN_MD(x)                                                     \
(   ((x) == TMR6_PIN_CMP_OUTPUT)                ||                             \
    ((x) == TMR6_PIN_CAPT_INPUT))

/*! Parameter valid check for pin output status when EMB event valid */
#define IS_VALID_EMB_VALID_PIN_POLARITY(x)                                     \
(   ((x) == TMR6_EMB_PIN_NORMAL)                ||                             \
    ((x) == TMR6_EMB_PIN_HIZ)                   ||                             \
    ((x) == TMR6_EMB_PIN_LOW)                   ||                             \
    ((x) == TMR6_EMB_PIN_HIGH))

/*! Parameter valid check for dead time buffer function for DTUAR and DTUBR register */
#define IS_VALID_DEADTIME_BUF_FUNC_DTUAR_REG(x)                                \
(   ((x) == TMR6_DEADTIME_CNT_UP_BUF_OFF)       ||                             \
    ((x) == TMR6_DEADTIME_CNT_UP_BUF_ON))

/*! Parameter valid check for dead time buffer function for DTDAR and DTDBR register */
#define IS_VALID_DEADTIME_BUF_FUNC_DTDAR_REG(x)                                \
(   ((x) == TMR6_DEADTIME_CNT_DOWN_BUF_OFF)     ||                             \
    ((x) == TMR6_DEADTIME_CNT_DOWN_BUF_ON))

/*! Parameter valid check for dead time equal function for DTUAR and DTDAR register */
#define IS_VALID_DEADTIME_EQUAL_FUNC_REG(x)                                    \
(   ((x) == TMR6_DEADTIME_EQUAL_OFF)            ||                             \
    ((x) == TMR6_DEADTIME_EQUAL_ON))

/*! Parameter valid check for start condition   */
#define IS_VALID_START_COND(x)                                                 \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_START_COND_ALL) == TMR6_START_COND_ALL))

/*! Parameter valid check for stop condition   */
#define IS_VALID_STOP_COND(x)                                                  \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_STOP_COND_ALL) == TMR6_STOP_COND_ALL))

/*! Parameter valid check for clear condition   */
#define IS_VALID_CLR_COND(x)                                                   \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_CLR_COND_ALL) == TMR6_CLR_COND_ALL))

/*! Parameter valid check for capture condition   */
#define IS_VALID_CAPT_COND(x)                                                  \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_CAPT_COND_ALL) == TMR6_CAPT_COND_ALL))

/*! Parameter valid check for hardware count up condition */
#define IS_VALID_CNT_UP_COND(x)                                                \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_CNT_UP_COND_ALL) == TMR6_CNT_UP_COND_ALL))

/*! Parameter valid check for hardware count down condition */
#define IS_VALID_CNT_DOWN_COND(x)                                              \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_CNT_DOWN_COND_ALL) == TMR6_CNT_DOWN_COND_ALL))

/*! Parameter valid check for count Mode */
#define IS_VALID_CNT_MD(x)                                                     \
(   ((x) == TMR6_MD_SAWTOOTH)                   ||                             \
    ((x) == TMR6_MD_TRIANGLE_A)                 ||                             \
    ((x) == TMR6_MD_TRIANGLE_B))

/*! Parameter valid check for count direction */
#define IS_VALID_CNT_DIR(x)                                                    \
(   ((x) == TMR6_CNT_UP)                        ||                             \
    ((x) == TMR6_CNT_DOWN))

/*! Parameter valid check for count clock division  */
#define IS_VALID_CNT_CLK_DIV(x)                                                \
(   ((x) == TMR6_CLK_DIV1)                      ||                             \
    ((x) == TMR6_CLK_DIV2)                      ||                             \
    ((x) == TMR6_CLK_DIV4)                      ||                             \
    ((x) == TMR6_CLK_DIV8)                      ||                             \
    ((x) == TMR6_CLK_DIV16)                     ||                             \
    ((x) == TMR6_CLK_DIV64)                     ||                             \
    ((x) == TMR6_CLK_DIV256)                    ||                             \
    ((x) == TMR6_CLK_DIV1024))

/*! Parameter valid check for Z Mask input function mask cycles number  */
#define IS_VALID_ZMASK_CYCLES(x)                                               \
(   ((x) == TMR6_ZMASK_FUNC_INVD)               ||                             \
    ((x) == TMR6_ZMASK_CYCLE_4)                 ||                             \
    ((x) == TMR6_ZMASK_CYCLE_8)                 ||                             \
    ((x) == TMR6_ZMASK_CYCLE_16))

/*! Parameter valid check for Z Mask function of timer6 position unit */
#define IS_VALID_POS_UNIT_ZMASK_FUNC(x)                                        \
(   ((x) == TMR6_POS_CLR_ZMASK_FUNC_OFF)        ||                             \
    ((x) == TMR6_POS_CLR_ZMASK_FUNC_ON))

/*! Parameter valid check for Z Mask function of timer6 revolution unit */
#define IS_VALID_REVO_UNIT_ZMASK_FUNC(x)                                       \
(   ((x) == TMR6_REVO_CNT_ZMASK_FUNC_OFF)       ||                             \
    ((x) == TMR6_REVO_CNT_ZMASK_FUNC_ON))

/*! Parameter valid check for software sync control unit */
#define IS_VALID_SW_UNIT(x)                                                    \
(   ((x) != 0UL)                                &&                             \
    (((x) | TMR6_SW_SYNC_ALL) == TMR6_SW_SYNC_ALL))

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
 * @defgroup TMR6_Global_Functions TMR6 Global Functions
 * @{
 */

/**
 * @brief  Initialize the timer6 count function
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] pstcTmr6Init        Pointer of configuration structure @ref stc_tmr6_init_t
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_Init(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_init_t *pstcTmr6Init)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcTmr6Init) {
        /* Check parameters */
        DDL_ASSERT(IS_TMR6_CNT_SRC(pstcTmr6Init->u8CountSrc));

        if (pstcTmr6Init->u8CountSrc == TMR6_CNT_SRC_SW) {
            /* Normal count */
            DDL_ASSERT(IS_VALID_CNT_MD(pstcTmr6Init->sw_count.u32CountMode));
            DDL_ASSERT(IS_VALID_CNT_DIR(pstcTmr6Init->sw_count.u32CountDir));
            DDL_ASSERT(IS_VALID_CNT_CLK_DIV(pstcTmr6Init->sw_count.u32ClockDiv));

            MODIFY_REG32(TMR6x->GCONR, TMR6_INIT_MASK, (pstcTmr6Init->sw_count.u32CountMode | pstcTmr6Init->sw_count.u32CountDir | \
                                                        pstcTmr6Init->sw_count.u32ClockDiv));
        } else {
            /* Hardware count */
            DDL_ASSERT(IS_VALID_CNT_UP_COND(pstcTmr6Init->hw_count.u32CountUpCond) ||
                       (pstcTmr6Init->hw_count.u32CountUpCond == TMR6_CNT_UP_COND_INVD));
            DDL_ASSERT(IS_VALID_CNT_DOWN_COND(pstcTmr6Init->hw_count.u32CountDownCond) ||
                       (pstcTmr6Init->hw_count.u32CountDownCond == TMR6_CNT_DOWN_COND_INVD));

            WRITE_REG32(TMR6x->HCUPR, pstcTmr6Init->hw_count.u32CountUpCond);
            WRITE_REG32(TMR6x->HCDOR, pstcTmr6Init->hw_count.u32CountDownCond);
        }

        DDL_ASSERT(IS_VALID_REG_RANGE_U16(pstcTmr6Init->u32PeriodValue));
        WRITE_REG32(TMR6x->PERAR, pstcTmr6Init->u32PeriodValue);
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set timer6 base count mode
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Mode             @ref TMR6_Count_Mode_Define
 * @retval None
 */
void TMR6_SetCountMode(CM_TMR6_TypeDef *TMR6x, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_MD(u32Mode));
    MODIFY_REG32(TMR6x->GCONR, TMR6_GCONR_MODE, u32Mode);
}

/**
 * @brief  Set timer6 base count direction
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Dir              @ref TMR6_Count_Dir_Define
 * @retval None
 */
void TMR6_SetCountDir(CM_TMR6_TypeDef *TMR6x, uint32_t u32Dir)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_DIR(u32Dir));
    MODIFY_REG32(TMR6x->GCONR, TMR6_GCONR_DIR, u32Dir);
}

/**
 * @brief  Set timer6 base count direction
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @retval uint32_t                 Count direction @ref TMR6_Count_Dir_Status_Define
 */
uint32_t TMR6_GetCountDir(CM_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    return READ_REG32_BIT(TMR6x->STFLR, TMR6_STFLR_DIRF);
}

/**
 * @brief  Set timer6 clock division
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Div              @ref TMR6_Count_Clock_Define
 * @retval None
 */
void TMR6_SetClockDiv(CM_TMR6_TypeDef *TMR6x, uint32_t u32Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CLK_DIV(u32Div));

    MODIFY_REG32(TMR6x->GCONR, TMR6_GCONR_CKDIV, u32Div);
}

/**
 * @brief  Hardware increase condition command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Cond             Events source for hardware count, maybe one or any combination of the parameter
 *                                  @ref TMR6_HW_Count_Up_Cond_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWCountUpCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_UP_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->HCUPR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR6x->HCUPR, u32Cond);
    }
}

/**
 * @brief  Hardware decrease condition command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Cond             Events source for hardware count, maybe one or any combination of the parameter
 *                                  @ref TMR6_HW_Count_Down_Cond_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWCountDownCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_DOWN_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->HCDOR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR6x->HCDOR, u32Cond);
    }
}

/**
 * @brief  Initialize the timer6 hardware count function
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               @ref TMR6_Count_Ch_Define
 * @param  [in] pstcPwmInit         Pointer of initialize structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_PWM_Init(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_pwm_init_t *pstcPwmInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    __IO uint32_t *TMR6_GCMxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));

    TMR6_GCMxR = (__IO uint32_t *)((uint32_t)&TMR6x->GCMAR + 4UL * u32Ch);

    if (NULL != pstcPwmInit) {
        DDL_ASSERT(IS_VALID_PWM_POLARITY_START_STOP(pstcPwmInit->u32StartPolarity));
        DDL_ASSERT(IS_VALID_PWM_POLARITY_START_STOP(pstcPwmInit->u32StopPolarity));
        DDL_ASSERT(IS_VALID_PWM_POLARITY(pstcPwmInit->u32CompareMatchPolarity));
        DDL_ASSERT(IS_VALID_PWM_POLARITY(pstcPwmInit->u32PeriodMatchPolarity));
        DDL_ASSERT(IS_VALID_PWM_START_STOP_HOLD(pstcPwmInit->u32StartStopHold));
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(pstcPwmInit->u32CompareValue));
        WRITE_REG32(*TMR6_GCMxR, pstcPwmInit->u32CompareValue);

        if (TMR6_CH_A == u32Ch) {
            MODIFY_REG32(TMR6x->PCONR, PCONR_REG_CHA_OUTPUT_CFG_MASK, \
                         pstcPwmInit->u32CompareMatchPolarity << TMR6_PCONR_CMPCA_POS \
                         | pstcPwmInit->u32PeriodMatchPolarity << TMR6_PCONR_PERCA_POS \
                         | pstcPwmInit->u32StopPolarity << TMR6_PCONR_STPCA_POS \
                         | pstcPwmInit->u32StartPolarity << TMR6_PCONR_STACA_POS \
                         | pstcPwmInit->u32StartStopHold);
        } else {
            MODIFY_REG32(TMR6x->PCONR, PCONR_REG_CHB_OUTPUT_CFG_MASK, \
                         pstcPwmInit->u32CompareMatchPolarity << TMR6_PCONR_CMPCB_POS \
                         | pstcPwmInit->u32PeriodMatchPolarity << TMR6_PCONR_PERCB_POS \
                         | pstcPwmInit->u32StopPolarity << TMR6_PCONR_STPCB_POS \
                         | pstcPwmInit->u32StartPolarity << TMR6_PCONR_STACB_POS \
                         | pstcPwmInit->u32StartStopHold);
        }
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Timer6 PWM output command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               @ref TMR6_Count_Ch_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_PWM_OutputCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t u32Tmp;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        u32Tmp = 0xFFFFFFFFUL;
    } else {
        u32Tmp = 0UL;
    }
    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_OUTENA, u32Tmp);
    } else {
        MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_OUTENB, u32Tmp);
    }
}

/**
 * @brief  Timer6 set pin polarity
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               @ref TMR6_Count_Ch_Define
 * @param  [in] u32CountState       Polarity set for @ref TMR6_Count_State_Define
 * @param  [in] u32Polarity         @ref TMR6_Pin_Polarity_Define
 * @retval None
 */
void TMR6_PWM_SetPolarity(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32CountState, uint32_t u32Polarity)
{
    uint32_t u32PolarityMask = PCONR_REG_POLARITY_MASK;

    uint8_t au8Pos[4] = {TMR6_PCONR_STACA_POS, TMR6_PCONR_STPCA_POS, TMR6_PCONR_CMPCA_POS, TMR6_PCONR_PERCA_POS };
    DDL_ASSERT(IS_VALID_CNT_STAT(u32CountState));
    if ((TMR6_STAT_START == u32CountState) || (TMR6_STAT_STOP == u32CountState)) {
        DDL_ASSERT(IS_VALID_PWM_POLARITY_START_STOP(u32Polarity));
        u32PolarityMask = PCONR_REG_POLARITY_START_STOP_MASK;
    } else {
        DDL_ASSERT(IS_VALID_PWM_POLARITY(u32Polarity));
    }
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));

    u32Polarity <<= au8Pos[u32CountState];
    u32PolarityMask <<= au8Pos[u32CountState];

    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->PCONR, u32PolarityMask, u32Polarity);
    } else {
        MODIFY_REG32(TMR6x->PCONR, u32PolarityMask << PCONR_REG_CHB_SHIFT, u32Polarity << PCONR_REG_CHB_SHIFT);
    }
}

/**
 * @brief  Timer6 set force polarity when next period
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               @ref TMR6_Count_Ch_Define
 * @param  [in] u32HoldStatus       @ref TMR6_Output_StaStp_Hold_Define
 * @retval None
 */
void TMR6_PWM_SetStartStopHold(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32HoldStatus)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_VALID_PWM_START_STOP_HOLD(u32HoldStatus));

    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_STASTPSA, u32HoldStatus);
    } else {
        MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_STASTPSB, u32HoldStatus << PCONR_REG_CHB_SHIFT);
    }
}

/**
 * @brief  Hardware capture condition command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               Input pin select @ref TMR6_Count_Ch_Define
 * @param  [in] u32Cond             Events source for hardware capture, maybe one or any combination of the parameter
 *                                  @ref TMR6_hardware_capture_condition_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWCaptureCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    __IO uint32_t *HCPxR;
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_VALID_CAPT_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    HCPxR = (__IO uint32_t *)((uint32_t)&TMR6x->HCPAR + (u32Ch * 4UL));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(*HCPxR, u32Cond);
    } else {
        CLR_REG32_BIT(*HCPxR, u32Cond);
    }
}

/**
 * @brief  Port input filter function configuration(Trig)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Pin              Pin to be configured @ref TMR6_Pin_Define
 * @param  [in] u32Div              Filter clock @ref TMR6_Input_Filter_Clock
 * @retval None
 */
void TMR6_SetFilterClockDiv(CM_TMR6_TypeDef *TMR6x, uint32_t u32Pin, uint32_t u32Div)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_PIN(u32Pin));
    DDL_ASSERT(IS_VALID_FILTER_CLK(u32Div));

    switch (u32Pin) {
        case TMR6_IO_PWMA:
            MODIFY_REG32(TMR6x->FCONR, TMR6_FCONR_NOFICKGA, u32Div << TMR6_FCONR_NOFICKGA_POS);
            break;
        case TMR6_IO_PWMB:
            MODIFY_REG32(TMR6x->FCONR, TMR6_FCONR_NOFICKGB, u32Div << TMR6_FCONR_NOFICKGB_POS);
            break;
        case TMR6_INPUT_TRIGA:
            MODIFY_REG32(CM_TMR6_1->FCONR, TMR6_FCONR_NOFICKTA, u32Div << TMR6_FCONR_NOFICKTA_POS);
            break;
        case TMR6_INPUT_TRIGB:
            MODIFY_REG32(CM_TMR6_1->FCONR, TMR6_FCONR_NOFICKTB, u32Div << TMR6_FCONR_NOFICKTB_POS);
            break;
        default:
            break;
    }
}

/**
 * @brief  Port input filter function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Pin              Input port to be configured @ref TMR6_Pin_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_FilterCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Pin, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_PIN(u32Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    switch (u32Pin) {
        case TMR6_IO_PWMA:
            MODIFY_REG32(TMR6x->FCONR, TMR6_FCONR_NOFIENGA, ((uint32_t)enNewState) << TMR6_FCONR_NOFIENGA_POS);
            break;
        case TMR6_IO_PWMB:
            MODIFY_REG32(TMR6x->FCONR, TMR6_FCONR_NOFIENGB, ((uint32_t)enNewState) << TMR6_FCONR_NOFIENGB_POS);
            break;
        case TMR6_INPUT_TRIGA:
            MODIFY_REG32(CM_TMR6_1->FCONR, TMR6_FCONR_NOFIENTA, ((uint32_t)enNewState) << TMR6_FCONR_NOFIENTA_POS);
            break;
        case TMR6_INPUT_TRIGB:
            MODIFY_REG32(CM_TMR6_1->FCONR, TMR6_FCONR_NOFIENTB, ((uint32_t)enNewState) << TMR6_FCONR_NOFIENTB_POS);
            break;
        default:
            break;
    }
}

/**
 * @brief  Set channel function
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               Channel to be configured @ref TMR6_Count_Ch_Define
 * @param  [in] u32Func             IO mode @ref TMR6_Pin_Mode_Define
 * @retval None
 */
void TMR6_SetFunc(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32Func)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_VALID_PIN_MD(u32Func));

    switch (u32Ch) {
        case TMR6_CH_A:
            MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_CAPMDA, u32Func);
            break;
        case TMR6_CH_B:
            MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_CAPMDB, u32Func << TMR6_PCONR_CAPMDB_POS);
            break;
        default:
            break;
    }
}

/**
 * @brief  Timer6 interrupt enable or disable
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32IntType          Irq flag, Can be one or any combination of the values from
 *                                  @ref TMR6_Int_Flag_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_IntCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_IRQ(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->ICONR, u32IntType);
    } else {
        CLR_REG32_BIT(TMR6x->ICONR, u32IntType);
    }
}

/**
 * @brief  Get Timer6 status flag
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Flag             Status bit to be read, Can be one or any combination of the values from
 *                                  @ref TMR6_Stat_Flag_Define
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t TMR6_GetStatus(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Flag)
{
    en_flag_status_t enStatus = RESET;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_GET_FLAG(u32Flag));

    if (0UL != READ_REG32_BIT(TMR6x->STFLR, u32Flag)) {
        enStatus =  SET;
    }
    return enStatus;
}

/**
 * @brief  Clear Timer6 status flag
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Flag             Status bit to be read, Can be one or any combination of the values from
 *                                  @ref TMR6_Stat_Flag_Define
 * @retval None
 */
void TMR6_ClearStatus(CM_TMR6_TypeDef *TMR6x, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CLR_FLAG(u32Flag));

    CLR_REG32_BIT(TMR6x->STFLR, u32Flag);
}

/**
 * @brief  Get Timer6 period number when valid period function enable
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @retval uint32_t                 Data for periods number
 */
uint32_t TMR6_GetPeriodNum(const CM_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    return (READ_REG32_BIT(TMR6x->STFLR, TMR6_STFLR_VPERNUM) >> TMR6_STFLR_VPERNUM_POS);
}

/**
 * @brief  De-initialize the timer6 unit
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @retval None
 */
void TMR6_DeInit(CM_TMR6_TypeDef *TMR6x)
{
    uint32_t u32RefRegResetValue;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    u32RefRegResetValue = TMR6_REG_RST_VALUE_U16;

    WRITE_REG32(TMR6x->GCONR, TMR6_REG_GCONR_RST_VALUE);
    WRITE_REG32(TMR6x->CNTER, 0UL);
    WRITE_REG32(TMR6x->PERAR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->PERBR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->PERCR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->GCMAR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->GCMBR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->GCMCR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->GCMDR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->GCMER, u32RefRegResetValue);
    WRITE_REG32(TMR6x->GCMFR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->SCMAR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->SCMBR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->SCMCR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->SCMDR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->SCMER, u32RefRegResetValue);
    WRITE_REG32(TMR6x->SCMFR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->DTUAR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->DTDAR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->DTUBR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->DTDBR, u32RefRegResetValue);
    WRITE_REG32(TMR6x->ICONR, 0UL);
    WRITE_REG32(TMR6x->BCONR, 0UL);
    WRITE_REG32(TMR6x->DCONR, 0UL);
    WRITE_REG32(TMR6x->PCONR, 0UL);
    WRITE_REG32(TMR6x->FCONR, 0UL);
    WRITE_REG32(TMR6x->VPERR, 0UL);
    WRITE_REG32(TMR6x->STFLR, 0UL);
    WRITE_REG32(TMR6x->HSTAR, 0UL);
    WRITE_REG32(TMR6x->HSTPR, 0UL);
    WRITE_REG32(TMR6x->HCLRR, 0UL);
    WRITE_REG32(TMR6x->HCPAR, 0UL);
    WRITE_REG32(TMR6x->HCPBR, 0UL);
    WRITE_REG32(TMR6x->HCUPR, 0UL);
    WRITE_REG32(TMR6x->HCDOR, 0UL);

    WRITE_REG32(CM_TMR6CR->SSTAR, 0UL);
    WRITE_REG32(CM_TMR6CR->SSTPR, 0UL);
    WRITE_REG32(CM_TMR6CR->SCLRR, 0UL);
}

/**
 * @brief  Timer6 count start
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @retval None
 */
void TMR6_Start(CM_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    SET_REG32_BIT(TMR6x->GCONR, TMR6_GCONR_START);
}

/**
 * @brief  Timer6 count stop
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @retval None
 */
void TMR6_Stop(CM_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    CLR_REG32_BIT(TMR6x->GCONR, TMR6_GCONR_START);
}

/**
 * @brief  Timer6 counter register set
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Value            Counter value
 * @retval None
 */
void TMR6_SetCountValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
    WRITE_REG32(TMR6x->CNTER, u32Value);
}

/**
 * @brief  Timer6 get counter register value
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @retval uint32_t                 Data for the count register value
 */
uint32_t TMR6_GetCountValue(const CM_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    return READ_REG32(TMR6x->CNTER);
}

/**
 * @brief  Timer6 set period register(A~C)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            Period register to be write, @ref TMR6_Period_Reg_Index_Define
 * @param  [in] u32Value            Period value for write
 * @retval None
 */
void TMR6_SetPeriodValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value)
{
    __IO uint32_t *TMR6_PERxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_PERIOD_REG(u32Index));

    TMR6_PERxR = (uint32_t *)((uint32_t)&TMR6x->PERAR + 4UL * u32Index);

    DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
    WRITE_REG32(*TMR6_PERxR, u32Value);
}

/**
 * @brief  Timer6 set general compare register(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            General compare register to be write, @ref TMR6_Compare_Reg_Index_Define
 * @param  [in] u32Value            Value for write
 * @retval None
 */
void TMR6_SetCompareValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value)
{
    __IO uint32_t *TMR6_GCMxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32Index));
    TMR6_GCMxR = (__IO uint32_t *)((uint32_t)&TMR6x->GCMAR + 4UL * u32Index);

    DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
    WRITE_REG32(*TMR6_GCMxR, u32Value);
}

/**
 * @brief  Timer6 set special compare register(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            Special compare register to be write, @ref TMR6_Compare_Reg_Index_Define
 * @param  [in] u32Value            Value for write
 * @retval None
 */
void TMR6_SetSpecialCompareValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value)
{
    __IO uint32_t *TMR6_SCMxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32Index));
    TMR6_SCMxR = (uint32_t *)((uint32_t)&TMR6x->SCMAR + 4UL * u32Index);

    DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
    WRITE_REG32(*TMR6_SCMxR, u32Value);
}

/**
 * @brief  Timer6 set dead time register
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            Special compare register to be write, @ref TMR6_DeadTime_Reg_Define
 * @param  [in] u32Value            Value for write
 * @retval None
 */
void TMR6_SetDeadTimeValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value)
{
    __IO uint32_t *TMR6_DTxyR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_DEADTIME_REG(u32Index));
    TMR6_DTxyR = (uint32_t *)((uint32_t)&TMR6x->DTUAR + 4UL * u32Index);

    DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
    WRITE_REG32(*TMR6_DTxyR, u32Value);
}

/**
 * @brief  Timer6 get general compare registers value(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            General compare register to be read, @ref TMR6_Compare_Reg_Index_Define
 * @retval uint32_t                 Data for value of the register
 */
uint32_t TMR6_GetCompareValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index)
{
    __IO uint32_t *TMR6_GCMxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32Index));
    TMR6_GCMxR = (uint32_t *)((uint32_t)&TMR6x->GCMAR + 4UL * u32Index);

    return READ_REG32(*TMR6_GCMxR);
}

/**
 * @brief  Timer6 get special compare registers value(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            Special compare register to be read, @ref TMR6_Compare_Reg_Index_Define
 * @retval uint32_t                 Data for value of the register
 */
uint32_t TMR6_GetSpecialCompareValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index)
{
    __IO uint32_t *TMR6_SCMxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32Index));
    TMR6_SCMxR = (uint32_t *)((uint32_t)&TMR6x->SCMAR + 4UL * u32Index);

    return READ_REG32(*TMR6_SCMxR);
}

/**
 * @brief  Timer6 Get period register(A~C)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            Period register to be write, @ref TMR6_Period_Reg_Index_Define
 * @retval uint32_t                 Data for value of the register
 */
uint32_t TMR6_GetPeriodValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index)
{
    __IO uint32_t *TMR6_PERxR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_PERIOD_REG(u32Index));
    TMR6_PERxR = (uint32_t *)((uint32_t)&TMR6x->PERAR + 4UL * u32Index);

    return READ_REG32(*TMR6_PERxR);
}

/**
 * @brief  Timer6 get dead time register
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Index            Dead time register to be write, @ref TMR6_DeadTime_Reg_Define
 * @retval uint32_t                 Data for value of the register
 */
uint32_t TMR6_GetDeadTimeValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index)
{
    __IO uint32_t *TMR6_DTxyR;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_DEADTIME_REG(u32Index));
    TMR6_DTxyR = (uint32_t *)((uint32_t)&TMR6x->DTUAR + 4UL * u32Index);

    return READ_REG32(*TMR6_DTxyR);
}

/**
 * @brief  Timer6 general compare buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               General compare buffer chose @ref TMR6_Count_Ch_Define
 * @param  [in] u32BufNum           Buffer number @ref TMR6_Buf_Num_Define
 * @retval None
 */
void TMR6_SetGeneralBufNum(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32BufNum)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_BUF_NUM(u32BufNum));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));

    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->BCONR, BCONR_GEN_CFG_MASK, u32BufNum);
    } else {
        MODIFY_REG32(TMR6x->BCONR, BCONR_GEN_CFG_MASK << BCONR_GEN_CFG_CHB_OFS, u32BufNum << BCONR_GEN_CFG_CHB_OFS);
    }
}

/**
 * @brief  Timer6 general compare buffer function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               General compare buffer chose, @ref TMR6_Count_Ch_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_GeneralBufCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->BCONR, BCONR_FUNC_CMD_MASK, enNewState);
    } else {
        MODIFY_REG32(TMR6x->BCONR, BCONR_FUNC_CMD_MASK << BCONR_GEN_CFG_CHB_OFS, \
                     ((uint32_t)enNewState) << BCONR_GEN_CFG_CHB_OFS);
    }
}

/**
 * @brief  Timer6 special compare buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               Special compare buffer chose, @ref TMR6_Count_Ch_Define
 * @param  [in] pstcBufConfig       Pointer of configuration structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_SpecialBufConfig(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_buf_config_t *pstcBufConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (NULL != pstcBufConfig) {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
        DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
        DDL_ASSERT(IS_VALID_BUF_NUM(pstcBufConfig->u32BufNum));
        DDL_ASSERT(IS_VALID_BUF_TRANS_TRIG(pstcBufConfig->u32BufTransCond));

        if (TMR6_CH_A == u32Ch) {
            MODIFY_REG32(TMR6x->BCONR, BCONR_SPECIAL_CFG_MASK << BCONR_SPECIAL_CFG_CHA_OFS, \
                         (pstcBufConfig->u32BufNum << BCONR_SPECIAL_CFG_CHA_OFS) \
                         | (pstcBufConfig->u32BufTransCond << BCONR_SPECIAL_CFG_TRIG_CHA_OFS));
        } else {
            MODIFY_REG32(TMR6x->BCONR, BCONR_SPECIAL_CFG_MASK << BCONR_SPECIAL_CFG_CHB_OFS, \
                         (pstcBufConfig->u32BufNum << BCONR_SPECIAL_CFG_CHB_OFS) | \
                         (pstcBufConfig->u32BufTransCond << BCONR_SPECIAL_CFG_TRIG_CHB_OFS));
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Timer6 special compare buffer function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               General compare buffer chose, @ref TMR6_Count_Ch_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_SpecialBufCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->BCONR, BCONR_FUNC_CMD_MASK << BCONR_SPECIAL_CFG_CHA_OFS, \
                     ((uint32_t)enNewState) << BCONR_SPECIAL_CFG_CHA_OFS);
    } else {
        MODIFY_REG32(TMR6x->BCONR, BCONR_FUNC_CMD_MASK << BCONR_SPECIAL_CFG_CHB_OFS, \
                     ((uint32_t)enNewState) << BCONR_SPECIAL_CFG_CHB_OFS);
    }
}

/**
 * @brief  Timer6 period buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32BufNum           Buffer number @ref TMR6_Buf_Num_Define
 * @retval None
 */
void TMR6_SetPeriodBufNum(CM_TMR6_TypeDef *TMR6x, uint32_t u32BufNum)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_BUF_NUM(u32BufNum));

    MODIFY_REG32(TMR6x->BCONR, BCONR_PERIOD_CFG_MASK << BCONR_PERIOD_CFG_OFS, u32BufNum << BCONR_PERIOD_CFG_OFS);
}

/**
 * @brief  Timer6 period buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_PeriodBufCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->BCONR, BCONR_FUNC_CMD_MASK << BCONR_PERIOD_CFG_OFS,
                 ((uint32_t)enNewState) << BCONR_PERIOD_CFG_OFS);
}

/**
 * @brief  Timer6 valid period function configuration for special compare function
 * @param  [in] TMR6x                   Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] pstcValidperiodConfig   Pointer of configuration structure
 * @retval int32_t:
 *         - LL_OK:                     Successfully done
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t TMR6_ValidPeriodConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_valid_period_config_t *pstcValidperiodConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (NULL != pstcValidperiodConfig) {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
        DDL_ASSERT(IS_VALID_PERIOD_CNT_COND(pstcValidperiodConfig->u32CountCond));
        DDL_ASSERT(IS_VALID_PERIOD_CNT(pstcValidperiodConfig->u32PeriodInterval));

        MODIFY_REG32(TMR6x->VPERR, TMR6_VPERR_PCNTS | TMR6_VPERR_PCNTE, \
                     pstcValidperiodConfig->u32CountCond | pstcValidperiodConfig->u32PeriodInterval);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Timer6 valid period function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Ch               General compare buffer chose, @ref TMR6_Count_Ch_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_ValidPeriodCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (TMR6_CH_A == u32Ch) {
        MODIFY_REG32(TMR6x->VPERR, TMR6_VPERR_SPPERIA, ((uint32_t)enNewState) << TMR6_VPERR_SPPERIA_POS);
    } else {
        MODIFY_REG32(TMR6x->VPERR, TMR6_VPERR_SPPERIB, ((uint32_t)enNewState) << TMR6_VPERR_SPPERIB_POS);
    }
}

/**
 * @brief  Timer6 dead time function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_DeadTimeFuncCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->DCONR, TMR6_DCONR_DTCEN);
    } else {
        CLR_REG32_BIT(TMR6x->DCONR, TMR6_DCONR_DTCEN);
    }
}

/**
 * @brief  DeadTime function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in]  pstcDeadTimeConfig Timer6 dead time config pointer
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_DeadTimeConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_deadtime_config_t *pstcDeadTimeConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcDeadTimeConfig) {
        DDL_ASSERT(IS_VALID_DEADTIME_EQUAL_FUNC_REG(pstcDeadTimeConfig->u32EqualUpDown));
        DDL_ASSERT(IS_VALID_DEADTIME_BUF_FUNC_DTUAR_REG(pstcDeadTimeConfig->u32BufUp));
        DDL_ASSERT(IS_VALID_DEADTIME_BUF_FUNC_DTDAR_REG(pstcDeadTimeConfig->u32BufDown));
        WRITE_REG32(TMR6x->DCONR, pstcDeadTimeConfig->u32EqualUpDown | pstcDeadTimeConfig->u32BufUp \
                    | pstcDeadTimeConfig->u32BufDown);
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Timer6 unit Z phase input mask config
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] pstcZMaskConfig     Pointer of configuration structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_ZMaskConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_zmask_config_t *pstcZMaskConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcZMaskConfig) {
        DDL_ASSERT(IS_VALID_ZMASK_CYCLES(pstcZMaskConfig->u32ZMaskCycle));
        DDL_ASSERT(IS_VALID_POS_UNIT_ZMASK_FUNC(pstcZMaskConfig->u32PosCountMaskFunc));
        DDL_ASSERT(IS_VALID_REVO_UNIT_ZMASK_FUNC(pstcZMaskConfig->u32RevoCountMaskFunc));

        MODIFY_REG32(TMR6x->GCONR, TMR6_ZMASK_CFG_MASK, pstcZMaskConfig->u32ZMaskCycle | \
                     pstcZMaskConfig->u32PosCountMaskFunc | pstcZMaskConfig->u32RevoCountMaskFunc);

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  EMB function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in]  u32Ch              Channel to be configured @ref TMR6_Count_Ch_Define
 * @param  [in]  pstcEmbConfig      Point EMB function Config Pointer
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_EMBConfig(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_emb_config_t *pstcEmbConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcEmbConfig) {
        DDL_ASSERT(IS_VALID_CNT_CH(u32Ch));
        DDL_ASSERT(IS_VALID_EMB_VALID_PIN_POLARITY(pstcEmbConfig->u32PinStatus));

        if (TMR6_CH_A == u32Ch) {
            MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_EMBVALA, pstcEmbConfig->u32PinStatus);
        } else {
            MODIFY_REG32(TMR6x->PCONR, TMR6_PCONR_EMBVALB,
                         pstcEmbConfig->u32PinStatus << (TMR6_PCONR_EMBVALB_POS - TMR6_PCONR_EMBVALA_POS));
        }

        i32Ret = LL_OK;
    }
    return i32Ret;

}

/**
 * @brief  Software Sync Start
 * @param  [in]  u32Unit            Software Sync units, This parameter can be one or any combination of the parameter
 *                                  @ref TMR6_SW_Sync_Unit_define
 * @retval None
 */
void TMR6_SWSyncStart(uint32_t u32Unit)
{
    DDL_ASSERT(IS_VALID_SW_UNIT(u32Unit));
    WRITE_REG32(CM_TMR6CR->SSTAR, u32Unit);
}

/**
 * @brief  Software Sync Stop
 * @param  [in]  u32Unit            Software Sync units, This parameter can be one or any combination of the parameter
 *                                  @ref TMR6_SW_Sync_Unit_define
 * @retval None
 */
void TMR6_SWSyncStop(uint32_t u32Unit)
{
    DDL_ASSERT(IS_VALID_SW_UNIT(u32Unit));
    WRITE_REG32(CM_TMR6CR->SSTPR, u32Unit);
}

/**
 * @brief  Software Sync clear
 * @param  [in]  u32Unit            Software Sync units, This parameter can be one or any combination of the parameter
 *                                  @ref TMR6_SW_Sync_Unit_define
 * @retval None
 */
void TMR6_SWSyncClear(uint32_t u32Unit)
{
    DDL_ASSERT(IS_VALID_SW_UNIT(u32Unit));
    WRITE_REG32(CM_TMR6CR->SCLRR, u32Unit);
}

/**
 * @brief  Hardware start function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWStartCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HSTAR, TMR6_HSTAR_STAS, ((uint32_t)enNewState) << TMR6_HSTAR_STAS_POS);
}

/**
 * @brief  Hardware stop function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWStopCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HSTPR, TMR6_HSTPR_STPS, ((uint32_t)enNewState) << TMR6_HSTPR_STPS_POS);
}

/**
 * @brief  Hardware clear function command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWClearCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HCLRR, TMR6_HCLRR_CLES, ((uint32_t)enNewState) << TMR6_HCLRR_CLES_POS);
}

/**
 * @brief  Hardware start condition command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Cond             Events source for hardware start, maybe one or any combination of the parameter
 *                                  @ref TMR6_hardware_start_condition_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWStartCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_START_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->HSTAR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR6x->HSTAR, u32Cond);
    }
}

/**
 * @brief  Hardware stop condition command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Cond             Events source for hardware stop, maybe one or any combination of the parameter
 *                                  @ref TMR6_hardware_stop_condition_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWStopCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_STOP_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->HSTPR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR6x->HSTPR, u32Cond);
    }
}

/**
 * @brief  Hardware clear condition command
 * @param  [in] TMR6x               Timer6 unit
 *  @arg CM_TMR6_x
 * @param  [in] u32Cond             Events source for hardware clear, maybe one or any combination of the parameter
 *                                  @ref TMR6_hardware_clear_condition_Define
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR6_HWClearCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CLR_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR6x->HCLRR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR6x->HCLRR, u32Cond);
    }
}

/**
 * @brief  Set the fields of structure stc_tmr6_init_t to default values
 * @param  [out] pstcTmr6Init       Pointer to a @ref stc_tmr6_init_t structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_StructInit(stc_tmr6_init_t *pstcTmr6Init)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint32_t u32RefRegResetValue;

    /* Check structure pointer */
    if (NULL != pstcTmr6Init) {
        pstcTmr6Init->u8CountSrc = TMR6_CNT_SRC_SW;
        pstcTmr6Init->sw_count.u32ClockDiv  = TMR6_CLK_DIV1;
        pstcTmr6Init->sw_count.u32CountMode = TMR6_MD_SAWTOOTH;
        pstcTmr6Init->sw_count.u32CountDir  = TMR6_CNT_UP;
        pstcTmr6Init->hw_count.u32CountUpCond   = TMR6_CNT_UP_COND_INVD;
        pstcTmr6Init->hw_count.u32CountDownCond = TMR6_CNT_DOWN_COND_INVD;
        u32RefRegResetValue = TMR6_REG_RST_VALUE_U16;
        pstcTmr6Init->u32PeriodValue = u32RefRegResetValue;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr6_buf_config_t to default values
 * @param  [out] pstcBufConfig      Pointer to a @ref stc_tmr6_buf_config_t structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_BufFuncStructInit(stc_tmr6_buf_config_t *pstcBufConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check structure pointer */
    if (NULL != pstcBufConfig) {
        pstcBufConfig->u32BufNum = TMR6_BUF_SINGLE;
        pstcBufConfig->u32BufTransCond = TMR6_BUF_TRANS_INVD;

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr6_valid_period_config_t to default values
 * @param  [out] pstcValidperiodConfig  Pointer to a @ref stc_tmr6_valid_period_config_t structure
 * @retval int32_t:
 *         - LL_OK:                     Successfully done
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t TMR6_ValidPeriodStructInit(stc_tmr6_valid_period_config_t *pstcValidperiodConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check structure pointer */
    if (NULL != pstcValidperiodConfig) {
        pstcValidperiodConfig->u32CountCond = TMR6_VALID_PERIOD_INVD;
        pstcValidperiodConfig->u32PeriodInterval = TMR6_VALID_PERIOD_CNT_INVD;

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr6_emb_config_t to default values
 * @param  [out] pstcEmbConfig      Pointer to a @ref stc_tmr6_emb_config_t structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_EMBConfigStructInit(stc_tmr6_emb_config_t *pstcEmbConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check structure pointer */
    if (NULL != pstcEmbConfig) {
        pstcEmbConfig->u32PinStatus = TMR6_EMB_PIN_NORMAL;

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr6_deadtime_config_t to default values
 * @param  [out] pstcDeadTimeConfig Pointer to a @ref stc_tmr6_deadtime_config_t structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_DeadTimeStructInit(stc_tmr6_deadtime_config_t *pstcDeadTimeConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check structure pointer */
    if (NULL != pstcDeadTimeConfig) {
        pstcDeadTimeConfig->u32EqualUpDown = TMR6_DEADTIME_EQUAL_OFF;
        pstcDeadTimeConfig->u32BufUp = TMR6_DEADTIME_CNT_UP_BUF_OFF;
        pstcDeadTimeConfig->u32BufDown = TMR6_DEADTIME_CNT_DOWN_BUF_OFF;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr6_zmask_config_t to default values
 * @param  [out] pstcZMaskConfig    Pointer to a @ref stc_tmr6_zmask_config_t structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_ZMaskConfigStructInit(stc_tmr6_zmask_config_t *pstcZMaskConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check structure pointer */
    if (NULL != pstcZMaskConfig) {
        pstcZMaskConfig->u32ZMaskCycle = TMR6_ZMASK_FUNC_INVD;
        pstcZMaskConfig->u32PosCountMaskFunc = TMR6_POS_CLR_ZMASK_FUNC_OFF;
        pstcZMaskConfig->u32RevoCountMaskFunc = TMR6_REVO_CNT_ZMASK_FUNC_OFF;

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr6_pwm_init_t to default values
 * @param  [out] pstcPwmInit        Pointer to a @ref stc_tmr6_pwm_init_t structure
 * @retval int32_t:
 *         - LL_OK:                 Successfully done
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t TMR6_PWM_StructInit(stc_tmr6_pwm_init_t *pstcPwmInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint32_t u32RefRegResetValue;

    /* Check structure pointer */
    if (NULL != pstcPwmInit) {
        pstcPwmInit->u32StartPolarity = TMR6_PWM_LOW;
        pstcPwmInit->u32StopPolarity = TMR6_PWM_LOW;

        u32RefRegResetValue = TMR6_REG_RST_VALUE_U16;
        pstcPwmInit->u32CompareMatchPolarity = TMR6_PWM_LOW;
        pstcPwmInit->u32PeriodMatchPolarity = TMR6_PWM_LOW;
        pstcPwmInit->u32StartStopHold = TMR6_PWM_START_STOP_CHANGE;
        pstcPwmInit->u32CompareValue = u32RefRegResetValue;
        i32Ret = LL_OK;
    }
    return i32Ret;
}
/**
 * @}
 */

#endif /* LL_TMR6_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
