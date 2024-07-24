/*!
    \file    gd32h7xx_lpdts.c
    \brief   LPDTS driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#include "gd32h7xx_lpdts.h"

/* LPDTS high threshold value offset macro */
#define LPDTS_IT_INTHT_OFFSET      ((uint32_t)16U)
/* sampling time offset macro */
#define LPDTS_CFG_SPT_OFFSET       ((uint32_t)16U)
/* engineering value offset macro */
#define LPDTS_SDATA_VAL_OFFSET     ((uint32_t)16U)
/* the T0 temperature macro */
#define LPDTS_T0_TMP_VAL           ((uint32_t)25U)

/*!
    \brief      reset the LPDTS registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_deinit(void)
{
    rcu_periph_reset_enable(RCU_LPDTSRST);
    rcu_periph_reset_disable(RCU_LPDTSRST);
}

/*!
    \brief      initialize the parameters of LPDTS struct with the default values
    \param[in]  none
    \param[out] init_struct: the initialization data needed to initialize LPDTS
    \retval     none
*/
void lpdts_struct_para_init(lpdts_parameter_struct *init_struct)
{
    /* set the struct with the default values */
    init_struct->ref_clock          = REF_PCLK;
    init_struct->trigger_input      = NO_HARDWARE_TRIGGER;
    init_struct->sampling_time      = SPT_CLOCK_15;
}

/*!
    \brief      initialize the LPDTS
    \param[in]  init_struct: the initialization data needed to initialize LPDTS_CFG
                  ref_clock: REF_PCLK, REF_LXTAL
                  trigger_input: NO_HARDWARE_TRIGGER, LPDTS_TRG
                  sampling_time: SPT_CLOCK_x(x=1..15)
    \param[out] none
    \retval     none
*/
void lpdts_init(lpdts_parameter_struct *init_struct)
{
    uint32_t reg;
    /* configure the LPDTS_CFG */
    reg = LPDTS_CFG;
    reg &= ~(LPDTS_CFG_REFSEL | LPDTS_CFG_ITSEL | LPDTS_CFG_SPT);
    reg |= (init_struct->ref_clock | init_struct->trigger_input | init_struct->sampling_time);
    LPDTS_CFG = reg;
}

/*!
    \brief      enable LPDTS temperature sensor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_enable(void)
{
    LPDTS_CFG |= LPDTS_CFG_TSEN;
}

/*!
    \brief      disable LPDTS temperature sensor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_disable(void)
{
    LPDTS_CFG &= ~LPDTS_CFG_TSEN;
}

/*!
    \brief      enable LPDTS software trigger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_soft_trigger_enable(void)
{
    LPDTS_CFG |= LPDTS_CFG_TRGS;
}

/*!
    \brief      disable LPDTS software trigger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_soft_trigger_disable(void)
{
    LPDTS_CFG &= ~LPDTS_CFG_TRGS;
}

/*!
    \brief      configure LPDTS high threshold value
    \param[in]  value: high threshold value(0~65535)
    \param[out] none
    \retval     none
*/
void lpdts_high_threshold_set(uint16_t value)
{
    uint32_t reg;
    /* configure the LPDTS_IT */
    reg = LPDTS_IT;
    reg &= ~LPDTS_IT_INTHT;
    reg |= (uint32_t)value << LPDTS_IT_INTHT_OFFSET;
    LPDTS_IT = reg;
}

/*!
    \brief      configure LPDTS low threshold value
    \param[in]  value: low threshold value(0~65535)
    \param[out] none
    \retval     none
*/
void lpdts_low_threshold_set(uint16_t value)
{
    uint32_t reg;
    /* configure the LPDTS_IT */
    reg = LPDTS_IT;
    reg &= ~LPDTS_IT_INTLT;
    reg |= (uint32_t)value;
    LPDTS_IT = reg;
}

/*!
    \brief      configure LPDTS reference clock selection
    \param[in]  source: reference clock source
                only one parameter can be selected which is shown as below:
      \arg        REF_PCLK: high speed reference clock (PCLK)
      \arg        REF_LXTAL: low speed reference clock (LXTAL)
    \param[out] none
    \retval     none
*/
void lpdts_ref_clock_source_config(uint32_t source)
{
    uint32_t reg;
    /* configure the LPDTS_CFG */
    reg = LPDTS_CFG;
    reg &= ~LPDTS_CFG_REFSEL;
    reg |= source;
    LPDTS_CFG = reg;
}

/*!
    \brief      get temperature from LPDTS
    \param[in]  none
    \param[out] none
    \retval     temperature: temperature in deg C
*/
int32_t lpdts_temperature_get(void)
{
    uint32_t freq;
    uint32_t count;
    uint32_t t0;
    uint32_t t0_freq;
    uint32_t ramp_coeff;
    uint32_t reg_cfg;
    int32_t temperature;

    /* get the total number of samples */
    count = (LPDTS_DATA & LPDTS_DATA_COVAL);
    /* get LPDTS_CFG configuration */
    reg_cfg = LPDTS_CFG;

    /* get the module frequency on Hz */
    if((reg_cfg & LPDTS_CFG_REFSEL) == LPDTS_CFG_REFSEL)
    {
        freq = (LXTAL_VALUE * count) / (2U * ((reg_cfg & LPDTS_CFG_SPT) >> LPDTS_CFG_SPT_OFFSET));
    } else {
        freq = (2U * rcu_clock_freq_get(CK_APB1) / count) * ((reg_cfg & LPDTS_CFG_SPT) >> LPDTS_CFG_SPT_OFFSET);
    }

    /* read factory settings */
    t0 = (LPDTS_SDATA & LPDTS_SDATA_VAL) >> LPDTS_SDATA_VAL_OFFSET;
    if(t0 == 0U)
    {
        t0 = LPDTS_T0_TMP_VAL;
    }

    /* get the T0 frequency on Hz */
    t0_freq = (LPDTS_SDATA & LPDTS_SDATA_FREQ) * 100U;
    /* get the ramp coefficient for the temperature sensor on deg C/Hz */
    ramp_coeff = LPDTS_RDATA & LPDTS_RDATA_RCVAL;

    /* figure out the temperature deg C */
    temperature = (int32_t)t0 + (((int32_t)freq - (int32_t)t0_freq) / (int32_t)ramp_coeff);

    return temperature;
}

/*!
    \brief      get LPDTS flag
    \param[in]  flag: LPDTS ready flag
                only one parameter can be selected which is shown as below:
      \arg        LPDTS_FLAG_TSR
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus lpdts_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(LPDTS_STAT & flag)
    {
        status = SET;
    }
    /* return the state of corresponding LPDTS flag */
    return status;
}

/*!
    \brief      enable LPDTS interrupt
    \param[in]  interrupt: the LPDTS interrupt
                one or more parameters can be selected which is shown as below:
      \arg        LPDTS_INT_EM
      \arg        LPDTS_INT_LT
      \arg        LPDTS_INT_HT
      \arg        LPDTS_INT_EMA
      \arg        LPDTS_INT_LTA
      \arg        LPDTS_INT_HTA
    \param[out] none
    \retval     none
*/
void lpdts_interrupt_enable(uint32_t interrupt)
{
    LPDTS_INTEN |= interrupt;
}

/*!
    \brief      disable LPDTS interrupt
    \param[in]  interrupt: the LPDTS interrupt
                one or more parameters can be selected which is shown as below:
      \arg        LPDTS_INT_EM
      \arg        LPDTS_INT_LT
      \arg        LPDTS_INT_HT
      \arg        LPDTS_INT_EMA
      \arg        LPDTS_INT_LTA
      \arg        LPDTS_INT_HTA
    \param[out] none
    \retval     none
*/
void lpdts_interrupt_disable(uint32_t interrupt)
{
    LPDTS_INTEN &= ~interrupt;
}

/*!
    \brief      get LPDTS interrupt flag
    \param[in]  flag: LPDTS interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        LPDTS_INT_FLAG_EM
      \arg        LPDTS_INT_FLAG_LT
      \arg        LPDTS_INT_FLAG_HT
      \arg        LPDTS_INT_FLAG_EMA
      \arg        LPDTS_INT_FLAG_LTA
      \arg        LPDTS_INT_FLAG_HTA
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus lpdts_interrupt_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;
    uint32_t state;

    state = LPDTS_STAT;
    if(state & flag)
    {
        state = LPDTS_INTEN;
        if(state & flag)
        {
            status = SET;
        }
    }
    /* return the state of corresponding LPDTS flag */
    return status;
}

/*!
    \brief      clear the LPDTS interrupt flag
    \param[in]  flag: LPDTS flag
                one or more parameter can be selected which is shown as below:
      \arg        LPDTS_INT_FLAG_EM
      \arg        LPDTS_INT_FLAG_LT
      \arg        LPDTS_INT_FLAG_HT
      \arg        LPDTS_INT_FLAG_EMA
      \arg        LPDTS_INT_FLAG_LTA
      \arg        LPDTS_INT_FLAG_HTA
    \param[out] none
    \retval     none
*/
void lpdts_interrupt_flag_clear(uint32_t flag)
{
    /* clear the flags */
    LPDTS_INTC = flag;
}
