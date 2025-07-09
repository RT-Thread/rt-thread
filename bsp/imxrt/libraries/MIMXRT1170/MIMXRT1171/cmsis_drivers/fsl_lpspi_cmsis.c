/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2021,2024-2025 NXP. Not a Contribution.
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

#include "fsl_lpspi_cmsis.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpspi_cmsis"
#endif

#if ((defined(RTE_SPI0) && RTE_SPI0 && (defined(LPSPI0) || defined(LPSPI_0))) || (defined(RTE_SPI1) && RTE_SPI1 && (defined(LPSPI1) || defined(LPSPI_1))) ||       \
     (defined(RTE_SPI2) && RTE_SPI2 && (defined(LPSPI2) || defined(LPSPI_2))) || (defined(RTE_SPI3) && RTE_SPI3 && (defined(LPSPI3) || defined(LPSPI_3))) ||       \
     (defined(RTE_SPI4) && RTE_SPI4 && (defined(LPSPI4) || defined(LPSPI_4))) || (defined(RTE_SPI5) && RTE_SPI5 && (defined(LPSPI5) || defined(LPSPI_5))) ||       \
     (defined(RTE_SPI6) && RTE_SPI6 && (defined(LPSPI6) || defined(LPSPI_6))) || (defined(RTE_SPI7) && RTE_SPI7 && (defined(LPSPI7) || defined(LPSPI_7))) ||       \
     (defined(RTE_SPI8) && RTE_SPI8 && (defined(LPSPI8) || defined(LPSPI_8))) || (defined(RTE_SPI9) && RTE_SPI9 && (defined(LPSPI9) || defined(LPSPI_9))) ||       \
     (defined(RTE_SPI10) && RTE_SPI10 && (defined(LPSPI10) || defined(LPSPI_10))) || (defined(RTE_SPI11) && RTE_SPI11 && (defined(LPSPI11) || defined(LPSPI_11))) || \
     (defined(RTE_SPI12) && RTE_SPI12 && (defined(LPSPI12) || defined(LPSPI_12))) || (defined(RTE_SPI13) && RTE_SPI13 && (defined(LPSPI13) || defined(LPSPI_13))) || \
     (defined(RTE_SPI14) && RTE_SPI14 && (defined(LPSPI14) || defined(LPSPI_14))) || (defined(RTE_SPI15) && RTE_SPI15 && (defined(LPSPI15) || defined(LPSPI_15))) || \
     (defined(RTE_SPI16) && RTE_SPI16 && (defined(LPSPI16) || defined(LPSPI_16))) || (defined(RTE_SPI17) && RTE_SPI17 && (defined(LPSPI17) || defined(LPSPI_17))) || \
     (defined(RTE_SPI18) && RTE_SPI18 && (defined(LPSPI18) || defined(LPSPI_18))) || (defined(RTE_SPI19) && RTE_SPI19 && (defined(LPSPI19) || defined(LPSPI_19))) || \
     (defined(RTE_SPI20) && RTE_SPI20 && (defined(LPSPI20) || defined(LPSPI_20))))

#define ARM_LPSPI_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR((2), (12)) /* driver version */

/*
 * ARMCC does not support split the data section automatically, so the driver
 * needs to split the data to separate sections explicitly, to reduce codesize.
 */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define ARMCC_SECTION(section_name) __attribute__((section(section_name)))
#endif

static clock_ip_name_t const s_lpspiClock[] = LPSPI_CLOCKS;

typedef const struct _cmsis_lpspi_resource
{
    LPSPI_Type *base;
    uint32_t instance;
    uint32_t (*GetFreq)(void);
} cmsis_lpspi_resource_t;

typedef union _cmsis_lpspi_handle
{
    lpspi_master_handle_t masterHandle;
    lpspi_slave_handle_t slaveHandle;
} cmsis_lpspi_handle_t;

typedef struct _cmsis_lpspi_interrupt_driver_state
{
    cmsis_lpspi_resource_t *resource;
    cmsis_lpspi_handle_t *handle;
    ARM_SPI_SignalEvent_t cb_event;
    uint32_t baudRate_Bps;
    uint8_t flags; /*!< Control and state flags. */
} cmsis_lpspi_interrupt_driver_state_t;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
typedef const struct _cmsis_lpspi_edma_resource
{
    void *txEdmaBase;
    uint32_t txEdmaChannel;
    uint16_t txDmaRequest;

    void *rxEdmaBase;
    uint32_t rxEdmaChannel;
    uint16_t rxDmaRequest;

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    DMAMUX_Type *txDmamuxBase;
    DMAMUX_Type *rxDmamuxBase;
#endif
} cmsis_lpspi_edma_resource_t;

typedef union _cmsis_lpspi_edma_handle
{
    lpspi_master_edma_handle_t masterHandle;
    lpspi_slave_edma_handle_t slaveHandle;
} cmsis_lpspi_edma_handle_t;

typedef struct _cmsis_lpspi_edma_driver_state
{
    cmsis_lpspi_resource_t *resource;
    cmsis_lpspi_edma_resource_t *dmaResource;
    cmsis_lpspi_edma_handle_t *handle;
    edma_handle_t *edmaRxRegToRxDataHandle;
    edma_handle_t *edmaTxDataToTxRegHandle;
    ARM_SPI_SignalEvent_t cb_event;
    uint32_t baudRate_Bps;
    uint8_t flags; /*!< Control and state flags. */
} cmsis_lpspi_edma_driver_state_t;
#endif

/* Driver Version */
static const ARM_DRIVER_VERSION s_lpspiDriverVersion = {ARM_SPI_API_VERSION, ARM_LPSPI_DRV_VERSION};

/* Driver Capabilities */
static const ARM_SPI_CAPABILITIES s_lpspiDriverCapabilities = {
    1, /* Simplex Mode (Master and Slave) */
    0, /* TI Synchronous Serial Interface */
    0, /* Microwire Interface  */
    0  /* Signal Mode Fault event: \ref ARM_SPI_EVENT_MODE_FAULT */
};

/*
 *Common Control function used by LPSPI_InterruptControl / LPSPI_EdmaControl.
 */
static int32_t LPSPI_CommonControl(uint32_t control,
                                   uint32_t arg,
                                   cmsis_lpspi_resource_t *resource,
                                   uint8_t *isConfigured)
{
    lpspi_master_config_t masterConfig;
    LPSPI_MasterGetDefaultConfig(&masterConfig);
    lpspi_slave_config_t slaveConfig;
    LPSPI_SlaveGetDefaultConfig(&slaveConfig);
    bool isMaster = ((control & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_MASTER) ||
                    ((control & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_MASTER_SIMPLEX);
    masterConfig.baudRate = arg;

    if (ARM_SPI_MODE_MASTER_SIMPLEX == (control & (uint32_t)ARM_SPI_CONTROL_Msk))
    {
        masterConfig.pinCfg = kLPSPI_SdoInSdoOut;
    }
    if (ARM_SPI_MODE_SLAVE_SIMPLEX == (control & (uint32_t)ARM_SPI_CONTROL_Msk))
    {
        slaveConfig.pinCfg = kLPSPI_SdiInSdiOut;
    }

#if (defined(RTE_SPI0_PCS_TO_SCK_DELAY) && defined(RTE_SPI0_SCK_TO_PSC_DELAY) && \
     defined(RTE_SPI0_BETWEEN_TRANSFER_DELAY))
    if (0U == resource->instance)
    {
        masterConfig.pcsToSckDelayInNanoSec        = (uint32_t)RTE_SPI0_PCS_TO_SCK_DELAY;
        masterConfig.lastSckToPcsDelayInNanoSec    = (uint32_t)RTE_SPI0_SCK_TO_PSC_DELAY;
        masterConfig.betweenTransferDelayInNanoSec = (uint32_t)RTE_SPI0_BETWEEN_TRANSFER_DELAY;
    }
#endif /*RTE LPSPI0 trnafer delay time configure */

#if (defined(RTE_SPI1_PCS_TO_SCK_DELAY) && defined(RTE_SPI1_SCK_TO_PSC_DELAY) && \
     defined(RTE_SPI1_BETWEEN_TRANSFER_DELAY))
    if (1U == resource->instance)
    {
        masterConfig.pcsToSckDelayInNanoSec        = (uint32_t)RTE_SPI1_PCS_TO_SCK_DELAY;
        masterConfig.lastSckToPcsDelayInNanoSec    = (uint32_t)RTE_SPI1_SCK_TO_PSC_DELAY;
        masterConfig.betweenTransferDelayInNanoSec = (uint32_t)RTE_SPI1_BETWEEN_TRANSFER_DELAY;
    }
#endif /*RTE LPSPI1 trnafer delay time configure */

#if (defined(RTE_SPI2_PCS_TO_SCK_DELAY) && defined(RTE_SPI2_SCK_TO_PSC_DELAY) && \
     defined(RTE_SPI2_BETWEEN_TRANSFER_DELAY))
    if (2U == resource->instance)
    {
        masterConfig.pcsToSckDelayInNanoSec        = (uint32_t)RTE_SPI2_PCS_TO_SCK_DELAY;
        masterConfig.lastSckToPcsDelayInNanoSec    = (uint32_t)RTE_SPI2_SCK_TO_PSC_DELAY;
        masterConfig.betweenTransferDelayInNanoSec = (uint32_t)RTE_SPI2_BETWEEN_TRANSFER_DELAY;
    }
#endif /*RTE LPSPI2 trnafer delay time configure */
#if (defined(RTE_SPI3_PCS_TO_SCK_DELAY) && defined(RTE_SPI3_SCK_TO_PSC_DELAY) && \
     defined(RTE_SPI3_BETWEEN_TRANSFER_DELAY))
    if (3U == resource->instance)
    {
        masterConfig.pcsToSckDelayInNanoSec        = (uint32_t)RTE_SPI3_PCS_TO_SCK_DELAY;
        masterConfig.lastSckToPcsDelayInNanoSec    = (uint32_t)RTE_SPI3_SCK_TO_PSC_DELAY;
        masterConfig.betweenTransferDelayInNanoSec = (uint32_t)RTE_SPI3_BETWEEN_TRANSFER_DELAY;
    }
#endif /*RTE LPSPI3 trnafer delay time configure */

#if (defined(RTE_SPI4_PCS_TO_SCK_DELAY) && defined(RTE_SPI4_SCK_TO_PSC_DELAY) && \
     defined(RTE_SPI4_BETWEEN_TRANSFER_DELAY))
    if (4U == resource->instance)
    {
        masterConfig.pcsToSckDelayInNanoSec        = (uint32_t)RTE_SPI4_PCS_TO_SCK_DELAY;
        masterConfig.lastSckToPcsDelayInNanoSec    = (uint32_t)RTE_SPI4_SCK_TO_PSC_DELAY;
        masterConfig.betweenTransferDelayInNanoSec = (uint32_t)RTE_SPI4_BETWEEN_TRANSFER_DELAY;
    }
#endif /*RTE LPSPI4 trnafer delay time configure */

#if (defined(RTE_SPI5_PCS_TO_SCK_DELAY) && defined(RTE_SPI5_SCK_TO_PSC_DELAY) && \
     defined(RTE_SPI5_BETWEEN_TRANSFER_DELAY))
    if (5U == resource->instance)
    {
        masterConfig.pcsToSckDelayInNanoSec        = (uint32_t)RTE_SPI5_PCS_TO_SCK_DELAY;
        masterConfig.lastSckToPcsDelayInNanoSec    = (uint32_t)RTE_SPI5_SCK_TO_PSC_DELAY;
        masterConfig.betweenTransferDelayInNanoSec = (uint32_t)RTE_SPI5_BETWEEN_TRANSFER_DELAY;
    }
#endif /*RTE LPSPI5 trnafer delay time configure */

    switch (control & (uint32_t)ARM_SPI_FRAME_FORMAT_Msk)
    {
        case ARM_SPI_CPOL0_CPHA0: /* Clock Polarity 0, Clock Phase 0*/
            if (isMaster)
            {
                masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh;
                masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge;
            }
            else
            {
                slaveConfig.cpol = kLPSPI_ClockPolarityActiveHigh;
                slaveConfig.cpha = kLPSPI_ClockPhaseFirstEdge;
            }
            break;
        case ARM_SPI_CPOL0_CPHA1: /* Clock Polarity 0, Clock Phase 1*/
            if (isMaster)
            {
                masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh;
                masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge;
            }
            else
            {
                slaveConfig.cpol = kLPSPI_ClockPolarityActiveHigh;
                slaveConfig.cpha = kLPSPI_ClockPhaseSecondEdge;
            }
            break;
        case ARM_SPI_CPOL1_CPHA0: /* Clock Polarity 1, Clock Phase 0*/
            if (isMaster)
            {
                masterConfig.cpol = kLPSPI_ClockPolarityActiveLow;
                masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge;
            }
            else
            {
                slaveConfig.cpol = kLPSPI_ClockPolarityActiveLow;
                slaveConfig.cpha = kLPSPI_ClockPhaseFirstEdge;
            }
            break;
        case ARM_SPI_CPOL1_CPHA1: /* Clock Polarity 1, Clock Phase 1*/
            if (isMaster)
            {
                masterConfig.cpol = kLPSPI_ClockPolarityActiveLow;
                masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge;
            }
            else
            {
                slaveConfig.cpol = kLPSPI_ClockPolarityActiveLow;
                slaveConfig.cpha = kLPSPI_ClockPhaseSecondEdge;
            }
            break;
        default:
            /* Avoid MISRA 16.4 violations. */
            break;
    }

    if ((control & (uint32_t)ARM_SPI_DATA_BITS_Msk) != 0U) /* Number of Data bits */
    {
        if ((((control & (uint32_t)ARM_SPI_DATA_BITS_Msk) >> ARM_SPI_DATA_BITS_Pos) >= 8UL))
        {
            if (isMaster)
            {
                masterConfig.bitsPerFrame = ((control & ARM_SPI_DATA_BITS_Msk) >> ARM_SPI_DATA_BITS_Pos);
            }
            else
            {
                slaveConfig.bitsPerFrame = ((control & ARM_SPI_DATA_BITS_Msk) >> ARM_SPI_DATA_BITS_Pos);
            }
        }
        else
        {
            return ARM_SPI_ERROR_DATA_BITS;
        }
    }

    switch (control & (uint32_t)ARM_SPI_BIT_ORDER_Msk)
    {
        case ARM_SPI_LSB_MSB: /* SPI Bit order from LSB to MSB */
            if (isMaster)
            {
                masterConfig.direction = kLPSPI_LsbFirst;
            }
            else
            {
                slaveConfig.direction = kLPSPI_LsbFirst;
            }
            break;
        case ARM_SPI_MSB_LSB: /* SPI Bit order from MSB to LSB */
            if (isMaster)
            {
                masterConfig.direction = kLPSPI_MsbFirst;
            }
            else
            {
                slaveConfig.direction = kLPSPI_MsbFirst;
            }
            break;
        default:
            /* Avoid MISRA 16.4 violations. */
            break;
    }

    if (isMaster)
    {
        /* The SPI slave select is controlled by hardware, the other mode is not supported by current driver. */
        switch (control & (uint32_t)ARM_SPI_SS_MASTER_MODE_Msk)
        {
            case ARM_SPI_SS_MASTER_UNUSED:
                break;
            case ARM_SPI_SS_MASTER_SW:
                break;
            case ARM_SPI_SS_MASTER_HW_OUTPUT:
                break;
            case ARM_SPI_SS_MASTER_HW_INPUT:
                break;
            default:
                /* Avoid MISRA 16.4 violations. */
                break;
        }
    }
    else
    {
        /* The SPI slave select is controlled by hardware, the other mode is not supported by current driver. */
        switch (control & (uint32_t)ARM_SPI_SS_SLAVE_MODE_Msk)
        {
            case ARM_SPI_SS_SLAVE_HW:
                break;
            case ARM_SPI_SS_SLAVE_SW:
                break;
            default:
                /* Avoid MISRA 16.4 violations. */
                break;
        }
    }

    /* LPSPI Init*/
    if (isMaster)
    {
        if (((*isConfigured) & (uint8_t)SPI_FLAG_CONFIGURED) != 0U)
        {
            LPSPI_Deinit(resource->base);
        }
        LPSPI_MasterInit(resource->base, &masterConfig, resource->GetFreq());
        *isConfigured |= (uint8_t)SPI_FLAG_CONFIGURED;
    }
    else
    {
        if (((*isConfigured) & (uint8_t)SPI_FLAG_CONFIGURED) != 0U)
        {
            LPSPI_Deinit(resource->base);
        }
        LPSPI_SlaveInit(resource->base, &slaveConfig);
        *isConfigured |= (uint8_t)SPI_FLAG_CONFIGURED;
    }

    return ARM_DRIVER_OK;
}

static void LPSPI_SetTransferConfigFlags(bool isMaster, uint32_t instance, lpspi_transfer_t *xfer)
{
    if (isMaster)
    {
        /* Set default config flag */
        xfer->configFlags = (uint32_t)kLPSPI_MasterPcs0 | (uint32_t)kLPSPI_MasterPcsContinuous;
#if (defined(RTE_SPI0_MASTER_PCS_PIN_SEL))
        if (0U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI0_MASTER_PCS_PIN_SEL | (uint32_t)kLPSPI_MasterPcsContinuous;
        }
#endif /* LPSPI0 PCS pin configuration */
#if (defined(RTE_SPI1_MASTER_PCS_PIN_SEL))
        if (1U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI1_MASTER_PCS_PIN_SEL | (uint32_t)kLPSPI_MasterPcsContinuous;
        }
#endif /* LPSPI1 PCS pin configuration */
#if (defined(RTE_SPI2_MASTER_PCS_PIN_SEL))
        if (2U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI2_MASTER_PCS_PIN_SEL | (uint32_t)kLPSPI_MasterPcsContinuous;
        }
#endif /* LPSPI2 PCS pin configuration */
#if (defined(RTE_SPI3_MASTER_PCS_PIN_SEL))
        if (3U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI3_MASTER_PCS_PIN_SEL | (uint32_t)kLPSPI_MasterPcsContinuous;
        }
#endif /* LPSPI3 PCS pin configuration */
#if (defined(RTE_SPI4_MASTER_PCS_PIN_SEL))
        if (4U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI4_MASTER_PCS_PIN_SEL | (uint32_t)kLPSPI_MasterPcsContinuous;
        }
#endif /* LPSPI4 PCS pin configuration */
#if (defined(RTE_SPI5_MASTER_PCS_PIN_SEL))
        if (5U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI5_MASTER_PCS_PIN_SEL | (uint32_t)kLPSPI_MasterPcsContinuous;
        }
#endif /* LPSPI5 PCS pin configuration */
    }
    else
    {
        /* Set default config flag */
        xfer->configFlags = (uint32_t)kLPSPI_SlavePcs0;
#if (defined(RTE_SPI0_SLAVE_PCS_PIN_SEL))
        if (0U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI0_SLAVE_PCS_PIN_SEL;
        }
#endif /* LPSPI0 PCS pin configuration */
#if (defined(RTE_SPI1_SLAVE_PCS_PIN_SEL))
        if (1U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI1_SLAVE_PCS_PIN_SEL;
        }
#endif /* LPSPI1 PCS pin configuration */
#if (defined(RTE_SPI2_SLAVE_PCS_PIN_SEL))
        if (2U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI2_SLAVE_PCS_PIN_SEL;
        }
#endif /* LPSPI2 PCS pin configuration */
#if (defined(RTE_SPI3_SLAVE_PCS_PIN_SEL))
        if (3U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI3_SLAVE_PCS_PIN_SEL;
        }
#endif /* LPSPI3 PCS pin configuration */
#if (defined(RTE_SPI4_SLAVE_PCS_PIN_SEL))
        if (4U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI4_SLAVE_PCS_PIN_SEL;
        }
#endif /* LPSPI4 PCS pin configuration */
#if (defined(RTE_SPI5_SLAVE_PCS_PIN_SEL))
        if (5U == instance)
        {
            xfer->configFlags = (uint32_t)RTE_SPI5_SLAVE_PCS_PIN_SEL;
        }
#endif /* LPSPI5 PCS pin configuration */
    }
}

static ARM_DRIVER_VERSION LPSPIx_GetVersion(void)
{
    return s_lpspiDriverVersion;
}

static ARM_SPI_CAPABILITIES LPSPIx_GetCapabilities(void)
{
    return s_lpspiDriverCapabilities;
}

#endif

#if ((defined(RTE_SPI0_DMA_EN) && RTE_SPI0_DMA_EN) || (defined(RTE_SPI1_DMA_EN) && RTE_SPI1_DMA_EN) ||     \
     (defined(RTE_SPI2_DMA_EN) && RTE_SPI2_DMA_EN) || (defined(RTE_SPI3_DMA_EN) && RTE_SPI3_DMA_EN) ||     \
     (defined(RTE_SPI4_DMA_EN) && RTE_SPI4_DMA_EN) || (defined(RTE_SPI5_DMA_EN) && RTE_SPI5_DMA_EN) ||     \
     (defined(RTE_SPI6_DMA_EN) && RTE_SPI6_DMA_EN) || (defined(RTE_SPI7_DMA_EN) && RTE_SPI7_DMA_EN) ||     \
     (defined(RTE_SPI8_DMA_EN) && RTE_SPI8_DMA_EN) || (defined(RTE_SPI9_DMA_EN) && RTE_SPI9_DMA_EN) ||     \
     (defined(RTE_SPI10_DMA_EN) && RTE_SPI10_DMA_EN) || (defined(RTE_SPI11_DMA_EN) && RTE_SPI11_DMA_EN) || \
     (defined(RTE_SPI12_DMA_EN) && RTE_SPI12_DMA_EN) || (defined(RTE_SPI13_DMA_EN) && RTE_SPI13_DMA_EN) || \
     (defined(RTE_SPI14_DMA_EN) && RTE_SPI14_DMA_EN) || (defined(RTE_SPI15_DMA_EN) && RTE_SPI15_DMA_EN) || \
     (defined(RTE_SPI16_DMA_EN) && RTE_SPI16_DMA_EN) || (defined(RTE_SPI17_DMA_EN) && RTE_SPI17_DMA_EN) || \
     (defined(RTE_SPI18_DMA_EN) && RTE_SPI18_DMA_EN) || (defined(RTE_SPI19_DMA_EN) && RTE_SPI19_DMA_EN) || \
     (defined(RTE_SPI20_DMA_EN) && RTE_SPI20_DMA_EN))

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static void KSDK_LPSPI_MasterEdmaCallback(LPSPI_Type *base,
                                          lpspi_master_edma_handle_t *handle,
                                          status_t status,
                                          void *userData)
{
    uint32_t event = 0U;

    if (kStatus_Success == status)
    {
        event = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    }
    else if (kStatus_LPSPI_OutOfRange == status)
    {
        event = ARM_SPI_EVENT_DATA_LOST;
    }
    else
    {
        /* Avoid MISRA 15.7 violations. */
    }
    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_SPI_SignalEvent_t)userData)(event);
    }
}
static void KSDK_LPSPI_SlaveEdmaCallback(LPSPI_Type *base,
                                         lpspi_slave_edma_handle_t *handle,
                                         status_t status,
                                         void *userData)
{
    uint32_t event = 0U;

    if (kStatus_Success == status)
    {
        event = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    }
    else if (kStatus_LPSPI_OutOfRange == status)
    {
        event = ARM_SPI_EVENT_DATA_LOST;
    }
    else
    {
        /* Avoid MISRA 15.7 violations. */
    }
    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_SPI_SignalEvent_t)userData)(event);
    }
}

static int32_t LPSPI_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event, cmsis_lpspi_edma_driver_state_t *lpspi)
{
    if (0U == (lpspi->flags & (uint8_t)SPI_FLAG_INIT))
    {
        lpspi->cb_event = cb_event;
        lpspi->flags    = (uint8_t)SPI_FLAG_INIT;
    }
    return ARM_DRIVER_OK;
}

static int32_t LPSPI_EdmaUninitialize(cmsis_lpspi_edma_driver_state_t *lpspi)
{
    lpspi->flags = (uint8_t)SPI_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPSPI_EdmaPowerControl(ARM_POWER_STATE state, cmsis_lpspi_edma_driver_state_t *lpspi)
{
    cmsis_lpspi_edma_resource_t *dmaResource = lpspi->dmaResource;
    int32_t result                           = ARM_DRIVER_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpspi->flags & (uint8_t)SPI_FLAG_POWER) != 0U)
            {
                LPSPI_Deinit(lpspi->resource->base);
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
                DMAMUX_DisableChannel(lpspi->dmaResource->rxDmamuxBase, lpspi->dmaResource->rxEdmaChannel);
                DMAMUX_DisableChannel(lpspi->dmaResource->txDmamuxBase, lpspi->dmaResource->txEdmaChannel);
#endif
                lpspi->flags = (uint8_t)SPI_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
        {
            if (lpspi->flags == (uint8_t)SPI_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpspi->flags & (uint8_t)SPI_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }
            /* Enable Clock gate */
            (void)CLOCK_EnableClock(s_lpspiClock[lpspi->resource->instance]);

            (void)memset(lpspi->edmaRxRegToRxDataHandle, 0, sizeof(edma_handle_t));
            (void)memset(lpspi->edmaTxDataToTxRegHandle, 0, sizeof(edma_handle_t));

            EDMA_CreateHandle(lpspi->edmaRxRegToRxDataHandle, dmaResource->rxEdmaBase, dmaResource->rxEdmaChannel);
            EDMA_CreateHandle(lpspi->edmaTxDataToTxRegHandle, dmaResource->txEdmaBase, dmaResource->txEdmaChannel);
#if defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
            EDMA_SetChannelMux(dmaResource->txEdmaBase, dmaResource->txEdmaChannel, (int32_t)dmaResource->txDmaRequest);
            EDMA_SetChannelMux(dmaResource->rxEdmaBase, dmaResource->rxEdmaChannel, (int32_t)dmaResource->rxDmaRequest);
#endif

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
            DMAMUX_SetSource(dmaResource->rxDmamuxBase, dmaResource->rxEdmaChannel, (int32_t)dmaResource->rxDmaRequest);
            DMAMUX_EnableChannel(dmaResource->rxDmamuxBase, dmaResource->rxEdmaChannel);

            DMAMUX_SetSource(dmaResource->txDmamuxBase, dmaResource->txEdmaChannel, (int32_t)dmaResource->txDmaRequest);
            DMAMUX_EnableChannel(dmaResource->txDmamuxBase, dmaResource->txEdmaChannel);
#endif
            lpspi->flags |= (uint8_t)SPI_FLAG_POWER;
            break;
        }
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t LPSPI_EdmaSend(const void *data, uint32_t num, cmsis_lpspi_edma_driver_state_t *lpspi)
{
    int32_t ret;
    status_t status;
    lpspi_transfer_t xfer = {0};
    uint32_t datawidth    = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    uint32_t bytesPerFrame = ((datawidth + 8U) / 8U);

    if (num == 0U)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    uint32_t tmp = UINT32_MAX / num;
    if (bytesPerFrame > tmp)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    xfer.rxData   = NULL;
    xfer.txData   = (uint8_t *)data;
    xfer.dataSize = num * bytesPerFrame;

    LPSPI_SetTransferConfigFlags(LPSPI_IsMaster(lpspi->resource->base), lpspi->resource->instance, &xfer);

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        status = LPSPI_MasterTransferEDMA(lpspi->resource->base, &(lpspi->handle->masterHandle), &xfer);
    }
    else
    {
        status = LPSPI_SlaveTransferEDMA(lpspi->resource->base, &(lpspi->handle->slaveHandle), &xfer);
    }

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPSPI_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPSPI_EdmaReceive(void *data, uint32_t num, cmsis_lpspi_edma_driver_state_t *lpspi)
{
    int32_t ret;
    status_t status;
    lpspi_transfer_t xfer = {0};
    uint32_t datawidth    = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    uint32_t bytesPerFrame = ((datawidth + 8U) / 8U);

    if (num == 0U)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    uint32_t tmp = UINT32_MAX / num;
    if (bytesPerFrame > tmp)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    xfer.txData   = NULL;
    xfer.rxData   = (uint8_t *)data;
    xfer.dataSize = num * bytesPerFrame;

    LPSPI_SetTransferConfigFlags(LPSPI_IsMaster(lpspi->resource->base), lpspi->resource->instance, &xfer);

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        status = LPSPI_MasterTransferEDMA(lpspi->resource->base, &(lpspi->handle->masterHandle), &xfer);
    }
    else
    {
        status = LPSPI_SlaveTransferEDMA(lpspi->resource->base, &(lpspi->handle->slaveHandle), &xfer);
    }

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPSPI_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPSPI_EdmaTransfer(const void *data_out,
                                  void *data_in,
                                  uint32_t num,
                                  cmsis_lpspi_edma_driver_state_t *lpspi)
{
    int32_t ret;
    status_t status;
    lpspi_transfer_t xfer = {0};
    uint32_t datawidth    = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    uint32_t bytesPerFrame = ((datawidth + 8U) / 8U);

    if (num == 0U)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    uint32_t tmp = UINT32_MAX / num;
    if (bytesPerFrame > tmp)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    xfer.txData   = (uint8_t *)data_out;
    xfer.rxData   = (uint8_t *)data_in;
    xfer.dataSize = num * bytesPerFrame;

    LPSPI_SetTransferConfigFlags(LPSPI_IsMaster(lpspi->resource->base), lpspi->resource->instance, &xfer);

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        status = LPSPI_MasterTransferEDMA(lpspi->resource->base, &(lpspi->handle->masterHandle), &xfer);
    }
    else
    {
        status = LPSPI_SlaveTransferEDMA(lpspi->resource->base, &(lpspi->handle->slaveHandle), &xfer);
    }

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPSPI_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}
static uint32_t LPSPI_EdmaGetCount(cmsis_lpspi_edma_driver_state_t *lpspi)
{
    uint32_t cnt;
    size_t bytes;
    uint32_t datawidth = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        bytes = (uint32_t)lpspi->handle->masterHandle.nbytes *
                EDMA_GetRemainingMajorLoopCount(lpspi->dmaResource->rxEdmaBase, lpspi->dmaResource->rxEdmaChannel);
        cnt = lpspi->handle->masterHandle.totalByteCount - bytes;
    }
    else
    {
        bytes = (uint32_t)lpspi->handle->masterHandle.nbytes *
                EDMA_GetRemainingMajorLoopCount(lpspi->dmaResource->rxEdmaBase, lpspi->dmaResource->rxEdmaChannel);
        cnt = lpspi->handle->slaveHandle.totalByteCount - bytes;
    }
    cnt /= ((datawidth + 8U) / 8U);
    return cnt;
}

static int32_t LPSPI_EdmaControl(uint32_t control, uint32_t arg, cmsis_lpspi_edma_driver_state_t *lpspi)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    if (0U == (lpspi->flags & (uint8_t)SPI_FLAG_POWER))
    {
        return ARM_DRIVER_ERROR;
    }

    switch (control & ARM_SPI_CONTROL_Msk)
    {
        case ARM_SPI_MODE_INACTIVE:
            LPSPI_Enable(lpspi->resource->base, false);
            break;
        case ARM_SPI_MODE_MASTER: /* SPI Master (Output on SOUT, Input on SIN); arg = Bus Speed in bps */
        {
            LPSPI_MasterTransferCreateHandleEDMA(lpspi->resource->base, &(lpspi->handle->masterHandle),
                                                 KSDK_LPSPI_MasterEdmaCallback, (void *)lpspi->cb_event,
                                                 lpspi->edmaRxRegToRxDataHandle, lpspi->edmaTxDataToTxRegHandle);

            lpspi->baudRate_Bps = arg;
            isContinue          = true;
            break;
        }
        case ARM_SPI_MODE_SLAVE: /* SPI Slave  (Output on SOUT, Input on SIN) */
        {
            LPSPI_SlaveTransferCreateHandleEDMA(lpspi->resource->base, &(lpspi->handle->slaveHandle),
                                                KSDK_LPSPI_SlaveEdmaCallback, (void *)lpspi->cb_event,
                                                lpspi->edmaRxRegToRxDataHandle, lpspi->edmaTxDataToTxRegHandle);
            isContinue = true;
            break;
        }
        case ARM_SPI_SET_BUS_SPEED: /* Get Bus Speed in bps */
        {
            uint32_t tcrPrescaleValue = 0;
            LPSPI_Enable(lpspi->resource->base, false);

            if (!LPSPI_IsMaster(lpspi->resource->base))
            {
                result = ARM_DRIVER_ERROR_UNSUPPORTED;
                break;
            }

            if (0UL ==
                LPSPI_MasterSetBaudRate(lpspi->resource->base, arg, lpspi->resource->GetFreq(), &tcrPrescaleValue))
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            LPSPI_Enable(lpspi->resource->base, true);
            lpspi->baudRate_Bps = arg;
            break;
        }

        case ARM_SPI_GET_BUS_SPEED: /* Set Bus Speed in bps; arg = value */
            if (!LPSPI_IsMaster(lpspi->resource->base))
            {
                result = ARM_DRIVER_ERROR_UNSUPPORTED;
                break;
            }
            result = (int32_t)lpspi->baudRate_Bps;
            break;
        case ARM_SPI_CONTROL_SS: /* Control Slave Select; arg = 0:inactive, 1:active  */
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;

        case ARM_SPI_ABORT_TRANSFER: /* Abort current data transfer */
            if (LPSPI_IsMaster(lpspi->resource->base))
            {
                LPSPI_MasterTransferAbortEDMA(lpspi->resource->base, &(lpspi->handle->masterHandle));
            }
            else
            {
                LPSPI_SlaveTransferAbortEDMA(lpspi->resource->base, &(lpspi->handle->slaveHandle));
            }
            result = ARM_DRIVER_OK;
            break;

        case ARM_SPI_SET_DEFAULT_TX_VALUE: /* Set default Transmit value; arg = value */
            if (arg > 0xFFU)
            {
                result = ARM_DRIVER_ERROR_PARAMETER;
                break;
            }
            LPSPI_SetDummyData(lpspi->resource->base, (uint8_t)arg);
            result = ARM_DRIVER_OK;
            break;

        case ARM_SPI_MODE_MASTER_SIMPLEX: /* SPI Master (Output/Input on SOUT); arg = Bus Speed in bps */
        {
            LPSPI_MasterTransferCreateHandleEDMA(lpspi->resource->base, &(lpspi->handle->masterHandle),
                                                 KSDK_LPSPI_MasterEdmaCallback, (void *)lpspi->cb_event,
                                                 lpspi->edmaRxRegToRxDataHandle, lpspi->edmaTxDataToTxRegHandle);

            lpspi->baudRate_Bps = arg;
            isContinue          = true;
            break;
        }

        case ARM_SPI_MODE_SLAVE_SIMPLEX: /* SPI Slave  (Output/Input on SIN) */
        {
            LPSPI_SlaveTransferCreateHandleEDMA(lpspi->resource->base, &(lpspi->handle->slaveHandle),
                                                KSDK_LPSPI_SlaveEdmaCallback, (void *)lpspi->cb_event,
                                                lpspi->edmaRxRegToRxDataHandle, lpspi->edmaTxDataToTxRegHandle);
            isContinue = true;
            break;
        }

        default:
            isContinue = true;
            break;
    }
    if (isContinue)
    {
        result = LPSPI_CommonControl(control, arg, lpspi->resource, &lpspi->flags);
    }

    return result;
}

static ARM_SPI_STATUS LPSPI_EdmaGetStatus(cmsis_lpspi_edma_driver_state_t *lpspi)
{
    ARM_SPI_STATUS stat = {0};

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        stat.busy      = ((uint8_t)kLPSPI_Busy == lpspi->handle->masterHandle.state) ? (1U) : (0U);
        stat.data_lost = ((uint8_t)kLPSPI_Error == lpspi->handle->masterHandle.state) ? (1U) : (0U);
    }
    else
    {
        stat.busy      = ((uint8_t)kLPSPI_Busy == lpspi->handle->slaveHandle.state) ? (1U) : (0U);
        stat.data_lost = ((uint8_t)kLPSPI_Error == lpspi->handle->slaveHandle.state) ? (1U) : (0U);
    }
    stat.mode_fault = 0U;
    stat.reserved   = 0U;

    return stat;
}
#endif /* defined(FSL_FEATURE_SOC_EDMA_COUNT) */

#endif

#if ((defined(RTE_SPI0) && RTE_SPI0 && !RTE_SPI0_DMA_EN) || (defined(RTE_SPI1) && RTE_SPI1 && !RTE_SPI1_DMA_EN) || \
     (defined(RTE_SPI2) && RTE_SPI2 && !RTE_SPI2_DMA_EN) || (defined(RTE_SPI3) && RTE_SPI3 && !RTE_SPI3_DMA_EN) || \
     (defined(RTE_SPI4) && RTE_SPI4 && !RTE_SPI4_DMA_EN) || (defined(RTE_SPI5) && RTE_SPI5 && !RTE_SPI5_DMA_EN) || \
     (defined(RTE_SPI6) && RTE_SPI6 && !RTE_SPI6_DMA_EN) || (defined(RTE_SPI7) && RTE_SPI7 && !RTE_SPI7_DMA_EN) || \
     (defined(RTE_SPI8) && RTE_SPI8 && !RTE_SPI8_DMA_EN) || (defined(RTE_SPI9) && RTE_SPI9 && !RTE_SPI9_DMA_EN) || \
     (defined(RTE_SPI10) && RTE_SPI10 && !RTE_SPI10_DMA_EN) ||                                                     \
     (defined(RTE_SPI11) && RTE_SPI11 && !RTE_SPI11_DMA_EN) ||                                                     \
     (defined(RTE_SPI12) && RTE_SPI12 && !RTE_SPI12_DMA_EN) ||                                                     \
     (defined(RTE_SPI13) && RTE_SPI13 && !RTE_SPI13_DMA_EN) ||                                                     \
     (defined(RTE_SPI14) && RTE_SPI14 && !RTE_SPI14_DMA_EN) ||                                                     \
     (defined(RTE_SPI15) && RTE_SPI15 && !RTE_SPI15_DMA_EN) ||                                                     \
     (defined(RTE_SPI16) && RTE_SPI16 && !RTE_SPI16_DMA_EN) ||                                                     \
     (defined(RTE_SPI17) && RTE_SPI17 && !RTE_SPI17_DMA_EN) ||                                                     \
     (defined(RTE_SPI18) && RTE_SPI18 && !RTE_SPI18_DMA_EN) ||                                                     \
     (defined(RTE_SPI19) && RTE_SPI19 && !RTE_SPI19_DMA_EN) || (defined(RTE_SPI20) && RTE_SPI20 && !RTE_SPI20_DMA_EN))

static void KSDK_LPSPI_MasterInterruptCallback(LPSPI_Type *base,
                                               lpspi_master_handle_t *handle,
                                               status_t status,
                                               void *userData)
{
    uint32_t event = 0U;

    if (kStatus_Success == status)
    {
        event = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    }
    else if (kStatus_LPSPI_Error == status)
    {
        event = ARM_SPI_EVENT_DATA_LOST;
    }
    else
    {
        /* Avoid MISRA 15.7 violations. */
    }
    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_SPI_SignalEvent_t)userData)(event);
    }
}

static void KSDK_LPSPI_SlaveInterruptCallback(LPSPI_Type *base,
                                              lpspi_slave_handle_t *handle,
                                              status_t status,
                                              void *userData)
{
    uint32_t event = 0U;

    if (kStatus_Success == status)
    {
        event = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    }
    if (kStatus_LPSPI_Error == status)
    {
        event = ARM_SPI_EVENT_DATA_LOST;
    }
    else
    {
        /* Avoid MISRA 16.4 violations. */
    }
    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_SPI_SignalEvent_t)userData)(event);
    }
}

static int32_t LPSPI_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event, cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    if (0U == (lpspi->flags & (uint8_t)SPI_FLAG_INIT))
    {
        lpspi->cb_event = cb_event;
        lpspi->flags    = (uint8_t)SPI_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t LPSPI_InterruptUninitialize(cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    lpspi->flags = (uint8_t)SPI_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPSPI_InterruptPowerControl(ARM_POWER_STATE state, cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    int32_t result = ARM_DRIVER_OK;
    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpspi->flags & (uint8_t)SPI_FLAG_POWER) != 0U)
            {
                LPSPI_Deinit(lpspi->resource->base);
                lpspi->flags = (uint8_t)SPI_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
            if (lpspi->flags == (uint8_t)SPI_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpspi->flags & (uint8_t)SPI_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            (void)CLOCK_EnableClock(s_lpspiClock[lpspi->resource->instance]);
            lpspi->flags |= (uint8_t)SPI_FLAG_POWER;

            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t LPSPI_InterruptSend(const void *data, uint32_t num, cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    int32_t ret;
    status_t status;
    lpspi_transfer_t xfer = {0};
    uint32_t datawidth    = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    uint32_t bytesPerFrame = ((datawidth + 8U) / 8U);

    if (num == 0U)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    uint32_t tmp = UINT32_MAX / num;
    if (bytesPerFrame > tmp)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    xfer.rxData   = NULL;
    xfer.txData   = (uint8_t *)data;
    xfer.dataSize = num * bytesPerFrame;

    LPSPI_SetTransferConfigFlags(LPSPI_IsMaster(lpspi->resource->base), lpspi->resource->instance, &xfer);

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        status = LPSPI_MasterTransferNonBlocking(lpspi->resource->base, &(lpspi->handle->masterHandle), &xfer);
    }
    else
    {
        status = LPSPI_SlaveTransferNonBlocking(lpspi->resource->base, &(lpspi->handle->slaveHandle), &xfer);
    }

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPSPI_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPSPI_InterruptReceive(void *data, uint32_t num, cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    int32_t ret;
    status_t status;
    lpspi_transfer_t xfer = {0};
    uint32_t datawidth    = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    uint32_t bytesPerFrame = ((datawidth + 8U) / 8U);

    if (num == 0U)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    uint32_t tmp = UINT32_MAX / num;
    if (bytesPerFrame > tmp)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    xfer.txData   = NULL;
    xfer.rxData   = (uint8_t *)data;
    xfer.dataSize = num * bytesPerFrame;

    LPSPI_SetTransferConfigFlags(LPSPI_IsMaster(lpspi->resource->base), lpspi->resource->instance, &xfer);

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        status = LPSPI_MasterTransferNonBlocking(lpspi->resource->base, &(lpspi->handle->masterHandle), &xfer);
    }
    else
    {
        status = LPSPI_SlaveTransferNonBlocking(lpspi->resource->base, &(lpspi->handle->slaveHandle), &xfer);
    }

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPSPI_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPSPI_InterruptTransfer(const void *data_out,
                                       void *data_in,
                                       uint32_t num,
                                       cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    int32_t ret;
    status_t status;
    lpspi_transfer_t xfer = {0};
    uint32_t datawidth    = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    uint32_t bytesPerFrame = ((datawidth + 8U) / 8U);

    if (num == 0U)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    uint32_t tmp = UINT32_MAX / num;
    if (bytesPerFrame > tmp)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    xfer.txData   = (uint8_t *)data_out;
    xfer.rxData   = (uint8_t *)data_in;
    xfer.dataSize = num * bytesPerFrame;

    LPSPI_SetTransferConfigFlags(LPSPI_IsMaster(lpspi->resource->base), lpspi->resource->instance, &xfer);

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        status = LPSPI_MasterTransferNonBlocking(lpspi->resource->base, &(lpspi->handle->masterHandle), &xfer);
    }
    else
    {
        status = LPSPI_SlaveTransferNonBlocking(lpspi->resource->base, &(lpspi->handle->slaveHandle), &xfer);
    }

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPSPI_Busy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static uint32_t LPSPI_InterruptGetCount(cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    uint32_t cnt;
    uint32_t datawidth = (LPSPI_GetTcr(lpspi->resource->base) & (uint32_t)LPSPI_TCR_FRAMESZ_MASK) >> LPSPI_TCR_FRAMESZ_SHIFT;
    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        cnt = (uint32_t)lpspi->handle->masterHandle.totalByteCount -
              (uint32_t)lpspi->handle->masterHandle.rxRemainingByteCount;
    }
    else
    {
        cnt = (uint32_t)lpspi->handle->slaveHandle.totalByteCount -
              (uint32_t)lpspi->handle->slaveHandle.rxRemainingByteCount;
    }
    cnt /= ((datawidth + 8U) / 8U);

    return cnt;
}

static int32_t LPSPI_InterruptControl(uint32_t control, uint32_t arg, cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    if (0U == (lpspi->flags & (uint8_t)SPI_FLAG_POWER))
    {
        return ARM_DRIVER_ERROR;
    }

    switch (control & ARM_SPI_CONTROL_Msk)
    {
        case ARM_SPI_MODE_INACTIVE:
            LPSPI_Enable(lpspi->resource->base, false);
            break;
        case ARM_SPI_MODE_MASTER: /* SPI Master (Output on SOUT, Input on SIN); arg = Bus Speed in bps */
        {
            LPSPI_MasterTransferCreateHandle(lpspi->resource->base, &(lpspi->handle->masterHandle),
                                             KSDK_LPSPI_MasterInterruptCallback, (void *)lpspi->cb_event);
            lpspi->baudRate_Bps = arg;
            isContinue          = true;
            break;
        }
        case ARM_SPI_MODE_SLAVE: /* SPI Slave  (Output on SOUT, Input on SIN) */
        {
            LPSPI_SlaveTransferCreateHandle(lpspi->resource->base, &(lpspi->handle->slaveHandle),
                                            KSDK_LPSPI_SlaveInterruptCallback, (void *)lpspi->cb_event);
            isContinue = true;
            break;
        }
        case ARM_SPI_SET_BUS_SPEED: /* Set Bus Speed in bps; */
        {
            uint32_t tcrPrescaleValue = 0;
            LPSPI_Enable(lpspi->resource->base, false);

            if (!LPSPI_IsMaster(lpspi->resource->base))
            {
                result = ARM_DRIVER_ERROR_UNSUPPORTED;
                break;
            }
            if (0UL ==
                LPSPI_MasterSetBaudRate(lpspi->resource->base, arg, lpspi->resource->GetFreq(), &tcrPrescaleValue))
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            LPSPI_Enable(lpspi->resource->base, true);
            lpspi->baudRate_Bps = arg;
            break;
        }
        case ARM_SPI_GET_BUS_SPEED: /* Get Bus Speed in bps */
            if (!LPSPI_IsMaster(lpspi->resource->base))
            {
                result = ARM_DRIVER_ERROR_UNSUPPORTED;
                break;
            }
            result = (int32_t)(lpspi->baudRate_Bps);
            break;
        case ARM_SPI_CONTROL_SS: /* Control Slave Select; arg = 0:inactive, 1:active  */
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_SPI_ABORT_TRANSFER: /* Abort current data transfer */

            if (LPSPI_IsMaster(lpspi->resource->base))
            {
                LPSPI_MasterTransferAbort(lpspi->resource->base, &(lpspi->handle->masterHandle));
            }
            else
            {
                LPSPI_SlaveTransferAbort(lpspi->resource->base, &(lpspi->handle->slaveHandle));
            }
            break;

        case ARM_SPI_SET_DEFAULT_TX_VALUE: /* Set default Transmit value; arg = value */
            if (LPSPI_IsMaster(lpspi->resource->base))
            {
                if (arg > 0xFFU)
                {
                    result = ARM_DRIVER_ERROR_PARAMETER;
                    break;
                }
                LPSPI_SetDummyData(lpspi->resource->base, (uint8_t)arg);
            }
            else
            {
                /* Mode is not supported by current driver.
                 * In slave mode, if the tx buffer is NULL, the output pin will keep tristated.
                 */
                result = ARM_DRIVER_ERROR_UNSUPPORTED;
            }
            break;

        case ARM_SPI_MODE_MASTER_SIMPLEX: /* SPI Master (Output/Input on SOUT); arg = Bus Speed in bps */
        {
            LPSPI_MasterTransferCreateHandle(lpspi->resource->base, &(lpspi->handle->masterHandle),
                                             KSDK_LPSPI_MasterInterruptCallback, (void *)lpspi->cb_event);
            lpspi->baudRate_Bps = arg;
            isContinue          = true;
            break;
        }
        case ARM_SPI_MODE_SLAVE_SIMPLEX: /* SPI Slave  (Output/Input on SIN) */
        {
            LPSPI_SlaveTransferCreateHandle(lpspi->resource->base, &(lpspi->handle->slaveHandle),
                                            KSDK_LPSPI_SlaveInterruptCallback, (void *)lpspi->cb_event);
            isContinue = true;
            break;
        }

        default:
            isContinue = true;
            break;
    }
    if (isContinue)
    {
        result = LPSPI_CommonControl(control, lpspi->baudRate_Bps, lpspi->resource, &lpspi->flags);
    }
    return result;
}

static ARM_SPI_STATUS LPSPI_InterruptGetStatus(cmsis_lpspi_interrupt_driver_state_t *lpspi)
{
    ARM_SPI_STATUS stat = {0};

    if (LPSPI_IsMaster(lpspi->resource->base))
    {
        stat.busy      = ((uint8_t)kLPSPI_Busy == lpspi->handle->masterHandle.state) ? (1U) : (0U);
        stat.data_lost = ((uint8_t)kLPSPI_Error == lpspi->handle->masterHandle.state) ? (1U) : (0U);
    }
    else
    {
        stat.busy      = ((uint8_t)kLPSPI_Busy == lpspi->handle->slaveHandle.state) ? (1U) : (0U);
        stat.data_lost = ((uint8_t)kLPSPI_Error == lpspi->handle->slaveHandle.state) ? (1U) : (0U);
    }
    stat.mode_fault = 0U;
    stat.reserved   = 0U;

    return stat;
}

#endif

#if (defined(LPSPI0) || defined(LPSPI_0)) && defined(RTE_SPI0) && RTE_SPI0

/* User needs to provide the implementation for LPSPI0_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI0_GetFreq(void);

#if defined(LPSPI0)
static cmsis_lpspi_resource_t LPSPI0_Resource = {LPSPI0, 0, LPSPI0_GetFreq};
#elif defined(LPSPI_0)
static cmsis_lpspi_resource_t LPSPI0_Resource = {LPSPI_0, 0, LPSPI0_GetFreq};
#endif

#if defined(RTE_SPI0_DMA_EN) && RTE_SPI0_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI0_EdmaResource = {
    RTE_SPI0_DMA_TX_DMA_BASE,    RTE_SPI0_DMA_TX_CH,          (uint16_t)RTE_SPI0_DMA_TX_PERI_SEL,
    RTE_SPI0_DMA_RX_DMA_BASE,    RTE_SPI0_DMA_RX_CH,          (uint16_t)RTE_SPI0_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI0_DMA_TX_DMAMUX_BASE, RTE_SPI0_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI0_EdmaHandle);
static edma_handle_t LPSPI0_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI0_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi0_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI0_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI0_EdmaDriverState = {
#endif
    &LPSPI0_Resource,
    &LPSPI0_EdmaResource,
    &LPSPI0_EdmaHandle,
    &LPSPI0_EdmaRxRegToRxDataHandle,
    &LPSPI0_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI0_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI0_PIN_INIT
    RTE_SPI0_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI0_EdmaDriverState);
}

static int32_t LPSPI0_EdmaUninitialize(void)
{
#ifdef RTE_SPI0_PIN_DEINIT
    RTE_SPI0_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI0_EdmaDriverState);
}

static int32_t LPSPI0_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI0_EdmaDriverState);
}

static int32_t LPSPI0_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI0_EdmaDriverState);
}

static int32_t LPSPI0_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI0_EdmaDriverState);
}

static int32_t LPSPI0_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI0_EdmaDriverState);
}

static uint32_t LPSPI0_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI0_EdmaDriverState);
}

static int32_t LPSPI0_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI0_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI0_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI0_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI0_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi0_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI0_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI0_InterruptDriverState = {
#endif
    &LPSPI0_Resource,
    &LPSPI0_Handle,
};

static int32_t LPSPI0_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI0_PIN_INIT
    RTE_SPI0_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI0_InterruptDriverState);
}

static int32_t LPSPI0_InterruptUninitialize(void)
{
#ifdef RTE_SPI0_PIN_DEINIT
    RTE_SPI0_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI0_InterruptDriverState);
}

static int32_t LPSPI0_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI0_InterruptDriverState);
}

static int32_t LPSPI0_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI0_InterruptDriverState);
}

static int32_t LPSPI0_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI0_InterruptDriverState);
}

static int32_t LPSPI0_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI0_InterruptDriverState);
}

static uint32_t LPSPI0_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI0_InterruptDriverState);
}

static int32_t LPSPI0_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI0_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI0_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI0_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI0 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI0_DMA_EN) && RTE_SPI0_DMA_EN
    LPSPI0_EdmaInitialize, LPSPI0_EdmaUninitialize, LPSPI0_EdmaPowerControl, LPSPI0_EdmaSend,     LPSPI0_EdmaReceive,
    LPSPI0_EdmaTransfer,   LPSPI0_EdmaGetCount,     LPSPI0_EdmaControl,      LPSPI0_EdmaGetStatus
#else
    LPSPI0_InterruptInitialize, LPSPI0_InterruptUninitialize, LPSPI0_InterruptPowerControl, LPSPI0_InterruptSend,
    LPSPI0_InterruptReceive,    LPSPI0_InterruptTransfer,     LPSPI0_InterruptGetCount,     LPSPI0_InterruptControl,
    LPSPI0_InterruptGetStatus
#endif
};

#endif /*  LPSPI0  */

#if (defined(LPSPI1) || defined(LPSPI_1)) && defined(RTE_SPI1) && RTE_SPI1

/* User needs to provide the implementation for LPSPI1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI1_GetFreq(void);

#if defined(LPSPI1)
static cmsis_lpspi_resource_t LPSPI1_Resource = {LPSPI1, 1, LPSPI1_GetFreq};
#elif defined(LPSPI_1)
static cmsis_lpspi_resource_t LPSPI1_Resource = {LPSPI_1, 1, LPSPI1_GetFreq};
#endif

#if defined(RTE_SPI1_DMA_EN) && RTE_SPI1_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI1_EdmaResource = {
    RTE_SPI1_DMA_TX_DMA_BASE,    RTE_SPI1_DMA_TX_CH,          (uint16_t)RTE_SPI1_DMA_TX_PERI_SEL,
    RTE_SPI1_DMA_RX_DMA_BASE,    RTE_SPI1_DMA_RX_CH,          (uint16_t)RTE_SPI1_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI1_DMA_TX_DMAMUX_BASE, RTE_SPI1_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI1_EdmaHandle);
static edma_handle_t LPSPI1_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI1_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi1_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI1_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI1_EdmaDriverState = {
#endif
    &LPSPI1_Resource,
    &LPSPI1_EdmaResource,
    &LPSPI1_EdmaHandle,
    &LPSPI1_EdmaRxRegToRxDataHandle,
    &LPSPI1_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI1_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI1_PIN_INIT
    RTE_SPI1_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI1_EdmaDriverState);
}

static int32_t LPSPI1_EdmaUninitialize(void)
{
#ifdef RTE_SPI1_PIN_DEINIT
    RTE_SPI1_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI1_EdmaDriverState);
}

static int32_t LPSPI1_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI1_EdmaDriverState);
}

static int32_t LPSPI1_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI1_EdmaDriverState);
}

static int32_t LPSPI1_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI1_EdmaDriverState);
}

static int32_t LPSPI1_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI1_EdmaDriverState);
}

static uint32_t LPSPI1_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI1_EdmaDriverState);
}

static int32_t LPSPI1_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI1_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI1_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI1_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI1_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi1_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI1_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI1_InterruptDriverState = {
#endif
    &LPSPI1_Resource,
    &LPSPI1_Handle,
};

static int32_t LPSPI1_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI1_PIN_INIT
    RTE_SPI1_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI1_InterruptDriverState);
}

static int32_t LPSPI1_InterruptUninitialize(void)
{
#ifdef RTE_SPI1_PIN_DEINIT
    RTE_SPI1_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI1_InterruptDriverState);
}

static int32_t LPSPI1_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI1_InterruptDriverState);
}

static int32_t LPSPI1_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI1_InterruptDriverState);
}

static int32_t LPSPI1_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI1_InterruptDriverState);
}

static int32_t LPSPI1_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI1_InterruptDriverState);
}

static uint32_t LPSPI1_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI1_InterruptDriverState);
}

static int32_t LPSPI1_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI1_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI1_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI1_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI1 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI1_DMA_EN) && RTE_SPI1_DMA_EN
    LPSPI1_EdmaInitialize, LPSPI1_EdmaUninitialize, LPSPI1_EdmaPowerControl, LPSPI1_EdmaSend,     LPSPI1_EdmaReceive,
    LPSPI1_EdmaTransfer,   LPSPI1_EdmaGetCount,     LPSPI1_EdmaControl,      LPSPI1_EdmaGetStatus
#else
    LPSPI1_InterruptInitialize, LPSPI1_InterruptUninitialize, LPSPI1_InterruptPowerControl, LPSPI1_InterruptSend,
    LPSPI1_InterruptReceive,    LPSPI1_InterruptTransfer,     LPSPI1_InterruptGetCount,     LPSPI1_InterruptControl,
    LPSPI1_InterruptGetStatus
#endif
};

#endif /*  LPSPI1  */

#if (defined(LPSPI2) || defined(LPSPI_2)) && defined(RTE_SPI2) && RTE_SPI2

/* User needs to provide the implementation for LPSPI2_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI2_GetFreq(void);

#if defined(LPSPI2)
static cmsis_lpspi_resource_t LPSPI2_Resource = {LPSPI2, 2, LPSPI2_GetFreq};
#elif defined(LPSPI_2)
static cmsis_lpspi_resource_t LPSPI2_Resource = {LPSPI_2, 2, LPSPI2_GetFreq};
#endif

#if defined(RTE_SPI2_DMA_EN) && RTE_SPI2_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI2_EdmaResource = {
    RTE_SPI2_DMA_TX_DMA_BASE,    RTE_SPI2_DMA_TX_CH,          (uint16_t)RTE_SPI2_DMA_TX_PERI_SEL,
    RTE_SPI2_DMA_RX_DMA_BASE,    RTE_SPI2_DMA_RX_CH,          (uint16_t)RTE_SPI2_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI2_DMA_TX_DMAMUX_BASE, RTE_SPI2_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI2_EdmaHandle);
static edma_handle_t LPSPI2_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI2_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi2_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI2_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI2_EdmaDriverState = {
#endif
    &LPSPI2_Resource,
    &LPSPI2_EdmaResource,
    &LPSPI2_EdmaHandle,
    &LPSPI2_EdmaRxRegToRxDataHandle,
    &LPSPI2_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI2_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI2_PIN_INIT
    RTE_SPI2_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI2_EdmaDriverState);
}

static int32_t LPSPI2_EdmaUninitialize(void)
{
#ifdef RTE_SPI2_PIN_DEINIT
    RTE_SPI2_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI2_EdmaDriverState);
}

static int32_t LPSPI2_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI2_EdmaDriverState);
}

static int32_t LPSPI2_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI2_EdmaDriverState);
}

static int32_t LPSPI2_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI2_EdmaDriverState);
}

static int32_t LPSPI2_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI2_EdmaDriverState);
}

static uint32_t LPSPI2_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI2_EdmaDriverState);
}

static int32_t LPSPI2_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI2_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI2_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI2_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI2_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi2_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI2_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI2_InterruptDriverState = {
#endif
    &LPSPI2_Resource,
    &LPSPI2_Handle,
};

static int32_t LPSPI2_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI2_PIN_INIT
    RTE_SPI2_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI2_InterruptDriverState);
}

static int32_t LPSPI2_InterruptUninitialize(void)
{
#ifdef RTE_SPI2_PIN_DEINIT
    RTE_SPI2_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI2_InterruptDriverState);
}

static int32_t LPSPI2_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI2_InterruptDriverState);
}

static int32_t LPSPI2_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI2_InterruptDriverState);
}

static int32_t LPSPI2_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI2_InterruptDriverState);
}

static int32_t LPSPI2_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI2_InterruptDriverState);
}

static uint32_t LPSPI2_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI2_InterruptDriverState);
}

static int32_t LPSPI2_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI2_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI2_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI2_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI2 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI2_DMA_EN) && RTE_SPI2_DMA_EN
    LPSPI2_EdmaInitialize, LPSPI2_EdmaUninitialize, LPSPI2_EdmaPowerControl, LPSPI2_EdmaSend,     LPSPI2_EdmaReceive,
    LPSPI2_EdmaTransfer,   LPSPI2_EdmaGetCount,     LPSPI2_EdmaControl,      LPSPI2_EdmaGetStatus
#else
    LPSPI2_InterruptInitialize, LPSPI2_InterruptUninitialize, LPSPI2_InterruptPowerControl, LPSPI2_InterruptSend,
    LPSPI2_InterruptReceive,    LPSPI2_InterruptTransfer,     LPSPI2_InterruptGetCount,     LPSPI2_InterruptControl,
    LPSPI2_InterruptGetStatus
#endif
};

#endif /*  LPSPI2  */

#if (defined(LPSPI3) || defined(LPSPI_3)) && defined(RTE_SPI3) && RTE_SPI3

/* User needs to provide the implementation for LPSPI3_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI3_GetFreq(void);

#if defined(LPSPI3)
static cmsis_lpspi_resource_t LPSPI3_Resource = {LPSPI3, 3, LPSPI3_GetFreq};
#elif defined(LPSPI_3)
static cmsis_lpspi_resource_t LPSPI3_Resource = {LPSPI_3, 3, LPSPI3_GetFreq};
#endif

#if defined(RTE_SPI3_DMA_EN) && RTE_SPI3_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI3_EdmaResource = {
    RTE_SPI3_DMA_TX_DMA_BASE,    RTE_SPI3_DMA_TX_CH,          (uint16_t)RTE_SPI3_DMA_TX_PERI_SEL,
    RTE_SPI3_DMA_RX_DMA_BASE,    RTE_SPI3_DMA_RX_CH,          (uint16_t)RTE_SPI3_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI3_DMA_TX_DMAMUX_BASE, RTE_SPI3_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI3_EdmaHandle);
static edma_handle_t LPSPI3_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI3_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi3_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI3_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI3_EdmaDriverState = {
#endif
    &LPSPI3_Resource,
    &LPSPI3_EdmaResource,
    &LPSPI3_EdmaHandle,
    &LPSPI3_EdmaRxRegToRxDataHandle,
    &LPSPI3_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI3_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI3_PIN_INIT
    RTE_SPI3_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI3_EdmaDriverState);
}

static int32_t LPSPI3_EdmaUninitialize(void)
{
#ifdef RTE_SPI3_PIN_DEINIT
    RTE_SPI3_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI3_EdmaDriverState);
}

static int32_t LPSPI3_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI3_EdmaDriverState);
}

static int32_t LPSPI3_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI3_EdmaDriverState);
}

static int32_t LPSPI3_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI3_EdmaDriverState);
}

static int32_t LPSPI3_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI3_EdmaDriverState);
}

static uint32_t LPSPI3_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI3_EdmaDriverState);
}

static int32_t LPSPI3_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI3_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI3_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI3_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI3_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi3_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI3_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI3_InterruptDriverState = {
#endif
    &LPSPI3_Resource,
    &LPSPI3_Handle,
};

static int32_t LPSPI3_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI3_PIN_INIT
    RTE_SPI3_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI3_InterruptDriverState);
}

static int32_t LPSPI3_InterruptUninitialize(void)
{
#ifdef RTE_SPI3_PIN_DEINIT
    RTE_SPI3_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI3_InterruptDriverState);
}

static int32_t LPSPI3_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI3_InterruptDriverState);
}

static int32_t LPSPI3_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI3_InterruptDriverState);
}

static int32_t LPSPI3_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI3_InterruptDriverState);
}

static int32_t LPSPI3_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI3_InterruptDriverState);
}

static uint32_t LPSPI3_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI3_InterruptDriverState);
}

static int32_t LPSPI3_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI3_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI3_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI3_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI3 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI3_DMA_EN) && RTE_SPI3_DMA_EN
    LPSPI3_EdmaInitialize, LPSPI3_EdmaUninitialize, LPSPI3_EdmaPowerControl, LPSPI3_EdmaSend,     LPSPI3_EdmaReceive,
    LPSPI3_EdmaTransfer,   LPSPI3_EdmaGetCount,     LPSPI3_EdmaControl,      LPSPI3_EdmaGetStatus
#else
    LPSPI3_InterruptInitialize, LPSPI3_InterruptUninitialize, LPSPI3_InterruptPowerControl, LPSPI3_InterruptSend,
    LPSPI3_InterruptReceive,    LPSPI3_InterruptTransfer,     LPSPI3_InterruptGetCount,     LPSPI3_InterruptControl,
    LPSPI3_InterruptGetStatus
#endif
};

#endif /*  LPSPI3  */

#if (defined(LPSPI4) || defined(LPSPI_4)) && defined(RTE_SPI4) && RTE_SPI4

/* User needs to provide the implementation for LPSPI4_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI4_GetFreq(void);

#if defined(LPSPI4)
static cmsis_lpspi_resource_t LPSPI4_Resource = {LPSPI4, 4, LPSPI4_GetFreq};
#elif defined(LPSPI_4)
static cmsis_lpspi_resource_t LPSPI4_Resource = {LPSPI_4, 4, LPSPI4_GetFreq};
#endif

#if defined(RTE_SPI4_DMA_EN) && RTE_SPI4_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI4_EdmaResource = {
    RTE_SPI4_DMA_TX_DMA_BASE,    RTE_SPI4_DMA_TX_CH,          (uint16_t)RTE_SPI4_DMA_TX_PERI_SEL,
    RTE_SPI4_DMA_RX_DMA_BASE,    RTE_SPI4_DMA_RX_CH,          (uint16_t)RTE_SPI4_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI4_DMA_TX_DMAMUX_BASE, RTE_SPI4_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI4_EdmaHandle);
static edma_handle_t LPSPI4_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI4_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi4_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI4_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI4_EdmaDriverState = {
#endif
    &LPSPI4_Resource,
    &LPSPI4_EdmaResource,
    &LPSPI4_EdmaHandle,
    &LPSPI4_EdmaRxRegToRxDataHandle,
    &LPSPI4_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI4_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI4_PIN_INIT
    RTE_SPI4_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI4_EdmaDriverState);
}

static int32_t LPSPI4_EdmaUninitialize(void)
{
#ifdef RTE_SPI4_PIN_DEINIT
    RTE_SPI4_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI4_EdmaDriverState);
}

static int32_t LPSPI4_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI4_EdmaDriverState);
}

static int32_t LPSPI4_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI4_EdmaDriverState);
}

static int32_t LPSPI4_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI4_EdmaDriverState);
}

static int32_t LPSPI4_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI4_EdmaDriverState);
}

static uint32_t LPSPI4_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI4_EdmaDriverState);
}

static int32_t LPSPI4_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI4_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI4_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI4_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI4_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi4_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI4_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI4_InterruptDriverState = {
#endif
    &LPSPI4_Resource,
    &LPSPI4_Handle,
};

static int32_t LPSPI4_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI4_PIN_INIT
    RTE_SPI4_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI4_InterruptDriverState);
}

static int32_t LPSPI4_InterruptUninitialize(void)
{
#ifdef RTE_SPI4_PIN_DEINIT
    RTE_SPI4_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI4_InterruptDriverState);
}

static int32_t LPSPI4_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI4_InterruptDriverState);
}

static int32_t LPSPI4_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI4_InterruptDriverState);
}

static int32_t LPSPI4_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI4_InterruptDriverState);
}

static int32_t LPSPI4_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI4_InterruptDriverState);
}

static uint32_t LPSPI4_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI4_InterruptDriverState);
}

static int32_t LPSPI4_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI4_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI4_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI4_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI4 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI4_DMA_EN) && RTE_SPI4_DMA_EN
    LPSPI4_EdmaInitialize, LPSPI4_EdmaUninitialize, LPSPI4_EdmaPowerControl, LPSPI4_EdmaSend,     LPSPI4_EdmaReceive,
    LPSPI4_EdmaTransfer,   LPSPI4_EdmaGetCount,     LPSPI4_EdmaControl,      LPSPI4_EdmaGetStatus
#else
    LPSPI4_InterruptInitialize, LPSPI4_InterruptUninitialize, LPSPI4_InterruptPowerControl, LPSPI4_InterruptSend,
    LPSPI4_InterruptReceive,    LPSPI4_InterruptTransfer,     LPSPI4_InterruptGetCount,     LPSPI4_InterruptControl,
    LPSPI4_InterruptGetStatus
#endif
};

#endif /*  LPSPI4  */

#if (defined(LPSPI5) || defined(LPSPI_5)) && defined(RTE_SPI5) && RTE_SPI5

/* User needs to provide the implementation for LPSPI5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI5_GetFreq(void);

#if defined(LPSPI5)
static cmsis_lpspi_resource_t LPSPI5_Resource = {LPSPI5, 5, LPSPI5_GetFreq};
#elif defined(LPSPI_5)
static cmsis_lpspi_resource_t LPSPI5_Resource = {LPSPI_5, 5, LPSPI5_GetFreq};
#endif

#if defined(RTE_SPI5_DMA_EN) && RTE_SPI5_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI5_EdmaResource = {
    RTE_SPI5_DMA_TX_DMA_BASE,    RTE_SPI5_DMA_TX_CH,          (uint16_t)RTE_SPI5_DMA_TX_PERI_SEL,
    RTE_SPI5_DMA_RX_DMA_BASE,    RTE_SPI5_DMA_RX_CH,          (uint16_t)RTE_SPI5_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI5_DMA_TX_DMAMUX_BASE, RTE_SPI5_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI5_EdmaHandle);
static edma_handle_t LPSPI5_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI5_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi5_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI5_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI5_EdmaDriverState = {
#endif
    &LPSPI5_Resource,
    &LPSPI5_EdmaResource,
    &LPSPI5_EdmaHandle,
    &LPSPI5_EdmaRxRegToRxDataHandle,
    &LPSPI5_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI5_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI5_PIN_INIT
    RTE_SPI5_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI5_EdmaDriverState);
}

static int32_t LPSPI5_EdmaUninitialize(void)
{
#ifdef RTE_SPI5_PIN_DEINIT
    RTE_SPI5_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI5_EdmaDriverState);
}

static int32_t LPSPI5_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI5_EdmaDriverState);
}

static int32_t LPSPI5_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI5_EdmaDriverState);
}

static int32_t LPSPI5_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI5_EdmaDriverState);
}

static int32_t LPSPI5_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI5_EdmaDriverState);
}

static uint32_t LPSPI5_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI5_EdmaDriverState);
}

static int32_t LPSPI5_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI5_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI5_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI5_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI5_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi5_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI5_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI5_InterruptDriverState = {
#endif
    &LPSPI5_Resource,
    &LPSPI5_Handle,
};

static int32_t LPSPI5_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI5_PIN_INIT
    RTE_SPI5_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI5_InterruptDriverState);
}

static int32_t LPSPI5_InterruptUninitialize(void)
{
#ifdef RTE_SPI5_PIN_DEINIT
    RTE_SPI5_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI5_InterruptDriverState);
}

static int32_t LPSPI5_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI5_InterruptDriverState);
}

static int32_t LPSPI5_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI5_InterruptDriverState);
}

static int32_t LPSPI5_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI5_InterruptDriverState);
}

static int32_t LPSPI5_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI5_InterruptDriverState);
}

static uint32_t LPSPI5_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI5_InterruptDriverState);
}

static int32_t LPSPI5_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI5_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI5_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI5_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI5 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI5_DMA_EN) && RTE_SPI5_DMA_EN
    LPSPI5_EdmaInitialize, LPSPI5_EdmaUninitialize, LPSPI5_EdmaPowerControl, LPSPI5_EdmaSend,     LPSPI5_EdmaReceive,
    LPSPI5_EdmaTransfer,   LPSPI5_EdmaGetCount,     LPSPI5_EdmaControl,      LPSPI5_EdmaGetStatus
#else
    LPSPI5_InterruptInitialize, LPSPI5_InterruptUninitialize, LPSPI5_InterruptPowerControl, LPSPI5_InterruptSend,
    LPSPI5_InterruptReceive,    LPSPI5_InterruptTransfer,     LPSPI5_InterruptGetCount,     LPSPI5_InterruptControl,
    LPSPI5_InterruptGetStatus
#endif
};

#endif /*  LPSPI5  */

#if (defined(LPSPI6) || defined(LPSPI_6)) && defined(RTE_SPI6) && RTE_SPI6

/* User needs to provide the implementation for LPSPI6_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI6_GetFreq(void);

#if defined(LPSPI6)
static cmsis_lpspi_resource_t LPSPI6_Resource = {LPSPI6, 6, LPSPI6_GetFreq};
#elif defined(LPSPI_6)
static cmsis_lpspi_resource_t LPSPI6_Resource = {LPSPI_6, 6, LPSPI6_GetFreq};
#endif

#if defined(RTE_SPI6_DMA_EN) && RTE_SPI6_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI6_EdmaResource = {
    RTE_SPI6_DMA_TX_DMA_BASE,    RTE_SPI6_DMA_TX_CH,          (uint16_t)RTE_SPI6_DMA_TX_PERI_SEL,
    RTE_SPI6_DMA_RX_DMA_BASE,    RTE_SPI6_DMA_RX_CH,          (uint16_t)RTE_SPI6_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI6_DMA_TX_DMAMUX_BASE, RTE_SPI6_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI6_EdmaHandle);
static edma_handle_t LPSPI6_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI6_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi6_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI6_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI6_EdmaDriverState = {
#endif
    &LPSPI6_Resource,
    &LPSPI6_EdmaResource,
    &LPSPI6_EdmaHandle,
    &LPSPI6_EdmaRxRegToRxDataHandle,
    &LPSPI6_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI6_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI6_PIN_INIT
    RTE_SPI6_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI6_EdmaDriverState);
}

static int32_t LPSPI6_EdmaUninitialize(void)
{
#ifdef RTE_SPI6_PIN_DEINIT
    RTE_SPI6_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI6_EdmaDriverState);
}

static int32_t LPSPI6_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI6_EdmaDriverState);
}

static int32_t LPSPI6_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI6_EdmaDriverState);
}

static int32_t LPSPI6_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI6_EdmaDriverState);
}

static int32_t LPSPI6_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI6_EdmaDriverState);
}

static uint32_t LPSPI6_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI6_EdmaDriverState);
}

static int32_t LPSPI6_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI6_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI6_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI6_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI6_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi6_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI6_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI6_InterruptDriverState = {
#endif
    &LPSPI6_Resource,
    &LPSPI6_Handle,
};

static int32_t LPSPI6_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI6_PIN_INIT
    RTE_SPI6_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI6_InterruptDriverState);
}

static int32_t LPSPI6_InterruptUninitialize(void)
{
#ifdef RTE_SPI6_PIN_DEINIT
    RTE_SPI6_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI6_InterruptDriverState);
}

static int32_t LPSPI6_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI6_InterruptDriverState);
}

static int32_t LPSPI6_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI6_InterruptDriverState);
}

static int32_t LPSPI6_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI6_InterruptDriverState);
}

static int32_t LPSPI6_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI6_InterruptDriverState);
}

static uint32_t LPSPI6_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI6_InterruptDriverState);
}

static int32_t LPSPI6_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI6_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI6_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI6_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI6 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI6_DMA_EN) && RTE_SPI6_DMA_EN
    LPSPI6_EdmaInitialize, LPSPI6_EdmaUninitialize, LPSPI6_EdmaPowerControl, LPSPI6_EdmaSend,     LPSPI6_EdmaReceive,
    LPSPI6_EdmaTransfer,   LPSPI6_EdmaGetCount,     LPSPI6_EdmaControl,      LPSPI6_EdmaGetStatus
#else
    LPSPI6_InterruptInitialize, LPSPI6_InterruptUninitialize, LPSPI6_InterruptPowerControl, LPSPI6_InterruptSend,
    LPSPI6_InterruptReceive,    LPSPI6_InterruptTransfer,     LPSPI6_InterruptGetCount,     LPSPI6_InterruptControl,
    LPSPI6_InterruptGetStatus
#endif
};

#endif /*  LPSPI6  */

#if (defined(LPSPI7) || defined(LPSPI_7)) && defined(RTE_SPI7) && RTE_SPI7

/* User needs to provide the implementation for LPSPI7_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI7_GetFreq(void);

#if defined(LPSPI7)
static cmsis_lpspi_resource_t LPSPI7_Resource = {LPSPI7, 7, LPSPI7_GetFreq};
#elif defined(LPSPI_7)
static cmsis_lpspi_resource_t LPSPI7_Resource = {LPSPI_7, 7, LPSPI7_GetFreq};
#endif

#if defined(RTE_SPI7_DMA_EN) && RTE_SPI7_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI7_EdmaResource = {
    RTE_SPI7_DMA_TX_DMA_BASE,    RTE_SPI7_DMA_TX_CH,          (uint16_t)RTE_SPI7_DMA_TX_PERI_SEL,
    RTE_SPI7_DMA_RX_DMA_BASE,    RTE_SPI7_DMA_RX_CH,          (uint16_t)RTE_SPI7_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI7_DMA_TX_DMAMUX_BASE, RTE_SPI7_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI7_EdmaHandle);
static edma_handle_t LPSPI7_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI7_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi7_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI7_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI7_EdmaDriverState = {
#endif
    &LPSPI7_Resource,
    &LPSPI7_EdmaResource,
    &LPSPI7_EdmaHandle,
    &LPSPI7_EdmaRxRegToRxDataHandle,
    &LPSPI7_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI7_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI7_PIN_INIT
    RTE_SPI7_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI7_EdmaDriverState);
}

static int32_t LPSPI7_EdmaUninitialize(void)
{
#ifdef RTE_SPI7_PIN_DEINIT
    RTE_SPI7_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI7_EdmaDriverState);
}

static int32_t LPSPI7_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI7_EdmaDriverState);
}

static int32_t LPSPI7_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI7_EdmaDriverState);
}

static int32_t LPSPI7_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI7_EdmaDriverState);
}

static int32_t LPSPI7_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI7_EdmaDriverState);
}

static uint32_t LPSPI7_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI7_EdmaDriverState);
}

static int32_t LPSPI7_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI7_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI7_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI7_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI7_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi7_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI7_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI7_InterruptDriverState = {
#endif
    &LPSPI7_Resource,
    &LPSPI7_Handle,
};

static int32_t LPSPI7_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI7_PIN_INIT
    RTE_SPI7_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI7_InterruptDriverState);
}

static int32_t LPSPI7_InterruptUninitialize(void)
{
#ifdef RTE_SPI7_PIN_DEINIT
    RTE_SPI7_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI7_InterruptDriverState);
}

static int32_t LPSPI7_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI7_InterruptDriverState);
}

static int32_t LPSPI7_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI7_InterruptDriverState);
}

static int32_t LPSPI7_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI7_InterruptDriverState);
}

static int32_t LPSPI7_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI7_InterruptDriverState);
}

static uint32_t LPSPI7_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI7_InterruptDriverState);
}

static int32_t LPSPI7_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI7_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI7_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI7_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI7 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI7_DMA_EN) && RTE_SPI7_DMA_EN
    LPSPI7_EdmaInitialize, LPSPI7_EdmaUninitialize, LPSPI7_EdmaPowerControl, LPSPI7_EdmaSend,     LPSPI7_EdmaReceive,
    LPSPI7_EdmaTransfer,   LPSPI7_EdmaGetCount,     LPSPI7_EdmaControl,      LPSPI7_EdmaGetStatus
#else
    LPSPI7_InterruptInitialize, LPSPI7_InterruptUninitialize, LPSPI7_InterruptPowerControl, LPSPI7_InterruptSend,
    LPSPI7_InterruptReceive,    LPSPI7_InterruptTransfer,     LPSPI7_InterruptGetCount,     LPSPI7_InterruptControl,
    LPSPI7_InterruptGetStatus
#endif
};

#endif /*  LPSPI7  */

#if (defined(LPSPI8) || defined(LPSPI_8)) && defined(RTE_SPI8) && RTE_SPI8

/* User needs to provide the implementation for LPSPI8_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI8_GetFreq(void);

#if defined(LPSPI8)
static cmsis_lpspi_resource_t LPSPI8_Resource = {LPSPI8, 8, LPSPI8_GetFreq};
#elif defined(LPSPI_8)
static cmsis_lpspi_resource_t LPSPI8_Resource = {LPSPI_8, 8, LPSPI8_GetFreq};
#endif

#if defined(RTE_SPI8_DMA_EN) && RTE_SPI8_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI8_EdmaResource = {
    RTE_SPI8_DMA_TX_DMA_BASE,    RTE_SPI8_DMA_TX_CH,          (uint16_t)RTE_SPI8_DMA_TX_PERI_SEL,
    RTE_SPI8_DMA_RX_DMA_BASE,    RTE_SPI8_DMA_RX_CH,          (uint16_t)RTE_SPI8_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI8_DMA_TX_DMAMUX_BASE, RTE_SPI8_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI8_EdmaHandle);
static edma_handle_t LPSPI8_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI8_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi8_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI8_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI8_EdmaDriverState = {
#endif
    &LPSPI8_Resource,
    &LPSPI8_EdmaResource,
    &LPSPI8_EdmaHandle,
    &LPSPI8_EdmaRxRegToRxDataHandle,
    &LPSPI8_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI8_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI8_PIN_INIT
    RTE_SPI8_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI8_EdmaDriverState);
}

static int32_t LPSPI8_EdmaUninitialize(void)
{
#ifdef RTE_SPI8_PIN_DEINIT
    RTE_SPI8_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI8_EdmaDriverState);
}

static int32_t LPSPI8_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI8_EdmaDriverState);
}

static int32_t LPSPI8_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI8_EdmaDriverState);
}

static int32_t LPSPI8_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI8_EdmaDriverState);
}

static int32_t LPSPI8_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI8_EdmaDriverState);
}

static uint32_t LPSPI8_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI8_EdmaDriverState);
}

static int32_t LPSPI8_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI8_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI8_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI8_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI8_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi8_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI8_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI8_InterruptDriverState = {
#endif
    &LPSPI8_Resource,
    &LPSPI8_Handle,
};

static int32_t LPSPI8_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI8_PIN_INIT
    RTE_SPI8_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI8_InterruptDriverState);
}

static int32_t LPSPI8_InterruptUninitialize(void)
{
#ifdef RTE_SPI8_PIN_DEINIT
    RTE_SPI8_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI8_InterruptDriverState);
}

static int32_t LPSPI8_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI8_InterruptDriverState);
}

static int32_t LPSPI8_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI8_InterruptDriverState);
}

static int32_t LPSPI8_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI8_InterruptDriverState);
}

static int32_t LPSPI8_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI8_InterruptDriverState);
}

static uint32_t LPSPI8_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI8_InterruptDriverState);
}

static int32_t LPSPI8_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI8_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI8_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI8_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI8 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI8_DMA_EN) && RTE_SPI8_DMA_EN
    LPSPI8_EdmaInitialize, LPSPI8_EdmaUninitialize, LPSPI8_EdmaPowerControl, LPSPI8_EdmaSend,     LPSPI8_EdmaReceive,
    LPSPI8_EdmaTransfer,   LPSPI8_EdmaGetCount,     LPSPI8_EdmaControl,      LPSPI8_EdmaGetStatus
#else
    LPSPI8_InterruptInitialize, LPSPI8_InterruptUninitialize, LPSPI8_InterruptPowerControl, LPSPI8_InterruptSend,
    LPSPI8_InterruptReceive,    LPSPI8_InterruptTransfer,     LPSPI8_InterruptGetCount,     LPSPI8_InterruptControl,
    LPSPI8_InterruptGetStatus
#endif
};

#endif /*  LPSPI8  */

#if (defined(LPSPI9) || defined(LPSPI_9)) && defined(RTE_SPI9) && RTE_SPI9

/* User needs to provide the implementation for LPSPI9_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI9_GetFreq(void);

#if defined(LPSPI9)
static cmsis_lpspi_resource_t LPSPI9_Resource = {LPSPI9, 9, LPSPI9_GetFreq};
#elif defined(LPSPI_9)
static cmsis_lpspi_resource_t LPSPI9_Resource = {LPSPI_9, 9, LPSPI9_GetFreq};
#endif

#if defined(RTE_SPI9_DMA_EN) && RTE_SPI9_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI9_EdmaResource = {
    RTE_SPI9_DMA_TX_DMA_BASE,    RTE_SPI9_DMA_TX_CH,          (uint16_t)RTE_SPI9_DMA_TX_PERI_SEL,
    RTE_SPI9_DMA_RX_DMA_BASE,    RTE_SPI9_DMA_RX_CH,          (uint16_t)RTE_SPI9_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI9_DMA_TX_DMAMUX_BASE, RTE_SPI9_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI9_EdmaHandle);
static edma_handle_t LPSPI9_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI9_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi9_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI9_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI9_EdmaDriverState = {
#endif
    &LPSPI9_Resource,
    &LPSPI9_EdmaResource,
    &LPSPI9_EdmaHandle,
    &LPSPI9_EdmaRxRegToRxDataHandle,
    &LPSPI9_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI9_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI9_PIN_INIT
    RTE_SPI9_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI9_EdmaDriverState);
}

static int32_t LPSPI9_EdmaUninitialize(void)
{
#ifdef RTE_SPI9_PIN_DEINIT
    RTE_SPI9_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI9_EdmaDriverState);
}

static int32_t LPSPI9_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI9_EdmaDriverState);
}

static int32_t LPSPI9_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI9_EdmaDriverState);
}

static int32_t LPSPI9_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI9_EdmaDriverState);
}

static int32_t LPSPI9_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI9_EdmaDriverState);
}

static uint32_t LPSPI9_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI9_EdmaDriverState);
}

static int32_t LPSPI9_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI9_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI9_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI9_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI9_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi9_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI9_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI9_InterruptDriverState = {
#endif
    &LPSPI9_Resource,
    &LPSPI9_Handle,
};

static int32_t LPSPI9_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI9_PIN_INIT
    RTE_SPI9_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI9_InterruptDriverState);
}

static int32_t LPSPI9_InterruptUninitialize(void)
{
#ifdef RTE_SPI9_PIN_DEINIT
    RTE_SPI9_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI9_InterruptDriverState);
}

static int32_t LPSPI9_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI9_InterruptDriverState);
}

static int32_t LPSPI9_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI9_InterruptDriverState);
}

static int32_t LPSPI9_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI9_InterruptDriverState);
}

static int32_t LPSPI9_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI9_InterruptDriverState);
}

static uint32_t LPSPI9_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI9_InterruptDriverState);
}

static int32_t LPSPI9_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI9_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI9_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI9_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI9 = {
    LPSPIx_GetVersion,     LPSPIx_GetCapabilities,
#if defined(RTE_SPI9_DMA_EN) && RTE_SPI9_DMA_EN
    LPSPI9_EdmaInitialize, LPSPI9_EdmaUninitialize, LPSPI9_EdmaPowerControl, LPSPI9_EdmaSend,     LPSPI9_EdmaReceive,
    LPSPI9_EdmaTransfer,   LPSPI9_EdmaGetCount,     LPSPI9_EdmaControl,      LPSPI9_EdmaGetStatus
#else
    LPSPI9_InterruptInitialize, LPSPI9_InterruptUninitialize, LPSPI9_InterruptPowerControl, LPSPI9_InterruptSend,
    LPSPI9_InterruptReceive,    LPSPI9_InterruptTransfer,     LPSPI9_InterruptGetCount,     LPSPI9_InterruptControl,
    LPSPI9_InterruptGetStatus
#endif
};

#endif /*  LPSPI9  */

#if (defined(LPSPI10) || defined(LPSPI_10)) && defined(RTE_SPI10) && RTE_SPI10

/* User needs to provide the implementation for LPSPI10_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI10_GetFreq(void);

#if defined(LPSPI10)
static cmsis_lpspi_resource_t LPSPI10_Resource = {LPSPI10, 10, LPSPI10_GetFreq};
#elif defined(LPSPI_10)
static cmsis_lpspi_resource_t LPSPI10_Resource = {LPSPI_10, 10, LPSPI10_GetFreq};
#endif

#if defined(RTE_SPI10_DMA_EN) && RTE_SPI10_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI10_EdmaResource = {
    RTE_SPI10_DMA_TX_DMA_BASE,    RTE_SPI10_DMA_TX_CH,          (uint16_t)RTE_SPI10_DMA_TX_PERI_SEL,
    RTE_SPI10_DMA_RX_DMA_BASE,    RTE_SPI10_DMA_RX_CH,          (uint16_t)RTE_SPI10_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI10_DMA_TX_DMAMUX_BASE, RTE_SPI10_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI10_EdmaHandle);
static edma_handle_t LPSPI10_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI10_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi10_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI10_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI10_EdmaDriverState = {
#endif
    &LPSPI10_Resource,
    &LPSPI10_EdmaResource,
    &LPSPI10_EdmaHandle,
    &LPSPI10_EdmaRxRegToRxDataHandle,
    &LPSPI10_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI10_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI10_PIN_INIT
    RTE_SPI10_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI10_EdmaDriverState);
}

static int32_t LPSPI10_EdmaUninitialize(void)
{
#ifdef RTE_SPI10_PIN_DEINIT
    RTE_SPI10_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI10_EdmaDriverState);
}

static int32_t LPSPI10_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI10_EdmaDriverState);
}

static int32_t LPSPI10_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI10_EdmaDriverState);
}

static int32_t LPSPI10_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI10_EdmaDriverState);
}

static int32_t LPSPI10_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI10_EdmaDriverState);
}

static uint32_t LPSPI10_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI10_EdmaDriverState);
}

static int32_t LPSPI10_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI10_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI10_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI10_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI10_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi10_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI10_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI10_InterruptDriverState = {
#endif
    &LPSPI10_Resource,
    &LPSPI10_Handle,
};

static int32_t LPSPI10_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI10_PIN_INIT
    RTE_SPI10_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI10_InterruptDriverState);
}

static int32_t LPSPI10_InterruptUninitialize(void)
{
#ifdef RTE_SPI10_PIN_DEINIT
    RTE_SPI10_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI10_InterruptDriverState);
}

static int32_t LPSPI10_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI10_InterruptDriverState);
}

static int32_t LPSPI10_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI10_InterruptDriverState);
}

static int32_t LPSPI10_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI10_InterruptDriverState);
}

static int32_t LPSPI10_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI10_InterruptDriverState);
}

static uint32_t LPSPI10_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI10_InterruptDriverState);
}

static int32_t LPSPI10_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI10_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI10_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI10_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI10 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI10_DMA_EN) && RTE_SPI10_DMA_EN
    LPSPI10_EdmaInitialize, LPSPI10_EdmaUninitialize, LPSPI10_EdmaPowerControl, LPSPI10_EdmaSend,
    LPSPI10_EdmaReceive,    LPSPI10_EdmaTransfer,     LPSPI10_EdmaGetCount,     LPSPI10_EdmaControl,
    LPSPI10_EdmaGetStatus
#else
    LPSPI10_InterruptInitialize, LPSPI10_InterruptUninitialize, LPSPI10_InterruptPowerControl, LPSPI10_InterruptSend,
    LPSPI10_InterruptReceive,    LPSPI10_InterruptTransfer,     LPSPI10_InterruptGetCount,     LPSPI10_InterruptControl,
    LPSPI10_InterruptGetStatus
#endif
};

#endif /*  LPSPI10  */

#if (defined(LPSPI11) || defined(LPSPI_11)) && defined(RTE_SPI11) && RTE_SPI11

/* User needs to provide the implementation for LPSPI11_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI11_GetFreq(void);

#if defined(LPSPI11)
static cmsis_lpspi_resource_t LPSPI11_Resource = {LPSPI11, 11, LPSPI11_GetFreq};
#elif defined(LPSPI_11)
static cmsis_lpspi_resource_t LPSPI11_Resource = {LPSPI_11, 11, LPSPI11_GetFreq};
#endif

#if defined(RTE_SPI11_DMA_EN) && RTE_SPI11_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI11_EdmaResource = {
    RTE_SPI11_DMA_TX_DMA_BASE,    RTE_SPI11_DMA_TX_CH,          (uint16_t)RTE_SPI11_DMA_TX_PERI_SEL,
    RTE_SPI11_DMA_RX_DMA_BASE,    RTE_SPI11_DMA_RX_CH,          (uint16_t)RTE_SPI11_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI11_DMA_TX_DMAMUX_BASE, RTE_SPI11_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI11_EdmaHandle);
static edma_handle_t LPSPI11_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI11_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi11_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI11_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI11_EdmaDriverState = {
#endif
    &LPSPI11_Resource,
    &LPSPI11_EdmaResource,
    &LPSPI11_EdmaHandle,
    &LPSPI11_EdmaRxRegToRxDataHandle,
    &LPSPI11_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI11_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI11_PIN_INIT
    RTE_SPI11_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI11_EdmaDriverState);
}

static int32_t LPSPI11_EdmaUninitialize(void)
{
#ifdef RTE_SPI11_PIN_DEINIT
    RTE_SPI11_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI11_EdmaDriverState);
}

static int32_t LPSPI11_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI11_EdmaDriverState);
}

static int32_t LPSPI11_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI11_EdmaDriverState);
}

static int32_t LPSPI11_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI11_EdmaDriverState);
}

static int32_t LPSPI11_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI11_EdmaDriverState);
}

static uint32_t LPSPI11_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI11_EdmaDriverState);
}

static int32_t LPSPI11_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI11_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI11_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI11_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI11_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi11_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI11_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI11_InterruptDriverState = {
#endif
    &LPSPI11_Resource,
    &LPSPI11_Handle,
};

static int32_t LPSPI11_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI11_PIN_INIT
    RTE_SPI11_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI11_InterruptDriverState);
}

static int32_t LPSPI11_InterruptUninitialize(void)
{
#ifdef RTE_SPI11_PIN_DEINIT
    RTE_SPI11_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI11_InterruptDriverState);
}

static int32_t LPSPI11_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI11_InterruptDriverState);
}

static int32_t LPSPI11_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI11_InterruptDriverState);
}

static int32_t LPSPI11_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI11_InterruptDriverState);
}

static int32_t LPSPI11_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI11_InterruptDriverState);
}

static uint32_t LPSPI11_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI11_InterruptDriverState);
}

static int32_t LPSPI11_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI11_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI11_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI11_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI11 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI11_DMA_EN) && RTE_SPI11_DMA_EN
    LPSPI11_EdmaInitialize, LPSPI11_EdmaUninitialize, LPSPI11_EdmaPowerControl, LPSPI11_EdmaSend,
    LPSPI11_EdmaReceive,    LPSPI11_EdmaTransfer,     LPSPI11_EdmaGetCount,     LPSPI11_EdmaControl,
    LPSPI11_EdmaGetStatus
#else
    LPSPI11_InterruptInitialize, LPSPI11_InterruptUninitialize, LPSPI11_InterruptPowerControl, LPSPI11_InterruptSend,
    LPSPI11_InterruptReceive,    LPSPI11_InterruptTransfer,     LPSPI11_InterruptGetCount,     LPSPI11_InterruptControl,
    LPSPI11_InterruptGetStatus
#endif
};

#endif /*  LPSPI11  */

#if (defined(LPSPI12) || defined(LPSPI_12)) && defined(RTE_SPI12) && RTE_SPI12

/* User needs to provide the implementation for LPSPI12_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI12_GetFreq(void);

#if defined(LPSPI12)
static cmsis_lpspi_resource_t LPSPI12_Resource = {LPSPI12, 12, LPSPI12_GetFreq};
#elif defined(LPSPI_12)
static cmsis_lpspi_resource_t LPSPI12_Resource = {LPSPI_12, 12, LPSPI12_GetFreq};
#endif

#if defined(RTE_SPI12_DMA_EN) && RTE_SPI12_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI12_EdmaResource = {
    RTE_SPI12_DMA_TX_DMA_BASE,    RTE_SPI12_DMA_TX_CH,          (uint16_t)RTE_SPI12_DMA_TX_PERI_SEL,
    RTE_SPI12_DMA_RX_DMA_BASE,    RTE_SPI12_DMA_RX_CH,          (uint16_t)RTE_SPI12_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI12_DMA_TX_DMAMUX_BASE, RTE_SPI12_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI12_EdmaHandle);
static edma_handle_t LPSPI12_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI12_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi12_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI12_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI12_EdmaDriverState = {
#endif
    &LPSPI12_Resource,
    &LPSPI12_EdmaResource,
    &LPSPI12_EdmaHandle,
    &LPSPI12_EdmaRxRegToRxDataHandle,
    &LPSPI12_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI12_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI12_PIN_INIT
    RTE_SPI12_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI12_EdmaDriverState);
}

static int32_t LPSPI12_EdmaUninitialize(void)
{
#ifdef RTE_SPI12_PIN_DEINIT
    RTE_SPI12_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI12_EdmaDriverState);
}

static int32_t LPSPI12_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI12_EdmaDriverState);
}

static int32_t LPSPI12_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI12_EdmaDriverState);
}

static int32_t LPSPI12_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI12_EdmaDriverState);
}

static int32_t LPSPI12_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI12_EdmaDriverState);
}

static uint32_t LPSPI12_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI12_EdmaDriverState);
}

static int32_t LPSPI12_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI12_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI12_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI12_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI12_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi12_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI12_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI12_InterruptDriverState = {
#endif
    &LPSPI12_Resource,
    &LPSPI12_Handle,
};

static int32_t LPSPI12_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI12_PIN_INIT
    RTE_SPI12_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI12_InterruptDriverState);
}

static int32_t LPSPI12_InterruptUninitialize(void)
{
#ifdef RTE_SPI12_PIN_DEINIT
    RTE_SPI12_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI12_InterruptDriverState);
}

static int32_t LPSPI12_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI12_InterruptDriverState);
}

static int32_t LPSPI12_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI12_InterruptDriverState);
}

static int32_t LPSPI12_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI12_InterruptDriverState);
}

static int32_t LPSPI12_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI12_InterruptDriverState);
}

static uint32_t LPSPI12_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI12_InterruptDriverState);
}

static int32_t LPSPI12_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI12_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI12_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI12_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI12 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI12_DMA_EN) && RTE_SPI12_DMA_EN
    LPSPI12_EdmaInitialize, LPSPI12_EdmaUninitialize, LPSPI12_EdmaPowerControl, LPSPI12_EdmaSend,
    LPSPI12_EdmaReceive,    LPSPI12_EdmaTransfer,     LPSPI12_EdmaGetCount,     LPSPI12_EdmaControl,
    LPSPI12_EdmaGetStatus
#else
    LPSPI12_InterruptInitialize, LPSPI12_InterruptUninitialize, LPSPI12_InterruptPowerControl, LPSPI12_InterruptSend,
    LPSPI12_InterruptReceive,    LPSPI12_InterruptTransfer,     LPSPI12_InterruptGetCount,     LPSPI12_InterruptControl,
    LPSPI12_InterruptGetStatus
#endif
};

#endif /*  LPSPI12  */

#if (defined(LPSPI13) || defined(LPSPI_13)) && defined(RTE_SPI13) && RTE_SPI13

/* User needs to provide the implementation for LPSPI13_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI13_GetFreq(void);

#if defined(LPSPI13)
static cmsis_lpspi_resource_t LPSPI13_Resource = {LPSPI13, 13, LPSPI13_GetFreq};
#elif defined(LPSPI_13)
static cmsis_lpspi_resource_t LPSPI13_Resource = {LPSPI_13, 13, LPSPI13_GetFreq};
#endif

#if defined(RTE_SPI13_DMA_EN) && RTE_SPI13_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI13_EdmaResource = {
    RTE_SPI13_DMA_TX_DMA_BASE,    RTE_SPI13_DMA_TX_CH,          (uint16_t)RTE_SPI13_DMA_TX_PERI_SEL,
    RTE_SPI13_DMA_RX_DMA_BASE,    RTE_SPI13_DMA_RX_CH,          (uint16_t)RTE_SPI13_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI13_DMA_TX_DMAMUX_BASE, RTE_SPI13_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI13_EdmaHandle);
static edma_handle_t LPSPI13_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI13_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi13_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI13_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI13_EdmaDriverState = {
#endif
    &LPSPI13_Resource,
    &LPSPI13_EdmaResource,
    &LPSPI13_EdmaHandle,
    &LPSPI13_EdmaRxRegToRxDataHandle,
    &LPSPI13_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI13_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI13_PIN_INIT
    RTE_SPI13_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI13_EdmaDriverState);
}

static int32_t LPSPI13_EdmaUninitialize(void)
{
#ifdef RTE_SPI13_PIN_DEINIT
    RTE_SPI13_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI13_EdmaDriverState);
}

static int32_t LPSPI13_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI13_EdmaDriverState);
}

static int32_t LPSPI13_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI13_EdmaDriverState);
}

static int32_t LPSPI13_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI13_EdmaDriverState);
}

static int32_t LPSPI13_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI13_EdmaDriverState);
}

static uint32_t LPSPI13_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI13_EdmaDriverState);
}

static int32_t LPSPI13_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI13_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI13_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI13_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI13_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi13_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI13_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI13_InterruptDriverState = {
#endif
    &LPSPI13_Resource,
    &LPSPI13_Handle,
};

static int32_t LPSPI13_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI13_PIN_INIT
    RTE_SPI13_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI13_InterruptDriverState);
}

static int32_t LPSPI13_InterruptUninitialize(void)
{
#ifdef RTE_SPI13_PIN_DEINIT
    RTE_SPI13_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI13_InterruptDriverState);
}

static int32_t LPSPI13_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI13_InterruptDriverState);
}

static int32_t LPSPI13_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI13_InterruptDriverState);
}

static int32_t LPSPI13_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI13_InterruptDriverState);
}

static int32_t LPSPI13_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI13_InterruptDriverState);
}

static uint32_t LPSPI13_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI13_InterruptDriverState);
}

static int32_t LPSPI13_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI13_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI13_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI13_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI13 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI13_DMA_EN) && RTE_SPI13_DMA_EN
    LPSPI13_EdmaInitialize, LPSPI13_EdmaUninitialize, LPSPI13_EdmaPowerControl, LPSPI13_EdmaSend,
    LPSPI13_EdmaReceive,    LPSPI13_EdmaTransfer,     LPSPI13_EdmaGetCount,     LPSPI13_EdmaControl,
    LPSPI13_EdmaGetStatus
#else
    LPSPI13_InterruptInitialize, LPSPI13_InterruptUninitialize, LPSPI13_InterruptPowerControl, LPSPI13_InterruptSend,
    LPSPI13_InterruptReceive,    LPSPI13_InterruptTransfer,     LPSPI13_InterruptGetCount,     LPSPI13_InterruptControl,
    LPSPI13_InterruptGetStatus
#endif
};

#endif /*  LPSPI13  */

#if (defined(LPSPI14) || defined(LPSPI_14)) && defined(RTE_SPI14) && RTE_SPI14

/* User needs to provide the implementation for LPSPI14_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI14_GetFreq(void);

#if defined(LPSPI14)
static cmsis_lpspi_resource_t LPSPI14_Resource = {LPSPI14, 14, LPSPI14_GetFreq};
#elif defined(LPSPI_14)
static cmsis_lpspi_resource_t LPSPI14_Resource = {LPSPI_14, 14, LPSPI14_GetFreq};
#endif

#if defined(RTE_SPI14_DMA_EN) && RTE_SPI14_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI14_EdmaResource = {
    RTE_SPI14_DMA_TX_DMA_BASE,    RTE_SPI14_DMA_TX_CH,          (uint16_t)RTE_SPI14_DMA_TX_PERI_SEL,
    RTE_SPI14_DMA_RX_DMA_BASE,    RTE_SPI14_DMA_RX_CH,          (uint16_t)RTE_SPI14_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI14_DMA_TX_DMAMUX_BASE, RTE_SPI14_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI14_EdmaHandle);
static edma_handle_t LPSPI14_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI14_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi14_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI14_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI14_EdmaDriverState = {
#endif
    &LPSPI14_Resource,
    &LPSPI14_EdmaResource,
    &LPSPI14_EdmaHandle,
    &LPSPI14_EdmaRxRegToRxDataHandle,
    &LPSPI14_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI14_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI14_PIN_INIT
    RTE_SPI14_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI14_EdmaDriverState);
}

static int32_t LPSPI14_EdmaUninitialize(void)
{
#ifdef RTE_SPI14_PIN_DEINIT
    RTE_SPI14_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI14_EdmaDriverState);
}

static int32_t LPSPI14_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI14_EdmaDriverState);
}

static int32_t LPSPI14_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI14_EdmaDriverState);
}

static int32_t LPSPI14_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI14_EdmaDriverState);
}

static int32_t LPSPI14_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI14_EdmaDriverState);
}

static uint32_t LPSPI14_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI14_EdmaDriverState);
}

static int32_t LPSPI14_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI14_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI14_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI14_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI14_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi14_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI14_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI14_InterruptDriverState = {
#endif
    &LPSPI14_Resource,
    &LPSPI14_Handle,
};

static int32_t LPSPI14_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI14_PIN_INIT
    RTE_SPI14_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI14_InterruptDriverState);
}

static int32_t LPSPI14_InterruptUninitialize(void)
{
#ifdef RTE_SPI14_PIN_DEINIT
    RTE_SPI14_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI14_InterruptDriverState);
}

static int32_t LPSPI14_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI14_InterruptDriverState);
}

static int32_t LPSPI14_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI14_InterruptDriverState);
}

static int32_t LPSPI14_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI14_InterruptDriverState);
}

static int32_t LPSPI14_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI14_InterruptDriverState);
}

static uint32_t LPSPI14_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI14_InterruptDriverState);
}

static int32_t LPSPI14_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI14_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI14_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI14_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI14 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI14_DMA_EN) && RTE_SPI14_DMA_EN
    LPSPI14_EdmaInitialize, LPSPI14_EdmaUninitialize, LPSPI14_EdmaPowerControl, LPSPI14_EdmaSend,
    LPSPI14_EdmaReceive,    LPSPI14_EdmaTransfer,     LPSPI14_EdmaGetCount,     LPSPI14_EdmaControl,
    LPSPI14_EdmaGetStatus
#else
    LPSPI14_InterruptInitialize, LPSPI14_InterruptUninitialize, LPSPI14_InterruptPowerControl, LPSPI14_InterruptSend,
    LPSPI14_InterruptReceive,    LPSPI14_InterruptTransfer,     LPSPI14_InterruptGetCount,     LPSPI14_InterruptControl,
    LPSPI14_InterruptGetStatus
#endif
};

#endif /*  LPSPI14  */

#if (defined(LPSPI15) || defined(LPSPI_15)) && defined(RTE_SPI15) && RTE_SPI15

/* User needs to provide the implementation for LPSPI15_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI15_GetFreq(void);

#if defined(LPSPI15)
static cmsis_lpspi_resource_t LPSPI15_Resource = {LPSPI15, 15, LPSPI15_GetFreq};
#elif defined(LPSPI_15)
static cmsis_lpspi_resource_t LPSPI15_Resource = {LPSPI_15, 15, LPSPI15_GetFreq};
#endif

#if defined(RTE_SPI15_DMA_EN) && RTE_SPI15_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI15_EdmaResource = {
    RTE_SPI15_DMA_TX_DMA_BASE,    RTE_SPI15_DMA_TX_CH,          (uint16_t)RTE_SPI15_DMA_TX_PERI_SEL,
    RTE_SPI15_DMA_RX_DMA_BASE,    RTE_SPI15_DMA_RX_CH,          (uint16_t)RTE_SPI15_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI15_DMA_TX_DMAMUX_BASE, RTE_SPI15_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI15_EdmaHandle);
static edma_handle_t LPSPI15_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI15_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi15_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI15_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI15_EdmaDriverState = {
#endif
    &LPSPI15_Resource,
    &LPSPI15_EdmaResource,
    &LPSPI15_EdmaHandle,
    &LPSPI15_EdmaRxRegToRxDataHandle,
    &LPSPI15_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI15_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI15_PIN_INIT
    RTE_SPI15_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI15_EdmaDriverState);
}

static int32_t LPSPI15_EdmaUninitialize(void)
{
#ifdef RTE_SPI15_PIN_DEINIT
    RTE_SPI15_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI15_EdmaDriverState);
}

static int32_t LPSPI15_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI15_EdmaDriverState);
}

static int32_t LPSPI15_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI15_EdmaDriverState);
}

static int32_t LPSPI15_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI15_EdmaDriverState);
}

static int32_t LPSPI15_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI15_EdmaDriverState);
}

static uint32_t LPSPI15_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI15_EdmaDriverState);
}

static int32_t LPSPI15_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI15_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI15_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI15_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI15_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi15_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI15_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI15_InterruptDriverState = {
#endif
    &LPSPI15_Resource,
    &LPSPI15_Handle,
};

static int32_t LPSPI15_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI15_PIN_INIT
    RTE_SPI15_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI15_InterruptDriverState);
}

static int32_t LPSPI15_InterruptUninitialize(void)
{
#ifdef RTE_SPI15_PIN_DEINIT
    RTE_SPI15_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI15_InterruptDriverState);
}

static int32_t LPSPI15_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI15_InterruptDriverState);
}

static int32_t LPSPI15_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI15_InterruptDriverState);
}

static int32_t LPSPI15_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI15_InterruptDriverState);
}

static int32_t LPSPI15_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI15_InterruptDriverState);
}

static uint32_t LPSPI15_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI15_InterruptDriverState);
}

static int32_t LPSPI15_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI15_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI15_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI15_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI15 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI15_DMA_EN) && RTE_SPI15_DMA_EN
    LPSPI15_EdmaInitialize, LPSPI15_EdmaUninitialize, LPSPI15_EdmaPowerControl, LPSPI15_EdmaSend,
    LPSPI15_EdmaReceive,    LPSPI15_EdmaTransfer,     LPSPI15_EdmaGetCount,     LPSPI15_EdmaControl,
    LPSPI15_EdmaGetStatus
#else
    LPSPI15_InterruptInitialize, LPSPI15_InterruptUninitialize, LPSPI15_InterruptPowerControl, LPSPI15_InterruptSend,
    LPSPI15_InterruptReceive,    LPSPI15_InterruptTransfer,     LPSPI15_InterruptGetCount,     LPSPI15_InterruptControl,
    LPSPI15_InterruptGetStatus
#endif
};

#endif /*  LPSPI15  */

#if (defined(LPSPI16) || defined(LPSPI_16)) && defined(RTE_SPI16) && RTE_SPI16

/* User needs to provide the implementation for LPSPI16_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI16_GetFreq(void);

#if defined(LPSPI16)
static cmsis_lpspi_resource_t LPSPI16_Resource = {LPSPI16, 16, LPSPI16_GetFreq};
#elif defined(LPSPI_16)
static cmsis_lpspi_resource_t LPSPI16_Resource = {LPSPI_16, 16, LPSPI16_GetFreq};
#endif

#if defined(RTE_SPI16_DMA_EN) && RTE_SPI16_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI16_EdmaResource = {
    RTE_SPI16_DMA_TX_DMA_BASE,    RTE_SPI16_DMA_TX_CH,          (uint16_t)RTE_SPI16_DMA_TX_PERI_SEL,
    RTE_SPI16_DMA_RX_DMA_BASE,    RTE_SPI16_DMA_RX_CH,          (uint16_t)RTE_SPI16_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI16_DMA_TX_DMAMUX_BASE, RTE_SPI16_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI16_EdmaHandle);
static edma_handle_t LPSPI16_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI16_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi16_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI16_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI16_EdmaDriverState = {
#endif
    &LPSPI16_Resource,
    &LPSPI16_EdmaResource,
    &LPSPI16_EdmaHandle,
    &LPSPI16_EdmaRxRegToRxDataHandle,
    &LPSPI16_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI16_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI16_PIN_INIT
    RTE_SPI16_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI16_EdmaDriverState);
}

static int32_t LPSPI16_EdmaUninitialize(void)
{
#ifdef RTE_SPI16_PIN_DEINIT
    RTE_SPI16_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI16_EdmaDriverState);
}

static int32_t LPSPI16_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI16_EdmaDriverState);
}

static int32_t LPSPI16_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI16_EdmaDriverState);
}

static int32_t LPSPI16_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI16_EdmaDriverState);
}

static int32_t LPSPI16_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI16_EdmaDriverState);
}

static uint32_t LPSPI16_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI16_EdmaDriverState);
}

static int32_t LPSPI16_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI16_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI16_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI16_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI16_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi16_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI16_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI16_InterruptDriverState = {
#endif
    &LPSPI16_Resource,
    &LPSPI16_Handle,
};

static int32_t LPSPI16_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI16_PIN_INIT
    RTE_SPI16_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI16_InterruptDriverState);
}

static int32_t LPSPI16_InterruptUninitialize(void)
{
#ifdef RTE_SPI16_PIN_DEINIT
    RTE_SPI16_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI16_InterruptDriverState);
}

static int32_t LPSPI16_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI16_InterruptDriverState);
}

static int32_t LPSPI16_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI16_InterruptDriverState);
}

static int32_t LPSPI16_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI16_InterruptDriverState);
}

static int32_t LPSPI16_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI16_InterruptDriverState);
}

static uint32_t LPSPI16_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI16_InterruptDriverState);
}

static int32_t LPSPI16_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI16_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI16_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI16_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI16 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI16_DMA_EN) && RTE_SPI16_DMA_EN
    LPSPI16_EdmaInitialize, LPSPI16_EdmaUninitialize, LPSPI16_EdmaPowerControl, LPSPI16_EdmaSend,
    LPSPI16_EdmaReceive,    LPSPI16_EdmaTransfer,     LPSPI16_EdmaGetCount,     LPSPI16_EdmaControl,
    LPSPI16_EdmaGetStatus
#else
    LPSPI16_InterruptInitialize, LPSPI16_InterruptUninitialize, LPSPI16_InterruptPowerControl, LPSPI16_InterruptSend,
    LPSPI16_InterruptReceive,    LPSPI16_InterruptTransfer,     LPSPI16_InterruptGetCount,     LPSPI16_InterruptControl,
    LPSPI16_InterruptGetStatus
#endif
};

#endif /*  LPSPI16  */

#if (defined(LPSPI17) || defined(LPSPI_17)) && defined(RTE_SPI17) && RTE_SPI17

/* User needs to provide the implementation for LPSPI17_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI17_GetFreq(void);

#if defined(LPSPI17)
static cmsis_lpspi_resource_t LPSPI17_Resource = {LPSPI17, 17, LPSPI17_GetFreq};
#elif defined(LPSPI_17)
static cmsis_lpspi_resource_t LPSPI17_Resource = {LPSPI_17, 17, LPSPI17_GetFreq};
#endif

#if defined(RTE_SPI17_DMA_EN) && RTE_SPI17_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI17_EdmaResource = {
    RTE_SPI17_DMA_TX_DMA_BASE,    RTE_SPI17_DMA_TX_CH,          (uint16_t)RTE_SPI17_DMA_TX_PERI_SEL,
    RTE_SPI17_DMA_RX_DMA_BASE,    RTE_SPI17_DMA_RX_CH,          (uint16_t)RTE_SPI17_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI17_DMA_TX_DMAMUX_BASE, RTE_SPI17_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI17_EdmaHandle);
static edma_handle_t LPSPI17_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI17_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi17_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI17_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI17_EdmaDriverState = {
#endif
    &LPSPI17_Resource,
    &LPSPI17_EdmaResource,
    &LPSPI17_EdmaHandle,
    &LPSPI17_EdmaRxRegToRxDataHandle,
    &LPSPI17_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI17_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI17_PIN_INIT
    RTE_SPI17_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI17_EdmaDriverState);
}

static int32_t LPSPI17_EdmaUninitialize(void)
{
#ifdef RTE_SPI17_PIN_DEINIT
    RTE_SPI17_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI17_EdmaDriverState);
}

static int32_t LPSPI17_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI17_EdmaDriverState);
}

static int32_t LPSPI17_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI17_EdmaDriverState);
}

static int32_t LPSPI17_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI17_EdmaDriverState);
}

static int32_t LPSPI17_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI17_EdmaDriverState);
}

static uint32_t LPSPI17_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI17_EdmaDriverState);
}

static int32_t LPSPI17_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI17_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI17_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI17_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI17_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi17_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI17_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI17_InterruptDriverState = {
#endif
    &LPSPI17_Resource,
    &LPSPI17_Handle,
};

static int32_t LPSPI17_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI17_PIN_INIT
    RTE_SPI17_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI17_InterruptDriverState);
}

static int32_t LPSPI17_InterruptUninitialize(void)
{
#ifdef RTE_SPI17_PIN_DEINIT
    RTE_SPI17_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI17_InterruptDriverState);
}

static int32_t LPSPI17_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI17_InterruptDriverState);
}

static int32_t LPSPI17_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI17_InterruptDriverState);
}

static int32_t LPSPI17_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI17_InterruptDriverState);
}

static int32_t LPSPI17_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI17_InterruptDriverState);
}

static uint32_t LPSPI17_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI17_InterruptDriverState);
}

static int32_t LPSPI17_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI17_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI17_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI17_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI17 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI17_DMA_EN) && RTE_SPI17_DMA_EN
    LPSPI17_EdmaInitialize, LPSPI17_EdmaUninitialize, LPSPI17_EdmaPowerControl, LPSPI17_EdmaSend,
    LPSPI17_EdmaReceive,    LPSPI17_EdmaTransfer,     LPSPI17_EdmaGetCount,     LPSPI17_EdmaControl,
    LPSPI17_EdmaGetStatus
#else
    LPSPI17_InterruptInitialize, LPSPI17_InterruptUninitialize, LPSPI17_InterruptPowerControl, LPSPI17_InterruptSend,
    LPSPI17_InterruptReceive,    LPSPI17_InterruptTransfer,     LPSPI17_InterruptGetCount,     LPSPI17_InterruptControl,
    LPSPI17_InterruptGetStatus
#endif
};

#endif /*  LPSPI17  */

#if (defined(LPSPI18) || defined(LPSPI_18)) && defined(RTE_SPI18) && RTE_SPI18

/* User needs to provide the implementation for LPSPI18_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI18_GetFreq(void);

#if defined(LPSPI18)
static cmsis_lpspi_resource_t LPSPI18_Resource = {LPSPI18, 18, LPSPI18_GetFreq};
#elif defined(LPSPI_18)
static cmsis_lpspi_resource_t LPSPI18_Resource = {LPSPI_18, 18, LPSPI18_GetFreq};
#endif

#if defined(RTE_SPI18_DMA_EN) && RTE_SPI18_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI18_EdmaResource = {
    RTE_SPI18_DMA_TX_DMA_BASE,    RTE_SPI18_DMA_TX_CH,          (uint16_t)RTE_SPI18_DMA_TX_PERI_SEL,
    RTE_SPI18_DMA_RX_DMA_BASE,    RTE_SPI18_DMA_RX_CH,          (uint16_t)RTE_SPI18_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI18_DMA_TX_DMAMUX_BASE, RTE_SPI18_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI18_EdmaHandle);
static edma_handle_t LPSPI18_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI18_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi18_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI18_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI18_EdmaDriverState = {
#endif
    &LPSPI18_Resource,
    &LPSPI18_EdmaResource,
    &LPSPI18_EdmaHandle,
    &LPSPI18_EdmaRxRegToRxDataHandle,
    &LPSPI18_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI18_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI18_PIN_INIT
    RTE_SPI18_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI18_EdmaDriverState);
}

static int32_t LPSPI18_EdmaUninitialize(void)
{
#ifdef RTE_SPI18_PIN_DEINIT
    RTE_SPI18_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI18_EdmaDriverState);
}

static int32_t LPSPI18_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI18_EdmaDriverState);
}

static int32_t LPSPI18_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI18_EdmaDriverState);
}

static int32_t LPSPI18_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI18_EdmaDriverState);
}

static int32_t LPSPI18_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI18_EdmaDriverState);
}

static uint32_t LPSPI18_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI18_EdmaDriverState);
}

static int32_t LPSPI18_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI18_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI18_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI18_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI18_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi18_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI18_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI18_InterruptDriverState = {
#endif
    &LPSPI18_Resource,
    &LPSPI18_Handle,
};

static int32_t LPSPI18_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI18_PIN_INIT
    RTE_SPI18_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI18_InterruptDriverState);
}

static int32_t LPSPI18_InterruptUninitialize(void)
{
#ifdef RTE_SPI18_PIN_DEINIT
    RTE_SPI18_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI18_InterruptDriverState);
}

static int32_t LPSPI18_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI18_InterruptDriverState);
}

static int32_t LPSPI18_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI18_InterruptDriverState);
}

static int32_t LPSPI18_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI18_InterruptDriverState);
}

static int32_t LPSPI18_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI18_InterruptDriverState);
}

static uint32_t LPSPI18_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI18_InterruptDriverState);
}

static int32_t LPSPI18_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI18_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI18_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI18_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI18 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI18_DMA_EN) && RTE_SPI18_DMA_EN
    LPSPI18_EdmaInitialize, LPSPI18_EdmaUninitialize, LPSPI18_EdmaPowerControl, LPSPI18_EdmaSend,
    LPSPI18_EdmaReceive,    LPSPI18_EdmaTransfer,     LPSPI18_EdmaGetCount,     LPSPI18_EdmaControl,
    LPSPI18_EdmaGetStatus
#else
    LPSPI18_InterruptInitialize, LPSPI18_InterruptUninitialize, LPSPI18_InterruptPowerControl, LPSPI18_InterruptSend,
    LPSPI18_InterruptReceive,    LPSPI18_InterruptTransfer,     LPSPI18_InterruptGetCount,     LPSPI18_InterruptControl,
    LPSPI18_InterruptGetStatus
#endif
};

#endif /*  LPSPI18  */

#if (defined(LPSPI19) || defined(LPSPI_19)) && defined(RTE_SPI19) && RTE_SPI19

/* User needs to provide the implementation for LPSPI19_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI19_GetFreq(void);

#if defined(LPSPI19)
static cmsis_lpspi_resource_t LPSPI19_Resource = {LPSPI19, 19, LPSPI19_GetFreq};
#elif defined(LPSPI_19)
static cmsis_lpspi_resource_t LPSPI19_Resource = {LPSPI_19, 19, LPSPI19_GetFreq};
#endif

#if defined(RTE_SPI19_DMA_EN) && RTE_SPI19_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI19_EdmaResource = {
    RTE_SPI19_DMA_TX_DMA_BASE,    RTE_SPI19_DMA_TX_CH,          (uint16_t)RTE_SPI19_DMA_TX_PERI_SEL,
    RTE_SPI19_DMA_RX_DMA_BASE,    RTE_SPI19_DMA_RX_CH,          (uint16_t)RTE_SPI19_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI19_DMA_TX_DMAMUX_BASE, RTE_SPI19_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI19_EdmaHandle);
static edma_handle_t LPSPI19_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI19_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi19_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI19_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI19_EdmaDriverState = {
#endif
    &LPSPI19_Resource,
    &LPSPI19_EdmaResource,
    &LPSPI19_EdmaHandle,
    &LPSPI19_EdmaRxRegToRxDataHandle,
    &LPSPI19_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI19_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI19_PIN_INIT
    RTE_SPI19_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI19_EdmaDriverState);
}

static int32_t LPSPI19_EdmaUninitialize(void)
{
#ifdef RTE_SPI19_PIN_DEINIT
    RTE_SPI19_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI19_EdmaDriverState);
}

static int32_t LPSPI19_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI19_EdmaDriverState);
}

static int32_t LPSPI19_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI19_EdmaDriverState);
}

static int32_t LPSPI19_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI19_EdmaDriverState);
}

static int32_t LPSPI19_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI19_EdmaDriverState);
}

static uint32_t LPSPI19_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI19_EdmaDriverState);
}

static int32_t LPSPI19_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI19_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI19_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI19_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI19_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi19_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI19_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI19_InterruptDriverState = {
#endif
    &LPSPI19_Resource,
    &LPSPI19_Handle,
};

static int32_t LPSPI19_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI19_PIN_INIT
    RTE_SPI19_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI19_InterruptDriverState);
}

static int32_t LPSPI19_InterruptUninitialize(void)
{
#ifdef RTE_SPI19_PIN_DEINIT
    RTE_SPI19_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI19_InterruptDriverState);
}

static int32_t LPSPI19_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI19_InterruptDriverState);
}

static int32_t LPSPI19_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI19_InterruptDriverState);
}

static int32_t LPSPI19_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI19_InterruptDriverState);
}

static int32_t LPSPI19_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI19_InterruptDriverState);
}

static uint32_t LPSPI19_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI19_InterruptDriverState);
}

static int32_t LPSPI19_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI19_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI19_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI19_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI19 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI19_DMA_EN) && RTE_SPI19_DMA_EN
    LPSPI19_EdmaInitialize, LPSPI19_EdmaUninitialize, LPSPI19_EdmaPowerControl, LPSPI19_EdmaSend,
    LPSPI19_EdmaReceive,    LPSPI19_EdmaTransfer,     LPSPI19_EdmaGetCount,     LPSPI19_EdmaControl,
    LPSPI19_EdmaGetStatus
#else
    LPSPI19_InterruptInitialize, LPSPI19_InterruptUninitialize, LPSPI19_InterruptPowerControl, LPSPI19_InterruptSend,
    LPSPI19_InterruptReceive,    LPSPI19_InterruptTransfer,     LPSPI19_InterruptGetCount,     LPSPI19_InterruptControl,
    LPSPI19_InterruptGetStatus
#endif
};

#endif /*  LPSPI19  */

#if (defined(LPSPI20) || defined(LPSPI_20)) && defined(RTE_SPI20) && RTE_SPI20

/* User needs to provide the implementation for LPSPI20_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPSPI20_GetFreq(void);

#if defined(LPSPI20)
static cmsis_lpspi_resource_t LPSPI20_Resource = {LPSPI20, 20, LPSPI20_GetFreq};
#elif defined(LPSPI_20)
static cmsis_lpspi_resource_t LPSPI20_Resource = {LPSPI_20, 20, LPSPI20_GetFreq};
#endif

#if defined(RTE_SPI20_DMA_EN) && RTE_SPI20_DMA_EN

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static cmsis_lpspi_edma_resource_t LPSPI20_EdmaResource = {
    RTE_SPI20_DMA_TX_DMA_BASE,    RTE_SPI20_DMA_TX_CH,          (uint16_t)RTE_SPI20_DMA_TX_PERI_SEL,
    RTE_SPI20_DMA_RX_DMA_BASE,    RTE_SPI20_DMA_RX_CH,          (uint16_t)RTE_SPI20_DMA_RX_PERI_SEL,
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_SPI20_DMA_TX_DMAMUX_BASE, RTE_SPI20_DMA_RX_DMAMUX_BASE,
#endif
};

AT_NONCACHEABLE_SECTION(static cmsis_lpspi_edma_handle_t LPSPI20_EdmaHandle);
static edma_handle_t LPSPI20_EdmaTxDataToTxRegHandle;
static edma_handle_t LPSPI20_EdmaRxRegToRxDataHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi20_edma_driver_state")
static cmsis_lpspi_edma_driver_state_t LPSPI20_EdmaDriverState = {
#else
static cmsis_lpspi_edma_driver_state_t LPSPI20_EdmaDriverState = {
#endif
    &LPSPI20_Resource,
    &LPSPI20_EdmaResource,
    &LPSPI20_EdmaHandle,
    &LPSPI20_EdmaRxRegToRxDataHandle,
    &LPSPI20_EdmaTxDataToTxRegHandle,
};

static int32_t LPSPI20_EdmaInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI20_PIN_INIT
    RTE_SPI20_PIN_INIT();
#endif
    return LPSPI_EdmaInitialize(cb_event, &LPSPI20_EdmaDriverState);
}

static int32_t LPSPI20_EdmaUninitialize(void)
{
#ifdef RTE_SPI20_PIN_DEINIT
    RTE_SPI20_PIN_DEINIT();
#endif
    return LPSPI_EdmaUninitialize(&LPSPI20_EdmaDriverState);
}

static int32_t LPSPI20_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_EdmaPowerControl(state, &LPSPI20_EdmaDriverState);
}

static int32_t LPSPI20_EdmaSend(const void *data, uint32_t num)
{
    return LPSPI_EdmaSend(data, num, &LPSPI20_EdmaDriverState);
}

static int32_t LPSPI20_EdmaReceive(void *data, uint32_t num)
{
    return LPSPI_EdmaReceive(data, num, &LPSPI20_EdmaDriverState);
}

static int32_t LPSPI20_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_EdmaTransfer(data_out, data_in, num, &LPSPI20_EdmaDriverState);
}

static uint32_t LPSPI20_EdmaGetCount(void)
{
    return LPSPI_EdmaGetCount(&LPSPI20_EdmaDriverState);
}

static int32_t LPSPI20_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPSPI_EdmaControl(control, arg, &LPSPI20_EdmaDriverState);
}

static ARM_SPI_STATUS LPSPI20_EdmaGetStatus(void)
{
    return LPSPI_EdmaGetStatus(&LPSPI20_EdmaDriverState);
}

#endif

#else

static cmsis_lpspi_handle_t LPSPI20_Handle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpspi20_interrupt_driver_state")
static cmsis_lpspi_interrupt_driver_state_t LPSPI20_InterruptDriverState = {
#else
static cmsis_lpspi_interrupt_driver_state_t LPSPI20_InterruptDriverState = {
#endif
    &LPSPI20_Resource,
    &LPSPI20_Handle,
};

static int32_t LPSPI20_InterruptInitialize(ARM_SPI_SignalEvent_t cb_event)
{
#ifdef RTE_SPI20_PIN_INIT
    RTE_SPI20_PIN_INIT();
#endif
    return LPSPI_InterruptInitialize(cb_event, &LPSPI20_InterruptDriverState);
}

static int32_t LPSPI20_InterruptUninitialize(void)
{
#ifdef RTE_SPI20_PIN_DEINIT
    RTE_SPI20_PIN_DEINIT();
#endif
    return LPSPI_InterruptUninitialize(&LPSPI20_InterruptDriverState);
}

static int32_t LPSPI20_InterruptPowerControl(ARM_POWER_STATE state)
{
    return LPSPI_InterruptPowerControl(state, &LPSPI20_InterruptDriverState);
}

static int32_t LPSPI20_InterruptSend(const void *data, uint32_t num)
{
    return LPSPI_InterruptSend(data, num, &LPSPI20_InterruptDriverState);
}

static int32_t LPSPI20_InterruptReceive(void *data, uint32_t num)
{
    return LPSPI_InterruptReceive(data, num, &LPSPI20_InterruptDriverState);
}

static int32_t LPSPI20_InterruptTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPSPI_InterruptTransfer(data_out, data_in, num, &LPSPI20_InterruptDriverState);
}

static uint32_t LPSPI20_InterruptGetCount(void)
{
    return LPSPI_InterruptGetCount(&LPSPI20_InterruptDriverState);
}

static int32_t LPSPI20_InterruptControl(uint32_t control, uint32_t arg)
{
    return LPSPI_InterruptControl(control, arg, &LPSPI20_InterruptDriverState);
}

static ARM_SPI_STATUS LPSPI20_InterruptGetStatus(void)
{
    return LPSPI_InterruptGetStatus(&LPSPI20_InterruptDriverState);
}

#endif

ARM_DRIVER_SPI Driver_SPI20 = {
    LPSPIx_GetVersion,      LPSPIx_GetCapabilities,
#if defined(RTE_SPI20_DMA_EN) && RTE_SPI20_DMA_EN
    LPSPI20_EdmaInitialize, LPSPI20_EdmaUninitialize, LPSPI20_EdmaPowerControl, LPSPI20_EdmaSend,
    LPSPI20_EdmaReceive,    LPSPI20_EdmaTransfer,     LPSPI20_EdmaGetCount,     LPSPI20_EdmaControl,
    LPSPI20_EdmaGetStatus
#else
    LPSPI20_InterruptInitialize, LPSPI20_InterruptUninitialize, LPSPI20_InterruptPowerControl, LPSPI20_InterruptSend,
    LPSPI20_InterruptReceive,    LPSPI20_InterruptTransfer,     LPSPI20_InterruptGetCount,     LPSPI20_InterruptControl,
    LPSPI20_InterruptGetStatus
#endif
};

#endif /*  LPSPI20  */
