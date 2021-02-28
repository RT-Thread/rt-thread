/**
 * @file       system_max32660.c
 * @brief      System-level initialization implementation file
 */

/*******************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
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
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 ******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "max32660.h"
#include "gcr_regs.h"
#include "pwrseq_regs.h"
#include "tmr_regs.h"
#include "wdt_regs.h"
#include "mxc_sys.h"

extern void (* const __isr_vector[])(void);
uint32_t SystemCoreClock = HIRC96_FREQ;

__weak void SystemCoreClockUpdate(void)
{
    uint32_t base_freq, div, clk_src,ovr;

    // Get the clock source and frequency
    clk_src = (MXC_GCR->clkcn & MXC_F_GCR_CLKCN_CLKSEL);
    
    if (clk_src == MXC_S_GCR_CLKCN_CLKSEL_HFXIN) {
        base_freq = HFX_FREQ;
    } else {
	if (clk_src == MXC_S_GCR_CLKCN_CLKSEL_NANORING) {
	    base_freq = NANORING_FREQ;
	} else {
	    ovr = (MXC_PWRSEQ->lp_ctrl & MXC_F_PWRSEQ_LP_CTRL_OVR);
	    if (ovr == MXC_S_PWRSEQ_LP_CTRL_OVR_0_9V) {
		base_freq = HIRC96_FREQ/4;
	    } else {
		if (ovr == MXC_S_PWRSEQ_LP_CTRL_OVR_1_0V) {
		    base_freq = HIRC96_FREQ/2;
		} else {
		    base_freq = HIRC96_FREQ;
		}
	    }
	}
    }

    // Get the clock divider
    div = (MXC_GCR->clkcn & MXC_F_GCR_CLKCN_PSC) >> MXC_F_GCR_CLKCN_PSC_POS;

    SystemCoreClock = base_freq >> div;
}

/* This function is called before C runtime initialization and can be
 * implemented by the application for early initializations. If a value other
 * than '0' is returned, the C runtime initialization will be skipped.
 *
 * You may over-ride this function in your program by defining a custom
 *  PreInit(), but care should be taken to reproduce the initilization steps
 *  or a non-functional system may result.
 */
__weak int PreInit(void)
{
    /* Do nothing */
#if defined ( __CC_ARM )
    SystemInit();
#endif
    return 0;
}

/* This function can be implemented by the application to initialize the board */
__weak int Board_Init(void)
{
    /* Do nothing */
    return 0;
}

/* This function is called just before control is transferred to main().
 *
 * You may over-ride this function in your program by defining a custom
 *  SystemInit(), but care should be taken to reproduce the initialization
 *  steps or a non-functional system may result.
 */
__weak void SystemInit(void)
{
    /* Configure the interrupt controller to use the application vector table in */
    /* the application space */
    /* IAR & Keil must set vector table after all memory initialization. */
    SCB->VTOR = (unsigned long)__isr_vector;

    MXC_WDT0->ctrl &= ~MXC_F_WDT_CTRL_WDT_EN;  /* Turn off watchdog. Application can re-enable as needed. */

    /* Enable FPU on Cortex-M4, which occupies coprocessor slots 10 & 11 */
    /* Grant full access, per "Table B3-24 CPACR bit assignments". */
    /* DDI0403D "ARMv7-M Architecture Reference Manual" */
    SCB->CPACR |= SCB_CPACR_CP10_Msk | SCB_CPACR_CP11_Msk;
    __DSB();
    __ISB();

    /* Switch system clock to HIRC */
    SYS_Clock_Select(SYS_CLOCK_HIRC, MXC_TMR0);

    /* Disable clocks to peripherals by default to reduce power */
    SYS_ClockDisable(SYS_PERIPH_CLOCK_DMA);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_SPI17Y);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_SPIMSS);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_UART0);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_UART1);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_I2C0);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_T0);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_T1);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_T2);
    SYS_ClockDisable(SYS_PERIPH_CLOCK_I2C1);
    
    Board_Init();
}

//#if defined ( __CC_ARM )
///* Global variable initialization does not occur until post scatterload in Keil tools.*/

///* External function called after our post scatterload function implementation. */
//extern void $Super$$__main_after_scatterload(void);

///**
// * @brief   Initialization function for SystemCoreClock and Board_Init.
// * @details $Sub$$__main_after_scatterload is called during system startup in the Keil
// *          toolset. Global variable and static variable space must be set up by the compiler
// *          prior to using these memory spaces. Setting up the SystemCoreClock and Board_Init
// *          require global memory for variable storage and are called from this function in
// *          the Keil tool chain.
// */
//void $Sub$$__main_after_scatterload(void)
//{
//    SystemInit();
//    $Super$$__main_after_scatterload();
//}
//#endif /* __CC_ARM */
