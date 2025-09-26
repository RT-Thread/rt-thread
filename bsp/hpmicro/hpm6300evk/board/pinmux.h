/*
 *Copyright (c) 2022-2024 HPMicro
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
void init_uart_pin_as_gpio(UART_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_femc_pins(void);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_pins(void);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_hall_trgm_pins(void);
void init_qei_trgm_pins(void);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_enet_pins(ENET_Type *ptr);
void init_pwm_pins(PWM_Type *ptr);
void init_sdxc_cmd_pin(SDXC_Type *ptr, bool open_drain, bool is_1v8);
void init_sdxc_cd_pin(SDXC_Type  *ptr, bool as_gpio);
void init_sdxc_clk_data_pins(SDXC_Type *ptr, uint32_t width, bool is_1v8);
void init_adc_pins(void);
void init_dac_pins(DAC_Type *ptr);
void init_usb_pins(USB_Type *ptr);
void init_can_pins(CAN_Type *ptr);
void init_adc_bldc_pins(void);
void init_rgb_pwm_pins(void);
void init_i2c_pins_as_gpio(I2C_Type *ptr);
void init_led_pins(void);
void init_trgmux_pins(uint32_t pin);
void init_enet_pps_pins(void);
void init_enet_pps_capture_pins(void);
void init_tamper_pins(void);
void init_uart_break_signal_pin(void);
void init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
