/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include <stdint.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if BSP_MCU_GROUP_RA6W1
 #define BSP_GRP_IRQ_TOTAL_ITEMS    (16U)
#else
 #define BSP_GRP_IRQ_TOTAL_ITEMS    (3U)
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
bsp_grp_irq_cb_t g_bsp_group_irq_sources[BSP_GRP_IRQ_TOTAL_ITEMS] BSP_SECTION_EARLY_INIT;

static void (* g_bsp_group_nmi_cb)(const uint32_t * p_exception_args);

BSP_WEAK_REFERENCE void NMI_HandlerC(unsigned long * exception_args);
BSP_WEAK_REFERENCE void HardFault_HandlerC(unsigned long * exception_args);
BSP_WEAK_REFERENCE void SecureFault_HandlerC(unsigned long * exception_args);

#if BSP_FEATURE_BSP_HAS_ICU
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

#endif

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
 * Register a callback function for NMI. If NULL is passed for the callback argument then any
 * previously registered callbacks are unregistered.
 *
 * @param[in]  p_callback   Pointer to function to call when NMI occurs.
 *
 * @retval     FSP_SUCCESS                  Callback registered
 * @retval     FSP_ERR_ASSERTION            Callback pointer is NULL
 **********************************************************************************************************************/
fsp_err_t R_BSP_GroupNmiWrite (void (* p_callback)(const uint32_t * p_exception_args))
{
    g_bsp_group_nmi_cb = p_callback;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Non-maskable interrupt handler. This exception is defined by the BSP, unlike other system exceptions, because
 * there are many sources that map to the NMI exception.
 *
 * @note NMI exception is caused due to watchdog timeout for DA1469x and hence the registered callback function
 *       for handling the WDT error is directly referred
 **********************************************************************************************************************/

BSP_WEAK_REFERENCE void NMI_HandlerC (unsigned long * exception_args)
{
    FSP_PARAMETER_NOT_USED(exception_args);
#if BSP_FEATURE_BSP_HAS_ICU
    uint32_t nmisr = ICU->ICU_NMISR_REG;

    /* Loop over all NMI status flags */
    bsp_grp_irq_t irq = BSP_GRP_IRQ_WDT_ERROR;
    if (0U != (nmisr & (1U << irq)))
    {
        g_bsp_group_nmi_cb((uint32_t *) exception_args);
    }
    else
    {
        for ( ; irq <= (bsp_grp_irq_t) (BSP_GRP_IRQ_TOTAL_ITEMS - 1); irq++)
        {
            /* If the current irq status register is set call the irq callback. */
            if (0U != (nmisr & (1U << irq)))
            {
                (void) bsp_group_irq_call(irq);
            }
        }
    }

    /* Clear status flags that have been handled. */
    ICU->ICU_NMICLR_REG = nmisr;
#else
    if (g_bsp_group_nmi_cb != NULL)
    {
        g_bsp_group_nmi_cb((uint32_t *) exception_args);
    }
    else
    {
        /* Wait for the reset to occur */
        while (1)
        {
        }
    }
#endif
}

BSP_WEAK_REFERENCE void HardFault_HandlerC (unsigned long * exception_args)
{
    FSP_PARAMETER_NOT_USED(exception_args);

    while (1)
    {
    }
}

BSP_WEAK_REFERENCE void SecureFault_HandlerC (unsigned long * exception_args)
{
    FSP_PARAMETER_NOT_USED(exception_args);

    while (1)
    {
    }
}

/** @} (end addtogroup BSP_MCU) */
