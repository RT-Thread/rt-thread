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
void init_cap_pins(void);
void init_i2c_pins_as_gpio(I2C_Type *ptr);
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
void init_adc_pins(void);
void init_usb_pins(void);
void init_can_pins(MCAN_Type *ptr);
void init_i2c_pins_as_gpio(I2C_Type *ptr);
void init_led_pins_as_gpio(void);
void init_cam_pins(void);
void init_cam_mipi_csi_pins(void);
void init_sdm_pins(void);
void init_mipi_lvds_tx_phy0_pin(void);
void init_mipi_lvds_tx_phy1_pin(void);
void init_mipi_lvds_rx_phy0_pin(void);
void init_mipi_lvds_rx_phy1_pin(void);
void init_lcd_mipi_ctl_pins(void);
void init_lcd_lvds_double_ctl_pins(void);
void init_lcd_lvds_single_ctl_pins(void);
void init_lcd_rgb_ctl_pins(void);
void init_lcd_rgb_pins(void);
void init_sdxc_cmd_pin(SDXC_Type *ptr, bool open_drain, bool is_1v8);
void init_sdxc_ds_pin(SDXC_Type *ptr);
void init_sdxc_pwr_pin(SDXC_Type  *ptr, bool as_gpio);
void init_sdxc_cd_pin(SDXC_Type  *ptr, bool as_gpio);
void init_sdxc_clk_data_pins(SDXC_Type *ptr, uint32_t width, bool is_1v8);
void init_sdxc_vsel_pin(SDXC_Type *ptr, bool as_gpio);
void init_i2s_pins(I2S_Type *ptr);
void init_dao_pins(void);
void init_pdm_pins(void);
void init_enet_pins(ENET_Type *ptr);
void init_enet_pps_pins(void);
void init_adc_pins(void);
void init_tamper_pins(void);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */
