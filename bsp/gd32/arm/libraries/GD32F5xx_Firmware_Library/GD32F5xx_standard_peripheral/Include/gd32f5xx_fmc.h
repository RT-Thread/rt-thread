/*!
    \file    gd32f5xx_fmc.h
    \brief   definitions for the FMC

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


#ifndef GD32F5XX_FMC_H
#define GD32F5XX_FMC_H

#include "gd32f5xx.h"

/* FMC and option byte definition */
#define FMC                            FMC_BASE                                        /*!< FMC register base address */
#define OB                             OB_BASE                                         /*!< option byte base address */

/* registers definitions */
#define FMC_KEY                        REG32((FMC) + 0x00000004U)                      /*!< FMC unlock key register */
#define FMC_OBKEY                      REG32((FMC) + 0x00000008U)                      /*!< FMC option byte unlock key register */
#define FMC_STAT                       REG32((FMC) + 0x0000000CU)                      /*!< FMC status register */
#define FMC_CTL                        REG32((FMC) + 0x00000010U)                      /*!< FMC control register */
#define FMC_OBCTL0                     REG32((FMC) + 0x00000014U)                      /*!< FMC option byte control register 0 */
#define FMC_OBCTL1                     REG32((FMC) + 0x00000018U)                      /*!< FMC option byte control register 1 */
#define FMC_PECFG                      REG32((FMC) + 0x00000020U)                      /*!< FMC page erase configuration register */
#define FMC_PEKEY                      REG32((FMC) + 0x00000024U)                      /*!< FMC unlock page erase key register */
#define FMC_OTP1CFG                    REG32((FMC) + 0x00000028U)                      /*!< FMC OTP1 configuration register */
#define FMC_LDECCADDR0                 REG32((FMC) + 0x0000002CU)                      /*!< FMC two bits ECC error address0 when load code from flash/bootloader/OTP1 */
#define FMC_LDECCADDR1                 REG32((FMC) + 0x00000030U)                      /*!< FMC two bits ECC error address1 when load code from flash/bootloader/OTP1 */
#define FMC_LDECCADDR2                 REG32((FMC) + 0x00000034U)                      /*!< FMC two bits ECC error address2 when load code from flash/bootloader/OTP1 */
#define FMC_OBSTAT                     REG32((FMC) + 0x00000040U)                      /*!< FMC option bytes status register */
#define FMC_PID                        REG32((FMC) + 0x00000100U)                      /*!< FMC product ID register */
#define EFUSE_CS                       REG32((FMC) + 0x00000200U)                      /*!< EFUSE control and status register */
#define EFUSE_ADDR                     REG32((FMC) + 0x00000204U)                      /*!< EFUSE address register */
#define EFUSE_CTL                      REG32((FMC) + 0x00000208U)                      /*!< EFUSE efuse controlregister */
#define EFUSE_USER_DATA                REG32((FMC) + 0x0000020CU)                      /*!< EFUSE user data register */

#define OB_USER                        REG8((OB) + 0x00010000U)                        /*!< option byte user value*/
#define OB_SPC                         REG8((OB) + 0x00010001U)                        /*!< option byte security protection value */
#define OB_WP0_0                       REG8((OB) + 0x00010008U)                        /*!< option byte write protection 0 */
#define OB_WP0_1                       REG8((OB) + 0x00010009U)                        /*!< option byte write protection 0 */
#define OB_WP0_2                       REG8((OB) + 0x0001000CU)                        /*!< option byte write protection 0 */
#define OB_WP1_0                       REG8((OB) + 0x00000008U)                        /*!< option byte write protection 1 */
#define OB_WP1_1                       REG8((OB) + 0x00000009U)                        /*!< option byte write protection 1 */
#define OB_WP1_2                       REG8((OB) + 0x0000000CU)                        /*!< option byte write protection 1 */

/* registers offset */
#define EFUSE_CTL_OFFSET               ((uint32_t)0x00000208U)                         /*!< EFUSE efuse control register offset */
#define EFUSE_USER_DATA_OFFSET         ((uint32_t)0x0000020CU)                         /*!< EFUSE user data register offset */

/* bits definitions */
/* FMC_KEY */
#define FMC_KEY_KEY                    BITS(0,31)                                      /*!< FMC main flash key bits */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY                BITS(0,31)                                      /*!< option byte key bits */

/* FMC_STAT */
#define FMC_STAT_END                   BIT(0)                                          /*!< end of operation flag bit */
#define FMC_STAT_OPERR                 BIT(1)                                          /*!< flash operation error flag bit */
#define FMC_STAT_LDECCDET              BIT(2)                                          /*!< two bits ECC error when load code from flash/OTP1/bootloader */
#define FMC_STAT_WPERR                 BIT(4)                                          /*!< erase/Program protection error flag bit */
#define FMC_STAT_PGAERR                BIT(5)                                          /*!< Program alignment error flag bit */
#define FMC_STAT_PGMERR                BIT(6)                                          /*!< program size not match error flag bit */
#define FMC_STAT_PGSERR                BIT(7)                                          /*!< program sequence error flag bit */
#define FMC_STAT_RDCERR                BIT(8)                                          /*!< CBUS data read protection error flag bit */
#define FMC_STAT_BUSY                  BIT(16)                                         /*!< flash busy flag bit */

/* FMC_CTL */
#define FMC_CTL_PG                     BIT(0)                                          /*!< main flash program command bit */
#define FMC_CTL_SER                    BIT(1)                                          /*!< main flash sector erase command bit */
#define FMC_CTL_MER0                   BIT(2)                                          /*!< main flash mass erase for bank0 command bit */
#define FMC_CTL_SN                     BITS(3,7)                                       /*!< select which sector number to be erased */
#define FMC_CTL_PSZ                    BITS(8,9)                                       /*!< program size bit */
#define FMC_CTL_DWPGE                  BIT(10)                                         /*!< double word Program size bit enable bit */
#define FMC_CTL_SN_5                   BIT(11)                                         /*!< bit 5 of SN */
#define FMC_CTL_MER1                   BIT(15)                                         /*!< main flash mass erase for bank1 command bit */
#define FMC_CTL_START                  BIT(16)                                         /*!< send erase command to FMC bit */
#define FMC_CTL_ENDIE                  BIT(24)                                         /*!< end of operation interrupt enable bit */
#define FMC_CTL_ERRIE                  BIT(25)                                         /*!< error interrupt enable bit */
#define FMC_CTL_LDECCIE                BIT(26)                                         /*!< load code ECC error interrupt enable bit */
#define FMC_CTL_NWLDE                  BIT(29)                                         /*!< No wait time area load enable when system reset */
#define FMC_CTL_RLBP                   BIT(30)                                         /*!< Read lock block protection for OTP2 */
#define FMC_CTL_LK                     BIT(31)                                         /*!< FMC_CTL lock bit */

/* FMC_OBCTL0 */
#define FMC_OBCTL0_OB_LK               BIT(0)                                          /*!< FMC_OBCTL0 lock bit */
#define FMC_OBCTL0_OB_START            BIT(1)                                          /*!< send option byte change command to FMC bit */
#define FMC_OBCTL0_BOR_TH              BITS(2,3)                                       /*!< option byte BOR threshold value */
#define FMC_OBCTL0_BB                  BIT(4)                                          /*!< option byte boot bank value */
#define FMC_OBCTL0_NWDG_HW             BIT(5)                                          /*!< option byte watchdog value */
#define FMC_OBCTL0_NRST_DPSLP          BIT(6)                                          /*!< option byte deepsleep reset value */
#define FMC_OBCTL0_NRST_STDBY          BIT(7)                                          /*!< option byte standby reset value */
#define FMC_OBCTL0_SPC                 BITS(8,15)                                      /*!< option byte Security Protection code */
#define FMC_OBCTL0_WP0                 BITS(16,27)                                     /*!< erase/program protection of low 12 sectors of bank0 when DRP is 0 */
#define FMC_OBCTL0_ECCEN               BIT(28)                                         /*!< ECC enable bit */
#define FMC_OBCTL0_NWA                 BIT(29)                                         /*!< no waiting time area select bit */
#define FMC_OBCTL0_DRP                 BIT(31)                                         /*!< CBUS read protection bit */

/* FMC_OBCTL1 */
#define FMC_OBCTL1_WP0_H               BITS(0,7)                                       /*!< erase/program protection of high 8 sectors of bank0 when DRP is 0 */
#define FMC_OBCTL1_WP1_H               BITS(8,15)                                      /*!< erase/program protection of high 8 sectors of bank1 when DRP is 0 */
#define FMC_OBCTL1_WP1_L               BITS(16,27)                                     /*!< erase/program protection of low 12 sectors of bank1 when DRP is 0 */

/* FMC_PECFG */
#define FMC_PECFG_PE_ADDR              BITS(0,28)                                      /*!< page address (4KB alignment) */
#define FMC_PECFG_PE_EN                BIT(31)                                         /*!< the enable bit of page erase function */

/* FMC_PEKEY */
#define FMC_PEKEY_PE_KEY               BITS(0,31)                                      /*!< FMC_PECFG unlock key value */

/* FMC_OTP1CFG */
#define FMC_OTP1CFG_OTP1REN            BITS(0,15)                                      /*!< FMC OTP1 read enable bits */

/* FMC_LDECCADDR0 */
#define FMC_LDECCADDR0_LDECCADDR0      BITS(0,31)                                      /*!< ECC two bits error address0 when load code from flash/bootloader/OTP1 */

/* FMC_LDECCADDR1 */
#define FMC_LDECCADDR1_LDECCADDR1      BITS(0,31)                                      /*!< ECC two bits error address1 when load code from flash/bootloader/OTP1 */

/* FMC_LDECCADDR2 */
#define FMC_LDECCADDR2_LDECCADDR2      BITS(0,31)                                      /*!< ECC two bits error address2 when load code from flash/bootloader/OTP1 */

/* FMC_OBSTAT */
#define FMC_OB_SPCL                    BIT(1)                                          /*!< security protection is level low */
#define FMC_OB_SPCH                    BIT(2)                                          /*!< security protection is level high */

/* FMC_PID */
#define FMC_PID_PID                    BITS(0,31)                                      /*!< product ID bits */

/* EFUSE_CS */
#define EFUSE_CS_EFSTR             BIT(0)                                              /*!< start efuse operation */
#define EFUSE_CS_EFRW              BIT(1)                                              /*!< the selection of efuse operation */
#define EFUSE_CS_EFBYP             BIT(2)                                              /*!< EFUSE program supply selection */
#define EFUSE_CS_PGIF              BIT(16)                                             /*!< program operation complete flag */
#define EFUSE_CS_RDIF              BIT(17)                                             /*!< read operation complete flag */
#define EFUSE_CS_OVBERIF           BIT(18)                                             /*!< overstep boundary error flag */
#define EFUSE_CS_PGIE              BIT(20)                                             /*!< enable bit for program operation completed interrupt */
#define EFUSE_CS_RDIE              BIT(21)                                             /*!< enable bit for read operation completed interrupt */
#define EFUSE_CS_OVBERIE           BIT(22)                                             /*!< enable bit for overstep boundary error interrupt */
#define EFUSE_CS_PGIC              BIT(24)                                             /*!< clear bit for program operation completed interrupt flag */
#define EFUSE_CS_RDIC              BIT(25)                                             /*!< clear bit for read operation completed interrupt flag */
#define EFUSE_CS_OVBERIC           BIT(26)                                             /*!< clear bit for overstep boundary error interrupt flag */

/* EFUSE_ADDR */
#define EFUSE_ADDR_EFADDR          BITS(0,4)                                           /*!< read or program efuse data start address */
#define EFUSE_ADDR_EFSIZE          BITS(8,12)                                          /*!< read or program efuse data size */

/* EFUSE_CTL */
#define EFUSE_CTL_EFSPC            BIT(0)                                              /*!< EFUSE security protection level */
#define EFUSE_CTL_NDBG             BIT(1)                                              /*!< debugging permission setting */
#define EFUSE_CTL_NBTSB            BIT(2)                                              /*!< not boot from sram or bootloader */
#define EFUSE_CTL_BTFOSEL          BIT(3)                                              /*!< select boot from flash or OTP1 when NBTSB is 1 or BOOT0 is 0 */
#define EFUSE_CTL_UDLK             BIT(6)                                              /*!< EFUSE_USER_DATA register lock bit */
#define EFUSE_CTL_LK               BIT(7)                                              /*!< EFUSE_CTL register lock bit */

/* EFUSE_USER_DATA */
#define EFUSE_USER_DATA_USERDATA   BITS(0,7)                                           /*!< EFUSE USER_DATA value */

/* unlock key */
#define UNLOCK_KEY0                    ((uint32_t)0x45670123U)                             /*!< unlock key 0 */
#define UNLOCK_KEY1                    ((uint32_t)0xCDEF89ABU)                             /*!< unlock key 1 */
#define UNLOCK_PE_KEY                  ((uint32_t)0xA9B8C7D6U)                             /*!< unlock page erase function key */

#define OB_UNLOCK_KEY0                 ((uint32_t)0x08192A3BU)                             /*!< ob unlock key 0 */
#define OB_UNLOCK_KEY1                 ((uint32_t)0x4C5D6E7FU)                             /*!< ob unlock key 1 */

/* option byte BOR threshold value */
#define OBCTL0_BOR_TH(regval)          (BITS(2,3) & ((uint32_t)(regval)) << 2U)
#define OB_BOR_TH_VALUE3               OBCTL0_BOR_TH(0)                                     /*!< BOR threshold value 3 */
#define OB_BOR_TH_VALUE2               OBCTL0_BOR_TH(1)                                     /*!< BOR threshold value 2 */
#define OB_BOR_TH_VALUE1               OBCTL0_BOR_TH(2)                                     /*!< BOR threshold value 1 */
#define OB_BOR_TH_OFF                  OBCTL0_BOR_TH(3)                                     /*!< no BOR function */

/* option byte boot bank value */
#define OBCTL0_BB(regval)              (BIT(4) & ((uint32_t)(regval) << 4U))
#define OB_BB_DISABLE                  OBCTL0_BB(0)                                         /*!< boot from bank0 */
#define OB_BB_ENABLE                   OBCTL0_BB(1)                                         /*!< boot from bank1 or bank0 if bank1 is void */

/* option byte software/hardware free watch dog timer */
#define OBCTL0_NWDG_HW(regval)         (BIT(5) & ((uint32_t)(regval)) << 5U)
#define OB_FWDGT_SW                    OBCTL0_NWDG_HW(1)                                    /*!< software free watchdog */
#define OB_FWDGT_HW                    OBCTL0_NWDG_HW(0)                                    /*!< hardware free watchdog */

/* option byte reset or not entering deep sleep mode */
#define OBCTL0_NRST_DPSLP(regval)      (BIT(6) & ((uint32_t)(regval)) << 6U)
#define OB_DEEPSLEEP_NRST              OBCTL0_NRST_DPSLP(1)                                 /*!< no reset when entering deepsleep mode */
#define OB_DEEPSLEEP_RST               OBCTL0_NRST_DPSLP(0)                                 /*!< generate a reset instead of entering deepsleep mode */

/* option byte reset or not entering standby mode */
#define OBCTL0_NRST_STDBY(regval)      (BIT(7) & ((uint32_t)(regval)) << 7U)
#define OB_STDBY_NRST                  OBCTL0_NRST_STDBY(1)                                 /*!< no reset when entering deepsleep mode */
#define OB_STDBY_RST                   OBCTL0_NRST_STDBY(0)                                 /*!< generate a reset instead of entering standby mode */

/* option byte sram/flash ECC configure */
#define OBCTL0_ECCEN(regval)           (BIT(28) & ((uint32_t)(regval) << 28U))
#define OB_ECC_DISABLE                 OBCTL0_ECCEN(0)                                      /*!< sram/flash ECC disable */
#define OB_ECC_ENABLE                  OBCTL0_ECCEN(1)                                      /*!< sram/flash ECC enable */

/* option byte no waiting time area select */
#define OBCTL0_NWA(regval)             (BIT(29) & ((uint32_t)(regval) << 29U))
#define OB_NWA_BANK1                   OBCTL0_NWA(0)                                      /*!< bank1 is no waiting time area */
#define OB_NWA_BANK0                   OBCTL0_NWA(1)                                      /*!< bank0 is no waiting time area */

/* read protect configure */
#define FMC_NSPC                       ((uint8_t)0xAAU)                                     /*!< no security protection */
#define FMC_LSPC                       ((uint8_t)0xBBU)                                     /*!< low security protection */
#define FMC_HSPC                       ((uint8_t)0xCCU)                                     /*!< high security protection */

/* option bytes write protection */
#define OB_WP_0                        ((uint64_t)0x0000000000000001U)                      /*!< erase/program protection of sector 0  */
#define OB_WP_1                        ((uint64_t)0x0000000000000002U)                      /*!< erase/program protection of sector 1  */
#define OB_WP_2                        ((uint64_t)0x0000000000000004U)                      /*!< erase/program protection of sector 2  */
#define OB_WP_3                        ((uint64_t)0x0000000000000008U)                      /*!< erase/program protection of sector 3  */
#define OB_WP_4                        ((uint64_t)0x0000000000000010U)                      /*!< erase/program protection of sector 4  */
#define OB_WP_5                        ((uint64_t)0x0000000000000020U)                      /*!< erase/program protection of sector 5  */
#define OB_WP_6                        ((uint64_t)0x0000000000000040U)                      /*!< erase/program protection of sector 6  */
#define OB_WP_7                        ((uint64_t)0x0000000000000080U)                      /*!< erase/program protection of sector 7  */
#define OB_WP_8                        ((uint64_t)0x0000000000000100U)                      /*!< erase/program protection of sector 8  */
#define OB_WP_9                        ((uint64_t)0x0000000000000200U)                      /*!< erase/program protection of sector 9  */
#define OB_WP_10                       ((uint64_t)0x0000000000000400U)                      /*!< erase/program protection of sector 10 */
#define OB_WP_11                       ((uint64_t)0x0000000000000800U)                      /*!< erase/program protection of sector 11 */
#define OB_WP_12                       ((uint64_t)0x0000000000001000U)                      /*!< erase/program protection of sector 12 */
#define OB_WP_13                       ((uint64_t)0x0000000000002000U)                      /*!< erase/program protection of sector 13 */
#define OB_WP_14                       ((uint64_t)0x0000000000004000U)                      /*!< erase/program protection of sector 14 */
#define OB_WP_15                       ((uint64_t)0x0000000000008000U)                      /*!< erase/program protection of sector 15 */
#define OB_WP_16                       ((uint64_t)0x0000000000010000U)                      /*!< erase/program protection of sector 16 */
#define OB_WP_17                       ((uint64_t)0x0000000000020000U)                      /*!< erase/program protection of sector 17 */
#define OB_WP_18                       ((uint64_t)0x0000000000040000U)                      /*!< erase/program protection of sector 18 */
#define OB_WP_19                       ((uint64_t)0x0000000000080000U)                      /*!< erase/program protection of sector 19 */
#define OB_WP_20                       ((uint64_t)0x0000000000100000U)                      /*!< erase/program protection of sector 20 */
#define OB_WP_21                       ((uint64_t)0x0000000000200000U)                      /*!< erase/program protection of sector 21 */
#define OB_WP_22                       ((uint64_t)0x0000000000400000U)                      /*!< erase/program protection of sector 22 */
#define OB_WP_23                       ((uint64_t)0x0000000000800000U)                      /*!< erase/program protection of sector 23 */
#define OB_WP_24                       ((uint64_t)0x0000000001000000U)                      /*!< erase/program protection of sector 24 */
#define OB_WP_25                       ((uint64_t)0x0000000002000000U)                      /*!< erase/program protection of sector 25 */
#define OB_WP_26                       ((uint64_t)0x0000000004000000U)                      /*!< erase/program protection of sector 26 */
#define OB_WP_27                       ((uint64_t)0x0000000008000000U)                      /*!< erase/program protection of sector 27 */
#define OB_WP_28                       ((uint64_t)0x0000000010000000U)                      /*!< erase/program protection of sector 28 */
#define OB_WP_29                       ((uint64_t)0x0000000020000000U)                      /*!< erase/program protection of sector 29 */
#define OB_WP_30                       ((uint64_t)0x0000000040000000U)                      /*!< erase/program protection of sector 30 */
#define OB_WP_31                       ((uint64_t)0x0000000080000000U)                      /*!< erase/program protection of sector 31 */
#define OB_WP_32                       ((uint64_t)0x0000000100000000U)                      /*!< erase/program protection of sector 32 */
#define OB_WP_33                       ((uint64_t)0x0000000200000000U)                      /*!< erase/program protection of sector 33 */
#define OB_WP_34                       ((uint64_t)0x0000000400000000U)                      /*!< erase/program protection of sector 34 */
#define OB_WP_35                       ((uint64_t)0x0000000800000000U)                      /*!< erase/program protection of sector 35 */
#define OB_WP_36                       ((uint64_t)0x0000001000000000U)                      /*!< erase/program protection of sector 36 */
#define OB_WP_37                       ((uint64_t)0x0000002000000000U)                      /*!< erase/program protection of sector 37 */
#define OB_WP_38                       ((uint64_t)0x0000004000000000U)                      /*!< erase/program protection of sector 38 */
#define OB_WP_39_53                    ((uint64_t)0x0000008000000000U)                      /*!< erase/program protection of sector 39~53 */
#define OB_WP_ALL                      ((uint64_t)0x000000FFFFFFFFFFU)                      /*!< erase/program protection of all sectors */

/* option bytes CBUS read protection */
#define OB_DRP_0                       ((uint64_t)0x0000000000000001U)                      /*!< CBUS read protection protection of sector 0  */
#define OB_DRP_1                       ((uint64_t)0x0000000000000002U)                      /*!< CBUS read protection protection of sector 1  */
#define OB_DRP_2                       ((uint64_t)0x0000000000000004U)                      /*!< CBUS read protection protection of sector 2  */
#define OB_DRP_3                       ((uint64_t)0x0000000000000008U)                      /*!< CBUS read protection protection of sector 3  */
#define OB_DRP_4                       ((uint64_t)0x0000000000000010U)                      /*!< CBUS read protection protection of sector 4  */
#define OB_DRP_5                       ((uint64_t)0x0000000000000020U)                      /*!< CBUS read protection protection of sector 5  */
#define OB_DRP_6                       ((uint64_t)0x0000000000000040U)                      /*!< CBUS read protection protection of sector 6  */
#define OB_DRP_7                       ((uint64_t)0x0000000000000080U)                      /*!< CBUS read protection protection of sector 7  */
#define OB_DRP_8                       ((uint64_t)0x0000000000000100U)                      /*!< CBUS read protection protection of sector 8  */
#define OB_DRP_9                       ((uint64_t)0x0000000000000200U)                      /*!< CBUS read protection protection of sector 9  */
#define OB_DRP_10                      ((uint64_t)0x0000000000000400U)                      /*!< CBUS read protection protection of sector 10 */
#define OB_DRP_11                      ((uint64_t)0x0000000000000800U)                      /*!< CBUS read protection protection of sector 11 */
#define OB_DRP_12                      ((uint64_t)0x0000000000001000U)                      /*!< CBUS read protection protection of sector 12 */
#define OB_DRP_13                      ((uint64_t)0x0000000000002000U)                      /*!< CBUS read protection protection of sector 13 */
#define OB_DRP_14                      ((uint64_t)0x0000000000004000U)                      /*!< CBUS read protection protection of sector 14 */
#define OB_DRP_15                      ((uint64_t)0x0000000000008000U)                      /*!< CBUS read protection protection of sector 15 */
#define OB_DRP_16                      ((uint64_t)0x0000000000010000U)                      /*!< CBUS read protection protection of sector 16 */
#define OB_DRP_17                      ((uint64_t)0x0000000000020000U)                      /*!< CBUS read protection protection of sector 17 */
#define OB_DRP_18                      ((uint64_t)0x0000000000040000U)                      /*!< CBUS read protection protection of sector 18 */
#define OB_DRP_19                      ((uint64_t)0x0000000000080000U)                      /*!< CBUS read protection protection of sector 19 */
#define OB_DRP_20                      ((uint64_t)0x0000000000100000U)                      /*!< CBUS read protection protection of sector 20 */
#define OB_DRP_21                      ((uint64_t)0x0000000000200000U)                      /*!< CBUS read protection protection of sector 21 */
#define OB_DRP_22                      ((uint64_t)0x0000000000400000U)                      /*!< CBUS read protection protection of sector 22 */
#define OB_DRP_23                      ((uint64_t)0x0000000000800000U)                      /*!< CBUS read protection protection of sector 23 */
#define OB_DRP_24                      ((uint64_t)0x0000000001000000U)                      /*!< CBUS read protection protection of sector 24 */
#define OB_DRP_25                      ((uint64_t)0x0000000002000000U)                      /*!< CBUS read protection protection of sector 25 */
#define OB_DRP_26                      ((uint64_t)0x0000000004000000U)                      /*!< CBUS read protection protection of sector 26 */
#define OB_DRP_27                      ((uint64_t)0x0000000008000000U)                      /*!< CBUS read protection protection of sector 27 */
#define OB_DRP_28                      ((uint64_t)0x0000000010000000U)                      /*!< CBUS read protection protection of sector 28 */
#define OB_DRP_29                      ((uint64_t)0x0000000020000000U)                      /*!< CBUS read protection protection of sector 29 */
#define OB_DRP_30                      ((uint64_t)0x0000000040000000U)                      /*!< CBUS read protection protection of sector 30 */
#define OB_DRP_31                      ((uint64_t)0x0000000080000000U)                      /*!< CBUS read protection protection of sector 31 */
#define OB_DRP_32                      ((uint64_t)0x0000000100000000U)                      /*!< CBUS read protection protection of sector 32 */
#define OB_DRP_33                      ((uint64_t)0x0000000200000000U)                      /*!< CBUS read protection protection of sector 33 */
#define OB_DRP_34                      ((uint64_t)0x0000000400000000U)                      /*!< CBUS read protection protection of sector 34 */
#define OB_DRP_35                      ((uint64_t)0x0000000800000000U)                      /*!< CBUS read protection protection of sector 35 */
#define OB_DRP_36                      ((uint64_t)0x0000001000000000U)                      /*!< CBUS read protection protection of sector 36 */
#define OB_DRP_37                      ((uint64_t)0x0000002000000000U)                      /*!< CBUS read protection protection of sector 37 */
#define OB_DRP_38                      ((uint64_t)0x0000004000000000U)                      /*!< CBUS read protection protection of sector 38 */
#define OB_DRP_39_53                   ((uint64_t)0x0000008000000000U)                      /*!< CBUS read protection protection of sector 39~53 */
#define OB_DRP_ALL                     ((uint64_t)0x000000FFFFFFFFFFU)                      /*!< CBUS read protection protection of all sectors */

/* option bytes CBUS read protection mode */
#define OBCTL0_DRP(regval)             (BIT(31) & ((uint32_t)(regval) << 31U))
#define OB_DRP_DISABLE                 OBCTL0_DRP(0)                                        /*!< the WPx bits used as erase/program protection of each sector */
#define OB_DRP_ENABLE                  OBCTL0_DRP(1)                                        /*!< the WPx bits used as erase/program protection and CBUS read protection of each sector */

/* FMC sectors */
#define SN_5                           FMC_CTL_SN_5                                         /* bit 5 of sector number */
#define CTL_SN(regval)                 (BITS(3,7) & ((uint32_t)(regval)) << 3)
#define CTL_SECTOR_NUMBER_0            CTL_SN(0)                                            /*!< sector 0  */
#define CTL_SECTOR_NUMBER_1            CTL_SN(1)                                            /*!< sector 1  */
#define CTL_SECTOR_NUMBER_2            CTL_SN(2)                                            /*!< sector 2  */
#define CTL_SECTOR_NUMBER_3            CTL_SN(3)                                            /*!< sector 3  */
#define CTL_SECTOR_NUMBER_4            CTL_SN(4)                                            /*!< sector 4  */
#define CTL_SECTOR_NUMBER_5            CTL_SN(5)                                            /*!< sector 5  */
#define CTL_SECTOR_NUMBER_6            CTL_SN(6)                                            /*!< sector 6  */
#define CTL_SECTOR_NUMBER_7            CTL_SN(7)                                            /*!< sector 7  */
#define CTL_SECTOR_NUMBER_8            CTL_SN(8)                                            /*!< sector 8  */
#define CTL_SECTOR_NUMBER_9            CTL_SN(9)                                            /*!< sector 9  */
#define CTL_SECTOR_NUMBER_10           CTL_SN(10)                                           /*!< sector 10 */
#define CTL_SECTOR_NUMBER_11           CTL_SN(11)                                           /*!< sector 11 */
#define CTL_SECTOR_NUMBER_12           CTL_SN(12)                                           /*!< sector 12 */
#define CTL_SECTOR_NUMBER_13           CTL_SN(13)                                           /*!< sector 13 */
#define CTL_SECTOR_NUMBER_14           CTL_SN(14)                                           /*!< sector 14 */
#define CTL_SECTOR_NUMBER_15           CTL_SN(15)                                           /*!< sector 15 */
#define CTL_SECTOR_NUMBER_16           CTL_SN(16)                                           /*!< sector 16 */
#define CTL_SECTOR_NUMBER_17           CTL_SN(17)                                           /*!< sector 17 */
#define CTL_SECTOR_NUMBER_18           CTL_SN(18)                                           /*!< sector 18 */
#define CTL_SECTOR_NUMBER_19           CTL_SN(19)                                           /*!< sector 19 */
#define CTL_SECTOR_NUMBER_20           CTL_SN(20)                                           /*!< sector 20 */
#define CTL_SECTOR_NUMBER_21           CTL_SN(21)                                           /*!< sector 21 */
#define CTL_SECTOR_NUMBER_22           CTL_SN(22)                                           /*!< sector 22 */
#define CTL_SECTOR_NUMBER_23           CTL_SN(23)                                           /*!< sector 23 */
#define CTL_SECTOR_NUMBER_24           CTL_SN(24)                                           /*!< sector 24 */
#define CTL_SECTOR_NUMBER_25           CTL_SN(25)                                           /*!< sector 25 */
#define CTL_SECTOR_NUMBER_26           CTL_SN(26)                                           /*!< sector 26 */
#define CTL_SECTOR_NUMBER_27           CTL_SN(27)                                           /*!< sector 27 */
#define CTL_SECTOR_NUMBER_28           CTL_SN(28)                                           /*!< sector 28 */
#define CTL_SECTOR_NUMBER_29           CTL_SN(29)                                           /*!< sector 29 */
#define CTL_SECTOR_NUMBER_30           CTL_SN(30)                                           /*!< sector 30 */
#define CTL_SECTOR_NUMBER_31           CTL_SN(31)                                           /*!< sector 31 */
#define CTL_SECTOR_NUMBER_32           (SN_5 | CTL_SN(0))                                   /*!< sector 32 */
#define CTL_SECTOR_NUMBER_33           (SN_5 | CTL_SN(1))                                   /*!< sector 33 */
#define CTL_SECTOR_NUMBER_34           (SN_5 | CTL_SN(2))                                   /*!< sector 34 */
#define CTL_SECTOR_NUMBER_35           (SN_5 | CTL_SN(3))                                   /*!< sector 35 */
#define CTL_SECTOR_NUMBER_36           (SN_5 | CTL_SN(4))                                   /*!< sector 36 */
#define CTL_SECTOR_NUMBER_37           (SN_5 | CTL_SN(5))                                   /*!< sector 37 */
#define CTL_SECTOR_NUMBER_38           (SN_5 | CTL_SN(6))                                   /*!< sector 38 */
#define CTL_SECTOR_NUMBER_39           (SN_5 | CTL_SN(7))                                   /*!< sector 39 */
#define CTL_SECTOR_NUMBER_40           (SN_5 | CTL_SN(8))                                   /*!< sector 40 */
#define CTL_SECTOR_NUMBER_41           (SN_5 | CTL_SN(9))                                   /*!< sector 41 */
#define CTL_SECTOR_NUMBER_42           (SN_5 | CTL_SN(10))                                  /*!< sector 42 */
#define CTL_SECTOR_NUMBER_43           (SN_5 | CTL_SN(11))                                  /*!< sector 43 */
#define CTL_SECTOR_NUMBER_44           (SN_5 | CTL_SN(12))                                  /*!< sector 44 */
#define CTL_SECTOR_NUMBER_45           (SN_5 | CTL_SN(13))                                  /*!< sector 45 */
#define CTL_SECTOR_NUMBER_46           (SN_5 | CTL_SN(14))                                  /*!< sector 46 */
#define CTL_SECTOR_NUMBER_47           (SN_5 | CTL_SN(15))                                  /*!< sector 47 */
#define CTL_SECTOR_NUMBER_48           (SN_5 | CTL_SN(16))                                  /*!< sector 48 */
#define CTL_SECTOR_NUMBER_49           (SN_5 | CTL_SN(17))                                  /*!< sector 49 */
#define CTL_SECTOR_NUMBER_50           (SN_5 | CTL_SN(18))                                  /*!< sector 50 */
#define CTL_SECTOR_NUMBER_51           (SN_5 | CTL_SN(19))                                  /*!< sector 51 */
#define CTL_SECTOR_NUMBER_52           (SN_5 | CTL_SN(20))                                  /*!< sector 52 */
#define CTL_SECTOR_NUMBER_53           (SN_5 | CTL_SN(21))                                  /*!< sector 53 */

/* FMC program size */
#define CTL_PSZ(regval)                (BITS(8,9) & ((uint32_t)(regval)) << 8U)
#define CTL_PSZ_BYTE                   CTL_PSZ(0)                                           /*!< FMC program by byte access */
#define CTL_PSZ_HALF_WORD              CTL_PSZ(1)                                           /*!< FMC program by half-word access */
#define CTL_PSZ_WORD                   CTL_PSZ(2)                                           /*!< FMC program by word access */

/* FMC interrupt enable */
#define FMC_INT_END                    FMC_CTL_ENDIE                              /*!< enable FMC end of program interrupt */
#define FMC_INT_ERR                    FMC_CTL_ERRIE                              /*!< enable FMC error interrupt */
#define FMC_INT_LDECC                  FMC_CTL_LDECCIE                            /*!< enable FMC load code ECC error interrupt */

/* FMC flags */
#define FMC_FLAG_END                   FMC_STAT_END                                         /*!< FMC end of operation flag bit */
#define FMC_FLAG_OPERR                 FMC_STAT_OPERR                                       /*!< FMC operation error flag bit */
#define FMC_FLAG_LDECCDET              FMC_STAT_LDECCDET                                    /*!< FMC two bits ECC error when load code from flash/OTP1/bootloader */
#define FMC_FLAG_WPERR                 FMC_STAT_WPERR                                       /*!< FMC erase/program protection error flag bit */
#define FMC_FLAG_PGAERR                FMC_STAT_PGAERR                                      /*!< FMC program alignment error flag bit */
#define FMC_FLAG_PGMERR                FMC_STAT_PGMERR                                      /*!< FMC program size not match error flag bit */
#define FMC_FLAG_PGSERR                FMC_STAT_PGSERR                                      /*!< FMC program sequence error flag bit */
#define FMC_FLAG_RDCERR                FMC_STAT_RDCERR                                      /*!< FMC CBUS data read protection error flag bit */
#define FMC_FLAG_BUSY                  FMC_STAT_BUSY                                        /*!< FMC busy flag */

/* FMC interrupt flags */
#define FMC_INT_FLAG_END               FMC_STAT_END                                         /*!< FMC end of operation interrupt flag */
#define FMC_INT_FLAG_OPERR             FMC_STAT_OPERR                                       /*!< FMC operation error interrupt flag */
#define FMC_INT_FLAG_LDECCDET          FMC_STAT_LDECCDET                                    /*!< FMC two bits ECC error when load code from flash/OTP1/bootloader interrupt flag */
#define FMC_INT_FLAG_WPERR             FMC_STAT_WPERR                                       /*!< FMC erase/program protection error interrupt flag */
#define FMC_INT_FLAG_PGAERR            FMC_STAT_PGAERR                                      /*!< FMC program alignment error interrupt flag */
#define FMC_INT_FLAG_PGMERR            FMC_STAT_PGMERR                                      /*!< FMC program size not match error interrupt flag */
#define FMC_INT_FLAG_PGSERR            FMC_STAT_PGSERR                                      /*!< FMC program sequence error interrupt flag */
#define FMC_INT_FLAG_RDCERR            FMC_STAT_RDCERR                                      /*!< FMC CBUS data read protection error interrupt flag */

/* FMC time out */
#define FMC_TIMEOUT_COUNT              ((uint32_t)0x4FFFFFFFU)                              /*!< count to judge of FMC timeout */

/* EFUSE flags */
#define EFUSE_PGIF                     EFUSE_CS_PGIF                                    /*!< programming operation completion flag */
#define EFUSE_RDIF                     EFUSE_CS_RDIF                                    /*!< read operation completion flag */
#define EFUSE_OBERIF                   EFUSE_CS_OVBERIF                                 /*!< overstep boundary error flag */

/* EFUSE flags clear */
#define EFUSE_PGIC                     EFUSE_CS_PGIC                                    /*!< clear programming operation completion flag */
#define EFUSE_RDIC                     EFUSE_CS_RDIC                                    /*!< clear read operation completion flag */
#define EFUSE_OBERIC                   EFUSE_CS_OVBERIC                                 /*!< clear overstep boundary error flag */

/* EFUSE interrupt enable */
#define EFUSE_INT_OBER                 EFUSE_CS_OVBERIE                                 /*!< overstep boundary error interrupt enable */
#define EFUSE_INT_PG                   EFUSE_CS_PGIE                                    /*!< programming operation completion interrupt enable */
#define EFUSE_INT_RD                   EFUSE_CS_RDIE                                    /*!< read operation completion interrupt enable */

/* EFUSE interrupt flags */
#define EFUSE_INT_OBERIF               EFUSE_CS_OVBERIF                                 /*!< overstep boundary error interrupt flag */
#define EFUSE_INT_PGIF                 EFUSE_CS_PGIF                                    /*!< programming operation completion interrupt flag */
#define EFUSE_INT_RDIF                 EFUSE_CS_RDIF                                    /*!< read operation completion interrupt flag */

/* EFUSE interrupt flags clear */
#define EFUSE_INT_OBERIC               EFUSE_CS_OVBERIC                                 /*!< clear overstep boundary error interrupt flag */
#define EFUSE_INT_PGIC                 EFUSE_CS_PGIC                                    /*!< clear programming operation completion interrupt flag */
#define EFUSE_INT_RDIC                 EFUSE_CS_RDIC                                    /*!< clear read operation completion interrupt flag */

/* EFUSE macro address */
#define EFUSE_CTL_EFADDR               ((uint32_t)0x00000001U)                              /*!< efuse control address */
#define USER_DATA_EFADDR               ((uint32_t)0x00000002U)                              /*!< user data address */

/* EFUSE time out */
#define EFUSE_TIMEOUT_COUNT            ((uint32_t)0x0000FFFFU)                              /*!< count to judge of EFUSE timeout */

/* OTP0 address */
#define OTP0_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FFF7800U)                              /*!< OTP0 data block base address */
#define OTP0_LOCK_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FFF7840U)                              /*!< OTP0 lock block base address */

/* OTP1 address */
#define OTP1_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FF00000U)                              /*!< OTP1 data block base address */
#define OTP1_LOCK_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FF20200U)                              /*!< OTP1 lock block base address */

/* OTP2 address */
#define OTP2_DATA_BLOCK_BASE_ADDRESS   ((uint32_t)0x1FF20000U)                              /*!< OTP2 data block base address */
#define OTP2_WLOCK_BLOCK_BASE_ADDRESS  ((uint32_t)0x1FF20210U)                              /*!< OTP2 write lock block base address */
#define OTP2_RLOCK_BLOCK_BASE_ADDRESS  ((uint32_t)0x1FF20220U)                              /*!< OTP2 read lock block base address */

/* OTP1 data blockx read enable */
#define OTP1_DATA_BLOCK_0                        BIT(0)                      /*!< erase/program protection of sector 0  */
#define OTP1_DATA_BLOCK_1                        BIT(1)                      /*!< erase/program protection of sector 1  */
#define OTP1_DATA_BLOCK_2                        BIT(2)                      /*!< erase/program protection of sector 2  */
#define OTP1_DATA_BLOCK_3                        BIT(3)                      /*!< erase/program protection of sector 3  */
#define OTP1_DATA_BLOCK_4                        BIT(4)                      /*!< erase/program protection of sector 4  */
#define OTP1_DATA_BLOCK_5                        BIT(5)                      /*!< erase/program protection of sector 5  */
#define OTP1_DATA_BLOCK_6                        BIT(6)                      /*!< erase/program protection of sector 6  */
#define OTP1_DATA_BLOCK_7                        BIT(7)                      /*!< erase/program protection of sector 7  */
#define OTP1_DATA_BLOCK_8                        BIT(8)                      /*!< erase/program protection of sector 8  */
#define OTP1_DATA_BLOCK_9                        BIT(9)                      /*!< erase/program protection of sector 9  */
#define OTP1_DATA_BLOCK_10                       BIT(10)                     /*!< erase/program protection of sector 10 */
#define OTP1_DATA_BLOCK_11                       BIT(11)                     /*!< erase/program protection of sector 11 */
#define OTP1_DATA_BLOCK_12                       BIT(12)                     /*!< erase/program protection of sector 12 */
#define OTP1_DATA_BLOCK_13                       BIT(13)                     /*!< erase/program protection of sector 13 */
#define OTP1_DATA_BLOCK_14                       BIT(14)                     /*!< erase/program protection of sector 14 */
#define OTP1_DATA_BLOCK_15                       BIT(15)                     /*!< erase/program protection of sector 15 */
#define OTP1_DATA_BLOCK_ALL                      BITS(0,15)                  /*!< ALL erase/program protection of sector */

/* constants definitions */
/* fmc state */
typedef enum {
    FMC_READY = 0U,                                                                          /*!< the operation has been completed */
    FMC_BUSY,                                                                               /*!< the operation is in progress */
    FMC_RDCERR,                                                                             /*!< CBUS data read protection error */
    FMC_PGSERR,                                                                             /*!< program sequence error */
    FMC_PGMERR,                                                                             /*!< program size not match error */
    FMC_PGAERR,                                                                             /*!< program alignment error */
    FMC_WPERR,                                                                              /*!< erase/program protection error */
    FMC_OPERR,                                                                              /*!< operation error */
    FMC_LDECCDET,                                                                           /*!< two bits ECC error when load code from flash/OTP1/bootloader */
    FMC_TOERR                                                                               /*!< timeout error */
} fmc_state_enum;

/* EFUSE state */
typedef enum {
    EFUSE_READY = 0U,                                                                       /*!< EFUSE operation has been completed */
    EFUSE_BUSY,                                                                             /*!< EFUSE operation is in progress */
    EFUSE_OBER,                                                                             /*!< EFUSE overstep boundary error */
    EFUSE_TOERR                                                                             /*!< EFUSE timeout error */
} efuse_state_enum;

/* function declarations */
/* FMC main memory programming functions */
/* unlock the main FMC operation */
void fmc_unlock(void);
/* lock the main FMC operation */
void fmc_lock(void);
/* FMC erase page */
fmc_state_enum fmc_page_erase(uint32_t page_addr);
/* FMC erase sector */
fmc_state_enum fmc_sector_erase(uint32_t fmc_sector);
/* FMC erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* FMC erase whole bank0 */
fmc_state_enum fmc_bank0_erase(void);
/* FMC erase whole bank1(include bank1_ex) */
fmc_state_enum fmc_bank1_erase(void);
/* FMC program a double word at the corresponding address */
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);
/* FMC program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);
/* FMC program a half word at the corresponding address */
fmc_state_enum fmc_halfword_program(uint32_t address, uint16_t data);
/* FMC program a byte at the corresponding address */
fmc_state_enum fmc_byte_program(uint32_t address, uint8_t data);

/* enable no waitinging time area load after system reset */
void fmc_nwa_enable(void);
/* disable no waiting time area load after system reset */
void fmc_nwa_disable(void);
/* set OTP1 data block not be read */
void otp1_read_disable(uint32_t block);
/* enable read lock block protection for OTP2 */
void otp2_rlock_enable(void);

/* FMC option bytes programming functions */
/* unlock the option byte operation */
void ob_unlock(void);
/* lock the option byte operation */
void ob_lock(void);
/* send option byte change command */
void ob_start(void);
/* erase option byte */
void ob_erase(void);
/* enable write protect */
ErrStatus ob_write_protection_enable(uint64_t ob_wp);
/* disable write protect */
ErrStatus ob_write_protection_disable(uint64_t ob_wp);
/* enable erase/program protection and CBUS read protection */
void ob_drp_enable(uint64_t ob_drp);
/* disable all erase/program protection and CBUS read protection */
void ob_drp_disable(void);
/* configure security protection level */
void ob_security_protection_config(uint8_t ob_spc);
/* program the FMC user option byte */
void ob_user_write(uint32_t ob_fwdgt, uint32_t ob_deepsleep, uint32_t ob_stdby);
/* program the option byte BOR threshold value */
void ob_user_bor_threshold(uint32_t ob_bor_th);
/* configure the option byte boot bank value */
void ob_boot_mode_config(uint32_t boot_mode);
/* configure FMC/SRAM ECC checking, only valid after power reset */
void ob_ecc_config(uint32_t ecc_config);
/* select no waiting time area, only valid after power reset, only for 4MB dual bank series */
void ob_nwa_select(uint32_t nwa_select);
/* get the FMC user option byte */
uint8_t ob_user_get(void);
/* get the FMC option byte write protection of bank0 */
uint32_t ob_write_protection0_get(void);
/* get the FMC option byte write protection of bank1 */
uint32_t ob_write_protection1_get(void);
/* get the FMC erase/program protection and CBUS read protection option bytes value of bank0 */
uint32_t ob_drp0_get(void);
/* get the FMC erase/program protection and CBUS read protection option bytes value of bank1 */
uint32_t ob_drp1_get(void);
/* get option byte security protection code value */
FlagStatus ob_spc_get(void);
/* get the FMC option byte BOR threshold value */
uint32_t ob_user_bor_threshold_get(void);
/* get the boot mode */
uint32_t ob_boot_mode_get(void);
/* get FMC/SRAM ECC checking */
uint32_t ob_ecc_get(void);
/* get no waiting time area */
uint32_t ob_nwa_get(void);

/* FMC interrupts and flags management functions */
/* get flag set or reset */
FlagStatus fmc_flag_get(uint32_t fmc_flag);
/* clear the FMC pending flag */
void fmc_flag_clear(uint32_t fmc_flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(uint32_t fmc_int);
/* disable FMC interrupt */
void fmc_interrupt_disable(uint32_t fmc_int);
/* get FMC interrupt flag set or reset */
FlagStatus fmc_interrupt_flag_get(uint32_t fmc_int_flag);
/* clear the FMC interrupt flag */
void fmc_interrupt_flag_clear(uint32_t fmc_int_flag);
/* get the FMC state */
fmc_state_enum fmc_state_get(void);
/* check whether FMC is ready or not */
fmc_state_enum fmc_ready_wait(uint32_t timeout);

/* EFUSE operation functions */
/* unlock the EFUSE_CTL register */
void efuse_ctrl_unlock(void);
/* lock the EFUSE_CTL register */
void efuse_ctrl_lock(void);
/* unlock the EFUSE_USER_DATA register */
void efuse_user_data_unlock(void);
/* lock the EFUSE_USER_DATA register */
void efuse_user_data_lock(void);
/* read EFUSE value */
efuse_state_enum efuse_read(uint32_t ef_addr, uint32_t size, uint32_t buf[]);
/* write EFUSE */
efuse_state_enum efuse_write(uint32_t ef_addr, uint32_t size, uint8_t ef_data);
/* write efuse control parameter */
efuse_state_enum efuse_control_write(uint8_t ef_data);
/* write user data parameter */
efuse_state_enum efuse_user_data_write(uint8_t ef_data);

/* flag and interrupt functions */
/* check EFUSE flag is set or not */
FlagStatus efuse_flag_get(uint32_t efuse_flag);
/* clear EFUSE pending flag */
void efuse_flag_clear(uint32_t efuse_cflag);
/* enable EFUSE interrupt */
void efuse_interrupt_enable(uint32_t source);
/* disable EFUSE interrupt */
void efuse_interrupt_disable(uint32_t source);
/* check EFUSE interrupt flag is set or not */
FlagStatus efuse_interrupt_flag_get(uint32_t int_flag);
/* clear EFUSE pending interrupt flag */
void efuse_interrupt_flag_clear(uint32_t int_cflag);
/* check EFUSE operation ready or not */
efuse_state_enum efuse_ready_wait(uint32_t efuse_flag, uint32_t timeout);

#endif /* GD32F5XX_FMC_H */
