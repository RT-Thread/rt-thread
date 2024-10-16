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

#ifdef __cplusplus
extern "C" {
#endif

/**
*   @file Dio_Ipw.c
*   @internal
*   @addtogroup DIO_IPW
*   @{
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Dio_Cfg.h"
#include "Dio_Ipw.h"
#ifdef DIO_ENABLE_USER_MODE_SUPPORT
    #define USER_MODE_REG_PROT_ENABLED (DIO_USER_MODE_SOFT_LOCKING)
#endif
#include "SchM_Dio.h"
#include "Siul2_Dio_Ip_Cfg.h"
#ifdef MCAL_ENABLE_FAULT_INJECTION
#include "Mcal.h"
#endif
/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define DIO_IPW_VENDOR_ID_C                    43
#define DIO_IPW_AR_RELEASE_MAJOR_VERSION_C     4
#define DIO_IPW_AR_RELEASE_MINOR_VERSION_C     7
#define DIO_IPW_AR_RELEASE_REVISION_VERSION_C  0
#define DIO_IPW_SW_MAJOR_VERSION_C             5
#define DIO_IPW_SW_MINOR_VERSION_C             0
#define DIO_IPW_SW_PATCH_VERSION_C             0
/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if Dio_Ipw source file and Dio_Ipw header file are of the same vendor */
#if (DIO_IPW_VENDOR_ID_C != DIO_IPW_VENDOR_ID_H)
    #error "Dio_Ipw.c and Dio_Ipw.h have different vendor ids"
#endif

/* Check if  Dio_Ipw source file and Dio_Ipw header file are of the same Autosar version */
#if ((DIO_IPW_AR_RELEASE_MAJOR_VERSION_C    != DIO_IPW_AR_RELEASE_MAJOR_VERSION_H) || \
     (DIO_IPW_AR_RELEASE_MINOR_VERSION_C    != DIO_IPW_AR_RELEASE_MINOR_VERSION_H) || \
     (DIO_IPW_AR_RELEASE_REVISION_VERSION_C != DIO_IPW_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Dio_Ipw.c and Dio_Ipw.h are different"
#endif

/* Check if Dio_Ipw source file and Dio_Ipw header file are of the same Software version */
#if ((DIO_IPW_SW_MAJOR_VERSION_C != DIO_IPW_SW_MAJOR_VERSION_H) || \
     (DIO_IPW_SW_MINOR_VERSION_C != DIO_IPW_SW_MINOR_VERSION_H) || \
     (DIO_IPW_SW_PATCH_VERSION_C != DIO_IPW_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Dio_Ipw.c and Dio_Ipw.h are different"
#endif

/* Check if Dio_Ipw source file and Dio_Cfg header file are of the same vendor */
#if (DIO_IPW_VENDOR_ID_C != DIO_VENDOR_ID_CFG_H)
    #error "Dio_Ipw.c and Dio_Cfg.h have different vendor ids"
#endif

/* Check if  Dio_Ipw source file and Dio_Cfg header file are of the same Autosar version */
#if ((DIO_IPW_AR_RELEASE_MAJOR_VERSION_C    != DIO_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (DIO_IPW_AR_RELEASE_MINOR_VERSION_C    != DIO_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (DIO_IPW_AR_RELEASE_REVISION_VERSION_C != DIO_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Dio_Ipw.c and Dio_Cfg.h are different"
#endif

/* Check if Dio_Ipw source file and Dio_Cfg header file are of the same Software version */
#if ((DIO_IPW_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION_CFG_H) || \
     (DIO_IPW_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION_CFG_H) || \
     (DIO_IPW_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Dio_Ipw.c and Dio_Cfg.h are different"
#endif

/* Check if Dio_Ipw source file and Siul2_Dio_Ip_Cfg header file are of the same vendor */
#if (DIO_IPW_VENDOR_ID_C != SIUL2_DIO_IP_VENDOR_ID_CFG_H)
    #error "Dio_Ipw.c and Siul2_Dio_Ip_Cfg.h have different vendor ids"
#endif

/* Check if  Dio_Ipw source file and Siul2_Dio_Ip_Cfg header file are of the same Autosar version */
#if ((DIO_IPW_AR_RELEASE_MAJOR_VERSION_C    != SIUL2_DIO_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (DIO_IPW_AR_RELEASE_MINOR_VERSION_C    != SIUL2_DIO_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (DIO_IPW_AR_RELEASE_REVISION_VERSION_C != SIUL2_DIO_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Dio_Ipw.c and Siul2_Dio_Ip_Cfg.h are different"
#endif

/* Check if Dio_Ipw source file and Siul2_Dio_Ip_Cfg header file are of the same Software version */
#if ((DIO_IPW_SW_MAJOR_VERSION_C != SIUL2_DIO_IP_SW_MAJOR_VERSION_CFG_H) || \
     (DIO_IPW_SW_MINOR_VERSION_C != SIUL2_DIO_IP_SW_MINOR_VERSION_CFG_H) || \
     (DIO_IPW_SW_PATCH_VERSION_C != SIUL2_DIO_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Dio_Ipw.c and Siul2_Dio_Ip_Cfg.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* SchM_Dio.h version check start */
    #if ((DIO_IPW_AR_RELEASE_MAJOR_VERSION_C != SCHM_DIO_AR_RELEASE_MAJOR_VERSION) ||   \
        (DIO_IPW_AR_RELEASE_MINOR_VERSION_C != SCHM_DIO_AR_RELEASE_MINOR_VERSION)       \
        )
        #error "AUTOSAR Version Numbers of Dio_Ipw.c and SchM_Dio.h are different"
    #endif
    /* SchM_Dio.h version check end */

    #ifdef MCAL_ENABLE_FAULT_INJECTION
        #if ((DIO_IPW_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
            (DIO_IPW_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Dio_Ipw.c and Mcal.h are different"
        #endif
    #endif
#endif
/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/
#define DIO_IPW_SIUL2_REVERSE_BITS_SHIFT            ((Dio_PortLevelType)1U)
#define DIO_IPW_SIUL2_REVERSE_BITS_MASK             ((Dio_PortLevelType)0x1U)
#define DIO_IPW_SIUL2_REVERSE_BITS_NUMBER           ((Dio_PortLevelType)((Dio_PortLevelType)((Dio_PortLevelType)(sizeof(Dio_PortLevelType)) << 0x3U) - 1U))

/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


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

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
static Dio_PortLevelType Dio_Ipw_ReverseBits(Dio_PortLevelType Level);
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

static Dio_LevelType Dio_Ipw_ReadChannelValue(uint8 u8Siul2Instance,
                                              Dio_ChannelType Channel
                                             );

/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/**
* @brief          Reverses bits.
*
* @param[in]      Level       Bits to be reversed.
*
* @return         The reversed bits.
*
* @pre            This function can be used only if @p DIO_REVERSEPORTBITS is
*                 enabled.
*/
static Dio_PortLevelType Dio_Ipw_ReverseBits(Dio_PortLevelType Level)
{
    /* RevLevel will be reversed bits of Level */
    Dio_PortLevelType TempLevel = Level;
    Dio_PortLevelType RevLevel = TempLevel;
    Dio_PortLevelType NumShifts = DIO_IPW_SIUL2_REVERSE_BITS_NUMBER; /* number of shifts needed due to trailing 0s */

    for (TempLevel = (Dio_PortLevelType)(TempLevel >> DIO_IPW_SIUL2_REVERSE_BITS_SHIFT); (Dio_PortLevelType)STD_LOW != TempLevel; TempLevel = (Dio_PortLevelType)(TempLevel >> DIO_IPW_SIUL2_REVERSE_BITS_SHIFT))
    {
        RevLevel = (Dio_PortLevelType)(RevLevel << DIO_IPW_SIUL2_REVERSE_BITS_SHIFT);
        RevLevel = (Dio_PortLevelType)(RevLevel | ((Dio_PortLevelType)(TempLevel & DIO_IPW_SIUL2_REVERSE_BITS_MASK)));
        NumShifts--;
    }

    RevLevel = (Dio_PortLevelType)((uint32)RevLevel << NumShifts); /* Remaining shifts when Level's highest bits are zero */

    return RevLevel;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

/**
* @brief          Dio_Ipw_ReadChannelValue.
*
* @param[in]      u8Siul2Instance       instance index
* @param[in]      Channel               Channel number which need to be read
*
* @return         Level value of channel
*/
static Dio_LevelType Dio_Ipw_ReadChannelValue(uint8 u8Siul2Instance,
                                              Dio_ChannelType Channel
                                             )
{
    Dio_LevelType returnValue = 0U;

    returnValue = (*(Dio_LevelType*)(SIUL2_DIO_IP_GPDI_ADDR32(u8Siul2Instance, Channel)));
#ifdef MCAL_ENABLE_FAULT_INJECTION
    MCAL_FAULT_INJECTION_POINT(DIO_CHANGE_GPDI_VALUE);
#endif
    returnValue &= SIUL2_DIO_IP_GPDI_MASK_U8;

    return returnValue;
}

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

/*===============================================================================================*/

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
*/
Dio_LevelType Dio_Ipw_ReadChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType ChannelLevel = (Dio_LevelType) STD_LOW;
    Dio_PortType PortId;
    uint8 u8Siul2Instance;
    Dio_ChannelType ChannelOffset;
    Dio_ChannelType ChannelIndex;
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    uint8 u8PdacIndex;
#endif

    PortId          = (Dio_PortType)DIO_IPW_PORTID_EXTRACT(ChannelId);
    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];
    ChannelOffset   = (Dio_ChannelType)(Dio_au8Port0OffsetInSiul2Instance[u8Siul2Instance] * DIO_NUM_CHANNELS_PER_PORT_U16);
    ChannelIndex    = ChannelId - ChannelOffset;
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    u8PdacIndex = Dio_au8ChannelToVirtWrapperMap[ChannelId];
#endif

#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    ChannelLevel = Dio_Ipw_ReadChannelValue(u8PdacIndex, ChannelIndex);
#else
    ChannelLevel = Dio_Ipw_ReadChannelValue(u8Siul2Instance, ChannelIndex);
#endif
    return ChannelLevel;
}

/*===============================================================================================*/
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
*/
void Dio_Ipw_WriteChannel(Dio_ChannelType ChannelId,
                          Dio_LevelType Level
                         )
{
    Dio_PortType PortId;
    uint8 u8Siul2Instance;
    Dio_ChannelType ChannelOffset;
    Dio_ChannelType ChannelIndex;
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    uint8 u8PdacIndex;
#endif

    PortId          = (Dio_PortType)DIO_IPW_PORTID_EXTRACT(ChannelId);
    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];
    ChannelOffset   = (Dio_ChannelType)(Dio_au8Port0OffsetInSiul2Instance[u8Siul2Instance] * DIO_NUM_CHANNELS_PER_PORT_U16);
    ChannelIndex    = ChannelId - ChannelOffset;
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    u8PdacIndex = Dio_au8ChannelToVirtWrapperMap[ChannelId];
#endif
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    *(Dio_LevelType*)(SIUL2_DIO_IP_GPDO_ADDR32(u8PdacIndex, ChannelIndex)) = Level;
#else
    *(Dio_LevelType*)(SIUL2_DIO_IP_GPDO_ADDR32(u8Siul2Instance, ChannelIndex)) = Level;
#endif
}

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/*===============================================================================================*/
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

*/
Dio_LevelType Dio_Ipw_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType ChannelLevel = (Dio_LevelType)STD_LOW;
    Dio_PortType PortId;
    uint8 u8Siul2Instance;
    Dio_ChannelType ChannelOffset;
    Dio_ChannelType ChannelIndex;
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    uint8 u8PdacIndex;
#endif

    PortId          = (Dio_PortType)DIO_IPW_PORTID_EXTRACT(ChannelId);
    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];
    ChannelOffset   = (Dio_ChannelType)(Dio_au8Port0OffsetInSiul2Instance[u8Siul2Instance] * DIO_NUM_CHANNELS_PER_PORT_U16);
    ChannelIndex    = ChannelId - ChannelOffset;
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    u8PdacIndex = Dio_au8ChannelToVirtWrapperMap[ChannelId];
#endif
    /* Enter critical region */
    SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_00();

#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    ChannelLevel = Dio_Ipw_ReadChannelValue(u8PdacIndex, ChannelIndex);
#else
    ChannelLevel = Dio_Ipw_ReadChannelValue(u8Siul2Instance, ChannelIndex);
#endif
    if ((Dio_LevelType)STD_LOW == (Dio_LevelType)(ChannelLevel))
    {
        ChannelLevel = (Dio_LevelType)STD_HIGH;
    }
    else
    {
        ChannelLevel = (Dio_LevelType)STD_LOW;
    }
#if (STD_ON == DIO_VIRTWRAPPER_SUPPORT)
    (*(Dio_LevelType*)(SIUL2_DIO_IP_GPDO_ADDR32(u8PdacIndex, ChannelIndex))) = ChannelLevel;
#else
    (*(Dio_LevelType*)(SIUL2_DIO_IP_GPDO_ADDR32(u8Siul2Instance, ChannelIndex))) = ChannelLevel;
#endif

    /* Exit critical region */
    SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_00();
    ChannelLevel = Dio_Ipw_ReadChannelValue(u8Siul2Instance, ChannelIndex);

    return ChannelLevel;
}
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*===============================================================================================*/
/**
* @brief          Returns the level of all channels of specified port.
* @details        This function will return the level of all channels
*                 belonging to the specified port.
*
* @param[in]      PortId      Specifies the required port id.
*
* @return                     Levels of all channels of specified port.
*/
Dio_PortLevelType Dio_Ipw_ReadPort(Dio_PortType PortId)
{
    Dio_PortLevelType PortLevel = (Dio_PortLevelType)STD_LOW;
    uint8 u8Siul2Instance;
    Dio_PortType PortOffset;
    uint32 u32PGPDOAdrress;

    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];
    PortOffset      = Dio_au8Port0OffsetInSiul2Instance[u8Siul2Instance];

    u32PGPDOAdrress = SIUL2_DIO_IP_PGPDO_ADDR32(u8Siul2Instance,(uint32)((uint32)PortId - (uint32)PortOffset));
    PortLevel       = (Dio_PortLevelType)(Siul2_Dio_Ip_ReadPins((Siul2_Dio_Ip_GpioType*)u32PGPDOAdrress));

#if (STD_ON == DIO_READZERO_UNDEFINEDPORTS)
#if (STD_ON == DIO_REVERSED_MAPPING_OF_PORT_BITS_OVER_PORT_PINS)
    PortLevel = (Dio_PortLevelType)(PortLevel & Dio_aAvailablePinsForRead[PortId]);
#else
    PortLevel = (Dio_PortLevelType)(PortLevel & Dio_Ipw_ReverseBits(Dio_aAvailablePinsForRead[PortId]));
#endif /* (STD_ON == DIO_REVERSED_MAPPING_OF_PORT_BITS_OVER_PORT_PINS) */
#endif /* (STD_ON == DIO_READZERO_UNDEFINEDPORTS) */

#if (STD_OFF == DIO_REVERSEPORTBITS)
    PortLevel = (Dio_PortLevelType)(Dio_Ipw_ReverseBits(PortLevel));
#endif
    return PortLevel;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*===============================================================================================*/
/**
* @brief          Sets the value of a port.
* @details        This function will set the specified value on the specified
*                 port.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
*/
void Dio_Ipw_WritePort(Dio_PortType PortId,
                       Dio_PortLevelType Level
                      )
{
    Dio_PortLevelType CrtLevel = Level;
    Dio_PortType PortOffset;
    uint32 u32PGPDOAdrress;
    uint8 u8Siul2Instance;

    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];
    PortOffset      = Dio_au8Port0OffsetInSiul2Instance[u8Siul2Instance];
    /* get PGPDO address from PortId */
    u32PGPDOAdrress = SIUL2_DIO_IP_PGPDO_ADDR32(u8Siul2Instance,(uint32)((uint32)PortId - (uint32)PortOffset));

#if (STD_OFF == DIO_REVERSEPORTBITS)
    CrtLevel = (Dio_PortLevelType)(Dio_Ipw_ReverseBits(CrtLevel));
#endif /* STD_OFF == DIO_REVERSEPORTBITS */
    Siul2_Dio_Ip_WritePins((Siul2_Dio_Ip_GpioType*)u32PGPDOAdrress,CrtLevel);
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*===============================================================================================*/
/**
* @brief          This service reads a subset of the adjoining bits of a port.
* @details        This function will read a subset of adjoining bits of a
*                 port (channel group).
*
* @param[in]      pChannelGroupIdPtr Pointer to the channel group.
* @return                     The channel group levels.
*/
Dio_PortLevelType Dio_Ipw_ReadChannelGroup(const Dio_ChannelGroupType * pChannelGroupIdPtr)
{
    Dio_PortLevelType PortLevel = (Dio_PortLevelType)STD_LOW;
    uint8 u8Siul2Instance;
    Dio_PortType PortId;
    Dio_PortType PortOffset;
    uint32 u32PGPDOAdrress;
    Dio_PortLevelType pinsValue;
    Dio_PortLevelType maskRevValue;

    PortId          = pChannelGroupIdPtr->port;
    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];
    PortOffset      = Dio_au8Port0OffsetInSiul2Instance[u8Siul2Instance];

    u32PGPDOAdrress = SIUL2_DIO_IP_PGPDO_ADDR32(u8Siul2Instance,(uint32)((uint32)PortId - (uint32)PortOffset));
    pinsValue       = (Dio_PortLevelType)Siul2_Dio_Ip_ReadPins((Siul2_Dio_Ip_GpioType*)u32PGPDOAdrress);
    maskRevValue    = (Dio_PortLevelType)Dio_Ipw_ReverseBits(pChannelGroupIdPtr->mask);

#if (STD_OFF == DIO_REVERSEPORTBITS)
    PortLevel = (Dio_PortLevelType)(pinsValue & maskRevValue);
    PortLevel = (Dio_PortLevelType)((uint32)(PortLevel) << (pChannelGroupIdPtr->u8offset));
    PortLevel = (Dio_PortLevelType)(Dio_Ipw_ReverseBits(PortLevel));
#else
    PortLevel = (Dio_PortLevelType)((pinsValue & maskRevValue) >> (pChannelGroupIdPtr->u8offset));
#endif

    return PortLevel;
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
/*===============================================================================================*/
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
* @param[in]      pChannelGroupIdPtr Pointer to the channel group.
* @param[in]      Level       Desired levels for the channel group.
*/
void Dio_Ipw_WriteChannelGroup(const Dio_ChannelGroupType * pChannelGroupIdPtr,
                               Dio_PortLevelType            Level
                              )
{
    Dio_PortType PortId;
    uint8 u8Siul2Instance;

    PortId              = pChannelGroupIdPtr->port;
    u8Siul2Instance     = Dio_au8PortSiul2Instance[PortId];

#if (STD_OFF == DIO_REVERSEPORTBITS)
    Siul2_Dio_Ip_MaskedWritePins(u8Siul2Instance,
                                 PortId,
                                 (Dio_Ipw_ReverseBits(Level)) >> (pChannelGroupIdPtr->u8offset),
                                 Dio_Ipw_ReverseBits(pChannelGroupIdPtr->mask)
                                );
#else
    Siul2_Dio_Ip_MaskedWritePins(u8Siul2Instance,
                                 PortId,
                                 ((Level) << (pChannelGroupIdPtr->u8offset)),
                                 Dio_Ipw_ReverseBits(pChannelGroupIdPtr->mask)
                                );
#endif /* (STD_OFF == DIO_REVERSEPORTBITS) */
}
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#ifdef DIO_VIRTWRAPPER_SUPPORT
#if (STD_OFF == DIO_VIRTWRAPPER_SUPPORT)
#if ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__))
/*===============================================================================================*/
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
*/

void Dio_Ipw_MaskedWritePort(Dio_PortType PortId,
                             Dio_PortLevelType Level,
                             Dio_PortLevelType Mask
                            )
{
    uint8 u8Siul2Instance;

    u8Siul2Instance = Dio_au8PortSiul2Instance[PortId];

#if (STD_OFF == DIO_REVERSEPORTBITS)
    Siul2_Dio_Ip_MaskedWritePins(u8Siul2Instance,
                                 PortId,
                                 Dio_Ipw_ReverseBits(Level),
                                 Dio_Ipw_ReverseBits(Mask & Dio_aAvailablePinsForWrite[PortId])
                                );
#else
    Siul2_Dio_Ip_MaskedWritePins(u8Siul2Instance,
                                 PortId,
                                 Level,
                                 Mask & Dio_aAvailablePinsForWrite[PortId]
                                );
#endif
}
#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__) */
#endif /* (STD_OFF == DIO_VIRTWRAPPER_SUPPORT) */
#endif /* DIO_VIRTWRAPPER_SUPPORT */

#define DIO_STOP_SEC_CODE

#include "Dio_MemMap.h"


#ifdef __cplusplus
}
#endif
/** @} */
