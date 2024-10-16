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

#ifndef TSPC_PORT_IP_TYPES_H
#define TSPC_PORT_IP_TYPES_H

/**
*   @file    Tspc_Port_Ip_Types.h
*
*   @defgroup Tspc_IPL TSPC IPL
*   @{
*/

#if defined(__cplusplus)
extern "C" {
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file and also in the
 *        module's description file
 */
#define TSPC_PORT_IP_TYPES_VENDOR_ID_H                     43
#define TSPC_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H      4
#define TSPC_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H      7
#define TSPC_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H   0
#define TSPC_PORT_IP_TYPES_SW_MAJOR_VERSION_H              5
#define TSPC_PORT_IP_TYPES_SW_MINOR_VERSION_H              0
#define TSPC_PORT_IP_TYPES_SW_PATCH_VERSION_H              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Tspc_Port_Ip_Types.h and Std_Types.h are of the same version */
    #if ((TSPC_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H != STD_AR_RELEASE_MAJOR_VERSION) || \
         (TSPC_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Tspc_Port_Ip_Types.h and Std_Types.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define TSPC_INVALID_GROUP_INDEX (0xFFFFU)

/******************************************************************************
* TSPC pads participating in the grouping
*
* Tspc_grp1
* @{
*******************************************************************************/
#define PTD1_OBE   (uint64_t)(1ULL << 0)  /* TSPC_ADC0/TSPC_GPIO0 */
#define PTD0_OBE   (uint64_t)(1ULL << 1)  /* TSPC_ADC0 */
#define PTB3_OBE   (uint64_t)(1ULL << 2)  /* TSPC_GPIO0 */
#define PTB2_OBE   (uint64_t)(1ULL << 3)  /* TSPC_GPIO0 */
#define PTB1_OBE   (uint64_t)(1ULL << 4)  /* TSPC_ADC0 */
#define PTB0_OBE   (uint64_t)(1ULL << 5)  /* TSPC_ADC0 */
#define PTC9_OBE   (uint64_t)(1ULL << 6)  /* TSPC_ADC0 */
#define PTC8_OBE   (uint64_t)(1ULL << 7)  /* TSPC_ADC0/TSPC_GPIO0 */
#define PTA7_OBE   (uint64_t)(1ULL << 8)  /* TSPC_ADC0 */
#define PTB13_OBE  (uint64_t)(1ULL << 9)  /* TSPC_ADC0/TSPC_GPIO0 */
#define PTD3_OBE   (uint64_t)(1ULL << 10) /* TSPC_ADC0/TSPC_GPIO0 */
#define PTD2_OBE   (uint64_t)(1ULL << 11) /* TSPC_ADC0 */
#define PTE16_OBE  (uint64_t)(1ULL << 12) /* TSPC_ADC0/TSPC_GPIO0 */
#define PTE15_OBE  (uint64_t)(1ULL << 13) /* TSPC_ADC0/TSPC_GPIO0 */
#define PTE11_OBE  (uint64_t)(1ULL << 14) /* TSPC_ADC0 */
#define PTE10_OBE  (uint64_t)(1ULL << 15) /* TSPC_ADC0/TSPC_GPIO0 */
#define PTC12_OBE  (uint64_t)(1ULL << 16) /* TSPC_GPIO0 */
#define PTC11_OBE  (uint64_t)(1ULL << 17) /* TSPC_ADC0 */
#define PTC10_OBE  (uint64_t)(1ULL << 18) /* TSPC_GPIO0 */
#define PTA6_OBE   (uint64_t)(1ULL << 19) /* TSPC_ADC0 */
#define PTB17_OBE  (uint64_t)(1ULL << 20) /* TSPC_GPIO0 */
#define PTB15_OBE  (uint64_t)(1ULL << 21) /* TSPC_GPIO0 */
#define PTB14_OBE  (uint64_t)(1ULL << 22) /* TSPC_ADC0 */
#define PTB12_OBE  (uint64_t)(1ULL << 23) /* TSPC_GPIO0 */
#define PTD4_OBE   (uint64_t)(1ULL << 24) /* TSPC_ADC0 */
#define PTA18_OBE  (uint64_t)(1ULL << 25) /* TSPC_GPIO0 */
#define PTA19_OBE  (uint64_t)(1ULL << 26) /* TSPC_GPIO0 */
#define PTA20_OBE  (uint64_t)(1ULL << 27) /* TSPC_GPIO0 */
#define PTA21_OBE  (uint64_t)(1ULL << 28) /* TSPC_GPIO0 */
#define PTE5_OBE   (uint64_t)(1ULL << 29) /* TSPC_GPIO0 */
#define PTE4_OBE   (uint64_t)(1ULL << 30) /* TSPC_GPIO0 */
#define PTC21_OBE  (uint64_t)(1ULL << 31) /* TSPC_GPIO0 */
#define PTC23_OBE  (uint64_t)(1ULL << 32) /* TSPC_GPIO0 */
#define PTC24_OBE  (uint64_t)(1ULL << 33) /* TSPC_GPIO0 */
#define PTC25_OBE  (uint64_t)(1ULL << 34) /* TSPC_ADC0 */
#define PTC26_OBE  (uint64_t)(1ULL << 35) /* TSPC_ADC0 */
#define PTC27_OBE  (uint64_t)(1ULL << 36) /* TSPC_GPIO0 */
#define PTC28_OBE  (uint64_t)(1ULL << 37) /* TSPC_GPIO0 */
#define PTC29_OBE  (uint64_t)(1ULL << 38) /* TSPC_GPIO0 */
#define PTC30_OBE  (uint64_t)(1ULL << 39) /* TSPC_GPIO0 */
#define PTC31_OBE  (uint64_t)(1ULL << 40) /* TSPC_GPIO0 */
#define PTE7_OBE   (uint64_t)(1ULL << 41) /* TSPC_GPIO0 */
#define PTA17_OBE  (uint64_t)(1ULL << 42) /* TSPC_GPIO0 */
#define PTD20_OBE  (uint64_t)(1ULL << 43) /* TSPC_ADC0 */
#define PTD21_OBE  (uint64_t)(1ULL << 44) /* TSPC_GPIO0 */
#define PTD22_OBE  (uint64_t)(1ULL << 45) /* TSPC_GPIO0 */
/*! @} End of tspc_grp1                                                       */

/******************************************************************************
* TSPC pads participating in the grouping
*
* Tspc_grp2
* @{
*******************************************************************************/
#define PTA3_OBE   (uint64_t)(1ULL << 0)  /* TSPC_ADC1 */
#define PTA2_OBE   (uint64_t)(1ULL << 1)  /* TSPC_GPIO1 */
#define PTA0_OBE   (uint64_t)(1ULL << 2)  /* TSPC_GPIO1 */
#define PTC7_OBE   (uint64_t)(1ULL << 3)  /* TSPC_ADC1/TSPC_GPIO1 */
#define PTA13_OBE  (uint64_t)(1ULL << 4)  /* TSPC_ADC1 */
#define PTA11_OBE  (uint64_t)(1ULL << 5)  /* TSPC_ADC1/TSPC_GPIO1 */
#define PTA10_OBE  (uint64_t)(1ULL << 6)  /* TSPC_GPIO1 */
#define PTC5_OBE   (uint64_t)(1ULL << 7)  /* TSPC_ADC1 */
#define PTA4_OBE   (uint64_t)(1ULL << 8)  /* TSPC_ADC1 */
#define PTB11_OBE  (uint64_t)(1ULL << 9)  /* TSPC_GPIO1 */
#define PTB10_OBE  (uint64_t)(1ULL << 10) /* TSPC_GPIO1 */
#define PTB9_OBE   (uint64_t)(1ULL << 11) /* TSPC_GPIO1 */
#define PTB8_OBE   (uint64_t)(1ULL << 12) /* TSPC_GPIO1 */
#define PTA16_OBE  (uint64_t)(1ULL << 13) /* TSPC_GPIO1 */
#define PTA15_OBE  (uint64_t)(1ULL << 14) /* TSPC_ADC1 */
#define PTE6_OBE   (uint64_t)(1ULL << 15) /* TSPC_ADC1/TSPC_GPIO1 */
#define PTE2_OBE   (uint64_t)(1ULL << 16) /* TSPC_ADC1 */
#define PTA14_OBE  (uint64_t)(1ULL << 17) /* TSPC_ADC1/TSPC_GPIO1 */
#define PTE1_OBE   (uint64_t)(1ULL << 18) /* TSPC_ADC1 */
#define PTE0_OBE   (uint64_t)(1ULL << 19) /* TSPC_GPIO1 */
#define PTA9_OBE   (uint64_t)(1ULL << 20) /* TSPC_GPIO1 */
#define PTA12_OBE  (uint64_t)(1ULL << 21) /* TSPC_ADC1 */
#define PTD23_OBE  (uint64_t)(1ULL << 22) /* TSPC_GPIO1 */
#define PTD24_OBE  (uint64_t)(1ULL << 23) /* TSPC_ADC1 */
#define PTD26_OBE  (uint64_t)(1ULL << 24) /* TSPC_GPIO1 */
#define PTD27_OBE  (uint64_t)(1ULL << 25) /* TSPC_ADC1 */
#define PTD28_OBE  (uint64_t)(1ULL << 26) /* TSPC_ADC1 */
#define PTD29_OBE  (uint64_t)(1ULL << 27) /* TSPC_ADC1 */
#define PTD30_OBE  (uint64_t)(1ULL << 28) /* TSPC_GPIO1 */
#define PTD31_OBE  (uint64_t)(1ULL << 29) /* TSPC_GPIO1 */
#define PTE17_OBE  (uint64_t)(1ULL << 30) /* TSPC_ADC1 */
#define PTE18_OBE  (uint64_t)(1ULL << 31) /* TSPC_GPIO1 */
#define PTE21_OBE  (uint64_t)(1ULL << 32) /* TSPC_GPIO1 */
#define PTE22_OBE  (uint64_t)(1ULL << 33) /* TSPC_GPIO1 */
#define PTE23_OBE  (uint64_t)(1ULL << 34) /* TSPC_GPIO1 */
#define PTE24_OBE  (uint64_t)(1ULL << 35) /* TSPC_GPIO1 */
#define PTE25_OBE  (uint64_t)(1ULL << 36) /* TSPC_GPIO1 */
#define PTE26_OBE  (uint64_t)(1ULL << 37) /* TSPC_GPIO1 */
/*! @} End of tspc_grp2                                                       */

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    uint8                       obeGroupSelect;    /*!< obeGroup number */
    uint32                      obeGroupIndex;     /*!< obeGroupIndex number */
} Tspc_Port_Ip_ObeGroupConfig;
/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#if defined(__cplusplus)
}
#endif

/** @} */

#endif /* TSPC_PORT_IP_TYPES_H */
