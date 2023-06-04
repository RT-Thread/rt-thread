/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_GRP_IRQ_TOTAL_ITEMS    (16U)

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
    uint16_t nmisr = R_ICU->NMISR;

    /* Loop over all NMI status flags */
    for (bsp_grp_irq_t irq = BSP_GRP_IRQ_IWDT_ERROR; irq <= (bsp_grp_irq_t) (BSP_GRP_IRQ_TOTAL_ITEMS - 1); irq++)
    {
        /* If the current irq status register is set call the irq callback. */
        if (0U != (nmisr & (1U << irq)))
        {
            (void) bsp_group_irq_call(irq);
        }
    }

    /* Clear status flags that have been handled. */
    R_ICU->NMICLR = nmisr;
}

/** @} (end addtogroup BSP_MCU) */
