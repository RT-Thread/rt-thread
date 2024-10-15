/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_pllctl_drv.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
#define FREQ_1MHz (1000000UL)

/* Clock preset values */
#define FREQ_PRESET1_OSC0_CLK0 (24000000UL)
#define FREQ_PRESET1_PLL0_CLK0 (648000000UL)
#define FREQ_PRESET1_PLL1_CLK0 (266000000UL)
#define FREQ_PRESET1_PLL1_CLK1 (400000000UL)
#define FREQ_PRESET1_PLL2_CLK0 (333000000UL)
#define FREQ_PRESET1_PLL2_CLK1 (250000000UL)
#define FREQ_PRESET1_PLL3_CLK0 (614400000UL)
#define FREQ_PRESET1_PLL4_CLK0 (594000000UL)
#define FREQ_32KHz (32768UL)
#define ADC_INSTANCE_NUM ARRAY_SIZE(HPM_SYSCTL->ADCCLK)
#define I2S_INSTANCE_NUM ARRAY_SIZE(HPM_SYSCTL->I2SCLK)
#define WDG_INSTANCE_NUM (4U)

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
 * @brief Get Clock frequency for I2S or ADC
 */
static uint32_t get_frequency_for_i2s_or_adc(uint32_t clk_src_type, uint32_t instance);

/**
 * @brief Get Clock frequency for WDG
 */
static uint32_t get_frequency_for_wdg(uint32_t instance);

/**
 * @brief Get Clock frequency for PWDG
 */
static uint32_t get_frequency_for_pwdg(void);

/**
 * @brief Turn on/off the IP clock
 */
static void switch_ip_clock(clock_name_t clock_name, bool on);

static uint64_t hpm_csr_get_core_cycle(void);

/***********************************************************************************************************************
 * Variables
 **********************************************************************************************************************/
static const clock_node_t s_adc_clk_mux_node[] = {
        clock_node_ahb0,
        clock_node_ana0,
        clock_node_ana1,
        clock_node_ana2,
};
static const clock_node_t s_i2s_clk_mux_node[] = {
        clock_node_ahb0,
        clock_node_aud0,
        clock_node_aud1,
        clock_node_aud2,
};

static WDG_Type *const s_wdgs[] = { HPM_WDG0, HPM_WDG1, HPM_WDG2, HPM_WDG3 };

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
        clk_freq = get_frequency_for_i2s_or_adc(CLK_SRC_GROUP_ADC, node_or_instance);
        break;
    case CLK_SRC_GROUP_I2S:
        clk_freq = get_frequency_for_i2s_or_adc(CLK_SRC_GROUP_I2S, node_or_instance);
        break;
    case CLK_SRC_GROUP_WDG:
        clk_freq = get_frequency_for_wdg(node_or_instance);
        break;
    case CLK_SRC_GROUP_PWDG:
        clk_freq = get_frequency_for_pwdg();
        break;
    case CLK_SRC_GROUP_PMIC:
        clk_freq = FREQ_PRESET1_OSC0_CLK0;
        break;
    case CLK_SRC_GROUP_AHB:
        clk_freq = get_frequency_for_ip_in_common_group(clock_node_ahb0);
        break;
    case CLK_SRC_GROUP_AXI0:
        clk_freq = get_frequency_for_ip_in_common_group(clock_node_axi0);
        break;
    case CLK_SRC_GROUP_AXI1:
        clk_freq = get_frequency_for_ip_in_common_group(clock_node_axi1);
        break;
    case CLK_SRC_GROUP_AXI2:
        clk_freq = get_frequency_for_ip_in_common_group(clock_node_axi2);
        break;
    case CLK_SRC_GROUP_CPU0:
        clk_freq = get_frequency_for_ip_in_common_group(clock_node_cpu0);
        break;
    case CLK_SRC_GROUP_CPU1:
        clk_freq = get_frequency_for_ip_in_common_group(clock_node_cpu1);
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
    uint32_t div = 1;
    switch (source) {
    case clock_source_osc0_clk0:
        clk_freq = FREQ_PRESET1_OSC0_CLK0;
        break;
    case clock_source_pll0_clk0:
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 0U);
        break;
    case clock_source_pll1_clk0:
        div = pllctl_get_div(HPM_PLLCTL, 1, 0);
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 1U) / div;
        break;
    case clock_source_pll1_clk1:
        div = pllctl_get_div(HPM_PLLCTL, 1, 1);
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 1U) / div;
        break;
    case clock_source_pll2_clk0:
        div = pllctl_get_div(HPM_PLLCTL, 2, 0);
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 2U) / div;
        break;
    case clock_source_pll2_clk1:
        div = pllctl_get_div(HPM_PLLCTL, 2, 1);
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 2U) / div;
        break;
    case clock_source_pll3_clk0:
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 3U);
        break;
    case clock_source_pll4_clk0:
        clk_freq = pllctl_get_pll_freq_in_hz(HPM_PLLCTL, 4U);
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

static uint32_t get_frequency_for_i2s_or_adc(uint32_t clk_src_type, uint32_t instance)
{
    uint32_t clk_freq = 0UL;
    bool is_mux_valid = false;
    clock_node_t node = clock_node_end;
    if (clk_src_type == CLK_SRC_GROUP_ADC) {
        uint32_t adc_index = instance;
        if (adc_index < ADC_INSTANCE_NUM) {
            uint32_t mux_in_reg = SYSCTL_ADCCLK_MUX_GET(HPM_SYSCTL->ADCCLK[adc_index]);
            if (mux_in_reg < ARRAY_SIZE(s_adc_clk_mux_node)) {
                node = s_adc_clk_mux_node[mux_in_reg];
                is_mux_valid = true;
            }
        }
    } else {
        uint32_t i2s_index = instance;
        if (i2s_index < I2S_INSTANCE_NUM) {
            uint32_t mux_in_reg = SYSCTL_I2SCLK_MUX_GET(HPM_SYSCTL->I2SCLK[i2s_index]);
            if (mux_in_reg < ARRAY_SIZE(s_i2s_clk_mux_node)) {
                node = s_i2s_clk_mux_node[mux_in_reg];
                is_mux_valid = true;
            }
        }
    }

    if (is_mux_valid) {
        if (node == clock_node_ahb0) {
            clk_freq = get_frequency_for_ip_in_common_group(clock_node_ahb0);
        } else {
            clk_freq = get_frequency_for_ip_in_common_group(node);
        }
    }
    return clk_freq;
}

static uint32_t get_frequency_for_wdg(uint32_t instance)
{
    uint32_t freq_in_hz;
    /* EXT clock is chosen */
    if (WDG_CTRL_CLKSEL_GET(s_wdgs[instance]->CTRL) == 0) {
        freq_in_hz = get_frequency_for_ip_in_common_group(clock_node_ahb0);
    }
        /* PCLK is chosen */
    else {
        freq_in_hz = FREQ_32KHz;
    }

    return freq_in_hz;
}

static uint32_t get_frequency_for_pwdg(void)
{
    uint32_t freq_in_hz;
    if (WDG_CTRL_CLKSEL_GET(HPM_PWDG->CTRL) == 0) {
        freq_in_hz = FREQ_PRESET1_OSC0_CLK0;
    } else {
        freq_in_hz = FREQ_32KHz;
    }

    return freq_in_hz;
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
    case CLK_SRC_GROUP_I2S:
        if (node_or_instance < I2S_INSTANCE_NUM) {
            clk_src_group = CLK_SRC_GROUP_I2S;
            clk_src_index = SYSCTL_I2SCLK_MUX_GET(HPM_SYSCTL->I2SCLK[node_or_instance]);
        }
        break;
    case CLK_SRC_GROUP_WDG:
        if (node_or_instance < WDG_INSTANCE_NUM) {
            clk_src_group = CLK_SRC_GROUP_WDG;
            clk_src_index = WDG_CTRL_CLKSEL_GET(s_wdgs[node_or_instance]->CTRL);
        }
        break;
    case CLK_SRC_GROUP_PWDG:
        clk_src_group = CLK_SRC_GROUP_PWDG;
        clk_src_index = WDG_CTRL_CLKSEL_GET(HPM_PWDG->CTRL);
        break;
    case CLK_SRC_GROUP_PMIC:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = clock_source_osc0_clk0;
        break;
    case CLK_SRC_GROUP_AHB:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_ahb0]);
        break;
    case CLK_SRC_GROUP_AXI0:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_axi0]);
        break;
    case CLK_SRC_GROUP_AXI1:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_axi1]);
        break;
    case CLK_SRC_GROUP_AXI2:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_axi2]);
        break;
    case CLK_SRC_GROUP_CPU0:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_cpu0]);
        break;
    case CLK_SRC_GROUP_CPU1:
        clk_src_group = CLK_SRC_GROUP_COMMON;
        clk_src_index = SYSCTL_CLOCK_MUX_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_cpu1]);
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
    case CLK_SRC_GROUP_WDG:
        if (node_or_instance < WDG_INSTANCE_NUM) {
            clk_divider = 1UL;
        }
        break;
    case CLK_SRC_GROUP_PWDG:
        clk_divider = 1UL;
        break;
    case CLK_SRC_GROUP_PMIC:
        clk_divider = 1UL;
        break;
    case CLK_SRC_GROUP_AHB:
        clk_divider = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_ahb0]);
        break;
    case CLK_SRC_GROUP_AXI0:
        clk_divider = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_axi0]);
        break;
    case CLK_SRC_GROUP_AXI1:
        clk_divider = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_axi1]);
        break;
    case CLK_SRC_GROUP_AXI2:
        clk_divider = SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_axi2]);
        break;
    case CLK_SRC_GROUP_CPU0:
        clk_divider = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_cpu0]);
        break;
    case CLK_SRC_GROUP_CPU1:
        clk_divider = 1UL + SYSCTL_CLOCK_DIV_GET(HPM_SYSCTL->CLOCK[(uint32_t) clock_node_cpu1]);
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

    if ((src < clk_adc_src_ahb0) || (src > clk_adc_src_ana2)) {
        return status_clk_src_invalid;
    }

    uint32_t clk_src_index = GET_CLK_SRC_INDEX(src);
    HPM_SYSCTL->ADCCLK[node_or_instance] =
            (HPM_SYSCTL->ADCCLK[node_or_instance] & ~SYSCTL_ADCCLK_MUX_MASK) | SYSCTL_ADCCLK_MUX_SET(clk_src_index);

    return status_success;
}

hpm_stat_t clock_set_i2s_source(clock_name_t clock_name, clk_src_t src)
{
    uint32_t clk_src_type = GET_CLK_SRC_GROUP_FROM_NAME(clock_name);
    uint32_t node_or_instance = GET_CLK_NODE_FROM_NAME(clock_name);

    if ((clk_src_type != CLK_SRC_GROUP_I2S) || (node_or_instance >= I2S_INSTANCE_NUM)) {
        return status_clk_invalid;
    }

    if ((src <= clk_i2s_src_ahb0) || (src >= clk_i2s_src_aud2)) {
        return status_clk_src_invalid;
    }

    uint32_t clk_src_index = GET_CLK_SRC_INDEX(src);
    HPM_SYSCTL->I2SCLK[node_or_instance] =
            (HPM_SYSCTL->I2SCLK[node_or_instance] & ~SYSCTL_I2SCLK_MUX_MASK) | SYSCTL_I2SCLK_MUX_SET(clk_src_index);

    return status_success;
}

hpm_stat_t clock_set_wdg_source(clock_name_t clock_name, clk_src_t src)
{
    uint32_t clk_src_grp = GET_CLK_SRC_GROUP(clock_name);
    if ((clk_src_grp != CLK_SRC_GROUP_WDG) && (clk_src_grp != CLK_SRC_GROUP_PWDG)) {
        return status_invalid_argument;
    }
    if (clock_name == clock_pwdg) {
        if ((src == clk_pwdg_src_osc24m) || (src == clk_pwdg_src_osc32k)) {
            uint32_t wdg_clk_src_in_ip = (uint32_t)(src - clk_pwdg_src_osc24m);
            HPM_PWDG->CTRL = (HPM_PWDG->CTRL & ~WDG_CTRL_CLKSEL_MASK) | WDG_CTRL_CLKSEL_SET(wdg_clk_src_in_ip);
        } else {
            return status_invalid_argument;
        }
    } else {
        uint32_t instance = GET_CLK_SRC_INDEX(clock_name);
        if ((src == clk_wdg_src_ahb0) || (src == clk_wdg_src_osc32k)) {
             uint32_t wdg_clk_src_in_ip = (uint32_t)(src - clk_wdg_src_ahb0);
            s_wdgs[instance]->CTRL = (s_wdgs[instance]->CTRL & ~WDG_CTRL_CLKSEL_MASK) | WDG_CTRL_CLKSEL_SET(wdg_clk_src_in_ip);
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
    case CLK_SRC_GROUP_I2S:
    case CLK_SRC_GROUP_WDG:
    case CLK_SRC_GROUP_PWDG:
    case CLK_SRC_GROUP_SRC:
        status = status_clk_operation_unsupported;
        break;
    case CLK_SRC_GROUP_PMIC:
        status = status_clk_fixed;
        break;
    case CLK_SRC_GROUP_AHB:
        status = status_clk_shared_ahb;
        break;
    case CLK_SRC_GROUP_AXI0:
        status = status_clk_shared_axi0;
        break;
    case CLK_SRC_GROUP_AXI1:
        status = status_clk_shared_axi1;
        break;
    case CLK_SRC_GROUP_AXI2:
        status = status_clk_shared_axi2;
        break;
    case CLK_SRC_GROUP_CPU0:
        status = status_clk_shared_cpu0;
        break;
    case CLK_SRC_GROUP_CPU1:
        status = status_clk_shared_cpu1;
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
    if (cpu < 2U) {
        HPM_SYSCTL->AFFILIATE[cpu].SET = (1UL << group);
    }
}

void clock_disconnect_group_from_cpu(uint32_t group, uint32_t cpu)
{
    if (cpu < 2U) {
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
    uint32_t hart_id = read_csr(CSR_MHARTID);
    clock_name_t cpu_clk_name = (hart_id == 1U) ? clock_cpu1 : clock_cpu0;
    hpm_core_clock = clock_get_frequency(cpu_clk_name);
}
