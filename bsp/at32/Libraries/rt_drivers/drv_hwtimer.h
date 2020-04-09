/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-16     Leo          first version
 */

#ifndef __TMR_CONFIG_H__
#define __TMR_CONFIG_H__

#include <rtthread.h>
#include <drivers/hwtimer.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TMR_DEV_INFO_CONFIG
#define TMR_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 1000000,                     \
        .minfreq = 4000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */  

#ifdef BSP_USING_HWTMR2
#ifndef TMR2_CONFIG
#define TMR2_CONFIG                   \
    {                                 \
       .tim_handle    = TMR2,         \
       .tim_irqn      = TMR2_GLOBAL_IRQn, \
       .name          = "timer2",     \
    }
#endif /* TMR2_CONFIG */  
#endif /* BSP_USING_HWTMR2 */ 
  
#ifdef BSP_USING_HWTMR3
#ifndef TMR3_CONFIG
#define TMR3_CONFIG                   \
    {                                 \
       .tim_handle    = TMR3,         \
       .tim_irqn      = TMR3_GLOBAL_IRQn, \
       .name          = "timer3",     \
    }
#endif /* TMR3_CONFIG */  
#endif /* BSP_USING_HWTMR3 */  

#ifdef BSP_USING_HWTMR4
#ifndef TMR4_CONFIG
#define TMR4_CONFIG                   \
    {                                 \
       .tim_handle    = TMR4,         \
       .tim_irqn      = TMR4_GLOBAL_IRQn, \
       .name          = "timer4",     \
    }
#endif /* TMR4_CONFIG */  
#endif /* BSP_USING_HWTMR4 */
    
#ifdef BSP_USING_HWTMR5
#ifndef TMR5_CONFIG
#define TMR5_CONFIG                   \
    {                                 \
       .tim_handle    = TMR5,         \
       .tim_irqn      = TMR5_GLOBAL_IRQn, \
       .name          = "timer5",     \
    }
#endif /* TMR5_CONFIG */  
#endif /* BSP_USING_HWTMR5 */    
    
#ifdef __cplusplus
}
#endif

#endif /* __TMR_CONFIG_H__ */

