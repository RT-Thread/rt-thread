/*!
    \file  gd32f4xx_wwdgt.c
    \brief WWDGT driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_wwdgt.h"

/* write value to WWDGT_CTL_CNT bit field */
#define CTL_CNT(regval)             (BITS(0,6) & ((uint32_t)(regval) << 0))
/* write value to WWDGT_CFG_WIN bit field */
#define CFG_WIN(regval)             (BITS(0,6) & ((uint32_t)(regval) << 0))

/*!
    \brief      reset the window watchdog timer configuration
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_deinit(void)
{
    rcu_periph_reset_enable(RCU_WWDGTRST);
    rcu_periph_reset_disable(RCU_WWDGTRST);
}

/*!
    \brief      configure the window watchdog timer counter value
    \param[in]  counter_value: 0x00 - 0x7F
    \param[out] none
    \retval     none
*/
void wwdgt_counter_update(uint16_t counter_value)
{
    uint32_t reg = 0U;
    
    reg = (WWDGT_CTL & (~WWDGT_CTL_CNT));
    reg |= CTL_CNT(counter_value);
    
    WWDGT_CTL = reg;
}

/*!
    \brief      start the window watchdog timer counter
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_enable(void)
{
    WWDGT_CTL |= WWDGT_CTL_WDGTEN;
}

/*!
    \brief      configure counter value, window value, and prescaler divider value  
    \param[in]  counter: 0x00 - 0x7F   
    \param[in]  window: 0x00 - 0x7F
    \param[in]  prescaler: wwdgt prescaler value
      \arg        WWDGT_CFG_PSC_DIV1: the time base of window watchdog counter = (PCLK1/4096)/1
      \arg        WWDGT_CFG_PSC_DIV2: the time base of window watchdog counter = (PCLK1/4096)/2
      \arg        WWDGT_CFG_PSC_DIV4: the time base of window watchdog counter = (PCLK1/4096)/4
      \arg        WWDGT_CFG_PSC_DIV8: the time base of window watchdog counter = (PCLK1/4096)/8
    \param[out] none
    \retval     none
*/
void wwdgt_config(uint16_t counter, uint16_t window, uint32_t prescaler)
{
    uint32_t reg_cfg = 0U, reg_ctl = 0U;

    /* clear WIN and PSC bits, clear CNT bit */
    reg_cfg = (WWDGT_CFG &(~(WWDGT_CFG_WIN|WWDGT_CFG_PSC)));
    reg_ctl = (WWDGT_CTL &(~WWDGT_CTL_CNT));
  
    /* configure WIN and PSC bits, configure CNT bit */
    reg_cfg |= CFG_WIN(window);
    reg_cfg |= prescaler;
    reg_ctl |= CTL_CNT(counter);
    
    WWDGT_CTL = reg_ctl;
    WWDGT_CFG = reg_cfg;
}

/*!
    \brief      enable early wakeup interrupt of WWDGT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_interrupt_enable(void)
{
    WWDGT_CFG |= WWDGT_CFG_EWIE;
}

/*!
    \brief      check early wakeup interrupt state of WWDGT
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus wwdgt_flag_get(void)
{
    if(WWDGT_STAT & WWDGT_STAT_EWIF){
        return SET;
    }

    return RESET;
}

/*!
    \brief      clear early wakeup interrupt state of WWDGT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_flag_clear(void)
{
    WWDGT_STAT &= (~WWDGT_STAT_EWIF);
}
