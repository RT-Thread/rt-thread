/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

#include <stdio.h>
#include "sdk.h"
#include "pwm/pwm_ifc.h"
#include "iomux_config.h"

#define INVALID_INT	0xFFFFFFFF
uint32_t g_pwm_test_end;

static uint32_t pwm_get_valid_int(uint32_t low, uint32_t high)
{
    uint32_t get_value = 0;
    int32_t retv = TRUE;

    while (1) {
        get_value = read_int();
        if (retv == TRUE) {
            if (get_value >= low && get_value <= high)
                break;
        }
        printf("!Invalid input! Please input intergers bwteen (%d - %d): \n", low, high);
    }
    return get_value;
}

int32_t pwm_output_test(void)
{
    uint16_t sample[3] = { 4, 8, 16 };
    struct pwm_parms pwm;
    uint32_t instance = 1;
    int32_t retv = TRUE;

    printf("Please select the clock you want to use, enter 'return' key to set\n");
    printf
        ("\t%d - Global Functional Clock: \t\t%dHz\n"
         "\t%d - High Frequency Clock or CKIH: \t%dHz\n"
         "\t%d - Low Reference Clock (32KHz): \t%dHz\n",
         kPwmClockSourceIpg, pwm_get_clock_freq(kPwmClockSourceIpg),
         kPwmClockSourceCkih, pwm_get_clock_freq(kPwmClockSourceCkih),
         kPwmClockSourceCkil, pwm_get_clock_freq(kPwmClockSourceCkil));
    pwm.clock = pwm_get_valid_int(kPwmClockSourceIpg, kPwmClockSourceCkil);
    //pwm.freq = kPwmClockSourceCkil;

    printf("Please input the prescaler you want to set, enter 'return' key to set: \n");
    pwm.prescale = pwm_get_valid_int(1, 4096);

    printf("Please input the period you want to set, enter 'return' key to set: \n");
    pwm.period = pwm_get_valid_int(0, 0xFFFF - 1);

    printf("Please input number of times each sample repeat, enter 'return' key to set: \n");
    printf
        ("\t0 - sample once\n\t1 - sample twice\n\t2 - sample four times\n\t3 - sample eight times\n");
    pwm.repeat = pwm_get_valid_int(0, 3);

    printf
        ("Please specify active polarity (0 - active low, 1 - active high), enter 'return' key to set: \n");
    pwm.active_pol = pwm_get_valid_int(0, 1);

    printf("\nConfirm your PWM settings\n"
           "\tclock\t\t- %dHz\n"
           "\tprescale\t- %d\n"
           "\tperiod\t\t- %d\n"
           "\trepeat\t\t- %d times per sample\n"
           "\tpolarity\t- %s\n\n",
           pwm_get_clock_freq(pwm.clock), pwm.prescale, pwm.period,
           1 << pwm.repeat, pwm.active_pol == 0 ? "active low" : "active high");

    pwm.sample = sample;
    pwm.smp_cnt = 3;
    pwm.interrupt = kPwmFifoEmptyIrq;
    g_pwm_test_end = FALSE;

    // Configure pins.
    pwm_iomux_config(instance);

    // Initialize PWM module 
    retv = pwm_init(instance, &pwm);
    if (retv == FALSE) {
        printf("PWM init failed.\n");
        return retv;
    }
    printf("PWM output start.\n");

    // Enable PWM output 
    pwm_enable(instance);

    // Wait until FIFO empty 
    while (g_pwm_test_end == FALSE) ;

    // Disable PWM output 
    pwm_disable(instance);

    printf("PWM output end.\n");

    return retv;
}
