/*!
    \file    gd32f10x_fmc.c
    \brief   FMC driver

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
    \version 2020-09-30, V2.2.0, firmware for GD32F10x
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

#include "gd32f10x_fmc.h"

/*!
    \brief      set the wait state counter value
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
    if((RESET != (FMC_CTL0 & FMC_CTL0_LK))){
        /* write the FMC unlock key */
        FMC_KEY0 = UNLOCK_KEY0;
        FMC_KEY0 = UNLOCK_KEY1;
    }

    if(FMC_BANK0_SIZE < FMC_SIZE){
        /* write the FMC unlock key */
        if(RESET != (FMC_CTL1 & FMC_CTL1_LK)){
            FMC_KEY1 = UNLOCK_KEY0;
            FMC_KEY1 = UNLOCK_KEY1;
        }
    }
}

/*!
    \brief      unlock the FMC bank0 operation
                this function can be used for all GD32F10x devices.
                for GD32F10x_MD and GD32F10x_HD, this function unlocks bank0.
                for GD32F10x_XD and GD32F10x_CL with flash no more than 512KB, it is equivalent to fmc_unlock function.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank0_unlock(void)
{
    if((RESET != (FMC_CTL0 & FMC_CTL0_LK))){
        /* write the FMC unlock key */
        FMC_KEY0 = UNLOCK_KEY0;
        FMC_KEY0 = UNLOCK_KEY1;
    }
}

/*!
    \brief      unlock the FMC bank1 operation
                this function can be used for GD32F10x_XD and GD32F10x_CL with flash more than 512KB.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank1_unlock(void)
{
    if((RESET != (FMC_CTL1 & FMC_CTL1_LK))){
        /* write the FMC unlock key */
        FMC_KEY1 = UNLOCK_KEY0;
        FMC_KEY1 = UNLOCK_KEY1;
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
    FMC_CTL0 |= FMC_CTL0_LK;

    if(FMC_BANK0_SIZE < FMC_SIZE){
        /* set the LK bit */
        FMC_CTL1 |= FMC_CTL1_LK;
    }
}

/*!
    \brief      lock the FMC bank0 operation
                this function can be used for all GD32F10X devices.
                for GD32F10x_MD and GD32F10x_HD, this function unlocks bank0.
                for GD32F10x_XD and GD32F10x_CL with flash no more than 512KB, it is equivalent to fmc_unlock function.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank0_lock(void)
{
    /* set the LK bit*/
    FMC_CTL0 |= FMC_CTL0_LK;
}

/*!
    \brief      lock the FMC bank1 operation
                this function can be used for GD32F10x_XD and GD32F10x_CL with flash more than 512KB.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_bank1_lock(void)
{
    /* set the LK bit*/
    FMC_CTL1 |= FMC_CTL1_LK;
}

/*!
    \brief      erase page
    \param[in]  page_address: the page address to be erased.
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state;

    if(FMC_BANK0_SIZE < FMC_SIZE){
        if(FMC_BANK0_END_ADDRESS > page_address){
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* if the last operation is completed, start page erase */
            if(FMC_READY == fmc_state){
                FMC_CTL0 |= FMC_CTL0_PER;
                FMC_ADDR0 = page_address;
                FMC_CTL0 |= FMC_CTL0_START;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PER bit */
                FMC_CTL0 &= ~FMC_CTL0_PER;
            }
        }else{
            /* wait for the FMC ready */
            fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
            /* if the last operation is completed, start page erase */
            if(FMC_READY == fmc_state){
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_ADDR1 = page_address;
                if(FMC_OBSTAT & FMC_OBSTAT_SPC){
                    FMC_ADDR0 = page_address;
                }
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;
            }
        }
    }else{
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        /* if the last operation is completed, start page erase */
        if(FMC_READY == fmc_state){
            FMC_CTL0 |= FMC_CTL0_PER;
            FMC_ADDR0 = page_address;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the PER bit */
            FMC_CTL0 &= ~FMC_CTL0_PER;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      erase whole chip
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state;
    if(FMC_BANK0_SIZE < FMC_SIZE){
        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state){
            /* start whole chip erase */
            FMC_CTL0 |= FMC_CTL0_MER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the MER bit */
            FMC_CTL0 &= ~FMC_CTL0_MER;
        }
        fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
        if(FMC_READY == fmc_state){
            /* start whole chip erase */
            FMC_CTL1 |= FMC_CTL1_MER;
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the MER bit */
            FMC_CTL1 &= ~FMC_CTL1_MER;
        }
    }else{
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* start whole chip erase */
            FMC_CTL0 |= FMC_CTL0_MER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the MER bit */
            FMC_CTL0 &= ~FMC_CTL0_MER;
        }
    }
    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      erase bank0
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank0_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* start FMC bank0 erase */
        FMC_CTL0 |= FMC_CTL0_MER;
        FMC_CTL0 |= FMC_CTL0_START;
        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL0 &= ~FMC_CTL0_MER;
    }
    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      erase bank1
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank1_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);

   if(FMC_READY == fmc_state){
        /* start FMC bank1 erase */
        FMC_CTL1 |= FMC_CTL1_MER;
        FMC_CTL1 |= FMC_CTL1_START;
        /* wait for the FMC ready */
        fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL1 &= ~FMC_CTL1_MER;
    }
    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      program a word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    if(FMC_BANK0_SIZE < FMC_SIZE){
        if(FMC_BANK0_END_ADDRESS > address){
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state){
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG32(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }else{
            fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state){
                /* set the PG bit to start program */
                FMC_CTL1 |= FMC_CTL1_PG;
                REG32(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL1 &= ~FMC_CTL1_PG;
            }
        }
    }else{
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* set the PG bit to start program */
            FMC_CTL0 |= FMC_CTL0_PG;
            REG32(address) = data;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the PG bit */
            FMC_CTL0 &= ~FMC_CTL0_PG;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a half word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: halfword to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    if(FMC_BANK0_SIZE < FMC_SIZE){
        if(FMC_BANK0_END_ADDRESS > address){
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state){
                /* set the PG bit to start program */
                FMC_CTL0 |= FMC_CTL0_PG;
                REG16(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }else{
            fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state){
                /* set the PG bit to start program */
                FMC_CTL1 |= FMC_CTL1_PG;
                REG16(address) = data;
                /* wait for the FMC ready */
                fmc_state = fmc_bank1_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL1 &= ~FMC_CTL1_PG;
            }
        }
    }else{
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* set the PG bit to start program */
            FMC_CTL0 |= FMC_CTL0_PG;
            REG16(address) = data;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            /* reset the PG bit */
            FMC_CTL0 &= ~FMC_CTL0_PG;
        }
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
    if(RESET == (FMC_CTL0 & FMC_CTL0_OBWEN)){
        /* write the FMC key */
        FMC_OBKEY = UNLOCK_KEY0;
        FMC_OBKEY = UNLOCK_KEY1;
    }

    /* wait until OBWEN bit is set by hardware */
    while(RESET == (FMC_CTL0 & FMC_CTL0_OBWEN)){
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
    FMC_CTL0 &= ~FMC_CTL0_OBWEN;
}

/*!
    \brief      erase the FMC option byte
                unlock the FMC_CTL0 and option byte before calling this function
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum ob_erase(void)
{
    uint16_t temp_spc = FMC_NSPC;

    fmc_state_enum fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    /* check the option byte security protection value */
    if(RESET != ob_spc_get()){
        temp_spc = FMC_USPC;
    }

    if(FMC_READY == fmc_state){

        /* start erase the option byte */
        FMC_CTL0 |= FMC_CTL0_OBER;
        FMC_CTL0 |= FMC_CTL0_START;

        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* reset the OBER bit */
            FMC_CTL0 &= ~FMC_CTL0_OBER;
            /* set the OBPG bit */
            FMC_CTL0 |= FMC_CTL0_OBPG;
            /* no security protection */
            OB_SPC = (uint16_t)temp_spc;
            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
            if(FMC_TOERR != fmc_state){
                /* reset the OBPG bit */
                FMC_CTL0 &= ~FMC_CTL0_OBPG;
            }
        }else{
            if(FMC_TOERR != fmc_state){
                /* reset the OBPG bit */
                FMC_CTL0 &= ~FMC_CTL0_OBPG;
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
      \arg        OB_WPx(x = 0..31): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp)
{
    uint16_t temp_wp0, temp_wp1, temp_wp2, temp_wp3;

    fmc_state_enum fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    ob_wp = (uint32_t)(~ob_wp);
    temp_wp0 = (uint16_t)(ob_wp & OB_WP0_WP0);
    temp_wp1 = (uint16_t)((ob_wp & OB_WP1_WP1) >> 8U);
    temp_wp2 = (uint16_t)((ob_wp & OB_WP2_WP2) >> 16U);
    temp_wp3 = (uint16_t)((ob_wp & OB_WP3_WP3) >> 24U);

    if(FMC_READY == fmc_state){

        /* set the OBPG bit*/
        FMC_CTL0 |= FMC_CTL0_OBPG;

        if(0xFFU != temp_wp0){
            OB_WP0 = temp_wp0;

            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if((FMC_READY == fmc_state) && (0xFFU != temp_wp1)){
            OB_WP1 = temp_wp1;

            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if((FMC_READY == fmc_state) && (0xFFU != temp_wp2)){
            OB_WP2 = temp_wp2;

            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if((FMC_READY == fmc_state) && (0xFFU != temp_wp3)){
            OB_WP3 = temp_wp3;

            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);
        }
        if(FMC_TOERR != fmc_state){
            /* reset the OBPG bit */
            FMC_CTL0 &= ~FMC_CTL0_OBPG;
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
    fmc_state_enum fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_CTL0 |= FMC_CTL0_OBER;
        FMC_CTL0 |= FMC_CTL0_START;

        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state){
            /* reset the OBER bit */
            FMC_CTL0 &= ~FMC_CTL0_OBER;

            /* start the option byte program */
            FMC_CTL0 |= FMC_CTL0_OBPG;

            OB_SPC = (uint16_t)ob_spc;

            /* wait for the FMC ready */
            fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_TOERR != fmc_state){
                /* reset the OBPG bit */
                FMC_CTL0 &= ~FMC_CTL0_OBPG;
            }
        }else{
            if(FMC_TOERR != fmc_state){
                /* reset the OBER bit */
                FMC_CTL0 &= ~FMC_CTL0_OBER;
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
      \arg        OB_BOOT_B1: boot from bank1 or bank0 if bank1 is void
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum ob_user_write(uint8_t ob_fwdgt, uint8_t ob_deepsleep, uint8_t ob_stdby, uint8_t ob_boot)
{
    fmc_state_enum fmc_state = FMC_READY;
    uint8_t temp;

    /* wait for the FMC ready */
    fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* set the OBPG bit*/
        FMC_CTL0 |= FMC_CTL0_OBPG;

        temp = ((uint8_t)((uint8_t)((uint8_t)(ob_boot | ob_fwdgt) | ob_deepsleep) | ob_stdby) | OB_USER_MASK);
        OB_USER = (uint16_t)temp;

        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_TOERR != fmc_state){
            /* reset the OBPG bit */
            FMC_CTL0 &= ~FMC_CTL0_OBPG;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program option bytes data
    \param[in]  address: the option bytes address to be programmed
    \param[in]  data: the byte to be programmed
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum ob_data_program(uint32_t address, uint8_t data)
{
    fmc_state_enum fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* set the OBPG bit */
        FMC_CTL0 |= FMC_CTL0_OBPG;
        REG16(address) = data;

        /* wait for the FMC ready */
        fmc_state = fmc_bank0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_TOERR != fmc_state){
            /* reset the OBPG bit */
            FMC_CTL0 &= ~FMC_CTL0_OBPG;
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get the FMC user option byte
    \param[in]  none
    \param[out] none
    \retval     the FMC user option byte values
*/
uint8_t ob_user_get(void)
{
    /* return the FMC user option byte value */
    return (uint8_t)(FMC_OBSTAT >> 2U);
}

/*!
    \brief      get OB_DATA in register FMC_OBSTAT
    \param[in]  none
    \param[out] none
    \retval     ob_data
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)(FMC_OBSTAT >> 10U);
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
    \brief      get the FMC option byte security protection
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
      \arg        FMC_INT_BANK0_END: enable FMC end of program interrupt
      \arg        FMC_INT_BANK0_ERR: enable FMC error interrupt
      \arg        FMC_INT_BANK1_END: enable FMC bank1 end of program interrupt
      \arg        FMC_INT_BANK1_ERR: enable FMC bank1 error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t interrupt)
{
    FMC_REG_VAL(interrupt) |= BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      disable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_BANK0_END: enable FMC end of program interrupt
      \arg        FMC_INT_BANK0_ERR: enable FMC error interrupt
      \arg        FMC_INT_BANK1_END: enable FMC bank1 end of program interrupt
      \arg        FMC_INT_BANK1_ERR: enable FMC bank1 error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t interrupt)
{
    FMC_REG_VAL(interrupt) &= ~BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      check flag is set or not
    \param[in]  flag: check FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BANK0_BUSY: FMC bank0 busy flag bit
      \arg        FMC_FLAG_BANK0_PGERR: FMC bank0 operation error flag bit
      \arg        FMC_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK0_END: FMC bank0 end of operation flag bit
      \arg        FMC_FLAG_OBERR: FMC option bytes read error flag bit
      \arg        FMC_FLAG_BANK1_BUSY: FMC bank1 busy flag bit
      \arg        FMC_FLAG_BANK1_PGERR: FMC bank1 operation error flag bit
      \arg        FMC_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK1_END: FMC bank1 end of operation flag bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t flag)
{
    if(RESET != (FMC_REG_VAL(flag) & BIT(FMC_BIT_POS(flag)))){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the FMC flag
    \param[in]  flag: clear FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BANK0_PGERR: FMC bank0 operation error flag bit
      \arg        FMC_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK0_END: FMC bank0 end of operation flag bit
      \arg        FMC_FLAG_BANK1_PGERR: FMC bank1 operation error flag bit
      \arg        FMC_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error flag bit
      \arg        FMC_FLAG_BANK1_END: FMC bank1 end of operation flag bit
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t flag)
{
    FMC_REG_VAL(flag) |= BIT(FMC_BIT_POS(flag));
}

/*!
    \brief      get FMC interrupt flag state
    \param[in]  flag: FMC interrupt flags, refer to fmc_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_BANK0_PGERR: FMC bank0 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_END: FMC bank0 end of operation interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_PGERR: FMC bank1 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_END: FMC bank1 end of operation interrupt flag bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;

    if(FMC_STAT0_REG_OFFSET == FMC_REG_OFFSET_GET(flag)){
        /* get the staus of interrupt flag */
        ret1 = (uint32_t)(FMC_REG_VALS(flag) & BIT(FMC_BIT_POS0(flag)));
        /* get the staus of interrupt enale bit */
        ret2 = (uint32_t)(FMC_CTL0 & BIT(FMC_BIT_POS1(flag)));
    }else{
        /* get the staus of interrupt flag */
        ret1 = (uint32_t)(FMC_REG_VALS(flag) & BIT(FMC_BIT_POS0(flag)));
        /* get the staus of interrupt enale bit */
        ret2 = (uint32_t)(FMC_CTL1 & BIT(FMC_BIT_POS1(flag)));
    }

    if(ret1 && ret2){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear FMC interrupt flag state
    \param[in]  flag: FMC interrupt flags, refer to can_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_BANK0_PGERR: FMC bank0 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_WPERR: FMC bank0 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK0_END: FMC bank0 end of operation interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_PGERR: FMC bank1 operation error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_WPERR: FMC bank1 erase/program protection error interrupt flag bit
      \arg        FMC_INT_FLAG_BANK1_END: FMC bank1 end of operation interrupt flag bit
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum flag)
{
    FMC_REG_VALS(flag) |= BIT(FMC_BIT_POS0(flag));
}

/*!
    \brief      get the FMC bank0 state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank0_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_BUSY)){
        fmc_state = FMC_BUSY;
    }else{
        if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_WPERR)){
            fmc_state = FMC_WPERR;
        }else{
            if((uint32_t)0x00U != (FMC_STAT0 & (FMC_STAT0_PGERR))){
                fmc_state = FMC_PGERR;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get the FMC bank1 state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank1_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_BUSY)){
        fmc_state = FMC_BUSY;
    }else{
        if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_WPERR)){
            fmc_state = FMC_WPERR;
        }else{
            if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_PGERR)){
                fmc_state = FMC_PGERR;
            }
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC bank0 is ready or not
    \param[in]  timeout: count of loop
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank0_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_bank0_state_get();
        timeout--;
    }while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state){
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC bank1 is ready or not
    \param[in]  timeout: count of loop
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
*/
fmc_state_enum fmc_bank1_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_bank1_state_get();
        timeout--;
    }while((FMC_BUSY == fmc_state) && (0x00U != timeout));

    if(FMC_BUSY == fmc_state){
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
