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
 
 /*
 * spi_fh_adapt.c
 *
 *  Created on: Mar 2, 2016
 *      Author: duobao
 */


#include <stdint.h>
#include "spi_fh_adapt.h"
#include "board_info.h"

#ifdef RT_USING_W25QXX
#include "spi_flash_w25qxx.h"
#endif

#ifdef RT_USING_AT45DBXX
#include "spi_flash_at45dbxx.h"
#endif

#ifdef RT_USING_SST25VFXX
#include "spi_flash_sst25vfxx.h"
#endif

#ifdef RT_USING_GD
#include "spi_flash_gd.h"
#endif


#ifdef RT_USING_FLASH_DEFAULT
#include "spi_flash_default.h"
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


#define WX_MANU_ID		0xEF
#define AT_MANU_ID      0x1F /* atmel */
#define SST_MANU_ID		0xBF
#define GD_MANU_ID      0xC8



#define SPI_ADAPT_DEBUG
#ifdef SPI_ADAPT_DEBUG

#define CMD_JEDEC_ID 			0x9f


#define FH_SPI_ADAPT_DEBUG(fmt, args...)	    		\
			rt_kprintf(fmt,##args);
#else
#define FH_SPI_ADAPT_DEBUG(fmt, args...)
#endif
struct fh_flash_id{
	unsigned char id;
	rt_err_t (*fh_flash_init)(struct flash_platform_data *plat_flash);
	char *name;
};
const struct fh_flash_id id_map[] = {

#ifdef RT_USING_W25QXX
		WX_MANU_ID,w25qxx_init,"winbond",
#endif

#ifdef RT_USING_AT45DBXX
		AT_MANU_ID,at45dbxx_init,"atmel",
#endif

#ifdef RT_USING_SST25VFXX
		SST_MANU_ID,sst25vfxx_init,"SST",
#endif

#ifdef RT_USING_GD
		GD_MANU_ID,gd_init,"GD",
#endif

};


struct fh_flash_id * fh_flash_check_id_map(unsigned char id){
	struct fh_flash_id *p_map = RT_NULL;
	unsigned int i;
	for (i = 0; i < ARRAY_SIZE(id_map); i++) {
		p_map = (struct fh_flash_id *)&id_map[i];
		if (p_map->id == id){
			return p_map;
		}
	}
	return RT_NULL;
}


int fh_flash_adapt_probe(void *priv_data)
{
    struct flash_platform_data *plat_flash = priv_data;
    const char * flash_device_name = plat_flash->flash_name;
    const char * spi_device_name = plat_flash->spi_name;
    struct rt_spi_device * rt_spi_device;
    struct fh_flash_id * flash_model;

    rt_spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if(rt_spi_device == RT_NULL)
    {
        rt_kprintf("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }


    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
        cfg.max_hz = 50 * 1000 * 1000; /* 50M */
        rt_spi_configure(rt_spi_device, &cfg);
    }

    /* init flash */

	rt_uint8_t cmd;
	rt_uint8_t id_recv[3];
	uint16_t memory_type_capacity;
	rt_err_t ret;

	cmd = 0xFF; /* reset SPI FLASH, cancel all cmd in processing. */
	rt_spi_send(rt_spi_device, &cmd, 1);
	/* read flash id */
	cmd = CMD_JEDEC_ID;
	rt_spi_send_then_recv(rt_spi_device, &cmd, 1, id_recv, 3);

	//if the flash is already connect.
	if(id_recv[0] != 0xff){
		flash_model =fh_flash_check_id_map(id_recv[0]);
		if(flash_model){
			ret = flash_model->fh_flash_init(plat_flash);
			if(ret != RT_EOK){
				rt_kprintf("flash:%s init error\n",flash_model->name);
				rt_kprintf("use default flash ops..\n");
				//flash_model->fh_flash_adapt_init =flash_default_init;
				ret = flash_default_init(plat_flash);
			}
		}
		else{
			rt_kprintf(
					"use default flash ops...\nunrecognized flash id is :%02X %02X %02X\n",
					id_recv[0], id_recv[1], id_recv[2]);
			ret = flash_default_init(plat_flash);

		}

		int i;
		for(i=0; i<plat_flash->nr_parts; i++)
		{
		    fh_spi_partition_register(plat_flash->flash_name, &plat_flash->parts[i]);
		}

		return ret;

	}
	else{
		rt_kprintf("please check if you connect the flash already...\n");
		return RT_ENOSYS;
	}


}

int fh_flash_adapt_exit(void *priv_data)
{
    return 0;
}

struct fh_board_ops flash_driver_ops =
{

        .probe = fh_flash_adapt_probe,
        .exit = fh_flash_adapt_exit,

};

rt_err_t fh_flash_adapt_init(void)
{
    fh_board_driver_register("fh_flash", &flash_driver_ops);
    return 0;
}
