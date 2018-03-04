#ifndef SSI_H_
#define SSI_H_

#include "gtypes.h"
#include <rtdevice.h>

#define MAX_SLAVE_DEVICE (2)

struct gk_spi_slave_info
{
    rt_uint32_t id;	
	rt_uint32_t cs_pin;
	GD_HANDLE spihandle;
	
    struct rt_spi_device spi_device;
    struct gk_spi_controller *control;
    struct gk_spi_slave_info *next;
};

struct gk_spi_controller;
struct gk_spi_controller_data
{
    rt_uint32_t id;
    rt_uint32_t total_slave;
    rt_uint32_t slave_cs_pin[MAX_SLAVE_DEVICE];
	struct gk_spi_controller *control;
};

struct gk_spi_controller
{
    rt_uint32_t id;
    struct rt_spi_bus spi_bus;
    struct rt_spi_message *current_message;
    struct rt_completion transfer_completion;
    struct rt_semaphore xfer_lock;
	
	struct gk_spi_slave_info *spi_slave;

};

void rt_hw_spi_init(void);

#endif
