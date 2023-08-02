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
 * FilePath: fpwm_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-25 11:45:05
 * Description:  This file is for pwm register definition.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/15   init commit
 */

#ifndef FPWM_HW_H
#define FPWM_HW_H

#include "fkernel.h"
#include "ftypes.h"
#include "fio.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* pwm register definitions */
#define FPWM_BASE_ADR(n)        ((FPWM_BASE_ADDR)+(n<<12)) /* 0<=n<=7 */

#define FPWM0_BASE_ADR           FPWM_BASE_ADR(0)     /* PWM 0 base address */
#define FPWM1_BASE_ADR           FPWM_BASE_ADR(1)     /* PWM 1 base address */
#define FPWM2_BASE_ADR           FPWM_BASE_ADR(2)
#define FPWM3_BASE_ADR           FPWM_BASE_ADR(3)
#define FPWM4_BASE_ADR           FPWM_BASE_ADR(4)
#define FPWM5_BASE_ADR           FPWM_BASE_ADR(5)
#define FPWM6_BASE_ADR           FPWM_BASE_ADR(6)
#define FPWM7_BASE_ADR           FPWM_BASE_ADR(7)

/* DB register */
#define FPWM_DB_CTRL_OFFSET      0x00
#define FPWM_DB_DLY_OFFSET       0x04

#define FPWM_OFFSET              0x400
#define FPWM_TIM_CNT_OFFSET      0x00
#define FPWM_TIM_CTRL_OFFSET     0x04
#define FPWM_STATE_OFFSET        0x08
#define FPWM_PERIOD_OFFSET       0x0C
#define FPWM_CTRL_OFFSET         0x10
#define FPWM_CCR_OFFSET          0x14

#define FPWM_MODE_CHANNEL       2
#define FPWM_N(x)               ((FPWM_OFFSET)*(x))

#define FPWM_RESET_TIMEOUT      10

#define NSEC_PER_SEC            (1000000000ULL)

/* pwm db_ctrl field */
#define FPWM_DB_CTRL_RESET          BIT(0)
#define FPWM_DB_CTRL_IN_MODE        BIT(1)
#define FPWM_DB_CTRL_POLSEL(data)   ((data) << 2)
#define FPWM_DB_CTRL_POLSEL_MASK    GENMASK(3, 2)
#define FPWM_DB_CTRL_POLSEL_GET(data)   ((data) >> 2)
#define FPWM_DB_CTRL_OUT_MODE(data) ((data) << 4)
#define FPWM_DB_CTRL_OUT_MODE_MASK  GENMASK(5, 4)
#define FPWM_DB_CTRL_OUT_MODE_GET(data) ((data) >> 4)

/* pwm db_ctrl field */
#define FPWM_DB_DLY_MAX   1024
#define FPWM_DB_DLY_RISE_MASK       GENMASK(9, 0)
#define FPWM_DB_DLY_FALL_MASK       GENMASK(19, 10)
#define FPWM_DB_DLY_FALL(data)      ((data) << 10)
#define FPWM_DB_DLY_FALL_GET(data)  ((data) >> 10)

/* pwm tim_ctrl field */
#define FPWM_TIM_CTRL_DIV_MAX   4096

#define FPWM_TIM_CTRL_RESET         BIT(0)
#define FPWM_TIM_CTRL_ENABLE        BIT(1)
#define FPWM_TIM_CTRL_MODE_UD       BIT(2) /* mode, modulo or up-and-down */
#define FPWM_TIM_CTRL_OVFIF_ENABLE  BIT(4) /* counter-overflow intr enable */
#define FPWM_TIM_CTRL_GIE           BIT(5) /* overall intr enable */
#define FPWM_TIM_CTRL_DIV(data)     ((data) << 16)
#define FPWM_TIM_CTRL_DIV_MASK      GENMASK(27, 16)
#define FPWM_TIM_CTRL_DIV_GET(data) ((data) >> 16)

/* pwm_state field */
#define FPWM_STATE_COUNTER_CLEAR    BIT(0)
#define FPWM_STATE_OVFIF_COUNTER    BIT(1)
#define FPWM_STATE_FIFO_EMPTY       BIT(2)
#define FPWM_STATE_FIFO_FULL        BIT(3)

/* pwm_period field */
#define FPWM_PERIOD_CCR_MASK        GENMASK(15, 0)

/* pwm_ctrl field */
#define FPWM_CTRL_MODE_OUTPUT               BIT(2)
#define FPWM_CTRL_INTR_COUNTER_ENABLE       BIT(3)
#define FPWM_CTRL_CMP(data)                 ((data) << 4)
#define FPWM_CTRL_CMP_MASK                  GENMASK(6, 4)
#define FPWM_CTRL_CMP_GET(data)             ((data) >> 4)
#define FPWM_CTRL_DUTY_SOURCE_FIFO          BIT(8)
#define FPWM_CTRL_INTR_FIFO_EMPTY_ENABLE    BIT(9)

/* pwm_ccr field */
#define FPWM_CCR_MASK           GENMASK(15, 0)
#define FPWM_CCR_GPIO	        BIT(16)

/* pwm lsd cfg, lsd pwm sync control */
#define FLSD_MIO_PWM_SYN_OFFSET 0x20
#define FLSD_MIO_PWM_SYN_MASK   GENMASK(7, 0)

/***************** Macros (Inline Functions) Definitions *********************/

/* 读FPWM寄存器 */
#define FPWM_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)reg_offset)

/* 写FPWM寄存器 */
#define FPWM_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)reg_offset, (u32)reg_value)

#define FPWM_SETBIT(base_addr, reg_offset, data) FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FPWM_CLEARBIT(base_addr, reg_offset, data) FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

/* enable pwm lsd syn */
void FPwmLsdEnable(uintptr lsd_addr, u8 pwm_id);

/* disable pwm lsd syn */
void FPwmLsdDisable(uintptr lsd_addr, u8 pwm_id);

#ifdef __cplusplus
}
#endif

#endif