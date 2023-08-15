/**
 * Copyright (c) 2021-2023 HPMicro
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
 */
typedef enum {
    sysctl_retention_domain_sys = 0,
    sysctl_retention_domain_cpu0 = 2,

    sysctl_retention_domain_xtal24m = 4,
    sysctl_retention_domain_pll0 = 5,
    sysctl_retention_domain_pll1 = 6,
    sysctl_retention_domain_pll2 = 7,
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
} sysctl_reset_domain_t;

/**
 * @brief Resource
 */
typedef enum {
    sysctl_resource_cpu0 = 0,
    sysctl_resource_cpx0 = 1,
    sysctl_resource_exe0 = 2,
    sysctl_resource_wak0 = 3,
    sysctl_resource_cpu0_per = 4,
    sysctl_resource_logic0 = 16,
    sysctl_resource_logic1 = 17,
    sysctl_resource_logic2 = 18,
    sysctl_resource_logic3 = 19,
    sysctl_resource_pmic = 20,
    sysctl_resource_pow_cpu0 = 21,
    sysctl_resource_rst_soc = 22,
    sysctl_resource_rst_cpu0 = 23,
    sysctl_resource_xtal = 32,
    sysctl_resource_pll0 = 33,
    sysctl_resource_clk0_pll0 = 34,
    sysctl_resource_clk1_pll0 = 35,
    sysctl_resource_clk2_pll0 = 36,
    sysctl_resource_pll1 = 37,
    sysctl_resource_clk0_pll1 = 38,
    sysctl_resource_clk1_pll1 = 39,
    sysctl_resource_pll2 = 40,
    sysctl_resource_clk0_pll2 = 41,
    sysctl_resource_clk1_pll2 = 42,
    sysctl_resource_pll0_ref = 43,
    sysctl_resource_pll1_ref = 44,
    sysctl_resource_pll2_ref = 45,
    sysctl_resource_mbist_soc = 48,
    sysctl_resource_mbist_cpu = 49,
    sysctl_resource_mbist_con = 50,
    sysctl_resource_dft_start_bus = 51,
    sysctl_resource_clk_top_cpu0 = 64,
    sysctl_resource_clk_top_mchtmr0 = 65,
    sysctl_resource_clk_top_femc = 66,
    sysctl_resource_clk_top_xpi0 = 67,
    sysctl_resource_clk_top_xpi1 = 68,
    sysctl_resource_clk_top_gptmr0 = 69,
    sysctl_resource_clk_top_gptmr1 = 70,
    sysctl_resource_clk_top_gptmr2 = 71,
    sysctl_resource_clk_top_gptmr3 = 72,
    sysctl_resource_clk_top_uart0 = 73,
    sysctl_resource_clk_top_uart1 = 74,
    sysctl_resource_clk_top_uart2 = 75,
    sysctl_resource_clk_top_uart3 = 76,
    sysctl_resource_clk_top_uart4 = 77,
    sysctl_resource_clk_top_uart5 = 78,
    sysctl_resource_clk_top_uart6 = 79,
    sysctl_resource_clk_top_uart7 = 80,
    sysctl_resource_clk_top_i2c0 = 81,
    sysctl_resource_clk_top_i2c1 = 82,
    sysctl_resource_clk_top_i2c2 = 83,
    sysctl_resource_clk_top_i2c3 = 84,
    sysctl_resource_clk_top_spi0 = 85,
    sysctl_resource_clk_top_spi1 = 86,
    sysctl_resource_clk_top_spi2 = 87,
    sysctl_resource_clk_top_spi3 = 88,
    sysctl_resource_clk_top_can0 = 89,
    sysctl_resource_clk_top_can1 = 90,
    sysctl_resource_clk_top_ptpc = 91,
    sysctl_resource_clk_top_ana0 = 92,
    sysctl_resource_clk_top_ana1 = 93,
    sysctl_resource_clk_top_ana2 = 94,
    sysctl_resource_clk_top_ana3 = 95,
    sysctl_resource_clk_top_aud0 = 96,
    sysctl_resource_clk_top_aud1 = 97,
    sysctl_resource_clk_top_eth0 = 98,
    sysctl_resource_clk_top_ptp0 = 99,
    sysctl_resource_clk_top_ref0 = 100,
    sysctl_resource_clk_top_ref1 = 101,
    sysctl_resource_clk_top_ntmr0 = 102,
    sysctl_resource_clk_top_sdxc0 = 103,
    sysctl_resource_clk_top_adc0 = 128,
    sysctl_resource_clk_top_adc1 = 129,
    sysctl_resource_clk_top_adc2 = 130,
    sysctl_resource_clk_top_dac0 = 131,
    sysctl_resource_clk_top_i2s0 = 132,
    sysctl_resource_clk_top_i2s1 = 133,

    sysctl_resource_eth0_mem = 192,
    sysctl_resource_sdxc0_mem = 193,
    sysctl_resource_usb0_mem = 194,
    sysctl_resource_ram0_mem = 195,
    sysctl_resource_ahbp_mem = 196,
    sysctl_resource_femc_mem = 197,
    sysctl_resource_rom0_mem = 198,
    sysctl_resource_xpi0_mem = 199,
    sysctl_resource_xpi1_mem = 200,
    sysctl_resource_can0_mem = 201,
    sysctl_resource_can1_mem = 202,
    sysctl_resource_i2s0_mem = 203,
    sysctl_resource_i2s1_mem = 204,
    sysctl_resource_pdm0_mem = 205,
    sysctl_resource_sdp0_mem = 206,
    sysctl_resource_ffa0_mem = 207,
    sysctl_resource_cpx_mem = 208,
    sysctl_resource_core_mem = 209,
    sysctl_resource_lmm0_mem = 210,


    sysctl_resource_linkable_start = 256,
    sysctl_resource_ahbp = 256,
    sysctl_resource_axis = 257,
    sysctl_resource_axic = 258,
    sysctl_resource_femc = 259,
    sysctl_resource_rom0 = 260,
    sysctl_resource_lmm0 = 261,
    sysctl_resource_ram0 = 262,
    sysctl_resource_mchtmr0 = 263,
    sysctl_resource_xpi0 = 264,
    sysctl_resource_xpi1 = 265,
    sysctl_resource_sdp0 = 266,
    sysctl_resource_rng0 = 267,
    sysctl_resource_kman = 268,
    sysctl_resource_dma0 = 269,
    sysctl_resource_dma1 = 270,
    sysctl_resource_ffa0 = 271,
    sysctl_resource_gpio = 272,
    sysctl_resource_mbx0 = 273,
    sysctl_resource_wdg0 = 274,
    sysctl_resource_wdg1 = 275,
    sysctl_resource_tsns = 276,
    sysctl_resource_gptmr0 = 277,
    sysctl_resource_gptmr1 = 278,
    sysctl_resource_gptmr2 = 279,
    sysctl_resource_gptmr3 = 280,
    sysctl_resource_uart0 = 281,
    sysctl_resource_uart1 = 282,
    sysctl_resource_uart2 = 283,
    sysctl_resource_uart3 = 284,
    sysctl_resource_uart4 = 285,
    sysctl_resource_uart5 = 286,
    sysctl_resource_uart6 = 287,
    sysctl_resource_uart7 = 288,
    sysctl_resource_i2c0 = 289,
    sysctl_resource_i2c1 = 290,
    sysctl_resource_i2c2 = 291,
    sysctl_resource_i2c3 = 292,
    sysctl_resource_spi0 = 293,
    sysctl_resource_spi1 = 294,
    sysctl_resource_spi2 = 295,
    sysctl_resource_spi3 = 296,
    sysctl_resource_can0 = 297,
    sysctl_resource_can1 = 298,
    sysctl_resource_ptpc = 299,
    sysctl_resource_adc0 = 300,
    sysctl_resource_adc1 = 301,
    sysctl_resource_adc2 = 302,
    sysctl_resource_dac0 = 303,
    sysctl_resource_acmp = 304,
    sysctl_resource_i2s0 = 305,
    sysctl_resource_i2s1 = 306,
    sysctl_resource_i2spdm0 = 307,
    sysctl_resource_i2sdao = 308,
    sysctl_resource_msyn = 309,
    sysctl_resource_mot0 = 310,
    sysctl_resource_mot1 = 311,
    sysctl_resource_eth0 = 312,
    sysctl_resource_ntmr0 = 313,
    sysctl_resource_sdxc0 = 314,
    sysctl_resource_usb0 = 315,
    sysctl_resource_ref0 = 316,
    sysctl_resource_ref1 = 317,
    sysctl_resource_linkable_end,
    sysctl_resource_end = sysctl_resource_linkable_end,
} sysctl_resource_t;

/**
 * @brief Resource modes
 */
typedef enum {
    sysctl_resource_mode_auto = 0,
    sysctl_resource_mode_force_on,
    sysctl_resource_mode_force_off,
} sysctl_resource_mode_t;

/**
 * @brief Clock nodes
 */
typedef enum {
    clock_node_mchtmr0 = 0,
    clock_node_femc = 1,
    clock_node_xpi0 = 2,
    clock_node_xpi1 = 3,
    clock_node_gptmr0 = 4,
    clock_node_gptmr1 = 5,
    clock_node_gptmr2 = 6,
    clock_node_gptmr3 = 7,
    clock_node_uart0 = 8,
    clock_node_uart1 = 9,
    clock_node_uart2 = 10,
    clock_node_uart3 = 11,
    clock_node_uart4 = 12,
    clock_node_uart5 = 13,
    clock_node_uart6 = 14,
    clock_node_uart7 = 15,
    clock_node_i2c0 = 16,
    clock_node_i2c1 = 17,
    clock_node_i2c2 = 18,
    clock_node_i2c3 = 19,
    clock_node_spi0 = 20,
    clock_node_spi1 = 21,
    clock_node_spi2 = 22,
    clock_node_spi3 = 23,
    clock_node_can0 = 24,
    clock_node_can1 = 25,
    clock_node_ptpc = 26,
    clock_node_ana0 = 27,
    clock_node_ana1 = 28,
    clock_node_ana2 = 29,
    clock_node_ana3 = 30,
    clock_node_aud0 = 31,
    clock_node_aud1 = 32,
    clock_node_eth0 = 33,
    clock_node_ptp0 = 34,
    clock_node_ref0 = 35,
    clock_node_ref1 = 36,
    clock_node_ntmr0 = 37,
    clock_node_sdxc0 = 38,

    clock_node_adc_i2s_start,
    clock_node_adc0 = clock_node_adc_i2s_start,
    clock_node_adc1,
    clock_node_adc2,

    clock_node_i2s0,
    clock_node_i2s1,

    clock_node_end,

    clock_node_core_start = 0xfc,
    clock_node_cpu0 = clock_node_core_start,
    clock_node_axi,
    clock_node_ahb,
} clock_node_t;

/**
 * @brief General clock sources
 */
typedef enum {
    clock_source_osc0_clk0 = 0,
    clock_source_pll0_clk0 = 1,
    clock_source_pll0_clk1 = 2,
    clock_source_pll0_clk2 = 3,
    clock_source_pll1_clk0 = 4,
    clock_source_pll1_clk1 = 5,
    clock_source_pll2_clk0 = 6,
    clock_source_pll2_clk1 = 7,
    clock_source_general_source_end,
} clock_source_t;

/**
 * @brief ADC/I2S clock sources
 */
typedef enum {
    clock_source_adc_ana_clk = 0,
    clock_source_adc_ahb_clk = 1,
    clock_source_i2s_aud0_clk = 0,
    clock_source_i2s_aud1_clk = 1,
    clock_source_adc_i2s_clk_end,
} clock_source_adc_i2s_t;

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
typedef enum {
    monitor_target_clk_32k = 0,
    monitor_target_clk_irc24m = 1,
    monitor_target_clk_xtal_24m = 2,
    monitor_target_clk_usb0_phy = 3,

    monitor_target_clk0_osc0 = 8,
    monitor_target_clk0_pll0 = 9,
    monitor_target_clk1_pll0 = 10,
    monitor_target_clk2_pll0 = 11,
    monitor_target_clk0_pll1 = 12,
    monitor_target_clk1_pll1 = 13,
    monitor_target_clk0_pll2 = 14,
    monitor_target_clk1_pll2 = 15,

    monitor_target_clk_top_cpu0 = 128,
    monitor_target_clk_top_mchtmr0 = 129,

    monitor_target_clk_top_femc = 136,
    monitor_target_clk_top_xpi0 = 137,
    monitor_target_clk_top_xpi1 = 138,
    monitor_target_clk_top_gptmr0 = 139,
    monitor_target_clk_top_gptmr1 = 140,
    monitor_target_clk_top_gptmr2 = 141,
    monitor_target_clk_top_gptmr3 = 142,

    monitor_target_clk_top_uart0 = 147,
    monitor_target_clk_top_uart1 = 148,
    monitor_target_clk_top_uart2 = 149,
    monitor_target_clk_top_uart3 = 150,
    monitor_target_clk_top_uart4 = 151,
    monitor_target_clk_top_uart5 = 152,
    monitor_target_clk_top_uart6 = 153,
    monitor_target_clk_top_uart7 = 154,

    monitor_target_clk_top_i2c0 = 163,
    monitor_target_clk_top_i2c1 = 164,
    monitor_target_clk_top_i2c2 = 165,
    monitor_target_clk_top_i2c3 = 166,
    monitor_target_clk_top_spi0 = 167,
    monitor_target_clk_top_spi1 = 168,
    monitor_target_clk_top_spi2 = 169,
    monitor_target_clk_top_spi3 = 170,
    monitor_target_clk_top_can0 = 171,
    monitor_target_clk_top_can1 = 172,

    monitor_target_clk_top_ptpc = 175,
    monitor_target_clk_top_ana0 = 176,
    monitor_target_clk_top_ana1 = 177,
    monitor_target_clk_top_ana2 = 178,
    monitor_target_clk_top_ana3 = 179,
    monitor_target_clk_top_aud0 = 180,
    monitor_target_clk_top_aud1 = 181,

    monitor_target_clk_top_eth0 = 185,

    monitor_target_clk_top_ptp0 = 187,

    monitor_target_clk_top_ref0 = 189,
    monitor_target_clk_top_ref1 = 190,
    monitor_target_clk_top_ntmr0 = 191,

    monitor_target_clk_top_sdxc0 = 193,

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
static inline hpm_stat_t
sysctl_monitor_set_limit(SYSCTL_Type *ptr, uint8_t monitor_index, uint32_t limit_high, uint32_t limit_low)
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
uint32_t
sysctl_monitor_measure_frequency(SYSCTL_Type *ptr, uint8_t monitor_index, monitor_target_t target, bool enable_output);

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
static inline void
sysctl_resource_target_set_mode(SYSCTL_Type *ptr, sysctl_resource_t resource, sysctl_resource_mode_t mode)
{
    ptr->RESOURCE[resource] = (ptr->RESOURCE[resource] & ~SYSCTL_RESOURCE_MODE_MASK) | SYSCTL_RESOURCE_MODE_SET(mode);
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
static inline void sysctl_clear_cpu0_lp_retention_with_mask(SYSCTL_Type *ptr,
                                                        uint32_t mask)
{
    sysctl_clear_cpu_lp_retention_with_mask(ptr, 0, mask);
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
static inline void sysctl_set_cpu0_lp_retention_with_mask(SYSCTL_Type *ptr,
                                            uint32_t mask)
{
    sysctl_set_cpu_lp_retention_with_mask(ptr, 0, mask);
}

/**
 * @brief Enable resource retention when CPU1 enters stop mode
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] mask bit mask to set
 */
static inline void sysctl_set_cpu1_lp_retention_with_mask(SYSCTL_Type *ptr,
                                            uint32_t mask)
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
static inline void sysctl_set_cpu_lp_retention(SYSCTL_Type *ptr,
                                            uint8_t cpu_index,
                                            uint32_t value)
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
 * @brief Retain target domain for specific CPU
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] domain target domain power to be retained
 * @param[in] retain_mem set true to retain memory/register of target domain
 */
static inline void
sysctl_set_cpu_lp_retain_domain(SYSCTL_Type *ptr, uint8_t cpu_index, sysctl_retention_domain_t domain, bool retain_mem)
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
 * @brief Check if cpu clock is busy
 *
 * @param[in] ptr SYSCTL_Type base address
 * @return true if any clock is busy
 */
static inline bool sysctl_cpu_clock_any_is_busy(SYSCTL_Type *ptr)
{
    return ptr->CLOCK_CPU[0] & SYSCTL_CLOCK_CPU_GLB_BUSY_MASK;
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
static inline uint32_t sysctl_get_cpu0_wakeup_source_status(SYSCTL_Type *ptr,
                                                       uint8_t status_index)
{
    return sysctl_get_wakeup_source_status(ptr, 0, status_index);
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
static inline uint32_t
sysctl_check_wakeup_source_status_with_mask(SYSCTL_Type *ptr, uint8_t cpu_index, uint8_t status_index, uint32_t mask)
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
static inline
    uint32_t sysctl_check_cpu0_wakeup_source_status_with_mask(SYSCTL_Type *ptr,
                                                         uint8_t status_index,
                                                         uint32_t mask)
{
    return sysctl_check_wakeup_source_status_with_mask(ptr, 0, status_index, mask);
}

/**
 * @brief Enable wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void
sysctl_enable_wakeup_source_with_mask(SYSCTL_Type *ptr, uint8_t cpu_index, uint8_t enable_index, uint32_t mask)
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
 * @brief Disable wakeup source status with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] enable_index wakeup enable index 0 - 7
 * @param[in] mask expected status mask
 */
static inline void
sysctl_disable_wakeup_source_with_mask(SYSCTL_Type *ptr, uint8_t cpu_index, uint8_t enable_index, uint32_t mask)
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
 * @brief Disable wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] irq_num irq number to be set as wakeup source
 */
static inline void sysctl_disable_wakeup_source_with_irq(SYSCTL_Type *ptr, uint8_t cpu_index, uint16_t irq_num)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[irq_num >> 2] &= ~(1UL << (irq_num % 32));
}

/**
 * @brief Disable CPU0 wakeup source status with irq
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] irq_num irq number to be disabled as wakeup source
 */
static inline void sysctl_disable_cpu0_wakeup_source_with_irq(SYSCTL_Type *ptr,
                                                        uint16_t irq_num)
{
    sysctl_disable_wakeup_source_with_irq(ptr, 0, irq_num);
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
static inline void sysctl_enable_cpu0_wakeup_source_with_irq(SYSCTL_Type *ptr,
                                                        uint16_t irq_num)
{
    sysctl_enable_wakeup_source_with_irq(ptr, 0, irq_num);
}

/**
 * @brief Lock CPU gpr with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu_lock_gpr_with_mask(SYSCTL_Type *ptr,
                                                  uint8_t cpu_index,
                                                  uint16_t gpr_mask)
{
    ptr->CPU[cpu_index].LOCK |= SYSCTL_CPU_LOCK_GPR_SET(gpr_mask);
}


/**
 * @brief Lock CPU0 gpr with mask
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu0_lock_gpr_with_mask(SYSCTL_Type *ptr,
                                                 uint16_t gpr_mask)
{
    sysctl_cpu_lock_gpr_with_mask(ptr, 0, gpr_mask);
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
 * @brief Clear CPU event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @param[in] flags flag mask to be cleared
 */
static inline void sysctl_clear_cpu_flags(SYSCTL_Type *ptr, uint8_t cpu_index, cpu_event_flag_mask_t flags)
{
    ptr->CPU[cpu_index].LP |= ((SYSCTL_CPU_LP_SLEEP_FLAG_MASK | SYSCTL_CPU_LP_WAKE_FLAG_MASK | SYSCTL_CPU_LP_RESET_FLAG_MASK) & flags);
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
 * @brief Get CPU event flags
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] cpu_index CPU index
 * @retval event flag mask
 */
static inline uint32_t sysctl_get_cpu_flags(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    return ptr->CPU[cpu_index].LP & (SYSCTL_CPU_LP_SLEEP_FLAG_MASK | SYSCTL_CPU_LP_WAKE_FLAG_MASK | SYSCTL_CPU_LP_RESET_FLAG_MASK);
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
 * @brief Configure CPU domain clock
 * @param ptr SYSCTL base address
 * @param source clock source to be used
 * @param cpu_div CPU divider
 * @param axi_sub_div AXI BUS divider based on divided CPU clock
 * @param ahb_sub_div AHB BUS divider based on divided CPU clock
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_config_cpu0_domain_clock(SYSCTL_Type *ptr, clock_source_t source, uint32_t cpu_div,
                                          uint32_t axi_sub_div, uint32_t ahb_sub_div);

/**
 * @brief Set ADC/I2S clock mux
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] node clock node to be configured
 * @param[in] source clock source to be used
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_adc_i2s_clock_mux(SYSCTL_Type *ptr, clock_node_t node, clock_source_adc_i2s_t source);

/**
 * @brief Enable group resource
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] group target group to be modified
 * @param[in] resource target resource to be added/removed from group
 * @param[in] enable set true to add resource, remove otherwise
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_enable_group_resource(SYSCTL_Type *ptr, uint8_t group, sysctl_resource_t resource, bool enable);
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
 * @brief Save data to GPU0 GPR starting from given index
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
 * @brief Get data saved from GPU0 GPR starting from given index
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] start Starting GPR index
 * @param[in] count Number of GPR registers to set
 * @param[out] data Pointer of buffer to save data
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu0_get_gpr(SYSCTL_Type *ptr, uint8_t start, uint8_t count, uint32_t *data);

/**
 * @brief Set entry point on CPU0 wakeup
 *
 * @param[in] ptr SYSCTL_Type base address
 * @param[in] entry Entry address for CPU0 on its wakeup
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_cpu0_wakeup_entry(SYSCTL_Type *ptr, uint32_t entry);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_SYSCTL_DRV_H */
