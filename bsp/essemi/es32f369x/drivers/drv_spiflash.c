/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-02-15     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include "board.h"
#include <rtthread.h>

#if defined(BSP_USING_SPI_FLASH)

#include "dev_spi_flash.h"
#include "drv_spiflash.h"
#include "dev_spi_flash_sfud.h"
#include "drv_spi.h"

int rt_hw_spi_flash_init(void)
{

    if (RT_NULL == rt_sfud_flash_probe(ES_DEVICE_NAME_SPI_FALSH_DEV, ES_DEVICE_NAME_SPI_DEV))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

#endif
