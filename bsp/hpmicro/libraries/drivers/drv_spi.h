/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DRV_SPI_H
#define DRV_SPI_H

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <stdint.h>


#define SPI_CS_TAKE (0)
#define SPI_CS_RELEASE (1)

typedef void (*cs_ctrl_callback_t)(uint32_t value);

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, cs_ctrl_callback_t callback);

int rt_hw_spi_init(void);



#endif /* DRV_SPI_H */
