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
 * FilePath: fsdio.c
 * Date: 2022-05-26 16:27:54
 * LastEditTime: 2022-05-26 16:27:54
 * Description:  This file is for SDIO user function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 */

/***************************** Include Files *********************************/

#include "fio.h"
#include "fdebug.h"
#include "fassert.h"
#include "ftypes.h"
#include "fsleep.h"

#include "fcache.h"

#include "fsdio_hw.h"
#include "fsdio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIO_DEBUG_TAG "FSDIO"
#define FSDIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
static FError FSdioReset(FSdio *const instance_p);
static FError FSdioUpdateExternalClk(uintptr base_addr, u32 uhs_reg_val);

/*****************************************************************************/
/**
 * @name: FSdioCfgInitialize
 * @msg: initialization SDIO controller instance
 * @return {FError} FSDIO_SUCCESS if initialization success, otherwise failed
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {FSdioConfig} *input_config_p, SDIO controller configure
 * @note get into card-detect mode after initialization, bus width = 1, card freq = 400kHz
 */
FError FSdioCfgInitialize(FSdio *const instance_p, const FSdioConfig *input_config_p)
{
    FASSERT(instance_p && input_config_p);
    FError ret = FSDIO_SUCCESS;

    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FSDIO_WARN("Device is already initialized!!!");
    }

    if (&instance_p->config != input_config_p)
    {
        instance_p->config = *input_config_p;
    }

    ret = FSdioReset(instance_p); /* reset the device */

    if (FSDIO_SUCCESS == ret)
    {
        instance_p->is_ready = FT_COMPONENT_IS_READY;
        FSDIO_INFO("Device initialize success !!!");
    }

    return ret;
}

/**
 * @name: FSdioDeInitialize
 * @msg: deinitialization SDIO controller instance
 * @return {NONE}
 * @param {FSdio} *instance_p, SDIO controller instance
 */
void FSdioDeInitialize(FSdio *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;

    FSdioSetInterruptMask(instance_p, FSDIO_GENERAL_INTR, FSDIO_INT_ALL_BITS, FALSE); /* 关闭控制器中断位 */
    FSdioSetInterruptMask(instance_p, FSDIO_IDMA_INTR, FSDIO_DMAC_INT_ENA_ALL, FALSE); /* 关闭DMA中断位 */

    FSdioClearRawStatus(base_addr); /* 清除中断状态 */
    FSdioClearDMAStatus(base_addr);

    FSdioSetPower(base_addr, FALSE); /* 关闭电源 */
    FSdioSetClock(base_addr, FALSE); /* 关闭卡时钟 */
    FSDIO_CLR_BIT(base_addr, FSDIO_UHS_REG_EXT_OFFSET, FSDIO_UHS_EXT_CLK_ENA); /* 关闭外部时钟 */
    FSDIO_CLR_BIT(base_addr, FSDIO_UHS_REG_OFFSET, FSDIO_UHS_REG_VOLT_180); /* 恢复为3.3v默认电压 */

    instance_p->is_ready = 0;
}

/**
 * @name: FSdioSetClkFreq
 * @msg: Set the Card clock freqency
 * @return {None}
 * @param {FSdio} *instance_p, SDIO controller instance
 * @param {u32} input_clk_hz, Card clock freqency in Hz
 */
FError FSdioSetClkFreq(FSdio *const instance_p, u32 input_clk_hz)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 div = 0xff, drv = 0, sample = 0;
    u32 first_uhs_div, tmp_ext_reg, div_reg;
    FError ret = FSDIO_SUCCESS;

    FSDIO_INFO("set clk as %ld.", input_clk_hz);

    /* must set 2nd stage clcok first then set 1st stage clock */
    /* experimental uhs setting  --> 2nd stage clock, below setting parameters get from
        experiment, for better sample timing */
    if (input_clk_hz >= FSDIO_SD_25_MHZ) /* e.g. 25MHz or 50MHz */
    {
        tmp_ext_reg = FSDIO_UHS_REG(0U, 0U, 0x2U) | FSDIO_UHS_EXT_CLK_ENA;
        FASSERT(tmp_ext_reg == 0x202);
    }
    else if (input_clk_hz == FSDIO_SD_400KHZ) /* 400kHz */
    {
        tmp_ext_reg = FSDIO_UHS_REG(0U, 0U, 0x5U) | FSDIO_UHS_EXT_CLK_ENA;
        FASSERT(tmp_ext_reg == 0x502);
    }
    else /* e.g. 20MHz */
    {
        tmp_ext_reg = FSDIO_UHS_REG(0U, 0U, 0x3U) | FSDIO_UHS_EXT_CLK_ENA;
        FASSERT(tmp_ext_reg == 0x302);
    }

    /* update uhs setting */
    ret = FSdioUpdateExternalClk(base_addr, tmp_ext_reg);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    FSdioSetClock(base_addr, FALSE); /* disable clock */

    /* send private cmd to update clock */
    ret = FSdioSendPrivateCmd(base_addr, FSDIO_CMD_UPD_CLK, 0U);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    /* experimental clk divide setting -- 1st stage clock */
    first_uhs_div = 1 + FSDIO_UHS_CLK_DIV_GET(tmp_ext_reg);
    div = FSDIO_CLK_FREQ_HZ / (2 * first_uhs_div * input_clk_hz);
    if (div > 2)
    {
        sample = div / 2 + 1;
        drv = sample - 1;
    }
    else if (div == 2)
    {
        drv = 0;
        sample = 1;
    }

    div_reg = FSDIO_CLK_DIV(sample, drv, div);
    FSDIO_WRITE_REG(base_addr, FSDIO_CLKDIV_OFFSET, div_reg);

    FSDIO_INFO("UHS_REG_EXT: %x, CLKDIV: %x",
               FSDIO_READ_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET),
               FSDIO_READ_REG(base_addr, FSDIO_CLKDIV_OFFSET));

    FSdioSetClock(base_addr, TRUE); /* enable clock */

    /* update clock for 1 stage clock */
    ret = FSdioSendPrivateCmd(base_addr, FSDIO_CMD_UPD_CLK, 0U);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    FSDIO_INFO("FSdioSetClkFreq done.");
    return ret;
}

/**
 * @name: FSdioGetClkFreq
 * @msg: Get the real Card clock freqency
 * @return {u32} real clock freqency in Hz
 * @param {FSdio} *instance_p, SDIO controller instance
 */
u32 FSdioGetClkFreq(FSdio *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;

    u32 uhs_reg_val = FSDIO_READ_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET);
    u32 first_uhs_div = 1 + FSDIO_UHS_CLK_DIV_GET(uhs_reg_val);

    u32 div_reg_val = FSDIO_READ_REG(base_addr, FSDIO_CLKDIV_OFFSET);
    u32 div = FSDIO_CLK_DIVDER_GET(div_reg_val);

    FSDIO_INFO("uhs_reg_val = 0x%x, div_reg_val = 0x%x", uhs_reg_val, div_reg_val);
    FSDIO_INFO("first_div = %d, second_div = %d", first_uhs_div, div);
    u32 real_clk_hz = FSDIO_CLK_FREQ_HZ / (2 * first_uhs_div * div);

    return real_clk_hz;
}

/**
 * @name: FSdioUpdateExternalClk
 * @msg: update uhs clock value and wait clock ready
 * @return {FError}
 * @param {uintptr} base_addr
 * @param {u32} uhs_reg_val
 */
static FError FSdioUpdateExternalClk(uintptr base_addr, u32 uhs_reg_val)
{
    u32 reg_val;
    int retries = FSDIO_TIMEOUT;
    FSDIO_WRITE_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET, 0U);
    FSDIO_WRITE_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET, uhs_reg_val);

    do
    {
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_GPIO_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (!(reg_val & FSDIO_CLK_READY));

    return (retries <= 0) ? FSDIO_ERR_TIMEOUT : FSDIO_SUCCESS;
}

/**
 * @name: FSdioResetCtrl
 * @msg: Reset fifo/DMA in cntrl register
 * @return {FError} FSDIO_SUCCESS if reset success
 * @param {uintptr} base_addr, base address of SDIO controller
 * @param {u32} reset_bits, bits to be reset
 */
FError FSdioResetCtrl(uintptr base_addr, u32 reset_bits)
{
    u32 reg_val;
    int retries = FSDIO_TIMEOUT;
    FSDIO_SET_BIT(base_addr, FSDIO_CNTRL_OFFSET, reset_bits);

    do
    {
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_CNTRL_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (reset_bits & reg_val);

    if (retries <= 0)
    {
        return FSDIO_ERR_TIMEOUT;
    }

    return FSDIO_SUCCESS;
}

/**
 * @name: FSdioResetBusyCard
 * @msg: reset controller from card busy state
 * @return {FError} FSDIO_SUCCESS if reset success
 * @param {uintptr} base_addr, base address of controller
 */
FError FSdioResetBusyCard(uintptr base_addr)
{
    u32 reg_val;
    int retries = FSDIO_TIMEOUT;
    FSDIO_SET_BIT(base_addr, FSDIO_CNTRL_OFFSET, FSDIO_CNTRL_CONTROLLER_RESET);

    do
    {
        FSDIO_SET_BIT(base_addr, FSDIO_CNTRL_OFFSET, FSDIO_CNTRL_CONTROLLER_RESET);
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_STATUS_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (reg_val & FSDIO_STATUS_DATA_BUSY);

    return (retries <= 0) ? FSDIO_ERR_BUSY : FSDIO_SUCCESS;
}

/**
 * @name: FSdioPollWaitBusyCard
 * @msg: poll wait until card not busy
 * @return {FError} FSDIO_SUCCESS if exit with card not busy
 * @param {FSdio *const} instance_p, instance of controller
 */
FError FSdioPollWaitBusyCard(FSdio *const instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->relax_handler);
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    FError err = FSDIO_SUCCESS;
    int retries = FSDIO_TIMEOUT;
    const u32 busy_bits = FSDIO_STATUS_DATA_BUSY | FSDIO_STATUS_DATA_STATE_MC_BUSY;

    reg_val = FSDIO_READ_REG(base_addr, FSDIO_STATUS_OFFSET);
    if (reg_val & busy_bits)
    {
        FSDIO_WARN("Card is busy, waiting ...");
    }

    do
    {
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_STATUS_OFFSET);
        if (--retries <= 0)
        {
            break;
        }

        if (instance_p->relax_handler)
        {
            instance_p->relax_handler();    /* wait card busy could be time-consuming */
        }
    }
    while (reg_val & busy_bits);   /* wait busy bits empty */

    if (--retries <= 0)
    {
        FSDIO_ERROR("Wait card busy timeout !!!");
        err = FSDIO_ERR_TIMEOUT;
    }

    return err;
}

/**
 * @name: FSdioRestartClk
 * @msg: restart controller clock from error status
 * @return {FError} FSDIO_SUCCESS if reset success
 * @param {uintptr} base_addr, base address of controller
 */
FError FSdioRestartClk(uintptr base_addr)
{
    u32 clk_div, uhs;
    int retries = FSDIO_TIMEOUT;
    u32 reg_val;
    FError ret = FSDIO_SUCCESS;

    /* wait command finish if previous command is in error state */
    do
    {
        reg_val = FSDIO_READ_REG(base_addr, FSDIO_CMD_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (reg_val & FSDIO_CMD_START);

    if (retries <= 0)
    {
        return FSDIO_ERR_TIMEOUT;
    }

    /* update clock */
    FSdioSetClock(base_addr, FALSE);

    clk_div = FSDIO_READ_REG(base_addr, FSDIO_CLKDIV_OFFSET);
    uhs = FSDIO_READ_REG(base_addr, FSDIO_UHS_REG_EXT_OFFSET);

    ret = FSdioUpdateExternalClk(base_addr, uhs);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    FSDIO_WRITE_REG(base_addr, FSDIO_CLKDIV_OFFSET, clk_div);

    FSdioSetClock(base_addr, TRUE);

    ret = FSdioSendPrivateCmd(base_addr, FSDIO_CMD_UPD_CLK, 0U);

    return ret;
}

/**
 * @name: FSdioReset
 * @msg: Reset SDIO controller instance
 * @return {FError} FSDIO_SUCCESS if reset success
 * @param {FSdio} *instance_p, SDIO controller instance
 */
static FError FSdioReset(FSdio *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    FError ret = FSDIO_SUCCESS;

    /* set fifo */
    reg_val = FSDIO_FIFOTH(FSDIO_FIFOTH_DMA_TRANS_8, FSDIO_RX_WMARK, FSDIO_TX_WMARK);
    FSDIO_WRITE_REG(base_addr, FSDIO_FIFOTH_OFFSET, reg_val);

    /* set card threshold */
    reg_val = FSDIO_CARD_THRCTL_THRESHOLD(FSDIO_FIFO_DEPTH_8) | FSDIO_CARD_THRCTL_CARDRD;
    FSDIO_WRITE_REG(base_addr, FSDIO_CARD_THRCTL_OFFSET, reg_val);

    /* disable clock and update ext clk */
    FSdioSetClock(base_addr, FALSE);

    /* set 1st clock */
    reg_val = FSDIO_UHS_REG(0U, 0U, 0x5U) | FSDIO_UHS_EXT_CLK_ENA;
    FASSERT_MSG(0x502 == reg_val, "invalid uhs config");
    ret = FSdioUpdateExternalClk(base_addr, reg_val);
    if (FSDIO_SUCCESS != ret)
    {
        FSDIO_ERROR("Update extern clock failed !!!");
        return ret;
    }

    /* power on */
    FSdioSetPower(base_addr, TRUE);
    FSdioSetClock(base_addr, TRUE);
    FSdioSetExtClock(base_addr, TRUE);

    /* set voltage as 3.3v */
    if (FSDIO_SD_1_8V_VOLTAGE == instance_p->config.voltage)
    {
        FSdioSetVoltage1_8V(base_addr, TRUE);
    }
    else
    {
        FSdioSetVoltage1_8V(base_addr, FALSE);
    }

    /* reset controller and card */
    ret = FSdioResetCtrl(base_addr, FSDIO_CNTRL_FIFO_RESET | FSDIO_CNTRL_DMA_RESET);
    if (FSDIO_SUCCESS != ret)
    {
        FSDIO_ERROR("Reset controller failed !!!");
        return ret;
    }

    /* send private command to update clock */
    ret = FSdioSendPrivateCmd(base_addr, FSDIO_CMD_UPD_CLK, 0U);
    if (FSDIO_SUCCESS != ret)
    {
        FSDIO_ERROR("Update clock failed !!!");
        return ret;
    }

    /* reset card for no-removeable media, e.g. eMMC */
    if (TRUE == instance_p->config.non_removable)
    {
        FSDIO_SET_BIT(base_addr, FSDIO_CARD_RESET_OFFSET, FSDIO_CARD_RESET_ENABLE);
    }
    else
    {
        FSDIO_CLR_BIT(base_addr, FSDIO_CARD_RESET_OFFSET, FSDIO_CARD_RESET_ENABLE);
    }

    /* clear interrupt status */
    FSDIO_WRITE_REG(base_addr, FSDIO_INT_MASK_OFFSET, 0U);
    reg_val = FSDIO_READ_REG(base_addr, FSDIO_RAW_INTS_OFFSET);
    FSDIO_WRITE_REG(base_addr, FSDIO_RAW_INTS_OFFSET, reg_val);

    FSDIO_WRITE_REG(base_addr, FSDIO_DMAC_INT_EN_OFFSET, 0U);
    reg_val = FSDIO_READ_REG(base_addr, FSDIO_DMAC_STATUS_OFFSET);
    FSDIO_WRITE_REG(base_addr, FSDIO_DMAC_STATUS_OFFSET, reg_val);

    /* enable card detect interrupt */
    if (FALSE == instance_p->config.non_removable)
    {
        FSDIO_SET_BIT(base_addr, FSDIO_INT_MASK_OFFSET, FSDIO_INT_CD_BIT);
    }

    /* enable controller and internal DMA */
    FSDIO_SET_BIT(base_addr, FSDIO_CNTRL_OFFSET, FSDIO_CNTRL_INT_ENABLE | FSDIO_CNTRL_USE_INTERNAL_DMAC);

    /* set data and resp timeout */
    FSDIO_WRITE_REG(base_addr, FSDIO_TMOUT_OFFSET,
                    FSDIO_TIMEOUT_DATA(FSDIO_MAX_DATA_TIMEOUT, FSDIO_MAX_RESP_TIMEOUT));

    /* reset descriptors and dma */
    FSdioSetDescriptor(base_addr, (uintptr)NULL); /* set decriptor list as NULL */
    FSdioResetIDMA(base_addr);

    FSDIO_INFO("Init hardware done !!!");
    return ret;
}

/**
 * @name: FSdioRestart
 * @msg: reset controller from error state
 * @return {FError} FSDIO_SUCCESS if restart success
 * @param {FSdio} *instance_p, instance of controller
 */
FError FSdioRestart(FSdio *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSDIO_SUCCESS;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIO_ERROR("Device is not yet initialized!!!");
        return FSDIO_ERR_NOT_INIT;
    }

    /* reset controller */
    ret = FSdioResetCtrl(base_addr, FSDIO_CNTRL_FIFO_RESET);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    /* reset controller if in busy state */
    ret = FSdioResetBusyCard(base_addr);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    /* reset clock */
    ret = FSdioRestartClk(base_addr);
    if (FSDIO_SUCCESS != ret)
    {
        return ret;
    }

    /* reset internal DMA */
    FSdioResetIDMA(base_addr);

    return ret;
}

void FSdioRegisterRelaxHandler(FSdio *const instance_p, FSdioRelaxHandler relax_handler)
{
    FASSERT(instance_p);
    instance_p->relax_handler = relax_handler;
}