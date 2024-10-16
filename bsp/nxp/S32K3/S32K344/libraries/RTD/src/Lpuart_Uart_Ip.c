/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXIO
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/**
*   @file     Lpuart_Uart_Ip.c
*   @defgroup lpuart_uart_ip Lpuart UART IPL
*   @addtogroup  lpuart_uart_ip Lpuart UART IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Lpuart_Uart_Ip.h"
#include "Lpuart_Uart_Ip_HwAccess.h"
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    #include "Dma_Ip.h"
#endif

#ifdef LPUART_UART_IP_DEV_ERROR_DETECT
    #if (LPUART_UART_IP_DEV_ERROR_DETECT == STD_ON)
        #include "Devassert.h"
    #endif /* (STD_ON == LPUART_UART_IP_DEV_ERROR_DETECT) */
#endif /* idfef LPUART_UART_IP_DEV_ERROR_DETECT */

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define LPUART_UART_IP_VENDOR_ID_C                      43
#define LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define LPUART_UART_IP_AR_RELEASE_MINOR_VERSION_C       7
#define LPUART_UART_IP_AR_RELEASE_REVISION_VERSION_C    0
#define LPUART_UART_IP_SW_MAJOR_VERSION_C               5
#define LPUART_UART_IP_SW_MINOR_VERSION_C               0
#define LPUART_UART_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Lpuart_Uart_Ip.h */
#if (LPUART_UART_IP_VENDOR_ID_C != LPUART_UART_IP_VENDOR_ID)
    #error "Lpuart_Uart_Ip.c and Lpuart_Uart_Ip.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION_C    != LPUART_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_REVISION_VERSION_C != LPUART_UART_IP_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip.c and Lpuart_Uart_Ip.h are different"
#endif
#if ((LPUART_UART_IP_SW_MAJOR_VERSION_C != LPUART_UART_IP_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_SW_MINOR_VERSION_C != LPUART_UART_IP_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_SW_PATCH_VERSION_C != LPUART_UART_IP_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lpuart_Uart_Ip.c and Lpuart_Uart_Ip.h are different"
#endif

/* Checks against Lpuart_Uart_Ip_HwAccess.h */
#if (LPUART_UART_IP_VENDOR_ID_C != LPUART_UART_IP_HWACCESS_VENDOR_ID)
    #error "Lpuart_Uart_Ip.c and Lpuart_Uart_Ip_HwAccess.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != LPUART_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION_C    != LPUART_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_AR_RELEASE_REVISION_VERSION_C != LPUART_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip.c and Lpuart_Uart_Ip_HwAccess.h are different"
#endif
#if ((LPUART_UART_IP_SW_MAJOR_VERSION_C != LPUART_UART_IP_HWACCESS_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_SW_MINOR_VERSION_C != LPUART_UART_IP_HWACCESS_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_SW_PATCH_VERSION_C != LPUART_UART_IP_HWACCESS_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lpuart_Uart_Ip.c and Lpuart_Uart_Ip_HwAccess.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Dma_Ip.h */
    #if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
        #if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION_C != DMA_IP_AR_RELEASE_MAJOR_VERSION) || \
             (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION_C != DMA_IP_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of Lpuart_Uart_Ip.c and Dma_Ip.h are different"
        #endif
    #endif
    /* Checks against Devassert.h */
    #ifdef LPUART_UART_IP_DEV_ERROR_DETECT
    #if (STD_ON == LPUART_UART_IP_DEV_ERROR_DETECT)
        /* Check if Lpuart_Uart_Ip.c file and Devassert.h file are of the same Autosar version */
        #if ((LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
         (LPUART_UART_IP_AR_RELEASE_MINOR_VERSION_C    != DEVASSERT_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Lpuart_Uart_Ip.c and Devassert.h are different"
        #endif
    #endif /* (STD_ON == LPUART_UART_IP_DEV_ERROR_DETECT) */
    #endif /* #ifdef LPUART_UART_IP_DEV_ERROR_DETECT */


#endif
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

#ifdef LPUART_UART_IP_DEV_ERROR_DETECT
    #if (LPUART_UART_IP_DEV_ERROR_DETECT == STD_ON)
        #define LPUART_UART_IP_DEV_ASSERT(x)      DevAssert(x)
    #else
        #define LPUART_UART_IP_DEV_ASSERT(x)      (void)(x)
    #endif
#endif

/* @brief Address of the least significant byte or word in a 32-bit register (depends on endianness) */
#define LPUART_UART_IP_LSBW_ADDR(reg)  ((uint32)(&(reg)))

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    #define LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION             (10U)
    #define LPUART_UART_IP_DMA_LEAST_CONFIG_LIST_DIMENSION       (2U)
#endif

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/
#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

/** @brief Array of UART driver runtime state structures */
Lpuart_Uart_Ip_StateStructureType Lpuart_Uart_Ip_apStateStructure[LPUART_UART_IP_NUMBER_OF_INSTANCES];

/** @brief User config structure. */
static const Lpuart_Uart_Ip_UserConfigType * Lpuart_Uart_Ip_apUserConfig[LPUART_INSTANCE_COUNT];

/* Pointer to lpuart runtime state structure */
static Lpuart_Uart_Ip_StateStructureType * Lpuart_Uart_Ip_apStateStructuresArray[LPUART_INSTANCE_COUNT];

#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_UNSPECIFIED
#include "Uart_MemMap.h"

/* Table of base addresses for lpuart instances. */
static LPUART_Type * const Lpuart_Uart_Ip_apBases[LPUART_INSTANCE_COUNT] = LPUART_IP_BASE_PTRS;

#define UART_STOP_SEC_CONST_UNSPECIFIED
#include "Uart_MemMap.h"

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
#define UART_START_SEC_CONST_BOOLEAN
#include "Uart_MemMap.h"

/** @brief Table storing timeout interrupt capabilities for LPUART instances. */
static const boolean Lpuart_Uart_Ip_InstHasTimeoutInterruptEnabled[LPUART_INSTANCE_COUNT] = LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT_PER_INSTANCE;

#define UART_STOP_SEC_CONST_BOOLEAN
#include "Uart_MemMap.h"
#endif

#if (LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK == STD_ON)
#define UART_START_SEC_CONST_BOOLEAN
#include "Uart_MemMap.h"

/** @brief Table storing DMA capabilities for LPUART instances. */
static const boolean Lpuart_Uart_Ip_InstHasLoopbackEnabled[LPUART_INSTANCE_COUNT] = LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK_PER_INSTANCE;

#define UART_STOP_SEC_CONST_BOOLEAN
#include "Uart_MemMap.h"
#endif
/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartSendDataUsingInt(const uint8 Instance,
                                                                      const uint8 * TxBuff,
                                                                      const uint32 TxSize);
static void Lpuart_Uart_Ip_CompleteSendDataUsingInt(const uint8 Instance);
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartReceiveDataUsingInt(const uint8 Instance,
                                                                         uint8 * RxBuff,
                                                                         const uint32 RxSize);
static void Lpuart_Uart_Ip_CompleteReceiveDataUsingInt(const uint8 Instance);
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartSendDataUsingDma(const uint8 Instance,
                                                                      const uint8 * TxBuff,
                                                                      const uint32 TxSize);
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartReceiveDataUsingDma(const uint8 Instance,
                                                                         uint8 * RxBuff,
                                                                         const uint32 RxSize);
static void Lpuart_Uart_Ip_SetupIntDmaMode(const uint8 Instance, boolean Enable);
static void Lpuart_Uart_Ip_CompleteTxOperationUsingDma(const uint8 Instance);
static void Lpuart_Uart_Ip_CompleteRxOperationUsingDma(const uint8 Instance);
#endif

static void Lpuart_Uart_Ip_PutData(const uint8 Instance);
static void Lpuart_Uart_Ip_GetData(const uint8 Instance);
static void Lpuart_Uart_Ip_RxIrqHandler(const uint8 Instance);
static void Lpuart_Uart_Ip_TxEmptyIrqHandler(const uint8 Instance);
static void Lpuart_Uart_Ip_TxCompleteIrqHandler(const uint8 Instance);
static void Lpuart_Uart_Ip_ErrIrqHandler(const uint8 Instance);
static void Lpuart_Uart_Ip_StartGetData(const uint8 Instance, const uint32 Timeout);
static void Lpuart_Uart_Ip_SetUp_Baudrate(const uint8 Instance);
static void Lpuart_Uart_Ip_SetUp_Parity(const uint8 Instance);
static void Lpuart_Uart_Ip_TxRxIrqHandler(const uint8 Instance);
static void Lpuart_Uart_Ip_SyncSendData(const uint8 Instance, const uint32 Timeout);

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_Init
 * Description   : This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPUART module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the partition, and enable the
 * LPUART module transmitter and receiver.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_Init_Activity*/
void Lpuart_Uart_Ip_Init(const uint8 Instance, const Lpuart_Uart_Ip_UserConfigType * UserConfig)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(UserConfig != NULL_PTR);
    /* Check if current instance is already initialized. */
    LPUART_UART_IP_DEV_ASSERT(NULL_PTR == Lpuart_Uart_Ip_apStateStructuresArray[Instance]);
    /* Check if Baudrate parameters are valid value */
    LPUART_UART_IP_DEV_ASSERT(UserConfig->BaudOverSamplingRatio <= 0x20U);
    LPUART_UART_IP_DEV_ASSERT((UserConfig->BaudRateDivisor <= 0x1FFFU) && (UserConfig->BaudRateDivisor >= 1U));

    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    Lpuart_Uart_Ip_StateStructureType *UartStatePtr;
    uint32 Index;
    uint8 *ClearStructPtr;

    Lpuart_Uart_Ip_apStateStructuresArray[Instance] = UserConfig->StateStruct;
    UartStatePtr = Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    Lpuart_Uart_Ip_apUserConfig[Instance] = UserConfig;
    ClearStructPtr = (uint8 *)UartStatePtr;

#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    /* In DMA mode, only 7-bits and 8-bits chars are supported */
    LPUART_UART_IP_DEV_ASSERT((UserConfig->TransferType != LPUART_UART_IP_USING_DMA) || \
                              ((LPUART_UART_IP_7_BITS_PER_CHAR == UserConfig->BitCountPerChar) || \
                               (LPUART_UART_IP_8_BITS_PER_CHAR == UserConfig->BitCountPerChar) \
                              ) \
                             );

#endif /* (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON) */


    /* For 10 bits per char, parity bit cannot be enabled */
    LPUART_UART_IP_DEV_ASSERT((UserConfig->BitCountPerChar != LPUART_UART_IP_10_BITS_PER_CHAR) || \
                              (LPUART_UART_IP_PARITY_DISABLED == UserConfig->ParityMode) \
                             );

    /* Clear the state struct for this instance. */
    for (Index = 0; Index < sizeof(Lpuart_Uart_Ip_StateStructureType); Index++)
    {
        ClearStructPtr[Index] = 0;
    }


    /* Initialize the LPUART instance */
    Lpuart_Uart_Ip_Hw_Init(Base);

#if (LPUART_UART_IP_ENABLE_INTERNAL_LOOPBACK == STD_ON)
    if (Lpuart_Uart_Ip_InstHasLoopbackEnabled[Instance])
    {
        Lpuart_Uart_Ip_EnableInternalLoopback(Base);
    }
#endif

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    if (Lpuart_Uart_Ip_InstHasTimeoutInterruptEnabled[Instance])
    {
        Lpuart_Uart_Ip_SetupIdleInterrupt(Base);
    }
#endif

    Lpuart_Uart_Ip_SetUp_Baudrate(Instance);

    Lpuart_Uart_Ip_SetUp_Parity(Instance);

    Lpuart_Uart_Ip_SetStopBitCount(Base, UserConfig->StopBitsCount);

    /* Initialize last driver operation status */
    UartStatePtr->TransmitStatus = LPUART_UART_IP_STATUS_SUCCESS;
    UartStatePtr->ReceiveStatus = LPUART_UART_IP_STATUS_SUCCESS;
    /* Set the initial baudrate from user's structure */
    UartStatePtr->BaudRate = UserConfig->BaudRate;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_Deinit
 * Description   : This function shuts down the UART by disabling interrupts and
 *                 transmitter/receiver.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_Deinit_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_Deinit(const uint8 Instance)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    const Lpuart_Uart_Ip_StateStructureType * UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    Lpuart_Uart_Ip_StatusType RetVal;

    /* Check if current instance is already de-initialized or is gated.*/
    LPUART_UART_IP_DEV_ASSERT(Lpuart_Uart_Ip_apStateStructuresArray[Instance] != NULL_PTR);

    Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, LPUART_UART_IP_TIMEOUT_VALUE_US, LPUART_UART_IP_TIMEOUT_TYPE);
    /* Wait until the data is completely shifted out of shift register */
    while ((UartState->IsTxBusy || UartState->IsRxBusy) && \
           !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {}
    /* Disable Tx data register empty and transmission complete interrupt */
    if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {
        RetVal = LPUART_UART_IP_STATUS_ERROR;
    }
    else
    {
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_DATA_REG_EMPTY, FALSE);
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_COMPLETE, FALSE);

        /* Disble  Rx data register full */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_DATA_REG_FULL, FALSE);

        /* Disable error interrupts */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_OVERRUN, FALSE);
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_PARITY_ERR_FLAG, FALSE);
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_NOISE_ERR_FLAG, FALSE);
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_FRAME_ERR_FLAG, FALSE);

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    if (Lpuart_Uart_Ip_InstHasTimeoutInterruptEnabled[Instance])
    {
        /* Disable timeout interrupt */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TIMEOUT, FALSE);
    }
#endif

        /* Clear our saved pointer to the state structure */
        Lpuart_Uart_Ip_apStateStructuresArray[Instance] = NULL_PTR;
        RetVal = LPUART_UART_IP_STATUS_SUCCESS;
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SyncSend
 * Description   : Send out multiple bytes of data using polling method.
 *
 *END**************************************************************************/
 /* @implements     Lpuart_Uart_Ip_SyncSend_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_SyncSend(const uint8 Instance, const uint8 *TxBuff, const uint32 TxSize, const uint32 Timeout)
{
    /* Check the validity of the parameters */
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(TxBuff != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(TxSize > 0U);

    LPUART_Type * Base;
    Lpuart_Uart_Ip_StateStructureType * UartState;
    boolean IsReturn = FALSE;
    Lpuart_Uart_Ip_StatusType RetVal = LPUART_UART_IP_STATUS_SUCCESS;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_00();
    /* Check driver is not busy transmitting data from a previous asynchronous call */
    if (UartState->IsTxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_00();
        RetVal = LPUART_UART_IP_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartState->IsTxBusy = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_00();
        UartState->TxBuff = TxBuff;
        UartState->TxSize = TxSize;

        UartState->TransmitStatus = LPUART_UART_IP_STATUS_BUSY;

        /* Disble  Tx data register empty and transmission complete interrupt */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_DATA_REG_EMPTY, FALSE);
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_COMPLETE, FALSE);

        /* Enable the LPUART transmitter */
        Lpuart_Uart_Ip_SetTransmitterCmd(Base, TRUE);

        /* Process for sync send data*/
        Lpuart_Uart_Ip_SyncSendData(Instance, Timeout);

        /* Disable the LPUART transmitter */
        Lpuart_Uart_Ip_SetTransmitterCmd(Base, FALSE);

        UartState->IsTxBusy = FALSE;
        RetVal = UartState->TransmitStatus;
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_AsyncSend
 * Description   : This function sends data out through the LPUART module using
 * non-blocking method. The function will return immediately after calling this
 * function.
 *
 *END**************************************************************************/
 /* @implements     Lpuart_Uart_Ip_AsyncSend_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AsyncSend(const uint8 Instance,
                                                   const uint8 * TxBuff,
                                                   const uint32 TxSize)
{
    /* Check the validity of the parameters */
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(TxBuff != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(TxSize > 0U);
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    Lpuart_Uart_Ip_StateStructureType * UartState;
    Lpuart_Uart_Ip_StatusType RetVal = LPUART_UART_IP_STATUS_SUCCESS;
    boolean IsReturn = FALSE;

    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_01();
    /* Check it's not busy transmitting data from a previous function call */
    if (UartState->IsTxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_01();
        RetVal = LPUART_UART_IP_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartState->IsTxBusy = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_01();

        LPUART_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);
        LPUART_UART_IP_DEV_ASSERT((LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType) ||
                                  (LPUART_UART_IP_USING_DMA == UartUserCfg->TransferType)
                                 );
        if (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType)
        {
            /* Start the transmission process using interrupts */
            RetVal = Lpuart_Uart_Ip_StartSendDataUsingInt(Instance, TxBuff, TxSize);
        }
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
        else
        {
            /* Start the transmission process using DMA */
            RetVal = Lpuart_Uart_Ip_StartSendDataUsingDma(Instance, TxBuff, TxSize);
        }
#endif
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_GetTransmitStatus
 * Description   : This function returns whether the previous LPUART transmit has
 * finished. When performing non-blocking transmit, the user can call this
 * function to ascertain the state of the current transmission:
 * in progress (or busy) or complete (success). In addition, if the transmission
 * is still in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_GetTransmitStatus_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_GetTransmitStatus(const uint8 Instance, uint32 * BytesRemaining)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    const Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    Lpuart_Uart_Ip_StatusType localStatus;
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    const Dma_Ip_LogicChannelInfoParamType DmaLogicChnParam = DMA_IP_CH_GET_CURRENT_ITER_COUNT;
#endif

    UartState = (const Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);

    /* Fill in the bytes not transferred yet. */
    if ((BytesRemaining != NULL_PTR) && (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType))
    {
        SchM_Enter_Uart_UART_EXCLUSIVE_AREA_05();
        localStatus = UartState->TransmitStatus;
        if (UartState->IsTxBusy)
        {
            /* In interrupt-based communication, the remaining bytes are retrieved
            * from the state structure
            */
            *BytesRemaining = UartState->TxSize;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
        }
        else
        {
            *BytesRemaining = 0;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
        }
    }
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    else if ((BytesRemaining != NULL_PTR) && (LPUART_UART_IP_USING_DMA == UartUserCfg->TransferType))
    {
        SchM_Enter_Uart_UART_EXCLUSIVE_AREA_05();
        localStatus = UartState->TransmitStatus;
        if (UartState->IsTxBusy)
        {
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
            /* In DMA-based communication, the remaining bytes are retrieved
            * from the current DMA major loop count
            */
            (void)Dma_Ip_GetLogicChannelParam(UartUserCfg->TxDMAChannel, DmaLogicChnParam, BytesRemaining);
        }
        else
        {
            *BytesRemaining = 0;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
        }
    }
#endif
    else
    {
        SchM_Enter_Uart_UART_EXCLUSIVE_AREA_05();
        localStatus = UartState->TransmitStatus;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
    }

    return localStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_AbortSendingData
 * Description   : This function terminates an non-blocking LPUART transmission
 * early. During a non-blocking LPUART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_AbortSendingData_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AbortSendingData(const uint8 Instance)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);

    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    boolean IsReturn = FALSE;
    Lpuart_Uart_Ip_StatusType RetVal = LPUART_UART_IP_STATUS_SUCCESS;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);

    /* Check if a transfer is running. */
    if (!UartState->IsTxBusy)
    {
        RetVal = LPUART_UART_IP_STATUS_SUCCESS;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        /* Update the tx status */
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_ABORTED;

        /* Stop the running transfer. */
        if (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType)
        {
            Lpuart_Uart_Ip_CompleteSendDataUsingInt(Instance);
        }
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
        else
        {
            /* Release the DMA channel */
            (void)Dma_Ip_SetLogicChannelCommand(UartUserCfg->TxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
            Lpuart_Uart_Ip_CompleteSendUsingDma(Instance);
        }
#endif
        /* Flush the Tx Buffer */
        Lpuart_Uart_Ip_FlushTxBuffer(Base);
    }

    if (LPUART_UART_IP_STATUS_TIMEOUT == UartState->TransmitStatus)
    {
        RetVal = LPUART_UART_IP_STATUS_ERROR;
    }

    return RetVal;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SyncReceive
 * Description   : Receive multiple bytes of data using polling method.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_SyncReceive_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_SyncReceive(const uint8 Instance, uint8 *RxBuff, const uint32 RxSize, const uint32 Timeout)
{
    /* Check the validity of the parameters */
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(RxBuff != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(RxSize > 0U);

    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    Lpuart_Uart_Ip_StateStructureType * UartState;
    boolean IsReturn = FALSE;
    Lpuart_Uart_Ip_StatusType RetVal = LPUART_UART_IP_STATUS_SUCCESS;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_02();
    /* Check driver is not busy receiving data from a previous asynchronous call */
    if (UartState->IsRxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_02();
        RetVal = LPUART_UART_IP_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartState->IsRxBusy = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_02();
        UartState->RxBuff = RxBuff;
        UartState->RxSize = RxSize;
        UartState->ReceiveStatus = LPUART_UART_IP_STATUS_BUSY;

        /* Disble  Rx data register full */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_DATA_REG_FULL, FALSE);
        /* Enable the LPUART receiver */
        Lpuart_Uart_Ip_SetReceiverCmd((LPUART_Type *)Base, TRUE);

        Lpuart_Uart_Ip_StartGetData(Instance, Timeout);

        /* Check other success receiving case*/
        if (LPUART_UART_IP_STATUS_BUSY == UartState->ReceiveStatus)
        {
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_SUCCESS;
        }

        if ((0U == UartState->RxSize) && (LPUART_UART_IP_STATUS_RX_OVERRUN == UartState->ReceiveStatus))
        {
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_SUCCESS;
        }

        /* Disable the LPUART receiver */
        Lpuart_Uart_Ip_SetReceiverCmd((LPUART_Type *)Base, FALSE);

        UartState->IsRxBusy = FALSE;

        /* Read dummy to clear RDRF flag */
        (void)Lpuart_Uart_Ip_Getchar(Base);

        RetVal = UartState->ReceiveStatus;
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_StartGetData
 * Description   : Start Getting Data in SyncReceive mode
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_StartGetData(const uint8 Instance, const uint32 Timeout)
{
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;
    Lpuart_Uart_Ip_StateStructureType * UartState;
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    uint8 StatusIndex = 0U;
    uint32 Mask = 0U;
    const Lpuart_Uart_Ip_StatusFlagType Lpuart_Uart_Ip_StatusFlagTypeArray[4U] = {LPUART_UART_IP_RX_OVERRUN,
                                                                                      LPUART_UART_IP_FRAME_ERR,
                                                                                      LPUART_UART_IP_NOISE_DETECT,
                                                                                      LPUART_UART_IP_PARITY_ERR
                                                                                     };
    const Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_ReceiveStatusArray[4U] = {LPUART_UART_IP_STATUS_RX_OVERRUN,
                                                                                 LPUART_UART_IP_STATUS_FRAMING_ERROR,
                                                                                 LPUART_UART_IP_STATUS_NOISE_ERROR,
                                                                                 LPUART_UART_IP_STATUS_PARITY_ERROR
                                                                                };
    const uint32 Lpuart_Uart_Ip_StatusRegMask[4U] = {LPUART_STAT_OR_MASK,
                                                         LPUART_STAT_FE_MASK,
                                                         LPUART_STAT_NF_MASK,
                                                         LPUART_STAT_PF_MASK
                                                        };

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, Timeout, LPUART_UART_IP_TIMEOUT_TYPE);
    while ((UartState->RxSize > 0U) && \
            !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {
        /* Wait until data reception flag is set or timeout occurs if there is an error during reception */
        while (!Lpuart_Uart_Ip_GetStatusFlag((const LPUART_Type*)Base, LPUART_UART_IP_DATA_REG_FULL) && \
               !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE) \
              )
        {}
        /* Check for errors on received data */
        for (StatusIndex = 0U; StatusIndex <= 3U; StatusIndex++)
        {
            if (Lpuart_Uart_Ip_GetStatusFlag((const LPUART_Type*)Base, Lpuart_Uart_Ip_StatusFlagTypeArray[StatusIndex]))
            {
                UartState->ReceiveStatus = Lpuart_Uart_Ip_ReceiveStatusArray[StatusIndex];
                Mask |= Lpuart_Uart_Ip_StatusRegMask[StatusIndex];
            }
        }

        if (Mask > 0U)
        {
            /* Disable the LPUART receiver */
            Lpuart_Uart_Ip_SetReceiverCmd((LPUART_Type *)Base, FALSE);
            /* Clear the flag */
            Lpuart_Uart_Ip_ClearStatusFlagWithMask(Base, Mask);
            break;
        }
        else
        {
            /* Get received data */
            Lpuart_Uart_Ip_GetData(Instance);
        }
    }

    /* Check if Timeout occur */
    if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {
        UartState->ReceiveStatus = LPUART_UART_IP_STATUS_TIMEOUT;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_ReceiveData
 * Description   : This function receives data from LPUART module using
 * non-blocking method.  This function returns immediately after initiating the
 * receive function. The application has to get the receive status to see when
 * the receive is complete. In other words, after calling non-blocking get
 * function, the application must get the receive status to check if receive
 * is completed or not.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_AsyncReceive_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AsyncReceive(const uint8 Instance, uint8 * RxBuff, const uint32 RxSize)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(RxBuff != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(RxSize > 0U);

    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    Lpuart_Uart_Ip_StateStructureType * UartState;
    Lpuart_Uart_Ip_StatusType RetVal = LPUART_UART_IP_STATUS_SUCCESS;
    boolean IsReturn = FALSE;

    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_03();
    /* Check it's not busy receiving data from a previous function call */
    if (UartState->IsRxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_03();
        RetVal = LPUART_UART_IP_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartState->IsRxBusy = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_03();

        LPUART_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);
        LPUART_UART_IP_DEV_ASSERT((LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType) ||
                                  (LPUART_UART_IP_USING_DMA == UartUserCfg->TransferType)
                                 );

        if (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType)
        {
            /* Start the reception process using interrupts */
            RetVal = Lpuart_Uart_Ip_StartReceiveDataUsingInt(Instance, RxBuff, RxSize);
        }
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
        else
        {
            /* Start the reception process using DMA */
            RetVal = Lpuart_Uart_Ip_StartReceiveDataUsingDma(Instance, RxBuff, RxSize);
        }
#endif
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_GetReceiveStatus
 * Description   : This function returns whether the previous LPUART receive is
 * complete. When performing a non-blocking receive, the user can call this
 * function to ascertain the state of the current receive progress: in progress
 * or complete. In addition, if the receive is still in progress, the user can
 * obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_GetReceiveStatus_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_GetReceiveStatus(const uint8 Instance, uint32 * BytesRemaining)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    const Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    Lpuart_Uart_Ip_StatusType localStatus;
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
    const Dma_Ip_LogicChannelInfoParamType DmaLogicChnParam = DMA_IP_CH_GET_CURRENT_ITER_COUNT;
#endif

    UartState = (const Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);

    if ((BytesRemaining != NULL_PTR) && (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType))
        {
            SchM_Enter_Uart_UART_EXCLUSIVE_AREA_04();
            localStatus = UartState->ReceiveStatus;
            if (UartState->IsRxBusy)
            {
                /* In interrupt-based communication, the remaining bytes are retrieved
                * from the state structure
                */
                *BytesRemaining = UartState->RxSize;
                SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
            }
            else
            {
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
                if (LPUART_UART_IP_STATUS_RX_IDLE_STATE == UartState->ReceiveStatus)
                {
                    *BytesRemaining = UartState->RxSize;
                    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
                }
                else
#endif
                {
                    *BytesRemaining = 0;
                    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
                }
            }
        }
    #if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
        else if ((BytesRemaining != NULL_PTR) && (LPUART_UART_IP_USING_DMA == UartUserCfg->TransferType))
        {
            SchM_Enter_Uart_UART_EXCLUSIVE_AREA_04();
            localStatus = UartState->ReceiveStatus;
            if (UartState->IsRxBusy)
            {
                SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
                /* In DMA-based communication, the remaining bytes are retrieved
                * from the current DMA major loop count
                */
                (void)Dma_Ip_GetLogicChannelParam(UartUserCfg->RxDMAChannel, DmaLogicChnParam, BytesRemaining);
            }
            else
            {
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
                if (LPUART_UART_IP_STATUS_RX_IDLE_STATE == UartState->ReceiveStatus)
                {
                    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
                    (void)Dma_Ip_GetLogicChannelParam(UartUserCfg->RxDMAChannel, DmaLogicChnParam, BytesRemaining);
                }
                else
#endif
                {
                    *BytesRemaining = 0;
                    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
                }
            }
        }
    #endif
        else
        {
            SchM_Enter_Uart_UART_EXCLUSIVE_AREA_04();
            localStatus = UartState->ReceiveStatus;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
        }

    return localStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_AbortReceivingData
 * Description   : Terminates a non-blocking receive early.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_AbortReceivingData_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_AbortReceivingData(const uint8 Instance)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);

    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    boolean IsReturn = FALSE;
    Lpuart_Uart_Ip_StatusType RetVal = LPUART_UART_IP_STATUS_SUCCESS;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);

    /* Check if a transfer is running. */
    if (!UartState->IsRxBusy)
    {
        IsReturn = TRUE;
    }

    if (!IsReturn)
    {
        /* Update the rx status */
        UartState->ReceiveStatus = LPUART_UART_IP_STATUS_ABORTED;

        /* Stop the running transfer. */
        if (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType)
        {
            Lpuart_Uart_Ip_CompleteReceiveDataUsingInt(Instance);
        }
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
        else
        {
            /* Release the DMA channel */
            (void)Dma_Ip_SetLogicChannelCommand(UartUserCfg->RxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
            Lpuart_Uart_Ip_CompleteReceiveUsingDma(Instance);
        }
#endif
        /* Clear all the error flags */
        Lpuart_Uart_Ip_ClearErrorFlags(Base);
        /* Flush the Rx Buffer */
        Lpuart_Uart_Ip_FlushRxBuffer(Base);
    }

    if (LPUART_UART_IP_STATUS_TIMEOUT == UartState->ReceiveStatus)
    {
        RetVal = LPUART_UART_IP_STATUS_ERROR;
    }

    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SetBaudRate
 * Description   : Configures the LPUART baud rate.
 * In some LPUART instances the user must disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_SetBaudRate_Activity*/
Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_SetBaudRate(const uint8 Instance,
                                                     const Lpuart_Uart_Ip_BaudrateType DesiredBaudrate,
                                                     const uint32 ClockFrequency
                                                    )
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);

    uint16 Sbr;
    uint16 SbrTemp;
    uint32 Idx;
    uint32 Osr;
    uint32 MaxOsr;
    uint32 TempDiff;
    uint32 CalculatedBaud;
    uint32 BaudDiff;
    uint32 ExpectedBaud = (uint32)DesiredBaudrate;
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    Lpuart_Uart_Ip_StateStructureType * UartState;
    Lpuart_Uart_Ip_StatusType Status;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    LPUART_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    if ((TRUE == UartState->IsTxBusy) || (TRUE == UartState->IsRxBusy))
    {
        Status = LPUART_UART_IP_STATUS_BUSY;
    }
    else
    {
        /* Check if current instance is clock gated off. */
        LPUART_UART_IP_DEV_ASSERT(ClockFrequency > 0U);
        /* Check if the desired baud rate can be configured with the current protocol clock. */
        LPUART_UART_IP_DEV_ASSERT(ClockFrequency >= (ExpectedBaud * 4U));

        /* This lpuart instantiation uses a slightly different baud rate calculation
         * The idea is to use the best OSR (over-sampling rate) possible
         * Note, Osr is typically hard-set to 16 in other lpuart instantiations
         * First calculate the baud rate using the minimum OSR possible (4) */
        Osr = 4;
        Sbr = (uint16)(ClockFrequency / (ExpectedBaud * Osr));
        CalculatedBaud = (ClockFrequency / ((uint32)Osr * (uint32)Sbr));
        if (CalculatedBaud > ExpectedBaud)
        {
            BaudDiff = CalculatedBaud - ExpectedBaud;
        }
        else
        {
            BaudDiff = ExpectedBaud - CalculatedBaud;
        }
        /* find maximum Osr */
        MaxOsr = ClockFrequency / ExpectedBaud;
        if (MaxOsr > 32U)
        {
            MaxOsr = 32U;
        }
        /* loop to find the best Osr value possible, one that generates minimum BaudDiff
         * iterate through the rest of the supported values of Osr */
        if (MaxOsr >= 5U)
        {
            for (Idx = 5U; Idx <= MaxOsr; Idx++)
            {
                /* calculate the temporary Sbr value   */
                SbrTemp = (uint16)(ClockFrequency / (ExpectedBaud * Idx));
                /* calculate the baud rate based on the temporary Osr and Sbr values */
                CalculatedBaud = (ClockFrequency / (Idx * (uint32)SbrTemp));

                if (CalculatedBaud > ExpectedBaud)
                {
                    TempDiff = CalculatedBaud - ExpectedBaud;
                }
                else
                {
                    TempDiff = ExpectedBaud - CalculatedBaud;
                }

                if (TempDiff <= BaudDiff)
                {
                    BaudDiff = TempDiff;
                    Osr = Idx;  /* update and store the best Osr value calculated */
                    Sbr = SbrTemp;  /* update store the best Sbr value calculated */
                }
            }
        }
        /* Check if Osr is between 4x and 7x oversampling.
         * If so, then "BOTHEDGE" sampling must be turned on */
        if (Osr < 8U)
        {
            Lpuart_Uart_Ip_EnableBothEdgeSamplingCmd(Base);
        }

        /* program the Osr value (bit value is one less than actual value) */
        Lpuart_Uart_Ip_SetOversamplingRatio(Base, (Osr - 1U));

        /* write the Sbr value to the BAUD registers */
        Lpuart_Uart_Ip_SetBaudRateDivisor(Base, Sbr);

        UartState->BaudRate = CalculatedBaud;

        Status = LPUART_UART_IP_STATUS_SUCCESS;
    }
    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_GetBaudRate
 * Description   : Returns the LPUART configured baud rate.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_GetBaudRate_Activity*/
void Lpuart_Uart_Ip_GetBaudRate(const uint8 Instance, uint32 * ConfiguredBaudRate)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(ConfiguredBaudRate != NULL_PTR);
    const Lpuart_Uart_Ip_StateStructureType * UartState;

    UartState = (const Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    *ConfiguredBaudRate = UartState->BaudRate;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SetTxBuffer
 * Description   : Sets the driver internal reference to the tx buffer.
 *                 Can be called from the tx callback to provide a different
 *                 buffer for continuous transmission.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_SetTxBuffer_Activity*/
void Lpuart_Uart_Ip_SetTxBuffer(const uint8 Instance, const uint8 * TxBuff, const uint32 TxSize)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(TxBuff != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(TxSize > 0U);
    Lpuart_Uart_Ip_StateStructureType * UartState;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    UartState->TxBuff = TxBuff;
    UartState->TxSize = TxSize;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SetRxBuffer
 * Description   : Sets the driver internal reference to the rx buffer.
 *                 Can be called from the rx callback to provide a different
 *                 buffer for continuous reception.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_SetRxBuffer_Activity*/
void Lpuart_Uart_Ip_SetRxBuffer(const uint8 Instance, uint8 * RxBuff, const uint32 RxSize)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);
    LPUART_UART_IP_DEV_ASSERT(RxBuff != NULL_PTR);
    LPUART_UART_IP_DEV_ASSERT(RxSize > 0U);
    Lpuart_Uart_Ip_StateStructureType * UartState;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartState->RxBuff = RxBuff;
    UartState->RxSize = RxSize;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_IrqHandler
 * Description   : Interrupt handler for LPUART.
 * This handler uses the buffers stored in the Lpuart_Uart_Ip_StateStructureType structs to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
/* @implements     Lpuart_Uart_Ip_IrqHandler_Activity*/
void Lpuart_Uart_Ip_IrqHandler(const uint8 Instance)
{
    LPUART_UART_IP_DEV_ASSERT(Instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * Base;
    const Lpuart_Uart_Ip_StateStructureType * UartState;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (const Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    /* Case of spurious interrupt when driver is not at all initialized or it is not in transmit/receive process*/
    if (NULL_PTR == UartState)
    {
        /* Read dummy to clear RDRF flag if it is set*/
        (void)Lpuart_Uart_Ip_Getchar(Base);
        /* Clear all the error flags */
        Lpuart_Uart_Ip_ClearErrorFlags(Base);
        /* Transmit flags can not be cleared, return to exit */
    }
    else
    {
        Lpuart_Uart_Ip_ErrIrqHandler(Instance);
        Lpuart_Uart_Ip_TxRxIrqHandler(Instance);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_RxIrqHandler
 * Description   : Rx Interrupt handler for LPUART.
 * This function treats the rx full interrupt.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_RxIrqHandler(const uint8 Instance)
{
    const Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Get data and put in receive buffer  */
    Lpuart_Uart_Ip_GetData(Instance);

    /* Check if this was the last byte in the current buffer */
    if (0U == UartState->RxSize)
    {
        /* Invoke callback if there is one (callback may reset the rx buffer for continuous reception) */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_RX_FULL, UartUserCfg->CallbackParam);
        }
    }

    /* Finish reception if this was the last byte received */
    if (0U == UartState->RxSize)
    {
        /* Complete transfer (disable rx logic) */
        Lpuart_Uart_Ip_CompleteReceiveDataUsingInt(Instance);

        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_END_TRANSFER, UartUserCfg->CallbackParam);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_TxEmptyIrqHandler
 * Description   : Tx Empty Interrupt handler for LPUART.
 * This function treats the tx empty interrupt.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_TxEmptyIrqHandler(const uint8 Instance)
{
    const Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Check if there are any more bytes to send */
    if (UartState->TxSize > 0U)
    {
        /* Transmit the data */
        Lpuart_Uart_Ip_PutData(Instance);

        /* Check if this was the last byte in the current buffer */
        if ((0U == UartState->TxSize) && (UartUserCfg->Callback != NULL_PTR))
        {
            /* Invoke callback if there is one (callback may reset the tx buffer for continuous transmission)*/
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_TX_EMPTY, UartUserCfg->CallbackParam);
        }
        /* If there's no new data, disable tx empty interrupt and enable transmission complete interrupt */
        if (0U == UartState->TxSize)
        {
            Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_DATA_REG_EMPTY, FALSE);
            Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_COMPLETE, TRUE);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_TxCompleteIrqHandler
 * Description   : Tx Complete Interrupt handler for LPUART.
 * This function treats the tx complete interrupt.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_TxCompleteIrqHandler(const uint8 Instance)
{
    const Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    if (0U == UartState->TxSize)
    {
        if (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType)
        {
            /* Complete the interrupt based transfer */
            Lpuart_Uart_Ip_CompleteSendDataUsingInt(Instance);
        }
        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_END_TRANSFER, UartUserCfg->CallbackParam);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_ErrIrqHandler
 * Description   : Error Interrupt handler for LPUART.
 * This function treats the error interrupts.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_ErrIrqHandler(const uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;
    boolean IsError = FALSE;
    boolean IsReturn = FALSE;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Handle receive overrun interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_RX_OVERRUN))
    {
        if (!Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_RX_OVERRUN))
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the status */
            IsError = TRUE;
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_RX_OVERRUN;
            /* Clear the flag */
            Lpuart_Uart_Ip_ClearStatusFlag(Base, LPUART_UART_IP_RX_OVERRUN);
        }
    }
    /* Handle framing error interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_FRAME_ERR) && (FALSE == IsReturn))
    {
        if (!Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_FRAME_ERR_FLAG))
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the status */
            IsError = TRUE;
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_FRAMING_ERROR;
            /* Clear the flag */
            Lpuart_Uart_Ip_ClearStatusFlag(Base, LPUART_UART_IP_FRAME_ERR);
        }
    }
    /* Handle parity error interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_PARITY_ERR) && (FALSE == IsReturn))
    {
        if (!Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_PARITY_ERR_FLAG))
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the status */
            IsError = TRUE;
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_PARITY_ERROR;
            /* Clear the flag */
            Lpuart_Uart_Ip_ClearStatusFlag(Base, LPUART_UART_IP_PARITY_ERR);
        }
    }
    /* Handle noise error interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_NOISE_DETECT) && (FALSE == IsReturn))
    {
        if (!Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_NOISE_ERR_FLAG))
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the internal status */
            IsError = TRUE;
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_NOISE_ERROR;
            /* Clear the flag */
            Lpuart_Uart_Ip_ClearStatusFlag(Base, LPUART_UART_IP_NOISE_DETECT);
        }
    }

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
        /* Handle the error interrupts if timeout error */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_TIMEOUT) && (FALSE == IsReturn))
    {
        /* This checking also ensures that the feature is activated for the current instance
         * because the Interrupt can be enabled only in this case.
         */
        if (Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_TIMEOUT))
        {
            /* Update the internal status */
            IsError = TRUE;
            /* Update the status */
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_RX_IDLE_STATE;
            /* Clear Timeout Interrupt Error flag */
            Lpuart_Uart_Ip_ClearStatusFlag(Base, LPUART_UART_IP_TIMEOUT);
        }
        else
        {
            IsReturn = TRUE;
        }
    }
#endif

    if (FALSE == IsReturn)
    {
        if (TRUE == IsError)
        {
            if (LPUART_UART_IP_USING_INTERRUPTS == UartUserCfg->TransferType)
            {
                /* Complete the transfer (disable rx logic) */
                Lpuart_Uart_Ip_CompleteReceiveDataUsingInt(Instance);
            }
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
            else
            {
                /* Complete the transfer (stop DMA channel) */
                (void)Dma_Ip_SetLogicChannelCommand(UartUserCfg->RxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
                Lpuart_Uart_Ip_CompleteReceiveUsingDma(Instance);
            }
#endif
            /* Invoke callback if there is one */
            if (UartUserCfg->Callback != NULL_PTR)
            {
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
                if (LPUART_UART_IP_STATUS_RX_IDLE_STATE == UartState->ReceiveStatus)
                {
                    UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_IDLE_STATE, UartUserCfg->CallbackParam);
                }
                else
#endif
                {
                    UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_ERROR, UartUserCfg->CallbackParam);
                }
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_StartSendDataUsingInt
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartSendDataUsingInt(const uint8 Instance, const uint8 * TxBuff, const uint32 TxSize)
{
    LPUART_Type * Base;
    Lpuart_Uart_Ip_StateStructureType * UartState;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    /* initialize the module driver state structure */
    UartState->TxBuff = TxBuff;
    UartState->TxSize = TxSize;
    UartState->TransmitStatus = LPUART_UART_IP_STATUS_BUSY;

    /* Enable the LPUART transmitter */
    Lpuart_Uart_Ip_SetTransmitterCmd(Base, TRUE);

    /* Enable tx empty interrupt */
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_DATA_REG_EMPTY, TRUE);

    return LPUART_UART_IP_STATUS_SUCCESS;
}

#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_StartSendDataUsingDma
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartSendDataUsingDma(const uint8 Instance, const uint8 * TxBuff, const uint32 TxSize)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
    DmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
    DmaTransferList[0].Value = (uint32)TxBuff;
    DmaTransferList[1].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
    DmaTransferList[1].Value = LPUART_UART_IP_LSBW_ADDR(Base->DATA);
    DmaTransferList[2].Param = DMA_IP_CH_SET_SOURCE_SIGNED_OFFSET;
    DmaTransferList[2].Value = 1;
    DmaTransferList[3].Param = DMA_IP_CH_SET_DESTINATION_SIGNED_OFFSET;
    DmaTransferList[3].Value = 0;
    DmaTransferList[4].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
    DmaTransferList[4].Value = TxSize;
    DmaTransferList[5].Param = DMA_IP_CH_SET_MINORLOOP_SIZE;
    DmaTransferList[5].Value = 1;
    DmaTransferList[6].Param = DMA_IP_CH_SET_DESTINATION_TRANSFER_SIZE;
    DmaTransferList[6].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
    DmaTransferList[7].Param = DMA_IP_CH_SET_SOURCE_TRANSFER_SIZE;
    DmaTransferList[7].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
    DmaTransferList[8].Param = DMA_IP_CH_SET_CONTROL_EN_MAJOR_INTERRUPT;
    DmaTransferList[8].Value = 1;
    DmaTransferList[9].Param = DMA_IP_CH_SET_CONTROL_DIS_AUTO_REQUEST;
    DmaTransferList[9].Value = 1;

    /* Update state structure */
    UartState->TxBuff = TxBuff;
    UartState->TxSize = 0U;
    UartState->TransmitStatus = LPUART_UART_IP_STATUS_BUSY;

    /* Configure the transfer control descriptor for the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UartUserCfg->TxDMAChannel, DmaTransferList, LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION);
    LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

    /* Start the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->TxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
    LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
    /* Enable the LPUART transmitter */
    Lpuart_Uart_Ip_SetTransmitterCmd(Base, TRUE);

    /* Enable tx DMA requests for the current instance */
    Lpuart_Uart_Ip_SetTxDmaCmd(Base, TRUE);

    return LPUART_UART_IP_STATUS_SUCCESS;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_CompleteSendDataUsingInt
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_CompleteSendDataUsingInt(const uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    LPUART_Type * Base;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    if (LPUART_UART_IP_STATUS_BUSY != UartState->TransmitStatus)
    {
        /* If the transfer is aborted or timed out, disable tx empty interrupt */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_DATA_REG_EMPTY, FALSE);
    }

    /* Disable transmission complete interrupt */
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TX_COMPLETE, FALSE);

    Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, LPUART_UART_IP_TIMEOUT_VALUE_US, LPUART_UART_IP_TIMEOUT_TYPE);
    /* Wait until the data is completely shifted out of shift register */
    while (!Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_TX_COMPLETE) && \
           !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE) \
          )
    {}

    if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {
        /* In case timeout occur */
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_TIMEOUT;
    }
    /* Disable transmitter */
    Lpuart_Uart_Ip_SetTransmitterCmd(Base, FALSE);

    if (LPUART_UART_IP_STATUS_BUSY == UartState->TransmitStatus)
    {
        /* If the transfer is completed, update the transmit status */
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_SUCCESS;
    }

    /* Update the internal busy flag */
    UartState->IsTxBusy = FALSE;
}

#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_CompleteSendUsingDma
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 *
 *END**************************************************************************/
void Lpuart_Uart_Ip_CompleteSendUsingDma(uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;
    Dma_Ip_LogicChannelStatusType DmaStatus;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];
    DmaStatus.ChStateValue = DMA_IP_CH_ERROR_STATE;

    /* Get Dma Ip Logic Channel Status */
    (void)Dma_Ip_GetLogicChannelStatus(UartUserCfg->TxDMAChannel, &DmaStatus);
    if (DMA_IP_CH_ERROR_STATE == DmaStatus.ChStateValue)
    {
        /* Reset the Dma Channel Error status. */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->TxDMAChannel, DMA_IP_CH_CLEAR_ERROR);

        LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
        /* Update transmit status */
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_DMA_ERROR;
        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_ERROR, UartUserCfg->CallbackParam);
        }
    }

    /* Invoke the callback when the buffer is finished;
     * Application can provide another buffer inside the callback by calling Lpuart_Uart_Ip_SetTxBuffer */
    if (LPUART_UART_IP_STATUS_BUSY == UartState->TransmitStatus)
    {
        /* Invoke callback if there is one (callback may reset the tx buffer for continuous transmission)*/
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_TX_EMPTY, UartUserCfg->CallbackParam);
        }
    }

    /* If the callback has updated the tx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if ((UartState->TxSize > 0U) && (UartState->TransmitStatus != LPUART_UART_IP_STATUS_DMA_ERROR))
    {
        /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
        DmaTransferList[0].Value = (uint32)(UartState->TxBuff);
        /* Update tx size and major loop count parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[1].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        DmaTransferList[1].Value = UartState->TxSize;

        /* Re-configure the transfer control descriptor for the DMA channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UartUserCfg->TxDMAChannel, DmaTransferList, LPUART_UART_IP_DMA_LEAST_CONFIG_LIST_DIMENSION);
        LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

        /* Now that this tx is set up, clear remaining bytes count */
        UartState->TxSize = 0U;

        /* Re-start the channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->TxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
        LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
    }
    else
    {
        /* Operation for complete send */
        Lpuart_Uart_Ip_CompleteTxOperationUsingDma(Instance);
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_StartReceiveDataUsingInt
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartReceiveDataUsingInt(const uint8 Instance, uint8 * RxBuff, const uint32 RxSize)
{
    LPUART_Type * Base;
    Lpuart_Uart_Ip_StateStructureType * UartState;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data. */
    UartState->IsRxBusy = TRUE;
    UartState->RxBuff = RxBuff;
    UartState->RxSize = RxSize;
    UartState->ReceiveStatus = LPUART_UART_IP_STATUS_BUSY;

    /* Clear all the error flags */
    Lpuart_Uart_Ip_ClearErrorFlags(Base);

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
        Lpuart_Uart_Ip_ClearStatusFlag(Base, LPUART_UART_IP_TIMEOUT);
#endif

    /* Flush the Tx Buffer */
    Lpuart_Uart_Ip_FlushRxBuffer(Base);

    /* Enable the receiver */
    Lpuart_Uart_Ip_SetReceiverCmd(Base, TRUE);

    /* Enable error interrupts */
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_OVERRUN, TRUE);
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_PARITY_ERR_FLAG, TRUE);
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_NOISE_ERR_FLAG, TRUE);
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_FRAME_ERR_FLAG, TRUE);
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    if (Lpuart_Uart_Ip_InstHasTimeoutInterruptEnabled[Instance])
    {
        /* Enable interrupt */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TIMEOUT, TRUE);
    }
#endif

    /* Enable receive data full interrupt */
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_DATA_REG_FULL, TRUE);

    return LPUART_UART_IP_STATUS_SUCCESS;
}

#if (STD_ON == LPUART_UART_IP_HAS_DMA_ENABLED)
/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_StartReceiveDataUsingDma
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Lpuart_Uart_Ip_StatusType Lpuart_Uart_Ip_StartReceiveDataUsingDma(const uint8 Instance, uint8 * RxBuff, const uint32 RxSize)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Clear all the error flags */
    Lpuart_Uart_Ip_ClearErrorFlags(Base);
    /* Flush the Tx Buffer */
    Lpuart_Uart_Ip_FlushRxBuffer(Base);

    /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
    DmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
    DmaTransferList[0].Value = LPUART_UART_IP_LSBW_ADDR(Base->DATA);
    DmaTransferList[1].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
    DmaTransferList[1].Value = (uint32)RxBuff;
    DmaTransferList[2].Param = DMA_IP_CH_SET_SOURCE_SIGNED_OFFSET;
    DmaTransferList[2].Value = 0;
    DmaTransferList[3].Param = DMA_IP_CH_SET_DESTINATION_SIGNED_OFFSET;
    DmaTransferList[3].Value = 1;
    DmaTransferList[4].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
    DmaTransferList[4].Value = RxSize;
    DmaTransferList[5].Param = DMA_IP_CH_SET_MINORLOOP_SIZE;
    DmaTransferList[5].Value = 1;
    DmaTransferList[6].Param = DMA_IP_CH_SET_DESTINATION_TRANSFER_SIZE;
    DmaTransferList[6].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
    DmaTransferList[7].Param = DMA_IP_CH_SET_SOURCE_TRANSFER_SIZE;
    DmaTransferList[7].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
    DmaTransferList[8].Param = DMA_IP_CH_SET_CONTROL_EN_MAJOR_INTERRUPT;
    DmaTransferList[8].Value = 1;
    DmaTransferList[9].Param = DMA_IP_CH_SET_CONTROL_DIS_AUTO_REQUEST;
    DmaTransferList[9].Value = 1;

    /* Update the state structure */
    UartState->RxBuff = RxBuff;
    UartState->RxSize = 0U;
    UartState->IsRxBusy = TRUE;
    UartState->ReceiveStatus = LPUART_UART_IP_STATUS_BUSY;

    /* Configure the transfer control descriptor for the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UartUserCfg->RxDMAChannel, DmaTransferList, LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION);
    LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

    /* Start the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->RxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
    LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

    /* Enable the receiver */
    Lpuart_Uart_Ip_SetReceiverCmd(Base, TRUE);
    /* Enable error interrupts and enable rx DMA requests for the current instance */
    Lpuart_Uart_Ip_SetupIntDmaMode(Instance, TRUE);

    return LPUART_UART_IP_STATUS_SUCCESS;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_CompleteReceiveDataUsingInt
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_CompleteReceiveDataUsingInt(const uint8 Instance)
{
    LPUART_Type * Base;
    Lpuart_Uart_Ip_StateStructureType * UartState;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    /* Disable all error interrupts */
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_OVERRUN, FALSE);
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_PARITY_ERR_FLAG, FALSE);
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_NOISE_ERR_FLAG, FALSE);
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_FRAME_ERR_FLAG, FALSE);

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    if (Lpuart_Uart_Ip_InstHasTimeoutInterruptEnabled[Instance])
    {
        /* Disable timeout interrupt */
        Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TIMEOUT, FALSE);
    }
#endif

    /* Disable receive data full and rx overrun interrupt. */
    Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_DATA_REG_FULL, FALSE);

    /* In Abort case, the transmission need to stop instantly */
    if (LPUART_UART_IP_STATUS_ABORTED == UartState->ReceiveStatus)
    {
        Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, LPUART_UART_IP_TIMEOUT_VALUE_US, LPUART_UART_IP_TIMEOUT_TYPE);
        /* Wait until the data is completely received */
        while (!Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_DATA_REG_FULL) && \
               !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE) \
              )
        {}

        if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
        {
          /* In case timeout occur */
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_TIMEOUT;
        }
    }

#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
    if (LPUART_UART_IP_STATUS_RX_IDLE_STATE != UartState->ReceiveStatus)
#endif
    {
        /* Disable receiver */
        Lpuart_Uart_Ip_SetReceiverCmd(Base, FALSE);
    }

    /* Read dummy to clear RDRF flag */
    (void)Lpuart_Uart_Ip_Getchar(Base);

    /* Update the information of the module driver state */
    UartState->IsRxBusy = FALSE;

    if (LPUART_UART_IP_STATUS_BUSY == UartState->ReceiveStatus)
    {
        UartState->ReceiveStatus = LPUART_UART_IP_STATUS_SUCCESS;
    }
}

#if (STD_ON == LPUART_UART_IP_HAS_DMA_ENABLED)
/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_CompleteReceiveUsingDma
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 *
 *END**************************************************************************/
void Lpuart_Uart_Ip_CompleteReceiveUsingDma(uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[LPUART_UART_IP_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;
    Dma_Ip_LogicChannelStatusType DmaStatus;

    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];
    DmaStatus.ChStateValue = DMA_IP_CH_ERROR_STATE;

    /* Get Dma Ip Logic Channel Status */
    (void)Dma_Ip_GetLogicChannelStatus(UartUserCfg->RxDMAChannel, &DmaStatus);

    if (DMA_IP_CH_ERROR_STATE == DmaStatus.ChStateValue)
    {
        /* Reset the Dma Channel Error status. */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->RxDMAChannel, DMA_IP_CH_CLEAR_ERROR);

        LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
        /* Update transmit status */
        UartState->ReceiveStatus = LPUART_UART_IP_STATUS_DMA_ERROR;
        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_ERROR, UartUserCfg->CallbackParam);
        }
    }

    /* Invoke the callback when the buffer is finished */
    if (LPUART_UART_IP_STATUS_BUSY == UartState->ReceiveStatus)
    {
        /* Application can provide another buffer inside the callback by calling Lpuart_Uart_Ip_SetRxBuffer */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_RX_FULL, UartUserCfg->CallbackParam);
        }
    }

    /* If the callback has updated the rx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if ((UartState->RxSize > 0U) && (UartState->ReceiveStatus != LPUART_UART_IP_STATUS_DMA_ERROR))
    {
        /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[0].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
        DmaTransferList[0].Value = (uint32)(UartState->RxBuff);
        DmaTransferList[1].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        DmaTransferList[1].Value = UartState->RxSize;

        /* Re-configure the transfer control descriptor for the DMA channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UartUserCfg->RxDMAChannel, DmaTransferList, LPUART_UART_IP_DMA_LEAST_CONFIG_LIST_DIMENSION);
        LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

        /* Now that this rx is set up, clear remaining bytes count */
        UartState->RxSize = 0U;

        /* Re-start the channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->RxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
        LPUART_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
    }
    else
    {
        /* Operation for complete receive data */
        Lpuart_Uart_Ip_CompleteRxOperationUsingDma(Instance);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SetupIntDmaMode
 * Description   : Setup error interrupts and Setup rx DMA requests for
 * the current instance
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_SetupIntDmaMode(const uint8 Instance, boolean Enable)
{
      LPUART_Type * Base;
      Base = Lpuart_Uart_Ip_apBases[Instance];

      /* Setup error interrupts */
      Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_RX_OVERRUN, Enable);
      Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_PARITY_ERR_FLAG, Enable);
      Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_NOISE_ERR_FLAG, Enable);
      Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_FRAME_ERR_FLAG, Enable);
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
      if (Lpuart_Uart_Ip_InstHasTimeoutInterruptEnabled[Instance])
      {
          Lpuart_Uart_Ip_SetIntMode(Base, LPUART_UART_IP_INT_TIMEOUT, Enable);
      }
#endif
      /* Setup rx DMA requests for the current instance */
      Lpuart_Uart_Ip_SetRxDmaCmd(Base, Enable);
}

#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_PutData
 * Description   : Write data to the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_PutData(const uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;
    uint16 Data16b;
    uint8 Data8b;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    if ((LPUART_UART_IP_7_BITS_PER_CHAR == UartUserCfg->BitCountPerChar) || (LPUART_UART_IP_8_BITS_PER_CHAR == UartUserCfg->BitCountPerChar))
    {
        Data8b = *(UartState->TxBuff);
        /* Update the state structure */
        ++UartState->TxBuff;
        --UartState->TxSize;
        /* Transmit the data */
        Lpuart_Uart_Ip_Putchar(Base, Data8b);
    }
    else
    {
        Data16b = (uint16)(*UartState->TxBuff);
        /* Update the state structure */
        if (1U == UartState->TxSize)
        {
            ++UartState->TxBuff;
            --UartState->TxSize;
        }
        else
        {
            ++UartState->TxBuff;
            Data16b |= (uint16)(((uint16)(*UartState->TxBuff)) << 8U);

            ++UartState->TxBuff;
            UartState->TxSize -= 2U;
        }

        /* Transmit the data */
        if (LPUART_UART_IP_9_BITS_PER_CHAR == UartUserCfg->BitCountPerChar)
        {
            Lpuart_Uart_Ip_Putchar9(Base, Data16b);
        }
        else
        {
            Lpuart_Uart_Ip_Putchar10(Base, Data16b);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_GetData
 * Description   : Read data from the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_GetData(const uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    const LPUART_Type * Base;
    uint16 Data16b;

    Base = (const LPUART_Type *)Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    if ((LPUART_UART_IP_7_BITS_PER_CHAR == UartUserCfg->BitCountPerChar) || (LPUART_UART_IP_8_BITS_PER_CHAR == UartUserCfg->BitCountPerChar))
    {
        /* Receive the data */
        *(UartState->RxBuff) = Lpuart_Uart_Ip_Getchar(Base);
        if (LPUART_UART_IP_7_BITS_PER_CHAR == UartUserCfg->BitCountPerChar)
        {
            *(UartState->RxBuff) &= 0x7FU;
        }
        /* Update the state structure */
        ++UartState->RxBuff;
        --UartState->RxSize;
    }
    else
    {
        if (LPUART_UART_IP_9_BITS_PER_CHAR == UartUserCfg->BitCountPerChar)
        {
            Data16b = Lpuart_Uart_Ip_Getchar9(Base);
        }
        else
        {
            Data16b = Lpuart_Uart_Ip_Getchar10(Base);
        }
        /* Get the data and update state structure */
        if (1U == UartState->RxSize)
        {
            *(UartState->RxBuff) = (uint8)Data16b;
            ++UartState->RxBuff;
            --UartState->RxSize;
        }
        else
        {
            /* Write the least significant bits to the receive buffer */
            *(UartState->RxBuff) = (uint8)(Data16b & 0xFFU);
            ++UartState->RxBuff;
            /* Write the ninth bit to the subsequent byte in the rx buffer */
            *UartState->RxBuff = (uint8)(Data16b >> 8U);
            ++UartState->RxBuff;
            UartState->RxSize -= 2U;
        }
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_SetUp_Baudrate
 * Description   : Set up baudrate for Lpuart Uart.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_SetUp_Baudrate(const uint8 Instance)
{
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;

    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Check if Osr is between 4x and 7x oversampling.
     * If so, then "BOTHEDGE" sampling must be turned on */
    if (UartUserCfg->BaudOverSamplingRatio < 8U)
    {
        Lpuart_Uart_Ip_EnableBothEdgeSamplingCmd(Base);
    }

    /* Program the Osr value (bit value is one less than actual value) */
    Lpuart_Uart_Ip_SetOversamplingRatio(Base, (uint32)UartUserCfg->BaudOverSamplingRatio -1U);

    /* Write the Sbr value to the BAUD registers */
    Lpuart_Uart_Ip_SetBaudRateDivisor(Base, UartUserCfg->BaudRateDivisor);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SetUp_Parity
 * Description   : Set up parity for Lpuart Uart.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_SetUp_Parity(const uint8 Instance)
{
    LPUART_Type * Base = Lpuart_Uart_Ip_apBases[Instance];
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;

    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    if (UartUserCfg->ParityMode != LPUART_UART_IP_PARITY_DISABLED)
    {
        Lpuart_Uart_Ip_SetBitCountPerChar(Base, UartUserCfg->BitCountPerChar, TRUE);
    }
    else
    {
        Lpuart_Uart_Ip_SetBitCountPerChar(Base, UartUserCfg->BitCountPerChar, FALSE);
    }
    Lpuart_Uart_Ip_SetParityMode(Base, UartUserCfg->ParityMode);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_TxRxIrqHandler
 * Description   : Transmit/Receive Interrupt handler for LPUART.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_TxRxIrqHandler(const uint8 Instance)
{
    const LPUART_Type * Base;
    boolean IsReturn = FALSE;

    Base = Lpuart_Uart_Ip_apBases[Instance];

    /* Handle receive data full interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_DATA_REG_FULL))
    {
        if (Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_RX_DATA_REG_FULL))
        {
            Lpuart_Uart_Ip_RxIrqHandler(Instance);
        }
        /* Case of spurious interrupt when the interupt enable flag is not set and respective interrupt status flag is set */
        else
        {
            /* CPR_RTD_00664.uart Spurious interrupt*/
            /* Do nothing - Return immediately */
        }
        IsReturn = TRUE;
    }
    /* Handle transmitter data register empty interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_TX_DATA_REG_EMPTY) && (FALSE == IsReturn))
    {
        if (Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_TX_DATA_REG_EMPTY))
        {
            Lpuart_Uart_Ip_TxEmptyIrqHandler(Instance);
            IsReturn = TRUE;
        }
        /* Case of spurious interrupt when the interupt enable flag is not set and respective interrupt status flag is set */
        else
        {
            /* Do nothing, because TDRE can not clear without affecting to normal operation*/
        }
    }
    /* Handle transmission complete interrupt */
    if (Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_TX_COMPLETE) && (FALSE == IsReturn))
    {
        if (Lpuart_Uart_Ip_GetIntMode(Base, LPUART_UART_IP_INT_TX_COMPLETE))
        {
            Lpuart_Uart_Ip_TxCompleteIrqHandler(Instance);
        }
        /* Case of spurious interrupt when the interupt enable flag is not set and respective interrupt status flag is set */
        else
        {
            /* Do nothing, because TC can not clear without affecting to normal operation*/
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_SyncSendData
 * Description   : Sync data sending process for Lpuart Uart.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_SyncSendData(const uint8 Instance, const uint32 Timeout)
{
    const LPUART_Type * Base;
    Lpuart_Uart_Ip_StateStructureType * UartState;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];

    Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, Timeout, LPUART_UART_IP_TIMEOUT_TYPE);

    while ((UartState->TxSize > 0U) && \
            !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE) \
          )
    {
        Lpuart_Uart_Ip_PutData(Instance);
        while (!Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_TX_DATA_REG_EMPTY)  && \
               !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE) \
              )
        {}
    }

    /* Check if Timeout occur */
    if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_TIMEOUT;
    }
    else /* The transmit process is complete */
    {
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_SUCCESS;
    }
}
#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_CompleteTxOperationUsingDma
 * Description   : Complete operation of the UART transmission using DMA.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_CompleteTxOperationUsingDma(const uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Disable tx DMA requests for the current instance */
    Lpuart_Uart_Ip_SetTxDmaCmd(Base, FALSE);

    /* Wait until the last transmission complete */
    Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, LPUART_UART_IP_TIMEOUT_VALUE_US, LPUART_UART_IP_TIMEOUT_TYPE);
    while (!Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_TX_COMPLETE) && \
       !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {}

    if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
    {
        /* In case timeout occur */
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_TIMEOUT;
    }

    /* Disable the transmitter */
    Lpuart_Uart_Ip_SetTransmitterCmd(Base, FALSE);

    if (LPUART_UART_IP_STATUS_BUSY == UartState->TransmitStatus)
    {
        /* If the transfer is completed, update the transmit status */
        UartState->TransmitStatus = LPUART_UART_IP_STATUS_SUCCESS;
        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_END_TRANSFER, UartUserCfg->CallbackParam);
        }
    }

    /* Update the busy flag */
    UartState->IsTxBusy = FALSE;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Lpuart_Uart_Ip_CompleteRxOperationUsingDma
 * Description   : Complete operation of the UART transmission using DMA.
 *
 *END**************************************************************************/
static void Lpuart_Uart_Ip_CompleteRxOperationUsingDma(const uint8 Instance)
{
    Lpuart_Uart_Ip_StateStructureType * UartState;
    const Lpuart_Uart_Ip_UserConfigType *UartUserCfg;
    LPUART_Type * Base;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    Base = Lpuart_Uart_Ip_apBases[Instance];
    UartState = (Lpuart_Uart_Ip_StateStructureType *)Lpuart_Uart_Ip_apStateStructuresArray[Instance];
    UartUserCfg = Lpuart_Uart_Ip_apUserConfig[Instance];

    /* Disable error interrupts and disable rx DMA requests for the current instance*/
    Lpuart_Uart_Ip_SetupIntDmaMode(Instance, FALSE);

    /* In Abort case, the transmission need to stop instantly */
    if (LPUART_UART_IP_STATUS_ABORTED == UartState->ReceiveStatus)
    {
        /* Wait until the last transmission complete */
        Lpuart_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, LPUART_UART_IP_TIMEOUT_VALUE_US, LPUART_UART_IP_TIMEOUT_TYPE);
        while (!Lpuart_Uart_Ip_GetStatusFlag(Base, LPUART_UART_IP_DATA_REG_FULL) && \
               !Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE) \
              )
        {}
        if (Lpuart_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, LPUART_UART_IP_TIMEOUT_TYPE))
        {
          /* In case timeout occur */
            UartState->ReceiveStatus = LPUART_UART_IP_STATUS_TIMEOUT;
        }
    }

    /* Disable receiver */
    Lpuart_Uart_Ip_SetReceiverCmd(Base, FALSE);

    /* Read dummy to clear RDRF flag */
    (void)Lpuart_Uart_Ip_Getchar(Base);

    /* Update the information of the module driver state */
    UartState->IsRxBusy = FALSE;

    /* If the current reception hasn't been aborted, update the status and call the callback */
    if (LPUART_UART_IP_STATUS_BUSY == UartState->ReceiveStatus)
    {
        UartState->ReceiveStatus = LPUART_UART_IP_STATUS_SUCCESS;

        /* Call the callback to notify application that the transfer is complete */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, LPUART_UART_IP_EVENT_END_TRANSFER, UartUserCfg->CallbackParam);
        }
    }
}
#endif
#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
