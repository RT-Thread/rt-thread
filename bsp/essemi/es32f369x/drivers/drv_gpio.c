/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-01-14     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 */

#include "board.h"
#include "drv_gpio.h"

/*管脚映射在 es_conf_info_map.h 的 pins[] 中*/

#ifdef RT_USING_PIN


struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn},
    {GPIO_PIN_1, EXTI1_IRQn},
    {GPIO_PIN_2, EXTI2_IRQn},
    {GPIO_PIN_3, EXTI3_IRQn},
    {GPIO_PIN_4, EXTI4_IRQn},
    {GPIO_PIN_5, EXTI5_IRQn},
    {GPIO_PIN_6, EXTI6_IRQn},
    {GPIO_PIN_7, EXTI7_IRQn},
    {GPIO_PIN_8, EXTI8_IRQn},
    {GPIO_PIN_9, EXTI9_IRQn},
    {GPIO_PIN_10, EXTI10_IRQn},
    {GPIO_PIN_11, EXTI11_IRQn},
    {GPIO_PIN_12, EXTI12_IRQn},
    {GPIO_PIN_13, EXTI13_IRQn},
    {GPIO_PIN_14, EXTI14_IRQn},
    {GPIO_PIN_15, EXTI15_IRQn},
};

struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
};

#ifdef ES_CONF_EXTI_IRQ_0

rt_weak void irq_pin0_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 0\r\n");
}
#endif

#ifdef ES_CONF_EXTI_IRQ_1

rt_weak void irq_pin1_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 1\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_2

   rt_weak void irq_pin2_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 2\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_3

rt_weak void irq_pin3_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 3\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_4

rt_weak void irq_pin4_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 4\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_5

rt_weak void irq_pin5_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 5\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_6

rt_weak void irq_pin6_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 6\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_7

rt_weak void irq_pin7_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 7\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_8

rt_weak void irq_pin8_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 8\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_9

rt_weak void irq_pin9_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 9\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_10

rt_weak void irq_pin10_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 10\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_11

rt_weak void irq_pin11_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 11\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_12

rt_weak void irq_pin12_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 12\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_13

rt_weak void irq_pin13_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 13\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_14

rt_weak void irq_pin14_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 14\r\n");
}

#endif

#ifdef ES_CONF_EXTI_IRQ_15

rt_weak void irq_pin15_callback(void* arg)
{
    rt_kprintf("\r\nEXTI 15\r\n");
}

#endif


#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;
    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }
    return index;
};

void es32f3_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    ald_gpio_write_pin(index->gpio, index->pin, value);
}

rt_int8_t es32f3_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_int8_t value;
    const struct pin_index *index;
    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }
    value = ald_gpio_read_pin(index->gpio, index->pin);
    return value;
}

void es32f3_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    gpio_init_t gpio_initstruct;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    gpio_initstruct.mode = GPIO_MODE_OUTPUT;
    gpio_initstruct.func = GPIO_FUNC_1;
    gpio_initstruct.podrv = GPIO_OUT_DRIVE_6;
    gpio_initstruct.nodrv = GPIO_OUT_DRIVE_6;
    gpio_initstruct.type = GPIO_TYPE_CMOS;
    gpio_initstruct.odos = GPIO_PUSH_PULL;
    gpio_initstruct.flt = GPIO_FILTER_DISABLE;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpio_initstruct.mode = GPIO_MODE_OUTPUT;
        gpio_initstruct.pupd = GPIO_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.pupd = GPIO_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.pupd = GPIO_PUSH_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.pupd = GPIO_PUSH_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpio_initstruct.mode = GPIO_MODE_OUTPUT;
        gpio_initstruct.pupd = GPIO_FLOATING;
        gpio_initstruct.odos = GPIO_OPEN_DRAIN;
    }
    ald_gpio_init(index->gpio, index->pin, &gpio_initstruct);
}

rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint16_t gpio_pin)
{
    uint8_t map_index = 0U;

    while(gpio_pin >> (++map_index))
    {
    }
    map_index--;

    if (map_index >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[map_index];
};

rt_err_t es32f3_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                               rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    /* pin no. convert to dec no. */
    for (irqindex = 0; irqindex < 16; irqindex++)
    {
        if ((0x01 << irqindex) == index->pin)
        {
            break;
        }
    }
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == pin &&
            pin_irq_hdr_tab[irqindex].hdr == hdr &&
            pin_irq_hdr_tab[irqindex].mode == mode &&
            pin_irq_hdr_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_err_t es32f3_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    for (irqindex = 0; irqindex < 16; irqindex++)
    {
        if ((0x01 << irqindex) == index->pin)
        {
            break;
        }
    }
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_err_t es32f3_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                               rt_uint8_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    /* Configure GPIO_InitStructure & EXTI_InitStructure */
    gpio_init_t gpio_initstruct;
    exti_init_t exti_initstruct;
    exti_initstruct.filter = DISABLE;
    exti_initstruct.cks = EXTI_FILTER_CLOCK_10K;
    exti_initstruct.filter_time = 0x0;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        /* pin no. convert to dec no. */
        for (irqindex = 0; irqindex < 16; irqindex++)
        {
            if ((0x01 << irqindex) == index->pin)
            {
                break;
            }
        }
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return -RT_ENOSYS;
        }
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        irqmap = &pin_irq_map[irqindex];
        ald_gpio_exti_init(index->gpio, index->pin, &exti_initstruct);
        /* Configure GPIO_InitStructure */
        gpio_initstruct.mode = GPIO_MODE_INPUT;
        gpio_initstruct.odos = GPIO_PUSH_PULL;
        gpio_initstruct.podrv = GPIO_OUT_DRIVE_6;
        gpio_initstruct.nodrv = GPIO_OUT_DRIVE_6;
        gpio_initstruct.func = GPIO_FUNC_1;
        gpio_initstruct.flt = GPIO_FILTER_DISABLE;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            gpio_initstruct.pupd = GPIO_PUSH_DOWN;
            ald_gpio_exti_interrupt_config(index->pin, EXTI_TRIGGER_RISING_EDGE, ENABLE);
            break;
        case PIN_IRQ_MODE_FALLING:
            gpio_initstruct.pupd = GPIO_PUSH_UP;
            ald_gpio_exti_interrupt_config(index->pin, EXTI_TRIGGER_TRAILING_EDGE, ENABLE);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            gpio_initstruct.pupd = GPIO_FLOATING;
            ald_gpio_exti_interrupt_config(index->pin, EXTI_TRIGGER_BOTH_EDGE, ENABLE);
            break;
        }
        ald_gpio_init(index->gpio, index->pin, &gpio_initstruct);
        NVIC_EnableIRQ(irqmap->irqno);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }
        NVIC_DisableIRQ(irqmap->irqno);
    }
    else
    {
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _es32f3_pin_ops =
{
    es32f3_pin_mode,
    es32f3_pin_write,
    es32f3_pin_read,
    es32f3_pin_attach_irq,
    es32f3_pin_detach_irq,
    es32f3_pin_irq_enable,
    /*RT_NULL,*/
};

rt_inline void pin_irq_hdr(uint16_t GPIO_Pin)
{
    uint16_t irqno;
    /* pin no. convert to dec no. */
    for (irqno = 0; irqno < 16; irqno++)
    {
        if ((0x01 << irqno) == GPIO_Pin)
        {
            break;
        }
    }
    if (irqno == 16)
        return;
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (ald_gpio_exti_get_flag_status(GPIO_Pin) != RESET)
    {
        ald_gpio_exti_clear_flag_status(GPIO_Pin);
        pin_irq_hdr(GPIO_Pin);
    }
}

void EXTI0_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_0);
    rt_interrupt_leave();
}

void EXTI1_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_1);
    rt_interrupt_leave();
}

void EXTI2_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_2);
    rt_interrupt_leave();
}

void EXTI3_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_3);
    rt_interrupt_leave();
}

void EXTI4_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_4);
    rt_interrupt_leave();
}

void EXTI5_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_5);
    rt_interrupt_leave();
}

void EXTI6_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_6);
    rt_interrupt_leave();
}

void EXTI7_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_7);
    rt_interrupt_leave();
}

void EXTI8_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_8);
    rt_interrupt_leave();
}

void EXTI9_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_9);
    rt_interrupt_leave();
}

void EXTI10_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_10);
    rt_interrupt_leave();
}

void EXTI11_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_11);
    rt_interrupt_leave();
}

void EXTI12_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_12);
    rt_interrupt_leave();
}

void EXTI13_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_13);
    rt_interrupt_leave();
}

void EXTI14_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_14);
    rt_interrupt_leave();
}

void EXTI15_Handler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(GPIO_PIN_15);
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
    int result;


#ifdef   ES_INIT_GPIOS

    rt_size_t i,gpio_conf_num = sizeof(gpio_conf_all) / sizeof(gpio_conf_t);

#endif

    ald_cmu_perh_clock_config(CMU_PERH_GPIO, ENABLE);

    result = rt_device_pin_register(ES_DEVICE_NAME_PIN, &_es32f3_pin_ops, RT_NULL);

    if(result != RT_EOK)return result;

#ifdef   ES_INIT_GPIOS

       for(i = 0;i < gpio_conf_num;i++)
    {
        rt_pin_mode( gpio_conf_all[i].pin,gpio_conf_all[i].pin_mode);

        if((gpio_conf_all[i].pin_mode == ES_C_GPIO_MODE_OUTPUT)||(gpio_conf_all[i].pin_mode == ES_C_GPIO_MODE_OUTPUT_OD))
        rt_pin_write(gpio_conf_all[i].pin,gpio_conf_all[i].pin_level);

        if(!gpio_conf_all[i].irq_en)continue;

        rt_pin_attach_irq(gpio_conf_all[i].pin, gpio_conf_all[i].irq_mode, gpio_conf_all[i].callback, RT_NULL);
        rt_pin_irq_enable(gpio_conf_all[i].pin, gpio_conf_all[i].irq_en);
    }

#endif



    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif
