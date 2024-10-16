/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
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

#ifndef POWER_IP_SPECIFIC_H
#define POWER_IP_SPECIFIC_H

/**
*   @file       Power_Ip_Specific.h
*   @version    5.0.0
*
*   @brief   POWER IP driver header file.
*   @details POWER IP driver header file.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
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
#include "Power_Ip_Cfg_Defines.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_SPECIFIC_VENDOR_ID                       43
#define POWER_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_SPECIFIC_SW_MAJOR_VERSION                5
#define POWER_IP_SPECIFIC_SW_MINOR_VERSION                0
#define POWER_IP_SPECIFIC_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_Specific.h file and Power_Ip_Cfg_Defines.h file have same versions */
#if (POWER_IP_SPECIFIC_VENDOR_ID  != POWER_IP_CFG_DEFINES_VENDOR_ID)
    #error "Power_Ip_Specific.h and Power_Ip_Cfg_Defines.h have different vendor IDs"
#endif

/* Check if Power_Ip_Specific.h file and Power_Ip_Cfg_Defines.h file are of the same Autosar version */
#if ((POWER_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION    != POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION    != POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION != POWER_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Specific.h and Power_Ip_Cfg_Defines.h are different"
#endif

/* Check if Power_Ip_Specific.h file and Power_Ip_Cfg_Defines.h file are of the same Software version */
#if ((POWER_IP_SPECIFIC_SW_MAJOR_VERSION != POWER_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (POWER_IP_SPECIFIC_SW_MINOR_VERSION != POWER_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (POWER_IP_SPECIFIC_SW_PATCH_VERSION != POWER_IP_CFG_DEFINES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_Specific.h and Power_Ip_Cfg_Defines.h are different"
#endif


/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#if (defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || defined(POWER_IP_DERIVATIVE_004) || defined(POWER_IP_DERIVATIVE_005))
    #define MC_RGM_FES_SWT1_RST_MASK32              ((uint32)0x00000080U)
    #define MC_RGM_FES_SWT1_RST_MASK                ((uint32)0x00000000U)
    #define MC_RGM_FERD_D_SWT1_RST_MASK             ((uint32)0x00000000U)
#endif

#if (!(defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_008) || defined(POWER_IP_DERIVATIVE_009)))
    #define MC_RGM_FES_SWT2_RST_MASK32              ((uint32)0x00000100U)
    #define MC_RGM_FES_SWT2_RST_MASK                ((uint32)0x00000000U)
    #define MC_RGM_FERD_D_SWT2_RST_MASK             ((uint32)0x00000000U)
#endif

#if (!(defined(POWER_IP_DERIVATIVE_008)))
    #define MC_RGM_FES_SWT3_RST_MASK32              ((uint32)0x00000400U)
    #define MC_RGM_FES_SWT3_RST_MASK                ((uint32)0x00000000U)
    #define MC_RGM_FERD_D_SWT3_RST_MASK             ((uint32)0x00000000U)
#endif

#if (!(defined(POWER_IP_DERIVATIVE_008) || defined(POWER_IP_DERIVATIVE_009)))
    #define MC_RGM_FES_PLL_AUX_MASK32              ((uint32)0x00001000U)
    #define MC_RGM_FES_PLL_AUX_MASK                ((uint32)0x00000000U)
#endif

#if (!(defined(POWER_IP_DERIVATIVE_006) || defined(POWER_IP_DERIVATIVE_008)))
    #define MC_RGM_DES_CM7_CORE_CLK_FAIL_MASK32     ((uint32)0x00010000U)
    #define MC_RGM_DES_CM7_CORE_CLK_FAIL_MASK       ((uint32)0x00000000U)
#endif

#define MC_RGM_FES_RWBITS_MASK32    ((uint32)(MC_RGM_FES_DEBUG_FUNC_MASK | \
                                              MC_RGM_FES_SW_FUNC_MASK | \
                                              MC_RGM_FES_HSE_BOOT_RST_MASK | \
                                              MC_RGM_FES_HSE_SWT_RST_MASK | \
                                              MC_RGM_FES_JTAG_RST_MASK | \
                                              MC_RGM_FES_PLL_AUX_MASK  | \
                                              MC_RGM_FES_SWT3_RST_MASK | \
                                              MC_RGM_FES_SWT2_RST_MASK | \
                                              MC_RGM_FES_SWT1_RST_MASK | \
                                              MC_RGM_FES_SWT0_RST_MASK  | \
                                              MC_RGM_FES_ST_DONE_MASK  | \
                                              MC_RGM_FES_FCCU_RST_MASK  | \
                                              MC_RGM_FES_F_EXR_MASK))

#define MC_RGM_DES_RWBITS_MASK32    ((uint32)(MC_RGM_DES_DEBUG_DEST_MASK | \
                                            MC_RGM_DES_SW_DEST_MASK | \
                                            MC_RGM_DES_HSE_SNVS_RST_MASK | \
                                            MC_RGM_DES_HSE_TMPR_RST_MASK | \
                                            MC_RGM_DES_CM7_CORE_CLK_FAIL_MASK | \
                                            MC_RGM_DES_SYS_DIV_FAIL_MASK | \
                                            MC_RGM_DES_HSE_CLK_FAIL_MASK | \
                                            MC_RGM_DES_AIPS_PLAT_CLK_FAIL_MASK | \
                                            MC_RGM_DES_CORE_CLK_FAIL_MASK  | \
                                            MC_RGM_DES_PLL_LOL_MASK  | \
                                            MC_RGM_DES_FXOSC_FAIL_MASK  | \
                                            MC_RGM_DES_MC_RGM_FRE_MASK  | \
                                            MC_RGM_DES_STCU_URF_MASK  | \
                                            MC_RGM_DES_FCCU_FTR_MASK  | \
                                            MC_RGM_DES_F_POR_MASK))

#define MC_RGM_FES_IRQ_BITS_MASK    ((uint32)(MC_RGM_FES_DEBUG_FUNC_MASK | \
                                              MC_RGM_FES_JTAG_RST_MASK  | \
                                              MC_RGM_FES_PLL_AUX_MASK | \
                                              MC_RGM_FES_SWT3_RST_MASK | \
                                              MC_RGM_FES_SWT2_RST_MASK  | \
                                              MC_RGM_FES_SWT1_RST_MASK  | \
                                              MC_RGM_FES_SWT0_RST_MASK  | \
                                              MC_RGM_FES_FCCU_RST_MASK))

#define MC_RGM_DES_IRQ_BITS_MASK    ((uint32) 0x00000000U)

#define MC_RGM_RAWRESET_FES_BASE_SHIFT_U32      ((uint32)15U)
#define MC_RGM_RAWRESET_DES_BASE_SHIFT_U32      ((uint32)0U)

#define MC_RGM_FERD_RWBITS_MASK     ((uint32)(MC_RGM_FERD_D_FCCU_RST_MASK | \
                                              MC_RGM_FERD_D_SWT0_RST_MASK | \
                                              MC_RGM_FERD_D_SWT1_RST_MASK  | \
                                              MC_RGM_FERD_D_SWT2_RST_MASK  | \
                                              MC_RGM_FERD_D_SWT3_RST_MASK  | \
                                              MC_RGM_FERD_D_JTAG_RST_MASK  | \
                                              MC_RGM_FERD_D_DEBUG_FUNC_MASK))
#define POWER_IP_RESET_REASON_FILTER

/***********************************************************/
/*                       MC_RGM_RDSS                       */
/***********************************************************/
#define MC_RGM_FES_RES_OCCURED_DURING_STANDBY_U32               ((uint32)MC_RGM_RDSS_FES_RES_MASK)
#define MC_RGM_FES_RES_NOT_OCCURED_DURING_STANDBY_U32           ((uint32)0x00000000U)

#define MC_RGM_DES_RES_OCCURED_DURING_STANDBY_U32               ((uint32)MC_RGM_RDSS_DES_RES_MASK)
#define MC_RGM_DES_RES_NOT_OCCURED_DURING_STANDBY_U32           ((uint32)0x00000000U)

#define MC_RGM_RDSS_RWBITS_MASK_U32                             ((uint32)MC_RGM_RDSS_DES_RES_MASK | (uint32)MC_RGM_RDSS_FES_RES_MASK)

#define MC_RGM_RDSS_FES_RES_MASK_U32                            ((uint32)MC_RGM_RDSS_FES_RES_MASK)
#define MC_RGM_RDSS_DES_RES_MASK_U32                            ((uint32)MC_RGM_RDSS_DES_RES_MASK)

/***********************************************************/
/*             Power_Ip_MC_RGM_GetResetRawValue Defines             */
/***********************************************************/
#define MC_RGM_RAWRESET_FES_F_F_EXR_MASK32               ((uint32)( ( (uint32)0x01U << (uint32)0x0U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_FCCU_RST_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x1U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_ST_DONE_MASK32             ((uint32)( ( (uint32)0x01U << (uint32)0x2U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_SWT0_RST_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x3U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_SWT1_RST_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x4U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_SWT2_RST_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x5U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_JTAG_RST_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x6U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_SWT3_RST_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x7U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_PLL_AUX_MASK32             ((uint32)( ( (uint32)0x01U << (uint32)0x8U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_HSE_SWT_RST_MASK32         ((uint32)( ( (uint32)0x01U << (uint32)0x9U ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_HSE_BOOT_RST_MASK32        ((uint32)( ( (uint32)0x01U << (uint32)0xAU ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_SW_FUNC_MASK32             ((uint32)( ( (uint32)0x01U << (uint32)0xBU ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_FES_F_DEBUG_FUNC_MASK32          ((uint32)( ( (uint32)0x01U << (uint32)0xCU ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_WAKEUP_MASK32                    ((uint32)( ( (uint32)0x01U << (uint32)0xDU ) << MC_RGM_RAWRESET_FES_BASE_SHIFT_U32 ))

#define MC_RGM_RAWRESET_DES_F_POR_MASK32                 ((uint32)( ( (uint32)0x01U << (uint32)0x0U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_FCCU_FTR_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x1U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_STCU_URF_MASK32            ((uint32)( ( (uint32)0x01U << (uint32)0x2U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_MC_RGM_FRE_MASK32          ((uint32)( ( (uint32)0x01U << (uint32)0x3U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_FXOSC_FAIL_MASK32          ((uint32)( ( (uint32)0x01U << (uint32)0x4U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_PLL_LOL_MASK32             ((uint32)( ( (uint32)0x01U << (uint32)0x5U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_CORE_CLK_FAIL_MASK32       ((uint32)( ( (uint32)0x01U << (uint32)0x6U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_AIPS_PLAT_CLK_FAIL_MASK32  ((uint32)( ( (uint32)0x01U << (uint32)0x7U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_HSE_CLK_FAIL_MASK32        ((uint32)( ( (uint32)0x01U << (uint32)0x8U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_SYS_DIV_FAIL_MASK32        ((uint32)( ( (uint32)0x01U << (uint32)0x9U ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_CM7_CORE_CLK_FAIL_MASK32   ((uint32)( ( (uint32)0x01U << (uint32)0xAU ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_HSE_TMPR_RST_MASK32        ((uint32)( ( (uint32)0x01U << (uint32)0xBU ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_HSE_SNVS_RST_MASK32        ((uint32)( ( (uint32)0x01U << (uint32)0xCU ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_SW_DEST_MASK32             ((uint32)( ( (uint32)0x01U << (uint32)0xDU ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))
#define MC_RGM_RAWRESET_DES_F_DEBUG_DEST_MASK32          ((uint32)( ( (uint32)0x01U << (uint32)0xEU ) << MC_RGM_RAWRESET_DES_BASE_SHIFT_U32 ))

/***********************************************************/
/*                    MC_ME_MAIN_COREID                    */
/***********************************************************/

#define MC_ME_MAIN_COREID_U32(value)                    ((uint32)( (uint32)(MC_ME_MAIN_COREID_CIDX(value)) | (uint32)(MC_ME_MAIN_COREID_PIDX(value)) ))

#define MC_ME_MAIN_COREID_NOT_USED_U32                  ((uint32)0x1FU)

#define MC_ME_MAIN_COREID_PIDX_CM7_0_U32                (MC_ME_MAIN_COREID_PIDX((uint32)0U))
#define MC_ME_MAIN_COREID_PIDX_CM7_1_U32                (MC_ME_MAIN_COREID_PIDX((uint32)0U))
#define MC_ME_MAIN_COREID_PIDX_CM7_2_U32                (MC_ME_MAIN_COREID_PIDX((uint32)0U))

#define MC_ME_MAIN_COREID_CIDX_CM7_0_U32                (MC_ME_MAIN_COREID_CIDX((uint32)0U))
#define MC_ME_MAIN_COREID_CIDX_CM7_1_U32                (MC_ME_MAIN_COREID_CIDX((uint32)1U))
#define MC_ME_MAIN_COREID_CIDX_CM7_2_U32                (MC_ME_MAIN_COREID_CIDX((uint32)2U))

#define MC_ME_PRTNx_PUPD_PCUD_MASK                      ((uint32)MC_ME_PRTN1_PUPD_PCUD_MASK)
#define MC_ME_PRTN0_PUPD_RWBITS_MASK                    ((uint32)MC_ME_PRTN1_PUPD_PCUD_MASK)
#define MC_ME_PRTN1_PUPD_RWBITS_MASK                    ((uint32)MC_ME_PRTN1_PUPD_PCUD_MASK)
#define MC_ME_PRTN2_PUPD_RWBITS_MASK                    ((uint32)MC_ME_PRTN1_PUPD_PCUD_MASK)
#define MC_ME_PRTN3_PUPD_RWBITS_MASK                    ((uint32)MC_ME_PRTN1_PUPD_PCUD_MASK)

#if defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_002) || defined(POWER_IP_DERIVATIVE_006)
#define PMC_LVSC_RAMP_UP_RESET_FLAGS_RWBITS_MASK    (((uint32)PMC_LVSC_PORF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11F_MASK | \
                                                      (uint32)PMC_LVSC_LVR25LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR25F_MASK | \
                                                      (uint32)PMC_LVSC_LVRALPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRAF_MASK))

#define PMC_LVSC_RWBITS_MASK                        (((uint32)PMC_LVSC_PORF_MASK | \
                                                      (uint32)PMC_LVSC_GNG11OSCF_MASK | \
                                                      (uint32)PMC_LVSC_GNG25OSCF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11F_MASK | \
                                                      (uint32)PMC_LVSC_LVR25LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR25F_MASK | \
                                                      (uint32)PMC_LVSC_LVRALPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRAF_MASK | \
                                                      (uint32)PMC_LVSC_LVD5AF_MASK | \
                                                      (uint32)PMC_LVSC_HVD11F_MASK | \
                                                      (uint32)PMC_LVSC_HVD25F_MASK | \
                                                      (uint32)PMC_LVSC_HVDAF_MASK))
#elif defined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_008)
#define PMC_LVSC_RAMP_UP_RESET_FLAGS_RWBITS_MASK    (((uint32)PMC_LVSC_PORF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11F_MASK | \
                                                      (uint32)PMC_LVSC_LVR25LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR25F_MASK | \
                                                      (uint32)PMC_LVSC_LVRBLPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRBF_MASK | \
                                                      (uint32)PMC_LVSC_LVRALPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRAF_MASK))

#define PMC_LVSC_RWBITS_MASK                        (((uint32)PMC_LVSC_PORF_MASK | \
                                                      (uint32)PMC_LVSC_GNG11OSCF_MASK | \
                                                      (uint32)PMC_LVSC_GNG25OSCF_MASK | \
                                                      (uint32)PMC_LVSC_GNG11OSCF_MASK | \
                                                      (uint32)PMC_LVSC_GNG25OSCF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11F_MASK | \
                                                      (uint32)PMC_LVSC_LVR25LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR25F_MASK | \
                                                      (uint32)PMC_LVSC_LVRBLPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRBF_MASK | \
                                                      (uint32)PMC_LVSC_LVRALPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRAF_MASK | \
                                                      (uint32)PMC_LVSC_HVD15S_MASK | \
                                                      (uint32)PMC_LVSC_LVD5AS_MASK | \
                                                      (uint32)PMC_LVSC_HVD11S_MASK | \
                                                      (uint32)PMC_LVSC_HVD25S_MASK | \
                                                      (uint32)PMC_LVSC_HVDBS_MASK | \
                                                      (uint32)PMC_LVSC_HVDAS_MASK | \
                                                      (uint32)PMC_LVSC_HVD15F_MASK | \
                                                      (uint32)PMC_LVSC_LVD5AF_MASK | \
                                                      (uint32)PMC_LVSC_HVD11F_MASK | \
                                                      (uint32)PMC_LVSC_HVD25F_MASK | \
                                                      (uint32)PMC_LVSC_HVDBF_MASK | \
                                                      (uint32)PMC_LVSC_HVDAF_MASK))
#else
#define PMC_LVSC_RAMP_UP_RESET_FLAGS_RWBITS_MASK    (((uint32)PMC_LVSC_PORF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11F_MASK | \
                                                      (uint32)PMC_LVSC_LVR25LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR25F_MASK | \
                                                      (uint32)PMC_LVSC_LVRBLPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRBF_MASK | \
                                                      (uint32)PMC_LVSC_LVRALPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRAF_MASK))

#define PMC_LVSC_RWBITS_MASK                        (((uint32)PMC_LVSC_PORF_MASK | \
                                                      (uint32)PMC_LVSC_GNG11OSCF_MASK | \
                                                      (uint32)PMC_LVSC_GNG25OSCF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR11F_MASK | \
                                                      (uint32)PMC_LVSC_LVR25LPF_MASK | \
                                                      (uint32)PMC_LVSC_LVR25F_MASK | \
                                                      (uint32)PMC_LVSC_LVRBLPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRBF_MASK | \
                                                      (uint32)PMC_LVSC_LVRALPF_MASK | \
                                                      (uint32)PMC_LVSC_LVRAF_MASK | \
                                                      (uint32)PMC_LVSC_LVD15F_MASK | \
                                                      (uint32)PMC_LVSC_LVD5AF_MASK | \
                                                      (uint32)PMC_LVSC_HVD11F_MASK | \
                                                      (uint32)PMC_LVSC_HVD25F_MASK | \
                                                      (uint32)PMC_LVSC_HVDBF_MASK | \
                                                      (uint32)PMC_LVSC_HVDAF_MASK))
#endif

#define MC_ME_MODE_CONF_MASK                        ( (uint32)(MC_ME_MODE_CONF_DEST_RST_MASK) | (uint32)(MC_ME_MODE_CONF_FUNC_RST_MASK) | (uint32)(MC_ME_MODE_CONF_STANDBY_MASK) )

#define MC_ME_MODE_CONF(value)                      ((uint32)(((uint32)(value)) & ((uint32)(MC_ME_MODE_CONF_MASK))))

#define POWER_IP_MC_ME_PRTN_COUNT                   (3U)
#define POWER_IP_MC_ME_CORE_COUNT                   (3U)
#define POWER_IP_MC_ME_COFB_COUNT                   (4U)

/**
* @brief            This macro is used to define the position of the first reset reason.
*
*/
#define POWER_IP_FIRST_RESET_REASON_POS                 ((uint32)MCU_POWER_ON_RESET)

#define POWER_IP_SOC_PREPARE_STANDBY_MODE_SUPPORT       (STD_ON)


/***********************************************************/
/*                        DMC_GPR                          */
/***********************************************************/

#if (defined(POWER_IP_DERIVATIVE_001) || defined(POWER_IP_DERIVATIVE_003) || defined(POWER_IP_DERIVATIVE_004) || defined(POWER_IP_DERIVATIVE_005) || defined(POWER_IP_DERIVATIVE_007))

#define DCM_GPR_DCMRWF2_RWBITS_MASK                 (((uint32)DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_MASK))

#elif (defined(POWER_IP_DERIVATIVE_006))
#define DCM_GPR_DCMRWF2_RWBITS_MASK                 (((uint32)DCM_GPR_DCMRWF2_PGOOD_POLARITY_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_MASK))
#elif (defined(POWER_IP_DERIVATIVE_008) || defined(POWER_IP_DERIVATIVE_009))
#define DCM_GPR_DCMRWF2_RWBITS_MASK                 (((uint32)DCM_GPR_DCMRWF2_PGOOD_POLARITY_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_PLL1_LOL_RST_EN_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_MASK))
#else
#define DCM_GPR_DCMRWF2_RWBITS_MASK                 (((uint32)DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_MASK | \
                                                      (uint32)DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_MASK))
#endif



#if defined(POWER_IP_DERIVATIVE_006)

/*! @name PRTN0_COFB0_CLKEN - Partition 0 COFB Set 0 Clock Enable Register */
/*! @{ */

#define MC_ME_PRTN0_COFB0_CLKEN_REQ3_MASK        (0x8U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ3_SHIFT       (3U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ3_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ3(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ3_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ3_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ4_MASK        (0x10U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ4_SHIFT       (4U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ4_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ4(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ4_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ4_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ5_MASK        (0x20U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ5_SHIFT       (5U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ5_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ5(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ5_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ5_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ6_MASK        (0x40U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ6_SHIFT       (6U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ6_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ6(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ6_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ6_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ7_MASK        (0x80U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ7_SHIFT       (7U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ7_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ7(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ7_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ7_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ8_MASK        (0x100U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ8_SHIFT       (8U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ8_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ8(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ8_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ8_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ9_MASK        (0x200U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ9_SHIFT       (9U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ9_WIDTH       (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ9(x)          (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ9_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ9_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ10_MASK       (0x400U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ10_SHIFT      (10U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ10_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ10(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ10_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ10_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ11_MASK       (0x800U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ11_SHIFT      (11U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ11_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ11(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ11_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ11_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ12_MASK       (0x1000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ12_SHIFT      (12U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ12_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ12(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ12_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ12_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ13_MASK       (0x2000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ13_SHIFT      (13U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ13_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ13(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ13_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ13_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ14_MASK       (0x4000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ14_SHIFT      (14U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ14_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ14(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ14_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ14_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ15_MASK       (0x8000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ15_SHIFT      (15U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ15_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ15(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ15_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ15_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ16_MASK       (0x10000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ16_SHIFT      (16U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ16_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ16(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ16_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ16_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ17_MASK       (0x20000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ17_SHIFT      (17U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ17_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ17(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ17_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ17_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ18_MASK       (0x40000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ18_SHIFT      (18U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ18_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ18(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ18_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ18_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ19_MASK       (0x80000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ19_SHIFT      (19U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ19_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ19(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ19_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ19_MASK)

#define MC_ME_PRTN0_COFB0_CLKEN_REQ20_MASK       (0x100000U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ20_SHIFT      (20U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ20_WIDTH      (1U)
#define MC_ME_PRTN0_COFB0_CLKEN_REQ20(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB0_CLKEN_REQ20_SHIFT)) & MC_ME_PRTN0_COFB0_CLKEN_REQ20_MASK)
/*! @} */

/*! @name PRTN0_COFB1_CLKEN - Partition 0 COFB Set 1 Clock Enable Register */
/*! @{ */

#define MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK       (0x1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ32_SHIFT      (0U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ32_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ32(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ32_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK       (0x2U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ33_SHIFT      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ33_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ33(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ33_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK       (0x4U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ34_SHIFT      (2U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ34_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ34(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ34_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK       (0x40U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ38_SHIFT      (6U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ38_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ38(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ38_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK       (0x80U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ39_SHIFT      (7U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ39_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ39(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ39_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK       (0x100U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ40_SHIFT      (8U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ40_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ40(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ40_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK       (0x200U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ41_SHIFT      (9U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ41_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ41(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ41_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK       (0x400U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ42_SHIFT      (10U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ42_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ42(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ42_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ43_MASK       (0x800U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ43_SHIFT      (11U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ43_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ43(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ43_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ43_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK       (0x1000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ44_SHIFT      (12U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ44_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ44(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ44_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK       (0x2000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ45_SHIFT      (13U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ45_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ45(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ45_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ46_MASK       (0x4000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ46_SHIFT      (14U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ46_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ46(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ46_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ46_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ47_MASK       (0x8000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ47_SHIFT      (15U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ47_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ47(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ47_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ47_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ48_MASK       (0x10000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ48_SHIFT      (16U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ48_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ48(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ48_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ48_MASK)

#define MC_ME_PRTN0_COFB1_CLKEN_REQ49_MASK       (0x20000U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ49_SHIFT      (17U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ49_WIDTH      (1U)
#define MC_ME_PRTN0_COFB1_CLKEN_REQ49(x)         (((uint32)(((uint32)(x)) << MC_ME_PRTN0_COFB1_CLKEN_REQ49_SHIFT)) & MC_ME_PRTN0_COFB1_CLKEN_REQ49_MASK)
/*! @} */

#endif

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/**
* @brief            The type Power_Ip_ResetType, represents the different reset that a specified POWER_IP can have.
* @details          The POWER_IP shall provide at least the values MCU_POWER_ON_RESET and MCU_RESET_UNDEFINED for the enumeration Power_Ip_ResetType.
*
* @implements Power_Ip_ResetType_Enumeration
*/
typedef enum
{
    /* 'Destructive' Event Status Register (MC_RGM_DES) */
    MCU_POWER_ON_RESET = McuConf_McuResetReasonConf_MCU_POWER_ON_RESET,                         /**< @brief Power on reset event. RGM_DES[F_DR0]. */
    MCU_FCCU_FTR_RESET = McuConf_McuResetReasonConf_MCU_FCCU_FTR_RESET,                         /**< @brief FCCU failure to react. RGM_DES[F_DR3]. */
    MCU_STCU_URF_RESET = McuConf_McuResetReasonConf_MCU_STCU_URF_RESET,                         /**< @brief STCU unrecoverable fault. RGM_DES[F_DR4]. */
    MCU_MC_RGM_FRE_RESET = McuConf_McuResetReasonConf_MCU_MC_RGM_FRE_RESET,                     /**< @brief Functional reset escalation. RGM_DES[F_DR6]. */
    MCU_FXOSC_FAIL_RESET = McuConf_McuResetReasonConf_MCU_FXOSC_FAIL_RESET,                     /**< @brief FXOSC failure. RGM_DES[F_DR8]. */
    MCU_PLL_LOL_RESET = McuConf_McuResetReasonConf_MCU_PLL_LOL_RESET,                           /**< @brief PLL_LOL and related PLL loss of lock. RGM_DES[F_DR9]. */
    MCU_CORE_CLK_FAIL_RESET = McuConf_McuResetReasonConf_MCU_CORE_CLK_FAIL_RESET,               /**< @brief CORE_CLK_FAIL and related Core clock failure. RGM_DES[F_DR10]. */
    MCU_AIPS_PLAT_CLK_FAIL_RESET = McuConf_McuResetReasonConf_MCU_AIPS_PLAT_CLK_FAIL_RESET,     /**< @brief AIPS_PLAT_CLK failure. RGM_DES[F_DR12]. */
    MCU_HSE_CLK_FAIL_RESET = McuConf_McuResetReasonConf_MCU_HSE_CLK_FAIL_RESET,                 /**< @brief HSE_CLK failure. RGM_DES[F_DR14]. */
    MCU_SYS_DIV_FAIL_RESET = McuConf_McuResetReasonConf_MCU_SYS_DIV_FAIL_RESET,                 /**< @brief System clock dividers alignment failure. RGM_DES[F_DR15]. */
    MCU_CM7_CORE_CLK_FAIL_RESET = McuConf_McuResetReasonConf_MCU_CM7_CORE_CLK_FAIL_RESET,       /**< @brief CM7_CORE_CLK Failure. RGM_DES[F_DR16]. */
    MCU_HSE_TMPR_RST_RESET = McuConf_McuResetReasonConf_MCU_HSE_TMPR_RST_RESET,                 /**< @brief HSE_B tamper detect reset. RGM_DES[F_DR17]. */
    MCU_HSE_SNVS_RST_RESET = McuConf_McuResetReasonConf_MCU_HSE_SNVS_RST_RESET,                 /**< @brief HSE_B SNVS tamper detection. RGM_DES[F_DR18]. */
    MCU_SW_DEST_RESET = McuConf_McuResetReasonConf_MCU_SW_DEST_RESET,                           /**< @brief Software destructive reset. RGM_DES[F_DR29]. */
    MCU_DEBUG_DEST_RESET = McuConf_McuResetReasonConf_MCU_DEBUG_DEST_RESET,                     /**< @brief Debug destructive reset. RGM_DES[F_DR30]. */

    /* 'Functional' Event Status Register (MC_RGM_FES) */
    MCU_F_EXR_RESET = McuConf_McuResetReasonConf_MCU_F_EXR_RESET,                               /**< @brief External reset. RGM_FES[F_FR0]. */
    MCU_FCCU_RST_RESET = McuConf_McuResetReasonConf_MCU_FCCU_RST_RESET,                         /**< @brief FCCU Reset Reaction. RGM_FES[F_FR3]. */
    MCU_ST_DONE_RESET = McuConf_McuResetReasonConf_MCU_ST_DONE_RESET,                           /**< @brief Self-Test Done. RGM_FES[F_FR4]. */
    MCU_SWT0_RST_RESET = McuConf_McuResetReasonConf_MCU_SWT0_RST_RESET,                         /**< @brief SWT0 Timeout. RGM_FES[F_FR6]. */
    MCU_SWT1_RST_RESET = McuConf_McuResetReasonConf_MCU_SWT1_RST_RESET,                         /**< @brief SWT1 Timeout. RGM_FES[F_FR7]. */
    MCU_SWT2_RST_RESET = McuConf_McuResetReasonConf_MCU_SWT2_RST_RESET,                         /**< @brief SWT2 Timeout. RGM_FES[F_FR8]. */
    MCU_JTAG_RST_RESET = McuConf_McuResetReasonConf_MCU_JTAG_RST_RESET,                         /**< @brief JTAG reset. RGM_FES[F_FR9]. */
    MCU_SWT3_RST_RESET = McuConf_McuResetReasonConf_MCU_SWT3_RST_RESET,                         /**< @brief SWT3 Timeout. RGM_FES[F_FR10].*/
    MCU_PLL_AUX_RESET = McuConf_McuResetReasonConf_MCU_PLL_AUX_RESET,                           /**< @brief PLL_AUX_CLK failure. RGM_FES[F_FR12].*/
    MCU_HSE_SWT_RST_RESET = McuConf_McuResetReasonConf_MCU_HSE_SWT_RST_RESET,                   /**< @brief HSE_B SWT timeout. RGM_FES[F_FR16]. */
    MCU_HSE_BOOT_RST_RESET = McuConf_McuResetReasonConf_MCU_HSE_BOOT_RST_RESET,                 /**< @brief HSE_B boot reset. RGM_FES[F_FR20]. */
    MCU_SW_FUNC_RESET = McuConf_McuResetReasonConf_MCU_SW_FUNC_RESET,                           /**< @brief Software functional reset. RGM_FES[F_FR29]. */
    MCU_DEBUG_FUNC_RESET = McuConf_McuResetReasonConf_MCU_DEBUG_FUNC_RESET,                     /**< @brief Debug functional reset. RGM_FES[F_FR30]. */
    
    MCU_WAKEUP_REASON = McuConf_McuResetReasonConf_MCU_WAKEUP_REASON,                           /**< @brief Wake-up event detected. */
    MCU_NO_RESET_REASON = McuConf_McuResetReasonConf_MCU_NO_RESET_REASON,                       /**< @brief No reset reason found */
    MCU_MULTIPLE_RESET_REASON = McuConf_McuResetReasonConf_MCU_MULTIPLE_RESET_REASON,           /**< @brief More than one reset events are logged except "Power on event" */
    MCU_RESET_UNDEFINED = McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED                        /**< @brief Undefined reset source. */

} Power_Ip_ResetType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    volatile uint32 PRTN_CORE_PCONF;                 /**< Partition 0 Core 0 Process Configuration Register, offset: 0x140 */
    volatile uint32 PRTN_CORE_PUPD;                  /**< Partition 0 Core 0 Process Update Register, offset: 0x144 */
    volatile const  uint32 PRTN_CORE_STAT;                  /**< Partition 0 Core 0 Status Register, offset: 0x148 */
    volatile uint32 PRTN_CORE_ADDR;                  /**< Partition 0 Core 0 Address Register, offset: 0x14C */
    uint8 RESERVED[16U];
} Power_Ip_MC_ME_Prtn_Core_Type;

typedef struct {
    volatile uint32 PRTN_PCONF;                                                         /**< Partition 0 Process Configuration Register, offset: 0x100 */
    volatile uint32 PRTN_PUPD;                                                          /**< Partition 0 Process Update Register, offset: 0x104 */
    volatile const  uint32 PRTN_STAT;                                                   /**< Partition 0 Status Register, offset: 0x108 */
#if (defined(POWER_IP_LOCKSTEP_CTRL_SUPPORT) && (POWER_IP_LOCKSTEP_CTRL_SUPPORT == STD_ON))   
    volatile uint32 CORE_LOCKSTEP;                                                      /**< Partition 0 Core LockStep Control Register, reserved for other partitions, offset: 0x10C */
#else
    uint8 RESERVED[4U];
#endif
    volatile const  uint32 PRTN_COFB_STAT[POWER_IP_MC_ME_COFB_COUNT];                   /**< Partition 0 COFB Set 0 Clock Status Register, offset: 0x110 */
    uint8 RESERVED_1[16U];
    volatile uint32 PRTN_COFB_CLKEN[POWER_IP_MC_ME_COFB_COUNT];                         /**< Partition 0 COFB Set 0 Clock Enable Register, offset: 0x130 */
    Power_Ip_MC_ME_Prtn_Core_Type McMePrtnCoreArray[POWER_IP_MC_ME_CORE_COUNT];
    uint8 RESERVED_2[352U];
} Power_Ip_MC_ME_Prtn_Type;

typedef struct{
    volatile uint32 CTL_KEY;                           /**< Control Key Register, offset: 0x0 */
    volatile uint32 MODE_CONF;                         /**< Mode Configuration Register, offset: 0x4 */
    volatile uint32 MODE_UPD;                          /**< Mode Update Register, offset: 0x8 */
    volatile const  uint32 MODE_STAT;                         /**< Mode Status Register, offset: 0xC */
    volatile uint32 MAIN_COREID;                       /**< Main Core ID Register, offset: 0x10 */
    uint8 RESERVED[236U];
    Power_Ip_MC_ME_Prtn_Type McMePrtnArray[POWER_IP_MC_ME_PRTN_COUNT];
} Power_Ip_MC_ME_Type;

/** MC_RGM - Register Layout Typedef */
typedef MC_RGM_Type Power_Ip_MC_RGM_Type;


/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* POWER_IP_SPECIFIC_H */

