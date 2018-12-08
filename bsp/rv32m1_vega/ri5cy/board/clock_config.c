/*
 * Copyright 2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * How to setup clock using clock driver functions:
 *
 * 1. Call CLOCK_InitXXX() to configure corresponding SCG clock source.
 *    Note: The clock could not be set when it is being used as system clock.
 *    In default out of reset, the CPU is clocked from FIRC(IRC48M),
 *    so before setting FIRC, change to use another avaliable clock source.
 *
 * 2. Call CLOCK_SetXtal0Freq() to set XTAL0 frequency based on board settings.
 *
 * 3. Call CLOCK_SetXxxModeSysClkConfig() to set SCG mode for Xxx run mode.
 *    Wait until the system clock source is changed to target source.
 *
 * 4. If power mode change is needed, call SMC_SetPowerModeProtection() to allow
 *    corresponding power mode and SMC_SetPowerModeXxx() to change to Xxx mode.
 *    Supported run mode and clock restrictions could be found in Reference Manual.
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v3.0
processor: RV32M1
package_id: RV32M1
mcu_data: ksdk2_0
processor_version: 0.0.0
board: RV32M1_VEGA
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "fsl_msmc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SCG_LPFLL_DISABLE                                 0U  /*!< LPFLL clock disabled */
#define SCG_SOSC_DISABLE                                  0U  /*!< System OSC disabled */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 * Code
 ******************************************************************************/
#ifndef SDK_SECONDARY_CORE
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_FircSafeConfig
 * Description   : This function is used to safely configure FIRC clock.
 *                 In default out of reset, the CPU is clocked from FIRC(IRC48M).
 *                 Before setting FIRC, change to use SIRC as system clock,
 *                 then configure FIRC. 
 * Param fircConfig  : FIRC configuration.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_FircSafeConfig(const scg_firc_config_t *fircConfig)
{
    scg_sys_clk_config_t curConfig;
    const scg_sirc_config_t scgSircConfig = {.enableMode = kSCG_SircEnable,
                                             .div1 = kSCG_AsyncClkDisable,
                                             .div2 = kSCG_AsyncClkDivBy2,
                                             .range = kSCG_SircRangeHigh};
    scg_sys_clk_config_t sysClkSafeConfigSource = {
         .divSlow = kSCG_SysClkDivBy4, /* Slow clock divider. */
         .divCore = kSCG_SysClkDivBy1, /* Core clock divider. */
         .src = kSCG_SysClkSrcSirc     /* System clock source. */
    };
    /* Init Sirc */
    CLOCK_InitSirc(&scgSircConfig);
    /* Change to use SIRC as system clock source to prepare to change FIRCCFG register */
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);

    /* Init Firc */
    CLOCK_InitFirc(fircConfig);
}
#endif

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
- {id: Bus_clock.outFreq, value: 48 MHz}
- {id: Core_clock.outFreq, value: 48 MHz}
- {id: FIRCDIV1_CLK.outFreq, value: 48 MHz}
- {id: FIRCDIV2_CLK.outFreq, value: 48 MHz}
- {id: FIRCDIV3_CLK.outFreq, value: 48 MHz}
- {id: LPO_CLK.outFreq, value: 1 kHz}
- {id: Platform_clock.outFreq, value: 48 MHz}
- {id: SIRCDIV3_CLK.outFreq, value: 8 MHz}
- {id: Slow_clock.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
settings:
- {id: SCG.FIRCDIV1.scale, value: '1', locked: true}
- {id: SCG.FIRCDIV2.scale, value: '1', locked: true}
- {id: SCG.FIRCDIV3.scale, value: '1', locked: true}
- {id: SCG.LPFLLDIV1.scale, value: '1', locked: true}
- {id: SCG.LPFLLDIV3.scale, value: '0', locked: true}
- {id: SCG.SIRCDIV1.scale, value: '0', locked: true}
- {id: SCG.SIRCDIV3.scale, value: '1', locked: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockRUN =
    {
        .divSlow = kSCG_SysClkDivBy2,             /* Slow Clock Divider: divided by 2 */
        .divBus = kSCG_SysClkDivBy1,              /* Bus Clock Divider: divided by 1 */
        .divExt = kSCG_SysClkDivBy1,              /* External Clock Divider: divided by 1 */
        .divCore = kSCG_SysClkDivBy1,             /* Core Clock Divider: divided by 1 */
        .src = kSCG_SysClkSrcFirc,                /* Fast IRC is selected as System Clock Source */
    };
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockRUN =
    {
        .freq = 0U,                               /* System Oscillator frequency: 0Hz */
        .monitorMode = kSCG_SysOscMonitorDisable, /* Monitor disabled */
        .enableMode = SCG_SOSC_DISABLE,           /* System OSC disabled */
        .div1 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 3: Clock output is disabled */
    };
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockRUN =
    {
        .enableMode = kSCG_SircEnable | kSCG_SircEnableInLowPower,/* Enable SIRC clock, Enable SIRC in low power mode */
        .div1 = kSCG_AsyncClkDisable,             /* Slow IRC Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* Slow IRC Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDivBy1,              /* Slow IRC Clock Divider 3: divided by 1 */
        .range = kSCG_SircRangeHigh,              /* Slow IRC high range clock (8 MHz) */
    };
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockRUN =
    {
        .enableMode = kSCG_FircEnable,            /* Enable FIRC clock */
        .div1 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 1: divided by 1 */
        .div2 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 2: divided by 1 */
        .div3 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 3: divided by 1 */
        .range = kSCG_FircRange48M,               /* Fast IRC is trimmed to 48MHz */
        .trimConfig = NULL,
    };
const scg_lpfll_config_t g_scgLpFllConfig_BOARD_BootClockRUN =
    {
        .enableMode = SCG_LPFLL_DISABLE,          /* LPFLL clock disabled */
        .div1 = kSCG_AsyncClkDivBy1,              /* Low Power FLL Clock Divider 1: divided by 1 */
        .div2 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 3: Clock output is disabled */
        .range = kSCG_LpFllRange48M,              /* LPFLL is trimmed to 48MHz */
        .trimConfig = NULL,
    };
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
#ifndef SDK_SECONDARY_CORE
    scg_sys_clk_config_t curConfig;

    /* Init FIRC */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockRUN);
    /* Set SCG to FIRC mode. */
    CLOCK_SetRunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockRUN);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockRUN.src);
    /* Init SIRC */
    CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockRUN);
    /* Init LPFLL */
    CLOCK_InitLpFll(&g_scgLpFllConfig_BOARD_BootClockRUN);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
#endif
}

/*******************************************************************************
 ********************* Configuration BOARD_BootClockHSRUN **********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockHSRUN
outputs:
- {id: Bus_clock.outFreq, value: 72 MHz}
- {id: Core_clock.outFreq, value: 72 MHz}
- {id: FIRCDIV1_CLK.outFreq, value: 48 MHz}
- {id: FIRCDIV2_CLK.outFreq, value: 48 MHz}
- {id: FIRCDIV3_CLK.outFreq, value: 48 MHz}
- {id: LPO_CLK.outFreq, value: 1 kHz}
- {id: Platform_clock.outFreq, value: 72 MHz}
- {id: SIRCDIV3_CLK.outFreq, value: 8 MHz}
- {id: Slow_clock.outFreq, value: 8 MHz}
- {id: System_clock.outFreq, value: 72 MHz}
settings:
- {id: SCGMode, value: LPFLL}
- {id: powerMode, value: HSRUN}
- {id: SCG.DIVCORE.scale, value: '1', locked: true}
- {id: SCG.DIVSLOW.scale, value: '9'}
- {id: SCG.FIRCDIV1.scale, value: '1', locked: true}
- {id: SCG.FIRCDIV2.scale, value: '1', locked: true}
- {id: SCG.FIRCDIV3.scale, value: '1', locked: true}
- {id: SCG.LPFLLDIV1.scale, value: '0', locked: true}
- {id: SCG.LPFLL_mul.scale, value: '36', locked: true}
- {id: SCG.SCSSEL.sel, value: SCG.LPFLL}
- {id: SCG.SIRCDIV3.scale, value: '1', locked: true}
- {id: SCG.TRIMDIV.scale, value: '24'}
- {id: SCG.TRIMSRCSEL.sel, value: SCG.FIRC}
- {id: 'SCG::RCCR[SCS].bitField', value: '5'}
- {id: SCG_LPFLLCSR_LPFLLEN_CFG, value: Enabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockHSRUN configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockHSRUN =
    {
        .divSlow = kSCG_SysClkDivBy9,             /* Slow Clock Divider: divided by 9 */
        .divBus = kSCG_SysClkDivBy1,              /* Bus Clock Divider: divided by 1 */
        .divExt = kSCG_SysClkDivBy1,              /* External Clock Divider: divided by 1 */
        .divCore = kSCG_SysClkDivBy1,             /* Core Clock Divider: divided by 1 */
        .src = kSCG_SysClkSrcLpFll,               /* Low power FLL is selected as System Clock Source */
    };
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockHSRUN =
    {
        .freq = 0U,                               /* System Oscillator frequency: 0Hz */
        .monitorMode = kSCG_SysOscMonitorDisable, /* Monitor disabled */
        .enableMode = SCG_SOSC_DISABLE,           /* System OSC disabled */
        .div1 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 3: Clock output is disabled */
    };
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockHSRUN =
    {
        .enableMode = kSCG_SircEnable | kSCG_SircEnableInLowPower,/* Enable SIRC clock, Enable SIRC in low power mode */
        .div1 = kSCG_AsyncClkDisable,             /* Slow IRC Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* Slow IRC Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDivBy1,              /* Slow IRC Clock Divider 3: divided by 1 */
        .range = kSCG_SircRangeHigh,              /* Slow IRC high range clock (8 MHz) */
    };
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockHSRUN =
    {
        .enableMode = kSCG_FircEnable,            /* Enable FIRC clock */
        .div1 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 1: divided by 1 */
        .div2 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 2: divided by 1 */
        .div3 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 3: divided by 1 */
        .range = kSCG_FircRange48M,               /* Fast IRC is trimmed to 48MHz */
        .trimConfig = NULL,
    };
const scg_lpfll_config_t g_scgLpFllConfig_BOARD_BootClockHSRUN =
    {
        .enableMode = kSCG_LpFllEnable,           /* Enable LPFLL clock */
        .div1 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 3: Clock output is disabled */
        .range = kSCG_LpFllRange72M,              /* LPFLL is trimmed to 72MHz */
        .trimConfig = NULL,
    };
/*******************************************************************************
 * Code for BOARD_BootClockHSRUN configuration
 ******************************************************************************/
void BOARD_BootClockHSRUN(void)
{
#ifndef SDK_SECONDARY_CORE
    scg_sys_clk_config_t curConfig;

    /* Init FIRC */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockHSRUN);
    /* Init LPFLL */
    CLOCK_InitLpFll(&g_scgLpFllConfig_BOARD_BootClockHSRUN);
#if defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_ri5cy)
    /* Set HSRUN power mode */
    SMC_SetPowerModeProtection(SMC0, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeHsrun(SMC0);
    while (SMC_GetPowerModeState(SMC0) != kSMC_PowerStateHsrun)
    {
    }
#elif defined(CPU_RV32M1_cm0plus) || defined(CPU_RV32M1_zero_riscy)
    SMC_SetPowerModeProtection(SMC1, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeHsrun(SMC1);
    while (SMC_GetPowerModeState(SMC1) != kSMC_PowerStateHsrun)
    {
    }
#endif
    /* Set SCG to LPFLL mode. */
    CLOCK_SetHsrunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockHSRUN);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockHSRUN.src);
    /* Init SIRC */
    CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockHSRUN);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKHSRUN_CORE_CLOCK;
#endif
}

/*******************************************************************************
 ********************* Configuration BOARD_BootClockVLPR ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockVLPR
outputs:
- {id: Bus_clock.outFreq, value: 2 MHz}
- {id: Core_clock.outFreq, value: 4 MHz}
- {id: LPO_CLK.outFreq, value: 1 kHz}
- {id: Platform_clock.outFreq, value: 4 MHz}
- {id: SIRCDIV1_CLK.outFreq, value: 8 MHz}
- {id: SIRCDIV2_CLK.outFreq, value: 8 MHz}
- {id: SIRCDIV3_CLK.outFreq, value: 8 MHz}
- {id: Slow_clock.outFreq, value: 4000/9 kHz}
- {id: System_clock.outFreq, value: 4 MHz}
settings:
- {id: SCGMode, value: SIRC}
- {id: powerMode, value: VLPR}
- {id: SCG.DIVBUS.scale, value: '2', locked: true}
- {id: SCG.DIVCORE.scale, value: '2', locked: true}
- {id: SCG.DIVSLOW.scale, value: '9'}
- {id: SCG.FIRCDIV1.scale, value: '1'}
- {id: SCG.SCSSEL.sel, value: SCG.SIRC}
- {id: SCG.SIRCDIV1.scale, value: '1', locked: true}
- {id: SCG.SIRCDIV2.scale, value: '1', locked: true}
- {id: SCG.SIRCDIV3.scale, value: '1', locked: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockVLPR configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockVLPR =
    {
        .divSlow = kSCG_SysClkDivBy9,             /* Slow Clock Divider: divided by 9 */
        .divBus = kSCG_SysClkDivBy2,              /* Bus Clock Divider: divided by 2 */
        .divExt = kSCG_SysClkDivBy1,              /* External Clock Divider: divided by 1 */
        .divCore = kSCG_SysClkDivBy2,             /* Core Clock Divider: divided by 2 */
        .src = kSCG_SysClkSrcSirc,                /* Slow IRC is selected as System Clock Source */
    };
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockVLPR =
    {
        .freq = 0U,                               /* System Oscillator frequency: 0Hz */
        .monitorMode = kSCG_SysOscMonitorDisable, /* Monitor disabled */
        .enableMode = SCG_SOSC_DISABLE,           /* System OSC disabled */
        .div1 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* System OSC Clock Divider 3: Clock output is disabled */
    };
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockVLPR =
    {
        .enableMode = kSCG_SircEnable | kSCG_SircEnableInLowPower,/* Enable SIRC clock, Enable SIRC in low power mode */
        .div1 = kSCG_AsyncClkDivBy1,              /* Slow IRC Clock Divider 1: divided by 1 */
        .div2 = kSCG_AsyncClkDivBy1,              /* Slow IRC Clock Divider 2: divided by 1 */
        .div3 = kSCG_AsyncClkDivBy1,              /* Slow IRC Clock Divider 3: divided by 1 */
        .range = kSCG_SircRangeHigh,              /* Slow IRC high range clock (8 MHz) */
    };
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockVLPR =
    {
        .enableMode = kSCG_FircEnable,            /* Enable FIRC clock */
        .div1 = kSCG_AsyncClkDivBy1,              /* Fast IRC Clock Divider 1: divided by 1 */
        .div2 = kSCG_AsyncClkDisable,             /* Fast IRC Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* Fast IRC Clock Divider 3: Clock output is disabled */
        .range = kSCG_FircRange48M,               /* Fast IRC is trimmed to 48MHz */
        .trimConfig = NULL,
    };
const scg_lpfll_config_t g_scgLpFllConfig_BOARD_BootClockVLPR =
    {
        .enableMode = SCG_LPFLL_DISABLE,          /* LPFLL clock disabled */
        .div1 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 1: Clock output is disabled */
        .div2 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 2: Clock output is disabled */
        .div3 = kSCG_AsyncClkDisable,             /* Low Power FLL Clock Divider 3: Clock output is disabled */
        .range = kSCG_LpFllRange48M,              /* LPFLL is trimmed to 48MHz */
        .trimConfig = NULL,
    };
/*******************************************************************************
 * Code for BOARD_BootClockVLPR configuration
 ******************************************************************************/
void BOARD_BootClockVLPR(void)
{
#ifndef SDK_SECONDARY_CORE
    scg_sys_clk_config_t curConfig;

    /* Init SIRC */
    CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockVLPR);
    /* Set SCG to SIRC mode. */
    CLOCK_SetVlprModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockVLPR);
    /* Init FIRC */
    CLOCK_InitFirc(&g_scgFircConfig_BOARD_BootClockVLPR);
    /* Init LPFLL */
    CLOCK_InitLpFll(&g_scgLpFllConfig_BOARD_BootClockVLPR);
#if defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_ri5cy)
    /* Set VLPR power mode. */
    SMC_SetPowerModeProtection(SMC0, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeVlpr(SMC0);
    while (SMC_GetPowerModeState(SMC0) != kSMC_PowerStateVlpr)
    {
    }
#elif defined(CPU_RV32M1_cm0plus) || defined(CPU_RV32M1_zero_riscy)
    /* Set VLPR power mode. */
    SMC_SetPowerModeProtection(SMC1, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeVlpr(SMC1);
    while (SMC_GetPowerModeState(SMC1) != kSMC_PowerStateVlpr)
    {
    }
#endif
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockVLPR.src);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKVLPR_CORE_CLOCK;
#endif
}

