/**
 * @file drv_spi.h
 * @author 100ask development team
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022 Chongqing 100ASK Technology Co., LTD
 * 
 */

#ifndef __DRV_SPI_H_
#define __DRV_SPI_H_

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include "drv_common.h"
#include "drv_dma.h"

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef* cs_gpiox, uint16_t cs_gpio_pin);

struct mm32_hw_spi_cs
{
    GPIO_Type* GPIOx;
    uint16_t GPIO_Pin;
};

struct mm32_spi_config
{
    SPI_Type *Instance;
    char *bus_name;
    struct dma_config *dma_rx, *dma_tx;
};

struct stm32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

#define SPI_USING_RX_DMA_FLAG   (1<<0)
#define SPI_USING_TX_DMA_FLAG   (1<<1)

/* stm32 spi dirver class */
struct mm32_spi
{
    SPI_Master_Init_Type handle;
    struct mm32_spi_config *config;
    struct rt_spi_configuration *cfg;

    struct
    {
        rt_uint16_t rx_buf_len;
        rt_uint8_t *rx_buf;
        DMA_Channel_Init_Type handle_rx;
        rt_uint16_t tx_buf_len;
        rt_uint8_t *tx_buf;
        DMA_Channel_Init_Type handle_tx;
    } dma;
    
    rt_uint8_t spi_dma_flag;
    struct rt_spi_bus spi_bus;
};

#endif /* __DRV_SPI_H_ */
