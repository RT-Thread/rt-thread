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
*   @file
*   @internal
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

#include "Uart_Ipw.h"
#include "Uart_Ipw_Cfg.h"
#ifdef UART_IPW_LPUART_HW_USING
    #include "Lpuart_Uart_Ip.h"
#endif
#ifdef UART_IPW_FLEXIO_HW_USING
    #include "Flexio_Uart_Ip.h"
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define UART_IPW_VENDOR_ID_C                    43
#define UART_IPW_AR_RELEASE_MAJOR_VERSION_C     4
#define UART_IPW_AR_RELEASE_MINOR_VERSION_C     7
#define UART_IPW_AR_RELEASE_REVISION_VERSION_C  0
#define UART_IPW_SW_MAJOR_VERSION_C             5
#define UART_IPW_SW_MINOR_VERSION_C             0
#define UART_IPW_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/*Checks against Uart_Ipw.h */
#if (UART_IPW_VENDOR_ID_C!= UART_IPW_VENDOR_ID)
    #error "Uart_Ipw.c and Uart_Ipw.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION_C   != UART_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION_C   != UART_IPW_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION_C!= UART_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw.c and Uart_Ipw.h are different"
#endif
#if ((UART_IPW_SW_MAJOR_VERSION_C!= UART_IPW_SW_MAJOR_VERSION) || \
     (UART_IPW_SW_MINOR_VERSION_C!= UART_IPW_SW_MINOR_VERSION) || \
     (UART_IPW_SW_PATCH_VERSION_C!= UART_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw.c and Uart_Ipw.h are different"
#endif

/* Checks against Uart_Ipw_Cfg.h */
#if (UART_IPW_VENDOR_ID_C != UART_IPW_CFG_VENDOR_ID)
    #error "Uart_Ipw.c and Uart_Ipw_Cfg.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION_C    != UART_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION_C    != UART_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION_C != UART_IPW_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw.c and Uart_Ipw_Cfg.h are different"
#endif
#if ((UART_IPW_SW_MAJOR_VERSION_C != UART_IPW_CFG_SW_MAJOR_VERSION) || \
     (UART_IPW_SW_MINOR_VERSION_C != UART_IPW_CFG_SW_MINOR_VERSION) || \
     (UART_IPW_SW_PATCH_VERSION_C != UART_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw.c and Uart_Ipw_Cfg.h are different"
#endif

#ifdef UART_IPW_LPUART_HW_USING
/* Checks against Lpuart_Uart_Ip.h */
#if (UART_IPW_VENDOR_ID_C != LPUART_UART_IP_VENDOR_ID)
    #error "Uart_Ipw.c and Lpuart_Uart_Ip.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION_C    != LPUART_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION_C    != LPUART_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION_C != LPUART_UART_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw.c and Lpuart_Uart_Ip.h are different"
#endif
#if ((UART_IPW_SW_MAJOR_VERSION_C != LPUART_UART_IP_SW_MAJOR_VERSION) || \
     (UART_IPW_SW_MINOR_VERSION_C != LPUART_UART_IP_SW_MINOR_VERSION) || \
     (UART_IPW_SW_PATCH_VERSION_C != LPUART_UART_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw.c and Lpuart_Uart_Ip.h are different"
#endif
#endif

#ifdef UART_IPW_FLEXIO_HW_USING
/* Checks against Flexio_Uart_Ip.h */
#if (UART_IPW_VENDOR_ID_C != FLEXIO_UART_IP_VENDOR_ID)
    #error "Uart_Ipw.c and Flexio_Uart_Ip.h have different vendor ids"
#endif
#if ((UART_IPW_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw.c and Flexio_Uart_Ip.h are different"
#endif
#if ((UART_IPW_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_SW_MAJOR_VERSION) || \
     (UART_IPW_SW_MINOR_VERSION_C != FLEXIO_UART_IP_SW_MINOR_VERSION) || \
     (UART_IPW_SW_PATCH_VERSION_C != FLEXIO_UART_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw.c and Flexio_Uart_Ip.h are different"
#endif
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/
#if (UART_CALLBACK_DECLARED == STD_ON)
#define UART_START_SEC_VAR_INIT_8_NO_CACHEABLE
#include "Uart_MemMap.h"

static sint8 Uart_Ipw_s8HwMapping[UART_NUMBER_OF_INSTANCES] = UART_HW_CHANNELS_MAPPING_FOR_INIT;

#define UART_STOP_SEC_VAR_INIT_8_NO_CACHEABLE
#include "Uart_MemMap.h"
#endif /* UART_CALLBACK_DECLARED == STD_ON */
#define UART_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Uart_MemMap.h"

static const Uart_Ipw_HwConfigType *Uart_Ipw_apChnConfig[UART_CH_MAX_CONFIG];

#define UART_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Uart_MemMap.h"

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

#ifdef UART_IPW_LPUART_HW_USING
    /* Convert Lpuart Status type to Standard status type */
    static Uart_StatusType Uart_Ipw_LpuartConvertStatus(Lpuart_Uart_Ip_StatusType Status);
    /* Convert Uart Baudrate type to Ip Baudrate type */
    static Lpuart_Uart_Ip_BaudrateType Uart_Ipw_LpuartConvertBaudrateType(Uart_BaudrateType Baudrate);
#if (UART_CALLBACK_DECLARED == STD_ON)
    /* Convert HLD Uart Event type to Ip Event type */
    static Uart_EventType Uart_Ipw_LpuartConvertEventType(Lpuart_Uart_Ip_EventType Event);
#endif /* UART_CALLBACK_DECLARED == STD_ON */
#endif
#ifdef UART_IPW_FLEXIO_HW_USING
    /* Convert Flexio Status type to Standard status type */
    static Uart_StatusType Uart_Ipw_FlexioConvertStatus(Flexio_Uart_Ip_StatusType Status);
    /* Convert Uart Baudrate type to Ip Baudrate type */
    static Flexio_Uart_Ip_BaudrateType Uart_Ipw_FlexioConvertBaudrateType(Uart_BaudrateType Baudrate);
#if (UART_CALLBACK_DECLARED == STD_ON)
    /* Convert HLD Uart Event type to Ip Event type */
    static Uart_EventType Uart_Ipw_FlexioConvertEventType(Flexio_Uart_Ip_EventType Event);
#endif /* UART_CALLBACK_DECLARED == STD_ON */
#endif


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
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
void Uart_Ipw_Init(uint8 Channel, const Uart_Ipw_HwConfigType* Config)
{
    uint8 HwUnit = (uint8)Config->UartHwChannel;

    /* Save the mapping between hardware instance and logical channel */
    /* Save the channel settings */
    Uart_Ipw_apChnConfig[Channel] = Config;
    /* Call the LLD Initialization function */
    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
    #if (UART_CALLBACK_DECLARED == STD_ON)
        Uart_Ipw_s8HwMapping[HwUnit] = (sint8)Channel;
    #endif /* UART_CALLBACK_DECLARED == STD_ON */
        Lpuart_Uart_Ip_Init(HwUnit, Config->UserConfig->LpuartUserConfig);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
    #if (UART_CALLBACK_DECLARED == STD_ON)
        Uart_Ipw_s8HwMapping[UART_NUMBER_OF_INSTANCES - FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER + HwUnit] = (sint8)Channel;
    #endif /* UART_CALLBACK_DECLARED == STD_ON */
        Flexio_Uart_Ip_Init(HwUnit, Config->UserConfig->FlexioUartUserConfig);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */
}
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
void Uart_Ipw_Deinit(uint8 Channel)
{
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
    #if (UART_CALLBACK_DECLARED == STD_ON)
        /* Remove the current hw to logic mapping */
        Uart_Ipw_s8HwMapping[HwUnit] = -1;
    #endif /* UART_CALLBACK_DECLARED == STD_ON */
        (void)Lpuart_Uart_Ip_Deinit(HwUnit);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
    #if (UART_CALLBACK_DECLARED == STD_ON)
        /* Remove the current hw to logic mapping */
        Uart_Ipw_s8HwMapping[UART_NUMBER_OF_INSTANCES - FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER + HwUnit] = -1;
    #endif /* UART_CALLBACK_DECLARED == STD_ON */
        (void)Flexio_Uart_Ip_Deinit(HwUnit);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */
    /* Remove refference to the current channel configuration */
    Uart_Ipw_apChnConfig[Channel] = NULL_PTR;
}
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
Std_ReturnType Uart_Ipw_SetBaudrate(uint8 Channel, Uart_BaudrateType BaudRateValue, uint32 ClockFrequency)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;
#ifdef UART_IPW_LPUART_HW_USING
    Lpuart_Uart_Ip_BaudrateType LpuartBaud = Uart_Ipw_LpuartConvertBaudrateType(BaudRateValue);
#endif
#ifdef UART_IPW_FLEXIO_HW_USING
    Flexio_Uart_Ip_BaudrateType FlexioBaud = Uart_Ipw_FlexioConvertBaudrateType(BaudRateValue);
#endif

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        if (LPUART_UART_IP_STATUS_SUCCESS == Lpuart_Uart_Ip_SetBaudRate(HwUnit, LpuartBaud, ClockFrequency))
        {
            TempStatus = (uint8)E_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        if (FLEXIO_UART_IP_STATUS_SUCCESS == Flexio_Uart_Ip_SetBaudRate(HwUnit, FlexioBaud, ClockFrequency))
        {
            TempStatus = (uint8)E_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}
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
void Uart_Ipw_GetBaudrate(uint8 Channel, uint32 *BaudrateValue)
{
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_GetBaudRate(HwUnit, BaudrateValue);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_GetBaudRate(HwUnit, BaudrateValue);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */
}
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
Std_ReturnType Uart_Ipw_AbortSendingData(uint8 Channel)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        if (LPUART_UART_IP_STATUS_SUCCESS == Lpuart_Uart_Ip_AbortSendingData(HwUnit))
        {
            TempStatus = (uint8)E_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        if (FLEXIO_UART_IP_STATUS_SUCCESS == Flexio_Uart_Ip_AbortTransferData(HwUnit))
        {
            TempStatus = (uint8)E_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}
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
Std_ReturnType Uart_Ipw_AbortReceivingData(uint8 Channel)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        if (LPUART_UART_IP_STATUS_SUCCESS == Lpuart_Uart_Ip_AbortReceivingData(HwUnit))
        {
            TempStatus = (uint8)E_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        if (FLEXIO_UART_IP_STATUS_SUCCESS == Flexio_Uart_Ip_AbortTransferData(HwUnit))
        {
            TempStatus = (uint8)E_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}
/**
* @internal
* @brief  Sets a tx buffer.
* @details This function calls a LLD function which sets a buffer for continuos transmission.
*
* @param[in] Channel  Uart channel where to set the buffer.
*
* @return  void
*/
void Uart_Ipw_SetTxBuffer(uint8 Channel, const uint8 *Buffer, uint32 BufferSize)
{
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_SetTxBuffer(HwUnit, Buffer, BufferSize);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_SetTxBuffer(HwUnit, Buffer, BufferSize);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */
}
/**
* @brief  Sets a rx buffer.
* @details This function calls a LLD function which sets a buffer for continuos reception.
*
* @param[in] Channel  Uart channel where to set the buffer.
*
* @return  void
*/
void Uart_Ipw_SetRxBuffer(uint8 Channel, uint8 *Buffer, uint32 BufferSize)
{
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_SetRxBuffer(HwUnit, Buffer, BufferSize);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_SetRxBuffer(HwUnit, Buffer, BufferSize);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */
}
/**
* @internal
* @brief  Sends a buffer synchronously.
* @details This function calls a LLD function which sends BufferSize bytes using polling method.
*
* @param[in] Channel      Uart channel used for transmission.
* @param[in] Buffer        Buffer to send.
* @param[in] BufferSize  The number of bytes to send.
* @param[in] Timeout        The timeout value in us.
*
*
* @return   E_OK:                   Tranmission ended successfully
*           UART_STATUS_TIMEOUT:         Tranmission has timeout
*           E_NOT_OK                Tranmission didn't end successfully
*/

Std_ReturnType Uart_Ipw_SyncSend(uint8 Channel, const uint8 *Buffer, uint32 BufferSize, uint32 Timeout)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    /* LPUART is used */
    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_StatusType u32LpuartIpStatus;
        u32LpuartIpStatus = Lpuart_Uart_Ip_SyncSend(HwUnit, Buffer, BufferSize, Timeout);
        if (LPUART_UART_IP_STATUS_SUCCESS == u32LpuartIpStatus)
        {
            TempStatus = (uint8)E_OK;
        }
        else if (LPUART_UART_IP_STATUS_TIMEOUT == u32LpuartIpStatus)
        {
            TempStatus = (uint8)UART_STATUS_TIMEOUT;
        }
        else
        {
            TempStatus = (uint8)E_NOT_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_StatusType u32FlexioIpStatus;
        u32FlexioIpStatus = Flexio_Uart_Ip_SyncSend(HwUnit, Buffer, BufferSize, Timeout);
        if (FLEXIO_UART_IP_STATUS_SUCCESS == u32FlexioIpStatus)
        {
            TempStatus = (uint8)E_OK;
        }
        else if (FLEXIO_UART_IP_STATUS_TIMEOUT == u32FlexioIpStatus)
        {
            TempStatus = (uint8)UART_STATUS_TIMEOUT;
        }
        else
        {
            TempStatus = (uint8)E_NOT_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}
/**
* @internal
* @brief  Receives a buffer synchronously.
* @details This function calls a LLD function which receives BufferSize bytes using polling method.
*
* @param[in] Channel     Uart channel used for reception.
* @param[in] Buffer      Buffer to receive.
* @param[in] BufferSize  The number of bytes to receive.
* @param[in] Timeout     The timeout value in us.
*
*
* @return   E_OK:               Reception ended successfully
*           E_NOT_OK:           Reception didn't end successfully
*           UART_STATUS_TIMEOUT:     Reception has timeout
*/
Std_ReturnType Uart_Ipw_SyncReceive(uint8 Channel, uint8 *Buffer, uint32 BufferSize, uint32 Timeout)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    /* LPUART is used */
    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_StatusType u32LpuartIpStatus;
        u32LpuartIpStatus = Lpuart_Uart_Ip_SyncReceive(HwUnit, Buffer, BufferSize, Timeout);
        if (LPUART_UART_IP_STATUS_SUCCESS == u32LpuartIpStatus)
        {
            TempStatus = (uint8)E_OK;
        }
        else if (LPUART_UART_IP_STATUS_TIMEOUT == u32LpuartIpStatus)
        {
            TempStatus = (uint8)UART_STATUS_TIMEOUT;
        }
        else
        {
            TempStatus = (uint8)E_NOT_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_StatusType u32FlexioIpStatus;
        u32FlexioIpStatus = Flexio_Uart_Ip_SyncReceive(HwUnit, Buffer, BufferSize, Timeout);
        if (FLEXIO_UART_IP_STATUS_SUCCESS == u32FlexioIpStatus)
        {
            TempStatus = (uint8)E_OK;
        }
        else if (FLEXIO_UART_IP_STATUS_TIMEOUT == u32FlexioIpStatus)
        {
            TempStatus = (uint8)UART_STATUS_TIMEOUT;
        }
        else
        {
            TempStatus = (uint8)E_NOT_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}
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
Std_ReturnType Uart_Ipw_AsyncReceive(uint8 Channel, uint8 *Buffer, uint32 BufferSize)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    /* LPUART is used */
    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        if (LPUART_UART_IP_STATUS_SUCCESS == Lpuart_Uart_Ip_AsyncReceive(HwUnit, Buffer, BufferSize))
        {
            TempStatus = (uint8)E_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        if (FLEXIO_UART_IP_STATUS_SUCCESS == Flexio_Uart_Ip_AsyncReceive(HwUnit, Buffer, BufferSize))
        {
            TempStatus = (uint8)E_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}
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
Std_ReturnType Uart_Ipw_AsyncSend(uint8 Channel, const uint8 *Buffer, uint32 BufferSize)
{
    Std_ReturnType TempStatus = (uint8)E_NOT_OK;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;

    /* LPUART is used */
    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        if (LPUART_UART_IP_STATUS_SUCCESS == Lpuart_Uart_Ip_AsyncSend(HwUnit, Buffer, BufferSize))
        {
            TempStatus = (uint8)E_OK;
        }
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        if (FLEXIO_UART_IP_STATUS_SUCCESS == Flexio_Uart_Ip_AsyncSend(HwUnit, Buffer, BufferSize))
        {
            TempStatus = (uint8)E_OK;
        }
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}


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
Uart_StatusType Uart_Ipw_GetTransmitStatus(uint8 Channel, uint32 *BytesRemaining)
{
    Uart_StatusType TempStatus = UART_STATUS_TIMEOUT;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;
    (void)TempStatus;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_StatusType u32LpuartIpStatus;
        u32LpuartIpStatus = Lpuart_Uart_Ip_GetTransmitStatus(HwUnit, BytesRemaining);
        TempStatus = Uart_Ipw_LpuartConvertStatus(u32LpuartIpStatus);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_StatusType u32FlexioIpStatus;
        u32FlexioIpStatus = Flexio_Uart_Ip_GetStatus(HwUnit, BytesRemaining);
        TempStatus = Uart_Ipw_FlexioConvertStatus(u32FlexioIpStatus);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;
}

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
            UART_STATUS_OPERATION_ONGOING      The reception is still on going
            UART_STATUS_ABORTED            The previous reception was aborted
            UART_STATUS_FRAMING_ERROR     Uart framing error
            UART_STATUS_RX_OVERRUN_ERROR  Uart overrun error
            UART_STATUS_PARITY_ERROR       Uart overrun error
            UART_STATUS_TIMEOUT          Uart operation has timeout

*/
Uart_StatusType Uart_Ipw_GetReceiveStatus(uint8 Channel, uint32 *BytesRemaining)
{
    Uart_StatusType TempStatus = UART_STATUS_TIMEOUT;
    uint8 HwUnit = (uint8)Uart_Ipw_apChnConfig[Channel]->UartHwChannel;
    (void)TempStatus;

    if (LPUART_IP == Uart_Ipw_apChnConfig[Channel]->UartIpType)
    {
#ifdef UART_IPW_LPUART_HW_USING
        Lpuart_Uart_Ip_StatusType u32LpuartIpStatus;
        u32LpuartIpStatus = Lpuart_Uart_Ip_GetReceiveStatus(HwUnit, BytesRemaining);
        TempStatus = Uart_Ipw_LpuartConvertStatus(u32LpuartIpStatus);
#endif /* #ifdef UART_IPW_LPUART_HW_USING */
    }
#ifdef UART_IPW_FLEXIO_HW_USING
    else
    {
        Flexio_Uart_Ip_StatusType u32FlexioIpStatus;
        u32FlexioIpStatus = Flexio_Uart_Ip_GetStatus(HwUnit, BytesRemaining);
        TempStatus = Uart_Ipw_FlexioConvertStatus(u32FlexioIpStatus);
    }
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

    return TempStatus;

}

#ifdef UART_IPW_LPUART_HW_USING
/**
* @internal
* @brief  Convert Uart IP layer return status to standard return status.
* @details This function receives Uart IP layer return status and convert to standard return status.
* @param[in] Status        Uart IP status
*
*
* @return   Standard status
* This is not a public API as it is called from other driver functions.
*/
static Uart_StatusType Uart_Ipw_LpuartConvertStatus(Lpuart_Uart_Ip_StatusType Status)
{
    Uart_StatusType TempStatus = UART_STATUS_NO_ERROR;

    switch (Status)
    {
        case LPUART_UART_IP_STATUS_SUCCESS:
            TempStatus = UART_STATUS_NO_ERROR;
            break;

        case LPUART_UART_IP_STATUS_BUSY:
            TempStatus = UART_STATUS_OPERATION_ONGOING;
            break;

        case LPUART_UART_IP_STATUS_ABORTED:
            TempStatus = UART_STATUS_ABORTED;
            break;

        case LPUART_UART_IP_STATUS_TIMEOUT:
            TempStatus = UART_STATUS_TIMEOUT;
            break;

        case LPUART_UART_IP_STATUS_FRAMING_ERROR:
            TempStatus = UART_STATUS_FRAMING_ERROR;
            break;

        case LPUART_UART_IP_STATUS_RX_OVERRUN:
            TempStatus = UART_STATUS_RX_OVERRUN_ERROR;
            break;

        case LPUART_UART_IP_STATUS_NOISE_ERROR:
            TempStatus = UART_STATUS_NOISE_ERROR;
            break;

        case LPUART_UART_IP_STATUS_PARITY_ERROR:
            TempStatus = UART_STATUS_PARITY_ERROR;
            break;

        case LPUART_UART_IP_STATUS_DMA_ERROR:
            TempStatus = UART_STATUS_DMA_ERROR;
            break;
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
        case LPUART_UART_IP_STATUS_RX_IDLE_STATE:
            TempStatus = UART_STATUS_RX_IDLE_STATE;
            break;
#endif
        default:
            /* Do nothing */
            break;
    }

    return TempStatus;
}

/**
* @internal
* @brief  Convert Uart HLD baudrate type to IP baudrate type.
* @details This function receives HLD baudrate and convert to IP baudrate.
* @param[in] Baudrate        Uart HLD Baudrate
*
*
* @return   IP baudrate
* This is not a public API as it is called from other driver functions.
*/
static Lpuart_Uart_Ip_BaudrateType Uart_Ipw_LpuartConvertBaudrateType(Uart_BaudrateType Baudrate)
{
    Lpuart_Uart_Ip_BaudrateType TempBaud = LPUART_UART_BAUDRATE_1200;

    switch (Baudrate)
    {
        case UART_BAUDRATE_1200:
            TempBaud = LPUART_UART_BAUDRATE_1200;
            break;
        case UART_BAUDRATE_2400:
            TempBaud = LPUART_UART_BAUDRATE_2400;
            break;
        case UART_BAUDRATE_4800:
            TempBaud = LPUART_UART_BAUDRATE_4800;
            break;
        case UART_BAUDRATE_7200:
            TempBaud = LPUART_UART_BAUDRATE_7200;
            break;
        case UART_BAUDRATE_9600:
            TempBaud = LPUART_UART_BAUDRATE_9600;
            break;
        case UART_BAUDRATE_14400:
            TempBaud = LPUART_UART_BAUDRATE_14400;
            break;
        case UART_BAUDRATE_19200:
            TempBaud = LPUART_UART_BAUDRATE_19200;
            break;
        case UART_BAUDRATE_28800:
            TempBaud = LPUART_UART_BAUDRATE_28800;
            break;
        case UART_BAUDRATE_38400:
            TempBaud = LPUART_UART_BAUDRATE_38400;
            break;
        case UART_BAUDRATE_57600:
            TempBaud = LPUART_UART_BAUDRATE_57600;
            break;
        case UART_BAUDRATE_115200:
            TempBaud = LPUART_UART_BAUDRATE_115200;
            break;
        case UART_BAUDRATE_230400:
            TempBaud = LPUART_UART_BAUDRATE_230400;
            break;
        case UART_BAUDRATE_460800:
            TempBaud = LPUART_UART_BAUDRATE_460800;
            break;
        case UART_BAUDRATE_921600:
            TempBaud = LPUART_UART_BAUDRATE_921600;
            break;
        default:
            TempBaud = LPUART_UART_BAUDRATE_1843200;
            break;
    }
    return TempBaud;
}

#if (UART_CALLBACK_DECLARED == STD_ON)
/**
* @internal
* @brief  Convert Uart IP Event type to HLD Event type.
* @details This function receives IP Event and convert to HLD Event.
* @param[in] Event        Uart IP Event
*
*
* @return   HLD Event
* This is not a public API as it is called from other driver functions.
*/
static Uart_EventType Uart_Ipw_LpuartConvertEventType(Lpuart_Uart_Ip_EventType Event)
{
    Uart_EventType TempEvent;

    switch (Event)
    {
        case LPUART_UART_IP_EVENT_RX_FULL:
            TempEvent = UART_EVENT_RX_FULL;
            break;
        case LPUART_UART_IP_EVENT_TX_EMPTY:
            TempEvent = UART_EVENT_TX_EMPTY;
            break;
        case LPUART_UART_IP_EVENT_END_TRANSFER:
            TempEvent = UART_EVENT_END_TRANSFER;
            break;
#if (LPUART_UART_IP_ENABLE_TIMEOUT_INTERRUPT == STD_ON)
        case LPUART_UART_IP_EVENT_IDLE_STATE:
            TempEvent = UART_EVENT_IDLE_STATE;
            break;
#endif
        default:
            TempEvent = UART_EVENT_ERROR;
            break;
    }
    return TempEvent;
}
#endif

#endif /* #ifdef UART_IPW_LPUART_HW_USING */

#ifdef UART_IPW_FLEXIO_HW_USING
/**
* @internal
* @brief  Convert Uart IP layer return status to standard return status.
* @details This function receives Uart IP layer return status and convert to standard return status.
* @param[in] Status        Uart IP status
*
*
* @return   Standard status
* This is not a public API as it is called from other driver functions.
*/
static Uart_StatusType Uart_Ipw_FlexioConvertStatus(Flexio_Uart_Ip_StatusType Status)
{
    Uart_StatusType TempStatus = UART_STATUS_NO_ERROR;

    switch (Status)
    {
        case FLEXIO_UART_IP_STATUS_SUCCESS:
            TempStatus = UART_STATUS_NO_ERROR;
            break;
        case FLEXIO_UART_IP_STATUS_BUSY:
            TempStatus = UART_STATUS_OPERATION_ONGOING;
            break;
        case FLEXIO_UART_IP_STATUS_ABORTED:
            TempStatus = UART_STATUS_ABORTED;
            break;
        case FLEXIO_UART_IP_STATUS_TIMEOUT:
            TempStatus = UART_STATUS_TIMEOUT;
            break;
        case FLEXIO_UART_IP_STATUS_RX_OVERRUN:
            TempStatus = UART_STATUS_RX_OVERRUN_ERROR;
            break;
        case FLEXIO_UART_IP_STATUS_DMA_ERROR:
            TempStatus = UART_STATUS_DMA_ERROR;
            break;
        default:
            /* Do nothing */
            break;
    }

    return TempStatus;
}


/**
* @internal
* @brief  Convert Uart HLD baudrate type to IP baudrate type.
* @details This function receives HLD baudrate and convert to IP baudrate.
* @param[in] Baudrate        Uart HLD Baudrate
*
*
* @return   IP baudrate
* This is not a public API as it is called from other driver functions.
*/
static Flexio_Uart_Ip_BaudrateType Uart_Ipw_FlexioConvertBaudrateType(Uart_BaudrateType Baudrate)
{
    Flexio_Uart_Ip_BaudrateType TempBaud = FLEXIO_UART_BAUDRATE_1200;

    switch (Baudrate)
    {
        case UART_BAUDRATE_1200:
            TempBaud = FLEXIO_UART_BAUDRATE_1200;
            break;
        case UART_BAUDRATE_2400:
            TempBaud = FLEXIO_UART_BAUDRATE_2400;
            break;
        case UART_BAUDRATE_4800:
            TempBaud = FLEXIO_UART_BAUDRATE_4800;
            break;
        case UART_BAUDRATE_7200:
            TempBaud = FLEXIO_UART_BAUDRATE_7200;
            break;
        case UART_BAUDRATE_9600:
            TempBaud = FLEXIO_UART_BAUDRATE_9600;
            break;
        case UART_BAUDRATE_14400:
            TempBaud = FLEXIO_UART_BAUDRATE_14400;
            break;
        case UART_BAUDRATE_19200:
            TempBaud = FLEXIO_UART_BAUDRATE_19200;
            break;
        case UART_BAUDRATE_28800:
            TempBaud = FLEXIO_UART_BAUDRATE_28800;
            break;
        case UART_BAUDRATE_38400:
            TempBaud = FLEXIO_UART_BAUDRATE_38400;
            break;
        case UART_BAUDRATE_57600:
            TempBaud = FLEXIO_UART_BAUDRATE_57600;
            break;
        case UART_BAUDRATE_115200:
            TempBaud = FLEXIO_UART_BAUDRATE_115200;
            break;
        case UART_BAUDRATE_230400:
            TempBaud = FLEXIO_UART_BAUDRATE_230400;
            break;
        case UART_BAUDRATE_460800:
            TempBaud = FLEXIO_UART_BAUDRATE_460800;
            break;
        case UART_BAUDRATE_921600:
            TempBaud = FLEXIO_UART_BAUDRATE_921600;
            break;
        default:
            TempBaud = FLEXIO_UART_BAUDRATE_1843200;
            break;
    }
    return TempBaud;
}

#if (UART_CALLBACK_DECLARED == STD_ON)
/**
* @internal
* @brief  Convert Uart IP Event type to HLD Event type.
* @details This function receives IP Event and convert to HLD Event.
* @param[in] Event        Uart IP Event
*
*
* @return   HLD Event
* This is not a public API as it is called from other driver functions.
*/
static Uart_EventType Uart_Ipw_FlexioConvertEventType(Flexio_Uart_Ip_EventType Event)
{
    Uart_EventType TempEvent;

    switch (Event)
    {
        case FLEXIO_UART_IP_EVENT_RX_FULL:
            TempEvent = UART_EVENT_RX_FULL;
            break;
        case FLEXIO_UART_IP_EVENT_TX_EMPTY:
            TempEvent = UART_EVENT_TX_EMPTY;
            break;
        case FLEXIO_UART_IP_EVENT_END_TRANSFER:
            TempEvent = UART_EVENT_END_TRANSFER;
            break;
        default:
            TempEvent = UART_EVENT_ERROR;
            break;
    }
    return TempEvent;
}
#endif

#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */

#if (UART_CALLBACK_DECLARED == STD_ON)
#ifdef UART_IPW_LPUART_HW_USING

/**
* @internal
* @internal
* @brief   Low level driver User callback for Lpuart
* @details This function is called by the low level driver in the ISR.
*
*
* This is not a public API as it is called from other driver functions.
*/
void Uart_Ipw_LpuartCallback(const uint8 HwInstance, const Lpuart_Uart_Ip_EventType Event, const void *UserData)
{
    uint8 Channel = (uint8)Uart_Ipw_s8HwMapping[HwInstance];
    Uart_EventType ConvertEvent = Uart_Ipw_LpuartConvertEventType(Event);
    (void)UserData;

    if (Uart_Ipw_apChnConfig[Channel]->Callback != NULL_PTR)
    {
        Uart_Ipw_apChnConfig[Channel]->Callback(Channel, ConvertEvent);
    }
}

#endif /* #ifdef UART_IPW_LPUART_HW_USING */

#ifdef UART_IPW_FLEXIO_HW_USING

/**
* @internal
* @brief   Low level driver callback for Flexio
* @details This function is called by the low level driver in the ISR.
*
*
* This is not a public API as it is called from other driver functions.
*/
void Uart_Ipw_FlexioTransferCallback(const uint8 HwChannel, const Flexio_Uart_Ip_EventType Event, const void *UserData)
{
    uint8 Channel = (uint8)Uart_Ipw_s8HwMapping[UART_NUMBER_OF_INSTANCES - FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER + HwChannel];
    Uart_EventType ConvertEvent = Uart_Ipw_FlexioConvertEventType(Event);
    (void)UserData;

    if (Uart_Ipw_apChnConfig[Channel]->Callback != NULL_PTR)
    {
        Uart_Ipw_apChnConfig[Channel]->Callback(Channel, ConvertEvent);
    }
}
#endif /* #ifdef UART_IPW_FLEXIO_HW_USING */
#endif /* UART_CALLBACK_DECLARED == STD_ON */

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
