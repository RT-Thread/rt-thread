/*!
    \file  gd32f4xx_iref.c
    \brief IREF driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_iref.h"

/*!
    \brief      deinit IREF
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iref_deinit(void)
{
    rcu_periph_reset_enable(RCU_IREFRST);
    rcu_periph_reset_disable(RCU_IREFRST);
}

/*!
    \brief      enable IREF
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iref_enable(void)
{
    IREF_CTL |= IREF_CTL_CREN;
}

/*!
    \brief      disable IREF
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iref_disable(void)
{
    IREF_CTL &= ~IREF_CTL_CREN;
}

/*!
    \brief      set IREF mode
    \param[in]  step
      \arg        IREF_MODE_LOW_POWER: 1uA step
      \arg        IREF_MODE_HIGH_CURRENT: 8uA step
    \param[out] none
    \retval     none
*/
void iref_mode_set(uint32_t step)
{
    IREF_CTL &= ~IREF_CTL_SSEL;
    IREF_CTL |= step;
}

/*!
    \brief      set IREF precision_trim_value
    \param[in]  precisiontrim
      \arg        IREF_CUR_PRECISION_TRIM_X(x=0..31): (-15+ x)%
    \param[out] none
    \retval     none
*/
void iref_precision_trim_value_set(uint32_t precisiontrim)
{
    IREF_CTL &= ~IREF_CTL_CPT;
    IREF_CTL |= precisiontrim;
}

/*!
    \brief      set IREF sink mode
    \param[in]  sinkmode
      \arg        IREF_SOURCE_CURRENT : source current.
      \arg        IREF_SINK_CURRENT: sink current
    \param[out] none
    \retval     none
*/
void iref_sink_set(uint32_t sinkmode)
{
    IREF_CTL &= ~IREF_CTL_SCMOD;
    IREF_CTL |= sinkmode;
}

/*!
    \brief      set IREF step data 
    \param[in]  stepdata
      \arg        IREF_CUR_STEP_DATA_X:(x=0..63): step*x
    \param[out] none
    \retval     none
*/

void iref_step_data_config(uint32_t stepdata)
{
    IREF_CTL &= ~IREF_CTL_CSDT;
    IREF_CTL |= stepdata;
}
