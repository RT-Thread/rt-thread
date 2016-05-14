/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef SSI_H_
#define SSI_H_
#include "libraries/inc/fh_driverlib.h"
#include <drivers/spi.h>
#include <rtdevice.h>
#include "fh_dma.h"
#define SPI_PRIV(drv)   ( (struct fh_spi_obj)(drv->priv) )

#define FH_SPI_SLAVE_MAX_NO			2

struct spi_controller;
//platform use below
struct spi_slave_platform_data{

	rt_uint32_t cs_pin;
#define ACTIVE_LOW			1
#define ACTIVE_HIGH			2
	rt_uint32_t actice_level;
};


struct spi_control_platform_data{
	rt_uint32_t id;
	rt_uint32_t irq;
	rt_uint32_t base;
	rt_uint32_t max_hz;
	rt_uint32_t slave_no;
	rt_uint32_t clk_in;
	//handshake no...
	rt_uint32_t rx_hs_no;
	rt_uint32_t tx_hs_no;

	char *dma_name;
	//isr will be the default...
#define USE_ISR_TRANSFER			0
#define USE_DMA_TRANSFER			1
	rt_uint32_t transfer_mode;
	struct spi_controller *control;
	struct spi_slave_platform_data plat_slave[FH_SPI_SLAVE_MAX_NO];

};


struct spi_controller;
//driver use below.......
struct spi_slave_info
{
    struct rt_spi_device spi_device;
    struct spi_controller *control;
    struct spi_slave_platform_data plat_slave;
    rt_uint32_t id;
    //spi control will use to find all the slave info..
    struct spi_slave_info *next;
};

struct spi_dma
{
	char *dma_name;
#define DMA_BIND_OK			0
#define DMA_BIND_ERROR		1
	rt_uint32_t dma_flag;
    //bind to the dma dev..
	rt_uint32_t rx_hs;
	rt_uint32_t tx_hs;
	rt_uint8_t *rx_dummy_buff;
	rt_uint8_t *tx_dummy_buff;
    struct rt_dma_device *dma_dev;
    struct dma_transfer tx_trans;
    struct dma_transfer rx_trans;
    struct spi_controller *control;
};

struct spi_controller
{
	rt_uint32_t id;
	rt_uint32_t irq;
	rt_uint32_t base;
	rt_uint32_t max_hz;
	rt_uint32_t slave_no;
	rt_uint32_t clk_in;
	//bind to the platform data....
	struct spi_control_platform_data *plat_data;

	//rt_uint32_t dma_xfer_flag;

#define XFER_USE_ISR		0
#define XFER_USE_DMA		1
	rt_uint32_t xfer_mode;

	struct spi_dma dma;
	rt_uint32_t dma_complete_times;
    struct rt_spi_bus spi_bus;
    struct spi_slave_info *spi_slave;
    struct rt_spi_message* current_message;
    struct rt_completion transfer_completion;
	struct rt_semaphore xfer_lock;
    struct fh_spi_obj obj;
    rt_uint32_t received_len;
    rt_uint32_t transfered_len;
    void*  priv;
};




void rt_hw_spi_init(void);

#endif /* SPI_H_ */
