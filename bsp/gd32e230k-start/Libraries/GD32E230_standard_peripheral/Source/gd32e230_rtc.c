/*!
    \file    gd32e230_rtc.c
    \brief   RTC driver
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "gd32e230_rtc.h"

/*!
    \brief      reset most of the RTC registers
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_deinit(void)
{
    ErrStatus error_status = ERROR;

    /* RTC_TAMP register is not under write protection */
    RTC_TAMP = RTC_REGISTER_RESET;

    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    /* reset RTC_CTL register, this can be done without the init mode */
    RTC_CTL &= RTC_REGISTER_RESET;

    /* enter init mode */
    error_status = rtc_init_mode_enter();

    if(ERROR != error_status){
        /* before reset RTC_TIME and RTC_DATE, BPSHAD bit in RTC_CTL should be reset as the condition.
           in order to read calendar from shadow register, not the real registers being reset */
        RTC_TIME = RTC_REGISTER_RESET;
        RTC_DATE = RTC_DATE_RESET;

        RTC_PSC = RTC_PSC_RESET;

        /* reset RTC_STAT register, also exit init mode.
           at the same time, RTC_STAT_SOPF bit is reset, as the condition to reset RTC_SHIFTCTL register later */
        RTC_STAT = RTC_STAT_RESET;
      
        /* to write RTC_ALRM0SS register, ALRM0EN bit in RTC_CTL register should be reset as the condition */
        RTC_ALRM0TD = RTC_REGISTER_RESET;
        RTC_ALRM0SS = RTC_REGISTER_RESET;

        /* reset RTC_SHIFTCTL and RTC_HRFC register, this can be done without the init mode */
        RTC_SHIFTCTL = RTC_REGISTER_RESET;
        RTC_HRFC = RTC_REGISTER_RESET;

        error_status = rtc_register_sync_wait();  
    }

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}

/*!
    \brief      initialize RTC registers
    \param[in]  rtc_initpara_struct: pointer to a rtc_parameter_struct structure which contains 
                parameters for initialization of the rtc peripheral
                members of the structure and the member values are shown as below:
                  rtc_year: 0x0 - 0x99(BCD format)
                  rtc_month: RTC_JAN, RTC_FEB, RTC_MAR, RTC_APR, RTC_MAY, RTC_JUN,
                             RTC_JUL, RTC_AUG, RTC_SEP, RTC_OCT, RTC_NOV, RTC_DEC
                  rtc_date: 0x1 - 0x31(BCD format)
                  rtc_day_of_week: RTC_MONDAY, RTC_TUESDAY, RTC_WEDSDAY, RTC_THURSDAY
                                   RTC_FRIDAY, RTC_SATURDAY, RTC_SUNDAY
                  rtc_hour: 0x0 - 0x12(BCD format) or 0x0 - 0x23(BCD format) depending on the rtc_display_format chose
                  rtc_minute: 0x0 - 0x59(BCD format)
                  rtc_second: 0x0 - 0x59(BCD format)
                  rtc_factor_asyn: 0x0 - 0x7F
                  rtc_factor_syn: 0x0 - 0x7FFF
                  rtc_am_pm: RTC_AM, RTC_PM
                  rtc_display_format: RTC_24HOUR, RTC_12HOUR
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_init(rtc_parameter_struct* rtc_initpara_struct)
{
    ErrStatus error_status = ERROR;
    uint32_t reg_time = 0x00U, reg_date = 0x00U;

    reg_date = (DATE_YR(rtc_initpara_struct->rtc_year) | \
                DATE_DOW(rtc_initpara_struct->rtc_day_of_week) | \
                DATE_MON(rtc_initpara_struct->rtc_month) | \
                DATE_DAY(rtc_initpara_struct->rtc_date)); 
    
    reg_time = (rtc_initpara_struct->rtc_am_pm| \
                TIME_HR(rtc_initpara_struct->rtc_hour) | \
                TIME_MN(rtc_initpara_struct->rtc_minute) | \
                TIME_SC(rtc_initpara_struct->rtc_second)); 
              
    /* 1st: disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    /* 2nd: enter init mode */
    error_status = rtc_init_mode_enter();

    if(ERROR != error_status){
        RTC_PSC = (uint32_t)(PSC_FACTOR_A(rtc_initpara_struct->rtc_factor_asyn)| \
                                  PSC_FACTOR_S(rtc_initpara_struct->rtc_factor_syn));

        RTC_TIME = (uint32_t)reg_time;
        RTC_DATE = (uint32_t)reg_date;

        RTC_CTL &= (uint32_t)(~RTC_CTL_CS);
        RTC_CTL |=  rtc_initpara_struct->rtc_display_format;
        
        /* 3rd: exit init mode */
        rtc_init_mode_exit();
        
        /* 4th: wait the RSYNF flag to set */
        error_status = rtc_register_sync_wait();
    }

    /* 5th: enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}

/*!
    \brief      enter RTC init mode
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_init_mode_enter(void)
{
    uint32_t time_index = RTC_INITM_TIMEOUT;
    uint32_t flag_status = RESET;
    ErrStatus error_status = ERROR;

    /* check whether it has been in init mode */
    if((uint32_t)RESET == (RTC_STAT & RTC_STAT_INITF)){
        RTC_STAT |= RTC_STAT_INITM;
        
        /* wait until the INITF flag to be set */
        do{
           flag_status = RTC_STAT & RTC_STAT_INITF;
        }while((--time_index > 0x00U) && ((uint32_t)RESET == flag_status));

        if((uint32_t)RESET != flag_status){
            error_status = SUCCESS;
        }
    }else{
        error_status = SUCCESS;
    }
    return error_status;
}

/*!
    \brief      exit RTC init mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_init_mode_exit(void)
{
    RTC_STAT &= (uint32_t)(~RTC_STAT_INITM);
}

/*!
    \brief      wait until RTC_TIME and RTC_DATE registers are synchronized with APB clock, and the shadow 
                registers are updated
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_register_sync_wait(void)
{
    volatile uint32_t time_index = RTC_RSYNF_TIMEOUT;
    uint32_t flag_status = RESET;
    ErrStatus error_status = ERROR;

    if((uint32_t)RESET == (RTC_CTL & RTC_CTL_BPSHAD)){
        /* disable the write protection */
        RTC_WPK = RTC_UNLOCK_KEY1;
        RTC_WPK = RTC_UNLOCK_KEY2;

        /* firstly clear RSYNF flag */
        RTC_STAT &= (uint32_t)(~RTC_STAT_RSYNF);

        /* wait until RSYNF flag to be set */
        do{
            flag_status = RTC_STAT & RTC_STAT_RSYNF;
        }while((--time_index > 0x00U) && ((uint32_t)RESET == flag_status));

        if((uint32_t)RESET != flag_status){
            error_status = SUCCESS;
        }
        
        /* enable the write protection */
        RTC_WPK = RTC_LOCK_KEY;
    }else{ 
        error_status = SUCCESS;
    }

    return error_status;
}

/*!
    \brief      get current time and date
    \param[in]  none
    \param[out] rtc_initpara_struct: pointer to a rtc_parameter_struct structure which contains 
                parameters for initialization of the rtc peripheral
                members of the structure and the member values are shown as below:
                  rtc_year: 0x0 - 0x99(BCD format)
                  rtc_month: RTC_JAN, RTC_FEB, RTC_MAR, RTC_APR, RTC_MAY, RTC_JUN,
                             RTC_JUL, RTC_AUG, RTC_SEP, RTC_OCT, RTC_NOV, RTC_DEC
                  rtc_date: 0x1 - 0x31(BCD format)
                  rtc_day_of_week: RTC_MONDAY, RTC_TUESDAY, RTC_WEDSDAY, RTC_THURSDAY
                                   RTC_FRIDAY, RTC_SATURDAY, RTC_SUNDAY
                  rtc_hour: 0x0 - 0x12(BCD format) or 0x0 - 0x23(BCD format) depending on the rtc_display_format chose
                  rtc_minute: 0x0 - 0x59(BCD format)
                  rtc_second: 0x0 - 0x59(BCD format)
                  rtc_factor_asyn: 0x0 - 0x7F
                  rtc_factor_syn: 0x0 - 0x7FFF
                  rtc_am_pm: RTC_AM, RTC_PM
                  rtc_display_format: RTC_24HOUR, RTC_12HOUR
    \retval     none
*/
void rtc_current_time_get(rtc_parameter_struct* rtc_initpara_struct)
{
    uint32_t temp_tr = 0x00U, temp_dr = 0x00U, temp_pscr = 0x00U, temp_ctlr = 0x00U;

    temp_tr = (uint32_t)RTC_TIME;   
    temp_dr = (uint32_t)RTC_DATE;
    temp_pscr = (uint32_t)RTC_PSC;
    temp_ctlr = (uint32_t)RTC_CTL;
  
    /* get current time and construct rtc_parameter_struct structure */
    rtc_initpara_struct->rtc_year = (uint8_t)GET_DATE_YR(temp_dr);
    rtc_initpara_struct->rtc_month = (uint8_t)GET_DATE_MON(temp_dr);
    rtc_initpara_struct->rtc_date = (uint8_t)GET_DATE_DAY(temp_dr);
    rtc_initpara_struct->rtc_day_of_week = (uint8_t)GET_DATE_DOW(temp_dr);  
    rtc_initpara_struct->rtc_hour = (uint8_t)GET_TIME_HR(temp_tr);
    rtc_initpara_struct->rtc_minute = (uint8_t)GET_TIME_MN(temp_tr);
    rtc_initpara_struct->rtc_second = (uint8_t)GET_TIME_SC(temp_tr);
    rtc_initpara_struct->rtc_factor_asyn = (uint16_t)GET_PSC_FACTOR_A(temp_pscr);
    rtc_initpara_struct->rtc_factor_syn = (uint16_t)GET_PSC_FACTOR_S(temp_pscr);
    rtc_initpara_struct->rtc_am_pm = (uint32_t)(temp_pscr & RTC_TIME_PM); 
    rtc_initpara_struct->rtc_display_format = (uint32_t)(temp_ctlr & RTC_CTL_CS);
}

/*!
    \brief      get current subsecond value
    \param[in]  none
    \param[out] none
    \retval     current subsecond value
*/
uint32_t rtc_subsecond_get(void)
{
    uint32_t reg = 0x00U;
    /* if BPSHAD bit is reset, reading RTC_SS will lock RTC_TIME and RTC_DATE automatically */
    reg = (uint32_t)RTC_SS;
    /* read RTC_DATE to unlock the 3 shadow registers */
    (void) (RTC_DATE);

    return reg;
}

/*!
    \brief      configure RTC alarm
    \param[in]  rtc_alarm_time: pointer to a rtc_alarm_struct structure which contains 
                parameters for RTC alarm configuration
                members of the structure and the member values are shown as below:
                  rtc_alarm_mask: RTC_ALARM_NONE_MASK, RTC_ALARM_DATE_MASK, RTC_ALARM_HOUR_MASK
                                  RTC_ALARM_MINUTE_MASK, RTC_ALARM_SECOND_MASK, RTC_ALARM_ALL_MASK
                  rtc_weekday_or_date: RTC_ALARM_DATE_SELECTED, RTC_ALARM_WEEKDAY_SELECTED
                  rtc_alarm_day: 1) 0x1 - 0x31(BCD format) if RTC_ALARM_DATE_SELECTED is set
                                 2) RTC_MONDAY, RTC_TUESDAY, RTC_WEDSDAY, RTC_THURSDAY, RTC_FRIDAY,
                                    RTC_SATURDAY, RTC_SUNDAY if RTC_ALARM_WEEKDAY_SELECTED is set
                  rtc_alarm_hour: 0x0 - 0x12(BCD format) or 0x0 - 0x23(BCD format) depending on the rtc_display_format
                  rtc_alarm_minute: 0x0 - 0x59(BCD format)
                  rtc_alarm_second: 0x0 - 0x59(BCD format)
                  rtc_am_pm: RTC_AM, RTC_PM
    \param[out] none
    \retval     none
*/
void rtc_alarm_config(rtc_alarm_struct* rtc_alarm_time)
{
    uint32_t reg_alrm0td = 0x00U;

    reg_alrm0td = (rtc_alarm_time->rtc_alarm_mask | \
                 rtc_alarm_time->rtc_weekday_or_date | \
                 rtc_alarm_time->rtc_am_pm | \
                 ALRM0TD_DAY(rtc_alarm_time->rtc_alarm_day) | \
                 ALRM0TD_HR(rtc_alarm_time->rtc_alarm_hour) | \
                 ALRM0TD_MN(rtc_alarm_time->rtc_alarm_minute) | \
                 ALRM0TD_SC(rtc_alarm_time->rtc_alarm_second));

    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_ALRM0TD = (uint32_t)reg_alrm0td;

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      configure subsecond of RTC alarm
    \param[in]  mask_subsecond: alarm subsecond mask
                only one parameter can be selected which is shown as below:
      \arg        RTC_MASKSSC_0_14: mask alarm subsecond configuration
      \arg        RTC_MASKSSC_1_14: mask RTC_ALRM0SS_SSC[14:1], and RTC_ALRM0SS_SSC[0] is to be compared
      \arg        RTC_MASKSSC_2_14: mask RTC_ALRM0SS_SSC[14:2], and RTC_ALRM0SS_SSC[1:0] is to be compared
      \arg        RTC_MASKSSC_3_14: mask RTC_ALRM0SS_SSC[14:3], and RTC_ALRM0SS_SSC[2:0] is to be compared
      \arg        RTC_MASKSSC_4_14: mask RTC_ALRM0SS_SSC[14:4], and RTC_ALRM0SS_SSC[3:0] is to be compared
      \arg        RTC_MASKSSC_5_14: mask RTC_ALRM0SS_SSC[14:5], and RTC_ALRM0SS_SSC[4:0] is to be compared
      \arg        RTC_MASKSSC_6_14: mask RTC_ALRM0SS_SSC[14:6], and RTC_ALRM0SS_SSC[5:0] is to be compared
      \arg        RTC_MASKSSC_7_14: mask RTC_ALRM0SS_SSC[14:7], and RTC_ALRM0SS_SSC[6:0] is to be compared
      \arg        RTC_MASKSSC_8_14: mask RTC_ALRM0SS_SSC[14:8], and RTC_ALRM0SS_SSC[7:0] is to be compared
      \arg        RTC_MASKSSC_9_14: mask RTC_ALRM0SS_SSC[14:9], and RTC_ALRM0SS_SSC[8:0] is to be compared
      \arg        RTC_MASKSSC_10_14: mask RTC_ALRM0SS_SSC[14:10], and RTC_ALRM0SS_SSC[9:0] is to be compared
      \arg        RTC_MASKSSC_11_14: mask RTC_ALRM0SS_SSC[14:11], and RTC_ALRM0SS_SSC[10:0] is to be compared
      \arg        RTC_MASKSSC_12_14: mask RTC_ALRM0SS_SSC[14:12], and RTC_ALRM0SS_SSC[11:0] is to be compared
      \arg        RTC_MASKSSC_13_14: mask RTC_ALRM0SS_SSC[14:13], and RTC_ALRM0SS_SSC[12:0] is to be compared
      \arg        RTC_MASKSSC_14: mask RTC_ALRM0SS_SSC[14], and RTC_ALRM0SS_SSC[13:0] is to be compared
      \arg        RTC_MASKSSC_NONE: mask none, and RTC_ALRM0SS_SSC[14:0] is to be compared
    \param[in]  subsecond: alarm subsecond value(0x000 - 0x7FFF)
    \param[out] none
    \retval     none
*/
void rtc_alarm_subsecond_config(uint32_t mask_subsecond, uint32_t subsecond)
{
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;  

    RTC_ALRM0SS = mask_subsecond | subsecond;  

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      enable RTC alarm
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_alarm_enable(void)
{
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_CTL |= RTC_CTL_ALRM0EN;

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      disable RTC alarm
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_alarm_disable(void)
{
    volatile uint32_t time_index = RTC_ALRM0WF_TIMEOUT;
    ErrStatus error_status = ERROR;
    uint32_t flag_status = RESET;

    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
    
    /* clear the state of alarm */
    RTC_CTL &= (uint32_t)(~RTC_CTL_ALRM0EN);  
    
    /* wait until ALRM0WF flag to be set after the alarm is disabled */
    do{
        flag_status = RTC_STAT & RTC_STAT_ALRM0WF;
    }while((--time_index > 0x00U) && ((uint32_t)RESET == flag_status));
    
    if((uint32_t)RESET != flag_status){     
        error_status = SUCCESS;
    }

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}

/*!
    \brief      get RTC alarm
    \param[in]  none
    \param[out] rtc_alarm_time: pointer to a rtc_alarm_struct structure which contains 
                parameters for RTC alarm configuration
                members of the structure and the member values are shown as below:
                  rtc_alarm_mask: RTC_ALARM_NONE_MASK, RTC_ALARM_DATE_MASK, RTC_ALARM_HOUR_MASK
                                  RTC_ALARM_MINUTE_MASK, RTC_ALARM_SECOND_MASK, RTC_ALARM_ALL_MASK
                  rtc_weekday_or_date: RTC_ALARM_DATE_SELECTED, RTC_ALARM_WEEKDAY_SELECTED
                  rtc_alarm_day: 1) 0x1 - 0x31(BCD format) if RTC_ALARM_DATE_SELECTED is set
                                 2) RTC_MONDAY, RTC_TUESDAY, RTC_WEDSDAY, RTC_THURSDAY, RTC_FRIDAY,
                                    RTC_SATURDAY, RTC_SUNDAY if RTC_ALARM_WEEKDAY_SELECTED is set
                  rtc_alarm_hour: 0x0 - 0x12(BCD format) or 0x0 - 0x23(BCD format) depending on the rtc_display_format
                  rtc_alarm_minute: 0x0 - 0x59(BCD format)
                  rtc_alarm_second: 0x0 - 0x59(BCD format)
                  rtc_am_pm: RTC_AM, RTC_PM
    \retval     none
*/
void rtc_alarm_get(rtc_alarm_struct* rtc_alarm_time)
{
    uint32_t reg_alrm0td = 0x00U;

    /* get the value of RTC_ALRM0TD register */
    reg_alrm0td = RTC_ALRM0TD;

    /* get alarm parameters and construct the rtc_alarm_struct structure */
    rtc_alarm_time->rtc_alarm_mask = reg_alrm0td & RTC_ALARM_ALL_MASK; 
    rtc_alarm_time->rtc_am_pm = (uint32_t)(reg_alrm0td & RTC_ALRM0TD_PM);
    rtc_alarm_time->rtc_weekday_or_date = (uint32_t)(reg_alrm0td & RTC_ALRM0TD_DOWS);
    rtc_alarm_time->rtc_alarm_day = (uint8_t)GET_ALRM0TD_DAY(reg_alrm0td);
    rtc_alarm_time->rtc_alarm_hour = (uint8_t)GET_ALRM0TD_HR(reg_alrm0td);
    rtc_alarm_time->rtc_alarm_minute = (uint8_t)GET_ALRM0TD_MN(reg_alrm0td);
    rtc_alarm_time->rtc_alarm_second = (uint8_t)GET_ALRM0TD_SC(reg_alrm0td);  
}

/*!
    \brief      get RTC alarm subsecond
    \param[in]  none
    \param[out] none
    \retval     RTC alarm subsecond value
*/
uint32_t rtc_alarm_subsecond_get(void)
{
    return ((uint32_t)(RTC_ALRM0SS & RTC_ALRM0SS_SSC));
}

/*!
    \brief      enable RTC time-stamp
    \param[in]  edge: specify which edge to detect of time-stamp
                only one parameter can be selected which is shown as below:
      \arg        RTC_TIMESTAMP_RISING_EDGE: rising edge is valid event edge for timestamp event
      \arg        RTC_TIMESTAMP_FALLING_EDGE: falling edge is valid event edge for timestamp event
    \param[out] none
    \retval     none
*/
void rtc_timestamp_enable(uint32_t edge)
{
    uint32_t reg_ctl = 0x00U;

    /* clear the bits to be configured in RTC_CTL */
    reg_ctl = (uint32_t)(RTC_CTL & (uint32_t)(~(RTC_CTL_TSEG | RTC_CTL_TSEN)));

    /* new configuration */
    reg_ctl |= (uint32_t)(edge | RTC_CTL_TSEN);
   
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_CTL = (uint32_t)reg_ctl;

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      disable RTC time-stamp
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_timestamp_disable(void)
{
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
    
    /* clear the TSEN bit */
    RTC_CTL &= (uint32_t)(~ RTC_CTL_TSEN);

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      get RTC timestamp time and date
    \param[in]  none
    \param[out] rtc_timestamp: pointer to a rtc_timestamp_struct structure which contains 
                parameters for RTC time-stamp configuration
                members of the structure and the member values are shown as below:
                  rtc_timestamp_month: RTC_JAN, RTC_FEB, RTC_MAR, RTC_APR, RTC_MAY, RTC_JUN,
                                       RTC_JUL, RTC_AUG, RTC_SEP, RTC_OCT, RTC_NOV, RTC_DEC
                  rtc_timestamp_date: 0x1 - 0x31(BCD format)
                  rtc_timestamp_day: RTC_MONDAY, RTC_TUESDAY, RTC_WEDSDAY, RTC_THURSDAY, RTC_FRIDAY,
                                     RTC_SATURDAY, RTC_SUNDAY if RTC_ALARM_WEEKDAY_SELECTED is set
                  rtc_timestamp_hour: 0x0 - 0x12(BCD format) or 0x0 - 0x23(BCD format) depending on the rtc_display_format
                  rtc_timestamp_minute: 0x0 - 0x59(BCD format)
                  rtc_timestamp_second: 0x0 - 0x59(BCD format)
                  rtc_am_pm: RTC_AM, RTC_PM
    \retval     none
*/
void rtc_timestamp_get(rtc_timestamp_struct* rtc_timestamp)
{
    uint32_t temp_tts = 0x00U, temp_dts = 0x00U;

    /* get the value of time_stamp registers */
    temp_tts = (uint32_t)RTC_TTS;
    temp_dts = (uint32_t)RTC_DTS;
  
    /* get timestamp time and construct the rtc_timestamp_struct structure */
    rtc_timestamp->rtc_am_pm = (uint32_t)(temp_tts & RTC_TTS_PM);
    rtc_timestamp->rtc_timestamp_month = (uint8_t)GET_DTS_MON(temp_dts);
    rtc_timestamp->rtc_timestamp_date = (uint8_t)GET_DTS_DAY(temp_dts);
    rtc_timestamp->rtc_timestamp_day = (uint8_t)GET_DTS_DOW(temp_dts);
    rtc_timestamp->rtc_timestamp_hour = (uint8_t)GET_TTS_HR(temp_tts);
    rtc_timestamp->rtc_timestamp_minute = (uint8_t)GET_TTS_MN(temp_tts);
    rtc_timestamp->rtc_timestamp_second = (uint8_t)GET_TTS_SC(temp_tts);
}

/*!
    \brief      get RTC time-stamp subsecond
    \param[in]  none
    \param[out] none
    \retval     RTC time-stamp subsecond value
*/
uint32_t rtc_timestamp_subsecond_get(void)
{
    return ((uint32_t)RTC_SSTS);
}

/*!
    \brief      enable RTC tamper
    \param[in]  rtc_tamper: pointer to a rtc_tamper_struct structure which contains 
                parameters for RTC tamper configuration
                members of the structure and the member values are shown as below:
                  rtc_tamper_source: RTC_TAMPER0, RTC_TAMPER1
                  rtc_tamper_trigger: RTC_TAMPER_TRIGGER_EDGE_RISING, RTC_TAMPER_TRIGGER_EDGE_FALLING
                                      RTC_TAMPER_TRIGGER_LEVEL_LOW, RTC_TAMPER_TRIGGER_LEVEL_HIGH
                  rtc_tamper_filter: RTC_FLT_EDGE, RTC_FLT_2S, RTC_FLT_4S, RTC_FLT_8S
                  rtc_tamper_sample_frequency: RTC_FREQ_DIV32768, RTC_FREQ_DIV16384, RTC_FREQ_DIV8192,
                                               RTC_FREQ_DIV4096, RTC_FREQ_DIV2048, RTC_FREQ_DIV1024,
                                               RTC_FREQ_DIV512, RTC_FREQ_DIV256
                  rtc_tamper_precharge_enable: DISABLE, ENABLE
                  rtc_tamper_precharge_time: RTC_PRCH_1C, RTC_PRCH_2C, RTC_PRCH_4C, RTC_PRCH_8C
                  rtc_tamper_with_timestamp: DISABLE, ENABLE
    \param[out] none
    \retval     none
*/
void rtc_tamper_enable(rtc_tamper_struct* rtc_tamper)
{
    /* disable tamper */
    RTC_TAMP &= (uint32_t)~(rtc_tamper->rtc_tamper_source); 

    /* tamper filter must be used when the tamper source is voltage level detection */
    RTC_TAMP &= (uint32_t)~RTC_TAMP_FLT;
    
    /* the tamper source is voltage level detection */
    if(rtc_tamper->rtc_tamper_filter != RTC_FLT_EDGE ){ 
        RTC_TAMP &= (uint32_t)~(RTC_TAMP_DISPU | RTC_TAMP_PRCH | RTC_TAMP_FREQ | RTC_TAMP_FLT);

        /* check if the tamper pin need precharge, if need, then configure the precharge time */
        if(DISABLE == rtc_tamper->rtc_tamper_precharge_enable){
            RTC_TAMP |=  (uint32_t)RTC_TAMP_DISPU;    
        }else{
            RTC_TAMP |= (uint32_t)(rtc_tamper->rtc_tamper_precharge_time);
        }

        RTC_TAMP |= (uint32_t)(rtc_tamper->rtc_tamper_sample_frequency);
        RTC_TAMP |= (uint32_t)(rtc_tamper->rtc_tamper_filter);
    }
    
    RTC_TAMP &= (uint32_t)~RTC_TAMP_TPTS;  
    
    if(DISABLE != rtc_tamper->rtc_tamper_with_timestamp){           
        /* the tamper event also cause a time-stamp event */
        RTC_TAMP |= (uint32_t)RTC_TAMP_TPTS;
    } 
    
    /* configure the tamper trigger */
    RTC_TAMP &= ((uint32_t)~((rtc_tamper->rtc_tamper_source) << RTC_TAMPER_TRIGGER_POS));    
    if(RTC_TAMPER_TRIGGER_EDGE_RISING != rtc_tamper->rtc_tamper_trigger){
        RTC_TAMP |= (uint32_t)((rtc_tamper->rtc_tamper_source)<< RTC_TAMPER_TRIGGER_POS);  
    }    
    /* enable tamper */
    RTC_TAMP |=  (uint32_t)(rtc_tamper->rtc_tamper_source); 
}

/*!
    \brief      disable RTC tamper
    \param[in]  source: specify which tamper source to be disabled
                only one parameter can be selected which is shown as below:
      \arg        RTC_TAMPER0
      \arg        RTC_TAMPER1
    \param[out] none
    \retval     none
*/
void rtc_tamper_disable(uint32_t source)
{
    /* disable tamper */
    RTC_TAMP &= (uint32_t)~source; 

}

/*!
    \brief      enable specified RTC interrupt
    \param[in]  interrupt: specify which interrupt source to be enabled
                only one parameter can be selected which is shown as below:
      \arg        RTC_INT_TIMESTAMP: timestamp interrupt
      \arg        RTC_INT_ALARM: alarm interrupt
      \arg        RTC_INT_TAMP: tamp interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_enable(uint32_t interrupt)
{  
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
 
    /* enable the interrupts in RTC_CTL register */
    RTC_CTL |= (uint32_t)(interrupt & (uint32_t)~RTC_TAMP_TPIE);
    /* enable the interrupts in RTC_TAMP register */
    RTC_TAMP |= (uint32_t)(interrupt & RTC_TAMP_TPIE);
    
    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY; 
}

/*!
    \brief      disble specified RTC interrupt
    \param[in]  interrupt: specify which interrupt source to be disabled
                only one parameter can be selected which is shown as below:
      \arg        RTC_INT_TIMESTAMP: timestamp interrupt
      \arg        RTC_INT_ALARM: alarm interrupt
      \arg        RTC_INT_TAMP: tamp interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_disable(uint32_t interrupt)
{  
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
 
    /* disable the interrupts in RTC_CTL register */
    RTC_CTL &= (uint32_t)~(interrupt & (uint32_t)~RTC_TAMP_TPIE);
    /* disable the interrupts in RTC_TAMP register */
    RTC_TAMP &= (uint32_t)~(interrupt & RTC_TAMP_TPIE);

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      check specified flag
    \param[in]  flag: specify which flag to check
                only one parameter can be selected which is shown as below:
      \arg        RTC_FLAG_RECALIBRATION: recalibration pending flag
      \arg        RTC_FLAG_TAMP1: tamper 1 event flag
      \arg        RTC_FLAG_TAMP0: tamper 0 event flag
      \arg        RTC_FLAG_TIMESTAMP_OVERFLOW: time-stamp overflow event flag
      \arg        RTC_FLAG_TIMESTAMP: time-stamp event flag
      \arg        RTC_FLAG_ALARM0: alarm event flag
      \arg        RTC_FLAG_INIT: init mode event flag
      \arg        RTC_FLAG_RSYN: time and date registers synchronized event flag
      \arg        RTC_FLAG_YCM: year parameter configured event flag
      \arg        RTC_FLAG_SHIFT: shift operation pending flag
      \arg        RTC_FLAG_ALARM0_WRITTEN: alarm writen available flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rtc_flag_get(uint32_t flag)
{
    FlagStatus flag_state = RESET;
    
    if((uint32_t)RESET != (RTC_STAT & flag)){   
        flag_state = SET;
    }
    return flag_state;
}

/*!
    \brief      clear specified flag
    \param[in]  flag: specify which flag to clear
                only one parameter can be selected which is shown as below:
      \arg        RTC_FLAG_TAMP1: tamper 1 event flag
      \arg        RTC_FLAG_TAMP0: tamper 0 event flag
      \arg        RTC_FLAG_TIMESTAMP_OVERFLOW: time-stamp overflow event flag
      \arg        RTC_FLAG_TIMESTAMP: time-stamp event flag
      \arg        RTC_FLAG_ALARM0: alarm event flag
      \arg        RTC_FLAG_RSYN: time and date registers synchronized event flag
    \param[out] none
    \retval     none
*/
void rtc_flag_clear(uint32_t flag)
{
    RTC_STAT &= (uint32_t)(~flag);  
}

/*!
    \brief      configure rtc alternate output source
    \param[in]  source: specify signal to output
                only one parameter can be selected which is shown as below:
      \arg        RTC_CALIBRATION_512HZ: when the LSE freqency is 32768Hz and the RTC_PSC 
                                         is the default value, output 512Hz signal
      \arg        RTC_CALIBRATION_1HZ: when the LSE freqency is 32768Hz and the RTC_PSC 
                                       is the default value, output 512Hz signal
      \arg        RTC_ALARM_HIGH: when the  alarm flag is set, the output pin is high
      \arg        RTC_ALARM_LOW: when the  Alarm flag is set, the output pin is low
    \param[in]  mode: specify the output pin (PC13) mode when output alarm signal
                only one parameter can be selected which is shown as below:
      \arg        RTC_ALARM_OUTPUT_OD: open drain mode
      \arg        RTC_ALARM_OUTPUT_PP: push pull mode
    \param[out] none
    \retval     none
*/
void rtc_alter_output_config(uint32_t source, uint32_t mode)
{
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_CTL &= (uint32_t)~(RTC_CTL_COEN | RTC_CTL_OS | RTC_CTL_OPOL | RTC_CTL_COS);

    RTC_CTL |= (uint32_t)(source);
    
    /* alarm output */
    if((uint32_t)RESET != (source & RTC_OS_ENABLE)){
        RTC_TAMP &= (uint32_t)~(RTC_TAMP_PC13VAL);
        RTC_TAMP |= (uint32_t)(mode);  
    }
    
    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      configure RTC calibration register
    \param[in]  window: select calibration window
                only one parameter can be selected which is shown as below:
      \arg        RTC_CALIBRATION_WINDOW_32S: 2exp20 RTCCLK cycles, 32s if RTCCLK = 32768 Hz
      \arg        RTC_CALIBRATION_WINDOW_16S: 2exp19 RTCCLK cycles, 16s if RTCCLK = 32768 Hz
      \arg        RTC_CALIBRATION_WINDOW_8S: 2exp18 RTCCLK cycles, 8s if RTCCLK = 32768 Hz
    \param[in]  plus: add RTC clock or not
                only one parameter can be selected which is shown as below:
      \arg        RTC_CALIBRATION_PLUS_SET: add one RTC clock every 2048 rtc clock
      \arg        RTC_CALIBRATION_PLUS_RESET: no effect
    \param[in]  minus: the RTC clock to minus during the calibration window(0x0 - 0x1FF)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_calibration_config(uint32_t window, uint32_t plus, uint32_t minus)
{
    uint32_t time_index = RTC_HRFC_TIMEOUT;
    ErrStatus error_status = ERROR;
    uint32_t flag_status = RESET;
    
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;    
    
    /* check if a calibration operation is ongoing */        
    do{
        flag_status = RTC_STAT & RTC_STAT_SCPF;
    }while((--time_index > 0x00U) && ((uint32_t)RESET != flag_status));
    
    if((uint32_t)RESET == flag_status){
        RTC_HRFC = (uint32_t)(window | plus | HRFC_CMSK(minus));
        error_status = SUCCESS;
    }

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}

/*!
    \brief      adjust the daylight saving time by adding or substracting one hour from the current time
    \param[in]  operation: hour ajustment operation
                only one parameter can be selected which is shown as below:
      \arg        RTC_CTL_A1H: add one hour
      \arg        RTC_CTL_S1H: substract one hour
    \param[out] none
    \retval     none
*/
void rtc_hour_adjust(uint32_t operation)
{
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_CTL |= (uint32_t)(operation);

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      adjust RTC second or subsecond value of current time
    \param[in]  add: add 1s to current time or not
                only one parameter can be selected which is shown as below:
      \arg        RTC_SHIFT_ADD1S_RESET: no effect
      \arg        RTC_SHIFT_ADD1S_SET: add 1s to current time
    \param[in]  minus: number of subsecond to minus from current time(0x0 - 0x7FFF)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_second_adjust(uint32_t add, uint32_t minus)
{
    uint32_t time_index = RTC_SHIFTCTL_TIMEOUT;
    ErrStatus error_status = ERROR;
    uint32_t flag_status = RESET;
    uint32_t temp=0U;

    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;
    
    /* check if a shift operation is ongoing */    
    do{
        flag_status = RTC_STAT & RTC_STAT_SOPF;
    }while((--time_index > 0x00U) && ((uint32_t)RESET != flag_status));
  
    temp = RTC_CTL & RTC_CTL_REFEN;
    /* check if the function of reference clock detection is disabled */
    if(((uint32_t)RESET == flag_status) && (RESET == temp)){  
        RTC_SHIFTCTL = (uint32_t)(add | SHIFTCTL_SFS(minus));
        error_status = rtc_register_sync_wait();        
    }

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}

/*!
    \brief      enable RTC bypass shadow registers function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_bypass_shadow_enable(void)
{ 
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_CTL |= (uint8_t)RTC_CTL_BPSHAD;

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      disable RTC bypass shadow registers function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_bypass_shadow_disable(void)
{ 
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    RTC_CTL &= (uint8_t)~RTC_CTL_BPSHAD;

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;
}

/*!
    \brief      enable RTC reference clock detection function
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_refclock_detection_enable(void)
{
    ErrStatus error_status = ERROR;
    
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    /* enter init mode */
    error_status = rtc_init_mode_enter();

    if(ERROR != error_status){
        RTC_CTL |= (uint32_t)RTC_CTL_REFEN;
        /* exit init mode */
        rtc_init_mode_exit();
    }

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}

/*!
    \brief      disable RTC reference clock detection function
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus rtc_refclock_detection_disable(void)
{
    ErrStatus error_status = ERROR;
    
    /* disable the write protection */
    RTC_WPK = RTC_UNLOCK_KEY1;
    RTC_WPK = RTC_UNLOCK_KEY2;

    /* enter init mode */
    error_status = rtc_init_mode_enter();

    if(ERROR != error_status){ 
        RTC_CTL &= (uint32_t)~RTC_CTL_REFEN;
        /* exit init mode */
        rtc_init_mode_exit();
    }

    /* enable the write protection */
    RTC_WPK = RTC_LOCK_KEY;

    return error_status;
}
