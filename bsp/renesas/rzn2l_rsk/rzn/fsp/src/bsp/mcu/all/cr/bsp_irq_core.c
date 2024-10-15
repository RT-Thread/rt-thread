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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** ELC event definitions. */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_IRQ_UINT32_MAX           (0xFFFFFFFFU)

#define BSP_PRV_CLEAR_REG_MAX        (13U)
#define BSP_PRV_ALL_BIT_CLEAR        (0xFFFFFFFFU)

#define BSP_PRV_ID_MASK              (0x000003FFU)
#define BSP_PRV_INTERRUPTABLE_NUM    (32U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
#if VECTOR_DATA_IRQ_COUNT > 0
extern fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES];
#endif
extern fsp_vector_t g_sgi_ppi_vector_table[BSP_CORTEX_VECTOR_TABLE_ENTRIES];

extern const uint32_t BSP_GICD_ICFGR_INIT[BSP_NON_SELECTABLE_ICFGR_MAX];

/* This table is used to store the context in the ISR. */
void * gp_renesas_isr_context[BSP_ICU_VECTOR_MAX_ENTRIES + BSP_CORTEX_VECTOR_TABLE_ENTRIES];

/* GIC current interrupt ID and variable. */
IRQn_Type g_current_interrupt_num[BSP_PRV_INTERRUPTABLE_NUM];
uint8_t   g_current_interrupt_pointer = 0;

const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_WEAK_REFERENCE =
{
    (bsp_interrupt_event_t) 0
};

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *        Using the vector table information section that has been built by the linker and placed into ROM in the
 * .vector_info. section, this function will initialize the ICU so that configured ELC events will trigger interrupts
 * in the NVIC.
 *
 **********************************************************************************************************************/
void bsp_irq_core_cfg (void)
{
    uint32_t                   gicd_reg_num;
    GICD_Type                * GICD;
    GICR_CONTROL_TARGET_Type * GICR_TARGET0_IFREG;

    GICD               = BSP_PRV_GICD_ADDRESS;
    GICR_TARGET0_IFREG = BSP_PRV_GICR_TARGET0_IFREG_ADDRESS;

    /* Enable Group1 interrupts from the GIC Distributor to the GIC CPU interface. */
    GICD->GICD_CTLR |= 0x00000002UL;

    /* Release Processor Sleep state of the target. */
    GICR_TARGET0_IFREG->GICR_WAKER = 0x00000000UL;

    /* Initialize GICD_ICFGR register for the edge-triggered interrupt. */
    for (gicd_reg_num = 0; gicd_reg_num < BSP_NON_SELECTABLE_ICFGR_MAX; gicd_reg_num++)
    {
        GICD->GICD_ICFGR[gicd_reg_num] = BSP_GICD_ICFGR_INIT[gicd_reg_num];
    }

    /* Clear the Pending and Active bit for the all interrupts. */
    for (gicd_reg_num = 0; gicd_reg_num < BSP_PRV_CLEAR_REG_MAX; gicd_reg_num++)
    {
        GICD->GICD_ICPENDR[gicd_reg_num]   = BSP_PRV_ALL_BIT_CLEAR;
        GICD->GICD_ICACTIVER[gicd_reg_num] = BSP_PRV_ALL_BIT_CLEAR;
    }

    __asm volatile ("cpsie i    \n"    /* Enable IRQ Interrupts */
                    "cpsie f    \n"    /* Enable FIQ Interrupts */
                    "cpsie a    \n"    /* Enable SError Interrupts */
                    "isb");            /* Ensuring Context-changing */
}

/*******************************************************************************************************************//**
 * This function is called first when an interrupt is generated and branches to each interrupt isr function.
 *
 * @param[in]  id    GIC INTID used to identify the interrupt.
 **********************************************************************************************************************/
void bsp_common_interrupt_handler (uint32_t id)
{
    uint16_t  gic_intid;
    IRQn_Type irq;

    /* Get interrupt ID (GIC INTID). */
    gic_intid = (uint16_t) (id & BSP_PRV_ID_MASK);

    irq = (IRQn_Type) (gic_intid - BSP_CORTEX_VECTOR_TABLE_ENTRIES);

    /* Remain the interrupt number */
    g_current_interrupt_num[g_current_interrupt_pointer++] = irq;
    __asm volatile ("dmb");

    BSP_CFG_MULTIPLEX_INTERRUPT_ENABLE

#if VECTOR_DATA_IRQ_COUNT > 0
    if (BSP_CORTEX_VECTOR_TABLE_ENTRIES <= gic_intid)
    {
        /* Branch to an interrupt handler. */
        g_vector_table[irq]();
    }
    else
#endif
    {
        /* Branch to an interrupt handler. */
        g_sgi_ppi_vector_table[gic_intid]();
    }

    g_current_interrupt_pointer--;

    BSP_CFG_MULTIPLEX_INTERRUPT_DISABLE
}
