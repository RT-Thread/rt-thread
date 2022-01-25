/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-05-25 16:46:54
 * @Description:  This files is for sd ctrl irq handling
 *
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_sdctrl.h"
#include "ft_sdctrl_hw.h"
#include "ft_assert.h"
#include "ft_types.h"
#include "ft_io.h"
#include "ft_printf.h"
#include "ft_debug.h"

#ifndef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL FT_LOG_NONE
#endif
#define FT_SD_CTRL_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_SD_CTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SD_CTRL_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FT_SD_CTRL_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_SD_CTRL_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_SD_CTRL_DEBUG_TAG, format, ##__VA_ARGS__)

void FSdCtrl_NormalIrq(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    FSdCtrl_Config_t *pConfig;
    FSdCtrl_IrqConfig_t *irqConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;
    irqConfig = &pFtsdCtrl->irqConfig;

    //FT_SD_CTRL_DEBUG_I("enter cmd irq procedure\r\n");
    if (irqConfig->pCmdCallback)
    {
        irqConfig->pCmdCallback(irqConfig->pCmdArgs);
    }

    /* clear interrupts */
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, NORMAL_INT_STATUS_ALL_MASK);
    Ft_out32(pConfig->baseAddress + NORMAL_INT_STATUS_REG, 0);
}

void FSdCtrl_DmaIrq(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    FSdCtrl_Config_t *pConfig;
    FSdCtrl_IrqConfig_t *irqConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;
    irqConfig = &pFtsdCtrl->irqConfig;

    if (irqConfig->pDmaDataCallback)
    {
        irqConfig->pDmaDataCallback(irqConfig->pDmaDataArgs);
    }

    /* clear interrupts */
    Ft_out32(pConfig->baseAddress + BD_ISR_REG, BD_ISR_ALL_MASK);
    Ft_out32(pConfig->baseAddress + BD_ISR_REG, 0);
}

void FSdCtrl_ErrIrq(FT_INOUT FtsdCtrl_t *pFtsdCtrl)
{
    FSdCtrl_Config_t *pConfig;
    FSdCtrl_IrqConfig_t *irqConfig;
    Ft_assertVoid(FT_NULL != pFtsdCtrl);
    pConfig = &pFtsdCtrl->config;
    irqConfig = &pFtsdCtrl->irqConfig;

    if (irqConfig->pErrorCallback)
    {
        irqConfig->pErrorCallback(irqConfig->pErrorArgs);
    }

    /* clear interrupts */
    Ft_out32(pConfig->baseAddress + ERROR_INT_STATUS_REG, ERROR_INT_STATUS_ALL_MASK);
    Ft_out32(pConfig->baseAddress + ERROR_INT_STATUS_REG, 0);
}

ft_error_t FSdCtrl_SetHandler(FT_INOUT FtsdCtrl_t *pFtsdCtrl, FT_IN FSdCtrl_IrqCallbackSelect_t selectIndex,
                              void *FuncPtr, void *Args)
{
    Ft_assertNonvoid(pFtsdCtrl != NULL);
    Ft_assertNonvoid(FuncPtr != NULL);
    Ft_assertNonvoid(pFtsdCtrl->isReady == FT_COMPONENT_IS_READLY);

    switch (selectIndex)
    {
    case FTSDCTRL_DMADATAIRQID:
        pFtsdCtrl->irqConfig.pDmaDataCallback = FuncPtr;
        pFtsdCtrl->irqConfig.pDmaDataArgs = Args;
        break;
    case FTSDCTRL_CMDIRQID:
        pFtsdCtrl->irqConfig.pCmdCallback = FuncPtr;
        pFtsdCtrl->irqConfig.pCmdArgs = Args;
        break;
    case FTSDCTRL_ERRORIRQID:
        pFtsdCtrl->irqConfig.pErrorCallback = FuncPtr;
        pFtsdCtrl->irqConfig.pErrorArgs = Args;
        break;
    default:
        return FTSDC_FAILURE;
    }

    return FTSDC_SUCCESS;
}
