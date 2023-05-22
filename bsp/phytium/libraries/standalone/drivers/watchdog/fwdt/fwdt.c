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
 * FilePath: fwdt.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-07-15 17:05:09
 * Description:  This file is for wdt ctrl function implementation.
 * Users can operate as a single stage watchdog or a two stages watchdog.
 * In the single stage mode, when the timeout is reached, your system will
 * be reset by WS1. The first signal (WS0) is ignored.
 * In the two stages mode, when the timeout is reached, the first signal (WS0)
 * will trigger panic. If the system is getting into trouble and cannot be reset
 * by panic or restart properly by the kdump kernel(if supported), then the
 * second stage (as long as the first stage) will be reached, system will be
 * reset by WS1. This function can help administrator to backup the system
 * context info by panic console output or kdump.
 *
 * GWDT:
 * two stages mode:
 * |--------WOR-------WS0--------WOR-------WS1
 * |----timeout-----(panic)----timeout-----reset
 *
 * single stage mode:
 * |------WOR-----WS0(ignored)-----WOR------WS1
 * |--------------timeout-------------------reset
 *
 * Note: Since this watchdog timer has two stages, and each stage is determined
 * by WOR, in the single stage mode, the timeout is (WOR * 2); in the two
 * stages mode, the timeout is WOR.
 * This driver use two stages mode, when WS0=1, it can Raise the timeout interrupt.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Wangxiaodong   2021/8/25   init
 * 1.1   Wangxiaodong   2021/11/5   restruct
 * 1.2   Wangxiaodong   2022/7/20   add some functions
 */

#include <string.h>
#include "fgeneric_timer.h"
#include "fkernel.h"
#include "fparameters.h"
#include "ftypes.h"
#include "ferror_code.h"
#include "fdebug.h"
#include "fwdt.h"
#include "fwdt_hw.h"

#define FWDT_DEBUG_TAG "FWDT"
#define FWDT_ERROR(format, ...)   FT_DEBUG_PRINT_E(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)
#define FWDT_WARN(format, ...)   FT_DEBUG_PRINT_W(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)
#define FWDT_INFO(format, ...) FT_DEBUG_PRINT_I(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)
#define FWDT_DEBUG(format, ...) FT_DEBUG_PRINT_D(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FWdtCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {FWdtCtrl} *pctrl, instance of FWDT controller
 * @param {FWdtConfig} *input_config_p, Configuration parameters of FWdt
 * @return err code information, FWDT_SUCCESS indicates success，others indicates failed
 */
FError FWdtCfgInitialize(FWdtCtrl *pctrl, const FWdtConfig *input_config_p)
{
    FASSERT(pctrl && input_config_p);

    FError ret = FWDT_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == pctrl->is_ready)
    {
        FWDT_WARN("Device is already initialized!!!");
    }

    /*Set default values and configuration data */
    FWdtDeInitialize(pctrl);

    pctrl->config = *input_config_p;

    pctrl->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}

/**
 * @name: FWdtDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FWdtCtrl} *pctrl, instance of FWDT controller
 * @return {*}
 */
void FWdtDeInitialize(FWdtCtrl *pctrl)
{
    FASSERT(pctrl);

    pctrl->is_ready = 0;
    memset(pctrl, 0, sizeof(*pctrl));

    return;
}

/**
 * @name: FWdtSetTimeout
 * @msg: Set Timeout Value, the first time it will raise a signal, which is typically
 *  wired to an interrupt; If this watchdog remains un-refreshed, it will raise a
 *  second signal which can be used to interrupt higher-privileged software
 *  or cause a PE reset.
 * @param {WdtCtrl} *pctrl, instance of FWDT controller.
 * @param {u32} timeout, represent in seconds, this parameter must be a number between 1 and 89.
 * @return {FError} err code information, FWDT_SUCCESS indicates success, others indicates failed.
 */
FError FWdtSetTimeout(FWdtCtrl *pctrl, u32 timeout)
{
    FASSERT(pctrl != NULL);
    if (pctrl->is_ready != FT_COMPONENT_IS_READY)
    {
        FWDT_ERROR("Device is not ready!!!");
        return FWDT_NOT_READY;
    }
    if (timeout > FWDT_MAX_TIMEOUT)
    {
        FWDT_ERROR("Timeout value is invalid.");
        return FWDT_ERR_INVAL_PARM;
    }
    uintptr base_addr = pctrl->config.control_base_addr;

    FWDT_WRITE_REG32(base_addr, FWDT_GWDT_WOR, (u32)(FWDT_CLK_FREQ_HZ * timeout));

    return FWDT_SUCCESS;
}

/**
 * @name: WdtGetTimeleft
 * @msg: Get Timeout countdown, in seconds
 * @param {FWdtCtrl} *pctrl, pointer to a WdtCtrl structure that contains
 *                the configuration information for the specified wdt module.
 * @return {u32} Timeout countdown, in seconds
 */
u32 FWdtGetTimeleft(FWdtCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    u64 timeleft = 0;
    uintptr base_addr = pctrl->config.control_base_addr;

    /* if the ws0 bit of register WCS is zero，indicates that there is one more timeout opportunity */
    if (!(FWdtReadWCS(base_addr) & FWDT_GWDT_WCS_WS0))
    {
        timeleft += FWdtReadWOR(base_addr);
    }

    u32 wcvh = (u32)FWdtReadWCVH(base_addr);
    u32 wcvl = (u32)FWdtReadWCVL(base_addr);
    u64 wcv = (((u64)wcvh << 32) | wcvl);

    timeleft += (wcv - GenericTimerRead());

    FWDT_DEBUG("wcvh=%llx, wcvl=%llx, wcv=%llx, timeleft=%llx\n", wcvh, wcvl, wcv, timeleft);

    do_div(timeleft, FWDT_CLK_FREQ_HZ);

    return (u32)timeleft;
}

/**
 * @name: FWdtRefresh
 * @msg: Refresh watchdog
 * @param {WdtCtrl} *pctrl, instance of FWDT controller.
 * @return {FError} err code information, FWDT_SUCCESS indicates success, others indicates failed.
 */
FError FWdtRefresh(FWdtCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    if (pctrl->is_ready != FT_COMPONENT_IS_READY)
    {
        FWDT_ERROR("Device is not ready!!!");
        return FWDT_NOT_READY;
    }
    uintptr base_addr = pctrl->config.refresh_base_addr;
    FWDT_WRITE_REG32(base_addr, FWDT_GWDT_WRR, 0);
    return FWDT_SUCCESS;
}

/**
 * @name: FWdtStart
 * @msg: Start watchdog
 * @param {WdtCtrl} *pctrl, instance of FWDT controller
 * @return {FError} err code information, FWDT_SUCCESS indicates success, others indicates failed.
 */
FError FWdtStart(FWdtCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    if (pctrl->is_ready != FT_COMPONENT_IS_READY)
    {
        FWDT_ERROR("Device is not ready!!!");
        return FWDT_NOT_READY;
    }

    uintptr base_addr = pctrl->config.control_base_addr;
    FWDT_WRITE_REG32(base_addr, FWDT_GWDT_WCS, FWDT_GWDT_WCS_WDT_EN);

    return FWDT_SUCCESS;
}

/**
 * @name: FWdtStop
 * @msg: Stop watchdog
 * @param {WdtCtrl} *pctrl, instance of FWDT controller
 * @return {FError} err code information, FWDT_SUCCESS indicates success, others indicates failed.
 */
FError FWdtStop(FWdtCtrl *pctrl)
{
    FASSERT(pctrl != NULL);
    uintptr base_addr = pctrl->config.control_base_addr;
    FWDT_WRITE_REG32(base_addr, FWDT_GWDT_WCS, 0);
    return FWDT_SUCCESS;
}

/**
 * @name: FWdtReadFWdtReadWIIDR
 * @msg:  Read wdt iidr register value.
 * @param {FWdtCtrl} *pctrl, instance of FWDT controller
 * @param {FWdtIdentifier} *wdt_identify, wdt identifier struct.
 * @return {FError} err code information, FWDT_SUCCESS indicates success, others indicates failed.
 */
FError FWdtReadFWdtReadWIIDR(FWdtCtrl *pctrl, FWdtIdentifier *wdt_identify)
{
    FASSERT(pctrl != NULL);
    FASSERT(wdt_identify != NULL);

    if (pctrl->is_ready != FT_COMPONENT_IS_READY)
    {
        FWDT_ERROR("Device is not ready!!!");
        return FWDT_NOT_READY;
    }

    u32 reg_val = 0;
    uintptr base_addr = pctrl->config.refresh_base_addr;
    reg_val =  FWDT_READ_REG32(base_addr, FWDT_GWDT_W_IIR);

    wdt_identify->version = (u16)((reg_val & FWDT_VERSION_MASK) >> 16);
    wdt_identify->continuation_code = (u8)((reg_val & FWDT_CONTINUATION_CODE_MASK) >> 8);
    wdt_identify->identity_code = (u8)((reg_val & FWDT_IDENTIFY_CODE_MASK));

    return FWDT_SUCCESS;
}