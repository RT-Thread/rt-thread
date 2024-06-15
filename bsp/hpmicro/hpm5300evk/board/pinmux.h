/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PINMUX_H
#define HPM_PINMUX_H

#ifdef __cplusplus
extern "C" {
#endif
void init_xtal_pins(void);
void init_py_pins_as_pgpio(void);
void init_uart_pins(UART_Type *ptr);
void init_uart_pin_as_gpio(UART_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr);
void init_gptmr_pins(GPTMR_Type *ptr);
void init_hall_trgm_pins(void);
void init_qei_trgm_pins(void);
void init_butn_pins(void);
void init_acmp_pins(void);
void init_pwm_pins(PWM_Type *ptr);
void init_adc_pins(void);
void init_adc_bldc_pins(void);
void init_adc_qeiv2_pins(void);
void init_usb_pins(void);
void init_can_pins(MCAN_Type *ptr);
void init_dac_pins(DAC_Type *ptr);
void init_led_pins_as_gpio(void);
void init_led_pins_as_pwm(void);
void init_plb_pins(void);
void init_qeo_pins(QEO_Type *ptr);
void init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx);
void init_rdc_pin(void);
void init_qeiv2_uvw_pins(QEIV2_Type *ptr);
void init_qeiv2_ab_pins(QEIV2_Type *ptr);
void init_qeiv2_abz_pins(QEIV2_Type *ptr);
void init_opamp_pins(void);
void init_lin_transceiver_ctrl_pin(void);
#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
