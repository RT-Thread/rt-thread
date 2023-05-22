/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fgpio_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:35
 * Description:  This files is for GPIO register definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
 */


#ifndef  FGPIO_HW_H
#define  FGPIO_HW_H

#include "fio.h"
#include "fkernel.h"

/***************************** Include Files *********************************/
#include "fio.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
/** @name Register Map
 *
 * Register offsets from the base address of an GPIO device.
 * @{
 */
#define FGPIO_SWPORTA_DR_OFFSET 0x00    /* WR Port A Output Data Register */
#define FGPIO_SWPORTA_DDR_OFFSET 0x04   /* WR Port A Data Direction Register */
#define FGPIO_EXT_PORTA_OFFSET 0x08     /* RO Port A Input Data Register */
#define FGPIO_SWPORTB_DR_OFFSET 0x0c    /* WR Port B Output Data Register */
#define FGPIO_SWPORTB_DDR_OFFSET 0x10   /* WR Port B Data Direction Register */
#define FGPIO_EXT_PORTB_OFFSET 0x14     /* RO Port B Input Data Register */

#define FGPIO_INTEN_OFFSET 0x18         /* WR Port A Interrput Enable Register */
#define FGPIO_INTMASK_OFFSET 0x1c       /* WR Port A Interrupt Mask Register */
#define FGPIO_INTTYPE_LEVEL_OFFSET 0x20 /* WR Port A Interrupt Level Register */
#define FGPIO_INT_POLARITY_OFFSET 0x24  /* WR Port A Interrupt Polarity Register */
#define FGPIO_INTSTATUS_OFFSET 0x28     /* RO Port A Interrupt Status Register */
#define FGPIO_RAW_INTSTATUS_OFFSET 0x2c /* RO Port A Raw Interrupt Status Register */
#define FGPIO_LS_SYNC_OFFSET 0x30       /* WR Level-sensitive Synchronization Enable Register */
#define FGPIO_DEBOUNCE_OFFSET 0x34      /* WR Debounce Enable Register */
#define FGPIO_PORTA_EOI_OFFSET 0x38     /* WO Port A Clear Interrupt Register */

/** @name FGPIO_SWPORTA_DR_OFFSET Register
 */
#define FGPIO_SWPORTA_DR_SET(dir)          SET_REG32_BITS((dir), 7, 0)
#define FGPIO_SWPORTA_DR_GET(reg_val)      GET_REG32_BITS((reg_val), 7, 0)
#define FGPIO_SWPORTA_DR_MASK              GENMASK(7, 0)

/** @name FGPIO_SWPORTA_DDR_OFFSET Register
 */
#define FGPIO_SWPORTA_DDR_SET(dir)          SET_REG32_BITS((dir), 7, 0)
#define FGPIO_SWPORTA_DDR_GET(reg_val)      GET_REG32_BITS((reg_val), 7, 0)
#define FGPIO_SWPORTA_DDR_MASK              GENMASK(7, 0)

/** @name FGPIO_EXT_PORTA_OFFSET Register
 */
#define FGPIO_EXT_PORTA_SET(dir)          SET_REG32_BITS((dir), 7, 0)
#define FGPIO_EXT_PORTA_GET(reg_val)      GET_REG32_BITS((reg_val), 7, 0)
#define FGPIO_EXT_PORTA_MASK              GENMASK(7, 0)

/** @name FGPIO_SWPORTB_DR_OFFSET Register
 */
#define FGPIO_SWPORTB_DR_SET(dir)          SET_REG32_BITS((dir), 7, 0)
#define FGPIO_SWPORTB_DR_GET(reg_val)      GET_REG32_BITS((reg_val), 7, 0)
#define FGPIO_SWPORTB_DR_MASK              GENMASK(7, 0)

/** @name FGPIO_SWPORTB_DDR_OFFSET Register
 */
#define FGPIO_SWPORTB_DDR_SET(dir)        SET_REG32_BITS((dir), 7, 0)
#define FGPIO_SWPORTB_DDR_GET(reg_val)    GET_REG32_BITS((reg_val), 7, 0)
#define FGPIO_SWPORTB_DDR_MASK            GENMASK(7, 0)

/** @name FGPIO_EXT_PORTB_OFFSET Register
 */
#define FGPIO_EXT_PORTB_SET(dir)          SET_REG32_BITS((dir), 7, 0)
#define FGPIO_EXT_PORTB_GET(reg_val)      GET_REG32_BITS((reg_val), 7, 0)
#define FGPIO_EXT_PORTB_MASK              GENMASK(7, 0)

/** @name FGPIO_INTEN_OFFSET Register
 */
#define FGPIO_INTR_PORTA_EN(n)            BIT(n) /* 1: enable the intr of n-th port in group-a */

/** @name FGPIO_INTMASK_OFFSET Register
 */
#define FGPIO_INTR_PORTA_MASK(n)          BIT(n) /* 1: disable the intr of n-th port in group-a */
#define FGPIO_INTR_PORTA_MASKALL          GENMASK(15, 0)

/** @name FGPIO_INTTYPE_LEVEL_OFFSET Register
 */
#define FGPIO_INTR_PORTA_LEVEL(n)         BIT(n) /* 1: intr by edge, 0: intr by level */

/** @name FGPIO_INT_POLARITY_OFFSET Register
 */
#define FGPIO_INTR_PORTA_POLARITY(n)      BIT(n) /* 1: intr by rising-edge/high-level, 0: intr by falling-edge/low-level */

/** @name FGPIO_INTSTATUS_OFFSET Register
 */
#define FGPIO_INTR_PORTA_STATUS(n)        BIT(n) /* intr status */

/** @name FGPIO_RAW_INTSTATUS_OFFSET Register
 */
#define FGPIO_INTR_PORTA_RAW_STATUS(n)    BIT(n) /* intr status without masking */

/** @name FGPIO_LS_SYNC_OFFSET Register
 */
#define FGPIO_PCLK_INTR_SYNC(n)           BIT(n) /* 1: sync to pclk_intr */

/** @name FGPIO_DEBOUNCE_OFFSET Register
 */
#define FGPIO_DEBOUNCE_CLK_CONFIG_SET(clk)          SET_REG32_BITS((clk), 15, 7)
#define FGPIO_DEBOUNCE_CLK_CONFIG_GET(reg_val)      GET_REG32_BITS((reg_val), 15, 7)
#define FGPIO_DEBOUNCE_CLK_CONFIG_MASK              GENMASK(15, 7)
#define FGPIO_DEBOUNCE_EN(n)                        BIT(n) /* 1: enable debounce */

/** @name FGPIO_PORTA_EOI_OFFSET Register
 */
#define FGPIO_CLR_INTR_PORTA(n)         BIT(n) /* 1: clear interrupt */


/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
static inline u32 FGpioReadReg32(uintptr base_addr, uintptr reg_off)
{
    return FtIn32(base_addr + reg_off);
}

static inline void FGpioWriteReg32(uintptr base_addr, uintptr reg_off, const u32 reg_val)
{
    FtOut32(base_addr + reg_off, reg_val);
}

static inline void FGpioSetBit32(uintptr base_addr, uintptr reg_off, u32 bit)
{
    if (0 == bit)
    {
        FtClearBit32(base_addr + reg_off, bit);
    }
    else if (1 == bit)
    {
        FtSetBit32(base_addr + reg_off, bit);
    }
}

/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif
