#pragma once

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>



extern int stm32_spi_register_bus(SPI_TypeDef * SPIx,const char * name);
extern rt_err_t stm32_spi_bus_attach_device(rt_uint32_t pin,const char * bus_name,const char * device_name);
extern int stm32_hw_spi_init(void);












