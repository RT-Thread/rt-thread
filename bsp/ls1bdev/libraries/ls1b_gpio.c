/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 * 2021-02-02     michael5hzg@gmail.com       adapt to ls1b
 */


#include "ls1b_public.h"
#include "ls1b_regs.h"
#include "ls1b_gpio.h"
#include "ls1b_pin.h"


/*
 * 获取指定gpio的CFG寄存器
 * @gpio gpio编号
 * @ret CFG寄存器
 */
volatile unsigned int *gpio_get_cfg_reg(unsigned int gpio)
{
    volatile unsigned int *gpio_cfgx = NULL;            // GPIO_CFGx寄存器
    unsigned int port = GPIO_GET_PORT(gpio);

    switch (port)
    {
        case 0:
            gpio_cfgx = (volatile unsigned int *)LS1B_GPIO_CFG0;
            break;

        case 1:
            gpio_cfgx = (volatile unsigned int *)LS1B_GPIO_CFG1;
            break;
        default:
            gpio_cfgx = NULL;
            break;
    }

    return gpio_cfgx;
}


/*
 * 获取指定gpio的EN寄存器
 * @gpio gpio编号
 * @ret EN寄存器
 */
volatile unsigned int *gpio_get_en_reg(unsigned int gpio)
{
    volatile unsigned int *gpio_enx = NULL;         // GPIO_ENx寄存器
    unsigned int port = GPIO_GET_PORT(gpio);
    
    switch (port)
    {
        case 0:
            gpio_enx = (volatile unsigned int *)LS1B_GPIO_EN0;
            break;

        case 1:
            gpio_enx = (volatile unsigned int *)LS1B_GPIO_EN1;
            break;
        default:
            gpio_enx    = NULL;
            return gpio_enx;
    }

    return gpio_enx;
}

/*
 * gpio初始化
 * @gpio gpio引脚，取值范围[0, 127]
 * @mode gpio的工作模式(输入、输出)
 *
 * 例: 将gpio50初始化为输出
 * gpio_init(50, gpio_mode_output);
 */
void gpio_init(unsigned int gpio, gpio_mode_t mode)
{
    volatile unsigned int *gpio_enx = NULL;        // GPIO_ENx寄存器
    unsigned int pin = GPIO_GET_PIN(gpio);

    // 将pin设为普通GPIO
    pin_set_purpose(gpio, PIN_PURPOSE_GPIO);

    // 设置gpio工作模式(输入、输出)
    gpio_enx  = gpio_get_en_reg(gpio);
    if (gpio_mode_output == mode)       // 输出
    {
        reg_clr_one_bit(gpio_enx, pin);
    }
    else                                // 输入
    {
        reg_set_one_bit(gpio_enx, pin);
    }

    return ;
}


/*
 * 在指定gpio输出高电平或低电平
 * @gpio gpio引脚，取值范围[0, 127]
 * @level 电平值
 *
 * 例: 在gpio50上输出低电平
 * gpio_set(50, gpio_level_low);
 */
void gpio_set(unsigned int gpio, gpio_level_t level)
{
    volatile unsigned int *gpio_outx = NULL;       // GPIO_OUTx寄存器
    unsigned int port   = GPIO_GET_PORT(gpio);
    unsigned int pin    = GPIO_GET_PIN(gpio);

    // 获取寄存器地址
    switch (port)
    {
        case 0:
            gpio_outx = (volatile unsigned int *)LS1B_GPIO_OUT0;
            break;

        case 1:
            gpio_outx = (volatile unsigned int *)LS1B_GPIO_OUT1;
            break;
        default:        // 正确的程序不应该走到这里，直接返回
            return ;
    }

    // 输出
    if (gpio_level_low == level)
    {
        reg_clr_one_bit(gpio_outx, pin);
    }
    else
    {
        reg_set_one_bit(gpio_outx, pin);
    }

    return ;
}


/*
 * 读取指定gpio引脚的值
 * @gpio gpio引脚，取值范围[0,127]
 *
 * 例: 读取gpio50引脚上的值
 * gpio_level_t level;
 * level = gpio_get(50);
 */
unsigned int gpio_get(unsigned int gpio)
{
    volatile unsigned int *gpio_inx = NULL;        // GPIO_INx寄存器
    unsigned int port   = GPIO_GET_PORT(gpio);
    unsigned int pin    = GPIO_GET_PIN(gpio);

    // 获取寄存器地址
    switch (port)
    {
        case 0:
            gpio_inx = (volatile unsigned int *)LS1B_GPIO_IN0;
            break;

        case 1:
            gpio_inx = (volatile unsigned int *)LS1B_GPIO_IN1;
            break;
        default:        // 正常的流程不应该走到这里，直接返回
            return 0;
    }

    // 读取
    return reg_get_bit(gpio_inx, pin);
}


/**
 * 设置中断类型
 * @gpio gpio引脚
 * @type 触发中断的条件。高电平触发、低电平触发、上升沿触发 or 下降沿触发
 */
void gpio_set_irq_type(unsigned int gpio, gpio_irq_type_t type)
{
    volatile unsigned int *int_pol = NULL;     // 中断极性选择寄存器
    volatile unsigned int *int_edge = NULL;    // 中断边沿选择寄存器
    unsigned int port = GPIO_GET_PORT(gpio);
    unsigned int pin  = GPIO_GET_PIN(gpio);

    // 获取寄存器地址
    switch (port)
    {
        case 0:     // GPIO[31:0]
            int_pol     = (volatile unsigned int *)LS1B_INT2_POL;
            int_edge    = (volatile unsigned int *)LS1B_INT2_EDGE;
            break;

        case 1:     // GPIO[63:32]
            int_pol     = (volatile unsigned int *)LS1B_INT3_POL;
            int_edge    = (volatile unsigned int *)LS1B_INT3_EDGE;
            break;

    }

    // 设置中断类型
    switch (type)
    {
        case IRQ_TYPE_EDGE_RISING:
            *int_pol    |= (1 << pin);
            *int_edge   |= (1 << pin);
            break;

        case IRQ_TYPE_EDGE_FALLING:
            *int_pol    &= ~(1 << pin);
            *int_edge   |= (1 << pin);
            break;

        case IRQ_TYPE_LEVEL_HIGH:
            *int_pol    |= (1 << pin);
            *int_edge   &= ~(1 << pin);
            break;

        case IRQ_TYPE_LEVEL_LOW:
            *int_pol    &= ~(1 << pin);
            *int_edge   &= ~(1 << pin);
            break;

        default:
            break;
    }

    return ;
}


    
