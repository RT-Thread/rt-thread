/*!
    \file  gd32e230_fmc.h
    \brief definitions for the FMC

    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#ifndef GD32E230_FMC_H
#define GD32E230_FMC_H

#include "gd32e230.h"

/* FMC and option byte definition */
#define FMC                     FMC_BASE                    /*!< FMC register base address */
#define OB                      OB_BASE                     /*!< option byte base address */

/* registers definitions */
#define FMC_WS                  REG32((FMC) + 0x00U)        /*!< FMC wait state register */
#define FMC_KEY                 REG32((FMC) + 0x04U)        /*!< FMC unlock key register */
#define FMC_OBKEY               REG32((FMC) + 0x08U)        /*!< FMC option bytes unlock key register */
#define FMC_STAT                REG32((FMC) + 0x0CU)        /*!< FMC status register */
#define FMC_CTL                 REG32((FMC) + 0x10U)        /*!< FMC control register */
#define FMC_ADDR                REG32((FMC) + 0x14U)        /*!< FMC address register */
#define FMC_OBSTAT              REG32((FMC) + 0x1CU)        /*!< FMC option bytes status register */
#define FMC_WP                  REG32((FMC) + 0x20U)        /*!< FMC write protection register */
#define FMC_PID                 REG32((FMC) + 0x100U)       /*!< FMC product ID register */

#define OB_SPC_USER             REG32((OB) + 0x00U)         /*!< option byte security protection value and user value */
#define OB_DATA                 REG32((OB) + 0x04U)         /*!< option byte data value*/
#define OB_WP                   REG32((OB) + 0x08U)         /*!< option byte write protection */

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT            BITS(0,2)                   /*!< wait state counter */
#define FMC_WS_PFEN             BIT(4)                      /*!< pre-fetch enable */
#define FMC_WS_PGW              BIT(15)                     /*!< program width to flash memory */

/* FMC_KEY */
#define FMC_KEY_KEY             BITS(0,31)                  /*!< FMC main flash unlock key bits */

/* FMC_OBKEY */
#define FMC_OBKEY_OBKEY         BITS(0,31)                  /*!< option bytes unlock key bits */

/* FMC_STAT */
#define FMC_STAT_BUSY           BIT(0)                      /*!< flash busy flag bit */
#define FMC_STAT_PGERR          BIT(2)                      /*!< flash program error flag bit */
#define FMC_STAT_PGAERR         BIT(3)                      /*!< program alignment error flag bit */
#define FMC_STAT_WPERR          BIT(4)                      /*!< flash write protection error flag bit */
#define FMC_STAT_ENDF           BIT(5)                      /*!< end of operation flag bit */

/* FMC_CTL */
#define FMC_CTL_PG              BIT(0)                      /*!< main flash program command bit */
#define FMC_CTL_PER             BIT(1)                      /*!< main flash page erase bit */
#define FMC_CTL_MER             BIT(2)                      /*!< main flash mass erase bit */
#define FMC_CTL_OBPG            BIT(4)                      /*!< option bytes program command bit */
#define FMC_CTL_OBER            BIT(5)                      /*!< option bytes erase command bit */
#define FMC_CTL_START           BIT(6)                      /*!< send erase command to FMC bit */
#define FMC_CTL_LK              BIT(7)                      /*!< flash lock bit */
#define FMC_CTL_OBWEN           BIT(9)                      /*!< option bytes erase/program enable bit */
#define FMC_CTL_ERRIE           BIT(10)                     /*!< error interrupt enable bit */
#define FMC_CTL_ENDIE           BIT(12)                     /*!< end of operation interrupt enable bit */
#define FMC_CTL_OBRLD           BIT(13)                     /*!< option bytes reload bit */

/* FMC_ADDR */
#define FMC_ADDR_ADDR           BITS(0,31)                  /*!< flash command address bits */

/* FMC_OBSTAT */
#define FMC_OBSTAT_OBERR        BIT(0)                      /*!< option bytes read error bit */
#define FMC_OBSTAT_PLEVEL_BIT0  BIT(1)                      /*!< protection level bit 0 */
#define FMC_OBSTAT_PLEVEL_BIT1  BIT(2)                      /*!< protection level bit 1 */
#define FMC_OBSTAT_USER         BITS(8,15)                  /*!< option bytes user bits */
#define FMC_OBSTAT_DATA         BITS(16,31)                 /*!< option byte data bits */

/* FMC_WP */
#define FMC_WP_WP               BITS(0,15)                  /*!< store WP[15:0] of option byte block after system reset */

/* FMC_PID */
#define FMC_PID_PID             BITS(0,31)                  /*!< product ID bits */

/* constants definitions */
/* fmc state */
typedef enum
{
    FMC_READY,                                              /*!< the operation has been completed */
    FMC_BUSY,                                               /*!< the operation is in progress */
    FMC_PGERR,                                              /*!< program error */
    FMC_PGAERR,                                             /*!< program alignment error */
    FMC_WPERR,                                              /*!< erase/program protection error */
    FMC_TOERR,                                              /*!< timeout error */
    FMC_OB_HSPC                                             /*!< option byte security protection code high */
}fmc_state_enum;

/* unlock key */
#define UNLOCK_KEY0                ((uint32_t)0x45670123U)  /*!< unlock key 0 */
#define UNLOCK_KEY1                ((uint32_t)0xCDEF89ABU)  /*!< unlock key 1 */

/* wait state counter value */
#define WS_WSCNT_0                 ((uint8_t)0x00U)         /*!< 0 wait state added */
#define WS_WSCNT_1                 ((uint8_t)0x01U)         /*!< 1 wait state added */
#define WS_WSCNT_2                 ((uint8_t)0x02U)         /*!< 2 wait state added */

/* read protect configure */
#define FMC_NSPC                   ((uint16_t)0x5AA5U)      /*!< no security protection */
#define FMC_LSPC                   ((uint16_t)0x44BBU)      /*!< low security protection, any value except 0xA5 or 0xCC */
#define FMC_HSPC                   ((uint16_t)0x33CCU)      /*!< high security protection */

#define LOW_16BITS_MASK            ((uint32_t)0x0000FFFFU)  /*!< low 16 bits mask  */
#define HIGH_16BITS_MASK           ((uint32_t)0xFFFF0000U)  /*!< high 16 bits mask  */

/* option byte address */
#define OB_SPC_USER_ADDRESS        ((uint32_t)0x1FFFF800U)  /*!< address of option byte security protection and user */
#define OB_DATA_ADDRESS            ((uint32_t)0x1FFFF804U)  /*!< address of option byte data */
#define OB_WP_ADDRESS              ((uint32_t)0x1FFFF808U)  /*!< address of option byte write protection */

/* option byte write protection */
#define OB_LWP                     ((uint32_t)0x000000FFU)  /*!< write protection low bits */
#define OB_HWP                     ((uint32_t)0x0000FF00U)  /*!< write protection high bits */

/* option byte software/hardware free watchdog timer */  
#define OB_FWDGT_HW                ((uint8_t)(~BIT(0)))     /*!< hardware free watchdog timer */
#define OB_FWDGT_SW                ((uint8_t)BIT(0))        /*!< software free watchdog timer */

/* option byte reset or not entering deep sleep mode */
#define OB_DEEPSLEEP_RST           ((uint8_t)(~BIT(1)))     /*!< generate a reset instead of entering deepsleep mode */
#define OB_DEEPSLEEP_NRST          ((uint8_t)BIT(1))        /*!< no reset when entering deepsleep mode */

/* option byte reset or not entering standby mode */
#define OB_STDBY_RST               ((uint8_t)(~BIT(2)))     /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST              ((uint8_t)BIT(2))        /*!< no reset when entering deepsleep mode */

/* option byte OB_BOOT1_n set */
#define OB_BOOT1_SET_1             ((uint8_t)(~BIT(4)))     /*!< BOOT1 bit is 1 */
#define OB_BOOT1_SET_0             ((uint8_t)BIT(4))        /*!< BOOT1 bit is 0 */

/* option byte VDDA monitor enable/disable */
#define OB_VDDA_DISABLE            ((uint8_t)(~BIT(5)))     /*!< disable VDDA monitor */
#define OB_VDDA_ENABLE             ((uint8_t)BIT(5))        /*!< enable VDDA monitor */

/* option byte SRAM parity enable/disable */
#define OB_SRAM_PARITY_ENABLE      ((uint8_t)(~BIT(6)))     /*!< enable SRAM parity check */
#define OB_SRAM_PARITY_DISABLE     ((uint8_t)BIT(6))        /*!< disable SRAM parity check */

/* option byte security protection level in FMC_OBSTAT register */
#define OB_OBSTAT_PLEVEL_NO        ((uint8_t)0x00U)         /*!< no security protection */
#define OB_OBSTAT_PLEVEL_LOW       ((uint8_t)0x01U)         /*!< low security protection */
#define OB_OBSTAT_PLEVEL_HIGH      ((uint8_t)0x03U)         /*!< high security protection */

/* option byte user mask */
#define OB_USER_MASK               ((uint8_t)0x88U)         /*!< OB_USER reserved bit mask */

/* option byte data address */
#define OB_DATA_ADDR0              ((uint32_t)0x1FFFF804U)  /*!< option byte data address 0 */
#define OB_DATA_ADDR1              ((uint32_t)0x1FFFF806U)  /*!< option byte data address 1 */

/* FMC flags */
#define FMC_FLAG_BUSY              FMC_STAT_BUSY            /*!< FMC busy flag */
#define FMC_FLAG_PGERR             FMC_STAT_PGERR           /*!< FMC programming error flag */
#define FMC_FLAG_PGAERR            FMC_STAT_PGAERR          /*!< FMC program alignment error flag */
#define FMC_FLAG_WPERR             FMC_STAT_WPERR           /*!< FMC write protection error flag */
#define FMC_FLAG_END               FMC_STAT_ENDF            /*!< FMC end of programming flag */

/* FMC interrupt flags */
#define FMC_INT_FLAG_PGERR         FMC_STAT_PGERR           /*!< FMC programming error flag */
#define FMC_INT_FLAG_PGAERR        FMC_STAT_PGAERR          /*!< FMC program alignment error flag */
#define FMC_INT_FLAG_WPERR         FMC_STAT_WPERR           /*!< FMC write protection error flag */
#define FMC_INT_FLAG_END           FMC_STAT_ENDF            /*!< FMC end of programming flag */

/* FMC interrupt enable */
#define FMC_INTEN_END              FMC_CTL_ENDIE            /*!< enable FMC end of operation interrupt */
#define FMC_INTEN_ERR              FMC_CTL_ERRIE            /*!< enable FMC error interrupt */

/* FMC time out */
#define FMC_TIMEOUT_COUNT          ((uint32_t)0x000F0000U)  /*!< count to judge of FMC timeout */

/* function declarations */
/* FMC main memory programming functions */
/* unlock the main FMC operation */
void fmc_unlock(void);
/* lock the main FMC operation */
void fmc_lock(void);
/* set the wait state counter value */
void fmc_wscnt_set(uint8_t wscnt);

/* pre-fetch enable */
void fmc_prefetch_enable(void);
/* pre-fetch disable */
void fmc_prefetch_disable(void);
/* FMC erase page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* FMC erase whole chip */
fmc_state_enum fmc_mass_erase(void);
/* FMC program a double word at the corresponding address */
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);
/* FMC program a word at the corresponding address */
fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);

/* FMC option bytes programming functions */
/* unlock the option byte operation */
void ob_unlock(void);
/* lock the option byte operation */
void ob_lock(void);
/* reload the option byte and generate a system reset */
void ob_reset(void);
/* get option byte value */
uint32_t option_byte_value_get(uint32_t addr);
/* erase option byte */
fmc_state_enum ob_erase(void);
/* enable option byte write protection (OB_WP) */
fmc_state_enum ob_write_protection_enable(uint16_t ob_wp);
/* configure read out protect */
fmc_state_enum ob_security_protection_config(uint16_t ob_spc);
/* write the FMC option byte user */
fmc_state_enum ob_user_write(uint8_t ob_user);
/* write the FMC option byte data */
fmc_state_enum ob_data_program(uint16_t data);
/* get the FMC option byte OB_USER */
uint8_t ob_user_get(void);
/* get the FMC option byte OB_DATA */
uint16_t ob_data_get(void);
/* get the FMC option byte write protection */
uint16_t ob_write_protection_get(void);
/* get the value of FMC option byte security protection level (PLEVEL) in FMC_OBSTAT register */
uint32_t ob_obstat_plevel_get(void);

/* FMC interrupts and flags management functions */
/* enable FMC interrupt */
void fmc_interrupt_enable(uint32_t interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(uint32_t interrupt);
/* get flag set or reset */
FlagStatus fmc_flag_get(uint32_t flag);
/* clear the FMC pending flag */
void fmc_flag_clear(uint32_t flag);
/* get intrrupt flag set or reset */
FlagStatus fmc_interrupt_flag_get(uint32_t int_flag);
/* clear the FMC interrupt pending flag by writing 1 */
void fmc_interrupt_flag_clear(uint32_t int_flag);
/* return the FMC state */
fmc_state_enum fmc_state_get(void);
/* check FMC ready or not */
fmc_state_enum fmc_ready_wait(uint32_t timeout);

#endif /* GD32E230_FMC_H */
