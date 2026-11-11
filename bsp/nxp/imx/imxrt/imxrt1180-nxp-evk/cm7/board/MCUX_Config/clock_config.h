/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BOARD_XTAL0_CLK_HZ 24000000U /*!< Board xtal0 frequency in Hz */

#define BOARD_XTAL32K_CLK_HZ 32768U  /*!< Board xtal32k frequency in Hz */

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes default configuration of clocks.
 *
 */
void BOARD_InitBootClocks(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockRUN configuration
 ******************************************************************************/
#if __CORTEX_M == 7
    #define BOARD_BOOTCLOCKRUN_CORE_CLOCK 792000000UL /*!< CM7 Core clock frequency: 792000000Hz */
#else
    #define BOARD_BOOTCLOCKRUN_CORE_CLOCK 240000000UL /*!< CM33 Core clock frequency: 240000000Hz */
#endif

/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKRUN_ACMP_CLK_ROOT              240000000UL    /* Clock consumers of ACMP_CLK_ROOT output : CMP1, CMP2, CMP3, CMP4 */
#define BOARD_BOOTCLOCKRUN_ADC1_CLK_ROOT              80000000UL     /* Clock consumers of ADC1_CLK_ROOT output : ADC1 */
#define BOARD_BOOTCLOCKRUN_ADC2_CLK_ROOT              80000000UL     /* Clock consumers of ADC2_CLK_ROOT output : ADC2 */
#define BOARD_BOOTCLOCKRUN_ARM_PLL_CLK                792000000UL    /* Clock consumers of ARM_PLL_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_ASRC_CLK_ROOT              240000000UL    /* Clock consumers of ASRC_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_BUS_AON_CLK_ROOT           132000000UL    /* Clock consumers of BUS_AON_CLK_ROOT output : CAN1, CAN3, I3C1, IOMUXC_AON, LPI2C1, LPI2C2, LPIT1, LPSPI1, LPSPI2, LPTMR1, LPUART1, LPUART2, LPUART7, LPUART8, MU2_MUA, MU2_MUB, RTWDOG1, RTWDOG2, RTWDOG3, RTWDOG4, RTWDOG5, SAI1, SEMA1, TPM1, TPM2, TSTMR1_TSTMRA */
#define BOARD_BOOTCLOCKRUN_BUS_WAKEUP_CLK_ROOT        132000000UL    /* Clock consumers of BUS_WAKEUP_CLK_ROOT output : ADC1, ADC2, AOI1, AOI2, AOI3, AOI4, CAN2, CMP1, CMP2, CMP3, CMP4, DAC, EQDC1, EQDC2, EQDC3, EQDC4, EWM, FLEXIO1, FLEXIO2, I3C2, IOMUXC, KPP, LPI2C3, LPI2C4, LPI2C5, LPI2C6, LPIT2, LPIT3, LPSPI3, LPSPI4, LPSPI5, LPSPI6, LPTMR2, LPTMR3, LPUART10, LPUART11, LPUART12, LPUART3, LPUART4, LPUART5, LPUART6, LPUART9, MECC1, MECC2, MU1_MUA, MU1_MUB, PDM, PWM1, PWM2, PWM3, PWM4, RGPIO2, RGPIO3, RGPIO4, RGPIO5, RGPIO6, RTWDOG3, SAI2, SAI3, SAI4, SEMA2, SINC1, SINC2, SINC3, SPDIF, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8, TPM3, TPM4, TPM5, TPM6, TSTMR2_TSTMRA, USBPHY1, USBPHY2, USDHC1, USDHC2, XBAR1, XBAR2, XBAR3 */
#define BOARD_BOOTCLOCKRUN_CAN1_CLK_ROOT              80000000UL     /* Clock consumers of CAN1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CAN2_CLK_ROOT              80000000UL     /* Clock consumers of CAN2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CAN3_CLK_ROOT              80000000UL     /* Clock consumers of CAN3_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CCM_CKO1_CLK_ROOT          80000000UL     /* Clock consumers of CCM_CKO1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CCM_CKO2_CLK_ROOT          50000000UL     /* Clock consumers of CCM_CKO2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CLK_1M                     1000000UL      /* Clock consumers of CLK_1M output : EWM, GPT1, GPT2 */
#define BOARD_BOOTCLOCKRUN_ECAT_CLK_ROOT              100000000UL    /* Clock consumers of ECAT_CLK_ROOT output : ECAT */
#define BOARD_BOOTCLOCKRUN_ECAT_PORT0_REF_CLK         50000000UL     /* Clock consumers of ECAT_PORT0_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_ECAT_PORT1_REF_CLK         50000000UL     /* Clock consumers of ECAT_PORT1_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_EDGELOCK_CLK_ROOT          200000000UL    /* Clock consumers of EDGELOCK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_ENET_REFCLK_ROOT           125000000UL    /* Clock consumers of ENET_REFCLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_FLEXIO1_CLK_ROOT           120000000UL    /* Clock consumers of FLEXIO1_CLK_ROOT output : FLEXIO1 */
#define BOARD_BOOTCLOCKRUN_FLEXIO2_CLK_ROOT           48000000UL     /* Clock consumers of FLEXIO2_CLK_ROOT output : FLEXIO2 */
#define BOARD_BOOTCLOCKRUN_FLEXSPI1_CLK_ROOT          130909090UL    /* Clock consumers of FLEXSPI1_CLK_ROOT output : FLEXSPI1 */
#define BOARD_BOOTCLOCKRUN_FLEXSPI2_CLK_ROOT          196363636UL    /* Clock consumers of FLEXSPI2_CLK_ROOT output : FLEXSPI2 */
#define BOARD_BOOTCLOCKRUN_FLEXSPI_SLV_CLK_ROOT       132000000UL    /* Clock consumers of FLEXSPI_SLV_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT1_CLK_ROOT              240000000UL    /* Clock consumers of GPT1_CLK_ROOT output : GPT1 */
#define BOARD_BOOTCLOCKRUN_GPT2_CLK_ROOT              240000000UL    /* Clock consumers of GPT2_CLK_ROOT output : GPT2 */
#define BOARD_BOOTCLOCKRUN_I3C1_CLK_ROOT              24000000UL     /* Clock consumers of I3C1_CLK_ROOT output : I3C1 */
#define BOARD_BOOTCLOCKRUN_I3C2_CLK_ROOT              24000000UL     /* Clock consumers of I3C2_CLK_ROOT output : I3C2 */
#define BOARD_BOOTCLOCKRUN_LPI2C0102_CLK_ROOT         60000000UL     /* Clock consumers of LPI2C0102_CLK_ROOT output : LPI2C1, LPI2C2 */
#define BOARD_BOOTCLOCKRUN_LPI2C0304_CLK_ROOT         60000000UL     /* Clock consumers of LPI2C0304_CLK_ROOT output : LPI2C3, LPI2C4 */
#define BOARD_BOOTCLOCKRUN_LPI2C0506_CLK_ROOT         60000000UL     /* Clock consumers of LPI2C0506_CLK_ROOT output : LPI2C5, LPI2C6 */
#define BOARD_BOOTCLOCKRUN_LPIT3_CLK_ROOT             80000000UL     /* Clock consumers of LPIT3_CLK_ROOT output : LPIT3 */
#define BOARD_BOOTCLOCKRUN_LPSPI0102_CLK_ROOT         130909090UL    /* Clock consumers of LPSPI0102_CLK_ROOT output : LPSPI1, LPSPI2 */
#define BOARD_BOOTCLOCKRUN_LPSPI0304_CLK_ROOT         130909090UL    /* Clock consumers of LPSPI0304_CLK_ROOT output : LPSPI3, LPSPI4 */
#define BOARD_BOOTCLOCKRUN_LPSPI0506_CLK_ROOT         130909090UL    /* Clock consumers of LPSPI0506_CLK_ROOT output : LPSPI5, LPSPI6 */
#define BOARD_BOOTCLOCKRUN_LPTMR1_CLK_ROOT            80000000UL     /* Clock consumers of LPTMR1_CLK_ROOT output : LPTMR1 */
#define BOARD_BOOTCLOCKRUN_LPTMR2_CLK_ROOT            80000000UL     /* Clock consumers of LPTMR2_CLK_ROOT output : LPTMR2 */
#define BOARD_BOOTCLOCKRUN_LPTMR3_CLK_ROOT            80000000UL     /* Clock consumers of LPTMR3_CLK_ROOT output : LPTMR3 */
#define BOARD_BOOTCLOCKRUN_LPUART0102_CLK_ROOT        24000000UL     /* Clock consumers of LPUART0102_CLK_ROOT output : LPUART1, LPUART2 */
#define BOARD_BOOTCLOCKRUN_LPUART0304_CLK_ROOT        24000000UL     /* Clock consumers of LPUART0304_CLK_ROOT output : LPUART3, LPUART4 */
#define BOARD_BOOTCLOCKRUN_LPUART0506_CLK_ROOT        24000000UL     /* Clock consumers of LPUART0506_CLK_ROOT output : LPUART5, LPUART6 */
#define BOARD_BOOTCLOCKRUN_LPUART0708_CLK_ROOT        24000000UL     /* Clock consumers of LPUART0708_CLK_ROOT output : LPUART7, LPUART8 */
#define BOARD_BOOTCLOCKRUN_LPUART0910_CLK_ROOT        24000000UL     /* Clock consumers of LPUART0910_CLK_ROOT output : LPUART10, LPUART9 */
#define BOARD_BOOTCLOCKRUN_LPUART1112_CLK_ROOT        24000000UL     /* Clock consumers of LPUART1112_CLK_ROOT output : LPUART11, LPUART12 */
#define BOARD_BOOTCLOCKRUN_M33_CLK_ROOT               240000000UL    /* Clock consumers of M33_CLK_ROOT output : ARM, DMA3, FLEXSPI2, RGPIO1, SysTick0 */
#define BOARD_BOOTCLOCKRUN_M33_SYSTICK_CLK_ROOT       100000UL       /* Clock consumers of M33_SYSTICK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_M7_CLK_ROOT                792000000UL    /* Clock consumers of M7_CLK_ROOT output : ARM, SysTick1 */
#define BOARD_BOOTCLOCKRUN_M7_SYSTICK_CLK_ROOT        100000UL       /* Clock consumers of M7_SYSTICK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_MAC0_CLK_ROOT              50000000UL     /* Clock consumers of MAC0_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_MAC1_CLK_ROOT              125000000UL    /* Clock consumers of MAC1_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_MAC2_CLK_ROOT              125000000UL    /* Clock consumers of MAC2_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_MAC3_CLK_ROOT              125000000UL    /* Clock consumers of MAC3_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_MAC4_CLK_ROOT              50000000UL     /* Clock consumers of MAC4_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_MIC_CLK_ROOT               80000000UL     /* Clock consumers of MIC_CLK_ROOT output : PDM, SPDIF */
#define BOARD_BOOTCLOCKRUN_NETC_CLK_ROOT              240000000UL    /* Clock consumers of NETC_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_NETC_PORT0_REF_CLK         50000000UL     /* Clock consumers of NETC_PORT0_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_NETC_PORT1_REF_CLK         50000000UL     /* Clock consumers of NETC_PORT1_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_NETC_PORT2_REF_CLK         50000000UL     /* Clock consumers of NETC_PORT2_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_NETC_PORT3_REF_CLK         50000000UL     /* Clock consumers of NETC_PORT3_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_NETC_PORT4_REF_CLK         50000000UL     /* Clock consumers of NETC_PORT4_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_OSC_24M                    24000000UL     /* Clock consumers of OSC_24M output : CAN1, CAN2, CAN3, DAC, GPT1, GPT2, SPDIF, TMPSNS */
#define BOARD_BOOTCLOCKRUN_OSC_32K                    32768UL        /* Clock consumers of OSC_32K output : CMP1, CMP2, CMP3, CMP4, EWM, GPT1, GPT2, KPP, LPTMR1, LPTMR2, LPTMR3, RTWDOG1, RTWDOG2, RTWDOG3, RTWDOG4, RTWDOG5, USBPHY1, USBPHY2, USB_OTG1, USB_OTG2, USDHC1, USDHC2 */
#define BOARD_BOOTCLOCKRUN_OSC_RC_24M                 24000000UL     /* Clock consumers of OSC_RC_24M output : DCDC, EWM, RTWDOG1, RTWDOG2, RTWDOG3, RTWDOG4, RTWDOG5 */
#define BOARD_BOOTCLOCKRUN_OSC_RC_400M                400000000UL    /* Clock consumers of OSC_RC_400M output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_CLK              0UL            /* Clock consumers of PLL_AUDIO_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_SS_MODULATION    0UL            /* Clock consumers of PLL_AUDIO_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_SS_RANGE         0UL            /* Clock consumers of PLL_AUDIO_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_SAI1_CLK_ROOT              0UL            /* Clock consumers of SAI1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK1                 0UL            /* Clock consumers of SAI1_MCLK1 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK2                 0UL            /* Clock consumers of SAI1_MCLK2 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_SAI2_CLK_ROOT              0UL            /* Clock consumers of SAI2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK1                 0UL            /* Clock consumers of SAI2_MCLK1 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK2                 0UL            /* Clock consumers of SAI2_MCLK2 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK3                 0UL            /* Clock consumers of SAI2_MCLK3 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_SAI3_CLK_ROOT              0UL            /* Clock consumers of SAI3_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK1                 0UL            /* Clock consumers of SAI3_MCLK1 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK2                 0UL            /* Clock consumers of SAI3_MCLK2 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK3                 0UL            /* Clock consumers of SAI3_MCLK3 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_SAI4_CLK_ROOT              0UL            /* Clock consumers of SAI4_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK1                 0UL            /* Clock consumers of SAI4_MCLK1 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK2                 0UL            /* Clock consumers of SAI4_MCLK2 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK3                 0UL            /* Clock consumers of SAI4_MCLK3 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_SEMC_CLK_ROOT              200000000UL    /* Clock consumers of SEMC_CLK_ROOT output : SEMC */
#define BOARD_BOOTCLOCKRUN_SPDIF_CLK_ROOT             0UL            /* Clock consumers of SPDIF_CLK_ROOT output : SPDIF */
#define BOARD_BOOTCLOCKRUN_SPDIF_EXTCLK_OUT           0UL            /* Clock consumers of SPDIF_EXTCLK_OUT output : N/A */
#define BOARD_BOOTCLOCKRUN_SWO_TRACE_CLK_ROOT         80000000UL     /* Clock consumers of SWO_TRACE_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_CLK               1000000000UL   /* Clock consumers of SYS_PLL1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_DIV2_CLK          500000000UL    /* Clock consumers of SYS_PLL1_DIV2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_DIV5_CLK          200000000UL    /* Clock consumers of SYS_PLL1_DIV5_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_SS_MODULATION     0UL            /* Clock consumers of SYS_PLL1_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_SS_RANGE          0UL            /* Clock consumers of SYS_PLL1_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_CLK               528000000UL    /* Clock consumers of SYS_PLL2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD0_CLK          352000000UL    /* Clock consumers of SYS_PLL2_PFD0_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD1_CLK          594000000UL    /* Clock consumers of SYS_PLL2_PFD1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD2_CLK          396000000UL    /* Clock consumers of SYS_PLL2_PFD2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_PFD3_CLK          297000000UL    /* Clock consumers of SYS_PLL2_PFD3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_SS_MODULATION     0UL            /* Clock consumers of SYS_PLL2_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL2_SS_RANGE          0UL            /* Clock consumers of SYS_PLL2_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_CLK               480000000UL    /* Clock consumers of SYS_PLL3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_DIV2_CLK          240000000UL    /* Clock consumers of SYS_PLL3_DIV2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD0_CLK          392727272UL    /* Clock consumers of SYS_PLL3_PFD0_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD1_CLK          261818181UL    /* Clock consumers of SYS_PLL3_PFD1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD2_CLK          392727272UL    /* Clock consumers of SYS_PLL3_PFD2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD3_CLK          480000000UL    /* Clock consumers of SYS_PLL3_PFD3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_TMR_1588_CLK_ROOT          240000000UL    /* Clock consumers of TMR_1588_CLK_ROOT output : NETC */
#define BOARD_BOOTCLOCKRUN_TMR_1588_REF_CLK           240000000UL    /* Clock consumers of TMR_1588_REF_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_TPM2_CLK_ROOT              80000000UL     /* Clock consumers of TPM2_CLK_ROOT output : TPM2 */
#define BOARD_BOOTCLOCKRUN_TPM4_CLK_ROOT              80000000UL     /* Clock consumers of TPM4_CLK_ROOT output : TPM4 */
#define BOARD_BOOTCLOCKRUN_TPM5_CLK_ROOT              80000000UL     /* Clock consumers of TPM5_CLK_ROOT output : TPM5 */
#define BOARD_BOOTCLOCKRUN_TPM6_CLK_ROOT              80000000UL     /* Clock consumers of TPM6_CLK_ROOT output : TPM6 */
#define BOARD_BOOTCLOCKRUN_USDHC1_CLK_ROOT            198000000UL    /* Clock consumers of USDHC1_CLK_ROOT output : USDHC1 */
#define BOARD_BOOTCLOCKRUN_USDHC2_CLK_ROOT            396000000UL    /* Clock consumers of USDHC2_CLK_ROOT output : USDHC2 */
#define BOARD_BOOTCLOCKRUN_WAKEUP_AXI_CLK_ROOT        240000000UL    /* Clock consumers of WAKEUP_AXI_CLK_ROOT output : DMA4, FLEXSPI1, IEE, MECC1, MECC2, USB_OTG1, USB_OTG2, USDHC1, USDHC2 */


/*******************************************************************************
 * API for BOARD_BootClockRUN configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockRUN(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */

