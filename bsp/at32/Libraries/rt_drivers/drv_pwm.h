/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-1-13      Leo          first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>
#include <drivers/rt_drv_pwm.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_TMR1_CH1
#ifndef PWM1_CONFIG
#define PWM1_CONFIG              \
  {                              \
    .tim_handle   = TMR1,        \
    .name         = "tmr1pwm1",  \
    .channel      = 1            \
  }
#endif /* PWM1_CONFIG */
#endif /* BSP_USING_TMR1_CH1 */
  
#ifdef BSP_USING_TMR1_CH2
#ifndef PWM2_CONFIG
#define PWM2_CONFIG              \
  {                              \
    .tim_handle   = TMR1,        \
    .name         = "tmr1pwm2",  \
    .channel      = 2            \
  }
#endif /* PWM2_CONFIG */
#endif /* BSP_USING_TMR1_CH2 */

#ifdef BSP_USING_TMR1_CH3
#ifndef PWM3_CONFIG
#define PWM3_CONFIG              \
  {                              \
    .tim_handle   = TMR1,        \
    .name         = "tmr1pwm3",  \
    .channel      = 3            \
  }
#endif /* PWM3_CONFIG */
#endif /* BSP_USING_TMR1_CH3 */

#ifdef BSP_USING_TMR1_CH4
#ifndef PWM4_CONFIG
#define PWM4_CONFIG              \
  {                              \
    .tim_handle   = TMR1,        \
    .name         = "tmr1pwm4",  \
    .channel      = 4            \
  }
#endif /* PWM4_CONFIG */
#endif /* BSP_USING_TMR1_CH4 */

#ifdef BSP_USING_TMR2_CH1
#ifndef PWM5_CONFIG
#define PWM5_CONFIG              \
  {                              \
    .tim_handle   = TMR2,        \
    .name         = "tmr2pwm1",  \
    .channel      = 1            \
  }
#endif /* PWM5_CONFIG */
#endif /* BSP_USING_TMR2_CH1 */
  
#ifdef BSP_USING_TMR2_CH2
#ifndef PWM6_CONFIG
#define PWM6_CONFIG              \
  {                              \
    .tim_handle   = TMR2,        \
    .name         = "tmr2pwm2",  \
    .channel      = 2            \
  }
#endif /* PWM6_CONFIG */
#endif /* BSP_USING_TMR2_CH2 */  
  
#ifdef BSP_USING_TMR2_CH3
#ifndef PWM7_CONFIG
#define PWM7_CONFIG              \
  {                              \
    .tim_handle   = TMR2,        \
    .name         = "tmr2pwm3",  \
    .channel      = 3            \
  }
#endif /* PWM7_CONFIG */
#endif /* BSP_USING_TMR2_CH3 */  

#ifdef BSP_USING_TMR2_CH4
#ifndef PWM8_CONFIG
#define PWM8_CONFIG              \
  {                              \
    .tim_handle   = TMR2,        \
    .name         = "tmr2pwm4",  \
    .channel      = 4            \
  }
#endif /* PWM8_CONFIG */
#endif /* BSP_USING_TMR2_CH4 */

#ifdef BSP_USING_TMR3_CH1
#ifndef PWM9_CONFIG
#define PWM9_CONFIG              \
  {                              \
    .tim_handle   = TMR3,        \
    .name         = "tmr3pwm1",  \
    .channel      = 1            \
  }
#endif /* PWM9_CONFIG */
#endif /* BSP_USING_TMR3_CH1 */   

#ifdef BSP_USING_TMR3_CH2
#ifndef PWM10_CONFIG
#define PWM10_CONFIG             \
  {                              \
    .tim_handle   = TMR3,        \
    .name         = "tmr3pwm2",  \
    .channel      = 2            \
  }
#endif /* PWM10_CONFIG */
#endif /* BSP_USING_TMR3_CH2 */

#ifdef BSP_USING_TMR3_CH3
#ifndef PWM11_CONFIG
#define PWM11_CONFIG             \
  {                              \
    .tim_handle   = TMR3,        \
    .name         = "tmr3pwm3",  \
    .channel      = 3            \
  }
#endif /* PWM11_CONFIG */
#endif /* BSP_USING_TMR3_CH3 */

#ifdef BSP_USING_TMR3_CH4
#ifndef PWM12_CONFIG
#define PWM12_CONFIG             \
  {                              \
    .tim_handle   = TMR3,        \
    .name         = "tmr3pwm4",  \
    .channel      = 4            \
  }
#endif /* PWM12_CONFIG */
#endif /* BSP_USING_TMR3_CH4 */
  
#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
