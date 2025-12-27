#ifndef __DRV_TIM_PULSE_WIDTH_H__
#define __DRV_TIM_PULSE_WIDTH_H__


#include <rtdbg.h>
#include <rtdevice.h>

typedef  void (*fun_pulse_callback)(rt_device_t dev, rt_uint32_t pulse_width_us, rt_uint32_t period_us,rt_uint32_t status);


#endif /* __DRV_TIM_PULSE_WIDTH_H__ */
									  
	
