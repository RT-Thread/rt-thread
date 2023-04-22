/***************************************************************************//**
* \file cyhal_lptimer.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Low-Power Timer.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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

/**
* \addtogroup group_hal_impl_lptimer LPTimer (Low-Power Timer)
* \ingroup group_hal_impl
* \{
* The maximum number of ticks that can set to an LPTimer is 0xFFF0FFFF for non CAT1C devices.
* It is not recommended to use 0xFFFFFFFF. This is to avoid overflowing both C0 and C1.
* For CAT1C devices (XMC), the maximum number of ticks that can be set to an LPTimer is 0xFFFFFFFF
* since C0 and C1 do not cascade.
*
* \section section_cat1c_lptimer_set_match LPTimer Set Match
* For CAT1C devices (XMC), \ref cyhal_lptimer_set_match will only trigger a single interrupt.
*
* \} group_hal_impl_lptimer
*/

#include "cmsis_compiler.h"
#include "cy_syslib.h"
#include "cy_sysint.h"
#include "cyhal_lptimer.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system_impl.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_clock.h"

#if (CYHAL_DRIVER_AVAILABLE_LPTIMER)

#if defined(CY_IP_MXS40SRSS) || defined(CY_IP_MXS40SSRSS) || defined(CY_IP_MXS28SRSS) || defined(CY_IP_MXS22SRSS)
#include "cy_mcwdt.h"
#define _CYHAL_LPTIMER_MCWDT
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || ((SRSS_NUM_MCWDT_B) > 0)
#define _CYHAL_LPTIMER_MCWDT_B
#if !defined(SRSS_NUM_MCWDT_B)
#define SRSS_NUM_MCWDT_B (SRSS_NUM_MCWDT)
#endif
#endif
#elif defined (CY_IP_M0S8WCO)
#include "cy_wdc.h"
#define Cy_MCWDT_Init               Cy_WDC_Init
#define Cy_MCWDT_DeInit             Cy_WDC_DeInit
#define Cy_MCWDT_Enable             Cy_WDC_Enable
#define Cy_MCWDT_Disable            Cy_WDC_Disable
#define Cy_MCWDT_GetInterruptStatus Cy_WDC_GetInterruptStatus
#define Cy_MCWDT_ClearInterrupt     Cy_WDC_ClearInterrupt
#define Cy_MCWDT_GetCount           Cy_WDC_GetCount
#define Cy_MCWDT_SetMatch           Cy_WDC_SetMatch
#define Cy_MCWDT_GetMatch           Cy_WDC_GetMatch
#define Cy_MCWDT_ResetCounters      Cy_WDC_ResetCounters
#define Cy_MCWDT_GetEnabledStatus   Cy_WDC_GetEnabledStatus
#define CY_MCWDT_COUNTER0           CY_WDC_COUNTER0
#define CY_MCWDT_COUNTER1           CY_WDC_COUNTER1
#define CY_MCWDT_COUNTER2           CY_WDC_COUNTER2
#define CY_MCWDT_CTR0               CY_WDC_COUNTER0_Msk
#define CY_MCWDT_CTR1               CY_WDC_COUNTER1_Msk
#define CY_MCWDT_CTR2               CY_WDC_COUNTER2_Msk
#define srss_interrupt_mcwdt_0_IRQn wco_interrupt_IRQn
#else
#error "Current HW block is not supported"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_CYHAL_LPTIMER_MCWDT)
#if defined (_CYHAL_LPTIMER_MCWDT_B)
#define _CYHAL_LPTIMER_INSTANCES    (SRSS_NUM_MCWDT_B)
static MCWDT_Type * const _CYHAL_LPTIMER_BASE_ADDRESSES[] = {
#if SRSS_NUM_MCWDT >= 1
    MCWDT0,
#endif
#if SRSS_NUM_MCWDT >= 2
    MCWDT1,
#endif
#if SRSS_NUM_MCWDT >= 3
    MCWDT2,
#endif
#else
#define _CYHAL_LPTIMER_INSTANCES    SRSS_NUM_MCWDT
static MCWDT_STRUCT_Type * const _CYHAL_LPTIMER_BASE_ADDRESSES[] = {
#if SRSS_NUM_MCWDT >= 1
    MCWDT_STRUCT0,
#endif
#if SRSS_NUM_MCWDT >= 2
    MCWDT_STRUCT1,
#endif
#if SRSS_NUM_MCWDT >= 3
#error "SRSS_NUM_MCWDT > 2 not supported"
#endif
#endif
};
#elif defined (CY_IP_M0S8WCO_INSTANCES)
#define _CYHAL_LPTIMER_INSTANCES CY_IP_M0S8WCO_INSTANCES
static WCO_Type * const _CYHAL_LPTIMER_BASE_ADDRESSES[] = {
#if CY_IP_M0S8WCO_INSTANCES >= 1
    WCO,
#endif
#if CY_IP_M0S8WCO_INSTANCES >= 2
#error "CY_IP_M0S8WCO_INSTANCES > 1 not supported"
#endif
};
#else
#error "Current HW block is not supported"
#endif

#define _CYHAL_LPTIMER_CTRL               (CY_MCWDT_CTR0 | CY_MCWDT_CTR1 | CY_MCWDT_CTR2)
#define _CYHAL_LPTIMER_MIN_DELAY          (3U) /* minimum amount of lfclk cycles of that LPTIMER can delay for. */
#if defined (_CYHAL_LPTIMER_MCWDT_B)
// The max sleep time for CAT1C devices is ~17.5 hours. This is because the toggle bit that is set for Counter2
// match value toggles every time the bit changes from 0 to 1 or from 1 to 0.
#define _CYHAL_LPTIMER_MAX_DELAY_TICKS    (0xffffffffUL) /* ~36hours, set to 0xffffffff since C0 and C1 do not cascade */
#else
#define _CYHAL_LPTIMER_MAX_DELAY_TICKS    (0xfff0ffffUL) /* ~36hours, Not set to 0xffffffff to avoid C0 and C1 both overflowing */
#endif
#define _CYHAL_LPTIMER_MAX_COUNTER_VAL    (0xffffffffUL) /* Maximum value of the counter before it rolls over */

#define _CYHAL_LPTIMER_DEFAULT_PRIORITY   (3U)

#define _CYHAL_LPTIMER_ISR_CALL_USER_CB_MASK            (0x01)
#define _CYHAL_LPTIMER_ISR_CRITICAL_SECTION_MASK        (0x02)

#if defined(_CYHAL_LPTIMER_MCWDT)
static cyhal_lptimer_t *_cyhal_lptimer_config_structs[_CYHAL_LPTIMER_INSTANCES];
#if defined (_CYHAL_LPTIMER_MCWDT_B)
static const uint16_t _CYHAL_LPTIMER_RESET_TIME_US = 93;
static const uint16_t _CYHAL_LPTIMER_SETMATCH_TIME_US = 93;
static const cy_stc_mcwdt_config_t default_cfg = {
                .c0UpperLimit = 0xFFFF,
                .c0WarnLimit =  0xFFFF,
                .c0WarnAction = CY_MCWDT_WARN_ACTION_NONE,
                .c0UpperAction = CY_MCWDT_ACTION_NONE,
                .c0DebugRun = CY_MCWDT_ENABLE,
                .c1UpperLimit = 0xFFFF,
                .c1UpperAction = CY_MCWDT_ACTION_NONE,
                .c1DebugRun = CY_MCWDT_ENABLE,
                .c1WarnLimit =  0xFFFF,
                .c1WarnAction = CY_MCWDT_WARN_ACTION_INT,
                .c1AutoService = CY_MCWDT_ENABLE,
                .c2ToggleBit = 0,
                .c2Action = CY_MCWDT_CNT2_ACTION_INT,
                .coreSelect = CY_MCWDT_PAUSED_BY_NO_CORE,
        };
#else
#if defined(CY_IP_MXS40SSRSS)
static const uint16_t _CYHAL_LPTIMER_RESET_TIME_US = 93; // Recommended value per PDL
#else
static const uint16_t _CYHAL_LPTIMER_RESET_TIME_US = 62;
#endif
static const uint16_t _CYHAL_LPTIMER_SETMATCH_TIME_US = 0;
static const cy_stc_mcwdt_config_t default_cfg = {
                .c0Match = 0xFFFF,
                .c1Match = 0xFFFF,
                .c0Mode = CY_MCWDT_MODE_INT,
                .c1Mode = CY_MCWDT_MODE_INT,
                .c2Mode = CY_MCWDT_MODE_NONE,
                .c2ToggleBit = 0,
                .c0ClearOnMatch = false,
                .c1ClearOnMatch = false,
                .c0c1Cascade = true,
                .c1c2Cascade = false
        };
#endif
#elif defined (CY_IP_M0S8WCO)
static cyhal_lptimer_t *_cyhal_lptimer_config_structs[CY_IP_M0S8WCO_INSTANCES];
static const uint16_t _CYHAL_LPTIMER_RESET_TIME_US = 180;
static const uint16_t _CYHAL_LPTIMER_SETMATCH_TIME_US = 180;
static const cy_stc_wdc_config_t default_cfg = {
                .counter0Match = 0xFFFF,
                .counter1Match = 0xFFFF,
                .counter2ToggleBit = 0,
                .counter0Interrupt = false,
                .counter1Interrupt = true,
                .counter2Interrupt = false,
                .counter0ClearOnMatch = false,
                .counter1ClearOnMatch = true,
                .countersCascade = CY_WDC_CASCADE_COUNTERS01,
                .clockSource = CY_WDC_CLOCK_ILO
        };
#else
#error "Current HW block is not supported"
#endif

#if (_CYHAL_IRQ_MUXING)
static const _cyhal_system_irq_t _CYHAL_MCWDT_DISCONNECTED_IRQ = disconnected_IRQn;
#else
static const _cyhal_system_irq_t _CYHAL_MCWDT_DISCONNECTED_IRQ = unconnected_IRQn;
#endif

#if defined(_CYHAL_LPTIMER_INSTANCES)
static const _cyhal_system_irq_t _CYHAL_MCWDT_IRQS[_CYHAL_LPTIMER_INSTANCES] =
{
#if (defined(COMPONENT_CM55) && defined(CY_IP_MXS22SRSS))
//For CM0P/CM55 cores, there is no 0 irqn.
    unconnected_IRQn,
#else
    srss_interrupt_mcwdt_0_IRQn,
#endif
#if (_CYHAL_LPTIMER_INSTANCES >=2)
#if (defined(COMPONENT_CM33) && defined(CY_IP_MXS22SRSS))
//For CM0P/CM33 cores, there is no 1 irqn
    unconnected_IRQn,
#else
    srss_interrupt_mcwdt_1_IRQn,
#endif
#endif
#if (_CYHAL_LPTIMER_INSTANCES ==3)
    srss_interrupt_mcwdt_2_IRQn,
#endif
#if (_CYHAL_LPTIMER_INSTANCES > 3)
#error "_CYHAL_LPTIMER_INSTANCES > 3 not supported"
#endif
};
#elif defined (CY_IP_M0S8WCO_INSTANCES)//MOS8WCO only has one instance
static const _cyhal_system_irq_t _CYHAL_MCWDT_IRQS[1] =
{
    wco_interrupt_IRQn,
};
#else
#error "HW Block not supported"
#endif

static uint32_t _cyhal_lptimer_get_instance_from_irq(void)
/* Gets instance from the IRQ array*/
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    for(uint8_t i = 0; i < sizeof(_CYHAL_MCWDT_IRQS)/sizeof(_CYHAL_MCWDT_IRQS[0]); ++i)
    {
        if (_CYHAL_MCWDT_IRQS[i] == irqn)
        {
            return i;
        }
    }

    /* The IRQ may be muxed and may be triggered by other sources */
    return _CYHAL_MCWDT_DISCONNECTED_IRQ;
}

#if defined (_CYHAL_LPTIMER_MCWDT_B)
/* Get the mask (for e.g. ClearInterrupt) associated with a particular counter */
uint32_t _cyhal_lptimer_counter_to_mask(cy_en_mcwdtctr_t counter)
{
    return 1u << ((uint8_t)counter);
}
#endif

static void _cyhal_lptimer_irq_handler(void)
{
    uint32_t instance = (uint32_t)_cyhal_lptimer_get_instance_from_irq();
    if (instance != _CYHAL_MCWDT_DISCONNECTED_IRQ)
    {
        cyhal_lptimer_t *obj = _cyhal_lptimer_config_structs[instance];
#if defined (_CYHAL_LPTIMER_MCWDT_B)
        uint32_t c2_count = Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER2);
        //Since CAT1C does not use Counter0, there is no need to clear the interrupt
        Cy_MCWDT_ClearInterrupt(obj->base, (CY_MCWDT_CTR1 | CY_MCWDT_CTR2));
#else
        Cy_MCWDT_ClearInterrupt(obj->base, (CY_MCWDT_CTR0 | CY_MCWDT_CTR1 | CY_MCWDT_CTR2));
#endif
#if defined (_CYHAL_LPTIMER_MCWDT_B)
        // We want to clear the interrupt mask everytime we enter the IRQ handler
        // for CAT1C devices regardless if set_delay or set_match was called.
        // This means if cyhal_lptimer_set_match was called, a single interrupt will be triggered.
        Cy_MCWDT_SetInterruptMask(obj->base, Cy_MCWDT_GetInterruptMask(obj->base) & ~_cyhal_lptimer_counter_to_mask(obj->counter));
#endif
        /* Clear interrupt mask if set only from cyhal_lptimer_set_delay() function */
        if (obj->clear_int_mask)
        {
#if defined (_CYHAL_LPTIMER_MCWDT)
            Cy_MCWDT_SetInterruptMask(obj->base, 0);
#else
            Cy_WDC_InterruptDisable(obj->base, CY_WDC_COUNTER1);
#endif
        }
#if defined (_CYHAL_LPTIMER_MCWDT_B)
        if(obj->final_time - c2_count > 0 && obj->final_time > c2_count)
        {
            cyhal_lptimer_set_delay(obj, obj->final_time - c2_count);
        }
        else
#endif
        {
            if (NULL != obj->callback_data.callback && ((obj->isr_instruction & _CYHAL_LPTIMER_ISR_CALL_USER_CB_MASK) != 0))
            {
                cyhal_lptimer_event_callback_t callback = (cyhal_lptimer_event_callback_t) obj->callback_data.callback;
                (callback)(obj->callback_data.callback_arg, CYHAL_LPTIMER_COMPARE_MATCH);
            }
        }
#if (_CYHAL_IRQ_MUXING)
        /* Check if the event flag should have been cleared when inside a critical situation */
        if ((obj->isr_instruction & _CYHAL_LPTIMER_ISR_CRITICAL_SECTION_MASK) != 0)
        {
            #if defined (_CYHAL_LPTIMER_MCWDT_B)
                Cy_MCWDT_ClearInterrupt(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter));
                Cy_MCWDT_SetInterruptMask(obj->base, Cy_MCWDT_GetInterruptMask(obj->base) & ~_cyhal_lptimer_counter_to_mask(obj->counter));
            #elif defined(_CYHAL_LPTIMER_MCWDT)
                Cy_MCWDT_ClearInterrupt(obj->base, CY_MCWDT_CTR1);
                Cy_MCWDT_SetInterruptMask(obj->base, 0);
            #elif defined (CY_IP_M0S8WCO)
                _cyhal_irq_disable(irqn);
            #endif
            obj->isr_instruction &= ~_CYHAL_LPTIMER_ISR_CRITICAL_SECTION_MASK;
        }
#endif
    }
}
#if defined (_CYHAL_LPTIMER_MCWDT_B)
uint32_t _cyhal_lptimer_get_toggle_bit(uint32_t c2_current, uint32_t delay)
{
    uint32_t val = c2_current ^ (c2_current + delay);
    int bit = 0;
    while (val > 0)
    {
        bit++;
        val >>= 1;
    }
    return bit - 1;
}
static uint32_t _cyhal_lptimer_set_delay_common(cyhal_lptimer_t *obj, uint32_t delay)
{
    // Check to see if Counter1 or Counter2 is enabled.
    // If neither is enabled, return Error Disabled.
    // We do not check to see if Counter0 is enabled as it is not used
    // for this IP implementation.
    if ((Cy_MCWDT_GetEnabledStatus(obj->base, CY_MCWDT_COUNTER1) == 0UL)
        || (Cy_MCWDT_GetEnabledStatus(obj->base, CY_MCWDT_COUNTER2) == 0UL))
    {
        return CYHAL_LPTIMER_RSLT_ERR_DISABLED;
    }
    if (delay <= _CYHAL_LPTIMER_MIN_DELAY)
    {
        delay = _CYHAL_LPTIMER_MIN_DELAY;
    }
#if (_CYHAL_LPTIMER_MAX_DELAY_TICKS != 0xffffffffUL)
    /* No point in this check if uint32_t can't exceed the max */
    if (delay > _CYHAL_LPTIMER_MAX_DELAY_TICKS)
    {
        delay = _CYHAL_LPTIMER_MAX_DELAY_TICKS;
    }
#endif
    // If the delay is greater than 2^16 we will use Counter2 for interrupts
    // we must then clear the Counter2 interrupt before setting the new match.
    obj->counter = (delay > ((1 << 16)-1)) ? CY_MCWDT_COUNTER2 : CY_MCWDT_COUNTER1;
    uint32_t critical_section = cyhal_system_critical_section_enter();
    uint32_t counter_value = Cy_MCWDT_GetCount(obj->base, obj->counter);
    // if the counter value + the delay exceeds 32 bits, it is expected
    // that the wrap around will be handled by the uin32_t variable
    uint32_t match_value = counter_value + delay;
    Cy_MCWDT_Unlock(obj->base);
    if(obj->counter == CY_MCWDT_COUNTER1)
    {
        if(match_value > ((1 << 16)-1))
        {
            // Wait 3 LFClk cycles for reset
            Cy_MCWDT_ResetCounters(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter), _CYHAL_LPTIMER_RESET_TIME_US);
            // Since we waited 3 LFClk cycles to reset the counter, we want to deduct that from our delay
            match_value = delay - _CYHAL_LPTIMER_MIN_DELAY;
            if(match_value < _CYHAL_LPTIMER_MIN_DELAY)
            {
                // After resetting the counter and deducting the number of clock cycles it took
                // The delay is below our minumum delay.
                Cy_MCWDT_Lock(obj->base);
                cyhal_system_critical_section_exit(critical_section);
                return CYHAL_LPTIMER_RSLT_ERR_BAD_ARGUMENT;
            }
        }
        Cy_MCWDT_SetWarnLimit(obj->base, obj->counter, (uint16_t)match_value, _CYHAL_LPTIMER_SETMATCH_TIME_US);
    }
    else
    {
        // We want to get the monitored bit to set for the toggle point
        uint32_t toggle_bit = _cyhal_lptimer_get_toggle_bit(counter_value, delay);
        // We want to set an interrupt for Counter2 to the 2^n value closest to the match value without going over
        // If there is a delta between our power of value of 2^n and the match value
        // We set the remaining delay time on the object which will trigger a follow up interrupt
        // In the IRQ handler
        Cy_MCWDT_SetToggleBit(obj->base, toggle_bit);
        // Wait 3 LFClk cycles to make sure the toggle bit was updated
        cyhal_system_delay_us(_CYHAL_LPTIMER_SETMATCH_TIME_US);
    }
    Cy_MCWDT_Lock(obj->base);
    cyhal_system_critical_section_exit(critical_section);
    Cy_MCWDT_ClearInterrupt(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter));
    Cy_MCWDT_SetInterruptMask(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter));
    return CY_RSLT_SUCCESS;
}
#else
static uint32_t _cyhal_lptimer_set_delay_common(cyhal_lptimer_t *obj, uint32_t delay)
{
    if ((Cy_MCWDT_GetEnabledStatus(obj->base, CY_MCWDT_COUNTER0) == 0UL)
        || (Cy_MCWDT_GetEnabledStatus(obj->base, CY_MCWDT_COUNTER1) == 0UL)
        || (Cy_MCWDT_GetEnabledStatus(obj->base, CY_MCWDT_COUNTER2) == 0UL))
    {
        return CYHAL_LPTIMER_RSLT_ERR_DISABLED;
    }

    /**
     * - 16 bit Counter0 (C0) & Counter1 (C1) are cascaded to generated a 32 bit counter.
     * - Counter2 (C2) is a free running counter.
     * - C0 continues counting after reaching its match value. On PSoC™ 4 Counter1 is reset on
     * match. On PSoC™ 6 it continues counting.
     * - An interrupt is generated when C1 reaches the match value. On PSoC™ 4 this happens when
     * the counter increments to the same value as match. On PSoC™ 6 this happens when it increments
     * past the match value.
     *
     * EXAMPLE:
     * Supposed T=C0=C1=0, and we need to trigger an interrupt at T=0x18000.
     * We set C0_match to 0x8000 and C1 match to 2 on PSoC™ 4 and 1 on PSoC™ 6.
     * At T = 0x8000, C0_value matches C0_match so C1 get incremented. C1/C0=0x18000.
     * At T = 0x18000, C0_value matches C0_match again so C1 get incremented from 1 to 2.
     * When C1 get incremented from 1 to 2 the interrupt is generated.
     * At T = 0x18000, C1/C0 = 0x28000.
     */

    if (delay <= _CYHAL_LPTIMER_MIN_DELAY)
    {
        delay = _CYHAL_LPTIMER_MIN_DELAY;
    }
    if (delay > _CYHAL_LPTIMER_MAX_DELAY_TICKS)
    {
        delay = _CYHAL_LPTIMER_MAX_DELAY_TICKS;
    }

    Cy_MCWDT_ClearInterrupt(obj->base, CY_MCWDT_CTR1);
    uint16_t c0_old_match = (uint16_t)Cy_MCWDT_GetMatch(obj->base, CY_MCWDT_COUNTER0);

    uint32_t critical_section = cyhal_system_critical_section_enter();

    /* Cascading from C0 match into C1 is queued and can take 1 full LF clk cycle.
     * There are 3 cases:
     * Case 1: if c0 = match0 then the cascade into C1 will happen 1 cycle from now. The value c1_current_ticks is 1 lower than expected.
     * Case 2: if c0 = match0 -1 then cascade may or not happen before new match value would occur. Match occurs on rising clock edge.
     *          Synchronizing match value occurs on falling edge. Wait until c0 = match0 to ensure cascade occurs.
     * Case 3: everything works as expected.
     *
     * Note: timeout is needed here just in case the LFCLK source gives out. This avoids device lockup.
     *
     * ((2 * Cycles_LFClk) / Cycles_cpu_iteration) * (HFCLk_max / LFClk_min) = Iterations_required
     * Typical case: (2 / 100) * ((150x10^6)/33576) = 89 iterations
     * Worst case: (2 / 100) * ((150x10^6)/1) = 3x10^6 iterations
     * Compromise: (2 / 100) * ((150x10^6)/0xFFFF iterations) = 45 Hz = LFClk_min
     */
    const uint32_t DEFAULT_TIMEOUT = 0xFFFFUL;
    uint32_t timeout = DEFAULT_TIMEOUT;
    uint16_t c0_current_ticks = (uint16_t)Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER0);
    // Wait until the cascade has definitively happened. It takes a clock cycle for the cascade to happen, and potentially another a full
    // LFCLK clock cycle for the cascade to propagate up to the HFCLK-domain registers that the CPU reads.
    while (((((uint16_t)(c0_old_match - 1)) == c0_current_ticks) ||
                        (c0_old_match       == c0_current_ticks) ||
            (((uint16_t)(c0_old_match + 1)) == c0_current_ticks)) && (timeout != 0UL))
    {
        c0_current_ticks = (uint16_t)Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER0);
        timeout--;
    }
    if (timeout == 0UL)
    {
        // Timeout has occurred. There could have been a clock failure while waiting for the count value to update.
        cyhal_system_critical_section_exit(critical_section);
        return CYHAL_LPTIMER_RSLT_ERR_DISABLED;
    }

    uint16_t c0_match = (uint16_t)(c0_current_ticks + delay);
    // Changes can take up to 2 clk_lf cycles to propagate. If we set the match within this window of the current value,
    // then it is nondeterministic whether the first cascade will trigger immediately or after 2^16 cycles. Wait until
    // c0 is in a more predictable state.
    timeout = DEFAULT_TIMEOUT;
    uint32_t c0_new_ticks = c0_current_ticks;
    while(((c0_new_ticks == c0_match) ||
          (c0_new_ticks == ((uint16_t)(c0_match + 1))) ||
          (c0_new_ticks == ((uint16_t)(c0_match + 2))))
        && (timeout != 0UL))
    {
        c0_new_ticks = (uint16_t)Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER0);
        timeout--;
    }

    delay -= (c0_new_ticks >= c0_current_ticks)
        ? (c0_new_ticks - c0_current_ticks)
        : ((0xFFFFU - c0_current_ticks) + c0_new_ticks);

    c0_match = (uint16_t)(c0_current_ticks + delay);
    uint16_t c1_current_ticks = (uint16_t)Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER1);
    uint16_t c1_match = (uint16_t)(c1_current_ticks + (delay >> 16));

#if defined(CY_IP_M0S8WCO)
    c1_match += 1;
    // Increase away from rollover glitch; can't go backward or c1 interrupt will not trigger
    if (c0_match == 0)
        c0_match = 1;
#endif
    Cy_MCWDT_SetMatch(obj->base, CY_MCWDT_COUNTER0, c0_match, _CYHAL_LPTIMER_SETMATCH_TIME_US);
    Cy_MCWDT_SetMatch(obj->base, CY_MCWDT_COUNTER1, c1_match, _CYHAL_LPTIMER_SETMATCH_TIME_US);
    cyhal_system_critical_section_exit(critical_section);
    #ifdef _CYHAL_LPTIMER_MCWDT
    Cy_MCWDT_SetInterruptMask(obj->base, CY_MCWDT_CTR1);
    #else
    Cy_WDC_InterruptEnable(obj->base, CY_MCWDT_COUNTER1);
    #endif
    return CY_RSLT_SUCCESS;
}
#endif

cy_rslt_t cyhal_lptimer_init(cyhal_lptimer_t *obj)
{
    CY_ASSERT(NULL != obj);

    obj->resource.type = CYHAL_RSC_INVALID;
    obj->clear_int_mask = false;
    obj->isr_instruction = 0;
    cy_rslt_t rslt = CYHAL_LPTIMER_RSLT_ERR_NOT_SUPPORTED;
    for(uint8_t inst=0; inst < _CYHAL_LPTIMER_INSTANCES; ++inst)
    {
        if(_CYHAL_MCWDT_IRQS[inst] != _CYHAL_MCWDT_DISCONNECTED_IRQ)
        {
            // Make a temp LPTIMER cyhal_resource_inst_t with block_num = inst
            cyhal_resource_inst_t temp = {
                .type = CYHAL_RSC_LPTIMER,
                .block_num = inst,
                .channel_num = 0,
            };

            rslt = cyhal_hwmgr_reserve(&temp);
            if(rslt == CY_RSLT_SUCCESS)
            {
                obj->resource = temp;
                break;
            }
        }
    }
    if (CY_RSLT_SUCCESS == rslt)
    {
        obj->base = _CYHAL_LPTIMER_BASE_ADDRESSES[obj->resource.block_num];
#if defined (_CYHAL_LPTIMER_MCWDT_B)
        obj->offset = 0;
        obj->final_time = 0;
        obj->counter = CY_MCWDT_COUNTER1;
        cy_stc_mcwdt_config_t cfg = default_cfg;
#elif defined (_CYHAL_LPTIMER_MCWDT)
        cy_stc_mcwdt_config_t cfg = default_cfg;
#elif defined (CY_IP_M0S8WCO)
        cy_stc_wdc_config_t cfg = default_cfg;
        // The WDC_SEL clock source is populated into the config
        // register by the clock driver. Extract it so that the
        // PDL init doesn't revert it to default
        cfg.clockSource = Cy_WDC_GetClockSource(WCO);
#endif
        rslt = (cy_rslt_t) Cy_MCWDT_Init(obj->base, &cfg);
    }

    if (CY_RSLT_SUCCESS == rslt)
    {
        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        _cyhal_lptimer_config_structs[obj->resource.block_num] = obj;
    }

    if (CY_RSLT_SUCCESS == rslt)
    {
        _cyhal_system_irq_t irqn = _CYHAL_MCWDT_IRQS[obj->resource.block_num];
        _cyhal_irq_register(irqn, _CYHAL_LPTIMER_DEFAULT_PRIORITY, _cyhal_lptimer_irq_handler);

        if (CY_RSLT_SUCCESS == rslt)
        {
            _cyhal_irq_enable(irqn);
        #if defined (_CYHAL_LPTIMER_MCWDT_B)
            Cy_MCWDT_Unlock(obj->base);
            Cy_MCWDT_Enable(obj->base, (CY_MCWDT_CTR1 | CY_MCWDT_CTR2), _CYHAL_LPTIMER_RESET_TIME_US);
            Cy_MCWDT_Lock(obj->base);
        #else
            Cy_MCWDT_Enable(obj->base, _CYHAL_LPTIMER_CTRL, _CYHAL_LPTIMER_RESET_TIME_US);
        #endif
        }
    }

    if (CY_RSLT_SUCCESS != rslt)
    {
        cyhal_lptimer_free(obj);
    }

    return rslt;
}

void cyhal_lptimer_free(cyhal_lptimer_t *obj)
{
    if (CYHAL_RSC_INVALID != obj->resource.type)
    {
        _cyhal_system_irq_t irqn = _CYHAL_MCWDT_IRQS[obj->resource.block_num];
        _cyhal_irq_free(irqn);

        cyhal_hwmgr_free(&(obj->resource));
        obj->resource.type = CYHAL_RSC_INVALID;
    }
    if (NULL != obj->base)
    {
#if defined (_CYHAL_LPTIMER_MCWDT_B)
        Cy_MCWDT_Unlock(obj->base);
        // only need to disable counter1 and counter2 since those are the only counters
        // used for the IP.
        Cy_MCWDT_Disable(obj->base, (CY_MCWDT_CTR1 | CY_MCWDT_CTR2), _CYHAL_LPTIMER_RESET_TIME_US);
        Cy_MCWDT_Lock(obj->base);
#else
        Cy_MCWDT_Disable(obj->base, _CYHAL_LPTIMER_CTRL, _CYHAL_LPTIMER_RESET_TIME_US);
#endif
        // When we're using the WDC, the clock source selection is stored in the WDC_CONFIG
        // register and we want that to persist across free/init calls. So don't call deinit
        // because that will clear it out.
#if !defined(CY_IP_M0S8WCO)
        Cy_MCWDT_DeInit(obj->base);
#endif
        obj->base = NULL;
    }
}

cy_rslt_t cyhal_lptimer_reload(cyhal_lptimer_t *obj)
{
#if defined (_CYHAL_LPTIMER_MCWDT_B)
    // we save the current value for counter2 as our offset.
    // This is done because for CAT1C devices we cannot reset counter2.
    // This gives us the ability to mimic a reset by keeping track of
    // the last time reload was called. The offset will be deducted
    // from the current counter2 value when cyhal_lptimer_read is called
    obj->offset = Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER2);
    Cy_MCWDT_Unlock(obj->base);
    Cy_MCWDT_ResetCounters(obj->base, CY_MCWDT_CTR1, _CYHAL_LPTIMER_RESET_TIME_US);
    Cy_MCWDT_Lock(obj->base);

#else
    Cy_MCWDT_ResetCounters(obj->base, (CY_MCWDT_CTR0 | CY_MCWDT_CTR1 | CY_MCWDT_CTR2), 2 * _CYHAL_LPTIMER_RESET_TIME_US);
#endif
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_lptimer_set_match(cyhal_lptimer_t *obj, uint32_t ticks)
{
    obj->clear_int_mask = false;
    uint32_t c2_current = cyhal_lptimer_read(obj);
#if defined (_CYHAL_LPTIMER_MCWDT_B)
    // The reason we add the offset to ticks is because we want to get
    // the current value of counter2 without the offset value.
    // Since our delay is ticks - c2_current, this will get us our
    // current time + delay
    obj->final_time = ticks + obj->offset;
#endif
    return _cyhal_lptimer_set_delay_common(obj, ticks - c2_current);
}

cy_rslt_t cyhal_lptimer_set_delay(cyhal_lptimer_t *obj, uint32_t delay)
{
    obj->clear_int_mask = true;
#if defined (_CYHAL_LPTIMER_MCWDT_B)
    obj->final_time = (Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER2) + delay);
#endif
    return _cyhal_lptimer_set_delay_common(obj, delay);
}

uint32_t cyhal_lptimer_read(const cyhal_lptimer_t *obj)
{
#if defined (_CYHAL_LPTIMER_MCWDT_B)
    uint32_t ctr2_count = Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER2);
    if(obj->offset > ctr2_count)
    {
        return (uint32_t)((((uint64_t)1 << 32) - obj->offset) + ctr2_count);
    }
    else
    {
        return ctr2_count - obj->offset;
    }
#else
    return Cy_MCWDT_GetCount(obj->base, CY_MCWDT_COUNTER2);
#endif
}

void cyhal_lptimer_register_callback(cyhal_lptimer_t *obj, cyhal_lptimer_event_callback_t callback, void *callback_arg)
{
    CY_ASSERT(CYHAL_RSC_INVALID != obj->resource.block_num);

    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_lptimer_enable_event(cyhal_lptimer_t *obj, cyhal_lptimer_event_t event, uint8_t intr_priority, bool enable)
{
    CY_UNUSED_PARAMETER(event);
    CY_ASSERT(event == CYHAL_LPTIMER_COMPARE_MATCH);

    obj->isr_instruction &= ~_CYHAL_LPTIMER_ISR_CALL_USER_CB_MASK;
    obj->isr_instruction |= (uint8_t)enable;

    _cyhal_system_irq_t irqn =_CYHAL_MCWDT_IRQS[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);

    if (enable)
    {
        #if defined (_CYHAL_LPTIMER_MCWDT_B)
            Cy_MCWDT_ClearInterrupt(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter));
            Cy_MCWDT_SetInterruptMask(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter));
        #elif defined(_CYHAL_LPTIMER_MCWDT)
            Cy_MCWDT_ClearInterrupt(obj->base, CY_MCWDT_CTR1);
            Cy_MCWDT_SetInterruptMask(obj->base, CY_MCWDT_CTR1);
        #elif defined (CY_IP_M0S8WCO)
            _cyhal_irq_enable(irqn);
        #endif
    }
    else
    {
#if (_CYHAL_IRQ_MUXING)
        /* We may be in a critical section. Only clear the interrupt status if there isn't a pending interrupt */
        if (Cy_MCWDT_GetInterruptStatus(obj->base) != 0)
        {
            obj->isr_instruction |= _CYHAL_LPTIMER_ISR_CRITICAL_SECTION_MASK;
        }
        else
#endif
        {
            #if defined (_CYHAL_LPTIMER_MCWDT_B)
                Cy_MCWDT_ClearInterrupt(obj->base, _cyhal_lptimer_counter_to_mask(obj->counter));
                Cy_MCWDT_SetInterruptMask(obj->base, Cy_MCWDT_GetInterruptMask(obj->base) & ~_cyhal_lptimer_counter_to_mask(obj->counter));
            #elif defined(_CYHAL_LPTIMER_MCWDT)
                Cy_MCWDT_ClearInterrupt(obj->base, CY_MCWDT_CTR1);
                Cy_MCWDT_SetInterruptMask(obj->base, 0);
            #elif defined (CY_IP_M0S8WCO)
                _cyhal_irq_disable(irqn);
            #endif
        }
    }
}

void cyhal_lptimer_irq_trigger(cyhal_lptimer_t *obj)
{
    CY_ASSERT(CYHAL_RSC_INVALID != obj->resource.block_num);
    cyhal_lptimer_event_callback_t callback = (cyhal_lptimer_event_callback_t) obj->callback_data.callback;
    (callback)(obj->callback_data.callback_arg, CYHAL_LPTIMER_COMPARE_MATCH);
}

void cyhal_lptimer_get_info(cyhal_lptimer_t *obj, cyhal_lptimer_info_t *info)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(info != NULL);

#if (WCO_WDT_EN == 1)
    const cyhal_clock_t *lf_obj = &CYHAL_CLOCK_WDCSEL;
#else
    const cyhal_clock_t *lf_obj = &CYHAL_CLOCK_LF;
#endif
    info->frequency_hz = cyhal_clock_get_frequency(lf_obj);
    info->min_set_delay = _CYHAL_LPTIMER_MIN_DELAY;
    info->max_counter_value = _CYHAL_LPTIMER_MAX_COUNTER_VAL;
}

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_LPTIMER
