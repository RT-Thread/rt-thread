/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_ewdg_drv.h"

/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/
#define EWDG_CTRL_REG_PARITY_BIT_MASK (1UL << 31)       /*!< Parity bit for Control Register */

#ifdef EWDG_SOC_CLK_DIV_VAL_MAX
#define EWDG_CTRL_DIV_VAL_MAX EWDG_SOC_CLK_DIV_VAL_MAX
#else
#define EWDG_CTRL_DIV_VAL_MAX (EWDG_CTRL0_DIV_VALUE_MASK >> EWDG_CTRL0_DIV_VALUE_SHIFT)
#endif
#define EWDG_CTRL_WIN_UPPER_MAX (EWDG_CTRL0_WIN_UPPER_MASK >> EWDG_CTRL0_WIN_UPPER_SHIFT)

#define EWDG_CTRL_REG_UPDATE_PERIOD_DEFAULT (4UL)       /* 512 Bus clock */

#define EWDG_RING_LEFT_SHIFT_1(val) (((uint16_t)(val) << 1) | ((uint16_t)(val) >> 15))

#define EWDG_REFRESH_PERIOD_DEFAULT             (10000U)

#define EWDG_INTERRUPT_TIMEOUT_TICKS_DEFAULT    (0UL)
#define EWDG_RESET_TIMEOUT_TICKS_DEFAULT        (65535UL)

#if defined(EWDG_SOC_OVERTIME_REG_WIDTH) && (EWDG_SOC_OVERTIME_REG_WIDTH == 16)
#define EWDG_TIMEOUT_TICK_MAX (65535)
#else
#define EWDG_TIMEOUT_TICK_MAX (0xFFFFFFFFUL)
#endif

/***********************************************************************************************************************
 *
 * Prototypes
 *
 **********************************************************************************************************************/
static bool ewdg_need_set_parity_bit(uint32_t reg_val);

/***********************************************************************************************************************
 *
 * Codes
 *
 **********************************************************************************************************************/
static bool ewdg_need_set_parity_bit(uint32_t reg_val)
{
    uint32_t non_zero_bits = 0;
    while (reg_val > 0) {
        reg_val &= (reg_val - 1UL);
        ++non_zero_bits;
    }
    return ((non_zero_bits & 1UL) != 0);
}

void ewdg_get_default_config(EWDG_Type *ptr, ewdg_config_t *config)
{
    if ((ptr != NULL) && (config != NULL)) {

        (void) memset(config, 0, sizeof(ewdg_config_t));

        config->ctrl_config.cnt_clk_sel = ewdg_cnt_clk_src_ext_osc_clk;
        config->ctrl_config.use_lowlevel_timeout = true;

        config->ctrl_config.refresh_unlock_method = ewdg_refresh_unlock_method_password;
        config->ctrl_config.enable_overtime_self_clear = false;

        config->ctrl_config.timeout_interrupt_val = EWDG_INTERRUPT_TIMEOUT_TICKS_DEFAULT;
        config->ctrl_config.timeout_reset_val = EWDG_RESET_TIMEOUT_TICKS_DEFAULT;
        config->ctrl_config.clock_div_by_power_of_2 = 0;

        config->ctrl_config.refresh_unlock_password = EWDG_REFRESH_UNLOCK_PASSWORD_DEFAULT;
        config->ctrl_config.ctrl_reg_update_password = EWDG_UPDATE_PASSWORD_DEFAULT;
        config->ctrl_config.ctrl_reg_update_period_bus_clk_x_128 = EWDG_CTRL_REG_UPDATE_PERIOD_DEFAULT;

        config->ctrl_config.low_power_mode = ewdg_low_power_mode_work_clock_normal;

        config->ctrl_config.refresh_period_in_bus_cycles = EWDG_REFRESH_PERIOD_DEFAULT;
    }
}

hpm_stat_t ewdg_init_ctrl_func(EWDG_Type *ptr, ewdg_func_ctrl_config_t *config, uint32_t cnt_src_freq)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (config == NULL) || (cnt_src_freq == 0)) {
            break;
        }
        if (config->window_lower_limit > ewdg_window_lower_timeout_period_max) {
            break;
        }
        if (config->window_upper_limit > ewdg_window_upper_timeout_period_max) {
            break;
        }
        if (config->refresh_unlock_method > ewdg_refresh_unlock_method_max) {
            break;
        }

        uint32_t ctrl0 = 0;

        uint32_t ot_int_ticks;
        uint32_t ot_reset_ticks;
        uint32_t clock_div_by_pwr_2 = 0;
        if (!config->use_lowlevel_timeout) {
            uint64_t timeout_interrupt_ticks = ewdg_convert_timeout_us_to_timeout_ticks(config->timeout_interrupt_us,
                                                                                        cnt_src_freq);
            uint64_t timeout_reset_ticks = ewdg_convert_timeout_us_to_timeout_ticks(config->timeout_reset_us,
                                                                                    cnt_src_freq);
            clock_div_by_pwr_2 = 0;
            while ((timeout_interrupt_ticks > EWDG_TIMEOUT_TICK_MAX) || (timeout_reset_ticks > EWDG_TIMEOUT_TICK_MAX)) {
                ++clock_div_by_pwr_2;
                timeout_interrupt_ticks >>= 1;
                timeout_reset_ticks >>= 1;
            }
            if (clock_div_by_pwr_2 > EWDG_SOC_CLK_DIV_VAL_MAX) {
                status = status_ewdg_div_out_of_range;
                /* Cannot get the expected EWDG setting via the specified timeout input */
                break;
            }
            ot_int_ticks = (uint32_t) (timeout_interrupt_ticks & 0xFFFFFFFFUL);
            ot_reset_ticks = (uint32_t) (timeout_reset_ticks & 0xFFFFFFFFUL);

        } else {
            clock_div_by_pwr_2 = config->clock_div_by_power_of_2;
            ot_int_ticks = config->timeout_interrupt_val;
            ot_reset_ticks = config->timeout_reset_val;

            if (clock_div_by_pwr_2 > EWDG_SOC_CLK_DIV_VAL_MAX) {
                status = status_ewdg_div_out_of_range;
                /* Cannot get the expected EWDG setting via the specified timeout input */
                break;
            }
            if ((ot_int_ticks > EWDG_TIMEOUT_TICK_MAX) || (ot_reset_ticks > EWDG_TIMEOUT_TICK_MAX)) {
                status = status_ewdg_tick_out_of_range;
                break;
            }
        }

        if (config->cnt_clk_sel == ewdg_cnt_clk_src_ext_osc_clk) {
            ctrl0 |= EWDG_CTRL0_CLK_SEL_MASK;
        }
        ctrl0 |= EWDG_CTRL0_DIV_VALUE_SET(clock_div_by_pwr_2);
        if (config->enable_window_mode) {
            ctrl0 |= EWDG_CTRL0_WIN_EN_MASK;

            ctrl0 |= EWDG_CTRL0_WIN_LOWER_SET(config->window_lower_limit);
            ctrl0 |= EWDG_CTRL0_WIN_UPPER_SET(config->window_upper_limit);
        }

        if (config->enable_config_lock) {
            ctrl0 |= EWDG_CTRL0_CFG_LOCK_MASK;
        }

        if (config->enable_refresh_period) {
            ctrl0 |= EWDG_CTRL0_REF_OT_REQ_MASK;
        }
        if (config->enable_refresh_lock) {
            ctrl0 |= EWDG_CTRL0_REF_LOCK_MASK;
        }
        ctrl0 |= EWDG_CTRL0_REF_UNLOCK_MEC_SET(config->refresh_unlock_method);

        if (config->enable_overtime_self_clear) {
            ctrl0 |= EWDG_CTRL0_OT_SELF_CLEAR_MASK;
        }
        if (config->keep_running_in_debug_mode) {
            ctrl0 |= EWDG_CTRL0_EN_DBG_MASK;
        }
        ctrl0 |= EWDG_CTRL0_EN_LP_SET(config->low_power_mode);

        /* Set Parity bit if necessary */
        if (ewdg_need_set_parity_bit(ctrl0)) {
            ctrl0 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }

        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL0 = ctrl0;

        ptr->CFG_PROT = EWDG_CFG_PROT_UPD_OT_TIME_SET(config->ctrl_reg_update_period_bus_clk_x_128) |
                        EWDG_CFG_PROT_UPD_PSD_SET(config->ctrl_reg_update_password);

        ptr->REF_TIME = config->refresh_period_in_bus_cycles;
        ptr->REF_PROT = EWDG_REF_PROT_REF_UNL_PSD_SET(config->refresh_unlock_password);


#if !defined(EWDG_SOC_SUPPORT_TIMEOUT_INTERRUPT) || (EWDG_SOC_SUPPORT_TIMEOUT_INTERRUPT == 1)
        ptr->OT_INT_VAL = ot_int_ticks;
#endif
        ptr->OT_RST_VAL = ot_reset_ticks;

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t ewdg_init_interrupt_reset(EWDG_Type *ptr, ewdg_interrupt_reset_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (config == NULL)) {
            break;
        }

        uint32_t ctrl1 = 0;
        if (config->enable_ctrl_parity_fail_reset) {
            ctrl1 |= EWDG_RST_PARITY_FAIL;
        }
        if (config->enable_ctrl_unlock_fail_reset) {
            ctrl1 |= EWDG_RST_CTRL_REG_UNLOCK_FAIL;
        }
        if (config->enable_refresh_unlock_fail_reset) {
            ctrl1 |= EWDG_RST_REFRESH_UNLOCK_FAIL;
        }
        if (config->enable_ctrl_update_violation_reset) {
            ctrl1 |= EWDG_RST_CTRL_REG_UPDATE_FAIL;
        }
        if (config->enable_timeout_reset) {
            ctrl1 |= EWDG_RST_TIMEOUT;
        }
        if (config->enable_refresh_violation_reset) {
            ctrl1 |= EWDG_RST_REFRESH_VIOLATION;
        }

#if defined(EWDG_SOC_SUPPORT_INTERRUPT) && (EWDG_SOC_SUPPORT_INTERRUPT == 0)
        if (config->enable_timeout_interrupt) {
            status = status_ewdg_feature_unsupported;
            break;
        }
#else
        if (config->enable_timeout_interrupt) {
            ctrl1 |= EWDG_INT_TIMEOUT;
        }
#endif
        if (config->enable_ctrl_parity_fail_interrupt) {
            ctrl1 |= EWDG_INT_PARITY_FAIL;
        }
        if (config->enable_ctrl_unlock_fail_interrupt) {
            ctrl1 |= EWDG_INT_CTRL_REG_UNLOCK_FAIL;
        }
        if (config->enable_refresh_unlock_fail_interrupt) {
            ctrl1 |= EWDG_INT_REFRESH_UNLOCK_FAIL;
        }
        if (config->enable_ctrl_update_violation_interrupt) {
            ctrl1 |= EWDG_INT_CTRL_REG_UPDATE_FAIL;
        }
        if (config->enable_refresh_violation_interrupt) {
            ctrl1 |= EWDG_INT_REFRESH_VIOLATION;
        }

        /* Set Parity bit if necessary */
        if (ewdg_need_set_parity_bit(ctrl1)) {
            ctrl1 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }

        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL1 = ctrl1;

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t ewdg_init(EWDG_Type *ptr, ewdg_config_t *config)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if ((ptr == NULL) || (config == NULL)) {
            break;
        }

        status = ewdg_init_ctrl_func(ptr, &config->ctrl_config, config->cnt_src_freq);
        if (status != status_success) {
            break;
        }
        status = ewdg_init_interrupt_reset(ptr, &config->int_rst_config);
        if (status != status_success) {
            break;
        }

        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->WDT_EN = (config->enable_watchdog) ? 1UL : 0UL;

    } while (false);

    return status;
}

hpm_stat_t ewdg_unlock_refresh(EWDG_Type *ptr)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        if (ptr == NULL) {
            break;
        }

        if (!ewdg_is_refresh_locked(ptr)) {
            status = status_success;
            break;
        }

        ewdg_refresh_unlock_method_t unlock_method = ewdg_get_refresh_unlock_method(ptr);
        uint32_t unlock_password;
        uint32_t reg_unlock_password = EWDG_REF_PROT_REF_UNL_PSD_GET(ptr->REF_PROT);
        if (unlock_method == ewdg_refresh_unlock_method_password) {
            unlock_password = reg_unlock_password;
        } else if (unlock_method == ewdg_refresh_unlock_method_fixed_key) {
            unlock_password = EWDG_REFRESH_UNLOCK_FIXED_KEY;
        } else if (unlock_method == ewdg_refresh_unlock_method_ring_left_shift_password_by_1) {
            unlock_password = EWDG_RING_LEFT_SHIFT_1(reg_unlock_password);
        } else if (unlock_method == ewdg_refresh_unlock_method_ring_left_shift_password_by_1_bit0_xor_password_bit0) {
            uint16_t high_15 = (reg_unlock_password << 1) & 0xFFFFU;
            uint16_t low_0 = reg_unlock_password >> 15;
            low_0 ^= reg_unlock_password;
            unlock_password = high_15 | (low_0 & 0x1UL);
        } else {
            /* Should never reach this branch */
            break;
        }

        ptr->REF_PROT = unlock_password;

        status = status_success;

    } while (false);

    return status;
}

hpm_stat_t ewdg_refresh(EWDG_Type *ptr)
{
    hpm_stat_t status = ewdg_unlock_refresh(ptr);
    if (status == status_success) {
        ewdg_write_refresh_reg(ptr);
    }
    return status;
}

uint32_t ewdg_get_count_clock_freq(EWDG_Type *ptr, uint32_t src_clk_freq)
{
    uint32_t divided_freq = 0;
    if (ptr != NULL) {
        uint32_t divider = ewdg_get_count_clk_divider(ptr);
        divided_freq = src_clk_freq / divider;
    }
    return divided_freq;
}

uint64_t ewdg_convert_timeout_us_to_timeout_ticks(uint32_t src_clk_freq, uint32_t timeout_us)
{
    uint64_t timeout_ticks = 0;
    if (src_clk_freq != 0U) {
        uint32_t ns_per_tick = 1000000000UL / src_clk_freq;
        uint64_t timeout_ns = (uint64_t) timeout_us * 1000UL;
        timeout_ticks = (timeout_ns + ns_per_tick - 1U) / ns_per_tick;
    }
    return timeout_ticks;
}

uint32_t ewdg_convert_timeout_ticks_to_timeout_us(EWDG_Type *ptr, uint32_t src_clk_freq, uint32_t timeout_ticks)
{
    uint32_t timeout_us;
    if (src_clk_freq == 0U) {
        timeout_us = 0;
    } else {
        uint32_t actual_clk_freq = src_clk_freq / ewdg_get_count_clk_divider(ptr);
        uint32_t ns_per_tick = 1000000000UL / actual_clk_freq;
        uint64_t timeout_ns = (uint64_t) timeout_ticks * ns_per_tick;
        timeout_us = timeout_ns / 1000UL;
    }
    return timeout_us;
}

void ewdg_enable_interrupt(EWDG_Type *ptr, uint32_t mask)
{
    uint32_t interrupt_mask = mask & EWDG_INT_ALL;
    if (ptr != NULL) {
        uint32_t ctrl1 = ptr->CTRL1 | interrupt_mask;
        /* Set Parity bit if necessary */
        if (ewdg_need_set_parity_bit(ctrl1)) {
            ctrl1 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }
        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL1 = ctrl1;
    }
}

void ewdg_disable_interrupt(EWDG_Type *ptr, uint32_t mask)
{
    uint32_t interrupt_mask = mask & EWDG_INT_ALL;
    if (ptr != NULL) {
        uint32_t ctrl1 = ptr->CTRL1 & ~interrupt_mask;
        /* Set Parity bit if necessary */
        if (ewdg_need_set_parity_bit(ctrl1)) {
            ctrl1 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }
        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL1 = ctrl1;
    }
}

void ewdg_enable_reset(EWDG_Type *ptr, uint32_t mask)
{
    uint32_t reset_mask = mask & EWDG_RST_ALL;
    if (ptr != NULL) {
        uint32_t ctrl1 = ptr->CTRL1 | reset_mask;
        /* Set Parity bit if necessary */
        if (ewdg_need_set_parity_bit(ctrl1)) {
            ctrl1 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }
        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL1 = ctrl1;
    }
}

void ewdg_disable_reset(EWDG_Type *ptr, uint32_t mask)
{
    uint32_t reset_mask = mask & EWDG_RST_ALL;
    if (ptr != NULL) {
        uint32_t ctrl1 = ptr->CTRL1 & ~reset_mask;
        /* Set Parity bit if necessary */
        if (ewdg_need_set_parity_bit(ctrl1)) {
            ctrl1 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }
        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL1 = ctrl1;
    }
}

void ewdg_switch_clock_source(EWDG_Type *ptr, ewdg_cnt_clk_sel_t clk_sel)
{
    if (ptr != NULL) {
        uint32_t ctrl0 = ptr->CTRL0 & ~EWDG_CTRL0_CLK_SEL_MASK;
        /* Set Parity bit if necessary */
        if (clk_sel == ewdg_cnt_clk_src_ext_osc_clk) {
            ctrl0 |= EWDG_CTRL0_CLK_SEL_MASK;
        }
        if (ewdg_need_set_parity_bit(ctrl0)) {
            ctrl0 |= EWDG_CTRL_REG_PARITY_BIT_MASK;
        }
        if (ewdg_is_ctrl_reg_locked(ptr)) {
            ewdg_unlock_ctrl_regs(ptr);
        }
        ptr->CTRL0 = ctrl0;
    }
}

void ewdg_enable(EWDG_Type *ptr)
{
    if (ewdg_is_ctrl_reg_locked(ptr)) {
        ewdg_unlock_ctrl_regs(ptr);
    }
    ptr->WDT_EN = 1;
}

void ewdg_disable(EWDG_Type *ptr)
{
    if (ewdg_is_ctrl_reg_locked(ptr)) {
        ewdg_unlock_ctrl_regs(ptr);
    }
    ptr->WDT_EN = 0;
}
