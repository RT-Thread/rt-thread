 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     dw_gpio.c
 * @brief
 * @version
 * @date     2020-01-08
 ******************************************************************************/

#include <string.h>

#include <csi_config.h>
#include <drv/gpio.h>
#include <drv/irq.h>
#include <drv/pin.h>

extern csi_error_t csi_pin_mode(pin_name_t pin_name, csi_gpio_mode_t mode);

static void dw_gpio_irqhandler(void *args)
{

    ///< TODO：获取GPIO中断的状态
    ///< TODO：清除中断
    ///< TODO：根据中断状态执行用户回调函数

}

csi_error_t csi_gpio_init(csi_gpio_t *gpio, uint32_t port_idx)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< 本函数初始化GPIO控制器，非单个GPIO PIN

    ///< 获取中断号、基地址等相关信息
    if (target_get(DEV_DW_GPIO_TAG, port_idx, &gpio->dev) != CSI_OK) {
        ret = CSI_ERROR;
    }

    return ret;
}

void csi_gpio_uninit(csi_gpio_t *gpio)
{
    CSI_PARAM_CHK_NORETVAL(gpio);

    ///< TODO：重置GPIO相关寄存器

    ///< 禁止中断控制器对应的中断和注销GPIO的中断服务函数
    csi_irq_disable((uint32_t)gpio->dev.irq_num);
    csi_irq_detach((uint32_t)gpio->dev.irq_num);

    ///< 释放句柄
    memset(gpio, 0, sizeof(csi_gpio_t));
}

csi_error_t csi_gpio_dir(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_dir_t dir)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);
    CSI_PARAM_CHK(pin_mask, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< 注意：pin_mask代表正在操作的GPIO PIN，例如pin_mask = 0x3，则代表正在操作GPIO PIN_0 和GPIO PIN_1

    ///< TODO：根据dir和pin_mask设置相应GPIO口数据传输的方向

    return ret;
}

csi_error_t csi_gpio_mode(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_mode_t mode)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);
    CSI_PARAM_CHK(pin_mask, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_error_t temp;
    uint8_t offset = 0U;
    pin_name_t pin_name;

    /* set pin mode */
    while (pin_mask) {
        if (pin_mask & 0x01U) {
            ///< 获取使用的GPIO口的引脚名称
            pin_name = csi_pin_get_pinname_by_gpio(gpio->dev.idx, offset);

            if ((uint8_t)pin_name != 0xFFU) {
                ///< 设置GPIO的模式：GPIO_MODE_PULLNONE、GPIO_MODE_PULLUP、GPIO_MODE_PULLDOWN、GPIO_MODE_OPEN_DRAIN、GPIO_MODE_PUSH_PULL
                temp = csi_pin_mode(pin_name, mode);

                if (temp == CSI_ERROR) { /* return CSI_ERROR if csi_pin_mode return CSI_ERROR */
                    ret = CSI_ERROR;
                    break;
                } else if (temp == CSI_UNSUPPORTED) { /* return CSI_UNSUPPORTED if csi_pin_mode return CSI_UNSUPPORTED */
                    ret = CSI_UNSUPPORTED;
                }
            }
        }

        pin_mask >>= 1U;
        offset++;
    }

    return ret;
}

csi_error_t csi_gpio_irq_mode(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_irq_mode_t mode)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);

    csi_error_t    ret = CSI_OK;

    switch (mode) {
        /* rising edge interrupt mode */
        case GPIO_IRQ_MODE_RISING_EDGE:
            ///< TODO：根据pin_mask和mode设置中断类型和中断极性
            break;

        /* falling edge interrupt mode */
        case GPIO_IRQ_MODE_FALLING_EDGE:
            ///< TODO：根据pin_mask和mode设置中断类型和中断极性
            break;

        /* low level interrupt mode */
        case GPIO_IRQ_MODE_LOW_LEVEL:
            ///< TODO：根据pin_mask和mode设置中断类型和中断极性
            break;

        /* high level interrupt mode */
        case GPIO_IRQ_MODE_HIGH_LEVEL:
            ///< TODO：根据pin_mask和mode设置中断类型和中断极性
            break;

        /* double edge interrupt mode */
        case GPIO_IRQ_MODE_BOTH_EDGE:
        default:
            ret = CSI_UNSUPPORTED;
            break;
    }

    return ret;
}

csi_error_t csi_gpio_irq_enable(csi_gpio_t *gpio, uint32_t pin_mask, bool enable)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);
    CSI_PARAM_CHK(pin_mask, CSI_ERROR);

    ///< TODO：打开或者关闭GPIO

    return CSI_OK;
}

csi_error_t csi_gpio_debonce(csi_gpio_t *gpio, uint32_t pin_mask, bool enable)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);
    CSI_PARAM_CHK(pin_mask, CSI_ERROR);

    return CSI_UNSUPPORTED;
}

void csi_gpio_toggle(csi_gpio_t *gpio, uint32_t pin_mask)
{
    CSI_PARAM_CHK_NORETVAL(gpio);
    CSI_PARAM_CHK_NORETVAL(pin_mask);

    ///< TODO：翻转GPIO口输出状态，例如，当前GPIO的输出状态是高电平，翻转之后则为低电平
}

void  csi_gpio_write(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_pin_state_t value)
{
    CSI_PARAM_CHK_NORETVAL(gpio);
    CSI_PARAM_CHK_NORETVAL(pin_mask);

    ///< TODO：根据value写数据寄存器

}

uint32_t csi_gpio_read(csi_gpio_t *gpio, uint32_t pin_mask)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);
    CSI_PARAM_CHK(pin_mask, CSI_ERROR);
    uint32_t status = 0U;

    ///< TODO：读取相应引脚的信号输入状态

    return status;

}

csi_error_t  csi_gpio_attach_callback(csi_gpio_t *gpio, void *callback, void *arg)
{
    CSI_PARAM_CHK(gpio, CSI_ERROR);
    CSI_PARAM_CHK(callback, CSI_ERROR);

    ///< TODO：清除中断

    gpio->callback = callback;
    gpio->arg      = arg;

    ///< 注册GPIO的中断服务函数，使能中断控制器对应的中断
    csi_irq_attach((uint32_t)gpio->dev.irq_num, &dw_gpio_irqhandler, &gpio->dev);
    csi_irq_enable((uint32_t)gpio->dev.irq_num);

    return CSI_OK;
}

void csi_gpio_detach_callback(csi_gpio_t *gpio)
{
    CSI_PARAM_CHK_NORETVAL(gpio);

    gpio->callback = NULL;
    gpio->arg      = NULL;

    ///< 注销GPIO的中断服务函数，禁止中断控制器对应的中断
    csi_irq_disable((uint32_t)gpio->dev.irq_num);
    csi_irq_detach((uint32_t)gpio->dev.irq_num);
}

#ifdef CONFIG_PM
csi_error_t dw_gpio_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复GPIO寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存GPIO寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_gpio_enable_pm(csi_gpio_t *gpio)
{
    ///< TODO：注册GPIO低功耗处理函数dw_gpio_pm_action
}

void csi_gpio_disable_pm(csi_gpio_t *gpio)
{
    csi_pm_dev_unregister(&gpio->dev);
}
#endif
