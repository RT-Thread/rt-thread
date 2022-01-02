/*!
    \file    gd32f30x_rtc.c
    \brief   RTC driver

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
    \version 2020-09-30, V2.1.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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


#include "gd32f30x_rtc.h"

/*!
    \brief      enable RTC interrupt
    \param[in]  interrupt: specify which interrupt to enbale
          \arg    RTC_INT_SECOND: second interrupt
          \arg    RTC_INT_ALARM: alarm interrupt
          \arg    RTC_INT_OVERFLOW: overflow interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_enable(uint32_t interrupt)
{
    RTC_INTEN |= interrupt;
}

/*!
    \brief      disable RTC interrupt
    \param[in]  interrupt: specify which interrupt to disbale
          \arg    RTC_INT_SECOND: second interrupt
          \arg    RTC_INT_ALARM: alarm interrupt
          \arg    RTC_INT_OVERFLOW: overflow interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_disable(uint32_t interrupt)
{
    RTC_INTEN &= ~interrupt;
}

/*!
    \brief      enter RTC configuration mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_configuration_mode_enter(void)
{
    RTC_CTL |= RTC_CTL_CMF;
}

/*!
    \brief      exit RTC configuration mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_configuration_mode_exit(void)
{
    RTC_CTL &= ~RTC_CTL_CMF;
}

/*!
    \brief      wait RTC last write operation finished flag set
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_lwoff_wait(void)
{
     /* loop until LWOFF flag is set */
    while (RESET == (RTC_CTL & RTC_CTL_LWOFF)){
    }
}

/*!
    \brief      wait RTC registers synchronized flag set
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_register_sync_wait(void)
{
     /* clear RSYNF flag */
    RTC_CTL &= ~RTC_CTL_RSYNF;
    /* loop until RSYNF flag is set */
    while (RESET == (RTC_CTL & RTC_CTL_RSYNF)){
    }
}

/*!
    \brief      get RTC counter value
    \param[in]  none
    \param[out] none
    \retval     RTC counter value
*/
uint32_t rtc_counter_get(void)
{
    uint32_t temp = 0x0U;
    temp = RTC_CNTL;
    temp |= (RTC_CNTH << 16);
    return temp;
}

/*!
    \brief      set RTC counter value
    \param[in]  cnt: RTC counter value
    \param[out] none
    \retval     none
*/
void rtc_counter_set(uint32_t cnt)
{
    rtc_configuration_mode_enter();
    /* set the RTC counter high bits */
    RTC_CNTH = cnt >> 16;
    /* set the RTC counter low bits */
    RTC_CNTL = (cnt & RTC_LOW_VALUE);
    rtc_configuration_mode_exit();
}

/*!
    \brief      set RTC prescaler value
    \param[in]  psc: RTC prescaler value
    \param[out] none
    \retval     none
*/
void rtc_prescaler_set(uint32_t psc)
{
    rtc_configuration_mode_enter();
    /* set the RTC prescaler high bits */
    RTC_PSCH = (psc & RTC_HIGH_VALUE) >> 16;
    /* set the RTC prescaler low bits */
    RTC_PSCL = (psc & RTC_LOW_VALUE);
    rtc_configuration_mode_exit();
}

/*!
    \brief      set RTC alarm value
    \param[in]  alarm: RTC alarm value
    \param[out] none
    \retval     none
*/
void rtc_alarm_config(uint32_t alarm)
{
    rtc_configuration_mode_enter();
    /* set the alarm high bits */
    RTC_ALRMH = alarm >> 16;
    /* set the alarm low bits */
    RTC_ALRML = (alarm & RTC_LOW_VALUE);
    rtc_configuration_mode_exit();
}

/*!
    \brief      get RTC divider value
    \param[in]  none
    \param[out] none
    \retval     RTC divider value
*/
uint32_t rtc_divider_get(void)
{
    uint32_t temp = 0x00U;
    temp = (RTC_DIVH & RTC_DIVH_DIV) << 16;
    temp |= RTC_DIVL;
    return temp;
}

/*!
    \brief      get RTC flag status
    \param[in]  flag: specify which flag status to get
          \arg    RTC_FLAG_SECOND: second interrupt flag
          \arg    RTC_FLAG_ALARM: alarm interrupt flag
          \arg    RTC_FLAG_OVERFLOW: overflow interrupt flag
          \arg    RTC_FLAG_RSYN: registers synchronized flag
          \arg    RTC_FLAG_LWOF: last write operation finished flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus rtc_flag_get(uint32_t flag)
{
    if(RESET != (RTC_CTL & flag)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear RTC flag status
    \param[in]  flag: specify which flag status to clear
          \arg    RTC_FLAG_SECOND: second interrupt flag
          \arg    RTC_FLAG_ALARM: alarm interrupt flag
          \arg    RTC_FLAG_OVERFLOW: overflow interrupt flag
          \arg    RTC_FLAG_RSYN: registers synchronized flag
    \param[out] none
    \retval     none
*/
void rtc_flag_clear(uint32_t flag)
{
    /* clear RTC flag */
    RTC_CTL &= ~flag;
}

