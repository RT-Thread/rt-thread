/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-02     Liuguang     the first version.
 */
 
#include "drv_spi_flash.h" 

#include "spi_flash.h" 
#include "spi_flash_sfud.h" 

#ifndef SPI_FLASH_USING_SPIBUS_NAME 
#define SPI_FLASH_USING_SPIBUS_NAME "spi4" 
#endif
#ifndef SPI_FLASH_NAME 
#define SPI_FLASH_NAME "flash0" 
#endif
#ifndef SPI_FLASH_USING_CS_PIN 
#define SPI_FLASH_USING_CS_PIN (79) 
#endif

int rt_hw_spi_flash_init(void)
{
    rt_err_t ret; 
    
    extern rt_err_t rt1050_spi_bus_attach_device(const char *bus_name, 
        const char *device_name, rt_uint32_t pin); 
    
    ret = rt1050_spi_bus_attach_device(SPI_FLASH_USING_SPIBUS_NAME, 
        SPI_FLASH_USING_SPIBUS_NAME "0", SPI_FLASH_USING_CS_PIN); 
    if(ret != RT_EOK) 
    {
        return ret; 
    }
    
    if(rt_sfud_flash_probe(SPI_FLASH_NAME, SPI_FLASH_USING_SPIBUS_NAME "0") == RT_NULL) 
    {
        return RT_ERROR;
    }

    return RT_EOK; 
}
INIT_DEVICE_EXPORT(rt_hw_spi_flash_init); 
