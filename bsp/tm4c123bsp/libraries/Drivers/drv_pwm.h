#ifndef _DRV_PWM_H_
#define _DRV_PWM_H_


#include<rtdevice.h>
#include<rthw.h>


struct tm4c123_pwm
{
	struct tm4c123_pwm_config *config;
	struct rt_device_pwm  pwm_device;
};

/* tm4c123 config class */
struct tm4c123_pwm_config
{
	rt_uint8_t channel;
	char *name;
	uint32_t   counterMode;
	uint32_t   syncMode;
};


int rt_hw_pwm_init(void);


#endif /*_DRV_PWM_H_*/
