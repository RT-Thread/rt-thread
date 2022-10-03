/**************************************************************************//**
 * @file     nu_timer_pwm.h
 * @brief    Timer PWM Controller(Timer PWM) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_TIMER_PWM_H__
#define __NU_TIMER_PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif



/** @addtogroup Standard_Driver Standard Driver
  @{
*/
/** @addtogroup TIMER_PWM_Driver TIMER PWM Driver
  @{
*/

/** @addtogroup TIMER_PWM_EXPORTED_CONSTANTS TIMER PWM Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  Output Channel Constant Definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_CH0                                (BIT0)       /*!< Indicate PWMx_CH0 \hideinitializer */
#define TPWM_CH1                                (BIT1)       /*!< Indicate PWMx_CH1 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Counter Type Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_UP_COUNT                           (0UL << TIMER_PWMCTL_CNTTYPE_Pos)       /*!< Up count type \hideinitializer */
#define TPWM_DOWN_COUNT                         (1UL << TIMER_PWMCTL_CNTTYPE_Pos)       /*!< Down count type \hideinitializer */
#define TPWM_UP_DOWN_COUNT                      (2UL << TIMER_PWMCTL_CNTTYPE_Pos)       /*!< Up-Down count type \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Counter Mode Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_AUTO_RELOAD_MODE                   (0UL)                            /*!< Auto-reload mode \hideinitializer */
#define TPWM_ONE_SHOT_MODE                      (TIMER_PWMCTL_CNTMODE_Msk)       /*!< One-shot mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Output Level Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_OUTPUT_TOGGLE                      (0UL)      /*!< Timer PWM output toggle \hideinitializer */
#define TPWM_OUTPUT_NOTHING                     (1UL)      /*!< Timer PWM output nothing \hideinitializer */
#define TPWM_OUTPUT_LOW                         (2UL)      /*!< Timer PWM output low \hideinitializer */
#define TPWM_OUTPUT_HIGH                        (3UL)      /*!< Timer PWM output high \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Trigger ADC Source Select Constant Definitions                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_TRIGGER_ADC_AT_ZERO_POINT                      (0UL << TIMER_PWMEADCTS_TRGSEL_Pos)     /*!< Timer PWM trigger ADC while counter zero point event occurred \hideinitializer */
#define TPWM_TRIGGER_ADC_AT_PERIOD_POINT                    (1UL << TIMER_PWMEADCTS_TRGSEL_Pos)     /*!< Timer PWM trigger ADC while counter period point event occurred \hideinitializer */
#define TPWM_TRIGGER_ADC_AT_ZERO_OR_PERIOD_POINT            (2UL << TIMER_PWMEADCTS_TRGSEL_Pos)     /*!< Timer PWM trigger ADC while counter zero or period point event occurred \hideinitializer */
#define TPWM_TRIGGER_ADC_AT_COMPARE_UP_COUNT_POINT          (3UL << TIMER_PWMEADCTS_TRGSEL_Pos)     /*!< Timer PWM trigger ADC while counter up count compare point event occurred \hideinitializer */
#define TPWM_TRIGGER_ADC_AT_COMPARE_DOWN_COUNT_POINT        (4UL << TIMER_PWMEADCTS_TRGSEL_Pos)     /*!< Timer PWM trigger ADC while counter down count compare point event occurred \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Brake Control Constant Definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_BRAKE_SOURCE_EDGE_ACMP0            (TIMER_PWMBRKCTL_CPO0EBEN_Msk) /*!< Comparator 0 as edge-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_EDGE_ACMP1            (TIMER_PWMBRKCTL_CPO1EBEN_Msk) /*!< Comparator 1 as edge-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_EDGE_BKPIN            (TIMER_PWMBRKCTL_BRKPEEN_Msk)  /*!< Brake pin as edge-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_EDGE_SYS_CSS          (TIMER_PWMBRKCTL_SYSEBEN_Msk | (TIMER_PWMFAILBRK_CSSBRKEN_Msk << 16))    /*!< System fail condition: clock security system detection as edge-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_EDGE_SYS_BOD          (TIMER_PWMBRKCTL_SYSEBEN_Msk | (TIMER_PWMFAILBRK_BODBRKEN_Msk << 16))    /*!< System fail condition: brown-out detection as edge-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_EDGE_SYS_COR          (TIMER_PWMBRKCTL_SYSEBEN_Msk | (TIMER_PWMFAILBRK_CORBRKEN_Msk << 16))    /*!< System fail condition: core lockup detection as edge-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_EDGE_SYS_RAM          (TIMER_PWMBRKCTL_SYSEBEN_Msk | (TIMER_PWMFAILBRK_RAMBRKEN_Msk << 16))    /*!< System fail condition: SRAM parity error detection as edge-detect fault brake source \hideinitializer */


#define TPWM_BRAKE_SOURCE_LEVEL_ACMP0           (TIMER_PWMBRKCTL_CPO0LBEN_Msk)  /*!< Comparator 0 as level-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_LEVEL_ACMP1           (TIMER_PWMBRKCTL_CPO1LBEN_Msk)  /*!< Comparator 1 as level-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_LEVEL_BKPIN           (TIMER_PWMBRKCTL_BRKPLEN_Msk)   /*!< Brake pin as level-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_LEVEL_SYS_CSS         (TIMER_PWMBRKCTL_SYSLBEN_Msk | (TIMER_PWMFAILBRK_CSSBRKEN_Msk << 16))    /*!< System fail condition: clock security system detection as level-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_LEVEL_SYS_BOD         (TIMER_PWMBRKCTL_SYSLBEN_Msk | (TIMER_PWMFAILBRK_BODBRKEN_Msk << 16))    /*!< System fail condition: brown-out detection as level-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_LEVEL_SYS_COR         (TIMER_PWMBRKCTL_SYSLBEN_Msk | (TIMER_PWMFAILBRK_CORBRKEN_Msk << 16))    /*!< System fail condition: core lockup detection as level-detect fault brake source \hideinitializer */
#define TPWM_BRAKE_SOURCE_LEVEL_SYS_RAM         (TIMER_PWMBRKCTL_SYSLBEN_Msk | (TIMER_PWMFAILBRK_RAMBRKEN_Msk << 16))    /*!< System fail condition: SRAM parity error detection as level-detect fault brake source \hideinitializer */

#define TPWM_BRAKE_EDGE                         (TIMER_PWMSWBRK_BRKETRG_Msk)    /*!< Edge-detect fault brake \hideinitializer */
#define TPWM_BRAKE_LEVEL                        (TIMER_PWMSWBRK_BRKLTRG_Msk)    /*!< Level-detect fault brake \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Load Mode Constant Definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_LOAD_MODE_PERIOD                   (0UL)                       /*!< Timer PWM period load mode \hideinitializer */
#define TPWM_LOAD_MODE_IMMEDIATE                (TIMER_PWMCTL_IMMLDEN_Msk)  /*!< Timer PWM immediately load mode \hideinitializer */
#define TPWM_LOAD_MODE_CENTER                   (TIMER_PWMCTL_CTRLD_Msk)    /*!< Timer PWM center load mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Brake Pin De-bounce Clock Source Select Constant Definitions                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_BKP_DBCLK_PCLK_DIV_1               (0UL)    /*!< De-bounce clock is PCLK divide by 1 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_2               (1UL)    /*!< De-bounce clock is PCLK divide by 2 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_4               (2UL)    /*!< De-bounce clock is PCLK divide by 4 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_8               (3UL)    /*!< De-bounce clock is PCLK divide by 8 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_16              (4UL)    /*!< De-bounce clock is PCLK divide by 16 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_32              (5UL)    /*!< De-bounce clock is PCLK divide by 32 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_64              (6UL)    /*!< De-bounce clock is PCLK divide by 64 \hideinitializer */
#define TPWM_BKP_DBCLK_PCLK_DIV_128             (7UL)    /*!< De-bounce clock is PCLK divide by 128 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Brake Pin Source Select Constant Definitions                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_TM_BRAKE0                          (0UL)    /*!< Brake pin source comes from TM_BRAKE0 \hideinitializer */
#define TPWM_TM_BRAKE1                          (1UL)    /*!< Brake pin source comes from TM_BRAKE1 \hideinitializer */
#define TPWM_TM_BRAKE2                          (2UL)    /*!< Brake pin source comes from TM_BRAKE2 \hideinitializer */
#define TPWM_TM_BRAKE3                          (3UL)    /*!< Brake pin source comes from TM_BRAKE3 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Counter Clock Source Select Constant Definitions                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_CNTR_CLKSRC_TMR_CLK             (0UL)    /*!< Timer PWM Clock source selects to TMR_CLK \hideinitializer */
#define TPWM_CNTR_CLKSRC_TIMER0_INT          (1UL)    /*!< Timer PWM Clock source selects to TIMER0 interrupt event \hideinitializer */
#define TPWM_CNTR_CLKSRC_TIMER1_INT          (2UL)    /*!< Timer PWM Clock source selects to TIMER1 interrupt event \hideinitializer */
#define TPWM_CNTR_CLKSRC_TIMER2_INT          (3UL)    /*!< Timer PWM Clock source selects to TIMER2 interrupt event \hideinitializer */
#define TPWM_CNTR_CLKSRC_TIMER3_INT          (4UL)    /*!< Timer PWM Clock source selects to TIMER3 interrupt event \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Counter Synchronous Mode Constant Definitions                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define TPWM_CNTR_SYNC_DISABLE               (0UL)    /*!< Disable TIMER PWM synchronous function \hideinitializer */
#define TPWM_CNTR_SYNC_START_BY_TIMER0       ((0<<TIMER_PWMSCTL_SYNCSRC_Pos) | (1<<TIMER_PWMSCTL_SYNCMODE_Pos))  /*!< PWM counter synchronous start by TIMER0 PWM \hideinitializer */
#define TPWM_CNTR_SYNC_CLEAR_BY_TIMER0       ((0<<TIMER_PWMSCTL_SYNCSRC_Pos) | (3<<TIMER_PWMSCTL_SYNCMODE_Pos))  /*!< PWM counter synchronous clear by TIMER0 PWM \hideinitializer */
#define TPWM_CNTR_SYNC_START_BY_TIMER2       ((1<<TIMER_PWMSCTL_SYNCSRC_Pos) | (1<<TIMER_PWMSCTL_SYNCMODE_Pos))  /*!< PWM counter synchronous start by TIMER2 PWM \hideinitializer */
#define TPWM_CNTR_SYNC_CLEAR_BY_TIMER2       ((1<<TIMER_PWMSCTL_SYNCSRC_Pos) | (3<<TIMER_PWMSCTL_SYNCMODE_Pos))  /*!< PWM counter synchronous clear by TIMER2 PWM \hideinitializer */

/*@}*/ /* end of group TIMER_PWM_EXPORTED_CONSTANTS */


/** @addtogroup TIMER_PWM_EXPORTED_FUNCTIONS TIMER PWM Exported Functions
  @{
*/

/**
  * @brief      Enable PWM Counter Mode
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable specified Timer channel as PWM counter mode, then timer counter mode is invalid.
  * @note       All registers about time counter function will be cleared to 0 and timer clock source will be changed to PCLKx automatically after executing this macro.
  * \hideinitializer
  */
#define TPWM_ENABLE_PWM_MODE(timer)         ((timer)->ALTCTL = (1 << TIMER_ALTCTL_FUNCSEL_Pos))

/**
  * @brief      Disable PWM Counter Mode
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to disable specified Timer channel as PWM counter mode, then timer counter mode is available.
  * @note       All registers about PWM counter function will be cleared to 0 after executing this macro.
  * \hideinitializer
  */
#define TPWM_DISABLE_PWM_MODE(timer)        ((timer)->ALTCTL = (0 << TIMER_ALTCTL_FUNCSEL_Pos))

/**
  * @brief      Enable Independent Mode
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable independent mode of TIMER PWM module and complementary mode will be disabled.
  * \hideinitializer
  */
#define TPWM_ENABLE_INDEPENDENT_MODE(timer)     ((timer)->PWMCTL &= ~(1 << TIMER_PWMCTL_OUTMODE_Pos))

/**
  * @brief      Enable Complementary Mode
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable complementary mode of Timer PWM module and independent mode will be disabled.
  * \hideinitializer
  */
#define TPWM_ENABLE_COMPLEMENTARY_MODE(timer)   ((timer)->PWMCTL |= (1 << TIMER_PWMCTL_OUTMODE_Pos))

/**
  * @brief      Set Counter Type
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  type        Timer PWM count type, could be one of the following type
  *                             - \ref TPWM_UP_COUNT
  *                             - \ref TPWM_DOWN_COUNT
  *                             - \ref TPWM_UP_DOWN_COUNT
  *
  * @return     None
  *
  * @details    This macro is used to set Timer PWM counter type.
  * \hideinitializer
  */
#define TPWM_SET_COUNTER_TYPE(timer, type)      ((timer)->PWMCTL = ((timer)->PWMCTL & ~TIMER_PWMCTL_CNTTYPE_Msk) | (type))

/**
  * @brief      Start PWM Counter
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable PWM generator and start counter counting.
  * \hideinitializer
  */
#define TPWM_START_COUNTER(timer)               ((timer)->PWMCTL |= TIMER_PWMCTL_CNTEN_Msk)

/**
  * @brief      Stop PWM Counter
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to stop PWM counter after current period is completed.
  * \hideinitializer
  */
#define TPWM_STOP_COUNTER(timer)                ((timer)->PWMPERIOD = 0x0)

/**
  * @brief      Set Counter Clock Prescaler
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  prescaler    Clock prescaler of specified channel. Valid values are between 0x0~0xFFF.
  *
  * @return     None
  *
  * @details    This macro is used to set the prescaler of specified TIMER PWM.
  * @note       If prescaler is 0, then there is no scaling in counter clock source.
  * \hideinitializer
  */
#define TPWM_SET_PRESCALER(timer, prescaler) ((timer)->PWMCLKPSC = (prescaler))

/**
  * @brief      Get Counter Clock Prescaler
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     Target prescaler setting, CLKPSC (TIMERx_PWMCLKPSC[11:0])
  *
  * @details    Get the prescaler setting, the target counter clock divider is (CLKPSC + 1).
  * \hideinitializer
  */
#define TPWM_GET_PRESCALER(timer)       ((timer)->PWMCLKPSC)

/**
  * @brief      Set Counter Period
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  period      Period of specified channel. Valid values are between 0x0~0xFFFF.
  *
  * @return     None
  *
  * @details    This macro is used to set the period of specified TIMER PWM.
  * \hideinitializer
  */
#define TPWM_SET_PERIOD(timer, period)  ((timer)->PWMPERIOD = (period))

/**
  * @brief      Get Counter Period
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     Target period setting, PERIOD (TIMERx_PWMPERIOD[15:0])
  *
  * @details    This macro is used to get the period of specified TIMER PWM.
  * \hideinitializer
  */
#define TPWM_GET_PERIOD(timer)          ((timer)->PWMPERIOD)

/**
  * @brief      Set Comparator Value
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  cmp     Comparator of specified channel. Valid values are between 0x0~0xFFFF.
  *
  * @return     None
  *
  * @details    This macro is used to set the comparator value of specified TIMER PWM.
  * \hideinitializer
  */
#define TPWM_SET_CMPDAT(timer, cmp)     ((timer)->PWMCMPDAT = (cmp))

/**
  * @brief      Get Comparator Value
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     Target comparator setting, CMPDAT (TIMERx_PWMCMPDAT[15:0])
  *
  * @details    This macro is used to get the comparator value of specified TIMER PWM.
  * \hideinitializer
  */
#define TPWM_GET_CMPDAT(timer)          ((timer)->PWMCMPDAT)

/**
  * @brief      Clear Counter
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to clear counter of specified TIMER PWM.
  * \hideinitializer
  */
#define TPWM_CLEAR_COUNTER(timer)       ((timer)->PWMCNTCLR = TIMER_PWMCNTCLR_CNTCLR_Msk)

/**
  * @brief      Software Trigger Brake Event
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  type        Type of brake trigger. Valid values are:
  *                             - \ref TPWM_BRAKE_EDGE
  *                             - \ref TPWM_BRAKE_LEVEL
  *
  * @return     None
  *
  * @details    This macro is used to trigger brake event by writing PWMSWBRK register.
  * \hideinitializer
  */
#define TPWM_SW_TRIGGER_BRAKE(timer, type)  ((timer)->PWMSWBRK = (type))

/**
  * @brief      Enable Output Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  ch          Enable specified channel output function. Valid values are the combination of:
  *                             - \ref TPWM_CH0
  *                             - \ref TPWM_CH1
  *
  * @return     None
  *
  * @details    This macro is used to enable output function of specified output pins.
  * @note       If the corresponding bit in ch parameter is 0, then output function will be disabled in this channel.
  * \hideinitializer
  */
#define TPWM_ENABLE_OUTPUT(timer, ch)  ((timer)->PWMPOEN = (ch))

/**
  * @brief      Set Output Inverse
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  ch          Set specified channel output is inversed or not. Valid values are the combination of:
  *                             - \ref TPWM_CH0
  *                             - \ref TPWM_CH1
  *
  * @return     None
  *
  * @details    This macro is used to enable output inverse of specified output pins.
  * @note       If ch parameter is 0, then output inverse function will be disabled.
  * \hideinitializer
  */
#define TPWM_SET_OUTPUT_INVERSE(timer, ch)  ((timer)->PWMPOLCTL = (ch))

/**
  * @brief      Enable Output Function
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  ch       Enable specified channel output mask function. Valid values are the combination of:
  *                             - \ref TPWM_CH0
  *                             - \ref TPWM_CH1
  *
  * @param[in]  level    Output to high or low on specified mask channel.
  *
  * @return     None
  *
  * @details    This macro is used to enable output function of specified output pins.
  * @note       If ch parameter is 0, then output mask function will be disabled.
  * \hideinitializer
  */
#define TPWM_SET_MASK_OUTPUT(timer, ch, level) do {(timer)->PWMMSKEN = (ch); (timer)->PWMMSK = (level); }while(0)

/**
  * @brief      Set Counter Synchronous Mode
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @param[in]  mode    Synchronous mode. Possible options are:
  *                         - \ref TPWM_CNTR_SYNC_DISABLE
  *                         - \ref TPWM_CNTR_SYNC_START_BY_TIMER0
  *                         - \ref TPWM_CNTR_SYNC_CLEAR_BY_TIMER0
  *                         - \ref TPWM_CNTR_SYNC_START_BY_TIMER2
  *                         - \ref TPWM_CNTR_SYNC_CLEAR_BY_TIMER2
  *
  * @return     None
  *
  * @details    This macro is used to set counter synchronous mode of specified Timer PWM module.
  * @note       Only support all PWM counters are synchronous by TIMER0 PWM or TIMER0~1 PWM counter synchronous by TIMER0 PWM and
  *             TIMER2~3 PWM counter synchronous by TIMER2 PWM.
  * \hideinitializer
  */
#define TPWM_SET_COUNTER_SYNC_MODE(timer, mode) ((timer)->PWMSCTL = (mode))

/**
  * @brief      Trigger Counter Synchronous
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to trigger synchronous event by specified TIMER PWM.
  * @note       1. This macro is only available for TIMER0 PWM and TIMER2 PWM. \n
  *             2. STRGEN (PWMSTRG[0]) is write only and always read as 0.
  * \hideinitializer
  */
#define TPWM_TRIGGER_COUNTER_SYNC(timer)    ((timer)->PWMSTRG = TIMER_PWMSTRG_STRGEN_Msk)

/**
  * @brief      Enable Zero Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable the zero event interrupt function.
  * \hideinitializer
  */
#define TPWM_ENABLE_ZERO_INT(timer)         ((timer)->PWMINTEN0 |= TIMER_PWMINTEN0_ZIEN_Msk)

/**
  * @brief      Disable Zero Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to disable the zero event interrupt function.
  * \hideinitializer
  */
#define TPWM_DISABLE_ZERO_INT(timer)        ((timer)->PWMINTEN0 &= ~TIMER_PWMINTEN0_ZIEN_Msk)

/**
  * @brief      Get Zero Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Zero event interrupt did not occur
  * @retval     1   Zero event interrupt occurred
  *
  * @details    This macro indicates zero event occurred or not.
  * \hideinitializer
  */
#define TPWM_GET_ZERO_INT_FLAG(timer)       (((timer)->PWMINTSTS0 & TIMER_PWMINTSTS0_ZIF_Msk)? 1 : 0)

/**
  * @brief      Clear Zero Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro clears zero event interrupt flag.
  * \hideinitializer
  */
#define TPWM_CLEAR_ZERO_INT_FLAG(timer)     ((timer)->PWMINTSTS0 = TIMER_PWMINTSTS0_ZIF_Msk)

/**
  * @brief      Enable Period Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable the period event interrupt function.
  * \hideinitializer
  */
#define TPWM_ENABLE_PERIOD_INT(timer)       ((timer)->PWMINTEN0 |= TIMER_PWMINTEN0_PIEN_Msk)

/**
  * @brief      Disable Period Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to disable the period event interrupt function.
  * \hideinitializer
  */
#define TPWM_DISABLE_PERIOD_INT(timer)      ((timer)->PWMINTEN0 &= ~TIMER_PWMINTEN0_PIEN_Msk)

/**
  * @brief      Get Period Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Period event interrupt did not occur
  * @retval     1   Period event interrupt occurred
  *
  * @details    This macro indicates period event occurred or not.
  * \hideinitializer
  */
#define TPWM_GET_PERIOD_INT_FLAG(timer)     (((timer)->PWMINTSTS0 & TIMER_PWMINTSTS0_PIF_Msk)? 1 : 0)

/**
  * @brief      Clear Period Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro clears period event interrupt flag.
  * \hideinitializer
  */
#define TPWM_CLEAR_PERIOD_INT_FLAG(timer)   ((timer)->PWMINTSTS0 = TIMER_PWMINTSTS0_PIF_Msk)

/**
  * @brief      Enable Compare Up Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable the compare up event interrupt function.
  * \hideinitializer
  */
#define TPWM_ENABLE_CMP_UP_INT(timer)       ((timer)->PWMINTEN0 |= TIMER_PWMINTEN0_CMPUIEN_Msk)

/**
  * @brief      Disable Compare Up Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to disable the compare up event interrupt function.
  * \hideinitializer
  */
#define TPWM_DISABLE_CMP_UP_INT(timer)      ((timer)->PWMINTEN0 &= ~TIMER_PWMINTEN0_CMPUIEN_Msk)

/**
  * @brief      Get Compare Up Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Compare up event interrupt did not occur
  * @retval     1   Compare up event interrupt occurred
  *
  * @details    This macro indicates compare up event occurred or not.
  * \hideinitializer
  */
#define TPWM_GET_CMP_UP_INT_FLAG(timer)     (((timer)->PWMINTSTS0 & TIMER_PWMINTSTS0_CMPUIF_Msk)? 1 : 0)

/**
  * @brief      Clear Compare Up Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro clears compare up event interrupt flag.
  * \hideinitializer
  */
#define TPWM_CLEAR_CMP_UP_INT_FLAG(timer)   ((timer)->PWMINTSTS0 = TIMER_PWMINTSTS0_CMPUIF_Msk)

/**
  * @brief      Enable Compare Down Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to enable the compare down event interrupt function.
  * \hideinitializer
  */
#define TPWM_ENABLE_CMP_DOWN_INT(timer)     ((timer)->PWMINTEN0 |= TIMER_PWMINTEN0_CMPDIEN_Msk)

/**
  * @brief      Disable Compare Down Event Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to disable the compare down event interrupt function.
  * \hideinitializer
  */
#define TPWM_DISABLE_CMP_DOWN_INT(timer)    ((timer)->PWMINTEN0 &= ~TIMER_PWMINTEN0_CMPDIEN_Msk)

/**
  * @brief      Get Compare Down Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Compare down event interrupt did not occur
  * @retval     1   Compare down event interrupt occurred
  *
  * @details    This macro indicates compare down event occurred or not.
  * \hideinitializer
  */
#define TPWM_GET_CMP_DOWN_INT_FLAG(timer)   (((timer)->PWMINTSTS0 & TIMER_PWMINTSTS0_CMPDIF_Msk)? 1 : 0)

/**
  * @brief      Clear Compare Down Event Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro clears compare down event interrupt flag.
  * \hideinitializer
  */
#define TPWM_CLEAR_CMP_DOWN_INT_FLAG(timer) ((timer)->PWMINTSTS0 = TIMER_PWMINTSTS0_CMPDIF_Msk)

/**
  * @brief      Get Counter Reach Maximum Count Status
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Timer PWM counter never counts to maximum value
  * @retval     1   Timer PWM counter counts to maximum value, 0xFFFF
  *
  * @details    This macro indicates Timer PWM counter has count to 0xFFFF or not.
  * \hideinitializer
  */
#define TPWM_GET_REACH_MAX_CNT_STATUS(timer)    (((timer)->PWMSTATUS & TIMER_PWMSTATUS_CNTMAXF_Msk)? 1 : 0)

/**
  * @brief      Clear Counter Reach Maximum Count Status
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro clears reach maximum count status.
  * \hideinitializer
  */
#define TPWM_CLEAR_REACH_MAX_CNT_STATUS(timer)  ((timer)->PWMSTATUS = TIMER_PWMSTATUS_CNTMAXF_Msk)

/**
  * @brief      Get Trigger ADC Status
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0       Trigger ADC start conversion is not occur
  * @retval     1       Specified counter compare event has trigger ADC start conversion
  *
  * @details    This macro is used to indicate PWM counter compare event has triggered ADC start conversion.
  * \hideinitializer
  */
#define TPWM_GET_TRG_ADC_STATUS(timer)          (((timer)->PWMSTATUS & TIMER_PWMSTATUS_EADCTRGF_Msk)? 1 : 0)

/**
  * @brief      Clear Trigger ADC Status
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to clear PWM counter compare event trigger ADC status.
  * \hideinitializer
  */
#define TPWM_CLEAR_TRG_ADC_STATUS(timer)        ((timer)->PWMSTATUS = TIMER_PWMSTATUS_EADCTRGF_Msk)

/**
  * @brief      Set Brake Event at Brake Pin High or Low-to-High
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to set detect brake event when external brake pin at high level or transfer from low to high.
  * @note       The default brake pin detection is high level or from low to high.
  * \hideinitializer
  */
#define TPWM_SET_BRAKE_PIN_HIGH_DETECT(timer)   ((timer)->PWMBNF &= ~TIMER_PWMBNF_BRKPINV_Msk)

/**
  * @brief      Set Brake Event at Brake Pin Low or High-to-Low
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This macro is used to set detect brake event when external brake pin at low level or transfer from high to low.
  * \hideinitializer
  */
#define TPWM_SET_BRAKE_PIN_LOW_DETECT(timer)    ((timer)->PWMBNF |= TIMER_PWMBNF_BRKPINV_Msk)

/**
  * @brief      Set External Brake Pin Source
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  pin         The external brake pin source, could be one of following source
  *                                 - \ref TPWM_TM_BRAKE0
  *                                 - \ref TPWM_TM_BRAKE1
  *                                 - \ref TPWM_TM_BRAKE2
  *                                 - \ref TPWM_TM_BRAKE3
  *
  * @return     None
  *
  * @details    This macro is used to set detect brake event when external brake pin at high level or transfer from low to high.
  * \hideinitializer
  */
#define TPWM_SET_BRAKE_PIN_SOURCE(timer, pin)   ((timer)->PWMBNF = ((timer)->PWMBNF & ~TIMER_PWMBNF_BKPINSRC_Msk) | ((pin)<<TIMER_PWMBNF_BKPINSRC_Pos))


void TPWM_SetCounterClockSource(TIMER_T *timer, uint32_t u32CntClkSrc);
uint32_t TPWM_ConfigOutputFreqAndDuty(TIMER_T *timer, uint32_t u32Frequency, uint32_t u32DutyCycle);
void TPWM_EnableDeadTime(TIMER_T *timer, uint32_t u32DTCount);
void TPWM_EnableDeadTimeWithPrescale(TIMER_T *timer, uint32_t u32DTCount);
void TPWM_DisableDeadTime(TIMER_T *timer);
void TPWM_EnableCounter(TIMER_T *timer);
void TPWM_DisableCounter(TIMER_T *timer);
void TPWM_EnableTriggerADC(TIMER_T *timer, uint32_t u32Condition);
void TPWM_DisableTriggerADC(TIMER_T *timer);
void TPWM_EnableFaultBrake(TIMER_T *timer, uint32_t u32CH0Level, uint32_t u32CH1Level, uint32_t u32BrakeSource);
void TPWM_EnableFaultBrakeInt(TIMER_T *timer, uint32_t u32IntSource);
void TPWM_DisableFaultBrakeInt(TIMER_T *timer, uint32_t u32IntSource);
uint32_t TPWM_GetFaultBrakeIntFlag(TIMER_T *timer, uint32_t u32IntSource);
void TPWM_ClearFaultBrakeIntFlag(TIMER_T *timer, uint32_t u32IntSource);
void TPWM_SetLoadMode(TIMER_T *timer, uint32_t u32LoadMode);
void TPWM_EnableBrakePinDebounce(TIMER_T *timer, uint32_t u32BrakePinSrc, uint32_t u32DebounceCnt, uint32_t u32ClkSrcSel);
void TPWM_DisableBrakePinDebounce(TIMER_T *timer);
void TPWM_EnableBrakePinInverse(TIMER_T *timer);
void TPWM_DisableBrakePinInverse(TIMER_T *timer);
void TPWM_SetBrakePinSource(TIMER_T *timer, uint32_t u32BrakePinNum);

/*@}*/ /* end of group TIMER_PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TIMER_PWM_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_TIMER_PWM_H__ */

