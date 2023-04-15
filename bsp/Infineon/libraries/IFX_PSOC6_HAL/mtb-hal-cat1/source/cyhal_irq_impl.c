/***************************************************************************//**
* \file cyhal_irq_impl.c
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

#include "cyhal_irq_impl.h"

/**
 * \addtogroup group_hal_impl_irq IRQ Muxing (Interrupt muxing)
 * \ingroup group_hal_impl
 * \{
 * There are two situations where system interrupts do not correlate 1:1 to CPU interrupts.
 * ("System interrupt" refers to a signal on a peripheral that can request an interrupt.
 * "CPU interrupt" refers to an IRQ input line on the cpu). Each has a different potential
 * impact on application behavior.
 * - When running on the CM0+ on PSoC 6 S1 devices, there are 32 CPU interrupts available.
 *   Each CPU interrupt can be associatedd with exactly one system interrupt. This means that
 *   if the application attempts to initialize more than 32 HAL driver instances which require
 *   unique interrupt handlers, the initialization will fail because there are no CPU interrupt
 *   slots remaining.
 * - When running on the CM0+ on all other CAT1 devices, or when running on the CM7 on CAT3 devices,
 *   there are 8 CPU interrupts. Any system interrupt can be assigned to any CPU interrupt. In the event
 *   that more than one system interrupt fires at the same time for a given CPU interrupt, the interrupts
 *   are serviced in ascending numerical order (see the device datasheet for numeric IRQ values). This
 *   means that the above error case where all CPU interrupts have been consumed does not apply. The HAL
 *   automatically divides the system interrupts across the CPU interrupts.
 *   However, it is only possible to assign one priority per CPU interrupt, even though the HAL APIs expose
 *   the interrupt priority per system interrupt. The CAT1 HAL handles this situation by tracking the requested
 *   priority for each system interrupt, then setting the priority for each CPU interrupt as the lowest
 *   (i.e. most important) value requested across all of its associated system interrupts.
 * \}
 */

#if _CYHAL_IRQ_LEGACY_M0
#include "cyhal_hwmgr.h"

static const uint8_t _CYHAL_IRQ_COUNT_M0 = 32; /* Fixed in the IP definition */
#elif _CYHAL_IRQ_MUXING
#if defined (COMPONENT_CAT1A)
#include "cyhal_hwmgr.h" // TODO: This is a temporary workaround to assign 1:1 CPU to system mapping.
#endif

static uint8_t _cyhal_system_irq_priority[((_CYHAL_IRQ_PRIO_BITS * _CYHAL_IRQ_COUNT) + 7) / 8]; /* Round up to nearest byte */

uint8_t _cyhal_system_irq_lookup_priority(cy_en_intr_t system_irq)
{
    uint16_t start_bit = ((uint16_t)system_irq) * _CYHAL_IRQ_PRIO_BITS;
    uint8_t result = 0u;
    for(uint16_t bit = start_bit; bit < start_bit + _CYHAL_IRQ_PRIO_BITS; ++bit)
    {
        uint16_t byte = bit / 8u;
        uint8_t bit_in_byte = bit % 8u;
        uint8_t offset = bit - start_bit;
        uint8_t bit_value = ((_cyhal_system_irq_priority[byte] >> bit_in_byte) & 1u);
        result |= (bit_value << offset);
    }

    return result;
}

void _cyhal_system_irq_store_priority(cy_en_intr_t system_irq, uint8_t priority)
{
    uint16_t start_bit = ((uint16_t)system_irq) * _CYHAL_IRQ_PRIO_BITS;
    for(uint16_t bit = start_bit; bit < start_bit + _CYHAL_IRQ_PRIO_BITS; ++bit)
    {
        uint16_t byte = bit / 8u;
        uint8_t bit_in_byte = bit % 8u;
        uint8_t offset = bit - start_bit;
        uint8_t bit_value = priority & (1u << offset);
        if(0u != bit_value)
        {
            _cyhal_system_irq_priority[byte] |= (1u << bit_in_byte);
        }
        else
        {
            _cyhal_system_irq_priority[byte] &= ~(1u << bit_in_byte);
        }
    }
}

uint8_t _cyhal_system_irq_lowest_priority(IRQn_Type cpu_irq)
{
    uint8_t lowest_priority = 0xFF;
    for(uint32_t i = 0; i < _CYHAL_IRQ_COUNT; ++i)
    {
        /* No reverse mapping from CPU interrupt to system interrupt, we have to look
         * through all of the system interrupts to see which ones correspond to this one */
        if(cpu_irq == Cy_SysInt_GetNvicConnection((cy_en_intr_t)i))
        {
            uint8_t priority = _cyhal_system_irq_lookup_priority((cy_en_intr_t)i);
            if(priority < lowest_priority)
            {
                lowest_priority = priority;
            }
        }
    }

    return lowest_priority;
}

#endif

#if (_CYHAL_IRQ_MUXING) && defined (COMPONENT_CAT1A) && (!_CYHAL_IRQ_LEGACY_M0)
uint8_t _cpu_irq_tracker = 0u; // TODO: This is a temporary workaround to assign 1:1 CPU to system mapping.
#endif

cy_rslt_t _cyhal_irq_register(_cyhal_system_irq_t system_intr, uint8_t intr_priority, cy_israddress irq_handler)
{
#if _CYHAL_IRQ_MUXING
    #if _CYHAL_IRQ_LEGACY_M0
        /* Find a free CM0 slot */
        IRQn_Type chosen_irq = unconnected_IRQn;
        bool deepsleep_irq = (uint16_t)system_intr < CPUSS_DPSLP_IRQ_NR;
        uint8_t max_cm0_irq = deepsleep_irq ? CPUSS_CM0_DPSLP_IRQ_NR : _CYHAL_IRQ_COUNT_M0;
        for(int i = 0; i < max_cm0_irq; ++i)
        {
            IRQn_Type irqn = (IRQn_Type)i;
            if(disconnected_IRQn == Cy_SysInt_GetInterruptSource(irqn))
            {
                chosen_irq = irqn;
                break;
            }
        }
        if(unconnected_IRQn == chosen_irq)
        {
            /* This is a highly device specific situation. "None free" is the closest matching generic error */
            return CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
        }
        cy_stc_sysint_t intr_cfg = { chosen_irq, system_intr, intr_priority };
    #else /* CM0+ on CPUSSv2, or CM4/CM7 on CPUSSv2 with SYSTEM_IRQ_PRESENT */
        /* Any system interrupt can go to any CPU interrupt. Map the system interrupts evenly across the CPU interrupts. Cluster
         * adjacent system interrupts together to make it more likely that interrupts from the same FFB type, which are reasonably
         * likely to want similar priorities. */
        #if defined(CY_IP_M4CPUSS)
        const uint8_t NUM_CPU_INTERRUPTS = 8u; /* Value fixed in the IP */
        #else /* M7CPUSS */
        #if defined(CY_CPU_CORTEX_M0P)
        /* There are 8 general purpose interrupts on the CM0+, but per comments in Cy_SysInt_Init, the first two
         * CPU interrupts  are reserved for ROM */
        const uint8_t NUM_CPU_INTERRUPTS = 6u;
        #else
        const uint8_t NUM_CPU_INTERRUPTS = CPUSS_CM7_INT_NR;
        #endif
        #endif
        // TODO: This is a temporary workaround to assign 1:1 CPU to system mapping.
        // When the PDL allows more than one mapping, remove this logic.
        #if defined (COMPONENT_CAT1A)
        cy_rslt_t status = CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
        uint8_t cpu_irq;
        for (int idx = 0; idx < NUM_CPU_INTERRUPTS; idx++)
        {
            if ((_cpu_irq_tracker & (1 << idx)) == 0)
            {
                cpu_irq = idx;
                _cpu_irq_tracker |= (1 << idx);
                status = CY_RSLT_SUCCESS;
                break;
            }
        }
        if (status != CY_RSLT_SUCCESS)
        {
            return status;
        }
        #else
        const uint8_t SYSTEM_IRQ_PER_CPU_IRQ = (_CYHAL_IRQ_COUNT + (NUM_CPU_INTERRUPTS / 2)) / NUM_CPU_INTERRUPTS;
        uint8_t cpu_irq = ((uint32_t)system_intr) / SYSTEM_IRQ_PER_CPU_IRQ;
        #endif
        #if defined (CY_IP_M7CPUSS)
        #if defined(CY_CPU_CORTEX_M0P)
        cpu_irq += 2u; /* Handle offset from interrupts reserved for ROM */
        #endif
        /* For CM7, the upper 16 bits of the intrSrc field are the CPU interrupt number */
        uint32_t intr_src = (uint32_t)system_intr;
        intr_src |= cpu_irq << 16;
        _cyhal_system_irq_store_priority(system_intr, intr_priority);
        /* We can avoid a "lowest priority" search here, because the currently set value is the lowest except
         * possibly for the one we're just now registering */
        uint8_t existing_priority = NVIC_GetPriority((IRQn_Type)cpu_irq);
        uint8_t lowest_priority = (existing_priority < intr_priority) ? existing_priority : intr_priority;
        cy_stc_sysint_t intr_cfg = { intr_src, lowest_priority };
        #else /* M4CPUSS */
        cy_stc_sysint_t intr_cfg = { (IRQn_Type)cpu_irq, system_intr, intr_priority };
        #endif
    #endif
#else
    cy_stc_sysint_t intr_cfg = { system_intr, intr_priority };
#endif
    return Cy_SysInt_Init(&intr_cfg, irq_handler);
}

#if _CYHAL_IRQ_LEGACY_M0
IRQn_Type _cyhal_irq_find_cm0(cy_en_intr_t system_irq)
{
    /* Need to look through all of the enabled CPU interrupts and see if any of them
     * is connected to this IRQn */
    for(int i = 0; i < _CYHAL_IRQ_COUNT_M0; ++i)
    {
        IRQn_Type irqn = (IRQn_Type)i;
        if(system_irq == Cy_SysInt_GetInterruptSource(irqn))
        {
            return irqn;
        }
    }

    return unconnected_IRQn;
}
#endif
