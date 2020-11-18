/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */

// 封装硬件pwm接口

#include "ls1c_public.h"
#include "ls1c_pin.h"
#include "ls1c_pwm.h"
#include "ls1c_clock.h"
#include "ls1c_regs.h"

// pwm的最大周期
#define PWM_MAX_PERIOD                  (0xFFFFFF)      // 计数器的值

/*
 * 根据gpio获取相应pwm的基地址
 * @gpio pwm引脚
 * @ret pwm基地址
 */
unsigned int pwm_get_reg_base(unsigned int gpio)
{
    unsigned int reg_base = 0;
    
    switch (gpio)
    {
        case LS1C_PWM0_GPIO06:
        case LS1C_PWM0_GPIO04:
            reg_base = LS1C_REG_BASE_PWM0;
            break;

        case LS1C_PWM1_GPIO92:
        case LS1C_PWM1_GPIO05:
            reg_base = LS1C_REG_BASE_PWM1;
            break;

        case LS1C_PWM2_GPIO52:
        case LS1C_PWM2_GPIO46:
            reg_base = LS1C_REG_BASE_PWM2;
            break;

        case LS1C_PWM3_GPIO47:
        case LS1C_PWM3_GPIO53:
            reg_base = LS1C_REG_BASE_PWM3;
            break;
    }

    return reg_base;
}


/*
 * 禁止pwm
 * @pwm_info PWMn的详细信息
 */
void pwm_disable(pwm_info_t *pwm_info)
{
    unsigned int pwm_reg_base = 0;
    
    // 检查入参
    if (NULL == pwm_info)
    {
        return ;
    }

    pwm_reg_base = pwm_get_reg_base(pwm_info->gpio);
    reg_write_32(0, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_CTRL));

    return ;
}



/*
 * 使能PWM
 * @pwm_info PWMn的详细信息
 */
void pwm_enable(pwm_info_t *pwm_info)
{
    unsigned int pwm_reg_base = 0;
    unsigned int ctrl = 0;

    // 检查入参
    if (NULL == pwm_info)
    {
        return ;
    }

    // 获取基地址
    pwm_reg_base = pwm_get_reg_base(pwm_info->gpio);

    // 清零计数器
    reg_write_32(0, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_CNTR));

    // 设置控制寄存器
    ctrl = (0 << LS1C_PWM_INT_LRC_EN)
           | (0 << LS1C_PWM_INT_HRC_EN)
           | (0 << LS1C_PWM_CNTR_RST)
           | (0 << LS1C_PWM_INT_SR)
           | (0 << LS1C_PWM_INTEN)
           | (0 << LS1C_PWM_OE)
           | (1 << LS1C_PWM_CNT_EN);
    if (PWM_MODE_PULSE == pwm_info->mode)     // 单脉冲
    {
        ctrl |= (1 << LS1C_PWM_SINGLE);
    }
    else                            // 连续脉冲
    {
        ctrl &= ~(1 << LS1C_PWM_SINGLE);
    }
    reg_write_32(ctrl, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_CTRL));
    
    return ;
}



/*
 * 初始化PWMn
 * @pwm_info PWMn的详细信息
 */
void pwm_init(pwm_info_t *pwm_info)
{
    unsigned int gpio;
    unsigned long pwm_clk = 0;          // pwm模块的时钟频率
    unsigned long tmp = 0;
    unsigned int pwm_reg_base = 0;
    unsigned long period = 0;
    
    // 判断入参
    if (NULL == pwm_info)
    {
        // 入参非法，则直接返回
        return ;
    }
    gpio = pwm_info->gpio;

    // 配置相应引脚用作pwm，而非gpio
    pin_set_purpose(gpio, PIN_PURPOSE_OTHER);

    // 复用
    switch (gpio)
    {
        // 不需要复用
        case LS1C_PWM0_GPIO06:
        case LS1C_PWM1_GPIO92:
            break;

        case LS1C_PWM0_GPIO04:          // gpio04的第三复用
            pin_set_remap(LS1C_PWM0_GPIO04, PIN_REMAP_THIRD);
            break;

        case LS1C_PWM1_GPIO05:          // gpio05的第三复用
            pin_set_remap(LS1C_PWM1_GPIO05, PIN_REMAP_THIRD);
            break;

        case LS1C_PWM2_GPIO52:          // gpio52的第四复用
            pin_set_remap(LS1C_PWM2_GPIO52, PIN_REMAP_FOURTH);
            break;

        case LS1C_PWM2_GPIO46:          // gpio46的第四复用
            pin_set_remap(LS1C_PWM2_GPIO46, PIN_REMAP_FOURTH);
            break;

        case LS1C_PWM3_GPIO47:          // gpio47的第四复用
            pin_set_remap(LS1C_PWM3_GPIO47, PIN_REMAP_FOURTH);
            break;

        case LS1C_PWM3_GPIO53:          // gpio53的第四复用
            pin_set_remap(LS1C_PWM3_GPIO53, PIN_REMAP_FOURTH);
            break;

        default:
            break;
    }

    // 根据占空比和pwm周期计算寄存器HRC和LRC的值
    // 两个64位数相乘，只能得到低32位，linux下却可以得到64位结果，
    // 暂不清楚原因，用浮点运算代替
    pwm_clk = clk_get_apb_rate();
    period = (1.0 * pwm_clk * pwm_info->period_ns) / 1000000000;
    period = MIN(period, PWM_MAX_PERIOD);       // 限制周期不能超过最大值
    tmp = period - (period * pwm_info->duty);
    
    // 写寄存器HRC和LRC
    pwm_reg_base = pwm_get_reg_base(gpio);
    reg_write_32(--tmp, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_HRC));
    reg_write_32(--period, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_LRC));

    // 写主计数器
    pwm_enable(pwm_info);
    
    return ;
}

