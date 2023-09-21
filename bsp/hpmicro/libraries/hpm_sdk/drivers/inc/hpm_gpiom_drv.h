/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPIOM_DRV_H
#define HPM_GPIOM_DRV_H

#include "hpm_gpiom_regs.h"
#include "hpm_gpiom_soc_drv.h"

/**
 *
 * @brief GPIOM driver APIs
 * @defgroup gpiom_interface GPIOM driver APIs
 * @ingroup io_interfaces
 * @{
 */

/* @brief pin visibility */
typedef enum gpiom_pin_visibility {
    gpiom_pin_visible = 0,
    gpiom_pin_invisible = 1,
} gpiom_pin_visibility_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get pin's controller
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 *
 * @retval pin control module
 */
static inline gpiom_gpio_t gpiom_get_pin_controller(GPIOM_Type *ptr,
                                                      uint8_t gpio_index,
                                                      uint8_t pin_index)
{
    return (gpiom_gpio_t)((ptr->ASSIGN[gpio_index].PIN[pin_index]
            & (GPIOM_ASSIGN_PIN_SELECT_MASK)) >> GPIOM_ASSIGN_PIN_SELECT_SHIFT);
}

/**
 * @brief set pin's controller
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 * @param gpio gpio module index
 */
static inline void gpiom_set_pin_controller(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              gpiom_gpio_t gpio)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] =
        (ptr->ASSIGN[gpio_index].PIN[pin_index] & ~(GPIOM_ASSIGN_PIN_SELECT_MASK))
      | GPIOM_ASSIGN_PIN_SELECT_SET(gpio);
}

/**
 * @brief Check if pin is visibility for specified module
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 * @param gpio gpio module index
 *
 * @retval true if pin is visible by specified module
 * @retval false if pin is not visible by specified module
 */
static inline bool gpiom_check_pin_visibility(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              gpiom_gpio_t gpio)
{
    return (ptr->ASSIGN[gpio_index].PIN[pin_index] & ((1 << gpio) << GPIOM_ASSIGN_PIN_HIDE_SHIFT))
        >> GPIOM_ASSIGN_PIN_HIDE_SHIFT >> gpio == gpiom_pin_visible;
}

/**
 * @brief enable pin visibility for specified module
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 * @param gpio gpio module index
 */
static inline void gpiom_enable_pin_visibility(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              gpiom_gpio_t gpio)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] =
        (ptr->ASSIGN[gpio_index].PIN[pin_index] & ~((1 << gpio) << GPIOM_ASSIGN_PIN_HIDE_SHIFT));
}

/**
 * @brief disable pin visibility for specified module
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 * @param gpio gpio module index
 */
static inline void gpiom_disable_pin_visibility(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              gpiom_gpio_t gpio)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] =
        (ptr->ASSIGN[gpio_index].PIN[pin_index] & ~((1 << gpio) << GPIOM_ASSIGN_PIN_HIDE_SHIFT))
      | GPIOM_ASSIGN_PIN_HIDE_SET(1 << gpio);
}

/**
 * @brief Check if pin management is locked
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 *
 * @retval true if pin management is locked
 * @retval false if pin management is not locked
 */
static inline bool gpiom_pin_is_locked(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index)
{
    return (ptr->ASSIGN[gpio_index].PIN[pin_index] & GPIOM_ASSIGN_PIN_LOCK_MASK)
        == GPIOM_ASSIGN_PIN_LOCK_MASK;
}

/**
 * @brief lock pin management
 *
 * @param ptr GPIOM base address
 * @param gpio_index gpio port index
 * @param pin_index pin index
 */
static inline void gpiom_lock_pin(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] |= GPIOM_ASSIGN_PIN_LOCK_MASK;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_GPIOM_DRV_H */

