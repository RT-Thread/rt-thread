/*
 * Copyright 2022-2023 NXP
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
    #define BOARD_BOOTCLOCKRUN_CORE_CLOCK 996000000UL /*!< CM7 Core clock frequency: 996000000Hz */
#else
    #define BOARD_BOOTCLOCKRUN_CORE_CLOCK 392727272UL /*!< CM4 Core clock frequency: 392727272Hz */
#endif

/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKRUN_ACMP_CLK_ROOT              24000000UL     /* Clock consumers of ACMP_CLK_ROOT output : CMP1, CMP2, CMP3, CMP4 */
#define BOARD_BOOTCLOCKRUN_ADC1_CLK_ROOT              24000000UL     /* Clock consumers of ADC1_CLK_ROOT output : LPADC1 */
#define BOARD_BOOTCLOCKRUN_ADC2_CLK_ROOT              24000000UL     /* Clock consumers of ADC2_CLK_ROOT output : LPADC2 */
#define BOARD_BOOTCLOCKRUN_ARM_PLL_CLK                996000000UL    /* Clock consumers of ARM_PLL_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_ASRC_CLK_ROOT              24000000UL     /* Clock consumers of ASRC_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_AXI_CLK_ROOT               996000000UL    /* Clock consumers of AXI_CLK_ROOT output : FLEXRAM */
#define BOARD_BOOTCLOCKRUN_BUS_CLK_ROOT               240000000UL    /* Clock consumers of BUS_CLK_ROOT output : ADC_ETC, AOI1, AOI2, CAAM, CAN1, CAN2, CM7_GPIO2, CM7_GPIO3, CMP1, CMP2, CMP3, CMP4, CSI, DAC, DMA0, DMAMUX0, DSI_HOST, EMVSIM1, EMVSIM2, ENC1, ENC2, ENC3, ENC4, ENET, ENET_1G, ENET_QOS, EWM, FLEXIO1, FLEXIO2, FLEXSPI1, FLEXSPI2, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, IEE_APC, IOMUXC, IOMUXC_GPR, KPP, LCDIF, LCDIFV2, LPADC1, LPADC2, LPI2C1, LPI2C2, LPI2C3, LPI2C4, LPSPI1, LPSPI2, LPSPI3, LPSPI4, LPUART1, LPUART10, LPUART2, LPUART3, LPUART4, LPUART5, LPUART6, LPUART7, LPUART8, LPUART9, MECC1, MECC2, MIPI_CSI2RX, PIT1, PWM1, PWM2, PWM3, PWM4, PXP, RTWDOG3, SAI1, SAI2, SAI3, SPDIF, TMR1, TMR2, TMR3, TMR4, USBPHY1, USBPHY2, USB_OTG1, USB_OTG2, USDHC1, USDHC2, WDOG1, WDOG2, XBARA1, XBARB2, XBARB3, XECC_FLEXSPI1, XECC_FLEXSPI2, XECC_SEMC, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_BUS_LPSR_CLK_ROOT          160000000UL    /* Clock consumers of BUS_LPSR_CLK_ROOT output : CAN3, GPIO10, GPIO11, GPIO12, GPIO7, GPIO8, GPIO9, IOMUXC_LPSR, LPI2C5, LPI2C6, LPSPI5, LPSPI6, LPUART11, LPUART12, MUA, MUB, PDM, PIT2, RDC, RTWDOG4, SAI4, SNVS, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_CAN1_CLK_ROOT              24000000UL     /* Clock consumers of CAN1_CLK_ROOT output : CAN1 */
#define BOARD_BOOTCLOCKRUN_CAN2_CLK_ROOT              24000000UL     /* Clock consumers of CAN2_CLK_ROOT output : CAN2 */
#define BOARD_BOOTCLOCKRUN_CAN3_CLK_ROOT              24000000UL     /* Clock consumers of CAN3_CLK_ROOT output : CAN3 */
#define BOARD_BOOTCLOCKRUN_CCM_CLKO1_CLK_ROOT         24000000UL     /* Clock consumers of CCM_CLKO1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CCM_CLKO2_CLK_ROOT         24000000UL     /* Clock consumers of CCM_CLKO2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CLK_1M                     1000000UL      /* Clock consumers of CLK_1M output : EWM, RTWDOG3, RTWDOG4 */
#define BOARD_BOOTCLOCKRUN_CSI2_CLK_ROOT              24000000UL     /* Clock consumers of CSI2_CLK_ROOT output : MIPI_CSI2RX */
#define BOARD_BOOTCLOCKRUN_CSI2_ESC_CLK_ROOT          24000000UL     /* Clock consumers of CSI2_ESC_CLK_ROOT output : MIPI_CSI2RX */
#define BOARD_BOOTCLOCKRUN_CSI2_UI_CLK_ROOT           24000000UL     /* Clock consumers of CSI2_UI_CLK_ROOT output : MIPI_CSI2RX */
#define BOARD_BOOTCLOCKRUN_CSI_CLK_ROOT               24000000UL     /* Clock consumers of CSI_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_CSSYS_CLK_ROOT             24000000UL     /* Clock consumers of CSSYS_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_CSTRACE_CLK_ROOT           132000000UL    /* Clock consumers of CSTRACE_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_ELCDIF_CLK_ROOT            24000000UL     /* Clock consumers of ELCDIF_CLK_ROOT output : LCDIF */
#define BOARD_BOOTCLOCKRUN_EMV1_CLK_ROOT              24000000UL     /* Clock consumers of EMV1_CLK_ROOT output : EMVSIM1 */
#define BOARD_BOOTCLOCKRUN_EMV2_CLK_ROOT              24000000UL     /* Clock consumers of EMV2_CLK_ROOT output : EMVSIM2 */
#define BOARD_BOOTCLOCKRUN_ENET1_CLK_ROOT             24000000UL     /* Clock consumers of ENET1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_ENET2_CLK_ROOT             24000000UL     /* Clock consumers of ENET2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_ENET_1G_REF_CLK            0UL            /* Clock consumers of ENET_1G_REF_CLK output : ENET_1G */
#define BOARD_BOOTCLOCKRUN_ENET_1G_TX_CLK             24000000UL     /* Clock consumers of ENET_1G_TX_CLK output : ENET_1G */
#define BOARD_BOOTCLOCKRUN_ENET_25M_CLK_ROOT          24000000UL     /* Clock consumers of ENET_25M_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_ENET_QOS_CLK_ROOT          24000000UL     /* Clock consumers of ENET_QOS_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_ENET_QOS_REF_CLK           0UL            /* Clock consumers of ENET_QOS_REF_CLK output : ENET_QOS */
#define BOARD_BOOTCLOCKRUN_ENET_QOS_TX_CLK            0UL            /* Clock consumers of ENET_QOS_TX_CLK output : ENET_QOS */
#define BOARD_BOOTCLOCKRUN_ENET_REF_CLK               0UL            /* Clock consumers of ENET_REF_CLK output : ENET */
#define BOARD_BOOTCLOCKRUN_ENET_TIMER1_CLK_ROOT       24000000UL     /* Clock consumers of ENET_TIMER1_CLK_ROOT output : ENET */
#define BOARD_BOOTCLOCKRUN_ENET_TIMER2_CLK_ROOT       24000000UL     /* Clock consumers of ENET_TIMER2_CLK_ROOT output : ENET_1G */
#define BOARD_BOOTCLOCKRUN_ENET_TIMER3_CLK_ROOT       24000000UL     /* Clock consumers of ENET_TIMER3_CLK_ROOT output : ENET_QOS */
#define BOARD_BOOTCLOCKRUN_ENET_TX_CLK                0UL            /* Clock consumers of ENET_TX_CLK output : ENET */
#define BOARD_BOOTCLOCKRUN_FLEXIO1_CLK_ROOT           24000000UL     /* Clock consumers of FLEXIO1_CLK_ROOT output : FLEXIO1 */
#define BOARD_BOOTCLOCKRUN_FLEXIO2_CLK_ROOT           24000000UL     /* Clock consumers of FLEXIO2_CLK_ROOT output : FLEXIO2 */
#define BOARD_BOOTCLOCKRUN_FLEXSPI1_CLK_ROOT          24000000UL     /* Clock consumers of FLEXSPI1_CLK_ROOT output : FLEXSPI1 */
#define BOARD_BOOTCLOCKRUN_FLEXSPI2_CLK_ROOT          24000000UL     /* Clock consumers of FLEXSPI2_CLK_ROOT output : FLEXSPI2 */
#define BOARD_BOOTCLOCKRUN_GC355_CLK_ROOT             492000012UL    /* Clock consumers of GC355_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT1_CLK_ROOT              24000000UL     /* Clock consumers of GPT1_CLK_ROOT output : GPT1 */
#define BOARD_BOOTCLOCKRUN_GPT1_IPG_CLK_HIGHFREQ      24000000UL     /* Clock consumers of GPT1_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT2_CLK_ROOT              24000000UL     /* Clock consumers of GPT2_CLK_ROOT output : GPT2 */
#define BOARD_BOOTCLOCKRUN_GPT2_IPG_CLK_HIGHFREQ      24000000UL     /* Clock consumers of GPT2_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT3_CLK_ROOT              24000000UL     /* Clock consumers of GPT3_CLK_ROOT output : GPT3 */
#define BOARD_BOOTCLOCKRUN_GPT3_IPG_CLK_HIGHFREQ      24000000UL     /* Clock consumers of GPT3_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT4_CLK_ROOT              24000000UL     /* Clock consumers of GPT4_CLK_ROOT output : GPT4 */
#define BOARD_BOOTCLOCKRUN_GPT4_IPG_CLK_HIGHFREQ      24000000UL     /* Clock consumers of GPT4_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT5_CLK_ROOT              24000000UL     /* Clock consumers of GPT5_CLK_ROOT output : GPT5 */
#define BOARD_BOOTCLOCKRUN_GPT5_IPG_CLK_HIGHFREQ      24000000UL     /* Clock consumers of GPT5_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_GPT6_CLK_ROOT              24000000UL     /* Clock consumers of GPT6_CLK_ROOT output : GPT6 */
#define BOARD_BOOTCLOCKRUN_GPT6_IPG_CLK_HIGHFREQ      24000000UL     /* Clock consumers of GPT6_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_LCDIFV2_CLK_ROOT           24000000UL     /* Clock consumers of LCDIFV2_CLK_ROOT output : LCDIFV2 */
#define BOARD_BOOTCLOCKRUN_LPI2C1_CLK_ROOT            24000000UL     /* Clock consumers of LPI2C1_CLK_ROOT output : LPI2C1 */
#define BOARD_BOOTCLOCKRUN_LPI2C2_CLK_ROOT            24000000UL     /* Clock consumers of LPI2C2_CLK_ROOT output : LPI2C2 */
#define BOARD_BOOTCLOCKRUN_LPI2C3_CLK_ROOT            24000000UL     /* Clock consumers of LPI2C3_CLK_ROOT output : LPI2C3 */
#define BOARD_BOOTCLOCKRUN_LPI2C4_CLK_ROOT            24000000UL     /* Clock consumers of LPI2C4_CLK_ROOT output : LPI2C4 */
#define BOARD_BOOTCLOCKRUN_LPI2C5_CLK_ROOT            24000000UL     /* Clock consumers of LPI2C5_CLK_ROOT output : LPI2C5 */
#define BOARD_BOOTCLOCKRUN_LPI2C6_CLK_ROOT            24000000UL     /* Clock consumers of LPI2C6_CLK_ROOT output : LPI2C6 */
#define BOARD_BOOTCLOCKRUN_LPSPI1_CLK_ROOT            24000000UL     /* Clock consumers of LPSPI1_CLK_ROOT output : LPSPI1 */
#define BOARD_BOOTCLOCKRUN_LPSPI2_CLK_ROOT            24000000UL     /* Clock consumers of LPSPI2_CLK_ROOT output : LPSPI2 */
#define BOARD_BOOTCLOCKRUN_LPSPI3_CLK_ROOT            24000000UL     /* Clock consumers of LPSPI3_CLK_ROOT output : LPSPI3 */
#define BOARD_BOOTCLOCKRUN_LPSPI4_CLK_ROOT            24000000UL     /* Clock consumers of LPSPI4_CLK_ROOT output : LPSPI4 */
#define BOARD_BOOTCLOCKRUN_LPSPI5_CLK_ROOT            24000000UL     /* Clock consumers of LPSPI5_CLK_ROOT output : LPSPI5 */
#define BOARD_BOOTCLOCKRUN_LPSPI6_CLK_ROOT            24000000UL     /* Clock consumers of LPSPI6_CLK_ROOT output : LPSPI6 */
#define BOARD_BOOTCLOCKRUN_LPUART10_CLK_ROOT          24000000UL     /* Clock consumers of LPUART10_CLK_ROOT output : LPUART10 */
#define BOARD_BOOTCLOCKRUN_LPUART11_CLK_ROOT          24000000UL     /* Clock consumers of LPUART11_CLK_ROOT output : LPUART11 */
#define BOARD_BOOTCLOCKRUN_LPUART12_CLK_ROOT          24000000UL     /* Clock consumers of LPUART12_CLK_ROOT output : LPUART12 */
#define BOARD_BOOTCLOCKRUN_LPUART1_CLK_ROOT           24000000UL     /* Clock consumers of LPUART1_CLK_ROOT output : LPUART1 */
#define BOARD_BOOTCLOCKRUN_LPUART2_CLK_ROOT           24000000UL     /* Clock consumers of LPUART2_CLK_ROOT output : LPUART2 */
#define BOARD_BOOTCLOCKRUN_LPUART3_CLK_ROOT           24000000UL     /* Clock consumers of LPUART3_CLK_ROOT output : LPUART3 */
#define BOARD_BOOTCLOCKRUN_LPUART4_CLK_ROOT           24000000UL     /* Clock consumers of LPUART4_CLK_ROOT output : LPUART4 */
#define BOARD_BOOTCLOCKRUN_LPUART5_CLK_ROOT           24000000UL     /* Clock consumers of LPUART5_CLK_ROOT output : LPUART5 */
#define BOARD_BOOTCLOCKRUN_LPUART6_CLK_ROOT           24000000UL     /* Clock consumers of LPUART6_CLK_ROOT output : LPUART6 */
#define BOARD_BOOTCLOCKRUN_LPUART7_CLK_ROOT           24000000UL     /* Clock consumers of LPUART7_CLK_ROOT output : LPUART7 */
#define BOARD_BOOTCLOCKRUN_LPUART8_CLK_ROOT           24000000UL     /* Clock consumers of LPUART8_CLK_ROOT output : LPUART8 */
#define BOARD_BOOTCLOCKRUN_LPUART9_CLK_ROOT           24000000UL     /* Clock consumers of LPUART9_CLK_ROOT output : LPUART9 */
#define BOARD_BOOTCLOCKRUN_M4_CLK_ROOT                392727272UL    /* Clock consumers of M4_CLK_ROOT output : ARM, DMA1, DMAMUX1, SSARC_HP, SSARC_LP, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_M4_SYSTICK_CLK_ROOT        24000000UL     /* Clock consumers of M4_SYSTICK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_M7_CLK_ROOT                996000000UL    /* Clock consumers of M7_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_M7_SYSTICK_CLK_ROOT        100000UL       /* Clock consumers of M7_SYSTICK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_MIC_CLK_ROOT               24000000UL     /* Clock consumers of MIC_CLK_ROOT output : ASRC, PDM, SPDIF */
#define BOARD_BOOTCLOCKRUN_MIPI_DSI_TX_CLK_ESC_ROOT   24000000UL     /* Clock consumers of MIPI_DSI_TX_CLK_ESC_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_MIPI_ESC_CLK_ROOT          24000000UL     /* Clock consumers of MIPI_ESC_CLK_ROOT output : DSI_HOST */
#define BOARD_BOOTCLOCKRUN_MIPI_REF_CLK_ROOT          24000000UL     /* Clock consumers of MIPI_REF_CLK_ROOT output : DSI_HOST */
#define BOARD_BOOTCLOCKRUN_MQS_CLK_ROOT               24000000UL     /* Clock consumers of MQS_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_MQS_MCLK                   24000000UL     /* Clock consumers of MQS_MCLK output : N/A */
#define BOARD_BOOTCLOCKRUN_OSC_24M                    24000000UL     /* Clock consumers of OSC_24M output : SPDIF, TMPSNS, USBPHY1, USBPHY2 */
#define BOARD_BOOTCLOCKRUN_OSC_32K                    32768UL        /* Clock consumers of OSC_32K output : GPIO13, RTWDOG3, RTWDOG4 */
#define BOARD_BOOTCLOCKRUN_OSC_RC_16M                 16000000UL     /* Clock consumers of OSC_RC_16M output : CCM, DCDC, EWM, GPT1, GPT2, GPT3, GPT4, GPT5, GPT6, SSARC_LP */
#define BOARD_BOOTCLOCKRUN_OSC_RC_400M                400000000UL    /* Clock consumers of OSC_RC_400M output : N/A */
#define BOARD_BOOTCLOCKRUN_OSC_RC_48M                 48000000UL     /* Clock consumers of OSC_RC_48M output : N/A */
#define BOARD_BOOTCLOCKRUN_OSC_RC_48M_DIV2            24000000UL     /* Clock consumers of OSC_RC_48M_DIV2 output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_CLK              0UL            /* Clock consumers of PLL_AUDIO_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_SS_MODULATION    0UL            /* Clock consumers of PLL_AUDIO_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_AUDIO_SS_RANGE         0UL            /* Clock consumers of PLL_AUDIO_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_VIDEO_CLK              984000025UL    /* Clock consumers of PLL_VIDEO_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_VIDEO_SS_MODULATION    0UL            /* Clock consumers of PLL_VIDEO_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_PLL_VIDEO_SS_RANGE         0UL            /* Clock consumers of PLL_VIDEO_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_SAI1_CLK_ROOT              24000000UL     /* Clock consumers of SAI1_CLK_ROOT output : SPDIF */
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK1                 24000000UL     /* Clock consumers of SAI1_MCLK1 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK2                 0UL            /* Clock consumers of SAI1_MCLK2 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_SAI1_MCLK3                 24000000UL     /* Clock consumers of SAI1_MCLK3 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_SAI2_CLK_ROOT              24000000UL     /* Clock consumers of SAI2_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK1                 24000000UL     /* Clock consumers of SAI2_MCLK1 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK2                 0UL            /* Clock consumers of SAI2_MCLK2 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_SAI2_MCLK3                 24000000UL     /* Clock consumers of SAI2_MCLK3 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_SAI3_CLK_ROOT              24000000UL     /* Clock consumers of SAI3_CLK_ROOT output : ASRC, SPDIF */
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK1                 24000000UL     /* Clock consumers of SAI3_MCLK1 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK2                 0UL            /* Clock consumers of SAI3_MCLK2 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_SAI3_MCLK3                 24000000UL     /* Clock consumers of SAI3_MCLK3 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_SAI4_CLK_ROOT              24000000UL     /* Clock consumers of SAI4_CLK_ROOT output : ASRC, SPDIF */
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK1                 24000000UL     /* Clock consumers of SAI4_MCLK1 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_SAI4_MCLK2                 0UL            /* Clock consumers of SAI4_MCLK2 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_SEMC_CLK_ROOT              198000000UL    /* Clock consumers of SEMC_CLK_ROOT output : SEMC, XECC_FLEXSPI1, XECC_FLEXSPI2, XECC_SEMC, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_SPDIF_CLK_ROOT             24000000UL     /* Clock consumers of SPDIF_CLK_ROOT output : SPDIF */
#define BOARD_BOOTCLOCKRUN_SPDIF_EXTCLK_OUT           0UL            /* Clock consumers of SPDIF_EXTCLK_OUT output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_CLK               0UL            /* Clock consumers of SYS_PLL1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_DIV2_CLK          0UL            /* Clock consumers of SYS_PLL1_DIV2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL1_DIV5_CLK          0UL            /* Clock consumers of SYS_PLL1_DIV5_CLK output : N/A */
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
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD0_CLK          664615384UL    /* Clock consumers of SYS_PLL3_PFD0_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD1_CLK          508235294UL    /* Clock consumers of SYS_PLL3_PFD1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD2_CLK          270000000UL    /* Clock consumers of SYS_PLL3_PFD2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_SYS_PLL3_PFD3_CLK          392727272UL    /* Clock consumers of SYS_PLL3_PFD3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_USDHC1_CLK_ROOT            24000000UL     /* Clock consumers of USDHC1_CLK_ROOT output : USDHC1 */
#define BOARD_BOOTCLOCKRUN_USDHC2_CLK_ROOT            24000000UL     /* Clock consumers of USDHC2_CLK_ROOT output : USDHC2 */


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

/*******************************************************************************
 ******************* Configuration BOARD_BootClockRUN_800M *********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockRUN_800M configuration
 ******************************************************************************/
#if __CORTEX_M == 7
    #define BOARD_BOOTCLOCKRUN_800M_CORE_CLOCK 798000000UL /*!< CM7 Core clock frequency: 798000000Hz */
#else
    #define BOARD_BOOTCLOCKRUN_800M_CORE_CLOCK 392727272UL /*!< CM4 Core clock frequency: 392727272Hz */
#endif

/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKRUN_800M_ACMP_CLK_ROOT         24000000UL     /* Clock consumers of ACMP_CLK_ROOT output : CMP1, CMP2, CMP3, CMP4 */
#define BOARD_BOOTCLOCKRUN_800M_ADC1_CLK_ROOT         24000000UL     /* Clock consumers of ADC1_CLK_ROOT output : LPADC1 */
#define BOARD_BOOTCLOCKRUN_800M_ADC2_CLK_ROOT         24000000UL     /* Clock consumers of ADC2_CLK_ROOT output : LPADC2 */
#define BOARD_BOOTCLOCKRUN_800M_ARM_PLL_CLK           798000000UL    /* Clock consumers of ARM_PLL_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_ASRC_CLK_ROOT         24000000UL     /* Clock consumers of ASRC_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_800M_AXI_CLK_ROOT          798000000UL    /* Clock consumers of AXI_CLK_ROOT output : FLEXRAM */
#define BOARD_BOOTCLOCKRUN_800M_BUS_CLK_ROOT          240000000UL    /* Clock consumers of BUS_CLK_ROOT output : ADC_ETC, AOI1, AOI2, CAAM, CAN1, CAN2, CM7_GPIO2, CM7_GPIO3, CMP1, CMP2, CMP3, CMP4, CSI, DAC, DMA0, DMAMUX0, DSI_HOST, EMVSIM1, EMVSIM2, ENC1, ENC2, ENC3, ENC4, ENET, ENET_1G, ENET_QOS, EWM, FLEXIO1, FLEXIO2, FLEXSPI1, FLEXSPI2, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, IEE_APC, IOMUXC, IOMUXC_GPR, KPP, LCDIF, LCDIFV2, LPADC1, LPADC2, LPI2C1, LPI2C2, LPI2C3, LPI2C4, LPSPI1, LPSPI2, LPSPI3, LPSPI4, LPUART1, LPUART10, LPUART2, LPUART3, LPUART4, LPUART5, LPUART6, LPUART7, LPUART8, LPUART9, MECC1, MECC2, MIPI_CSI2RX, PIT1, PWM1, PWM2, PWM3, PWM4, PXP, RTWDOG3, SAI1, SAI2, SAI3, SPDIF, TMR1, TMR2, TMR3, TMR4, USBPHY1, USBPHY2, USB_OTG1, USB_OTG2, USDHC1, USDHC2, WDOG1, WDOG2, XBARA1, XBARB2, XBARB3, XECC_FLEXSPI1, XECC_FLEXSPI2, XECC_SEMC, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_800M_BUS_LPSR_CLK_ROOT     160000000UL    /* Clock consumers of BUS_LPSR_CLK_ROOT output : CAN3, GPIO10, GPIO11, GPIO12, GPIO7, GPIO8, GPIO9, IOMUXC_LPSR, LPI2C5, LPI2C6, LPSPI5, LPSPI6, LPUART11, LPUART12, MUA, MUB, PDM, PIT2, RDC, RTWDOG4, SAI4, SNVS, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_800M_CAN1_CLK_ROOT         24000000UL     /* Clock consumers of CAN1_CLK_ROOT output : CAN1 */
#define BOARD_BOOTCLOCKRUN_800M_CAN2_CLK_ROOT         24000000UL     /* Clock consumers of CAN2_CLK_ROOT output : CAN2 */
#define BOARD_BOOTCLOCKRUN_800M_CAN3_CLK_ROOT         24000000UL     /* Clock consumers of CAN3_CLK_ROOT output : CAN3 */
#define BOARD_BOOTCLOCKRUN_800M_CCM_CLKO1_CLK_ROOT    24000000UL     /* Clock consumers of CCM_CLKO1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_CCM_CLKO2_CLK_ROOT    24000000UL     /* Clock consumers of CCM_CLKO2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_CLK_1M                1000000UL      /* Clock consumers of CLK_1M output : EWM, RTWDOG3, RTWDOG4 */
#define BOARD_BOOTCLOCKRUN_800M_CSI2_CLK_ROOT         24000000UL     /* Clock consumers of CSI2_CLK_ROOT output : MIPI_CSI2RX */
#define BOARD_BOOTCLOCKRUN_800M_CSI2_ESC_CLK_ROOT     24000000UL     /* Clock consumers of CSI2_ESC_CLK_ROOT output : MIPI_CSI2RX */
#define BOARD_BOOTCLOCKRUN_800M_CSI2_UI_CLK_ROOT      24000000UL     /* Clock consumers of CSI2_UI_CLK_ROOT output : MIPI_CSI2RX */
#define BOARD_BOOTCLOCKRUN_800M_CSI_CLK_ROOT          24000000UL     /* Clock consumers of CSI_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_CSSYS_CLK_ROOT        24000000UL     /* Clock consumers of CSSYS_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_800M_CSTRACE_CLK_ROOT      132000000UL    /* Clock consumers of CSTRACE_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_800M_ELCDIF_CLK_ROOT       24000000UL     /* Clock consumers of ELCDIF_CLK_ROOT output : LCDIF */
#define BOARD_BOOTCLOCKRUN_800M_EMV1_CLK_ROOT         24000000UL     /* Clock consumers of EMV1_CLK_ROOT output : EMVSIM1 */
#define BOARD_BOOTCLOCKRUN_800M_EMV2_CLK_ROOT         24000000UL     /* Clock consumers of EMV2_CLK_ROOT output : EMVSIM2 */
#define BOARD_BOOTCLOCKRUN_800M_ENET1_CLK_ROOT        24000000UL     /* Clock consumers of ENET1_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_ENET2_CLK_ROOT        24000000UL     /* Clock consumers of ENET2_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_ENET_1G_REF_CLK       0UL            /* Clock consumers of ENET_1G_REF_CLK output : ENET_1G */
#define BOARD_BOOTCLOCKRUN_800M_ENET_1G_TX_CLK        24000000UL     /* Clock consumers of ENET_1G_TX_CLK output : ENET_1G */
#define BOARD_BOOTCLOCKRUN_800M_ENET_25M_CLK_ROOT     24000000UL     /* Clock consumers of ENET_25M_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_ENET_QOS_CLK_ROOT     24000000UL     /* Clock consumers of ENET_QOS_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_ENET_QOS_REF_CLK      0UL            /* Clock consumers of ENET_QOS_REF_CLK output : ENET_QOS */
#define BOARD_BOOTCLOCKRUN_800M_ENET_QOS_TX_CLK       0UL            /* Clock consumers of ENET_QOS_TX_CLK output : ENET_QOS */
#define BOARD_BOOTCLOCKRUN_800M_ENET_REF_CLK          0UL            /* Clock consumers of ENET_REF_CLK output : ENET */
#define BOARD_BOOTCLOCKRUN_800M_ENET_TIMER1_CLK_ROOT  24000000UL     /* Clock consumers of ENET_TIMER1_CLK_ROOT output : ENET */
#define BOARD_BOOTCLOCKRUN_800M_ENET_TIMER2_CLK_ROOT  24000000UL     /* Clock consumers of ENET_TIMER2_CLK_ROOT output : ENET_1G */
#define BOARD_BOOTCLOCKRUN_800M_ENET_TIMER3_CLK_ROOT  24000000UL     /* Clock consumers of ENET_TIMER3_CLK_ROOT output : ENET_QOS */
#define BOARD_BOOTCLOCKRUN_800M_ENET_TX_CLK           0UL            /* Clock consumers of ENET_TX_CLK output : ENET */
#define BOARD_BOOTCLOCKRUN_800M_FLEXIO1_CLK_ROOT      24000000UL     /* Clock consumers of FLEXIO1_CLK_ROOT output : FLEXIO1 */
#define BOARD_BOOTCLOCKRUN_800M_FLEXIO2_CLK_ROOT      24000000UL     /* Clock consumers of FLEXIO2_CLK_ROOT output : FLEXIO2 */
#define BOARD_BOOTCLOCKRUN_800M_FLEXSPI1_CLK_ROOT     24000000UL     /* Clock consumers of FLEXSPI1_CLK_ROOT output : FLEXSPI1 */
#define BOARD_BOOTCLOCKRUN_800M_FLEXSPI2_CLK_ROOT     24000000UL     /* Clock consumers of FLEXSPI2_CLK_ROOT output : FLEXSPI2 */
#define BOARD_BOOTCLOCKRUN_800M_GC355_CLK_ROOT        492000012UL    /* Clock consumers of GC355_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_GPT1_CLK_ROOT         24000000UL     /* Clock consumers of GPT1_CLK_ROOT output : GPT1 */
#define BOARD_BOOTCLOCKRUN_800M_GPT1_IPG_CLK_HIGHFREQ 24000000UL     /* Clock consumers of GPT1_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_GPT2_CLK_ROOT         24000000UL     /* Clock consumers of GPT2_CLK_ROOT output : GPT2 */
#define BOARD_BOOTCLOCKRUN_800M_GPT2_IPG_CLK_HIGHFREQ 24000000UL     /* Clock consumers of GPT2_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_GPT3_CLK_ROOT         24000000UL     /* Clock consumers of GPT3_CLK_ROOT output : GPT3 */
#define BOARD_BOOTCLOCKRUN_800M_GPT3_IPG_CLK_HIGHFREQ 24000000UL     /* Clock consumers of GPT3_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_GPT4_CLK_ROOT         24000000UL     /* Clock consumers of GPT4_CLK_ROOT output : GPT4 */
#define BOARD_BOOTCLOCKRUN_800M_GPT4_IPG_CLK_HIGHFREQ 24000000UL     /* Clock consumers of GPT4_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_GPT5_CLK_ROOT         24000000UL     /* Clock consumers of GPT5_CLK_ROOT output : GPT5 */
#define BOARD_BOOTCLOCKRUN_800M_GPT5_IPG_CLK_HIGHFREQ 24000000UL     /* Clock consumers of GPT5_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_GPT6_CLK_ROOT         24000000UL     /* Clock consumers of GPT6_CLK_ROOT output : GPT6 */
#define BOARD_BOOTCLOCKRUN_800M_GPT6_IPG_CLK_HIGHFREQ 24000000UL     /* Clock consumers of GPT6_ipg_clk_highfreq output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_LCDIFV2_CLK_ROOT      24000000UL     /* Clock consumers of LCDIFV2_CLK_ROOT output : LCDIFV2 */
#define BOARD_BOOTCLOCKRUN_800M_LPI2C1_CLK_ROOT       24000000UL     /* Clock consumers of LPI2C1_CLK_ROOT output : LPI2C1 */
#define BOARD_BOOTCLOCKRUN_800M_LPI2C2_CLK_ROOT       24000000UL     /* Clock consumers of LPI2C2_CLK_ROOT output : LPI2C2 */
#define BOARD_BOOTCLOCKRUN_800M_LPI2C3_CLK_ROOT       24000000UL     /* Clock consumers of LPI2C3_CLK_ROOT output : LPI2C3 */
#define BOARD_BOOTCLOCKRUN_800M_LPI2C4_CLK_ROOT       24000000UL     /* Clock consumers of LPI2C4_CLK_ROOT output : LPI2C4 */
#define BOARD_BOOTCLOCKRUN_800M_LPI2C5_CLK_ROOT       24000000UL     /* Clock consumers of LPI2C5_CLK_ROOT output : LPI2C5 */
#define BOARD_BOOTCLOCKRUN_800M_LPI2C6_CLK_ROOT       24000000UL     /* Clock consumers of LPI2C6_CLK_ROOT output : LPI2C6 */
#define BOARD_BOOTCLOCKRUN_800M_LPSPI1_CLK_ROOT       24000000UL     /* Clock consumers of LPSPI1_CLK_ROOT output : LPSPI1 */
#define BOARD_BOOTCLOCKRUN_800M_LPSPI2_CLK_ROOT       24000000UL     /* Clock consumers of LPSPI2_CLK_ROOT output : LPSPI2 */
#define BOARD_BOOTCLOCKRUN_800M_LPSPI3_CLK_ROOT       24000000UL     /* Clock consumers of LPSPI3_CLK_ROOT output : LPSPI3 */
#define BOARD_BOOTCLOCKRUN_800M_LPSPI4_CLK_ROOT       24000000UL     /* Clock consumers of LPSPI4_CLK_ROOT output : LPSPI4 */
#define BOARD_BOOTCLOCKRUN_800M_LPSPI5_CLK_ROOT       24000000UL     /* Clock consumers of LPSPI5_CLK_ROOT output : LPSPI5 */
#define BOARD_BOOTCLOCKRUN_800M_LPSPI6_CLK_ROOT       24000000UL     /* Clock consumers of LPSPI6_CLK_ROOT output : LPSPI6 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART10_CLK_ROOT     24000000UL     /* Clock consumers of LPUART10_CLK_ROOT output : LPUART10 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART11_CLK_ROOT     24000000UL     /* Clock consumers of LPUART11_CLK_ROOT output : LPUART11 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART12_CLK_ROOT     24000000UL     /* Clock consumers of LPUART12_CLK_ROOT output : LPUART12 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART1_CLK_ROOT      24000000UL     /* Clock consumers of LPUART1_CLK_ROOT output : LPUART1 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART2_CLK_ROOT      24000000UL     /* Clock consumers of LPUART2_CLK_ROOT output : LPUART2 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART3_CLK_ROOT      24000000UL     /* Clock consumers of LPUART3_CLK_ROOT output : LPUART3 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART4_CLK_ROOT      24000000UL     /* Clock consumers of LPUART4_CLK_ROOT output : LPUART4 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART5_CLK_ROOT      24000000UL     /* Clock consumers of LPUART5_CLK_ROOT output : LPUART5 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART6_CLK_ROOT      24000000UL     /* Clock consumers of LPUART6_CLK_ROOT output : LPUART6 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART7_CLK_ROOT      24000000UL     /* Clock consumers of LPUART7_CLK_ROOT output : LPUART7 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART8_CLK_ROOT      24000000UL     /* Clock consumers of LPUART8_CLK_ROOT output : LPUART8 */
#define BOARD_BOOTCLOCKRUN_800M_LPUART9_CLK_ROOT      24000000UL     /* Clock consumers of LPUART9_CLK_ROOT output : LPUART9 */
#define BOARD_BOOTCLOCKRUN_800M_M4_CLK_ROOT           392727272UL    /* Clock consumers of M4_CLK_ROOT output : ARM, DMA1, DMAMUX1, SSARC_HP, SSARC_LP, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_800M_M4_SYSTICK_CLK_ROOT   24000000UL     /* Clock consumers of M4_SYSTICK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_M7_CLK_ROOT           798000000UL    /* Clock consumers of M7_CLK_ROOT output : ARM */
#define BOARD_BOOTCLOCKRUN_800M_M7_SYSTICK_CLK_ROOT   100000UL       /* Clock consumers of M7_SYSTICK_CLK_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_MIC_CLK_ROOT          24000000UL     /* Clock consumers of MIC_CLK_ROOT output : ASRC, PDM, SPDIF */
#define BOARD_BOOTCLOCKRUN_800M_MIPI_DSI_TX_CLK_ESC_ROOT 24000000UL  /* Clock consumers of MIPI_DSI_TX_CLK_ESC_ROOT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_MIPI_ESC_CLK_ROOT     24000000UL     /* Clock consumers of MIPI_ESC_CLK_ROOT output : DSI_HOST */
#define BOARD_BOOTCLOCKRUN_800M_MIPI_REF_CLK_ROOT     24000000UL     /* Clock consumers of MIPI_REF_CLK_ROOT output : DSI_HOST */
#define BOARD_BOOTCLOCKRUN_800M_MQS_CLK_ROOT          24000000UL     /* Clock consumers of MQS_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_800M_MQS_MCLK              24000000UL     /* Clock consumers of MQS_MCLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_OSC_24M               24000000UL     /* Clock consumers of OSC_24M output : SPDIF, TMPSNS, USBPHY1, USBPHY2 */
#define BOARD_BOOTCLOCKRUN_800M_OSC_32K               32768UL        /* Clock consumers of OSC_32K output : GPIO13, RTWDOG3, RTWDOG4 */
#define BOARD_BOOTCLOCKRUN_800M_OSC_RC_16M            16000000UL     /* Clock consumers of OSC_RC_16M output : CCM, DCDC, EWM, GPT1, GPT2, GPT3, GPT4, GPT5, GPT6, SSARC_LP */
#define BOARD_BOOTCLOCKRUN_800M_OSC_RC_400M           400000000UL    /* Clock consumers of OSC_RC_400M output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_OSC_RC_48M            48000000UL     /* Clock consumers of OSC_RC_48M output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_OSC_RC_48M_DIV2       24000000UL     /* Clock consumers of OSC_RC_48M_DIV2 output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_PLL_AUDIO_CLK         0UL            /* Clock consumers of PLL_AUDIO_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_PLL_AUDIO_SS_MODULATION 0UL          /* Clock consumers of PLL_AUDIO_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_PLL_AUDIO_SS_RANGE    0UL            /* Clock consumers of PLL_AUDIO_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_PLL_VIDEO_CLK         984000025UL    /* Clock consumers of PLL_VIDEO_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_PLL_VIDEO_SS_MODULATION 0UL          /* Clock consumers of PLL_VIDEO_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_PLL_VIDEO_SS_RANGE    0UL            /* Clock consumers of PLL_VIDEO_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SAI1_CLK_ROOT         24000000UL     /* Clock consumers of SAI1_CLK_ROOT output : SPDIF */
#define BOARD_BOOTCLOCKRUN_800M_SAI1_MCLK1            24000000UL     /* Clock consumers of SAI1_MCLK1 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_800M_SAI1_MCLK2            0UL            /* Clock consumers of SAI1_MCLK2 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_800M_SAI1_MCLK3            24000000UL     /* Clock consumers of SAI1_MCLK3 output : SAI1 */
#define BOARD_BOOTCLOCKRUN_800M_SAI2_CLK_ROOT         24000000UL     /* Clock consumers of SAI2_CLK_ROOT output : ASRC */
#define BOARD_BOOTCLOCKRUN_800M_SAI2_MCLK1            24000000UL     /* Clock consumers of SAI2_MCLK1 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_800M_SAI2_MCLK2            0UL            /* Clock consumers of SAI2_MCLK2 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_800M_SAI2_MCLK3            24000000UL     /* Clock consumers of SAI2_MCLK3 output : SAI2 */
#define BOARD_BOOTCLOCKRUN_800M_SAI3_CLK_ROOT         24000000UL     /* Clock consumers of SAI3_CLK_ROOT output : ASRC, SPDIF */
#define BOARD_BOOTCLOCKRUN_800M_SAI3_MCLK1            24000000UL     /* Clock consumers of SAI3_MCLK1 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_800M_SAI3_MCLK2            0UL            /* Clock consumers of SAI3_MCLK2 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_800M_SAI3_MCLK3            24000000UL     /* Clock consumers of SAI3_MCLK3 output : SAI3 */
#define BOARD_BOOTCLOCKRUN_800M_SAI4_CLK_ROOT         24000000UL     /* Clock consumers of SAI4_CLK_ROOT output : ASRC, SPDIF */
#define BOARD_BOOTCLOCKRUN_800M_SAI4_MCLK1            24000000UL     /* Clock consumers of SAI4_MCLK1 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_800M_SAI4_MCLK2            0UL            /* Clock consumers of SAI4_MCLK2 output : SAI4 */
#define BOARD_BOOTCLOCKRUN_800M_SEMC_CLK_ROOT         198000000UL    /* Clock consumers of SEMC_CLK_ROOT output : SEMC, XECC_FLEXSPI1, XECC_FLEXSPI2, XECC_SEMC, XRDC2_D0, XRDC2_D1 */
#define BOARD_BOOTCLOCKRUN_800M_SPDIF_CLK_ROOT        24000000UL     /* Clock consumers of SPDIF_CLK_ROOT output : SPDIF */
#define BOARD_BOOTCLOCKRUN_800M_SPDIF_EXTCLK_OUT      0UL            /* Clock consumers of SPDIF_EXTCLK_OUT output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL1_CLK          0UL            /* Clock consumers of SYS_PLL1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL1_DIV2_CLK     0UL            /* Clock consumers of SYS_PLL1_DIV2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL1_DIV5_CLK     0UL            /* Clock consumers of SYS_PLL1_DIV5_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL1_SS_MODULATION0UL            /* Clock consumers of SYS_PLL1_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL1_SS_RANGE     0UL            /* Clock consumers of SYS_PLL1_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_CLK          528000000UL    /* Clock consumers of SYS_PLL2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_PFD0_CLK     352000000UL    /* Clock consumers of SYS_PLL2_PFD0_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_PFD1_CLK     594000000UL    /* Clock consumers of SYS_PLL2_PFD1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_PFD2_CLK     396000000UL    /* Clock consumers of SYS_PLL2_PFD2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_PFD3_CLK     297000000UL    /* Clock consumers of SYS_PLL2_PFD3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_SS_MODULATION0UL            /* Clock consumers of SYS_PLL2_SS_MODULATION output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL2_SS_RANGE     0UL            /* Clock consumers of SYS_PLL2_SS_RANGE output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL3_CLK          480000000UL    /* Clock consumers of SYS_PLL3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL3_DIV2_CLK     240000000UL    /* Clock consumers of SYS_PLL3_DIV2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL3_PFD0_CLK     664615384UL    /* Clock consumers of SYS_PLL3_PFD0_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL3_PFD1_CLK     508235294UL    /* Clock consumers of SYS_PLL3_PFD1_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL3_PFD2_CLK     270000000UL    /* Clock consumers of SYS_PLL3_PFD2_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_SYS_PLL3_PFD3_CLK     392727272UL    /* Clock consumers of SYS_PLL3_PFD3_CLK output : N/A */
#define BOARD_BOOTCLOCKRUN_800M_USDHC1_CLK_ROOT       24000000UL     /* Clock consumers of USDHC1_CLK_ROOT output : USDHC1 */
#define BOARD_BOOTCLOCKRUN_800M_USDHC2_CLK_ROOT       24000000UL     /* Clock consumers of USDHC2_CLK_ROOT output : USDHC2 */


/*******************************************************************************
 * API for BOARD_BootClockRUN_800M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockRUN_800M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */

