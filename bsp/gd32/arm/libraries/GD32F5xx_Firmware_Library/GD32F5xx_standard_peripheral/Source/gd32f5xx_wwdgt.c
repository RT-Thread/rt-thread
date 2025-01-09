/*!
    \file    gd32f5xx_wwdgt.c
    \brief   WWDGT driver

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
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

#include "gd32f5xx_wwdgt.h"

/*!
    \brief    reset the window watchdog timer configuration
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
    \brief    start the window watchdog timer counter
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_enable(void)
{
    WWDGT_CTL |= WWDGT_CTL_WDGTEN;
}

/*!
    \brief    configure the window watchdog timer counter value
    \param[in]  counter_value: 0x00 - 0x7F
    \param[out] none
    \retval     none
*/
void wwdgt_counter_update(uint16_t counter_value)
{
    WWDGT_CTL = (uint32_t)(CTL_CNT(counter_value));
}

/*!
    \brief    configure counter value, window value, and prescaler divider value
    \param[in]  counter: 0x00 - 0x7F
    \param[in]  window: 0x00 - 0x7F
    \param[in]  prescaler: wwdgt prescaler value
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_CFG_PSC_DIV1     : the time base of window watchdog counter = (PCLK1/4096)/1
      \arg        WWDGT_CFG_PSC_DIV2     : the time base of window watchdog counter = (PCLK1/4096)/2
      \arg        WWDGT_CFG_PSC_DIV4     : the time base of window watchdog counter = (PCLK1/4096)/4
      \arg        WWDGT_CFG_PSC_DIV8     : the time base of window watchdog counter = (PCLK1/4096)/8
      \arg        WWDGT_CFG_PSC_DIV16    : the time base of window watchdog counter = (PCLK1/4096)/16
      \arg        WWDGT_CFG_PSC_DIV32    : the time base of window watchdog counter = (PCLK1/4096)/32
      \arg        WWDGT_CFG_PSC_DIV64    : the time base of window watchdog counter = (PCLK1/4096)/64
      \arg        WWDGT_CFG_PSC_DIV128   : the time base of window watchdog counter = (PCLK1/4096)/128
      \arg        WWDGT_CFG_PSC_DIV256   : the time base of window watchdog counter = (PCLK1/4096)/256
      \arg        WWDGT_CFG_PSC_DIV512   : the time base of window watchdog counter = (PCLK1/4096)/512
      \arg        WWDGT_CFG_PSC_DIV1024  : the time base of window watchdog counter = (PCLK1/4096)/1024
      \arg        WWDGT_CFG_PSC_DIV2048  : the time base of window watchdog counter = (PCLK1/4096)/2048
      \arg        WWDGT_CFG_PSC_DIV4096  : the time base of window watchdog counter = (PCLK1/4096)/4096
      \arg        WWDGT_CFG_PSC_DIV8192  : the time base of window watchdog counter = (PCLK1/4096)/8192
      \arg        WWDGT_CFG_PSC_DIV16384 : the time base of window watchdog counter = (PCLK1/4096)/16384
      \arg        WWDGT_CFG_PSC_DIV32768 : the time base of window watchdog counter = (PCLK1/4096)/32768
      \arg        WWDGT_CFG_PSC_DIV65536 : the time base of window watchdog counter = (PCLK1/4096)/65536
      \arg        WWDGT_CFG_PSC_DIV131072: the time base of window watchdog counter = (PCLK1/4096)/131072
      \arg        WWDGT_CFG_PSC_DIV262144: the time base of window watchdog counter = (PCLK1/4096)/262144
    \param[out] none
    \retval     none
*/
void wwdgt_config(uint16_t counter, uint16_t window, uint32_t prescaler)
{
    /* configure WIN and PSC bits, configure CNT bit */
    WWDGT_CTL = (uint32_t)(CTL_CNT(counter));
    WWDGT_CFG = (uint32_t)(CFG_WIN(window) | prescaler);
}

/*!
    \brief    check early wakeup interrupt state of WWDGT
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus wwdgt_flag_get(void)
{
    if(RESET != (WWDGT_STAT & WWDGT_STAT_EWIF)) {
        return SET;
    }

    return RESET;
}

/*!
    \brief    clear early wakeup interrupt state of WWDGT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_flag_clear(void)
{
    WWDGT_STAT = (uint32_t)(RESET);
}

/*!
    \brief    enable early wakeup interrupt of WWDGT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wwdgt_interrupt_enable(void)
{
    WWDGT_CFG |= WWDGT_CFG_EWIE;
}
