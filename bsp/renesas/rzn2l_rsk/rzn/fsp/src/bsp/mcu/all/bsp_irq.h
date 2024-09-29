/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_IRQ_H
#define BSP_IRQ_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#if defined(BSP_CFG_CORE_CR52)
 #include "cr/bsp_irq_core.h"
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Inline Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
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
    r_fsp_irq_context_set(irq, p_context);
}

/*******************************************************************************************************************//**
 * Clear the GIC pending interrupt.
 *
 * @param[in] irq            Interrupt for which to clear the Pending bit. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqClearPending (IRQn_Type irq)
{
    r_bsp_irq_clear_pending(irq);
}

/*******************************************************************************************************************//**
 * Get the GIC pending interrupt.
 *
 * @param[in] irq            Interrupt that gets a pending bit.. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @return  Value indicating the status of the level interrupt.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_IrqPendingGet (IRQn_Type irq)
{
    return r_bsp_irq_pending_get(irq);
}

/*******************************************************************************************************************//**
 * Sets the interrupt priority and context.
 *
 * @param[in] irq            The IRQ number to configure.
 * @param[in] priority       GIC priority of the interrupt
 * @param[in] p_context      The interrupt context is a pointer to data required in the ISR.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqCfg (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    r_bsp_irq_cfg(irq, priority);

    /* Store the context. The context is recovered in the ISR. */
    R_FSP_IsrContextSet(irq, p_context);
}

/*******************************************************************************************************************//**
 * Enable the IRQ in the GIC (Without clearing the pending bit).
 *
 * @param[in] irq            The IRQ number to enable. Note that the enums listed for IRQn_Type are only those for the
 *                           Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqEnableNoClear (IRQn_Type const irq)
{
    r_bsp_irq_enable_no_clear(irq);
}

/*******************************************************************************************************************//**
 * Enable the IRQ in the GIC (With clearing the pending bit).
 *
 * @param[in] irq            The IRQ number to enable. Note that the enums listed for IRQn_Type are only those for the
 *                           Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqEnable (IRQn_Type const irq)
{
    /* Clear pending interrupts in the GIC. */
    R_BSP_IrqClearPending(irq);

    /* Enable the interrupt in the GIC. */
    R_BSP_IrqEnableNoClear(irq);
}

/*******************************************************************************************************************//**
 * Disables interrupts in the GIC.
 *
 * @param[in] irq            The IRQ number to disable in the GIC. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqDisable (IRQn_Type const irq)
{
    r_bsp_irq_disable(irq);
}

/*******************************************************************************************************************//**
 * Sets the interrupt priority and context, clears pending interrupts, then enables the interrupt.
 *
 * @param[in] irq            Interrupt number.
 * @param[in] priority       GIC priority of the interrupt
 * @param[in] p_context      The interrupt context is a pointer to data required in the ISR.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqCfgEnable (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    R_BSP_IrqCfg(irq, priority, p_context);
    R_BSP_IrqEnable(irq);
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
    return gp_renesas_isr_context[irq + BSP_VECTOR_NUM_OFFSET];
}

/*******************************************************************************************************************//**
 * Sets the interrupt detect type.
 *
 * @param[in] irq             The IRQ number to configure.
 * @param[in] detect_type     GIC detect type of the interrupt (0 : active-HIGH level, 1 : rising edge-triggerd).
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqDetectTypeSet (IRQn_Type const irq, uint32_t detect_type)
{
    r_bsp_irq_detect_type_set(irq, detect_type);
}

/*******************************************************************************************************************//**
 * Sets the interrupt Group.
 *
 * @param[in] irq               The IRQ number to configure.
 * @param[in] interrupt_group   GIC interrupt group number ( 0 : FIQ, 1 : IRQ ).
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqGroupSet (IRQn_Type const irq, uint32_t interrupt_group)
{
    r_bsp_irq_group_set(irq, interrupt_group);
}

/*******************************************************************************************************************//**
 * Sets the interrupt mask level.
 *
 * @param[in] mask_level          The interrupt mask level
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqMaskLevelSet (uint32_t mask_level)
{
    FSP_CRITICAL_SECTION_SET_STATE(mask_level << BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT);
}

/*******************************************************************************************************************//**
 * Gets the interrupt mask level.
 *
 * @return  Value indicating the interrupt mask level.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_IrqMaskLevelGet (void)
{
    return (uint32_t) ((FSP_CRITICAL_SECTION_GET_CURRENT_STATE() >> BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT) &
                       0x0000001FUL);
}

/** @} (end addtogroup BSP_MCU) */

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
