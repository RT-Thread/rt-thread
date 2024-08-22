/*!
    \file    gd32h7xx_fmc.c
    \brief   FMC driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
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

#include "gd32h7xx_fmc.h"

#define FLASH_DENSITY_ADDRESS               ((uint32_t)0x1FF0F7E0U)       /*!< memory density information address */
#define FLASH_DENSITY_OFFSET                ((uint32_t)0x00000010U)       /*!< bit offset of FLASH_DENSITY in memory density information */

/* FMC register bit offset */
#define BTADDR_BOOT_ADDR0_OFFSET            ((uint32_t)0x00000000U)       /*!< bit offset of BOOT_ADDR0 in FMC_BTADDR_EFT/FMC_BTADDR_MDF register*/
#define BTADDR_BOOT_ADDR1_OFFSET            ((uint32_t)0x00000010U)       /*!< bit offset of BOOT_ADDR1 in FMC_BTADDR_EFT/FMC_BTADDR_MDF register */
#define SCRADDR_SCR_AREA_START_OFFSET       ((uint32_t)0x00000000U)       /*!< bit offset of SCR_AREA_START in FMC_SCRADDR_EFT/FMC_SCRADDR_MDF register */
#define SCRADDR_SCR_AREA_END_OFFSET         ((uint32_t)0x00000010U)       /*!< bit offset of SCR_AREA_END in FMC_SCRADDR_EFT/FMC_SCRADDR_MDF register */
#define DCRPADDR_DCRP_AREA_START_OFFSET     ((uint32_t)0x00000000U)       /*!< bit offset of DCRP_AREA_START in FMC_DCRPADDR_EFT/FMC_DCRPADDR_MDF register */
#define DCRPADDR_DCRP_AREA_END_OFFSET       ((uint32_t)0x00000010U)       /*!< bit offset of DCRP_AREA_END in FMC_DCRPADDR_EFT/FMC_DCRPADDR_MDF register */
#define OBSTAT0_SPC_OFFSET                  ((uint32_t)0x00000008U)       /*!< bit offset of SPC in FMC_OBSTAT0_EFT/FMC_OBSTAT0_MDF register */
#define OBSTAT1_DATA_OFFSET                 ((uint32_t)0x00000010U)       /*!< bit offset of DATA in FMC_OBSTAT1_EFT/FMC_OBSTAT1_MDF register */
#define NODEC_NODEC_AREA_START_OFFSET       ((uint32_t)0x00000000U)       /*!< bit offset of SCR_AREA_START in FMC_SCRADDR_EFT/FMC_SCRADDR_MDF register */
#define NODEC_NODEC_AREA_END_OFFSET         ((uint32_t)0x00000010U)       /*!< bit offset of SCR_AREA_END in FMC_SCRADDR_EFT/FMC_SCRADDR_MDF register */

/* option byte factory value */
#define OB_OBSTAT0_FACTORY_VALUE            ((uint32_t)0x01C6AAD0U)       /*!< the factory value of option byte in FMC_OBSTAT0_EFT/FMC_OBSTAT0_MDF */
#define OB_OBSTAT1_FACTORY_VALUE            ((uint32_t)0x00000087U)       /*!< the factory value of option byte in FMC_OBSTAT1_EFT/FMC_OBSTAT1_MDF */
#define OB_BTADDR_FACTORY_VALUE             ((uint32_t)0x1FF00800U)       /*!< the factory value of option byte in FMC_BTADDR_EFT/FMC_BTADDR_MDF */
#define OB_DCRPADDR_FACTORY_VALUE           ((uint32_t)0x000000FFU)       /*!< the factory value of option byte in FMC_DCRPADDR_EFT/FMC_DCRPADDR_MDF */
#define OB_SCRADDR_FACTORY_VALUE            ((uint32_t)0x000000FFU)       /*!< the factory value of option byte in FMC_SCRADDR_EFT/FMC_SCRADDR_MDF */
#define OB_WP_FACTORY_VALUE                 ((uint32_t)0x3FFFFFFFU)       /*!< the factory value of option byte in FMC_WP_EFT/FMC_WP_MDF */

/* invalid DCRP area value */
#define INVALID_DCRP_START_ADDR              ((uint32_t)0x000000FFU)       /*!< the start address to make DCRP area invalid */
#define INVALID_DCRP_END_ADDR                ((uint32_t)0x00000000U)       /*!< the end address to make DCRP area invalid */

/* invalid SCR area value */
#define INVALID_SCR_START_ADDR               ((uint32_t)0x000000FFU)       /*!< the start address to make SCR area invalid */
#define INVALID_SCR_END_ADDR                 ((uint32_t)0x00000000U)       /*!< the end address to make SCR area invalid */

/* get FMC state */
static fmc_state_enum fmc_state_get(void);
/* check whether FMC is ready or not */
static fmc_state_enum fmc_ready_wait(uint32_t timeout);

/*!
    \brief      unlock FMC_CTL register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if((RESET != (FMC_CTL & FMC_CTL_LK)))
    {
        /* write the FMC key */
        FMC_KEY = UNLOCK_KEY0;
        FMC_KEY = UNLOCK_KEY1;
    }
}

/*!
    \brief      lock FMC_CTL register
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
    \brief      FMC erase sector
    \param[in]  address: address to erase
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_sector_erase(uint32_t address)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        FMC_CTL |= FMC_CTL_SER;
        /* write the sector address */
        FMC_ADDR = address;
        /* start sector erase */
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the SER bit */
        FMC_CTL &= (~FMC_CTL_SER);
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC typical mass erase
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_typical_mass_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* enable mass erase operation */
        FMC_CTL |= FMC_CTL_MER;
        /* start whole chip erase */
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
    }

    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      FMC protection-removed mass erase
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_protection_removed_mass_erase(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* remove DCRP area */
        ob_dcrp_area_config(OB_DCRP_AREA_ERASE_ENABLE, INVALID_DCRP_START_ADDR, INVALID_DCRP_END_ADDR);
        /* remove secure-access area */
        ob_secure_area_config(OB_SCR_AREA_ERASE_ENABLE, INVALID_SCR_START_ADDR, INVALID_SCR_END_ADDR);
        /* disable all sectors' erase/program protection */
        ob_write_protection_disable(OB_WP_ALL);
        /* enable mass erase operation */
        FMC_CTL |= FMC_CTL_MER;
        /* start chip erase */
        FMC_CTL |= FMC_CTL_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the MER bit */
        FMC_CTL &= ~FMC_CTL_MER;
    }

    /* return the fmc state */
    return fmc_state;
}

/*!
    \brief      FMC program a word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: word to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* set the PG bit to start program */
        FMC_CTL |= FMC_CTL_PG;
        __ISB();
        __DSB();
        REG32(address) = data;
        __ISB();
        __DSB();
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the PG bit */
        FMC_CTL &= ~FMC_CTL_PG;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      FMC program a double-word at the corresponding address
    \param[in]  address: address to program
    \param[in]  data: double word to program
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data)
{
    uint32_t data0, data1;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    data0 = (uint32_t)(data & 0xFFFFFFFFU);
    data1 = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);
    if(FMC_READY == fmc_state)
    {
        /* set the PG bit to start program */
        FMC_CTL |= FMC_CTL_PG;
        __ISB();
        __DSB();
        REG32(address) = data0;
        REG32(address + 4U) = data1;
        __ISB();
        __DSB();
        /* wait for the FMC ready */
        fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
        /* reset the PG bit */
        FMC_CTL &= ~FMC_CTL_PG;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      enable check programming area
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_check_programming_area_enable(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    fmc_unlock();
    FMC_CTL |= FMC_CTL_PGCHEN;
    fmc_lock();
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      disable check programming area
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_check_programming_area_disable(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);
    fmc_unlock();
    FMC_CTL &= ~FMC_CTL_PGCHEN;
    fmc_lock();
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
    if(RESET != (FMC_OBCTL & FMC_OBCTL_OBLK))
    {
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
    /* set the OB_LK bit */
    FMC_OBCTL |= FMC_OBCTL_OBLK;
}

/*!
    \brief      send option bytes modification start command
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_start(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    /* set the OB_START bit in OBCTL register */
    FMC_OBCTL |= FMC_OBCTL_OBSTART;
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    return fmc_state;
}

/*!
    \brief      modify option byte to factory value
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_factory_value_config(void)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        /* get the option byte security protection value */
        obstat0_reg = (FMC_OBSTAT0_EFT & FMC_OBSTAT0_EFT_SPC);
        /* write factory value to FMC_OBSTAT0_MDF */
        FMC_OBSTAT0_MDF = obstat0_reg | OB_OBSTAT0_FACTORY_VALUE;
        /* write factory value to FMC_OBSTAT1_MDF */
        FMC_OBSTAT1_MDF = OB_OBSTAT1_FACTORY_VALUE;
        /* write factory value to FMC_BTADDR_MDF */
        FMC_BTADDR_MDF = OB_BTADDR_FACTORY_VALUE;
        /* write factory value to FMC_DCRPADDR_MDF */
        FMC_DCRPADDR_MDF = OB_DCRPADDR_FACTORY_VALUE;
        /* write factory value to FMC_SCRADDR_MDF */
        FMC_SCRADDR_MDF = OB_SCRADDR_FACTORY_VALUE;
        /* write factory value to FMC_WP_MDF */
        FMC_WP_MDF = OB_WP_FACTORY_VALUE;
    }

    fmc_state = ob_start();

    return fmc_state;
}

/*!
    \brief      enable secure access mode
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_secure_access_mode_enable(void)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* enable secure access mode */
        obstat0_reg |= FMC_OBSTAT0_MDF_SCR;
        FMC_OBSTAT0_MDF = obstat0_reg;
    }

    return fmc_state;
}

/*!
    \brief      disable secure access mode
    \param[in]  none
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_secure_access_mode_disable(void)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* disable secure access mode */
        obstat0_reg &= ~FMC_OBSTAT0_MDF_SCR;
        FMC_OBSTAT0_MDF = obstat0_reg;
    }

    return fmc_state;
}

/*!
    \brief      configure the option byte security protection level
    \param[in]  ob_spc: specify security protection level
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no protection
      \arg        FMC_LSPC: protection level low
      \arg        FMC_HSPC: protection level high
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_security_protection_config(uint8_t ob_spc)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* reset the OBSTAT0_SPC, set according to ob_spc */
        obstat0_reg &= ~FMC_OBSTAT0_MDF_SPC;
        obstat0_reg |= ((uint32_t)ob_spc << OBSTAT0_SPC_OFFSET);
        FMC_OBSTAT0_MDF = obstat0_reg;
    }

    return fmc_state;
}

/*!
    \brief      configure the option byte BOR threshold value
    \param[in]  ob_bor_th: option byte BOR threshold value
                only one parameter can be selected which is shown as below:
      \arg        OB_BOR_TH_VALUE3: BOR threshold value 3
      \arg        OB_BOR_TH_VALUE2: BOR threshold value 2
      \arg        OB_BOR_TH_VALUE1: BOR threshold value 1
      \arg        OB_BOR_TH_OFF: no BOR function
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_bor_threshold_config(uint32_t ob_bor_th)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* set BOR threshold level */
        obstat0_reg &= ~FMC_OBSTAT0_MDF_BOR_TH;
        FMC_OBSTAT0_MDF = (uint32_t)(obstat0_reg | ob_bor_th);
    }

    return fmc_state;
}

/*!
    \brief      configure low power related option byte
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
    \param[in]  ob_fwdg_suspend_deepsleep: option byte FWDG suspend status in deep-sleep mode
                only one parameter can be selected which is shown as below:
      \arg        OB_DPSLP_FWDGT_SUSPEND: free watchdog is suspended in deep-sleep mode
      \arg        OB_DPSLP_FWDGT_RUN: free watchdog is running in deep-sleep mode
    \param[in]  ob_fwdg_suspend_standby: option byte FWDG suspend status in standby mode
                only one parameter can be selected which is shown as below:
      \arg        OB_STDBY_FWDGT_SUSPEND: free watchdog is suspended in standby mode
      \arg        OB_STDBY_FWDGT_RUN: free watchdog is running in standby mode
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_low_power_config(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby, uint32_t ob_fwdg_suspend_deepsleep,
                                   uint32_t ob_fwdg_suspend_standby)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* set according to ob_fwdgt, ob_deepsleep, ob_stdby, ob_fwdg_suspend_deepsleep, ob_fwdg_suspend_standby */
        obstat0_reg &= ~(FMC_OBSTAT0_MDF_NWDG_HW | FMC_OBSTAT0_MDF_NRST_DPSLP | FMC_OBSTAT0_MDF_NRST_STDBY
                         | FMC_OBSTAT0_MDF_FWDGSPD_DPSLP | FMC_OBSTAT0_MDF_FWDGSPD_STDBY);
        FMC_OBSTAT0_MDF = (uint32_t)(obstat0_reg | ob_fwdgt | ob_deepsleep | ob_stdby | ob_fwdg_suspend_deepsleep | ob_fwdg_suspend_standby);
    }

    return fmc_state;
}

/*!
    \brief      configure TCM ECC option byte
    \param[in]  ob_itcmecc: ITCM ECC function enable bit
                only one parameter can be selected which is shown as below:
      \arg        OB_ITCMECCEN_DISABLE: disabled ITCM ECC function
      \arg        OB_ITCMECCEN_ENABLE: enabled ITCM ECC function
    \param[in]  ob_dtcm0ecc: DTCM0 ECC function enable bit
                only one parameter can be selected which is shown as below:
      \arg        OB_DTCM0ECCEN_DISABLE: disabled DTCM0 ECC function
      \arg        OB_DTCME0CCEN_ENABLE: enabled DTCM0 ECC function
    \param[in]  ob_dtcm1ecc: DTCM1 ECC function enable bit
                only one parameter can be selected which is shown as below:
      \arg        OB_DTCM1ECCEN_DISABLE: disabled DTCM1 ECC function
      \arg        OB_DTCM1ECCEN_ENABLE: enabled DTCM1 ECC function
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_tcm_ecc_config(uint32_t ob_itcmecc, uint32_t ob_dtcm0ecc, uint32_t ob_dtcm1ecc)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* set according to ob_itcmecc, ob_dtcm0ecc, ob_stdby, ob_dtcm1ecc */
        obstat0_reg &= ~(FMC_OBSTAT0_MDF_ITCMECCEN | FMC_OBSTAT0_MDF_DTCM0ECCEN | FMC_OBSTAT0_MDF_DTCM1ECCEN);
        FMC_OBSTAT0_MDF = (uint32_t)(obstat0_reg | ob_itcmecc | ob_dtcm0ecc | ob_dtcm1ecc);
    }

    return fmc_state;
}

/*!
    \brief      configure I/O speed optimization option byte
    \param[in]  ob_iospeed_op: configure I/O speed optimization, high-speed at low-voltage enable bit
                only one parameter can be selected which is shown as below:
      \arg        OB_IOSPDOPEN_DISABLE: disabled I/O speed optimization
      \arg        OB_IOSPDOPEN_ENABLE: enabled I/O speed optimization
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_iospeed_optimize_config(uint32_t ob_iospeed_op)
{
    uint32_t obstat0_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat0_reg = FMC_OBSTAT0_EFT;
        /* set according to ob_iospeed_op */
        obstat0_reg &= ~(FMC_OBSTAT0_MDF_IOSPDOPEN);
        FMC_OBSTAT0_MDF = (uint32_t)(obstat0_reg | ob_iospeed_op);
    }

    return fmc_state;
}


/*!
    \brief      configure option byte TCM shared RAM size
                ITCM RAM + DTCM RAM size should not exceed 512KB
    \param[in]  itcm_shared_ram_size: ITCM shared RAM size
                only one parameter can be selected which is shown as below:
      \arg        OB_ITCM_SHARED_RAM_0KB: ITCM shared RAM size is 0KB
      \arg        OB_ITCM_SHARED_RAM_64KB: ITCM shared RAM size is 64KB
      \arg        OB_ITCM_SHARED_RAM_128KB: ITCM shared RAM size is 128KB
      \arg        OB_ITCM_SHARED_RAM_256KB: ITCM shared RAM size is 256KB
      \arg        OB_ITCM_SHARED_RAM_512KB: ITCM shared RAM size is 512KB
    \param[in]  dtcm_shared_ram_size: DTCM shared RAM size
                only one parameter can be selected which is shown as below:
      \arg        OB_DTCM_SHARED_RAM_0KB: DTCM shared RAM size is 0KB
      \arg        OB_DTCM_SHARED_RAM_64KB: DTCM shared RAM size is 64KB
      \arg        OB_DTCM_SHARED_RAM_128KB: DTCM shared RAM size is 128KB
      \arg        OB_DTCM_SHARED_RAM_256KB: DTCM shared RAM size is 256KB
      \arg        OB_DTCM_SHARED_RAM_512KB: DTCM shared RAM size is 512KB
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_tcm_shared_ram_config(uint32_t itcm_shared_ram_size, uint32_t dtcm_shared_ram_size)
{
    uint32_t obstat1_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat1_reg = FMC_OBSTAT1_EFT;

        /* set ITCM shared ram size according to itcm_shared_ram_size */
        obstat1_reg &= ~FMC_OBSTAT1_MDF_ITCM_SZ_SHRRAM;
        obstat1_reg |= itcm_shared_ram_size;

        /* set DTCM shared ram size according to dtcm_shared_ram_size */
        obstat1_reg &= ~FMC_OBSTAT1_MDF_DTCM_SZ_SHRRAM;
        obstat1_reg |= dtcm_shared_ram_size;

        FMC_OBSTAT1_MDF = obstat1_reg;
    }

    return fmc_state;
}

/*!
    \brief      modify option byte DATA
    \param[in]  ob_data: option bytes user data
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_data_program(uint16_t ob_data)
{
    uint32_t obstat1_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        obstat1_reg = FMC_OBSTAT1_EFT;

        /* modify user data according to ob_data */
        obstat1_reg &= ~FMC_OBSTAT1_MDF_DATA;
        obstat1_reg |= ((uint32_t)ob_data << OBSTAT1_DATA_OFFSET);
        FMC_OBSTAT1_MDF = obstat1_reg;
    }

    return fmc_state;
}

/*!
    \brief      configure boot address
    \param[in]  boot_pin: boot pin configuration
                only one parameter can be selected which is shown as below:
      \arg        BOOT_PIN_0: boot pin value is 0
      \arg        BOOT_PIN_1: boot pin value is 1
    \param[in]  boot_address: specify the MSB of boot address
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_boot_address_config(uint8_t boot_pin, uint16_t boot_address)
{
    uint32_t btaddr_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        btaddr_reg = FMC_BTADDR_EFT;

        if(BOOT_PIN_0 == boot_pin)
        {
            /* set to boot address 0 */
            btaddr_reg &= ~FMC_BTADDR_MDF_BOOT_ADDR0;
            btaddr_reg |= (uint32_t)((uint32_t)boot_address << BTADDR_BOOT_ADDR0_OFFSET);
        } else {
            /* set to boot address 1 */
            btaddr_reg &= ~FMC_BTADDR_MDF_BOOT_ADDR1;
            btaddr_reg |= (uint32_t)((uint32_t)boot_address << BTADDR_BOOT_ADDR1_OFFSET);
        }
        FMC_BTADDR_MDF = btaddr_reg;
    }

    return fmc_state;
}

/*!
    \brief      configure DCRP area
    \param[in]  dcrp_eren: DCRP area erase enable bit
      \arg        OB_DCRP_AREA_ERASE_DISABLE: DCRP area erase disable
      \arg        OB_DCRP_AREA_ERASE_ENABLE: DCRP area erase enable
    \param[in]  dcrp_start: DCRP area start address, contain the first 4K-byte block of the DCRP area.(0 - 0x3BF)
    \param[in]  dcrp_end: DCRP area end address, contain the last 4K-byte block of the DCRP area.(0 - 0x3BF)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_dcrp_area_config(uint32_t dcrp_eren, uint32_t dcrp_start, uint32_t dcrp_end)
{
    uint32_t dcrpaddr_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        dcrpaddr_reg = 0U;
        dcrpaddr_reg |= dcrp_eren;
        dcrpaddr_reg |= dcrp_start;
        dcrpaddr_reg |= (uint32_t)(dcrp_end << DCRPADDR_DCRP_AREA_END_OFFSET);
        FMC_DCRPADDR_MDF = dcrpaddr_reg;
    }

    return fmc_state;
}

/*!
    \brief      configure secure-access area
    \param[in]  scr_eren: secure-access area erase enable bit
      \arg        OB_SCR_AREA_ERASE_DISABLE: secure-access area erase disable
      \arg        OB_SCR_AREA_ERASE_ENABLE: secure-access area erase enable
    \param[in]  scr_start: secure-access area start address, contain the first 4K-byte block of the secure-access area.(0 - 0x3BF)
    \param[in]  scr_end: secure-access area end address, contain the last 4K-byte block of the secure-access area.(0 - 0x3BF)
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_secure_area_config(uint32_t scr_eren, uint32_t scr_start, uint32_t scr_end)
{
    uint32_t scraddr_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        scraddr_reg = 0U;
        scraddr_reg |= scr_eren;
        scraddr_reg |= scr_start;
        scraddr_reg |= (uint32_t)(scr_end << SCRADDR_SCR_AREA_END_OFFSET);
        FMC_SCRADDR_MDF = scraddr_reg;
    }

    return fmc_state;
}

/*!
    \brief      enable erase/program protection
    \param[in]  ob_wp: specify sector to be erase/program protected
                one or more parameters can be selected which are shown as below:
      \arg        OB_WP_0 erase/program protect sector 0 ~ sector 15
      \arg        OB_WP_1: erase/program protect sector 16 ~ sector 31
      \arg        OB_WP_2: erase/program protect sector 32 ~ sector 47
      \arg        OB_WP_3: erase/program protect sector 48 ~ sector 63
      \arg        OB_WP_4: erase/program protect sector 64 ~ sector 79
      \arg        OB_WP_5: erase/program protect sector 80 ~ sector 95
      \arg        OB_WP_6: erase/program protect sector 96 ~ sector 111
      \arg        OB_WP_7: erase/program protect sector 112 ~ sector 127
      \arg        OB_WP_8: erase/program protect sector 128 ~ sector 143
      \arg        OB_WP_9: erase/program protect sector 144 ~ sector 159
      \arg        OB_WP_10: erase/program protect sector 160 ~ sector 175
      \arg        OB_WP_11: erase/program protect sector 176 ~ sector 191
      \arg        OB_WP_12: erase/program protect sector 192 ~ sector 207
      \arg        OB_WP_13: erase/program protect sector 208 ~ sector 223
      \arg        OB_WP_14: erase/program protect sector 224 ~ sector 239
      \arg        OB_WP_15: erase/program protect sector 240 ~ sector 255
      \arg        OB_WP_16: erase/program protect sector 256 ~ sector 383
      \arg        OB_WP_17: erase/program protect sector 384 ~ sector 511
      \arg        OB_WP_18: erase/program protect sector 512 ~ sector 639
      \arg        OB_WP_19: erase/program protect sector 640 ~ sector 767
      \arg        OB_WP_20: erase/program protect sector 768 ~ sector 895
      \arg        OB_WP_21: erase/program protect sector 896 ~ sector 959
      \arg        OB_WP_ALL: all sectors
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp)
{
    uint32_t wp_reg = FMC_WP_EFT;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        wp_reg &= ~ob_wp;
        FMC_WP_MDF = wp_reg;
    }

    return fmc_state;
}

/*!
    \brief      disable erase/program protection
    \param[in]  ob_wp: specify sector to be erase/program protected
                one or more parameters can be selected which are shown as below:
      \arg        OB_WP_0 ee/program protect sector 0 ~ sector 15
      \arg        OB_WP_1: erase/program protect sector 16 ~ sector 31
      \arg        OB_WP_2: erase/program protect sector 32 ~ sector 47
      \arg        OB_WP_3: erase/program protect sector 48 ~ sector 63
      \arg        OB_WP_4: erase/program protect sector 64 ~ sector 79
      \arg        OB_WP_5: erase/program protect sector 80 ~ sector 95
      \arg        OB_WP_6: erase/program protect sector 96 ~ sector 111
      \arg        OB_WP_7: erase/program protect sector 112 ~ sector 127
      \arg        OB_WP_8: erase/program protect sector 128 ~ sector 143
      \arg        OB_WP_9: erase/program protect sector 144 ~ sector 159
      \arg        OB_WP_10: erase/program protect sector 160 ~ sector 175
      \arg        OB_WP_11: erase/program protect sector 176 ~ sector 191
      \arg        OB_WP_12: erase/program protect sector 192 ~ sector 207
      \arg        OB_WP_13: erase/program protect sector 208 ~ sector 223
      \arg        OB_WP_14: erase/program protect sector 224 ~ sector 239
      \arg        OB_WP_15: erase/program protect sector 240 ~ sector 255
      \arg        OB_WP_16: erase/program protect sector 256 ~ sector 383
      \arg        OB_WP_17: erase/program protect sector 384 ~ sector 511
      \arg        OB_WP_18: erase/program protect sector 512 ~ sector 639
      \arg        OB_WP_19: erase/program protect sector 640 ~ sector 767
      \arg        OB_WP_20: erase/program protect sector 768 ~ sector 895
      \arg        OB_WP_21: erase/program protect sector 896 ~ sector 959
      \arg        OB_WP_ALL: all sectors
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum ob_write_protection_disable(uint32_t ob_wp)
{
    uint32_t wp_reg = FMC_WP_EFT;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        wp_reg |= ob_wp;
        FMC_WP_MDF = wp_reg;
    }

    return fmc_state;
}

/*!
    \brief      get the option byte secure access mode
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_secure_mode_get(void)
{
    FlagStatus secure_mode_state = RESET;

    if(OB_SECURE_MODE_ENABLE == (uint32_t)(FMC_OBSTAT0_EFT & FMC_OBSTAT0_EFT_SCR))
    {
        secure_mode_state = SET;
    } else {
        secure_mode_state = RESET;
    }
    return secure_mode_state;
}

/*!
    \brief      get the option byte security protection level
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_security_protection_flag_get(void)
{
    FlagStatus spc_state = RESET;

    if(((uint8_t)(FMC_OBSTAT0_EFT >> OBSTAT0_SPC_OFFSET)) != (uint8_t)FMC_NSPC)
    {
        spc_state = SET;
    } else {
        spc_state = RESET;
    }
    return spc_state;
}

/*!
    \brief      get the option byte BOR threshold value
    \param[in]  none
    \param[out] none
    \retval     the BOR threshold value:
      \arg        OB_BOR_TH_VALUE3: BOR threshold value 3
      \arg        OB_BOR_TH_VALUE2: BOR threshold value 2
      \arg        OB_BOR_TH_VALUE1: BOR threshold value 1
      \arg        OB_BOR_TH_OFF: no BOR function
*/
uint32_t ob_bor_threshold_get(void)
{
    return (uint32_t)((uint32_t)FMC_OBSTAT0_EFT & FMC_OBSTAT0_EFT_BOR_TH);
}

/*!
    \brief      get low power related option byte
    \param[in]  none
    \param[out] fwdgt: watchdog option
      \arg        OB_FWDGT_HW: hardware free watchdog
      \arg        OB_FWDGT_SW: software free watchdog
    \param[out] deepsleep: deepsleep reset option
      \arg        OB_DEEPSLEEP_RST: generate a reset instead of entering deepsleep mode
      \arg        OB_DEEPSLEEP_NRST: no reset when entering deepsleep mode
    \param[out] standby: standby reset option
      \arg        OB_STDBY_RST: generate a reset instead of entering standby mode
      \arg        OB_STDBY_NRST: no reset when entering standby mode
    \param[out] fwdg_suspend_deepsleep: FWDG suspend status in deepsleep mode option
      \arg        OB_DPSLP_FWDGT_SUSPEND: free watchdog is suspended in deepsleep mode
      \arg        OB_DPSLP_FWDGT_RUN: free watchdog is running in deepsleep mode
    \param[out] fwdg_suspend_standby: FWDG suspend status in standby mode option
      \arg        OB_STDBY_FWDGT_SUSPEND: free watchdog is suspended in standby mode
      \arg        OB_STDBY_FWDGT_RUN: free watchdog is running in standby mode
    \retval     none
*/
void ob_low_power_get(uint32_t *fwdgt, uint32_t *deepsleep, uint32_t *standby, uint32_t *fwdg_suspend_deepsleep, uint32_t *fwdg_suspend_standby)
{
    uint32_t obstat0_reg;

    obstat0_reg = FMC_OBSTAT0_EFT;
    *fwdgt = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_NWDG_HW);
    *deepsleep = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_NRST_DPSLP);
    *standby = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_NRST_STDBY);
    *fwdg_suspend_deepsleep = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_FWDGSPD_DPSLP);
    *fwdg_suspend_standby = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_FWDGSPD_STDBY);
}

/*!
    \brief      get TCM ECC configuration
    \param[in]  none
    \param[out] itcmecc_option: CPU ITCM ECC function enable option
      \arg        OB_ITCMECCEN_DISABLE: ITCM ECC function disable
      \arg        OB_ITCMECCEN_ENABLE: ITCM ECC function enable
    \param[out] dtcm0ecc_option: CPU DTCM0 ECC function enable option
      \arg        OB_DTCM0ECCEN_DISABLE: DTCM0 ECC function disable
      \arg        OB_DTCM0ECCEN_ENABLE: DTCM0 ECC function enable
    \param[out] dtcm1ecc_option: CPU DTCM1 ECC function enable option
      \arg        OB_DTCM1ECCEN_DISABLE: DTCM1 ECC function disable
      \arg        OB_DTCM1ECCEN_ENABLE: DTCM1 ECC function enable
    \retval     none
*/
void ob_tcm_ecc_get(uint32_t *itcmecc_option, uint32_t *dtcm0ecc_option, uint32_t *dtcm1ecc_option)
{
    uint32_t obstat0_reg;

    obstat0_reg = FMC_OBSTAT0_EFT;
    *itcmecc_option = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_ITCMECCEN);
    *dtcm0ecc_option = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_DTCM0ECCEN);
    *dtcm1ecc_option = (uint32_t)(obstat0_reg & FMC_OBSTAT0_EFT_DTCM1ECCEN);
}

/*!
    \brief      get IO speed optimize configuration
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus ob_iospeed_optimize_get(void)
{
    FlagStatus iospeed_opt_state = RESET;

    if(OB_IOSPDOPEN_ENABLE == (uint32_t)(FMC_OBSTAT0_EFT & FMC_OBSTAT0_EFT_IOSPDOPEN))
    {
        iospeed_opt_state = SET;
    } else {
        iospeed_opt_state = RESET;
    }
    return iospeed_opt_state;
}

/*!
    \brief      get the option byte TCM shared RAM size
    \param[in]  none
    \param[out] itcm_shared_ram_kb_size: ITCM shared RAM size in KB unit
      \arg        OB_ITCM_SHARED_RAM_0KB: ITCM shared RAM size is 0KB
      \arg        OB_ITCM_SHARED_RAM_64KB: ITCM shared RAM size is 64KB
      \arg        OB_ITCM_SHARED_RAM_128KB: ITCM shared RAM size is 128KB
      \arg        OB_ITCM_SHARED_RAM_256KB: ITCM shared RAM size is 256KB
      \arg        OB_ITCM_SHARED_RAM_512KB: ITCM shared RAM size is 512KB
    \param[out] dtcm_shared_ram_kb_size: DTCM shared RAM size in KB unit
      \arg        OB_DTCM_SHARED_RAM_0KB: DTCM shared RAM size is 0KB
      \arg        OB_DTCM_SHARED_RAM_64KB: DTCM shared RAM size is 64KB
      \arg        OB_DTCM_SHARED_RAM_128KB: DTCM shared RAM size is 128KB
      \arg        OB_DTCM_SHARED_RAM_256KB: DTCM shared RAM size is 256KB
      \arg        OB_DTCM_SHARED_RAM_512KB: DTCM shared RAM size is 512KB
    \retval     none
*/
void ob_tcm_shared_ram_size_get(uint32_t *itcm_shared_ram_kb_size, uint32_t *dtcm_shared_ram_kb_size)
{
    uint32_t itcm_size_value, dtcm_size_value;

    itcm_size_value = (uint32_t)((uint32_t)FMC_OBSTAT1_EFT & FMC_OBSTAT1_EFT_ITCM_SZ_SHRRAM);
    dtcm_size_value = (uint32_t)((uint32_t)FMC_OBSTAT1_EFT & FMC_OBSTAT1_EFT_DTCM_SZ_SHRRAM);

    switch(itcm_size_value)
    {
    case OB_ITCM_SHARED_RAM_0KB:
        /* ITCM shared RAM size is 0KB */
        *itcm_shared_ram_kb_size = 0U;
        break;
    case OB_ITCM_SHARED_RAM_64KB:
        /* ITCM shared RAM size is 64KB */
        *itcm_shared_ram_kb_size = 64U;
        break;
    case OB_ITCM_SHARED_RAM_128KB:
        /* ITCM shared RAM size is 128KB */
        *itcm_shared_ram_kb_size = 128U;
        break;
    case OB_ITCM_SHARED_RAM_256KB:
        /* ITCM shared RAM size is 256KB */
        *itcm_shared_ram_kb_size = 256U;
        break;
    case OB_ITCM_SHARED_RAM_512KB:
        /* ITCM shared RAM size is 512KB */
        *itcm_shared_ram_kb_size = 512U;
        break;
    default:
        break;
    }

    switch(dtcm_size_value)
    {
    case OB_DTCM_SHARED_RAM_0KB:
        /* DTCM shared RAM size is 0KB */
        *dtcm_shared_ram_kb_size = 0U;
        break;
    case OB_DTCM_SHARED_RAM_64KB:
        /* DTCM shared RAM size is 64KB */
        *dtcm_shared_ram_kb_size = 64U;
        break;
    case OB_DTCM_SHARED_RAM_128KB:
        /* DTCM shared RAM size is 128KB */
        *dtcm_shared_ram_kb_size = 128U;
        break;
    case OB_DTCM_SHARED_RAM_256KB:
        /* DTCM shared RAM size is 256KB */
        *dtcm_shared_ram_kb_size = 256U;
        break;
    case OB_DTCM_SHARED_RAM_512KB:
        /* DTCM shared RAM size is 512KB */
        *dtcm_shared_ram_kb_size = 512U;
        break;
    default:
        break;
    }
}

/*!
    \brief      get user data value
    \param[in]  none
    \param[out] none
    \retval     option bytes user data
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)(FMC_OBSTAT1_EFT >> OBSTAT1_DATA_OFFSET);
}

/*!
    \brief      get boot address
    \param[in]  boot_pin: boot pin configuration
                only one parameter can be selected which is shown as below:
      \arg        BOOT_PIN_0: boot pin value is 0
      \arg        BOOT_PIN_1: boot pin value is 1
    \param[out] none
    \retval     boot_address: boot address
*/
uint32_t ob_boot_address_get(uint8_t boot_pin)
{
    uint32_t boot_address;
    uint32_t btaddr_reg = FMC_BTADDR_EFT;

    if(BOOT_PIN_0 == boot_pin)
    {
        /* get boot address 0 */
        boot_address = (uint32_t)((btaddr_reg & FMC_BTADDR_EFT_BOOT_ADDR0) << 16u);
    } else {
        /* get boot address 1 */
        boot_address = (uint32_t)((btaddr_reg & FMC_BTADDR_EFT_BOOT_ADDR1));
    }
    return boot_address;
}

/*!
    \brief      get DCRP area configuration
    \param[in]  none
    \param[out] dcrp_erase_option: DCRP area erase option
      \arg        OB_DCRP_AREA_ERASE_DISABLE: DCRP area erase disable
      \arg        OB_DCRP_AREA_ERASE_ENABLE: DCRP area erase enable
    \param[out] dcrp_start_addr: DCRP area start address, contain the first 4K-byte block of the DCRP area.(0 - 0x3BF)
    \param[out] dcrp_end_addr: DCRP area end address, contain the last 4K-byte block of the DCRP area.(0 - 0x3BF)
    \retval     state of DCRP area address
      \arg        INVLD_AREA_ADDRESS: the area address is invalid
      \arg        VLD_AREA_ADDRESS: the area address is valid
*/
uint8_t ob_dcrp_area_get(uint32_t *dcrp_erase_option, uint32_t *dcrp_area_start_addr, uint32_t *dcrp_area_end_addr)
{
    uint32_t dcrpaddr_reg;
    uint32_t main_flash_size;
    dcrpaddr_reg = FMC_DCRPADDR_EFT;
    main_flash_size = REG32(FLASH_DENSITY_ADDRESS) >> FLASH_DENSITY_OFFSET;

    /* get DCRP area erase option */
    *dcrp_erase_option = (uint32_t)(dcrpaddr_reg & FMC_DCRPADDR_EFT_DCRP_EREN);
    *dcrp_area_start_addr = ((uint32_t)(dcrpaddr_reg & FMC_DCRPADDR_EFT_DCRP_AREA_START)) >> DCRPADDR_DCRP_AREA_START_OFFSET;
    *dcrp_area_end_addr = ((uint32_t)(dcrpaddr_reg & FMC_DCRPADDR_EFT_DCRP_AREA_END)) >> DCRPADDR_DCRP_AREA_END_OFFSET;
    if((*dcrp_area_start_addr) == (*dcrp_area_end_addr))
    {
        /* the whole main flash memory is DCRP area */
        *dcrp_area_start_addr = MAIN_FLASH_BASE_ADDRESS;
        *dcrp_area_end_addr = MAIN_FLASH_BASE_ADDRESS + main_flash_size - 1U;
        return VLD_AREA_ADDRESS;
    } else if((*dcrp_area_start_addr) < (*dcrp_area_end_addr))
    {
        /* get DCRP area start address */
        *dcrp_area_start_addr = (*dcrp_area_start_addr) * DCRP_SIZE_UNIT;
        *dcrp_area_start_addr += MAIN_FLASH_BASE_ADDRESS;
        /* get DCRP area end address */
        *dcrp_area_end_addr = ((*dcrp_area_end_addr) + 1U) * DCRP_SIZE_UNIT - 1U;
        *dcrp_area_end_addr += MAIN_FLASH_BASE_ADDRESS;
        return VLD_AREA_ADDRESS;
    } else {
        /* no valid DCRP area */
        return INVLD_AREA_ADDRESS;
    }
}

/*!
    \brief      get secure-access area configuration
    \param[in]  none
    \param[out] secure_erase_option: secure-access area erase option
      \arg        OB_SCR_AREA_ERASE_DISABLE: secure-access area erase disable
      \arg        OB_SCR_AREA_ERASE_ENABLE: secure-access area erase enable
    \param[out] scr_area_start_addr: secure-access area start address, contain the first 4K-byte block of the secure-access area.(0 - 0x3BF)
    \param[out] scr_area_end_addr: secure-access area end address, contain the last 4K-byte block of the secure-access area.(0 - 0x3BF)
    \retval     state of secure-access area address
      \arg        INVLD_AREA_ADDRESS: the area address is invalid
      \arg        VLD_AREA_ADDRESS: the area address is valid
*/
uint8_t ob_secure_area_get(uint32_t *secure_area_option, uint32_t *scr_area_start_addr, uint32_t *scr_area_end_addr)
{
    uint32_t scraddr_reg;
    uint32_t main_flash_size;
    scraddr_reg = FMC_SCRADDR_EFT;
    main_flash_size = REG32(FLASH_DENSITY_ADDRESS) >> FLASH_DENSITY_OFFSET;

    /* get secure-access area erase option */
    *secure_area_option = (uint32_t)(scraddr_reg & FMC_SCRADDR_EFT_SCR_EREN);
    *scr_area_start_addr = ((uint32_t)(scraddr_reg & FMC_SCRADDR_EFT_SCR_AREA_START)) >> SCRADDR_SCR_AREA_START_OFFSET;
    *scr_area_end_addr = ((uint32_t)(scraddr_reg & FMC_SCRADDR_EFT_SCR_AREA_END)) >> SCRADDR_SCR_AREA_END_OFFSET;
    if((*scr_area_start_addr) == (*scr_area_end_addr))
    {
        /* the whole main flash memory is secure-access area */
        *scr_area_start_addr = MAIN_FLASH_BASE_ADDRESS;
        *scr_area_end_addr = MAIN_FLASH_BASE_ADDRESS + main_flash_size - 1U;
        return VLD_AREA_ADDRESS;
    } else if((*scr_area_start_addr) < (*scr_area_end_addr))
    {
        /* get secure-access area start address */
        *scr_area_start_addr = (*scr_area_start_addr) * SCR_SIZE_UNIT;
        *scr_area_start_addr += MAIN_FLASH_BASE_ADDRESS;
        /* get secure-access area end address */
        *scr_area_end_addr = ((*scr_area_end_addr) + 1U) * SCR_SIZE_UNIT - 1U;
        *scr_area_end_addr += MAIN_FLASH_BASE_ADDRESS;
        return VLD_AREA_ADDRESS;
    } else {
        /* no valid area */
        return INVLD_AREA_ADDRESS;
    }
}

/*!
    \brief      get the option byte erase/program protection
    \param[in]  none
    \param[out] none
    \retval     the FMC erase/program protection option byte value(0 - 0x3FFFFFFF)
*/
uint32_t ob_write_protection_get(void)
{
    /* return the FMC erase/program protection option byte value */
    return (uint32_t)(FMC_WP_EFT);
}

/*!
    \brief      configure NO-RTDEC area
    \param[in]  nodec_area_start: no rtdec area start address, contain the last 4K-byte block that reading main flash block without decryption.
    \param[in]  nodec_area_end: no rtdec area end address, contain the first 4K-byte block that reading main flash block without decryption.
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_no_rtdec_config(uint32_t nodec_area_start, uint32_t nodec_area_end)
{
    uint32_t nodec_reg;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        fmc_unlock();
        nodec_reg = 0U;
        nodec_reg |= nodec_area_start;
        nodec_reg |= (uint32_t)(nodec_area_end << NODEC_NODEC_AREA_END_OFFSET);
        FMC_NODEC = nodec_reg;
        fmc_lock();
    }

    return fmc_state;
}

/*!
    \brief      configure AES initialization vector
    \param[in]  aes_iv: high 96 bits of AES initialization vector
    \param[out] none
    \retval     state of FMC
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
fmc_state_enum fmc_aes_iv_config(uint32_t *aes_iv)
{
    uint32_t aes_iv_addr = (uint32_t)aes_iv;
    fmc_state_enum fmc_state = FMC_READY;

    /* wait for the FMC ready */
    fmc_state = fmc_ready_wait(FMC_TIMEOUT_COUNT);

    if(FMC_READY == fmc_state)
    {
        fmc_unlock();
        FMC_AESIV0_MDF = *(uint32_t *)(aes_iv_addr);
        aes_iv_addr += 4U;
        FMC_AESIV1_MDF = *(uint32_t *)(aes_iv_addr);
        aes_iv_addr += 4U;
        FMC_AESIV2_MDF = *(uint32_t *)(aes_iv_addr);
        fmc_lock();
    }

    return fmc_state;
}

/*!
    \brief      get Flash ECC function enable flag
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flash_ecc_get(void)
{
    return fmc_flag_get((fmc_flag_enum)FMC_FLAG_FECC);
}

/*!
    \brief      get NO-RTDEC area
    \param[in]  none
    \param[out] nodec_area_start: no rtdec area start address, contain the last 4K-byte block that reading main flash block without decryption.
    \param[out] nodec_area_end: no rtdec area end address, contain the first 4K-byte block that reading main flash block without decryption.
    \retval     none
*/
void fmc_no_rtdec_get(uint32_t *nodec_area_start, uint32_t *nodec_area_end)
{
    uint32_t nodec_reg;

    nodec_reg = FMC_NODEC;
    *nodec_area_start = (uint32_t)(nodec_reg & FMC_NODEC_NODEC_AREA_START);
    *nodec_area_end = (uint32_t)(nodec_reg & FMC_NODEC_NODEC_AREA_END);
}

/*!
    \brief      get AES initialization vector
    \param[in]  none
    \param[out] aes_iv: high 96 bits of AES initialization vector
    \retval     none
*/
void fmc_aes_iv_get(uint32_t *aes_iv)
{
    uint32_t aes_iv_addr = (uint32_t)aes_iv;
    *(uint32_t *)aes_iv_addr = (uint32_t)(FMC_AESIV0_EFT);
    aes_iv_addr += 4U;
    *(uint32_t *)aes_iv_addr = (uint32_t)(FMC_AESIV1_EFT);
    aes_iv_addr += 4U;
    *(uint32_t *)aes_iv_addr = (uint32_t)(FMC_AESIV2_EFT);
}

/*!
    \brief      get product ID
    \param[in]  none
    \param[out] pid: product ID
    \retval     none
*/
void fmc_pid_get(uint32_t *pid)
{
    uint32_t pid_addr = (uint32_t)pid;
    *(uint32_t *)pid_addr = (uint32_t)(FMC_PID0);
    pid_addr += 4U;
    *(uint32_t *)pid_addr = (uint32_t)(FMC_PID1);
}

/*!
    \brief      get FMC flag status
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_BUSY: flash busy flag bit
      \arg        FMC_FLAG_END: flash end of operation flag bit
      \arg        FMC_FLAG_WPERR: flash erase/program protection error flag bit
      \arg        FMC_FLAG_PGSERR: flash program sequence error flag bit
      \arg        FMC_FLAG_RPERR: flash read protection error flag bit
      \arg        FMC_FLAG_RSERR: flash read secure error flag bit
      \arg        FMC_FLAG_ECCCOR: flash one bit correct error flag bit
      \arg        FMC_FLAG_ECCDET: flash two bits detect error flag bit
      \arg        FMC_FLAG_OBMERR: flash option byte modify error flag bit
      \arg        FMC_FLAG_FECC: flash ECC function flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(fmc_flag_enum flag)
{
    if(RESET != (FMC_REG_VAL(flag) & BIT(FMC_BIT_POS(flag))))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear FMC flag status
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_FLAG_END: flash end of operation flag bit
      \arg        FMC_FLAG_WPERR: flash erase/program protection error flag bit
      \arg        FMC_FLAG_PGSERR: flash program sequence error flag bit
      \arg        FMC_FLAG_RPERR: flash read protection error flag bit
      \arg        FMC_FLAG_RSERR: flash read secure error flag bit
      \arg        FMC_FLAG_ECCCOR: flash one bit correct error flag bit
      \arg        FMC_FLAG_ECCDET: flash two bits detect error flag bit
      \arg        FMC_FLAG_OBMERR: flash option byte modify error flag bit
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(fmc_flag_enum flag)
{
    /* clear the flags */
    FMC_REG_VAL(flag) = BIT(FMC_BIT_POS(flag));
}

/*!
    \brief      enable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END : FMC end of program interrupt
      \arg        FMC_INT_WPERR: FMC erase/program protection error interrupt
      \arg        FMC_INT_PGSERR: FMC program sequence error interrupt
      \arg        FMC_INT_RPERR: FMC read protection error interrupt
      \arg        FMC_INT_RSERR: FMC read secure error interrupt
      \arg        FMC_INT_ECCCOR: FMC one bit correct error interrupt
      \arg        FMC_INT_ECCDET: FMC two bits detect error interrupt
      \arg        FMC_INT_OBMERR: FMC option byte modify error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(fmc_interrupt_enum interrupt)
{
    FMC_REG_VAL(interrupt) |= BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      disable FMC interrupt
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_END : FMC end of program interrupt
      \arg        FMC_INT_WPERR: FMC erase/program protection error interrupt
      \arg        FMC_INT_PGSERR: FMC program sequence error interrupt
      \arg        FMC_INT_RPERR: FMC read protection error interrupt
      \arg        FMC_INT_RSERR: FMC read secure error interrupt
      \arg        FMC_INT_ECCCOR: FMC one bit correct error interrupt
      \arg        FMC_INT_ECCDET: FMC two bits detect error interrupt
      \arg        FMC_INT_OBMERR: FMC option byte modify error interrupt
    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(fmc_interrupt_enum interrupt)
{
    FMC_REG_VAL(interrupt) &= ~BIT(FMC_BIT_POS(interrupt));
}

/*!
    \brief      get FMC interrupt flag status
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_END: flash end of operation interrupt flag
      \arg        FMC_INT_FLAG_WPERR: flash erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_PGSERR: flash program sequence error interrupt flag
      \arg        FMC_INT_FLAG_RPERR: flash read protection error interrupt flag
      \arg        FMC_INT_FLAG_RSERR: flash read secure error interrupt flag
      \arg        FMC_INT_FLAG_ECCCOR: flash one bit error detected and correct interrupt flag
      \arg        FMC_INT_FLAG_ECCDET: flash two bit errors detect interrupt flag
      \arg        FMC_INT_FLAG_OBMERR: option byte modify error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag)
{
    uint32_t intenable = 0U, flagstatus = 0U;
    /* get the interrupt enable bit status */
    intenable = (FMC_REG_VAL(int_flag) & BIT(FMC_BIT_POS(int_flag)));
    /* get the corresponding flag bit status */
    flagstatus = (FMC_REG_VAL2(int_flag) & BIT(FMC_BIT_POS2(int_flag)));

    if(flagstatus && intenable)
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief    clear FMC interrupt flag status
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_INT_FLAG_END: flash end of operation interrupt flag
      \arg        FMC_INT_FLAG_WPERR: flash erase/program protection error interrupt flag
      \arg        FMC_INT_FLAG_PGSERR: flash program sequence error interrupt flag
      \arg        FMC_INT_FLAG_RPERR: flash read protection error interrupt flag
      \arg        FMC_INT_FLAG_RSERR: flash read secure error interrupt flag
      \arg        FMC_INT_FLAG_ECCCOR: flash one bit error detected and correct interrupt flag
      \arg        FMC_INT_FLAG_ECCDET: flash two bit errors detect interrupt flag
      \arg        FMC_INT_FLAG_OBMERR: option byte modify error flag
    \param[out] none
    \retval     none
*/
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag)
{
    /* clear the intrrupt flag */
    FMC_REG_VAL2(int_flag) = BIT(FMC_BIT_POS2(int_flag));
}

/*!
    \brief      get FMC state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: operation has been completed
      \arg        FMC_BUSY: operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
*/
static fmc_state_enum fmc_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_BUSY))
    {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_WPERR))
        {
            fmc_state = FMC_WPERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_PGSERR))
        {
            fmc_state = FMC_PGSERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_RPERR))
        {
            fmc_state = FMC_RPERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_RSERR))
        {
            fmc_state = FMC_RSERR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_ECCCOR))
        {
            fmc_state = FMC_ECCCOR;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_ECCDET))
        {
            fmc_state = FMC_ECCDET;
        } else if((uint32_t)0x00U != (FMC_STAT & FMC_STAT_OBMERR))
        {
            fmc_state = FMC_OBMERR;
        } else {
            /* illegal parameters */
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
      \arg        FMC_READY: operation has been completed
      \arg        FMC_BUSY: operation is in progress
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_RPERR: read protection error
      \arg        FMC_RSERR: read secure error
      \arg        FMC_ECCCOR: one bit correct error
      \arg        FMC_ECCDET: two bits detect error
      \arg        FMC_OBMERR: option byte modify error
      \arg        FMC_TOERR: timeout error
*/
static fmc_state_enum fmc_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state = FMC_BUSY;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0U != timeout));

    if(FMC_BUSY == fmc_state)
    {
        fmc_state = FMC_TOERR;
    }
    /* return the FMC state */
    return fmc_state;
}
