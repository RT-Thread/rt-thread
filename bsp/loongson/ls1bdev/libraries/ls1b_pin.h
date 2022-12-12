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

#ifndef __LOONGSON_PIN_H
#define __LOONGSON_PIN_H


// 引脚用途
typedef enum
{
    PIN_PURPOSE_GPIO = 0,               // 引脚用作普通gpio
    PIN_PURPOSE_OTHER,                  // 引脚用作其它功能(非gpio)
}pin_purpose_t;


// 引脚复用
typedef enum
{
    PIN_REMAP_FIRST = 0,                // 第一复用
    PIN_REMAP_SECOND,                   // 第二复用
    PIN_REMAP_THIRD,                    // 第三复用
    PIN_REMAP_FOURTH,                   // 第四复用
    PIN_REMAP_FIFTH,                    // 第五复用
    PIN_REMAP_DEFAULT,                //缺省复用
}pin_remap_t;


/*
 * 把指定pin设置为指定用途(普通gpio，非gpio)
 * @gpio gpio引脚编号
 * @purpose 用途
 */
void pin_set_purpose(unsigned int gpio, pin_purpose_t purpose);


/*
 * 设置指定pin为第n复用
 * @gpio gpio编号
 * @remap 第n复用
 */
void pin_set_remap(unsigned int gpio, pin_remap_t remap);


#endif

