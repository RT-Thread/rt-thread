/*!
    \file    gd32f5xx_fmc.c
    \brief   FMC driver

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


#include "gd32f5xx_fmc.h"

/* write protection/CBUS read protection sector mask */
#define WP0_DRP_LOW_12BITS_MASK           ((uint64_t)0x0000000000000FFFU)
#define WP0_DRP_HIGH_8BITS_MASK           ((uint64_t)0x00000000000FF000U)
#define WP1_DRP_LOW_12BITS_MASK           ((uint64_t)0x00000000FFF00000U)
#define WP1_DRP_HIGH_8BITS_MASK           ((uint64_t)0x000000FF00000000U)

/* write protection/CBUS read protection sector offset */
#define WP0_DRP_LOW_12BITS_OFFSET         ((uint32_t)0x00000000U)
#define WP0_DRP_HIGH_8BITS_OFFSET         ((uint32_t)0x0000000CU)
#define WP1_DRP_LOW_12BITS_OFFSET         ((uint32_t)0x00000014U)
#define WP1_DRP_HIGH_8BITS_OFFSET         ((uint32_t)0x00000020U)

/* FMC register bit offset */
#define OBCTL0_WP0_L_OFFSET               ((uint32_t)0x00000010U)           /*!< bit offset of WP0[11:0] in OBCTL1 */
#define OBCTL1_WP0_H_OFFSET               ((uint32_t)0x00000000U)           /*!< bit offset of WP0[19:12] in OBCTL1 */
#define OBCTL1_WP1_L_OFFSET               ((uint32_t)0x00000010U)           /*!< bit offset of WP1[11:0] in OBCTL1 */
#define OBCTL1_WP1_H_OFFSET               ((uint32_t)0x00000008U)           /*!< bit offset of WP1[19:12] in OBCTL1 */

/* EFUSE register bit offset */
#define EFUSE_ADDR_EFSIZE_OFFSET          ((uint32_t)(0x00000008U))         /*!< EFSIZE OFFSET in register EFUSE_ADDR */


/*!
    \brief      unlock the main FMC operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if((RESET != (FMC_CTL & FMC_CTL_LK))) {
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
    \brief      FMC erase page
    \param[in]  page_addr: the page address to be erased.
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_page_erase(uint32_t page_addr)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* unlock page erase operation */
        FMC_PEKEY = UNLOCK_PE_KEY;

        /* start page erase */
        FMC_PECFG = FMC_PECFG_PE_EN | page_addr;
        FMC_CTL |= FMC_CTL_SER;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        FMC_PECFG &= ~FMC_PECFG_PE_EN;
        FMC_CTL &= ~FMC_CTL_SER;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC erase sector
    \param[in]  fmc_sector: select the sector to erase
                only one parameter can be selected which is shown as below:
      \arg        CTL_SECTOR_NUMBER_x: sector x(x = 0,1,2...53)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_sector_erase(uint32_t fmc_sector)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        /* start sector erase */
        FMC_CTL &= ~FMC_CTL_SER;
        FMC_CTL &= ~(FMC_CTL_SN | FMC_CTL_SN_5);
        FMC_CTL |= FMC_CTL_SER | fmc_sector;
        FMC_CTL |= FMC_CTL_START;

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the SER bit */
        FMC_CTL &= ~FMC_CTL_SER;
        FMC_CTL &= ~(FMC_CTL_SN | FMC_CTL_SN_5);
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
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_mass_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
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
    \brief      FMC erase whole bank0
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_bank0_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
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
    \brief      FMC erase whole bank1(include bank1_ex)
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_bank1_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
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
    \brief      program a doubleword at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: doubleword to program(0x0000000000000000 - 0xFFFFFFFFFFFFFFFF)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_CTL |= FMC_CTL_DWPGE;

        /* set the PG bit to start program */
        FMC_CTL |= FMC_CTL_PG;

        REG32(address) = (uint32_t)(data & 0xFFFFFFFFU);
        REG32(address + 4U) = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);

        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

        /* reset the PG bit */
        FMC_CTL &= ~FMC_CTL_PG;
        /* reset the DWPGE bit */
        FMC_CTL &= ~FMC_CTL_DWPGE;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program(0x00000000 - 0xFFFFFFFF)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_CTL &= ~FMC_CTL_DWPGE;
        FMC_CTL &= ~FMC_CTL_PSZ;
        FMC_CTL |= CTL_PSZ_WORD;

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
    \param[in]  data: halfword to program(0x0000 - 0xFFFF)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_CTL &= ~FMC_CTL_DWPGE;
        FMC_CTL &= ~FMC_CTL_PSZ;
        FMC_CTL |= CTL_PSZ_HALF_WORD;

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
    \brief      program a byte at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: byte to program(0x00 - 0xFF)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_byte_program(uint32_t address, uint8_t data)
{
    fmc_state_enum fmc_state = FMC_READY;
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        FMC_CTL &= ~FMC_CTL_DWPGE;
        FMC_CTL &= ~FMC_CTL_PSZ;
        FMC_CTL |= CTL_PSZ_BYTE;

        /* set the PG bit to start program */
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
    \brief      enable no waiting time area load after system reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_nwa_enable(void)
{
    FMC_CTL |= FMC_CTL_NWLDE;
}

/*!
    \brief      disable no waiting time area load after system reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_nwa_disable(void)
{
    FMC_CTL &= ~FMC_CTL_NWLDE;
}

/*!
    \brief      set OTP1 data block not be read
    \param[in]  block: specify OTP1 data block x not be read
                one or more parameters can be selected which are shown as below:
        \arg    OTP1_DATA_BLOCK_x: data blcok x(x = 0,1,2...15)
        \arg    OTP1_DATA_BLOCK_ALL: all data blcok
    \param[out] none
    \retval     none
*/
void otp1_read_disable(uint32_t block)
{
    FMC_OTP1CFG &= ~block;
}

/*!
    \brief      enable read lock block protection for OTP2
    \param[in]  none
    \param[out] none
    \retval     none
*/
void otp2_rlock_enable(void)
{
    FMC_CTL |= FMC_CTL_RLBP;
}

/*!
    \brief      unlock the option byte operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_unlock(void)
{
    if(RESET != (FMC_OBCTL0 & FMC_OBCTL0_OB_LK)) {
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
    FMC_OBCTL0 |= FMC_OBCTL0_OB_LK;
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
    \brief      erase option byte
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_erase(void)
{
    uint32_t reg, reg1;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    reg = FMC_OBCTL0;
    reg1 = FMC_OBCTL1;

    if(FMC_READY == fmc_state) {
        /* reset the OB_FWDGT, OB_DEEPSLEEP and OB_STDBY, set according to ob_fwdgt, ob_deepsleep and ob_stdby */
        reg |= (FMC_OBCTL0_NWDG_HW | FMC_OBCTL0_NRST_DPSLP | FMC_OBCTL0_NRST_STDBY);
        /* reset the BOR level */
        reg |= FMC_OBCTL0_BOR_TH;
        /* reset option byte boot bank value */
        reg &= ~FMC_OBCTL0_BB;
        /* set option byte eccen value */
        reg |= FMC_OBCTL0_ECCEN;
        /* reset drp and wp value */
        reg |= FMC_OBCTL0_WP0;
        reg &= (~FMC_OBCTL0_DRP);
        /* set option byte nwa value */
        reg |= FMC_OBCTL0_NWA;
        FMC_OBCTL0 = reg;

        reg1 |= FMC_OBCTL1_WP0_H | FMC_OBCTL1_WP1_L | FMC_OBCTL1_WP1_H;
        FMC_OBCTL1 = reg1;
    }
}

/*!
    \brief      enable write protection
    \param[in]  ob_wp: specify sector to be write protected
                one or more parameters can be selected which are shown as below:
      \arg        OB_WP_x(x=0..38):sector x(x = 0,1,2...38)
      \arg        OB_WP_39_53: sector39~53
      \arg        OB_WP_ALL: all sector
    \param[out] none
    \retval     SUCCESS or ERROR
*/
ErrStatus ob_write_protection_enable(uint64_t ob_wp)
{
    uint32_t reg0 = FMC_OBCTL0;
    uint32_t reg1 = FMC_OBCTL1;
    uint32_t wp0_low;
    uint32_t wp0_high;
    uint32_t wp1_low;
    uint32_t wp1_high;
    fmc_state_enum fmc_state = FMC_READY;

    if(RESET != (FMC_OBCTL0 & FMC_OBCTL0_DRP)) {
        return ERROR;
    }

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        wp0_low = (uint32_t)(((ob_wp & WP0_DRP_LOW_12BITS_MASK) >> WP0_DRP_LOW_12BITS_OFFSET) << OBCTL0_WP0_L_OFFSET);
        wp0_high = (uint32_t)(((ob_wp & WP0_DRP_HIGH_8BITS_MASK) >> WP0_DRP_HIGH_8BITS_OFFSET) << OBCTL1_WP0_H_OFFSET);
        wp1_low = (uint32_t)(((ob_wp & WP1_DRP_LOW_12BITS_MASK) >> WP1_DRP_LOW_12BITS_OFFSET) << OBCTL1_WP1_L_OFFSET);
        wp1_high = (uint32_t)(((ob_wp & WP1_DRP_HIGH_8BITS_MASK) >> WP1_DRP_HIGH_8BITS_OFFSET) << OBCTL1_WP1_H_OFFSET);

        reg0 &= ~wp0_low;
        reg1 &= ~(wp0_high | wp1_low | wp1_high);
        FMC_OBCTL0 = reg0;
        FMC_OBCTL1 = reg1;

        return SUCCESS;
    } else {
        return ERROR;
    }
}

/*!
    \brief      disable write protection
    \param[in]  ob_wp: specify sector to be write protected
                one or more parameters can be selected which are shown as below:
      \arg        OB_WP_x(x=0..38): sector x(x = 0,1,2...38)
      \arg        OB_WP_39_53: sector39~53
      \arg        OB_WP_ALL: all sector
    \param[out] none
    \retval     SUCCESS or ERROR
*/
ErrStatus ob_write_protection_disable(uint64_t ob_wp)
{
    uint32_t reg0 = FMC_OBCTL0;
    uint32_t reg1 = FMC_OBCTL1;
    uint32_t wp0_low;
    uint32_t wp0_high;
    uint32_t wp1_low;
    uint32_t wp1_high;
    fmc_state_enum fmc_state = FMC_READY;

    if(RESET != (FMC_OBCTL0 & FMC_OBCTL0_DRP)) {
        return ERROR;
    }
    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        wp0_low = (uint32_t)(((ob_wp & WP0_DRP_LOW_12BITS_MASK) >> WP0_DRP_LOW_12BITS_OFFSET) << OBCTL0_WP0_L_OFFSET);
        wp0_high = (uint32_t)(((ob_wp & WP0_DRP_HIGH_8BITS_MASK) >> WP0_DRP_HIGH_8BITS_OFFSET) << OBCTL1_WP0_H_OFFSET);
        wp1_low = (uint32_t)(((ob_wp & WP1_DRP_LOW_12BITS_MASK) >> WP1_DRP_LOW_12BITS_OFFSET) << OBCTL1_WP1_L_OFFSET);
        wp1_high = (uint32_t)(((ob_wp & WP1_DRP_HIGH_8BITS_MASK) >> WP1_DRP_HIGH_8BITS_OFFSET) << OBCTL1_WP1_H_OFFSET);

        reg0 |= wp0_low;
        reg1 |= wp0_high | wp1_low | wp1_high;

        FMC_OBCTL0 = reg0;
        FMC_OBCTL1 = reg1;

        return SUCCESS;
    } else {
        return ERROR;
    }
}

/*!
    \brief      enable erase/program protection and CBUS read protection
    \param[in]  ob_drp: enable the WPx bits used as erase/program protection and CBUS read protection of each sector
                one or more parameters can be selected which are shown as below:
      \arg        OB_DRP_x(x=0..38): sector x(x = 0,1,2...38)
      \arg        OB_DRP_39_53: sector39~53
      \arg        OB_DRP_ALL: all sector
    \param[out] none
    \retval     none
*/
void ob_drp_enable(uint64_t ob_drp)
{
    uint32_t reg0 = FMC_OBCTL0;
    uint32_t reg1 = FMC_OBCTL1;
    fmc_state_enum fmc_state = FMC_READY;
    uint32_t drp_state = FMC_OBCTL0 & FMC_OBCTL0_DRP;
    uint32_t drp0_low;
    uint32_t drp0_high;
    uint32_t drp1_low;
    uint32_t drp1_high;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        if(RESET == drp_state) {
            reg0 &= ~FMC_OBCTL0_WP0;
            reg1 &= ~(FMC_OBCTL1_WP1_L | FMC_OBCTL1_WP1_H | FMC_OBCTL1_WP0_H);
        }

        drp0_low = (uint32_t)(((ob_drp & WP0_DRP_LOW_12BITS_MASK) >> WP0_DRP_LOW_12BITS_OFFSET) << OBCTL0_WP0_L_OFFSET);
        drp0_high = (uint32_t)(((ob_drp & WP0_DRP_HIGH_8BITS_MASK) >> WP0_DRP_HIGH_8BITS_OFFSET) << OBCTL1_WP0_H_OFFSET);
        drp1_low = (uint32_t)(((ob_drp & WP1_DRP_LOW_12BITS_MASK) >> WP1_DRP_LOW_12BITS_OFFSET) << OBCTL1_WP1_L_OFFSET);
        drp1_high = (uint32_t)(((ob_drp & WP1_DRP_HIGH_8BITS_MASK) >> WP1_DRP_HIGH_8BITS_OFFSET) << OBCTL1_WP1_H_OFFSET);

        reg0 |= drp0_low;
        reg0 |= FMC_OBCTL0_DRP;
        reg1 |= drp0_high | drp1_low | drp1_high;

        FMC_OBCTL0 = reg0;
        FMC_OBCTL1 = reg1;
    }
}

/*!
    \brief      disable all erase/program protection and CBUS read protection
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_drp_disable(void)
{
    uint32_t reg0 = FMC_OBCTL0;
    uint32_t reg1 = FMC_OBCTL1;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state) {
        if(((uint8_t)(reg0 >> 8U)) == (uint8_t)FMC_NSPC) {
            /* security protection should be set as low level protection before disable CBUS read protection */
            reg0 &= ~FMC_OBCTL0_SPC;
            reg0 |= ((uint32_t)FMC_LSPC << 8U);
            FMC_OBCTL0 = reg0;

            /* set the OB_START bit in OBCTL0 register */
            FMC_OBCTL0 |= FMC_OBCTL0_OB_START;
        }

        /* it is necessary to disable the security protection at the same time when CBUS read protection is disabled */
        reg0 &= ~FMC_OBCTL0_SPC;
        reg0 |= ((uint32_t)FMC_NSPC << 8U);
        reg0 |= FMC_OBCTL0_WP0;
        reg0 &= (~FMC_OBCTL0_DRP);
        FMC_OBCTL0 = reg0;

        reg1 |= FMC_OBCTL1_WP0_H | FMC_OBCTL1_WP1_L | FMC_OBCTL1_WP1_H;
        FMC_OBCTL1 = reg1;
    }
}

/*!
    \brief      configure security protection level
    \param[in]  ob_spc: specify security protection level
                only one parameter can be selected which is shown as below:
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

    if(FMC_READY == fmc_state) {
        uint32_t reg;

        reg = FMC_OBCTL0;
        /* reset the OBCTL0_SPC, set according to ob_spc */
        reg &= ~FMC_OBCTL0_SPC;
        reg |= ((uint32_t)ob_spc << 8U);
        FMC_OBCTL0 = reg;
    }
}

/*!
    \brief      program the FMC user option byte
    \param[in]  ob_fwdgt: option byte watchdog value
                only one parameter can be selected which is shown as below:
      \arg        OB_FWDGT_SW: software free watchdog
      \arg        OB_FWDGT_HW: hardware free watchdog
    \param[in]  ob_deepsleep: option byte deepsleep reset value
                only one parameter can be selected which is shown as below:
      \arg        OB_DEEPSLEEP_NRST: no reset when entering deepsleep mode
      \arg        OB_DEEPSLEEP_RST: generate a reset instead of entering deepsleep mode
    \param[in]  ob_stdby:option byte standby reset value
                only one parameter can be selected which is shown as below:
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

    if(FMC_READY == fmc_state) {
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
                only one parameter can be selected which is shown as below:
      \arg        OB_BOR_TH_VALUE3: BOR threshold value 3
      \arg        OB_BOR_TH_VALUE2: BOR threshold value 2
      \arg        OB_BOR_TH_VALUE1: BOR threshold value 1
      \arg        OB_BOR_TH_OFF: no BOR function
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
                only one parameter can be selected which is shown as below:
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
    \brief      configure FMC/SRAM ECC checking, only valid after power reset.
    \param[in]  ecc_config: specifies the option byte FMC/SRAM ECC checking
                only one parameter can be selected which is shown as below:
      \arg        OB_ECC_DISABLE: disable FMC/SRAM ECC checking
      \arg        OB_ECC_ENABLE: enable FMC/SRAM ECC checking
    \param[out] none
    \retval     none
*/
void ob_ecc_config(uint32_t ecc_config)
{
    uint32_t reg;

    reg = FMC_OBCTL0;

    /* set option byte boot bank value */
    reg &= ~FMC_OBCTL0_ECCEN;
    FMC_OBCTL0 = (reg | ecc_config);
}

/*!
    \brief      select no waiting time area, only valid after power reset, only for 4MB dual bank series.
    \param[in]  nwa_select: specifies the option byte no waiting time area
                only one parameter can be selected which is shown as below:
      \arg        OB_NWA_BANK1: bank1 is no waiting time area
      \arg        OB_NWA_BANK0: bank0 is no waiting time area
    \param[out] none
    \retval     none
*/
void ob_nwa_select(uint32_t nwa_select)
{
    uint32_t reg;

    reg = FMC_OBCTL0;

    /* set option byte boot bank value */
    reg &= ~FMC_OBCTL0_NWA;
    FMC_OBCTL0 = (reg | nwa_select);
}

/*!
    \brief      get the FMC user option byte
    \param[in]  none
    \param[out] none
    \retval     the FMC user option byte values: ob_fwdgt(Bit0), ob_deepsleep(Bit1), ob_stdby(Bit2)
*/
uint8_t ob_user_get(void)
{
    return (uint8_t)((uint8_t)(FMC_OBCTL0 >> 5U) & 0x07U);
}

/*!
    \brief      get the FMC option byte write protection of bank0
    \param[in]  none
    \param[out] none
    \retval     the FMC write protection option byte value
*/
uint32_t ob_write_protection0_get(void)
{
    uint32_t wp0_value;

    wp0_value = (uint32_t)(((uint32_t)(FMC_OBCTL0 & FMC_OBCTL0_WP0)) >> OBCTL0_WP0_L_OFFSET);
    wp0_value |= (uint32_t)((((uint32_t)(FMC_OBCTL1 & FMC_OBCTL1_WP0_H)) >> OBCTL1_WP0_H_OFFSET) << 12U);

    return wp0_value;
}

/*!
    \brief      get the FMC option byte write protection of bank1
    \param[in]  none
    \param[out] none
    \retval     the FMC write protection option byte value
*/
uint32_t ob_write_protection1_get(void)
{
    uint32_t wp1_value;

    wp1_value = (uint32_t)(((uint32_t)(FMC_OBCTL1 & FMC_OBCTL1_WP1_L)) >> OBCTL1_WP1_L_OFFSET);
    wp1_value |= (uint32_t)((((uint32_t)(FMC_OBCTL1 & FMC_OBCTL1_WP1_H)) >> OBCTL1_WP1_H_OFFSET) << 12U);

    return wp1_value;
}

/*!
    \brief      get the FMC erase/program protection and CBUS read protection option bytes value of bank0
    \param[in]  none
    \param[out] none
    \retval     the FMC erase/program protection and CBUS read protection option bytes value
*/
uint32_t ob_drp0_get(void)
{
    uint32_t drp0_value;

    /* return the FMC erase/program protection and CBUS read protection option bytes value */
    if(FMC_OBCTL0 & FMC_OBCTL0_DRP) {
        drp0_value = (uint32_t)(((uint32_t)(FMC_OBCTL0 & FMC_OBCTL0_WP0)) >> OBCTL0_WP0_L_OFFSET);
        drp0_value |= (uint32_t)((((uint32_t)(FMC_OBCTL1 & FMC_OBCTL1_WP0_H)) >> OBCTL1_WP0_H_OFFSET) << 12U);
    } else {
        drp0_value = 0U;
    }
    return drp0_value;
}

/*!
    \brief      get the FMC erase/program protection and CBUS read protection option bytes value of bank1
    \param[in]  none
    \param[out] none
    \retval     the FMC erase/program protection and CBUS read protection option bytes value
*/
uint32_t ob_drp1_get(void)
{
    uint32_t drp1_value;

    /* return the FMC erase/program protection and CBUS read protection option bytes value */
    if(FMC_OBCTL0 & FMC_OBCTL0_DRP) {
        drp1_value = (uint32_t)(((uint32_t)(FMC_OBCTL1 & FMC_OBCTL1_WP1_L)) >> OBCTL1_WP1_L_OFFSET);
        drp1_value |= (uint32_t)((((uint32_t)(FMC_OBCTL1 & FMC_OBCTL1_WP1_H)) >> OBCTL1_WP1_H_OFFSET) << 12U);
    } else {
        drp1_value = 0U;
    }
    return drp1_value;
}

/*!
    \brief      get option byte security protection code value
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_spc_get(void)
{
    FlagStatus spc_state = RESET;

    if(((uint8_t)(FMC_OBCTL0 >> 8U)) != FMC_NSPC) {
        spc_state = SET;
    } else {
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
uint32_t ob_user_bor_threshold_get(void)
{
    /* return the FMC BOR threshold value */
    return (FMC_OBCTL0 & FMC_OBCTL0_BOR_TH);
}

/*!
    \brief      get the boot mode
    \param[in]  none
    \param[out] none
    \retval     the FMC boot bank value:OB_BB_DISABLE,OB_BB_ENABLE
*/
uint32_t ob_boot_mode_get(void)
{
    /* return the boot mode */
    return (FMC_OBCTL0 & FMC_OBCTL0_BB);
}

/*!
    \brief      get FMC/SRAM ECC checking
    \param[in]  none
    \param[out] none
    \retval     the FMC ECCEN value:OB_ECC_DISABLE,OB_ECC_ENABLE
*/
uint32_t ob_ecc_get(void)
{
    /* return the FMC/SRAM ECC checking */
    return (FMC_OBCTL0 & FMC_OBCTL0_ECCEN);
}

/*!
    \brief      get no waiting time area
    \param[in]  none
    \param[out] none
    \retval     the no waiting time area:OB_NWA_BANK1,OB_NWA_BANK0
*/
uint32_t ob_nwa_get(void)
{
    /* return the no waiting time area */
    return (FMC_OBCTL0 & FMC_OBCTL0_NWA);
}

/*!
    \brief      get flag set or reset
    \param[in]  fmc_flag: check FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_END: FMC end of operation flag bit
      \arg        FMC_FLAG_OPERR: FMC operation error flag bit
      \arg        FMC_FLAG_LDECCDET: FMC multi bit ECC error when load code from flash flag bit
      \arg        FMC_FLAG_WPERR: FMC Erase/Program protection error flag bit
      \arg        FMC_FLAG_PGAERR: FMC program alignment error flag bit
      \arg        FMC_FLAG_PGMERR: FMC program size not match error flag bit
      \arg        FMC_FLAG_PGSERR: FMC program sequence error flag bit
      \arg        FMC_FLAG_RDCERR: FMC CBUS data read protection error flag bit
      \arg        FMC_FLAG_BUSY: FMC busy flag bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(uint32_t fmc_flag)
{
    if(FMC_STAT & fmc_flag) {
        return SET;
    }
    /* return the state of corresponding FMC flag */
    return RESET;
}

/*!
    \brief      clear the FMC pending flag
    \param[in]  FMC_flag: clear FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_END: FMC end of operation flag bit
      \arg        FMC_FLAG_OPERR: FMC operation error flag bit
      \arg        FMC_FLAG_LDECCDET: FMC multi bit ECC error when load code from flash flag bit
      \arg        FMC_FLAG_WPERR: FMC Erase/Program protection error flag bit
      \arg        FMC_FLAG_PGAERR: FMC program alignment error flag bit
      \arg        FMC_FLAG_PGMERR: FMC program size not match error flag bit
      \arg        FMC_FLAG_PGSERR: FMC program sequence error flag bit
      \arg        FMC_FLAG_RDCERR: FMC CBUS data read protection error flag bit
      \arg        FMC_FLAG_BUSY: FMC busy flag bit
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(uint32_t fmc_flag)
{
    /* clear the flags */
    FMC_STAT = fmc_flag;
}

/*!
    \brief      enable FMC interrupt
    \param[in]  fmc_int: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: enable FMC end of program interrupt
      \arg        FMC_INT_ERR: enable FMC error interrupt
      \arg        FMC_INT_LDECC: enable FMC load code ECC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(uint32_t fmc_int)
{
    FMC_CTL |= fmc_int;
}

/*!
    \brief      disable FMC interrupt
    \param[in]  fmc_int: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END: disable FMC end of program interrupt
      \arg        FMC_INT_ERR: disable FMC error interrupt
      \arg        FMC_INT_LDECC: enable FMC load code ECC error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(uint32_t fmc_int)
{
    FMC_CTL &= ~fmc_int;
}

/*!
    \brief      get FMC interrupt flag set or reset
    \param[in]  fmc_int_flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
      \arg        FMC_INT_FLAG_OPERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_LDECCDET: FMC two bits ECC error when load code from flash/OTP1/bootloader interrupt flag
      \arg        FMC_INT_FLAG_WPERR: FMC Erase/Program protection error interrupt flag
      \arg        FMC_INT_FLAG_PGAERR: FMC program alignment error interrupt flag
      \arg        FMC_INT_FLAG_PGMERR: FMC program size not match error interrupt flag
      \arg        FMC_INT_FLAG_PGSERR: FMC program sequence error interrupt flag
      \arg        FMC_INT_FLAG_RDCERR: FMC CBUS data read protection error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(uint32_t fmc_int_flag)
{
    if(FMC_FLAG_END == fmc_int_flag) {
        /* end of operation interrupt flag */
        if(FMC_CTL & FMC_CTL_ENDIE) {
            if(FMC_STAT & fmc_int_flag) {
                return SET;
            }
        }
    } else {
        /* error interrupt flags */
        if(FMC_CTL & FMC_CTL_ERRIE) {
            if(FMC_STAT & fmc_int_flag) {
                return SET;
            }
        }
    }
    return RESET;
}

/*!
    \brief      clear the FMC interrupt flag
    \param[in]  fmc_int_flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_END: FMC end of operation interrupt flag
      \arg        FMC_INT_FLAG_OPERR: FMC operation error interrupt flag
      \arg        FMC_INT_FLAG_LDECCDET: FMC two bits ECC error when load code from flash/OTP1/bootloader interrupt flag
      \arg        FMC_INT_FLAG_WPERR: FMC Erase/Program protection error interrupt flag
      \arg        FMC_INT_FLAG_PGAERR: FMC program alignment error interrupt flag
      \arg        FMC_INT_FLAG_PGMERR: FMC program size not match error interrupt flag
      \arg        FMC_INT_FLAG_PGSERR: FMC program sequence error interrupt flag
      \arg        FMC_INT_FLAG_RDCERR: FMC CBUS data read protection error interrupt flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(uint32_t fmc_int_flag)
{
    /* clear the interrupt flag */
    FMC_STAT = fmc_int_flag;
}

/*!
    \brief      get the FMC state
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
*/
fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;
    uint32_t temp_val = FMC_STAT;

    if(RESET != (temp_val & FMC_FLAG_BUSY)) {
        fmc_state = FMC_BUSY;
    } else if(RESET != (temp_val & FMC_FLAG_RDCERR)) {
        fmc_state = FMC_RDCERR;
    } else if(RESET != (temp_val & FMC_FLAG_PGSERR)) {
        fmc_state = FMC_PGSERR;
    } else if(RESET != (temp_val & FMC_FLAG_PGMERR)) {
        fmc_state = FMC_PGMERR;
    } else if(RESET != (temp_val & FMC_FLAG_PGAERR)) {
        fmc_state = FMC_PGAERR;
    } else if(RESET != (temp_val & FMC_FLAG_WPERR)) {
        fmc_state = FMC_WPERR;
    } else if(RESET != (temp_val & FMC_FLAG_OPERR)) {
        fmc_state = FMC_OPERR;
    } else if(RESET != (temp_val & FMC_FLAG_LDECCDET)) {
        fmc_state = FMC_LDECCDET;
    } else {
        fmc_state = FMC_READY;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC is ready or not
    \param[in]  timeout: timeout value
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_RDCERR: CBUS data read protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGMERR: program size not match error
      \arg        FMC_PGAERR: program alignment error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_OPERR: operation error
      \arg        FMC_LDECCDET: two bits ECC error when load code from flash/OTP1/bootloader
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0U != timeout));

    if(0U == timeout) {
        fmc_state = FMC_TOERR;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      unlock the EFUSE_CTL register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void efuse_ctrl_unlock(void)
{
    /* clear the LK bit */
    EFUSE_CTL &= ~EFUSE_CTL_LK;
}

/*!
    \brief      lock the EFUSE_CTL register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void efuse_ctrl_lock(void)
{
    /* set the LK bit */
    EFUSE_CTL |= EFUSE_CTL_LK;
}

/*!
    \brief      unlock the EFUSE_USER_DATA register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void efuse_user_data_unlock(void)
{
    /* clear the UDLK bit */
    EFUSE_CTL &= ~EFUSE_CTL_UDLK;
}

/*!
    \brief      lock the EFUSE_USER_DATA register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void efuse_user_data_lock(void)
{
    /* set the UDLK bit */
    EFUSE_CTL |= EFUSE_CTL_UDLK;
}

/*!
    \brief      read EFUSE value
    \param[in]  ef_addr: EFUSE address
      \arg        EFUSE_CTL_EFADDR: efuse controladdress
      \arg        USER_DATA_EFADDR: user data address
    \param[in]  size: byte count to read
    \param[out] buf: the buffer for storing read-out EFUSE data
    \retval     state of EFUSE:
      \arg        EFUSE_READY: EFUSE operation has been completed
      \arg        EFUSE_BUSY: EFUSE operation is in progress
      \arg        EFUSE_OBER: overstep boundary error
      \arg        EFUSE_TOERR: EFUSE timeout error
*/
efuse_state_enum efuse_read(uint32_t ef_addr, uint32_t size, uint32_t buf[])
{
    uint32_t reg_addr = 0U;
    efuse_state_enum efuse_state = EFUSE_READY;

    if(1U != size) {
        return EFUSE_OBER;
    }

    if(EFUSE_CTL_EFADDR == ef_addr) {
        /* read efuse control*/
        reg_addr = (uint32_t)(FMC + EFUSE_CTL_OFFSET);
    } else if(USER_DATA_EFADDR == ef_addr) {
        /* read user data */
        reg_addr = (uint32_t)(FMC + EFUSE_USER_DATA_OFFSET);
    } else {
        return EFUSE_OBER;
    }

    /* clear the RDIF bit if it is SET */
    efuse_flag_clear(EFUSE_RDIC);

    /* make sure no overstep boundary errors */
    if(RESET != efuse_flag_get(EFUSE_OBERIF)) {
        return EFUSE_OBER;
    }

    /* EFUSE read operation */
    EFUSE_CS &= (~EFUSE_CS_EFRW);

    /* write the desired efuse address and size to the EFUSE_ADDR register */
    EFUSE_ADDR = (uint32_t)((1U << EFUSE_ADDR_EFSIZE_OFFSET) | ef_addr);

    /* start read EFUSE operation */
    EFUSE_CS |= EFUSE_CS_EFSTR;

    /* wait for the operation to complete */
    efuse_state = efuse_ready_wait(EFUSE_RDIF, EFUSE_TIMEOUT_COUNT);
    if(EFUSE_READY == efuse_state) {
        /* read EFUSE data to buffer */
        buf[0] = REG32(reg_addr);
    }

    return efuse_state;
}

/*!
    \brief      write EFUSE
    \param[in]  ef_addr: EFUSE address
      \arg        EFUSE_CTL_EFADDR: efuse controladdress
      \arg        USER_DATA_EFADDR: user data address
    \param[in]  size: byte count to write, (1~1)
    \param[in]  ef_data: data to write EFUSE
    \param[out] none
    \retval     state of EFUSE:
      \arg        EFUSE_READY: EFUSE operation has been completed
      \arg        EFUSE_BUSY: EFUSE operation is in progress
      \arg        EFUSE_OBER: overstep boundary error
      \arg        EFUSE_TOERR: EFUSE timeout error
*/
efuse_state_enum efuse_write(uint32_t ef_addr, uint32_t size, uint8_t ef_data)
{
    uint32_t reg_addr = 0U;
    efuse_state_enum efuse_state;

    if(1U != size) {
        return EFUSE_OBER;
    }

    if(EFUSE_CTL_EFADDR == ef_addr) {
        /* program efuse control*/
        reg_addr = (uint32_t)(FMC + EFUSE_CTL_OFFSET);
    } else if(USER_DATA_EFADDR == ef_addr) {
        /* program user data */
        reg_addr = (uint32_t)(FMC + EFUSE_USER_DATA_OFFSET);
    } else {
        return EFUSE_OBER;
    }

    /* clear the PGIF bit if it is SET */
    efuse_flag_clear(EFUSE_PGIC);

    /* make sure no overstep boundary errors */
    if(RESET != efuse_flag_get(EFUSE_OBERIF)) {
        return EFUSE_OBER;
    }

    /* EFUSE write operation */
    EFUSE_CS |= EFUSE_CS_EFRW;

    /* write the desired efuse address and size to the EFUSE_ADDR register */
    EFUSE_ADDR = (uint32_t)((size << EFUSE_ADDR_EFSIZE_OFFSET) | ef_addr);

    REG32(reg_addr) = (uint32_t)ef_data;

    /* start array write EFUSE operation */
    EFUSE_CS |= EFUSE_CS_EFSTR;

    /* wait for the operation to complete */
    efuse_state = efuse_ready_wait(EFUSE_PGIF, EFUSE_TIMEOUT_COUNT);

    return efuse_state;
}

/*!
    \brief      write control data parameter
    \param[in]  ef_data: EFUSE data to write
    \param[out] none
    \retval     state of EFUSE:
      \arg        EFUSE_READY: EFUSE operation has been completed
      \arg        EFUSE_BUSY: EFUSE operation is in progress
      \arg        EFUSE_OBER: overstep boundary error
      \arg        EFUSE_TOERR: EFUSE timeout error
*/
efuse_state_enum efuse_control_write(uint8_t ef_data)
{
    return efuse_write(EFUSE_CTL_EFADDR, 1UL, ef_data);
}

/*!
    \brief      write user data parameter
    \param[in]  ef_data: EFUSE data to write
    \param[out] none
    \retval     state of EFUSE:
      \arg        EFUSE_READY: EFUSE operation has been completed
      \arg        EFUSE_BUSY: EFUSE operation is in progress
      \arg        EFUSE_OBER: overstep boundary error
      \arg        EFUSE_TOERR: EFUSE timeout error
*/
efuse_state_enum efuse_user_data_write(uint8_t ef_data)
{
    return efuse_write(USER_DATA_EFADDR, 1UL, ef_data);
}

/*!
    \brief      get EFUSE flag is set or not
    \param[in]  efuse_flag: specifies to get a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_PGIF: programming operation completion flag
      \arg        EFUSE_RDIF: read operation completion flag
      \arg        EFUSE_OBERIF: overstep boundary error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus efuse_flag_get(uint32_t efuse_flag)
{
    if(EFUSE_CS & efuse_flag) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear EFUSE pending flag
    \param[in]  flag: specifies to clear a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_PGIC: clear programming operation completion flag
      \arg        EFUSE_RDIC: clear read operation completion flag
      \arg        EFUSE_OBERIC: clear overstep boundary error flag
    \param[out] none
    \retval     none
*/
void efuse_flag_clear(uint32_t efuse_cflag)
{
    EFUSE_CS |= efuse_cflag;
}

/*!
    \brief      enable EFUSE interrupt
    \param[in]  source: specifies an interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        EFUSE_INT_PG: programming operation completion interrupt
      \arg        EFUSE_INT_RD: read operation completion interrupt
      \arg        EFUSE_INT_OBER: overstep boundary error interrupt
    \param[out] none
    \retval     none
*/
void efuse_interrupt_enable(uint32_t source)
{
    EFUSE_CS = source;
}

/*!
    \brief      disable EFUSE interrupt
    \param[in]  source: specifies an interrupt to disable
                one or more parameters can be selected which are shown as below:
      \arg        EFUSE_INT_PG: programming operation completion interrupt
      \arg        EFUSE_INT_RD: read operation completion interrupt
      \arg        EFUSE_INT_OBER: overstep boundary error interrupt
    \param[out] none
    \retval     none
*/
void efuse_interrupt_disable(uint32_t source)
{
    EFUSE_CS &= ~source;
}

/*!
    \brief      get EFUSE interrupt flag is set or not
    \param[in]  efuse_flag: specifies to get a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_INT_PGIF: programming operation completion interrupt flag
      \arg        EFUSE_INT_RDIF: read operation completion interrupt flag
      \arg        EFUSE_INT_OBERIF: overstep boundary error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus efuse_interrupt_flag_get(uint32_t int_flag)
{
    if(EFUSE_CS & int_flag) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear EFUSE pending interrupt flag
    \param[in]  efuse_flag: specifies to clear a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_INT_PGIC: clear programming operation completion interrupt flag
      \arg        EFUSE_INT_RDIC: clear operation completion interrupt flag
      \arg        EFUSE_INT_OBERIC: clear overstep boundary error interrupt flag
    \param[out] none
    \retval     none
*/
void efuse_interrupt_flag_clear(uint32_t int_cflag)
{
    EFUSE_CS |= int_cflag;
}

/*!
    \brief      check whether EFUSE is ready or not
    \param[in]  efuse_flag: specifies to get a flag
                only one parameter can be selected which is shown as below:
      \arg        EFUSE_PGIF: programming operation completion flag
      \arg        EFUSE_RDIF: read operation completion flag
      \arg        EFUSE_OBERIF: overstep boundary error flag
    \param[in]  timeout: timeout value
    \param[out] none
    \retval     state of EFUSE
      \arg        EFUSE_READY: EFUSE operation has been completed
      \arg        EFUSE_BUSY: EFUSE operation is in progress
      \arg        EFUSE_OBER: overstep boundary error
      \arg        EFUSE_TOERR: EFUSE timeout error
*/
efuse_state_enum efuse_ready_wait(uint32_t efuse_flag, uint32_t timeout)
{
    efuse_state_enum efuse_state = EFUSE_BUSY;

    /* wait for EFUSE ready */
    do {
        /* get EFUSE flag set or not */
        if(EFUSE_CS & (uint32_t)efuse_flag) {
            efuse_state = EFUSE_READY;
        } else if(EFUSE_CS & EFUSE_CS_OVBERIF) {
            efuse_state = EFUSE_OBER;
        } else {

        }
        timeout--;
    } while((EFUSE_BUSY == efuse_state) && (0U != timeout));

    if(EFUSE_BUSY == efuse_state) {
        efuse_state = EFUSE_TOERR;
    }

    /* return the EFUSE state */
    return efuse_state;
}
