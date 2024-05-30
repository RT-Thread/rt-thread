/*******************************************************************************
 * File Name: cycfg_system.c
 *
 * Description:
 * System configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.20.0
 * device-db 4.15.0.5746
 * mtb-pdl-cat1 3.10.0.32115
 *
 *******************************************************************************
 * Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#include "cycfg_system.h"

#define CY_CFG_SYSCLK_ECO_ERROR 1
#define CY_CFG_SYSCLK_ALTHF_ERROR 2
#define CY_CFG_SYSCLK_PLL_ERROR 3
#define CY_CFG_SYSCLK_FLL_ERROR 4
#define CY_CFG_SYSCLK_WCO_ERROR 5

#if  (CY_CPU_CORTEX_M7)
#define CY_CFG_SYSCLK_CLKALTSYSTICK_ENABLED 1
#define CY_CFG_SYSCLK_CLKALTSYSTICK_SOURCE CY_SYSTICK_CLOCK_SOURCE_CLK_IMO
#define CY_CFG_SYSCLK_CLKALTSYSTICK_INTERVAL 0
#define CY_CFG_SYSCLK_CLKALTSYSTICK_FREQUENCY 8000000
#define CY_CFG_SYSCLK_CLKALTSYSTICK_TICKS ((0)/1000000.0)*8000000
#endif /*  (CY_CPU_CORTEX_M7) */

#define CY_CFG_SYSCLK_CLKBAK_ENABLED 1
#define CY_CFG_SYSCLK_CLKBAK_SOURCE CY_SYSCLK_BAK_IN_CLKLF
#define CY_CFG_SYSCLK_ECO_ENABLED 1
#define CY_CFG_SYSCLK_ECO_FREQ 16000000UL
#define CY_CFG_SYSCLK_ECO_GPIO_IN_PRT GPIO_PRT21
#define CY_CFG_SYSCLK_ECO_GPIO_IN_PIN 2
#define CY_CFG_SYSCLK_ECO_GPIO_OUT_PRT GPIO_PRT21
#define CY_CFG_SYSCLK_ECO_GPIO_OUT_PIN 3
#define CY_CFG_SYSCLK_ECO_CLOAD 10UL
#define CY_CFG_SYSCLK_ECO_ESR 150UL
#define CY_CFG_SYSCLK_ECO_DRIVE_LEVEL 100UL
#define CY_CFG_SYSCLK_CLKFAST_0_ENABLED 1
#define CY_CFG_SYSCLK_CLKFAST_0_INT_DIVIDER 0
#define CY_CFG_SYSCLK_CLKFAST_0_FRAC_DIVIDER 0
#define CY_CFG_SYSCLK_CLKFAST_1_ENABLED 1
#define CY_CFG_SYSCLK_CLKFAST_1_INT_DIVIDER 0
#define CY_CFG_SYSCLK_CLKFAST_1_FRAC_DIVIDER 0
#define CY_CFG_SYSCLK_FLL_ENABLED 1
#define CY_CFG_SYSCLK_FLL_MULT 500U
#define CY_CFG_SYSCLK_FLL_REFDIV 40U
#define CY_CFG_SYSCLK_FLL_CCO_RANGE CY_SYSCLK_FLL_CCO_RANGE4
#define CY_CFG_SYSCLK_FLL_ENABLE_OUTDIV true
#define CY_CFG_SYSCLK_FLL_LOCK_TOLERANCE 2U
#define CY_CFG_SYSCLK_FLL_IGAIN 9U
#define CY_CFG_SYSCLK_FLL_PGAIN 5U
#define CY_CFG_SYSCLK_FLL_SETTLING_COUNT 16U
#define CY_CFG_SYSCLK_FLL_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT
#define CY_CFG_SYSCLK_FLL_CCO_FREQ 355U
#define CY_CFG_SYSCLK_FLL_OUT_FREQ 100000000
#define CY_CFG_SYSCLK_CLKHF0_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF0_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF0_FREQ_MHZ 200UL
#define CY_CFG_SYSCLK_CLKHF0_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH3
#define CY_CFG_SYSCLK_CLKHF1_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF1_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF1_FREQ_MHZ 350UL
#define CY_CFG_SYSCLK_CLKHF1_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH1
#define CY_CFG_SYSCLK_CLKHF2_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF2_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF2_FREQ_MHZ 100UL
#define CY_CFG_SYSCLK_CLKHF2_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH4
#define CY_CFG_SYSCLK_CLKHF3_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF3_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF3_FREQ_MHZ 100UL
#define CY_CFG_SYSCLK_CLKHF3_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH3
#define CY_CFG_SYSCLK_CLKHF4_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF4_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF4_FREQ_MHZ 125UL
#define CY_CFG_SYSCLK_CLKHF4_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF5_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF5_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF5_FREQ_MHZ 125UL
#define CY_CFG_SYSCLK_CLKHF5_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF6_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF6_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF6_FREQ_MHZ 200UL
#define CY_CFG_SYSCLK_CLKHF6_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH3
#define CY_CFG_SYSCLK_CLKHF7_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF7_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF7_FREQ_MHZ 0UL
#define CY_CFG_SYSCLK_CLKHF7_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH5
#define CY_CFG_SYSCLK_ILO0_ENABLED 1
#define CY_CFG_SYSCLK_ILO0_HIBERNATE true
#define CY_CFG_SYSCLK_ILO1_ENABLED 1
#define CY_CFG_SYSCLK_ILO1_HIBERNATE true
#define CY_CFG_SYSCLK_IMO_ENABLED 1
#define CY_CFG_SYSCLK_CLKLF_ENABLED 1
#define CY_CFG_SYSCLK_CLKMEM_ENABLED 1
#define CY_CFG_SYSCLK_CLKMEM_DIVIDER 0
#define CY_CFG_SYSCLK_CLKPATH0_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH0_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH0_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH1_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH1_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH1_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH2_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH2_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH2_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH3_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH3_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH3_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH4_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH4_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH4_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH5_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH5_SOURCE CY_SYSCLK_CLKPATH_IN_ILO0
#define CY_CFG_SYSCLK_CLKPATH5_SOURCE_NUM 6UL
#define CY_CFG_SYSCLK_CLKPATH6_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH6_SOURCE CY_SYSCLK_CLKPATH_IN_IMO
#define CY_CFG_SYSCLK_CLKPATH6_SOURCE_NUM 0UL
#define CY_CFG_SYSCLK_PLL0_ENABLED 1
#define CY_CFG_SYSCLK_PLL0_FEEDBACK_DIV 43
#define CY_CFG_SYSCLK_PLL0_REFERENCE_DIV 1
#define CY_CFG_SYSCLK_PLL0_OUTPUT_DIV 2
#define CY_CFG_SYSCLK_PLL0_FRAC_DIV 12582912
#define CY_CFG_SYSCLK_PLL0_FRAC_DITHER_EN false
#define CY_CFG_SYSCLK_PLL0_FRAC_EN true
#define CY_CFG_SYSCLK_PLL0_LF_MODE false
#define CY_CFG_SYSCLK_PLL0_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_PLL0_OUTPUT_FREQ 350000000
#define CY_CFG_SYSCLK_PLL1_ENABLED 1
#define CY_CFG_SYSCLK_PLL1_FEEDBACK_DIV 31
#define CY_CFG_SYSCLK_PLL1_REFERENCE_DIV 1
#define CY_CFG_SYSCLK_PLL1_OUTPUT_DIV 2
#define CY_CFG_SYSCLK_PLL1_FRAC_DIV 4194304
#define CY_CFG_SYSCLK_PLL1_FRAC_DITHER_EN false
#define CY_CFG_SYSCLK_PLL1_FRAC_EN true
#define CY_CFG_SYSCLK_PLL1_LF_MODE false
#define CY_CFG_SYSCLK_PLL1_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_PLL1_OUTPUT_FREQ 250000000
#define CY_CFG_SYSCLK_PLL2_ENABLED 1
#define CY_CFG_SYSCLK_PLL2_FEEDBACK_DIV 50
#define CY_CFG_SYSCLK_PLL2_REFERENCE_DIV 2
#define CY_CFG_SYSCLK_PLL2_OUTPUT_DIV 2
#define CY_CFG_SYSCLK_PLL2_LF_MODE false
#define CY_CFG_SYSCLK_PLL2_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_PLL2_OUTPUT_FREQ 200000000
#define CY_CFG_SYSCLK_PLL3_ENABLED 1
#define CY_CFG_SYSCLK_PLL3_FEEDBACK_DIV 25
#define CY_CFG_SYSCLK_PLL3_REFERENCE_DIV 2
#define CY_CFG_SYSCLK_PLL3_OUTPUT_DIV 2
#define CY_CFG_SYSCLK_PLL3_LF_MODE false
#define CY_CFG_SYSCLK_PLL3_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_PLL3_OUTPUT_FREQ 100000000
#define CY_CFG_SYSCLK_CLKSLOW_ENABLED 1
#define CY_CFG_SYSCLK_CLKSLOW_DIVIDER 1
#define CY_CFG_SYSCLK_WCO_ENABLED 1
#define CY_CFG_SYSCLK_WCO_IN_PRT GPIO_PRT21
#define CY_CFG_SYSCLK_WCO_IN_PIN 0U
#define CY_CFG_SYSCLK_WCO_OUT_PRT GPIO_PRT21
#define CY_CFG_SYSCLK_WCO_OUT_PIN 1U
#define CY_CFG_SYSCLK_WCO_BYPASS CY_SYSCLK_WCO_NOT_BYPASSED
#define CY_CFG_PWR_ENABLED 1
#define CY_CFG_PWR_INIT 1
#define CY_CFG_PWR_VBACKUP_USING_VDDD 1
#define CY_CFG_PWR_REGULATOR_MODE_MIN 0
#define CY_CFG_PWR_USING_ULP 0

#if (!defined(CY_DEVICE_SECURE))
static const cy_stc_fll_manual_config_t srss_0_clock_0_fll_0_fllConfig =
{
    .fllMult = 500U,
    .refDiv = 40U,
    .ccoRange = CY_SYSCLK_FLL_CCO_RANGE4,
    .enableOutputDiv = true,
    .lockTolerance = 2U,
    .igain = 9U,
    .pgain = 5U,
    .settlingCount = 16U,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT,
    .cco_Freq = 355U,
};
#endif /* (!defined(CY_DEVICE_SECURE)) */

#if defined (CY_USING_HAL)
const cyhal_resource_inst_t srss_0_clock_0_pathmux_0_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 0U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_1_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 1U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_2_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 2U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_3_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 3U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_4_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 4U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_5_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 5U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_6_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 6U,
    .channel_num = 0U,
};
#endif /* defined (CY_USING_HAL) */

static const cy_stc_pll_manual_config_t srss_0_clock_0_pll400m_0_pllConfig =
{
    .feedbackDiv = 43,
    .referenceDiv = 1,
    .outputDiv = 2,
    .lfMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
    .fracDiv = 12582912,
    .fracDitherEn = false,
    .fracEn = true,
};
static const cy_stc_pll_manual_config_t srss_0_clock_0_pll400m_1_pllConfig =
{
    .feedbackDiv = 31,
    .referenceDiv = 1,
    .outputDiv = 2,
    .lfMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
    .fracDiv = 4194304,
    .fracDitherEn = false,
    .fracEn = true,
};

#if (!defined(CY_DEVICE_SECURE))
static const cy_stc_pll_manual_config_t srss_0_clock_0_pll_0_pllConfig =
{
    .feedbackDiv = 50,
    .referenceDiv = 2,
    .outputDiv = 2,
    .lfMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
};
static const cy_stc_pll_manual_config_t srss_0_clock_0_pll_1_pllConfig =
{
    .feedbackDiv = 25,
    .referenceDiv = 2,
    .outputDiv = 2,
    .lfMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
};
#endif /* (!defined(CY_DEVICE_SECURE)) */

__WEAK void cycfg_ClockStartupError(uint32_t error)
{
    (void)error; /* Suppress the compiler warning */
    while(1);
}

#if !defined (CY_CFG_SYSCLK_ILO0_ENABLED)
__STATIC_INLINE void Cy_SysClk_Ilo0DeInit()
{
    if(Cy_SysPm_IsBgRefCtrl())
    {
        Cy_SysPm_BgRefCtrl(false);
        Cy_WDT_Unlock();
        Cy_SysClk_IloSrcDisable(0);
        Cy_SysClk_IloSrcHibernateOn(0, false);
        Cy_WDT_Lock();
        Cy_SysPm_BgRefCtrl(true);
    }
    else
    {
        Cy_WDT_Unlock();
        Cy_SysClk_IloSrcDisable(0);
        Cy_SysClk_IloSrcHibernateOn(0, false);
        Cy_WDT_Lock();
    }
}
#endif /* !defined (CY_CFG_SYSCLK_ILO0_ENABLED) */

#if !defined (CY_CFG_SYSCLK_ILO1_ENABLED)
__STATIC_INLINE void Cy_SysClk_Ilo1DeInit()
{
    Cy_SysClk_IloSrcDisable(1);
    Cy_SysClk_IloSrcHibernateOn(1, false);
}
#endif /* !defined (CY_CFG_SYSCLK_ILO1_ENABLED) */

#if ((!defined(CY_DEVICE_SECURE)))
__STATIC_INLINE void Cy_SysClk_FllDeInit()
{
    Cy_SysClk_FllDisable();
}
#endif /* ((!defined(CY_DEVICE_SECURE))) */

#if  (CY_CPU_CORTEX_M7)
__STATIC_INLINE void Cy_SysClk_ClkAltSysTickInit()
{
    Cy_SysTick_Init(CY_CFG_SYSCLK_CLKALTSYSTICK_SOURCE, CY_CFG_SYSCLK_CLKALTSYSTICK_TICKS);
}
#endif /*  (CY_CPU_CORTEX_M7) */

#if (!defined(CY_DEVICE_SECURE))
__STATIC_INLINE void Cy_SysClk_ClkBakInit()
{
    Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_CLKLF);
}
__STATIC_INLINE void Cy_SysClk_EcoInit()
{
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT21, 2, CY_GPIO_DM_ANALOG, 0UL, HSIOM_SEL_GPIO);
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT21, 3, CY_GPIO_DM_ANALOG, 0UL, HSIOM_SEL_GPIO);
    if (CY_SYSCLK_BAD_PARAM == Cy_SysClk_EcoConfigure(CY_CFG_SYSCLK_ECO_FREQ, 17UL, 150UL, 100UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_ECO_ERROR);
    }
    if (CY_SYSCLK_TIMEOUT == Cy_SysClk_EcoEnable(3000UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_ECO_ERROR);
    }
}
#endif /* (!defined(CY_DEVICE_SECURE)) */

__STATIC_INLINE void Cy_SysClk_ClkFast_0_Init()
{
    Cy_SysClk_ClkFastSrcSetDivider(0, CY_CFG_SYSCLK_CLKFAST_0_INT_DIVIDER, CY_CFG_SYSCLK_CLKFAST_0_FRAC_DIVIDER);
}
__STATIC_INLINE void Cy_SysClk_ClkFast_1_Init()
{
    Cy_SysClk_ClkFastSrcSetDivider(1, CY_CFG_SYSCLK_CLKFAST_1_INT_DIVIDER, CY_CFG_SYSCLK_CLKFAST_1_FRAC_DIVIDER);
}

#if (!defined(CY_DEVICE_SECURE))
__STATIC_INLINE void Cy_SysClk_FllInit()
{
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_FllManualConfigure(&srss_0_clock_0_fll_0_fllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_FLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_FllEnable(200000UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_FLL_ERROR);
    }
}
#endif /* (!defined(CY_DEVICE_SECURE)) */

__STATIC_INLINE void Cy_SysClk_ClkHf0Init()
{
    Cy_SysClk_ClkHfSetSource(0U, CY_CFG_SYSCLK_CLKHF0_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(0U, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF0, false);
}
__STATIC_INLINE void Cy_SysClk_ClkHf1Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF1, CY_CFG_SYSCLK_CLKHF1_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF1, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF1, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF1);
}
__STATIC_INLINE void Cy_SysClk_ClkHf2Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF2, CY_CFG_SYSCLK_CLKHF2_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF2, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF2, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF2);
}
__STATIC_INLINE void Cy_SysClk_ClkHf3Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF3, CY_CFG_SYSCLK_CLKHF3_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF3, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF3, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF3);
}
__STATIC_INLINE void Cy_SysClk_ClkHf4Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF4, CY_CFG_SYSCLK_CLKHF4_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF4, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF4, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF4);
}
__STATIC_INLINE void Cy_SysClk_ClkHf5Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF5, CY_CFG_SYSCLK_CLKHF5_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF5, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF5, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF5);
}
__STATIC_INLINE void Cy_SysClk_ClkHf6Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF6, CY_CFG_SYSCLK_CLKHF6_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF6, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF6, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF6);
}
__STATIC_INLINE void Cy_SysClk_ClkHf7Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF7, CY_CFG_SYSCLK_CLKHF7_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF7, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfDirectSel(CY_CFG_SYSCLK_CLKHF7, false);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF7);
}

#if (!defined(CY_DEVICE_SECURE))
__STATIC_INLINE void Cy_SysClk_Ilo0Init()
{
    /* The WDT is unlocked in the default startup code */
    Cy_SysClk_IloSrcEnable(0);
    Cy_SysClk_IloSrcHibernateOn(0, true);
}
__STATIC_INLINE void Cy_SysClk_Ilo1Init()
{
    /* The WDT is unlocked in the default startup code */
    Cy_SysClk_IloSrcEnable(1);
    Cy_SysClk_IloSrcHibernateOn(1, true);
}
#endif /* (!defined(CY_DEVICE_SECURE)) */

__STATIC_INLINE void Cy_SysClk_ClkLfInit()
{
    /* The WDT is unlocked in the default startup code */
    Cy_SysClk_ClkLfSetSource(CY_CFG_SYSCLK_CLKLF_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkMemInit()
{
    Cy_SysClk_ClkMemSetDivider(0U);
}

#if (!defined(CY_DEVICE_SECURE))
__STATIC_INLINE void Cy_SysClk_ClkPath0Init()
{
    Cy_SysClk_ClkPathSetSource(0U, CY_CFG_SYSCLK_CLKPATH0_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath1Init()
{
    Cy_SysClk_ClkPathSetSource(1U, CY_CFG_SYSCLK_CLKPATH1_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath2Init()
{
    Cy_SysClk_ClkPathSetSource(2U, CY_CFG_SYSCLK_CLKPATH2_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath3Init()
{
    Cy_SysClk_ClkPathSetSource(3U, CY_CFG_SYSCLK_CLKPATH3_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath4Init()
{
    Cy_SysClk_ClkPathSetSource(4U, CY_CFG_SYSCLK_CLKPATH4_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath5Init()
{
    Cy_SysClk_ClkPathSetSource(5U, CY_CFG_SYSCLK_CLKPATH5_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath6Init()
{
    Cy_SysClk_ClkPathSetSource(6U, CY_CFG_SYSCLK_CLKPATH6_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPeriInit()
{
    Cy_SysClk_ClkPeriSetDivider(1U);
}
#endif /* (!defined(CY_DEVICE_SECURE)) */

__STATIC_INLINE void Cy_SysClk_Pll0Init()
{
    Cy_SysClk_PllDisable(SRSS_PLL_400M_0_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_PLL_400M_0_PATH_NUM, &srss_0_clock_0_pll400m_0_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_PLL_400M_0_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
}
__STATIC_INLINE void Cy_SysClk_Pll1Init()
{
    Cy_SysClk_PllDisable(SRSS_PLL_400M_1_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_PLL_400M_1_PATH_NUM, &srss_0_clock_0_pll400m_1_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_PLL_400M_1_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
}
__STATIC_INLINE void Cy_SysClk_Pll2Init()
{
    Cy_SysClk_PllDisable(SRSS_PLL_200M_0_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_PLL_200M_0_PATH_NUM, &srss_0_clock_0_pll_0_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_PLL_200M_0_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
}
__STATIC_INLINE void Cy_SysClk_Pll3Init()
{
    Cy_SysClk_PllDisable(SRSS_PLL_200M_1_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_PLL_200M_1_PATH_NUM, &srss_0_clock_0_pll_1_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_PLL_200M_1_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
}

#if (!defined(CY_DEVICE_SECURE))
__STATIC_INLINE void Cy_SysClk_ClkSlowInit()
{
    Cy_SysClk_ClkSlowSetDivider(1U);
}
__STATIC_INLINE void Cy_SysClk_WcoInit()
{
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT21, 0U, 0x00U, 0x00U, HSIOM_SEL_GPIO);
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT21, 1U, 0x00U, 0x00U, HSIOM_SEL_GPIO);
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_WcoEnable(1000000UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_WCO_ERROR);
    }
}
#endif /* (!defined(CY_DEVICE_SECURE)) */

__STATIC_INLINE void init_cycfg_power(void)
{
    /* **Reset the Backup domain on POR, XRES, BOD only if Backup domain is supplied by VDDD** */
    #if (CY_CFG_PWR_VBACKUP_USING_VDDD)
        #ifdef CY_CFG_SYSCLK_ILO_ENABLED
            if (0u == Cy_SysLib_GetResetReason() /* POR, XRES, or BOD */)
            {
                Cy_SysLib_ResetBackupDomain();
                Cy_SysClk_IloDisable();
                Cy_SysClk_IloInit();
            }
        #endif /* CY_CFG_SYSCLK_ILO_ENABLED */
    #endif /* CY_CFG_PWR_VBACKUP_USING_VDDD */

    /* **REGHC Configuration** */
    #if (CY_CFG_PWR_REGHC_ENABLED)
        Cy_SysPm_ReghcConfigure(CY_CFG_PWR_REGHC_MODE, CY_CFG_PWR_REGHC_TRANS_VADJ_VOLT);
    #endif /* CY_CFG_PWR_REGHC_ENABLED */

     /* **System Active Low Power Profile(LPACTIVE/LPSLEEP) Configuration** */
    #if (CY_CFG_PWR_SYS_LP_PROFILE_MODE)
        Cy_SysPm_SystemLpActiveEnter();
    #endif /* CY_CFG_PWR_SYS_ACTIVE_MODE */

    /* **System Regulators Low Current Configuration** */
    #if CY_CFG_PWR_REGULATOR_MODE_MIN
        Cy_SysPm_SystemSetMinRegulatorCurrent();
    #else
        Cy_SysPm_SystemSetNormalRegulatorCurrent();
    #endif /* CY_CFG_PWR_REGULATOR_MODE_MIN */
}
void init_cycfg_system(void)
{
    Cy_SysClk_PeriPclkAssignDivider(PCLK_CPUSS_CLOCK_TRACE_IN, CY_SYSCLK_DIV_8_BIT, 3U);
        /* Set worst case memory wait states (! ultra low power, 150 MHz), will update at the end */
        Cy_SysLib_SetWaitStates(false, 150UL);
    #ifdef CY_CFG_PWR_ENABLED
        #ifdef CY_CFG_PWR_INIT
            init_cycfg_power();
        #else
            #warning Power system will not be configured. Update power personality to v1.20 or later.
        #endif /* CY_CFG_PWR_INIT */
    #endif /* CY_CFG_PWR_ENABLED */

    /* Disable FLL */
        Cy_SysClk_FllDeInit();

    #ifdef CY_CFG_SYSCLK_ILO0_ENABLED
        Cy_SysClk_Ilo0Init();
    #else
        Cy_SysClk_Ilo0DeInit();
    #endif

    #ifdef CY_CFG_SYSCLK_ILO1_ENABLED
        Cy_SysClk_Ilo1Init();
    #else
        Cy_SysClk_Ilo1DeInit();
    #endif

    /* Enable all source clocks */
    #ifdef CY_CFG_SYSCLK_PILO_ENABLED
        Cy_SysClk_PiloInit();
    #endif

    #ifdef CY_CFG_SYSCLK_WCO_ENABLED
        Cy_SysClk_WcoInit();
    #endif

    #ifdef CY_CFG_SYSCLK_ECO_ENABLED
        Cy_SysClk_EcoInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKLF_ENABLED
        Cy_SysClk_ClkLfInit();
    #endif

    #ifdef CY_CFG_SYSCLK_EXTCLK_ENABLED
        Cy_SysClk_ExtClkInit();
    #endif

    #ifdef CY_CFG_SYSCLK_ALTHF_ENABLED
        Cy_SysClk_AltHfInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKPERI_ENABLED
        Cy_SysClk_ClkPeriInit();
    #endif

    /* Configure Path Clocks */
    #ifdef CY_CFG_SYSCLK_CLKPATH1_ENABLED
        Cy_SysClk_ClkPath1Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH2_ENABLED
        Cy_SysClk_ClkPath2Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH3_ENABLED
        Cy_SysClk_ClkPath3Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH4_ENABLED
        Cy_SysClk_ClkPath4Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH5_ENABLED
        Cy_SysClk_ClkPath5Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH6_ENABLED
        Cy_SysClk_ClkPath6Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH7_ENABLED
        Cy_SysClk_ClkPath7Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH8_ENABLED
        Cy_SysClk_ClkPath8Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH9_ENABLED
        Cy_SysClk_ClkPath9Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH10_ENABLED
        Cy_SysClk_ClkPath10Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH11_ENABLED
        Cy_SysClk_ClkPath11Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH12_ENABLED
        Cy_SysClk_ClkPath12Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH13_ENABLED
        Cy_SysClk_ClkPath13Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH14_ENABLED
        Cy_SysClk_ClkPath14Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH15_ENABLED
        Cy_SysClk_ClkPath15Init();
    #endif

    /* Configure and enable PLLs */
    #ifdef CY_CFG_SYSCLK_PLL0_ENABLED
        Cy_SysClk_Pll0Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL1_ENABLED
        Cy_SysClk_Pll1Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL2_ENABLED
        Cy_SysClk_Pll2Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL3_ENABLED
        Cy_SysClk_Pll3Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL4_ENABLED
        Cy_SysClk_Pll4Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL5_ENABLED
        Cy_SysClk_Pll5Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL6_ENABLED
        Cy_SysClk_Pll6Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL7_ENABLED
        Cy_SysClk_Pll7Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL8_ENABLED
        Cy_SysClk_Pll8Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL9_ENABLED
        Cy_SysClk_Pll9Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL10_ENABLED
        Cy_SysClk_Pll10Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL11_ENABLED
        Cy_SysClk_Pll11Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL12_ENABLED
       Cy_SysClk_Pll12Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL13_ENABLED
        Cy_SysClk_Pll13Init();
    #endif
    #ifdef CY_CFG_SYSCLK_PLL14_ENABLED
        Cy_SysClk_Pll14Init();
    #endif

    /* Configure HF clocks */
    #ifdef CY_CFG_SYSCLK_CLKHF1_ENABLED
        Cy_SysClk_ClkHf1Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF2_ENABLED
        Cy_SysClk_ClkHf2Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF3_ENABLED
        Cy_SysClk_ClkHf3Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF4_ENABLED
        Cy_SysClk_ClkHf4Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF5_ENABLED
        Cy_SysClk_ClkHf5Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF6_ENABLED
        Cy_SysClk_ClkHf6Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF7_ENABLED
        Cy_SysClk_ClkHf7Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF8_ENABLED
        Cy_SysClk_ClkHf8Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF9_ENABLED
        Cy_SysClk_ClkHf9Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF10_ENABLED
        Cy_SysClk_ClkHf10Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF11_ENABLED
        Cy_SysClk_ClkHf11Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF12_ENABLED
        Cy_SysClk_ClkHf12Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF13_ENABLED
        Cy_SysClk_ClkHf13Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF14_ENABLED
        Cy_SysClk_ClkHf14Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF15_ENABLED
        Cy_SysClk_ClkHf15Init();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKALTSYSTICK_ENABLED
        Cy_SysClk_ClkAltSysTickInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKPUMP_ENABLED
        Cy_SysClk_ClkPumpInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKBAK_ENABLED
        Cy_SysClk_ClkBakInit();
    #endif

    /* Configure default enabled clocks */
    #ifdef CY_CFG_SYSCLK_ILO_ENABLED
        Cy_SysClk_IloInit();
    #endif

    #ifndef CY_CFG_SYSCLK_IMO_ENABLED
        #error the IMO must be enabled for proper chip operation
    #endif

    #ifdef CY_CFG_SYSCLK_MFO_ENABLED
        Cy_SysClk_MfoInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKMF_ENABLED
        Cy_SysClk_ClkMfInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKPWR_ENABLED
        Cy_SysClk_ClkPwrInit();
    #endif

        /* Set accurate flash wait states */
        #if (defined (CY_CFG_PWR_ENABLED) && defined (CY_CFG_SYSCLK_CLKHF1_ENABLED))
            Cy_SysLib_SetWaitStates(false, CY_CFG_SYSCLK_CLKHF1_FREQ_MHZ);
        #endif

    #ifdef CY_CFG_SYSCLK_CLKPATH0_ENABLED
        Cy_SysClk_ClkPath0Init();
    #endif
    /* Configure and enable FLL */
    #ifdef CY_CFG_SYSCLK_FLL_ENABLED
        Cy_SysClk_FllInit();
    #endif

    Cy_SysClk_ClkHf0Init();

    #ifdef CY_CFG_SYSCLK_CLKFAST_0_ENABLED
        Cy_SysClk_ClkFast_0_Init();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKFAST_1_ENABLED
        Cy_SysClk_ClkFast_1_Init();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKSLOW_ENABLED
        Cy_SysClk_ClkSlowInit();
    #endif

    #ifdef CY_CFG_SYSCLK_CLKMEM_ENABLED
        Cy_SysClk_ClkMemInit();
    #endif

#if defined(CY_CFG_SYSCLK_ECO_PRESCALER_ENABLED)
        Cy_SysClk_EcoPrescalerInit();
#endif /* defined(CY_CFG_SYSCLK_ECO_PRESCALER_ENABLED) */
    #ifdef CY_CFG_SYSCLK_CLKALTSYSTICK_ENABLED
        Cy_SysClk_ClkAltSysTickInit();
    #endif

    /* Update System Core Clock values for correct Cy_SysLib_Delay functioning */
    SystemCoreClockUpdate();
#if defined (CY_USING_HAL)
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_0_obj);
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_1_obj);
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_2_obj);
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_3_obj);
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_4_obj);
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_5_obj);
    (void)cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_6_obj);
#endif /* defined (CY_USING_HAL) */
}
void reserve_cycfg_system(void)
{
    Cy_SysClk_EcoSetFrequency(CY_CFG_SYSCLK_ECO_FREQ);
    SystemCoreClockUpdate();
}
