/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2024-2025 NXP. Not a Contribution.
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

#include "fsl_lpi2c_cmsis.h"

#if ((defined(RTE_I2C0) && RTE_I2C0 && (defined(LPI2C0) || defined(LPI2C_0))) || (defined(RTE_I2C1) && RTE_I2C1 && (defined(LPI2C1) || defined(LPI2C_1))) ||       \
     (defined(RTE_I2C2) && RTE_I2C2 && (defined(LPI2C2) || defined(LPI2C_2))) || (defined(RTE_I2C3) && RTE_I2C3 && (defined(LPI2C3) || defined(LPI2C_3))) ||       \
     (defined(RTE_I2C4) && RTE_I2C4 && (defined(LPI2C4) || defined(LPI2C_4))) || (defined(RTE_I2C5) && RTE_I2C5 && (defined(LPI2C5) || defined(LPI2C_5))) ||       \
     (defined(RTE_I2C6) && RTE_I2C6 && (defined(LPI2C6) || defined(LPI2C_6))) || (defined(RTE_I2C7) && RTE_I2C7 && (defined(LPI2C7) || defined(LPI2C_7))) ||       \
     (defined(RTE_I2C8) && RTE_I2C8 && (defined(LPI2C8) || defined(LPI2C_8))) || (defined(RTE_I2C9) && RTE_I2C9 && (defined(LPI2C9) || defined(LPI2C_9))) ||       \
     (defined(RTE_I2C10) && RTE_I2C10 && (defined(LPI2C10) || defined(LPI2C_10))) || (defined(RTE_I2C11) && RTE_I2C11 && (defined(LPI2C11) || defined(LPI2C_11))) || \
     (defined(RTE_I2C12) && RTE_I2C12 && (defined(LPI2C12) || defined(LPI2C_12))) || (defined(RTE_I2C13) && RTE_I2C13 && (defined(LPI2C13) || defined(LPI2C_13))) || \
     (defined(RTE_I2C14) && RTE_I2C14 && (defined(LPI2C14) || defined(LPI2C_14))) || (defined(RTE_I2C15) && RTE_I2C15 && (defined(LPI2C15) || defined(LPI2C_15))) || \
     (defined(RTE_I2C16) && RTE_I2C16 && (defined(LPI2C16) || defined(LPI2C_16))) || (defined(RTE_I2C17) && RTE_I2C17 && (defined(LPI2C17) || defined(LPI2C_17))) || \
     (defined(RTE_I2C18) && RTE_I2C18 && (defined(LPI2C18) || defined(LPI2C_18))) || (defined(RTE_I2C19) && RTE_I2C19 && (defined(LPI2C19) || defined(LPI2C_19))) || \
     (defined(RTE_I2C20) && RTE_I2C20 && (defined(LPI2C20) || defined(LPI2C_20))))

#define ARM_LPI2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR((2), (6))

/*
 * ARMCC does not support split the data section automatically, so the driver
 * needs to split the data to separate sections explicitly, to reduce codesize.
 */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define ARMCC_SECTION(section_name) __attribute__((section(section_name)))
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpi2c_cmsis"
#endif

typedef const struct _cmsis_lpi2c_resource
{
    LPI2C_Type *base;          /*!< LPI2C peripheral base address.      */
    uint32_t (*GetFreq)(void); /*!< Function to get the clock frequency. */

} cmsis_lpi2c_resource_t;

typedef union _cmsis_i2c_handle
{
    lpi2c_master_handle_t master_handle;
    lpi2c_slave_handle_t slave_handle;
} cmsis_i2c_handle_t;

typedef struct _cmsis_lpi2c_interrupt_driver_state
{
    cmsis_lpi2c_resource_t *resource; /*!< Basic LPI2C resource. */
    cmsis_i2c_handle_t *handle;
    uint8_t *slave_data;              /*!< slave Transfer buffer */
    size_t slave_dataSize;            /*!< slave Transfer size */
    ARM_I2C_SignalEvent_t cb_event;   /*!< call back function */
    uint8_t flags;                    /*!< Control and state flags. */
} cmsis_lpi2c_interrupt_driver_state_t;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
typedef const struct _cmsis_lpi2c_edma_resource
{
    void *txEdmaBase;          /*!< EDMA peripheral base address for Tx.  */
    uint32_t txEdmaChannel;    /*!< EDMA channel for Tx                   */
    uint16_t txDmaRequest;     /*!< Tx EDMA request source.               */

    void *rxEdmaBase;          /*!< EDMA peripheral base address for Rx.  */
    uint32_t rxEdmaChannel;    /*!< EDMA channel for Rx                   */
    uint16_t rxDmaRequest;     /*!< Rx EDMA request source.               */
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    DMAMUX_Type *txDmamuxBase; /*!< DMAMUX peripheral base address for Tx */
    DMAMUX_Type *rxDmamuxBase; /*!< DMAMUX peripheral base address for Rx */
#endif
} cmsis_lpi2c_edma_resource_t;

typedef struct _cmsis_lpi2c_edma_driver_state
{
    cmsis_lpi2c_resource_t *resource;               /*!< lpi2c basic resource.       */
    cmsis_lpi2c_edma_resource_t *edmaResource;      /*!< lpi2c EDMA resource.        */
    lpi2c_master_edma_handle_t *master_edma_handle; /*!< lpi2c EDMA transfer handle. */
    edma_handle_t *edmaTxHandle;                    /*!< EDMA lpi2c Tx handle.       */
    edma_handle_t *edmaRxHandle;                    /*!< EDMA lpi2c Rx handle.       */
    uint8_t flags;                                  /*!< Control and state flags. */
} cmsis_lpi2c_edma_driver_state_t;
#endif                                              /* FSL_FEATURE_SOC_EDMA_COUNT */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static const ARM_DRIVER_VERSION s_lpi2cDriverVersion        = {ARM_I2C_API_VERSION, ARM_LPI2C_DRV_VERSION};
static const ARM_I2C_CAPABILITIES s_lpi2cDriverCapabilities = {
    0, /* Do not support 10-bit addressing.*/
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Returns version information */
static ARM_DRIVER_VERSION LPI2Cx_GetVersion(void)
{
    return s_lpi2cDriverVersion;
}

/* Returns information about capabilities of this driver implementation */
static ARM_I2C_CAPABILITIES LPI2Cx_GetCapabilities(void)
{
    return s_lpi2cDriverCapabilities;
}

#endif

#if ((defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN) || (defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN) ||     \
     (defined(RTE_I2C2_DMA_EN) && RTE_I2C2_DMA_EN) || (defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN) ||     \
     (defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN) || (defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN) ||     \
     (defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN) || (defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN) ||     \
     (defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN) || (defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN) ||     \
     (defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN) || (defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN) || \
     (defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN) || (defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN) || \
     (defined(RTE_I2C14_DMA_EN) && RTE_I2C14_DMA_EN) || (defined(RTE_I2C15_DMA_EN) && RTE_I2C15_DMA_EN) || \
     (defined(RTE_I2C16_DMA_EN) && RTE_I2C16_DMA_EN) || (defined(RTE_I2C17_DMA_EN) && RTE_I2C17_DMA_EN) || \
     (defined(RTE_I2C18_DMA_EN) && RTE_I2C18_DMA_EN) || (defined(RTE_I2C19_DMA_EN) && RTE_I2C19_DMA_EN) || \
     (defined(RTE_I2C20_DMA_EN) && RTE_I2C20_DMA_EN))

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static void KSDK_LPI2C_MASTER_EdmaCallback(LPI2C_Type *base,
                                           lpi2c_master_edma_handle_t *handle,
                                           status_t status,
                                           void *userData)
{
    uint32_t event = 0;

    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        event = ARM_I2C_EVENT_TRANSFER_DONE;
    }

    if (userData != NULL)
    {
        ((ARM_I2C_SignalEvent_t)userData)(event);
    }
}

static int32_t LPI2C_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event, cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    if (0U == (lpi2c->flags & (uint8_t)I2C_FLAG_INIT))
    {
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
        /* TxDMAMUX init */
        DMAMUX_SetSource(lpi2c->edmaResource->txDmamuxBase, lpi2c->edmaResource->txEdmaChannel,
                         (int32_t)lpi2c->edmaResource->txDmaRequest);
        DMAMUX_EnableChannel(lpi2c->edmaResource->txDmamuxBase, lpi2c->edmaResource->txEdmaChannel);
        /* RxDMAMUX init */
        DMAMUX_SetSource(lpi2c->edmaResource->rxDmamuxBase, lpi2c->edmaResource->rxEdmaChannel,
                         (int32_t)lpi2c->edmaResource->rxDmaRequest);
        DMAMUX_EnableChannel(lpi2c->edmaResource->rxDmamuxBase, lpi2c->edmaResource->rxEdmaChannel);
#endif
        /* Create edmaTxHandle */
        EDMA_CreateHandle(lpi2c->edmaTxHandle, lpi2c->edmaResource->txEdmaBase, lpi2c->edmaResource->txEdmaChannel);

        /* Create edmaRxHandle */
        EDMA_CreateHandle(lpi2c->edmaRxHandle, lpi2c->edmaResource->rxEdmaBase, lpi2c->edmaResource->rxEdmaChannel);

#if defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
        EDMA_SetChannelMux(lpi2c->edmaResource->txEdmaBase, lpi2c->edmaResource->txEdmaChannel,
                           (int32_t)lpi2c->edmaResource->txDmaRequest);
        EDMA_SetChannelMux(lpi2c->edmaResource->rxEdmaBase, lpi2c->edmaResource->rxEdmaChannel,
                           (int32_t)lpi2c->edmaResource->rxDmaRequest);
#endif
        /* Create master_edma_handle */
        LPI2C_MasterCreateEDMAHandle(lpi2c->resource->base, lpi2c->master_edma_handle, lpi2c->edmaRxHandle,
                                     lpi2c->edmaTxHandle, KSDK_LPI2C_MASTER_EdmaCallback, (void *)cb_event);

        lpi2c->flags = (uint8_t)I2C_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t LPI2C_Master_EdmaUninitialize(cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    lpi2c->flags = (uint8_t)I2C_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPI2C_Master_EdmaTransmit(
    uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending, cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    int32_t status;
    int32_t ret;
    lpi2c_master_transfer_t masterXfer;

    /* Setup the master transfer */
    masterXfer.slaveAddress   = (uint16_t)addr;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = 0U;
    masterXfer.subaddressSize = 0U;
    masterXfer.data           = (uint8_t *)data;
    masterXfer.dataSize       = num;
    masterXfer.flags          = (uint32_t)kLPI2C_TransferDefaultFlag;

    if (xfer_pending)
    {
        /* Do not transfer stop */
        masterXfer.flags |= (uint32_t)kLPI2C_TransferNoStopFlag;
    }

    /* Send master non-blocking data to slave */
    status = LPI2C_MasterTransferEDMA(lpi2c->resource->base, lpi2c->master_edma_handle, &masterXfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;

        case kStatus_LPI2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;

        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPI2C_Master_EdmaReceive(
    uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending, cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    int32_t status;
    int32_t ret;
    lpi2c_master_transfer_t masterXfer;

    /* Setup the master transfer */
    masterXfer.slaveAddress   = (uint16_t)addr;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = 0U;
    masterXfer.subaddressSize = 0U;
    masterXfer.data           = data;
    masterXfer.dataSize       = num;
    masterXfer.flags          = (uint32_t)kLPI2C_TransferDefaultFlag;

    if (xfer_pending)
    {
        masterXfer.flags |= (uint32_t)kLPI2C_TransferNoStopFlag;
    }

    /* Receive non-blocking data from slave */
    status = LPI2C_MasterTransferEDMA(lpi2c->resource->base, lpi2c->master_edma_handle, &masterXfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_LPI2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPI2C_Master_EdmaGetDataCount(cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    size_t cnt;

    (void)LPI2C_MasterTransferGetCountEDMA(lpi2c->resource->base, lpi2c->master_edma_handle, &cnt);

    return (int32_t)cnt;
}

static int32_t LPI2C_Master_EdmaControl(uint32_t control, uint32_t arg, cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    uint32_t baudRate_Bps;
    int32_t result = ARM_DRIVER_OK;
    switch (control)
    {
        /* Set Own Slave Address */
        case ARM_I2C_OWN_ADDRESS:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;

        /* Set Bus Speed; arg = bus speed */
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

            if (result != ARM_DRIVER_ERROR_UNSUPPORTED)
            {
                LPI2C_MasterSetBaudRate(lpi2c->resource->base, lpi2c->resource->GetFreq(), baudRate_Bps);
                result = ARM_DRIVER_OK;
            }

            break;

        /* Not supported. */
        case ARM_I2C_BUS_CLEAR:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;

        /* Only support aborting data transfer when master transmit in master mode */
        case ARM_I2C_ABORT_TRANSFER:

            if ((lpi2c->resource->base->MDER & 0x3UL) == 0x3UL)
            {
                if (lpi2c->master_edma_handle->transfer.direction == kLPI2C_Write)
                {
                    (void)LPI2C_MasterTransferAbortEDMA(lpi2c->resource->base, lpi2c->master_edma_handle);

                    lpi2c->master_edma_handle->transfer.data     = NULL;
                    lpi2c->master_edma_handle->transfer.dataSize = 0;
                }
            }

            result = ARM_DRIVER_OK;
            break;

        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static int32_t LPI2C_Master_EdmaPowerControl(ARM_POWER_STATE state, cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    lpi2c_master_config_t masterConfig;
    int32_t result = ARM_DRIVER_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpi2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                /* Terminates any pending data transfers */
                (void)LPI2C_Master_EdmaControl(ARM_I2C_ABORT_TRANSFER, 0, lpi2c);

                /* Disables peripheral */
                LPI2C_MasterDeinit(lpi2c->resource->base);
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
                /* Disable DMAMUX channel */
                DMAMUX_DisableChannel(lpi2c->edmaResource->txDmamuxBase, lpi2c->edmaResource->txEdmaChannel);
                DMAMUX_DisableChannel(lpi2c->edmaResource->rxDmamuxBase, lpi2c->edmaResource->rxEdmaChannel);
#endif
                lpi2c->flags = (uint8_t)I2C_FLAG_INIT;
            }
            result = ARM_DRIVER_OK;
            break;

        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;

        case ARM_POWER_FULL:
            if (lpi2c->flags == (uint8_t)I2C_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpi2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            /*
             * masterConfig.debugEnable = false;
             * masterConfig.ignoreAck = false;
             * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
             * masterConfig.baudRate_Hz = 100000U;
             * masterConfig.busIdleTimeout_ns = 0;
             * masterConfig.pinLowTimeout_ns = 0;
             * masterConfig.sdaGlitchFilterWidth_ns = 0;
             * masterConfig.sclGlitchFilterWidth_ns = 0;
             */
            LPI2C_MasterGetDefaultConfig(&masterConfig);

            /* Initialize the LPI2C master peripheral */
            LPI2C_MasterInit(lpi2c->resource->base, &masterConfig, lpi2c->resource->GetFreq());

            lpi2c->flags |= (uint8_t)I2C_FLAG_POWER;

            result = ARM_DRIVER_OK;
            break;

        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static ARM_I2C_STATUS LPI2C_Master_EdmaGetStatus(cmsis_lpi2c_edma_driver_state_t *lpi2c)
{
    ARM_I2C_STATUS stat               = {0};
    uint32_t ksdk_lpi2c_master_status = LPI2C_MasterGetStatusFlags(lpi2c->resource->base);

    stat.busy      = (uint32_t)((ksdk_lpi2c_master_status & (uint32_t)kLPI2C_MasterBusyFlag) != 0U); /* Busy flag */
    stat.mode      = 1;                                                       /* Mode: 0=Slave, 1=Master */
    stat.direction = (uint32_t)lpi2c->master_edma_handle->transfer.direction; /* Direction: 0=Transmitter, 1=Receiver */
    stat.arbitration_lost = (uint32_t)((ksdk_lpi2c_master_status & (uint32_t)kLPI2C_MasterArbitrationLostFlag) !=
                                       0U);                                   /* Master lost arbitration */

    return stat;
}
#endif

#endif

#if ((defined(RTE_I2C0) && RTE_I2C0 && !RTE_I2C0_DMA_EN) || (defined(RTE_I2C1) && RTE_I2C1 && !RTE_I2C1_DMA_EN) || \
     (defined(RTE_I2C2) && RTE_I2C2 && !RTE_I2C2_DMA_EN) || (defined(RTE_I2C3) && RTE_I2C3 && !RTE_I2C3_DMA_EN) || \
     (defined(RTE_I2C4) && RTE_I2C4 && !RTE_I2C4_DMA_EN) || (defined(RTE_I2C5) && RTE_I2C5 && !RTE_I2C5_DMA_EN) || \
     (defined(RTE_I2C6) && RTE_I2C6 && !RTE_I2C6_DMA_EN) || (defined(RTE_I2C7) && RTE_I2C7 && !RTE_I2C7_DMA_EN) || \
     (defined(RTE_I2C8) && RTE_I2C8 && !RTE_I2C8_DMA_EN) || (defined(RTE_I2C9) && RTE_I2C9 && !RTE_I2C9_DMA_EN) || \
     (defined(RTE_I2C10) && RTE_I2C10 && !RTE_I2C10_DMA_EN) ||                                                     \
     (defined(RTE_I2C11) && RTE_I2C11 && !RTE_I2C11_DMA_EN) ||                                                     \
     (defined(RTE_I2C12) && RTE_I2C12 && !RTE_I2C12_DMA_EN) ||                                                     \
     (defined(RTE_I2C13) && RTE_I2C13 && !RTE_I2C13_DMA_EN) ||                                                     \
     (defined(RTE_I2C14) && RTE_I2C14 && !RTE_I2C14_DMA_EN) ||                                                     \
     (defined(RTE_I2C15) && RTE_I2C15 && !RTE_I2C15_DMA_EN) ||                                                     \
     (defined(RTE_I2C16) && RTE_I2C16 && !RTE_I2C16_DMA_EN) ||                                                     \
     (defined(RTE_I2C17) && RTE_I2C17 && !RTE_I2C17_DMA_EN) ||                                                     \
     (defined(RTE_I2C18) && RTE_I2C18 && !RTE_I2C18_DMA_EN) ||                                                     \
     (defined(RTE_I2C19) && RTE_I2C19 && !RTE_I2C19_DMA_EN) || (defined(RTE_I2C20) && RTE_I2C20 && !RTE_I2C20_DMA_EN))

static void KSDK_LPI2C_SLAVE_InterruptCallback(LPI2C_Type *base,
                                               lpi2c_slave_transfer_t *xfer,
                                               void *userData,
                                               cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    uint32_t event = 0;

    switch (xfer->event)
    {
        /*  Transfer done */
        case kLPI2C_SlaveCompletionEvent:
            event = ARM_I2C_EVENT_TRANSFER_DONE;
            break;

        /* Setup the slave receive buffer */
        case kLPI2C_SlaveReceiveEvent:
            xfer->data     = lpi2c->slave_data;
            xfer->dataSize = lpi2c->slave_dataSize;
            break;

        /* Setup the slave transmit buffer */
        case kLPI2C_SlaveTransmitEvent:
            xfer->data     = lpi2c->slave_data;
            xfer->dataSize = lpi2c->slave_dataSize;
            break;

        default:
            event = ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
            break;
    }

    if (userData != NULL)
    {
        ((ARM_I2C_SignalEvent_t)userData)(event);
    }
}

static void KSDK_LPI2C_MASTER_InterruptCallback(LPI2C_Type *base,
                                                lpi2c_master_handle_t *handle,
                                                status_t status,
                                                void *userData)
{
    uint32_t event = 0;

    /* Signal transfer success when received success status. */
    switch (status)
    {
        /*  Transfer done */
        case kStatus_Success:
            event = ARM_I2C_EVENT_TRANSFER_DONE;
            break;

        /* Occurs in master mode when arbitration is lost */
        case kStatus_LPI2C_ArbitrationLost:
            event = ARM_I2C_EVENT_ARBITRATION_LOST;
            break;

        default:
            event = ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
            break;
    }

    if (userData != NULL)
    {
        ((ARM_I2C_SignalEvent_t)userData)(event);
    }
}

static int32_t LPI2C_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event, cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    if (0U == (lpi2c->flags & (uint8_t)I2C_FLAG_INIT))
    {
        lpi2c->cb_event = cb_event; /* Call back function */
        lpi2c->flags    = (uint8_t)I2C_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t LPI2C_InterruptUninitialize(cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    lpi2c->flags = (uint8_t)I2C_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPI2C_Master_InterruptTransmit(
    uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending, cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    int32_t status;
    int32_t ret;
    lpi2c_master_transfer_t masterXfer;

    if (lpi2c->handle->master_handle.state != 0U)
    {
        return ARM_DRIVER_ERROR_BUSY; /* Master is busy */
    }

    /* Create master_handle */
    LPI2C_MasterTransferCreateHandle(lpi2c->resource->base, &(lpi2c->handle->master_handle),
                                     KSDK_LPI2C_MASTER_InterruptCallback, (void *)lpi2c->cb_event);

    /* Setup the master transfer */
    masterXfer.slaveAddress   = (uint16_t)addr;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = 0U;
    masterXfer.subaddressSize = 0U;
    masterXfer.data           = (uint8_t *)data;
    masterXfer.dataSize       = num;
    masterXfer.flags          = (uint32_t)kLPI2C_TransferDefaultFlag;

    if (xfer_pending)
    {
        /* Stop condition will not be generated */
        masterXfer.flags |= (uint32_t)kLPI2C_TransferNoStopFlag;
    }

    /* Send master non-blocking data to slave */
    status = LPI2C_MasterTransferNonBlocking(lpi2c->resource->base, &(lpi2c->handle->master_handle), &masterXfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;

        case kStatus_LPI2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;

        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPI2C_Master_InterruptReceive(
    uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending, cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    int32_t status;
    int32_t ret;
    lpi2c_master_transfer_t masterXfer;

    if (lpi2c->handle->master_handle.state != 0U)
    {
        /* Master is busy */
        return ARM_DRIVER_ERROR_BUSY;
    }

    /* Create master_handle */
    LPI2C_MasterTransferCreateHandle(lpi2c->resource->base, &(lpi2c->handle->master_handle),
                                     KSDK_LPI2C_MASTER_InterruptCallback, (void *)lpi2c->cb_event);

    /* Setup the master transfer */
    masterXfer.slaveAddress   = (uint16_t)addr;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = 0U;
    masterXfer.subaddressSize = 0U;
    masterXfer.data           = data;
    masterXfer.dataSize       = num;
    masterXfer.flags          = (uint32_t)kLPI2C_TransferDefaultFlag;

    if (xfer_pending)
    {
        /* Stop condition will not be generated */
        masterXfer.flags |= (uint32_t)kLPI2C_TransferNoStopFlag;
    }

    /* Receive non-blocking data from slave */
    status = LPI2C_MasterTransferNonBlocking(lpi2c->resource->base, &(lpi2c->handle->master_handle), &masterXfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;

        case kStatus_LPI2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;

        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPI2C_Slave_InterruptTransmit(const uint8_t *data,
                                             uint32_t num,
                                             cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    int32_t status;
    int32_t ret;

    /* Create slave_handle */
    LPI2C_SlaveTransferCreateHandle(lpi2c->resource->base, &(lpi2c->handle->slave_handle),
                                    lpi2c->handle->slave_handle.callback, (void *)lpi2c->cb_event);

    /* Slave send Nonblocking data to master */
    status = LPI2C_SlaveTransferNonBlocking(lpi2c->resource->base, &(lpi2c->handle->slave_handle),
                                            (uint32_t)kLPI2C_SlaveCompletionEvent);

    lpi2c->slave_data                            = (uint8_t *)data; /*!< slave Transfer buffer */
    lpi2c->slave_dataSize                        = num;             /*!< slave Transfer data size */
    lpi2c->handle->slave_handle.transferredCount = 0U;              /*!< slave Transfered data count */

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;

        case kStatus_LPI2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;

        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPI2C_Slave_InterruptReceive(uint8_t *data, uint32_t num, cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    int32_t status;
    int32_t ret;

    /* Create slave_handle */
    LPI2C_SlaveTransferCreateHandle(lpi2c->resource->base, &(lpi2c->handle->slave_handle),
                                    lpi2c->handle->slave_handle.callback, (void *)lpi2c->cb_event);

    /* Slave receive Nonblocking data from master */
    status = LPI2C_SlaveTransferNonBlocking(lpi2c->resource->base, &(lpi2c->handle->slave_handle),
                                            (uint32_t)kLPI2C_SlaveCompletionEvent);

    lpi2c->slave_data                            = data; /*!< slave Transfer buffer */
    lpi2c->slave_dataSize                        = num;  /*!< slave Transfer data size */
    lpi2c->handle->slave_handle.transferredCount = 0U;   /*!< slave Transfered data count */

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;

        case kStatus_LPI2C_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;

        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPI2C_InterruptGetDataCount(cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    size_t cnt;

    if ((lpi2c->resource->base->SIER & (uint32_t)kLPI2C_SlaveIrqFlags) == (uint32_t)kLPI2C_SlaveIrqFlags)
    {
        /* In slave mode */
        (void)LPI2C_SlaveTransferGetCount(lpi2c->resource->base, &lpi2c->handle->slave_handle, &cnt);
    }
    else
    {
        /* In master mode */
        (void)LPI2C_MasterTransferGetCount(lpi2c->resource->base, &lpi2c->handle->master_handle, &cnt);
    }
    return (int32_t)cnt;
}

static int32_t LPI2C_InterruptControl(uint32_t control, uint32_t arg, cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    uint32_t baudRate_Bps;
    int32_t result = ARM_DRIVER_OK;

    switch (control)
    {
        case ARM_I2C_OWN_ADDRESS:
            /* Set Own Slave Address */
            lpi2c->resource->base->SAMR = (arg << 1U);
            break;

        case ARM_I2C_BUS_SPEED:
            /* Set Bus Speed */
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
                LPI2C_MasterSetBaudRate(lpi2c->resource->base, lpi2c->resource->GetFreq(), baudRate_Bps);
            }

            break;

        /* Not supported. */
        case ARM_I2C_BUS_CLEAR:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;

        /* Only support aborting data transfer when master transmit(in master mode) or slave receive(in slave mode) */
        case ARM_I2C_ABORT_TRANSFER:
            /* Abort data transfer when slave receive(in slave mode) */
            if ((lpi2c->resource->base->SIER & (uint32_t)kLPI2C_SlaveIrqFlags) == (uint32_t)kLPI2C_SlaveIrqFlags)
            {
                /* Disable slave mode */
                lpi2c->resource->base->SCR = 0U;

                /* Diable slave interrupt */
                LPI2C_SlaveTransferAbort(lpi2c->resource->base, &(lpi2c->handle->slave_handle));

                /* Enable slave mode */
                lpi2c->resource->base->SCR = 0x31U;
            }

            /* Bort data transfer when master transmit abort(in master mode) */
            if ((lpi2c->resource->base->MIER & (uint32_t)kLPI2C_MasterIrqFlags) == (uint32_t)kLPI2C_MasterIrqFlags)
            {
                /* Disable master interrupt and send stop */
                LPI2C_MasterTransferAbort(lpi2c->resource->base, &(lpi2c->handle->master_handle));

                lpi2c->handle->master_handle.remainingBytes    = 0;
                lpi2c->handle->master_handle.transfer.data     = NULL;
                lpi2c->handle->master_handle.transfer.dataSize = 0;
            }

            result = ARM_DRIVER_OK;
            break;

        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static int32_t LPI2C_InterruptPowerControl(ARM_POWER_STATE state, cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    int32_t result = ARM_DRIVER_OK;
    lpi2c_slave_config_t slaveConfig;
    lpi2c_master_config_t masterConfig;
    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpi2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                /* Terminates any pending data transfers */
                (void)LPI2C_InterruptControl(ARM_I2C_ABORT_TRANSFER, 0, lpi2c);

                /* Disables peripheral */
                LPI2C_MasterDeinit(lpi2c->resource->base);
                lpi2c->flags = (uint8_t)I2C_FLAG_INIT;
            }
            break;

        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;

        case ARM_POWER_FULL:

            if (lpi2c->flags == (uint8_t)I2C_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpi2c->flags & (uint8_t)I2C_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            /*
             * slaveConfig.address0 = 0U;
             * slaveConfig.address1 = 0U;
             * slaveConfig.addressMatchMode = kLPI2C_MatchAddress0;
             * slaveConfig.filterDozeEnable = true;
             * slaveConfig.filterEnable = true;
             * slaveConfig.enableGeneralCall = false;
             * slaveConfig.ignoreAck = false;
             * slaveConfig.enableReceivedAddressRead = false;
             * slaveConfig.sdaGlitchFilterWidth_ns = 0;
             * slaveConfig.sclGlitchFilterWidth_ns = 0;
             * slaveConfig.dataValidDelay_ns = 0;
             * slaveConfig.clockHoldTime_ns = 0;
             */
            LPI2C_SlaveGetDefaultConfig(&slaveConfig);

            /* Initialize the LPI2C slave peripheral */
            LPI2C_SlaveInit(lpi2c->resource->base, &slaveConfig, lpi2c->resource->GetFreq());

            /*
             * masterConfig.debugEnable = false;
             * masterConfig.ignoreAck = false;
             * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
             * masterConfig.baudRate_Hz = 100000U;
             * masterConfig.busIdleTimeout_ns = 0;
             * masterConfig.pinLowTimeout_ns = 0;
             * masterConfig.sdaGlitchFilterWidth_ns = 0;
             * masterConfig.sclGlitchFilterWidth_ns = 0;
             */
            LPI2C_MasterGetDefaultConfig(&masterConfig);

            /* Initialize the LPI2C master peripheral */
            LPI2C_MasterInit(lpi2c->resource->base, &masterConfig, lpi2c->resource->GetFreq());

            lpi2c->flags |= (uint8_t)I2C_FLAG_POWER;

            break;

        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static ARM_I2C_STATUS LPI2C_InterruptGetStatus(cmsis_lpi2c_interrupt_driver_state_t *lpi2c)
{
    ARM_I2C_STATUS stat               = {0};
    uint32_t ksdk_lpi2c_master_status = LPI2C_MasterGetStatusFlags(lpi2c->resource->base);
    uint32_t ksdk_lpi2c_slave_status  = LPI2C_SlaveGetStatusFlags(lpi2c->resource->base);

    /* Busy flag */
    stat.busy = (uint32_t)(((ksdk_lpi2c_master_status & (uint32_t)kLPI2C_MasterBusyFlag) != 0U) ||
                           ((ksdk_lpi2c_slave_status & (uint32_t)kLPI2C_SlaveBusyFlag) != 0U));

    /* Mode: 0=Slave, 1=Master */
    if ((lpi2c->resource->base->SIER & (uint32_t)kLPI2C_SlaveIrqFlags) == (uint32_t)kLPI2C_SlaveIrqFlags)
    {
        stat.mode = 0UL;
    }
    else
    {
        stat.mode = 1UL;
    }

    /* Direction: 0=Transmitter, 1=Receiver */
    stat.direction = (uint32_t)lpi2c->handle->master_handle.transfer.direction;

    /* Master lost arbitration */
    stat.arbitration_lost = (uint32_t)((ksdk_lpi2c_master_status & (uint32_t)kLPI2C_MasterArbitrationLostFlag) != 0U);

    return stat;
}

#endif

#if (defined(LPI2C0) || defined(LPI2C_0)) && defined(RTE_I2C0) && RTE_I2C0
/* User needs to provide the implementation for LPI2C0_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C0_GetFreq(void);

#if defined(LPI2C0)
static cmsis_lpi2c_resource_t LPI2C0_Resource = {LPI2C0, LPI2C0_GetFreq};
#elif defined(LPI2C_0)
static cmsis_lpi2c_resource_t LPI2C0_Resource = {LPI2C_0, LPI2C0_GetFreq};
#endif

#if defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C0_EdmaResource = {
    RTE_I2C0_DMA_TX_DMA_BASE,    RTE_I2C0_DMA_TX_CH,          (uint16_t)RTE_I2C0_DMA_TX_PERI_SEL,
    RTE_I2C0_DMA_RX_DMA_BASE,    RTE_I2C0_DMA_RX_CH,          (uint16_t)RTE_I2C0_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C0_DMA_TX_DMAMUX_BASE, RTE_I2C0_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C0_EdmaHandle);
static edma_handle_t LPI2C0_EdmaTxHandle;
static edma_handle_t LPI2C0_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c0_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C0_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C0_EdmaDriverState = {
#endif
    &LPI2C0_Resource, &LPI2C0_EdmaResource, &LPI2C0_EdmaHandle, &LPI2C0_EdmaTxHandle, &LPI2C0_EdmaRxHandle,
};

static int32_t LPI2C0_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C0_PIN_INIT
    RTE_I2C0_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C0_EdmaDriverState);
}

static int32_t LPI2C0_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C0_PIN_DEINIT
    RTE_I2C0_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C0_EdmaDriverState);
}

static int32_t LPI2C0_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C0_EdmaDriverState);
}

static int32_t LPI2C0_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C0_EdmaDriverState);
}

static int32_t LPI2C0_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C0_EdmaDriverState);
}

static int32_t LPI2C0_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C0_EdmaDriverState);
}

static int32_t LPI2C0_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C0_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C0_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C0_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C0_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c0_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C0_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C0_InterruptDriverState = {
#endif
    &LPI2C0_Resource,
    &LPI2C0_Handle,
};

static void KSDK_LPI2C0_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C0_PIN_INIT
    RTE_I2C0_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_InterruptUninitialize(void)
{
#ifdef RTE_I2C0_PIN_DEINIT
    RTE_I2C0_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C0_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C0_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C0_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C0_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C0_InterruptDriverState);
}

static int32_t LPI2C0_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C0_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C0_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C0_InterruptDriverState);
}

#endif /* RTE_I2C0_DMA_EN */

ARM_DRIVER_I2C Driver_I2C0 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C0_DMA_EN) && RTE_I2C0_DMA_EN
                              LPI2C0_Master_EdmaInitialize,
                              LPI2C0_Master_EdmaUninitialize,
                              LPI2C0_Master_EdmaPowerControl,
                              LPI2C0_Master_EdmaTransmit,
                              LPI2C0_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C0_Master_EdmaGetDataCount,
                              LPI2C0_Master_EdmaControl,
                              LPI2C0_Master_EdmaGetStatus
#else
                              LPI2C0_InterruptInitialize,
                              LPI2C0_InterruptUninitialize,
                              LPI2C0_InterruptPowerControl,
                              LPI2C0_Master_InterruptTransmit,
                              LPI2C0_Master_InterruptReceive,
                              LPI2C0_Slave_InterruptTransmit,
                              LPI2C0_Slave_InterruptReceive,
                              LPI2C0_InterruptGetDataCount,
                              LPI2C0_InterruptControl,
                              LPI2C0_InterruptGetStatus
#endif /* RTE_I2C0_DMA_EN */
};

#endif /* LPI2C0 */

#if (defined(LPI2C1) || defined(LPI2C_1)) && defined(RTE_I2C1) && RTE_I2C1
/* User needs to provide the implementation for LPI2C1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C1_GetFreq(void);

#if defined(LPI2C1)
static cmsis_lpi2c_resource_t LPI2C1_Resource = {LPI2C1, LPI2C1_GetFreq};
#elif defined(LPI2C_1)
static cmsis_lpi2c_resource_t LPI2C1_Resource = {LPI2C_1, LPI2C1_GetFreq};
#endif

#if defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C1_EdmaResource = {
    RTE_I2C1_DMA_TX_DMA_BASE,    RTE_I2C1_DMA_TX_CH,          (uint16_t)RTE_I2C1_DMA_TX_PERI_SEL,
    RTE_I2C1_DMA_RX_DMA_BASE,    RTE_I2C1_DMA_RX_CH,          (uint16_t)RTE_I2C1_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C1_DMA_TX_DMAMUX_BASE, RTE_I2C1_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C1_EdmaHandle);
static edma_handle_t LPI2C1_EdmaTxHandle;
static edma_handle_t LPI2C1_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c1_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C1_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C1_EdmaDriverState = {
#endif
    &LPI2C1_Resource, &LPI2C1_EdmaResource, &LPI2C1_EdmaHandle, &LPI2C1_EdmaTxHandle, &LPI2C1_EdmaRxHandle,
};

static int32_t LPI2C1_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C1_PIN_INIT
    RTE_I2C1_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C1_EdmaDriverState);
}

static int32_t LPI2C1_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C1_PIN_DEINIT
    RTE_I2C1_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C1_EdmaDriverState);
}

static int32_t LPI2C1_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C1_EdmaDriverState);
}

static int32_t LPI2C1_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C1_EdmaDriverState);
}

static int32_t LPI2C1_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C1_EdmaDriverState);
}

static int32_t LPI2C1_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C1_EdmaDriverState);
}

static int32_t LPI2C1_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C1_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C1_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C1_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C1_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c1_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C1_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C1_InterruptDriverState = {
#endif
    &LPI2C1_Resource,
    &LPI2C1_Handle,
};

static void KSDK_LPI2C1_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C1_PIN_INIT
    RTE_I2C1_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_InterruptUninitialize(void)
{
#ifdef RTE_I2C1_PIN_DEINIT
    RTE_I2C1_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C1_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C1_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C1_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C1_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C1_InterruptDriverState);
}

static int32_t LPI2C1_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C1_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C1_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C1_InterruptDriverState);
}

#endif /* RTE_I2C1_DMA_EN */

ARM_DRIVER_I2C Driver_I2C1 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C1_DMA_EN) && RTE_I2C1_DMA_EN
                              LPI2C1_Master_EdmaInitialize,
                              LPI2C1_Master_EdmaUninitialize,
                              LPI2C1_Master_EdmaPowerControl,
                              LPI2C1_Master_EdmaTransmit,
                              LPI2C1_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C1_Master_EdmaGetDataCount,
                              LPI2C1_Master_EdmaControl,
                              LPI2C1_Master_EdmaGetStatus
#else
                              LPI2C1_InterruptInitialize,
                              LPI2C1_InterruptUninitialize,
                              LPI2C1_InterruptPowerControl,
                              LPI2C1_Master_InterruptTransmit,
                              LPI2C1_Master_InterruptReceive,
                              LPI2C1_Slave_InterruptTransmit,
                              LPI2C1_Slave_InterruptReceive,
                              LPI2C1_InterruptGetDataCount,
                              LPI2C1_InterruptControl,
                              LPI2C1_InterruptGetStatus
#endif /* RTE_I2C1_DMA_EN */
};

#endif /* LPI2C1 */

#if (defined(LPI2C2) || defined(LPI2C_2)) && defined(RTE_I2C2) && RTE_I2C2
/* User needs to provide the implementation for LPI2C2_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C2_GetFreq(void);

#if defined(LPI2C2)
static cmsis_lpi2c_resource_t LPI2C2_Resource = {LPI2C2, LPI2C2_GetFreq};
#elif defined(LPI2C_2)
static cmsis_lpi2c_resource_t LPI2C2_Resource = {LPI2C_2, LPI2C2_GetFreq};
#endif

#if defined(RTE_I2C2_DMA_EN) && RTE_I2C2_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C2_EdmaResource = {
    RTE_I2C2_DMA_TX_DMA_BASE,    RTE_I2C2_DMA_TX_CH,          (uint16_t)RTE_I2C2_DMA_TX_PERI_SEL,
    RTE_I2C2_DMA_RX_DMA_BASE,    RTE_I2C2_DMA_RX_CH,          (uint16_t)RTE_I2C2_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C2_DMA_TX_DMAMUX_BASE, RTE_I2C2_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C2_EdmaHandle);
static edma_handle_t LPI2C2_EdmaTxHandle;
static edma_handle_t LPI2C2_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c2_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C2_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C2_EdmaDriverState = {
#endif
    &LPI2C2_Resource, &LPI2C2_EdmaResource, &LPI2C2_EdmaHandle, &LPI2C2_EdmaTxHandle, &LPI2C2_EdmaRxHandle,
};

static int32_t LPI2C2_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C2_PIN_INIT
    RTE_I2C2_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C2_EdmaDriverState);
}

static int32_t LPI2C2_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C2_PIN_DEINIT
    RTE_I2C2_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C2_EdmaDriverState);
}

static int32_t LPI2C2_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C2_EdmaDriverState);
}

static int32_t LPI2C2_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C2_EdmaDriverState);
}

static int32_t LPI2C2_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C2_EdmaDriverState);
}

static int32_t LPI2C2_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C2_EdmaDriverState);
}

static int32_t LPI2C2_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C2_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C2_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C2_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C2_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c2_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C2_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C2_InterruptDriverState = {
#endif
    &LPI2C2_Resource,
    &LPI2C2_Handle,
};

static void KSDK_LPI2C2_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C2_PIN_INIT
    RTE_I2C2_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_InterruptUninitialize(void)
{
#ifdef RTE_I2C2_PIN_DEINIT
    RTE_I2C2_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C2_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C2_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C2_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C2_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C2_InterruptDriverState);
}

static int32_t LPI2C2_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C2_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C2_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C2_InterruptDriverState);
}

#endif /* RTE_I2C2_DMA_EN */

ARM_DRIVER_I2C Driver_I2C2 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C2_DMA_EN) && RTE_I2C2_DMA_EN
                              LPI2C2_Master_EdmaInitialize,
                              LPI2C2_Master_EdmaUninitialize,
                              LPI2C2_Master_EdmaPowerControl,
                              LPI2C2_Master_EdmaTransmit,
                              LPI2C2_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C2_Master_EdmaGetDataCount,
                              LPI2C2_Master_EdmaControl,
                              LPI2C2_Master_EdmaGetStatus
#else
                              LPI2C2_InterruptInitialize,
                              LPI2C2_InterruptUninitialize,
                              LPI2C2_InterruptPowerControl,
                              LPI2C2_Master_InterruptTransmit,
                              LPI2C2_Master_InterruptReceive,
                              LPI2C2_Slave_InterruptTransmit,
                              LPI2C2_Slave_InterruptReceive,
                              LPI2C2_InterruptGetDataCount,
                              LPI2C2_InterruptControl,
                              LPI2C2_InterruptGetStatus
#endif /* RTE_I2C2_DMA_EN */
};

#endif /* LPI2C2 */

#if (defined(LPI2C3) || defined(LPI2C_3)) && defined(RTE_I2C3) && RTE_I2C3
/* User needs to provide the implementation for LPI2C3_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C3_GetFreq(void);

#if defined(LPI2C3)
static cmsis_lpi2c_resource_t LPI2C3_Resource = {LPI2C3, LPI2C3_GetFreq};
#elif defined(LPI2C_3)
static cmsis_lpi2c_resource_t LPI2C3_Resource = {LPI2C_3, LPI2C3_GetFreq};
#endif

#if defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C3_EdmaResource = {
    RTE_I2C3_DMA_TX_DMA_BASE,    RTE_I2C3_DMA_TX_CH,          (uint16_t)RTE_I2C3_DMA_TX_PERI_SEL,
    RTE_I2C3_DMA_RX_DMA_BASE,    RTE_I2C3_DMA_RX_CH,          (uint16_t)RTE_I2C3_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C3_DMA_TX_DMAMUX_BASE, RTE_I2C3_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C3_EdmaHandle);
static edma_handle_t LPI2C3_EdmaTxHandle;
static edma_handle_t LPI2C3_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c3_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C3_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C3_EdmaDriverState = {
#endif
    &LPI2C3_Resource, &LPI2C3_EdmaResource, &LPI2C3_EdmaHandle, &LPI2C3_EdmaTxHandle, &LPI2C3_EdmaRxHandle,
};

static int32_t LPI2C3_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C3_PIN_INIT
    RTE_I2C3_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C3_EdmaDriverState);
}

static int32_t LPI2C3_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C3_PIN_DEINIT
    RTE_I2C3_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C3_EdmaDriverState);
}

static int32_t LPI2C3_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C3_EdmaDriverState);
}

static int32_t LPI2C3_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C3_EdmaDriverState);
}

static int32_t LPI2C3_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C3_EdmaDriverState);
}

static int32_t LPI2C3_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C3_EdmaDriverState);
}

static int32_t LPI2C3_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C3_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C3_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C3_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C3_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c3_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C3_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C3_InterruptDriverState = {
#endif
    &LPI2C3_Resource,
    &LPI2C3_Handle,
};

static void KSDK_LPI2C3_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C3_PIN_INIT
    RTE_I2C3_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_InterruptUninitialize(void)
{
#ifdef RTE_I2C3_PIN_DEINIT
    RTE_I2C3_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C3_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C3_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C3_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C3_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C3_InterruptDriverState);
}

static int32_t LPI2C3_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C3_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C3_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C3_InterruptDriverState);
}

#endif /* RTE_I2C3_DMA_EN */

ARM_DRIVER_I2C Driver_I2C3 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C3_DMA_EN) && RTE_I2C3_DMA_EN
                              LPI2C3_Master_EdmaInitialize,
                              LPI2C3_Master_EdmaUninitialize,
                              LPI2C3_Master_EdmaPowerControl,
                              LPI2C3_Master_EdmaTransmit,
                              LPI2C3_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C3_Master_EdmaGetDataCount,
                              LPI2C3_Master_EdmaControl,
                              LPI2C3_Master_EdmaGetStatus
#else
                              LPI2C3_InterruptInitialize,
                              LPI2C3_InterruptUninitialize,
                              LPI2C3_InterruptPowerControl,
                              LPI2C3_Master_InterruptTransmit,
                              LPI2C3_Master_InterruptReceive,
                              LPI2C3_Slave_InterruptTransmit,
                              LPI2C3_Slave_InterruptReceive,
                              LPI2C3_InterruptGetDataCount,
                              LPI2C3_InterruptControl,
                              LPI2C3_InterruptGetStatus
#endif /* RTE_I2C3_DMA_EN */
};

#endif /* LPI2C3 */

#if (defined(LPI2C4) || defined(LPI2C_4)) && defined(RTE_I2C4) && RTE_I2C4
/* User needs to provide the implementation for LPI2C4_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C4_GetFreq(void);

#if defined(LPI2C4)
static cmsis_lpi2c_resource_t LPI2C4_Resource = {LPI2C4, LPI2C4_GetFreq};
#elif defined(LPI2C_4)
static cmsis_lpi2c_resource_t LPI2C4_Resource = {LPI2C_4, LPI2C4_GetFreq};
#endif

#if defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C4_EdmaResource = {
    RTE_I2C4_DMA_TX_DMA_BASE,    RTE_I2C4_DMA_TX_CH,          (uint16_t)RTE_I2C4_DMA_TX_PERI_SEL,
    RTE_I2C4_DMA_RX_DMA_BASE,    RTE_I2C4_DMA_RX_CH,          (uint16_t)RTE_I2C4_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C4_DMA_TX_DMAMUX_BASE, RTE_I2C4_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C4_EdmaHandle);
static edma_handle_t LPI2C4_EdmaTxHandle;
static edma_handle_t LPI2C4_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c4_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C4_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C4_EdmaDriverState = {
#endif
    &LPI2C4_Resource, &LPI2C4_EdmaResource, &LPI2C4_EdmaHandle, &LPI2C4_EdmaTxHandle, &LPI2C4_EdmaRxHandle,
};

static int32_t LPI2C4_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C4_PIN_INIT
    RTE_I2C4_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C4_EdmaDriverState);
}

static int32_t LPI2C4_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C4_PIN_DEINIT
    RTE_I2C4_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C4_EdmaDriverState);
}

static int32_t LPI2C4_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C4_EdmaDriverState);
}

static int32_t LPI2C4_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C4_EdmaDriverState);
}

static int32_t LPI2C4_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C4_EdmaDriverState);
}

static int32_t LPI2C4_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C4_EdmaDriverState);
}

static int32_t LPI2C4_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C4_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C4_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C4_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C4_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c4_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C4_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C4_InterruptDriverState = {
#endif
    &LPI2C4_Resource,
    &LPI2C4_Handle,
};

static void KSDK_LPI2C4_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C4_PIN_INIT
    RTE_I2C4_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_InterruptUninitialize(void)
{
#ifdef RTE_I2C4_PIN_DEINIT
    RTE_I2C4_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C4_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C4_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C4_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C4_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C4_InterruptDriverState);
}

static int32_t LPI2C4_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C4_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C4_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C4_InterruptDriverState);
}

#endif /* RTE_I2C4_DMA_EN */

ARM_DRIVER_I2C Driver_I2C4 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C4_DMA_EN) && RTE_I2C4_DMA_EN
                              LPI2C4_Master_EdmaInitialize,
                              LPI2C4_Master_EdmaUninitialize,
                              LPI2C4_Master_EdmaPowerControl,
                              LPI2C4_Master_EdmaTransmit,
                              LPI2C4_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C4_Master_EdmaGetDataCount,
                              LPI2C4_Master_EdmaControl,
                              LPI2C4_Master_EdmaGetStatus
#else
                              LPI2C4_InterruptInitialize,
                              LPI2C4_InterruptUninitialize,
                              LPI2C4_InterruptPowerControl,
                              LPI2C4_Master_InterruptTransmit,
                              LPI2C4_Master_InterruptReceive,
                              LPI2C4_Slave_InterruptTransmit,
                              LPI2C4_Slave_InterruptReceive,
                              LPI2C4_InterruptGetDataCount,
                              LPI2C4_InterruptControl,
                              LPI2C4_InterruptGetStatus
#endif /* RTE_I2C4_DMA_EN */
};

#endif /* LPI2C4 */

#if (defined(LPI2C5) || defined(LPI2C_5)) && defined(RTE_I2C5) && RTE_I2C5
/* User needs to provide the implementation for LPI2C5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C5_GetFreq(void);

#if defined(LPI2C5)
static cmsis_lpi2c_resource_t LPI2C5_Resource = {LPI2C5, LPI2C5_GetFreq};
#elif defined(LPI2C_5)
static cmsis_lpi2c_resource_t LPI2C5_Resource = {LPI2C_5, LPI2C5_GetFreq};
#endif

#if defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C5_EdmaResource = {
    RTE_I2C5_DMA_TX_DMA_BASE,    RTE_I2C5_DMA_TX_CH,          (uint16_t)RTE_I2C5_DMA_TX_PERI_SEL,
    RTE_I2C5_DMA_RX_DMA_BASE,    RTE_I2C5_DMA_RX_CH,          (uint16_t)RTE_I2C5_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C5_DMA_TX_DMAMUX_BASE, RTE_I2C5_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C5_EdmaHandle);
static edma_handle_t LPI2C5_EdmaTxHandle;
static edma_handle_t LPI2C5_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c5_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C5_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C5_EdmaDriverState = {
#endif
    &LPI2C5_Resource, &LPI2C5_EdmaResource, &LPI2C5_EdmaHandle, &LPI2C5_EdmaTxHandle, &LPI2C5_EdmaRxHandle,
};

static int32_t LPI2C5_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C5_PIN_INIT
    RTE_I2C5_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C5_EdmaDriverState);
}

static int32_t LPI2C5_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C5_PIN_DEINIT
    RTE_I2C5_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C5_EdmaDriverState);
}

static int32_t LPI2C5_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C5_EdmaDriverState);
}

static int32_t LPI2C5_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C5_EdmaDriverState);
}

static int32_t LPI2C5_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C5_EdmaDriverState);
}

static int32_t LPI2C5_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C5_EdmaDriverState);
}

static int32_t LPI2C5_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C5_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C5_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C5_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C5_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c5_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C5_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C5_InterruptDriverState = {
#endif
    &LPI2C5_Resource,
    &LPI2C5_Handle,
};

static void KSDK_LPI2C5_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C5_PIN_INIT
    RTE_I2C5_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_InterruptUninitialize(void)
{
#ifdef RTE_I2C5_PIN_DEINIT
    RTE_I2C5_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C5_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C5_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C5_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C5_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C5_InterruptDriverState);
}

static int32_t LPI2C5_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C5_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C5_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C5_InterruptDriverState);
}

#endif /* RTE_I2C5_DMA_EN */

ARM_DRIVER_I2C Driver_I2C5 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C5_DMA_EN) && RTE_I2C5_DMA_EN
                              LPI2C5_Master_EdmaInitialize,
                              LPI2C5_Master_EdmaUninitialize,
                              LPI2C5_Master_EdmaPowerControl,
                              LPI2C5_Master_EdmaTransmit,
                              LPI2C5_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C5_Master_EdmaGetDataCount,
                              LPI2C5_Master_EdmaControl,
                              LPI2C5_Master_EdmaGetStatus
#else
                              LPI2C5_InterruptInitialize,
                              LPI2C5_InterruptUninitialize,
                              LPI2C5_InterruptPowerControl,
                              LPI2C5_Master_InterruptTransmit,
                              LPI2C5_Master_InterruptReceive,
                              LPI2C5_Slave_InterruptTransmit,
                              LPI2C5_Slave_InterruptReceive,
                              LPI2C5_InterruptGetDataCount,
                              LPI2C5_InterruptControl,
                              LPI2C5_InterruptGetStatus
#endif /* RTE_I2C5_DMA_EN */
};

#endif /* LPI2C5 */

#if (defined(LPI2C6) || defined(LPI2C_6)) && defined(RTE_I2C6) && RTE_I2C6
/* User needs to provide the implementation for LPI2C6_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C6_GetFreq(void);

#if defined(LPI2C6)
static cmsis_lpi2c_resource_t LPI2C6_Resource = {LPI2C6, LPI2C6_GetFreq};
#elif defined(LPI2C_6)
static cmsis_lpi2c_resource_t LPI2C6_Resource = {LPI2C_6, LPI2C6_GetFreq};
#endif

#if defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C6_EdmaResource = {
    RTE_I2C6_DMA_TX_DMA_BASE,    RTE_I2C6_DMA_TX_CH,          (uint16_t)RTE_I2C6_DMA_TX_PERI_SEL,
    RTE_I2C6_DMA_RX_DMA_BASE,    RTE_I2C6_DMA_RX_CH,          (uint16_t)RTE_I2C6_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C6_DMA_TX_DMAMUX_BASE, RTE_I2C6_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C6_EdmaHandle);
static edma_handle_t LPI2C6_EdmaTxHandle;
static edma_handle_t LPI2C6_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c6_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C6_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C6_EdmaDriverState = {
#endif
    &LPI2C6_Resource, &LPI2C6_EdmaResource, &LPI2C6_EdmaHandle, &LPI2C6_EdmaTxHandle, &LPI2C6_EdmaRxHandle,
};

static int32_t LPI2C6_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C6_PIN_INIT
    RTE_I2C6_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C6_EdmaDriverState);
}

static int32_t LPI2C6_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C6_PIN_DEINIT
    RTE_I2C6_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C6_EdmaDriverState);
}

static int32_t LPI2C6_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C6_EdmaDriverState);
}

static int32_t LPI2C6_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C6_EdmaDriverState);
}

static int32_t LPI2C6_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C6_EdmaDriverState);
}

static int32_t LPI2C6_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C6_EdmaDriverState);
}

static int32_t LPI2C6_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C6_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C6_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C6_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C6_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c6_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C6_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C6_InterruptDriverState = {
#endif
    &LPI2C6_Resource,
    &LPI2C6_Handle,
};

static void KSDK_LPI2C6_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C6_PIN_INIT
    RTE_I2C6_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_InterruptUninitialize(void)
{
#ifdef RTE_I2C6_PIN_DEINIT
    RTE_I2C6_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C6_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C6_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C6_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C6_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C6_InterruptDriverState);
}

static int32_t LPI2C6_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C6_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C6_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C6_InterruptDriverState);
}

#endif /* RTE_I2C6_DMA_EN */

ARM_DRIVER_I2C Driver_I2C6 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C6_DMA_EN) && RTE_I2C6_DMA_EN
                              LPI2C6_Master_EdmaInitialize,
                              LPI2C6_Master_EdmaUninitialize,
                              LPI2C6_Master_EdmaPowerControl,
                              LPI2C6_Master_EdmaTransmit,
                              LPI2C6_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C6_Master_EdmaGetDataCount,
                              LPI2C6_Master_EdmaControl,
                              LPI2C6_Master_EdmaGetStatus
#else
                              LPI2C6_InterruptInitialize,
                              LPI2C6_InterruptUninitialize,
                              LPI2C6_InterruptPowerControl,
                              LPI2C6_Master_InterruptTransmit,
                              LPI2C6_Master_InterruptReceive,
                              LPI2C6_Slave_InterruptTransmit,
                              LPI2C6_Slave_InterruptReceive,
                              LPI2C6_InterruptGetDataCount,
                              LPI2C6_InterruptControl,
                              LPI2C6_InterruptGetStatus
#endif /* RTE_I2C6_DMA_EN */
};

#endif /* LPI2C6 */

#if (defined(LPI2C7) || defined(LPI2C_7)) && defined(RTE_I2C7) && RTE_I2C7
/* User needs to provide the implementation for LPI2C7_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C7_GetFreq(void);

#if defined(LPI2C7)
static cmsis_lpi2c_resource_t LPI2C7_Resource = {LPI2C7, LPI2C7_GetFreq};
#elif defined(LPI2C_7)
static cmsis_lpi2c_resource_t LPI2C7_Resource = {LPI2C_7, LPI2C7_GetFreq};
#endif

#if defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C7_EdmaResource = {
    RTE_I2C7_DMA_TX_DMA_BASE,    RTE_I2C7_DMA_TX_CH,          (uint16_t)RTE_I2C7_DMA_TX_PERI_SEL,
    RTE_I2C7_DMA_RX_DMA_BASE,    RTE_I2C7_DMA_RX_CH,          (uint16_t)RTE_I2C7_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C7_DMA_TX_DMAMUX_BASE, RTE_I2C7_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C7_EdmaHandle);
static edma_handle_t LPI2C7_EdmaTxHandle;
static edma_handle_t LPI2C7_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c7_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C7_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C7_EdmaDriverState = {
#endif
    &LPI2C7_Resource, &LPI2C7_EdmaResource, &LPI2C7_EdmaHandle, &LPI2C7_EdmaTxHandle, &LPI2C7_EdmaRxHandle,
};

static int32_t LPI2C7_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C7_PIN_INIT
    RTE_I2C7_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C7_EdmaDriverState);
}

static int32_t LPI2C7_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C7_PIN_DEINIT
    RTE_I2C7_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C7_EdmaDriverState);
}

static int32_t LPI2C7_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C7_EdmaDriverState);
}

static int32_t LPI2C7_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C7_EdmaDriverState);
}

static int32_t LPI2C7_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C7_EdmaDriverState);
}

static int32_t LPI2C7_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C7_EdmaDriverState);
}

static int32_t LPI2C7_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C7_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C7_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C7_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C7_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c7_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C7_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C7_InterruptDriverState = {
#endif
    &LPI2C7_Resource,
    &LPI2C7_Handle,
};

static void KSDK_LPI2C7_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C7_PIN_INIT
    RTE_I2C7_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_InterruptUninitialize(void)
{
#ifdef RTE_I2C7_PIN_DEINIT
    RTE_I2C7_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C7_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C7_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C7_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C7_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C7_InterruptDriverState);
}

static int32_t LPI2C7_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C7_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C7_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C7_InterruptDriverState);
}

#endif /* RTE_I2C7_DMA_EN */

ARM_DRIVER_I2C Driver_I2C7 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C7_DMA_EN) && RTE_I2C7_DMA_EN
                              LPI2C7_Master_EdmaInitialize,
                              LPI2C7_Master_EdmaUninitialize,
                              LPI2C7_Master_EdmaPowerControl,
                              LPI2C7_Master_EdmaTransmit,
                              LPI2C7_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C7_Master_EdmaGetDataCount,
                              LPI2C7_Master_EdmaControl,
                              LPI2C7_Master_EdmaGetStatus
#else
                              LPI2C7_InterruptInitialize,
                              LPI2C7_InterruptUninitialize,
                              LPI2C7_InterruptPowerControl,
                              LPI2C7_Master_InterruptTransmit,
                              LPI2C7_Master_InterruptReceive,
                              LPI2C7_Slave_InterruptTransmit,
                              LPI2C7_Slave_InterruptReceive,
                              LPI2C7_InterruptGetDataCount,
                              LPI2C7_InterruptControl,
                              LPI2C7_InterruptGetStatus
#endif /* RTE_I2C7_DMA_EN */
};

#endif /* LPI2C7 */

#if (defined(LPI2C8) || defined(LPI2C_8)) && defined(RTE_I2C8) && RTE_I2C8
/* User needs to provide the implementation for LPI2C8_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C8_GetFreq(void);

#if defined(LPI2C8)
static cmsis_lpi2c_resource_t LPI2C8_Resource = {LPI2C8, LPI2C8_GetFreq};
#elif defined(LPI2C_8)
static cmsis_lpi2c_resource_t LPI2C8_Resource = {LPI2C_8, LPI2C8_GetFreq};
#endif

#if defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C8_EdmaResource = {
    RTE_I2C8_DMA_TX_DMA_BASE,    RTE_I2C8_DMA_TX_CH,          (uint16_t)RTE_I2C8_DMA_TX_PERI_SEL,
    RTE_I2C8_DMA_RX_DMA_BASE,    RTE_I2C8_DMA_RX_CH,          (uint16_t)RTE_I2C8_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C8_DMA_TX_DMAMUX_BASE, RTE_I2C8_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C8_EdmaHandle);
static edma_handle_t LPI2C8_EdmaTxHandle;
static edma_handle_t LPI2C8_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c8_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C8_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C8_EdmaDriverState = {
#endif
    &LPI2C8_Resource, &LPI2C8_EdmaResource, &LPI2C8_EdmaHandle, &LPI2C8_EdmaTxHandle, &LPI2C8_EdmaRxHandle,
};

static int32_t LPI2C8_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C8_PIN_INIT
    RTE_I2C8_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C8_EdmaDriverState);
}

static int32_t LPI2C8_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C8_PIN_DEINIT
    RTE_I2C8_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C8_EdmaDriverState);
}

static int32_t LPI2C8_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C8_EdmaDriverState);
}

static int32_t LPI2C8_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C8_EdmaDriverState);
}

static int32_t LPI2C8_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C8_EdmaDriverState);
}

static int32_t LPI2C8_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C8_EdmaDriverState);
}

static int32_t LPI2C8_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C8_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C8_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C8_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C8_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c8_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C8_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C8_InterruptDriverState = {
#endif
    &LPI2C8_Resource,
    &LPI2C8_Handle,
};

static void KSDK_LPI2C8_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C8_PIN_INIT
    RTE_I2C8_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_InterruptUninitialize(void)
{
#ifdef RTE_I2C8_PIN_DEINIT
    RTE_I2C8_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C8_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C8_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C8_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C8_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C8_InterruptDriverState);
}

static int32_t LPI2C8_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C8_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C8_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C8_InterruptDriverState);
}

#endif /* RTE_I2C8_DMA_EN */

ARM_DRIVER_I2C Driver_I2C8 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C8_DMA_EN) && RTE_I2C8_DMA_EN
                              LPI2C8_Master_EdmaInitialize,
                              LPI2C8_Master_EdmaUninitialize,
                              LPI2C8_Master_EdmaPowerControl,
                              LPI2C8_Master_EdmaTransmit,
                              LPI2C8_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C8_Master_EdmaGetDataCount,
                              LPI2C8_Master_EdmaControl,
                              LPI2C8_Master_EdmaGetStatus
#else
                              LPI2C8_InterruptInitialize,
                              LPI2C8_InterruptUninitialize,
                              LPI2C8_InterruptPowerControl,
                              LPI2C8_Master_InterruptTransmit,
                              LPI2C8_Master_InterruptReceive,
                              LPI2C8_Slave_InterruptTransmit,
                              LPI2C8_Slave_InterruptReceive,
                              LPI2C8_InterruptGetDataCount,
                              LPI2C8_InterruptControl,
                              LPI2C8_InterruptGetStatus
#endif /* RTE_I2C8_DMA_EN */
};

#endif /* LPI2C8 */

#if (defined(LPI2C9) || defined(LPI2C_9)) && defined(RTE_I2C9) && RTE_I2C9
/* User needs to provide the implementation for LPI2C9_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C9_GetFreq(void);

#if defined(LPI2C9)
static cmsis_lpi2c_resource_t LPI2C9_Resource = {LPI2C9, LPI2C9_GetFreq};
#elif defined(LPI2C_9)
static cmsis_lpi2c_resource_t LPI2C9_Resource = {LPI2C_9, LPI2C9_GetFreq};
#endif

#if defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C9_EdmaResource = {
    RTE_I2C9_DMA_TX_DMA_BASE,    RTE_I2C9_DMA_TX_CH,          (uint16_t)RTE_I2C9_DMA_TX_PERI_SEL,
    RTE_I2C9_DMA_RX_DMA_BASE,    RTE_I2C9_DMA_RX_CH,          (uint16_t)RTE_I2C9_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C9_DMA_TX_DMAMUX_BASE, RTE_I2C9_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C9_EdmaHandle);
static edma_handle_t LPI2C9_EdmaTxHandle;
static edma_handle_t LPI2C9_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c9_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C9_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C9_EdmaDriverState = {
#endif
    &LPI2C9_Resource, &LPI2C9_EdmaResource, &LPI2C9_EdmaHandle, &LPI2C9_EdmaTxHandle, &LPI2C9_EdmaRxHandle,
};

static int32_t LPI2C9_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C9_PIN_INIT
    RTE_I2C9_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C9_EdmaDriverState);
}

static int32_t LPI2C9_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C9_PIN_DEINIT
    RTE_I2C9_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C9_EdmaDriverState);
}

static int32_t LPI2C9_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C9_EdmaDriverState);
}

static int32_t LPI2C9_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C9_EdmaDriverState);
}

static int32_t LPI2C9_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C9_EdmaDriverState);
}

static int32_t LPI2C9_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C9_EdmaDriverState);
}

static int32_t LPI2C9_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C9_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C9_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C9_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C9_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c9_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C9_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C9_InterruptDriverState = {
#endif
    &LPI2C9_Resource,
    &LPI2C9_Handle,
};

static void KSDK_LPI2C9_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C9_PIN_INIT
    RTE_I2C9_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_InterruptUninitialize(void)
{
#ifdef RTE_I2C9_PIN_DEINIT
    RTE_I2C9_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C9_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C9_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C9_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C9_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C9_InterruptDriverState);
}

static int32_t LPI2C9_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C9_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C9_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C9_InterruptDriverState);
}

#endif /* RTE_I2C9_DMA_EN */

ARM_DRIVER_I2C Driver_I2C9 = {LPI2Cx_GetVersion,
                              LPI2Cx_GetCapabilities,
#if defined(RTE_I2C9_DMA_EN) && RTE_I2C9_DMA_EN
                              LPI2C9_Master_EdmaInitialize,
                              LPI2C9_Master_EdmaUninitialize,
                              LPI2C9_Master_EdmaPowerControl,
                              LPI2C9_Master_EdmaTransmit,
                              LPI2C9_Master_EdmaReceive,
                              NULL,
                              NULL,
                              LPI2C9_Master_EdmaGetDataCount,
                              LPI2C9_Master_EdmaControl,
                              LPI2C9_Master_EdmaGetStatus
#else
                              LPI2C9_InterruptInitialize,
                              LPI2C9_InterruptUninitialize,
                              LPI2C9_InterruptPowerControl,
                              LPI2C9_Master_InterruptTransmit,
                              LPI2C9_Master_InterruptReceive,
                              LPI2C9_Slave_InterruptTransmit,
                              LPI2C9_Slave_InterruptReceive,
                              LPI2C9_InterruptGetDataCount,
                              LPI2C9_InterruptControl,
                              LPI2C9_InterruptGetStatus
#endif /* RTE_I2C9_DMA_EN */
};

#endif /* LPI2C9 */

#if (defined(LPI2C10) || defined(LPI2C_10)) && defined(RTE_I2C10) && RTE_I2C10
/* User needs to provide the implementation for LPI2C10_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C10_GetFreq(void);

#if defined(LPI2C10)
static cmsis_lpi2c_resource_t LPI2C10_Resource = {LPI2C10, LPI2C10_GetFreq};
#elif defined(LPI2C_10)
static cmsis_lpi2c_resource_t LPI2C10_Resource = {LPI2C_10, LPI2C10_GetFreq};
#endif

#if defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C10_EdmaResource = {
    RTE_I2C10_DMA_TX_DMA_BASE,    RTE_I2C10_DMA_TX_CH,          (uint16_t)RTE_I2C10_DMA_TX_PERI_SEL,
    RTE_I2C10_DMA_RX_DMA_BASE,    RTE_I2C10_DMA_RX_CH,          (uint16_t)RTE_I2C10_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C10_DMA_TX_DMAMUX_BASE, RTE_I2C10_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C10_EdmaHandle);
static edma_handle_t LPI2C10_EdmaTxHandle;
static edma_handle_t LPI2C10_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c10_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C10_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C10_EdmaDriverState = {
#endif
    &LPI2C10_Resource, &LPI2C10_EdmaResource, &LPI2C10_EdmaHandle, &LPI2C10_EdmaTxHandle, &LPI2C10_EdmaRxHandle,
};

static int32_t LPI2C10_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C10_PIN_INIT
    RTE_I2C10_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C10_EdmaDriverState);
}

static int32_t LPI2C10_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C10_PIN_DEINIT
    RTE_I2C10_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C10_EdmaDriverState);
}

static int32_t LPI2C10_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C10_EdmaDriverState);
}

static int32_t LPI2C10_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C10_EdmaDriverState);
}

static int32_t LPI2C10_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C10_EdmaDriverState);
}

static int32_t LPI2C10_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C10_EdmaDriverState);
}

static int32_t LPI2C10_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C10_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C10_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C10_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C10_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c10_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C10_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C10_InterruptDriverState = {
#endif
    &LPI2C10_Resource,
    &LPI2C10_Handle,
};

static void KSDK_LPI2C10_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C10_PIN_INIT
    RTE_I2C10_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_InterruptUninitialize(void)
{
#ifdef RTE_I2C10_PIN_DEINIT
    RTE_I2C10_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C10_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C10_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C10_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C10_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C10_InterruptDriverState);
}

static int32_t LPI2C10_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C10_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C10_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C10_InterruptDriverState);
}

#endif /* RTE_I2C10_DMA_EN */

ARM_DRIVER_I2C Driver_I2C10 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C10_DMA_EN) && RTE_I2C10_DMA_EN
                               LPI2C10_Master_EdmaInitialize,
                               LPI2C10_Master_EdmaUninitialize,
                               LPI2C10_Master_EdmaPowerControl,
                               LPI2C10_Master_EdmaTransmit,
                               LPI2C10_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C10_Master_EdmaGetDataCount,
                               LPI2C10_Master_EdmaControl,
                               LPI2C10_Master_EdmaGetStatus
#else
                               LPI2C10_InterruptInitialize,
                               LPI2C10_InterruptUninitialize,
                               LPI2C10_InterruptPowerControl,
                               LPI2C10_Master_InterruptTransmit,
                               LPI2C10_Master_InterruptReceive,
                               LPI2C10_Slave_InterruptTransmit,
                               LPI2C10_Slave_InterruptReceive,
                               LPI2C10_InterruptGetDataCount,
                               LPI2C10_InterruptControl,
                               LPI2C10_InterruptGetStatus
#endif /* RTE_I2C10_DMA_EN */
};

#endif /* LPI2C10 */

#if (defined(LPI2C11) || defined(LPI2C_11)) && defined(RTE_I2C11) && RTE_I2C11
/* User needs to provide the implementation for LPI2C11_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C11_GetFreq(void);

#if defined(LPI2C11)
static cmsis_lpi2c_resource_t LPI2C11_Resource = {LPI2C11, LPI2C11_GetFreq};
#elif defined(LPI2C_11)
static cmsis_lpi2c_resource_t LPI2C11_Resource = {LPI2C_11, LPI2C11_GetFreq};
#endif

#if defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C11_EdmaResource = {
    RTE_I2C11_DMA_TX_DMA_BASE,    RTE_I2C11_DMA_TX_CH,          (uint16_t)RTE_I2C11_DMA_TX_PERI_SEL,
    RTE_I2C11_DMA_RX_DMA_BASE,    RTE_I2C11_DMA_RX_CH,          (uint16_t)RTE_I2C11_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C11_DMA_TX_DMAMUX_BASE, RTE_I2C11_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C11_EdmaHandle);
static edma_handle_t LPI2C11_EdmaTxHandle;
static edma_handle_t LPI2C11_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c11_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C11_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C11_EdmaDriverState = {
#endif
    &LPI2C11_Resource, &LPI2C11_EdmaResource, &LPI2C11_EdmaHandle, &LPI2C11_EdmaTxHandle, &LPI2C11_EdmaRxHandle,
};

static int32_t LPI2C11_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C11_PIN_INIT
    RTE_I2C11_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C11_EdmaDriverState);
}

static int32_t LPI2C11_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C11_PIN_DEINIT
    RTE_I2C11_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C11_EdmaDriverState);
}

static int32_t LPI2C11_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C11_EdmaDriverState);
}

static int32_t LPI2C11_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C11_EdmaDriverState);
}

static int32_t LPI2C11_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C11_EdmaDriverState);
}

static int32_t LPI2C11_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C11_EdmaDriverState);
}

static int32_t LPI2C11_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C11_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C11_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C11_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C11_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c11_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C11_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C11_InterruptDriverState = {
#endif
    &LPI2C11_Resource,
    &LPI2C11_Handle,
};

static void KSDK_LPI2C11_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C11_PIN_INIT
    RTE_I2C11_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_InterruptUninitialize(void)
{
#ifdef RTE_I2C11_PIN_DEINIT
    RTE_I2C11_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C11_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C11_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C11_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C11_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C11_InterruptDriverState);
}

static int32_t LPI2C11_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C11_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C11_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C11_InterruptDriverState);
}

#endif /* RTE_I2C11_DMA_EN */

ARM_DRIVER_I2C Driver_I2C11 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C11_DMA_EN) && RTE_I2C11_DMA_EN
                               LPI2C11_Master_EdmaInitialize,
                               LPI2C11_Master_EdmaUninitialize,
                               LPI2C11_Master_EdmaPowerControl,
                               LPI2C11_Master_EdmaTransmit,
                               LPI2C11_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C11_Master_EdmaGetDataCount,
                               LPI2C11_Master_EdmaControl,
                               LPI2C11_Master_EdmaGetStatus
#else
                               LPI2C11_InterruptInitialize,
                               LPI2C11_InterruptUninitialize,
                               LPI2C11_InterruptPowerControl,
                               LPI2C11_Master_InterruptTransmit,
                               LPI2C11_Master_InterruptReceive,
                               LPI2C11_Slave_InterruptTransmit,
                               LPI2C11_Slave_InterruptReceive,
                               LPI2C11_InterruptGetDataCount,
                               LPI2C11_InterruptControl,
                               LPI2C11_InterruptGetStatus
#endif /* RTE_I2C11_DMA_EN */
};

#endif /* LPI2C11 */

#if (defined(LPI2C12) || defined(LPI2C_12)) && defined(RTE_I2C12) && RTE_I2C12
/* User needs to provide the implementation for LPI2C12_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C12_GetFreq(void);

#if defined(LPI2C12)
static cmsis_lpi2c_resource_t LPI2C12_Resource = {LPI2C12, LPI2C12_GetFreq};
#elif defined(LPI2C_12)
static cmsis_lpi2c_resource_t LPI2C12_Resource = {LPI2C_12, LPI2C12_GetFreq};
#endif

#if defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C12_EdmaResource = {
    RTE_I2C12_DMA_TX_DMA_BASE,    RTE_I2C12_DMA_TX_CH,          (uint16_t)RTE_I2C12_DMA_TX_PERI_SEL,
    RTE_I2C12_DMA_RX_DMA_BASE,    RTE_I2C12_DMA_RX_CH,          (uint16_t)RTE_I2C12_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C12_DMA_TX_DMAMUX_BASE, RTE_I2C12_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C12_EdmaHandle);
static edma_handle_t LPI2C12_EdmaTxHandle;
static edma_handle_t LPI2C12_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c12_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C12_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C12_EdmaDriverState = {
#endif
    &LPI2C12_Resource, &LPI2C12_EdmaResource, &LPI2C12_EdmaHandle, &LPI2C12_EdmaTxHandle, &LPI2C12_EdmaRxHandle,
};

static int32_t LPI2C12_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C12_PIN_INIT
    RTE_I2C12_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C12_EdmaDriverState);
}

static int32_t LPI2C12_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C12_PIN_DEINIT
    RTE_I2C12_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C12_EdmaDriverState);
}

static int32_t LPI2C12_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C12_EdmaDriverState);
}

static int32_t LPI2C12_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C12_EdmaDriverState);
}

static int32_t LPI2C12_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C12_EdmaDriverState);
}

static int32_t LPI2C12_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C12_EdmaDriverState);
}

static int32_t LPI2C12_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C12_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C12_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C12_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C12_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c12_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C12_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C12_InterruptDriverState = {
#endif
    &LPI2C12_Resource,
    &LPI2C12_Handle,
};

static void KSDK_LPI2C12_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C12_PIN_INIT
    RTE_I2C12_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_InterruptUninitialize(void)
{
#ifdef RTE_I2C12_PIN_DEINIT
    RTE_I2C12_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C12_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C12_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C12_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C12_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C12_InterruptDriverState);
}

static int32_t LPI2C12_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C12_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C12_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C12_InterruptDriverState);
}

#endif /* RTE_I2C12_DMA_EN */

ARM_DRIVER_I2C Driver_I2C12 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C12_DMA_EN) && RTE_I2C12_DMA_EN
                               LPI2C12_Master_EdmaInitialize,
                               LPI2C12_Master_EdmaUninitialize,
                               LPI2C12_Master_EdmaPowerControl,
                               LPI2C12_Master_EdmaTransmit,
                               LPI2C12_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C12_Master_EdmaGetDataCount,
                               LPI2C12_Master_EdmaControl,
                               LPI2C12_Master_EdmaGetStatus
#else
                               LPI2C12_InterruptInitialize,
                               LPI2C12_InterruptUninitialize,
                               LPI2C12_InterruptPowerControl,
                               LPI2C12_Master_InterruptTransmit,
                               LPI2C12_Master_InterruptReceive,
                               LPI2C12_Slave_InterruptTransmit,
                               LPI2C12_Slave_InterruptReceive,
                               LPI2C12_InterruptGetDataCount,
                               LPI2C12_InterruptControl,
                               LPI2C12_InterruptGetStatus
#endif /* RTE_I2C12_DMA_EN */
};

#endif /* LPI2C12 */

#if (defined(LPI2C13) || defined(LPI2C_13)) && defined(RTE_I2C13) && RTE_I2C13
/* User needs to provide the implementation for LPI2C13_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C13_GetFreq(void);

#if defined(LPI2C13)
static cmsis_lpi2c_resource_t LPI2C13_Resource = {LPI2C13, LPI2C13_GetFreq};
#elif defined(LPI2C_13)
static cmsis_lpi2c_resource_t LPI2C13_Resource = {LPI2C_13, LPI2C13_GetFreq};
#endif

#if defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C13_EdmaResource = {
    RTE_I2C13_DMA_TX_DMA_BASE,    RTE_I2C13_DMA_TX_CH,          (uint16_t)RTE_I2C13_DMA_TX_PERI_SEL,
    RTE_I2C13_DMA_RX_DMA_BASE,    RTE_I2C13_DMA_RX_CH,          (uint16_t)RTE_I2C13_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C13_DMA_TX_DMAMUX_BASE, RTE_I2C13_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C13_EdmaHandle);
static edma_handle_t LPI2C13_EdmaTxHandle;
static edma_handle_t LPI2C13_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c13_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C13_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C13_EdmaDriverState = {
#endif
    &LPI2C13_Resource, &LPI2C13_EdmaResource, &LPI2C13_EdmaHandle, &LPI2C13_EdmaTxHandle, &LPI2C13_EdmaRxHandle,
};

static int32_t LPI2C13_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C13_PIN_INIT
    RTE_I2C13_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C13_EdmaDriverState);
}

static int32_t LPI2C13_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C13_PIN_DEINIT
    RTE_I2C13_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C13_EdmaDriverState);
}

static int32_t LPI2C13_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C13_EdmaDriverState);
}

static int32_t LPI2C13_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C13_EdmaDriverState);
}

static int32_t LPI2C13_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C13_EdmaDriverState);
}

static int32_t LPI2C13_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C13_EdmaDriverState);
}

static int32_t LPI2C13_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C13_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C13_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C13_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C13_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c13_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C13_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C13_InterruptDriverState = {
#endif
    &LPI2C13_Resource,
    &LPI2C13_Handle,
};

static void KSDK_LPI2C13_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C13_PIN_INIT
    RTE_I2C13_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_InterruptUninitialize(void)
{
#ifdef RTE_I2C13_PIN_DEINIT
    RTE_I2C13_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C13_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C13_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C13_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C13_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C13_InterruptDriverState);
}

static int32_t LPI2C13_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C13_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C13_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C13_InterruptDriverState);
}

#endif /* RTE_I2C13_DMA_EN */

ARM_DRIVER_I2C Driver_I2C13 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C13_DMA_EN) && RTE_I2C13_DMA_EN
                               LPI2C13_Master_EdmaInitialize,
                               LPI2C13_Master_EdmaUninitialize,
                               LPI2C13_Master_EdmaPowerControl,
                               LPI2C13_Master_EdmaTransmit,
                               LPI2C13_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C13_Master_EdmaGetDataCount,
                               LPI2C13_Master_EdmaControl,
                               LPI2C13_Master_EdmaGetStatus
#else
                               LPI2C13_InterruptInitialize,
                               LPI2C13_InterruptUninitialize,
                               LPI2C13_InterruptPowerControl,
                               LPI2C13_Master_InterruptTransmit,
                               LPI2C13_Master_InterruptReceive,
                               LPI2C13_Slave_InterruptTransmit,
                               LPI2C13_Slave_InterruptReceive,
                               LPI2C13_InterruptGetDataCount,
                               LPI2C13_InterruptControl,
                               LPI2C13_InterruptGetStatus
#endif /* RTE_I2C13_DMA_EN */
};

#endif /* LPI2C13 */

#if (defined(LPI2C14) || defined(LPI2C_14)) && defined(RTE_I2C14) && RTE_I2C14
/* User needs to provide the implementation for LPI2C14_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C14_GetFreq(void);

#if defined(LPI2C14)
static cmsis_lpi2c_resource_t LPI2C14_Resource = {LPI2C14, LPI2C14_GetFreq};
#elif defined(LPI2C_14)
static cmsis_lpi2c_resource_t LPI2C14_Resource = {LPI2C_14, LPI2C14_GetFreq};
#endif

#if defined(RTE_I2C14_DMA_EN) && RTE_I2C14_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C14_EdmaResource = {
    RTE_I2C14_DMA_TX_DMA_BASE,    RTE_I2C14_DMA_TX_CH,          (uint16_t)RTE_I2C14_DMA_TX_PERI_SEL,
    RTE_I2C14_DMA_RX_DMA_BASE,    RTE_I2C14_DMA_RX_CH,          (uint16_t)RTE_I2C14_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C14_DMA_TX_DMAMUX_BASE, RTE_I2C14_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C14_EdmaHandle);
static edma_handle_t LPI2C14_EdmaTxHandle;
static edma_handle_t LPI2C14_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c14_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C14_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C14_EdmaDriverState = {
#endif
    &LPI2C14_Resource, &LPI2C14_EdmaResource, &LPI2C14_EdmaHandle, &LPI2C14_EdmaTxHandle, &LPI2C14_EdmaRxHandle,
};

static int32_t LPI2C14_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C14_PIN_INIT
    RTE_I2C14_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C14_EdmaDriverState);
}

static int32_t LPI2C14_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C14_PIN_DEINIT
    RTE_I2C14_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C14_EdmaDriverState);
}

static int32_t LPI2C14_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C14_EdmaDriverState);
}

static int32_t LPI2C14_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C14_EdmaDriverState);
}

static int32_t LPI2C14_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C14_EdmaDriverState);
}

static int32_t LPI2C14_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C14_EdmaDriverState);
}

static int32_t LPI2C14_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C14_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C14_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C14_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C14_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c14_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C14_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C14_InterruptDriverState = {
#endif
    &LPI2C14_Resource,
    &LPI2C14_Handle,
};

static void KSDK_LPI2C14_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C14_PIN_INIT
    RTE_I2C14_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_InterruptUninitialize(void)
{
#ifdef RTE_I2C14_PIN_DEINIT
    RTE_I2C14_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C14_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C14_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C14_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C14_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C14_InterruptDriverState);
}

static int32_t LPI2C14_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C14_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C14_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C14_InterruptDriverState);
}

#endif /* RTE_I2C14_DMA_EN */

ARM_DRIVER_I2C Driver_I2C14 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C14_DMA_EN) && RTE_I2C14_DMA_EN
                               LPI2C14_Master_EdmaInitialize,
                               LPI2C14_Master_EdmaUninitialize,
                               LPI2C14_Master_EdmaPowerControl,
                               LPI2C14_Master_EdmaTransmit,
                               LPI2C14_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C14_Master_EdmaGetDataCount,
                               LPI2C14_Master_EdmaControl,
                               LPI2C14_Master_EdmaGetStatus
#else
                               LPI2C14_InterruptInitialize,
                               LPI2C14_InterruptUninitialize,
                               LPI2C14_InterruptPowerControl,
                               LPI2C14_Master_InterruptTransmit,
                               LPI2C14_Master_InterruptReceive,
                               LPI2C14_Slave_InterruptTransmit,
                               LPI2C14_Slave_InterruptReceive,
                               LPI2C14_InterruptGetDataCount,
                               LPI2C14_InterruptControl,
                               LPI2C14_InterruptGetStatus
#endif /* RTE_I2C14_DMA_EN */
};

#endif /* LPI2C14 */

#if (defined(LPI2C15) || defined(LPI2C_15)) && defined(RTE_I2C15) && RTE_I2C15
/* User needs to provide the implementation for LPI2C15_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C15_GetFreq(void);

#if defined(LPI2C15)
static cmsis_lpi2c_resource_t LPI2C15_Resource = {LPI2C15, LPI2C15_GetFreq};
#elif defined(LPI2C_15)
static cmsis_lpi2c_resource_t LPI2C15_Resource = {LPI2C_15, LPI2C15_GetFreq};
#endif

#if defined(RTE_I2C15_DMA_EN) && RTE_I2C15_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C15_EdmaResource = {
    RTE_I2C15_DMA_TX_DMA_BASE,    RTE_I2C15_DMA_TX_CH,          (uint16_t)RTE_I2C15_DMA_TX_PERI_SEL,
    RTE_I2C15_DMA_RX_DMA_BASE,    RTE_I2C15_DMA_RX_CH,          (uint16_t)RTE_I2C15_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C15_DMA_TX_DMAMUX_BASE, RTE_I2C15_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C15_EdmaHandle);
static edma_handle_t LPI2C15_EdmaTxHandle;
static edma_handle_t LPI2C15_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c15_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C15_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C15_EdmaDriverState = {
#endif
    &LPI2C15_Resource, &LPI2C15_EdmaResource, &LPI2C15_EdmaHandle, &LPI2C15_EdmaTxHandle, &LPI2C15_EdmaRxHandle,
};

static int32_t LPI2C15_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C15_PIN_INIT
    RTE_I2C15_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C15_EdmaDriverState);
}

static int32_t LPI2C15_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C15_PIN_DEINIT
    RTE_I2C15_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C15_EdmaDriverState);
}

static int32_t LPI2C15_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C15_EdmaDriverState);
}

static int32_t LPI2C15_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C15_EdmaDriverState);
}

static int32_t LPI2C15_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C15_EdmaDriverState);
}

static int32_t LPI2C15_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C15_EdmaDriverState);
}

static int32_t LPI2C15_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C15_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C15_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C15_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C15_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c15_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C15_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C15_InterruptDriverState = {
#endif
    &LPI2C15_Resource,
    &LPI2C15_Handle,
};

static void KSDK_LPI2C15_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C15_PIN_INIT
    RTE_I2C15_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_InterruptUninitialize(void)
{
#ifdef RTE_I2C15_PIN_DEINIT
    RTE_I2C15_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C15_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C15_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C15_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C15_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C15_InterruptDriverState);
}

static int32_t LPI2C15_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C15_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C15_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C15_InterruptDriverState);
}

#endif /* RTE_I2C15_DMA_EN */

ARM_DRIVER_I2C Driver_I2C15 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C15_DMA_EN) && RTE_I2C15_DMA_EN
                               LPI2C15_Master_EdmaInitialize,
                               LPI2C15_Master_EdmaUninitialize,
                               LPI2C15_Master_EdmaPowerControl,
                               LPI2C15_Master_EdmaTransmit,
                               LPI2C15_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C15_Master_EdmaGetDataCount,
                               LPI2C15_Master_EdmaControl,
                               LPI2C15_Master_EdmaGetStatus
#else
                               LPI2C15_InterruptInitialize,
                               LPI2C15_InterruptUninitialize,
                               LPI2C15_InterruptPowerControl,
                               LPI2C15_Master_InterruptTransmit,
                               LPI2C15_Master_InterruptReceive,
                               LPI2C15_Slave_InterruptTransmit,
                               LPI2C15_Slave_InterruptReceive,
                               LPI2C15_InterruptGetDataCount,
                               LPI2C15_InterruptControl,
                               LPI2C15_InterruptGetStatus
#endif /* RTE_I2C15_DMA_EN */
};

#endif /* LPI2C15 */

#if (defined(LPI2C16) || defined(LPI2C_16)) && defined(RTE_I2C16) && RTE_I2C16
/* User needs to provide the implementation for LPI2C16_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C16_GetFreq(void);

#if defined(LPI2C16)
static cmsis_lpi2c_resource_t LPI2C16_Resource = {LPI2C16, LPI2C16_GetFreq};
#elif defined(LPI2C_16)
static cmsis_lpi2c_resource_t LPI2C16_Resource = {LPI2C_16, LPI2C16_GetFreq};
#endif

#if defined(RTE_I2C16_DMA_EN) && RTE_I2C16_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C16_EdmaResource = {
    RTE_I2C16_DMA_TX_DMA_BASE,    RTE_I2C16_DMA_TX_CH,          (uint16_t)RTE_I2C16_DMA_TX_PERI_SEL,
    RTE_I2C16_DMA_RX_DMA_BASE,    RTE_I2C16_DMA_RX_CH,          (uint16_t)RTE_I2C16_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C16_DMA_TX_DMAMUX_BASE, RTE_I2C16_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C16_EdmaHandle);
static edma_handle_t LPI2C16_EdmaTxHandle;
static edma_handle_t LPI2C16_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c16_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C16_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C16_EdmaDriverState = {
#endif
    &LPI2C16_Resource, &LPI2C16_EdmaResource, &LPI2C16_EdmaHandle, &LPI2C16_EdmaTxHandle, &LPI2C16_EdmaRxHandle,
};

static int32_t LPI2C16_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C16_PIN_INIT
    RTE_I2C16_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C16_EdmaDriverState);
}

static int32_t LPI2C16_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C16_PIN_DEINIT
    RTE_I2C16_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C16_EdmaDriverState);
}

static int32_t LPI2C16_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C16_EdmaDriverState);
}

static int32_t LPI2C16_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C16_EdmaDriverState);
}

static int32_t LPI2C16_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C16_EdmaDriverState);
}

static int32_t LPI2C16_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C16_EdmaDriverState);
}

static int32_t LPI2C16_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C16_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C16_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C16_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C16_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c16_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C16_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C16_InterruptDriverState = {
#endif
    &LPI2C16_Resource,
    &LPI2C16_Handle,
};

static void KSDK_LPI2C16_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C16_PIN_INIT
    RTE_I2C16_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_InterruptUninitialize(void)
{
#ifdef RTE_I2C16_PIN_DEINIT
    RTE_I2C16_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C16_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C16_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C16_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C16_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C16_InterruptDriverState);
}

static int32_t LPI2C16_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C16_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C16_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C16_InterruptDriverState);
}

#endif /* RTE_I2C16_DMA_EN */

ARM_DRIVER_I2C Driver_I2C16 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C16_DMA_EN) && RTE_I2C16_DMA_EN
                               LPI2C16_Master_EdmaInitialize,
                               LPI2C16_Master_EdmaUninitialize,
                               LPI2C16_Master_EdmaPowerControl,
                               LPI2C16_Master_EdmaTransmit,
                               LPI2C16_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C16_Master_EdmaGetDataCount,
                               LPI2C16_Master_EdmaControl,
                               LPI2C16_Master_EdmaGetStatus
#else
                               LPI2C16_InterruptInitialize,
                               LPI2C16_InterruptUninitialize,
                               LPI2C16_InterruptPowerControl,
                               LPI2C16_Master_InterruptTransmit,
                               LPI2C16_Master_InterruptReceive,
                               LPI2C16_Slave_InterruptTransmit,
                               LPI2C16_Slave_InterruptReceive,
                               LPI2C16_InterruptGetDataCount,
                               LPI2C16_InterruptControl,
                               LPI2C16_InterruptGetStatus
#endif /* RTE_I2C16_DMA_EN */
};

#endif /* LPI2C16 */

#if (defined(LPI2C17) || defined(LPI2C_17)) && defined(RTE_I2C17) && RTE_I2C17
/* User needs to provide the implementation for LPI2C17_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C17_GetFreq(void);

#if defined(LPI2C17)
static cmsis_lpi2c_resource_t LPI2C17_Resource = {LPI2C17, LPI2C17_GetFreq};
#elif defined(LPI2C_17)
static cmsis_lpi2c_resource_t LPI2C17_Resource = {LPI2C_17, LPI2C17_GetFreq};
#endif

#if defined(RTE_I2C17_DMA_EN) && RTE_I2C17_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C17_EdmaResource = {
    RTE_I2C17_DMA_TX_DMA_BASE,    RTE_I2C17_DMA_TX_CH,          (uint16_t)RTE_I2C17_DMA_TX_PERI_SEL,
    RTE_I2C17_DMA_RX_DMA_BASE,    RTE_I2C17_DMA_RX_CH,          (uint16_t)RTE_I2C17_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C17_DMA_TX_DMAMUX_BASE, RTE_I2C17_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C17_EdmaHandle);
static edma_handle_t LPI2C17_EdmaTxHandle;
static edma_handle_t LPI2C17_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c17_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C17_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C17_EdmaDriverState = {
#endif
    &LPI2C17_Resource, &LPI2C17_EdmaResource, &LPI2C17_EdmaHandle, &LPI2C17_EdmaTxHandle, &LPI2C17_EdmaRxHandle,
};

static int32_t LPI2C17_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C17_PIN_INIT
    RTE_I2C17_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C17_EdmaDriverState);
}

static int32_t LPI2C17_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C17_PIN_DEINIT
    RTE_I2C17_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C17_EdmaDriverState);
}

static int32_t LPI2C17_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C17_EdmaDriverState);
}

static int32_t LPI2C17_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C17_EdmaDriverState);
}

static int32_t LPI2C17_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C17_EdmaDriverState);
}

static int32_t LPI2C17_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C17_EdmaDriverState);
}

static int32_t LPI2C17_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C17_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C17_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C17_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C17_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c17_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C17_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C17_InterruptDriverState = {
#endif
    &LPI2C17_Resource,
    &LPI2C17_Handle,
};

static void KSDK_LPI2C17_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C17_PIN_INIT
    RTE_I2C17_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_InterruptUninitialize(void)
{
#ifdef RTE_I2C17_PIN_DEINIT
    RTE_I2C17_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C17_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C17_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C17_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C17_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C17_InterruptDriverState);
}

static int32_t LPI2C17_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C17_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C17_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C17_InterruptDriverState);
}

#endif /* RTE_I2C17_DMA_EN */

ARM_DRIVER_I2C Driver_I2C17 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C17_DMA_EN) && RTE_I2C17_DMA_EN
                               LPI2C17_Master_EdmaInitialize,
                               LPI2C17_Master_EdmaUninitialize,
                               LPI2C17_Master_EdmaPowerControl,
                               LPI2C17_Master_EdmaTransmit,
                               LPI2C17_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C17_Master_EdmaGetDataCount,
                               LPI2C17_Master_EdmaControl,
                               LPI2C17_Master_EdmaGetStatus
#else
                               LPI2C17_InterruptInitialize,
                               LPI2C17_InterruptUninitialize,
                               LPI2C17_InterruptPowerControl,
                               LPI2C17_Master_InterruptTransmit,
                               LPI2C17_Master_InterruptReceive,
                               LPI2C17_Slave_InterruptTransmit,
                               LPI2C17_Slave_InterruptReceive,
                               LPI2C17_InterruptGetDataCount,
                               LPI2C17_InterruptControl,
                               LPI2C17_InterruptGetStatus
#endif /* RTE_I2C17_DMA_EN */
};

#endif /* LPI2C17 */

#if (defined(LPI2C18) || defined(LPI2C_18)) && defined(RTE_I2C18) && RTE_I2C18
/* User needs to provide the implementation for LPI2C18_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C18_GetFreq(void);

#if defined(LPI2C18)
static cmsis_lpi2c_resource_t LPI2C18_Resource = {LPI2C18, LPI2C18_GetFreq};
#elif defined(LPI2C_18)
static cmsis_lpi2c_resource_t LPI2C18_Resource = {LPI2C_18, LPI2C18_GetFreq};
#endif

#if defined(RTE_I2C18_DMA_EN) && RTE_I2C18_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C18_EdmaResource = {
    RTE_I2C18_DMA_TX_DMA_BASE,    RTE_I2C18_DMA_TX_CH,          (uint16_t)RTE_I2C18_DMA_TX_PERI_SEL,
    RTE_I2C18_DMA_RX_DMA_BASE,    RTE_I2C18_DMA_RX_CH,          (uint16_t)RTE_I2C18_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C18_DMA_TX_DMAMUX_BASE, RTE_I2C18_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C18_EdmaHandle);
static edma_handle_t LPI2C18_EdmaTxHandle;
static edma_handle_t LPI2C18_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c18_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C18_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C18_EdmaDriverState = {
#endif
    &LPI2C18_Resource, &LPI2C18_EdmaResource, &LPI2C18_EdmaHandle, &LPI2C18_EdmaTxHandle, &LPI2C18_EdmaRxHandle,
};

static int32_t LPI2C18_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C18_PIN_INIT
    RTE_I2C18_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C18_EdmaDriverState);
}

static int32_t LPI2C18_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C18_PIN_DEINIT
    RTE_I2C18_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C18_EdmaDriverState);
}

static int32_t LPI2C18_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C18_EdmaDriverState);
}

static int32_t LPI2C18_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C18_EdmaDriverState);
}

static int32_t LPI2C18_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C18_EdmaDriverState);
}

static int32_t LPI2C18_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C18_EdmaDriverState);
}

static int32_t LPI2C18_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C18_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C18_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C18_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C18_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c18_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C18_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C18_InterruptDriverState = {
#endif
    &LPI2C18_Resource,
    &LPI2C18_Handle,
};

static void KSDK_LPI2C18_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C18_PIN_INIT
    RTE_I2C18_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_InterruptUninitialize(void)
{
#ifdef RTE_I2C18_PIN_DEINIT
    RTE_I2C18_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C18_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C18_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C18_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C18_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C18_InterruptDriverState);
}

static int32_t LPI2C18_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C18_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C18_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C18_InterruptDriverState);
}

#endif /* RTE_I2C18_DMA_EN */

ARM_DRIVER_I2C Driver_I2C18 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C18_DMA_EN) && RTE_I2C18_DMA_EN
                               LPI2C18_Master_EdmaInitialize,
                               LPI2C18_Master_EdmaUninitialize,
                               LPI2C18_Master_EdmaPowerControl,
                               LPI2C18_Master_EdmaTransmit,
                               LPI2C18_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C18_Master_EdmaGetDataCount,
                               LPI2C18_Master_EdmaControl,
                               LPI2C18_Master_EdmaGetStatus
#else
                               LPI2C18_InterruptInitialize,
                               LPI2C18_InterruptUninitialize,
                               LPI2C18_InterruptPowerControl,
                               LPI2C18_Master_InterruptTransmit,
                               LPI2C18_Master_InterruptReceive,
                               LPI2C18_Slave_InterruptTransmit,
                               LPI2C18_Slave_InterruptReceive,
                               LPI2C18_InterruptGetDataCount,
                               LPI2C18_InterruptControl,
                               LPI2C18_InterruptGetStatus
#endif /* RTE_I2C18_DMA_EN */
};

#endif /* LPI2C18 */

#if (defined(LPI2C19) || defined(LPI2C_19)) && defined(RTE_I2C19) && RTE_I2C19
/* User needs to provide the implementation for LPI2C19_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C19_GetFreq(void);

#if defined(LPI2C19)
static cmsis_lpi2c_resource_t LPI2C19_Resource = {LPI2C19, LPI2C19_GetFreq};
#elif defined(LPI2C_19)
static cmsis_lpi2c_resource_t LPI2C19_Resource = {LPI2C_19, LPI2C19_GetFreq};
#endif

#if defined(RTE_I2C19_DMA_EN) && RTE_I2C19_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C19_EdmaResource = {
    RTE_I2C19_DMA_TX_DMA_BASE,    RTE_I2C19_DMA_TX_CH,          (uint16_t)RTE_I2C19_DMA_TX_PERI_SEL,
    RTE_I2C19_DMA_RX_DMA_BASE,    RTE_I2C19_DMA_RX_CH,          (uint16_t)RTE_I2C19_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C19_DMA_TX_DMAMUX_BASE, RTE_I2C19_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C19_EdmaHandle);
static edma_handle_t LPI2C19_EdmaTxHandle;
static edma_handle_t LPI2C19_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c19_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C19_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C19_EdmaDriverState = {
#endif
    &LPI2C19_Resource, &LPI2C19_EdmaResource, &LPI2C19_EdmaHandle, &LPI2C19_EdmaTxHandle, &LPI2C19_EdmaRxHandle,
};

static int32_t LPI2C19_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C19_PIN_INIT
    RTE_I2C19_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C19_EdmaDriverState);
}

static int32_t LPI2C19_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C19_PIN_DEINIT
    RTE_I2C19_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C19_EdmaDriverState);
}

static int32_t LPI2C19_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C19_EdmaDriverState);
}

static int32_t LPI2C19_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C19_EdmaDriverState);
}

static int32_t LPI2C19_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C19_EdmaDriverState);
}

static int32_t LPI2C19_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C19_EdmaDriverState);
}

static int32_t LPI2C19_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C19_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C19_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C19_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C19_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c19_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C19_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C19_InterruptDriverState = {
#endif
    &LPI2C19_Resource,
    &LPI2C19_Handle,
};

static void KSDK_LPI2C19_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C19_PIN_INIT
    RTE_I2C19_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_InterruptUninitialize(void)
{
#ifdef RTE_I2C19_PIN_DEINIT
    RTE_I2C19_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C19_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C19_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C19_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C19_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C19_InterruptDriverState);
}

static int32_t LPI2C19_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C19_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C19_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C19_InterruptDriverState);
}

#endif /* RTE_I2C19_DMA_EN */

ARM_DRIVER_I2C Driver_I2C19 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C19_DMA_EN) && RTE_I2C19_DMA_EN
                               LPI2C19_Master_EdmaInitialize,
                               LPI2C19_Master_EdmaUninitialize,
                               LPI2C19_Master_EdmaPowerControl,
                               LPI2C19_Master_EdmaTransmit,
                               LPI2C19_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C19_Master_EdmaGetDataCount,
                               LPI2C19_Master_EdmaControl,
                               LPI2C19_Master_EdmaGetStatus
#else
                               LPI2C19_InterruptInitialize,
                               LPI2C19_InterruptUninitialize,
                               LPI2C19_InterruptPowerControl,
                               LPI2C19_Master_InterruptTransmit,
                               LPI2C19_Master_InterruptReceive,
                               LPI2C19_Slave_InterruptTransmit,
                               LPI2C19_Slave_InterruptReceive,
                               LPI2C19_InterruptGetDataCount,
                               LPI2C19_InterruptControl,
                               LPI2C19_InterruptGetStatus
#endif /* RTE_I2C19_DMA_EN */
};

#endif /* LPI2C19 */

#if (defined(LPI2C20) || defined(LPI2C_20)) && defined(RTE_I2C20) && RTE_I2C20
/* User needs to provide the implementation for LPI2C20_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPI2C20_GetFreq(void);

#if defined(LPI2C20)
static cmsis_lpi2c_resource_t LPI2C20_Resource = {LPI2C20, LPI2C20_GetFreq};
#elif defined(LPI2C_20)
static cmsis_lpi2c_resource_t LPI2C20_Resource = {LPI2C_20, LPI2C20_GetFreq};
#endif

#if defined(RTE_I2C20_DMA_EN) && RTE_I2C20_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpi2c_edma_resource_t LPI2C20_EdmaResource = {
    RTE_I2C20_DMA_TX_DMA_BASE,    RTE_I2C20_DMA_TX_CH,          (uint16_t)RTE_I2C20_DMA_TX_PERI_SEL,
    RTE_I2C20_DMA_RX_DMA_BASE,    RTE_I2C20_DMA_RX_CH,          (uint16_t)RTE_I2C20_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_I2C20_DMA_TX_DMAMUX_BASE, RTE_I2C20_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static lpi2c_master_edma_handle_t LPI2C20_EdmaHandle);
static edma_handle_t LPI2C20_EdmaTxHandle;
static edma_handle_t LPI2C20_EdmaRxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c20_edma_driver_state")
static cmsis_lpi2c_edma_driver_state_t LPI2C20_EdmaDriverState = {
#else
static cmsis_lpi2c_edma_driver_state_t LPI2C20_EdmaDriverState = {
#endif
    &LPI2C20_Resource, &LPI2C20_EdmaResource, &LPI2C20_EdmaHandle, &LPI2C20_EdmaTxHandle, &LPI2C20_EdmaRxHandle,
};

static int32_t LPI2C20_Master_EdmaInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C20_PIN_INIT
    RTE_I2C20_PIN_INIT();
#endif
    return LPI2C_Master_EdmaInitialize(cb_event, &LPI2C20_EdmaDriverState);
}

static int32_t LPI2C20_Master_EdmaUninitialize(void)
{
#ifdef RTE_I2C20_PIN_DEINIT
    RTE_I2C20_PIN_DEINIT();
#endif
    return LPI2C_Master_EdmaUninitialize(&LPI2C20_EdmaDriverState);
}

static int32_t LPI2C20_Master_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_Master_EdmaPowerControl(state, &LPI2C20_EdmaDriverState);
}

static int32_t LPI2C20_Master_EdmaTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaTransmit(addr, data, num, xfer_pending, &LPI2C20_EdmaDriverState);
}

static int32_t LPI2C20_Master_EdmaReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_EdmaReceive(addr, data, num, xfer_pending, &LPI2C20_EdmaDriverState);
}

static int32_t LPI2C20_Master_EdmaGetDataCount(void)
{
    return LPI2C_Master_EdmaGetDataCount(&LPI2C20_EdmaDriverState);
}

static int32_t LPI2C20_Master_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPI2C_Master_EdmaControl(control, arg, &LPI2C20_EdmaDriverState);
}

static ARM_I2C_STATUS LPI2C20_Master_EdmaGetStatus(void)
{
    return LPI2C_Master_EdmaGetStatus(&LPI2C20_EdmaDriverState);
}

#endif

#else

static cmsis_i2c_handle_t LPI2C20_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpi2c20_interrupt_driver_state")
static cmsis_lpi2c_interrupt_driver_state_t LPI2C20_InterruptDriverState = {
#else
static cmsis_lpi2c_interrupt_driver_state_t LPI2C20_InterruptDriverState = {
#endif
    &LPI2C20_Resource,
    &LPI2C20_Handle,
};

static void KSDK_LPI2C20_SLAVE_InterruptCallback(LPI2C_Type *base, lpi2c_slave_transfer_t *xfer, void *userData)
{
    KSDK_LPI2C_SLAVE_InterruptCallback(base, xfer, userData, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_InterruptInitialize(ARM_I2C_SignalEvent_t cb_event)
{
#ifdef RTE_I2C20_PIN_INIT
    RTE_I2C20_PIN_INIT();
#endif
    return LPI2C_InterruptInitialize(cb_event, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_InterruptUninitialize(void)
{
#ifdef RTE_I2C20_PIN_DEINIT
    RTE_I2C20_PIN_DEINIT();
#endif
    return LPI2C_InterruptUninitialize(&LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPI2C_InterruptPowerControl(state, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_Master_InterruptTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptTransmit(addr, data, num, xfer_pending, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_Master_InterruptReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return LPI2C_Master_InterruptReceive(addr, data, num, xfer_pending, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_Slave_InterruptTransmit(const uint8_t *data, uint32_t num)
{
    LPI2C20_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C20_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptTransmit(data, num, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_Slave_InterruptReceive(uint8_t *data, uint32_t num)
{
    LPI2C20_InterruptDriverState.handle->slave_handle.callback = KSDK_LPI2C20_SLAVE_InterruptCallback;
    return LPI2C_Slave_InterruptReceive(data, num, &LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_InterruptGetDataCount(void)
{
    return LPI2C_InterruptGetDataCount(&LPI2C20_InterruptDriverState);
}

static int32_t LPI2C20_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPI2C_InterruptControl(control, arg, &LPI2C20_InterruptDriverState);
}

static ARM_I2C_STATUS LPI2C20_InterruptGetStatus(void)
{
    return LPI2C_InterruptGetStatus(&LPI2C20_InterruptDriverState);
}

#endif /* RTE_I2C20_DMA_EN */

ARM_DRIVER_I2C Driver_I2C20 = {LPI2Cx_GetVersion,
                               LPI2Cx_GetCapabilities,
#if defined(RTE_I2C20_DMA_EN) && RTE_I2C20_DMA_EN
                               LPI2C20_Master_EdmaInitialize,
                               LPI2C20_Master_EdmaUninitialize,
                               LPI2C20_Master_EdmaPowerControl,
                               LPI2C20_Master_EdmaTransmit,
                               LPI2C20_Master_EdmaReceive,
                               NULL,
                               NULL,
                               LPI2C20_Master_EdmaGetDataCount,
                               LPI2C20_Master_EdmaControl,
                               LPI2C20_Master_EdmaGetStatus
#else
                               LPI2C20_InterruptInitialize,
                               LPI2C20_InterruptUninitialize,
                               LPI2C20_InterruptPowerControl,
                               LPI2C20_Master_InterruptTransmit,
                               LPI2C20_Master_InterruptReceive,
                               LPI2C20_Slave_InterruptTransmit,
                               LPI2C20_Slave_InterruptReceive,
                               LPI2C20_InterruptGetDataCount,
                               LPI2C20_InterruptControl,
                               LPI2C20_InterruptGetStatus
#endif /* RTE_I2C20_DMA_EN */
};

#endif /* LPI2C20 */
