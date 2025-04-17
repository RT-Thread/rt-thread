/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-25 14:01:16
 * @LastEditTime: 2021-04-30 14:43:12
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <board.h>
#include <drv_spi.h>
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>
#include "ft_spi.h"

#ifdef BSP_USE_SPI

#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"

static int rt_hw_spi_flash_init(void)
{
    uint16_t cs_pin = 5;
    rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_DEV_NAME, cs_pin);

    rt_kprintf("attach spi flash\r\n");
    /* lookup flah */
    if (RT_NULL == rt_sfud_flash_probe("S25FS256S", SPI_DEV_NAME))
    {
        rt_kprintf("attach spi flash failed\r\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
#endif
