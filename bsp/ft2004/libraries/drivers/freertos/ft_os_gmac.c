/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:00:19
 * @Description:  This files is for freertos gmac ports
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_os_gmac.h"
#include "ft_gmac.h"
#include "ft_assert.h"
#include "ft_io.h"
#include "system_gic.h"
#include "ft_list.h"
#include "ft_debug.h"

#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

#include <string.h>

#define OS_MAC_DEBUG_TAG "OS_MAC"

#define OS_MAC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(OS_MAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define OS_MAC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(OS_MAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define OS_MAC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(OS_MAC_DEBUG_TAG, format, ##__VA_ARGS__)

#define FT_OS_GMACOBJECT_READLY 0x58

/**
 * @name: Ft_Os_GmacMem_Create
 * @msg:  Initialize the Gmac TX/Rx Describe Memory 。
 * @param {*}
 * @return {*}
 */
static void Ft_Os_GmacMem_Create(Ft_Os_Gmac *Os_Gmac)
{
    Os_Gmac->Rxbuffer = pvPortMalloc(RX_DESCNUM * GMAC_MAX_PACKET_SIZE);
    if (Os_Gmac->Rxbuffer == NULL)
    {
        OS_MAC_DEBUG_E("Rxbuffer Malloc is error ");
        Ft_assertVoidAlways();
    }

    Os_Gmac->Txbuffer = pvPortMalloc(TX_DESCNUM * GMAC_MAX_PACKET_SIZE);
    if (Os_Gmac->Txbuffer == NULL)
    {
        OS_MAC_DEBUG_E("Txbuffer Malloc is error ");
        Ft_assertVoidAlways();
    }

    Os_Gmac->Gmac.TxDesc = pvPortMalloc(TX_DESCNUM * sizeof(FGmac_DmaDesc_t));
    if (Os_Gmac->Gmac.TxDesc == NULL)
    {
        OS_MAC_DEBUG_E("TxDesc Malloc is error ");
        Ft_assertVoidAlways();
    }

    Os_Gmac->Gmac.RxDesc = pvPortMalloc(RX_DESCNUM * sizeof(FGmac_DmaDesc_t) + 128);
    if (Os_Gmac->Gmac.RxDesc == NULL)
    {
        OS_MAC_DEBUG_E("RxDesc Malloc is error ");
        Ft_assertVoidAlways();
    }

    OS_MAC_DEBUG_E("RxDesc fit before addr %x ", Os_Gmac->Gmac.RxDesc);

#define ROUND_UP(x, align) (((long)(x) + ((long)align - 1)) & \
                            ~((long)align - 1))

    Os_Gmac->Gmac.RxDesc = (FGmac_DmaDesc_t *)ROUND_UP(Os_Gmac->Gmac.RxDesc, 128);
    OS_MAC_DEBUG_E("RxDesc fit after addr %x ", Os_Gmac->Gmac.RxDesc);
}

static void Ft_Os_GmacMem_Free(Ft_Os_Gmac *Os_Gmac)
{
    if (Os_Gmac->Rxbuffer)
    {
        vPortFree(Os_Gmac->Rxbuffer);
    }

    if (Os_Gmac->Txbuffer)
    {
        vPortFree(Os_Gmac->Txbuffer);
    }

    if (Os_Gmac->Gmac.RxDesc)
    {
        vPortFree(Os_Gmac->Gmac.RxDesc);
    }

    if (Os_Gmac->Gmac.TxDesc)
    {
        vPortFree(Os_Gmac->Gmac.TxDesc);
    }
}

/**
 * @name: Ft_Os_GmacObject_Init
 * @msg:  
 * @param {Ft_Os_Gmac} *Os_Gmac
 * @param {Ft_Os_Gmac_Config} *Config
 * @return {*}
 */
void Ft_Os_GmacObject_Init(Ft_Os_Gmac *Os_Gmac, Ft_Os_Gmac_Config *Config)
{
    Ft_assertVoid(Os_Gmac != NULL);
    Ft_assertVoid(Os_Gmac->IsReady != FT_OS_GMACOBJECT_READLY);
    memset(Os_Gmac, 0, sizeof(Ft_Os_Gmac));
    Os_Gmac->Config = *Config;
    Os_Gmac->IsReady = FT_OS_GMACOBJECT_READLY;
}

/**
 * @name: Ft_Os_Gmac_Init
 * @msg: 
 * @param {Ft_Os_Gmac} *Os_Gmac
 * @param {u32} InstanceId
 * @return {*}
 */
void Ft_Os_Gmac_Init(Ft_Os_Gmac *Os_Gmac)
{
    Ft_Gmac_t *Gmac;
    Ft_assertVoid(Os_Gmac != NULL);
    Ft_assertVoid((Os_Gmac->IsReady == FT_OS_GMACOBJECT_READLY));
    Gmac = &Os_Gmac->Gmac;
    Ft_Os_GmacMem_Free(Os_Gmac);
    Ft_assertVoid(Ft_GmacCfgInitialize(Gmac, Ft_Gmac_LookupConfig(Os_Gmac->Config.Gmac_Instance)) == FST_SUCCESS);
    Ft_Os_GmacMem_Create(Os_Gmac);

    /* Create a binary semaphore used for informing ethernetif of frame reception */
    Ft_assertVoid((Os_Gmac->s_xSemaphore = xSemaphoreCreateBinary()) != NULL);
    /* Create a event group used for ethernetif of status change */
    Ft_assertVoid((Os_Gmac->s_xStatusEvent = xEventGroupCreate()) != NULL);
}

/**
 * @name: Ft_Os_Gmac_Start
 * @msg: 
 * @param {Ft_Os_Gmac} *Os_Gmac
 * @return {*}
 */
void Ft_Os_Gmac_Start(Ft_Os_Gmac *Os_Gmac)
{
    Ft_Gmac_t *Gmac;
    Ft_assertVoid(Os_Gmac != NULL);
    Ft_assertVoid((Os_Gmac->IsReady == FT_OS_GMACOBJECT_READLY));
    Gmac = &Os_Gmac->Gmac;
    u32 ret;

    ret = Ft_Gmac_HwInitialize(Gmac);
    if (FST_SUCCESS != ret)
    {
        OS_MAC_DEBUG_E("Gmac return err code %d\r\n", ret);
        Ft_assertVoid(FST_SUCCESS == ret);
    }

    /* Initialize Rx Description list : ring Mode */
    FGmac_DmaRxDescRingInit(Gmac, Gmac->RxDesc, Os_Gmac->Rxbuffer, GMAC_MAX_PACKET_SIZE, RX_DESCNUM);

    /* Initialize Tx Description list : ring Mode */
    FGmac_DmaTxDescRingInit(Gmac, Gmac->TxDesc, Os_Gmac->Txbuffer, GMAC_MAX_PACKET_SIZE, TX_DESCNUM);

    Ft_Gmac_Start(Gmac);
    /* Gmac interrupt init */
    System_Gic_Enable(Gmac->Config.IRQ_NUM, (FGicv3_InterruptHandler_t)FGmac_IntrHandler, Gmac->Config.IRQPriority, Gmac);

    return;
}

void Ft_Os_Gmac_Stop(Ft_Os_Gmac *Os_Gmac)
{
    Ft_Gmac_t *Gmac;

    Ft_assertVoid(Os_Gmac != NULL);
    Ft_assertVoid((Os_Gmac->IsReady == FT_OS_GMACOBJECT_READLY));
    Gmac = &Os_Gmac->Gmac;
    Ft_Gmac_Stop(Gmac);
}