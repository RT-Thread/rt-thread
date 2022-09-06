/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_enet.h"
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
#include "fsl_cache.h"
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.enet"
#endif

/*! @brief Ethernet mac address length. */
#define ENET_FRAME_MACLEN 6U
/*! @brief MDC frequency. */
#define ENET_MDC_FREQUENCY 2500000U
/*! @brief NanoSecond in one second. */
#define ENET_NANOSECOND_ONE_SECOND 1000000000U

/*! @brief Define the ENET ring/class bumber . */
enum
{
    kENET_Ring0 = 0U, /*!< ENET ring/class 0. */
#if FSL_FEATURE_ENET_QUEUE > 1
    kENET_Ring1 = 1U, /*!< ENET ring/class 1. */
    kENET_Ring2 = 2U  /*!< ENET ring/class 2. */
#endif                /* FSL_FEATURE_ENET_QUEUE > 1 */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to enet clocks for each instance. */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
const clock_ip_name_t s_enetClock[] = ENET_CLOCKS;
#if defined(FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE) && FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE
const clock_ip_name_t s_enetExtraClock[] = ENET_EXTRA_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to enet transmit IRQ number for each instance. */
static const IRQn_Type s_enetTxIrqId[] = ENET_Transmit_IRQS;
/*! @brief Pointers to enet receive IRQ number for each instance. */
static const IRQn_Type s_enetRxIrqId[] = ENET_Receive_IRQS;
#if defined(ENET_ENHANCEDBUFFERDESCRIPTOR_MODE) && ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
/*! @brief Pointers to enet timestamp IRQ number for each instance. */
static const IRQn_Type s_enetTsIrqId[] = ENET_Ts_IRQS;
/*! @brief Pointers to enet 1588 timestamp IRQ number for each instance. */
static const IRQn_Type s_enet1588TimerIrqId[] = ENET_1588_Timer_IRQS;
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
/*! @brief Pointers to enet error IRQ number for each instance. */
static const IRQn_Type s_enetErrIrqId[] = ENET_Error_IRQS;

/*! @brief Pointers to enet bases for each instance. */
static ENET_Type *const s_enetBases[] = ENET_BASE_PTRS;

/*! @brief Pointers to enet handles for each instance. */
static enet_handle_t *s_ENETHandle[ARRAY_SIZE(s_enetBases)];

/* ENET ISR for transactional APIs. */
#if FSL_FEATURE_ENET_QUEUE > 1
static enet_isr_ring_t s_enetTxIsr[ARRAY_SIZE(s_enetBases)];
static enet_isr_ring_t s_enetRxIsr[ARRAY_SIZE(s_enetBases)];
#else
static enet_isr_t s_enetTxIsr[ARRAY_SIZE(s_enetBases)];
static enet_isr_t s_enetRxIsr[ARRAY_SIZE(s_enetBases)];
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
static enet_isr_t s_enetErrIsr[ARRAY_SIZE(s_enetBases)];
static enet_isr_t s_enetTsIsr[ARRAY_SIZE(s_enetBases)];
static enet_isr_t s_enet1588TimerIsr[ARRAY_SIZE(s_enetBases)];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Set ENET MAC controller with the configuration.
 *
 * @param base ENET peripheral base address.
 * @param handle The ENET handle pointer.
 * @param config ENET Mac configuration.
 * @param bufferConfig ENET buffer configuration.
 * @param macAddr ENET six-byte mac address.
 * @param srcClock_Hz ENET module clock source, normally it's system clock.
 */
static void ENET_SetMacController(ENET_Type *base,
                                  enet_handle_t *handle,
                                  const enet_config_t *config,
                                  const enet_buffer_config_t *bufferConfig,
                                  uint8_t *macAddr,
                                  uint32_t srcClock_Hz);

/*!
 * @brief Set ENET handler.
 *
 * @param base ENET peripheral base address.
 * @param handle The ENET handle pointer.
 * @param config ENET configuration stucture pointer.
 * @param bufferConfig ENET buffer configuration.
 */
static void ENET_SetHandler(ENET_Type *base,
                            enet_handle_t *handle,
                            const enet_config_t *config,
                            const enet_buffer_config_t *bufferConfig,
                            uint32_t srcClock_Hz);

/*!
 * @brief Set ENET MAC transmit buffer descriptors.
 *
 * @param handle The ENET handle pointer.
 * @param config The ENET configuration structure.
 * @param bufferConfig The ENET buffer configuration.
 */
static void ENET_SetTxBufferDescriptors(enet_handle_t *handle,
                                        const enet_config_t *config,
                                        const enet_buffer_config_t *bufferConfig);

/*!
 * @brief Set ENET MAC receive buffer descriptors.
 *
 * @param handle The ENET handle pointer.
 * @param config The ENET configuration structure.
 * @param bufferConfig The ENET buffer configuration.
 */
static void ENET_SetRxBufferDescriptors(enet_handle_t *handle,
                                        const enet_config_t *config,
                                        const enet_buffer_config_t *bufferConfig);

/*!
 * @brief Updates the ENET read buffer descriptors.
 *
 * @param base ENET peripheral base address.
 * @param handle The ENET handle pointer.
 * @param ringId The descriptor ring index, range from 0 ~ (FSL_FEATURE_ENET_INSTANCE_QUEUEn(x) - 1).
 */
static void ENET_UpdateReadBuffers(ENET_Type *base, enet_handle_t *handle, uint8_t ringId);

/*!
 * @brief Updates index.
 */
static uint16_t ENET_IncreaseIndex(uint16_t index, uint16_t max);

/*!
 * @brief Allocates all Rx buffers in BDs.
 */
static status_t ENET_RxBufferAllocAll(ENET_Type *base, enet_handle_t *handle);

/*!
 * @brief Frees all Rx buffers in BDs.
 */
static void ENET_RxBufferFreeAll(ENET_Type *base, enet_handle_t *handle);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
uint32_t ENET_GetInstance(ENET_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_enetBases); instance++)
    {
        if (s_enetBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_enetBases));

    return instance;
}

/*!
 * brief Gets the ENET default configuration structure.
 *
 * The purpose of this API is to get the default ENET MAC controller
 * configure structure for ENET_Init(). User may use the initialized
 * structure unchanged in ENET_Init(), or modify some fields of the
 * structure before calling ENET_Init().
 * Example:
   code
   enet_config_t config;
   ENET_GetDefaultConfig(&config);
   endcode
 * param config The ENET mac controller configuration structure pointer.
 */
void ENET_GetDefaultConfig(enet_config_t *config)
{
    /* Checks input parameter. */
    assert(config != NULL);

    /* Initializes the MAC configure structure to zero. */
    (void)memset(config, 0, sizeof(enet_config_t));

    /* Sets MII mode, full duplex, 100Mbps for MAC and PHY data interface. */
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
    config->miiMode = kENET_RgmiiMode;
#else
    config->miiMode = kENET_RmiiMode;
#endif
    config->miiSpeed  = kENET_MiiSpeed100M;
    config->miiDuplex = kENET_MiiFullDuplex;

    config->ringNum = 1;

    /* Sets the maximum receive frame length. */
    config->rxMaxFrameLen = ENET_FRAME_MAX_FRAMELEN;
}

/*!
 * brief Initializes the ENET module.
 *
 * This function initializes the module with the ENET configuration.
 * note ENET has two buffer descriptors legacy buffer descriptors and
 * enhanced IEEE 1588 buffer descriptors. The legacy descriptor is used by default. To
 * use the IEEE 1588 feature, use the enhanced IEEE 1588 buffer descriptor
 * by defining "ENET_ENHANCEDBUFFERDESCRIPTOR_MODE" and calling ENET_Ptp1588Configure()
 * to configure the 1588 feature and related buffers after calling ENET_Up().
 *
 * param base    ENET peripheral base address.
 * param handle  ENET handler pointer.
 * param config  ENET mac configuration structure pointer.
 *        The "enet_config_t" type mac configuration return from ENET_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * param bufferConfig  ENET buffer configuration structure pointer.
 *        The buffer configuration should be prepared for ENET Initialization.
 *        It is the start address of "ringNum" enet_buffer_config structures.
 *        To support added multi-ring features in some soc and compatible with the previous
 *        enet driver version. For single ring supported, this bufferConfig is a buffer
 *        configure structure pointer, for multi-ring supported and used case, this bufferConfig
 *        pointer should be a buffer configure structure array pointer.
 * param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * param srcClock_Hz The internal module clock source for MII clock.
 * retval kStatus_Success  Succeed to initialize the ethernet driver.
 * retval kStatus_ENET_InitMemoryFail  Init fails since buffer memory is not enough.
 */
status_t ENET_Up(ENET_Type *base,
                 enet_handle_t *handle,
                 const enet_config_t *config,
                 const enet_buffer_config_t *bufferConfig,
                 uint8_t *macAddr,
                 uint32_t srcClock_Hz)
{
    /* Checks input parameters. */
    assert(handle != NULL);
    assert(config != NULL);
    assert(bufferConfig != NULL);
    assert(macAddr != NULL);
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);
    assert(config->ringNum <= (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    status_t result = kStatus_Success;

    /* Initializes the ENET transmit buffer descriptors. */
    ENET_SetTxBufferDescriptors(handle, config, bufferConfig);

    /* Initializes the ENET receive buffer descriptors. */
    ENET_SetRxBufferDescriptors(handle, config, bufferConfig);

    /* Initializes the ENET MAC controller with basic function. */
    ENET_SetMacController(base, handle, config, bufferConfig, macAddr, srcClock_Hz);

    /* Set all buffers or data in handler for data transmit/receive process. */
    ENET_SetHandler(base, handle, config, bufferConfig, srcClock_Hz);

    /* Allocate buffers for all Rx BDs when zero copy Rx API is needed. */
    if (handle->rxBuffAlloc != NULL)
    {
        result = ENET_RxBufferAllocAll(base, handle);
    }

    return result;
}

/*!
 * brief Initializes the ENET module.
 *
 * This function ungates the module clock and initializes it with the ENET configuration.
 * note ENET has two buffer descriptors legacy buffer descriptors and
 * enhanced IEEE 1588 buffer descriptors. The legacy descriptor is used by default. To
 * use the IEEE 1588 feature, use the enhanced IEEE 1588 buffer descriptor
 * by defining "ENET_ENHANCEDBUFFERDESCRIPTOR_MODE" and calling ENET_Ptp1588Configure()
 * to configure the 1588 feature and related buffers after calling ENET_Init().
 *
 * param base    ENET peripheral base address.
 * param handle  ENET handler pointer.
 * param config  ENET mac configuration structure pointer.
 *        The "enet_config_t" type mac configuration return from ENET_GetDefaultConfig
 *        can be used directly. It is also possible to verify the Mac configuration using other methods.
 * param bufferConfig  ENET buffer configuration structure pointer.
 *        The buffer configuration should be prepared for ENET Initialization.
 *        It is the start address of "ringNum" enet_buffer_config structures.
 *        To support added multi-ring features in some soc and compatible with the previous
 *        enet driver version. For single ring supported, this bufferConfig is a buffer
 *        configure structure pointer, for multi-ring supported and used case, this bufferConfig
 *        pointer should be a buffer configure structure array pointer.
 * param macAddr  ENET mac address of Ethernet device. This MAC address should be
 *        provided.
 * param srcClock_Hz The internal module clock source for MII clock.
 * retval kStatus_Success  Succeed to initialize the ethernet driver.
 * retval kStatus_ENET_InitMemoryFail  Init fails since buffer memory is not enough.
 */
status_t ENET_Init(ENET_Type *base,
                   enet_handle_t *handle,
                   const enet_config_t *config,
                   const enet_buffer_config_t *bufferConfig,
                   uint8_t *macAddr,
                   uint32_t srcClock_Hz)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = ENET_GetInstance(base);

    /* Ungate ENET clock. */
    (void)CLOCK_EnableClock(s_enetClock[instance]);

#if defined(FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE) && FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE
    /* Ungate ENET extra clock. */
    (void)CLOCK_EnableClock(s_enetExtraClock[instance]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Reset ENET module. */
    ENET_Reset(base);

    return ENET_Up(base, handle, config, bufferConfig, macAddr, srcClock_Hz);
}

/*!
 * brief Stops the ENET module.

 * This function disables the ENET module.
 *
 * param base  ENET peripheral base address.
 */
void ENET_Down(ENET_Type *base)
{
    uint32_t instance     = ENET_GetInstance(base);
    enet_handle_t *handle = s_ENETHandle[instance];

    /* Disable interrupt. */
    base->EIMR = 0;

    /* Disable ENET. */
    base->ECR &= ~ENET_ECR_ETHEREN_MASK;

    if (handle->rxBuffFree != NULL)
    {
        ENET_RxBufferFreeAll(base, handle);
    }
}

/*!
 * brief Deinitializes the ENET module.

 * This function gates the module clock, clears ENET interrupts, and disables the ENET module.
 *
 * param base  ENET peripheral base address.
 */
void ENET_Deinit(ENET_Type *base)
{
    ENET_Down(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disables the clock source. */
    (void)CLOCK_DisableClock(s_enetClock[ENET_GetInstance(base)]);

#if defined(FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE) && FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE
    /* Disables ENET extra clock. */
    (void)CLOCK_DisableClock(s_enetExtraClock[ENET_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * deprecated Do not use this function. It has been superceded by the config param in @ref ENET_Init.
 */
void ENET_SetCallback(enet_handle_t *handle, enet_callback_t callback, void *userData)
{
    assert(handle != NULL);

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;
}

#if FSL_FEATURE_ENET_QUEUE > 1
void ENET_SetRxISRHandler(ENET_Type *base, enet_isr_ring_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enetRxIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enetRxIrqId[instance]);
}

void ENET_SetTxISRHandler(ENET_Type *base, enet_isr_ring_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enetTxIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enetTxIrqId[instance]);
}
#else
void ENET_SetRxISRHandler(ENET_Type *base, enet_isr_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enetRxIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enetRxIrqId[instance]);
}

void ENET_SetTxISRHandler(ENET_Type *base, enet_isr_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enetTxIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enetTxIrqId[instance]);
}
#endif

void ENET_SetErrISRHandler(ENET_Type *base, enet_isr_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enetErrIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enetErrIrqId[instance]);
}

#if defined(ENET_ENHANCEDBUFFERDESCRIPTOR_MODE) && ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
void ENET_SetTsISRHandler(ENET_Type *base, enet_isr_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enetTsIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enetTsIrqId[instance]);
}

void ENET_Set1588TimerISRHandler(ENET_Type *base, enet_isr_t ISRHandler)
{
    uint32_t instance = ENET_GetInstance(base);

    s_enet1588TimerIsr[instance] = ISRHandler;
    (void)EnableIRQ(s_enet1588TimerIrqId[instance]);
}
#endif

static void ENET_SetHandler(ENET_Type *base,
                            enet_handle_t *handle,
                            const enet_config_t *config,
                            const enet_buffer_config_t *bufferConfig,
                            uint32_t srcClock_Hz)
{
    uint8_t count;
    uint32_t instance                   = ENET_GetInstance(base);
    const enet_buffer_config_t *buffCfg = bufferConfig;

    /* Store transfer parameters in handle pointer. */
    (void)memset(handle, 0, sizeof(enet_handle_t));

    for (count = 0; count < config->ringNum; count++)
    {
        assert(buffCfg->rxBuffSizeAlign * buffCfg->rxBdNumber > config->rxMaxFrameLen);

        handle->rxBdRing[count].rxBdBase       = buffCfg->rxBdStartAddrAlign;
        handle->rxBuffSizeAlign[count]         = buffCfg->rxBuffSizeAlign;
        handle->rxBdRing[count].rxRingLen      = buffCfg->rxBdNumber;
        handle->rxMaintainEnable[count]        = buffCfg->rxMaintainEnable;
        handle->txBdRing[count].txBdBase       = buffCfg->txBdStartAddrAlign;
        handle->txBuffSizeAlign[count]         = buffCfg->txBuffSizeAlign;
        handle->txBdRing[count].txRingLen      = buffCfg->txBdNumber;
        handle->txMaintainEnable[count]        = buffCfg->txMaintainEnable;
        handle->txDirtyRing[count].txDirtyBase = buffCfg->txFrameInfo;
        handle->txDirtyRing[count].txRingLen   = buffCfg->txBdNumber;
        buffCfg++;
    }

    handle->ringNum     = config->ringNum;
    handle->rxBuffAlloc = config->rxBuffAlloc;
    handle->rxBuffFree  = config->rxBuffFree;
    handle->callback    = config->callback;
    handle->userData    = config->userData;
#if defined(FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID) && FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID
    handle->enetClock = srcClock_Hz;
#endif

    /* Save the handle pointer in the global variables. */
    s_ENETHandle[instance] = handle;

    /* Set the IRQ handler when the interrupt is enabled. */
    if (0U != (config->interrupt & (uint32_t)ENET_TX_INTERRUPT))
    {
        ENET_SetTxISRHandler(base, ENET_TransmitIRQHandler);
    }
    if (0U != (config->interrupt & (uint32_t)ENET_RX_INTERRUPT))
    {
        ENET_SetRxISRHandler(base, ENET_ReceiveIRQHandler);
    }
    if (0U != (config->interrupt & (uint32_t)ENET_ERR_INTERRUPT))
    {
        ENET_SetErrISRHandler(base, ENET_ErrorIRQHandler);
    }
}

static void ENET_SetMacController(ENET_Type *base,
                                  enet_handle_t *handle,
                                  const enet_config_t *config,
                                  const enet_buffer_config_t *bufferConfig,
                                  uint8_t *macAddr,
                                  uint32_t srcClock_Hz)
{
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
    if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(base) == 1)
    {
        /* Check the MII mode/speed/duplex setting. */
        if (config->miiSpeed == kENET_MiiSpeed1000M)
        {
            /* Only RGMII mode has the 1000M bit/s. The 1000M only support full duplex. */
            assert(config->miiMode == kENET_RgmiiMode);
            assert(config->miiDuplex == kENET_MiiFullDuplex);
        }
    }
#endif /* FSL_FEATURE_ENET_HAS_AVB */

    uint32_t rcr              = 0;
    uint32_t tcr              = 0;
    uint32_t ecr              = base->ECR;
    uint32_t macSpecialConfig = config->macSpecialConfig;
    uint32_t maxFrameLen      = config->rxMaxFrameLen;
    uint32_t configVal        = 0;

    /* Maximum frame length check. */
    if (0U != (macSpecialConfig & (uint32_t)kENET_ControlVLANTagEnable))
    {
        maxFrameLen = (ENET_FRAME_MAX_FRAMELEN + ENET_FRAME_VLAN_TAGLEN);
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
        if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(base) == 1)
        {
            if (0U != (macSpecialConfig & (uint32_t)kENET_ControlSVLANEnable))
            {
                /* Double vlan tag (SVLAN) supported. */
                maxFrameLen += ENET_FRAME_VLAN_TAGLEN;
            }
            ecr |= (uint32_t)(((macSpecialConfig & (uint32_t)kENET_ControlSVLANEnable) != 0U) ?
                                  (ENET_ECR_SVLANEN_MASK | ENET_ECR_SVLANDBL_MASK) :
                                  0U) |
                   (uint32_t)(((macSpecialConfig & (uint32_t)kENET_ControlVLANUseSecondTag) != 0U) ?
                                  ENET_ECR_VLANUSE2ND_MASK :
                                  0U);
        }
#endif /* FSL_FEATURE_ENET_HAS_AVB */
    }

    /* Configures MAC receive controller with user configure structure. */
    rcr = ((0U != (macSpecialConfig & (uint32_t)kENET_ControlRxPayloadCheckEnable)) ? ENET_RCR_NLC_MASK : 0U) |
          ((0U != (macSpecialConfig & (uint32_t)kENET_ControlFlowControlEnable)) ? ENET_RCR_CFEN_MASK : 0U) |
          ((0U != (macSpecialConfig & (uint32_t)kENET_ControlFlowControlEnable)) ? ENET_RCR_FCE_MASK : 0U) |
          ((0U != (macSpecialConfig & (uint32_t)kENET_ControlRxPadRemoveEnable)) ? ENET_RCR_PADEN_MASK : 0U) |
          ((0U != (macSpecialConfig & (uint32_t)kENET_ControlRxBroadCastRejectEnable)) ? ENET_RCR_BC_REJ_MASK : 0U) |
          ((0U != (macSpecialConfig & (uint32_t)kENET_ControlPromiscuousEnable)) ? ENET_RCR_PROM_MASK : 0U) |
          ENET_RCR_MAX_FL(maxFrameLen) | ENET_RCR_CRCFWD_MASK;

/* Set the RGMII or RMII, MII mode and control register. */
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
    if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(base) == 1)
    {
        if (config->miiMode == kENET_RgmiiMode)
        {
            rcr |= ENET_RCR_RGMII_EN_MASK;
        }
        else
        {
            rcr &= ~ENET_RCR_RGMII_EN_MASK;
        }

        if (config->miiSpeed == kENET_MiiSpeed1000M)
        {
            ecr |= ENET_ECR_SPEED_MASK;
        }
        else
        {
            ecr &= ~ENET_ECR_SPEED_MASK;
        }
    }
#endif /* FSL_FEATURE_ENET_HAS_AVB */
    rcr |= ENET_RCR_MII_MODE_MASK;
    if (config->miiMode == kENET_RmiiMode)
    {
        rcr |= ENET_RCR_RMII_MODE_MASK;
    }

    /* Speed. */
    if (config->miiSpeed == kENET_MiiSpeed10M)
    {
        rcr |= ENET_RCR_RMII_10T_MASK;
    }

    /* Receive setting for half duplex. */
    if (config->miiDuplex == kENET_MiiHalfDuplex)
    {
        rcr |= ENET_RCR_DRT_MASK;
    }
    /* Sets internal loop only for MII mode. */
    if ((0U != (config->macSpecialConfig & (uint32_t)kENET_ControlMIILoopEnable)) &&
        (config->miiMode != kENET_RmiiMode))
    {
        rcr |= ENET_RCR_LOOP_MASK;
        rcr &= ~ENET_RCR_DRT_MASK;
    }
    base->RCR = rcr;

    /* Configures MAC transmit controller: duplex mode, mac address insertion. */
    tcr = base->TCR & ~(ENET_TCR_FDEN_MASK | ENET_TCR_ADDINS_MASK);
    tcr |= ((kENET_MiiHalfDuplex != config->miiDuplex) ? (uint32_t)ENET_TCR_FDEN_MASK : 0U) |
           ((0U != (macSpecialConfig & (uint32_t)kENET_ControlMacAddrInsert)) ? (uint32_t)ENET_TCR_ADDINS_MASK : 0U);
    base->TCR = tcr;

    /* Configures receive and transmit accelerator. */
    base->TACC = config->txAccelerConfig;
    base->RACC = config->rxAccelerConfig;

    /* Sets the pause duration and FIFO threshold for the flow control enabled case. */
    if (0U != (macSpecialConfig & (uint32_t)kENET_ControlFlowControlEnable))
    {
        uint32_t reemReg;
        base->OPD = config->pauseDuration;
        reemReg   = ENET_RSEM_RX_SECTION_EMPTY(config->rxFifoEmptyThreshold);
#if defined(FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD) && FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD
        reemReg |= ENET_RSEM_STAT_SECTION_EMPTY(config->rxFifoStatEmptyThreshold);
#endif /* FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD */
        base->RSEM = reemReg;
    }

    /* FIFO threshold setting for store and forward enable/disable case. */
    if (0U != (macSpecialConfig & (uint32_t)kENET_ControlStoreAndFwdDisable))
    {
        /* Transmit fifo watermark settings. */
        configVal  = ((uint32_t)config->txFifoWatermark) & ENET_TFWR_TFWR_MASK;
        base->TFWR = configVal;
        /* Receive fifo full threshold settings. */
        configVal  = ((uint32_t)config->rxFifoFullThreshold) & ENET_RSFL_RX_SECTION_FULL_MASK;
        base->RSFL = configVal;
    }
    else
    {
        /* Transmit fifo watermark settings. */
        base->TFWR = ENET_TFWR_STRFWD_MASK;
        base->RSFL = 0;
    }

    /* Enable store and forward when accelerator is enabled */
    if (0U !=
        (config->txAccelerConfig & ((uint32_t)kENET_TxAccelIpCheckEnabled | (uint32_t)kENET_TxAccelProtoCheckEnabled)))
    {
        base->TFWR = ENET_TFWR_STRFWD_MASK;
    }
    if (0U != ((config->rxAccelerConfig &
                ((uint32_t)kENET_RxAccelIpCheckEnabled | (uint32_t)kENET_RxAccelProtoCheckEnabled))))
    {
        base->RSFL = 0;
    }

/* Initializes the ring 0. */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    base->TDSR = MEMORY_ConvertMemoryMapAddress((uint32_t)bufferConfig->txBdStartAddrAlign, kMEMORY_Local2DMA);
    base->RDSR = MEMORY_ConvertMemoryMapAddress((uint32_t)bufferConfig->rxBdStartAddrAlign, kMEMORY_Local2DMA);
#else
    base->TDSR = (uint32_t)bufferConfig->txBdStartAddrAlign;
    base->RDSR = (uint32_t)bufferConfig->rxBdStartAddrAlign;
#endif
    base->MRBR = (uint32_t)bufferConfig->rxBuffSizeAlign;

#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
    if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(base) == 1)
    {
        const enet_buffer_config_t *buffCfg = bufferConfig;

        if (config->ringNum > 1U)
        {
            /* Initializes the ring 1. */
            buffCfg++;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            base->TDSR1 = MEMORY_ConvertMemoryMapAddress((uint32_t)buffCfg->txBdStartAddrAlign, kMEMORY_Local2DMA);
            base->RDSR1 = MEMORY_ConvertMemoryMapAddress((uint32_t)buffCfg->rxBdStartAddrAlign, kMEMORY_Local2DMA);
#else
            base->TDSR1 = (uint32_t)buffCfg->txBdStartAddrAlign;
            base->RDSR1 = (uint32_t)buffCfg->rxBdStartAddrAlign;
#endif
            base->MRBR1 = (uint32_t)buffCfg->rxBuffSizeAlign;
            /* Enable the DMAC for ring 1 and with no rx classification set. */
            base->DMACFG[0] = ENET_DMACFG_DMA_CLASS_EN_MASK;
        }
        if (config->ringNum > 2U)
        {
            /* Initializes the ring 2. */
            buffCfg++;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            base->TDSR2 = MEMORY_ConvertMemoryMapAddress((uint32_t)buffCfg->txBdStartAddrAlign, kMEMORY_Local2DMA);
            base->RDSR2 = MEMORY_ConvertMemoryMapAddress((uint32_t)buffCfg->rxBdStartAddrAlign, kMEMORY_Local2DMA);
#else
            base->TDSR2 = (uint32_t)buffCfg->txBdStartAddrAlign;
            base->RDSR2 = (uint32_t)buffCfg->rxBdStartAddrAlign;
#endif
            base->MRBR2 = (uint32_t)buffCfg->rxBuffSizeAlign;
            /* Enable the DMAC for ring 2 and with no rx classification set. */
            base->DMACFG[1] = ENET_DMACFG_DMA_CLASS_EN_MASK;
        }

        /* Defaulting the class/ring 1 and 2 are not enabled and the receive classification is disabled
         * so we set the default transmit scheme with the round-robin mode. Beacuse the legacy bd mode
         * only supports the round-robin mode. If the avb feature is required, just call the setup avb
         * feature API. */
        base->QOS |= ENET_QOS_TX_SCHEME(1);
    }
#endif /*  FSL_FEATURE_ENET_HAS_AVB */

    /* Configures the Mac address. */
    ENET_SetMacAddr(base, macAddr);

    /* Initialize the SMI if uninitialized. */
    if (!ENET_GetSMI(base))
    {
        ENET_SetSMI(base, srcClock_Hz,
                    ((0U != (config->macSpecialConfig & (uint32_t)kENET_ControlSMIPreambleDisable)) ? true : false));
    }

/* Enables Ethernet interrupt, enables the interrupt coalsecing if it is required. */
#if defined(FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE) && FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE
    uint8_t queue = 0;

    if (NULL != config->intCoalesceCfg)
    {
        uint32_t intMask = (ENET_EIMR_TXB_MASK | ENET_EIMR_RXB_MASK);

#if FSL_FEATURE_ENET_QUEUE > 1
        if (FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) > 1)
        {
            intMask |= ENET_EIMR_TXB2_MASK | ENET_EIMR_RXB2_MASK | ENET_EIMR_TXB1_MASK | ENET_EIMR_RXB1_MASK;
        }
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */

        /* Clear all buffer interrupts. */
        base->EIMR &= ~intMask;

        /* Set the interrupt coalescence. */
        for (queue = 0; queue < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base); queue++)
        {
            base->TXIC[queue] = ENET_TXIC_ICFT(config->intCoalesceCfg->txCoalesceFrameCount[queue]) |
                                config->intCoalesceCfg->txCoalesceTimeCount[queue] | ENET_TXIC_ICCS_MASK |
                                ENET_TXIC_ICEN_MASK;
            base->RXIC[queue] = ENET_RXIC_ICFT(config->intCoalesceCfg->rxCoalesceFrameCount[queue]) |
                                config->intCoalesceCfg->rxCoalesceTimeCount[queue] | ENET_RXIC_ICCS_MASK |
                                ENET_RXIC_ICEN_MASK;
        }
    }
#endif /* FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE */
    ENET_EnableInterrupts(base, config->interrupt);

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    /* Sets the 1588 enhanced feature. */
    ecr |= ENET_ECR_EN1588_MASK;
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
    /* Enables Ethernet module after all configuration except the buffer descriptor active. */
    ecr |= ENET_ECR_ETHEREN_MASK | ENET_ECR_DBSWP_MASK;
    base->ECR = ecr;
}

static void ENET_SetTxBufferDescriptors(enet_handle_t *handle,
                                        const enet_config_t *config,
                                        const enet_buffer_config_t *bufferConfig)
{
    assert(config != NULL);
    assert(bufferConfig != NULL);

    /* Default single ring is supported. */
    uint8_t ringNum;
    uint16_t count;
    uint32_t txBuffSizeAlign;
    uint8_t *txBuffer                   = NULL;
    const enet_buffer_config_t *buffCfg = bufferConfig;

    /* Check the input parameters. */
    for (ringNum = 0; ringNum < config->ringNum; ringNum++)
    {
        if (buffCfg->txBdStartAddrAlign != NULL)
        {
            volatile enet_tx_bd_struct_t *curBuffDescrip = buffCfg->txBdStartAddrAlign;
            txBuffSizeAlign                              = buffCfg->txBuffSizeAlign;

            if (buffCfg->txBufferAlign != NULL)
            {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                txBuffer =
                    (uint8_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)buffCfg->txBufferAlign, kMEMORY_Local2DMA);
#else
                txBuffer = buffCfg->txBufferAlign;
#endif
            }

            for (count = 0; count < buffCfg->txBdNumber; count++)
            {
                if (buffCfg->txBufferAlign != NULL)
                {
                    /* Set data buffer address. */
                    curBuffDescrip->buffer = (uint8_t *)((uint32_t)&txBuffer[count * txBuffSizeAlign]);
                }
                /* Initializes data length. */
                curBuffDescrip->length = 0;
                /* Sets the crc. */
                curBuffDescrip->control = ENET_BUFFDESCRIPTOR_TX_TRANMITCRC_MASK;
                /* Sets the last buffer descriptor with the wrap flag. */
                if (count == (buffCfg->txBdNumber - 1U))
                {
                    curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_TX_WRAP_MASK;
                }

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                /* Enable transmit interrupt for store the transmit timestamp. */
                curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_INTERRUPT_MASK;
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
                /* Set the type of the frame when the credit-based scheme is used. */
                curBuffDescrip->controlExtend1 |= (uint16_t)(ENET_BD_FTYPE(ringNum));
#endif /* FSL_FEATURE_ENET_HAS_AVB */
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
                /* Increase the index. */
                curBuffDescrip++;
            }
        }
        buffCfg++;
    }
}

static void ENET_SetRxBufferDescriptors(enet_handle_t *handle,
                                        const enet_config_t *config,
                                        const enet_buffer_config_t *bufferConfig)
{
    assert(config != NULL);
    assert(bufferConfig != NULL);

    /* Default single ring is supported. */
    uint8_t ringNum;
    uint16_t count;
    uint16_t rxBuffSizeAlign;
    uint8_t *rxBuffer;
    const enet_buffer_config_t *buffCfg = bufferConfig;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    uint32_t mask = ((uint32_t)kENET_RxFrameInterrupt | (uint32_t)kENET_RxBufferInterrupt);
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

    /* Check the input parameters. */
    for (ringNum = 0; ringNum < config->ringNum; ringNum++)
    {
        assert(buffCfg->rxBuffSizeAlign >= ENET_RX_MIN_BUFFERSIZE);
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
#if FSL_FEATURE_ENET_QUEUE > 1
        if (ringNum == 1U)
        {
            mask = ((uint32_t)kENET_RxFrame1Interrupt | (uint32_t)kENET_RxBuffer1Interrupt);
        }
        else if (ringNum == 2U)
        {
            mask = ((uint32_t)kENET_RxFrame2Interrupt | (uint32_t)kENET_RxBuffer2Interrupt);
        }
        else
        {
            /* Intentional empty */
        }
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

        if ((buffCfg->rxBdStartAddrAlign != NULL) && ((buffCfg->rxBufferAlign != NULL) || config->rxBuffAlloc != NULL))
        {
            volatile enet_rx_bd_struct_t *curBuffDescrip = buffCfg->rxBdStartAddrAlign;
            rxBuffSizeAlign                              = buffCfg->rxBuffSizeAlign;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            rxBuffer = (uint8_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)buffCfg->rxBufferAlign, kMEMORY_Local2DMA);
#else
            rxBuffer = buffCfg->rxBufferAlign;
#endif

#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
            if (buffCfg->rxMaintainEnable)
            {
                /* Invalidate rx buffers before DMA transfer data into them. */
                DCACHE_InvalidateByRange((uint32_t)rxBuffer, ((uint32_t)buffCfg->rxBdNumber * rxBuffSizeAlign));
            }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */

            for (count = 0; count < buffCfg->rxBdNumber; count++)
            {
                /* Set data buffer and the length. */
                curBuffDescrip->length = 0;
                if (config->rxBuffAlloc == NULL)
                {
                    curBuffDescrip->buffer = (uint8_t *)((uint32_t)&rxBuffer[count * rxBuffSizeAlign]);
                    /* Initializes the buffer descriptors with empty bit. */
                    curBuffDescrip->control = ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
                }

                /* Sets the last buffer descriptor with the wrap flag. */
                if (count == (buffCfg->rxBdNumber - 1U))
                {
                    curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
                }

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                if (0U != (config->interrupt & mask))
                {
                    /* Enable receive interrupt. */
                    curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_RX_INTERRUPT_MASK;
                }
                else
                {
                    curBuffDescrip->controlExtend1 = 0;
                }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
                /* Increase the index. */
                curBuffDescrip++;
            }
        }
        buffCfg++;
    }
}

/*!
 * brief Allocates all Rx buffers in BDs.
 */
static status_t ENET_RxBufferAllocAll(ENET_Type *base, enet_handle_t *handle)
{
    assert(handle->rxBuffAlloc != NULL);

    enet_rx_bd_ring_t *rxBdRing;
    volatile enet_rx_bd_struct_t *curBuffDescrip;
    uint16_t index;
    void *buffer;
    uint16_t ringId;

    /* Allocate memory for all empty buffers in buffer descriptor */
    for (ringId = 0; ringId < handle->ringNum; ringId++)
    {
        assert(handle->rxBdRing[ringId].rxBdBase != NULL);

        rxBdRing       = &handle->rxBdRing[ringId];
        curBuffDescrip = rxBdRing->rxBdBase;
        index          = 0;

        do
        {
            buffer = handle->rxBuffAlloc(base, handle->userData, ringId);
            if (buffer == NULL)
            {
                ENET_RxBufferFreeAll(base, handle);
                return kStatus_ENET_InitMemoryFail;
            }

#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
            if (handle->rxMaintainEnable[ringId])
            {
                /* Invalidate cache in case any unfinished cache operation occurs. */
                DCACHE_InvalidateByRange((uint32_t)(uint32_t *)buffer, handle->rxBuffSizeAlign[ringId]);
            }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            buffer =
                (void *)(uint32_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)buffer, kMEMORY_Local2DMA);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
            curBuffDescrip->buffer = (uint8_t *)(uint32_t *)buffer;
            curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;

            /* Increase the buffer descriptor, if it's the last one, increase to first one of the ring. */
            index          = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
            curBuffDescrip = rxBdRing->rxBdBase + index;
        } while (index != 0U);
    }
    return kStatus_Success;
}

/*!
 * brief Frees all Rx buffers in BDs.
 */
static void ENET_RxBufferFreeAll(ENET_Type *base, enet_handle_t *handle)
{
    assert(handle->rxBuffFree != NULL);

    uint16_t index;
    enet_rx_bd_ring_t *rxBdRing;
    volatile enet_rx_bd_struct_t *curBuffDescrip;
    void *buffer;
    uint16_t ringId;

    for (ringId = 0; ringId < handle->ringNum; ringId++)
    {
        assert(handle->rxBdRing[ringId].rxBdBase != NULL);

        rxBdRing       = &handle->rxBdRing[ringId];
        curBuffDescrip = rxBdRing->rxBdBase;
        index          = 0;

        /* Free memory for all buffers in buffer descriptor */
        do
        {
            if (curBuffDescrip->buffer != NULL)
            {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                buffer = (void *)(uint32_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer,
                                                                            kMEMORY_DMA2Local);
#else
                buffer = curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                handle->rxBuffFree(base, buffer, handle->userData, ringId);
                curBuffDescrip->buffer = NULL;
                /* Clears status. */
                curBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            }

            /* Increase the buffer descriptor, if it's the last one, increase to first one of the ring. */
            index          = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
            curBuffDescrip = rxBdRing->rxBdBase + index;
        } while (index != 0U);
    }
}

/*!
 * brief Activates frame reception for specified ring.
 *
 * This function is to active the enet read process for specified ring.
 * note This must be called after the MAC configuration and
 * state are ready. It must be called after the ENET_Init() and
 * ENET_Ptp1588Configure(). This should be called when the ENET receive required.
 *
 * param base  ENET peripheral base address.
 * param ringId The ring index, range from 0 ~ (FSL_FEATURE_ENET_INSTANCE_QUEUEn(x) - 1).
 */
static inline void ENET_ActiveReadRing(ENET_Type *base, uint8_t ringId)
{
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    /* Ensure previous data update is completed with Data Synchronization Barrier before activing Rx BD. */
    __DSB();

    /* Actives the receive buffer descriptor. */
    switch (ringId)
    {
        case kENET_Ring0:
            base->RDAR = ENET_RDAR_RDAR_MASK;
            break;
#if FSL_FEATURE_ENET_QUEUE > 1
        case kENET_Ring1:
            base->RDAR1 = ENET_RDAR1_RDAR_MASK;
            break;
        case kENET_Ring2:
            base->RDAR2 = ENET_RDAR2_RDAR_MASK;
            break;
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        default:
            assert(false);
            break;
    }
}

/*!
 * brief Activates frame sending for specified ring.
 * note This must be called after the MAC configuration and
 * state are ready. It must be called after the ENET_Init() and
 * this should be called when the ENET receive required.
 *
 * param base  ENET peripheral base address.
 * param ringId The descriptor ring index, range from 0 ~ (FSL_FEATURE_ENET_INSTANCE_QUEUEn(x) - 1).
 *
 */
static void ENET_ActiveSendRing(ENET_Type *base, uint8_t ringId)
{
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    volatile uint32_t *txDesActive = NULL;

    /* Ensure previous data update is completed with Data Synchronization Barrier before activing Tx BD. */
    __DSB();

    switch (ringId)
    {
        case kENET_Ring0:
            txDesActive = &(base->TDAR);
            break;
#if FSL_FEATURE_ENET_QUEUE > 1
        case kENET_Ring1:
            txDesActive = &(base->TDAR1);
            break;
        case kENET_Ring2:
            txDesActive = &(base->TDAR2);
            break;
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        default:
            txDesActive = &(base->TDAR);
            break;
    }

#if defined(FSL_FEATURE_ENET_HAS_ERRATA_007885) && FSL_FEATURE_ENET_HAS_ERRATA_007885
    /* There is a TDAR race condition for mutliQ when the software sets TDAR
     * and the UDMA clears TDAR simultaneously or in a small window (2-4 cycles).
     * This will cause the udma_tx and udma_tx_arbiter state machines to hang.
     * Software workaround: introduces a delay by reading the relevant ENET_TDARn_TDAR 4 times
     */
    for (uint8_t i = 0; i < 4U; i++)
    {
        if (*txDesActive == 0U)
        {
            break;
        }
    }
#endif

    /* Write to active tx descriptor */
    *txDesActive = 0;
}

/*!
 * brief Sets the ENET MII speed and duplex.
 *
 * This API is provided to dynamically change the speed and dulpex for MAC.
 *
 * param base  ENET peripheral base address.
 * param speed The speed of the RMII mode.
 * param duplex The duplex of the RMII mode.
 */
void ENET_SetMII(ENET_Type *base, enet_mii_speed_t speed, enet_mii_duplex_t duplex)
{
    uint32_t rcr = base->RCR;
    uint32_t tcr = base->TCR;

#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
    if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(base) == 1)
    {
        uint32_t ecr = base->ECR;

        if (kENET_MiiSpeed1000M == speed)
        {
            assert(duplex == kENET_MiiFullDuplex);
            ecr |= ENET_ECR_SPEED_MASK;
        }
        else
        {
            ecr &= ~ENET_ECR_SPEED_MASK;
        }

        base->ECR = ecr;
    }
#endif /* FSL_FEATURE_ENET_HAS_AVB */

    /* Sets speed mode. */
    if (kENET_MiiSpeed10M == speed)
    {
        rcr |= ENET_RCR_RMII_10T_MASK;
    }
    else
    {
        rcr &= ~ENET_RCR_RMII_10T_MASK;
    }
    /* Set duplex mode. */
    if (duplex == kENET_MiiHalfDuplex)
    {
        rcr |= ENET_RCR_DRT_MASK;
        tcr &= ~ENET_TCR_FDEN_MASK;
    }
    else
    {
        rcr &= ~ENET_RCR_DRT_MASK;
        tcr |= ENET_TCR_FDEN_MASK;
    }

    base->RCR = rcr;
    base->TCR = tcr;
}

/*!
 * brief Sets the ENET module Mac address.
 *
 * param base  ENET peripheral base address.
 * param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 */
void ENET_SetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    uint32_t address;

    /* Set physical address lower register. */
    address = (uint32_t)(((uint32_t)macAddr[0] << 24U) | ((uint32_t)macAddr[1] << 16U) | ((uint32_t)macAddr[2] << 8U) |
                         (uint32_t)macAddr[3]);
    base->PALR = address;
    /* Set physical address high register. */
    address    = (uint32_t)(((uint32_t)macAddr[4] << 8U) | ((uint32_t)macAddr[5]));
    base->PAUR = address << ENET_PAUR_PADDR2_SHIFT;
}

/*!
 * brief Gets the ENET module Mac address.
 *
 * param base  ENET peripheral base address.
 * param macAddr The six-byte Mac address pointer.
 *        The pointer is allocated by application and input into the API.
 */
void ENET_GetMacAddr(ENET_Type *base, uint8_t *macAddr)
{
    assert(macAddr != NULL);

    uint32_t address;

    /* Get from physical address lower register. */
    address    = base->PALR;
    macAddr[0] = 0xFFU & (uint8_t)(address >> 24U);
    macAddr[1] = 0xFFU & (uint8_t)(address >> 16U);
    macAddr[2] = 0xFFU & (uint8_t)(address >> 8U);
    macAddr[3] = 0xFFU & (uint8_t)address;

    /* Get from physical address high register. */
    address    = (base->PAUR & ENET_PAUR_PADDR2_MASK) >> ENET_PAUR_PADDR2_SHIFT;
    macAddr[4] = 0xFFU & (uint8_t)(address >> 8U);
    macAddr[5] = 0xFFU & (uint8_t)address;
}

/*!
 * brief Sets the ENET SMI(serial management interface)- MII management interface.
 *
 * param base  ENET peripheral base address.
 * param srcClock_Hz This is the ENET module clock frequency. See clock distribution.
 * param isPreambleDisabled The preamble disable flag.
 *        - true   Enables the preamble.
 *        - false  Disables the preamble.
 */
void ENET_SetSMI(ENET_Type *base, uint32_t srcClock_Hz, bool isPreambleDisabled)
{
    /* Due to bits limitation of SPEED and HOLDTIME, srcClock_Hz must ensure MDC <= 2.5M and holdtime >= 10ns. */
    assert((srcClock_Hz != 0U) && (srcClock_Hz <= 320000000U));

    uint32_t clkCycle = 0;
    uint32_t speed    = 0;
    uint32_t mscr     = 0;

    /* Use (param + N - 1) / N to increase accuracy with rounding. */
    /* Calculate the MII speed which controls the frequency of the MDC. */
    speed = (srcClock_Hz + 2U * ENET_MDC_FREQUENCY - 1U) / (2U * ENET_MDC_FREQUENCY) - 1U;
    /* Calculate the hold time on the MDIO output. */
    clkCycle = (10U + ENET_NANOSECOND_ONE_SECOND / srcClock_Hz - 1U) / (ENET_NANOSECOND_ONE_SECOND / srcClock_Hz) - 1U;
    /* Build the configuration for MDC/MDIO control. */
    mscr =
        ENET_MSCR_MII_SPEED(speed) | ENET_MSCR_HOLDTIME(clkCycle) | (isPreambleDisabled ? ENET_MSCR_DIS_PRE_MASK : 0U);
    base->MSCR = mscr;
}

/*!
 * brief Starts an SMI write command.
 *
 * Used for standard IEEE802.3 MDIO Clause 22 format.
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register. Range from 0 ~ 31.
 * param operation The write operation.
 * param data The data written to PHY.
 */
void ENET_StartSMIWrite(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, enet_mii_write_t operation, uint32_t data)
{
    uint32_t mmfr = 0;

    /* Build MII write command. */
    mmfr = ENET_MMFR_ST(1U) | ENET_MMFR_OP(operation) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(phyReg) |
           ENET_MMFR_TA(2U) | (data & 0xFFFFU);
    base->MMFR = mmfr;
}

/*!
 * brief Starts an SMI (Serial Management Interface) read command.
 *
 * Used for standard IEEE802.3 MDIO Clause 22 format.
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register. Range from 0 ~ 31.
 * param operation The read operation.
 */
void ENET_StartSMIRead(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, enet_mii_read_t operation)
{
    uint32_t mmfr = 0;

    /* Build MII read command. */
    mmfr = ENET_MMFR_ST(1U) | ENET_MMFR_OP(operation) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(phyReg) | ENET_MMFR_TA(2U);
    base->MMFR = mmfr;
}

#if defined(FSL_FEATURE_ENET_HAS_EXTEND_MDIO) && FSL_FEATURE_ENET_HAS_EXTEND_MDIO
/*!
 * brief Starts the extended IEEE802.3 Clause 45 MDIO format SMI write register command.
 *
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register. For MDIO IEEE802.3 Clause 45,
 *        the phyReg is a 21-bits combination of the devaddr (5 bits device address)
 *        and the regAddr (16 bits phy register): phyReg = (devaddr << 16) | regAddr.
 */
void ENET_StartExtC45SMIWriteReg(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg)
{
    uint32_t mmfr = 0;

    /* Parse the address from the input register. */
    uint16_t devAddr = (uint16_t)((phyReg >> 16U) & 0x1FU);
    uint16_t regAddr = (uint16_t)(phyReg & 0xFFFFU);

    /* Address write. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiAddrWrite_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2) | ENET_MMFR_DATA(regAddr);
    base->MMFR = mmfr;
}

/*!
 * brief Starts the extended IEEE802.3 Clause 45 MDIO format SMI write data command.
 *
 * After writing MMFR register, we need to check whether the transmission is over.
 * This is an example for whole precedure of clause 45 MDIO write.
 * code
 *       ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
 *       ENET_StartExtC45SMIWriteReg(base, phyAddr, phyReg);
 *       while ((ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) == 0U)
 *       {
 *       }
 *       ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
 *       ENET_StartExtC45SMIWriteData(base, phyAddr, phyReg, data);
 *       while ((ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) == 0U)
 *       {
 *       }
 *       ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
 * endcode
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register. For MDIO IEEE802.3 Clause 45,
 *        the phyReg is a 21-bits combination of the devaddr (5 bits device address)
 *        and the regAddr (16 bits phy register): phyReg = (devaddr << 16) | regAddr.
 * param data The data written to PHY.
 */
void ENET_StartExtC45SMIWriteData(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t mmfr = 0;

    /* Parse the address from the input register. */
    uint16_t devAddr = (uint16_t)((phyReg >> 16U) & 0x1FU);

    /* Build MII write command. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiWriteFrame_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2) | ENET_MMFR_DATA(data);
    base->MMFR = mmfr;
}

/*!
 * brief Starts the extended IEEE802.3 Clause 45 MDIO format SMI read data command.
 *
 * After writing MMFR register, we need to check whether the transmission is over.
 * This is an example for whole precedure of clause 45 MDIO read.
 * code
 *       uint32_t data;
 *       ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
 *       ENET_StartExtC45SMIWriteReg(base, phyAddr, phyReg);
 *       while ((ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) == 0U)
 *       {
 *       }
 *       ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
 *       ENET_StartExtC45SMIReadData(base, phyAddr, phyReg);
 *       while ((ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK) == 0U)
 *       {
 *       }
 *       ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
 *       data = ENET_ReadSMIData(base);
 * endcode
 * param base  ENET peripheral base address.
 * param phyAddr The PHY address.
 * param phyReg The PHY register. For MDIO IEEE802.3 Clause 45,
 *        the phyReg is a 21-bits combination of the devaddr (5 bits device address)
 *        and the regAddr (16 bits phy register): phyReg = (devaddr << 16) | regAddr.
 */
void ENET_StartExtC45SMIReadData(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg)
{
    uint32_t mmfr = 0;

    /* Parse the address from the input register. */
    uint16_t devAddr = (uint16_t)((phyReg >> 16U) & 0x1FU);

    /* Build MII read command. */
    mmfr = ENET_MMFR_ST(0) | ENET_MMFR_OP(kENET_MiiReadFrame_C45) | ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(devAddr) |
           ENET_MMFR_TA(2);
    base->MMFR = mmfr;
}
#endif /* FSL_FEATURE_ENET_HAS_EXTEND_MDIO */

static uint16_t ENET_IncreaseIndex(uint16_t index, uint16_t max)
{
    assert(index < max);

    /* Increase the index. */
    index++;
    if (index >= max)
    {
        index = 0;
    }
    return index;
}

static inline bool ENET_TxDirtyRingAvailable(enet_tx_dirty_ring_t *txDirtyRing)
{
    return !txDirtyRing->isFull;
}

/*!
 * brief Gets the error statistics of a received frame for ENET specified ring.
 *
 * This API must be called after the ENET_GetRxFrameSize and before the ENET_ReadFrame().
 * If the ENET_GetRxFrameSize returns kStatus_ENET_RxFrameError,
 * the ENET_GetRxErrBeforeReadFrame can be used to get the exact error statistics.
 * This is an example.
 * code
 *       status = ENET_GetRxFrameSize(&g_handle, &length, 0);
 *       if (status == kStatus_ENET_RxFrameError)
 *       {
 *           ENET_GetRxErrBeforeReadFrame(&g_handle, &eErrStatic, 0);
 *           ENET_ReadFrame(EXAMPLE_ENET, &g_handle, NULL, 0);
 *       }
 * endcode
 * param handle The ENET handler structure pointer. This is the same handler pointer used in the ENET_Init.
 * param eErrorStatic The error statistics structure pointer.
 * param ringId The ring index, range from 0 ~ (FSL_FEATURE_ENET_INSTANCE_QUEUEn(x) - 1).
 */
void ENET_GetRxErrBeforeReadFrame(enet_handle_t *handle, enet_data_error_stats_t *eErrorStatic, uint8_t ringId)
{
    assert(handle != NULL);
    assert(eErrorStatic != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);

    uint16_t control                             = 0;
    enet_rx_bd_ring_t *rxBdRing                  = &handle->rxBdRing[ringId];
    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    volatile enet_rx_bd_struct_t *cmpBuffDescrip = curBuffDescrip;

    do
    {
        /* The last buffer descriptor of a frame. */
        if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
        {
            control = curBuffDescrip->control;
            if (0U != (control & ENET_BUFFDESCRIPTOR_RX_TRUNC_MASK))
            {
                /* The receive truncate error. */
                eErrorStatic->statsRxTruncateErr++;
            }
            if (0U != (control & ENET_BUFFDESCRIPTOR_RX_OVERRUN_MASK))
            {
                /* The receive over run error. */
                eErrorStatic->statsRxOverRunErr++;
            }
            if (0U != (control & ENET_BUFFDESCRIPTOR_RX_LENVLIOLATE_MASK))
            {
                /* The receive length violation error. */
                eErrorStatic->statsRxLenGreaterErr++;
            }
            if (0U != (control & ENET_BUFFDESCRIPTOR_RX_NOOCTET_MASK))
            {
                /* The receive alignment error. */
                eErrorStatic->statsRxAlignErr++;
            }
            if (0U != (control & ENET_BUFFDESCRIPTOR_RX_CRC_MASK))
            {
                /* The receive CRC error. */
                eErrorStatic->statsRxFcsErr++;
            }
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
            uint16_t controlExt = curBuffDescrip->controlExtend1;
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_RX_MACERR_MASK))
            {
                /* The MAC error. */
                eErrorStatic->statsRxMacErr++;
            }
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_RX_PHYERR_MASK))
            {
                /* The PHY error. */
                eErrorStatic->statsRxPhyErr++;
            }
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_RX_COLLISION_MASK))
            {
                /* The receive collision error. */
                eErrorStatic->statsRxCollisionErr++;
            }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

            break;
        }

        /* Increase the buffer descriptor, if it's the last one, increase to first one of the ring buffer. */
        if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK))
        {
            curBuffDescrip = rxBdRing->rxBdBase;
        }
        else
        {
            curBuffDescrip++;
        }

    } while (curBuffDescrip != cmpBuffDescrip);
}

/*!
 * brief Gets statistical data in transfer.
 *
 * param base  ENET peripheral base address.
 * param statistics The statistics structure pointer.
 */
void ENET_GetStatistics(ENET_Type *base, enet_transfer_stats_t *statistics)
{
    /* Rx statistics */
    statistics->statsRxFrameCount      = base->RMON_R_PACKETS;
    statistics->statsRxFrameOk         = base->IEEE_R_FRAME_OK;
    statistics->statsRxCrcErr          = base->IEEE_R_CRC;
    statistics->statsRxAlignErr        = base->IEEE_R_ALIGN;
    statistics->statsRxDropInvalidSFD  = base->IEEE_R_DROP;
    statistics->statsRxFifoOverflowErr = base->IEEE_R_MACERR;

    /* Tx statistics */
    statistics->statsTxFrameCount      = base->RMON_T_PACKETS;
    statistics->statsTxFrameOk         = base->IEEE_T_FRAME_OK;
    statistics->statsTxCrcAlignErr     = base->RMON_T_CRC_ALIGN;
    statistics->statsTxFifoUnderRunErr = base->IEEE_T_MACERR;
}

/*!
 * brief Gets the size of the read frame for specified ring.
 *
 * This function gets a received frame size from the ENET buffer descriptors.
 * note The FCS of the frame is automatically removed by MAC and the size is the length without the FCS.
 * After calling ENET_GetRxFrameSize, ENET_ReadFrame() should be called to receive frame and update the BD
 * if the result is not "kStatus_ENET_RxFrameEmpty".
 *
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * param length The length of the valid frame received.
 * param ringId The ring index or ring number.
 * retval kStatus_ENET_RxFrameEmpty No frame received. Should not call ENET_ReadFrame to read frame.
 * retval kStatus_ENET_RxFrameError Data error happens. ENET_ReadFrame should be called with NULL data
 *         and NULL length to update the receive buffers.
 * retval kStatus_Success Receive a frame Successfully then the ENET_ReadFrame
 *         should be called with the right data buffer and the captured data length input.
 */
status_t ENET_GetRxFrameSize(enet_handle_t *handle, uint32_t *length, uint8_t ringId)
{
    assert(handle != NULL);
    assert(length != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);

    /* Reset the length to zero. */
    *length = 0;

    uint16_t validLastMask                       = ENET_BUFFDESCRIPTOR_RX_LAST_MASK | ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
    enet_rx_bd_ring_t *rxBdRing                  = &handle->rxBdRing[ringId];
    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    uint16_t index                               = rxBdRing->rxGenIdx;
    bool isReturn                                = false;
    status_t result                              = kStatus_Success;

    /* Check the current buffer descriptor's empty flag. If empty means there is no frame received. */
    /* If this buffer descriptor is owned by application, return empty. Only need to check the first BD's owner if one
     * frame in mutiple BDs. */
    if (0U != (curBuffDescrip->control & (ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK | ENET_BUFFDESCRIPTOR_RX_SOFTOWNER1_MASK)))
    {
        isReturn = true;
        result   = kStatus_ENET_RxFrameEmpty;
    }
    else
    {
        do
        {
            /* Add check for abnormal case. */
            if (curBuffDescrip->length == 0U)
            {
                isReturn = true;
                result   = kStatus_ENET_RxFrameError;
                break;
            }

            /* Find the last buffer descriptor. */
            if ((curBuffDescrip->control & validLastMask) == ENET_BUFFDESCRIPTOR_RX_LAST_MASK)
            {
                isReturn = true;
                /* The last buffer descriptor in the frame check the status of the received frame. */
                if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_ERR_MASK))
                {
                    result = kStatus_ENET_RxFrameError;
                    break;
                }
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                if (0U != (curBuffDescrip->controlExtend1 & ENET_BUFFDESCRIPTOR_RX_EXT_ERR_MASK))
                {
                    result = kStatus_ENET_RxFrameError;
                    break;
                }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

                /* FCS is removed by MAC. */
                *length = curBuffDescrip->length;
                break;
            }
            /* Increase the buffer descriptor, if it is the last one, increase to first one of the ring buffer. */
            index          = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
            curBuffDescrip = rxBdRing->rxBdBase + index;
        } while (index != rxBdRing->rxGenIdx);
    }

    if (isReturn == false)
    {
        /* The frame is on processing - set to empty status to make application to receive it next time. */
        result = kStatus_ENET_RxFrameEmpty;
    }

    return result;
}

/*!
 * brief Reads a frame from the ENET device.
 * This function reads a frame (both the data and the length) from the ENET buffer descriptors.
 * User can get timestamp through ts pointer if the ts is not NULL.
 * note It doesn't store the timestamp in the receive timestamp queue.
 * The ENET_GetRxFrameSize should be used to get the size of the prepared data buffer.
 * This API uses memcpy to copy data from DMA buffer to application buffer, 4 bytes aligned data buffer
 * in 32 bits platforms provided by user may let compiler use optimization instruction to reduce time
 * consumption.
 * This is an example:
 * code
 *       uint32_t length;
 *       enet_handle_t g_handle;
 *       Comments: Get the received frame size firstly.
 *       status = ENET_GetRxFrameSize(&g_handle, &length, 0);
 *       if (length != 0)
 *       {
 *           Comments: Allocate memory here with the size of "length"
 *           uint8_t *data = memory allocate interface;
 *           if (!data)
 *           {
 *               ENET_ReadFrame(ENET, &g_handle, NULL, 0, 0, NULL);
 *               Comments: Add the console warning log.
 *           }
 *           else
 *           {
 *               status = ENET_ReadFrame(ENET, &g_handle, data, length, 0, NULL);
 *               Comments: Call stack input API to deliver the data to stack
 *           }
 *       }
 *       else if (status == kStatus_ENET_RxFrameError)
 *       {
 *           Comments: Update the received buffer when a error frame is received.
 *           ENET_ReadFrame(ENET, &g_handle, NULL, 0, 0, NULL);
 *       }
 * endcode
 * param base  ENET peripheral base address.
 * param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * param data The data buffer provided by user to store the frame which memory size should be at least "length".
 * param length The size of the data buffer which is still the length of the received frame.
 * param ringId The ring index or ring number.
 * param ts The timestamp address to store received timestamp.
 * return The execute status, successful or failure.
 */
status_t ENET_ReadFrame(
    ENET_Type *base, enet_handle_t *handle, uint8_t *data, uint32_t length, uint8_t ringId, uint32_t *ts)
{
    assert(handle != NULL);
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    uint32_t len    = 0;
    uint32_t offset = 0;
    uint16_t control;
    bool isLastBuff                              = false;
    enet_rx_bd_ring_t *rxBdRing                  = &handle->rxBdRing[ringId];
    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    uint16_t index                               = rxBdRing->rxGenIdx;
    status_t result                              = kStatus_Success;
    uint32_t address;
    uint32_t dest;

    /* For data-NULL input, only update the buffer descriptor. */
    if (data == NULL)
    {
        do
        {
            /* Update the control flag. */
            control = curBuffDescrip->control;

            /* Updates the receive buffer descriptors. */
            ENET_UpdateReadBuffers(base, handle, ringId);

            /* Find the last buffer descriptor for the frame. */
            if (0U != (control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
            {
                break;
            }
            curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
        } while (index != rxBdRing->rxGenIdx);
    }
    else
    {
        while (!isLastBuff)
        {
/* A frame on one buffer or several receive buffers are both considered. */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
            address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
            if (handle->rxMaintainEnable[ringId])
            {
                /* Add the cache invalidate maintain. */
                DCACHE_InvalidateByRange(address, handle->rxBuffSizeAlign[ringId]);
            }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */

            dest = (uint32_t)data + offset;
            /* The last buffer descriptor of a frame. */
            if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
            {
                /* This is a valid frame. */
                isLastBuff = true;
                if (length == curBuffDescrip->length)
                {
                    /* Copy the frame to user's buffer without FCS. */
                    len = curBuffDescrip->length - offset;
                    (void)memcpy((void *)(uint32_t *)dest, (void *)(uint32_t *)address, len);
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                    /* Get the timestamp if the ts isn't NULL. */
                    if (ts != NULL)
                    {
                        *ts = curBuffDescrip->timestamp;
                    }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

                    /* Updates the receive buffer descriptors. */
                    ENET_UpdateReadBuffers(base, handle, ringId);
                    break;
                }
                else
                {
                    /* Updates the receive buffer descriptors. */
                    ENET_UpdateReadBuffers(base, handle, ringId);
                }
            }
            else
            {
                /* Store a frame on several buffer descriptors. */
                isLastBuff = false;
                /* Length check. */
                if (offset >= length)
                {
                    result = kStatus_ENET_RxFrameFail;
                    break;
                }
                (void)memcpy((void *)(uint32_t *)dest, (void *)(uint32_t *)address, handle->rxBuffSizeAlign[ringId]);
                offset += handle->rxBuffSizeAlign[ringId];

                /* Updates the receive buffer descriptors. */
                ENET_UpdateReadBuffers(base, handle, ringId);
            }

            /* Get the current buffer descriptor. */
            curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
        }
    }

    return result;
}

static void ENET_UpdateReadBuffers(ENET_Type *base, enet_handle_t *handle, uint8_t ringId)
{
    assert(handle != NULL);
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    enet_rx_bd_ring_t *rxBdRing                  = &handle->rxBdRing[ringId];
    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;

    /* Clears status. */
    curBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
    /* Sets the receive buffer descriptor with the empty flag. */
    curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;

    /* Increase current buffer descriptor to the next one. */
    rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

    ENET_ActiveReadRing(base, ringId);
}

/*!
 * brief Transmits an ENET frame for specified ring.
 * note The CRC is automatically appended to the data. Input the data to send without the CRC.
 * This API uses memcpy to copy data from DMA buffer to application buffer, 4 bytes aligned data buffer
 * in 32 bits platforms provided by user may let compiler use optimization instruction to reduce time
 * consumption.
 *
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param data The data buffer provided by user to send.
 * param length The length of the data to send.
 * param ringId The ring index or ring number.
 * param tsFlag Timestamp enable flag.
 * param context Used by user to handle some events after transmit over.
 * retval kStatus_Success  Send frame succeed.
 * retval kStatus_ENET_TxFrameBusy  Transmit buffer descriptor is busy under transmission.
 *        The transmit busy happens when the data send rate is over the MAC capacity.
 *        The waiting mechanism is recommended to be added after each call return with
 *        kStatus_ENET_TxFrameBusy.
 */
status_t ENET_SendFrame(ENET_Type *base,
                        enet_handle_t *handle,
                        const uint8_t *data,
                        uint32_t length,
                        uint8_t ringId,
                        bool tsFlag,
                        void *context)
{
    assert(handle != NULL);
    assert(data != NULL);
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    volatile enet_tx_bd_struct_t *curBuffDescrip;
    enet_tx_bd_ring_t *txBdRing       = &handle->txBdRing[ringId];
    enet_tx_dirty_ring_t *txDirtyRing = &handle->txDirtyRing[ringId];
    enet_frame_info_t *txDirty        = NULL;
    uint32_t len                      = 0;
    uint32_t sizeleft                 = 0;
    uint32_t address;
    status_t result = kStatus_Success;
    uint32_t src;
    uint32_t configVal;
    bool isReturn = false;
    uint32_t primask;

    /* Check the frame length. */
    if (length > ENET_FRAME_TX_LEN_LIMITATION(base))
    {
        result = kStatus_ENET_TxFrameOverLen;
    }
    else
    {
        /* Check if the transmit buffer is ready. */
        curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;
        if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK))
        {
            result = kStatus_ENET_TxFrameBusy;
        }
        /* Check txDirtyRing if need frameinfo in tx interrupt callback. */
        else if ((handle->txReclaimEnable[ringId]) && !ENET_TxDirtyRingAvailable(txDirtyRing))
        {
            result = kStatus_ENET_TxFrameBusy;
        }
        else
        {
            /* One transmit buffer is enough for one frame. */
            if (handle->txBuffSizeAlign[ringId] >= length)
            {
                /* Copy data to the buffer for uDMA transfer. */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
                address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                (void)memcpy((void *)(uint32_t *)address, (const void *)(uint32_t *)(uint32_t)data, length);
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
                if (handle->txMaintainEnable[ringId])
                {
                    DCACHE_CleanByRange(address, length);
                }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
                /* Set data length. */
                curBuffDescrip->length = (uint16_t)length;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                /* For enable the timestamp. */
                if (tsFlag)
                {
                    curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
                }
                else
                {
                    curBuffDescrip->controlExtend1 &= (uint16_t)(~ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK);
                }

#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
                curBuffDescrip->control |= (ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK);

                /* Increase the buffer descriptor address. */
                txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

                /* Add context to frame info ring */
                if (handle->txReclaimEnable[ringId])
                {
                    txDirty               = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                    txDirty->context      = context;
                    txDirtyRing->txGenIdx = ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                    if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                    {
                        txDirtyRing->isFull = true;
                    }
                    primask = DisableGlobalIRQ();
                    txBdRing->txDescUsed++;
                    EnableGlobalIRQ(primask);
                }

                /* Active the transmit buffer descriptor. */
                ENET_ActiveSendRing(base, ringId);
            }
            else
            {
                /* One frame requires more than one transmit buffers. */
                do
                {
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                    /* For enable the timestamp. */
                    if (tsFlag)
                    {
                        curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
                    }
                    else
                    {
                        curBuffDescrip->controlExtend1 &= (uint16_t)(~ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK);
                    }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

                    /* Update the size left to be transmit. */
                    sizeleft = length - len;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
                    address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                    src = (uint32_t)data + len;

                    /* Increase the current software index of BD */
                    txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

                    if (sizeleft > handle->txBuffSizeAlign[ringId])
                    {
                        /* Data copy. */
                        (void)memcpy((void *)(uint32_t *)address, (void *)(uint32_t *)src,
                                     handle->txBuffSizeAlign[ringId]);
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
                        if (handle->txMaintainEnable[ringId])
                        {
                            /* Add the cache clean maintain. */
                            DCACHE_CleanByRange(address, handle->txBuffSizeAlign[ringId]);
                        }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
                        /* Data length update. */
                        curBuffDescrip->length = handle->txBuffSizeAlign[ringId];
                        len += handle->txBuffSizeAlign[ringId];
                        /* Sets the control flag. */
                        configVal = (uint32_t)curBuffDescrip->control;
                        configVal &= ~ENET_BUFFDESCRIPTOR_TX_LAST_MASK;
                        configVal |= ENET_BUFFDESCRIPTOR_TX_READY_MASK;
                        curBuffDescrip->control = (uint16_t)configVal;

                        if (handle->txReclaimEnable[ringId])
                        {
                            primask = DisableGlobalIRQ();
                            txBdRing->txDescUsed++;
                            EnableGlobalIRQ(primask);
                        }

                        /* Active the transmit buffer descriptor*/
                        ENET_ActiveSendRing(base, ringId);
                    }
                    else
                    {
                        (void)memcpy((void *)(uint32_t *)address, (void *)(uint32_t *)src, sizeleft);
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
                        if (handle->txMaintainEnable[ringId])
                        {
                            /* Add the cache clean maintain. */
                            DCACHE_CleanByRange(address, sizeleft);
                        }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
                        curBuffDescrip->length = (uint16_t)sizeleft;
                        /* Set Last buffer wrap flag. */
                        curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK;

                        if (handle->txReclaimEnable[ringId])
                        {
                            /* Add context to frame info ring */
                            txDirty               = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                            txDirty->context      = context;
                            txDirtyRing->txGenIdx = ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                            if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                            {
                                txDirtyRing->isFull = true;
                            }
                            primask = DisableGlobalIRQ();
                            txBdRing->txDescUsed++;
                            EnableGlobalIRQ(primask);
                        }

                        /* Active the transmit buffer descriptor. */
                        ENET_ActiveSendRing(base, ringId);
                        isReturn = true;
                        break;
                    }
                    /* Update the buffer descriptor address. */
                    curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;
                } while (0U == (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK));

                if (isReturn == false)
                {
                    result = kStatus_ENET_TxFrameBusy;
                }
            }
        }
    }
    return result;
}

/*!
 * brief Enable or disable tx descriptors reclaim mechanism.
 * note This function must be called when no pending send frame action.
 * Set enable if you want to reclaim context or timestamp in interrupt.
 *
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param isEnable Enable or disable flag.
 * param ringId The ring index or ring number.
 * retval kStatus_Success  Succeed to enable/disable Tx reclaim.
 * retval kStatus_Fail  Fail to enable/disable Tx reclaim.
 */
status_t ENET_SetTxReclaim(enet_handle_t *handle, bool isEnable, uint8_t ringId)
{
    assert(handle != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);

    enet_tx_bd_ring_t *txBdRing       = &handle->txBdRing[ringId];
    enet_tx_dirty_ring_t *txDirtyRing = &handle->txDirtyRing[ringId];

    status_t result = kStatus_Success;

    /* If tx dirty ring is empty, can set this flag and reset txConsumIdx */
    if ((txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx) && ENET_TxDirtyRingAvailable(txDirtyRing))
    {
        if (isEnable)
        {
            handle->txReclaimEnable[ringId] = true;
            txBdRing->txConsumIdx           = txBdRing->txGenIdx;
        }
        else
        {
            handle->txReclaimEnable[ringId] = false;
        }
    }
    else
    {
        result = kStatus_Fail;
    }
    return result;
}

/*!
 * brief Reclaim tx descriptors.
 * This function is used to update the tx descriptor status and
 * store the tx timestamp when the 1588 feature is enabled.
 * This is called by the transmit interupt IRQ handler after the
 * complete of a frame transmission.
 *
 * param base   ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param ringId The ring index or ring number.
 */
void ENET_ReclaimTxDescriptor(ENET_Type *base, enet_handle_t *handle, uint8_t ringId)
{
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    enet_tx_bd_ring_t *txBdRing                  = &handle->txBdRing[ringId];
    volatile enet_tx_bd_struct_t *curBuffDescrip = txBdRing->txBdBase + txBdRing->txConsumIdx;
    enet_tx_dirty_ring_t *txDirtyRing            = &handle->txDirtyRing[ringId];
    enet_frame_info_t *txDirty                   = NULL;
    uint32_t primask;

    /* Need to update the first index for transmit buffer free. */
    while ((0U == (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK)) && (txBdRing->txDescUsed > 0U))
    {
        if ((curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_LAST_MASK) != 0U)
        {
            txDirty                  = txDirtyRing->txDirtyBase + txDirtyRing->txConsumIdx;
            txDirtyRing->txConsumIdx = ENET_IncreaseIndex(txDirtyRing->txConsumIdx, txDirtyRing->txRingLen);
            txDirtyRing->isFull      = false;

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
            txDirty->isTsAvail = false;
            if ((curBuffDescrip->controlExtend1 & ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK) != 0U)
            {
                enet_ptp_time_t *ts = &txDirty->timeStamp;
                /* Get transmit time stamp second. */
                txDirty->isTsAvail = true;
                ts->second         = handle->msTimerSecond;
                ts->nanosecond     = curBuffDescrip->timestamp;
            }
#endif
            /* For tx buffer free or requeue for last descriptor.
             * The tx interrupt callback should free/requeue the tx buffer. */
            if (handle->callback != NULL)
            {
#if FSL_FEATURE_ENET_QUEUE > 1
                handle->callback(base, handle, ringId, kENET_TxEvent, txDirty, handle->userData);
#else
                handle->callback(base, handle, kENET_TxEvent, txDirty, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
            }
        }

        primask = DisableGlobalIRQ();
        txBdRing->txDescUsed--;
        EnableGlobalIRQ(primask);

        /* Update the index. */
        txBdRing->txConsumIdx = ENET_IncreaseIndex(txBdRing->txConsumIdx, txBdRing->txRingLen);
        curBuffDescrip        = txBdRing->txBdBase + txBdRing->txConsumIdx;
    }
}

/*!
 * deprecated Do not use this function. It has been superseded by @ref ENET_GetRxFrame.
 */
status_t ENET_GetRxBuffer(ENET_Type *base,
                          enet_handle_t *handle,
                          void **buffer,
                          uint32_t *length,
                          uint8_t ringId,
                          bool *isLastBuff,
                          uint32_t *ts)
{
    assert(handle != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);
    assert(handle->rxBdRing[ringId].rxBdBase != NULL);
    assert(handle->rxBuffAlloc == NULL);

    enet_rx_bd_ring_t *rxBdRing                  = &handle->rxBdRing[ringId];
    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    uint32_t address;

    /* Check if current rx BD is under usage by certain application */
    /* Buffer owner flag, 1: owned by application, 0: owned by driver */
    if ((curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_SOFTOWNER1_MASK) == 0U)
    {
        curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_SOFTOWNER1_MASK;
    }
    else
    {
        return kStatus_ENET_RxFrameFail;
    }

/* A frame on one buffer or several receive buffers are both considered. */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
    address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
    if (handle->rxMaintainEnable[ringId])
    {
        /* Add the cache invalidate maintain. */
        DCACHE_InvalidateByRange(address, handle->rxBuffSizeAlign[ringId]);
    }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */

    *buffer = (void *)(uint32_t *)address;
    *length = curBuffDescrip->length;

    /* The last buffer descriptor of a frame. */
    if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
    {
        /* This is a valid frame. */
        *isLastBuff = true;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
        if (ts != NULL)
        {
            *ts = curBuffDescrip->timestamp;
        }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
    }
    else
    {
        *isLastBuff = false;
    }

    /* Increase current buffer descriptor to the next one. */
    rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);

    return kStatus_Success;
}

/*!
 * deprecated Do not use this function. It has been superseded by @ref ENET_GetRxFrame.
 */
void ENET_ReleaseRxBuffer(ENET_Type *base, enet_handle_t *handle, void *buffer, uint8_t ringId)
{
    assert(handle != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);

    enet_rx_bd_ring_t *rxBdRing           = &handle->rxBdRing[ringId];
    enet_rx_bd_struct_t *ownBuffDescrip   = (enet_rx_bd_struct_t *)(uint32_t)rxBdRing->rxBdBase;
    enet_rx_bd_struct_t *blockBuffDescrip = (enet_rx_bd_struct_t *)(uint32_t)rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    enet_rx_bd_struct_t tempBuffDescrip;
    uint16_t index   = rxBdRing->rxGenIdx;
    bool isReleaseBd = false;

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    buffer = (void *)(uint32_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)buffer, kMEMORY_Local2DMA);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

    do
    {
        /* Find the BD for releasing, do nothing if it's not owned by application. */
        if (buffer == ownBuffDescrip->buffer)
        {
            if (0U != (ownBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_SOFTOWNER1_MASK))
            {
                isReleaseBd = true;
                break;
            }
        }

        if (0U != (ownBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK))
        {
            break;
        }
        ownBuffDescrip++;
    } while (true);

    if (isReleaseBd)
    {
        /* Find the first BD owned by application after rxBdCurrent, isReleaseBd is true so there's at least one BD is
         * owned by application */
        do
        {
            if (0U != (blockBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_SOFTOWNER1_MASK))
            {
                break;
            }
            if (0U != (blockBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK))
            {
                blockBuffDescrip = (enet_rx_bd_struct_t *)(uint32_t)rxBdRing->rxBdBase;
            }
            else
            {
                blockBuffDescrip++;
            }
            index = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
        } while (index != rxBdRing->rxGenIdx);

        /* If the BD ready for releasing isn't the first BD owned by application after rxBdCurrent then exchange the two
         * BDs */
        if (blockBuffDescrip != ownBuffDescrip)
        {
            /* Exchange buffer descriptor content */
            tempBuffDescrip   = *ownBuffDescrip;
            *ownBuffDescrip   = *blockBuffDescrip;
            *blockBuffDescrip = tempBuffDescrip;

            /* Maintain the wrap flag */
            if (0U != (ownBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK))
            {
                ownBuffDescrip->control &= (uint16_t)(~ENET_BUFFDESCRIPTOR_RX_WRAP_MASK);
                blockBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            }
            else if (0U != (blockBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_WRAP_MASK))
            {
                blockBuffDescrip->control &= (uint16_t)(~ENET_BUFFDESCRIPTOR_RX_WRAP_MASK);
                ownBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            }
            else
            {
                /* Intentional empty */
            }

            /* Clears status including the owner flag. */
            blockBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            /* Sets the receive buffer descriptor with the empty flag. */
            blockBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
        }
        else
        {
            /* Clears status including the owner flag. */
            ownBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            /* Sets the receive buffer descriptor with the empty flag. */
            ownBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;
        }

        ENET_ActiveReadRing(base, ringId);
    }
}

static inline status_t ENET_GetRxFrameErr(enet_rx_bd_struct_t *rxDesc, enet_rx_frame_error_t *rxFrameError)
{
    assert(rxDesc != NULL);
    assert(rxFrameError != NULL);

    status_t result  = kStatus_Success;
    uint16_t control = rxDesc->control;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    uint16_t controlExtend1 = rxDesc->controlExtend1;
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

    union _frame_error
    {
        uint32_t data;
        enet_rx_frame_error_t frameError;
    };
    union _frame_error error;

    (void)memset((void *)&error.frameError, 0, sizeof(enet_rx_frame_error_t));

    /* The last buffer descriptor in the frame check the status of the received frame. */
    if (0U != (control & ENET_BUFFDESCRIPTOR_RX_ERR_MASK))
    {
        result = kStatus_ENET_RxFrameError;
    }
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    if (0U != (controlExtend1 & ENET_BUFFDESCRIPTOR_RX_EXT_ERR_MASK))
    {
        result = kStatus_ENET_RxFrameError;
    }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

    if (result != kStatus_Success)
    {
        error.data = control;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
        error.data |= ((uint32_t)controlExtend1 << 16U);
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
    }

    *rxFrameError = error.frameError;

    return result;
}

/*!
 * brief Receives one frame in specified BD ring with zero copy.
 *
 * This function will use the user-defined allocate and free callback. Every time application gets one frame through
 * this function, driver will allocate new buffers for the BDs whose buffers have been taken by application.
 * note This function will drop current frame and update related BDs as available for DMA if new buffers allocating
 * fails. Application must provide a memory pool including at least BD number + 1 buffers to make this function work
 * normally. If user calls this function in Rx interrupt handler, be careful that this function makes Rx BD ready with
 * allocating new buffer(normal) or updating current BD(out of memory). If there's always new Rx frame input, Rx
 * interrupt will be triggered forever. Application need to disable Rx interrupt according to specific design in this
 * case.
 *
 * param base   ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param rxFrame The received frame information structure provided by user.
 * param ringId The ring index or ring number.
 * retval kStatus_Success  Succeed to get one frame and allocate new memory for Rx buffer.
 * retval kStatus_ENET_RxFrameEmpty  There's no Rx frame in the BD.
 * retval kStatus_ENET_RxFrameError  There's issue in this receiving.
 * retval kStatus_ENET_RxFrameDrop  There's no new buffer memory for BD, drop this frame.
 */
status_t ENET_GetRxFrame(ENET_Type *base, enet_handle_t *handle, enet_rx_frame_struct_t *rxFrame, uint8_t ringId)
{
    assert(handle != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);
    assert(handle->rxBdRing[ringId].rxBdBase != NULL);
    assert(rxFrame != NULL);
    assert(rxFrame->rxBuffArray != NULL);

    status_t result                              = kStatus_Success;
    enet_rx_bd_ring_t *rxBdRing                  = &handle->rxBdRing[ringId];
    volatile enet_rx_bd_struct_t *curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    void *newBuff                                = NULL;
    bool isLastBuff                              = false;
    uint16_t buffLen                             = 0;
    enet_buffer_struct_t *rxBuffer;
    uint16_t index;
    uint32_t address;
    void *buffer;

    /* Check the current buffer descriptor's empty flag. If empty means there is no frame received. */
    if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK))
    {
        result = kStatus_ENET_RxFrameEmpty;
    }
    else
    {
        index = rxBdRing->rxGenIdx;
        do
        {
            /* Find the last buffer descriptor. */
            if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
            {
                /* The last buffer descriptor stores the status of rhis received frame. */
                result = ENET_GetRxFrameErr((enet_rx_bd_struct_t *)(uint32_t)curBuffDescrip, &rxFrame->rxFrameError);
                break;
            }

            /* Can't find the last BD flag, no valid frame. */
            index          = ENET_IncreaseIndex(index, rxBdRing->rxRingLen);
            curBuffDescrip = rxBdRing->rxBdBase + index;
            if (index == rxBdRing->rxGenIdx)
            {
                result = kStatus_ENET_RxFrameEmpty;
                break;
            }
        } while (0U == (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK));
    }

    /* Drop the error frame. */
    if (result == kStatus_ENET_RxFrameError)
    {
        curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
        do
        {
            /* The last buffer descriptor of a frame. */
            if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
            {
                isLastBuff = true;
            }

            /* Clears status including the owner flag. */
            curBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            /* Sets the receive buffer descriptor with the empty flag. */
            curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;

            /* Increase current buffer descriptor to the next one. */
            rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
            curBuffDescrip     = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
        } while (!isLastBuff);

        ENET_ActiveReadRing(base, ringId);

        return result;
    }
    else if (result != kStatus_Success)
    {
        return result;
    }
    else
    {
        /* Intentional empty */
    }

    /* Get the valid frame */
    curBuffDescrip = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
    index          = 0;
    do
    {
        newBuff = handle->rxBuffAlloc(base, handle->userData, ringId);
        if (newBuff != NULL)
        {
            rxBuffer = &rxFrame->rxBuffArray[index];

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
            address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
            if (handle->rxMaintainEnable[ringId])
            {
                DCACHE_InvalidateByRange(address, handle->rxBuffSizeAlign[ringId]);
            }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */

            rxBuffer->buffer = (void *)(uint32_t *)address;

            /* The last buffer descriptor of a frame. */
            if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
            {
                /* This is a valid frame. */
                isLastBuff       = true;
                rxFrame->totLen  = curBuffDescrip->length;
                rxBuffer->length = curBuffDescrip->length - buffLen;

                rxFrame->rxAttribute.promiscuous = false;
                if (0U != (base->RCR & ENET_RCR_PROM_MASK))
                {
                    if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_MISS_MASK))
                    {
                        rxFrame->rxAttribute.promiscuous = true;
                    }
                }
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                rxFrame->rxAttribute.timestamp = curBuffDescrip->timestamp;
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
            }
            else
            {
                rxBuffer->length = curBuffDescrip->length;
                buffLen += rxBuffer->length;
            }

            /* Give new buffer from application to BD */

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            buffer =
                (void *)(uint32_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)(uint32_t *)newBuff, kMEMORY_Local2DMA);
#else
            buffer  = newBuff;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
            if (handle->rxMaintainEnable[ringId])
            {
                DCACHE_InvalidateByRange((uint32_t)(uint32_t *)buffer, handle->rxBuffSizeAlign[ringId]);
            }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */

            curBuffDescrip->buffer = buffer;

            /* Clears status including the owner flag. */
            curBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
            /* Sets the receive buffer descriptor with the empty flag. */
            curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;

            /* Increase Rx array index and the buffer descriptor address. */
            index++;
            rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
            curBuffDescrip     = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
        }
        else
        {
            /* Drop frame if there's no new buffer memory */

            /* Free the incomplete frame buffers. */
            while (index-- != 0U)
            {
                handle->rxBuffFree(base, &rxFrame->rxBuffArray[index].buffer, handle->userData, ringId);
            }

            /* Update left buffers as ready for next coming frame */
            do
            {
                /* The last buffer descriptor of a frame. */
                if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_RX_LAST_MASK))
                {
                    isLastBuff = true;
                }

                /* Clears status including the owner flag. */
                curBuffDescrip->control &= ENET_BUFFDESCRIPTOR_RX_WRAP_MASK;
                /* Sets the receive buffer descriptor with the empty flag. */
                curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_RX_EMPTY_MASK;

                /* Increase current buffer descriptor to the next one. */
                rxBdRing->rxGenIdx = ENET_IncreaseIndex(rxBdRing->rxGenIdx, rxBdRing->rxRingLen);
                curBuffDescrip     = rxBdRing->rxBdBase + rxBdRing->rxGenIdx;
            } while (!isLastBuff);

            result = kStatus_ENET_RxFrameDrop;
            break;
        }
    } while (!isLastBuff);

    ENET_ActiveReadRing(base, ringId);

    return result;
}

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
static inline void ENET_PrepareTxDesc(volatile enet_tx_bd_struct_t *txDesc, enet_tx_config_struct_t *txConfig)
{
    uint16_t controlExtend1 = 0U;

    /* For enable the timestamp. */
    if (txConfig->intEnable)
    {
        controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_INTERRUPT_MASK;
    }
    if (txConfig->tsEnable)
    {
        controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
    }
    if (txConfig->autoProtocolChecksum)
    {
        controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_PROTOCHECKSUM_MASK;
    }
    if (txConfig->autoIPChecksum)
    {
        controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_IPCHECKSUM_MASK;
    }
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
    if (txConfig->tltEnable)
    {
        controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_USETXLAUNCHTIME_MASK;
        txDesc->txLaunchTimeLow |= txConfig->tltLow;
        txDesc->txLaunchTimeHigh |= txConfig->tltHigh;
    }
    controlExtend1 |= (uint16_t)ENET_BD_FTYPE(txConfig->AVBFrameType);
#endif /* FSL_FEATURE_ENET_HAS_AVB */

    txDesc->controlExtend1 = controlExtend1;
}
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

/*!
 * brief Sends one frame in specified BD ring with zero copy.
 *
 * This function supports scattered buffer transmit, user needs to provide the buffer array.
 * note Tx reclaim should be enabled to ensure the Tx buffer ownership can be given back to
 * application after Tx is over.
 *
 * param base   ENET peripheral base address.
 * param handle The ENET handler pointer. This is the same handler pointer used in the ENET_Init.
 * param txFrame The Tx frame structure.
 * param ringId The ring index or ring number.
 * retval kStatus_Success  Succeed to send one frame.
 * retval kStatus_ENET_TxFrameBusy  The BD is not ready for Tx or the reclaim operation still not finishs.
 * retval kStatus_ENET_TxFrameOverLen  The Tx frame length is over max ethernet frame length.
 */
status_t ENET_StartTxFrame(ENET_Type *base, enet_handle_t *handle, enet_tx_frame_struct_t *txFrame, uint8_t ringId)
{
    assert(handle != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);
    assert(txFrame->txBuffArray != NULL);
    assert(txFrame->txBuffNum != 0U);
    assert(handle->txReclaimEnable[ringId]);

    volatile enet_tx_bd_struct_t *curBuffDescrip;
    enet_tx_bd_ring_t *txBdRing       = &handle->txBdRing[ringId];
    enet_tx_dirty_ring_t *txDirtyRing = &handle->txDirtyRing[ringId];
    status_t result                   = kStatus_Success;
    enet_buffer_struct_t *txBuff      = txFrame->txBuffArray;
    uint32_t txBuffNum                = txFrame->txBuffNum;
    enet_frame_info_t *txDirty        = NULL;
    uint32_t frameLen                 = 0;
    uint32_t idleDescNum              = 0;
    uint16_t index                    = 0;
    uint32_t configVal;
    uint32_t primask;
    void *buffer;

    /* Calculate frame length and Tx data buffer number. */
    do
    {
        frameLen += txBuff->length;
        txBuff++;
    } while (--txBuffNum != 0U);
    txBuffNum = txFrame->txBuffNum;

    /* Check whether the available BD number is enough for Tx data buffer. */
    curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;
    index          = txBdRing->txGenIdx;
    do
    {
        if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK))
        {
            break;
        }

        /* Idle BD number is enough */
        if (++idleDescNum >= txBuffNum)
        {
            break;
        }
        index          = ENET_IncreaseIndex(index, txBdRing->txRingLen);
        curBuffDescrip = txBdRing->txBdBase + index;
    } while (index != txBdRing->txGenIdx);

    /* Check the frame length. */
    if (frameLen > ENET_FRAME_TX_LEN_LIMITATION(base))
    {
        result = kStatus_ENET_TxFrameOverLen;
    }
    /* Return busy if idle BD is not enough. */
    else if (txBuffNum > idleDescNum)
    {
        result = kStatus_ENET_TxFrameBusy;
    }
    /* Check txDirtyRing if need frameinfo in tx interrupt callback. */
    else if (!ENET_TxDirtyRingAvailable(txDirtyRing))
    {
        result = kStatus_ENET_TxFrameBusy;
    }
    else
    {
        txBuff = txFrame->txBuffArray;
        do
        {
            assert(txBuff->buffer != NULL);

#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
            if (handle->txMaintainEnable[ringId])
            {
                DCACHE_CleanByRange((uint32_t)(uint32_t *)txBuff->buffer, txBuff->length);
            }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            /* Map loacl memory address to DMA for special platform. */
            buffer = (uint8_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)txBuff->buffer, kMEMORY_Local2DMA);
#else
            buffer  = txBuff->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

            /* Set data buffer and length. */
            curBuffDescrip         = txBdRing->txBdBase + txBdRing->txGenIdx;
            curBuffDescrip->buffer = (uint8_t *)(uint32_t *)buffer;
            curBuffDescrip->length = txBuff->length;

            /* Increase txBuffer array address and the buffer descriptor address. */
            txBuff++;
            txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
            ENET_PrepareTxDesc(curBuffDescrip, &txFrame->txConfig);
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

            /* Linked buffers */
            if (--txBuffNum != 0U)
            {
                /* Set BD ready flag and clean last BD flag. */
                configVal = (uint32_t)curBuffDescrip->control;
                configVal &= ~ENET_BUFFDESCRIPTOR_TX_LAST_MASK;
                configVal |= ENET_BUFFDESCRIPTOR_TX_READY_MASK;
                curBuffDescrip->control = (uint16_t)configVal;

                primask = DisableGlobalIRQ();
                txBdRing->txDescUsed++;
                EnableGlobalIRQ(primask);
            }
            else
            {
                curBuffDescrip->control |= (ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK);

                /* Add context to frame info ring */
                txDirty               = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                txDirty->context      = txFrame->context;
                txDirtyRing->txGenIdx = ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                {
                    txDirtyRing->isFull = true;
                }
                primask = DisableGlobalIRQ();
                txBdRing->txDescUsed++;
                EnableGlobalIRQ(primask);
            }
            /* Active Tx BD everytime to speed up transfer */
            ENET_ActiveSendRing(base, ringId);
        } while (txBuffNum != 0U);
    }
    return result;
}

/*!
 * deprecated Do not use this function. It has been superseded by @ref ENET_StartTxFrame.
 */
status_t ENET_SendFrameZeroCopy(ENET_Type *base,
                                enet_handle_t *handle,
                                const uint8_t *data,
                                uint32_t length,
                                uint8_t ringId,
                                bool tsFlag,
                                void *context)
{
    assert(handle != NULL);
    assert(data != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);

    volatile enet_tx_bd_struct_t *curBuffDescrip;
    enet_tx_bd_ring_t *txBdRing       = &handle->txBdRing[ringId];
    enet_tx_dirty_ring_t *txDirtyRing = &handle->txDirtyRing[ringId];
    enet_frame_info_t *txDirty        = NULL;
    uint32_t len                      = 0;
    uint32_t sizeleft                 = 0;
    status_t result                   = kStatus_Success;
    uint8_t *data_temp;
    uint32_t configVal;
    bool isReturn = false;
    uint32_t primask;

    /* Check the frame length. */
    if (length > ENET_FRAME_TX_LEN_LIMITATION(base))
    {
        result = kStatus_ENET_TxFrameOverLen;
    }
    else
    {
        /* Check if the transmit buffer is ready. */
        curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;
        if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK))
        {
            result = kStatus_ENET_TxFrameBusy;
        }
        /* Check txDirtyRing if need frameinfo in tx interrupt callback. */
        else if (handle->txReclaimEnable[ringId] && !ENET_TxDirtyRingAvailable(txDirtyRing))
        {
            result = kStatus_ENET_TxFrameBusy;
        }
        else
        {
            /* One transmit buffer is enough for one frame. */
            if (handle->txBuffSizeAlign[ringId] >= length)
            {
                /* Copy data to the buffer for uDMA transfer. */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                data = (uint8_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)data, kMEMORY_Local2DMA);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                curBuffDescrip->buffer = (uint8_t *)(uint32_t)data;
                /* Set data length. */
                curBuffDescrip->length = (uint16_t)length;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                /* For enable the timestamp. */
                if (tsFlag)
                {
                    curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
                }
                else
                {
                    curBuffDescrip->controlExtend1 &= (uint16_t)(~ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK);
                }

#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
                curBuffDescrip->control |= (ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK);

                /* Increase the buffer descriptor address. */
                txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

                /* Add context to frame info ring */
                if (handle->txReclaimEnable[ringId])
                {
                    txDirty               = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                    txDirty->context      = context;
                    txDirtyRing->txGenIdx = ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                    if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                    {
                        txDirtyRing->isFull = true;
                    }
                    primask = DisableGlobalIRQ();
                    txBdRing->txDescUsed++;
                    EnableGlobalIRQ(primask);
                }

                /* Active the transmit buffer descriptor. */
                ENET_ActiveSendRing(base, ringId);
            }
            else
            {
                /* One frame requires more than one transmit buffers. */
                do
                {
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                    /* For enable the timestamp. */
                    if (tsFlag)
                    {
                        curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
                    }
                    else
                    {
                        curBuffDescrip->controlExtend1 &= (uint16_t)(~ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK);
                    }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

                    /* Update the size left to be transmit. */
                    sizeleft = length - len;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    data = (uint8_t *)MEMORY_ConvertMemoryMapAddress((uint32_t)data, kMEMORY_Local2DMA);
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                    data_temp = (uint8_t *)(uint32_t)data + len;

                    /* Increase the current software index of BD */
                    txBdRing->txGenIdx = ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

                    if (sizeleft > handle->txBuffSizeAlign[ringId])
                    {
                        /* Set buffer. */
                        curBuffDescrip->buffer = data_temp;
                        /* Data length update. */
                        curBuffDescrip->length = handle->txBuffSizeAlign[ringId];
                        len += handle->txBuffSizeAlign[ringId];
                        /* Sets the control flag. */
                        configVal = (uint32_t)curBuffDescrip->control;
                        configVal &= ~ENET_BUFFDESCRIPTOR_TX_LAST_MASK;
                        configVal |= ENET_BUFFDESCRIPTOR_TX_READY_MASK;
                        curBuffDescrip->control = (uint16_t)configVal;

                        if (handle->txReclaimEnable[ringId])
                        {
                            primask = DisableGlobalIRQ();
                            txBdRing->txDescUsed++;
                            EnableGlobalIRQ(primask);
                        }

                        /* Active the transmit buffer descriptor*/
                        ENET_ActiveSendRing(base, ringId);
                    }
                    else
                    {
                        curBuffDescrip->buffer = data_temp;
                        curBuffDescrip->length = (uint16_t)sizeleft;
                        /* Set Last buffer wrap flag. */
                        curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK;

                        if (handle->txReclaimEnable[ringId])
                        {
                            /* Add context to frame info ring */
                            txDirty               = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                            txDirty->context      = context;
                            txDirtyRing->txGenIdx = ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                            if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                            {
                                txDirtyRing->isFull = true;
                            }
                            primask = DisableGlobalIRQ();
                            txBdRing->txDescUsed++;
                            EnableGlobalIRQ(primask);
                        }

                        /* Active the transmit buffer descriptor. */
                        ENET_ActiveSendRing(base, ringId);
                        isReturn = true;
                        break;
                    }
                    /* Update buffer descriptor address. */
                    curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;

                } while (0U == (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK));

                if (isReturn == false)
                {
                    result = kStatus_ENET_TxFrameBusy;
                }
            }
        }
    }
    return result;
}

/*!
 * brief Adds the ENET device to a multicast group.
 *
 * param base    ENET peripheral base address.
 * param address The six-byte multicast group address which is provided by application.
 */
void ENET_AddMulticastGroup(ENET_Type *base, uint8_t *address)
{
    assert(address != NULL);

    enet_handle_t *handle = s_ENETHandle[ENET_GetInstance(base)];
    uint32_t crc          = 0xFFFFFFFFU;
    uint32_t count1       = 0;
    uint32_t count2       = 0;
    uint32_t configVal    = 0;

    /* Calculates the CRC-32 polynomial on the multicast group address. */
    for (count1 = 0; count1 < ENET_FRAME_MACLEN; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < 0x08U; count2++)
        {
            if (0U != ((c ^ crc) & 1U))
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
                c >>= 1U;
            }
        }
    }

    crc = crc >> 26U;

    handle->multicastCount[crc]++;

    /* Enable a multicast group address. */
    configVal = ((uint32_t)1U << (crc & 0x1FU));

    if (0U != (crc & 0x20U))
    {
        base->GAUR |= configVal;
    }
    else
    {
        base->GALR |= configVal;
    }
}

/*!
 * brief Moves the ENET device from a multicast group.
 *
 * param base  ENET peripheral base address.
 * param address The six-byte multicast group address which is provided by application.
 */
void ENET_LeaveMulticastGroup(ENET_Type *base, uint8_t *address)
{
    assert(address != NULL);

    enet_handle_t *handle = s_ENETHandle[ENET_GetInstance(base)];
    uint32_t crc          = 0xFFFFFFFFU;
    uint32_t count1       = 0;
    uint32_t count2       = 0;
    uint32_t configVal    = 0;

    /* Calculates the CRC-32 polynomial on the multicast group address. */
    for (count1 = 0; count1 < ENET_FRAME_MACLEN; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < 0x08U; count2++)
        {
            if (0U != ((c ^ crc) & 1U))
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= 0xEDB88320U;
            }
            else
            {
                crc >>= 1U;
                c >>= 1U;
            }
        }
    }

    crc = crc >> 26U;

    handle->multicastCount[crc]--;

    /* Set the hash table if no collisions */
    if (0U == handle->multicastCount[crc])
    {
        configVal = ~((uint32_t)1U << (crc & 0x1FU));

        if (0U != (crc & 0x20U))
        {
            base->GAUR &= configVal;
        }
        else
        {
            base->GALR &= configVal;
        }
    }
}

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
/*!
 * brief Gets the ENET transmit frame statistics after the data send for specified ring.
 *
 * This interface gets the error statistics of the transmit frame.
 * Because the error information is reported by the uDMA after the data delivery, this interface
 * should be called after the data transmit API. It is recommended to call this function on
 * transmit interrupt handler. After calling the ENET_SendFrame, the
 * transmit interrupt notifies the transmit completion.
 *
 * param handle The PTP handler pointer. This is the same handler pointer used in the ENET_Init.
 * param eErrorStatic The error statistics structure pointer.
 * param ringId The ring index, range from 0 ~ (FSL_FEATURE_ENET_INSTANCE_QUEUEn(x) - 1).
 * return The execute status.
 */
status_t ENET_GetTxErrAfterSendFrame(enet_handle_t *handle, enet_data_error_stats_t *eErrorStatic, uint8_t ringId)
{
    assert(handle != NULL);
    assert(eErrorStatic != NULL);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_QUEUE);

    uint16_t control                             = 0;
    uint16_t controlExt                          = 0;
    status_t result                              = kStatus_Success;
    bool isReturn                                = false;
    enet_tx_bd_ring_t *txBdRing                  = &handle->txBdRing[ringId];
    volatile enet_tx_bd_struct_t *curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;

    do
    {
        /* Get the current dirty transmit buffer descriptor. */
        control    = handle->txBdDirtyStatic[ringId]->control;
        controlExt = handle->txBdDirtyStatic[ringId]->controlExtend0;

        /* Get the control status data, If the buffer descriptor has not been processed break out. */
        if (0U != (control & ENET_BUFFDESCRIPTOR_TX_READY_MASK))
        {
            result   = kStatus_ENET_TxFrameBusy;
            isReturn = true;
            break;
        }

        /* Increase the transmit dirty static pointer. */
        if (0U != (handle->txBdDirtyStatic[ringId]->control & ENET_BUFFDESCRIPTOR_TX_WRAP_MASK))
        {
            handle->txBdDirtyStatic[ringId] = txBdRing->txBdBase;
        }
        else
        {
            handle->txBdDirtyStatic[ringId]++;
        }

        /* If the transmit buffer descriptor is ready and the last buffer descriptor, store packet statistic. */
        if (0U != (control & ENET_BUFFDESCRIPTOR_TX_LAST_MASK))
        {
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_TX_ERR_MASK))
            {
                /* Transmit error. */
                eErrorStatic->statsTxErr++;
            }
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_TX_EXCCOLLISIONERR_MASK))
            {
                /* Transmit excess collision error. */
                eErrorStatic->statsTxExcessCollisionErr++;
            }
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_TX_LATECOLLISIONERR_MASK))
            {
                /* Transmit late collision error. */
                eErrorStatic->statsTxLateCollisionErr++;
            }
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_TX_UNDERFLOWERR_MASK))
            {
                /* Transmit under flow error. */
                eErrorStatic->statsTxUnderFlowErr++;
            }
            if (0U != (controlExt & ENET_BUFFDESCRIPTOR_TX_OVERFLOWERR_MASK))
            {
                /* Transmit over flow error. */
                eErrorStatic->statsTxOverFlowErr++;
            }
            isReturn = true;
            break;
        }

    } while (handle->txBdDirtyStatic[ringId] != curBuffDescrip);

    if (isReturn == false)
    {
        result = kStatus_ENET_TxFrameFail;
    }
    return result;
}

void ENET_Ptp1588ConfigureHandler(ENET_Type *base, enet_handle_t *handle, enet_ptp_config_t *ptpConfig)
{
    assert(handle != NULL);
    assert(ptpConfig != NULL);
    uint8_t count;

    uint32_t mask = (uint32_t)kENET_TxBufferInterrupt;
#if FSL_FEATURE_ENET_QUEUE > 1
    mask |= (uint32_t)kENET_TxBuffer1Interrupt | (uint32_t)kENET_TxBuffer2Interrupt;
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */

    for (count = 0; count < handle->ringNum; count++)
    {
        handle->txBdDirtyStatic[count] = handle->txBdRing[count].txBdBase;
    }

    /* Setting the receive and transmit state for transaction. */
    handle->msTimerSecond = 0;

#if defined(FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID) && FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID
    uint32_t refClock;

    /* The minimum time is defined by the greater of either six register clock cycles or six ptp clock cycles. */
    if (handle->enetClock <= ptpConfig->ptp1588ClockSrc_Hz)
    {
        /* Caculate how many core cycles delay is needed. */
        /* In the cases with this IP design issue, core clock = enetClock */
        handle->tsDelayCount = 6U * handle->enetClock;
    }
    else
    {
        refClock = ptpConfig->ptp1588ClockSrc_Hz;

        /* Caculate how many core cycles delay is needed. */
        /* In the cases with this IP design issue, core clock = enetClock */
        handle->tsDelayCount = 6U * ((handle->enetClock + refClock - 1U) / refClock);
    }

#endif

    ENET_DisableInterrupts(base, mask);

    /* Set the IRQ handler when the interrupt is enabled. */
    ENET_SetTsISRHandler(base, ENET_TimeStampIRQHandler);
    ENET_SetTxISRHandler(base, ENET_TransmitIRQHandler);

    /* Enables the time stamp interrupt and transmit frame interrupt to
     * handle the time-stamp . */
    ENET_EnableInterrupts(base, (ENET_TS_INTERRUPT | ENET_TX_INTERRUPT));
}

/*!
 * brief Configures the ENET PTP IEEE 1588 feature with the basic configuration.
 * The function sets the clock for PTP 1588 timer and enables
 * time stamp interrupts and transmit interrupts for PTP 1588 features.
 * This API should be called when the 1588 feature is enabled
 * or the ENET_ENHANCEDBUFFERDESCRIPTOR_MODE is defined.
 * ENET_Init should be called before calling this API.
 *
 * note The PTP 1588 time-stamp second increase though time-stamp interrupt handler
 *  and the transmit time-stamp store is done through transmit interrupt handler.
 *  As a result, the TS interrupt and TX interrupt are enabled when you call this API.
 *
 * param base    ENET peripheral base address.
 * param handle  ENET handler pointer.
 * param ptpConfig The ENET PTP1588 configuration.
 */
void ENET_Ptp1588Configure(ENET_Type *base, enet_handle_t *handle, enet_ptp_config_t *ptpConfig)
{
    assert(handle != NULL);
    assert(ptpConfig != NULL);

    /* Start the 1588 timer. */
    ENET_Ptp1588StartTimer(base, ptpConfig->ptp1588ClockSrc_Hz);

    ENET_Ptp1588ConfigureHandler(base, handle, ptpConfig);
}

/*!
 * brief Starts the ENET PTP 1588 Timer.
 * This function is used to initialize the PTP timer. After the PTP starts,
 * the PTP timer starts running.
 *
 * param base  ENET peripheral base address.
 * param ptpClkSrc The clock source of the PTP timer.
 */
void ENET_Ptp1588StartTimer(ENET_Type *base, uint32_t ptpClkSrc)
{
    /* Restart PTP 1588 timer, master clock. */
    base->ATCR = ENET_ATCR_RESTART_MASK;

    /* Initializes PTP 1588 timer. */
    base->ATINC = ENET_ATINC_INC(ENET_NANOSECOND_ONE_SECOND / ptpClkSrc);
    base->ATPER = ENET_NANOSECOND_ONE_SECOND;
    /* Sets periodical event and the event signal output assertion and Actives PTP 1588 timer.  */
    base->ATCR = ENET_ATCR_PEREN_MASK | ENET_ATCR_PINPER_MASK | ENET_ATCR_EN_MASK;
}

/*!
 * brief Gets the current ENET time from the PTP 1588 timer.
 *       Interrupts are not disabled.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET state pointer. This is the same state pointer used in the ENET_Init.
 * param ptpTime The PTP timer structure.
 */
void ENET_Ptp1588GetTimerNoIrqDisable(ENET_Type *base, enet_handle_t *handle, enet_ptp_time_t *ptpTime)
{
    /* Get the current PTP time. */
    ptpTime->second = handle->msTimerSecond;
    /* Get the nanosecond from the master timer. */
    base->ATCR |= ENET_ATCR_CAPTURE_MASK;

#if defined(FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID) && FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID
    /* The whole while loop includes at least three instructions(subs, nop and bne). */
    uint32_t count = (handle->tsDelayCount + 3U - 1U) / 3U;

    while (0U != (count--))
    {
        __NOP();
    }
#else
    /* Wait for capture over */
    while (0U != (base->ATCR & ENET_ATCR_CAPTURE_MASK))
    {
    }
#endif

    /* Get the captured time. */
    ptpTime->nanosecond = base->ATVR;
}

/*!
 * brief Gets the current ENET time from the PTP 1588 timer.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET state pointer. This is the same state pointer used in the ENET_Init.
 * param ptpTime The PTP timer structure.
 */
void ENET_Ptp1588GetTimer(ENET_Type *base, enet_handle_t *handle, enet_ptp_time_t *ptpTime)
{
    assert(handle != NULL);
    assert(ptpTime != NULL);
    uint32_t primask;

    /* Disables the interrupt. */
    primask = DisableGlobalIRQ();

    ENET_Ptp1588GetTimerNoIrqDisable(base, handle, ptpTime);

    /* Get PTP timer wrap event. */
    if (0U != (base->EIR & (uint32_t)kENET_TsTimerInterrupt))
    {
        ptpTime->second++;
    }

    /* Enables the interrupt. */
    EnableGlobalIRQ(primask);
}

/*!
 * brief Sets the ENET PTP 1588 timer to the assigned time.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET state pointer. This is the same state pointer used in the ENET_Init.
 * param ptpTime The timer to be set to the PTP timer.
 */
void ENET_Ptp1588SetTimer(ENET_Type *base, enet_handle_t *handle, enet_ptp_time_t *ptpTime)
{
    assert(handle != NULL);
    assert(ptpTime != NULL);

    uint32_t primask;

    /* Disables the interrupt. */
    primask = DisableGlobalIRQ();

    /* Sets PTP timer. */
    handle->msTimerSecond = ptpTime->second;
    base->ATVR            = ptpTime->nanosecond;

    /* Enables the interrupt. */
    EnableGlobalIRQ(primask);
}

/*!
 * brief Adjusts the ENET PTP 1588 timer.
 *
 * param base  ENET peripheral base address.
 * param corrIncrease The correction increment value. This value is added every time the correction
 *       timer expires. A value less than the PTP timer frequency(1/ptpClkSrc) slows down the timer,
 *        a value greater than the 1/ptpClkSrc speeds up the timer.
 * param corrPeriod The PTP timer correction counter wrap-around value. This defines after how
 *       many timer clock the correction counter should be reset and trigger a correction
 *       increment on the timer. A value of 0 disables the correction counter and no correction occurs.
 */
void ENET_Ptp1588AdjustTimer(ENET_Type *base, uint32_t corrIncrease, uint32_t corrPeriod)
{
    /* Set correction for PTP timer increment. */
    base->ATINC = (base->ATINC & ~ENET_ATINC_INC_CORR_MASK) | (corrIncrease << ENET_ATINC_INC_CORR_SHIFT);
    /* Set correction for PTP timer period. */
    base->ATCOR = (base->ATCOR & ~ENET_ATCOR_COR_MASK) | (corrPeriod << ENET_ATCOR_COR_SHIFT);
}

#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
/*!
 * brief Sets the ENET AVB feature.
 *
 * ENET AVB feature configuration, set the Receive classification match and transmit
 * bandwidth. This API is called when the AVB feature is required.
 *
 * Note: The AVB frames transmission scheme is credit-based tx scheme and it's only supported
 * with the Enhanced buffer descriptors. so the AVB configuration should only done with
 * Enhanced buffer descriptor. so when the AVB feature is required, please make sure the
 * the "ENET_ENHANCEDBUFFERDESCRIPTOR_MODE" is defined.
 *
 * param base ENET peripheral base address.
 * param handle ENET handler pointer.
 * param config The ENET AVB feature configuration structure.
 */
void ENET_AVBConfigure(ENET_Type *base, enet_handle_t *handle, const enet_avb_config_t *config)
{
    assert(config != NULL);
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);

    uint8_t count = 0;

    for (count = 0; count < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) - 1U; count++)
    {
        /* Set the AVB receive ring classification match when the match is not 0. */
        if (0U != (config->rxClassifyMatch[count]))
        {
            base->RCMR[count] = ((uint32_t)config->rxClassifyMatch[count] & 0xFFFFU) | ENET_RCMR_MATCHEN_MASK;
        }
        /* Set the dma controller for the extended ring. */
        base->DMACFG[count] |= ENET_DMACFG_IDLE_SLOPE(config->idleSlope[count]);
    }

    /* Shall use the credit-based scheme for avb. */
    base->QOS &= ~ENET_QOS_TX_SCHEME_MASK;
    base->QOS |= ENET_QOS_RX_FLUSH0_MASK;
}
#endif /* FSL_FEATURE_ENET_HAS_AVB */
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

#if FSL_FEATURE_ENET_QUEUE > 1
/*!
 * brief The transmit IRQ handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer.
 */
void ENET_TransmitIRQHandler(ENET_Type *base, enet_handle_t *handle, uint32_t ringId)
#else
/*!
 * brief The transmit IRQ handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer.
 */
void ENET_TransmitIRQHandler(ENET_Type *base, enet_handle_t *handle)
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
{
    assert(handle != NULL);
    uint32_t mask  = (uint32_t)kENET_TxBufferInterrupt | (uint32_t)kENET_TxFrameInterrupt;
    uint32_t index = 0;
    uint32_t irq;

/* Check if the transmit interrupt happen. */
#if FSL_FEATURE_ENET_QUEUE > 1
    switch (ringId)
    {
        case kENET_Ring1:
            mask = ((uint32_t)kENET_TxFrame1Interrupt | (uint32_t)kENET_TxBuffer1Interrupt);
            break;
        case kENET_Ring2:
            mask = ((uint32_t)kENET_TxFrame2Interrupt | (uint32_t)kENET_TxBuffer2Interrupt);
            break;
        default:
            mask = (uint32_t)kENET_TxBufferInterrupt | (uint32_t)kENET_TxFrameInterrupt;
            break;
    }
    index = ringId;
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */

    while (0U != (mask & base->EIR))
    {
        irq = base->EIR;

        /* Clear the transmit interrupt event. */
        base->EIR = mask;

        /* Callback Handler. */
        if (handle->txReclaimEnable[index] && (0U != (irq & (uint32_t)kENET_TxFrameInterrupt)))
        {
            ENET_ReclaimTxDescriptor(base, handle, (uint8_t)index);
        }
        else
        {
            if (NULL != handle->callback)
            {
#if FSL_FEATURE_ENET_QUEUE > 1
                handle->callback(base, handle, index, kENET_TxEvent, NULL, handle->userData);
#else
                handle->callback(base, handle, kENET_TxEvent, NULL, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
            }
        }
    }
}

/*!
 * brief The receive IRQ handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer.
 */
#if FSL_FEATURE_ENET_QUEUE > 1
void ENET_ReceiveIRQHandler(ENET_Type *base, enet_handle_t *handle, uint32_t ringId)
#else
void ENET_ReceiveIRQHandler(ENET_Type *base, enet_handle_t *handle)
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
{
    assert(handle != NULL);
    uint32_t mask = (uint32_t)kENET_RxFrameInterrupt | (uint32_t)kENET_RxBufferInterrupt;

/* Check if the receive interrupt happen. */
#if FSL_FEATURE_ENET_QUEUE > 1
    switch (ringId)
    {
        case kENET_Ring1:
            mask = ((uint32_t)kENET_RxFrame1Interrupt | (uint32_t)kENET_RxBuffer1Interrupt);
            break;
        case kENET_Ring2:
            mask = ((uint32_t)kENET_RxFrame2Interrupt | (uint32_t)kENET_RxBuffer2Interrupt);
            break;
        default:
            mask = (uint32_t)kENET_RxFrameInterrupt | (uint32_t)kENET_RxBufferInterrupt;
            break;
    }
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */

    while (0U != (mask & base->EIR))
    {
        /* Clear the transmit interrupt event. */
        base->EIR = mask;

        /* Callback function. */
        if (NULL != handle->callback)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            handle->callback(base, handle, ringId, kENET_RxEvent, NULL, handle->userData);
#else
            handle->callback(base, handle, kENET_RxEvent, NULL, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }
}

/*!
 * brief Some special IRQ handler including the error, mii, wakeup irq handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET handler pointer.
 */
void ENET_ErrorIRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t errMask = (uint32_t)kENET_BabrInterrupt | (uint32_t)kENET_BabtInterrupt | (uint32_t)kENET_EBusERInterrupt |
                       (uint32_t)kENET_PayloadRxInterrupt | (uint32_t)kENET_LateCollisionInterrupt |
                       (uint32_t)kENET_RetryLimitInterrupt | (uint32_t)kENET_UnderrunInterrupt;

    /* Check if the error interrupt happen. */
    if (0U != ((uint32_t)kENET_WakeupInterrupt & base->EIR))
    {
        /* Clear the wakeup interrupt. */
        base->EIR = (uint32_t)kENET_WakeupInterrupt;
        /* wake up and enter the normal mode. */
        ENET_EnableSleepMode(base, false);
        /* Callback function. */
        if (NULL != handle->callback)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            handle->callback(base, handle, 0, kENET_WakeUpEvent, NULL, handle->userData);
#else
            handle->callback(base, handle, kENET_WakeUpEvent, NULL, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }
    else
    {
        /* Clear the error interrupt event status. */
        errMask &= base->EIR;
        base->EIR = errMask;
        /* Callback function. */
        if (NULL != handle->callback)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            handle->callback(base, handle, 0, kENET_ErrEvent, NULL, handle->userData);
#else
            handle->callback(base, handle, kENET_ErrEvent, NULL, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }
}

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
/*!
 * brief The IEEE 1588 PTP time stamp interrupt handler.
 *
 * param base  ENET peripheral base address.
 * param handle The ENET state pointer. This is the same state pointer used in the ENET_Init.
 */
void ENET_TimeStampIRQHandler(ENET_Type *base, enet_handle_t *handle)
{
    assert(handle != NULL);

    /* Check if the PTP time stamp interrupt happen. */
    if (0U != ((uint32_t)kENET_TsTimerInterrupt & base->EIR))
    {
        /* Clear the time stamp interrupt. */
        base->EIR = (uint32_t)kENET_TsTimerInterrupt;

        /* Increase timer second counter. */
        handle->msTimerSecond++;

        /* Callback function. */
        if (NULL != handle->callback)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            handle->callback(base, handle, 0, kENET_TimeStampEvent, NULL, handle->userData);
#else
            handle->callback(base, handle, kENET_TimeStampEvent, NULL, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }

    if (0U != ((uint32_t)kENET_TsAvailInterrupt & base->EIR))
    {
        /* Clear the time stamp interrupt. */
        base->EIR = (uint32_t)kENET_TsAvailInterrupt;
        /* Callback function. */
        if (NULL != handle->callback)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            handle->callback(base, handle, 0, kENET_TimeStampAvailEvent, NULL, handle->userData);
#else
            handle->callback(base, handle, kENET_TimeStampAvailEvent, NULL, handle->userData);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }
}
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

/*!
 * brief the common IRQ handler for the tx/rx/error etc irq handler.
 *
 * This is used for the combined tx/rx/error interrupt for single/mutli-ring (frame 0).
 *
 * param base  ENET peripheral base address.
 */
void ENET_CommonFrame0IRQHandler(ENET_Type *base)
{
    uint32_t event    = base->EIR;
    uint32_t instance = ENET_GetInstance(base);

    event &= base->EIMR;
    if (0U != (event & ((uint32_t)kENET_TxBufferInterrupt | (uint32_t)kENET_TxFrameInterrupt)))
    {
        if (s_enetTxIsr[instance] != NULL)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            s_enetTxIsr[instance](base, s_ENETHandle[instance], 0);
#else
            s_enetTxIsr[instance](base, s_ENETHandle[instance]);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }

    if (0U != (event & ((uint32_t)kENET_RxBufferInterrupt | (uint32_t)kENET_RxFrameInterrupt)))
    {
        if (s_enetRxIsr[instance] != NULL)
        {
#if FSL_FEATURE_ENET_QUEUE > 1
            s_enetRxIsr[instance](base, s_ENETHandle[instance], 0);
#else
            s_enetRxIsr[instance](base, s_ENETHandle[instance]);
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
        }
    }

    if (0U != (event & ENET_TS_INTERRUPT) && (NULL != s_enetTsIsr[instance]))
    {
        s_enetTsIsr[instance](base, s_ENETHandle[instance]);
    }
    if (0U != (event & ENET_ERR_INTERRUPT) && (NULL != s_enetErrIsr[instance]))
    {
        s_enetErrIsr[instance](base, s_ENETHandle[instance]);
    }
}

#if FSL_FEATURE_ENET_QUEUE > 1
/*!
 * brief the common IRQ handler for the tx/rx irq handler.
 *
 * This is used for the combined tx/rx interrupt for multi-ring (frame 1).
 *
 * param base  ENET peripheral base address.
 */
void ENET_CommonFrame1IRQHandler(ENET_Type *base)
{
    uint32_t event    = base->EIR;
    uint32_t instance = ENET_GetInstance(base);

    event &= base->EIMR;
    if (0U != (event & ((uint32_t)kENET_TxBuffer1Interrupt | (uint32_t)kENET_TxFrame1Interrupt)))
    {
        if (s_enetTxIsr[instance] != NULL)
        {
            s_enetTxIsr[instance](base, s_ENETHandle[instance], 1);
        }
    }

    if (0U != (event & ((uint32_t)kENET_RxBuffer1Interrupt | (uint32_t)kENET_RxFrame1Interrupt)))
    {
        if (s_enetRxIsr[instance] != NULL)
        {
            s_enetRxIsr[instance](base, s_ENETHandle[instance], 1);
        }
    }
}

/*!
 * brief the common IRQ handler for the tx/rx irq handler.
 *
 * This is used for the combined tx/rx interrupt for multi-ring (frame 2).
 *
 * param base  ENET peripheral base address.
 */
void ENET_CommonFrame2IRQHandler(ENET_Type *base)
{
    uint32_t event    = base->EIR;
    uint32_t instance = ENET_GetInstance(base);

    event &= base->EIMR;
    if (0U != (event & ((uint32_t)kENET_TxBuffer2Interrupt | (uint32_t)kENET_TxFrame2Interrupt)))
    {
        if (s_enetTxIsr[instance] != NULL)
        {
            s_enetTxIsr[instance](base, s_ENETHandle[instance], 2);
        }
    }

    if (0U != (event & ((uint32_t)kENET_RxBuffer2Interrupt | (uint32_t)kENET_RxFrame2Interrupt)))
    {
        if (s_enetRxIsr[instance] != NULL)
        {
            s_enetRxIsr[instance](base, s_ENETHandle[instance], 2);
        }
    }
}
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */

void ENET_Ptp1588IRQHandler(ENET_Type *base)
{
    uint32_t instance = ENET_GetInstance(base);

#if defined(ENET_ENHANCEDBUFFERDESCRIPTOR_MODE) && ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    /* In some platforms, the 1588 event uses same irq with timestamp event. */
    if ((s_enetTsIrqId[instance] == s_enet1588TimerIrqId[instance]) && (s_enetTsIrqId[instance] != NotAvail_IRQn))
    {
        uint32_t event = base->EIR;
        event &= base->EIMR;
        if (0U != (event & ((uint32_t)kENET_TsTimerInterrupt | (uint32_t)kENET_TsAvailInterrupt)))
        {
            if (s_enetTsIsr[instance] != NULL)
            {
                s_enetTsIsr[instance](base, s_ENETHandle[instance]);
            }
        }
    }
#endif

    if (s_enet1588TimerIsr[instance] != NULL)
    {
        s_enet1588TimerIsr[instance](base, s_ENETHandle[instance]);
    }
}

#if defined(ENET)
#if FSL_FEATURE_ENET_QUEUE < 2
void ENET_TxIRQHandler(ENET_Type *base);
void ENET_TxIRQHandler(ENET_Type *base)
{
    uint32_t instance = ENET_GetInstance(base);

    if (s_enetTxIsr[instance] != NULL)
    {
        s_enetTxIsr[instance](base, s_ENETHandle[instance]);
    }
    SDK_ISR_EXIT_BARRIER;
}

void ENET_RxIRQHandler(ENET_Type *base);
void ENET_RxIRQHandler(ENET_Type *base)
{
    uint32_t instance = ENET_GetInstance(base);

    if (s_enetRxIsr[instance] != NULL)
    {
        s_enetRxIsr[instance](base, s_ENETHandle[instance]);
    }
}

void ENET_ErrIRQHandler(ENET_Type *base);
void ENET_ErrIRQHandler(ENET_Type *base)
{
    uint32_t instance = ENET_GetInstance(base);

    if (s_enetErrIsr[instance] != NULL)
    {
        s_enetErrIsr[instance](base, s_ENETHandle[instance]);
    }
}

void ENET_Transmit_DriverIRQHandler(void);
void ENET_Transmit_DriverIRQHandler(void)
{
    ENET_TxIRQHandler(ENET);
    SDK_ISR_EXIT_BARRIER;
}

void ENET_Receive_DriverIRQHandler(void);
void ENET_Receive_DriverIRQHandler(void)
{
    ENET_RxIRQHandler(ENET);
    SDK_ISR_EXIT_BARRIER;
}

void ENET_Error_DriverIRQHandler(void);
void ENET_Error_DriverIRQHandler(void)
{
    ENET_ErrIRQHandler(ENET);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_ENET_QUEUE < 2 */

void ENET_DriverIRQHandler(void);
void ENET_DriverIRQHandler(void)
{
    ENET_CommonFrame0IRQHandler(ENET);
    SDK_ISR_EXIT_BARRIER;
}

void ENET_1588_Timer_DriverIRQHandler(void);
void ENET_1588_Timer_DriverIRQHandler(void)
{
    ENET_Ptp1588IRQHandler(ENET);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* ENET */

#if defined(ENET1)
void ENET1_DriverIRQHandler(void);
void ENET1_DriverIRQHandler(void)
{
    ENET_CommonFrame0IRQHandler(ENET1);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* ENET1 */

#if defined(ENET2)
void ENET2_DriverIRQHandler(void);
void ENET2_DriverIRQHandler(void)
{
    ENET_CommonFrame0IRQHandler(ENET2);
    SDK_ISR_EXIT_BARRIER;
}

void ENET2_1588_Timer_DriverIRQHandler(void);
void ENET2_1588_Timer_DriverIRQHandler(void)
{
    ENET_Ptp1588IRQHandler(ENET2);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* ENET2 */

#if defined(CONNECTIVITY__ENET0)
void CONNECTIVITY_ENET0_FRAME0_EVENT_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET0_FRAME0_EVENT_INT_DriverIRQHandler(void)
{
    ENET_CommonFrame0IRQHandler(CONNECTIVITY__ENET0);
    SDK_ISR_EXIT_BARRIER;
}
#if FSL_FEATURE_ENET_QUEUE > 1
void CONNECTIVITY_ENET0_FRAME1_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET0_FRAME1_INT_DriverIRQHandler(void)
{
    ENET_CommonFrame1IRQHandler(CONNECTIVITY__ENET0);
    SDK_ISR_EXIT_BARRIER;
}
void CONNECTIVITY_ENET0_FRAME2_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET0_FRAME2_INT_DriverIRQHandler(void)
{
    ENET_CommonFrame2IRQHandler(CONNECTIVITY__ENET0);
    SDK_ISR_EXIT_BARRIER;
}
void CONNECTIVITY_ENET0_TIMER_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET0_TIMER_INT_DriverIRQHandler(void)
{
    ENET_Ptp1588IRQHandler(CONNECTIVITY__ENET0);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
#endif /* CONNECTIVITY__ENET0 */
#if defined(CONNECTIVITY__ENET1)
void CONNECTIVITY_ENET1_FRAME0_EVENT_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET1_FRAME0_EVENT_INT_DriverIRQHandler(void)
{
    ENET_CommonFrame0IRQHandler(CONNECTIVITY__ENET1);
    SDK_ISR_EXIT_BARRIER;
}
#if FSL_FEATURE_ENET_QUEUE > 1
void CONNECTIVITY_ENET1_FRAME1_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET1_FRAME1_INT_DriverIRQHandler(void)
{
    ENET_CommonFrame1IRQHandler(CONNECTIVITY__ENET1);
    SDK_ISR_EXIT_BARRIER;
}
void CONNECTIVITY_ENET1_FRAME2_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET1_FRAME2_INT_DriverIRQHandler(void)
{
    ENET_CommonFrame2IRQHandler(CONNECTIVITY__ENET1);
    SDK_ISR_EXIT_BARRIER;
}
void CONNECTIVITY_ENET1_TIMER_INT_DriverIRQHandler(void);
void CONNECTIVITY_ENET1_TIMER_INT_DriverIRQHandler(void)
{
    ENET_Ptp1588IRQHandler(CONNECTIVITY__ENET1);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
#endif /* CONNECTIVITY__ENET1 */
#if FSL_FEATURE_ENET_QUEUE > 1
#if defined(ENET_1G)
void ENET_1G_DriverIRQHandler(void);
void ENET_1G_DriverIRQHandler(void)
{
    ENET_CommonFrame0IRQHandler(ENET_1G);
    SDK_ISR_EXIT_BARRIER;
}
void ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler(void);
void ENET_1G_MAC0_Tx_Rx_1_DriverIRQHandler(void)
{
    ENET_CommonFrame1IRQHandler(ENET_1G);
    SDK_ISR_EXIT_BARRIER;
}
void ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler(void);
void ENET_1G_MAC0_Tx_Rx_2_DriverIRQHandler(void)
{
    ENET_CommonFrame2IRQHandler(ENET_1G);
    SDK_ISR_EXIT_BARRIER;
}
void ENET_1G_1588_Timer_DriverIRQHandler(void);
void ENET_1G_1588_Timer_DriverIRQHandler(void)
{
    ENET_Ptp1588IRQHandler(ENET_1G);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* ENET_1G */

#if defined(ENET1)
void ENET1_MAC0_Rx_Tx_Done0_DriverIRQHandler(void);
void ENET1_MAC0_Rx_Tx_Done0_DriverIRQHandler(void)
{
    ENET_CommonFrame1IRQHandler(ENET1);
    SDK_ISR_EXIT_BARRIER;
}
void ENET1_MAC0_Rx_Tx_Done1_DriverIRQHandler(void);
void ENET1_MAC0_Rx_Tx_Done1_DriverIRQHandler(void)
{
    ENET_CommonFrame2IRQHandler(ENET1);
    SDK_ISR_EXIT_BARRIER;
}
void ENET1_1588_Timer_DriverIRQHandler(void);
void ENET1_1588_Timer_DriverIRQHandler(void)
{
    ENET_Ptp1588IRQHandler(ENET1);
    SDK_ISR_EXIT_BARRIER;
}
#endif /* ENET1 */
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
