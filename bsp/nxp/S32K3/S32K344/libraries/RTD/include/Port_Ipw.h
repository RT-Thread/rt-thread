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

#ifndef PORT_IPW_H
#define PORT_IPW_H

/**
*   @file    Port_Ipw.h
*   @internal
*   @defgroup Port_IPW Port IPW
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

#include "Siul2_Port_Ip.h"
#ifdef FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING
#include "Tspc_Port_Ip.h"
#endif /* FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER
#include "Igf_Port_Ip.h"
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER */
#include "Port_Cfg.h"
/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file.
*
*/
#define PORT_VENDOR_ID_IPW_H                    43
#define PORT_AR_RELEASE_MAJOR_VERSION_IPW_H     4
#define PORT_AR_RELEASE_MINOR_VERSION_IPW_H     7
#define PORT_AR_RELEASE_REVISION_VERSION_IPW_H  0
#define PORT_SW_MAJOR_VERSION_IPW_H             5
#define PORT_SW_MINOR_VERSION_IPW_H             0
#define PORT_SW_PATCH_VERSION_IPW_H             0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if the files Port_Ipw.h and Siul2_Port_Ip.h are of the same vendor */
#if (PORT_VENDOR_ID_IPW_H != SIUL2_PORT_IP_VENDOR_ID_H)
    #error "Port_Ipw.h and Siul2_Port_Ip.h have different vendor ids"
#endif
/* Check if the files Port_Ipw.h and Siul2_Port_Ip.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_H    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_H    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_H != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "AutoSar Version Numbers of Port_Ipw.h and Siul2_Port_Ip.h are different"
#endif
/* Check if the files Port_Ipw.h and Siul2_Port_Ip.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_H != SIUL2_PORT_IP_SW_MAJOR_VERSION_H) || \
     (PORT_SW_MINOR_VERSION_IPW_H != SIUL2_PORT_IP_SW_MINOR_VERSION_H) || \
     (PORT_SW_PATCH_VERSION_IPW_H != SIUL2_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_Ipw.h and Siul2_Port_Ip.h are different"
#endif

#ifdef FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING
/* Check if the files Port_Ipw.h and Tspc_Port_Ip.h are of the same vendor */
#if (PORT_VENDOR_ID_IPW_H != TSPC_PORT_IP_VENDOR_ID_H)
    #error "Port_Ipw.h and Tspc_Port_Ip.h have different vendor ids"
#endif
/* Check if the files Port_Ipw.h and Tspc_Port_Ip.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_H    != TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_H    != TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_H != TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "AutoSar Version Numbers of Port_Ipw.h and Tspc_Port_Ip.h are different"
#endif
/* Check if the files Port_Ipw.h and Tspc_Port_Ip.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_H != TSPC_PORT_IP_SW_MAJOR_VERSION_H) || \
     (PORT_SW_MINOR_VERSION_IPW_H != TSPC_PORT_IP_SW_MINOR_VERSION_H) || \
     (PORT_SW_PATCH_VERSION_IPW_H != TSPC_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_Ipw.h and Tspc_Port_Ip.h are different"
#endif
#endif /* FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING */

/* Check if the files Port_Ipw.h and Port_Cfg.h are of the same vendor */
#if (PORT_VENDOR_ID_IPW_H != PORT_CFG_VENDOR_ID_H)
    #error "Port_Ipw.h and Port_Cfg.h have different vendor ids"
#endif
/* Check if the files Port_Ipw.h and Port_Cfg.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_H    != PORT_CFG_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_H    != PORT_CFG_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_H != PORT_CFG_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "AutoSar Version Numbers of Port_Ipw.h and Port_Cfg.h are different"
#endif
/* Check if the files Port_Ipw.h and Port_Cfg.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_H != PORT_CFG_SW_MAJOR_VERSION_H) || \
     (PORT_SW_MINOR_VERSION_IPW_H != PORT_CFG_SW_MINOR_VERSION_H) || \
     (PORT_SW_PATCH_VERSION_IPW_H != PORT_CFG_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_Ipw.h and Port_Cfg.h are different"
#endif
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER
/* Check if the files Port_Ipw.h and Igf_Port_Ip.h are of the same vendor */
#if (PORT_VENDOR_ID_IPW_H != IGF_PORT_IP_VENDOR_ID_H)
    #error "Port_Ipw.h and Igf_Port_Ip.h have different vendor ids"
#endif
/* Check if the files Port_Ipw.h and Igf_Port_Ip.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_IPW_H    != IGF_PORT_IP_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_AR_RELEASE_MINOR_VERSION_IPW_H    != IGF_PORT_IP_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_AR_RELEASE_REVISION_VERSION_IPW_H != IGF_PORT_IP_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "AutoSar Version Numbers of Port_Ipw.h and Igf_Port_Ip.h are different"
#endif
/* Check if the files Port_Ipw.h and Igf_Port_Ip.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_IPW_H != IGF_PORT_IP_SW_MAJOR_VERSION_H) || \
     (PORT_SW_MINOR_VERSION_IPW_H != IGF_PORT_IP_SW_MINOR_VERSION_H) || \
     (PORT_SW_PATCH_VERSION_IPW_H != IGF_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_Ipw.h and Igf_Port_Ip.h are different"
#endif
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_GLITCH_FILTER */
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/
#if (STD_ON == PORT_MULTIPARTITION_ENABLED)
    #define Port_GetUserId()            OsIf_GetUserId()
#else
    #define Port_GetUserId()            ((uint32)0UL)
#endif

#define SIUL2_MODE_BIT_OFFSET_MASK_U8  ((uint8)0x0F)
/* @brief Mask definitions for MSCR bit field IBE */
#define SIUL2_MSCR_IBE_U32                          ((uint32)0x00080000U)
#define SIUL2_MSCR_IBE_ON_U32                       ((uint32)0x00080000U)

#define SIUL2_MSCR_OBE_U32                          ((uint32)0x00200000U)
#define SIUL2_MSCR_OBE_ON_U32                       ((uint32)0x00200000U)

#define SIUL2_MSCR_SSS_U32                          ((uint32)0x0000000FU)
#define SIUL2_MSCR_SSS_OFFSET_U32                   ((uint32)0)

/*
* @brief Initializing value for the unused IMCR registers in order to avoid writting in not valid
*        memory areas
*/
#define SIUL2_UNUSED_IMCR_PATTERN_U8        ((uint32)0xFFU)
/* @brief Mode bit offset mask */
#define SIUL2_BIT_OFFSET_MASK_U8                        ((uint8)0x0F)



/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
void Port_Ipw_Init
(
    const Port_ConfigType * pConfigPtr
);

#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_ON == PORT_SET_PIN_DIRECTION_API) || ((STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION))
/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
Std_ReturnType Port_Ipw_SetPinDirection
(
    Port_PinType PinIndex,
    Port_PinDirectionType eDirection,
    const Port_ConfigType * pConfigPtr
);

#endif /* (STD_ON == PORT_SET_PIN_DIRECTION_API) || ((STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
void Port_Ipw_RefreshPortDirection
(
    const Port_ConfigType * pConfigPtr
);

#ifdef PORT_SET_AS_UNUSED_PIN_API
#if (STD_ON == PORT_SET_AS_UNUSED_PIN_API)
/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
void Port_Ipw_SetAsUnusedPin
(
    Port_PinType PinIndex,
    const Port_ConfigType * pConfigPtr
);

/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
void Port_Ipw_SetAsUsedPin
(
    Port_PinType PinIndex,
    const Port_ConfigType * pConfigPtr
);

#endif /* (STD_ON == PORT_SET_AS_UNUSED_PIN_API) */
#endif

#ifdef PORT_CODE_SIZE_OPTIMIZATION
#ifdef PORT_RESET_PIN_MODE_API
#if (STD_ON == PORT_RESET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)
/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
void Port_Ipw_ResetPinMode
(
    Port_PinType PinIndex,
    const Port_ConfigType * pConfigPtr
);

#endif /* (STD_ON == PORT_RESET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_RESET_PIN_MODE_API */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */

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
*                                     FUNCTION PROTOTYPES
=================================================================================================*/
/* Allocate defined section for PORT code */


#ifdef PORT_CODE_SIZE_OPTIMIZATION
#if (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION)
/*!
 * @brief
 *
 * @details
 *
 *
 * @param[in]
 *
 * @return void
 *
 *
 **/
Std_ReturnType Port_Ipw_SetPinMode
(
    Port_PinType PinIndex,
    Port_PinModeType PinMode,
    const Port_ConfigType * pConfigPtr
);
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) && (STD_OFF == PORT_CODE_SIZE_OPTIMIZATION) */
#endif /* PORT_CODE_SIZE_OPTIMIZATION */


#ifdef __cplusplus
}
#endif

/** @} */

#endif /*PORT_IPW_H*/
