/***************************************************************************//**
* \file cyhal_irq_impl.h
*
* \brief
* Provides internal utility functions for working with interrupts on CAT1/CAT2.
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
#include "cyhal_utils.h"
#include "cy_result.h"
#include "cy_sysint.h"

/* System IRQ refers to signals that peripherals produce to request and interrupt,
 * which may or may not correspond 1:1 to the CPU IRQ lines */
#if defined(COMPONENT_CAT1)
#define _CYHAL_IRQ_MUXING (CY_CPU_CORTEX_M0P || CPUSS_SYSTEM_IRQ_PRESENT)
#else
#define _CYHAL_IRQ_MUXING (0)
#endif
/* Old-style IRQ muxing where each CPU interrupt can be driven by exactly one System interrupt.
 * This is a subset of _CYHAL_IRQ_MUXING. */
#define _CYHAL_IRQ_LEGACY_M0 (CY_CPU_CORTEX_M0P && (1u == CY_IP_M4CPUSS_VERSION))

#if !(_CYHAL_IRQ_LEGACY_M0)
/* Interrupt priority is set per CPU interrupt, but application-defined priorities are set
 * in terms of system interrupts. So keep track of the IRQ per system interrupt and
 * set the CPU interrupt priority to the lowest (i.e. most important) value of any
 * system interrupt that is connected to it */
#if (CY_CPU_CORTEX_M0P)
    #define _CYHAL_IRQ_PRIO_BITS (3u)
#elif defined(CY_IP_M4CPUSS)
    #define _CYHAL_IRQ_PRIO_BITS (CPUSS_CM4_LVL_WIDTH)
#else /* M7CPUSS */
    #define _CYHAL_IRQ_PRIO_BITS (CPUSS_CM7_LVL_WIDTH)
#endif

#if defined(CY_IP_M4CPUSS)
    #define _CYHAL_IRQ_COUNT    (CPUSS_IRQ_NR)
#else /* M7CPUSS */
    #define _CYHAL_IRQ_COUNT    (CPUSS_SYSTEM_INT_NR)
#endif

#endif // !(_CYHAL_IRQ_LEGACY_M0)

#if (_CYHAL_IRQ_MUXING)
typedef cy_en_intr_t _cyhal_system_irq_t;
#else
typedef IRQn_Type    _cyhal_system_irq_t;
#endif

#if _CYHAL_IRQ_LEGACY_M0
IRQn_Type _cyhal_irq_find_cm0(cy_en_intr_t system_intr);
#elif _CYHAL_IRQ_MUXING
uint8_t _cyhal_system_irq_lookup_priority(cy_en_intr_t system_irq);
void _cyhal_system_irq_store_priority(cy_en_intr_t system_irq, uint8_t priority);
uint8_t _cyhal_system_irq_lowest_priority(IRQn_Type cpu_irq);
#endif

void _cyhal_system_irq_clear_disabled_in_pending(void);
cy_rslt_t _cyhal_irq_register(_cyhal_system_irq_t system_intr, uint8_t intr_priority, cy_israddress irq_handler);

// TODO: Remove this once DRIVERS-7707 is fixed
#if defined(CY_IP_M4CPUSS) && (CY_CPU_CORTEX_M0P) && !(_CYHAL_IRQ_LEGACY_M0)
static void Cy_SysInt_EnableSystemInt(cy_en_intr_t sysIntSrc)
{
    #if defined(CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk)
    CPUSS_CM0_SYSTEM_INT_CTL[sysIntSrc] |= CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk;
    #else
    CPUSS_CM0_SYSTEM_INT_CTL[sysIntSrc] |= CPUSS_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk;
    #endif
}

static void Cy_SysInt_DisableSystemInt(cy_en_intr_t sysIntSrc)
{
    #if defined(CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk)
    CPUSS->CM0_SYSTEM_INT_CTL[sysIntSrc] &= (uint32_t) ~CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk;
    #else
    CPUSS->CM0_SYSTEM_INT_CTL[sysIntSrc] &= (uint32_t) ~CPUSS_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk;
    #endif
}
#endif

static inline void _cyhal_irq_set_priority(_cyhal_system_irq_t system_irq, uint8_t intr_priority)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    uint8_t priority_to_set = intr_priority;
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
    IRQn_Type irqn = Cy_SysInt_GetNvicConnection(system_irq);
    _cyhal_system_irq_store_priority(system_irq, intr_priority);
    uint8_t priority_to_set = _cyhal_system_irq_lowest_priority(irqn);
    #endif
#else
    IRQn_Type irqn = system_irq;
    uint8_t priority_to_set = intr_priority;
#endif
    NVIC_SetPriority(irqn, priority_to_set);
}

static inline uint8_t _cyhal_irq_get_priority(_cyhal_system_irq_t system_irq)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    return NVIC_GetPriority(irqn);
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
    return _cyhal_system_irq_lookup_priority(system_irq);
    #endif
#else
    return NVIC_GetPriority(system_irq);
#endif
}

static inline void _cyhal_irq_clear_pending(_cyhal_system_irq_t system_irq)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
    IRQn_Type irqn = Cy_SysInt_GetNvicConnection(system_irq);
    #endif
#else
    IRQn_Type irqn = system_irq;
#endif
    NVIC_ClearPendingIRQ(irqn);
}

static inline void _cyhal_irq_enable(_cyhal_system_irq_t system_irq)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
    Cy_SysInt_EnableSystemInt(system_irq);
    IRQn_Type irqn = Cy_SysInt_GetNvicConnection(system_irq);
    #endif
#else
    IRQn_Type irqn = system_irq;
#endif
    NVIC_EnableIRQ(irqn);
}

static inline void _cyhal_irq_disable(_cyhal_system_irq_t system_irq)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    NVIC_DisableIRQ(irqn);
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
    Cy_SysInt_DisableSystemInt(system_irq);
    /* Don't call NVIC_DisableIRQ because there could be other system interrupts still using this IRQn */
    #endif
#else
    NVIC_DisableIRQ(system_irq);
#endif
}

#if (_CYHAL_IRQ_MUXING) && defined (COMPONENT_CAT1A) && (!_CYHAL_IRQ_LEGACY_M0)
extern uint8_t _cpu_irq_tracker; // TODO: This is a temporary workaround to assign 1:1 CPU to system mapping.
#endif

static inline void _cyhal_irq_free(_cyhal_system_irq_t system_irq)
{
    #if _CYHAL_IRQ_LEGACY_M0
    /* Need to turn the IRQ off and also clear out the NVIC slot so that we
     * know it's available for other drivers to use */
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    NVIC_DisableIRQ(irqn); /* Don't reuse irq_disable because it would have to repeat the find_cm0 */
    Cy_SysInt_DisconnectInterruptSource(irqn, system_irq /* ignored for CPUSSv1 */);
    #elif _CYHAL_IRQ_MUXING /* New style IRQ muxing */
    /* DisconnectInterruptSource on M4CPUSS and DisableSystemInt on M7CPUSS are functionally equivalent */
    IRQn_Type irqn = Cy_SysInt_GetNvicConnection(system_irq);
    // TODO: This is a temporary workaround to assign 1:1 CPU to system mapping.
    #if defined (COMPONENT_CAT1A)
    _cpu_irq_tracker &= ~(1 << irqn);
    #endif
    #if defined(CY_IP_M4CPUSS)
    Cy_SysInt_DisconnectInterruptSource(irqn, system_irq);
    #elif defined(CY_IP_M7CPUSS)
    Cy_SysInt_DisableSystemInt(system_irq);
    #endif

    /* Must happen after the interrupt source is disabled because we use GetNvicConnection to determine
     * what system interrupts are actively associated with a given CPU interrupt */
    uint8_t lowest_priority = _cyhal_system_irq_lowest_priority(irqn);
    NVIC_SetPriority(irqn, lowest_priority);
    #endif

    _cyhal_irq_disable(system_irq);
}

static inline bool _cyhal_irq_is_enabled(_cyhal_system_irq_t system_irq)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    IRQn_Type irqn = _cyhal_irq_find_cm0(system_irq);
    return (unconnected_IRQn != irqn) && NVIC_GetEnableIRQ(irqn);
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
        /* Based on Cy_SysInt_EnableSystemInt */
        if (CY_CPU_CORTEX_M0P)
        {
            #if defined(CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk)
            return (0u != (CPUSS_CM0_SYSTEM_INT_CTL[system_irq] & CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk));
            #else
            return (0u != (CPUSS_CM0_SYSTEM_INT_CTL[system_irq] & CPUSS_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk));
            #endif
        }
#if defined(CY_IP_M7CPUSS)
        else if (CY_IS_CM7_CORE_0)
        {
            return (0u != (CPUSS_CM7_0_SYSTEM_INT_CTL[system_irq] & CPUSS_CM7_0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk));
        }
        else if (CY_IS_CM7_CORE_1)
        {
            return (0u != (CPUSS_CM7_1_SYSTEM_INT_CTL[system_irq] & CPUSS_CM7_1_SYSTEM_INT_CTL_CPU_INT_VALID_Msk));
        }
#endif
        else
        {
            CY_ASSERT(false); /* Unsupported CPU */
            return false;
        }
    #endif
#else
    return NVIC_GetEnableIRQ(system_irq);
#endif
}

static inline _cyhal_system_irq_t _cyhal_irq_get_active(void)
{
    IRQn_Type irqn = _CYHAL_UTILS_GET_CURRENT_IRQN();
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
    /* No pre-built functionality for this. Need to see what CPU interrupt is active, then
     * indirect through the NVIC mux to figure out what system IRQ it is mapped to. */
    return Cy_SysInt_GetInterruptSource(irqn);
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
    return Cy_SysInt_GetInterruptActive(irqn);
    #endif
#else
    return irqn;
#endif
}
