/*!
    \file    gd32h7xx_efuse.h
    \brief   definitions for the EFUSE

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

#ifndef GD32H7XX_EFUSE_H
#define GD32H7XX_EFUSE_H

#include "gd32h7xx.h"

/* EFUSE definitions */
#define EFUSE                              EFUSE_BASE                        /*!< EFUSE base address */

/* registers definitions */
#define EFUSE_CTL                          REG32(EFUSE + 0x00000000U)        /*!< EFUSE control register */
#define EFUSE_ADDR                         REG32(EFUSE + 0x00000004U)        /*!< EFUSE address register */
#define EFUSE_STAT                         REG32(EFUSE + 0x0000000CU)        /*!< EFUSE status register */
#define EFUSE_STATC                        REG32(EFUSE + 0x00000010U)        /*!< EFUSE status clear register */
#define EFUSE_USER_CTL                     REG32(EFUSE + 0x00000014U)        /*!< EFUSE user control register */
#define EFUSE_MCU_RSV                      REG32(EFUSE + 0x00000018U)        /*!< EFUSE MCU reserved register */
#define EFUSE_DP0                          REG32(EFUSE + 0x0000001CU)        /*!< EFUSE debug password register 0 */
#define EFUSE_DP1                          REG32(EFUSE + 0x00000020U)        /*!< EFUSE debug password register 1 */
#define EFUSE_AES_KEY0                     REG32(EFUSE + 0x00000024U)        /*!< EFUSE firmware AES key register 0 */
#define EFUSE_AES_KEY1                     REG32(EFUSE + 0x00000028U)        /*!< EFUSE firmware AES key register 1 */
#define EFUSE_AES_KEY2                     REG32(EFUSE + 0x0000002CU)        /*!< EFUSE firmware AES key register  2 */
#define EFUSE_AES_KEY3                     REG32(EFUSE + 0x00000030U)        /*!< EFUSE firmware AES key register3 */
#define EFUSE_USER_DATA0                   REG32(EFUSE + 0x00000034U)        /*!< EFUSE user data register 0 */
#define EFUSE_USER_DATA1                   REG32(EFUSE + 0x00000038U)        /*!< EFUSE user data register 1 */
#define EFUSE_USER_DATA2                   REG32(EFUSE + 0x0000003CU)        /*!< EFUSE user data register 2 */
#define EFUSE_USER_DATA3                   REG32(EFUSE + 0x00000040U)        /*!< EFUSE user data register 3 */

/* bits definitions */
/* EFUSE_CTL */
#define EFUSE_CTL_EFSTR                    BIT(0)                            /*!< start EFUSE operation */
#define EFUSE_CTL_EFRW                     BIT(1)                            /*!< selection of EFUSE operation */
#define EFUSE_CTL_MPVEN                    BIT(15)                           /*!< enable bit for program-voltage monitoring function */
#define EFUSE_CTL_IAERRIE                  BIT(16)                           /*!< enable bit for illegal access error interrupt */
#define EFUSE_CTL_PGIE                     BIT(17)                           /*!< enable bit for program complete interrupt */
#define EFUSE_CTL_RDIE                     BIT(18)                           /*!< enable bit for read complete interrupt */
#define EFUSE_CTL_PVIE                     BIT(19)                           /*!< enable bit for program voltage setting error interrupt */
#define EFUSE_CTL_AES_KEY_CRC              BITS(24,31)                       /*!< 8-bits CRC calculation result value of AES key bits */

/* EFUSE_ADDR */
#define EFUSE_ADDR_EFADDR                  BITS(0,9)                         /*!< read or write EFUSE data start address */
#define EFUSE_ADDR_EFSIZE                  BITS(10,14)                       /*!< read or write EFUSE data size */

/* EFUSE_STAT */
#define EFUSE_STAT_IAERRIF                 BIT(0)                            /*!< illegal access error flag */
#define EFUSE_STAT_PGIF                    BIT(1)                            /*!< program complete flag */
#define EFUSE_STAT_RDIF                    BIT(2)                            /*!< read complete flag */
#define EFUSE_STAT_PVIF                    BIT(3)                            /*!< program voltage setting error flag */
#define EFUSE_STAT_LDO_RDY                 BIT(4)                            /*!< EFUSE LDO ready signal */

/* EFUSE_STATC */
#define EFUSE_STATC_IAERRIC                BIT(0)                            /*!< clear bit for illegal access error interrupt */
#define EFUSE_STATC_PGIC                   BIT(1)                            /*!< clear bit for program complete interrupt flag */
#define EFUSE_STATC_RDIC                   BIT(2)                            /*!< clear bit for read complete interrupt flag */
#define EFUSE_STATC_PVIC                   BIT(3)                            /*!< clear bit for program voltage setting error interrupt flag */

/* EFUSE_USER_CTL */
#define EFUSE_USER_CTL_DPLK                BIT(0)                            /*!< EFUSE_DP register lock bit */
#define EFUSE_USER_CTL_SCRLK               BIT(1)                            /*!< secure-access area start/end address lock bit */
#define EFUSE_USER_CTL_UCLK                BIT(2)                            /*!< low 16 bits of EFUSE_USER_CTL register lock bit */
#define EFUSE_USER_CTL_AESEN               BIT(3)                            /*!< lock EFUSE_AES_KEY register and enable AES decrypt function */
#define EFUSE_USER_CTL_UDLK                BIT(4)                            /*!< EFUSE_USER_DATA register lock bit */
#define EFUSE_USER_CTL_NDBG                BITS(8,9)                         /*!< debug mode setting bit */
#define EFUSE_USER_CTL_JTAGNSW             BIT(10)                           /*!< debugger select bit */
#define EFUSE_USER_CTL_SPC_L               BIT(11)                           /*!< low security protection */
#define EFUSE_USER_CTL_SPC_H               BIT(12)                           /*!< high security protection */
#define EFUSE_USER_CTL_SCR                 BIT(13)                           /*!< secure access mode enable bit */
#define EFUSE_USER_CTL_ESPI_START_MODE     BITS(14,15)                       /*!< external SPI start mode */
#define EFUSE_USER_CTL_SCR_AREA_START      BITS(16,23)                       /*!< secure-access area start address */
#define EFUSE_USER_CTL_SCR_AREA_END        BITS(24,31)                       /*!< secure-access area end address */

/* EFUSE_MCU_RSV */
#define EFUSE_MCU_RSV_AESNCAU              BIT(0)                            /*!< AES key available for CAU */
#define EFUSE_MCU_RSV_DISLFI               BIT(6)                            /*!< disable bit for licensed firmware install (LFI) */
#define EFUSE_MCU_RSV_VFIMG                BIT(7)                            /*!< enable bit for verify firmware image */
#define EFUSE_MCU_RSV_MCURSVLK             BIT(8)                            /*!< lock bit for low 16 bits of EFUSE_MCU_RSV register */
#define EFUSE_MCU_RSV_DCRPLK               BIT(9)                            /*!< lock bit for DCRP area start/end address */
#define EFUSE_MCU_RSV_MCU_RSV              BITS(10,15)                       /*!< MCU reserved value */
#define EFUSE_MCU_RSV_DCRP_AREA_START      BITS(16,23)                       /*!< DCRP area start address */
#define EFUSE_MCU_RSV_DCRP_AREA_END        BITS(24,31)                       /*!< DCRP area end address */

/* EFUSE_DP */
#define EFUSE_DP_DP                        BITS(0,31)                        /*!< EFUSE Debug password value */

/* EFUSE_AES_KEY */
#define EFUSE_AES_KEY_AESKEY               BITS(0,31)                        /*!< EFUSE AES key value */

/* EFUSE_USER_DATA */
#define EFUSE_USER_DATA_USERDATA           BITS(0,31)                        /*!< EFUSE USER_DATA value */

/* constants definitions */

/* define the EFUSE bit position and its register index offset */
#define EFUSE_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define EFUSE_REG_VAL(offset)             (REG32(EFUSE + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define EFUSE_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define EFUSE_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                            | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define EFUSE_REG_VAL2(offset)            (REG32(EFUSE + ((uint32_t)(offset) >> 22)))
#define EFUSE_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define EFUSE_CTL_REG_OFFSET              ((uint32_t)0x00000000U)         /*!< CTL0 register offset */
#define EFUSE_STAT_REG_OFFSET             ((uint32_t)0x0000000CU)         /*!< STAT register offset */
#define EFUSE_STATC_REG_OFFSET            ((uint32_t)0x00000010U)         /*!< STATC register offset */

/* EFUSE interrupt flags */
typedef enum {
    EFUSE_INT_FLAG_ILLEGAL_ACCESS_ERR = EFUSE_REGIDX_BIT2(EFUSE_CTL_REG_OFFSET, 16U, EFUSE_STAT_REG_OFFSET, 0U),          /*!< illegal access error interrupt flag */
    EFUSE_INT_FLAG_PROGRAM_COMPLETE = EFUSE_REGIDX_BIT2(EFUSE_CTL_REG_OFFSET, 17U, EFUSE_STAT_REG_OFFSET, 1U),            /*!< programming operation completion interrupt flag */
    EFUSE_INT_FLAG_READ_COMPLETE = EFUSE_REGIDX_BIT2(EFUSE_CTL_REG_OFFSET, 18U, EFUSE_STAT_REG_OFFSET, 2U),               /*!< read operation completion interrupt flag */
    EFUSE_INT_FLAG_PROGRAM_VOLTAGE_ERR = EFUSE_REGIDX_BIT2(EFUSE_CTL_REG_OFFSET, 19U, EFUSE_STAT_REG_OFFSET, 3U),         /*!< program voltage setting error flag */
} efuse_interrupt_flag_enum;

/* EFUSE flag */
#define EFUSE_FLAG_LDO_READY                       EFUSE_STAT_LDO_RDY        /*!< EFUSE LDO ready signal flag */
#define EFUSE_FLAG_ILLEGAL_ACCESS_ERR              EFUSE_STAT_IAERRIF        /*!< illegal access error flag */
#define EFUSE_FLAG_PROGRAM_COMPLETE                EFUSE_STAT_PGIF           /*!< programming operation completion flag */
#define EFUSE_FLAG_READ_COMPLETE                   EFUSE_STAT_RDIF           /*!< read operation completion flag */
#define EFUSE_FLAG_PROGRAM_VOLTAGE_ERR             EFUSE_STAT_PVIF           /*!< program voltage setting error flag */

/* EFUSE flag clear */
#define EFUSE_FLAG_ILLEGAL_ACCESS_ERR_CLR          EFUSE_STATC_IAERRIC       /*!< clear illegal access error flag */
#define EFUSE_FLAG_PROGRAM_COMPLETE_CLR            EFUSE_STATC_PGIC          /*!< clear programming operation completion flag */
#define EFUSE_FLAG_READ_COMPLETE_CLR               EFUSE_STATC_RDIC          /*!< clear read operation completion flag */
#define EFUSE_FLAG_PROGRAM_VOLTAGE_ERR_CLR         EFUSE_STATC_PVIC          /*!< clear program voltage setting error interrupt flag */

/* EFUSE interrupt enable */
#define EFUSE_INT_ILLEGAL_ACCESS_ERR               EFUSE_CTL_IAERRIE         /*!< illegal access error interrupt enable */
#define EFUSE_INT_PROGRAM_COMPLETE                 EFUSE_CTL_PGIE            /*!< programming operation completion interrupt enable */
#define EFUSE_INT_READ_COMPLETE                    EFUSE_CTL_RDIE            /*!< read operation completion interrupt enable */
#define EFUSE_INT_PROGRAM_VOLTAGE_ERR              EFUSE_CTL_PVIE            /*!< program voltage setting error interrupt enable */

/* EFUSE interrupt flag clear */
#define EFUSE_INT_FLAG_ILLEGAL_ACCESS_ERR_CLR      EFUSE_STATC_IAERRIC       /*!< clear illegal access error interrupt flag */
#define EFUSE_INT_FLAG_PROGRAM_COMPLETE_CLR        EFUSE_STATC_PGIC          /*!< clear programming operation completion interrupt flag */
#define EFUSE_INT_FLAG_READ_COMPLETE_CLR           EFUSE_STATC_RDIC          /*!< clear read operation completion interrupt flag */
#define EFUSE_INT_FLAG_PROGRAM_VOLTAGE_ERR_CLR     EFUSE_STATC_PVIC          /*!< clear program voltage setting error interrupt flag */

/* EFUSE system parameter size enum, in byte unit */
typedef enum {
    USER_CTL_SIZE     = 4U,                                                  /*!< user control parameter size */
    MCU_RESERVED_SIZE = 4U,                                                  /*!< MCU reserved parameter size */
    DP_SIZE           = 8U,                                                  /*!< debug password parameter size */
    AES_KEY_SIZE      = 16U,                                                 /*!< AES key parameter size */
    USER_DATA_SIZE    = 16U,                                                 /*!< user data parameter size */
} efuse_system_para_size_enum;

/* EFUSE system parameter index */
typedef enum {
    USER_CTL_IDX      = 0U,                                                  /*!< index of user control parameter */
    MCU_RESERVED_IDX  = 1U,                                                  /*!< index of MCU reserved parameter */
    DP_IDX            = 2U,                                                  /*!< index of debug password parameter */
    AES_KEY_IDX       = 3U,                                                  /*!< index of AES key parameter */
    USER_DATA_IDX     = 4U,                                                  /*!< index of user data parameter */
} efuse_system_para_index_enum;

/* EFUSE state */
typedef enum {
    EFUSE_READY = 0U,                                                        /*!< operation has been completed */
    EFUSE_BUSY,                                                              /*!< operation is in progress */
    EFUSE_IAERR,                                                             /*!< illegal access error */
    EFUSE_PVERR,                                                             /*!< program voltage setting error */
    EFUSE_TOERR,                                                             /*!< timeout error */
} efuse_state_enum;

/* EFADDR of EFUSE system parameters */
#define USER_CTL_EFADDR                    ((uint32_t)0x00000000U)           /*!< user control parameter start address */
#define MCU_RESERVED_EFADDR                ((uint32_t)0x00000020U)           /*!< MCU reserved parameter start address */
#define DP_EFADDR                          ((uint32_t)0x00000040U)           /*!< debug password parameter start address */
#define AES_KEY_EFADDR                     ((uint32_t)0x00000080U)           /*!< AES key parameter start address */
#define USER_DATA_EFADDR                   ((uint32_t)0x00000100U)           /*!< user data parameter start address */
#define MAX_EFADDR                         ((uint32_t)0x0000017FU)           /*!< max efuse address */
#define EFUSE_PARA_CNT                     ((uint32_t)0x00000005U)           /*!< the count of system parameters in EFUSE */

/* EFUSE parameters' register address */
#define EFUSE_USER_CTL_REG_ADDR            (EFUSE + 0x00000014U)             /*!< user control register address */
#define EFUSE_MCU_RSV_REG_ADDR             (EFUSE + 0x00000018U)             /*!< MCU reserved register address */
#define EFUSE_DP_REG_ADDR                  (EFUSE + 0x0000001CU)             /*!< debug password register address */
#define EFUSE_AES_KEY_REG_ADDR             (EFUSE + 0x00000024U)             /*!< AES key register address */
#define EFUSE_USER_DATA_REG_ADDR           (EFUSE + 0x00000034U)             /*!< user data register address */

/* function declarations */
/* EFUSE operation functions */

/* read system parameters from EFUSE macro to registers */
ErrStatus efuse_read(uint32_t ef_addr, uint32_t size, uint32_t buf[]);
/* program register values to EFUSE macro system parameters */
ErrStatus efuse_write(uint32_t ef_addr, uint32_t size, uint8_t *buf);
/* program all user control parameters */
ErrStatus efuse_user_control_write(uint8_t *buf);
/* program all MCU reserved parameters */
ErrStatus efuse_mcu_reserved_write(uint8_t *buf);
/* program all debug password parameters */
ErrStatus efuse_dp_write(uint8_t *buf);
/* program all AES key parameters */
ErrStatus efuse_aes_key_write(uint8_t *buf);
/* program all user data parameters */
ErrStatus efuse_user_data_write(uint8_t *buf);

/* FMC universal functions */
/* get 8-bits CRC calculation result value of AES key */
uint8_t efuse_aes_key_crc_get(void);
/* enable monitor program voltage function */
void efuse_monitor_program_voltage_enable(void);
/* disable monitor program voltage function */
void efuse_monitor_program_voltage_disable(void);
/* get monitor program voltage function */
FlagStatus efuse_monitor_program_voltage_get(void);
/* get ldo ready signal */
FlagStatus efuse_ldo_ready_get(void);

/* flag and interrupt functions */
/* check EFUSE flag is set or not */
FlagStatus efuse_flag_get(uint32_t flag);
/* clear EFUSE pending flag */
void efuse_flag_clear(uint32_t flag);
/* enable EFUSE interrupt */
void efuse_interrupt_enable(uint32_t interrupt);
/* disable EFUSE interrupt */
void efuse_interrupt_disable(uint32_t interrupt);
/* check EFUSE interrupt flag is set or not */
FlagStatus efuse_interrupt_flag_get(uint32_t int_flag);
/* clear EFUSE pending interrupt flag */
void efuse_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32H7XX_EFUSE_H */
