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
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/* Driver to control and configure the PULP GPIO pins */
/* Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

#include <stdint.h>
#include <assert.h>
#include <hal_gpio_pulp.h>
#include <hal_pinmux1.h>
#include <bits.h>
#include <pulp_io.h>
#include "core-v-mcu-pulp-mem-map.h"

int gpio_pin_conf_pad(int pin, uint32_t flags)
{
	assert(0 <= pin && pin < 32);

	/* this is only correct if the static assert in gpio.h regarding padcfg*
	 * registers doesn't fail
	 */
	uintptr_t pad_conf_reg =
		(((uintptr_t)pin & 0xf) >> 3) * 4 +
		(uintptr_t)(PULP_GPIO_ADDR + GPIO_PADCFG0_OFFSET);
	uint32_t pad_shift = (pin & 0x3) << 3; /* (0,1) (8,9) (16,17) (24,25) */
	uint32_t val = (flags & GPIO_PULL_ENABLE) |
		       (flags & GPIO_DRIVE_STRENGTH_HIGH) << 1;

	writew(val << pad_shift, pad_conf_reg);

	return 0;
}

/* for now we only handle the gpio from 0-31 and ignore 32-63 */
int gpio_pin_configure(int pin, uint32_t flags)
{
	/* check for misconfigurations */
	assert(!((flags & GPIO_INPUT) && (flags & GPIO_OUTPUT)));

	/* set pad mux to gpio */
	pinmux_pin_set(pin, PINMUX_FUNC_B);

	/* configure pad pull and drive */
	gpio_pin_conf_pad(pin, flags);

	/* configure direction */
	uint32_t pads = readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_PADDIR_OFFSET));
	WRITE_BIT(pads, pin, flags & GPIO_OUTPUT);
	writew(pads, (uintptr_t)(PULP_GPIO_ADDR + GPIO_PADDIR_OFFSET));

	/* default value to prevent glitches */
	if (flags & GPIO_OUTPUT_INIT_HIGH)
		gpio_pin_set_raw(pin, 1);

	if (flags & GPIO_OUTPUT_INIT_LOW)
		gpio_pin_set_raw(pin, 0);

	/* control pad clock gating: need to enable clock for inputs */
	uint32_t en = readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_GPIOEN_OFFSET));
	WRITE_BIT(en, pin, GPIO_INPUT);
	writew(en, (uintptr_t)(PULP_GPIO_ADDR + GPIO_GPIOEN_OFFSET));

	return 0;
}

inline int gpio_port_get_raw(uint32_t *value)
{
	/* this api is a bit dumb but the return value is mean to signal an
	 * error. This never happens in our implementation.
	 */
	*value = readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_PADIN_OFFSET));

	return 0;
}

inline int gpio_port_set_masked_raw(uint32_t mask, uint32_t value)
{
	uint32_t outval =
		readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));
	writew((outval & ~mask) | (value & mask),
	       (uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));

	return 0;
}

inline int gpio_port_set_bits_raw(uint32_t mask)
{
	uint32_t outval =
		readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));
	writew(outval | mask, (uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));

	return 0;
}

inline int gpio_port_clear_bits_raw(uint32_t mask)
{
	uint32_t outval =
		readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));
	writew(outval & ~mask,
	       (uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));

	return 0;
}

inline int gpio_port_toggle_bits(uint32_t mask)
{
	uint32_t outval =
		readw((uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));
	writew(outval ^ mask, (uintptr_t)(PULP_GPIO_ADDR + GPIO_PADOUT_OFFSET));

	return 0;
}

inline int gpio_pin_get_raw(int pin)
{
	assert(0 <= pin && pin < 32);

	uint32_t value = 0;
	int ret = gpio_port_get_raw(&value);
	if (!ret)
		ret = (value & BIT(pin)) != 0;

	return ret;
}

inline int gpio_pin_set_raw(int pin, int value)
{
	assert(0 <= pin && pin < 32);

	if (value != 0)
		gpio_port_set_bits_raw(BIT(pin));
	else
		gpio_port_clear_bits_raw(BIT(pin));

	return 0;
}

inline int gpio_pin_toggle(int pin)
{
	return gpio_port_toggle_bits(BIT(pin));
}
