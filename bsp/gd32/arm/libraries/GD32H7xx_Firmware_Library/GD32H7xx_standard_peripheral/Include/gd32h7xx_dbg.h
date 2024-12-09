/*!
    \file    gd32h7xx_dbg.h
    \brief   definitions for the DBG

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

#ifndef GD32H7XX_DBG_H
#define GD32H7XX_DBG_H

#include "gd32h7xx.h"

/* DBG definitions */
#define DBG                      DBG_BASE                      /*!< DBG base address */

/* registers definitions */
#define DBG_ID                   REG32(DBG + 0x00000000U)      /*!< DBG_ID code register */
#define DBG_CTL0                 REG32(DBG + 0x00000004U)      /*!< DBG control register 0 */
#define DBG_CTL1                 REG32(DBG + 0x00000034U)      /*!< DBG control register 1 */
#define DBG_CTL2                 REG32(DBG + 0x0000003CU)      /*!< DBG control register 2 */
#define DBG_CTL3                 REG32(DBG + 0x0000004CU)      /*!< DBG control register 3 */
#define DBG_CTL4                 REG32(DBG + 0x00000054U)      /*!< DBG control register 4 */

/* bits definitions */
/* DBG_ID */
#define DBG_ID_ID_CODE           BITS(0,31)                    /*!< DBG ID code values */

/* DBG_CTL0 */
#define DBG_CTL0_SLP_HOLD        BIT(0)                        /*!< keep debugger connection during sleep mode */
#define DBG_CTL0_DSLP_HOLD       BIT(1)                        /*!< keep debugger connection during deepsleep mode */
#define DBG_CTL0_STB_HOLD        BIT(2)                        /*!< keep debugger connection during standby mode */
#define DBG_CTL0_TRACE_MODE      BITS(18,19)                   /*!< trace pin mode selection */
#define DBG_CTL0_TRACECLKEN      BIT(20)                       /*!< enable trace pin assignment */

/* DBG_CTL1 */
#define DBG_CTL1_WWDGT_HOLD      BIT(6)                        /*!< debug WWDGT kept when core is halted */

/* DBG_CTL2 */
#define DBG_CTL2_TIMER1_HOLD     BIT(0)                        /*!< debug TIMER1 kept when core is halted */
#define DBG_CTL2_TIMER2_HOLD     BIT(1)                        /*!< debug TIMER2 kept when core is halted */
#define DBG_CTL2_TIMER3_HOLD     BIT(2)                        /*!< debug TIMER3 kept when core is halted */
#define DBG_CTL2_TIMER4_HOLD     BIT(3)                        /*!< debug TIMER4 kept when core is halted */
#define DBG_CTL2_TIMER5_HOLD     BIT(4)                        /*!< debug TIMER5 kept when core is halted */
#define DBG_CTL2_TIMER6_HOLD     BIT(5)                        /*!< debug TIMER6 kept when core is halted */
#define DBG_CTL2_TIMER22_HOLD    BIT(6)                        /*!< debug TIMER22 kept when core is halted */
#define DBG_CTL2_TIMER23_HOLD    BIT(7)                        /*!< debug TIMER23 kept when core is halted */
#define DBG_CTL2_TIMER30_HOLD    BIT(8)                        /*!< debug TIMER30 kept when core is halted */
#define DBG_CTL2_TIMER31_HOLD    BIT(9)                        /*!< debug TIMER31 kept when core is halted */
#define DBG_CTL2_TIMER50_HOLD    BIT(10)                       /*!< debug TIMER50 kept when core is halted */
#define DBG_CTL2_TIMER51_HOLD    BIT(11)                       /*!< debug TIMER51 kept when core is halted */
#define DBG_CTL2_I2C0_HOLD       BIT(21)                       /*!< debug I2C0 kept when core is halted */
#define DBG_CTL2_I2C1_HOLD       BIT(22)                       /*!< debug I2C1 kept when core is halted */
#define DBG_CTL2_I2C2_HOLD       BIT(23)                       /*!< debug I2C2 kept when core is halted */
#define DBG_CTL2_I2C3_HOLD       BIT(24)                       /*!< debug I2C3 kept when core is halted */

/* DBG_CTL3 */
#define DBG_CTL3_TIMER0_HOLD     BIT(0)                        /*!< debug TIMER0 kept when core is halted */
#define DBG_CTL3_TIMER7_HOLD     BIT(1)                        /*!< debug TIMER7 kept when core is halted */
#define DBG_CTL3_CAN0_HOLD       BIT(2)                        /*!< debug CAN0 kept when core is halted */
#define DBG_CTL3_CAN1_HOLD       BIT(3)                        /*!< debug CAN1 kept when core is halted */
#define DBG_CTL3_CAN2_HOLD       BIT(4)                        /*!< debug CAN2 kept when core is halted */
#define DBG_CTL3_TIMER14_HOLD    BIT(16)                       /*!< debug TIMER14 kept when core is halted */
#define DBG_CTL3_TIMER15_HOLD    BIT(17)                       /*!< debug TIMER15 kept when core is halted */
#define DBG_CTL3_TIMER16_HOLD    BIT(18)                       /*!< debug TIMER16 kept when core is halted */
#define DBG_CTL3_TIMER40_HOLD    BIT(19)                       /*!< debug TIMER40 kept when core is halted */
#define DBG_CTL3_TIMER41_HOLD    BIT(20)                       /*!< debug TIMER41 kept when core is halted */
#define DBG_CTL3_TIMER42_HOLD    BIT(21)                       /*!< debug TIMER42 kept when core is halted */
#define DBG_CTL3_TIMER43_HOLD    BIT(22)                       /*!< debug TIMER43 kept when core is halted */
#define DBG_CTL3_TIMER44_HOLD    BIT(23)                       /*!< debug TIMER44 kept when core is halted */

/* DBG_CTL4 */
#define DBG_CTL4_RTC_HOLD        BIT(16)                       /*!< debug RTC kept when core is halted */
#define DBG_CTL4_FWDGT_HOLD      BIT(18)                       /*!< debug FWDGT kept when core is halted */

/* constants definitions */
#define DBG_LOW_POWER_SLEEP      DBG_CTL0_SLP_HOLD             /*!< keep debugger connection during sleep mode */
#define DBG_LOW_POWER_DEEPSLEEP  DBG_CTL0_DSLP_HOLD            /*!< keep debugger connection during deepsleep mode */
#define DBG_LOW_POWER_STANDBY    DBG_CTL0_STB_HOLD             /*!< keep debugger connection during standby mode */

/* define the peripheral debug hold bit position and its register index offset */
#define DBG_REGIDX_BIT(regidx, bitpos)      (((regidx) << 6) | (bitpos))
#define DBG_REG_VAL(periph)                 (REG32(DBG + ((uint32_t)(periph) >> 6)))
#define DBG_BIT_POS(val)                    ((uint32_t)(val) & 0x0000001FU)

/* register index */
typedef enum
{
    DBG_IDX_CTL1            = 0x34U,                                         /*!< DBG control register 1 offset */
    DBG_IDX_CTL2            = 0x3CU,                                         /*!< DBG control register 2 offset */
    DBG_IDX_CTL3            = 0x4CU,                                         /*!< DBG control register 3 offset */
    DBG_IDX_CTL4            = 0x54U                                          /*!< DBG control register 4 offset */
}dbg_reg_idx;

/* peripherals hold bit */
typedef enum
{
    DBG_WWDGT_HOLD               = DBG_REGIDX_BIT(DBG_IDX_CTL1, 6U),                     /*!< debug WWDGT kept when core is halted */
    DBG_I2C3_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL2, 24U),                    /*!< debug I2C3 kept when core is halted */
    DBG_I2C2_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL2, 23U),                    /*!< debug I2C2 kept when core is halted */
    DBG_I2C1_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL2, 22U),                    /*!< debug I2C1 kept when core is halted */
    DBG_I2C0_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL2, 21U),                    /*!< debug I2C0 kept when core is halted */
    DBG_TIMER51_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL2, 11U),                    /*!< debug TIMER51 kept when core is halted */
    DBG_TIMER50_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL2, 10U),                    /*!< debug TIMER50 kept when core is halted */
    DBG_TIMER31_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL2, 9U),                     /*!< debug TIMER31 kept when core is halted */
    DBG_TIMER30_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL2, 8U),                     /*!< debug TIMER30 kept when core is halted */
    DBG_TIMER23_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL2, 7U),                     /*!< debug TIMER23 kept when core is halted */
    DBG_TIMER22_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL2, 6U),                     /*!< debug TIMER22 kept when core is halted */
    DBG_TIMER6_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL2, 5U),                     /*!< debug TIMER6 kept when core is halted */
    DBG_TIMER5_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL2, 4U),                     /*!< debug TIMER5 kept when core is halted */
    DBG_TIMER4_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL2, 3U),                     /*!< debug TIMER4 kept when core is halted */
    DBG_TIMER3_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL2, 2U),                     /*!< debug TIMER3 kept when core is halted */
    DBG_TIMER2_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL2, 1U),                     /*!< debug TIMER2 kept when core is halted */
    DBG_TIMER1_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL2, 0U),                     /*!< debug TIMER1 kept when core is halted */
    DBG_TIMER44_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 23U),                    /*!< debug TIMER44 kept when core is halted */
    DBG_TIMER43_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 22U),                    /*!< debug TIMER43 kept when core is halted */
    DBG_TIMER42_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 21U),                    /*!< debug TIMER42 kept when core is halted */
    DBG_TIMER41_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 20U),                    /*!< debug TIMER41 kept when core is halted */
    DBG_TIMER40_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 19U),                    /*!< debug TIMER40 kept when core is halted */
    DBG_TIMER16_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 18U),                    /*!< debug TIMER16 kept when core is halted */
    DBG_TIMER15_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 17U),                    /*!< debug TIMER15 kept when core is halted */
    DBG_TIMER14_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL3, 16U),                    /*!< debug TIMER14 kept when core is halted */
    DBG_CAN2_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL3, 4U),                     /*!< debug CAN2 kept when core is halted */
    DBG_CAN1_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL3, 3U),                     /*!< debug CAN1 kept when core is halted */
    DBG_CAN0_HOLD                = DBG_REGIDX_BIT(DBG_IDX_CTL3, 2U),                     /*!< debug CAN0 kept when core is halted */
    DBG_TIMER7_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL3, 1U),                     /*!< debug TIMER7 kept when core is halted */
    DBG_TIMER0_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL3, 0U),                     /*!< debug TIMER0 kept when core is halted */
    DBG_FWDGT_HOLD               = DBG_REGIDX_BIT(DBG_IDX_CTL4, 18U),                    /*!< debug FWDGT kept when core is halted */
    DBG_RTC_HOLD                 = DBG_REGIDX_BIT(DBG_IDX_CTL4, 16U)                     /*!< debug RTC kept when core is halted */
}dbg_periph_enum;

#define CTL0_TRACE_MODE(regval)       (BITS(18,19) & ((uint32_t)(regval) << 18U))
#define TRACE_MODE_ASYNC              CTL0_TRACE_MODE(0)    /*!< trace pin used for async mode */
#define TRACE_MODE_SYNC_DATASIZE_1    CTL0_TRACE_MODE(1)    /*!< trace pin used for sync mode and data size is 1 */
#define TRACE_MODE_SYNC_DATASIZE_2    CTL0_TRACE_MODE(2)    /*!< trace pin used for sync mode and data size is 2 */
#define TRACE_MODE_SYNC_DATASIZE_4    CTL0_TRACE_MODE(3)    /*!< trace pin used for sync mode and data size is 4 */

/* function declarations */
/* deinitialize the DBG */
void dbg_deinit(void);
/* read DBG_ID code register */
uint32_t dbg_id_get(void);

/*enable low power behavior when the mcu is in debug mode*/
void dbg_low_power_enable(uint32_t dbg_low_power);
/*disable low power behavior when the mcu is in debug mode*/
void dbg_low_power_disable(uint32_t dbg_low_power);

/*enable trace pin assignment*/
void dbg_trace_pin_enable(void);
/*disable trace pin assignment*/
void dbg_trace_pin_disable(void);
/* set trace pin mode */
void dbg_trace_pin_mode_set(uint32_t trace_mode);

/* enable peripheral behavior when the MCU is in debug mode */
void dbg_periph_enable(dbg_periph_enum dbg_periph);
/* disable peripheral behavior when the MCU is in debug mode */
void dbg_periph_disable(dbg_periph_enum dbg_periph);

#endif /* GD32H7XX_DBG_H */
