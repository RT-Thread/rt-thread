/*
 * Copyright (c) 2023 hpmicro
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
void init_i2c_pins_as_gpio(I2C_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_femc_pins(void);
void init_ppi_pins(void);
void init_sdm_pins(void);
void init_pwm_pin_as_sdm_clock(void);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_hall_trgm_pins(void);
void init_qei_trgm_pins(void);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_pwm_pins(PWMV2_Type *ptr);
void init_usb_pins(void);
void init_i2s_pins(I2S_Type *ptr);
void init_qeo_pins(QEOV2_Type *ptr);
void init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx);
void init_qeiv2_uvw_pins(QEIV2_Type *ptr);
void init_qeiv2_ab_pins(QEIV2_Type *ptr);
void init_qeiv2_abz_pins(QEIV2_Type *ptr);
void init_rdc_pin(void);
void init_dao_pins(void);
void init_pdm_pins(void);
void init_enet_pins(ENET_Type *ptr);
void init_enet_pps_pins(void);
void init_adc16_pins(void);
void init_adc_bldc_pins(void);
void init_adc_qeiv2_pins(void);
void init_can_pins(MCAN_Type *ptr);
void init_led_pins_as_gpio(void);
void init_led_pins_as_pwm(void);
void init_plb_pins(void);
void init_esc_pins(void);
void init_esc_in_out_pin(void);
void init_tsw_pins(void);
void init_tamper_pins(void);
void init_pwm_fault_pins(void);
void init_uart_break_signal_pin(void);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
