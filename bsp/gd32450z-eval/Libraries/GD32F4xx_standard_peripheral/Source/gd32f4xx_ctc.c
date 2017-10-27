/*!
    \file  gd32f4xx_ctc.c
    \brief CTC driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_ctc.h"

#define CTC_FLAG_MASK            ((uint32_t)0x00000700U)

/*!
    \brief      reset CTC clock trim controller
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ctc_deinit(void)
{
    /* reset CTC */
    rcu_periph_reset_enable(RCU_CTCRST);
    rcu_periph_reset_disable(RCU_CTCRST);
}

/*!
    \brief      configure the IRC48M trim value
    \param[in]  ctc_trim_value: 8-bit IRC48M trim value
    \param[out] none
    \retval     none
*/
void ctc_irc48m_trim_value_config(uint8_t ctc_trim_value)
{
    /* clear TRIMVALUE bits */
    CTC_CTL0 &= (~(uint32_t)CTC_CTL0_TRIMVALUE);
    /* set TRIMVALUE bits */
    CTC_CTL0 |= ((uint32_t)ctc_trim_value << 8);
}

/*!
    \brief      generate software reference source sync pulse
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ctc_software_refsource_pulse_generate(void)
{
    CTC_CTL0 |= (uint32_t)CTC_CTL0_SWREFPUL;
}

/*!
    \brief      configure hardware automatically trim mode
    \param[in]  ctc_hardmode:
      \arg        CTC_HARDWARE_TRIM_MODE_ENABLE: hardware automatically trim mode enable
      \arg        CTC_HARDWARE_TRIM_MODE_DISABLE: hardware automatically trim mode disable
    \param[out] none
    \retval     none
*/
void ctc_hardware_trim_mode_config(uint32_t ctc_hardmode)
{
    CTC_CTL0 &= (uint32_t)(~CTC_CTL0_AUTOTRIM);
    CTC_CTL0 |= (uint32_t)ctc_hardmode;
}

/*!
    \brief      enable CTC counter
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ctc_counter_enable(void)
{
    CTC_CTL0 |= (uint32_t)CTC_CTL0_CNTEN;
}

/*!
    \brief      disable CTC counter
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ctc_counter_disable(void)
{
    CTC_CTL0 &= (uint32_t)(~CTC_CTL0_CNTEN);
}

/*!
    \brief      configure reference signal source polarity
    \param[in]  ctc_polarity:
      \arg        CTC_REFSOURCE_POLARITY_FALLING: reference signal source polarity is falling edge
      \arg        CTC_REFSOURCE_POLARITY_RISING: reference signal source polarity is rising edge
    \param[out] none
    \retval     none
*/
void ctc_refsource_polarity_config(uint32_t ctc_polarity)
{
    CTC_CTL1 &= (uint32_t)(~CTC_CTL1_REFPOL);
    CTC_CTL1 |= (uint32_t)ctc_polarity;
}

/*!
    \brief      select USBFS or USBHS SOF signal
    \param[in]  ctc_usbsof:
      \arg        CTC_USBSOFSEL_USBHS: USBHS SOF signal is selected
      \arg        CTC_USBSOFSEL_USBFS: USBFS SOF signal is selected
    \param[out] none
    \retval     none
*/
void ctc_usbsof_signal_select(uint32_t ctc_usbsof)
{
    CTC_CTL1 &= (uint32_t)(~CTC_CTL1_USBSOFSEL);
    CTC_CTL1 |= (uint32_t)ctc_usbsof;
}

/*!
    \brief      select reference signal source
    \param[in]  ctc_refs:
      \arg        CTC_REFSOURCE_GPIO: GPIO is selected
      \arg        CTC_REFSOURCE_LXTAL: LXTAL is clock selected
      \arg        CTC_REFSOURCE_USBSOF: USBSOF is selected
    \param[out] none
    \retval     none
*/
void ctc_refsource_signal_select(uint32_t ctc_refs)
{
    CTC_CTL1 &= (uint32_t)(~CTC_CTL1_REFSEL);
    CTC_CTL1 |= (uint32_t)ctc_refs;
}

/*!
    \brief      configure reference signal source prescaler
    \param[in]  ctc_prescaler:
      \arg        CTC_REFSOURCE_PSC_OFF: reference signal not divided
      \arg        CTC_REFSOURCE_PSC_DIV2: reference signal divided by 2
      \arg        CTC_REFSOURCE_PSC_DIV4: reference signal divided by 4
      \arg        CTC_REFSOURCE_PSC_DIV8: reference signal divided by 8
      \arg        CTC_REFSOURCE_PSC_DIV16: reference signal divided by 16
      \arg        CTC_REFSOURCE_PSC_DIV32: reference signal divided by 32
      \arg        CTC_REFSOURCE_PSC_DIV64: reference signal divided by 64
      \arg        CTC_REFSOURCE_PSC_DIV128: reference signal divided by 128
    \param[out] none
    \retval     none
*/
void ctc_refsource_prescaler_config(uint32_t ctc_prescaler)
{
    CTC_CTL1 &= (uint32_t)(~CTC_CTL1_REFPSC);
    CTC_CTL1 |= (uint32_t)ctc_prescaler;
}

/*!
    \brief      configure clock trim base limit value
    \param[in]  ctc_limit_value: 8-bit clock trim base limit value
    \param[out] none
    \retval     none
*/
void ctc_clock_limit_value_config(uint8_t ctc_limit_value)
{
    CTC_CTL1 &= (uint32_t)(~CTC_CTL1_CKLIM);
    CTC_CTL1 |= (uint32_t)((uint32_t)ctc_limit_value << 16);
}

/*!
    \brief      configure CTC counter reload value
    \param[in]  ctc_reload_value: 16-bit CTC counter reload value
    \param[out] none
    \retval     none
*/
void ctc_counter_reload_value_config(uint16_t ctc_reload_value)
{
    CTC_CTL1 &= (uint32_t)(~CTC_CTL1_RLVALUE);
    CTC_CTL1 |= (uint32_t)ctc_reload_value;
}

/*!
    \brief      read CTC counter capture value when reference sync pulse occurred
    \param[in]  none
    \param[out] none
    \retval     the 16-bit CTC counter capture value
*/
uint16_t ctc_counter_capture_value_read(void)
{
    uint16_t capture_value = 0U;
    capture_value = (uint16_t)((CTC_STAT & CTC_STAT_REFCAP)>> 16);
    return (capture_value);
}

/*!
    \brief      read CTC trim counter direction when reference sync pulse occurred
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
      \arg        SET: CTC trim counter direction is down-counting
      \arg        RESET: CTC trim counter direction is up-counting
*/
FlagStatus ctc_counter_direction_read(void)
{
    if(RESET != (CTC_STAT & CTC_STAT_REFDIR)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      read CTC counter reload value
    \param[in]  none
    \param[out] none
    \retval     the 16-bit CTC counter reload value
*/
uint16_t ctc_counter_reload_value_read(void)
{
    uint16_t reload_value = 0U;
    reload_value = (uint16_t)(CTC_CTL1 & CTC_CTL1_RLVALUE);
    return (reload_value);
}

/*!
    \brief      read the IRC48M trim value
    \param[in]  none
    \param[out] none
    \retval     the 8-bit IRC48M trim value
*/
uint8_t ctc_irc48m_trim_value_read(void)
{
    uint8_t trim_value = 0U;
    trim_value = (uint8_t)((CTC_CTL0 & CTC_CTL0_TRIMVALUE) >> 8);
    return (trim_value);
}

/*!
    \brief      enable the CTC interrupt
    \param[in]  ctc_interrupt: CTC interrupt enable
      \arg        CTC_INT_CKOKIE: clock trim OK interrupt enable
      \arg        CTC_INT_CKWARNIE: clock trim warning interrupt enable
      \arg        CTC_INT_ERRIE: error interrupt enable
      \arg        CTC_INT_EREFIE: expect reference interrupt enable
    \param[out] none
    \retval     none
*/
void ctc_interrupt_enable(uint32_t ctc_interrupt)
{
    CTC_CTL0 |= (uint32_t)ctc_interrupt; 
}

/*!
    \brief      disable the CTC interrupt
    \param[in]  ctc_interrupt: CTC interrupt enable source
      \arg        CTC_INT_CKOKIE: clock trim OK interrupt enable
      \arg        CTC_INT_CKWARNIE: clock trim warning interrupt enable
      \arg        CTC_INT_ERRIE: error interrupt enable
      \arg        CTC_INT_EREFIE: expect reference interrupt enable
    \param[out] none
    \retval     none
*/
void ctc_interrupt_disable(uint32_t ctc_interrupt)
{
    CTC_CTL0 &= (uint32_t)(~ctc_interrupt); 
}

/*!
    \brief      get CTC interrupt flag
    \param[in]  ctc_interrupt: the CTC interrupt flag
      \arg        CTC_INT_CKOK: clock trim OK interrupt
      \arg        CTC_INT_CKWARN: clock trim warning interrupt 
      \arg        CTC_INT_ERR: error interrupt 
      \arg        CTC_INT_EREF: expect reference interrupt
      \arg        CTC_INT_CKERR: clock trim error bit interrupt
      \arg        CTC_INT_REFMISS: reference sync pulse miss interrupt 
      \arg        CTC_INT_TRIMERR: trim value error interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ctc_interrupt_flag_get(uint32_t ctc_interrupt)
{
    uint32_t interrupt = 0U, intenable = 0U;

    if(ctc_interrupt & CTC_FLAG_MASK){
        intenable = CTC_CTL0 & CTC_INT_ERRIE;
    }else{
        intenable = CTC_CTL0 & ctc_interrupt;
    }
    interrupt = CTC_STAT & ctc_interrupt;

    if(interrupt && intenable){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CTC interrupt flag
    \param[in]  ctc_interrupt: the CTC interrupt flag
      \arg        CTC_INT_CKOK: clock trim OK interrupt
      \arg        CTC_INT_CKWARN: clock trim warning interrupt 
      \arg        CTC_INT_ERR: error interrupt 
      \arg        CTC_INT_EREF: expect reference interrupt 
      \arg        CTC_INT_CKERR: clock trim error bit interrupt
      \arg        CTC_INT_REFMISS: reference sync pulse miss interrupt 
      \arg        CTC_INT_TRIMERR: trim value error interrupt
    \param[out] none
    \retval     none
*/ 
void ctc_interrupt_flag_clear(uint32_t ctc_interrupt)
{
    if(ctc_interrupt & CTC_FLAG_MASK){
        CTC_INTC |= CTC_INTC_ERRIC;
    }else{
        CTC_INTC |= ctc_interrupt;
    }
}

/*!
    \brief      get CTC flag
    \param[in]  ctc_flag: the CTC flag
      \arg        CTC_FLAG_CKOK: clock trim OK flag
      \arg        CTC_FLAG_CKWARN: clock trim warning flag 
      \arg        CTC_FLAG_ERR: error flag 
      \arg        CTC_FLAG_EREF: expect reference flag
      \arg        CTC_FLAG_CKERR: clock trim error bit
      \arg        CTC_FLAG_REFMISS: reference sync pulse miss
      \arg        CTC_FLAG_TRIMERR: trim value error bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ctc_flag_get(uint32_t ctc_flag)
{
    if(RESET != (CTC_STAT & ctc_flag)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CTC flag
    \param[in]  ctc_flag: the CTC flag
      \arg        CTC_FLAG_CKOK: clock trim OK flag
      \arg        CTC_FLAG_CKWARN: clock trim warning flag 
      \arg        CTC_FLAG_ERR: error flag 
      \arg        CTC_FLAG_EREF: expect reference flag
      \arg        CTC_FLAG_CKERR: clock trim error bit
      \arg        CTC_FLAG_REFMISS: reference sync pulse miss
      \arg        CTC_FLAG_TRIMERR: trim value error bit
    \param[out] none
    \retval     none
*/
void ctc_flag_clear(uint32_t ctc_flag)
{
    if(ctc_flag & CTC_FLAG_MASK){
        CTC_INTC |= CTC_INTC_ERRIC;
    }else{
        CTC_INTC |= ctc_flag;
    }
}
