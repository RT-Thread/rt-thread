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
#ifndef CDD_UART_H
#define CDD_UART_H
/**
*   @file
*
*   @defgroup uart_driver UART Driver
*   @addtogroup  uart_driver UART Driver
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
#include "Mcal.h"
#include "CDD_Uart_Cfg.h"
#include "CDD_Uart_Defines.h"
#include "Uart_Types.h"
#include "Uart_Ipw.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define UART_MODULE_ID                      255
#define UART_AR_RELEASE_MAJOR_VERSION       4
#define UART_AR_RELEASE_MINOR_VERSION       7
#define UART_AR_RELEASE_REVISION_VERSION    0
#define UART_SW_MAJOR_VERSION               5
#define UART_SW_MINOR_VERSION               0
#define UART_SW_PATCH_VERSION               0
#define UART_VENDOR_ID                      43

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/*Checks against CDD_Uart_Defines.h */
#if (UART_VENDOR_ID!= UART_DEFINES_VENDOR_ID_CFG)
    #error "CDD_Uart.h and CDD_Uart_Defines.h have different vendor ids"
#endif
#if ((UART_AR_RELEASE_MAJOR_VERSION   != UART_DEFINES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (UART_AR_RELEASE_MINOR_VERSION   != UART_DEFINES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (UART_AR_RELEASE_REVISION_VERSION!= UART_DEFINES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AUTOSAR Version Numbers of CDD_Uart.h and CDD_Uart_Defines.h are different"
#endif
#if ((UART_SW_MAJOR_VERSION!= UART_DEFINES_SW_MAJOR_VERSION_CFG) || \
     (UART_SW_MINOR_VERSION!= UART_DEFINES_SW_MINOR_VERSION_CFG) || \
     (UART_SW_PATCH_VERSION!= UART_DEFINES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of CDD_Uart.h and CDD_Uart_Defines.h are different"
#endif
/*Checks against Uart_Ipw.h */
#if (UART_VENDOR_ID!= UART_IPW_VENDOR_ID)
    #error "CDD_Uart.h and Uart_Ipw.h have different vendor ids"
#endif
#if ((UART_AR_RELEASE_MAJOR_VERSION   != UART_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (UART_AR_RELEASE_MINOR_VERSION   != UART_IPW_AR_RELEASE_MINOR_VERSION) || \
     (UART_AR_RELEASE_REVISION_VERSION!= UART_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of CDD_Uart.h and Uart_Ipw.h are different"
#endif
#if ((UART_SW_MAJOR_VERSION!= UART_IPW_SW_MAJOR_VERSION) || \
     (UART_SW_MINOR_VERSION!= UART_IPW_SW_MINOR_VERSION) || \
     (UART_SW_PATCH_VERSION!= UART_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Uart.h and Uart_Ipw.h are different"
#endif
/* Checks against CDD_Uart_Cfg.h */
#if (UART_VENDOR_ID != UART_CFG_VENDOR_ID)
    #error "CDD_Uart.h and CDD_Uart_Cfg.h have different vendor ids"
#endif
#if ((UART_AR_RELEASE_MAJOR_VERSION   != UART_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (UART_AR_RELEASE_MINOR_VERSION   != UART_CFG_AR_RELEASE_MINOR_VERSION) || \
     (UART_AR_RELEASE_REVISION_VERSION!= UART_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of CDD_Uart.h and CDD_Uart_Cfg.h are different"
#endif
#if ((UART_SW_MAJOR_VERSION!= UART_CFG_SW_MAJOR_VERSION) || \
     (UART_SW_MINOR_VERSION!= UART_CFG_SW_MINOR_VERSION) || \
     (UART_SW_PATCH_VERSION!= UART_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Uart.h and CDD_Uart_Cfg.h are different"
#endif
/* Checks against Uart_Types.h */
#if (UART_VENDOR_ID != UART_TYPES_VENDOR_ID)
    #error "CDD_Uart.h and Uart_Types.h have different vendor ids"
#endif
#if ((UART_AR_RELEASE_MAJOR_VERSION   != UART_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (UART_AR_RELEASE_MINOR_VERSION   != UART_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (UART_AR_RELEASE_REVISION_VERSION!= UART_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of CDD_Uart.h and Uart_Types.h are different"
#endif
#if ((UART_SW_MAJOR_VERSION!= UART_TYPES_SW_MAJOR_VERSION) || \
     (UART_SW_MINOR_VERSION!= UART_TYPES_SW_MINOR_VERSION) || \
     (UART_SW_PATCH_VERSION!= UART_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Uart.h and Uart_Types.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((UART_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (UART_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of CDD_Uart.h and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref Uart_h_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
#if STD_OFF == UART_PRECOMPILE_SUPPORT
UART_CONFIG_EXT
#endif
#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref Uart_h_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

/**
* @brief   Initializes the UART module.
* @details This function performs software initialization of UART
*          driver. It shall configure the Uart hardware peripheral for each channel.
*
* @param[in] Config - Pointer to UART driver configuration set.
*
* @return  void
*
* @pre     -
*
*
**/
void Uart_Init(const Uart_ConfigType * Config);

/**
* @brief   De-initializes the UART module.
* @details This function performs software de-initialization of UART
*          driver.
*
* @param   -
*
* @return  void
*
* @pre     -
*
*
**/
void Uart_Deinit(void);

/**
* @brief   Configures the baud rate for the serial communication.
* @details This function performs the setting of the communication baudrate provided in the parameter.
*
* @param[in] Channel - Uart channel to be addressed.
* @param[in] Baudrate - Baudrate value to be set.
*
* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          a transfer is on-going or
*                          wrong partition is addressed.
*
* @retval E_OK             Successfull baudrate configuration.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Std_ReturnType Uart_SetBaudrate(uint8 Channel, Uart_BaudrateType Baudrate);

/**
* @brief   Retrieves the baud rate which is currently set for the serial communication.
* @details This function returns via the second parameter the current serial baudrate.
*
* @param[in]  Channel - Uart channel to be addressed.
* @param[out] Baudrate - Pointer to a memory location where the baudrate value is returned.
*
* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          a transfer is on-going or
*                          wrong partition is addressed or
*                          a NULL_PTR pointer has been provided
*
* @retval E_OK             Successfull baudrate retrieval.
*
*
* @pre    Uart_Init function must be called before this API. Otherwise a random value can be returned.
*
*
**/
Std_ReturnType Uart_GetBaudrate(uint8 Channel, uint32 *Baudrate);

/**
* @brief   Configures a new buffer for continuous transfers.
* @details This function can be called inside a notification callback and
*          offers the possibility to change the buffer in order to assure a
*          continuous asynchronous transfer.
* @param[in] Channel - Uart channel to be addressed.
* @param[in] Buffer - The new buffer provided.
* @param[in] BufferSize - The size of the new buffer.
* @param[in] Direction - This parameter indicates for which type of transmission is the buffer set. Its values are UART_SEND for
*                   setting a buffer when the previous buffer is empty and there are more bytes to send and UART_RECEIVE to set
*                   a new buffer when the previous buffer is full with received buffer and there is more data to be received.
*
* @return                  void.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
void Uart_SetBuffer(uint8 Channel,  uint8* Buffer, uint32 BufferSize, Uart_DataDirectionType Direction);

/**
* @brief   Starts a synchronous transfer of bytes.
* @details This function starts sending a number of bytes in a synchronous manner.
*
* @param[in] Channel - Uart channel to be addressed.
* @param[in] Buffer - The buffer which contains the bytes to be sent.
* @param[in] BufferSize - The Buffer size.
* @param[in] Timeout - The timeout in us.

* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          Buffer is a NULL_PTR or
*                          BufferSize is 0, meaning no space has been allocated for the buffer or
*                          a wrong partition has been accessed or
*                          a transfer is already on going on the requested channel or
*                          timeout occured.
*
* @retval E_OK             Successful transfer.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Std_ReturnType Uart_SyncSend(uint8 Channel, const uint8* Buffer, uint32 BufferSize, uint32 Timeout);

/**
* @brief   Starts a synchronous reception of bytes.
* @details This function starts receiving a number of bytes in a synchronous manner.
*
* @param[in] Channel - Uart channel to be addressed.
* @param[in] Buffer - The buffer where the bytes will be located.
* @param[in] BufferSize - The Buffer size.
* @param[in] Timeout - The timeout in us.
*
* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          Buffer is a NULL_PTR or
*                          BufferSize is 0, meaning no space has been allocated for the buffer or
*                          a wrong partition has been accessed or
*                          a reception is already on going on the requested channel or
*                          timeout occured.
*
* @retval E_OK             Successful reception.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Std_ReturnType Uart_SyncReceive(uint8 Channel, uint8* Buffer, uint32 BufferSize, uint32 Timeout);

/**
* @brief   Aborts an on-going transfer.
* @details This function aborts either a reception or a transmission depending on the last parameter.
*
* @param[in] Channel - Uart channel to be addressed.
* @param[in] TransmissionType - Type of the transfer to be aborted. It can be either UART_SEND or UART_RECEIVE.
*
* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          a wrong partition has been accessed
*
* @retval E_OK             Successful transfer aborted or in case no transfer was on going.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Std_ReturnType Uart_Abort(uint8 Channel, Uart_DataDirectionType TransmissionType);

/**
* @brief   Starts an asynchronous transfer(send) of bytes.
* @details This function starts sending a number of bytes in an asynchronous manner. The transfer can be performed using
*          either DMA or interrupts depending on the transfer type configured on the addressed channel.
*
* @param[in] Channel - Uart channel to be addressed.
* @param[in] Buffer - The buffer where the data to be sent is located.
* @param[in] BufferSize - The Buffer size.
*
* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          Buffer is a NULL_PTR or
*                          BufferSize is 0, meaning no space has been allocated for the buffer or
*                          a wrong partition has been accessed or
*                          a transfer(send) is already on going on the requested channel.
*
* @retval E_OK             The transfer(send) started successfully.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Std_ReturnType Uart_AsyncSend(uint8 Channel, const uint8* Buffer, uint32 BufferSize);

/**
* @brief   Starts an asynchronous transfer(receive) of bytes.
* @details This function starts receiving a number of bytes in an asynchronous manner. The transfer can be performed using
*          either DMA or interrupts depending on the transfer type configured on the addressed channel.
*
* @param[in] Channel - Uart channel to be addressed.
* @param[in] Buffer - The buffer where the data to be received will located.
* @param[in] BufferSize - The Buffer size.
*
* @return                  Std_ReturnType.
* @retval E_NOT_OK         If the Uart Channel is not valid or
*                          Uart driver is not initialized or
*                          Buffer is a NULL_PTR or
*                          BufferSize is 0, meaning no space has been allocated for the buffer or
*                          a wrong partition has been accessed or
*                          a transfer(receive) is already on going on the requested channel.
*
* @retval E_OK             The transfer(receive) started successfully.
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Std_ReturnType Uart_AsyncReceive(uint8 Channel,  uint8* Buffer, uint32 BufferSize);

/**
* @brief   Returns the status of the previous transfer.
* @details This function returns the status of the previous transfer.
*          If there is a transfer in progress, this function will also get the number of remaining bytes at the time the function was called.
* @param[in]  Channel - Uart channel to be addressed.
* @param[out] BytesTransfered - A pointer where the number of remaining bytes will be written.
* @param[in]  TransferType - The type of trasfer in discussion (UART_SEND or UART_RECEIVE).
*
* @return  Uart_StatusType.
* @retval  UART_STATUS_NO_ERROR  - Operation has ended successfully.
* @retval  UART_STATUS_FRAMING_ERROR  - Operation has had a framing error. This status is returned only if the TransferType parameter is RECEIVE.
* @retval  UART_STATUS_RX_OVERRUN_ERROR  - Operation has had an overrun error. This status is returned only if the TransferType parameter is RECEIVE.
* @retval  UART_STATUS_PARITY_ERROR - Operation has had a parity error. This status is returned only if the TransferType parameter is RECEIVE.
* @retval  UART_STATUS_OPERATION_ONGOING - Operation has not finished at the moment of function call.
* @retval  UART_STATUS_ABORTED - Operation has been aborted.
* @retval  UART_STATUS_TIMEOUT - Operation has had timeout in synchronous transfer functions with timeout value pass in Timeout parameter
*                                or functions that use the loop function whose execution time exceeds the timeout value configured through the UI
*
*
* @pre    Uart_Init function must be called before this API.
*
*
**/
Uart_StatusType Uart_GetStatus(uint8 Channel, uint32 *BytesTransfered, Uart_DataDirectionType TransferType);

#if (UART_VERSION_INFO_API == STD_ON)
/**
* @brief   Returns the version information of this module.
* @details The version information includes:
*
*          - Two bytes for the Vendor ID
*          - Two bytes for the Module ID
*          - One byte  for the Instance ID
*          - Three bytes version number. The numbering shall be vendor
*            specific: it consists of:
*
*             - The major, the minor and the patch version number of
*               the module;
*             - The AUTOSAR specification version number shall not
*               be included. The AUTOSAR specification version number is
*               checked during compile time and therefore not required
*               in this API.
*
* @param[in,out] VersionInfo   Pointer for storing the version information
*                              of this module.
*
* @return void.
*
*
*
*
**/
void Uart_GetVersionInfo (Std_VersionInfoType * VersionInfo);
#endif /* (UART_VERSION_INFO_API == STD_ON) */

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* CDD_UART_H */
