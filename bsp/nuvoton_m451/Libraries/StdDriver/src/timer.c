/**************************************************************************//**
 * @file     timer.c
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series Timer driver source file
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M451Series.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TIMER_Driver TIMER Driver
  @{
*/

/** @addtogroup TIMER_EXPORTED_FUNCTIONS TIMER Exported Functions
  @{
*/

/**
  * @brief      Open Timer with Operate Mode and Frequency
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Mode     Operation mode. Possible options are
  *                         - \ref TIMER_ONESHOT_MODE
  *                         - \ref TIMER_PERIODIC_MODE
  *                         - \ref TIMER_TOGGLE_MODE
  *                         - \ref TIMER_CONTINUOUS_MODE
  * @param[in]  u32Freq     Target working frequency
  *
  * @return     Real timer working frequency
  *
  * @details    This API is used to configure timer to operate in specified mode and frequency.
  *             If timer cannot work in target frequency, a closest frequency will be chose and returned.
  * @note       After calling this API, Timer is \b NOT running yet. But could start timer running be calling
  *             \ref TIMER_Start macro or program registers directly.
  */
uint32_t TIMER_Open(TIMER_T *timer, uint32_t u32Mode, uint32_t u32Freq)
{
    uint32_t u32Clk = TIMER_GetModuleClock(timer);
    uint32_t u32Cmpr = 0, u32Prescale = 0;

    // Fastest possible timer working freq is (u32Clk / 2). While cmpr = 2, pre-scale = 0.
    if(u32Freq > (u32Clk / 2))
    {
        u32Cmpr = 2;
    }
    else
    {
        if(u32Clk > 64000000)
        {
            u32Prescale = 7;    // real prescaler value is 8
            u32Clk >>= 3;
        }
        else if(u32Clk > 32000000)
        {
            u32Prescale = 3;    // real prescaler value is 4
            u32Clk >>= 2;
        }
        else if(u32Clk > 16000000)
        {
            u32Prescale = 1;    // real prescaler value is 2
            u32Clk >>= 1;
        }

        u32Cmpr = u32Clk / u32Freq;
    }

    timer->CTL = u32Mode | u32Prescale;
    timer->CMP = u32Cmpr;

    return(u32Clk / (u32Cmpr * (u32Prescale + 1)));
}

/**
  * @brief      Stop Timer Counting
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This API stops timer counting and disable all timer interrupt function.
  */
void TIMER_Close(TIMER_T *timer)
{
    timer->CTL = 0;
    timer->EXTCTL = 0;
}

/**
  * @brief      Create a specify Delay Time
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Usec     Delay period in micro seconds. Valid values are between 100~1000000 (100 micro second ~ 1 second).
  *
  * @return     None
  *
  * @details    This API is used to create a delay loop for u32usec micro seconds by using timer one-shot mode.
  * @note       This API overwrites the register setting of the timer used to count the delay time.
  * @note       This API use polling mode. So there is no need to enable interrupt for the timer module used to generate delay.
  */
void TIMER_Delay(TIMER_T *timer, uint32_t u32Usec)
{
    uint32_t u32Clk = TIMER_GetModuleClock(timer);
    uint32_t u32Prescale = 0, delay = (SystemCoreClock / u32Clk) + 1;
    uint32_t u32Cmpr, u32NsecPerTick;

    // Clear current timer configuration/
    timer->CTL = 0;
    timer->EXTCTL = 0;

    if(u32Clk <= 1000000)    // min delay is 1000 us if timer clock source is <= 1 MHz
    {
        if(u32Usec < 1000)
            u32Usec = 1000;
        if(u32Usec > 1000000)
            u32Usec = 1000000;
    }
    else
    {
        if(u32Usec < 100)
            u32Usec = 100;
        if(u32Usec > 1000000)
            u32Usec = 1000000;
    }

    if(u32Clk <= 1000000)
    {
        u32Prescale = 0;
        u32NsecPerTick = 1000000000 / u32Clk;
        u32Cmpr = (u32Usec * 1000) / u32NsecPerTick;
    }
    else
    {
        if(u32Clk > 64000000)
        {
            u32Prescale = 7;    // real prescaler value is 8
            u32Clk >>= 3;
        }
        else if(u32Clk > 32000000)
        {
            u32Prescale = 3;    // real prescaler value is 4
            u32Clk >>= 2;
        }
        else if(u32Clk > 16000000)
        {
            u32Prescale = 1;    // real prescaler value is 2
            u32Clk >>= 1;
        }

        if(u32Usec < 250)
        {
            u32Cmpr = (u32Usec * u32Clk) / 1000000;
        }
        else
        {
            u32NsecPerTick = 1000000000 / u32Clk;
            u32Cmpr = (u32Usec * 1000) / u32NsecPerTick;
        }
    }

    timer->CMP = u32Cmpr;
    timer->CTL = TIMER_CTL_CNTEN_Msk | TIMER_ONESHOT_MODE | u32Prescale;

    // When system clock is faster than timer clock, it is possible timer active bit cannot set in time while we check it.
    // And the while loop below return immediately, so put a tiny delay here allowing timer start counting and raise active flag.
    for(; delay > 0; delay--)
    {
        __NOP();
    }

    while(timer->CTL & TIMER_CTL_ACTSTS_Msk);
}

/**
  * @brief      Enable Timer Capture Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32CapMode  Timer capture mode. Could be
  *                         - \ref TIMER_CAPTURE_FREE_COUNTING_MODE
  *                         - \ref TIMER_CAPTURE_COUNTER_RESET_MODE
  * @param[in]  u32Edge     Timer capture trigger edge. Possible values are
  *                         - \ref TIMER_CAPTURE_FALLING_EDGE
  *                         - \ref TIMER_CAPTURE_RISING_EDGE
  *                         - \ref TIMER_CAPTURE_FALLING_AND_RISING_EDGE
  *
  * @return     None
  *
  * @details    This API is used to enable timer capture function with specify capture trigger edge \n
  *             to get current counter value or reset counter value to 0.
  * @note       Timer frequency should be configured separately by using \ref TIMER_Open API, or program registers directly.
  */
void TIMER_EnableCapture(TIMER_T *timer, uint32_t u32CapMode, uint32_t u32Edge)
{

    timer->EXTCTL = (timer->EXTCTL & ~(TIMER_EXTCTL_CAPFUNCS_Msk | TIMER_EXTCTL_CAPEDGE_Msk)) |
                    u32CapMode | u32Edge | TIMER_EXTCTL_CAPEN_Msk;
}

/**
  * @brief      Disable Timer Capture Function
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This API is used to disable the timer capture function.
  */
void TIMER_DisableCapture(TIMER_T *timer)
{
    timer->EXTCTL &= ~TIMER_EXTCTL_CAPEN_Msk;
}

/**
  * @brief      Enable Timer Counter Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Edge     Detection edge of counter pin. Could be ether
  *                         - \ref TIMER_COUNTER_FALLING_EDGE, or
  *                         - \ref TIMER_COUNTER_RISING_EDGE
  *
  * @return     None
  *
  * @details    This function is used to enable the timer counter function with specify detection edge.
  * @note       Timer compare value should be configured separately by using \ref TIMER_SET_CMP_VALUE macro or program registers directly.
  * @note       While using event counter function, \ref TIMER_TOGGLE_MODE cannot set as timer operation mode.
  */
void TIMER_EnableEventCounter(TIMER_T *timer, uint32_t u32Edge)
{
    timer->EXTCTL = (timer->EXTCTL & ~TIMER_EXTCTL_CNTPHASE_Msk) | u32Edge;
    timer->CTL |= TIMER_CTL_EXTCNTEN_Msk;
}

/**
  * @brief      Disable Timer Counter Function
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This API is used to disable the timer event counter function.
  */
void TIMER_DisableEventCounter(TIMER_T *timer)
{
    timer->CTL &= ~TIMER_CTL_EXTCNTEN_Msk;
}

/**
  * @brief      Get Timer Clock Frequency
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     Timer clock frequency
  *
  * @details    This API is used to get the timer clock frequency.
  * @note       This API cannot return correct clock rate if timer source is from external clock input.
  */
uint32_t TIMER_GetModuleClock(TIMER_T *timer)
{
    uint32_t u32Src;
    const uint32_t au32Clk[] = {__HXT, __LXT, 0, 0, 0, __LIRC, 0, __HIRC};

    if(timer == TIMER0)
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR0SEL_Msk) >> CLK_CLKSEL1_TMR0SEL_Pos;
    else if(timer == TIMER1)
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR1SEL_Msk) >> CLK_CLKSEL1_TMR1SEL_Pos;
    else if(timer == TIMER2)
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR2SEL_Msk) >> CLK_CLKSEL1_TMR2SEL_Pos;
    else  // Timer 3
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR3SEL_Msk) >> CLK_CLKSEL1_TMR3SEL_Pos;

    if(u32Src == 2)
    {
        return (SystemCoreClock);
    }

    return (au32Clk[u32Src]);
}

/*@}*/ /* end of group TIMER_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TIMER_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2013~2015 Nuvoton Technology Corp. ***/
