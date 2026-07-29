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

 #include "core-v-mcu-config.h"
 #include "efpga_template_reg_defs.h"
 #include "hal_apb_gpio_reg_defs.h"
 #include "hal_gpio.h"
 
void hal_efpgaio_output(uint8_t efpgaio_num, efpgaio_enum_typedef value) {

Efpga_t *efpga = (Efpga_t*)EFPGAIO_START_ADDR;

switch(value) {
	case CLEAR:
		if (efpgaio_num < 32)
			efpga->fpgaio_out31_00 &= ~(1 << efpgaio_num) ;
		else if (efpgaio_num < 64)
			efpga->fpgaio_out63_32 &= ~(1 << (efpgaio_num-32)) ;
		else if (efpgaio_num < 80)
			efpga->fpgaio_out79_64 &= ~(1 << (efpgaio_num-64)) ;
		break;
	case SET:
		if (efpgaio_num < 32)
			efpga->fpgaio_out31_00 |= (1 << efpgaio_num) ;
		else if (efpgaio_num < 64)
			efpga->fpgaio_out63_32 |= (1 << (efpgaio_num-32)) ;
		else if (efpgaio_num < 80)
			efpga->fpgaio_out79_64 |= (1 << (efpgaio_num-64)) ;
		break;
	case TOGGLE:
		if (efpgaio_num < 32)
			efpga->fpgaio_out31_00 ^= (1 << efpgaio_num) ;
		else if (efpgaio_num < 64)
			efpga->fpgaio_out63_32 ^= (1 << (efpgaio_num-32)) ;
		else if (efpgaio_num < 80)
			efpga->fpgaio_out79_64 ^= (1 << (efpgaio_num-64)) ;
		break;

	default:
		break;
 }
}

void hal_efpgaio_outen(uint8_t efpgaio_num, efpgaio_enum_typedef value) {

	Efpga_t *efpga = (Efpga_t*)EFPGAIO_START_ADDR;

	switch(value) {
		case CLEAR:
			if (efpgaio_num < 32)
				efpga->fpgaio_oe31_00 &= ~(1 << efpgaio_num) ;
			else if (efpgaio_num < 64)
				efpga->fpgaio_oe63_32 &= ~(1 << (efpgaio_num-32)) ;
			else if (efpgaio_num < 80)
				efpga->fpgaio_oe79_64 &= ~(1 << (efpgaio_num-64)) ;
			break;
		case SET:
			if (efpgaio_num < 32)
				efpga->fpgaio_oe31_00 |= (1 << efpgaio_num) ;
			else if (efpgaio_num < 64)
				efpga->fpgaio_oe63_32 |= (1 << (efpgaio_num-32)) ;
			else if (efpgaio_num < 80)
				efpga->fpgaio_oe79_64 |= (1 << (efpgaio_num-64)) ;
			break;
		default:
			break;
 }
}

int hal_efpgaio_input(uint8_t efpgaio_num) {
 int retval=-1;
	Efpga_t *efpga = (Efpga_t*)EFPGAIO_START_ADDR;
	if (efpgaio_num < 32)
		retval = (efpga->fpgaio_in31_00 >> efpgaio_num) & 0x1 ;
	else if (efpgaio_num < 64)
		retval = (efpga->fpgaio_in63_32 >> (efpgaio_num-32)) & 0x1 ;
	else if (efpgaio_num < 80)
		retval = (efpga->fpgaio_in79_64 >> (efpgaio_num-64)) & 0x1 ;
}

void hal_efpgaio_event(uint8_t event_num) {

	Efpga_t *efpga = (Efpga_t*)EFPGAIO_START_ADDR;
	efpga->fpga_event15_00 |= (1 << event_num);
	efpga->fpga_event15_00 &= ~(1 << event_num);

}

void hal_efpgaio_status(gpio_hal_typedef *hgpio){
	Efpga_t *efpga = (Efpga_t*)EFPGAIO_START_ADDR;
	if (hgpio->number < 32) {
		hgpio->out_val  = (efpga->fpgaio_out31_00 >> hgpio->number) & 0x1;
		hgpio->in_val   = (efpga->fpgaio_in31_00  >> hgpio->number) & 0x1;
		hgpio->mode = (efpga->fpgaio_oe31_00  >> hgpio->number) & 0x1;
	} else if (hgpio->number < 64) {
		hgpio->out_val  = (efpga->fpgaio_out63_32 >> (hgpio->number - 32)) & 0x1;
		hgpio->in_val   = (efpga->fpgaio_in63_32  >> (hgpio->number - 32)) & 0x1;
		hgpio->mode = (efpga->fpgaio_oe63_32  >> (hgpio->number - 32)) & 0x1;
	} else if (hgpio->number < 64) {
		hgpio->out_val  = (efpga->fpgaio_out79_64 >> (hgpio->number - 64)) & 0x1;
		hgpio->in_val   = (efpga->fpgaio_in79_64  >> (hgpio->number - 64)) & 0x1;
		hgpio->mode = (efpga->fpgaio_oe79_64  >> (hgpio->number - 64)) & 0x1;
	}
}


void hal_write_gpio(uint8_t gpio_num, uint8_t value) {
	if (value) {
		hal_set_gpio(gpio_num);
	} else {
		hal_clr_gpio(gpio_num);
	}
}

void hal_set_gpio(uint8_t gpio_num) {
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;

	papbgpio->setgpio_b.gpio_num = gpio_num;
}

void hal_clr_gpio(uint8_t gpio_num) {
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;

	papbgpio->clrgpio_b.gpio_num = gpio_num;
}

void hal_toggle_gpio(uint8_t gpio_num) {
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;

	papbgpio->toggpio_b.gpio_num = gpio_num;
}

void hal_set_gpio_num(uint8_t gpio_num){
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	unsigned int value = 0xff;

	while ((value & 0xff) != gpio_num) {
		papbgpio->setsel= gpio_num;		// Set address for following reads
		value = papbgpio->rdstat;
	}
}

void hal_read_gpio_status(gpio_hal_typedef *hgpio){
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	unsigned int value = 0xff;

	while ((value & 0xff) != hgpio->number) {
		papbgpio->setsel_b.gpio_num = hgpio->number;		// Set address for following reads
		value = papbgpio->rdstat;
	}
	hgpio->mode = (uint8_t)((value >> 24) & 0x3); //papbgpio->rdstat_b.mode;
	hgpio->int_type = (uint8_t)((value >> 17) & 0x7); //papbgpio->rdstat_b.inttype;
	hgpio->int_en = (uint8_t)((value >> 16) & 0x1); //papbgpio->rdstat_b.inten;
	hgpio->in_val = (uint8_t)((value >> 12) & 0x1); //papbgpio->rdstat_b.input;
	hgpio->out_val = (uint8_t)((value >> 8) & 0x1); //papbgpio->rdstat_b.output;
	hgpio->number = (uint8_t)((value >> 0) & 0xFF); //papbgpio->rdstat_b.number;

}

void hal_read_gpio_status_raw(uint8_t gpio_num, uint32_t* register_value){
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	unsigned int value = 0xff;

	while ((value & 0xff) != gpio_num) {
		papbgpio->setsel_b.gpio_num = gpio_num;		// Set address for following reads
		value = papbgpio->rdstat;
	}

	*register_value = value;
}

void hal_gpio_int_ack (uint8_t gpio_num) {
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	papbgpio->intack = gpio_num;
}

void hal_set_gpio_mode(uint8_t gpio_num, uint8_t gpio_mode){
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	unsigned int value = gpio_num;
	value = (value & 0xfcffffff) | (gpio_mode << 24);
	//papbgpio->setmode_b.gpio_num = gpio_num;  //ToDo: is there a race here -- do we need to write both at same time?
	//papbgpio->setmode_b.mode = gpio_mode;
	papbgpio->setmode = value;
}

void hal_set_gpio_interrupt(uint8_t gpio_num, uint8_t interrupt_type, uint8_t interrupt_enable){
	unsigned int regval;
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	regval = papbgpio->setint;
	regval = regval & 0xFFF0FF00;

	regval = regval | (((interrupt_type & REG_SETINT_INTTYPE_MASK) << REG_SETINT_INTTYPE_LSB ) |
			 ((interrupt_enable & REG_SETINT_INTENABLE_MASK) << REG_SETINT_INTENABLE_LSB) |
			 ((gpio_num & REG_SETINT_gpio_num_MASK ) << REG_SETINT_gpio_num_LSB));

	papbgpio->setint = regval;
}

void hal_enable_gpio_interrupt(uint8_t gpio_num){
	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	unsigned int regval = papbgpio->setint;
	regval = regval & (~(REG_SETINT_gpio_num_MASK << REG_SETINT_gpio_num_LSB));
	regval = regval & (~(REG_SETINT_INTENABLE_MASK << REG_SETINT_INTENABLE_LSB));
	regval = regval | (((0x1 & REG_SETINT_INTENABLE_MASK) << REG_SETINT_INTENABLE_LSB) |
			 ((gpio_num & REG_SETINT_gpio_num_MASK ) << REG_SETINT_gpio_num_LSB));

	papbgpio->setint = regval;
}

void hal_disable_gpio_interrupt(uint8_t gpio_num) {

	ApbGpio_t*	papbgpio = (ApbGpio_t*)GPIO_START_ADDR;
	unsigned int regval = papbgpio->setint;
	regval = regval & (~(REG_SETINT_gpio_num_MASK << REG_SETINT_gpio_num_LSB));
	regval = regval & (~(REG_SETINT_INTENABLE_MASK << REG_SETINT_INTENABLE_LSB));
	regval = regval | ((gpio_num & REG_SETINT_gpio_num_MASK ) << REG_SETINT_gpio_num_LSB);

	papbgpio->setint = regval;
}
