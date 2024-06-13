/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPIO_DRV_H
#define HPM_GPIO_DRV_H

#include "hpm_common.h"
#include "hpm_gpio_regs.h"
#include "hpm_soc_feature.h"

#ifndef PORT_PIN_COUNT
#define PORT_PIN_COUNT (32U)
#endif
#define GPIO_GET_PORT_INDEX(x) (x / PORT_PIN_COUNT)
#define GPIO_GET_PIN_INDEX(x)  (x % PORT_PIN_COUNT)

/**
 *
 * @brief GPIO driver APIs
 * @defgroup gpio_interface GPIO driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief Interrupt trigger type
 */
typedef enum gpio_interrupt_trigger {
    gpio_interrupt_trigger_level_high = 0,
    gpio_interrupt_trigger_level_low,
    gpio_interrupt_trigger_edge_rising,
    gpio_interrupt_trigger_edge_falling,
#if defined(GPIO_SOC_HAS_EDGE_BOTH_INTERRUPT) && (GPIO_SOC_HAS_EDGE_BOTH_INTERRUPT == 1)
    gpio_interrupt_trigger_edge_both,
#endif
} gpio_interrupt_trigger_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Read target pin level
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 *
 * @return Pin status mask
 */
static inline uint8_t gpio_read_pin(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    return (ptr->DI[port].VALUE & (1 << pin)) >> pin;
}

/**
 * @brief   Read target pin output state
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 *
 * @return Pin output state
 */
static inline uint32_t gpio_get_pin_output_status(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    return (ptr->DO[port].VALUE & (1 << pin)) >> pin;
}

/**
 * @brief   Toggle pin level
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
static inline void gpio_toggle_pin(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    ptr->DO[port].TOGGLE = 1 << pin;
}

/**
 * @brief   Write pin level
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 * @param high Pin level set to high when it is set to true
 */
static inline void gpio_write_pin(GPIO_Type *ptr, uint32_t port, uint8_t pin, uint8_t high)
{
    if (high) {
        ptr->DO[port].SET = 1 << pin;
    } else {
        ptr->DO[port].CLEAR = 1 << pin;
    }
}

/**
 * @brief   Set pin to input mode
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
static inline void gpio_set_pin_input(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    ptr->OE[port].CLEAR = 1 << pin;
}

/**
 * @brief   Set pin to output mode
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
static inline void gpio_set_pin_output(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    ptr->OE[port].SET = 1 << pin;
}

/**
 * @brief   Set pin to output mode with initial value
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 * @param initial Initial value
 */
void gpio_set_pin_output_with_initial(GPIO_Type *ptr, uint32_t port, uint8_t pin, uint8_t initial);

/**
 * @brief   Check specific pin interrupt status
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 *
 * @return true if interrupt flag is set
 */
static inline bool gpio_check_pin_interrupt_flag(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    return ptr->IF[port].VALUE & (1 << pin);
}

/**
 * @brief   Clear specific pin interrupt flag
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
static inline void gpio_clear_pin_interrupt_flag(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    ptr->IF[port].VALUE = 1 << pin;
}

/**
 * @brief   Check if specific pin interrupt is enabled or not
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 *
 * @return true if interrupt is enabled
 */
static inline bool gpio_check_pin_interrupt_enabled(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    return (ptr->IE[port].VALUE & (1 << pin)) == (uint32_t) (1 << pin);
}

/**
 * @brief  Enable interrupt for specific pin
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
static inline void gpio_enable_pin_interrupt(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    ptr->IE[port].SET = 1 << pin;
}

/**
 * @brief   Disable interrupt for specific pin
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
static inline void gpio_disable_pin_interrupt(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    ptr->IE[port].CLEAR = 1 << pin;
}

/**
 * @brief   Check interrupt flag of specific pin and clear if it is set
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 *
 * @return true if the interrupt flag is set and cleared
 * @return false if the interrupt flag is not set
 */
static inline bool gpio_check_clear_interrupt_flag(GPIO_Type *ptr, uint32_t port, uint8_t pin)
{
    if (!gpio_check_pin_interrupt_flag(ptr, port, pin)) {
        return false;
    }
    gpio_clear_pin_interrupt_flag(ptr, port, pin);
    return true;
}


/**
 * @brief   Read all pins level on specific port
 *
 * @param ptr GPIO base address
 * @param port Port index
 *
 * @return Port pin level status
 */
static inline uint32_t gpio_read_port(GPIO_Type *ptr, uint32_t port)
{
    return ptr->DI[port].VALUE;
}

/**
 * @brief   Toggle port with specific pin mask
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask pins to be toggled
 */
static inline void gpio_toggle_port_with_mask(GPIO_Type *ptr, uint32_t port, uint32_t mask)
{
    ptr->DO[port].TOGGLE = mask;
}

/**
 * @brief   Write specific port with value
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param value Value to be written
 */
static inline void gpio_write_port(GPIO_Type *ptr, uint32_t port, uint32_t value)
{
    ptr->DO[port].VALUE = value;
}

/**
 * @brief   Set spcific port pin high according to the given mask
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of pins to be set to low
 */
static inline void gpio_set_port_low_with_mask(GPIO_Type *ptr, uint32_t port, uint32_t mask)
{
    ptr->DO[port].CLEAR = mask;
}

/**
 * @brief   Set spcific port pin high according to the given mask
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of pins to be set to high
 */
static inline void gpio_set_port_high_with_mask(GPIO_Type *ptr, uint32_t port, uint32_t mask)
{
    ptr->DO[port].SET = mask;
}

/**
 * @brief   Enable pins output of specific port according to the given mask
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of pins to be enabled
 */
static inline void gpio_enable_port_output_with_mask(GPIO_Type *ptr, uint32_t port, uint32_t mask)
{
    ptr->OE[port].SET = mask;
}

/**
 * @brief   Disable pins output of specific port according to the given mask
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of pins to be disabled
 */
static inline void gpio_disable_port_output_with_mask(GPIO_Type *ptr, uint32_t port, uint32_t mask)
{
    ptr->OE[port].CLEAR = mask;
}

/**
 * @brief   Get current interrupt flags on specific port
 *
 * @param ptr GPIO base address
 * @param port Port index
 *
 * @return Current interrupt flags on specific port
 */
static inline uint32_t gpio_get_port_interrupt_flags(GPIO_Type *ptr, uint32_t port)
{
    return ptr->IF[port].VALUE;
}


/**
 * @brief   Clear interrupt flags with given mask on specific port
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of interrupts to be cleared
 */
static inline void gpio_clear_port_interrupt_flags_with_mask(GPIO_Type *ptr, uint32_t port, uint32_t mask)
{
    ptr->IF[port].VALUE |= mask;
}

/**
 * @brief   Enable interrupts with given mask on specific port
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of interrupts to be enabled
 */
static inline void gpio_enable_port_interrupt_with_mask(GPIO_Type *ptr, uint32_t port, uint8_t mask)
{
    ptr->IE[port].SET = mask;
}

/**
 * @brief   Disable interrupts with given mask on specific port
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param mask Mask of interrupts to be disabled
 */
static inline void gpio_disable_port_interrupt_with_mask(GPIO_Type *ptr, uint32_t port, uint8_t mask)
{
    ptr->IE[port].CLEAR = mask;
}


/**
 * @brief   Config pin interrupt
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 * @param trigger Trigger type
 */
void gpio_config_pin_interrupt(GPIO_Type *ptr, uint32_t port, uint8_t pin, gpio_interrupt_trigger_t trigger);


/**
 * @brief   Toggle pin interrupt trigger polarity
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
void gpio_toggle_pin_interrupt_trigger_polarity(GPIO_Type *ptr, uint32_t port, uint8_t pin);

/**
 * @brief   Toggle pin interrupt trigger type
 *
 * @param ptr GPIO base address
 * @param port Port index
 * @param pin Pin index
 */
void gpio_toggle_pin_interrupt_trigger_type(GPIO_Type *ptr, uint32_t port, uint8_t pin);
#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_GPIO_DRV_H */
