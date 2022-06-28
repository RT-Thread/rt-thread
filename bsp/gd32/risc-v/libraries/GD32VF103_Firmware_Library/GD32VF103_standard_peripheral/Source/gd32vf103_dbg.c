/*!
    \file    gd32vf103_dbg.c
    \brief   DBG driver

    \version 2019-06-05, V1.0.0, firmware for GD32VF103
    \version 2020-08-04, V1.1.0, firmware for GD32VF103
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

#include "gd32vf103_dbg.h"

/*!
    \brief      read DBG_ID code register
    \param[in]  none
    \param[out] none
    \retval     DBG_ID code
*/
uint32_t dbg_id_get(void)
{
    return DBG_ID;
}

/*!
    \brief      enable low power behavior when the mcu is in debug mode
    \param[in]  dbg_low_power:
                one or more parameters can be selected which are shown as below:
      \arg        DBG_LOW_POWER_SLEEP: keep debugger connection during sleep mode
      \arg        DBG_LOW_POWER_DEEPSLEEP: keep debugger connection during deepsleep mode
      \arg        DBG_LOW_POWER_STANDBY: keep debugger connection during standby mode
    \param[out] none
    \retval     none
*/
void dbg_low_power_enable(uint32_t dbg_low_power)
{
    DBG_CTL |= dbg_low_power;
}

/*!
    \brief      disable low power behavior when the mcu is in debug mode
    \param[in]  dbg_low_power:
                one or more parameters can be selected which are shown as below:
      \arg        DBG_LOW_POWER_SLEEP: donot keep debugger connection during sleep mode
      \arg        DBG_LOW_POWER_DEEPSLEEP: donot keep debugger connection during deepsleep mode
      \arg        DBG_LOW_POWER_STANDBY: donot keep debugger connection during standby mode
    \param[out] none
    \retval     none
*/
void dbg_low_power_disable(uint32_t dbg_low_power)
{
    DBG_CTL &= ~dbg_low_power;
}

/*!
    \brief      enable peripheral behavior when the mcu is in debug mode
    \param[in]  dbg_periph: refer to dbg_periph_enum
                one or more parameters can be selected which are shown as below:
      \arg        DBG_FWDGT_HOLD : debug FWDGT kept when core is halted
      \arg        DBG_WWDGT_HOLD : debug WWDGT kept when core is halted
      \arg        DBG_CANx_HOLD (x=0,1): hold CANx counter when core is halted
      \arg        DBG_I2Cx_HOLD (x=0,1): hold I2Cx smbus when core is halted
      \arg        DBG_TIMERx_HOLD (x=0,1,2,3,4,5,6): hold TIMERx counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_enable(dbg_periph_enum dbg_periph)
{
    DBG_CTL |= (uint32_t)dbg_periph;
}

/*!
    \brief      disable peripheral behavior when the mcu is in debug mode
    \param[in]  dbg_periph: refer to dbg_periph_enum
                one or more parameters can be selected which are shown as below:
      \arg        DBG_FWDGT_HOLD : debug FWDGT kept when core is halted
      \arg        DBG_WWDGT_HOLD : debug WWDGT kept when core is halted
      \arg        DBG_CANx_HOLD (x=0,1): hold CAN0 counter when core is halted
      \arg        DBG_I2Cx_HOLD (x=0,1): hold I2Cx smbus when core is halted
      \arg        DBG_TIMERx_HOLD (x=0,1,2,3,4,5,6): hold TIMERx counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_disable(dbg_periph_enum dbg_periph)
{
    DBG_CTL &= ~(uint32_t)dbg_periph;
}
