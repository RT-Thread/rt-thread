/*!
    \file    gd32f5xx_syscfg.c
    \brief   SYSCFG driver

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

#include "gd32f5xx_syscfg.h"

/*!
    \brief    reset the SYSCFG registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

/*!
    \brief    configure the boot mode
    \param[in]  syscfg_bootmode: selects the memory remapping
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_BOOTMODE_FLASH: main flash memory (0x08000000~0x0877FFFF) is mapped at address 0x00000000
      \arg        SYSCFG_BOOTMODE_BOOTLOADER: boot loader (0x1FFF0000~0x1FFF77FF) is mapped at address 0x00000000
      \arg        SYSCFG_BOOTMODE_SRAM:       SRAM0 of on-chip SRAM(0x20000000~0x2003FFFF)  is mapped at address 0x00000000
      \arg        SYSCFG_BOOTMODE_OTP:        OTP(0x1FF00000~0x1FF1FFFF) is mapped at address 0x00000000
    \param[out] none
    \retval     none
*/
void syscfg_bootmode_config(uint8_t syscfg_bootmode)
{
    /* reset the SYSCFG_CFG0_BOOT_MODE bit and set according to syscfg_bootmode */
    SYSCFG_CFG0 &= ~SYSCFG_CFG0_BOOT_MODE;
    SYSCFG_CFG0 |= (uint32_t)syscfg_bootmode;
}

/*!
    \brief    FMC memory mapping swap
    \param[in]  syscfg_fmc_swap: selects the interal flash bank swapping
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_FMC_SWP_BANK0: bank 0 is mapped at address 0x08000000 and bank 1 is mapped at address 0x08100000(if main flash is 4M,the swaped address is 0x0820_0000)
      \arg        SYSCFG_FMC_SWP_BANK1: bank 1 is mapped at address 0x08000000 and bank 0 is mapped at address 0x08100000(if main flash is 4M,the swaped address is 0x0820_0000)
    \param[out] none
    \retval     none
*/
void syscfg_fmc_swap_config(uint32_t syscfg_fmc_swap)
{
    uint32_t reg;
    reg = SYSCFG_CFG0;
    /* reset the FMC_SWP bit and set according to syscfg_fmc_swap */
    reg &= ~SYSCFG_CFG0_FMC_SWP;
    SYSCFG_CFG0 = (reg | syscfg_fmc_swap);
}

/*!
    \brief    EXMC memory mapping swap
    \param[in]  syscfg_exmc_swap: selects the memories in EXMC swapping
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_EXMC_SWP_ENABLE: SDRAM bank 0 and bank 1 are swapped with NAND bank 1 and PC card
      \arg        SYSCFG_EXMC_SWP_DISABLE: no memory mapping swap
    \param[out] none
    \retval     none
*/
void syscfg_exmc_swap_config(uint32_t syscfg_exmc_swap)
{
    uint32_t reg;

    reg = SYSCFG_CFG0;
    /* reset the SYSCFG_CFG0_EXMC_SWP bits and set according to syscfg_exmc_swap */
    reg &= ~SYSCFG_CFG0_EXMC_SWP;
    SYSCFG_CFG0 = (reg | syscfg_exmc_swap);
}

/*!
    \brief    configure the GPIO pin as EXTI Line
    \param[in]  exti_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_GPIOx(x = A,B,C,D,E,F,G,H,I): EXTI GPIO port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_PINx(x = 0..15): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

    switch(exti_pin / EXTI_SS_JSTEP) {
    case EXTISS0:
        /* clear EXTI source line(0..3) */
        SYSCFG_EXTISS0 &= clear_exti_mask;
        /* configure EXTI soure line(0..3) */
        SYSCFG_EXTISS0 |= config_exti_mask;
        break;
    case EXTISS1:
        /* clear EXTI soure line(4..7) */
        SYSCFG_EXTISS1 &= clear_exti_mask;
        /* configure EXTI soure line(4..7) */
        SYSCFG_EXTISS1 |= config_exti_mask;
        break;
    case EXTISS2:
        /* clear EXTI soure line(8..11) */
        SYSCFG_EXTISS2 &= clear_exti_mask;
        /* configure EXTI soure line(8..11) */
        SYSCFG_EXTISS2 |= config_exti_mask;
        break;
    case EXTISS3:
        /* clear EXTI soure line(12..15) */
        SYSCFG_EXTISS3 &= clear_exti_mask;
        /* configure EXTI soure line(12..15) */
        SYSCFG_EXTISS3 |= config_exti_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief    configure the PHY interface for the ethernet MAC
    \param[in]  syscfg_enet_phy_interface: specifies the media interface mode.
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_ENET_PHY_MII: MII mode is selected
      \arg        SYSCFG_ENET_PHY_RMII: RMII mode is selected
    \param[out] none
    \retval     none
*/
void syscfg_enet_phy_interface_config(uint32_t syscfg_enet_phy_interface)
{
    uint32_t reg;

    reg = SYSCFG_CFG1;
    /* reset the ENET_PHY_SEL bit and set according to syscfg_enet_phy_interface */
    reg &= ~SYSCFG_CFG1_ENET_PHY_SEL;
    SYSCFG_CFG1 = (reg | syscfg_enet_phy_interface);
}

/*!
    \brief    configure the I/O compensation cell
    \param[in]  syscfg_compensation: specifies the I/O compensation cell mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_COMPENSATION_ENABLE: I/O compensation cell is enabled
      \arg        SYSCFG_COMPENSATION_DISABLE: I/O compensation cell is disabled
    \param[out] none
    \retval     none
*/
void syscfg_compensation_config(uint32_t syscfg_compensation)
{
    uint32_t reg;

    reg = SYSCFG_CPSCTL;
    /* reset the SYSCFG_CPSCTL_CPS_EN bit and set according to syscfg_compensation */
    reg &= ~SYSCFG_CPSCTL_CPS_EN;
    SYSCFG_CPSCTL = (reg | syscfg_compensation);
}

/*!
    \brief      get Compensation cell ready flag
    \param[in]  none
    \param[out] FlagStatus: the status of vref
      \arg        SET: the VREF output is ready
      \arg        RESET: the VREF output is not ready
    \retval     none
*/
FlagStatus syscfg_cps_cell_ready_get(void)
{
    if(SYSCFG_CPSCTL & SYSCFG_CPSCTL_CPS_RDY){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      get ECC event error bits
    \param[in]  ecc_type: ECC event type, refer to syscfg_ecc_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_SRAM0_ECC: SRAM0 ECC event
      \arg        SYSCFG_SRAM1_ECC: SRAM1 ECC event
      \arg        SYSCFG_SRAM2_ECC: SRAM2 ECC event
      \arg        SYSCFG_ADDSRAM_ECC: ADDSRAM ECC event
      \arg        SYSCFG_TCMSRAM_ECC: TCMSRAM ECC event
      \arg        SYSCFG_BKPSRAM_ECC: BKPSRAM ECC event
      \arg        SYSCFG_FLASH_ECC: FLASH ECC event
    \param[out] none
    \retval     error bits
*/
uint32_t syscfg_ecc_err_bits_get(syscfg_ecc_enum ecc_type)
{
    uint32_t err_bits = 0U;
    
    switch(ecc_type){
    case SYSCFG_SRAM0_ECC:
        err_bits = (uint32_t)((SYSCFG_SRAM0ECC & SYSCFG_SRAM0ECC_ECCSERRBITS0) >> 10U);
        break;
    case SYSCFG_SRAM1_ECC:
        err_bits = (uint32_t)((SYSCFG_SRAM1ECC & SYSCFG_SRAM1ECC_ECCSERRBITS1) >> 12U);
        break;
    case SYSCFG_SRAM2_ECC:
        err_bits = (uint32_t)((SYSCFG_SRAM2ECC & SYSCFG_SRAM2ECC_ECCSERRBITS2) >> 10U);
        break;
    case SYSCFG_ADDSRAM_ECC:
        err_bits = (uint32_t)((SYSCFG_ADDSRAMECC & SYSCFG_ADDSRAMECC_ECCSERRBITS3) >> 8U);
        break;
    case SYSCFG_TCMSRAM_ECC:
        err_bits = (uint32_t)((SYSCFG_TCMSRAMECC & SYSCFG_TCMSRAMECC_ECCSERRBITS4) >> 12U);
        break;
    case SYSCFG_BKPSRAM_ECC:
        err_bits = (uint32_t)((SYSCFG_BKPSRAMECC & SYSCFG_BKPSRAMECC_ECCSERRBITS5) >> 16U);
        break;
    case SYSCFG_FLASH_ECC:
        err_bits = (uint32_t)((SYSCFG_FLASHECC & SYSCFG_FLASHECC_ECCSERRBITS6) >> 2U);
        break;
    default:
        /* should not jump to here */
        break;
    }
    
    return err_bits;
}

/*!
    \brief      get last address of ECC event
    \param[in]  ecc_type: ECC event type, refer to syscfg_ecc_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_SRAM0_ECC: SRAM0 ECC event
      \arg        SYSCFG_SRAM1_ECC: SRAM1 ECC event
      \arg        SYSCFG_SRAM2_ECC: SRAM2 ECC event
      \arg        SYSCFG_ADDSRAM_ECC: ADDSRAM ECC event
      \arg        SYSCFG_TCMSRAM_ECC: TCMSRAM ECC event
      \arg        SYSCFG_BKPSRAM_ECC: BKPSRAM ECC event
      \arg        SYSCFG_FLASH_ECC: FLASH ECC event
    \param[out] none
    \retval     error address
*/
uint32_t syscfg_ecc_address_get(syscfg_ecc_enum ecc_type)
{
    uint32_t err_addr = 0U;
    
    switch(ecc_type){
    case SYSCFG_SRAM0_ECC:
        err_addr = (uint32_t)((SYSCFG_SRAM0ECC & SYSCFG_SRAM0ECC_ECCEADDR0) >> 16U);
        break;
    case SYSCFG_SRAM1_ECC:
        err_addr = (uint32_t)((SYSCFG_SRAM1ECC & SYSCFG_SRAM1ECC_ECCEADDR1) >> 18U);
        break;
    case SYSCFG_SRAM2_ECC:
        err_addr = (uint32_t)((SYSCFG_SRAM2ECC & SYSCFG_SRAM2ECC_ECCEADDR2) >> 16U);
        break;
    case SYSCFG_ADDSRAM_ECC:
        err_addr = (uint32_t)((SYSCFG_ADDSRAMECC & SYSCFG_ADDSRAMECC_ECCEADDR3) >> 14U);
        break;
    case SYSCFG_TCMSRAM_ECC:
        err_addr = (uint32_t)((SYSCFG_TCMSRAMECC & SYSCFG_TCMSRAMECC_ECCEADDR4) >> 18U);
        break;
    case SYSCFG_BKPSRAM_ECC:
        err_addr = (uint32_t)((SYSCFG_BKPSRAMECC & SYSCFG_BKPSRAMECC_ECCEADDR5) >> 22U);
        break;
    case SYSCFG_FLASH_ECC:
        err_addr = (uint32_t)(SYSCFG_FLASHECC_ADDR);
        break;
    default:
        /* should not jump to here */
        break;
    }
    
    return err_addr;
}

/*!
    \brief      get SYSCFG flag state
    \param[in]  flag: SYSCFG flags, refer to syscfg_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_FLAG_ECCME0: SRAM0 two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE0: SRAM0 single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME1: SRAM1 two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE1: SRAM1 single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME2: SRAM2 two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE2: SRAM2 single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME3: ADDSRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE3: ADDSRAM single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME4: TCMSRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE4: TCMSRAM single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME5: BKPSRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE5: BKPSRAM single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME6: FLASH two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE6: FLASH single bit correction event flag
      \arg        SYSCFG_FLAG_CKMNMI: HXTAL clock moniotor NMI flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_flag_get(syscfg_flag_enum flag)
{
    /* get flag and interrupt enable state */
    if(RESET != (SYSCFG_STAT & (uint32_t)flag)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear SYSCFG flag state
    \param[in]  flag: SYSCFG flags, refer to syscfg_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_FLAG_ECCME0: SRAM0 two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE0: SRAM0 single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME1: SRAM1 two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE1: SRAM1 single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME2: SRAM2 two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE2: SRAM2 single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME3: ADDSRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE3: ADDSRAM single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME4: TCMSRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE4: TCMSRAM single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME5: BKPSRAM two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE5: BKPSRAM single bit correction event flag
      \arg        SYSCFG_FLAG_ECCME6: FLASH two bits non-correction event flag
      \arg        SYSCFG_FLAG_ECCSE6: FLASH single bit correction event flag
      \arg        SYSCFG_FLAG_CKMNMI: HXTAL clock moniotor NMI flag
    \param[out] none
    \retval     none
*/
void syscfg_flag_clear(syscfg_flag_enum flag)
{
    SYSCFG_STAT = (uint32_t)flag;
}

/*!
    \brief      enable SYSCFG interrupt
    \param[in]  interrupt: SYSCFG interrupt, refer to syscfg_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_ECCME0: SRAM0 two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE0: SRAM0 single bit correction interrupt
      \arg        SYSCFG_INT_CKMNMI: HXTAL clock moniotor NMI interrupt
      \arg        SYSCFG_INT_ECCME1: SRAM1 two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE1: SRAM1 single bit correction interrupt
      \arg        SYSCFG_INT_ECCME2: SRAM2 two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE2: SRAM2 single bit correction interrupt
      \arg        SYSCFG_INT_ECCME3: ADDSRAM two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE3: ADDSRAM single bit correction interrupt
      \arg        SYSCFG_INT_ECCME4: TCMSRAM two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE4: TCMSRAM single bit correction interrupt
      \arg        SYSCFG_INT_ECCME5: BKPSRAM two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE5: BKPSRAM single bit correction interrupt
      \arg        SYSCFG_INT_ECCME6: FLASH two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE6: FLASH single bit correction interrupt
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_enable(syscfg_interrupt_enum interrupt)
{
    SYSCFG_REG_VAL(interrupt) |= BIT(SYSCFG_BIT_POS(interrupt));
}

/*!
    \brief      disable SYSCFG interrupt
    \param[in]  interrupt: SYSCFG interrupt, refer to syscfg_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_ECCME0: SRAM0 two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE0: SRAM0 single bit correction interrupt
      \arg        SYSCFG_INT_CKMNMI: HXTAL clock moniotor NMI interrupt
      \arg        SYSCFG_INT_ECCME1: SRAM1 two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE1: SRAM1 single bit correction interrupt
      \arg        SYSCFG_INT_ECCME2: SRAM2 two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE2: SRAM2 single bit correction interrupt
      \arg        SYSCFG_INT_ECCME3: ADDSRAM two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE3: ADDSRAM single bit correction interrupt
      \arg        SYSCFG_INT_ECCME4: TCMSRAM two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE4: TCMSRAM single bit correction interrupt
      \arg        SYSCFG_INT_ECCME5: BKPSRAM two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE5: BKPSRAM single bit correction interrupt
      \arg        SYSCFG_INT_ECCME6: FLASH two bits non-correction interrupt
      \arg        SYSCFG_INT_ECCSE6: FLASH single bit correction interrupt
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_disable(syscfg_interrupt_enum interrupt)
{
    SYSCFG_REG_VAL(interrupt) &= ~BIT(SYSCFG_BIT_POS(interrupt));
}

/*!
    \brief      get SYSCFG interrupt flag state
    \param[in]  flag: SYSCFG interrupt flags, refer to syscfg_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_FLAG_ECCME0: SRAM0 two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE0: SRAM0 single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME1: SRAM1 two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE1: SRAM1 single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME2: SRAM2 two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE2: SRAM2 single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME3: ADDSRAM two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE3: ADDSRAM single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME4: TCMSRAM two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE4: TCMSRAM single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME5: BKPSRAM two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE5: BKPSRAM single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME6: FLASH two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE6: FLASH single bit correction event flag
      \arg        SYSCFG_INT_FLAG_CKMNMI: HXTAL clock moniotor NMI flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_interrupt_flag_get(syscfg_interrupt_flag_enum flag)
{
    /* get flag and interrupt enable state */
    if(RESET != (SYSCFG_STAT & (uint32_t)flag)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear SYSCFG interrupt flag state
    \param[in]  flag: SYSCFG interrupt flags, refer to syscfg_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_INT_FLAG_ECCME0: SRAM0 two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE0: SRAM0 single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME1: SRAM1 two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE1: SRAM1 single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME2: SRAM2 two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE2: SRAM2 single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME3: ADDSRAM two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE3: ADDSRAM single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME4: TCMSRAM two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE4: TCMSRAM single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME5: BKPSRAM two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE5: BKPSRAM single bit correction event flag
      \arg        SYSCFG_INT_FLAG_ECCME6: FLASH two bits non-correction event flag
      \arg        SYSCFG_INT_FLAG_ECCSE6: FLASH single bit correction event flag
      \arg        SYSCFG_INT_FLAG_CKMNMI: HXTAL clock moniotor NMI flag
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_flag_clear(syscfg_interrupt_flag_enum flag)
{
    SYSCFG_STAT = (uint32_t)flag;
}
