/*!
    \file  gd32vf103_usb_hw.c
    \brief this file implements the board support package for the USB host library

    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/
#include "gd32vf103_libopt.h"
#include "drv_usb_hw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TIM_MSEC_DELAY                          0x01
#define TIM_USEC_DELAY                          0x02

#define HOST_POWERSW_PORT_RCC                   RCU_GPIOD
#define HOST_POWERSW_PORT                       GPIOD
#define HOST_POWERSW_VBUS                       GPIO_PIN_13

__IO uint32_t delay_time = 0;
__IO uint32_t usbfs_prescaler = 0;
__IO uint32_t timer_prescaler = 5;

static void hwp_time_set         (uint8_t unit);
static void hwp_delay            (uint32_t ntime, uint8_t unit);

/*!
    \brief      configure USB clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usb_rcu_config (void)
{
    uint32_t system_clock = rcu_clock_freq_get(CK_SYS);
  
    if (system_clock == 48000000) {
        usbfs_prescaler = RCU_CKUSB_CKPLL_DIV1;
        timer_prescaler = 3;
    } else if (system_clock == 72000000) {
        usbfs_prescaler = RCU_CKUSB_CKPLL_DIV1_5;
        timer_prescaler = 5;
    } else if (system_clock == 96000000) {
        usbfs_prescaler = RCU_CKUSB_CKPLL_DIV2;
        timer_prescaler = 7;
    } else {
        /*  reserved  */
    }

    rcu_usb_clock_config(usbfs_prescaler);
    rcu_periph_clock_enable(RCU_USBFS);
}

/*!
    \brief      configure USB global interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usb_intr_config (void)
{
    ECLIC_SetLevelIRQ(USBFS_IRQn,1);
    ECLIC_SetPriorityIRQ(USBFS_IRQn,0);
    ECLIC_EnableIRQ(USBFS_IRQn);
#ifdef USB_OTG_FS_LOW_PWR_MGMT_SUPPORT

    /* enable the power module clock */
    rcu_periph_clock_enable(RCU_PMU);

    /* USB wakeup EXTI line configuration */
    exti_interrupt_flag_clear(EXTI_18);
    exti_init(EXTI_18, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    exti_interrupt_enable(EXTI_18);

    ECLIC_SetLevelIRQ(USBFS_WKUP_IRQn,3);
    ECLIC_SetPriorityIRQ(USBFS_WKUP_IRQn,0);
    ECLIC_EnableIRQ(USBFS_WKUP_IRQn);

#endif /* USBHS_LOW_PWR_MGMT_SUPPORT */
}

/*!
    \brief      drives the VBUS signal through gpio
    \param[in]  state: VBUS states
    \param[out] none
    \retval     none
*/
void usb_vbus_drive (uint8_t state)
{
    if (0 == state)
    { 
        /* DISABLE is needed on output of the Power Switch */
        gpio_bit_reset(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
    }
    else
    {
        /*ENABLE the Power Switch by driving the Enable LOW */
        gpio_bit_set(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
    }
}

/*!
    \brief      configures the GPIO for the VBUS
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usb_vbus_config (void)
{
    rcu_periph_clock_enable(HOST_POWERSW_PORT_RCC);

    gpio_init(HOST_POWERSW_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, HOST_POWERSW_VBUS);

    /* by default, disable is needed on output of the power switch */
    gpio_bit_set(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);

    /* Delay is need for stabilising the Vbus Low in Reset Condition,
     * when Vbus=1 and Reset-button is pressed by user 
     */
    //usb_mdelay (1);
    usb_mdelay (2);
}

/*!
    \brief      initializes delay unit using Timer2
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usb_timer_init (void)
{
    rcu_periph_clock_enable(RCU_TIMER2);
    
    //eclic_irq_enable(TIMER2_IRQn, 2, 0);
    /*ECLIC_Register_IRQn(TIMER2_IRQn, ECLIC_VECTOR_INTERRUPT,
                                    ECLIC_LEVEL_TRIGGER, 2, 0,
                                    TIMER2_IRQHandler);*/
}

/*!
    \brief      delay in micro seconds
    \param[in]  usec: value of delay required in micro seconds
    \param[out] none
    \retval     none
*/
void usb_udelay (const uint32_t usec)
{
    hwp_delay(usec, TIM_USEC_DELAY);
}

/*!
    \brief      delay in milli seconds
    \param[in]  msec: value of delay required in milli seconds
    \param[out] none
    \retval     none
*/
void usb_mdelay (const uint32_t msec)
{
    hwp_delay(msec, TIM_MSEC_DELAY);
}

/*!
    \brief      timer base IRQ
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usb_timer_irq (void)
{
    if (timer_interrupt_flag_get(TIMER2, TIMER_INT_UP) != RESET){
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);

        if (delay_time > 0x00U){
            delay_time--;
        } else {
            timer_disable(TIMER2);
        }
    }
}

/*!
    \brief      delay routine based on TIM2
    \param[in]  ntime: delay Time 
    \param[in]  unit: delay Time unit = mili sec / micro sec
    \param[out] none
    \retval     none
*/
static void hwp_delay(uint32_t ntime, uint8_t unit)
{
    delay_time = ntime;
    hwp_time_set(unit);

    while(delay_time != 0);

    timer_disable(TIMER2);
}

/*!
    \brief      configures TIM2 for delay routine based on TIM2
    \param[in]  unit: msec /usec
    \param[out] none
    \retval     none
*/
static void hwp_time_set(uint8_t unit)
{
    timer_parameter_struct  timer_basestructure;

    timer_disable(TIMER2);
    timer_interrupt_disable(TIMER2, TIMER_INT_UP);

    if (unit == TIM_USEC_DELAY) {
        timer_basestructure.period = 11;
    } else if(unit == TIM_MSEC_DELAY) {
        timer_basestructure.period = 11999;
    } else {
        /* no operation */
    }

    timer_basestructure.prescaler         = timer_prescaler;
    timer_basestructure.alignedmode       = TIMER_COUNTER_EDGE;
    timer_basestructure.counterdirection  = TIMER_COUNTER_UP;
    timer_basestructure.clockdivision     = TIMER_CKDIV_DIV1;
    timer_basestructure.repetitioncounter = 0;

    timer_init(TIMER2, &timer_basestructure);

    timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);

    timer_auto_reload_shadow_enable(TIMER2);

    /* timer2 interrupt enable */
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);

    /* timer2 enable counter */
    timer_enable(TIMER2);
}

