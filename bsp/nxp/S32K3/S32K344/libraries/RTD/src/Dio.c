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

/**
*   @file    Dio.c
*   @implements        Dio.c_Artifact
*
*   @addtogroup DIO_HLD
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

#include "Dio.h"
#include "Dio_Ipw.h"

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    #include "Det.h"
#endif
/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_VENDOR_ID_C                      43
#define DIO_AR_RELEASE_MAJOR_VERSION_C       4
#define DIO_AR_RELEASE_MINOR_VERSION_C       7
#define DIO_AR_RELEASE_REVISION_VERSION_C    0
#define DIO_SW_MAJOR_VERSION_C               5
#define DIO_SW_MINOR_VERSION_C               0
#define DIO_SW_PATCH_VERSION_C               0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if current file and DET header file are of the same version.*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (STD_ON == DIO_DEV_ERROR_DETECT)
        #if ((DIO_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
             (DIO_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Dio.c and Det.h are different"
        #endif
    #endif
#endif

/* Check if current file and DIO header file are of the same vendor.*/
#if (DIO_VENDOR_ID_C != DIO_VENDOR_ID)
    #error "Dio.c and Dio.h have different vendor ids"
#endif

/* Check if current file and DIO header file are of the same Autosar version.*/
#if ((DIO_AR_RELEASE_MAJOR_VERSION_C    != DIO_AR_RELEASE_MAJOR_VERSION) || \
     (DIO_AR_RELEASE_MINOR_VERSION_C    != DIO_AR_RELEASE_MINOR_VERSION) || \
     (DIO_AR_RELEASE_REVISION_VERSION_C != DIO_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Dio.c and Dio.h are different"
#endif

/* Check if current file and DIO header file are of the same Software version.*/
#if ((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Dio.c and Dio.h are different"
#endif

/* Dio_Ipw.h version check start */
#if ((DIO_AR_RELEASE_MAJOR_VERSION_C != DIO_IPW_AR_RELEASE_MAJOR_VERSION_H)   || \
     (DIO_AR_RELEASE_MINOR_VERSION_C != DIO_IPW_AR_RELEASE_MINOR_VERSION_H)   || \
     (DIO_AR_RELEASE_REVISION_VERSION_C != DIO_IPW_AR_RELEASE_REVISION_VERSION_H)\
    )
    #error "AUTOSAR Version Numbers of Dio.c and Dio_Ipw.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_C != DIO_IPW_SW_MAJOR_VERSION_H) || \
     (DIO_SW_MINOR_VERSION_C != DIO_IPW_SW_MINOR_VERSION_H) || \
     (DIO_SW_PATCH_VERSION_C != DIO_IPW_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Dio.c and Dio_Ipw.h are different"
#endif

#if (DIO_VENDOR_ID_C != DIO_IPW_VENDOR_ID_H)
    #error "VENDOR ID for Dio.c and Dio_Ipw.h is different"
#endif
/* Dio_Ipw.h version check end */

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/

#if (STD_ON == DIO_MULTIPARTITION_ENABLED)
    #define Dio_GetUserId()            OsIf_GetUserId()
#else
    #define Dio_GetUserId()            ((uint32)0UL)
#endif


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/

#if (defined(DIO_PRECOMPILE_SUPPORT) || defined(DIO_LINKTIME_SUPPORT))

#define DIO_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "Dio_MemMap.h"

/* Local Variable for storing the generated Dio configuration */
extern const Dio_ConfigType Dio_ConfigPC;

#define DIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Dio_MemMap.h"

#endif /* (defined(DIO_PRECOMPILE_SUPPORT) || defined(DIO_LINKTIME_SUPPORT)) */

/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/
#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"

#if (STD_ON == DIO_DEV_ERROR_DETECT)
static inline Std_ReturnType Dio_ValidateChannelLevel(Dio_LevelType Level);

static inline Std_ReturnType Dio_ValidateChannelForWrite(Dio_ChannelType ChannelId,
                                                                         uint8 u8ServiceId
                                                        );
static inline Std_ReturnType Dio_ValidateChannelForRead(Dio_ChannelType ChannelId,
                                                                        uint8 u8ServiceId
                                                       );

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
static inline Std_ReturnType Dio_ValidatePortForRead(Dio_PortType PortId,
                                                                     uint8 u8ServiceId
                                                    );

static inline Std_ReturnType Dio_ValidatePortForWrite(Dio_PortType PortId,
                                                                      uint8 u8ServiceId
                                                     );

static inline Std_ReturnType Dio_ValidateChannelGroupForWrite(const Dio_ChannelGroupType * pChannelGroup,
                                                                              uint8 u8ServiceId
                                                             );

static inline Std_ReturnType Dio_ValidateChannelGroupForRead(const Dio_ChannelGroupType * pChannelGroup,
                                                                             uint8 u8ServiceId
                                                            );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /*DIO_VIRTWRAPPER_SUPPORT*/
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/

#if (STD_ON == DIO_DEV_ERROR_DETECT)
/**
 * @brief       DIO channel level validation.
 * @details     Checks if the specified channel level is valid (either STD_HIGH or STD_LOW).
 *
 * @param[in]   Level   channel level parameter to be checked
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidateChannelLevel_Activity
 */
static inline Std_ReturnType Dio_ValidateChannelLevel(Dio_LevelType Level)
{
    Std_ReturnType Valid = (Std_ReturnType)E_NOT_OK;

    if (((Dio_LevelType)STD_HIGH == Level) || ((Dio_LevelType)STD_LOW == Level))
    {
        Valid = (Std_ReturnType)E_OK;
    }
    else
    {
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITECHANNEL_ID, DIO_E_PARAM_LEVEL);
    }

    return Valid;
}
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
/**
 * @brief       DIO channel availability check.
 * @details     Checks if the specified channel is implemented in the current platform package.
 *
 * @param[in]   ChannelId   Identifier of the channel to be checked.
 *              u8ServiceId The service id of the caller function
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidateChannelForWrite_Activity
 */
static inline Std_ReturnType Dio_ValidateChannelForWrite(Dio_ChannelType ChannelId,
                                                                         uint8 u8ServiceId
                                                        )
{
    Std_ReturnType Valid = (Std_ReturnType)E_NOT_OK;
    uint8 PartitionId = (uint8)Dio_GetUserId();
    Dio_ChannelType maxChannelId = (Dio_ChannelType)DIO_NUM_CHANNELS_U16;
    uint32 u32ChannelToPartitionMap;

#ifdef SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE
    if (SIUL2_DIO_IP_MAX_MSCR_REGISTERS <= ChannelId)
    {
        maxChannelId = (Dio_ChannelType)(SIUL2_DIO_IP_MAX_MSCR_REGISTERS + SIUL2_DIO_IP_MAX_SIUL2_AE_CHANNELS);
    }
#endif /* SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE */
    if ((((Dio_ChannelType)(ChannelId) <= (Dio_ChannelType)maxChannelId)) &&
        ((Dio_PortLevelType)0 != (Dio_aAvailablePinsForWrite[(DIO_IPW_PORTID_EXTRACT(ChannelId))] &
                                                    (DIO_IPW_CHECK_CHANNEL_VALIDITY((uint16)ChannelId))
                                 )
        )
       )
    {
#ifdef SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE
        if (SIUL2_DIO_IP_MAX_MSCR_REGISTERS <= ChannelId)
        {
            u32ChannelToPartitionMap = Dio_ConfigPC.pau32Dio_ChannelAEToPartitionMap[(ChannelId) - SIUL2_DIO_IP_MAX_MSCR_REGISTERS];
        }
        else
        {
            u32ChannelToPartitionMap = Dio_ConfigPC.pau32Dio_ChannelToPartitionMap[ChannelId];
        }
#else
        u32ChannelToPartitionMap = Dio_ConfigPC.pau32Dio_ChannelToPartitionMap[ChannelId];
#endif /* SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE */
        if ((uint32)1 == ((u32ChannelToPartitionMap & ((uint32)1 << PartitionId)) >> PartitionId))
        {
            Valid = (Std_ReturnType)E_OK;
        }
        else
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_CONFIG);
        }
    }
    else
    {
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }

    return Valid;
}
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
/**
 * @brief       DIO channel availability check.
 * @details     Checks if the specified channel is implemented in the current platform package.
 *
 * @param[in]   ChannelId   Identifier of the channel to be checked.
 *              u8ServiceId The service id of the caller function
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidateChannelForRead_Activity
 */
static inline Std_ReturnType Dio_ValidateChannelForRead(Dio_ChannelType ChannelId,
                                                                        uint8 u8ServiceId
                                                       )
{
    Std_ReturnType Valid  = (Std_ReturnType)E_NOT_OK;
    uint8 PartitionId = (uint8)Dio_GetUserId();
    Dio_ChannelType maxChannelId = (Dio_ChannelType)DIO_NUM_CHANNELS_U16;
    uint32 u32ChannelToPartitionMap;

#ifdef SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE
    if (SIUL2_DIO_IP_MAX_MSCR_REGISTERS <= ChannelId)
    {
        maxChannelId = (Dio_ChannelType)(SIUL2_DIO_IP_MAX_MSCR_REGISTERS + SIUL2_DIO_IP_MAX_SIUL2_AE_CHANNELS);
    }
#endif /* SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE */

    /* Check if that channel ID is available for read */
    if ((((Dio_ChannelType)(ChannelId) <= (Dio_ChannelType)maxChannelId)) &&
        ((Dio_PortLevelType)0 != (Dio_aAvailablePinsForRead[(DIO_IPW_PORTID_EXTRACT(ChannelId))] &
                                  (DIO_IPW_CHECK_CHANNEL_VALIDITY((uint16)ChannelId))
                                 )
        )
       )
    {
#ifdef SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE
        if (SIUL2_DIO_IP_MAX_MSCR_REGISTERS <= ChannelId)
        {
            u32ChannelToPartitionMap = Dio_ConfigPC.pau32Dio_ChannelAEToPartitionMap[(ChannelId) - SIUL2_DIO_IP_MAX_MSCR_REGISTERS];
        }
        else
        {
            u32ChannelToPartitionMap = Dio_ConfigPC.pau32Dio_ChannelToPartitionMap[ChannelId];
        }
#else
        u32ChannelToPartitionMap = Dio_ConfigPC.pau32Dio_ChannelToPartitionMap[ChannelId];
#endif /* SIUL2_DIO_IP_HAS_SIUL2_AE_INSTANCE */
        /* Check if port was assigned to the current PartitionId */
        if ((uint32)1 == ((u32ChannelToPartitionMap & ((uint32)1 << PartitionId)) >> PartitionId))
        {
            Valid = (Std_ReturnType)E_OK;
        }
        else
        {
            /* Raise Det error when invalid serviceID */
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_CONFIG);
        }
    }
    else
    {
        /* Raise Det error when invalid channel ID */
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }

    return Valid;
}
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * @brief       DIO port availability check.
 * @details     Checks if the specified port is implemented in the current platform package.
 *
 * @param[in]   PortId      Identifier of the port to be checked.
 *              u8ServiceId The service id of the caller function
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidatePortForWrite_Activity
 */
static inline Std_ReturnType Dio_ValidatePortForWrite(Dio_PortType PortId,
                                                                      uint8 u8ServiceId
                                                     )
{
    Std_ReturnType Valid  = (Std_ReturnType)E_NOT_OK;
    uint8 PartitionId = (uint8)Dio_GetUserId();

    if (((uint8)(PortId) < DIO_NUM_PORTS_U16) &&
        (Dio_aAvailablePinsForWrite[(uint8)(PortId)] != DIO_NO_AVAILABLE_CHANNELS_U16)
       )
    {
        if ((uint32)1 == ((Dio_ConfigPC.pau32Dio_PortToPartitionMap[PortId] & ((uint32)1 << PartitionId)) >> PartitionId))
        {
            Valid = (Std_ReturnType)E_OK;
        }
        else
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_CONFIG);
        }
    }
    else
    {
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_INVALID_PORT_ID);
    }

    return Valid;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * @brief       DIO port availability check.
 * @details     Checks if the specified port is implemented in the current platform package.
 *
 * @param[in]   PortId      Identifier of the port to be checked.
 *              u8ServiceId The service id of the caller function
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidatePortForRead_Activity
 */
static inline Std_ReturnType Dio_ValidatePortForRead(Dio_PortType PortId,
                                                                     uint8 u8ServiceId
                                                    )
{
    Std_ReturnType Valid  = (Std_ReturnType)E_NOT_OK;
    uint8 PartitionId = (uint8)Dio_GetUserId();

    /* Check input parameters are available for read */
    if (((uint8)(PortId) < DIO_NUM_PORTS_U16) &&
        (Dio_aAvailablePinsForRead[(uint8)(PortId)] != DIO_NO_AVAILABLE_CHANNELS_U16)
       )
    {
        /* Check if Port was assigned to the current PartitionId */
        if ((uint32)1 == ((Dio_ConfigPC.pau32Dio_PortToPartitionMap[PortId] & ((uint32)1 << PartitionId)) >> PartitionId))
        {
            Valid = (Std_ReturnType)E_OK;
        }
        else
        {
            /* Raise Det error when invalid serviceID */
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_CONFIG);
        }
    }
    else
    {
        /* Raise Det error when invalid port ID */
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_INVALID_PORT_ID);
    }

    return Valid;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * @brief       DIO channel group validity check.
 * @details     Checks if the parameter matches one of the channel group pointers in
 *              the configuration.
 *
 * @param[in]   pChannelGroup  The channel group to be validated.
 *              u8ServiceId    The service id of the caller function
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidateChannelGroupForWrite_Activity
 */
static inline Std_ReturnType Dio_ValidateChannelGroupForWrite(const Dio_ChannelGroupType * pChannelGroup,
                                                                              uint8 u8ServiceId
                                                             )
{
    Std_ReturnType Valid = (Std_ReturnType)E_NOT_OK;
    uint8 u8ChannelGroup = pChannelGroup->port;

    /* Compiler_Warning: Pointer to channel group is converted to unsigned long in order for it to
                          be compared with the boundaries of the channel group list. */
    if ((((pointerSizeType)(pChannelGroup)) >= ((pointerSizeType)Dio_ConfigPC.pChannelGroupList))                                  &&  \
        (((pointerSizeType)(pChannelGroup)) <= (pointerSizeType)(&Dio_ConfigPC.pChannelGroupList[Dio_ConfigPC.u8NumChannelGroups - 1U])) &&  \
        (u8ChannelGroup < DIO_NUM_PORTS_U16)                                                       &&  \
        (Dio_aAvailablePinsForWrite[u8ChannelGroup] != DIO_NO_AVAILABLE_CHANNELS_U16)              &&  \
        ((uint8)(pChannelGroup->u8offset) <= DIO_MAX_VALID_OFFSET_U8)
       )
    {
        Valid = (Std_ReturnType)E_OK;
    }
    else
    {
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_INVALID_GROUP_ID);
    }

    return Valid;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
 * @brief       DIO channel group validity check.
 * @details     Checks if the parameter matches one of the channel group pointers in
 *              the configuration.
 *
 * @param[in]   pChannelGroup  The channel group to be validated.
 *              u8ServiceId    The service id of the caller function
 *
 * @return      Std_ReturnType
 *
 * @api
 *
 * @implements  Dio_ValidateChannelGroupForRead_Activity
 */
static inline Std_ReturnType Dio_ValidateChannelGroupForRead(const Dio_ChannelGroupType * pChannelGroup,
                                                                             uint8 u8ServiceId
                                                            )
{
    Std_ReturnType Valid = (Std_ReturnType)E_NOT_OK;
    uint8 u8ChannelGroup = pChannelGroup->port;

    /* Compiler_Warning: Pointer to channel group is converted to unsigned long in order for it to
                          be compared with the boundaries of the channel group list. */
    if ((((pointerSizeType)(pChannelGroup)) >= ((pointerSizeType)Dio_ConfigPC.pChannelGroupList))                                  &&  \
        (((pointerSizeType)(pChannelGroup)) <= (pointerSizeType)(&Dio_ConfigPC.pChannelGroupList[Dio_ConfigPC.u8NumChannelGroups - 1U])) &&  \
        (u8ChannelGroup < DIO_NUM_PORTS_U16)                                                       &&  \
        (Dio_aAvailablePinsForRead[u8ChannelGroup] != DIO_NO_AVAILABLE_CHANNELS_U16)               &&  \
        ((uint8)(pChannelGroup->u8offset) <= DIO_MAX_VALID_OFFSET_U8)
       )
    {
        Valid = (Std_ReturnType)E_OK;
    }
    else
    {
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, u8ServiceId, DIO_E_PARAM_INVALID_GROUP_ID);
    }

    return Valid;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

/*================================================================================================*/


#if (STD_ON == DIO_VERSION_INFO_API)
/*================================================================================================*/
/**
* @brief          Service to get the version information of this module.
* @details        The @p Dio_GetVersionInfo() function shall return the version
*                 information of this module. The version information includes:
*                 - Module Id.
*                 - Vendor Id.
*                 - Vendor specific version numbers.
*                 .
*
* @param[in,out]  VersionInfo Pointer to where to store the version
*                             information of this module.
*
* @pre            This function can be used only if @p DIO_VERSION_INFO_API
*                 has been enabled.
*
* @implements     Dio_GetVersionInfo_Activity
*/
void Dio_GetVersionInfo(Std_VersionInfoType * VersionInfo)
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfo)
    {
        (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GETVERSIONINFO_ID, DIO_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */
    {
        VersionInfo->vendorID         = (uint16)DIO_VENDOR_ID;
        VersionInfo->moduleID         = (uint16)DIO_MODULE_ID;
        VersionInfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON == DIO_DEV_ERROR_DETECT) */

/*================================================================================================*/
/**
* @brief          Returns the value of the specified DIO channel.
* @details        This function returns the value of the specified DIO channel.
*
* @param[in]      ChannelId   Specifies the required channel id.
*
* @return                     Returns the level of the corresponding pin as
*                             @p STD_HIGH or @p STD_LOW.
* @retval STD_HIGH            The logical level of the corresponding pin is 1.
* @retval STD_LOW             The logical level of the corresponding Pin is 0.
*
* @implements     Dio_ReadChannel_Activity
*/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType ChannelLevel = (Dio_LevelType)STD_LOW;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    Std_ReturnType Valid = Dio_ValidateChannelForRead(ChannelId, DIO_READCHANNEL_ID);

    if ((Std_ReturnType)E_OK == Valid)
    {
#endif
        ChannelLevel = Dio_Ipw_ReadChannel(ChannelId);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    }
#endif

    return ChannelLevel;
}

/*================================================================================================*/
/**
* @brief          Sets the level of a channel.
* @details        If the specified channel is configured as an output channel,
*                 this function shall set the specified level on the
*                 specified channel. If the specified channel is configured
*                 as an input channel, this function shall have no influence
*                 on the physical output and on the result of the next read
*                 service.
*
* @param[in]      ChannelId   Specifies the required channel id.
* @param[in]      Level       Specifies the channel desired level.
*
* @implements     Dio_WriteChannel_Activity
*/
void Dio_WriteChannel(Dio_ChannelType ChannelId,
                                      Dio_LevelType Level
                     )
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    Std_ReturnType Valid = Dio_ValidateChannelForWrite(ChannelId, DIO_WRITECHANNEL_ID);

    if ((Std_ReturnType) E_OK == Valid)
    {
        Valid = Dio_ValidateChannelLevel(Level);
        if ((Std_ReturnType) E_OK == Valid)
        {
#endif
            Dio_Ipw_WriteChannel(ChannelId, Level);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
        }
    }
#endif

}

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/*================================================================================================*/
/**
* @brief          Inverts the level of a channel.
* @details        If the specified channel is configured as an output channel,
*                 this function shall invert the level of the specified
*                 channel. If the specified channel is configured as an
*                 input channel, this function shall have no influence
*                 on the physical output and on the result of the next
*                 read service.
*
* @param[in]      ChannelId   Specifies the required channel id.
*
* @return                     Returns the level of the corresponding pin as
*                             @p STD_HIGH or @p STD_LOW.
* @retval STD_HIGH            The logical level of the corresponding pin is 1.
* @retval STD_LOW             The logical level of the corresponding Pin is 0.
*
* @pre            This function can be used only if @p DIO_FLIP_CHANNEL_API
*                 has been enabled.
*
* @implements     Dio_FlipChannel_Activity
*/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType ChannelLevel = (Dio_LevelType)STD_LOW;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    Std_ReturnType Valid = Dio_ValidateChannelForWrite(ChannelId, DIO_FLIPCHANNEL_ID);

    if ((Std_ReturnType)E_OK == Valid)
    {
#endif
        ChannelLevel = Dio_Ipw_FlipChannel(ChannelId);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    }
#endif

   return ChannelLevel;
}
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*================================================================================================*/
/**
* @brief        Returns the level of all channels of specified port.
* @details      This function will return the level of all channels
*               belonging to the specified port.
*
* @param[in]    PortId      Specifies the required port id.
*
* @return       Levels of all channels of specified port.
*
* @implements   Dio_ReadPort_Activity
*/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    Dio_PortLevelType PortLevel = (Dio_PortLevelType)STD_LOW;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    Std_ReturnType Valid = Dio_ValidatePortForRead(PortId, DIO_READPORT_ID);

    if ((Std_ReturnType) E_OK == Valid)
    {
#endif
        PortLevel = Dio_Ipw_ReadPort(PortId);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    }
#endif

    return PortLevel;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*================================================================================================*/
/**
* @brief          Sets the value of a port.
* @details        This function will set the specified value on the specified
*                 port.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
*
* @implements     Dio_WritePort_Activity
*/
void Dio_WritePort(Dio_PortType PortId,
                                   Dio_PortLevelType Level
                  )
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    Std_ReturnType Valid = Dio_ValidatePortForWrite(PortId, DIO_WRITEPORT_ID);

    if ((Std_ReturnType)E_OK == Valid)
    {
#endif
        Dio_Ipw_WritePort(PortId, Level);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    }
#endif
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*================================================================================================*/
/**
* @brief          This service reads a subset of the adjoining bits of a port.
* @details        This function will read a subset of adjoining bits of a
*                 port (channel group).
*
* @param[in]      ChannelGroupIdPtr Pointer to the channel group.
*
* @return         The channel group levels.
*
* @implements     Dio_ReadChannelGroup_Activity
*/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType * ChannelGroupIdPtr)
{
    Dio_PortLevelType PortLevel = (Dio_PortLevelType)STD_LOW;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    uint8 GroupAlocated = 0;
    uint8 GroupIndex    = 0;
    uint8 PartitionId;
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
    Std_ReturnType Valid;

#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    PartitionId = (uint8)Dio_GetUserId();
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
    Valid = Dio_ValidateChannelGroupForRead(ChannelGroupIdPtr, DIO_READCHANNELGROUP_ID);

    if ((Std_ReturnType)E_OK == Valid)
    {
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
        for (GroupIndex = 0; GroupIndex < Dio_ConfigPC.u8NumChannelGroups; GroupIndex++)
        {
            if (Dio_pxChannelGroupsListForEachPartition[PartitionId][GroupIndex] == ChannelGroupIdPtr)
            {
                GroupAlocated = 1;
            }
        }
        if ((uint8)1 == GroupAlocated)
        {
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
#endif /* DIO_DEV_ERROR_DETECT */
            PortLevel = Dio_Ipw_ReadChannelGroup(ChannelGroupIdPtr);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
        }
        else
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READCHANNELGROUP_ID, DIO_E_PARAM_CONFIG);
        }
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
    }
#endif /* DIO_DEV_ERROR_DETECT */

    return PortLevel;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*================================================================================================*/
/**
* @brief          Sets a subset of the adjoining bits of a port to the
*                 specified levels.
* @details        This function will set a subset of adjoining bits of a port
*                 (channel group) to the specified levels without changing
*                 the remaining channels of the port and channels that
*                 are configured as input.
*                 This function will do the masking of the channels and will
*                 do the shifting so that the values written by the function
*                 are aligned to the LSB.
*
* @param[in]      ChannelGroupIdPtr Pointer to the channel group.
* @param[in]      Level       Desired levels for the channel group.
*
* @implements     Dio_WriteChannelGroup_Activity
*/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType * ChannelGroupIdPtr,
                                           Dio_PortLevelType Level
                          )
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    uint8 GroupAlocated = 0;
    uint8 GroupIndex    = 0;
    uint8 PartitionId;
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
    Std_ReturnType Valid;

#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
    PartitionId = (uint8)Dio_GetUserId();
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */

    Valid = Dio_ValidateChannelGroupForWrite(ChannelGroupIdPtr, DIO_WRITECHANNELGROUP_ID);

    if ((Std_ReturnType)E_OK == Valid)
    {
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
        for (GroupIndex = 0; GroupIndex < Dio_ConfigPC.u8NumChannelGroups; GroupIndex++)
        {
            if (Dio_pxChannelGroupsListForEachPartition[PartitionId][GroupIndex] == ChannelGroupIdPtr)
            {
                GroupAlocated = 1;
            }
        }
        if ((uint8)1 == GroupAlocated)
        {
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
#endif /* DIO_DEV_ERROR_DETECT */
            Dio_Ipw_WriteChannelGroup(ChannelGroupIdPtr, Level);
#if (STD_ON == DIO_DEV_ERROR_DETECT)
#ifdef DIO_CHANNEL_GROUPS_AVAILABLE
        }
        else
        {
            (void)Det_ReportError((uint16)DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_CONFIG);
        }
#endif /* DIO_CHANNEL_GROUPS_AVAILABLE */
    }
#endif /* DIO_DEV_ERROR_DETECT */
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
#if ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__))
/*================================================================================================*/
/**
* @brief          DIO Mask write port using mask.
* @details        Writes a DIO port with masked value.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
* @param[in]      Mask        Specifies the Mask value of the port.
*
* @pre            This function can be used only if @p DIO_MASKEDWRITEPORT_API
*                 has been enabled.
*
* @implements     Dio_MaskedWritePort_Activity
*/
void Dio_MaskedWritePort(Dio_PortType PortId,
                                         Dio_PortLevelType Level,
                                         Dio_PortLevelType Mask
                        )
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    Std_ReturnType Valid = Dio_ValidatePortForWrite(PortId, DIO_MASKEDWRITEPORT_ID);

    if ((Std_ReturnType)E_OK == Valid)
    {
#endif
        Dio_Ipw_MaskedWritePort(PortId, Level, Mask);

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    }
#endif
}
#endif /* ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__)) */
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#define DIO_STOP_SEC_CODE

#include "Dio_MemMap.h"

#ifdef __cplusplus
}
#endif


/** @} */
