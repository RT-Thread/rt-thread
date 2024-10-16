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
*   @addtogroup UART_IPW_DRIVER
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Uart_Ipw_Cfg.h"
#ifdef UART_IPW_LPUART_HW_USING
#include "Lpuart_Uart_Ip_Cfg.h"
#endif
#ifdef UART_IPW_FLEXIO_HW_USING
#include "Flexio_Uart_Ip_Cfg.h"
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define UART_IPW_PBCFG_VENDOR_ID_C                     43
#define UART_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define UART_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define UART_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define UART_IPW_PBCFG_SW_MAJOR_VERSION_C              5
#define UART_IPW_PBCFG_SW_MINOR_VERSION_C              0
#define UART_IPW_PBCFG_SW_PATCH_VERSION_C              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Uart_Ipw_Cfg.h */
#if (UART_IPW_PBCFG_VENDOR_ID_C != UART_IPW_CFG_VENDOR_ID)
    #error "Uart_Ipw_PBcfg.c and Uart_Ipw_Cfg.h have different vendor ids"
#endif
#if ((UART_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != UART_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C    != UART_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C != UART_IPW_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw_PBcfg.c and Uart_Ipw_Cfg.h are different"
#endif
#if ((UART_IPW_PBCFG_SW_MAJOR_VERSION_C != UART_IPW_CFG_SW_MAJOR_VERSION) || \
     (UART_IPW_PBCFG_SW_MINOR_VERSION_C != UART_IPW_CFG_SW_MINOR_VERSION) || \
     (UART_IPW_PBCFG_SW_PATCH_VERSION_C != UART_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw_PBcfg.c and Uart_Ipw_Cfg.h are different"
#endif

#ifdef UART_IPW_LPUART_HW_USING
/* Checks against Lpuart_Uart_Ip_Cfg.h */
#if (UART_IPW_PBCFG_VENDOR_ID_C != LPUART_UART_IP_CFG_VENDOR_ID)
    #error "Uart_Ipw_PBcfg.c and Lpuart_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((UART_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != LPUART_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C    != LPUART_UART_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C != LPUART_UART_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw_PBcfg.c and Lpuart_Uart_Ip_Cfg.h are different"
#endif
#if ((UART_IPW_PBCFG_SW_MAJOR_VERSION_C != LPUART_UART_IP_CFG_SW_MAJOR_VERSION) || \
     (UART_IPW_PBCFG_SW_MINOR_VERSION_C != LPUART_UART_IP_CFG_SW_MINOR_VERSION) || \
     (UART_IPW_PBCFG_SW_PATCH_VERSION_C != LPUART_UART_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw_PBcfg.c and Lpuart_Uart_Ip_Cfg.h are different"
#endif
#endif

#ifdef UART_IPW_FLEXIO_HW_USING
/* Checks against Flexio_Uart_Ip_Cfg.h */
#if (UART_IPW_PBCFG_VENDOR_ID_C != FLEXIO_UART_IP_CFG_VENDOR_ID)
    #error "Uart_Ipw_PBcfg.c and Flexio_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((UART_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (UART_IPW_PBCFG_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (UART_IPW_PBCFG_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Uart_Ipw_PBcfg.c and Flexio_Uart_Ip_Cfg.h are different"
#endif
#if ((UART_IPW_PBCFG_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_CFG_SW_MAJOR_VERSION) || \
     (UART_IPW_PBCFG_SW_MINOR_VERSION_C != FLEXIO_UART_IP_CFG_SW_MINOR_VERSION) || \
     (UART_IPW_PBCFG_SW_PATCH_VERSION_C != FLEXIO_UART_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Uart_Ipw_PBcfg.c and Flexio_Uart_Ip_Cfg.h are different"
#endif
#endif

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"

#ifdef UART_IPW_LPUART_HW_USING
/**
* @brief   Export Lpuart Uart configurations.
*/
LPUART_UART_IP_CONFIG_EXT
#endif

#ifdef UART_IPW_FLEXIO_HW_USING
/**
* @brief   Export Flexio Uart configurations.
*/
FLEXIO_UART_IP_CONFIG_EXT
#endif

#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
/*==================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"
/**
* @brief   The Ip configuration structure pointer
*/
static const Uart_Ipw_IpConfigType Uart_Ipw_IpChnConfigPB_0 =
{
    /* Lpuart Ip configuration structure  */
    &Lpuart_Uart_Ip_xHwConfigPB_0,
    /* Flexio Ip configuration structure  */
    NULL_PTR
};


/**
* @brief    Hardware configuration for Uart Hardware - Configuration.
*/
const Uart_Ipw_HwConfigType Uart_Ipw_xHwConfigPB_0 =
{
    /* Uart Hardware Channel.*/
    3U,
    /* Type of Hardware interface configured.*/
    LPUART_IP,
    /* User Callback */
    NULL_PTR,
    /* Pointer to the Ip configuration structure.*/
    &Uart_Ipw_IpChnConfigPB_0
};
#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

