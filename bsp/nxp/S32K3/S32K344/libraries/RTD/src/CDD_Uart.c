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
*   @file CDD_Uart.c
*   @implements CDD_Uart.c_Artifact
*   @addtogroup UART
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "CDD_Uart.h"
#if ((UART_DEV_ERROR_DETECT == STD_ON) || (UART_RUNTIME_ERROR_DETECT ==STD_ON))
#include "Det.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define UART_VENDOR_ID_C                      43
#define UART_AR_RELEASE_MAJOR_VERSION_C       4
#define UART_AR_RELEASE_MINOR_VERSION_C       7
#define UART_AR_RELEASE_REVISION_VERSION_C    0
#define UART_SW_MAJOR_VERSION_C               5
#define UART_SW_MINOR_VERSION_C               0
#define UART_SW_PATCH_VERSION_C               0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Uart header file are of the same Autosar version */
#if (UART_VENDOR_ID_C != UART_VENDOR_ID)
    #error "CDD_Uart.c and CDD_Uart.h have different vendor ids"
#endif
#if ((UART_AR_RELEASE_MAJOR_VERSION_C    != UART_AR_RELEASE_MAJOR_VERSION) || \
     (UART_AR_RELEASE_MINOR_VERSION_C    != UART_AR_RELEASE_MINOR_VERSION) || \
     (UART_AR_RELEASE_REVISION_VERSION_C != UART_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of CDD_Uart.c and CDD_Uart.h are different"
#endif
/* Check if current file and Uart header file are of the same Software version */
#if ((UART_SW_MAJOR_VERSION_C != UART_SW_MAJOR_VERSION) || \
     (UART_SW_MINOR_VERSION_C != UART_SW_MINOR_VERSION) || \
     (UART_SW_PATCH_VERSION_C != UART_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Uart.c and CDD_Uart.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK

#if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Check if the source file and Det header file are of the same Autosar version */
        #if ((UART_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
             (UART_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AutoSar Version Numbers of CDD_Uart.c and Det.h are different"
        #endif
    #endif
 #endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"
/**
* @brief          UART driver status variable.
* @details        UART driver initialization status variable.
*/
static Uart_DrvStatusType Uart_au8DriverStatus[UART_MAX_PARTITIONS];

#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_CLEARED_32_NO_CACHEABLE
#include "Uart_MemMap.h"

/**
* @brief          Uart clock frequencies.
* @details        This variable retains the values of clock frequencies set at driver initialization for each channel.
*/
static uint32 Uart_au32ClockFrequency[UART_MAX_PARTITIONS][UART_CH_MAX_CONFIG];

#define UART_STOP_SEC_VAR_CLEARED_32_NO_CACHEABLE
#include "Uart_MemMap.h"
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"

#if (UART_PRECOMPILE_SUPPORT == STD_ON)
/**
* @brief          Global precompiled configuration pointer.
* @details        Pointer to the precompiled configuration structure.
*/
extern const Uart_ConfigType* const Uart_pxPBcfgVariantPredefined[UART_MAX_PARTITIONS];

#endif /* (UART_PRECOMPILE_SUPPORT == STD_OFF) */

#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/

#include "Uart_MemMap.h"
/**
* @brief          Global configuration pointer.
* @details        Pointer to the configuration structure.
*/
static const Uart_ConfigType * Uart_apConfig[UART_MAX_PARTITIONS];

#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Uart_MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

static Std_ReturnType Uart_StartSyncReceive(uint8 PartitionId, uint8 Channel, uint8* Buffer, uint32 BufferSize, uint32 Timeout);
static Std_ReturnType Uart_StartSyncSend(uint8 PartitionId, uint8 Channel, const uint8* Buffer, uint32 BufferSize, uint32 Timeout);
static Std_ReturnType Uart_StartAsyncReceive(uint8 PartitionId, uint8 Channel, uint8* Buffer, uint32 BufferSize);
static Std_ReturnType Uart_StartAsyncSend(uint8 PartitionId, uint8 Channel, const uint8* Buffer, uint32 BufferSize);
static void Uart_StartSetBuffer(uint8 PartitionId, uint8 Channel, uint8* Buffer, uint32 BufferSize, Uart_DataDirectionType Direction);

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @internal
* @brief  Start Receive data with polling method.
* @details This function will start receive data when Uart_Ipw_GetReceiveStatus do not in ONGOING status.
* @param[in] PartitionId       Partition ID
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to receive.
* @param[in] BufferSize  The number of bytes to receive.
*
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
*           UART_STATUS_TIMEOUT:     Reception has timeout
* This is not a public API as it is called from other driver functions.
*/
static Std_ReturnType Uart_StartSyncReceive(uint8 PartitionId, uint8 Channel, uint8* Buffer, uint32 BufferSize, uint32 Timeout)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    Uart_StatusType ReceiveStatus;

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Invalid PartitionId */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_PARAM_CONFIG);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
        }
        else
        {
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
            ReceiveStatus = Uart_Ipw_GetReceiveStatus(Channel, NULL_PTR);
            if (UART_STATUS_OPERATION_ONGOING == ReceiveStatus)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_CHANNEL_BUSY);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {

                TempReturn = Uart_Ipw_SyncReceive(Channel, Buffer, BufferSize, Timeout);
                (void)PartitionId;

                if ((uint8)UART_STATUS_TIMEOUT == TempReturn)
                {
                #if (UART_RUNTIME_ERROR_DETECT == STD_ON)
                    /* Timeout occur */
                    (void)Det_ReportRuntimeError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_TIMEOUT);
                #endif /* (UART_RUNTIME_ERROR_DETECT == STD_ON) */
                    TempReturn = E_NOT_OK;
                }
            }

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
        }
    }
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
    return TempReturn;
}

/**
* @internal
* @brief  Start Transfer data with polling method.
* @details This function will start transfer data when Uart_Ipw_GetReceiveStatus do not in ONGOING status.
* @param[in] PartitionId       Partition ID
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to send.
* @param[in] BufferSize  The number of bytes to send.
*
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
*           UART_STATUS_TIMEOUT:     Reception has timeout
* This is not a public API as it is called from other driver functions.
*/
static Std_ReturnType Uart_StartSyncSend(uint8 PartitionId, uint8 Channel, const uint8* Buffer, uint32 BufferSize, uint32 Timeout)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    Uart_StatusType TransmitStatus;

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Invalid PartitionId */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_PARAM_CONFIG);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
        }
        else
        {
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
            TransmitStatus = Uart_Ipw_GetTransmitStatus(Channel, NULL_PTR);
            if (UART_STATUS_OPERATION_ONGOING == TransmitStatus)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_CHANNEL_BUSY);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                TempReturn = Uart_Ipw_SyncSend(Channel, Buffer, BufferSize, Timeout);
                (void)PartitionId;

                if ((uint8)UART_STATUS_TIMEOUT == TempReturn)
                {
                #if (UART_RUNTIME_ERROR_DETECT == STD_ON)
                        /* Timeout occur */
                        (void)Det_ReportRuntimeError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_TIMEOUT);
                #endif /* (UART_RUNTIME_ERROR_DETECT == STD_ON) */
                    TempReturn = E_NOT_OK;
                }
            }

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
        }
    }
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
    return TempReturn;
}

/**
* @internal
* @brief  Start Receive data with asynchronously method.
* @details This function will start receive data when Uart_Ipw_GetReceiveStatus do not in ONGOING status.
* @param[in] PartitionId       Partition ID
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to receive.
* @param[in] BufferSize  The number of bytes to receive.
*
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
*           UART_STATUS_TIMEOUT:     Reception has timeout
* This is not a public API as it is called from other driver functions.
*/
static Std_ReturnType Uart_StartAsyncReceive(uint8 PartitionId, uint8 Channel, uint8* Buffer, uint32 BufferSize)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    Uart_StatusType ReceiveStatus;

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Invalid PartitionId */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_PARAM_CONFIG);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
        }
        else
        {
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
            ReceiveStatus = Uart_Ipw_GetReceiveStatus(Channel, NULL_PTR);
            if (UART_STATUS_OPERATION_ONGOING == ReceiveStatus)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_CHANNEL_BUSY);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                TempReturn = Uart_Ipw_AsyncReceive(Channel, Buffer, BufferSize);
                (void)PartitionId;
            }

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
        }
    }
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
    return TempReturn;
}

/**
* @internal
* @brief  Start Transfer data with asynchronously method.
* @details This function will start transfer data when Uart_Ipw_GetReceiveStatus do not in ONGOING status.
* @param[in] PartitionId       Partition ID
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to send.
* @param[in] BufferSize  The number of bytes to send.
*
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
*           UART_STATUS_TIMEOUT:     Reception has timeout
* This is not a public API as it is called from other driver functions.
*/
static Std_ReturnType Uart_StartAsyncSend(uint8 PartitionId, uint8 Channel, const uint8* Buffer, uint32 BufferSize)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    Uart_StatusType TransmitStatus;

    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Invalid PartitionId */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_PARAM_CONFIG);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
        }
        else
        {
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
            TransmitStatus = Uart_Ipw_GetTransmitStatus(Channel, NULL_PTR);
            if (UART_STATUS_OPERATION_ONGOING == TransmitStatus)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_CHANNEL_BUSY);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                TempReturn = Uart_Ipw_AsyncSend(Channel, Buffer, BufferSize);
                (void)PartitionId;
            }
    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
        }
    }
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
    return TempReturn;
}

/**
* @internal
* @brief  Sets a tx or rx buffer.
* @details This function will start set up a buffer to receive or transmit.
* @param[in] PartitionId       Partition ID
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to send.
* @param[in] BufferSize  The number of bytes to send.
* @param[in] Direction           Transmission type.
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
* This is not a public API as it is called from other driver functions.
*/
static void Uart_StartSetBuffer(uint8 PartitionId, uint8 Channel, uint8* Buffer, uint32 BufferSize, Uart_DataDirectionType Direction)
{
    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
    if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Invalid PartitionId */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBUFFER_ID, (uint8)UART_E_PARAM_CONFIG);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBUFFER_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
        }
        else
        {
    #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
            if (UART_SEND == Direction)
            {
                Uart_Ipw_SetTxBuffer(Channel,(const uint8 *)Buffer, BufferSize);
            }
            else
            {
                Uart_Ipw_SetRxBuffer(Channel, Buffer, BufferSize);
            }
            (void)PartitionId;
                    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
            }
        }
        #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
}
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/* implements     Uart_Init_Activity*/
void Uart_Init(const Uart_ConfigType * Config)
{
    uint8 u8ChLoop;
    uint8 PartitionId;
    uint8 Channel;

    /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    /* Check whether the Uart driver is in UART_DRV_UNINIT state */
    if (UART_DRV_UNINIT != Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Uart driver has been already initialized */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_INIT_ID, (uint8)UART_E_ALREADY_INITIALIZED);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        #if (UART_PRECOMPILE_SUPPORT == STD_OFF)
        /* Check Config for not being a null pointer */
        if (NULL_PTR == Config)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)

            /* Invalid pointer */
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_INIT_ID, (uint8)UART_E_INIT_FAILED);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
        else if (PartitionId != Config->PartitionId)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            /* Invalid PartitionId */
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_INIT_ID, (uint8)UART_E_PARAM_CONFIG);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
        else
        {
            Uart_apConfig[PartitionId] = Config;

        #else /* UART_PRECOMPILE_SUPPORT == STD_ON */
        if (NULL_PTR != Config)
        {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
            /* Invalid pointer */
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_INIT_ID, (uint8)UART_E_INIT_FAILED);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
        else if ((NULL_PTR == Uart_pxPBcfgVariantPredefined[PartitionId]) ||
                 (PartitionId != Uart_pxPBcfgVariantPredefined[PartitionId]->PartitionId))
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            /* Invalid PartitionId */
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_INIT_ID, (uint8)UART_E_PARAM_CONFIG);
            #endif /* UART_DEV_ERROR_DETECT == STD_ON */
        }
        #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
        else
        {
            Uart_apConfig[PartitionId] = Uart_pxPBcfgVariantPredefined[PartitionId];
            (void)Config;

    #endif /* UART_PRECOMPILE_SUPPORT == STD_ON */

            for (u8ChLoop = 0U; u8ChLoop < UART_CH_MAX_CONFIG; u8ChLoop++)
            {
                if (Uart_apConfig[PartitionId]->Configs[u8ChLoop] != NULL_PTR)
                {
                    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                    if (PartitionId == Uart_apConfig[PartitionId]->Configs[u8ChLoop]->ChannelPartitionId)
                    {
                    #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
                        Channel = Uart_apConfig[PartitionId]->Configs[u8ChLoop]->UartChannelId;
                        Uart_Ipw_Init(Channel, Uart_apConfig[PartitionId]->Configs[u8ChLoop]->UartChannelConfig);
                        Uart_au32ClockFrequency[PartitionId][Channel] = Uart_apConfig[PartitionId]->Configs[u8ChLoop]->ChannelClockFrequency;
                    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                    }
                    #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
                }
            }
            /* Update UART driver status to UART_DRV_INIT */
            Uart_au8DriverStatus[PartitionId] = UART_DRV_INIT;
        }
    }
}
/* implements     Uart_Deinit_Activity*/
void Uart_Deinit(void)
{
    uint8 u8ChLoop = 0U;
    uint8 PartitionId = 0U;
    uint8 Channel;
    Uart_StatusType ReceiveStatus;
    Uart_StatusType TransmitStatus;
    boolean IsAllChannelsIdle = TRUE;

    /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    /* Check whether the UART driver is in UART_DRV_UNINIT state */
    if (UART_DRV_INIT != Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        /* Uart driver has been already initialized */
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_DEINIT_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        for (u8ChLoop = 0U; u8ChLoop < UART_CH_MAX_CONFIG; u8ChLoop++)
        {
            if (Uart_apConfig[PartitionId]->Configs[u8ChLoop] != NULL_PTR)
            {
                #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                if (PartitionId == Uart_apConfig[PartitionId]->Configs[u8ChLoop]->ChannelPartitionId)
                {
                #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
                    Channel = Uart_apConfig[PartitionId]->Configs[u8ChLoop]->UartChannelId;
                    ReceiveStatus = Uart_Ipw_GetReceiveStatus(Channel, NULL_PTR);
                    TransmitStatus = Uart_Ipw_GetTransmitStatus(Channel, NULL_PTR);
                    /* Check whether channel is busy sending or receiving */
                    if ((UART_STATUS_OPERATION_ONGOING == ReceiveStatus) || (UART_STATUS_OPERATION_ONGOING == TransmitStatus))
                    {
                        IsAllChannelsIdle = FALSE;
                        break;
                    }
                #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                }
                #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
            }
        }

        if (IsAllChannelsIdle)
        {
            /* In case all of setting channel are free */
            for (u8ChLoop = 0U; u8ChLoop < UART_CH_MAX_CONFIG; u8ChLoop++)
            {
                if (Uart_apConfig[PartitionId]->Configs[u8ChLoop] != NULL_PTR)
                {
                    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                    if (PartitionId == Uart_apConfig[PartitionId]->Configs[u8ChLoop]->ChannelPartitionId)
                    {
                    #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
                        Channel = Uart_apConfig[PartitionId]->Configs[u8ChLoop]->UartChannelId;
                        /* Deinit channel */
                        Uart_Ipw_Deinit(Channel);
                    #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                    }
                    #endif /* UART_MULTIPARTITION_SUPPORT == STD_ON */
                }
            }
            Uart_au8DriverStatus[PartitionId] = UART_DRV_UNINIT;
            Uart_apConfig[PartitionId] = NULL_PTR;
        }
        else
        {
            /* In case one or more channels are busy */
            #if (UART_RUNTIME_ERROR_DETECT == STD_ON)
                    /* Timeout occur */
                    (void)Det_ReportRuntimeError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_DEINIT_ID, (uint8)UART_E_DEINIT_FAILED);
            #endif /* (UART_RUNTIME_ERROR_DETECT == STD_ON) */
        }
    }
}


/* implements     Uart_SetBaudrate_Activity*/
Std_ReturnType Uart_SetBaudrate(uint8 Channel, Uart_BaudrateType Baudrate)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;
    Uart_StatusType ReceiveStatus;
    Uart_StatusType TransmitStatus;

    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBAUDRATE_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */

    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBAUDRATE_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
        }
        else
        {
            #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
            if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                /* Invalid PartitionId */
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBAUDRATE_ID, (uint8)UART_E_PARAM_CONFIG);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBAUDRATE_ID, (uint8)UART_E_INVALID_CHANNEL);
                    #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
                }
                else
                {
            #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
                    ReceiveStatus = Uart_Ipw_GetReceiveStatus(Channel, NULL_PTR);
                    TransmitStatus = Uart_Ipw_GetTransmitStatus(Channel, NULL_PTR);
                    /* Check whether channel is busy sending or receiving */
                    if ((UART_STATUS_OPERATION_ONGOING == ReceiveStatus) || (UART_STATUS_OPERATION_ONGOING == TransmitStatus))
                    {
                        #if (UART_DEV_ERROR_DETECT == STD_ON)
                        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBAUDRATE_ID, (uint8)UART_E_CHANNEL_BUSY);
                        #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
                    }
                    else
                    {
                        TempReturn = Uart_Ipw_SetBaudrate(Channel, Baudrate, Uart_au32ClockFrequency[PartitionId][Channel]);
                    }

            #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                }
            }
            #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
        }
    }
    return TempReturn;
}


/* implements     Uart_GetBaudrate_Activity*/
Std_ReturnType Uart_GetBaudrate(uint8 Channel, uint32 *Baudrate)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;

    /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETBAUDRATE_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETBAUDRATE_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == Baudrate)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETBAUDRATE_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    /* Invalid PartitionId */
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETBAUDRATE_ID, (uint8)UART_E_PARAM_CONFIG);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
                    {
                        #if (UART_DEV_ERROR_DETECT == STD_ON)
                        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETBAUDRATE_ID, (uint8)UART_E_INVALID_CHANNEL);
                        #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
                    }
                    else
                    {
                #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */

                        Uart_Ipw_GetBaudrate(Channel, Baudrate);
                        TempReturn = E_OK;
                        (void)PartitionId;

                #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                    }
                }
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
        }
    }
    return TempReturn;
}


/* implements     Uart_Abort_Activity*/
Std_ReturnType Uart_Abort(uint8 Channel, Uart_DataDirectionType TransmissionType)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;

   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ABORT_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ABORT_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
            if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                /* Invalid PartitionId */
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ABORT_ID, (uint8)UART_E_PARAM_CONFIG);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ABORT_ID, (uint8)UART_E_INVALID_CHANNEL);
                    #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
                }
                else
                {
            #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */

                    if (UART_SEND == TransmissionType)
                    {
                        TempReturn = Uart_Ipw_AbortSendingData(Channel);

                    }
                    else
                    {
                        TempReturn = Uart_Ipw_AbortReceivingData(Channel);

                    }
                    (void)PartitionId;

            #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                }
            }
            #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
        }
    }
    return TempReturn;
}

/* implements     Uart_SetBuffer_Activity*/
void Uart_SetBuffer(uint8 Channel,  uint8* Buffer, uint32 BufferSize, Uart_DataDirectionType Direction)
{
    uint8 PartitionId;

   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBUFFER_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBUFFER_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == Buffer)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBUFFER_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (0U == BufferSize)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SETBUFFER_ID, (uint8)UART_E_INVALID_PARAMETER);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    Uart_StartSetBuffer(PartitionId, Channel, Buffer, BufferSize, Direction);
                }
            }
        }
    }
}



/* implements     Uart_SyncSend_Activity*/
Std_ReturnType Uart_SyncSend(uint8 Channel, const uint8* Buffer, uint32 BufferSize, uint32 Timeout)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;

   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == Buffer)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (0U == BufferSize)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCSEND_ID, (uint8)UART_E_INVALID_PARAMETER);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    TempReturn = Uart_StartSyncSend(PartitionId, Channel, Buffer, BufferSize, Timeout);
                }
            }
        }
    }
    return TempReturn;
}




/* implements     Uart_SyncReceive_Activity*/
Std_ReturnType Uart_SyncReceive(uint8 Channel, uint8* Buffer, uint32 BufferSize, uint32 Timeout)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;

   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == Buffer)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (0U == BufferSize)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_SYNCRECEIVE_ID, (uint8)UART_E_INVALID_PARAMETER);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    TempReturn = Uart_StartSyncReceive(PartitionId, Channel, Buffer, BufferSize, Timeout);
                }
            }
        }
    }
    return TempReturn;
}


/* implements     Uart_AsyncReceive_Activity*/
Std_ReturnType Uart_AsyncReceive(uint8 Channel, uint8* Buffer, uint32 BufferSize)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;

   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == Buffer)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (0U == BufferSize)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCRECEIVE_ID, (uint8)UART_E_INVALID_PARAMETER);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    TempReturn = Uart_StartAsyncReceive(PartitionId, Channel, Buffer, BufferSize);
                }
            }
        }
    }
    return TempReturn;
}


/* implements     Uart_AsyncSend_Activity*/
Std_ReturnType Uart_AsyncSend(uint8 Channel, const uint8* Buffer, uint32 BufferSize)
{
    Std_ReturnType TempReturn = E_NOT_OK;
    uint8 PartitionId;

   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == Buffer)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                if (0U == BufferSize)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_ASYNCSEND_ID, (uint8)UART_E_INVALID_PARAMETER);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    TempReturn = Uart_StartAsyncSend(PartitionId, Channel, Buffer, BufferSize);
                }
            }
        }
    }
    return TempReturn;
}

/* implements     Uart_GetStatus_Activity*/
Uart_StatusType Uart_GetStatus(uint8 Channel, uint32 *BytesTransfered, Uart_DataDirectionType TransferType)
{
    Uart_StatusType TempReturn;
    uint8 PartitionId;

    TempReturn = UART_STATUS_RX_OVERRUN_ERROR;
   /* Get partition ID of current processor */
    PartitionId = (uint8) Uart_GetUserID();

    if (UART_DRV_UNINIT == Uart_au8DriverStatus[PartitionId])
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETSTATUS_ID, (uint8)UART_E_UNINIT);
        #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Channel >= UART_CH_MAX_CONFIG)
        {
            #if (UART_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETSTATUS_ID, (uint8)UART_E_INVALID_CHANNEL);
            #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            if (NULL_PTR == BytesTransfered)
            {
                #if (UART_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETSTATUS_ID, (uint8)UART_E_INVALID_POINTER);
                #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
            }
            else
            {
                #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                if (PartitionId != Uart_apConfig[PartitionId]->PartitionId)
                {
                    #if (UART_DEV_ERROR_DETECT == STD_ON)
                    /* Invalid PartitionId */
                    (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETSTATUS_ID, (uint8)UART_E_PARAM_CONFIG);
                    #endif /* (UART_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    if (NULL_PTR == Uart_apConfig[PartitionId]->Configs[Channel])
                    {
                        #if (UART_DEV_ERROR_DETECT == STD_ON)
                        (void)Det_ReportError((uint16)UART_MODULE_ID, (uint8)0, (uint8)UART_GETSTATUS_ID, (uint8)UART_E_INVALID_CHANNEL);
                        #endif /* (UART_DEV_ERROR_DETECT     == STD_ON) */
                    }
                    else
                    {
                #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */

                        if (UART_SEND == TransferType)
                        {
                            TempReturn = Uart_Ipw_GetTransmitStatus(Channel, BytesTransfered);

                        }
                        else
                        {
                            TempReturn = Uart_Ipw_GetReceiveStatus(Channel, BytesTransfered);

                        }
                        (void)PartitionId;

                #if (UART_MULTIPARTITION_SUPPORT == STD_ON)
                    }
                }
                #endif /* (UART_MULTIPARTITION_SUPPORT == STD_ON) */
            }
        }
    }
    return TempReturn;
}

#if (UART_VERSION_INFO_API == STD_ON)
/* implements     Uart_GetVersionInfo_Activity*/
void Uart_GetVersionInfo (Std_VersionInfoType * VersionInfo)
{
    if (NULL_PTR == VersionInfo)
    {
        #if (UART_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)UART_MODULE_ID, \
                              (uint8)0, \
                              (uint8)UART_VERSIONINFO_ID, \
                              (uint8) UART_E_INVALID_POINTER \
                             );
        #endif /* UART_DEV_ERROR_DETECT == STD_ON */
    }
    else
    {

        VersionInfo->vendorID = (uint16) UART_VENDOR_ID;
        VersionInfo->moduleID = (uint8) UART_MODULE_ID;
        VersionInfo->sw_major_version = (uint8) UART_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = (uint8) UART_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = (uint8) UART_SW_PATCH_VERSION;
    }
}

#endif /* (UART_VERSION_INFO_API == STD_ON) */

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
