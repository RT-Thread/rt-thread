/*
 * Copyright (c) 2021-2023 HPMicro
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
void init_lcd_pins(LCDC_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_cap_pins(void);
void init_sdram_pins(void);
void init_sram_pins(void);
void init_gpio_pins(uint8_t pin_stat);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_pins(void);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_hall_trgm_pins(void);
void init_qei_trgm_pins(void);
void init_i2s_pins(I2S_Type *ptr);
void init_dao_pins(void);
void init_pdm_pins(void);
void init_vad_pins(void);
void init_cam_pins(void);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_enet_pins(ENET_Type *ptr);
void init_pwm_pins(PWM_Type *ptr);
void init_adc12_pins(void);
void init_adc16_pins(void);
void init_usb_pins(void);
void init_can_pins(CAN_Type *ptr);
void init_sdxc_cmd_pin(SDXC_Type *ptr, bool open_drain, bool is_1v8);
void init_sdxc_cd_pin(SDXC_Type  *ptr, bool as_gpio);
void init_sdxc_clk_data_pins(SDXC_Type *ptr, uint32_t width, bool is_1v8);
void init_sdxc_pwr_pin(SDXC_Type  *ptr, bool as_gpio);
void init_adc12_pins(void);
void init_adc16_pins(void);
void init_usb_pins(void);
void init_can_pins(CAN_Type *ptr);
void init_adc_bldc_pins(void);
void init_rgb_pwm_pins(void);
void init_i2c_pins_as_gpio(I2C_Type *ptr);
void init_led_pins_as_gpio(void);
void init_trgmux_pins(uint32_t pin);
void init_enet_pps_pins(void);
void init_tamper_pins(void);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
