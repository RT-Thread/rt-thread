/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include "inc/fh_driverlib.h"

int I2C_WaitMasterIdle(struct fh_i2c_obj *i2c_obj)
{
    UINT32 reg;
    int timeout = 200;  //20 ms

    while (GET_REG(i2c_obj->base + OFFSET_I2C_STATUS) & DW_IC_STATUS_MASTER_ACTIVITY)
    {
        if(timeout < 0)
        {
            rt_kprintf( "ERROR: %s, timeout waiting for master not active, txflr: 0x%x, rxflr: 0x%x, stat: 0x%x\n",
                    __func__, I2C_GetReceiveFifoLevel(i2c_obj), I2C_GetTransmitFifoLevel(i2c_obj), GET_REG(i2c_obj->base + OFFSET_I2C_INTR_STAT));
            return -RT_ETIMEOUT;
        }
        timeout--;
        udelay(100);
    }

    return 0;
}

int I2C_WaitDeviceIdle(struct fh_i2c_obj *i2c_obj)
{
    UINT32 reg;

    int timeout = 2000;  //200 ms

    while (GET_REG(i2c_obj->base + OFFSET_I2C_STATUS) & DW_IC_STATUS_ACTIVITY)
    {
        if(timeout < 0)
        {
            rt_kprintf( "ERROR: %s, timeout waiting for device not active\n", __func__);
            return -RT_ETIMEOUT;
        }
        timeout--;
        udelay(100);
    }

    return 0;
}


static inline UINT32 I2C_CalcSclHcnt(UINT32 ic_clk, UINT32 tSYMBOL, UINT32 tf, int cond, int offset)
{
    /*
     * DesignWare I2C core doesn't seem to have solid strategy to meet
     * the tHD;STA timing spec.  Configuring _HCNT based on tHIGH spec
     * will result in violation of the tHD;STA spec.
     */
    if (cond)
    /*
     * Conditional expression:
     *
     *   IC_[FS]S_SCL_HCNT + (1+4+3) >= IC_CLK * tHIGH
     *
     * This is based on the DW manuals, and represents an ideal
     * configuration.  The resulting I2C bus speed will be
     * faster than any of the others.
     *
     * If your hardware is free from tHD;STA issue, try this one.
     */
        return (ic_clk * tSYMBOL + 5000) / 10000 - 8 + offset;
    else
    /*
     * Conditional expression:
     *
     *   IC_[FS]S_SCL_HCNT + 3 >= IC_CLK * (tHD;STA + tf)
     *
     * This is just experimental rule; the tHD;STA period turned
     * out to be proportinal to (_HCNT + 3).  With this setting,
     * we could meet both tHIGH and tHD;STA timing specs.
     *
     * If unsure, you'd better to take this alternative.
     *
     * The reason why we need to take into account "tf" here,
     * is the same as described in i2c_fh_scl_lcnt().
     */
        return (ic_clk * (tSYMBOL + tf) + 5000) / 10000 - 3 + offset;
}

static inline UINT32 I2C_CalcSclLcnt(UINT32 ic_clk, UINT32 tLOW, UINT32 tf, int offset)
{
    /*
     * Conditional expression:
     *
     *   IC_[FS]S_SCL_LCNT + 1 >= IC_CLK * (tLOW + tf)
     *
     * DW I2C core starts counting the SCL CNTs for the LOW period
     * of the SCL clock (tLOW) as soon as it pulls the SCL line.
     * In order to meet the tLOW timing spec, we need to take into
     * account the fall time of SCL signal (tf).  Default tf value
     * should be 0.3 us, for safety.
     */
    return ((ic_clk * (tLOW + tf) + 5000) / 10000) - 1 + offset;
}

static int I2C_SetSpeedCount(struct fh_i2c_obj *i2c_obj)
{
    UINT32 hcnt, lcnt;

    /* set standard and fast speed count for high/low periods */

    /* Standard-mode */
    hcnt = I2C_CalcSclHcnt(i2c_obj->input_clock,
            40, /* tHD;STA = tHIGH = 4.0 us */
            3, /* tf = 0.3 us */
            0, /* 0: DW default, 1: Ideal */
            0); /* No offset */
    lcnt = I2C_CalcSclLcnt(i2c_obj->input_clock,
            47, /* tLOW = 4.7 us */
            3, /* tf = 0.3 us */
            0); /* No offset */

    SET_REG(i2c_obj->base + OFFSET_I2C_SS_SCL_HCNT, hcnt);
    SET_REG(i2c_obj->base + OFFSET_I2C_SS_SCL_LCNT, lcnt);

    /* Fast-mode */
    hcnt = I2C_CalcSclHcnt(i2c_obj->input_clock,
            6, /* tHD;STA = tHIGH = 0.6 us */
            3, /* tf = 0.3 us */
            0, /* 0: DW default, 1: Ideal */
            0); /* No offset */
    lcnt = I2C_CalcSclLcnt(i2c_obj->input_clock,
            13, /* tLOW = 1.3 us */
            3, /* tf = 0.3 us */
            0); /* No offset */
    SET_REG(i2c_obj->base + OFFSET_I2C_FS_SCL_HCNT, hcnt);
    SET_REG(i2c_obj->base + OFFSET_I2C_FS_SCL_LCNT, lcnt);

    return 0;
}

UINT32 I2C_ClearAndGetInterrupts(struct fh_i2c_obj *i2c_obj)
{
    UINT32 stat;
    /*
     * The IC_INTR_STAT register just indicates "enabled" interrupts.
     * Ths unmasked raw version of interrupt status bits are available
     * in the IC_RAW_INTR_STAT register.
     *
     * That is,
     *   stat = readl(IC_INTR_STAT);
     * equals to,
     *   stat = readl(IC_RAW_INTR_STAT) & readl(IC_INTR_MASK);
     *
     * The raw version might be useful for debugging purposes.
     */
    stat = GET_REG(i2c_obj->base + OFFSET_I2C_INTR_STAT);

    /*
     * Do not use the IC_CLR_INTR register to clear interrupts, or
     * you'll miss some interrupts, triggered during the period from
     * readl(IC_INTR_STAT) to readl(IC_CLR_INTR).
     *
     * Instead, use the separately-prepared IC_CLR_* registers.
     */
    if (stat & DW_IC_INTR_RX_UNDER)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_RX_UNDER);
    if (stat & DW_IC_INTR_RX_OVER)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_RX_OVER);
    if (stat & DW_IC_INTR_TX_OVER)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_TX_OVER);
    if (stat & DW_IC_INTR_RD_REQ)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_RD_REQ);
    if (stat & DW_IC_INTR_TX_ABRT)
    {
        /*
         * The IC_TX_ABRT_SOURCE register is cleared whenever
         * the IC_CLR_TX_ABRT is read.  Preserve it beforehand.
         */
        i2c_obj->abort_source = GET_REG(i2c_obj->base + OFFSET_I2C_TX_ABRT_SOURCE);
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_TX_ABRT);
    }
    if (stat & DW_IC_INTR_RX_DONE)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_RX_DONE);
    if (stat & DW_IC_INTR_ACTIVITY)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_ACTIVITY);
    if (stat & DW_IC_INTR_STOP_DET)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_STOP_DET);
    if (stat & DW_IC_INTR_START_DET)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_START_DET);
    if (stat & DW_IC_INTR_GEN_CALL)
        GET_REG(i2c_obj->base + OFFSET_I2C_CLR_GEN_CALL);

    return stat;
}

int I2C_HandleTxAbort(struct fh_i2c_obj *i2c_obj)
{
    unsigned long abort_source = i2c_obj->abort_source;
    int i;

    if (abort_source & DW_IC_TX_ABRT_NOACK)
    {
        //for_each_set_bit(i, &abort_source, ARRAY_SIZE(abort_sources))
        //    rt_kprintf(   "%s: %s\n", __func__, abort_sources[i]);
        return 0;
    }

    //for_each_set_bit(i, &abort_source, ARRAY_SIZE(abort_sources))
    //    rt_kprintf( "%s: %s\n", __func__, abort_sources[i]);
    rt_kprintf("%s: abort_sources 0x%x\n", __func__, abort_sources);

    if (abort_source & DW_IC_TX_ARB_LOST)
        return 0;
    else if (abort_source & DW_IC_TX_ABRT_GCALL_READ)
        return 0; /* wrong msgs[] data */
    else
        return 0;
}

void I2C_Init(struct fh_i2c_obj *i2c_obj)
{
    UINT32 ic_con;
    UINT32 param0 = GET_REG(i2c_obj->base + OFFSET_I2C_COMP_PARAM1);

    I2C_WaitMasterIdle(i2c_obj);
    I2C_Enable(i2c_obj, RT_FALSE);
    I2C_SetSpeedCount(i2c_obj);

    i2c_obj->config.tx_fifo_depth = ((param0 >> 16) & 0xff) + 1;
    i2c_obj->config.rx_fifo_depth = ((param0 >> 8) & 0xff) + 1;

    /* Configure Tx/Rx FIFO threshold levels */
    SET_REG(i2c_obj->base + OFFSET_I2C_TX_TL, i2c_obj->config.tx_fifo_depth - 1);
    SET_REG(i2c_obj->base + OFFSET_I2C_RX_TL, 0);

    /* configure the i2c master */
    ic_con = DW_IC_CON_MASTER | DW_IC_CON_SLAVE_DISABLE |
    /*OFFSET_I2C_CON_RESTART_EN |*/ DW_IC_CON_SPEED_FAST; //DW_IC_CON_SPEED_STD;

    SET_REG( i2c_obj->base + OFFSET_I2C_CON, ic_con);
}
