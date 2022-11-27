/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdmmc_common.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if SDMMCHOST_SUPPORT_DDR50 || SDMMCHOST_SUPPORT_SDR104 || SDMMCHOST_SUPPORT_SDR50 || SDMMCHOST_SUPPORT_HS200 || \
    SDMMCHOST_SUPPORT_HS400
/* sdmmc tuning block */
const uint32_t SDMMC_TuningBlockPattern4Bit[16U] = {
    0xFF0FFF00U, 0xFFCCC3CCU, 0xC33CCCFFU, 0xFEFFFEEFU, 0xFFDFFFDDU, 0xFFFBFFFBU, 0xBFFF7FFFU, 0x77F7BDEFU,
    0xFFF0FFF0U, 0x0FFCCC3CU, 0xCC33CCCFU, 0xFFEFFFEEU, 0xFFFDFFFDU, 0xDFFFBFFFU, 0xBBFFF7FFU, 0xF77F7BDEU,
};
const uint32_t SDMMC_TuningBlockPattern8Bit[32U] = {
    0xffff00ffU, 0xffff0000U, 0xffffccccU, 0xcc33ccccU, 0xcc3333ccU, 0xccccffffU, 0xffeeffffU, 0xffeeeeffU,
    0xffffddffU, 0xffffddddU, 0xffffffbbU, 0xffffffbbU, 0xbbffffffU, 0x77ffffffU, 0x7777ff77U, 0xbbddeeffU,
    0xffffff00U, 0xffffff00U, 0x00ffffccU, 0xcccc33ccU, 0xcccc3333U, 0xccccccffU, 0xffffeeffU, 0xffffeeeeU,
    0xffffffddU, 0xffffffddU, 0xddffffffU, 0xbbffffffU, 0xbbbbffffU, 0xff77ffffU, 0xff7777ffU, 0x77bbddeeU,
};
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t SDMMC_SelectCard(sdmmchost_t *host, uint32_t relativeAddress, bool isSelected)
{
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index = (uint32_t)kSDMMC_SelectCard;
    if (isSelected)
    {
        command.argument     = relativeAddress << 16U;
        command.responseType = kCARD_ResponseTypeR1;
    }
    else
    {
        command.argument     = 0U;
        command.responseType = kCARD_ResponseTypeNone;
    }

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(host, &content);
    if ((kStatus_Success != error) || ((command.response[0U] & SDMMC_R1_ALL_ERROR_FLAG) != 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    /* Wait until card to transfer state */
    return kStatus_Success;
}

status_t SDMMC_SendApplicationCommand(sdmmchost_t *host, uint32_t relativeAddress)
{
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kSDMMC_ApplicationCommand;
    command.argument     = (relativeAddress << 16U);
    command.responseType = kCARD_ResponseTypeR1;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(host, &content);
    if ((kStatus_Success != error) || ((command.response[0U] & SDMMC_R1_ALL_ERROR_FLAG) != 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    if (0U == (command.response[0U] & SDMMC_MASK(kSDMMC_R1ApplicationCommandFlag)))
    {
        return kStatus_SDMMC_CardNotSupport;
    }

    return kStatus_Success;
}

status_t SDMMC_SetBlockCount(sdmmchost_t *host, uint32_t blockCount)
{
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kSDMMC_SetBlockCount;
    command.argument     = blockCount;
    command.responseType = kCARD_ResponseTypeR1;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(host, &content);
    if ((kStatus_Success != error) || ((command.response[0U] & SDMMC_R1_ALL_ERROR_FLAG) != 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDMMC_GoIdle(sdmmchost_t *host)
{
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index = (uint32_t)kSDMMC_GoIdleState;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(host, &content);
    if (kStatus_Success != error)
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDMMC_SetBlockSize(sdmmchost_t *host, uint32_t blockSize)
{
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kSDMMC_SetBlockLength;
    command.argument     = blockSize;
    command.responseType = kCARD_ResponseTypeR1;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(host, &content);
    if ((kStatus_Success != error) || ((command.response[0U] & SDMMC_R1_ALL_ERROR_FLAG) != 0U))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}

status_t SDMMC_SetCardInactive(sdmmchost_t *host)
{
    sdmmchost_transfer_t content = {0};
    sdmmchost_cmd_t command      = {0};
    status_t error               = kStatus_Success;

    command.index        = (uint32_t)kSDMMC_GoInactiveState;
    command.argument     = 0U;
    command.responseType = kCARD_ResponseTypeNone;

    content.command = &command;
    content.data    = NULL;
    error           = SDMMCHOST_TransferFunction(host, &content);
    if ((kStatus_Success != error))
    {
        return kStatus_SDMMC_TransferFailed;
    }

    return kStatus_Success;
}
