/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * @file drv_gpio.c
 * @brief GPIO driver implementation for RT-Thread
 * 
 * This file implements the GPIO (General Purpose Input/Output) driver for HPMicro
 * microcontrollers, providing a complete interface between RT-Thread's pin framework
 * and the HPM GPIO hardware.
 * 
 * Features:
 * - Support for multiple GPIO ports (A, B, C, D, E, F, V, W, X, Y, Z)
 * - Configurable pin modes (input, output, pull-up, pull-down, open-drain)
 * - Interrupt-driven GPIO operations with configurable triggers
 * - Pin naming convention: P<PORT><INDEX> (e.g., PA00, PZ03)
 * - Configurable interrupt priorities
 * - Real-time pin state monitoring
 * 
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   HPMicro     First version
 * 2022-07-28   HPMicro     Fixed compiling warnings
 * 2023-05-08   HPMicro     Adapt RT-Thread V5.0.0
 * 2023-08-15   HPMicro     Enable pad loopback feature
 * 2024-01-08   HPMicro     Implemented pin_get
 * 2024-04-17   HPMicro     Refined pin irq implementation
 * 2024-07-03   HPMicro     Determined the existence of GPIO via GPIO_DO_GPIOx macro
 * 2025-09-01   HPMicro     Revised the code, reduced repetitive codes, added comments
 * 2025-12-04   HPMicro     Changed the return type of hpm_pin_read from int to rt_ssize_t
 */

#include "rtconfig.h"

#ifdef BSP_USING_GPIO

/* RT-Thread includes */
#include <rthw.h>
#include <rtdevice.h>

/* HPM SDK includes */
#include "drv_gpio.h"
#include "hpm_gpio_drv.h"
#include "hpm_gpiom_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_soc_feature.h"
#include <rtthread.h>
#include "hpm_soc.h"

/* ============================================================================
 * Configuration Macros
 * ============================================================================ */

/* 
 * GPIO Pin Interrupt Header Declaration Macro
 * Creates a static array of pin interrupt headers for a specific GPIO port.
 * Each GPIO port can have up to 32 pins, each with its own interrupt handler.
 * 
 * @param port GPIO port letter (A, B, C, D, E, F, V, W, X, Y, Z)
 */
#define GPIO_PIN_HDR_DECLARE(port) \
    static struct rt_pin_irq_hdr hpm_gpio0_##port##_pin_hdr[32]

/* 
 * GPIO Interrupt Priority Configuration Macro
 * Handles the configuration of interrupt priority for GPIO controllers.
 * If a specific priority is defined in the board configuration, it will be used;
 * otherwise, a default priority of 1 is applied.
 */
#ifdef BSP_GPIO_IRQ_PRIORITY
#define GPIO_IRQ_PRIORITY_VAL BSP_GPIO_IRQ_PRIORITY
#else
#define GPIO_IRQ_PRIORITY_VAL 1
#endif

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/* 
 * GPIO Interrupt Mapping Entry Macro
 * Creates an entry in the GPIO interrupt mapping table that associates
 * GPIO port indices with their corresponding interrupt numbers, priorities,
 * and pin interrupt header tables.
 * 
 * @param port GPIO port letter (A, B, C, D, E, F, V, W, X, Y, Z)
 */
#define GPIO_IRQ_MAP_ENTRY(port) \
    { \
        GPIO_IE_GPIO##port, \
        IRQn_GPIO0_##port, \
        GPIO_IRQ_PRIORITY_VAL, \
        hpm_gpio0_##port##_pin_hdr \
    }

/* 
 * GPIO ISR Definition Macro
 * Creates the interrupt service routine function and its declaration
 * for a specific GPIO port. The ISR handles pin-level interrupts
 * and calls the common GPIO interrupt handler.
 * 
 * @param port GPIO port letter (A, B, C, D, E, F, V, W, X, Y, Z)
 */
#define GPIO_ISR_DEFINE(port) \
    SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_##port, gpio##port##_isr) \
    void gpio##port##_isr(void) \
    { \
        hpm_gpio_isr(GPIO_IF_GPIO##port, HPM_GPIO0); \
    }
#else
/**
 * @brief GPIO interrupt parameter structure
 * 
 * This structure used for passing parameters to the GPIO interrupt service routine.
 */
typedef struct
{
    uint32_t gpio_idx;                    /**< GPIO port index (0-11 for A-Z) */
    GPIO_Type *base;
} gpio_irq_param_t;

/* 
 * GPIO Interrupt Mapping Entry Macro
 * Creates an entry in the GPIO interrupt mapping table that associates
 * GPIO port indices with their corresponding interrupt numbers, priorities,
 * and pin interrupt header tables.
 * 
 * @param port GPIO port letter (A, B, C, D, E, F, V, W, X, Y, Z)
 */
#define GPIO_IRQ_MAP_ENTRY(port) \
    { \
        GPIO_IE_GPIO##port, \
        IRQn_GPIO0_##port, \
        GPIO_IRQ_PRIORITY_VAL, \
        hpm_gpio0_##port##_pin_hdr, \
        &(gpio_irq_param_t){ \
            .gpio_idx = GPIO_IE_GPIO##port, \
            .base     = HPM_GPIO0 \
        } \
    }
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/* ============================================================================
 * Data Structures
 * ============================================================================ */

/**
 * @brief GPIO interrupt mapping structure
 * 
 * This structure maps GPIO port indices to their corresponding interrupt
 * configuration and pin interrupt handler tables.
 */
typedef struct
{
    uint32_t gpio_idx;                    /**< GPIO port index (0-11 for A-Z) */
    uint32_t irq_num;                     /**< Interrupt number for this GPIO port */
    uint8_t irq_priority;                 /**< Interrupt priority for this GPIO port */
    struct rt_pin_irq_hdr *pin_irq_tbl;   /**< Pointer to pin interrupt handler table */
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
    gpio_irq_param_t *irq_param;          /**< Pointer to GPIO interrupt parameter structure */
#endif
} gpio_irq_map_t;

/* ============================================================================
 * GPIO Device Instances
 * ============================================================================ */

/* GPIO Pin Interrupt Header Declarations - created for each enabled GPIO port */
#ifdef GPIO_DO_GPIOA
GPIO_PIN_HDR_DECLARE(A);
#endif
#ifdef GPIO_DO_GPIOB
GPIO_PIN_HDR_DECLARE(B);
#endif
#ifdef GPIO_DO_GPIOC
GPIO_PIN_HDR_DECLARE(C);
#endif
#ifdef GPIO_DO_GPIOD
GPIO_PIN_HDR_DECLARE(D);
#endif
#ifdef GPIO_DO_GPIOE
GPIO_PIN_HDR_DECLARE(E);
#endif
#ifdef GPIO_DO_GPIOF
GPIO_PIN_HDR_DECLARE(F);
#endif
#ifdef GPIO_DO_GPIOV
GPIO_PIN_HDR_DECLARE(V);
#endif
#ifdef GPIO_DO_GPIOW
GPIO_PIN_HDR_DECLARE(W);
#endif
#ifdef GPIO_DO_GPIOX
GPIO_PIN_HDR_DECLARE(X);
#endif
#ifdef GPIO_DO_GPIOY
GPIO_PIN_HDR_DECLARE(Y);
#endif
#ifdef GPIO_DO_GPIOZ
GPIO_PIN_HDR_DECLARE(Z);
#endif

/* GPIO Interrupt Mapping Table - maps GPIO ports to their interrupt configuration */
static const gpio_irq_map_t hpm_gpio_irq_map[] = {
#ifdef GPIO_DO_GPIOA
    GPIO_IRQ_MAP_ENTRY(A),
#endif
#ifdef GPIO_DO_GPIOB
    GPIO_IRQ_MAP_ENTRY(B),
#endif
#ifdef GPIO_DO_GPIOC
    GPIO_IRQ_MAP_ENTRY(C),
#endif
#ifdef GPIO_DO_GPIOD
    GPIO_IRQ_MAP_ENTRY(D),
#endif
#ifdef GPIO_DO_GPIOE
    GPIO_IRQ_MAP_ENTRY(E),
#endif
#ifdef GPIO_DO_GPIOF
    GPIO_IRQ_MAP_ENTRY(F),
#endif
#ifdef GPIO_DO_GPIOV
    GPIO_IRQ_MAP_ENTRY(V),
#endif
#ifdef GPIO_DO_GPIOW
    GPIO_IRQ_MAP_ENTRY(W),
#endif
#ifdef GPIO_DO_GPIOX
    GPIO_IRQ_MAP_ENTRY(X),
#endif
#ifdef GPIO_DO_GPIOY
    GPIO_IRQ_MAP_ENTRY(Y),
#endif
#ifdef GPIO_DO_GPIOZ
    GPIO_IRQ_MAP_ENTRY(Z),
#endif
};

/* ============================================================================
 * Function Implementations
 * ============================================================================ */

/**
 * @brief Lookup pin interrupt header table for a given pin
 * 
 * This function finds the appropriate pin interrupt header table for a given
 * pin number by extracting the GPIO port index and searching the interrupt
 * mapping table.
 * 
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @return Pointer to pin interrupt header table, or RT_NULL if not found
 */
static struct rt_pin_irq_hdr *lookup_pin_irq_hdr_tbl(rt_base_t pin)
{
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = RT_NULL;
    uint32_t gpio_idx = pin >> 5;  /* Extract GPIO port index (upper bits) */

    /* Search through the GPIO interrupt mapping table */
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            pin_irq_hdr_tbl = hpm_gpio_irq_map[i].pin_irq_tbl;
            break;
        }
    }
    return pin_irq_hdr_tbl;
}

/**
 * @brief Get interrupt number for a GPIO port
 * 
 * This function retrieves the interrupt number associated with a specific
 * GPIO port index by searching the interrupt mapping table.
 * 
 * @param [in] gpio_idx GPIO port index (0-11 for A-Z)
 * @return Interrupt number, or -1 if not found
 */
static int hpm_get_gpio_irq_num(uint32_t gpio_idx)
{
    int irq_num = -1;

    /* Search through the GPIO interrupt mapping table */
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            irq_num = hpm_gpio_irq_map[i].irq_num;
            break;
        }
    }
    return irq_num;
}

/**
 * @brief Get interrupt priority for a GPIO port
 * 
 * This function retrieves the interrupt priority associated with a specific
 * GPIO port index by searching the interrupt mapping table.
 * 
 * @param [in] gpio_idx GPIO port index (0-11 for A-Z)
 * @return Interrupt priority, or -1 if not found
 */
static int hpm_get_gpio_irq_priority(uint32_t gpio_idx)
{
    int irq_priority = -1;

    /* Search through the GPIO interrupt mapping table */
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            irq_priority = hpm_gpio_irq_map[i].irq_priority;
            break;
        }
    }
    return irq_priority;
}

/**
 * @brief GPIO interrupt service routine
 * 
 * This function is called when a GPIO interrupt occurs. It handles pin-level
 * interrupts by checking which pins have triggered interrupts, clearing the
 * interrupt flags, and calling the appropriate user-defined interrupt handlers.
 * 
 * @param [in] gpio_idx GPIO port index that triggered the interrupt
 * @param [in] base GPIO hardware base address
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_gpio_isr(uint32_t gpio_idx, GPIO_Type *base)
#else
static void hpm_gpio_isr(int vector, gpio_irq_param_t *param)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
    uint32_t gpio_idx = param->gpio_idx;
    GPIO_Type *base = param->base;
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    /* Lookup the Pin IRQ Header Table for this GPIO port */

    struct rt_pin_irq_hdr *pin_irq_hdr = RT_NULL;
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            pin_irq_hdr = hpm_gpio_irq_map[i].pin_irq_tbl;
            break;
        }
    }

    /* Check each pin in the GPIO port for interrupt flags */
    for(uint32_t pin_idx = 0; pin_idx < 32; pin_idx++)
    {
        if (gpio_check_pin_interrupt_flag(base, gpio_idx, pin_idx))
        {
            /* Clear the interrupt flag for this pin */
            gpio_clear_pin_interrupt_flag(base, gpio_idx, pin_idx);

            /* Call user-defined interrupt handler if registered */
            if (pin_irq_hdr[pin_idx].hdr != RT_NULL)
            {
                pin_irq_hdr[pin_idx].hdr(pin_irq_hdr[pin_idx].args);
            }
        }
    }
}

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/* ============================================================================
 * GPIO Interrupt Service Routines
 * ============================================================================ */

/* GPIOA ISR - created if GPIO_DO_GPIOA is enabled */
#ifdef GPIO_DO_GPIOA
GPIO_ISR_DEFINE(A);
#endif

/* GPIOB ISR - created if GPIO_DO_GPIOB is enabled */
#ifdef GPIO_DO_GPIOB
GPIO_ISR_DEFINE(B);
#endif

/* GPIOC ISR - created if GPIO_DO_GPIOC is enabled */
#ifdef GPIO_DO_GPIOC
GPIO_ISR_DEFINE(C);
#endif

/* GPIOD ISR - created if GPIO_DO_GPIOD is enabled */
#ifdef GPIO_DO_GPIOD
GPIO_ISR_DEFINE(D);
#endif

/* GPIOE ISR - created if GPIO_DO_GPIOE is enabled */
#ifdef GPIO_DO_GPIOE
GPIO_ISR_DEFINE(E);
#endif

/* GPIOF ISR - created if GPIO_DO_GPIOF is enabled */
#ifdef GPIO_DO_GPIOF
GPIO_ISR_DEFINE(F);
#endif

/* GPIOV ISR - created if GPIO_DO_GPIOV is enabled */
#ifdef GPIO_DO_GPIOV
GPIO_ISR_DEFINE(V);
#endif

/* GPIOW ISR - created if GPIO_DO_GPIOW is enabled */
#ifdef GPIO_DO_GPIOW
GPIO_ISR_DEFINE(W);
#endif

/* GPIOX ISR - created if GPIO_DO_GPIOX is enabled */
#ifdef GPIO_DO_GPIOX
GPIO_ISR_DEFINE(X);
#endif

/* GPIOY ISR - created if GPIO_DO_GPIOY is enabled */
#ifdef GPIO_DO_GPIOY
GPIO_ISR_DEFINE(Y);
#endif

/* GPIOZ ISR - created if GPIO_DO_GPIOZ is enabled */
#ifdef GPIO_DO_GPIOZ
GPIO_ISR_DEFINE(Z);
#endif
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/**
 * @brief Get Pin index from name string
 * 
 * This function converts a pin name string to a pin index number.
 * The pin naming convention follows the pattern: P<PORT><INDEX>
 * 
 * Supported formats:
 * - PA00 to PF99: GPIO ports A-F with pin indices 00-99
 * - PV00 to PZ99: GPIO ports V-Z with pin indices 00-99
 * 
 * Examples:
 * - "PA00" -> pin index 0 (GPIO A, pin 0)
 * - "PZ03" -> pin index 355 (GPIO Z, pin 3)
 * - "PB15" -> pin index 47 (GPIO B, pin 15)
 *
 * @param [in] name Pin name string (must be exactly 4 characters)
 * @return Pin index number, or -RT_EINVAL if name is invalid
 */
static rt_base_t hpm_pin_get(const char *name)
{
    /* Validate pin name format: P<PORT><INDEX> (4 characters total) */
    if (!(  (rt_strlen(name) == 4) &&                    /* Exactly 4 characters */
            (name[0] == 'P') &&                          /* First character is 'P' */
            ((('A' <= name[1]) && (name[1] <= 'F')) ||   /* Port A-F or V-Z */
             (('V' <= name[1]) && (name[1] <= 'Z'))) &&
            (('0' <= name[2]) && (name[2] <= '9')) &&    /* Third character is digit */
            (('0' <= name[3]) && (name[3] <= '9'))       /* Fourth character is digit */
        ))
    {
        return -RT_EINVAL;
    }

    /* Calculate GPIO port index */
    uint32_t gpio_idx = (name[1] <= 'F') ? (name[1] - 'A') : (11 + name[1] - 'V');
    
    /* Calculate pin index within the port */
    uint32_t pin_idx = (uint32_t)(name[2] - '0') * 10 + (name[3] - '0');
    
    /* Return combined pin index (gpio_idx * 32 + pin_idx) */
    return (gpio_idx * 32 + pin_idx);
}

/**
 * @brief Configure GPIO pin mode
 * 
 * This function configures a GPIO pin for the specified mode, including
 * direction (input/output), pull-up/pull-down resistors, and open-drain settings.
 * It also configures the pin controller and pad settings.
 * 
 * @param [in] dev Device pointer (unused)
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @param [in] mode Pin mode (PIN_MODE_*)
 */
static void hpm_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;  /* Extract GPIO port index */
    uint32_t pin_idx = pin & 0x1FU; /* Extract pin index within port */

    /* Configure pin controller to use GPIO0 */
    gpiom_set_pin_controller(HPM_GPIOM, gpio_idx, pin_idx, gpiom_soc_gpio0);

    /* Clear function control register */
    HPM_IOC->PAD[pin].FUNC_CTL = 0;

    /* Handle special cases for specific GPIO ports */
    switch (gpio_idx)
    {
    case GPIO_DI_GPIOY :
        /* GPIOY requires special PIOC configuration */
        HPM_PIOC->PAD[pin].FUNC_CTL = 3;
        break;
#ifdef GPIO_DI_GPIOZ
    case GPIO_DI_GPIOZ :
#ifdef HPM_BIOC
        /* GPIOZ requires special BIOC configuration if available */
        HPM_BIOC->PAD[pin].FUNC_CTL = 3;
#endif
        break;
#endif
    default :
        break;
    }

    /* Configure pin mode and pad settings */
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        /* Configure as output with push-pull driver */
        gpio_set_pin_output(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL &=  ~(IOC_PAD_PAD_CTL_PS_MASK | IOC_PAD_PAD_CTL_PE_MASK | IOC_PAD_PAD_CTL_OD_MASK);
        break;
        
    case PIN_MODE_INPUT:
        /* Configure as input with no pull resistors */
        gpio_set_pin_input(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL &= ~(IOC_PAD_PAD_CTL_PS_MASK | IOC_PAD_PAD_CTL_PE_MASK);
        break;
        
    case PIN_MODE_INPUT_PULLDOWN:
        /* Configure as input with pull-down resistor */
        gpio_set_pin_input(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL = (HPM_IOC->PAD[pin].PAD_CTL & ~IOC_PAD_PAD_CTL_PS_MASK) | IOC_PAD_PAD_CTL_PE_SET(1);
        break;
        
    case PIN_MODE_INPUT_PULLUP:
        /* Configure as input with pull-up resistor */
        gpio_set_pin_input(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        break;
        
    case PIN_MODE_OUTPUT_OD:
        /* Configure as output with open-drain driver */
        gpio_set_pin_output(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL = (HPM_IOC->PAD[pin].PAD_CTL & ~(IOC_PAD_PAD_CTL_PS_MASK | IOC_PAD_PAD_CTL_PE_MASK)) | IOC_PAD_PAD_CTL_OD_SET(1);
        break;
        
    default:
        /* Invalid mode - no action taken */
        break;
    }
    
    /* Enable pad loopback feature */
    HPM_IOC->PAD[pin].FUNC_CTL = IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
}

/**
 * @brief Read GPIO pin state
 * 
 * This function reads the current state (high/low) of a GPIO pin.
 * 
 * @param [in] dev Device pointer (unused)
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @return Pin state: 1 for high, 0 for low
 */
static rt_ssize_t hpm_pin_read(rt_device_t dev, rt_base_t pin)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;  /* Extract GPIO port index */
    uint32_t pin_idx = pin & 0x1FU; /* Extract pin index within port */

    return (rt_ssize_t) gpio_read_pin(HPM_GPIO0, gpio_idx, pin_idx);
}

/**
 * @brief Write GPIO pin state
 * 
 * This function sets the output state of a GPIO pin to high or low.
 * 
 * @param [in] dev Device pointer (unused)
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @param [in] value Pin state: 1 for high, 0 for low
 */
static void hpm_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;  /* Extract GPIO port index */
    uint32_t pin_idx = pin & 0x1FU; /* Extract pin index within port */

    gpio_write_pin(HPM_GPIO0, gpio_idx, pin_idx, value);
}

/**
 * @brief Attach interrupt handler to GPIO pin
 * 
 * This function registers an interrupt handler for a specific GPIO pin.
 * The handler will be called when the pin triggers an interrupt based on
 * the specified mode (rising edge, falling edge, high level, low level).
 * 
 * @param [in] device Device pointer (unused)
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @param [in] mode Interrupt mode (PIN_IRQ_MODE_*)
 * @param [in] hdr Interrupt handler function pointer
 * @param [in] args Arguments to pass to the interrupt handler
 * @retval RT_EOK Interrupt handler attached successfully
 * @retval -RT_EINVAL Invalid pin number
 */
static rt_err_t hpm_pin_attach_irq(struct rt_device *device,
                                   rt_base_t pin,
                                   rt_uint8_t mode,
                                   void (*hdr)(void *args),
                                   void *args)
{
    /* Lookup the pin interrupt header table for this pin */
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = lookup_pin_irq_hdr_tbl(pin);
    if (pin_irq_hdr_tbl == RT_NULL)
    {
        return -RT_EINVAL;
    }

    /* Disable interrupts during registration to ensure atomic operation */
    rt_base_t level = rt_hw_interrupt_disable();
    uint32_t pin_idx = pin & 0x1FUL;  /* Extract pin index within port */
    
    /* Register the interrupt handler */
    pin_irq_hdr_tbl[pin_idx].pin = pin;
    pin_irq_hdr_tbl[pin_idx].hdr = hdr;
    pin_irq_hdr_tbl[pin_idx].mode = mode;
    pin_irq_hdr_tbl[pin_idx].args = args;
    
    /* Re-enable interrupts */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @brief Detach interrupt handler from GPIO pin
 * 
 * This function removes the interrupt handler registration for a specific GPIO pin.
 * After calling this function, the pin will no longer trigger interrupts.
 * 
 * @param [in] device Device pointer (unused)
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @retval RT_EOK Interrupt handler detached successfully
 * @retval -RT_EINVAL Invalid pin number
 */
static rt_err_t hpm_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    /* Lookup the pin interrupt header table for this pin */
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = lookup_pin_irq_hdr_tbl(pin);
    if (pin_irq_hdr_tbl == RT_NULL)
    {
        return -RT_EINVAL;
    }
    
    /* Disable interrupts during deregistration to ensure atomic operation */
    rt_base_t level = rt_hw_interrupt_disable();
    uint32_t pin_idx = pin & 0x1FUL;  /* Extract pin index within port */
    
    /* Clear the interrupt handler registration */
    pin_irq_hdr_tbl[pin_idx].pin = -1;
    pin_irq_hdr_tbl[pin_idx].hdr = RT_NULL;
    pin_irq_hdr_tbl[pin_idx].mode = 0;
    pin_irq_hdr_tbl[pin_idx].args = RT_NULL;
    
    /* Re-enable interrupts */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @brief Enable or disable GPIO pin interrupt
 * 
 * This function enables or disables interrupt generation for a specific GPIO pin.
 * When enabling, it configures the interrupt trigger mode and enables the hardware
 * interrupt. When disabling, it disables the hardware interrupt.
 * 
 * @param [in] device Device pointer (unused)
 * @param [in] pin Pin number (encoded as gpio_idx * 32 + pin_idx)
 * @param [in] enabled Enable/disable flag (PIN_IRQ_ENABLE or PIN_IRQ_DISABLE)
 * @retval RT_EOK Operation completed successfully
 * @retval -RT_EINVAL Invalid pin number or enable flag
 */
static rt_err_t hpm_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;  /* Extract GPIO port index */
    uint32_t pin_idx = pin & 0x1FU; /* Extract pin index within port */

    /* Lookup the pin interrupt header table for this pin */
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = lookup_pin_irq_hdr_tbl(pin);
    if (pin_irq_hdr_tbl == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        /* Configure interrupt trigger mode based on registered mode */
        gpio_interrupt_trigger_t trigger;
        switch(pin_irq_hdr_tbl[pin_idx].mode)
        {
        case PIN_IRQ_MODE_RISING:
            trigger = gpio_interrupt_trigger_edge_rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            trigger = gpio_interrupt_trigger_edge_falling;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            trigger = gpio_interrupt_trigger_level_high;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            trigger = gpio_interrupt_trigger_level_low;
            break;
        default:
            trigger = gpio_interrupt_trigger_edge_rising;
            break;
        }
        
        /* Configure and enable the pin interrupt */
        gpio_config_pin_interrupt(HPM_GPIO0, gpio_idx, pin_idx, trigger);
        
        /* Get interrupt number and priority for this GPIO port */
        rt_uint32_t irq_num = hpm_get_gpio_irq_num(gpio_idx);
        rt_uint32_t irq_priority = hpm_get_gpio_irq_priority(gpio_idx);
        
        /* Enable pin interrupt and system interrupt */
        gpio_enable_pin_interrupt(HPM_GPIO0, gpio_idx, pin_idx);
        intc_m_enable_irq_with_priority(irq_num, irq_priority);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        /* Disable the pin interrupt */
        gpio_disable_pin_interrupt(HPM_GPIO0, gpio_idx, pin_idx);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

/* ============================================================================
 * RT-Thread Interface Structures
 * ============================================================================ */

/* RT-Thread pin operations structure - defines the interface between RT-Thread and this driver */
const static struct rt_pin_ops hpm_pin_ops = {
        .pin_mode = hpm_pin_mode,         /* Configure pin mode */
        .pin_write = hpm_pin_write,       /* Write pin state */
        .pin_read = hpm_pin_read,         /* Read pin state */
        .pin_attach_irq = hpm_pin_attach_irq,   /* Attach interrupt handler */
        .pin_detach_irq = hpm_pin_detach_irq,   /* Detach interrupt handler */
        .pin_irq_enable = hpm_pin_irq_enable,   /* Enable/disable interrupt */
        .pin_get = hpm_pin_get,           /* Get pin index from name */
};

/* ============================================================================
 * Driver Initialization
 * ============================================================================ */

/**
 * @brief Initialize GPIO driver
 * 
 * This function initializes the GPIO driver and registers it with the
 * RT-Thread device framework. It sets up the pin operations structure
 * and makes the GPIO functionality available to the system.
 * 
 * @retval RT_EOK Initialization successful
 * @retval -RT_ERROR Initialization failed
 */
int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    /* Register the pin device with RT-Thread */
    ret = rt_device_pin_register("pin", &hpm_pin_ops, RT_NULL);

#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        /* Register GPIO device to irq table */
        rt_hw_interrupt_install(hpm_gpio_irq_map[i].irq_num, (rt_isr_handler_t)hpm_gpio_isr, hpm_gpio_irq_map[i].irq_param, "GPIO");
    }
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

    return ret;
}

/* Register initialization function to be called during system startup */
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* BSP_USING_GPIO */
