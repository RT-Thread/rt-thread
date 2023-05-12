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
 * FilePath: fi2c_hw.c
 * Date: 2021-11-01 14:53:42
 * LastEditTime: 2022-02-18 08:36:22
 * Description:  This file is for I2C register read/write operation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/02/18  support slave mode
 */

/***************************** Include Files *********************************/
#include <string.h>
#include "fsleep.h"
#include "fdebug.h"
#include "ferror_code.h"
#include "fassert.h"
#include "fi2c_hw.h"
#include "fi2c.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

typedef struct
{
    u32 speed_mode;
    u32 scl_lcnt;
    u32 scl_hcnt;
    u32 sda_hold;
} FI2cSpeedCfg; /* speed related configs */

typedef struct
{
    u32 speed;
    u32 min_scl_hightime_ns;
    u32 min_scl_lowtime_ns;
    u32 def_risetime_ns;
    u32 def_falltime_ns;
} FI2cSpeedModeInfo; /* speed calculation related configs */

/************************** Variable Definitions *****************************/
static const FI2cSpeedModeInfo I2C_SPEED_CFG[FI2C_SPEED_MODE_MAX] =
{
    [FI2C_STANDARD_SPEED] = {
        FI2C_SPEED_STANDARD_RATE,
        4000,
        4700,
        1000,
        300,
    },
    [FI2C_FAST_SPEED] = {
        FI2C_SPEED_FAST_RATE,
        1000,
        1300,
        300,
        300,
    }
};

/***************** Macros (Inline Functions) Definitions *********************/
#define FI2C_DEBUG_TAG "I2C_HW"
#define FI2C_ERROR(format, ...) FT_DEBUG_PRINT_E(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_INFO(format, ...) FT_DEBUG_PRINT_I(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_DEBUG(format, ...) FT_DEBUG_PRINT_D(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)

#define FI2C_TIMEOUT 500

/************************** Function Prototypes ******************************/
/**
 * @name: FI2cSetEnable
 * @msg: 设置I2C控制器的使能状态
 * @return {*}
 * @param {uintptr} addr， I2c控制器基地址
 * @param {boolean} enable， TRUE: 使能，FALSE: 去使能
 */
FError FI2cSetEnable(uintptr addr, boolean enable)
{
    u32 status = enable ? FI2C_IC_ENABLE : FI2C_IC_DISABLE;
    u32 timeout = FI2C_TIMEOUT;

    do
    {
        FI2C_WRITE_REG32(addr, FI2C_ENABLE_OFFSET, status);
        if (((FI2C_READ_REG32(addr, FI2C_ENABLE_STATUS_OFFSET)) & FI2C_IC_ENABLE_MASK) == status)
        {
            return FI2C_SUCCESS;
        }

    }
    while (0 != timeout--);

    FI2C_ERROR("Timeout in %sabling I2C ctrl.", enable ? "en" : "dis");
    return FI2C_ERR_TIMEOUT;
}

/**
 * @name: FI2cCalcTiming
 * @msg: 计算I2C的上升沿下降沿配置
 * @return {*}
 * @param {u32} bus_clk_hz， I2C总线时钟速度 Hz，默认48MHz
 * @param {u32} spk_cnt, spk数目
 * @param {FI2cSpeedCfg} *speed_cfg_p，速度配置
 */
static FError FI2cCalcTiming(u32 bus_clk_hz, u32 spk_cnt, FI2cSpeedCfg *speed_cfg_p)
{
    FASSERT(speed_cfg_p);
    u32 speed_mode = speed_cfg_p->speed_mode;
    const FI2cSpeedModeInfo *info_p = &I2C_SPEED_CFG[speed_mode];
    int fall_cnt, rise_cnt, min_t_low_cnt, min_t_high_cnt;
    int hcnt, lcnt, period_cnt, diff, tot;
    int sda_hold_time_ns, scl_rise_time_ns, scl_fall_time_ns;

    period_cnt = bus_clk_hz / info_p->speed;
    scl_rise_time_ns = info_p->def_risetime_ns;
    scl_fall_time_ns = info_p->def_falltime_ns;

    /* convert a period to a number of IC clk cycles */
    rise_cnt = DIV_ROUND_UP(bus_clk_hz / 1000 * scl_rise_time_ns, NANO_TO_KILO);
    fall_cnt = DIV_ROUND_UP(bus_clk_hz / 1000 * scl_fall_time_ns, NANO_TO_KILO);
    min_t_low_cnt = DIV_ROUND_UP(bus_clk_hz / 1000 * info_p->min_scl_lowtime_ns, NANO_TO_KILO);
    min_t_high_cnt = DIV_ROUND_UP(bus_clk_hz / 1000 * info_p->min_scl_hightime_ns, NANO_TO_KILO);

    FI2C_INFO("i2c: mode %d, bus_clk %d, speed %d, period %d rise %d fall %d tlow %d thigh %d spk %d\n",
              speed_mode, bus_clk_hz, info_p->speed, period_cnt, rise_cnt, fall_cnt,
              min_t_low_cnt, min_t_high_cnt, spk_cnt);

    /*
     * Back-solve for hcnt and lcnt according to the following equations:
     * SCL_High_time = [(HCNT + IC_*_SPKLEN + 7) * icClk] + SCL_Fall_time
     * SCL_Low_time = [(LCNT + 1) * icClk] - SCL_Fall_time + SCL_Rise_time
     */
    hcnt = min_t_high_cnt - fall_cnt - 7 - spk_cnt;
    lcnt = min_t_low_cnt - rise_cnt + fall_cnt - 1;

    if (hcnt < 0 || lcnt < 0)
    {
        FI2C_ERROR("i2c: bad counts. hcnt = %d lcnt = %d\n", hcnt, lcnt);
        return FI2C_ERR_INVAL_PARM;
    }

    /*
     * Now add things back up to ensure the period is hit. If it is off,
     * split the difference and bias to lcnt for remainder
     */
    tot = hcnt + lcnt + 7 + spk_cnt + rise_cnt + 1;

    if (tot < period_cnt)
    {
        diff = (period_cnt - tot) / 2;
        hcnt += diff;
        lcnt += diff;
        tot = hcnt + lcnt + 7 + spk_cnt + rise_cnt + 1;
        lcnt += period_cnt - tot;
    }

    speed_cfg_p->scl_lcnt = lcnt;
    speed_cfg_p->scl_hcnt = hcnt;
    speed_cfg_p->sda_hold = DIV_ROUND_UP(bus_clk_hz / 1000 * 300, NANO_TO_KILO); /* Use internal default unless other value is specified */

    FI2C_INFO("i2c: hcnt = %d lcnt = %d sda hold = %d\n",
              speed_cfg_p->scl_hcnt,
              speed_cfg_p->scl_lcnt,
              speed_cfg_p->sda_hold);

    return FI2C_SUCCESS;
}

/**
 * @name: FI2cCalcSpeedCfg
 * @msg: 计算I2C的速度配置
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 * @param {u32} speed, I2C传输速率
 * @param {u32} bus_clk_hz, I2C时钟频率
 * @param {FI2cSpeedCfg} *speed_cfg_p, I2C速度配置
 */
static FError FI2cCalcSpeedCfg(uintptr addr, u32 speed, u32 bus_clk_hz, FI2cSpeedCfg *speed_cfg_p)
{
    FASSERT(speed_cfg_p);
    u32 spk_cnt = 0;

    if (FI2C_SPEED_FAST_RATE <= speed)
    {
        speed_cfg_p->speed_mode = FI2C_FAST_SPEED;
    }
    else if (FI2C_SPEED_STANDARD_RATE <= speed)
    {
        speed_cfg_p->speed_mode = FI2C_STANDARD_SPEED;
    }
    else
    {
        return FI2C_ERR_INVAL_PARM;
    }

    spk_cnt = FI2C_READ_REG32(addr, FI2C_FS_SPKLEN_OFFSET);
    return FI2cCalcTiming(bus_clk_hz, spk_cnt, speed_cfg_p);
}

/**
 * @name: FI2cSetSpeed
 * @msg: 设置I2C控制器的速率
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 * @param {u32} speed_rate, I2C传输速率
 */
FError FI2cSetSpeed(uintptr addr, u32 speed_rate)
{
    FError ret = FI2C_SUCCESS;
    FI2cSpeedCfg speed_cfg;
    u32 enable_status;
    u32 reg_val;

    memset(&speed_cfg, 0, sizeof(speed_cfg));
    ret = FI2cCalcSpeedCfg(addr, speed_rate, FI2C_CLK_FREQ_HZ, &speed_cfg);
    if (FI2C_SUCCESS != ret)
    {
        return ret;
    }

    /* get enable setting for restore later */
    enable_status = FI2cGetEnable(addr);

    /* reset speed mode bits */
    reg_val = ((FI2C_READ_REG32(addr, FI2C_CON_OFFSET)) & (~FI2C_CON_SPEED_MASK));
    switch (speed_cfg.speed_mode)
    {
        case FI2C_STANDARD_SPEED:
            reg_val |= FI2C_CON_STD_SPEED;
            FI2C_WRITE_REG32(addr, FI2C_SS_SCL_HCNT_OFFSET, speed_cfg.scl_hcnt);
            FI2C_WRITE_REG32(addr, FI2C_SS_SCL_LCNT_OFFSET, speed_cfg.scl_lcnt);
            break;
        case FI2C_FAST_SPEED:
            reg_val |= FI2C_CON_FAST_SPEED;
            FI2C_WRITE_REG32(addr, FI2C_FS_SCL_HCNT_OFFSET, speed_cfg.scl_hcnt);
            FI2C_WRITE_REG32(addr, FI2C_FS_SCL_LCNT_OFFSET, speed_cfg.scl_lcnt);
            break;
        default:
            ret |= FI2C_ERR_INVAL_PARM;
            break;
    }

    FI2C_WRITE_REG32(addr, FI2C_CON_OFFSET, reg_val);

    /* Configure SDA Hold Time if required */
    if (0 != speed_cfg.sda_hold)
    {
        FI2C_WRITE_REG32(addr, FI2C_SDA_HOLD_OFFSET, speed_cfg.sda_hold);
    }

    /* Restore back i2c now speed set */
    if (FI2C_IC_ENABLE == enable_status)
    {
        ret |= FI2cSetEnable(addr, TRUE);
    }

    return ret;
}

/**
 * @name: FI2cWaitStatus
 * @msg: 等待特定的I2C状态位直到状态不存在或者超时
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 * @param {u32} stat_bit, I2C状态位
 */
FError FI2cWaitStatus(uintptr addr, u32 stat_bit)
{
    u32 timeout = 0;

    /* wait until statbit was set or timeout */
    do
    {
        fsleep_millisec(2); /*wait 2 ms*/
    }
    while (!((FI2C_READ_REG32(addr, FI2C_STATUS_OFFSET)) & stat_bit) && (FI2C_TIMEOUT > ++timeout));

    if (FI2C_TIMEOUT <= timeout)
    {
        FI2C_ERROR("Timeout when wait status: 0x%x.", stat_bit);
        return FI2C_ERR_TIMEOUT;
    }

    return FI2C_SUCCESS;
}

/**
 * @name: FI2cWaitBusBusy
 * @msg: 等待I2C总线忙
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 */
FError FI2cWaitBusBusy(uintptr addr)
{
    u32 timeout = FI2C_TIMEOUT;
    u32 ret = FI2C_SUCCESS;

    if (((FI2C_READ_REG32(addr, FI2C_STATUS_OFFSET)) & FI2C_STATUS_MST_ACTIVITY) &&
        (FI2C_SUCCESS != FI2cWaitStatus(addr, FI2C_STATUS_TFE)))
    {
        ret = FI2C_ERR_TIMEOUT;
        FI2C_ERROR("Timeout when wait i2c bus busy.");
    }

    return ret;
}

/**
 * @name: FI2cSetTar
 * @msg: 设置与I2C主机通信的从机地址
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 * @param {u32} tar_addr, I2C从机地址
 */
FError FI2cSetTar(uintptr addr, u32 tar_addr)
{
    u32 enable_status = FI2cGetEnable(addr);
    u32 ret = FI2C_SUCCESS;
    u32 reg_val = 0;

    if (FI2C_IC_ENABLE == enable_status)
    {
        ret = FI2cSetEnable(addr, FALSE);
    }

    if (FI2C_SUCCESS == ret)
    {
        FI2C_WRITE_REG32(addr, FI2C_TAR_OFFSET, (tar_addr & FI2C_IC_TAR_MASK));
    }

    if (FI2C_IC_ENABLE == enable_status)
    {
        ret = FI2cSetEnable(addr, TRUE);
    }

    return ret;
}

/**
 * @name: FI2cSetSar
 * @msg: 从机模式下，设置I2C地址
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 * @param {u32} sar_addr, 作为从机的地址
 */
FError FI2cSetSar(uintptr addr, u32 sar_addr)
{
    u32 enable_status = FI2cGetEnable(addr);
    u32 ret = FI2C_SUCCESS;
    u32 reg_val = 0;

    if (FI2C_IC_ENABLE == enable_status)
    {
        ret = FI2cSetEnable(addr, FALSE);
    }

    if (FI2C_SUCCESS == ret)
    {
        FI2C_WRITE_REG32(addr, FI2C_SAR_OFFSET, (sar_addr & FI2C_IC_SAR_MASK));
    }

    if (FI2C_IC_ENABLE == enable_status)
    {
        ret = FI2cSetEnable(addr, TRUE);
    }

    return ret;
}

/**
 * @name: FI2cFlushRxFifo
 * @msg: 等待接收Fifo传输完成
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 */
FError FI2cFlushRxFifo(uintptr addr)
{
    u8 data;
    int timeout = 0;
    FError ret = FI2C_SUCCESS;

    /* read data to trigger trans until fifo empty */
    while (FI2C_GET_STATUS(addr) & FI2C_STATUS_RFNE)
    {
        data = FI2C_READ_DATA(addr);

        if (FI2C_TIMEOUT < ++timeout)
        {
            ret = FI2C_TIMEOUT;
            FI2C_ERROR("Timeout when flush fifo.");
            break;
        }
    }

    return ret;
}

/**
 * @name: FI2cClearIntrBits
 * @msg: 清除中断状态位，返回清除前的中断状态
 * @return {*}
 * @param {uintptr} addr, I2C控制器基地址
 * @param {u32} *last_err_p, Abort错误
 */
u32 FI2cClearIntrBits(uintptr addr, u32 *last_err_p)
{
    FASSERT(last_err_p);

    const u32 stat = FI2C_READ_INTR_STAT(addr);

    /* read to clr intrrupt status bits */
    if (stat & FI2C_INTR_TX_ABRT)
    {
        *last_err_p = FI2C_READ_REG32(addr, FI2C_TX_ABRT_SOURCE_OFFSET); /* read out abort sources */
        FI2C_READ_REG32(addr, FI2C_CLR_TX_ABRT_OFFSET);
    }

    if (stat & FI2C_INTR_RX_UNDER)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_RX_UNDER_OFFSET);
    }

    if (stat & FI2C_INTR_RX_OVER)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_RX_OVER_OFFSET);
    }

    if (stat & FI2C_INTR_TX_OVER)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_TX_OVER_OFFSET);
    }

    if (stat & FI2C_INTR_RX_DONE)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_RX_DONE_OFFSET);
    }

    if (stat & FI2C_INTR_ACTIVITY)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_ACTIVITY_OFFSET);
    }

    if (stat & FI2C_INTR_STOP_DET)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_STOP_DET_OFFSET);
    }

    if (stat & FI2C_INTR_START_DET)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_START_DET_OFFSET);
    }

    if (stat & FI2C_INTR_GEN_CALL)
    {
        FI2C_READ_REG32(addr, FI2C_CLR_GEN_CALL_OFFSET);
    }

    return stat;
}