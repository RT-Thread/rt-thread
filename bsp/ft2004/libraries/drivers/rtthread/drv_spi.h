/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-25 14:01:39
 * @LastEditTime: 2021-04-29 09:40:13
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */
#ifndef FT_DRIVERS_RTT_SPI_H
#define FT_DRIVERS_RTT_SPI_H

#include <rtthread.h>

#define SPI_BUS_NAME "spi0"
#define SPI_DEV_NAME "S25FS256"

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint16_t cs_gpio_pin);

#ifdef __cplusplus
extern "C"
{
#endif

#endif