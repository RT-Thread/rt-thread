/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** ELC event definitions. */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_IRQ_UINT32_MAX       (0xFFFFFFFFU)
#define BSP_PRV_BITS_PER_WORD    (32)

#if (BSP_CFG_CPU_CORE == 1)
 #define BSP_EVENT_NUM_TO_INTSELR(x)         (x >> 5)        // Convert event number to INTSELR register number
 #define BSP_EVENT_NUM_TO_INTSELR_MASK(x)    (1 << (x % 32)) // Convert event number to INTSELR bit mask
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* This table is used to store the context in the ISR. */
void * gp_renesas_isr_context[BSP_ICU_VECTOR_NUM_ENTRIES];

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_WEAK_REFERENCE =
{
    (bsp_interrupt_event_t) 0
};

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/
#if 0 == BSP_CFG_INLINE_IRQ_FUNCTIONS
 #if BSP_FEATURE_ICU_HAS_IELSR

/*******************************************************************************************************************//**
 * Clear the interrupt status flag (IR) for a given interrupt. When an interrupt is triggered the IR bit
 * is set. If it is not cleared in the ISR then the interrupt will trigger again immediately.
 *
 * @param[in] irq            Interrupt for which to clear the IR bit. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqStatusClear (IRQn_Type irq)
{
    /* Clear the IR bit in the selected IELSR register. */
    R_ICU->IELSR_b[irq].IR = 0U;

    /* Read back the IELSR register to ensure that the IR bit is cleared.
     * See section "13.5.1 Operations During an Interrupt" in the RA8M1 manual R01UH0994EJ0100. */
    FSP_REGISTER_READ(R_ICU->IELSR[irq]);
}

 #endif

/*******************************************************************************************************************//**
 * Clear the interrupt status flag (IR) for a given interrupt and clear the NVIC pending interrupt.
 *
 * @param[in] irq            Interrupt for which to clear the IR bit. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqClearPending (IRQn_Type irq)
{
 #if BSP_FEATURE_ICU_HAS_IELSR

    /* Clear the IR bit in the selected IELSR register. */
    R_BSP_IrqStatusClear(irq);

    /* Flush memory transactions to ensure that the IR bit is cleared before clearing the pending bit in the NVIC. */
    __DMB();
 #endif

    /* The following statement is used in place of NVIC_ClearPendingIRQ to avoid including a branch for system
     * exceptions every time an interrupt is cleared in the NVIC. */
    uint32_t _irq = (uint32_t) irq;
    NVIC->ICPR[(((uint32_t) irq) >> 5UL)] = (uint32_t) (1UL << (_irq & 0x1FUL));
}

/*******************************************************************************************************************//**
 * Sets the interrupt priority and context.
 *
 * @param[in] irq            The IRQ to configure.
 * @param[in] priority       NVIC priority of the interrupt
 * @param[in] p_context      The interrupt context is a pointer to data required in the ISR.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqCfg (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    /* The following statement is used in place of NVIC_SetPriority to avoid including a branch for system exceptions
     * every time a priority is configured in the NVIC. */
 #if (4U == __CORTEX_M)
    NVIC->IPR[((uint32_t) irq)] = (uint8_t) ((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t) UINT8_MAX);
 #elif (33 == __CORTEX_M)
    NVIC->IPR[((uint32_t) irq)] = (uint8_t) ((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t) UINT8_MAX);
 #elif (23 == __CORTEX_M)
    NVIC->IPR[_IP_IDX(irq)] = ((uint32_t) (NVIC->IPR[_IP_IDX(irq)] & ~((uint32_t) UINT8_MAX << _BIT_SHIFT(irq))) |
                               (((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t) UINT8_MAX) << _BIT_SHIFT(irq)));
 #else
    NVIC_SetPriority(irq, priority);
 #endif

    /* Store the context. The context is recovered in the ISR. */
    R_FSP_IsrContextSet(irq, p_context);
}

/*******************************************************************************************************************//**
 * Enable the IRQ in the NVIC (Without clearing the pending bit).
 *
 * @param[in] irq            The IRQ to enable. Note that the enums listed for IRQn_Type are only those for the Cortex
 *                           Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqEnableNoClear (IRQn_Type const irq)
{
    /* The following statement is used in place of NVIC_EnableIRQ to avoid including a branch for system exceptions
     * every time an interrupt is enabled in the NVIC. */
    uint32_t _irq = (uint32_t) irq;

    __COMPILER_BARRIER();
    NVIC->ISER[(_irq >> 5UL)] = (uint32_t) (1UL << (_irq & 0x1FUL));
    __COMPILER_BARRIER();
}

/*******************************************************************************************************************//**
 * Clears pending interrupts in both ICU and NVIC, then enables the interrupt.
 *
 * @param[in] irq            Interrupt for which to clear the IR bit and enable in the NVIC. Note that the enums listed
 *                           for IRQn_Type are only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqEnable (IRQn_Type const irq)
{
    /* Clear pending interrupts in the ICU and NVIC. */
    R_BSP_IrqClearPending(irq);

    /* Enable the IRQ in the NVIC. */
    R_BSP_IrqEnableNoClear(irq);
}

/*******************************************************************************************************************//**
 * Disables interrupts in the NVIC.
 *
 * @param[in] irq            The IRQ to disable in the NVIC. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqDisable (IRQn_Type const irq)
{
    /* The following statements is used in place of NVIC_DisableIRQ to avoid including a branch for system
     * exceptions every time an interrupt is cleared in the NVIC. */
    uint32_t _irq = (uint32_t) irq;
    NVIC->ICER[(((uint32_t) irq) >> 5UL)] = (uint32_t) (1UL << (_irq & 0x1FUL));

    __DSB();
    __ISB();
}

/*******************************************************************************************************************//**
 * Sets the interrupt priority and context, clears pending interrupts, then enables the interrupt.
 *
 * @param[in] irq            Interrupt number.
 * @param[in] priority       NVIC priority of the interrupt
 * @param[in] p_context      The interrupt context is a pointer to data required in the ISR.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
void R_BSP_IrqCfgEnable (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    R_BSP_IrqCfg(irq, priority, p_context);
    R_BSP_IrqEnable(irq);
}

#endif                                 // 0 == BSP_CFG_INLINE_IRQ_FUNCTIONS

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 *        Using the vector table information section that has been built by the linker and placed into ROM in the
 * .vector_info. section, this function will initialize the ICU so that configured ELC events will trigger interrupts
 * in the NVIC.
 *
 **********************************************************************************************************************/
void bsp_irq_cfg (void)
{
#if FSP_PRIV_TZ_USE_SECURE_REGS
 #if (BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_SECURE_BUILD == 0)

    /* On MCUs with this implementation of TrustZone, IRQ security attribution is set to secure by default.
     * This means that flat projects do not need to set security attribution to secure. */
 #else

    /* Unprotect security registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

  #if !BSP_TZ_SECURE_BUILD

    /* Set the DMAC channels to secure access. */
   #ifdef BSP_TZ_CFG_ICUSARC
    R_CPSCU->ICUSARC = ~R_CPSCU_ICUSARC_SADMACn_Msk;
   #endif
  #endif

    /* Place all vectors in non-secure state unless they are used in the secure project. */
    uint32_t interrupt_security_state[BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD];
    memset(&interrupt_security_state, UINT8_MAX, sizeof(interrupt_security_state));

    for (uint32_t i = 0U; i < BSP_ICU_VECTOR_NUM_ENTRIES; i++)
    {
        if (0U != g_interrupt_event_link_select[i])
        {
            /* This is a secure vector. Clear the associated bit. */
            uint32_t index = i / BSP_PRV_BITS_PER_WORD;
            uint32_t bit   = i % BSP_PRV_BITS_PER_WORD;
            interrupt_security_state[index] &= ~(1U << bit);
        }
    }

    /* The Secure Attribute managed within the ARM CPU NVIC must match the security attribution of IELSEn
     * (Reference section 13.2.9 in the RA6M4 manual R01UH0890EJ0050). */
    uint32_t volatile * p_icusarg = &R_CPSCU->ICUSARG;
    for (uint32_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD; i++)
    {
        p_icusarg[i]  = interrupt_security_state[i];
        NVIC->ITNS[i] = interrupt_security_state[i];
    }

    /* Protect security registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
 #endif
#endif

#if BSP_FEATURE_ICU_HAS_IELSR

    /* Calculate the number of IELSR registers that need to be initialized. */
    uint32_t ielsr_count = BSP_ICU_VECTOR_MAX_ENTRIES - BSP_FEATURE_ICU_FIXED_IELSR_COUNT;
    if (ielsr_count > BSP_ICU_VECTOR_NUM_ENTRIES)
    {
        ielsr_count = BSP_ICU_VECTOR_NUM_ENTRIES;
    }

    for (uint32_t i = 0U; i < ielsr_count; i++)
    {
        if (0U != g_interrupt_event_link_select[i])
        {
            R_ICU->IELSR[i] = (uint32_t) g_interrupt_event_link_select[i];

 #if (BSP_CFG_CPU_CORE == 1)

            /* Set INTSELR for selected events. */
            uint32_t intselr_num = BSP_EVENT_NUM_TO_INTSELR((uint32_t) g_interrupt_event_link_select[i]);
            uint32_t intselr     = R_ICU->INTSELR[intselr_num];

            intselr |= BSP_EVENT_NUM_TO_INTSELR_MASK((uint32_t) g_interrupt_event_link_select[i]);
            R_ICU->INTSELR[intselr_num] = intselr;
 #endif
        }
    }
#endif
}
