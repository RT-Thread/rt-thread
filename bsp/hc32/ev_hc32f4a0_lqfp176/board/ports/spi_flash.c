/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include <rtthread.h>
#include "drv_spi.h"

#if defined(BSP_USING_SPI_FLASH)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static int rt_hw_spi_flash_init(void)
{
    rt_hw_spi_device_attach("spi1", "spi10", GPIO_PORT_C, GPIO_PIN_07);
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

#endif
