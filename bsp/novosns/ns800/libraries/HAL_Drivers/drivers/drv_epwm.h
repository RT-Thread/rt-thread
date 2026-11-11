/**************************************************************************//**
*
* @copyright (C) 2026 Novosense Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2026-6-15        Eric           First version
*
******************************************************************************/

#ifndef __DRV_EPWM_H__
#define __DRV_EPWM_H__

#include <rtdef.h>

/* custom command to configure phase */
#define PWM_CMD_EXT_SET_SLAVE_PHASE     (RT_DEVICE_CTRL_BASE(PWM) + 99)

#define EPWM_PIN_INFO(epwm_port_a, epwm_pin_a, pin_mux_a,   \
                    epwm_port_b, epwm_pin_b, pin_mux_b)     \
    {                                           \
        .port_a = epwm_port_a,                  \
        .pin_a = epwm_pin_a,                    \
        .mux_a = pin_mux_a,                     \
        .port_b = epwm_port_b,                  \
        .pin_b = epwm_pin_b,                    \
        .mux_b = pin_mux_b                      \
    }

#define EPWM_DRV_INIT(num, cnt_mode, clk_div, hs_clk_div)   \
    {                                       \
        .name = "epwm"#num ,                \
        .instance = EPWM##num,              \
        .count_mode = cnt_mode,             \
        .clock_div = clk_div,               \
        .hs_clock_div = hs_clk_div          \
    }

/**
 *  @brief  EPWMx channel
 */
enum
{
    EPWMX_A = 0,
    EPWMX_B
};

/**
 *  @brief  EPWMx phase configuration
 */
struct rt_epwm_slave_phase_ext
{
    /*  EPWM master reference device,
        slave pwm phase compare with this master devcie */
    rt_device_t master_dev;
    /* unit: degree, 0~360 */
    rt_uint32_t phase_angle;
};

#endif
