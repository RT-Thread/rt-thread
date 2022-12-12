/*!
    \file  gd32f3x0_fmc.c
    \brief FMC driver
    
    \version 2017-06-06, V1.0.0, firmware for GD32F3x0
    \version 2019-06-01, V2.0.0, firmware for GD32F3x0
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#include "gd32f3x0_fmc.h"

/* FMC main memory programming functions */

/*!
    \brief      unlock the main FMC operation
                it is better to used in pairs with fmc_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if((RESET != (FMC_CTL & FMC_CTL_LK))){
        /* write the FMC key */
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
    /* set the LK bit*/
    FMC_CTL |= FMC_CTL_LK;
}

/*!
    \brief      set the wait state counter value
    \param[in]  wscnt: wait state counter value
                only one parameter can be selected which is shown as below:
      \arg        WS_WSCNT_0: 0 wait state added
      \arg        WS_WSCNT_1: 1 wait state added
      \arg        WS_WSCNT_2: 2 wait state added
    \param[out] none
    \retval     none
*/
void fmc_wscnt_set(uint8_t wscnt)
{
    uint32_t reg;
    
    reg = FMC_WS;
    /* set the wait state counter value */
    reg &= ~FMC_WS_WSCNT;
    FMC_WS = (reg | wscnt);
}

/*!
    \brief      fmc wait state enable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_wait_state_enable(void)
{
    /* unlock the main flash */
    fmc_unlock();

    /* set the WSEN bit in register FMC_WSEN */
    FMC_WSEN |= FMC_WSEN_WSEN;

    /* lock the main flash after operation */
    fmc_lock();
}

/*!
    \brief      fmc wait state disable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_wait_state_disable(void)
{
    /* unlock the main flash */
    fmc_unlock();

    /* reset the WSEN bit in register FMC_WSEN */
    FMC_WSEN &= ~FMC_WSEN_WSEN;

    /* lock the main flash after operation */
    fmc_lock();
}

/*!
    \brief      erase page
    \param[in]  page_address: target page start address
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){ 
        /* start page erase */
        FMC_CTL |= FMC_CTL_PER;
        FMC_ADDR = page_address;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    
        /* reset the PER bit */
        FMC_CTL &= ~FMC_CTL_PER;
    }
    
    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      erase whole chip
    \param[in]  none
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){ 
        /* start chip erase */
        FMC_CTL |= FMC_CTL_MER; 
        FMC_CTL |= FMC_CTL_START;
    
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
    }
    
    /* return the fmc state  */
    return fmc_state;
}

/*!
    \brief      program a word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
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

/*!
    \brief      program a half word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
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
    \brief      program a word at the corresponding address without erasing
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum fmc_word_reprogram(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    FMC_WSEN |= FMC_WSEN_BPEN;

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

/* FMC option bytes programming functions */

/*!
    \brief      unlock the option byte operation
                it is better to used in pairs with ob_lock
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
}

/*!
    \brief      lock the option byte operation
                it is better to used in pairs with ob_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_lock(void)
{
    /* reset the OBWE bit */
    FMC_CTL &= ~FMC_CTL_OBWEN;
}

/*!
    \brief      reload the option byte and generate a system reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_reset(void)
{
    /* set the OBRLD bit */
    FMC_CTL |= FMC_CTL_OBRLD;
}

/*!
    \brief      erase the option byte
                programmer must ensure FMC & option byte are both unlocked before calling this function
    \param[in]  none
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum ob_erase(void)
{
    uint16_t fmc_spc;
    
    uint32_t fmc_plevel = ob_obstat_plevel_get();
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    /* get the original option byte security protection code */
    if(OB_OBSTAT_PLEVEL_NO == fmc_plevel){
        fmc_spc = FMC_NSPC;
    }else if(OB_OBSTAT_PLEVEL_LOW == fmc_plevel){
        fmc_spc = FMC_LSPC;
    }else{
        fmc_spc = FMC_HSPC;
        fmc_state = FMC_OB_HSPC;
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

            /* restore the last get option byte security protection code */
            OB_SPC = fmc_spc;
            OB_USER = OB_USER_DEFAULT;

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
 
            if(FMC_TOERR != fmc_state){
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
    \brief      enable option byte write protection(OB_WP) depending on current option byte 
    \param[in]  ob_wp: write protection configuration data
                       setting the bit of ob_wp means enabling the corresponding sector write protection
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum ob_write_protection_enable(uint16_t ob_wp)
{
    uint8_t ob_wrp0, ob_wrp1;
    ob_parm_struct ob_parm;
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    ob_parm_get(&ob_parm);
    ob_wp   = (uint16_t)(~ob_wp);
    ob_wrp0 = (uint8_t)(ob_wp & OB_LWP);
    ob_wrp1 = (uint8_t)((ob_wp & OB_HWP) >> 8U);
    
    if(0xFFU == (uint8_t)OB_WP0){
        if (0xFFU == (uint8_t)OB_WP1){
            if(FMC_READY == fmc_state){
                /* set the OBPG bit*/
                FMC_CTL |= FMC_CTL_OBPG;

                if(0xFFU != ob_wrp0){
                    OB_WP0 = ob_wrp0 ;
                    /* wait for the FMC ready */
                    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
                }
                
                if((FMC_READY == fmc_state) && (0xFFU != ob_wrp1)){
                    OB_WP1 = ob_wrp1 ;
                    /* wait for the FMC ready */
                    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
                }
                
                if(FMC_TOERR != fmc_state){
                    /* reset the OBPG bit */
                    FMC_CTL &= ~FMC_CTL_OBPG;
                }
            } 
        }
    }else{
        if(FMC_READY == fmc_state){
            /* start erase the option byte */
            FMC_CTL |= FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_START;
        
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        
            if(FMC_READY == fmc_state){
            
                /* reset the OBER bit */
                FMC_CTL &= ~FMC_CTL_OBER;
          
                /* enable the option bytes programming */
                FMC_CTL |= FMC_CTL_OBPG;
           
                ob_value_modify(OB_WP_ADDR0, ob_wp ,&ob_parm);
                /* wait for the FMC ready */
                fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT); 
        
                if(FMC_TOERR != fmc_state){
                    /* reset the OBPG bit */
                    FMC_CTL &= ~FMC_CTL_OBPG;
                }
            }else{
                if(FMC_TOERR != fmc_state){
                    /* reset the OBER bit */
                    FMC_CTL &= ~FMC_CTL_OBER;
                }
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure security protection
    \param[in]  ob_spc: specify security protection code
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    
    ob_parm_struct ob_parm;
    ob_parm_get(&ob_parm);

    /* the OB_SPC byte cannot be reprogrammed if protection level is high */
    if(OB_OBSTAT_PLEVEL_HIGH == ob_obstat_plevel_get()){
        fmc_state = FMC_OB_HSPC;
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
      
            /* enable the option bytes programming */
            FMC_CTL |= FMC_CTL_OBPG;
       
            ob_value_modify(OB_SPC_ADDR, (uint16_t)ob_spc ,&ob_parm);
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT); 
    
            if(FMC_TOERR != fmc_state){
                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            }
        }else{
            if(FMC_TOERR != fmc_state){
                /* reset the OBER bit */
                FMC_CTL &= ~FMC_CTL_OBER;
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the FMC user option byte depending on current option byte
    \param[in]  ob_user: user option byte
                one or more parameters (bitwise AND) can be selected which are shown as below:
      \arg        OB_FWDGT_HW: hardware free watchdog timer
      \arg        OB_DEEPSLEEP_RST: generate a reset instead of entering deepsleep mode
      \arg        OB_STDBY_RST: generate a reset instead of entering standby mode
      \arg        OB_BOOT1_SET_1: BOOT1 bit is 1
      \arg        OB_VDDA_DISABLE: disable VDDA monitor
      \arg        OB_SRAM_PARITY_ENABLE: enable sram parity check
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum ob_user_write(uint8_t ob_user)
{
    /* check whether FMC is ready or not */
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    ob_parm_struct ob_parm;
    ob_parm_get(&ob_parm);
    
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

            /* restore the last get option byte security protection code */
            ob_value_modify(OB_USER_ADDR, (uint16_t)ob_user, &ob_parm);

            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
 
            if(FMC_TOERR != fmc_state){
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
    \brief      program the FMC data option byte
    \param[in]  address: OB_DATA_ADDR0 or OB_DATA_ADDR1
                only one parameter can be selected which is shown as below:
      \arg        OB_DATA_ADDR0: option byte data address 0
      \arg        OB_DATA_ADDR1: option byte data address 1
    \param[in]  data: the byte to be programmed
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum ob_data_program(uint32_t address, uint8_t data)
{   
    fmc_state_enum fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    ob_parm_struct ob_parm;
    ob_parm_get(&ob_parm);
    if(0xFFU == REG8(address))
    {
        if(FMC_READY == fmc_state){
            /* set the OBPG bit */
            FMC_CTL |= FMC_CTL_OBPG; 
             
            REG16(address) = data ;
        
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        
            if(FMC_TOERR != fmc_state){
                /* reset the OBPG bit */
                FMC_CTL &= ~FMC_CTL_OBPG;
            }
        }
    }else{
        if(FMC_READY == fmc_state){
            /* start erase the option byte */
            FMC_CTL |= FMC_CTL_OBER;
            FMC_CTL |= FMC_CTL_START;
        
            /* wait for the FMC ready */
            fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        
            if(FMC_READY == fmc_state){
            
                /* reset the OBER bit */
                FMC_CTL &= ~FMC_CTL_OBER;
          
                /* enable the option bytes programming */
                FMC_CTL |= FMC_CTL_OBPG;

                ob_value_modify(address, (uint16_t)data ,&ob_parm);
                /* wait for the FMC ready */
                fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT); 
        
                if(FMC_TOERR != fmc_state){
                    /* reset the OBPG bit */
                    FMC_CTL &= ~FMC_CTL_OBPG;
                }
            }else{
                if(FMC_TOERR != fmc_state){
                    /* reset the OBER bit */
                    FMC_CTL &= ~FMC_CTL_OBER;
                }
            }
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get OB_USER in register FMC_OBSTAT
    \param[in]  none
    \param[out] none
    \retval     ob_user
*/
uint8_t ob_user_get(void)
{
    return (uint8_t)(FMC_OBSTAT >> 8U);
}

/*!
    \brief      get OB_DATA in register FMC_OBSTAT
    \param[in]  none
    \param[out] none
    \retval     ob_data
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)(FMC_OBSTAT >> 16U);
}

/*!
    \brief      get the FMC option byte write protection (OB_WP) in register FMC_WP
    \param[in]  none
    \param[out] none
    \retval     OB_WP
*/
uint16_t ob_write_protection_get(void)
{
    return (uint16_t)(FMC_WP);
}

/*!
    \brief      get the value of FMC option byte security protection level (PLEVEL) in FMC_OBSTAT register
    \param[in]  none
    \param[out] none
    \retval     the value of PLEVEL
*/
uint32_t ob_obstat_plevel_get(void)
{
    return (FMC_OBSTAT & (FMC_OBSTAT_PLEVEL_BIT0 | FMC_OBSTAT_PLEVEL_BIT1));
}

/* FMC interrupts and flags management functions */
/*!
    \brief      enable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
                one or more parameters can be selected which are shown as below:
      \arg        FMC_INTEN_END: FMC end of operation interrupt
      \arg        FMC_INTEN_ERR: FMC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t interrupt)
{
    FMC_CTL |= interrupt;
}

/*!
    \brief      disable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
                one or more parameters can be selected which are shown as below:
      \arg        FMC_INTEN_END: FMC end of operation interrupt
      \arg        FMC_INTEN_ERR: FMC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t interrupt)
{
    FMC_CTL &= ~(uint32_t)interrupt;
}

/*!
    \brief      get flag set or reset
    \param[in]  flag: check FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: FMC busy flag
      \arg        FMC_FLAG_PGERR: FMC programming error flag
      \arg        FMC_FLAG_WPERR: FMC write protection error flag
      \arg        FMC_FLAG_END: FMC end of programming flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag){
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status; 
}

/*!
    \brief      clear the FMC pending flag by writing 1
    \param[in]  flag: clear FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_PGERR: FMC programming error flag
      \arg        FMC_FLAG_WPERR: FMC write protection error flag
      \arg        FMC_FLAG_END: fmc end of programming flag
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t flag)
{
    /* clear the flags */
    FMC_STAT = flag;
}

/*!
    \brief      get flag set or reset
    \param[in]  flag: check FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_PGERR: FMC programming error flag
      \arg        FMC_FLAG_WPERR: FMC write protection error flag
      \arg        FMC_FLAG_END: FMC end of programming flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;

    if(FMC_STAT & flag){
        status = SET;
    }
    /* return the state of corresponding FMC flag */
    return status; 
}

/*!
    \brief      clear the FMC pending flag by writing 1
    \param[in]  flag: clear FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_PGERR: FMC programming error flag
      \arg        FMC_FLAG_WPERR: FMC write protection error flag
      \arg        FMC_FLAG_END: fmc end of programming flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(uint32_t flag)
{
    /* clear the flags */
    FMC_STAT = flag;
}

/*!
    \brief      get the FMC state
    \param[in]  none
    \param[out] none
    \retval     fmc_state
*/
fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;
  
    if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_BUSY)){
        fmc_state = FMC_BUSY;
    }else{
        if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_WPERR)){
            fmc_state = FMC_WPERR;
        }else{
            if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGERR)){
                fmc_state = FMC_PGERR; 
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
    \retval     fmc_state
*/
fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;
  
    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    }while((FMC_BUSY == fmc_state) && (0U != timeout));
  
    if(FMC_BUSY == fmc_state){
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get current option byte value
    \param[in]  ob_parm: pointer to option byte parameter struct
    \param[out] ob_parm: pointer to option byte parameter struct
    \retval     none
*/
void ob_parm_get(ob_parm_struct *ob_parm)
{
    /* get current option byte value */
    ob_parm->spc = (uint8_t)OB_SPC;
    ob_parm->user = (uint8_t)OB_USER;
    ob_parm->data0 = (uint8_t)OB_DATA0;
    ob_parm->data1 = (uint8_t)OB_DATA1;
    ob_parm->wp0 = (uint8_t)OB_WP0;
    ob_parm->wp1 = (uint8_t)OB_WP1;
}

/*!
    \brief      modify the target option byte depending on the original value
    \param[in]  address: target option byte address
    \param[in]  value: target option byte value
    \param[in]  ob_parm: pointer to option byte parameter struct
    \param[out] none
    \retval     none
*/
void ob_value_modify(uint32_t address, uint16_t value,ob_parm_struct *ob_parm)
{
    uint8_t spc, user, data0, data1, wp0, wp1;
    /* store the original option bytes */
    spc = ob_parm->spc;
    user = ob_parm->user;
    data0 = ob_parm->data0;
    data1 = ob_parm->data1;
    wp0 = ob_parm->wp0;
    wp1 = ob_parm->wp1;
    
    /* bring in the target option byte */
    if(OB_SPC_ADDR == address){
        spc = (uint8_t)value;
    }else if(OB_DATA_ADDR0 == address){
        data0 = (uint8_t)value;
    }else if(OB_DATA_ADDR1 == address){
        data1 = (uint8_t)value;
    }else if(OB_USER_ADDR == address){
        user =  user & (uint8_t)value;
    }else{
        wp0 = wp0 & ((uint8_t) (value));
        wp1 = wp1 & ((uint8_t) (value >> 8U));
    }
    /* basing on original value, modify the target option byte */
    OB_SPC = spc;
    OB_USER = user;
    if(0xFFU != data0){
        OB_DATA0 = data0;
    }
    if(0xFFU != data1){
        OB_DATA1 = data1;
    }
    if(0xFFU != wp0){
        OB_WP0 = wp0;
    }
    if(0xFFU != wp1){
        OB_WP1 = wp1;  
    }
}
