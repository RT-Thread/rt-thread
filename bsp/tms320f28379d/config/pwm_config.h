/*
 * pwm_config.h
 *
 *  Created on: 2022Äê6ÔÂ11ÈÕ
 *      Author: Felix
 */

#ifndef DRIVERS_CONFIG_PWM_CONFIG_H_
#define DRIVERS_CONFIG_PWM_CONFIG_H_
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2837xD_epwm.h"
#include "rtthread.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef BSP_USING_PWM1
#ifndef PWM1_CONFIG
#define PWM1_CONFIG                             \
{                                           \
    .name = "pwm1",                         \
    .pwm_regs   = EPwm1Regs,                \
}
#endif
#endif



#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_CONFIG_PWM_CONFIG_H_ */

