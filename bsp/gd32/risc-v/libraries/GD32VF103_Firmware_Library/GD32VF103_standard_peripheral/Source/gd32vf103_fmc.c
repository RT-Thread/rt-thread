/*!
    \file    gd32vf103_fmc.c
    \brief   FMC driver

    \version 2019-06-05, V1.0.0, firmware for GD32VF103
    \version 2019-09-18, V1.0.1, firmware for GD32VF103
    \version 2020-02-20, V1.0.2, firmware for GD32VF103
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

#include "gd32vf103_fmc.h"

/*!
    \brief      set the FMC wait state counter
    \param[in]  wscnt£ºwait state counter value
      \arg        WS_WSCNT_0: FMC 0 wait state
      \arg        WS_WSCNT_1: FMC 1 wait state
      \arg        WS_WSCNT_2: FMC 2 wait state
    \param[out] none
    \retval     none
 */
void fmc_wscnt_set(uint32_t wscnt)
{
    uint32_t reg;

    reg = FMC_WS;
    /* set the wait state counter value */
    reg &= ~FMC_WS_WSCNT;
    FMC_WS = (reg | wscnt);
}

/*!
    \brief      unlock the main FMC operation
    \param[in]  none
    \param[out] none
    \retval     none
 */
void fmc_unlock(void)
{
    if((RESET != (FMC_CTL & FMC_CTL_LK))){
        /* write the FMC unlock key */
        FMC_KEY = UNLOCK_KEY0;
        FMC_KEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock the main FMC operation
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
    \brief      FMC erase page
    \param[in]  page_address: the page address to be erased.
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state;
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    /* if the last operation is completed, start page erase */
    if (FMC_READY == fmc_state) {
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
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state;
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* start whole chip erase */
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
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
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
/*
    \brief      FMC program a half word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: halfword to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* set the PG bit to start program */
        FMC_CTL |= FMC_CTL_PG;
        REG16(address) = data;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the PG bit */
        FMC_CTL &= ~FMC_CTL_PG;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      unlock the option byte operation
    \param[in]  none
    \param[out] none
    \retval     none
 */
void ob_unlock(void)
{
    if(RESET == (FMC_CTL & FMC_CTL_OBWEN)){
        /* write the FMC key */
        FMC_OBKEY = UNLOCK_KEY0;
        FMC_OBKEY = UNLOCK_KEY1;
    }

    /* wait until OBWEN bit is set by hardware */
    while (RESET == (FMC_CTL & FMC_CTL_OBWEN)){
    }
}

/*!
    \brief      lock the option byte operation
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
    \brief      erase the FMC option byte
    unlock the FMC_CTL and option byte before calling this function
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum ob_erase(void)
{
    uint16_t temp_spc = FMC_NSPC;

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    /* check the option byte security protection value */
    if(RESET != ob_spc_get()){
        temp_spc = FMC_USPC;
    }

    if(FMC_READY == fmc_state){

        /* start erase the option byte */
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;
            /* set the OBPG bit */
            FMC_CTL |= FMC_CTL_OBPG;
            /* no security protection */
            OB_SPC = (uint16_t) temp_spc;
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
            if (FMC_TOERR != fmc_state) {
                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            }
        }else{
            if(FMC_TOERR != fmc_state){
                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      enable write protection
    \param[in]  ob_wp: specify sector to be write protected, set the bit to 1 if
    you want to protect the corresponding pages. meanwhile, sector
    macro could used to set specific sector write protected.
    one or more parameters can be selected which are shown as below:
      \arg        OB_WP_x(x = 0..31): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp)
{
    uint16_t temp_wp0, temp_wp1, temp_wp2, temp_wp3;

    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    ob_wp = (uint32_t) (~ob_wp);
    temp_wp0 = (uint16_t) (ob_wp & OB_WP0_WP0);
    temp_wp1 = (uint16_t) ((ob_wp & OB_WP1_WP1) >> 8U);
    temp_wp2 = (uint16_t) ((ob_wp & OB_WP2_WP2) >> 16U);
    temp_wp3 = (uint16_t) ((ob_wp & OB_WP3_WP3) >> 24U);

    if(FMC_READY == fmc_state){

        /* set the OBPG bit*/
        FMC_CTL |= FMC_CTL_OBPG;

        if(0xFFU != temp_wp0){
            OB_WP0 = temp_wp0;

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if((FMC_READY == fmc_state) && (0xFFU != temp_wp1)){
            OB_WP1 = temp_wp1;

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if((FMC_READY == fmc_state) && (0xFFU != temp_wp2)){
            OB_WP2 = temp_wp2;

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if((FMC_READY == fmc_state) && (0xFFU != temp_wp3)){
            OB_WP3 = temp_wp3;

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if(FMC_TOERR != fmc_state){
            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure security protection
    \param[in]  ob_spc: specify security protection
    only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_USPC: under security protection
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_CTL |= FMC_CTL_OBER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* reset the OBER bit */
            FMC_CTL &= ~FMC_CTL_OBER;

            /* start the option byte program */
            FMC_CTL |= FMC_CTL_OBPG;

            OB_SPC = (uint16_t) ob_spc;

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

            if (FMC_TOERR != fmc_state) {
                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            }
        }else{
            if (FMC_TOERR != fmc_state) {
                /* reset the OBER bit */
                FMC_CTL &= ~FMC_CTL_OBER;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the FMC user option byte
    \param[in]  ob_fwdgt: option byte watchdog value
      \arg        OB_FWDGT_SW: software free watchdog
      \arg        OB_FWDGT_HW: hardware free watchdog
    \param[in]  ob_deepsleep: option byte deepsleep reset value
      \arg        OB_DEEPSLEEP_NRST: no reset when entering deepsleep mode
      \arg        OB_DEEPSLEEP_RST: generate a reset instead of entering deepsleep mode
    \param[in]  ob_stdby:option byte standby reset value
      \arg        OB_STDBY_NRST: no reset when entering standby mode
      \arg        OB_STDBY_RST: generate a reset instead of entering standby mode
    \param[in]  ob_boot: specifies the option byte boot bank value
      \arg        OB_BOOT_B0: boot from bank0
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum ob_user_write(uint8_t ob_fwdgt, uint8_t ob_deepsleep, uint8_t ob_stdby, uint8_t ob_boot)
{
    fmc_state_enum fmc_state = FMC_READY;
    uint8_t temp;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* set the OBPG bit*/
        FMC_CTL |= FMC_CTL_OBPG;

        temp = ((uint8_t)((uint8_t)((uint8_t)(ob_boot | ob_fwdgt) | ob_deepsleep) | ob_stdby) | OB_USER_MASK);
        OB_USER = (uint16_t) temp;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_TOERR != fmc_state){
            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the FMC data option byte
    \param[in]  address: the option bytes address to be programmed
    \param[in]  data: the byte to be programmed
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum ob_data_program(uint32_t address, uint8_t data)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* set the OBPG bit */
        FMC_CTL |= FMC_CTL_OBPG;
        REG16(address) = data;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_TOERR != fmc_state){
            /* reset the OBPG bit */
            FMC_CTL &= ~FMC_CTL_OBPG;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get OB_USER in register FMC_OBSTAT
    \param[in]  none
    \param[out] none
    \retval     the FMC user option byte values
 */
uint8_t ob_user_get(void)
{
    /* return the FMC user option byte value */
    return (uint8_t) (FMC_OBSTAT >> 2U);
}

/*!
    \brief      get OB_DATA in register FMC_OBSTAT
    \param[in]  none
    \param[out] none
    \retval     ob_data
 */
uint16_t ob_data_get(void)
{
    return (uint16_t) (FMC_OBSTAT >> 10U);
}

/*!
    \brief      get the FMC option byte write protection
    \param[in]  none
    \param[out] none
    \retval     the FMC write protection option byte value
 */
uint32_t ob_write_protection_get(void)
{
    /* return the FMC write protection option byte value */
    return FMC_WP;
}

/*!
    \brief      get FMC option byte security protection state
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
 */
FlagStatus ob_spc_get(void)
{
    FlagStatus spc_state = RESET;

    if(RESET != (FMC_OBSTAT & FMC_OBSTAT_SPC)){
        spc_state = SET;
    }else{
        spc_state = RESET;
    }
    return spc_state;
}

/*!
    \brief      enable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
    only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: enable FMC end of program interrupt
      \arg        FMC_INT_ERR: enable FMC error interrupt
    \param[out] none
    \retval     none
 */
void fmc_interrupt_enable(fmc_int_enum interrupt)
{
    FMC_CTL |= (uint32_t)interrupt;
}

/*!
    \brief      disable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
    only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: enable FMC end of program interrupt
      \arg        FMC_INT_ERR: enable FMC error interrupt
    \param[out] none
    \retval     none
 */
void fmc_interrupt_disable(fmc_int_enum interrupt)
{
    FMC_CTL &= ~(uint32_t)interrupt;
}

/*!
    \brief      check flag is set or not
    \param[in]  flag: check FMC flag
    only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: FMC busy flag
      \arg        FMC_FLAG_PGERR: FMC operation error flag
      \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag
      \arg        FMC_FLAG_END: FMC end of operation flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
 */
FlagStatus fmc_flag_get(fmc_flag_enum flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag){
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
 \brief      clear the FMC flag
 \param[in]  flag: clear FMC flag
 only one parameter can be selected which is shown as below:
 \arg        FMC_FLAG_PGERR: FMC operation error flag
 \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag
 \arg        FMC_FLAG_END: FMC end of operation flag
 \param[out] none
 \retval     none
 */
void fmc_flag_clear(fmc_flag_enum flag)
{
    /* clear the flags */
    FMC_STAT = flag;
}

/*!
    \brief      get FMC interrupt flag state
    \param[in]  flag: FMC interrupt flags, refer to fmc_interrupt_flag_enum
    only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_PGERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_WPERR: FMC erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
 */
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag){
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status;
}

/*!
    \brief      clear FMC interrupt flag state
    \param[in]  flag: FMC interrupt flags, refer to can_interrupt_flag_enum
    only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_PGERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_WPERR: FMC erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
     \param[out] none
     \retval     none
 */
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum flag)
{
    /* clear the flags */
    FMC_STAT = flag;
}

/*!
    \brief      get the FMC state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t) 0x00U != (FMC_STAT & FMC_STAT_BUSY)){
        fmc_state = FMC_BUSY;
    }else{
        if((uint32_t) 0x00U != (FMC_STAT & FMC_STAT_WPERR)){
            fmc_state = FMC_WPERR;
        }else{
            if((uint32_t) 0x00U != (FMC_STAT & (FMC_STAT_PGERR))){
                fmc_state = FMC_PGERR;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC is ready or not
    \param[in]  timeout: count of loop
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
 */
fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    }while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state){
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
