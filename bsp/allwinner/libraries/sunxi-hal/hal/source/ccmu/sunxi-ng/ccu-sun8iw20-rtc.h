/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 lvda@allwinnertech.com
 */

#ifndef _CCU_SUN8IW20_RTC_H_
#define _CCU_SUN8IW20_RTC_H_

#define SUNXI_RTC_CCU_REG       0x07090000
#define LOSC_CTRL_REG           0x00
#define KEY_FIELD_MAGIC_NUM_RTC     0x16AA0000
#define LOSC_OUT_GATING_REG     0x60  /* Or: 32K_FOUT_CTRL_GATING_REG */
#define XO_CTRL_REG         0x160

#define CLK_IOSC        0
#define CLK_EXT32K_GATE     1
#define CLK_IOSC_DIV32K     2
#define CLK_OSC32K      3
#define CLK_DCXO24M_DIV32K  4
#define CLK_RTC32K      5
#define CLK_RTC_1K      6
#define CLK_RTC_32K_FANOUT  7
#define CLK_RTC_SPI     8

#define CLK_RTC_MAX_NO      CLK_RTC_SPI
#define CLK_RTC_NUMBER      (CLK_RTC_MAX_NO + 1)

#endif /* _CCU_SUN50IW9_RTC_H_ */
