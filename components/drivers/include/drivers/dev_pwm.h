/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-07     aozima       the first version
 * 2022-09-24     yuqi         add phase and dead time configuration
 */

#ifndef __DEV_PWM_H__
#define __DEV_PWM_H__

#include <rtthread.h>
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    PWM              PWM
 *
 * @brief       PWM driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include <rtdevice.h>
 *
 * #define PWM_DEV_NAME        "pwm3"  // PWM设备名称
 * #define PWM_DEV_CHANNEL     4       // PWM通道
 *
 * struct rt_device_pwm *pwm_dev;      // PWM设备句柄
 *
 * static int pwm_led_sample(int argc, char *argv[])
 * {
 *     rt_uint32_t period, pulse, dir;
 *
 *     period = 500000;    // 周期为0.5ms，单位为纳秒ns
 *     dir = 1;            // PWM脉冲宽度值的增减方向
 *     pulse = 0;          // PWM脉冲宽度值，单位为纳秒ns
 *
 *     // 查找设备
 *     pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
 *     if (pwm_dev == RT_NULL)
 *     {
 *         rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
 *         return -RT_ERROR;
 *     }
 *
 *     // 设置PWM周期和脉冲宽度默认值
 *     rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
 *     // 使能设备
 *     rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
 *
 *     while (1)
 *     {
 *         rt_thread_mdelay(50);
 *         if (dir)
 *         {
 *             pulse += 5000;      // 从0值开始每次增加5000ns
 *         }
 *         else
 *         {
 *             pulse -= 5000;      // 从最大值开始每次减少5000ns
 *         }
 *         if (pulse >= period)
 *         {
 *             dir = 0;
 *         }
 *         if (0 == pulse)
 *         {
 *             dir = 1;
 *         }
 *
 *         // 设置PWM周期和脉冲宽度
 *         rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
 *     }
 * }
 *
 * MSH_CMD_EXPORT(pwm_led_sample, pwm sample);
 * @endcode
 *
 * @ingroup     Drivers
 */

/*!
 * @addtogroup PWM
 * @{
 */
#define PWM_CMD_ENABLE      (RT_DEVICE_CTRL_BASE(PWM) + 0)
#define PWM_CMD_DISABLE     (RT_DEVICE_CTRL_BASE(PWM) + 1)
#define PWM_CMD_SET         (RT_DEVICE_CTRL_BASE(PWM) + 2)
#define PWM_CMD_GET         (RT_DEVICE_CTRL_BASE(PWM) + 3)
#define PWMN_CMD_ENABLE     (RT_DEVICE_CTRL_BASE(PWM) + 4)
#define PWMN_CMD_DISABLE    (RT_DEVICE_CTRL_BASE(PWM) + 5)
#define PWM_CMD_SET_PERIOD  (RT_DEVICE_CTRL_BASE(PWM) + 6)
#define PWM_CMD_SET_PULSE   (RT_DEVICE_CTRL_BASE(PWM) + 7)
#define PWM_CMD_SET_DEAD_TIME  (RT_DEVICE_CTRL_BASE(PWM) + 8)
#define PWM_CMD_SET_PHASE   (RT_DEVICE_CTRL_BASE(PWM) + 9)
#define PWM_CMD_ENABLE_IRQ  (RT_DEVICE_CTRL_BASE(PWM) + 10)
#define PWM_CMD_DISABLE_IRQ  (RT_DEVICE_CTRL_BASE(PWM) + 11)

/**
 * @brief PWM configuration
 */
struct rt_pwm_configuration
{
    rt_uint32_t channel; /* 0 ~ n or 0 ~ -n, which depends on specific MCU requirements */
    rt_uint32_t period;  /* unit:ns 1ns~4.29s:1Ghz~0.23hz */
    rt_uint32_t pulse;   /* unit:ns (pulse<=period) */
    rt_uint32_t dead_time;  /* unit:ns */
    rt_uint32_t phase;  /*unit: degree, 0~360, which is the phase of pwm output, */
    /*
     * RT_TRUE  : The channel of pwm is complememtary.
     * RT_FALSE : The channel of pwm is nomal.
    */
    rt_bool_t  complementary;
};

struct rt_device_pwm;
/**
 * @brief PWM operations
 */
struct rt_pwm_ops
{
    rt_err_t (*control)(struct rt_device_pwm *device, int cmd, void *arg);
};

/**
 * @brief PWM device
 */
struct rt_device_pwm
{
    struct rt_device parent;
    const struct rt_pwm_ops *ops;
};
/**
 * @brief register a PWM device
 * @param device the PWM device
 * @param name the name of PWM device
 * @param ops the operations of PWM device
 * @param user_data the user data of PWM device
 * @return rt_err_t error code
 */
rt_err_t rt_device_pwm_register(struct rt_device_pwm *device, const char *name, const struct rt_pwm_ops *ops, const void *user_data);

/**
 * @brief enable the PWM channel
 * @param device the PWM device
 * @param channel the channel of PWM
 * @return rt_err_t error code
 */
rt_err_t rt_pwm_enable(struct rt_device_pwm *device, int channel);

/**
 * @brief disable the PWM channel
 * @param device the PWM device
 * @param channel the channel of PWM
 * @return rt_err_t error code
 */
rt_err_t rt_pwm_disable(struct rt_device_pwm *device, int channel);

/**
 * @brief set the PWM channel
 * @param device the PWM device
 * @param channel the channel of PWM
 * @param period the period of PWM
 * @param pulse the pulse of PWM
 * @return rt_err_t error code
 */
rt_err_t rt_pwm_set(struct rt_device_pwm *device, int channel, rt_uint32_t period, rt_uint32_t pulse);

/**
 * @brief set the PWM channel period
 * @param device the PWM device
 * @param channel the channel of PWM
 * @param period the period of PWM
 * @return rt_err_t error code
*/
rt_err_t rt_pwm_set_period(struct rt_device_pwm *device, int channel, rt_uint32_t period);

/**
 * @brief set the PWM channel pulse
 * @param device the PWM device
 * @param channel the channel of PWM
 * @param pulse the period of PWM
 * @return rt_err_t error code
*/
rt_err_t rt_pwm_set_pulse(struct rt_device_pwm *device, int channel, rt_uint32_t pulse);

/**
 * @brief set the dead zone time of PWM
 * @param device the PWM device
 * @param channel the channel of PWM
 * @param dead_time dead zone time
 * @return rt_err_t error code
*/
rt_err_t rt_pwm_set_dead_time(struct rt_device_pwm *device, int channel, rt_uint32_t dead_time);

/**
 * @brief set the phase of PWM
 * @param device the PWM device
 * @param channel the channel of PWM
 * @param phase phase
 * @return rt_err_t error code
*/
rt_err_t rt_pwm_set_phase(struct rt_device_pwm *device, int channel, rt_uint32_t phase);

/*! @}*/

#endif /* __DEV_PWM_H__ */
