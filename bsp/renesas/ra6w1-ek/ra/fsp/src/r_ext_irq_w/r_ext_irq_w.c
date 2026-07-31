/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ext_irq_w.h"
#include "r_ext_irq_w_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "EXT_IRQ" in ASCII, used to determine if channel is open. */
#define EXT_IRQ_W_OPEN                 (0x00494355U)

#define EXT_IRQ_W_IRQMD_OFFSET         (0)

#define EXT_IRQ_W_PORT0_PINBIT_MASK    (0x3FFF)
#define EXT_IRQ_W_PORT1_PINBIT_MASK    (0xFFFF)

#define EXT_IRQ_W_WKUP_PINBIT_MASK     (0x7FF)

#define EXT_IRQ_W_MAX_CHANNEL          (30)
#define EXT_IRQ_W_MAX_IO_PORT          (BSP_IO_PORT_MAX - 1)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * ext_irq_w_prv_ns_callback)(external_irq_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile ext_irq_w_prv_ns_callback)(external_irq_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void r_ext_irq_w_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static uint32_t gs_enabled_pin_bit[EXT_IRQ_W_MAX_IO_PORT] = {0, 0, };

static ext_irq_w_instance_ctrl_t * volatile gp_ext_irq_w_ctrls[EXT_IRQ_W_MAX_CHANNEL];

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* EXT_IRQ implementation of External IRQ API. */
const external_irq_api_t g_external_irq_on_ext_irq_w =
{
    .open        = R_EXT_IRQ_W_ExternalIrqOpen,
    .enable      = R_EXT_IRQ_W_ExternalIrqEnable,
    .disable     = R_EXT_IRQ_W_ExternalIrqDisable,
    .callbackSet = R_EXT_IRQ_W_ExternalIrqCallbackSet,
    .close       = R_EXT_IRQ_W_ExternalIrqClose,
};

/*******************************************************************************************************************//**
 * @addtogroup EXT_IRQ_W
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
fsp_err_t R_EXT_IRQ_W_ExternalIrqOpen (external_irq_ctrl_t * const p_api_ctrl, external_irq_cfg_t const * const p_cfg)
{
    ext_irq_w_instance_ctrl_t * p_ctrl = (ext_irq_w_instance_ctrl_t *) p_api_ctrl;

#if EXT_IRQ_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif

    FSP_ERROR_RETURN(EXT_IRQ_W_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Verify the configuration trigger source is correct */
    FSP_ERROR_RETURN((EXTERNAL_IRQ_TRIG_FALLING == p_cfg->trigger) ||
                     (EXTERNAL_IRQ_TRIG_RISING == p_cfg->trigger) ||
                     (EXTERNAL_IRQ_TRIG_LEVEL_LOW == p_cfg->trigger) ||
                     (EXTERNAL_IRQ_TRIG_LEVEL_HIGH == p_cfg->trigger),
                     FSP_ERR_UNSUPPORTED);

    FSP_ERROR_RETURN(0 != ((1U << p_cfg->channel) & BSP_FEATURE_ICU_IRQ_CHANNELS_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Callback must be used with a valid interrupt priority otherwise it will never be called. */
    if (p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(BSP_IRQ_DISABLED != p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);
    }

    /* Channel must be free */
    FSP_ERROR_RETURN(gp_ext_irq_w_ctrls[p_cfg->channel] == NULL, FSP_ERR_INVALID_CHANNEL);

    p_ctrl->irq_pin = ((ext_irq_w_extended_cfg_t *) p_cfg->p_extend)->irq_pin;

    uint8_t  port    = (uint8_t) ((p_ctrl->irq_pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET);
    uint8_t  pin     = (uint8_t) (p_ctrl->irq_pin & BSP_IO_PIN_BITS);
    uint32_t pin_bit = 0;

    pin_bit = 1 << pin;

    if ((BSP_IO_PORT_00 == port) && (0 != (EXT_IRQ_W_PORT0_PINBIT_MASK & pin_bit)))
    {
        p_ctrl->irq = GPIO_P0_IRQn;
    }
    else if ((BSP_IO_PORT_01 == port) && (0 != (EXT_IRQ_W_PORT1_PINBIT_MASK & pin_bit)))
    {
        p_ctrl->irq = GPIO_P1_IRQn;
    }
    else
    {
        FSP_RETURN(FSP_ERR_UNSUPPORTED);
    }

    /* Initialize control block. */
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;
    p_ctrl->channel    = p_cfg->channel;

    switch (p_cfg->trigger)
    {
        case EXTERNAL_IRQ_TRIG_FALLING:
        {
            BSP_IO_PXX_POL_REG(port)  = BSP_IO_PXX_POL_REG(port) | pin_bit;  /* give an event if that input goes low */
            BSP_IO_PXX_SEL1_REG(port) = BSP_IO_PXX_SEL1_REG(port) | pin_bit; /* Edge sensitive */
            break;
        }

        case EXTERNAL_IRQ_TRIG_RISING:
        {
            BSP_IO_PXX_POL_REG(port)  = BSP_IO_PXX_POL_REG(port) & ~pin_bit; /* give an event if that input goes high */
            BSP_IO_PXX_SEL1_REG(port) = BSP_IO_PXX_SEL1_REG(port) | pin_bit; /* Edge sensitive */
            break;
        }

        case EXTERNAL_IRQ_TRIG_LEVEL_LOW:
        {
            BSP_IO_PXX_POL_REG(port)  = BSP_IO_PXX_POL_REG(port) | pin_bit;   /* give an event if that input goes low */
            BSP_IO_PXX_SEL1_REG(port) = BSP_IO_PXX_SEL1_REG(port) & ~pin_bit; /* Level sensitive */
            break;
        }

        case EXTERNAL_IRQ_TRIG_LEVEL_HIGH:
        {
            BSP_IO_PXX_POL_REG(port)  = BSP_IO_PXX_POL_REG(port) & ~pin_bit;  /* give an event if that input goes high */
            BSP_IO_PXX_SEL1_REG(port) = BSP_IO_PXX_SEL1_REG(port) & ~pin_bit; /* Level sensitive */
            break;
        }

        default:
        {
            ;                          /* do nothing */
        }
    }

    R_BSP_IrqCfg(p_ctrl->irq, p_cfg->ipl, p_ctrl);

    gp_ext_irq_w_ctrls[p_ctrl->channel] = p_ctrl;

    /* Mark the control block as open */
    p_ctrl->open = EXT_IRQ_W_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable external interrupt for specified channel at NVIC. Implements @ref external_irq_api_t::enable.
 *
 * @retval FSP_SUCCESS                 Interrupt Enabled successfully.
 * @retval FSP_ERR_ASSERTION           The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_EXT_IRQ_W_ExternalIrqEnable (external_irq_ctrl_t * const p_api_ctrl)
{
    ext_irq_w_instance_ctrl_t * p_ctrl = (ext_irq_w_instance_ctrl_t *) p_api_ctrl;

#if EXT_IRQ_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
#endif

    FSP_ERROR_RETURN(EXT_IRQ_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    uint8_t  port    = (uint8_t) ((p_ctrl->irq_pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET);
    uint8_t  pin     = (uint8_t) (p_ctrl->irq_pin & BSP_IO_PIN_BITS);
    uint32_t pin_bit = 0;

    pin_bit = 1 << pin;

    if (pin_bit == (BSP_IO_PXX_INT_STS_REG(port) & pin_bit))
    {
        BSP_IO_PXX_INT_CLR_REG(port) = pin_bit;
    }

    BSP_IO_PXX_SEL_REG(port) = BSP_IO_PXX_SEL_REG(port) | pin_bit;

    /* Clear the interrupt status and Pending bits, before the interrupt is enabled. */
    if (0 == gs_enabled_pin_bit[port])
    {
        R_BSP_IrqEnable(p_ctrl->irq);
    }

    gs_enabled_pin_bit[port] = gs_enabled_pin_bit[port] | pin_bit;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable external interrupt for specified channel at NVIC. Implements @ref external_irq_api_t::disable.
 *
 * @retval FSP_SUCCESS                 Interrupt disabled successfully.
 * @retval FSP_ERR_ASSERTION           The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_EXT_IRQ_W_ExternalIrqDisable (external_irq_ctrl_t * const p_api_ctrl)
{
    ext_irq_w_instance_ctrl_t * p_ctrl = (ext_irq_w_instance_ctrl_t *) p_api_ctrl;

#if EXT_IRQ_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
#endif

    FSP_ERROR_RETURN(EXT_IRQ_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    uint8_t  port    = (uint8_t) ((p_ctrl->irq_pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET);
    uint8_t  pin     = (uint8_t) (p_ctrl->irq_pin & BSP_IO_PIN_BITS);
    uint32_t pin_bit = 0;

    pin_bit = 1 << pin;

    BSP_IO_PXX_SEL_REG(port) = BSP_IO_PXX_SEL_REG(port) & ~pin_bit;

    if (pin_bit == (BSP_IO_PXX_INT_STS_REG(port) & pin_bit))
    {
        BSP_IO_PXX_INT_CLR_REG(port) = pin_bit;
    }

    gs_enabled_pin_bit[port] = gs_enabled_pin_bit[port] & ~pin_bit;

    /* Disable the interrupt, and then clear the interrupt pending bits and interrupt status. */
    if (0 == gs_enabled_pin_bit[port])
    {
        R_BSP_IrqDisable(p_ctrl->irq);
    }

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
fsp_err_t R_EXT_IRQ_W_ExternalIrqCallbackSet (external_irq_ctrl_t * const p_api_ctrl,
                                              void (                    * p_callback)(
                                                  external_irq_callback_args_t *),
                                              void * const                         p_context,
                                              external_irq_callback_args_t * const p_callback_memory)
{
    ext_irq_w_instance_ctrl_t * p_ctrl = p_api_ctrl;

    FSP_PARAMETER_NOT_USED(p_callback_memory);

#if EXT_IRQ_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
#endif

    FSP_ERROR_RETURN(EXT_IRQ_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the external interrupt channel. Implements @ref external_irq_api_t::close.
 *
 * @retval     FSP_SUCCESS          Successfully closed.
 * @retval     FSP_ERR_ASSERTION    The parameter p_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN     The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_EXT_IRQ_W_ExternalIrqClose (external_irq_ctrl_t * const p_api_ctrl)
{
    ext_irq_w_instance_ctrl_t * p_ctrl = (ext_irq_w_instance_ctrl_t *) p_api_ctrl;

#if EXT_IRQ_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
#endif

    FSP_ERROR_RETURN(EXT_IRQ_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    uint8_t  port    = (uint8_t) ((p_ctrl->irq_pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET);
    uint8_t  pin     = (uint8_t) (p_ctrl->irq_pin & BSP_IO_PIN_BITS);
    uint32_t pin_bit = 0;

    pin_bit = 1 << pin;

    gs_enabled_pin_bit[port] = gs_enabled_pin_bit[port] & ~pin_bit;
    BSP_IO_PXX_SEL_REG(port) = BSP_IO_PXX_SEL_REG(port) & ~pin_bit;

    /* Cleanup. Disable interrupt */
    if (0 == gs_enabled_pin_bit[port])
    {
        /* Disable the interrupt, and then clear the interrupt pending bits and interrupt status. */
        R_BSP_IrqDisable(p_ctrl->irq);
        R_FSP_IsrContextSet(p_ctrl->irq, NULL);
    }

    p_ctrl->open = 0U;

    gp_ext_irq_w_ctrls[p_ctrl->channel] = NULL;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup EXT_IRQ_W)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * EXT_IRQ External Interrupt ISR.
 **********************************************************************************************************************/
void r_ext_irq_w_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq        = R_FSP_CurrentIrqGet();
    uint8_t   port       = 0;
    uint32_t  status_reg = 0;
    uint8_t   pin        = 0;
    uint32_t  pin_bit    = 0;

    if (GPIO_P0_IRQn == irq)
    {
        port = BSP_IO_PORT_00;
    }
    else if (GPIO_P1_IRQn == irq)
    {
        port = BSP_IO_PORT_01;
    }
    else
    {
        return;
    }

    status_reg = BSP_IO_PXX_INT_STS_REG(port);

    if (0 == status_reg)
    {
        /* Status is empty, but maybe this is wakeup from GPIO context */
        bsp_io_wakeup_pin_t wakeup_pin = R_BSP_WakeupSourcePinGet();

        if (wakeup_pin != 0)
        {
            /* Fake status based on the wakeup GPIO */
            status_reg = (1 << (bsp_prv_wakeup_pin_to_port_pin(wakeup_pin) & BSP_IO_PIN_BITS));
        }
        else
        {
            return;
        }
    }

    for (pin = 0; 0 != status_reg; pin++)
    {
        status_reg >>= 1;
    }

    pin_bit = (uint32_t) (1 << (pin - 1));

    BSP_IO_PXX_INT_CLR_REG(port) = pin_bit;

    uint32_t irq_pin = (uint32_t) (port << BSP_IO_PORT_OFFSET) | (uint32_t) (pin - 1);

    if (pin_bit == (gs_enabled_pin_bit[port] & pin_bit))
    {
        for (uint8_t channel = 0; channel < EXT_IRQ_W_MAX_CHANNEL; channel++)
        {
            if ((NULL != gp_ext_irq_w_ctrls[channel]) && (irq_pin == gp_ext_irq_w_ctrls[channel]->irq_pin) &&
                (NULL != gp_ext_irq_w_ctrls[channel]->p_callback))
            {
                /* Set data to identify callback to user, then call user callback. */
                external_irq_callback_args_t args;

                args.channel   = gp_ext_irq_w_ctrls[channel]->channel;
                args.p_context = gp_ext_irq_w_ctrls[channel]->p_context;
                gp_ext_irq_w_ctrls[channel]->p_callback(&args);

                break;
            }
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
