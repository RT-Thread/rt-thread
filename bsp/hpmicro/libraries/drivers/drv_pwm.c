/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-05-09   HPMicro     First version
 * 2023-04-12   HPMicro     Adapt hpm_sdk v1.0.0
 * 2023-05-13   HPMicro     Fix compiling error on HPM6360/HPM6200
 * 2026-09-10   HPMicro     Check shared counter frequency conflicts
 * 2026-09-10   HPMicro     Support optional RT-Thread PWM controls
 * 2026-09-11   HPMicro     Fix runtime updates and shared counter handling
 */

#include <rtthread.h>

#if defined(BSP_USING_PWM) || defined(BSP_USING_PWMV2)
#if defined(BSP_USING_PWMV2)
#define HPMSOC_HAS_HPMSDK_PWMV2
#endif
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
#include "hpm_pwmv2_drv.h"
#else
#include "hpm_pwm_drv.h"
#endif
#include "hpm_clock_drv.h"

#define PWM_CHANNEL_NUM PWM_SOC_PWM_MAX_COUNT

typedef struct {
    struct rt_pwm_configuration config;
    uint32_t reload;
    bool configured;
    bool enabled;
    bool irq_enabled;
} hpm_pwm_channel_state_t;

#ifdef HPM_PWM3
#define PWM_INSTANCE_NUM 4
#elif defined(HPM_PWM2)
#define PWM_INSTANCE_NUM 3
#elif defined(HPM_PWM1)
#define PWM_INSTANCE_NUM 2
#else
#define PWM_INSTANCE_NUM 1
#endif

#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
static PWMV2_Type * pwm_base_tbl[PWM_INSTANCE_NUM] = {
#else
static PWM_Type * pwm_base_tbl[PWM_INSTANCE_NUM] = {
#endif
    HPM_PWM0,
#ifdef HPM_PWM1
    HPM_PWM1,
#endif
#ifdef HPM_PWM2
    HPM_PWM2,
#endif
#ifdef HPM_PWM3
    HPM_PWM3
#endif
    };

static hpm_pwm_channel_state_t pwm_channel_state[PWM_INSTANCE_NUM][PWM_CHANNEL_NUM];

#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
#define PWMV2_RELOAD_MAX 0xFFFFFFU

static const pwm_counter_t pwmv2_counter_tbl[PWM_CHANNEL_NUM] = {
    pwm_counter_0,
    pwm_counter_0,
    pwm_counter_1,
    pwm_counter_1,
    pwm_counter_2,
    pwm_counter_2,
    pwm_counter_3,
    pwm_counter_3,
};
#endif

#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
extern uint32_t rtt_board_init_pwm_clock(PWMV2_Type *ptr);
#else
extern uint32_t rtt_board_init_pwm_clock(PWM_Type *ptr);
#endif

static rt_err_t hpm_pwm_calculate_timing(uint8_t pwm_index, uint32_t period, uint32_t pulse,
                                         uint32_t *reload, uint32_t *duty)
{
    uint32_t freq;
    uint64_t reload_ticks;
    uint64_t duty_ticks;

    if ((pwm_index >= PWM_INSTANCE_NUM) || (period == 0U) || (pulse > period)) {
        return -RT_EINVAL;
    }

    freq = rtt_board_init_pwm_clock(pwm_base_tbl[pwm_index]);
    reload_ticks = (uint64_t)freq * period / 1000000000U;
    duty_ticks = (uint64_t)freq * pulse / 1000000000U;

    if ((reload_ticks == 0U) || (reload_ticks > UINT32_MAX)) {
        return -RT_EINVAL;
    }
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    if (reload_ticks > PWMV2_RELOAD_MAX) {
        return -RT_EINVAL;
    }
#else
    if (reload_ticks > PWM_RLD_RLD_GET(PWM_RLD_RLD_MASK)) {
        return -RT_EINVAL;
    }
#endif

    *reload = (uint32_t)reload_ticks;
    *duty = (uint32_t)duty_ticks;

    return RT_EOK;
}

static rt_err_t hpm_pwm_calculate_dead_time(uint8_t pwm_index, uint32_t dead_time,
                                            uint32_t *dead_ticks)
{
    uint32_t freq;
    uint64_t ticks;

    if (pwm_index >= PWM_INSTANCE_NUM) {
        return -RT_EINVAL;
    }

    if (dead_time == 0U) {
        *dead_ticks = 0U;
        return RT_EOK;
    }

    freq = rtt_board_init_pwm_clock(pwm_base_tbl[pwm_index]);
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    ticks = ((uint64_t)freq * dead_time + 999999999U) / 1000000000U;
    /* Values below two clocks disable dead-area insertion. */
    if (ticks < 2U) {
        ticks = 2U;
    }
    if (ticks > UINT16_MAX) {
        return -RT_EINVAL;
    }
#else
    ticks = ((uint64_t)freq * dead_time * 2U + 999999999U) / 1000000000U;
    /* The dead-area unit is half a clock and the hardware minimum is one clock. */
    if (ticks < 2U) {
        ticks = 2U;
    }
    if (ticks > PWM_PWMCFG_DEADAREA_GET(PWM_PWMCFG_DEADAREA_MASK)) {
        return -RT_EINVAL;
    }
#endif

    *dead_ticks = (uint32_t)ticks;
    return RT_EOK;
}

static bool hpm_pwm_use_complementary(uint8_t channel, bool requested)
{
    /* RT-Thread cannot represent negative channel zero, so keep channel zero as normal output. */
    return requested && (channel != 0U);
}

static bool hpm_pwm_channel_has_pair(uint8_t channel)
{
    return ((channel & 1U) == 0U) && ((channel + 1U) < PWM_CHANNEL_NUM);
}

static rt_err_t hpm_pwm_validate_configuration(uint8_t pwm_index,
                                               const struct rt_pwm_configuration *config,
                                               uint32_t *reload, uint32_t *duty,
                                               uint32_t *dead_ticks)
{
    bool complementary;

    if (config->phase > 360U) {
        return -RT_EINVAL;
    }

    complementary = hpm_pwm_use_complementary(config->channel, config->complementary);
    if (complementary && !hpm_pwm_channel_has_pair(config->channel)) {
        return -RT_EINVAL;
    }

    if (hpm_pwm_calculate_timing(pwm_index, config->period, config->pulse,
                                 reload, duty) != RT_EOK) {
        return -RT_EINVAL;
    }

    return hpm_pwm_calculate_dead_time(pwm_index, config->dead_time, dead_ticks);
}

static void hpm_pwm_calculate_compare(uint32_t reload, uint32_t duty, uint32_t phase,
                                      uint32_t *cmp_a, uint32_t *cmp_b, bool *invert)
{
    uint32_t phase_ticks;
    uint64_t start;
    uint64_t end;

    phase_ticks = (uint32_t)((uint64_t)reload * (phase % 360U) / 360U);
    start = (uint64_t)((reload - duty) >> 1) + phase_ticks;
    end = ((uint64_t)reload + duty) / 2U + phase_ticks;
    *invert = false;

    if (start >= reload) {
        start -= reload;
        end -= reload;
    } else if (end > reload) {
        uint32_t wrapped_end = end - reload;

        end = start;
        start = wrapped_end;
        *invert = true;
    }
    *cmp_a = (uint32_t)start;
    *cmp_b = (uint32_t)end;
}

static bool hpm_pwm_channel_shares_counter(uint8_t channel_a, uint8_t channel_b)
{
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    return (channel_a / 2U) == (channel_b / 2U);
#else
    (void)channel_a;
    (void)channel_b;
    return true;
#endif
}

static bool hpm_pwm_counter_is_active(uint8_t pwm_index, uint8_t channel)
{
    uint8_t index;

    for (index = 0; index < PWM_CHANNEL_NUM; index++) {
        if (pwm_channel_state[pwm_index][index].enabled
            && hpm_pwm_channel_shares_counter(channel, index)) {
            return true;
        }
    }

    return false;
}

static void hpm_pwm_stop_counter(uint8_t pwm_index, uint8_t channel)
{
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    pwmv2_disable_counter(pwm_base_tbl[pwm_index], pwmv2_counter_tbl[channel]);
#else
    (void)channel;
    pwm_stop_counter(pwm_base_tbl[pwm_index]);
#endif
}

static rt_err_t hpm_pwm_check_frequency_conflict(uint8_t pwm_index, uint8_t channel, uint32_t reload)
{
    uint8_t index;

    for (index = 0; index < PWM_CHANNEL_NUM; index++) {
        if ((index != channel)
            && pwm_channel_state[pwm_index][index].enabled
            && hpm_pwm_channel_shares_counter(channel, index)
            && (pwm_channel_state[pwm_index][index].reload != reload)) {
            rt_kprintf("pwm%u channel %u conflicts with enabled channel %u: "
                       "shared counter requires the same frequency\n",
                       (unsigned int)pwm_index, (unsigned int)channel, (unsigned int)index);
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}

static rt_err_t hpm_pwm_check_pair_conflict(uint8_t pwm_index,
                                            const struct rt_pwm_configuration *config)
{
    uint8_t channel = config->channel;
    bool complementary = hpm_pwm_use_complementary(channel, config->complementary);

    if (complementary && !hpm_pwm_channel_has_pair(channel)) {
        return -RT_EINVAL;
    }

    if (complementary && pwm_channel_state[pwm_index][channel + 1U].enabled) {
        rt_kprintf("pwm%u channel %u conflicts with enabled channel %u: "
                   "complementary output requires the channel pair\n",
                   (unsigned int)pwm_index, (unsigned int)channel,
                   (unsigned int)(channel + 1U));
        return -RT_EBUSY;
    }

    if (((channel & 1U) != 0U)
        && pwm_channel_state[pwm_index][channel - 1U].enabled
        && hpm_pwm_use_complementary(channel - 1U,
                                     pwm_channel_state[pwm_index][channel - 1U].config.complementary)) {
        rt_kprintf("pwm%u channel %u is used by complementary channel %u\n",
                   (unsigned int)pwm_index, (unsigned int)channel,
                   (unsigned int)(channel - 1U));
        return -RT_EBUSY;
    }

    return RT_EOK;
}

static rt_err_t hpm_generate_central_aligned_waveform(
    uint8_t pwm_index, const struct rt_pwm_configuration *config)
{
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    PWMV2_Type * pwm_base;
    pwm_counter_t pwm_counter;
#else
    PWM_Type * pwm_base;
    pwm_cmp_config_t cmp_config[2] = {0};
    pwm_config_t pwm_config = {0};
    pwm_pair_config_t pair_config = {0};
#endif
    uint8_t channel = config->channel;
    uint32_t duty;
    uint32_t reload;
    uint32_t dead_ticks;
    uint32_t cmp_a;
    uint32_t cmp_b;
    bool complementary;
    bool counter_active;
    bool invert;

    pwm_base = pwm_base_tbl[pwm_index];

    init_pwm_pins(pwm_base);
    if (hpm_pwm_validate_configuration(pwm_index, config, &reload, &duty,
                                       &dead_ticks) != RT_EOK) {
        return -RT_EINVAL;
    }
    complementary = hpm_pwm_use_complementary(channel, config->complementary);
    counter_active = hpm_pwm_counter_is_active(pwm_index, channel);
    hpm_pwm_calculate_compare(reload, duty, config->phase, &cmp_a, &cmp_b, &invert);

#if defined(HPMSOC_HAS_HPMSDK_PWMV2)

    pwm_counter = pwmv2_counter_tbl[channel];

    if (!counter_active) {
        pwmv2_disable_counter(pwm_base, pwm_counter);
        pwmv2_reset_counter(pwm_base, pwm_counter);
    }
    pwmv2_shadow_register_unlock(pwm_base);

    pwmv2_set_shadow_val(pwm_base, channel / 2, reload, 0, false);  /**< cnt use 0-3 shadow */
    pwmv2_set_shadow_val(pwm_base, channel * 2 + 4, reload, 0, false);
    pwmv2_set_shadow_val(pwm_base, channel * 2 + 5, reload, 0, false);

    pwmv2_counter_select_data_offset_from_shadow_value(pwm_base, pwm_counter, channel / 2);
    pwmv2_counter_burst_disable(pwm_base, pwm_counter);
    pwmv2_set_reload_update_time(pwm_base, pwm_counter, pwm_reload_update_on_reload);

    pwmv2_select_cmp_source(pwm_base, channel * 2, cmp_value_from_shadow_val, channel * 2 + 4);
    pwmv2_select_cmp_source(pwm_base, channel * 2 + 1, cmp_value_from_shadow_val, channel * 2 + 5);

    pwmv2_shadow_register_lock(pwm_base);
    pwmv2_cmp_update_trig_time(pwm_base, channel * 2,
                               pwm_shadow_register_update_on_reload);
    pwmv2_cmp_update_trig_time(pwm_base, channel * 2 + 1,
                               pwm_shadow_register_update_on_reload);
    pwmv2_disable_four_cmp(pwm_base, channel);
    if (invert) {
        pwmv2_enable_output_invert(pwm_base, channel);
    } else {
        pwmv2_disable_output_invert(pwm_base, channel);
    }
    pwmv2_disable_pair_mode(pwm_base, channel & ~1U);
    pwmv2_disable_pair_mode(pwm_base, (channel & ~1U) + 1U);
    if (complementary) {
        pwmv2_set_dead_area(pwm_base, channel, dead_ticks);
        pwmv2_set_dead_area(pwm_base, channel + 1U, dead_ticks);
        pwmv2_enable_pair_mode(pwm_base, channel);
        pwmv2_enable_pair_mode(pwm_base, channel + 1U);
        pwmv2_channel_enable_output(pwm_base, channel + 1U);
    }
    pwmv2_channel_enable_output(pwm_base, channel);
    pwmv2_enable_counter(pwm_base, pwm_counter);
    pwmv2_start_pwm_output(pwm_base, pwm_counter);

    pwmv2_shadow_register_unlock(pwm_base);
    pwmv2_set_shadow_val(pwm_base, channel * 2 + 4, cmp_a, 0, false);
    pwmv2_set_shadow_val(pwm_base, channel * 2 + 5, cmp_b, 0, false);
    pwmv2_shadow_register_lock(pwm_base);
#else

    if (!counter_active) {
        pwm_stop_counter(pwm_base);
    }

    /*
     * reload and start counter
     */
    pwm_set_reload(pwm_base, 0, reload);
    if (!counter_active) {
        pwm_set_start_count(pwm_base, 0, 0);
    }

    /*
     * config cmp1 and cmp2
     */

    cmp_config[0].mode = pwm_cmp_mode_output_compare;
    cmp_config[0].cmp = cmp_a;
    cmp_config[0].update_trigger = pwm_shadow_register_update_on_shlk;

    cmp_config[1].mode = pwm_cmp_mode_output_compare;
    cmp_config[1].cmp = cmp_b;
    cmp_config[1].update_trigger = pwm_shadow_register_update_on_shlk;

    /*
     * config pwm
     */
    if (complementary) {
        pwm_get_default_pwm_pair_config(pwm_base, &pair_config);
        pair_config.pwm[0].enable_output = true;
        pair_config.pwm[0].dead_zone_in_half_cycle = dead_ticks;
        pair_config.pwm[0].invert_output = invert;
        pair_config.pwm[1].enable_output = true;
        pair_config.pwm[1].dead_zone_in_half_cycle = dead_ticks;
        pair_config.pwm[1].invert_output = invert;
        if (status_success != pwm_setup_waveform_in_pair(pwm_base, channel, &pair_config,
                                                         channel * 2, cmp_config, 2)) {
            return -RT_ERROR;
        }
    } else {
        pwm_get_default_pwm_config(pwm_base, &pwm_config);
        pwm_config.enable_output = true;
        pwm_config.invert_output = invert;
        if (status_success != pwm_setup_waveform(pwm_base, channel, &pwm_config,
                                                 channel * 2, cmp_config, 2)) {
            return -RT_ERROR;
        }
        pwm_base->PWMCFG[channel & ~1U] &= ~PWM_PWMCFG_PAIR_MASK;
        pwm_base->PWMCFG[(channel & ~1U) + 1U] &= ~PWM_PWMCFG_PAIR_MASK;
    }
    pwm_start_counter(pwm_base);
    pwm_issue_shadow_register_lock_event(pwm_base);

#endif
    return RT_EOK;

}

static rt_err_t hpm_set_central_aligned_waveform(
    uint8_t pwm_index, const struct rt_pwm_configuration *config)
{
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    PWMV2_Type * pwm_base;
#else
    PWM_Type * pwm_base;
#endif
    uint8_t channel = config->channel;
    uint32_t duty;
    uint32_t reload;
    uint32_t dead_ticks;
    uint32_t cmp_a;
    uint32_t cmp_b;
    bool complementary;
    bool invert;

    pwm_base = pwm_base_tbl[pwm_index];
    if (hpm_pwm_validate_configuration(pwm_index, config, &reload, &duty,
                                       &dead_ticks) != RT_EOK) {
        return -RT_EINVAL;
    }
    complementary = hpm_pwm_use_complementary(channel, config->complementary);
    hpm_pwm_calculate_compare(reload, duty, config->phase, &cmp_a, &cmp_b, &invert);

#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    pwmv2_shadow_register_unlock(pwm_base);
    pwmv2_set_shadow_val(pwm_base, channel / 2, reload, 0, false);  /**< cnt use 0-3 shadow */
    pwmv2_set_shadow_val(pwm_base, channel * 2 + 4, cmp_a, 0, false);
    pwmv2_set_shadow_val(pwm_base, channel * 2 + 5, cmp_b, 0, false);
    pwmv2_shadow_register_lock(pwm_base);
    if (invert) {
        pwmv2_enable_output_invert(pwm_base, channel);
    } else {
        pwmv2_disable_output_invert(pwm_base, channel);
    }
    if (complementary) {
        pwmv2_set_dead_area(pwm_base, channel, dead_ticks);
        pwmv2_set_dead_area(pwm_base, channel + 1U, dead_ticks);
    }
#else
    if (complementary) {
        pwm_disable_output(pwm_base, channel);
        pwm_disable_output(pwm_base, channel + 1U);
    }
    pwm_set_reload(pwm_base, 0, reload);
    pwm_shadow_register_unlock(pwm_base);
    pwm_cmp_update_cmp_value(pwm_base, channel * 2, cmp_a, 0);
    pwm_cmp_update_cmp_value(pwm_base, channel * 2 + 1, cmp_b, 0);
    pwm_base->CHCFG[channel] = (pwm_base->CHCFG[channel] & ~PWM_CHCFG_OUTPOL_MASK)
                               | PWM_CHCFG_OUTPOL_SET(invert);
    if (complementary) {
        pwm_base->CHCFG[channel + 1U] =
            (pwm_base->CHCFG[channel + 1U] & ~PWM_CHCFG_OUTPOL_MASK)
            | PWM_CHCFG_OUTPOL_SET(invert);
        pwm_base->PWMCFG[channel] = (pwm_base->PWMCFG[channel] & ~PWM_PWMCFG_DEADAREA_MASK)
                                    | PWM_PWMCFG_PAIR_MASK
                                    | PWM_PWMCFG_DEADAREA_SET(dead_ticks);
        pwm_base->PWMCFG[channel + 1U] =
            (pwm_base->PWMCFG[channel + 1U] & ~PWM_PWMCFG_DEADAREA_MASK)
            | PWM_PWMCFG_PAIR_MASK
            | PWM_PWMCFG_DEADAREA_SET(dead_ticks);
        pwm_enable_output(pwm_base, channel);
        pwm_enable_output(pwm_base, channel + 1U);
    }
    pwm_issue_shadow_register_lock_event(pwm_base);
#endif

    return RT_EOK;
}

static rt_err_t hpm_disable_pwm(uint8_t pwm_index, uint8_t channel, bool complementary)
{
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
    pwmv2_channel_disable_output(pwm_base_tbl[pwm_index], channel);
    if (complementary) {
        pwmv2_channel_disable_output(pwm_base_tbl[pwm_index], channel + 1U);
    }
#else
    pwm_disable_output(pwm_base_tbl[pwm_index], channel);
    if (complementary) {
        pwm_disable_output(pwm_base_tbl[pwm_index], channel + 1U);
    }
#endif
    return RT_EOK;

}

static rt_err_t hpm_pwm_update_configuration(uint8_t pwm_index,
                                             hpm_pwm_channel_state_t *state,
                                             struct rt_pwm_configuration *config)
{
    uint32_t reload;
    uint32_t duty;
    uint32_t dead_ticks;
    rt_err_t status;

    config->complementary = hpm_pwm_use_complementary(config->channel,
                                                       config->complementary);
    status = hpm_pwm_validate_configuration(pwm_index, config, &reload, &duty,
                                            &dead_ticks);
    if (status != RT_EOK) {
        return status;
    }
    status = hpm_pwm_check_frequency_conflict(pwm_index, config->channel, reload);
    if (status != RT_EOK) {
        return status;
    }
    status = hpm_pwm_check_pair_conflict(pwm_index, config);
    if (status != RT_EOK) {
        return status;
    }

    if (state->enabled) {
        status = hpm_set_central_aligned_waveform(pwm_index, config);
        if (status != RT_EOK) {
            return status;
        }
    }

    state->config = *config;
    state->reload = reload;
    state->configured = true;
    return RT_EOK;
}

static rt_err_t hpm_pwm_set_reload_irq(uint8_t pwm_index, uint8_t channel, bool enable)
{
    uint8_t index;
    bool shared_irq_enabled = false;

    pwm_channel_state[pwm_index][channel].irq_enabled = enable;
    if (!enable) {
        for (index = 0; index < PWM_CHANNEL_NUM; index++) {
            if ((index != channel)
                && pwm_channel_state[pwm_index][index].irq_enabled
                && hpm_pwm_channel_shares_counter(channel, index)) {
                shared_irq_enabled = true;
                break;
            }
        }
    }

    if (enable || !shared_irq_enabled) {
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
        if (enable) {
            pwmv2_clear_reload_irq_status(pwm_base_tbl[pwm_index],
                                          1U << pwmv2_counter_tbl[channel]);
            pwmv2_enable_reload_irq(pwm_base_tbl[pwm_index], pwmv2_counter_tbl[channel]);
        } else {
            pwmv2_disable_reload_irq(pwm_base_tbl[pwm_index], pwmv2_counter_tbl[channel]);
        }
#else
        if (enable) {
            pwm_clear_status(pwm_base_tbl[pwm_index], PWM_IRQ_RELOAD);
            pwm_enable_irq(pwm_base_tbl[pwm_index], PWM_IRQ_RELOAD);
        } else {
            pwm_disable_irq(pwm_base_tbl[pwm_index], PWM_IRQ_RELOAD);
        }
#endif
    }

    return RT_EOK;
}

static rt_err_t hpm_pwm_execute_control_impl(uint8_t pwm_index, int cmd,
                                             struct rt_pwm_configuration *configuration)
{
    hpm_pwm_channel_state_t *state;
    struct rt_pwm_configuration config;
    bool release_complementary_output;
    rt_err_t status;

    if ((configuration == RT_NULL) || (pwm_index >= PWM_INSTANCE_NUM)
        || (configuration->channel >= PWM_CHANNEL_NUM)) {
        return -RT_EINVAL;
    }

    state = &pwm_channel_state[pwm_index][configuration->channel];

    switch (cmd) {
    case PWM_CMD_ENABLE:
        if (!state->configured) {
            rt_kprintf("pwm%u channel %u has not been configured\n",
                       (unsigned int)pwm_index, (unsigned int)configuration->channel);
            return -RT_EINVAL;
        }
        config = state->config;
        config.complementary = hpm_pwm_use_complementary(config.channel,
                                                          configuration->complementary);
        status = hpm_pwm_check_frequency_conflict(pwm_index, config.channel, state->reload);
        if (status != RT_EOK) {
            return status;
        }
        status = hpm_pwm_check_pair_conflict(pwm_index, &config);
        if (status != RT_EOK) {
            return status;
        }
        release_complementary_output = state->enabled
                                       && state->config.complementary
                                       && !config.complementary;
        if (release_complementary_output) {
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
            pwmv2_channel_disable_output(pwm_base_tbl[pwm_index], config.channel + 1U);
#else
            pwm_disable_output(pwm_base_tbl[pwm_index], config.channel + 1U);
#endif
        }
        status = hpm_generate_central_aligned_waveform(pwm_index, &config);
        if (status == RT_EOK) {
            state->config = config;
            state->enabled = true;
        } else if (release_complementary_output) {
#if defined(HPMSOC_HAS_HPMSDK_PWMV2)
            pwmv2_channel_enable_output(pwm_base_tbl[pwm_index], config.channel + 1U);
#else
            pwm_enable_output(pwm_base_tbl[pwm_index], config.channel + 1U);
#endif
        }
        return status;

    case PWM_CMD_DISABLE:
        status = hpm_disable_pwm(pwm_index, configuration->channel,
                                 state->configured && state->config.complementary);
        if (status == RT_EOK) {
            state->enabled = false;
            if (!hpm_pwm_counter_is_active(pwm_index, configuration->channel)) {
                hpm_pwm_stop_counter(pwm_index, configuration->channel);
            }
        }
        return status;

    case PWM_CMD_SET:
        config = *configuration;
        if (state->configured) {
            config.dead_time = state->config.dead_time;
            config.phase = state->config.phase;
            config.complementary = state->config.complementary;
        }
        return hpm_pwm_update_configuration(pwm_index, state, &config);

    case PWM_CMD_GET:
        if (!state->configured) {
            return -RT_EINVAL;
        }
        *configuration = state->config;
        return RT_EOK;

    case PWM_CMD_SET_PERIOD:
        if (!state->configured) {
            return -RT_EINVAL;
        }
        config = state->config;
        config.period = configuration->period;
        return hpm_pwm_update_configuration(pwm_index, state, &config);

    case PWM_CMD_SET_PULSE:
        if (!state->configured) {
            return -RT_EINVAL;
        }
        config = state->config;
        config.pulse = configuration->pulse;
        return hpm_pwm_update_configuration(pwm_index, state, &config);

    case PWM_CMD_SET_DEAD_TIME:
        if (!state->configured) {
            return -RT_EINVAL;
        }
        config = state->config;
        config.dead_time = configuration->dead_time;
        return hpm_pwm_update_configuration(pwm_index, state, &config);

    case PWM_CMD_SET_PHASE:
        if (!state->configured) {
            return -RT_EINVAL;
        }
        config = state->config;
        config.phase = configuration->phase;
        return hpm_pwm_update_configuration(pwm_index, state, &config);

    case PWM_CMD_ENABLE_IRQ:
        return hpm_pwm_set_reload_irq(pwm_index, configuration->channel, true);

    case PWM_CMD_DISABLE_IRQ:
        return hpm_pwm_set_reload_irq(pwm_index, configuration->channel, false);

    default:
        return -RT_EINVAL;
    }
}

static rt_err_t hpm_pwm_execute_control(uint8_t pwm_index, int cmd,
                                        struct rt_pwm_configuration *configuration)
{
    rt_base_t critical_level;
    rt_err_t status;

    critical_level = rt_enter_critical();
    status = hpm_pwm_execute_control_impl(pwm_index, cmd, configuration);
    rt_exit_critical_safe(critical_level);

    return status;
}

static rt_err_t hpm_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    uint8_t pwm_index;

    pwm_index = (uint8_t)(rt_ubase_t)device->parent.user_data;

    return hpm_pwm_execute_control(pwm_index, cmd, (struct rt_pwm_configuration *)arg);
}

static const struct rt_pwm_ops hpm_pwm_ops = {
        .control = &hpm_pwm_control
};

#ifdef HPM_PWM0
static struct rt_device_pwm hpm_dev_pwm0 = {
        .ops = &hpm_pwm_ops,
};
#endif

#ifdef HPM_PWM1
static struct rt_device_pwm hpm_dev_pwm1 = {
        .ops = &hpm_pwm_ops,
};
#endif

#ifdef HPM_PWM2
static struct rt_device_pwm hpm_dev_pwm2 = {
        .ops = &hpm_pwm_ops,
};
#endif

#ifdef HPM_PWM3
static struct rt_device_pwm hpm_dev_pwm3 = {
        .ops = &hpm_pwm_ops,
};
#endif


int rt_hw_pwm_init(void)
{
    int ret = RT_EOK;

#ifdef HPM_PWM0
    ret = rt_device_pwm_register(&hpm_dev_pwm0, "pwm0", &hpm_pwm_ops,
                                 (void *)(rt_ubase_t)0U);
    if (ret != RT_EOK) {
        return ret;
    }
#endif

#ifdef HPM_PWM1
    ret = rt_device_pwm_register(&hpm_dev_pwm1, "pwm1", &hpm_pwm_ops,
                                 (void *)(rt_ubase_t)1U);
    if (ret != RT_EOK) {
        return ret;
    }
#endif
#ifdef HPM_PWM2
    ret = rt_device_pwm_register(&hpm_dev_pwm2, "pwm2", &hpm_pwm_ops,
                                 (void *)(rt_ubase_t)2U);
    if (ret != RT_EOK) {
        return ret;
    }
#endif
#ifdef HPM_PWM3
    ret = rt_device_pwm_register(&hpm_dev_pwm3, "pwm3", &hpm_pwm_ops,
                                 (void *)(rt_ubase_t)3U);
    if (ret != RT_EOK) {
        return ret;
    }
#endif

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */
