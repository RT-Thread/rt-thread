/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-20 15:35:44
 * @LastEditTime: 2021-05-25 16:44:45
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_i2c.h"

void FI2C_irqHandler(void *pArgs)
{
    FI2C_t *pDev;
    u32 RegVal;
    FI2C_IrqType_t IrqType = I2C_IRQ_TYPE_NONE;

    Ft_assertNoneReturn(NULL != pArgs);
    pDev = (FI2C_t *)pArgs;

    RegVal = FI2C_GET_IRQ_STATUS(pDev);
    if (I2C_IRQ_RX_FULL & RegVal)
    {
        IrqType = I2C_IRQ_TYPE_RX_COMPLETE;
    }
    else if (I2C_IRQ_TX_EMPTY & RegVal)
    {
        IrqType = I2C_IRQ_TYPE_TX_COMPLETE;
    }

    if ((NULL != pDev->pIrqCallBack) && (I2C_IRQ_TYPE_NONE != IrqType))
    {
        pDev->pIrqCallBack(IrqType, pDev, NULL);
    }

    if (I2C_IRQ_TYPE_RX_COMPLETE == IrqType)
    {
        FI2C_setIrq(pDev, I2C_IRQ_RX_FULL, FALSE);
    }
    else if (I2C_IRQ_TYPE_TX_COMPLETE == IrqType)
    {
        FI2C_setIrq(pDev, I2C_IRQ_TX_EMPTY, FALSE);
    }

    FI2C_CLR_ALL_IRQ_STATUS(pDev);
    return;
}

void FI2C_irqHandler4Fifo(void *pArgs)
{
    FI2C_t *pDev;
    u32 RegVal;
    u32 BytesToRx;
    FI2C_IrqType_t IrqType = I2C_IRQ_TYPE_NONE;

    Ft_assertNoneReturn(NULL != pArgs);
    pDev = (FI2C_t *)pArgs;

    /* check if i2c controller is enabled */
    if (!FI2C_IS_I2C_BUS_ENABLED(pDev))
    {
        pDev->LastIrqErr = ERR_I2C_BUS_NOT_ENABLED;
        return;
    }

    /* check there is no interrupt */
    if (!FI2C_checkIfIntr(pDev))
    {
        pDev->LastIrqErr = ERR_I2C_INVALID_PARAM;
        return;
    }

    /* read interrupt status  */
    RegVal = FI2C_GET_IRQ_STATUS(pDev);
    if (I2C_IRQ_RX_FULL & RegVal)
    {
        IrqType = I2C_IRQ_TYPE_RX_COMPLETE;
        BytesToRx = FI2C_GET_RXFLR(pDev);

        while ((pDev->RxBuf.CurIndex < pDev->RxBuf.DataLength) &&
               (0 < BytesToRx))
        {
            /* read one byte */
            pDev->RxBuf.BytePtr[pDev->RxBuf.CurIndex] = FI2C_GET_RX_DATA(pDev);

            pDev->RxBuf.CurIndex++;
            BytesToRx--;
            pDev->DelayHandle(10);

            /* read next byte */
            if (pDev->RxBuf.CurIndex != pDev->RxBuf.DataLength)
            {
                FI2C_SEND_RX_NEXT_CMD(pDev);
            }
            else
            {
                FI2C_SEND_RX_STOP_CMD(pDev);
                pDev->DelayHandle(10);
                FI2C_setIrq(pDev, I2C_IRQ_RX_FULL, FALSE);
            }
        }
    }
    else if (I2C_IRQ_TX_EMPTY & RegVal)
    {
        IrqType = I2C_IRQ_TYPE_TX_COMPLETE;

        if (pDev->TxBuf.CurIndex == pDev->TxBuf.DataLength)
        {
            FI2C_SEND_TX_STOP_CMD(pDev);
            pDev->DelayHandle(10);
            FI2C_setIrq(pDev, I2C_IRQ_TX_EMPTY, FALSE);
        }
        else
        {
            FI2C_SET_TX_DATA(pDev, pDev->TxBuf.BytePtr[pDev->TxBuf.CurIndex]);
            pDev->TxBuf.CurIndex++;
        }
    }

    if ((NULL != pDev->pIrqCallBack) && (I2C_IRQ_TYPE_NONE != IrqType))
    {
        pDev->pIrqCallBack(IrqType, pDev, NULL);
    }

    pDev->LastIrqErr = ERR_I2C_OK;
    return;
}

u32 FI2C_getIrqMask(FT_IN FI2C_t *pDev)
{
    u32 RegVal;
    Ft_assertNoneReturn(NULL != pDev);

    RegVal = FI2C_GET_IRQ_MASK(pDev);
    return RegVal;
}

void FI2C_setIrqMask(FT_IN FI2C_t *pDev, FT_IN u32 mask)
{
    u32 RegVal;
    Ft_assertNoneReturn(NULL != pDev);

    RegVal = mask & I2C_IRQ_ALL_MASK;
    FI2C_SET_IRQ_MASK(pDev, RegVal);
    return;
}

void FI2C_setIrq(FT_IN FI2C_t *pDev, FT_IN u32 maskBit, FT_IN bool_t enable)
{
    Ft_assertNoneReturn(0x0 != maskBit);

    if (TRUE == enable)
    {
        FI2C_setIrqMask(pDev, FI2C_getIrqMask(pDev) | maskBit);
    }
    else
    {
        FI2C_setIrqMask(pDev, FI2C_getIrqMask(pDev) & (~maskBit));
    }
    return;
}

bool_t FI2C_checkIfIntr(FT_IN FI2C_t *pDev)
{
    u32 RegVal;
    Ft_assertNoneReturn(NULL != pDev);

    RegVal = FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_RAW_INTR_STAT);
    if (0 == (RegVal & (~I2C_IRQ_ACTIVITY)))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
