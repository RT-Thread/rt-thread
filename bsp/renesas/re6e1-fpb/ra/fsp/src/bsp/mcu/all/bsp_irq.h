/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/** @} (end addtogroup BSP_MCU) */

#ifndef BSP_IRQ_H
#define BSP_IRQ_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_ICU_VECTOR_MAX_ENTRIES    (BSP_VECTOR_TABLE_MAX_ENTRIES - BSP_CORTEX_VECTOR_TABLE_ENTRIES)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern void * gp_renesas_isr_context[BSP_ICU_VECTOR_MAX_ENTRIES];

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief      Sets the ISR context associated with the requested IRQ.
 *
 * @param[in]  irq            IRQ number (parameter checking must ensure the IRQ number is valid before calling this
 *                            function.
 * @param[in]  p_context      ISR context for IRQ.
 **********************************************************************************************************************/
__STATIC_INLINE void R_FSP_IsrContextSet (IRQn_Type const irq, void * p_context)
{
    /* This provides access to the ISR context array defined in bsp_irq.c. This is an inline function instead of
     * being part of bsp_irq.c for performance considerations because it is used in interrupt service routines. */
    gp_renesas_isr_context[irq] = p_context;
}

/*******************************************************************************************************************//**
 * @brief      Finds the ISR context associated with the requested IRQ.
 *
 * @param[in]  irq            IRQ number (parameter checking must ensure the IRQ number is valid before calling this
 *                            function.
 * @return  ISR context for IRQ.
 **********************************************************************************************************************/
__STATIC_INLINE void * R_FSP_IsrContextGet (IRQn_Type const irq)
{
    /* This provides access to the ISR context array defined in bsp_irq.c. This is an inline function instead of
     * being part of bsp_irq.c for performance considerations because it is used in interrupt service routines. */
    return gp_renesas_isr_context[irq];
}

#if BSP_CFG_INLINE_IRQ_FUNCTIONS

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
__STATIC_INLINE void R_BSP_IrqStatusClear (IRQn_Type irq)
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
__STATIC_INLINE void R_BSP_IrqClearPending (IRQn_Type irq)
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
__STATIC_INLINE void R_BSP_IrqCfg (IRQn_Type const irq, uint32_t priority, void * p_context)
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
__STATIC_INLINE void R_BSP_IrqEnableNoClear (IRQn_Type const irq)
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
__STATIC_INLINE void R_BSP_IrqEnable (IRQn_Type const irq)
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
__STATIC_INLINE void R_BSP_IrqDisable (IRQn_Type const irq)
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
__STATIC_INLINE void R_BSP_IrqCfgEnable (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    R_BSP_IrqCfg(irq, priority, p_context);
    R_BSP_IrqEnable(irq);
}

#else
 #if BSP_FEATURE_ICU_HAS_IELSR
void R_BSP_IrqStatusClear(IRQn_Type irq);

 #endif
void R_BSP_IrqClearPending(IRQn_Type irq);
void R_BSP_IrqCfg(IRQn_Type const irq, uint32_t priority, void * p_context);
void R_BSP_IrqEnableNoClear(IRQn_Type const irq);
void R_BSP_IrqEnable(IRQn_Type const irq);
void R_BSP_IrqDisable(IRQn_Type const irq);
void R_BSP_IrqCfgEnable(IRQn_Type const irq, uint32_t priority, void * p_context);

#endif

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_irq_cfg(void);                // Used internally by BSP

/** @} (end addtogroup BSP_MCU_PRV) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
