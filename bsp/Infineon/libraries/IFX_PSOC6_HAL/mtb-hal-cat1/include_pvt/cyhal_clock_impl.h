/*******************************************************************************
* File Name: cyhal_clock_impl.h
*
* Description:
* CAT1 specific implementation for clocks API.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
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
*******************************************************************************/

#pragma once

#include "cyhal_hw_resources.h"

#if (CYHAL_DRIVER_AVAILABLE_CLOCK)

#if defined(__cplusplus)
extern "C"
{
#endif

#if !defined(SRSS_NUM_PLL)

#if defined(COMPONENT_CAT1D)
#define SRSS_NUM_PLL SRSS_NUM_TOTAL_DPLL
#elif defined(COMPONENT_CAT1B)
#define SRSS_NUM_PLL (SRSS_NUM_PLL200M + SRSS_NUM_PLL400M)
#endif

#endif /* !defined(SRSS_NUM_PLL) */

#if defined(COMPONENT_CAT1C)
#define _CYHAL_SRSS_NUM_PLL (SRSS_NUM_PLL + SRSS_NUM_PLL400M)
#else
#define _CYHAL_SRSS_NUM_PLL SRSS_NUM_PLL
#endif /* defined(COMPONENT_CAT1C) or other */

/**
 * \addtogroup group_hal_impl_clock Clocks
 * \ingroup group_hal_impl
 * \{
 * Implementation specific interface for using the Clock driver. These items, while usable
 * within the HAL, are <b>not</b> necessarily portable between devices. The diagrams below
 * show how the clocks relate to each other. This is a superset of what is available. See
 * the device specific Data Sheet for the exact set of clocks that are available on a
 * specific device.
 * \section section_clock_snippets_impl Code snippets
 * \note Error handling code has been intentionally left out of snippets to highlight API usage.
 *
 * \subsection subsection_clock_snippet_5_impl Snippet: System initialization
 * The following snippet shows the clock driver can be used to initialize all clocks in the system.
 * \note This example is device specific.
 * \snippet hal_clock.c snippet_cyhal_clock_system_init_p6
 * \addtogroup group_hal_impl_clock_psoc6_01 PSoC™ 6S1 Clocks
 * \{
 * <b>PSoC™ 6S1 Clock Tree:</b>
 * \image html psoc6able2_clock_tree.png
 * \}
 * \addtogroup group_hal_impl_clock_psoc6_02 PSoC™ 6S2 Clocks
 * \{
 * <b>PSoC™ 6S2 Clock Tree:</b>
 * \image html psoc6a2m_clock_tree.png
 * \}
 * \addtogroup group_hal_impl_clock_psoc6_03 PSoC™ 6S3 Clocks
 * \{
 * <b>PSoC™ 6S3 Clock Tree:</b>
 * \image html psoc6a512k_clock_tree.png
 * \}
 * \addtogroup group_hal_impl_clock_psoc6_04 PSoC™ 6S4 Clocks
 * \{
 * <b>PSoC™ 6S4 Clock Tree:</b>
 * \image html psoc6a256k_clock_tree.png
 * \}
 * \addtogroup group_hal_impl_clock_xmc7100 XMC7100/T2G-B-H-4M Clocks
 * \{
 * <b>XMC7100/T2G-B-H-4M Clock Tree:</b>
 * \image html xmc7100_clock_tree.png
 * \}
 * \addtogroup group_hal_impl_clock_xmc7200 XMC7200/T2G-B-H-8M Clocks
  * \{
 * <b>XMC7200/T2G-B-H-8M Clock Tree:</b>
 * \image html xmc7200_clock_tree.png
 * \}
 */

/** \cond INTERNAL */
#define SRSS_MFO_PRESENT    (SRSS_VER1P3)
/** \endcond */

/** Internal Main Oscillator: This is a fixed-frequency clock that is commonly used as a general purpose source for clocks that do not require specific frequencies or very high accuracy. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_IMO;
/** Internal Main Oscillator: This is a fixed-frequency clock that is commonly used as a general purpose source for clocks that do not require specific frequencies or very high accuracy. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_IMO;

/** External Clock: This is an off-chip clock (not an oscillator). This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_EXT;
/** External Clock: This is an off-chip clock (not an oscillator). This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_EXT;

#if defined(COMPONENT_CAT1C)
/*!< CLK MEM */
extern const cyhal_clock_t CYHAL_CLOCK_MEM;
/*!< CLK MEM */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_MEM;
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
/** Internal Low Speed Oscillator: This is a low accuracy fixed-frequency clock in the kilohertz range that is available in sleep, deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_ILO;
/** Internal Low Speed Oscillator: This is a low accuracy fixed-frequency clock in the kilohertz range that is available in sleep, deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ILO;
#elif defined(COMPONENT_CAT1C)
/** Internal Low Speed Oscillator: This is a low accuracy fixed-frequency clock in the kilohertz range that is available in sleep, deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_ILO[_CYHAL_SRSS_NUM_ILO];
/** Internal Low Speed Oscillator: This is a low accuracy fixed-frequency clock in the kilohertz range that is available in sleep, deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ILO[_CYHAL_SRSS_NUM_ILO];
#endif

#if SRSS_ECO_PRESENT
/** External Crystal Oscillator: This is an off-chip clock source that is used when specific frequencies and/or very high accuracy is required. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_ECO;
/** External Crystal Oscillator: This is an off-chip clock source that is used when specific frequencies and/or very high accuracy is required. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ECO;
#endif
#if SRSS_ALTHF_PRESENT
/** Alternate High Frequency Clock: A high speed clock input provided by a subsystem outside the clocking system. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_ALTHF;
/** Alternate High Frequency Clock: A high speed clock input provided by a subsystem outside the clocking system. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ALTHF;
#endif
#if SRSS_ALTLF_PRESENT
/** Alternate Low Frequency Clock: A low speed clock input provided by a subsystem outside the clocking system. This clock is the hibernate power mode. */
extern const cyhal_clock_t CYHAL_CLOCK_ALTLF;
/** Alternate Low Frequency Clock: A low speed clock input provided by a subsystem outside the clocking system. This clock is the hibernate power mode. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ALTLF;
#endif
#if SRSS_PILO_PRESENT
/** Precision ILO: An additional source that can provide a much more accurate 32.768kHz clock than ILO when periodically calibrated using a high-accuracy clock such as the ECO. This clock is stopped in the hibernate power mode. */
extern const cyhal_clock_t CYHAL_CLOCK_PILO;
/** Precision ILO: An additional source that can provide a much more accurate 32.768kHz clock than ILO when periodically calibrated using a high-accuracy clock such as the ECO. This clock is stopped in the hibernate power mode. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PILO;
#endif
#if SRSS_BACKUP_PRESENT
/** Watch Crystal Oscillator: This source is driven from an off-chip watch crystal that provides an extremely accurate source. This clock is stopped in the hibernate power mode. */
extern const cyhal_clock_t CYHAL_CLOCK_WCO;
/** Watch Crystal Oscillator: This source is driven from an off-chip watch crystal that provides an extremely accurate source. This clock is stopped in the hibernate power mode. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_WCO;
#endif
#if SRSS_S40E_LPECO_PRESENT
/** Low Power External Crystal Oscillator: This source is driven from an off-chip external crystal that provides an extremely accurate source. This clock is stopped in the hibernate power mode. */
extern const cyhal_clock_t CYHAL_CLOCK_LPECO_PRESCALER;
/** Low Power External Crystal Oscillator: This source is driven from an off-chip external crystal that provides an extremely accurate source. This clock is stopped in the hibernate power mode. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_LPECO_PRESCALER;
#endif
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
/** Medium Frequency Oscillator: This source produced by dividing the IMO by 4. The MFO works down to DeepSleep, and the IMO does not turn off if this clock requires it. */
extern const cyhal_clock_t CYHAL_CLOCK_MFO;
/** Medium Frequency Oscillator: This source produced by dividing the IMO by 4. The MFO works down to DeepSleep, and the IMO does not turn off if this clock requires it. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_MFO;

/** Medium Frequency Clock: This clock is a medium frequency, between the Low Frequency Clock (LF) and High Frequency Clock (HF). */
extern const cyhal_clock_t CYHAL_CLOCK_MF;
/** Medium Frequency Clock: This clock is a medium frequency, between the Low Frequency Clock (LF) and High Frequency Clock (HF). */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_MF;
#endif

/** Low Frequency Clock: This clock is the source for the multi-counter watchdog timers (MCWDT), and can also be a source for the RTC. */
extern const cyhal_clock_t CYHAL_CLOCK_LF;
/** Low Frequency Clock: This clock is the source for the multi-counter watchdog timers (MCWDT), and can also be a source for the RTC. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_LF;

/* PUMP clock is only available on CAT1A and CAT1B devices */
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
/** Analog Pump Clock: This clock ensures precision analog performance in low voltage applications. */
extern const cyhal_clock_t CYHAL_CLOCK_PUMP;
/** Analog Pump Clock: This clock ensures precision analog performance in low voltage applications. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PUMP;
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */

/** Backup Clock: This clock is available to the backup domain. Typically useful if an external WCO is not available. */
extern const cyhal_clock_t CYHAL_CLOCK_BAK;
/** Backup Clock: This clock is available to the backup domain. Typically useful if an external WCO is not available. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_BAK;

/** AltSysTickClk: Provides an optional external source for the CM4/CM0+ SysTick timers. */
extern const cyhal_clock_t CYHAL_CLOCK_ALT_SYS_TICK;
/** AltSysTickClk: Provides an optional external source for the CM4/CM0+ SysTick timers. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ALT_SYS_TICK;

#if (SRSS_NUM_CLKPATH > 0)
/** Path mux selection: A clock source for high frequency clocks. */
extern const cyhal_clock_t CYHAL_CLOCK_PATHMUX[SRSS_NUM_CLKPATH];
/** Path mux selection: A clock source for high frequency clocks. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PATHMUX[SRSS_NUM_CLKPATH];
#endif

#if defined(COMPONENT_CAT1A)
/** Fast Clock: This clock is used for the CM4 and associated AHB-Lite bus infrastructure. */
extern const cyhal_clock_t CYHAL_CLOCK_FAST;
/** Fast Clock: This clock is used for the CM4 and associated AHB-Lite bus infrastructure. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_FAST;

/** Peripheral Clock: This is the source clock for any divided clock in the design. */
extern const cyhal_clock_t CYHAL_CLOCK_PERI;
/** Peripheral Clock: This is the source clock for any divided clock in the design. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PERI;
#endif

#if defined(COMPONENT_CAT1C)
/** Fast Clock: This clock is used for the CM4 and associated AHB-Lite bus infrastructure. */
extern const cyhal_clock_t CYHAL_CLOCK_FAST[_CYHAL_SRSS_NUM_FAST];
/** Fast Clock: This clock is used for the CM4 and associated AHB-Lite bus infrastructure. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_FAST[_CYHAL_SRSS_NUM_FAST];

#endif

#if defined(COMPONENT_CAT1A)
/** Timer Clock: This clock is intended as a source for high-frequency timers, such as the Energy Profiler and CPU SysTick clock. This clock is stopped in the hibernate power mode. */
extern const cyhal_clock_t CYHAL_CLOCK_TIMER;
/** Timer Clock: This clock is intended as a source for high-frequency timers, such as the Energy Profiler and CPU SysTick clock. This clock is stopped in the hibernate power mode. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_TIMER;
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
/** Slow Clock: This clock is used for the CM0+ CPU, Datawire and CRYPTO components and the associated CPUSS slow infrastructure. */
extern const cyhal_clock_t CYHAL_CLOCK_SLOW;
/** Slow Clock: This clock is used for the CM0+ CPU, Datawire and CRYPTO components and the associated CPUSS slow infrastructure. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_SLOW;
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
/** Internal High-Speed Oscillator: This is a fixed-frequency clock that is commonly used as a general purpose source for clocks that do not require specific frequencies or very high accuracy. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_IHO;
/** Internal High-Speed Oscillator: This is a fixed-frequency clock that is commonly used as a general purpose source for clocks that do not require specific frequencies or very high accuracy. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_IHO;
#endif

/** Peripheral Clock: This is the source clock for any divided clock in the design. */
extern const cyhal_clock_t CYHAL_CLOCK_PERI[CY_PERI_GROUP_NR];
/** Peripheral Clock: This is the source clock for any divided clock in the design. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PERI[CY_PERI_GROUP_NR];
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
/** Frequency-Locked Loop: This is a high-frequency clock suitable for most on-chip purposes.  It is similar to a PLL, but starts up much faster and consumes less current. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_FLL;
/** Frequency-Locked Loop: This is a high-frequency clock suitable for most on-chip purposes.  It is similar to a PLL, but starts up much faster and consumes less current. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_FLL;
#endif

#if (_CYHAL_SRSS_NUM_PLL > 0) && defined(COMPONENT_CAT1A)
/** Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_PLL[_CYHAL_SRSS_NUM_PLL];
/** Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL[_CYHAL_SRSS_NUM_PLL];
#endif
#if (SRSS_NUM_PLL > 0) && defined(COMPONENT_CAT1C)
/** 200MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_PLL200[SRSS_NUM_PLL200M];
/** 200MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL200M[SRSS_NUM_PLL200M];
#endif
#if (SRSS_NUM_PLL400M > 0) && defined(COMPONENT_CAT1C)
/** 400MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_PLL400[SRSS_NUM_PLL400M];
/** 400MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL400M[SRSS_NUM_PLL400M];
#endif

#if (SRSS_NUM_PLL200M > 0) && defined(COMPONENT_CAT1B)
/** 200MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_PLL[SRSS_NUM_PLL200M];
/** 200MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL[SRSS_NUM_PLL200M];
#endif
#if (SRSS_NUM_PLL400M > 0) && defined(COMPONENT_CAT1B)
/** 400MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_PLL[SRSS_NUM_PLL400M];
/** 400MHz Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL[SRSS_NUM_PLL400M];
#endif

#if (SRSS_NUM_DPLL_LP > 0) && defined(COMPONENT_CAT1D)
/** 250MHz Digital Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_DPLL_LP[SRSS_NUM_DPLL_LP];
/** 250MHz Digital Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_DPLL_LP[SRSS_NUM_DPLL_LP];
#endif
#if (SRSS_NUM_DPLL_HP > 0) && defined(COMPONENT_CAT1D)
/** 500MHz Digital Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_clock_t CYHAL_CLOCK_DPLL_HP[SRSS_NUM_DPLL_HP];
/** 500MHz Digital Phase-Locked Loop: A high-frequency clock able to generate a wide range of clock frequencies making it suitable for most on-chip purposes. This clock is stopped in the deep sleep and hibernate power modes. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_DPLL_HP[SRSS_NUM_DPLL_HP];
#endif

/** High Frequency Clock: A high-frequency clock output driving specific peripherals. */
extern const cyhal_clock_t CYHAL_CLOCK_HF[SRSS_NUM_HFROOT];
/** High Frequency Clock: A high-frequency clock output driving specific peripherals. */
extern const cyhal_resource_inst_t CYHAL_CLOCK_RSC_HF[SRSS_NUM_HFROOT];

/** \} group_hal_impl_clock */

cy_rslt_t _cyhal_clock_allocate_channel(cyhal_clock_t *clock, cyhal_clock_block_t block, const void* funcs);

const void* _cyhal_clock_get_funcs_pathmux(void);
#if (_CYHAL_SRSS_NUM_PLL > 0)
const void* _cyhal_clock_get_funcs_pll(void);
#endif
const void* _cyhal_clock_get_funcs_hf(void);
const void* _cyhal_clock_get_funcs_peripheral(void);


static inline const void* _cyhal_clock_get_funcs(cyhal_clock_block_t block)
{
    switch (block)
    {
        case CYHAL_CLOCK_BLOCK_PATHMUX:
            return _cyhal_clock_get_funcs_pathmux();
#if (_CYHAL_SRSS_NUM_PLL > 0)
        #if defined(COMPONENT_CAT1C)
        case CYHAL_CLOCK_BLOCK_PLL200:
        case CYHAL_CLOCK_BLOCK_PLL400:
        #elif defined(COMPONENT_CAT1D)
        case CYHAL_CLOCK_BLOCK_DPLL_LP:
        case CYHAL_CLOCK_BLOCK_DPLL_HP:
        #else
        case CYHAL_CLOCK_BLOCK_PLL:
        #endif
            return _cyhal_clock_get_funcs_pll();
#endif
        case CYHAL_CLOCK_BLOCK_HF:
            return _cyhal_clock_get_funcs_hf();
        default:
            return (block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
                ? _cyhal_clock_get_funcs_peripheral()
                : NULL;
    }
}
static inline cy_rslt_t _cyhal_clock_allocate(cyhal_clock_t *clock, cyhal_clock_block_t block)
{
    CY_ASSERT(NULL != clock);

    const void* funcs = _cyhal_clock_get_funcs(block);
    return (NULL == funcs)
        ? CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED
        : _cyhal_clock_allocate_channel(clock, block, funcs);
}
static inline cy_rslt_t _cyhal_clock_allocate_peri(cyhal_clock_t *clock, cyhal_clock_block_t block)
{
    CY_ASSERT(NULL != clock);

    const void* funcs = _cyhal_clock_get_funcs_peripheral();
    return _cyhal_clock_allocate_channel(clock, block, funcs);
}

#define cyhal_clock_allocate(clock, block)  _cyhal_clock_allocate(clock, block)

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_CLOCK
