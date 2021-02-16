/**
 * @file    mxc_sys.c
 * @brief   System level setup help
 */

/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2020-01-17 08:38:51 -0600 (Fri, 17 Jan 2020) $
 * $Revision: 50772 $
 *
 ******************************************************************************/

#include <stddef.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_sys.h"
#include "gpio.h"
#include "mxc_pins.h"
#include "gcr_regs.h"
#include "tmr_regs.h"
#include "pwrseq_regs.h"
#include "spi17y_regs.h"
#include "spimss_regs.h"
#include "mxc_delay.h"
#include "rtc.h"

/**
 * @ingroup MXC_sys
 * @{
 */

/***** Definitions *****/
#define SYS_CLOCK_TIMEOUT       MXC_DELAY_MSEC(1)

#define SYS_RTC_CLK 32768UL

/***** Functions ******/
static int SYS_Clock_Timeout(uint32_t ready)
{
    // Start timeout, wait for ready
    mxc_delay_start(SYS_CLOCK_TIMEOUT);
    do {
        if (MXC_GCR->clkcn & ready) {
            mxc_delay_stop();
            return E_NO_ERROR;
        }
    } while (mxc_delay_check() == E_BUSY);

    return E_TIME_OUT;
}

/* ************************************************************************ */
int SYS_Clock_Select(sys_system_clock_t clock, mxc_tmr_regs_t* tmr)
{
    uint32_t current_clock,ovr, div;

    // Save the current system clock
    current_clock = MXC_GCR->clkcn & MXC_F_GCR_CLKCN_CLKSEL;
    // Set FWS higher than what the minimum for the fastest clock is
    MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x5UL << MXC_F_GCR_MEMCKCN_FWS_POS);
    switch(clock) {
        case SYS_CLOCK_NANORING:
            // Set NANORING clock as System Clock
            MXC_SETFIELD(MXC_GCR->clkcn, MXC_F_GCR_CLKCN_CLKSEL, MXC_S_GCR_CLKCN_CLKSEL_NANORING);

        break;
        case SYS_CLOCK_HFXIN:
            // Enable 32k Oscillator
            MXC_GCR->clkcn |=MXC_F_GCR_CLKCN_X32K_EN;

            // Check if 32k clock is ready
            if (SYS_Clock_Timeout(MXC_F_GCR_CLKCN_X32K_RDY) != E_NO_ERROR) {
                return E_TIME_OUT;
            }
            MXC_RTC->ctrl |= MXC_F_RTC_CTRL_WE;      // Allow writing to registers

            // Set 32k clock as System Clock
            MXC_SETFIELD(MXC_GCR->clkcn, MXC_F_GCR_CLKCN_CLKSEL, MXC_S_GCR_CLKCN_CLKSEL_HFXIN);

        break;

        case SYS_CLOCK_HFXIN_DIGITAL:
            // Enable 32k Oscillator
            MXC_GCR->clkcn |=MXC_F_GCR_CLKCN_X32K_EN;

            // Check if 32k clock is ready
            if (SYS_Clock_Timeout(MXC_F_GCR_CLKCN_X32K_RDY) != E_NO_ERROR) {
                return E_TIME_OUT;
            }
            MXC_RTC->ctrl |= MXC_F_RTC_CTRL_WE;      // Allow writing to registers
            MXC_RTC->oscctrl |= MXC_F_RTC_OSCCTRL_BYPASS;  // To allow square wave driven on 32KIN
            // Set 32k clock as System Clock
            MXC_SETFIELD(MXC_GCR->clkcn, MXC_F_GCR_CLKCN_CLKSEL, MXC_S_GCR_CLKCN_CLKSEL_HFXIN);

        break;
        case SYS_CLOCK_HIRC:
            // Enable 96MHz Clock
            MXC_GCR->clkcn |=MXC_F_GCR_CLKCN_HIRC_EN;

            // Check if 96MHz clock is ready
            if (SYS_Clock_Timeout(MXC_F_GCR_CLKCN_HIRC_RDY) != E_NO_ERROR) {
                return E_TIME_OUT;
            }

            // Set 96MHz clock as System Clock
            MXC_SETFIELD(MXC_GCR->clkcn, MXC_F_GCR_CLKCN_CLKSEL, MXC_S_GCR_CLKCN_CLKSEL_HIRC);

        break;
        default:
        return E_BAD_PARAM;
    }

    // Wait for system clock to be ready
    if (SYS_Clock_Timeout(MXC_F_GCR_CLKCN_CKRDY) != E_NO_ERROR) {

        // Restore the old system clock if timeout
        MXC_SETFIELD(MXC_GCR->clkcn, MXC_F_GCR_CLKCN_CLKSEL, current_clock);

        return E_TIME_OUT;
    }

    // Disable other clocks
    switch(clock) {
        case SYS_CLOCK_NANORING:
            MXC_GCR->clkcn &= ~(MXC_F_GCR_CLKCN_HIRC_EN);
        break;

        case SYS_CLOCK_HFXIN:
            MXC_GCR->clkcn &= ~(MXC_F_GCR_CLKCN_HIRC_EN);
        break;

        case SYS_CLOCK_HFXIN_DIGITAL:
            MXC_GCR->clkcn &= ~(MXC_F_GCR_CLKCN_HIRC_EN);
        break;

        case SYS_CLOCK_HIRC:
            //Don't disable 32KHz clock
        break;
    }

    // Update the system core clock
    SystemCoreClockUpdate();

    // Get the clock divider
    div = (MXC_GCR->clkcn & MXC_F_GCR_CLKCN_PSC) >> MXC_F_GCR_CLKCN_PSC_POS;

    //get ovr setting
    ovr = (MXC_PWRSEQ->lp_ctrl & MXC_F_PWRSEQ_LP_CTRL_OVR);

    //Set flash wait settings
    if(ovr == MXC_S_PWRSEQ_LP_CTRL_OVR_0_9V){

        if(div == 0){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x2UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else{
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x1UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        }

    } else if( ovr == MXC_S_PWRSEQ_LP_CTRL_OVR_1_0V){
        if(div == 0){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x2UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else{
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x1UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        }

    } else {

        if(div == 0){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x4UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else if(div == 1){
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x2UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        } else{
            MXC_GCR->memckcn = (MXC_GCR->memckcn & ~(MXC_F_GCR_MEMCKCN_FWS)) | (0x1UL << MXC_F_GCR_MEMCKCN_FWS_POS);

        }
    }

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_ClockEnable_X32K(sys_cfg_rtc_t *sys_cfg)
{
    // Enable 32k Oscillator
    MXC_GCR->clkcn |=MXC_F_GCR_CLKCN_X32K_EN;

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_ClockDisable_X32K()
{
    // Disable 32k Oscillator
    MXC_GCR->clkcn &= (~MXC_F_GCR_CLKCN_X32K_EN);
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_UART_Init(mxc_uart_regs_t *uart, const sys_cfg_uart_t* sys_cfg)
{
        // Configure GPIO for UART
    if (uart == MXC_UART0) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_UART0);
        if(sys_cfg->map == MAP_A){
            GPIO_Config(&gpio_cfg_uart0a);
        }
        else{
            return E_BAD_PARAM;
        }
        if(sys_cfg->flow_flag == UART_FLOW_ENABLE){
            GPIO_Config(&gpio_cfg_uart0rtscts);
        }
    }
    if (uart == MXC_UART1) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_UART1);
        if(sys_cfg->map == MAP_A){
            GPIO_Config(&gpio_cfg_uart1a);
        }
        else if(sys_cfg->map == MAP_B){
            GPIO_Config(&gpio_cfg_uart1b);
        }
        else if(sys_cfg->map == MAP_C){
            GPIO_Config(&gpio_cfg_uart1c);
        }
        else{
            return E_BAD_PARAM;
        }
        if(sys_cfg->flow_flag == UART_FLOW_ENABLE){
            GPIO_Config(&gpio_cfg_uart1rtscts);
        }
    }
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_UART_Shutdown(mxc_uart_regs_t *uart)
{
    if (uart == MXC_UART0) {
        SYS_ClockDisable(SYS_PERIPH_CLOCK_UART0);
    }
    else if (uart == MXC_UART1) {
        SYS_ClockDisable(SYS_PERIPH_CLOCK_UART1);
    }
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_I2C_Init(mxc_i2c_regs_t *i2c,  const sys_cfg_i2c_t* sys_cfg)
{

    // Configure GPIO for I2C
    if (i2c == MXC_I2C0) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_I2C0);
        GPIO_Config(&gpio_cfg_i2c0);

    } else if (i2c == MXC_I2C1) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_I2C1);
        GPIO_Config(&gpio_cfg_i2c1);
    } else {
        return E_NO_DEVICE;
    }

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_I2C_Shutdown(mxc_i2c_regs_t *i2c)
{
    if (i2c == MXC_I2C0) {
        gpio_cfg_t cfg = { gpio_cfg_i2c0.port, gpio_cfg_i2c0.mask, GPIO_FUNC_IN, GPIO_PAD_NONE };
        SYS_ClockDisable(SYS_PERIPH_CLOCK_I2C0);
        GPIO_Config(&cfg);
    } else if (i2c == MXC_I2C1) {
        gpio_cfg_t cfg = { gpio_cfg_i2c1.port, gpio_cfg_i2c1.mask, GPIO_FUNC_IN, GPIO_PAD_NONE };
        SYS_ClockDisable(SYS_PERIPH_CLOCK_I2C1);
        GPIO_Config(&cfg);
    } else {
        return E_NO_DEVICE;
    }
    // Clear registers
    i2c->ctrl = 0;

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_DMA_Init(void)
{
    SYS_ClockEnable(SYS_PERIPH_CLOCK_DMA);
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_DMA_Shutdown(void)
{
    SYS_ClockDisable(SYS_PERIPH_CLOCK_DMA);
    return E_NO_ERROR;
}

/* ************************************************************************ */
unsigned SYS_I2C_GetFreq(mxc_i2c_regs_t *i2c)
{
    return PeripheralClock;
}

/* ************************************************************************ */
unsigned SYS_TMR_GetFreq(mxc_tmr_regs_t *tmr)
{
    return PeripheralClock;
}

/* ************************************************************************ */
void SYS_Reset0(sys_reset0_t reset)
{
    MXC_GCR->rstr0 = reset;
    while(MXC_GCR->rstr0 != 0x0) {}
}

/* ************************************************************************ */
void SYS_Reset1(sys_reset1_t reset)
{
    MXC_GCR->rstr1 = reset;
    while(MXC_GCR->rstr0 != 0x0) {}
}

/* ************************************************************************ */
void SYS_ClockDisable(sys_periph_clock_t clock)
{
    /* The sys_periph_clock_t enum uses bit 27 (an unused bit in both perkcn registers)
       to determine which of the two perckcn registers to write to. */
    if (clock & (1<<27)) {
        clock &= ~(1<<27);
        MXC_GCR->perckcn1 |= clock;
    } else {
        MXC_GCR->perckcn0 |= clock;
    }
}

/* ************************************************************************ */
void SYS_ClockEnable(sys_periph_clock_t clock)
{
    /* The sys_periph_clock_t enum uses bit 27 (an unused bit in both perkcn registers)
       to determine which of the two perckcn registers to write to. */
    if (clock & (1<<27)) {
        clock &= ~(1<<27);
        MXC_GCR->perckcn1 &= ~(clock);
    } else {
        MXC_GCR->perckcn0 &= ~(clock);
    }
}

/* ************************************************************************ */
#if defined (__ICCARM__)
#pragma optimize=none           /* Turn off optimizations for next function */
#elif defined ( __CC_ARM )
/* Keil MDK - Turn off optimizations after saving current state */
#pragma push                    /* Save current optimization level */
#pragma O0                      /* Optimization level 0 */
#elif ( __GNUC__ )
/* GCC - Turn off optimizations after saving current state */
#pragma GCC push_options        /* Save current optimization level */
#pragma GCC optimize ("O0")     /* Set optimization level to none for this function */
#endif
void SYS_Flash_Operation(void)
{
    volatile uint32_t *line_addr;
    volatile uint32_t __attribute__ ((unused)) line;

    // Clear the cache
    MXC_ICC->cache_ctrl ^= MXC_F_ICC_CACHE_CTRL_CACHE_EN;
    MXC_ICC->cache_ctrl ^= MXC_F_ICC_CACHE_CTRL_CACHE_EN;

    // Clear the line fill buffer
    line_addr = (uint32_t*)(MXC_FLASH_MEM_BASE);
    line = *line_addr;

    line_addr = (uint32_t*)(MXC_FLASH_MEM_BASE + MXC_FLASH_PAGE_SIZE);
    line = *line_addr;
}
/* Set optimizations to the previous level. For IAR, the optimize none applies
   only to the next function. Keil MDK and GNUC need state restored. */
#if defined ( __CC_ARM )
#pragma pop                     /* Restore Kiel MDK optimizations to saved level */
#elif defined ( __GNUC__ )
#pragma GCC pop_options         /* Restore GCC optimization level */
#endif

/* ************************************************************************ */
int SYS_TMR_Init(mxc_tmr_regs_t *tmr, const sys_cfg_tmr_t* sys_cfg)
{
    if(sys_cfg) {
        if(sys_cfg->out_en) {

            if (tmr == MXC_TMR0) {
                GPIO_Config(&gpio_cfg_tmr0);
            }
        }
    }

    if (tmr == MXC_TMR0) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_T0);
    }
    else if (tmr == MXC_TMR1) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_T1);
    }
    else if (tmr == MXC_TMR2) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_T2);
    }

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_FLC_Init(const sys_cfg_flc_t* sys_cfg)
{
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_FLC_Shutdown(void)
{
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_SPI17Y_Init(mxc_spi17y_regs_t *spi, const sys_cfg_spi17y_t* sys_cfg)
{
    // Configure GPIO for spi17y
    if (spi == MXC_SPI17Y) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_SPI17Y);
        if(sys_cfg->map == MAP_A){
            GPIO_Config(&gpio_cfg_spi17y);
             MXC_GPIO0->ds |= 0x0003BF0;
        }else{
            return E_BAD_PARAM;
        }
    } else {
        return E_NO_DEVICE;
    }
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_SPI17Y_Shutdown(mxc_spi17y_regs_t *spi)
{
    if (spi == MXC_SPI17Y) {
        SYS_ClockDisable(SYS_PERIPH_CLOCK_SPI17Y);
    }
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_SPIMSS_Init(mxc_spimss_regs_t *spi, const sys_cfg_spimss_t* sys_cfg)
{
    // Configure GPIO for spimss
    if (spi == MXC_SPIMSS) {
        SYS_ClockEnable(SYS_PERIPH_CLOCK_SPIMSS);
        if(sys_cfg->map == MAP_A){
            GPIO_Config(&gpio_cfg_spimss1a);  // SPI1A chosen
        }else if(sys_cfg->map == MAP_B){
            GPIO_Config(&gpio_cfg_spimss1b);  // SPI1B chosen
        }else{
            return E_BAD_PARAM;
        }
    } else {
        return E_NO_DEVICE;
    }
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_SPIMSS_Shutdown(mxc_spimss_regs_t *spi)
{
    if(spi == MXC_SPIMSS) {
        SYS_ClockDisable(SYS_PERIPH_CLOCK_SPIMSS);
    }
    return E_NO_ERROR;
}

int SYS_TMR_Shutdown(mxc_tmr_regs_t *tmr)
{
    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_I2S_Init(const sys_cfg_i2s_t* sys_cfg)
{
    if(sys_cfg->map == MAP_A) {
        GPIO_Config(&gpio_cfg_i2s1a);
    }
    else if(sys_cfg->map == MAP_B) {
        GPIO_Config(&gpio_cfg_i2s1b);
    }
    else {
        return E_BAD_PARAM;
    }
        SYS_ClockEnable(SYS_PERIPH_CLOCK_SPIMSS);

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_I2S_Shutdown(void)
{
        SYS_ClockDisable(SYS_PERIPH_CLOCK_SPIMSS);

    return E_NO_ERROR;
}

/* ************************************************************************ */
int SYS_I2S_GetFreq(mxc_spimss_regs_t *spimss)
{
    return PeripheralClock;
}

/* ************************************************************************ */
int SYS_RTC_SqwavInit(const sys_cfg_rtc_t* sys_cfg)
{
    GPIO_Config(&gpio_cfg_rtc);
    return E_NO_ERROR;
}

/* ************************************************************************ */
uint32_t SYS_SysTick_GetFreq(void)
{
    // Determine is using internal (SystemCoreClock) or external (32768) clock
    if ( (SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk) || !(SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)) {
        return SystemCoreClock;
    } else {
        return SYS_RTC_CLK;
    }
}

/* ************************************************************************ */
int SYS_SysTick_Config(uint32_t ticks, int clk_src, mxc_tmr_regs_t* tmr)
{

    if(ticks == 0)
        return E_BAD_PARAM;

    // If SystemClock, call default CMSIS config and return
    if (clk_src) {
        return SysTick_Config(ticks);
    } else { /* External clock source requested
                enable RTC clock in run mode*/
        RTC_Init(MXC_RTC, 0, 0, NULL);
        RTC_EnableRTCE(MXC_RTC);

        // Disable SysTick Timer
        SysTick->CTRL = 0;
        // Check reload value for valid
        if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk) {
            // Reload value impossible
            return E_BAD_PARAM;
        }
        // set reload register
        SysTick->LOAD  = ticks - 1;

        // set Priority for Systick Interrupt
        NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

        // Load the SysTick Counter Value
        SysTick->VAL   = 0;

        // Enable SysTick IRQ and SysTick Timer leaving clock source as external
        SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

        // Function successful
        return E_NO_ERROR;
    }
}

/* ************************************************************************ */
void SYS_SysTick_Disable(void)
{
    SysTick->CTRL = 0;
}

/* ************************************************************************ */
int SYS_SysTick_Delay(uint32_t ticks)
{
    uint32_t cur_ticks, num_full, num_remain, previous_ticks, num_subtract, i;
    uint32_t reload, value, ctrl;  // save/restore variables

    if(ticks == 0)
        return E_BAD_PARAM;

    // If SysTick is not enabled we can take it for our delay
    if (!(SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)) {

        // Save current state in case it's disabled but already configured, restore at return.
        reload = SysTick->LOAD;
        value = SysTick->VAL;
        ctrl = SysTick->CTRL;

        // get the number of ticks less than max RELOAD.
        num_remain = ticks % SysTick_LOAD_RELOAD_Msk;

        /* if ticks is < Max SysTick Reload num_full will be 0, otherwise it will
           give us the number of max SysTicks cycles required */
        num_full = (ticks - 1) / SysTick_LOAD_RELOAD_Msk;

        // Do the required full systick countdowns
        if (num_full) {
            // load the max count value into systick
            SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
            // load the starting value
            SysTick->VAL = 0;
            // enable SysTick counter with SystemClock source internal, immediately forces LOAD register into VAL register
            SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
            // CountFlag will get set when VAL reaches zero
            for (i = num_full; i > 0; i--) {
                do {
                    cur_ticks = SysTick->CTRL;
                } while (!(cur_ticks & SysTick_CTRL_COUNTFLAG_Msk));
            }
            // Disable systick
            SysTick->CTRL = 0;
        }
        // Now handle the remainder of ticks
        if (num_remain) {
            SysTick->LOAD = num_remain;
            SysTick->VAL = 0;
            SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
            // wait for countflag to get set
            do {
                cur_ticks = SysTick->CTRL;
            } while (!(cur_ticks & SysTick_CTRL_COUNTFLAG_Msk));
            // Disable systick
            SysTick->CTRL = 0;
        }

        // restore original state of SysTick and return
        SysTick->LOAD = reload;
        SysTick->VAL =  value;
        SysTick->CTRL = ctrl;

        return E_NO_ERROR;

    } else { /* SysTick is enabled
           When SysTick is enabled count flag can not be used
           and the reload can not be changed.
           Do not read the CTRL register -> clears count flag */

        // Get the reload value for wrap/reload case
        reload = SysTick->LOAD;

        // Read the starting systick value
        previous_ticks = SysTick->VAL;

        do {
            // get current SysTick value
            cur_ticks = SysTick->VAL;
            // Check for wrap/reload of timer countval
            if (cur_ticks > previous_ticks) {
                // subtract count to 0 (previous_ticks) and wrap (reload value - cur_ticks)
                num_subtract = (previous_ticks + (reload - cur_ticks));
            } else { /* standard case (no wrap)
                        subtract off the number of ticks since last pass */
                num_subtract = (previous_ticks - cur_ticks);
            }
            // check to see if we are done.
            if (num_subtract >= ticks)
                return E_NO_ERROR;
            else
                ticks -= num_subtract;
            // cur_ticks becomes previous_ticks for next timer read.
            previous_ticks = cur_ticks;
        } while (ticks > 0);
        // Should not ever be reached
        return E_NO_ERROR;
    }
}

/* ************************************************************************ */
void SYS_SysTick_DelayUs(uint32_t us)
{
    SYS_SysTick_Delay((uint32_t)(((uint64_t)SYS_SysTick_GetFreq() * us) / 1000000));
}

/* ************************************************************************ */
int SYS_WDT_Init(mxc_wdt_regs_t* wdt, const sys_cfg_wdt_t* sys_cfg)
{
    return E_NO_ERROR;
}
/**@} end of ingroup MXC_sys*/
