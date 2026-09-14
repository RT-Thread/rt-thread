/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-25     CYFS         add the default PWM matrix test configuration
 */

#ifndef __PWM_TC_CONFIG_H__
#define __PWM_TC_CONFIG_H__

/*
 * Channel catalog
 *
 * Set ENABLED to RT_TRUE to include a channel in every group below, or
 * RT_FALSE to skip it. Disabled channels are not looked up or started.
 * READBACK_TOLERANCE is in permyriad; 0 disables PWM_CMD_GET verification.
 * The default enables only channel 1, which sweeps continuously in each group.
 */
#define PWM_TC_CFG_CHANNEL_1_ENABLED            RT_TRUE
#define PWM_TC_CFG_CHANNEL_1_DEVICE_NAME        "pwm12"
#define PWM_TC_CFG_CHANNEL_1_NUMBER             0
#define PWM_TC_CFG_CHANNEL_1_READBACK_TOLERANCE 500U

#define PWM_TC_CFG_CHANNEL_2_ENABLED            RT_FALSE
#define PWM_TC_CFG_CHANNEL_2_DEVICE_NAME        "pwm2"
#define PWM_TC_CFG_CHANNEL_2_NUMBER             1
#define PWM_TC_CFG_CHANNEL_2_READBACK_TOLERANCE 0U

#define PWM_TC_CFG_CHANNEL_3_ENABLED            RT_FALSE
#define PWM_TC_CFG_CHANNEL_3_DEVICE_NAME        "pwm3"
#define PWM_TC_CFG_CHANNEL_3_NUMBER             1
#define PWM_TC_CFG_CHANNEL_3_READBACK_TOLERANCE 0U

#define PWM_TC_CFG_CHANNEL_4_ENABLED            RT_FALSE
#define PWM_TC_CFG_CHANNEL_4_DEVICE_NAME        "pwm4"
#define PWM_TC_CFG_CHANNEL_4_NUMBER             1
#define PWM_TC_CFG_CHANNEL_4_READBACK_TOLERANCE 0U

/* Group timing */
#define PWM_TC_CFG_GROUP_1_DURATION_MS 2000U
#define PWM_TC_CFG_GROUP_2_DURATION_MS 1000U

/*
 * Waveform point tables
 *
 * PWM_TC_POINT_PERCENT takes frequency in Hz and duty cycle in percent.
 * PWM_TC_POINT takes frequency in Hz and duty cycle in permyriad.
 */
static const struct pwm_tc_point pwm_tc_channel_1_sweep_points[] = {
    PWM_TC_POINT_PERCENT(2500, 10),
    PWM_TC_POINT_PERCENT(2500, 50),
    PWM_TC_POINT_PERCENT(5000, 25),
    PWM_TC_POINT_PERCENT(5000, 75),
};

static const struct pwm_tc_point pwm_tc_channel_2_sweep_points[] = {
    PWM_TC_POINT_PERCENT(500, 20),
    PWM_TC_POINT_PERCENT(1500, 40),
    PWM_TC_POINT_PERCENT(4000, 60),
};

static const struct pwm_tc_point pwm_tc_channel_2_fixed_points[] = {
    PWM_TC_POINT_PERCENT(10000, 65),
};

static const struct pwm_tc_point pwm_tc_channel_3_sweep_points[] = {
    PWM_TC_POINT_PERCENT(800, 15),
    PWM_TC_POINT_PERCENT(1800, 35),
    PWM_TC_POINT_PERCENT(3200, 55),
};

static const struct pwm_tc_point pwm_tc_channel_3_fixed_points[] = {
    PWM_TC_POINT_PERCENT(6000, 30),
};

static const struct pwm_tc_point pwm_tc_channel_4_sweep_points[] = {
    PWM_TC_POINT_PERCENT(1200, 25),
    PWM_TC_POINT_PERCENT(2400, 50),
    PWM_TC_POINT_PERCENT(4800, 75),
};

static const struct pwm_tc_point pwm_tc_channel_4_fixed_points[] = {
    PWM_TC_POINT_PERCENT(8000, 70),
};

/*
 * Group 1 channel behavior
 *
 * Channels in a group run concurrently. Each channel selects its own output
 * mode, point table, and step interval in milliseconds.
 */
static const struct pwm_tc_channel pwm_tc_group_1_channels[] = {
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_1_ENABLED,
                          PWM_TC_CFG_CHANNEL_1_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_1_NUMBER,
                          PWM_TC_MODE_SWEEP_LOOP,
                          pwm_tc_channel_1_sweep_points,
                          200U,
                          PWM_TC_CFG_CHANNEL_1_READBACK_TOLERANCE),
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_2_ENABLED,
                          PWM_TC_CFG_CHANNEL_2_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_2_NUMBER,
                          PWM_TC_MODE_FIXED,
                          pwm_tc_channel_2_fixed_points,
                          0U,
                          PWM_TC_CFG_CHANNEL_2_READBACK_TOLERANCE),
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_3_ENABLED,
                          PWM_TC_CFG_CHANNEL_3_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_3_NUMBER,
                          PWM_TC_MODE_SWEEP_ONCE,
                          pwm_tc_channel_3_sweep_points,
                          250U,
                          PWM_TC_CFG_CHANNEL_3_READBACK_TOLERANCE),
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_4_ENABLED,
                          PWM_TC_CFG_CHANNEL_4_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_4_NUMBER,
                          PWM_TC_MODE_FIXED,
                          pwm_tc_channel_4_fixed_points,
                          0U,
                          PWM_TC_CFG_CHANNEL_4_READBACK_TOLERANCE),
};

/* Group 2 channel behavior */
static const struct pwm_tc_channel pwm_tc_group_2_channels[] = {
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_1_ENABLED,
                          PWM_TC_CFG_CHANNEL_1_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_1_NUMBER,
                          PWM_TC_MODE_SWEEP_LOOP,
                          pwm_tc_channel_1_sweep_points,
                          200U,
                          PWM_TC_CFG_CHANNEL_1_READBACK_TOLERANCE),
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_2_ENABLED,
                          PWM_TC_CFG_CHANNEL_2_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_2_NUMBER,
                          PWM_TC_MODE_SWEEP_ONCE,
                          pwm_tc_channel_2_sweep_points,
                          300U,
                          PWM_TC_CFG_CHANNEL_2_READBACK_TOLERANCE),
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_3_ENABLED,
                          PWM_TC_CFG_CHANNEL_3_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_3_NUMBER,
                          PWM_TC_MODE_FIXED,
                          pwm_tc_channel_3_fixed_points,
                          0U,
                          PWM_TC_CFG_CHANNEL_3_READBACK_TOLERANCE),
    PWM_TC_CHANNEL_CONFIG(PWM_TC_CFG_CHANNEL_4_ENABLED,
                          PWM_TC_CFG_CHANNEL_4_DEVICE_NAME,
                          PWM_TC_CFG_CHANNEL_4_NUMBER,
                          PWM_TC_MODE_SWEEP_LOOP,
                          pwm_tc_channel_4_sweep_points,
                          350U,
                          PWM_TC_CFG_CHANNEL_4_READBACK_TOLERANCE),
};

/* Test group list; groups run in array order. */
static const struct pwm_tc_group pwm_tc_groups[] = {
    {
        "mixed-output-loop",
        pwm_tc_group_1_channels,
        PWM_TC_ARRAY_SIZE(pwm_tc_group_1_channels),
        PWM_TC_CFG_GROUP_1_DURATION_MS,
    },
    {
        "mixed-output-sweep",
        pwm_tc_group_2_channels,
        PWM_TC_ARRAY_SIZE(pwm_tc_group_2_channels),
        PWM_TC_CFG_GROUP_2_DURATION_MS,
    },
};

#define PWM_TC_GROUPS      pwm_tc_groups
#define PWM_TC_GROUP_COUNT PWM_TC_ARRAY_SIZE(pwm_tc_groups)

#endif /* __PWM_TC_CONFIG_H__ */
