/**
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SYSCTL_DRV_H
#define HPM_SYSCTL_DRV_H

#include "hpm_common.h"
#include "hpm_sysctl_regs.h"

/**
 *
 * @brief SYSCTL driver APIs
 * @defgroup sysctl_interface SYSCTL driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief Retention domains
 */typedef enum {
    sysctl_retention_domain_sys = 0,
    sysctl_retention_domain_cpu0 = 2,
    sysctl_retention_domain_cpu1 = 4,
    sysctl_retention_domain_otn = 6,
    sysctl_retention_domain_xtal24m = 8,
    sysctl_retention_domain_pll0 = 9,
    sysctl_retention_domain_pll1 = 10,
    sysctl_retention_domain_pll2 = 11,
} sysctl_retention_domain_t;

/**
 * @brief Clock presets
 */
typedef enum {
    sysctl_preset_0 = 1 << 0,
    sysctl_preset_1 = 1 << 1,
    sysctl_preset_2 = 1 << 2,
    sysctl_preset_3 = 1 << 3,
} sysctl_preset_t;

/**
 * @brief Reset domains
 */
typedef enum {
    sysctl_reset_domain_soc = 0,
    sysctl_reset_domain_cpu0,
    sysctl_reset_domain_cpu1,
    sysctl_reset_domain_otn,
} sysctl_reset_domain_t;

/**
 * @brief Resource
 */
typedef enum {
    sysctl_resource_cpu0 = SYSCTL_RESOURCE_CPU0,
    sysctl_resource_cpx0 = SYSCTL_RESOURCE_CPX0,
    sysctl_resource_cpu1 = SYSCTL_RESOURCE_CPU1,
    sysctl_resource_cpx1 = SYSCTL_RESOURCE_CPX1,
    sysctl_resource_pow_cpu0 = SYSCTL_RESOURCE_POW_CPU0,
    sysctl_resource_pow_cpu1 = SYSCTL_RESOURCE_POW_CPU1,
    sysctl_resource_pow_otn = SYSCTL_RESOURCE_POW_OTN,
    sysctl_resource_rst_soc = SYSCTL_RESOURCE_RST_SOC,
    sysctl_resource_rst_cpu0 = SYSCTL_RESOURCE_RST_CPU0,
    sysctl_resource_rst_cpu1 = SYSCTL_RESOURCE_RST_CPU1,
    sysctl_resource_rst_otn = SYSCTL_RESOURCE_RST_OTN,
    sysctl_resource_xtal = SYSCTL_RESOURCE_CLK_SRC_XTAL,
    sysctl_resource_pll0 = SYSCTL_RESOURCE_CLK_SRC_PLL0,
    sysctl_resource_clk0_pll0 = SYSCTL_RESOURCE_CLK_SRC_CLK0_PLL0,
    sysctl_resource_clk1_pll0 = SYSCTL_RESOURCE_CLK_SRC_CLK1_PLL0,
    sysctl_resource_pll1 = SYSCTL_RESOURCE_CLK_SRC_PLL1,
    sysctl_resource_clk0_pll1 = SYSCTL_RESOURCE_CLK_SRC_CLK0_PLL1,
    sysctl_resource_clk1_pll1 = SYSCTL_RESOURCE_CLK_SRC_CLK1_PLL1,
    sysctl_resource_clk2_pll1 = SYSCTL_RESOURCE_CLK_SRC_CLK2_PLL1,
    sysctl_resource_pll2 = SYSCTL_RESOURCE_CLK_SRC_PLL2,
    sysctl_resource_clk0_pll2 = SYSCTL_RESOURCE_CLK_SRC_CLK0_PLL2,
    sysctl_resource_clk1_pll2 = SYSCTL_RESOURCE_CLK_SRC_CLK1_PLL2,
    sysctl_resource_pll0_ref = SYSCTL_RESOURCE_CLK_SRC_PLL0_REF,
    sysctl_resource_pll1_ref = SYSCTL_RESOURCE_CLK_SRC_PLL1_REF,
    sysctl_resource_pll2_ref = SYSCTL_RESOURCE_CLK_SRC_PLL2_REF,

    sysctl_resource_clk_top_cpu0 = SYSCTL_RESOURCE_CLK_TOP_CPU0,
    sysctl_resource_clk_top_mchtmr0 = SYSCTL_RESOURCE_CLK_TOP_MCT0,
    sysctl_resource_clk_top_cpu1 = SYSCTL_RESOURCE_CLK_TOP_CPU1,
    sysctl_resource_clk_top_mchtmr1 = SYSCTL_RESOURCE_CLK_TOP_MCT1,
    sysctl_resource_clk_top_ahb0 = SYSCTL_RESOURCE_CLK_TOP_AHB0,
    sysctl_resource_clk_top_axif = SYSCTL_RESOURCE_CLK_TOP_AXIF,
    sysctl_resource_clk_top_axis = SYSCTL_RESOURCE_CLK_TOP_AXIS,
    sysctl_resource_clk_top_axic = SYSCTL_RESOURCE_CLK_TOP_AXIC,
    sysctl_resource_clk_top_axin = SYSCTL_RESOURCE_CLK_TOP_AXIN,
    sysctl_resource_clk_top_gptmr0 = SYSCTL_RESOURCE_CLK_TOP_TMR0,
    sysctl_resource_clk_top_gptmr1 = SYSCTL_RESOURCE_CLK_TOP_TMR1,
    sysctl_resource_clk_top_gptmr2 = SYSCTL_RESOURCE_CLK_TOP_TMR2,
    sysctl_resource_clk_top_gptmr3 = SYSCTL_RESOURCE_CLK_TOP_TMR3,
    sysctl_resource_clk_top_gptmr4 = SYSCTL_RESOURCE_CLK_TOP_TMR4,
    sysctl_resource_clk_top_gptmr5 = SYSCTL_RESOURCE_CLK_TOP_TMR5,
    sysctl_resource_clk_top_gptmr6 = SYSCTL_RESOURCE_CLK_TOP_TMR6,
    sysctl_resource_clk_top_gptmr7 = SYSCTL_RESOURCE_CLK_TOP_TMR7,
    sysctl_resource_clk_top_i2c0 = SYSCTL_RESOURCE_CLK_TOP_I2C0,
    sysctl_resource_clk_top_i2c1 = SYSCTL_RESOURCE_CLK_TOP_I2C1,
    sysctl_resource_clk_top_i2c2 = SYSCTL_RESOURCE_CLK_TOP_I2C2,
    sysctl_resource_clk_top_i2c3 = SYSCTL_RESOURCE_CLK_TOP_I2C3,
    sysctl_resource_clk_top_i2c4 = SYSCTL_RESOURCE_CLK_TOP_I2C4,
    sysctl_resource_clk_top_i2c5 = SYSCTL_RESOURCE_CLK_TOP_I2C5,
    sysctl_resource_clk_top_i2c6 = SYSCTL_RESOURCE_CLK_TOP_I2C6,
    sysctl_resource_clk_top_i2c7 = SYSCTL_RESOURCE_CLK_TOP_I2C7,
    sysctl_resource_clk_top_spi0 = SYSCTL_RESOURCE_CLK_TOP_SPI0,
    sysctl_resource_clk_top_spi1 = SYSCTL_RESOURCE_CLK_TOP_SPI1,
    sysctl_resource_clk_top_spi2 = SYSCTL_RESOURCE_CLK_TOP_SPI2,
    sysctl_resource_clk_top_spi3 = SYSCTL_RESOURCE_CLK_TOP_SPI3,
    sysctl_resource_clk_top_spi4 = SYSCTL_RESOURCE_CLK_TOP_SPI4,
    sysctl_resource_clk_top_spi5 = SYSCTL_RESOURCE_CLK_TOP_SPI5,
    sysctl_resource_clk_top_spi6 = SYSCTL_RESOURCE_CLK_TOP_SPI6,
    sysctl_resource_clk_top_spi7 = SYSCTL_RESOURCE_CLK_TOP_SPI7,
    sysctl_resource_clk_top_uart0 = SYSCTL_RESOURCE_CLK_TOP_URT0,
    sysctl_resource_clk_top_uart1 = SYSCTL_RESOURCE_CLK_TOP_URT1,
    sysctl_resource_clk_top_uart2 = SYSCTL_RESOURCE_CLK_TOP_URT2,
    sysctl_resource_clk_top_uart3 = SYSCTL_RESOURCE_CLK_TOP_URT3,
    sysctl_resource_clk_top_uart4 = SYSCTL_RESOURCE_CLK_TOP_URT4,
    sysctl_resource_clk_top_uart5 = SYSCTL_RESOURCE_CLK_TOP_URT5,
    sysctl_resource_clk_top_uart6 = SYSCTL_RESOURCE_CLK_TOP_URT6,
    sysctl_resource_clk_top_uart7 = SYSCTL_RESOURCE_CLK_TOP_URT7,
    sysctl_resource_clk_top_uart8 = SYSCTL_RESOURCE_CLK_TOP_URT8,
    sysctl_resource_clk_top_uart9 = SYSCTL_RESOURCE_CLK_TOP_URT9,
    sysctl_resource_clk_top_uart10 = SYSCTL_RESOURCE_CLK_TOP_URT10,
    sysctl_resource_clk_top_uart11 = SYSCTL_RESOURCE_CLK_TOP_URT11,
    sysctl_resource_clk_top_uart12 = SYSCTL_RESOURCE_CLK_TOP_URT12,
    sysctl_resource_clk_top_uart13 = SYSCTL_RESOURCE_CLK_TOP_URT13,
    sysctl_resource_clk_top_uart14 = SYSCTL_RESOURCE_CLK_TOP_URT14,
    sysctl_resource_clk_top_uart15 = SYSCTL_RESOURCE_CLK_TOP_URT15,
    sysctl_resource_clk_top_ana0 = SYSCTL_RESOURCE_CLK_TOP_ANA0,
    sysctl_resource_clk_top_ana1 = SYSCTL_RESOURCE_CLK_TOP_ANA1,
    sysctl_resource_clk_top_ana2 = SYSCTL_RESOURCE_CLK_TOP_ANA2,
    sysctl_resource_clk_top_ana3 = SYSCTL_RESOURCE_CLK_TOP_ANA3,
    sysctl_resource_clk_top_aud0 = SYSCTL_RESOURCE_CLK_TOP_AUD0,
    sysctl_resource_clk_top_aud1 = SYSCTL_RESOURCE_CLK_TOP_AUD1,
    sysctl_resource_clk_top_can0 = SYSCTL_RESOURCE_CLK_TOP_CAN0,
    sysctl_resource_clk_top_can1 = SYSCTL_RESOURCE_CLK_TOP_CAN1,
    sysctl_resource_clk_top_can2 = SYSCTL_RESOURCE_CLK_TOP_CAN2,
    sysctl_resource_clk_top_can3 = SYSCTL_RESOURCE_CLK_TOP_CAN3,
    sysctl_resource_clk_top_can4 = SYSCTL_RESOURCE_CLK_TOP_CAN4,
    sysctl_resource_clk_top_can5 = SYSCTL_RESOURCE_CLK_TOP_CAN5,
    sysctl_resource_clk_top_can6 = SYSCTL_RESOURCE_CLK_TOP_CAN6,
    sysctl_resource_clk_top_can7 = SYSCTL_RESOURCE_CLK_TOP_CAN7,
    sysctl_resource_clk_top_xpi0 = SYSCTL_RESOURCE_CLK_TOP_XPI0,
    sysctl_resource_clk_top_femc = SYSCTL_RESOURCE_CLK_TOP_FEMC,
    sysctl_resource_clk_top_eth0 = SYSCTL_RESOURCE_CLK_TOP_ETH0,
    sysctl_resource_clk_top_ptp0 = SYSCTL_RESOURCE_CLK_TOP_PTP0,
    sysctl_resource_clk_top_ref0 = SYSCTL_RESOURCE_CLK_TOP_REF0,
    sysctl_resource_clk_top_ref1 = SYSCTL_RESOURCE_CLK_TOP_REF1,
    sysctl_resource_clk_top_ntm0 = SYSCTL_RESOURCE_CLK_TOP_NTM0,
    sysctl_resource_clk_top_tsn1 = SYSCTL_RESOURCE_CLK_TOP_TSW1,
    sysctl_resource_clk_top_tsn2 = SYSCTL_RESOURCE_CLK_TOP_TSW2,
    sysctl_resource_clk_top_tsn3 = SYSCTL_RESOURCE_CLK_TOP_TSW3,
    sysctl_resource_clk_top_adc0 = SYSCTL_RESOURCE_CLK_TOP_ADC0,
    sysctl_resource_clk_top_adc1 = SYSCTL_RESOURCE_CLK_TOP_ADC1,
    sysctl_resource_clk_top_adc2 = SYSCTL_RESOURCE_CLK_TOP_ADC2,
    sysctl_resource_clk_top_adc3 = SYSCTL_RESOURCE_CLK_TOP_ADC3,
    sysctl_resource_clk_top_i2s0 = SYSCTL_RESOURCE_CLK_TOP_I2S0,
    sysctl_resource_clk_top_i2s1 = SYSCTL_RESOURCE_CLK_TOP_I2S1,

    sysctl_resource_linkable_start = 256,
    sysctl_resource_ahbp = SYSCTL_RESOURCE_AHBP,
    sysctl_resource_axis = SYSCTL_RESOURCE_AXIS,
    sysctl_resource_axic = SYSCTL_RESOURCE_AXIC,
    sysctl_resource_axin = SYSCTL_RESOURCE_AXIN,
    sysctl_resource_rom0 = SYSCTL_RESOURCE_ROM0,
    sysctl_resource_lmm0 = SYSCTL_RESOURCE_LMM0,
    sysctl_resource_mchtmr0 = SYSCTL_RESOURCE_MCT0,
    sysctl_resource_lmm1 = SYSCTL_RESOURCE_LMM1,
    sysctl_resource_mchtmr1 = SYSCTL_RESOURCE_MCT1,
    sysctl_resource_gptmr0 = SYSCTL_RESOURCE_TMR0,
    sysctl_resource_gptmr1 = SYSCTL_RESOURCE_TMR1,
    sysctl_resource_gptmr2 = SYSCTL_RESOURCE_TMR2,
    sysctl_resource_gptmr3 = SYSCTL_RESOURCE_TMR3,
    sysctl_resource_gptmr4 = SYSCTL_RESOURCE_TMR4,
    sysctl_resource_gptmr5 = SYSCTL_RESOURCE_TMR5,
    sysctl_resource_gptmr6 = SYSCTL_RESOURCE_TMR6,
    sysctl_resource_gptmr7 = SYSCTL_RESOURCE_TMR7,
    sysctl_resource_i2c0 = SYSCTL_RESOURCE_I2C0,
    sysctl_resource_i2c1 = SYSCTL_RESOURCE_I2C1,
    sysctl_resource_i2c2 = SYSCTL_RESOURCE_I2C2,
    sysctl_resource_i2c3 = SYSCTL_RESOURCE_I2C3,
    sysctl_resource_i2c4 = SYSCTL_RESOURCE_I2C4,
    sysctl_resource_i2c5 = SYSCTL_RESOURCE_I2C5,
    sysctl_resource_i2c6 = SYSCTL_RESOURCE_I2C6,
    sysctl_resource_i2c7 = SYSCTL_RESOURCE_I2C7,
    sysctl_resource_spi0 = SYSCTL_RESOURCE_SPI0,
    sysctl_resource_spi1 = SYSCTL_RESOURCE_SPI1,
    sysctl_resource_spi2 = SYSCTL_RESOURCE_SPI2,
    sysctl_resource_spi3 = SYSCTL_RESOURCE_SPI3,
    sysctl_resource_spi4 = SYSCTL_RESOURCE_SPI4,
    sysctl_resource_spi5 = SYSCTL_RESOURCE_SPI5,
    sysctl_resource_spi6 = SYSCTL_RESOURCE_SPI6,
    sysctl_resource_spi7 = SYSCTL_RESOURCE_SPI7,
    sysctl_resource_uart0 = SYSCTL_RESOURCE_URT0,
    sysctl_resource_uart1 = SYSCTL_RESOURCE_URT1,
    sysctl_resource_uart2 = SYSCTL_RESOURCE_URT2,
    sysctl_resource_uart3 = SYSCTL_RESOURCE_URT3,
    sysctl_resource_uart4 = SYSCTL_RESOURCE_URT4,
    sysctl_resource_uart5 = SYSCTL_RESOURCE_URT5,
    sysctl_resource_uart6 = SYSCTL_RESOURCE_URT6,
    sysctl_resource_uart7 = SYSCTL_RESOURCE_URT7,
    sysctl_resource_uart8 = SYSCTL_RESOURCE_URT8,
    sysctl_resource_uart9 = SYSCTL_RESOURCE_URT9,
    sysctl_resource_uart10 = SYSCTL_RESOURCE_URT10,
    sysctl_resource_uart11 = SYSCTL_RESOURCE_URT11,
    sysctl_resource_uart12 = SYSCTL_RESOURCE_URT12,
    sysctl_resource_uart13 = SYSCTL_RESOURCE_URT13,
    sysctl_resource_uart14 = SYSCTL_RESOURCE_URT14,
    sysctl_resource_uart15 = SYSCTL_RESOURCE_URT15,
    sysctl_resource_crc0 = SYSCTL_RESOURCE_CRC0,
    sysctl_resource_tsns = SYSCTL_RESOURCE_TSNS,
    sysctl_resource_wdg0 = SYSCTL_RESOURCE_WDG0,
    sysctl_resource_wdg1 = SYSCTL_RESOURCE_WDG1,
    sysctl_resource_wdg2 = SYSCTL_RESOURCE_WDG2,
    sysctl_resource_wdg3 = SYSCTL_RESOURCE_WDG3,
    sysctl_resource_mbx0 = SYSCTL_RESOURCE_MBX0,
    sysctl_resource_mbx1 = SYSCTL_RESOURCE_MBX1,
    sysctl_resource_gpio = SYSCTL_RESOURCE_GPIO,
    sysctl_resource_ppi0 = SYSCTL_RESOURCE_PPI0,
    sysctl_resource_hdma = SYSCTL_RESOURCE_HDMA,
    sysctl_resource_lobs = SYSCTL_RESOURCE_LOBS,
    sysctl_resource_adc0 = SYSCTL_RESOURCE_ADC0,
    sysctl_resource_adc1 = SYSCTL_RESOURCE_ADC1,
    sysctl_resource_adc2 = SYSCTL_RESOURCE_ADC2,
    sysctl_resource_adc3 = SYSCTL_RESOURCE_ADC3,
    sysctl_resource_cmp0 = SYSCTL_RESOURCE_CMP0,
    sysctl_resource_cmp1 = SYSCTL_RESOURCE_CMP1,
    sysctl_resource_cmp2 = SYSCTL_RESOURCE_CMP2,
    sysctl_resource_cmp3 = SYSCTL_RESOURCE_CMP3,
    sysctl_resource_i2s0 = SYSCTL_RESOURCE_I2S0,
    sysctl_resource_i2s1 = SYSCTL_RESOURCE_I2S1,
    sysctl_resource_i2spdm0 = SYSCTL_RESOURCE_PDM0,
    sysctl_resource_i2sdao = SYSCTL_RESOURCE_CLSD,
    sysctl_resource_can0 = SYSCTL_RESOURCE_CAN0,
    sysctl_resource_can1 = SYSCTL_RESOURCE_CAN1,
    sysctl_resource_can2 = SYSCTL_RESOURCE_CAN2,
    sysctl_resource_can3 = SYSCTL_RESOURCE_CAN3,
    sysctl_resource_can4 = SYSCTL_RESOURCE_CAN4,
    sysctl_resource_can5 = SYSCTL_RESOURCE_CAN5,
    sysctl_resource_can6 = SYSCTL_RESOURCE_CAN6,
    sysctl_resource_can7 = SYSCTL_RESOURCE_CAN7,
    sysctl_resource_ptpc = SYSCTL_RESOURCE_PTPC,
    sysctl_resource_qei0 = SYSCTL_RESOURCE_QEI0,
    sysctl_resource_qei1 = SYSCTL_RESOURCE_QEI1,
    sysctl_resource_qei2 = SYSCTL_RESOURCE_QEI2,
    sysctl_resource_qei3 = SYSCTL_RESOURCE_QEI3,
    sysctl_resource_qeo0 = SYSCTL_RESOURCE_QEO0,
    sysctl_resource_qeo1 = SYSCTL_RESOURCE_QEO1,
    sysctl_resource_qeo2 = SYSCTL_RESOURCE_QEO2,
    sysctl_resource_qeo3 = SYSCTL_RESOURCE_QEO3,
    sysctl_resource_pwm0 = SYSCTL_RESOURCE_PWM0,
    sysctl_resource_pwm1 = SYSCTL_RESOURCE_PWM1,
    sysctl_resource_pwm2 = SYSCTL_RESOURCE_PWM2,
    sysctl_resource_pwm3 = SYSCTL_RESOURCE_PWM3,
    sysctl_resource_rdc0 = SYSCTL_RESOURCE_RDC0,
    sysctl_resource_rdc1 = SYSCTL_RESOURCE_RDC1,
    sysctl_resource_sdm0 = SYSCTL_RESOURCE_SDM0,
    sysctl_resource_sdm1 = SYSCTL_RESOURCE_SDM1,
    sysctl_resource_plb0 = SYSCTL_RESOURCE_PLB0,
    sysctl_resource_sei0 = SYSCTL_RESOURCE_SEI0,
    sysctl_resource_mtg0 = SYSCTL_RESOURCE_MTG0,
    sysctl_resource_mtg1 = SYSCTL_RESOURCE_MTG1,
    sysctl_resource_vsc0 = SYSCTL_RESOURCE_VSC0,
    sysctl_resource_vsc1 = SYSCTL_RESOURCE_VSC1,
    sysctl_resource_clc0 = SYSCTL_RESOURCE_CLC0,
    sysctl_resource_clc1 = SYSCTL_RESOURCE_CLC1,
    sysctl_resource_emds = SYSCTL_RESOURCE_EMDS,
    sysctl_resource_rng0 = SYSCTL_RESOURCE_RNG0,
    sysctl_resource_sdp0 = SYSCTL_RESOURCE_SDP0,
    sysctl_resource_pka0 = SYSCTL_RESOURCE_PKA0,
    sysctl_resource_kman = SYSCTL_RESOURCE_KMAN,
    sysctl_resource_xpi0 = SYSCTL_RESOURCE_XPI0,
    sysctl_resource_femc = SYSCTL_RESOURCE_FEMC,
    sysctl_resource_ram0 = SYSCTL_RESOURCE_RAM0,
    sysctl_resource_ram1 = SYSCTL_RESOURCE_RAM1,
    sysctl_resource_xdma = SYSCTL_RESOURCE_XDMA,
    sysctl_resource_ffa0 = SYSCTL_RESOURCE_FFA0,
    sysctl_resource_eth0 = SYSCTL_RESOURCE_ETH0,
    sysctl_resource_usb0 = SYSCTL_RESOURCE_USB0,
    sysctl_resource_ntmr0 = SYSCTL_RESOURCE_NTM0,
    sysctl_resource_ref0 = SYSCTL_RESOURCE_REF0,
    sysctl_resource_ref1 = SYSCTL_RESOURCE_REF1,
    sysctl_resource_tsn0 = SYSCTL_RESOURCE_TSW0,
    sysctl_resource_esc0 = SYSCTL_RESOURCE_ESC0,
    sysctl_resource_linkable_end,
    sysctl_resource_end = sysctl_resource_linkable_end,
} sysctl_resource_t;

/**
 * @brief Resource modes
 */
typedef enum {
    sysctl_resource_mode_auto = 0,  /*!< Resource clock is automatically managed by system request */
    sysctl_resource_mode_force_on,  /*!< Force the resource clock on */
    sysctl_resource_mode_force_off, /*!< Force the resource clock off */
} sysctl_resource_mode_t;

/**
 * @brief Clock nodes
 */
typedef enum {
    clock_node_cpu0 = SYSCTL_CLOCK_CLK_TOP_CPU0,
    clock_node_mchtmr0 = SYSCTL_CLOCK_CLK_TOP_MCT0,
    clock_node_cpu1 = SYSCTL_CLOCK_CLK_TOP_CPU1,
    clock_node_mchtmr1 = SYSCTL_CLOCK_CLK_TOP_MCT1,
    clock_node_ahb0 = SYSCTL_CLOCK_CLK_TOP_AHB0,
    clock_node_axif = SYSCTL_CLOCK_CLK_TOP_AXIF,
    clock_node_axis = SYSCTL_CLOCK_CLK_TOP_AXIS,
    clock_node_axic = SYSCTL_CLOCK_CLK_TOP_AXIC,
    clock_node_axin = SYSCTL_CLOCK_CLK_TOP_AXIN,
    clock_node_gptmr0 = SYSCTL_CLOCK_CLK_TOP_TMR0,
    clock_node_gptmr1 = SYSCTL_CLOCK_CLK_TOP_TMR1,
    clock_node_gptmr2 = SYSCTL_CLOCK_CLK_TOP_TMR2,
    clock_node_gptmr3 = SYSCTL_CLOCK_CLK_TOP_TMR3,
    clock_node_gptmr4 = SYSCTL_CLOCK_CLK_TOP_TMR4,
    clock_node_gptmr5 = SYSCTL_CLOCK_CLK_TOP_TMR5,
    clock_node_gptmr6 = SYSCTL_CLOCK_CLK_TOP_TMR6,
    clock_node_gptmr7 = SYSCTL_CLOCK_CLK_TOP_TMR7,
    clock_node_i2c0 = SYSCTL_CLOCK_CLK_TOP_I2C0,
    clock_node_i2c1 = SYSCTL_CLOCK_CLK_TOP_I2C1,
    clock_node_i2c2 = SYSCTL_CLOCK_CLK_TOP_I2C2,
    clock_node_i2c3 = SYSCTL_CLOCK_CLK_TOP_I2C3,
    clock_node_i2c4 = SYSCTL_CLOCK_CLK_TOP_I2C4,
    clock_node_i2c5 = SYSCTL_CLOCK_CLK_TOP_I2C5,
    clock_node_i2c6 = SYSCTL_CLOCK_CLK_TOP_I2C6,
    clock_node_i2c7 = SYSCTL_CLOCK_CLK_TOP_I2C7,
    clock_node_spi0 = SYSCTL_CLOCK_CLK_TOP_SPI0,
    clock_node_spi1 = SYSCTL_CLOCK_CLK_TOP_SPI1,
    clock_node_spi2 = SYSCTL_CLOCK_CLK_TOP_SPI2,
    clock_node_spi3 = SYSCTL_CLOCK_CLK_TOP_SPI3,
    clock_node_spi4 = SYSCTL_CLOCK_CLK_TOP_SPI4,
    clock_node_spi5 = SYSCTL_CLOCK_CLK_TOP_SPI5,
    clock_node_spi6 = SYSCTL_CLOCK_CLK_TOP_SPI6,
    clock_node_spi7 = SYSCTL_CLOCK_CLK_TOP_SPI7,
    clock_node_uart0 = SYSCTL_CLOCK_CLK_TOP_URT0,
    clock_node_uart1 = SYSCTL_CLOCK_CLK_TOP_URT1,
    clock_node_uart2 = SYSCTL_CLOCK_CLK_TOP_URT2,
    clock_node_uart3 = SYSCTL_CLOCK_CLK_TOP_URT3,
    clock_node_uart4 = SYSCTL_CLOCK_CLK_TOP_URT4,
    clock_node_uart5 = SYSCTL_CLOCK_CLK_TOP_URT5,
    clock_node_uart6 = SYSCTL_CLOCK_CLK_TOP_URT6,
    clock_node_uart7 = SYSCTL_CLOCK_CLK_TOP_URT7,
    clock_node_uart8 = SYSCTL_CLOCK_CLK_TOP_URT8,
    clock_node_uart9 = SYSCTL_CLOCK_CLK_TOP_URT9,
    clock_node_uart10 = SYSCTL_CLOCK_CLK_TOP_URT10,
    clock_node_uart11 = SYSCTL_CLOCK_CLK_TOP_URT11,
    clock_node_uart12 = SYSCTL_CLOCK_CLK_TOP_URT12,
    clock_node_uart13 = SYSCTL_CLOCK_CLK_TOP_URT13,
    clock_node_uart14 = SYSCTL_CLOCK_CLK_TOP_URT14,
    clock_node_uart15 = SYSCTL_CLOCK_CLK_TOP_URT15,
    clock_node_ana0 = SYSCTL_CLOCK_CLK_TOP_ANA0,
    clock_node_ana1 = SYSCTL_CLOCK_CLK_TOP_ANA1,
    clock_node_ana2 = SYSCTL_CLOCK_CLK_TOP_ANA2,
    clock_node_ana3 = SYSCTL_CLOCK_CLK_TOP_ANA3,
    clock_node_aud0 = SYSCTL_CLOCK_CLK_TOP_AUD0,
    clock_node_aud1 = SYSCTL_CLOCK_CLK_TOP_AUD1,
    clock_node_can0 = SYSCTL_CLOCK_CLK_TOP_CAN0,
    clock_node_can1 = SYSCTL_CLOCK_CLK_TOP_CAN1,
    clock_node_can2 = SYSCTL_CLOCK_CLK_TOP_CAN2,
    clock_node_can3 = SYSCTL_CLOCK_CLK_TOP_CAN3,
    clock_node_can4 = SYSCTL_CLOCK_CLK_TOP_CAN4,
    clock_node_can5 = SYSCTL_CLOCK_CLK_TOP_CAN5,
    clock_node_can6 = SYSCTL_CLOCK_CLK_TOP_CAN6,
    clock_node_can7 = SYSCTL_CLOCK_CLK_TOP_CAN7,
    clock_node_xpi0 = SYSCTL_CLOCK_CLK_TOP_XPI0,
    clock_node_femc = SYSCTL_CLOCK_CLK_TOP_FEMC,
    clock_node_eth0 = SYSCTL_CLOCK_CLK_TOP_ETH0,
    clock_node_ptp0 = SYSCTL_CLOCK_CLK_TOP_PTP0,
    clock_node_ntmr0 = SYSCTL_CLOCK_CLK_TOP_NTM0,
    clock_node_ref0 = SYSCTL_CLOCK_CLK_TOP_REF0,
    clock_node_ref1 = SYSCTL_CLOCK_CLK_TOP_REF1,
    clock_node_tsn1 = SYSCTL_CLOCK_CLK_TOP_TSW1,
    clock_node_tsn2 = SYSCTL_CLOCK_CLK_TOP_TSW2,
    clock_node_tsn3 = SYSCTL_CLOCK_CLK_TOP_TSW3,

    clock_node_adc_start,
    clock_node_adc0 = clock_node_adc_start,
    clock_node_adc1,
    clock_node_adc2,
    clock_node_adc3,

    clock_node_i2s_start,
    clock_node_i2s0 = clock_node_i2s_start,
    clock_node_i2s1,
    clock_node_end,
} clock_node_t;

/**
 * @brief General clock sources
 */
typedef enum {
    clock_source_osc0_clk0 = 0,
    clock_source_pll0_clk0 = 1,
    clock_source_pll0_clk1 = 2,
    clock_source_pll1_clk0 = 3,
    clock_source_pll1_clk1 = 4,
    clock_source_pll1_clk2 = 5,
    clock_source_pll2_clk0 = 6,
    clock_source_pll2_clk1 = 7,
    clock_source_general_source_end,
} clock_source_t;

/**
 * @brief ADC clock sources
 */
typedef enum {
    clock_source_adc_ana_clock = 0,
    clock_source_adc_ahb_clock = 1,
    clock_source_adc_clk_end,
} clock_source_adc_t;

/**
 * @brief I2S clock sources
 */
typedef enum {
    clock_source_i2s_audn_clock = 0,
    clock_source_i2s_audx_clock = 1,
    clock_source_i2s_clk_end,
} clock_source_i2s_t;

/**
 * @brief CPU low power mode
 */
typedef enum {
    cpu_lp_mode_gate_cpu_clock = 0,
    cpu_lp_mode_trigger_system_lp = 0x1,
    cpu_lp_mode_ungate_cpu_clock = 0x2,
} cpu_lp_mode_t;

/**
 * @brief Monitor targets
 */
/* Monitor Target types */
typedef enum {
    monitor_target_clk_32k_batt = 0,
    monitor_target_clk_32k_pmic = 1,
    monitor_target_clk_irc24m = 2,
    monitor_target_clk_xtal_24m = 3,
    monitor_target_clk_usb0_phy = 4,
    monitor_target_clk0_osc0 = 20,
    monitor_target_clk0_pll0 = 21,
    monitor_target_clk1_pll0 = 22,
    monitor_target_clk0_pll1 = 23,
    monitor_target_clk1_pll1 = 24,
    monitor_target_clk2_pll1 = 25,
    monitor_target_clk0_pll2 = 26,
    monitor_target_clk1_pll2 = 27,
    monitor_target_clk_top_cpu0 = 128,
    monitor_target_clk_top_mchtmr0 = 129,
    monitor_target_clk_top_cpu1 = 130,
    monitor_target_clk_top_mchtmr1 = 131,
    monitor_target_clk_top_axif = 132,
    monitor_target_clk_top_axis = 133,
    monitor_target_clk_top_axic = 134,
    monitor_target_clk_top_axin = 135,
    monitor_target_clk_top_ahb0 = 136,
    monitor_target_clk_top_gptmr0 = 137,
    monitor_target_clk_top_gptmr1 = 138,
    monitor_target_clk_top_gptmr2 = 139,
    monitor_target_clk_top_gptmr3 = 140,
    monitor_target_clk_top_gptmr4 = 141,
    monitor_target_clk_top_gptmr5 = 142,
    monitor_target_clk_top_gptmr6 = 143,
    monitor_target_clk_top_gptmr7 = 144,
    monitor_target_clk_top_i2c0 = 145,
    monitor_target_clk_top_i2c1 = 146,
    monitor_target_clk_top_i2c2 = 147,
    monitor_target_clk_top_i2c3 = 148,
    monitor_target_clk_top_i2c4 = 149,
    monitor_target_clk_top_i2c5 = 150,
    monitor_target_clk_top_i2c6 = 151,
    monitor_target_clk_top_i2c7 = 152,
    monitor_target_clk_top_spi0 = 153,
    monitor_target_clk_top_spi1 = 154,
    monitor_target_clk_top_spi2 = 155,
    monitor_target_clk_top_spi3 = 156,
    monitor_target_clk_top_spi4 = 157,
    monitor_target_clk_top_spi5 = 158,
    monitor_target_clk_top_spi6 = 159,
    monitor_target_clk_top_spi7 = 160,
    monitor_target_clk_top_uart0 = 161,
    monitor_target_clk_top_uart1 = 162,
    monitor_target_clk_top_uart2 = 163,
    monitor_target_clk_top_uart3 = 164,
    monitor_target_clk_top_uart4 = 165,
    monitor_target_clk_top_uart5 = 166,
    monitor_target_clk_top_uart6 = 167,
    monitor_target_clk_top_uart7 = 168,
    monitor_target_clk_top_uart8 = 169,
    monitor_target_clk_top_uart9 = 170,
    monitor_target_clk_top_uart10 = 171,
    monitor_target_clk_top_uart11 = 172,
    monitor_target_clk_top_uart12 = 173,
    monitor_target_clk_top_uart13 = 174,
    monitor_target_clk_top_uart14 = 175,
    monitor_target_clk_top_uart15 = 176,
    monitor_target_clk_top_can0 = 177,
    monitor_target_clk_top_can1 = 178,
    monitor_target_clk_top_can2 = 179,
    monitor_target_clk_top_can3 = 180,
    monitor_target_clk_top_can4 = 181,
    monitor_target_clk_top_can5 = 182,
    monitor_target_clk_top_can6 = 183,
    monitor_target_clk_top_can7 = 184,
    monitor_target_clk_top_xpi0 = 185,
    monitor_target_clk_top_femc = 186,
    monitor_target_clk_top_ana0 = 187,
    monitor_target_clk_top_ana1 = 188,
    monitor_target_clk_top_ana2 = 189,
    monitor_target_clk_top_ana3 = 190,
    monitor_target_clk_top_aud0 = 191,
    monitor_target_clk_top_aud1 = 192,
    monitor_target_clk_top_eth0 = 193,
    monitor_target_clk_top_ptp0 = 194,
    monitor_target_clk_top_ref0 = 195,
    monitor_target_clk_top_ref1 = 196,
    monitor_target_clk_top_ntmr0 = 197,
    monitor_target_clk_top_tsn1 = 198,
    monitor_target_clk_top_tsn2 = 199,
    monitor_target_clk_top_tsn3 = 200,
} monitor_target_t;

/**
 * @brief Monitor work mode
 */
typedef enum {
    monitor_work_mode_compare = 0,
    monitor_work_mode_record = 1,
} monitor_work_mode_t;

/**
 * @brief Monitor accuracy
 */
typedef enum {
    monitor_accuracy_1khz = 0,
    monitor_accuracy_1hz = 1,
} monitor_accuracy_t;

/**
 * @brief Monitor reference clock source
 */
typedef enum {
    monitor_reference_32khz = 0,
    monitor_reference_24mhz = 1,
} monitor_reference_t;

typedef enum {
    cpu_event_flag_mask_reset = SYSCTL_CPU_LP_RESET_FLAG_MASK,
    cpu_event_flag_mask_sleep = SYSCTL_CPU_LP_SLEEP_FLAG_MASK,
    cpu_event_flag_mask_wake = SYSCTL_CPU_LP_WAKE_FLAG_MASK,
    cpu_event_flag_mask_all = SYSCTL_CPU_LP_RESET_FLAG_MASK | SYSCTL_CPU_LP_SLEEP_FLAG_MASK | SYSCTL_CPU_LP_WAKE_FLAG_MASK,
} cpu_event_flag_mask_t;

/**
 * @brief Monitor config
 */
typedef struct monitor_config {
    uint8_t divide_by;              /**< Divider to be used for OBS output to pads */
    monitor_work_mode_t mode;       /**< Monitor work mode */
    monitor_accuracy_t accuracy;    /**< Monitor reference accuracy */
    monitor_reference_t reference;  /**< Monitor reference clock source */
    monitor_target_t target;        /**< Monitor target */
    bool start_measure;             /**< Start flag */
    bool enable_output;             /**< Enable output to pads if true */
    uint32_t high_limit;            /**< Maximum frequency at compare mode */
    uint32_t low_limit;             /**< Minimum frequency at compare mode */
} monitor_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Check if monitor result is valid
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 *
 * @return true if it is valid
 */
static inline bool sysctl_monitor_result_is_valid(SYSCTL_Type *ptr, uint8_t monitor_index)
{
    return SYSCTL_MONITOR_CONTROL_VALID_GET(ptr->MONITOR[monitor_index].CONTROL);
}

/**
 * @brief Get target monitor instance result
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @return value of monitor result measured
 */
static inline uint32_t sysctl_monitor_get_current_result(SYSCTL_Type *ptr, uint8_t monitor_index)
{
    while (!sysctl_monitor_result_is_valid(ptr, monitor_index)) {
    }
    return ptr->MONITOR[monitor_index].CURRENT;
}

/**
 * @brief Set work mode for target monitor instance
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @param[in] mode monitor_work_mode_compare, monitor_work_mode_record
 */
static inline void sysctl_monitor_set_work_mode(SYSCTL_Type *ptr, uint8_t monitor_index, monitor_work_mode_t mode)
{
    ptr->MONITOR[monitor_index].CONTROL = (ptr->MONITOR[monitor_index].CONTROL & ~SYSCTL_MONITOR_CONTROL_MODE_MASK) |
        (SYSCTL_MONITOR_CONTROL_MODE_SET(mode));
}

/**
 * @brief Set minimum frequency for target monitor instance
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @param[in] limit measurement low limit
 */
static inline hpm_stat_t sysctl_monitor_set_limit_low(SYSCTL_Type *ptr, uint8_t monitor_index, uint32_t limit)
{
    if (ptr->MONITOR[monitor_index].CONTROL & SYSCTL_MONITOR_CONTROL_MODE_MASK) {
        return status_invalid_argument;
    }
    ptr->MONITOR[monitor_index].LOW_LIMIT = SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(limit);
    return status_success;
}

/**
 * @brief Set maximum frequency for target monitor instance
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @param[in] limit measurement high limit
 */
static inline hpm_stat_t sysctl_monitor_set_limit_high(SYSCTL_Type *ptr, uint8_t monitor_index, uint32_t limit)
{
    if (ptr->MONITOR[monitor_index].CONTROL & SYSCTL_MONITOR_CONTROL_MODE_MASK) {
        return status_invalid_argument;
    }
    ptr->MONITOR[monitor_index].HIGH_LIMIT = SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SET(limit);
    return status_success;
}

/**
 * @brief Set frequency limit for target monitor instance
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @param[in] limit_high measurement high limit
 * @param[in] limit_low measurement low limit
 */
static inline hpm_stat_t sysctl_monitor_set_limit(SYSCTL_Type *ptr,
                                                  uint8_t monitor_index,
                                                  uint32_t limit_high,
                                                  uint32_t limit_low)
{
    if (ptr->MONITOR[monitor_index].CONTROL & SYSCTL_MONITOR_CONTROL_MODE_MASK) {
        return status_invalid_argument;
    }
    ptr->MONITOR[monitor_index].HIGH_LIMIT = SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SET(limit_high);
    ptr->MONITOR[monitor_index].LOW_LIMIT = SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(limit_low);
    return status_success;
}

/**
 * @brief Get maximum frequency for target monitor instance
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @return current high limit value
 */
static inline uint32_t sysctl_monitor_get_limit_high(SYSCTL_Type *ptr, uint32_t monitor_index)
{
    return SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_GET(ptr->MONITOR[monitor_index].HIGH_LIMIT);
}

/**
 * @brief Get minimum frequency for target monitor instance
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @return current low limit value
 */
static inline uint32_t sysctl_monitor_get_limit_low(SYSCTL_Type *ptr, uint32_t monitor_index)
{
    return SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(ptr->MONITOR[monitor_index].LOW_LIMIT);
}

/**
 * @brief Measure specific target frequency
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index specific monitor instance to be used
 * @param[in] target monitor target to be measured
 * @param[in] enable_output enable clock obs output
 * @return frequency of monitor target measured
 */
uint32_t sysctl_monitor_measure_frequency(SYSCTL_Type *ptr,
                                          uint8_t monitor_index,
                                          monitor_target_t target,
                                          bool enable_output);

/**
 * @brief Link current CPU core its own group
 *
 * Once it is linked, peripherals state in that group will keep on as long as this core is not in low power mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index cpu index to enable its own affiliated group
 */
static inline void sysctl_set_enable_cpu_affiliate(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    ptr->AFFILIATE[cpu_index].SET = 1 << cpu_index;
}

/**
 * @brief Unlink current CPU core with its own group
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index cpu index to enable its own affiliated group
 */
static inline void sysctl_set_disable_cpu_affiliate(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    ptr->AFFILIATE[cpu_index].CLEAR = 1 << cpu_index;
}

/**
 * @brief Check if any resource is busy
 *
 * @param[in] ptr SYSCTL_Type base address
 * @return true if any resource is busy
 */
static inline bool sysctl_resource_any_is_busy(SYSCTL_Type *ptr)
{
    return ptr->RESOURCE[0] & SYSCTL_RESOURCE_GLB_BUSY_MASK;
}

/**
 * @brief Check if specific target is busy
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource target resource index
 * @return true if target resource is busy
 */
static inline bool sysctl_resource_target_is_busy(SYSCTL_Type *ptr, sysctl_resource_t resource)
{
    return ptr->RESOURCE[resource] & SYSCTL_RESOURCE_LOC_BUSY_MASK;
}

/**
 * @brief Set target mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource target resource index
 * @param[in] mode target resource mode
 */
static inline void sysctl_resource_target_set_mode(SYSCTL_Type *ptr,
                                                   sysctl_resource_t resource,
                                                   sysctl_resource_mode_t mode)
{
    ptr->RESOURCE[resource] =
        (ptr->RESOURCE[resource] & ~SYSCTL_RESOURCE_MODE_MASK) |
        SYSCTL_RESOURCE_MODE_SET(mode);
}

/**
 * @brief Get target mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource target resource index
 * @return target resource mode
 */
static inline uint8_t sysctl_resource_target_get_mode(SYSCTL_Type *ptr,
                                                   sysctl_resource_t resource)
{
    return SYSCTL_RESOURCE_MODE_GET(ptr->RESOURCE[resource]);
}

/**
 * @brief Disable resource retention when specific CPU enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index cpu index
 * @param[in] mask bit mask to clear
 */
static inline void sysctl_clear_cpu_lp_retention_with_mask(SYSCTL_Type *ptr, uint8_t cpu_index, uint32_t mask)
{
    ptr->RETENTION[cpu_index].CLEAR = mask;
}

/**
 * @brief Disable resource retention when CPU0 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mask bit mask to clear
 */
static inline void sysctl_clear_cpu0_lp_retention_with_mask(SYSCTL_Type *ptr, uint32_t mask)
{
    sysctl_clear_cpu_lp_retention_with_mask(ptr, 0, mask);
}

/**
 * @brief Disable resource retention when CPU1 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mask bit mask to clear
 */
static inline void sysctl_clear_cpu1_lp_retention_with_mask(SYSCTL_Type *ptr, uint32_t mask)
{
    sysctl_clear_cpu_lp_retention_with_mask(ptr, 1, mask);
}

/**
 * @brief Enable resource retention when specific CPU enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index cpu index
 * @param[in] mask bit mask to set
 */
static inline void sysctl_set_cpu_lp_retention_with_mask(SYSCTL_Type *ptr, uint8_t cpu_index, uint32_t mask)
{
    ptr->RETENTION[cpu_index].SET = mask;
}

/**
 * @brief Enable resource retention when CPU0 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mask bit mask to set
 */
static inline void sysctl_set_cpu0_lp_retention_with_mask(SYSCTL_Type *ptr, uint32_t mask)
{
    sysctl_set_cpu_lp_retention_with_mask(ptr, 0, mask);
}

/**
 * @brief Enable resource retention when CPU1 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mask bit mask to set
 */
static inline void sysctl_set_cpu1_lp_retention_with_mask(SYSCTL_Type *ptr, uint32_t mask)
{
    sysctl_set_cpu_lp_retention_with_mask(ptr, 1, mask);
}

/**
 * @brief Enable resource retention when specific CPU enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index cpu index
 * @param[in] value value to be set
 */
static inline void sysctl_set_cpu_lp_retention(SYSCTL_Type *ptr, uint8_t cpu_index, uint32_t value)
{
    ptr->RETENTION[cpu_index].VALUE = value;
}

/**
 * @brief Enable resource retention when CPU0 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] value value to be set
 */
static inline void sysctl_set_cpu0_lp_retention(SYSCTL_Type *ptr, uint32_t value)
{
    sysctl_set_cpu_lp_retention(ptr, 0, value);
}

/**
 * @brief Enable resource retention when CPU1 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] value value to be set
 */
static inline void sysctl_set_cpu1_lp_retention(SYSCTL_Type *ptr, uint32_t value)
{
    sysctl_set_cpu_lp_retention(ptr, 1, value);
}

/**
 * @brief Retain target domain for specific CPU
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] domain target domain power to be retained
 * @param[in] retain_mem set true to retain memory/register of target domain
 */
static inline void sysctl_set_cpu_lp_retain_domain(SYSCTL_Type *ptr,
                                                   uint8_t cpu_index,
                                                   sysctl_retention_domain_t domain,
                                                   bool retain_mem)
{
    uint8_t set_mask = 0x1;
    if (domain < sysctl_retention_domain_xtal24m) {
        set_mask = retain_mem ? 0x3 : 0x1;
    }
    ptr->RETENTION[cpu_index].SET = (set_mask << domain);
}

/**
 * @brief Retain target domain for specific CPU0
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain power to be retained
 * @param[in] retain_mem set true to retain memory/register of target domain
 */
static inline void sysctl_set_cpu0_lp_retain_domain(SYSCTL_Type *ptr,
                                                    sysctl_retention_domain_t domain,
                                                    bool retain_mem)
{
    sysctl_set_cpu_lp_retain_domain(ptr, 0, domain, retain_mem);
}

/**
 * @brief Retain target domain for specific CPU
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain power to be retained
 * @param[in] retain_mem set true to retain memory/register of target domain
 */
static inline void sysctl_set_cpu1_lp_retain_domain(SYSCTL_Type *ptr,
                                                    sysctl_retention_domain_t domain,
                                                    bool retain_mem)
{
    sysctl_set_cpu_lp_retain_domain(ptr, 1, domain, retain_mem);
}

/**
 * @brief Check if any clock is busy
 *
 * @param[in] ptr SYSCTL_Type base address
 * @return true if any clock is busy
 */
static inline bool sysctl_clock_any_is_busy(SYSCTL_Type *ptr)
{
    return ptr->CLOCK[0] & SYSCTL_CLOCK_GLB_BUSY_MASK;
}

/**
 * @brief Check if target clock is busy
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] clock target clock
 * @return true if target clock is busy
 */
static inline bool sysctl_clock_target_is_busy(SYSCTL_Type *ptr, uint32_t clock)
{
    return ptr->CLOCK[clock] & SYSCTL_CLOCK_LOC_BUSY_MASK;
}

/**
 * @brief Preserve clock setting for certain node
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] clock target clock
 */
static inline void sysctl_clock_preserve_settings(SYSCTL_Type *ptr, clock_node_t clock)
{
    ptr->CLOCK[clock] |= SYSCTL_CLOCK_PRESERVE_MASK;
}

/**
 * @brief Unpreserve clock setting for certain node
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] clock target clock
 */
static inline void sysctl_clock_unpreserve_settings(SYSCTL_Type *ptr, clock_node_t clock)
{
    ptr->CLOCK[clock] &= ~SYSCTL_CLOCK_PRESERVE_MASK;
}

/**
 * @brief Set clock preset
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] preset preset
 */
static inline void sysctl_clock_set_preset(SYSCTL_Type *ptr, sysctl_preset_t preset)
{
    ptr->GLOBAL00 = (ptr->GLOBAL00 & ~SYSCTL_GLOBAL00_MUX_MASK) | SYSCTL_GLOBAL00_MUX_SET(preset);
}

/**
 * @brief Check if target reset domain wakeup status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain to be checked
 * @return true if target domain was taken wakeup reset
 */
static inline bool sysctl_reset_check_target_domain_wakeup_flag(SYSCTL_Type *ptr, sysctl_reset_domain_t domain)
{
    return ptr->RESET[domain].CONTROL & SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK;
}

/**
 * @brief Clear target reset domain wakeup status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain to be checked
 */
static inline void sysctl_reset_clear_target_domain_wakeup_flag(SYSCTL_Type *ptr, sysctl_reset_domain_t domain)
{
    ptr->RESET[domain].CONTROL |= SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK;
}

/**
 * @brief Clear target reset domain reset status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain to be checked
 * @return true if target domain was taken reset
 */
static inline bool sysctl_reset_check_target_domain_flag(SYSCTL_Type *ptr, sysctl_reset_domain_t domain)
{
    return ptr->RESET[domain].CONTROL & SYSCTL_RESET_CONTROL_FLAG_MASK;
}

/**
 * @brief Clear target reset domain reset status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain to be checked
 */
static inline void sysctl_reset_clear_target_domain_flag(SYSCTL_Type *ptr, sysctl_reset_domain_t domain)
{
    ptr->RESET[domain].CONTROL |= SYSCTL_RESET_CONTROL_FLAG_MASK;
}

/**
 * @brief Clear target reset domain for all reset status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] domain target domain to be checked
 */
static inline void sysctl_reset_clear_target_domain_all_flags(SYSCTL_Type *ptr, sysctl_reset_domain_t domain)
{
    ptr->RESET[domain].CONTROL |= SYSCTL_RESET_CONTROL_FLAG_MASK | SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK;
}

/**
 * @brief Get target CPU wakeup source status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] status_index wakeup status index 0 - 7
 * @return wakeup source status mask
 */
static inline uint32_t sysctl_get_wakeup_source_status(SYSCTL_Type *ptr, uint8_t cpu_index, uint8_t status_index)
{
    return ptr->CPU[cpu_index].WAKEUP_STATUS[status_index];
}

/**
 * @brief Get target CPU0 wakeup source status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] status_index wakeup status index 0 - 7
 * @return wakeup source status mask
 */
static inline uint32_t sysctl_get_cpu0_wakeup_source_status(SYSCTL_Type *ptr, uint8_t status_index)
{
    return sysctl_get_wakeup_source_status(ptr, 0, status_index);
}

/**
 * @brief Get target CPU1 wakeup source status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] status_index wakeup status index 0 - 7
 * @return wakeup source status mask
 */
static inline uint32_t sysctl_get_cpu1_wakeup_source_status(SYSCTL_Type *ptr, uint8_t status_index)
{
    return sysctl_get_wakeup_source_status(ptr, 1, status_index);
}

/**
 * @brief Check wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] status_index wakeup status index 0 - 7
 * @param[in] mask expected status mask
 * @return wakeup status according to given bit mask
 */
static inline uint32_t sysctl_check_wakeup_source_status_with_mask(SYSCTL_Type *ptr,
                                                                   uint8_t cpu_index,
                                                                   uint8_t status_index,
                                                                   uint32_t mask)
{
    return ptr->CPU[cpu_index].WAKEUP_STATUS[status_index] & mask;
}

/**
 * @brief Check CPU0 wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] status_index wakeup status index 0 - 7
 * @param[in] mask expected status mask
 * @return wakeup status according to given bit mask
 */
static inline uint32_t sysctl_check_cpu0_wakeup_source_status_with_mask(SYSCTL_Type *ptr,
                                                                        uint8_t status_index,
                                                                        uint32_t mask)
{
    return sysctl_check_wakeup_source_status_with_mask(ptr, 0, status_index, mask);
}

/**
 * @brief Check CPU1 wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] status_index wakeup status index 0 - 7
 * @param[in] mask expected status mask
 * @return wakeup status according to given bit mask
 */
static inline uint32_t sysctl_check_cpu1_wakeup_source_status_with_mask(SYSCTL_Type *ptr,
                                                                        uint8_t status_index,
                                                                        uint32_t mask)
{
    return sysctl_check_wakeup_source_status_with_mask(ptr, 1, status_index, mask);
}

/**
 * @brief Enable wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void sysctl_enable_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                         uint8_t cpu_index,
                                                         uint8_t enable_index,
                                                         uint32_t mask)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[enable_index] |= mask;
}

/**
 * @brief Enable CPU0 wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void sysctl_enable_cpu0_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                              uint8_t enable_index,
                                                              uint32_t mask)
{
    ptr->CPU[0].WAKEUP_ENABLE[enable_index] |= mask;
}

/**
 * @brief Enable CPU1 wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void sysctl_enable_cpu1_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                              uint8_t enable_index,
                                                              uint32_t mask)
{
    ptr->CPU[1].WAKEUP_ENABLE[enable_index] |= mask;
}

/**
 * @brief Disable wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void sysctl_disable_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                          uint8_t cpu_index,
                                                          uint8_t enable_index,
                                                          uint32_t mask)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[enable_index] &= ~mask;
}

/**
 * @brief Disable CPU0 wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void sysctl_disable_cpu0_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                               uint8_t enable_index,
                                                               uint32_t mask)
{
    sysctl_disable_wakeup_source_with_mask(ptr, 0, enable_index, mask);
}


/**
 * @brief Disable CPU1 wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void sysctl_disable_cpu1_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                               uint8_t enable_index,
                                                               uint32_t mask)
{
    sysctl_disable_wakeup_source_with_mask(ptr, 1, enable_index, mask);
}

/**
 * @brief Disable wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] irq_num irq number to be disabled as wakeup source
 */
static inline void sysctl_disable_wakeup_source_with_irq(SYSCTL_Type *ptr,
                                                         uint8_t cpu_index,
                                                         uint16_t irq_num)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[irq_num >> 2] &= ~(1UL << (irq_num % 32));
}

/**
 * @brief Disable CPU0 wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] irq_num irq number to be disabled as wakeup source
 */
static inline void sysctl_disable_cpu0_wakeup_source_with_irq(SYSCTL_Type *ptr, uint16_t irq_num)
{
    sysctl_disable_wakeup_source_with_irq(ptr, 0, irq_num);
}


/**
 * @brief Disable CPU1 wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] irq_num irq number to be disabled as wakeup source
 */
static inline void sysctl_disable_cpu1_wakeup_source_with_irq(SYSCTL_Type *ptr, uint16_t irq_num)
{
    sysctl_disable_wakeup_source_with_irq(ptr, 1, irq_num);
}

/**
 * @brief Enable wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] irq_num irq number to be set as wakeup source
 */
static inline void sysctl_enable_wakeup_source_with_irq(SYSCTL_Type *ptr, uint8_t cpu_index, uint16_t irq_num)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[irq_num / 32] |= 1UL << (irq_num & 0x1F);
}

/**
 * @brief Enable CPU0 wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] irq_num irq number to be set as wakeup source
 */
static inline void sysctl_enable_cpu0_wakeup_source_with_irq(SYSCTL_Type *ptr, uint16_t irq_num)
{
    sysctl_enable_wakeup_source_with_irq(ptr, 0, irq_num);
}

/**
 * @brief Enable CPU1 wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] irq_num irq number to be set as wakeup source
 */
static inline void sysctl_enable_cpu1_wakeup_source_with_irq(SYSCTL_Type *ptr, uint16_t irq_num)
{
    sysctl_enable_wakeup_source_with_irq(ptr, 1, irq_num);
}

/**
 * @brief Lock CPU gpr with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu_lock_gpr_with_mask(SYSCTL_Type *ptr, uint8_t cpu_index, uint16_t gpr_mask)
{
    ptr->CPU[cpu_index].LOCK |= SYSCTL_CPU_LOCK_GPR_SET(gpr_mask);
}


/**
 * @brief Lock CPU0 gpr with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu0_lock_gpr_with_mask(SYSCTL_Type *ptr, uint16_t gpr_mask)
{
    sysctl_cpu_lock_gpr_with_mask(ptr, 0, gpr_mask);
}

/**
 * @brief Lock CPU1 gpr with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu1_lock_gpr_with_mask(SYSCTL_Type *ptr, uint16_t gpr_mask)
{
    sysctl_cpu_lock_gpr_with_mask(ptr, 1, gpr_mask);
}

/**
 * @brief Lock CPU lock
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 */
static inline void sysctl_cpu_lock(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    ptr->CPU[cpu_index].LOCK |= SYSCTL_CPU_LOCK_LOCK_MASK;
}

/**
 * @brief Lock CPU0 lock
 *
 * @param[in] ptr SYSCTL_Type base address
 */
static inline void sysctl_cpu0_lock(SYSCTL_Type *ptr)
{
    sysctl_cpu_lock(ptr, 0);
}

/**
 * @brief Lock CPU1 lock
 *
 * @param[in] ptr SYSCTL_Type base address
 */
static inline void sysctl_cpu1_lock(SYSCTL_Type *ptr)
{
    sysctl_cpu_lock(ptr, 1);
}

/**
 * @brief Set CPU low power mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] mode target mode to set
 */
static inline void sysctl_set_cpu_lp_mode(SYSCTL_Type *ptr, uint8_t cpu_index, cpu_lp_mode_t mode)
{
    ptr->CPU[cpu_index].LP = (ptr->CPU[cpu_index].LP & ~(SYSCTL_CPU_LP_MODE_MASK)) | (mode);
}

/**
 * @brief Set CPU0 low power mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mode target mode to set
 */
static inline void sysctl_set_cpu0_lp_mode(SYSCTL_Type *ptr, cpu_lp_mode_t mode)
{
    sysctl_set_cpu_lp_mode(ptr, 0, mode);
}

/**
 * @brief Set CPU1 low power mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mode target mode to set
 */
static inline void sysctl_set_cpu1_lp_mode(SYSCTL_Type *ptr, cpu_lp_mode_t mode)
{
    sysctl_set_cpu_lp_mode(ptr, 1, mode);
}

/**
 * @brief Clear CPU event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] flags flag mask to be cleared
 */
static inline void sysctl_clear_cpu_flags(SYSCTL_Type *ptr, uint8_t cpu_index, cpu_event_flag_mask_t flags)
{
    ptr->CPU[cpu_index].LP |=
        ((SYSCTL_CPU_LP_SLEEP_FLAG_MASK | SYSCTL_CPU_LP_WAKE_FLAG_MASK | SYSCTL_CPU_LP_RESET_FLAG_MASK) & flags);
}

/**
 * @brief Clear CPU0 event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] flags flag mask to be cleared
 */
static inline void sysctl_clear_cpu0_flags(SYSCTL_Type *ptr, cpu_event_flag_mask_t flags)
{
    sysctl_clear_cpu_flags(ptr, 0, flags);
}

/**
 * @brief Clear CPU1 event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] flags flag mask to be cleared
 */
static inline void sysctl_clear_cpu1_flags(SYSCTL_Type *ptr, cpu_event_flag_mask_t flags)
{
    sysctl_clear_cpu_flags(ptr, 1, flags);
}

/**
 * @brief Get CPU event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @retval event flag mask
 */
static inline uint32_t sysctl_get_cpu_flags(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    return ptr->CPU[cpu_index].LP &
        (SYSCTL_CPU_LP_SLEEP_FLAG_MASK | SYSCTL_CPU_LP_WAKE_FLAG_MASK | SYSCTL_CPU_LP_RESET_FLAG_MASK);
}

/**
 * @brief Get CPU0 event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @retval event flag mask
 */
static inline uint32_t sysctl_get_cpu0_flags(SYSCTL_Type *ptr)
{
    return sysctl_get_cpu_flags(ptr, 0);
}

/**
 * @brief Get CPU1 event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @retval event flag mask
 */
static inline uint32_t sysctl_get_cpu1_flags(SYSCTL_Type *ptr)
{
    return sysctl_get_cpu_flags(ptr, 1);
}

/**
 * @brief Release cpu
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 */
static inline void sysctl_release_cpu(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    ptr->CPU[cpu_index].LP &= ~SYSCTL_CPU_LP_HALT_MASK;
}

/**
 * @brief Release cpu1
 *
 * @param[in] ptr SYSCTL_Type base address
 */
static inline void sysctl_release_cpu1(SYSCTL_Type *ptr)
{
    sysctl_release_cpu(ptr, 1);
}

/**
 * @brief Check whether CPU is released or not
 *
 * @param [in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @retval true CPU is released
 * @retval false CPU is on-hold
 */
static inline bool sysctl_is_cpu_released(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    return ((ptr->CPU[cpu_index].LP & SYSCTL_CPU_LP_HALT_MASK) == 0U);
}

/**
 * @brief Check whether CPU1 is released or not
 *
 * @param [in] ptr SYSCTL_Type base address
 * @retval true CPU1 is released
 * @retval false CPU1 is on-hold
 */
static inline bool sysctl_is_cpu1_released(SYSCTL_Type *ptr)
{
    return sysctl_is_cpu_released(ptr, 1);
}

/**
 * @brief Config lock
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] node clock node to be configured
 * @param[in] source clock source to be used
 * @param[in] divide_by clock frequency divider
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_config_clock(SYSCTL_Type *ptr, clock_node_t node, clock_source_t source, uint32_t divide_by);

/**
 * @brief Set ADC clock mux
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] node clock node to be configured
 * @param[in] source clock source to be used
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_adc_clock_mux(SYSCTL_Type *ptr, clock_node_t node, clock_source_adc_t source);

/**
 * @brief Set I2S clock mux
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] node clock node to be configured
 * @param[in] source clock source to be used
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_i2s_clock_mux(SYSCTL_Type *ptr, clock_node_t node, clock_source_i2s_t source);

/**
 * @brief Enable group resource
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] group target group to be modified
 * @param[in] resource target resource to be added/removed from group
 * @param[in] enable set true to add resource, remove otherwise
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_enable_group_resource(SYSCTL_Type *ptr,
                                        uint8_t group,
                                        sysctl_resource_t resource,
                                        bool enable);

/**
 * @brief Check group resource enable status
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] group target group to be checked
 * @param[in] resource target resource to be checked from group
 * @return enable true if resource enable, false if resource disable
 */
bool sysctl_check_group_resource_enable(SYSCTL_Type *ptr, uint8_t group, sysctl_resource_t linkable_resource);

/**
 * @brief Get group resource value
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] group target group to be getted
 * @param[in] index target group index
 * @return group index value
 */
uint32_t sysctl_get_group_resource_value(SYSCTL_Type *ptr, uint8_t group, uint8_t index);

/**
 * @brief Add resource to CPU0
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource resource to be added to CPU0
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_add_resource_to_cpu0(SYSCTL_Type *ptr, sysctl_resource_t resource);

/**
 * @brief Remove resource from CPU0
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource Resource to be removed to CPU0
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_remove_resource_from_cpu0(SYSCTL_Type *ptr, sysctl_resource_t resource);

/**
 * @brief Add resource to CPU1
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource Resource to be added to CPU1
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_add_resource_to_cpu1(SYSCTL_Type *ptr, sysctl_resource_t resource);

/**
 * @brief Remove resource from CPU1
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] resource Resource to be removed to CPU1
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_remove_resource_from_cpu1(SYSCTL_Type *ptr, sysctl_resource_t resource);

/**
 * @brief Get default monitor config
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] config Monitor config structure pointer
 */
void sysctl_monitor_get_default_config(SYSCTL_Type *ptr, monitor_config_t *config);

/**
 * @brief Initialize Monitor
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] monitor_index Monitor instance to be initialized
 * @param[in] config Monitor config structure pointer
 */
void sysctl_monitor_init(SYSCTL_Type *ptr, uint8_t monitor_index, monitor_config_t *config);

/**
 * @brief Save data to CPU0 GPR starting from given index
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] start Starting GPR index
 * @param[in] count Number of GPR registers to set
 * @param[in] data Pointer to data buffer
 * @param[in] lock Set true to lock written GPR registers after setting
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu0_set_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data, bool lock);

/**
 * @brief Get data saved from CPU0 GPR starting from given index
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] start Starting GPR index
 * @param[in] count Number of GPR registers to set
 * @param[out] data Pointer of buffer to save data
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu0_get_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data);

/**
 * @brief Set data to CPU1 GPR starting from given index
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] start Starting GPR index
 * @param[in] count Number of GPR registers to set
 * @param[in] data Pointer to data buffer
 * @param[in] lock Set true to lock written GPR registers after setting
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu1_set_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data, bool lock);

/**
 * @brief Get data saved in CPU1 GPR starting from given index
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] start Starting GPR index
 * @param[in] count Number of GPR registers to set
 * @param[out] data Pointer of buffer to save data
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_get_cpu1_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data);

/**
 * @brief Set entry point on CPU boot or wakeup
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu CPU index
 * @param[in] entry Entry address for CPU
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_cpu_entry(SYSCTL_Type *ptr, uint8_t cpu, uint32_t entry);

/**
 * @brief Set entry point on CPU0 wakeup
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] entry Entry address for CPU0 on its wakeup
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_cpu0_wakeup_entry(SYSCTL_Type *ptr, uint32_t entry);

/**
 * @brief Set entry point on either CPU1 boot or wakeup
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] entry Entry address for CPU1
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_cpu1_entry(SYSCTL_Type *ptr, uint32_t entry);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_SYSCTL_DRV_H */
