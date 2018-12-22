/*!
    \file  gd32f4xx_dbg.h
    \brief definitions for the DBG
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_DBG_H
#define GD32F4XX_DBG_H

#include "gd32f4xx.h"

/* DBG definitions */
#define DBG                      DBG_BASE

/* registers definitions */
#define DBG_ID                   REG32(DBG + 0x00U)         /*!< DBG_ID code register */
#define DBG_CTL0                 REG32(DBG + 0x04U)         /*!< DBG control register 0 */
#define DBG_CTL1                 REG32(DBG + 0x08U)         /*!< DBG control register 1 */
#define DBG_CTL2                 REG32(DBG + 0x0CU)         /*!< DBG control register 2 */

/* bits definitions */
/* DBG_ID */
#define DBG_ID_ID_CODE           BITS(0,31)                 /*!< DBG ID code values */

/* DBG_CTL0 */
#define DBG_CTL0_SLP_HOLD        BIT(0)                     /*!< keep debugger connection during sleep mode */
#define DBG_CTL0_DSLP_HOLD       BIT(1)                     /*!< keep debugger connection during deepsleep mode */
#define DBG_CTL0_STB_HOLD        BIT(2)                     /*!< keep debugger connection during standby mode */
#define DBG_CTL0_TRACE_IOEN      BIT(5)                     /*!< enable trace pin assignment */
#define DBG_CTL0_TRACE_MODE      BITS(6,7)                  /*!< trace pin mode selection */

/* DBG_CTL1 */
#define DBG_CTL1_TIMER1_HOLD     BIT(0)                     /*!< hold TIMER1 counter when core is halted */
#define DBG_CTL1_TIMER2_HOLD     BIT(1)                     /*!< hold TIMER2 counter when core is halted */
#define DBG_CTL1_TIMER3_HOLD     BIT(2)                     /*!< hold TIMER3 counter when core is halted */
#define DBG_CTL1_TIMER4_HOLD     BIT(3)                     /*!< hold TIMER4 counter when core is halted */
#define DBG_CTL1_TIMER5_HOLD     BIT(4)                     /*!< hold TIMER5 counter when core is halted */
#define DBG_CTL1_TIMER6_HOLD     BIT(5)                     /*!< hold TIMER6 counter when core is halted */
#define DBG_CTL1_TIMER11_HOLD    BIT(6)                     /*!< hold TIMER11 counter when core is halted */
#define DBG_CTL1_TIMER12_HOLD    BIT(7)                     /*!< hold TIMER12 counter when core is halted */
#define DBG_CTL1_TIMER13_HOLD    BIT(8)                     /*!< hold TIMER13 counter when core is halted */
#define DBG_CTL1_RTC_HOLD        BIT(10)                    /*!< hold RTC calendar and wakeup counter when core is halted */
#define DBG_CTL1_WWDGT_HOLD      BIT(11)                    /*!< debug WWDGT kept when core is halted */
#define DBG_CTL1_FWDGT_HOLD      BIT(12)                    /*!< debug FWDGT kept when core is halted */
#define DBG_CTL1_I2C0_HOLD       BIT(21)                    /*!< hold I2C0 smbus when core is halted */
#define DBG_CTL1_I2C1_HOLD       BIT(22)                    /*!< hold I2C1 smbus when core is halted */
#define DBG_CTL1_I2C2_HOLD       BIT(23)                    /*!< hold I2C2 smbus when core is halted */
#define DBG_CTL1_CAN0_HOLD       BIT(25)                    /*!< debug CAN0 kept when core is halted */
#define DBG_CTL1_CAN1_HOLD       BIT(26)                    /*!< debug CAN1 kept when core is halted */

/* DBG_CTL2 */
#define DBG_CTL2_TIMER0_HOLD     BIT(0)                     /*!< hold TIMER0 counter when core is halted */
#define DBG_CTL2_TIMER7_HOLD     BIT(1)                     /*!< hold TIMER7 counter when core is halted */
#define DBG_CTL2_TIMER8_HOLD     BIT(16)                    /*!< hold TIMER8 counter when core is halted */
#define DBG_CTL2_TIMER9_HOLD     BIT(17)                    /*!< hold TIMER9 counter when core is halted */
#define DBG_CTL2_TIMER10_HOLD    BIT(18)                    /*!< hold TIMER10 counter when core is halted */

/* constants definitions */
#define DBG_LOW_POWER_SLEEP      DBG_CTL0_SLP_HOLD          /*!< keep debugger connection during sleep mode */
#define DBG_LOW_POWER_DEEPSLEEP  DBG_CTL0_DSLP_HOLD         /*!< keep debugger connection during deepsleep mode */
#define DBG_LOW_POWER_STANDBY    DBG_CTL0_STB_HOLD          /*!< keep debugger connection during standby mode */

typedef enum
{
    DBG_TIMER1_HOLD            = BIT(0),                    /*!< hold TIMER1 counter when core is halted */
    DBG_TIMER2_HOLD            = BIT(1),                    /*!< hold TIMER2 counter when core is halted */
    DBG_TIMER3_HOLD            = BIT(2),                    /*!< hold TIMER3 counter when core is halted */
    DBG_TIMER4_HOLD            = BIT(3),                    /*!< hold TIMER4 counter when core is halted */
    DBG_TIMER5_HOLD            = BIT(4),                    /*!< hold TIMER5 counter when core is halted */
    DBG_TIMER6_HOLD            = BIT(5),                    /*!< hold TIMER6 counter when core is halted */
    DBG_TIMER11_HOLD           = BIT(6),                    /*!< hold TIMER11 counter when core is halted */
    DBG_TIMER12_HOLD           = BIT(7),                    /*!< hold TIMER12 counter when core is halted */
    DBG_TIMER13_HOLD           = BIT(8),                    /*!< hold TIMER13 counter when core is halted */
    DBG_RTC_HOLD               = BIT(10),                   /*!< hold RTC calendar and wakeup counter when core is halted */
    DBG_WWDGT_HOLD             = BIT(11),                   /*!< debug WWDGT kept when core is halted */
    DBG_FWDGT_HOLD             = BIT(12),                   /*!< debug FWDGT kept when core is halted */
    DBG_I2C0_HOLD              = BIT(21),                   /*!< hold I2C0 smbus when core is halted */
    DBG_I2C1_HOLD              = BIT(22),                   /*!< hold I2C1 smbus when core is halted */
    DBG_I2C2_HOLD              = BIT(23),                   /*!< hold I2C2 smbus when core is halted */
    DBG_CAN0_HOLD              = BIT(25),                   /*!< debug CAN0 kept when core is halted */
    DBG_CAN1_HOLD              = BIT(26),                   /*!< debug CAN1 kept when core is halted */
    DBG_TIMER0_HOLD            = (BIT(0) | BIT(30)),        /*!< hold TIMER0 counter when core is halted */
    DBG_TIMER7_HOLD            = (BIT(1) | BIT(30)),        /*!< hold TIMER7 counter when core is halted */
    DBG_TIMER8_HOLD            = (BIT(16) | BIT(30)),       /*!< hold TIMER8 counter when core is halted */
    DBG_TIMER9_HOLD            = (BIT(17) | BIT(30)),       /*!< hold TIMER9 counter when core is halted */
    DBG_TIMER10_HOLD           = (BIT(18) | BIT(30)),       /*!< hold TIMER10 counter when core is halted */
}dbg_periph_enum;

#define CTL0_TRACE_MODE(regval)       (BITS(6,7)&((uint32_t)(regval)<<6))
#define TRACE_MODE_ASYNC              CTL0_TRACE_MODE(0)    /*!< trace pin used for async mode */
#define TRACE_MODE_SYNC_DATASIZE_1    CTL0_TRACE_MODE(1)    /*!< trace pin used for sync mode and data size is 1 */
#define TRACE_MODE_SYNC_DATASIZE_2    CTL0_TRACE_MODE(2)    /*!< trace pin used for sync mode and data size is 2 */
#define TRACE_MODE_SYNC_DATASIZE_4    CTL0_TRACE_MODE(3)    /*!< trace pin used for sync mode and data size is 4 */

/* function declarations */
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

/* enable trace pin assignment */
void dbg_trace_pin_enable(void);
/* disable trace pin assignment */
void dbg_trace_pin_disable(void);
/* set trace pin mode */
void dbg_trace_pin_mode_set(uint32_t trace_mode);

#endif /* GD32F4XX_DBG_H */
