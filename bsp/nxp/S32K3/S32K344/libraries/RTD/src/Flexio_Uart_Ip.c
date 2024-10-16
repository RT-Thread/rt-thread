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
*   @file     Flexio_Uart_Ip.c
*   @defgroup flexio_uart_ip Flexio UART IPL
*   @addtogroup  flexio_uart_ip Flexio UART IPL
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
#include "Flexio_Uart_Ip_HwAccess.h"
#include "Flexio_Uart_Ip_Irq.h"
#include "Flexio_Uart_Ip.h"
#include "SchM_Uart.h"
#ifdef FLEXIO_UART_IP_DEV_ERROR_DETECT
    #if (FLEXIO_UART_IP_DEV_ERROR_DETECT == STD_ON)
#include "Devassert.h"
    #endif
#endif
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
#include "Dma_Ip.h"
#endif
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define FLEXIO_UART_IP_VENDOR_ID_C                      43
#define FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C       7
#define FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION_C    0
#define FLEXIO_UART_IP_SW_MAJOR_VERSION_C               5
#define FLEXIO_UART_IP_SW_MINOR_VERSION_C               0
#define FLEXIO_UART_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Flexio_Uart_Ip_Irq.h */
#if (FLEXIO_UART_IP_VENDOR_ID_C != FLEXIO_UART_IP_IRQ_VENDOR_ID)
    #error "Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip_Irq.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip.c and Flexio_Uart_Ip_Irq.h are different"
#endif
#if ((FLEXIO_UART_IP_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_SW_MINOR_VERSION_C != FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_SW_PATCH_VERSION_C != FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip.c and Flexio_Uart_Ip_Irq.h are different"
#endif
/* Checks against Flexio_Uart_Ip.h */
#if (FLEXIO_UART_IP_VENDOR_ID_C != FLEXIO_UART_IP_VENDOR_ID)
    #error "Flexio_Uart_Ip.c and Flexio_Uart_Ip.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip.c and Flexio_Uart_Ip.h are different"
#endif
#if ((FLEXIO_UART_IP_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_SW_MINOR_VERSION_C != FLEXIO_UART_IP_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_SW_PATCH_VERSION_C != FLEXIO_UART_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip.c and Flexio_Uart_Ip.h are different"
#endif

/* Checks against Flexio_Uart_Ip_Types.h */
#if (FLEXIO_UART_IP_VENDOR_ID_C != FLEXIO_UART_IP_HWACCESS_VENDOR_ID)
    #error "Flexio_Uart_Ip.c and Flexio_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip.c and Flexio_Uart_Ip_Types.h are different"
#endif
#if ((FLEXIO_UART_IP_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_HWACCESS_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_SW_MINOR_VERSION_C != FLEXIO_UART_IP_HWACCESS_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_SW_PATCH_VERSION_C != FLEXIO_UART_IP_HWACCESS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip.c and Flexio_Uart_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and SchM_Uart.h header file are of the same Autosar version */
    #if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_UART_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_UART_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Flexio_Uart_Ip.c and SchM_Uart.h are different"
    #endif
    /* Checks against Dma_Ip.h */
    #if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
        #if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C != DMA_IP_AR_RELEASE_MAJOR_VERSION) || \
             (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C != DMA_IP_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AutoSar Version Numbers of Flexio_Uart_Ip.c and Dma_Ip.h are different"
        #endif
    #endif
    #ifdef FLEXIO_UART_IP_DEV_ERROR_DETECT
    #if (STD_ON == FLEXIO_UART_IP_DEV_ERROR_DETECT)
        /* Check if Flexio_Uart_Ip.c file and Devassert.h file are of the same Autosar version */
        #if ((FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
             (FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION_C    != DEVASSERT_AR_RELEASE_MINOR_VERSION) \
            )
        #error "AutoSar Version Numbers of Flexio_Uart_Ip.c and Devassert.h are different"
        #endif
    #endif /* (STD_ON == FLEXIO_UART_IP_DEV_ERROR_DETECT) */
    #endif /* #ifdef FLEXIO_UART_IP_DEV_ERROR_DETECT */
#endif
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/
#ifdef FLEXIO_UART_IP_DEV_ERROR_DETECT
    #if (FLEXIO_UART_IP_DEV_ERROR_DETECT == STD_ON)
        #define FLEXIO_UART_IP_DEV_ASSERT(x)      DevAssert(x)
    #else
        #define FLEXIO_UART_IP_DEV_ASSERT(x)      (void)(x)
    #endif
#endif

/* Shifters/Timers used for UART simulation The parameter x represents the
   ResourceIndex value for the current driver Channel */
#define SHIFTER(x)    (x)
#define TIMER(x)      (x)
/* @brief Address of the least significant byte or word in a 32-bit register (depends on endianness) */
#define FLEXIO_UART_IP_LSBW_ADDR(reg)  ((uint32)(&(reg)))

#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    #define FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION             (10U)
    #define FLEXIO_UART_DMA_LEAST_CONFIG_LIST_DIMENSION       (2U)
#endif
/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

/** @brief Pointer to flexio runtime state structure */
Flexio_Uart_Ip_StateStructureType Flexio_Uart_Ip_apStateStructure[FLEXIO_UART_IP_NUMBER_OF_INSTANCES];

#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

#ifdef FLEXIO_UART_IP_IS_USING
    #if (FLEXIO_UART_IP_IS_USING == STD_ON)
        #define UART_START_SEC_CONST_UNSPECIFIED
        /* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
        #include "Uart_MemMap.h"
        /** @brief Table of base addresses for FLEXIO instances. */
        static FLEXIO_Type * const Flexio_Uart_Ip_apBases[FLEXIO_INSTANCE_COUNT] = IP_FLEXIO_BASE_PTRS;
        #define UART_STOP_SEC_CONST_UNSPECIFIED
        /* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
        #include "Uart_MemMap.h"
    #endif
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */
/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/
#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"
#ifdef FLEXIO_UART_IP_IS_USING
    #if (FLEXIO_UART_IP_IS_USING == STD_ON)
        /** @brief User config structure. */
        static const Flexio_Uart_Ip_UserConfigType * Flexio_Uart_Ip_apUserConfig[FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER];
        /** @brief Array of UART driver runtime state structures */
        static Flexio_Uart_Ip_StateStructureType * Flexio_Uart_Ip_apStateStructuresArray[FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER];
    #endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */

#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"
/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#ifdef FLEXIO_UART_IP_IS_USING
#if (FLEXIO_UART_IP_IS_USING == STD_ON)
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"
static void Flexio_Uart_Ip_ConfigureTx(const uint8 Channel,
                                       const Flexio_Uart_Ip_BitCountPerCharType BitCount,
                                       const uint16 Divider,
                                       const uint8 DataPin,
                                       const Flexio_Uart_Ip_TimerDecrementType TimerDec
                                      );

static void Flexio_Uart_Ip_ConfigureRx(const uint8 Channel,
                                       const Flexio_Uart_Ip_BitCountPerCharType BitCount,
                                       const uint16 Divider,
                                       const uint8 DataPin,
                                       const Flexio_Uart_Ip_TimerDecrementType TimerDec
                                      );
static void Flexio_Uart_Ip_StopTransfer(const uint8 Channel);
static void Flexio_Uart_Ip_CheckTxOperation(const uint8 Channel, const uint8 ShifterMaskFlag, const uint8 TimerMaskFlag);
static void Flexio_Uart_Ip_ReadData(const uint8 Channel);
static void Flexio_Uart_Ip_CheckRxOperation(const uint8 Channel, const uint8 ShifterMaskFlag, const uint8 ShifterErrMaskFlag);
static void Flexio_Uart_Ip_EnableReceiver(const uint8 Channel);
static void Flexio_Uart_Ip_EndTransfer(const uint8 Channel);
static void Flexio_Uart_Ip_WriteData(const uint8 Channel);
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
static Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_StartSendDataUsingDma(uint8 Channel, const uint8 * TxData, uint32 TxSize);
static Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_StartReceiveDataUsingDma(uint8 Channel, uint8 * RxBuff, uint32 RxSize);
static void Flexio_Uart_Ip_CompleteRxOperationUsingDma(const uint8 Channel);
static void Flexio_Uart_Ip_CompleteTxOperationUsingDma(const uint8 Channel);
#endif /*(FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)*/
static void Flexio_Uart_Ip_CheckCompleteTransferData(const uint8 Channel);
static void Flexio_Uart_Ip_SetupReceiveData(const uint8 Channel);
static void Flexio_Uart_Ip_CheckShifterErrorStatus(const uint8 Channel);
static void Flexio_Uart_Ip_SetShifterInterrupt(const uint8 Channel, boolean Enable);
static void Flexio_Uart_Ip_Callback(const uint8 Channel, const Flexio_Uart_Ip_EventType Event);
static void Flexio_Uart_Ip_CompleteTxOperation(const uint8 Channel);
static void Flexio_Uart_Ip_SyncSendData(const uint8 Channel, const uint32 Timeout);
static void Flexio_Uart_Ip_SyncReceiveData(const uint8 Channel, const uint32 Timeout);
static void Flexio_Uart_Ip_ConfigureRxShifter(const uint8 Channel, const uint8 DataPin);
static void Flexio_Uart_Ip_ConfigureRxTimer(const uint8 Channel, const uint8 DataPin, const Flexio_Uart_Ip_TimerDecrementType TimerDec);
static void Flexio_Uart_Ip_ConfigureTxTimer(const uint8 Channel, const Flexio_Uart_Ip_TimerDecrementType TimerDec);
static void Flexio_Uart_Ip_ConfigureTxShifter(const uint8 Channel, const uint8 DataPin);
static void Flexio_Uart_Ip_CheckTransferCompleteData(const uint8 Channel);

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_IrqHandler
 * Description   : Implementation of FLEXIO interrupt handler named in start-up code
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_IrqHandlerHandler_Activity*/
void Flexio_Uart_Ip_IrqHandler(uint8 Channel, uint8 ShifterMaskFlag, uint8 ShifterErrorMaskFlag, uint8 TimerMaskFlag)
{
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    FLEXIO_Type *Base;

    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* If the driver is not initialized, the ISR shall only clear interrupt status flag and return immediately. */
    if (NULL_PTR == UartUserCfg)
    {
        /* Clear timer status */
        Flexio_Mcl_Ip_ClearTimerStatus(Base, Channel);
        /* Clear Shifter status */
        Flexio_Mcl_Ip_ClearShifterStatus(Base, Channel);
        /*Clear Error Status flag*/
        Flexio_Mcl_Ip_ClearShifterErrorStatus(Base, Channel);
    }
    else
    {
        /* There is an Event for the current instance - call the isr */
        if (FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction)
        {
            Flexio_Uart_Ip_CheckTxOperation(Channel, ShifterMaskFlag, TimerMaskFlag);
        }
        else
        {
            Flexio_Uart_Ip_CheckRxOperation(Channel, ShifterMaskFlag, ShifterErrorMaskFlag);
        }
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ConfigureTx
 * Description   : configures the FLEXIO module for UART
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_ConfigureTx(const uint8 Channel,
                                       const Flexio_Uart_Ip_BitCountPerCharType BitCount,
                                       const uint16 Divider,
                                       const uint8 DataPin,
                                       const Flexio_Uart_Ip_TimerDecrementType TimerDec
                                      )
{
    FLEXIO_Type *Base;
    uint16 Bits;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    Bits = (uint16)BitCount;

    /* Configure tx shifter */
    Flexio_Uart_Ip_ConfigureTxShifter(Channel, DataPin);
    /* (Divider = InputClock / (BaudRate * 16U or 256U depend on baudrate), CMP bit = Divider/2 - 1 */
    Flexio_Uart_Ip_SetTimerCompare(Base, TIMER(Channel), (uint16)((((uint16)(Bits << 1U) - 1U) << 8U) + ((uint8)(Divider/2U) - 1U)));

    /* Configure tx timer */
    Flexio_Uart_Ip_ConfigureTxTimer(Channel, TimerDec);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ConfigureRx
 * Description   : configures the FLEXIO module for UART
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_ConfigureRx(const uint8 Channel,
                                       const Flexio_Uart_Ip_BitCountPerCharType BitCount,
                                       const uint16 Divider,
                                       const uint8 DataPin,
                                       const Flexio_Uart_Ip_TimerDecrementType TimerDec
                                      )
{
    FLEXIO_Type *Base;
    uint16 Bits;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    Bits = (uint16)BitCount;

    /* Configure rx shifter */
    Flexio_Uart_Ip_ConfigureRxShifter(Channel, DataPin);

    /* (Divider = InputClock / (BaudRate * 16U or 256U depend on baudrate), CMP bit = Divider/2 - 1 */
    Flexio_Uart_Ip_SetTimerCompare(Base, TIMER(Channel), (uint16)((((uint16)(Bits << 1U) - 1U) << 8U) + ((uint8)(Divider/2U) - 1U)));

    /* Configure rx timer */
    Flexio_Uart_Ip_ConfigureRxTimer(Channel, DataPin, TimerDec);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_EndTransfer
 * Description   : End the current transfer
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_EndTransfer(const uint8 Channel)
{
    FLEXIO_Type *Base;
    Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Disable transfer engine */
    /* Disable interrupts for Rx / Tx shifter */
    Flexio_Uart_Ip_SetShifterInterrupt(Channel, FALSE);
    /* Disable timer interrupt  */
    Flexio_Mcl_Ip_SetTimerInterrupt(Base, (uint8)(1U << TIMER(Channel)), FALSE);

    UartState->RemainingBytes = 0U;
    UartState->DriverIdle = FALSE;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_StopTransfer
 * Description   : Forcefully stops the current transfer
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_StopTransfer(const uint8 Channel)
{
    FLEXIO_Type *Base;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    const Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];

    /* End the transfer */
    Flexio_Uart_Ip_EndTransfer(Channel);

    if (FLEXIO_UART_IP_STATUS_ABORTED == UartState->Status)
    {
        Flexio_Uart_Ip_CheckTransferCompleteData(Channel);
    }

    /* Disable and re-enable timers and shifters to reset them */
    Flexio_Uart_Ip_SetTimerMode(Base, TIMER(Channel), FLEXIO_TIMER_MODE_DISABLED);
    Flexio_Uart_Ip_SetShifterMode(Base, SHIFTER(Channel), FLEXIO_SHIFTER_MODE_DISABLED);

    /* Clear any leftover error flags */
    Flexio_Mcl_Ip_ClearShifterErrorStatus(Base, SHIFTER(Channel));

    /* Re-enable shifter for Tx, to ensure correct idle state */
    if (FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction)
    {
        /* In tx mode restore start bit in case it was changed for end of transmission detection */
        Flexio_Uart_Ip_SetShifterStartBit(Base, SHIFTER(Channel), FLEXIO_SHIFTER_START_BIT_0);
        Flexio_Uart_Ip_SetShifterMode(Base, SHIFTER(Channel), FLEXIO_SHIFTER_MODE_TRANSMIT);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_WriteData
 * Description   : Writes data to be transmitted by the module
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_WriteData(const uint8 Channel)
{
    FLEXIO_Type *Base;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_StateStructureType * UartState;
    uint32 Data32b = 0UL;

    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];

    FLEXIO_UART_IP_DEV_ASSERT(UartState->TxData != NULL_PTR);

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Read data from user buffer and update tx buffer pointer and remaining bytes count */
    if (FLEXIO_UART_IP_8_BITS_PER_CHAR == UartUserCfg->BitCount)
    {
        Data32b = (uint32)(*UartState->TxData);
        UartState->TxData++;
        UartState->RemainingBytes -= 1U;
    }
    /* Writes data in the specified shifter buffer.*/
    Flexio_Uart_Ip_WriteShifterBuffer(Base, SHIFTER(Channel), Data32b);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CheckTxOperation
 * Description   : Check status of the UART transmission. This function can be
 *                 called either in an interrupt routine or directly in polling
 *                 mode to advance the transfer.
 *
 *END**************************************************************************/

static void Flexio_Uart_Ip_CheckTxOperation(const uint8 Channel, const uint8 ShifterMaskFlag, const uint8 TimerMaskFlag)
{
    const FLEXIO_Type *Base;
    const Flexio_Uart_Ip_StateStructureType * UartState;
    uint32 ResourceMask = (1UL << Channel);
    boolean IsReturn = FALSE;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    /* No need to check for Tx underflow since timer is controlled by the shifter status flag */
    /* Check for transfer end */
    if (0U == UartState->RemainingBytes)
    {
        if (((uint32)TimerMaskFlag & ResourceMask) != 0U)
        {
            if (!Flexio_Uart_Ip_GetTimerInterrupt(Base,TIMER(Channel)))
            {
                /* CPR_RTD_00664.uart Spurious interrupt*/
                /* Do nothing - Return immediately */
               IsReturn = TRUE;
            }
            if (!IsReturn)
            {
                Flexio_Uart_Ip_CompleteTxOperation(Channel);
            }
        }
    }
    /* Check if transmitter needs more data */
    else if ((((uint32)ShifterMaskFlag & ResourceMask) != 0U) && (UartState->RemainingBytes > 0U))
    {
        if (!Flexio_Uart_Ip_GetShifterInterrupt(Base, SHIFTER(Channel)))
        {
            /* CPR_RTD_00664.uart Spurious interrupt*/
            /* Do nothing - Return immediately */
        }
        else
        {
            Flexio_Uart_Ip_WriteData(Channel);
            Flexio_Uart_Ip_CheckCompleteTransferData(Channel);
        }
    }
    else
    {
        /* No relevant Events - nothing to do */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CheckCompleteTransferData
 * Description   : Setup User Callback, Clear Timer Status, Setup Shifter, Timer
 * Interrupt when all remaning bytes are transmited.
 *
 *END**************************************************************************/

static void Flexio_Uart_Ip_CheckCompleteTransferData(const uint8 Channel)
{
    FLEXIO_Type *Base;
    const Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    if (0U == UartState->RemainingBytes)
    {
        /* Out of data, call callback to allow user to provide a new buffer */
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_TX_EMPTY);
    }
    if (0U == UartState->RemainingBytes)
    {
        /* No more data, transmission will stop after the last bytes are sent.
           The timer Event will indicate when the send is complete */
        /* Clear any previous timer events */
        Flexio_Mcl_Ip_ClearTimerStatus(Base, TIMER(Channel));
        if (FLEXIO_UART_IP_DRIVER_TYPE_INTERRUPTS == UartUserCfg->DriverType)
        {
            /* Transmission completed; disable interrupt */
            Flexio_Mcl_Ip_SetShifterInterrupt(Base, (uint8)(1U << SHIFTER(Channel)), FALSE);
            /* Enable timer interrupt to ensure that transfer is completed */
            Flexio_Mcl_Ip_SetTimerInterrupt(Base, (uint8)(1U << TIMER(Channel)), TRUE);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ReadData
 * Description   : reads data received by the module
 *
 *END**************************************************************************/

static void Flexio_Uart_Ip_ReadData(const uint8 Channel)
{
    const FLEXIO_Type *Base;
    uint32 Data32b;
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];

    FLEXIO_UART_IP_DEV_ASSERT(UartState->RemainingBytes > 0U);
    FLEXIO_UART_IP_DEV_ASSERT(UartState->RxData != NULL_PTR);

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Read data from shifter buffer */
    Data32b = Flexio_Uart_Ip_ReadShifterBuffer(Base, SHIFTER(Channel));
    Data32b >>= 32U - (uint32)(UartUserCfg->BitCount);

    if (FLEXIO_UART_IP_8_BITS_PER_CHAR == UartUserCfg->BitCount)
    {
        *UartState->RxData = (uint8)Data32b;
        /* Update rx buffer pointer and remaining bytes count */
        UartState->RxData ++;
        UartState->RemainingBytes -= 1U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CheckRxOperation
 * Description   : Check status of the UART reception. This function can be
 *                 called either in an interrupt routine or directly in polling
 *                 mode to advance the transfer.
 *
 *END**************************************************************************/

static void Flexio_Uart_Ip_CheckRxOperation(const uint8 Channel, const uint8 ShifterMaskFlag, const uint8 ShifterErrMaskFlag)
{
    FLEXIO_Type * Base;
    Flexio_Uart_Ip_StateStructureType * UartState;
    uint32 ResourceMask = (1UL << Channel);
    boolean IsReturn = FALSE;
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
#endif

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Check for errors */
    if (((uint32)ShifterErrMaskFlag & ResourceMask) != 0U)
    {
        if (!Flexio_Uart_Ip_GetShifterErrorInterrupt(Base, SHIFTER(Channel)))
        {
            /* CPR_RTD_00664.uart Spurious interrupt*/
            /* Do nothing - Return immediately */
            IsReturn = TRUE;
        }
        else
        {
            UartState->Status = FLEXIO_UART_IP_STATUS_RX_OVERRUN;
            UartState->RemainingBytes = 0U;

            /* Invoke callback if there is one */
            Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_ERROR);
            /* Continue processing Events */
        }
    }
    /* Check if data was received */
    else if ((((uint32)ShifterMaskFlag & ResourceMask) != 0U))
    {
        if (!Flexio_Uart_Ip_GetShifterInterrupt(Base, SHIFTER(Channel)))
        {
            /* CPR_RTD_00664.uart Spurious interrupt*/
            /* Do nothing - Return immediately */
            IsReturn = TRUE;
        }
        else
        {
            Flexio_Uart_Ip_ReadData(Channel);
            if (0U == UartState->RemainingBytes)
            {
                /* Out of data, call callback to allow user to provide a new buffer */
                Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_RX_FULL);
            }
        }
    }
    else
    {
        /* No Events - nothing to do */
    }
    /* Check if transfer is over */
    if ((0U == UartState->RemainingBytes) && (!IsReturn))
    {
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
        if (FLEXIO_UART_IP_DRIVER_TYPE_DMA == UartUserCfg->DriverType)
        {
            /* Disable rx DMA requests for the current instance */
            Flexio_Mcl_Ip_SetShifterDMARequest(Base, (uint8)(1U << SHIFTER(Channel)), FALSE);
        }
#endif
        /* Discard any leftover rx data */
        Flexio_Mcl_Ip_ClearShifterStatus(Base, SHIFTER(Channel));
        /* End transfer */
        Flexio_Uart_Ip_StopTransfer(Channel);
        /* Record success if there was no error */
        if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
        {
            UartState->Status = FLEXIO_UART_IP_STATUS_SUCCESS;
            /* Call callback to announce the Event to the user */
            Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_END_TRANSFER);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CheckShifterErrorStatus
 * Description   : Checking Shifter Error Status and clear it if an error occured
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_CheckShifterErrorStatus(const uint8 Channel)
{
    FLEXIO_Type * Base;
    Flexio_Uart_Ip_StateStructureType * UartState;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];

    if (Flexio_Mcl_Ip_GetShifterErrorStatus(Base, SHIFTER(Channel)))
    {
        UartState->Status = FLEXIO_UART_IP_STATUS_RX_OVERRUN;
        Flexio_Mcl_Ip_ClearShifterErrorStatus(Base, SHIFTER(Channel));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SetShifterInterrupt
 * Description   : Setup interrupts for shifter
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_SetShifterInterrupt(const uint8 Channel, boolean Enable)
{
    FLEXIO_Type * Base;
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    Flexio_Mcl_Ip_SetShifterInterrupt(Base, (uint8)(1U << Channel), Enable);
    Flexio_Mcl_Ip_SetShifterErrorInterrupt(Base, (uint8)(1U << Channel), Enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SetupReceiveData
 * Description   : Disable interrupts for Rx Shifter and enable timer
 * and shifter to receiver data.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_SetupReceiveData(const uint8 Channel)
{
    /* Disable interrupts for Rx shifter */
    Flexio_Uart_Ip_SetShifterInterrupt(Channel, FALSE);
    /* Enable timers and shifters for receive data */
    Flexio_Uart_Ip_EnableReceiver(Channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_EnableReceiver
 * Description   : Enables timers and shifters to start receive data.
 *
 *END**************************************************************************/

static void Flexio_Uart_Ip_EnableReceiver(const uint8 Channel)
{
    FLEXIO_Type * Base;
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Enable timers and shifters and discard any leftover rx data*/
    Flexio_Mcl_Ip_ClearShifterStatus(Base, SHIFTER(Channel));
    Flexio_Uart_Ip_SetShifterMode(Base, SHIFTER(Channel), FLEXIO_SHIFTER_MODE_RECEIVE);
    Flexio_Uart_Ip_SetTimerMode(Base, TIMER(Channel), FLEXIO_TIMER_MODE_8BIT_BAUD);
}

#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_StartSendDataUsingDma
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_StartSendDataUsingDma(uint8 Channel, const uint8 * TxData, uint32 TxSize)
{
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UserConfig;
    FLEXIO_Type * Base;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UserConfig = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
    DmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
    DmaTransferList[0].Value = (uint32)TxData;
    DmaTransferList[1].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
    DmaTransferList[1].Value = FLEXIO_UART_IP_LSBW_ADDR(Base->SHIFTBUF[Channel]);
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
    UartState->TxData = TxData;
    UartState->RemainingBytes = 0U;
    UartState->Status = FLEXIO_UART_IP_STATUS_BUSY;

    /* Configure the transfer control descriptor for the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UserConfig->DmaChannel, DmaTransferList, FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION);
    FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

    /* Start the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UserConfig->DmaChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
    FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
    /* Enable FlexIO DMA requests */
    Flexio_Mcl_Ip_SetShifterDMARequest(Base, (uint8)(1U << SHIFTER(Channel)), TRUE);

    return FLEXIO_UART_IP_STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_StartReceiveDataUsingDma
 * Description   : Initiate (start) a transmit by beginning the process of
 * receiving data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_StartReceiveDataUsingDma(uint8 Channel, uint8 * RxBuff, uint32 RxSize)
{
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UserConfig;
    FLEXIO_Type * Base;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UserConfig = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
    DmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
    DmaTransferList[0].Value = FLEXIO_UART_IP_LSBW_ADDR(Base->SHIFTBUF[Channel]) + 3U;
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

    /* Update state structure */
    UartState->RxData = RxBuff;
    UartState->RemainingBytes = 0U;
    UartState->Status = FLEXIO_UART_IP_STATUS_BUSY;

    /* Configure the transfer control descriptor for the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UserConfig->DmaChannel, DmaTransferList, FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION);
    FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

    /* Start the DMA channel */
    DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UserConfig->DmaChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
    FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

    /* Enable FlexIO DMA requests */
    Flexio_Mcl_Ip_SetShifterDMARequest(Base, (uint8)(1U << SHIFTER(Channel)), TRUE);

    return FLEXIO_UART_IP_STATUS_SUCCESS;
}
#endif

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_Init
 * Description   : Initialize the FLEXIO_UART driver
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_Init_Activity*/
void Flexio_Uart_Ip_Init(const uint8 Channel, const Flexio_Uart_Ip_UserConfigType * UserConfig)
{
    Flexio_Uart_Ip_StateStructureType *UartStatePtr;

    UartStatePtr = UserConfig->StateStruct;

    FLEXIO_UART_IP_DEV_ASSERT(NULL_PTR == Flexio_Uart_Ip_apStateStructuresArray[Channel]);
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(Channel == UserConfig->Channel);
    Flexio_Uart_Ip_apStateStructuresArray[Channel] = UserConfig->StateStruct;
    Flexio_Uart_Ip_apUserConfig[Channel] = UserConfig;

    /* Initialize driver-specific context structure */
    UartStatePtr->RxData = NULL_PTR;
    UartStatePtr->TxData = NULL_PTR;
    UartStatePtr->RemainingBytes = 0U;
    UartStatePtr->BaudRate = UserConfig->BaudRate;
    UartStatePtr->Status = FLEXIO_UART_IP_STATUS_SUCCESS;
    UartStatePtr->DriverIdle = FALSE;

    if (FLEXIO_UART_IP_DIRECTION_TX == UserConfig->Direction)
    {
        /* Configure device for UART Tx mode */
        Flexio_Uart_Ip_ConfigureTx(Channel, UserConfig->BitCount, UserConfig->Divider, UserConfig->DataPin, UserConfig->TimerDec);
    }
    else
    {
        /* Configure device for UART Rx mode */
        Flexio_Uart_Ip_ConfigureRx(Channel, UserConfig->BitCount, UserConfig->Divider, UserConfig->DataPin, UserConfig->TimerDec);
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_GetBaudRate
 * Description   : Returns the FLEXIO configured baud rate.
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_GetBaudRate_Activity*/
void Flexio_Uart_Ip_GetBaudRate(const uint8 Channel, uint32 * BaudRate)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(BaudRate != NULL_PTR);
    const Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    *BaudRate = UartState->BaudRate;
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_Deinit
 * Description   : De-initialize the FLEXIO_UART driver
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_Deinit_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_Deinit(const uint8 Channel)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;
    FLEXIO_Type *Base;
    Flexio_Uart_Ip_StatusType RetVal;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    FLEXIO_UART_IP_DEV_ASSERT(Flexio_Uart_Ip_apStateStructuresArray[Channel] != NULL_PTR);
    Flexio_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_VALUE_US, FLEXIO_UART_IP_TIMEOUT_TYPE);
    /* Wait until the data is completely shifted out of shift register */
    while ((FLEXIO_UART_IP_STATUS_BUSY == Flexio_Uart_Ip_GetStatus(Channel, NULL_PTR)) && \
           !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
          )
    {}
    if (Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE))
    {
        RetVal = FLEXIO_UART_IP_STATUS_ERROR;
    }
    else
    {
        /* Clear our saved pointer to the state structure */
        Flexio_Uart_Ip_apStateStructuresArray[Channel] = NULL_PTR;
        /* Disable interrupts for Tx or Rx shifter */
        Flexio_Uart_Ip_SetShifterInterrupt(Channel, FALSE);
        /* Reset FlexIO module */
        Flexio_Mcl_Ip_SetSoftwareReset(Base, TRUE);
        /* Clear reset bit */
        Flexio_Mcl_Ip_SetSoftwareReset(Base, FALSE);
        RetVal = FLEXIO_UART_IP_STATUS_SUCCESS;
    }
    return RetVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_AsyncSend
 * Description   : Perform a Async UART transmission
 *
 *END**************************************************************************/
 /* @implements     Flexio_Uart_Ip_AsyncSend_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_AsyncSend(const uint8 Channel, const uint8 * TxBuff, const uint32 TxSize)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_Type *Base;
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_StatusType RetStatus = FLEXIO_UART_IP_STATUS_ERROR;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];

    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(TxBuff != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(TxSize > 0U);
    FLEXIO_UART_IP_DEV_ASSERT(FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction);
    /* If 2 bytes per word are needed, then the size must be even */
    FLEXIO_UART_IP_DEV_ASSERT((UartUserCfg->BitCount <= FLEXIO_UART_IP_8_BITS_PER_CHAR) || (0U == (TxSize & 1U)));
    /* Check if driver is busy */
    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_08();
    if (UartState->DriverIdle)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_08();
        RetStatus = FLEXIO_UART_IP_STATUS_BUSY;
    }
    else
    {
        UartState->DriverIdle = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_08();
        Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

        UartState->TxData = TxBuff;
        UartState->RemainingBytes = TxSize;
        UartState->Status = FLEXIO_UART_IP_STATUS_BUSY;
        /* Number of bytes to flush after the last byte is copied in the tx shifter buffer */
        UartState->TxFlush = (uint8)((1U == TxSize) ? 1U : 2U);

        /* Enable timers for sending data */
        Flexio_Uart_Ip_SetTimerMode(Base, TIMER(Channel), FLEXIO_TIMER_MODE_8BIT_BAUD);
        /* Enable transfer engine */
        switch (UartUserCfg->DriverType)
        {
            case FLEXIO_UART_IP_DRIVER_TYPE_INTERRUPTS:

                /* Enable interrupts for Tx shifter */
                Flexio_Uart_Ip_SetShifterInterrupt(Channel, TRUE);
                RetStatus = FLEXIO_UART_IP_STATUS_SUCCESS;
                break;
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
            case FLEXIO_UART_IP_DRIVER_TYPE_DMA:
                RetStatus = Flexio_Uart_Ip_StartSendDataUsingDma(Channel, TxBuff, TxSize);
                break;
#endif
            default:
                /* Impossible type - do nothing */
                break;
        }
    }
    return RetStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_GetStatus
 * Description   : Get the status of the current non-blocking UART transaction
 *
 *END**************************************************************************/
 /* @implements     Flexio_Uart_Ip_GetStatus_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_GetStatus(const uint8 Channel, uint32 *BytesRemaining)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    const Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_StatusType localStatus;
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    const Dma_Ip_LogicChannelInfoParamType DmaLogicChnParam = DMA_IP_CH_GET_CURRENT_ITER_COUNT;
#endif

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];

    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    /* Fill in the bytes not transferred yet. */
    if ((BytesRemaining != NULL_PTR) && (FLEXIO_UART_IP_DRIVER_TYPE_INTERRUPTS == UartUserCfg->DriverType))
    {
        SchM_Enter_Uart_UART_EXCLUSIVE_AREA_09();
        localStatus = UartState->Status;
        if (UartState->DriverIdle)
        {
            *BytesRemaining = UartState->RemainingBytes;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_09();
        }
        else
        {
            *BytesRemaining = 0;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_09();
        }
    }
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    else if ((BytesRemaining != NULL_PTR) && (FLEXIO_UART_IP_DRIVER_TYPE_DMA == UartUserCfg->DriverType))
    {
        SchM_Enter_Uart_UART_EXCLUSIVE_AREA_09();
        localStatus = UartState->Status;
        if (UartState->DriverIdle)
        {
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_09();
            /* In DMA-based communication, the remaining bytes are retrieved
            * from the current DMA major loop count
            */
            (void)Dma_Ip_GetLogicChannelParam(UartUserCfg->DmaChannel, DmaLogicChnParam, BytesRemaining);
        }
        else
        {
            *BytesRemaining = 0;
            SchM_Exit_Uart_UART_EXCLUSIVE_AREA_09();
        }
    }
#endif
    else
    {
        SchM_Enter_Uart_UART_EXCLUSIVE_AREA_09();
        localStatus = UartState->Status;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_09();
    }

    return localStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SyncSend
 * Description   : Perform a non-blocking UART transmission
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_SyncSend_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_SyncSend(const uint8 Channel, const uint8 * TxBuff, const uint32 TxSize, const uint32 Timeout)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(TxBuff != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(TxSize > 0U);
    FLEXIO_Type *Base;
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_StatusType RetStatus;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction);
    /* If 2 bytes per word are needed, then the size must be even */
    FLEXIO_UART_IP_DEV_ASSERT((UartUserCfg->BitCount <= FLEXIO_UART_IP_8_BITS_PER_CHAR) || ( 0U == (TxSize & 1U)));

    /* Check if driver is busy */
    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_10();
    if (UartState->DriverIdle)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_10();
        RetStatus = FLEXIO_UART_IP_STATUS_BUSY;
    }
    else
    {
        UartState->DriverIdle = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_10();
        UartState->TxData = TxBuff;
        UartState->RemainingBytes = TxSize;

        UartState->Status = FLEXIO_UART_IP_STATUS_BUSY;
        /* Disable interrupts for Tx shifter */
        Flexio_Uart_Ip_SetShifterInterrupt(Channel, FALSE);

        /* Number of bytes to flush after the last byte is copied in the tx shifter buffer */
        UartState->TxFlush = (uint8)((1U == TxSize) ? 1U : 2U);

        /* Enable timers and shifters */
        Flexio_Uart_Ip_SetTimerMode(Base, TIMER(Channel), FLEXIO_TIMER_MODE_8BIT_BAUD);

        /* Process for sync send data*/
        Flexio_Uart_Ip_SyncSendData(Channel, Timeout);

        /* Check other success receiving case*/
        if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
        {
            UartState->Status = FLEXIO_UART_IP_STATUS_SUCCESS;
        }
        /* Clear any previous timer events */
        Flexio_Mcl_Ip_ClearTimerStatus(Base, TIMER(Channel));
        UartState->DriverIdle = FALSE;
        RetStatus = UartState->Status;
    }
    return RetStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_AsyncReceive
 * Description   : Perform a non-blocking UART reception
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_AsyncReceive_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_AsyncReceive(const uint8 Channel, uint8 * RxBuff, const uint32 RxSize)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    FLEXIO_Type *Base;
#endif
    Flexio_Uart_Ip_StatusType RetStatus = FLEXIO_UART_IP_STATUS_ERROR;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
#endif

    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(RxBuff != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(RxSize > 0U);
    FLEXIO_UART_IP_DEV_ASSERT(FLEXIO_UART_IP_DIRECTION_RX == UartUserCfg->Direction);
    /* If 2 bytes per word are needed, then the size must be even */
    FLEXIO_UART_IP_DEV_ASSERT((UartUserCfg->BitCount <= FLEXIO_UART_IP_8_BITS_PER_CHAR) || (0U == (RxSize & 1U)));
    /* Check if driver is busy */
    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_06();
    if (UartState->DriverIdle)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_06();
        RetStatus = FLEXIO_UART_IP_STATUS_BUSY;
    }
    else
    {
        UartState->DriverIdle = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_06();

        UartState->RxData = RxBuff;
        UartState->RemainingBytes = RxSize;
        UartState->Status = FLEXIO_UART_IP_STATUS_BUSY;

        /* Enable timers and shifters for receive data */
        Flexio_Uart_Ip_EnableReceiver(Channel);
        /* Enable transfer engine */
        switch (UartUserCfg->DriverType)
        {
            case FLEXIO_UART_IP_DRIVER_TYPE_INTERRUPTS:
            /* Enable interrupts for Rx shifter */
            Flexio_Uart_Ip_SetShifterInterrupt(Channel, TRUE);
            RetStatus = FLEXIO_UART_IP_STATUS_SUCCESS;
            break;
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
            case FLEXIO_UART_IP_DRIVER_TYPE_DMA:
                Flexio_Mcl_Ip_SetShifterErrorInterrupt(Base, (uint8)(1U << Channel), TRUE);
                RetStatus = Flexio_Uart_Ip_StartReceiveDataUsingDma(Channel, RxBuff, RxSize);
                break;
#endif
            default:
                /* Impossible type - do nothing */
                break;
        }
    }
    return RetStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SyncReceive
 * Description   : Perform a non-blocking UART reception
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_SyncReceive_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_SyncReceive(const uint8 Channel, uint8 * RxBuff, const uint32 RxSize, const uint32 Timeout)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(RxBuff != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(RxSize > 0U);

    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    FLEXIO_Type *Base;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    Flexio_Uart_Ip_StatusType RetStatus;
    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];


    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(FLEXIO_UART_IP_DIRECTION_RX == UartUserCfg->Direction);
    /* If 2 bytes per word are needed, then the size must be even */
    FLEXIO_UART_IP_DEV_ASSERT((UartUserCfg->BitCount <= FLEXIO_UART_IP_8_BITS_PER_CHAR) || (0U == (RxSize & 1U)));

    /* Check if driver is busy */
    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_07();
    if (UartState->DriverIdle)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_07();
        RetStatus = FLEXIO_UART_IP_STATUS_BUSY;
    }
    else
    {
        UartState->DriverIdle = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_07();
        UartState->RxData = RxBuff;
        UartState->RemainingBytes = RxSize;
        UartState->Status = FLEXIO_UART_IP_STATUS_BUSY;
        Flexio_Uart_Ip_SetupReceiveData(Channel);

        /* Process for sync receive data*/
        Flexio_Uart_Ip_SyncReceiveData(Channel, Timeout);

        /* Clear any previous timer events */
        Flexio_Mcl_Ip_ClearTimerStatus(Base, TIMER(Channel));
        UartState->DriverIdle = FALSE;
        RetStatus = UartState->Status;
    }
    return RetStatus;
}
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CompleteSendUsingDma
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 *
 *END**************************************************************************/
void Flexio_Uart_Ip_CompleteSendUsingDma(uint8 Channel)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;
    Dma_Ip_LogicChannelStatusType DmaStatus;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    DmaStatus.ChStateValue = DMA_IP_CH_ERROR_STATE;

    /* Get Dma Ip Logic Channel Status */
    (void)Dma_Ip_GetLogicChannelStatus(UartUserCfg->DmaChannel, &DmaStatus);
    if (DMA_IP_CH_ERROR_STATE == DmaStatus.ChStateValue)
    {
        /* Reset the Dma Channel Error status. */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->DmaChannel, DMA_IP_CH_CLEAR_ERROR);

        FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

        /* Update transmit status */
        UartState->Status = FLEXIO_UART_IP_STATUS_DMA_ERROR;
        /* Invoke callback if there is one */
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_ERROR);
    }

    /* Invoke the callback when the buffer is finished;
     * Application can provide another buffer inside the callback by calling Flexio_Uart_Ip_SetTxBuffer */
    if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
    {
        /* Invoke callback if there is one (callback may reset the tx buffer for continuous transmission)*/
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_TX_EMPTY);
    }

    /* If the callback has updated the tx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if ((UartState->RemainingBytes > 0U) && (UartState->Status != FLEXIO_UART_IP_STATUS_DMA_ERROR))
    {
        /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
        DmaTransferList[0].Value = (uint32)(UartState->TxData);
        /* Update tx size and major loop count parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[1].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        DmaTransferList[1].Value = UartState->RemainingBytes;

        /* Re-configure the transfer control descriptor for the DMA channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UartUserCfg->DmaChannel, DmaTransferList, FLEXIO_UART_DMA_LEAST_CONFIG_LIST_DIMENSION);
        FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

        /* Now that this tx is set up, clear remaining bytes count */
        UartState->RemainingBytes = 0U;

        /* Re-start the channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->DmaChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
        FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
    }
    else
    {
        /* Operation for complete send */
        Flexio_Uart_Ip_CompleteTxOperationUsingDma(Channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CompleteReceiveUsingDma
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 *
 *END**************************************************************************/
void Flexio_Uart_Ip_CompleteReceiveUsingDma(uint8 Channel)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType * UartUserCfg;
    Dma_Ip_LogicChannelTransferListType DmaTransferList[FLEXIO_UART_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType DmaReturnStatus;
    Dma_Ip_LogicChannelStatusType DmaStatus;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    DmaStatus.ChStateValue = DMA_IP_CH_ERROR_STATE;

    /* Get Dma Ip Logic Channel Status */
    (void)Dma_Ip_GetLogicChannelStatus(UartUserCfg->DmaChannel, &DmaStatus);
    if (DMA_IP_CH_ERROR_STATE == DmaStatus.ChStateValue)
    {
        /* Reset the Dma Channel Error status. */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->DmaChannel, DMA_IP_CH_CLEAR_ERROR);

        FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
        /* Update transmit status */
        UartState->Status = FLEXIO_UART_IP_STATUS_DMA_ERROR;
        /* Invoke callback if there is one */
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_ERROR);
    }

    /* Invoke the callback when the buffer is finished;
     * Application can provide another buffer inside the callback by calling Flexio_Uart_Ip_SetTxBuffer */
    if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
    {
        /* Invoke callback if there is one (callback may reset the tx buffer for continuous transmission)*/
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_RX_FULL);
    }

    /* If the callback has updated the tx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if ((UartState->RemainingBytes > 0U) && (UartState->Status != FLEXIO_UART_IP_STATUS_DMA_ERROR))
    {
        /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[0].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
        DmaTransferList[0].Value = (uint32)(UartState->RxData);
        /* Update tx size and major loop count parameters for Dma_Ip_LogicChannelTransferListType */
        DmaTransferList[1].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        DmaTransferList[1].Value = UartState->RemainingBytes;

        /* Re-configure the transfer control descriptor for the DMA channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(UartUserCfg->DmaChannel, DmaTransferList, FLEXIO_UART_DMA_LEAST_CONFIG_LIST_DIMENSION);
        FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);

        /* Now that this rx is set up, clear remaining bytes count */
        UartState->RemainingBytes = 0U;

        /* Re-start the channel */
        DmaReturnStatus = Dma_Ip_SetLogicChannelCommand(UartUserCfg->DmaChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
        FLEXIO_UART_IP_DEV_ASSERT(DMA_IP_STATUS_SUCCESS == DmaReturnStatus);
    }
    else
    {
        /* Operation for complete receive data */
        Flexio_Uart_Ip_CompleteRxOperationUsingDma(Channel);
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_AbortTransferData
 * Description   : This function terminates an non-blocking FLEXIO transmission
 * early. During a non-blocking FLEXIO transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
/* @implements     Flexio_Uart_Ip_AbortTransferData_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_AbortTransferData(const uint8 Channel)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_StatusType RetStatus = FLEXIO_UART_IP_STATUS_SUCCESS;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];

    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(UartUserCfg != NULL_PTR);

    /* Check if a transfer is running. */
    if (!UartState->DriverIdle)
    {
        RetStatus = FLEXIO_UART_IP_STATUS_SUCCESS;
    }
    else
    {
        /* Update the tx status */
        UartState->Status = FLEXIO_UART_IP_STATUS_ABORTED;

        /* Stop the running transfer. */
        if (FLEXIO_UART_IP_DRIVER_TYPE_INTERRUPTS == UartUserCfg->DriverType)
        {
            Flexio_Uart_Ip_StopTransfer(Channel);
        }
#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
        else
        {
            /* Release the DMA channel */
            (void)Dma_Ip_SetLogicChannelCommand(UartUserCfg->DmaChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
            if (FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction)
            {
                Flexio_Uart_Ip_CompleteSendUsingDma(Channel);
            }
            else
            {
                Flexio_Uart_Ip_CompleteReceiveUsingDma(Channel);
            }
        }
#endif
        if (FLEXIO_UART_IP_STATUS_TIMEOUT == UartState->Status)
        {
            RetStatus = FLEXIO_UART_IP_STATUS_ERROR;
        }
    }
    return RetStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SetBaudRate
 * Description   : Configures the FLEXIO baud rate.
 * In some FLEXIO instances the user must disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all FLEXIOs to ensure safe operation.
 *
 *END**************************************************************************/
 /* @implements     Flexio_Uart_Ip_SetBaudRate_Activity*/
Flexio_Uart_Ip_StatusType Flexio_Uart_Ip_SetBaudRate(const uint8 Channel,
                                                     const Flexio_Uart_Ip_BaudrateType DesiredBaudrate,
                                                     const uint32 ClockFrequency
                                                    )
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(ClockFrequency > 0U);

    Flexio_Uart_Ip_StateStructureType * UartState;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_TimerDecrementType TimerDecrement;
    Flexio_Uart_Ip_StatusType Status;
    FLEXIO_Type * Base;
    sint32 CMP_value;
    uint16 BitCountValue;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    BitCountValue = (uint16)UartUserCfg->BitCount;

    FLEXIO_UART_IP_DEV_ASSERT(UartState != NULL_PTR);

    /* Check if there is an ongoing transfer */
    if (TRUE == UartState->DriverIdle)
    {
        Status = FLEXIO_UART_IP_STATUS_BUSY;
    }
    else
    {
        /*  In case driver does not support 16/256 prescale timer decreasement modes */
        if (FLEXIO_TIMER_DECREMENT_FXIO_CLK_SHIFT_TMR == UartUserCfg->TimerDec)
        {
            TimerDecrement = FLEXIO_TIMER_DECREMENT_FXIO_CLK_SHIFT_TMR;
            /* Add 0.5 to around the value of CMP bit => CMP_bit equal to Flexio_CLK/(DesiredBaudrate * 2) - 1 +0.5 */
            CMP_value = (sint32)(((sint32)ClockFrequency - (sint32)DesiredBaudrate) / ((sint32)DesiredBaudrate * 2));
            FLEXIO_UART_IP_DEV_ASSERT((CMP_value <= 255) && (CMP_value >= 0));
            UartState->BaudRate = (uint32)(ClockFrequency / (2U * ((uint32)CMP_value + 1U)));
        }
        else
        {
            /* Add 0.5 to around the value of CMP bit => CMP_bit equal to Flexio_CLK/(DesiredBaudrate * 2 * 16) - 1 +0.5 */
            CMP_value = (sint32)(((sint32)ClockFrequency - ((sint32)DesiredBaudrate * 16)) / ((sint32)DesiredBaudrate * 16 * 2));

            if ((CMP_value <= 255) && (CMP_value >= 0))
            {
                TimerDecrement = FLEXIO_TIMER_DECREMENT_FXIO_CLK_DIV_16;
                UartState->BaudRate = (uint32)(ClockFrequency / (16U * 2U * ((uint32)CMP_value + 1U)));
            }
            else
            {
                TimerDecrement = FLEXIO_TIMER_DECREMENT_FXIO_CLK_DIV_256;
                /* Add 0.5 to around the value of CMP bit => CMP_bit equal to Flexio_CLK/(DesiredBaudrate * 2 * 256) - 1 +0.5 */
                CMP_value = (sint32)(((sint32)ClockFrequency - ((sint32)DesiredBaudrate * 256)) / ((sint32)DesiredBaudrate * 256 * 2));
                FLEXIO_UART_IP_DEV_ASSERT((CMP_value <= 255) && (CMP_value >= 0));
                UartState->BaudRate = (uint32)(ClockFrequency / (256U * 2U * ((uint32)CMP_value + 1U)));
            }
        }

        Flexio_Uart_Ip_SetTimerCompare(Base, TIMER(Channel), (uint16)((((uint16)(BitCountValue << 1U) - 1U) << 8U) + (uint8)CMP_value));

        if (FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction)
        {
            /* Configure tx timer */
            Flexio_Uart_Ip_SetTimerConfig(Base,
                                          TIMER(Channel),
                                          FLEXIO_TIMER_RESET_NEVER,
                                          TimerDecrement,                    /* Decrement on FlexIO clock */
                                          FLEXIO_TIMER_INITOUT_ONE
                                         );

            Flexio_Uart_Ip_SetTimerStartStopBitConfig(Base,
                                                      TIMER(Channel),
                                                      FLEXIO_TIMER_START_BIT_ENABLED,
                                                      FLEXIO_TIMER_STOP_BIT_TIM_DIS
                                                     );

            Flexio_Uart_Ip_SetTimerCondition(Base,
                                             TIMER(Channel),
                                             FLEXIO_TIMER_ENABLE_TRG_HIGH,            /* Enable when Tx data is available */
                                             FLEXIO_TIMER_DISABLE_TIM_CMP
                                            );
        }
        else
        {
            /* Configure rx timer */
            Flexio_Uart_Ip_SetTimerConfig(Base,
                                          TIMER(Channel),
                                          FLEXIO_TIMER_RESET_PIN_RISING,
                                          TimerDecrement,                    /* Decrement on FlexIO clock */
                                          FLEXIO_TIMER_INITOUT_ONE_RESET
                                         );

            Flexio_Uart_Ip_SetTimerStartStopBitConfig(Base,
                                                      TIMER(Channel),
                                                      FLEXIO_TIMER_START_BIT_ENABLED,
                                                      FLEXIO_TIMER_STOP_BIT_TIM_DIS
                                                     );

            Flexio_Uart_Ip_SetTimerCondition(Base,
                                             TIMER(Channel),
                                             FLEXIO_TIMER_ENABLE_PIN_POSEDGE,    /* Enable when data is available */
                                             FLEXIO_TIMER_DISABLE_TIM_CMP
                                            );
        }

        Status = FLEXIO_UART_IP_STATUS_SUCCESS;
    }

    return Status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SetTxBuffer
 * Description   : Sets the driver internal reference to the tx buffer.
 *                 Can be called from the tx callback to provide a different
 *                 buffer for continuous transmission.
 *
 *END**************************************************************************/
 /* @implements     Flexio_Uart_Ip_SetTxBuffer_Activity*/
void Flexio_Uart_Ip_SetTxBuffer(const uint8 Channel, const uint8 * TxData, const uint32 TxSize)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(TxData != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(TxSize > 0U);
    Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];

    UartState->TxData = TxData;
    UartState->RemainingBytes = TxSize;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SetRxBuffer
 * Description   : Sets the driver internal reference to the rx buffer.
 *                 Can be called from the rx callback to provide a different
 *                 buffer for continuous reception.
 *
 *END**************************************************************************/
 /* @implements     Flexio_Uart_Ip_SetRxBuffer_Activity*/
void Flexio_Uart_Ip_SetRxBuffer(const uint8 Channel, uint8 * RxData, const uint32 RxSize)
{
    FLEXIO_UART_IP_DEV_ASSERT(Channel < FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER);
    FLEXIO_UART_IP_DEV_ASSERT(RxData != NULL_PTR);
    FLEXIO_UART_IP_DEV_ASSERT(RxSize > 0U);
    Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    UartState->RxData = RxData;
    UartState->RemainingBytes = RxSize;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_Callback
 * Description   : Enter callback function for Flexio Uart.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_Callback(const uint8 Channel, const Flexio_Uart_Ip_EventType Event)
{
    const Flexio_Uart_Ip_UserConfigType * UartUserCfg;

    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];

    if (UartUserCfg->Callback != NULL_PTR)
    {
        UartUserCfg->Callback(Channel, Event, UartUserCfg->CallbackParam);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CompleteTxOperation
 * Description   : Complete operation of the UART transmission.
 *
 *END**************************************************************************/

static void Flexio_Uart_Ip_CompleteTxOperation(const uint8 Channel)
{
    FLEXIO_Type *Base;
    Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    UartState->TxFlush--;
    if (0U == UartState->TxFlush)
    {
        /* Clear Shifter status for transmit mode*/
        Flexio_Mcl_Ip_ClearShifterStatus(Base, SHIFTER(Channel));
        /* Done flushing the Tx buffer, end transfer */
        Flexio_Uart_Ip_StopTransfer(Channel);
        /* Record success if there was no error */
        if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
        {
            UartState->Status = FLEXIO_UART_IP_STATUS_SUCCESS;
        }
        /* Call callback to announce the end transfer Event to the user */
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_END_TRANSFER);
    }
    else if (Flexio_Mcl_Ip_GetShifterStatus(Base, SHIFTER(Channel)))
    {
        /* TxFlush == 1, but last byte was already transferred from buffer to shifter. There is a
           danger that the transmission is over and we end up never reporting the end Event.
           To avoid this, send one extra dummy byte */
        /* Set start bit to 1 and send an 0xFF byte, this way the line will appear idle */
        Flexio_Uart_Ip_SetShifterStartBit(Base, SHIFTER(Channel), FLEXIO_SHIFTER_START_BIT_1);
        /* Writes data in the specified shifter buffer.*/
        Flexio_Uart_Ip_WriteShifterBuffer(Base, SHIFTER(Channel), 0xFFFFFFFFUL);
    }
    else
    {
        /* TxFlush == 1, and last byte was not yet transferred from buffer to shifter.
           No need to do anything, just wait for the next timer Event. */
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SyncSendData
 * Description   : Sync data sending process for Flexio Uart.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_SyncSendData(const uint8 Channel, const uint32 Timeout)
{
    const FLEXIO_Type *Base;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;
    Flexio_Uart_Ip_StateStructureType * UartState;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    Flexio_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, Timeout, FLEXIO_UART_IP_TIMEOUT_TYPE);

    while ((UartState->RemainingBytes > 0U) && \
           !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
          )
    {
        Flexio_Uart_Ip_WriteData(Channel);
        while (!Flexio_Mcl_Ip_GetShifterStatus(Base, Channel)  && \
               !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
              )
        {}
    }

    /* Check if Timeout occur */
    if (Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE))
    {
        UartState->Status = FLEXIO_UART_IP_STATUS_TIMEOUT;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_SyncReceiveData
 * Description   : Sync data sending process for Flexio Uart.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_SyncReceiveData(const uint8 Channel, const uint32 Timeout)
{
    Flexio_Uart_Ip_StateStructureType * UartState;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;
    const FLEXIO_Type *Base;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];
    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];

    Flexio_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, Timeout, FLEXIO_UART_IP_TIMEOUT_TYPE);

    while ((UartState->RemainingBytes > 0U) && \
            !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
          )
    {
        while (!Flexio_Mcl_Ip_GetShifterStatus(Base, Channel) && \
               !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
              )
        {}
        /* For SMOD=Receive, indicates Shifter was ready to store new data into SHIFTBUF before the previous data
        was read from SHIFTBUF (SHIFTBUF Overrun), or indicates that the received start or stop bit does not
        match the expected value. */
        Flexio_Uart_Ip_CheckShifterErrorStatus(Channel);
        if (FLEXIO_UART_IP_STATUS_RX_OVERRUN == UartState->Status)
        {
            break;
        }
        /* Read only data from SHIFBUF when shifter status flag is set */
        Flexio_Uart_Ip_ReadData(Channel);
    }

    /* Check other success receiving case*/
    if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
    {
        /* Check if Timeout occur */
        if (Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE))
        {
            UartState->Status = FLEXIO_UART_IP_STATUS_TIMEOUT;
        }
        else
        {
            UartState->Status = FLEXIO_UART_IP_STATUS_SUCCESS;
        }
    }
}

#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CompleteTxOperationUsingDma
 * Description   : Complete operation of the UART transmission using DMA.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_CompleteTxOperationUsingDma(const uint8 Channel)
{
    const Flexio_Uart_Ip_StateStructureType * UartState;
    FLEXIO_Type * Base;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];


    /* Disable tx DMA requests for the current instance */
    Flexio_Mcl_Ip_SetShifterDMARequest(Base, (uint8)(1U << SHIFTER(Channel)), FALSE);

    if (FLEXIO_UART_IP_STATUS_DMA_ERROR == UartState->Status)
    {
        /* End transfer */
        Flexio_Uart_Ip_StopTransfer(Channel);
    }
    else
    {
        /* No more data to transmit, transmission will stop */
        /* Enable timer interrupt to let IRQ ensure that transfer is completed */
        Flexio_Mcl_Ip_ClearTimerStatus(Base, Channel);
        Flexio_Mcl_Ip_SetTimerInterrupt(Base, (uint8)(1U << TIMER(Channel)), TRUE);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CompleteTxOperationUsingDma
 * Description   : Complete operation of the UART receiver using DMA.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_CompleteRxOperationUsingDma(const uint8 Channel)
{
    Flexio_Uart_Ip_StateStructureType * UartState;
    FLEXIO_Type * Base;

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Disable rx DMA requests for the current instance */
    Flexio_Mcl_Ip_SetShifterDMARequest(Base, (uint8)(1U << SHIFTER(Channel)), FALSE);

    if (FLEXIO_UART_IP_STATUS_ABORTED == UartState->Status)
    {
        (void)Flexio_Uart_Ip_ReadShifterBuffer(Base, SHIFTER(Channel));
    }
    /* End transfer */
    Flexio_Uart_Ip_StopTransfer(Channel);
    /* Update the busy flag */
    UartState->DriverIdle = FALSE;
    /* If the current reception hasn't been aborted, update the status */
    if (FLEXIO_UART_IP_STATUS_BUSY == UartState->Status)
    {
        UartState->Status = FLEXIO_UART_IP_STATUS_SUCCESS;
        /* Call the callback to notify application that the transfer is complete */
        Flexio_Uart_Ip_Callback(Channel, FLEXIO_UART_IP_EVENT_END_TRANSFER);
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ConfigureRxShifter
 * Description   : Configures Rx shifter the FLEXIO module for UART
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_ConfigureRxShifter(const uint8 Channel, const uint8 DataPin)
{
    FLEXIO_Type *Base;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Configure rx shifter */
    Flexio_Uart_Ip_SetShifterConfig(Base,
                                    SHIFTER(Channel),
                                    FLEXIO_SHIFTER_START_BIT_0,
                                    FLEXIO_SHIFTER_STOP_BIT_1,
                                    FLEXIO_SHIFTER_SOURCE_PIN
                                   );
    Flexio_Uart_Ip_SetShifterControl(Base,
                                     SHIFTER(Channel),
                                     FLEXIO_SHIFTER_MODE_DISABLED,
                                     TIMER(Channel),
                                     FLEXIO_TIMER_POLARITY_NEGEDGE
                                    );
    Flexio_Uart_Ip_SetPinShifterControl(Base,
                                        SHIFTER(Channel),
                                        DataPin,             /* Input from rx pin */
                                        FLEXIO_PIN_POLARITY_HIGH,
                                        FLEXIO_PIN_CONFIG_DISABLED
                                       );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ConfigureRxTimer
 * Description   : Configures Rx timer the FLEXIO module for UART
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_ConfigureRxTimer(const uint8 Channel, const uint8 DataPin, const Flexio_Uart_Ip_TimerDecrementType TimerDec)
{
    FLEXIO_Type *Base;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    Flexio_Uart_Ip_SetTimerConfig(Base,
                                  TIMER(Channel),
                                  FLEXIO_TIMER_RESET_PIN_RISING,
                                  TimerDec,                                   /* Decrement on FlexIO clock */
                                  FLEXIO_TIMER_INITOUT_ONE_RESET
                                 );

    Flexio_Uart_Ip_SetTimerStartStopBitConfig(Base,
                                              TIMER(Channel),
                                              FLEXIO_TIMER_START_BIT_ENABLED,
                                              FLEXIO_TIMER_STOP_BIT_TIM_DIS
                                             );

    Flexio_Uart_Ip_SetTimerCondition(Base,
                                     TIMER(Channel),
                                     FLEXIO_TIMER_ENABLE_PIN_POSEDGE,            /* Enable when data is available */
                                     FLEXIO_TIMER_DISABLE_TIM_CMP
                                    );

    Flexio_Uart_Ip_SetTimerControl(Base, TIMER(Channel), FLEXIO_TIMER_MODE_DISABLED);

    Flexio_Uart_Ip_SetTimerTrigger(Base,
                                   TIMER(Channel),
                                   0U,                                            /* Trigger unused */
                                   FLEXIO_TRIGGER_POLARITY_HIGH,
                                   FLEXIO_TRIGGER_SOURCE_EXTERNAL
                                  );

    Flexio_Uart_Ip_SetPinTimerControl(Base,
                                     TIMER(Channel),
                                     DataPin,                                   /* Input from rx pin */
                                     FLEXIO_PIN_POLARITY_LOW,
                                     FLEXIO_PIN_CONFIG_DISABLED
                                    );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ConfigureTxShifter
 * Description   : Configures Tx shifter the FLEXIO module for UART
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_ConfigureTxShifter(const uint8 Channel, const uint8 DataPin)
{
    FLEXIO_Type *Base;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    /* Configure tx shifter */
    Flexio_Uart_Ip_SetShifterConfig(Base,
                                    SHIFTER(Channel),
                                    FLEXIO_SHIFTER_START_BIT_0,
                                    FLEXIO_SHIFTER_STOP_BIT_1,
                                    FLEXIO_SHIFTER_SOURCE_PIN
                                   );
    Flexio_Uart_Ip_SetShifterControl(Base,
                                     SHIFTER(Channel),
                                     FLEXIO_SHIFTER_MODE_TRANSMIT,
                                     TIMER(Channel),
                                     FLEXIO_TIMER_POLARITY_POSEDGE
                                    );
    Flexio_Uart_Ip_SetPinShifterControl(Base,
                                        SHIFTER(Channel),
                                        DataPin,             /* Output on tx pin */
                                        FLEXIO_PIN_POLARITY_HIGH,
                                        FLEXIO_PIN_CONFIG_OUTPUT
                                       );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_ConfigureTxTimer
 * Description   : Configures Tx timer the FLEXIO module for UART
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_ConfigureTxTimer(const uint8 Channel, const Flexio_Uart_Ip_TimerDecrementType TimerDec)
{
    FLEXIO_Type *Base;

    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    Flexio_Uart_Ip_SetTimerConfig(Base,
                                  TIMER(Channel),
                                  FLEXIO_TIMER_RESET_NEVER,
                                  TimerDec,                             /* Decrement on FlexIO clock */
                                  FLEXIO_TIMER_INITOUT_ONE
                                 );

    Flexio_Uart_Ip_SetTimerStartStopBitConfig(Base,
                                              TIMER(Channel),
                                              FLEXIO_TIMER_START_BIT_ENABLED,
                                              FLEXIO_TIMER_STOP_BIT_TIM_DIS
                                             );

    Flexio_Uart_Ip_SetTimerCondition(Base,
                                     TIMER(Channel),
                                     FLEXIO_TIMER_ENABLE_TRG_HIGH,         /* Enable when Tx data is available */
                                     FLEXIO_TIMER_DISABLE_TIM_CMP
                                    );

    Flexio_Uart_Ip_SetTimerControl(Base, TIMER(Channel), FLEXIO_TIMER_MODE_DISABLED);

    Flexio_Uart_Ip_SetTimerTrigger(Base,
                                   TIMER(Channel),
                                   (uint8)((uint8)(SHIFTER(Channel) << 2U) + 1U), /* Trigger on tx shifter status flag */
                                   FLEXIO_TRIGGER_POLARITY_LOW,
                                   FLEXIO_TRIGGER_SOURCE_INTERNAL
                                  );

    Flexio_Uart_Ip_SetPinTimerControl(Base,
                                      TIMER(Channel),
                                      0U,                                     /* Pin unused */
                                      FLEXIO_PIN_POLARITY_HIGH,
                                      FLEXIO_PIN_CONFIG_DISABLED
                                     );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_CheckTransferCompleteData
 * Description   : This function will be waited until the data is completely transfer the data.
 *
 *END**************************************************************************/
static void Flexio_Uart_Ip_CheckTransferCompleteData(const uint8 Channel)
{
    const FLEXIO_Type *Base;
    const Flexio_Uart_Ip_UserConfigType *UartUserCfg;
    Flexio_Uart_Ip_StateStructureType * UartState;
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    UartUserCfg = Flexio_Uart_Ip_apUserConfig[Channel];
    Base = Flexio_Uart_Ip_apBases[FLEXIO_HW_INSTANCE];

    UartState = (Flexio_Uart_Ip_StateStructureType *)Flexio_Uart_Ip_apStateStructuresArray[Channel];

    Flexio_Uart_Ip_StartTimeout(&StartTime, &TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_VALUE_US, FLEXIO_UART_IP_TIMEOUT_TYPE);
    if (FLEXIO_UART_IP_DIRECTION_TX == UartUserCfg->Direction)
    {
        while (!Flexio_Mcl_Ip_GetTimerStatus(Base, TIMER(Channel)) && \
               !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
              )
        {}
    }
    else
    {
        while (!Flexio_Mcl_Ip_GetShifterStatus(Base, SHIFTER(Channel)) && \
               !Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE) \
              )
        {}
        if (Flexio_Mcl_Ip_GetShifterStatus(Base, SHIFTER(Channel)))
        {
            /* Read Dummy */
            (void)Flexio_Uart_Ip_ReadShifterBuffer(Base, SHIFTER(Channel));
        }
    }

    if (Flexio_Uart_Ip_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, FLEXIO_UART_IP_TIMEOUT_TYPE))
    {
      /* In case timeout occur */
        UartState->Status = FLEXIO_UART_IP_STATUS_TIMEOUT;
    }
}
#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */

#ifdef __cplusplus
}
#endif

/** @} */
