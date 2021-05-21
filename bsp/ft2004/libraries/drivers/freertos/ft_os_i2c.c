/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-21 09:29:56
 * @LastEditTime: 2021-04-23 10:11:00
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <string.h>
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>
#include "ft_os_i2c.h"
#include "ft_i2c.h"
#include "system_gic.h"

static FI2C_t g_I2cCtrl[MAX_I2C_CTRL_ID];

inline static FI2C_t *FOS_getI2cCtrl(FI2C_Instance_t id)
{
    return &g_I2cCtrl[id];
}

static void FOS_waitI2cCallback(const u32 IrqType,
                                void *pArg)
{
    FI2C_t *pDev = (FI2C_t *)pArg;
    u32 irqMask;

    /* wait for TX over signal */
    EventBits_t ev = 0;

    Ft_assertNoneReturn(NULL != pDev);

    irqMask = FI2C_getIrqMask(pDev);
    FI2C_setIrqMask(pDev, irqMask);

    FT_I2C_DEBUG_I("%d wait for event mask 0x%x", IrqType, FI2C_getIrqMask(pDev));
    switch (IrqType)
    {
    case I2C_IRQ_TYPE_TX_COMPLETE:
        ev = xEventGroupWaitBits(pDev->pTxEvent, 
                                 FOS_I2C_TX_OVER_EVT,
                                 pdTRUE, pdFALSE, I2C_TIMEOUT);
        break;
    case I2C_IRQ_TYPE_RX_COMPLETE:
        ev = xEventGroupWaitBits(pDev->pRxEvent, 
                                 FOS_I2C_RX_OVER_EVT,
                                 pdTRUE, pdFALSE, I2C_TIMEOUT);
        break; 
    default:
        Ft_assertNoneReturn(0);
        break;
    }

    if (ev & FOS_I2C_TX_OVER_EVT)
    {
        FT_I2C_DEBUG_I("recev tx over event");
    }
    else if (ev & FOS_I2C_RX_OVER_EVT)
    {
        FT_I2C_DEBUG_I("recev rx over event");
    }
    else
    {
        FT_I2C_ERROR("wait evt timeout");
        pDev->LastIrqErr = ERR_I2C_EVT_TIMEOUT;
    }

    return;
}

static void FOS_irqI2cCallback(const u32 IrqType,
                               void *pArg,
                               void *pData)
{
    FI2C_t *pDev = (FI2C_t *)pArg;

    /* send RX over signal */
    BaseType_t xResult = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    Ft_assertNoneReturn((NULL != pDev));

    switch (IrqType)
    {
    case I2C_IRQ_TYPE_TX_COMPLETE:
        xResult = xEventGroupSetBitsFromISR(pDev->pTxEvent, 
                                            FOS_I2C_TX_OVER_EVT,
                                            &xHigherPriorityTaskWoken);       
        break;
    case I2C_IRQ_TYPE_RX_COMPLETE:
        xResult = xEventGroupSetBitsFromISR(pDev->pRxEvent, 
                                            FOS_I2C_RX_OVER_EVT,
                                            &xHigherPriorityTaskWoken);    
        break;
    default:
        Ft_assertNoneReturn(0);
        break;
    }
    FT_I2C_DEBUG_I("send signal %d, result %d", IrqType, xResult);

    if (pdFAIL != xResult)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    return;    
}

void FOS_deInitI2cCtrl(FI2C_Instance_t Id)
{
    FI2C_deInitMaster(FOS_getI2cCtrl(Id));
}

u32 FOS_initI2cCtrl(FOS_I2cConfig_t *pConf)
{
    u32 ret = ERR_I2C_OK;
    u32 irqMask;
    u32 txBufSize;
    u32 rxBufSize;
    FI2C_t *pCtrl = FOS_getI2cCtrl(pConf->Id);
    if (I2C_MASTER_DEV == pConf->DevType)
    {
        FI2C_initMaster(pConf->Id, pConf->WorkMode,pConf->SlaveAddr,
                        pConf->UseWRFIFO,
                        pConf->PageSize, pCtrl);
    }
    else
    {
        return ERR_I2C_NOT_SUPPORT;
    }

    if (ERR_I2C_OK != ret)
    {
        return ret;
    }

    if (I2C_IRQ_MODE == pConf->WorkMode)
    {
        /* enable some irq */
        irqMask = I2C_IRQ_TX_ABRT | I2C_IRQ_STOP_DET |
                  I2C_IRQ_START_DET | I2C_IRQ_RX_OVER | I2C_IRQ_RX_FULL | 
                  I2C_IRQ_TX_OVER | I2C_IRQ_TX_EMPTY;

        //I2C_IRQ_DEFAULT_MASK; //I2C_IRQ_RX_OVER | I2C_IRQ_TX_OVER;
        FI2C_setIrqMask(pCtrl, irqMask);
        //FT_I2C_DEBUG_I("set irq mask 0x%x", FI2C_getIrqMask(pCtrl));

        /* register irq handler */
        pCtrl->pIrqCallBack = FOS_irqI2cCallback;
        pCtrl->pWaitCallBack = FOS_waitI2cCallback;

        /* create sync event */
        pCtrl->pRxEvent = xEventGroupCreate();
        pCtrl->pTxEvent = xEventGroupCreate();
        if (!pCtrl->pRxEvent || !pCtrl->pTxEvent)
        {
            FT_I2C_ERROR("alloc event failed!!!");
            ret = ERR_I2C_INVALID_NO_MEM;
            goto EXIT;
        }

        /* register i2c irq to gic */
        if (pConf->UseWRFIFO)
        {
            System_Gic_Enable(g_FI2cIrqNum[pConf->Id], 
                            (FGicv3_interruptHandler)FI2C_irqHandler4Fifo, 
                            I2C_DEFAULT_IRQ_PRIORITY, 
                            pCtrl);            
        }
        else
        {
            System_Gic_Enable(g_FI2cIrqNum[pConf->Id], 
                            (FGicv3_interruptHandler)FI2C_irqHandler, 
                            I2C_DEFAULT_IRQ_PRIORITY, 
                            pCtrl);
        }
    }

EXIT:
    return ret;
}

u32 FOS_i2cRead(FOS_I2cConfig_t *pConf)
{
    FI2C_t *pDev = FOS_getI2cCtrl(pConf->Id);
    FI2C_Buffer_t *pBuf = &pDev->RxBuf;
    u32 ret;
    if (pConf->UseWRFIFO)
    {
        pBuf->BytePtr = pConf->pRxBuf;
        pBuf->DataLength = pConf->RxBufSize ;
        pBuf->CurIndex = 0;
        ret = FI2C_readByFifo(pConf->PageAddr, pDev);
    }
    else
    {
        ret =  FI2C_readByByte(pConf->RxBufSize, pConf->pRxBuf, 
                               pConf->PageAddr, pDev);        
    }

    return ret;
}

u32 FOS_i2cWrite(FOS_I2cConfig_t *pConf)
{
    FI2C_t *pDev = FOS_getI2cCtrl(pConf->Id);
    FI2C_Buffer_t *pBuf = &pDev->TxBuf;
    u32 ret = ERR_I2C_OK;
    if (pConf->UseWRFIFO)
    {
        pBuf->BytePtr = pConf->pTxBuf;
        pBuf->DataLength = pConf->TxBufSize;
        pBuf->CurIndex = 0;

        ret = FI2C_writeByFifo(pConf->PageAddr, pDev); 
    }
    else
    {
        ret = FI2C_writeByByte(pConf->TxBufSize, pConf->pTxBuf, 
                            pConf->PageAddr, pDev);        
    }

    return ret;
}