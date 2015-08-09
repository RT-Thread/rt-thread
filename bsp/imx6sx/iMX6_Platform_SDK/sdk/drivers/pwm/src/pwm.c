/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "pwm/pwm_ifc.h"
#include "interrupt.h"
#include "iomux_config.h"
#include "registers/regspwm.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! Number of sample FIFO entries.
#define PWM_CNT_FIFO_SZ       (4)

//! IRQ id of pwm
#define PWM_IRQS(x) ( (x) == HW_PWM1 ? IMX_INT_PWM1 : (x) == HW_PWM2 ? IMX_INT_PWM2 : (x) == HW_PWM3 ? IMX_INT_PWM3 : (x) == HW_PWM4 ? IMX_INT_PWM4 : 0xFFFFFFFF)

struct pwm_interrupt_status pwm_int_test_end;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
int pwm_init(uint32_t instance, struct pwm_parms *pwm)
{
    int idx;

    // Disable PWM first 
    HW_PWM_PWMCR(instance).B.EN = 0;

    // Verify and set clock source 
    if ((pwm->clock < kPwmClockSourceIpg) || (pwm->clock > kPwmClockSourceCkil)) {
        printf("Invalid clock source selection.\n");
        return FALSE;
    }

    HW_PWM_PWMCR(instance).B.CLKSRC = pwm->clock;

    // Set FIFO watermark to 4 empty slots 
    HW_PWM_PWMCR(instance).B.FWM = 3;

    // Set prescale after checking its range.
    if (pwm->prescale - 1 >= (BM_PWM_PWMCR_PRESCALER >> BP_PWM_PWMCR_PRESCALER)) {
        printf("Invalid prescaler value.\n");
        return FALSE;
    }

    // 0 - divide by 1, 1 - divide by 2
    HW_PWM_PWMCR(instance).B.PRESCALER = pwm->prescale - 1;

    // Set active polarity: 0 set at rollover, 1 clear at rollover
    HW_PWM_PWMCR(instance).B.POUTC = pwm->active_pol;

    // Set period 
    HW_PWM_PWMPR(instance).B.PERIOD = pwm->period;

    // Set sample repeat
    HW_PWM_PWMCR(instance).B.REPEAT = pwm->repeat;

    // Write count to FIFO 
    if ((pwm->smp_cnt > PWM_CNT_FIFO_SZ) || (pwm->smp_cnt < 1)) {
        printf("Invalid number of samples.\n");
        return FALSE;
    }

    for (idx = 0; idx < pwm->smp_cnt; idx++) {
        HW_PWM_PWMSAR(instance).B.SAMPLE = pwm->sample[idx];
    }

    // Setup interrupt for FIFO empty
    if (pwm->interrupt == kPwmFifoEmptyIrq) {
	/* register FIFO Empty interrupt to end the output test */
	pwm_int_test_end.instance = instance;
	pwm_int_test_end.interrupt = pwm->interrupt;
	pwm_setup_interrupt(instance, pwm_isr_test_end, pwm->interrupt);
    }
    return TRUE;
}

void pwm_clear_int_status(uint32_t instance, uint32_t mask)
{
    // Convert mask from abstract constants to register bitmasks.
    uint32_t convertedMask = 0;
    if (mask & kPwmFifoEmptyIrq) {
        convertedMask |= BM_PWM_PWMSR_FE;
    }
    if (mask & kPwmRolloverIrq) {
        convertedMask |= BM_PWM_PWMSR_ROV;
    }
    if (mask & kPwmCompareIrq) {
        convertedMask |= BM_PWM_PWMSR_CMP;
    }
    // Clear status bits by writing 1s.
    HW_PWM_PWMSR_WR(instance, convertedMask);
}

void pwm_setup_interrupt(uint32_t instance, void (*irq_subroutine) (void), uint8_t mask)
{
    int irq_id = PWM_IRQS(instance);

    // Disable the IRQ first
    disable_interrupt(irq_id, CPU_0);

    // Clear status register
    HW_PWM_PWMSR_WR(instance,
                    BM_PWM_PWMSR_FE | BM_PWM_PWMSR_ROV | BM_PWM_PWMSR_CMP | BM_PWM_PWMSR_FWE);

    // Register the IRQ sub-routine
    register_interrupt_routine(irq_id, irq_subroutine);

    // Enable the IRQ at ARM core level
    enable_interrupt(irq_id, CPU_0, 0);

    // Enable interrupt to status
    HW_PWM_PWMIR(instance).B.FIE = ((mask & kPwmFifoEmptyIrq) != 0);
    HW_PWM_PWMIR(instance).B.RIE = ((mask & kPwmRolloverIrq) != 0);
    HW_PWM_PWMIR(instance).B.CIE = ((mask & kPwmCompareIrq) != 0);
}

void pwm_free_interrupt(uint32_t instance)
{
    int irq_id = IMX_INT_PWM1 + instance - 1;

    // Disable the IRQ at ARM core level
    disable_interrupt(irq_id, CPU_0);

    // Clear all interrupt enables.
    HW_PWM_PWMIR_WR(instance, 0);
}

void pwm_isr_test_end(void)
{
    // Clear Interrupt status
    pwm_clear_int_status(pwm_int_test_end.instance, pwm_int_test_end.interrupt);

    // Set PWM output end flag
    g_pwm_test_end = TRUE;
}

void pwm_enable(uint32_t instance)
{
    HW_PWM_PWMCR(instance).B.EN = 1;
}

void pwm_disable(uint32_t instance)
{
    // Disable PWM interrupt
    pwm_free_interrupt(instance);

    HW_PWM_PWMCR(instance).B.EN = 0;
}

int pwm_get_clock_freq(uint32_t clock)
{
    int freq;
    switch (clock) {
	case kPwmClockSourceIpg:
	    freq = get_main_clock(IPG_CLK);
	    break;
	case kPwmClockSourceCkih:
	    /* Extern High Frequency: CKIH:
	     * XTALOSC 24MHz*/
	    freq = 24000000;
	    break;
	case kPwmClockSourceCkil:
	    /* Extern Low Frequency: CKIH:
	     * XTALOSC 32kHz or 32.768kHz
	     * on current all mx6dq or mx6sl evk board, are 32.768KHz */
	    freq = 32768;
	    break;
	default:
	    freq = 0;
	    break;
    }

    return freq;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
