/**************************************************************************//**
 * @file     nu_timer.h
 * @version  V0.10
 * $Revision: 6 $
 * $Date: 18/07/13 4:59p $
 * @brief    M031 Series Timer Controller (TIMER) Driver Header File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_TIMER_H__
#define __NU_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TIMER_Driver TIMER Driver
  @{
*/

/** @addtogroup TIMER_EXPORTED_CONSTANTS TIMER Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  TIMER Operation Mode, External Counter and Capture Mode Constant Definitions                           */
/*---------------------------------------------------------------------------------------------------------*/
#define TIMER_ONESHOT_MODE                      (0UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in one-shot mode              \hideinitializer */
#define TIMER_PERIODIC_MODE                     (1UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in periodic mode              \hideinitializer */
#define TIMER_TOGGLE_MODE                       (2UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in toggle-output mode         \hideinitializer */
#define TIMER_CONTINUOUS_MODE                   (3UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in continuous counting mode   \hideinitializer */

#define TIMER_TOUT_PIN_FROM_TX                  (0UL << TIMER_CTL_TGLPINSEL_Pos)   /*!< Timer toggle-output pin is from Tx pin      \hideinitializer */
#define TIMER_TOUT_PIN_FROM_TX_EXT              (1UL << TIMER_CTL_TGLPINSEL_Pos)   /*!< Timer toggle-output pin is from Tx_EXT pin  \hideinitializer */

#define TIMER_CAPTURE_FREE_COUNTING_MODE        (0UL << TIMER_EXTCTL_CAPFUNCS_Pos) /*!< Timer capture event to get timer counter value  \hideinitializer */
#define TIMER_CAPTURE_COUNTER_RESET_MODE        (1UL << TIMER_EXTCTL_CAPFUNCS_Pos) /*!< Timer capture event to reset timer counter      \hideinitializer */

#define TIMER_CAPTURE_FALLING_EDGE              (0UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Falling edge detection to trigger timer capture \hideinitializer */
#define TIMER_CAPTURE_RISING_EDGE               (1UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Rising edge detection to trigger timer capture  \hideinitializer */
#define TIMER_CAPTURE_FALLING_AND_RISING_EDGE   (2UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Both falling and rising edge detection to trigger timer capture     \hideinitializer */

#define TIMER_COUNTER_FALLING_EDGE              (0UL << TIMER_EXTCTL_CNTPHASE_Pos) /*!< Counter increase on falling edge detection  \hideinitializer */
#define TIMER_COUNTER_RISING_EDGE               (1UL << TIMER_EXTCTL_CNTPHASE_Pos) /*!< Counter increase on rising edge detection   \hideinitializer */

#define TIMER_TRGSRC_TIMEOUT_EVENT              (0UL << TIMER_CTL_TRGSSEL_Pos)     /*!< Trigger source from Timeout event   \hideinitializer */
#define TIMER_TRGSRC_CAPTURE_EVENT              (1UL << TIMER_CTL_TRGSSEL_Pos)     /*!< Trigger source from Capture event   \hideinitializer */

#define TIMER_CAPSRC_TX_EXT                     (0UL << TIMER_CTL_CAPSRC_Pos)      /*!< Capture source from Tx_EXT pin      \hideinitializer */
#define TIMER_CAPSRC_INTERNAL                   (1UL << TIMER_CTL_CAPSRC_Pos)      /*!< Capture source from Internal event such as LIRC or ACMP0/1  \hideinitializer */

#define TIMER_INTERCAPSEL_ACMP0                 (0UL << TIMER_EXTCTL_INTERCAPSEL_Pos)   /*!< Capture source from Internal event ACMP0   \hideinitializer */
#define TIMER_INTERCAPSEL_ACMP1                 (1UL << TIMER_EXTCTL_INTERCAPSEL_Pos)   /*!< Capture source from Internal event ACMP1   \hideinitializer */
#define TIMER_INTERCAPSEL_LIRC                  (5UL << TIMER_EXTCTL_INTERCAPSEL_Pos)   /*!< Capture source from Internal event LIRC    \hideinitializer */

#define TIMER_TRG_TO_PWM                        (TIMER_CTL_TRGPWM_Msk)             /*!< Timer trigger PWM   \hideinitializer */
#define TIMER_TRG_TO_ADC                        (TIMER_CTL_TRGADC_Msk)             /*!< Timer trigger ADC   \hideinitializer */
#define TIMER_TRG_TO_PDMA                       (TIMER_CTL_TRGPDMA_Msk)            /*!< Timer trigger PDMA  \hideinitializer */
#define TIMER_TRG_TO_BPWM                       (TIMER_CTL_TRGBPWM_Msk)            /*!< Timer trigger BPWM  \hideinitializer */

#define TIMER_CMP_MAX_VALUE                     (0xFFFFFFUL)                       /*!< Max Timer compare value \hideinitializer */

/*@}*/ /* end of group TIMER_EXPORTED_CONSTANTS */


/** @addtogroup TIMER_EXPORTED_FUNCTIONS TIMER Exported Functions
  @{
*/

/**
  * @brief      Set Timer Compared Value
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  * @param[in]  u32Value    Timer compare value. Valid values are between 2 to 0xFFFFFF.
  *
  * @return     None
  *
  * @details    This macro is used to set timer compared value to adjust timer time-out interval.
  * @note       1. Never write 0x0 or 0x1 in this field, or the core will run into unknown state.
  * @note       2. If update timer compared value in continuous counting mode, timer counter value will keep counting continuously.
  *                But if timer is operating at other modes, the timer up counter will restart counting and start from 0.
  *
  * \hideinitializer
  */
#define TIMER_SET_CMP_VALUE(timer, u32Value)        ((timer)->CMP = (u32Value))

/**
  * @brief      Set Timer Prescale Value
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  * @param[in]  u32Value    Timer prescale value. Valid values are between 0 to 0xFF.
  *
  * @return     None
  *
  * @details    This macro is used to set timer prescale value and timer source clock will be divided by (prescale + 1) \n
  *             before it is fed into timer.
  *
  * \hideinitializer
  */
#define TIMER_SET_PRESCALE_VALUE(timer, u32Value)   ((timer)->CTL = ((timer)->CTL & ~TIMER_CTL_PSC_Msk) | (u32Value))

/**
  * @brief      Check specify Timer Status
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @retval     0   Timer 24-bit up counter is inactive
  * @retval     1   Timer 24-bit up counter is active
  *
  * @details    This macro is used to check if specify Timer counter is inactive or active.
  *
  * \hideinitializer
  */
#define TIMER_IS_ACTIVE(timer)                      (((timer)->CTL & TIMER_CTL_ACTSTS_Msk)? 1 : 0)

/**
  * @brief      Select Toggle-output Pin
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  * @param[in]  u32ToutSel  Toggle-output pin selection, valid values are:
  *                         - \ref TIMER_TOUT_PIN_FROM_TX
  *                         - \ref TIMER_TOUT_PIN_FROM_TX_EXT
  *
  * @return     None
  *
  * @details    This macro is used to select timer toggle-output pin is output on Tx or Tx_EXT pin.
  *
  * \hideinitializer
  */
#define TIMER_SELECT_TOUT_PIN(timer, u32ToutSel)    ((timer)->CTL = ((timer)->CTL & ~TIMER_CTL_TGLPINSEL_Msk) | (u32ToutSel))

/**
  * @brief      Start Timer Counting
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to start Timer counting.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_Start(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_CNTEN_Msk;
}

/**
  * @brief      Stop Timer Counting
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to stop/suspend Timer counting.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_Stop(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_CNTEN_Msk;
}

/**
  * @brief      Enable Timer Interrupt Wake-up Function
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to enable the timer interrupt wake-up function and interrupt source could be time-out interrupt, \n
  *             counter event interrupt or capture trigger interrupt.
  * @note       To wake the system from Power-down mode, timer clock source must be ether LXT or LIRC.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_EnableWakeup(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_WKEN_Msk;
}

/**
  * @brief      Disable Timer Wake-up Function
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to disable the timer interrupt wake-up function.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_DisableWakeup(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_WKEN_Msk;
}

/**
  * @brief      Enable Capture Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to enable the detect de-bounce function of capture pin.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_EnableCaptureDebounce(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CAPDBEN_Msk;
}

/**
  * @brief      Disable Capture Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to disable the detect de-bounce function of capture pin.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_DisableCaptureDebounce(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CAPDBEN_Msk;
}

/**
  * @brief      Enable Counter Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to enable the detect de-bounce function of counter pin.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_EnableEventCounterDebounce(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CNTDBEN_Msk;
}

/**
  * @brief      Disable Counter Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to disable the detect de-bounce function of counter pin.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_DisableEventCounterDebounce(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CNTDBEN_Msk;
}

/**
  * @brief      Enable Timer Time-out Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to enable the timer time-out interrupt function.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_EnableInt(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_INTEN_Msk;
}

/**
  * @brief      Disable Timer Time-out Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to disable the timer time-out interrupt function.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_DisableInt(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_INTEN_Msk;
}

/**
  * @brief      Enable Capture Trigger Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to enable the timer capture trigger interrupt function.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_EnableCaptureInt(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CAPIEN_Msk;
}

/**
  * @brief      Disable Capture Trigger Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to disable the timer capture trigger interrupt function.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_DisableCaptureInt(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CAPIEN_Msk;
}

/**
  * @brief      Get Timer Time-out Interrupt Flag
  *
  * @param[in]  timer   The pointer of the specified Timer module.
  *
  * @retval     0   Timer time-out interrupt did not occur
  * @retval     1   Timer time-out interrupt occurred
  *
  * @details    This function indicates timer time-out interrupt occurred or not.
  *
  * \hideinitializer
  */
static __INLINE uint32_t TIMER_GetIntFlag(TIMER_T *timer)
{
    return ((timer->INTSTS & TIMER_INTSTS_TIF_Msk) ? 1 : 0);
}

/**
  * @brief      Clear Timer Time-out Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function clears timer time-out interrupt flag to 0.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_ClearIntFlag(TIMER_T *timer)
{
    timer->INTSTS = TIMER_INTSTS_TIF_Msk;
}

/**
  * @brief      Get Timer Capture Interrupt Flag
  *
  * @param[in]  timer   The pointer of the specified Timer module.
  *
  * @retval     0   Timer capture interrupt did not occur
  * @retval     1   Timer capture interrupt occurred
  *
  * @details    This function indicates timer capture trigger interrupt occurred or not.
  *
  * \hideinitializer
  */
static __INLINE uint32_t TIMER_GetCaptureIntFlag(TIMER_T *timer)
{
    return timer->EINTSTS;
}

/**
  * @brief      Clear Timer Capture Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function clears timer capture trigger interrupt flag to 0.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_ClearCaptureIntFlag(TIMER_T *timer)
{
    timer->EINTSTS = TIMER_EINTSTS_CAPIF_Msk;
}

/**
  * @brief      Get Timer Wake-up Flag
  *
  * @param[in]  timer   The pointer of the specified Timer module.
  *
  * @retval     0   Timer does not cause CPU wake-up
  * @retval     1   Timer interrupt event cause CPU wake-up
  *
  * @details    This function indicates timer interrupt event has waked up system or not.
  *
  * \hideinitializer
  */
static __INLINE uint32_t TIMER_GetWakeupFlag(TIMER_T *timer)
{
    return (timer->INTSTS & TIMER_INTSTS_TWKF_Msk ? 1 : 0);
}

/**
  * @brief      Clear Timer Wake-up Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function clears the timer wake-up system flag to 0.
  *
  * \hideinitializer
  */
static __INLINE void TIMER_ClearWakeupFlag(TIMER_T *timer)
{
    timer->INTSTS = TIMER_INTSTS_TWKF_Msk;
}

/**
  * @brief      Get Capture value
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     24-bit Capture Value
  *
  * @details    This function reports the current 24-bit timer capture value.
  *
  * \hideinitializer
  */
static __INLINE uint32_t TIMER_GetCaptureData(TIMER_T *timer)
{
    return timer->CAP;
}

/**
  * @brief      Get Counter value
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     24-bit Counter Value
  *
  * @details    This function reports the current 24-bit timer counter value.
  *
  * \hideinitializer
  */
static __INLINE uint32_t TIMER_GetCounter(TIMER_T *timer)
{
    return timer->CNT;
}

/**
  * @brief      Reset Counter
  *
  * @param[in]  timer       The pointer of the specified Timer module.
  *
  * @return     None
  *
  * @details    This function is used to reset current counter value and internal prescale counter value.
  */
__STATIC_INLINE void TIMER_ResetCounter(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_RSTCNT_Msk;
}

uint32_t TIMER_Open(TIMER_T *timer, uint32_t u32Mode, uint32_t u32Freq);
void TIMER_Close(TIMER_T *timer);
void TIMER_Delay(TIMER_T *timer, uint32_t u32Usec);
void TIMER_EnableCapture(TIMER_T *timer, uint32_t u32CapMode, uint32_t u32Edge);
void TIMER_DisableCapture(TIMER_T *timer);
void TIMER_EnableEventCounter(TIMER_T *timer, uint32_t u32Edge);
void TIMER_DisableEventCounter(TIMER_T *timer);
uint32_t TIMER_GetModuleClock(TIMER_T *timer);
void TIMER_EnableFreqCounter(TIMER_T *timer,
                             uint32_t u32DropCount,
                             uint32_t u32Timeout,
                             uint32_t u32EnableInt);
void TIMER_DisableFreqCounter(TIMER_T *timer);
void TIMER_SetTriggerSource(TIMER_T *timer, uint32_t u32Src);
void TIMER_SetTriggerTarget(TIMER_T *timer, uint32_t u32Mask);

/*@}*/ /* end of group TIMER_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TIMER_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_TIMER_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
