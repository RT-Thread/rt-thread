

#include <rtthread.h>
#include <rtdevice.h>
#include "rtconfig.h"

#if defined BSP_USING_CAN
rt_err_t can_loopback_sample();
#endif
#if defined BSP_USING_GPIO
rt_err_t gpio_toggle_sample();
#endif
#if defined BSP_USING_I2C
rt_err_t i2c_sample();
#endif
#if defined BSP_USING_SPI
rt_err_t fspim_test_sample();
#endif
#if defined BSP_USING_QSPI
rt_err_t qspi_sample();
#endif

