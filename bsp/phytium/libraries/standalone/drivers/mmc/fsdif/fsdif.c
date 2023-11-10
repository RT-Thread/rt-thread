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
 * FilePath: fsdif.c
 * Date: 2022-05-26 16:27:54
 * LastEditTime: 2022-05-26 16:27:54
 * Description:  This file is for sdif user function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 */

/***************************** Include Files *********************************/

#include "fio.h"
#include "fdrivers_port.h"
#include "fassert.h"
#include "ftypes.h"



#include "fsdif_hw.h"
#include "fsdif.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDIF_DEBUG_TAG "FSDIF"
#define FSDIF_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDIF_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDIF_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
static FError FSdifReset(FSdif *const instance_p);
static FError FSdifUpdateExternalClk(uintptr base_addr, u32 uhs_reg_val);

/*****************************************************************************/
/**
 * @name: FSdifCfgInitialize
 * @msg: initialization SDIF controller instance
 * @return {FError} FSDIF_SUCCESS if initialization success, otherwise failed
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {FSdifConfig} *input_config_p, SDIF controller configure
 * @note get into card-detect mode after initialization, bus width = 1, card freq = 400kHz
 */
FError FSdifCfgInitialize(FSdif *const instance_p, const FSdifConfig *input_config_p)
{
    FASSERT(instance_p && input_config_p);
    FError ret = FSDIF_SUCCESS;

    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FSDIF_WARN("Device is already initialized!!!");
    }

    if (&instance_p->config != input_config_p)
    {
        instance_p->config = *input_config_p;
    }

    ret = FSdifReset(instance_p); /* reset the device */

    if (FSDIF_SUCCESS == ret)
    {
        instance_p->is_ready = FT_COMPONENT_IS_READY;
        FSDIF_INFO("Device initialize success !!!");
    }

    return ret;
}

/**
 * @name: FSdifDeInitialize
 * @msg: deinitialization SDIF controller instance
 * @return {NONE}
 * @param {FSdif} *instance_p, SDIF controller instance
 */
void FSdifDeInitialize(FSdif *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;

    FSdifSetInterruptMask(instance_p, FSDIF_GENERAL_INTR, FSDIF_INT_ALL_BITS, FALSE); /* 关闭控制器中断位 */
    FSdifSetInterruptMask(instance_p, FSDIF_IDMA_INTR, FSDIF_DMAC_INT_ENA_ALL, FALSE); /* 关闭DMA中断位 */

    FSdifClearRawStatus(base_addr); /* 清除中断状态 */
    FSdifClearDMAStatus(base_addr);

    FSdifSetPower(base_addr, FALSE); /* 关闭电源 */
    FSdifSetClock(base_addr, FALSE); /* 关闭卡时钟 */
    FSDIF_CLR_BIT(base_addr, FSDIF_CLK_SRC_OFFSET, FSDIF_UHS_EXT_CLK_ENA); /* 关闭外部时钟 */
    FSDIF_CLR_BIT(base_addr, FSDIF_UHS_REG_OFFSET, FSDIF_UHS_REG_VOLT_180); /* 恢复为3.3v默认电压 */

    instance_p->is_ready = 0;
}

/**
 * @name: FSdifSetClkFreq
 * @msg: Set the Card clock freqency
 * @return {None}
 * @param {FSdif} *instance_p, SDIF controller instance
 * @param {u32} input_clk_hz, Card clock freqency in Hz
 */
FError FSdifSetClkFreq(FSdif *const instance_p, u32 input_clk_hz)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 mci_cmd_bits = FSDIF_CMD_UPD_CLK;
    FError ret = FSDIF_SUCCESS;
    const FSdifTiming *target_timing;
    u32 cmd_reg;
    u32 cur_cmd_index;

    cmd_reg = FSDIF_READ_REG(base_addr, FSDIF_CMD_OFFSET);
    cur_cmd_index = FSDIF_CMD_INDX_GET(cmd_reg);

    FSDIF_INFO("Set clk as %ld.", input_clk_hz);
    if (FSDIF_SWITCH_VOLTAGE == cur_cmd_index)
    {
        mci_cmd_bits |= FSDIF_CMD_VOLT_SWITCH;
    }

    if ((input_clk_hz > 0) && (instance_p->config.get_tuning))
    {
        /* select board-related time-tuning configurations */
        target_timing = instance_p->config.get_tuning(input_clk_hz,
                        instance_p->config.non_removable);
        if (NULL == target_timing)
        {
            FSDIF_ERROR("No available timeing !!!");
            return FSDIF_ERR_INVALID_TIMING;
        }

        /* update pad delay */
        if (target_timing->pad_delay)
        {
            target_timing->pad_delay(instance_p->config.instance_id);
        }

        /* update clock source setting */
        ret = FSdifUpdateExternalClk(base_addr, target_timing->clk_src);
        if (FSDIF_SUCCESS != ret)
        {
            FSDIF_ERROR("update clock source failed !!!");
            return ret;
        }

        FSdifSetClock(base_addr, FALSE);

        /* update clock for clock source */
        if (FSDIF_SWITCH_VOLTAGE == cur_cmd_index)
        {
            ret = FSdifSendPrivateCmd11(base_addr, mci_cmd_bits | cmd_reg);
        }
        else
        {
            ret = FSdifSendPrivateCmd(base_addr, mci_cmd_bits, 0);
        }

        if (FSDIF_SUCCESS != ret)
        {
            FSDIF_ERROR("update ext clock failed !!!");
            return ret;
        }

        /* set clock divider */
        FSDIF_WRITE_REG(base_addr, FSDIF_CLKDIV_OFFSET, target_timing->clk_div);

        FSDIF_WRITE_REG(base_addr, FSDIF_ENABLE_SHIFT_OFFSET, target_timing->shift);

        FSDIF_INFO("clk_src: 0x%x clk_div: 0x%x, shift: 0x%x",
                   FSDIF_READ_REG(base_addr, FSDIF_CLK_SRC_OFFSET),
                   FSDIF_READ_REG(base_addr, FSDIF_CLKDIV_OFFSET),
                   FSDIF_READ_REG(base_addr, FSDIF_ENABLE_SHIFT_OFFSET));

        FSdifSetClock(base_addr, TRUE);

        /* update clock for clock divider */
        if (FSDIF_SWITCH_VOLTAGE == cur_cmd_index)
        {
            ret = FSdifSendPrivateCmd11(base_addr, mci_cmd_bits | cmd_reg);
        }
        else
        {
            ret = FSdifSendPrivateCmd(base_addr, mci_cmd_bits, 0);
        }

        instance_p->curr_timing = target_timing;
    }
    else
    {
        /* close bus clock in case target clock is 0 */
        FSdifSetClock(base_addr, FALSE);

        if (FSDIF_SWITCH_VOLTAGE == cur_cmd_index)
        {
            ret = FSdifSendPrivateCmd11(base_addr, mci_cmd_bits | cmd_reg);
        }
        else
        {
            ret = FSdifSendPrivateCmd(base_addr, mci_cmd_bits, 0);
        }

        FSDIF_CLR_BIT(base_addr, FSDIF_CLK_SRC_OFFSET, FSDIF_UHS_EXT_CLK_ENA);

        instance_p->curr_timing = NULL;
    }

    FSDIF_INFO("Update clock freq done.");
    return ret;
}

/**
 * @name: FSdifUpdateExternalClk
 * @msg: update uhs clock value and wait clock ready
 * @return {FError}
 * @param {uintptr} base_addr
 * @param {u32} uhs_reg_val
 */
static FError FSdifUpdateExternalClk(uintptr base_addr, u32 uhs_reg_val)
{
    u32 reg_val;
    int retries = FSDIF_TIMEOUT;
    FSDIF_WRITE_REG(base_addr, FSDIF_CLK_SRC_OFFSET, 0U);
    FSDIF_WRITE_REG(base_addr, FSDIF_CLK_SRC_OFFSET, uhs_reg_val);

    do
    {
        reg_val = FSDIF_READ_REG(base_addr, FSDIF_CKSTS_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (!(reg_val & FSDIF_CLK_READY));

    return (retries <= 0) ? FSDIF_ERR_TIMEOUT : FSDIF_SUCCESS;
}

/**
 * @name: FSdifResetCtrl
 * @msg: Reset fifo/DMA in cntrl register
 * @return {FError} FSDIF_SUCCESS if reset success
 * @param {uintptr} base_addr, base address of SDIF controller
 * @param {u32} reset_bits, bits to be reset
 */
FError FSdifResetCtrl(uintptr base_addr, u32 reset_bits)
{
    u32 reg_val;
    int retries = FSDIF_TIMEOUT;
    FSDIF_SET_BIT(base_addr, FSDIF_CNTRL_OFFSET, reset_bits);

    do
    {
        reg_val = FSDIF_READ_REG(base_addr, FSDIF_CNTRL_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (reset_bits & reg_val);

    if (retries <= 0)
    {
        FSDIF_ERROR("Reset failed, bits = 0x%x", reset_bits);
        return FSDIF_ERR_TIMEOUT;
    }

    /* update clock after reset */
    if (FSDIF_SUCCESS != FSdifSendPrivateCmd(base_addr, FSDIF_CMD_UPD_CLK, 0U))
    {
        FSDIF_ERROR("Update clock failed !!!");
        return FSDIF_ERR_CMD_TIMEOUT;
    }

    /* for fifo reset, need to check if fifo empty */
    if (reset_bits & FSDIF_CNTRL_FIFO_RESET)
    {
        retries = FSDIF_TIMEOUT;

        do
        {
            reg_val = FSDIF_READ_REG(base_addr, FSDIF_STATUS_OFFSET);
        }
        while (!(FSDIF_STATUS_FIFO_EMPTY & reg_val));

        if (retries <= 0)
        {
            FSDIF_ERROR("Fifo not empty !!!");
            return FSDIF_ERR_TIMEOUT;
        }
    }

    return FSDIF_SUCCESS;
}

/**
 * @name: FSdifResetBusyCard
 * @msg: reset controller from card busy state
 * @return {FError} FSDIF_SUCCESS if reset success
 * @param {uintptr} base_addr, base address of controller
 */
FError FSdifResetBusyCard(uintptr base_addr)
{
    u32 reg_val;
    int retries = FSDIF_TIMEOUT;
    FSDIF_SET_BIT(base_addr, FSDIF_CNTRL_OFFSET, FSDIF_CNTRL_CONTROLLER_RESET);

    do
    {
        FSDIF_SET_BIT(base_addr, FSDIF_CNTRL_OFFSET, FSDIF_CNTRL_CONTROLLER_RESET);
        reg_val = FSDIF_READ_REG(base_addr, FSDIF_STATUS_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (reg_val & FSDIF_STATUS_DATA_BUSY);

    return (retries <= 0) ? FSDIF_ERR_BUSY : FSDIF_SUCCESS;
}

/**
 * @name: FSdifPollWaitBusyCard
 * @msg: poll wait until card not busy
 * @return {FError} FSDIF_SUCCESS if exit with card not busy
 * @param {FSdif *const} instance_p, instance of controller
 */
FError FSdifPollWaitBusyCard(FSdif *const instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->relax_handler);
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    FError err = FSDIF_SUCCESS;
    int retries = FSDIF_TIMEOUT;
    const u32 busy_bits = FSDIF_STATUS_DATA_BUSY | FSDIF_STATUS_DATA_STATE_MC_BUSY;

    reg_val = FSDIF_READ_REG(base_addr, FSDIF_STATUS_OFFSET);
    if (reg_val & busy_bits)
    {
        FSDIF_WARN("Card is busy, waiting ...");
    }

    do
    {
        reg_val = FSDIF_READ_REG(base_addr, FSDIF_STATUS_OFFSET);
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
        FSDIF_ERROR("Wait card busy timeout !!!");
        err = FSDIF_ERR_TIMEOUT;
    }

    return err;
}

/**
 * @name: FSdifRestartClk
 * @msg: restart controller clock from error status
 * @return {FError} FSDIF_SUCCESS if reset success
 * @param {uintptr} base_addr, base address of controller
 */
FError FSdifRestartClk(uintptr base_addr)
{
    u32 clk_div, uhs;
    int retries = FSDIF_TIMEOUT;
    u32 reg_val;
    FError ret = FSDIF_SUCCESS;

    /* wait command finish if previous command is in error state */
    do
    {
        reg_val = FSDIF_READ_REG(base_addr, FSDIF_CMD_OFFSET);
        if (--retries <= 0)
        {
            break;
        }
    }
    while (reg_val & FSDIF_CMD_START);

    if (retries <= 0)
    {
        return FSDIF_ERR_TIMEOUT;
    }

    /* update clock */
    FSdifSetClock(base_addr, FALSE);

    clk_div = FSDIF_READ_REG(base_addr, FSDIF_CLKDIV_OFFSET);
    uhs = FSDIF_READ_REG(base_addr, FSDIF_CLK_SRC_OFFSET);

    ret = FSdifUpdateExternalClk(base_addr, uhs);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    FSDIF_WRITE_REG(base_addr, FSDIF_CLKDIV_OFFSET, clk_div);

    FSdifSetClock(base_addr, TRUE);

    ret = FSdifSendPrivateCmd(base_addr, FSDIF_CMD_UPD_CLK, 0U);

    return ret;
}

/**
 * @name: FSdifReset
 * @msg: Reset SDIF controller instance
 * @return {FError} FSDIF_SUCCESS if reset success
 * @param {FSdif} *instance_p, SDIF controller instance
 */
static FError FSdifReset(FSdif *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    u32 reg_val;
    FError ret = FSDIF_SUCCESS;

    /* set fifo */
    reg_val = FSDIF_FIFOTH(FSDIF_FIFOTH_DMA_TRANS_8, FSDIF_RX_WMARK, FSDIF_TX_WMARK);
    FSDIF_WRITE_REG(base_addr, FSDIF_FIFOTH_OFFSET, reg_val);

    /* set card threshold */
    reg_val = FSDIF_CARD_THRCTL_THRESHOLD(FSDIF_FIFO_DEPTH_8) | FSDIF_CARD_THRCTL_CARDRD;
    FSDIF_WRITE_REG(base_addr, FSDIF_CARD_THRCTL_OFFSET, reg_val);

    /* disable clock and update ext clk */
    FSdifSetClock(base_addr, FALSE);

    /* set 1st clock */
    reg_val = FSDIF_UHS_REG(0U, 0U, 0x5U) | FSDIF_UHS_EXT_CLK_ENA;
    FASSERT_MSG(0x502 == reg_val, "invalid uhs config");
    ret = FSdifUpdateExternalClk(base_addr, reg_val);
    if (FSDIF_SUCCESS != ret)
    {
        FSDIF_ERROR("Update extern clock failed !!!");
        return ret;
    }

    /* power on */
    FSdifSetPower(base_addr, TRUE);
    FSdifSetClock(base_addr, TRUE);
    FSdifSetClockSrc(base_addr, TRUE);

    /* set voltage as 3.3v */
    FSdifSetVoltage1_8V(base_addr, FALSE);

    /* set bus width as 1 */
    FSdifSetBusWidth(base_addr, 1);

    /* reset controller and card */
    if (FSDIF_IDMA_TRANS_MODE == instance_p->config.trans_mode)
    {
        ret = FSdifResetCtrl(base_addr, FSDIF_CNTRL_FIFO_RESET | FSDIF_CNTRL_DMA_RESET);
    }
    else
    {
        ret = FSdifResetCtrl(base_addr, FSDIF_CNTRL_FIFO_RESET);
    }

    if (FSDIF_SUCCESS != ret)
    {
        FSDIF_ERROR("Reset controller failed !!!");
        return ret;
    }

    /* send private command to update clock */
    ret = FSdifSendPrivateCmd(base_addr, FSDIF_CMD_UPD_CLK, 0U);
    if (FSDIF_SUCCESS != ret)
    {
        FSDIF_ERROR("Update clock failed !!!");
        return ret;
    }

    /* reset card for no-removeable media, e.g. eMMC */
    if (TRUE == instance_p->config.non_removable)
    {
        FSDIF_SET_BIT(base_addr, FSDIF_CARD_RESET_OFFSET, FSDIF_CARD_RESET_ENABLE);
    }
    else
    {
        FSDIF_CLR_BIT(base_addr, FSDIF_CARD_RESET_OFFSET, FSDIF_CARD_RESET_ENABLE);
    }

    /* clear interrupt status */
    FSDIF_WRITE_REG(base_addr, FSDIF_INT_MASK_OFFSET, 0U);
    reg_val = FSDIF_READ_REG(base_addr, FSDIF_RAW_INTS_OFFSET);
    FSDIF_WRITE_REG(base_addr, FSDIF_RAW_INTS_OFFSET, reg_val);

    FSDIF_WRITE_REG(base_addr, FSDIF_DMAC_INT_EN_OFFSET, 0U);
    reg_val = FSDIF_READ_REG(base_addr, FSDIF_DMAC_STATUS_OFFSET);
    FSDIF_WRITE_REG(base_addr, FSDIF_DMAC_STATUS_OFFSET, reg_val);

    /* enable card detect interrupt */
    if (FALSE == instance_p->config.non_removable)
    {
        FSDIF_SET_BIT(base_addr, FSDIF_INT_MASK_OFFSET, FSDIF_INT_CD_BIT);
    }

    /* enable controller and internal DMA */
    FSDIF_SET_BIT(base_addr, FSDIF_CNTRL_OFFSET, FSDIF_CNTRL_INT_ENABLE | FSDIF_CNTRL_USE_INTERNAL_DMAC);

    /* set data and resp timeout */
    FSDIF_WRITE_REG(base_addr, FSDIF_TMOUT_OFFSET,
                    FSDIF_TIMEOUT_DATA(FSDIF_MAX_DATA_TIMEOUT, FSDIF_MAX_RESP_TIMEOUT));

    /* reset descriptors and dma */
    if (FSDIF_IDMA_TRANS_MODE == instance_p->config.trans_mode)
    {
        FSdifSetDescriptor(base_addr, (uintptr)NULL); /* set decriptor list as NULL */
        FSdifResetIDMA(base_addr);
    }

    FSDIF_INFO("Reset hardware done !!!");
    return ret;
}

/**
 * @name: FSdifRestart
 * @msg: reset controller from error state
 * @return {FError} FSDIF_SUCCESS if restart success
 * @param {FSdif} *instance_p, instance of controller
 */
FError FSdifRestart(FSdif *const instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSDIF_SUCCESS;

    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FSDIF_ERROR("Device is not yet initialized!!!");
        return FSDIF_ERR_NOT_INIT;
    }

    /* reset controller */
    ret = FSdifResetCtrl(base_addr, FSDIF_CNTRL_FIFO_RESET);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    /* reset controller if in busy state */
    ret = FSdifResetBusyCard(base_addr);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    /* reset clock */
    ret = FSdifRestartClk(base_addr);
    if (FSDIF_SUCCESS != ret)
    {
        return ret;
    }

    /* reset internal DMA */
    if (FSDIF_IDMA_TRANS_MODE == instance_p->config.trans_mode)
    {
        FSdifResetIDMA(base_addr);
    }

    return ret;
}

void FSdifRegisterRelaxHandler(FSdif *const instance_p, FSdifRelaxHandler relax_handler)
{
    FASSERT(instance_p);
    instance_p->relax_handler = relax_handler;
}