/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_icu.h"
#include "r_icu_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "ICU" in ASCII, used to determine if channel is open. */
#define ICU_OPEN               (0x00494355U)

#define ICU_IRQMD_OFFSET       (0)

#if BSP_FEATURE_ICU_HAS_FILTER
 #define ICU_FCLKSEL_OFFSET    (4)
 #define ICU_FLTEN_OFFSET      (7)
 #if BSP_FEATURE_ICU_HAS_LOCO_FILTER
  #define LOCO_CLOCK_HZ        (R_BSP_SourceClockHzGet(FSP_PRIV_CLOCK_LOCO))
  #define SYSTEM_CLOCK_HZ      (SystemCoreClock)
 #endif
#endif

/* If the mask is larger than 0xFFFF, then it requires 32-bit values instead of 16-bit */
#if BSP_FEATURE_ICU_IRQ_CHANNELS_MASK > 0xFFFFU

/* When mask is over 16-bit, there are actually two registers - R_ICU->IRQCRa and R_ICU->IRQCRb. Between them in memory
 * is R_ICU->NMICR and means there is a 4 byte offset between the end of IRQCRa and beginning of IRQCRb. To save some
 * instructions, this arithmetic determines if the 4 byte offset should be added to the indexing of IRQCRa to write to
 * channels 16-31 */
 #define ICU_IRQCR_CH(c)    ((c) + (uint8_t) (((c) >> 4) << 2))
 #define ICU_IRQCR_REG             (R_ICU->IRQCRa)
 #define ICU_IRQCR_REG_BITFIELD    (R_ICU->IRQCRa_b)
#else
 #define ICU_IRQCR_CH(c)    (c)
 #define ICU_IRQCR_REG             (R_ICU->IRQCR)
 #define ICU_IRQCR_REG_BITFIELD    (R_ICU->IRQCR_b)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * icu_prv_ns_callback)(external_irq_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile icu_prv_ns_callback)(external_irq_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void r_icu_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* ICU implementation of External IRQ API. */
const external_irq_api_t g_external_irq_on_icu =
{
    .open        = R_ICU_ExternalIrqOpen,
    .enable      = R_ICU_ExternalIrqEnable,
    .disable     = R_ICU_ExternalIrqDisable,
    .callbackSet = R_ICU_ExternalIrqCallbackSet,
    .close       = R_ICU_ExternalIrqClose,
};

/*******************************************************************************************************************//**
 * @addtogroup ICU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure an IRQ input pin for use with the external interrupt interface.  Implements @ref external_irq_api_t::open.
 *
 * The Open function is responsible for preparing an external IRQ pin for operation.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              One of the following is invalid:
 *                                          - p_ctrl or p_cfg is NULL
 * @retval FSP_ERR_ALREADY_OPEN           The channel specified has already been opened. No configurations were changed.
 *                                        Call the associated Close function to reconfigure the channel.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in p_cfg is not available on the device selected in
 *                                        r_bsp_cfg.h.
 * @retval FSP_ERR_INVALID_ARGUMENT       p_cfg->p_callback is not NULL, but ISR is not enabled. ISR must be enabled to
 *                                        use callback function.
 * @retval FSP_ERR_UNSUPPORTED            An input argument is not supported by selected mode.
 *
 * @note This function is reentrant for different channels.  It is not reentrant for the same channel.
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqOpen (external_irq_ctrl_t * const p_api_ctrl, external_irq_cfg_t const * const p_cfg)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    FSP_ASSERT(NULL != p_cfg);

 #if BSP_FEATURE_ICU_HAS_LOCO_FILTER
    FSP_ASSERT(NULL != p_cfg->p_extend);
 #endif

 #if !BSP_FEATURE_ICU_HAS_FILTER

    /* Verify the configuration trigger source is correct */
    FSP_ERROR_RETURN((EXTERNAL_IRQ_TRIG_FALLING == p_cfg->trigger) ||
                     (EXTERNAL_IRQ_TRIG_RISING == p_cfg->trigger) ||
                     (EXTERNAL_IRQ_TRIG_BOTH_EDGE == p_cfg->trigger) ||
                     (EXTERNAL_IRQ_TRIG_LEVEL_LOW == p_cfg->trigger),
                     FSP_ERR_UNSUPPORTED);
 #endif

    FSP_ERROR_RETURN(0 != ((1ULL << p_cfg->channel) & BSP_FEATURE_ICU_IRQ_CHANNELS_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Callback must be used with a valid interrupt priority otherwise it will never be called. */
    if (p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(BSP_IRQ_DISABLED != p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);
    }
#endif

    p_ctrl->irq = p_cfg->irq;

#if BSP_FEATURE_ICU_HAS_IELSR

    /* IELSR Must be zero when modifying the IRQCR bits.
     * (See ICU Section 14.2.1 of the RA6M3 manual R01UH0886EJ0100). */
    uint32_t ielsr = R_ICU->IELSR[p_ctrl->irq];
    R_ICU->IELSR[p_ctrl->irq] = 0;
#endif

#if BSP_TZ_SECURE_BUILD

    /* If this is a secure build, the callback provided in p_cfg must be secure. */
    p_ctrl->p_callback_memory = NULL;
#endif

    /* Initialize control block. */
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;
    p_ctrl->channel    = p_cfg->channel;

    uint8_t channel = ICU_IRQCR_CH(p_ctrl->channel);
    uint8_t irqcr   = 0;

#if BSP_FEATURE_ICU_HAS_FILTER

    /* Disable digital filter */
    ICU_IRQCR_REG[channel] = 0U;

 #if BSP_FEATURE_ICU_HAS_LOCO_FILTER
    icu_extended_cfg_t * p_extend = (icu_extended_cfg_t *) p_cfg->p_extend;

    /* Set the digital filter divider. */
    irqcr = (uint8_t) (p_extend->filter_src << R_ICU_IRQCR_LOCOSEL_Pos);
 #endif

    /* Set the digital filter divider. */
    irqcr |= (uint8_t) (p_cfg->clock_source_div << ICU_FCLKSEL_OFFSET);

    /* Enable/Disable digital filter. */
    irqcr |= (uint8_t) (p_cfg->filter_enable << ICU_FLTEN_OFFSET);

    /* Set the IRQ trigger. */
    irqcr |= (uint8_t) (p_cfg->trigger << ICU_IRQMD_OFFSET);
#else
    irqcr = (uint8_t) (p_cfg->trigger << ICU_IRQMD_OFFSET);
#endif

    /* Write IRQCR */
    ICU_IRQCR_REG[channel] = irqcr;

#if BSP_FEATURE_ICU_HAS_IELSR
 #if BSP_FEATURE_ICU_HAS_LOCO_FILTER

    /* If LOCO is used as Digital Filtering Sample Clock, delay 4 LOCO clock cycles before restore IELSR */
    if (EXTERNAL_IRQ_DIGITAL_FILTER_LOCO == p_extend->filter_src)
    {
        /* If LOCO is used as Digital Filtering Sample Clock, delay 4 LOCO clock cycles before restore IELSR.
         * Total_cycles = (4 * system_clock_hz) / (loco_clock_hz).
         */
        uint32_t total_cycles = (uint32_t) ((4 * SYSTEM_CLOCK_HZ) / LOCO_CLOCK_HZ);

        bsp_prv_software_delay_loop(BSP_DELAY_LOOPS_CALCULATE(total_cycles));
    }
 #endif

    /* Restore IELSR. */
    R_ICU->IELSR[p_ctrl->irq] = ielsr;
#endif

    /* NOTE: User can have the driver opened when the IRQ is not in the vector table. This is for use cases
     * where the external IRQ driver is used to generate ELC events only (without CPU interrupts).
     * In such cases we will not set the IRQ priority but will continue with the processing.
     */
    if (p_ctrl->irq >= 0)
    {
        R_BSP_IrqCfg(p_ctrl->irq, p_cfg->ipl, p_ctrl);
    }

    /* Mark the control block as open */
    p_ctrl->open = ICU_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable external interrupt for specified channel at NVIC. Implements @ref external_irq_api_t::enable.
 *
 * @retval FSP_SUCCESS                 Interrupt Enabled successfully.
 * @retval FSP_ERR_ASSERTION           The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    Requested IRQ is not defined in this system
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqEnable (external_irq_ctrl_t * const p_api_ctrl)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_ctrl->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#endif

    /* Clear the interrupt status and Pending bits, before the interrupt is enabled. */
    R_BSP_IrqEnable(p_ctrl->irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable external interrupt for specified channel at NVIC. Implements @ref external_irq_api_t::disable.
 *
 * @retval FSP_SUCCESS                 Interrupt disabled successfully.
 * @retval FSP_ERR_ASSERTION           The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    Requested IRQ is not defined in this system
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqDisable (external_irq_ctrl_t * const p_api_ctrl)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_ctrl->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#endif

    /* Disable the interrupt, and then clear the interrupt pending bits and interrupt status. */
    R_BSP_IrqDisable(p_ctrl->irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements external_irq_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqCallbackSet (external_irq_ctrl_t * const p_api_ctrl,
                                        void (                    * p_callback)(
                                            external_irq_callback_args_t *),
                                        void * const                         p_context,
                                        external_irq_callback_args_t * const p_callback_memory)
{
    icu_instance_ctrl_t * p_ctrl = p_api_ctrl;

#if BSP_TZ_SECURE_BUILD

    /* cmse_check_address_range returns NULL if p_callback is located in secure memory */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));
#else
    FSP_PARAMETER_NOT_USED(p_callback_memory);
#endif

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_callback);

 #if BSP_TZ_SECURE_BUILD

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    external_irq_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                               CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback_memory = p_callback_memory;
    p_ctrl->p_callback        = callback_is_secure ? p_callback :
                                (void (*)(external_irq_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the external interrupt channel. Implements @ref external_irq_api_t::close.
 *
 * @retval     FSP_SUCCESS          Successfully closed.
 * @retval     FSP_ERR_ASSERTION    The parameter p_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN     The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqClose (external_irq_ctrl_t * const p_api_ctrl)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Cleanup. Disable interrupt */
    if (p_ctrl->irq >= 0)
    {
        /* Disable the interrupt, and then clear the interrupt pending bits and interrupt status. */
        R_BSP_IrqDisable(p_ctrl->irq);
        R_FSP_IsrContextSet(p_ctrl->irq, NULL);
    }

    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ICU)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * ICU External Interrupt ISR.
 **********************************************************************************************************************/
void r_icu_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

#if BSP_FEATURE_ICU_HAS_IELSR
    bool level_irq = false;

    uint8_t channel = ICU_IRQCR_CH(p_ctrl->channel);
    uint8_t mode    = ICU_IRQCR_REG_BITFIELD[channel].IRQMD;

    if (EXTERNAL_IRQ_TRIG_LEVEL_LOW == mode)
    {
        level_irq = true;
    }
    else
    {
        /* Clear the IR bit before calling the user callback so that if an edge is detected while the ISR is active
         * it will not be missed. */
        R_BSP_IrqStatusClear(irq);
    }
#endif

    if ((NULL != p_ctrl) && (NULL != p_ctrl->p_callback))
    {
#if BSP_TZ_SECURE_BUILD

        /* p_callback can point to a secure function or a non-secure function. */
        external_irq_callback_args_t args;
        if (!cmse_is_nsfptr(p_ctrl->p_callback))
        {
            /* If p_callback is secure, then the project does not need to change security state. */
            args.channel   = p_ctrl->channel;
            args.p_context = p_ctrl->p_context;
            p_ctrl->p_callback(&args);
        }
        else
        {
            /* Save current state of p_callback_args so that it can be shared between interrupts. */
            args = *p_ctrl->p_callback_memory;

            /* Set the callback args passed to the Non-secure callback. */
            p_ctrl->p_callback_memory->channel   = p_ctrl->channel;
            p_ctrl->p_callback_memory->p_context = p_ctrl->p_context;

            /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
            icu_prv_ns_callback p_callback = (icu_prv_ns_callback) (p_ctrl->p_callback);
            p_callback(p_ctrl->p_callback_memory);

            /* Restore the state of p_callback_args. */
            *p_ctrl->p_callback_memory = args;
        }

#else

        /* Set data to identify callback to user, then call user callback. */
        external_irq_callback_args_t args;
        args.channel   = p_ctrl->channel;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
#endif
    }

#if BSP_FEATURE_ICU_HAS_IELSR
    if (level_irq)
    {
        /* Clear the IR bit after calling the user callback so that if the condition is cleared the ISR will not
         * be called again. */
        R_BSP_IrqStatusClear(irq);
    }
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
