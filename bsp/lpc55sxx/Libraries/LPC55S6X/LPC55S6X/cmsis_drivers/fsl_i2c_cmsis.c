/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2020,2022 NXP. Not a Contribution.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fsl_i2c_cmsis.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_i2c_cmsis"
#endif

#if ((defined(RTE_I2C0) && RTE_I2C0) || (defined(RTE_I2C1) && RTE_I2C1) || (defined(RTE_I2C2) && RTE_I2C2) ||     \
     (defined(RTE_I2C3) && RTE_I2C3) || (defined(RTE_I2C4) && RTE_I2C4) || (defined(RTE_I2C5) && RTE_I2C5) ||     \
     (defined(RTE_I2C6) && RTE_I2C6) || (defined(RTE_I2C7) && RTE_I2C7) || (defined(RTE_I2C8) && RTE_I2C8) ||     \
     (defined(RTE_I2C9) && RTE_I2C9) || (defined(RTE_I2C10) && RTE_I2C10) || (defined(RTE_I2C11) && RTE_I2C11) || \
     (defined(RTE_I2C12) && RTE_I2C12) || (defined(RTE_I2C13) && RTE_I2C13))

#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR((2), (3))

/*
 * ARMCC does not support split the data section automatically, so the driver
 * needs to split the data to separate sections explicitly, to reduce codesize.
 */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define ARMCC_SECTION(section_name) __attribute__((section(section_name)))
#endif

typedef const struct _cmsis_i2c_resource
{
    I2C_Type *base;            /*!< I2C peripheral base address.      */
    uint32_t (*GetFreq)(void); /*!< Function to get the clock frequency. */

} cmsis_i2c_resource_t;

typedef union _cmsis_i2c_handle
{
    i2c_master_handle_t master_handle; /*!< master Interupt transfer handle. */
    i2c_slave_handle_t slave_handle;   /*!< slave Interupt transfer handle. */
} cmsis_i2c_handle_t;

typedef struct _cmsis_i2c_interrupt_driver_state
{
    cmsis_i2c_resource_t *resource; /*!< Basic I2C resource. */
    cmsis_i2c_handle_t *handle;
    ARM_I2C_SignalEvent_t cb_event; /*!< Callback function.     */
    uint8_t flags;                  /*!< Control and state flags. */
} cmsis_i2c_interrupt_driver_state_t;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
typedef const struct _cmsis_i2c_dma_resource
{
    DMA_Type *i2cDmaBase;   /*!< DMA peripheral base address for i2c.    */
    uint32_t i2cDmaChannel; /*!< DMA channel for i2c.             */
} cmsis_i2c_dma_resource_t;

typedef struct _cmsis_i2c_dma_driver_state
{
    cmsis_i2c_resource_t *resource;             /*!< i2c basic resource.      */
    cmsis_i2c_dma_resource_t *dmaResource;      /*!< i2c DMA resource.        */
    i2c_master_dma_handle_t *master_dma_handle; /*!< i2c DMA transfer handle. */
    dma_handle_t *dmaHandle;                    /*!< DMA i2c handle.          */
    uint8_t flags;                              /*!< Control and state flags. */
} cmsis_i2c_dma_driver_state_t;
#endif

static const ARM_DRIVER_VERSION s_i2cDriverVersion = {ARM_I2C_API_VERSION, ARM_I2C_DRV_VERSION};

static const ARM_I2C_CAPABILITIES s_i2cDriverCapabilities = {
    0, /*< supports 10-bit addressing*/
};

static ARM_DRIVER_VERSION I2Cx_GetVersion(void)
{
    return s_i2cDriverVersion;
}

static ARM_I2C_CAPABILITIES I2Cx_GetCapabilities(void)
{
    return s_i2cDriverCapabilities;
}

#endif

#if ((defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN) || (defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN) ||     \
     (defined(RTE_I2C2_DMA_EN) && RTE_I2C2_DMA_EN) || (defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN) ||     \
     (defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN) || (defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN) ||     \
     (defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN) || (defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN) ||     \
     (defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN) || (defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN) ||     \
     (defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN) || (defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN) || \
     (defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN) || (defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN))

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
static void KSDK_I2C_MASTER_DmaCallback(I2C_Type *base,
                                        i2c_master_dma_handle_t *handle,
                                        status_t status,
                                        void *userData)
{
    uint32_t event = 0U;

    if (status == kStatus_Success) /* Occurs after Master Transmit/Receive operation has finished. */
    {
        event = ARM_I2C_EVENT_TRANSFER_DONE;
    }
    else if (status == kStatus_I2C_Nak) /* Slave nacks master before all data are transmitted */
    {
        event = ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    }
    else if (status == kStatus_I2C_Addr_Nak) /* Failed during slave probing */
    {
        event = ARM_I2C_EVENT_ADDRESS_NACK;
    }
    else if (status == kStatus_I2C_ArbitrationLost) /* Arbitration lost */
    {
        event = ARM_I2C_EVENT_ARBITRATION_LOST;
    }
    else /* kStatus_I2C_UnexpectedState, kStatus_I2C_Busy and kStatus_I2C_StartStopError */
    {
        event = ARM_I2C_EVENT_BUS_ERROR;
    }

    if (userData != NULL)
    {
        ((ARM_I2C_SignalEvent_t)userData)(event);
    }
}

static int32_t I2C_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event, cmsis_i2c_dma_driver_state_t *i2c)
{
    if (0U == (i2c->flags & (uint8_t)I2C_FLAG_INIT))
    {
        DMA_EnableChannel(i2c->dmaResource->i2cDmaBase, i2c->dmaResource->i2cDmaChannel);
        DMA_CreateHandle(i2c->dmaHandle, i2c->dmaResource->i2cDmaBase, i2c->dmaResource->i2cDmaChannel);

        I2C_MasterTransferCreateHandleDMA(i2c->resource->base, i2c->master_dma_handle, KSDK_I2C_MASTER_DmaCallback,
                                          (void *)cb_event, i2c->dmaHandle);
        i2c->flags = (uint8_t)I2C_FLAG_INIT;
    }
    return ARM_DRIVER_OK;
}

static int32_t I2C_Master_DmaUninitialize(cmsis_i2c_dma_driver_state_t *i2c)
{
    i2c->flags = (uint8_t)I2C_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t I2C_Master_DmaTransmit(
    uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending, cmsis_i2c_dma_driver_state_t *i2c)
{
    int32_t status;
    int32_t ret;
    i2c_master_transfer_t masterXfer;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (i2c->master_dma_handle->state != 0U)
    {
        return ARM_DRIVER_ERROR_BUSY;
    }

    masterXfer.slaveAddress   = (uint8_t)addr;                      /*7-bit slave address.*/
    masterXfer.direction      = kI2C_Write;                         /*Transfer direction.*/
    masterXfer.subaddress     = 0U;                                 /*Sub address*/
    masterXfer.subaddressSize = 0U;                                 /*Size of command buffer.*/
    masterXfer.data           = (void *)data;                       /*Transfer buffer.*/
    masterXfer.dataSize       = num;                                /*Transfer size.*/
    masterXfer.flags          = (uint32_t)kI2C_TransferDefaultFlag; /*Transfer flag which controls the transfer.*/

    if (xfer_pending)
    {
        masterXfer.flags |= (uint32_t)kI2C_TransferNoStopFlag;
    }

    status = I2C_MasterTransferDMA(i2c->resource->base, i2c->master_dma_handle, &masterXfer);
    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_I2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t I2C_Master_DmaReceive(
    uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending, cmsis_i2c_dma_driver_state_t *i2c)
{
    int32_t status;
    int32_t ret;
    i2c_master_transfer_t masterXfer;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (i2c->master_dma_handle->state != 0U)
    {
        return ARM_DRIVER_ERROR_BUSY;
    }

    masterXfer.slaveAddress   = (uint8_t)addr;                      /*7-bit slave address.*/
    masterXfer.direction      = kI2C_Read;                          /*Transfer direction.*/
    masterXfer.subaddress     = 0U;                                 /*Sub address*/
    masterXfer.subaddressSize = 0U;                                 /*Size of command buffer.*/
    masterXfer.data           = (uint8_t *)data;                    /*Transfer buffer.*/
    masterXfer.dataSize       = num;                                /*Transfer size.*/
    masterXfer.flags          = (uint32_t)kI2C_TransferDefaultFlag; /*Transfer flag which controls the transfer.*/

    if (xfer_pending)
    {
        masterXfer.flags |= (uint32_t)kI2C_TransferNoStopFlag;
    }

    status = I2C_MasterTransferDMA(i2c->resource->base, i2c->master_dma_handle, &masterXfer);
    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_I2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t I2C_Master_DmaGetDataCount(cmsis_i2c_dma_driver_state_t *i2c)
{
    size_t cnt; /*the number of currently transferred data bytes*/

    (void)I2C_MasterTransferGetCountDMA(i2c->resource->base, i2c->master_dma_handle, &cnt);
    return (int32_t)cnt;
}

static int32_t I2C_Master_DmaControl(uint32_t control, uint32_t arg, cmsis_i2c_dma_driver_state_t *i2c)
{
    uint32_t baudRate_Bps = 0;
    int32_t result        = ARM_DRIVER_OK;
    switch (control)
    {
        /* Not supported */
        case ARM_I2C_OWN_ADDRESS:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        /*Set Bus Speed; arg = bus speed*/
        case ARM_I2C_BUS_SPEED:
            switch (arg)
            {
                case ARM_I2C_BUS_SPEED_STANDARD:
                    baudRate_Bps = 100000;
                    break;
                case ARM_I2C_BUS_SPEED_FAST:
                    baudRate_Bps = 400000;
                    break;
                case ARM_I2C_BUS_SPEED_FAST_PLUS:
                    baudRate_Bps = 1000000;
                    break;
                default:
                    result = ARM_DRIVER_ERROR_UNSUPPORTED;
                    break;
            }
            I2C_MasterSetBaudRate(i2c->resource->base, baudRate_Bps, i2c->resource->GetFreq());
            break;
        /* Not supported */
        case ARM_I2C_BUS_CLEAR:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        /*Aborts the data transfer  when Master for Transmit or Receive*/
        case ARM_I2C_ABORT_TRANSFER:
            /*disable dma*/
            I2C_MasterTransferAbortDMA(i2c->resource->base, i2c->master_dma_handle);

            i2c->master_dma_handle->transferCount     = 0;
            i2c->master_dma_handle->transfer.data     = NULL;
            i2c->master_dma_handle->transfer.dataSize = 0;
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static int32_t I2C_Master_DmaPowerControl(ARM_POWER_STATE state, cmsis_i2c_dma_driver_state_t *i2c)
{
    int32_t result = ARM_DRIVER_OK;
    switch (state)
    {
        /*terminates any pending data transfers, disable i2c moduole and i2c clock and related dma*/
        case ARM_POWER_OFF:
            if ((i2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                (void)I2C_Master_DmaControl(ARM_I2C_ABORT_TRANSFER, 0, i2c);
                I2C_MasterDeinit(i2c->resource->base);
                DMA_DisableChannel(i2c->dmaResource->i2cDmaBase, i2c->dmaResource->i2cDmaChannel);
                i2c->flags = (uint8_t)I2C_FLAG_INIT;
            }
            break;
        /* Not supported */
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        /*enable i2c moduole and i2c clock*/
        case ARM_POWER_FULL:
            if (i2c->flags == (uint8_t)I2C_FLAG_UNINIT)
            {
                return ARM_DRIVER_ERROR;
            }

            if ((i2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }
            (void)FLEXCOMM_Init(i2c->resource->base, FLEXCOMM_PERIPH_I2C);
            I2C_MasterEnable(i2c->resource->base, true);
            i2c->flags |= (uint8_t)I2C_FLAG_POWER;
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static ARM_I2C_STATUS I2C_Master_DmaGetStatus(cmsis_i2c_dma_driver_state_t *i2c)
{
    ARM_I2C_STATUS stat      = {0};
    uint32_t ksdk_i2c_status = I2C_GetStatusFlags(i2c->resource->base);

    stat.busy      = (uint32_t)(0UL == (ksdk_i2c_status & (uint32_t)I2C_STAT_MSTPENDING_MASK)); /*Busy flag.*/
    stat.direction = (uint32_t)i2c->master_dma_handle->transfer.direction; /*Direction: 0=Transmitter, 1=Receiver.*/
    stat.mode      = 1UL;                                                  /*Mode: 0=Slave, 1=Master.*/
    stat.arbitration_lost = (uint32_t)((ksdk_i2c_status & (uint32_t)I2C_STAT_MSTARBLOSS_MASK) != 0U);
    /*Master lost arbitration (cleared on start of next Master operation)*/

    return stat;
}

#endif

#endif

#if ((defined(RTE_I2C0) && RTE_I2C0 && !(defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN)) ||     \
     (defined(RTE_I2C1) && RTE_I2C1 && !(defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN)) ||     \
     (defined(RTE_I2C2) && RTE_I2C2 && !(defined(RTE_I2C2_DMA_EN) && RTE_I2C2_DMA_EN)) ||     \
     (defined(RTE_I2C3) && RTE_I2C3 && !(defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN)) ||     \
     (defined(RTE_I2C4) && RTE_I2C4 && !(defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN)) ||     \
     (defined(RTE_I2C5) && RTE_I2C5 && !(defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN)) ||     \
     (defined(RTE_I2C6) && RTE_I2C6 && !(defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN)) ||     \
     (defined(RTE_I2C7) && RTE_I2C7 && !(defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN)) ||     \
     (defined(RTE_I2C8) && RTE_I2C8 && !(defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN)) ||     \
     (defined(RTE_I2C9) && RTE_I2C9 && !(defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN)) ||     \
     (defined(RTE_I2C10) && RTE_I2C10 && !(defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN)) || \
     (defined(RTE_I2C11) && RTE_I2C11 && !(defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN)) || \
     (defined(RTE_I2C12) && RTE_I2C12 && !(defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN)) || \
     (defined(RTE_I2C13) && RTE_I2C13 && !(defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN)))

static void KSDK_I2C_SLAVE_InterruptCallback(I2C_Type *base, volatile i2c_slave_transfer_t *xfer, void *param)
{
    uint32_t event;

    switch (xfer->event)
    {
        case kI2C_SlaveCompletionEvent: /* Occurs after Slave Transmit/Receive operation has finished. */
            event = ARM_I2C_EVENT_TRANSFER_DONE;
            break;
        default:
            event = ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
            break;
    }

    if (param != NULL)
    {
        ((ARM_I2C_SignalEvent_t)param)(event);
    }
}

static void KSDK_I2C_MASTER_InterruptCallback(I2C_Type *base,
                                              i2c_master_handle_t *handle,
                                              status_t status,
                                              void *userData)
{
    uint32_t event;

    switch (status)
    {
        case kStatus_Success: /* Occurs after Master Transmit/Receive operation has finished. */
            event = ARM_I2C_EVENT_TRANSFER_DONE;
            break;
        case kStatus_I2C_ArbitrationLost: /*Occurs in master mode when arbitration is lost.*/
            event = ARM_I2C_EVENT_ARBITRATION_LOST;
            break;
        case kStatus_I2C_Nak: /* Slave nacks master before all data are transmitted */
            event = ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
            break;
        case kStatus_I2C_Addr_Nak: /* Failed during slave probing */
            event = ARM_I2C_EVENT_ADDRESS_NACK;
            break;
        default:
            event = ARM_I2C_EVENT_BUS_ERROR;
            break;
    }

    /* User data is actually CMSIS driver callback. */
    if (userData != NULL)
    {
        ((ARM_I2C_SignalEvent_t)userData)(event);
    }
}

static int32_t I2C_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    if (0U == (i2c->flags & (uint8_t)I2C_FLAG_INIT))
    {
        i2c->cb_event = cb_event; /* cb_event is CMSIS driver callback. */
        i2c->flags    = (uint8_t)I2C_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t I2C_InterruptUninitialize(cmsis_i2c_interrupt_driver_state_t *i2c)
{
    i2c->flags = (uint8_t)I2C_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t I2C_Master_InterruptTransmit(
    uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    int32_t status;
    int32_t ret;
    i2c_master_transfer_t masterXfer;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (i2c->handle->master_handle.state != 0U)
    {
        return ARM_DRIVER_ERROR_BUSY;
    }

    I2C_MasterEnable(i2c->resource->base, true);

    /*create master_handle*/
    I2C_MasterTransferCreateHandle(i2c->resource->base, &(i2c->handle->master_handle),
                                   KSDK_I2C_MASTER_InterruptCallback, (void *)i2c->cb_event);

    masterXfer.slaveAddress   = (uint8_t)addr;                      /*7-bit slave address.*/
    masterXfer.direction      = kI2C_Write;                         /*Transfer direction.*/
    masterXfer.subaddress     = 0U;                                 /*Sub address*/
    masterXfer.subaddressSize = 0U;                                 /*Size of command buffer.*/
    masterXfer.data           = (uint8_t *)data;                    /*Transfer buffer.*/
    masterXfer.dataSize       = num;                                /*Transfer size.*/
    masterXfer.flags          = (uint32_t)kI2C_TransferDefaultFlag; /*Transfer flag which controls the transfer.*/

    if (xfer_pending)
    {
        masterXfer.flags |= (uint32_t)kI2C_TransferNoStopFlag;
    }

    status = I2C_MasterTransferNonBlocking(i2c->resource->base, &(i2c->handle->master_handle), &masterXfer);
    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_I2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t I2C_Master_InterruptReceive(
    uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    int32_t status;
    int32_t ret;
    i2c_master_transfer_t masterXfer;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (i2c->handle->master_handle.state != 0U)
    {
        return ARM_DRIVER_ERROR_BUSY;
    }

    I2C_MasterEnable(i2c->resource->base, true);

    /*create master_handle*/
    I2C_MasterTransferCreateHandle(i2c->resource->base, &(i2c->handle->master_handle),
                                   KSDK_I2C_MASTER_InterruptCallback, (void *)i2c->cb_event);

    masterXfer.slaveAddress   = (uint8_t)addr;                      /*7-bit slave address.*/
    masterXfer.direction      = kI2C_Read;                          /*Transfer direction.*/
    masterXfer.subaddress     = 0U;                                 /*Sub address*/
    masterXfer.subaddressSize = 0U;                                 /*Size of command buffer.*/
    masterXfer.data           = data;                               /*Transfer buffer.*/
    masterXfer.dataSize       = num;                                /*Transfer size.*/
    masterXfer.flags          = (uint32_t)kI2C_TransferDefaultFlag; /*Transfer flag which controls the transfer.*/

    if (xfer_pending)
    {
        masterXfer.flags |= (uint32_t)kI2C_TransferNoStopFlag;
    }

    status = I2C_MasterTransferNonBlocking(i2c->resource->base, &(i2c->handle->master_handle), &masterXfer);
    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_I2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t I2C_Slave_InterruptTransmit(const uint8_t *data, uint32_t num, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    int32_t status;
    int32_t ret;

    /* set Slave enable */
    I2C_SlaveEnable(i2c->resource->base, true);

    /*create slave_handle*/
    I2C_SlaveTransferCreateHandle(i2c->resource->base, &(i2c->handle->slave_handle), KSDK_I2C_SLAVE_InterruptCallback,
                                  (void *)i2c->cb_event);

    status = I2C_SlaveTransferNonBlocking(i2c->resource->base, &(i2c->handle->slave_handle),
                                          (uint32_t)kI2C_SlaveCompletionEvent);

    i2c->handle->slave_handle.transfer.txData =
        (uint8_t *)data;                             /*Pointer to buffer with data to transmit to I2C Master*/
    i2c->handle->slave_handle.transfer.txSize = num; /*Number of data bytes to transmit*/
    i2c->handle->slave_handle.transfer.transferredCount =
        0U; /*Number of bytes actually transferred since start or last repeated start. */

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_I2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t I2C_Slave_InterruptReceive(uint8_t *data, uint32_t num, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    int32_t status;
    int32_t ret;

    /* set Slave enable */
    I2C_SlaveEnable(i2c->resource->base, true);

    /*create slave_handle*/
    I2C_SlaveTransferCreateHandle(i2c->resource->base, &(i2c->handle->slave_handle), KSDK_I2C_SLAVE_InterruptCallback,
                                  (void *)i2c->cb_event);

    status = I2C_SlaveTransferNonBlocking(i2c->resource->base, &(i2c->handle->slave_handle),
                                          (uint32_t)kI2C_SlaveCompletionEvent);

    i2c->handle->slave_handle.transfer.rxData = data; /*Pointer to buffer with data to transmit to I2C Master*/
    i2c->handle->slave_handle.transfer.rxSize = num;  /*Number of data bytes to transmit*/
    i2c->handle->slave_handle.transfer.transferredCount =
        0U; /*Number of bytes actually transferred since start or last repeated start. */

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_I2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t I2C_InterruptGetDataCount(cmsis_i2c_interrupt_driver_state_t *i2c)
{
    uint32_t cnt = 0; /*the number of currently transferred data bytes*/

    if ((i2c->resource->base->CFG & (uint8_t)I2C_CFG_MSTEN_MASK) != 0U)
    {
        cnt = i2c->handle->master_handle.transferCount;
    }
    else
    {
        cnt = i2c->handle->slave_handle.transfer.transferredCount;
    }

    return (int32_t)cnt;
}

static int32_t I2C_InterruptControl(uint32_t control, uint32_t arg, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    uint32_t baudRate_Bps;
    uint32_t clkDiv;
    int32_t result = ARM_DRIVER_OK;
    switch (control)
    {
        /*Set Own Slave Address; arg = slave address*/
        case ARM_I2C_OWN_ADDRESS:
            /* Use as slave, set CLKDIV for clock stretching, ensure data set up time for standard mode 250ns. */
            /* divVal = (sourceClock_Hz / 1000000) * (dataSetupTime_ns / 1000) */
            clkDiv                      = i2c->resource->GetFreq() / 1000U;
            clkDiv                      = (clkDiv * 250U) / 1000000U;
            i2c->resource->base->CLKDIV = clkDiv & I2C_CLKDIV_DIVVAL_MASK;

            /* Set slave address. */
            I2C_SlaveSetAddress(i2c->resource->base, kI2C_SlaveAddressRegister0, (uint8_t)arg, false);
            /* set Slave address 0 qual */
            i2c->resource->base->SLVQUAL0 = I2C_SLVQUAL0_QUALMODE0(0) | I2C_SLVQUAL0_SLVQUAL0(0);
            break;
        /*Set Bus Speed; arg = bus speed*/
        case ARM_I2C_BUS_SPEED:
            switch (arg)
            {
                case ARM_I2C_BUS_SPEED_STANDARD:
                    baudRate_Bps = 100000;
                    break;
                case ARM_I2C_BUS_SPEED_FAST:
                    baudRate_Bps = 400000;
                    break;
                case ARM_I2C_BUS_SPEED_FAST_PLUS:
                    baudRate_Bps = 1000000;
                    break;
                default:
                    result = ARM_DRIVER_ERROR_UNSUPPORTED;
                    break;
            }
            if (result == ARM_DRIVER_OK)
            {
                I2C_MasterSetBaudRate(i2c->resource->base, baudRate_Bps, i2c->resource->GetFreq());
            }
            break;
        // Not supported
        case ARM_I2C_BUS_CLEAR:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        /*Aborts the data transfer between Master and Slave for Transmit or Receive*/
        case ARM_I2C_ABORT_TRANSFER:
            if ((i2c->resource->base->CFG & (uint8_t)I2C_CFG_MSTEN_MASK) != 0U)
            {
                /*disable master interrupt and send STOP signal*/
                (void)I2C_MasterTransferAbort(i2c->resource->base, &(i2c->handle->master_handle));

                i2c->handle->master_handle.transferCount     = 0;
                i2c->handle->master_handle.transfer.data     = NULL;
                i2c->handle->master_handle.transfer.dataSize = 0;
            }
            /*if slave receive*/
            if (((i2c->resource->base->CFG & (uint32_t)I2C_CFG_SLVEN_MASK) != 0U) &&
                ((i2c->handle->slave_handle.slaveFsm) == kI2C_SlaveFsmReceive))
            {
                /*disable slave interrupt*/
                I2C_SlaveTransferAbort(i2c->resource->base, &(i2c->handle->slave_handle));

                i2c->handle->slave_handle.transfer.transferredCount = 0;
                i2c->handle->slave_handle.transfer.txData           = NULL;
                i2c->handle->slave_handle.transfer.rxData           = NULL;
            }
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static int32_t I2C_InterruptPowerControl(ARM_POWER_STATE state, cmsis_i2c_interrupt_driver_state_t *i2c)
{
    int32_t result = ARM_DRIVER_OK;
    switch (state)
    {
        /*terminates any pending data transfers, disable i2c moduole and i2c clock*/
        case ARM_POWER_OFF:
            if ((i2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                (void)I2C_InterruptControl(ARM_I2C_ABORT_TRANSFER, 0, i2c);
                I2C_MasterDeinit(i2c->resource->base);
                I2C_SlaveDeinit(i2c->resource->base);
                i2c->flags = (uint8_t)I2C_FLAG_INIT;
            }
            break;
        /* Not supported */
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        /*enable i2c moduole and i2c clock*/
        case ARM_POWER_FULL:
            if (i2c->flags == (uint8_t)I2C_FLAG_UNINIT)
            {
                return ARM_DRIVER_ERROR;
            }

            if ((i2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }
            (void)FLEXCOMM_Init(i2c->resource->base, FLEXCOMM_PERIPH_I2C);
            i2c->flags |= (uint8_t)I2C_FLAG_POWER;
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static ARM_I2C_STATUS I2C_InterruptGetStatus(cmsis_i2c_interrupt_driver_state_t *i2c)
{
    ARM_I2C_STATUS stat      = {0};
    uint32_t ksdk_i2c_status = I2C_GetStatusFlags(i2c->resource->base);

    if ((i2c->resource->base->CFG & (uint32_t)I2C_CFG_MSTEN_MASK) != 0U)
    {
        stat.busy = (uint32_t)(0UL == (ksdk_i2c_status & (uint32_t)I2C_STAT_MSTPENDING_MASK)); /*Busy flag.*/
        stat.direction =
            (uint32_t)i2c->handle->master_handle.transfer.direction; /*Direction: 0=Transmitter, 1=Receiver.*/
        stat.mode             = 1UL;                                 /*Mode: 0=Slave, 1=Master.*/
        stat.arbitration_lost = (uint32_t)((ksdk_i2c_status & (uint32_t)I2C_STAT_MSTARBLOSS_MASK) != 0U);
        /*Master lost arbitration (cleared on start of next Master operation)*/
    }

    if ((i2c->resource->base->CFG & (uint32_t)I2C_CFG_SLVEN_MASK) != 0U)
    {
        stat.busy = (uint32_t)(0UL == (ksdk_i2c_status & (uint32_t)I2C_STAT_SLVPENDING_MASK)); /*Busy flag.*/
        if (i2c->handle->slave_handle.slaveFsm == kI2C_SlaveFsmReceive)
        {
            stat.direction = 1; /*Direction: 0=Transmitter, 1=Receiver.*/
        }
        else
        {
            stat.direction = 0; /*Direction: 0=Transmitter, 1=Receiver.*/
        }
        stat.mode = 0; /*Mode: 0=Slave, 1=Master.*/
    }

    return stat;
}

#endif

#if defined(I2C0) && defined(RTE_I2C0) && RTE_I2C0
/* User needs to provide the implementation for I2C0_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C0_GetFreq(void);

static cmsis_i2c_resource_t I2C0_Resource = {I2C0, I2C0_GetFreq};

#if (defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C0_DmaResource = {RTE_I2C0_Master_DMA_BASE, RTE_I2C0_Master_DMA_CH};

static i2c_master_dma_handle_t I2C0_DmaHandle;
static dma_handle_t I2C0_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c0_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C0_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C0_DmaDriverState  = {
#endif
    &I2C0_Resource,
    &I2C0_DmaResource,
    &I2C0_DmaHandle,
    &I2C0_DmaTxRxHandle,
};

static int32_t I2C0_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C0_PIN_INIT
    RTE_I2C0_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C0_DmaDriverState);
}

static int32_t I2C0_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C0_PIN_DEINIT
    RTE_I2C0_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C0_DmaDriverState);
}

static int32_t I2C0_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C0_DmaDriverState);
}

static int32_t I2C0_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C0_DmaDriverState);
}

static int32_t I2C0_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C0_DmaDriverState);
}

static int32_t I2C0_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C0_DmaDriverState);
}

static int32_t I2C0_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C0_DmaDriverState);
}

static ARM_I2C_STATUS I2C0_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C0_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C0_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c0_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C0_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C0_InterruptDriverState  = {
#endif
    &I2C0_Resource,
    &I2C0_handle,

};

static int32_t I2C0_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C0_PIN_INIT
    RTE_I2C0_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C0_InterruptDriverState);
}

static int32_t I2C0_InterruptUninitialize(void)
{
#ifdef RTE_I2C0_PIN_DEINIT
    RTE_I2C0_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C0_InterruptDriverState);
}

static int32_t I2C0_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C0_InterruptDriverState);
}

static int32_t I2C0_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C0_InterruptDriverState);
}

static int32_t I2C0_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C0_InterruptDriverState);
}

static int32_t I2C0_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C0_InterruptDriverState);
}

static int32_t I2C0_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C0_InterruptDriverState);
}

static int32_t I2C0_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C0_InterruptDriverState);
}

static int32_t I2C0_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C0_InterruptDriverState);
}

static ARM_I2C_STATUS I2C0_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C0_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C0 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN
                              I2C0_Master_DmaInitialize,
                              I2C0_Master_DmaUninitialize,
                              I2C0_Master_DmaPowerControl,
                              I2C0_Master_DmaTransmit,
                              I2C0_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C0_Master_DmaGetDataCount,
                              I2C0_Master_DmaControl,
                              I2C0_Master_DmaGetStatus
#else
                              I2C0_InterruptInitialize,
                              I2C0_InterruptUninitialize,
                              I2C0_InterruptPowerControl,
                              I2C0_Master_InterruptTransmit,
                              I2C0_Master_InterruptReceive,
                              I2C0_Slave_InterruptTransmit,
                              I2C0_Slave_InterruptReceive,
                              I2C0_InterruptGetDataCount,
                              I2C0_InterruptControl,
                              I2C0_InterruptGetStatus
#endif
};

#endif

#if defined(I2C1) && defined(RTE_I2C1) && RTE_I2C1

/* User needs to provide the implementation for I2C1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C1_GetFreq(void);

static cmsis_i2c_resource_t I2C1_Resource = {I2C1, I2C1_GetFreq};

#if (defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C1_DmaResource = {RTE_I2C1_Master_DMA_BASE, RTE_I2C1_Master_DMA_CH};

static i2c_master_dma_handle_t I2C1_DmaHandle;
static dma_handle_t I2C1_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c1_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C1_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C1_DmaDriverState  = {
#endif
    &I2C1_Resource,
    &I2C1_DmaResource,
    &I2C1_DmaHandle,
    &I2C1_DmaTxRxHandle,
};

static int32_t I2C1_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C1_PIN_INIT
    RTE_I2C1_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C1_DmaDriverState);
}

static int32_t I2C1_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C1_PIN_DEINIT
    RTE_I2C1_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C1_DmaDriverState);
}

static int32_t I2C1_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C1_DmaDriverState);
}

static int32_t I2C1_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C1_DmaDriverState);
}

static int32_t I2C1_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C1_DmaDriverState);
}

static int32_t I2C1_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C1_DmaDriverState);
}

static int32_t I2C1_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C1_DmaDriverState);
}

static ARM_I2C_STATUS I2C1_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C1_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C1_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c1_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C1_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C1_InterruptDriverState  = {
#endif
    &I2C1_Resource,
    &I2C1_Handle,
};

static int32_t I2C1_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C1_PIN_INIT
    RTE_I2C1_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C1_InterruptDriverState);
}

static int32_t I2C1_InterruptUninitialize(void)
{
#ifdef RTE_I2C1_PIN_DEINIT
    RTE_I2C1_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C1_InterruptDriverState);
}

static int32_t I2C1_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C1_InterruptDriverState);
}

static int32_t I2C1_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C1_InterruptDriverState);
}

static int32_t I2C1_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C1_InterruptDriverState);
}

static int32_t I2C1_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C1_InterruptDriverState);
}

static int32_t I2C1_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C1_InterruptDriverState);
}

static int32_t I2C1_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C1_InterruptDriverState);
}

static int32_t I2C1_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C1_InterruptDriverState);
}

static ARM_I2C_STATUS I2C1_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C1_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C1 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN
                              I2C1_Master_DmaInitialize,
                              I2C1_Master_DmaUninitialize,
                              I2C1_Master_DmaPowerControl,
                              I2C1_Master_DmaTransmit,
                              I2C1_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C1_Master_DmaGetDataCount,
                              I2C1_Master_DmaControl,
                              I2C1_Master_DmaGetStatus
#else
                              I2C1_InterruptInitialize,
                              I2C1_InterruptUninitialize,
                              I2C1_InterruptPowerControl,
                              I2C1_Master_InterruptTransmit,
                              I2C1_Master_InterruptReceive,
                              I2C1_Slave_InterruptTransmit,
                              I2C1_Slave_InterruptReceive,
                              I2C1_InterruptGetDataCount,
                              I2C1_InterruptControl,
                              I2C1_InterruptGetStatus
#endif
};

#endif

#if defined(I2C2) && defined(RTE_I2C2) && RTE_I2C2

/* User needs to provide the implementation for I2C2_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C2_GetFreq(void);

static cmsis_i2c_resource_t I2C2_Resource = {I2C2, I2C2_GetFreq};

#if (defined(RTE_I2C2_DMA_EN) && RTE_I2C2_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C2_DmaResource = {RTE_I2C2_Master_DMA_BASE, RTE_I2C2_Master_DMA_CH};

static i2c_master_dma_handle_t I2C2_DmaHandle;
static dma_handle_t I2C2_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c2_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C2_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C2_DmaDriverState  = {
#endif
    &I2C2_Resource,
    &I2C2_DmaResource,
    &I2C2_DmaHandle,
    &I2C2_DmaTxRxHandle,
};

static int32_t I2C2_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C2_PIN_INIT
    RTE_I2C2_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C2_DmaDriverState);
}

static int32_t I2C2_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C2_PIN_DEINIT
    RTE_I2C2_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C2_DmaDriverState);
}

static int32_t I2C2_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C2_DmaDriverState);
}

static int32_t I2C2_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C2_DmaDriverState);
}

static int32_t I2C2_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C2_DmaDriverState);
}

static int32_t I2C2_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C2_DmaDriverState);
}

static int32_t I2C2_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C2_DmaDriverState);
}

static ARM_I2C_STATUS I2C2_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C2_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C2_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c2_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C2_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C2_InterruptDriverState  = {
#endif
    &I2C2_Resource,
    &I2C2_Handle,

};

static int32_t I2C2_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C2_PIN_INIT
    RTE_I2C2_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C2_InterruptDriverState);
}

static int32_t I2C2_InterruptUninitialize(void)
{
#ifdef RTE_I2C2_PIN_DEINIT
    RTE_I2C2_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C2_InterruptDriverState);
}

static int32_t I2C2_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C2_InterruptDriverState);
}

static int32_t I2C2_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C2_InterruptDriverState);
}

static int32_t I2C2_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C2_InterruptDriverState);
}

static int32_t I2C2_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C2_InterruptDriverState);
}

static int32_t I2C2_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C2_InterruptDriverState);
}

static int32_t I2C2_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C2_InterruptDriverState);
}

static int32_t I2C2_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C2_InterruptDriverState);
}

static ARM_I2C_STATUS I2C2_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C2_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C2 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C2_DMA_EN) && (RTE_I2C2_DMA_EN)
                              I2C2_Master_DmaInitialize,
                              I2C2_Master_DmaUninitialize,
                              I2C2_Master_DmaPowerControl,
                              I2C2_Master_DmaTransmit,
                              I2C2_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C2_Master_DmaGetDataCount,
                              I2C2_Master_DmaControl,
                              I2C2_Master_DmaGetStatus
#else
                              I2C2_InterruptInitialize,
                              I2C2_InterruptUninitialize,
                              I2C2_InterruptPowerControl,
                              I2C2_Master_InterruptTransmit,
                              I2C2_Master_InterruptReceive,
                              I2C2_Slave_InterruptTransmit,
                              I2C2_Slave_InterruptReceive,
                              I2C2_InterruptGetDataCount,
                              I2C2_InterruptControl,
                              I2C2_InterruptGetStatus
#endif
};

#endif

#if defined(I2C3) && defined(RTE_I2C3) && RTE_I2C3

/* User needs to provide the implementation for I2C3_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C3_GetFreq(void);

static cmsis_i2c_resource_t I2C3_Resource = {I2C3, I2C3_GetFreq};

#if (defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C3_DmaResource = {RTE_I2C3_Master_DMA_BASE, RTE_I2C3_Master_DMA_CH};

static i2c_master_dma_handle_t I2C3_DmaHandle;
static dma_handle_t I2C3_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c3_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C3_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C3_DmaDriverState  = {
#endif
    &I2C3_Resource,
    &I2C3_DmaResource,
    &I2C3_DmaHandle,
    &I2C3_DmaTxRxHandle,
};

static int32_t I2C3_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C3_PIN_INIT
    RTE_I2C3_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C3_DmaDriverState);
}

static int32_t I2C3_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C3_PIN_DEINIT
    RTE_I2C3_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C3_DmaDriverState);
}

static int32_t I2C3_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C3_DmaDriverState);
}

static int32_t I2C3_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C3_DmaDriverState);
}

static int32_t I2C3_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C3_DmaDriverState);
}

static int32_t I2C3_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C3_DmaDriverState);
}

static int32_t I2C3_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C3_DmaDriverState);
}

static ARM_I2C_STATUS I2C3_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C3_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C3_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c3_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C3_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C3_InterruptDriverState  = {
#endif
    &I2C3_Resource,
    &I2C3_Handle,
};

static int32_t I2C3_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C3_PIN_INIT
    RTE_I2C3_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C3_InterruptDriverState);
}

static int32_t I2C3_InterruptUninitialize(void)
{
#ifdef RTE_I2C3_PIN_DEINIT
    RTE_I2C3_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C3_InterruptDriverState);
}

static int32_t I2C3_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C3_InterruptDriverState);
}

static int32_t I2C3_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C3_InterruptDriverState);
}

static int32_t I2C3_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C3_InterruptDriverState);
}

static int32_t I2C3_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C3_InterruptDriverState);
}

static int32_t I2C3_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C3_InterruptDriverState);
}

static int32_t I2C3_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C3_InterruptDriverState);
}

static int32_t I2C3_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C3_InterruptDriverState);
}

static ARM_I2C_STATUS I2C3_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C3_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C3 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN
                              I2C3_Master_DmaInitialize,
                              I2C3_Master_DmaUninitialize,
                              I2C3_Master_DmaPowerControl,
                              I2C3_Master_DmaTransmit,
                              I2C3_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C3_Master_DmaGetDataCount,
                              I2C3_Master_DmaControl,
                              I2C3_Master_DmaGetStatus
#else
                              I2C3_InterruptInitialize,
                              I2C3_InterruptUninitialize,
                              I2C3_InterruptPowerControl,
                              I2C3_Master_InterruptTransmit,
                              I2C3_Master_InterruptReceive,
                              I2C3_Slave_InterruptTransmit,
                              I2C3_Slave_InterruptReceive,
                              I2C3_InterruptGetDataCount,
                              I2C3_InterruptControl,
                              I2C3_InterruptGetStatus
#endif
};

#endif

#if defined(I2C4) && defined(RTE_I2C4) && RTE_I2C4
/* User needs to provide the implementation for I2C4_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C4_GetFreq(void);

static cmsis_i2c_resource_t I2C4_Resource = {I2C4, I2C4_GetFreq};

#if (defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C4_DmaResource = {RTE_I2C4_Master_DMA_BASE, RTE_I2C4_Master_DMA_CH};

static i2c_master_dma_handle_t I2C4_DmaHandle;
static dma_handle_t I2C4_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c4_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C4_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C4_DmaDriverState  = {
#endif
    &I2C4_Resource,
    &I2C4_DmaResource,
    &I2C4_DmaHandle,
    &I2C4_DmaTxRxHandle,
};

static int32_t I2C4_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C4_PIN_INIT
    RTE_I2C4_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C4_DmaDriverState);
}

static int32_t I2C4_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C4_PIN_DEINIT
    RTE_I2C4_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C4_DmaDriverState);
}

static int32_t I2C4_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C4_DmaDriverState);
}

static int32_t I2C4_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C4_DmaDriverState);
}

static int32_t I2C4_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C4_DmaDriverState);
}

static int32_t I2C4_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C4_DmaDriverState);
}

static int32_t I2C4_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C4_DmaDriverState);
}

static ARM_I2C_STATUS I2C4_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C4_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C4_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c4_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C4_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C4_InterruptDriverState  = {
#endif
    &I2C4_Resource,
    &I2C4_handle,

};

static int32_t I2C4_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C4_PIN_INIT
    RTE_I2C4_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C4_InterruptDriverState);
}

static int32_t I2C4_InterruptUninitialize(void)
{
#ifdef RTE_I2C4_PIN_DEINIT
    RTE_I2C4_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C4_InterruptDriverState);
}

static int32_t I2C4_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C4_InterruptDriverState);
}

static int32_t I2C4_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C4_InterruptDriverState);
}

static int32_t I2C4_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C4_InterruptDriverState);
}

static int32_t I2C4_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C4_InterruptDriverState);
}

static int32_t I2C4_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C4_InterruptDriverState);
}

static int32_t I2C4_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C4_InterruptDriverState);
}

static int32_t I2C4_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C4_InterruptDriverState);
}

static ARM_I2C_STATUS I2C4_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C4_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C4 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN
                              I2C4_Master_DmaInitialize,
                              I2C4_Master_DmaUninitialize,
                              I2C4_Master_DmaPowerControl,
                              I2C4_Master_DmaTransmit,
                              I2C4_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C4_Master_DmaGetDataCount,
                              I2C4_Master_DmaControl,
                              I2C4_Master_DmaGetStatus
#else
                              I2C4_InterruptInitialize,
                              I2C4_InterruptUninitialize,
                              I2C4_InterruptPowerControl,
                              I2C4_Master_InterruptTransmit,
                              I2C4_Master_InterruptReceive,
                              I2C4_Slave_InterruptTransmit,
                              I2C4_Slave_InterruptReceive,
                              I2C4_InterruptGetDataCount,
                              I2C4_InterruptControl,
                              I2C4_InterruptGetStatus
#endif
};

#endif

#if defined(I2C5) && defined(RTE_I2C5) && RTE_I2C5
/* User needs to provide the implementation for I2C5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C5_GetFreq(void);

static cmsis_i2c_resource_t I2C5_Resource = {I2C5, I2C5_GetFreq};

#if (defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C5_DmaResource = {RTE_I2C5_Master_DMA_BASE, RTE_I2C5_Master_DMA_CH};

static i2c_master_dma_handle_t I2C5_DmaHandle;
static dma_handle_t I2C5_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c5_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C5_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C5_DmaDriverState  = {
#endif
    &I2C5_Resource,
    &I2C5_DmaResource,
    &I2C5_DmaHandle,
    &I2C5_DmaTxRxHandle,
};

static int32_t I2C5_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C5_PIN_INIT
    RTE_I2C5_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C5_DmaDriverState);
}

static int32_t I2C5_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C5_PIN_DEINIT
    RTE_I2C5_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C5_DmaDriverState);
}

static int32_t I2C5_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C5_DmaDriverState);
}

static int32_t I2C5_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C5_DmaDriverState);
}

static int32_t I2C5_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C5_DmaDriverState);
}

static int32_t I2C5_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C5_DmaDriverState);
}

static int32_t I2C5_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C5_DmaDriverState);
}

static ARM_I2C_STATUS I2C5_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C5_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C5_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c5_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C5_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C5_InterruptDriverState  = {
#endif
    &I2C5_Resource,
    &I2C5_handle,

};

static int32_t I2C5_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C5_PIN_INIT
    RTE_I2C5_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C5_InterruptDriverState);
}

static int32_t I2C5_InterruptUninitialize(void)
{
#ifdef RTE_I2C5_PIN_DEINIT
    RTE_I2C5_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C5_InterruptDriverState);
}

static int32_t I2C5_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C5_InterruptDriverState);
}

static int32_t I2C5_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C5_InterruptDriverState);
}

static int32_t I2C5_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C5_InterruptDriverState);
}

static int32_t I2C5_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C5_InterruptDriverState);
}

static int32_t I2C5_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C5_InterruptDriverState);
}

static int32_t I2C5_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C5_InterruptDriverState);
}

static int32_t I2C5_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C5_InterruptDriverState);
}

static ARM_I2C_STATUS I2C5_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C5_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C5 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN
                              I2C5_Master_DmaInitialize,
                              I2C5_Master_DmaUninitialize,
                              I2C5_Master_DmaPowerControl,
                              I2C5_Master_DmaTransmit,
                              I2C5_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C5_Master_DmaGetDataCount,
                              I2C5_Master_DmaControl,
                              I2C5_Master_DmaGetStatus
#else
                              I2C5_InterruptInitialize,
                              I2C5_InterruptUninitialize,
                              I2C5_InterruptPowerControl,
                              I2C5_Master_InterruptTransmit,
                              I2C5_Master_InterruptReceive,
                              I2C5_Slave_InterruptTransmit,
                              I2C5_Slave_InterruptReceive,
                              I2C5_InterruptGetDataCount,
                              I2C5_InterruptControl,
                              I2C5_InterruptGetStatus
#endif
};

#endif

#if defined(I2C6) && defined(RTE_I2C6) && RTE_I2C6
/* User needs to provide the implementation for I2C6_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C6_GetFreq(void);

static cmsis_i2c_resource_t I2C6_Resource = {I2C6, I2C6_GetFreq};

#if (defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C6_DmaResource = {RTE_I2C6_Master_DMA_BASE, RTE_I2C6_Master_DMA_CH};

static i2c_master_dma_handle_t I2C6_DmaHandle;
static dma_handle_t I2C6_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c6_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C6_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C6_DmaDriverState  = {
#endif
    &I2C6_Resource,
    &I2C6_DmaResource,
    &I2C6_DmaHandle,
    &I2C6_DmaTxRxHandle,
};

static int32_t I2C6_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C6_PIN_INIT
    RTE_I2C6_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C6_DmaDriverState);
}

static int32_t I2C6_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C6_PIN_DEINIT
    RTE_I2C6_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C6_DmaDriverState);
}

static int32_t I2C6_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C6_DmaDriverState);
}

static int32_t I2C6_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C6_DmaDriverState);
}

static int32_t I2C6_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C6_DmaDriverState);
}

static int32_t I2C6_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C6_DmaDriverState);
}

static int32_t I2C6_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C6_DmaDriverState);
}

static ARM_I2C_STATUS I2C6_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C6_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C6_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c6_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C6_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C6_InterruptDriverState  = {
#endif
    &I2C6_Resource,
    &I2C6_handle,

};

static int32_t I2C6_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C6_PIN_INIT
    RTE_I2C6_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C6_InterruptDriverState);
}

static int32_t I2C6_InterruptUninitialize(void)
{
#ifdef RTE_I2C6_PIN_DEINIT
    RTE_I2C6_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C6_InterruptDriverState);
}

static int32_t I2C6_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C6_InterruptDriverState);
}

static int32_t I2C6_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C6_InterruptDriverState);
}

static int32_t I2C6_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C6_InterruptDriverState);
}

static int32_t I2C6_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C6_InterruptDriverState);
}

static int32_t I2C6_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C6_InterruptDriverState);
}

static int32_t I2C6_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C6_InterruptDriverState);
}

static int32_t I2C6_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C6_InterruptDriverState);
}

static ARM_I2C_STATUS I2C6_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C6_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C6 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN
                              I2C6_Master_DmaInitialize,
                              I2C6_Master_DmaUninitialize,
                              I2C6_Master_DmaPowerControl,
                              I2C6_Master_DmaTransmit,
                              I2C6_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C6_Master_DmaGetDataCount,
                              I2C6_Master_DmaControl,
                              I2C6_Master_DmaGetStatus
#else
                              I2C6_InterruptInitialize,
                              I2C6_InterruptUninitialize,
                              I2C6_InterruptPowerControl,
                              I2C6_Master_InterruptTransmit,
                              I2C6_Master_InterruptReceive,
                              I2C6_Slave_InterruptTransmit,
                              I2C6_Slave_InterruptReceive,
                              I2C6_InterruptGetDataCount,
                              I2C6_InterruptControl,
                              I2C6_InterruptGetStatus
#endif
};

#endif

#if defined(I2C7) && defined(RTE_I2C7) && RTE_I2C7
/* User needs to provide the implementation for I2C7_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C7_GetFreq(void);

static cmsis_i2c_resource_t I2C7_Resource = {I2C7, I2C7_GetFreq};

#if (defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C7_DmaResource = {RTE_I2C7_Master_DMA_BASE, RTE_I2C7_Master_DMA_CH};

static i2c_master_dma_handle_t I2C7_DmaHandle;
static dma_handle_t I2C7_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c7_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C7_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C7_DmaDriverState  = {
#endif
    &I2C7_Resource,
    &I2C7_DmaResource,
    &I2C7_DmaHandle,
    &I2C7_DmaTxRxHandle,
};

static int32_t I2C7_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C7_PIN_INIT
    RTE_I2C7_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C7_DmaDriverState);
}

static int32_t I2C7_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C7_PIN_DEINIT
    RTE_I2C7_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C7_DmaDriverState);
}

static int32_t I2C7_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C7_DmaDriverState);
}

static int32_t I2C7_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C7_DmaDriverState);
}

static int32_t I2C7_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C7_DmaDriverState);
}

static int32_t I2C7_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C7_DmaDriverState);
}

static int32_t I2C7_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C7_DmaDriverState);
}

static ARM_I2C_STATUS I2C7_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C7_DmaDriverState);
}

#endif

#else
static cmsis_i2c_handle_t I2C7_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c7_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C7_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C7_InterruptDriverState  = {
#endif
    &I2C7_Resource,
    &I2C7_handle,

};

static int32_t I2C7_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C7_PIN_INIT
    RTE_I2C7_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C7_InterruptDriverState);
}

static int32_t I2C7_InterruptUninitialize(void)
{
#ifdef RTE_I2C7_PIN_DEINIT
    RTE_I2C7_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C7_InterruptDriverState);
}

static int32_t I2C7_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C7_InterruptDriverState);
}

static int32_t I2C7_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C7_InterruptDriverState);
}

static int32_t I2C7_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C7_InterruptDriverState);
}

static int32_t I2C7_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C7_InterruptDriverState);
}

static int32_t I2C7_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C7_InterruptDriverState);
}

static int32_t I2C7_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C7_InterruptDriverState);
}

static int32_t I2C7_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C7_InterruptDriverState);
}

static ARM_I2C_STATUS I2C7_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C7_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C7 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN
                              I2C7_Master_DmaInitialize,
                              I2C7_Master_DmaUninitialize,
                              I2C7_Master_DmaPowerControl,
                              I2C7_Master_DmaTransmit,
                              I2C7_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C7_Master_DmaGetDataCount,
                              I2C7_Master_DmaControl,
                              I2C7_Master_DmaGetStatus
#else
                              I2C7_InterruptInitialize,
                              I2C7_InterruptUninitialize,
                              I2C7_InterruptPowerControl,
                              I2C7_Master_InterruptTransmit,
                              I2C7_Master_InterruptReceive,
                              I2C7_Slave_InterruptTransmit,
                              I2C7_Slave_InterruptReceive,
                              I2C7_InterruptGetDataCount,
                              I2C7_InterruptControl,
                              I2C7_InterruptGetStatus
#endif
};

#endif

#if defined(I2C8) && defined(RTE_I2C8) && RTE_I2C8
/* User needs to provide the implementation for I2C8_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C8_GetFreq(void);

static cmsis_i2c_resource_t I2C8_Resource = {I2C8, I2C8_GetFreq};

#if (defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C8_DmaResource = {RTE_I2C8_Master_DMA_BASE, RTE_I2C8_Master_DMA_CH};

static i2c_master_dma_handle_t I2C8_DmaHandle;
static dma_handle_t I2C8_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c8_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C8_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C8_DmaDriverState  = {
#endif
    &I2C8_Resource,
    &I2C8_DmaResource,
    &I2C8_DmaHandle,
    &I2C8_DmaTxRxHandle,
};

static int32_t I2C8_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C8_PIN_INIT
    RTE_I2C8_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C8_DmaDriverState);
}

static int32_t I2C8_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C8_PIN_DEINIT
    RTE_I2C8_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C8_DmaDriverState);
}

static int32_t I2C8_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C8_DmaDriverState);
}

static int32_t I2C8_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C8_DmaDriverState);
}

static int32_t I2C8_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C8_DmaDriverState);
}

static int32_t I2C8_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C8_DmaDriverState);
}

static int32_t I2C8_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C8_DmaDriverState);
}

static ARM_I2C_STATUS I2C8_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C8_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C8_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c8_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C8_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C8_InterruptDriverState  = {
#endif
    &I2C8_Resource,
    &I2C8_handle,

};

static int32_t I2C8_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C8_PIN_INIT
    RTE_I2C8_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C8_InterruptDriverState);
}

static int32_t I2C8_InterruptUninitialize(void)
{
#ifdef RTE_I2C8_PIN_DEINIT
    RTE_I2C8_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C8_InterruptDriverState);
}

static int32_t I2C8_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C8_InterruptDriverState);
}

static int32_t I2C8_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C8_InterruptDriverState);
}

static int32_t I2C8_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C8_InterruptDriverState);
}

static int32_t I2C8_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C8_InterruptDriverState);
}

static int32_t I2C8_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C8_InterruptDriverState);
}

static int32_t I2C8_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C8_InterruptDriverState);
}

static int32_t I2C8_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C8_InterruptDriverState);
}

static ARM_I2C_STATUS I2C8_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C8_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C8 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN
                              I2C8_Master_DmaInitialize,
                              I2C8_Master_DmaUninitialize,
                              I2C8_Master_DmaPowerControl,
                              I2C8_Master_DmaTransmit,
                              I2C8_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C8_Master_DmaGetDataCount,
                              I2C8_Master_DmaControl,
                              I2C8_Master_DmaGetStatus
#else
                              I2C8_InterruptInitialize,
                              I2C8_InterruptUninitialize,
                              I2C8_InterruptPowerControl,
                              I2C8_Master_InterruptTransmit,
                              I2C8_Master_InterruptReceive,
                              I2C8_Slave_InterruptTransmit,
                              I2C8_Slave_InterruptReceive,
                              I2C8_InterruptGetDataCount,
                              I2C8_InterruptControl,
                              I2C8_InterruptGetStatus
#endif
};

#endif

#if defined(I2C9) && defined(RTE_I2C9) && RTE_I2C9
/* User needs to provide the implementation for I2C9_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C9_GetFreq(void);

static cmsis_i2c_resource_t I2C9_Resource = {I2C9, I2C9_GetFreq};

#if (defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C9_DmaResource = {RTE_I2C9_Master_DMA_BASE, RTE_I2C9_Master_DMA_CH};

static i2c_master_dma_handle_t I2C9_DmaHandle;
static dma_handle_t I2C9_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c9_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C9_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C9_DmaDriverState  = {
#endif
    &I2C9_Resource,
    &I2C9_DmaResource,
    &I2C9_DmaHandle,
    &I2C9_DmaTxRxHandle,
};

static int32_t I2C9_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C9_PIN_INIT
    RTE_I2C9_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C9_DmaDriverState);
}

static int32_t I2C9_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C9_PIN_DEINIT
    RTE_I2C9_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C9_DmaDriverState);
}

static int32_t I2C9_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C9_DmaDriverState);
}

static int32_t I2C9_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C9_DmaDriverState);
}

static int32_t I2C9_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C9_DmaDriverState);
}

static int32_t I2C9_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C9_DmaDriverState);
}

static int32_t I2C9_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C9_DmaDriverState);
}

static ARM_I2C_STATUS I2C9_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C9_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C9_handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c9_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C9_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C9_InterruptDriverState  = {
#endif
    &I2C9_Resource,
    &I2C9_handle,

};

static int32_t I2C9_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C9_PIN_INIT
    RTE_I2C9_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C9_InterruptDriverState);
}

static int32_t I2C9_InterruptUninitialize(void)
{
#ifdef RTE_I2C9_PIN_DEINIT
    RTE_I2C9_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C9_InterruptDriverState);
}

static int32_t I2C9_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C9_InterruptDriverState);
}

static int32_t I2C9_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C9_InterruptDriverState);
}

static int32_t I2C9_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C9_InterruptDriverState);
}

static int32_t I2C9_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C9_InterruptDriverState);
}

static int32_t I2C9_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C9_InterruptDriverState);
}

static int32_t I2C9_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C9_InterruptDriverState);
}

static int32_t I2C9_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C9_InterruptDriverState);
}

static ARM_I2C_STATUS I2C9_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C9_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C9 = {I2Cx_GetVersion,
                              I2Cx_GetCapabilities,
#if defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN
                              I2C9_Master_DmaInitialize,
                              I2C9_Master_DmaUninitialize,
                              I2C9_Master_DmaPowerControl,
                              I2C9_Master_DmaTransmit,
                              I2C9_Master_DmaReceive,
                              NULL,
                              NULL,
                              I2C9_Master_DmaGetDataCount,
                              I2C9_Master_DmaControl,
                              I2C9_Master_DmaGetStatus
#else
                              I2C9_InterruptInitialize,
                              I2C9_InterruptUninitialize,
                              I2C9_InterruptPowerControl,
                              I2C9_Master_InterruptTransmit,
                              I2C9_Master_InterruptReceive,
                              I2C9_Slave_InterruptTransmit,
                              I2C9_Slave_InterruptReceive,
                              I2C9_InterruptGetDataCount,
                              I2C9_InterruptControl,
                              I2C9_InterruptGetStatus
#endif
};

#endif

#if defined(I2C10) && defined(RTE_I2C10) && RTE_I2C10

/* User needs to provide the implementation for I2C10_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C10_GetFreq(void);

static cmsis_i2c_resource_t I2C10_Resource = {I2C10, I2C10_GetFreq};

#if (defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C10_DmaResource = {RTE_I2C10_Master_DMA_BASE, RTE_I2C10_Master_DMA_CH};

static i2c_master_dma_handle_t I2C10_DmaHandle;
static dma_handle_t I2C10_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c10_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C10_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C10_DmaDriverState = {
#endif
    &I2C10_Resource,
    &I2C10_DmaResource,
    &I2C10_DmaHandle,
    &I2C10_DmaTxRxHandle,
};

static int32_t I2C10_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C10_PIN_INIT
    RTE_I2C10_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C10_DmaDriverState);
}

static int32_t I2C10_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C10_PIN_DEINIT
    RTE_I2C10_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C10_DmaDriverState);
}

static int32_t I2C10_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C10_DmaDriverState);
}

static int32_t I2C10_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C10_DmaDriverState);
}

static int32_t I2C10_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C10_DmaDriverState);
}

static int32_t I2C10_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C10_DmaDriverState);
}

static int32_t I2C10_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C10_DmaDriverState);
}

static ARM_I2C_STATUS I2C10_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C10_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C10_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c10_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C10_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C10_InterruptDriverState = {
#endif
    &I2C10_Resource,
    &I2C10_Handle,
};

static int32_t I2C10_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C10_PIN_INIT
    RTE_I2C10_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C10_InterruptDriverState);
}

static int32_t I2C10_InterruptUninitialize(void)
{
#ifdef RTE_I2C10_PIN_DEINIT
    RTE_I2C10_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C10_InterruptDriverState);
}

static int32_t I2C10_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C10_InterruptDriverState);
}

static int32_t I2C10_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C10_InterruptDriverState);
}

static int32_t I2C10_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C10_InterruptDriverState);
}

static int32_t I2C10_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C10_InterruptDriverState);
}

static int32_t I2C10_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C10_InterruptDriverState);
}

static int32_t I2C10_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C10_InterruptDriverState);
}

static int32_t I2C10_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C10_InterruptDriverState);
}

static ARM_I2C_STATUS I2C10_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C10_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C10 = {I2Cx_GetVersion,
                               I2Cx_GetCapabilities,
#if defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN
                               I2C10_Master_DmaInitialize,
                               I2C10_Master_DmaUninitialize,
                               I2C10_Master_DmaPowerControl,
                               I2C10_Master_DmaTransmit,
                               I2C10_Master_DmaReceive,
                               NULL,
                               NULL,
                               I2C10_Master_DmaGetDataCount,
                               I2C10_Master_DmaControl,
                               I2C10_Master_DmaGetStatus
#else
                               I2C10_InterruptInitialize,
                               I2C10_InterruptUninitialize,
                               I2C10_InterruptPowerControl,
                               I2C10_Master_InterruptTransmit,
                               I2C10_Master_InterruptReceive,
                               I2C10_Slave_InterruptTransmit,
                               I2C10_Slave_InterruptReceive,
                               I2C10_InterruptGetDataCount,
                               I2C10_InterruptControl,
                               I2C10_InterruptGetStatus
#endif
};

#endif

#if defined(I2C11) && defined(RTE_I2C11) && RTE_I2C11

/* User needs to provide the implementation for I2C1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C11_GetFreq(void);

static cmsis_i2c_resource_t I2C11_Resource = {I2C11, I2C11_GetFreq};

#if (defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C11_DmaResource = {RTE_I2C11_Master_DMA_BASE, RTE_I2C11_Master_DMA_CH};

static i2c_master_dma_handle_t I2C11_DmaHandle;
static dma_handle_t I2C11_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c11_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C11_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C11_DmaDriverState = {
#endif
    &I2C11_Resource,
    &I2C11_DmaResource,
    &I2C11_DmaHandle,
    &I2C11_DmaTxRxHandle,
};

static int32_t I2C11_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C11_PIN_INIT
    RTE_I2C11_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C11_DmaDriverState);
}

static int32_t I2C11_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C11_PIN_DEINIT
    RTE_I2C11_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C11_DmaDriverState);
}

static int32_t I2C11_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C11_DmaDriverState);
}

static int32_t I2C11_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C11_DmaDriverState);
}

static int32_t I2C11_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C11_DmaDriverState);
}

static int32_t I2C11_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C11_DmaDriverState);
}

static int32_t I2C11_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C11_DmaDriverState);
}

static ARM_I2C_STATUS I2C11_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C11_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C11_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c11_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C11_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C11_InterruptDriverState = {
#endif
    &I2C11_Resource,
    &I2C11_Handle,
};

static int32_t I2C11_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C11_PIN_INIT
    RTE_I2C11_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C11_InterruptDriverState);
}

static int32_t I2C11_InterruptUninitialize(void)
{
#ifdef RTE_I2C11_PIN_DEINIT
    RTE_I2C11_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C11_InterruptDriverState);
}

static int32_t I2C11_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C11_InterruptDriverState);
}

static int32_t I2C11_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C11_InterruptDriverState);
}

static int32_t I2C11_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C11_InterruptDriverState);
}

static int32_t I2C11_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C11_InterruptDriverState);
}

static int32_t I2C11_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C11_InterruptDriverState);
}

static int32_t I2C11_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C11_InterruptDriverState);
}

static int32_t I2C11_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C11_InterruptDriverState);
}

static ARM_I2C_STATUS I2C11_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C11_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C11 = {I2Cx_GetVersion,
                               I2Cx_GetCapabilities,
#if defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN
                               I2C11_Master_DmaInitialize,
                               I2C11_Master_DmaUninitialize,
                               I2C11_Master_DmaPowerControl,
                               I2C11_Master_DmaTransmit,
                               I2C11_Master_DmaReceive,
                               NULL,
                               NULL,
                               I2C11_Master_DmaGetDataCount,
                               I2C11_Master_DmaControl,
                               I2C11_Master_DmaGetStatus
#else
                               I2C11_InterruptInitialize,
                               I2C11_InterruptUninitialize,
                               I2C11_InterruptPowerControl,
                               I2C11_Master_InterruptTransmit,
                               I2C11_Master_InterruptReceive,
                               I2C11_Slave_InterruptTransmit,
                               I2C11_Slave_InterruptReceive,
                               I2C11_InterruptGetDataCount,
                               I2C11_InterruptControl,
                               I2C11_InterruptGetStatus
#endif
};

#endif

#if defined(I2C12) && defined(RTE_I2C12) && RTE_I2C12

/* User needs to provide the implementation for I2C1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C12_GetFreq(void);

static cmsis_i2c_resource_t I2C12_Resource = {I2C12, I2C12_GetFreq};

#if (defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C12_DmaResource = {RTE_I2C12_Master_DMA_BASE, RTE_I2C12_Master_DMA_CH};

static i2c_master_dma_handle_t I2C12_DmaHandle;
static dma_handle_t I2C12_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c12_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C12_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C12_DmaDriverState = {
#endif
    &I2C12_Resource,
    &I2C12_DmaResource,
    &I2C12_DmaHandle,
    &I2C12_DmaTxRxHandle,
};

static int32_t I2C12_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C12_PIN_INIT
    RTE_I2C12_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C12_DmaDriverState);
}

static int32_t I2C12_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C12_PIN_DEINIT
    RTE_I2C12_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C12_DmaDriverState);
}

static int32_t I2C12_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C12_DmaDriverState);
}

static int32_t I2C12_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C12_DmaDriverState);
}

static int32_t I2C12_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C12_DmaDriverState);
}

static int32_t I2C12_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C12_DmaDriverState);
}

static int32_t I2C12_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C12_DmaDriverState);
}

static ARM_I2C_STATUS I2C12_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C12_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C12_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c12_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C12_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C12_InterruptDriverState = {
#endif
    &I2C12_Resource,
    &I2C12_Handle,
};

static int32_t I2C12_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C12_PIN_INIT
    RTE_I2C12_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C12_InterruptDriverState);
}

static int32_t I2C12_InterruptUninitialize(void)
{
#ifdef RTE_I2C12_PIN_DEINIT
    RTE_I2C12_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C12_InterruptDriverState);
}

static int32_t I2C12_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C12_InterruptDriverState);
}

static int32_t I2C12_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C12_InterruptDriverState);
}

static int32_t I2C12_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C12_InterruptDriverState);
}

static int32_t I2C12_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C12_InterruptDriverState);
}

static int32_t I2C12_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C12_InterruptDriverState);
}

static int32_t I2C12_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C12_InterruptDriverState);
}

static int32_t I2C12_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C12_InterruptDriverState);
}

static ARM_I2C_STATUS I2C12_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C12_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C12 = {I2Cx_GetVersion,
                               I2Cx_GetCapabilities,
#if defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN
                               I2C12_Master_DmaInitialize,
                               I2C12_Master_DmaUninitialize,
                               I2C12_Master_DmaPowerControl,
                               I2C12_Master_DmaTransmit,
                               I2C12_Master_DmaReceive,
                               NULL,
                               NULL,
                               I2C12_Master_DmaGetDataCount,
                               I2C12_Master_DmaControl,
                               I2C12_Master_DmaGetStatus
#else
                               I2C12_InterruptInitialize,
                               I2C12_InterruptUninitialize,
                               I2C12_InterruptPowerControl,
                               I2C12_Master_InterruptTransmit,
                               I2C12_Master_InterruptReceive,
                               I2C12_Slave_InterruptTransmit,
                               I2C12_Slave_InterruptReceive,
                               I2C12_InterruptGetDataCount,
                               I2C12_InterruptControl,
                               I2C12_InterruptGetStatus
#endif
};

#endif

#if defined(I2C13) && defined(RTE_I2C13) && RTE_I2C13

/* User needs to provide the implementation for I2C1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t I2C13_GetFreq(void);

static cmsis_i2c_resource_t I2C13_Resource = {I2C13, I2C13_GetFreq};

#if (defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN)

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_i2c_dma_resource_t I2C13_DmaResource = {RTE_I2C13_Master_DMA_BASE, RTE_I2C13_Master_DMA_CH};

static i2c_master_dma_handle_t I2C13_DmaHandle;
static dma_handle_t I2C13_DmaTxRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c13_dma_driver_state")
static cmsis_i2c_dma_driver_state_t I2C13_DmaDriverState = {
#else
static cmsis_i2c_dma_driver_state_t I2C13_DmaDriverState = {
#endif
    &I2C13_Resource,
    &I2C13_DmaResource,
    &I2C13_DmaHandle,
    &I2C13_DmaTxRxHandle,
};

static int32_t I2C13_Master_DmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C13_PIN_INIT
    RTE_I2C13_PIN_INIT();
#endif
    return I2C_Master_DmaInitialize(cb_event, &I2C13_DmaDriverState);
}

static int32_t I2C13_Master_DmaUninitialize(void)
{
#ifdef RTE_I2C13_PIN_DEINIT
    RTE_I2C13_PIN_DEINIT();
#endif
    return I2C_Master_DmaUninitialize(&I2C13_DmaDriverState);
}

static int32_t I2C13_Master_DmaPowerControl(ARM_POWER_STATE state)
{
    return I2C_Master_DmaPowerControl(state, &I2C13_DmaDriverState);
}

static int32_t I2C13_Master_DmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaTransmit(addr, data, num, xfer_pending, &I2C13_DmaDriverState);
}

static int32_t I2C13_Master_DmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_DmaReceive(addr, data, num, xfer_pending, &I2C13_DmaDriverState);
}

static int32_t I2C13_Master_DmaGetDataCount(void)
{
    return I2C_Master_DmaGetDataCount(&I2C13_DmaDriverState);
}

static int32_t I2C13_Master_DmaControl(uint32_t control, uint32_t arg)
{
    return I2C_Master_DmaControl(control, arg, &I2C13_DmaDriverState);
}

static ARM_I2C_STATUS I2C13_Master_DmaGetStatus(void)
{
    return I2C_Master_DmaGetStatus(&I2C13_DmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t I2C13_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("i2c13_interrupt_driver_state")
static cmsis_i2c_interrupt_driver_state_t I2C13_InterruptDriverState = {
#else
static cmsis_i2c_interrupt_driver_state_t I2C13_InterruptDriverState = {
#endif
    &I2C13_Resource,
    &I2C13_Handle,
};

static int32_t I2C13_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C13_PIN_INIT
    RTE_I2C13_PIN_INIT();
#endif
    return I2C_InterruptInitialize(cb_event, &I2C13_InterruptDriverState);
}

static int32_t I2C13_InterruptUninitialize(void)
{
#ifdef RTE_I2C13_PIN_DEINIT
    RTE_I2C13_PIN_DEINIT();
#endif
    return I2C_InterruptUninitialize(&I2C13_InterruptDriverState);
}

static int32_t I2C13_InterruptPowerControl(ARM_POWER_STATE state)
{
    return I2C_InterruptPowerControl(state, &I2C13_InterruptDriverState);
}

static int32_t I2C13_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &I2C13_InterruptDriverState);
}

static int32_t I2C13_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_Master_InterruptReceive(addr, data, num, xfer_pending, &I2C13_InterruptDriverState);
}

static int32_t I2C13_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptTransmit(data, num, &I2C13_InterruptDriverState);
}

static int32_t I2C13_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    return I2C_Slave_InterruptReceive(data, num, &I2C13_InterruptDriverState);
}

static int32_t I2C13_InterruptGetDataCount(void)
{
    return I2C_InterruptGetDataCount(&I2C13_InterruptDriverState);
}

static int32_t I2C13_InterruptControl(uint32_t control, uint32_t arg)
{
    return I2C_InterruptControl(control, arg, &I2C13_InterruptDriverState);
}

static ARM_I2C_STATUS I2C13_InterruptGetStatus(void)
{
    return I2C_InterruptGetStatus(&I2C13_InterruptDriverState);
}

#endif

ARM_DRIVER_I2C Driver_I2C13 = {I2Cx_GetVersion,
                               I2Cx_GetCapabilities,
#if defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN
                               I2C13_Master_DmaInitialize,
                               I2C13_Master_DmaUninitialize,
                               I2C13_Master_DmaPowerControl,
                               I2C13_Master_DmaTransmit,
                               I2C13_Master_DmaReceive,
                               NULL,
                               NULL,
                               I2C13_Master_DmaGetDataCount,
                               I2C13_Master_DmaControl,
                               I2C13_Master_DmaGetStatus
#else
                               I2C13_InterruptInitialize,
                               I2C13_InterruptUninitialize,
                               I2C13_InterruptPowerControl,
                               I2C13_Master_InterruptTransmit,
                               I2C13_Master_InterruptReceive,
                               I2C13_Slave_InterruptTransmit,
                               I2C13_Slave_InterruptReceive,
                               I2C13_InterruptGetDataCount,
                               I2C13_InterruptControl,
                               I2C13_InterruptGetStatus
#endif
};

#endif
