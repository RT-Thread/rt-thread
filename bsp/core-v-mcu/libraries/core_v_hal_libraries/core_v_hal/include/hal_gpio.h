/*
 * Copyright 2021 QuickLogic
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

#ifndef HAL_INCLUDE_HAL_GPIO_H_
#define HAL_INCLUDE_HAL_GPIO_H_

typedef enum {
	CLEAR,
	SET,
	TOGGLE
}efpgaio_enum_typedef;

typedef struct {
	uint8_t		mode;
	uint32_t	int_type;
	uint8_t		in_val;
	uint8_t		out_val;
	uint32_t	int_en;
	uint32_t	number;
}gpio_hal_typedef;

void hal_write_gpio(uint8_t gpio_num, uint8_t value);
void hal_set_gpio(uint8_t gpio_num);
void hal_clr_gpio(uint8_t gpio_num);
void hal_toggle_gpio(uint8_t gpio_num);
void hal_gpio_int_ack (uint8_t int_gpio_num);
void hal_set_gpio_num(uint8_t gpio_num);
void hal_read_gpio_status(gpio_hal_typedef *hgpio);
void hal_read_gpio_status_raw(uint8_t gpio_num, uint32_t* register_value);
void hal_set_gpio_mode(uint8_t gpio_num, uint8_t gpio_mode);
void hal_set_gpio_interrupt(uint8_t gpio_num, uint8_t interrupt_type, uint8_t interrupt_enable);
void hal_enable_gpio_interrupt(uint8_t gpio_num);
void hal_disable_gpio_interrupt(uint8_t gpio_num);

void hal_efpgaio_output(uint8_t gpio_num, efpgaio_enum_typedef value);
void hal_efpgaio_outen(uint8_t gpio_num, efpgaio_enum_typedef value);
void hal_efpgaio_event(uint8_t gpio_num);
void hal_efpgaio_status(gpio_hal_typedef *efpgaio);

#endif /* HAL_INCLUDE_HAL_GPIO_H_ */
