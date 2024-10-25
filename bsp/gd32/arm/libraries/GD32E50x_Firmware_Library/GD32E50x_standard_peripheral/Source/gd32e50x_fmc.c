/*!
    \file    gd32e50x_fmc.c
    \brief   FMC driver

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

#include "gd32e50x_fmc.h"

/* FMC mask */
#define LOW_8BITS_MASK                    ((uint32_t)0x000000FFU)
#define HIGH_8BITS_MASK                   ((uint32_t)0x0000FF00U)
#define LOW_8BITS_MASK1                   ((uint32_t)0x00FF0000U)
#define HIGH_8BITS_MASK1                  ((uint32_t)0xFF000000U)
#define LOW_16BITS_MASK                   ((uint32_t)0x0000FFFFU)
#define HIGH_16BITS_MASK                  ((uint32_t)0xFFFF0000U)

/* USER of option bytes mask */
#define OB_USER_MASK                      ((uint8_t)0x38U)

/* default offset */
#define FMC_OBSTAT_USER_OFFSET            2U
#define FMC_OBSTAT_DATA_OFFSET            10U

/* return the FMC state */
static fmc_state_enum fmc_state_get(void);
/* check FMC ready or not */
static fmc_state_enum fmc_ready_wait(uint32_t timeout);

/*!
    \brief      unlock the main FMC operation
                it is better to used in pairs with fmc_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if(RESET != (FMC_CTL & FMC_CTL_LK))
    {
        /* write the FMC unlock key */
        FMC_KEY = UNLOCK_KEY0;
        FMC_KEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the main FMC operation
                it is better to used in pairs with fmc_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_lock(void)
{
    /* set the LK bit */
    FMC_CTL |= FMC_CTL_LK;
}

/*!
    \brief      set the wait state
    \param[in]  wscnt: wait state
                only one parameter can be selected which is shown as below:
      \arg        FMC_WAIT_STATE_0: 0 wait state added
      \arg        FMC_WAIT_STATE_1: 1 wait state added
      \arg        FMC_WAIT_STATE_2: 2 wait state added
      \arg        FMC_WAIT_STATE_3: 3 wait state added
      \arg        FMC_WAIT_STATE_4: 4 wait state added
    \param[out] none
    \retval     none
*/
void fmc_wscnt_set(uint32_t wscnt)
{
    uint32_t ws;

    ws = FMC_WS;

    /* set the wait state counter value */
    ws &= ~FMC_WS_WSCNT;
    FMC_WS = (ws | wscnt);
}

/*!
    \brief      enable pre-fetch
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_prefetch_enable(void)
{
    FMC_WS |= FMC_WS_PFEN;
}

/*!
    \brief      disable pre-fetch
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_prefetch_disable(void)
{
    FMC_WS &= ~FMC_WS_PFEN;
}

/*!
    \brief      enable IBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_enable(void)
{
    FMC_WS |= FMC_WS_ICEN;
}

/*!
    \brief      disable IBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_disable(void)
{
    FMC_WS &= ~FMC_WS_ICEN;
}

/*!
    \brief      reset IBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ibus_reset(void)
{
    FMC_WS |= FMC_WS_ICRST;
}

/*!
    \brief      enable DBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_enable(void)
{
    FMC_WS |= FMC_WS_DCEN;
}

/*!
    \brief      disable DBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_disable(void)
{
    FMC_WS &= ~FMC_WS_DCEN;
}

/*!
    \brief      reset DBUS cache
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_dbus_reset(void)
{
    FMC_WS |= FMC_WS_DCRST;
}

/*!
    \brief      FMC erase page
    \param[in]  page_address: target page address
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* start page erase */
        FMC_CTL |= FMC_CTL_PER;
        FMC_ADDR = page_address;
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the PER bit */
        FMC_CTL &= ~FMC_CTL_PER;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC erase whole chip
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* start chip erase */
        FMC_CTL |= FMC_CTL_MER;
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
    }
    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      FMC program a word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* set the PG bit to start program */
        FMC_CTL |= FMC_CTL_PG;
        REG32(address) = data;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the PG bit */
        FMC_CTL &= ~FMC_CTL_PG;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      unlock the option bytes operation
                it is better to used in pairs with ob_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_unlock(void)
{
    if(RESET == (FMC_CTL & FMC_CTL_OBWEN))
    {
        /* write the FMC ob unlock key */
        FMC_OBKEY = UNLOCK_KEY0;
        FMC_OBKEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the option bytes operation
                it is better to used in pairs with ob_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_lock(void)
{
    /* reset the OBWEN bit */
    FMC_CTL &= ~FMC_CTL_OBWEN;
}

/*!
    \brief      erase the option bytes
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OB_HSPC: high security protection
*/
fmc_state_enum ob_erase(void)
{
    uint32_t temp_spc;
    fmc_state_enum fmc_state;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK)))
    {
        fmc_state = FMC_OB_HSPC;
    }

    if(FMC_READY == fmc_state)
    {
        /* start erase the option bytes */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state)
        {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            /* set the OBPG bit */
            FMC_CTL |= FMC_CTL_OBPG;
            /* restore the last get option bytes security protection code */
            OB_SPC_USER = (temp_spc & LOW_8BITS_MASK) | LOW_8BITS_MASK1;
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }else{
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      enable write protection
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_wp: specify sector to be write protected
                only one parameter can be selected which are shown as below:
      \arg        OB_WP_NONE: disable all write protection
      \arg        OB_WP_x(x=0..31): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OB_HSPC: high security protection
*/
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[4];

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK)))
    {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 4U; i++)
    {
        op_byte[i] = OP_BYTE(i);
    }

    ob_wp      = (uint32_t)(~ob_wp);
    op_byte[2] = (ob_wp & LOW_8BITS_MASK) | ((ob_wp & HIGH_8BITS_MASK) << 8);
    op_byte[3] = ((ob_wp & LOW_8BITS_MASK1) >> 16) | ((ob_wp & HIGH_8BITS_MASK1) >> 8);

    if(FMC_READY == fmc_state)
    {
        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state)
        {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 4U; i++)
            {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state)
                {
                    break;
                }
            }
            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }else{
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure security protection
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_spc: specify security protection
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OB_HSPC: high security protection
*/
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[4];

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER & LOW_16BITS_MASK;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK)))
    {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 4U; i++)
    {
        op_byte[i] = OP_BYTE(i);
    }
    op_byte[0] = ((uint32_t)(ob_spc)) | ((op_byte[0] & HIGH_16BITS_MASK));

    if(FMC_READY == fmc_state)
    {
        /* start erase the option bytes */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state)
        {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 4U; i++)
            {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state)
                {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }else{
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes USER
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_fwdgt: option bytes free watchdog value
                only one parameter can be selected which is shown as below:
      \arg        OB_FWDGT_SW: software free watchdog
      \arg        OB_FWDGT_HW: hardware free watchdog
    \param[in]  ob_deepsleep: option bytes deepsleep reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_DEEPSLEEP_NRST: no reset when entering deepsleep mode
      \arg        OB_DEEPSLEEP_RST: generate a reset instead of entering deepsleep mode
    \param[in]  ob_stdby:option bytes standby reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_STDBY_NRST: no reset when entering standby mode
      \arg        OB_STDBY_RST: generate a reset instead of entering standby mode
    \param[in]  ob_bor_th: option bytes BOR threshold value
                only one parameter can be selected which is shown as below:
      \arg        OB_BOR_TH_VALUE3: BOR threshold value 3
      \arg        OB_BOR_TH_VALUE2: BOR threshold value 2
      \arg        OB_BOR_TH_VALUE1: BOR threshold value 1
      \arg        OB_BOR_TH_VALUE0: BOR threshold value 0
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OB_HSPC: high security protection
*/
fmc_state_enum ob_user_write(uint8_t ob_fwdgt, uint8_t ob_deepsleep, uint8_t ob_stdby, uint8_t ob_bor_th)
{
    uint32_t temp_spc;
    uint8_t temp;
    uint8_t i;
    uint32_t op_byte[4];

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK)))
    {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 4U; i++)
    {
        op_byte[i] = OP_BYTE(i);
    }
    temp = ((uint8_t)((uint8_t)((uint8_t)((uint8_t)(ob_fwdgt) | ob_deepsleep) | ob_stdby) | ob_bor_th) | (OB_USER_MASK));
    op_byte[0] = ((uint32_t)(temp) << 16U) | ((op_byte[0] & LOW_16BITS_MASK));

    if(FMC_READY == fmc_state)
    {
        /* start erase the option bytes */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state)
        {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 4U; i++)
            {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state)
                {
                    break;
                }
            }

            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }else{
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes DATA
    \param[in]  data: the byte to be programmed
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_PGERR: program error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_OB_HSPC: high security protection
*/
fmc_state_enum ob_data_program(uint16_t ob_data)
{
    uint32_t temp_spc;
    uint8_t i;
    uint32_t op_byte[4];

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    temp_spc = OB_SPC_USER;

    /* check the option bytes security protection value */
    if((RESET != ob_security_protection_flag_get()) && (FMC_HSPC == (temp_spc & LOW_8BITS_MASK)))
    {
        fmc_state = FMC_OB_HSPC;
    }

    for(i = 0U; i < 4U; i++)
    {
        op_byte[i] = OP_BYTE(i);
    }
    op_byte[1] = (uint32_t)((ob_data & LOW_8BITS_MASK) | ((ob_data & HIGH_8BITS_MASK) << 8));

    if(FMC_READY == fmc_state)
    {
        /* start erase the option bytes */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state)
        {
            /* reset the OBER bit and enable the option bytes programming */
            FMC_CTL &= ~FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_OBPG;

            for(i = 0U; i < 4U; i++)
            {
                OP_BYTE(i) = op_byte[i];
                /* wait for the FMC ready */
                fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
                if(FMC_READY != fmc_state)
                {
                    break;
                }
            }
            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }else{
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get the value of option bytes USER
    \param[in]  none
    \param[out] none
    \retval     the option bytes USER value
*/
uint8_t ob_user_get(void)
{
    /* return the FMC user option bytes value */
    return (uint8_t)(FMC_OBSTAT >> FMC_OBSTAT_USER_OFFSET);
}

/*!
    \brief      get the value of option bytes DATA
    \param[in]  none
    \param[out] none
    \retval     the option bytes DATA value
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)(FMC_OBSTAT >> FMC_OBSTAT_DATA_OFFSET);
}

/*!
    \brief      get the value of option bytes write protection
    \param[in]  none
    \param[out] none
    \retval     the write protection option bytes value
*/
uint32_t ob_write_protection_get(void)
{
    /* return the FMC write protection option bytes value */
    return FMC_WP;
}

/*!
    \brief      get the FMC option bytes security protection state
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_security_protection_flag_get(void)
{
    FlagStatus spc_state = RESET;

    if(RESET != (FMC_OBSTAT & FMC_OBSTAT_SPC))
    {
        spc_state = SET;
    }else{
        spc_state = RESET;
    }
    return spc_state;
}

/*!
    \brief      get FMC flag status
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: FMC busy flag
      \arg        FMC_FLAG_PGERR: FMC program error flag
      \arg        FMC_FLAG_PGAERR: FMC program alignment error flag
      \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag
      \arg        FMC_FLAG_END: FMC end of operation flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag)
    {
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear the FMC flag
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_PGERR: FMC program error flag
      \arg        FMC_FLAG_PGAERR: FMC program alignment error flag
      \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag
      \arg        FMC_FLAG_END: FMC end of operation flag
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t flag)
{
    /* clear the flags */
    FMC_STAT = flag;
}

/*!
    \brief      enable FMC interrupt
    \param[in]  interrupt: the FMC interrupt
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: FMC end of operation interrupt
      \arg        FMC_INT_ERR: FMC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t interrupt)
{
    FMC_CTL |= interrupt;
}

/*!
    \brief      disable FMC interrupt
    \param[in]  interrupt: the FMC interrupt
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: FMC end of operation interrupt
      \arg        FMC_INT_ERR: FMC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t interrupt)
{
    FMC_CTL &= ~(uint32_t)interrupt;
}

/*!
    \brief      get FMC interrupt flag
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_PGERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_PGAERR: FMC program alignment error interrupt flag
      \arg        FMC_INT_FLAG_WPERR: FMC erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag)
    {
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear FMC interrupt flag
    \param[in]  flag: FMC interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        FMC_INT_FLAG_PGERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_PGAERR: FMC program alignment error interrupt flag
      \arg        FMC_INT_FLAG_WPERR: FMC erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(uint32_t flag)
{
    /* clear the flag */
    FMC_STAT = flag;
}

/*!
    \brief      get the FMC state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
static fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_BUSY))
    {
        fmc_state = FMC_BUSY;
    }else{
        if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_WPERR))
        {
            fmc_state = FMC_WPERR;
        }else{
            if((uint32_t)0x00U != (FMC_STAT & (FMC_STAT_PGERR)))
            {
                fmc_state = FMC_PGERR;
            }else{
                if((uint32_t)0x00U != (FMC_STAT & (FMC_STAT_PGAERR)))
                {
                    fmc_state = FMC_PGAERR;
                }
            }
        }
  }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC is ready or not
    \param[in]  timeout: timeout count
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
static fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    }while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state)
    {
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
