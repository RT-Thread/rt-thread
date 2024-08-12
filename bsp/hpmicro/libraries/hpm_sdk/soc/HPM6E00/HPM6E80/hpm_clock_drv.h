/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_CLOCK_DRV_H
#define HPM_CLOCK_DRV_H

#include "hpm_common.h"
#include "hpm_sysctl_drv.h"


/**
 * @brief Error codes for clock driver
 */
enum {
    status_clk_div_invalid = MAKE_STATUS(status_group_clk, 0),
    status_clk_src_invalid = MAKE_STATUS(status_group_clk, 1),
    status_clk_invalid = MAKE_STATUS(status_group_clk, 2),
    status_clk_operation_unsupported = MAKE_STATUS(status_group_clk, 3),
    status_clk_shared_ahb = MAKE_STATUS(status_group_clk, 4),
    status_clk_shared_axif = MAKE_STATUS(status_group_clk, 5),
    status_clk_shared_axis = MAKE_STATUS(status_group_clk, 6),
    status_clk_shared_axic = MAKE_STATUS(status_group_clk, 7),
    status_clk_shared_axin = MAKE_STATUS(status_group_clk, 8),
    status_clk_shared_cpu0 = MAKE_STATUS(status_group_clk, 9),
    status_clk_shared_cpu1 = MAKE_STATUS(status_group_clk, 10),
    status_clk_fixed = MAKE_STATUS(status_group_clk, 11),
};

/**
 * @brief Clock source group definitions
 */
#define CLK_SRC_GROUP_COMMON  (0U)
#define CLK_SRC_GROUP_ADC     (1U)
#define CLK_SRC_GROUP_I2S     (2U)
#define CLK_SRC_GROUP_EWDG    (3U)
#define CLK_SRC_GROUP_AHB     (4U)
#define CLK_SRC_GROUP_AXIF    (5U)
#define CLK_SRC_GROUP_AXIS    (6U)
#define CLK_SRC_GROUP_AXIC    (7U)
#define CLK_SRC_GROUP_AXIN    (8U)
#define CLK_SRC_GROUP_PMIC    (9U)
#define CLK_SRC_GROUP_PEWDG   (10U)
#define CLK_SRC_GROUP_CPU0    (11U)
#define CLK_SRC_GROUP_CPU1    (12U)
#define CLK_SRC_GROUP_SRC     (13U)
#define CLK_SRC_GROUP_INVALID (14U)

#define MAKE_CLK_SRC(src_grp, index) (((uint8_t)(src_grp)<<4) | (index))
#define GET_CLK_SRC_GROUP(src) (((uint8_t)(src)>>4) & 0x0FU)
#define GET_CLK_SRC_INDEX(src) ((uint8_t)(src) & 0x0FU)

#define GET_CLOCK_SOURCE_FROM_CLK_SRC(clk_src) (clock_source_t)((uint32_t)(clk_src) & 0xFU)

/**
 * @brief Clock source definitions
 */
typedef enum _clock_sources {
    clk_src_osc24m = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 0),
    clk_src_pll0_clk0 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 1),
    clk_src_pll0_clk1 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 2),
    clk_src_pll1_clk0 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 3),
    clk_src_pll1_clk1 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 4),
    clk_src_pll1_clk2 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 5),
    clk_src_pll2_clk0 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 6),
    clk_src_pll2_clk1 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 7),
    clk_src_osc32k = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 8),

    clk_adc_src_ana0 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ana1 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ana2 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ana3 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ahb0 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 1),

    clk_i2s_src_aud0 = MAKE_CLK_SRC(CLK_SRC_GROUP_I2S, 0),
    clk_i2s_src_aud1 = MAKE_CLK_SRC(CLK_SRC_GROUP_I2S, 0),
    clk_i2s_src_audx = MAKE_CLK_SRC(CLK_SRC_GROUP_I2S, 1),

    clk_wdg_src_ahb0 = MAKE_CLK_SRC(CLK_SRC_GROUP_EWDG, 0),
    clk_wdg_src_osc32k = MAKE_CLK_SRC(CLK_SRC_GROUP_EWDG, 1),

    clk_pwdg_src_osc24m = MAKE_CLK_SRC(CLK_SRC_GROUP_PEWDG, 0),
    clk_pwdg_src_osc32k = MAKE_CLK_SRC(CLK_SRC_GROUP_PEWDG, 1),

    clk_src_invalid = MAKE_CLK_SRC(CLK_SRC_GROUP_INVALID, 15),
} clk_src_t;

#define RESOURCE_INVALID (0xFFFFU)

#define GET_CLOCK_SOURCE_FROM_CLK_SRC(clk_src) (clock_source_t)((uint32_t)(clk_src) & 0xFU)

/* Clock NAME related Macros */
#define MAKE_CLOCK_NAME(resource, src_type, node) (((uint32_t)(resource) << 16) | ((uint32_t)(src_type) << 8) | ((uint32_t)node))
#define GET_CLK_SRC_GROUP_FROM_NAME(name)  (((uint32_t)(name) >> 8) & 0xFFUL)
#define GET_CLK_NODE_FROM_NAME(name) ((uint32_t)(name) & 0xFFUL)
#define GET_CLK_RESOURCE_FROM_NAME(name) ((uint32_t)(name) >> 16)

/**
 * @brief Peripheral Clock Type Description
 */
typedef enum _clock_name {
    clock_cpu0 = MAKE_CLOCK_NAME(sysctl_resource_cpu0, CLK_SRC_GROUP_COMMON, clock_node_cpu0),
    clock_mchtmr0 = MAKE_CLOCK_NAME(sysctl_resource_mchtmr0, CLK_SRC_GROUP_COMMON, clock_node_mchtmr0),
    clock_cpu1 = MAKE_CLOCK_NAME(sysctl_resource_cpu1, CLK_SRC_GROUP_COMMON, clock_node_cpu1),
    clock_mchtmr1 = MAKE_CLOCK_NAME(sysctl_resource_mchtmr1, CLK_SRC_GROUP_COMMON, clock_node_mchtmr1),
    clock_ahb0 = MAKE_CLOCK_NAME(sysctl_resource_ahbp, CLK_SRC_GROUP_COMMON, clock_node_ahb0),
    clock_axif = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_axif),
    clock_axis = MAKE_CLOCK_NAME(sysctl_resource_axis, CLK_SRC_GROUP_COMMON, clock_node_axis),
    clock_axic = MAKE_CLOCK_NAME(sysctl_resource_axic, CLK_SRC_GROUP_COMMON, clock_node_axic),
    clock_axin = MAKE_CLOCK_NAME(sysctl_resource_axin, CLK_SRC_GROUP_COMMON, clock_node_axin),
    clock_gptmr0 = MAKE_CLOCK_NAME(sysctl_resource_gptmr0, CLK_SRC_GROUP_COMMON, clock_node_gptmr0),
    clock_gptmr1 = MAKE_CLOCK_NAME(sysctl_resource_gptmr1, CLK_SRC_GROUP_COMMON, clock_node_gptmr1),
    clock_gptmr2 = MAKE_CLOCK_NAME(sysctl_resource_gptmr2, CLK_SRC_GROUP_COMMON, clock_node_gptmr2),
    clock_gptmr3 = MAKE_CLOCK_NAME(sysctl_resource_gptmr3, CLK_SRC_GROUP_COMMON, clock_node_gptmr3),
    clock_gptmr4 = MAKE_CLOCK_NAME(sysctl_resource_gptmr4, CLK_SRC_GROUP_COMMON, clock_node_gptmr4),
    clock_gptmr5 = MAKE_CLOCK_NAME(sysctl_resource_gptmr5, CLK_SRC_GROUP_COMMON, clock_node_gptmr5),
    clock_gptmr6 = MAKE_CLOCK_NAME(sysctl_resource_gptmr6, CLK_SRC_GROUP_COMMON, clock_node_gptmr6),
    clock_gptmr7 = MAKE_CLOCK_NAME(sysctl_resource_gptmr7, CLK_SRC_GROUP_COMMON, clock_node_gptmr7),
    clock_i2c0 = MAKE_CLOCK_NAME(sysctl_resource_i2c0, CLK_SRC_GROUP_COMMON, clock_node_i2c0),
    clock_i2c1 = MAKE_CLOCK_NAME(sysctl_resource_i2c1, CLK_SRC_GROUP_COMMON, clock_node_i2c1),
    clock_i2c2 = MAKE_CLOCK_NAME(sysctl_resource_i2c2, CLK_SRC_GROUP_COMMON, clock_node_i2c2),
    clock_i2c3 = MAKE_CLOCK_NAME(sysctl_resource_i2c3, CLK_SRC_GROUP_COMMON, clock_node_i2c3),
    clock_i2c4 = MAKE_CLOCK_NAME(sysctl_resource_i2c4, CLK_SRC_GROUP_COMMON, clock_node_i2c4),
    clock_i2c5 = MAKE_CLOCK_NAME(sysctl_resource_i2c5, CLK_SRC_GROUP_COMMON, clock_node_i2c5),
    clock_i2c6 = MAKE_CLOCK_NAME(sysctl_resource_i2c6, CLK_SRC_GROUP_COMMON, clock_node_i2c6),
    clock_i2c7 = MAKE_CLOCK_NAME(sysctl_resource_i2c7, CLK_SRC_GROUP_COMMON, clock_node_i2c7),
    clock_spi0 = MAKE_CLOCK_NAME(sysctl_resource_spi0, CLK_SRC_GROUP_COMMON, clock_node_spi0),
    clock_spi1 = MAKE_CLOCK_NAME(sysctl_resource_spi1, CLK_SRC_GROUP_COMMON, clock_node_spi1),
    clock_spi2 = MAKE_CLOCK_NAME(sysctl_resource_spi2, CLK_SRC_GROUP_COMMON, clock_node_spi2),
    clock_spi3 = MAKE_CLOCK_NAME(sysctl_resource_spi3, CLK_SRC_GROUP_COMMON, clock_node_spi3),
    clock_spi4 = MAKE_CLOCK_NAME(sysctl_resource_spi4, CLK_SRC_GROUP_COMMON, clock_node_spi4),
    clock_spi5 = MAKE_CLOCK_NAME(sysctl_resource_spi5, CLK_SRC_GROUP_COMMON, clock_node_spi5),
    clock_spi6 = MAKE_CLOCK_NAME(sysctl_resource_spi6, CLK_SRC_GROUP_COMMON, clock_node_spi6),
    clock_spi7 = MAKE_CLOCK_NAME(sysctl_resource_spi7, CLK_SRC_GROUP_COMMON, clock_node_spi7),
    clock_uart0 = MAKE_CLOCK_NAME(sysctl_resource_uart0, CLK_SRC_GROUP_COMMON, clock_node_uart0),
    clock_uart1 = MAKE_CLOCK_NAME(sysctl_resource_uart1, CLK_SRC_GROUP_COMMON, clock_node_uart1),
    clock_uart2 = MAKE_CLOCK_NAME(sysctl_resource_uart2, CLK_SRC_GROUP_COMMON, clock_node_uart2),
    clock_uart3 = MAKE_CLOCK_NAME(sysctl_resource_uart3, CLK_SRC_GROUP_COMMON, clock_node_uart3),
    clock_uart4 = MAKE_CLOCK_NAME(sysctl_resource_uart4, CLK_SRC_GROUP_COMMON, clock_node_uart4),
    clock_uart5 = MAKE_CLOCK_NAME(sysctl_resource_uart5, CLK_SRC_GROUP_COMMON, clock_node_uart5),
    clock_uart6 = MAKE_CLOCK_NAME(sysctl_resource_uart6, CLK_SRC_GROUP_COMMON, clock_node_uart6),
    clock_uart7 = MAKE_CLOCK_NAME(sysctl_resource_uart7, CLK_SRC_GROUP_COMMON, clock_node_uart7),
    clock_uart8 = MAKE_CLOCK_NAME(sysctl_resource_uart8, CLK_SRC_GROUP_COMMON, clock_node_uart8),
    clock_uart9 = MAKE_CLOCK_NAME(sysctl_resource_uart9, CLK_SRC_GROUP_COMMON, clock_node_uart9),
    clock_uart10 = MAKE_CLOCK_NAME(sysctl_resource_uart10, CLK_SRC_GROUP_COMMON, clock_node_uart10),
    clock_uart11 = MAKE_CLOCK_NAME(sysctl_resource_uart11, CLK_SRC_GROUP_COMMON, clock_node_uart11),
    clock_uart12 = MAKE_CLOCK_NAME(sysctl_resource_uart12, CLK_SRC_GROUP_COMMON, clock_node_uart12),
    clock_uart13 = MAKE_CLOCK_NAME(sysctl_resource_uart13, CLK_SRC_GROUP_COMMON, clock_node_uart13),
    clock_uart14 = MAKE_CLOCK_NAME(sysctl_resource_uart14, CLK_SRC_GROUP_COMMON, clock_node_uart14),
    clock_uart15 = MAKE_CLOCK_NAME(sysctl_resource_uart15, CLK_SRC_GROUP_COMMON, clock_node_uart15),
    clock_can0 = MAKE_CLOCK_NAME(sysctl_resource_can0, CLK_SRC_GROUP_COMMON, clock_node_can0),
    clock_can1 = MAKE_CLOCK_NAME(sysctl_resource_can1, CLK_SRC_GROUP_COMMON, clock_node_can1),
    clock_can2 = MAKE_CLOCK_NAME(sysctl_resource_can2, CLK_SRC_GROUP_COMMON, clock_node_can2),
    clock_can3 = MAKE_CLOCK_NAME(sysctl_resource_can3, CLK_SRC_GROUP_COMMON, clock_node_can3),
    clock_can4 = MAKE_CLOCK_NAME(sysctl_resource_can4, CLK_SRC_GROUP_COMMON, clock_node_can4),
    clock_can5 = MAKE_CLOCK_NAME(sysctl_resource_can5, CLK_SRC_GROUP_COMMON, clock_node_can5),
    clock_can6 = MAKE_CLOCK_NAME(sysctl_resource_can6, CLK_SRC_GROUP_COMMON, clock_node_can6),
    clock_can7 = MAKE_CLOCK_NAME(sysctl_resource_can7, CLK_SRC_GROUP_COMMON, clock_node_can7),
    clock_xpi0 = MAKE_CLOCK_NAME(sysctl_resource_xpi0, CLK_SRC_GROUP_COMMON, clock_node_xpi0),
    clock_femc = MAKE_CLOCK_NAME(sysctl_resource_femc, CLK_SRC_GROUP_COMMON, clock_node_femc),
    clock_eth0 = MAKE_CLOCK_NAME(sysctl_resource_eth0, CLK_SRC_GROUP_COMMON, clock_node_eth0),
    clock_ptp0 = MAKE_CLOCK_NAME(sysctl_resource_eth0, CLK_SRC_GROUP_COMMON, clock_node_ptp0),
    clock_ntmr0 = MAKE_CLOCK_NAME(sysctl_resource_ntmr0, CLK_SRC_GROUP_COMMON, clock_node_ntmr0),
    clock_ref0 = MAKE_CLOCK_NAME(sysctl_resource_ref0, CLK_SRC_GROUP_COMMON, clock_node_ref0),
    clock_ref1 = MAKE_CLOCK_NAME(sysctl_resource_ref1, CLK_SRC_GROUP_COMMON, clock_node_ref1),
    clock_tsn1 = MAKE_CLOCK_NAME(sysctl_resource_tsn0, CLK_SRC_GROUP_COMMON, clock_node_tsn1),
    clock_tsn2 = MAKE_CLOCK_NAME(sysctl_resource_tsn0, CLK_SRC_GROUP_COMMON, clock_node_tsn2),
    clock_tsn3 = MAKE_CLOCK_NAME(sysctl_resource_tsn0, CLK_SRC_GROUP_COMMON, clock_node_tsn3),

    clock_crc0 = MAKE_CLOCK_NAME(sysctl_resource_crc0, CLK_SRC_GROUP_AHB, 0),
    clock_tsns = MAKE_CLOCK_NAME(sysctl_resource_tsns, CLK_SRC_GROUP_AHB, 0),
    clock_mbx0 = MAKE_CLOCK_NAME(sysctl_resource_mbx0, CLK_SRC_GROUP_AHB, 0),
    clock_mbx1 = MAKE_CLOCK_NAME(sysctl_resource_mbx1, CLK_SRC_GROUP_AHB, 0),
    clock_gpio = MAKE_CLOCK_NAME(sysctl_resource_gpio, CLK_SRC_GROUP_AHB, 0),
    clock_ppi0 = MAKE_CLOCK_NAME(sysctl_resource_ppi0, CLK_SRC_GROUP_AHB, 0),
    clock_hdma = MAKE_CLOCK_NAME(sysctl_resource_hdma, CLK_SRC_GROUP_AHB, 0),
    clock_lobs = MAKE_CLOCK_NAME(sysctl_resource_lobs, CLK_SRC_GROUP_AHB, 0),
    clock_cmp0 = MAKE_CLOCK_NAME(sysctl_resource_cmp0, CLK_SRC_GROUP_AHB, 0),
    clock_cmp1 = MAKE_CLOCK_NAME(sysctl_resource_cmp1, CLK_SRC_GROUP_AHB, 0),
    clock_cmp2 = MAKE_CLOCK_NAME(sysctl_resource_cmp2, CLK_SRC_GROUP_AHB, 0),
    clock_cmp3 = MAKE_CLOCK_NAME(sysctl_resource_cmp3, CLK_SRC_GROUP_AHB, 0),
    clock_ptpc = MAKE_CLOCK_NAME(sysctl_resource_ptpc, CLK_SRC_GROUP_AHB, 0),
    clock_mot0 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_AHB, 0),
    clock_qei0 = MAKE_CLOCK_NAME(sysctl_resource_qei0, CLK_SRC_GROUP_AHB, 0),
    clock_qei1 = MAKE_CLOCK_NAME(sysctl_resource_qei1, CLK_SRC_GROUP_AHB, 0),
    clock_qei2 = MAKE_CLOCK_NAME(sysctl_resource_qei2, CLK_SRC_GROUP_AHB, 0),
    clock_qei3 = MAKE_CLOCK_NAME(sysctl_resource_qei3, CLK_SRC_GROUP_AHB, 0),
    clock_qeo0 = MAKE_CLOCK_NAME(sysctl_resource_qeo0, CLK_SRC_GROUP_AHB, 0),
    clock_qeo1 = MAKE_CLOCK_NAME(sysctl_resource_qeo1, CLK_SRC_GROUP_AHB, 0),
    clock_qeo2 = MAKE_CLOCK_NAME(sysctl_resource_qeo2, CLK_SRC_GROUP_AHB, 0),
    clock_qeo3 = MAKE_CLOCK_NAME(sysctl_resource_qeo3, CLK_SRC_GROUP_AHB, 0),
    clock_pwm0 = MAKE_CLOCK_NAME(sysctl_resource_pwm0, CLK_SRC_GROUP_AHB, 0),
    clock_pwm1 = MAKE_CLOCK_NAME(sysctl_resource_pwm1, CLK_SRC_GROUP_AHB, 0),
    clock_pwm2 = MAKE_CLOCK_NAME(sysctl_resource_pwm2, CLK_SRC_GROUP_AHB, 0),
    clock_pwm3 = MAKE_CLOCK_NAME(sysctl_resource_pwm3, CLK_SRC_GROUP_AHB, 0),
    clock_rdc0 = MAKE_CLOCK_NAME(sysctl_resource_rdc0, CLK_SRC_GROUP_AHB, 0),
    clock_rdc1 = MAKE_CLOCK_NAME(sysctl_resource_rdc1, CLK_SRC_GROUP_AHB, 0),
    clock_sdm0 = MAKE_CLOCK_NAME(sysctl_resource_sdm0, CLK_SRC_GROUP_AHB, 0),
    clock_sdm1 = MAKE_CLOCK_NAME(sysctl_resource_sdm1, CLK_SRC_GROUP_AHB, 0),
    clock_plb0 = MAKE_CLOCK_NAME(sysctl_resource_plb0, CLK_SRC_GROUP_AHB, 0),
    clock_sei0 = MAKE_CLOCK_NAME(sysctl_resource_sei0, CLK_SRC_GROUP_AHB, 0),
    clock_mtg0 = MAKE_CLOCK_NAME(sysctl_resource_mtg0, CLK_SRC_GROUP_AHB, 0),
    clock_mtg1 = MAKE_CLOCK_NAME(sysctl_resource_mtg1, CLK_SRC_GROUP_AHB, 0),
    clock_vsc0 = MAKE_CLOCK_NAME(sysctl_resource_vsc0, CLK_SRC_GROUP_AHB, 0),
    clock_vsc1 = MAKE_CLOCK_NAME(sysctl_resource_vsc1, CLK_SRC_GROUP_AHB, 0),
    clock_clc0 = MAKE_CLOCK_NAME(sysctl_resource_clc0, CLK_SRC_GROUP_AHB, 0),
    clock_clc1 = MAKE_CLOCK_NAME(sysctl_resource_clc1, CLK_SRC_GROUP_AHB, 0),
    clock_emds = MAKE_CLOCK_NAME(sysctl_resource_emds, CLK_SRC_GROUP_AHB, 0),

    clock_watchdog0 = MAKE_CLOCK_NAME(sysctl_resource_wdg0, CLK_SRC_GROUP_EWDG, 0),
    clock_watchdog1 = MAKE_CLOCK_NAME(sysctl_resource_wdg1, CLK_SRC_GROUP_EWDG, 1),
    clock_watchdog2 = MAKE_CLOCK_NAME(sysctl_resource_wdg2, CLK_SRC_GROUP_EWDG, 2),
    clock_watchdog3 = MAKE_CLOCK_NAME(sysctl_resource_wdg3, CLK_SRC_GROUP_EWDG, 3),

    clock_rng = MAKE_CLOCK_NAME(sysctl_resource_rng0, CLK_SRC_GROUP_AXIS, 0),
    clock_sdp = MAKE_CLOCK_NAME(sysctl_resource_sdp0, CLK_SRC_GROUP_AXIS, 1),
    clock_pka = MAKE_CLOCK_NAME(sysctl_resource_pka0, CLK_SRC_GROUP_AXIS, 2),
    clock_kman = MAKE_CLOCK_NAME(sysctl_resource_kman, CLK_SRC_GROUP_AXIS, 3),
    clock_xdma = MAKE_CLOCK_NAME(sysctl_resource_xdma, CLK_SRC_GROUP_AXIS, 4),
    clock_ffa0 = MAKE_CLOCK_NAME(sysctl_resource_ffa0, CLK_SRC_GROUP_AXIS, 5),
    clock_rom0 = MAKE_CLOCK_NAME(sysctl_resource_rom0, CLK_SRC_GROUP_AXIS, 6),

    clock_ram0 = MAKE_CLOCK_NAME(sysctl_resource_ram0, CLK_SRC_GROUP_AXIF, 0),
    clock_ram1 = MAKE_CLOCK_NAME(sysctl_resource_ram1, CLK_SRC_GROUP_AXIF, 1),

    clock_usb0 = MAKE_CLOCK_NAME(sysctl_resource_usb0, CLK_SRC_GROUP_AXIC, 0),

    clock_esc0 = MAKE_CLOCK_NAME(sysctl_resource_esc0, CLK_SRC_GROUP_AXIN, 0),

    clock_lmm0 = MAKE_CLOCK_NAME(sysctl_resource_lmm0, CLK_SRC_GROUP_CPU0, 0),
    clock_lmm1 = MAKE_CLOCK_NAME(sysctl_resource_lmm0, CLK_SRC_GROUP_CPU1, 0),

    clock_puart = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_PMIC, 0),
    clock_ptmr = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_PMIC, 1),

    clock_pwdg = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_PEWDG, 0),

    /* For ADC, there are 2-stage clock source and divider configurations */
    clock_ana0 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana0),
    clock_ana1 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana1),
    clock_ana2 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana2),
    clock_ana3 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana3),
    clock_adc0 = MAKE_CLOCK_NAME(sysctl_resource_adc0, CLK_SRC_GROUP_ADC, 0),
    clock_adc1 = MAKE_CLOCK_NAME(sysctl_resource_adc1, CLK_SRC_GROUP_ADC, 1),
    clock_adc2 = MAKE_CLOCK_NAME(sysctl_resource_adc2, CLK_SRC_GROUP_ADC, 2),
    clock_adc3 = MAKE_CLOCK_NAME(sysctl_resource_adc3, CLK_SRC_GROUP_ADC, 3),

    /* For I2S, there are 2-stage clock source and divider configurations */
    clock_aud0 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_aud0),
    clock_aud1 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_aud1),
    clock_i2s0 = MAKE_CLOCK_NAME(sysctl_resource_i2s0, CLK_SRC_GROUP_I2S, 0),
    clock_i2s1 = MAKE_CLOCK_NAME(sysctl_resource_i2s1, CLK_SRC_GROUP_I2S, 1),
    clock_pdm = MAKE_CLOCK_NAME(sysctl_resource_i2spdm0, CLK_SRC_GROUP_I2S, 0),
    clock_dao = MAKE_CLOCK_NAME(sysctl_resource_i2sdao, CLK_SRC_GROUP_I2S, 1),

    /* Clock sources */
    clk_osc0clk0 = MAKE_CLOCK_NAME(sysctl_resource_xtal, CLK_SRC_GROUP_SRC, 0),
    clk_pll0clk0 = MAKE_CLOCK_NAME(sysctl_resource_clk0_pll0, CLK_SRC_GROUP_SRC, 1),
    clk_pll0clk1 = MAKE_CLOCK_NAME(sysctl_resource_clk1_pll0, CLK_SRC_GROUP_SRC, 2),
    clk_pll1clk0 = MAKE_CLOCK_NAME(sysctl_resource_clk0_pll1, CLK_SRC_GROUP_SRC, 3),
    clk_pll1clk1 = MAKE_CLOCK_NAME(sysctl_resource_clk1_pll1, CLK_SRC_GROUP_SRC, 4),
    clk_pll1clk2 = MAKE_CLOCK_NAME(sysctl_resource_clk2_pll1, CLK_SRC_GROUP_SRC, 5),
    clk_pll2clk0 = MAKE_CLOCK_NAME(sysctl_resource_clk0_pll2, CLK_SRC_GROUP_SRC, 6),
    clk_pll2clk1 = MAKE_CLOCK_NAME(sysctl_resource_clk1_pll2, CLK_SRC_GROUP_SRC, 7),
} clock_name_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get specified IP frequency
 * @param[in] clock_name IP clock name
 *
 * @return IP clock frequency in Hz
 */
uint32_t clock_get_frequency(clock_name_t clock_name);


/**
 * @brief Get Clock frequency for selected clock source
 * @param [in] source clock source
 * @return clock frequency for selected clock source
 */
uint32_t get_frequency_for_source(clock_source_t source);

/**
 * @brief Get the IP clock source
 *        Note: This API return the direct clock source
 * @param [in] clock_name clock name
 * @return IP clock source
 */
clk_src_t clock_get_source(clock_name_t clock_name);

/**
 * @brief Set ADC clock source
 * @param[in] clock_name ADC clock name
 * @param[in] src ADC clock source
 *
 * @return #status_success Setting ADC clock source is successful
 *         #status_clk_invalid Invalid ADC clock
 *         #status_clk_src_invalid Invalid ADC clock source
 */
hpm_stat_t clock_set_adc_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set DAC clock source
 * @param[in] clock_name DAC clock name
 * @param[in] src DAC clock source
 *
 * @return #status_success Setting DAC clock source is successful
 *         #status_clk_invalid Invalid DAC clock
 *         #status_clk_src_invalid Invalid DAC clock source
 */
hpm_stat_t clock_set_dac_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set I2S clock source
 * @param[in] clock_name I2S clock name
 * @param[in] src I2S clock source
 *
 * @return #status_success Setting I2S clock source is successful
 *         #status_clk_invalid Invalid I2S clock
 *         #status_clk_src_invalid Invalid I2S clock source
 */
hpm_stat_t clock_set_i2s_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set the WDG clock source
 * @param [in] clock_name WDG clock name
 * @param [in] src WDG clock source
 *
 * @retval status_success Setting WDG clock source is successful
 * @retval status_invalid_argument Invalid WDG or invalid clock source
 */
hpm_stat_t clock_set_wdg_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set the IP clock source and divider
 * @param[in] clock_name clock name
 * @param[in] src clock source
 * @param[in] div clock divider, valid range (1 - 256)
 *
 * @return #status_success Setting Clock source and divider is successful.
 *         #status_clk_src_invalid clock source is invalid.
 *         #status_clk_fixed clock source and divider is a fixed value
 *         #status_clk_shared_ahb Clock is shared with the AHB clock
 *         #status_clk_shared_axi0 Clock is shared with the AXI0 clock
 *         #status_clk_shared_axi1 CLock is shared with the AXI1 clock
 *         #status_clk_shared_axi2 Clock is shared with the AXI2 clock
 *         #status_clk_shared_cpu0 Clock is shared with the CPU0 clock
 *         #status_clk_shared_cpu1 Clock is shared with the CPU1 clock
 */
hpm_stat_t clock_set_source_divider(clock_name_t clock_name, clk_src_t src, uint32_t div);

/**
 * @brief Enable IP clock
 * @param[in] clock_name IP clock name
 */
void clock_enable(clock_name_t clock_name);

/**
 * @brief Disable IP clock
 * @param[in] clock_name IP clock name
 */
void clock_disable(clock_name_t clock_name);

/**
 * @brief Add IP to specified group
 * @param[in] clock_name IP clock name
 * @param[in] group resource group index, valid value: 0/1/2/3
 */
void clock_add_to_group(clock_name_t clock_name, uint32_t group);

/**
 * @brief Remove IP from specified group
 * @param[in] clock_name IP clock name
 * @param[in] group resource group index, valid value: 0/1/2/3
 */
void clock_remove_from_group(clock_name_t clock_name, uint32_t group);

/**
 * @brief Check IP in specified group
 * @param[in] clock_name IP clock name
 * @return true if in group, false if not in group
 */
bool clock_check_in_group(clock_name_t clock_name, uint32_t group);

/**
 * @brief Disconnect the clock group from specified CPU
 * @param[in] group clock group index, value value is 0/1/2/3
 * @param[in] cpu CPU index, valid value is 0/1
 */
void clock_connect_group_to_cpu(uint32_t group, uint32_t cpu);

/**
 * @brief Disconnect the clock group from specified CPU
 * @param[in] group clock group index, value value is 0/1/2/3
 * @param[in] cpu CPU index, valid value is 0/1
 */
void clock_disconnect_group_from_cpu(uint32_t group, uint32_t cpu);

/**
 * @brief Delay specified microseconds
 *
 * @param [in] us expected delay interval in microseconds
 */
void clock_cpu_delay_us(uint32_t us);

/**
 * @brief Delay specified milliseconds
 *
 * @param [in] ms expected delay interval in milliseconds
 */
void clock_cpu_delay_ms(uint32_t ms);

/**
 * @brief Update the Core clock frequency
 */
void clock_update_core_clock(void);

/**
 * @brief HPM Core clock variable
 */
extern uint32_t hpm_core_clock;

#ifdef __cplusplus
}
#endif

#endif /* HPM_CLOCK_DRV_H */
