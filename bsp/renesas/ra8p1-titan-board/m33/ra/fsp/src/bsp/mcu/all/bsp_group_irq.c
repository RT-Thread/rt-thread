/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (BSP_FEATURE_ICU_NMIER_MAX_INDEX > 15U)
 #define BSP_PRV_NMIER_T    uint32_t
#else
 #define BSP_PRV_NMIER_T    uint16_t
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/** This array holds callback functions. */
bsp_grp_irq_cb_t g_bsp_group_irq_sources[BSP_FEATURE_ICU_NMIER_MAX_INDEX + 1] BSP_SECTION_EARLY_INIT;

void        NMI_Handler(void);
static void bsp_group_irq_call(bsp_grp_irq_t irq);

/*******************************************************************************************************************//**
 * Calls the callback function for an interrupt if a callback has been registered.
 *
 * @param[in]   irq         Which interrupt to check and possibly call.
 *
 * @retval FSP_SUCCESS              Callback was called.
 * @retval FSP_ERR_INVALID_ARGUMENT No valid callback has been registered for this interrupt source.
 *
 * @warning This function is called from within an interrupt
 **********************************************************************************************************************/
static void bsp_group_irq_call (bsp_grp_irq_t irq)
{
    /** Check for valid callback */
    if (NULL != g_bsp_group_irq_sources[irq])
    {
        /** Callback has been found. Call it. */
        g_bsp_group_irq_sources[irq](irq);
    }
}

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Register a callback function for supported interrupts. If NULL is passed for the callback argument then any
 * previously registered callbacks are unregistered.
 *
 * @param[in]  irq          Interrupt for which  to register a callback.
 * @param[in]  p_callback   Pointer to function to call when interrupt occurs.
 *
 * @retval     FSP_SUCCESS                  Callback registered
 * @retval     FSP_ERR_ASSERTION            Callback pointer is NULL
 **********************************************************************************************************************/
fsp_err_t R_BSP_GroupIrqWrite (bsp_grp_irq_t irq, void (* p_callback)(bsp_grp_irq_t irq))
{
#if BSP_CFG_PARAM_CHECKING_ENABLE

    /* Check pointer for NULL value. */
    FSP_ASSERT(p_callback);
#endif

    /* Register callback. */
    g_bsp_group_irq_sources[irq] = p_callback;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Non-maskable interrupt handler. This exception is defined by the BSP, unlike other system exceptions, because
 * there are many sources that map to the NMI exception.
 **********************************************************************************************************************/
void NMI_Handler (void)
{
    /* NMISR is masked by NMIER to prevent iterating over NMI status flags that are not enabled. */
    BSP_PRV_NMIER_T nmier = R_ICU->NMIER;
    BSP_PRV_NMIER_T nmisr = R_ICU->NMISR & nmier;

    /* Loop over all NMI status flags */
    for (bsp_grp_irq_t irq = BSP_GRP_IRQ_IWDT_ERROR; irq <= (bsp_grp_irq_t) (BSP_FEATURE_ICU_NMIER_MAX_INDEX); irq++)
    {
        /* If the current irq status register is set call the irq callback. */
        if (0U != (nmisr & (1U << irq)))
        {
            (void) bsp_group_irq_call(irq);
        }
    }

    /* Clear status flags that have been handled. */
    R_ICU->NMICLR = nmisr;

#if BSP_CFG_MCU_PART_SERIES == 8

    /* Wait for NMISR to be cleared before exiting the ISR to prevent the IRQ from being regenerated.
     * See "NMICLR : Non-Maskable Interrupt Status Clear Register" description in the ICU section
     * of the relevant hardware manual */
    FSP_HARDWARE_REGISTER_WAIT((R_ICU->NMISR & nmisr), 0);
#endif
}

/** @} (end addtogroup BSP_MCU) */
