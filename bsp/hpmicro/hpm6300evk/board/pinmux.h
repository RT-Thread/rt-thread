/*
 *Copyright (c) 2022-2023 HPMicro
 *
 *SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PINMUX_H
#define HPM_PINMUX_H

#ifdef __cplusplus
extern "C" {
#endif
void init_uart_pins(UART_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_sdram_pins(void);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_pins(void);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_hall_trgm_pins(void);
void init_qei_trgm_pins(void);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_enet_pins(ENET_Type *ptr);
void init_pwm_pins(PWM_Type *ptr);
void init_adc_pins(void);
void init_dac_pins(DAC_Type *ptr);
void init_usb_pins(void);
void init_can_pins(CAN_Type *ptr);
void init_sdxc_power_pin(SDXC_Type *ptr);
void init_sdxc_vsel_pin(SDXC_Type *ptr);
void init_sdxc_card_detection_pin(SDXC_Type *ptr);
void init_sdxc_pins(SDXC_Type *ptr, bool use_1v8);
void init_adc_bldc_pins(void);
void init_rgb_pwm_pins(void);
void init_i2c_pins_as_gpio(I2C_Type *ptr);
void init_led_pins(void);
void init_trgmux_pins(uint32_t pin);
#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
