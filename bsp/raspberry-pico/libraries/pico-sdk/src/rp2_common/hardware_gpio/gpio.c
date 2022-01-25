/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/gpio.h"
#include "hardware/sync.h"

#include "hardware/structs/iobank0.h"
#include "hardware/irq.h"

#include "pico/binary_info.h"

static gpio_irq_callback_t _callbacks[NUM_CORES];

// Get the raw value from the pin, bypassing any muxing or overrides.
int gpio_get_pad(uint gpio) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    hw_set_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_IE_BITS);
    return (iobank0_hw->io[gpio].status & IO_BANK0_GPIO0_STATUS_INFROMPAD_BITS)
            >> IO_BANK0_GPIO0_STATUS_INFROMPAD_LSB;
}

/// \tag::gpio_set_function[]
// Select function for this GPIO, and ensure input/output are enabled at the pad.
// This also clears the input/output/irq override bits.
void gpio_set_function(uint gpio, enum gpio_function fn) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    invalid_params_if(GPIO, fn << IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB & ~IO_BANK0_GPIO0_CTRL_FUNCSEL_BITS);
    // Set input enable on, output disable off
    hw_write_masked(&padsbank0_hw->io[gpio],
                   PADS_BANK0_GPIO0_IE_BITS,
                   PADS_BANK0_GPIO0_IE_BITS | PADS_BANK0_GPIO0_OD_BITS
    );
    // Zero all fields apart from fsel; we want this IO to do what the peripheral tells it.
    // This doesn't affect e.g. pullup/pulldown, as these are in pad controls.
    iobank0_hw->io[gpio].ctrl = fn << IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB;
}
/// \end::gpio_set_function[]

enum gpio_function gpio_get_function(uint gpio) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    return (enum gpio_function) ((iobank0_hw->io[gpio].ctrl & IO_BANK0_GPIO0_CTRL_FUNCSEL_BITS) >> IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB);
}

// Note that, on RP2040, setting both pulls enables a "bus keep" function,
// i.e. weak pull to whatever is current high/low state of GPIO.
void gpio_set_pulls(uint gpio, bool up, bool down) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    hw_write_masked(
            &padsbank0_hw->io[gpio],
            (!!up << PADS_BANK0_GPIO0_PUE_LSB) | (!!down << PADS_BANK0_GPIO0_PDE_LSB),
            PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_PDE_BITS
    );
}

// Direct overrides for pad controls
void gpio_set_inover(uint gpio, uint value) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_INOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_INOVER_BITS
    );
}

void gpio_set_outover(uint gpio, uint value) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_OUTOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_OUTOVER_BITS
    );
}

void gpio_set_oeover(uint gpio, uint value) {
    invalid_params_if(GPIO, gpio >= N_GPIOS);
    hw_write_masked(&iobank0_hw->io[gpio].ctrl,
                   value << IO_BANK0_GPIO0_CTRL_OEOVER_LSB,
                   IO_BANK0_GPIO0_CTRL_OEOVER_BITS
    );
}

static void gpio_irq_handler(void) {
    io_irq_ctrl_hw_t *irq_ctrl_base = get_core_num() ?
                                           &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
    for (uint gpio = 0; gpio < N_GPIOS; gpio++) {
        io_rw_32 *status_reg = &irq_ctrl_base->ints[gpio / 8];
        uint events = (*status_reg >> 4 * (gpio % 8)) & 0xf;
        if (events) {
            // TODO: If both cores care about this event then the second core won't get the irq?
            gpio_acknowledge_irq(gpio, events);
            gpio_irq_callback_t callback = _callbacks[get_core_num()];
            if (callback) {
                callback(gpio, events);
            }
        }
    }
}

static void _gpio_set_irq_enabled(uint gpio, uint32_t events, bool enabled, io_irq_ctrl_hw_t *irq_ctrl_base) {
    // Clear stale events which might cause immediate spurious handler entry
    gpio_acknowledge_irq(gpio, events);

    io_rw_32 *en_reg = &irq_ctrl_base->inte[gpio / 8];
    events <<= 4 * (gpio % 8);

    if (enabled)
        hw_set_bits(en_reg, events);
    else
        hw_clear_bits(en_reg, events);
}

void gpio_set_irq_enabled(uint gpio, uint32_t events, bool enabled) {
    // Separate mask/force/status per-core, so check which core called, and
    // set the relevant IRQ controls.
    io_irq_ctrl_hw_t *irq_ctrl_base = get_core_num() ?
                                           &iobank0_hw->proc1_irq_ctrl : &iobank0_hw->proc0_irq_ctrl;
    _gpio_set_irq_enabled(gpio, events, enabled, irq_ctrl_base);
}

void gpio_set_irq_enabled_with_callback(uint gpio, uint32_t events, bool enabled, gpio_irq_callback_t callback) {
    gpio_set_irq_enabled(gpio, events, enabled);

    // TODO: Do we want to support a callback per GPIO pin?
    // Install IRQ handler
    _callbacks[get_core_num()] = callback;
    irq_set_exclusive_handler(IO_IRQ_BANK0, gpio_irq_handler);
    irq_set_enabled(IO_IRQ_BANK0, true);
}

void gpio_set_dormant_irq_enabled(uint gpio, uint32_t events, bool enabled) {
    io_irq_ctrl_hw_t *irq_ctrl_base = &iobank0_hw->dormant_wake_irq_ctrl;
    _gpio_set_irq_enabled(gpio, events, enabled, irq_ctrl_base);
}

void gpio_acknowledge_irq(uint gpio, uint32_t events) {
    iobank0_hw->intr[gpio / 8] = events << 4 * (gpio % 8);
}

#define DEBUG_PIN_MASK (((1u << PICO_DEBUG_PIN_COUNT)-1) << PICO_DEBUG_PIN_BASE)
void gpio_debug_pins_init() {
    gpio_init_mask(DEBUG_PIN_MASK);
    gpio_set_dir_masked(DEBUG_PIN_MASK, DEBUG_PIN_MASK);
    bi_decl_if_func_used(bi_pin_mask_with_names(DEBUG_PIN_MASK, "Debug"));
}

void gpio_set_input_enabled(uint gpio, bool enabled) {
    if (enabled)
        hw_set_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_IE_BITS);
    else
        hw_clear_bits(&padsbank0_hw->io[gpio], PADS_BANK0_GPIO0_IE_BITS);
}

void gpio_init(uint gpio) {
    sio_hw->gpio_oe_clr = 1ul << gpio;
    sio_hw->gpio_clr = 1ul << gpio;
    gpio_set_function(gpio, GPIO_FUNC_SIO);
}

void gpio_init_mask(uint gpio_mask) {
    for(uint i=0;i<32;i++) {
        if (gpio_mask & 1) {
            gpio_init(i);
        }
        gpio_mask >>= 1;
    }
}

