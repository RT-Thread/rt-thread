/*!
    \file  gd32vf103_rtc.c
    \brief RTC driver
    
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

#include "gd32vf103_rtc.h"

/* RTC register high / low bits mask */
#define RTC_HIGH_BITS_MASK         ((uint32_t)0x000F0000U)  /* RTC high bits mask */
#define RTC_LOW_BITS_MASK          ((uint32_t)0x0000FFFFU)  /* RTC low bits mask */

/* RTC register high bits offset */
#define RTC_HIGH_BITS_OFFSET       ((uint32_t)16U)

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
    \brief      set RTC counter value
    \param[in]  cnt: RTC counter value
    \param[out] none
    \retval     none
*/
void rtc_counter_set(uint32_t cnt)
{
    rtc_configuration_mode_enter();
    /* set the RTC counter high bits */
    RTC_CNTH = (cnt >> RTC_HIGH_BITS_OFFSET);
    /* set the RTC counter low bits */
    RTC_CNTL = (cnt & RTC_LOW_BITS_MASK);
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
    RTC_PSCH = ((psc & RTC_HIGH_BITS_MASK) >> RTC_HIGH_BITS_OFFSET);
    /* set the RTC prescaler low bits */
    RTC_PSCL = (psc & RTC_LOW_BITS_MASK);
    rtc_configuration_mode_exit();
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
    while(RESET == (RTC_CTL & RTC_CTL_LWOFF)){
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
    while(RESET == (RTC_CTL & RTC_CTL_RSYNF)){
    }
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
    RTC_ALRMH = (alarm >> RTC_HIGH_BITS_OFFSET);
    /* set the alarm low bits */
    RTC_ALRML = (alarm & RTC_LOW_BITS_MASK);
    rtc_configuration_mode_exit();
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
    temp |= (RTC_CNTH << RTC_HIGH_BITS_OFFSET);
    return temp;
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
    
    temp = ((RTC_DIVH & RTC_DIVH_DIV) << RTC_HIGH_BITS_OFFSET);
    temp |= RTC_DIVL;
    return temp;
}

/*!
    \brief      get RTC flag status 
    \param[in]  flag: specify which flag status to get
                only one parameter can be selected which is shown as below:
      \arg        RTC_FLAG_SECOND: second interrupt flag
      \arg        RTC_FLAG_ALARM: alarm interrupt flag
      \arg        RTC_FLAG_OVERFLOW: overflow interrupt flag
      \arg        RTC_FLAG_RSYN: registers synchronized flag
      \arg        RTC_FLAG_LWOF: last write operation finished flag
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
                one or more parameters can be selected which are shown as below:
      \arg        RTC_FLAG_SECOND: second interrupt flag
      \arg        RTC_FLAG_ALARM: alarm interrupt flag
      \arg        RTC_FLAG_OVERFLOW: overflow interrupt flag
      \arg        RTC_FLAG_RSYN: registers synchronized flag
    \param[out] none
    \retval     none
*/
void rtc_flag_clear(uint32_t flag)
{
    /* clear RTC flag */
    RTC_CTL &= ~flag;
}

/*!
    \brief      get RTC interrupt flag status 
    \param[in]  flag: specify which flag status to get
                only one parameter can be selected which is shown as below:
      \arg        RTC_INT_FLAG_SECOND: second interrupt flag
      \arg        RTC_INT_FLAG_ALARM: alarm interrupt flag
      \arg        RTC_INT_FLAG_OVERFLOW: overflow interrupt flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus rtc_interrupt_flag_get(uint32_t flag)
{
    if(RESET != (RTC_CTL & flag)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear RTC interrupt flag status
    \param[in]  flag: specify which flag status to clear
                one or more parameters can be selected which are shown as below:
      \arg        RTC_INT_FLAG_SECOND: second interrupt flag
      \arg        RTC_INT_FLAG_ALARM: alarm interrupt flag
      \arg        RTC_INT_FLAG_OVERFLOW: overflow interrupt flag
    \param[out] none
    \retval     none
*/
void rtc_interrupt_flag_clear(uint32_t flag)
{
    /* clear RTC interrupt flag */
    RTC_CTL &= ~flag;
}

/*!
    \brief      enable RTC interrupt
    \param[in]  interrupt: specify which interrupt to enbale
                one or more parameters can be selected which are shown as below:
      \arg        RTC_INT_SECOND: second interrupt
      \arg        RTC_INT_ALARM: alarm interrupt
      \arg        RTC_INT_OVERFLOW: overflow interrupt
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
                one or more parameters can be selected which are shown as below:
      \arg        RTC_INT_SECOND: second interrupt
      \arg        RTC_INT_ALARM: alarm interrupt
      \arg        RTC_INT_OVERFLOW: overflow interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_disable(uint32_t interrupt)
{
    RTC_INTEN &= ~interrupt;
}
