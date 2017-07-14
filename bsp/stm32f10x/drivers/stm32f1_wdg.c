/*
 * File      : stm32f1_wdg.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author                Notes
 * 2017-01-18     aubrcool@qq.com       1st version
 */
#include "stm32f10x.h"
#include <rtdevice.h>

#ifdef RT_USING_WDT

static rt_err_t stm32f1_wdg_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}
static rt_err_t stm32f1_wdg_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
     rt_uint32_t timeout_ms = 0;
     rt_uint32_t timeout_pow = 1;
     switch(cmd)
     {
     case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
          timeout_ms = (rt_uint32_t) arg;
          IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
          if(timeout_ms >= 13107)
          {
              if(timeout_ms >= 26214)
              {
                  timeout_ms = 26214;
              }
              IWDG_SetPrescaler(IWDG_Prescaler_256);
              timeout_pow = 256;
          }
          else if(timeout_ms >= 6553)
          {
              IWDG_SetPrescaler(IWDG_Prescaler_128);
              timeout_pow = 128;
          }
          else if(timeout_ms >= 3276)
          {
              IWDG_SetPrescaler(IWDG_Prescaler_64);
              timeout_pow = 64;
          }
          else if(timeout_ms >= 1638)
          {
              IWDG_SetPrescaler(IWDG_Prescaler_32);
              timeout_pow = 32;
          }
          else if(timeout_ms >= 819)
          {
              IWDG_SetPrescaler(IWDG_Prescaler_16);
              timeout_pow = 16;
          }
          else if(timeout_ms >= 409)
          {
              IWDG_SetPrescaler(IWDG_Prescaler_8);
              timeout_pow = 8;
          }
          else
          {
              IWDG_SetPrescaler(IWDG_Prescaler_4);
              timeout_pow = 4;
          }
          timeout_ms = timeout_ms * 40 / timeout_pow;
          if(timeout_ms > 0xFFF)
          {
              timeout_ms = 0xFFF;
          }
          IWDG_SetReload(timeout_ms);
          IWDG_ReloadCounter();
       break;
     case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
          timeout_pow = IWDG->PR;
          if(timeout_pow > 6)
          {
               timeout_pow = 6;
          }
          timeout_pow = 1 << (2 + timeout_pow);
          timeout_ms = IWDG->RLR;
          timeout_ms &= 0xFFF;
          *((rt_uint32_t *) arg) = timeout_ms * timeout_pow / 40;
       break;
     case RT_DEVICE_CTRL_WDT_KEEPALIVE:
          IWDG_ReloadCounter();
       break;
     case RT_DEVICE_CTRL_WDT_START:
          IWDG_Enable();
       break;
     default:
       return RT_EIO;
     }
     return RT_EOK;
}

static const struct rt_watchdog_ops stm32f1_wdg_pos =
{
     stm32f1_wdg_init,
     stm32f1_wdg_control,
};
static rt_watchdog_t stm32f1_wdg;

int rt_hw_wdg_init(void)
{
    stm32f1_wdg.ops = &stm32f1_wdg_pos;
    rt_hw_watchdog_register(&stm32f1_wdg, "wdg",  0, RT_NULL);
    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_wdg_init);

#endif /*RT_USING_WDT*/
