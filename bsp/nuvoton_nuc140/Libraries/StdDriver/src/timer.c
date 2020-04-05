/**************************************************************************//**
 * @file     timer.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    Timer driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC100Series.h"


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
  * @brief      Open Timer in specified mode and frequency
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Mode     Operation mode. Possible options are
  *                         - \ref TIMER_ONESHOT_MODE
  *                         - \ref TIMER_PERIODIC_MODE
  *                         - \ref TIMER_TOGGLE_MODE
  *                         - \ref TIMER_CONTINUOUS_MODE
  * @param[in]  u32Freq     Target working frequency
  *
  * @return     Real Timer working frequency
  *
  * @details    This API is used to configure timer to operate in specified mode and frequency.
  *             If timer cannot work in target frequency, a closest frequency will be chose and returned.
  * @note       After calling this API, Timer is \b NOT running yet. But could start timer running be calling
  *             \ref TIMER_Start macro or program registers directly.
  */
uint32_t TIMER_Open(TIMER_T *timer, uint32_t u32Mode, uint32_t u32Freq)
{
    uint32_t u32Clk = TIMER_GetModuleClock(timer);
    uint32_t u32Cmpr = 0UL, u32Prescale = 0UL;

    /* Fastest possible timer working freq is (u32Clk / 2). While cmpr = 2, prescaler = 0. */
    if(u32Freq > (u32Clk / 2UL))
    {
        u32Cmpr = 2UL;
    }
    else
    {
        u32Cmpr = u32Clk / u32Freq;
        u32Prescale = (u32Cmpr >> 24);  /* for 24 bits CMPDAT */
        if (u32Prescale > 0UL)
            u32Cmpr = u32Cmpr / (u32Prescale + 1UL);
    }

    timer->TCSR = u32Mode | u32Prescale;
    timer->TCMPR = u32Cmpr;

    return(u32Clk / (u32Cmpr * (u32Prescale + 1UL)));
}

/**
  * @brief      Stop Timer Counting
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This API stops Timer counting and disable all Timer interrupt function.
  */
void TIMER_Close(TIMER_T *timer)
{
    timer->TCSR = 0;
    timer->TEXCON = 0;
}

/**
  * @brief      Create a specify delay time
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32Usec     Delay period in micro seconds. Valid values are between 100~1000000 (100 micro second ~ 1 second).
  *
  * @return     None
  *
  * @details    This API is used to create a delay loop for u32usec micro seconds.
  * @note       This API overwrites the register setting of the timer used to count the delay time.
  * @note       This API use polling mode. So there is no need to enable interrupt for the timer module used to generate delay.
  */
void TIMER_Delay(TIMER_T *timer, uint32_t u32Usec)
{
    uint32_t u32Clk = TIMER_GetModuleClock(timer);
    uint32_t u32Prescale = 0UL, u32Delay = (SystemCoreClock / u32Clk) + 1UL;
    uint32_t u32Cmpr, u32NsecPerTick;

    /* Clear current timer configuration */
    timer->TCSR = 0UL;
    timer->TEXCON = 0UL;

    if(u32Clk <= 1000000UL)   /* min delay is 1000 us if timer clock source is <= 1 MHz */
    {
        if(u32Usec < 1000UL)
        {
            u32Usec = 1000UL;
        }
        if(u32Usec > 1000000UL)
        {
            u32Usec = 1000000UL;
        }
    }
    else
    {
        if(u32Usec < 100UL)
        {
            u32Usec = 100UL;
        }
        if(u32Usec > 1000000UL)
        {
            u32Usec = 1000000UL;
        }
    }

    if(u32Clk <= 1000000UL)
    {
        u32Prescale = 0UL;
        u32NsecPerTick = 1000000000UL / u32Clk;
        u32Cmpr = (u32Usec * 1000UL) / u32NsecPerTick;
    }
    else
    {
        u32Cmpr = u32Usec * (u32Clk / 1000000UL);
        u32Prescale = (u32Cmpr >> 24);  /* for 24 bits CMPDAT */
        if (u32Prescale > 0UL)
            u32Cmpr = u32Cmpr / (u32Prescale + 1UL);
    }

    timer->TCMPR = u32Cmpr;
    timer->TCSR = TIMER_TCSR_CEN_Msk | TIMER_ONESHOT_MODE | u32Prescale;

    /*
        When system clock is faster than timer clock, it is possible timer active bit cannot set in time while we check it.
        And the while loop below return immediately, so put a tiny delay here allowing timer start counting and raise active flag.
    */
    for(; u32Delay > 0UL; u32Delay--)
    {
        __NOP();
    }

    while(timer->TCSR & TIMER_TCSR_CACT_Msk);
}

/**
  * @brief      Enable Timer Capture Function
  *
  * @param[in]  timer       The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  * @param[in]  u32CapMode  Timer capture mode. Could be
  *                         - \ref TIMER_CAPTURE_FREE_COUNTING_MODE
  *                         - \ref TIMER_CAPTURE_COUNTER_RESET_MODE
  * @param[in]  u32Edge     Timer capture edge. Possible values are
  *                         - \ref TIMER_CAPTURE_FALLING_EDGE
  *                         - \ref TIMER_CAPTURE_RISING_EDGE
  *                         - \ref TIMER_CAPTURE_FALLING_AND_RISING_EDGE
  *
  * @return     None
  *
  * @details    This API is used to enable timer capture function with specified mode and capture edge.
  * @note       Timer frequency should be configured separately by using \ref TIMER_Open API, or program registers directly.
  */
void TIMER_EnableCapture(TIMER_T *timer, uint32_t u32CapMode, uint32_t u32Edge)
{

    timer->TEXCON = (timer->TEXCON & ~(TIMER_TEXCON_RSTCAPSEL_Msk |
                                       TIMER_TEXCON_TEX_EDGE_Msk)) |
                    u32CapMode | u32Edge | TIMER_TEXCON_TEXEN_Msk;
}

/**
  * @brief      Disable Timer Capture Function
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This API is used to disable the Timer capture function.
  */
void TIMER_DisableCapture(TIMER_T *timer)
{
    timer->TEXCON &= ~TIMER_TEXCON_TEXEN_Msk;
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
  * @details    This function is used to enable the Timer counter function with specify detection edge.
  * @note       Timer compare value should be configured separately by using \ref TIMER_SET_CMP_VALUE macro or program registers directly.
  * @note       While using event counter function, \ref TIMER_TOGGLE_MODE cannot set as timer operation mode.
  */
void TIMER_EnableEventCounter(TIMER_T *timer, uint32_t u32Edge)
{
    timer->TEXCON = (timer->TEXCON & ~TIMER_TEXCON_TX_PHASE_Msk) | u32Edge;
    timer->TCSR |= TIMER_TCSR_CTB_Msk;
}

/**
  * @brief      Disable Timer Counter Function
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     None
  *
  * @details    This API is used to disable the Timer event counter function.
  */
void TIMER_DisableEventCounter(TIMER_T *timer)
{
    timer->TCSR &= ~TIMER_TCSR_CTB_Msk;
}

/**
  * @brief      Get Timer Clock Frequency
  *
  * @param[in]  timer   The pointer of the specified Timer module. It could be TIMER0, TIMER1, TIMER2, TIMER3.
  *
  * @return     Timer clock frequency
  *
  * @details    This API is used to get the clock frequency of Timer.
  * @note       This API cannot return correct clock rate if timer source is external clock input.
  */
uint32_t TIMER_GetModuleClock(TIMER_T *timer)
{
    uint32_t u32Src;
    const uint32_t au32Clk[] = {__HXT, __LXT, 0, 0, 0, __LIRC, 0, __HIRC};

    if(timer == TIMER0)
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR0_S_Msk) >> CLK_CLKSEL1_TMR0_S_Pos;
    else if(timer == TIMER1)
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR1_S_Msk) >> CLK_CLKSEL1_TMR1_S_Pos;
    else if(timer == TIMER2)
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR2_S_Msk) >> CLK_CLKSEL1_TMR2_S_Pos;
    else  // Timer 3
        u32Src = (CLK->CLKSEL1 & CLK_CLKSEL1_TMR3_S_Msk) >> CLK_CLKSEL1_TMR3_S_Pos;

    if(u32Src == 2)
    {
        return(SystemCoreClock);
    }

    return(au32Clk[u32Src]);
}

/*@}*/ /* end of group TIMER_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TIMER_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
