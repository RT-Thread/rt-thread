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
*   @file       Clock_Ip_Frequency.c
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

#if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON))


/*==================================================================================================
*                                     SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_FREQUENCY_VENDOR_ID_C                      43
#define CLOCK_IP_FREQUENCY_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_FREQUENCY_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_FREQUENCY_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_FREQUENCY_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_FREQUENCY_SW_MINOR_VERSION_C               0
#define CLOCK_IP_FREQUENCY_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_FREQUENCY_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Frequency.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_FREQUENCY_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Frequency.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_FREQUENCY_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Frequency.c and Clock_Ip_Private.h are different"
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef struct{

    Clock_Ip_NameType Name;
    uint64 Frequency;

}extSignalFreq;

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


#define CLOCK_IP_SELECTOR_SOURCE_NO                        32U
#define CLOCK_IP_RTC_SELECTOR_SOURCE_NO                    4U
#define CLOCK_IP_FIRC_DIV_SEL_VALS_NO                      4U
#define CLOCK_IP_MUL_BY_16384                              14U
#define CLOCK_IP_MUL_BY_2048                               11U
#define CLOCK_IP_DISABLED                                  0U
#define CLOCK_IP_ENABLED                                   0xFFFFFFFFFFFFFFFU
#define CLOCK_IP_EXT_SIGNALS_NO                            6U
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
#define CLOCK_IP_EMAC_MII_RX_CLK_INDEX_ENTRY               0U
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
#define CLOCK_IP_EMAC_MII_RMII_TX_CLK_INDEX_ENTRY          1U
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
#define CLOCK_IP_GMAC_MII_RGMII_RX_CLK_INDEX_ENTRY               0U
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
#define CLOCK_IP_GMAC_MII_RMII_RGMII_TX_CLK_INDEX_ENTRY          1U
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
#define CLOCK_IP_GMAC0_MII_RGMII_RX_CLK_INDEX_ENTRY               0U
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
#define CLOCK_IP_GMAC0_MII_RMII_RGMII_TX_CLK_INDEX_ENTRY          1U
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
#define CLOCK_IP_LFAST_REF_EXT_CLK_INDEX_ENTRY             2U
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
#define CLOCK_IP_SWG_PAD_CLK_INDEX_ENTRY                   3U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
#define CLOCK_IP_GMAC1_MII_RGMII_RX_CLK_INDEX_ENTRY              4U
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
#define CLOCK_IP_GMAC1_MII_RMII_RGMII_TX_CLK_INDEX_ENTRY            5U
#endif

#define CLOCK_IP_PLL_CLK_FREQ                        2000000000U
#define CLOCK_IP_PLL_CLK_CHECKSUM                    4147U

#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
#define CLOCK_IP_PLLAUX_CLK_FREQ                     2000000000U
#define CLOCK_IP_PLLAUX_CLK_CHECKSUM                 4147U
#endif

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/



/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

static extSignalFreq Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EXT_SIGNALS_NO] =  {
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
{EMAC_MII_RX_CLK,0U},
#elif defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
{GMAC_MII_RGMII_RX_CLK,0U},
#elif defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
{GMAC0_MII_RGMII_RX_CLK,0U},
#else
{RESERVED_CLK,CLOCK_IP_EXT_SIGNALS_NO},
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
{EMAC_MII_RMII_TX_CLK,0U},
#elif defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
{GMAC_MII_RMII_RGMII_TX_CLK,0U},
#elif defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
{GMAC0_MII_RMII_RGMII_TX_CLK,0U},
#else
{RESERVED_CLK,CLOCK_IP_EXT_SIGNALS_NO},
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
{LFAST_REF_EXT_CLK,0U},
#else
{RESERVED_CLK,CLOCK_IP_EXT_SIGNALS_NO},
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
{SWG_PAD_CLK,0U},
#else
{RESERVED_CLK,CLOCK_IP_EXT_SIGNALS_NO},
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
{GMAC1_MII_RGMII_RX_CLK,0U},
#else
{RESERVED_CLK,CLOCK_IP_EXT_SIGNALS_NO},
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
{GMAC1_MII_RMII_RGMII_TX_CLK,0U},
#else
{RESERVED_CLK,CLOCK_IP_EXT_SIGNALS_NO},
#endif
};

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"





/* Clock stop constant section data */
#define MCU_START_SEC_VAR_INIT_32
#include "Mcu_MemMap.h"

/* External oscillators */
static uint64 Clock_Ip_u32fxosc = CLOCK_IP_DEFAULT_FXOSC_FREQUENCY;
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
static uint64 Clock_Ip_u32sxosc = CLOCK_IP_DEFAULT_SXOSC_FREQUENCY;
#endif
static uint64 Clock_Ip_u32PLL_CLKFreq                        = CLOCK_IP_PLL_CLK_FREQ;
static uint32 Clock_Ip_u32PLL_CLKChecksum                    = CLOCK_IP_PLL_CLK_CHECKSUM;
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
static uint64 Clock_Ip_u32PLLAUX_CLKFreq                     = CLOCK_IP_PLLAUX_CLK_FREQ;
static uint32 Clock_Ip_u32PLLAUX_CLKChecksum                 = CLOCK_IP_PLLAUX_CLK_CHECKSUM;
#endif

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_32
#include "Mcu_MemMap.h"

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

uint32 Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall(void);
static uint64 Clock_Ip_PLL_VCO(const PLL_Type *Base);
static uint64 Clock_Ip_Get_Zero_Frequency(void);
static uint64 Clock_Ip_Get_FIRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FIRC_STANDBY_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIRC_STANDBY_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FXOSC_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
static uint64 Clock_Ip_Get_SXOSC_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_PLL_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
static uint64 Clock_Ip_Get_PLLAUX_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency(void);

#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
static uint64 Clock_Ip_Get_PLLAUX_POSTDIV_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_PLL_PHI0_Frequency(void);
static uint64 Clock_Ip_Get_PLL_PHI1_Frequency(void);

#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
static uint64 Clock_Ip_Get_PLLAUX_PHI0_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
static uint64 Clock_Ip_Get_PLLAUX_PHI1_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
static uint64 Clock_Ip_Get_PLLAUX_PHI2_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
static uint64 Clock_Ip_Get_emac_mii_rx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
static uint64 Clock_Ip_Get_emac_mii_rmii_tx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
static uint64 Clock_Ip_Get_gmac_mii_rgmii_rx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
static uint64 Clock_Ip_Get_gmac_mii_rmii_rgmii_tx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
static uint64 Clock_Ip_Get_gmac0_mii_rgmii_rx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
static uint64 Clock_Ip_Get_gmac0_mii_rmii_rgmii_tx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
static uint64 Clock_Ip_Get_gmac1_mii_rgmii_rx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
static uint64 Clock_Ip_Get_gmac1_mii_rmii_rgmii_tx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
static uint64 Clock_Ip_Get_lfast_ext_ref_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
static uint64 Clock_Ip_Get_swg_pad_Frequency(void);
#endif
static uint64 Clock_Ip_Get_SCS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CORE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_AIPS_PLAT_CLK_Frequency(void);
static uint64 Clock_Ip_Get_AIPS_SLOW_CLK_Frequency(void);
static uint64 Clock_Ip_Get_HSE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DCM_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LBIST_CLK)
static uint64 Clock_Ip_Get_LBIST_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
static uint64 Clock_Ip_Get_QSPI_MEM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
static uint64 Clock_Ip_Get_CM7_CORE_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_CLKOUT_RUN_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ADC0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ADC1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_ADC2_CLK)
static uint64 Clock_Ip_Get_ADC2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
static uint64 Clock_Ip_Get_ADC3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
static uint64 Clock_Ip_Get_ADC4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
static uint64 Clock_Ip_Get_ADC5_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
static uint64 Clock_Ip_Get_ADC6_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
static uint64 Clock_Ip_Get_ADCBIST_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
static uint64 Clock_Ip_Get_AXBS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
static uint64 Clock_Ip_Get_AXBS0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
static uint64 Clock_Ip_Get_AXBS1_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_BCTU0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
static uint64 Clock_Ip_Get_BCTU1_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_CLKOUT_STANDBY_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CMP0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_CMP1_CLK)
static uint64 Clock_Ip_Get_CMP1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
static uint64 Clock_Ip_Get_CMP2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
static uint64 Clock_Ip_Get_COOLFLUX_D_RAM0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
static uint64 Clock_Ip_Get_COOLFLUX_D_RAM1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
static uint64 Clock_Ip_Get_COOLFLUX_DSP16L_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
static uint64 Clock_Ip_Get_COOLFLUX_I_RAM0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
static uint64 Clock_Ip_Get_COOLFLUX_I_RAM1_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_CRC0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMAMUX0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMAMUX1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
static uint64 Clock_Ip_Get_DMAMUX2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
static uint64 Clock_Ip_Get_DMAMUX3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
static uint64 Clock_Ip_Get_DSPI_MSC_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_EDMA0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD6_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD7_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD8_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD9_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD10_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_TCD11_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD12_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD13_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD14_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD15_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD16_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD17_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD18_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD19_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD20_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD21_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD22_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD23_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD24_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD25_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD26_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD27_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD28_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD29_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD30_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
static uint64 Clock_Ip_Get_EDMA0_TCD31_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
static uint64 Clock_Ip_Get_EDMA1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD5_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD6_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD7_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD8_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD9_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD10_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD11_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD12_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD13_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD14_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD15_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD16_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD17_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD18_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD19_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD20_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD21_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD22_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD23_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD24_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD25_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD26_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD27_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD28_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD29_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD30_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
static uint64 Clock_Ip_Get_EDMA1_TCD31_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
static uint64 Clock_Ip_Get_EFLEX_PWM0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
static uint64 Clock_Ip_Get_EFLEX_PWM1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
static uint64 Clock_Ip_Get_EIM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
static uint64 Clock_Ip_Get_EIM0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
static uint64 Clock_Ip_Get_EIM1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
static uint64 Clock_Ip_Get_EIM2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
static uint64 Clock_Ip_Get_EIM3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
static uint64 Clock_Ip_Get_GMAC0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK)
static uint64 Clock_Ip_Get_GMAC1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
static uint64 Clock_Ip_Get_GMAC0_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
static uint64 Clock_Ip_Get_GMAC0_TX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
static uint64 Clock_Ip_Get_GMAC_TS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
static uint64 Clock_Ip_Get_GMAC_TX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
static uint64 Clock_Ip_Get_GMAC_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
static uint64 Clock_Ip_Get_GMAC0_TX_RMII_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
static uint64 Clock_Ip_Get_GMAC1_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
static uint64 Clock_Ip_Get_GMAC1_TX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
static uint64 Clock_Ip_Get_GMAC1_RMII_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
static uint64 Clock_Ip_Get_AES_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
static uint64 Clock_Ip_Get_EMAC_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
static uint64 Clock_Ip_Get_EMAC0_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
static uint64 Clock_Ip_Get_EMAC_TS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
static uint64 Clock_Ip_Get_EMAC0_TS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
static uint64 Clock_Ip_Get_EMAC_TX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
static uint64 Clock_Ip_Get_EMAC0_TX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
static uint64 Clock_Ip_Get_EMAC_TX_RMII_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_EMIOS0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
static uint64 Clock_Ip_Get_EMIOS1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
static uint64 Clock_Ip_Get_EMIOS2_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_ERM0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_ERM1_CLK)
static uint64 Clock_Ip_Get_ERM1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
static uint64 Clock_Ip_Get_ETPU_AB_REGISTERS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
static uint64 Clock_Ip_Get_ETPU_CODE_RAM1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
static uint64 Clock_Ip_Get_ETPU_CODE_RAM2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
static uint64 Clock_Ip_Get_ETPU_RAM_MIRROR_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
static uint64 Clock_Ip_Get_ETPU_RAM_SDM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
static uint64 Clock_Ip_Get_FCCU_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
static uint64 Clock_Ip_Get_FLASH0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
static uint64 Clock_Ip_Get_FLASH0_ALT_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
static uint64 Clock_Ip_Get_FLASH1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
static uint64 Clock_Ip_Get_FLASH1_ALT_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_FLEXCANA_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN2_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
static uint64 Clock_Ip_Get_FLEXCANB_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
static uint64 Clock_Ip_Get_FLEXCAN3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
static uint64 Clock_Ip_Get_FLEXCAN4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
static uint64 Clock_Ip_Get_FLEXCAN5_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
static uint64 Clock_Ip_Get_FLEXCAN6_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
static uint64 Clock_Ip_Get_FLEXCAN7_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_FLEXIO0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
static uint64 Clock_Ip_Get_HSE_MU0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
static uint64 Clock_Ip_Get_HSE_MU1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
static uint64 Clock_Ip_Get_JDC_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
static uint64 Clock_Ip_Get_IGF0_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_INTM_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LCU0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LCU1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
static uint64 Clock_Ip_Get_LFAST_REF_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
static uint64 Clock_Ip_Get_LPI2C0_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_LPI2C1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPSPI0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPSPI1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPSPI2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPSPI3_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
static uint64 Clock_Ip_Get_LPSPI4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
static uint64 Clock_Ip_Get_LPSPI5_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_LPUART0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPUART1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPUART2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LPUART3_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
static uint64 Clock_Ip_Get_LPUART4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
static uint64 Clock_Ip_Get_LPUART5_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
static uint64 Clock_Ip_Get_LPUART6_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
static uint64 Clock_Ip_Get_LPUART7_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
static uint64 Clock_Ip_Get_LPUART8_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
static uint64 Clock_Ip_Get_LPUART9_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
static uint64 Clock_Ip_Get_LPUART10_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
static uint64 Clock_Ip_Get_LPUART11_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
static uint64 Clock_Ip_Get_LPUART12_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
static uint64 Clock_Ip_Get_LPUART13_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
static uint64 Clock_Ip_Get_LPUART14_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
static uint64 Clock_Ip_Get_LPUART15_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
static uint64 Clock_Ip_Get_LPUART_MSC_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_MSCM_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_MU2A_CLK)
static uint64 Clock_Ip_Get_MU2A_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
static uint64 Clock_Ip_Get_MU2B_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
static uint64 Clock_Ip_Get_MU3A_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
static uint64 Clock_Ip_Get_MU3B_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
static uint64 Clock_Ip_Get_MU4A_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
static uint64 Clock_Ip_Get_MU4B_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_PIT0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PIT1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_PIT2_CLK)
static uint64 Clock_Ip_Get_PIT2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
static uint64 Clock_Ip_Get_PIT3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
static uint64 Clock_Ip_Get_PRAMC0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
static uint64 Clock_Ip_Get_PRAMC1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
static uint64 Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
static uint64 Clock_Ip_Get_QSPI0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
static uint64 Clock_Ip_Get_QSPI0_RAM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
static uint64 Clock_Ip_Get_QSPI0_TX_MEM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
static uint64 Clock_Ip_Get_QSPI_SFCK_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_RTC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTC0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SAI0_CLK)
static uint64 Clock_Ip_Get_SAI0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
static uint64 Clock_Ip_Get_SAI1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
static uint64 Clock_Ip_Get_SDA_AP_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
static uint64 Clock_Ip_Get_SDADC0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
static uint64 Clock_Ip_Get_SDADC1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
static uint64 Clock_Ip_Get_SDADC2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
static uint64 Clock_Ip_Get_SDADC3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
static uint64 Clock_Ip_Get_SEMA42_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
static uint64 Clock_Ip_Get_SIPI0_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_SIUL2_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
static uint64 Clock_Ip_Get_SIUL2_PDAC0_0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
static uint64 Clock_Ip_Get_SIUL2_PDAC0_1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
static uint64 Clock_Ip_Get_SIUL2_PDAC1_0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
static uint64 Clock_Ip_Get_SIUL2_PDAC1_1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
static uint64 Clock_Ip_Get_SIUL2_PDAC2_0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
static uint64 Clock_Ip_Get_SIUL2_PDAC2_1_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_STCU0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_STMA_CLK_Frequency(void);
static uint64 Clock_Ip_Get_STM0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_STMB_CLK)
static uint64 Clock_Ip_Get_STMB_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
static uint64 Clock_Ip_Get_STM1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
static uint64 Clock_Ip_Get_STMC_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
static uint64 Clock_Ip_Get_STM2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
static uint64 Clock_Ip_Get_STMD_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
static uint64 Clock_Ip_Get_STM3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
static uint64 Clock_Ip_Get_USDHC_PER_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
static uint64 Clock_Ip_Get_SWG_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
static uint64 Clock_Ip_Get_SWG0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
static uint64 Clock_Ip_Get_SWG1_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_SWT0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SWT1_CLK)
static uint64 Clock_Ip_Get_SWT1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
static uint64 Clock_Ip_Get_SWT2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
static uint64 Clock_Ip_Get_SWT3_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_TEMPSENSE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_TRACE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_TRGMUX0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
static uint64 Clock_Ip_Get_TRGMUX1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
static uint64 Clock_Ip_Get_TSENSE0_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_WKPU0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_XRDC_CLK)
static uint64 Clock_Ip_Get_XRDC_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
static uint64 Clock_Ip_Get_AES_ACCEL_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
static uint64 Clock_Ip_Get_AES_APP0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
static uint64 Clock_Ip_Get_AES_APP1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
static uint64 Clock_Ip_Get_AES_APP2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
static uint64 Clock_Ip_Get_AES_APP3_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
static uint64 Clock_Ip_Get_AES_APP4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
static uint64 Clock_Ip_Get_AES_APP5_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
static uint64 Clock_Ip_Get_AES_APP6_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
static uint64 Clock_Ip_Get_AES_APP7_CLK_Frequency(void);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

typedef uint64 (*getFreqType)(void);
static const getFreqType Clock_Ip_apfFreqTableClkSrc[CLOCK_IP_SELECTOR_SOURCE_NO] =
{
    &Clock_Ip_Get_FIRC_CLK_Frequency,                      /* clock name for 0  hardware value */
    &Clock_Ip_Get_SIRC_CLK_Frequency,                      /* clock name for 1  hardware value */
    &Clock_Ip_Get_FXOSC_CLK_Frequency,                     /* clock name for 2  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 3  hardware value */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    &Clock_Ip_Get_SXOSC_CLK_Frequency,                     /* clock name for 4  hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 5  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 6  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 7  hardware value */
    &Clock_Ip_Get_PLL_PHI0_Frequency,
    &Clock_Ip_Get_PLL_PHI1_Frequency,
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 10 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 11 hardware value */
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
    &Clock_Ip_Get_PLLAUX_PHI0_Frequency,
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
    &Clock_Ip_Get_PLLAUX_PHI1_Frequency,
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
    &Clock_Ip_Get_PLLAUX_PHI2_Frequency,
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 15 hardware value */
    &Clock_Ip_Get_CORE_CLK_Frequency,                      /* clock name for 16 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 17 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 18 hardware value */
    &Clock_Ip_Get_HSE_CLK_Frequency,                       /* clock name for 19 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 20 hardware value */
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    &Clock_Ip_Get_CM7_CORE_CLK_Frequency,                  /* clock name for 21 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
    &Clock_Ip_Get_AIPS_PLAT_CLK_Frequency,                 /* clock name for 22 hardware value */
    &Clock_Ip_Get_AIPS_SLOW_CLK_Frequency,                 /* clock name for 23 hardware value */
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
    &Clock_Ip_Get_emac_mii_rmii_tx_Frequency,              /* clock name for 24 hardware value */
#elif defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
    &Clock_Ip_Get_gmac_mii_rmii_rgmii_tx_Frequency,              /* clock name for 24 hardware value */
#elif defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
    &Clock_Ip_Get_gmac0_mii_rmii_rgmii_tx_Frequency,              /* clock name for 24 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
    &Clock_Ip_Get_emac_mii_rx_Frequency,                   /* clock name for 25 hardware value */
#elif defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
    &Clock_Ip_Get_gmac_mii_rgmii_rx_Frequency,                   /* clock name for 25 hardware value */
#elif defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
    &Clock_Ip_Get_gmac0_mii_rgmii_rx_Frequency,                   /* clock name for 25 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 26 hardware value */
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
    &Clock_Ip_Get_lfast_ext_ref_Frequency,                 /* clock name for 27 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
    &Clock_Ip_Get_swg_pad_Frequency,                       /* clock name for 28 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
    &Clock_Ip_Get_gmac1_mii_rgmii_rx_Frequency,                   /* clock name for 29 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
    &Clock_Ip_Get_gmac1_mii_rmii_rgmii_tx_Frequency,                 /* clock name for 30 hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 31 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableRTC_CLK[CLOCK_IP_RTC_SELECTOR_SOURCE_NO] =
{
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    &Clock_Ip_Get_SXOSC_CLK_Frequency,                     /* clock name for 0  hardware value */
#else
    &Clock_Ip_Get_Zero_Frequency,
#endif
    &Clock_Ip_Get_SIRC_CLK_Frequency,                      /* clock name for 1  hardware value */
    &Clock_Ip_Get_FIRC_CLK_Frequency,                      /* clock name for 2  hardware value */
    &Clock_Ip_Get_FXOSC_CLK_Frequency,                     /* clock name for 3  hardware value */
};

static const getFreqType Clock_Ip_apfFreqTable[CLOCK_IP_NAMES_NO] =
{
    &Clock_Ip_Get_Zero_Frequency,                                    /* CLOCK_IS_OFF                 */
    &Clock_Ip_Get_FIRC_CLK_Frequency,                                /* FIRC_CLK                     */
    &Clock_Ip_Get_FIRC_STANDBY_CLK_Frequency,                        /* FIRC_STANDBY_CLK             */
    &Clock_Ip_Get_SIRC_CLK_Frequency,                                /* SIRC_CLK                     */
    &Clock_Ip_Get_SIRC_STANDBY_CLK_Frequency,                        /* SIRC_STANDBY_CLK             */
    &Clock_Ip_Get_FXOSC_CLK_Frequency,                               /* FXOSC_CLK                    */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    &Clock_Ip_Get_SXOSC_CLK_Frequency,                               /* SXOSC_CLK                    */
#endif
    &Clock_Ip_Get_PLL_CLK_Frequency,
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    &Clock_Ip_Get_PLLAUX_CLK_Frequency,
#endif
    &Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency,
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
    &Clock_Ip_Get_PLLAUX_POSTDIV_CLK_Frequency,
#endif
    &Clock_Ip_Get_PLL_PHI0_Frequency,
    &Clock_Ip_Get_PLL_PHI1_Frequency,
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
    &Clock_Ip_Get_PLLAUX_PHI0_Frequency,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
    &Clock_Ip_Get_PLLAUX_PHI1_Frequency,
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
    &Clock_Ip_Get_PLLAUX_PHI2_Frequency,
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
    &Clock_Ip_Get_emac_mii_rx_Frequency,                             /* emac_mii_rx                  */
#elif defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
    &Clock_Ip_Get_gmac_mii_rgmii_rx_Frequency,                             /* gmac_mii_rgmii_rx                  */
#elif defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
    &Clock_Ip_Get_gmac0_mii_rgmii_rx_Frequency,                             /* gmac0_mii_rgmii_rx                  */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
    &Clock_Ip_Get_emac_mii_rmii_tx_Frequency,                        /* emac_mii_rmii_tx             */
#elif defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
    &Clock_Ip_Get_gmac_mii_rmii_rgmii_tx_Frequency,                        /* gmac_mii_rmii_rgmii_tx             */
#elif defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
    &Clock_Ip_Get_gmac0_mii_rmii_rgmii_tx_Frequency,                        /* gmac0_mii_rmii_rgmii_tx             */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
    &Clock_Ip_Get_gmac1_mii_rgmii_rx_Frequency,                             /* gmac1_mii_rgmii_rx                  */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
    &Clock_Ip_Get_gmac1_mii_rmii_rgmii_tx_Frequency,                             /* gmac1_mii_rmii_rgmii_tx                  */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
    &Clock_Ip_Get_lfast_ext_ref_Frequency,                           /* lfast_ext_ref                */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
    &Clock_Ip_Get_swg_pad_Frequency,                                 /* swg_pad                      */
#endif
    &Clock_Ip_Get_SCS_CLK_Frequency,                                 /* SCS_CLK                      */
    &Clock_Ip_Get_CORE_CLK_Frequency,                                /* CORE_CLK                     */
    &Clock_Ip_Get_AIPS_PLAT_CLK_Frequency,                           /* AIPS_PLAT_CLK                */
    &Clock_Ip_Get_AIPS_SLOW_CLK_Frequency,                           /* AIPS_SLOW_CLK                */
    &Clock_Ip_Get_HSE_CLK_Frequency,                                 /* HSE_CLK                      */
    &Clock_Ip_Get_DCM_CLK_Frequency,                                 /* DCM_CLK                      */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    &Clock_Ip_Get_LBIST_CLK_Frequency,                               /* LBIST_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    &Clock_Ip_Get_QSPI_MEM_CLK_Frequency,                            /* QSPI_MEM_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    &Clock_Ip_Get_CM7_CORE_CLK_Frequency,                            /* CM7_CORE_CLK                 */
#endif
    &Clock_Ip_Get_CLKOUT_RUN_CLK_Frequency,                          /* CLKOUT_RUN_CLK               */
    &Clock_Ip_Get_Zero_Frequency,                                    /* THE_LAST_PRODUCER_CLK         */
    &Clock_Ip_Get_ADC0_CLK_Frequency,                                /* ADC0_CLK                     */
    &Clock_Ip_Get_ADC1_CLK_Frequency,                                /* ADC1_CLK                     */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
    &Clock_Ip_Get_ADC2_CLK_Frequency,                                /* ADC2_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
    &Clock_Ip_Get_ADC3_CLK_Frequency,                                /* ADC3_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
    &Clock_Ip_Get_ADC4_CLK_Frequency,                                /* ADC4_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
    &Clock_Ip_Get_ADC5_CLK_Frequency,                                /* ADC5_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
    &Clock_Ip_Get_ADC6_CLK_Frequency,                                /* ADC6_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
    &Clock_Ip_Get_ADCBIST_CLK_Frequency,                             /* ADCBIST_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
    &Clock_Ip_Get_AES_ACCEL_CLK_Frequency,                            /* AES_ACCEL_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
    &Clock_Ip_Get_AES_APP0_CLK_Frequency,                             /* AES_APP0_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
    &Clock_Ip_Get_AES_APP1_CLK_Frequency,                             /* AES_APP1_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
    &Clock_Ip_Get_AES_APP2_CLK_Frequency,                             /* AES_APP2_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
    &Clock_Ip_Get_AES_APP3_CLK_Frequency,                             /* AES_APP3_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
    &Clock_Ip_Get_AES_APP4_CLK_Frequency,                             /* AES_APP4_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
    &Clock_Ip_Get_AES_APP5_CLK_Frequency,                             /* AES_APP5_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
    &Clock_Ip_Get_AES_APP6_CLK_Frequency,                             /* AES_APP6_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
    &Clock_Ip_Get_AES_APP7_CLK_Frequency,                             /* AES_APP7_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_AES_CLK)
    &Clock_Ip_Get_AES_CLK_Frequency,                                /* AES_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_AXBS_CLK)
    &Clock_Ip_Get_AXBS_CLK_Frequency,                                /* AXBS_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
    &Clock_Ip_Get_AXBS0_CLK_Frequency,                               /* AXBS0_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
    &Clock_Ip_Get_AXBS1_CLK_Frequency,                               /* AXBS1_CLK                    */
#endif
    &Clock_Ip_Get_BCTU0_CLK_Frequency,                               /* BCTU0_CLK                    */
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
    &Clock_Ip_Get_BCTU1_CLK_Frequency,                               /* BCTU1_CLK                    */
#endif
    &Clock_Ip_Get_CLKOUT_STANDBY_CLK_Frequency,                      /* CLKOUT_STANDBY_CLK           */
    &Clock_Ip_Get_CMP0_CLK_Frequency,                                /* CMP0_CLK                     */
#if defined(CLOCK_IP_HAS_CMP1_CLK)
    &Clock_Ip_Get_CMP1_CLK_Frequency,                                /* CMP1_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
    &Clock_Ip_Get_CMP2_CLK_Frequency,                                /* CMP2_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
    &Clock_Ip_Get_COOLFLUX_D_RAM0_CLK_Frequency,                    /* COOLFLUX_D_RAM0_CLK           */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
    &Clock_Ip_Get_COOLFLUX_D_RAM1_CLK_Frequency,                    /* COOLFLUX_D_RAM1_CLK           */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
    &Clock_Ip_Get_COOLFLUX_DSP16L_CLK_Frequency,                    /* COOLFLUX_DSP16L_CLK           */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
    &Clock_Ip_Get_COOLFLUX_I_RAM0_CLK_Frequency,                    /* COOLFLUX_I_RAM0_CLK           */
#endif
#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
    &Clock_Ip_Get_COOLFLUX_I_RAM1_CLK_Frequency,                    /* COOLFLUX_I_RAM1_CLK           */
#endif
    &Clock_Ip_Get_CRC0_CLK_Frequency,                                /* CRC0_CLK                     */
    &Clock_Ip_Get_DCM_CLK_Frequency,                                 /* DCM0_CLK                     */
    &Clock_Ip_Get_DMAMUX0_CLK_Frequency,                             /* DMAMUX0_CLK                  */
    &Clock_Ip_Get_DMAMUX1_CLK_Frequency,                             /* DMAMUX1_CLK                  */
#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
    &Clock_Ip_Get_DMAMUX2_CLK_Frequency,                             /* DMAMUX2_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
    &Clock_Ip_Get_DMAMUX3_CLK_Frequency,                             /* DMAMUX3_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
    &Clock_Ip_Get_DSPI_MSC_CLK_Frequency,                            /* DSPI_MSC_CLK                 */
#endif
    &Clock_Ip_Get_EDMA0_CLK_Frequency,                               /* EDMA0_CLK                    */
    &Clock_Ip_Get_EDMA0_TCD0_CLK_Frequency,                          /* EDMA0_TCD0_CLK               */
    &Clock_Ip_Get_EDMA0_TCD1_CLK_Frequency,                          /* EDMA0_TCD1_CLK               */
    &Clock_Ip_Get_EDMA0_TCD2_CLK_Frequency,                          /* EDMA0_TCD2_CLK               */
    &Clock_Ip_Get_EDMA0_TCD3_CLK_Frequency,                          /* EDMA0_TCD3_CLK               */
    &Clock_Ip_Get_EDMA0_TCD4_CLK_Frequency,                          /* EDMA0_TCD4_CLK               */
    &Clock_Ip_Get_EDMA0_TCD5_CLK_Frequency,                          /* EDMA0_TCD5_CLK               */
    &Clock_Ip_Get_EDMA0_TCD6_CLK_Frequency,                          /* EDMA0_TCD6_CLK               */
    &Clock_Ip_Get_EDMA0_TCD7_CLK_Frequency,                          /* EDMA0_TCD7_CLK               */
    &Clock_Ip_Get_EDMA0_TCD8_CLK_Frequency,                          /* EDMA0_TCD8_CLK               */
    &Clock_Ip_Get_EDMA0_TCD9_CLK_Frequency,                          /* EDMA0_TCD9_CLK               */
    &Clock_Ip_Get_EDMA0_TCD10_CLK_Frequency,                         /* EDMA0_TCD10_CLK              */
    &Clock_Ip_Get_EDMA0_TCD11_CLK_Frequency,                         /* EDMA0_TCD11_CLK              */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
    &Clock_Ip_Get_EDMA0_TCD12_CLK_Frequency,                         /* EDMA0_TCD12_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
    &Clock_Ip_Get_EDMA0_TCD13_CLK_Frequency,                         /* EDMA0_TCD13_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
    &Clock_Ip_Get_EDMA0_TCD14_CLK_Frequency,                         /* EDMA0_TCD14_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
    &Clock_Ip_Get_EDMA0_TCD15_CLK_Frequency,                         /* EDMA0_TCD15_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
    &Clock_Ip_Get_EDMA0_TCD16_CLK_Frequency,                         /* EDMA0_TCD16_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
    &Clock_Ip_Get_EDMA0_TCD17_CLK_Frequency,                         /* EDMA0_TCD17_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
    &Clock_Ip_Get_EDMA0_TCD18_CLK_Frequency,                         /* EDMA0_TCD18_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
    &Clock_Ip_Get_EDMA0_TCD19_CLK_Frequency,                         /* EDMA0_TCD19_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
    &Clock_Ip_Get_EDMA0_TCD20_CLK_Frequency,                         /* EDMA0_TCD20_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
    &Clock_Ip_Get_EDMA0_TCD21_CLK_Frequency,                         /* EDMA0_TCD21_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
    &Clock_Ip_Get_EDMA0_TCD22_CLK_Frequency,                         /* EDMA0_TCD22_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
    &Clock_Ip_Get_EDMA0_TCD23_CLK_Frequency,                         /* EDMA0_TCD23_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
    &Clock_Ip_Get_EDMA0_TCD24_CLK_Frequency,                         /* EDMA0_TCD24_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
    &Clock_Ip_Get_EDMA0_TCD25_CLK_Frequency,                         /* EDMA0_TCD25_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
    &Clock_Ip_Get_EDMA0_TCD26_CLK_Frequency,                         /* EDMA0_TCD26_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
    &Clock_Ip_Get_EDMA0_TCD27_CLK_Frequency,                         /* EDMA0_TCD27_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
    &Clock_Ip_Get_EDMA0_TCD28_CLK_Frequency,                         /* EDMA0_TCD28_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
    &Clock_Ip_Get_EDMA0_TCD29_CLK_Frequency,                         /* EDMA0_TCD29_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
    &Clock_Ip_Get_EDMA0_TCD30_CLK_Frequency,                         /* EDMA0_TCD30_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
    &Clock_Ip_Get_EDMA0_TCD31_CLK_Frequency,                         /* EDMA0_TCD31_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
    &Clock_Ip_Get_EDMA1_CLK_Frequency,                               /* EDMA1_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
    &Clock_Ip_Get_EDMA1_TCD0_CLK_Frequency,                          /* EDMA1_TCD0_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
    &Clock_Ip_Get_EDMA1_TCD1_CLK_Frequency,                          /* EDMA1_TCD1_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
    &Clock_Ip_Get_EDMA1_TCD2_CLK_Frequency,                          /* EDMA1_TCD2_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
    &Clock_Ip_Get_EDMA1_TCD3_CLK_Frequency,                          /* EDMA1_TCD3_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
    &Clock_Ip_Get_EDMA1_TCD4_CLK_Frequency,                          /* EDMA1_TCD4_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
    &Clock_Ip_Get_EDMA1_TCD5_CLK_Frequency,                          /* EDMA1_TCD5_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
    &Clock_Ip_Get_EDMA1_TCD6_CLK_Frequency,                          /* EDMA1_TCD6_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
    &Clock_Ip_Get_EDMA1_TCD7_CLK_Frequency,                          /* EDMA1_TCD7_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
    &Clock_Ip_Get_EDMA1_TCD8_CLK_Frequency,                          /* EDMA1_TCD8_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
    &Clock_Ip_Get_EDMA1_TCD9_CLK_Frequency,                          /* EDMA1_TCD9_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
    &Clock_Ip_Get_EDMA1_TCD10_CLK_Frequency,                         /* EDMA1_TCD10_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
    &Clock_Ip_Get_EDMA1_TCD11_CLK_Frequency,                         /* EDMA1_TCD11_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
    &Clock_Ip_Get_EDMA1_TCD12_CLK_Frequency,                         /* EDMA1_TCD12_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
    &Clock_Ip_Get_EDMA1_TCD13_CLK_Frequency,                         /* EDMA1_TCD13_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
    &Clock_Ip_Get_EDMA1_TCD14_CLK_Frequency,                         /* EDMA1_TCD14_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
    &Clock_Ip_Get_EDMA1_TCD15_CLK_Frequency,                         /* EDMA1_TCD15_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
    &Clock_Ip_Get_EDMA1_TCD16_CLK_Frequency,                         /* EDMA1_TCD16_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
    &Clock_Ip_Get_EDMA1_TCD17_CLK_Frequency,                         /* EDMA1_TCD17_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
    &Clock_Ip_Get_EDMA1_TCD18_CLK_Frequency,                         /* EDMA1_TCD18_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
    &Clock_Ip_Get_EDMA1_TCD19_CLK_Frequency,                         /* EDMA1_TCD19_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
    &Clock_Ip_Get_EDMA1_TCD20_CLK_Frequency,                         /* EDMA1_TCD20_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
    &Clock_Ip_Get_EDMA1_TCD21_CLK_Frequency,                         /* EDMA1_TCD21_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
    &Clock_Ip_Get_EDMA1_TCD22_CLK_Frequency,                         /* EDMA1_TCD22_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
    &Clock_Ip_Get_EDMA1_TCD23_CLK_Frequency,                         /* EDMA1_TCD23_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
    &Clock_Ip_Get_EDMA1_TCD24_CLK_Frequency,                         /* EDMA1_TCD24_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
    &Clock_Ip_Get_EDMA1_TCD25_CLK_Frequency,                         /* EDMA1_TCD25_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
    &Clock_Ip_Get_EDMA1_TCD26_CLK_Frequency,                         /* EDMA1_TCD26_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
    &Clock_Ip_Get_EDMA1_TCD27_CLK_Frequency,                         /* EDMA1_TCD27_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
    &Clock_Ip_Get_EDMA1_TCD28_CLK_Frequency,                         /* EDMA1_TCD28_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
    &Clock_Ip_Get_EDMA1_TCD29_CLK_Frequency,                         /* EDMA1_TCD29_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
    &Clock_Ip_Get_EDMA1_TCD30_CLK_Frequency,                         /* EDMA1_TCD30_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
    &Clock_Ip_Get_EDMA1_TCD31_CLK_Frequency,                         /* EDMA1_TCD31_CLK              */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
    &Clock_Ip_Get_EFLEX_PWM0_CLK_Frequency,                         /* EFLEX_PWM0_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
    &Clock_Ip_Get_EFLEX_PWM1_CLK_Frequency,                         /* EFLEX_PWM1_CLK               */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
    &Clock_Ip_Get_EIM_CLK_Frequency,                                 /* EIM_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
    &Clock_Ip_Get_EIM0_CLK_Frequency,                                /* EIM0_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
    &Clock_Ip_Get_EIM1_CLK_Frequency,                                /* EIM1_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
    &Clock_Ip_Get_EIM2_CLK_Frequency,                                /* EIM2_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
    &Clock_Ip_Get_EIM3_CLK_Frequency,                                /* EIM3_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
    &Clock_Ip_Get_EMAC_RX_CLK_Frequency,                             /* EMAC_RX_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
    &Clock_Ip_Get_GMAC_RX_CLK_Frequency,                             /* GMAC_RX_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
    &Clock_Ip_Get_EMAC0_RX_CLK_Frequency,                            /* EMAC0_RX_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
    &Clock_Ip_Get_EMAC_TS_CLK_Frequency,                             /* EMAC_TS_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
    &Clock_Ip_Get_EMAC0_TS_CLK_Frequency,                            /* EMAC0_TS_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
    &Clock_Ip_Get_EMAC_TX_CLK_Frequency,                             /* EMAC_TX_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
    &Clock_Ip_Get_GMAC_TX_CLK_Frequency,                             /* GMAC_TX_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
    &Clock_Ip_Get_EMAC0_TX_CLK_Frequency,                            /* EMAC0_TX_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
    &Clock_Ip_Get_EMAC_TX_RMII_CLK_Frequency,                        /* EMAC_TX_RMII_CLK             */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_RMII_CLK)
    &Clock_Ip_Get_EMAC_TX_RMII_CLK_Frequency,                        /* EMAC0_TX_RMII_CLK            */
#endif
    &Clock_Ip_Get_EMIOS0_CLK_Frequency,                              /* EMIOS0_CLK                   */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
    &Clock_Ip_Get_EMIOS1_CLK_Frequency,                              /* EMIOS1_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
    &Clock_Ip_Get_EMIOS2_CLK_Frequency,                              /* EMIOS2_CLK                   */
#endif
    &Clock_Ip_Get_ERM0_CLK_Frequency,                                /* ERM0_CLK                     */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
    &Clock_Ip_Get_ERM1_CLK_Frequency,                                /* ERM1_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
    &Clock_Ip_Get_ETPU_AB_REGISTERS_CLK_Frequency,                   /* ETPU_AB_REGISTERS_CLK        */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
    &Clock_Ip_Get_ETPU_CODE_RAM1_CLK_Frequency,                      /* ETPU_CODE_RAM1_CLK           */
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
    &Clock_Ip_Get_ETPU_CODE_RAM2_CLK_Frequency,                      /* ETPU_CODE_RAM2_CLK           */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
    &Clock_Ip_Get_ETPU_RAM_MIRROR_CLK_Frequency,                     /* ETPU_RAM_MIRROR_CLK          */
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
    &Clock_Ip_Get_ETPU_RAM_SDM_CLK_Frequency,                        /* ETPU_RAM_SDM_CLK             */
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
    &Clock_Ip_Get_FCCU_CLK_Frequency,                                /* FCCU_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
    &Clock_Ip_Get_FLASH0_CLK_Frequency,                              /* FLASH0_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
    &Clock_Ip_Get_FLASH0_ALT_CLK_Frequency,                          /* FLASH0_ALT_CLK               */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
    &Clock_Ip_Get_FLASH1_CLK_Frequency,                              /* FLASH1_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
    &Clock_Ip_Get_FLASH1_ALT_CLK_Frequency,                          /* FLASH1_ALT_CLK               */
#endif
    &Clock_Ip_Get_FLEXCANA_CLK_Frequency,                            /* FLEXCANA_CLK                 */
    &Clock_Ip_Get_FLEXCAN0_CLK_Frequency,                            /* FLEXCAN0_CLK                 */
    &Clock_Ip_Get_FLEXCAN1_CLK_Frequency,                            /* FLEXCAN1_CLK                 */
    &Clock_Ip_Get_FLEXCAN2_CLK_Frequency,                            /* FLEXCAN2_CLK                 */
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
    &Clock_Ip_Get_FLEXCANB_CLK_Frequency,                            /* FLEXCANB_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
    &Clock_Ip_Get_FLEXCAN3_CLK_Frequency,                            /* FLEXCAN3_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
    &Clock_Ip_Get_FLEXCAN4_CLK_Frequency,                            /* FLEXCAN4_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
    &Clock_Ip_Get_FLEXCAN5_CLK_Frequency,                            /* FLEXCAN5_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
    &Clock_Ip_Get_FLEXCAN6_CLK_Frequency,                            /* FLEXCAN6_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
    &Clock_Ip_Get_FLEXCAN7_CLK_Frequency,                            /* FLEXCAN7_CLK                 */
#endif
    &Clock_Ip_Get_FLEXIO0_CLK_Frequency,                             /* FLEXIO0_CLK                  */
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
    &Clock_Ip_Get_HSE_MU0_CLK_Frequency,                             /* HSE_MU0_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
    &Clock_Ip_Get_HSE_MU1_CLK_Frequency,                             /* HSE_MU1_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
    &Clock_Ip_Get_JDC_CLK_Frequency,                                 /* JDC_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
    &Clock_Ip_Get_IGF0_CLK_Frequency,                                /* IGF0_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
    &Clock_Ip_Get_GMAC0_CLK_Frequency,                               /* GMAC0_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK)
    &Clock_Ip_Get_GMAC1_CLK_Frequency,                               /* GMAC1_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
    &Clock_Ip_Get_GMAC0_RX_CLK_Frequency,                            /* GMAC0_RX_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
    &Clock_Ip_Get_GMAC0_TX_CLK_Frequency,                            /* GMAC0_TX_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
    &Clock_Ip_Get_GMAC_TS_CLK_Frequency,                             /* GMAC_TS_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
    &Clock_Ip_Get_GMAC0_TX_RMII_CLK_Frequency,                       /* GMAC0_TX_RMII_CLK            */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
    &Clock_Ip_Get_GMAC1_RX_CLK_Frequency,                            /* GMAC1_RX_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
    &Clock_Ip_Get_GMAC1_TX_CLK_Frequency,                            /* GMAC1_TX_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
    &Clock_Ip_Get_GMAC1_RMII_CLK_Frequency,                          /* GMAC1_RMII_CLK               */
#endif
    &Clock_Ip_Get_INTM_CLK_Frequency,                                /* INTM_CLK                     */
    &Clock_Ip_Get_LCU0_CLK_Frequency,                                /* LCU0_CLK                     */
    &Clock_Ip_Get_LCU1_CLK_Frequency,                                /* LCU1_CLK                     */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
    &Clock_Ip_Get_LFAST_REF_CLK_Frequency,                           /* LFAST_REF_CLK                */
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
    &Clock_Ip_Get_LPI2C0_CLK_Frequency,                              /* LPI2C0_CLK                   */
#endif
    &Clock_Ip_Get_LPI2C1_CLK_Frequency,                              /* LPI2C1_CLK                   */
    &Clock_Ip_Get_LPSPI0_CLK_Frequency,                              /* LPSPI0_CLK                   */
    &Clock_Ip_Get_LPSPI1_CLK_Frequency,                              /* LPSPI1_CLK                   */
    &Clock_Ip_Get_LPSPI2_CLK_Frequency,                              /* LPSPI2_CLK                   */
    &Clock_Ip_Get_LPSPI3_CLK_Frequency,                              /* LPSPI3_CLK                   */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
    &Clock_Ip_Get_LPSPI4_CLK_Frequency,                              /* LPSPI4_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
    &Clock_Ip_Get_LPSPI5_CLK_Frequency,                              /* LPSPI5_CLK                   */
#endif
    &Clock_Ip_Get_LPUART0_CLK_Frequency,                             /* LPUART0_CLK                  */
    &Clock_Ip_Get_LPUART1_CLK_Frequency,                             /* LPUART1_CLK                  */
    &Clock_Ip_Get_LPUART2_CLK_Frequency,                             /* LPUART2_CLK                  */
    &Clock_Ip_Get_LPUART3_CLK_Frequency,                             /* LPUART3_CLK                  */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
    &Clock_Ip_Get_LPUART4_CLK_Frequency,                             /* LPUART4_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
    &Clock_Ip_Get_LPUART5_CLK_Frequency,                             /* LPUART5_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
    &Clock_Ip_Get_LPUART6_CLK_Frequency,                             /* LPUART6_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
    &Clock_Ip_Get_LPUART7_CLK_Frequency,                             /* LPUART7_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
    &Clock_Ip_Get_LPUART8_CLK_Frequency,                             /* LPUART8_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
    &Clock_Ip_Get_LPUART9_CLK_Frequency,                             /* LPUART9_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
    &Clock_Ip_Get_LPUART10_CLK_Frequency,                            /* LPUART10_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
    &Clock_Ip_Get_LPUART11_CLK_Frequency,                            /* LPUART11_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
    &Clock_Ip_Get_LPUART12_CLK_Frequency,                            /* LPUART12_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
    &Clock_Ip_Get_LPUART13_CLK_Frequency,                            /* LPUART13_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
    &Clock_Ip_Get_LPUART14_CLK_Frequency,                            /* LPUART14_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
    &Clock_Ip_Get_LPUART15_CLK_Frequency,                            /* LPUART15_CLK                 */
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
    &Clock_Ip_Get_LPUART_MSC_CLK_Frequency,                          /* LPUART_MSC_CLK               */
#endif
    &Clock_Ip_Get_MSCM_CLK_Frequency,                                /* MSCM_CLK                     */
#if defined(CLOCK_IP_HAS_MU2A_CLK)
    &Clock_Ip_Get_MU2A_CLK_Frequency,                                 /* MU2A_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
    &Clock_Ip_Get_MU2B_CLK_Frequency,                                 /* MU2B_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
    &Clock_Ip_Get_MU3A_CLK_Frequency,                                 /* MU3A_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
    &Clock_Ip_Get_MU3B_CLK_Frequency,                                 /* MU3B_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
    &Clock_Ip_Get_MU4A_CLK_Frequency,                                 /* MU4A_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
    &Clock_Ip_Get_MU4B_CLK_Frequency,                                 /* MU4B_CLK                      */
#endif
    &Clock_Ip_Get_PIT0_CLK_Frequency,                                /* PIT0_CLK                     */
    &Clock_Ip_Get_PIT1_CLK_Frequency,                                /* PIT1_CLK                     */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
    &Clock_Ip_Get_PIT2_CLK_Frequency,                                /* PIT2_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
    &Clock_Ip_Get_PIT3_CLK_Frequency,                                /* PIT3_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
    &Clock_Ip_Get_PRAMC0_CLK_Frequency,                              /* PRAMC0_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
    &Clock_Ip_Get_PRAMC1_CLK_Frequency,                              /* PRAMC1_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
    &Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency,                         /* QSPI_2XSFIF_CLK              */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
    &Clock_Ip_Get_QSPI0_CLK_Frequency,                               /* QSPI0_CLK                    */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
    &Clock_Ip_Get_QSPI0_RAM_CLK_Frequency,                           /* QSPI0_RAM_CLK                */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
    &Clock_Ip_Get_QSPI0_TX_MEM_CLK_Frequency,                        /* QSPI0_TX_MEM_CLK             */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
    &Clock_Ip_Get_QSPI_SFCK_CLK_Frequency,                           /* QSPI_SFCK_CLK                */
#endif
    &Clock_Ip_Get_RTC_CLK_Frequency,                                 /* RTC_CLK                      */
    &Clock_Ip_Get_RTC0_CLK_Frequency,                                /* RTC0_CLK                     */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
    &Clock_Ip_Get_SAI0_CLK_Frequency,                                /* SAI0_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
    &Clock_Ip_Get_SAI1_CLK_Frequency,                                /* SAI1_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
    &Clock_Ip_Get_SDA_AP_CLK_Frequency,                              /* SDA_AP_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
    &Clock_Ip_Get_SDADC0_CLK_Frequency,                              /* SDADC0_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
    &Clock_Ip_Get_SDADC1_CLK_Frequency,                              /* SDADC1_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
    &Clock_Ip_Get_SDADC2_CLK_Frequency,                              /* SDADC2_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
    &Clock_Ip_Get_SDADC3_CLK_Frequency,                              /* SDADC3_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
    &Clock_Ip_Get_SEMA42_CLK_Frequency,                              /* SEMA42_CLK                   */
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
    &Clock_Ip_Get_SIPI0_CLK_Frequency,                              /* SIPI0_CLK                   */
#endif
    &Clock_Ip_Get_SIUL2_CLK_Frequency,                               /* SIUL2_CLK                    */
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
    &Clock_Ip_Get_SIUL2_PDAC0_0_CLK_Frequency,                       /* SIUL2_PDAC0_0_CLK            */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
    &Clock_Ip_Get_SIUL2_PDAC0_1_CLK_Frequency,                       /* SIUL2_PDAC0_1_CLK            */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
    &Clock_Ip_Get_SIUL2_PDAC1_0_CLK_Frequency,                       /* SIUL2_PDAC1_0_CLK            */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
    &Clock_Ip_Get_SIUL2_PDAC1_1_CLK_Frequency,                       /* SIUL2_PDAC1_1_CLK            */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
    &Clock_Ip_Get_SIUL2_PDAC2_0_CLK_Frequency,                       /* SIUL2_PDAC2_0_CLK            */
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
    &Clock_Ip_Get_SIUL2_PDAC2_1_CLK_Frequency,                       /* SIUL2_PDAC2_1_CLK            */
#endif
    &Clock_Ip_Get_STCU0_CLK_Frequency,                               /* STCU0_CLK                    */
    &Clock_Ip_Get_STMA_CLK_Frequency,                                /* STMA_CLK                     */
    &Clock_Ip_Get_STM0_CLK_Frequency,                                /* STM0_CLK                     */
#if defined(CLOCK_IP_HAS_STMB_CLK)
    &Clock_Ip_Get_STMB_CLK_Frequency,                                /* STMB_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
    &Clock_Ip_Get_STM1_CLK_Frequency,                                /* STM1_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
    &Clock_Ip_Get_STMC_CLK_Frequency,                                /* STMC_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
    &Clock_Ip_Get_STM2_CLK_Frequency,                                /* STM2_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
    &Clock_Ip_Get_STMD_CLK_Frequency,                                /* STMD_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
    &Clock_Ip_Get_STM3_CLK_Frequency,                                /* STM3_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
    &Clock_Ip_Get_SWG_CLK_Frequency,                                 /* SWG_CLK                      */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
    &Clock_Ip_Get_SWG0_CLK_Frequency,                                /* SWG0_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
    &Clock_Ip_Get_SWG1_CLK_Frequency,                                /* SWG1_CLK                     */
#endif
    &Clock_Ip_Get_SWT0_CLK_Frequency,                                /* SWT0_CLK                     */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
    &Clock_Ip_Get_SWT1_CLK_Frequency,                                /* SWT1_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
    &Clock_Ip_Get_SWT2_CLK_Frequency,                                /* SWT2_CLK                     */
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
    &Clock_Ip_Get_SWT3_CLK_Frequency,                                /* SWT3_CLK                     */
#endif
    &Clock_Ip_Get_TEMPSENSE_CLK_Frequency,                           /* TEMPSENSE_CLK                */
    &Clock_Ip_Get_TRACE_CLK_Frequency,                               /* TRACE_CLK                    */
    &Clock_Ip_Get_TRGMUX0_CLK_Frequency,                             /* TRGMUX0_CLK                  */
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
    &Clock_Ip_Get_TRGMUX1_CLK_Frequency,                             /* TRGMUX1_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
    &Clock_Ip_Get_TSENSE0_CLK_Frequency,                             /* TSENSE0_CLK                  */
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
    &Clock_Ip_Get_USDHC_PER_CLK_Frequency,                                /* USDHC_PER_CLK                     */
#endif
    &Clock_Ip_Get_WKPU0_CLK_Frequency,                               /* WKPU0_CLK                    */
#if defined(CLOCK_IP_HAS_XRDC_CLK)
    &Clock_Ip_Get_XRDC_CLK_Frequency,                                /* XRDC_CLK                     */
#endif
};
/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"


/* Clock start constant section data */
#define MCU_START_SEC_CONST_32
#include "Mcu_MemMap.h"

static const uint64 Clock_Ip_au32EnableDivider[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};
static const uint64 Clock_Ip_u32EnableGate[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};
#ifdef CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR
static const uint64 Clock_Ip_apfTableDividerValue[CLOCK_IP_FIRC_DIV_SEL_VALS_NO] =
{
    2U,                  /* Divider value for 0  hardware value */
    2U,                  /* Divider value for 1  hardware value */
    16U,                 /* Divider value for 2  hardware value */
    1U,                  /* Divider value for 3  hardware value */
};
#endif

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_32
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"


/* Return zero frequency */
static uint64 Clock_Ip_Get_Zero_Frequency(void)
{
    return 0U;
}
/* Return FIRC_CLK frequency */
static uint64 Clock_Ip_Get_FIRC_CLK_Frequency(void) {
    uint64 Frequency = CLOCK_IP_FIRC_FREQUENCY;
#ifdef CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR
    uint64 DividerValue = Clock_Ip_apfTableDividerValue[(IP_CONFIGURATION_GPR->CONFIG_REG_GPR & CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_MASK) >> CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_SHIFT];

    Frequency /= DividerValue;
#endif
    return Frequency;
}
/* Return FIRC_STANDBY_CLK frequency */
static uint64 Clock_Ip_Get_FIRC_STANDBY_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[((IP_FIRC->STDBY_ENABLE & FIRC_STDBY_ENABLE_STDBY_EN_MASK) >> FIRC_STDBY_ENABLE_STDBY_EN_SHIFT)];
    return Frequency;
}
/* Return SIRC_CLK frequency */
static uint64 Clock_Ip_Get_SIRC_CLK_Frequency(void) {
    return CLOCK_IP_SIRC_FREQUENCY;
}
/* Return SIRC_STANDBY_CLK frequency */
static uint64 Clock_Ip_Get_SIRC_STANDBY_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SIRC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[((IP_SIRC->MISCELLANEOUS_IN & SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK) >> SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_SHIFT)];
    return Frequency;
}
/* Return FXOSC_CLK frequency */
static uint64 Clock_Ip_Get_FXOSC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_u32fxosc;

    if (((IP_FXOSC->STAT & FXOSC_STAT_OSC_STAT_MASK) >> FXOSC_STAT_OSC_STAT_SHIFT) == 0U)
    {
        Frequency = 0U;
    }
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK53_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK53_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
/* Return SXOSC_CLK frequency */
static uint64 Clock_Ip_Get_SXOSC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_u32sxosc;

    if (((IP_SXOSC->SXOSC_STAT & SXOSC_SXOSC_STAT_OSC_STAT_MASK) >> SXOSC_SXOSC_STAT_OSC_STAT_SHIFT) == 0U)
    {
        Frequency = 0U;
    }
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif
/* Return PLL_CLK frequency */
static uint64 Clock_Ip_Get_PLL_CLK_Frequency(void) {
    uint32 PLLDVBuffer = IP_PLL->PLLDV;
    uint32 PLLFDBuffer = IP_PLL->PLLFD;
    uint32 PLLCLKMUXBuffer = 1U;

#ifdef CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX
    #if (CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX == STD_ON)
        PLLCLKMUXBuffer = IP_PLL->PLLCLKMUX;
    #endif /*(CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX == STD_ON)*/
#endif /*CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX*/

    if (Clock_Ip_u32PLL_CLKChecksum != (PLLDVBuffer ^ PLLFDBuffer ^ PLLCLKMUXBuffer))
    {
        Clock_Ip_u32PLL_CLKChecksum = (PLLDVBuffer ^ PLLFDBuffer ^ PLLCLKMUXBuffer);
        Clock_Ip_u32PLL_CLKFreq = Clock_Ip_PLL_VCO(IP_PLL);
    }
    return (((IP_PLL->PLLSR & PLL_PLLSR_LOCK_MASK) >> PLL_PLLSR_LOCK_SHIFT) != 0U) ? Clock_Ip_u32PLL_CLKFreq : 0U;
}
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
/* Return PLLAUX_CLK frequency */
static uint64 Clock_Ip_Get_PLLAUX_CLK_Frequency(void) {
    if (Clock_Ip_u32PLLAUX_CLKChecksum != (IP_PLL_AUX->PLLDV))
    {
        Clock_Ip_u32PLLAUX_CLKChecksum = (IP_PLL_AUX->PLLDV);
        Clock_Ip_u32PLLAUX_CLKFreq = Clock_Ip_PLL_VCO(IP_PLL_AUX);
    }
    return (((IP_PLL_AUX->PLLSR & PLL_PLLSR_LOCK_MASK) >> PLL_PLLSR_LOCK_SHIFT) != 0U) ? Clock_Ip_u32PLLAUX_CLKFreq : 0U;
}
#endif
/* Return PLL_POSTDIV_CLK frequency */
static uint64 Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLL_CLK_Frequency();
    uint64 DividerValue = ((uint64)IP_PLL->PLLDV & (uint64)PLL_PLLDV_ODIV2_MASK) >> (uint64)PLL_PLLDV_ODIV2_SHIFT;

    if ((uint64)0U != DividerValue)
    {
        Frequency /= DividerValue;
    }
    else
    {
        Frequency = (uint64)0U;
    }
    return Frequency;
}
#if defined(CLOCK_IP_HAS_PLLAUX_POSTDIV_CLK)
/* Return PLLAUX_POSTDIV_CLK frequency */
static uint64 Clock_Ip_Get_PLLAUX_POSTDIV_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLLAUX_CLK_Frequency();
    uint64 DividerValue = ((uint64)IP_PLL_AUX->PLLDV & (uint64)PLL_PLLDV_ODIV2_MASK) >> (uint64)PLL_PLLDV_ODIV2_SHIFT;

    if ((uint64)0U != DividerValue)
    {
        Frequency /= DividerValue;
    }
    else
    {
        Frequency = (uint64)0U;
    }
    return Frequency;
}
#endif
/* Return PLL_PHI0 frequency */
static uint64 Clock_Ip_Get_PLL_PHI0_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_PLL->PLLODIV[0U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                   /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_PLL->PLLODIV[0U] & (uint64)PLL_PLLODIV_DIV_MASK) >> (uint64)PLL_PLLODIV_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return Frequency;
}
/* Return PLL_PHI1 frequency */
static uint64 Clock_Ip_Get_PLL_PHI1_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_PLL->PLLODIV[1U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                   /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_PLL->PLLODIV[1U] & (uint64)PLL_PLLODIV_DIV_MASK) >> (uint64)PLL_PLLODIV_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return Frequency;
}
#if defined(CLOCK_IP_HAS_PLLAUX_PHI0_CLK)
/* Return PLLAUX_PHI0 frequency */
static uint64 Clock_Ip_Get_PLLAUX_PHI0_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLLAUX_POSTDIV_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_PLL_AUX->PLLODIV[0U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                   /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_PLL_AUX->PLLODIV[0U] & (uint64)PLL_PLLODIV_DIV_MASK) >> (uint64)PLL_PLLODIV_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI1_CLK)
/* Return PLLAUX_PHI1 frequency */
static uint64 Clock_Ip_Get_PLLAUX_PHI1_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLLAUX_POSTDIV_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_PLL_AUX->PLLODIV[1U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                   /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_PLL_AUX->PLLODIV[1U] & (uint64)PLL_PLLODIV_DIV_MASK) >> (uint64)PLL_PLLODIV_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_PLLAUX_PHI2_CLK)
/* Return PLLAUX_PHI2 frequency */
static uint64 Clock_Ip_Get_PLLAUX_PHI2_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_PLLAUX_POSTDIV_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_PLL_AUX->PLLODIV[2U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                   /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_PLL_AUX->PLLODIV[2U] & (uint64)PLL_PLLODIV_DIV_MASK) >> (uint64)PLL_PLLODIV_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
/* Return emac_mii_rx frequency */
static uint64 Clock_Ip_Get_emac_mii_rx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EMAC_MII_RX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
/* Return emac_mii_rmii_tx frequency */
static uint64 Clock_Ip_Get_emac_mii_rmii_tx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EMAC_MII_RMII_TX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RGMII_RX_CLK)
/* Return gmac_mii_rgmii_rx frequency */
static uint64 Clock_Ip_Get_gmac_mii_rgmii_rx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_GMAC_MII_RGMII_RX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC_MII_RMII_RGMII_TX_CLK)
/* Return gmac_mii_rmii_rgmii_tx frequency */
static uint64 Clock_Ip_Get_gmac_mii_rmii_rgmii_tx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_GMAC_MII_RMII_RGMII_TX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RGMII_RX_CLK)
/* Return gmac0_mii_rgmii_rx frequency */
static uint64 Clock_Ip_Get_gmac0_mii_rgmii_rx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_GMAC0_MII_RGMII_RX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC0_MII_RMII_RGMII_TX_CLK)
/* Return gmac0_mii_rmii_rgmii_tx frequency */
static uint64 Clock_Ip_Get_gmac0_mii_rmii_rgmii_tx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_GMAC0_MII_RMII_RGMII_TX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RGMII_RX_CLK)
/* Return gmac1_mii_rgmii_rx frequency */
static uint64 Clock_Ip_Get_gmac1_mii_rgmii_rx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_GMAC1_MII_RGMII_RX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC1_MII_RMII_RGMII_TX_CLK)
/* Return gmac1_mii_rmii_rgmii_tx frequency */
static uint64 Clock_Ip_Get_gmac1_mii_rmii_rgmii_tx_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_GMAC1_MII_RMII_RGMII_TX_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
/* Return lfast_ext_ref frequency */
static uint64 Clock_Ip_Get_lfast_ext_ref_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_LFAST_REF_EXT_CLK_INDEX_ENTRY].Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
/* Return swg_pad frequency */
static uint64 Clock_Ip_Get_swg_pad_Frequency(void) {
    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_SWG_PAD_CLK_INDEX_ENTRY].Frequency;
}
#endif
/* Return SCS_CLK frequency */
static uint64 Clock_Ip_Get_SCS_CLK_Frequency(void) {

    uint64 Frequency;

    if (((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT) != (uint32)8U)
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_PLL_PHI0_Frequency();
    }

    return Frequency;            /*  Selector value */
}
/* Return CORE_CLK frequency */
static uint64 Clock_Ip_Get_CORE_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_0 & MC_CGM_MUX_0_DC_0_DE_MASK) >> MC_CGM_MUX_0_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_0 & (uint64)MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return AIPS_PLAT_CLK frequency */
static uint64 Clock_Ip_Get_AIPS_PLAT_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_1 & MC_CGM_MUX_0_DC_1_DE_MASK) >> MC_CGM_MUX_0_DC_1_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_1 & (uint64)MC_CGM_MUX_0_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_1_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return AIPS_SLOW_CLK frequency */
static uint64 Clock_Ip_Get_AIPS_SLOW_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_2 & MC_CGM_MUX_0_DC_2_DE_MASK) >> MC_CGM_MUX_0_DC_2_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_2 & (uint64)MC_CGM_MUX_0_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_2_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return HSE_CLK frequency */
static uint64 Clock_Ip_Get_HSE_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_3 & MC_CGM_MUX_0_DC_3_DE_MASK) >> MC_CGM_MUX_0_DC_3_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_3 & (uint64)MC_CGM_MUX_0_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_3_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return DCM_CLK frequency */
static uint64 Clock_Ip_Get_DCM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_4 & MC_CGM_MUX_0_DC_4_DE_MASK) >> MC_CGM_MUX_0_DC_4_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_4 & (uint64)MC_CGM_MUX_0_DC_4_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_4_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#if defined(CLOCK_IP_HAS_LBIST_CLK)
/* Return LBIST_CLK frequency */
static uint64 Clock_Ip_Get_LBIST_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_5 & MC_CGM_MUX_0_DC_5_DE_MASK) >> MC_CGM_MUX_0_DC_5_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_5 & (uint64)MC_CGM_MUX_0_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_5_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
/* Return QSPI_MEM_CLK frequency */
static uint64 Clock_Ip_Get_QSPI_MEM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_6 & MC_CGM_MUX_0_DC_6_DE_MASK) >> MC_CGM_MUX_0_DC_6_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_6 & (uint64)MC_CGM_MUX_0_DC_6_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_6_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/* Return CM7_CORE_CLK frequency */
static uint64 Clock_Ip_Get_CM7_CORE_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SCS_CLK_Frequency();

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_0_DC_7 & MC_CGM_MUX_0_DC_7_DE_MASK) >> MC_CGM_MUX_0_DC_7_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_0_DC_7 & (uint64)MC_CGM_MUX_0_DC_7_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_7_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
/* Return CLKOUT_RUN_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT_RUN_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();            /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DE_MASK) >> MC_CGM_MUX_6_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return ADC0_CLK frequency */
static uint64 Clock_Ip_Get_ADC0_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK40_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK40_SHIFT];
    return Frequency;
}
/* Return ADC1_CLK frequency */
static uint64 Clock_Ip_Get_ADC1_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK41_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK41_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_ADC2_CLK)
/* Return ADC2_CLK frequency */
static uint64 Clock_Ip_Get_ADC2_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK42_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK42_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
/* Return ADC3_CLK frequency */
static uint64 Clock_Ip_Get_ADC3_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK43_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK43_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
/* Return ADC4_CLK frequency */
static uint64 Clock_Ip_Get_ADC4_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK52_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK52_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
/* Return ADC5_CLK frequency */
static uint64 Clock_Ip_Get_ADC5_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK53_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK53_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
/* Return ADC6_CLK frequency */
static uint64 Clock_Ip_Get_ADC6_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK54_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK54_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ADCBIST_CLK)
/* Return ADCBIST_CLK frequency */
static uint64 Clock_Ip_Get_ADCBIST_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_006)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB2_STAT & MC_ME_PRTN3_COFB2_STAT_BLOCK65_MASK) >> MC_ME_PRTN3_COFB2_STAT_BLOCK65_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_AXBS_CLK)
/* Return AXBS_CLK frequency */
static uint64 Clock_Ip_Get_AXBS_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK0_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK0_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AXBS0_CLK)
/* Return AXBS0_CLK frequency */
static uint64 Clock_Ip_Get_AXBS0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK1_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK1_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AXBS1_CLK)
/* Return AXBS1_CLK frequency */
static uint64 Clock_Ip_Get_AXBS1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK2_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK2_SHIFT];
    return Frequency;
}
#endif
/* Return BCTU0_CLK frequency */
static uint64 Clock_Ip_Get_BCTU0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_BCTU1_CLK)
/* Return BCTU1_CLK frequency */
static uint64 Clock_Ip_Get_BCTU1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK49_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK49_SHIFT];
    return Frequency;
}
#endif
/* Return CLKOUT_STANDBY_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT_STANDBY_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_5_DC_0 & MC_CGM_MUX_5_DC_0_DE_MASK) >> MC_CGM_MUX_5_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_5_DC_0 & (uint64)MC_CGM_MUX_5_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_5_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return CMP0_CLK frequency */
static uint64 Clock_Ip_Get_CMP0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK92_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK92_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_CMP1_CLK)
/* Return CMP1_CLK frequency */
static uint64 Clock_Ip_Get_CMP1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK93_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK93_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_CMP2_CLK)
/* Return CMP2_CLK frequency */
static uint64 Clock_Ip_Get_CMP2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK58_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK58_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM0_CLK)
/* Return COOLFLUX_D_RAM0_CLK frequency */
static uint64 Clock_Ip_Get_COOLFLUX_D_RAM0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK58_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK58_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_COOLFLUX_D_RAM1_CLK)
/* Return COOLFLUX_D_RAM1_CLK frequency */
static uint64 Clock_Ip_Get_COOLFLUX_D_RAM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK59_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK59_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_COOLFLUX_DSP16L_CLK)
/* Return COOLFLUX_DSP16L_CLK frequency */
static uint64 Clock_Ip_Get_COOLFLUX_DSP16L_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK55_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK55_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM0_CLK)
/* Return COOLFLUX_I_RAM0_CLK frequency */
static uint64 Clock_Ip_Get_COOLFLUX_I_RAM0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK56_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK56_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_COOLFLUX_I_RAM1_CLK)
/* Return COOLFLUX_I_RAM1_CLK frequency */
static uint64 Clock_Ip_Get_COOLFLUX_I_RAM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK57_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK57_SHIFT];
    return Frequency;
}
#endif

/* Return CRC0_CLK frequency */
static uint64 Clock_Ip_Get_CRC0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK96_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK96_SHIFT];
    return Frequency;
}
/* Return DMAMUX0_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
/* Return DMAMUX1_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_DMAMUX2_CLK)
/* Return DMAMUX2_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK40_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK40_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_DMAMUX3_CLK)
/* Return DMAMUX3_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK41_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK41_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_DSPI_MSC_CLK)
/* Return DSPI_MSC_CLK frequency */
static uint64 Clock_Ip_Get_DSPI_MSC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK66_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK66_SHIFT];
    return Frequency;
}
#endif

/* Return EDMA0_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK3_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK3_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD0_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK4_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK4_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD1_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK5_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK5_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD2_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK6_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK6_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD3_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK7_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK7_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD4_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD4_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK8_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK8_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD5_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD5_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK9_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK9_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD6_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD6_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK10_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK10_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD7_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD7_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK11_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK11_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD8_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD8_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK12_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK12_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD9_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD9_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK13_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK13_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD10_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD10_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK14_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK14_SHIFT];
    return Frequency;
}
/* Return EDMA0_TCD11_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD11_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK15_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK15_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
/* Return EDMA0_TCD12_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD12_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK4_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK4_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
/* Return EDMA0_TCD13_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD13_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK5_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK5_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
/* Return EDMA0_TCD14_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD14_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK6_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK6_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
/* Return EDMA0_TCD15_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD15_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK7_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK7_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
/* Return EDMA0_TCD16_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD16_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK8_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK8_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
/* Return EDMA0_TCD17_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD17_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK9_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK9_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
/* Return EDMA0_TCD18_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD18_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK10_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK10_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
/* Return EDMA0_TCD19_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD19_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK11_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK11_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
/* Return EDMA0_TCD20_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD20_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK12_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK12_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
/* Return EDMA0_TCD21_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD21_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK13_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK13_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
/* Return EDMA0_TCD22_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD22_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK14_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK14_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
/* Return EDMA0_TCD23_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD23_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK15_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK15_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
/* Return EDMA0_TCD24_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD24_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK16_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK16_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
/* Return EDMA0_TCD25_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD25_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK17_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK17_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
/* Return EDMA0_TCD26_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD26_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK18_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK18_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
/* Return EDMA0_TCD27_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD27_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK19_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK19_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
/* Return EDMA0_TCD28_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD28_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK20_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK20_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
/* Return EDMA0_TCD29_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD29_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK21_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK21_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
/* Return EDMA0_TCD30_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD30_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK22_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK22_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
/* Return EDMA0_TCD31_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_TCD31_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK23_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK23_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_CLK)
/* Return EDMA1_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK4_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK4_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD0_CLK)
/* Return EDMA1_TCD0_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK5_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK5_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD1_CLK)
/* Return EDMA1_TCD1_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK6_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK6_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD2_CLK)
/* Return EDMA1_TCD2_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK7_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK7_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD3_CLK)
/* Return EDMA1_TCD3_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK8_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK8_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD4_CLK)
/* Return EDMA1_TCD4_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD4_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK9_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK9_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD5_CLK)
/* Return EDMA1_TCD5_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD5_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK10_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK10_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD6_CLK)
/* Return EDMA1_TCD6_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD6_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK11_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK11_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD7_CLK)
/* Return EDMA1_TCD7_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD7_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK12_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK12_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD8_CLK)
/* Return EDMA1_TCD8_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD8_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK13_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK13_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD9_CLK)
/* Return EDMA1_TCD9_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD9_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK14_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK14_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD10_CLK)
/* Return EDMA1_TCD10_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD10_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK15_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK15_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD11_CLK)
/* Return EDMA1_TCD11_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD11_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK16_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK16_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD12_CLK)
/* Return EDMA1_TCD12_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD12_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK17_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK17_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD13_CLK)
/* Return EDMA1_TCD13_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD13_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK18_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK18_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD14_CLK)
/* Return EDMA1_TCD14_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD14_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK19_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK19_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD15_CLK)
/* Return EDMA1_TCD15_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD15_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK20_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK20_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD16_CLK)
/* Return EDMA1_TCD16_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD16_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK0_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK0_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD17_CLK)
/* Return EDMA1_TCD17_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD17_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK1_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK1_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD18_CLK)
/* Return EDMA1_TCD18_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD18_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK2_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK2_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD19_CLK)
/* Return EDMA1_TCD19_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD19_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK3_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK3_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD20_CLK)
/* Return EDMA1_TCD20_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD20_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK4_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK4_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD21_CLK)
/* Return EDMA1_TCD21_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD21_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK5_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK5_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD22_CLK)
/* Return EDMA1_TCD22_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD22_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK6_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK6_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD23_CLK)
/* Return EDMA1_TCD23_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD23_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK7_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK7_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD24_CLK)
/* Return EDMA1_TCD24_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD24_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK8_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK8_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD25_CLK)
/* Return EDMA1_TCD25_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD25_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK9_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK9_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD26_CLK)
/* Return EDMA1_TCD26_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD26_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK10_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK10_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD27_CLK)
/* Return EDMA1_TCD27_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD27_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK11_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK11_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD28_CLK)
/* Return EDMA1_TCD28_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD28_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK12_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK12_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD29_CLK)
/* Return EDMA1_TCD29_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD29_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK13_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK13_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD30_CLK)
/* Return EDMA1_TCD30_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD30_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK14_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK14_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA1_TCD31_CLK)
/* Return EDMA1_TCD31_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_TCD31_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB0_STAT & MC_ME_PRTN3_COFB0_STAT_BLOCK15_MASK) >> MC_ME_PRTN3_COFB0_STAT_BLOCK15_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM0_CLK)
/* Return EFLEX_PWM0_CLK frequency */
static uint64 Clock_Ip_Get_EFLEX_PWM0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK46_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK46_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EFLEX_PWM1_CLK)
/* Return EFLEX_PWM1_CLK frequency */
static uint64 Clock_Ip_Get_EFLEX_PWM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK47_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK47_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
/* Return EIM_CLK frequency */
static uint64 Clock_Ip_Get_EIM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK22_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK22_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
/* Return EIM0_CLK frequency */
static uint64 Clock_Ip_Get_EIM0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK67_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK67_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
/* Return EIM1_CLK frequency */
static uint64 Clock_Ip_Get_EIM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK68_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK68_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
/* Return EIM2_CLK frequency */
static uint64 Clock_Ip_Get_EIM2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK69_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK69_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EIM3_CLK)
/* Return EIM3_CLK frequency */
static uint64 Clock_Ip_Get_EIM3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK70_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK70_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC0_CLK)
/* Return GMAC0_CLK frequency */
static uint64 Clock_Ip_Get_GMAC0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC1_CLK)
/* Return GMAC1_CLK frequency */
static uint64 Clock_Ip_Get_GMAC1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
/* Return EMAC_RX_CLK frequency */
static uint64 Clock_Ip_Get_EMAC_RX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
/* Return EMAC0_RX_CLK frequency */
static uint64 Clock_Ip_Get_EMAC0_RX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_EMAC_RX_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
/* Return EMAC_TS_CLK frequency */
static uint64 Clock_Ip_Get_EMAC_TS_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DE_MASK) >> MC_CGM_MUX_9_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
/* Return EMAC0_TS_CLK frequency */
static uint64 Clock_Ip_Get_EMAC0_TS_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_EMAC_TS_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
/* Return EMAC_TX_CLK frequency */
static uint64 Clock_Ip_Get_EMAC_TX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
/* Return EMAC0_TX_CLK frequency */
static uint64 Clock_Ip_Get_EMAC0_TX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_EMAC_TX_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
/* Return EMAC_TX_RMII_CLK frequency */
static uint64 Clock_Ip_Get_EMAC_TX_RMII_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_12_CSS & MC_CGM_MUX_12_CSS_SELSTAT_MASK) >> MC_CGM_MUX_12_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_12_DC_0 & MC_CGM_MUX_12_DC_0_DE_MASK) >> MC_CGM_MUX_12_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_12_DC_0 & (uint64)MC_CGM_MUX_12_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_12_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
/* Return EMIOS0_CLK frequency */
static uint64 Clock_Ip_Get_EMIOS0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/* Return EMIOS1_CLK frequency */
static uint64 Clock_Ip_Get_EMIOS1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK35_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK35_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
/* Return EMIOS2_CLK frequency */
static uint64 Clock_Ip_Get_EMIOS2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK36_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK36_SHIFT];
    return Frequency;
}
#endif
/* Return ERM0_CLK frequency */
static uint64 Clock_Ip_Get_ERM0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK23_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK23_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_ERM1_CLK)
/* Return ERM1_CLK frequency */
static uint64 Clock_Ip_Get_ERM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK3_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK3_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ETPU_AB_REGISTERS_CLK)
/* Return ETPU_AB_REGISTERS_CLK frequency */
static uint64 Clock_Ip_Get_ETPU_AB_REGISTERS_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CM7_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM1_CLK)
/* Return ETPU_CODE_RAM1_CLK frequency */
static uint64 Clock_Ip_Get_ETPU_CODE_RAM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CM7_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK36_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK36_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ETPU_CODE_RAM2_CLK)
/* Return ETPU_CODE_RAM2_CLK frequency */
static uint64 Clock_Ip_Get_ETPU_CODE_RAM2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CM7_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK37_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK37_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_MIRROR_CLK)
/* Return ETPU_RAM_MIRROR_CLK frequency */
static uint64 Clock_Ip_Get_ETPU_RAM_MIRROR_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CM7_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK35_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK35_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_ETPU_RAM_SDM_CLK)
/* Return ETPU_RAM_SDM_CLK frequency */
static uint64 Clock_Ip_Get_ETPU_RAM_SDM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CM7_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FCCU_CLK)
/* Return FCCU_CLK frequency */
static uint64 Clock_Ip_Get_FCCU_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK97_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK97_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLASH0_CLK)
/* Return FLASH0_CLK frequency */
static uint64 Clock_Ip_Get_FLASH0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK26_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK26_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLASH0_ALT_CLK)
/* Return FLASH0_ALT_CLK frequency */
static uint64 Clock_Ip_Get_FLASH0_ALT_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK27_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK27_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLASH1_CLK)
/* Return FLASH1_CLK frequency */
static uint64 Clock_Ip_Get_FLASH1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK59_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK59_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLASH1_ALT_CLK)
/* Return FLASH1_ALT_CLK frequency */
static uint64 Clock_Ip_Get_FLASH1_ALT_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK60_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK60_SHIFT];
    return Frequency;
}
#endif
/* Return FLEXCANA_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCANA_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_3_DC_0 & MC_CGM_MUX_3_DC_0_DE_MASK) >> MC_CGM_MUX_3_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return FLEXCAN0_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANA_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK65_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK65_SHIFT];
    return Frequency;
}
/* Return FLEXCAN1_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANA_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK66_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK66_SHIFT];
    return Frequency;
}
/* Return FLEXCAN2_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANA_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK67_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK67_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_FLEXCANB_CLK)
/* Return FLEXCANB_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCANB_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN3_CLK)
/* Return FLEXCAN3_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK68_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK68_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
/* Return FLEXCAN4_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN4_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK69_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK69_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
/* Return FLEXCAN5_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN5_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK70_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK70_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN6_CLK)
/* Return FLEXCAN6_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN6_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK71_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK71_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN7_CLK)
/* Return FLEXCAN7_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN7_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK72_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK72_SHIFT];
    return Frequency;
}
#endif
/* Return FLEXIO0_CLK frequency */
static uint64 Clock_Ip_Get_FLEXIO0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK73_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK73_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_HSE_MU0_CLK)
/* Return HSE_MU0_CLK frequency */
static uint64 Clock_Ip_Get_HSE_MU0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK99_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK99_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_HSE_MU1_CLK)
/* Return HSE_MU1_CLK frequency */
static uint64 Clock_Ip_Get_HSE_MU1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK59_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK59_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_JDC_CLK)
/* Return JDC_CLK frequency */
static uint64 Clock_Ip_Get_JDC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK101_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK101_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_IGF0_CLK)
/* Return IGF0_CLK frequency */
static uint64 Clock_Ip_Get_IGF0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK44_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK44_SHIFT];
    return Frequency;
}
#endif
/* Return INTM_CLK frequency */
static uint64 Clock_Ip_Get_INTM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK31_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK31_SHIFT];
    return Frequency;
}
/* Return LCU0_CLK frequency */
static uint64 Clock_Ip_Get_LCU0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK38_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK38_SHIFT];
    return Frequency;
}
/* Return LCU1_CLK frequency */
static uint64 Clock_Ip_Get_LCU1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK39_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK39_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
/* Return LFAST_REF_CLK frequency */
static uint64 Clock_Ip_Get_LFAST_REF_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_15_CSS & MC_CGM_MUX_15_CSS_SELSTAT_MASK) >> MC_CGM_MUX_15_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_15_DC_0 & MC_CGM_MUX_15_DC_0_DE_MASK) >> MC_CGM_MUX_15_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_15_DC_0 & (uint64)MC_CGM_MUX_15_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_15_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPI2C0_CLK)
/* Return LPI2C0_CLK frequency */
static uint64 Clock_Ip_Get_LPI2C0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK84_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK84_SHIFT];
    return Frequency;
}
#endif
/* Return LPI2C1_CLK frequency */
static uint64 Clock_Ip_Get_LPI2C1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK85_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK85_SHIFT];
    return Frequency;
}
/* Return LPSPI0_CLK frequency */
static uint64 Clock_Ip_Get_LPSPI0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK86_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK86_SHIFT];
    return Frequency;
}
/* Return LPSPI1_CLK frequency */
static uint64 Clock_Ip_Get_LPSPI1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK87_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK87_SHIFT];
    return Frequency;
}
/* Return LPSPI2_CLK frequency */
static uint64 Clock_Ip_Get_LPSPI2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK88_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK88_SHIFT];
    return Frequency;
}
/* Return LPSPI3_CLK frequency */
static uint64 Clock_Ip_Get_LPSPI3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK89_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK89_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
/* Return LPSPI4_CLK frequency */
static uint64 Clock_Ip_Get_LPSPI4_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK47_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK47_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
/* Return LPSPI5_CLK frequency */
static uint64 Clock_Ip_Get_LPSPI5_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK48_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK48_SHIFT];
    return Frequency;
}
#endif
/* Return LPUART0_CLK frequency */
static uint64 Clock_Ip_Get_LPUART0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK74_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK74_SHIFT];
    return Frequency;
}
/* Return LPUART1_CLK frequency */
static uint64 Clock_Ip_Get_LPUART1_CLK_Frequency(void) {
#if (defined(CLOCK_IP_DERIVATIVE_006) || defined(CLOCK_IP_DERIVATIVE_009) || defined(CLOCK_IP_DERIVATIVE_008) || \
     defined(CLOCK_IP_DERIVATIVE_004) || defined(CLOCK_IP_DERIVATIVE_007) || \
    (defined(CLOCK_IP_DERIVATIVE_001) && (!defined(CLOCK_IP_HAS_LPUART4_CLK))))
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK75_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK75_SHIFT];
    return Frequency;
}
/* Return LPUART2_CLK frequency */
static uint64 Clock_Ip_Get_LPUART2_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK76_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK76_SHIFT];
    return Frequency;
}
/* Return LPUART3_CLK frequency */
static uint64 Clock_Ip_Get_LPUART3_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK77_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK77_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
/* Return LPUART4_CLK frequency */
static uint64 Clock_Ip_Get_LPUART4_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK78_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK78_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
/* Return LPUART5_CLK frequency */
static uint64 Clock_Ip_Get_LPUART5_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK79_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK79_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
/* Return LPUART6_CLK frequency */
static uint64 Clock_Ip_Get_LPUART6_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK80_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK80_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
/* Return LPUART7_CLK frequency */
static uint64 Clock_Ip_Get_LPUART7_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK81_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK81_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
/* Return LPUART8_CLK frequency */
static uint64 Clock_Ip_Get_LPUART8_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK35_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK35_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
/* Return LPUART9_CLK frequency */
static uint64 Clock_Ip_Get_LPUART9_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK36_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK36_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
/* Return LPUART10_CLK frequency */
static uint64 Clock_Ip_Get_LPUART10_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK37_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK37_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
/* Return LPUART11_CLK frequency */
static uint64 Clock_Ip_Get_LPUART11_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK38_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK38_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
/* Return LPUART12_CLK frequency */
static uint64 Clock_Ip_Get_LPUART12_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK39_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK39_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
/* Return LPUART13_CLK frequency */
static uint64 Clock_Ip_Get_LPUART13_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK40_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK40_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
/* Return LPUART14_CLK frequency */
static uint64 Clock_Ip_Get_LPUART14_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK41_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK41_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
/* Return LPUART15_CLK frequency */
static uint64 Clock_Ip_Get_LPUART15_CLK_Frequency(void) {
#if defined(CLOCK_IP_DERIVATIVE_008)
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
#else
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
#endif

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK42_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK42_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART_MSC_CLK)
/* Return LPUART_MSC_CLK frequency */
static uint64 Clock_Ip_Get_LPUART_MSC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK65_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK65_SHIFT];
    return Frequency;
}
#endif
/* Return MSCM_CLK frequency */
static uint64 Clock_Ip_Get_MSCM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK24_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK24_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_MU2A_CLK)
/* Return MU2A_CLK frequency */
static uint64 Clock_Ip_Get_MU2A_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK46_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK46_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_MU2B_CLK)
/* Return MU2B_CLK frequency */
static uint64 Clock_Ip_Get_MU2B_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK47_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK47_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_MU3A_CLK)
/* Return MU3A_CLK frequency */
static uint64 Clock_Ip_Get_MU3A_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK49_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK49_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_MU3B_CLK)
/* Return MU3B_CLK frequency */
static uint64 Clock_Ip_Get_MU3B_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK50_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK50_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_MU4A_CLK)
/* Return MU4A_CLK frequency */
static uint64 Clock_Ip_Get_MU4A_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_MU4B_CLK)
/* Return MU4B_CLK frequency */
static uint64 Clock_Ip_Get_MU4B_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK52_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK52_SHIFT];
    return Frequency;
}
#endif
/* Return PIT0_CLK frequency */
static uint64 Clock_Ip_Get_PIT0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK44_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK44_SHIFT];
    return Frequency;
}
/* Return PIT1_CLK frequency */
static uint64 Clock_Ip_Get_PIT1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK45_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK45_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_PIT2_CLK)
/* Return PIT2_CLK frequency */
static uint64 Clock_Ip_Get_PIT2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK63_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK63_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_PIT3_CLK)
/* Return PIT3_CLK frequency */
static uint64 Clock_Ip_Get_PIT3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK64_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK64_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_PRAMC0_CLK)
/* Return PRAMC0_CLK frequency */
static uint64 Clock_Ip_Get_PRAMC0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK25_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK25_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_PRAMC1_CLK)
/* Return PRAMC1_CLK frequency */
static uint64 Clock_Ip_Get_PRAMC1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK25_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK25_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/* Return QSPI_2XSFIF_CLK frequency */
static uint64 Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_10_DC_0 & MC_CGM_MUX_10_DC_0_DE_MASK) >> MC_CGM_MUX_10_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)(IP_MC_CGM->MUX_10_DC_0 & (uint64)MC_CGM_MUX_10_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_10_DC_0_DIV_SHIFT) + 1U) * 2U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI0_CLK)
/* Return QSPI0_CLK frequency */
static uint64 Clock_Ip_Get_QSPI0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_QSPI_SFCK_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
/* Return QSPI0_RAM_CLK frequency */
static uint64 Clock_Ip_Get_QSPI0_RAM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_QSPI_MEM_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
/* Return QSPI0_TX_MEM_CLK frequency */
static uint64 Clock_Ip_Get_QSPI0_TX_MEM_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_QSPI_MEM_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK) && defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/* Return QSPI_SFCK_CLK frequency */
static uint64 Clock_Ip_Get_QSPI_SFCK_CLK_Frequency(void) {
    return Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency() / 2U;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK) && !defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/* Return QSPI_SFCK_CLK frequency */
static uint64 Clock_Ip_Get_QSPI_SFCK_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_10_DC_0 & MC_CGM_MUX_10_DC_0_DE_MASK) >> MC_CGM_MUX_10_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_10_DC_0 & (uint64)MC_CGM_MUX_10_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_10_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
#if defined(CLOCK_IP_QSPI_SFCK_CLK_DIV2_SUPPORTED)
    Frequency /= 2U;
#endif
    return Frequency;
}
#endif
/* Return RTC_CLK frequency */
static uint64 Clock_Ip_Get_RTC_CLK_Frequency(void) {
    uint64 Frequency = 0;

#ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    Frequency = (uint64)OsIf_Trusted_Call_Return(Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall);
  #else
    Frequency = (uint64)Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall();
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

    return Frequency;
}
/* Return RTC_CLK frequency */
uint32 Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall(void)
{
    uint32 Frequency = (uint32)Clock_Ip_apfFreqTableRTC_CLK[((IP_RTC->RTCC & RTC_RTCC_CLKSEL_MASK) >> RTC_RTCC_CLKSEL_SHIFT)]();                                     /*  Selector value */

    return Frequency;
}
/* Return RTC0_CLK frequency */
static uint64 Clock_Ip_Get_RTC0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_RTC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_SAI0_CLK)
/* Return SAI0_CLK frequency */
static uint64 Clock_Ip_Get_SAI0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK91_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK91_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
/* Return SAI1_CLK frequency */
static uint64 Clock_Ip_Get_SAI1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK55_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK55_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SDA_AP_CLK)
/* Return SDA_AP_CLK frequency */
static uint64 Clock_Ip_Get_SDA_AP_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK21_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK21_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SDADC0_CLK)
/* Return SDADC0_CLK frequency */
static uint64 Clock_Ip_Get_SDADC0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK61_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK61_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SDADC1_CLK)
/* Return SDADC1_CLK frequency */
static uint64 Clock_Ip_Get_SDADC1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK62_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK62_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SDADC2_CLK)
/* Return SDADC2_CLK frequency */
static uint64 Clock_Ip_Get_SDADC2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK63_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK63_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SDADC3_CLK)
/* Return SDADC3_CLK frequency */
static uint64 Clock_Ip_Get_SDADC3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB2_STAT & MC_ME_PRTN3_COFB2_STAT_BLOCK64_MASK) >> MC_ME_PRTN3_COFB2_STAT_BLOCK64_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
/* Return SEMA42_CLK frequency */
static uint64 Clock_Ip_Get_SEMA42_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK24_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK24_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SIPI0_CLK)
/* Return SIPI0_CLK frequency */
static uint64 Clock_Ip_Get_SIPI0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK60_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK60_SHIFT];
    return Frequency;
}
#endif
/* Return SIUL2_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK42_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK42_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_0_CLK)
/* Return SIUL2_PDAC0_0_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_PDAC0_0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK36_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK36_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC0_1_CLK)
/* Return SIUL2_PDAC0_1_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_PDAC0_1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK37_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK37_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_0_CLK)
/* Return SIUL2_PDAC1_0_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_PDAC1_0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK38_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK38_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC1_1_CLK)
/* Return SIUL2_PDAC1_1_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_PDAC1_1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK39_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK39_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_0_CLK)
/* Return SIUL2_PDAC2_0_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_PDAC2_0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK40_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK40_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SIUL2_PDAC2_1_CLK)
/* Return SIUL2_PDAC2_1_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_PDAC2_1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK41_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK41_SHIFT];
    return Frequency;
}
#endif
/* Return STCU0_CLK frequency */
static uint64 Clock_Ip_Get_STCU0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK104_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK104_SHIFT];
    return Frequency;
}
/* Return STMA_CLK frequency */
static uint64 Clock_Ip_Get_STMA_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
/* Return STM0_CLK frequency */
static uint64 Clock_Ip_Get_STM0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_STMA_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK29_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK29_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_STMB_CLK)
/* Return STMB_CLK frequency */
static uint64 Clock_Ip_Get_STMB_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();         /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                     /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                                        /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
/* Return STM1_CLK frequency */
static uint64 Clock_Ip_Get_STM1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_STMB_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK29_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK29_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
/* Return STMC_CLK frequency */
static uint64 Clock_Ip_Get_STMC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_13_CSS & MC_CGM_MUX_13_CSS_SELSTAT_MASK) >> MC_CGM_MUX_13_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_13_DC_0 & MC_CGM_MUX_13_DC_0_DE_MASK) >> MC_CGM_MUX_13_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_13_DC_0 & (uint64)MC_CGM_MUX_13_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_13_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
/* Return STM2_CLK frequency */
static uint64 Clock_Ip_Get_STM2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_STMC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK30_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK30_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_USDHC_PER_CLK)
/* Return USDHC_PER_CLK frequency */
static uint64 Clock_Ip_Get_USDHC_PER_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_14_CSS & MC_CGM_MUX_14_CSS_SELSTAT_MASK) >> MC_CGM_MUX_14_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_14_DC_0 & MC_CGM_MUX_14_DC_0_DE_MASK) >> MC_CGM_MUX_14_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_14_DC_0 & (uint64)MC_CGM_MUX_14_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_14_DC_0_DIV_SHIFT) + 1U);
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK57_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK57_SHIFT];  /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
/* Return SWG_CLK frequency */
static uint64 Clock_Ip_Get_SWG_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_16_CSS & MC_CGM_MUX_16_CSS_SELSTAT_MASK) >> MC_CGM_MUX_16_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_16_DC_0 & MC_CGM_MUX_16_DC_0_DE_MASK) >> MC_CGM_MUX_16_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_16_DC_0 & (uint64)MC_CGM_MUX_16_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_16_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC0_RX_CLK)
/* Return GMAC0_RX_CLK frequency */
static uint64 Clock_Ip_Get_GMAC0_RX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_CLK)
/* Return GMAC0_TX_CLK frequency */
static uint64 Clock_Ip_Get_GMAC0_TX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC_RX_CLK)
/* Return GMAC_RX_CLK frequency */
static uint64 Clock_Ip_Get_GMAC_RX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC_TS_CLK)
/* Return GMAC_TS_CLK frequency */
static uint64 Clock_Ip_Get_GMAC_TS_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DE_MASK) >> MC_CGM_MUX_9_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC_TX_CLK)
/* Return GMAC_TX_CLK frequency */
static uint64 Clock_Ip_Get_GMAC_TX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC0_TX_RMII_CLK)
/* Return GMAC0_TX_RMII_CLK frequency */
static uint64 Clock_Ip_Get_GMAC0_TX_RMII_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_12_CSS & MC_CGM_MUX_12_CSS_SELSTAT_MASK) >> MC_CGM_MUX_12_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_12_DC_0 & MC_CGM_MUX_12_DC_0_DE_MASK) >> MC_CGM_MUX_12_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_12_DC_0 & (uint64)MC_CGM_MUX_12_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_12_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RX_CLK)
/* Return GMAC1_RX_CLK frequency */
static uint64 Clock_Ip_Get_GMAC1_RX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_15_CSS & MC_CGM_MUX_15_CSS_SELSTAT_MASK) >> MC_CGM_MUX_15_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_15_DC_0 & MC_CGM_MUX_15_DC_0_DE_MASK) >> MC_CGM_MUX_15_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_15_DC_0 & (uint64)MC_CGM_MUX_15_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_15_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC1_TX_CLK)
/* Return GMAC1_TX_CLK frequency */
static uint64 Clock_Ip_Get_GMAC1_TX_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_16_CSS & MC_CGM_MUX_16_CSS_SELSTAT_MASK) >> MC_CGM_MUX_16_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_16_DC_0 & MC_CGM_MUX_16_DC_0_DE_MASK) >> MC_CGM_MUX_16_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_16_DC_0 & (uint64)MC_CGM_MUX_16_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_16_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_GMAC1_RMII_CLK)
/* Return GMAC1_RMII_CLK frequency */
static uint64 Clock_Ip_Get_GMAC1_RMII_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_17_CSS & MC_CGM_MUX_17_CSS_SELSTAT_MASK) >> MC_CGM_MUX_17_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_17_DC_0 & MC_CGM_MUX_17_DC_0_DE_MASK) >> MC_CGM_MUX_17_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_17_DC_0 & (uint64)MC_CGM_MUX_17_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_17_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_STMD_CLK)
/* Return STMD_CLK frequency */
static uint64 Clock_Ip_Get_STMD_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_18_CSS & MC_CGM_MUX_18_CSS_SELSTAT_MASK) >> MC_CGM_MUX_18_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_18_DC_0 & MC_CGM_MUX_18_DC_0_DE_MASK) >> MC_CGM_MUX_18_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_18_DC_0 & (uint64)MC_CGM_MUX_18_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_18_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_STM3_CLK)
/* Return STM3_CLK frequency */
static uint64 Clock_Ip_Get_STM3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_STMD_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK31_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK31_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_AES_CLK)
/* Return AES_CLK frequency */
static uint64 Clock_Ip_Get_AES_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_19_CSS & MC_CGM_MUX_19_CSS_SELSTAT_MASK) >> MC_CGM_MUX_19_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_19_DC_0 & MC_CGM_MUX_19_DC_0_DE_MASK) >> MC_CGM_MUX_19_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_19_DC_0 & (uint64)MC_CGM_MUX_19_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_19_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
/* Return SWG0_CLK frequency */
static uint64 Clock_Ip_Get_SWG0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SWG_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK50_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK50_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
/* Return SWG1_CLK frequency */
static uint64 Clock_Ip_Get_SWG1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SWG_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif
/* Return SWT0_CLK frequency */
static uint64 Clock_Ip_Get_SWT0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SIRC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK28_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK28_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_SWT1_CLK)
/* Return SWT1_CLK frequency */
static uint64 Clock_Ip_Get_SWT1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SIRC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK27_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK27_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SWT2_CLK)
/* Return SWT2_CLK frequency */
static uint64 Clock_Ip_Get_SWT2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SIRC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK28_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK28_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_SWT3_CLK)
/* Return SWT3_CLK frequency */
static uint64 Clock_Ip_Get_SWT3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_SIRC_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB0_STAT & MC_ME_PRTN0_COFB0_STAT_BLOCK28_MASK) >> MC_ME_PRTN0_COFB0_STAT_BLOCK28_SHIFT];
    return Frequency;
}
#endif
/* Return TEMPSENSE_CLK frequency */
static uint64 Clock_Ip_Get_TEMPSENSE_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK95_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK95_SHIFT];
    return Frequency;
}
/* Return TRACE_CLK frequency */
static uint64 Clock_Ip_Get_TRACE_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_11_CSS & MC_CGM_MUX_11_CSS_SELSTAT_MASK) >> MC_CGM_MUX_11_CSS_SELSTAT_SHIFT)]();      /*  Selector value */

    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM->MUX_11_DC_0 & MC_CGM_MUX_11_DC_0_DE_MASK) >> MC_CGM_MUX_11_DC_0_DE_SHIFT)];                  /*  Divider enable/disable */
    Frequency /= ((((uint64)IP_MC_CGM->MUX_11_DC_0 & (uint64)MC_CGM_MUX_11_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_11_DC_0_DIV_SHIFT) + 1U);                                     /*  Apply divider value */
    return Frequency;
}
/* Return TRGMUX0_CLK frequency */
static uint64 Clock_Ip_Get_TRGMUX0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_TRGMUX1_CLK)
/* Return TRGMUX1_CLK frequency */
static uint64 Clock_Ip_Get_TRGMUX1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN3_COFB1_STAT & MC_ME_PRTN3_COFB1_STAT_BLOCK48_MASK) >> MC_ME_PRTN3_COFB1_STAT_BLOCK48_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/* Return TSENSE0_CLK frequency */
static uint64 Clock_Ip_Get_TSENSE0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK49_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK49_SHIFT];
    return Frequency;
}
#endif
/* Return WKPU0_CLK frequency */
static uint64 Clock_Ip_Get_WKPU0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK45_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK45_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_XRDC_CLK)
/* Return XRDC_CLK frequency */
static uint64 Clock_Ip_Get_XRDC_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK30_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK30_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_ACCEL_CLK)
/* Return AES_ACCEL_CLK frequency */
static uint64 Clock_Ip_Get_AES_ACCEL_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK112_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK112_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP0_CLK)
/* Return AES_APP0_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP0_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK116_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK116_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP1_CLK)
/* Return AES_APP1_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP1_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK120_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK120_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP2_CLK)
/* Return AES_APP2_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP2_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK124_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK124_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP3_CLK)
/* Return AES_APP3_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP3_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK72_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK72_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP4_CLK)
/* Return AES_APP4_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP4_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK76_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK76_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP5_CLK)
/* Return AES_APP5_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP5_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK80_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK80_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP6_CLK)
/* Return AES_APP6_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP6_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK84_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK84_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_AES_APP7_CLK)
/* Return AES_APP7_CLK frequency */
static uint64 Clock_Ip_Get_AES_APP7_CLK_Frequency(void) {
    uint64 Frequency = Clock_Ip_Get_AES_CLK_Frequency();

    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB2_STAT & MC_ME_PRTN2_COFB2_STAT_BLOCK88_MASK) >> MC_ME_PRTN2_COFB2_STAT_BLOCK88_SHIFT];
    return Frequency;
}
#endif

/* Return Clock_Ip_PLL_VCO frequency */
#define CLOCK_IP_PLL_VCO_MAX_FREQ             (1280000000u)
static uint64 Clock_Ip_PLL_VCO(const PLL_Type *Base)
{
    uint64 Fin;
    uint64 Rdiv;
    uint64 Mfi;
    uint64 Mfn;
    uint64 Fout = 0U;
    uint64 Var1;
    uint64 Var2;
    uint64 Var3;
    uint64 Var4;
    uint64 Var5;
    boolean Overflow = FALSE;

    Fin  = Clock_Ip_Get_FXOSC_CLK_Frequency();   /* input freq */

#ifdef CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX
    #if (CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX == STD_ON)
            if(((Base->PLLCLKMUX & PLL_PLLCLKMUX_REFCLKSEL_MASK) >> PLL_PLLCLKMUX_REFCLKSEL_SHIFT) == CLOCK_IP_FIRC_PLL_REFERENCE)
            {
                Fin  = CLOCK_IP_FIRC_FREQUENCY/2U;   /* input freq */
            }
    #endif /*(CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX == STD_ON)*/
#endif /*CLOCK_IP_PLL_SUPPORTED_PLLCLKMUX*/

    Rdiv = (((uint64)Base->PLLDV & (uint64)PLL_PLLDV_RDIV_MASK) >> (uint64)PLL_PLLDV_RDIV_SHIFT);              /* Rdiv */
    Mfi  = (((uint64)Base->PLLDV & (uint64)PLL_PLLDV_MFI_MASK) >> (uint64)PLL_PLLDV_MFI_SHIFT);                /* Mfi */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    if (IP_PLL_AUX != Base)
    {
#endif
        Mfn  = (((uint64)Base->PLLFD & (uint64)PLL_PLLFD_MFN_MASK) >> (uint64)PLL_PLLFD_MFN_SHIFT);                /* Mfn */
#if defined(CLOCK_IP_HAS_PLLAUX_CLK)
    }
    else
    {

        Mfn = 0;
    }
#endif
    Var1 = Mfi / Rdiv;                                      /* Mfi divided by Rdiv */
    Var2 = Mfi - (Var1 * Rdiv);                             /* Mfi minus Var1 multiplied by Rdiv */
    Var3 = (Rdiv << (uint64)CLOCK_IP_MUL_BY_16384) + (Rdiv << (uint64)CLOCK_IP_MUL_BY_2048);  /* Rdiv multiplied by 18432 */
    Var4 = Fin / Var3;                                      /* Fin divide by (Rdiv multiplied by 18432) */
    Var5 = Fin - (Var4 * Var3);                               /* Fin minus Var4 multiplied by (Rdiv mul 18432) */

    if (0U != Fin)
    {
        if (Var1 == ((uint64)(Var1 * Fin) / Fin))
        {
            Fout = Var1 * Fin;                                      /* Var1 multipied by Fin */
        }
        else
        {
            Overflow = TRUE;
        }

        if ((Var2 == ((uint64)(Fin * Var2) / Fin)) && (CLOCK_IP_PLL_VCO_MAX_FREQ >= Fout))
        {
            Fout += Fin / Rdiv * Var2;                              /* Fin divided by Rdiv and multiplied by Var2 */
        }
        else
        {
            Overflow = TRUE;
        }

        if (0U != Var4)
        {
            if ((Mfn == ((uint64)(Var4 * Mfn) / Var4)) && (CLOCK_IP_PLL_VCO_MAX_FREQ >= Fout))
            {
                Fout += Var4 * Mfn;                                     /* Mfn multiplied by Var4 */
            }
            else
            {
                Overflow = TRUE;
            }
        }

        if (0U != Mfn)
        {
            if ((Var5  == ((uint64)(Var5 * Mfn) / Mfn)) && (CLOCK_IP_PLL_VCO_MAX_FREQ >= Fout))
            {
                Fout += Var5 * Mfn / Var3;                              /* Var5 multiplied by Mfn and divide by (Rdiv mul 18432) */
            }
            else
            {
                Overflow = TRUE;
            }
        }
    }

    if (TRUE == Overflow)
    {
        Fout = 0U;
    }

    return Fout;
}

/* Set frequency value for External Oscillator */
void Clock_Ip_SetExternalOscillatorFrequency(Clock_Ip_NameType ExtOscName, uint64 Frequency)
{
   switch(ExtOscName)
   {
        case FXOSC_CLK:
            Clock_Ip_u32fxosc = Frequency;
            break;
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
        case SXOSC_CLK:
            Clock_Ip_u32sxosc = Frequency;
            break;
#endif
        default:
            /* Do nothing */
            break;
   }
}

/* Return frequency value */
uint64 Clock_Ip_GetFreq(Clock_Ip_NameType ClockName)
{
    return Clock_Ip_apfFreqTable[ClockName]();
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#endif  /* #if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON)) */

/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/* Set frequency value for External Signal */
void Clock_Ip_SetExternalSignalFrequency(Clock_Ip_NameType SignalName, uint64 Frequency)
{
#if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON))
    uint32 Index;

    for (Index = 0U; Index < CLOCK_IP_EXT_SIGNALS_NO; Index++)
    {
        if (SignalName == Clock_Ip_axExtSignalFreqEntries[Index].Name)
        {
            Clock_Ip_axExtSignalFreqEntries[Index].Frequency = Frequency;
            break;
        }
    }
#else
    (void)SignalName;
    (void)Frequency;
#endif
}
/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

