/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-25 16:45:00
 * @Description:  This files is for i2c user interface
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include "ft_mux.h"
#include "ft_i2c_hw.h"
#include "ft_i2c.h"
#include "ft_generic_timer.h"

/* reset val of register */
#define I2C_CON_DEFAULT 0x7F
#define I2C_TAR_DEFAULT 0x1055
#define I2C_SAR_DEFAULT 0x55
#define I2C_DATA_CMD_DEFAULT 0x0
#define I2C_SS_SCL_LCNT_DEFAULT 0x1D6
#define I2C_SS_SCL_HCNT_DEFAULT 0x190
#define I2C_FS_SCL_LCNT_DEFAULT 0x82
#define I2C_FS_SCL_HCNT_DEFAULT 0x3C
#define I2C_HS_SCL_LCNT_DEFAULT 0x10
#define I2C_HS_SCL_HCNT_DEFAULT 0x6
#define I2C_INTR_MASK_DEFAULT 0x8FF
//#define I2C_RX_TL_DEFAULT        0x0
//#define I2C_TX_TL_DEFAULT        0x0
#define I2C_SCL_HCNT_DEFAULT 0x2f
#define I2C_SCL_LCNT_DEFAULT 0x2f
//#define I2C_RX_TL_SET            0xff
//#define I2C_TX_TL_SET            0xff

#define I2C_RX_TL_BY_BYTE 0x0
#define I2C_TX_TL_BY_BYTE 0x0
#define I2C_RX_TL_BY_FIFO 0x01
#define I2C_TX_TL_BY_FIFO 0x01

LOCAL const u32 g_I2cSpeedMask[MAX_I2C_SPEED] = {I2C_STANDARD_SPEED_MASK,
                                                 I2C_FAST_SPEED_MASK,
                                                 I2C_HIGH_SPEED_MASK};
LOCAL const u32 g_I2cSclLcntReg[MAX_I2C_SPEED] = {I2C_SS_SCL_LCNT,
                                                  I2C_FS_SCL_LCNT, I2C_HS_SCL_LCNT};
LOCAL const u32 g_I2cSclHcntReg[MAX_I2C_SPEED] = {I2C_SS_SCL_HCNT,
                                                  I2C_FS_SCL_LCNT, I2C_HS_SCL_LCNT};

void FI2C_resetReg(u32 BaseAddr)
{
    /* set default value for register */
    FI2C_WriteReg(BaseAddr, I2C_CON, I2C_CON_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_TAR, I2C_TAR_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_SAR, I2C_SAR_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_DATA_CMD, I2C_DATA_CMD_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_SS_SCL_LCNT, I2C_SS_SCL_LCNT_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_SS_SCL_HCNT, I2C_SS_SCL_HCNT_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_FS_SCL_LCNT, I2C_FS_SCL_LCNT_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_FS_SCL_HCNT, I2C_FS_SCL_HCNT_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_HS_SCL_LCNT, I2C_HS_SCL_LCNT_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_HS_SCL_HCNT, I2C_HS_SCL_HCNT_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_INTR_MASK, I2C_INTR_MASK_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_RX_TL, I2C_RX_TL_DEFAULT);
    FI2C_WriteReg(BaseAddr, I2C_TX_TL, I2C_TX_TL_DEFAULT);
}

inline LOCAL void FI2C_setSclClk(FT_IN u32 BaseAddr, FT_IN FI2C_SpeedType_t SpeedType,
                                 FT_IN u32 SclLcnt, FT_IN u32 SclHcnt)
{
    u32 SclLcntAddr = g_I2cSclLcntReg[SpeedType];
    u32 SclHcntAddr = g_I2cSclHcntReg[SpeedType];

    FI2C_WriteReg(BaseAddr, SclLcntAddr, SclLcnt);
    FI2C_WriteReg(BaseAddr, SclHcntAddr, SclHcnt);

    return;
}

inline LOCAL void FI2C_setCtrlParam(FT_IN u32 BaseAddr, FT_IN FI2C_SpeedType_t SpeedType, FT_IN bool_t Is7BitAddr)
{
    u32 RegVal;

    RegVal = I2C_CON_ME | g_I2cSpeedMask[SpeedType];
    RegVal |= ((TRUE == Is7BitAddr) ? I2C_CON_MASTER_ADR_7BIT : I2C_CON_MASTER_ADR_10BIT);
    RegVal |= I2C_CON_RESTART_EN | I2C_CON_SLAVE_DISABLE;

    FI2C_WriteReg(BaseAddr, I2C_CON, RegVal);
    return;
}

void FI2C_initMasterCfg(FT_IN FI2C_Instance_t id,
                        FT_IN FI2C_WorkMode_t mode,
                        FT_IN bool_t UseWRFifo,
                        FT_IN u32 PageSize,
                        FT_INOUT FI2C_Config_t *pCfg)
{
    Ft_assertNoneReturn(NULL != pCfg);

    pCfg->InstanceId = id;
    pCfg->BaseAddress = g_FI2cRegBaseAddr[id];
    pCfg->IrqNum = g_FI2cIrqNum[id];
    pCfg->IrqPriority = I2C_DEFAULT_IRQ_PRIORITY;
    pCfg->BusSpeed = I2C_STANDARD_SPEED;
    pCfg->SclLcnt = I2C_SCL_LCNT_DEFAULT;
    pCfg->SclHcnt = I2C_SCL_HCNT_DEFAULT;
    pCfg->WRByFifo = UseWRFifo;
    if (TRUE == pCfg->WRByFifo)
    {
        pCfg->RxThres = I2C_RX_TL_BY_FIFO;
        pCfg->TxThres = I2C_TX_TL_BY_FIFO;
    }
    else
    {
        pCfg->RxThres = I2C_RX_TL_BY_BYTE;
        pCfg->TxThres = I2C_TX_TL_BY_BYTE;
    }
    pCfg->Is7BitAddr = TRUE;
    pCfg->BlockSize = PageSize;

    if (I2C_POLLING_MODE == mode)
    {
        pCfg->IsPolling = TRUE;
    }
    else if (I2C_IRQ_MODE == mode)
    {
        pCfg->IsPolling = FALSE;
    }
    else
    {
        Ft_assertNoneReturn(0);
    }

    return;
}

void FI2C_initMaster(FT_IN FI2C_Instance_t id,
                     FT_IN FI2C_WorkMode_t mode,
                     FT_IN u32 SlaveAddr,
                     FT_IN bool_t UseWRFifo,
                     FT_IN u32 PageSize,
                     FT_INOUT FI2C_t *pDev)
{
    u32 RxDepth;
    u32 TxDepth;

    Ft_assertNoneReturn(NULL != pDev);

    memset(pDev, 0, sizeof(FI2C_t));

    /* setup i2c bus mux */
    Ft_setI2cMux(id);

    /* setup i2c config as master */
    FI2C_initMasterCfg(id, mode, UseWRFifo, PageSize, &pDev->Config);
    pDev->SlaveAddr = SlaveAddr;
    pDev->DelayHandle = Ft_GenericTimer_UsDelay;

    /* init irq handler */
    pDev->pRxEvent = NULL;
    pDev->pTxEvent = NULL;

    pDev->pIrqCallBack = NULL;
    pDev->pWaitCallBack = NULL;

    FI2C_DISABLE_I2C_BUS(pDev);
    FI2C_CLR_ALL_IRQ_STATUS(pDev);

    /* reset reg val */
    FI2C_resetReg(pDev->Config.BaseAddress);

    /* set scl high && low level */
    FI2C_setSclClk(pDev->Config.BaseAddress,
                   pDev->Config.BusSpeed,
                   pDev->Config.SclLcnt,
                   pDev->Config.SclHcnt);

    /* set ctrl parameters */
    FI2C_setCtrlParam(pDev->Config.BaseAddress,
                      pDev->Config.BusSpeed,
                      pDev->Config.Is7BitAddr);

    /* set rx & tx trigger level */
    RxDepth = FI2C_GET_RX_BUFFER_DEPTH(pDev);
    TxDepth = FI2C_GET_TX_BUFFER_DEPTH(pDev);

    /* threshold shall not greater than depth */

    FI2C_SET_TX_TL(pDev, FT_MIN(pDev->Config.TxThres, TxDepth));
    FI2C_SET_RX_TL(pDev, FT_MIN(pDev->Config.RxThres, RxDepth));
    pDev->IsReady = TRUE;
    return;
}

void FI2C_deInitMaster(FT_INOUT FI2C_t *pDev)
{
    /* assert no memory need to release */
    pDev->IsReady = FALSE;
}

inline LOCAL void FI2C_sendRestartCmd(FT_IN u32 BaseAddr)
{
    u32 RegVal = FI2C_ReadReg(BaseAddr, I2C_CON);
    RegVal |= I2C_CON_RESTART_EN;
    FI2C_WriteReg(BaseAddr, I2C_CON, RegVal);
}

inline LOCAL void FI2C_setTarAddr(FT_IN u32 BaseAddr, FT_IN u32 SlaveAddr)
{
    u32 RegVal = (SlaveAddr & I2C_TAR_ADR_MASK);
    FI2C_WriteReg(BaseAddr, I2C_TAR, RegVal);
}

inline LOCAL void FI2C_sendWriteCmd(FT_IN u32 BaseAddr, FT_IN u32 PageAddr)
{
    u32 RegVal = I2C_DATA_CMD_RESTART | (PageAddr & I2C_DATA_CMD_DAT_MASK);
    FI2C_WriteReg(BaseAddr, I2C_DATA_CMD, RegVal);
}

inline LOCAL void FI2C_sendStartReadCmd(FT_IN u32 BaseAddr, FT_IN u32 PageAddr)
{
    /* send read cmd */
    u32 RegVal = I2C_DATA_CMD_STOP | I2C_DATA_CMD_RESTART | (PageAddr & 0xff);
    FI2C_WriteReg(BaseAddr, I2C_DATA_CMD, RegVal);
}

void FI2C_sendStopCmd(FT_IN u32 BaseAddr)
{
    /* send stop signal */
    u32 RegVal = I2C_DATA_CMD_STOP;
    FI2C_WriteReg(BaseAddr, I2C_DATA_CMD, RegVal);
}

LOCAL bool_t FI2C_blockWaitForStatus(FT_IN u32 stMask, FT_INOUT FI2C_t *pDev)
{
    u32 timeout = 0;
    bool_t IsFree = FALSE;

    Ft_assertNoneReturn(NULL != pDev);

    /* Wait until Specific Status Bit in I2C_STATUS is 1 */
    while ((!FI2C_CHECK_STATUS(pDev, stMask)) && (timeout < I2C_TIMEOUT))
    {
        pDev->DelayHandle(5000);
        timeout++;
    }

    /* check if status wait successful or timeout */
    if (I2C_TIMEOUT != timeout)
    {
        IsFree = TRUE;
    }
    else
    {
        FT_I2C_ERROR("wait status 0x%x failed!!! reg val is 0x%x",
                     stMask, FI2C_GET_STATUS(pDev));
    }

    return IsFree;
}

u32 FI2C_writeByByte(FT_IN u32 len, FT_IN u8 *pI2cBuf, FT_IN u8 PageAddr, FT_INOUT FI2C_t *pDev)
{
    u32 loop;
    bool_t isNotTimeout;
    u32 ret = ERR_I2C_OK;
    Ft_assertNoneReturn((NULL != pDev) && (NULL != pI2cBuf));

    if (!pDev->IsReady)
    {
        return ERR_I2C_NOT_READY;
    }

    if (pDev->Config.BlockSize <= len)
    {
        return ERR_I2C_SIZE_TOO_LARGE;
    }

    FI2C_DISABLE_I2C_BUS(pDev);
    FI2C_sendRestartCmd(pDev->Config.BaseAddress);
    FI2C_setTarAddr(pDev->Config.BaseAddress, pDev->SlaveAddr);
    FI2C_ENABLE_I2C_BUS(pDev);

    FI2C_sendWriteCmd(pDev->Config.BaseAddress, PageAddr);

    for (loop = 0; loop < len; loop++)
    {
        if (!pDev->Config.IsPolling)
        {
            FI2C_setIrq(pDev, I2C_IRQ_TX_EMPTY, TRUE);
        }
        pDev->DelayHandle(2);
        FI2C_SET_TX_DATA(pDev, pI2cBuf[loop]);

        /* wait until TX fifo is empty */
        if (pDev->Config.IsPolling)
        {
            isNotTimeout = FI2C_blockWaitForStatus(I2C_STATUS_TFE, pDev);
            if (!isNotTimeout)
            {
                ret = ERR_I2C_WRITE_TIMEOUT;
                goto EXIT;
            }
        }
        else
        {
            pDev->LastIrqErr = ERR_I2C_OK;
            if (pDev->pWaitCallBack)
            {
                pDev->pWaitCallBack(I2C_IRQ_TYPE_TX_COMPLETE, pDev);
            }
            else
            {
                ret = ERR_I2C_INVALID_HANDLER;
                goto EXIT;
            }

            if (ERR_I2C_OK != pDev->LastIrqErr)
            {
                ret = pDev->LastIrqErr;
                goto EXIT;
            }
        }

        pDev->DelayHandle(2);
    }

EXIT:
    FI2C_SEND_TX_STOP_CMD(pDev);
    pDev->DelayHandle(2);

    return ret;
}

u32 FI2C_readByByte(FT_IN u32 len, FT_OUT u8 *pI2cBuf, FT_IN u8 PageAddr, FT_INOUT FI2C_t *pDev)
{
    u32 loop;
    bool_t isNotTimeout;
    u32 ret = ERR_I2C_OK;
    Ft_assertNoneReturn((NULL != pDev) && (NULL != pI2cBuf));

    if (!pDev->IsReady)
    {
        return ERR_I2C_NOT_READY;
    }

    FI2C_DISABLE_I2C_BUS(pDev);
    FI2C_sendRestartCmd(pDev->Config.BaseAddress);
    FI2C_CLR_ALL_IRQ_STATUS(pDev);
    FI2C_setTarAddr(pDev->Config.BaseAddress, pDev->SlaveAddr);
    FI2C_ENABLE_I2C_BUS(pDev);

    /* assign page addr when start read */
    FI2C_sendStartReadCmd(pDev->Config.BaseAddress, PageAddr);

    /* read contents */
    for (loop = 0; loop < len; loop++)
    {
        if (!pDev->Config.IsPolling)
        {
            FI2C_setIrq(pDev, I2C_IRQ_RX_FULL, TRUE);
        }

        FI2C_SEND_RX_NEXT_CMD(pDev);
        pDev->DelayHandle(2);

        /* wait until data reach and start fetch data */
        if (pDev->Config.IsPolling)
        {
            isNotTimeout = FI2C_blockWaitForStatus(I2C_STATUS_RFNE, pDev);
            if (!isNotTimeout)
            {
                ret = ERR_I2C_READ_TIMEOUT;
                goto EXIT;
            }
        }
        else
        {
            pDev->LastIrqErr = ERR_I2C_OK;
            if (pDev->pWaitCallBack)
            {
                pDev->pWaitCallBack(I2C_IRQ_TYPE_RX_COMPLETE, pDev);
            }
            else
            {
                ret = ERR_I2C_INVALID_HANDLER;
                goto EXIT;
            }

            if (ERR_I2C_OK != pDev->LastIrqErr)
            {
                ret = pDev->LastIrqErr;
                goto EXIT;
            }
        }

        pI2cBuf[loop] = FI2C_GET_RX_DATA(pDev);
        pDev->DelayHandle(2);
    }

EXIT:
    FI2C_SEND_RX_STOP_CMD(pDev);
    pDev->DelayHandle(2);
    return ret;
}

u32 FI2C_writeByFifo(FT_IN u8 PageAddr, FT_INOUT FI2C_t *pDev)
{
    u32 loop;
    u32 ret = ERR_I2C_OK;
    u32 timeout = I2C_TIMEOUT / 10;
    Ft_assertNoneReturn(NULL != pDev);

    if (!pDev->IsReady)
    {
        return ERR_I2C_NOT_READY;
    }

    if (pDev->Config.IsPolling)
    {
        return ERR_I2C_NOT_SUPPORT;
    }

    FI2C_DISABLE_I2C_BUS(pDev);
    FI2C_sendRestartCmd(pDev->Config.BaseAddress);
    FI2C_setTarAddr(pDev->Config.BaseAddress, pDev->SlaveAddr);
    FI2C_ENABLE_I2C_BUS(pDev);

    FI2C_sendWriteCmd(pDev->Config.BaseAddress, PageAddr);

    /* enable TX Empty, disable Rx Full */
    FI2C_setIrq(pDev, I2C_IRQ_TX_EMPTY, TRUE);
    FI2C_setIrq(pDev, I2C_IRQ_RX_FULL, FALSE);

    pDev->LastIrqErr = ERR_I2C_OK;
    if (pDev->pWaitCallBack)
    {
        pDev->pWaitCallBack(I2C_IRQ_TYPE_TX_COMPLETE, pDev);
    }
    else
    {
        ret = ERR_I2C_INVALID_HANDLER;
    }

    if (ERR_I2C_OK != pDev->LastIrqErr)
    {
        ret = pDev->LastIrqErr;
    }

    return ret;
}

u32 FI2C_readByFifo(FT_IN u8 PageAddr, FT_INOUT FI2C_t *pDev)
{
    u32 loop;
    u32 ret = ERR_I2C_OK;
    u32 timeout = I2C_TIMEOUT / 10;
    Ft_assertNoneReturn((NULL != pDev));

    if (!pDev->IsReady)
    {
        return ERR_I2C_NOT_READY;
    }

    if (pDev->Config.IsPolling)
    {
        return ERR_I2C_NOT_SUPPORT;
    }

    FI2C_DISABLE_I2C_BUS(pDev);
    FI2C_sendRestartCmd(pDev->Config.BaseAddress);
    FI2C_setTarAddr(pDev->Config.BaseAddress, pDev->SlaveAddr);
    FI2C_ENABLE_I2C_BUS(pDev);

    /* assign page addr when start read */
    FI2C_sendStartReadCmd(pDev->Config.BaseAddress, PageAddr);

    FI2C_setIrq(pDev, I2C_IRQ_RX_FULL, TRUE);
    FI2C_setIrq(pDev, I2C_IRQ_TX_EMPTY, FALSE);
    FI2C_SET_RX_TL(pDev, 1);

    pDev->DelayHandle(2);
    FT_I2C_DEBUG_I("rx tl is 0x%x irq mask 0x%x",
                   FI2C_GET_RX_TL(pDev),
                   FI2C_getIrqMask(pDev));

    FI2C_SEND_RX_NEXT_CMD(pDev);
    pDev->DelayHandle(2);

    pDev->LastIrqErr = ERR_I2C_OK;
    if (pDev->pWaitCallBack)
    {
        pDev->pWaitCallBack(I2C_IRQ_TYPE_RX_COMPLETE, pDev);
    }
    else
    {
        ret = ERR_I2C_INVALID_HANDLER;
    }

    if (ERR_I2C_OK != pDev->LastIrqErr)
    {
        ret = pDev->LastIrqErr;
    }
    FI2C_SET_RX_TL(pDev, 0);
    return ret;
}
