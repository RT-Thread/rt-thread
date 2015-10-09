
#include "app_config.h"
#include <rtthread.h>

#include "fsl_os_abstraction.h"
#include "fsl_i2c_hal.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_gpio_driver.h"
#include "fsl_interrupt_manager.h"

#include "fsl_device_registers.h"

static uint32_t s_instance = MPU6050_I2C_INSTANCE;

motor_ch_t motor_demo_config[MOTOR_NUM] = {
#ifdef TWR_K64F120M
  {0, 6, true, 0},
  {0, 7, false, 0},
  {2, 0, true, 0},
  {0, 1, false, 0},
#else
#warn need define the output pin
#endif
};


s_gpio_t motor_gpio[GPIO_NUM] = {
#ifdef TWR_K64F120M
  /* ptd13*/
  {3u, 13u, kPortIntFallingEdge, kPortPullUp},
#else
#warn need define the output pin
#endif
};

void gpio_init(s_gpio_t * pgpio)
{
  
  int i = 0;
  for (i = 0; i < GPIO_NUM ; i++)
  {
    uint32_t gpioInstance = motor_gpio[i].instance;
    uint32_t pinName =  motor_gpio[i].pinnum;
    port_interrupt_config_t int_mode = motor_gpio[i].int_mode;
    port_pull_t pull_mode = motor_gpio[i].pull_mode;
    /* Set current pin as digital Input.*/
    PORT_HAL_SetMuxMode(g_portBase[gpioInstance], pinName, kPortMuxAsGpio);
    GPIO_HAL_SetPinDir(g_gpioBase[gpioInstance], pinName, kGpioDigitalInput);

    /* Configure gpio input features. */
  /* Configure gpio input features. */
    PORT_HAL_SetPullCmd(g_portBase[gpioInstance], pinName, false);
    PORT_HAL_SetPullMode(g_portBase[gpioInstance], pinName, kPortPullUp);
#if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
    PORT_HAL_SetPassiveFilterCmd(g_portBase[gpioInstance], pinName, false);
#endif /* FSL_FEATURE_PORT_HAS_PASSIVE_FILTER */

    /*set pin interrupt mode*/
    PORT_HAL_SetPinIntMode(g_portBase[gpioInstance], pinName, int_mode);
    /* Enable GPIO interrupt.*/
    INT_SYS_EnableIRQ(g_portIrqId[gpioInstance]);
  }
}

void rt_thread_delay_ms(uint32_t t)
{
  rt_thread_delay(RT_TICK_PER_SECOND*t/1000);
}

void rt_get_ms(unsigned long * t)
{
  *t = rt_tick_get() * 1000 / RT_TICK_PER_SECOND;
}

void get_tick_count(unsigned long * ts)
{
  *ts = (unsigned long)rt_tick_get();
}

int Sensors_I2C_WriteRegister(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char const *data)
{
  I2C_Type * baseAddr = g_i2cBase[s_instance];
  I2C_HAL_MasterSendDataPolling(baseAddr, (uint16_t)slave_addr, (const uint8_t * )&reg_addr, 1, (const uint8_t *)data, length);
  return 0;
}

int Sensors_I2C_ReadRegister(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char *data)
{
  i2c_status_t ret;
  I2C_Type * baseAddr = g_i2cBase[s_instance];
  ret = I2C_HAL_MasterReceiveDataPolling(baseAddr, slave_addr, (const uint8_t * )&reg_addr, 1, data, length);
  if (ret == kStatus_I2C_Success)
  {
    return 0;
  } else {
    return -1;
  }  
}

