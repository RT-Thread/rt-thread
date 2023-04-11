/***************************************************************************//**
* \file cy_ipc_bt.c
* \version 1.80
*
* \brief
*  This driver provides the source code for BT IPC.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXIPC)

#include "cy_ipc_bt.h"

/* Should not include this. To be removed */
#include <string.h>

#include <stdio.h>

CY_MISRA_DEVIATE_BLOCK_START('ARRAY_VS_SINGLETON', 1, \
'Checked manually. Using pointer as an array will not corrupt or misinterpret adjacent memory locations.');

//#define BTIPC_DBG_L0
//#define BTIPC_DBG_L1
//#define BTIPC_DBG_L2
//#define BTIPC_STATUS

/** Buffer descriptor offset in the init message */
#ifndef BT_OLD_INIT
#define INIT_IPC_BUFF_DESC_OFFSET 5
#else
#define INIT_IPC_BUFF_DESC_OFFSET 1
#endif

#ifdef BTIPC_DBG_L0
#define BTIPC_LOG_L0(...)   printf(__VA_ARGS__)
#else
#define BTIPC_LOG_L0(...)
#endif

#ifdef BTIPC_DBG_L1
#define BTIPC_LOG_L1(...)   printf(__VA_ARGS__)
#else
#define BTIPC_LOG_L1(...)
#endif

#ifdef BTIPC_DBG_L2
#define BTIPC_LOG_L2(...)   printf(__VA_ARGS__)
#else
#define BTIPC_LOG_L2(...)
#endif

/* local functions prototype */
cy_en_btipcdrv_status_t Cy_bt_handle_hpclong_msg(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t * msgPtr);
cy_en_btipcdrv_status_t Cy_bt_handle_buf_add(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t * msgPtr);
static cy_en_btipc_buftype_t Cy_bt_get_buf_type(cy_en_btipc_hcipti_t pti);
static uint32_t Cy_bt_getPLLegnth(cy_en_btipc_hcipti_t pti, uint8_t* bufAddr);
static bool Cy_bt_isOffsetNeeded(cy_en_btipc_hcipti_t pti);
static cy_en_btipcdrv_status_t Cy_bt_GetBuffer (cy_stc_ipc_bt_context_t *btIpcContext, void **ppBuf, cy_en_btipc_buftype_t bufType, size_t length);
static cy_en_btipcdrv_status_t Cy_bt_PutBuffer(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_buf_t *bufDecriptor);
static cy_en_btipcdrv_status_t Cy_BTIPC_HCI_FIFOPut(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t *pMsg);
cy_en_btipcdrv_status_t Cy_BTIPC_HPC_RelBuffer(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t* msgPtr);

CY_IPC_SECTION_BEGIN
void Cy_BTIPC_IRQ_Handler(cy_stc_ipc_bt_context_t *btIpcContext)
{
    uint32_t shadowIntr;
    IPC_STRUCT_Type *ipcPtr;
    IPC_INTR_STRUCT_Type *ipcIntrPtr;
    uint32_t mesg[2], backup[2];
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t notify;
    uint32_t release;
    uint32_t channelHCI;
    uint32_t channelHPC;
    uint8_t idx;
    cy_en_btipc_hpcpti_t msgType;

    if (NULL == contextPtr)
    {
        BTIPC_LOG_L0("Context ptr null\n");
        return;
    }

#ifdef CY_BTIPC_STATS
    contextPtr->ipc_int_count++;
#endif

    ipcIntrPtr = Cy_IPC_Drv_GetIntrBaseAddr(contextPtr->intStuctureSelf);
    shadowIntr = Cy_IPC_Drv_GetInterruptStatusMasked(ipcIntrPtr);

    notify = Cy_IPC_Drv_ExtractAcquireMask(shadowIntr);

    /* Check to make sure the interrupt was a release interrupt */
    release = Cy_IPC_Drv_ExtractReleaseMask(shadowIntr);

    BTIPC_LOG_L1("shadow 0x%lx, notifyMask 0x%lx, relMask 0x%lx\n", shadowIntr, notify, release);

    /* First process the release callback */
    if (0UL != release)  /* Check for a Release interrupt */
    {
        BTIPC_LOG_L1("Release int\n");
        /* Clear the release interrupt  */
        Cy_IPC_Drv_ClearInterrupt(ipcIntrPtr, release, CY_IPC_NO_NOTIFICATION);
#ifdef CY_BTIPC_STATS
        if ((release & (uint32_t)(0x1UL << contextPtr->ulChannelHPC)) != 0UL)
        {
            contextPtr->ipc_hpc_release_count++;
        }
        if ((release & (uint32_t)(0x1UL << contextPtr->ulChannelHCI)) != 0UL)
        {
            contextPtr->ipc_hci_release_count++;
        }
#endif
        /* release callback can be added here. */
        if ((contextPtr->ulReleaseCallbackPtr) != NULL )
        {
            contextPtr->ulReleaseCallbackPtr();
        }
    }

    /* Check to make sure the interrupt was a notify interrupt */
    if (0UL != notify)
    {
        BTIPC_LOG_L1("Notify int ");
        /* Clear the notify interrupt.  */
        Cy_IPC_Drv_ClearInterrupt(ipcIntrPtr, CY_IPC_NO_NOTIFICATION, notify);

        if ((notify & (uint32_t)(0x1UL << contextPtr->dlChannelHPC)) != 0UL)
        {
#ifdef CY_BTIPC_STATS
            contextPtr->ipc_hpc_notify_count++;
            if (contextPtr->ipc_hci_fifo_full > 0UL)
            {
                contextPtr->ipc_hci_notify_in_fifo_full++;
            }
#endif
            channelHPC = contextPtr->dlChannelHPC;

            BTIPC_LOG_L1("on ch %ld\n",channelHPC);

            ipcPtr = Cy_IPC_Drv_GetIpcBaseAddress(channelHPC);
            Cy_IPC_Drv_ReadDDataValue(ipcPtr, mesg);
            /* Keep back up of mesg needed to release the buffer */
            backup[0] = mesg[0];
            backup[1] = mesg[1];

            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_btipc_hpcpti_t enum.');
            msgType = (cy_en_btipc_hpcpti_t)((0xFFUL) & mesg[0]);

            BTIPC_LOG_L1("HPC payload type %d\n",msgType);

            if ((contextPtr->internal_hpc_notify_cb) != NULL)
            {
                BTIPC_LOG_L1("Notify HPC int cb+\n");
                contextPtr->internal_hpc_notify_cb((void*)contextPtr, mesg);
                BTIPC_LOG_L1("Notify HPC int cb-\n");
            }
            for (idx = 0; idx < ((uint8_t)MAX_BT_IPC_HPC_CB); idx++)
            {
                BTIPC_LOG_L1("idx %d, Notify HPC cb %p, msgType %d\n",idx, contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr, contextPtr->hpcNotifyCallbackParam[idx].msgType);
                if ((contextPtr->hpcNotifyCallbackParam[idx].msgType == msgType) &&
                    (contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr != NULL))
                {
                   BTIPC_LOG_L1("Calling Notify HPC cb %p\n",contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr);
                    if ((msgType == CY_BT_IPC_HPC_LONG) && (*(((uint8_t*)mesg)+1) == (uint8_t)CY_BT_IPC_HPC_INIT))
                    {
                        /* Add Boot type to the message add pass it to the application */
                        *(((uint8_t*)mesg)+2) = contextPtr->bootType;
                        /* Certificate error field, so that the app can process if needed */
                        mesg[1] = contextPtr->certError;
                    }
                    contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr(mesg);
                }
            }
            /* Release channel for HPC message only */
            (void)Cy_BTIPC_HPC_RelChannel(contextPtr, backup); /* Suppress a compiler warning about unused return value */
#ifdef CY_BTIPC_STATS
            contextPtr->ipc_hpc_peer_release_count++;
#endif
            if (0xFFUL == (0xFFUL & mesg[0]))
            {
                (void)Cy_BTIPC_HPC_RelBuffer(contextPtr, backup); /* Suppress a compiler warning about unused return value */
            }
        }

        if ((notify & (uint32_t)(0x1UL << contextPtr->dlChannelHCI)) != 0UL)
        {
#ifdef CY_BTIPC_STATS
            contextPtr->ipc_hci_notify_count++;
#endif
            channelHCI = contextPtr->dlChannelHCI;

            BTIPC_LOG_L1("on ch %ld\n",channelHCI);

            ipcPtr = Cy_IPC_Drv_GetIpcBaseAddress(channelHCI);
            Cy_IPC_Drv_ReadDDataValue(ipcPtr, mesg);
            /* Push the mesg to FIFO */
            if (((uint32_t)Cy_BTIPC_HCI_FIFOPut(contextPtr, mesg)) == 0UL)
            {
                if (((uint16_t)MAX_IPC_FIFO_SIZE) > Cy_BTIPC_HCI_FIFOCount(contextPtr))
                {
                    /* Release channel for HCI message only if FIFO is not full */
                    (void)Cy_BTIPC_HCI_RelChannel(contextPtr); /* Suppress a compiler warning about unused return value */
#ifdef CY_BTIPC_STATS
                    contextPtr->ipc_hci_peer_release_count++;
#endif
                }
                else
                {
                    contextPtr->ipc_hci_fifo_full++;
                    BTIPC_LOG_L0("\nFIFO is Full. Ch 0x%lx not released !\n",channelHCI);
                }
                BTIPC_LOG_L1("FIFO count %d\n",contextPtr->IpcFifo.bufLen);

                /* call the callback function */
                if ((contextPtr->dlNotifyCallbackPtr) != NULL)
                {

                    BTIPC_LOG_L1("Notify HCI cb\n");
                    contextPtr->dlNotifyCallbackPtr(mesg);
                }
            }
            else
            {
                BTIPC_LOG_L0("Error: Msg received after FIFO is full !\n");
                contextPtr->droppedHCI++;
                /* Add assert here */
                CY_ASSERT_L1(false);
                return;
            }
        }
    }
}
CY_IPC_SECTION_END

CY_IPC_SECTION_BEGIN
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_RelChannel(cy_stc_ipc_bt_context_t *btIpcContext)
{
    IPC_STRUCT_Type *ipcPtr;
    uint32_t rel_mask;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;

    if (NULL == contextPtr)
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    ipcPtr = Cy_IPC_Drv_GetIpcBaseAddress (contextPtr->dlChannelHCI);

    rel_mask = (uint32_t)(1UL << contextPtr->intStucturePeer);

    Cy_IPC_Drv_ReleaseNotify(ipcPtr, rel_mask);

    return CY_BT_IPC_DRV_SUCCESS;
}
CY_IPC_SECTION_END


cy_en_btipcdrv_status_t Cy_BTIPC_HPC_RelChannel(cy_stc_ipc_bt_context_t *btIpcContext, void * buf)
{
    IPC_STRUCT_Type *ipcPtr;
    uint32_t rel_mask;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    (void)buf;
    // Fix if this is causing issue
#if 1
    if ((NULL == contextPtr) || (NULL == buf))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }
#endif

    ipcPtr = Cy_IPC_Drv_GetIpcBaseAddress (contextPtr->dlChannelHPC);

    rel_mask = (uint32_t)(1UL << contextPtr->intStucturePeer);
    BTIPC_LOG_L1("Release %p, mask 0x%lx\n", ipcPtr, rel_mask);
    Cy_IPC_Drv_ReleaseNotify(ipcPtr, rel_mask);
    BTIPC_LOG_L1("Release register 0x%lx\n", ipcPtr->RELEASE);
    return CY_BT_IPC_DRV_SUCCESS;
}


cy_en_btipcdrv_status_t Cy_BTIPC_HCI_RelBuffer(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t* msgPtr)
{
    cy_stc_ipc_msg_alloc_t ipcMsgAlloc;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;
    uint8_t found;
    uint32_t interruptState;
    uint32_t *pMsg;

    if ((NULL == contextPtr) || (NULL == msgPtr))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    if (((cy_stc_ipc_msg_buff_t*)((void*)msgPtr))->pti != ((uint8_t)CY_BT_IPC_HCI_LONG))
    {
        /* Remove the FIFO entry */
        (void)Cy_BTIPC_HCI_FIFOGet(contextPtr, &pMsg, 1);
        return CY_BT_IPC_DRV_SUCCESS;
    }

    found = 0;

    interruptState = Cy_SysLib_EnterCriticalSection();

    /* If the channel is busy then do not proceed further, return CH BUSY error */
    if (Cy_IPC_Drv_IsLockAcquired (Cy_IPC_Drv_GetIpcBaseAddress(contextPtr->ulChannelHPC)))
    {
        Cy_SysLib_ExitCriticalSection(interruptState);
        return CY_BT_IPC_DRV_ERROR_CH_BUSY;
    }

    for (idx = 0U; idx < ((uint8_t)MAX_TO_FREE_BUF_COUNT); idx++)
    {
        if (contextPtr->toFreeBuf[idx].bufPtr == (uint8_t*)msgPtr[1])
        {
            ipcMsgAlloc.pti = (uint8_t)CY_BT_IPC_HPC_BUFRELEASE;
            ipcMsgAlloc.bufType = ((uint8_t)contextPtr->toFreeBuf[idx].bufType);
            ipcMsgAlloc.bufSize = contextPtr->toFreeBuf[idx].bufLen;
            ipcMsgAlloc.bufAddr = contextPtr->toFreeBuf[idx].bufPtr;
            found = 1;
            contextPtr->toFreeBuf[idx].bufType = CY_BT_IPC_HCI_INVALID_BUF;
            contextPtr->toFreeBuf[idx].bufLen = 0;
            contextPtr->toFreeBuf[idx].bufPtr = NULL;
            break;
        }
    }

    Cy_SysLib_ExitCriticalSection(interruptState);

    /* Remove the FIFO entry */
    (void)Cy_BTIPC_HCI_FIFOGet(contextPtr, &pMsg, 1);

    if (found != 0UL)
    {
#ifdef CY_BTIPC_STATS
        contextPtr->ipc_hci_peer_outbuf_count++;
#endif
        return (Cy_BTIPC_HPC_Write(contextPtr, &ipcMsgAlloc, (size_t) 2));
    }
    else
    {
        return CY_BT_IPC_DRV_ERROR_BUF_GET;
    }
}


cy_en_btipcdrv_status_t Cy_BTIPC_HPC_RelBuffer(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t* msgPtr)
{
    cy_stc_ipc_msg_alloc_t ipcMsgAlloc;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;

    if ((NULL == contextPtr) || (NULL == msgPtr))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    BTIPC_LOG_L1("Releasing HPC buffer 0x%lx\n", msgPtr[1]);
#ifdef CY_BTIPC_STATS
    contextPtr->ipc_hpc_peer_outbuf_count++;
#endif
    ipcMsgAlloc.pti = (uint8_t)CY_BT_IPC_HPC_BUFRELEASE;
    ipcMsgAlloc.bufType = 0;
    ipcMsgAlloc.bufSize = 0;
    ipcMsgAlloc.bufAddr = (uint8_t*)msgPtr[1];

    return (Cy_BTIPC_HPC_Write(contextPtr, &ipcMsgAlloc, (size_t) 2));
}


void Cy_BTIPC_HPC_Notify(void *btIpcContext, uint32_t * msgPtr)
{
    cy_en_btipc_hpcpti_t pti;
    cy_stc_ipc_bt_context_t *contextPtr = (cy_stc_ipc_bt_context_t*) btIpcContext;
    if ((NULL == contextPtr) || (NULL == msgPtr))
    {
        return;
    }

    BTIPC_LOG_L1("Internal cb for HPC\n");

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_btipc_hpcpti_t enum.');
    pti = (cy_en_btipc_hpcpti_t)((0xFFUL) & msgPtr[0]);

    switch (pti)
    {
        case CY_BT_IPC_HPC_LONG:
            (void)Cy_bt_handle_hpclong_msg(contextPtr, msgPtr);
            break;
        case CY_BT_IPC_HPC_BUFPROVIDE:
            (void)Cy_bt_handle_buf_add(contextPtr, msgPtr);
            break;
        default:
            /* default invalid pti */
            break;
    }
}


cy_en_btipcdrv_status_t Cy_BTIPC_Init(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_config_t *btIpcConfig)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_en_btipcdrv_status_t status;
    uint8_t idx;

    if ((NULL == contextPtr) || (NULL == btIpcConfig))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    contextPtr->dlChannelHCI = btIpcConfig->dlChannelHCI;
    contextPtr->ulChannelHCI = btIpcConfig->ulChannelHCI;

    contextPtr->dlChannelHPC = btIpcConfig->dlChannelHPC;
    contextPtr->ulChannelHPC = btIpcConfig->ulChannelHPC;

    contextPtr->intStuctureSelf = btIpcConfig->intStuctureSelf;
    contextPtr->intStucturePeer = btIpcConfig->intStucturePeer;
    contextPtr->intPeerMask = (uint32_t) (0x1UL << btIpcConfig->intStucturePeer);

    contextPtr->dlNotifyCallbackPtr = NULL;
    contextPtr->ulReleaseCallbackPtr = btIpcConfig->ulReleaseCallbackPtr;
    contextPtr->bufCallbackPtr = btIpcConfig->bufCallbackPtr;

    contextPtr->irqHandlerPtr = btIpcConfig->irqHandlerPtr;
    contextPtr->ipcIntConfig.intrSrc = btIpcConfig->ipcIntConfig.intrSrc;
    contextPtr->ipcIntConfig.intrPriority = btIpcConfig->ipcIntConfig.intrPriority;

    contextPtr->internal_hpc_notify_cb = btIpcConfig->internal_hpc_notify_cb;

    contextPtr->dlNotifyMask = (uint32_t)((uint32_t)(0x1UL << btIpcConfig->dlChannelHCI) | (uint32_t)(0x1UL << btIpcConfig->dlChannelHPC));
    contextPtr->ulReleaseMask = (uint32_t)((uint32_t)(0x1UL << btIpcConfig->ulChannelHCI) | (uint32_t)(0x1UL << btIpcConfig->ulChannelHPC));

    contextPtr->droppedHCI = 0;

    contextPtr->bootType = 0xFF;

    for (idx = 0U; idx <((uint8_t)MAX_BT_IPC_HPC_CB); idx++)
    {
        contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr = NULL;
        contextPtr->hpcNotifyCallbackParam[idx].msgType = CY_BT_IPC_HPC_RESERVED;
    }

    for (idx = 0U; idx < ((uint8_t)MAX_BUF_COUNT); idx++)
    {
        contextPtr->buffPool[idx].bufPtr = NULL;
        contextPtr->buffPool[idx].bufType = CY_BT_IPC_HCI_INVALID_BUF;
    }

    for (idx = 0U; idx < ((uint8_t)MAX_IPC_FIFO_SIZE); idx++)
    {
        contextPtr->IpcFifo.fifo[idx].msg[0] = 0;
        contextPtr->IpcFifo.fifo[idx].msg[1] = 0;
    }
    contextPtr->IpcFifo.rdIdx = 0;
    contextPtr->IpcFifo.wrIdx = 0;
    contextPtr->IpcFifo.bufLen = 0;

    for (idx = 0U; idx < ((uint8_t)MAX_TO_FREE_BUF_COUNT); idx++)
    {
        contextPtr->toFreeBuf[idx].bufPtr = NULL;
        contextPtr->toFreeBuf[idx].bufType = CY_BT_IPC_HCI_INVALID_BUF;
        contextPtr->toFreeBuf[idx].bufLen = 0;
    }

    status = Cy_BTIPC_WarmInit(contextPtr, btIpcConfig);

#ifdef CY_BTIPC_STATS
    contextPtr->ipc_int_count = 0;

    contextPtr->ipc_hci_cmd_count = 0;
    contextPtr->ipc_hpc_cmd_count = 0;

    contextPtr->ipc_hci_release_count = 0;
    contextPtr->ipc_hpc_release_count = 0;

    contextPtr->ipc_hci_notify_count = 0;
    contextPtr->ipc_hpc_notify_count = 0;

    contextPtr->ipc_hci_peer_release_count = 0;
    contextPtr->ipc_hpc_peer_release_count = 0;

    contextPtr->ipc_hci_peer_inbuf_count = 0;
    contextPtr->ipc_hci_peer_outbuf_count = 0;

    contextPtr->ipc_hpc_peer_inbuf_count = 0;
    contextPtr->ipc_hpc_peer_outbuf_count = 0;

    contextPtr->ipc_hci_cmd_self_outbuf_count = 0;
    contextPtr->ipc_hci_cmd_self_inbuf_count = 0;
    contextPtr->ipc_hci_cmd_self_outbuf_success = 0;

    contextPtr->ipc_hci_fifo_full = 0;
    contextPtr->ipc_hci_notify_in_fifo_full = 0;
#endif
    return status;
 }


cy_en_btipcdrv_status_t Cy_BTIPC_WarmInit(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_config_t *btIpcConfig)
{
    cy_en_sysint_status_t intrStatus;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;

    if ((NULL == contextPtr) || (NULL == btIpcConfig))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    intrStatus = Cy_SysInt_Init(&contextPtr->ipcIntConfig, contextPtr->irqHandlerPtr);
    if (((uint32_t)intrStatus) != 0UL)
    {
        return CY_BT_IPC_DRV_ERROR;
    }

    /* enable interrupt */
    NVIC_EnableIRQ(contextPtr->ipcIntConfig.intrSrc);

    /* Set IPC Interrupt mask */
    /* Allow only notify on DL channel  and release on UL channel interrupts */
    Cy_IPC_Drv_SetInterruptMask(Cy_IPC_Drv_GetIntrBaseAddr(contextPtr->intStuctureSelf), contextPtr->ulReleaseMask, contextPtr->dlNotifyMask);
    return CY_BT_IPC_DRV_SUCCESS;
 }


cy_en_btipcdrv_status_t Cy_BTIPC_Deinit(cy_stc_ipc_bt_context_t *btIpcContext)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;

    if (NULL == contextPtr)
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    /* enable interrupt */
    NVIC_DisableIRQ(contextPtr->ipcIntConfig.intrSrc);

    contextPtr->irqHandlerPtr = NULL;
    contextPtr->internal_hpc_notify_cb = NULL;

    for (idx = 0; idx < ((uint8_t)MAX_BT_IPC_HPC_CB); idx++)
    {
        contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr = NULL;
        contextPtr->hpcNotifyCallbackParam[idx].msgType = CY_BT_IPC_HPC_RESERVED;
    }

    for (idx = 0U; idx < ((uint8_t)MAX_BUF_COUNT); idx++)
    {
        contextPtr->buffPool[idx].bufPtr = NULL;
        contextPtr->buffPool[idx].bufType = CY_BT_IPC_HCI_INVALID_BUF;
    }

    return CY_BT_IPC_DRV_SUCCESS;
}


CY_IPC_SECTION_BEGIN
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_getPTI (cy_en_btipc_hcipti_t *pti, uint32_t *p_length, uint32_t *msgPtr)
{
    cy_stc_ipc_msg_buff_t *ipcMsgBuf;
    uint8_t *bufAddr;
    cy_en_btipc_hcipti_t mesgPti;

    if ((NULL == pti) || (NULL == msgPtr) || (NULL == p_length))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    /* Incase of long messages the PTI needs to be read from DATA0[bit 8-15] */
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_btipc_hcipti_t enum');
    mesgPti = (cy_en_btipc_hcipti_t)((0xFFUL) & msgPtr[0]);
    if (mesgPti == CY_BT_IPC_HCI_LONG)
    {
        ipcMsgBuf = (cy_stc_ipc_msg_buff_t*)((void*)msgPtr);
        *pti = (cy_en_btipc_hcipti_t)ipcMsgBuf->actualPti;
        bufAddr = ipcMsgBuf->bufAddr;
        /* Mapping of BT address space to MCU address space */
#if defined(BT_IPC_SIM) || !defined (BTSS)
        bufAddr = (uint8_t*)bufAddr;
#else
        bufAddr = (uint8_t*)((uint32_t)(bufAddr) + ((uint32_t)BTSS_DATA_RAM_IPC - 0x28000000UL));
#endif

        if (Cy_bt_isOffsetNeeded(*pti))
        {
            bufAddr++;
        }
    }
    else
    {
        *pti = mesgPti;
        bufAddr = (uint8_t*)msgPtr;
        /* Skip the PTI byte read from the DATA0 register */
        bufAddr++;
    }
    *p_length = Cy_bt_getPLLegnth(*pti, bufAddr);
    return CY_BT_IPC_DRV_SUCCESS;
}
CY_IPC_SECTION_END

CY_IPC_SECTION_BEGIN
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_GetReadBufPtr (cy_stc_ipc_bt_context_t *btIpcContext, void **ppData, size_t* pLength)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_stc_ipc_msg_buff_t *ipcMsgBuf;
    cy_stc_ipc_msg_short_t *shortMesg;
    cy_en_btipc_hcipti_t actualPti;
    cy_en_btipc_hcipti_t mesgPti;
    cy_en_btipcdrv_status_t status;
    uint32_t *pMsg;
    uint8_t *srcPtr;
    uint8_t idx;
    uint8_t done;
    uint32_t interruptState;

    if ((NULL == contextPtr) || (NULL == ppData))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    status = Cy_BTIPC_HCI_FIFOGet(contextPtr, &pMsg, 0);

    if (((uint32_t)status) != 0UL)
    {
        return status;
    }

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_btipc_hcipti_t enum.');
    mesgPti = (cy_en_btipc_hcipti_t)((0xFFUL) & pMsg[0]);

    if (mesgPti == CY_BT_IPC_HCI_LONG)
    {
        ipcMsgBuf = (cy_stc_ipc_msg_buff_t*)((void*)pMsg);
        actualPti = (cy_en_btipc_hcipti_t)ipcMsgBuf->actualPti;
        srcPtr = ipcMsgBuf->bufAddr;
        /* Mapping of BT address space to MCU address space */
#if defined(BT_IPC_SIM) || !defined (BTSS)
        srcPtr = (uint8_t*)(srcPtr);
#else
        srcPtr = (uint8_t*)((uint32_t)(srcPtr) + ((uint32_t)BTSS_DATA_RAM_IPC - 0x28000000UL));
#endif
#ifdef CY_BTIPC_STATS
        contextPtr->ipc_hci_peer_inbuf_count++;
#endif
        if (Cy_bt_isOffsetNeeded(actualPti))
        {
            srcPtr++;
        }
        *pLength = Cy_bt_getPLLegnth(actualPti, srcPtr);

        interruptState = Cy_SysLib_EnterCriticalSection();

        done = 0;
        for (idx = 0U; idx < ((uint8_t)MAX_TO_FREE_BUF_COUNT); idx++)
        {
            if (contextPtr->toFreeBuf[idx].bufPtr == NULL)
            {
                contextPtr->toFreeBuf[idx].bufType = Cy_bt_get_buf_type(actualPti);
                contextPtr->toFreeBuf[idx].bufLen = (uint16_t)(*pLength);
                contextPtr->toFreeBuf[idx].bufPtr = ipcMsgBuf->bufAddr;
                done = 1;
                break;
            }
        }

        Cy_SysLib_ExitCriticalSection(interruptState);

        if (done == 0U)
        {
            return CY_BT_IPC_DRV_ERROR_BUF_FULL;
        }

    }
    else
    {
        shortMesg = (cy_stc_ipc_msg_short_t*)((void*)pMsg);
        srcPtr = &(shortMesg->db0);
        *pLength = Cy_bt_getPLLegnth(mesgPti, srcPtr);
    }

    *ppData = srcPtr;
    return CY_BT_IPC_DRV_SUCCESS;
}
CY_IPC_SECTION_END

CY_IPC_SECTION_BEGIN
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_GetWriteBufPtr(cy_stc_ipc_bt_context_t *btIpcContext, cy_en_btipc_hcipti_t pti, void **ppData, size_t length)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_en_btipcdrv_status_t status;
    uint8_t *destBuf;
    cy_en_btipc_buftype_t bufType;
    uint8_t *bPtr;
    uint32_t interruptState;

    if ((NULL == contextPtr) || (NULL == ppData))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();
    /* If the HCI channel is busy then do not proceed further, return CH BUSY error */
    if (Cy_IPC_Drv_IsLockAcquired (Cy_IPC_Drv_GetIpcBaseAddress(contextPtr->ulChannelHCI)))
    {
        Cy_SysLib_ExitCriticalSection(interruptState);
        return CY_BT_IPC_DRV_ERROR_CH_BUSY;
    }
    Cy_SysLib_ExitCriticalSection(interruptState);

    *ppData = NULL;

    /* Get the buffer type based on the payload type indicator */
    bufType = Cy_bt_get_buf_type(pti);
    /* Pick a free buffer from the pool of buffers */
    status = Cy_bt_GetBuffer (contextPtr, (void **)&destBuf, bufType, length);
    if (((uint32_t)status) != 0UL)
    {
        return status;
    }

    bPtr = destBuf;
    /* Skip pad byte if needed */
    if (Cy_bt_isOffsetNeeded(pti))
    {
        bPtr++;
    }
    *ppData = bPtr;
    return CY_BT_IPC_DRV_SUCCESS;
}
CY_IPC_SECTION_END

CY_IPC_SECTION_BEGIN
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_Write(cy_stc_ipc_bt_context_t *btIpcContext, cy_en_btipc_hcipti_t pti, void *data, size_t length)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_stc_ipc_msg_buff_t ipcPacket;
    cy_stc_ipc_msg_short_t ipcShort;
    uint32_t *msgPtr;
    uint8_t *bPtr, *bDptr;
    uint8_t i;

    if ((NULL == contextPtr) || (NULL == data))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    /* Check if it is long message or ACL or ISO packet.
     * As per BT FW team's request, this deviation is taken to use buffers for
     * ACL and ISO short packets. Ref JIRA DRIVERS-6513 for more details */
    if ((length > ((uint8_t)MAX_SHORT_MESG_LENGTH)) || (pti == CY_BT_IPC_HCI_ACL)
        || (pti == CY_BT_IPC_HCI_ISO))
    {
        /* Add pad byte if needed */
        bPtr = (uint8_t*)data;
        if (Cy_bt_isOffsetNeeded(pti))
        {
            bPtr--;
        }

        ipcPacket.pti = (uint8_t) CY_BT_IPC_HCI_LONG;
        ipcPacket.actualPti = (uint8_t)pti;
        ipcPacket.bufSize = 0;
        // Remap the address to BT memory map
#if defined(BT_IPC_SIM) || !defined (BTSS)
        ipcPacket.bufAddr = bPtr;
#else
        ipcPacket.bufAddr = (uint8_t*)((uint32_t)bPtr - ((uint32_t)BTSS_DATA_RAM_IPC - 0x28000000UL));
#endif
        /* end of buffer preparation */
        msgPtr = (uint32_t*)((void*)&ipcPacket);
    }
    else /* Short Message */
    {
        msgPtr = (uint32_t*)((void*)&ipcShort);
        msgPtr[0] = 0;
        msgPtr[1] = 0;
        ipcShort.pti = (uint8_t)pti;
        bPtr = &(ipcShort.db0);
        bDptr = (uint8_t*)data;

        for (i = 0; i < length; i++)
        {
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 18.1','Checked manually, these pointer will not exceed register range.');
            *bPtr++ = *bDptr++;
        }
    }

    if (Cy_IPC_Drv_SendMsgDWord(Cy_IPC_Drv_GetIpcBaseAddress(contextPtr->ulChannelHCI),
                                contextPtr->intPeerMask, msgPtr) == CY_IPC_DRV_SUCCESS)
    {
#ifdef CY_BTIPC_STATS
        contextPtr->ipc_hci_cmd_count++;
#endif
        return CY_BT_IPC_DRV_SUCCESS;
    }
    else
    {
        (void)ipcShort.pti; /* Suppress a compiler warning about unused variables */
        return CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE;
    }
}
CY_IPC_SECTION_END

cy_en_btipcdrv_status_t Cy_BTIPC_HPC_GetWriteBufPtr(cy_stc_ipc_bt_context_t *btIpcContext, void **ppData, size_t length)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_en_btipcdrv_status_t status;
    uint8_t *destBuf;
    (void)length;
    uint32_t interruptState;

    if ((NULL == contextPtr) || (NULL == ppData))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();
    /* If the HPC channel is busy then do not proceed further, return CH BUSY error */
    if (Cy_IPC_Drv_IsLockAcquired (Cy_IPC_Drv_GetIpcBaseAddress(contextPtr->ulChannelHPC)))
    {
        Cy_SysLib_ExitCriticalSection(interruptState);
        return CY_BT_IPC_DRV_ERROR_CH_BUSY;
    }
    Cy_SysLib_ExitCriticalSection(interruptState);

    *ppData = NULL;
    /* Pick a free control buffer from the pool of buffers */
    status = Cy_bt_GetBuffer (contextPtr, (void **)&destBuf, CY_BT_IPC_CTRL_BUF, length);
    if (((uint32_t)status) == 0UL)
    {
        *ppData = destBuf;
    }
    (void) length; /* Suppress a compiler warning about unused variables */
    return status;
}


cy_en_btipcdrv_status_t Cy_BTIPC_HPC_Write(cy_stc_ipc_bt_context_t *btIpcContext, void *data, size_t length)
{
    uint32_t *dataPtr = (uint32_t*) data;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;

    (void) length;

    if ((NULL == contextPtr) || (NULL == data))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    if (!((bool)(Cy_IPC_Drv_SendMsgDWord(Cy_IPC_Drv_GetIpcBaseAddress(contextPtr->ulChannelHPC),
                                contextPtr->intPeerMask, (uint32_t*) dataPtr))))
    {
#ifdef CY_BTIPC_STATS
        contextPtr->ipc_hpc_cmd_count++;
#endif
        return CY_BT_IPC_DRV_SUCCESS;
    }
    else
    {
        return CY_BT_IPC_DRV_ERROR_LOCK_ACQUIRE;
    }
}


cy_en_btipcdrv_status_t Cy_BTIPC_HCI_RegisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_ipc_bt_callback_ptr_t hciNotifyCallbackPtr)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;

    if ((NULL == contextPtr) || (NULL == hciNotifyCallbackPtr))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    contextPtr->dlNotifyCallbackPtr = hciNotifyCallbackPtr;
    return CY_BT_IPC_DRV_SUCCESS;
}


cy_en_btipcdrv_status_t Cy_BTIPC_HCI_UnregisterCb(cy_stc_ipc_bt_context_t *btIpcContext)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;

    if (NULL == contextPtr)
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    contextPtr->dlNotifyCallbackPtr = NULL;

    return CY_BT_IPC_DRV_SUCCESS;
}


cy_en_btipcdrv_status_t Cy_BTIPC_HPC_RegisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_hcp_cb_t *pHpcNotifyCallbackParam)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;
    uint8_t placed;

    if ((NULL == contextPtr) || (NULL == pHpcNotifyCallbackParam))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    placed = 0U;
    for (idx = 0U; idx < ((uint8_t)MAX_BT_IPC_HPC_CB); idx++)
    {
        if ((contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr == NULL) &&
            (contextPtr->hpcNotifyCallbackParam[idx].msgType == CY_BT_IPC_HPC_RESERVED))
        {
            contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr = pHpcNotifyCallbackParam->hpcNotifyCallbackPtr;
            contextPtr->hpcNotifyCallbackParam[idx].msgType = pHpcNotifyCallbackParam->msgType;
            placed = 1;
            break;
        }
    }

    if (placed != 0U)
    {
        return CY_BT_IPC_DRV_SUCCESS;
    }
    else
    {
        return CY_BT_IPC_DRV_ERROR;
    }
}


cy_en_btipcdrv_status_t Cy_BTIPC_HPC_UnregisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_hcp_cb_t *pHpcNotifyCallbackParam)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;
    uint8_t found;

    if ((NULL == contextPtr) || (NULL == pHpcNotifyCallbackParam))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    found = 0;
    for (idx = 0U; idx < ((uint8_t)MAX_BT_IPC_HPC_CB); idx++)
    {
        if ((contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr == pHpcNotifyCallbackParam->hpcNotifyCallbackPtr) &&
            (contextPtr->hpcNotifyCallbackParam[idx].msgType == pHpcNotifyCallbackParam->msgType))
        {
            contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr = NULL;
            contextPtr->hpcNotifyCallbackParam[idx].msgType = CY_BT_IPC_HPC_RESERVED;
            found = 1;
            break;
        }
    }

    if (found != 0UL)
    {
        return CY_BT_IPC_DRV_SUCCESS;
    }
    else
    {
        return CY_BT_IPC_DRV_ERROR;
    }
}


cy_en_btipcdrv_status_t Cy_BTIPC_Buffer_RegisterCb(cy_stc_ipc_bt_context_t *btIpcContext, cy_ipc_bt_bufcallback_ptr_t bufCallbackPtr)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t interruptState;

    if ((NULL == contextPtr) || (NULL == bufCallbackPtr))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();
    contextPtr->bufCallbackPtr = bufCallbackPtr;
    Cy_SysLib_ExitCriticalSection(interruptState);

    return CY_BT_IPC_DRV_SUCCESS;
}


CY_IPC_SECTION_BEGIN
static cy_en_btipcdrv_status_t Cy_bt_GetBuffer (cy_stc_ipc_bt_context_t *btIpcContext, void **ppBuf, cy_en_btipc_buftype_t bufType, size_t length)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;
    uint8_t found;
    uint8_t size_error;
    uint32_t interruptState;

    if ((NULL == contextPtr) || (NULL == ppBuf))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();

    found = 0;
    size_error = 0;

    BTIPC_LOG_L2("Buf req: Type 0x%x, Size %d\n",bufType,length);
    BTIPC_LOG_L2("Buf Pool content\n");

#ifdef CY_BTIPC_STATS
    if (bufType == CY_BT_IPC_HCI_CMD_BUF)
    {
        contextPtr->ipc_hci_cmd_self_outbuf_count++;
    }
#endif
    for (idx = 0U; idx < ((uint8_t)MAX_BUF_COUNT); idx++)
    {
        BTIPC_LOG_L2("idx %d, bufType 0x%x, bufLen %d, bufPtr %p\n",idx, contextPtr->buffPool[idx].bufType,contextPtr->buffPool[idx].bufLen, contextPtr->buffPool[idx].bufPtr);

        if ((contextPtr->buffPool[idx].bufType == bufType) && (contextPtr->buffPool[idx].bufPtr != NULL))
        {
            if (length <= contextPtr->buffPool[idx].bufLen)
            {
                *ppBuf = (void*)contextPtr->buffPool[idx].bufPtr;
                // Mapping of address
#if defined(BT_IPC_SIM) || !defined (BTSS)
                *ppBuf = (void*)(*ppBuf);
#else
                *ppBuf = (void*)((uint32_t)(*ppBuf) + ((uint32_t)BTSS_DATA_RAM_IPC - 0x28000000UL));
#endif
                contextPtr->buffPool[idx].bufPtr = NULL;
                contextPtr->buffPool[idx].bufType = CY_BT_IPC_HCI_INVALID_BUF;
                found = 1;
#ifdef CY_BTIPC_STATS
                if (bufType == CY_BT_IPC_HCI_CMD_BUF)
                {
                   contextPtr->ipc_hci_cmd_self_outbuf_success++;
                }
#endif
                break;
            }
            else
            {
                size_error = 1;
            }
        }
    }

    Cy_SysLib_ExitCriticalSection(interruptState);

    if (found != 0UL)
    {
        return CY_BT_IPC_DRV_SUCCESS;
    }
    else if (size_error == 1UL)
    {
        return CY_BT_IPC_DRV_ERROR_BUF_SIZE;
    }
    else
    {
        *ppBuf = NULL;
        return CY_BT_IPC_DRV_ERROR_BUF_GET;
    }

}
CY_IPC_SECTION_END

static cy_en_btipcdrv_status_t Cy_bt_PutBuffer(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_buf_t *bufDecriptor)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;
    uint32_t interruptState;
    cy_en_btipcdrv_status_t status = CY_BT_IPC_DRV_ERROR_BUF_FULL;

    BTIPC_LOG_L2("Put buffer+\n");

    if ((NULL == contextPtr) || (NULL == bufDecriptor) || (bufDecriptor->bufPtr == NULL))
    {
        BTIPC_LOG_L2("Put buffer-\n");
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();

    for (idx = 0U; idx < ((uint8_t)MAX_BUF_COUNT); idx++)
    {
        if ((contextPtr->buffPool[idx].bufType == bufDecriptor->bufType) &&
            (contextPtr->buffPool[idx].bufPtr == bufDecriptor->bufPtr))
        {
            BTIPC_LOG_L2("Buffer already present in the pool at %d\n",idx);
            status = CY_BT_IPC_DRV_ERROR_BUF_PRESENT;
            break;
        }
        else if (contextPtr->buffPool[idx].bufType == CY_BT_IPC_HCI_INVALID_BUF)
        {
            contextPtr->buffPool[idx] = *bufDecriptor;
            status = CY_BT_IPC_DRV_SUCCESS;
            BTIPC_LOG_L2("Added buffer at index %d\n",idx);
            break;
        }
        else
        {
            /* This is just to keep coverity happy */
        }
    }

    Cy_SysLib_ExitCriticalSection(interruptState);

    /* Call handler for buffer */
    if ((status == CY_BT_IPC_DRV_SUCCESS) && (NULL != contextPtr->bufCallbackPtr))
    {
        contextPtr->bufCallbackPtr(bufDecriptor->bufType);
    }

    BTIPC_LOG_L2("Put buffer-\n");
    return status;
}


/* Local function implementation */
cy_en_btipcdrv_status_t Cy_bt_handle_hpclong_msg(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t * msgPtr)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_stc_ipc_msg_init_t *ptr;
    cy_stc_ipc_bt_buf_t bufDescriptor;
    cy_en_btipcdrv_status_t status;
    uint8_t i;
    uint8_t bufCount;
    uint8_t *bPtr;
    uint8_t *bDptr;
    cy_en_btipc_hpcmsgid_t longMsgType;
    uint8_t idx;

    if ((NULL == contextPtr) || (NULL == msgPtr))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    bPtr = (uint8_t*)msgPtr;
    longMsgType = (cy_en_btipc_hpcmsgid_t)(*(bPtr+1));

    BTIPC_LOG_L1("longMsgType %d\n", longMsgType);

    status = CY_BT_IPC_DRV_SUCCESS;
#ifdef CY_BTIPC_STATS
    contextPtr->ipc_hpc_peer_inbuf_count++;
#endif
    switch (longMsgType)
    {
        case CY_BT_IPC_HPC_INIT:
            ptr = (cy_stc_ipc_msg_init_t*)(* (msgPtr+1));
            if (NULL == ptr)
            {
                status = CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
                break;
            }
            /* mapping of memory */
#if defined(BT_IPC_SIM) || !defined (BTSS)
            ptr = (cy_stc_ipc_msg_init_t*)(ptr);
#else
            ptr = (cy_stc_ipc_msg_init_t*)((uint32)ptr + ((uint32_t)BTSS_DATA_RAM_IPC - 0x28000000UL));
#endif
            /* The payloadLen includes bootype (1 byte) and error code (4 bytes).
            Hence, subtract INIT_IPC_BUFF_DESC_OFFSET (5 Bytes) from it */
            bufCount = (ptr->payLoadLen - (uint8_t)INIT_IPC_BUFF_DESC_OFFSET)/((uint8_t)BUFFER_DESCRIPTION_LEN);

            /* Add code to extract boot type from init structure */
            contextPtr->bootType = ptr->bootType;
#ifndef BT_OLD_INIT
            bPtr = (uint8_t*)(&ptr->bootType);
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 18.1','Checked manually, the byte pointer will not corrupt memory.');
            bPtr++;
            bDptr = (uint8_t*)(&contextPtr->certError);
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 18.1','Checked manually, the byte pointer will not corrupt memory.');
            *bDptr++ = *bPtr++;
            *bDptr++ = *bPtr++;
            *bDptr++ = *bPtr++;
            *bDptr++ = *bPtr++;
#endif

#ifdef BT_OLD_INIT
            BTIPC_LOG_L0("handling Init mesg from %p, boottype %d, payload len 0x%x, bufCount %d\n",
                ptr, ptr->bootType, ptr->payLoadLen, bufCount);
#else
            BTIPC_LOG_L0("handling Init mesg from %p, boottype %d, payload len 0x%x, certError 0x%lx bufCount %d\n",
                ptr, ptr->bootType, ptr->payLoadLen, contextPtr->certError , bufCount);
#endif


            if ((ptr->bootType == (uint8_t)CY_BT_IPC_BOOT_CONFIG_WAIT) ||
                (ptr->bootType == (uint8_t)CY_BT_IPC_BOOT_FULLY_UP))
            {

                /* Clear all buffers in the pool */
                for (idx = 0U; idx < ((uint8_t)MAX_BUF_COUNT); idx++)
                {
                    contextPtr->buffPool[idx].bufPtr = NULL;
                    contextPtr->buffPool[idx].bufType = CY_BT_IPC_HCI_INVALID_BUF;
                }

                //msgId
                //bootType
                /* point to the start of buffer pool */
                bPtr = (uint8_t*)ptr + sizeof(cy_stc_ipc_msg_init_t);

                BTIPC_LOG_L0("\nExtract buffers from %p\n",bPtr);

                for (i = 0; i < bufCount; i++)
                {
                    bufDescriptor.bufType = (cy_en_btipc_buftype_t) (*bPtr++);

                    bDptr = (uint8_t*)(&bufDescriptor.bufLen);
                    *bDptr++ = *bPtr++;
                    *bDptr++ = *bPtr++;

                    bDptr = (uint8_t*)(&bufDescriptor.bufPtr);
                    *bDptr++ = *bPtr++;
                    *bDptr++ = *bPtr++;
                    *bDptr++ = *bPtr++;
                    *bDptr++ = *bPtr++;

                    BTIPC_LOG_L0("bufType %x, bufLen %d, bufPtr %p\n",bufDescriptor.bufType, bufDescriptor.bufLen, bufDescriptor.bufPtr);

                    status = Cy_bt_PutBuffer(contextPtr, &bufDescriptor);
                    if (((uint32_t)status) != 0UL)
                    {
                        /* Need to check if some cleaning needed for error condition */
                        BTIPC_LOG_L0("Error in putting the buffer to pool\n");
                    }
                    else
                    {
                        BTIPC_LOG_L0("Added buf %d\n",i);
                    }
                }
                BTIPC_LOG_L0("Bufs add done\n\n");
            }
            else
            {
                BTIPC_LOG_L0("\nInvalid Boot type\n");
            }
            break;

        case CY_BT_IPC_HPC_HADM:
            BTIPC_LOG_L1("HADM Data\n");
            /* Add code to handle HADM data */
            break;

        default:
            /* Invalid long message type */
            status = CY_BT_IPC_DRV_ERROR_PARAM;
            break;
    }
    return status;
}


cy_en_btipcdrv_status_t Cy_bt_handle_buf_add(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t * msgPtr)
{
    cy_stc_ipc_bt_buf_t bufDescriptor;
    cy_stc_ipc_msg_alloc_t allocBuf;
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    cy_en_btipcdrv_status_t status;

    BTIPC_LOG_L2("Adding buf\n");

    if ((NULL == contextPtr) || (NULL == msgPtr))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    allocBuf = *(cy_stc_ipc_msg_alloc_t*)((void*)msgPtr);
    bufDescriptor.bufType = (cy_en_btipc_buftype_t) allocBuf.bufType;
    bufDescriptor.bufLen = allocBuf.bufSize;
    bufDescriptor.bufPtr = (uint8_t*) allocBuf.bufAddr;

    BTIPC_LOG_L2("bufType 0x%x, bufLen 0x%x, bufPtr %p\n",bufDescriptor.bufType, bufDescriptor.bufLen, bufDescriptor.bufPtr);
#ifdef CY_BTIPC_STATS
    if (bufDescriptor.bufType == CY_BT_IPC_HCI_CMD_BUF)
    {
        contextPtr->ipc_hci_cmd_self_inbuf_count++;
    }
#endif
    status = Cy_bt_PutBuffer(contextPtr, &bufDescriptor);
    if (((uint32_t)status) != 0UL)
    {
        /* Need to check if some cleaning needed for error condition */
        BTIPC_LOG_L0("Error: 0x%x in putting the buffer to pool\n",status);
    }
    return status;
}


CY_IPC_SECTION_BEGIN
static cy_en_btipc_buftype_t Cy_bt_get_buf_type(cy_en_btipc_hcipti_t pti)
{
    cy_en_btipc_buftype_t bufType;

    /* To be done: Currently returning Control buffer for all PTIs. Need to change it once we have clarity on it */
    switch (pti)
    {
        case CY_BT_IPC_HCI_CMD:
            bufType = CY_BT_IPC_HCI_CMD_BUF;
            break;
        case CY_BT_IPC_HCI_ACL:
        /* CY_BT_IPC_HCI_BREDR_BUF if classic BT, or CY_BT_IPC_HCI_BLE_BUF for BLE. 20829 only supports BLE*/
            bufType = CY_BT_IPC_HCI_BLE_BUF;
            break;
        case CY_BT_IPC_HCI_ISO:
            bufType = CY_BT_IPC_HCI_ISOC_BUF;
            break;
        case CY_BT_IPC_HCI_EVT:
        /* This will not be sent from MCU. But simulation code needs it */
            bufType = CY_BT_IPC_HCI_CMD_BUF;
            break;
        case CY_BT_IPC_HCI_DIAG:
            bufType = CY_BT_IPC_HCI_CMD_BUF;
        break;
        case CY_BT_IPC_HCI_SCO:
        /* SCO is not supported in CYW20829 */
        /* Do not have info. Needs to be revisited later */
        case CY_BT_IPC_HCI_MPAF:
        /* Not Supported */
        case CY_BT_IPC_HCI_SLIPH5:
        /* Not Supported */
        default:
            bufType = CY_BT_IPC_HCI_INVALID_BUF;
            break;
    }
    return bufType;
}
CY_IPC_SECTION_END

CY_IPC_SECTION_BEGIN
static uint32_t Cy_bt_getPLLegnth(cy_en_btipc_hcipti_t pti, uint8_t* bufAddr)
{
    uint32_t length;
    switch (pti)
    {
        case CY_BT_IPC_HCI_CMD:
            length = (uint32_t)(((BTHCI_CMD_HDR_t*)((void*)bufAddr))->params_len);
            length += sizeof(BTHCI_CMD_HDR_t);
            break;
        case CY_BT_IPC_HCI_ACL:
            length = (uint32_t)(((BTHCI_ACL_HDR_t*)((void*)bufAddr))->data_len);
            length += sizeof(BTHCI_ACL_HDR_t);
            break;
        case CY_BT_IPC_HCI_SCO:
            length = (uint32_t)(((BTHCI_SCO_HDR_t*)((void*)bufAddr))->data_len);
            length += sizeof(BTHCI_SCO_HDR_t);
            break;
        case CY_BT_IPC_HCI_EVT:
            length = (uint32_t)(((BTHCI_EVENT_HDR_t*)((void*)bufAddr))->params_len);
            length += sizeof(BTHCI_EVENT_HDR_t);
            break;
        case CY_BT_IPC_HCI_ISO:
            length = (uint32_t)(((BTHCI_ISO_HDR_t*)((void*)bufAddr))->data_len);
            length += sizeof(BTHCI_ISO_HDR_t);
            break;
        case CY_BT_IPC_HCI_DIAG:
            length = *bufAddr; /* The first byte of the payload holds the payload length */
            break;
        /* To be done: Header length for the remaining PTI needs to be updated */
        case CY_BT_IPC_HCI_MPAF:
            length = 0;
            break;
        case CY_BT_IPC_HCI_SLIPH5:
            length = 0;
            break;
        default:
            length = 0;
            break;
    }
    return length;
}
CY_IPC_SECTION_END

CY_IPC_SECTION_BEGIN
static bool Cy_bt_isOffsetNeeded(cy_en_btipc_hcipti_t pti)
{
    bool ret;

    switch (pti)
    {
        case CY_BT_IPC_HCI_CMD:
        case CY_BT_IPC_HCI_SCO:
            ret = true;
            break;
        case CY_BT_IPC_HCI_ACL:
        case CY_BT_IPC_HCI_EVT:
        case CY_BT_IPC_HCI_ISO:
        case CY_BT_IPC_HCI_DIAG:
        case CY_BT_IPC_HCI_MPAF:
        case CY_BT_IPC_HCI_SLIPH5:
        default:
            ret = false;
            break;
    }

    return ret;
}
CY_IPC_SECTION_END

static cy_en_btipcdrv_status_t Cy_BTIPC_HCI_FIFOPut(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t *pMsg)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t interruptState;

    /* Check if buffer is full */
    if (contextPtr->IpcFifo.bufLen == ((uint8_t)MAX_IPC_FIFO_SIZE))
    {
        return CY_BT_IPC_DRV_ERROR_BUF_FULL;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();

    contextPtr->IpcFifo.fifo[contextPtr->IpcFifo.wrIdx].msg[0] = pMsg[0];
    contextPtr->IpcFifo.fifo[contextPtr->IpcFifo.wrIdx].msg[1] = pMsg[1];

    contextPtr->IpcFifo.bufLen++;
    contextPtr->IpcFifo.wrIdx++;

    /* If at last index in buffer, set writeIndex back to 0 */
    if (contextPtr->IpcFifo.wrIdx == ((uint8_t)MAX_IPC_FIFO_SIZE))
    {
        contextPtr->IpcFifo.wrIdx = 0;
    }

    Cy_SysLib_ExitCriticalSection(interruptState);
    return CY_BT_IPC_DRV_SUCCESS;
}

CY_IPC_SECTION_BEGIN
cy_en_btipcdrv_status_t Cy_BTIPC_HCI_FIFOGet(cy_stc_ipc_bt_context_t *btIpcContext, uint32_t **ppMsg, uint8_t delete)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t interruptState;

    /* Check if buffer is empty */
    if (contextPtr->IpcFifo.bufLen == 0U)
    {
        return CY_BT_IPC_DRV_ERROR_BUF_EMPTY;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();
    *ppMsg = contextPtr->IpcFifo.fifo[contextPtr->IpcFifo.rdIdx].msg;

    if (delete != 0U)
    {
        contextPtr->IpcFifo.bufLen--;
        contextPtr->IpcFifo.rdIdx++;

        /* If at last index in buffer, set readIndex back to 0 */
        if (contextPtr->IpcFifo.rdIdx == ((uint8_t)MAX_IPC_FIFO_SIZE))
        {
            contextPtr->IpcFifo.rdIdx = 0;
        }
    }
    Cy_SysLib_ExitCriticalSection(interruptState);

    if ((delete != 0UL) && (((uint8_t)MAX_IPC_FIFO_SIZE - 1U) == contextPtr->IpcFifo.bufLen))
    {
        /* Release the channel as FIFO gets a free location */
        (void)Cy_BTIPC_HCI_RelChannel(contextPtr); /* Suppress a compiler warning about unused return value */
#ifdef CY_BTIPC_STATS
        contextPtr->ipc_hci_peer_release_count++;
#endif
        BTIPC_LOG_L0("Releasing the channel\n");
    }
    return CY_BT_IPC_DRV_SUCCESS;
}
CY_IPC_SECTION_END

uint16_t Cy_BTIPC_HCI_FIFOCount(cy_stc_ipc_bt_context_t *btIpcContext)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t interruptState;
    uint16_t count;

    interruptState = Cy_SysLib_EnterCriticalSection();
    count = contextPtr->IpcFifo.bufLen;
    Cy_SysLib_ExitCriticalSection(interruptState);
    return count;
}

cy_en_btipcdrv_status_t Cy_BTIPC_RetrieveContext(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_save_ctxt_t *pContextRet)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t i;

    if ((NULL == contextPtr) || (NULL == pContextRet))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    for (i = 0U; i < ((uint8_t)MAX_BUF_COUNT); i++)
    {
        pContextRet->buffPool[i].bufType = (uint16_t) contextPtr->buffPool[i].bufType;
        pContextRet->buffPool[i].bufLen = contextPtr->buffPool[i].bufLen;
        pContextRet->buffPool[i].bufPtr = contextPtr->buffPool[i].bufPtr;
    }
    return CY_BT_IPC_DRV_SUCCESS;
}

cy_en_btipcdrv_status_t Cy_BTIPC_RestoreContext(cy_stc_ipc_bt_context_t *btIpcContext, cy_stc_ipc_bt_save_ctxt_t *pContextRet)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint32_t i;
    if ((NULL == contextPtr) || (NULL == pContextRet))
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    for (i = 0U; i < ((uint8_t)MAX_BUF_COUNT); i++)
    {
        contextPtr->buffPool[i].bufType = (cy_en_btipc_buftype_t) pContextRet->buffPool[i].bufType;
        contextPtr->buffPool[i].bufLen = pContextRet->buffPool[i].bufLen;
        contextPtr->buffPool[i].bufPtr = pContextRet->buffPool[i].bufPtr;
    }
    return CY_BT_IPC_DRV_SUCCESS;
}

#ifdef BTIPC_STATUS
cy_en_btipcdrv_status_t Cy_bt_PrintStatus (cy_stc_ipc_bt_context_t *btIpcContext)
{
    cy_stc_ipc_bt_context_t *contextPtr = btIpcContext;
    uint8_t idx;
    uint32_t interruptState;

    if (NULL == contextPtr)
    {
        return CY_BT_IPC_DRV_ERROR_BAD_HANDLE;
    }

    interruptState = Cy_SysLib_EnterCriticalSection();

    printf("\n\nBuf Pool content\n");
    for (idx = 0U; idx < ((uint8_t)MAX_BUF_COUNT); idx++)
    {
#if defined (__ARMCC_VERSION)
        printf("idx %d, bufType 0x%x, bufLen %d, bufPtr 0x%x\n",idx, contextPtr->buffPool[idx].bufType,contextPtr->buffPool[idx].bufLen, (uint32_t)(contextPtr->buffPool[idx].bufPtr));
#else
    printf("idx %d, bufType 0x%x, bufLen %d, bufPtr %p\n",idx, contextPtr->buffPool[idx].bufType,contextPtr->buffPool[idx].bufLen, contextPtr->buffPool[idx].bufPtr);
#endif
    }

    printf("\nFIFO content\n");
    for (idx = 0; idx < MAX_IPC_FIFO_SIZE; idx++)
    {
#if defined (__ARMCC_VERSION)
        printf("idx %d, msg[0] 0x%x, msg[1] 0x%x\n",idx, contextPtr->IpcFifo.fifo[idx].msg[0], contextPtr->IpcFifo.fifo[idx].msg[1]);
#else
        printf("idx %d, msg[0] 0x%lx, msg[1] 0x%lx\n",idx, contextPtr->IpcFifo.fifo[idx].msg[0], contextPtr->IpcFifo.fifo[idx].msg[1]);
#endif
    }
    printf("rdIdx %d, wrIdx %d, bufLen %d\n",contextPtr->IpcFifo.rdIdx, contextPtr->IpcFifo.wrIdx, contextPtr->IpcFifo.bufLen);

    printf("\nCallbacks registered\n");
    for (idx = 0; idx < MAX_BT_IPC_HPC_CB; idx++)
    {
#if defined (__ARMCC_VERSION)
        printf("idx %d, hpcNotifyCallbackPtr 0x%x, msgType %d\n", idx,
                (uint32_t)(contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr),
                contextPtr->hpcNotifyCallbackParam[idx].msgType);
#else
    printf("idx %d, hpcNotifyCallbackPtr %p, msgType %d\n", idx,
            contextPtr->hpcNotifyCallbackParam[idx].hpcNotifyCallbackPtr,
            contextPtr->hpcNotifyCallbackParam[idx].msgType);
#endif
    }

    Cy_SysLib_ExitCriticalSection(interruptState);
    return CY_BT_IPC_DRV_SUCCESS;
}
#endif
CY_MISRA_BLOCK_END('ARRAY_VS_SINGLETON');
#endif
