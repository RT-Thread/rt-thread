
#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <board.h>
#include <rtthread.h>
#include "fsl_debug_console.h"

#define MPU6050_I2C_INSTANCE (0u)

#define fputc debug_putchar

typedef struct MOTOR_CH_S {
  uint8_t instance;
  uint8_t channel;
  bool need_init;
  uint8_t reserved;
} motor_ch_t;

typedef struct GPIO_ARRAY {
  uint32_t instance;
  uint32_t pinnum;
  port_interrupt_config_t int_mode;
  port_pull_t pull_mode;
} s_gpio_t;

#define MOTOR_NUM 4
#define GPIO_NUM 1
extern motor_ch_t motor_demo_config[MOTOR_NUM];
extern s_gpio_t motor_gpio[GPIO_NUM];

void gpio_init(s_gpio_t * pgpio);

int register_gpio_cb(void (*cb)(void), unsigned char port, unsigned char pin);

void rt_thread_delay_ms(uint32_t t);

void rt_get_ms(unsigned long *);

int mpl_function(void);

void get_tick_count(unsigned long * ts);

/* i2c_write(unsigned char slave_addr, unsigned char reg_addr,
 *      unsigned char length, unsigned char const *data)
 * i2c_read(unsigned char slave_addr, unsigned char reg_addr,
 *      unsigned char length, unsigned char *data)
*/
int Sensors_I2C_WriteRegister(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char const *data);
int Sensors_I2C_ReadRegister(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char *data); 

#endif

