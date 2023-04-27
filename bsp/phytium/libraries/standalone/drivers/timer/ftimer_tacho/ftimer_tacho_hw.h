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
 * FilePath: ftimer_tacho_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:09:15
 * Description:  This file is for timer_tacho register definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/02/18   first commit
 */

#ifndef FTIMER_TACHO_HW_H
#define FTIMER_TACHO_HW_H

#include "fio.h"
#include "ftypes.h"
#include "fkernel.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* register offset */
#define FTIMER_CTRL_REG_OFFSET (0x0)                /*Timer or Tachometer 控制寄存器*/
#define FTACHO_RESULT_REG_OFFSET (0x4)                /*一个转速周期内的时钟周期计数结果*/
#define FTIMER_COMP_VALU_OFFSET (0x8)               /*定时计数值高 32 位*/
#define FTIMER_COMP_VALL_OFFSET (0x1c)              /*timer模式下：定时计数值低32位,tacho模式下：配置tach转速周期 = pulse_num*/
#define FTIMER_CNT_VALU_OFFSET (0x20)               /*计数器当前计数值高 32 位*/
#define FTIMER_CNT_VALL_OFFSET (0x24)               /*计数器当前计数值低 32 位*/
#define FTIMER_INTR_MASK_OFFSET (0x28)              /*中断使能寄存器*/
#define FTIMER_INTR_STATUS_OFFSET (0x2c)            /*中断状态寄存器*/
#define FTACHO_OVER_LIM_OFFSET (0x30)               /*预设的 tach 最大值*/
#define FTACHO_UNDER_LIM_OFFSET (0x34)              /*预设的 tach 最小值*/
#define FTIMER_START_VAL_OFFSET (0x38)              /*计数器初始值*/

/* bit set */
/* timer ctrl */
#define FTIMER_REG_TACHO_MODE_MASK (0x3 << 0)       /*bit [1:0] RW*/
#define FTIMER_REG_TACHO_MODE_TIMER (0x0 << 0)      /*定时器功能*/
#define FTIMER_REG_TACHO_MODE_TACHO (0x1 << 0)      /*tachometer 功能*/
#define FTIMER_REG_TACHO_MODE_CAPTURE (0x2 << 0)    /*输入 capture 功能*/

#define FTIMER_REG_TACHO_RESET (0x1 << 2)           /*in reset status*/

#define FTIMER_REG_TACHO_FORCE_LOAD (0x1 << 3)      /*force to update*/
#define FTIMER_REG_TACHO_CAPTURE_ENABLE (0x1 << 4)  /*enable input capture*/
#define FTIMER_REG_TACHO_CAPTURE_CNT_MASK (0x7f << 5)    /*in capture mode, cause intr when egde counting reach this val*/
#define FTIMER_REG_TACHO_CAPTURE_CNT_SHIFT 5        /*cap_cnt shift*/

#define FTACHO_REG_ANTI_JITTER_MASK (0x3 << 18)     /*anti jitter num = N + 1*/
#define FTACHO_REG_ANTI_JITTER_SHIFT 18             /*anti_jitter_number shift*/

#define FTACHO_REG_MODE_MASK (0x3 << 20)            /*select tacho input mode*/
#define FTACHO_REG_MODE_FALLING_EDGE (0x0 << 20)    /*select falling edge*/
#define FTACHO_REG_MODE_RISING_EDGE (0x1 << 20)     /*select rising edge*/
#define FTACHO_REG_MODE_DOUBLE_EDGE (0x2 << 20)     /*select both falling edge and rising*/

#define FTIMER_REG_CNT_RESTART (0x1 << 22)          /*select timer restart mode*/
#define FTIMER_REG_CNT_FREERUN (0x0 << 22)          /*select timer free_run mode*/

#define FTIMER_REG_CNT_SERIES_64BIT (0x1 << 24)     /*select counter bit 64 */
#define FTIMER_REG_CNT_SERIES_32BIT (0x0 << 24)     /*select counter bit 32 */

#define FTIMER_REG_ENABLE (0x1 << 25)               /*enable timer count*/

#define FTIMER_REG_CNT_CLR (0x1 << 26)              /*clear counter*/
#define FTIMER_REG_CNT_NOCLR (0x0 << 26)            /*don't clear counter*/

#define FTIMER_REG_MODE_ONCE (0x1 << 27)            /*one time timer*/
#define FTIMER_REG_MODE_CYC (0x0 << 27)             /*cycle timer*/

#define FTACHO_REG_CAP_IN_ENABLE (0x1 << 31)        /*enable tacho capture input*/

/* tacho result */
#define FTACHO_REG_RESU_MASK GENMASK(30, 0)         /*bit [30:0], tacho result*/
#define FTACHO_REG_RESU_ISVALID (0x1 << 31)         /*tacho result is valid*/

/* tacho over */
#define FTACHO_REG_OVER_MASK GENMASK(30, 0)         /*tacho max value mask*/

/* tacho under */
#define FTACHO_REG_UNDER_MASK GENMASK(30, 0)        /*tacho min value mask*/

/* intr mask */
#define FTACHO_OVER_INTR_EN (0x1 << 0)              /*tach 超转速中断使能*/
#define FTACHO_UNDER_INTR_EN (0x1 << 1)             /*tach 低于转速中断使能*/
#define FTIMER_ROLLOVER_INTR_EN (0x1 << 2)          /*计数器翻转中断使能*/
#define FTIMER_ONCECMP_INTR_EN (0x1 << 3)           /*一次定时输出中断使能*/
#define FTIMER_CYCCMP_INTR_EN (0x1 << 4)            /*重复定时输出中断使能*/
#define FTACHO_CAPTURE_INTR_EN (0x1 << 5)           /*tach 输入捕获中断使能*/

#define FTIMER_ALL_INTR_EN (FTIMER_ROLLOVER_INTR_EN | FTIMER_ONCECMP_INTR_EN | FTIMER_CYCCMP_INTR_EN)

/* intr status */
#define FTACHO_OVER_INTR_STATUS (0x1 << 0)          /*tach 超转速中断*/
#define FTACHO_UNDER_INTR_STATUS (0x1 << 1)         /*tach 低于转速中断*/
#define FTIMER_ROLLOVER_INTR_STATUS (0x1 << 2)      /*计数器翻转中断*/
#define FTIMER_ONCECMP_INTR_STATUS (0x1 << 3)       /*一次定时输出中断*/
#define FTIMER_CYCCMP_INTR_STATUS (0x1 << 4)        /*重复定时输出中断*/
#define FTACHO_CAPTURE_INTR_STATUS (0x1 << 5)       /*tach 输入捕获中断*/

/**
 * @name: FTIMER_READ_REG32
 * @msg:  读取定时器寄存器
 * @param {u32} addr 定时器的基地址
 * @param {u32} reg_offset   定时器的寄存器的偏移
 * @return {u32} 寄存器参数
 */
#define FTIMER_READ_REG32(addr, reg_offset) FtIn32(addr + (u32)reg_offset)

/**
 * @name: FTIMER_WRITE_REG32
 * @msg:  写入定时器寄存器
 * @param {u32} addr 定时器的基地址
 * @param {u32} reg_offset   定时器的寄存器的偏移
 * @param {u32} reg_value    写入寄存器参数
 * @return {void}
 */
#define FTIMER_WRITE_REG32(addr, reg_offset, reg_value) FtOut32(addr + (u32)reg_offset, (u32)reg_value)

#define FTIMER_TIMEOUT 3000     /*超时时间*/

#define FTIMER_BASE_ADDR(instance_p) FTIMER_TACHO_BASE_ADDR((instance_p)->config.id)        /*获取设备基地址*/
/*read and write reg value*/
#define FTIMER_CTRL_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_CTRL_REG_OFFSET)
#define FTIMER_CTRL_WRITE(instance_p, regVal) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_CTRL_REG_OFFSET, (regVal))
#define FTIMER_CMPL_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_COMP_VALL_OFFSET)
#define FTIMER_CMPL_WRITE(instance_p, cmpL) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_COMP_VALL_OFFSET, (cmpL))
#define FTIMER_CMPU_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_COMP_VALU_OFFSET)
#define FTIMER_CMPU_WRITE(instance_p, cmpU) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_COMP_VALU_OFFSET, (cmpU))
#define FTIMER_STAR_WRITE(instance_p, cnt) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_START_VAL_OFFSET, (cnt))
#define FTIMER_STAR_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_START_VAL_OFFSET)
#define FTIMER_CNTL_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_CNT_VALL_OFFSET)
#define FTIMER_CNTU_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_CNT_VALU_OFFSET)
#define FTACHO_RESU_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTACHO_RESULT_REG_OFFSET)
#define FTACHO_OVER_WRITE(instance_p, over) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTACHO_OVER_LIM_OFFSET, (over))
#define FTACHO_UNDER_WRITE(instance_p, under) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTACHO_UNDER_LIM_OFFSET, (under))

#define FTIMER_INTR_M_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_INTR_MASK_OFFSET)
#define FTIMER_INTR_M_WRITE(instance_p, mask) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_INTR_MASK_OFFSET, (mask))
#define FTIMER_INTR_S_READ(instance_p) FTIMER_READ_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_INTR_STATUS_OFFSET)
/* write 1 clear */
#define FTIMER_INTR_S_CLEAR(instance_p, status) FTIMER_WRITE_REG32(FTIMER_BASE_ADDR(instance_p), FTIMER_INTR_STATUS_OFFSET, (status))

#ifdef __cplusplus
}
#endif

#endif // !