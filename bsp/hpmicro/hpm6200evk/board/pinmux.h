/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PINMUX_H
#define HPM_PINMUX_H

#ifdef __cplusplus
extern "C" {
#endif
void init_uart_pins(UART_Type *ptr);
void init_uart_pin_as_gpio(UART_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_pins(void);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_hall_trgm_pins(void);
void init_qei_trgm_pins(void);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_pwm_pins(PWM_Type *ptr);
void init_hrpwm_pins(PWM_Type *ptr);
void init_adc_pins(void);
void init_dac_pins(DAC_Type *ptr);
void init_usb_pins(void);
void init_can_pins(MCAN_Type *ptr);
void init_adc_bldc_pins(void);
void init_rgb_pwm_pins(void);
void init_i2c_pins_as_gpio(I2C_Type *ptr);
void init_led_pins_as_gpio(void);
void init_led_pins_as_pwm(void);
void init_trgmux_pins(uint32_t pin);
void init_pla_pins(void);
void init_lin_pins(LIN_Type *ptr);
void init_sdm_pins(void);
void init_pla_tamagawa_pins(void);
void init_motor_over_zero_sensorless_adc_pins(void);
void init_tamper_pins(void);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
