/*!
    \file    gd32f5xx_syscfg.h
    \brief   definitions for the SYSCFG
    
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

#ifndef GD32F5XX_SYSCFG_H
#define GD32F5XX_SYSCFG_H

#include "gd32f5xx.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE

/* registers definitions */
#define SYSCFG_CFG0                         REG32(SYSCFG + 0x00U)    /*!< system configuration register 0 */
#define SYSCFG_CFG1                         REG32(SYSCFG + 0x04U)    /*!< system configuration register 1 */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x08U)    /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0CU)    /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x10U)    /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x14U)    /*!< EXTI sources selection register 3 */
#define SYSCFG_CPSCTL                       REG32(SYSCFG + 0x20U)    /*!< system I/O compensation control register */
#define SYSCFG_STAT                         REG32(SYSCFG + 0x24U)    /*!< system status register 0 */
#define SYSCFG_SRAM0ECC                     REG32(SYSCFG + 0x28U)    /*!< SRAM0 ECC status register */
#define SYSCFG_SRAM1ECC                     REG32(SYSCFG + 0x2CU)    /*!< SRAM1 ECC status register */
#define SYSCFG_SRAM2ECC                     REG32(SYSCFG + 0x30U)    /*!< SRAM2 ECC status register */
#define SYSCFG_ADDSRAMECC                   REG32(SYSCFG + 0x34U)    /*!< ADDSRAM ECC status register */
#define SYSCFG_TCMSRAMECC                   REG32(SYSCFG + 0x38U)    /*!< TCMSRAM ECC status register */
#define SYSCFG_BKPSRAMECC                   REG32(SYSCFG + 0x3CU)    /*!< BKPSRAM ECC status register */
#define SYSCFG_FLASHECC_ADDR                REG32(SYSCFG + 0x40U)    /*!< FLASH ECC address register */
#define SYSCFG_FLASHECC                     REG32(SYSCFG + 0x44U)    /*!< FLASH ECC register */
#define USER_CFG                            REG32(SYSCFG + 0x300U)   /*!< user configuration register */

/* SYSCFG_CFG0 bits definitions */
#define SYSCFG_CFG0_BOOT_MODE               BITS(0,2)                /*!< SYSCFG memory remap config */
#define SYSCFG_CFG0_FMC_SWP                 BIT(8)                   /*!< FMC memory swap config */
#define SYSCFG_CFG0_EXMC_SWP                BITS(10,11)              /*!< EXMC memory swap config */

/* SYSCFG_CFG1 bits definitions */
#define SYSCFG_CFG1_I2C3FMP                 BIT(0)                   /*!< enable fast mode+ on I2C3 */
#define SYSCFG_CFG1_I2C4FMP                 BIT(1)                   /*!< enable fast mode+ on I2C4 */
#define SYSCFG_CFG1_I2C5FMP                 BIT(2)                   /*!< enable fast mode+ on I2C5 */
#define SYSCFG_CFG1_ENET_PHY_SEL            BIT(23)                  /*!< Ethernet PHY selection config */

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,3)                /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,7)                /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,11)               /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,15)              /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BITS(0,3)                /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BITS(4,7)                /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,11)               /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,15)              /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BITS(0,3)                /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BITS(4,7)                /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BITS(8,11)               /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BITS(12,15)              /*!< EXTI 11 configuration */

/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BITS(0,3)                /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,7)                /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,11)               /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,15)              /*!< EXTI 15 configuration */

/* SYSCFG_CPSCTL bits definitions */
#define SYSCFG_CPSCTL_CPS_EN                BIT(0)                   /*!< I/O compensation cell enable */
#define SYSCFG_CPSCTL_CPS_RDY               BIT(8)                   /*!< I/O compensation cell is ready or not */

/* SYSCFG_STAT bits definitions */
#define SYSCFG_STAT_ECCMEIF0                BIT(0)                   /*!< SRAM0 two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF0                BIT(1)                   /*!< SRAM0 single bit correction event flag */
#define SYSCFG_STAT_ECCMEIF1                BIT(2)                   /*!< SRAM1 two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF1                BIT(3)                   /*!< SRAM1 single bit correction event flag */
#define SYSCFG_STAT_ECCMEIF2                BIT(4)                   /*!< SRAM2 two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF2                BIT(5)                   /*!< SRAM2 single bit correction event flag */
#define SYSCFG_STAT_ECCMEIF3                BIT(6)                   /*!< ADDSRAM two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF3                BIT(7)                   /*!< ADDSRAM single bit correction event flag */
#define SYSCFG_STAT_ECCMEIF4                BIT(8)                   /*!< TCMSRAM two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF4                BIT(9)                   /*!< TCMSRAM single bit correction event flag */
#define SYSCFG_STAT_ECCMEIF5                BIT(10)                  /*!< BKPSRAM two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF5                BIT(11)                  /*!< BKPSRAM single bit correction event flag */
#define SYSCFG_STAT_ECCMEIF6                BIT(12)                  /*!< FLASH two bits no-correction event flag */
#define SYSCFG_STAT_ECCSEIF6                BIT(13)                  /*!< FLASH single bit correction event flag */
#define SYSCFG_STAT_CKMNMIIF                BIT(14)                  /*!< HXTAL clock moniotor NMI interrupt flag */

/* SYSCFG_SRAM0ECC bits definitions */
#define SYSCFG_SRAM0ECC_ECCMEIE0            BIT(0)                   /*!< SRAM0 two bits non-correction interrupt enable */
#define SYSCFG_SRAM0ECC_ECCSEIE0            BIT(1)                   /*!< SRAM0 single bit correction interrupt enable */
#define SYSCFG_SRAM0ECC_CKMNMIIE            BIT(2)                   /*!< HXTAL clock moniotor NMI interrupt enable */
#define SYSCFG_SRAM0ECC_ECCSERRBITS0        BITS(10,15)              /*!< indicates the error bit */
#define SYSCFG_SRAM0ECC_ECCEADDR0           BITS(16,31)              /*!< indicates the last address ECC event on SRAM0 occurred */
                                            
/* SYSCFG_SRAM1ECC bits definitions */      
#define SYSCFG_SRAM1ECC_ECCMEIE1            BIT(0)                   /*!< SRAM1 two bits non-correction interrupt enable */
#define SYSCFG_SRAM1ECC_ECCSEIE1            BIT(1)                   /*!< SRAM1 single bit correction interrupt enable */
#define SYSCFG_SRAM1ECC_ECCSERRBITS1        BITS(12,17)              /*!< indicates the error bit */
#define SYSCFG_SRAM1ECC_ECCEADDR1           BITS(18,31)              /*!< indicates the last address ECC event on SRAM1 occurred */
                                            
/* SYSCFG_SRAM2ECC bits definitions */      
#define SYSCFG_SRAM2ECC_ECCMEIE2            BIT(0)                   /*!< SRAM2 two bits non-correction interrupt enable */
#define SYSCFG_SRAM2ECC_ECCSEIE2            BIT(1)                   /*!< SRAM2 single bit correction interrupt enable */
#define SYSCFG_SRAM2ECC_ECCSERRBITS2        BITS(10,15)              /*!< indicates the error bit */
#define SYSCFG_SRAM2ECC_ECCEADDR2           BITS(16,31)              /*!< indicates the last address ECC event on SRAM2 occurred */

/* SYSCFG_ADDSRAMECC bits definitions */
#define SYSCFG_ADDSRAMECC_ECCMEIE3          BIT(0)                   /*!< ADDSRAM two bits non-correction interrupt enable */
#define SYSCFG_ADDSRAMECC_ECCSEIE3          BIT(1)                   /*!< ADDSRAM single bit correction interrupt enable */
#define SYSCFG_ADDSRAMECC_ECCSERRBITS3      BITS(8,13)               /*!< indicates the error bit */
#define SYSCFG_ADDSRAMECC_ECCEADDR3         BITS(14,31)              /*!< indicates the last address ECC event on ADDSRAM occurred */
                                                                
/* SYSCFG_TCMSRAMECC bits definitions */                        
#define SYSCFG_TCMSRAMECC_ECCMEIE4          BIT(0)                   /*!< TCMSRAM two bits non-correction interrupt enable */
#define SYSCFG_TCMSRAMECC_ECCSEIE4          BIT(1)                   /*!< TCMSRAM single bit correction interrupt enable */
#define SYSCFG_TCMSRAMECC_ECCSERRBITS4      BITS(12,17)              /*!< indicates the error bit */
#define SYSCFG_TCMSRAMECC_ECCEADDR4         BITS(18,31)              /*!< indicates the last address ECC event on TCMSRAM occurred */
                                                                
/* SYSCFG_BKPSRAMECC bits definitions */                        
#define SYSCFG_BKPSRAMECC_ECCMEIE5          BIT(0)                   /*!< BKPSRAM two bits non-correction interrupt enable */
#define SYSCFG_BKPSRAMECC_ECCSEIE5          BIT(1)                   /*!< BKPSRAM single bit correction interrupt enable */
#define SYSCFG_BKPSRAMECC_ECCSERRBITS5      BITS(16,21)              /*!< indicates the error bit */
#define SYSCFG_BKPSRAMECC_ECCEADDR5         BITS(22,31)              /*!< indicates the last address ECC event on BKPSRAM occurred */
                                                                
/* SYSCFG_FLASHECC_ADDR */                                      
#define SYSCFG_FLASHECC_ADDR_ECCEADDR6      BITS(0,31)               /*!< indicates the last address of ECC event on FLASH occurred */

/* SYSCFG_FLASHECC bits definitions */
#define SYSCFG_FLASHECC_ECCMEIE6            BIT(0)                   /*!< FLASH two bits non-correction interrupt enable */
#define SYSCFG_FLASHECC_ECCSEIE6            BIT(1)                   /*!< FLASH single bit correction interrupt enable */
#define SYSCFG_FLASHECC_ECCSERRBITS6        BITS(2,7)                /*!< indicates the error bit */

/* USER_CFG bits definitions */
#define USER_CFG_ANA_VERSION                BITS(24,31)              /*!< analog version information */

/* constants definitions */
/* boot mode definitions */
#define SYSCFG_BOOTMODE_FLASH               ((uint8_t)0x00U)         /*!< main flash memory remap */
#define SYSCFG_BOOTMODE_BOOTLOADER          ((uint8_t)0x01U)         /*!< boot loader remap */
#define SYSCFG_BOOTMODE_SRAM                ((uint8_t)0x03U)         /*!< SRAM0 of on-chip SRAM remap */
#define SYSCFG_BOOTMODE_OTP                 ((uint8_t)0x05U)         /*!< OTP remap */

/* FMC swap definitions */
#define SYSCFG_FMC_SWP_BANK0                ((uint32_t)0x00000000U)  /*!< main flash Bank 0 is mapped at address 0x08000000 */
#define SYSCFG_FMC_SWP_BANK1                ((uint32_t)0x00000100U)  /*!< main flash Bank 1 is mapped at address 0x08000000 */

/* EXMC swap enable/disable */
#define SYSCFG_EXMC_SWP_ENABLE              ((uint32_t)0x00000400U)  /*!< SDRAM bank 0 and bank 1 are swapped with NAND bank 1 and PC card */
#define SYSCFG_EXMC_SWP_DISABLE             ((uint32_t)0x00000000U)  /*!< no memory mapping swap */

/* EXTI source select definition */
#define EXTISS0                             ((uint8_t)0x00U)         /*!< EXTI source select GPIOx pin 0~3 */
#define EXTISS1                             ((uint8_t)0x01U)         /*!< EXTI source select GPIOx pin 4~7 */
#define EXTISS2                             ((uint8_t)0x02U)         /*!< EXTI source select GPIOx pin 8~11 */
#define EXTISS3                             ((uint8_t)0x03U)         /*!< EXTI source select GPIOx pin 12~15 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                        BITS(0,3)                /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                       ((uint8_t)(0x04U))       /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                  (EXTI_SS_JSTEP*((pin)%EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                   ((uint8_t)0x00U)          /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                   ((uint8_t)0x01U)          /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                   ((uint8_t)0x02U)          /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                   ((uint8_t)0x03U)          /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOE                   ((uint8_t)0x04U)          /*!< EXTI GPIOE configuration */
#define EXTI_SOURCE_GPIOF                   ((uint8_t)0x05U)          /*!< EXTI GPIOF configuration */
#define EXTI_SOURCE_GPIOG                   ((uint8_t)0x06U)          /*!< EXTI GPIOG configuration */
#define EXTI_SOURCE_GPIOH                   ((uint8_t)0x07U)          /*!< EXTI GPIOH configuration */
#define EXTI_SOURCE_GPIOI                   ((uint8_t)0x08U)          /*!< EXTI GPIOI configuration */

/* EXTI source pin definitions */
#define EXTI_SOURCE_PIN0                    ((uint8_t)0x00U)          /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                    ((uint8_t)0x01U)          /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                    ((uint8_t)0x02U)          /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                    ((uint8_t)0x03U)          /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                    ((uint8_t)0x04U)          /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                    ((uint8_t)0x05U)          /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                    ((uint8_t)0x06U)          /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                    ((uint8_t)0x07U)          /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                    ((uint8_t)0x08U)          /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                    ((uint8_t)0x09U)          /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                   ((uint8_t)0x0AU)          /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                   ((uint8_t)0x0BU)          /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                   ((uint8_t)0x0CU)          /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                   ((uint8_t)0x0DU)          /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                   ((uint8_t)0x0EU)          /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                   ((uint8_t)0x0FU)          /*!< EXTI GPIO pin15 configuration */

/* ethernet PHY selection */
#define SYSCFG_ENET_PHY_MII                 ((uint32_t)0x00000000U)   /*!< MII is selected for the Ethernet MAC */
#define SYSCFG_ENET_PHY_RMII                ((uint32_t)0x00800000U)   /*!< RMII is selected for the Ethernet MAC */

/* I/O compensation cell enable/disable */
#define SYSCFG_COMPENSATION_ENABLE          ((uint32_t)0x00000001U)   /*!< I/O compensation cell enable */
#define SYSCFG_COMPENSATION_DISABLE         ((uint32_t)0x00000000U)   /*!< I/O compensation cell disable */

/* define ECC type */
typedef enum
{
    SYSCFG_SRAM0_ECC = 0,                                             /*!< SRAM0 ECC event */
    SYSCFG_SRAM1_ECC,                                                 /*!< SRAM1 ECC event */
    SYSCFG_SRAM2_ECC,                                                 /*!< SRAM2 ECC event */
    SYSCFG_ADDSRAM_ECC,                                               /*!< ADDSRAM ECC event */
    SYSCFG_TCMSRAM_ECC,                                               /*!< TCMSRAM ECC event */
    SYSCFG_BKPSRAM_ECC,                                               /*!< BKPSRAM ECC event */
    SYSCFG_FLASH_ECC                                                  /*!< FLASH ECC event */
} syscfg_ecc_enum;

/* define the EXTI bit position and its register group index offset */
#define SYSCFG_REGIDX_BIT(regidx, bitpos)   (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define SYSCFG_REG_VAL(offset)              (REG32(SYSCFG + ((uint32_t)(offset) >> 6U)))
#define SYSCFG_BIT_POS(val)                 ((uint32_t)(val) & 0x0000001FU)
                                            
/* register offset */                       
#define SRAM0ECC_REG_OFFSET                 ((uint32_t)0x00000028U)   /*!< SRAM0ECC register offset */
#define SRAM1ECC_REG_OFFSET                 ((uint32_t)0x0000002CU)   /*!< SRAM1ECC register offset */
#define SRAM2ECC_REG_OFFSET                 ((uint32_t)0x00000030U)   /*!< SRAM2ECC register offset */
#define ADDSRAMECC_REG_OFFSET               ((uint32_t)0x00000034U)   /*!< ADDSRAMECC register offset */
#define TCMSRAMECC_REG_OFFSET               ((uint32_t)0x00000038U)   /*!< TCMSRAMECC register offset */
#define BKPSRAMECC_REG_OFFSET               ((uint32_t)0x0000003CU)   /*!< BKPSRAMECC register offset */
#define FLASHECC_REG_OFFSET                 ((uint32_t)0x00000044U)   /*!< FLASHECC register offset */

/* SYSCFG interrupt enable or disable */
typedef enum
{
    SYSCFG_INT_ECCME0                       = SYSCFG_REGIDX_BIT(SRAM0ECC_REG_OFFSET, 0U),      /*!< SRAM0 two bits non-correction interrupt */
    SYSCFG_INT_ECCSE0                       = SYSCFG_REGIDX_BIT(SRAM0ECC_REG_OFFSET, 1U),      /*!< SRAM0 single bit correction interrupt */
    SYSCFG_INT_CKMNMI                       = SYSCFG_REGIDX_BIT(SRAM0ECC_REG_OFFSET, 2U),      /*!< HXTAL clock moniotor NMI interrupt */
    SYSCFG_INT_ECCME1                       = SYSCFG_REGIDX_BIT(SRAM1ECC_REG_OFFSET, 0U),      /*!< SRAM1 two bits non-correction interrupt */
    SYSCFG_INT_ECCSE1                       = SYSCFG_REGIDX_BIT(SRAM1ECC_REG_OFFSET, 1U),      /*!< SRAM1 single bit correction interrupt */
    SYSCFG_INT_ECCME2                       = SYSCFG_REGIDX_BIT(SRAM2ECC_REG_OFFSET, 0U),      /*!< SRAM2 two bits non-correction interrupt */
    SYSCFG_INT_ECCSE2                       = SYSCFG_REGIDX_BIT(SRAM2ECC_REG_OFFSET, 1U),      /*!< SRAM2 single bit correction interrupt */
    SYSCFG_INT_ECCME3                       = SYSCFG_REGIDX_BIT(ADDSRAMECC_REG_OFFSET, 0U),    /*!< ADDSRAM two bits non-correction interrupt */
    SYSCFG_INT_ECCSE3                       = SYSCFG_REGIDX_BIT(ADDSRAMECC_REG_OFFSET, 1U),    /*!< ADDSRAM single bit correction interrupt */
    SYSCFG_INT_ECCME4                       = SYSCFG_REGIDX_BIT(TCMSRAMECC_REG_OFFSET, 0U),    /*!< TCMSRAM two bits non-correction interrupt */
    SYSCFG_INT_ECCSE4                       = SYSCFG_REGIDX_BIT(TCMSRAMECC_REG_OFFSET, 1U),    /*!< TCMSRAM single bit correction interrupt */
    SYSCFG_INT_ECCME5                       = SYSCFG_REGIDX_BIT(BKPSRAMECC_REG_OFFSET, 0U),    /*!< BKPSRAM two bits non-correction interrupt */
    SYSCFG_INT_ECCSE5                       = SYSCFG_REGIDX_BIT(BKPSRAMECC_REG_OFFSET, 1U),    /*!< BKPSRAM single bit correction interrupt */
    SYSCFG_INT_ECCME6                       = SYSCFG_REGIDX_BIT(FLASHECC_REG_OFFSET, 0U),      /*!< FLASH two bits non-correction interrupt */
    SYSCFG_INT_ECCSE6                       = SYSCFG_REGIDX_BIT(FLASHECC_REG_OFFSET, 1U)       /*!< FLASH single bit correction interrupt */
} syscfg_interrupt_enum;

/* SYSCFG flags */
typedef enum
{
    SYSCFG_FLAG_ECCME0                      = SYSCFG_STAT_ECCMEIF0,   /*!< SRAM0 two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE0                      = SYSCFG_STAT_ECCSEIF0,   /*!< SRAM0 single bit correction event flag */
    SYSCFG_FLAG_ECCME1                      = SYSCFG_STAT_ECCMEIF1,   /*!< SRAM1 two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE1                      = SYSCFG_STAT_ECCSEIF1,   /*!< SRAM1 single bit correction event flag */
    SYSCFG_FLAG_ECCME2                      = SYSCFG_STAT_ECCMEIF2,   /*!< SRAM2 two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE2                      = SYSCFG_STAT_ECCSEIF2,   /*!< SRAM2 single bit correction event flag */
    SYSCFG_FLAG_ECCME3                      = SYSCFG_STAT_ECCMEIF3,   /*!< ADDSRAM two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE3                      = SYSCFG_STAT_ECCSEIF3,   /*!< ADDSRAM single bit correction event flag */
    SYSCFG_FLAG_ECCME4                      = SYSCFG_STAT_ECCMEIF4,   /*!< TCMSRAM two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE4                      = SYSCFG_STAT_ECCSEIF4,   /*!< TCMSRAM single bit correction event flag */
    SYSCFG_FLAG_ECCME5                      = SYSCFG_STAT_ECCMEIF5,   /*!< BKPSRAM two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE5                      = SYSCFG_STAT_ECCSEIF5,   /*!< BKPSRAM single bit correction event flag */
    SYSCFG_FLAG_ECCME6                      = SYSCFG_STAT_ECCMEIF6,   /*!< FLASH two bits non-correction event flag */
    SYSCFG_FLAG_ECCSE6                      = SYSCFG_STAT_ECCSEIF6,   /*!< FLASH single bit correction event flag */    
    SYSCFG_FLAG_CKMNMI                      = SYSCFG_STAT_CKMNMIIF    /*!< HXTAL clock moniotor NMI flag */    
} syscfg_flag_enum;

/* SYSCFG interrupt flags */
typedef enum
{
    SYSCFG_INT_FLAG_ECCME0                  = SYSCFG_STAT_ECCMEIF0,   /*!< SRAM0 two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE0                  = SYSCFG_STAT_ECCSEIF0,   /*!< SRAM0 single bit correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCME1                  = SYSCFG_STAT_ECCMEIF1,   /*!< SRAM1 two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE1                  = SYSCFG_STAT_ECCSEIF1,   /*!< SRAM1 single bit correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCME2                  = SYSCFG_STAT_ECCMEIF2,   /*!< SRAM2 two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE2                  = SYSCFG_STAT_ECCSEIF2,   /*!< SRAM2 single bit correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCME3                  = SYSCFG_STAT_ECCMEIF3,   /*!< ADDSRAM two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE3                  = SYSCFG_STAT_ECCSEIF3,   /*!< ADDSRAM single bit correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCME4                  = SYSCFG_STAT_ECCMEIF4,   /*!< TCMSRAM two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE4                  = SYSCFG_STAT_ECCSEIF4,   /*!< TCMSRAM single bit correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCME5                  = SYSCFG_STAT_ECCMEIF5,   /*!< BKPSRAM two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE5                  = SYSCFG_STAT_ECCSEIF5,   /*!< BKPSRAM single bit correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCME6                  = SYSCFG_STAT_ECCMEIF6,   /*!< FLASH two bits non-correction event interrupt flag */
    SYSCFG_INT_FLAG_ECCSE6                  = SYSCFG_STAT_ECCSEIF6,   /*!< FLASH single bit correction event interrupt flag */    
    SYSCFG_INT_FLAG_CKMNMI                  = SYSCFG_STAT_CKMNMIIF    /*!< HXTAL clock moniotor NMI interrupt flag */    
} syscfg_interrupt_flag_enum;

/* function declarations */
/* initialization functions */
/* deinit syscfg module */
void syscfg_deinit(void);

/* function configuration */
/* configure the boot mode */
void syscfg_bootmode_config(uint8_t syscfg_bootmode);
/* configure FMC memory mapping swap */
void syscfg_fmc_swap_config(uint32_t syscfg_fmc_swap);
/* configure the EXMC swap */
void syscfg_exmc_swap_config(uint32_t syscfg_exmc_swap); 
/* configure the GPIO pin as EXTI Line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);
/* configure the PHY interface for the ethernet MAC */
void syscfg_enet_phy_interface_config(uint32_t syscfg_enet_phy_interface);
/* configure the I/O compensation cell */
void syscfg_compensation_config(uint32_t syscfg_compensation);
/* get Compensation cell ready flag */
FlagStatus syscfg_cps_cell_ready_get(void);
/* get ecc err bits */
uint32_t syscfg_ecc_err_bits_get(syscfg_ecc_enum ecc_type);
/* get ecc address */
uint32_t syscfg_ecc_address_get(syscfg_ecc_enum ecc_type);

/* interrupt & flag functions */
/* get SYSCFG flag state */
FlagStatus syscfg_flag_get(syscfg_flag_enum flag);
/* clear SYSCFG flag state */
void syscfg_flag_clear(syscfg_flag_enum flag);
/* enable SYSCFG interrupt */
void syscfg_interrupt_enable(syscfg_interrupt_enum interrupt);
/* disable SYSCFG interrupt */
void syscfg_interrupt_disable(syscfg_interrupt_enum interrupt);
/* get SYSCFG interrupt flag state */
FlagStatus syscfg_interrupt_flag_get(syscfg_interrupt_flag_enum flag);
/* clear SYSCFG interrupt flag state */
void syscfg_interrupt_flag_clear(syscfg_interrupt_flag_enum flag);

#endif /* GD32F5XX_SYSCFG_H */
