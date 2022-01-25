/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2021-02-14       supperthomas    first version
 */

#include <stdint.h>
#include <string.h>
#include "board.h"
#include "drv_spi.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG                "drv.spi"

#ifdef BSP_USING_SPI

#if defined(BSP_USING_SPI0) || defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2)
static struct mcu_drv_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI0
    MCU_SPI0_CONFIG,
#endif
#ifdef BSP_USING_SPI1
    MCU_SPI1_CONFIG,
#endif

};

static struct mcu_drv_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])];


/**
  * @brief  This function config spi bus
  * @param  device
  * @param  configuration
  * @retval RT_EOK / RT_ERROR
  */
static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    struct mcu_drv_spi *tmp_spi;
    tmp_spi = rt_container_of(device->bus, struct mcu_drv_spi, spi_bus);
    int mode;

    ///init

    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0/* RT_SPI_CPOL:0 , RT_SPI_CPHA:0 */:
    case RT_SPI_MODE_1/* RT_SPI_CPOL:0 , RT_SPI_CPHA:1 */:
    case RT_SPI_MODE_2/* RT_SPI_CPOL:1 , RT_SPI_CPHA:0 */:
    case RT_SPI_MODE_3/* RT_SPI_CPOL:1 , RT_SPI_CPHA:1 */:
        mode = configuration->mode & RT_SPI_MODE_3;
        break;
    default:
        LOG_E("spi_configure mode error %x\n", configuration->mode);
        return RT_ERROR;
    }

    tmp_spi->spixfer_req.width = SPI17Y_WIDTH_1;
    tmp_spi->spixfer_req.bits = configuration->data_width;
    tmp_spi->spixfer_req.ssel = 0;
    tmp_spi->spixfer_req.deass = 1;
    tmp_spi->spixfer_req.tx_num = 0;
    tmp_spi->spixfer_req.rx_num = 0;
    tmp_spi->spixfer_req.callback = NULL;
    LOG_D("spi init mode:%d, rate:%d", mode, configuration->max_hz);
    if (SPI_Init(tmp_spi->spi_instance, mode, configuration->max_hz) != 0)
    {
        LOG_E("Error configuring SPI\n");
        while (1) {}
    }
    //init
    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    int ret = 0;
    struct mcu_drv_spi *tmp_spi;
    tmp_spi = rt_container_of(device->bus, struct mcu_drv_spi, spi_bus);


    tmp_spi->spixfer_req.tx_data = message->send_buf;
    tmp_spi->spixfer_req.rx_data = message->recv_buf;
    tmp_spi->spixfer_req.len = message->length;
    ret = SPI_MasterTrans(tmp_spi->spi_instance, &tmp_spi->spixfer_req);
    if (ret == E_NO_ERROR)
    {
        return message->length;
    }
    else
    {
        LOG_E("spixfer faild, ret %d", ret);
        return 0;
    }
}

/* spi bus callback function  */
static const struct rt_spi_ops nrfx_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

/*spi bus init*/
static int rt_hw_spi_bus_init(void)
{
    rt_err_t result = RT_ERROR;
    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].spi_instance = spi_config[i].spi_instance;
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];   //SPI INSTANCE
        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &nrfx_spi_ops);
        RT_ASSERT(result == RT_EOK);
    }
    return result;
}

int rt_hw_spi_init(void)
{
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(cs_pin != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    /* initialize the cs pin */
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d", device_name, bus_name, result);
        result = RT_ERROR;
    }
    /* TODO: SET THE GPIO */

    RT_ASSERT(result == RT_EOK);
    return result;
}

#endif /* BSP_USING_SPI0 || BSP_USING_SPI1 || BSP_USING_SPI2 */
#endif /*BSP_USING_SPI*/


