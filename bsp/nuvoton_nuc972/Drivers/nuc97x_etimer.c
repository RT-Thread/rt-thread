/*
 * File      : nuc97x_etimer.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "nuc97x_conf.h"

/**
  * @brief This API is used to get the clock frequency of Timer
  * @param[in] timer ETIMER number. Range from 0 ~ 3
  * @return Timer clock frequency
  * @note This API cannot return correct clock rate if timer source is external clock input.
  */
static UINT ETIMER_GetModuleClock(UINT timer)
{
    UINT src;

    src = (inpw(REG_CLK_DIVCTL8) >> (16 + timer * 4)) & 0x3;

    if (src == 0)
        return 12000000;
    else if (src == 1)
        return sysGetClock(SYS_PCLK);
    else if (src == 2)
        return sysGetClock(SYS_PCLK) / 4096;
    else return 32768;

}


/**
  * @brief This API is used to configure timer to operate in specified mode
  *        and frequency. If timer cannot work in target frequency, a closest
  *        frequency will be chose and returned.
  * @param[in] timer ETIMER number. Range from 0 ~ 3
  * @param[in] u32Mode Operation mode. Possible options are
  *                 - \ref ETIMER_ONESHOT_MODE
  *                 - \ref ETIMER_PERIODIC_MODE
  *                 - \ref ETIMER_TOGGLE_MODE
  *                 - \ref ETIMER_CONTINUOUS_MODE
  * @param[in] u32Freq Target working frequency
  * @return Real Timer working frequency
  * @note After calling this API, Timer is \b NOT running yet. But could start timer running be calling
  *       \ref ETIMER_Start macro or program registers directly
  */
UINT ETIMER_Open(UINT timer, UINT u32Mode, UINT u32Freq)
{
    UINT u32Clk = ETIMER_GetModuleClock(timer);
    UINT u32Cmpr = 0, u32Prescale = 0;

    // Fastest possible timer working freq is u32Clk / 2. While cmpr = 2, pre-scale = 0
    if (u32Freq > (u32Clk / 2))
    {
        u32Cmpr = 2;
    }
    else
    {
        if (u32Clk >= 0x4000000)
        {
            u32Prescale = 7;    // real prescaler value is 8
            u32Clk >>= 3;
        }
        else if (u32Clk >= 0x2000000)
        {
            u32Prescale = 3;    // real prescaler value is 4
            u32Clk >>= 2;
        }
        else if (u32Clk >= 0x1000000)
        {
            u32Prescale = 1;    // real prescaler value is 2
            u32Clk >>= 1;
        }
        u32Cmpr = u32Clk / u32Freq;
    }

    if (timer == 0)
    {
        outpw(REG_ETMR0_CMPR, u32Cmpr);
        outpw(REG_ETMR0_PRECNT, u32Prescale);
        outpw(REG_ETMR0_CTL, 1 | u32Mode);
    }
    else if (timer == 1)
    {
        outpw(REG_ETMR1_CMPR, u32Cmpr);
        outpw(REG_ETMR1_PRECNT, u32Prescale);
        outpw(REG_ETMR1_CTL, 1 | u32Mode);
    }
    else if (timer == 2)
    {
        outpw(REG_ETMR2_CMPR, u32Cmpr);
        outpw(REG_ETMR2_PRECNT, u32Prescale);
        outpw(REG_ETMR2_CTL, 1 | u32Mode);
    }
    else
    {
        outpw(REG_ETMR3_CMPR, u32Cmpr);
        outpw(REG_ETMR3_PRECNT, u32Prescale);
        outpw(REG_ETMR3_CTL, 1 | u32Mode);
    }

    return(u32Clk / (u32Cmpr * (u32Prescale + 1)));
}

/**
  * @brief This API stops Timer counting and disable the Timer interrupt function
  * @param[in] timer ETIMER number. Range from 0 ~ 3
  * @return None
  */
void ETIMER_Close(UINT timer)
{
    if (timer == 0)
    {
        outpw(REG_ETMR0_CTL, 0);
        outpw(REG_ETMR0_IER, 0);
    }
    else if (timer == 1)
    {
        outpw(REG_ETMR1_CTL, 0);
        outpw(REG_ETMR1_IER, 0);
    }
    else if (timer == 2)
    {
        outpw(REG_ETMR2_CTL, 0);
        outpw(REG_ETMR2_IER, 0);
    }
    else
    {
        outpw(REG_ETMR3_CTL, 0);
        outpw(REG_ETMR3_IER, 0);
    }
}

/**
  * @brief This API is used to create a delay loop for u32usec micro seconds
  * @param[in] timer ETIMER number. Range from 0 ~ 3
  * @param[in] u32Usec Delay period in micro seconds with 10 usec every step. Valid values are between 10~1000000 (10 micro second ~ 1 second)
  * @return None
  * @note This API overwrites the register setting of the timer used to count the delay time.
  * @note This API use polling mode. So there is no need to enable interrupt for the timer module used to generate delay
  */
void ETIMER_Delay(UINT timer, UINT u32Usec)
{
    UINT u32Clk = ETIMER_GetModuleClock(timer);
    UINT u32Prescale = 0, delay = 300000000 / u32Clk;
    float fCmpr;

    // Clear current timer configuration
    if (timer == 0)
    {
        outpw(REG_ETMR0_CTL, 0);
    }
    else if (timer == 1)
    {
        outpw(REG_ETMR1_CTL, 0);
    }
    else if (timer == 2)
    {
        outpw(REG_ETMR2_CTL, 0);
    }
    else
    {
        outpw(REG_ETMR3_CTL, 0);
    }

    if (u32Clk == 10000)
    {         // min delay is 100us if timer clock source is LIRC 10k
        u32Usec = ((u32Usec + 99) / 100) * 100;
    }
    else
    {    // 10 usec every step
        u32Usec = ((u32Usec + 9) / 10) * 10;
    }

    if (u32Clk >= 0x4000000)
    {
        u32Prescale = 7;    // real prescaler value is 8
        u32Clk >>= 3;
    }
    else if (u32Clk >= 0x2000000)
    {
        u32Prescale = 3;    // real prescaler value is 4
        u32Clk >>= 2;
    }
    else if (u32Clk >= 0x1000000)
    {
        u32Prescale = 1;    // real prescaler value is 2
        u32Clk >>= 1;
    }

    // u32Usec * u32Clk might overflow if using UINT
    fCmpr = ((float) u32Usec * (float) u32Clk) / 1000000.0;

    if (timer == 0)
    {
        outpw(REG_ETMR0_CMPR, (UINT )fCmpr);
        outpw(REG_ETMR0_PRECNT, u32Prescale);
        outpw(REG_ETMR0_CTL, 1);
    }
    else if (timer == 1)
    {
        outpw(REG_ETMR1_CMPR, (UINT )fCmpr);
        outpw(REG_ETMR1_PRECNT, u32Prescale);
        outpw(REG_ETMR1_CTL, 1);
    }
    else if (timer == 2)
    {
        outpw(REG_ETMR2_CMPR, (UINT )fCmpr);
        outpw(REG_ETMR2_PRECNT, u32Prescale);
        outpw(REG_ETMR2_CTL, 1);
    }
    else
    {
        outpw(REG_ETMR3_CMPR, (UINT )fCmpr);
        outpw(REG_ETMR3_PRECNT, u32Prescale);
        outpw(REG_ETMR3_CTL, 1);
    }

    // When system clock is faster than timer clock, it is possible timer active bit cannot set in time while we check it.
    // And the while loop below return immediately, so put a tiny delay here allowing timer start counting and raise active flag.
    for (; delay > 0; delay--)
    {
    }

    if(timer == 0) {
        while(inpw(REG_ETMR0_CTL) & 0x80);
    } else if(timer == 1) {
        while(inpw(REG_ETMR1_CTL) & 0x80);
    } else if(timer == 2) {
        while(inpw(REG_ETMR2_CTL) & 0x80);
    } else {
        while(inpw(REG_ETMR3_CTL) & 0x80);
    }
}

/**
  * @brief This API is used to enable timer capture function with specified mode and capture edge
  * @param[in] timer ETIMER number. Range from 0 ~ 3
  * @param[in] u32CapMode Timer capture mode. Could be
  *                 - \ref ETIMER_CAPTURE_FREE_COUNTING_MODE
  *                 - \ref ETIMER_CAPTURE_TRIGGER_COUNTING_MODE
  *                 - \ref ETIMER_CAPTURE_COUNTER_RESET_MODE
  * @param[in] u32Edge Timer capture edge. Possible values are
  *                 - \ref ETIMER_CAPTURE_FALLING_EDGE
  *                 - \ref ETIMER_CAPTURE_RISING_EDGE
  *                 - \ref ETIMER_CAPTURE_FALLING_THEN_RISING_EDGE
  *                 - \ref ETIMER_CAPTURE_RISING_THEN_FALLING_EDGE
  * @return None
  * @note Timer frequency should be configured separately by using \ref ETIMER_Open API, or program registers directly
  */
void ETIMER_EnableCapture(UINT timer, UINT u32CapMode, UINT u32Edge)
{
    if (timer == 0)
    {
        outpw(REG_ETMR0_CTL, (inpw(REG_ETMR0_CTL) & ~0x1E0000) | u32CapMode | u32Edge | 0x10000);
    }
    else if (timer == 1)
    {
        outpw(REG_ETMR1_CTL, (inpw(REG_ETMR1_CTL) & ~0x1E0000) | u32CapMode | u32Edge | 0x10000);
    }
    else if (timer == 2)
    {
        outpw(REG_ETMR2_CTL, (inpw(REG_ETMR2_CTL) & ~0x1E0000) | u32CapMode | u32Edge | 0x10000);
    }
    else
    {
        outpw(REG_ETMR3_CTL, (inpw(REG_ETMR3_CTL) & ~0x1E0000) | u32CapMode | u32Edge | 0x10000);
    }
}

/**
  * @brief This API is used to disable the Timer capture function
  * @param[in] timer ETIMER number. Range from 0 ~ 3
  * @return None
  */
void ETIMER_DisableCapture(UINT timer)
{
    if (timer == 0)
    {
        outpw(REG_ETMR0_CTL, inpw(REG_ETMR0_CTL) & ~0x10000);
    }
    else if (timer == 1)
    {
        outpw(REG_ETMR1_CTL, inpw(REG_ETMR1_CTL) & ~0x10000);
    }
    else if (timer == 2)
    {
        outpw(REG_ETMR2_CTL, inpw(REG_ETMR2_CTL) & ~0x10000);
    }
    else
    {
        outpw(REG_ETMR3_CTL, inpw(REG_ETMR3_CTL) & ~0x10000);
    }
}

static void ETMR0_IRQHandler(int vector,void *param)
{
    // clear timer interrupt flag
    ETIMER_ClearIntFlag(0);

    rt_tick_increase();
}

void  rt_hw_systick_init (void)
{
    // Enable ETIMER0 engine clock
    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | (1 << 4));

    // Set timer frequency to 1HZ
    ETIMER_Open(0, ETIMER_PERIODIC_MODE, RT_TICK_PER_SECOND);
    // Enable timer interrupt
    ETIMER_EnableInt(0);
    ETIMER_Start(0);

    rt_hw_interrupt_install(ETMR0_IRQn,ETMR0_IRQHandler,RT_NULL,"etmr0");
    rt_hw_interrupt_set_priority(ETMR0_IRQn,IRQ_LEVEL_1);
    rt_hw_interrupt_set_type(ETMR0_IRQn,HIGH_LEVEL_SENSITIVE);
    rt_hw_interrupt_umask(ETMR0_IRQn);
} /* rt_hw_systick_init */
