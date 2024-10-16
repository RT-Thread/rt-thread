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

#ifndef DIO_H
#define DIO_H

/**
*   @file Dio.h
*   @implements Dio.h_Artifact
*
*   @defgroup DIO_HLD Dio HLD
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
#include "Std_Types.h"
#include "Mcal.h"
#include "Dio_Cfg.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_VENDOR_ID                    43
#define DIO_MODULE_ID                    120
#define DIO_AR_RELEASE_MAJOR_VERSION     4
#define DIO_AR_RELEASE_MINOR_VERSION     7
#define DIO_AR_RELEASE_REVISION_VERSION  0
#define DIO_SW_MAJOR_VERSION             5
#define DIO_SW_MINOR_VERSION             0
#define DIO_SW_PATCH_VERSION             0


/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Std_Types.h file are of the same Autosar version */
    #if ((DIO_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (DIO_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Dio.h and Std_Types.h are different"
    #endif
    /* Check if source file and Mcal.h header file are of the same Autosar version */
    #if ((DIO_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (DIO_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Dio.h and Mcal.h are different"
    #endif
#endif

/* Check if Dio header file and Dio configuration header file are of the same vendor */
#if (DIO_VENDOR_ID != DIO_VENDOR_ID_CFG_H)
    #error "Dio.h and Dio_Cfg.h have different vendor ids"
#endif

/* Check if Dio header file and Dio configuration header file are of the same Autosar version */
#if ((DIO_AR_RELEASE_MAJOR_VERSION    != DIO_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (DIO_AR_RELEASE_MINOR_VERSION    != DIO_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (DIO_AR_RELEASE_REVISION_VERSION != DIO_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Dio.h and Dio_Cfg.h are different"
#endif

/* Check if Dio source file and Dio configuration header file are of the same Software version */
#if ((DIO_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION_CFG_H) || \
     (DIO_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION_CFG_H) || \
     (DIO_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Dio.h and Dio_Cfg.h are different"
#endif
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/
/**
* @brief          The DIO module is not properly configured
*/
#define DIO_E_PARAM_CONFIG                      ((uint8)0xF0U)

/**
* @brief          Invalid channel name requested.
*
* @implements     Dio_ErrorCodes_define
*/
#define DIO_E_PARAM_INVALID_CHANNEL_ID          ((uint8)0x0AU)

/**
* @brief          Invalid port name requested.
*
* @implements     Dio_ErrorCodes_define
*/
#define DIO_E_PARAM_INVALID_PORT_ID             ((uint8)0x14U)

/**
* @brief          Invalid ChannelGroup id passed.
*
* @implements     Dio_ErrorCodes_define
*/
#define DIO_E_PARAM_INVALID_GROUP_ID            ((uint8)0x1FU)

/**
* @brief          API service called with a NULL pointer.
* @details        In case of this error, the API service shall return
*                 immediately without any further action, beside reporting
*                 this development error.
*
* @implements     Dio_ErrorCodes_define
*/
#define DIO_E_PARAM_POINTER                     ((uint8)0x20U)

/**
* @brief          API service called with invalid channel level value.
* @details        In case of this error, the API service shall return
*                 immediately without any further action, beside reporting
*                 this development error.
*
* @implements     Dio_ErrorCodes_define
*/
#define DIO_E_PARAM_LEVEL                       ((uint8)0x21U)


/**
* @brief          API service ID for @p Dio_ReadChannel() function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_READCHANNEL_ID                      ((uint8)0x00U)

/**
* @brief          API service ID for @p Dio_WriteChannel() function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_WRITECHANNEL_ID                     ((uint8)0x01U)

/**
* @brief          API service ID for @p Dio_FlipChannel() function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_FLIPCHANNEL_ID                      ((uint8)0x11U)

/**
* @brief          API service ID for @p Dio_ReadPort() function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_READPORT_ID                         ((uint8)0x02U)

/**
* @brief          API service ID for @p Dio_WritePort() function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_WRITEPORT_ID                        ((uint8)0x03U)

/**
* @brief          API service ID for @p Dio_ReadChannel() Group function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_READCHANNELGROUP_ID                 ((uint8)0x04U)

/**
* @brief          API service ID for @p Dio_WriteChannel() Group function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_WRITECHANNELGROUP_ID                ((uint8)0x05U)

/**
* @brief          API service ID for DIO Get Version() Info function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_GETVERSIONINFO_ID                   ((uint8)0x12U)

/**
* @brief          API service ID for @p Dio_MaskedWritePort() function.
* @details        Parameters used when raising an error/exception.
*/
#define DIO_MASKEDWRITEPORT_ID                  ((uint8)0x13U)

/**
* @brief          Instance ID of the Dio driver.
*
* @implements     .
*/
#define DIO_INSTANCE_ID                         ((uint8)0x00U)


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/

/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"

#if (STD_ON == DIO_VERSION_INFO_API)
/*!
 * @brief Service to get the version information of this module.
 *
 * The @p Dio_GetVersionInfo() function shall return the version
 * information of this module. The version information includes:
 * - Module Id.
 * - Vendor Id.
 * - Vendor specific version numbers.
 *
 * @param[in]  VersionInfo Pointer to where to store the version
 *             information of this module.
 */
void Dio_GetVersionInfo(Std_VersionInfoType * VersionInfo);
#endif /* (STD_ON == DIO_VERSION_INFO_API) */

/*!
 * @brief Returns the value of the specified DIO channel.
 *
 * This function returns the value of the specified DIO channel.
 *
 * @param[in] ChannelId Specifies the required channel id.
 *
 * @return Returns the level of the corresponding pin @p STD_HIGH or @p STD_LOW.
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/*!
 * @brief Sets the level of a channel.
 *
 * If the specified channel is configured as an output channel,
 * this function shall set the specified level on the
 * specified channel. If the specified channel is configured
 * as an input channel, this function shall have no influence
 * on the physical output and on the result of the next read
 * service.
 *
 * @param[in] ChannelId Specifies the required channel id.
 * @param[in] Level Specifies the channel desired level.
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId,
                                      Dio_LevelType Level
                     );

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/*!
 * @brief Inverts the level of a channel.
 *
 * If the specified channel is configured as an output channel,
 * this function shall invert the level of the specified
 * channel. If the specified channel is configured as an
 * input channel, this function shall have no influence
 * on the physical output and on the result of the next
 * read service.
 *
 * @param[in]      ChannelId   Specifies the required channel id.
 *
 * @return Returns the level of the corresponding pin as @p STD_HIGH or @p STD_LOW.
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*!
 * @brief Returns the level of all channels of specified port.
 *
 * This function will return the level of all channels
 * belonging to the specified port.
 *
 * @param[in] PortId Specifies the required port id.
 *
 * @return Levels of all channels of specified port.
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*!
 * @brief Sets the value of a port.
 *
 * This function will set the specified value on the specified port.
 *
 * @param[in] PortId Specifies the required port id.
 * @param[in] Level Specifies the required levels for the port pins.
 */
void Dio_WritePort(Dio_PortType PortId,
                                   Dio_PortLevelType Level
                  );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /*DIO_VIRTWRAPPER_SUPPORT*/

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*!
 * @brief This service reads a subset of the adjoining bits of a port.
 *
 * This function will read a subset of adjoining bits of a port (channel group).
 *
 * @param[in] ChannelGroupIdPtr Pointer to the channel group.
 *
 * @return         The channel group levels.
 */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType * ChannelGroupIdPtr);
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /*DIO_VIRTWRAPPER_SUPPORT*/

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*!
 * @brief Sets a subset of the adjoining bits of a port to the specified levels.
 *
 * This function will set a subset of adjoining bits of a port
 * (channel group) to the specified levels without changing
 * the remaining channels of the port and channels that are configured as input.
 * This function will do the masking of the channels and will
 * do the shifting so that the values written by the function
 * are aligned to the LSB.
 *
 * @param[in] ChannelGroupIdPtr Pointer to the channel group.
 * @param[in] Level Desired levels for the channel group.
 */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType * ChannelGroupIdPtr,
                                           Dio_PortLevelType Level
                          );
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /*DIO_VIRTWRAPPER_SUPPORT*/

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
#if ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__))
/*!
 * @brief DIO Mask write port using mask.
 *
 * Writes a DIO port with masked value.
 *
 * @param[in] PortId Specifies the required port id.
 * @param[in] Level Specifies the required levels for the port pins.
 * @param[in] Mask Specifies the Mask value of the port.
 *
 * @pre This function can be used only if @p DIO_MASKEDWRITEPORT_API has been enabled.
 */
void Dio_MaskedWritePort(Dio_PortType PortId,
                                         Dio_PortLevelType Level,
                                         Dio_PortLevelType Mask
                        );
#endif /* ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__)) */
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /*DIO_VIRTWRAPPER_SUPPORT*/

#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* DIO_H */
