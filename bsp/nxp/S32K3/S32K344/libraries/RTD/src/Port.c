/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : SIUL2
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/
/**
* @file Port.c
*
* @implements Port.c_Artifact
* @brief Autosar Port driver main source file
* @details Port driver file that contains the implementation of the interface functions
*
* @addtogroup Port_HLD
* @{
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
#include "Port.h"

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    #include "Det.h"
#endif
#include "Port_Ipw.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
*/
#define PORT_VENDOR_ID_C                    43
#define PORT_AR_RELEASE_MAJOR_VERSION_C     4
#define PORT_AR_RELEASE_MINOR_VERSION_C     7
#define PORT_AR_RELEASE_REVISION_VERSION_C  0
#define PORT_SW_MAJOR_VERSION_C             5
#define PORT_SW_MINOR_VERSION_C             0
#define PORT_SW_PATCH_VERSION_C             0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if source file and Port header file are of the same vendor */
#if (PORT_VENDOR_ID_C != PORT_VENDOR_ID)
    #error "Port.c and Port.h have different vendor ids"
#endif

/* Check if source file and Port header file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port.c and Port.h are different"
#endif

/* Check if source file and Port header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port.c and Port.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the source file and Det.h file are of the same Autosar version */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
        #if ((PORT_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
             (PORT_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Port.c and Det.h are different"
        #endif
    #endif
#endif

/* Check if source file Port.c and header file Port_Ipw.h are of the same vendor */
#if (PORT_VENDOR_ID_C != PORT_VENDOR_ID_IPW_H)
    #error "Port.c and Port_Ipw.h have different vendor ids"
#endif
/* Check if source file Port.c and header file Port_Ipw.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_C    != PORT_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (PORT_AR_RELEASE_MINOR_VERSION_C    != PORT_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (PORT_AR_RELEASE_REVISION_VERSION_C != PORT_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Port.c and Port_Ipw.h are different"
#endif
/* Check if source file Port.c and header file Port'_Ipw.h are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION_IPW_H) || \
     (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION_IPW_H) || \
     (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION_IPW_H)    \
    )
    #error "Software Version Numbers of Port.c and Port_Ipw.h are different"
#endif
/*=================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


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
#define PORT_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Port_MemMap.h"

static const Port_ConfigType * Port_pConfigPtr;

#define PORT_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Port_MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
    extern const Port_ConfigType Port_Config;
#endif

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/
/*=================================================================================================
*                                      LOCAL FUNCTIONS
=================================================================================================*/
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*=================================================================================================
*                                      GLOBAL FUNCTIONS
=================================================================================================*/

/**
* @brief   Initializes the Port Driver module.
* @details The function @p Port_Init() will initialize ALL ports and port pins
*          with the configuration set pointed to by the parameter @p pConfigPtr.
* @post    Port_Init() must be called before all other Port Driver module's functions
*          otherwise no operation can occur on the MCU ports and port pins.
*
* @param[in] ConfigPtr     A pointer to the structure which contains
*                          initialization parameters.
*/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
    const Port_ConfigType * pLocalConfigPtr = &Port_Config;
    /* Cast ConfigPtr to avoid the compiler warning when configuring with PORT_PRECOMPILE_SUPPORT == STD_ON and PORT_DEV_ERROR_DETECT == STD_OFF */
    (void)ConfigPtr;
#else
    const Port_ConfigType * pLocalConfigPtr = ConfigPtr;
#endif /* (STD_ON == PORT_PRECOMPILE_SUPPORT) */

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    uint8 PartitionId;

    PartitionId = (uint8)Port_GetUserId();
#if (STD_OFF == PORT_PRECOMPILE_SUPPORT)
    if (NULL_PTR == ConfigPtr)
#else /*(STD_OFF == PORT_PRECOMPILE_SUPPORT) */
    if (NULL_PTR != ConfigPtr)
#endif /* (STD_OFF == PORT_PRECOMPILE_SUPPORT) */
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, (uint8)PORT_INIT_ID, (uint8)PORT_E_INIT_FAILED);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {

#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if ((uint32)1 != pLocalConfigPtr->pau8Port_PartitionList[PartitionId])
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, (uint8)PORT_INIT_ID, (uint8)PORT_E_PARAM_CONFIG);
        }
        else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
        {
            Port_Ipw_Init(pLocalConfigPtr);
            /*  Save configuration pointer in global variable */
            Port_pConfigPtr = pLocalConfigPtr;
        }
    }
}

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)

/**
* @brief   Sets the port pin direction.
* @details The function @p Port_SetPinDirection() will set the port pin direction
*          during runtime.
* @pre     @p Port_Init() must have been called first. In order to change the
*          pin direction the PortPinDirectionChangeable flag must have been set
*          to @p TRUE.
*
* @param[in] Pin            Pin ID number.
* @param[in] Direction     Port Pin direction.
*
*/
void Port_SetPinDirection(Port_PinType Pin,
                          Port_PinDirectionType Direction
                         )
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Variable used to store current error status */
    Std_ReturnType ErrStatus;

    /* Check if Port module is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif /* PORT_DEV_ERROR_DETECT */
    {
        /* Avoid compiler warning */
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        ErrStatus = Port_Ipw_SetPinDirection(Pin, Direction, Port_pConfigPtr);
#else
        (void)Port_Ipw_SetPinDirection(Pin, Direction, Port_pConfigPtr);
#endif
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if ((Std_ReturnType)E_NOT_OK == ErrStatus)
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_DIRECTION_UNCHANGEABLE);
        }
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
}
#endif /* (STD_ON == PORT_SET_PIN_DIRECTION_API) */


#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)

/**
* @brief   Sets the port pin mode.
* @details The function @p Port_SetPinMode() will set the port pin mode of the
*          referenced pin during runtime.
* @pre     @p Port_Init() must have been called first.
*
* @param[in] Pin       Pin ID number.
* @param[in] Mode      New Port Pin mode to be set on port pin.
*
*/
void Port_SetPinMode(Port_PinType Pin,
                     Port_PinModeType Mode
                    )
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    uint8 u8PinModeError = (uint8)0U;

    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        /* Sets the port pin direction */
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        u8PinModeError = (uint8)Port_Ipw_SetPinMode(Pin, Mode, Port_pConfigPtr);
#else
        (void)Port_Ipw_SetPinMode(Pin, Mode, Port_pConfigPtr);
#endif

#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if (PORT_E_PARAM_INVALID_MODE == u8PinModeError)
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_PARAM_INVALID_MODE);
        }
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
}
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

/**
* @brief   Refreshes port direction.
* @details This function will refresh the direction of all configured ports to
*          the configured direction.
*          The PORT driver will exclude from refreshing those port pins that
*          are configured as "pin direction changeable during runtime".
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_RefreshPortDirection(void)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    uint8 PartitionId;

    PartitionId = (uint8)Port_GetUserId();
    /* Check if Port module is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_REFRESHPINDIRECTION_ID, (uint8)PORT_E_UNINIT);
    }
    else if ((uint32)1 != Port_pConfigPtr->pau8Port_PartitionList[PartitionId])
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, (uint8)PORT_REFRESHPINDIRECTION_ID, (uint8)PORT_E_PARAM_CONFIG);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        Port_Ipw_RefreshPortDirection(Port_pConfigPtr);
    }
}

#if  (STD_ON == PORT_VERSION_INFO_API)
/**
* @brief   Returns the version information of this module.
* @details The function Port_GetVersionInfo() will return the version
*          information of this module. The version information includes:
*          - Module Id,
*          - Vendor Id,
*          - Vendor specific version numbers.
*
* @param[in,out] versioninfo      Pointer to where to store the version
*                                  information of this module.
*
*
*/
void Port_GetVersionInfo(Std_VersionInfoType * versioninfo)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_GETVERSIONINFO_ID, (uint8)PORT_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        (versioninfo)->vendorID         = (uint16)PORT_VENDOR_ID;
        (versioninfo)->moduleID         = (uint16)PORT_MODULE_ID;
        (versioninfo)->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON == PORT_VERSION_INFO_API) */

#ifdef PORT_SET_AS_UNUSED_PIN_API
#if (STD_ON == PORT_SET_AS_UNUSED_PIN_API)

/**
* @brief   Set as unused pin.
* @details This function shall configure the referenced pin with all
*          the properties specified in the NotUsedPortPin container.
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_SetAsUnusedPin(Port_PinType Pin)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETASUNUSEDPIN_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif
    {
        Port_Ipw_SetAsUnusedPin(Pin, Port_pConfigPtr);
    }
}

/**
* @brief   Set as used pin.
* @details This function shall configure the referenced pin with
*          all the properties that where set during the Port_Init operation.
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_SetAsUsedPin(Port_PinType Pin)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETASUSEDPIN_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif
    {
        Port_Ipw_SetAsUsedPin(Pin, Port_pConfigPtr);
    }
}
#endif /* (STD_ON == PORT_SET_AS_UNUSED_PIN_API) */
#endif

#ifdef PORT_CODE_SIZE_OPTIMIZATION
#ifdef PORT_RESET_PIN_MODE_API
#if (STD_ON == PORT_RESET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)

/**
* @brief   Reset Pin Mode.
* @details This function shall revert the port pin mode of the referenced pin
*          to the value that was set by Port_Init operation.
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_ResetPinMode(Port_PinType Pin)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_RESETPINMODE_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif
    {
        Port_Ipw_ResetPinMode(Pin, Port_pConfigPtr);
    }
}

#endif /* (STD_ON == PORT_RESET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_RESET_PIN_MODE_API */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
