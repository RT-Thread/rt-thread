/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : S32K3XX
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
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef REG_ESYS_H
#define REG_ESYS_H

/**
*   @file
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define REG_ESYS_VENDOR_ID                    43
#define REG_ESYS_MODULE_ID                    0
#define REG_ESYS_AR_RELEASE_MAJOR_VERSION     4
#define REG_ESYS_AR_RELEASE_MINOR_VERSION     7
#define REG_ESYS_AR_RELEASE_REVISION_VERSION  0
#define REG_ESYS_SW_MAJOR_VERSION             5
#define REG_ESYS_SW_MINOR_VERSION             0
#define REG_ESYS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                   REGISTER PROTECTION (REG_PROT)                                  
==================================================================================================*/
/**
* @brief Macros defined for the IPVs that are protected.
*/

#define MCAL_AXBS_REG_PROT_AVAILABLE              (STD_ON)
#define MCAL_XBIC_REG_PROT_AVAILABLE              (STD_ON)
#define MCAL_DMA_REG_PROT_AVAILABLE               (STD_ON)
#define MCAL_DMAMUX_REG_PROT_AVAILABLE            (STD_ON)
#define MCAL_CRC_REG_PROT_AVAILABLE               (STD_ON)
#define MCAL_ZIPWIRE_REG_PROT_AVAILABLE           (STD_ON)
#define MCAL_SIUL2_REG_PROT_AVAILABLE             (STD_ON)
#define MCAL_STM_REG_PROT_AVAILABLE               (STD_ON)
#define MCAL_PRAMC_REG_PROT_AVAILABLE             (STD_ON)
#define MCAL_PFLASH_REG_PROT_AVAILABLE            (STD_ON)
#define MCAL_C40ASF_REG_PROT_AVAILABLE            (STD_ON)
#define MCAL_DCM_REG_PROT_AVAILABLE               (STD_ON)
#define MCAL_CMU_REG_PROT_AVAILABLE               (STD_ON)
#define MCAL_FXOSC_REG_PROT_AVAILABLE             (STD_ON)
#define MCAL_MC_RGM_REG_PROT_AVAILABLE            (STD_ON)
#define MCAL_MC_CGM_REG_PROT_AVAILABLE            (STD_ON)
#define MCAL_MC_ME_REG_PROT_AVAILABLE             (STD_ON)
#define MCAL_PLLDIG_REG_PROT_AVAILABLE            (STD_ON)
#define MCAL_PMC_REG_PROT_AVAILABLE               (STD_ON)

/**
* @brief Macros defined for the protection size
*/
#define AXBS_PROT_MEM_U32                         ((uint32)0x00000004UL)
#define XBIC_PROT_MEM_U32                         ((uint32)0x00000004UL)
#define DMA_PROT_MEM_U32                          ((uint32)0x00000004UL)
#define DMAMUX_PROT_MEM_U32                       ((uint32)0x00000004UL)
#define CRC_PROT_MEM_U32                          ((uint32)0x00000004UL)
#define ZIPWIRE_PROT_MEM_U32                      ((uint32)0x00000004UL)
#define SIUL2_PROT_MEM_U32                        ((uint32)0x00000008UL)
#define STM_PROT_MEM_U32                          ((uint32)0x00000004UL)
#define PRAMC_PROT_MEM_U32                        ((uint32)0x00000004UL)
#define PFLASH_PROT_MEM_U32                       ((uint32)0x00000004UL)
#define C40ASF_PROT_MEM_U32                       ((uint32)0x00000004UL)
#define DCM_PROT_MEM_U32                          ((uint32)0x00000004UL)
#define CMU_PROT_MEM_U32                          ((uint32)0x00000004UL)
#define FXOSC_PROT_MEM_U32                        ((uint32)0x00000004UL)
#define MC_RGM_PROT_MEM_U32                       ((uint32)0x00000004UL)
#define MC_CGM_PROT_MEM_U32                       ((uint32)0x00000004UL)
#define MC_ME_PROT_MEM_U32                        ((uint32)0x00000004UL)
#define PLLDIG_PROT_MEM_U32                       ((uint32)0x00000004UL)
#define PMC_PROT_MEM_U32                          ((uint32)0x00000004UL)


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif


/** @} */

#endif /* REG_ESYS_H */
