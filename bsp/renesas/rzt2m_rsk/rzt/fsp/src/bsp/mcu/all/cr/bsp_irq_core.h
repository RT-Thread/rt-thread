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

#ifndef BSP_IRQ_CORE_H
#define BSP_IRQ_CORE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_ICU_VECTOR_MAX_ENTRIES              (BSP_VECTOR_TABLE_MAX_ENTRIES)

#if (0 == BSP_CFG_CORE_CR52)
 #define BSP_PRV_GICD_ADDRESS                   (GICD0)
 #define BSP_PRV_GICR_TARGET0_INTREG_ADDRESS    (GICR0_TARGET0_INTREG)
 #define BSP_PRV_GICR_TARGET0_IFREG_ADDRESS     (GICR0_TARGET0_IFREG)

#elif (1 == BSP_CFG_CORE_CR52)
 #define BSP_PRV_GICD_ADDRESS                   (GICD1)
 #define BSP_PRV_GICR_TARGET0_INTREG_ADDRESS    (GICR1_TARGET0_INTREG)
 #define BSP_PRV_GICR_TARGET0_IFREG_ADDRESS     (GICR1_TARGET0_IFREG)

#endif

#define BSP_EVENT_SGI_PPI_ARRAY_NUM             (2U)
#define BSP_NON_SELECTABLE_ICFGR_MAX            (BSP_VECTOR_TABLE_MAX_ENTRIES / BSP_INTERRUPT_TYPE_OFFSET)

#define BSP_PRV_IRQ_CONFIG_MASK                 (0x000000FFU)
#define BSP_PRV_GICD_ICFGR_INT_CONFIG_MASK      (1UL << 1UL)

#define BSP_PRV_GIC_REG_STRIDE04                (4U)
#define BSP_PRV_GIC_REG_STRIDE16                (16U)
#define BSP_PRV_GIC_REG_STRIDE32                (32U)

#define BSP_PRV_GIC_REG_BITS1                   (1U)
#define BSP_PRV_GIC_REG_BITS2                   (2U)
#define BSP_PRV_GIC_REG_BITS8                   (8U)

#define BSP_PRV_GIC_REG_MASK_1BIT               (1U)

#define BSP_PRV_GIC_LOWEST_PPI_INTERRUPT_NUM    (-17)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern void * gp_renesas_isr_context[BSP_ICU_VECTOR_MAX_ENTRIES + BSP_CORTEX_VECTOR_TABLE_ENTRIES];

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Inline Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief      Sets the ISR context associated with the requested IRQ.
 *
 * @param[in]  irq            IRQ number (parameter checking must ensure the IRQ number is valid before calling this
 *                            function.
 * @param[in]  p_context      ISR context for IRQ.
 **********************************************************************************************************************/
__STATIC_INLINE void r_fsp_irq_context_set (IRQn_Type const irq, void * p_context)
{
    /* This provides access to the ISR context array defined in bsp_irq.c. This is an inline function instead of
     * being part of bsp_irq.c for performance considerations because it is used in interrupt service routines. */
    gp_renesas_isr_context[irq + BSP_VECTOR_NUM_OFFSET] = p_context;
}

/*******************************************************************************************************************//**
 * Clear the GIC pending interrupt.
 *
 * @param[in] irq            Interrupt for which to clear the Pending bit. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void r_bsp_irq_clear_pending (IRQn_Type irq)
{
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq = (uint32_t) irq;
        GICD->GICD_ICPENDR[_irq / BSP_PRV_GIC_REG_STRIDE32] =
            (uint32_t) (BSP_PRV_GIC_REG_BITS1 << (_irq % BSP_PRV_GIC_REG_STRIDE32));
    }
    else
    {
        uint32_t _irq = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);
        GICR_TARGET0_INTREG->GICR_ICPENDR0 = (uint32_t) (BSP_PRV_GIC_REG_BITS1 << _irq);
    }
}

/*******************************************************************************************************************//**
 * Get the GIC pending interrupt.
 *
 * @param[in] irq            Interrupt that gets a pending bit.. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @return  Value indicating the status of the level interrupt.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t r_bsp_irq_pending_get (IRQn_Type irq)
{
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;
    uint32_t            value = 0;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq  = (uint32_t) irq;
        uint32_t shift = (_irq % BSP_PRV_GIC_REG_STRIDE32);
        value = (GICD->GICD_ISPENDR[_irq / BSP_PRV_GIC_REG_STRIDE32] >> shift) & (uint32_t) (BSP_PRV_GIC_REG_MASK_1BIT);
    }
    else
    {
        uint32_t _irq  = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);
        uint32_t shift = _irq;
        value = (GICR_TARGET0_INTREG->GICR_ISPENDR0 >> shift) & (uint32_t) (BSP_PRV_GIC_REG_MASK_1BIT);
    }

    return value;
}

/*******************************************************************************************************************//**
 * Sets the interrupt priority and context.
 *
 * @param[in] irq            The IRQ number to configure.
 * @param[in] priority       GIC priority of the interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void r_bsp_irq_cfg (IRQn_Type const irq, uint32_t priority)
{
#if (52U == __CORTEX_R)
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq = (uint32_t) irq;

        /* Set the interrupt group to 1 (IRQ) */
        GICD->GICD_IGROUPR[_irq / BSP_PRV_GIC_REG_STRIDE32] |=
            (uint32_t) (BSP_PRV_GIC_REG_BITS1 << (_irq % BSP_PRV_GIC_REG_STRIDE32));

        /* Set the interrupt priority */
        GICD->GICD_IPRIORITYR[_irq / BSP_PRV_GIC_REG_STRIDE04] &=
            (uint32_t) (~(BSP_PRV_IRQ_CONFIG_MASK << (BSP_PRV_GIC_REG_BITS8 * (_irq % BSP_PRV_GIC_REG_STRIDE04))));
        GICD->GICD_IPRIORITYR[_irq / BSP_PRV_GIC_REG_STRIDE04] |=
            (priority <<
             (BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT + (BSP_PRV_GIC_REG_BITS8 * (_irq % BSP_PRV_GIC_REG_STRIDE04))));
    }
    else
    {
        uint32_t _irq = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);

        /* Set the interrupt group to 1 (IRQ) */
        GICR_TARGET0_INTREG->GICR_IGROUPR0 |= (uint32_t) (BSP_PRV_GIC_REG_BITS1 << _irq);

        /* Set the interrupt priority */
        GICR_TARGET0_INTREG->GICR_IPRIORITYR[_irq / BSP_PRV_GIC_REG_STRIDE04] &=
            (uint32_t) (~(BSP_PRV_IRQ_CONFIG_MASK << (BSP_PRV_GIC_REG_BITS8 * (_irq % BSP_PRV_GIC_REG_STRIDE04))));
        GICR_TARGET0_INTREG->GICR_IPRIORITYR[_irq / BSP_PRV_GIC_REG_STRIDE04] |=
            (priority <<
             (BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT + (BSP_PRV_GIC_REG_BITS8 * (_irq % BSP_PRV_GIC_REG_STRIDE04))));
    }
#endif
}

/*******************************************************************************************************************//**
 * Enable the IRQ in the GIC (Without clearing the pending bit).
 *
 * @param[in] irq            The IRQ number to enable. Note that the enums listed for IRQn_Type are only those for the
 *                           Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void r_bsp_irq_enable_no_clear (IRQn_Type const irq)
{
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq = (uint32_t) irq;
        GICD->GICD_ISENABLER[_irq / BSP_PRV_GIC_REG_STRIDE32] |=
            (uint32_t) (BSP_PRV_GIC_REG_BITS1 << (_irq % BSP_PRV_GIC_REG_STRIDE32));
    }
    else
    {
        uint32_t _irq = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);
        GICR_TARGET0_INTREG->GICR_ISENABLER0 |= (uint32_t) (BSP_PRV_GIC_REG_BITS1 << _irq);
    }
}

/*******************************************************************************************************************//**
 * Disables interrupts in the GIC.
 *
 * @param[in] irq            The IRQ number to disable in the GIC. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 **********************************************************************************************************************/
__STATIC_INLINE void r_bsp_irq_disable (IRQn_Type const irq)
{
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq = (uint32_t) irq;
        GICD->GICD_ICENABLER[_irq / BSP_PRV_GIC_REG_STRIDE32] =
            (uint32_t) (BSP_PRV_GIC_REG_BITS1 << (_irq % BSP_PRV_GIC_REG_STRIDE32));
    }
    else
    {
        uint32_t _irq = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);
        GICR_TARGET0_INTREG->GICR_ICENABLER0 = (uint32_t) (BSP_PRV_GIC_REG_BITS1 << _irq);
    }

    __DSB();
    __ISB();
}

/*******************************************************************************************************************//**
 * Sets the interrupt detect type.
 *
 * @param[in] irq             The IRQ number to configure.
 * @param[in] detect_type     GIC detect type of the interrupt (0 : active-HIGH level, 1 : rising edge-triggerd).
 **********************************************************************************************************************/
__STATIC_INLINE void r_bsp_irq_detect_type_set (IRQn_Type const irq, uint32_t detect_type)
{
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq = (uint32_t) irq;
        if (0 != detect_type)
        {
            GICD->GICD_ICFGR[_irq / BSP_PRV_GIC_REG_STRIDE16] |=
                (uint32_t) (BSP_PRV_GICD_ICFGR_INT_CONFIG_MASK <<
                            (BSP_PRV_GIC_REG_BITS2 * (_irq % BSP_PRV_GIC_REG_STRIDE16)));
        }
        else
        {
            GICD->GICD_ICFGR[_irq / BSP_PRV_GIC_REG_STRIDE16] &=
                ~((uint32_t) (BSP_PRV_GICD_ICFGR_INT_CONFIG_MASK <<
                              (BSP_PRV_GIC_REG_BITS2 * (_irq % BSP_PRV_GIC_REG_STRIDE16))));
        }
    }
    else if (irq >= BSP_PRV_GIC_LOWEST_PPI_INTERRUPT_NUM)
    {
        uint32_t _irq = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);
        if (0 != detect_type)
        {
            GICR_TARGET0_INTREG->GICR_ICFGR1 |=
                (uint32_t) (BSP_PRV_GICD_ICFGR_INT_CONFIG_MASK <<
                            (BSP_PRV_GIC_REG_BITS2 * (_irq % BSP_PRV_GIC_REG_STRIDE16)));
        }
        else
        {
            GICR_TARGET0_INTREG->GICR_ICFGR1 &=
                ~((uint32_t) (BSP_PRV_GICD_ICFGR_INT_CONFIG_MASK <<
                              (BSP_PRV_GIC_REG_BITS2 * (_irq % BSP_PRV_GIC_REG_STRIDE16))));
        }
    }
    else
    {
        /* The register that sets the SGI interrupt type (GICR_ICFGR0) is read-only, so do not set it. */
    }
}

/*******************************************************************************************************************//**
 * Sets the interrupt Group.
 *
 * @param[in] irq               The IRQ number to configure.
 * @param[in] interrupt_group   GIC interrupt group number ( 0 : FIQ, 1 : IRQ ).
 **********************************************************************************************************************/
__STATIC_INLINE void r_bsp_irq_group_set (IRQn_Type const irq, uint32_t interrupt_group)
{
    GICD_Type         * GICD;
    GICR_SGI_PPI_Type * GICR_TARGET0_INTREG;

    GICD                = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_INTREG = BSP_PRV_GICR_TARGET0_INTREG_ADDRESS;

    if (irq >= 0)
    {
        uint32_t _irq = (uint32_t) irq;
        GICD->GICD_IGROUPR[_irq / BSP_PRV_GIC_REG_STRIDE32] |= (interrupt_group << (_irq % BSP_PRV_GIC_REG_STRIDE32));
    }
    else
    {
        uint32_t _irq = (uint32_t) (irq + BSP_VECTOR_NUM_OFFSET);
        GICR_TARGET0_INTREG->GICR_IGROUPR0 |= interrupt_group << _irq;
    }
}

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_irq_core_cfg(void);           // Used internally by BSP
void bsp_common_interrupt_handler(uint32_t id);

/** @} (end addtogroup BSP_MCU_PRV) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
