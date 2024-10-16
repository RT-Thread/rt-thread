/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
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

#ifndef DIO_IPW_H
#define DIO_IPW_H

/**
*   @file Dio_Ipw.h
*   @internal
*   @defgroup DIO_IPW Dio IPW
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Siul2_Dio_Ip.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define DIO_IPW_VENDOR_ID_H                    43
#define DIO_IPW_AR_RELEASE_MAJOR_VERSION_H     4
#define DIO_IPW_AR_RELEASE_MINOR_VERSION_H     7
#define DIO_IPW_AR_RELEASE_REVISION_VERSION_H  0
#define DIO_IPW_SW_MAJOR_VERSION_H             5
#define DIO_IPW_SW_MINOR_VERSION_H             0
#define DIO_IPW_SW_PATCH_VERSION_H             0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if Dio_Ipw header file and Siul2_Dio_Ip header file are of the same vendor */
#if (DIO_IPW_VENDOR_ID_H != SIUL2_DIO_IP_VENDOR_ID_H)
    #error "Dio_Ipw.h and Siul2_Dio_Ip.h have different vendor ids"
#endif

/* Check if  Dio_Ipw header file and Siul2_Dio_Ip header file are of the same Autosar version */
#if ((DIO_IPW_AR_RELEASE_MAJOR_VERSION_H    != SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (DIO_IPW_AR_RELEASE_MINOR_VERSION_H    != SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (DIO_IPW_AR_RELEASE_REVISION_VERSION_H != SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Dio_Ipw.h and Siul2_Dio_Ip.h are different"
#endif

/* Check if Dio_Ipw header file and Siul2_Dio_Ip header file are of the same Software version */
#if ((DIO_IPW_SW_MAJOR_VERSION_H != SIUL2_DIO_IP_SW_MAJOR_VERSION_H) || \
     (DIO_IPW_SW_MINOR_VERSION_H != SIUL2_DIO_IP_SW_MINOR_VERSION_H) || \
     (DIO_IPW_SW_PATCH_VERSION_H != SIUL2_DIO_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Dio_Ipw.h and Siul2_Dio_Ip.h are different"
#endif
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/
/** Bit mask for the leftmost channel in a port*/
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    #define DIO_IPW_BIT1_LEFTMOST_MASK_U16                  ((uint16)1U)
    #define DIO_IPW_PIN_MASK_U16                            ((uint16)0x000FU)
    #define DIO_IPW_CHECK_CHANNEL_VALIDITY(channelId)       (DIO_IPW_BIT1_LEFTMOST_MASK_U16 << ((channelId) & DIO_IPW_PIN_MASK_U16))
#endif


#define DIO_IPW_PORTID_SHIFT_U8                             ((uint8)0x4U)
#define DIO_IPW_PORTID_EXTRACT(ChannelId)                   ((ChannelId) >> DIO_IPW_PORTID_SHIFT_U8)

#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"


/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
Dio_LevelType Dio_Ipw_ReadChannel(Dio_ChannelType ChannelId);

/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
void Dio_Ipw_WriteChannel(Dio_ChannelType ChannelId,
                          Dio_LevelType Level
                         );

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
Dio_LevelType Dio_Ipw_FlipChannel(Dio_ChannelType ChannelId);

#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
Dio_PortLevelType Dio_Ipw_ReadPort(Dio_PortType PortId);
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
void Dio_Ipw_WritePort(Dio_PortType PortId,
                       Dio_PortLevelType Level
                      );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
Dio_PortLevelType Dio_Ipw_ReadChannelGroup(const Dio_ChannelGroupType * pChannelGroupIdPtr);
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
void Dio_Ipw_WriteChannelGroup(const Dio_ChannelGroupType * pChannelGroupIdPtr,
                               Dio_PortLevelType Level
                              );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
#if (STD_ON == DIO_MASKEDWRITEPORT_API)
/**
* @brief          Mapping macro between low level layer and high level layer.
*
*/
void Dio_Ipw_MaskedWritePort(Dio_PortType PortId,Dio_PortLevelType Level,
                             Dio_PortLevelType Mask
                            );

#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) */
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    #ifdef CPU_TYPE
        #if (CPU_TYPE == CPU_TYPE_64)
        /**
        * @brief size of pointer type. on CPU_TYPE_64, the size is 64bits.
        */
        typedef uint64 pointerSizeType;
        #elif (CPU_TYPE == CPU_TYPE_32)
        /**
        * @brief size of pointer type. on CPU_TYPE_32, the size is 32bits.
        */
        typedef uint32 pointerSizeType;
        #elif (CPU_TYPE == CPU_TYPE_16)
        /**
        * @brief size of pointer type. on CPU_TYPE_16, the size is 16bits.
        */
        typedef uint16 pointerSizeType;
        #endif
    #endif
#endif

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* DIO_IPW_H */

/** @} */
