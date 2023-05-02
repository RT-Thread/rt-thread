/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*
 * How to setup clock using clock driver functions:
 *
 * 1. Call CLOCK_InitXXXPLL() to configure corresponding PLL clock.
 *
 * 2. Call CLOCK_InitXXXpfd() to configure corresponding PLL pfd clock.
 *
 * 3. Call CLOCK_SetMux() to configure corresponding clock source for target clock out.
 *
 * 4. Call CLOCK_SetDiv() to configure corresponding clock divider for target clock out.
 *
 * 5. Call CLOCK_SetXtalFreq() to set XTAL frequency based on board settings.
 *
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v4.1
processor: MIMXRT1021xxxxx
package_id: MIMXRT1021DAG5A
mcu_data: ksdk2_0
processor_version: 0.0.0
board: MIMXRT1020-EVK
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: AHB_CLK_ROOT.outFreq, value: 500 MHz}
- {id: CAN_CLK_ROOT.outFreq, value: 40 MHz}
- {id: CKIL_SYNC_CLK_ROOT.outFreq, value: 32.768 kHz}
- {id: CLK_1M.outFreq, value: 1 MHz}
- {id: CLK_24M.outFreq, value: 24 MHz}
- {id: ENET_500M_REF_CLK.outFreq, value: 500 MHz}
- {id: FLEXIO1_CLK_ROOT.outFreq, value: 30 MHz}
- {id: FLEXSPI_CLK_ROOT.outFreq, value: 31.25 MHz}
- {id: IPG_CLK_ROOT.outFreq, value: 125 MHz}
- {id: LPI2C_CLK_ROOT.outFreq, value: 60 MHz}
- {id: LPSPI_CLK_ROOT.outFreq, value: 105.6 MHz}
- {id: PERCLK_CLK_ROOT.outFreq, value: 62.5 MHz}
- {id: SAI1_CLK_ROOT.outFreq, value: 1080/17 MHz}
- {id: SAI2_CLK_ROOT.outFreq, value: 1080/17 MHz}
- {id: SAI3_CLK_ROOT.outFreq, value: 1080/17 MHz}
- {id: SEMC_CLK_ROOT.outFreq, value: 62.5 MHz}
- {id: SPDIF0_CLK_ROOT.outFreq, value: 30 MHz}
- {id: TRACE_CLK_ROOT.outFreq, value: 352/3 MHz}
- {id: UART_CLK_ROOT.outFreq, value: 80 MHz}
- {id: USDHC1_CLK_ROOT.outFreq, value: 176 MHz}
- {id: USDHC2_CLK_ROOT.outFreq, value: 176 MHz}
settings:
- {id: CCM.AHB_PODF.scale, value: '1', locked: true}
- {id: CCM.ARM_PODF.scale, value: '1', locked: true}
- {id: CCM.FLEXSPI_PODF.scale, value: '2', locked: true}
- {id: CCM.IPG_PODF.scale, value: '4'}
- {id: CCM.LPSPI_PODF.scale, value: '5', locked: true}
- {id: CCM.PERCLK_PODF.scale, value: '2', locked: true}
- {id: CCM.PRE_PERIPH_CLK_SEL.sel, value: CCM.ARM_PODF}
- {id: CCM.SEMC_PODF.scale, value: '8'}
- {id: CCM.TRACE_PODF.scale, value: '3', locked: true}
- {id: CCM.USDHC1_PODF.scale, value: '3', locked: true}
- {id: CCM.USDHC2_PODF.scale, value: '3', locked: true}
- {id: CCM_ANALOG.PLL2.denom, value: '1', locked: true}
- {id: CCM_ANALOG.PLL2.div, value: '22'}
- {id: CCM_ANALOG.PLL2.num, value: '0', locked: true}
- {id: CCM_ANALOG.PLL2_BYPASS.sel, value: CCM_ANALOG.PLL2_OUT_CLK}
- {id: CCM_ANALOG.PLL2_PFD0_BYPASS.sel, value: CCM_ANALOG.PLL2_PFD0}
- {id: CCM_ANALOG.PLL2_PFD1_BYPASS.sel, value: CCM_ANALOG.PLL2_PFD1}
- {id: CCM_ANALOG.PLL2_PFD2_BYPASS.sel, value: CCM_ANALOG.PLL2_PFD2}
- {id: CCM_ANALOG.PLL2_PFD2_DIV.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL2_PFD2_MUL.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL2_PFD3_BYPASS.sel, value: CCM_ANALOG.PLL2_PFD3}
- {id: CCM_ANALOG.PLL2_PFD3_DIV.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL2_PFD3_MUL.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL3_BYPASS.sel, value: CCM_ANALOG.PLL3}
- {id: CCM_ANALOG.PLL3_PFD0_BYPASS.sel, value: CCM_ANALOG.PLL3_PFD0}
- {id: CCM_ANALOG.PLL3_PFD0_DIV.scale, value: '22', locked: true}
- {id: CCM_ANALOG.PLL3_PFD0_MUL.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL3_PFD1_BYPASS.sel, value: CCM_ANALOG.PLL3_PFD1}
- {id: CCM_ANALOG.PLL3_PFD2_BYPASS.sel, value: CCM_ANALOG.PLL3_PFD2}
- {id: CCM_ANALOG.PLL3_PFD3_BYPASS.sel, value: CCM_ANALOG.PLL3_PFD3}
- {id: CCM_ANALOG.PLL3_PFD3_DIV.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL3_PFD3_MUL.scale, value: '18', locked: true}
- {id: CCM_ANALOG.PLL4.denom, value: '50'}
- {id: CCM_ANALOG.PLL4.div, value: '47'}
- {id: CCM_ANALOG.PLL6_BYPASS.sel, value: CCM_ANALOG.PLL6}
- {id: CCM_ANALOG_PLL_ENET_ENABLE_CFG, value: Disabled}
- {id: CCM_ANALOG_PLL_ENET_ENET_25M_REF_EN_CFG, value: Disabled}
- {id: CCM_ANALOG_PLL_USB1_POWER_CFG, value: 'Yes'}
sources:
- {id: XTALOSC24M.OSC.outFreq, value: 24 MHz, enabled: true}
- {id: XTALOSC24M.RTC_OSC.outFreq, value: 32.768 kHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const clock_enet_pll_config_t enetPllConfig_BOARD_BootClockRUN = {
    .enableClkOutput500M = true,
};
const clock_sys_pll_config_t sysPllConfig_BOARD_BootClockRUN = {
    .loopDivider = 1, /* PLL loop divider, Fout = Fin * 22 */
};
const clock_usb_pll_config_t usb1PllConfig_BOARD_BootClockRUN = {
    .loopDivider = 0, /* PLL loop divider, Fout = Fin * 20 */
};
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /* Init RTC OSC clock frequency. */
    CLOCK_SetRtcXtalFreq(BOARD_XTAL32K_CLK_HZ);
    /* Set XTAL 24MHz clock frequency. */
    CLOCK_SetXtalFreq(BOARD_XTAL0_CLK_HZ);
    /* Setting PeriphClk2Mux and PeriphMux to provide stable clock before PLLs are initialed */
    CLOCK_SetMux(kCLOCK_PeriphClk2Mux, 0x1); /* Set PERIPH_CLK2 MUX to OSC */
    CLOCK_SetMux(kCLOCK_PeriphMux, 0x1);     /* Set PERIPH_CLK MUX to PERIPH_CLK2 */

    DCDC->REG3 = (DCDC->REG3 & (~DCDC_REG3_TRG_MASK)) | DCDC_REG3_TRG(0x12);
    /* Set AHB_PODF. */
    CLOCK_SetDiv(kCLOCK_AhbDiv, 0x0);
    /* Set ARM_PODF. */
    CLOCK_SetDiv(kCLOCK_ArmDiv, 0x0);
    /* Set IPG_PODF. */
    CLOCK_SetDiv(kCLOCK_IpgDiv, 0x3);
    /* Set PERCLK_PODF. */
    CLOCK_SetDiv(kCLOCK_PerclkDiv, 0x1);
    /* Set per clock source. */
    CLOCK_SetMux(kCLOCK_PerclkMux, 0x0);
    /* Set USDHC1_PODF. */
    CLOCK_SetDiv(kCLOCK_Usdhc1Div, 0x2);
    /* Set Usdhc1 clock source. */
    CLOCK_SetMux(kCLOCK_Usdhc1Mux, 0x0);
    /* Set USDHC2_PODF. */
    CLOCK_SetDiv(kCLOCK_Usdhc2Div, 0x2);
    /* Set Usdhc2 clock source. */
    CLOCK_SetMux(kCLOCK_Usdhc2Mux, 0x0);
#ifndef SKIP_SYSCLK_INIT
    /* Set Semc alt clock source. */
    CLOCK_SetMux(kCLOCK_SemcAltMux, 0x0);
    /* Set SEMC_PODF. */
    CLOCK_SetDiv(kCLOCK_SemcDiv, 0x7);
    /* Set Semc clock source. */
    CLOCK_SetMux(kCLOCK_SemcMux, 0x0);
#endif
#ifndef XIP_EXTERNAL_FLASH
    /* Set FLEXSPI_PODF. */
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 0x1);
    /* Set Flexspi clock source. */
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x0);
#endif
    /* Set LPSPI_PODF. */
    CLOCK_SetDiv(kCLOCK_LpspiDiv, 0x4);
    /* Set Lpspi clock source. */
    CLOCK_SetMux(kCLOCK_LpspiMux, 0x2);
    /* Set TRACE_PODF. */
    CLOCK_SetDiv(kCLOCK_TraceDiv, 0x2);
    /* Set Trace clock source. */
    CLOCK_SetMux(kCLOCK_TraceMux, 0x2);
    /* Set SAI1_CLK_PRED. */
    CLOCK_SetDiv(kCLOCK_Sai1PreDiv, 0x3);
    /* Set SAI1_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Sai1Div, 0x1);
    /* Set Sai1 clock source. */
    CLOCK_SetMux(kCLOCK_Sai1Mux, 0x0);
    /* Set SAI2_CLK_PRED. */
    CLOCK_SetDiv(kCLOCK_Sai2PreDiv, 0x3);
    /* Set SAI2_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Sai2Div, 0x1);
    /* Set Sai2 clock source. */
    CLOCK_SetMux(kCLOCK_Sai2Mux, 0x0);
    /* Set SAI3_CLK_PRED. */
    CLOCK_SetDiv(kCLOCK_Sai3PreDiv, 0x3);
    /* Set SAI3_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Sai3Div, 0x1);
    /* Set Sai3 clock source. */
    CLOCK_SetMux(kCLOCK_Sai3Mux, 0x0);
    /* Set LPI2C_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, 0x0);
    /* Set Lpi2c clock source. */
    CLOCK_SetMux(kCLOCK_Lpi2cMux, 0x0);
    /* Set CAN_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_CanDiv, 0x1);
    /* Set Can clock source. */
    CLOCK_SetMux(kCLOCK_CanMux, 0x2);
    /* Set SPDIF0_CLK_PRED. */
    CLOCK_SetDiv(kCLOCK_Spdif0PreDiv, 0x1);
    /* Set SPDIF0_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Spdif0Div, 0x7);
    /* Set Spdif clock source. */
    CLOCK_SetMux(kCLOCK_SpdifMux, 0x3);
    /* Set FLEXIO1_CLK_PRED. */
    CLOCK_SetDiv(kCLOCK_Flexio1PreDiv, 0x1);
    /* Set FLEXIO1_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_Flexio1Div, 0x7);
    /* Set Flexio1 clock source. */
    CLOCK_SetMux(kCLOCK_Flexio1Mux, 0x3);
    /* Set Pll3 sw clock source. */
    CLOCK_SetMux(kCLOCK_Pll3SwMux, 0x0);
    /* Set UART_CLK_PODF. */
    CLOCK_SetDiv(kCLOCK_UartDiv, 0x0);
    /* Set Uart clock source. */
    CLOCK_SetMux(kCLOCK_UartMux, 0x0);

#ifndef SKIP_SYSCLK_INIT
    /* Init System PLL (PLL2). */
    CLOCK_InitSysPll(&sysPllConfig_BOARD_BootClockRUN);
    CLOCK_InitSysPfd(kCLOCK_Pfd2, 18);
    CLOCK_InitSysPfd(kCLOCK_Pfd3, 18);
#endif
#ifndef XIP_EXTERNAL_FLASH
    /* Init Usb1 PLL (PLL3). */
    CLOCK_InitUsb1Pll(&usb1PllConfig_BOARD_BootClockRUN);
    CLOCK_InitUsb1Pfd(kCLOCK_Pfd3, 18);
#endif
    CLOCK_InitEnetPll(&enetPllConfig_BOARD_BootClockRUN);
    /* Set preperiph clock source. */
    CLOCK_SetMux(kCLOCK_PrePeriphMux, 0x3);
    /* Set periph clock source. */
    CLOCK_SetMux(kCLOCK_PeriphMux, 0x0);
    /* Set PERIPH_CLK2_PODF. */
    CLOCK_SetDiv(kCLOCK_PeriphClk2Div, 0x0);
    /* Set periph clock2 clock source. */
    CLOCK_SetMux(kCLOCK_PeriphClk2Mux, 0x0);

    SystemCoreClockUpdate();
}
