/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-08-04     Emuzit            first version
 */
#ifndef __CH56X_PWM_H__
#define __CH56X_PWM_H__

#include "soc.h"
#include "ch56x_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_DEVICE_NAME     "pwmx"

#define PWM_CHANNELS        4

#define PWM0_PIN            GET_PIN(B, 15)
#define PWM1_PIN            GET_PIN(A, 4)
#define PWM2_PIN            GET_PIN(B, 1)
#define PWM3_PIN            GET_PIN(B, 2)

union _pwm_ctrl_mod
{
    uint8_t reg;
    struct
    {
        uint8_t pwm0_out_en : 1;  // RW, PWM output enable
        uint8_t pwm1_out_en : 1;
        uint8_t pwm2_out_en : 1;
        uint8_t pwm3_out_en : 1;
        uint8_t pwm0_polar  : 1;  // RW, PWM output polarity
        uint8_t pwm1_polar  : 1;
        uint8_t pwm2_polar  : 1;
        uint8_t pwm3_polar  : 1;
    };
};
#define RB_PWM0_OUT_EN      0x01
#define RB_PWM1_OUT_EN      0x02
#define RB_PWM2_OUT_EN      0x04
#define RB_PWM3_OUT_EN      0x08
#define RB_PWM0_POLAR       0x10
#define RB_PWM1_POLAR       0x20
#define RB_PWM2_POLAR       0x40
#define RB_PWM3_POLAR       0x80

#define PWM_OUT_EN_MASK     0x0f

union _pwm_ctrl_cfg
{
    uint8_t reg;
    struct
    {
        uint8_t cycle_sel   : 1;  // RW, PWM cycle select, 0/1 for 256/255
        uint8_t resv_1      : 7;
    };
};
#define RB_PWM_CYCLE_SEL    0x01

#define PWM_CYCLE_SEL_256   0
#define PWM_CYCLE_SEL_255   1

/*
 * 0x00  R8_PWM_CTRL_MOD:   PWM control register
 * 0x01  R8_PWM_CTRL_CFG:   PWM control configuration register
 * 0x02  R8_PWM_CLOCK_DIV:  PWM clock divisor register
 * 0x04  R8_PWM0_DATA:      PWM0 data holding register
 * 0x05  R8_PWM1_DATA:      PWM1 data holding register
 * 0x06  R8_PWM2_DATA:      PWM2 data holding register
 * 0x07  R8_PWM3_DATA:      PWM3 data holding register
 */
struct pwm_registers
{
    union _pwm_ctrl_mod     CTRL_MOD;
    union _pwm_ctrl_cfg     CTRL_CFG;
    uint8_t                 CLOCK_DIV;
    uint8_t                 resv_3;
    union
    {
        uint32_t            R32_PWM_DATA;
        uint8_t             PWM_DATA[4];
        struct
        {
            uint8_t         PWM0_DATA;
            uint8_t         PWM1_DATA;
            uint8_t         PWM2_DATA;
            uint8_t         PWM3_DATA;
        };
    };
};
CHECK_STRUCT_SIZE(struct pwm_registers, 8);

#ifdef __cplusplus
}
#endif

#endif
