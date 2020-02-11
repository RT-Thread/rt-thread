/*
 * File      : drv_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-10-10     JQ            the first version
 */
#include "board.h"
#include "rt_nrf_gpio.h"

#include "nrf_drv_common.h"
#include "app_util_platform.h"
#include "nrf_drv_gpiote.h"
#include "nrf_gpio.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "nrf_bitmask.h"


static void _nrf_pin_mode(struct rt_device *device, rt_base_t pin, rt_base_t mode)
{
    switch(mode)
    {
      case PIN_MODE_OUTPUT:
      {
         /* output setting */
         nrf_gpio_cfg_output(pin);
      }
      break;

      case PIN_MODE_INPUT:         
      {
         /* input setting: not pull. */
         nrf_gpio_cfg_input(pin,NRF_GPIO_PIN_NOPULL);
      }
      break;

      case PIN_MODE_INPUT_PULLUP:
      {
         /* input setting: pull up. */
         nrf_gpio_cfg_input(pin,NRF_GPIO_PIN_PULLUP);
      }
      break;

      case PIN_MODE_INPUT_PULLDOWN:
      {
         /* input setting: pull up. */
         nrf_gpio_cfg_input(pin,NRF_GPIO_PIN_PULLDOWN);
      }
      break;

      case PIN_MODE_OUTPUT_OD:    
      {
        /* output setting: od. */
      }
      break;

      default:
      break;
   }   
}

static void _nrf_pin_write(struct rt_device *device, rt_base_t pin, rt_base_t value)
{
    nrf_gpio_pin_write(pin,value);
}

static int _nrf_pin_read(struct rt_device *device, rt_base_t pin)
{
   return nrf_gpio_pin_read(pin);
}

struct rt_pin_irq_hdr pin_irq_hdr_tab[P0_PIN_NUM+P1_PIN_NUM] =
{
    /*P0*/
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

    /*P1*/
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

static rt_err_t _nrf_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                           rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t pinindex = pin;

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[pinindex].pin == pin &&
            pin_irq_hdr_tab[pinindex].hdr == hdr &&
            pin_irq_hdr_tab[pinindex].mode == mode &&
            pin_irq_hdr_tab[pinindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[pinindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EBUSY;
    }
    pin_irq_hdr_tab[pinindex].pin = pin;
    pin_irq_hdr_tab[pinindex].hdr = hdr;
    pin_irq_hdr_tab[pinindex].mode = mode;
    pin_irq_hdr_tab[pinindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _nrf_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int32_t pinindex = pin;

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[pinindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[pinindex].pin = -1;
    pin_irq_hdr_tab[pinindex].hdr = RT_NULL;
    pin_irq_hdr_tab[pinindex].mode = 0;
    pin_irq_hdr_tab[pinindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _nrf_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    rt_base_t level;
    rt_int32_t pinindex = pin;
    nrf_gpio_pin_sense_t sense;
    nrf_gpio_pin_pull_t config; 
    if (enabled == PIN_IRQ_ENABLE)
    {     
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[pinindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ENOSYS;
        }

        switch ((pin_irq_hdr_tab[pinindex].mode) & 0x03)		// >>  RT_GPIO_POLARITY_Pos
        {
           case NRF_GPIOTE_POLARITY_HITOLO:
               sense = NRF_GPIO_PIN_SENSE_LOW;
               config = NRF_GPIO_PIN_PULLUP;
               break;
           case NRF_GPIOTE_POLARITY_LOTOHI:
               sense = NRF_GPIO_PIN_SENSE_HIGH;
               config = NRF_GPIO_PIN_PULLDOWN;
               break;
           case NRF_GPIOTE_POLARITY_TOGGLE:
               /* read current pin state and set for next sense to oposit */
               sense = (nrf_gpio_pin_read(pin)) ? NRF_GPIO_PIN_SENSE_LOW : NRF_GPIO_PIN_SENSE_HIGH;
               config = (sense == NRF_GPIO_PIN_SENSE_LOW)?NRF_GPIO_PIN_PULLUP:NRF_GPIO_PIN_PULLDOWN;
               break;
           default:
               break;
        }
        nrf_gpio_cfg_sense_input(pin,config,sense);
        NVIC_SetPriority(GPIOTE_IRQn, 5);
        NVIC_EnableIRQ(GPIOTE_IRQn);
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_PORT);
        nrf_gpiote_int_enable(GPIOTE_INTENSET_PORT_Msk);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_PORT);
        nrf_gpiote_int_disable((uint32_t)NRF_GPIOTE_INT_PORT_MASK);
        NVIC_DisableIRQ(GPIOTE_IRQn);
    }
    else
    {
        return RT_ENOSYS;
    }

    return RT_EOK;
}

const static struct rt_pin_ops _nrf_pin_ops =
{
   _nrf_pin_mode,
   _nrf_pin_write,
   _nrf_pin_read,
   _nrf_pin_attach_irq,
   _nrf_pin_detach_irq,
   _nrf_pin_irq_enable
};

int rt_hw_pin_init(void)
{
   int ret = RT_EOK;
   ret = rt_device_pin_register("nrfpin", &_nrf_pin_ops, RT_NULL);
   return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

typedef void (*rt_evt_handler_t)(void *args);
void nrfx_gpiote_irq_handler(void)
{
    uint8_t i;
    uint32_t status            = 0;
    uint32_t input[GPIO_COUNT] = {0};  //得到所有引脚的输入状态

    /* collect PORT status event, if event is set read pins state. Processing is postponed to the
     * end of interrupt. */
    if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_PORT))   //是否是   port事件
    {
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_PORT);  //清事件
        status |= (uint32_t)NRF_GPIOTE_INT_PORT_MASK;
        nrf_gpio_ports_read(0, GPIO_COUNT, input);//得到所有引脚的输入状态
    }

    if (status & (uint32_t)NRF_GPIOTE_INT_PORT_MASK)   //port中断
    {
        /* Process port event. */
        uint32_t port_idx;  //共有 2个    port
        uint8_t  repeat                  = 0;
        uint32_t toggle_mask[GPIO_COUNT] = {0};
        uint32_t pins_to_check[GPIO_COUNT];

        // Faster way of doing memset because in interrupt context.
        for (port_idx = 0; port_idx < GPIO_COUNT; port_idx++)
        {
            pins_to_check[port_idx] = 0xFFFFFFFF;
        }

        do
        {
            repeat = 0;

            for (i = 0; i < P0_PIN_NUM+P1_PIN_NUM; i++)  //所有的引脚进行遍历
            {
                uint8_t           polarity_and_sense = (uint8_t)pin_irq_hdr_tab[i].mode;   //得到   i 号数组中存放的极性和 采样的触发条件
                int16_t  pin           = pin_irq_hdr_tab[i].pin;   //得到引脚     带    port和 pin

                if (pin != -1 && nrf_bitmask_bit_is_set(pin, pins_to_check))   //pin  是否置位了      刚开始      pins_to_check是 0 xffffffff 所以一定都置位了       这里的作用是边沿触发时需要
                {
                    nrf_gpiote_polarity_t polarity = (nrf_gpiote_polarity_t)((polarity_and_sense >> RT_GPIO_POLARITY_Pos) & 0x03);  //得到极性
                    rt_evt_handler_t handler =  pin_irq_hdr_tab[i].hdr;   //得到回调
                    if (handler || (polarity == NRF_GPIOTE_POLARITY_TOGGLE))  //如果有回调或者极性是边沿触发
                    {
                        if (polarity == NRF_GPIOTE_POLARITY_TOGGLE)
                        {
                            nrf_bitmask_bit_set(pin, toggle_mask);  //设置这个引脚为边沿触发
                        }
                        nrf_gpio_pin_sense_t sense     = nrf_gpio_pin_sense_get(pin);   //得到配置中的极性配置
                        uint32_t             pin_state = nrf_bitmask_bit_is_set(pin, input);  //引脚的状态
                        if ((pin_state && (sense == NRF_GPIO_PIN_SENSE_HIGH)) ||  //如果输入是1并且引脚的极性配置是上升沿 那么就是这个引脚产生了中断
                            (!pin_state && (sense == NRF_GPIO_PIN_SENSE_LOW))  ) //如果输入是0并且引脚的极性配置是下降沿 那么就是这个引脚产生了中断
                        {
														rt_kprintf("PORT event for pin: %d, polarity: %d.", pin, polarity);
                            if (polarity == NRF_GPIOTE_POLARITY_TOGGLE)
                            {
                                nrf_gpio_pin_sense_t next_sense =
                                    (sense == NRF_GPIO_PIN_SENSE_HIGH) ?
                                    NRF_GPIO_PIN_SENSE_LOW :
                                    NRF_GPIO_PIN_SENSE_HIGH;
                                nrf_gpio_cfg_sense_set(pin, next_sense);
                                ++repeat;
                            }
                            if (handler)
                            {
                                uint32_t args = polarity<<6|pin;
                                handler((void*)args);
                            }
                        }
                    }
                }
            }

            if (repeat)
            {
                // When one of the pins in low-accuracy and toggle mode becomes active,
                // it's sense mode is inverted to clear the internal SENSE signal.
                // State of any other enabled low-accuracy input in toggle mode must be checked
                // explicitly, because it does not trigger the interrput when SENSE signal is active.
                // For more information about SENSE functionality, refer to Product Specification.

                uint32_t new_input[GPIO_COUNT];
                bool     input_unchanged = true;
                nrf_gpio_ports_read(0, GPIO_COUNT, new_input);

                // Faster way of doing memcmp because in interrupt context.
                for (port_idx = 0; port_idx < GPIO_COUNT; port_idx++)
                {
                    if (new_input[port_idx] != input[port_idx])
                    {
                        input_unchanged = false;
                        break;
                    }
                }

                if (input_unchanged)
                {
                    // No change.
                    repeat = 0;
                }
                else
                {
                    // Faster way of doing memcpy because in interrupt context.
                    for (port_idx = 0; port_idx < GPIO_COUNT; port_idx++)
                    {
                        input[port_idx]         = new_input[port_idx];
                        pins_to_check[port_idx] = toggle_mask[port_idx];
                    }
                }
            }
        }
        while (repeat);
    }
}



