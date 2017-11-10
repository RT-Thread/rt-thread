/*!
    \file  gd32f4xx_fmc.c
    \brief FMC driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_fmc.h"

/*!
    \brief      set the wait state counter value
    \param[in]  wscnt£ºwait state counter value
      \arg        WS_WSCNT_0: FMC 0 wait
      \arg        WS_WSCNT_1: FMC 1 wait
      \arg        WS_WSCNT_2: FMC 2 wait
      \arg        WS_WSCNT_3: FMC 3 wait
      \arg        WS_WSCNT_4: FMC 4 wait
      \arg        WS_WSCNT_5: FMC 5 wait
      \arg        WS_WSCNT_6: FMC 6 wait
      \arg        WS_WSCNT_7: FMC 7 wait
      \arg        WS_WSCNT_8: FMC 8 wait
      \arg        WS_WSCNT_9: FMC 9 wait
      \arg        WS_WSCNT_10: FMC 10 wait
      \arg        WS_WSCNT_11: FMC 11 wait
      \arg        WS_WSCNT_12: FMC 12 wait
      \arg        WS_WSCNT_13: FMC 13 wait
      \arg        WS_WSCNT_14: FMC 14 wait
      \arg        WS_WSCNT_15: FMC 15 wait
    \param[out] none
    \retval     none
*/
void fmc_wscnt_set(uint32_t wscnt)
{
    uint32_t reg;
    
    reg = FMC_WS;
    /* set the wait state counter value */
    reg &= ~FMC_WC_WSCNT;
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
        /* write the FMC key */
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
    /* set the LK bit*/
    FMC_CTL |= FMC_CTL_LK;
}

/*!
    \brief      erase sector
    \param[in]  fmc_sector: select the sector to erase
      \arg        CTL_SECTOR_NUMBER_0: sector 0 
      \arg        CTL_SECTOR_NUMBER_1: sector 1 
      \arg        CTL_SECTOR_NUMBER_2: sector 2 
      \arg        CTL_SECTOR_NUMBER_3: sector 3 
      \arg        CTL_SECTOR_NUMBER_4: sector 4 
      \arg        CTL_SECTOR_NUMBER_5: sector 5 
      \arg        CTL_SECTOR_NUMBER_6: sector 6 
      \arg        CTL_SECTOR_NUMBER_7: sector 7 
      \arg        CTL_SECTOR_NUMBER_8: sector 8 
      \arg        CTL_SECTOR_NUMBER_9: sector 9 
      \arg        CTL_SECTOR_NUMBER_10: sector 10 
      \arg        CTL_SECTOR_NUMBER_11: sector 11 
      \arg        CTL_SECTOR_NUMBER_12: sector 12 
      \arg        CTL_SECTOR_NUMBER_13: sector 13 
      \arg        CTL_SECTOR_NUMBER_14: sector 14 
      \arg        CTL_SECTOR_NUMBER_15: sector 15 
      \arg        CTL_SECTOR_NUMBER_16: sector 16 
      \arg        CTL_SECTOR_NUMBER_17: sector 17 
      \arg        CTL_SECTOR_NUMBER_18: sector 18 
      \arg        CTL_SECTOR_NUMBER_19: sector 19 
      \arg        CTL_SECTOR_NUMBER_20: sector 20 
      \arg        CTL_SECTOR_NUMBER_21: sector 21 
      \arg        CTL_SECTOR_NUMBER_22: sector 22 
      \arg        CTL_SECTOR_NUMBER_23: sector 23 
      \arg        CTL_SECTOR_NUMBER_24: sector 24 
      \arg        CTL_SECTOR_NUMBER_25: sector 25 
      \arg        CTL_SECTOR_NUMBER_26: sector 26 
      \arg        CTL_SECTOR_NUMBER_27: sector 27 
      \arg        CTL_SECTOR_NUMBER_28: sector 28 
      \arg        CTL_SECTOR_NUMBER_29: sector 29 
      \arg        CTL_SECTOR_NUMBER_30: sector 30 
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_sector_erase(uint32_t fmc_sector)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){ 
        /* start sector erase */
        FMC_CTL &= ~FMC_CTL_SN;
        FMC_CTL |= (FMC_CTL_SER | fmc_sector);
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    
        /* reset the SER bit */
        FMC_CTL &= (~FMC_CTL_SER);
        FMC_CTL &= ~FMC_CTL_SN; 
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      erase whole chip
    \param[in]  none
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){ 
        /* start whole chip erase */  
        FMC_CTL |= (FMC_CTL_MER0 | FMC_CTL_MER1);
        FMC_CTL |= FMC_CTL_START;
    
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER bits */
        FMC_CTL &= ~(FMC_CTL_MER0 | FMC_CTL_MER1);
    }

    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      erase all FMC sectors in bank0
    \param[in]  none
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_bank0_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        /* start FMC bank0 erase */
        FMC_CTL |= FMC_CTL_MER0;
        FMC_CTL |= FMC_CTL_START;
    
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER0 bit */
        FMC_CTL &= (~FMC_CTL_MER0);
    }

    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      erase all FMC sectors in bank1
    \param[in]  none
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_bank1_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
   if(FMC_READY == fmc_state){
        /* start FMC bank1 erase */
        FMC_CTL |= FMC_CTL_MER1;
        FMC_CTL |= FMC_CTL_START;
    
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the MER1 bit */
        FMC_CTL &= (~FMC_CTL_MER1);
    }

    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      program a word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){
        /* set the PG bit to start program */
        FMC_CTL &= ~FMC_CTL_PSZ;
        FMC_CTL |= CTL_PSZ_WORD;
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
    \param[in]  data: halfword to program
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){ 
        /* set the PG bit to start program */
        FMC_CTL &= ~FMC_CTL_PSZ;
        FMC_CTL |= CTL_PSZ_HALF_WORD;
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
    \brief      program a byte at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: byte to program
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_byte_program(uint32_t address, uint8_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){
        /* set the PG bit to start program */
        FMC_CTL &= ~FMC_CTL_PSZ;
        FMC_CTL |= CTL_PSZ_BYTE;
        FMC_CTL |= FMC_CTL_PG;
  
        REG8(address) = data;

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
    if(RESET != (FMC_OBCTL0 & FMC_OBCTL0_OB_LK)){
        /* write the FMC key */
        FMC_OBKEY = OB_UNLOCK_KEY0;
        FMC_OBKEY = OB_UNLOCK_KEY1;
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
    /* reset the OB_LK bit */
    FMC_OBCTL0 &= ~FMC_OBCTL0_OB_LK;
}

/*!
    \brief      send option byte change command
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_start(void)
{
    /* set the OB_START bit in OBCTL0 register */
    FMC_OBCTL0 |= FMC_OBCTL0_OB_START;
}

/*!
    \brief      enable write protection
    \param[in]  ob_wp: specify sector to be write protected
      \arg        OB_WPx(x=0..11): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     none
*/
void ob_write_protection0_enable(uint32_t ob_wp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL0 &= (~((uint32_t)ob_wp << 16));
    }
}

/*!
    \brief      disable write protection
    \param[in]  ob_wp: specify sector to be write protected
      \arg        OB_WPx(x=0..11): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     none
*/
void ob_write_protection0_disable(uint32_t ob_wp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL0 |= ((uint32_t)ob_wp << 16);
    }
}

/*!
    \brief      enable write protection
    \param[in]  ob_wp: specify sector to be write protected
      \arg        OB_WPx(x=12..30): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     none
*/
void ob_write_protection1_enable(uint32_t ob_wp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL1 &= (~((uint32_t)ob_wp << 16));
    }
}

/*!
    \brief      disable write protection
    \param[in]  ob_wp: specify sector to be write protected
      \arg        OB_WPx(x=12..30): write protect specify sector
      \arg        OB_WP_ALL: write protect all sector
    \param[out] none
    \retval     none
*/
void ob_write_protection1_disable(uint32_t ob_wp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL1 |= ((uint32_t)ob_wp << 16);
    }
}
/*!
    \brief      configure the protection mode
    \param[in]  ob_drp: configure the protection mode of WPx bits
      \arg        OB_DRP_DISABLE: the WPx bits used as erase/program protection of each sector
      \arg        OB_DRP_ENABLE: the WPx bits used as erase/program protection and D-bus read protection of each sector
    \param[out] none
    \retval     none
*/
void ob_drp_config(uint32_t ob_drp)
{
    FMC_OBCTL0 &= ~FMC_OBCTL0_DRP; 
    FMC_OBCTL0 |= ob_drp;
}

/*!
    \brief      enable erase/program protection and D-bus read protection
    \param[in]  ob_drp: enable the WPx bits used as erase/program protection and D-bus read protection of each sector 
      \arg        OB_DRPx(x=0..11): erase/program protection and D-bus read protection of specify sector
      \arg        OB_DRP_ALL: erase/program protection and D-bus read protection of all sector
    \param[out] none
    \retval     none
*/
void ob_drp0_enable(uint32_t ob_drp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL0 |= ((uint32_t)ob_drp << 16);
    }
}

/*!
    \brief      disable erase/program protection and D-bus read protection
    \param[in]  ob_drp: disable the WPx bits used as erase/program protection and D-bus read protection of each sector
      \arg        OB_DRPx(x=0..11): erase/program protection and D-bus read protection of specify sector
      \arg        OB_DRP_ALL: erase/program protection and D-bus read protection of all sector
    \param[out] none
    \retval     none
*/
void ob_drp0_disable(uint32_t ob_drp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL0 &= (~((uint32_t)ob_drp << 16));
    }
}

/*!
    \brief      enable erase/program protection and D-bus read protection
    \param[in]  ob_drp: enable the WPx bits used as erase/program protection and D-bus read protection of each sector 
      \arg        OB_DRPx(x=12..30): erase/program protection and D-bus read protection of specify sector
      \arg        OB_DRP_ALL: erase/program protection and D-bus read protection of all sector
    \param[out] none
    \retval     none
*/
void ob_drp1_enable(uint32_t ob_drp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL1 |= ((uint32_t)ob_drp << 16);  
    }
}

/*!
    \brief      disable erase/program protection and D-bus read protection
    \param[in]  ob_drp: disable the WPx bits used as erase/program protection and D-bus read protection of each sector
      \arg        OB_DRPx(x=12..30): erase/program protection and D-bus read protection of specify sector
      \arg        OB_DRP_ALL: erase/program protection and D-bus read protection of all sector
    \param[out] none
    \retval     none
*/
void ob_drp1_disable(uint32_t ob_drp)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        FMC_OBCTL1 &= (~((uint32_t)ob_drp << 16));
    }
}

/*!
    \brief      configure security protection level
    \param[in]  ob_spc: specify security protection level
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     none
*/
void ob_security_protection_config(uint8_t ob_spc)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state){
        uint32_t reg;
    
        reg = FMC_OBCTL0;
        /* reset the OBCTL0_SPC, set according to ob_spc */
        reg &= ~FMC_OBCTL0_SPC;
        FMC_OBCTL0 |= ((uint32_t)ob_spc << 8);
    }
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
    \param[out] none
    \retval     none
*/
void ob_user_write(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
  
    if(FMC_READY == fmc_state){
        uint32_t reg;
    
        reg = FMC_OBCTL0;
        /* reset the OB_FWDGT, OB_DEEPSLEEP and OB_STDBY, set according to ob_fwdgt ,ob_deepsleep and ob_stdby */
        reg &= ~(FMC_OBCTL0_NWDG_HW | FMC_OBCTL0_NRST_DPSLP | FMC_OBCTL0_NRST_STDBY);
        FMC_OBCTL0 = (reg | ob_fwdgt | ob_deepsleep | ob_stdby);
    }
}

/*!
    \brief      program the option byte BOR threshold value
    \param[in]  ob_bor_th: user option byte
      \arg        OB_BOR_TH_VALUE3: BOR threshold value 3
      \arg        OB_BOR_TH_VALUE2: BOR threshold value 2
      \arg        OB_BOR_TH_VALUE1: BOR threshold value 1
      \arg        OB_BOR_TH_OFF: no BOR function.
    \param[out] none
    \retval     none
*/
void ob_user_bor_threshold(uint32_t ob_bor_th)
{
    uint32_t reg;
    
    reg = FMC_OBCTL0;
    /* set the BOR level */
    reg &= ~FMC_OBCTL0_BOR_TH;
    FMC_OBCTL0 = (reg | ob_bor_th);
}

/*!
    \brief      configure the option byte boot bank value
    \param[in]  boot_mode: specifies the option byte boot bank value
      \arg        OB_BB_DISABLE: boot from bank0
      \arg        OB_BB_ENABLE: boot from bank1 or bank0 if bank1 is void
    \param[out] none
    \retval     none
*/
void ob_boot_mode_config(uint32_t boot_mode)
{
    uint32_t reg;
    
    reg = FMC_OBCTL0;
    /* set option byte boot bank value */
    reg &= ~FMC_OBCTL0_BB;
    FMC_OBCTL0 = (reg | boot_mode);
}

/*!
    \brief      get the FMC user option byte
    \param[in]  none
    \param[out] none
    \retval     the FMC user option byte values: ob_fwdgt(Bit0), ob_deepsleep(Bit1), ob_stdby(Bit2).
*/
uint8_t ob_user_get(void)
{
    return (uint8_t)((uint8_t)(FMC_OBCTL0 >> 5) & (uint8_t)0x07);
}

/*!
    \brief      get the FMC option byte write protection
    \param[in]  none
    \param[out] none
    \retval     the FMC write protection option byte value
*/
uint16_t ob_write_protection0_get(void)
{
    /* return the FMC write protection option byte value */
    return (uint16_t)(((uint16_t)(FMC_OBCTL0 >> 16)) & (uint16_t)0x0FFF);
}

/*!
    \brief      get the FMC option byte write protection
    \param[in]  none
    \param[out] none
    \retval     the FMC write protection option byte value
*/
uint16_t ob_write_protection1_get(void)
{
    /* return the the FMC write protection option byte value */
    return (uint16_t)(((uint16_t)(FMC_OBCTL1 >> 16)) & (uint16_t)0x0FFF);
}

/*!
    \brief      get the FMC D-bus read protection protection
    \param[in]  none
    \param[out] none
    \retval     the FMC erase/program protection and D-bus read protection option bytes value
*/
uint16_t ob_drp0_get(void)
{
    /* return the FMC erase/program protection and D-bus read protection option bytes value */
    return (uint16_t)(((uint16_t)(FMC_OBCTL0 >> 16)) & (uint16_t)0x0FFF);
}

/*!
    \brief      get the FMC D-bus read protection protection
    \param[in]  none
    \param[out] none
    \retval     the FMC erase/program protection and D-bus read protection option bytes value
*/
uint16_t ob_drp1_get(void)
{
    /* return the FMC erase/program protection and D-bus read protection option bytes value */
    return (uint16_t)(((uint16_t)(FMC_OBCTL1 >> 16)) & (uint16_t)0x0FFF);
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
  
    if (((uint8_t)(FMC_OBCTL0 >> 8)) != (uint8_t)FMC_NSPC){
        spc_state = SET;
    }else{
        spc_state = RESET;
    }
    return spc_state;
}

/*!
    \brief      get the FMC option byte BOR threshold value
    \param[in]  none
    \param[out] none
    \retval     the FMC BOR threshold value:OB_BOR_TH_OFF,OB_BOR_TH_VALUE1,OB_BOR_TH_VALUE2,OB_BOR_TH_VALUE3
*/
uint8_t ob_user_bor_threshold_get(void)
{
    /* return the FMC BOR threshold value */
    return (uint8_t)((uint8_t)FMC_OBCTL0 & (uint8_t)0x0C);
}

/*!
    \brief      enable FMC interrupt
    \param[in]  the FMC interrupt source
      \arg        FMC_INTEN_END: enable FMC end of program interrupt
      \arg        FMC_INTEN_ERR: enable FMC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t fmc_int)
{
    FMC_CTL |= fmc_int;
}

/*!
    \brief      disable FMC interrupt
    \param[in]  the FMC interrupt source
      \arg        FMC_INTEN_END: disable FMC end of program interrupt
      \arg        FMC_INTEN_ERR: disable FMC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t fmc_int)
{
    FMC_CTL &= ~(uint32_t)fmc_int;
}

/*!
    \brief      get flag set or reset
    \param[in]  fmc_flag: check FMC flag
      \arg        FMC_FLAG_BUSY: FMC busy flag
      \arg        FMC_FLAG_RDDERR: FMC read D-bus protection error flag bit
      \arg        FMC_FLAG_PGSERR: FMC program sequence error flag bit
      \arg        FMC_FLAG_PGMERR: FMC program size not match error flag bit
      \arg        FMC_FLAG_WPERR: FMC Erase/Program protection error flag bit
      \arg        FMC_FLAG_OPERR: FMC operation error flag bit 
      \arg        FMC_FLAG_END: FMC end of operation flag bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t fmc_flag)
{
    if(FMC_STAT & fmc_flag){
        return  SET;
    }
    /* return the state of corresponding FMC flag */
    return RESET; 
}

/*!
    \brief      clear the FMC pending flag
    \param[in]  FMC_flag: clear FMC flag
      \arg        FMC_FLAG_RDDERR: FMC read D-bus protection error flag bit
      \arg        FMC_FLAG_PGSERR: FMC program sequence error flag bit
      \arg        FMC_FLAG_PGMERR: FMC program size not match error flag bit
      \arg        FMC_FLAG_WPERR: FMC erase/program protection error flag bit
      \arg        FMC_FLAG_OPERR: FMC operation error flag bit 
      \arg        FMC_FLAG_END: FMC end of operation flag bit
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t fmc_flag)
{
    /* clear the flags */
    FMC_STAT = fmc_flag;
}

/*!
    \brief      get the FMC state
    \param[in]  none
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;
  
    if((FMC_STAT & FMC_FLAG_BUSY) == FMC_FLAG_BUSY){
        fmc_state = FMC_BUSY;
    }else{
        if((FMC_STAT & FMC_FLAG_WPERR) != (uint32_t)0x00){ 
            fmc_state = FMC_WPERR;
        }else{
            if((FMC_STAT & FMC_FLAG_RDDERR) != (uint32_t)0x00){ 
                fmc_state = FMC_RDDERR;
            }else{
                if((FMC_STAT & (uint32_t)0xEF) != (uint32_t)0x00){
                    fmc_state = FMC_PGERR; 
                }else{
                    if((FMC_STAT & FMC_FLAG_OPERR) != (uint32_t)0x00){
                        fmc_state = FMC_OPERR;
                    }else{
                        fmc_state = FMC_READY;
                    }
                }
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC is ready or not
    \param[in]  count: FMC_TIMEOUT_COUNT
    \param[out] none
    \retval     fmc_state_enum
*/
fmc_state_enum fmc_ready_wait(uint32_t count)
{
    fmc_state_enum fmc_state = FMC_BUSY;
  
    /* wait for FMC ready */
    do{
        /* get FMC state */
        fmc_state = fmc_state_get();
        count--;
    }while((FMC_BUSY == fmc_state) && ((uint32_t)RESET != count));
  
    if(FMC_BUSY == fmc_state){
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
