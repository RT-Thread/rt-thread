/*!
    \file    gd32e50x_shrtimer.c
    \brief   SHRTIMER driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#include "gd32e50x_shrtimer.h"

#ifndef GD32EPRT

/* SHRTIMER related parameter mask */
#define CNTCKDIV2_0_MASK  (uint32_t)(0x00000007)
#define CNTCKDIV3_MASK  (uint32_t)(0x00000008)
#define STX_UPDATESOURCE_MASK (SHRTIMER_STXCTL0_UPBST0 | SHRTIMER_STXCTL0_UPBST1 | SHRTIMER_STXCTL0_UPBST2 | SHRTIMER_STXCTL0_UPBST3 | SHRTIMER_STXCTL0_UPBST4 | SHRTIMER_STXCTL0_UPBMT)
#define STX_FAULTCH_MASK (SHRTIMER_STXFLTCTL_FLT0EN | SHRTIMER_STXFLTCTL_FLT1EN | SHRTIMER_STXFLTCTL_FLT2EN | SHRTIMER_STXFLTCTL_FLT3EN | SHRTIMER_STXFLTCTL_FLT4EN)

/* configure Master_TIMER timer base */
static void master_timer_base_config(uint32_t shrtimer_periph, shrtimer_baseinit_parameter_struct* master_baseinit);
/* configure Master_TIMER in waveform mode  */
static void master_timer_waveform_config(uint32_t shrtimer_periph, shrtimer_timerinit_parameter_struct * master_timerinit);
/* configure Slave_TIMER timer base */
static void slave_timer_base_config(uint32_t shrtimer_periph, uint32_t slave_id, shrtimer_baseinit_parameter_struct* slave_baseinit);
/* configure Slave_TIMER in waveform mode  */
static void slave_timer_waveform_config(uint32_t shrtimer_periph, uint32_t slave_id, shrtimer_timerinit_parameter_struct * slave_timerinit);
/* configure the an external event channel */
static void external_event_config(uint32_t shrtimer_periph, uint32_t event_id, shrtimer_exeventcfg_parameter_struct* eventcfg);
/* configure the channel output  */
static void channel_output_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel, shrtimer_channel_outputcfg_parameter_struct * outcfg);

/*!
    \brief      deinit a SHRTIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[out] none
    \retval     none
*/
void shrtimer_deinit(uint32_t shrtimer_periph)
{
    switch(shrtimer_periph)
    {
    case SHRTIMER0:
        /* reset SHRTIMER0 */
        rcu_periph_reset_enable(RCU_SHRTIMERRST);
        rcu_periph_reset_disable(RCU_SHRTIMERRST);
        break;
    default:
    break;
    }
}

/*!
    \brief      configure and start DLL calibration
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  calform: specify the calibration form
                only one can be selected which is shown as below:
      \arg          SHRTIMER_CALIBRATION_ONCE: DLL calibration start once
      \arg          SHRTIMER_CALIBRATION_1048576_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 1048576 * tSHRTIMER_CK
      \arg          SHRTIMER_CALIBRATION_131072_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 131072  * tSHRTIMER_CK
      \arg          SHRTIMER_CALIBRATION_16384_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 16384  * tSHRTIMER_CK
      \arg          SHRTIMER_CALIBRATION_2048_PERIOD: DLL periodic calibration, the length of the DLL calibration cycle is 2048 * tSHRTIMER_CK
    \param[out] none
    \retval     none
*/
void shrtimer_dll_calibration_start(uint32_t shrtimer_periph, uint32_t calform)
{
    uint32_t dllcctl_reg;

    /* configure DLL calibration */
    dllcctl_reg = SHRTIMER_DLLCCTL(shrtimer_periph);

    if (SHRTIMER_CALIBRATION_ONCE == calform)
    {
        /* DLL periodic calibration disable */
        dllcctl_reg &= ~(SHRTIMER_DLLCCTL_CLBPEREN);
        dllcctl_reg |= SHRTIMER_DLLCCTL_CLBSTRT;
    }else{
        /* DLL periodic calibration enable */
        dllcctl_reg &= ~(SHRTIMER_DLLCCTL_CLBPER | SHRTIMER_DLLCCTL_CLBSTRT);
        dllcctl_reg |= (calform | SHRTIMER_DLLCCTL_CLBPEREN);
    }

    SHRTIMER_DLLCCTL(shrtimer_periph) = dllcctl_reg;
}

/*!
    \brief      initialize SHRTIMER time base parameters struct with a default value
    \param[in]  baseinit: SHRTIMER time base parameters struct
    \param[out] none
    \retval     none
*/
void shrtimer_baseinit_struct_para_init(shrtimer_baseinit_parameter_struct* baseinit)
{
    baseinit->counter_mode = SHRTIMER_COUNTER_MODE_SINGLEPULSE;
    baseinit->period = 0xFFDFU;
    baseinit->prescaler = SHRTIMER_PRESCALER_MUL32;
    baseinit->repetitioncounter = 0x00U;
}

/*!
    \brief      initialize Master_TIMER and Slave_TIMER timerbase
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  baseinit: SHRTIMER time base parameters struct
                  period: period value, min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
                  repetitioncounter: the counter repetition value, 0x00~0xFF
                  prescaler: SHRTIMER_PRESCALER_MULy(y=64,32,16,8,4,2), SHRTIMER_PRESCALER_DIVy(y=1,2,4)
                  counter_mode: SHRTIMER_COUNTER_MODE_CONTINOUS, SHRTIMER_COUNTER_MODE_SINGLEPULSE, SHRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE
    \param[out] none
    \retval     none
*/
void shrtimer_timers_base_init(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_baseinit_parameter_struct* baseinit)
{
    if(SHRTIMER_MASTER_TIMER == timer_id)
    {
        /* configure Master_TIMER timer base */
        master_timer_base_config(shrtimer_periph, baseinit);
    }else{
        /* configure Slave_TIMER timer base */
        slave_timer_base_config(shrtimer_periph, timer_id, baseinit);
    }
}

/*!
    \brief      enable a counter
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  cntid: specify the counter to configure
                only one can be selected which is shown as below:
      \arg          SHRTIMER_MT_COUNTER: the counter of Master_TIMER
      \arg          SHRTIMER_ST0_COUNTER: the counter of Slave_TIMER0
      \arg          SHRTIMER_ST1_COUNTER: the counter of Slave_TIMER1
      \arg          SHRTIMER_ST2_COUNTER: the counter of Slave_TIMER2
      \arg          SHRTIMER_ST3_COUNTER: the counter of Slave_TIMER3
      \arg          SHRTIMER_ST4_COUNTER: the counter of Slave_TIMER4
    \param[out] none
    \retval     none
*/
void shrtimer_timers_counter_enable(uint32_t shrtimer_periph, uint32_t cntid)
{
    SHRTIMER_MTCTL0(shrtimer_periph) |= cntid;
}

/*!
    \brief      disable a counter
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  cntid: specify the counter to configure
                only one can be selected which is shown as below:
      \arg          SHRTIMER_MT_COUNTER: the counter of Master_TIMER
      \arg          SHRTIMER_ST0_COUNTER: the counter of Slave_TIMER0
      \arg          SHRTIMER_ST1_COUNTER: the counter of Slave_TIMER1
      \arg          SHRTIMER_ST2_COUNTER: the counter of Slave_TIMER2
      \arg          SHRTIMER_ST3_COUNTER: the counter of Slave_TIMER3
      \arg          SHRTIMER_ST4_COUNTER: the counter of Slave_TIMER4
    \param[out] none
    \retval     none
*/
void shrtimer_timers_counter_disable(uint32_t shrtimer_periph, uint32_t cntid)
{
    SHRTIMER_MTCTL0(shrtimer_periph) &= ~(cntid);
}

/*!
    \brief      enable the Master_TIMER or Slave_TIMER update event
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[out] none
    \retval     none
*/
void shrtimer_timers_update_event_enable(uint32_t shrtimer_periph, uint32_t timer_id)
{
    switch(timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
            /* enable the Master_TIMER update event */
            SHRTIMER_CTL0(shrtimer_periph) &= ~SHRTIMER_CTL0_MTUPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER0:
            /* enable the Slave_TIMER0 update event */
            SHRTIMER_CTL0(shrtimer_periph) &= ~SHRTIMER_CTL0_ST0UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER1:
            /* enable the Slave_TIMER1 update event */
            SHRTIMER_CTL0(shrtimer_periph) &= ~SHRTIMER_CTL0_ST1UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER2:
            /* enable the Slave_TIMER2 update event */
            SHRTIMER_CTL0(shrtimer_periph) &= ~SHRTIMER_CTL0_ST2UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER3:
            /* enable the Slave_TIMER3 update event */
            SHRTIMER_CTL0(shrtimer_periph) &= ~SHRTIMER_CTL0_ST3UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER4:
            /* enable the Slave_TIMER4 update event */
            SHRTIMER_CTL0(shrtimer_periph) &= ~SHRTIMER_CTL0_ST4UPDIS;
        break;
        default:
        break;
    }
}

/*!
    \brief      disable the Master_TIMER or Slave_TIMER update event
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[out] none
    \retval     none
*/
void shrtimer_timers_update_event_disable(uint32_t shrtimer_periph, uint32_t timer_id)
{
    switch(timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
            /* disable the Master_TIMER update event */
            SHRTIMER_CTL0(shrtimer_periph) |= SHRTIMER_CTL0_MTUPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER0:
            /* disable the Slave_TIMER0 update event */
            SHRTIMER_CTL0(shrtimer_periph) |= SHRTIMER_CTL0_ST0UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER1:
            /* disable the Slave_TIMER1 update event */
            SHRTIMER_CTL0(shrtimer_periph) |= SHRTIMER_CTL0_ST1UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER2:
            /* disable the Slave_TIMER2 update event */
            SHRTIMER_CTL0(shrtimer_periph) |= SHRTIMER_CTL0_ST2UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER3:
            /* disable the Slave_TIMER3 update event */
            SHRTIMER_CTL0(shrtimer_periph) |= SHRTIMER_CTL0_ST3UPDIS;
        break;
        case SHRTIMER_SLAVE_TIMER4:
            /* disable the Slave_TIMER4 update event */
            SHRTIMER_CTL0(shrtimer_periph) |= SHRTIMER_CTL0_ST4UPDIS;
        break;
        default:
        break;
    }
}

/*!
    \brief      trigger the Master_TIMER and Slave_TIMER registers update by software
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timersrc: which timer to be update by software
                only one can be selected which is shown as below:
      \arg         SHRTIMER_UPDATE_SW_MT: Master_TIMER software update
      \arg         SHRTIMER_UPDATE_SW_ST0: Slave_TIMER0 software update
      \arg         SHRTIMER_UPDATE_SW_ST1: Slave_TIMER1 software update
      \arg         SHRTIMER_UPDATE_SW_ST2: Slave_TIMER2 software update
      \arg         SHRTIMER_UPDATE_SW_ST3: Slave_TIMER3 software update
      \arg         SHRTIMER_UPDATE_SW_ST4: Slave_TIMER4 software update
    \param[out] none
    \retval     none
*/
void shrtimer_software_update(uint32_t shrtimer_periph, uint32_t timersrc)
{
    SHRTIMER_CTL1(shrtimer_periph) |= timersrc;
}

/*!
    \brief      reset the Master_TIMER and Slave_TIMER counter by software
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timerrst: which timer to be reset by software
                only one can be selected which is shown as below:
      \arg         SHRTIMER_COUNTER_RESET_SW_MT: Master_TIMER software reset
      \arg         SHRTIMER_COUNTER_RESET_SW_ST0: Slave_TIMER0 software reset
      \arg         SHRTIMER_COUNTER_RESET_SW_ST1: Slave_TIMER1 software reset
      \arg         SHRTIMER_COUNTER_RESET_SW_ST2: Slave_TIMER2 software reset
      \arg         SHRTIMER_COUNTER_RESET_SW_ST3: Slave_TIMER3 software reset
      \arg         SHRTIMER_COUNTER_RESET_SW_ST4: Slave_TIMER4 software reset
    \param[out] none
    \retval     none
*/
void shrtimer_software_counter_reset(uint32_t shrtimer_periph, uint32_t timerrst)
{
    SHRTIMER_CTL1(shrtimer_periph) |= timerrst;
}

/*!
    \brief      initialize waveform mode initialization parameters struct with a default value
    \param[in]  timerinitpara: SHRTIMER waveform mode initialization parameters
    \param[out] none
    \retval     none
*/
void shrtimer_timerinit_struct_para_init(shrtimer_timerinit_parameter_struct* timerinit)
{
    timerinit->cnt_bunch = SHRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK;
    timerinit->dac_trigger = SHRTIMER_DAC_TRIGGER_NONE;
    timerinit->half_mode = SHRTIMER_HALFMODE_DISABLED;
    timerinit->repetition_update = SHRTIMER_UPDATEONREPETITION_DISABLED;
    timerinit->reset_sync = SHRTIMER_SYNCRESET_DISABLED;
    timerinit->shadow = SHRTIMER_SHADOW_DISABLED;
    timerinit->start_sync = SHRTIMER_SYNISTART_DISABLED;
    timerinit->update_selection = SHRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT;
}

/*!
    \brief      initialize a timer to work in waveform mode
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  timerinitpara: SHRTIMER waveform mode initialization parameters
                  half_mode: SHRTIMER_HALFMODE_DISABLED, SHRTIMER_HALFMODE_ENABLED
                  start_sync: SHRTIMER_SYNISTART_DISABLED, SHRTIMER_SYNISTART_ENABLED
                  reset_sync: SHRTIMER_SYNCRESET_DISABLED, SHRTIMER_SYNCRESET_ENABLED
                  dac_trigger: SHRTIMER_DAC_TRIGGER_NONE, SHRTIMER_DAC_TRIGGER_DACTRIGy(y=0..2)
                  shadow: SHRTIMER_SHADOW_DISABLED, SHRTIMER_SHADOW_ENABLED
                  update_selection: SHRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT, for Master_TIMER and Slave_TIMER
                                    SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE, for Master_TIMER and Slave_TIMER
                                    SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE, for Master_TIMER and Slave_TIMER
                                    SHRTIMER_ST_UPDATE_SELECTION_STXUPINy(y=2), for Slave_TIMER
                                    SHRTIMER_ST_UPDATE_SELECTION_STXUPINy_UPDATE(y=2), for Slave_TIMER
                  cnt_bunch: SHRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK, SHRTIMER_TIMERBUNCHMODE_RESETCOUNTER
                  repetition_update: SHRTIMER_UPDATEONREPETITION_DISABLED, SHRTIMER_UPDATEONREPETITION_ENABLED
    \param[out] none
    \retval     none
*/
void shrtimer_timers_waveform_init(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_timerinit_parameter_struct* timerinitpara)
{
    if(SHRTIMER_MASTER_TIMER == timer_id)
    {
        /* configure Master_TIMER in waveform mode */
        master_timer_waveform_config(shrtimer_periph, timerinitpara);
    }else{
        /* configure Slave_TIMER in waveform mode */
        slave_timer_waveform_config(shrtimer_periph, timer_id, timerinitpara);
    }
}

/*!
    \brief      initialize Slave_TIMER general behavior configuration struct with a default value
    \param[in]  timercfg: Slave_TIMER general behavior configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_timercfg_struct_para_init(shrtimer_timercfg_parameter_struct* timercgf)
{
    timercgf->balanced_mode = SHRTIMER_STXBALANCEDMODE_DISABLED;
    timercgf->cnt_reset = SHRTIMER_STXCNT_RESET_NONE;
    timercgf->deadtime_enable = SHRTIMER_STXDEADTIME_DISABLED;
    timercgf->delayed_idle = SHRTIMER_STXDELAYED_IDLE_DISABLED;
    timercgf->fault_enable = SHRTIMER_STXFAULTENABLE_NONE;
    timercgf->fault_protect = SHRTIMER_STXFAULT_PROTECT_READWRITE;
    timercgf->reset_update = SHRTIMER_STXUPDATEONRESET_DISABLED;
    timercgf->update_source = SHRTIMER_STXUPDATETRIGGER_NONE;
}

/*!
    \brief      configure the general behavior of a Slave_TIMER which work in waveform mode
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  timercfg: Slave_TIMER general behavior configuration struct
                  balanced_mode: SHRTIMER_STXBALANCEDMODE_DISABLED, SHRTIMER_STXBALANCEDMODE_ENABLED
                  fault_enable: SHRTIMER_STXFAULTENABLE_NONE, SHRTIMER_STXFAULTENABLE_FAULT0, SHRTIMER_STXFAULTENABLE_FAULT1, SHRTIMER_STXFAULTENABLE_FAULT2, SHRTIMER_STXFAULTENABLE_FAULT3 ,SHRTIMER_STXFAULTENABLE_FAULT4
                  fault_protect: SHRTIMER_STXFAULT_PROTECT_READWRITE, SHRTIMER_STXFAULT_PROTECT_READONLY
                  deadtime_enable: SHRTIMER_STXDEADTIME_DISABLED, SHRTIMER_STXDEADTIME_ENABLED
                  delayed_idle: SHRTIMER_STXDELAYED_IDLE_DISABLED,SHRTIMER_STXDELAYED_IDLE_CH0_EEV57,SHRTIMER_STXDELAYED_IDLE_CH1_EEV57,SHRTIMER_STXDELAYED_IDLE_BOTH_EEV57,SHRTIMER_STXDELAYED_IDLE_BALANCED_EEV57,
                                 SHRTIMER_STXDELAYED_IDLE_CH0_DEEV68,SHRTIMER_STXDELAYED_IDLE_CH1_DEEV68,SHRTIMER_STXDELAYED_IDLE_BOTH_EEV68,SHRTIMER_STXDELAYED_IDLE_BALANCED_EEV68
                  update_source: SHRTIMER_STXUPDATETRIGGER_NONE, SHRTIMER_STXUPDATETRIGGER_MASTER, SHRTIMER_STXUPDATETRIGGER_STx(x=0..4)
                  cnt_reset: SHRTIMER_STXCNT_RESET_NONE, SHRTIMER_STXCNT_RESET_UPDATE, SHRTIMER_STXCNT_RESET_CMP1, SHRTIMER_STXCNT_RESET_CMP3, SHRTIMER_STXCNT_RESET_MASTER_PER, SHRTIMER_STXCNT_RESET_MASTER_CMPy(y=0..3),
                             SHRTIMER_STXCNT_RESET_EEV_y(y=0..9), SHRTIMER_STXCNT_RESET_OTHERx_CMPy(x=0..3, y=0,1,3)
                  reset_update: SHRTIMER_STXUPDATEONRESET_DISABLED, SHRTIMER_STXUPDATEONRESET_ENABLED
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_waveform_config(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_timercfg_parameter_struct * timercfg)
{
    uint32_t stxctl0_reg;
    uint32_t stxfltctl_reg;
    uint32_t stxchoctl_reg;
    uint32_t stxcntrst_reg;

    /* get the value of registers */
    stxctl0_reg = SHRTIMER_STXCTL0(shrtimer_periph, timer_id);
    stxfltctl_reg = SHRTIMER_STXFLTCTL(shrtimer_periph, timer_id);
    stxchoctl_reg = SHRTIMER_STXCHOCTL(shrtimer_periph, timer_id);
    stxcntrst_reg = SHRTIMER_STXCNTRST(shrtimer_periph, timer_id);

    /* set the balanced mode */
    stxctl0_reg &= ~(SHRTIMER_STXCTL0_BLNMEN);
    stxctl0_reg |= timercfg->balanced_mode;

    /* update event generated by reset event */
    stxctl0_reg &= ~(SHRTIMER_STXCTL0_UPRST);
    stxctl0_reg |= timercfg->reset_update;

    /* set the timer update source */
    stxctl0_reg &= ~(STX_UPDATESOURCE_MASK);
    stxctl0_reg |= timercfg->update_source;

    /* enable/disable the fault channel (at Slave_TIMER level) */
    stxfltctl_reg &= ~(STX_FAULTCH_MASK);
    stxfltctl_reg |= (timercfg->fault_enable & STX_FAULTCH_MASK);

    /* protect fault enable (at Slave_TIMER level) */
    stxfltctl_reg &= ~(SHRTIMER_STXFLTCTL_FLTENPROT);
    stxfltctl_reg |= timercfg->fault_protect;

    /* enable/disable dead time insertion (at Slave_TIMER level) */
    stxchoctl_reg &= ~(SHRTIMER_STXCHOCTL_DTEN);
    stxchoctl_reg |= timercfg->deadtime_enable;

    /* enable/disable delayed IDLE (at Slave_TIMER level) */
    stxchoctl_reg &= ~(SHRTIMER_STXCHOCTL_DLYISCH| SHRTIMER_STXCHOCTL_DLYISMEN);
    stxchoctl_reg |= timercfg->delayed_idle;

    /* resets Slave_TIMER counter */
    stxcntrst_reg = timercfg->cnt_reset;

    SHRTIMER_STXCTL0(shrtimer_periph, timer_id) = stxctl0_reg;
    SHRTIMER_STXFLTCTL(shrtimer_periph, timer_id) = stxfltctl_reg;
    SHRTIMER_STXCHOCTL(shrtimer_periph, timer_id) = stxchoctl_reg;
    SHRTIMER_STXCNTRST(shrtimer_periph, timer_id) = stxcntrst_reg;
}


/*!
    \brief      initialize compare unit configuration struct with a default value
    \param[in]  cmpcfg: compare unit configuration struct definitions
    \param[out] none
    \retval     none
*/
void shrtimer_comparecfg_struct_para_init(shrtimer_comparecfg_parameter_struct* comparecfg)
{
    comparecfg->compare_value = 0x0000U;
    comparecfg->delayed_mode = SHRTIMER_DELAYEDMODE_DISABLE;
    comparecfg->timeout_value = 0x0U;
}

/*!
    \brief      configure the compare unit of a Slave_TIMER which work in waveform mode
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  comparex: SHRTIMER_COMPAREy(y=0..3)
    \param[in]  cmpcfg: compare unit configuration struct definitions
                  compare_value: min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
                  delayed_mode: SHRTIMER_DELAYEDMODE_DISABLE, SHRTIMER_DELAYEDMODE_NOTIMEOUT, SHRTIMER_DELAYEDMODE_TIMEOUTCMP0, SHRTIMER_DELAYEDMODE_TIMEOUTCMP2
                  timeout_value: 0x0000~((timeout_value + compare_value) < 0xFFFF)
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_waveform_compare_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t comparex, shrtimer_comparecfg_parameter_struct* cmpcfg)
{
    uint32_t stxctl0_reg;

    /* configure the compare unit */
    switch (comparex)
    {
        case SHRTIMER_COMPARE0:
        {
            /* set the compare value */
            SHRTIMER_STXCMP0V(shrtimer_periph, timer_id) = cmpcfg->compare_value;
        }
        break;

        case SHRTIMER_COMPARE1:
        {
            /* set the compare value */
            SHRTIMER_STXCMP1V(shrtimer_periph, timer_id) = cmpcfg->compare_value;

            if(SHRTIMER_DELAYEDMODE_DISABLE != cmpcfg->delayed_mode)
            {
                /* configure delayed mode */
                stxctl0_reg = SHRTIMER_STXCTL0(shrtimer_periph, timer_id);
                stxctl0_reg &= ~SHRTIMER_STXCTL0_DELCMP1M;
                stxctl0_reg |= cmpcfg->delayed_mode;
                SHRTIMER_STXCTL0(shrtimer_periph, timer_id) = stxctl0_reg;

                /* set the compare value for timeout compare unit */
                if(SHRTIMER_DELAYEDMODE_TIMEOUTCMP0 == cmpcfg->delayed_mode)
                {
                    SHRTIMER_STXCMP0V(shrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else if(SHRTIMER_DELAYEDMODE_TIMEOUTCMP2 == cmpcfg->delayed_mode)
                {
                    SHRTIMER_STXCMP2V(shrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else{
                }
            }
        }
        break;

        case SHRTIMER_COMPARE2:
        {
            /* set the compare value */
            SHRTIMER_STXCMP2V(shrtimer_periph, timer_id) = cmpcfg->compare_value;
        }
        break;
        case SHRTIMER_COMPARE3:
        {
            /* set the compare value */
            SHRTIMER_STXCMP3V(shrtimer_periph, timer_id) = cmpcfg->compare_value;

            if(SHRTIMER_DELAYEDMODE_DISABLE != cmpcfg->delayed_mode)
            {
                /* configure delayed mode */
                stxctl0_reg = SHRTIMER_STXCTL0(shrtimer_periph, timer_id);
                stxctl0_reg &= ~SHRTIMER_STXCTL0_DELCMP3M;
                stxctl0_reg |= (cmpcfg->delayed_mode << 2);
                SHRTIMER_STXCTL0(shrtimer_periph, timer_id) = stxctl0_reg;

                /* set the compare value for timeout compare unit */
                if(SHRTIMER_DELAYEDMODE_TIMEOUTCMP0 == cmpcfg->delayed_mode)
                {
                  SHRTIMER_STXCMP0V(shrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else if(SHRTIMER_DELAYEDMODE_TIMEOUTCMP2 == cmpcfg->delayed_mode)
                {
                  SHRTIMER_STXCMP2V(shrtimer_periph, timer_id) = cmpcfg->timeout_value;
                }else{
                }
            }
        }
        break;

        default:
        break;
    }
}

/*!
    \brief      initialize channel output configuration struct with a default value
    \param[in]  channelcfg: channel output configuration struct definitions
    \param[out] none
    \retval     none
*/
void shrtimer_channel_outputcfg_struct_para_init(shrtimer_channel_outputcfg_parameter_struct * channelcfg)
{
    channelcfg->carrier_mode = SHRTIMER_CHANNEL_CARRIER_DISABLED;
    channelcfg->deadtime_bunch = SHRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR;
    channelcfg->fault_state = SHRTIMER_CHANNEL_FAULTSTATE_NONE;
    channelcfg->idle_bunch = SHRTIMER_CHANNEL_BUNCH_IDLE_DISABLE;
    channelcfg->idle_state = SHRTIMER_CHANNEL_IDLESTATE_INACTIVE;
    channelcfg->polarity = SHRTIMER_CHANNEL_POLARITY_HIGH;
    channelcfg->reset_request = SHRTIMER_CHANNEL_RESET_NONE;
    channelcfg->set_request = SHRTIMER_CHANNEL_SET_NONE;
}

/*!
    \brief      configure the channel output of a Slave_TIMER work in waveform mode
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  channel: SHRTIMER_STx_CHy(x=0..4,y=0,1)
    \param[in]  channelcfg: channel output configuration struct definitions
                  polarity: SHRTIMER_CHANNEL_POLARITY_HIGH, SHRTIMER_CHANNEL_POLARITY_LOW
                  set_request: SHRTIMER_CHANNEL_SET_NONE, SHRTIMER_CHANNEL_SET_RSTSYNI, SHRTIMER_CHANNEL_SET_PER, SHRTIMER_CHANNEL_SET_CMPy(y=0..3),
                               SHRTIMER_CHANNEL_SET_MTPER, SHRTIMER_CHANNEL_SET_MTCMPy(y=0..3), SHRTIMER_CHANNEL_SET_STEVy(y=0..8),
                               SHRTIMER_CHANNEL_SET_EXEVy(y=0..9), SHRTIMER_CHANNEL_SET_UPDATE
                  reset_request: SHRTIMER_CHANNEL_RESET_NONE, SHRTIMER_CHANNEL_RESET_RSTSYNI, SHRTIMER_CHANNEL_RESET_PER, SHRTIMER_CHANNEL_RESET_CMPy(y=0..3),
                               SHRTIMER_CHANNEL_RESET_MTPER, SHRTIMER_CHANNEL_RESET_MTCMPy(y=0..3), SHRTIMER_CHANNEL_RESET_STEVy(y=0..8),
                               SHRTIMER_CHANNEL_RESET_EXEVy(y=0..9), SHRTIMER_CHANNEL_RESET_UPDATE
                  idle_bunch: SHRTIMER_CHANNEL_BUNCH_IDLE_DISABLE, SHRTIMER_CHANNEL_BUNCH_IDLE_ENABLE
                  idle_state: SHRTIMER_CHANNEL_IDLESTATE_INACTIVE, SHRTIMER_CHANNEL_IDLESTATE_ACTIVE
                  fault_state: SHRTIMER_CHANNEL_FAULTSTATE_NONE, SHRTIMER_CHANNEL_FAULTSTATE_ACTIVE, SHRTIMER_CHANNEL_FAULTSTATE_INACTIVE, SHRTIMER_CHANNEL_FAULTSTATE_HIGHZ
                  carrier_mode: SHRTIMER_CHANNEL_CARRIER_DISABLED, SHRTIMER_CHANNEL_CARRIER_ENABLED
                  deadtime_bunch: SHRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR, SHRTIMER_CHANNEL_BUNCH_ENTRY_DEADTIME
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_waveform_channel_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel, shrtimer_channel_outputcfg_parameter_struct * channelcfg)
{
    channel_output_config(shrtimer_periph, timer_id, channel, channelcfg);
}

/*!
    \brief      software generates channel "set request" or "reset request"
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  channel: SHRTIMER_STx_CHy(x=0..4,y=0,1)
    \param[in]  request: "set request" or "reset request"
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_CHANNEL_SOFTWARE_SET: software event cannot generate request
      \arg         SHRTIMER_CHANNEL_SOFTWARE_RESET: software event can generate request
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_waveform_channel_software_request(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel, uint32_t request)
{
    /* configure the output set/reset crossbar */
    switch (channel)
    {
        /* configure the channel 0 output set/reset crossbar */
        case SHRTIMER_ST0_CH0:
        case SHRTIMER_ST1_CH0:
        case SHRTIMER_ST2_CH0:
        case SHRTIMER_ST3_CH0:
        case SHRTIMER_ST4_CH0:
        {
            if(SHRTIMER_CHANNEL_SOFTWARE_SET == request)
            {
                /* software generates channel "set request" */
                SHRTIMER_STXCH0SET(shrtimer_periph, timer_id) |= SHRTIMER_STXCH0SET_CH0SSEV;
            }else{
                /* software generates channel "reset request" */
                SHRTIMER_STXCH0RST(shrtimer_periph, timer_id) |= SHRTIMER_STXCH0RST_CH0RSSEV;
            }
        }
        break;
        /* configure the channel 1 output set/reset crossbar */
        case SHRTIMER_ST0_CH1:
        case SHRTIMER_ST1_CH1:
        case SHRTIMER_ST2_CH1:
        case SHRTIMER_ST3_CH1:
        case SHRTIMER_ST4_CH1:
        {
            if(SHRTIMER_CHANNEL_SOFTWARE_SET == request)
            {
                /* software generates channel "set request" */
                SHRTIMER_STXCH1SET(shrtimer_periph, timer_id) |= SHRTIMER_STXCH1SET_CH1SSEV;
            }else{
                /* software generates channel "reset request" */
                SHRTIMER_STXCH1RST(shrtimer_periph, timer_id) |= SHRTIMER_STXCH1RST_CH1RSSEV;
            }
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get Slave_TIMER channel output level
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  channel: SHRTIMER_STx_CHy(x=0..4,y=0,1)
    \param[out] none
    \retval     channel output level
*/
uint32_t shrtimer_slavetimer_waveform_channel_output_level_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel)
{
    uint32_t output_level = SHRTIMER_CHANNEL_OUTPUT_INACTIVE;

    switch (channel)
    {
        /* get Slave_TIMER channel 0 output level */
        case SHRTIMER_ST0_CH0:
        case SHRTIMER_ST1_CH0:
        case SHRTIMER_ST2_CH0:
        case SHRTIMER_ST3_CH0:
        case SHRTIMER_ST4_CH0:
        {
            if(RESET != (SHRTIMER_STXINTF(shrtimer_periph, timer_id) & SHRTIMER_STXINTF_CH0F))
            {
                output_level = SHRTIMER_CHANNEL_OUTPUT_ACTIVE;
            }else{
                output_level = SHRTIMER_CHANNEL_OUTPUT_INACTIVE;
            }
        }
        break;
        /* get Slave_TIMER channel 1 output level */
        case SHRTIMER_ST0_CH1:
        case SHRTIMER_ST1_CH1:
        case SHRTIMER_ST2_CH1:
        case SHRTIMER_ST3_CH1:
        case SHRTIMER_ST4_CH1:
        {
            if(RESET != (SHRTIMER_STXINTF(shrtimer_periph, timer_id) & SHRTIMER_STXINTF_CH1F))
            {
                output_level = SHRTIMER_CHANNEL_OUTPUT_ACTIVE;
            }else{
                output_level = SHRTIMER_CHANNEL_OUTPUT_INACTIVE;
            }
        }
        break;
        default:
        break;
    }
    return output_level;
}

/*!
    \brief      get Slave_TIMER channel run state
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  channel: SHRTIMER_STx_CHy(x=0..4,y=0,1)
    \param[out] none
    \retval     channel state
*/
uint32_t shrtimer_slavetimer_waveform_channel_state_get(uint32_t shrtimer_periph, uint32_t channel)
{
    uint32_t enbit = 0U;
    uint32_t state = SHRTIMER_CHANNEL_STATE_IDLE;

    switch (channel)
    {
        /* get Slave_TIMER0 channel 0 run state */
        case SHRTIMER_ST0_CH0:
            enbit = SHRTIMER_CHOUTEN_ST0CH0EN;
        break;
        /* get Slave_TIMER0 channel 1 run state */
        case SHRTIMER_ST0_CH1:
            enbit = SHRTIMER_CHOUTEN_ST0CH1EN;
        break;
        /* get Slave_TIMER1 channel 0 run state */
        case SHRTIMER_ST1_CH0:
            enbit = SHRTIMER_CHOUTEN_ST1CH0EN;
        break;
        /* get Slave_TIMER1 channel 1 run state */
        case SHRTIMER_ST1_CH1:
            enbit = SHRTIMER_CHOUTEN_ST1CH1EN;
        break;
        /* get Slave_TIMER2 channel 0 run state */
        case SHRTIMER_ST2_CH0:
            enbit = SHRTIMER_CHOUTEN_ST2CH0EN;
        break;
        /* get Slave_TIMER2 channel 1 run state */
        case SHRTIMER_ST2_CH1:
            enbit = SHRTIMER_CHOUTEN_ST2CH1EN;
        break;
        /* get Slave_TIMER3 channel 0 run state */
        case SHRTIMER_ST3_CH0:
            enbit = SHRTIMER_CHOUTEN_ST3CH0EN;
        break;
        /* get Slave_TIMER3 channel 1 run state */
        case SHRTIMER_ST3_CH1:
            enbit = SHRTIMER_CHOUTEN_ST3CH1EN;
        break;
        /* get Slave_TIMER4 channel 0 run state */
        case SHRTIMER_ST4_CH0:
            enbit = SHRTIMER_CHOUTEN_ST4CH0EN;
        break;
        /* get Slave_TIMER4 channel 1 run state */
        case SHRTIMER_ST4_CH1:
            enbit = SHRTIMER_CHOUTEN_ST4CH1EN;
        break;
        default:
        break;
    }
    if ( RESET != (SHRTIMER_CHOUTEN(shrtimer_periph) & enbit))
    {
        /* Run state*/
        state = SHRTIMER_CHANNEL_STATE_RUN;
    }else{
        if (RESET != (SHRTIMER_CHOUTDISF(shrtimer_periph) & enbit))
        {
            /* Fault state */
            state = SHRTIMER_CHANNEL_STATE_FAULT;
        }else{
            /* Idle state */
            state = SHRTIMER_CHANNEL_STATE_IDLE;
        }
    }
    return state;
}

/*!
    \brief      initialize dead time configuration struct with a default value
    \param[in]  dtcfg: dead time configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_deadtimercfg_struct_para_init(shrtimer_deadtimecfg_parameter_struct * dtcfg)
{
    dtcfg->fallingsign_protect = SHRTIMER_DEADTIME_FALLINGSIGN_PROTECT_DISABLE;
    dtcfg->falling_protect = SHRTIMER_DEADTIME_FALLING_PROTECT_DISABLE;
    dtcfg->falling_sign = SHRTIMER_DEADTIME_FALLINGSIGN_POSITIVE;
    dtcfg->falling_value = 0U;
    dtcfg->prescaler = SHRTIMER_DEADTIME_PRESCALER_MUL8;
    dtcfg->risingsign_protect = SHRTIMER_DEADTIME_RISINGSIGN_PROTECT_DISABLE;
    dtcfg->rising_protect = SHRTIMER_DEADTIME_RISING_PROTECT_DISABLE;
    dtcfg->rising_sign = SHRTIMER_DEADTIME_RISINGSIGN_POSITIVE;
    dtcfg->rising_value = 0U;
}

/*!
    \brief      configure the dead time for Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  dtcfg: dead time configuration struct
                  prescaler: SHRTIMER_DEADTIME_PRESCALER_MULy(y=64,32,16,8,4,2), SHRTIMER_DEADTIME_PRESCALER_DIVy(y=1,2,4,8,16)
                  rising_value: 0x0000~0xFFFF
                  rising_sign: SHRTIMER_DEADTIME_RISINGSIGN_POSITIVE, SHRTIMER_DEADTIME_RISINGSIGN_NEGATIVE
                  rising_protect: SHRTIMER_DEADTIME_RISING_PROTECT_DISABLE, SHRTIMER_DEADTIME_RISING_PROTECT_ENABLE
                  risingsign_protect: SHRTIMER_DEADTIME_RISINGSIGN_PROTECT_DISABLE, SHRTIMER_DEADTIME_RISINGSIGN_PROTECT_ENABLE
                  falling_value: 0x0000~0xFFFF
                  falling_sign: SHRTIMER_DEADTIME_FALLINGSIGN_POSITIVE, SHRTIMER_DEADTIME_FALLINGSIGN_NEGATIVE
                  falling_protect: SHRTIMER_DEADTIME_FALLING_PROTECT_DISABLE, SHRTIMER_DEADTIME_FALLING_PROTECT_ENABLE
                  fallingsign_protect: SHRTIMER_DEADTIME_FALLINGSIGN_PROTECT_DISABLE, SHRTIMER_DEADTIME_FALLINGSIGN_PROTECT_ENABLE
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_deadtime_config(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_deadtimecfg_parameter_struct* dtcfg)
{
    uint32_t dtctl_reg;
    uint32_t stxactl;

    dtctl_reg = SHRTIMER_STXDTCTL(shrtimer_periph, timer_id);
    stxactl = SHRTIMER_STXACTL(shrtimer_periph, timer_id);

    /* clear dead time configuration */
    dtctl_reg &= ~(SHRTIMER_STXDTCTL_DTRCFG8_0 | SHRTIMER_STXDTCTL_DTRS | SHRTIMER_STXDTCTL_DTGCKDIV |
                 SHRTIMER_STXDTCTL_DTRSPROT | SHRTIMER_STXDTCTL_DTRSVPROT | SHRTIMER_STXDTCTL_DTFCFG8_0 |
                 SHRTIMER_STXDTCTL_DTFS | SHRTIMER_STXDTCTL_DTFSPROT | SHRTIMER_STXDTCTL_DTFSVPROT);
    stxactl &= ~(SHRTIMER_STXACTL_DTRCFG15_9 | SHRTIMER_STXACTL_DTFCFG15_9);

    /* set dead time configuration */
    dtctl_reg |= (dtcfg->prescaler << 10);
    dtctl_reg |= ((dtcfg->rising_value) & SHRTIMER_STXDTCTL_DTRCFG8_0);
    stxactl |= (((dtcfg->rising_value) & (~SHRTIMER_STXDTCTL_DTRCFG8_0)));
    dtctl_reg |= dtcfg->rising_sign;
    dtctl_reg |= dtcfg->risingsign_protect;
    dtctl_reg |= dtcfg->rising_protect;
    dtctl_reg |= (((dtcfg->falling_value) & SHRTIMER_STXDTCTL_DTRCFG8_0) << 16);
    stxactl |= ((dtcfg->falling_value) & (~SHRTIMER_STXDTCTL_DTRCFG8_0)) << 16;
    dtctl_reg |= dtcfg->falling_sign;
    dtctl_reg |= dtcfg->fallingsign_protect;
    dtctl_reg |= dtcfg->falling_protect;

    SHRTIMER_STXACTL(shrtimer_periph, timer_id) = stxactl;
    SHRTIMER_STXDTCTL(shrtimer_periph, timer_id) = dtctl_reg;
}

/*!
    \brief      initialize carrier signal configuration struct with a default value
    \param[in]  carriercfg: carrier signal configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_carriersignalcfg_struct_para_init(shrtimer_carriersignalcfg_parameter_struct* carriercfg)
{
    carriercfg->duty_cycle = 0U;
    carriercfg->first_pulse = 0U;
    carriercfg->period = 0U;
}

/*!
    \brief      configure the carrier signal mode for Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  carriercfg: carrier signal configuration struct
                  period: 0x0~0xF. specifies carrier signal period: (period + 1) * 16 * tSHRTIMER_CK
                  duty_cycle: 0x0~0x7. specifies Carrier signal duty cycle: duty_cycle/8
                  first_pulse: 0x0~0xF. specifies first carrier-signal pulse width: (first_pulse+1) * 16 * tSHRTIMER_CK
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_carriersignal_config(uint32_t shrtimer_periph, uint32_t timer_id, shrtimer_carriersignalcfg_parameter_struct* carriercfg)
{
    uint32_t csctl_reg;

    csctl_reg = SHRTIMER_STXCSCTL(shrtimer_periph, timer_id);

    /* clear timer chopper mode configuration */
    csctl_reg &= ~(SHRTIMER_STXCSCTL_CSPRD | SHRTIMER_STXCSCTL_CSDTY | SHRTIMER_STXCSCTL_CSFSTPW);

    /* set timer chopper mode configuration */
    csctl_reg |= carriercfg->period;
    csctl_reg |= (carriercfg->duty_cycle << 4);
    csctl_reg |= (carriercfg->first_pulse << 7);

    SHRTIMER_STXCSCTL(shrtimer_periph, timer_id) = csctl_reg;
}

/*!
    \brief      enable a output channel
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  chid: specify the channel to configure
                only one can be selected which is shown as below:
      \arg          SHRTIMER_ST0_CH0: ST0CH0_O output channel
      \arg          SHRTIMER_ST0_CH1: ST0CH1_O output channel
      \arg          SHRTIMER_ST1_CH0: ST1CH0_O output channel
      \arg          SHRTIMER_ST1_CH1: ST1CH1_O output channel
      \arg          SHRTIMER_ST2_CH0: ST2CH0_O output channel
      \arg          SHRTIMER_ST2_CH1: ST2CH1_O output channel
      \arg          SHRTIMER_ST3_CH0: ST3CH0_O output channel
      \arg          SHRTIMER_ST3_CH1: ST3CH1_O output channel
      \arg          SHRTIMER_ST4_CH0: ST4CH0_O output channel
      \arg          SHRTIMER_ST4_CH1: ST4CH1_O output channel
    \param[out] none
    \retval     none
*/
void shrtimer_output_channel_enable(uint32_t shrtimer_periph, uint32_t chid)
{
    SHRTIMER_CHOUTEN(shrtimer_periph) = chid;
}

/*!
    \brief      disable a output channel
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  chid: specify the channel to configure
                only one can be selected which is shown as below:
      \arg          SHRTIMER_ST0_CH0: ST0CH0_O output channel
      \arg          SHRTIMER_ST0_CH1: ST0CH1_O output channel
      \arg          SHRTIMER_ST1_CH0: ST1CH0_O output channel
      \arg          SHRTIMER_ST1_CH1: ST1CH1_O output channel
      \arg          SHRTIMER_ST2_CH0: ST2CH0_O output channel
      \arg          SHRTIMER_ST2_CH1: ST2CH1_O output channel
      \arg          SHRTIMER_ST3_CH0: ST3CH0_O output channel
      \arg          SHRTIMER_ST3_CH1: ST3CH1_O output channel
      \arg          SHRTIMER_ST4_CH0: ST4CH0_O output channel
      \arg          SHRTIMER_ST4_CH1: ST4CH1_O output channel
    \param[out] none
    \retval     none
*/
void shrtimer_output_channel_disable(uint32_t shrtimer_periph, uint32_t chid)
{
    SHRTIMER_CHOUTDIS(shrtimer_periph) = chid;
}

/*!
    \brief      configure the compare value in Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  comparex: SHRTIMER_COMPAREy(y=0..3), SHRTIMER_COMPARE0_COMPOSITE
    \param[in]  cmpvalue:  min value: 3 tSHRTIMER_CK clock, max value: 0xFFFF �C (1 tSHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_compare_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t comparex, uint32_t cmpvalue)
{
    /* configure the compare unit */
    switch (comparex)
    {
        case SHRTIMER_COMPARE0:
        {
            /* set the compare 0 value */
            SHRTIMER_STXCMP0V(shrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE1:
        {
            /* set the compare 1 value */
            SHRTIMER_STXCMP1V(shrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE2:
        {
            /* set the compare 2 value */
            SHRTIMER_STXCMP2V(shrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE3:
        {
            /* set the compare 3 value */
            SHRTIMER_STXCMP3V(shrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE0_COMPOSITE:
        {
            /* set the compare 0 composite value */
            SHRTIMER_STXCMP0CP(shrtimer_periph, timer_id) = cmpvalue;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get the compare value in Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  comparex: SHRTIMER_COMPAREy(y=0..3), SHRTIMER_COMPARE0_COMPOSITE
    \param[out] none
    \retval     the compare value
*/
uint32_t shrtimer_slavetimer_compare_value_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t comparex)
{
    uint32_t cmpval = 0U;
    /* configure the compare unit */
    switch (comparex)
    {
        case SHRTIMER_COMPARE0:
        {
            /* get the compare 0 value */
            cmpval = SHRTIMER_STXCMP0V(shrtimer_periph, timer_id);
        }
        break;
        case SHRTIMER_COMPARE1:
        {
            /* get the compare 1 value */
            cmpval = SHRTIMER_STXCMP1V(shrtimer_periph, timer_id);
        }
        break;
        case SHRTIMER_COMPARE2:
        {
            /* get the compare 2 value */
            cmpval = SHRTIMER_STXCMP2V(shrtimer_periph, timer_id);
        }
        break;
        case SHRTIMER_COMPARE3:
        {
            /* get the compare 3 value */
            cmpval = SHRTIMER_STXCMP3V(shrtimer_periph, timer_id);
        }
        break;
        case SHRTIMER_COMPARE0_COMPOSITE:
        {
            /* get the compare 0 composite value */
            cmpval = SHRTIMER_STXCMP0CP(shrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return cmpval;
}

/*!
    \brief      configure the compare value in Master_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  comparex: SHRTIMER_COMPAREy(y=0..3)
    \param[in]  cmpvalue: min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void shrtimer_mastertimer_compare_value_config(uint32_t shrtimer_periph, uint32_t comparex, uint32_t cmpvalue)
{
    /* configure the compare unit */
    switch (comparex)
    {
        case SHRTIMER_COMPARE0:
        {
            /* set the compare 0 value */
            SHRTIMER_MTCMP0V(shrtimer_periph) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE1:
        {
            /* set the compare 1 value */
            SHRTIMER_MTCMP1V(shrtimer_periph) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE2:
        {
            /* set the compare 2 value */
            SHRTIMER_MTCMP2V(shrtimer_periph) = cmpvalue;
        }
        break;
        case SHRTIMER_COMPARE3:
        {
            /* set the compare 3 value */
            SHRTIMER_MTCMP3V(shrtimer_periph) = cmpvalue;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get the compare value in Master_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  comparex: SHRTIMER_COMPAREy(y=0..3)
    \param[out] none
    \retval     the compare value
*/
uint32_t shrtimer_mastertimer_compare_value_get(uint32_t shrtimer_periph, uint32_t comparex)
{
    uint32_t cmpval = 0U;
    switch (comparex)
    {
        case SHRTIMER_COMPARE0:
        {
            /* get the compare 0 value */
            cmpval = SHRTIMER_MTCMP0V(shrtimer_periph);
        }
        break;
        case SHRTIMER_COMPARE1:
        {
            /* get the compare 1 value */
            cmpval = SHRTIMER_MTCMP1V(shrtimer_periph);
        }
        break;
        case SHRTIMER_COMPARE2:
        {
            /* get the compare 2 value */
            cmpval = SHRTIMER_MTCMP2V(shrtimer_periph);
        }
        break;
        case SHRTIMER_COMPARE3:
        {
            /* get the compare 3 value */
            cmpval = SHRTIMER_MTCMP3V(shrtimer_periph);
        }
        break;
        default:
        break;
    }
    return cmpval;
}

/*!
    \brief      configure the counter value in Master_TIMER and Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  cntvalue: min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void shrtimer_timers_counter_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t cntvalue)
{
    /* configure the counter */
    switch (timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
        {
            if(RESET == (SHRTIMER_MTCTL0(shrtimer_periph) & SHRTIMER_MTCTL0_MTCEN))
            {
                /* set the Master_TIMER counter value */
                SHRTIMER_MTCNT(shrtimer_periph) = cntvalue;
            }
        }
        break;
        case SHRTIMER_SLAVE_TIMER0:
        {
            if(RESET == (SHRTIMER_MTCTL0(shrtimer_periph) & SHRTIMER_MTCTL0_ST0CEN))
            {
                /* set the Slave_TIMER0 compare value */
                SHRTIMER_STXCNT(shrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case SHRTIMER_SLAVE_TIMER1:
        {
            if(RESET == (SHRTIMER_MTCTL0(shrtimer_periph) & SHRTIMER_MTCTL0_ST1CEN))
            {
                /* set the Slave_TIMER1 compare value */
                SHRTIMER_STXCNT(shrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case SHRTIMER_SLAVE_TIMER2:
        {
            if(RESET == (SHRTIMER_MTCTL0(shrtimer_periph) & SHRTIMER_MTCTL0_ST2CEN))
            {
                /* set the Slave_TIMER2 compare value */
                SHRTIMER_STXCNT(shrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case SHRTIMER_SLAVE_TIMER3:
        {
            if(RESET == (SHRTIMER_MTCTL0(shrtimer_periph) & SHRTIMER_MTCTL0_ST3CEN))
            {
                /* set the Slave_TIMER3 compare value */
                SHRTIMER_STXCNT(shrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        case SHRTIMER_SLAVE_TIMER4:
        {
            if(RESET == (SHRTIMER_MTCTL0(shrtimer_periph) & SHRTIMER_MTCTL0_ST4CEN))
            {
                /* set the Slave_TIMER4 counter value */
                SHRTIMER_STXCNT(shrtimer_periph, timer_id) = cntvalue;
            }
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get the counter value in Master_TIMER and Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[out] none
    \retval     the counter value
*/
uint32_t shrtimer_timers_counter_value_get(uint32_t shrtimer_periph, uint32_t timer_id)
{
    uint32_t cunval = 0U;

    switch (timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
        {
            /* get the Master_TIMER counter value */
            cunval = SHRTIMER_MTCNT(shrtimer_periph);
        }
        break;
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
        {
            /* get the Slave_TIMER counter value */
            cunval = SHRTIMER_STXCNT(shrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return cunval;
}

/*!
    \brief      configure the counter auto reload value in Master_TIMER and Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  carlvalue: min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
    \param[out] none
    \retval     none
*/
void shrtimer_timers_autoreload_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t carlvalue)
{
    /* configure the counter auto reload value */
    switch (timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
        {
            /* set the Master_TIMER counter value */
            SHRTIMER_MTCAR(shrtimer_periph) = carlvalue;
        }
        break;
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
        {
            /* set the Slave_TIMER compare value */
            SHRTIMER_STXCAR(shrtimer_periph, timer_id) = carlvalue;
        }
        break;
        default:
        break;
    }
}
/*!
    \brief      get the counter auto reload value in Master_TIMER and Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[out] none
    \retval     the counter auto reload value
*/
uint32_t shrtimer_timers_autoreload_value_get(uint32_t shrtimer_periph, uint32_t timer_id)
{
    uint32_t cralval = 0U;

    switch (timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
        {
            /* get the Master_TIMER counter auto reload value value */
            cralval = SHRTIMER_MTCAR(shrtimer_periph);
        }
        break;
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
        {
            /* get the Slave_TIMER counter auto reload value value */
            cralval = SHRTIMER_STXCAR(shrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return cralval;
}

/*!
    \brief      configure the counter repetition value in Master_TIMER and Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  replvalue: 0~255
    \param[out] none
    \retval     none
*/
void shrtimer_timers_repetition_value_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t replvalue)
{
    /* configure the counter repetition value */
    switch (timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
        {
            /* set the Master_TIMER repetition value */
            SHRTIMER_MTCREP(shrtimer_periph) = replvalue;
        }
        break;
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
        {
            /* set the Slave_TIMER repetition value */
            SHRTIMER_STXCREP(shrtimer_periph, timer_id) = replvalue;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      get the counter repetition value in Master_TIMER and Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[out] none
    \retval     the counter repetition value
*/
uint32_t shrtimer_timers_repetition_value_get(uint32_t shrtimer_periph, uint32_t timer_id)
{
    uint32_t repval = 0U;

    switch (timer_id)
    {
        case SHRTIMER_MASTER_TIMER:
        {
            /* get the Master_TIMER counter repetition value value */
            repval = SHRTIMER_MTCREP(shrtimer_periph);
        }
        break;
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
        {
            /* get the Slave_TIMER counter repetition value value */
            repval = SHRTIMER_STXCREP(shrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }
    return repval;
}

/*!
    \brief      initialize external event filtering for Slave_TIMER configuration struct with a default value
    \param[in]  exevfilter: external event filtering for Slave_TIMER struct definitions
    \param[out] none
    \retval     none
*/
void shrtimer_exevfilter_struct_para_init(shrtimer_exevfilter_parameter_struct * exevfilter)
{
    exevfilter->filter_mode = SHRTIMER_EXEVFILTER_DISABLE;
    exevfilter->memorized = SHRTIMER_EXEVMEMORIZED_DISABLE;
}

/*!
    \brief      configure the external event filtering for Slave_TIMER (blanking, windowing)
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  event_id: SHRTIMER_EXEVENT_NONE, SHRTIMER_EXEVENT_y(y=0..9)
    \param[in]  exevfilter: external event filtering for Slave_TIMER struct definitions
                  filter_mode: SHRTIMER_EXEVFILTER_DISABLE, SHRTIMER_EXEVFILTER_BLANKINGCMPy(y=0..3), SHRTIMER_EXEVFILTER_BLANKINGSRCy(y=0..7), SHRTIMER_EXEVFILTER_WINDOWINGCMPy(y=1,2), SHRTIMER_EXEVFILTER_WINDOWINGSRC
                  memorized: SHRTIMER_EXEVMEMORIZED_DISABLE, SHRTIMER_EXEVMEMORIZED_ENABLE
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_exevent_filtering_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t event_id, shrtimer_exevfilter_parameter_struct *exevfilter)
{
    uint32_t exevfcfg_reg;

    switch (event_id)
    {
        /* reset external event filtering */
        case SHRTIMER_EXEVENT_NONE:
        {
            SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id) = 0U;
            SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id) = 0U;
        }
        break;
        /* configure external event 0 filtering */
        case SHRTIMER_EXEVENT_0:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG0_EXEV0FM | SHRTIMER_STXEXEVFCFG0_EXEV0MEEN);
            exevfcfg_reg |= (exevfilter->filter_mode | exevfilter->memorized);
            SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 1 filtering */
        case SHRTIMER_EXEVENT_1:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG0_EXEV1FM | SHRTIMER_STXEXEVFCFG0_EXEV1MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 6);
            SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 2 filtering */
        case SHRTIMER_EXEVENT_2:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG0_EXEV2FM | SHRTIMER_STXEXEVFCFG0_EXEV2MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 12);
            SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 3 filtering */
        case SHRTIMER_EXEVENT_3:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG0_EXEV3FM | SHRTIMER_STXEXEVFCFG0_EXEV3MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 18);
            SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 4 filtering */
        case SHRTIMER_EXEVENT_4:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG0_EXEV4FM | SHRTIMER_STXEXEVFCFG0_EXEV4MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 24);
            SHRTIMER_STXEXEVFCFG0(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 5 filtering */
        case SHRTIMER_EXEVENT_5:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG1_EXEV5FM | SHRTIMER_STXEXEVFCFG1_EXEV5MEEN);
            exevfcfg_reg |= (exevfilter->filter_mode | exevfilter->memorized);
            SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 6 filtering */
        case SHRTIMER_EXEVENT_6:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG1_EXEV6FM | SHRTIMER_STXEXEVFCFG1_EXEV6MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 6);
            SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 7 filtering */
        case SHRTIMER_EXEVENT_7:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG1_EXEV7FM | SHRTIMER_STXEXEVFCFG1_EXEV7MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 12);
            SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 8 filtering */
        case SHRTIMER_EXEVENT_8:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG1_EXEV8FM | SHRTIMER_STXEXEVFCFG1_EXEV8MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 18);
            SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        /* configure external event 9 filtering */
        case SHRTIMER_EXEVENT_9:
        {
            exevfcfg_reg = SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id);
            exevfcfg_reg &= ~(SHRTIMER_STXEXEVFCFG1_EXEV9FM | SHRTIMER_STXEXEVFCFG1_EXEV9MEEN);
            exevfcfg_reg |= ((exevfilter->filter_mode | exevfilter->memorized) << 24);
            SHRTIMER_STXEXEVFCFG1(shrtimer_periph, timer_id) = exevfcfg_reg;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      initialize external event configuration struct with a default value
    \param[in]  exevcfg: external event configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_exeventcfg_struct_para_init(shrtimer_exeventcfg_parameter_struct * exevcfg)
{
    exevcfg->digital_filter = 0U;
    exevcfg->edge = SHRTIMER_EXEV_EDGE_LEVEL;
    exevcfg->polarity = SHRTIMER_EXEV_POLARITY_HIGH;
    exevcfg->source = SHRTIMER_EXEV_SRC0;
}

/*!
    \brief      configure the an external event
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  event_id: SHRTIMER_EXEVENT_NONE, SHRTIMER_EXEVENT_y(y=0..9)
    \param[in]  exevcfg: external event configuration struct
                  source: SHRTIMER_EXEV_SRCy(y=0..3)
                  polarity: SHRTIMER_EXEV_POLARITY_HIGH, SHRTIMER_EXEV_POLARITY_LOW
                  edge: SHRTIMER_EXEV_EDGE_LEVEL, SHRTIMER_EXEV_EDGE_RISING, SHRTIMER_EXEV_EDGE_FALLING, SHRTIMER_EXEV_EDGE_BOTH
                  digital_filter: 0x0~0xF
    \param[out] none
    \retval     none
*/
void shrtimer_exevent_config(uint32_t shrtimer_periph, uint32_t event_id, shrtimer_exeventcfg_parameter_struct* exevcfg)
{
    /* configure the an external event channel */
    external_event_config(shrtimer_periph, event_id, exevcfg);
}

/*!
    \brief      configure external event digital filter clock division
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  prescaler: clock division value
                only one parameter can be selected which is shown as below:
      \arg          SHRTIMER_EXEV_PRESCALER_DIV1: fSHRTIMER_EXEVFCK = fSHRTIMER_CK
      \arg          SHRTIMER_EXEV_PRESCALER_DIV2: fSHRTIMER_EXEVFCK = fSHRTIMER_CK / 2
      \arg          SHRTIMER_EXEV_PRESCALER_DIV4: fSHRTIMER_EXEVFCK = fSHRTIMER_CK / 4
      \arg          SHRTIMER_EXEV_PRESCALER_DIV8: fSHRTIMER_EXEVFCK = fSHRTIMER_CK / 8
    \param[out] none
    \retval     none
*/
void shrtimer_exevent_prescaler(uint32_t shrtimer_periph, uint32_t prescaler)
{
  uint32_t exevdfctl_reg;

  /* set the external event digital filter clock division */
  exevdfctl_reg = SHRTIMER_EXEVDFCTL(shrtimer_periph);
  exevdfctl_reg &= ~(SHRTIMER_EXEVDFCTL_EXEVFDIV);
  exevdfctl_reg |= prescaler;

  SHRTIMER_EXEVDFCTL(shrtimer_periph) = exevdfctl_reg;
}

/*!
    \brief      initialize synchronization configuration struct with a default value
    \param[in]  synccfg: synchronization configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_synccfg_struct_para_init(shrtimer_synccfg_parameter_struct* synccfg)
{
    synccfg->input_source = SHRTIMER_SYNCINPUTSOURCE_DISABLE;
    synccfg->output_polarity = SHRTIMER_SYNCOUTPUTPOLARITY_DISABLE;
    synccfg->output_source = SHRTIMER_SYNCOUTPUTSOURCE_MTSTART;
}

/*!
    \brief      configure the synchronization input/output of the SHRTIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  synccfg: synchronization configuration struct
                  input_source: SHRTIMER_SYNCINPUTSOURCE_DISABLE, SHRTIMER_SYNCINPUTSOURCE_INTERNAL, SHRTIMER_SYNCINPUTSOURCE_EXTERNAL
                  output_source: SHRTIMER_SYNCOUTPUTSOURCE_MTSTART, SHRTIMER_SYNCOUTPUTSOURCE_MTCMP0, SHRTIMER_SYNCOUTPUTSOURCE_ST0START, SHRTIMER_SYNCOUTPUTSOURCE_ST0CMP0
                  output_polarity: SHRTIMER_SYNCOUTPUTPOLARITY_DISABLE, SHRTIMER_SYNCOUTPUTPOLARITY_POSITIVE, SHRTIMER_SYNCOUTPUTPOLARITY_NEGATIVE
    \param[out] none
    \retval     none
*/
void shrtimer_synchronization_config(uint32_t shrtimer_periph, shrtimer_synccfg_parameter_struct* synccfg)
{
    uint32_t mtctl0_reg;

    mtctl0_reg = SHRTIMER_MTCTL0(shrtimer_periph);

    /* set the synchronization input source */
    mtctl0_reg &= ~(SHRTIMER_MTCTL0_SYNISRC);
    mtctl0_reg |= synccfg->input_source;

    /* set the event to be sent on the synchronization output */
    mtctl0_reg &= ~(SHRTIMER_MTCTL0_SYNOSRC);
    mtctl0_reg |= synccfg->output_source;

    /* set the polarity of the synchronization output */
    mtctl0_reg &= ~(SHRTIMER_MTCTL0_SYNOPLS);
    mtctl0_reg |= synccfg->output_polarity;

    SHRTIMER_MTCTL0(shrtimer_periph) = mtctl0_reg;
}

/*!
    \brief      initialize fault input configuration struct with a default value
    \param[in]  faultcfg: fault input configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_faultcfg_struct_para_init(shrtimer_faultcfg_parameter_struct * faultcfg)
{
    faultcfg->filter = 0x0U;
    faultcfg->polarity = SHRTIMER_FAULT_POLARITY_LOW;
    faultcfg->protect = SHRTIMER_FAULT_PROTECT_DISABLE;
    faultcfg->source = SHRTIMER_FAULT_SOURCE_PIN;
    faultcfg->control = SHRTIMER_FAULT_CHANNEL_DISABLE;
}

/*!
    \brief      configure the fault input
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  fault_id: SHRTIMER_FAULT_y(y=0..4)
    \param[in]  faultcfg: fault input configuration struct
                  source: SHRTIMER_FAULT_SOURCE_PIN, SHRTIMER_FAULT_SOURCE_INTERNAL
                  polarity: SHRTIMER_FAULT_POLARITY_LOW, SHRTIMER_FAULT_POLARITY_HIGH
                  control: SHRTIMER_FAULT_CHANNEL_DISABLE, SHRTIMER_FAULT_CHANNEL_ENABLE
                  filter: 0x0~0xF
                  protect: SHRTIMER_FAULT_PROTECT_DISABLE, SHRTIMER_FAULT_PROTECT_ENABLE
    \param[out] none
    \retval     none
*/
void shrtimer_fault_config(uint32_t shrtimer_periph, uint32_t fault_id, shrtimer_faultcfg_parameter_struct* faultcfg)
{
    uint32_t fltincfg0;
    uint32_t fltincfg1;

    fltincfg0 = SHRTIMER_FLTINCFG0(shrtimer_periph);
    fltincfg1 = SHRTIMER_FLTINCFG1(shrtimer_periph);

    switch (fault_id)
    {
        case SHRTIMER_FAULT_0:
        {
            /* configure fault input 0 */
            fltincfg0 &= ~( SHRTIMER_FLTINCFG0_FLT0INP | SHRTIMER_FLTINCFG0_FLT0INSRC | SHRTIMER_FLTINCFG0_FLT0INFC | SHRTIMER_FLTINCFG0_FLT0INPROT | SHRTIMER_FLTINCFG0_FLT0INEN);
            fltincfg0 |= faultcfg->source;
            fltincfg0 |= faultcfg->polarity;
            fltincfg0 |= ((faultcfg->filter) << 3);
            fltincfg0 |= faultcfg->control;
            fltincfg0 |= faultcfg->protect;
        }
        break;
        case SHRTIMER_FAULT_1:
        {
            /* configure fault input 1 */
            fltincfg0 &= ~( SHRTIMER_FLTINCFG0_FLT1INP | SHRTIMER_FLTINCFG0_FLT1INSRC | SHRTIMER_FLTINCFG0_FLT1INFC | SHRTIMER_FLTINCFG0_FLT1INPROT | SHRTIMER_FLTINCFG0_FLT1INEN );
            fltincfg0 |= ((faultcfg->source) << 8);
            fltincfg0 |= ((faultcfg->polarity) << 8);
            fltincfg0 |= ((faultcfg->filter) << 11);
            fltincfg0 |= ((faultcfg->control) << 8);
            fltincfg0 |= ((faultcfg->protect) << 8);
        }
        break;
        case SHRTIMER_FAULT_2:
        {
            /* configure fault input 2 */
            fltincfg0 &= ~( SHRTIMER_FLTINCFG0_FLT2INP | SHRTIMER_FLTINCFG0_FLT2INSRC | SHRTIMER_FLTINCFG0_FLT2INFC | SHRTIMER_FLTINCFG0_FLT2INPROT | SHRTIMER_FLTINCFG0_FLT2INEN);
            fltincfg0 |= ((faultcfg->source) << 16);
            fltincfg0 |= ((faultcfg->polarity) << 16);
            fltincfg0 |= ((faultcfg->filter) << 19);
            fltincfg0 |= ((faultcfg->control) << 16);
            fltincfg0 |= ((faultcfg->protect) << 16);
        }
        break;
        case SHRTIMER_FAULT_3:
        {
            /* configure fault input 3 */
            fltincfg0 &= ~( SHRTIMER_FLTINCFG0_FLT3INP | SHRTIMER_FLTINCFG0_FLT3INSRC | SHRTIMER_FLTINCFG0_FLT3INFC | SHRTIMER_FLTINCFG0_FLT3INPROT | SHRTIMER_FLTINCFG0_FLT3INEN);
            fltincfg0 |= ((faultcfg->source) << 24);
            fltincfg0 |= ((faultcfg->polarity) << 24);
            fltincfg0 |= ((faultcfg->filter) << 27);
            fltincfg0 |= ((faultcfg->control) << 24);
            fltincfg0 |= ((faultcfg->protect) << 24);
        }
        break;
        case SHRTIMER_FAULT_4:
        {
            /* configure fault input 4 */
            fltincfg1 &= ~( SHRTIMER_FLTINCFG1_FLT4INP | SHRTIMER_FLTINCFG1_FLT4INSRC | SHRTIMER_FLTINCFG1_FLT4INFC | SHRTIMER_FLTINCFG1_FLT4INPROT | SHRTIMER_FLTINCFG1_FLT4INEN);
            fltincfg1 |= faultcfg->source;
            fltincfg1 |= faultcfg->polarity;
            fltincfg1 |= ((faultcfg->filter) << 3);
            fltincfg1 |= (faultcfg->control);
            fltincfg1 |= faultcfg->protect;
        }
        break;
        default:
        break;
    }

    SHRTIMER_FLTINCFG0(shrtimer_periph) = fltincfg0;
    SHRTIMER_FLTINCFG1(shrtimer_periph) = fltincfg1;
}

/*!
    \brief      configure the fault input digital filter clock division
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  prescaler: clock division value
                only one parameter can be selected which is shown as below:
      \arg          SHRTIMER_FAULT_PRESCALER_DIV1: fSHRTIMER_FLTFCK = fSHRTIMER_CK
      \arg          SHRTIMER_FAULT_PRESCALER_DIV2: fSHRTIMER_FLTFCK = fSHRTIMER_CK / 2
      \arg          SHRTIMER_EFAULT_PRESCALER_DIV4: fSHRTIMER_FLTFCK = fSHRTIMER_CK / 4
      \arg          SHRTIMER_FAULT_PRESCALER_DIV8: fSHRTIMER_FLTFCK = fSHRTIMER_CK / 8
    \param[out] none
    \retval     none
*/
void shrtimer_fault_prescaler_config(uint32_t shrtimer_periph, uint32_t prescaler)
{
    uint32_t fltincfg1;

    /* configure digital filter clock division */
    fltincfg1 = SHRTIMER_FLTINCFG1(shrtimer_periph);
    fltincfg1 &= ~(SHRTIMER_FLTINCFG1_FLTFDIV);
    fltincfg1 |= prescaler;
    SHRTIMER_FLTINCFG1(shrtimer_periph) = fltincfg1;
}

/*!
    \brief      fault input enable
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  fault_id: SHRTIMER_FAULT_y(y=0..4)
    \param[out] none
    \retval     none
*/
void shrtimer_fault_input_enable(uint32_t shrtimer_periph, uint32_t fault_id)
{
    uint32_t fltincfg0;
    uint32_t fltincfg1;

    fltincfg0 = SHRTIMER_FLTINCFG0(shrtimer_periph);
    fltincfg1 = SHRTIMER_FLTINCFG1(shrtimer_periph);

    switch (fault_id)
    {
        case SHRTIMER_FAULT_0:
        {
            /* configure fault input 0 */
            fltincfg0 |= SHRTIMER_FLTINCFG0_FLT0INEN;
        }
        break;
        case SHRTIMER_FAULT_1:
        {
            /* configure fault input 1 */
            fltincfg0 |= SHRTIMER_FLTINCFG0_FLT1INEN;
        }
        break;
        case SHRTIMER_FAULT_2:
        {
            /* configure fault input 2 */
            fltincfg0 |= SHRTIMER_FLTINCFG0_FLT2INEN;
        }
        break;
        case SHRTIMER_FAULT_3:
        {
            /* configure fault input 3 */
            fltincfg0 |= SHRTIMER_FLTINCFG0_FLT3INEN;
        }
        break;
        case SHRTIMER_FAULT_4:
        {
            /* configure fault input 4 */
            fltincfg1 |= SHRTIMER_FLTINCFG1_FLT4INEN;
        }
        break;
        default:
        break;
    }

    SHRTIMER_FLTINCFG0(shrtimer_periph) = fltincfg0;
    SHRTIMER_FLTINCFG1(shrtimer_periph) = fltincfg1;
}

/*!
    \brief      fault input disable
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  fault_id: SHRTIMER_FAULT_y(y=0..4)
    \param[out] none
    \retval     none
*/
void shrtimer_fault_input_disable(uint32_t shrtimer_periph, uint32_t fault_id)
{
    uint32_t fltincfg0;
    uint32_t fltincfg1;

    fltincfg0 = SHRTIMER_FLTINCFG0(shrtimer_periph);
    fltincfg1 = SHRTIMER_FLTINCFG1(shrtimer_periph);

    switch (fault_id)
    {
        case SHRTIMER_FAULT_0:
        {
            /* configure fault input 0 */
            fltincfg0 &= ~SHRTIMER_FLTINCFG0_FLT0INEN;
        }
        break;
        case SHRTIMER_FAULT_1:
        {
            /* configure fault input 1 */
            fltincfg0 &= ~SHRTIMER_FLTINCFG0_FLT1INEN;
        }
        break;
        case SHRTIMER_FAULT_2:
        {
            /* configure fault input 2 */
            fltincfg0 &= ~SHRTIMER_FLTINCFG0_FLT2INEN;
        }
        break;
        case SHRTIMER_FAULT_3:
        {
            /* configure fault input 3 */
            fltincfg0 &= ~SHRTIMER_FLTINCFG0_FLT3INEN;
        }
        break;
        case SHRTIMER_FAULT_4:
        {
            /* configure fault input 4 */
            fltincfg1 &= ~SHRTIMER_FLTINCFG1_FLT4INEN;
        }
        break;
        default:
        break;
    }

    SHRTIMER_FLTINCFG0(shrtimer_periph) = fltincfg0;
    SHRTIMER_FLTINCFG1(shrtimer_periph) = fltincfg1;
}

/*!
    \brief      enable the Master_TIMER and Slave_TIMER DMA request
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  dmareq: DMA request source
                only one parameter can be selected which is shown as below:
      \arg          SHRTIMER_MT_ST_DMA_CMP0: compare 0 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_CMP1: compare 1 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_CMP2: compare 2 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_CMP3: compare 3 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_REP: repetition DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_DMA_SYNID: synchronization input DMA request, for Master_TIMER
      \arg          SHRTIMER_MT_ST_DMA_UPD: update DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CAP0: capture 0 DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CAP0: capture 1 DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH0OA: channel 0 output active DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH0ONA: channel 0 output inactive DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH1OA: channel 1 output active DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH1ONA: channel 1 output inactive DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CNTRST: counter reset DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_DLYIDLE: delay IDLE DMA request, for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_timers_dma_enable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t dmareq)
{
    switch(timer_id)
    {
        /* enable the Master_TIMER request */
        case SHRTIMER_MASTER_TIMER:
            SHRTIMER_MTDMAINTEN(shrtimer_periph) |= dmareq;
        break;
        /* enable the Slave_TIMER DMA request */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            SHRTIMER_STXDMAINTEN(shrtimer_periph, timer_id) |= dmareq;
        break;

        default:
        break;
    }
}

/*!
    \brief      disable the Master_TIMER and Slave_TIMER DMA request
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  dmareq: DMA request source
                only one parameter can be selected which is shown as below:
      \arg          SHRTIMER_MT_ST_DMA_CMP0: compare 0 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_CMP1: compare 1 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_CMP2: compare 2 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_CMP3: compare 3 DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_ST_DMA_REP: repetition DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_MT_DMA_SYNID: synchronization input DMA request, for Master_TIMER
      \arg          SHRTIMER_MT_ST_DMA_UPD: update DMA request, for Master_TIMER and Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CAP0: capture 0 DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CAP0: capture 1 DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH0OA: channel 0 output active DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH0ONA: channel 0 output inactive DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH1OA: channel 1 output active DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CH1ONA: channel 1 output inactive DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_CNTRST: counter reset DMA request, for Slave_TIMER
      \arg          SHRTIMER_ST_DMA_DLYIDLE: delay IDLE DMA request, for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_timers_dma_disable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t dmareq)
{
    switch(timer_id)
    {
        /* disable the Master_TIMER request */
        case SHRTIMER_MASTER_TIMER:
            SHRTIMER_MTDMAINTEN(shrtimer_periph) &= ~dmareq;
        break;
        /* disable the Slave_TIMER request */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            SHRTIMER_STXDMAINTEN(shrtimer_periph, timer_id) &= ~dmareq;
        break;

        default:
        break;
    }
}

/*!
    \brief      configure the DMA mode for Master_TIMER or Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  regupdate: registers to be updated
                one or more parameters can be selected which is shown as below:
      \arg         SHRTIMER_DMAMODE_NONE: No register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CTL0: MTCTL0 or STxCTL0 register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_INTC: MT or STx register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_DMAINTEN: MTINTC or STxINTC register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CNT: MTCNT or STxCNT register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CAR: MTCAR or STxCAR register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CREP: MTCREP or STxCREP register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CMP0V: MTCMP0V or STxCMP0V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CMP1V: MTCMP1V or STxCMP1V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CMP2V: MTCMP2V or STxCMP2V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CMP3V: MTCMP3V or STxCMP3V register is updated by DMA mode, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_DMAMODE_DTCTL: STxDTCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CH0SET: STxCH0SET register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CH0RST: STxCH0RST register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CH1SET: STxCH1SET register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CH1RST: STxCH1RST register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_EXEVFCFG0: STxEXEVFCFG0 register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_EXEVFCFG1: STxEXEVFCFG1 register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CNTRST: STxCNTRST register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CSCTL: STxCSCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_CHOCTL: STxCHOCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_FLTCTL: STxFLTCTL register is updated by DMA mode, only for Slave_TIMER
      \arg         SHRTIMER_DMAMODE_ACTL: STxACTL register is updated by DMA mode, only for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_dmamode_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t regupdate)
{
    switch (timer_id)
    {
        /* set the DMA mode update Slave_TIMER0 registers */
        case SHRTIMER_SLAVE_TIMER0:
        {
            SHRTIMER_DMAUPST0R(shrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER1 registers */
        case SHRTIMER_SLAVE_TIMER1:
        {
            SHRTIMER_DMAUPST1R(shrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER2 registers */
        case SHRTIMER_SLAVE_TIMER2:
        {
            SHRTIMER_DMAUPST2R(shrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Slave_TIMER3 registers */
        case SHRTIMER_SLAVE_TIMER3:
        {
            SHRTIMER_DMAUPST3R(shrtimer_periph) = regupdate;
        }
        /* set the DMA mode update Slave_TIMER4 registers */
        break;
        case SHRTIMER_SLAVE_TIMER4:
        {
            SHRTIMER_DMAUPST4R(shrtimer_periph) = regupdate;
        }
        break;
        /* set the DMA mode update Master_TIMER registers */
        case SHRTIMER_MASTER_TIMER:
        {
            SHRTIMER_DMAUPMTR(shrtimer_periph) = regupdate;
        }
        break;
        default:
        break;
    }
}

/*!
    \brief      initialize bunch mode configuration struct with a default value
    \param[in]  bmcfg: bunch mode configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_bunchmode_struct_para_init(shrtimer_bunchmode_parameter_struct* bmcfg)
{
    bmcfg->clock_source = SHRTIMER_BUNCHMODE_CLOCKSOURCE_MASTER;
    bmcfg->idle_duration = 0U;
    bmcfg->mode = SHRTIMER_BUNCHMODE_SINGLE;
    bmcfg->period = 0U;
    bmcfg->prescaler = SHRTIMER_BUNCHMODE_PRESCALER_DIV1;
    bmcfg->shadow = SHRTIMER_BUNCHMODEPRELOAD_DISABLED;
    bmcfg->trigger = SHRTIMER_BUNCHMODE_TRIGGER_NONE;
}

/*!
    \brief      configure bunch mode for the SHRTIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  bmcfg: bunch mode configuration struct
                  mode: SHRTIMER_BUNCHMODE_SINGLE, SHRTIMER_BUNCHMODE_CONTINOUS
                  clock_source: SHRTIMER_BUNCHMODE_CLOCKSOURCE_MASTER, SHRTIMER_BUNCHMODE_CLOCKSOURCE_STy(y=0..4), SHRTIMER_BUNCHMODE_CLOCKSOURCE_TIMER6_TRGO, SHRTIMER_BUNCHMODE_CLOCKSOURCE_SHRTIMERCK
                  prescaler: SHRTIMER_BUNCHMODE_PRESCALER_DIVy(y=1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768)
                  shadow: SHRTIMER_BUNCHMODEPRELOAD_DISABLED, SHRTIMER_BUNCHMODEPRELOAD_ENABLED
                  trigger: SHRTIMER_BUNCHMODE_TRIGGER_NONE, SHRTIMER_BUNCHMODE_TRIGGER_MTRESET, SHRTIMER_BUNCHMODE_TRIGGER_MTREPETITION, SHRTIMER_BUNCHMODE_TRIGGER_MTCMPy(y=0..3),
                           SHRTIMER_BUNCHMODE_TRIGGER_STxRESET(x=0..4), SHRTIMER_BUNCHMODE_TRIGGER_STxREPETITION(x=0..4), SHRTIMER_BUNCHMODE_TRIGGER_STxCMPy(x=0..4, y=0,1), SHRTIMER_BUNCHMODE_TRIGGER_ST0EVENT6,
                           SHRTIMER_BUNCHMODE_TRIGGER_ST3EVENT7, SHRTIMER_BUNCHMODE_TRIGGER_EVENT6, SHRTIMER_BUNCHMODE_TRIGGER_EVENT7, SHRTIMER_BUNCHMODE_TRIGGER_CHIP
                  idle_duration: 0x0000~0xFFFF
                  period: 0x0001~0xFFFF
    \param[out] none
    \retval     none
*/
void shrtimer_bunchmode_config(uint32_t shrtimer_periph, shrtimer_bunchmode_parameter_struct* bmcfg)
{
    uint32_t bmctl_reg;

    bmctl_reg = SHRTIMER_BMCTL(shrtimer_periph);

    /* set the bunch mode operating mode */
    bmctl_reg &= ~(SHRTIMER_BMCTL_BMCTN);
    bmctl_reg |= bmcfg->mode;

    /* set the bunch mode clock source */
    bmctl_reg &= ~(SHRTIMER_BMCTL_BMCLKS);
    bmctl_reg |= bmcfg->clock_source;

    /* set the bunch mode prescaler */
    bmctl_reg &= ~(SHRTIMER_BMCTL_BMPSC);
    bmctl_reg |= bmcfg->prescaler;

    /* enable/disable bunch mode shadow registers */
    bmctl_reg &= ~(SHRTIMER_BMCTL_BMSE);
    bmctl_reg |= bmcfg->shadow;

    /* set the bunch mode trigger */
    SHRTIMER_BMSTRG(shrtimer_periph) = bmcfg->trigger;

    /* set the bunch mode compare value */
    SHRTIMER_BMCMPV(shrtimer_periph) = bmcfg->idle_duration;

    /* set the bunch mode period */
    SHRTIMER_BMCAR(shrtimer_periph) = bmcfg->period;

    SHRTIMER_BMCTL(shrtimer_periph) = bmctl_reg;
}

/*!
    \brief      enable bunch mode for the SHRTIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[out] none
    \retval     none
*/
void shrtimer_bunchmode_enable(uint32_t shrtimer_periph)
{
    SHRTIMER_BMCTL(shrtimer_periph) |= SHRTIMER_BMCTL_BMEN;
}

/*!
    \brief      disable bunch mode for the SHRTIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[out] none
    \retval     none
*/
void shrtimer_bunchmode_disable(uint32_t shrtimer_periph)
{
    SHRTIMER_BMCTL(shrtimer_periph) &= ~SHRTIMER_BMCTL_BMEN;
}

/*!
    \brief      get bunch mode operating flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[out] none
    \retval     bunch mode operating state
*/
uint32_t shrtimer_bunchmode_flag_get(uint32_t shrtimer_periph)
{
    uint32_t val = SHRTIMER_BUNCHMODE_OPERATION_OFF;
    /* judge bunch mode operating state */
    if(RESET != (SHRTIMER_BMCTL(shrtimer_periph) & SHRTIMER_BMCTL_BMOPTF))
    {
        val = SHRTIMER_BUNCHMODE_OPERATION_ON;
    }else{
        val = SHRTIMER_BUNCHMODE_OPERATION_OFF;
    }
    return val;
}

/*!
    \brief      bunch mode started by software
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[out] none
    \retval     bunch mode operating state
*/
void shrtimer_bunchmode_software_start(uint32_t shrtimer_periph)
{
    SHRTIMER_BMSTRG(shrtimer_periph) |= SHRTIMER_BMSTRG_SWTRG;
}

/*!
    \brief      configure the capture source in Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  capturex: SHRTIMER_CAPTURE_y(y=0, 1)
    \param[in]  trgsource: capture source
                one or more parameters can be selected which is shown as below:
      \arg         SHRTIMER_CAPTURETRIGGER_NONE: Capture trigger is disabled
      \arg         SHRTIMER_CAPTURETRIGGER_UPDATE: capture triggered by update event
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_0: capture triggered by external event 0
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_1: capture triggered by external event 1
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_2: capture triggered by external event 2
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_3: capture triggered by external event 3
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_4: capture triggered by external event 4
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_5: capture triggered by external event 5
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_6: capture triggered by external event 6
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_7: capture triggered by external event 7
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_8: capture triggered by external event 8
      \arg         SHRTIMER_CAPTURETRIGGER_EXEV_9: capture triggered by external event 9
      \arg         SHRTIMER_CAPTURETRIGGER_ST0_ACTIVE: capture triggered by ST0CH0_O output inactive to active transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST0_INACTIVE: capture triggered by ST0CH0_O output active to inactive transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST0_CMP0: capture triggered by compare 0 event of Slave_TIMER0
      \arg         SHRTIMER_CAPTURETRIGGER_ST0_CMP1: capture triggered by compare 1 event of Slave_TIMER0
      \arg         SHRTIMER_CAPTURETRIGGER_ST1_ACTIVE: capture triggered by ST1CH0_O output inactive to active transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST1_INACTIVE: capture triggered by ST1CH0_O output active to inactive transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST1_CMP0: capture triggered by compare 0 event of Slave_TIMER1
      \arg         SHRTIMER_CAPTURETRIGGER_ST1_CMP1: capture triggered by compare 1 event of Slave_TIMER1
      \arg         SHRTIMER_CAPTURETRIGGER_ST2_ACTIVE: capture triggered by ST2CH0_O output inactive to active transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST2_INACTIVE: capture triggered by ST2CH0_O output active to inactive transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST2_CMP0: capture triggered by compare 0 event of Slave_TIMER2
      \arg         SHRTIMER_CAPTURETRIGGER_ST2_CMP1: capture triggered by compare 1 event of Slave_TIMER2
      \arg         SHRTIMER_CAPTURETRIGGER_ST3_ACTIVE: capture triggered by ST3CH0_O output inactive to active transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST3_INACTIVE: capture triggered by ST3CH0_O output active to inactive transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST3_CMP0: capture triggered by compare 0 event of Slave_TIMER3
      \arg         SHRTIMER_CAPTURETRIGGER_ST3_CMP1: capture triggered by compare 1 event of Slave_TIMER3
      \arg         SHRTIMER_CAPTURETRIGGER_ST4_ACTIVE: capture triggered by ST4CH0_O output inactive to active transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST4_INACTIVE: capture triggered by ST4CH0_O output active to inactive transition
      \arg         SHRTIMER_CAPTURETRIGGER_ST4_CMP0: capture triggered by compare 0 event of Slave_TIMER4
      \arg         SHRTIMER_CAPTURETRIGGER_ST4_CMP1: capture triggered by compare 1 event of Slave_TIMER4
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_capture_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t capturex, uint32_t trgsource)
{
    switch (capturex)
    {
        /* configure the capture 0 unit */
        case SHRTIMER_CAPTURE_0:
        {
            SHRTIMER_STXCAP0TRG(shrtimer_periph, timer_id) = trgsource;
        }
        break;
        /* configure the capture 1 unit */
        case SHRTIMER_CAPTURE_1:
        {
            SHRTIMER_STXCAP1TRG(shrtimer_periph, timer_id) = trgsource;
        }
        break;
        default:
        break;
  }
}

/*!
    \brief      configure the capture source in Slave_TIMER
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  capturex: SHRTIMER_CAPTURE_y(y=0, 1)
    \param[out] none
    \retval     none
*/
void shrtimer_slavetimer_capture_software(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t capturex)
{
    switch (capturex)
    {
        /* configure the capture 0 unit */
        case SHRTIMER_CAPTURE_0:
        {
            SHRTIMER_STXCAP0TRG(shrtimer_periph, timer_id) |= SHRTIMER_STXCAP0TRG_CP0BSW;
        }
        break;
        /* configure the capture 1 unit */
        case SHRTIMER_CAPTURE_1:
        {
            SHRTIMER_STXCAP1TRG(shrtimer_periph, timer_id) |= SHRTIMER_STXCAP1TRG_CP1BSW;
        }
        break;
        default:
        break;
  }
}

/*!
    \brief      read the capture value
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  capturex: SHRTIMER_CAPTURE_y(y=0, 1)
    \param[out] none
    \retval     capture value
*/
uint32_t shrtimer_slavetimer_capture_value_read(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t capturex)
{
    uint32_t cap_val = 0;

    switch (capturex)
    {
        /* read capture 0 value */
        case SHRTIMER_CAPTURE_0:
        {
          cap_val = SHRTIMER_STXCAP0V(shrtimer_periph, timer_id);
        }
        break;
        /* read capture 1 value */
        case SHRTIMER_CAPTURE_1:
        {
          cap_val = SHRTIMER_STXCAP1V(shrtimer_periph, timer_id);
        }
        break;
        default:
        break;
    }

    return cap_val;
}

/*!
    \brief      initialize ADC trigger configuration struct with a default value
    \param[in]  triggercfg: ADC trigger configuration struct
    \param[out] none
    \retval     none
*/
void shrtimer_adctrigcfg_struct_para_init(shrtimer_adctrigcfg_parameter_struct* triggercfg)
{
    triggercfg->trigger = SHRTIMER_ADCTRGI02_EVENT_NONE;
    triggercfg->update_source = SHRTIMER_ADCTRGI_UPDATE_MT;
}

/*!
    \brief      configure the trigger source to ADC and the update source
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  trigger_id: SHRTIMER_ADCTRIG_y(y=0..3)
    \param[in]  triggercfg: ADC trigger configuration struct
                  update_source: SHRTIMER_ADCTRGI_UPDATE_MT, SHRTIMER_ADCTRGI_UPDATE_STx(x=0..4)
                  trigger:
                    for SHRTIMER_ADCTRIG0 and SHRTIMER_ADCTRIG2:
                           SHRTIMER_ADCTRGI02_EVENT_NONE, SHRTIMER_ADCTRGI02_EVENT_MTCMPy(y=0..3),
                           SHRTIMER_ADCTRGI02_EVENT_MTPER, SHRTIMER_ADCTRGI02_EVENT_EXEVy(y=0..4),
                           SHRTIMER_ADCTRGI02_EVENT_STxCMPy(x=0..4,y=1..3),
                           SHRTIMER_ADCTRGI02_EVENT_STxPER(x=0..4), SHRTIMER_ADCTRGI02_EVENT_ST0xRST(x=0,1)
                    for SHRTIMER_ADCTRIG1 and SHRTIMER_ADCTRIG3:
                           SHRTIMER_ADCTRGI13_EVENT_NONE, SHRTIMER_ADCTRGI13_EVENT_MTCMPy(y=0..3), SHRTIMER_ADCTRGI13_EVENT_MTPER,
                           SHRTIMER_ADCTRGI13_EVENT_EXEVy(y=5..9),  SHRTIMER_ADCTRGI13_EVENT_STxCMPy(x=0..4, y=1..3),
                           SHRTIMER_ADCTRGI13_EVENT_STxPER(x=0..3), SHRTIMER_ADCTRGI13_EVENT_STxRST(x=2..4)
    \param[out] none
    \retval     none
*/
void shrtimer_adc_trigger_config(uint32_t shrtimer_periph, uint32_t trigger_id, shrtimer_adctrigcfg_parameter_struct* triggercfg)
{
    uint32_t comctl0_reg;

    comctl0_reg = SHRTIMER_CTL0(shrtimer_periph);
    switch (trigger_id)
    {
        /* configure the ADC trigger 0 */
        case SHRTIMER_ADCTRIG_0:
        {
            /* configure update source */
            comctl0_reg &= ~(SHRTIMER_CTL0_ADTG0USRC);
            comctl0_reg |= triggercfg->update_source;

            /* set the SHRTIMER_ADCTRIG0 source */
            SHRTIMER_ADCTRIGS0(shrtimer_periph) = triggercfg->trigger;
        }
        break;
        /* configure the ADC trigger 1 */
        case SHRTIMER_ADCTRIG_1:
        {
            /* configure update source */
            comctl0_reg &= ~(SHRTIMER_CTL0_ADTG1USRC);
            comctl0_reg |= ((triggercfg->update_source) << 3);

            /* set the SHRTIMER_ADCTRIG1 source */
            SHRTIMER_ADCTRIGS1(shrtimer_periph) = triggercfg->trigger;
        }
        break;
        /* configure the ADC trigger 2 */
        case SHRTIMER_ADCTRIG_2:
        {
            /* configure update source */
            comctl0_reg &= ~(SHRTIMER_CTL0_ADTG2USRC);
            comctl0_reg |= ((triggercfg->update_source) << 6);

            /* set the SHRTIMER_ADCTRIG2 source */
            SHRTIMER_ADCTRIGS2(shrtimer_periph) = triggercfg->trigger;
        }
        break;
        /* configure the ADC trigger 3 */
        case SHRTIMER_ADCTRIG_3:
        {
            /* configure update source */
            comctl0_reg &= ~(SHRTIMER_CTL0_ADTG3USRC);
            comctl0_reg |= ((triggercfg->update_source) << 9);

            /* set the SHRTIMER_ADCTRIG3 source */
            SHRTIMER_ADCTRIGS3(shrtimer_periph) = triggercfg->trigger;
        }
        break;
        default:
        break;
    }

    SHRTIMER_CTL0(shrtimer_periph) = comctl0_reg;
}

/*!
    \brief      get the Master_TIMER and Slave_TIMER flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_MT_ST_FLAG_CMP0: compare 0 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_CMP1: compare 1 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_CMP2: compare 2 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_CMP3: compare 3 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_REP: repetition flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_FLAG_SYNI: synchronization input flag, for Master_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_UPD: update flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CAP0: capture 0 flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CAP1: capture 1 flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH0OA: channel 0 output active flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH0ONA: channel 0 output inactive flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH1OA: channel 1 output active flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH1ONA: channel 1 output inactive flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CNTRST: counter reset flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_DLYIDLE: delayed IDLE mode entry flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CBLN: current balanced flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_BLNIDLE: balanced IDLE flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH0OUT: channel 0 output flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH1OUT: channel 1 output flag, for Slave_TIMER
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus shrtimer_timers_flag_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t flag)
{
    FlagStatus flag_val = RESET;
    switch(timer_id)
    {
        /* get the Master_TIMER flag */
        case SHRTIMER_MASTER_TIMER:
            if(RESET != (SHRTIMER_MTINTF(shrtimer_periph) & flag))
            {
                flag_val = SET;
            }else{
                flag_val = RESET;
            }
        break;
        /* get the Slave_TIMER flag */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            if(RESET != (SHRTIMER_STXINTF(shrtimer_periph, timer_id) & flag))
            {
                flag_val = SET;
            }else{
                flag_val = RESET;
            }
        break;

        default:
        break;
    }
    return flag_val;
}

/*!
    \brief      clear the Master_TIMER and Slave_TIMER flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_MT_ST_FLAG_CMP0: compare 0 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_CMP1: compare 1 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_CMP2: compare 2 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_CMP3: compare 3 flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_REP: repetition flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_FLAG_SYNI: synchronization input flag, for Master_TIMER
      \arg         SHRTIMER_MT_ST_FLAG_UPD: update flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CAP0: capture 0 flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CAP1: capture 1 flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH0OA: channel 0 output active flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH0ONA: channel 0 output inactive flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH1OA: channel 1 output active flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH1ONA: channel 1 output inactive flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CNTRST: counter reset flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_DLYIDLE: delayed IDLE mode entry flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CBLN: current balanced flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_BLNIDLE: balanced IDLE flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH0OUT: channel 0 output flag, for Slave_TIMER
      \arg         SHRTIMER_ST_FLAG_CH1OUT: channel 1 output flag, for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_timers_flag_clear(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t flag)
{
    switch(timer_id)
    {
        /* clear the Master_TIMER flag */
        case SHRTIMER_MASTER_TIMER:
            SHRTIMER_MTINTC(shrtimer_periph) |= flag;
        break;
        /* clear the Slave_TIMER flag */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            SHRTIMER_STXINTC(shrtimer_periph, timer_id) |= flag;
        break;
        default:
        break;
    }
}

/*!
    \brief      get the common interrupt flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_FLAG_FLT0: fault 0 flag
      \arg         SHRTIMER_FLAG_FLT1: fault 1 flag
      \arg         SHRTIMER_FLAG_FLT2: fault 2 flag
      \arg         SHRTIMER_FLAG_FLT3: fault 3 flag
      \arg         SHRTIMER_FLAG_FLT4: fault 4 flag
      \arg         SHRTIMER_FLAG_SYSFLT: system fault flag
      \arg         SHRTIMER_FLAG_DLLCAL: DLL calibration completed flag
      \arg         SHRTIMER_FLAG_BMPER: bunch mode period flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus shrtimer_common_flag_get(uint32_t shrtimer_periph, uint32_t flag)
{
    /* judge interrupt status */
    if(RESET != (SHRTIMER_INTF(shrtimer_periph) & flag))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the common interrupt flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  flag: flag source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_FLAG_FLT0: fault 0 flag
      \arg         SHRTIMER_FLAG_FLT1: fault 1 flag
      \arg         SHRTIMER_FLAG_FLT2: fault 2 flag
      \arg         SHRTIMER_FLAG_FLT3: fault 3 flag
      \arg         SHRTIMER_FLAG_FLT4: fault 4 flag
      \arg         SHRTIMER_FLAG_SYSFLT: system fault flag
      \arg         SHRTIMER_FLAG_DLLCAL: DLL calibration completed flag
      \arg         SHRTIMER_FLAG_BMPER: bunch mode period flag
    \param[out] none
    \retval     none
*/
void shrtimer_common_flag_clear(uint32_t shrtimer_periph, uint32_t flag)
{
    SHRTIMER_INTC(shrtimer_periph) |= flag;
}

/*!
    \brief      enable the Master_TIMER and Slave_TIMER interrupt
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_MT_ST_INT_CMP0: compare 0 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_CMP1: compare 1 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_CMP2: compare 2 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_CMP3: compare 3 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_REP: repetition interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_INT_SYNI: synchronization input interrupt, for Master_TIMER
      \arg         SHRTIMER_MT_ST_INT_UPD: update interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_ST_INT_CAP0: capture 0 interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CAP1: capture 1 interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH0OA: channel 0 output active interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH0ONA: channel 0 output inactive interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH1OA: channel 1 output active interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH1ONA: channel 1 output inactive interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CNTRST: counter reset interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_DLYIDLE: delayed IDLE mode entry interrupt, for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_timers_interrupt_enable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    switch(timer_id)
    {
        /* enable the Master_TIMER interrupt */
        case SHRTIMER_MASTER_TIMER:
            SHRTIMER_MTDMAINTEN(shrtimer_periph) |= interrupt;
        break;
        /* enable the Slave_TIMER interrupt */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            SHRTIMER_STXDMAINTEN(shrtimer_periph, timer_id) |= interrupt;
        break;

        default:
        break;
    }
}
/*!
    \brief      disable the Master_TIMER and Slave_TIMER interrupt
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_MT_ST_INT_CMP0: compare 0 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_CMP1: compare 1 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_CMP2: compare 2 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_CMP3: compare 3 interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_REP: repetition interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_INT_SYNI: synchronization input interrupt, for Master_TIMER
      \arg         SHRTIMER_MT_ST_INT_UPD: update interrupt, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_ST_INT_CAP0: capture 0 interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CAP1: capture 1 interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH0OA: channel 0 output active interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH0ONA: channel 0 output inactive interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH1OA: channel 1 output active interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CH1ONA: channel 1 output inactive interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_CNTRST: counter reset interrupt, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_DLYIDLE: delayed IDLE mode entry interrupt, for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_timers_interrupt_disable(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    switch(timer_id)
    {
        /* disable the Master_TIMER interrupt */
        case SHRTIMER_MASTER_TIMER:
            SHRTIMER_MTDMAINTEN(shrtimer_periph) &= ~interrupt;
        break;
        /* disable the Slave_TIMER interrupt */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            SHRTIMER_STXDMAINTEN(shrtimer_periph, timer_id) &= ~interrupt;
        break;

        default:
        break;
    }
}

/*!
    \brief      get the Master_TIMER and Slave_TIMER interrupt flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP0: compare 0 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP1: compare 1 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP2: compare 2 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP3: compare 3 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_REP: repetition interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_INT_FLAG_SYNI: synchronization input interrupt flag, for Master_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_UPD: update interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CAP0: capture 0 interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CAP1: capture 1 interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH0OA: channel 0 output active interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH0ONA: channel 0 output inactive interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH1OA: channel 1 output active interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH1ONA: channel 1 output inactive interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CNTRST: counter reset interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_DLYIDLE: delayed IDLE mode entry interrupt flag, for Slave_TIMER
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus shrtimer_timers_interrupt_flag_get(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    FlagStatus flag = RESET;
    uint32_t interflag = 0U;
    uint32_t interen = 0U;

    switch(timer_id)
    {
        /* get the Master_TIMER interrupt flag */
        case SHRTIMER_MASTER_TIMER:
            interflag = (SHRTIMER_MTINTF(shrtimer_periph) & interrupt);
            interen = (SHRTIMER_MTDMAINTEN(shrtimer_periph) & interrupt);
            if((RESET != interflag) && (RESET != interen))
            {
                flag = SET;
            }else{
                flag =  RESET;
            }
        break;
        /* get the Slave_TIMER interrupt flag */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            interflag = (SHRTIMER_STXINTF(shrtimer_periph, timer_id) & interrupt);
            interen = (SHRTIMER_STXDMAINTEN(shrtimer_periph, timer_id) & interrupt);
            if((RESET != interflag) && (RESET != interen))
            {
                flag =  SET;
            }else{
                flag =  RESET;
            }
        break;

        default:
        break;
    }
    return flag;
}

/*!
    \brief      clear the Master_TIMER and Slave_TIMER interrupt flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_MASTER_TIMER, SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP0: compare 0 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP1: compare 1 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP2: compare 2 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_CMP3: compare 3 interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_REP: repetition interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_MT_INT_FLAG_SYNI: synchronization input interrupt flag, for Master_TIMER
      \arg         SHRTIMER_MT_ST_INT_FLAG_UPD: update interrupt flag, for Master_TIMER and Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CAP0: capture 0 interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CAP1: capture 1 interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH0OA: channel 0 output active interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH0ONA: channel 0 output inactive interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH1OA: channel 1 output active interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CH1ONA: channel 1 output inactive interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_CNTRST: counter reset interrupt flag, for Slave_TIMER
      \arg         SHRTIMER_ST_INT_FLAG_DLYIDLE: delayed IDLE mode entry interrupt flag, for Slave_TIMER
    \param[out] none
    \retval     none
*/
void shrtimer_timers_interrupt_flag_clear(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t interrupt)
{
    switch(timer_id)
    {
        /* clear the Master_TIMER interrupt flag */
        case SHRTIMER_MASTER_TIMER:
            SHRTIMER_MTINTC(shrtimer_periph) |= interrupt;
        break;
        /* clear theSlave_TIMER interrupt flag */
        case SHRTIMER_SLAVE_TIMER0:
        case SHRTIMER_SLAVE_TIMER1:
        case SHRTIMER_SLAVE_TIMER2:
        case SHRTIMER_SLAVE_TIMER3:
        case SHRTIMER_SLAVE_TIMER4:
            SHRTIMER_STXINTC(shrtimer_periph, timer_id) |= interrupt;
        break;

        default:
        break;
    }
}

/*!
    \brief      enable SHRTIMER common interrupt
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_INT_SYSFLT: system fault interrupt
      \arg         SHRTIMER_INT_DLLCAL: DLL calibration completed interrupt
      \arg         SHRTIMER_INT_BMPER: bunch mode period interrupt
    \param[out] none
    \retval     none
*/
void shrtimer_common_interrupt_enable(uint32_t shrtimer_periph, uint32_t interrupt)
{
    SHRTIMER_INTEN(shrtimer_periph) |= interrupt;
}

/*!
    \brief      disable SHRTIMER common interrupt
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_INT_FLT0: fault 0 interrupt
      \arg         SHRTIMER_INT_FLT1: fault 1 interrupt
      \arg         SHRTIMER_INT_FLT2: fault 2 interrupt
      \arg         SHRTIMER_INT_FLT3: fault 3 interrupt
      \arg         SHRTIMER_INT_FLT4: fault 4 interrupt
      \arg         SHRTIMER_INT_SYSFLT: system fault interrupt
      \arg         SHRTIMER_INT_DLLCAL: DLL calibration completed interrupt
      \arg         SHRTIMER_INT_BMPER: bunch mode period interrupt
    \param[out] none
    \retval     none
*/
void shrtimer_common_interrupt_disable(uint32_t shrtimer_periph, uint32_t interrupt)
{
    SHRTIMER_INTEN(shrtimer_periph) &= ~interrupt;
}

/*!
    \brief      get the common interrupt flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_INT_FLAG_FLT0: fault 0 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT1: fault 1 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT2: fault 2 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT3: fault 3 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT4: fault 4 interrupt flag
      \arg         SHRTIMER_INT_FLAG_SYSFLT: system fault interrupt flag
      \arg         SHRTIMER_INT_FLAG_DLLCAL: DLL calibration completed interrupt flag
      \arg         SHRTIMER_INT_FLAG_BMPER: bunch mode period interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus shrtimer_common_interrupt_flag_get(uint32_t shrtimer_periph, uint32_t interrupt)
{
    uint32_t interflag = 0U;
    uint32_t interen = 0U;

    /* get the interrupt correlation bit value */
    interflag = (SHRTIMER_INTF(shrtimer_periph) & interrupt);
    interen = (SHRTIMER_INTEN(shrtimer_periph) & interrupt);

    /* get the interrupt flag */
    if((RESET != interflag) && (RESET != interen))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the common interrupt flag
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  interrupt: interrupt source
                only one parameter can be selected which is shown as below:
      \arg         SHRTIMER_INT_FLAG_FLT0: fault 0 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT1: fault 1 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT2: fault 2 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT3: fault 3 interrupt flag
      \arg         SHRTIMER_INT_FLAG_FLT4: fault 4 interrupt flag
      \arg         SHRTIMER_INT_FLAG_SYSFLT: system fault interrupt flag
      \arg         SHRTIMER_INT_FLAG_DLLCAL: DLL calibration completed interrupt flag
      \arg         SHRTIMER_INT_FLAG_BMPER: bunch mode period interrupt flag
    \param[out] none
    \retval     none
*/
void shrtimer_common_interrupt_flag_clear(uint32_t shrtimer_periph, uint32_t interrupt)
{
    SHRTIMER_INTC(shrtimer_periph) |= interrupt;
}

/*!
    \brief      configure Master_TIMER timer base
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  master_baseinit: SHRTIMER time base parameters struct
                  period: period value, min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
                  repetitioncounter: the counter repetition value, 0x00~0xFF
                  prescaler: SHRTIMER_PRESCALER_MULy(y=64,32,16,8,4,2),SHRTIMER_PRESCALER_DIVy(y=1,2,4)
                  counter_mode: SHRTIMER_COUNTER_MODE_CONTINOUS, SHRTIMER_COUNTER_MODE_SINGLEPULSE, SHRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE
    \param[out] none
    \retval     none
*/
static void master_timer_base_config(uint32_t shrtimer_periph, shrtimer_baseinit_parameter_struct* master_baseinit)
{
    /* set counter clock division */
    SHRTIMER_MTCTL0(shrtimer_periph) &= (uint32_t) ~(SHRTIMER_MTCTL0_CNTCKDIV2_0);
    SHRTIMER_MTACTL(shrtimer_periph) &= (uint32_t) ~(SHRTIMER_MTACTL_CNTCKDIV3);
    SHRTIMER_MTCTL0(shrtimer_periph) |= (uint32_t)((master_baseinit->prescaler) & CNTCKDIV2_0_MASK);
    SHRTIMER_MTACTL(shrtimer_periph) |= (uint32_t)((master_baseinit->prescaler) & CNTCKDIV3_MASK);

    /* set the counter operating mode */
    SHRTIMER_MTCTL0(shrtimer_periph) &= (uint32_t) ~(SHRTIMER_STXCTL0_CTNM | SHRTIMER_STXCTL0_CNTRSTM);
    SHRTIMER_MTCTL0(shrtimer_periph) |= (uint32_t)master_baseinit->counter_mode;

    /* set the period and repetition registers */
    SHRTIMER_MTCAR(shrtimer_periph) = master_baseinit->period;
    SHRTIMER_MTCREP(shrtimer_periph) = master_baseinit->repetitioncounter;
}

/*!
    \brief      configure Master_TIMER in waveform mode
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  master_timerinit: waveform mode initialization parameters
                  half_mode: SHRTIMER_HALFMODE_DISABLED, SHRTIMER_HALFMODE_ENABLED
                  start_sync: SHRTIMER_SYNISTART_DISABLED, SHRTIMER_SYNISTART_ENABLED
                  reset_sync: SHRTIMER_SYNCRESET_DISABLED, SHRTIMER_SYNCRESET_ENABLED
                  dac_trigger: SHRTIMER_DAC_TRIGGER_NONE, SHRTIMER_DAC_TRIGGER_DACTRIGy(y=0..2)
                  shadow: SHRTIMER_SHADOW_DISABLED, SHRTIMER_SHADOW_ENABLED
                  update_selection: SHRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT, SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE, SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE
                  cnt_bunch: SHRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK, SHRTIMER_TIMERBUNCHMODE_RESETCOUNTER
                  repetition_update: SHRTIMER_UPDATEONREPETITION_DISABLED, SHRTIMER_UPDATEONREPETITION_ENABLED
    \param[out] none
    \retval     none
*/
static void master_timer_waveform_config(uint32_t shrtimer_periph, shrtimer_timerinit_parameter_struct * master_timerinit)
{
    uint32_t mtctl0_reg;
    uint32_t bmctl_reg;

    mtctl0_reg = SHRTIMER_MTCTL0(shrtimer_periph);
    bmctl_reg = SHRTIMER_BMCTL(shrtimer_periph);

    /* configure the half mode */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_HALFM);
    mtctl0_reg |= master_timerinit->half_mode;

    /* configure synchronization input start counter */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_SYNISTRT);
    mtctl0_reg |= master_timerinit->start_sync;

    /* configure synchronization input reset counter */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_SYNIRST);
    mtctl0_reg |= master_timerinit->reset_sync;

    /* configure trigger source to DAC */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_DACTRGS);
    mtctl0_reg |= master_timerinit->dac_trigger;

    /* enable/disable shadow registers */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_SHWEN);
    mtctl0_reg |= master_timerinit->shadow;

    /* update event selection */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_UPSEL);
    mtctl0_reg |= (master_timerinit->update_selection << 2);

    /* enable/disable registers update on repetition event */
    mtctl0_reg &= ~(uint32_t)(SHRTIMER_MTCTL0_UPREP);
    mtctl0_reg |= (master_timerinit->repetition_update);

    /* set the timer bunch mode */
    bmctl_reg &= ~(SHRTIMER_BMCTL_BMMT);
    bmctl_reg |= master_timerinit->cnt_bunch;

    SHRTIMER_MTCTL0(shrtimer_periph) = mtctl0_reg;
    SHRTIMER_BMCTL(shrtimer_periph) = bmctl_reg;
}

/*!
    \brief      configure Slave_TIMER timer base
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  slave_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  slave_baseinit: SHRTIMER time base parameters struct
                  period: period value, min value: 3*tSHRTIMER_CK clock, max value: 0xFFFF �C (1*tSHRTIMER_CK)
                  repetitioncounter: the counter repetition value, 0x00~0xFF
                  prescaler: SHRTIMER_PRESCALER_MULy(y=64,32,16,8,4,2),SHRTIMER_PRESCALER_DIVy(y=1,2,4)
                  counter_mode: SHRTIMER_COUNTER_MODE_CONTINOUS, SHRTIMER_COUNTER_MODE_SINGLEPULSE, SHRTIMER_COUNTER_MODE_SINGLEPULSE_RETRIGGERABLE
    \param[out] none
    \retval     none
*/
static void slave_timer_base_config(uint32_t shrtimer_periph, uint32_t slave_id, shrtimer_baseinit_parameter_struct* slave_baseinit)
{
    /* set counter clock division */
    SHRTIMER_STXCTL0(shrtimer_periph, slave_id) &= (uint32_t) ~(SHRTIMER_MTCTL0_CNTCKDIV2_0);
    SHRTIMER_STXACTL(shrtimer_periph, slave_id) &= (uint32_t) ~(SHRTIMER_MTACTL_CNTCKDIV3);
    SHRTIMER_STXCTL0(shrtimer_periph, slave_id) |= (uint32_t)((slave_baseinit->prescaler) & CNTCKDIV2_0_MASK);
    SHRTIMER_STXACTL(shrtimer_periph, slave_id) |= (uint32_t)((slave_baseinit->prescaler) & CNTCKDIV3_MASK);

    /* set the counter operating mode */
    SHRTIMER_STXCTL0(shrtimer_periph, slave_id) &= (uint32_t) ~(SHRTIMER_STXCTL0_CTNM | SHRTIMER_STXCTL0_CNTRSTM);
    SHRTIMER_STXCTL0(shrtimer_periph, slave_id) |= (uint32_t)slave_baseinit->counter_mode;

    /* set the period and repetition registers */
    SHRTIMER_STXCAR(shrtimer_periph, slave_id) = slave_baseinit->period;
    SHRTIMER_STXCREP(shrtimer_periph, slave_id) = slave_baseinit->repetitioncounter;
}

/*!
    \brief      configure Slave_TIMER in waveform mode
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  slave_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  slave_timerinit: waveform mode initialization parameters
                  half_mode: SHRTIMER_HALFMODE_DISABLED, SHRTIMER_HALFMODE_ENABLED
                  start_sync: SHRTIMER_SYNISTART_DISABLED, SHRTIMER_SYNISTART_ENABLED
                  reset_sync: SHRTIMER_SYNCRESET_DISABLED, SHRTIMER_SYNCRESET_ENABLED
                  dac_trigger: SHRTIMER_DAC_TRIGGER_NONE, SHRTIMER_DAC_TRIGGER_DACTRIGy(y=0..2)
                  shadow: SHRTIMER_SHADOW_DISABLED, SHRTIMER_SHADOW_ENABLED
                  update_selection: SHRTIMER_MT_ST_UPDATE_SELECTION_INDEPENDENT, for Master_TIMER and Slave_TIMER
                                    SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE,  for Master_TIMER and Slave_TIMER
                                    SHRTIMER_MT_ST_UPDATE_SELECTION_DMAMODE_UPDATE, for Master_TIMER and Slave_TIMER
                                    SHRTIMER_ST_UPDATE_SELECTION_STXUPINy(y=2), for Slave_TIMER
                                    SHRTIMER_ST_UPDATE_SELECTION_STXUPINy_UPDATE(y=2), for Slave_TIMER
                  cnt_bunch: SHRTIMER_TIMERBUNCHNMODE_MAINTAINCLOCK, SHRTIMER_TIMERBUNCHMODE_RESETCOUNTER
                  repetition_update: SHRTIMER_UPDATEONREPETITION_DISABLED, SHRTIMER_UPDATEONREPETITION_ENABLED
    \param[out] none
    \retval     none
*/
static void slave_timer_waveform_config(uint32_t shrtimer_periph, uint32_t slave_id, shrtimer_timerinit_parameter_struct * slave_timerinit)
{
    uint32_t stxctl0_reg;
    uint32_t bmctl_reg;

    stxctl0_reg = SHRTIMER_STXCTL0(shrtimer_periph, slave_id);
    bmctl_reg = SHRTIMER_BMCTL(shrtimer_periph);

    /* configure the half mode */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_HALFM);
    stxctl0_reg |= slave_timerinit->half_mode;

    /* configure synchronization input start counter */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_SYNISTRT);
    stxctl0_reg |= slave_timerinit->start_sync;

    /* configure synchronization input reset counter */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_SYNIRST);
    stxctl0_reg |= slave_timerinit->reset_sync;

    /* configure trigger source to DAC */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_DACTRGS);
    stxctl0_reg |= slave_timerinit->dac_trigger;

    /* enable/disable shadow registers */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_SHWEN);
    stxctl0_reg |= slave_timerinit->shadow;

    /* update event selection */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_UPSEL);
    stxctl0_reg |= (slave_timerinit->update_selection);

    /* enable/disable registers update on repetition event */
    stxctl0_reg &= ~(uint32_t)(SHRTIMER_STXCTL0_UPREP);
    if(SHRTIMER_UPDATEONREPETITION_ENABLED == slave_timerinit->repetition_update)
    {
        stxctl0_reg |= (SHRTIMER_STXCTL0_UPREP);
    }

    /* Set the timer bunch mode */
    switch (slave_id)
    {
        case SHRTIMER_SLAVE_TIMER0:
        {
            bmctl_reg &= ~(SHRTIMER_BMCTL_BMST0);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 1);
        }
        break;
        case SHRTIMER_SLAVE_TIMER1:
        {
            bmctl_reg &= ~(SHRTIMER_BMCTL_BMST1);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 2);
        }
        break;
        case SHRTIMER_SLAVE_TIMER2:
        {
            bmctl_reg &= ~(SHRTIMER_BMCTL_BMST2);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 3);
        }
        break;
        case SHRTIMER_SLAVE_TIMER3:
        {
            bmctl_reg &= ~(SHRTIMER_BMCTL_BMST3);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 4);
        }
        break;
        case SHRTIMER_SLAVE_TIMER4:
        {
            bmctl_reg &= ~(SHRTIMER_BMCTL_BMST4);
            bmctl_reg |= (slave_timerinit->cnt_bunch << 5);
        }
        break;
        default:
        break;
    }

    SHRTIMER_STXCTL0(shrtimer_periph, slave_id) = stxctl0_reg;
    SHRTIMER_BMCTL(shrtimer_periph) = bmctl_reg;
}

/*!
    \brief      configure the an external event channel
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  event_id: SHRTIMER_EXEVENT_NONE, SHRTIMER_EXEVENT_y(y=0..9)
    \param[in]  eventcfg: external event configuration struct
                  source: SHRTIMER_EXEV_SRCy(y=0..3)
                  polarity: SHRTIMER_EXEV_POLARITY_HIGH, SHRTIMER_EXEV_POLARITY_LOW
                  edge: SHRTIMER_EXEV_EDGE_LEVEL, SHRTIMER_EXEV_EDGE_RISING, SHRTIMER_EXEV_EDGE_FALLING, SHRTIMER_EXEV_EDGE_BOTH
                  digital_filter: 0x0~0xF
    \param[out] none
    \retval     none
*/
static void external_event_config(uint32_t shrtimer_periph, uint32_t event_id, shrtimer_exeventcfg_parameter_struct* eventcfg)
{
    uint32_t exevcfg0_reg;
    uint32_t exevcfg1_reg;
    uint32_t exevdfctl_reg;

    exevcfg0_reg = SHRTIMER_EXEVCFG0(shrtimer_periph);
    exevcfg1_reg = SHRTIMER_EXEVCFG1(shrtimer_periph);
    exevdfctl_reg = SHRTIMER_EXEVDFCTL(shrtimer_periph);

    switch (event_id)
    {
        case SHRTIMER_EXEVENT_0:
        {
            /* configure external event 0 */
            exevcfg0_reg &= ~(SHRTIMER_EXEVCFG0_EXEV0SRC | SHRTIMER_EXEVCFG0_EXEV0P | SHRTIMER_EXEVCFG0_EXEV0EG);
            exevcfg0_reg |= eventcfg->source;
            exevcfg0_reg |= eventcfg->polarity;
            exevcfg0_reg |= eventcfg->edge;
            SHRTIMER_EXEVCFG0(shrtimer_periph) = exevcfg0_reg;
        }
        break;
        case SHRTIMER_EXEVENT_1:
        {
            /* configure external event 1 */
            exevcfg0_reg &= ~(SHRTIMER_EXEVCFG0_EXEV1SRC | SHRTIMER_EXEVCFG0_EXEV1P | SHRTIMER_EXEVCFG0_EXEV1EG);
            exevcfg0_reg |= ((eventcfg->source) << 6);
            exevcfg0_reg |= ((eventcfg->polarity) << 6);
            exevcfg0_reg |= ((eventcfg->edge) << 6);
            SHRTIMER_EXEVCFG0(shrtimer_periph) = exevcfg0_reg;
        }
        break;
        case SHRTIMER_EXEVENT_2:
        {
            /* configure external event 2 */
            exevcfg0_reg &= ~(SHRTIMER_EXEVCFG0_EXEV2SRC | SHRTIMER_EXEVCFG0_EXEV2P | SHRTIMER_EXEVCFG0_EXEV2EG);
            exevcfg0_reg |= ((eventcfg->source) << 12);
            exevcfg0_reg |= ((eventcfg->polarity) << 12);
            exevcfg0_reg |= ((eventcfg->edge) << 12);
            SHRTIMER_EXEVCFG0(shrtimer_periph) = exevcfg0_reg;
        }
        break;
        case SHRTIMER_EXEVENT_3:
        {
            /* configure external event 3 */
            exevcfg0_reg &= ~(SHRTIMER_EXEVCFG0_EXEV3SRC | SHRTIMER_EXEVCFG0_EXEV3P | SHRTIMER_EXEVCFG0_EXEV3EG);
            exevcfg0_reg |= ((eventcfg->source) << 18);
            exevcfg0_reg |= ((eventcfg->polarity) << 18);
            exevcfg0_reg |= ((eventcfg->edge) << 18);
            SHRTIMER_EXEVCFG0(shrtimer_periph) = exevcfg0_reg;
        }
        break;
        case SHRTIMER_EXEVENT_4:
        {
            /* configure external event 4 */
            exevcfg0_reg &= ~(SHRTIMER_EXEVCFG0_EXEV4SRC | SHRTIMER_EXEVCFG0_EXEV4P | SHRTIMER_EXEVCFG0_EXEV4EG);
            exevcfg0_reg |= ((eventcfg->source) << 24);
            exevcfg0_reg |= ((eventcfg->polarity) << 24);
            exevcfg0_reg |= ((eventcfg->edge) << 24);
            SHRTIMER_EXEVCFG0(shrtimer_periph) = exevcfg0_reg;
        }
        break;
        case SHRTIMER_EXEVENT_5:
        {
            /* configure external event 5 */
            exevcfg1_reg &= ~(SHRTIMER_EXEVCFG1_EXEV5SRC | SHRTIMER_EXEVCFG1_EXEV5P | SHRTIMER_EXEVCFG1_EXEV5EG);
            exevcfg1_reg |= (eventcfg->source);
            exevcfg1_reg |= (eventcfg->polarity);
            exevcfg1_reg |= (eventcfg->edge);
            exevdfctl_reg &= ~(SHRTIMER_EXEVDFCTL_EXEV5FC);
            exevdfctl_reg |= (eventcfg->digital_filter);
            SHRTIMER_EXEVCFG1(shrtimer_periph) = exevcfg1_reg;
            SHRTIMER_EXEVDFCTL(shrtimer_periph) = exevdfctl_reg;
        }
        break;
        case SHRTIMER_EXEVENT_6:
        {
            /* configure external event 6 */
            exevcfg1_reg &= ~(SHRTIMER_EXEVCFG1_EXEV6SRC | SHRTIMER_EXEVCFG1_EXEV6P | SHRTIMER_EXEVCFG1_EXEV6EG);
            exevcfg1_reg |= ((eventcfg->source) << 6);
            exevcfg1_reg |= ((eventcfg->polarity) << 6);
            exevcfg1_reg |= ((eventcfg->edge) << 6);
            exevdfctl_reg &= ~(SHRTIMER_EXEVDFCTL_EXEV6FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 6);
            SHRTIMER_EXEVCFG1(shrtimer_periph) = exevcfg1_reg;
            SHRTIMER_EXEVDFCTL(shrtimer_periph) = exevdfctl_reg;
        }
        break;
        case SHRTIMER_EXEVENT_7:
        {
            /* configure external event 7 */
            exevcfg1_reg &= ~(SHRTIMER_EXEVCFG1_EXEV7SRC | SHRTIMER_EXEVCFG1_EXEV7P | SHRTIMER_EXEVCFG1_EXEV7EG);
            exevcfg1_reg |= ((eventcfg->source) << 12);
            exevcfg1_reg |= ((eventcfg->polarity) << 12);
            exevcfg1_reg |= ((eventcfg->edge) << 12);
            exevdfctl_reg &= ~(SHRTIMER_EXEVDFCTL_EXEV7FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 12);
            SHRTIMER_EXEVCFG1(shrtimer_periph) = exevcfg1_reg;
            SHRTIMER_EXEVDFCTL(shrtimer_periph) = exevdfctl_reg;
        }
        break;
        case SHRTIMER_EXEVENT_8:
        {
            /* configure external event 8 */
            exevcfg1_reg &= ~(SHRTIMER_EXEVCFG1_EXEV8SRC | SHRTIMER_EXEVCFG1_EXEV8P | SHRTIMER_EXEVCFG1_EXEV8EG);
            exevcfg1_reg |= ((eventcfg->source) << 18);
            exevcfg1_reg |= ((eventcfg->polarity) << 18);
            exevcfg1_reg |= ((eventcfg->edge) << 18);
            exevdfctl_reg &= ~(SHRTIMER_EXEVDFCTL_EXEV8FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 18);
            SHRTIMER_EXEVCFG1(shrtimer_periph) = exevcfg1_reg;
            SHRTIMER_EXEVDFCTL(shrtimer_periph) = exevdfctl_reg;
        }
        break;
        case SHRTIMER_EXEVENT_9:
        {
            /* configure external event 9 */
            exevcfg1_reg &= ~(SHRTIMER_EXEVCFG1_EXEV9SRC | SHRTIMER_EXEVCFG1_EXEV9P | SHRTIMER_EXEVCFG1_EXEV9EG);
            exevcfg1_reg |= ((eventcfg->source) << 24);
            exevcfg1_reg |= ((eventcfg->polarity) << 24);
            exevcfg1_reg |= ((eventcfg->edge) << 24);
            exevdfctl_reg &= ~(SHRTIMER_EXEVDFCTL_EXEV9FC);
            exevdfctl_reg |= ((eventcfg->digital_filter) << 24);
            SHRTIMER_EXEVCFG1(shrtimer_periph) = exevcfg1_reg;
            SHRTIMER_EXEVDFCTL(shrtimer_periph) = exevdfctl_reg;
        }
        break;
        default:
        break;
    }
}


/*!
    \brief      configure the channel output
    \param[in]  shrtimer_periph: SHRTIMER0
    \param[in]  timer_id: SHRTIMER_SLAVE_TIMERx(x=0..4)
    \param[in]  channel: SHRTIMER_STx_CHy(x=0..4,y=0,1)
    \param[in]  outcfg: channel output configuration struct definitions
                  polarity: SHRTIMER_CHANNEL_POLARITY_HIGH, SHRTIMER_CHANNEL_POLARITY_LOW
                  set_request: SHRTIMER_CHANNEL_SET_NONE, SHRTIMER_CHANNEL_SET_RSTSYNI, SHRTIMER_CHANNEL_SET_PER, SHRTIMER_CHANNEL_SET_CMPy(y=0..3),
                               SHRTIMER_CHANNEL_SET_MTPER, SHRTIMER_CHANNEL_SET_MTCMPy(y=0..3), SHRTIMER_CHANNEL_SET_STEVy(y=0..8),
                               SHRTIMER_CHANNEL_SET_EXEVy(y=0..9), SHRTIMER_CHANNEL_SET_UPDATE
                  reset_request: SHRTIMER_CHANNEL_RESET_NONE, SHRTIMER_CHANNEL_RESET_RSTSYNI, SHRTIMER_CHANNEL_RESET_PER, SHRTIMER_CHANNEL_RESET_CMPy(y=0..3),
                               SHRTIMER_CHANNEL_RESET_MTPER, SHRTIMER_CHANNEL_RESET_MTCMPy(y=0..3), SHRTIMER_CHANNEL_RESET_STEVy(y=0..8),
                               SHRTIMER_CHANNEL_RESET_EXEVy(y=0..9), SHRTIMER_CHANNEL_RESET_UPDATE
                  idle_bunch: SHRTIMER_CHANNEL_BUNCH_IDLE_DISABLE, SHRTIMER_CHANNEL_BUNCH_IDLE_ENABLE
                  idle_state: SHRTIMER_CHANNEL_IDLESTATE_INACTIVE, SHRTIMER_CHANNEL_IDLESTATE_ACTIVE
                  fault_state: SHRTIMER_CHANNEL_FAULTSTATE_NONE, SHRTIMER_CHANNEL_FAULTSTATE_ACTIVE, SHRTIMER_CHANNEL_FAULTSTATE_INACTIVE, SHRTIMER_CHANNEL_FAULTSTATE_HIGHZ
                  carrier_mode: SHRTIMER_CHANNEL_CARRIER_DISABLED, SHRTIMER_CHANNEL_CARRIER_ENABLED
                  deadtime_bunch: SHRTIMER_CHANNEL_BUNCH_ENTRY_REGULAR, SHRTIMER_CHANNEL_BUNCH_ENTRY_DEADTIME
    \param[out] none
    \retval     none
*/
static void channel_output_config(uint32_t shrtimer_periph, uint32_t timer_id, uint32_t channel, shrtimer_channel_outputcfg_parameter_struct * outcfg)
{
    uint32_t stxchoctl_reg;
    uint32_t shift = 0U;

    stxchoctl_reg = SHRTIMER_STXCHOCTL(shrtimer_periph, timer_id);
    /* configure the output set/reset crossbar */
    switch (channel)
    {
        case SHRTIMER_ST0_CH0:
        case SHRTIMER_ST1_CH0:
        case SHRTIMER_ST2_CH0:
        case SHRTIMER_ST3_CH0:
        case SHRTIMER_ST4_CH0:
        {
            shift = 0U;
            SHRTIMER_STXCH0SET(shrtimer_periph, timer_id) = outcfg->set_request;
            SHRTIMER_STXCH0RST(shrtimer_periph, timer_id) = outcfg->reset_request;
        }
        break;
        case SHRTIMER_ST0_CH1:
        case SHRTIMER_ST1_CH1:
        case SHRTIMER_ST2_CH1:
        case SHRTIMER_ST3_CH1:
        case SHRTIMER_ST4_CH1:
        {
            shift = 16U;
            SHRTIMER_STXCH1SET(shrtimer_periph, timer_id) = outcfg->set_request;
            SHRTIMER_STXCH1RST(shrtimer_periph, timer_id) = outcfg->reset_request;
        }
        break;
        default:
        break;
    }

    /* clear output config */
    stxchoctl_reg &= ~((SHRTIMER_STXCHOCTL_CH0P | SHRTIMER_STXCHOCTL_BMCH0IEN | SHRTIMER_STXCHOCTL_ISO0 | SHRTIMER_STXCHOCTL_CH0FLTOS|\
                     SHRTIMER_STXCHOCTL_CH0CSEN | SHRTIMER_STXCHOCTL_BMCH0DTI)  << shift);

    /* config the polarity */
    stxchoctl_reg |= (outcfg->polarity << shift);

    /* channel IDLE enable state config in bunch mode */
    stxchoctl_reg |= (outcfg->idle_bunch << shift);

    /* config channel output IDLE state */
    stxchoctl_reg |= (outcfg->idle_state << shift);

    /* config the FAULT output state */
    stxchoctl_reg |= (outcfg->fault_state << shift);

    /* config the channel carrier-signal mode enable state */
    stxchoctl_reg |= (outcfg->carrier_mode << shift);

    /* config channel dead-time insert in bunch mode */
    stxchoctl_reg |= (outcfg->deadtime_bunch << shift);

    SHRTIMER_STXCHOCTL(shrtimer_periph, timer_id) = stxchoctl_reg;
}

#endif /* GD32EPRT */
