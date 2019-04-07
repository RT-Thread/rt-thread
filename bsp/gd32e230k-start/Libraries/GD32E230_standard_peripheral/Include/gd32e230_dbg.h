/*!
    \file    gd32e230_dbg.h
    \brief   definitions for the DBG
    
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

#ifndef GD32E230_DBG_H
#define GD32E230_DBG_H

#include "gd32e230.h"

/* DBG definitions */
#define DBG                      DBG_BASE

/* registers definitions */
#define DBG_ID                   REG32(DBG + 0x00U)      /*!< DBG_ID code register */
#define DBG_CTL0                 REG32(DBG + 0x04U)      /*!< DBG control register 0 */
#define DBG_CTL1                 REG32(DBG + 0x08U)      /*!< DBG control register 1 */

/* bits definitions */
/* DBG_ID */
#define DBG_ID_ID_CODE           BITS(0,31)             /*!< DBG ID code values */

/* DBG_CTL0 */
#define DBG_CTL0_SLP_HOLD        BIT(0)                 /*!< keep debugger connection during sleep mode */
#define DBG_CTL0_DSLP_HOLD       BIT(1)                 /*!< keep debugger connection during deepsleep mode */
#define DBG_CTL0_STB_HOLD        BIT(2)                 /*!< keep debugger connection during standby mode */
#define DBG_CTL0_FWDGT_HOLD      BIT(8)                 /*!< debug FWDGT kept when core is halted */
#define DBG_CTL0_WWDGT_HOLD      BIT(9)                 /*!< debug WWDGT kept when core is halted */
#define DBG_CTL0_TIMER0_HOLD     BIT(10)                /*!< TIMER0 counter kept when core is halted */
#define DBG_CTL0_TIMER2_HOLD     BIT(12)                /*!< TIMER2 counter kept when core is halted */
#define DBG_CTL0_I2C0_HOLD       BIT(15)                /*!< hold I2C0 smbus when core is halted */
#define DBG_CTL0_I2C1_HOLD       BIT(16)                /*!< hold I2C1 smbus when core is halted */
#define DBG_CTL0_TIMER5_HOLD     BIT(19)                /*!< hold TIMER5 counter when core is halted */
#define DBG_CTL0_TIMER13_HOLD    BIT(27)                /*!< hold TIMER13 counter when core is halted */

/* DBG_CTL1 */
#define DBG_CTL1_RTC_HOLD        BIT(10)                /*!< hold RTC calendar and wakeup counter when core is halted */
#define DBG_CTL1_TIMER14_HOLD    BIT(16)                /*!< hold TIMER14 counter when core is halted */
#define DBG_CTL1_TIMER15_HOLD    BIT(17)                /*!< hold TIMER15 counter when core is halted */
#define DBG_CTL1_TIMER16_HOLD    BIT(18)                /*!< hold TIMER16 counter when core is halted */

/* constants definitions */
#define DBG_LOW_POWER_SLEEP      DBG_CTL0_SLP_HOLD      /*!< keep debugger connection during sleep mode */
#define DBG_LOW_POWER_DEEPSLEEP  DBG_CTL0_DSLP_HOLD     /*!< keep debugger connection during deepsleep mode */
#define DBG_LOW_POWER_STANDBY    DBG_CTL0_STB_HOLD      /*!< keep debugger connection during standby mode */

/* define the peripheral debug hold bit position and its register index offset */
#define DBG_REGIDX_BIT(regidx, bitpos)      (((regidx) << 6) | (bitpos))
#define DBG_REG_VAL(periph)                 (REG32(DBG + ((uint32_t)(periph) >> 6)))
#define DBG_BIT_POS(val)                    ((uint32_t)(val) & 0x1FU)

/* register index */
enum dbg_reg_idx
{
    DBG_IDX_CTL0  = 0x04U, 
    DBG_IDX_CTL1  = 0x08U, 
};

/* peripherals hold bit */
typedef enum
{
    DBG_FWDGT_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL0, 8U),              /*!< FWDGT hold bit */
    DBG_WWDGT_HOLD          = DBG_REGIDX_BIT(DBG_IDX_CTL0, 9U),              /*!< WWDGT hold bit */
    DBG_TIMER0_HOLD         = DBG_REGIDX_BIT(DBG_IDX_CTL0, 10U),             /*!< TIMER0 hold bit */
    DBG_TIMER2_HOLD         = DBG_REGIDX_BIT(DBG_IDX_CTL0, 12U),             /*!< TIMER2 hold bit */
    DBG_TIMER5_HOLD         = DBG_REGIDX_BIT(DBG_IDX_CTL0, 19U),             /*!< TIMER5 hold bit */
    DBG_TIMER13_HOLD        = DBG_REGIDX_BIT(DBG_IDX_CTL0, 27U),             /*!< TIMER13 hold bit */
    DBG_TIMER14_HOLD        = DBG_REGIDX_BIT(DBG_IDX_CTL1, 16U),             /*!< TIMER14 hold bit */
    DBG_TIMER15_HOLD        = DBG_REGIDX_BIT(DBG_IDX_CTL1, 17U),             /*!< TIMER15 hold bit */
    DBG_TIMER16_HOLD        = DBG_REGIDX_BIT(DBG_IDX_CTL1, 18U),             /*!< TIMER16 hold bit */
    DBG_I2C0_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL0, 15U),             /*!< I2C0 hold bit */
    DBG_I2C1_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL0, 16U),             /*!< I2C1 hold bit */
    DBG_RTC_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL1, 10U),             /*!< RTC hold bit */
}dbg_periph_enum;

/* function declarations */
/* deinitialize the DBG */
void dbg_deinit(void);
/* read DBG_ID code register */
uint32_t dbg_id_get(void);

/* enable low power behavior when the MCU is in debug mode */
void dbg_low_power_enable(uint32_t dbg_low_power);
/* disable low power behavior when the MCU is in debug mode */
void dbg_low_power_disable(uint32_t dbg_low_power);

/* enable peripheral behavior when the MCU is in debug mode */
void dbg_periph_enable(dbg_periph_enum dbg_periph);
/* disable peripheral behavior when the MCU is in debug mode */
void dbg_periph_disable(dbg_periph_enum dbg_periph);

#endif /* GD32E230_DBG_H */
