/**************************************************************************//**
 * @file     nu_timer.h
 * @brief    Timer Controller(Timer) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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
#define TIMER_ONESHOT_MODE                      (0UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in one-shot mode \hideinitializer */
#define TIMER_PERIODIC_MODE                     (1UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in periodic mode \hideinitializer */
#define TIMER_TOGGLE_MODE                       (2UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in toggle-output mode \hideinitializer */
#define TIMER_CONTINUOUS_MODE                   (3UL << TIMER_CTL_OPMODE_Pos)      /*!< Timer working in continuous counting mode \hideinitializer */
#define TIMER_TOUT_PIN_FROM_TMX                 (0UL << TIMER_CTL_TGLPINSEL_Pos)   /*!< Timer toggle-output pin is from TMx pin \hideinitializer */
#define TIMER_TOUT_PIN_FROM_TMX_EXT             (1UL << TIMER_CTL_TGLPINSEL_Pos)   /*!< Timer toggle-output pin is from TMx_EXT pin \hideinitializer */

#define TIMER_COUNTER_EVENT_FALLING             (0UL << TIMER_EXTCTL_CNTPHASE_Pos) /*!< Counter increase on falling edge detection \hideinitializer */
#define TIMER_COUNTER_EVENT_RISING              (1UL << TIMER_EXTCTL_CNTPHASE_Pos) /*!< Counter increase on rising edge detection \hideinitializer */
#define TIMER_CAPTURE_FREE_COUNTING_MODE        (0UL << TIMER_EXTCTL_CAPFUNCS_Pos) /*!< Timer capture event to get timer counter value \hideinitializer */
#define TIMER_CAPTURE_COUNTER_RESET_MODE        (1UL << TIMER_EXTCTL_CAPFUNCS_Pos) /*!< Timer capture event to reset timer counter \hideinitializer */

#define TIMER_CAPTURE_EVENT_FALLING             (0UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Falling edge detection to trigger capture event \hideinitializer */
#define TIMER_CAPTURE_EVENT_RISING              (1UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Rising edge detection to trigger capture event \hideinitializer */
#define TIMER_CAPTURE_EVENT_FALLING_RISING      (2UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Both falling and rising edge detection to trigger capture event, and first event at falling edge \hideinitializer */
#define TIMER_CAPTURE_EVENT_RISING_FALLING      (3UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< Both rising and falling edge detection to trigger capture event, and first event at rising edge \hideinitializer */
#define TIMER_CAPTURE_EVENT_GET_LOW_PERIOD      (6UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< First capture event is at falling edge, follows are at at rising edge \hideinitializer */
#define TIMER_CAPTURE_EVENT_GET_HIGH_PERIOD     (7UL << TIMER_EXTCTL_CAPEDGE_Pos)  /*!< First capture event is at rising edge, follows are at at falling edge \hideinitializer */

#define TIMER_TRGSRC_TIMEOUT_EVENT              (0UL << TIMER_TRGCTL_TRGSSEL_Pos) /*!< Select internal trigger source from timer time-out event \hideinitializer */
#define TIMER_TRGSRC_CAPTURE_EVENT              (1UL << TIMER_TRGCTL_TRGSSEL_Pos) /*!< Select internal trigger source from timer capture event \hideinitializer */
#define TIMER_TRG_TO_EPWM                       (TIMER_TRGCTL_TRGEPWM_Msk)        /*!< Each timer event as EPWM counter clock source \hideinitializer */
#define TIMER_TRG_TO_EADC                       (TIMER_TRGCTL_TRGEADC_Msk)        /*!< Each timer event to start ADC conversion \hideinitializer */
#define TIMER_TRG_TO_DAC                        (TIMER_TRGCTL_TRGDAC_Msk)         /*!< Each timer event to start DAC conversion \hideinitializer */
#define TIMER_TRG_TO_PDMA                       (TIMER_TRGCTL_TRGPDMA_Msk)        /*!< Each timer event to trigger PDMA transfer \hideinitializer */

/*@}*/ /* end of group TIMER_EXPORTED_CONSTANTS */


/** @addtogroup TIMER_EXPORTED_FUNCTIONS TIMER Exported Functions
  @{
*/

/**
  * @brief      Set Timer Compared Value
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Value    Timer compare value. Valid values are between 2 to 0xFFFFFF.
  *
  * @return     None
  *
  * @details    This macro is used to set timer compared value to adjust timer time-out interval.
  * @note       1. Never write 0x0 or 0x1 in this field, or the core will run into unknown state. \n
  *             2. If update timer compared value in continuous counting mode, timer counter value will keep counting continuously. \n
  *                But if timer is operating at other modes, the timer up counter will restart counting and start from 0.
  * \hideinitializer
  */
#define TIMER_SET_CMP_VALUE(timer, u32Value)        ((timer)->CMP = (u32Value))

/**
  * @brief      Set Timer Prescale Value
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Value    Timer prescale value. Valid values are between 0 to 0xFF.
  *
  * @return     None
  *
  * @details    This macro is used to set timer prescale value and timer source clock will be divided by (prescale + 1) \n
  *             before it is fed into timer.
  * \hideinitializer
  */
#define TIMER_SET_PRESCALE_VALUE(timer, u32Value)   ((timer)->CTL = ((timer)->CTL & ~TIMER_CTL_PSC_Msk) | (u32Value))

/**
  * @brief      Check specify Timer Status
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Timer 24-bit up counter is inactive
  * @retval     1   Timer 24-bit up counter is active
  *
  * @details    This macro is used to check if specify Timer counter is inactive or active.
  * \hideinitializer
  */
#define TIMER_IS_ACTIVE(timer)                      (((timer)->CTL & TIMER_CTL_ACTSTS_Msk)? 1 : 0)

/**
  * @brief      Select Toggle-output Pin
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32ToutSel  Toggle-output pin selection, valid values are:
  *                         - \ref TIMER_TOUT_PIN_FROM_TMX
  *                         - \ref TIMER_TOUT_PIN_FROM_TMX_EXT
  *
  * @return     None
  *
  * @details    This macro is used to select timer toggle-output pin is output on TMx or TMx_EXT pin.
  * \hideinitializer
  */
#define TIMER_SELECT_TOUT_PIN(timer, u32ToutSel)    ((timer)->CTL = ((timer)->CTL & ~TIMER_CTL_TGLPINSEL_Msk) | (u32ToutSel))

/**
  * @brief      Select Timer operating mode
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32OpMode   Operation mode. Possible options are
  *                         - \ref TIMER_ONESHOT_MODE
  *                         - \ref TIMER_PERIODIC_MODE
  *                         - \ref TIMER_TOGGLE_MODE
  *                         - \ref TIMER_CONTINUOUS_MODE
  *
  * @return     None
  * \hideinitializer
  */
#define TIMER_SET_OPMODE(timer, u32OpMode)   ((timer)->CTL = ((timer)->CTL & ~TIMER_CTL_OPMODE_Msk) | (u32OpMode))

/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void TIMER_Start(TIMER_T *timer);
__STATIC_INLINE void TIMER_Stop(TIMER_T *timer);
__STATIC_INLINE void TIMER_EnableWakeup(TIMER_T *timer);
__STATIC_INLINE void TIMER_DisableWakeup(TIMER_T *timer);
__STATIC_INLINE void TIMER_StartCapture(TIMER_T *timer);
__STATIC_INLINE void TIMER_StopCapture(TIMER_T *timer);
__STATIC_INLINE void TIMER_EnableCaptureDebounce(TIMER_T *timer);
__STATIC_INLINE void TIMER_DisableCaptureDebounce(TIMER_T *timer);
__STATIC_INLINE void TIMER_EnableEventCounterDebounce(TIMER_T *timer);
__STATIC_INLINE void TIMER_DisableEventCounterDebounce(TIMER_T *timer);
__STATIC_INLINE void TIMER_EnableInt(TIMER_T *timer);
__STATIC_INLINE void TIMER_DisableInt(TIMER_T *timer);
__STATIC_INLINE void TIMER_EnableCaptureInt(TIMER_T *timer);
__STATIC_INLINE void TIMER_DisableCaptureInt(TIMER_T *timer);
__STATIC_INLINE uint32_t TIMER_GetIntFlag(TIMER_T *timer);
__STATIC_INLINE void TIMER_ClearIntFlag(TIMER_T *timer);
__STATIC_INLINE uint32_t TIMER_GetCaptureIntFlag(TIMER_T *timer);
__STATIC_INLINE void TIMER_ClearCaptureIntFlag(TIMER_T *timer);
__STATIC_INLINE uint32_t TIMER_GetWakeupFlag(TIMER_T *timer);
__STATIC_INLINE void TIMER_ClearWakeupFlag(TIMER_T *timer);
__STATIC_INLINE uint32_t TIMER_GetCaptureData(TIMER_T *timer);
__STATIC_INLINE uint32_t TIMER_GetCounter(TIMER_T *timer);
__STATIC_INLINE void TIMER_ResetCounter(TIMER_T *timer);

/**
  * @brief      Start Timer Counting
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to start Timer counting.
  */
__STATIC_INLINE void TIMER_Start(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_CNTEN_Msk;
}

/**
  * @brief      Stop Timer Counting
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to stop/suspend Timer counting.
  */
__STATIC_INLINE void TIMER_Stop(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_CNTEN_Msk;
}

/**
  * @brief      Enable Timer Interrupt Wake-up Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to enable the timer interrupt wake-up function and interrupt source could be time-out interrupt, \n
  *             counter event interrupt or capture trigger interrupt.
  * @note       To wake the system from Power-down mode, timer clock source must be ether LXT or LIRC.
  */
__STATIC_INLINE void TIMER_EnableWakeup(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_WKEN_Msk;
}

/**
  * @brief      Disable Timer Wake-up Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to disable the timer interrupt wake-up function.
  */
__STATIC_INLINE void TIMER_DisableWakeup(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_WKEN_Msk;
}

/**
  * @brief      Start Timer Capture Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to start Timer capture function.
  */
__STATIC_INLINE void TIMER_StartCapture(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CAPEN_Msk;
}

/**
  * @brief      Stop Timer Capture Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to stop Timer capture function.
  */
__STATIC_INLINE void TIMER_StopCapture(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CAPEN_Msk;
}

/**
  * @brief      Enable Capture Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to enable the detect de-bounce function of capture pin.
  */
__STATIC_INLINE void TIMER_EnableCaptureDebounce(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CAPDBEN_Msk;
}

/**
  * @brief      Disable Capture Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to disable the detect de-bounce function of capture pin.
  */
__STATIC_INLINE void TIMER_DisableCaptureDebounce(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CAPDBEN_Msk;
}

/**
  * @brief      Enable Counter Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to enable the detect de-bounce function of counter pin.
  */
__STATIC_INLINE void TIMER_EnableEventCounterDebounce(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CNTDBEN_Msk;
}

/**
  * @brief      Disable Counter Pin De-bounce
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to disable the detect de-bounce function of counter pin.
  */
__STATIC_INLINE void TIMER_DisableEventCounterDebounce(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CNTDBEN_Msk;
}

/**
  * @brief      Enable Timer Time-out Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to enable the timer time-out interrupt function.
  */
__STATIC_INLINE void TIMER_EnableInt(TIMER_T *timer)
{
    timer->CTL |= TIMER_CTL_INTEN_Msk;
}

/**
  * @brief      Disable Timer Time-out Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to disable the timer time-out interrupt function.
  */
__STATIC_INLINE void TIMER_DisableInt(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_INTEN_Msk;
}

/**
  * @brief      Enable Capture Trigger Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to enable the timer capture trigger interrupt function.
  */
__STATIC_INLINE void TIMER_EnableCaptureInt(TIMER_T *timer)
{
    timer->EXTCTL |= TIMER_EXTCTL_CAPIEN_Msk;
}

/**
  * @brief      Disable Capture Trigger Interrupt
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to disable the timer capture trigger interrupt function.
  */
__STATIC_INLINE void TIMER_DisableCaptureInt(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CAPIEN_Msk;
}

/**
  * @brief      Get Timer Time-out Interrupt Flag
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Timer time-out interrupt did not occur
  * @retval     1   Timer time-out interrupt occurred
  *
  * @details    This function indicates timer time-out interrupt occurred or not.
  */
__STATIC_INLINE uint32_t TIMER_GetIntFlag(TIMER_T *timer)
{
    return ((timer->INTSTS & TIMER_INTSTS_TIF_Msk) ? 1UL : 0UL);
}

/**
  * @brief      Clear Timer Time-out Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function clears timer time-out interrupt flag to 0.
  */
__STATIC_INLINE void TIMER_ClearIntFlag(TIMER_T *timer)
{
    timer->INTSTS = TIMER_INTSTS_TIF_Msk;
}

/**
  * @brief      Get Timer Capture Interrupt Flag
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Timer capture interrupt did not occur
  * @retval     1   Timer capture interrupt occurred
  *
  * @details    This function indicates timer capture trigger interrupt occurred or not.
  */
__STATIC_INLINE uint32_t TIMER_GetCaptureIntFlag(TIMER_T *timer)
{
    return timer->EINTSTS;
}

/**
  * @brief      Clear Timer Capture Interrupt Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function clears timer capture trigger interrupt flag to 0.
  */
__STATIC_INLINE void TIMER_ClearCaptureIntFlag(TIMER_T *timer)
{
    timer->EINTSTS = TIMER_EINTSTS_CAPIF_Msk;
}

/**
  * @brief      Get Timer Wake-up Flag
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @retval     0   Timer does not cause CPU wake-up
  * @retval     1   Timer interrupt event cause CPU wake-up
  *
  * @details    This function indicates timer interrupt event has waked up system or not.
  */
__STATIC_INLINE uint32_t TIMER_GetWakeupFlag(TIMER_T *timer)
{
    return (timer->INTSTS & TIMER_INTSTS_TWKF_Msk ? 1UL : 0UL);
}

/**
  * @brief      Clear Timer Wake-up Flag
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function clears the timer wake-up system flag to 0.
  */
__STATIC_INLINE void TIMER_ClearWakeupFlag(TIMER_T *timer)
{
    timer->INTSTS = TIMER_INTSTS_TWKF_Msk;
}

/**
  * @brief      Get Capture value
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     24-bit Capture Value
  *
  * @details    This function reports the current 24-bit timer capture value.
  */
__STATIC_INLINE uint32_t TIMER_GetCaptureData(TIMER_T *timer)
{
    return timer->CAP;
}

/**
  * @brief      Get Counter value
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     24-bit Counter Value
  *
  * @details    This function reports the current 24-bit timer counter value.
  */
__STATIC_INLINE uint32_t TIMER_GetCounter(TIMER_T *timer)
{
    return timer->CNT;
}

/**
  * @brief      Reset Counter
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This function is used to reset current counter value and internal prescale counter value.
  */
__STATIC_INLINE void TIMER_ResetCounter(TIMER_T *timer)
{
    timer->CNT = 0UL;
    while ((timer->CNT & TIMER_CNT_RSTACT_Msk) == TIMER_CNT_RSTACT_Msk)
    {
        ;
    }
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

#endif /* __NU_TIMER_H__ */


