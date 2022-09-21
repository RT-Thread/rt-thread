/*
 * drv_pwm.h
 *
 *  Created on: 2022Äê6ÔÂ10ÈÕ
 *      Author: Felix
 */

#ifndef DRIVERS_DRV_PWM_H_
#define DRIVERS_DRV_PWM_H_
#include "board.h"
#include "rtdevice.h"

int c28x_pwm_init(void);
struct c28x_pwm
{
    struct rt_device_pwm pwm_device;
    volatile struct EPWM_REGS *pwm_regs;
    const char *name;
};

#endif /* DRIVERS_DRV_PWM_H_ */
