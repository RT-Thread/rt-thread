/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_gpio_drv.h"

void gpio_toggle_pin_interrupt_trigger_polarity(GPIO_Type *ptr, uint32_t gpio_index, uint8_t pin_index)
{
    bool intr_was_enabled = gpio_check_pin_interrupt_enabled(ptr, gpio_index, pin_index);
    gpio_disable_pin_interrupt(ptr, gpio_index, pin_index);
    ptr->PL[gpio_index].TOGGLE = 1 << pin_index;
    if (intr_was_enabled) {
        gpio_enable_pin_interrupt(ptr, gpio_index, pin_index);
    }
}

void gpio_toggle_pin_interrupt_trigger_type(GPIO_Type *ptr, uint32_t gpio_index, uint8_t pin_index)
{
    bool intr_was_enabled = gpio_check_pin_interrupt_enabled(ptr, gpio_index, pin_index);
    gpio_disable_pin_interrupt(ptr, gpio_index, pin_index);
    ptr->TP[gpio_index].TOGGLE = 1 << pin_index;
    if (intr_was_enabled) {
        gpio_enable_pin_interrupt(ptr, gpio_index, pin_index);
    }
}


void gpio_config_pin_interrupt(GPIO_Type *ptr, uint32_t gpio_index, uint8_t pin_index, gpio_interrupt_trigger_t trigger)
{
    switch (trigger) {
    case gpio_interrupt_trigger_level_high:
    case gpio_interrupt_trigger_level_low:
        ptr->TP[gpio_index].CLEAR = 1 << pin_index;
        if (trigger == gpio_interrupt_trigger_level_high) {
            ptr->PL[gpio_index].CLEAR = 1 << pin_index;
        } else {
            ptr->PL[gpio_index].SET = 1 << pin_index;
        }
        break;
    case gpio_interrupt_trigger_edge_falling:
    case gpio_interrupt_trigger_edge_rising:
        ptr->TP[gpio_index].SET = 1 << pin_index;
        if (trigger == gpio_interrupt_trigger_edge_rising) {
            ptr->PL[gpio_index].CLEAR = 1 << pin_index;
        } else {
            ptr->PL[gpio_index].SET = 1 << pin_index;
        }
        break;
    default:
        return;
    }
}

void gpio_set_pin_output_with_initial(GPIO_Type *ptr, uint32_t port, uint8_t pin, uint8_t initial)
{
    if (initial & 1) {
        ptr->DO[port].SET = 1 << pin;
    } else {
        ptr->DO[port].CLEAR = 1 << pin;
    }
    ptr->OE[port].SET = 1 << pin;
}
