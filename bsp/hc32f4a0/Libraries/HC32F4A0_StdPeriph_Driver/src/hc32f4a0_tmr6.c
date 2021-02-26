/**
 *******************************************************************************
 * @file  hc32f4a0_tmr6.c
 * @brief This file provides firmware functions to manage the TMR6 (TMR6).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wangmin         First version
   2020-07-15       Wangmin         Refine macro define
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
#include "hc32f4a0_tmr6.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR6 TMR6
 * @brief TMR6 Driver Library
 * @{
 */

#if (DDL_TMR6_ENABLE == DDL_ON)

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
#define TMR6_REG_REFERENCE_RESET_VALUE_U32      (0xFFFFFFFFUL)
#define TMR6_REG_REFERENCE_RESET_VALUE_U16      (0xFFFFU)
#define TMR6_REG_GCONR_RESET_VALUE              (0x00000100UL)

/* Define for BCONR register configuration */
#define BCONR_REG_CFG_MSK                       (0x0000000FUL)
#define BCONR_GEN_BUF_CHA_OFFSET                (0x00UL)
#define BCONR_GEN_BUF_CHB_OFFSET                (0x04UL)
#define BCONR_PERIOD_BUF_OFFSET                 (0x08UL)
#define BCONR_SPECIAL_BUF_CHA_OFFSET            (0x10UL)
#define BCONR_SPECIAL_BUF_CHB_OFFSET            (0x14UL)

/* Define mask value for port output configuration for PCNAR/PCNBR register */
#define PCNA_BR_REG_OUTPUT_CFG_MASK             (0x9003FFFFUL)
#define PCNA_BR_REG_EMB_CFG_MASK                (TMR6_PCNAR_EMBSA | TMR6_PCNAR_EMBRA | TMR6_PCNAR_EMBCA)
/* Define mask value for GCONR register */
#define TMR6_INITIAL_MASK                       (TMR6_GCONR_DIR | TMR6_GCONR_MODE | TMR6_GCONR_CKDIV | TMR6_GCONR_OVSTP)
#define TMR6_ZMASK_CFG_MASK                     (TMR6_GCONR_ZMSKVAL | TMR6_GCONR_ZMSKPOS | TMR6_GCONR_ZMSKREV)

#define TMR6_HW_CTRL_EVENT_MASK  (TMR6_HW_CTRL_PWMA_RISING           |         \
                                  TMR6_HW_CTRL_PWMA_FAILLING         |         \
                                  TMR6_HW_CTRL_PWMB_RISING           |         \
                                  TMR6_HW_CTRL_PWMB_FAILLING         |         \
                                  TMR6_HW_CTRL_INTER_EVENT0          |         \
                                  TMR6_HW_CTRL_INTER_EVENT1          |         \
                                  TMR6_HW_CTRL_INTER_EVENT2          |         \
                                  TMR6_HW_CTRL_INTER_EVENT3          |         \
                                  TMR6_HW_CTRL_TRIGEA_RISING         |         \
                                  TMR6_HW_CTRL_TRIGEA_FAILLING       |         \
                                  TMR6_HW_CTRL_TRIGEB_RISING         |         \
                                  TMR6_HW_CTRL_TRIGEB_FAILLING       |         \
                                  TMR6_HW_CTRL_TRIGEC_RISING         |         \
                                  TMR6_HW_CTRL_TRIGEC_FAILLING       |         \
                                  TMR6_HW_CTRL_TRIGED_RISING         |         \
                                  TMR6_HW_CTRL_TRIGED_FAILLING)

#define TMR6_HW_CNT_EVENT_MASK   (TMR6_HW_CNT_PWMAL_PWMBRISING       |         \
                                  TMR6_HW_CNT_PWMAL_PWMBFAILLING     |         \
                                  TMR6_HW_CNT_PWMAH_PWMBRISING       |         \
                                  TMR6_HW_CNT_PWMAH_PWMBFAILLING     |         \
                                  TMR6_HW_CNT_PWMBL_PWMARISING       |         \
                                  TMR6_HW_CNT_PWMBL_PWMAFAILLING     |         \
                                  TMR6_HW_CNT_PWMBH_PWMARISING       |         \
                                  TMR6_HW_CNT_PWMBH_PWMAFAILLING     |         \
                                  TMR6_HW_CNT_INTER_EVENT0           |         \
                                  TMR6_HW_CNT_INTER_EVENT1           |         \
                                  TMR6_HW_CNT_INTER_EVENT2           |         \
                                  TMR6_HW_CNT_INTER_EVENT3           |         \
                                  TMR6_HW_CNT_TRIGEA_RISING          |         \
                                  TMR6_HW_CNT_TRIGEA_FAILLING        |         \
                                  TMR6_HW_CNT_TRIGEB_RISING          |         \
                                  TMR6_HW_CNT_TRIGEB_FAILLING        |         \
                                  TMR6_HW_CNT_TRIGEC_RISING          |         \
                                  TMR6_HW_CNT_TRIGEC_FAILLING        |         \
                                  TMR6_HW_CNT_TRIGED_RISING          |         \
                                  TMR6_HW_CNT_TRIGED_FAILLING)

#define TMR6_IRQ_EN_MASK       (TMR6_IRQ_EN_CNT_MATCH_A           |            \
                                TMR6_IRQ_EN_CNT_MATCH_B           |            \
                                TMR6_IRQ_EN_CNT_MATCH_C           |            \
                                TMR6_IRQ_EN_CNT_MATCH_D           |            \
                                TMR6_IRQ_EN_CNT_MATCH_E           |            \
                                TMR6_IRQ_EN_CNT_MATCH_F           |            \
                                TMR6_IRQ_EN_OVERFLOW              |            \
                                TMR6_IRQ_EN_UNDERFLOW             |            \
                                TMR6_IRQ_EN_DEAD_TIME_ERR         |            \
                                TMR6_IRQ_EN_UPCNT_SP_MATCH_A      |            \
                                TMR6_IRQ_EN_DOWNCNT_SP_MATCH_A    |            \
                                TMR6_IRQ_EN_UPCNT_SP_MATCH_B      |            \
                                TMR6_IRQ_EN_DOWNCNT_SP_MATCH_B)

#define TMR6_STAT_FLAG_MASK    (TMR6_STAT_CNT_MATCH_A             |            \
                                TMR6_STAT_CNT_MATCH_B             |            \
                                TMR6_STAT_CNT_MATCH_C             |            \
                                TMR6_STAT_CNT_MATCH_D             |            \
                                TMR6_STAT_CNT_MATCH_E             |            \
                                TMR6_STAT_CNT_MATCH_F             |            \
                                TMR6_STAT_OVERFLOW                |            \
                                TMR6_STAT_UNDERFLOW               |            \
                                TMR6_STAT_DEAD_TIME_ERR           |            \
                                TMR6_STAT_UPCNT_SP_MATCH_A        |            \
                                TMR6_STAT_DOWNCNT_SP_MATCH_A      |            \
                                TMR6_STAT_UPCNT_SP_MATCH_B        |            \
                                TMR6_STAT_DOWNCNT_SP_MATCH_B      |            \
                                TMR6_STAT_CNT_DIR)

#define TMR6_SW_CTRL_REG_MASK  (TMR6_SSTAR_SSTA1                  |            \
                                TMR6_SSTAR_SSTA2                  |            \
                                TMR6_SSTAR_SSTA3                  |            \
                                TMR6_SSTAR_SSTA4                  |            \
                                TMR6_SSTAR_SSTA5                  |            \
                                TMR6_SSTAR_SSTA6                  |            \
                                TMR6_SSTAR_SSTA7                  |            \
                                TMR6_SSTAR_SSTA8)




/**
 * @defgroup TMR6_Check_Parameters_Validity TMR6 Check Parameters Validity
 * @{
 */

/*! Parameter valid check for normal timer6 unit */
#define IS_VALID_TMR6_UNIT(__TMR6x__)                                          \
(   (M4_TMR6_1 == (__TMR6x__))                  ||                             \
    (M4_TMR6_2 == (__TMR6x__))                  ||                             \
    (M4_TMR6_3 == (__TMR6x__))                  ||                             \
    (M4_TMR6_4 == (__TMR6x__))                  ||                             \
    (M4_TMR6_5 == (__TMR6x__))                  ||                             \
    (M4_TMR6_6 == (__TMR6x__))                  ||                             \
    (M4_TMR6_7 == (__TMR6x__))                  ||                             \
    (M4_TMR6_8 == (__TMR6x__)))

/*! Parameter valid check for interrupt source configuration */
#define IS_VALID_IRQ_SOURCE_CONFIG(x)                                          \
(   ((x) != 0UL)                                     &&                        \
    (((x) | TMR6_IRQ_EN_MASK) == TMR6_IRQ_EN_MASK))

/*! Parameter valid check for status bit read */
#define IS_VALID_STABIT_GET(x)                                                 \
(   ((x) != 0UL)                          &&                                   \
    (((x) | TMR6_STAT_FLAG_MASK) == TMR6_STAT_FLAG_MASK))

/*! Parameter valid check for period register */
#define IS_VALID_PERIOD_REG(x)                                                 \
(   (TMR6_PERIOD_REG_A == (x))           ||                                    \
    (TMR6_PERIOD_REG_B == (x))           ||                                    \
    (TMR6_PERIOD_REG_C == (x)))

/*! Parameter valid check for general compare register */
#define IS_VALID_CMP_REG(x)                                                    \
(   (TMR6_CMP_REG_A == (x))              ||                                    \
    (TMR6_CMP_REG_B == (x))              ||                                    \
    (TMR6_CMP_REG_C == (x))              ||                                    \
    (TMR6_CMP_REG_D == (x))              ||                                    \
    (TMR6_CMP_REG_E == (x))              ||                                    \
    (TMR6_CMP_REG_F == (x)))

/*! Parameter valid check for general/special compare channel */
#define IS_VALID_CMP_CH(x)                                                     \
(   (TMR6_CH_A == (x))                   ||                                    \
    (TMR6_CH_B == (x)))

/*! Parameter valid check for buffer function status */
#define IS_VALID_BUF_STAT(x)                                                   \
(   (TMR6_BUF_FUNC_OFF == (x))           ||                                    \
    (TMR6_BUF_FUNC_ON == (x)))

/*! Parameter valid check for buffer function number */
#define IS_VALID_BUF_FUN_NUM(x)                                                \
(   (TMR6_BUF_FUNC_SINGLE == (x))        ||                                    \
    (TMR6_BUF_FUNC_DOUBLE == (x)))

/*! Parameter valid check for buffer transfer timer configuration */
#define IS_VALID_BUF_TRANS_TIM(x)                                              \
(   (TMR6_BUF_TRANS_TIM_NONE == (x))     ||                                    \
    (TMR6_BUF_TRANS_TIM_OVERFLOW == (x)) ||                                    \
    (TMR6_BUF_TRANS_TIM_UNDERFLOW == (x))||                                    \
    (TMR6_BUF_TRANS_TIM_BOTH == (x)))

/*! Parameter valid check for valid period function status for channel A */
#define IS_VALID_VALID_PERIOD_STAT_CHA(x)                                      \
(   (TMR6_VALID_PERIOD_FUNC_CHA_OFF == (x))   ||                               \
    (TMR6_VALID_PERIOD_FUNC_CHA_ON == (x)))

/*! Parameter valid check for valid period function status for channel B */
#define IS_VALID_VALID_PERIOD_STAT_CHB(x)                                      \
(   (TMR6_VALID_PERIOD_FUNC_CHB_OFF == (x))   ||                               \
    (TMR6_VALID_PERIOD_FUNC_CHB_ON == (x)))

/*! Parameter valid check for count condition for valid period function */
#define IS_VALID_PERIOD_CNT_COND(x)                                            \
(   (TMR6_VALID_PERIOD_FUNC_OFF == (x))             ||                         \
    (TMR6_VALID_PERIOD_CNT_COND_UNDERFLOW == (x))   ||                         \
    (TMR6_VALID_PERIOD_CNT_COND_OVERFLOW == (x))    ||                         \
    (TMR6_VALID_PERIOD_CNT_COND_BOTH == (x)))

/*! Parameter valid check for count condition for valid period count */
#define IS_VALID_PERIOD_CNT(x)                                                 \
(   (TMR6_VALID_PERIOD_CNT_INVALID == (x))          ||                         \
    (TMR6_VALID_PERIOD_CNT_1 == (x))                ||                         \
    (TMR6_VALID_PERIOD_CNT_2 == (x))                ||                         \
    (TMR6_VALID_PERIOD_CNT_3 == (x))                ||                         \
    (TMR6_VALID_PERIOD_CNT_4 == (x))                ||                         \
    (TMR6_VALID_PERIOD_CNT_5 == (x))                ||                         \
    (TMR6_VALID_PERIOD_CNT_6 == (x))                ||                         \
    (TMR6_VALID_PERIOD_CNT_7 == (x)))

/*! Parameter valid check for count register data range */
#define IS_VALID_REG_RANGE_U16(x)               ((x) <= 0xFFFFUL)

/*! Parameter valid check for dead time register */
#define IS_VALID_DEADTIME_REG(x)                                               \
(   (TMR6_DEADTIME_REG_UP_A == (x))             ||                             \
    (TMR6_DEADTIME_REG_DOWN_A == (x))           ||                             \
    (TMR6_DEADTIME_REG_UP_B == (x))             ||                             \
    (TMR6_DEADTIME_REG_DOWN_B == (x)))

/*! Parameter valid check for input port */
#define IS_VALID_INPUT_PORT(x)                                                 \
(   (TMR6_IO_PWMA == (x))                       ||                             \
    (TMR6_IO_PWMB == (x))                       ||                             \
    (TMR6_INPUT_TRIGA == (x))                   ||                             \
    (TMR6_INPUT_TRIGB == (x))                   ||                             \
    (TMR6_INPUT_TRIGC == (x))                   ||                             \
    (TMR6_INPUT_TRIGD == (x)))

/*! Parameter valid check for output port */
#define IS_VALID_OUTPUT_PORT(x)                                                \
(   (TMR6_IO_PWMA == (x))                       ||                             \
    (TMR6_IO_PWMB == (x)))

/*! Parameter valid check for input port filter clock */
#define IS_VALID_INPUT_FILTER_CLK(x)                                           \
(   (TMR6_INPUT_FILTER_PCLK0_DIV1 == (x))       ||                             \
    (TMR6_INPUT_FILTER_PCLK0_DIV4 == (x))       ||                             \
    (TMR6_INPUT_FILTER_PCLK0_DIV16 == (x))      ||                             \
    (TMR6_INPUT_FILTER_PCLK0_DIV64 == (x)))

/*! Parameter valid check for port function mode*/
#define IS_VALID_PORT_MODE_FUNC(x)                                             \
(   (TMR6_PORT_COMPARE_OUTPUT == (x))           ||                             \
    (TMR6_PORT_CAPTURE_INPUT == (x)))

/*! Parameter valid check for port input filter function status */
#define IS_VALID_PORT_INPUT_FILTER_STA(x)                                      \
(   (TMR6_PORT_INPUT_FILTER_OFF == (x))         ||                             \
    (TMR6_PORT_INPUT_FILTER_ON == (x)))

/*! Parameter valid check for output port status for count result  */
#define IS_VALID_OUTPUT_STA_RESULT(x)                                          \
(   (TMR6_PORT_OUTPUT_STA_LOW == (x))           ||                             \
    (TMR6_PORT_OUTPUT_STA_HIGH == (x))          ||                             \
    (TMR6_PORT_OUTPUT_STA_HOLD == (x))          ||                             \
    (TMR6_PORT_OUTPUT_STA_REVERSE == (x)))

/*! Parameter valid check for force output port status for count result  */
#define IS_VALID_FORCE_OUTPUT_STA_RESULT(x)                                    \
(   (TMR6_FORCE_PORT_OUTPUT_INVALID == (x))     ||                             \
    (TMR6_FORCE_PORT_OUTPUT_STA_LOW == (x))     ||                             \
    (TMR6_FORCE_PORT_OUTPUT_STA_HIGH == (x)))

/*! Parameter valid check for output port status for count status  */
#define IS_VALID_OUTPUT_STA_STA(x)                                             \
(   (TMR6_PORT_OUTPUT_STA_LOW == (x))           ||                             \
    (TMR6_PORT_OUTPUT_STA_HIGH == (x))          ||                             \
    (TMR6_PORT_OUTPUT_STA_HOLD == (x)))

/*! Parameter valid check for EMB event valid channel  */
#define IS_VALID_EMB_CH(x)                                                     \
(   (TMR6_EMB_EVENT_VALID_CH0 == (x))           ||                             \
    (TMR6_EMB_EVENT_VALID_CH1 == (x))           ||                             \
    (TMR6_EMB_EVENT_VALID_CH2 == (x))           ||                             \
    (TMR6_EMB_EVENT_VALID_CH3 == (x)))

/*! Parameter valid check for EMB release mode when EMB event invalid   */
#define IS_VALID_EMB_RELEASE_MODE(x)                                           \
(   (TMR6_EMB_RELEASE_IMMEDIATE == (x))         ||                             \
    (TMR6_EMB_RELEASE_OVERFLOW == (x))          ||                             \
    (TMR6_EMB_RELEASE_UNDERFLOW == (x))         ||                             \
    (TMR6_EMB_RELEASE_OVERFLOW_UNDERFLOW == (x)))

/*! Parameter valid check for port output status when EMB event valid */
#define IS_VALID_EMB_VALID_PORT_STA(x)                                         \
(   (TMR6_EMB_PORTSTA_NORMAL == (x))            ||                             \
    (TMR6_EMB_PORTSTA_HIZ == (x))               ||                             \
    (TMR6_EMB_PORTSTA_LOW == (x))               ||                             \
    (TMR6_EMB_PORTSTA_HIGH == (x)))

/*! Parameter valid check for dead time buffer function for DTUAR and DTUBR register */
#define IS_VALID_DEADTIME_BUF_FUNC_DTUAR_REG(x)                                \
(   (TMR6_DEADTIME_CNT_UP_BUF_OFF == (x))       ||                             \
    (TMR6_DEADTIME_CNT_UP_BUF_ON == (x)))

/*! Parameter valid check for dead time buffer function for DTDAR and DTDBR register */
#define IS_VALID_DEADTIME_BUF_FUNC_DTDAR_REG(x)                                \
(   (TMR6_DEADTIME_CNT_DOWN_BUF_OFF == (x))     ||                             \
    (TMR6_DEADTIME_CNT_DOWN_BUF_ON == (x)))

/*! Parameter valid check for dead time buffer transfer condition */
#define IS_VALID_DEADTIME_BUF_TRANS_COND_REG(x)                                \
(   (TMR6_DEADTIME_TRANS_COND_NONE == (x))      ||                             \
    (TMR6_DEADTIME_TRANS_COND_OVERFLOW == (x))  ||                             \
    (TMR6_DEADTIME_TRANS_COND_UNDERFLOW == (x)) ||                             \
    (TMR6_DEADTIME_TRANS_COND_BOTH == (x)))

/*! Parameter valid check for dead time equal function for DTUAR and DTDAR register */
#define IS_VALID_DEADTIME_EQUAL_FUNC_REG(x)                                    \
(   (TMR6_DEADTIME_EQUAL_OFF == (x))            ||                             \
    (TMR6_DEADTIME_EQUAL_ON == (x)))

/*! Parameter valid check for hardware control events   */
#define IS_VALID_HW_CTRL_EVENTS(x)                                             \
(   ((x) != 0UL)                                     &&                        \
    (((x) | TMR6_HW_CTRL_EVENT_MASK) == TMR6_HW_CTRL_EVENT_MASK))

/*! Parameter valid check for hardware count events   */
#define IS_VALID_HW_CNT_EVENTS(x)                                              \
(   ((x) != 0UL)                                     &&                        \
    (((x) | TMR6_HW_CNT_EVENT_MASK) == TMR6_HW_CNT_EVENT_MASK))

/*! Parameter valid check for count Mode */
#define IS_VALID_CNT_MODE(x)                                                   \
(   (TMR6_MODE_SAWTOOTH == (x))                 ||                             \
    (TMR6_MODE_TRIANGLE == (x)))

/*! Parameter valid check for count direction */
#define IS_VALID_CNT_DIRECTION(x)                                              \
(   (TMR6_CNT_INCREASE == (x))                  ||                             \
    (TMR6_CNT_DECREASE == (x)))

/*! Parameter valid check for count clock source  */
#define IS_VALID_CNT_CLK_SRC(x)                                                \
(   (TMR6_CLK_PCLK0_DIV1 == (x))                ||                             \
    (TMR6_CLK_PCLK0_DIV2 == (x))                ||                             \
    (TMR6_CLK_PCLK0_DIV4 == (x))                ||                             \
    (TMR6_CLK_PCLK0_DIV8 == (x))                ||                             \
    (TMR6_CLK_PCLK0_DIV16 == (x))               ||                             \
    (TMR6_CLK_PCLK0_DIV32 == (x))               ||                             \
    (TMR6_CLK_PCLK0_DIV64 == (x))               ||                             \
    (TMR6_CLK_PCLK0_DIV128 == (x))              ||                             \
    (TMR6_CLK_PCLK0_DIV256 == (x))              ||                             \
    (TMR6_CLK_PCLK0_DIV512 == (x))              ||                             \
    (TMR6_CLK_PCLK0_DIV1024 == (x)))

/*! Parameter valid check for stop when overflow mode */
#define IS_VALID_STOP_AFTER_OVF_MODE(x)                                        \
(   (TMR6_CNT_CONTINUOUS == (x))                ||                             \
    (TMR6_STOP_AFTER_OVF == (x)))

/*! Parameter valid check for Z Mask input function mask cycles number  */
#define IS_VALID_ZMASK_CYCLES(x)                                               \
(   (TMR6_ZMASK_CYCLE_FUNC_INVALID == (x))      ||                             \
    (TMR6_ZMASK_CYCLE_4 == (x))                 ||                             \
    (TMR6_ZMASK_CYCLE_8 == (x))                 ||                             \
    (TMR6_ZMASK_CYCLE_16 == (x)))

/*! Parameter valid check for Z Mask function of timer6 position unit */
#define IS_VALID_POS_UNIT_ZMASK_FUNC(x)                                        \
(   (TMR6_POS_CLR_ZMASK_FUNC_INVALID == (x))    ||                             \
    (TMR6_POS_CLR_ZMASK_FUNC_VALID == (x)))

/*! Parameter valid check for Z Mask function of timer6 revolution unit */
#define IS_VALID_REVO_UNIT_ZMASK_FUNC(x)                                       \
(   (TMR6_REVO_CNT_ZMASK_FUNC_INVALID == (x))   ||                             \
    (TMR6_REVO_CNT_ZMASK_FUNC_VALID == (x)))

/*! Parameter valid check for hardware trigger index  */
#define IS_VALID_HW_TRIGGER_INDEX(x)                                           \
(   (TMR6_HW_TRIG_0 == (x))                     ||                             \
    (TMR6_HW_TRIG_1 == (x))                     ||                             \
    (TMR6_HW_TRIG_2 == (x))                     ||                             \
    (TMR6_HW_TRIG_3 == (x)))

/*! Parameter valid check for software sync control unit configuration */
#define IS_VALID_SW_CTRL_CFG(x)                                                \
(   ((x) != 0UL)                                     &&                        \
    (((x) | TMR6_SW_CTRL_REG_MASK) == TMR6_SW_CTRL_REG_MASK))

/*! Parameter valid check for common trigger configuration. */
#define IS_VALID_TMR6_COM_TRIG(x)                                              \
(   ((x) != 0x00UL)                        &&                                  \
    (((x) | TMR6_COM_TRIG_MASK) == TMR6_COM_TRIG_MASK))

/* Unit check for TMR6 which data width is 32 bit */
#define IS_TMR6_32BIT_UINT(x)                                                  \
(   (M4_TMR6_1 == (x))                          ||                             \
    (M4_TMR6_2 == (x))                          ||                             \
    (M4_TMR6_3 == (x))                          ||                             \
    (M4_TMR6_4 == (x)))

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
 * @brief  Timer6 interrupt request enable or disable
 * @param  [in] TMR6x            Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32Tmr6Irq       Irq source,  Can be one or any combination of
 *                               the values from @ref TMR6_Interrupt_Enable_Bit_Define
 * @param  [in] enNewState       Disable or Enable the function
 * @retval None
 */
void TMR6_IntCmd(M4_TMR6_TypeDef *TMR6x, uint32_t u32Tmr6Irq, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_IRQ_SOURCE_CONFIG(u32Tmr6Irq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->ICONR, u32Tmr6Irq);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->ICONR, u32Tmr6Irq);
    }
}

/**
 * @brief  Get Timer6 status flag
 * @param  [in] TMR6x           Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32StaBit       Status bit to be read, Can be one or any combination of
 *                              the values from @ref TMR6_Sta_Bit_Get_Define
 * @retval An en_flag_status_t enumeration value.
 *  @arg Set:                   Status bit is set
 *  @arg Reset:                 Status bit is reset
 */
en_flag_status_t TMR6_GetSta(const M4_TMR6_TypeDef *TMR6x, uint32_t u32StaBit)
{
    en_flag_status_t enRet = Reset;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_STABIT_GET(u32StaBit));

    if(0UL != READ_REG32_BIT(TMR6x->STFLR, u32StaBit))
    {
        enRet =  Set;
    }
    return enRet;
}

/**
 * @brief  Get Timer6 period number when valid period function enable
 * @param  [in] TMR6x           Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval A uint32_t data for periods number
 */
uint32_t TMR6_GetPeriodNum(const M4_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    return (READ_REG32_BIT(TMR6x->STFLR, TMR6_STFLR_VPERNUM) >> TMR6_STFLR_VPERNUM_POS);
}

/**
 * @brief  De-initialize the timer6 unit
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_DeInit(M4_TMR6_TypeDef *TMR6x)
{
    uint32_t u32RefRegRstValue;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        u32RefRegRstValue = TMR6_REG_REFERENCE_RESET_VALUE_U32;
    }
    else
    {
        u32RefRegRstValue = TMR6_REG_REFERENCE_RESET_VALUE_U16;
    }

    WRITE_REG32(TMR6x->GCONR, TMR6_REG_GCONR_RESET_VALUE);
    WRITE_REG32(TMR6x->CNTER, 0x00000000UL);
    WRITE_REG32(TMR6x->UPDAR, 0x00000000UL);
    WRITE_REG32(TMR6x->PERAR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->PERBR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->PERCR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->GCMAR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->GCMBR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->GCMCR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->GCMDR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->GCMER, u32RefRegRstValue);
    WRITE_REG32(TMR6x->GCMFR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->SCMAR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->SCMBR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->SCMCR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->SCMDR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->SCMER, u32RefRegRstValue);
    WRITE_REG32(TMR6x->SCMFR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->DTUAR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->DTDAR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->DTUBR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->DTDBR, u32RefRegRstValue);
    WRITE_REG32(TMR6x->ICONR, 0x00000000UL);
    WRITE_REG32(TMR6x->BCONR, 0x00000000UL);
    WRITE_REG32(TMR6x->DCONR, 0x00000000UL);
    WRITE_REG32(TMR6x->PCNAR, 0x00000000UL);
    WRITE_REG32(TMR6x->PCNBR, 0x00000000UL);
    WRITE_REG32(TMR6x->FCNGR, 0x00000000UL);
    WRITE_REG32(TMR6x->VPERR, 0x00000000UL);
    WRITE_REG32(TMR6x->STFLR, 0x00000000UL);
    WRITE_REG32(TMR6x->HSTAR, 0x00000000UL);
    WRITE_REG32(TMR6x->HSTPR, 0x00000000UL);
    WRITE_REG32(TMR6x->HCLRR, 0x00000000UL);
    WRITE_REG32(TMR6x->HUPDR, 0x00000000UL);
    WRITE_REG32(TMR6x->HCPAR, 0x00000000UL);
    WRITE_REG32(TMR6x->HCPBR, 0x00000000UL);
    WRITE_REG32(TMR6x->HCUPR, 0x00000000UL);
    WRITE_REG32(TMR6x->HCDOR, 0x00000000UL);
}

/**
 * @brief  Initialize the timer6 unit
 * @param  [in] TMR6x                      Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] pstcTmr6BaseCntCfg         Pointer of configuration structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                               Successfully done
 *  @arg ErrorInvalidParameter:            Parameter error
 */
en_result_t TMR6_Init(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_basecnt_cfg_t* pstcTmr6BaseCntCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if(NULL != pstcTmr6BaseCntCfg)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_CNT_MODE(pstcTmr6BaseCntCfg->u32CntMode));
        DDL_ASSERT(IS_VALID_CNT_DIRECTION(pstcTmr6BaseCntCfg->u32CntDir));
        DDL_ASSERT(IS_VALID_CNT_CLK_SRC(pstcTmr6BaseCntCfg->u32CntClkDiv));
        DDL_ASSERT(IS_VALID_STOP_AFTER_OVF_MODE(pstcTmr6BaseCntCfg->u32CntStpAftOvf));

        MODIFY_REG32(TMR6x->GCONR,
                    TMR6_INITIAL_MASK,
                    (pstcTmr6BaseCntCfg->u32CntMode      \
                    | pstcTmr6BaseCntCfg->u32CntDir      \
                    | pstcTmr6BaseCntCfg->u32CntClkDiv   \
                    | pstcTmr6BaseCntCfg->u32CntStpAftOvf));
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Timer6 unit Z phase input mask config
 * @param  [in] TMR6x                      Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] pstcTmr6ZMaskCfg           Pointer of configuration structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                               Successfully done
 *  @arg ErrorInvalidParameter:            Parameter error
 */
en_result_t TMR6_ZMaskCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_zmask_cfg_t* pstcTmr6ZMaskCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if(NULL != pstcTmr6ZMaskCfg)
    {
        DDL_ASSERT(IS_VALID_ZMASK_CYCLES(pstcTmr6ZMaskCfg->u32ZMaskCycle));
        DDL_ASSERT(IS_VALID_POS_UNIT_ZMASK_FUNC(pstcTmr6ZMaskCfg->u32PosCntMaskEn));
        DDL_ASSERT(IS_VALID_REVO_UNIT_ZMASK_FUNC(pstcTmr6ZMaskCfg->u32RevCntMaskEn));

        MODIFY_REG32(TMR6x->GCONR,
                    TMR6_ZMASK_CFG_MASK,
                    pstcTmr6ZMaskCfg->u32ZMaskCycle | pstcTmr6ZMaskCfg->u32PosCntMaskEn | pstcTmr6ZMaskCfg->u32RevCntMaskEn);

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Timer6 counter function command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] enNewState  Disable or Enable the function
 * @retval None
 */
void TMR6_CountCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->GCONR, TMR6_GCONR_START);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->GCONR, TMR6_GCONR_START);
    }
}

/**
 * @brief  Timer6 counter register set
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32Value    Counter value
 * @retval None
 */
void TMR6_SetCntReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        WRITE_REG32(TMR6x->CNTER, u32Value);
    }
    else
    {
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
        WRITE_REG16(TMR6x->CNTER, u32Value);
    }

}

/**
 * @brief  Timer6 update register set
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32Value    Counter value
 * @retval None
 */
void TMR6_SetUpdateReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        WRITE_REG32(TMR6x->UPDAR, u32Value);
    }
    else
    {
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32Value));
        WRITE_REG16(TMR6x->UPDAR, u32Value);
    }
}

/**
 * @brief  Timer6 get counter register value
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval A uint32_t data for the count register value
 */
uint32_t TMR6_GetCntReg(const M4_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    return READ_REG32(TMR6x->CNTER);
}

/**
 * @brief  Timer6 get update register value
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval A uint32_t data for register value
 */
uint32_t TMR6_GetUpdateReg(const M4_TMR6_TypeDef *TMR6x)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    return READ_REG32(TMR6x->UPDAR);
}

/**
 * @brief  Timer6 set period register(A~C)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32PeriodReg        Period register to be write, @ref TMR6_Period_Register_Index_Define
 * @param  [in] u32PeriodVal        Period value for write
 * @retval None
 */
void TMR6_SetPeriodReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32PeriodReg, uint32_t u32PeriodVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_PERIOD_REG(u32PeriodReg));
    __IO uint32_t *TMR6_PERxR = (uint32_t *)((uint32_t)&TMR6x->PERAR + 4UL * u32PeriodReg);

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        /* 32bit */
        WRITE_REG32(*TMR6_PERxR, u32PeriodVal);
    }
    else
    {
        /* 16bit */
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32PeriodVal));
        WRITE_REG16(*TMR6_PERxR, u32PeriodVal);
    }
}

/**
 * @brief  Timer6 set general compare register(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32GenCmpReg        General compare register to be write, @ref TMR6_Compare_Register_Index_Define
 * @param  [in] u32CmpVal           Value for write
 * @retval None
 */
void TMR6_SetGenCmpReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32GenCmpReg, uint32_t u32CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32GenCmpReg));
    __IO uint32_t *TMR6_GCMxR = (__IO uint32_t *)((uint32_t)&TMR6x->GCMAR + 4UL * u32GenCmpReg);

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        /* 32bit */
        WRITE_REG32(*TMR6_GCMxR ,u32CmpVal);
    }
    else
    {
        /* 16bit */
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32CmpVal));
        WRITE_REG16(*TMR6_GCMxR ,u32CmpVal);
    }
}

/**
 * @brief  Timer6 set special compare register(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32SpecialCmpReg    Special compare register to be write, @ref TMR6_Compare_Register_Index_Define
 * @param  [in] u32CmpVal           Value for write
 * @retval None
 */
void TMR6_SetSpecialCmpReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32SpecialCmpReg, uint32_t u32CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32SpecialCmpReg));
    __IO uint32_t *TMR6_SCMxR = (uint32_t *)((uint32_t)&TMR6x->SCMAR + 4UL * u32SpecialCmpReg);

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        /* 32bit */
        WRITE_REG32(*TMR6_SCMxR, u32CmpVal);
    }
    else
    {
        /* 16bit */
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32CmpVal));
        WRITE_REG16(*TMR6_SCMxR, u32CmpVal);
    }
}

/**
 * @brief  Timer6 set dead time registerr
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32DeadTimeReg      Special compare register to be write, @ref TMR6_DeadTime_Reg_Define
 * @param  [in] u32CmpVal           Value for write
 * @retval None
 */
void TMR6_SetDeadTimeReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32DeadTimeReg, uint32_t u32CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_DEADTIME_REG(u32DeadTimeReg));
    __IO uint32_t *TMR6_DTxyR = (uint32_t *)((uint32_t)&TMR6x->DTUAR + 4UL * u32DeadTimeReg);

    if(IS_TMR6_32BIT_UINT(TMR6x))
    {
        /* 32bit */
        WRITE_REG32(*TMR6_DTxyR, u32CmpVal);
    }
    else
    {
        /* 16bit */
        DDL_ASSERT(IS_VALID_REG_RANGE_U16(u32CmpVal));
        WRITE_REG16(*TMR6_DTxyR, u32CmpVal);
    }
}

/**
 * @brief  Timer6 get general compare registers value(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32GenCmpReg        General compare register to be read, @ref TMR6_Compare_Register_Index_Define
 * @retval A uint32_t data for value of the register
 */
uint32_t TMR6_GetGenCmpReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32GenCmpReg)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32GenCmpReg));
    __IO uint32_t *TMR6_GCMxR = (uint32_t *)((uint32_t)&TMR6x->GCMAR + 4UL * u32GenCmpReg);

    return READ_REG32(*TMR6_GCMxR);
}

/**
 * @brief  Timer6 get special compare registers value(A~F)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32SpecialCmpReg    Special compare register to be read, @ref TMR6_Compare_Register_Index_Define
 * @retval A uint32_t data for value of the register
 */
uint32_t TMR6_GetSpecialCmpReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32SpecialCmpReg)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_CMP_REG(u32SpecialCmpReg));
    __IO uint32_t *TMR6_SCMxR = (uint32_t *)((uint32_t)&TMR6x->SCMAR + 4UL * u32SpecialCmpReg);

    return READ_REG32(*TMR6_SCMxR);
}

/**
 * @brief  Timer6 Get period register(A~C)
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32PeriodReg        Period register to be write, @ref TMR6_Period_Register_Index_Define
 * @retval A uint32_t data for value of the register
 */
uint32_t TMR6_GetPeriodReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32PeriodReg)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_PERIOD_REG(u32PeriodReg));
    __IO uint32_t *TMR6_PERxR = (uint32_t *)((uint32_t)&TMR6x->PERAR + 4UL * u32PeriodReg);

    return READ_REG32(*TMR6_PERxR);
}

/**
 * @brief  Timer6 get dead time register
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32DeadTimeReg      Dead time register to be write, @ref TMR6_DeadTime_Reg_Define
 * @retval A uint32_t data for value of the register
 */
uint32_t TMR6_GetDeadTimeReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32DeadTimeReg)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_DEADTIME_REG(u32DeadTimeReg));
    __IO uint32_t *TMR6_DTxyR = (uint32_t *)((uint32_t)&TMR6x->DTUAR + 4UL * u32DeadTimeReg);

    return READ_REG32(*TMR6_DTxyR);
}

/**
 * @brief  Timer6 general compare buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CmpChIdx         General compare buffer chose, @ref TMR6_Compare_channel_Define
 * @param  [in] pstcGenBufCfg       Pointer of configuration structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_GenCmpBufCfg(M4_TMR6_TypeDef *TMR6x, uint32_t u32CmpChIdx, const stc_tmr6_buf_func_cfg_t* pstcGenBufCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
    if(NULL != pstcGenBufCfg)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
        DDL_ASSERT(IS_VALID_CMP_CH(u32CmpChIdx));
        DDL_ASSERT(IS_VALID_BUF_STAT(pstcGenBufCfg->u32BufFunCmd));
        DDL_ASSERT(IS_VALID_BUF_FUN_NUM(pstcGenBufCfg->u32BufNum));
        DDL_ASSERT(IS_VALID_BUF_TRANS_TIM(pstcGenBufCfg->u32BufTransTim));

        if(TMR6_CH_A == u32CmpChIdx)
        {
            MODIFY_REG32(TMR6x->BCONR,
                        BCONR_REG_CFG_MSK<<BCONR_GEN_BUF_CHA_OFFSET,
                        (pstcGenBufCfg->u32BufFunCmd | pstcGenBufCfg->u32BufNum | pstcGenBufCfg->u32BufTransTim)<<BCONR_GEN_BUF_CHA_OFFSET);
        }
        else
        {
            MODIFY_REG32(TMR6x->BCONR,
                        BCONR_REG_CFG_MSK<<BCONR_GEN_BUF_CHB_OFFSET,
                        (pstcGenBufCfg->u32BufFunCmd | pstcGenBufCfg->u32BufNum | pstcGenBufCfg->u32BufTransTim)<<BCONR_GEN_BUF_CHB_OFFSET);
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Timer6 special compare buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CmpChIdx         Special compare buffer chose, @ref TMR6_Compare_channel_Define
 * @param  [in] pstcSpecialBufCfg   Pointer of configuration structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_SpecialCmpBufCfg(M4_TMR6_TypeDef *TMR6x, uint32_t u32CmpChIdx, const stc_tmr6_buf_func_cfg_t* pstcSpecialBufCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
    if(NULL != pstcSpecialBufCfg)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
        DDL_ASSERT(IS_VALID_CMP_CH(u32CmpChIdx));
        DDL_ASSERT(IS_VALID_BUF_STAT(pstcSpecialBufCfg->u32BufFunCmd));
        DDL_ASSERT(IS_VALID_BUF_FUN_NUM(pstcSpecialBufCfg->u32BufNum));
        DDL_ASSERT(IS_VALID_BUF_TRANS_TIM(pstcSpecialBufCfg->u32BufTransTim));

        if(TMR6_CH_A == u32CmpChIdx)
        {
            MODIFY_REG32(TMR6x->BCONR,
                        BCONR_REG_CFG_MSK<<BCONR_SPECIAL_BUF_CHA_OFFSET,
                        (pstcSpecialBufCfg->u32BufFunCmd | pstcSpecialBufCfg->u32BufNum | pstcSpecialBufCfg->u32BufTransTim)<<BCONR_SPECIAL_BUF_CHA_OFFSET);
        }
        else
        {
            MODIFY_REG32(TMR6x->BCONR,
                        BCONR_REG_CFG_MSK<<BCONR_SPECIAL_BUF_CHB_OFFSET,
                        (pstcSpecialBufCfg->u32BufFunCmd | pstcSpecialBufCfg->u32BufNum | pstcSpecialBufCfg->u32BufTransTim)<<BCONR_SPECIAL_BUF_CHB_OFFSET);
        }
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Timer6 period buffer function configuration
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] pstcPeriodBufCfg    Pointer of configuration structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_PeriodBufCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_buf_func_cfg_t* pstcPeriodBufCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
    if(NULL != pstcPeriodBufCfg)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
        DDL_ASSERT(IS_VALID_BUF_STAT(pstcPeriodBufCfg->u32BufFunCmd));
        DDL_ASSERT(IS_VALID_BUF_FUN_NUM(pstcPeriodBufCfg->u32BufNum));
        DDL_ASSERT(IS_VALID_BUF_TRANS_TIM(pstcPeriodBufCfg->u32BufTransTim));

        MODIFY_REG32(TMR6x->BCONR,
                   BCONR_REG_CFG_MSK<<BCONR_PERIOD_BUF_OFFSET,
                  (pstcPeriodBufCfg->u32BufFunCmd | pstcPeriodBufCfg->u32BufNum | pstcPeriodBufCfg->u32BufTransTim)<<BCONR_PERIOD_BUF_OFFSET);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Timer6 valid period function configuration for special compare function
 * @param  [in] TMR6x               Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] pstcValidPeriodCfg  Pointer of configuration structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_ValidPeriodCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_valid_period_func_cfg_t* pstcValidPeriodCfg)
{
    en_result_t enRet = ErrorInvalidParameter;
    if(NULL != pstcValidPeriodCfg)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

        DDL_ASSERT(IS_VALID_VALID_PERIOD_STAT_CHA(pstcValidPeriodCfg->u32StatChA));
        DDL_ASSERT(IS_VALID_VALID_PERIOD_STAT_CHB(pstcValidPeriodCfg->u32StatChB));
        DDL_ASSERT(IS_VALID_PERIOD_CNT_COND(pstcValidPeriodCfg->u32CntCond));
        DDL_ASSERT(IS_VALID_PERIOD_CNT(pstcValidPeriodCfg->u32PeriodInterval));

        WRITE_REG32(TMR6x->VPERR, pstcValidPeriodCfg->u32StatChA |
                                    pstcValidPeriodCfg->u32StatChB |
                                    pstcValidPeriodCfg->u32CntCond |
                                    pstcValidPeriodCfg->u32PeriodInterval);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Port input configuration(Trig)
 * @param  [in]  TMR6x                  Timer6 unit
 * @param  [in]  u32PortSel             Input port to be configured
 *  @arg  TMR6_IO_PWMA
 *  @arg  TMR6_IO_PWMB
 *  @arg  TMR6_INPUT_TRIGA
 *  @arg  TMR6_INPUT_TRIGB
 *  @arg  TMR6_INPUT_TRIGC
 *  @arg  TMR6_INPUT_TRIGD
 * @param  [in]  pstcTmr6PortInputCfg   Point Input Config Pointer
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                            Successfully done
 *  @arg ErrorInvalidParameter:         Parameter error
 */
en_result_t TMR6_PortInputConfig(M4_TMR6_TypeDef *TMR6x,
                                    uint32_t u32PortSel,
                                    const stc_tmr6_port_input_cfg_t* pstcTmr6PortInputCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcTmr6PortInputCfg)
    {
        DDL_ASSERT(IS_VALID_INPUT_PORT(u32PortSel));
        DDL_ASSERT(IS_VALID_PORT_MODE_FUNC(pstcTmr6PortInputCfg->u32PortMode));
        DDL_ASSERT(IS_VALID_PORT_INPUT_FILTER_STA(pstcTmr6PortInputCfg->u32FilterSta));
        DDL_ASSERT(IS_VALID_INPUT_FILTER_CLK(pstcTmr6PortInputCfg->u32FltClk));

        enRet = Ok;
        switch (u32PortSel)
        {
            case TMR6_IO_PWMA:
                MODIFY_REG32(TMR6x->PCNAR,
                             TMR6_PCNAR_CAPMDA,
                             pstcTmr6PortInputCfg->u32PortMode);
                MODIFY_REG32(TMR6x->FCNGR,
                             TMR6_FCNGR_NOFIENGA | TMR6_FCNGR_NOFICKGA,
                             pstcTmr6PortInputCfg->u32FilterSta<<TMR6_FCNGR_NOFIENGA_POS
                               | pstcTmr6PortInputCfg->u32FltClk<<TMR6_FCNGR_NOFICKGA_POS);
                break;

            case TMR6_IO_PWMB:
                MODIFY_REG32(TMR6x->PCNBR,
                             TMR6_PCNBR_CAPMDB,
                             pstcTmr6PortInputCfg->u32PortMode);
                MODIFY_REG32(TMR6x->FCNGR,
                             TMR6_FCNGR_NOFIENGB | TMR6_FCNGR_NOFICKGB,
                             pstcTmr6PortInputCfg->u32FilterSta<<TMR6_FCNGR_NOFIENGB_POS
                               | pstcTmr6PortInputCfg->u32FltClk<<TMR6_FCNGR_NOFICKGB_POS);
                break;

            case TMR6_INPUT_TRIGA:
                MODIFY_REG32(M4_TMR6_1->FCNTR,
                             TMR6_FCNTR_NOFIENTA | TMR6_FCNTR_NOFICKTA,
                             pstcTmr6PortInputCfg->u32FilterSta<<TMR6_FCNTR_NOFIENTA_POS
                               | pstcTmr6PortInputCfg->u32FltClk<<TMR6_FCNTR_NOFICKTA_POS);
                break;

            case TMR6_INPUT_TRIGB:
                MODIFY_REG32(M4_TMR6_1->FCNTR,
                             TMR6_FCNTR_NOFIENTB | TMR6_FCNTR_NOFICKTB,
                             pstcTmr6PortInputCfg->u32FilterSta<<TMR6_FCNTR_NOFIENTB_POS
                               | pstcTmr6PortInputCfg->u32FltClk<<TMR6_FCNTR_NOFICKTB_POS);
                break;

            case TMR6_INPUT_TRIGC:
                MODIFY_REG32(M4_TMR6_1->FCNTR,
                             TMR6_FCNTR_NOFIENTC | TMR6_FCNTR_NOFICKTC,
                             pstcTmr6PortInputCfg->u32FilterSta<<TMR6_FCNTR_NOFIENTC_POS
                               | pstcTmr6PortInputCfg->u32FltClk<<TMR6_FCNTR_NOFICKTC_POS);
                break;

            case TMR6_INPUT_TRIGD:
                MODIFY_REG32(M4_TMR6_1->FCNTR,
                             TMR6_FCNTR_NOFIENTD | TMR6_FCNTR_NOFICKTD,
                             pstcTmr6PortInputCfg->u32FilterSta<<TMR6_FCNTR_NOFIENTD_POS
                               | pstcTmr6PortInputCfg->u32FltClk<<TMR6_FCNTR_NOFICKTD_POS);
                break;

            default:
                enRet = ErrorInvalidParameter;
                break;
        }
    }
    return enRet;

}

/**
 * @brief  Port output configuration(Trig)
 * @param  [in]  TMR6x                  Timer6 unit
 * @param  [in]  u32PortSel             Output port to be configured
 *  @arg  TMR6_IO_PWMA
 *  @arg  TMR6_IO_PWMB
 * @param  [in]  pstcTmr6PortOutputCfg  Point Output Config Pointer
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_PortOutputConfig(M4_TMR6_TypeDef *TMR6x,
                                    uint32_t u32PortSel,
                                    const stc_tmr6_port_output_cfg_t* pstcTmr6PortOutputCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcTmr6PortOutputCfg)
    {
        DDL_ASSERT(IS_VALID_OUTPUT_PORT(u32PortSel));
        DDL_ASSERT(IS_VALID_PORT_MODE_FUNC(pstcTmr6PortOutputCfg->u32PortMode));
        DDL_ASSERT(IS_VALID_FORCE_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32NextPeriodForceSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32DownCntMatchAnotherCmpRegSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32UpCntMatchAnotherCmpRegSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32DownCntMatchCmpRegSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32UpCntMatchCmpRegSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32UnderflowSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_RESULT(pstcTmr6PortOutputCfg->u32OverflowSta));

        DDL_ASSERT(IS_VALID_OUTPUT_STA_STA(pstcTmr6PortOutputCfg->u32StopSta));
        DDL_ASSERT(IS_VALID_OUTPUT_STA_STA(pstcTmr6PortOutputCfg->u32StartSta));

        if(TMR6_IO_PWMA == u32PortSel)
        {
            MODIFY_REG32(TMR6x->PCNAR,
                         PCNA_BR_REG_OUTPUT_CFG_MASK,
                         pstcTmr6PortOutputCfg->u32PortMode | TMR6_PCNAR_OUTENA
                         | pstcTmr6PortOutputCfg->u32NextPeriodForceSta << TMR6_PCNAR_FORCA_POS
                         | pstcTmr6PortOutputCfg->u32DownCntMatchAnotherCmpRegSta << TMR6_PCNAR_CMBDCA_POS
                         | pstcTmr6PortOutputCfg->u32UpCntMatchAnotherCmpRegSta << TMR6_PCNAR_CMBUCA_POS
                         | pstcTmr6PortOutputCfg->u32DownCntMatchCmpRegSta << TMR6_PCNAR_CMADCA_POS
                         | pstcTmr6PortOutputCfg->u32UpCntMatchCmpRegSta << TMR6_PCNAR_CMAUCA_POS
                         | pstcTmr6PortOutputCfg->u32UnderflowSta << TMR6_PCNAR_UDFCA_POS
                         | pstcTmr6PortOutputCfg->u32OverflowSta << TMR6_PCNAR_OVFCA_POS
                         | pstcTmr6PortOutputCfg->u32StopSta << TMR6_PCNAR_STPCA_POS
                         | pstcTmr6PortOutputCfg->u32StartSta << TMR6_PCNAR_STACA_POS);
        }
        else
        {
            MODIFY_REG32(TMR6x->PCNBR,
                         PCNA_BR_REG_OUTPUT_CFG_MASK,
                         pstcTmr6PortOutputCfg->u32PortMode | TMR6_PCNBR_OUTENB
                         | pstcTmr6PortOutputCfg->u32NextPeriodForceSta << TMR6_PCNBR_FORCB_POS
                         | pstcTmr6PortOutputCfg->u32DownCntMatchAnotherCmpRegSta << TMR6_PCNBR_CMADCB_POS
                         | pstcTmr6PortOutputCfg->u32UpCntMatchAnotherCmpRegSta << TMR6_PCNBR_CMAUCB_POS
                         | pstcTmr6PortOutputCfg->u32DownCntMatchCmpRegSta << TMR6_PCNBR_CMBDCB_POS
                         | pstcTmr6PortOutputCfg->u32UpCntMatchCmpRegSta << TMR6_PCNBR_CMBUCB_POS
                         | pstcTmr6PortOutputCfg->u32UnderflowSta << TMR6_PCNBR_UDFCB_POS
                         | pstcTmr6PortOutputCfg->u32OverflowSta << TMR6_PCNBR_OVFCB_POS
                         | pstcTmr6PortOutputCfg->u32StopSta << TMR6_PCNBR_STPCB_POS
                         | pstcTmr6PortOutputCfg->u32StartSta << TMR6_PCNBR_STACB_POS);
        }
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  EMB function configuration
 * @param  [in]  TMR6x              Timer6 unit
 * @param  [in]  u32PortSel         Output port to be configured
 *  @arg  TMR6_IO_PWMA
 *  @arg  TMR6_IO_PWMB
 * @param  [in]  pstcTmr6EmbCfg     Point EMB function Config Pointer
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_EMBConfig(M4_TMR6_TypeDef *TMR6x,
                           uint32_t u32PortSel,
                           const stc_tmr6_emb_cfg_t* pstcTmr6EmbCfg)
{
    __IO uint32_t *PCNXR;
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcTmr6EmbCfg)
    {
        DDL_ASSERT(IS_VALID_OUTPUT_PORT(u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_CH(pstcTmr6EmbCfg->u32ValidCh));
        DDL_ASSERT(IS_VALID_EMB_RELEASE_MODE(pstcTmr6EmbCfg->u32ReleaseMode));
        DDL_ASSERT(IS_VALID_EMB_VALID_PORT_STA(pstcTmr6EmbCfg->u32PortSta));

        if(TMR6_IO_PWMA == u32PortSel)
        {
            PCNXR = (__IO uint32_t*)&TMR6x->PCNAR;
        }
        else
        {
            PCNXR = (__IO uint32_t*)&TMR6x->PCNBR;
        }

        MODIFY_REG32(*PCNXR,
                      PCNA_BR_REG_EMB_CFG_MASK,
                      pstcTmr6EmbCfg->u32ValidCh
                      | pstcTmr6EmbCfg->u32ReleaseMode
                      | pstcTmr6EmbCfg->u32PortSta );

        enRet = Ok;
    }
    return enRet;

}

/**
 * @brief  Timer6 dead time function command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] enNewState  Disable or Enable the function
 * @retval None
 */
void TMR6_DeadTimeFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->DCONR, TMR6_DCONR_DTCEN);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->DCONR, TMR6_DCONR_DTCEN);
    }
}

/**
 * @brief  DeadTime function configuration
 * @param  [in]  TMR6x              Timer6 unit
 * @param  [in]  pstcTmr6DTCfg      Timer6 dead time config pointer
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_DeadTimeCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_deadtime_cfg_t* pstcTmr6DTCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    if (NULL != pstcTmr6DTCfg)
    {
        DDL_ASSERT(IS_VALID_DEADTIME_EQUAL_FUNC_REG(pstcTmr6DTCfg->u32DtEqualUpDwn));
        DDL_ASSERT(IS_VALID_DEADTIME_BUF_FUNC_DTUAR_REG(pstcTmr6DTCfg->u32EnDtBufUp));
        DDL_ASSERT(IS_VALID_DEADTIME_BUF_FUNC_DTDAR_REG(pstcTmr6DTCfg->u32EnDtBufDwn));
        DDL_ASSERT(IS_VALID_DEADTIME_BUF_TRANS_COND_REG(pstcTmr6DTCfg->u32DtUpdCond));

        WRITE_REG32(TMR6x->DCONR, pstcTmr6DTCfg->u32DtEqualUpDwn
                                    | pstcTmr6DTCfg->u32EnDtBufUp
                                    | pstcTmr6DTCfg->u32EnDtBufDwn
                                    | pstcTmr6DTCfg->u32DtUpdCond);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Software Sync Start
 * @param  [in]  u32UnitCombine  Software Sync units, This parameter can
 *                               be one or any combination of the parameter
 *                               @ref TMR6_Soft_Sync_Ctrl_Unit_Number_define
 * @retval None
 */
void TMR6_SwSyncStart(uint32_t u32UnitCombine)
{
    DDL_ASSERT(IS_VALID_SW_CTRL_CFG(u32UnitCombine));
    WRITE_REG32(M4_TMR6_1->SSTAR, u32UnitCombine);
}

/**
 * @brief  Software Sync Stop
 * @param  [in]  u32UnitCombine  Software Sync units, This parameter can
 *                               be one or any combination of the parameter
 *                               @ref TMR6_Soft_Sync_Ctrl_Unit_Number_define
 * @retval None
 */
void TMR6_SwSyncStop(uint32_t u32UnitCombine)
{
    DDL_ASSERT(IS_VALID_SW_CTRL_CFG(u32UnitCombine));
    WRITE_REG32(M4_TMR6_1->SSTPR, u32UnitCombine);
}

/**
 * @brief  Software Sync clear
 * @param  [in]  u32UnitCombine  Software Sync units, This parameter can
 *                               be one or any combination of the parameter
 *                               @ref TMR6_Soft_Sync_Ctrl_Unit_Number_define
 * @retval None
 */
void TMR6_SwSyncClr(uint32_t u32UnitCombine)
{
    DDL_ASSERT(IS_VALID_SW_CTRL_CFG(u32UnitCombine));
    WRITE_REG32(M4_TMR6_1->SCLRR, u32UnitCombine);
}

/**
 * @brief  Software Sync update
 * @param  [in]  u32UnitCombine  Software Sync units, This parameter can
 *                               be one or any combination of the parameter
 *                               @ref TMR6_Soft_Sync_Ctrl_Unit_Number_define
 * @retval None
 */
void TMR6_SwSyncUpdate(uint32_t u32UnitCombine)
{
    DDL_ASSERT(IS_VALID_SW_CTRL_CFG(u32UnitCombine));
    WRITE_REG32(M4_TMR6_1->SUPDR, u32UnitCombine);
}

/**
 * @brief  Hardware start function command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] enNewState  Disable or Enable the function
 * @retval None
 */
void TMR6_HwStartFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HSTAR, TMR6_HSTAR_STAS, (uint32_t)enNewState << TMR6_HSTAR_STAS_POS);
}

/**
 * @brief  Hardware stop function command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] enNewState  Disable or Enable the function
 * @retval None
 */
void TMR6_HwStopFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HSTPR, TMR6_HSTPR_STPS, (uint32_t)enNewState << TMR6_HSTPR_STPS_POS);
}

/**
 * @brief  Hardware clear function command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] enNewState  Disable or Enable the function
 * @retval None
 */
void TMR6_HwClrFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HCLRR, TMR6_HCLRR_CLES, (uint32_t)enNewState << TMR6_HCLRR_CLES_POS);
}

/**
 * @brief  Hardware update function command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] enNewState  Disable or Enable the function
 *
 * @retval None
 */
void TMR6_HwUpdateFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(TMR6x->HUPDR, TMR6_HUPDR_UPDS, (uint32_t)enNewState << TMR6_HUPDR_UPDS_POS);
}

/**
 * @brief  Hardware start condtion command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware start, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_control_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwStartCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CTRL_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HSTAR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HSTAR, u32CondSrc);
    }
}

/**
 * @brief  Hardware start condition clear
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwStartCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HSTAR, 0UL);
}

/**
 * @brief  Hardware stop condtion command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware stop, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_control_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwStopCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CTRL_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HSTPR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HSTPR, u32CondSrc);
    }
}

/**
 * @brief  Hardware stop condtion clear
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwStopCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HSTPR, 0UL);
}

/**
 * @brief  Hardware clear condtion command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware clear, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_control_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwClrCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CTRL_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HCLRR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HCLRR, u32CondSrc);
    }
}

/**
 * @brief  Hardware clear condtion clear
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwClrCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HCLRR, 0UL);
}

/**
 * @brief  Hardware update condtion command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware update, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_control_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwUpdCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CTRL_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HUPDR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HUPDR, u32CondSrc);
    }
}

/**
 * @brief  Hardware update conditon clear
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwUpdCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HUPDR, 0UL);
}

/**
 * @brief  Hardware capture condtion command for channel A
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware capture, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_control_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwCaptureChACondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CTRL_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HCPAR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HCPAR, u32CondSrc);
    }
}

/**
 * @brief  Hardware capture condition clear for channel A
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwCaptureChACondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HCPAR, 0UL);
}

/**
 * @brief  Hardware capture condtion command for channel B
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware capture, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_control_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwCaptureChBCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CTRL_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HCPBR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HCPBR, u32CondSrc);
    }
}

/**
 * @brief  Hardware capture condition clear for channel B
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwCaptureChBCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HCPBR, 0UL);
}

/**
 * @brief  Hardware increase conditon command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware count, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_count_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwIncreaseCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CNT_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HCUPR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HCUPR, u32CondSrc);
    }
}

/**
 * @brief  Hardware increase condition clear
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3s
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwIncreaseCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HCUPR, 0UL);
}

/**
 * @brief  Hardware decrease condition command
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @param  [in] u32CondSrc  Events source for hardware count, maybe one or any combination of the parameter
 *                          @ref TMR6_hardware_count_event_define
 * @param  [in] enNewState  The function new state
 *  @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void TMR6_HwDecreaseCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));
    DDL_ASSERT(IS_VALID_HW_CNT_EVENTS(u32CondSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(TMR6x->HCDOR, u32CondSrc);
    }
    else
    {
        CLEAR_REG32_BIT(TMR6x->HCDOR, u32CondSrc);
    }
}

/**
 * @brief  Hardware decrease condtion clear
 * @param  [in] TMR6x       Timer6 unit
 *  @arg M4_TMR6_1
 *  @arg M4_TMR6_2
 *  @arg M4_TMR6_3
 *  @arg M4_TMR6_4
 *  @arg M4_TMR6_5
 *  @arg M4_TMR6_6
 *  @arg M4_TMR6_7
 *  @arg M4_TMR6_8
 * @retval None
 */
void TMR6_HwDecreaseCondClr(M4_TMR6_TypeDef *TMR6x)
{
    DDL_ASSERT(IS_VALID_TMR6_UNIT(TMR6x));

    WRITE_REG32(TMR6x->HCDOR, 0UL);
}

/**
 * @brief  Timer6 Hardware trigger event configuration for(trigger0~trigger3)
 * @param  [in] u32TrigIndex    Timer6 Hardware trigger index
 *                              @ref TMR6_Hardware_Trigger_Index_define
 * @param  [in] enEvent         Event configuration for timer6 hardware trigger
 * @retval None
 */
void TMR6_SetTriggerSrc(uint32_t u32TrigIndex, en_event_src_t enEvent)
{
    DDL_ASSERT(IS_VALID_HW_TRIGGER_INDEX(u32TrigIndex));

    __IO uint32_t *TMR6_HTSSRx = (__IO uint32_t *)((uint32_t)&M4_AOS->TMR6_HTSSR1 +  4UL * u32TrigIndex);
    MODIFY_REG32(*TMR6_HTSSRx, AOS_TMR6_HTSSR_TRGSEL, enEvent);
}

/**
 * @brief  Timer6 Hardware trigger common event function command for(trigger0~trigger3)
 * @param  [in] u32TrigIndex        Timer6 Hardware trigger index
 *                                  @ref TMR6_Hardware_Trigger_Index_define
 * @param  [in] u32ComTrig          Common trigger event enable.
 *                                  This parameter can be one of the following values:
 *   @arg  TMR6_COM_TRIG1: Common trigger event 1.
 *   @arg  TMR6_COM_TRIG2: Common trigger event 2.
 * @param  [in] enNewState          New state of common trigger function.
 * @retval none
 */
void TMR6_ComTriggerCmd(uint32_t u32TrigIndex, uint32_t u32ComTrig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_HW_TRIGGER_INDEX(u32TrigIndex));
    DDL_ASSERT(IS_VALID_TMR6_COM_TRIG(u32ComTrig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    __IO uint32_t *TMR6_HTSSRx = (__IO uint32_t *)((uint32_t)&M4_AOS->TMR6_HTSSR1 +  4UL * u32TrigIndex);

    if (Enable == enNewState)
    {
        SET_REG32_BIT(*TMR6_HTSSRx, u32ComTrig);
    }
    else
    {
        CLEAR_REG32_BIT(*TMR6_HTSSRx, u32ComTrig);
    }
}

/**
 * @brief  Set the fields of structure stc_tmr6_basecnt_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_basecnt_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_BaseCntStructInit(stc_tmr6_basecnt_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32CntMode = TMR6_MODE_SAWTOOTH;
        pstcInit->u32CntDir = TMR6_CNT_INCREASE;
        pstcInit->u32CntClkDiv = TMR6_CLK_PCLK0_DIV1;
        pstcInit->u32CntStpAftOvf = TMR6_CNT_CONTINUOUS;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_buf_func_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_buf_func_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_BufFuncStructInit(stc_tmr6_buf_func_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32BufFunCmd = TMR6_BUF_FUNC_OFF;
        pstcInit->u32BufNum = TMR6_BUF_FUNC_SINGLE;
        pstcInit->u32BufTransTim = TMR6_BUF_TRANS_TIM_NONE;

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_valid_period_func_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_valid_period_func_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_ValidPeriodStructInit(stc_tmr6_valid_period_func_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32StatChA = TMR6_VALID_PERIOD_FUNC_CHA_OFF;
        pstcInit->u32StatChB = TMR6_VALID_PERIOD_FUNC_CHB_OFF;
        pstcInit->u32CntCond = TMR6_VALID_PERIOD_FUNC_OFF;
        pstcInit->u32PeriodInterval = TMR6_VALID_PERIOD_CNT_INVALID;

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_port_input_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_port_input_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_PortInputStructInit(stc_tmr6_port_input_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32PortMode = TMR6_PORT_CAPTURE_INPUT;
        pstcInit->u32FilterSta = TMR6_PORT_INPUT_FILTER_OFF;
        pstcInit->u32FltClk = TMR6_INPUT_FILTER_PCLK0_DIV1;

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_port_output_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_port_output_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_PortOutputStructInit(stc_tmr6_port_output_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32PortMode = TMR6_PORT_COMPARE_OUTPUT;
        pstcInit->u32NextPeriodForceSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32DownCntMatchAnotherCmpRegSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32UpCntMatchAnotherCmpRegSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32DownCntMatchCmpRegSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32UpCntMatchCmpRegSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32UnderflowSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32OverflowSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32StopSta = TMR6_PORT_OUTPUT_STA_LOW;
        pstcInit->u32StartSta = TMR6_PORT_OUTPUT_STA_LOW;

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_emb_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_emb_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_EMBCfgStructInit(stc_tmr6_emb_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32ValidCh = TMR6_EMB_EVENT_VALID_CH0;
        pstcInit->u32ReleaseMode = TMR6_EMB_RELEASE_IMMEDIATE;
        pstcInit->u32PortSta = TMR6_EMB_PORTSTA_NORMAL;

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_deadtime_cfg_t to default values
 * @param  [out] pstcInit           Pointer to a @ref stc_tmr6_deadtime_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                        Successfully done
 *  @arg ErrorInvalidParameter:     Parameter error
 */
en_result_t TMR6_DeadTimeCfgStructInit(stc_tmr6_deadtime_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32DtEqualUpDwn = TMR6_DEADTIME_EQUAL_OFF;
        pstcInit->u32EnDtBufUp = TMR6_DEADTIME_CNT_UP_BUF_OFF;
        pstcInit->u32EnDtBufDwn = TMR6_DEADTIME_CNT_DOWN_BUF_OFF;

        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmr6_zmask_cfg_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_tmr6_zmask_cfg_t structure
 * @retval An en_result_t enumeration value.
 *  @arg Ok:                            Successfully done
 *  @arg ErrorInvalidParameter:         Parameter error
 */
en_result_t TMR6_ZMaskCfgStructInit(stc_tmr6_zmask_cfg_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32ZMaskCycle = TMR6_ZMASK_CYCLE_FUNC_INVALID;
        pstcInit->u32PosCntMaskEn = TMR6_POS_CLR_ZMASK_FUNC_INVALID;
        pstcInit->u32RevCntMaskEn = TMR6_REVO_CNT_ZMASK_FUNC_INVALID;

        enRet = Ok;
    }
    return enRet;
}
/**
 * @}
 */

#endif /* DDL_TMR6_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
