/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright (c) 2019-2020 Nordic Semiconductor ASA
 * Copyright (c) 2019 Piotr Mienkowski
 * Copyright (c) 2017 ARM Ltd
 * Copyright (c) 2015-2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Driver to control and configure the PULP GPIO pins */
/* Author: Germain Haugou (germain.haugou@iis.ee.ethz.ch)
 *         Robert Balas (balasr@iis.ee.ethz.ch)
 */

#ifndef HAL_INCLUDE_HAL_GPIO_PULP_H_
#define HAL_INCLUDE_HAL_GPIO_PULP_H_

#include <stdint.h>
#include <assert.h>
#include "pulp_io.h"
#include "hal_pinmux1.h"
#include "core-v-mcu-pulp-mem-map.h"

/* TODO: static assert on expected register sequence */
//
// REGISTERS
//

// GPIO pad direction configuration register.
#define GPIO_PADDIR_OFFSET 0x0

// GPIO enable register.
#define GPIO_GPIOEN_OFFSET 0x4

// GPIO pad input value register.
#define GPIO_PADIN_OFFSET 0x8

// GPIO pad output value register.
#define GPIO_PADOUT_OFFSET 0xc

// GPIO pad output set register.
#define GPIO_PADOUTSET_OFFSET 0x10

// GPIO pad output clear register.
#define GPIO_PADOUTCLR_OFFSET 0x14

// GPIO pad interrupt enable configuration register.
#define GPIO_INTEN_OFFSET 0x18

// GPIO pad interrupt type gpio 0 to 15 register.
#define GPIO_INTTYPE0_OFFSET 0x1c

// GPIO pad interrupt type gpio 16 to 31 register.
#define GPIO_INTTYPE1_OFFSET 0x20

// GPIO pad interrupt status register.
#define GPIO_INTSTATUS_OFFSET 0x24

// GPIO pad pin 0 to 7 configuration register.
#define GPIO_PADCFG0_OFFSET 0x28

// GPIO pad pin 8 to 15 configuration register.
#define GPIO_PADCFG1_OFFSET 0x2c

// GPIO pad pin 16 to 23 configuration register.
#define GPIO_PADCFG2_OFFSET 0x30

// GPIO pad pin 24 to 31 configuration register.
#define GPIO_PADCFG3_OFFSET 0x34

// GPIO pad direction configuration register.
#define GPIO_PADDIR_32_63_OFFSET 0x38

// GPIO enable register.
#define GPIO_GPIOEN_32_63_OFFSET 0x3c

// GPIO pad input value register.
#define GPIO_PADIN_32_63_OFFSET 0x40

// GPIO pad output value register.
#define GPIO_PADOUT_32_63_OFFSET 0x44

// GPIO pad output set register.
#define GPIO_PADOUTSET_32_63_OFFSET 0x48

// GPIO pad output clear register.
#define GPIO_PADOUTCLR_32_63_OFFSET 0x4c

// GPIO pad interrupt enable configuration register.
#define GPIO_INTEN_32_63_OFFSET 0x50

// GPIO pad interrupt type gpio 32 to 47 register.
#define GPIO_INTTYPE_32_47_OFFSET 0x54

// GPIO pad interrupt type gpio 48 to 63 register.
#define GPIO_INTTYPE_48_63_OFFSET 0x58

// GPIO pad interrupt status register.
#define GPIO_INTSTATUS_32_63_OFFSET 0x5c

// GPIO pad pin 32 to 39 configuration register.
#define GPIO_PADCFG_32_39_OFFSET 0x60

// GPIO pad pin 40 to 47 configuration register.
#define GPIO_PADCFG_40_47_OFFSET 0x64

// GPIO pad pin 48 to 55 configuration register.
#define GPIO_PADCFG_48_55_OFFSET 0x68

// GPIO pad pin 56 to 63 configuration register.
#define GPIO_PADCFG_56_63_OFFSET 0x6c

//
// REGISTERS FIELDS
//

// GPIO[31:0] direction configuration bitfield: - bit[i]=1'b0: Input mode for GPIO[i] - bit[i]=1'b1: Output mode for GPIO[i] (access: R/W)
#define GPIO_PADDIR_DIR_BIT   0
#define GPIO_PADDIR_DIR_WIDTH 32
#define GPIO_PADDIR_DIR_MASK  0xffffffff

// GPIO[31:0] clock enable configuration bitfield: - bit[i]=1'b0: disable clock for GPIO[i] - bit[i]=1'b1: enable clock for GPIO[i] GPIOs are gathered by groups of 4. The clock gating of one group is done only if all 4 GPIOs are disabled.  Clock must be enabled for a GPIO if it's direction is configured in input mode. (access: R/W)
#define GPIO_GPIOEN_GPIOEN_BIT	 0
#define GPIO_GPIOEN_GPIOEN_WIDTH 32
#define GPIO_GPIOEN_GPIOEN_MASK	 0xffffffff

// GPIO[31:0] input data read bitfield. DATA_IN[i] corresponds to input data of GPIO[i]. (access: R)
#define GPIO_PADIN_DATA_IN_BIT	 0
#define GPIO_PADIN_DATA_IN_WIDTH 32
#define GPIO_PADIN_DATA_IN_MASK	 0xffffffff

// GPIO[31:0] output data read bitfield. DATA_OUT[i] corresponds to output data set on GPIO[i]. (access: R/W)
#define GPIO_PADOUT_DATA_OUT_BIT   0
#define GPIO_PADOUT_DATA_OUT_WIDTH 32
#define GPIO_PADOUT_DATA_OUT_MASK  0xffffffff

// GPIO[31:0] set bitfield: - bit[i]=1'b0: No change for GPIO[i] - bit[i]=1'b1: Sets GPIO[i] to 1 (access: W)
#define GPIO_PADOUTSET_DATA_SET_BIT   0
#define GPIO_PADOUTSET_DATA_SET_WIDTH 32
#define GPIO_PADOUTSET_DATA_SET_MASK  0xffffffff

// GPIO[31:0] clear bitfield: - bit[i]=1'b0: No change for GPIO[i] - bit[i]=1'b1: Clears GPIO[i] (access: W)
#define GPIO_PADOUTCLR_DATA_CLEAR_BIT	0
#define GPIO_PADOUTCLR_DATA_CLEAR_WIDTH 32
#define GPIO_PADOUTCLR_DATA_CLEAR_MASK	0xffffffff

// GPIO[31:0] interrupt enable configuration bitfield: - bit[i]=1'b0: disable interrupt for GPIO[i] - bit[i]=1'b1: enable interrupt for GPIO[i] (access: R/W)
#define GPIO_INTEN_INTEN_BIT   0
#define GPIO_INTEN_INTEN_WIDTH 32
#define GPIO_INTEN_INTEN_MASK  0xffffffff

// GPIO[15:0] interrupt type configuration bitfield: - bit[2*i+1:2*i]=2'b00: interrupt on falling edge for GPIO[i] - bit[2*i+1:2*i]=2'b01: interrupt on rising edge for GPIO[i] - bit[2*i+1:2*i]=2'b10: interrupt on rising and falling edge for GPIO[i] - bit[2*i+1:2*i]=2'b11: RFU (access: R/W)
#define GPIO_INTTYPE0_INTTYPE0_BIT   0
#define GPIO_INTTYPE0_INTTYPE0_WIDTH 32
#define GPIO_INTTYPE0_INTTYPE0_MASK  0xffffffff

// GPIO[31:16] interrupt type configuration bitfield: - bit[2*i+1:2*i]=2'b00: interrupt on falling edge for GPIO[16+i] - bit[2*i+1:2*i]=2'b01: interrupt on rising edge for GPIO[16+i] - bit[2*i+1:2*i]=2'b10: interrupt on rising and falling edge for GPIO[16+i] - bit[2*i+1:2*i]=2'b11: RFU (access: R/W)
#define GPIO_INTTYPE1_INTTYPE1_BIT   0
#define GPIO_INTTYPE1_INTTYPE1_WIDTH 32
#define GPIO_INTTYPE1_INTTYPE1_MASK  0xffffffff

// GPIO[31:0] Interrupt status flags bitfield. INTSTATUS[i]=1 when interrupt received on GPIO[i]. INTSTATUS is cleared when it is red. GPIO interrupt line is also cleared when INTSTATUS register is red. (access: R)
#define GPIO_INTSTATUS_INTSTATUS_BIT   0
#define GPIO_INTSTATUS_INTSTATUS_WIDTH 32
#define GPIO_INTSTATUS_INTSTATUS_MASK  0xffffffff

// GPIO[0] pull activation configuration bitfield: - 1'b0: pull disabled - 1'b1: pull enabled (access: R/W)
#define GPIO_PADCFG0_GPIO0_CFG_BIT   0
#define GPIO_PADCFG0_GPIO0_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO0_CFG_MASK  0xf

// GPIO[0] drive strength configuration bitfield: - 1'b0: low drive strength - 1'b1: high drive strength (access: R/W)
#define GPIO_PADCFG0_GPIO1_CFG_BIT   4
#define GPIO_PADCFG0_GPIO1_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO1_CFG_MASK  0xf0

// GPIO[1] pull activation configuration bitfield: - 1'b0: pull disabled - 1'b1: pull enabled (access: R/W)
#define GPIO_PADCFG0_GPIO2_CFG_BIT   8
#define GPIO_PADCFG0_GPIO2_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO2_CFG_MASK  0xf00

// GPIO[1] drive strength configuration bitfield: - 1'b0: low drive strength - 1'b1: high drive strength (access: R/W)
#define GPIO_PADCFG0_GPIO3_CFG_BIT   12
#define GPIO_PADCFG0_GPIO3_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO3_CFG_MASK  0xf000

// GPIO[2] pull activation configuration bitfield: - 1'b0: pull disabled - 1'b1: pull enabled (access: R/W)
#define GPIO_PADCFG0_GPIO4_CFG_BIT   16
#define GPIO_PADCFG0_GPIO4_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO4_CFG_MASK  0xf0000

// GPIO[2] drive strength configuration bitfield: - 1'b0: low drive strength - 1'b1: high drive strength (access: R/W)
#define GPIO_PADCFG0_GPIO5_CFG_BIT   20
#define GPIO_PADCFG0_GPIO5_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO5_CFG_MASK  0xf00000

// GPIO[3] pull activation configuration bitfield: - 1'b0: pull disabled - 1'b1: pull enabled (access: R/W)
#define GPIO_PADCFG0_GPIO6_CFG_BIT   24
#define GPIO_PADCFG0_GPIO6_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO6_CFG_MASK  0xf000000

// GPIO[3] drive strength configuration bitfield: - 1'b0: low drive strength - 1'b1: high drive strength (access: R/W)
#define GPIO_PADCFG0_GPIO7_CFG_BIT   28
#define GPIO_PADCFG0_GPIO7_CFG_WIDTH 4
#define GPIO_PADCFG0_GPIO7_CFG_MASK  0xf0000000

// GPIO[4] pull activation configuration bitfield: - 1'b0: pull disabled - 1'b1: pull enabled (access: R/W)
#define GPIO_PADCFG1_GPIO4_PE_BIT   0
#define GPIO_PADCFG1_GPIO4_PE_WIDTH 1
#define GPIO_PADCFG1_GPIO4_PE_MASK  0x1

// GPIO[4] drive strength configuration bitfield: - 1'b0: low drive strength - 1'b1: high drive strength (access: R/W)
#define GPIO_PADCFG1_GPIO4_DS_BIT   1
#define GPIO_PADCFG1_GPIO4_DS_WIDTH 1
#define GPIO_PADCFG1_GPIO4_DS_MASK  0x2

// GPIO[63:32] direction configuration bitfield: - bit[i]=1'b0: Input mode for GPIO[i] - bit[i]=1'b1: Output mode for GPIO[i] (access: R/W)
#define GPIO_PADDIR_32_63_DIR_BIT   0
#define GPIO_PADDIR_32_63_DIR_WIDTH 32
#define GPIO_PADDIR_32_63_DIR_MASK  0xffffffff

// GPIO[63:32] clock enable configuration bitfield: - bit[i]=1'b0: disable clock for GPIO[i] - bit[i]=1'b1: enable clock for GPIO[i] GPIOs are gathered by groups of 4. The clock gating of one group is done only if all 4 GPIOs are disabled.  Clock must be enabled for a GPIO if it's direction is configured in input mode. (access: R/W)
#define GPIO_GPIOEN_32_63_GPIOEN_BIT   0
#define GPIO_GPIOEN_32_63_GPIOEN_WIDTH 32
#define GPIO_GPIOEN_32_63_GPIOEN_MASK  0xffffffff

// GPIO[63:32] input data read bitfield. DATA_IN[i] corresponds to input data of GPIO[i]. (access: R)
#define GPIO_PADIN_32_63_DATA_IN_BIT   0
#define GPIO_PADIN_32_63_DATA_IN_WIDTH 32
#define GPIO_PADIN_32_63_DATA_IN_MASK  0xffffffff

// GPIO[63:32] output data read bitfield. DATA_OUT[i] corresponds to output data set on GPIO[i]. (access: R/W)
#define GPIO_PADOUT_32_63_DATA_OUT_BIT	 0
#define GPIO_PADOUT_32_63_DATA_OUT_WIDTH 32
#define GPIO_PADOUT_32_63_DATA_OUT_MASK	 0xffffffff

// GPIO[63:32] set bitfield: - bit[i]=1'b0: No change for GPIO[i] - bit[i]=1'b1: Sets GPIO[i] to 1 (access: W)
#define GPIO_PADOUTSET_32_63_DATA_SET_BIT   0
#define GPIO_PADOUTSET_32_63_DATA_SET_WIDTH 32
#define GPIO_PADOUTSET_32_63_DATA_SET_MASK  0xffffffff

// GPIO[63:32] clear bitfield: - bit[i]=1'b0: No change for GPIO[i] - bit[i]=1'b1: Clears GPIO[i] (access: W)
#define GPIO_PADOUTCLR_32_63_DATA_CLEAR_BIT   0
#define GPIO_PADOUTCLR_32_63_DATA_CLEAR_WIDTH 32
#define GPIO_PADOUTCLR_32_63_DATA_CLEAR_MASK  0xffffffff

// GPIO[63:32] interrupt enable configuration bitfield: - bit[i]=1'b0: disable interrupt for GPIO[i] - bit[i]=1'b1: enable interrupt for GPIO[i] (access: R/W)
#define GPIO_INTEN_32_63_INTEN_BIT   0
#define GPIO_INTEN_32_63_INTEN_WIDTH 32
#define GPIO_INTEN_32_63_INTEN_MASK  0xffffffff

// GPIO[47:32] interrupt type configuration bitfield: - bit[2*i+1:2*i]=2'b00: interrupt on falling edge for GPIO[i] - bit[2*i+1:2*i]=2'b01: interrupt on rising edge for GPIO[i] - bit[2*i+1:2*i]=2'b10: interrupt on rising and falling edge for GPIO[i] - bit[2*i+1:2*i]=2'b11: RFU (access: R/W)
#define GPIO_INTTYPE_32_47_INTTYPE0_BIT	  0
#define GPIO_INTTYPE_32_47_INTTYPE0_WIDTH 32
#define GPIO_INTTYPE_32_47_INTTYPE0_MASK  0xffffffff

// GPIO[63:48] interrupt type configuration bitfield: - bit[2*i+1:2*i]=2'b00: interrupt on falling edge for GPIO[16+i] - bit[2*i+1:2*i]=2'b01: interrupt on rising edge for GPIO[16+i] - bit[2*i+1:2*i]=2'b10: interrupt on rising and falling edge for GPIO[16+i] - bit[2*i+1:2*i]=2'b11: RFU (access: R/W)
#define GPIO_INTTYPE_48_63_INTTYPE1_BIT	  0
#define GPIO_INTTYPE_48_63_INTTYPE1_WIDTH 32
#define GPIO_INTTYPE_48_63_INTTYPE1_MASK  0xffffffff

// GPIO[63:32] Interrupt status flags bitfield. INTSTATUS[i]=1 when interrupt received on GPIO[i]. INTSTATUS is cleared when it is red. GPIO interrupt line is also cleared when INTSTATUS register is red. (access: R)
#define GPIO_INTSTATUS_32_63_INTSTATUS_BIT   0
#define GPIO_INTSTATUS_32_63_INTSTATUS_WIDTH 32
#define GPIO_INTSTATUS_32_63_INTSTATUS_MASK  0xffffffff

/* required for gpio_pin_conf_pad() */
static_assert((GPIO_PADCFG0_OFFSET + 0x4 == GPIO_PADCFG1_OFFSET) &&
		      (GPIO_PADCFG1_OFFSET + 0x4 == GPIO_PADCFG2_OFFSET) &&
		      (GPIO_PADCFG2_OFFSET + 0x4 == GPIO_PADCFG3_OFFSET),
	      "GPIO_PADCFG*_OFFSET has unexpected addresses (spacing)");

/* this API is from gpio.h of zephyr */

/* this is custom */
/** Enables internal pull */
#define GPIO_PULL_ENABLE (1U << 1)

/** Enables high drive strength */
#define GPIO_DRIVE_STRENGTH_HIGH (1U << 1)

/* this is zephyr */
/** Enables pin as input. */
#define GPIO_INPUT (1U << 8)

/** Enables pin as output, no change to the output state. */
#define GPIO_OUTPUT (1U << 9)

/** Disables pin for both input and output. */
#define GPIO_DISCONNECTED 0

/** @cond INTERNAL_HIDDEN */

/* Initializes output to a low state. */
#define GPIO_OUTPUT_INIT_LOW (1U << 10)

/* Initializes output to a high state. */
#define GPIO_OUTPUT_INIT_HIGH (1U << 11)

/* Initializes output based on logic level */
#define GPIO_OUTPUT_INIT_LOGICAL (1U << 12)

/** @endcond */

/** Configures GPIO pin as output and initializes it to a low state. */
#define GPIO_OUTPUT_LOW (GPIO_OUTPUT | GPIO_OUTPUT_INIT_LOW)
/** Configures GPIO pin as output and initializes it to a high state. */
#define GPIO_OUTPUT_HIGH (GPIO_OUTPUT | GPIO_OUTPUT_INIT_HIGH)
/** Configures GPIO pin as output and initializes it to a logic 0. */
#define GPIO_OUTPUT_INACTIVE                                                   \
	(GPIO_OUTPUT | GPIO_OUTPUT_INIT_LOW | GPIO_OUTPUT_INIT_LOGICAL)
/** Configures GPIO pin as output and initializes it to a logic 1. */
#define GPIO_OUTPUT_ACTIVE                                                     \
	(GPIO_OUTPUT | GPIO_OUTPUT_INIT_HIGH | GPIO_OUTPUT_INIT_LOGICAL)

int gpio_pin_conf_pad(int pin, uint32_t flags);


/* for now we only handle the gpio from 0-31 and ignore 32-63 */
int gpio_pin_configure(int pin, uint32_t flags);
int gpio_port_get_raw(uint32_t *value);
int gpio_port_set_masked_raw(uint32_t mask, uint32_t value);
int gpio_port_set_bits_raw(uint32_t mask);
int gpio_port_clear_bits_raw(uint32_t mask);
int gpio_port_toggle_bits(uint32_t mask);
int gpio_pin_get_raw(int pin);
int gpio_pin_set_raw(int pin, int value);
int gpio_pin_toggle(int pin);


#endif /* HAL_INCLUDE_HAL_GPIO_PULP_H_ */
