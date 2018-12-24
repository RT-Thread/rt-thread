/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */

// 引脚功能(普通gpio，pwm，复用等)相关接口


#include "ls1c_public.h"
#include "ls1c_regs.h"
#include "ls1c_gpio.h"
#include "ls1c_pin.h"


/*
 * 把指定pin设置为指定用途(普通gpio，非gpio)
 * @gpio gpio引脚编号
 * @purpose 用途
 */
void pin_set_purpose(unsigned int gpio, pin_purpose_t purpose)
{
    volatile unsigned int *gpio_cfgx;           // GPIO_CFGx寄存器
    unsigned int pin = GPIO_GET_PIN(gpio);

    gpio_cfgx = gpio_get_cfg_reg(gpio);
    if (PIN_PURPOSE_GPIO == purpose)            // 引脚用作普通gpio
    {
        reg_set_one_bit(gpio_cfgx, pin);
    }
    else                                        // 引脚用作其它功能(非gpio)
    {
        reg_clr_one_bit(gpio_cfgx, pin);
    }

    return ;
}



/*
 * 设置指定pin为第n复用
 * @gpio gpio编号
 * @remap 第n复用
 */
void pin_set_remap(unsigned int gpio, pin_remap_t remap)
{
    volatile unsigned int *reg = NULL;          // 复用寄存器
    unsigned int port = GPIO_GET_PORT(gpio);
    unsigned int pin  = GPIO_GET_PIN(gpio);
    int i;

    /*指定全部pin复用为0*/
    for (i = 0; i <= 4; i++)
    {
        reg = (volatile unsigned int *)((LS1C_CBUS_FIRST0) + ((port) * 0x04) + ((i) * 0x10));
        // 置0
        reg_clr_one_bit(reg, pin);
    }

    if (remap == PIN_REMAP_DEFAULT) return;

    switch (port)
    {
    case 0:
        switch (remap)
        {
        case PIN_REMAP_FIRST:
            reg = (volatile unsigned int *)LS1C_CBUS_FIRST0;
            break;
        case PIN_REMAP_SECOND:
            reg = (volatile unsigned int *)LS1C_CBUS_SECOND0;
            break;
        case PIN_REMAP_THIRD:
            reg = (volatile unsigned int *)LS1C_CBUS_THIRD0;
            break;
        case PIN_REMAP_FOURTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FOURTH0;
            break;
        case PIN_REMAP_FIFTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FIFTH0;
            break;
        }
        break;

    case 1:
        switch (remap)
        {
        case PIN_REMAP_FIRST:
            reg = (volatile unsigned int *)LS1C_CBUS_FIRST1;
            break;
        case PIN_REMAP_SECOND:
            reg = (volatile unsigned int *)LS1C_CBUS_SECOND1;
            break;
        case PIN_REMAP_THIRD:
            reg = (volatile unsigned int *)LS1C_CBUS_THIRD1;
            break;
        case PIN_REMAP_FOURTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FOURTH1;
            break;
        case PIN_REMAP_FIFTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FIFTH1;
            break;
        }
        break;

    case 2:
        switch (remap)
        {
        case PIN_REMAP_FIRST:
            reg = (volatile unsigned int *)LS1C_CBUS_FIRST2;
            break;
        case PIN_REMAP_SECOND:
            reg = (volatile unsigned int *)LS1C_CBUS_SECOND2;
            break;
        case PIN_REMAP_THIRD:
            reg = (volatile unsigned int *)LS1C_CBUS_THIRD2;
            break;
        case PIN_REMAP_FOURTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FOURTH2;
            break;
        case PIN_REMAP_FIFTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FIFTH2;
            break;
        }
        break;

    case 3:
        switch (remap)
        {
        case PIN_REMAP_FIRST:
            reg = (volatile unsigned int *)LS1C_CBUS_FIRST3;
            break;
        case PIN_REMAP_SECOND:
            reg = (volatile unsigned int *)LS1C_CBUS_SECOND3;
            break;
        case PIN_REMAP_THIRD:
            reg = (volatile unsigned int *)LS1C_CBUS_THIRD3;
            break;
        case PIN_REMAP_FOURTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FOURTH3;
            break;
        case PIN_REMAP_FIFTH:
            reg = (volatile unsigned int *)LS1C_CBUS_FIFTH3;
            break;
        }
        break;

    default:
        return ;
    }

    // 置1
    reg_set_one_bit(reg, pin);

    return ;
}



