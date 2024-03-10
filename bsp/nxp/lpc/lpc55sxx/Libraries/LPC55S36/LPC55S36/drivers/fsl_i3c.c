/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i3c.h"
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.i3c"
#endif

#define I3C_BROADCASE_ADDR (0x7EU)

#define NSEC_PER_SEC            (1000000000UL)
#define FSL_I3C_ERROR_RATE_MAX  (10U)
#define FSL_I3C_PPBAUD_DIV_MAX  ((I3C_MCONFIG_PPBAUD_MASK >> I3C_MCONFIG_PPBAUD_SHIFT) + 1U)
#define FSL_I3C_ODBAUD_DIV_MAX  ((I3C_MCONFIG_ODBAUD_MASK >> I3C_MCONFIG_ODBAUD_SHIFT) + 1U)
#define FSL_I3C_I2CBAUD_DIV_MAX (((I3C_MCONFIG_I2CBAUD_MASK >> I3C_MCONFIG_I2CBAUD_SHIFT) + 1U) / 2U)

/*! @brief Common sets of flags used by the driver. */
enum _i3c_flag_constants
{
    /*! All flags which are cleared by the driver upon starting a transfer. */
    kMasterClearFlags = kI3C_MasterSlaveStartFlag | kI3C_MasterControlDoneFlag | kI3C_MasterCompleteFlag |
                        kI3C_MasterArbitrationWonFlag | kI3C_MasterSlave2MasterFlag | kI3C_MasterErrorFlag,

    /*! IRQ sources enabled by the non-blocking transactional API. */
    kMasterIrqFlags = kI3C_MasterSlaveStartFlag | kI3C_MasterControlDoneFlag | kI3C_MasterCompleteFlag |
                      kI3C_MasterRxReadyFlag /* | kI3C_MasterTxReadyFlag */ | kI3C_MasterArbitrationWonFlag |
                      kI3C_MasterErrorFlag | kI3C_MasterSlave2MasterFlag,

    /*! Errors to check for. */
    kMasterErrorFlags = kI3C_MasterErrorNackFlag | kI3C_MasterErrorWriteAbortFlag |
#if !defined(FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM) || (!FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM)
                        kI3C_MasterErrorTermFlag |
#endif
                        kI3C_MasterErrorParityFlag | kI3C_MasterErrorCrcFlag | kI3C_MasterErrorReadFlag |
                        kI3C_MasterErrorWriteFlag | kI3C_MasterErrorMsgFlag | kI3C_MasterErrorInvalidReqFlag |
                        kI3C_MasterErrorTimeoutFlag,
    /*! All flags which are cleared by the driver upon starting a transfer. */
    kSlaveClearFlags = kI3C_SlaveBusStartFlag | kI3C_SlaveMatchedFlag | kI3C_SlaveBusStopFlag,

    /*! IRQ sources enabled by the non-blocking transactional API. */
    kSlaveIrqFlags = kI3C_SlaveBusStartFlag | kI3C_SlaveMatchedFlag | kI3C_SlaveBusStopFlag | kI3C_SlaveRxReadyFlag |
                     kI3C_SlaveDynamicAddrChangedFlag | kI3C_SlaveReceivedCCCFlag | kI3C_SlaveErrorFlag |
                     kI3C_SlaveHDRCommandMatchFlag | kI3C_SlaveCCCHandledFlag | kI3C_SlaveEventSentFlag,

    /*! Errors to check for. */
    kSlaveErrorFlags = kI3C_SlaveErrorOverrunFlag | kI3C_SlaveErrorUnderrunFlag | kI3C_SlaveErrorUnderrunNakFlag |
                       kI3C_SlaveErrorTermFlag | kI3C_SlaveErrorInvalidStartFlag | kI3C_SlaveErrorSdrParityFlag |
                       kI3C_SlaveErrorHdrParityFlag | kI3C_SlaveErrorHdrCRCFlag | kI3C_SlaveErrorS0S1Flag |
                       kI3C_SlaveErrorOverreadFlag | kI3C_SlaveErrorOverwriteFlag,
};

/*! @brief States for the state machine used by transactional APIs. */
enum _i3c_transfer_states
{
    kIdleState = 0,
    kIBIWonState,
    kSlaveStartState,
    kSendCommandState,
    kWaitRepeatedStartCompleteState,
    kTransferDataState,
    kStopState,
    kWaitForCompletionState,
};

/*! @brief Typedef for slave interrupt handler. */
typedef void (*i3c_slave_isr_t)(I3C_Type *base, i3c_slave_handle_t *handle);

/*!
 * @brief Used for conversion between `uint8_t*` and `uint32_t`.
 */
typedef union i3c_puint8_to_u32
{
    uint8_t *puint8;
    uint32_t u32;
    const uint8_t *cpuint8;
} i3c_puint8_to_u32_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Not static so it can be used from fsl_i3c_dma.c. */
static status_t I3C_MasterWaitForTxReady(I3C_Type *base, uint8_t byteCounts);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map I3C instance number to base pointer. */
static I3C_Type *const kI3cBases[] = I3C_BASE_PTRS;

/*! @brief Array to map I3C instance number to IRQ number. */
IRQn_Type const kI3cIrqs[] = I3C_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map I3C instance number to clock gate enum. */
static clock_ip_name_t const kI3cClocks[] = I3C_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
/*! @brief Pointers to I3C resets for each instance. */
static const reset_ip_name_t kI3cResets[] = I3C_RSTS;
#endif

static i3c_device_info_t devList[I3C_MAX_DEVCNT]; /*!< I3C slave record list */

/*! @brief Pointer to master IRQ handler for each instance. */
i3c_master_isr_t s_i3cMasterIsr;

/*! @brief Pointers to master handles for each instance. */
void *s_i3cMasterHandle[ARRAY_SIZE(kI3cBases)];

/*! @brief Pointer to slave IRQ handler for each instance. */
static i3c_slave_isr_t s_i3cSlaveIsr;

/*! @brief Pointers to slave handles for each instance. */
i3c_slave_handle_t *s_i3cSlaveHandle[ARRAY_SIZE(kI3cBases)];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Returns an instance number given a base address.
 *
 * If an invalid base address is passed, debug builds will assert. Release builds will just return
 * instance number 0.
 *
 * @param base The I3C peripheral base address.
 * @return I3C instance number starting from 0.
 */
uint32_t I3C_GetInstance(I3C_Type *base)
{
    uint32_t instance;
    for (instance = 0; instance < ARRAY_SIZE(kI3cBases); ++instance)
    {
        if (kI3cBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(kI3cBases));

    return instance;
}

/*!
 * @brief Convert provided flags to status code, and clear any errors if present.
 * @param base The I3C peripheral base address.
 * @param status Current status flags value that will be checked.
 * @retval #kStatus_Success
 * @retval #kStatus_I3C_Nak
 * @retval #kStatus_I3C_WriteAbort
 * @retval #kStatus_I3C_Term
 * @retval #kStatus_I3C_HdrParityError
 * @retval #kStatus_I3C_CrcError
 * @retval #kStatus_I3C_ReadFifoError
 * @retval #kStatus_I3C_WriteFifoError
 * @retval #kStatus_I3C_MsgError
 * @retval #kStatus_I3C_InvalidReq
 * @retval #kStatus_I3C_Timeout
 */
/* Not static so it can be used from fsl_i3c_edma.c. */
status_t I3C_MasterCheckAndClearError(I3C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new transfer can start. */
    status &= (uint32_t)kMasterErrorFlags;
    if (0UL != (status))
    {
        /* Select the correct error code. Ordered by severity, with bus issues first. */
        if (0UL != (status & (uint32_t)kI3C_MasterErrorTimeoutFlag))
        {
            result = kStatus_I3C_Timeout;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorNackFlag))
        {
            result = kStatus_I3C_Nak;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorWriteAbortFlag))
        {
            result = kStatus_I3C_WriteAbort;
        }
#if !defined(FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM) || (!FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM)
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorTermFlag))
        {
            result = kStatus_I3C_Term;
        }
#endif
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorParityFlag))
        {
            result = kStatus_I3C_HdrParityError;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorCrcFlag))
        {
            result = kStatus_I3C_CrcError;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorMsgFlag))
        {
            result = kStatus_I3C_MsgError;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorReadFlag))
        {
            result = kStatus_I3C_ReadFifoError;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorWriteFlag))
        {
            result = kStatus_I3C_WriteFifoError;
        }
        else if (0UL != (status & (uint32_t)kI3C_MasterErrorInvalidReqFlag))
        {
            result = kStatus_I3C_InvalidReq;
        }
        else
        {
            assert(false);
        }

        /* Clear the flags. */
        I3C_MasterClearErrorStatusFlags(base, status);

        /* Reset fifos. These flags clear automatically. */
        base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;
    }

    return result;
}

static status_t I3C_MasterWaitForCtrlDone(I3C_Type *base, bool waitIdle)
{
    status_t result = kStatus_Success;
    uint32_t status, errStatus;
#if I3C_RETRY_TIMES
    uint32_t waitTimes = I3C_RETRY_TIMES;
#endif

#if I3C_RETRY_TIMES
    while ((result == kStatus_Success) && (--waitTimes))
#else
    while (result == kStatus_Success)
#endif
    {
        status    = I3C_MasterGetStatusFlags(base);
        errStatus = I3C_MasterGetErrorStatusFlags(base);
        /* Check for error flags. */
        result = I3C_MasterCheckAndClearError(base, errStatus);
        /* Check if the control finishes. */
        if (0UL != (status & (uint32_t)kI3C_MasterControlDoneFlag))
        {
            I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterControlDoneFlag);
            if (!waitIdle)
            {
                break;
            }
        }
        /* kI3C_MasterControlDoneFlag only indicates ACK got, need to wait for SDA high. */
        if (waitIdle && I3C_MasterGetState(base) == kI3C_MasterStateIdle)
        {
            break;
        }
    }

#if I3C_RETRY_TIMES
    if (waitTimes == 0)
    {
        return kStatus_I3C_Timeout;
    }
#endif

    return result;
}

static status_t I3C_MasterWaitForTxReady(I3C_Type *base, uint8_t byteCounts)
{
    uint32_t errStatus;
    status_t result;
    size_t txCount;
    size_t txFifoSize =
        2UL << ((base->SCAPABILITIES & I3C_SCAPABILITIES_FIFOTX_MASK) >> I3C_SCAPABILITIES_FIFOTX_SHIFT);

#if I3C_RETRY_TIMES
    uint32_t waitTimes = I3C_RETRY_TIMES;
#endif
    do
    {
        /* Get the number of words in the tx fifo and compute empty slots. */
        I3C_MasterGetFifoCounts(base, NULL, &txCount);
        txCount = txFifoSize - txCount;

        /* Check for error flags. */
        errStatus = I3C_MasterGetErrorStatusFlags(base);
        result    = I3C_MasterCheckAndClearError(base, errStatus);
        if (kStatus_Success != result)
        {
            return result;
        }
#if I3C_RETRY_TIMES
    } while ((txCount < byteCounts) && (--waitTimes));

    if (waitTimes == 0)
    {
        return kStatus_I3C_Timeout;
    }
#else
    } while (txCount < byteCounts);
#endif

    return kStatus_Success;
}

static status_t I3C_MasterWaitForComplete(I3C_Type *base, bool waitIdle)
{
    uint32_t status, errStatus;
    status_t result = kStatus_Success;
#if I3C_RETRY_TIMES
    uint32_t waitTimes = I3C_RETRY_TIMES;
#endif
    do
    {
        status    = I3C_MasterGetStatusFlags(base);
        errStatus = I3C_MasterGetErrorStatusFlags(base);
        result    = I3C_MasterCheckAndClearError(base, errStatus);
#if I3C_RETRY_TIMES
    } while (((status & (uint32_t)kI3C_MasterCompleteFlag) != (uint32_t)kI3C_MasterCompleteFlag) &&
             (result == kStatus_Success) && --waitTimes);
#else
    } while (((status & (uint32_t)kI3C_MasterCompleteFlag) != (uint32_t)kI3C_MasterCompleteFlag) &&
             (result == kStatus_Success));
#endif

    I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterCompleteFlag);

#if I3C_RETRY_TIMES
    if (waitTimes == 0UL)
    {
        return kStatus_I3C_Timeout;
    }
#endif

    if (waitIdle)
    {
#if I3C_RETRY_TIMES
        while ((I3C_MasterGetState(base) != kI3C_MasterStateIdle) && --waitTimes)
#else
        while (I3C_MasterGetState(base) != kI3C_MasterStateIdle)
#endif
        {
        }
    }

    return result;
}

/*!
 * @brief Convert provided flags to status code, and clear any errors if present.
 * @param base The I3C peripheral base address.
 * @param status Current status flags value that will be checked.
 * @retval #kStatus_Success
 * @retval #kStatus_I3C_OverrunError
 * @retval #kStatus_I3C_UnderrunError
 * @retval #kStatus_I3C_UnderrunNak
 * @retval #kStatus_I3C_Term
 * @retval #kStatus_I3C_InvalidStart
 * @retval #kStatus_I3C_SdrParityError
 * @retval #kStatus_I3C_HdrParityError
 * @retval #kStatus_I3C_CrcError
 * @retval #kStatus_I3C_S0S1Error
 * @retval #kStatus_I3C_ReadFifoError
 * @retval #kStatus_I3C_WriteFifoError
 */
static status_t I3C_SlaveCheckAndClearError(I3C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new transfer can start. */
    status &= (uint32_t)kSlaveErrorFlags;
    if (0UL != status)
    {
        /* Select the correct error code. Ordered by severity, with bus issues first. */
        if (0UL != (status & (uint32_t)kI3C_SlaveErrorOverrunFlag))
        {
            result = kStatus_I3C_OverrunError;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorUnderrunFlag))
        {
            result = kStatus_I3C_UnderrunError;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorUnderrunNakFlag))
        {
            result = kStatus_I3C_UnderrunNak;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorTermFlag))
        {
            result = kStatus_I3C_Term;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorInvalidStartFlag))
        {
            result = kStatus_I3C_InvalidStart;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorSdrParityFlag))
        {
            result = kStatus_I3C_SdrParityError;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorHdrParityFlag))
        {
            result = kStatus_I3C_HdrParityError;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorHdrCRCFlag))
        {
            result = kStatus_I3C_CrcError;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorS0S1Flag))
        {
            result = kStatus_I3C_S0S1Error;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorOverreadFlag))
        {
            result = kStatus_I3C_ReadFifoError;
        }
        else if (0UL != (status & (uint32_t)kI3C_SlaveErrorOverwriteFlag))
        {
            result = kStatus_I3C_WriteFifoError;
        }
        else
        {
            assert(false);
        }

        /* Clear the flags. */
        I3C_SlaveClearErrorStatusFlags(base, status);

        /* Reset fifos. These flags clear automatically. */
        base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK | I3C_SDATACTRL_FLUSHFB_MASK;
    }

    return result;
}

static status_t I3C_SlaveWaitForTxReady(I3C_Type *base)
{
    uint32_t errStatus;
    status_t result;
    size_t txCount;
    size_t txFifoSize =
        2UL << ((base->SCAPABILITIES & I3C_SCAPABILITIES_FIFOTX_MASK) >> I3C_SCAPABILITIES_FIFOTX_SHIFT);

#if I3C_RETRY_TIMES
    uint32_t waitTimes = I3C_RETRY_TIMES;
#endif
    do
    {
        /* Get the number of words in the tx fifo and compute empty slots. */
        I3C_SlaveGetFifoCounts(base, NULL, &txCount);
        txCount = txFifoSize - txCount;

        /* Check for error flags. */
        errStatus = I3C_SlaveGetErrorStatusFlags(base);
        result    = I3C_SlaveCheckAndClearError(base, errStatus);
        if (kStatus_Success != result)
        {
            return result;
        }
#if I3C_RETRY_TIMES
    } while ((txCount == 0UL) && (--waitTimes));

    if (waitTimes == 0)
    {
        return kStatus_I3C_Timeout;
    }
#else
    } while (txCount == 0UL);
#endif

    return kStatus_Success;
}

static status_t I3C_MasterEmitStop(I3C_Type *base, bool waitIdle)
{
    status_t result = kStatus_Success;

    /* Return an error if the bus is not in transaction. */
    if (I3C_MasterGetState(base) != kI3C_MasterStateNormAct)
    {
        return kStatus_I3C_InvalidReq;
    }

    /* Send the STOP signal */
    base->MCTRL = (base->MCTRL & ~(I3C_MCTRL_REQUEST_MASK | I3C_MCTRL_DIR_MASK | I3C_MCTRL_RDTERM_MASK)) |
                  I3C_MCTRL_REQUEST(kI3C_RequestEmitStop);

    /* Wait for the stop operation finishes. */
    /* Also check for errors while waiting. */
    result = I3C_MasterWaitForCtrlDone(base, waitIdle);

    return result;
}

static i3c_ibi_type_t I3C_GetIBIType(I3C_Type *base)
{
    uint32_t ibiValue      = (base->MSTATUS & I3C_MSTATUS_IBITYPE_MASK) >> I3C_MSTATUS_IBITYPE_SHIFT;
    i3c_ibi_type_t ibiType = kI3C_IbiNormal;

    switch (ibiValue)
    {
        case 3L:
            ibiType = kI3C_IbiHotJoin;
            break;
        case 2L:
            ibiType = kI3C_IbiMasterRequest;
            break;
        default:
            ibiType = kI3C_IbiNormal;
            break;
    }

    return ibiType;
}

static inline uint8_t I3C_GetIBIAddress(I3C_Type *base)
{
    return (uint8_t)((base->MSTATUS & I3C_MSTATUS_IBIADDR_MASK) >> I3C_MSTATUS_IBIADDR_SHIFT);
}
/*!
 * @brief Make sure the bus isn't already busy.
 *
 * A busy bus is allowed if we are the one driving it.
 *
 * @param base The I3C peripheral base address.
 * @retval #kStatus_Success
 * @retval #kStatus_I3C_Busy
 */
/* Not static so it can be used from fsl_i3c_edma.c. */
status_t I3C_CheckForBusyBus(I3C_Type *base)
{
    return (I3C_MasterGetBusIdleState(base) == true) ? kStatus_Success : kStatus_I3C_Busy;
}

/* brief Provides a default configuration for the I3C peripheral.
 *
 */
void I3C_GetDefaultConfig(i3c_config_t *config)
{
    assert(NULL != config);

    (void)memset(config, 0, sizeof(*config));

    config->enableMaster                 = kI3C_MasterCapable;
    config->disableTimeout               = false;
    config->hKeep                        = kI3C_MasterHighKeeperNone;
    config->enableOpenDrainStop          = true;
    config->enableOpenDrainHigh          = true;
    config->baudRate_Hz.i2cBaud          = 400000U;
    config->baudRate_Hz.i3cPushPullBaud  = 12500000U;
    config->baudRate_Hz.i3cOpenDrainBaud = 2500000U;
    config->masterDynamicAddress         = 0x0AU;    /* Default master dynamic address. */
    config->slowClock_Hz                 = 1000000U; /* Default slow timer clock 1MHz. */
    config->enableSlave                  = true;
    config->vendorID                     = 0x11BU;
    config->enableRandomPart             = false;
    config->partNumber                   = 0;
    config->dcr                          = 0; /* Generic device. */
    config->bcr = 0; /* BCR[7:6]: device role, I3C slave(2b'00), BCR[5]: SDR Only / SDR and HDR Capable,  SDR and HDR
                        Capable(1b'1), BCR[4]: Bridge Identifier, Not a bridge device(1b'0), BCR[3]: Offline Capable,
                        device is offline capable(1b'1), BCR[2]: IBI Payload, No data byte following(1b'0), BCR[1]: IBI
                        Request Capable, capable(1b'1), BCR[0]: Max Data Speed Limitation, has limitation(1b'1). */
    config->hdrMode             = (uint8_t)kI3C_HDRModeDDR;
    config->nakAllRequest       = false;
    config->ignoreS0S1Error     = false;
    config->offline             = false;
    config->matchSlaveStartStop = false;
    config->maxWriteLength      = 256U;
    config->maxReadLength       = 256U;
}

/*!
 * @brief Initializes the I3C peripheral.
 *
 */
void I3C_Init(I3C_Type *base, const i3c_config_t *config, uint32_t sourceClock_Hz)
{
    uint32_t instance = I3C_GetInstance(base);
    uint32_t configValue;
    uint8_t matchCount;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the clock. */
    CLOCK_EnableClock(kI3cClocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    /* Reset the I3C module */
    RESET_PeripheralReset(kI3cResets[instance]);
#endif

    if ((config->masterDynamicAddress != 0U) && (config->enableMaster == kI3C_MasterOn))
    {
        base->MDYNADDR &= ~I3C_MDYNADDR_DADDR_MASK;
        base->MDYNADDR |= I3C_MDYNADDR_DADDR(config->masterDynamicAddress) | I3C_MDYNADDR_DAVALID_MASK;
    }

    base->MCONFIG = I3C_MCONFIG_MSTENA(config->enableMaster) | I3C_MCONFIG_DISTO(config->disableTimeout) |
                    I3C_MCONFIG_HKEEP(config->hKeep) | I3C_MCONFIG_ODSTOP(config->enableOpenDrainStop) |
                    I3C_MCONFIG_ODHPP(config->enableOpenDrainHigh);

    I3C_MasterSetWatermarks(base, kI3C_TxTriggerUntilOneLessThanFull, kI3C_RxTriggerOnNotEmpty, true, true);

    I3C_MasterSetBaudRate(base, &config->baudRate_Hz, sourceClock_Hz);

    /* Caculate bus available condition match value for current slow clock, count value provides 1us.*/
    matchCount = (uint8_t)(config->slowClock_Hz / 1000000UL);

    configValue = base->SCONFIG;

    configValue &= ~(I3C_SCONFIG_SADDR_MASK | I3C_SCONFIG_BAMATCH_MASK | I3C_SCONFIG_OFFLINE_MASK |
                     I3C_SCONFIG_IDRAND_MASK | I3C_SCONFIG_DDROK_MASK | I3C_SCONFIG_S0IGNORE_MASK |
                     I3C_SCONFIG_MATCHSS_MASK | I3C_SCONFIG_NACK_MASK | I3C_SCONFIG_SLVENA_MASK);
    configValue |= I3C_SCONFIG_SADDR(config->staticAddr) | I3C_SCONFIG_BAMATCH(matchCount) |
                   I3C_SCONFIG_OFFLINE(config->offline) | I3C_SCONFIG_IDRAND(config->enableRandomPart) |
                   I3C_SCONFIG_DDROK((0U != (config->hdrMode & (uint8_t)kI3C_HDRModeDDR)) ? 1U : 0U) |
                   I3C_SCONFIG_S0IGNORE(config->ignoreS0S1Error) | I3C_SCONFIG_MATCHSS(config->matchSlaveStartStop) |
                   I3C_SCONFIG_NACK(config->nakAllRequest) | I3C_SCONFIG_SLVENA(config->enableSlave);

    base->SVENDORID &= ~I3C_SVENDORID_VID_MASK;
    base->SVENDORID |= I3C_SVENDORID_VID(config->vendorID);

    if (!config->enableRandomPart)
    {
        base->SIDPARTNO = config->partNumber;
    }

    base->SIDEXT &= ~(I3C_SIDEXT_BCR_MASK | I3C_SIDEXT_DCR_MASK);
    base->SIDEXT |= I3C_SIDEXT_BCR(config->bcr) | I3C_SIDEXT_DCR(config->dcr);

    base->SMAXLIMITS &= ~(I3C_SMAXLIMITS_MAXRD_MASK | I3C_SMAXLIMITS_MAXWR_MASK);
    base->SMAXLIMITS |= (I3C_SMAXLIMITS_MAXRD(config->maxReadLength) | I3C_SMAXLIMITS_MAXWR(config->maxWriteLength));

    base->SCONFIG = configValue;
}

/*!
 * brief Provides a default configuration for the I3C master peripheral.
 *
 * This function provides the following default configuration for the I3C master peripheral:
 * code
 *  masterConfig->enableMaster            = kI3C_MasterOn;
 *  masterConfig->disableTimeout          = false;
 *  masterConfig->hKeep                   = kI3C_MasterHighKeeperNone;
 *  masterConfig->enableOpenDrainStop     = true;
 *  masterConfig->enableOpenDrainHigh     = true;
 *  masterConfig->baudRate_Hz             = 100000U;
 *  masterConfig->busType                 = kI3C_TypeI2C;
 * endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the master driver with I3C_MasterInit().
 *
 * param[out] masterConfig User provided configuration structure for default values. Refer to #i3c_master_config_t.
 */
void I3C_MasterGetDefaultConfig(i3c_master_config_t *masterConfig)
{
    masterConfig->enableMaster                 = kI3C_MasterOn;
    masterConfig->disableTimeout               = false;
    masterConfig->hKeep                        = kI3C_MasterHighKeeperNone;
    masterConfig->enableOpenDrainStop          = true;
    masterConfig->enableOpenDrainHigh          = true;
    masterConfig->baudRate_Hz.i2cBaud          = 400000U;
    masterConfig->baudRate_Hz.i3cPushPullBaud  = 12500000U;
    masterConfig->baudRate_Hz.i3cOpenDrainBaud = 2500000U;
}

/*!
 * brief Initializes the I3C master peripheral.
 *
 * This function enables the peripheral clock and initializes the I3C master peripheral as described by the user
 * provided configuration. A software reset is performed prior to configuration.
 *
 * param base The I3C peripheral base address.
 * param masterConfig User provided peripheral configuration. Use I3C_MasterGetDefaultConfig() to get a set of
 * defaults that you can override.
 * param sourceClock_Hz Frequency in Hertz of the I3C functional clock. Used to calculate the baud rate divisors,
 *      filter widths, and timeout periods.
 */
void I3C_MasterInit(I3C_Type *base, const i3c_master_config_t *masterConfig, uint32_t sourceClock_Hz)
{
    uint32_t instance = I3C_GetInstance(base);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the clock. */
    CLOCK_EnableClock(kI3cClocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    /* Reset the I3C module */
    RESET_PeripheralReset(kI3cResets[instance]);
#endif
    base->MCONFIG = I3C_MCONFIG_MSTENA(masterConfig->enableMaster) | I3C_MCONFIG_DISTO(masterConfig->disableTimeout) |
                    I3C_MCONFIG_HKEEP(masterConfig->hKeep) | I3C_MCONFIG_ODSTOP(masterConfig->enableOpenDrainStop) |
                    I3C_MCONFIG_ODHPP(masterConfig->enableOpenDrainHigh);

    I3C_MasterSetWatermarks(base, kI3C_TxTriggerUntilOneLessThanFull, kI3C_RxTriggerOnNotEmpty, true, true);

    I3C_MasterSetBaudRate(base, &masterConfig->baudRate_Hz, sourceClock_Hz);
}

/*!
 * @brief Gets the I3C master state.
 *
 * @param base The I3C peripheral base address.
 * @return I3C master state.
 */
i3c_master_state_t I3C_MasterGetState(I3C_Type *base)
{
    uint32_t masterState = (base->MSTATUS & I3C_MSTATUS_STATE_MASK) >> I3C_MSTATUS_STATE_SHIFT;
    i3c_master_state_t returnCode;

    switch (masterState)
    {
        case (uint32_t)kI3C_MasterStateIdle:
            returnCode = kI3C_MasterStateIdle;
            break;
        case (uint32_t)kI3C_MasterStateSlvReq:
            returnCode = kI3C_MasterStateSlvReq;
            break;
        case (uint32_t)kI3C_MasterStateMsgSdr:
            returnCode = kI3C_MasterStateMsgSdr;
            break;
        case (uint32_t)kI3C_MasterStateNormAct:
            returnCode = kI3C_MasterStateNormAct;
            break;
        case (uint32_t)kI3C_MasterStateDdr:
            returnCode = kI3C_MasterStateDdr;
            break;
        case (uint32_t)kI3C_MasterStateDaa:
            returnCode = kI3C_MasterStateDaa;
            break;
        case (uint32_t)kI3C_MasterStateIbiAck:
            returnCode = kI3C_MasterStateIbiAck;
            break;
        case (uint32_t)kI3C_MasterStateIbiRcv:
            returnCode = kI3C_MasterStateIbiRcv;
            break;
        default:
            returnCode = kI3C_MasterStateIdle;
            break;
    }

    return returnCode;
}

/*!
 * brief Deinitializes the I3C master peripheral.
 *
 * This function disables the I3C master peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * param base The I3C peripheral base address.
 */
void I3C_MasterDeinit(I3C_Type *base)
{
    uint32_t idx = I3C_GetInstance(base);

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    /* Reset the I3C module */
    RESET_PeripheralReset(kI3cResets[idx]);
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate clock. */
    CLOCK_DisableClock(kI3cClocks[idx]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset handle pointer. */
    s_i3cMasterHandle[idx] = NULL;
}

static uint32_t I3C_CalcErrorRatio(uint32_t curFreq, uint32_t desiredFreq)
{
    if (curFreq > desiredFreq)
    {
        return (curFreq - desiredFreq) * 100UL / desiredFreq;
    }
    else
    {
        return (desiredFreq - curFreq) * 100UL / desiredFreq;
    }
}

/*!
 * brief Sets the I3C bus frequency for master transactions.
 *
 * The I3C master is automatically disabled and re-enabled as necessary to configure the baud
 * rate. Do not call this function during a transfer, or the transfer is aborted.
 *
 * param base The I3C peripheral base address.
 * param baudRate_Hz Pointer to structure of requested bus frequency in Hertz.
 * param sourceClock_Hz I3C functional clock frequency in Hertz.
 */
void I3C_MasterSetBaudRate(I3C_Type *base, const i3c_baudrate_hz_t *baudRate_Hz, uint32_t sourceClock_Hz)
{
    uint32_t div, freq;
    uint32_t divEven, divOdd;
    uint32_t ppBaud, odBaud, i2cBaud;
    uint32_t errRate0, errRate1;
    uint32_t i3cPPBaud_HZ    = baudRate_Hz->i3cPushPullBaud;
    uint32_t i3cPPBaudMax_HZ = i3cPPBaud_HZ / 10U + i3cPPBaud_HZ; /* max is 1.1*i3cPPBaud_HZ */
    uint32_t i3cODBaud_HZ    = baudRate_Hz->i3cOpenDrainBaud;
    uint32_t i3cODBaudMax_HZ = i3cODBaud_HZ / 10U + i3cODBaud_HZ; /* max is 1.1*i3cODBaud_HZ */
    uint32_t i2cBaud_HZ      = baudRate_Hz->i2cBaud;
    uint32_t i3cPPLow_Ns, i3cOdLow_Ns;
    bool isODHigh = (0U != (base->MCONFIG & I3C_MCONFIG_ODHPP_MASK)) ? true : false;

    /* Find out the div to generate target freq */
    freq = sourceClock_Hz / 2UL;
    /* ppFreq = FCLK / 2 / (PPBAUD + 1)), 0 <= PPBAUD <= 15 */
    /* We need PPBAUD generate 12.5MHz or so. */
    div = freq / i3cPPBaud_HZ;
    div = (div == 0UL) ? 1UL : div;
    if (freq / div > i3cPPBaudMax_HZ)
    {
        div++;
    }
    assert(div <= FSL_I3C_PPBAUD_DIV_MAX);
    ppBaud = div - 1UL;
    freq /= div;

    i3cPPLow_Ns = (uint32_t)(NSEC_PER_SEC / (2UL * freq));

    /* We need ODBAUD generate 2.5MHz or so. */
    if (isODHigh)
    {
        /* odFreq = (2*freq) / (ODBAUD + 2), 1 <= ODBAUD <= 255 */
        div = (2UL * freq) / i3cODBaud_HZ;
        div = div < 2UL ? 2UL : div;
        if ((2UL * freq / div) > i3cODBaudMax_HZ)
        {
            div++;
        }
        odBaud = div - 2UL;
        freq   = (2UL * freq) / div;
    }
    else
    {
        /* odFreq = ppFreq / (ODBAUD + 1), 1 <= ODBAUD <= 255 */
        div = freq / i3cODBaud_HZ;
        div = div < 1UL ? 1UL : div;
        if (freq / div > i3cODBaudMax_HZ)
        {
            div++;
        }
        odBaud = div - 1UL;
        freq /= div;
    }

    i3cOdLow_Ns = (odBaud + 1UL) * i3cPPLow_Ns;

    /* i2cFreq = odFreq / (I2CBAUD + 1), 0 <= I2CBAUD <= 7 (I2CBAUD need << 1 in register) */
    /* i2cFreq = NSEC_PER_SEC / (I2CBAUD + 1)*i3cOdLow_Ns */
    divEven  = (sourceClock_Hz / i2cBaud_HZ) / (2UL * (ppBaud + 1UL) * (odBaud + 1UL));
    divEven  = divEven == 0UL ? 1UL : divEven;
    errRate0 = I3C_CalcErrorRatio((uint32_t)(NSEC_PER_SEC / (2UL * divEven * i3cOdLow_Ns)), i2cBaud_HZ);

    divOdd   = ((sourceClock_Hz / i2cBaud_HZ) / ((ppBaud + 1UL) * (odBaud + 1UL) - 1UL)) / 2UL;
    divOdd   = divOdd == 0UL ? 1UL : divOdd;
    errRate1 = I3C_CalcErrorRatio((uint32_t)(NSEC_PER_SEC / ((2UL * divOdd + 1UL) * i3cOdLow_Ns)), i2cBaud_HZ);

    if (errRate0 < FSL_I3C_ERROR_RATE_MAX || errRate1 < FSL_I3C_ERROR_RATE_MAX)
    {
        /* Use this div */
        i2cBaud = errRate0 < errRate1 ? (divEven - 1UL) * 2UL : (divOdd - 1UL) * 2UL + 1UL;
    }
    else
    {
        /* Use div + 1, unless current freq is already lower than desired. */
        i2cBaud = freq / divEven < i2cBaud_HZ ? (divEven - 1UL) * 2UL : divEven * 2UL;
    }

    base->MCONFIG = (base->MCONFIG & ~(I3C_MCONFIG_PPBAUD_MASK | I3C_MCONFIG_PPLOW_MASK | I3C_MCONFIG_ODBAUD_MASK |
                                       I3C_MCONFIG_I2CBAUD_MASK)) |
                    I3C_MCONFIG_PPBAUD(ppBaud) | I3C_MCONFIG_ODBAUD(odBaud) | I3C_MCONFIG_I2CBAUD(i2cBaud);
}

/*!
 * brief Sends a START signal and slave address on the I2C/I3C bus.
 *
 * This function is used to initiate a new master mode transfer. First, the bus state is checked to ensure
 * that another master is not occupying the bus. Then a START signal is transmitted, followed by the
 * 7-bit address specified in the a address parameter. Note that this function does not actually wait
 * until the START and address are successfully sent on the bus before returning.
 *
 * param base The I3C peripheral base address.
 * param type The bus type to use in this transaction.
 * param address 7-bit slave device address, in bits [6:0].
 * param dir Master transfer direction, either #kI3C_Read or #kI3C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * retval #kStatus_Success START signal and address were successfully enqueued in the transmit FIFO.
 * retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 */
status_t I3C_MasterStart(I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir)
{
    i3c_master_state_t masterState = I3C_MasterGetState(base);
    bool checkDdrState             = (type == kI3C_TypeI3CDdr) ? (masterState != kI3C_MasterStateDdr) : true;
    if ((masterState != kI3C_MasterStateIdle) && (masterState != kI3C_MasterStateNormAct) && checkDdrState)
    {
        return kStatus_I3C_Busy;
    }

    return I3C_MasterRepeatedStart(base, type, address, dir);
}

/*!
 * brief Sends a repeated START signal and slave address on the I2C/I3C bus.
 *
 * This function is used to send a Repeated START signal when a transfer is already in progress. Like
 * I3C_MasterStart(), it also sends the specified 7-bit address.
 *
 * note This function exists primarily to maintain compatible APIs between I3C and I2C drivers,
 *      as well as to better document the intent of code that uses these APIs.
 *
 * param base The I3C peripheral base address.
 * param type The bus type to use in this transaction.
 * param address 7-bit slave device address, in bits [6:0].
 * param dir Master transfer direction, either #kI3C_Read or #kI3C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * param rxSize if dir is #kI3C_Read, this assigns bytes to read. Otherwise set to 0.
 * retval #kStatus_Success Repeated START signal and address were successfully enqueued in the transmit FIFO.
 */
status_t I3C_MasterRepeatedStart(I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir)
{
    uint32_t mctrlVal;

    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);

    /* Issue start command. */
    mctrlVal = base->MCTRL;
    mctrlVal &= ~(I3C_MCTRL_TYPE_MASK | I3C_MCTRL_REQUEST_MASK | I3C_MCTRL_DIR_MASK | I3C_MCTRL_ADDR_MASK |
                  I3C_MCTRL_RDTERM_MASK);
    mctrlVal |= I3C_MCTRL_TYPE(type) | I3C_MCTRL_REQUEST(kI3C_RequestEmitStartAddr) | I3C_MCTRL_DIR(dir) |
                I3C_MCTRL_ADDR(address);

    base->MCTRL = mctrlVal;

    return kStatus_Success;
}

/*!
 * brief Sends a repeated START signal and slave address on the I2C/I3C bus, receive size is also specified
 * in the call.
 *
 * This function is used to send a Repeated START signal when a transfer is already in progress. Like
 * I3C_MasterStart(), it also sends the specified 7-bit address. Call this API also configures the read
 * terminate size for the following read transfer. For example, set the rxSize = 2, the following read transfer
 * will be terminated after two bytes of data received. Write transfer will not be affected by the rxSize
 * configuration.
 *
 * note This function exists primarily to maintain compatible APIs between I3C and I2C drivers,
 *      as well as to better document the intent of code that uses these APIs.
 *
 * param base The I3C peripheral base address.
 * param type The bus type to use in this transaction.
 * param address 7-bit slave device address, in bits [6:0].
 * param dir Master transfer direction, either #kI3C_Read or #kI3C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * param rxSize Read terminate size for the followed read transfer, limit to 255 bytes.
 * retval #kStatus_Success Repeated START signal and address were successfully enqueued in the transmit FIFO.
 */
status_t I3C_MasterRepeatedStartWithRxSize(
    I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir, uint8_t rxSize)
{
    uint32_t mctrlVal;

    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);

    /* Issue start command. */
    mctrlVal = base->MCTRL;
    mctrlVal &= ~(I3C_MCTRL_TYPE_MASK | I3C_MCTRL_REQUEST_MASK | I3C_MCTRL_DIR_MASK | I3C_MCTRL_ADDR_MASK |
                  I3C_MCTRL_RDTERM_MASK);
    mctrlVal |= I3C_MCTRL_TYPE(type) | I3C_MCTRL_REQUEST(kI3C_RequestEmitStartAddr) | I3C_MCTRL_DIR(dir) |
                I3C_MCTRL_ADDR(address) | I3C_MCTRL_RDTERM(rxSize);

    base->MCTRL = mctrlVal;

    return kStatus_Success;
}
/*!
 * brief Sends a STOP signal on the I2C/I3C bus.
 *
 * This function does not return until the STOP signal is seen on the bus, or an error occurs.
 *
 * param base The I3C peripheral base address.
 * retval #kStatus_Success The STOP signal was successfully sent on the bus and the transaction terminated.
 * retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_I3C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_I3C_FifoError FIFO under run or overrun.
 * retval #kStatus_I3C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_I3C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t I3C_MasterStop(I3C_Type *base)
{
    return I3C_MasterEmitStop(base, true);
}

/*!
 * brief I3C master emit request.
 *
 * param base The I3C peripheral base address.
 * param masterReq  I3C master request of type #i3c_bus_request_t
 */
void I3C_MasterEmitRequest(I3C_Type *base, i3c_bus_request_t masterReq)
{
    uint32_t mctrlReg = base->MCTRL;
    mctrlReg &= ~I3C_MCTRL_REQUEST_MASK;
    mctrlReg |= I3C_MCTRL_REQUEST(masterReq);

    base->MCTRL = mctrlReg;
}

/*!
 * brief I3C master register IBI rule.
 *
 * param base The I3C peripheral base address.
 * param ibiRule Pointer to ibi rule description of type #i3c_register_ibi_addr_t
 */
void I3C_MasterRegisterIBI(I3C_Type *base, i3c_register_ibi_addr_t *ibiRule)
{
    assert(NULL != ibiRule);
    uint32_t ruleValue = I3C_MIBIRULES_MSB0_MASK;

    for (uint32_t count = 0; count < ARRAY_SIZE(ibiRule->address); count++)
    {
        ruleValue |= ((uint32_t)ibiRule->address[count]) << (count * I3C_MIBIRULES_ADDR1_SHIFT);
    }

    ruleValue &= ~I3C_MIBIRULES_NOBYTE_MASK;

    if (!ibiRule->ibiHasPayload)
    {
        ruleValue |= I3C_MIBIRULES_NOBYTE_MASK;
    }

    base->MIBIRULES = ruleValue;
}

/*!
 * brief I3C master get IBI rule.
 *
 * param base The I3C peripheral base address.
 * param ibiRule Pointer to store the read out ibi rule description.
 */
void I3C_MasterGetIBIRules(I3C_Type *base, i3c_register_ibi_addr_t *ibiRule)
{
    assert(NULL != ibiRule);

    uint32_t ruleValue = base->MIBIRULES;

    for (uint32_t count = 0; count < ARRAY_SIZE(ibiRule->address); count++)
    {
        ibiRule->address[count] =
            (uint8_t)(ruleValue >> (count * I3C_MIBIRULES_ADDR1_SHIFT)) & I3C_MIBIRULES_ADDR0_MASK;
    }

    ibiRule->ibiHasPayload = (0U == (ruleValue & I3C_MIBIRULES_NOBYTE_MASK));
}

/*!
 * brief Performs a polling receive transfer on the I2C/I3C bus.
 *
 * param base  The I3C peripheral base address.
 * param rxBuff The pointer to the data to be transferred.
 * param rxSize The length in bytes of the data to be transferred.
 * param flags Bit mask of options for the transfer. See enumeration #_i3c_master_transfer_flags for available options.
 * retval #kStatus_Success Data was received successfully.
 * retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_I3C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_I3C_FifoError FIFO under run or overrun.
 * retval #kStatus_I3C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_I3C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t I3C_MasterReceive(I3C_Type *base, void *rxBuff, size_t rxSize, uint32_t flags)
{
    status_t result = kStatus_Success;
    uint32_t status;
    bool completed = false;
    uint8_t *buf;

    assert(NULL != rxBuff);

    /* Handle empty read. */
    if (rxSize == 0UL)
    {
        return kStatus_Success;
    }

#if I3C_RETRY_TIMES
    uint32_t waitTimes = I3C_RETRY_TIMES;
#endif

    /* Receive data */
    buf = (uint8_t *)rxBuff;

    while ((rxSize != 0UL) || !completed)
    {
#if I3C_RETRY_TIMES
        if (--waitTimes == 0)
        {
            return kStatus_I3C_Timeout;
        }
#endif
        /* Check for errors. */
        result = I3C_MasterCheckAndClearError(base, I3C_MasterGetErrorStatusFlags(base));
        if (kStatus_Success != result)
        {
            return result;
        }

        /* Check complete flag */
        if (!completed)
        {
            status = I3C_MasterGetStatusFlags(base) & (uint32_t)kI3C_MasterCompleteFlag;
            if (0UL != status)
            {
                completed = true;
                /* Clear complete flag */
                I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterCompleteFlag);
                /* Send stop if needed */
                if ((flags & (uint32_t)kI3C_TransferNoStopFlag) == 0UL)
                {
                    if (I3C_MasterGetState(base) == kI3C_MasterStateDdr)
                    {
                        I3C_MasterEmitRequest(base, kI3C_RequestForceExit);
                    }
                    else
                    {
                        result = I3C_MasterEmitStop(base, false);
                    }
                    if (kStatus_Success != result)
                    {
                        return result;
                    }
                }
            }
        }

        /* Check RX data */
        if ((0UL != rxSize) && (0UL != (base->MDATACTRL & I3C_MDATACTRL_RXCOUNT_MASK)))
        {
            *buf++ = (uint8_t)(base->MRDATAB & I3C_MRDATAB_VALUE_MASK);
            rxSize--;
            if (rxSize == 1U)
            {
                base->MCTRL |= I3C_MCTRL_RDTERM(1U);
            }
        }
    }

    /* Wait idle if stop is sent. */
    if ((flags & (uint32_t)kI3C_TransferNoStopFlag) == 0UL)
    {
#if I3C_RETRY_TIMES
        while ((I3C_MasterGetState(base) != kI3C_MasterStateIdle) && --waitTimes)
#else
        while (I3C_MasterGetState(base) != kI3C_MasterStateIdle)
#endif
        {
        }
    }
    return result;
}

/*!
 * brief Performs a polling send transfer on the I2C/I3C bus.
 *
 * Sends up to a txSize number of bytes to the previously addressed slave device. The slave may
 * reply with a NAK to any byte in order to terminate the transfer early. If this happens, this
 * function returns #kStatus_I3C_Nak.
 *
 * param base  The I3C peripheral base address.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * param flags Bit mask of options for the transfer. See enumeration #_i3c_master_transfer_flags for available options.
 * retval #kStatus_Success Data was sent successfully.
 * retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_I3C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_I3C_FifoError FIFO under run or over run.
 * retval #kStatus_I3C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_I3C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t I3C_MasterSend(I3C_Type *base, const void *txBuff, size_t txSize, uint32_t flags)
{
    i3c_puint8_to_u32_t buf;
    buf.cpuint8     = (const uint8_t *)((const void *)txBuff);
    status_t result = kStatus_Success;
    bool enableWord = ((flags & (uint32_t)kI3C_TransferWordsFlag) == (uint32_t)kI3C_TransferWordsFlag) ? true : false;
    uint8_t byteCounts = enableWord ? 2U : 1U;

    assert(NULL != txBuff);
    if (enableWord)
    {
        assert(txSize % 2UL == 0UL);
    }

    /* Send data buffer */
    while (0UL != txSize)
    {
        /* Wait until there is room in the fifo. This also checks for errors. */
        result = I3C_MasterWaitForTxReady(base, byteCounts);
        if (kStatus_Success != result)
        {
            return result;
        }

        /* Write byte into I3C master data register. */
        if (txSize > byteCounts)
        {
            if (enableWord)
            {
                base->MWDATAH = (uint32_t)buf.cpuint8[1] << 8UL | (uint32_t)buf.cpuint8[0];
            }
            else
            {
                base->MWDATAB = *buf.cpuint8;
            }
        }
        else
        {
            if (enableWord)
            {
                base->MWDATAHE = (uint32_t)buf.cpuint8[1] << 8UL | (uint32_t)buf.cpuint8[0];
            }
            else
            {
                base->MWDATABE = *buf.cpuint8;
            }
        }

        buf.u32 = buf.u32 + byteCounts;
        txSize  = txSize - byteCounts;
    }

    result = I3C_MasterWaitForComplete(base, false);
    if ((result == kStatus_Success) && ((flags & (uint32_t)kI3C_TransferNoStopFlag) == 0UL))
    {
        if (I3C_MasterGetState(base) == kI3C_MasterStateDdr)
        {
            I3C_MasterEmitRequest(base, kI3C_RequestForceExit);
        }
        else
        {
            result = I3C_MasterEmitStop(base, true);
        }
    }

    return result;
}
/*!
 * brief Performs a DAA in the i3c bus
 *
 * param base The I3C peripheral base address.
 * param addressList The pointer for address list which is used to do DAA.
 * param count The address count in the address list.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t I3C_MasterProcessDAA(I3C_Type *base, uint8_t *addressList, uint32_t count)
{
    status_t result = kStatus_Success;
    uint32_t status;
    uint32_t errStatus;
    size_t rxCount;
    uint8_t rxBuffer[8] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    uint8_t rxSize      = 0;
    uint32_t devCount   = 0;

    /* Return an error if the bus is already in use not by us. */
    result = I3C_CheckForBusyBus(base);
    if (kStatus_Success != result)
    {
        return result;
    }

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);

    /* Disable I3C IRQ sources while we configure stuff. */
    uint32_t enabledInts = I3C_MasterGetEnabledInterrupts(base);
    I3C_MasterDisableInterrupts(base, enabledInts);

    /* Emit process DAA */
    I3C_MasterEmitRequest(base, kI3C_RequestProcessDAA);

    do
    {
        do
        {
            status = I3C_MasterGetStatusFlags(base);
            I3C_MasterGetFifoCounts(base, &rxCount, NULL);

            /* Check for error flags. */
            errStatus = I3C_MasterGetErrorStatusFlags(base);
            result    = I3C_MasterCheckAndClearError(base, errStatus);
            if (kStatus_Success != result)
            {
                return result;
            }

            if ((0UL != (status & (uint32_t)kI3C_MasterRxReadyFlag)) && (rxCount != 0U))
            {
                rxBuffer[rxSize++] = (uint8_t)(base->MRDATAB & I3C_MRDATAB_VALUE_MASK);
            }
        } while ((status & (uint32_t)kI3C_MasterControlDoneFlag) != (uint32_t)kI3C_MasterControlDoneFlag);

        I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterControlDoneFlag);

        if ((I3C_MasterGetState(base) == kI3C_MasterStateDaa) &&
            (0UL != (I3C_MasterGetStatusFlags(base) & (uint32_t)kI3C_MasterBetweenFlag)))
        {
            rxSize = 0;
            if ((devCount > (count - 1UL)) || ((devCount + 1UL) > I3C_MAX_DEVCNT))
            {
                return kStatus_I3C_SlaveCountExceed;
            }

            devList[devCount].dynamicAddr = *addressList++;
            devList[devCount].vendorID    = (((uint16_t)rxBuffer[0] << 8U | (uint16_t)rxBuffer[1]) & 0xFFFEU) >> 1U;
            devList[devCount].partNumber  = ((uint32_t)rxBuffer[2] << 24U | (uint32_t)rxBuffer[3] << 16U |
                                            (uint32_t)rxBuffer[4] << 8U | (uint32_t)rxBuffer[5]);
            devList[devCount].bcr         = rxBuffer[6];
            devList[devCount].dcr         = rxBuffer[7];
            base->MWDATAB                 = devList[devCount].dynamicAddr;
            /* Emit process DAA again. */
            I3C_MasterEmitRequest(base, kI3C_RequestProcessDAA);
            devCount++;
        }
    } while ((status & (uint32_t)kI3C_MasterCompleteFlag) != (uint32_t)kI3C_MasterCompleteFlag);

    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);

    /* Enable I3C IRQ sources while we configure stuff. */
    I3C_MasterEnableInterrupts(base, enabledInts);

    return result;
}

/*!
 * brief Performs a master polling transfer on the I2C/I3C bus.
 *
 * note The API does not return until the transfer succeeds or fails due
 * to error happens during transfer.
 *
 * param base The I3C peripheral base address.
 * param transfer Pointer to the transfer structure.
 * retval #kStatus_Success Data was received successfully.
 * retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * retval #kStatus_I3C_Nak The slave device sent a NAK in response to a byte.
 * retval #kStatus_I3C_FifoError FIFO under run or overrun.
 * retval #kStatus_I3C_ArbitrationLost Arbitration lost error.
 * retval #kStatus_I3C_PinLowTimeout SCL or SDA were held low longer than the timeout.
 */
status_t I3C_MasterTransferBlocking(I3C_Type *base, i3c_master_transfer_t *transfer)
{
    assert(NULL != transfer);
    assert(transfer->subaddressSize <= sizeof(transfer->subaddress));

    status_t result                = kStatus_Success;
    i3c_direction_t direction      = transfer->direction;
    i3c_master_state_t masterState = I3C_MasterGetState(base);
    bool checkDdrState             = false;

    /* Return an error if the bus is already in use not by us. */
    checkDdrState = (transfer->busType == kI3C_TypeI3CDdr) ? (masterState != kI3C_MasterStateDdr) : true;

    if ((masterState != kI3C_MasterStateIdle) && (masterState != kI3C_MasterStateNormAct) && checkDdrState)
    {
        return kStatus_I3C_Busy;
    }

    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Reset fifos. These flags clear automatically. */
    base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

    /* Disable I3C IRQ sources while we configure stuff. */
    I3C_MasterDisableInterrupts(base, (uint32_t)kMasterIrqFlags);

    if (transfer->busType != kI3C_TypeI3CDdr)
    {
        direction = (0UL != transfer->subaddressSize) ? kI3C_Write : transfer->direction;
    }

    if (0UL == (transfer->flags & (uint32_t)kI3C_TransferNoStartFlag))
    {
        result = I3C_MasterStart(base, transfer->busType, transfer->slaveAddress, direction);
        /* Wait tx fifo empty. */
        size_t txCount = 0xFFUL;

        while (txCount != 0U)
        {
            I3C_MasterGetFifoCounts(base, NULL, &txCount);
        }

        /* Check if device request wins arbitration. */
        if (0UL != (I3C_MasterGetStatusFlags(base) & (uint32_t)kI3C_MasterArbitrationWonFlag))
        {
            /* Clear all flags. */
            I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
            /* Enable I3C IRQ sources. */
            I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);
            return kStatus_I3C_IBIWon;
        }
    }

    /* Subaddress, MSB first. */
    if (0U != transfer->subaddressSize)
    {
        uint32_t subaddressRemaining = transfer->subaddressSize;
        while (0UL != subaddressRemaining--)
        {
            uint8_t subaddressByte = (uint8_t)((transfer->subaddress >> (8UL * subaddressRemaining)) & 0xFFUL);

            result = I3C_MasterWaitForTxReady(base, 1U);

            if ((0UL == subaddressRemaining) && ((transfer->direction == kI3C_Read) || (0UL == transfer->dataSize)) &&
                (transfer->busType != kI3C_TypeI3CDdr))
            {
                base->MWDATABE = subaddressByte;
                result         = I3C_MasterWaitForComplete(base, false);
                if (kStatus_Success != result)
                {
                    if (result == kStatus_I3C_Nak)
                    {
                        (void)I3C_MasterEmitStop(base, true);
                    }
                    /* Clear all flags. */
                    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
                    /* Enable I3C IRQ sources. */
                    I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);
                    return result;
                }
            }
            else
            {
                base->MWDATAB = subaddressByte;
            }
        }
        /* Need to send repeated start if switching directions to read. */
        if ((transfer->busType != kI3C_TypeI3CDdr) && (0UL != transfer->dataSize) && (transfer->direction == kI3C_Read))
        {
            result = I3C_MasterRepeatedStart(base, transfer->busType, transfer->slaveAddress, kI3C_Read);
            if (kStatus_Success != result)
            {
                /* Clear all flags. */
                I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
                /* Enable I3C IRQ sources. */
                I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);
                return result;
            }
        }
    }

    /* Transmit data. */
    if ((transfer->direction == kI3C_Write) && (transfer->dataSize > 0UL))
    {
        /* Send Data. */
        result = I3C_MasterSend(base, transfer->data, transfer->dataSize, transfer->flags);
    }
    /* Receive Data. */
    else if ((transfer->direction == kI3C_Read) && (transfer->dataSize > 0UL))
    {
        if (transfer->dataSize == 1U)
        {
            base->MCTRL |= I3C_MCTRL_RDTERM(1U);
        }
        result = I3C_MasterReceive(base, transfer->data, transfer->dataSize, transfer->flags);
    }
    else
    {
        if ((transfer->flags & (uint32_t)kI3C_TransferNoStopFlag) == 0UL)
        {
            result = I3C_MasterEmitStop(base, true);
        }
    }

    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Enable I3C IRQ sources. */
    I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);

    return result;
}

/*!
 * brief Creates a new handle for the I3C master non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_MasterTransferAbort() API shall be called.
 *
 *
 * note The function also enables the NVIC IRQ for the input I3C. Need to notice
 * that on some SoCs the I3C IRQ is connected to INTMUX, in this case user needs to
 * enable the associated INTMUX IRQ in application.
 *
 * param base The I3C peripheral base address.
 * param[out] handle Pointer to the I3C master driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void I3C_MasterTransferCreateHandle(I3C_Type *base,
                                    i3c_master_handle_t *handle,
                                    const i3c_master_transfer_callback_t *callback,
                                    void *userData)
{
    uint32_t instance;

    assert(NULL != handle);

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I3C_GetInstance(base);

    /* Save base and instance. */
    handle->callback = *callback;
    handle->userData = userData;

    /* Save this handle for IRQ use. */
    s_i3cMasterHandle[instance] = handle;

    /* Set irq handler. */
    s_i3cMasterIsr = I3C_MasterTransferHandleIRQ;

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Reset fifos. These flags clear automatically. */
    base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

    /* Enable NVIC IRQ, this only enables the IRQ directly connected to the NVIC.
     In some cases the I3C IRQ is configured through INTMUX, user needs to enable
     INTMUX IRQ in application code. */
    (void)EnableIRQ(kI3cIrqs[instance]);

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);
}

static status_t I3C_RunTransferStateMachine(I3C_Type *base, i3c_master_handle_t *handle, bool *isDone)
{
    uint32_t status;
    uint32_t errStatus;
    status_t result = kStatus_Success;
    i3c_master_transfer_t *xfer;
    size_t txCount;
    size_t rxCount;
    size_t txFifoSize =
        2UL << ((base->SCAPABILITIES & I3C_SCAPABILITIES_FIFOTX_MASK) >> I3C_SCAPABILITIES_FIFOTX_SHIFT);
    bool state_complete = false;
    i3c_puint8_to_u32_t dataBuff;

    /* Set default isDone return value. */
    *isDone = false;

    /* Check for errors. */
    status = (uint32_t)I3C_MasterGetPendingInterrupts(base);
    I3C_MasterClearStatusFlags(base, status);

    i3c_master_state_t masterState = I3C_MasterGetState(base);
    errStatus                      = I3C_MasterGetErrorStatusFlags(base);
    result                         = I3C_MasterCheckAndClearError(base, errStatus);
    if (kStatus_Success != result)
    {
        return result;
    }

    if (0UL != (status & (uint32_t)kI3C_MasterSlave2MasterFlag))
    {
        if (handle->callback.slave2Master != NULL)
        {
            handle->callback.slave2Master(base, handle->userData);
        }
    }

    if ((0UL != (status & (uint32_t)kI3C_MasterSlaveStartFlag)) && (handle->transfer.busType != kI3C_TypeI2C))
    {
        handle->state = (uint8_t)kSlaveStartState;
    }

    if ((masterState == kI3C_MasterStateIbiRcv) || (masterState == kI3C_MasterStateIbiAck))
    {
        handle->state = (uint8_t)kIBIWonState;
    }

    if (handle->state == (uint8_t)kIdleState)
    {
        return result;
    }

    /* Get pointer to private data. */
    xfer = &handle->transfer;

    /* Get fifo counts and compute room in tx fifo. */
    I3C_MasterGetFifoCounts(base, &rxCount, &txCount);
    txCount = txFifoSize - txCount;

    while (!state_complete)
    {
        /* Execute the state. */
        switch (handle->state)
        {
            case (uint8_t)kSlaveStartState:
                /* Emit start + 0x7E */
                I3C_MasterEmitRequest(base, kI3C_RequestAutoIbi);
                handle->state  = (uint8_t)kIBIWonState;
                state_complete = true;
                break;

            case (uint8_t)kIBIWonState:
                if (masterState == kI3C_MasterStateIbiAck)
                {
                    handle->ibiType = I3C_GetIBIType(base);
                    if (handle->callback.ibiCallback != NULL)
                    {
                        handle->callback.ibiCallback(base, handle, handle->ibiType, kI3C_IbiAckNackPending);
                    }
                    else
                    {
                        I3C_MasterEmitIBIResponse(base, kI3C_IbiRespNack);
                    }
                }

                /* Make sure there is data in the rx fifo. */
                if (0UL != rxCount)
                {
                    if ((handle->ibiBuff == NULL) && (handle->callback.ibiCallback != NULL))
                    {
                        handle->callback.ibiCallback(base, handle, kI3C_IbiNormal, kI3C_IbiDataBuffNeed);
                    }
                    uint8_t tempData = (uint8_t)base->MRDATAB;
                    if (handle->ibiBuff != NULL)
                    {
                        handle->ibiBuff[handle->ibiPayloadSize++] = tempData;
                    }
                    rxCount--;
                    break;
                }
                else if (0UL != (status & (uint32_t)kI3C_MasterCompleteFlag))
                {
                    handle->ibiType    = I3C_GetIBIType(base);
                    handle->ibiAddress = I3C_GetIBIAddress(base);
                    state_complete     = true;
                    result             = kStatus_I3C_IBIWon;
                }
                else
                {
                    state_complete = true;
                }
                break;

            case (uint8_t)kSendCommandState:
            {
                I3C_MasterEnableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);
                /* Make sure there is room in the tx fifo for the next command. */
                if (0UL == txCount--)
                {
                    state_complete = true;
                    break;
                }
                if (xfer->subaddressSize > 1U)
                {
                    xfer->subaddressSize--;
                    base->MWDATAB = (uint8_t)((xfer->subaddress) >> (8U * xfer->subaddressSize));
                }
                else if (xfer->subaddressSize == 1U)
                {
                    xfer->subaddressSize--;

                    if ((xfer->direction == kI3C_Read) || (0UL == xfer->dataSize))
                    {
                        base->MWDATABE = (uint8_t)((xfer->subaddress) >> (8U * xfer->subaddressSize));
                        handle->state  = (uint8_t)kWaitForCompletionState;
                    }
                    else
                    {
                        /* Next state, receive data begin. */
                        handle->state = (uint8_t)kTransferDataState;
                        base->MWDATAB = (uint8_t)((xfer->subaddress) >> (8U * xfer->subaddressSize));
                    }

                    if ((xfer->busType != kI3C_TypeI3CDdr) && (xfer->direction == kI3C_Read))
                    {
                        handle->state = (uint8_t)kWaitRepeatedStartCompleteState;
                    }
                }
                else
                {
                    /* Eliminate misra 15.7*/
                }
                break;
            }

            case (uint8_t)kWaitRepeatedStartCompleteState:
                /* We stay in this state until the master complete. */
                if (0UL != (status & (uint32_t)kI3C_MasterCompleteFlag))
                {
                    handle->state = (uint8_t)kTransferDataState;
                    I3C_MasterDisableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);

                    if (handle->remainingBytes < 256U)
                    {
                        handle->isReadTerm = true;
                        result = I3C_MasterRepeatedStartWithRxSize(base, xfer->busType, xfer->slaveAddress, kI3C_Read,
                                                                   (uint8_t)handle->remainingBytes);
                    }
                    else
                    {
                        result = I3C_MasterRepeatedStart(base, xfer->busType, xfer->slaveAddress, kI3C_Read);
                    }
                }

                state_complete = true;
                break;

            case (uint8_t)kTransferDataState:

                if (xfer->direction == kI3C_Write)
                {
                    /* Make sure there is room in the tx fifo. */
                    if (0UL == txCount--)
                    {
                        state_complete = true;
                        break;
                    }

                    /* Put byte to send in fifo. */
                    dataBuff.puint8 = (uint8_t *)xfer->data;
                    if (xfer->dataSize > 1U)
                    {
                        base->MWDATAB = *dataBuff.puint8;
                    }
                    else
                    {
                        base->MWDATABE = *dataBuff.puint8;
                    }
                    dataBuff.u32 = dataBuff.u32 + 1U;
                    xfer->dataSize--;
                    xfer->data = (void *)(dataBuff.puint8);

                    /* Move to stop when the transfer is done. */
                    if (--handle->remainingBytes == 0UL)
                    {
                        handle->state = (uint8_t)kWaitForCompletionState;
                    }
                }
                else
                {
                    /* Make sure there is data in the rx fifo. */
                    if (0UL == rxCount--)
                    {
                        state_complete = true;
                        break;
                    }

                    /* Read byte from fifo. */
                    dataBuff.puint8  = (uint8_t *)xfer->data;
                    *dataBuff.puint8 = (uint8_t)base->MRDATAB;
                    dataBuff.u32     = dataBuff.u32 + 1U;
                    xfer->data       = (void *)(dataBuff.puint8);

                    /* Move to stop when the transfer is done. */
                    if (--handle->remainingBytes == 0UL)
                    {
                        handle->isReadTerm = false;
                        handle->state      = (uint8_t)kWaitForCompletionState;
                    }

                    if (!handle->isReadTerm && (handle->remainingBytes == 1UL))
                    {
                        base->MCTRL |= I3C_MCTRL_RDTERM(1UL);
                    }
                }

                break;

            case (uint8_t)kWaitForCompletionState:
                /* We stay in this state until the maste complete. */
                if (0UL != (status & (uint32_t)kI3C_MasterCompleteFlag))
                {
                    handle->state = (uint8_t)kStopState;
                }
                else
                {
                    state_complete = true;
                }

                break;

            case (uint8_t)kStopState:
                /* Only issue a stop transition if the caller requested it. */
                if (0UL == (xfer->flags & (uint32_t)kI3C_TransferNoStopFlag))
                {
                    /* Make sure there is room in the tx fifo for the stop command. */
                    if (0UL == txCount--)
                    {
                        state_complete = true;
                        break;
                    }
                    if (xfer->busType == kI3C_TypeI3CDdr)
                    {
                        I3C_MasterEmitRequest(base, kI3C_RequestForceExit);
                    }
                    else
                    {
                        (void)I3C_MasterEmitStop(base, false);
                    }
                }
                *isDone        = true;
                state_complete = true;
                break;

            default:
                assert(false);
                break;
        }
    }
    return result;
}

static status_t I3C_InitTransferStateMachine(I3C_Type *base, i3c_master_handle_t *handle)
{
    i3c_master_transfer_t *xfer = &handle->transfer;
    status_t result             = kStatus_Success;
    i3c_direction_t direction   = xfer->direction;

    if (xfer->busType != kI3C_TypeI3CDdr)
    {
        direction = (0UL != xfer->subaddressSize) ? kI3C_Write : xfer->direction;
    }

    /* Handle no start option. */
    if (0U != (xfer->flags & (uint32_t)kI3C_TransferNoStartFlag))
    {
        /* No need to send start flag, directly go to send command or data */
        if (xfer->subaddressSize > 0UL)
        {
            handle->state = (uint8_t)kSendCommandState;
        }
        else
        {
            if (direction == kI3C_Write)
            {
                /* Next state, send data. */
                handle->state = (uint8_t)kTransferDataState;
            }
            else
            {
                /* Only support write with no stop signal. */
                return kStatus_InvalidArgument;
            }
        }
        I3C_MasterTransferHandleIRQ(base, handle);
        return result;
    }
    /* If repeated start is requested, send repeated start. */
    else if (0U != (xfer->flags & (uint32_t)kI3C_TransferRepeatedStartFlag))
    {
        result = I3C_MasterRepeatedStart(base, xfer->busType, xfer->slaveAddress, direction);
    }
    else /* For normal transfer, send start. */
    {
        result = I3C_MasterStart(base, xfer->busType, xfer->slaveAddress, direction);
    }

    if (xfer->subaddressSize > 0U)
    {
        handle->state = (uint8_t)kSendCommandState;
    }
    else
    {
        handle->state = (uint8_t)kTransferDataState;
    }

    if ((handle->remainingBytes < 256U) && (direction == kI3C_Read))
    {
        handle->isReadTerm = true;
        base->MCTRL |= I3C_MCTRL_RDTERM(handle->remainingBytes);
    }

    return result;
}

/*!
 * brief Performs a non-blocking transaction on the I2C/I3C bus.
 *
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C master driver handle.
 * param transfer The pointer to the transfer descriptor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t I3C_MasterTransferNonBlocking(I3C_Type *base, i3c_master_handle_t *handle, i3c_master_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);
    assert(transfer->subaddressSize <= sizeof(transfer->subaddress));
    i3c_master_state_t masterState = I3C_MasterGetState(base);
    bool checkDdrState             = false;

    /* Return busy if another transaction is in progress. */
    if (handle->state != (uint8_t)kIdleState)
    {
        return kStatus_I3C_Busy;
    }

    /* Return an error if the bus is already in use not by us. */
    checkDdrState = (transfer->busType == kI3C_TypeI3CDdr) ? (masterState != kI3C_MasterStateDdr) : true;
    if ((masterState != kI3C_MasterStateIdle) && (masterState != kI3C_MasterStateNormAct) && checkDdrState)
    {
        return kStatus_I3C_Busy;
    }

    /* Disable I3C IRQ sources while we configure stuff. */
    I3C_MasterDisableInterrupts(base, (uint32_t)kMasterIrqFlags);

    /* Save transfer into handle. */
    handle->transfer       = *transfer;
    handle->remainingBytes = transfer->dataSize;

    /* Configure IBI response type. */
    base->MCTRL &= ~I3C_MCTRL_IBIRESP_MASK;
    base->MCTRL |= I3C_MCTRL_IBIRESP(transfer->ibiResponse);

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Reset fifos. These flags clear automatically. */
    base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

    /* Generate commands to send. */
    (void)I3C_InitTransferStateMachine(base, handle);

    /* Enable I3C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
    I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);

    if (transfer->direction == kI3C_Write)
    {
        I3C_MasterEnableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);
    }

    return kStatus_Success;
}

/*!
 * brief Returns number of bytes transferred so far.
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C master driver handle.
 * param[out] count Number of bytes transferred so far by the non-blocking transaction.
 * retval #kStatus_Success
 * retval #kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t I3C_MasterTransferGetCount(I3C_Type *base, i3c_master_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state == (uint8_t)kIdleState)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    uint8_t state;
    uint32_t remainingBytes;
    uint32_t dataSize;

    /* Cache some fields with IRQs disabled. This ensures all field values */
    /* are synchronized with each other during an ongoing transfer. */
    uint32_t irqs = I3C_MasterGetEnabledInterrupts(base);
    I3C_MasterDisableInterrupts(base, irqs);
    state          = handle->state;
    remainingBytes = handle->remainingBytes;
    dataSize       = handle->transfer.dataSize;
    I3C_MasterEnableInterrupts(base, irqs);

    /* Get transfer count based on current transfer state. */
    switch (state)
    {
        case (uint8_t)kIdleState:
        case (uint8_t)kSendCommandState:
            *count = 0;
            break;

        case (uint8_t)kTransferDataState:
            *count = dataSize - remainingBytes;
            break;

        case (uint8_t)kStopState:
        case (uint8_t)kWaitForCompletionState:
        default:
            *count = dataSize;
            break;
    }

    return kStatus_Success;
}

/*!
 * brief Terminates a non-blocking I3C master transmission early.
 *
 * note It is not safe to call this function from an IRQ handler that has a higher priority than the
 *      I3C peripheral's IRQ priority.
 *
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C master driver handle.
 * retval #kStatus_Success A transaction was successfully aborted.
 * retval #kStatus_I3C_Idle There is not a non-blocking transaction currently in progress.
 */
void I3C_MasterTransferAbort(I3C_Type *base, i3c_master_handle_t *handle)
{
    if (handle->state != (uint8_t)kIdleState)
    {
        /* Disable internal IRQ enables. */
        I3C_MasterDisableInterrupts(base, (uint32_t)kMasterIrqFlags);

        /* Reset fifos. These flags clear automatically. */
        base->MDATACTRL |= I3C_MDATACTRL_FLUSHTB_MASK | I3C_MDATACTRL_FLUSHFB_MASK;

        /* Send a stop command to finalize the transfer. */
        (void)I3C_MasterStop(base);

        /* Reset handle. */
        handle->state = (uint8_t)kIdleState;
    }
}

/*!
 * brief Reusable routine to handle master interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  nonblocking API's interrupt handler routines to add special functionality.
 * param base The I3C peripheral base address.
 * param handle Pointer to the I3C master driver handle.
 */
void I3C_MasterTransferHandleIRQ(I3C_Type *base, i3c_master_handle_t *handle)
{
    bool isDone;
    status_t result;

    /* Don't do anything if we don't have a valid handle. */
    if (NULL == handle)
    {
        return;
    }

    result = I3C_RunTransferStateMachine(base, handle, &isDone);

    if (handle->state == (uint8_t)kIdleState)
    {
        I3C_MasterDisableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);
        return;
    }

    if (isDone || (result != kStatus_Success))
    {
        /* XXX need to handle data that may be in rx fifo below watermark level? */

        /* XXX handle error, terminate xfer */
        if ((result == kStatus_I3C_Nak) || (result == kStatus_I3C_IBIWon))
        {
            (void)I3C_MasterEmitStop(base, false);
        }

        /* Disable internal IRQ enables. */
        I3C_MasterDisableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);

        /* Set handle to idle state. */
        handle->state = (uint8_t)kIdleState;

        /* Invoke IBI user callback. */
        if ((result == kStatus_I3C_IBIWon) && (handle->callback.ibiCallback != NULL))
        {
            handle->callback.ibiCallback(base, handle, handle->ibiType, kI3C_IbiReady);
            handle->ibiPayloadSize = 0;
        }

        /* Invoke callback. */
        if (NULL != handle->callback.transferComplete)
        {
            handle->callback.transferComplete(base, handle, result, handle->userData);
        }
    }
}

/*!
 * brief Provides a default configuration for the I3C slave peripheral.
 *
 * This function provides the following default configuration for the I3C slave peripheral:
 * code
 *  slaveConfig->enableslave             = true;
 * endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the slave driver with I3C_SlaveInit().
 *
 * param[out] slaveConfig User provided configuration structure for default values. Refer to #i3c_slave_config_t.
 */
void I3C_SlaveGetDefaultConfig(i3c_slave_config_t *slaveConfig)
{
    assert(NULL != slaveConfig);

    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    slaveConfig->enableSlave      = true;
    slaveConfig->isHotJoin        = false;
    slaveConfig->vendorID         = 0x11BU;
    slaveConfig->enableRandomPart = false;
    slaveConfig->partNumber       = 0;
    slaveConfig->dcr              = 0; /* Generic device. */
    slaveConfig->bcr =
        0; /* BCR[7:6]: device role, I3C slave(2b'00), BCR[5]: SDR Only / SDR and HDR Capable,  SDR and HDR
              Capable(1b'1), BCR[4]: Bridge Identifier, Not a bridge device(1b'0), BCR[3]: Offline Capable, device is
              offline capable(1b'1), BCR[2]: IBI Payload, No data byte following(1b'0), BCR[1]: IBI Request Capable,
              capable(1b'1), BCR[0]: Max Data Speed Limitation, has limitation(1b'1). */
    slaveConfig->hdrMode             = (uint8_t)kI3C_HDRModeDDR;
    slaveConfig->nakAllRequest       = false;
    slaveConfig->ignoreS0S1Error     = true;
    slaveConfig->offline             = false;
    slaveConfig->matchSlaveStartStop = false;
    slaveConfig->maxWriteLength      = 256U;
    slaveConfig->maxReadLength       = 256U;
}

/*!
 * brief Initializes the I3C slave peripheral.
 *
 * This function enables the peripheral clock and initializes the I3C slave peripheral as described by the user
 * provided configuration.
 *
 * param base The I3C peripheral base address.
 * param slaveConfig User provided peripheral configuration. Use I3C_SlaveGetDefaultConfig() to get a set of
 * defaults that you can override.
 * param slowClock_Hz Frequency in Hertz of the I3C slow clock. Used to calculate the bus match condition values.
 */
void I3C_SlaveInit(I3C_Type *base, const i3c_slave_config_t *slaveConfig, uint32_t slowClock_Hz)
{
    assert(NULL != slaveConfig);
    assert(0UL != slowClock_Hz);

    uint32_t configValue = base->SCONFIG;
    uint8_t matchCount;
    uint32_t instance = I3C_GetInstance(base);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the clock. */
    CLOCK_EnableClock(kI3cClocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    /* Reset the I3C module */
    RESET_PeripheralReset(kI3cResets[instance]);
#endif

    /* Caculate bus available condition match value for current slow clock, count value provides 1us.*/
    matchCount = (uint8_t)(slowClock_Hz / 1000000UL);

    configValue &= ~(I3C_SCONFIG_SADDR_MASK | I3C_SCONFIG_BAMATCH_MASK | I3C_SCONFIG_OFFLINE_MASK |
                     I3C_SCONFIG_IDRAND_MASK | I3C_SCONFIG_DDROK_MASK | I3C_SCONFIG_S0IGNORE_MASK |
                     I3C_SCONFIG_MATCHSS_MASK | I3C_SCONFIG_NACK_MASK | I3C_SCONFIG_SLVENA_MASK);
    configValue |= I3C_SCONFIG_SADDR(slaveConfig->staticAddr) | I3C_SCONFIG_BAMATCH(matchCount) |
                   I3C_SCONFIG_OFFLINE(slaveConfig->offline) | I3C_SCONFIG_IDRAND(slaveConfig->enableRandomPart) |
                   I3C_SCONFIG_DDROK((0U != (slaveConfig->hdrMode & (uint8_t)kI3C_HDRModeDDR)) ? 1U : 0U) |
                   I3C_SCONFIG_S0IGNORE(slaveConfig->ignoreS0S1Error) |
                   I3C_SCONFIG_MATCHSS(slaveConfig->matchSlaveStartStop) |
                   I3C_SCONFIG_NACK(slaveConfig->nakAllRequest) | I3C_SCONFIG_SLVENA(slaveConfig->enableSlave);

    base->SVENDORID &= ~I3C_SVENDORID_VID_MASK;
    base->SVENDORID |= I3C_SVENDORID_VID(slaveConfig->vendorID);

    if (!slaveConfig->enableRandomPart)
    {
        base->SIDPARTNO = slaveConfig->partNumber;
    }

    base->SIDEXT &= ~(I3C_SIDEXT_BCR_MASK | I3C_SIDEXT_DCR_MASK);
    base->SIDEXT |= I3C_SIDEXT_BCR(slaveConfig->bcr) | I3C_SIDEXT_DCR(slaveConfig->dcr);

    base->SMAXLIMITS &= ~(I3C_SMAXLIMITS_MAXRD_MASK | I3C_SMAXLIMITS_MAXWR_MASK);
    base->SMAXLIMITS |=
        (I3C_SMAXLIMITS_MAXRD(slaveConfig->maxReadLength) | I3C_SMAXLIMITS_MAXWR(slaveConfig->maxWriteLength));

    if (slaveConfig->isHotJoin)
    {
        I3C_SlaveRequestEvent(base, kI3C_SlaveEventHotJoinReq);
    }
    base->SCONFIG = configValue;
}

/*!
 * brief Deinitializes the I3C master peripheral.
 *
 * This function disables the I3C master peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * param base The I3C peripheral base address.
 */
void I3C_SlaveDeinit(I3C_Type *base)
{
    uint32_t idx = I3C_GetInstance(base);

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    /* Reset the I3C module */
    RESET_PeripheralReset(kI3cResets[idx]);
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate clock. */
    CLOCK_DisableClock(kI3cClocks[idx]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset handle pointer */
    s_i3cSlaveHandle[idx] = NULL;
}

/*!
 * @brief Gets the I3C slave state.
 *
 * @param base The I3C peripheral base address.
 * @return I3C slave activity state, refer #i3c_slave_activity_state_t.
 */
i3c_slave_activity_state_t I3C_SlaveGetActivityState(I3C_Type *base)
{
    uint8_t activeState = (uint8_t)((base->SSTATUS & I3C_SSTATUS_ACTSTATE_MASK) >> I3C_SSTATUS_ACTSTATE_SHIFT);
    i3c_slave_activity_state_t returnCode;
    switch (activeState)
    {
        case (uint8_t)kI3C_SlaveNoLatency:
            returnCode = kI3C_SlaveNoLatency;
            break;
        case (uint8_t)kI3C_SlaveLatency1Ms:
            returnCode = kI3C_SlaveLatency1Ms;
            break;
        case (uint8_t)kI3C_SlaveLatency100Ms:
            returnCode = kI3C_SlaveLatency100Ms;
            break;
        case (uint8_t)kI3C_SlaveLatency10S:
            returnCode = kI3C_SlaveLatency10S;
            break;
        default:
            returnCode = kI3C_SlaveNoLatency;
            break;
    }

    return returnCode;
}

/*!
 * brief I3C slave request event.
 *
 * param base The I3C peripheral base address.
 * param event I3C slave event of type #i3c_slave_event_t
 * param data IBI data if In-band interrupt has data, only applicable for event type #kI3C_SlaveEventIBI
 */
void I3C_SlaveRequestEvent(I3C_Type *base, i3c_slave_event_t event)
{
    uint32_t ctrlValue = base->SCTRL;

    ctrlValue &= ~I3C_SCTRL_EVENT_MASK;
    ctrlValue |= I3C_SCTRL_EVENT(event);

    base->SCTRL = ctrlValue;
}

/*!
 * brief I3C slave request event.
 *
 * param base The I3C peripheral base address.
 * param data IBI data pointer
 * param dataSize IBI data length
 */
void I3C_SlaveRequestIBIWithData(I3C_Type *base, i3c_slave_handle_t *handle, uint8_t *data, size_t dataSize)
{
    uint32_t ctrlValue = base->SCTRL;

    ctrlValue &= ~(I3C_SCTRL_EVENT_MASK | I3C_SCTRL_IBIDATA_MASK);
    ctrlValue |= I3C_SCTRL_EVENT(1U) | I3C_SCTRL_IBIDATA(*data);

    if (dataSize > 1U)
    {
        handle->ibiData     = &data[1];
        handle->ibiDataSize = dataSize - 1U;
    }

    base->SCTRL = ctrlValue;
}

/*!
 * brief Performs a polling send transfer on the I3C bus.
 *
 * param base  The I3C peripheral base address.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * return Error or success status returned by API.
 */
status_t I3C_SlaveSend(I3C_Type *base, const void *txBuff, size_t txSize)
{
    const uint8_t *buf = (const uint8_t *)((const void *)txBuff);
    status_t result    = kStatus_Success;

    assert(NULL != txBuff);

    /* Send data buffer */
    while (0UL != txSize--)
    {
        /* Wait until there is room in the fifo. This also checks for errors. */
        result = I3C_SlaveWaitForTxReady(base);
        if (kStatus_Success != result)
        {
            return result;
        }

        /* Write byte into I3C slave data register. */
        if (0UL != txSize)
        {
            base->SWDATAB = *buf++;
        }
        else
        {
            base->SWDATABE = *buf++;
        }
    }

    return result;
}

/*!
 * brief Performs a polling receive transfer on the I3C bus.
 *
 * param base  The I3C peripheral base address.
 * param rxBuff The pointer to the data to be transferred.
 * param rxSize The length in bytes of the data to be transferred.
 * return Error or success status returned by API.
 */
status_t I3C_SlaveReceive(I3C_Type *base, void *rxBuff, size_t rxSize)
{
    status_t result = kStatus_Success;
    uint8_t *buf;

    assert(NULL != rxBuff);

    /* Handle empty read. */
    if (0UL == rxSize)
    {
        return kStatus_Success;
    }

#if I3C_RETRY_TIMES
    uint32_t waitTimes = I3C_RETRY_TIMES;
#endif

    /* Receive data */
    buf = (uint8_t *)rxBuff;
    while (0UL != rxSize)
    {
#if I3C_RETRY_TIMES
        if (--waitTimes == 0)
        {
            return kStatus_I3C_Timeout;
        }
#endif
        /* Check for errors. */
        result = I3C_SlaveCheckAndClearError(base, I3C_SlaveGetErrorStatusFlags(base));
        if (kStatus_Success != result)
        {
            return result;
        }

        /* Check RX data */
        if (0UL != (base->SDATACTRL & I3C_SDATACTRL_RXCOUNT_MASK))
        {
            *buf++ = (uint8_t)(base->SRDATAB & I3C_SRDATAB_DATA0_MASK);
            rxSize--;
        }
    }

    return result;
}

/*!
 * brief Creates a new handle for the I3C slave non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_SlaveTransferAbort() API shall be called.
 *
 * note The function also enables the NVIC IRQ for the input I3C. Need to notice
 * that on some SoCs the I3C IRQ is connected to INTMUX, in this case user needs to
 * enable the associated INTMUX IRQ in application.

 * param base The I3C peripheral base address.
 * param[out] handle Pointer to the I3C slave driver handle.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void I3C_SlaveTransferCreateHandle(I3C_Type *base,
                                   i3c_slave_handle_t *handle,
                                   i3c_slave_transfer_callback_t callback,
                                   void *userData)
{
    uint32_t instance;

    assert(NULL != handle);

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I3C_GetInstance(base);

    /* Save base and instance. */
    handle->callback = callback;
    handle->userData = userData;

    /* Save this handle for IRQ use. */
    s_i3cSlaveHandle[instance] = handle;

    /* Set irq handler. */
    s_i3cSlaveIsr = I3C_SlaveTransferHandleIRQ;

    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I3C_SlaveDisableInterrupts(base, (uint32_t)kSlaveIrqFlags);
    (void)EnableIRQ(kI3cIrqs[instance]);
}

/*!
 * brief Starts accepting slave transfers.
 *
 * Call this API after calling I2C_SlaveInit() and I3C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and pass events to the
 * callback that was passed into the call to I3C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #i3c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI3C_SlaveTransmitEvent and #kI3C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, you can pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI3C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The I3C peripheral base address.
 * param handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * param eventMask Bit mask formed by OR'ing together #i3c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI3C_SlaveAllEvents to enable all events.
 *
 * retval #kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_I3C_Busy Slave transfers have already been started on this handle.
 */
status_t I3C_SlaveTransferNonBlocking(I3C_Type *base, i3c_slave_handle_t *handle, uint32_t eventMask)
{
    assert(NULL != handle);

    /* Return busy if another transaction is in progress. */
    if (handle->isBusy)
    {
        return kStatus_I3C_Busy;
    }

    /* Disable I3C IRQ sources while we configure stuff. */
    I3C_SlaveDisableInterrupts(base, (uint32_t)kSlaveIrqFlags);

    /* Clear transfer in handle. */
    (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

    /* Set up event mask. tx and rx are always enabled. */
    handle->eventMask = eventMask | (uint32_t)kI3C_SlaveTransmitEvent | (uint32_t)kI3C_SlaveReceiveEvent;

    /* Clear all flags. */
    I3C_SlaveClearStatusFlags(base, (uint32_t)kSlaveClearFlags);

    /* Enable I3C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
    I3C_SlaveEnableInterrupts(base, (uint32_t)kSlaveIrqFlags);

    return kStatus_Success;
}

/*!
 * brief Gets the slave transfer status during a non-blocking transfer.
 * param base The I3C peripheral base address.
 * param handle Pointer to i2c_slave_handle_t structure.
 * param[out] count Pointer to a value to hold the number of bytes transferred. May be NULL if the count is not
 *      required.
 * retval #kStatus_Success
 * retval #kStatus_NoTransferInProgress
 */
status_t I3C_SlaveTransferGetCount(I3C_Type *base, i3c_slave_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (!handle->isBusy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* For an active transfer, just return the count from the handle. */
    *count = handle->transferredCount;

    return kStatus_Success;
}

/*!
 * brief Aborts the slave non-blocking transfers.
 * note This API could be called at any time to stop slave for handling the bus events.
 * param base The I3C peripheral base address.
 * param handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * retval #kStatus_Success
 * retval #kStatus_I3C_Idle
 */
void I3C_SlaveTransferAbort(I3C_Type *base, i3c_slave_handle_t *handle)
{
    assert(NULL != handle);

    /* Return idle if no transaction is in progress. */
    if (handle->isBusy)
    {
        /* Disable I3C IRQ sources. */
        I3C_SlaveDisableInterrupts(base, (uint32_t)kSlaveIrqFlags);

        /* Reset transfer info. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* We're no longer busy. */
        handle->isBusy = false;
    }
}

/*!
 * brief Reusable routine to handle slave interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  non blocking API's interrupt handler routines to add special functionality.
 * param base The I3C peripheral base address.
 * param handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 */
void I3C_SlaveTransferHandleIRQ(I3C_Type *base, i3c_slave_handle_t *handle)
{
    uint32_t flags;
    uint32_t errFlags;
    uint32_t pendingInts;
    uint32_t enabledInts;
    size_t rxCount;
    size_t txCount;
    size_t txFifoSize =
        2UL << ((base->SCAPABILITIES & I3C_SCAPABILITIES_FIFOTX_MASK) >> I3C_SCAPABILITIES_FIFOTX_SHIFT);
    i3c_slave_transfer_t *xfer;

    /* Check for a valid handle in case of a spurious interrupt. */
    if (NULL == handle)
    {
        return;
    }

    xfer = &handle->transfer;

    /* Get status flags. */
    flags    = I3C_SlaveGetStatusFlags(base);
    errFlags = I3C_SlaveGetErrorStatusFlags(base);

    pendingInts = I3C_SlaveGetPendingInterrupts(base);
    enabledInts = I3C_SlaveGetEnabledInterrupts(base);

    if (0UL != (errFlags & (uint32_t)kSlaveErrorFlags))
    {
        xfer->event            = (uint32_t)kI3C_SlaveCompletionEvent;
        xfer->completionStatus = I3C_SlaveCheckAndClearError(base, errFlags);

        if ((0UL != (handle->eventMask & (uint32_t)kI3C_SlaveCompletionEvent)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
        return;
    }

    /* Clear status flags. */
    I3C_SlaveClearStatusFlags(base, flags);

    if (0UL != (flags & (uint32_t)kI3C_SlaveBusStartFlag))
    {
        base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK;
        xfer->txDataSize = 0;
        I3C_SlaveEnableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
        pendingInts |= (uint32_t)kI3C_SlaveTxReadyFlag;
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveEventSentFlag))
    {
        xfer->event = (uint32_t)kI3C_SlaveRequestSentEvent;
        if (handle->ibiData != NULL)
        {
            size_t count = 0U;
            while (count < handle->ibiDataSize)
            {
                base->SCTRL = (base->SCTRL & ~I3C_SCTRL_IBIDATA_MASK) | I3C_SCTRL_IBIDATA(handle->ibiData[count]) |
                              I3C_SCTRL_EVENT(1U);
                count++;
            }
        }

        /* Reset IBI data buffer. */
        handle->ibiData = NULL;

        if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveReceivedCCCFlag))
    {
        handle->isBusy = true;
        xfer->event    = (uint32_t)kI3C_SlaveReceivedCCCEvent;
        if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveBusStopFlag))
    {
        I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
        pendingInts &= ~(uint32_t)kI3C_SlaveTxReadyFlag;
        base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK | I3C_SDATACTRL_FLUSHFB_MASK;
        if (handle->isBusy == true)
        {
            xfer->event            = (uint32_t)kI3C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            xfer->transferredCount = handle->transferredCount;
            handle->isBusy         = false;

            if (handle->wasTransmit)
            {
                /* Subtract one from the transmit count to offset the fact that I3C asserts the */
                /* tx flag before it sees the nack from the master-receiver, thus causing one more */
                /* count that the master actually receives. */
                --xfer->transferredCount;
                handle->wasTransmit = false;
            }

            if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
            {
                handle->callback(base, xfer, handle->userData);
            }

            /* Clean up transfer info on completion, after the callback has been invoked. */
            (void)memset(&handle->transfer, 0, sizeof(handle->transfer));
        }
        else
        {
            return;
        }
    }

    if (0UL != (flags & (uint32_t)kI3C_SlaveMatchedFlag))
    {
        xfer->event    = (uint32_t)kI3C_SlaveAddressMatchEvent;
        handle->isBusy = true;
        if ((0UL != (handle->eventMask & (uint32_t)kI3C_SlaveAddressMatchEvent)) && (NULL != handle->callback))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }

    /* Get fifo counts and compute room in tx fifo. */
    I3C_SlaveGetFifoCounts(base, &rxCount, &txCount);
    txCount = txFifoSize - txCount;

    /* Handle transmit and receive. */
    if ((0UL != (flags & (uint32_t)kI3C_SlaveTxReadyFlag)) && (0UL != (pendingInts & (uint32_t)kI3C_SlaveTxReadyFlag)))
    {
        handle->wasTransmit = true;

        /* If we're out of data, invoke callback to get more. */
        if ((NULL == xfer->txData) || (0UL == xfer->txDataSize))
        {
            xfer->event = (uint32_t)kI3C_SlaveTransmitEvent;
            if (0UL != (flags & (uint32_t)kI3C_SlaveBusHDRModeFlag))
            {
                xfer->event |= (uint32_t)kI3C_SlaveHDRCommandMatchEvent;
            }
            if (NULL != handle->callback)
            {
                handle->callback(base, xfer, handle->userData);
            }

            /* Clear the transferred count now that we have a new buffer. */
            handle->transferredCount = 0;
        }

        if ((NULL == xfer->txData) || (0UL == xfer->txDataSize))
        {
            I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
            pendingInts &= ~(uint32_t)kI3C_SlaveTxReadyFlag;
        }

        /* Transmit a byte. */
        while ((xfer->txDataSize != 0UL) && (txCount != 0U))
        {
            if (xfer->txDataSize > 1UL)
            {
                base->SWDATAB = *xfer->txData++;
            }
            else
            {
                base->SWDATABE = *xfer->txData++;
                I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
            }
            --xfer->txDataSize;
            ++handle->transferredCount;
            txCount--;
        }
    }
    if ((0UL != (flags & (uint32_t)kI3C_SlaveRxReadyFlag)) && (0UL != (enabledInts & (uint32_t)kI3C_SlaveRxReadyFlag)))
    {
        /* If we're out of room in the buffer, invoke callback to get another. */
        if ((NULL == xfer->rxData) || (0UL == xfer->rxDataSize))
        {
            xfer->event = (uint32_t)kI3C_SlaveReceiveEvent;
            if (0UL != (flags & (uint32_t)kI3C_SlaveBusHDRModeFlag))
            {
                xfer->event |= (uint32_t)kI3C_SlaveHDRCommandMatchEvent;
            }
            if (NULL != handle->callback)
            {
                handle->callback(base, xfer, handle->userData);
            }
            handle->transferredCount = 0;
        }

        /* Receive a byte. */
        if ((I3C_SlaveGetEnabledInterrupts(base) & (uint32_t)kI3C_SlaveRxReadyFlag) != 0U)
        {
            while ((rxCount != 0U) && ((xfer->rxData != NULL) && (xfer->rxDataSize != 0UL)))
            {
                *xfer->rxData++ = (uint8_t)base->SRDATAB;
                --xfer->rxDataSize;
                ++handle->transferredCount;
                rxCount--;
            }
        }
    }
}

static void I3C_CommonIRQHandler(I3C_Type *base, uint32_t instance)
{
    /* Check for master IRQ. */
    if (((uint32_t)kI3C_MasterOn == (base->MCONFIG & I3C_MCONFIG_MSTENA_MASK)) && (NULL != s_i3cMasterIsr))
    {
        /* Master mode. */
        s_i3cMasterIsr(base, s_i3cMasterHandle[instance]);
    }

    /* Check for slave IRQ. */
    if ((I3C_SCONFIG_SLVENA_MASK == (base->SCONFIG & I3C_SCONFIG_SLVENA_MASK)) && (NULL != s_i3cSlaveIsr))
    {
        /* Slave mode. */
        s_i3cSlaveIsr(base, s_i3cSlaveHandle[instance]);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if defined(I3C)
/* Implementation of I3C handler named in startup code. */
void I3C0_DriverIRQHandler(void);
void I3C0_DriverIRQHandler(void)
{
    I3C_CommonIRQHandler(I3C, 0);
}
#endif

#if defined(I3C0)
/* Implementation of I3C0 handler named in startup code. */
void I3C0_DriverIRQHandler(void);
void I3C0_DriverIRQHandler(void)
{
    I3C_CommonIRQHandler(I3C0, 0);
}
#endif

#if defined(I3C1)
/* Implementation of I3C1 handler named in startup code. */
void I3C1_DriverIRQHandler(void);
void I3C1_DriverIRQHandler(void)
{
    I3C_CommonIRQHandler(I3C1, 1);
}
#endif
