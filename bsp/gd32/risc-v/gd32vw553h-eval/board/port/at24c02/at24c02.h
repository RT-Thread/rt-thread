#ifndef AT24C02_H
#define AT24C02_H

#include <rtthread.h>
#include "at24cxx.h"

#define AT24C02_I2C_NAME "i2c0"
#define AT24C02_ADDR_INPUT  0x0

#ifdef BSP_USING_AT24C02_INIT
extern at24cxx_device_t gd32_at24c02;
#endif // BSP_USING_AT24C02_INIT

#endif // AT24C02_H