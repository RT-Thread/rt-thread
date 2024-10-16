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
/**
*   @file       Clock_Ip_Data.c
*   @version    5.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


#include "Clock_Ip_Private.h"

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_DATA_VENDOR_ID_C                      43
#define CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_DATA_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_DATA_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_DATA_SW_MINOR_VERSION_C               0
#define CLOCK_IP_DATA_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_DATA_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Data.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_DATA_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Data.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_DATA_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_DATA_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_DATA_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Data.c and Clock_Ip_Private.h are different"
#endif

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Clock_Ip_Data.c file and RegLockMacros.h file are of the same Autosar version */
    #if ((CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
        (CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Clock_Ip_Data.c and RegLockMacros.h are different"
    #endif
    #endif
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_PLL                           2U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_FIRCOSC_STDBY                 2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_SIRCOSC_STDBY                 3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_HWMUX_DIV_GATE                8U
#define CLOCK_IP_DIV_TRIGGER_CMU_HSE           9U

#define CLOCK_IP_SCS_EXTENSION                                      0U
#define CLOCK_IP_CLKOUT_RUN_EXTENSION                               1U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION                           2U
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
#define CLOCK_IP_EMAC_RX_EXTENSION                                  3U
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
#define CLOCK_IP_EMAC_TS_EXTENSION                                  4U
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
#define CLOCK_IP_EMAC_TX_EXTENSION                                  5U
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
#define CLOCK_IP_EMAC_TX_RMII_EXTENSION                             6U
#endif
#define CLOCK_IP_FLEXCANA_EXTENSION                                 7U
#define CLOCK_IP_FLEXCANB_EXTENSION                                 8U
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
#define CLOCK_IP_LFAST_REF_EXTENSION                                9U
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
#define CLOCK_IP_QSPI_2XSFIF_EXTENSION                              10U
#elif defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
#define CLOCK_IP_QSPI_SFIF_EXTENSION                                10U
#endif
#define CLOCK_IP_STMA_EXTENSION                                     11U
#if defined(CLOCK_IP_HAS_STMB_CLK)
#define CLOCK_IP_STMB_EXTENSION                                     12U
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
#define CLOCK_IP_STMC_EXTENSION                                     13U
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
#define CLOCK_IP_SWG_EXTENSION                                      14U
#endif
#define CLOCK_IP_TRACE_EXTENSION                                    15U
#define CLOCK_IP_AIPS_PLAT_EXTENSION                                16U
#define CLOCK_IP_AIPS_SLOW_EXTENSION                                17U
#define CLOCK_IP_HSE_EXTENSION                                      18U
#define CLOCK_IP_DCM_EXTENSION                                      19U
#if defined(CLOCK_IP_HAS_LBIST_CLK)
#define CLOCK_IP_LBIST_EXTENSION                                    20U
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
#define CLOCK_IP_USDHC_EXTENSION                                     21U
#endif
#define CLOCK_IP_CORE_EXTENSION                                     22U
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
#define CLOCK_IP_QSPI_MEM_EXTENSION                                 23U
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
#define CLOCK_IP_STMD_EXTENSION                                     24U
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
#define CLOCK_IP_GMAC0_RX_EXTENSION                                 25U
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
#define CLOCK_IP_GMAC0_TX_EXTENSION                                 26U
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
#define CLOCK_IP_GMAC_TS_EXTENSION                                  27U
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
#define CLOCK_IP_GMAC0_TX_RMII_EXTENSION                            28U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
#define CLOCK_IP_GMAC1_RX_EXTENSION                                 29U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
#define CLOCK_IP_GMAC1_TX_EXTENSION                                 30U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
#define CLOCK_IP_GMAC1_MII_RMII_RGMII_TXENSION                               31U
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
#define CLOCK_IP_AES_EXTENSION                                      32U
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
#define CLOCK_IP_CM7_CORE_EXTENSION                                 33U
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
#define CLOCK_IP_GMAC_RX_EXTENSION                                  34U
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
#define CLOCK_IP_GMAC_TX_EXTENSION                                  35U
#endif


#define CLOCK_IP_PRT0_COL1_REQ40_INDEX  0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX  1U
#if defined(CLOCK_IP_HAS_ADC2_CLK)
#define CLOCK_IP_PRT0_COL1_REQ42_INDEX  2U
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
#define CLOCK_IP_PRT0_COL1_REQ43_INDEX  3U
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
#define CLOCK_IP_PRT3_COL1_REQ52_INDEX  4U
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
#define CLOCK_IP_PRT3_COL1_REQ53_INDEX  5U
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
#define CLOCK_IP_PRT3_COL1_REQ54_INDEX  6U
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
#define CLOCK_IP_PRT1_COL0_REQ0_INDEX   7U
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
#define CLOCK_IP_PRT1_COL0_REQ1_INDEX   8U
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
#define CLOCK_IP_PRT1_COL0_REQ2_INDEX   9U
#endif
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX  10U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX  11U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX  12U
#if defined(CLOCK_IP_HAS_CMP2_CLK)
#define CLOCK_IP_PRT2_COL1_REQ58_INDEX  13U
#endif
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX  14U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX  15U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX  16U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX   17U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX   18U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX   19U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX   20U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX   21U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX   22U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX   23U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX  24U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX  25U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX  26U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX  27U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX  28U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX  29U
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX   30U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX   31U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX   32U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX   33U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX   34U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX   35U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX  36U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX  37U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX  38U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX  39U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX  40U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX  41U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX  42U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX  43U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX  44U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX  45U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX  46U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX  47U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX  48U
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX  49U
#endif
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX  50U
#if defined(CLOCK_IP_HAS_EIM0_CLK)
#define CLOCK_IP_PRT2_COL2_REQ67_INDEX  51U
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
#define CLOCK_IP_PRT2_COL2_REQ68_INDEX  52U
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
#define CLOCK_IP_PRT2_COL2_REQ69_INDEX  53U
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX  54U
#endif
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX  55U
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX  56U
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
#define CLOCK_IP_PRT0_COL1_REQ36_INDEX  57U
#endif
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX  58U
#if defined(CLOCK_IP_HAS_ERM1_CLK)
#define CLOCK_IP_PRT0_COL0_REQ3_INDEX   59U
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
#define CLOCK_IP_PRT1_COL3_REQ97_INDEX  60U
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
#define CLOCK_IP_PRT1_COL0_REQ26_INDEX  61U
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
#define CLOCK_IP_PRT1_COL0_REQ27_INDEX  62U
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
#define CLOCK_IP_PRT1_COL1_REQ59_INDEX  63U
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
#define CLOCK_IP_PRT1_COL1_REQ60_INDEX  64U
#endif
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX  65U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX  66U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX  67U
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX  68U
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
#define CLOCK_IP_PRT1_COL2_REQ69_INDEX  69U
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
#define CLOCK_IP_PRT1_COL2_REQ70_INDEX  70U
#endif
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX  71U
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
#define CLOCK_IP_PRT1_COL3_REQ99_INDEX  72U
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
#define CLOCK_IP_PRT2_COL1_REQ59_INDEX  73U
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
#define CLOCK_IP_PRT1_COL3_REQ101_INDEX 74U
#endif
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX  75U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX  76U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX  77U
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX  78U
#endif
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX  79U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX  80U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX  81U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX  82U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX  83U
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
#define CLOCK_IP_PRT2_COL1_REQ47_INDEX  84U
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
#define CLOCK_IP_PRT2_COL1_REQ48_INDEX  85U
#endif
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX  86U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX  87U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX  88U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX  89U
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
#define CLOCK_IP_PRT1_COL2_REQ78_INDEX  90U
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
#define CLOCK_IP_PRT1_COL2_REQ79_INDEX  91U
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
#define CLOCK_IP_PRT1_COL2_REQ80_INDEX  92U
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
#define CLOCK_IP_PRT1_COL2_REQ81_INDEX  93U
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
#define CLOCK_IP_PRT2_COL1_REQ35_INDEX  94U
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
#define CLOCK_IP_PRT2_COL1_REQ36_INDEX  95U
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
#define CLOCK_IP_PRT2_COL1_REQ37_INDEX  96U
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
#define CLOCK_IP_PRT2_COL1_REQ38_INDEX  97U
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
#define CLOCK_IP_PRT2_COL1_REQ39_INDEX  98U
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
#define CLOCK_IP_PRT2_COL1_REQ40_INDEX  99U
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
#define CLOCK_IP_PRT2_COL1_REQ41_INDEX  100U
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
#define CLOCK_IP_PRT2_COL1_REQ42_INDEX  101U
#endif
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX  102U
#if defined(CLOCK_IP_HAS_MU2A_CLK)
#define CLOCK_IP_PRT0_COL1_REQ46_INDEX  103U
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
#define CLOCK_IP_PRT0_COL1_REQ47_INDEX  104U
#endif
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX  105U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX  106U
#if defined(CLOCK_IP_HAS_PIT2_CLK)
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX  107U
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
#define CLOCK_IP_PRT1_COL0_REQ25_INDEX  108U
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
#define CLOCK_IP_PRT2_COL0_REQ25_INDEX  109U
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX  110U
#endif
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX  111U
#if defined(CLOCK_IP_HAS_SAI0_CLK)
#define CLOCK_IP_PRT1_COL2_REQ91_INDEX  112U
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
#define CLOCK_IP_PRT2_COL1_REQ55_INDEX  113U
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX  114U
#endif
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX  115U
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
#define CLOCK_IP_PRT1_COL1_REQ36_INDEX  116U
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
#define CLOCK_IP_PRT1_COL1_REQ37_INDEX  117U
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
#define CLOCK_IP_PRT1_COL1_REQ38_INDEX  118U
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
#define CLOCK_IP_PRT1_COL1_REQ39_INDEX  119U
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
#define CLOCK_IP_PRT1_COL1_REQ40_INDEX  120U
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
#define CLOCK_IP_PRT1_COL1_REQ41_INDEX  121U
#endif
#define CLOCK_IP_PRT1_COL3_REQ104_INDEX 122U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX  123U
#if defined(CLOCK_IP_HAS_STM1_CLK)
#define CLOCK_IP_PRT2_COL0_REQ29_INDEX  124U
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
#define CLOCK_IP_PRT2_COL0_REQ30_INDEX  125U
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
#define CLOCK_IP_PRT3_COL1_REQ50_INDEX  126U
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ51_INDEX  127U
#endif
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX  128U
#if defined(CLOCK_IP_HAS_SWT1_CLK)
#define CLOCK_IP_PRT2_COL0_REQ27_INDEX  129U
#endif
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX  130U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX  131U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX  132U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX  133U
#if defined(CLOCK_IP_HAS_XRDC_CLK)
#define CLOCK_IP_PRT1_COL0_REQ30_INDEX  134U
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
#define CLOCK_IP_PRT2_COL1_REQ57_INDEX  135U
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
#define CLOCK_IP_PRT1_COL2_REQ71_INDEX  136U
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
#define CLOCK_IP_PRT1_COL2_REQ72_INDEX  137U
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
#define CLOCK_IP_PRT2_COL0_REQ28_INDEX  138U
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
#define CLOCK_IP_PRT2_COL1_REQ60_INDEX  139U
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK) || defined(CLOCK_IP_HAS_GMAC0_RX_CLK) || defined(CLOCK_IP_HAS_GMAC0_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_TS_CLK)
#define CLOCK_IP_PRT2_COL1_REQ33_INDEX  140U
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
#define CLOCK_IP_PRT2_COL2_REQ70_INDEX  141U
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
#define CLOCK_IP_PRT2_COL0_REQ31_INDEX  142U
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
#define CLOCK_IP_PRT0_COL0_REQ28_INDEX  143U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK) || defined(CLOCK_IP_HAS_GMAC1_RX_CLK) || defined(CLOCK_IP_HAS_GMAC1_TX_CLK) || defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
#define CLOCK_IP_PRT2_COL1_REQ34_INDEX  144U
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
#define CLOCK_IP_PRT3_COL2_REQ65_INDEX  145U
#endif
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ49_INDEX  146U
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
#define CLOCK_IP_PRT3_COL1_REQ58_INDEX  147U
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ59_INDEX  148U
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
#define CLOCK_IP_PRT3_COL1_REQ55_INDEX  149U
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
#define CLOCK_IP_PRT3_COL1_REQ56_INDEX  150U
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ57_INDEX  151U
#endif
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
#define CLOCK_IP_PRT3_COL1_REQ40_INDEX  152U
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
#define CLOCK_IP_PRT3_COL1_REQ41_INDEX  153U
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
#define CLOCK_IP_PRT2_COL2_REQ66_INDEX  154U
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
#define CLOCK_IP_PRT1_COL0_REQ21_INDEX  155U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
#define CLOCK_IP_PRT0_COL0_REQ4_INDEX  156U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
#define CLOCK_IP_PRT0_COL0_REQ5_INDEX  157U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
#define CLOCK_IP_PRT0_COL0_REQ6_INDEX   158U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
#define CLOCK_IP_PRT0_COL0_REQ7_INDEX   159U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
#define CLOCK_IP_PRT0_COL0_REQ8_INDEX   160U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
#define CLOCK_IP_PRT0_COL0_REQ9_INDEX   161U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
#define CLOCK_IP_PRT0_COL0_REQ10_INDEX   162U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
#define CLOCK_IP_PRT0_COL0_REQ11_INDEX   163U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
#define CLOCK_IP_PRT0_COL0_REQ12_INDEX  164U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
#define CLOCK_IP_PRT0_COL0_REQ13_INDEX  165U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
#define CLOCK_IP_PRT0_COL0_REQ14_INDEX  166U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
#define CLOCK_IP_PRT0_COL0_REQ15_INDEX  167U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
#define CLOCK_IP_PRT0_COL0_REQ16_INDEX  168U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
#define CLOCK_IP_PRT0_COL0_REQ17_INDEX  169U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
#define CLOCK_IP_PRT0_COL0_REQ18_INDEX  170U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
#define CLOCK_IP_PRT0_COL0_REQ19_INDEX  171U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
#define CLOCK_IP_PRT0_COL0_REQ20_INDEX  172U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
#define CLOCK_IP_PRT3_COL0_REQ0_INDEX  173U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
#define CLOCK_IP_PRT3_COL0_REQ1_INDEX  174U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
#define CLOCK_IP_PRT3_COL0_REQ2_INDEX   175U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
#define CLOCK_IP_PRT3_COL0_REQ3_INDEX   176U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
#define CLOCK_IP_PRT3_COL0_REQ4_INDEX   177U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
#define CLOCK_IP_PRT3_COL0_REQ5_INDEX   178U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
#define CLOCK_IP_PRT3_COL0_REQ6_INDEX   179U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
#define CLOCK_IP_PRT3_COL0_REQ7_INDEX   180U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
#define CLOCK_IP_PRT3_COL0_REQ8_INDEX   181U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
#define CLOCK_IP_PRT3_COL0_REQ9_INDEX   182U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
#define CLOCK_IP_PRT3_COL0_REQ10_INDEX   183U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
#define CLOCK_IP_PRT3_COL0_REQ11_INDEX   184U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
#define CLOCK_IP_PRT3_COL0_REQ12_INDEX  185U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
#define CLOCK_IP_PRT3_COL0_REQ13_INDEX  186U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
#define CLOCK_IP_PRT3_COL0_REQ14_INDEX  187U
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
#define CLOCK_IP_PRT3_COL0_REQ15_INDEX  188U
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
#define CLOCK_IP_PRT3_COL1_REQ46_INDEX  189U
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ47_INDEX  190U
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
#define CLOCK_IP_PRT3_COL1_REQ32_INDEX  191U
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ36_INDEX  192U
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
#define CLOCK_IP_PRT3_COL1_REQ37_INDEX  193U
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
#define CLOCK_IP_PRT3_COL1_REQ35_INDEX  194U
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
#define CLOCK_IP_PRT3_COL1_REQ34_INDEX  195U
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
#define CLOCK_IP_PRT3_COL1_REQ44_INDEX  196U
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
#define CLOCK_IP_PRT2_COL2_REQ65_INDEX  197U
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
#define CLOCK_IP_PRT3_COL1_REQ61_INDEX  198U
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ62_INDEX  199U
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
#define CLOCK_IP_PRT3_COL1_REQ63_INDEX  200U
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
#define CLOCK_IP_PRT3_COL2_REQ64_INDEX  201U
#endif
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
#define CLOCK_IP_PRT3_COL1_REQ48_INDEX  202U
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
#define CLOCK_IP_PRT1_COL2_REQ64_INDEX  203U
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
#define CLOCK_IP_PRT1_COL3_REQ112_INDEX  204U
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
#define CLOCK_IP_PRT1_COL3_REQ116_INDEX  205U
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
#define CLOCK_IP_PRT1_COL3_REQ120_INDEX  206U
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
#define CLOCK_IP_PRT1_COL3_REQ124_INDEX  207U
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
#define CLOCK_IP_PRT2_COL2_REQ72_INDEX  208U
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
#define CLOCK_IP_PRT2_COL2_REQ76_INDEX  209U
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
#define CLOCK_IP_PRT2_COL2_REQ80_INDEX  210U
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
#define CLOCK_IP_PRT2_COL2_REQ84_INDEX  211U
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
#define CLOCK_IP_PRT2_COL2_REQ88_INDEX  212U
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
#define CLOCK_IP_PRT0_COL1_REQ49_INDEX  213U
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
#define CLOCK_IP_PRT0_COL1_REQ50_INDEX  214U
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
#define CLOCK_IP_PRT0_COL1_REQ51_INDEX  215U
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
#define CLOCK_IP_PRT0_COL1_REQ52_INDEX  216U
#endif



#define CLOCK_IP_FXOSC_INSTANCE                             0U
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
#define CLOCK_IP_SXOSC_INSTANCE                             1U
#endif

#define CLOCK_IP_PLL_INSTANCE                               0U
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
#define CLOCK_IP_PLLAUX_INSTANCE                            1U
#endif


#define CLOCK_IP_CGM_0_INSTANCE                             0U

#define CLOCK_IP_CMU_0_INSTANCE                             0U
#define CLOCK_IP_CMU_3_INSTANCE                             3U
#define CLOCK_IP_CMU_4_INSTANCE                             4U
#define CLOCK_IP_CMU_5_INSTANCE                             5U
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
#define CLOCK_IP_CMU_6_INSTANCE                             6U
#endif

#define CLOCK_IP_DIV_0_INDEX                             0U
#define CLOCK_IP_DIV_1_INDEX                             1U
#define CLOCK_IP_DIV_2_INDEX                             2U
#define CLOCK_IP_DIV_3_INDEX                             3U
#define CLOCK_IP_DIV_4_INDEX                             4U
#if defined(CLOCK_IP_HAS_LBIST_CLK)
#define CLOCK_IP_DIV_5_INDEX                             5U
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
#define CLOCK_IP_DIV_6_INDEX                             6U
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
#define CLOCK_IP_DIV_7_INDEX                             7U
#endif

#define CLOCK_IP_PCFS_7_INDEX                             7U

#define CLOCK_IP_PARTITION_0_INDEX                             0U
#define CLOCK_IP_PARTITION_1_INDEX                             1U
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
#define CLOCK_IP_PARTITION_2_INDEX                             2U
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
#define CLOCK_IP_PARTITION_3_INDEX                             3U
#endif

#define CLOCK_IP_COLLECTION_0_INDEX                             0U
#define CLOCK_IP_COLLECTION_1_INDEX                             1U
#define CLOCK_IP_COLLECTION_2_INDEX                             2U
#define CLOCK_IP_COLLECTION_3_INDEX                             3U

#define CLOCK_IP_SEL_0_INDEX                             0U
#define CLOCK_IP_SEL_1_INDEX                             1U
#if defined(CLOCK_IP_HAS_STMB_CLK)
#define CLOCK_IP_SEL_2_INDEX                             2U
#endif
#define CLOCK_IP_SEL_3_INDEX                             3U
#define CLOCK_IP_SEL_4_INDEX                             4U
#define CLOCK_IP_SEL_5_INDEX                             5U
#define CLOCK_IP_SEL_6_INDEX                             6U
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK) || defined(CLOCK_IP_HAS_GMAC0_RX_CLK) || defined(CLOCK_IP_HAS_GMAC_RX_CLK)
#define CLOCK_IP_SEL_7_INDEX                             7U
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK) || defined(CLOCK_IP_HAS_GMAC0_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_TX_CLK)
#define CLOCK_IP_SEL_8_INDEX                             8U
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK) || defined(CLOCK_IP_HAS_GMAC_TS_CLK)
#define CLOCK_IP_SEL_9_INDEX                             9U
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
#define CLOCK_IP_SEL_10_INDEX                            10U
#endif
#define CLOCK_IP_SEL_11_INDEX                            11U
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK) || defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
#define CLOCK_IP_SEL_12_INDEX                            12U
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
#define CLOCK_IP_SEL_13_INDEX                            13U
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
#define CLOCK_IP_SEL_14_INDEX                            14U
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK) || defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
#define CLOCK_IP_SEL_15_INDEX                            15U
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK) || defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
#define CLOCK_IP_SEL_16_INDEX                            16U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
#define CLOCK_IP_SEL_17_INDEX                            17U
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
#define CLOCK_IP_SEL_18_INDEX                            18U
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
#define CLOCK_IP_SEL_19_INDEX                            19U
#endif

#define PRTN0_COFB0_STAT_ADDRESS     (uint32)(IP_MC_ME_BASE + 0x110U)
#define PRTN0_COFB0_CLKEN_ADDRESS    (uint32)(IP_MC_ME_BASE + 0x130U)

#define CLOCK_IP_PLL_DIVIDER_COUNT         2U
#if defined(CLOCK_IP_DERIVATIVE_008)
  #define CLOCK_IP_PLLAUX_DIVIDER_COUNT      2U
#else
  #define CLOCK_IP_PLLAUX_DIVIDER_COUNT      3U
#endif
/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_8
#include "Mcu_MemMap.h"

const uint8 Clock_Ip_au8DividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_SWMUX_DIV */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_HWMUX_DIV */
    CLOCK_IP_PLL_PLLDV_ODIV2_OUTPUT,                            /* CLOCK_IP_PLL_POSTDIV */
    CLOCK_IP_PLL_PLL0DIV_DE_DIV_OUTPUT,                         /* CLOCK_IP_PCFS_PLL_OUT */
    CLOCK_IP_PLL_PLL0DIV_DE_DIV_OUTPUT,                         /* CLOCK_IP_PLL_OUT */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_DIV_TRIGGER_CMU */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_DIV_TRIGGER */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_HWMUX_DIV_GATE */
#if defined(CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WAIT_FOR_HSE_CORE)
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WAIT_FOR_HSE_CORE, /* CLOCK_IP_DIV_TRIGGER_CMU_HSE */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
};
const uint8 Clock_Ip_au8DividerTriggerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* CLOCK_IP_DIV_TRIGGER_CMU */
    CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* CLOCK_IP_DIV_TRIGGER */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#if defined(CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT)
    CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* CLOCK_IP_DIV_TRIGGER_CMU_HSE */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
};
const uint8 Clock_Ip_au8XoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL,                       /* CLOCK_IP_FAST_XOSC_CMU */
#if defined(CLOCK_IP_SXOSC_OSCON_EOCV)
    CLOCK_IP_SXOSC_OSCON_EOCV,                                  /* CLOCK_IP_SLOW_XOSC */
#elif defined(CLOCK_IP_SXOSC_OSCON_EOCV_CURR_PRG_SF_CURR_PRG_COMP_GM_SEL)
    CLOCK_IP_SXOSC_OSCON_EOCV_CURR_PRG_SF_CURR_PRG_COMP_GM_SEL, /* CLOCK_IP_SXOSC_OSCON_EOCV_CURR_PRG_SF_CURR_PRG_COMP_GM_SEL */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8IrcoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#if defined(CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR)
    CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR,                  /* CLOCK_IP_FIRCOSC */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
    CLOCK_IP_FIRC_STDBY_ENABLE,                                 /* CLOCK_IP_FIRCOSC_STDBY */
    CLOCK_IP_SIRC_STDBY_ENABLE,                                 /* CLOCK_IP_SIRCOSC_STDBY */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8GateCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST,               /* CLOCK_IP_GATE */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST,               /* CLOCK_IP_HWMUX_DIV_GATE */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8FractionalDividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8PllCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE,/* CLOCK_IP_PLL_MOD */
#if defined(CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN)
    CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN,                      /* CLOCK_IP_PLL */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8SelectorCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_CSC_CSS_CS_GRIP,                             /* CLOCK_IP_SWMUX_DIV */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP,         /* CLOCK_IP_HWMUX_PCFS */
    CLOCK_IP_RTC_RTCC_CLKSELECT,                                /* CLOCK_IP_RTC_SEL */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV_GATE */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8PcfsCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* CLOCK_IP_PCFS_PLL_OUT */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8CmuCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_FAST_XOSC_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_DIV_TRIGGER_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#if defined(CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF)
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_DIV_TRIGGER_CMU_HSE */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
};




/* Clock features mapping */
const uint8 Clock_Ip_au8ClockFeatures[CLOCK_IP_NAMES_NO][CLOCK_IP_FEATURES_NO] =
/*
***************************************************************************************************************************************************************************************************************************************************************
***********************************     ***********************       ***********************   E   ***************************       *       ****************       *****************       **********************       *****************       *************
***********************************  I  ***********************   C   ***********************   X   ***************************       *   S   ****************   D   *****************       **********************       *****************       *************
***********************************  N  ***********************   A   ***********************   T   ***************************   P   *   E   ****************   I   *****************   G   **********************   P   *****************       *************
***********************************  S  ***********************   L   ***********************   E   ***************************   O   *   L   ****************   V   *****************   A   **********************   C   *****************   C   *************
***********************************  T  ***********************   L   ***********************   N   ***************************   W   *   E   ****************   I   *****************   T   **********************   F   *****************   M   *************
***********************************  A  ***********************   B   ***********************   S   ***************************   E   *   C   ****************   D   *****************   E   **********************   S   *****************   U   *************
***********************************  N  ***********************   A   ***********************   I   ***************************   R   *   T   ****************   E   *****************       **********************       *****************       *************
***********************************  C  ***********************   C   ***********************   O   ***************************       *   O   ****************   R   *****************       **********************       *****************       *************
***********************************  E  ***********************   K   ***********************   N   ***************************       *   R   ****************       *****************       **********************       *****************       *************
***********************************     ***********************       ***********************       ***************************       *       ****************       *****************       **********************       *****************       *************
******************************************************************************************************************************************************************************************************************************************************************/
{
/*   CLOCK_IS_OFF clock         */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   CLOCK_IS_OFF clock         */
/*   FIRC_CLK clock             */ {0U,                          CLOCK_IP_FIRCOSC,             0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   FIRC_CLK clock             */
/*   FIRC_STANDBY_CLK clock     */ {0U,                          CLOCK_IP_FIRCOSC_STDBY,       0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   FIRC_STANDBY_CLK clock     */
/*   SIRC_CLK clock             */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   SIRC_CLK clock             */
/*   SIRC_STANDBY_CLK clock     */ {0U,                          CLOCK_IP_SIRCOSC_STDBY,       0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   SIRC_STANDBY_CLK clock     */
/*   FXOSC_CLK clock            */ {CLOCK_IP_FXOSC_INSTANCE,     CLOCK_IP_FAST_XOSC_CMU,       0U,                               0U,    0U,                     0U,                     0U,                           0U,                     CLOCK_IP_CMU_0_INSTANCE},    /*   FXOSC_CLK clock            */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
/*   SXOSC_CLK clock            */ {CLOCK_IP_SXOSC_INSTANCE,     CLOCK_IP_SLOW_XOSC,           0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   SXOSC_CLK clock            */
#endif
/*   PLL_CLK clock              */ {CLOCK_IP_PLL_INSTANCE,       CLOCK_IP_PLL_MOD,             0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   PLL_CLK clock              */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
/*   PLLAUX_CLK clock           */ {CLOCK_IP_PLLAUX_INSTANCE,    CLOCK_IP_PLL,                 0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   PLLAUX_CLK clock           */
#endif
/*   PLL_POSTDIV_CLK clock      */ {CLOCK_IP_PLL_INSTANCE,       CLOCK_IP_PLL_POSTDIV,         0U,                               0U,    0U,                     CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   PLL_POSTDIV_CLK clock      */
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
/*   PLLAUX_POSTDIV_CLK clock   */ {CLOCK_IP_PLLAUX_INSTANCE,    CLOCK_IP_PLL_POSTDIV,         0U,                               0U,    0U,                     CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   PLLAUX_POSTDIV_CLK clock   */
#endif
/*   PLL_PHI0_CLK clock         */ {CLOCK_IP_PLL_INSTANCE,       CLOCK_IP_PCFS_PLL_OUT,        0U,                               0U,    0U,                     CLOCK_IP_DIV_0_INDEX,   0U,                           CLOCK_IP_PCFS_7_INDEX,  0U},                         /*   PLL_PHI0_CLK clock         */
/*   PLL_PHI1_CLK clock         */ {CLOCK_IP_PLL_INSTANCE,       CLOCK_IP_PLL_OUT,             0U,                               0U,    0U,                     CLOCK_IP_DIV_1_INDEX,   0U,                           0U,                     0U},                         /*   PLL_PHI1_CLK clock         */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
/*   PLLAUX_PHI0_CLK clock      */ {CLOCK_IP_PLLAUX_INSTANCE,    CLOCK_IP_PLL_OUT,             0U,                               0U,    0U,                     CLOCK_IP_DIV_0_INDEX,   0U,                           0U,  0U},                         /*   PLLAUX_PHI0_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
/*   PLLAUX_PHI1_CLK clock      */ {CLOCK_IP_PLLAUX_INSTANCE,    CLOCK_IP_PLL_OUT,             0U,                               0U,    0U,                     CLOCK_IP_DIV_1_INDEX,   0U,                           0U,                     0U},                         /*   PLLAUX_PHI1_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
/*   PLLAUX_PHI2_CLK clock      */ {CLOCK_IP_PLLAUX_INSTANCE,    CLOCK_IP_PLL_OUT,             0U,                               0U,    0U,                     CLOCK_IP_DIV_2_INDEX,   0U,                           0U,                     0U},                         /*   PLLAUX_PHI2_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
/*   EMAC_MII_RX_CLK clock      */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   EMAC_MII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
/*   EMAC_MII_RMII_TX_CLK clock */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   EMAC_MII_RMII_TX_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
/*   GMAC_MII_RGMII_RX_CLK clock      */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   GMAC_MII_RGMII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
/*   GMAC_MII_RMII_RGMII_TX_CLK clock */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   GMAC_MII_RMII_RGMII_TX_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
/*   GMAC0_MII_RGMII_RX_CLK clock     */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   GMAC0_MII_RGMII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
/*   GMAC0_MII_RMII_RGMII_TX_CLK clock */{0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   GMAC0_MII_RMII_RGMII_TX_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
/*   GMAC1_MII_RGMII_RX_CLK clock     */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   GMAC1_MII_RGMII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
/*   GMAC1_MII_RMII_RGMII_TX_CLK clock   */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   GMAC1_MII_RMII_RGMII_TX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
/*   LFAST_EXT_REF_CLK clock    */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   LFAST_EXT_REF_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
/*   SWG_PAD_CLK clock          */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   SWG_PAD_CLK clock          */
#endif
/*   SCS_CLK clock              */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_PCFS,          CLOCK_IP_SCS_EXTENSION,           0U,    CLOCK_IP_SEL_0_INDEX,   0U,                     0U,                           0U,                     0U},                         /*   SCS_CLK clock              */
/*   CORE_CLK clock             */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER_CMU,     CLOCK_IP_CORE_EXTENSION,          0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     CLOCK_IP_CMU_3_INSTANCE},    /*   CORE_CLK clock             */
/*   AIPS_PLAT_CLK clock        */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER_CMU,     CLOCK_IP_AIPS_PLAT_EXTENSION,     0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_1_INDEX,   0U,                           0U,                     CLOCK_IP_CMU_4_INSTANCE},    /*   AIPS_PLAT_CLK clock        */
/*   AIPS_SLOW_CLK clock        */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER,         CLOCK_IP_AIPS_SLOW_EXTENSION,     0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_2_INDEX,   0U,                           0U,                     0U},                         /*   AIPS_SLOW_CLK clock        */
#if defined(CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WAIT_FOR_HSE_CORE)
/*   HSE_CLK clock              */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER_CMU_HSE,     CLOCK_IP_HSE_EXTENSION,           0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_3_INDEX,   0U,                           0U,                     CLOCK_IP_CMU_5_INSTANCE},    /*   HSE_CLK clock              */
#else
/*   HSE_CLK clock              */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER_CMU,     CLOCK_IP_HSE_EXTENSION,           0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_3_INDEX,   0U,                           0U,                     CLOCK_IP_CMU_5_INSTANCE},    /*   HSE_CLK clock              */
#endif
/*   DCM_CLK clock              */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER,         CLOCK_IP_DCM_EXTENSION,           0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_4_INDEX,   0U,                           0U,                     0U},                         /*   DCM_CLK clock              */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
/*   LBIST_CLK clock            */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER,         CLOCK_IP_LBIST_EXTENSION,         0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_5_INDEX,   0U,                           0U,                     0U},                         /*   LBIST_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
/*   QSPI_MEM_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER,         CLOCK_IP_QSPI_MEM_EXTENSION,      0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_6_INDEX,   0U,                           0U,                     0U},                         /*   QSPI_MEM_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/*   CM7_CORE_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_DIV_TRIGGER_CMU,     CLOCK_IP_CM7_CORE_EXTENSION,      0U,    CLOCK_IP_SEL_0_INDEX,   CLOCK_IP_DIV_7_INDEX,   0U,                           0U,                     CLOCK_IP_CMU_6_INSTANCE},    /*   CM7_CORE_CLK clock         */
#endif
/*   CLKOUT_RUN_CLK clock       */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_SWMUX_DIV,           CLOCK_IP_CLKOUT_RUN_EXTENSION,    0U,    CLOCK_IP_SEL_6_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   CLKOUT_RUN_CLK clock       */
/*   THE_LAST_PRODUCER_CLK      */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   THE_LAST_PRODUCER_CLK      */
/*   ADC0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ40_INDEX,0U,                    0U},                         /*   ADC0_CLK clock             */
/*   ADC1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ41_INDEX,0U,                    0U},                         /*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
/*   ADC2_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ42_INDEX,0U,                    0U},                         /*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
/*   ADC3_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ43_INDEX,0U,                    0U},                         /*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
/*   ADC4_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ52_INDEX,0U,                    0U},                         /*   ADC4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
/*   ADC5_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ53_INDEX,0U,                    0U},                         /*   ADC5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
/*   ADC6_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ54_INDEX,0U,                    0U},                         /*   ADC6_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
/*   ADCBIST_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL2_REQ65_INDEX,0U,                    0U},                         /*   ADCBIST_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
/*   AES_ACCEL_CLK clock          */ {0U,                        CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ112_INDEX,0U,                    0U},                         /*   AES_ACCEL_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
/*   AES_APP0_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ116_INDEX,0U,                    0U},                         /*   AES_APP0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
/*   AES_APP1_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ120_INDEX,0U,                    0U},                         /*   AES_APP1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
/*   AES_APP2_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ124_INDEX,0U,                    0U},                         /*   AES_APP2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
/*   AES_APP3_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ72_INDEX,0U,                    0U},                         /*   AES_APP3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
/*   AES_APP4_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ76_INDEX,0U,                    0U},                         /*   AES_APP4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
/*   AES_APP5_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ80_INDEX,0U,                    0U},                         /*   AES_APP5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
/*   AES_APP6_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ84_INDEX,0U,                    0U},                         /*   AES_APP6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
/*   AES_APP7_CLK clock          */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ88_INDEX,0U,                    0U},                         /*   AES_APP7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
/*   AES_CLK clock              */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_AES_EXTENSION,           0U,    CLOCK_IP_SEL_19_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   AES_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
/*   AXBS_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ0_INDEX,0U,                     0U},                         /*   AXBS_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
/*   AXBS0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ1_INDEX,0U,                     0U},                         /*   AXBS0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
/*   AXBS1_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ2_INDEX,0U,                     0U},                         /*   AXBS1_CLK clock            */
#endif
/*   BCTU0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ33_INDEX,0U,                    0U},                         /*   BCTU0_CLK clock            */
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
/*   BCTU1_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ49_INDEX,0U,                    0U},                         /*   BCTU1_CLK clock            */
#endif
/*   CLKOUT_STANDBY_CLK clock   */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_SWMUX_DIV,           CLOCK_IP_CLKOUT_STANDBY_EXTENSION,0U,    CLOCK_IP_SEL_5_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   CLKOUT_STANDBY_CLK clock   */
/*   CMP0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ92_INDEX,0U,                    0U},                         /*   CMP0_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP1_CLK)
/*   CMP1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ93_INDEX,0U,                    0U},                         /*   CMP1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
/*   CMP2_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ58_INDEX,0U,                    0U},                         /*   CMP2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
/*   COOLFLUX_D_RAM0_CLK clock  */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ58_INDEX,0U,                    0U},                         /*   COOLFLUX_D_RAM0_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
/*   COOLFLUX_D_RAM1_CLK clock  */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ59_INDEX,0U,                    0U},                         /*   COOLFLUX_D_RAM1_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
/*   COOLFLUX_DSP16L_CLK clock  */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ55_INDEX,0U,                    0U},                         /*   COOLFLUX_DSP16L_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
/*   COOLFLUX_I_RAM0_CLK clock  */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ56_INDEX,0U,                    0U},                         /*   COOLFLUX_I_RAM0_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
/*   COOLFLUX_I_RAM1_CLK clock  */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ57_INDEX,0U,                    0U},                         /*   COOLFLUX_I_RAM1_CLK clock              */
#endif
/*   CRC0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ96_INDEX,0U,                    0U},                         /*   CRC0_CLK clock             */
/*   DCM0_CLK clock             */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   DCM0_CLK clock             */
/*   DMAMUX0_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ32_INDEX,0U,                    0U},                         /*   DMAMUX0_CLK clock          */
/*   DMAMUX1_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ33_INDEX,0U,                    0U},                         /*   DMAMUX1_CLK clock          */
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
/*   DMAMUX2_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ40_INDEX,0U,                    0U},                         /*   DMAMUX2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
/*   DMAMUX3_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ41_INDEX,0U,                    0U},                         /*   DMAMUX3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
/*   DSPI_MSC_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ66_INDEX,0U,                    0U},                         /*   DSPI_MSC_CLK clock         */
#endif
/*   EDMA0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ3_INDEX,0U,                     0U},                         /*   EDMA0_CLK clock            */
/*   EDMA0_TCD0_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ4_INDEX,0U,                     0U},                         /*   EDMA0_TCD0_CLK clock       */
/*   EDMA0_TCD1_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ5_INDEX,0U,                     0U},                         /*   EDMA0_TCD1_CLK clock       */
/*   EDMA0_TCD2_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ6_INDEX,0U,                     0U},                         /*   EDMA0_TCD2_CLK clock       */
/*   EDMA0_TCD3_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ7_INDEX,0U,                     0U},                         /*   EDMA0_TCD3_CLK clock       */
/*   EDMA0_TCD4_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ8_INDEX,0U,                     0U},                         /*   EDMA0_TCD4_CLK clock       */
/*   EDMA0_TCD5_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ9_INDEX,0U,                     0U},                         /*   EDMA0_TCD5_CLK clock       */
/*   EDMA0_TCD6_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ10_INDEX,0U,                    0U},                         /*   EDMA0_TCD6_CLK clock       */
/*   EDMA0_TCD7_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ11_INDEX,0U,                    0U},                         /*   EDMA0_TCD7_CLK clock       */
/*   EDMA0_TCD8_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ12_INDEX,0U,                    0U},                         /*   EDMA0_TCD8_CLK clock       */
/*   EDMA0_TCD9_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ13_INDEX,0U,                    0U},                         /*   EDMA0_TCD9_CLK clock       */
/*   EDMA0_TCD10_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ14_INDEX,0U,                    0U},                         /*   EDMA0_TCD10_CLK clock      */
/*   EDMA0_TCD11_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ15_INDEX,0U,                    0U},                         /*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
/*   EDMA0_TCD12_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ4_INDEX,0U,                     0U},                         /*   EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
/*   EDMA0_TCD13_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ5_INDEX,0U,                     0U},                         /*   EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
/*   EDMA0_TCD14_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ6_INDEX,0U,                     0U},                         /*   EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
/*   EDMA0_TCD15_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ7_INDEX,0U,                     0U},                         /*   EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
/*   EDMA0_TCD16_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ8_INDEX,0U,                     0U},                         /*   EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
/*   EDMA0_TCD17_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ9_INDEX,0U,                     0U},                         /*   EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
/*   EDMA0_TCD18_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ10_INDEX,0U,                    0U},                         /*   EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
/*   EDMA0_TCD19_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ11_INDEX,0U,                    0U},                         /*   EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
/*   EDMA0_TCD20_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ12_INDEX,0U,                    0U},                         /*   EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
/*   EDMA0_TCD21_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ13_INDEX,0U,                    0U},                         /*   EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
/*   EDMA0_TCD22_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ14_INDEX,0U,                    0U},                         /*   EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
/*   EDMA0_TCD23_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ15_INDEX,0U,                    0U},                         /*   EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
/*   EDMA0_TCD24_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ16_INDEX,0U,                    0U},                         /*   EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
/*   EDMA0_TCD25_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ17_INDEX,0U,                    0U},                         /*   EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
/*   EDMA0_TCD26_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ18_INDEX,0U,                    0U},                         /*   EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
/*   EDMA0_TCD27_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ19_INDEX,0U,                    0U},                         /*   EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
/*   EDMA0_TCD28_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ20_INDEX,0U,                    0U},                         /*   EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
/*   EDMA0_TCD29_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ21_INDEX,0U,                    0U},                         /*   EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
/*   EDMA0_TCD30_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ22_INDEX,0U,                    0U},                         /*   EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
/*   EDMA0_TCD31_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ23_INDEX,0U,                    0U},                         /*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
/*   EDMA1_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ4_INDEX, 0U,                    0U},                         /*   EDMA1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
/*   EDMA1_TCD0_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ5_INDEX,0U,                     0U},                         /*   EDMA1_TCD0_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
/*   EDMA1_TCD1_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ6_INDEX,0U,                     0U},                         /*   EDMA1_TCD1_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
/*   EDMA1_TCD2_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ7_INDEX,0U,                     0U},                         /*   EDMA1_TCD2_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
/*   EDMA1_TCD3_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ8_INDEX,0U,                     0U},                         /*   EDMA1_TCD3_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
/*   EDMA1_TCD4_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ9_INDEX,0U,                     0U},                         /*   EDMA1_TCD4_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
/*   EDMA1_TCD5_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ10_INDEX,0U,                    0U},                         /*   EDMA1_TCD5_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
/*   EDMA1_TCD6_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ11_INDEX,0U,                    0U},                         /*   EDMA1_TCD6_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
/*   EDMA1_TCD7_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ12_INDEX,0U,                    0U},                         /*   EDMA1_TCD7_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
/*   EDMA1_TCD8_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ13_INDEX,0U,                    0U},                         /*   EDMA1_TCD8_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
/*   EDMA1_TCD9_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ14_INDEX,0U,                    0U},                         /*   EDMA1_TCD9_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
/*   EDMA1_TCD10_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ15_INDEX,0U,                    0U},                         /*   EDMA1_TCD10_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
/*   EDMA1_TCD11_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ16_INDEX,0U,                    0U},                         /*   EDMA1_TCD11_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
/*   EDMA1_TCD12_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ17_INDEX,0U,                    0U},                         /*   EDMA1_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
/*   EDMA1_TCD13_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ18_INDEX,0U,                    0U},                         /*   EDMA1_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
/*   EDMA1_TCD14_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ19_INDEX,0U,                    0U},                         /*   EDMA1_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
/*   EDMA1_TCD15_CLK clock      */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ20_INDEX,0U,                    0U},                         /*   EDMA1_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
/*   EDMA1_TCD16_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ0_INDEX,0U,                     0U},                         /*   EDMA1_TCD16_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
/*   EDMA1_TCD17_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ1_INDEX,0U,                     0U},                         /*   EDMA1_TCD17_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
/*   EDMA1_TCD18_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ2_INDEX,0U,                     0U},                         /*   EDMA1_TCD18_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
/*   EDMA1_TCD19_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ3_INDEX,0U,                     0U},                         /*   EDMA1_TCD19_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
/*   EDMA1_TCD20_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ4_INDEX,0U,                     0U},                         /*   EDMA1_TCD20_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
/*   EDMA1_TCD21_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ5_INDEX,0U,                     0U},                         /*   EDMA1_TCD21_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
/*   EDMA1_TCD22_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ6_INDEX,0U,                     0U},                         /*   EDMA1_TCD22_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
/*   EDMA1_TCD23_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ7_INDEX,0U,                     0U},                         /*   EDMA1_TCD23_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
/*   EDMA1_TCD24_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ8_INDEX,0U,                     0U},                         /*   EDMA1_TCD24_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
/*   EDMA1_TCD25_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ9_INDEX,0U,                     0U},                         /*   EDMA1_TCD25_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
/*   EDMA1_TCD26_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ10_INDEX,0U,                    0U},                         /*   EDMA1_TCD26_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
/*   EDMA1_TCD27_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ11_INDEX,0U,                    0U},                         /*   EDMA1_TCD27_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
/*   EDMA1_TCD28_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ12_INDEX,0U,                    0U},                         /*   EDMA1_TCD28_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
/*   EDMA1_TCD29_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ13_INDEX,0U,                    0U},                         /*   EDMA1_TCD29_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
/*   EDMA1_TCD30_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ14_INDEX,0U,                    0U},                         /*   EDMA1_TCD30_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
/*   EDMA1_TCD31_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL0_REQ15_INDEX,0U,                    0U},                         /*   EDMA1_TCD31_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
/*   EFLEX_PWM0_CLK clock        */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ46_INDEX,0U,                    0U},                         /*   EFLEX_PWM0_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
/*   EFLEX_PWM1_CLK clock        */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ47_INDEX,0U,                    0U},                         /*   EFLEX_PWM1_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
/*   EIM_CLK clock              */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ22_INDEX,0U,                    0U},                         /*   EIM_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
/*   EIM0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ67_INDEX,0U,                    0U},                         /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
/*   EIM1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ68_INDEX,0U,                    0U},                         /*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
/*   EIM2_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ69_INDEX,0U,                    0U},                         /*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
/*   EIM3_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ70_INDEX,0U,                    0U},                         /*   EIM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
/*   EMAC_RX_CLK clock          */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_EMAC_RX_EXTENSION,       0U,    CLOCK_IP_SEL_7_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   EMAC_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
/*   GMAC_RX_CLK clock          */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_GMAC_RX_EXTENSION,       0U,    CLOCK_IP_SEL_7_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   GMAC_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
/*   EMAC0_RX_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ32_INDEX,0U,                    0U},                         /*   EMAC0_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
/*   EMAC_TS_CLK clock          */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_EMAC_TS_EXTENSION,       0U,    CLOCK_IP_SEL_9_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   EMAC_TS_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
/*   EMAC0_TS_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ32_INDEX,0U,                    0U},                         /*   EMAC0_TS_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
/*   EMAC_TX_CLK clock          */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_EMAC_TX_EXTENSION,       0U,    CLOCK_IP_SEL_8_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   EMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
/*   GMAC_TX_CLK clock          */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_GMAC_TX_EXTENSION,       0U,    CLOCK_IP_SEL_8_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   GMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
/*   EMAC0_TX_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ32_INDEX,0U,                    0U},                         /*   EMAC0_TX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
/*   EMAC_TX_RMII_CLK clock     */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_EMAC_TX_RMII_EXTENSION,  0U,    CLOCK_IP_SEL_12_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   EMAC_TX_RMII_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_RMII_CLK)
/*   EMAC0_TX_RMII_CLK clock    */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    0U,                     0U,                     0U,                           0U,                     0U},                         /*   EMAC0_TX_RMII_CLK clock    */
#endif
/*   EMIOS0_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ34_INDEX,0U,                    0U},                         /*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/*   EMIOS1_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ35_INDEX,0U,                    0U},                         /*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
/*   EMIOS2_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ36_INDEX,0U,                    0U},                         /*   EMIOS2_CLK clock           */
#endif
/*   ERM0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ23_INDEX,0U,                    0U},                         /*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
/*   ERM1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ3_INDEX,0U,                     0U},                         /*   ERM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
/*   ETPU_AB_REGISTERS_CLK clock */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ32_INDEX,0U,                    0U},                         /*   ETPU_AB_REGISTERS_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
/*   ETPU_CODE_RAM1_CLK clock    */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ36_INDEX,0U,                    0U},                         /*   ETPU_CODE_RAM1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
/*   ETPU_CODE_RAM2_CLK clock    */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ37_INDEX,0U,                    0U},                         /*   ETPU_CODE_RAM2_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
/*   ETPU_RAM_MIRROR_CLK clock   */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ35_INDEX,0U,                    0U},                         /*   ETPU_RAM_MIRROR_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
/*   ETPU_RAM_SDM_CLK clock      */ {0U,                         CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ34_INDEX,0U,                    0U},                         /*   ETPU_RAM_SDM_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
/*   FCCU_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ97_INDEX,0U,                    0U},                         /*   FCCU_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
/*   FLASH0_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ26_INDEX,0U,                    0U},                         /*   FLASH0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
/*   FLASH0_ALT_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ27_INDEX,0U,                    0U},                         /*   FLASH0_ALT_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
/*   FLASH1_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ59_INDEX,0U,                    0U},                         /*   FLASH1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
/*   FLASH1_ALT_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ60_INDEX,0U,                    0U},                         /*   FLASH1_ALT_CLK clock       */
#endif
/*   FLEXCANA_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_FLEXCANA_EXTENSION,      0U,    CLOCK_IP_SEL_3_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   FLEXCANA_CLK clock         */
/*   FLEXCAN0_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ65_INDEX,0U,                    0U},                         /*   FLEXCAN0_CLK clock         */
/*   FLEXCAN1_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ66_INDEX,0U,                    0U},                         /*   FLEXCAN1_CLK clock         */
/*   FLEXCAN2_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ67_INDEX,0U,                    0U},                         /*   FLEXCAN2_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
/*   FLEXCANB_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_FLEXCANB_EXTENSION,      0U,    CLOCK_IP_SEL_4_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   FLEXCANB_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
/*   FLEXCAN3_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ68_INDEX,0U,                    0U},                         /*   FLEXCAN3_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
/*   FLEXCAN4_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ69_INDEX,0U,                    0U},                         /*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
/*   FLEXCAN5_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ70_INDEX,0U,                    0U},                         /*   FLEXCAN5_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
/*   FLEXCAN6_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ71_INDEX,0U,                    0U},                         /*   FLEXCAN6_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
/*   FLEXCAN7_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ72_INDEX,0U,                    0U},                         /*   FLEXCAN7_CLK clock         */
#endif
/*   FLEXIO0_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ73_INDEX,0U,                    0U},                         /*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
/*   HSE_MU0_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ99_INDEX,0U,                    0U},                         /*   HSE_MU0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
/*   HSE_MU1_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ59_INDEX,0U,                    0U},                         /*   HSE_MU1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
/*   JDC_CLK clock              */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ101_INDEX,0U,                   0U},                         /*   JDC_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
/*   IGF0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ44_INDEX,0U,                    0U},                         /*   IGF0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
/*   GMAC0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ33_INDEX,0U,                    0U},                         /*   GMAC0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK)
/*   GMAC1_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ34_INDEX,0U,                    0U},                         /*   GMAC1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
/*   GMAC0_RX_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_GMAC0_RX_EXTENSION,      0U,    CLOCK_IP_SEL_7_INDEX,   CLOCK_IP_DIV_0_INDEX,   CLOCK_IP_PRT2_COL1_REQ33_INDEX,0U,                     0U},                         /*   GMAC0_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
/*   GMAC0_TX_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_GMAC0_TX_EXTENSION,      0U,    CLOCK_IP_SEL_8_INDEX,   CLOCK_IP_DIV_0_INDEX,   CLOCK_IP_PRT2_COL1_REQ33_INDEX,0U,                     0U},                         /*   GMAC0_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
/*   GMAC_TS_CLK clock          */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_GMAC_TS_EXTENSION,       0U,    CLOCK_IP_SEL_9_INDEX,   CLOCK_IP_DIV_0_INDEX,   CLOCK_IP_PRT2_COL1_REQ33_INDEX,0U,                     0U},                         /*   GMAC_TS_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
/*   GMAC0_TX_RMII_CLK clock    */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_GMAC0_TX_RMII_EXTENSION, 0U,    CLOCK_IP_SEL_12_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   GMAC0_TX_RMII_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
/*   GMAC1_RX_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_GMAC1_RX_EXTENSION,      0U,    CLOCK_IP_SEL_15_INDEX,  CLOCK_IP_DIV_0_INDEX,   CLOCK_IP_PRT2_COL1_REQ34_INDEX,0U,                     0U},                         /*   GMAC1_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
/*   GMAC1_TX_CLK clock         */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_GMAC1_TX_EXTENSION,      0U,    CLOCK_IP_SEL_16_INDEX,  CLOCK_IP_DIV_0_INDEX,   CLOCK_IP_PRT2_COL1_REQ34_INDEX,0U,                     0U},                         /*   GMAC1_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
/*   GMAC1_RMII_CLK clock       */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_GMAC1_MII_RMII_RGMII_TXENSION,    0U,    CLOCK_IP_SEL_17_INDEX,  CLOCK_IP_DIV_0_INDEX,   CLOCK_IP_PRT2_COL1_REQ34_INDEX,0U,                     0U},                         /*   GMAC1_RMII_CLK clock          */
#endif
/*   INTM_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ31_INDEX,0U,                    0U},                         /*   INTM_CLK clock             */
/*   LCU0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ38_INDEX,0U,                    0U},                         /*   LCU0_CLK clock             */
/*   LCU1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ39_INDEX,0U,                    0U},                         /*   LCU1_CLK clock             */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
/*   LFAST_REF_CLK clock        */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_LFAST_REF_EXTENSION,     0U,    CLOCK_IP_SEL_15_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   LFAST_REF_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
/*   LPI2C0_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ84_INDEX,0U,                    0U},                         /*   LPI2C0_CLK clock           */
#endif
/*   LPI2C1_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ85_INDEX,0U,                    0U},                         /*   LPI2C1_CLK clock           */
/*   LPSPI0_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ86_INDEX,0U,                    0U},                         /*   LPSPI0_CLK clock           */
/*   LPSPI1_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ87_INDEX,0U,                    0U},                         /*   LPSPI1_CLK clock           */
/*   LPSPI2_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ88_INDEX,0U,                    0U},                         /*   LPSPI2_CLK clock           */
/*   LPSPI3_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ89_INDEX,0U,                    0U},                         /*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
/*   LPSPI4_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ47_INDEX,0U,                    0U},                         /*   LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
/*   LPSPI5_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ48_INDEX,0U,                    0U},                         /*   LPSPI5_CLK clock           */
#endif
/*   LPUART0_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ74_INDEX,0U,                    0U},                         /*   LPUART0_CLK clock          */
/*   LPUART1_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ75_INDEX,0U,                    0U},                         /*   LPUART1_CLK clock          */
/*   LPUART2_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ76_INDEX,0U,                    0U},                         /*   LPUART2_CLK clock          */
/*   LPUART3_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ77_INDEX,0U,                    0U},                         /*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
/*   LPUART4_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ78_INDEX,0U,                    0U},                         /*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
/*   LPUART5_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ79_INDEX,0U,                    0U},                         /*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
/*   LPUART6_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ80_INDEX,0U,                    0U},                         /*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
/*   LPUART7_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ81_INDEX,0U,                    0U},                         /*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
/*   LPUART8_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ35_INDEX,0U,                    0U},                         /*   LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
/*   LPUART9_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ36_INDEX,0U,                    0U},                         /*   LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
/*   LPUART10_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ37_INDEX,0U,                    0U},                         /*   LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
/*   LPUART11_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ38_INDEX,0U,                    0U},                         /*   LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
/*   LPUART12_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ39_INDEX,0U,                    0U},                         /*   LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
/*   LPUART13_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ40_INDEX,0U,                    0U},                         /*   LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
/*   LPUART14_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ41_INDEX,0U,                    0U},                         /*   LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
/*   LPUART15_CLK clock         */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ42_INDEX,0U,                    0U},                         /*   LPUART15_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
/*   LPUART_MSC_CLK clock       */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL2_REQ65_INDEX,0U,                    0U},                         /*   LPUART_MSC_CLK clock       */
#endif
/*   MSCM_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ24_INDEX,0U,                    0U},                         /*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MU2A_CLK)
/*   MU2A_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ46_INDEX,0U,                    0U},                         /*   MU2A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
/*   MU2B_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ47_INDEX,0U,                    0U},                         /*   MU2B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
/*   MU3A_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ49_INDEX,0U,                    0U},                         /*   MU3A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
/*   MU3B_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ50_INDEX,0U,                    0U},                         /*   MU3B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
/*   MU4A_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ51_INDEX,0U,                    0U},                         /*   MU4A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
/*   MU4B_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ52_INDEX,0U,                    0U},                         /*   MU4B_CLK clock              */
#endif
/*   PIT0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ44_INDEX,0U,                    0U},                         /*   PIT0_CLK clock             */
/*   PIT1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ45_INDEX,0U,                    0U},                         /*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
/*   PIT2_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ63_INDEX,0U,                    0U},                         /*   PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
/*   PIT3_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ64_INDEX,0U,                    0U},                         /*   PIT3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
/*   PRAMC0_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ25_INDEX,0U,                    0U},                         /*   PRAMC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
/*   PRAMC1_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ25_INDEX,0U,                    0U},                         /*   PRAMC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/*   QSPI_2XSFIF_CLK clock      */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_QSPI_2XSFIF_EXTENSION,   0U,    CLOCK_IP_SEL_10_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   QSPI_2XSFIF_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
/*   QSPI0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ51_INDEX,0U,                    0U},                         /*   QSPI0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
/*   QSPI0_RAM_CLK clock        */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ51_INDEX,0U,                    0U},                         /*   QSPI0_RAM_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
/*   QSPI0_TX_MEM_CLK clock     */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ51_INDEX,0U,                    0U},                         /*   QSPI0_TX_MEM_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK) && defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/*   QSPI_SFCK_CLK clock        */ {0U,                          CLOCK_IP_NO_CALLBACK,         0U,                               0U,    CLOCK_IP_SEL_10_INDEX,  0U,                     0U,                           0U,                     0U},                         /*   QSPI_SFCK_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK) && !defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/*   QSPI_SFCK_CLK clock        */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_QSPI_SFIF_EXTENSION,     0U,    CLOCK_IP_SEL_10_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   QSPI_SFCK_CLK clock        */
#endif
/*   RTC_CLK clock              */ {0U,                          CLOCK_IP_RTC_SEL,             0U,                               0U,    CLOCK_IP_SEL_0_INDEX,   0U,                     0U,                           0U,                     0U},                         /*   RTC_CLK clock              */
/*   RTC0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ34_INDEX,0U,                    0U},                         /*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
/*   SAI0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ91_INDEX,0U,                    0U},                         /*   SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
/*   SAI1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ55_INDEX,0U,                    0U},                         /*   SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
/*   SDA_AP_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ21_INDEX,0U,                    0U},                         /*   SDA_AP_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
/*   SDADC0_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ61_INDEX,0U,                    0U},                         /*   SDADC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
/*   SDADC1_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ62_INDEX,0U,                    0U},                         /*   SDADC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
/*   SDADC2_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ63_INDEX,0U,                    0U},                         /*   SDADC2_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
/*   SDADC3_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL2_REQ64_INDEX,0U,                    0U},                         /*   SDADC3_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
/*   SEMA42_CLK clock           */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ24_INDEX,0U,                    0U},                         /*   SEMA42_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
/*   SIPI0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL1_REQ60_INDEX,0U,                    0U},                         /*   SIPI0_CLK clock             */
#endif
/*   SIUL2_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ42_INDEX,0U,                    0U},                         /*   SIUL2_CLK clock            */
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
/*   SIUL2_PDAC0_0_CLK clock    */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ36_INDEX,0U,                    0U},                         /*   SIUL2_PDAC0_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
/*   SIUL2_PDAC0_1_CLK clock    */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ37_INDEX,0U,                    0U},                         /*   SIUL2_PDAC0_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
/*   SIUL2_PDAC1_0_CLK clock    */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ38_INDEX,0U,                    0U},                         /*   SIUL2_PDAC1_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
/*   SIUL2_PDAC1_1_CLK clock    */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ39_INDEX,0U,                    0U},                         /*   SIUL2_PDAC1_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
/*   SIUL2_PDAC2_0_CLK clock    */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ40_INDEX,0U,                    0U},                         /*   SIUL2_PDAC2_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
/*   SIUL2_PDAC2_1_CLK clock    */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ41_INDEX,0U,                    0U},                         /*   SIUL2_PDAC2_1_CLK clock    */
#endif
/*   STCU0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL3_REQ104_INDEX,0U,                   0U},                         /*   STCU0_CLK clock            */
/*   STMA_CLK clock             */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_STMA_EXTENSION,          0U,    CLOCK_IP_SEL_1_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   STMA_CLK clock             */
/*   STM0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ29_INDEX,0U,                    0U},                         /*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STMB_CLK)
/*   STMB_CLK clock             */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_STMB_EXTENSION,          0U,    CLOCK_IP_SEL_2_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   STMB_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
/*   STM1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ29_INDEX,0U,                    0U},                         /*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
/*   STMC_CLK clock             */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_STMC_EXTENSION,          0U,    CLOCK_IP_SEL_13_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   STMC_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
/*   STM2_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ30_INDEX,0U,                    0U},                         /*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
/*   STMD_CLK clock             */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_STMD_EXTENSION,          0U,    CLOCK_IP_SEL_18_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   STMD_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
/*   STM3_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ31_INDEX,0U,                    0U},                         /*   STM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
/*   SWG_CLK clock              */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV,           CLOCK_IP_SWG_EXTENSION,           0U,    CLOCK_IP_SEL_16_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                           0U,                     0U},                         /*   SWG_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
/*   SWG0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ50_INDEX,0U,                    0U},                         /*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
/*   SWG1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ51_INDEX,0U,                    0U},                         /*   SWG1_CLK clock             */
#endif
/*   SWT0_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ28_INDEX,0U,                    0U},                         /*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
/*   SWT1_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ27_INDEX,0U,                    0U},                         /*   SWT1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
/*   SWT2_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT2_COL0_REQ28_INDEX,0U,                    0U},                         /*   SWT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
/*   SWT3_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL0_REQ28_INDEX,0U,                    0U},                         /*   SWT3_CLK clock             */
#endif
/*   TEMPSENSE_CLK clock        */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL2_REQ95_INDEX,0U,                    0U},                         /*   TEMPSENSE_CLK clock        */
/*   TRACE_CLK clock            */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_SWMUX_DIV,           CLOCK_IP_TRACE_EXTENSION,         0U,    CLOCK_IP_SEL_11_INDEX,  CLOCK_IP_DIV_0_INDEX,   0U,                            0U,                    0U},                         /*   TRACE_CLK clock            */
/*   TRGMUX0_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT0_COL1_REQ32_INDEX,0U,                    0U},                         /*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
/*   TRGMUX1_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT3_COL1_REQ48_INDEX,0U,                    0U},                         /*   TRGMUX1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/*   TSENSE0_CLK clock          */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ49_INDEX,0U,                    0U},                         /*   TSENSE0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
/*   USDHC_PER_CLK clock            */ {CLOCK_IP_CGM_0_INSTANCE,     CLOCK_IP_HWMUX_DIV_GATE,      CLOCK_IP_USDHC_EXTENSION,         0U,    CLOCK_IP_SEL_14_INDEX,  CLOCK_IP_DIV_0_INDEX, CLOCK_IP_PRT2_COL1_REQ57_INDEX,0U,                      0U},                         /*   USDHC_PER_CLK clock             */
#endif
/*   WKPU0_CLK clock            */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL1_REQ45_INDEX,0U,                    0U},                         /*   WKPU0_CLK clock            */
#if defined(CLOCK_IP_HAS_XRDC_CLK)
/*   XRDC_CLK clock             */ {0U,                          CLOCK_IP_GATE,                0U,                               0U,    0U,                     0U,                     CLOCK_IP_PRT1_COL0_REQ30_INDEX,0U,                    0U},                         /*   XRDC_CLK clock             */
#endif
};


/*!
* @brief Reset value of a software clock mux associated to a clock name
*/
const uint8 Clock_Ip_au8SoftwareMuxResetValue[CLOCK_IP_NAMES_NO] = {
0U,   /*   CLOCK_IS_OFF clock         */
0U,   /*   FIRC_CLK clock             */
0U,   /*   FIRC_STANDBY_CLK clock     */
0U,   /*   SIRC_CLK clock             */
0U,   /*   SIRC_STANDBY_CLK clock     */
0U,   /*   FXOSC_CLK clock            */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
0U,   /*   SXOSC_CLK clock            */
#endif
0U,   /*   PLL_CLK clock              */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
0U,   /*   PLLAUX_CLK clock           */
#endif
0U,   /*   PLL_POSTDIV_CLK clock      */
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
0U,   /*   PLLAUX_POSTDIV_CLK clock   */
#endif
0U,   /*   PLL_PHI0 clock             */
0U,   /*   PLL_PHI1 clock             */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
0U,   /*   PLLAUX_PHI0_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
0U,   /*   PLLAUX_PHI1_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
0U,   /*   PLLAUX_PHI2_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
0U,   /*   emac_mii_rx clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
0U,   /*   emac_mii_rmii_tx clock     */
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
0U,   /*   Gmac_mii_rx clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
0U,   /*   Gmac_mii_rmii_tx clock     */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
0U,   /*   GMAC0_MII_RGMII_RX clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
0U,   /*   GMAC0_MII_RMII_RGMII_TX clock     */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
0U,   /*   GMAC1_MII_RGMII_RX clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
0U,   /*   GMAC1_MII_RMII_RGMII_TX clock          */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
0U,   /*   lfast_ext_ref clock        */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
0U,   /*   swg_pad clock              */
#endif
0U,   /*   SCS_CLK clock             */
0U,   /*   CORE_CLK clock             */
0U,   /*   AIPS_PLAT_CLK clock        */
0U,   /*   AIPS_SLOW_CLK clock        */
0U,   /*   HSE_CLK clock              */
0U,   /*   DCM_CLK clock              */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
0U,   /*   LBIST_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
0U,   /*   QSPI_MEM_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
0U,   /*   CM7_CORE_CLK clock         */
#endif
0U,   /*   CLKOUT_RUN_CLK clock      */
0U,   /*   THE_LAST_PRODUCER_CLK clock */
0U,   /*   ADC0_CLK clock             */
0U,   /*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
0U,   /*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
0U,   /*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
0U,   /*   ADC4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
0U,   /*   ADC5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
0U,   /*   ADC6_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
0U,   /*   ADCBIST_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
0U,   /*   AES_ACCEL_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
0U,   /*   AES_APP0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
0U,   /*   AES_APP1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
0U,   /*   AES_APP2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
0U,   /*   AES_APP3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
0U,   /*   AES_APP4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
0U,   /*   AES_APP5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
0U,   /*   AES_APP6_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
0U,   /*   AES_APP7_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
0U,   /*   AES_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
0U,   /*   AXBS_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
0U,   /*   AXBS0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
0U,   /*   AXBS1_CLK clock            */
#endif
0U,   /*   BCTU0_CLK clock            */
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
0U,   /*   BCTU1_CLK clock            */
#endif
0U,   /*   CLKOUT_STANDBY_CLK clock  */
0U,   /*   CMP0_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP1_CLK)
0U,   /*   CMP1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
0U,   /*   CMP2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
0U,   /*   COOLFLUX_D_RAM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
0U,   /*   COOLFLUX_D_RAM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
0U,   /*   COOLFLUX_DSP16L_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
0U,   /*   COOLFLUX_I_RAM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
0U,   /*   COOLFLUX_I_RAM1_CLK clock             */
#endif
0U,   /*   CRC0_CLK clock             */
0U,   /*   DCM0_CLK clock             */
0U,   /*   DMAMUX0_CLK clock          */
0U,   /*   DMAMUX1_CLK clock          */
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
0U,   /*   DMAMUX2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
0U,   /*   DMAMUX3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
0U,   /*   DSPI_MSC_CLK clock          */
#endif
0U,   /*   EDMA0_CLK clock            */
0U,   /*   EDMA0_TCD0_CLK clock       */
0U,   /*   EDMA0_TCD1_CLK clock       */
0U,   /*   EDMA0_TCD2_CLK clock       */
0U,   /*   EDMA0_TCD3_CLK clock       */
0U,   /*   EDMA0_TCD4_CLK clock       */
0U,   /*   EDMA0_TCD5_CLK clock       */
0U,   /*   EDMA0_TCD6_CLK clock       */
0U,   /*   EDMA0_TCD7_CLK clock       */
0U,   /*   EDMA0_TCD8_CLK clock       */
0U,   /*   EDMA0_TCD9_CLK clock       */
0U,   /*   EDMA0_TCD10_CLK clock      */
0U,   /*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
0U,   /*   EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
0U,   /*   EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
0U,   /*   EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
0U,   /*   EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
0U,   /*   EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
0U,   /*   EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
0U,   /*   EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
0U,   /*   EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
0U,   /*   EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
0U,   /*   EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
0U,   /*   EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
0U,   /*   EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
0U,   /*   EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
0U,   /*   EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
0U,   /*   EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
0U,   /*   EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
0U,   /*   EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
0U,   /*   EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
0U,   /*   EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
0U,   /*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
0U,   /*   EDMA1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
0U,   /*   EDMA1_TCD0_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
0U,   /*   EDMA1_TCD1_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
0U,   /*   EDMA1_TCD2_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
0U,   /*   EDMA1_TCD3_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
0U,   /*   EDMA1_TCD4_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
0U,   /*   EDMA1_TCD5_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
0U,   /*   EDMA1_TCD6_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
0U,   /*   EDMA1_TCD7_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
0U,   /*   EDMA1_TCD8_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
0U,   /*   EDMA1_TCD9_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
0U,   /*   EDMA1_TCD10_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
0U,   /*   EDMA1_TCD11_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
0U,   /*   EDMA1_TCD12_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
0U,   /*   EDMA1_TCD13_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
0U,   /*   EDMA1_TCD14_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
0U,   /*   EDMA1_TCD15_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
0U,   /*   EDMA1_TCD16_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
0U,   /*   EDMA1_TCD17_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
0U,   /*   EDMA1_TCD18_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
0U,   /*   EDMA1_TCD19_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
0U,   /*   EDMA1_TCD20_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
0U,   /*   EDMA1_TCD21_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
0U,   /*   EDMA1_TCD22_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
0U,   /*   EDMA1_TCD23_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
0U,   /*   EDMA1_TCD24_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
0U,   /*   EDMA1_TCD25_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
0U,   /*   EDMA1_TCD26_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
0U,   /*   EDMA1_TCD27_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
0U,   /*   EDMA1_TCD28_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
0U,   /*   EDMA1_TCD29_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
0U,   /*   EDMA1_TCD30_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
0U,   /*   EDMA1_TCD31_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
0U,   /*   EFLEX_PWM0_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
0U,   /*   EFLEX_PWM1_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
0U,   /*   EIM_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
0U,   /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
0U,   /*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
0U,   /*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
0U,   /*   EIM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
0U,   /*   EMAC_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
0U,   /*   GMAC_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
0U,   /*   EMAC0_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
0U,   /*   EMAC_TS_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
0U,   /*   EMAC0_TS_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
0U,   /*   EMAC_TX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
0U,   /*   GMAC_TX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
0U,   /*   EMAC0_TX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
0U,   /*   EMAC_TX_RMII_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_RMII_CLK)
0U,   /*   EMAC0_TX_RMII_CLK clock    */
#endif
0U,   /*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
0U,   /*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
0U,   /*   EMIOS2_CLK clock           */
#endif
0U,   /*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
0U,   /*   ERM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
0U,   /*   ETPU_AB_REGISTERS_CLK clock*/
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
0U,   /*   ETPU_CODE_RAM1_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
0U,   /*   ETPU_CODE_RAM2_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
0U,   /*   ETPU_RAM_MIRROR_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
0U,   /*   ETPU_RAM_SDM_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
0U,   /*   FCCU_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
0U,   /*   FLASH0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
0U,   /*   FLASH0_ALT_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
0U,   /*   FLASH1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
0U,   /*   FLASH1_ALT_CLK clock       */
#endif
0U,   /*   FLEXCANA_CLK clock        */
0U,   /*   FLEXCAN0_CLK clock         */
0U,   /*   FLEXCAN1_CLK clock         */
0U,   /*   FLEXCAN2_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
0U,   /*   FLEXCANB_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
0U,   /*   FLEXCAN3_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
0U,   /*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
0U,   /*   FLEXCAN5_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
0U,   /*   FLEXCAN6_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
0U,   /*   FLEXCAN7_CLK clock         */
#endif
0U,   /*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
0U,   /*   HSE_MU0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
0U,   /*   HSE_MU1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
0U,   /*   JDC_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
0U,   /*   IGF0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
0U,   /*   GMAC0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK)
0U,   /*   GMAC1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
0U,   /*   GMAC0_RX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
0U,   /*   GMAC0_TX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
0U,   /*   GMAC_TS_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
0U,   /*   GMAC0_TX_RMII_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
0U,   /*   GMAC1_RX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
0U,   /*   GMAC1_TX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
0U,   /*   GMAC1_RMII_CLK clock             */
#endif
0U,   /*   INTM_CLK clock             */
0U,   /*   LCU0_CLK clock             */
0U,   /*   LCU1_CLK clock             */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
0U,   /*   LFAST_REF_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
0U,   /*   LPI2C0_CLK clock           */
#endif
0U,   /*   LPI2C1_CLK clock           */
0U,   /*   LPSPI0_CLK clock           */
0U,   /*   LPSPI1_CLK clock           */
0U,   /*   LPSPI2_CLK clock           */
0U,   /*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
0U,   /*   LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
0U,   /*   LPSPI5_CLK clock           */
#endif
0U,   /*   LPUART0_CLK clock          */
0U,   /*   LPUART1_CLK clock          */
0U,   /*   LPUART2_CLK clock          */
0U,   /*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
0U,   /*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
0U,   /*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
0U,   /*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
0U,   /*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
0U,   /*   LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
0U,   /*   LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
0U,   /*   LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
0U,   /*   LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
0U,   /*   LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
0U,   /*   LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
0U,   /*   LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
0U,   /*   LPUART15_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
0U,   /*   LPUART_MSC_CLK clock       */
#endif
0U,   /*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MU2A_CLK)
0U,   /*   MU2A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
0U,   /*   MU2B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
0U,   /*   MU3A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
0U,   /*   MU3B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
0U,   /*   MU4A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
0U,   /*   MU4B_CLK clock              */
#endif
0U,   /*   PIT0_CLK clock             */
0U,   /*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
0U,   /*   PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
0U,   /*   PIT3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
0U,   /*   PRAMC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
0U,   /*   PRAMC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
0U,   /*   QSPI_2XSFIF_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
0U,   /*   QSPI0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
0U,   /*   QSPI0_RAM_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
0U,   /*   QSPI0_TX_MEM_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
0U,   /*   QSPI_SFCK_CLK clock        */
#endif
0U,   /*   RTC_CLK clock             */
0U,   /*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
0U,   /*   SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
0U,   /*   SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
0U,   /*   SDA_AP_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
0U,   /*   SDADC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
0U,   /*   SDADC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
0U,   /*   SDADC2_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
0U,   /*   SDADC3_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
0U,   /*   SEMA42_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
0U,   /*   SIPI0_CLK clock             */
#endif
0U,   /*   SIUL2_CLK clock            */
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
0U,   /*   SIUL2_PDAC0_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
0U,   /*   SIUL2_PDAC0_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
0U,   /*   SIUL2_PDAC1_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
0U,   /*   SIUL2_PDAC1_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
0U,   /*   SIUL2_PDAC2_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
0U,   /*   SIUL2_PDAC2_1_CLK clock    */
#endif
0U,   /*   STCU0_CLK clock            */
0U,   /*   STMA_CLK clock            */
0U,   /*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STMB_CLK)
0U,   /*   STMB_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
0U,   /*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
0U,   /*   STMC_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
0U,   /*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
0U,   /*   STMD_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
0U,   /*   STM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
0U,   /*   SWG_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
0U,   /*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
0U,   /*   SWG1_CLK clock             */
#endif
0U,   /*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
0U,   /*   SWT1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
0U,   /*   SWT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
0U,   /*   SWT3_CLK clock             */
#endif
0U,   /*   TEMPSENSE_CLK clock        */
0U,   /*   TRACE_CLK clock           */
0U,   /*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
0U,   /*   TRGMUX1_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
0U,   /*   TSENSE0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
0U,   /*   USDHC_PER_CLK clock             */
#endif
0U,   /*   WKPU0_CLK clock            */
#if defined(CLOCK_IP_HAS_XRDC_CLK)
0U,   /*   XRDC_CLK clock             */
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_8
#include "Mcu_MemMap.h"




/* Clock start constant section data */
#define MCU_START_SEC_CONST_16
#include "Mcu_MemMap.h"
/*!
 * @brief Converts a clock name to a selector entry hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryHardwareValue[CLOCK_IP_PRODUCERS_NO] = {
    0U,                                       /*!< CLOCK_IS_OFF                            */
    0U,                                       /*!< FIRC_CLK                                */
    0U,                                       /*!< FIRC_STANDBY_CLK                        */
    1U,                                       /*!< SIRC_CLK                                */
    0U,                                       /*!< SIRC_STANDBY_CLK                        */
    2U,                                       /*!< FXOSC_CLK                               */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    4U,                                       /*!< SXOSC_CLK                               */
#endif
    0U,                                       /*!< PLL_CLK                                 */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    0U,                                       /*!< PLLAUX_CLK                              */
#endif
    0U,                                       /*!< PLL_POSTDIV_CLK                         */
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
    0U,                                       /*!< PLLAUX_POSTDIV_CLK                      */
#endif
    8U,                                       /*!< PLL_PHI0                                */
    9U,                                       /*!< PLL_PHI1                                */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
    12U,                                      /*!< PLLAUX_PHI0_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
    13U,                                      /*!< PLLAUX_PHI1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
    14U,                                      /*!< PLLAUX_PHI2_CLK                         */
#endif
#if (defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK) || defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK))
    25U,                                      /*!< emac_mii_rx/gmac_mii_rgmii_rx                 */
#endif
#if (defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK))
    24U,                                      /*!< emac_mii_rmii_tx/gmac_mii_rmii_rgmii_tx        */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
    25U,                                      /*!< GMAC0_MII_RGMII_RX                             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
    24U,                                      /*!< GMAC0_MII_RMII_RGMII_TX                        */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
    29U,                                      /*!< GMAC1_MII_RGMII_RX                             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
    30U,                                      /*!< GMAC1_MII_RMII_RGMII_TX                             */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
    27U,                                      /*!< lfast_ext_ref                           */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
    28U,                                      /*!< swg_pad                                 */
#endif
    0U,                                       /*!< SCS_CLK                                 */
    16U,                                      /*!< CORE_CLK                                */
    22U,                                      /*!< AIPS_PLAT_CLK                           */
    23U,                                      /*!< AIPS_SLOW_CLK                           */
    19U,                                      /*!< HSE_CLK                                 */
    0U,                                       /*!< DCM_CLK                                 */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    0U,                                       /*!< LBIST_CLK                               */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    0U,                                       /*!< QSPI_MEM_CLK                            */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    21U,                                       /*!< CM7_CORE_CLK                            */
#endif
    50U,                                      /*!< CLKOUT_RUN_CLK                          */
};
/*!
 * @brief Converts a clock name to a RTC selector entry hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryRtcHardwareValue[CLOCK_IP_PRODUCERS_NO] = {
    0U,                                       /*!< CLOCK_IS_OFF                            */
    2U,                                       /*!< FIRC_CLK                                */
    0U,                                       /*!< FIRC_STANDBY_CLK                        */
    1U,                                       /*!< SIRC_CLK                                */
    0U,                                       /*!< SIRC_STANDBY_CLK                        */
    3U,                                       /*!< FXOSC_CLK                               */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    0U,                                       /*!< SXOSC_CLK                               */
#endif
    0U,                                       /*!< PLL_CLK                                 */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    0U,                                       /*!< PLLAUX_CLK                              */
#endif
    0U,                                       /*!< PLL_POSTDIV_CLK                         */
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
    0U,                                       /*!< PLLAUX_POSTDIV_CLK                      */
#endif
    0U,                                       /*!< PLL_PHI0_CLK                            */
    0U,                                       /*!< PLL_PHI1_CLK                            */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
    0U,                                       /*!< PLLAUX_PHI0_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
    0U,                                       /*!< PLLAUX_PHI1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
    0U,                                       /*!< PLLAUX_PHI2_CLK                         */
#endif
#if (defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK) || defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK))
    0U,                                      /*!< emac_mii_rx/gmac_mii_rgmii_rx                 */
#endif
#if (defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK))
    0U,                                      /*!< emac_mii_rmii_tx/gmac_mii_rmii_rgmii_tx        */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
    0U,                                       /*!< GMAC0_MII_RGMII_RX_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
    0U,                                       /*!< GMAC0_MII_RMII_RGMII_TX_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
    0U,                                       /*!< GMAC1_MII_RGMII_RX_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
    0U,                                       /*!< GMAC1_MII_RMII_RGMII_TX_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
    0U,                                       /*!< LFAST_EXT_REF_CLK                       */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
    0U,                                       /*!< SWG_PAD_CLK                             */
#endif
    0U,                                       /*!< SCS_CLK                                 */
    0U,                                       /*!< CORE_CLK                                */
    0U,                                       /*!< AIPS_PLAT_CLK                           */
    0U,                                       /*!< AIPS_SLOW_CLK                           */
    0U,                                       /*!< HSE_CLK                                 */
    0U,                                       /*!< DCM_CLK                                 */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    0U,                                       /*!< LBIST_CLK                               */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    0U,                                       /*!< QSPI_MEM_CLK                            */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    0U,                                       /*!< CM7_CORE_CLK                            */
#endif
    0U,                                       /*!< CLKOUT_RUN_CLK                          */
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_16
#include "Mcu_MemMap.h"




/* Clock start constant section data */
#define MCU_START_SEC_CONST_32
#include "Mcu_MemMap.h"

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
    #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
/* Clock name types */
const uint32 Clock_Ip_au8ClockNameTypes[CLOCK_IP_NAMES_NO] =
{
/*   CLOCK_IS_OFF clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CLOCK_IS_OFF clock         */
/*   FIRC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FIRC_CLK clock             */
/*   FIRC_STANDBY_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FIRC_STANDBY_CLK clock     */
/*   SIRC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIRC_CLK clock             */
/*   SIRC_STANDBY_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIRC_STANDBY_CLK clock     */
/*   FXOSC_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FXOSC_CLK clock            */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
/*   SXOSC_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SXOSC_CLK clock            */
#endif
/*   PLL_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLL_CLK clock              */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
/*   PLLAUX_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLLAUX_CLK clock           */
#endif
/*   PLL_POSTDIV_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLL_POSTDIV_CLK clock      */
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
/*   PLLAUX_POSTDIV_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLLAUX_POSTDIV_CLK clock   */
#endif
/*   PLL_PHI0_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLL_PHI0_CLK clock         */
/*   PLL_PHI1_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLL_PHI1_CLK clock         */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
/*   PLLAUX_PHI0_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLLAUX_PHI0_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
/*   PLLAUX_PHI1_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLLAUX_PHI1_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
/*   PLLAUX_PHI2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PLLAUX_PHI2_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
/*   EMAC_MII_RX_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC_MII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
/*   EMAC_MII_RMII_TX_CLK clock */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC_MII_RMII_TX_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
/*   GMAC_MII_RGMII_RX_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC_MII_RGMII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
/*   GMAC_MII_RMII_RGMII_TX_CLK clock */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC_MII_RMII_RGMII_TX_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
/*   GMAC0_MII_RGMII_RX_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC0_MII_RGMII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
/*   GMAC0_MII_RMII_RGMII_TX_CLK clock*/ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC0_MII_RMII_RGMII_TX_CLK clock */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
/*   GMAC1_MII_RGMII_RX_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC1_MII_RGMII_RX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
/*   GMAC1_MII_RMII_RGMII_TX_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC1_MII_RMII_RGMII_TX_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
/*   LFAST_EXT_REF_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LFAST_EXT_REF_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
/*   SWG_PAD_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWG_PAD_CLK clock          */
#endif
/*   SCS_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SCS_CLK clock              */
/*   CORE_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CORE_CLK clock             */
/*   AIPS_PLAT_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AIPS_PLAT_CLK clock        */
/*   AIPS_SLOW_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AIPS_SLOW_CLK clock        */
/*   HSE_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   HSE_CLK clock              */
/*   DCM_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DCM_CLK clock              */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
/*   LBIST_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LBIST_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
/*   QSPI_MEM_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   QSPI_MEM_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/*   CM7_CORE_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CM7_CORE_CLK clock         */
#endif
/*   CLKOUT_RUN_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CLKOUT_RUN_CLK clock       */
/*   THE_LAST_PRODUCER_CLK      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   THE_LAST_PRODUCER_CLK      */
/*   ADC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC0_CLK clock             */
/*   ADC1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
/*   ADC2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
/*   ADC3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
/*   ADC4_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
/*   ADC5_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
/*   ADC6_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADC6_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
/*   ADCBIST_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ADCBIST_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
/*   AES_ACCEL_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_ACCEL_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
/*   AES_APP0_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
/*   AES_APP1_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
/*   AES_APP2_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
/*   AES_APP3_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
/*   AES_APP4_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
/*   AES_APP5_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
/*   AES_APP6_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
/*   AES_APP7_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_APP7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
/*   AES_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AES_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
/*   AXBS_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AXBS_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
/*   AXBS0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AXBS0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
/*   AXBS1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   AXBS1_CLK clock            */
#endif
/*   BCTU0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   BCTU0_CLK clock            */
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
/*   BCTU1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   BCTU1_CLK clock            */
#endif
/*   CLKOUT_STANDBY_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CLKOUT_STANDBY_CLK clock   */
/*   CMP0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CMP0_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP1_CLK)
/*   CMP1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CMP1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
/*   CMP2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CMP2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
/*   COOLFLUX_D_RAM0_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   COOLFLUX_D_RAM0_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
/*   COOLFLUX_D_RAM1_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   COOLFLUX_D_RAM1_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
/*   COOLFLUX_DSP16L_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   COOLFLUX_DSP16L_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
/*   COOLFLUX_I_RAM0_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   COOLFLUX_I_RAM0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
/*   COOLFLUX_I_RAM1_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   COOLFLUX_I_RAM1_CLK clock    */
#endif
/*   CRC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   CRC0_CLK clock             */
/*   DCM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DCM0_CLK clock             */
/*   DMAMUX0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DMAMUX0_CLK clock          */
/*   DMAMUX1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DMAMUX1_CLK clock          */
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
/*   DMAMUX2_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DMAMUX2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
/*   DMAMUX3_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DMAMUX3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
/*   DSPI_MSC_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   DSPI_MSC_CLK clock         */
#endif
/*   EDMA0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_CLK clock            */
/*   EDMA0_TCD0_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD0_CLK clock       */
/*   EDMA0_TCD1_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD1_CLK clock       */
/*   EDMA0_TCD2_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD2_CLK clock       */
/*   EDMA0_TCD3_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD3_CLK clock       */
/*   EDMA0_TCD4_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD4_CLK clock       */
/*   EDMA0_TCD5_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD5_CLK clock       */
/*   EDMA0_TCD6_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD6_CLK clock       */
/*   EDMA0_TCD7_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD7_CLK clock       */
/*   EDMA0_TCD8_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD8_CLK clock       */
/*   EDMA0_TCD9_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD9_CLK clock       */
/*   EDMA0_TCD10_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD10_CLK clock      */
/*   EDMA0_TCD11_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
/*   EDMA0_TCD12_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
/*   EDMA0_TCD13_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
/*   EDMA0_TCD14_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
/*   EDMA0_TCD15_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
/*   EDMA0_TCD16_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
/*   EDMA0_TCD17_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
/*   EDMA0_TCD18_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
/*   EDMA0_TCD19_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
/*   EDMA0_TCD20_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
/*   EDMA0_TCD21_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
/*   EDMA0_TCD22_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
/*   EDMA0_TCD23_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
/*   EDMA0_TCD24_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
/*   EDMA0_TCD25_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
/*   EDMA0_TCD26_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
/*   EDMA0_TCD27_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
/*   EDMA0_TCD28_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
/*   EDMA0_TCD29_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
/*   EDMA0_TCD30_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
/*   EDMA0_TCD31_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
/*   EDMA1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
/*   EDMA1_TCD0_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD0_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
/*   EDMA1_TCD1_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD1_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
/*   EDMA1_TCD2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD2_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
/*   EDMA1_TCD3_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD3_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
/*   EDMA1_TCD4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD4_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
/*   EDMA1_TCD5_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD5_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
/*   EDMA1_TCD6_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD6_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
/*   EDMA1_TCD7_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD7_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
/*   EDMA1_TCD8_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD8_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
/*   EDMA1_TCD9_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD9_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
/*   EDMA1_TCD10_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD10_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
/*   EDMA1_TCD11_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD11_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
/*   EDMA1_TCD12_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD12_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
/*   EDMA1_TCD13_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD13_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
/*   EDMA1_TCD14_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD14_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
/*   EDMA1_TCD15_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD15_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
/*   EDMA1_TCD16_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD16_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
/*   EDMA1_TCD17_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD17_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
/*   EDMA1_TCD18_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD18_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
/*   EDMA1_TCD19_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD19_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
/*   EDMA1_TCD20_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD20_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
/*   EDMA1_TCD21_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD21_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
/*   EDMA1_TCD22_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD22_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
/*   EDMA1_TCD23_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD23_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
/*   EDMA1_TCD24_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD24_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
/*   EDMA1_TCD25_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD25_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
/*   EDMA1_TCD26_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD26_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
/*   EDMA1_TCD27_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD27_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
/*   EDMA1_TCD28_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD28_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
/*   EDMA1_TCD29_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD29_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
/*   EDMA1_TCD30_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD30_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
/*   EDMA1_TCD31_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EDMA1_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
/*   EFLEX_PWM0_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EFLEX_PWM0_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
/*   EFLEX_PWM1_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EFLEX_PWM1_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
/*   EIM_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EIM_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
/*   EIM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
/*   EIM1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
/*   EIM2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
/*   EIM3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EIM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
/*   EMAC_RX_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
/*   GMAC_RX_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
/*   EMAC0_RX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC0_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
/*   EMAC_TS_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC_TS_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
/*   EMAC0_TS_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC0_TS_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
/*   EMAC_TX_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
/*   GMAC_TX_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
/*   EMAC0_TX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC0_TX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
/*   EMAC_TX_RMII_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC_TX_RMII_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_RMII_CLK)
/*   EMAC0_TX_RMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMAC0_TX_RMII_CLK clock    */
#endif
/*   EMIOS0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/*   EMIOS1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
/*   EMIOS2_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   EMIOS2_CLK clock           */
#endif
/*   ERM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
/*   ERM1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ERM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
/*   ETPU_AB_REGISTERS_CLK clock*/ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ETPU_AB_REGISTERS_CLK clock*/
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
/*   ETPU_CODE_RAM1_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ETPU_CODE_RAM1_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
/*   ETPU_CODE_RAM2_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ETPU_CODE_RAM2_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
/*   ETPU_RAM_MIRROR_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ETPU_RAM_MIRROR_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
/*   ETPU_RAM_SDM_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   ETPU_RAM_SDM_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
/*   FCCU_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FCCU_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
/*   FLASH0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLASH0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
/*   FLASH0_ALT_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLASH0_ALT_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
/*   FLASH1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLASH1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
/*   FLASH1_ALT_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLASH1_ALT_CLK clock       */
#endif
/*   FLEXCANA_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCANA_CLK clock         */
/*   FLEXCAN0_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN0_CLK clock         */
/*   FLEXCAN1_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN1_CLK clock         */
/*   FLEXCAN2_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN2_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
/*   FLEXCANB_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCANB_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
/*   FLEXCAN3_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN3_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
/*   FLEXCAN4_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
/*   FLEXCAN5_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN5_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
/*   FLEXCAN6_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN6_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
/*   FLEXCAN7_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXCAN7_CLK clock         */
#endif
/*   FLEXIO0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
/*   HSE_MU0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   HSE_MU0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
/*   HSE_MU1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   HSE_MU1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
/*   JDC_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   JDC_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
/*   IGF0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   IGF0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
/*   GMAC0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK)
/*   GMAC1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
/*   GMAC0_RX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC0_RX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
/*   GMAC0_TX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC0_TX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
/*   GMAC_TS_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC_TS_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
/*   GMAC0_TX_RMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC0_TX_RMII_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
/*   GMAC1_RX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC1_RX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
/*   GMAC1_TX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC1_TX_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
/*   GMAC1_RMII_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   GMAC1_RMII_CLK clock             */
#endif
/*   INTM_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   INTM_CLK clock             */
/*   LCU0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LCU0_CLK clock             */
/*   LCU1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LCU1_CLK clock             */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
/*   LFAST_REF_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LFAST_REF_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
/*   LPI2C0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPI2C0_CLK clock           */
#endif
/*   LPI2C1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPI2C1_CLK clock           */
/*   LPSPI0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPSPI0_CLK clock           */
/*   LPSPI1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPSPI1_CLK clock           */
/*   LPSPI2_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPSPI2_CLK clock           */
/*   LPSPI3_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
/*   LPSPI4_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
/*   LPSPI5_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPSPI5_CLK clock           */
#endif
/*   LPUART0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART0_CLK clock          */
/*   LPUART1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART1_CLK clock          */
/*   LPUART2_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART2_CLK clock          */
/*   LPUART3_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
/*   LPUART4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
/*   LPUART5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
/*   LPUART6_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
/*   LPUART7_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
/*   LPUART8_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
/*   LPUART9_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
/*   LPUART10_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
/*   LPUART11_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
/*   LPUART12_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
/*   LPUART13_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
/*   LPUART14_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
/*   LPUART15_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART15_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
/*   LPUART_MSC_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   LPUART_MSC_CLK clock       */
#endif
/*   MSCM_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MU2A_CLK)
/*   MU2A_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MU2A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
/*   MU2B_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MU2B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
/*   MU3A_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MU3A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
/*   MU3B_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MU3B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
/*   MU4A_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MU4A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
/*   MU4B_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   MU4B_CLK clock              */
#endif
/*   PIT0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PIT0_CLK clock             */
/*   PIT1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
/*   PIT2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
/*   PIT3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PIT3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
/*   PRAMC0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PRAMC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
/*   PRAMC1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   PRAMC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/*   QSPI_2XSFIF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   QSPI_2XSFIF_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
/*   QSPI0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   QSPI0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
/*   QSPI0_RAM_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   QSPI0_RAM_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
/*   QSPI0_TX_MEM_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   QSPI0_TX_MEM_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
/*   QSPI_SFCK_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   QSPI_SFCK_CLK clock        */
#endif
/*   RTC_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   RTC_CLK clock              */
/*   RTC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
/*   SAI0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
/*   SAI1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
/*   SDA_AP_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SDA_AP_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
/*   SDADC0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SDADC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
/*   SDADC1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SDADC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
/*   SDADC2_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SDADC2_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
/*   SDADC3_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SDADC3_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
/*   SEMA42_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SEMA42_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
/*   SIPI0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIPI0_CLK clock             */
#endif
/*   SIUL2_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_CLK clock            */
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
/*   SIUL2_PDAC0_0_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_PDAC0_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
/*   SIUL2_PDAC0_1_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_PDAC0_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
/*   SIUL2_PDAC1_0_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_PDAC1_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
/*   SIUL2_PDAC1_1_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_PDAC1_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
/*   SIUL2_PDAC2_0_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_PDAC2_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
/*   SIUL2_PDAC2_1_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SIUL2_PDAC2_1_CLK clock    */
#endif
/*   STCU0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STCU0_CLK clock            */
/*   STMA_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STMA_CLK clock             */
/*   STM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STMB_CLK)
/*   STMB_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STMB_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
/*   STM1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
/*   STMC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STMC_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
/*   STM2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
/*   STMD_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STMD_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
/*   STM3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   STM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
/*   SWG_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWG_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
/*   SWG0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
/*   SWG1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWG1_CLK clock             */
#endif
/*   SWT0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
/*   SWT1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWT1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
/*   SWT2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
/*   SWT3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   SWT3_CLK clock             */
#endif
/*   TEMPSENSE_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   TEMPSENSE_CLK clock        */
/*   TRACE_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   TRACE_CLK clock            */
/*   TRGMUX0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
/*   TRGMUX1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   TRGMUX1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/*   TSENSE0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   TSENSE0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
/*   USDHC_PER_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   USDHC_PER_CLK clock             */
#endif
/*   WKPU0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   WKPU0_CLK clock            */
#if defined(CLOCK_IP_HAS_XRDC_CLK)
/*   XRDC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,/*   XRDC_CLK clock             */
#endif
};
    #endif /* CLOCK_IP_DEV_ERROR_DETECT == STD_ON */
#endif /* CLOCK_IP_DEV_ERROR_DETECT */

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_32
#include "Mcu_MemMap.h"


/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

Clock_Ip_CgmMuxType* const Clock_Ip_apxCgm[CLOCK_IP_MC_CGM_INSTANCES_COUNT][CLOCK_IP_MC_CGM_MUXS_COUNT] =
{
    {
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_0_CSC)),
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_1_CSC)),
#if defined(CLOCK_IP_HAS_STMB_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_2_CSC)),
#else
        NULL_PTR,
#endif
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_3_CSC)),
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_4_CSC)),
#else
        NULL_PTR,
#endif
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_5_CSC)),
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_6_CSC)),
#if (defined(CLOCK_IP_HAS_EMAC_RX_CLK) || defined(CLOCK_IP_HAS_GMAC0_RX_CLK) || defined(CLOCK_IP_HAS_GMAC_RX_CLK))
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_7_CSC)),
#else
        NULL_PTR,
#endif
#if (defined(CLOCK_IP_HAS_EMAC_TX_CLK) || defined(CLOCK_IP_HAS_GMAC0_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_TX_CLK))
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_8_CSC)),
#else
        NULL_PTR,
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK) || defined(CLOCK_IP_HAS_GMAC_TS_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_9_CSC)),
#else
        NULL_PTR,
#endif
#if (defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK) || defined(CLOCK_IP_HAS_QSPI_SFCK_CLK))
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_10_CSC)),
#else
        NULL_PTR,
#endif
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_11_CSC)),
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_12_CSC)),
#else
        NULL_PTR,
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_13_CSC)),
#else
        NULL_PTR,
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_14_CSC)),
#else
        NULL_PTR,
#endif
#if (defined(CLOCK_IP_HAS_LFAST_REF_CLK) || defined(CLOCK_IP_HAS_GMAC1_RX_CLK))
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_15_CSC)),
#else
        NULL_PTR,
#endif
#if (defined(CLOCK_IP_HAS_SWG_CLK) || defined(CLOCK_IP_HAS_GMAC1_TX_CLK))
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_16_CSC)),
#else
        NULL_PTR,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_17_CSC)),
#else
        NULL_PTR,
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_18_CSC)),
#else
        NULL_PTR,
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
        (Clock_Ip_CgmMuxType*)(&(IP_MC_CGM->MUX_19_CSC)),
#else
        NULL_PTR,
#endif
    },
};
volatile Clock_Ip_CgmPcfsType* const Clock_Ip_apxCgmPcfs[CLOCK_IP_MC_CGM_INSTANCES_COUNT] =
{
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM->PCFS_SDUR)),
};

Clock_Ip_ExtOSCType* const Clock_Ip_apxXosc[CLOCK_IP_XOSC_INSTANCES_ARRAY_SIZE] =
{
    (Clock_Ip_ExtOSCType*)IP_FXOSC,
#ifdef IP_SXOSC
    (Clock_Ip_ExtOSCType*)IP_SXOSC,
#else
    NULL_PTR,
#endif
};

Clock_Ip_PllType const Clock_Ip_apxPll[CLOCK_IP_PLL_INSTANCES_ARRAY_SIZE] = {
    {
        IP_PLL,
        CLOCK_IP_PLL_DIVIDER_COUNT,
    },
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    {
        IP_PLL_AUX,
        CLOCK_IP_PLLAUX_DIVIDER_COUNT,
    },
#else
    {
        NULL_PTR,
        0,
    },
#endif
};

Clock_Ip_ClockMonitorType* const Clock_Ip_apxCmu[CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE] =
{
    (Clock_Ip_ClockMonitorType*)IP_CMU_0,
    NULL_PTR,
    NULL_PTR,
    (Clock_Ip_ClockMonitorType*)IP_CMU_3,
    (Clock_Ip_ClockMonitorType*)IP_CMU_4,
    (Clock_Ip_ClockMonitorType*)IP_CMU_5,
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    (Clock_Ip_ClockMonitorType*)IP_CMU_6,
#else
    NULL_PTR,
#endif
};

Clock_Ip_NameType const Clock_Ip_aeCmuNames[CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE] =
{
        FXOSC_CLK,
        RESERVED_CLK,
        RESERVED_CLK,
        CORE_CLK,
        AIPS_PLAT_CLK,
        HSE_CLK,
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
        CM7_CORE_CLK,
#else
        RESERVED_CLK,
#endif
};

Clock_Ip_CmuInfoType const Clock_Ip_axCmuInfo[CLOCK_IP_CMU_INFO_SIZE] =  {

/* CLOCK_IP_CMU_0_INSTANCE */
{
    FXOSC_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                          /* Name of the reference clock */
    AIPS_SLOW_CLK,                                     /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_0,              /* Cmu instance */
},
/* Reserved cmu instance */
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,                                        /* Cmu instance */
},
/* Reserved cmu instance */
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,                                        /* Cmu instance */
},
/* CLOCK_IP_CMU_3_INSTANCE */
{
    CORE_CLK,                                          /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                         /* Name of the reference clock */
    AIPS_SLOW_CLK,                                     /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_3,              /* Cmu instance */
},
/* CLOCK_IP_CMU_4_INSTANCE */
{
    AIPS_PLAT_CLK,                                     /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                          /* Name of the reference clock */
    AIPS_SLOW_CLK,                                     /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_4,              /* Cmu instance */
},
/* CLOCK_IP_CMU_5_INSTANCE */
{
    HSE_CLK,                                           /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                          /* Name of the reference clock */
    AIPS_SLOW_CLK,                                     /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_5,              /* Cmu instance */
},
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/* CLOCK_IP_CMU_6_INSTANCE */
{
    CM7_CORE_CLK,                                      /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                         /* Name of the reference clock */
    AIPS_SLOW_CLK,                                     /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_6,              /* Cmu instance */
},
#else
/* Reserved cmu instance */
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,                                        /* Cmu instance */
},
#endif
};

volatile Clock_Ip_McmePartitionSetType* const Clock_Ip_apxMcMeSetPartitions[CLOCK_IP_MC_ME_PARTITIONS_COUNT] =
{
     (volatile Clock_Ip_McmePartitionSetType*)(PRTN0_COFB0_CLKEN_ADDRESS),

     (volatile Clock_Ip_McmePartitionSetType*)( ((volatile uint8*)&(IP_MC_ME->PRTN1_COFB0_CLKEN)) ),
#if (!(defined(CLOCK_IP_DERIVATIVE_001) || defined(CLOCK_IP_DERIVATIVE_002)))
     (volatile Clock_Ip_McmePartitionSetType*)( ((volatile uint8*)&(IP_MC_ME->PRTN2_COFB0_CLKEN)) ),
#else
     NULL_PTR,
#endif
#ifdef CLOCK_IP_DERIVATIVE_006
     (volatile Clock_Ip_McmePartitionSetType*)( ((volatile uint8*)&(IP_MC_ME->PRTN3_COFB0_CLKEN)) ),
#else
     NULL_PTR,
#endif

};

volatile const Clock_Ip_McmePartitionGetType* const Clock_Ip_apxMcMeGetPartitions[CLOCK_IP_MC_ME_PARTITIONS_COUNT] =
{
     (volatile const Clock_Ip_McmePartitionGetType*)(PRTN0_COFB0_STAT_ADDRESS),

     (volatile const Clock_Ip_McmePartitionGetType*)( ((volatile const uint8*)&(IP_MC_ME->PRTN1_COFB0_STAT)) ),
#if (!(defined(CLOCK_IP_DERIVATIVE_001) || defined(CLOCK_IP_DERIVATIVE_002)))
     (volatile const Clock_Ip_McmePartitionGetType*)( ((volatile const uint8*)&(IP_MC_ME->PRTN2_COFB0_STAT)) ),
#else
     NULL_PTR,
#endif
#ifdef CLOCK_IP_DERIVATIVE_006
     (volatile const Clock_Ip_McmePartitionGetType*)( ((volatile const uint8*)&(IP_MC_ME->PRTN3_COFB0_STAT)) ),
#else
     NULL_PTR,
#endif
};

volatile Clock_Ip_McmePartitionTriggerType* const Clock_Ip_apxMcMeTriggerPartitions[CLOCK_IP_MC_ME_PARTITIONS_COUNT] =
{
     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN0_PCONF)) ),

     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN1_PCONF)) ),
#if (!(defined(CLOCK_IP_DERIVATIVE_001) || defined(CLOCK_IP_DERIVATIVE_002)))
     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN2_PCONF)) ),
#else
     NULL_PTR,
#endif
#ifdef CLOCK_IP_DERIVATIVE_006
     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN3_PCONF)) ),
#else
     NULL_PTR,
#endif
};

const Clock_Ip_ClockNameSourceType Clock_Ip_aeSourceTypeClockName[CLOCK_IP_PRODUCERS_NO] = {
    UKNOWN_TYPE,                               /*!< CLOCK_IS_OFF                            */
    IRCOSC_TYPE,                               /*!< FIRC_CLK                                */
    IRCOSC_TYPE,                               /*!< FIRC_STANDBY_CLK                        */
    IRCOSC_TYPE,                               /*!< SIRC_CLK                                */
    IRCOSC_TYPE,                               /*!< SIRC_STANDBY_CLK                        */
    XOSC_TYPE,                                 /*!< FXOSC_CLK                               */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    XOSC_TYPE,                                 /*!< SXOSC_CLK                               */
#endif
    PLL_TYPE,                                  /*!< PLL_CLK                                 */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    PLL_TYPE,                                  /*!< PLLAUX_CLK                              */
#endif
    PLL_TYPE,                                  /*!< PLL_POSTDIV_CLK                         */
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
    PLL_TYPE,                                  /*!< PLLAUX_POSTDIV_CLK                      */
#endif
    PLL_TYPE,                                  /*!< PLL_PHI0                                */
    PLL_TYPE,                                  /*!< PLL_PHI1                                */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
    PLL_TYPE,                                  /*!< PLLAUX_PHI0_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
    PLL_TYPE,                                  /*!< PLLAUX_PHI1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
    PLL_TYPE,                                  /*!< PLLAUX_PHI2_CLK                         */
#endif
#if (defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK) || defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK))
    EXT_CLK_TYPE,                              /*!< emac_mii_rx/gmac_mii_rgmii_rx                 */
#endif
#if (defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK))
    EXT_CLK_TYPE,                              /*!< emac_mii_rmii_tx/gmac_mii_rmii_rgmii_tx       */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
    EXT_CLK_TYPE,                              /*!< GMAC0_MII_RGMII_RX                             */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
    EXT_CLK_TYPE,                              /*!< GMAC0_MII_RMII_RGMII_TX                        */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
    EXT_CLK_TYPE,                              /*!< GMAC1_MII_RGMII_RX                             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
    EXT_CLK_TYPE,                              /*!< GMAC1_MII_RMII_RGMII_TX                             */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
    EXT_CLK_TYPE,                              /*!< lfast_ext_ref                           */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
    EXT_CLK_TYPE,                              /*!< swg_pad                                 */
#endif
    UKNOWN_TYPE,                               /*!< SCS_CLK                                 */
    UKNOWN_TYPE,                               /*!< CORE_CLK                                */
    UKNOWN_TYPE,                               /*!< AIPS_PLAT_CLK                           */
    UKNOWN_TYPE,                               /*!< AIPS_SLOW_CLK                           */
    UKNOWN_TYPE,                               /*!< HSE_CLK                                 */
    UKNOWN_TYPE,                               /*!< DCM_CLK                                 */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    UKNOWN_TYPE,                               /*!< LBIST_CLK                               */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    UKNOWN_TYPE,                               /*!< QSPI_MEM_CLK                            */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    UKNOWN_TYPE,                               /*!< CM7_CORE_CLK                            */
#endif
    UKNOWN_TYPE,                               /*!< CLKOUT_RUN_CLK                          */
};


const Clock_Ip_NameType Clock_Ip_aeHwPllName[CLOCK_IP_HARDWARE_PLL_ARRAY_SIZE] =
{
    PLL_CLK,        /* PLL_CLK clock */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    PLLAUX_CLK      /* PLLAUX_CLK clock */
#endif
};

const Clock_Ip_NameType Clock_Ip_aeHwDfsName[CLOCK_IP_HARDWARE_DFS_ARRAY_SIZE] =
{
    RESERVED_CLK,              /* RESERVED_CLK Clock */
};

const Clock_Ip_ClockExtensionType Clock_Ip_axFeatureExtensions[CLOCK_IP_EXTENSIONS_SIZE] = {
    /* Selector value mask            Selector value shift              Divider value mask             Divider value shift  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          0U,                                    0U},                                       /*   CLOCK_IP_SCS_EXTENSION  */
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,          MC_CGM_MUX_6_CSC_SELCTL_SHIFT,          MC_CGM_MUX_6_DC_0_DIV_MASK,            MC_CGM_MUX_6_DC_0_DIV_SHIFT},              /*   CLOCK_IP_CLKOUT_RUN_EXTENSION  */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,          MC_CGM_MUX_5_CSC_SELCTL_SHIFT,          MC_CGM_MUX_5_DC_0_DIV_MASK,            MC_CGM_MUX_5_DC_0_DIV_SHIFT},              /*   CLOCK_IP_CLKOUT_STANDBY_EXTENSION  */
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,          MC_CGM_MUX_7_CSC_SELCTL_SHIFT,          MC_CGM_MUX_7_DC_0_DIV_MASK,            MC_CGM_MUX_7_DC_0_DIV_SHIFT},              /*   CLOCK_IP_EMAC_RX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,          MC_CGM_MUX_9_CSC_SELCTL_SHIFT,          MC_CGM_MUX_9_DC_0_DIV_MASK,            MC_CGM_MUX_9_DC_0_DIV_SHIFT},              /*   CLOCK_IP_EMAC_TS_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,          MC_CGM_MUX_8_CSC_SELCTL_SHIFT,          MC_CGM_MUX_8_DC_0_DIV_MASK,            MC_CGM_MUX_8_DC_0_DIV_SHIFT},              /*   CLOCK_IP_EMAC_TX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
    {MC_CGM_MUX_12_CSC_SELCTL_MASK,         MC_CGM_MUX_12_CSC_SELCTL_SHIFT,         MC_CGM_MUX_12_DC_0_DIV_MASK,           MC_CGM_MUX_12_DC_0_DIV_SHIFT},             /*   CLOCK_IP_EMAC_TX_RMII_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,          MC_CGM_MUX_3_CSC_SELCTL_SHIFT,          MC_CGM_MUX_3_DC_0_DIV_MASK,            MC_CGM_MUX_3_DC_0_DIV_SHIFT},              /*   CLOCK_IP_FLEXCANA_EXTENSION  */
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,          MC_CGM_MUX_4_CSC_SELCTL_SHIFT,          MC_CGM_MUX_4_DC_0_DIV_MASK,            MC_CGM_MUX_4_DC_0_DIV_SHIFT},              /*   CLOCK_IP_FLEXCANB_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
    {MC_CGM_MUX_15_CSC_SELCTL_MASK,         MC_CGM_MUX_15_CSC_SELCTL_SHIFT,         MC_CGM_MUX_15_DC_0_DIV_MASK,           MC_CGM_MUX_15_DC_0_DIV_SHIFT},             /*   CLOCK_IP_LFAST_REF_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
    {MC_CGM_MUX_10_CSC_SELCTL_MASK,         MC_CGM_MUX_10_CSC_SELCTL_SHIFT,         MC_CGM_MUX_10_DC_0_DIV_MASK,           MC_CGM_MUX_10_DC_0_DIV_SHIFT},             /*   CLOCK_IP_QSPI_2XSFIF_EXTENSION  */
#elif defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
    {MC_CGM_MUX_10_CSC_SELCTL_MASK,         MC_CGM_MUX_10_CSC_SELCTL_SHIFT,         MC_CGM_MUX_10_DC_0_DIV_MASK,           MC_CGM_MUX_10_DC_0_DIV_SHIFT},             /*   CLOCK_IP_QSPI_SFCK_EXTENSION    */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,          MC_CGM_MUX_1_CSC_SELCTL_SHIFT,          MC_CGM_MUX_1_DC_0_DIV_MASK,            MC_CGM_MUX_1_DC_0_DIV_SHIFT},              /*   CLOCK_IP_STMA_EXTENSION  */
#if defined(CLOCK_IP_HAS_STMB_CLK)
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,          MC_CGM_MUX_2_CSC_SELCTL_SHIFT,          MC_CGM_MUX_2_DC_0_DIV_MASK,            MC_CGM_MUX_2_DC_0_DIV_SHIFT},              /*   CLOCK_IP_STMB_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
    {MC_CGM_MUX_13_CSC_SELCTL_MASK,         MC_CGM_MUX_13_CSC_SELCTL_SHIFT,         MC_CGM_MUX_13_DC_0_DIV_MASK,           MC_CGM_MUX_13_DC_0_DIV_SHIFT},             /*   CLOCK_IP_STMC_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
    {MC_CGM_MUX_16_CSC_SELCTL_MASK,         MC_CGM_MUX_16_CSC_SELCTL_SHIFT,         MC_CGM_MUX_16_DC_0_DIV_MASK,           MC_CGM_MUX_16_DC_0_DIV_SHIFT},             /*   CLOCK_IP_SWG_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
    {MC_CGM_MUX_11_CSC_SELCTL_MASK,         MC_CGM_MUX_11_CSC_SELCTL_SHIFT,         MC_CGM_MUX_11_DC_0_DIV_MASK,           MC_CGM_MUX_11_DC_0_DIV_SHIFT},             /*   CLOCK_IP_TRACE_EXTENSION  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_1_DIV_MASK,            MC_CGM_MUX_0_DC_1_DIV_SHIFT},              /*   CLOCK_IP_AIPS_PLAT_EXTENSION  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_2_DIV_MASK,            MC_CGM_MUX_0_DC_2_DIV_SHIFT},              /*   CLOCK_IP_AIPS_SLOW_EXTENSION  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_3_DIV_MASK,            MC_CGM_MUX_0_DC_3_DIV_SHIFT},              /*   CLOCK_IP_HSE_EXTENSION  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_4_DIV_MASK,            MC_CGM_MUX_0_DC_4_DIV_SHIFT},              /*   CLOCK_IP_DCM_EXTENSION  */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_5_DIV_MASK,            MC_CGM_MUX_0_DC_5_DIV_SHIFT},              /*   CLOCK_IP_LBIST_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
    {MC_CGM_MUX_14_CSC_SELCTL_MASK,         MC_CGM_MUX_14_CSC_SELCTL_SHIFT,         MC_CGM_MUX_14_DC_0_DIV_MASK,           MC_CGM_MUX_14_DC_0_DIV_SHIFT},             /*   CLOCK_IP_USDHC_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_0_DIV_MASK,            MC_CGM_MUX_0_DC_0_DIV_SHIFT},              /*   CLOCK_IP_CORE_EXTENSION  */
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_6_DIV_MASK,            MC_CGM_MUX_0_DC_6_DIV_SHIFT},              /*   CLOCK_IP_QSPI_MEM_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
    {MC_CGM_MUX_18_CSC_SELCTL_MASK,         MC_CGM_MUX_18_CSC_SELCTL_SHIFT,         MC_CGM_MUX_18_DC_0_DIV_MASK,           MC_CGM_MUX_18_DC_0_DIV_SHIFT},             /*   CLOCK_IP_STMD_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,          MC_CGM_MUX_7_CSC_SELCTL_SHIFT,          MC_CGM_MUX_7_DC_0_DIV_MASK,            MC_CGM_MUX_7_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC0_RX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,          MC_CGM_MUX_8_CSC_SELCTL_SHIFT,          MC_CGM_MUX_8_DC_0_DIV_MASK,            MC_CGM_MUX_8_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC0_TX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,          MC_CGM_MUX_9_CSC_SELCTL_SHIFT,          MC_CGM_MUX_9_DC_0_DIV_MASK,            MC_CGM_MUX_9_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC_TS_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
    {MC_CGM_MUX_12_CSC_SELCTL_MASK,         MC_CGM_MUX_12_CSC_SELCTL_SHIFT,         MC_CGM_MUX_12_DC_0_DIV_MASK,           MC_CGM_MUX_12_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC0_TX_RMII_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
    {MC_CGM_MUX_15_CSC_SELCTL_MASK,         MC_CGM_MUX_15_CSC_SELCTL_SHIFT,         MC_CGM_MUX_15_DC_0_DIV_MASK,           MC_CGM_MUX_15_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC1_RX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
    {MC_CGM_MUX_16_CSC_SELCTL_MASK,         MC_CGM_MUX_16_CSC_SELCTL_SHIFT,         MC_CGM_MUX_16_DC_0_DIV_MASK,           MC_CGM_MUX_16_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC1_TX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
    {MC_CGM_MUX_17_CSC_SELCTL_MASK,         MC_CGM_MUX_17_CSC_SELCTL_SHIFT,         MC_CGM_MUX_17_DC_0_DIV_MASK,           MC_CGM_MUX_17_DC_0_DIV_SHIFT},             /*   CLOCK_IP_GMAC1_MII_RMII_RGMII_TXENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
    {MC_CGM_MUX_19_CSC_SELCTL_MASK,         MC_CGM_MUX_19_CSC_SELCTL_SHIFT,         MC_CGM_MUX_19_DC_0_DIV_MASK,           MC_CGM_MUX_19_DC_0_DIV_SHIFT},             /*   CLOCK_IP_AES_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,          MC_CGM_MUX_0_CSC_SELCTL_SHIFT,          MC_CGM_MUX_0_DC_7_DIV_MASK,            MC_CGM_MUX_0_DC_7_DIV_SHIFT},              /*   CLOCK_IP_CM7_CORE_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,          MC_CGM_MUX_7_CSC_SELCTL_SHIFT,          MC_CGM_MUX_7_DC_0_DIV_MASK,            MC_CGM_MUX_7_DC_0_DIV_SHIFT},              /*   CLOCK_IP_GMAC_RX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,          MC_CGM_MUX_8_CSC_SELCTL_SHIFT,          MC_CGM_MUX_8_DC_0_DIV_MASK,            MC_CGM_MUX_8_DC_0_DIV_SHIFT},              /*   CLOCK_IP_GMAC_TX_EXTENSION  */
#else
    {0U,                                    0U,                                     0U,                                    0U},
#endif

};


Clock_Ip_GateInfoType const Clock_Ip_axGateInfo[CLOCK_IP_GATE_INFO_SIZE] =  {
    /* Partition value index           Selector value index              Request value shift                         Request value mask  */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ40_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK},        /*   ADC0_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ41_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK},        /*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ42_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK},        /*   ADC2_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ43_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ43_MASK},        /*   ADC3_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ52_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ52_MASK},        /*   ADC4_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ADC4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ53_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ53_MASK},        /*   ADC5_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ADC5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ54_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ54_MASK},        /*   ADC6_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ADC6_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ0_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ0_MASK},         /*   AXBS_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AXBS_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ1_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ1_MASK},         /*   AXBS0_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AXBS0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ2_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ2_MASK},         /*   AXBS1_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AXBS1_CLK clock            */
#endif
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ33_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK},        /*   BCTU0_CLK clock            */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ92_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ92_MASK},        /*   CMP0_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ93_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ93_MASK},        /*   CMP1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   CMP1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ58_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ58_MASK},        /*   CMP2_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   CMP2_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ96_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ96_MASK},        /*   CRC0_CLK clock             */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ32_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ32_MASK},        /*   DMAMUX0_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ33_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ33_MASK},        /*   DMAMUX1_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ3_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ3_MASK},         /*   EDMA0_CLK clock            */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ4_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ4_MASK},         /*   EDMA0_TCD0_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ5_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ5_MASK},         /*   EDMA0_TCD1_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ6_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ6_MASK},         /*   EDMA0_TCD2_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ7_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ7_MASK},         /*   EDMA0_TCD3_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ8_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ8_MASK},         /*   EDMA0_TCD4_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ9_SHIFT,         MC_ME_PRTN1_COFB0_CLKEN_REQ9_MASK},         /*   EDMA0_TCD5_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ10_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ10_MASK},        /*   EDMA0_TCD6_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ11_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ11_MASK},        /*   EDMA0_TCD7_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ12_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ12_MASK},        /*   EDMA0_TCD8_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ13_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ13_MASK},        /*   EDMA0_TCD9_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ14_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ14_MASK},        /*   EDMA0_TCD10_CLK clock      */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ15_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ15_MASK},        /*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ4_SHIFT,         MC_ME_PRTN2_COFB0_CLKEN_REQ4_MASK},         /*   EDMA0_TCD12_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ5_SHIFT,         MC_ME_PRTN2_COFB0_CLKEN_REQ5_MASK},         /*   EDMA0_TCD13_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ6_SHIFT,         MC_ME_PRTN2_COFB0_CLKEN_REQ6_MASK},         /*   EDMA0_TCD14_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ7_SHIFT,         MC_ME_PRTN2_COFB0_CLKEN_REQ7_MASK},         /*   EDMA0_TCD15_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ8_SHIFT,         MC_ME_PRTN2_COFB0_CLKEN_REQ8_MASK},         /*   EDMA0_TCD16_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ9_SHIFT,         MC_ME_PRTN2_COFB0_CLKEN_REQ9_MASK},         /*   EDMA0_TCD17_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ10_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ10_MASK},        /*   EDMA0_TCD18_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ11_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ11_MASK},        /*   EDMA0_TCD19_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ12_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ12_MASK},        /*   EDMA0_TCD20_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ13_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ13_MASK},        /*   EDMA0_TCD21_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ14_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ14_MASK},        /*   EDMA0_TCD22_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ15_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ15_MASK},        /*   EDMA0_TCD23_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ16_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ16_MASK},        /*   EDMA0_TCD24_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ17_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ17_MASK},        /*   EDMA0_TCD25_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ18_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ18_MASK},        /*   EDMA0_TCD26_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ19_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ19_MASK},        /*   EDMA0_TCD27_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ20_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ20_MASK},        /*   EDMA0_TCD28_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ21_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ21_MASK},        /*   EDMA0_TCD29_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ22_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ22_MASK},        /*   EDMA0_TCD30_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ23_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ23_MASK},        /*   EDMA0_TCD31_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ22_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ22_MASK},        /*   EIM_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EIM_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ67_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ67_MASK},        /*   EIM0_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ68_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ68_MASK},        /*   EIM1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ69_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ69_MASK},        /*   EIM2_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ32_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ32_MASK},        /*   EMAC0_RX_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EMAC0_RX_CLK clock         */
#endif
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ34_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK},        /*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ35_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ35_MASK},        /*   EMIOS1_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ36_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ36_MASK},        /*   EMIOS2_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EMIOS2_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ23_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ23_MASK},        /*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ3_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ3_MASK},         /*   ERM1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ERM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ97_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ97_MASK},        /*   FCCU_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FCCU_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ26_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ26_MASK},        /*   FLASH0_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLASH0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ27_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ27_MASK},        /*   FLASH0_ALT_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLASH0_ALT_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ59_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ59_MASK},        /*   FLASH1_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLASH1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ60_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ60_MASK},        /*   FLASH1_ALT_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLASH1_ALT_CLK clock       */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ65_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ65_MASK},        /*   FLEXCAN0_CLK clock         */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ66_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ66_MASK},        /*   FLEXCAN1_CLK clock         */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ67_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ67_MASK},        /*   FLEXCAN2_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ68_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ68_MASK},        /*   FLEXCAN3_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLEXCAN3_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ69_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ69_MASK},        /*   FLEXCAN4_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ70_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ70_MASK},        /*   FLEXCAN5_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLEXCAN5_CLK clock         */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ73_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ73_MASK},        /*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ99_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ99_MASK},        /*   HSE_MU0_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   HSE_MU0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ59_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ59_MASK},        /*   HSE_MU1_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   HSE_MU1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ101_SHIFT,       MC_ME_PRTN1_COFB3_CLKEN_REQ101_MASK},       /*   JDC_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   JDC_CLK clock              */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ31_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ31_MASK},        /*   INTM_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ38_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK},        /*   LCU0_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ39_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK},        /*   LCU1_CLK clock             */
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ84_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ84_MASK},        /*   LPI2C0_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPI2C0_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ85_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ85_MASK},        /*   LPI2C1_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ86_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ86_MASK},        /*   LPSPI0_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ87_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ87_MASK},        /*   LPSPI1_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ88_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ88_MASK},        /*   LPSPI2_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ89_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ89_MASK},        /*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ47_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ47_MASK},        /*   LPSPI4_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ48_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ48_MASK},        /*   LPSPI5_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPSPI5_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ74_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ74_MASK},        /*   LPUART0_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ75_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ75_MASK},        /*   LPUART1_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ76_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ76_MASK},        /*   LPUART2_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ77_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ77_MASK},        /*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ78_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ78_MASK},        /*   LPUART4_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ79_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ79_MASK},        /*   LPUART5_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ80_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ80_MASK},        /*   LPUART6_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ81_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ81_MASK},        /*   LPUART7_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ35_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ35_MASK},        /*   LPUART8_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ36_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ36_MASK},        /*   LPUART9_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ37_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ37_MASK},        /*   LPUART10_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ38_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ38_MASK},        /*   LPUART11_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ39_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ39_MASK},        /*   LPUART12_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ40_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ40_MASK},        /*   LPUART13_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ41_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ41_MASK},        /*   LPUART14_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ42_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ42_MASK},        /*   LPUART15_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART15_CLK clock         */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ24_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ24_MASK},        /*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MU2A_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ46_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ46_MASK},        /*   MU2A_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   MU2A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ47_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ47_MASK},        /*   MU2B_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   MU2B_CLK clock              */
#endif
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ44_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK},        /*   PIT0_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ45_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK},        /*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ63_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ63_MASK},        /*   PIT2_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ25_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ25_MASK},        /*   PRAMC0_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   PRAMC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ25_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ25_MASK},        /*   PRAMC1_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   PRAMC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ51_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ51_MASK},        /*   QSPI0_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   QSPI0_CLK clock            */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ34_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ34_MASK},        /*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ91_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ91_MASK},        /*   SAI0_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ55_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ55_MASK},        /*   SAI1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ24_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ24_MASK},        /*   SEMA42_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SEMA42_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ42_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ42_MASK},        /*   SIUL2_CLK clock            */
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ36_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ36_MASK},        /*   SIUL2_PDAC0_0_CLK clock    */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIUL2_PDAC0_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ37_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ37_MASK},        /*   SIUL2_PDAC0_1_CLK clock    */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIUL2_PDAC0_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ38_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ38_MASK},        /*   SIUL2_PDAC1_0_CLK clock    */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIUL2_PDAC1_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ39_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ39_MASK},        /*   SIUL2_PDAC1_1_CLK clock    */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIUL2_PDAC1_1_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ40_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ40_MASK},        /*   SIUL2_PDAC2_0_CLK clock    */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIUL2_PDAC2_0_CLK clock    */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ41_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ41_MASK},        /*   SIUL2_PDAC2_1_CLK clock    */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIUL2_PDAC2_1_CLK clock    */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ104_SHIFT,       MC_ME_PRTN1_COFB3_CLKEN_REQ104_MASK},       /*   STCU0_CLK clock            */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ29_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ29_MASK},        /*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STM1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ29_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ29_MASK},        /*   STM1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ30_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ30_MASK},        /*   STM2_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ50_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ50_MASK},        /*   SWG0_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ51_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ51_MASK},        /*   SWG1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SWG1_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ28_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ28_MASK},        /*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ27_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ27_MASK},        /*   SWT1_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SWT1_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ95_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ95_MASK},        /*   TEMPSENSE_CLK clock        */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ32_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK},        /*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ49_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ49_MASK},        /*   TSENSE0_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   TSENSE0_CLK clock          */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN1_COFB1_CLKEN_REQ45_SHIFT,        MC_ME_PRTN1_COFB1_CLKEN_REQ45_MASK},        /*   WKPU0_CLK clock            */
#if defined(CLOCK_IP_HAS_XRDC_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ30_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ30_MASK},        /*   XRDC_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   XRDC_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ57_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ57_MASK},        /*   USDHC_PER_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   USDHC_PER_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ71_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ71_MASK},        /*   FLEXCAN6_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLEXCAN6_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ72_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ72_MASK},        /*   FLEXCAN7_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   FLEXCAN7_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ28_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ28_MASK},        /*   SWT2_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SWT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ60_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ60_MASK},        /*   SIPI0_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SIPI0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK) || defined(CLOCK_IP_HAS_GMAC0_RX_CLK) || defined(CLOCK_IP_HAS_GMAC0_TX_CLK) || defined(CLOCK_IP_HAS_GMAC_TS_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ33_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ33_MASK},        /*   GMAC0_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   GMAC0_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ70_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ70_MASK},        /*   EIM3_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EIM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN2_COFB0_CLKEN_REQ31_SHIFT,        MC_ME_PRTN2_COFB0_CLKEN_REQ31_MASK},        /*   STM3_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   STM3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ28_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ28_MASK},        /*   SWT3_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SWT3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK) || defined(CLOCK_IP_HAS_GMAC1_RX_CLK) || defined(CLOCK_IP_HAS_GMAC1_TX_CLK) || defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN2_COFB1_CLKEN_REQ34_SHIFT,        MC_ME_PRTN2_COFB1_CLKEN_REQ34_MASK},        /*   GMAC1_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   GMAC1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN3_COFB2_CLKEN_REQ65_SHIFT,        MC_ME_PRTN3_COFB2_CLKEN_REQ65_MASK},        /*   ADCBIST_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ADCBIST_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ49_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ49_MASK},        /*   BCTU1_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   BCTU1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ58_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ58_MASK},        /*   COOLFLUX_D_RAM0_CLK clock  */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   COOLFLUX_D_RAM0_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ59_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ59_MASK},        /*   COOLFLUX_D_RAM1_CLK clock  */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   COOLFLUX_D_RAM1_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ55_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ55_MASK},        /*   COOLFLUX_DSP16L_CLK clock  */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   COOLFLUX_DSP16L_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ56_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ56_MASK},        /*   COOLFLUX_I_RAM0_CLK clock  */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   COOLFLUX_I_RAM0_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ57_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ57_MASK},        /*   COOLFLUX_I_RAM1_CLK clock  */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   COOLFLUX_I_RAM1_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ40_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ40_MASK},        /*   DMAMUX2_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   DMAMUX2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ41_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ41_MASK},        /*   DMAMUX3_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   DMAMUX3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ66_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ66_MASK},        /*   DSPI_MSC_CLK clock         */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   DSPI_MSC_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN1_COFB0_CLKEN_REQ21_SHIFT,        MC_ME_PRTN1_COFB0_CLKEN_REQ21_MASK},        /*   SDA_AP_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SDA_AP_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ4_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ4_MASK},         /*   EDMA1_CLK clock            */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ5_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ5_MASK},         /*   EDMA1_TCD0_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD0_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ6_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ6_MASK},         /*   EDMA1_TCD1_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD1_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ7_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ7_MASK},         /*   EDMA1_TCD2_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD2_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ8_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ8_MASK},         /*   EDMA1_TCD3_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD3_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ9_SHIFT,         MC_ME_PRTN0_COFB0_CLKEN_REQ9_MASK},         /*   EDMA1_TCD4_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD4_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ10_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ10_MASK},        /*   EDMA1_TCD5_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD5_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ11_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ11_MASK},        /*   EDMA1_TCD6_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD6_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ12_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ12_MASK},        /*   EDMA1_TCD7_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD7_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ13_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ13_MASK},        /*   EDMA1_TCD8_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD8_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ14_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ14_MASK},        /*   EDMA1_TCD9_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD9_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ15_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ15_MASK},        /*   EDMA1_TCD10_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD10_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ16_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ16_MASK},        /*   EDMA1_TCD11_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD11_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ17_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ17_MASK},        /*   EDMA1_TCD12_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ18_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ18_MASK},        /*   EDMA1_TCD13_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ19_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ19_MASK},        /*   EDMA1_TCD14_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN0_COFB0_CLKEN_REQ20_SHIFT,        MC_ME_PRTN0_COFB0_CLKEN_REQ20_MASK},        /*   EDMA1_TCD15_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ0_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ0_MASK},         /*   EDMA1_TCD16_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ1_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ1_MASK},         /*   EDMA1_TCD17_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ2_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ2_MASK},         /*   EDMA1_TCD18_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ3_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ3_MASK},         /*   EDMA1_TCD19_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ4_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ4_MASK},         /*   EDMA1_TCD20_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ5_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ5_MASK},         /*   EDMA1_TCD21_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ6_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ6_MASK},         /*   EDMA1_TCD22_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ7_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ7_MASK},         /*   EDMA1_TCD23_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ8_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ8_MASK},         /*   EDMA1_TCD24_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ9_SHIFT,         MC_ME_PRTN3_COFB0_CLKEN_REQ9_MASK},         /*   EDMA1_TCD25_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ10_SHIFT,        MC_ME_PRTN3_COFB0_CLKEN_REQ10_MASK},        /*   EDMA1_TCD26_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ11_SHIFT,        MC_ME_PRTN3_COFB0_CLKEN_REQ11_MASK},        /*   EDMA1_TCD27_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ12_SHIFT,        MC_ME_PRTN3_COFB0_CLKEN_REQ12_MASK},        /*   EDMA1_TCD28_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ13_SHIFT,        MC_ME_PRTN3_COFB0_CLKEN_REQ13_MASK},        /*   EDMA1_TCD29_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ14_SHIFT,        MC_ME_PRTN3_COFB0_CLKEN_REQ14_MASK},        /*   EDMA1_TCD30_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,      MC_ME_PRTN3_COFB0_CLKEN_REQ15_SHIFT,        MC_ME_PRTN3_COFB0_CLKEN_REQ15_MASK},        /*   EDMA1_TCD31_CLK clock      */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EDMA1_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ46_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ46_MASK},        /*   EFLEX_PWM0_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EFLEX_PWM0_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ47_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ47_MASK},        /*   EFLEX_PWM1_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   EFLEX_PWM1_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ32_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ32_MASK},        /*   ETPU_AB_REGISTERS_CLK clock*/
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ETPU_AB_REGISTERS_CLK clock*/
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ36_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ36_MASK},        /*   ETPU_CODE_RAM1_CLK clock   */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ETPU_CODE_RAM1_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ37_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ37_MASK},        /*   ETPU_CODE_RAM2_CLK clock   */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ETPU_CODE_RAM2_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ35_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ35_MASK},        /*   ETPU_RAM_MIRROR_CLK clock  */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ETPU_RAM_MIRROR_CLK clock  */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ34_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ34_MASK},        /*   ETPU_RAM_SDM_CLK clock     */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   ETPU_RAM_SDM_CLK clock     */
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ44_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ44_MASK},        /*   IGF0_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   IGF0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ65_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ65_MASK},        /*   LPUART_MSC_CLK clock       */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   LPUART_MSC_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ61_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ61_MASK},        /*   SDADC0_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SDADC0_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ62_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ62_MASK},        /*   SDADC1_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SDADC1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ63_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ63_MASK},        /*   SDADC2_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SDADC2_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN3_COFB2_CLKEN_REQ64_SHIFT,        MC_ME_PRTN3_COFB2_CLKEN_REQ64_MASK},        /*   SDADC3_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   SDADC3_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN3_COFB1_CLKEN_REQ48_SHIFT,        MC_ME_PRTN3_COFB1_CLKEN_REQ48_MASK},        /*   TRGMUX1_CLK clock           */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   TRGMUX1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN1_COFB2_CLKEN_REQ64_SHIFT,        MC_ME_PRTN1_COFB2_CLKEN_REQ64_MASK},        /*   PIT3_CLK clock             */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   PIT3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ112_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ112_MASK},      /*   AES_ACCEL_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_ACCEL_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ116_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ116_MASK},      /*   AES_APP0_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP0_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ120_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ120_MASK},      /*   AES_APP1_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP1_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,      MC_ME_PRTN1_COFB3_CLKEN_REQ124_SHIFT,        MC_ME_PRTN1_COFB3_CLKEN_REQ124_MASK},      /*   AES_APP2_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP2_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ72_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ72_MASK},        /*   AES_APP3_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP3_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ76_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ76_MASK},        /*   AES_APP4_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ80_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ80_MASK},        /*   AES_APP5_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ84_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ84_MASK},        /*   AES_APP6_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,      MC_ME_PRTN2_COFB2_CLKEN_REQ88_SHIFT,        MC_ME_PRTN2_COFB2_CLKEN_REQ88_MASK},        /*   AES_APP7_CLK clock          */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   AES_APP7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ49_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ49_MASK},        /*   MU3A_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   MU3A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ50_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ50_MASK},        /*   MU3B_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   MU3B_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ51_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ51_MASK},        /*   MU4A_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   MU4A_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,      MC_ME_PRTN0_COFB1_CLKEN_REQ52_SHIFT,        MC_ME_PRTN0_COFB1_CLKEN_REQ52_MASK},        /*   MU4B_CLK clock              */
#else
    {0U,                               0U,                               0U,                                         0U},                                        /*   MU4B_CLK clock              */
#endif

};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/




#ifdef __cplusplus
}
#endif

/** @} */
