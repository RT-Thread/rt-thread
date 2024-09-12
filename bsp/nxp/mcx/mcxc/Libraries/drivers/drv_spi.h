#ifndef DRV_SPI_H
#define DRV_SPI_H


#include <rtthread.h>
#include <rtdevice.h>

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin);
int rt_hw_spi_init(void);

#endif //DRV_SPI_H
