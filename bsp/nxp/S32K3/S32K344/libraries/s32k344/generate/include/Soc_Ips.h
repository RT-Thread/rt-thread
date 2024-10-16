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

#ifndef SOC_IPS_H
#define SOC_IPS_H

/**
*   @file   Soc_Ips.h
*
*  @addtogroup BASENXP_COMPONENT
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
#include "Platform_Types.h"
#include "IpVersionMacros.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SOC_IPS_VENDOR_ID                    43
#define SOC_IPS_MODULE_ID                    0
#define SOC_IPS_AR_RELEASE_MAJOR_VERSION     4
#define SOC_IPS_AR_RELEASE_MINOR_VERSION     7
#define SOC_IPS_AR_RELEASE_REVISION_VERSION  0
#define SOC_IPS_SW_MAJOR_VERSION             5
#define SOC_IPS_SW_MINOR_VERSION             0
#define SOC_IPS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Platform_Types.h header file are of the same Autosar version */
    #if ((SOC_IPS_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (SOC_IPS_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Soc_Ips.h and Platform_Types.h are different"
    #endif

    /* Check if source file and IpVersionMacros.h header file are of the same Autosar version */
    #if ((SOC_IPS_AR_RELEASE_MAJOR_VERSION != IPVERSIONMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (SOC_IPS_AR_RELEASE_MINOR_VERSION != IPVERSIONMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Soc_Ips.h and IpVersionMacros.h are different"
    #endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/
/* 40 = 0x28 = CORTEXM_PLATFORM
 * 34 = 0x22 = S32K3 DERIVATIVE ID
 * 02 = 0x02 = Rev. 2
 * 01 = 0x01 = Draft A      (A-B-C-D-E-F-G-H-I-J-K-L-M-N-O-P-Q-R-S-T-U-V-W-X-Y-Z)
*/

/**
* @brief PMC IP Version: PMC v03.00.01.00
* @details S32K3XX IP Versions
*/
#define IPV_PMC                  (0x28220201UL)


/**
* @brief PIT_RTI IP Version: PIT_RTI v05.00.06.11
* @details S32K3XX IP Versions
*/
#define IPV_PIT              (0x28220201UL)


/**
* @brief RTC IP Version: RTC 00.00.03.06
* @details S32K3XX IP Versions
*/
#define IPV_RTC                (0x28220201UL)


/**
* @brief ADCDIG IP Version: v00.00.18.00
* @details S32K3XX IP Versions
*/
#define IPV_ADCDIG               (0x28220201UL)


/**
* @brief SIUL2 IP Version: v00.00.00.10
* @details S32K3XX IP Versions
*/
#define IPV_SIULV2               (0x28220201UL)

/**
* @brief MC IP Version: D_IP_magic_carpet_SYN_302 [v07.00.02.03]
* @details S32K3XX IP Versions
*/
#define IPV_MC                (0x28220201UL)

/**
* @brief PLLDIG IP Version: DA_IP_PLL_SYS_C40ESF3_008 [v00.00.03.04]
* @details S32K3XX IP Versions
*/
#define IPV_PLLDIG               (0x28220201UL)

/**
* @brief FXOSC IP Version: DA_IP_FXOSC_C [v40.00.00.02.05]
* @details S32K3XX IP Versions
*/
#define IPV_FXOSC               (0x28220201UL)

/**
* @brief FIRC IP Version: D_IP_FIRC_SYN_SPEC [v00.00.00.21]
* @details S32K3XX IP Versions
*/
#define IPV_FIRC                (0x28220201UL)

/**
* @brief GMAC IP Version: D_IP_3P_ENET_MAC_SYN_017 [v02.00.00.08]
* @details S32K3XX IP Versions
*/
#define IPV_GMAC                (0x28220201UL)  

/**
* @brief C40ASF IP Version: M_IP_c40asf_spec [v00.00.00.04]
* @details S32K3XX IP Versions
*/
#define IPV_C40ASF              (0x28220201UL) 

/**
* @brief PFLASH IP Version: pflash_c40asf_s32k_spec [v00.00.00.11]
* @details S32K3XX IP Versions
*/
#define IPV_PFLASH              (0x28220201UL)

/**
* @brief C40ASF IP Version: M_IP_c40asf_spec [v00.00.00.04]
* @details S32K3XX IP Versions
*/
#define IPV_FLASH_ARRAY         (0x28220201UL) 

/**
* @brief PFLASH IP Version: pflash_c40asf_s32k_spec [v00.00.00.11]
* @details S32K3XX IP Versions
*/
#define IPV_FLASH_CONTROLLER    (0x28220201UL)  

/**
* @brief QSPI IP Version: QSPI d_ip_quadspi_v2_sync_spec.025
* @details S32K3XX IP Versions
*/
#define IPV_QSPI                (0x28220201UL)          

/**
* @brief Clock Monitoring Unit Frequency Check (CMU_FC) IP Version
* @details S32K3XX IP Versions
*/
#define IPV_CMU_FC              (0x28220201UL) 

/**
* @brief Flexible I/O (FLEXIO) IP Version
* @details S32K3XX IP Versions
*/
#define IPV_FLEXIO              (0x28220201UL) 

/*==================================================================================================
*                              REGISTER PROTECTION (REG_PROT)
==================================================================================================*/
/**
* @brief Register Protection IP Version
* @details S32K3XX IP Versions
*/
#define IPV_REG_PROT                  (0x28220201UL)
 
/*==================================================================================================
*                              Software Erratas for Hardware Erratas
==================================================================================================*/
/**
* @brief Hardware errata for LPSPI: (ERR050456)
* @details ERR050456 LPSPI: Reset to fifo does not work as expected
*/
#define ERR_IPV_LPSPIV2_E050456         (STD_ON)


/**
* @brief Hardware errata for LPSPI: (ERR051588)
* @details ERR051588 LPSPI: Reset transmit FIFO after FIFO underrun by LPSPI Slave
*/
#define ERR_IPV_LPSPIV2_E051588         (STD_ON)

/**
* @brief Hardware errata for GMAC/EMAC: (ERR050705)
* @details ERR050705 GMAC/EMAC: Head-Of-Line blocking error due to incorrect packet size when gates of gate control list (GCL) are closed
*/
#define ERR_IPV_GMAC_E050705    (STD_ON)



/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Enable CACHE management feature
* @details Global define to enable CACHE management at runtime
*/
#define MCAL_CACHE_RUNTIME_MNGMNT (STD_ON)

/**
* @brief number of EMIOS channels per each interrupt
* @details S32K3XX Platform specific Defines/Configurations for EMIOS.
* Can be 1U, 2U, 4U, etc.. depending on the platform
*/
#define EMIOS_CHANNELS_PER_INTERRUPT (4U)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/**
* @brief User Mode feature is enabled
* @details User Mode feature - MCAL is configured to run in supervisor mode, by default.
*/

#ifdef MCAL_ENABLE_SUPERVISOR_MODE
    #undef MCAL_ENABLE_USER_MODE_SUPPORT
#endif
/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


/** @} */

#endif /* SOC_IPS_H */

