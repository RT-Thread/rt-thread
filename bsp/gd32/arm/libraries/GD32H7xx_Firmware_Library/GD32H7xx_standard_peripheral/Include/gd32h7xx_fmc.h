/*!
    \file    gd32h7xx_fmc.h
    \brief   definitions for the FMC

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

#ifndef GD32H7XX_FMC_H
#define GD32H7XX_FMC_H

#include "gd32h7xx.h"

/* FMC definition */
#define FMC                               FMC_BASE                         /*!< FMC register base address */

/* registers definitions */
#define FMC_KEY                           REG32((FMC) + 0x00000004U)       /*!< FMC unlock key register */
#define FMC_OBKEY                         REG32((FMC) + 0x00000008U)       /*!< FMC option byte unlock key register */
#define FMC_CTL                           REG32((FMC) + 0x0000000CU)       /*!< FMC control register */
#define FMC_STAT                          REG32((FMC) + 0x00000010U)       /*!< FMC status register */
#define FMC_ADDR                          REG32((FMC) + 0x00000014U)       /*!< FMC address register */
#define FMC_OBCTL                         REG32((FMC) + 0x00000018U)       /*!< FMC option byte control register */
#define FMC_OBSTAT0_EFT                   REG32((FMC) + 0x0000001CU)       /*!< FMC effective option byte status 0 register */
#define FMC_OBSTAT0_MDF                   REG32((FMC) + 0x00000020U)       /*!< FMC modified option byte status 0 register */
#define FMC_DCRPADDR_EFT                  REG32((FMC) + 0x00000028U)       /*!< FMC effective DCRP address register */
#define FMC_DCRPADDR_MDF                  REG32((FMC) + 0x0000002CU)       /*!< FMC modified DCRP address register */
#define FMC_SCRADDR_EFT                   REG32((FMC) + 0x00000030U)       /*!< FMC effective secure address register */
#define FMC_SCRADDR_MDF                   REG32((FMC) + 0x00000034U)       /*!< FMC modified secure address register */
#define FMC_WP_EFT                        REG32((FMC) + 0x00000038U)       /*!< FMC effective erase/program protection register */
#define FMC_WP_MDF                        REG32((FMC) + 0x0000003CU)       /*!< FMC modified erase/program protection register */
#define FMC_BTADDR_EFT                    REG32((FMC) + 0x00000040U)       /*!< FMC effective boot address register */
#define FMC_BTADDR_MDF                    REG32((FMC) + 0x00000044U)       /*!< FMC modified boot address register */
#define FMC_OBSTAT1_EFT                   REG32((FMC) + 0x00000050U)       /*!< FMC effective option byte status 1 register */
#define FMC_OBSTAT1_MDF                   REG32((FMC) + 0x00000054U)       /*!< FMC modified option byte status 1 register */
#define FMC_NODEC                         REG32((FMC) + 0x00000060U)       /*!< FMC NO-RTDEC area register */
#define FMC_ECCADDR                       REG32((FMC) + 0x00000064U)       /*!< FMC ECC error address register */
#define FMC_AESIV0_EFT                    REG32((FMC) + 0x00000068U)       /*!< FMC effective AES IV 0 register */
#define FMC_AESIV1_EFT                    REG32((FMC) + 0x0000006CU)       /*!< FMC effective AES IV 1 register */
#define FMC_AESIV2_EFT                    REG32((FMC) + 0x00000070U)       /*!< FMC effective AES IV 2 register */
#define FMC_AESIV0_MDF                    REG32((FMC) + 0x00000074U)       /*!< FMC modified AES IV 0 register */
#define FMC_AESIV1_MDF                    REG32((FMC) + 0x00000078U)       /*!< FMC modified AES IV 1 register */
#define FMC_AESIV2_MDF                    REG32((FMC) + 0x0000007CU)       /*!< FMC modified AES IV 2 register */
#define FMC_PID0                          REG32((FMC) + 0x00000100U)       /*!< FMC product ID register 0 */
#define FMC_PID1                          REG32((FMC) + 0x00000104U)       /*!< FMC product ID register 1 */

/* bits definitions */
/* FMC_KEY */
#define FMC_KEY_KEY                       BITS(0,31)                       /*!< FMC_CTL unlock key bits */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY                   BITS(0,31)                       /*!< option byte unlock key bits */

/* FMC_CTL */
#define FMC_CTL_LK                        BIT(0)                           /*!< FMC_CTL lock bit */
#define FMC_CTL_PG                        BIT(1)                           /*!< main flash program command bit */
#define FMC_CTL_SER                       BIT(2)                           /*!< main flash sector erase command bit */
#define FMC_CTL_MER                       BIT(3)                           /*!< main flash mass erase command bit */
#define FMC_CTL_PGCHEN                    BIT(4)                           /*!< check programming area enable bit */
#define FMC_CTL_START                     BIT(7)                           /*!< send erase command to FMC bit */
#define FMC_CTL_ENDIE                     BIT(16)                          /*!< end of operation interrupt enable bit */
#define FMC_CTL_WPERRIE                   BIT(17)                          /*!< erase/program protection error interrupt enable bit */
#define FMC_CTL_PGSERRIE                  BIT(18)                          /*!< program sequence error interrupt enable bit */
#define FMC_CTL_RPERRIE                   BIT(23)                          /*!< read protection error interrupt enable bit */
#define FMC_CTL_RSERRIE                   BIT(24)                          /*!< read secure error interrupt enable bit */
#define FMC_CTL_ECCCORIE                  BIT(25)                          /*!< one bit correct error interrupt enable bit */
#define FMC_CTL_ECCDETIE                  BIT(26)                          /*!< two bits detect error interrupt enable bit */

/* FMC_STAT */
#define FMC_STAT_BUSY                     BIT(0)                           /*!< flash busy flag bit */
#define FMC_STAT_ENDF                     BIT(16)                          /*!< end of operation flag bit */
#define FMC_STAT_WPERR                    BIT(17)                          /*!< erase/program protection error flag bit */
#define FMC_STAT_PGSERR                   BIT(18)                          /*!< program sequence error flag bit */
#define FMC_STAT_RPERR                    BIT(23)                          /*!< read protection error flag bit */
#define FMC_STAT_RSERR                    BIT(24)                          /*!< read secure error flag bit */
#define FMC_STAT_ECCCOR                   BIT(25)                          /*!< one bit correct error flag bit */
#define FMC_STAT_ECCDET                   BIT(26)                          /*!< two bits detect error flag bit */
#define FMC_STAT_OBMERR                   BIT(30)                          /*!< option byte modify error flag */
#define FMC_STAT_FECCF                    BIT(31)                          /*!< flash ECC function flag */

/* FMC_ADDR */
#define FMC_ADDR_ADDR                     BITS(0,31)                       /*!< address of flash to be erased */

/* FMC_OBCTL */
#define FMC_OBCTL_OBLK                    BIT(0)                           /*!< FMC_OBCTL lock bit */
#define FMC_OBCTL_OBSTART                 BIT(1)                           /*!< send option bytes modification start command to FMC */
#define FMC_OBCTL_OBMERRIE                BIT(30)                          /*!< option byte modify error interrupt enable bit */

/* FMC_OBSTAT0_EFT */
#define FMC_OBSTAT0_EFT_BOR_TH            BITS(2,3)                        /*!< effective option byte brownout reset threshold value */
#define FMC_OBSTAT0_EFT_NWDG_HW           BIT(4)                           /*!< effective option byte watchdog value */
#define FMC_OBSTAT0_EFT_NRST_DPSLP        BIT(6)                           /*!< effective option byte deepsleep reset value */
#define FMC_OBSTAT0_EFT_NRST_STDBY        BIT(7)                           /*!< effective option byte standby reset value */
#define FMC_OBSTAT0_EFT_SPC               BITS(8,15)                       /*!< effective option byte security protection code */
#define FMC_OBSTAT0_EFT_FWDGSPD_DPSLP     BIT(17)                          /*!< effective option byte watchdog suspend status in deepsleep mode */
#define FMC_OBSTAT0_EFT_FWDGSPD_STDBY     BIT(18)                          /*!< effective option byte watchdog suspend status in standby mode */
#define FMC_OBSTAT0_EFT_SCR               BIT(21)                          /*!< effective option byte security access mode status bit */
#define FMC_OBSTAT0_EFT_ITCMECCEN         BIT(22)                          /*!< effective option byte ITCM ECC function enable status bit */
#define FMC_OBSTAT0_EFT_DTCM0ECCEN        BIT(23)                          /*!< effective option byte DTCM0 ECC function enable status bit */
#define FMC_OBSTAT0_EFT_DTCM1ECCEN        BIT(24)                          /*!< effective option byte DTCM1 ECC function enable status bit */
#define FMC_OBSTAT0_EFT_IOSPDOPEN         BIT(29)                          /*!< effective option byte I/O speed optimization, high-speed at low-voltage enable status bit */

/* FMC_OBSTAT0_MDF */
#define FMC_OBSTAT0_MDF_BOR_TH            BITS(2,3)                        /*!< modified option byte brownout reset threshold value */
#define FMC_OBSTAT0_MDF_NWDG_HW           BIT(4)                           /*!< modified option byte watchdog value */
#define FMC_OBSTAT0_MDF_NRST_DPSLP        BIT(6)                           /*!< modified option byte deepsleep reset value */
#define FMC_OBSTAT0_MDF_NRST_STDBY        BIT(7)                           /*!< modified option byte standby reset value */
#define FMC_OBSTAT0_MDF_SPC               BITS(8,15)                       /*!< modified option byte security protection code */
#define FMC_OBSTAT0_MDF_FWDGSPD_DPSLP     BIT(17)                          /*!< modified option byte watchdog suspend status in deepsleep mode */
#define FMC_OBSTAT0_MDF_FWDGSPD_STDBY     BIT(18)                          /*!< modified option byte watchdog suspend status in standby mode */
#define FMC_OBSTAT0_MDF_SCR               BIT(21)                          /*!< modified option byte security access mode status bit */
#define FMC_OBSTAT0_MDF_ITCMECCEN         BIT(22)                          /*!< modified option byte ITCM ECC function enable status bit */
#define FMC_OBSTAT0_MDF_DTCM0ECCEN        BIT(23)                          /*!< modified option byte DTCM0 ECC function enable status bit */
#define FMC_OBSTAT0_MDF_DTCM1ECCEN        BIT(24)                          /*!< modified option byte DTCM1 ECC function enable status bit */
#define FMC_OBSTAT0_MDF_IOSPDOPEN         BIT(29)                          /*!< modified option byte I/O speed optimization, high-speed at low-voltage enable status bit */

/* FMC_DCRPADDR_EFT */
#define FMC_DCRPADDR_EFT_DCRP_AREA_START  BITS(0,10)                       /*!< effective option byte DCRP area start status bits */
#define FMC_DCRPADDR_EFT_DCRP_AREA_END    BITS(16,26)                      /*!< effective option byte DCRP area end status bits */
#define FMC_DCRPADDR_EFT_DCRP_EREN        BIT(31)                          /*!< effective option byte DCRP area erase enable bit */

/* FMC_DCRPADDR_MDF */
#define FMC_DCRPADDR_MDF_DCRP_AREA_START  BITS(0,10)                       /*!< modified option byte DCRP area start status bits */
#define FMC_DCRPADDR_MDF_DCRP_AREA_END    BITS(16,26)                      /*!< modified option byte DCRP area end status bits */
#define FMC_DCRPADDR_MDF_DCRP_EREN        BIT(31)                          /*!< modified option byte DCRP area erase enable bit */

/* FMC_SCRADDR_EFT */
#define FMC_SCRADDR_EFT_SCR_AREA_START    BITS(0,10)                       /*!< effective option byte secure-access area start status bits */
#define FMC_SCRADDR_EFT_SCR_AREA_END      BITS(16,26)                      /*!< effective option byte secure-access area end status bits */
#define FMC_SCRADDR_EFT_SCR_EREN          BIT(31)                          /*!< effective option byte secure-access area erase enable bit */

/* FMC_SCRADDR_MDF */
#define FMC_SCRADDR_MDF_SCR_AREA_START    BITS(0,10)                       /*!< modified option byte secure-access area start status bits */
#define FMC_SCRADDR_MDF_SCR_AREA_END      BITS(16,26)                      /*!< modified option byte secure-access area end status bits */
#define FMC_SCRADDR_MDF_SCR_EREN          BIT(31)                          /*!< modified option byte secure-access area erase enable bit */

/* FMC_WP_EFT */
#define FMC_WP_EFT_WP                     BITS(0,29)                       /*!< effective option byte erase/program protection status bits */

/* FMC_WP_MDF */
#define FMC_WP_MDF_WP                     BITS(0,29)                       /*!< modified option byte erase/program protection status bits */

/* FMC_BTADDR_EFT */
#define FMC_BTADDR_EFT_BOOT_ADDR0         BITS(0,15)                       /*!< effective option byte boot address 0 */
#define FMC_BTADDR_EFT_BOOT_ADDR1         BITS(16,31)                      /*!< effective option byte boot address 1 */

/* FMC_BTADDR_MDF */
#define FMC_BTADDR_MDF_BOOT_ADDR0         BITS(0,15)                       /*!< modified option byte boot address 0 */
#define FMC_BTADDR_MDF_BOOT_ADDR1         BITS(16,31)                      /*!< modified option byte boot address 1 */

/* FMC_OBSTAT1_EFT */
#define FMC_OBSTAT1_EFT_ITCM_SZ_SHRRAM    BITS(0,3)                        /*!< effective option byte ITCM size of shared RAM */
#define FMC_OBSTAT1_EFT_DTCM_SZ_SHRRAM    BITS(4,7)                        /*!< effective option byte DTCM size of shared RAM */
#define FMC_OBSTAT1_EFT_DATA              BITS(16,31)                      /*!< effective option byte user data value */

/* FMC_OBSTAT1_MDF */
#define FMC_OBSTAT1_MDF_ITCM_SZ_SHRRAM    BITS(0,3)                        /*!< modified option byte ITCM size of shared RAM */
#define FMC_OBSTAT1_MDF_DTCM_SZ_SHRRAM    BITS(4,7)                        /*!< modified option byte DTCM size of shared RAM */
#define FMC_OBSTAT1_MDF_DATA              BITS(16,31)                      /*!< modified option byte user data value */

/* FMC_NODEC */
#define FMC_NODEC_NODEC_AREA_START        BITS(0,10)                       /*!< NO-RTDEC area start status bits */
#define FMC_NODEC_NODEC_AREA_END          BITS(16,26)                      /*!< NO-RTDEC area end status bits */

/* FMC_ECCADDR */
#define FMC_ECCADDR_ECCADDR               BITS(0,31)                       /*!< address of byte where an ECC error is detected */

/* FMC_AESIV0_EFT */
#define FMC_AESIV0_EFT_AESIV              BITS(0,31)                       /*!< AES initialization vector status value 0 */

/* FMC_AESIV1_EFT */
#define FMC_AESIV1_EFT_AESIV              BITS(0,31)                       /*!< AES initialization vector status value 1 */

/* FMC_AESIV2_EFT */
#define FMC_AESIV2_EFT_AESIV              BITS(0,31)                       /*!< AES initialization vector status value 2 */

/* FMC_AESIV0_MDF */
#define FMC_AESIV0_MDF_AESIV              BITS(0,31)                       /*!< AES initialization vector configuration value 0 */

/* FMC_AESIV1_MDF */
#define FMC_AESIV1_MDF_AESIV              BITS(0,31)                       /*!< AES initialization vector configuration value 1 */

/* FMC_AESIV2_MDF */
#define FMC_AESIV2_MDF_AESIV              BITS(0,31)                       /*!< AES initialization vector configuration value 2 */

/* FMC_PID0 */
#define FMC_PID0_PID                      BITS(0,31)                       /*!< product ID 0 */

/* FMC_PID1 */
#define FMC_PID1_PID                      BITS(0,31)                       /*!< product ID 1 */

/* constants definitions */
/* FMC state */
typedef enum {
    FMC_READY = 0U,                                                        /*!< the operation has been completed */
    FMC_BUSY,                                                              /*!< the operation is in progress */
    FMC_WPERR,                                                             /*!< erase/program protection error */
    FMC_PGSERR,                                                            /*!< program sequence error */
    FMC_RPERR,                                                             /*!< read protection error */
    FMC_RSERR,                                                             /*!< read secure error */
    FMC_ECCCOR,                                                            /*!< one bit correct error */
    FMC_ECCDET,                                                            /*!< two bits detect error */
    FMC_OBMERR,                                                            /*!< option byte modify error */
    FMC_TOERR                                                              /*!< timeout error */
} fmc_state_enum;

/* define the FMC bit position and its register index offset */
#define FMC_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define FMC_REG_VAL(offset)             (REG32(FMC + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define FMC_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define FMC_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                            | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define FMC_REG_VAL2(offset)            (REG32(FMC + ((uint32_t)(offset) >> 22)))
#define FMC_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define FMC_STAT_REG_OFFSET             ((uint32_t)0x00000010U)            /*!< STAT register offset */
#define FMC_CTL_REG_OFFSET              ((uint32_t)0x0000000CU)            /*!< CTL register offset */
#define FMC_OBCTL_REG_OFFSET            ((uint32_t)0x00000018U)            /*!< OBCTL register offset */

/* FMC flags */
typedef enum {
    /* flags in STAT register */
    FMC_FLAG_BUSY = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 0U),               /*!< flash busy flag */
    FMC_FLAG_END = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 16U),               /*!< flash end of operation flag */
    FMC_FLAG_WPERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 17U),             /*!< flash erase/program protection error flag */
    FMC_FLAG_PGSERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 18U),            /*!< flash program sequence error flag */
    FMC_FLAG_RPERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 23U),             /*!< flash read protection error flag */
    FMC_FLAG_RSERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 24U),             /*!< flash read secure error flag */
    FMC_FLAG_ECCCOR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 25U),            /*!< flash one bit correct error flag */
    FMC_FLAG_ECCDET = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 26U),            /*!< flash two bits detect error flag */
    FMC_FLAG_OBMERR = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 30U),            /*!< option byte modify error flag */
    FMC_FLAG_FECC = FMC_REGIDX_BIT(FMC_STAT_REG_OFFSET, 31U)               /*!< flash ECC function flag */
} fmc_flag_enum;

/* FMC interrupt flags */
typedef enum {
    /* interrupt flags in STAT register */
    FMC_INT_FLAG_END = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 16U, FMC_STAT_REG_OFFSET, 16U),                 /*!< flash end of operation interrupt flag */
    FMC_INT_FLAG_WPERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 17U, FMC_STAT_REG_OFFSET, 17U),               /*!< flash erase/program protection error interrupt flag */
    FMC_INT_FLAG_PGSERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 18U, FMC_STAT_REG_OFFSET, 18U),              /*!< flash program sequence error interrupt flag */
    FMC_INT_FLAG_RPERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 23U, FMC_STAT_REG_OFFSET, 23U),               /*!< flash read protection error interrupt flag */
    FMC_INT_FLAG_RSERR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 24U, FMC_STAT_REG_OFFSET, 24U),               /*!< flash read secure error interrupt flag */
    FMC_INT_FLAG_ECCCOR = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 25U, FMC_STAT_REG_OFFSET, 25U),              /*!< flash one bit error detected and correct interrupt flag */
    FMC_INT_FLAG_ECCDET = FMC_REGIDX_BIT2(FMC_CTL_REG_OFFSET, 26U, FMC_STAT_REG_OFFSET, 26U),              /*!< flash two bit errors detect interrupt flag */
    FMC_INT_FLAG_OBMERR = FMC_REGIDX_BIT2(FMC_OBCTL_REG_OFFSET, 30U, FMC_STAT_REG_OFFSET, 30U)             /*!< option byte modify error flag */
} fmc_interrupt_flag_enum;

/* FMC interrupt */
typedef enum {
    /* interrupt in CTL register */
    FMC_INT_END = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 16U),                 /*!< FMC end of operation interrupt */
    FMC_INT_WPERR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 17U),               /*!< FMC erase/program protection error interrupt */
    FMC_INT_PGSERR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 18U),              /*!< FMC program sequence error interrupt */
    FMC_INT_RPERR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 23U),               /*!< FMC read protection error interrupt */
    FMC_INT_RSERR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 24U),               /*!< FMC read secure error interrupt */
    FMC_INT_ECCCOR = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 25U),              /*!< FMC one bit correct error interrupt */
    FMC_INT_ECCDET = FMC_REGIDX_BIT(FMC_CTL_REG_OFFSET, 26U),              /*!< FMC two bits detect error interrupt */
    /* interrupt in OBCTL register */
    FMC_INT_OBMERR = FMC_REGIDX_BIT(FMC_OBCTL_REG_OFFSET, 30U)             /*!< FMC option byte modify error interrupt */
} fmc_interrupt_enum;

/* unlock key */
#define UNLOCK_KEY0                       ((uint32_t)0x45670123U)          /*!< unlock key 0 */
#define UNLOCK_KEY1                       ((uint32_t)0xCDEF89ABU)          /*!< unlock key 1 */

/* option byte unlock key */
#define OB_UNLOCK_KEY0                    ((uint32_t)0x08192A3BU)          /*!< option byte unlock key 0 */
#define OB_UNLOCK_KEY1                    ((uint32_t)0x4C5D6E7FU)          /*!< option byte unlock key 1 */

/* option byte BOR threshold value */
#define OBSTAT0_BOR_TH(regval)            (BITS(2,3) & ((uint32_t)(regval) << 2U))
#define OB_BOR_TH_OFF                     OBSTAT0_BOR_TH(0)                /*!< no BOR function */
#define OB_BOR_TH_VALUE1                  OBSTAT0_BOR_TH(1)                /*!< BOR threshold value 1 */
#define OB_BOR_TH_VALUE2                  OBSTAT0_BOR_TH(2)                /*!< BOR threshold value 2 */
#define OB_BOR_TH_VALUE3                  OBSTAT0_BOR_TH(3)                /*!< BOR threshold value 3 */

/* option byte software/hardware free watchdog timer */
#define OBSTAT0_NWDG_HW(regval)           (BIT(4) & ((uint32_t)(regval) << 4U))
#define OB_FWDGT_HW                       OBSTAT0_NWDG_HW(0)               /*!< hardware free watchdog */
#define OB_FWDGT_SW                       OBSTAT0_NWDG_HW(1)               /*!< software free watchdog */

/* option byte reset or not entering deep sleep mode */
#define OBSTAT0_NRST_DPSLP(regval)        (BIT(6) & ((uint32_t)(regval) << 6U))
#define OB_DEEPSLEEP_RST                  OBSTAT0_NRST_DPSLP(0)            /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST                 OBSTAT0_NRST_DPSLP(1)            /*!< no reset when entering deepsleep mode */

/* option byte reset or not entering standby mode */
#define OBSTAT0_NRST_STDBY(regval)        (BIT(7) & ((uint32_t)(regval) << 7U))
#define OB_STDBY_RST                      OBSTAT0_NRST_STDBY(0)            /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST                     OBSTAT0_NRST_STDBY(1)            /*!< no reset when entering standby mode */

/* option byte FWDGT status in deep-sleep mode */
#define OBSTAT0_FWDGSPD_DPSLP(regval)     (BIT(17) & ((uint32_t)(regval)<< 17U))
#define OB_DPSLP_FWDGT_SUSPEND            OBSTAT0_FWDGSPD_DPSLP(0)         /*!< free watchdog is suspended in deepsleep mode */
#define OB_DPSLP_FWDGT_RUN                OBSTAT0_FWDGSPD_DPSLP(1)         /*!< free watchdog is running in deepsleep mode */

/* option byte FWDGT status in standby mode */
#define OBSTAT0_FWDGSPD_STDBY(regval)     (BIT(18) & ((uint32_t)(regval) << 18U))
#define OB_STDBY_FWDGT_SUSPEND            OBSTAT0_FWDGSPD_STDBY(0)         /*!< free watchdog is suspended in standby mode */
#define OB_STDBY_FWDGT_RUN                OBSTAT0_FWDGSPD_STDBY(1)         /*!< free watchdog is running in standby mode */

/* option byte security access mode configuration */
#define OBSTAT0_SCR(regval)               (BIT(21) & ((uint32_t)(regval) << 21U))
#define OB_SECURE_MODE_DISABLE            OBSTAT0_SCR(0)                   /*!< secure access mode disable */
#define OB_SECURE_MODE_ENABLE             OBSTAT0_SCR(1)                   /*!< secure access mode enable */

/* option byte ITCM ECC function enable configuration */
#define OBSTAT0_ITCMECCEN(regval)         (BIT(22) & ((uint32_t)(regval) << 22U))
#define OB_ITCMECCEN_DISABLE              OBSTAT0_ITCMECCEN(0)             /*!< ITCM ECC function disable */
#define OB_ITCMECCEN_ENABLE               OBSTAT0_ITCMECCEN(1)             /*!< ITCM ECC function enable */

/* option byte DTCM0 ECC function enable configuration */
#define OBSTAT0_DTCM0ECCEN(regval)        (BIT(23) & ((uint32_t)(regval) << 23U))
#define OB_DTCM0ECCEN_DISABLE             OBSTAT0_DTCM0ECCEN(0)            /*!< DTCM0 ECC function disable */
#define OB_DTCM0ECCEN_ENABLE              OBSTAT0_DTCM0ECCEN(1)            /*!< DTCM0 ECC function enable */

/* option byte DTCM1 ECC function enable configuration */
#define OBSTAT0_DTCM1ECCEN(regval)        (BIT(24) & ((uint32_t)(regval) << 24U))
#define OB_DTCM1ECCEN_DISABLE             OBSTAT0_DTCM1ECCEN(0)            /*!< DTCM1 ECC function disable */
#define OB_DTCM1ECCEN_ENABLE              OBSTAT0_DTCM1ECCEN(1)            /*!< DTCM1 ECC function enable */

/* option byte I/O speed optimization configuration */
#define OBSTAT0_IOSPDOPEN(regval)         (BIT(29) & ((uint32_t)(regval) << 29U))
#define OB_IOSPDOPEN_DISABLE              OBSTAT0_IOSPDOPEN(0)             /*!< I/O speed optimization, high-speed at low-voltage diable */
#define OB_IOSPDOPEN_ENABLE               OBSTAT0_IOSPDOPEN(1)             /*!< I/O speed optimization, high-speed at low-voltage enable */

/* option byte security protection configuration */
#define FMC_NSPC                          ((uint8_t)0xAAU)                 /*!< no protection */
#define FMC_LSPC                          ((uint8_t)0xBBU)                 /*!< protection level low */
#define FMC_HSPC                          ((uint8_t)0xCCU)                 /*!< protection level high */

/* option byte DCRP erase enable configuration */
#define OB_DCRPADDR_DCRP_EREN(regval)     (BIT(31) & ((uint32_t)(regval) << 31U))
#define OB_DCRP_AREA_ERASE_DISABLE        OB_DCRPADDR_DCRP_EREN(0)         /*!< DCRP area erase disable */
#define OB_DCRP_AREA_ERASE_ENABLE         OB_DCRPADDR_DCRP_EREN(1)         /*!< DCRP area erase enable */

/* option byte secure-access erase enable configuration */
#define OB_SCRADDR_SCR_EREN(regval)       (BIT(31) & ((uint32_t)(regval) << 31U))
#define OB_SCR_AREA_ERASE_DISABLE         OB_SCRADDR_SCR_EREN(0)           /*!< secure-access area erase disable */
#define OB_SCR_AREA_ERASE_ENABLE          OB_SCRADDR_SCR_EREN(1)           /*!< secure-access area erase enable */

/* option byte erase/program protection */
#define OB_WP_0                           BIT(0)                           /*!< erase/program protection of sector 0~15 */
#define OB_WP_1                           BIT(1)                           /*!< erase/program protection of sector 16~31 */
#define OB_WP_2                           BIT(2)                           /*!< erase/program protection of sector 32~47 */
#define OB_WP_3                           BIT(3)                           /*!< erase/program protection of sector 48~63 */
#define OB_WP_4                           BIT(4)                           /*!< erase/program protection of sector 64~79 */
#define OB_WP_5                           BIT(5)                           /*!< erase/program protection of sector 80~95 */
#define OB_WP_6                           BIT(6)                           /*!< erase/program protection of sector 96~111 */
#define OB_WP_7                           BIT(7)                           /*!< erase/program protection of sector 112~127 */
#define OB_WP_8                           BIT(8)                           /*!< erase/program protection of sector 128~143 */
#define OB_WP_9                           BIT(9)                           /*!< erase/program protection of sector 144~159 */
#define OB_WP_10                          BIT(10)                          /*!< erase/program protection of sector 160~175 */
#define OB_WP_11                          BIT(11)                          /*!< erase/program protection of sector 176~191 */
#define OB_WP_12                          BIT(12)                          /*!< erase/program protection of sector 192~207 */
#define OB_WP_13                          BIT(13)                          /*!< erase/program protection of sector 208~223 */
#define OB_WP_14                          BIT(14)                          /*!< erase/program protection of sector 224~239 */
#define OB_WP_15                          BIT(15)                          /*!< erase/program protection of sector 240~255 */
#define OB_WP_16                          BIT(16)                          /*!< erase/program protection of sector 256~383 */
#define OB_WP_17                          BIT(17)                          /*!< erase/program protection of sector 384~511 */
#define OB_WP_18                          BIT(18)                          /*!< erase/program protection of sector 512~639 */
#define OB_WP_19                          BIT(19)                          /*!< erase/program protection of sector 640~767 */
#define OB_WP_20                          BIT(20)                          /*!< erase/program protection of sector 768~895 */
#define OB_WP_21                          BIT(21)                          /*!< erase/program protection of sector 896~1023 */
#define OB_WP_ALL                         BITS(0,29)                       /*!< erase/program protection of all sectors */

/* option byte DTCM size of shared RAM */
#define OBSTAT1_DTCM_SZ_SHRRAM(regval)    (BITS(4,7) & ((uint32_t)(regval) << 4U))
#define OB_DTCM_SHARED_RAM_0KB            OBSTAT1_DTCM_SZ_SHRRAM(0)        /*!< DTCM shared RAM size is 0KB */
#define OB_DTCM_SHARED_RAM_64KB           OBSTAT1_DTCM_SZ_SHRRAM(7)        /*!< DTCM shared RAM size is 64KB */
#define OB_DTCM_SHARED_RAM_128KB          OBSTAT1_DTCM_SZ_SHRRAM(8)        /*!< DTCM shared RAM size is 128KB */
#define OB_DTCM_SHARED_RAM_256KB          OBSTAT1_DTCM_SZ_SHRRAM(9)        /*!< DTCM shared RAM size is 256KB */
#define OB_DTCM_SHARED_RAM_512KB          OBSTAT1_DTCM_SZ_SHRRAM(10)       /*!< DTCM shared RAM size is 512KB */

/* option byte ITCM size of shared RAM */
#define OBSTAT1_ITCM_SZ_SHRRAM(regval)    (BITS(0,3) & ((uint32_t)(regval)))
#define OB_ITCM_SHARED_RAM_0KB            OBSTAT1_ITCM_SZ_SHRRAM(0)        /*!< ITCM shared RAM size is 0KB */
#define OB_ITCM_SHARED_RAM_64KB           OBSTAT1_ITCM_SZ_SHRRAM(7)        /*!< ITCM shared RAM size is 64KB */
#define OB_ITCM_SHARED_RAM_128KB          OBSTAT1_ITCM_SZ_SHRRAM(8)        /*!< ITCM shared RAM size is 128KB */
#define OB_ITCM_SHARED_RAM_256KB          OBSTAT1_ITCM_SZ_SHRRAM(9)        /*!< ITCM shared RAM size is 256KB */
#define OB_ITCM_SHARED_RAM_512KB          OBSTAT1_ITCM_SZ_SHRRAM(10)       /*!< ITCM shared RAM size is 512KB */

/* boot pin value definitions */
#define BOOT_PIN_0                        ((uint8_t)0x00U)              /*!< boot pin value is 0 */
#define BOOT_PIN_1                        ((uint8_t)0x01U)              /*!< boot pin value is 1 */

#define MAIN_FLASH_BASE_ADDRESS           ((uint32_t)0x08000000U)          /*!< main flash base address */
#define SCR_SIZE_UNIT                     ((uint32_t)0x00001000U)          /*!< secure-access area granularity */
#define DCRP_SIZE_UNIT                    ((uint32_t)0x00001000U)          /*!< DCRP area granularity */
#define FMC_TIMEOUT_COUNT                 ((uint32_t)0xFFFFFFFFU)          /*!< count to judge of FMC timeout */

#define INVLD_AREA_ADDRESS                ((uint8_t)0x00U)                 /*!< the area address is invalid */
#define VLD_AREA_ADDRESS                  ((uint8_t)0x01U)                 /*!< the area address is valid */

/* function declarations */
/* FMC operation functions */
/* unlock FMC_CTL register */
void fmc_unlock(void);
/* lock FMC_CTL register */
void fmc_lock(void);
/* FMC erase sector */
fmc_state_enum fmc_sector_erase(uint32_t address);
/* FMC typical mass erase */
fmc_state_enum fmc_typical_mass_erase(void);
/* FMC protection-removed mass erase */
fmc_state_enum fmc_protection_removed_mass_erase(void);
/* FMC program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);
/* FMC program a double-word at the corresponding address */
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);
/* enable check programming area */
fmc_state_enum fmc_check_programming_area_enable(void);
/* disable check programming area */
fmc_state_enum fmc_check_programming_area_disable(void);

/* FMC option bytes operation functions */
/* unlock the option byte operation */
void ob_unlock(void);
/* lock the option byte operation */
void ob_lock(void);
/* send option bytes modification start command */
fmc_state_enum ob_start(void);
/* modify option byte to factory value */
fmc_state_enum ob_factory_value_config(void);
/* enable secure access mode */
fmc_state_enum ob_secure_access_mode_enable(void);
/* disable secure access mode */
fmc_state_enum ob_secure_access_mode_disable(void);
/* configure the option byte security protection level */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc);
/* configure option byte BOR threshold value */
fmc_state_enum ob_bor_threshold_config(uint32_t ob_bor_th);
/* configure low power related option byte */
fmc_state_enum ob_low_power_config(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby, uint32_t ob_fwdg_suspend_deepsleep,
                                   uint32_t ob_fwdg_suspend_standby);
/* configure TCM ECC option byte */
fmc_state_enum ob_tcm_ecc_config(uint32_t ob_itcmecc, uint32_t ob_dtcm0ecc, uint32_t ob_dtcm1ecc);
/* configure I/O speed optimization option byte */
fmc_state_enum ob_iospeed_optimize_config(uint32_t ob_iospeed_op);
/* configure option byte TCM shared RAM size */
fmc_state_enum ob_tcm_shared_ram_config(uint32_t itcm_shared_ram_size, uint32_t dtcm_shared_ram_size);
/* modify option byte DATA */
fmc_state_enum ob_data_program(uint16_t ob_data);
/* configure boot address */
fmc_state_enum ob_boot_address_config(uint8_t boot_pin, uint16_t boot_address);
/* configure DCRP area */
fmc_state_enum ob_dcrp_area_config(uint32_t dcrp_eren, uint32_t dcrp_start, uint32_t dcrp_end);
/* configure secure-access area */
fmc_state_enum ob_secure_area_config(uint32_t scr_eren, uint32_t scr_start, uint32_t scr_end);
/* enable erase/program protection */
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp);
/* disable erase/program protection */
fmc_state_enum ob_write_protection_disable(uint32_t ob_wp);
/* get the option byte secure access mode */
FlagStatus ob_secure_mode_get(void);
/* get the option byte security protection level */
FlagStatus ob_security_protection_flag_get(void);
/* get the option byte BOR threshold value */
uint32_t ob_bor_threshold_get(void);
/* get low power related option byte */
void ob_low_power_get(uint32_t *fwdgt, uint32_t *deepsleep, uint32_t *standby, uint32_t *fwdg_suspend_deepsleep, uint32_t *fwdg_suspend_standby);
/* get TCM ECC configuration */
void ob_tcm_ecc_get(uint32_t *itcmecc_option, uint32_t *dtcm0ecc_option, uint32_t *dtcm1ecc_option);
/* get IO speed optimize configuration */
FlagStatus ob_iospeed_optimize_get(void);
/* get the option byte TCM shared RAM size */
void ob_tcm_shared_ram_size_get(uint32_t *itcm_shared_ram_kb_size, uint32_t *dtcm_shared_ram_kb_size);
/* get user data value */
uint16_t ob_data_get(void);
/* get boot address */
uint32_t ob_boot_address_get(uint8_t boot_pin);
/* get DCRP area configuration */
uint8_t ob_dcrp_area_get(uint32_t *dcrp_erase_option, uint32_t *dcrp_area_start_addr, uint32_t *dcrp_area_end_addr);
/* get secure-access area configuration */
uint8_t ob_secure_area_get(uint32_t *secure_area_option, uint32_t *scr_area_start_addr, uint32_t *scr_area_end_addr);
/* get the option byte erase/program protection state */
uint32_t ob_write_protection_get(void);

/* FMC universal functions */
/* configure NO-RTDEC area */
fmc_state_enum fmc_no_rtdec_config(uint32_t nodec_area_start, uint32_t nodec_area_end);
/* configure aes initialization vector */
fmc_state_enum fmc_aes_iv_config(uint32_t *aes_iv);
/* get Flash ECC function enable flag */
FlagStatus fmc_flash_ecc_get(void);
/* get NO-RTDEC area */
void fmc_no_rtdec_get(uint32_t *nodec_area_start, uint32_t *nodec_area_end);
/* get AES initialization vector */
void fmc_aes_iv_get(uint32_t *aes_iv);
/* get product ID */
void fmc_pid_get(uint32_t *pid);

/* interrupt & flag functions */
/* get FMC flag status */
FlagStatus fmc_flag_get(fmc_flag_enum flag);
/* clear FMC flag status */
void fmc_flag_clear(fmc_flag_enum flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(fmc_interrupt_enum interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(fmc_interrupt_enum interrupt);
/* get FMC interrupt flag status */
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag);
/* clear FMC interrupt flag status */
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag);

#endif /* GD32H7XX_FMC_H */
