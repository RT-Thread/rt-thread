/*
 * Copyright (c) 2023,2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PINMUX_H
#define HPM_PINMUX_H

#ifdef __cplusplus
extern "C" {
#endif
void init_py_pins_as_pgpio(void);
void init_uart_pins(UART_Type *ptr);
void init_uart_pin_as_gpio(UART_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_adc_pins(void);
void init_adc_bldc_pins(void);
void init_usb_pins(USB_Type *ptr);
void init_led_pins_as_gpio(void);
void init_uart_break_signal_pin(void);
void init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);
void init_clk_ref_pin(void);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
