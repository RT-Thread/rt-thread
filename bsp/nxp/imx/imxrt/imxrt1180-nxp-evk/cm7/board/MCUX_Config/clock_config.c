/*
 * Copyright 2022-2025 NXP
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
 * 3. Call CLOCK_SetRootClock() to configure corresponding module clock source and divider.
 *
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v13.0
processor: MIMXRT1189xxxxx
package_id: MIMXRT1189CVM8C
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "clock_config.h"
#include "fsl_misc.h"
#include "fsl_dcdc.h"
#include "fsl_pmu.h"
#include "fsl_clock.h"
#include "fsl_ele_base_api.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_FlexspiClockSafeConfig
 * Description   : FLEXSPI clock source safe configuration weak function.
 *                 Called before clock source configuration.
 * Note          : Users need override this function to change FLEXSPI clock source to stable source when executing
 *                 code on FLEXSPI memory(XIP). If XIP, the function should runs in RAM and move the FLEXSPI clock source
 *                 to a stable clock to avoid instruction/data fetch issue during clock updating.
 *END**************************************************************************/
__attribute__((weak)) void BOARD_FlexspiClockSafeConfig(void)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_SetFlexspiClock
 * Description   : This function should be overridden if executing code on FLEXSPI memory(XIP).
 *                 To Change FLEXSPI clock, should move to run from RAM and then configure FLEXSPI clock source.
 *                 After the clock is changed and stable, move back to run on FLEXSPI.
 * Param base    : FLEXSPI peripheral base address.
 * Param src     : FLEXSPI clock source.
 * Param divider : FLEXSPI clock divider.
 *END**************************************************************************/
__attribute__((weak)) void BOARD_SetFlexspiClock(FLEXSPI_Type *base, uint8_t src, uint32_t divider)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EdgeLock_SetClock
 * Description   : Set EdgeLock clock via safe method
 * Note          : It requires specific sequence to change edgelock clock source,
 *                 otherwise the soc behavior is unpredictable.
 *END**************************************************************************/
__attribute__((weak)) void EdgeLock_SetClock(uint8_t mux, uint8_t div)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DCDC_SetVoltage
 * Description   : Set DCDC voltage via safe method
 * Note          : It requires specific sequence to change DCDC voltage when GDET
 *                 is enabled, otherwise the soc behavior is unpredictable.
 *END**************************************************************************/
__attribute__((weak)) void DCDC_SetVoltage(uint8_t core, uint8_t targetVoltage)
{
}


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
- {id: ACMP_CLK_ROOT.outFreq, value: 240 MHz}
- {id: ADC1_CLK_ROOT.outFreq, value: 80 MHz}
- {id: ADC2_CLK_ROOT.outFreq, value: 80 MHz}
- {id: ARM_PLL_CLK.outFreq, value: 792 MHz}
- {id: ASRC_CLK_ROOT.outFreq, value: 240 MHz}
- {id: BUS_AON_CLK_ROOT.outFreq, value: 132 MHz}
- {id: BUS_WAKEUP_CLK_ROOT.outFreq, value: 132 MHz}
- {id: CAN1_CLK_ROOT.outFreq, value: 80 MHz}
- {id: CAN2_CLK_ROOT.outFreq, value: 80 MHz}
- {id: CAN3_CLK_ROOT.outFreq, value: 80 MHz}
- {id: CCM_CKO1_CLK_ROOT.outFreq, value: 80 MHz}
- {id: CCM_CKO2_CLK_ROOT.outFreq, value: 50 MHz}
- {id: CLK_1M.outFreq, value: 1 MHz}
- {id: ECAT_CLK_ROOT.outFreq, value: 100 MHz}
- {id: ECAT_PORT0_REF_CLK.outFreq, value: 50 MHz}
- {id: ECAT_PORT1_REF_CLK.outFreq, value: 50 MHz}
- {id: EDGELOCK_CLK_ROOT.outFreq, value: 200 MHz}
- {id: ENET_REFCLK_ROOT.outFreq, value: 125 MHz}
- {id: FLEXIO1_CLK_ROOT.outFreq, value: 120 MHz}
- {id: FLEXIO2_CLK_ROOT.outFreq, value: 48 MHz}
- {id: FLEXSPI1_CLK_ROOT.outFreq, value: 1440/11 MHz}
- {id: FLEXSPI2_CLK_ROOT.outFreq, value: 2160/11 MHz}
- {id: FLEXSPI_SLV_CLK_ROOT.outFreq, value: 132 MHz}
- {id: GPT1_CLK_ROOT.outFreq, value: 240 MHz}
- {id: GPT2_CLK_ROOT.outFreq, value: 240 MHz}
- {id: I3C1_CLK_ROOT.outFreq, value: 24 MHz}
- {id: I3C2_CLK_ROOT.outFreq, value: 24 MHz}
- {id: LPI2C0102_CLK_ROOT.outFreq, value: 60 MHz}
- {id: LPI2C0304_CLK_ROOT.outFreq, value: 60 MHz}
- {id: LPI2C0506_CLK_ROOT.outFreq, value: 60 MHz}
- {id: LPIT3_CLK_ROOT.outFreq, value: 80 MHz}
- {id: LPSPI0102_CLK_ROOT.outFreq, value: 1440/11 MHz}
- {id: LPSPI0304_CLK_ROOT.outFreq, value: 1440/11 MHz}
- {id: LPSPI0506_CLK_ROOT.outFreq, value: 1440/11 MHz}
- {id: LPTMR1_CLK_ROOT.outFreq, value: 80 MHz}
- {id: LPTMR2_CLK_ROOT.outFreq, value: 80 MHz}
- {id: LPTMR3_CLK_ROOT.outFreq, value: 80 MHz}
- {id: LPUART0102_CLK_ROOT.outFreq, value: 24 MHz}
- {id: LPUART0304_CLK_ROOT.outFreq, value: 24 MHz}
- {id: LPUART0506_CLK_ROOT.outFreq, value: 24 MHz}
- {id: LPUART0708_CLK_ROOT.outFreq, value: 24 MHz}
- {id: LPUART0910_CLK_ROOT.outFreq, value: 24 MHz}
- {id: LPUART1112_CLK_ROOT.outFreq, value: 24 MHz}
- {id: M33_CLK_ROOT.outFreq, value: 240 MHz}
- {id: M33_SYSTICK_CLK_ROOT.outFreq, value: 100 kHz}
- {id: M7_CLK_ROOT.outFreq, value: 792 MHz}
- {id: M7_SYSTICK_CLK_ROOT.outFreq, value: 100 kHz}
- {id: MAC0_CLK_ROOT.outFreq, value: 50 MHz}
- {id: MAC1_CLK_ROOT.outFreq, value: 125 MHz}
- {id: MAC2_CLK_ROOT.outFreq, value: 125 MHz}
- {id: MAC3_CLK_ROOT.outFreq, value: 125 MHz}
- {id: MAC4_CLK_ROOT.outFreq, value: 50 MHz}
- {id: MIC_CLK_ROOT.outFreq, value: 80 MHz}
- {id: NETC_CLK_ROOT.outFreq, value: 240 MHz}
- {id: NETC_PORT0_REF_CLK.outFreq, value: 50 MHz}
- {id: NETC_PORT1_REF_CLK.outFreq, value: 50 MHz}
- {id: NETC_PORT2_REF_CLK.outFreq, value: 50 MHz}
- {id: NETC_PORT3_REF_CLK.outFreq, value: 50 MHz}
- {id: NETC_PORT4_REF_CLK.outFreq, value: 50 MHz}
- {id: OSC_24M.outFreq, value: 24 MHz}
- {id: OSC_32K.outFreq, value: 32.768 kHz}
- {id: OSC_RC_24M.outFreq, value: 24 MHz}
- {id: OSC_RC_400M.outFreq, value: 400 MHz}
- {id: SEMC_CLK_ROOT.outFreq, value: 200 MHz}
- {id: SWO_TRACE_CLK_ROOT.outFreq, value: 80 MHz}
- {id: SYS_PLL1_CLK.outFreq, value: 1 GHz}
- {id: SYS_PLL1_DIV2_CLK.outFreq, value: 500 MHz}
- {id: SYS_PLL1_DIV5_CLK.outFreq, value: 200 MHz}
- {id: SYS_PLL2_CLK.outFreq, value: 528 MHz}
- {id: SYS_PLL2_PFD0_CLK.outFreq, value: 352 MHz}
- {id: SYS_PLL2_PFD1_CLK.outFreq, value: 594 MHz}
- {id: SYS_PLL2_PFD2_CLK.outFreq, value: 396 MHz}
- {id: SYS_PLL2_PFD3_CLK.outFreq, value: 297 MHz}
- {id: SYS_PLL3_CLK.outFreq, value: 480 MHz}
- {id: SYS_PLL3_DIV2_CLK.outFreq, value: 240 MHz}
- {id: SYS_PLL3_PFD0_CLK.outFreq, value: 4320/11 MHz}
- {id: SYS_PLL3_PFD1_CLK.outFreq, value: 2880/11 MHz}
- {id: SYS_PLL3_PFD2_CLK.outFreq, value: 4320/11 MHz}
- {id: SYS_PLL3_PFD3_CLK.outFreq, value: 480 MHz}
- {id: TMR_1588_CLK_ROOT.outFreq, value: 240 MHz}
- {id: TMR_1588_REF_CLK.outFreq, value: 240 MHz}
- {id: TPM2_CLK_ROOT.outFreq, value: 80 MHz}
- {id: TPM4_CLK_ROOT.outFreq, value: 80 MHz}
- {id: TPM5_CLK_ROOT.outFreq, value: 80 MHz}
- {id: TPM6_CLK_ROOT.outFreq, value: 80 MHz}
- {id: USDHC1_CLK_ROOT.outFreq, value: 198 MHz}
- {id: USDHC2_CLK_ROOT.outFreq, value: 396 MHz}
- {id: WAKEUP_AXI_CLK_ROOT.outFreq, value: 240 MHz}
settings:
- {id: AONDomainVoltage, value: OD}
- {id: CoreClockRootsInitializationConfig, value: selectedCore}
- {id: SOCDomainVoltage, value: OD}
- {id: ANADIG_OSC_OSC_24M_CTRL_LP_EN_CFG, value: Low}
- {id: ANADIG_OSC_OSC_24M_CTRL_OSC_EN_CFG, value: Enabled}
- {id: ANADIG_PLL.ARM_PLL_POST_DIV.scale, value: '2', locked: true}
- {id: ANADIG_PLL.ARM_PLL_PREDIV.scale, value: '1', locked: true}
- {id: ANADIG_PLL.ARM_PLL_VDIV.scale, value: '132', locked: true}
- {id: ANADIG_PLL.PLL_AUDIO_BYPASS.sel, value: ANADIG_OSC.OSC_24M}
- {id: ANADIG_PLL.SYS_PLL2.denom, value: '268435455', locked: true}
- {id: ANADIG_PLL.SYS_PLL2.div, value: '22'}
- {id: ANADIG_PLL.SYS_PLL2.num, value: '0'}
- {id: ANADIG_PLL.SYS_PLL2_SS_DIV.scale, value: '268435455'}
- {id: ANADIG_PLL.SYS_PLL3_PFD0_DIV.scale, value: '22'}
- {id: ANADIG_PLL.SYS_PLL3_PFD1_DIV.scale, value: '33', locked: true}
- {id: ANADIG_PLL.SYS_PLL3_PFD1_MUL.scale, value: '18', locked: true}
- {id: ANADIG_PLL.SYS_PLL3_PFD2_DIV.scale, value: '22', locked: true}
- {id: ANADIG_PLL.SYS_PLL3_PFD2_MUL.scale, value: '18', locked: true}
- {id: ANADIG_PLL.SYS_PLL3_PFD3_DIV.scale, value: '18'}
- {id: ANADIG_PLL_ARM_PLL_CTRL_POWERUP_CFG, value: Enabled}
- {id: ANADIG_PLL_PLL_AUDIO_CTRL_GATE_CFG, value: Disabled}
- {id: ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV2_CFG, value: Enabled}
- {id: ANADIG_PLL_SYS_PLL1_CTRL_SYS_PLL1_DIV5_CFG, value: Enabled}
- {id: ANADIG_PLL_SYS_PLL2_CTRL_POWERUP_CFG, value: Enabled}
- {id: ANADIG_PLL_SYS_PLL3_CTRL_POWERUP_CFG, value: Enabled}
- {id: ANADIG_PLL_SYS_PLL3_CTRL_SYS_PLL3_DIV2_CFG, value: Enabled}
- {id: CCM.CLOCK_ROOT0.DIV.scale, value: '1', locked: true}
- {id: CCM.CLOCK_ROOT0.MUX.sel, value: ANADIG_PLL.ARM_PLL_CLK}
- {id: CCM.CLOCK_ROOT1.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT1.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT10.DIV.scale, value: '5', locked: true}
- {id: CCM.CLOCK_ROOT10.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT11.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT11.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT12.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT12.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT13.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT13.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT14.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT14.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT15.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT15.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT16.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT16.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT17.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT17.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT18.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT18.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT19.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT2.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT2.MUX.sel, value: ANADIG_OSC.OSC_RC_400M}
- {id: CCM.CLOCK_ROOT20.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT21.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT21.MUX.sel, value: ANADIG_PLL.SYS_PLL3_PFD0_CLK}
- {id: CCM.CLOCK_ROOT22.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT22.MUX.sel, value: ANADIG_PLL.SYS_PLL3_PFD2_CLK}
- {id: CCM.CLOCK_ROOT23.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT23.MUX.sel, value: ANADIG_PLL.SYS_PLL2_CLK}
- {id: CCM.CLOCK_ROOT24.DIV.scale, value: '6', locked: true}
- {id: CCM.CLOCK_ROOT24.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT25.DIV.scale, value: '6', locked: true}
- {id: CCM.CLOCK_ROOT25.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT26.DIV.scale, value: '6', locked: true}
- {id: CCM.CLOCK_ROOT26.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT27.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT27.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT28.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT28.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT29.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT29.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT3.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT3.MUX.sel, value: ANADIG_PLL.SYS_PLL2_CLK}
- {id: CCM.CLOCK_ROOT30.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT30.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT31.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT31.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT32.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT32.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT33.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT33.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT34.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT34.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT35.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT35.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT36.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT36.MUX.sel, value: ANADIG_PLL.SYS_PLL3_PFD1_CLK}
- {id: CCM.CLOCK_ROOT37.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT37.MUX.sel, value: ANADIG_PLL.SYS_PLL3_PFD1_CLK}
- {id: CCM.CLOCK_ROOT38.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT38.MUX.sel, value: ANADIG_PLL.SYS_PLL3_PFD1_CLK}
- {id: CCM.CLOCK_ROOT39.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT39.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT4.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT4.MUX.sel, value: ANADIG_PLL.SYS_PLL2_CLK}
- {id: CCM.CLOCK_ROOT40.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT40.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT41.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT41.MUX.sel, value: ANADIG_PLL.SYS_PLL2_PFD2_CLK}
- {id: CCM.CLOCK_ROOT42.MUX.sel, value: ANADIG_PLL.SYS_PLL2_PFD2_CLK}
- {id: CCM.CLOCK_ROOT43.DIV.scale, value: '5', locked: true}
- {id: CCM.CLOCK_ROOT43.MUX.sel, value: ANADIG_PLL.SYS_PLL1_CLK}
- {id: CCM.CLOCK_ROOT44.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT44.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT45.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT45.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT46.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT46.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT47.DIV.scale, value: '5', locked: true}
- {id: CCM.CLOCK_ROOT47.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT48.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT48.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT49.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT49.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT5.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT5.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT50.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT50.MUX.sel, value: ANADIG_PLL.SYS_PLL3_PFD3_CLK}
- {id: CCM.CLOCK_ROOT51.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT51.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT52.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT52.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT53.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT53.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT54.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT54.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT55.DIV.scale, value: '10', locked: true}
- {id: CCM.CLOCK_ROOT55.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV2_CLK}
- {id: CCM.CLOCK_ROOT6.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT6.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT65.DIV.scale, value: '12', locked: true}
- {id: CCM.CLOCK_ROOT65.MUX.sel, value: ANADIG_PLL.PLL_AUDIO_CLK}
- {id: CCM.CLOCK_ROOT66.DIV.scale, value: '12', locked: true}
- {id: CCM.CLOCK_ROOT66.MUX.sel, value: ANADIG_PLL.PLL_AUDIO_CLK}
- {id: CCM.CLOCK_ROOT67.DIV.scale, value: '12', locked: true}
- {id: CCM.CLOCK_ROOT67.MUX.sel, value: ANADIG_PLL.PLL_AUDIO_CLK}
- {id: CCM.CLOCK_ROOT68.DIV.scale, value: '12', locked: true}
- {id: CCM.CLOCK_ROOT68.MUX.sel, value: ANADIG_PLL.PLL_AUDIO_CLK}
- {id: CCM.CLOCK_ROOT69.DIV.scale, value: '12', locked: true}
- {id: CCM.CLOCK_ROOT69.MUX.sel, value: ANADIG_PLL.PLL_AUDIO_CLK}
- {id: CCM.CLOCK_ROOT7.DIV.scale, value: '240', locked: true}
- {id: CCM.CLOCK_ROOT7.MUX.sel, value: ANADIG_OSC.OSC_24M}
- {id: CCM.CLOCK_ROOT70.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT70.MUX.sel, value: ANADIG_PLL.SYS_PLL3_CLK}
- {id: CCM.CLOCK_ROOT71.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT71.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT72.DIV.scale, value: '3', locked: true}
- {id: CCM.CLOCK_ROOT72.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
- {id: CCM.CLOCK_ROOT73.DIV.scale, value: '4', locked: true}
- {id: CCM.CLOCK_ROOT73.MUX.sel, value: ANADIG_PLL.SYS_PLL1_DIV5_CLK}
- {id: CCM.CLOCK_ROOT8.DIV.scale, value: '240', locked: true}
- {id: CCM.CLOCK_ROOT8.MUX.sel, value: ANADIG_OSC.OSC_24M}
- {id: CCM.CLOCK_ROOT9.DIV.scale, value: '2', locked: true}
- {id: CCM.CLOCK_ROOT9.MUX.sel, value: ANADIG_PLL.SYS_PLL3_DIV2_CLK}
sources:
- {id: BLK_CTRL_WAKEUPMIX.ECAT_PORT0_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.ECAT_PORT1_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.NETC_PORT0_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.NETC_PORT1_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.NETC_PORT2_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.NETC_PORT3_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.NETC_PORT4_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
- {id: BLK_CTRL_WAKEUPMIX.SAI1_MCLK_EXT.outFreq, value: 100 kHz}
- {id: BLK_CTRL_WAKEUPMIX.SAI2_MCLK_EXT.outFreq, value: 200 kHz}
- {id: BLK_CTRL_WAKEUPMIX.SAI3_MCLK_EXT.outFreq, value: 300 kHz}
- {id: BLK_CTRL_WAKEUPMIX.SAI4_MCLK_EXT.outFreq, value: 400 kHz}
- {id: BLK_CTRL_WAKEUPMIX.SPDIF_CLK_EXT.outFreq, value: 2 MHz}
- {id: BLK_CTRL_WAKEUPMIX.TMR_1588_REF_CLK_EXT.outFreq, value: 50 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const clock_arm_pll_config_t armPllConfig_BOARD_BootClockRUN = {
        .postDivider = kCLOCK_PllPostDiv2,        /* Post divider, 0 - DIV by 2, 1 - DIV by 4, 2 - DIV by 8, 3 - DIV by 1 */
        .loopDivider = 132,                       /* PLL Loop divider, Fout = Fin * ( loopDivider / ( 2 * postDivider ) ) */
    };

const clock_sys_pll1_config_t sysPll1Config_BOARD_BootClockRUN = {
        .pllDiv2En = 1,                           /* Enable Sys Pll1 divide-by-2 clock or not */
        .pllDiv5En = 1,                           /* Enable Sys Pll1 divide-by-5 clock or not */
        .ss = NULL,                               /* Spread spectrum parameter */
        .ssEnable = false,                        /* Enable spread spectrum or not */
    };

const clock_sys_pll2_config_t sysPll2Config_BOARD_BootClockRUN = {
        .mfd = 268435455,                         /* Denominator of spread spectrum */
        .ss = NULL,                               /* Spread spectrum parameter */
        .ssEnable = false,                        /* Enable spread spectrum or not */
    };

/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    clock_root_config_t rootCfg = {0};

    /* Init OSC RC 400M */
    CLOCK_OSC_EnableOscRc400M();

    /* Switch both core to OscRC400M first */
#if (__CORTEX_M == 7)
    rootCfg.mux = kCLOCK_M7_ClockRoot_MuxOscRc400M;
    rootCfg.div = 1;
    CLOCK_SetRootClock(kCLOCK_Root_M7, &rootCfg);
#endif

#if (__CORTEX_M == 33)
    /* When FlexSPI2 is used, CM33 root clock must be higher than 1/4
       of FlexSPI2 root clock, so set it to OSC RC 400M(but not OSC RC 24M)
       firstly as common setting */
    rootCfg.mux = kCLOCK_M33_ClockRoot_MuxOscRc400M;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_M33, &rootCfg);
#endif

#if (__CORTEX_M == 7)
    DCDC_SetVoltage(kDCDC_CORE0, kDCDC_1P0Target1P125V);
    DCDC_SetVoltage(kDCDC_CORE1, kDCDC_1P0Target1P125V);
    /* FBB need to be enabled in OverDrive(OD) mode */
    PMU_EnableFBB(ANADIG_PMU, true);
#endif

    /* Config CLK_1M */
    CLOCK_OSC_Set1MHzOutputBehavior(kCLOCK_1MHzOutEnableFreeRunning1Mhz);

    /* Init OSC RC 24M */
    CLOCK_OSC_EnableOscRc24M(true);

    /* Config OSC 24M */
    ANADIG_OSC->OSC_24M_CTRL |= ANADIG_OSC_OSC_24M_CTRL_OSC_EN(1) | ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN(0) | ANADIG_OSC_OSC_24M_CTRL_LP_EN(1) | ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE(0);
    /* Wait for 24M OSC to be stable. */
    while (ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_MASK !=
            (ANADIG_OSC->OSC_24M_CTRL & ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_MASK))
    {
    }

    /* Call function BOARD_FlexspiClockSafeConfig() to move FlexSPI clock to a stable clock source to avoid
       instruction/data fetch issue when updating PLL if XIP(execute code on FLEXSPI memory). */
    BOARD_FlexspiClockSafeConfig();

    /* Init Arm Pll. */
    CLOCK_InitArmPll(&armPllConfig_BOARD_BootClockRUN);

    /* Init Sys Pll1. */
    CLOCK_InitSysPll1(&sysPll1Config_BOARD_BootClockRUN);

#ifndef USE_SDRAM
    /* Init Sys Pll2. */
    CLOCK_InitSysPll2(&sysPll2Config_BOARD_BootClockRUN);
    /* Init System Pll2 pfd0. */
    CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd0, 27);
#endif
    /* Init System Pll2 pfd1. */
    CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd1, 16);
    /* Init System Pll2 pfd2. */
    CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd2, 24);
    /* Init System Pll2 pfd3. */
    CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd3, 32);

#ifndef USE_HYPERRAM
    /* Init Sys Pll3. */
    CLOCK_InitSysPll3();
#endif
    /* Init System Pll3 pfd0. */
    CLOCK_InitPfd(kCLOCK_PllSys3, kCLOCK_Pfd0, 22);
    /* Init System Pll3 pfd1. */
    CLOCK_InitPfd(kCLOCK_PllSys3, kCLOCK_Pfd1, 33);
#ifndef USE_HYPERRAM
    /* Init System Pll3 pfd2. */
    CLOCK_InitPfd(kCLOCK_PllSys3, kCLOCK_Pfd2, 22);
#endif
    /* Init System Pll3 pfd3. */
    CLOCK_InitPfd(kCLOCK_PllSys3, kCLOCK_Pfd3, 18);

    /* Bypass Audio Pll. */
    CLOCK_SetPllBypass(kCLOCK_PllAudio, true);
    /* DeInit Audio Pll. */
    CLOCK_DeinitAudioPll();

    /* Module clock root configurations. */
    /* Configure M7 using ARM_PLL_CLK */
#if (__CORTEX_M == 7)
    rootCfg.mux = kCLOCK_M7_ClockRoot_MuxArmPllOut;
    rootCfg.div = 1;
    CLOCK_SetRootClock(kCLOCK_Root_M7, &rootCfg);
#endif

    /* Configure M33 using SYS_PLL3_CLK */
#if (__CORTEX_M == 33)
    rootCfg.mux = kCLOCK_M33_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_M33, &rootCfg);
#endif

    /* Configure EDGELOCK using OSC_RC_400M */
    EdgeLock_SetClock(kCLOCK_EDGELOCK_ClockRoot_MuxOscRc400M, 2);

    /* Configure BUS_AON using SYS_PLL2_CLK */
    rootCfg.mux = kCLOCK_BUS_AON_ClockRoot_MuxSysPll2Out;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Bus_Aon, &rootCfg);

    /* Configure BUS_WAKEUP using SYS_PLL2_CLK */
    rootCfg.mux = kCLOCK_BUS_WAKEUP_ClockRoot_MuxSysPll2Out;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Bus_Wakeup, &rootCfg);

    /* Configure WAKEUP_AXI using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_WAKEUP_AXI_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Wakeup_Axi, &rootCfg);

    /* Configure SWO_TRACE using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_SWO_TRACE_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Swo_Trace, &rootCfg);

    /* Configure M33_SYSTICK using OSC_24M */
#if (__CORTEX_M == 33)
    rootCfg.mux = kCLOCK_M33_SYSTICK_ClockRoot_MuxOsc24MOut;
    rootCfg.div = 240;
    CLOCK_SetRootClock(kCLOCK_Root_M33_Systick, &rootCfg);
#endif

    /* Configure M7_SYSTICK using OSC_24M */
#if (__CORTEX_M == 7)
    rootCfg.mux = kCLOCK_M7_SYSTICK_ClockRoot_MuxOsc24MOut;
    rootCfg.div = 240;
    CLOCK_SetRootClock(kCLOCK_Root_M7_Systick, &rootCfg);
#endif

    /* Configure FLEXIO1 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_FLEXIO1_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Flexio1, &rootCfg);

    /* Configure FLEXIO2 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_FLEXIO2_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 5;
    CLOCK_SetRootClock(kCLOCK_Root_Flexio2, &rootCfg);

    /* Configure LPIT3 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPIT3_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Lpit3, &rootCfg);

    /* Configure LPTIMER1 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPTIMER1_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Lptimer1, &rootCfg);

    /* Configure LPTIMER2 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPTIMER2_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Lptimer2, &rootCfg);

    /* Configure LPTIMER3 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPTIMER3_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Lptimer3, &rootCfg);

    /* Configure TPM2 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_TPM2_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Tpm2, &rootCfg);

    /* Configure TPM4 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_TPM4_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Tpm4, &rootCfg);

    /* Configure TPM5 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_TPM5_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Tpm5, &rootCfg);

    /* Configure TPM6 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_TPM6_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Tpm6, &rootCfg);

    /* Configure GPT1 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_GPT1_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 1;
    CLOCK_SetRootClock(kCLOCK_Root_Gpt1, &rootCfg);

    /* Configure GPT2 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_GPT2_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 1;
    CLOCK_SetRootClock(kCLOCK_Root_Gpt2, &rootCfg);

    /* Configure FLEXSPI1 using SYS_PLL3_PFD0_CLK */
    BOARD_SetFlexspiClock(FLEXSPI1, kCLOCK_FLEXSPI1_ClockRoot_MuxSysPll3Pfd0, 3U);

    /* Configure FLEXSPI2 using SYS_PLL3_PFD2_CLK */
#ifndef USE_HYPERRAM
    BOARD_SetFlexspiClock(FLEXSPI2, kCLOCK_FLEXSPI2_ClockRoot_MuxSysPll3Pfd2, 2U);
#endif

    /* Configure FLEXSPI_SLV using SYS_PLL2_CLK */
    rootCfg.mux = kCLOCK_FLEXSPI_SLV_ClockRoot_MuxSysPll2Out;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Flexspi_Slv, &rootCfg);

    /* Configure CAN1 using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_CAN1_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 6;
    CLOCK_SetRootClock(kCLOCK_Root_Can1, &rootCfg);

    /* Configure CAN2 using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_CAN2_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 6;
    CLOCK_SetRootClock(kCLOCK_Root_Can2, &rootCfg);

    /* Configure CAN3 using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_CAN3_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 6;
    CLOCK_SetRootClock(kCLOCK_Root_Can3, &rootCfg);

    /* Configure LPUART0102 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPUART0102_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Lpuart0102, &rootCfg);

    /* Configure LPUART0304 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPUART0304_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Lpuart0304, &rootCfg);

    /* Configure LPUART0506 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPUART0506_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Lpuart0506, &rootCfg);

    /* Configure LPUART0708 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPUART0708_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Lpuart0708, &rootCfg);

    /* Configure LPUART0910 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPUART0910_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Lpuart0910, &rootCfg);

    /* Configure LPUART1112 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPUART1112_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Lpuart1112, &rootCfg);

    /* Configure LPI2C0102 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPI2C0102_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Lpi2c0102, &rootCfg);

    /* Configure LPI2C0304 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPI2C0304_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Lpi2c0304, &rootCfg);

    /* Configure LPI2C0506 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_LPI2C0506_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Lpi2c0506, &rootCfg);

    /* Configure LPSPI0102 using SYS_PLL3_PFD1_CLK */
    rootCfg.mux = kCLOCK_LPSPI0102_ClockRoot_MuxSysPll3Pfd1;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Lpspi0102, &rootCfg);

    /* Configure LPSPI0304 using SYS_PLL3_PFD1_CLK */
    rootCfg.mux = kCLOCK_LPSPI0304_ClockRoot_MuxSysPll3Pfd1;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Lpspi0304, &rootCfg);

    /* Configure LPSPI0506 using SYS_PLL3_PFD1_CLK */
    rootCfg.mux = kCLOCK_LPSPI0506_ClockRoot_MuxSysPll3Pfd1;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Lpspi0506, &rootCfg);

    /* Configure I3C1 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_I3C1_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_I3c1, &rootCfg);

    /* Configure I3C2 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_I3C2_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_I3c2, &rootCfg);

    /* Configure USDHC1 using SYS_PLL2_PFD2_CLK */
    rootCfg.mux = kCLOCK_USDHC1_ClockRoot_MuxSysPll2Pfd2;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Usdhc1, &rootCfg);

    /* Configure USDHC2 using SYS_PLL2_PFD2_CLK */
    rootCfg.mux = kCLOCK_USDHC2_ClockRoot_MuxSysPll2Pfd2;
    rootCfg.div = 1;
    CLOCK_SetRootClock(kCLOCK_Root_Usdhc2, &rootCfg);

    /* Configure SEMC using SYS_PLL1_CLK */
#ifndef USE_SDRAM
    rootCfg.mux = kCLOCK_SEMC_ClockRoot_MuxSysPll1Out;
    rootCfg.div = 5;
    CLOCK_SetRootClock(kCLOCK_Root_Semc, &rootCfg);
#endif

    /* Configure ADC1 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_ADC1_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Adc1, &rootCfg);

    /* Configure ADC2 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_ADC2_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Adc2, &rootCfg);

    /* Configure ACMP using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_ACMP_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Acmp, &rootCfg);

    /* Configure ECAT using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_ECAT_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 5;
    CLOCK_SetRootClock(kCLOCK_Root_Ecat, &rootCfg);

    /* Configure ENET using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_ENET_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Enet, &rootCfg);

    /* Configure TMR_1588 using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_TMR_1588_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Tmr_1588, &rootCfg);

    /* Configure NETC using SYS_PLL3_PFD3_CLK */
    rootCfg.mux = kCLOCK_NETC_ClockRoot_MuxSysPll3Pfd3;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Netc, &rootCfg);

    /* Configure MAC0 using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_MAC0_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Mac0, &rootCfg);

    /* Configure MAC1 using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_MAC1_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Mac1, &rootCfg);

    /* Configure MAC2 using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_MAC2_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Mac2, &rootCfg);

    /* Configure MAC3 using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_MAC3_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Mac3, &rootCfg);

    /* Configure MAC4 using SYS_PLL1_DIV2_CLK */
    rootCfg.mux = kCLOCK_MAC4_ClockRoot_MuxSysPll1Div2;
    rootCfg.div = 10;
    CLOCK_SetRootClock(kCLOCK_Root_Mac4, &rootCfg);

    /* Configure SAI1 using PLL_AUDIO_CLK */
    rootCfg.mux = kCLOCK_SAI1_ClockRoot_MuxAudioPllOut;
    rootCfg.div = 12;
    CLOCK_SetRootClock(kCLOCK_Root_Sai1, &rootCfg);

    /* Configure SAI2 using PLL_AUDIO_CLK */
    rootCfg.mux = kCLOCK_SAI2_ClockRoot_MuxAudioPllOut;
    rootCfg.div = 12;
    CLOCK_SetRootClock(kCLOCK_Root_Sai2, &rootCfg);

    /* Configure SAI3 using PLL_AUDIO_CLK */
    rootCfg.mux = kCLOCK_SAI3_ClockRoot_MuxAudioPllOut;
    rootCfg.div = 12;
    CLOCK_SetRootClock(kCLOCK_Root_Sai3, &rootCfg);

    /* Configure SAI4 using PLL_AUDIO_CLK */
    rootCfg.mux = kCLOCK_SAI4_ClockRoot_MuxAudioPllOut;
    rootCfg.div = 12;
    CLOCK_SetRootClock(kCLOCK_Root_Sai4, &rootCfg);

    /* Configure SPDIF using PLL_AUDIO_CLK */
    rootCfg.mux = kCLOCK_SPDIF_ClockRoot_MuxAudioPllOut;
    rootCfg.div = 12;
    CLOCK_SetRootClock(kCLOCK_Root_Spdif, &rootCfg);

    /* Configure ASRC using SYS_PLL3_CLK */
    rootCfg.mux = kCLOCK_ASRC_ClockRoot_MuxSysPll3Out;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Asrc, &rootCfg);

    /* Configure MIC using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_MIC_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Mic, &rootCfg);

    /* Configure CKO1 using SYS_PLL3_DIV2_CLK */
    rootCfg.mux = kCLOCK_CKO1_ClockRoot_MuxSysPll3Div2;
    rootCfg.div = 3;
    CLOCK_SetRootClock(kCLOCK_Root_Cko1, &rootCfg);

    /* Configure CKO2 using SYS_PLL1_DIV5_CLK */
    rootCfg.mux = kCLOCK_CKO2_ClockRoot_MuxSysPll1Div5;
    rootCfg.div = 4;
    CLOCK_SetRootClock(kCLOCK_Root_Cko2, &rootCfg);

    /* Set SAI MCLK clock source. */
    BLK_CTRL_SetSaiMClkClockSource(BLK_CTRL_WAKEUPMIX, kBLK_CTRL_SAI2MClk3Sel, 0);
    BLK_CTRL_SetSaiMClkClockSource(BLK_CTRL_WAKEUPMIX, kBLK_CTRL_SAI3MClk3Sel, 0);
    BLK_CTRL_SetSaiMClkClockSource(BLK_CTRL_WAKEUPMIX, kBLK_CTRL_SAI4MClk1Sel, 0);
    BLK_CTRL_SetSaiMClkClockSource(BLK_CTRL_WAKEUPMIX, kBLK_CTRL_SAI4MClk2Sel, 0);
    BLK_CTRL_SetSaiMClkClockSource(BLK_CTRL_WAKEUPMIX, kBLK_CTRL_SAI4MClk3Sel, 0);

    /* Set ECAT PORT Ref clock source. */
    BLK_CTRL_WAKEUPMIX->ECAT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_ECAT_MISC_CFG_RMII_REF_CLK_DIR0_MASK;
    BLK_CTRL_WAKEUPMIX->ECAT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_ECAT_MISC_CFG_RMII_REF_CLK_DIR1_MASK;

    /* Set NETC PORT Ref clock source. */
    BLK_CTRL_WAKEUPMIX->NETC_PORT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT0_RMII_REF_CLK_DIR_MASK;
    BLK_CTRL_WAKEUPMIX->NETC_PORT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT1_RMII_REF_CLK_DIR_MASK;
    BLK_CTRL_WAKEUPMIX->NETC_PORT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT2_RMII_REF_CLK_DIR_MASK;
    BLK_CTRL_WAKEUPMIX->NETC_PORT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT3_RMII_REF_CLK_DIR_MASK;
    BLK_CTRL_WAKEUPMIX->NETC_PORT_MISC_CFG &= ~BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_PORT4_RMII_REF_CLK_DIR_MASK;

    /* Set TMR 1588 Ref clock source. */
    BLK_CTRL_WAKEUPMIX->NETC_PORT_MISC_CFG |= BLK_CTRL_WAKEUPMIX_NETC_PORT_MISC_CFG_TMR_EXT_CLK_SEL_MASK;

#if (__CORTEX_M == 7)
    SystemCoreClock = CLOCK_GetRootClockFreq(kCLOCK_Root_M7);
#else
    SystemCoreClock = CLOCK_GetRootClockFreq(kCLOCK_Root_M33);
#endif
}
