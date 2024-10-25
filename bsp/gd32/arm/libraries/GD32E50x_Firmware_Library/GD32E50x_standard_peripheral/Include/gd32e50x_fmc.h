/*!
    \file    gd32e50x_fmc.h
    \brief   definitions for the FMC

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32E50X_FMC_H
#define GD32E50X_FMC_H

#include "gd32e50x.h"

/* FMC and option bytes definition */
#define FMC                        FMC_BASE                                         /*!< FMC base address */
#define OB                         OB_BASE                                          /*!< option bytes base address */

/* registers definitions */
#define FMC_WS                     REG32(FMC + 0x00000000U)                         /*!< FMC wait state register */
#define FMC_KEY                    REG32(FMC + 0x00000004U)                         /*!< FMC unlock key register */
#define FMC_OBKEY                  REG32(FMC + 0x00000008U)                         /*!< FMC option bytes unlock key register */
#define FMC_STAT                   REG32(FMC + 0x0000000CU)                         /*!< FMC status register */
#define FMC_CTL                    REG32(FMC + 0x00000010U)                         /*!< FMC control register */
#define FMC_ADDR                   REG32(FMC + 0x00000014U)                         /*!< FMC address register */
#define FMC_OBSTAT                 REG32(FMC + 0x0000001CU)                         /*!< FMC option bytes status register */
#define FMC_WP                     REG32(FMC + 0x00000020U)                         /*!< FMC erase/program protection register */
#define FMC_PID                    REG32(FMC + 0x00000100U)                         /*!< FMC product ID register */

#define OP_BYTE(x)                 REG32(OB + ((uint32_t)((uint32_t)0x04U * (x))))  /*!< option bytes value */
#define OB_SPC_USER                REG32(OB + 0x00000000U)                          /*!< option bytes security protection value and user value */
#define OB_DATA                    REG32(OB + 0x00000004U)                          /*!< option bytes data value */
#define OB_WP0                     REG32(OB + 0x00000008U)                          /*!< option bytes write protection value 0 */
#define OB_WP1                     REG32(OB + 0x0000000CU)                          /*!< option bytes write protection value 1 */

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT               BITS(0,2)                                        /*!< wait state counter */
#define FMC_WS_PFEN                BIT(4)                                           /*!< pre-fetch enable */
#define FMC_WS_ICEN                BIT(9)                                           /*!< IBUS cache enable */
#define FMC_WS_DCEN                BIT(10)                                          /*!< DBUS cache enable */
#define FMC_WS_ICRST               BIT(11)                                          /*!< IBUS cache reset */
#define FMC_WS_DCRST               BIT(12)                                          /*!< DBUS cache reset */

/* FMC_KEY */
#define FMC_KEY_KEY                BITS(0,31)                                       /*!< FMC_CTL unlock key */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY            BITS(0,31)                                       /*!< option bytes unlock key */

/* FMC_STAT */
#define FMC_STAT_BUSY              BIT(0)                                           /*!< flash busy flag */
#define FMC_STAT_PGERR             BIT(2)                                           /*!< flash program error flag */
#define FMC_STAT_PGAERR            BIT(3)                                           /*!< flash program alignment error flag */
#define FMC_STAT_WPERR             BIT(4)                                           /*!< erase/program protection error flag */
#define FMC_STAT_ENDF              BIT(5)                                           /*!< end of operation flag */

/* FMC_CTL */
#define FMC_CTL_PG                 BIT(0)                                           /*!< main flash program command */
#define FMC_CTL_PER                BIT(1)                                           /*!< main flash page erase command */
#define FMC_CTL_MER                BIT(2)                                           /*!< main flash mass erase command */
#define FMC_CTL_OBPG               BIT(4)                                           /*!< option bytes program command */
#define FMC_CTL_OBER               BIT(5)                                           /*!< option bytes erase command */
#define FMC_CTL_START              BIT(6)                                           /*!< send erase command to FMC */
#define FMC_CTL_LK                 BIT(7)                                           /*!< FMC_CTL lock */
#define FMC_CTL_OBWEN              BIT(9)                                           /*!< option bytes erase/program enable */
#define FMC_CTL_ERRIE              BIT(10)                                          /*!< error interrupt enable */
#define FMC_CTL_ENDIE              BIT(12)                                          /*!< end of operation interrupt enable */

/* FMC_ADDR */
#define FMC_ADDR_ADDR              BITS(0,31)                                       /*!< address of flash to be erased/programmed */

/* FMC_OBSTAT */
#define FMC_OBSTAT_OBERR           BIT(0)                                           /*!< option bytes read error */
#define FMC_OBSTAT_SPC             BIT(1)                                           /*!< option bytes security protection code */
#define FMC_OBSTAT_USER            BITS(2,9)                                        /*!< store USER of option bytes block after system reset */
#define FMC_OBSTAT_DATA            BITS(10,25)                                      /*!< store DATA of option bytes block after system reset */

/* FMC_WP */
#define FMC_WP_WP                  BITS(0,31)                                       /*!< store WP of option bytes block after system reset */

/* FMC_PID */
#define FMC_PID_PID                BITS(0,31)                                       /*!< product ID */

/* constants definitions */
/* fmc state */
typedef enum
{
    FMC_READY,                                                                      /*!< the operation has been completed */
    FMC_BUSY,                                                                       /*!< the operation is in progress */
    FMC_PGERR,                                                                      /*!< program error */
    FMC_PGAERR,                                                                     /*!< program alignment error */
    FMC_WPERR,                                                                      /*!< erase/program protection error */
    FMC_TOERR,                                                                      /*!< timeout error */
    FMC_OB_HSPC,                                                                    /*!< high security protection */
}fmc_state_enum;

/* unlock key */
#define UNLOCK_KEY0                ((uint32_t)0x45670123U)                          /*!< unlock key 0 */
#define UNLOCK_KEY1                ((uint32_t)0xCDEF89ABU)                          /*!< unlock key 1 */

/* FMC wait state added */
#define WS_WSCNT(regval)           (BITS(0,2) & ((uint32_t)(regval)))
#define FMC_WAIT_STATE_0           WS_WSCNT(0)                                      /*!< 0 wait state added */
#define FMC_WAIT_STATE_1           WS_WSCNT(1)                                      /*!< 1 wait state added */
#define FMC_WAIT_STATE_2           WS_WSCNT(2)                                      /*!< 2 wait state added */
#define FMC_WAIT_STATE_3           WS_WSCNT(3)                                      /*!< 3 wait state added */
#define FMC_WAIT_STATE_4           WS_WSCNT(4)                                      /*!< 4 wait state added */

/* read protection configuration */
#define FMC_NSPC                   ((uint8_t)0xA5U)                                 /*!< no security protection */
#define FMC_LSPC                   ((uint8_t)0xBBU)                                 /*!< low security protection */
#define FMC_HSPC                   ((uint8_t)0xCCU)                                 /*!< high security protection */

/* option bytes software/hardware free watch dog timer */
#define OB_FWDGT_HW                ((uint8_t)0x00U)                                 /*!< hardware free watchdog */
#define OB_FWDGT_SW                ((uint8_t)0x01U)                                 /*!< software free watchdog */

/* option bytes reset or not entering deep sleep mode */
#define OB_DEEPSLEEP_RST           ((uint8_t)0x00U)                                 /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST          ((uint8_t)0x02U)                                 /*!< no reset when entering deepsleep mode */

/* option bytes reset or not entering standby mode */
#define OB_STDBY_RST               ((uint8_t)0x00U)                                 /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST              ((uint8_t)0x04U)                                 /*!< no reset when entering standby mode */

/* option bytes BOR threshold value */
#define OB_BOR_TH_VALUE3           ((uint8_t)0x00U)                                 /*!< BOR threshold value 3 */
#define OB_BOR_TH_VALUE2           ((uint8_t)0x40U)                                 /*!< BOR threshold value 2 */
#define OB_BOR_TH_VALUE1           ((uint8_t)0x80U)                                 /*!< BOR threshold value 1 */
#define OB_BOR_TH_OFF              ((uint8_t)0xC0U)                                 /*!< no BOR function */

/* option bytes write protection */
#define OB_WP_NONE                 ((uint32_t)0x00000000U)                          /*!< disable all erase/program protection */
#define OB_WP_0                    ((uint32_t)0x00000001U)                          /*!< erase/program protection of sector 0  */
#define OB_WP_1                    ((uint32_t)0x00000002U)                          /*!< erase/program protection of sector 1  */
#define OB_WP_2                    ((uint32_t)0x00000004U)                          /*!< erase/program protection of sector 2  */
#define OB_WP_3                    ((uint32_t)0x00000008U)                          /*!< erase/program protection of sector 3  */
#define OB_WP_4                    ((uint32_t)0x00000010U)                          /*!< erase/program protection of sector 4  */
#define OB_WP_5                    ((uint32_t)0x00000020U)                          /*!< erase/program protection of sector 5  */
#define OB_WP_6                    ((uint32_t)0x00000040U)                          /*!< erase/program protection of sector 6  */
#define OB_WP_7                    ((uint32_t)0x00000080U)                          /*!< erase/program protection of sector 7  */
#define OB_WP_8                    ((uint32_t)0x00000100U)                          /*!< erase/program protection of sector 8  */
#define OB_WP_9                    ((uint32_t)0x00000200U)                          /*!< erase/program protection of sector 9  */
#define OB_WP_10                   ((uint32_t)0x00000400U)                          /*!< erase/program protection of sector 10 */
#define OB_WP_11                   ((uint32_t)0x00000800U)                          /*!< erase/program protection of sector 11 */
#define OB_WP_12                   ((uint32_t)0x00001000U)                          /*!< erase/program protection of sector 12 */
#define OB_WP_13                   ((uint32_t)0x00002000U)                          /*!< erase/program protection of sector 13 */
#define OB_WP_14                   ((uint32_t)0x00004000U)                          /*!< erase/program protection of sector 14 */
#define OB_WP_15                   ((uint32_t)0x00008000U)                          /*!< erase/program protection of sector 15 */
#define OB_WP_16                   ((uint32_t)0x00010000U)                          /*!< erase/program protection of sector 16 */
#define OB_WP_17                   ((uint32_t)0x00020000U)                          /*!< erase/program protection of sector 17 */
#define OB_WP_18                   ((uint32_t)0x00040000U)                          /*!< erase/program protection of sector 18 */
#define OB_WP_19                   ((uint32_t)0x00080000U)                          /*!< erase/program protection of sector 19 */
#define OB_WP_20                   ((uint32_t)0x00100000U)                          /*!< erase/program protection of sector 20 */
#define OB_WP_21                   ((uint32_t)0x00200000U)                          /*!< erase/program protection of sector 21 */
#define OB_WP_22                   ((uint32_t)0x00400000U)                          /*!< erase/program protection of sector 22 */
#define OB_WP_23                   ((uint32_t)0x00800000U)                          /*!< erase/program protection of sector 23 */
#define OB_WP_24                   ((uint32_t)0x01000000U)                          /*!< erase/program protection of sector 24 */
#define OB_WP_25                   ((uint32_t)0x02000000U)                          /*!< erase/program protection of sector 25 */
#define OB_WP_26                   ((uint32_t)0x04000000U)                          /*!< erase/program protection of sector 26 */
#define OB_WP_27                   ((uint32_t)0x08000000U)                          /*!< erase/program protection of sector 27 */
#define OB_WP_28                   ((uint32_t)0x10000000U)                          /*!< erase/program protection of sector 28 */
#define OB_WP_29                   ((uint32_t)0x20000000U)                          /*!< erase/program protection of sector 29 */
#define OB_WP_30                   ((uint32_t)0x40000000U)                          /*!< erase/program protection of sector 30 */
#define OB_WP_31                   ((uint32_t)0x80000000U)                          /*!< erase/program protection of sector 31 ~ 63 */
#define OB_WP_ALL                  ((uint32_t)0xFFFFFFFFU)                          /*!< erase/program protection of all sectors */

/* FMC interrupt enable */
#define FMC_INT_ERR                FMC_CTL_ERRIE                                    /*!< FMC error interrupt enable */
#define FMC_INT_END                FMC_CTL_ENDIE                                    /*!< FMC end of operation interrupt enable */

/* FMC flags */
#define FMC_FLAG_BUSY              FMC_STAT_BUSY                                    /*!< FMC busy flag */
#define FMC_FLAG_PGERR             FMC_STAT_PGERR                                   /*!< FMC operation error flag */
#define FMC_FLAG_PGAERR            FMC_STAT_PGAERR                                  /*!< FMC program alignment error flag */
#define FMC_FLAG_WPERR             FMC_STAT_WPERR                                   /*!< FMC erase/program protection error flag */
#define FMC_FLAG_END               FMC_STAT_ENDF                                    /*!< FMC end of operation flag */

/* FMC interrupt flags */
#define FMC_INT_FLAG_PGERR         FMC_STAT_PGERR                                   /*!< FMC operation error interrupt flag */
#define FMC_INT_FLAG_PGAERR        FMC_STAT_PGAERR                                  /*!< FMC program alignment error interrupt flag */
#define FMC_INT_FLAG_WPERR         FMC_STAT_WPERR                                   /*!< FMC erase/program protection error interrupt flag */
#define FMC_INT_FLAG_END           FMC_STAT_ENDF                                    /*!< FMC end of operation interrupt flag */

/* FMC timeout */
#define FMC_TIMEOUT_COUNT          ((uint32_t)0x00100000U)                          /*!< FMC timeout count value */

/* function declarations */
/* FMC main memory programming functions */
/* unlock the main FMC operation */
void fmc_unlock(void);
/* lock the main FMC operation */
void fmc_lock(void);
/* set the wait state */
void fmc_wscnt_set(uint32_t wscnt);
/* enable pre-fetch */
void fmc_prefetch_enable(void);
/* disable pre-fetch */
void fmc_prefetch_disable(void);
/* enable IBUS cache */
void fmc_ibus_enable(void);
/* disable IBUS cache */
void fmc_ibus_disable(void);
/* reset IBUS cache  */
void fmc_ibus_reset(void);
/* enable DBUS cache */
void fmc_dbus_enable(void);
/* disable DBUS cache */
void fmc_dbus_disable(void);
/* reset DBUS cache */
void fmc_dbus_reset(void);
/* FMC erase page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* FMC erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* FMC program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);

/* FMC option bytes programming functions */
/* unlock the option bytes operation */
void ob_unlock(void);
/* lock the option bytes operation */
void ob_lock(void);
/* erase the option bytes */
fmc_state_enum ob_erase(void);
/* enable write protection */
fmc_state_enum ob_write_protection_enable(uint32_t ob_wp);
/* configure the option bytes security protection */
fmc_state_enum ob_security_protection_config(uint8_t ob_spc);
/* program option bytes USER */
fmc_state_enum ob_user_write(uint8_t ob_fwdgt, uint8_t ob_deepsleep, uint8_t ob_stdby, uint8_t ob_bor_th);
/* program option bytes DATA */
fmc_state_enum ob_data_program(uint16_t ob_data);
/* get the value of option bytes USER */
uint8_t ob_user_get(void);
/* get the value of option bytes DATA */
uint16_t ob_data_get(void);
/* get the value of option bytes write protection */
uint32_t ob_write_protection_get(void);
/* get option bytes security protection state */
FlagStatus ob_security_protection_flag_get(void);

/* FMC interrupts and flags management functions */
/* get FMC flag status */
FlagStatus fmc_flag_get(uint32_t flag);
/* clear the FMC flag */
void fmc_flag_clear(uint32_t flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(uint32_t interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(uint32_t interrupt);
/* get FMC interrupt flag */
FlagStatus fmc_interrupt_flag_get(uint32_t flag);
/* clear FMC interrupt flag */
void fmc_interrupt_flag_clear(uint32_t flag);

#endif /* GD32E50X_FMC_H */
