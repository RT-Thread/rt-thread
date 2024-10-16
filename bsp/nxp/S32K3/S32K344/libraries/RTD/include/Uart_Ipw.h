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

#ifndef UART_IPW_H
#define UART_IPW_H

/**
*   @file
*   @internal
*   @addtogroup UART_IPW_DRIVER
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
#include "Uart_Ipw_Types.h"
#include "CDD_Uart_Defines.h"
#include "Uart_Types.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define UART_IPW_VENDOR_ID                    43
#define UART_IPW_AR_RELEASE_MAJOR_VERSION     4
#define UART_IPW_AR_RELEASE_MINOR_VERSION     7
#define UART_IPW_AR_RELEASE_REVISION_VERSION  0
#define UART_IPW_SW_MAJOR_VERSION             5
#define UART_IPW_SW_MINOR_VERSION             0
#define UART_IPW_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/*Checks against Uart_Ipw_Types.h */
#if (UART_IPW_VENDOR_ID!= UART_IPW_TYPES_VENDOR_ID)
    #error "Uart_Ipw.h and Uart_Ipw_Types.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION   != UART_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION   != UART_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION!= UART_IPW_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw.h and Uart_Ipw_Types.h are different"
#endif
#if ((UART_IPW_SW_MAJOR_VERSION!= UART_IPW_TYPES_SW_MAJOR_VERSION) || \
     (UART_IPW_SW_MINOR_VERSION!= UART_IPW_TYPES_SW_MINOR_VERSION) || \
     (UART_IPW_SW_PATCH_VERSION!= UART_IPW_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw.h and Uart_Ipw_Types.h are different"
#endif

/*Checks against Uart_Types.h */
#if (UART_IPW_VENDOR_ID!= UART_TYPES_VENDOR_ID)
    #error "Uart_Ipw.h and Uart_Types.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION   != UART_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION   != UART_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION!= UART_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw.h and Uart_Types.h are different"
#endif
#if ((UART_IPW_SW_MAJOR_VERSION!= UART_TYPES_SW_MAJOR_VERSION) || \
     (UART_IPW_SW_MINOR_VERSION!= UART_TYPES_SW_MINOR_VERSION) || \
     (UART_IPW_SW_PATCH_VERSION!= UART_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw.h and Uart_Types.h are different"
#endif

/* Checks against CDD_Uart_Defines.h */
#if (UART_IPW_VENDOR_ID != UART_DEFINES_VENDOR_ID_CFG)
    #error "Uart_Ipw.h and CDD_Uart_Defines.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION    != UART_DEFINES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION    != UART_DEFINES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION != UART_DEFINES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Uart_Ipw.h and CDD_Uart_Defines.h are different"
#endif
/* Check if current file and CDD_Uart_Defines.h header file are of the same Software version */
#if ((UART_IPW_SW_MAJOR_VERSION != UART_DEFINES_SW_MAJOR_VERSION_CFG) || \
     (UART_IPW_SW_MINOR_VERSION != UART_DEFINES_SW_MINOR_VERSION_CFG) || \
     (UART_IPW_SW_PATCH_VERSION != UART_DEFINES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Uart_Ipw.h and CDD_Uart_Defines.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"
/**
* @internal
* @brief   Initialize an Uart channel.
* @details This function calls a LLD function initializes all hardware registers needed to
*          start the Uart functionality on the selected channel.
*
* @param   [in]    Channel  Uart channel to be initialized.
*          [in]    Config Configuration pointer containing hardware specific settings.
*
* @return            void.
*
*/
void Uart_Ipw_Init(uint8 Channel, const Uart_Ipw_HwConfigType* Config);

/**
* @internal
* @brief   De-initialize an Uart channel.
* @details This function calls a LLD function de-initializes an Uart Hw instance and resets the current
            information regarding the current channel
*
* @param[in] Channel  Uart channel to be de-initialized.
*
* @return            void.
*
*/
void Uart_Ipw_Deinit(uint8 Channel);

/**
* @internal
* @brief  Retrieves the baudrate value configured for the current channel.
* @details This function calls a LLD function returns the baudrate value configured for the given channel
* via a pointer parameter provided by user.
*
* @param[in] Channel           Uart channel where the baudrate shall be configured
* @param[out] BaudrateValue     The pointer which will contain the baudrate value.
*
* @return   void
*
*/

void Uart_Ipw_GetBaudrate(uint8 Channel, uint32* BaudrateValue);

/**
* @internal
* @brief  Set a baudrate value for the current channel.
* @details This function calls a LLD function which sets a baudrate value for a given channel,
*
* @param[in] Channel          Uart channel where the baudrate shall be configured
* @param[in] BaudRateValue     The baudrate value to be configured.
* @param[in] ClockFrequency  The clock frequency set for the Uart module.
*
* @return   E_OK:     Baud rate successfully configured
*           E_NOT_OK: Baud rate wasn't successfully configured
*
*/
Std_ReturnType Uart_Ipw_SetBaudrate(uint8 Channel, Uart_BaudrateType BaudRateValue, uint32 ClockFrequency);

/**
* @internal
* @brief  Aborts an on-going reception.
* @details This function calls a LLD function which ends a reception earlier.
*
* @param[in] Channel          Uart channel where the reception shall be ended.
*
* @return   E_OK:     The reception ended successfully
*           E_NOT_OK: The reception didn't end successfully
*
*/
Std_ReturnType Uart_Ipw_AbortReceivingData(uint8 Channel);

/**
* @internal
* @brief  Aborts an on-going transmission.
* @details This function calls a LLD function which ends a transfer earlier.
*
* @param[in] Channel          Uart channel where the transmission shall be ended.
*
* @return   E_OK:     The transfer ended successfully
*           E_NOT_OK: The transfer didn't end successfully
*
*/
Std_ReturnType Uart_Ipw_AbortSendingData(uint8 Channel);

/**
* @internal
* @brief  Sets a tx buffer.
* @details This function calls a LLD function which sets a buffer for continuos transmission.
*
* @param[in] Channel  Uart channel where to set the buffer.
*
* @return  void
*/
void Uart_Ipw_SetTxBuffer(uint8 Channel, const uint8 *Buffer, uint32 BufferSize);

/**
* @internal
* @brief  Sets a rx buffer.
* @details This function calls a LLD function which sets a buffer for continuos reception.
*
* @param[in] Channel  Uart channel where to set the buffer.
*
* @return  void
*/
void Uart_Ipw_SetRxBuffer(uint8 Channel, uint8 *Buffer, uint32 BufferSize);

/**
* @internal
* @brief  Sends a buffer synchronously.
* @details This function calls a LLD function which sends BufferSize bytes using polling method.
*
* @param[in] Channel     Uart channel used for transmission.
* @param[in] Buffer      Buffer to send.
* @param[in] BufferSize  The number of bytes to send.
* @param[in] Timeout     The timeout value in us.
*
*
* @return   E_OK:                   Tranmission ended successfully
*           UART_STATUS_TIMEOUT:         Tranmission has timeout
*/
Std_ReturnType Uart_Ipw_SyncSend(uint8 Channel, const uint8* Buffer, uint32 BufferSize, uint32 Timeout);

/**
* @internal
* @brief  Receives a buffer synchronously.
* @details This function calls a LLD function which receives BufferSize bytes using polling method.
*
* @param[in] Channel     Uart channel used for reception.
* @param[in] Buffer      Buffer to receive.
* @param[in] BufferSize  The number of bytes to receive.
* @param[in] Timeout        The timeout value in us.
*
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
*           UART_STATUS_TIMEOUT:     Reception has timeout
*/
Std_ReturnType Uart_Ipw_SyncReceive(uint8 Channel, uint8* Buffer, uint32 BufferSize, uint32 Timeout);

/**
* @internal
* @brief  Receives a buffer asynchronously.
* @details This function calls a LLD function which receives BufferSize bytes using an asynchornous method.
*
* @param[in] Channel      Uart channel used for reception.
* @param[in] Buffer        Buffer to receive.
* @param[in] BufferSize  The number of bytes to receive.
*
*
* @return   E_OK:               Reception started successfully
            E_NOT_OK:           Reception didn't start successfully
*/
Std_ReturnType Uart_Ipw_AsyncReceive(uint8 Channel, uint8 *Buffer, uint32 BufferSize);

/**
* @internal
* @brief  Sends a buffer asynchronously.
* @details This function calls a LLD function which sends BufferSize bytes using an asynchornous method.
*
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to send.
* @param[in] BufferSize  The number of bytes to send.
*
*
* @return   E_OK:               Transmission started successfully
            E_NOT_OK:           Transmission didn't start successfully
*/
Std_ReturnType Uart_Ipw_AsyncSend(uint8 Channel, const uint8 *Buffer, uint32 BufferSize);

/**
* @internal
* @brief  Retrieves the status of the previous transfer.
* @details This function calls a LLD function which retrieves the status of the previous transfer
*          and the number of the remaining bytes to send.
*
* @param[in] Channel   Uart channel.
* @param[out] BytesRemaining   The pointer where to write the number of remaining bytes
*
*
* @return   UART_NO_ERR0R:                  The previous transfer ended successfully
            UART_STATUS_OPERATION_ONGOING      The transfer is still on going
            UART_STATUS_ABORTED            The previous transfer was aborted
            UART_STATUS_TIMEOUT          The previous transfer was timeout

*/
Uart_StatusType Uart_Ipw_GetTransmitStatus(uint8 Channel, uint32 *BytesRemaining);

/**
* @internal
* @brief  Retrieves the status of the previous reception.
* @details This function calls a LLD function which retrieves the status of the previous reception
*          and the number of the remaining bytes to receive.
*
* @param[in] Channel   Uart channel.
* @param[out] BytesRemaining   The pointer where to write the number of remaining bytes
*
*
* @return   UART_NO_ERR0R:                  The previous transfer ended successfully
            UART_STATUS_OPERATION_ONGOING          The reception is still on going
            UART_STATUS_ABORTED                    The previous reception was aborted
            UART_STATUS_FRAMING_ERROR            Uart framing error
            UART_STATUS_RX_OVERRUN_ERROR         Uart overrun error
            UART_STATUS_PARITY_ERROR             Uart overrun error
            UART_STATUS_TIMEOUT                  Uart operation has timeout

*/
Uart_StatusType Uart_Ipw_GetReceiveStatus(uint8 Channel, uint32 *BytesRemaining);

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /*UART_IPW_H*/
