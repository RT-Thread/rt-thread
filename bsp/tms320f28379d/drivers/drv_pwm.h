/*
 * drv_pwm.h
 *
 *  Created on: 2022-9-21
 *      Author: Felix
 */

#ifndef DRIVERS_DRV_PWM_H_
#define DRIVERS_DRV_PWM_H_
#include <board.h>
#include "rtdevice.h"

struct c28x_pwm
{
    struct rt_device_pwm pwm_device;
    volatile struct EPWM_REGS *pwm_regs;
    const char *name;
};

int c28x_pwm_init(void);

#endif /* DRIVERS_DRV_PWM_H_ */
