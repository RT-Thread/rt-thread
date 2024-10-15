/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_soc.h"
#include "hpm_common.h"
#include "hpm_pllctlv2_drv.h"
/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* Clock preset values */
#define FREQ_PRESET1_OSC0_CLK0 (24000000UL)
#define FREQ_PRESET1_PLL0_CLK0 (720000000UL)
#define FREQ_PRESET1_PLL0_CLK1 (450000000UL)
#define FREQ_PRESET1_PLL0_CLK2 (300000000UL)
#define FREQ_PRESET1_PLL1_CLK0 (800000000UL)
#define FREQ_PRESET1_PLL1_CLK1 (666666666UL)
#define FREQ_PRESET1_PLL1_CLK2 (500000000UL)
#define FREQ_PRESET1_PLL1_CLK3 (266666666UL)
#define FREQ_32KHz (32768UL)
#define ADC_INSTANCE_NUM ARRAY_SIZE(HPM_SYSCTL->ADCCLK)
#define DAC_INSTANCE_NUM ARRAY_SIZE(HPM_SYSCTL->DACCLK)
#define WDG_INSTANCE_NUM (2U)
#define BUS_FREQ_MAX           (200000000UL)
#define FREQ_1MHz (1000000UL)

/* Clock On/Off definitions */
#define CLOCK_ON (true)
#define CLOCK_OFF (false)


/***********************************************************************************************************************
 * Prototypes
 **********************************************************************************************************************/

/**
 * @brief Get Clock frequency for IP in common group
 */
static uint32_t get_frequency_for_ip_in_common_group(clock_node_t node);

/**
 * @brief Get Clock frequency for ADC
 */
static uint32_t get_frequency_for_adc(uint32_t clk_src_type, uint32_t instance);

/**
 * @brief Get Clock frequency for WDG
 */
static uint32_t get_frequency_for_ewdg(uint32_t instance);

/**
 * @brief Get Clock frequency for PWDG
 */
static uint32_t get_frequency_for_pewdg(void);

/**
 * @brief Turn on/off the IP clock
 */
static void switch_ip_clock(clock_name_t clock_name, bool on);

static uint32_t get_frequency_for_cpu(void);
static uint32_t get_frequency_for_ahb(void);


/***********************************************************************************************************************
 * Variables
 **********************************************************************************************************************/
static const clock_node_t s_adc_clk_mux_node[] = {
        clock_node_ahb,
        clock_node_ana0
};

static EWDG_Type *const s_wdgs[] = { HPM_EWDG0, HPM_EWDG1};

uint32_t hpm_core_clock;


/***********************************************************************************************************************
 * Codes
 **********************************************************************************************************************/
uint32_t clock_get_frequency(clock_name_t clock_name)
{
    uint32_t clk_freq = 0UL;
    uint32_t clk_src_type = GET_CLK_SRC_GROUP_FROM_NAME(clock_name);
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(clock_name);
    switch (clk_src_type) {
    case CLK_SRC_GROUP_COMMON:
        clk_freq = get_frequency_for_ip_in_common_group((clock_node_t) node_or_instance);
        break;
    case CLK_SRC_GROUP_ADC:
        clk_freq = get_frequency_for_adc(CLK_SRC_GROUP_ADC, node_or_instance);
        break;
    case CLK_SRC_GROUP_EWDG:
        clk_freq = get_frequency_for_ewdg(node_or_instance);
        break;
    case CLK_SRC_GROUP_PEWDG:
        clk_freq = get_frequency_for_pewdg();
        break;
    case CLK_SRC_GROUP_PMIC:
        clk_freq = FREQ_PRESET1_OSC0_CLK0;
        break;
    case CLK_SRC_GROUP_CPU0:
        clk_freq = get_frequency_for_cpu();
        break;
    case CLK_SRC_GROUP_AHB:
        clk_freq = get_frequency_for_ahb();
        break;
    case CLK_SRC_GROUP_SRC:
        clk_freq = get_frequency_for_source((clock_source_t) node_or_instance);
        break;
    default:
        clk_freq = 0UL;
        break;
    }
    return clk_freq;
}

uint32_t get_frequency_for_source(clock_source_t source)
{
    uint32_t clk_freq = 0UL;
    switch (source) {
    case clock_source_osc0_clk0:
        clk_freq = FREQ_PRESET1_OSC0_CLK0;
        break;
    case clock_source_pll0_clk0:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 0U, 0U);
        break;
    case clock_source_pll0_clk1:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 0U, 1U);
        break;
    case clock_source_pll0_clk2:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 0U, 2U);
        break;
    case clock_source_pll1_clk0:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 1U, 0U);
        break;
    case clock_source_pll1_clk1:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 1U, 1U);
        break;
    case clock_source_pll1_clk2:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 1U, 2U);
        break;
    case clock_source_pll1_clk3:
        clk_freq = pllctlv2_get_pll_postdiv_freq_in_hz(HPM_PLLCTLV2, 1U, 3U);
        break;
    default:
        clk_freq = 0UL;
        break;
    }

    return clk_freq;
}

static uint32_t get_frequency_for_ip_in_common_group(clock_node_t node)
{
    uint32_t clk_freq = 0UL;
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(node);

    if (node_or_instance < clock_node_end) {
        uint32_t clk_node = (uint32_t) node_or_instance;

        uint32_t clk_div = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[clk_node]);
        clock_source_t clk_mux = (clock_source_t) SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[clk_node]);
        clk_freq = get_frequency_for_source(clk_mux) / clk_div;
    }
    return clk_freq;
}

static uint32_t get_frequency_for_adc(uint32_t clk_src_type, uint32_t instance)
{
    uint32_t clk_freq = 0UL;
    bool is_mux_valid = false;
    clock_node_t node = clock_node_end;
    uint32_t adc_index = instance;

    (void) clk_src_type;

    if (adc_index < ADC_INSTANCE_NUM) {
        uint32_t mux_in_reg = SYSCTL_ADCCLK_MUX_GET(HPM_SYSCTL->ADCCLK[adc_index]);
        if (mux_in_reg < ARRAY_SIZE(s_adc_clk_mux_node)) {
            node = s_adc_clk_mux_node[mux_in_reg];
            is_mux_valid = true;
        }
    }

    if (is_mux_valid) {
        if (node != clock_node_ahb) {
            node += instance;
            clk_freq = get_frequency_for_ip_in_common_group(node);
        } else {
            clk_freq = get_frequency_for_ahb();
        }
    }
    return clk_freq;
}

static uint32_t get_frequency_for_ewdg(uint32_t instance)
{
    uint32_t freq_in_hz;
    if (EWDG_CTRL0_CLK_SEL_GET(s_wdgs[instance]->CTRL0) == 0) {
        freq_in_hz = get_frequency_for_ahb();
    } else {
        freq_in_hz = FREQ_32KHz;
    }

    return freq_in_hz;
}

static uint32_t get_frequency_for_pewdg(void)
{
    uint32_t freq_in_hz;
    if (EWDG_CTRL0_CLK_SEL_GET(HPM_PEWDG->CTRL0) == 0) {
        freq_in_hz = FREQ_PRESET1_OSC0_CLK0;
    } else {
        freq_in_hz = FREQ_32KHz;
    }

    return freq_in_hz;
}

static uint32_t get_frequency_for_cpu(void)
{
    uint32_t mux = SYSCTL_CLOCK_CPU_MUX_GET(HPM_SYSCTL->CLOCK_CPU[0]);
    uint32_t div = SYSCTL_CLOCK_CPU_DIV_GET(HPM_SYSCTL->CLOCK_CPU[0]) + 1U;
    return (get_frequency_for_source(mux) / div);
}

static uint32_t get_frequency_for_ahb(void)
{
    uint32_t div = SYSCTL_CLOCK_CPU_SUB0_DIV_GET(HPM_SYSCTL->CLOCK_CPU[0]) + 1U;
    return (get_frequency_for_cpu() / div);
}

clk_src_t clock_get_source(clock_name_t clock_name)
{
    uint8_t clk_src_group = CLK_SRC_GROUP_INVALID;
    uint8_t clk_src_index = 0xFU;
    uint32_t clk_src_type = GET_CLK_SRC_GROUP_FROM_NAME(clock_name);
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(clock_name);
    switch (clk_src_type) {
    case CLK_SRC_GROUP_COMMON:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[node_or_instance]);
        break;
    case CLK_SRC_GROUP_ADC:
        if (node_or_instance < ADC_INSTANCE_NUM) {
            clk_src_group = CLK_SRC_GROUP_ADC;
            clk_src_index = SYSCTL_ADCCLK_MUX_GET(HPM_SYSCTL->ADCCLK[node_or_instance]);
        }
        break;
    case CLK_SRC_GROUP_EWDG:
        if (node_or_instance < WDG_INSTANCE_NUM) {
            clk_src_group = CLK_SRC_GROUP_EWDG;
            clk_src_index = EWDG_CTRL0_CLK_SEL_GET(s_wdgs[node_or_instance]->CTRL0);
        }
        break;
    case CLK_SRC_GROUP_PEWDG:
        clk_src_group = CLK_SRC_GROUP_PEWDG;
        clk_src_index = EWDG_CTRL0_CLK_SEL_GET(HPM_PEWDG->CTRL0);
        break;
    case CLK_SRC_GROUP_PMIC:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = clock_source_osc0_clk0;
        break;
    case CLK_SRC_GROUP_CPU0:
    case CLK_SRC_GROUP_AHB:
        clk_src_group = CLK_SRC_GROUP_CPU0;
        clk_src_index = SYSCTL_CLOCK_CPU_MUX_GET(HPM_SYSCTL->CLOCK_CPU[0]);
        break;
    case CLK_SRC_GROUP_SRC:
        clk_src_index = (clk_src_t) node_or_instance;
        break;
    default:
        clk_src_group = CLK_SRC_GROUP_INVALID;
        break;
    }

    clk_src_t clk_src;
    if (clk_src_group != CLK_SRC_GROUP_INVALID) {
        clk_src = MAKE_CLK_SRC(clk_src_group, clk_src_index);
    } else {
        clk_src = clk_src_invalid;
    }

    return clk_src;
}

uint32_t clock_get_divider(clock_name_t clock_name)
{
    uint32_t clk_divider = CLOCK_DIV_INVALID;
    uint32_t clk_src_type = GET_CLK_SRC_GROUP_FROM_NAME(clock_name);
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(clock_name);
    switch (clk_src_type) {
    case CLK_SRC_GROUP_COMMON:
        clk_divider = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[node_or_instance]);
        break;
    case CLK_SRC_GROUP_EWDG:
        clk_divider = 1;
        break;
    case CLK_SRC_GROUP_PEWDG:
        clk_divider = 1;
        break;
    case CLK_SRC_GROUP_PMIC:
        clk_divider = 1;
        break;
    case CLK_SRC_GROUP_CPU0:
        clk_divider = 1UL + SYSCTL_CLOCK_CPU_DIV_GET(HPM_SYSCTL->CLOCK_CPU[0]);
        break;
    case CLK_SRC_GROUP_AHB:
        clk_divider = 1UL + SYSCTL_CLOCK_CPU_SUB0_DIV_GET(HPM_SYSCTL->CLOCK_CPU[0]);
        break;
    default:
        clk_divider = CLOCK_DIV_INVALID;
        break;
    }
    return clk_divider;
}

hpm_stat_t clock_set_adc_source(clock_name_t clock_name, clk_src_t src)
{
    uint32_t clk_src_type = GET_CLK_SRC_GROUP_FROM_NAME(clock_name);
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(clock_name);

    if ((clk_src_type != CLK_SRC_GROUP_ADC) || (node_or_instance >= ADC_INSTANCE_NUM)) {
        return status_clk_invalid;
    }

    if ((src < clk_adc_src_ahb0) || (src > clk_adc_src_ana1)) {
        return status_clk_src_invalid;
    }

    uint32_t clk_src_index = GET_CLK_SRC_INDEX(src);
    HPM_SYSCTL->ADCCLK[node_or_instance] =
            (HPM_SYSCTL->ADCCLK[node_or_instance] & ~SYSCTL_ADCCLK_MUX_MASK) | SYSCTL_ADCCLK_MUX_SET(clk_src_index);

    return status_success;
}

hpm_stat_t clock_set_wdg_source(clock_name_t clock_name, clk_src_t src)
{
    uint32_t clk_src_grp = GET_CLK_SRC_GROUP(clock_name);
    if ((clk_src_grp != CLK_SRC_GROUP_EWDG) && (clk_src_grp != CLK_SRC_GROUP_PEWDG)) {
        return status_invalid_argument;
    }
    if (clock_name == clock_pwdg) {
        if ((src == clk_pwdg_src_osc24m) || (src == clk_pwdg_src_osc32k)) {
            uint32_t wdg_clk_src_in_ip = (uint32_t)(src - clk_pwdg_src_osc24m);
            HPM_PEWDG->CTRL0 = (HPM_PEWDG->CTRL0 & ~EWDG_CTRL0_CLK_SEL_MASK) | EWDG_CTRL0_CLK_SEL_SET(wdg_clk_src_in_ip);
        } else {
            return status_invalid_argument;
        }
    } else {
        uint32_t instance = GET_CLK_SRC_INDEX(clock_name);
        if ((src == clk_wdg_src_ahb0) || (src == clk_wdg_src_osc32k)) {
             uint32_t wdg_clk_src_in_ip = (uint32_t)(src - clk_wdg_src_ahb0);
            s_wdgs[instance]->CTRL0 = (s_wdgs[instance]->CTRL0 & ~EWDG_CTRL0_CLK_SEL_MASK) | EWDG_CTRL0_CLK_SEL_SET(wdg_clk_src_in_ip);
        } else {
            return status_invalid_argument;
        }
    }
    return status_success;
}

hpm_stat_t clock_set_source_divider(clock_name_t clock_name, clk_src_t src, uint32_t div)
{
    hpm_stat_t status = status_success;
    uint32_t clk_src_type = GET_CLK_SRC_GROUP_FROM_NAME(clock_name);
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(clock_name);
    switch (clk_src_type) {
    case CLK_SRC_GROUP_COMMON:
        if ((div < 1U) || (div > 256U)) {
            status = status_clk_div_invalid;
        } else {
            clock_source_t clk_src = GET_CLOCK_SOURCE_FROM_CLK_SRC(src);
            sysctl_config_clock(HPM_SYSCTL, (clock_node_t) node_or_instance, clk_src, div);
        }
        break;
    case CLK_SRC_GROUP_ADC:
    case CLK_SRC_GROUP_EWDG:
    case CLK_SRC_GROUP_PEWDG:
    case CLK_SRC_GROUP_SRC:
        status = status_clk_operation_unsupported;
        break;
    case CLK_SRC_GROUP_PMIC:
        status = status_clk_fixed;
        break;
    case CLK_SRC_GROUP_AHB:
        status = status_clk_shared_cpu0;
        break;
    case CLK_SRC_GROUP_CPU0:
        if (node_or_instance == clock_node_cpu0) {
            /* Note: the AXI and AHB BUS share the same CPU clock, once the CPU clock frequency
             *  changes, the AXI and AHB clock changes accordingly, here the driver ensures the
             *  AXI and AHB bus clock frequency is in valid range.
             */
            uint32_t expected_freq = get_frequency_for_source((clock_source_t) src) / div;
            uint32_t ahb_sub_div = (expected_freq + BUS_FREQ_MAX - 1U) / BUS_FREQ_MAX;
            sysctl_config_cpu0_domain_clock(HPM_SYSCTL, (clock_source_t) src, div, ahb_sub_div);
        } else {
            status = status_clk_shared_cpu0;
        }
        break;
    default:
        status = status_clk_src_invalid;
        break;
    }

    return status;
}

static void switch_ip_clock(clock_name_t clock_name, bool on)
{
    uint32_t resource = GET_CLK_RESOURCE_FROM_NAME(clock_name);

    if (resource < sysctl_resource_end) {
        uint32_t mode = on ? 1UL : 2UL;
        HPM_SYSCTL->RESOURCE[resource] =
                (HPM_SYSCTL->RESOURCE[resource] & ~SYSCTL_RESOURCE_MODE_MASK) | SYSCTL_RESOURCE_MODE_SET(mode);
    }
}


void clock_enable(clock_name_t clock_name)
{
    switch_ip_clock(clock_name, CLOCK_ON);
}

void clock_disable(clock_name_t clock_name)
{
    switch_ip_clock(clock_name, CLOCK_OFF);
}

void clock_add_to_group(clock_name_t clock_name, uint32_t group)
{
    uint32_t resource = GET_CLK_RESOURCE_FROM_NAME(clock_name);

    if (resource < sysctl_resource_end) {
        sysctl_enable_group_resource(HPM_SYSCTL, group, resource, true);
    }
}

void clock_remove_from_group(clock_name_t clock_name, uint32_t group)
{
    uint32_t resource = GET_CLK_RESOURCE_FROM_NAME(clock_name);

    if (resource < sysctl_resource_end) {
        sysctl_enable_group_resource(HPM_SYSCTL, group, resource, false);
    }
}

bool clock_check_in_group(clock_name_t clock_name, uint32_t group)
{
    uint32_t resource = GET_CLK_RESOURCE_FROM_NAME(clock_name);

    return sysctl_check_group_resource_enable(HPM_SYSCTL, group, resource);
}

void clock_connect_group_to_cpu(uint32_t group, uint32_t cpu)
{
    if (cpu == 0U) {
        HPM_SYSCTL->AFFILIATE[cpu].SET = (1UL << group);
    }
}

void clock_disconnect_group_from_cpu(uint32_t group, uint32_t cpu)
{
    if (cpu == 0U) {
        HPM_SYSCTL->AFFILIATE[cpu].CLEAR = (1UL << group);
    }
}

void clock_cpu_delay_us(uint32_t us)
{
    uint32_t ticks_per_us = (hpm_core_clock + FREQ_1MHz - 1U) / FREQ_1MHz;
    uint64_t expected_ticks = hpm_csr_get_core_cycle() + ticks_per_us * us;
    while (hpm_csr_get_core_cycle() < expected_ticks) {
    }
}

void clock_cpu_delay_ms(uint32_t ms)
{
    uint32_t ticks_per_us = (hpm_core_clock + FREQ_1MHz - 1U) / FREQ_1MHz;
    uint64_t expected_ticks = hpm_csr_get_core_cycle() + (uint64_t)ticks_per_us * 1000UL * ms;
    while (hpm_csr_get_core_cycle() < expected_ticks) {
    }
}

void clock_update_core_clock(void)
{
    hpm_core_clock = clock_get_frequency(clock_cpu0);
}
