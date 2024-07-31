/*
 * Copyright 2018-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i3c.h"
#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
#include "fsl_reset.h"
#endif
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

/*!
 * @brief Used for conversion between `uint8_t*` and `uint32_t`.
 */
typedef union i3c_puint8_to_u32
{
    uint8_t *puint8;
    uint32_t u32;
    const uint8_t *cpuint8;
} i3c_puint8_to_u32_t;

/*
 * <! Structure definition for variables that passed as parameters in I3C_RunTransferStateMachine.
 * The structure is private.
 */
typedef struct _i3c_state_machine_param
{
    bool state_complete;
    size_t txCount;
    size_t rxCount;
    uint32_t status;
    status_t result;
    i3c_master_state_t masterState;
} i3c_master_state_machine_param_t;

/*
 * <! Structure definition for variables that passed as parameters in I3C_SlaveTransferHandleIRQ.
 * The structure is private.
 */
typedef struct _i3c_transfer_handleIrq_param
{
    size_t txCount;
    size_t rxCount;
    uint32_t flags;
    uint32_t pendingInts;
    uint32_t enabledInts;
} i3c_slave_handleIrq_param_t;

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
static uint8_t usedDevCount = 0;

/*! @brief Pointer to master IRQ handler for each instance. */
i3c_master_isr_t s_i3cMasterIsr;

/*! @brief Pointers to master handles for each instance. */
void *s_i3cMasterHandle[ARRAY_SIZE(kI3cBases)];

/*! @brief Pointer to slave IRQ handler for each instance. */
i3c_slave_isr_t s_i3cSlaveIsr;

/*! @brief Pointers to slave handles for each instance. */
void *s_i3cSlaveHandle[ARRAY_SIZE(kI3cBases)];

/*!
 * @brief introduce function I3C_TransferStateMachineIBIWonState.
 * This function was deal with init function I3C_RunTransferStateMachine`s variable.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_TransferStateMachineIBIWonState(I3C_Type *base,
                                                i3c_master_handle_t *handle,
                                                i3c_master_state_machine_param_t *stateParams);

/*!
 * @brief introduce function static bool I3C_TransferStateMachineSendCommandState.
 * This function was deal with when state is stop.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_TransferStateMachineSendCommandState(I3C_Type *base,
                                                     i3c_master_handle_t *handle,
                                                     i3c_master_state_machine_param_t *stateParams);

/*!
 * @brief introduce function I3C_TransferStateMachineWaitRepeatedStartCompleteState.
 * This function was deal with Wait Repeated Start Complete State.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_TransferStateMachineWaitRepeatedStartCompleteState(I3C_Type *base,
                                                                   i3c_master_handle_t *handle,
                                                                   i3c_master_state_machine_param_t *stateParams);

/*!
 * @brief introduce function I3C_TransferStateMachineTransferDataState.
 * This function was deal with Transfer Data State.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_TransferStateMachineTransferDataState(I3C_Type *base,
                                                      i3c_master_handle_t *handle,
                                                      i3c_master_state_machine_param_t *stateParams);
/*!
 * @brief introduce function I3C_TransferStateMachineWaitForCompletionState.
 * This function was deal with Wait For Completion State.
 *
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_TransferStateMachineWaitForCompletionState(i3c_master_handle_t *handle,
                                                           i3c_master_state_machine_param_t *stateParams);

/*!
 * @brief introduce function I3C_TransferStateMachineStopState.
 * This function was deal with Stop State.
 *
 * @param base The I3C peripheral base address.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_TransferStateMachineStopState(I3C_Type *base,
                                              i3c_master_handle_t *handle,
                                              i3c_master_state_machine_param_t *stateParams);

/*!
 * @brief introduce function I3C_SlaveTransferHandleGetStatusFlags.
 * This function was deal get status flag.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 *
 * @return default true when No abnormality.
 * @return true when error.
 */
static bool I3C_SlaveTransferHandleGetStatusFlags(I3C_Type *base,
                                                  i3c_slave_handle_t *handle,
                                                  i3c_slave_handleIrq_param_t *stateParams);
/*!
 * @brief introduce function I3C_SlaveTransferHandleBusStart.
 * This function was deal start Bus.
 *
 * @param base The I3C peripheral base address.
 * @param xfer address to xfer.
 * @param pendingInts address to pendingInts.
 */
static void I3C_SlaveTransferHandleBusStart(I3C_Type *base, i3c_slave_transfer_t *xfer, uint32_t *pendingInts);

/*!
 * @brief introduce function I3C_SlaveTransferHandleEventSent.
 * This function was deal sent event.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param xfer address to xfer.
 */
static void I3C_SlaveTransferHandleEventSent(I3C_Type *base, i3c_slave_handle_t *handle, i3c_slave_transfer_t *xfer);

/*!
 * @brief introduce function I3C_SlaveTransferHandleReceivedCCC.
 * This function was deal Received.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param xfer address to xfer.
 */
static void I3C_SlaveTransferHandleReceivedCCC(I3C_Type *base, i3c_slave_handle_t *handle, i3c_slave_transfer_t *xfer);

/*!
 * @brief introduce function I3C_SlaveTransferHandleBusStop.
 * This function was deal stop Bus.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_SlaveTransferHandleBusStop(I3C_Type *base,
                                           i3c_slave_handle_t *handle,
                                           i3c_slave_handleIrq_param_t *stateParams);

/*!
 * @brief introduce function I3C_SlaveTransferHandleMatched.
 * This function was deal matched.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param xfer address to xfer.
 */
static void I3C_SlaveTransferHandleMatched(I3C_Type *base, i3c_slave_handle_t *handle, i3c_slave_transfer_t *xfer);

/*!
 * @brief introduce function I3C_SlaveTransferHandleTxReady.
 * This function was deal when Tx was ready.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_SlaveTransferHandleTxReady(I3C_Type *base,
                                           i3c_slave_handle_t *handle,
                                           i3c_slave_handleIrq_param_t *stateParams);

/*!
 * @brief introduce function I3C_SlaveTransferHandleRxReadyy.
 * This function was deal with when Rx was ready.
 *
 * @param base The I3C peripheral base address.
 * @param handle handle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 * @param stateParams Pass the address of the parent function variable.
 */
static void I3C_SlaveTransferHandleRxReady(I3C_Type *base,
                                           i3c_slave_handle_t *handle,
                                           i3c_slave_handleIrq_param_t *stateParams);

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

#if defined(I3C_DMA_IGNORE_FIFO_ERROR)
    status &= ~((uint32_t)kI3C_MasterErrorWriteFlag | (uint32_t)kI3C_MasterErrorReadFlag);
    I3C_MasterClearErrorStatusFlags(base, ((uint32_t)kI3C_MasterErrorWriteFlag | (uint32_t)kI3C_MasterErrorReadFlag));
#endif

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

status_t I3C_MasterWaitForCtrlDone(I3C_Type *base, bool waitIdle)
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
status_t I3C_SlaveCheckAndClearError(I3C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new transfer can start. */
    status &= (uint32_t)kSlaveErrorFlags;

#if defined(I3C_DMA_IGNORE_FIFO_ERROR)
    status &= ~((uint32_t)kI3C_SlaveErrorUnderrunFlag | (uint32_t)kI3C_SlaveErrorOverwriteFlag);
    I3C_SlaveClearErrorStatusFlags(base,
                                   ((uint32_t)kI3C_SlaveErrorUnderrunFlag | (uint32_t)kI3C_SlaveErrorOverwriteFlag));
#endif

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

/*!
 * brief I3C master get IBI Type.
 *
 * param base The I3C peripheral base address.
 * param i3c_ibi_type_t Type of #i3c_ibi_type_t.
 */
i3c_ibi_type_t I3C_GetIBIType(I3C_Type *base)
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
    config->masterDynamicAddress         = 0x0AU; /* Default master dynamic address. */
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
    config->slowClock_Hz                 = 0; /* Not update the Soc default setting. */
#endif
    config->enableSlave                  = true;
    config->vendorID                     = 0x11BU;
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND)
    config->enableRandomPart = false;
#endif
    config->partNumber = 0;
    config->dcr        = 0; /* Generic device. */
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
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) || \
    !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    uint32_t instance = I3C_GetInstance(base);
#endif
    uint32_t configValue;

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

#if defined(FSL_FEATURE_I3C_HAS_START_SCL_DELAY) && FSL_FEATURE_I3C_HAS_START_SCL_DELAY
    base->MCONFIG_EXT = I3C_MCONFIG_EXT_I3C_CAS_DEL(config->startSclDelay) | I3C_MCONFIG_EXT_I3C_CASR_DEL(config->restartSclDelay);
#endif

    I3C_MasterSetWatermarks(base, kI3C_TxTriggerUntilOneLessThanFull, kI3C_RxTriggerOnNotEmpty, true, true);

    I3C_MasterSetBaudRate(base, &config->baudRate_Hz, sourceClock_Hz);

#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
    assert((config->slowClock_Hz >= 1000000U) || (config->slowClock_Hz == 0U));

    uint8_t matchCount;
    /* Set as (slowClk(MHz) - 1) to generate 1us clock cycle. Controller uses it to count 100us timeout. Target uses it as IBI request to drive SDA low.
       Note: Use BAMATCH = 1 to generate 1us clock cycle if slow clock is 1MHz. The value of 0 would not give a correct match indication. */
    if (config->slowClock_Hz != 0U)
    {
        matchCount = (uint8_t)(config->slowClock_Hz / 1000000UL) - 1U;
        matchCount = (matchCount == 0U) ? 1U : matchCount;
    }
    else
    {
        /* BAMATCH has default value based on Soc default slow clock after reset, using this default value when slowClock_Hz is 0. */
        matchCount = (uint8_t)((base->SCONFIG & I3C_SCONFIG_BAMATCH_MASK) >> I3C_SCONFIG_BAMATCH_SHIFT);
    }
#endif

    configValue = base->SCONFIG;

    configValue &=
        ~(I3C_SCONFIG_SADDR_MASK |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
          I3C_SCONFIG_BAMATCH_MASK |
#endif
          I3C_SCONFIG_OFFLINE_MASK |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND)
          I3C_SCONFIG_IDRAND_MASK |
#endif
#if defined(FSL_FEATURE_I3C_HAS_HDROK) && FSL_FEATURE_I3C_HAS_HDROK
          I3C_SCONFIG_HDROK_MASK |
#else
          I3C_SCONFIG_DDROK_MASK |
#endif
          I3C_SCONFIG_S0IGNORE_MASK | I3C_SCONFIG_MATCHSS_MASK | I3C_SCONFIG_NACK_MASK | I3C_SCONFIG_SLVENA_MASK);

    configValue |= I3C_SCONFIG_SADDR(config->staticAddr) |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
                   I3C_SCONFIG_BAMATCH(matchCount) |
#endif
                   I3C_SCONFIG_OFFLINE(config->offline) |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND)
                   I3C_SCONFIG_IDRAND(config->enableRandomPart) |
#endif
#if defined(FSL_FEATURE_I3C_HAS_HDROK) && FSL_FEATURE_I3C_HAS_HDROK
                   I3C_SCONFIG_HDROK((0U != (config->hdrMode & (uint8_t)kI3C_HDRModeDDR)) ? 1U : 0U) |
#else
                   I3C_SCONFIG_DDROK((0U != (config->hdrMode & (uint8_t)kI3C_HDRModeDDR)) ? 1U : 0U) |
#endif
                   I3C_SCONFIG_S0IGNORE(config->ignoreS0S1Error) | I3C_SCONFIG_MATCHSS(config->matchSlaveStartStop) |
                   I3C_SCONFIG_NACK(config->nakAllRequest) | I3C_SCONFIG_SLVENA(config->enableSlave);

    base->SVENDORID &= ~I3C_SVENDORID_VID_MASK;
    base->SVENDORID |= I3C_SVENDORID_VID(config->vendorID);

#if defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND
    base->SIDPARTNO = config->partNumber;
#else
    if (!config->enableRandomPart)
    {
        base->SIDPARTNO = config->partNumber;
    }
#endif

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
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

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
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) || \
    !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    uint32_t instance = I3C_GetInstance(base);
#endif

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

#if defined(FSL_FEATURE_I3C_HAS_START_SCL_DELAY) && FSL_FEATURE_I3C_HAS_START_SCL_DELAY
    base->MCONFIG_EXT = I3C_MCONFIG_EXT_I3C_CAS_DEL(masterConfig->startSclDelay) | I3C_MCONFIG_EXT_I3C_CASR_DEL(masterConfig->restartSclDelay);
#endif

    I3C_MasterSetWatermarks(base, kI3C_TxTriggerUntilOneLessThanFull, kI3C_RxTriggerOnNotEmpty, true, true);

    I3C_MasterSetBaudRate(base, &masterConfig->baudRate_Hz, sourceClock_Hz);

#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
    assert((masterConfig->slowClock_Hz >= 1000000U) || (masterConfig->slowClock_Hz == 0U));

    uint32_t configValue;
    uint8_t matchCount;

    /* BAMATCH has default value based on Soc default slow clock after reset, using this default value when slowClock_Hz is 0. */
    if (masterConfig->slowClock_Hz != 0U)
    {
        /* Set as (slowClk(MHz) - 1) to generate 1us clock cycle for 100us timeout. Note: Use BAMATCH = 1 to generate 1us clock cycle
           if slow clock is 1MHz. The value of 0 would not give a correct match indication. */
        matchCount = (uint8_t)(masterConfig->slowClock_Hz / 1000000UL) - 1U;
        matchCount = (matchCount == 0U) ? 1U : matchCount;

        configValue = base->SCONFIG & I3C_SCONFIG_BAMATCH_MASK;
        configValue |= I3C_SCONFIG_BAMATCH(matchCount);
        base->SCONFIG = configValue;
    }
#endif
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
 * brief Sends a START signal and slave address on the I2C/I3C bus, receive size is also specified
 * in the call.
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
 * param rxSize Read terminate size for the followed read transfer, limit to 255 bytes.
 * retval #kStatus_Success START signal and address were successfully enqueued in the transmit FIFO.
 * retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 */
status_t I3C_MasterStartWithRxSize(
    I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir, uint8_t rxSize)
{
    i3c_master_state_t masterState = I3C_MasterGetState(base);
    bool checkDdrState             = (type == kI3C_TypeI3CDdr) ? (masterState != kI3C_MasterStateDdr) : true;
    if ((masterState != kI3C_MasterStateIdle) && (masterState != kI3C_MasterStateNormAct) && checkDdrState)
    {
        return kStatus_I3C_Busy;
    }

    return I3C_MasterRepeatedStartWithRxSize(base, type, address, dir, rxSize);
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

    return I3C_MasterStartWithRxSize(base, type, address, dir, 0);
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

#if defined(FSL_FEATURE_I3C_HAS_ERRATA_051617) && (FSL_FEATURE_I3C_HAS_ERRATA_051617)
    /* ERRATA051617: When used as I2C controller generates repeated START randomly before the STOP under PVT condition.
    This issue is caused by a glitch at the output of an internal clock MUX. The glitch when generates acts as a clock
    pulse which causes the SDA line to fall early during SCL high period and creates the unintended Repeated START before
    actual STOP. */
    if (type == kI3C_TypeI2C)
    {
        base->MCONFIG |= I3C_MCONFIG_SKEW(1);
    }
    else
    {
        base->MCONFIG &= ~I3C_MCONFIG_SKEW_MASK;
    }
#endif

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

    if (masterReq == kI3C_RequestProcessDAA)
    {
        mctrlReg &= ~I3C_MCTRL_TYPE_MASK;
    }

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
    status_t result   = kStatus_Success;
    bool isRxAutoTerm = ((flags & (uint32_t)kI3C_TransferRxAutoTermFlag) != 0UL);
    bool completed    = false;
    uint32_t status;
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
                        result = I3C_MasterWaitForCtrlDone(base, false);
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
            if ((flags & (uint32_t)kI3C_TransferDisableRxTermFlag) == 0UL)
            {
                if ((!isRxAutoTerm) && (rxSize == 1U))
                {
                    base->MCTRL |= I3C_MCTRL_RDTERM(1U);
                }
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
            result = I3C_MasterWaitForCtrlDone(base, false);
        }
        else
        {
            result = I3C_MasterEmitStop(base, true);
        }
    }

    return result;
}

/*!
 * brief Performs a DAA in the i3c bus with specified temporary baud rate.
 *
 * param base The I3C peripheral base address.
 * param addressList The pointer for address list which is used to do DAA.
 * param count The address count in the address list.
 * param daaBaudRate The temporary baud rate in DAA process, NULL for using initial setting.
 * The initial setting is set back between the completion of the DAA and the return of this function.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 * retval #kStatus_I3C_SlaveCountExceed The I3C slave count has exceed the definition in I3C_MAX_DEVCNT.
 */
status_t I3C_MasterProcessDAASpecifiedBaudrate(I3C_Type *base,
                                               uint8_t *addressList,
                                               uint32_t count,
                                               i3c_master_daa_baudrate_t *daaBaudRate)
{
    assert(addressList != NULL);
    assert(count != 0U);

    status_t result       = kStatus_Success;
    uint8_t rxBuffer[8]   = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    uint32_t masterConfig = 0;
    uint32_t devCount     = 0;
    uint8_t rxSize        = 0;
    bool mctrlDone        = false;
    i3c_baudrate_hz_t baudRate_Hz;
    uint32_t errStatus;
    uint32_t status;
    size_t rxCount;

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

    /* Temporarily adjust baud rate before DAA. */
    if (daaBaudRate != NULL)
    {
        masterConfig = base->MCONFIG;
        /* Set non-zero value for I2C baud rate which is useless here. */
        baudRate_Hz.i2cBaud          = 1;
        baudRate_Hz.i3cOpenDrainBaud = daaBaudRate->i3cOpenDrainBaud;
        baudRate_Hz.i3cPushPullBaud  = daaBaudRate->i3cPushPullBaud;
        I3C_MasterSetBaudRate(base, &baudRate_Hz, daaBaudRate->sourceClock_Hz);
    }

    /* Emit process DAA */
    I3C_MasterEmitRequest(base, kI3C_RequestProcessDAA);

    do
    {
        status = I3C_MasterGetStatusFlags(base);

        /* Check for error flags. */
        errStatus = I3C_MasterGetErrorStatusFlags(base);
        result    = I3C_MasterCheckAndClearError(base, errStatus);
        if (kStatus_Success != result)
        {
            break;
        }

        if ((!mctrlDone) || (rxSize < 8U))
        {
            I3C_MasterGetFifoCounts(base, &rxCount, NULL);

            if (rxCount != 0U)
            {
                rxBuffer[rxSize++] = (uint8_t)(base->MRDATAB & I3C_MRDATAB_VALUE_MASK);
            }

            if ((status & (uint32_t)kI3C_MasterControlDoneFlag) != 0U)
            {
                I3C_MasterClearStatusFlags(base, (uint32_t)kI3C_MasterControlDoneFlag);
                mctrlDone = true;
            }
        }
        else if ((I3C_MasterGetState(base) == kI3C_MasterStateDaa) &&
                 (0UL != (I3C_MasterGetStatusFlags(base) & (uint32_t)kI3C_MasterBetweenFlag)))
        {
            if (((devCount + 1UL) > count) || ((devCount + 1UL) > I3C_MAX_DEVCNT))
            {
                result = kStatus_I3C_SlaveCountExceed;
                break;
            }

            /* Assign the dynamic address from address list. */
            devList[devCount].dynamicAddr = *addressList++;
            base->MWDATAB                 = devList[devCount].dynamicAddr;

            /* Emit process DAA again. */
            I3C_MasterEmitRequest(base, kI3C_RequestProcessDAA);

            devList[devCount].vendorID   = (((uint16_t)rxBuffer[0] << 8U | (uint16_t)rxBuffer[1]) & 0xFFFEU) >> 1U;
            devList[devCount].partNumber = ((uint32_t)rxBuffer[2] << 24U | (uint32_t)rxBuffer[3] << 16U |
                                            (uint32_t)rxBuffer[4] << 8U | (uint32_t)rxBuffer[5]);
            devList[devCount].bcr        = rxBuffer[6];
            devList[devCount].dcr        = rxBuffer[7];
            devCount++;
            usedDevCount++;

            /* Ready to handle next device. */
            mctrlDone = false;
            rxSize    = 0;
        }
        else
        {
            /* Intentional empty */
        }
    } while ((status & (uint32_t)kI3C_MasterCompleteFlag) != (uint32_t)kI3C_MasterCompleteFlag);

    /* Master stops DAA if slave device number exceeds the prepared address number. */
    if (result == kStatus_I3C_SlaveCountExceed)
    {
        /* Send the STOP signal */
        base->MCTRL = (base->MCTRL & ~(I3C_MCTRL_REQUEST_MASK | I3C_MCTRL_DIR_MASK | I3C_MCTRL_RDTERM_MASK)) |
                      I3C_MCTRL_REQUEST(kI3C_RequestEmitStop);
    }

    /* Set back initial baud rate after DAA is over. */
    if (daaBaudRate != NULL)
    {
        base->MCONFIG = masterConfig;
    }

    /* Clear all flags. */
    I3C_MasterClearErrorStatusFlags(base, (uint32_t)kMasterErrorFlags);
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);

    /* Enable I3C IRQ sources while we configure stuff. */
    I3C_MasterEnableInterrupts(base, enabledInts);

    return result;
}

/*!
 * brief Get device information list after DAA process is done.
 *
 * param base The I3C peripheral base address.
 * param[out] count The pointer to store the available device count.
 * return Pointer to the i3c_device_info_t array.
 */
i3c_device_info_t *I3C_MasterGetDeviceListAfterDAA(I3C_Type *base, uint8_t *count)
{
    assert(NULL != count);

    *count = usedDevCount;

    return devList;
}

/*!
 * @brief introduce function I3C_MasterClearFlagsAndEnableIRQ.
 *
 * This function was used of Clear all flags and Enable I3C IRQ sources for @param *base.
 *
 * @param base The I3C peripheral base address.
 */
static void I3C_MasterClearFlagsAndEnableIRQ(I3C_Type *base)
{
    /* Clear all flags. */
    I3C_MasterClearStatusFlags(base, (uint32_t)kMasterClearFlags);
    /* Enable I3C IRQ sources. */
    I3C_MasterEnableInterrupts(base, (uint32_t)kMasterIrqFlags);
}

/*!
 * @brief introduce function I3C_MasterTransferNoStartFlag.
 *
 * This function was used of Check if device request wins arbitration.
 *
 * @param base The I3C peripheral base address.
 * @param transfer Pointer to the transfer structure.
 * @retval #true if the device wins arbitration.
 * @retval #false if the device not wins arbitration.
 */
static bool I3C_MasterTransferNoStartFlag(I3C_Type *base, i3c_master_transfer_t *transfer)
{
    /* Wait tx fifo empty. */
    size_t txCount = 0xFFUL;

    while (txCount != 0U)
    {
        I3C_MasterGetFifoCounts(base, NULL, &txCount);
    }

    /* Check if device request wins arbitration. */
    if (0UL != (I3C_MasterGetStatusFlags(base) & (uint32_t)kI3C_MasterArbitrationWonFlag))
    {
        I3C_MasterClearFlagsAndEnableIRQ(base);
        return true;
    }
    return false;
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
    i3c_rx_term_ops_t rxTermOps;

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

    /* True: Set Rx termination bytes at start point, False: Set Rx termination one bytes in advance. */
    if ((transfer->flags & (uint32_t)kI3C_TransferDisableRxTermFlag) != 0U)
    {
        rxTermOps = kI3C_RxTermDisable;
    }
    else if (transfer->dataSize <= 255U)
    {
        rxTermOps = kI3C_RxAutoTerm;
    }
    else
    {
        rxTermOps = kI3C_RxTermLastByte;
    }

    if (0UL != (transfer->flags & (uint32_t)kI3C_TransferStartWithBroadcastAddr))
    {
        if (0UL != (transfer->flags & (uint32_t)kI3C_TransferNoStartFlag))
        {
            return kStatus_InvalidArgument;
        }

        if (0UL != (transfer->flags & (uint32_t)kI3C_TransferRepeatedStartFlag))
        {
            return kStatus_InvalidArgument;
        }

        /* Issue 0x7E as start. */
        result = I3C_MasterStart(base, transfer->busType, 0x7E, kI3C_Write);
        if (result != kStatus_Success)
        {
            return result;
        }

        result = I3C_MasterWaitForCtrlDone(base, false);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    if (0UL == (transfer->flags & (uint32_t)kI3C_TransferNoStartFlag))
    {
        if ((direction == kI3C_Read) && (rxTermOps == kI3C_RxAutoTerm))
        {
            result = I3C_MasterStartWithRxSize(base, transfer->busType, transfer->slaveAddress, direction,
                                               (uint8_t)transfer->dataSize);
        }
        else
        {
            result = I3C_MasterStart(base, transfer->busType, transfer->slaveAddress, direction);
        }
        if (result != kStatus_Success)
        {
            return result;
        }

        result = I3C_MasterWaitForCtrlDone(base, false);
        if (result != kStatus_Success)
        {
            return result;
        }

        if (true == I3C_MasterTransferNoStartFlag(base, transfer))
        {
            return kStatus_I3C_IBIWon;
        }
    }
    else
    {
        if ((direction == kI3C_Read) && (rxTermOps != kI3C_RxTermDisable))
        {
            /* Can't set Rx termination more than one bytes in advance without START. */
            rxTermOps = kI3C_RxTermLastByte;
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
                    I3C_MasterClearFlagsAndEnableIRQ(base);
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
            if (rxTermOps == kI3C_RxAutoTerm)
            {
                result = I3C_MasterRepeatedStartWithRxSize(base, transfer->busType, transfer->slaveAddress, kI3C_Read,
                                                           (uint8_t)transfer->dataSize);
            }
            else
            {
                result = I3C_MasterRepeatedStart(base, transfer->busType, transfer->slaveAddress, kI3C_Read);
            }

            if (kStatus_Success != result)
            {
                I3C_MasterClearFlagsAndEnableIRQ(base);
                return result;
            }

            result = I3C_MasterWaitForCtrlDone(base, false);
            if (result != kStatus_Success)
            {
                return result;
            }
        }
    }

    if (rxTermOps == kI3C_RxAutoTerm)
    {
        transfer->flags |= (uint32_t)kI3C_TransferRxAutoTermFlag;
    }
    else
    {
        transfer->flags &= ~(uint32_t)kI3C_TransferRxAutoTermFlag;
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
        result = I3C_MasterReceive(base, transfer->data, transfer->dataSize, transfer->flags);
    }
    else
    {
        if ((transfer->flags & (uint32_t)kI3C_TransferNoStopFlag) == 0UL)
        {
            result = I3C_MasterEmitStop(base, true);
        }
    }

    if (result == kStatus_I3C_Nak)
    {
        (void)I3C_MasterEmitStop(base, true);
    }

    I3C_MasterClearFlagsAndEnableIRQ(base);

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

static void I3C_TransferStateMachineIBIWonState(I3C_Type *base,
                                                i3c_master_handle_t *handle,
                                                i3c_master_state_machine_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    if (stateParams->masterState == kI3C_MasterStateIbiAck)
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
    if (0UL != stateParams->rxCount)
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
        (stateParams->rxCount)--;
        return;
    }
    else if (0UL != (stateParams->status & (uint32_t)kI3C_MasterCompleteFlag))
    {
        handle->ibiType             = I3C_GetIBIType(base);
        handle->ibiAddress          = I3C_GetIBIAddress(base);
        stateParams->state_complete = true;
        stateParams->result         = kStatus_I3C_IBIWon;
    }
    else
    {
        stateParams->state_complete = true;
    }
}

static void I3C_TransferStateMachineSendCommandState(I3C_Type *base,
                                                     i3c_master_handle_t *handle,
                                                     i3c_master_state_machine_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    I3C_MasterEnableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);
    /* Make sure there is room in the tx fifo for the next command. */
    if (0UL == (stateParams->txCount)--)
    {
        stateParams->state_complete = true;
        return;
    }
    if (handle->transfer.subaddressSize > 1U)
    {
        handle->transfer.subaddressSize--;
        base->MWDATAB = (uint8_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));
    }
    else if (handle->transfer.subaddressSize == 1U)
    {
        handle->transfer.subaddressSize--;

        if ((handle->transfer.direction == kI3C_Read) || (0UL == handle->transfer.dataSize))
        {
            base->MWDATABE = (uint8_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));

            if (handle->transfer.busType != kI3C_TypeI3CDdr)
            {
                if (0UL == handle->transfer.dataSize)
                {
                    handle->state = (uint8_t)kWaitForCompletionState;
                }
                else
                {
                    /* xfer->dataSize != 0U, xfer->direction = kI3C_Read */
                    handle->state = (uint8_t)kWaitRepeatedStartCompleteState;
                }
            }
            else
            {
                handle->state = (uint8_t)kTransferDataState;
            }
        }
        else
        {
            /* Next state, transfer data. */
            handle->state = (uint8_t)kTransferDataState;
            base->MWDATAB = (uint8_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));
        }
    }
    else
    {
        /* Eliminate misra 15.7*/
    }
}

static void I3C_TransferStateMachineWaitRepeatedStartCompleteState(I3C_Type *base,
                                                                   i3c_master_handle_t *handle,
                                                                   i3c_master_state_machine_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    /* We stay in this state until the master complete. */
    if (0UL != (stateParams->status & (uint32_t)kI3C_MasterCompleteFlag))
    {
        handle->state = (uint8_t)kTransferDataState;
        I3C_MasterDisableInterrupts(base, (uint32_t)kI3C_MasterTxReadyFlag);

        if (handle->remainingBytes < 256U)
        {
            handle->rxTermOps = (handle->rxTermOps == kI3C_RxTermDisable) ? handle->rxTermOps : kI3C_RxAutoTerm;
            stateParams->result =
                I3C_MasterRepeatedStartWithRxSize(base, handle->transfer.busType, handle->transfer.slaveAddress,
                                                  kI3C_Read, (uint8_t)handle->remainingBytes);
        }
        else
        {
            stateParams->result =
                I3C_MasterRepeatedStart(base, handle->transfer.busType, handle->transfer.slaveAddress, kI3C_Read);
        }
    }

    stateParams->state_complete = true;
}

static void I3C_TransferStateMachineTransferDataState(I3C_Type *base,
                                                      i3c_master_handle_t *handle,
                                                      i3c_master_state_machine_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);

    i3c_puint8_to_u32_t dataBuff;
    if (handle->transfer.direction == kI3C_Write)
    {
        /* Make sure there is room in the tx fifo. */
        if (0UL == (stateParams->txCount)--)
        {
            stateParams->state_complete = true;
            return;
        }

        /* Put byte to send in fifo. */
        dataBuff.puint8 = (uint8_t *)handle->transfer.data;
        if (handle->transfer.dataSize > 1U)
        {
            base->MWDATAB = *dataBuff.puint8;
        }
        else
        {
            base->MWDATABE = *dataBuff.puint8;
        }
        dataBuff.u32 = dataBuff.u32 + 1U;
        (handle->transfer.dataSize)--;
        handle->transfer.data = (void *)(dataBuff.puint8);

        /* Move to stop when the transfer is done. */
        if (--handle->remainingBytes == 0UL)
        {
            handle->state = (uint8_t)kWaitForCompletionState;
        }
    }
    else
    {
        /* Make sure there is data in the rx fifo. */
        if (0UL == (stateParams->rxCount)--)
        {
            stateParams->state_complete = true;
            return;
        }

        /* Read byte from fifo. */
        dataBuff.puint8       = (uint8_t *)handle->transfer.data;
        *dataBuff.puint8      = (uint8_t)base->MRDATAB;
        dataBuff.u32          = dataBuff.u32 + 1U;
        handle->transfer.data = (void *)(dataBuff.puint8);

        /* Move to stop when the transfer is done. */
        if (--handle->remainingBytes == 0UL)
        {
            handle->state = (uint8_t)kWaitForCompletionState;
        }

        if ((handle->rxTermOps == kI3C_RxTermLastByte) && (handle->remainingBytes == 1UL))
        {
            base->MCTRL |= I3C_MCTRL_RDTERM(1UL);
        }
    }
}

static void I3C_TransferStateMachineWaitForCompletionState(i3c_master_handle_t *handle,
                                                           i3c_master_state_machine_param_t *stateParams)
{
    /* We stay in this state until the maste complete. */
    if (0UL != (stateParams->status & (uint32_t)kI3C_MasterCompleteFlag))
    {
        handle->state = (uint8_t)kStopState;
    }
    else
    {
        stateParams->state_complete = true;
    }
}

static void I3C_TransferStateMachineStopState(I3C_Type *base,
                                              i3c_master_handle_t *handle,
                                              i3c_master_state_machine_param_t *stateParams)
{
    /* Only issue a stop transition if the caller requested it. */
    if (0UL == (handle->transfer.flags & (uint32_t)kI3C_TransferNoStopFlag))
    {
        /* Make sure there is room in the tx fifo for the stop command. */
        if (0UL == (stateParams->txCount)--)
        {
            stateParams->state_complete = true;
            return;
        }
        if (handle->transfer.busType == kI3C_TypeI3CDdr)
        {
            I3C_MasterEmitRequest(base, kI3C_RequestForceExit);
        }
        else
        {
            (void)I3C_MasterEmitStop(base, false);
        }
    }
    stateParams->state_complete = true;
}

static status_t I3C_RunTransferStateMachine(I3C_Type *base, i3c_master_handle_t *handle, bool *isDone)
{
    i3c_master_state_machine_param_t stateParams;
    (void)memset(&stateParams, 0, sizeof(stateParams));

    stateParams.result         = kStatus_Success;
    stateParams.state_complete = false;

    /* Set default isDone return value. */
    *isDone = false;

    uint32_t errStatus;
    size_t txFifoSize =
        2UL << ((base->SCAPABILITIES & I3C_SCAPABILITIES_FIFOTX_MASK) >> I3C_SCAPABILITIES_FIFOTX_SHIFT);

    /* Check for errors. */
    stateParams.status = (uint32_t)I3C_MasterGetPendingInterrupts(base);
    I3C_MasterClearStatusFlags(base, stateParams.status);

    stateParams.masterState = I3C_MasterGetState(base);
    errStatus               = I3C_MasterGetErrorStatusFlags(base);
    stateParams.result      = I3C_MasterCheckAndClearError(base, errStatus);
    if (kStatus_Success != stateParams.result)
    {
        return stateParams.result;
    }

    if (0UL != (stateParams.status & (uint32_t)kI3C_MasterSlave2MasterFlag))
    {
        if (handle->callback.slave2Master != NULL)
        {
            handle->callback.slave2Master(base, handle->userData);
        }
    }

    if ((0UL != (stateParams.status & (uint32_t)kI3C_MasterSlaveStartFlag)) &&
        (handle->transfer.busType != kI3C_TypeI2C))
    {
        handle->state = (uint8_t)kSlaveStartState;
    }

    if ((stateParams.masterState == kI3C_MasterStateIbiRcv) || (stateParams.masterState == kI3C_MasterStateIbiAck))
    {
        handle->state = (uint8_t)kIBIWonState;
    }

    if (handle->state == (uint8_t)kIdleState)
    {
        return stateParams.result;
    }

    /* Get fifo counts and compute room in tx fifo. */
    I3C_MasterGetFifoCounts(base, &stateParams.rxCount, &stateParams.txCount);
    stateParams.txCount = txFifoSize - stateParams.txCount;

    while (!stateParams.state_complete)
    {
        /* Execute the state. */
        switch (handle->state)
        {
            case (uint8_t)kSlaveStartState:
                /* Emit start + 0x7E */
                I3C_MasterEmitRequest(base, kI3C_RequestAutoIbi);
                handle->state              = (uint8_t)kIBIWonState;
                stateParams.state_complete = true;
                break;

            case (uint8_t)kIBIWonState:
                I3C_TransferStateMachineIBIWonState(base, handle, &stateParams);
                break;

            case (uint8_t)kSendCommandState:
                I3C_TransferStateMachineSendCommandState(base, handle, &stateParams);
                break;

            case (uint8_t)kWaitRepeatedStartCompleteState:
                I3C_TransferStateMachineWaitRepeatedStartCompleteState(base, handle, &stateParams);
                break;

            case (uint8_t)kTransferDataState:
                I3C_TransferStateMachineTransferDataState(base, handle, &stateParams);
                break;

            case (uint8_t)kWaitForCompletionState:
                I3C_TransferStateMachineWaitForCompletionState(handle, &stateParams);
                break;

            case (uint8_t)kStopState:
                I3C_TransferStateMachineStopState(base, handle, &stateParams);
                *isDone = true;
                break;

            default:
                assert(false);
                break;
        }
    }
    return stateParams.result;
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

    if (0UL != (xfer->flags & (uint32_t)kI3C_TransferStartWithBroadcastAddr))
    {
        if (0UL != (xfer->flags & (uint32_t)kI3C_TransferNoStartFlag))
        {
            return kStatus_InvalidArgument;
        }

        if (0UL != (xfer->flags & (uint32_t)kI3C_TransferRepeatedStartFlag))
        {
            return kStatus_InvalidArgument;
        }

        /* Issue 0x7E as start. */
        result = I3C_MasterStart(base, xfer->busType, 0x7E, kI3C_Write);
        if (result != kStatus_Success)
        {
            return result;
        }

        result = I3C_MasterWaitForCtrlDone(base, false);
        if (result != kStatus_Success)
        {
            return result;
        }
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
    else if (xfer->dataSize != 0U)
    {
        handle->state = (uint8_t)kTransferDataState;
    }
    else
    {
        handle->state = (uint8_t)kStopState;
    }

    if ((handle->remainingBytes < 256U) && (direction == kI3C_Read))
    {
        handle->rxTermOps = (handle->rxTermOps == kI3C_RxTermDisable) ? handle->rxTermOps : kI3C_RxAutoTerm;
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

    if ((transfer->flags & (uint32_t)kI3C_TransferDisableRxTermFlag) != 0U)
    {
        handle->rxTermOps = kI3C_RxTermDisable;
    }
    else if (transfer->dataSize <= 255U)
    {
        handle->rxTermOps = kI3C_RxAutoTerm;
    }
    else
    {
        handle->rxTermOps = kI3C_RxTermLastByte;
    }

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
 * param intHandle Pointer to the I3C master driver handle.
 */
void I3C_MasterTransferHandleIRQ(I3C_Type *base, void *intHandle)
{
    i3c_master_handle_t *handle = (i3c_master_handle_t *)intHandle;
    status_t result;
    bool isDone;

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

    slaveConfig->enableSlave = true;
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ) && FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ)
    slaveConfig->isHotJoin   = false;
#endif
    slaveConfig->vendorID    = 0x11BU;
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND)
    slaveConfig->enableRandomPart = false;
#endif
    slaveConfig->partNumber = 0;
    slaveConfig->dcr        = 0; /* Generic device. */
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
 * If FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH defines as 1, this parameter is useless.
 */
void I3C_SlaveInit(I3C_Type *base, const i3c_slave_config_t *slaveConfig, uint32_t slowClock_Hz)
{
    assert(NULL != slaveConfig);
    assert((slowClock_Hz >= 1000000U) || (slowClock_Hz == 0U));

    uint32_t configValue;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) || \
    !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    uint32_t instance = I3C_GetInstance(base);
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate the clock. */
    CLOCK_EnableClock(kI3cClocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_I3C_HAS_NO_RESET) && FSL_FEATURE_I3C_HAS_NO_RESET)
    /* Reset the I3C module */
    RESET_PeripheralReset(kI3cResets[instance]);
#endif

#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
    uint8_t matchCount;
    /* Set as (slowClk(MHz) - 1) to generate 1us clock cycle for IBI request to drive SDA low. Note: Use BAMATCH = 1 to
       generate 1us clock cycle if slow clock is 1MHz. The value of 0 would not give a correct match indication. */
    if (slowClock_Hz != 0U)
    {
        matchCount = (uint8_t)(slowClock_Hz / 1000000UL) - 1U;
        matchCount = (matchCount == 0U) ? 1U : matchCount;
    }
    else
    {
        /* BAMATCH has default value based on Soc default slow clock after reset, using this default value when slowClock_Hz is 0. */
        matchCount = (uint8_t)((base->SCONFIG & I3C_SCONFIG_BAMATCH_MASK) >> I3C_SCONFIG_BAMATCH_SHIFT);
    }
#endif

    configValue = base->SCONFIG;
    configValue &=
        ~(I3C_SCONFIG_SADDR_MASK |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
          I3C_SCONFIG_BAMATCH_MASK |
#endif
          I3C_SCONFIG_OFFLINE_MASK |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND)
          I3C_SCONFIG_IDRAND_MASK |
#endif
#if defined(FSL_FEATURE_I3C_HAS_HDROK) && FSL_FEATURE_I3C_HAS_HDROK
          I3C_SCONFIG_HDROK_MASK |
#else
          I3C_SCONFIG_DDROK_MASK |
#endif
          I3C_SCONFIG_S0IGNORE_MASK | I3C_SCONFIG_MATCHSS_MASK | I3C_SCONFIG_NACK_MASK | I3C_SCONFIG_SLVENA_MASK);
    configValue |= I3C_SCONFIG_SADDR(slaveConfig->staticAddr) |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH)
                   I3C_SCONFIG_BAMATCH(matchCount) |
#endif
                   I3C_SCONFIG_OFFLINE(slaveConfig->offline) |
#if !(defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND)
                   I3C_SCONFIG_IDRAND(slaveConfig->enableRandomPart) |
#endif
#if defined(FSL_FEATURE_I3C_HAS_HDROK) && FSL_FEATURE_I3C_HAS_HDROK
                   I3C_SCONFIG_HDROK((0U != (slaveConfig->hdrMode & (uint8_t)kI3C_HDRModeDDR)) ? 1U : 0U) |
#else
                   I3C_SCONFIG_DDROK((0U != (slaveConfig->hdrMode & (uint8_t)kI3C_HDRModeDDR)) ? 1U : 0U) |
#endif
                   I3C_SCONFIG_S0IGNORE(slaveConfig->ignoreS0S1Error) |
                   I3C_SCONFIG_MATCHSS(slaveConfig->matchSlaveStartStop) |
                   I3C_SCONFIG_NACK(slaveConfig->nakAllRequest) | I3C_SCONFIG_SLVENA(slaveConfig->enableSlave);

    base->SVENDORID &= ~I3C_SVENDORID_VID_MASK;
    base->SVENDORID |= I3C_SVENDORID_VID(slaveConfig->vendorID);

#if defined(FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND) && FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND
    base->SIDPARTNO = slaveConfig->partNumber;
#else
    if (!slaveConfig->enableRandomPart)
    {
        base->SIDPARTNO = slaveConfig->partNumber;
    }
#endif

    base->SIDEXT &= ~(I3C_SIDEXT_BCR_MASK | I3C_SIDEXT_DCR_MASK);
    base->SIDEXT |= I3C_SIDEXT_BCR(slaveConfig->bcr) | I3C_SIDEXT_DCR(slaveConfig->dcr);

    base->SMAXLIMITS &= ~(I3C_SMAXLIMITS_MAXRD_MASK | I3C_SMAXLIMITS_MAXWR_MASK);
    base->SMAXLIMITS |=
        (I3C_SMAXLIMITS_MAXRD(slaveConfig->maxReadLength) | I3C_SMAXLIMITS_MAXWR(slaveConfig->maxWriteLength));

#if !(defined(FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ) && FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ)
    if (slaveConfig->isHotJoin)
    {
        I3C_SlaveRequestEvent(base, kI3C_SlaveEventHotJoinReq);
    }
#endif
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

#if !(defined(FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ) && FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ)
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
 * deprecated Do not use this function. It has been superseded by @ref I3C_SlaveRequestIBIWithData.
 *
 * param base The I3C peripheral base address.
 * param data IBI data
 * param dataSize IBI data size.
 */
void I3C_SlaveRequestIBIWithSingleData(I3C_Type *base, uint8_t data, size_t dataSize)
{
    uint32_t ctrlValue = base->SCTRL;

    ctrlValue &= ~(I3C_SCTRL_EVENT_MASK | I3C_SCTRL_IBIDATA_MASK);
    ctrlValue |= I3C_SCTRL_EVENT(1U) | I3C_SCTRL_IBIDATA(data);

    base->SCTRL = ctrlValue;
}

/*!
 * brief I3C slave request IBI event with data payload(mandatory and extended).
 *
 * param base The I3C peripheral base address.
 * param data Pointer to IBI data to be sent in the request.
 * param dataSize IBI data size.
 */
void I3C_SlaveRequestIBIWithData(I3C_Type *base, uint8_t *data, size_t dataSize)
{
    assert((dataSize > 0U) && (dataSize <= 8U));

    uint32_t ctrlValue;

#if (defined(I3C_IBIEXT1_MAX_MASK) && I3C_IBIEXT1_MAX_MASK)
    if (dataSize > 1U)
    {
        ctrlValue = I3C_IBIEXT1_EXT1(data[1]);
        if (dataSize > 2U)
        {
            ctrlValue |= I3C_IBIEXT1_EXT2(data[2]);
        }
        if (dataSize > 3U)
        {
            ctrlValue |= I3C_IBIEXT1_EXT3(data[3]);
        }
        ctrlValue |= I3C_IBIEXT1_CNT(dataSize - 1U);
        base->IBIEXT1 = ctrlValue;
    }

    if (dataSize > 4U)
    {
        ctrlValue = I3C_IBIEXT2_EXT4(data[4]);
        if (dataSize > 5U)
        {
            ctrlValue |= I3C_IBIEXT2_EXT5(data[5]);
        }
        if (dataSize > 6U)
        {
            ctrlValue |= I3C_IBIEXT2_EXT6(data[6]);
        }
        if (dataSize > 7U)
        {
            ctrlValue |= I3C_IBIEXT2_EXT7(data[7]);
        }
        base->IBIEXT2 = ctrlValue;
    }
#endif

    ctrlValue = base->SCTRL;
#if (defined(I3C_IBIEXT1_MAX_MASK) && I3C_IBIEXT1_MAX_MASK)
    ctrlValue &= ~(I3C_SCTRL_EVENT_MASK | I3C_SCTRL_IBIDATA_MASK | I3C_SCTRL_EXTDATA_MASK);
    ctrlValue |= I3C_SCTRL_EVENT(1U) | I3C_SCTRL_IBIDATA(data[0]) | I3C_SCTRL_EXTDATA(dataSize > 1U);
#else
    ctrlValue &= ~(I3C_SCTRL_EVENT_MASK | I3C_SCTRL_IBIDATA_MASK);
    ctrlValue |= I3C_SCTRL_EVENT(1U) | I3C_SCTRL_IBIDATA(data[0]);
#endif
    base->SCTRL = ctrlValue;
}
#endif /* !(defined(FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ) && FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ) */

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

    /* Save Tx FIFO Size. */
    handle->txFifoSize =
        2U << ((base->SCAPABILITIES & I3C_SCAPABILITIES_FIFOTX_MASK) >> I3C_SCAPABILITIES_FIFOTX_SHIFT);

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

static bool I3C_SlaveTransferHandleGetStatusFlags(I3C_Type *base,
                                                  i3c_slave_handle_t *handle,
                                                  i3c_slave_handleIrq_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    /* Check for a valid handle in case of a spurious interrupt. */
    uint32_t errFlags;
    stateParams->flags = I3C_SlaveGetStatusFlags(base);
    errFlags           = I3C_SlaveGetErrorStatusFlags(base);

    stateParams->pendingInts = I3C_SlaveGetPendingInterrupts(base);
    stateParams->enabledInts = I3C_SlaveGetEnabledInterrupts(base);

    if (0UL != (errFlags & (uint32_t)kSlaveErrorFlags))
    {
        handle->transfer.event            = (uint32_t)kI3C_SlaveCompletionEvent;
        handle->transfer.completionStatus = I3C_SlaveCheckAndClearError(base, errFlags);

        if ((0UL != (handle->eventMask & (uint32_t)kI3C_SlaveCompletionEvent)) && (NULL != handle->callback))
        {
            handle->callback(base, &handle->transfer, handle->userData);
        }
        return false;
    }
    return true;
}

static void I3C_SlaveTransferHandleBusStart(I3C_Type *base, i3c_slave_transfer_t *xfer, uint32_t *pendingInts)
{
    base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK;
    xfer->txDataSize = 0;
    I3C_SlaveEnableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
    (*pendingInts) |= (uint32_t)kI3C_SlaveTxReadyFlag;
}

static void I3C_SlaveTransferHandleEventSent(I3C_Type *base, i3c_slave_handle_t *handle, i3c_slave_transfer_t *xfer)
{
    xfer->event = (uint32_t)kI3C_SlaveRequestSentEvent;
    if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
    {
        handle->callback(base, xfer, handle->userData);
    }
}

static void I3C_SlaveTransferHandleReceivedCCC(I3C_Type *base, i3c_slave_handle_t *handle, i3c_slave_transfer_t *xfer)
{
    handle->isBusy = true;
    xfer->event    = (uint32_t)kI3C_SlaveReceivedCCCEvent;
    if ((0UL != (handle->eventMask & xfer->event)) && (NULL != handle->callback))
    {
        handle->callback(base, xfer, handle->userData);
    }
}

static void I3C_SlaveTransferHandleBusStop(I3C_Type *base,
                                           i3c_slave_handle_t *handle,
                                           i3c_slave_handleIrq_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
    stateParams->pendingInts &= ~(uint32_t)kI3C_SlaveTxReadyFlag;
    base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK | I3C_SDATACTRL_FLUSHFB_MASK;
    if (handle->isBusy)
    {
        handle->transfer.event            = (uint32_t)kI3C_SlaveCompletionEvent;
        handle->transfer.completionStatus = kStatus_Success;
        handle->transfer.transferredCount = handle->transferredCount;
        handle->isBusy                    = false;

        if (handle->wasTransmit)
        {
            /* Subtract one from the transmit count to offset the fact that I3C asserts the */
            /* tx flag before it sees the nack from the master-receiver, thus causing one more */
            /* count that the master actually receives. */
            --handle->transfer.transferredCount;
            handle->wasTransmit = false;
        }

        if ((0UL != (handle->eventMask & handle->transfer.event)) && (NULL != handle->callback))
        {
            handle->callback(base, &handle->transfer, handle->userData);
        }

        /* Clean up transfer info on completion, after the callback has been invoked. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));
    }
}

static void I3C_SlaveTransferHandleMatched(I3C_Type *base, i3c_slave_handle_t *handle, i3c_slave_transfer_t *xfer)
{
    assert(NULL != base && NULL != handle && NULL != xfer);
    xfer->event    = (uint32_t)kI3C_SlaveAddressMatchEvent;
    handle->isBusy = true;
    if ((0UL != (handle->eventMask & (uint32_t)kI3C_SlaveAddressMatchEvent)) && (NULL != handle->callback))
    {
        handle->callback(base, xfer, handle->userData);
    }
}

static void I3C_SlaveTransferHandleTxReady(I3C_Type *base,
                                           i3c_slave_handle_t *handle,
                                           i3c_slave_handleIrq_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    handle->wasTransmit = true;

    /* If we're out of data, invoke callback to get more. */
    if ((NULL == handle->transfer.txData) || (0UL == handle->transfer.txDataSize))
    {
        handle->transfer.event = (uint32_t)kI3C_SlaveTransmitEvent;
        if (0UL != (stateParams->flags & (uint32_t)kI3C_SlaveBusHDRModeFlag))
        {
            handle->transfer.event |= (uint32_t)kI3C_SlaveHDRCommandMatchEvent;
            handle->isBusy = true;
        }
        if (NULL != handle->callback)
        {
            handle->callback(base, &handle->transfer, handle->userData);
        }

        /* Clear the transferred count now that we have a new buffer. */
        handle->transferredCount = 0;
    }

    if ((NULL == handle->transfer.txData) || (0UL == handle->transfer.txDataSize))
    {
        I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
        (stateParams->pendingInts) &= ~(uint32_t)kI3C_SlaveTxReadyFlag;
    }

    /* Transmit a byte. */
    while ((handle->transfer.txDataSize != 0UL) && ((stateParams->txCount) != 0U))
    {
        if (handle->transfer.txDataSize > 1UL)
        {
            base->SWDATAB = *handle->transfer.txData++;
        }
        else
        {
            base->SWDATABE = *handle->transfer.txData++;
            I3C_SlaveDisableInterrupts(base, (uint32_t)kI3C_SlaveTxReadyFlag);
        }
        --(handle->transfer.txDataSize);
        ++(handle->transferredCount);
        (stateParams->txCount)--;
    }
}

static void I3C_SlaveTransferHandleRxReady(I3C_Type *base,
                                           i3c_slave_handle_t *handle,
                                           i3c_slave_handleIrq_param_t *stateParams)
{
    assert(NULL != base && NULL != handle && NULL != stateParams);
    /* If we're out of room in the buffer, invoke callback to get another. */
    if ((NULL == handle->transfer.rxData) || (0UL == handle->transfer.rxDataSize))
    {
        handle->transfer.event = (uint32_t)kI3C_SlaveReceiveEvent;
        if (0UL != (stateParams->flags & (uint32_t)kI3C_SlaveBusHDRModeFlag))
        {
            handle->transfer.event |= (uint32_t)kI3C_SlaveHDRCommandMatchEvent;
            handle->isBusy = true;
        }
        if (NULL != handle->callback)
        {
            handle->callback(base, &handle->transfer, handle->userData);
        }
        handle->transferredCount = 0;
    }
    /* Receive a byte. */
    while ((stateParams->rxCount != 0U) && ((handle->transfer.rxData != NULL) && (handle->transfer.rxDataSize != 0UL)))
    {
        *(handle->transfer.rxData++) = (uint8_t)base->SRDATAB;
        --(handle->transfer.rxDataSize);
        ++(handle->transferredCount);
        (stateParams->rxCount)--;
    }
}

/*!
 * brief Reusable routine to handle slave interrupts.
 * note This function does not need to be called unless you are reimplementing the
 *  non blocking API's interrupt handler routines to add special functionality.
 * param base The I3C peripheral base address.
 * param intHandle Pointer to #i3c_slave_handle_t structure which stores the transfer state.
 */
void I3C_SlaveTransferHandleIRQ(I3C_Type *base, void *intHandle)
{
    i3c_slave_handleIrq_param_t stateParams;

    (void)memset(&stateParams, 0, sizeof(stateParams));
    i3c_slave_handle_t *handle = (i3c_slave_handle_t *)intHandle;

    /* Check for a valid handle in case of a spurious interrupt. */
    if (NULL == handle)
    {
        return;
    }

    /* Get status flags. */
    if (false == I3C_SlaveTransferHandleGetStatusFlags(base, handle, &stateParams))
    {
        return;
    }

    /* Clear status flags. */
    I3C_SlaveClearStatusFlags(base, stateParams.flags);

    if (0UL != (stateParams.flags & (uint32_t)kI3C_SlaveBusStartFlag))
    {
        I3C_SlaveTransferHandleBusStart(base, &handle->transfer, &stateParams.pendingInts);
    }

    if (0UL != (stateParams.flags & (uint32_t)kI3C_SlaveEventSentFlag))
    {
        I3C_SlaveTransferHandleEventSent(base, handle, &handle->transfer);
    }

    if (0UL != (stateParams.flags & (uint32_t)kI3C_SlaveReceivedCCCFlag))
    {
        I3C_SlaveTransferHandleReceivedCCC(base, handle, &handle->transfer);
    }

    if (0UL != (stateParams.flags & (uint32_t)kI3C_SlaveMatchedFlag))
    {
        I3C_SlaveTransferHandleMatched(base, handle, &handle->transfer);
    }

    /* Get fifo counts and compute room in tx fifo. */
    I3C_SlaveGetFifoCounts(base, &stateParams.rxCount, &stateParams.txCount);
    stateParams.txCount = handle->txFifoSize - stateParams.txCount;

    /* Handle transmit and receive. */
    if ((0UL != (stateParams.flags & (uint32_t)kI3C_SlaveTxReadyFlag)) &&
        (0UL != (stateParams.pendingInts & (uint32_t)kI3C_SlaveTxReadyFlag)))
    {
        I3C_SlaveTransferHandleTxReady(base, handle, &stateParams);
    }

    if ((0UL != (stateParams.flags & (uint32_t)kI3C_SlaveRxReadyFlag)) &&
        (0UL != (stateParams.enabledInts & (uint32_t)kI3C_SlaveRxReadyFlag)))
    {
        I3C_SlaveTransferHandleRxReady(base, handle, &stateParams);
    }

    /* Handle stop event. */
    if (0UL != (stateParams.flags & (uint32_t)kI3C_SlaveBusStopFlag))
    {
        I3C_SlaveTransferHandleBusStop(base, handle, &stateParams);
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

#if defined(I3C2)
/* Implementation of I3C2 handler named in startup code. */
void I3C2_DriverIRQHandler(void);
void I3C2_DriverIRQHandler(void)
{
    I3C_CommonIRQHandler(I3C2, 2);
}
#endif

#if defined(I3C3)
/* Implementation of I3C3 handler named in startup code. */
void I3C3_DriverIRQHandler(void);
void I3C3_DriverIRQHandler(void)
{
    I3C_CommonIRQHandler(I3C3, 3);
}
#endif
