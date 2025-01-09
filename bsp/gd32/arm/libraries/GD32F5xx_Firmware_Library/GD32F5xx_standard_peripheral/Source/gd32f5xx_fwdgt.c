/*!
    \file    gd32f5xx_fwdgt.c
    \brief   FWDGT driver

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

#include "gd32f5xx_fwdgt.h"

/*!
    \brief    enable write access to FWDGT_PSC and FWDGT_RLD
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fwdgt_write_enable(void)
{
    FWDGT_CTL = FWDGT_WRITEACCESS_ENABLE;
}

/*!
    \brief    disable write access to FWDGT_PSC and FWDGT_RLD
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fwdgt_write_disable(void)
{
    FWDGT_CTL = FWDGT_WRITEACCESS_DISABLE;
}

/*!
    \brief    start the free watchdog timer counter
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fwdgt_enable(void)
{
    FWDGT_CTL = FWDGT_KEY_ENABLE;
}

/*!
    \brief      configure the free watchdog timer counter prescaler value
    \param[in]  prescaler_value: specify prescaler value
                only one parameter can be selected which is shown as below:
      \arg        FWDGT_PSC_DIV4: FWDGT prescaler set to 4
      \arg        FWDGT_PSC_DIV8: FWDGT prescaler set to 8
      \arg        FWDGT_PSC_DIV16: FWDGT prescaler set to 16
      \arg        FWDGT_PSC_DIV32: FWDGT prescaler set to 32
      \arg        FWDGT_PSC_DIV64: FWDGT prescaler set to 64
      \arg        FWDGT_PSC_DIV128: FWDGT prescaler set to 128
      \arg        FWDGT_PSC_DIV256: FWDGT prescaler set to 256
      \arg        FWDGT_PSC_DIV512: FWDGT prescaler set to 512
      \arg        FWDGT_PSC_DIV1024: FWDGT prescaler set to 1024
      \arg        FWDGT_PSC_DIV2048: FWDGT prescaler set to 2048
      \arg        FWDGT_PSC_DIV4096: FWDGT prescaler set to 4096
      \arg        FWDGT_PSC_DIV8192: FWDGT prescaler set to 8192
      \arg        FWDGT_PSC_DIV16384: FWDGT prescaler set to 16384
      \arg        FWDGT_PSC_DIV32768: FWDGT prescaler set to 32768
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_prescaler_value_config(uint16_t prescaler_value)
{
    uint32_t timeout = FWDGT_PSC_TIMEOUT;
    uint32_t flag_status = RESET;

    /* enable write access to FWDGT_PSC */
    FWDGT_CTL = FWDGT_WRITEACCESS_ENABLE;

    /* wait until the PUD flag to be reset */
    do {
        flag_status = FWDGT_STAT & FWDGT_STAT_PUD;
    } while((--timeout > 0U) && ((uint32_t)RESET != flag_status));

    if((uint32_t)RESET != flag_status) {
        return ERROR;
    }

    /* configure FWDGT */
    FWDGT_PSC = (uint32_t)prescaler_value;

    return SUCCESS;
}

/*!
    \brief      configure the free watchdog timer counter reload value
    \param[in]  reload_value: specify reload value(0x0000 - 0x0FFF)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_reload_value_config(uint16_t reload_value)
{
    uint32_t timeout = FWDGT_RLD_TIMEOUT;
    uint32_t flag_status = RESET;

    /* enable write access to FWDGT_RLD */
    FWDGT_CTL = FWDGT_WRITEACCESS_ENABLE;

    /* wait until the RUD flag to be reset */
    do {
        flag_status = FWDGT_STAT & FWDGT_STAT_RUD;
    } while((--timeout > 0U) && ((uint32_t)RESET != flag_status));

    if((uint32_t)RESET != flag_status) {
        return ERROR;
    }

    FWDGT_RLD = RLD_RLD(reload_value);

    return SUCCESS;
}

/*!
    \brief    reload the counter of FWDGT
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fwdgt_counter_reload(void)
{
    FWDGT_CTL = FWDGT_KEY_RELOAD;
}

/*!
    \brief    configure counter reload value, and prescaler divider value
    \param[in]  reload_value: specify reload value(0x0000 - 0x0FFF)
    \param[in]  prescaler_div: FWDGT prescaler value
                only one parameter can be selected which is shown as below:
      \arg        FWDGT_PSC_DIV4: FWDGT prescaler set to 4
      \arg        FWDGT_PSC_DIV8: FWDGT prescaler set to 8
      \arg        FWDGT_PSC_DIV16: FWDGT prescaler set to 16
      \arg        FWDGT_PSC_DIV32: FWDGT prescaler set to 32
      \arg        FWDGT_PSC_DIV64: FWDGT prescaler set to 64
      \arg        FWDGT_PSC_DIV128: FWDGT prescaler set to 128
      \arg        FWDGT_PSC_DIV256: FWDGT prescaler set to 256
      \arg        FWDGT_PSC_DIV512   : FWDGT prescaler set to 512
      \arg        FWDGT_PSC_DIV1024  : FWDGT prescaler set to 1024
      \arg        FWDGT_PSC_DIV2048  : FWDGT prescaler set to 2048
      \arg        FWDGT_PSC_DIV4096  : FWDGT prescaler set to 4096
      \arg        FWDGT_PSC_DIV8192  : FWDGT prescaler set to 8192
      \arg        FWDGT_PSC_DIV16384 : FWDGT prescaler set to 16384
      \arg        FWDGT_PSC_DIV32768 : FWDGT prescaler set to 32768
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_config(uint16_t reload_value, uint8_t prescaler_div)
{
    uint32_t timeout = FWDGT_PSC_TIMEOUT;
    uint32_t flag_status = RESET;

    /* enable write access to FWDGT_PSC,and FWDGT_RLD */
    FWDGT_CTL = FWDGT_WRITEACCESS_ENABLE;

    /* wait until the PUD flag to be reset */
    do {
        flag_status = FWDGT_STAT & FWDGT_STAT_PUD;
    } while((--timeout > 0U) && ((uint32_t)RESET != flag_status));

    if((uint32_t)RESET != flag_status) {
        return ERROR;
    }

    /* configure FWDGT */
    FWDGT_PSC = (uint32_t)prescaler_div;

    timeout = FWDGT_RLD_TIMEOUT;
    /* wait until the RUD flag to be reset */
    do {
        flag_status = FWDGT_STAT & FWDGT_STAT_RUD;
    } while((--timeout > 0U) && ((uint32_t)RESET != flag_status));

    if((uint32_t)RESET != flag_status) {
        return ERROR;
    }

    FWDGT_RLD = RLD_RLD(reload_value);

    /* reload the counter */
    FWDGT_CTL = FWDGT_KEY_RELOAD;

    return SUCCESS;
}

/*!
    \brief    get flag state of FWDGT
    \param[in]  flag: flag to get
                only one parameter can be selected which is shown as below:
      \arg        FWDGT_STAT_PUD: a write operation to FWDGT_PSC register is on going
      \arg        FWDGT_STAT_RUD: a write operation to FWDGT_RLD register is on going
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fwdgt_flag_get(uint16_t flag)
{
    if(RESET != (FWDGT_STAT & flag)) {
        return SET;
    }

    return RESET;
}
