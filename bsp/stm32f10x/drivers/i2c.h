#ifndef __I2C_SOFT_INIT_H__
#define __I2C_SOFT_INIT_H__

#include <rtthread.h>
#include <rtdevice.h>

#define I2C1_GPIO 		GPIOB
#define I2C1_GPIO_SCL 	GPIO_Pin_6
#define I2C1_GPIO_SDA 	GPIO_Pin_7
#define RCC_I2C 		RCC_APB2Periph_GPIOB

int rt_hw_i2c_init(void);

void stm32_set_sda(void *data, rt_int32_t state);
void stm32_set_scl(void *data, rt_int32_t state);
rt_int32_t stm32_get_sda(void *data);
rt_int32_t stm32_get_scl(void *data);

void stm32_udelay(rt_uint32_t us);
void stm32_mdelay(rt_uint32_t ms);

static void RCC_Configuration(void);
static void GPIO_Configuration(void);

#endif
