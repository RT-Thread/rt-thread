/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     Mr.Tiger     first version
 * 2021-11-04     Sherman      ADD complete_event
 * 2022-12-7      Vandoul      ADD sci spi
 */
/**< Note : Turn on any DMA mode and all SPIs will turn on DMA */

#include "drv_sci_spi.h"

#ifdef RT_USING_SPI

//#define DRV_DEBUG
#define DBG_TAG              "drv.scispi"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#define RA_SCI_SPI0_EVENT 0x0001
#define RA_SCI_SPI1_EVENT 0x0002
#define RA_SCI_SPI2_EVENT 0x0004
#define RA_SCI_SPI3_EVENT 0x0008
#define RA_SCI_SPI4_EVENT 0x0010
#define RA_SCI_SPI5_EVENT 0x0020
#define RA_SCI_SPI6_EVENT 0x0040
#define RA_SCI_SPI7_EVENT 0x0080
#define RA_SCI_SPI8_EVENT 0x0100
#define RA_SCI_SPI9_EVENT 0x0200
static struct rt_event complete_event = {0};

static struct ra_sci_spi_handle spi_handle[] =
{
#ifdef BSP_USING_SCI_SPI0
    {.bus_name = "scpi0", .spi_ctrl_t = &g_sci_spi0_ctrl, .spi_cfg_t = &g_sci_spi0_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI1
    {.bus_name = "scpi1", .spi_ctrl_t = &g_sci_spi1_ctrl, .spi_cfg_t = &g_sci_spi1_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI2
    {.bus_name = "scpi2", .spi_ctrl_t = &g_sci_spi2_ctrl, .spi_cfg_t = &g_sci_spi2_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI3
    {.bus_name = "scpi3", .spi_ctrl_t = &g_sci_spi3_ctrl, .spi_cfg_t = &g_sci_spi3_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI4
    {.bus_name = "scpi4", .spi_ctrl_t = &g_sci_spi4_ctrl, .spi_cfg_t = &g_sci_spi4_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI5
    {.bus_name = "scpi5", .spi_ctrl_t = &g_sci_spi5_ctrl, .spi_cfg_t = &g_sci_spi5_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI6
    {.bus_name = "scpi6", .spi_ctrl_t = &g_sci_spi6_ctrl, .spi_cfg_t = &g_sci_spi6_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI7
    {.bus_name = "scpi7", .spi_ctrl_t = &g_sci_spi7_ctrl, .spi_cfg_t = &g_sci_spi7_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI8
    {.bus_name = "scpi8", .spi_ctrl_t = &g_sci_spi8_ctrl, .spi_cfg_t = &g_sci_spi8_cfg,},
#endif

#ifdef BSP_USING_SCI_SPI9
    {.bus_name = "scpi9", .spi_ctrl_t = &g_sci_spi9_ctrl, .spi_cfg_t = &g_sci_spi9_cfg,},
#endif
};

static struct ra_sci_spi spi_config[sizeof(spi_handle) / sizeof(spi_handle[0])] = {0};
#define SCI_SPIx_CALLBACK(n)        \
void sci_spi##n##_callback(spi_callback_args_t *p_args) \
{ \
    rt_interrupt_enter(); \
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event) \
    { \
        rt_event_send(&complete_event, RA_SCI_SPI##n##_EVENT); \
    } \
    rt_interrupt_leave(); \
}

SCI_SPIx_CALLBACK(0);
SCI_SPIx_CALLBACK(1);
SCI_SPIx_CALLBACK(2);
SCI_SPIx_CALLBACK(3);
SCI_SPIx_CALLBACK(4);
SCI_SPIx_CALLBACK(5);
SCI_SPIx_CALLBACK(6);
SCI_SPIx_CALLBACK(7);
SCI_SPIx_CALLBACK(8);
SCI_SPIx_CALLBACK(9);

#define SCI_SPIx_EVENT_RECV(n)      \
    rt_event_recv(event, \
    RA_SCI_SPI##n##_EVENT, \
    RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, \
    RT_WAITING_FOREVER, \
    &recved);

static rt_err_t ra_wait_complete(rt_event_t event, const char bus_name[RT_NAME_MAX])
{
    rt_uint32_t recved = 0x00;

    switch (bus_name[4])
    {
        case '0':
        return SCI_SPIx_EVENT_RECV(0);
        case '1':
        return SCI_SPIx_EVENT_RECV(1);
        case '2':
        return SCI_SPIx_EVENT_RECV(2);
        case '3':
        return SCI_SPIx_EVENT_RECV(3);
        case '4':
        return SCI_SPIx_EVENT_RECV(4);
        case '5':
        return SCI_SPIx_EVENT_RECV(5);
        case '6':
        return SCI_SPIx_EVENT_RECV(6);
        case '7':
        return SCI_SPIx_EVENT_RECV(7);
        case '8':
        return SCI_SPIx_EVENT_RECV(8);
        case '9':
        return SCI_SPIx_EVENT_RECV(9);
    }
    return -RT_EINVAL;
}

static spi_bit_width_t ra_width_shift(rt_uint8_t data_width)
{
    spi_bit_width_t bit_width = SPI_BIT_WIDTH_8_BITS;
    if(data_width == 1)
        bit_width = SPI_BIT_WIDTH_8_BITS;
    else if(data_width == 2)
        bit_width = SPI_BIT_WIDTH_16_BITS;
    else if(data_width == 4)
        bit_width = SPI_BIT_WIDTH_32_BITS;

    return bit_width;
}

static rt_err_t ra_write_message(struct rt_spi_device *device, const void *send_buf, const rt_size_t len)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(send_buf != NULL);
    RT_ASSERT(len > 0);
    rt_err_t err = RT_EOK;
    struct ra_sci_spi *spi_dev =  rt_container_of(device->bus, struct ra_sci_spi, bus);

    spi_bit_width_t bit_width = ra_width_shift(spi_dev->rt_spi_cfg_t->data_width);
    /**< send msessage */
    err = R_SCI_SPI_Write((spi_ctrl_t *)spi_dev->ra_spi_handle_t->spi_ctrl_t, send_buf, len, bit_width);
    if (RT_EOK != err)
    {
        LOG_E("%s write failed. %d", spi_dev->ra_spi_handle_t->bus_name, err);
        return -RT_ERROR;
    }
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    ra_wait_complete(&complete_event, spi_dev->ra_spi_handle_t->bus_name);
    return len;
}

static rt_err_t ra_read_message(struct rt_spi_device *device, void *recv_buf, const rt_size_t len)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(recv_buf != NULL);
    RT_ASSERT(len > 0);
    rt_err_t err = RT_EOK;
    struct ra_sci_spi *spi_dev =  rt_container_of(device->bus, struct ra_sci_spi, bus);

    spi_bit_width_t bit_width = ra_width_shift(spi_dev->rt_spi_cfg_t->data_width);
    /**< receive message */
    err = R_SCI_SPI_Read((spi_ctrl_t *)spi_dev->ra_spi_handle_t->spi_ctrl_t, recv_buf, len, bit_width);
    if (RT_EOK != err)
    {
        LOG_E("%s write failed. %d", spi_dev->ra_spi_handle_t->bus_name, err);
        return -RT_ERROR;
    }
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    ra_wait_complete(&complete_event, spi_dev->ra_spi_handle_t->bus_name);
    return len;
}

static rt_err_t ra_write_read_message(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);
    RT_ASSERT(message->length > 0);
    rt_err_t err = RT_EOK;
    struct ra_sci_spi *spi_dev =  rt_container_of(device->bus, struct ra_sci_spi, bus);

    spi_bit_width_t bit_width = ra_width_shift(spi_dev->rt_spi_cfg_t->data_width);
    /**< write and receive message */
    err = R_SCI_SPI_WriteRead((spi_ctrl_t *)spi_dev->ra_spi_handle_t->spi_ctrl_t, message->send_buf, message->recv_buf, message->length, bit_width);
    if (RT_EOK != err)
    {
        LOG_E("%s write and read failed. %d", spi_dev->ra_spi_handle_t->bus_name, err);
        return -RT_ERROR;
    }
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    ra_wait_complete(&complete_event, spi_dev->ra_spi_handle_t->bus_name);
    return message->length;
}

/**< init spi TODO : MSB does not support modification */
static rt_err_t ra_hw_spi_configure(struct rt_spi_device *device,
                                    struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(configuration != NULL);
    rt_err_t err = RT_EOK;

    struct ra_sci_spi *spi_dev =  rt_container_of(device->bus, struct ra_sci_spi, bus);

    /**< data_width : 1 -> 8 bits , 2 -> 16 bits, 4 -> 32 bits, default 32 bits*/
    rt_uint8_t data_width = configuration->data_width / 8;
    RT_ASSERT(data_width == 1 || data_width == 2 || data_width == 4);
    configuration->data_width = configuration->data_width / 8;
    spi_dev->rt_spi_cfg_t = configuration;

    sci_spi_extended_cfg_t *spi_cfg = (sci_spi_extended_cfg_t *)spi_dev->ra_spi_handle_t->spi_cfg_t->p_extend;

    /**< Configure Select Line */
    rt_pin_write(device->cs_pin, PIN_HIGH);

    /**< config bitrate */
    R_SCI_SPI_CalculateBitrate(spi_dev->rt_spi_cfg_t->max_hz, &spi_cfg->clk_div, false);

    /**< init */
    err = R_SCI_SPI_Open((spi_ctrl_t *)spi_dev->ra_spi_handle_t->spi_ctrl_t, (spi_cfg_t const * const)spi_dev->ra_spi_handle_t->spi_cfg_t);
    /* handle error */
    if(err == FSP_ERR_IN_USE) {
        R_SCI_SPI_Close((spi_ctrl_t *)spi_dev->ra_spi_handle_t->spi_ctrl_t);
        err = R_SCI_SPI_Open((spi_ctrl_t *)spi_dev->ra_spi_handle_t->spi_ctrl_t, (spi_cfg_t const * const)spi_dev->ra_spi_handle_t->spi_cfg_t);
    }
    if (RT_EOK != err)
    {
        LOG_E("%s init failed. %d", spi_dev->ra_spi_handle_t->bus_name, err);
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_ssize_t ra_spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    rt_err_t err = RT_EOK;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_HIGH);
        else
            rt_pin_write(device->cs_pin, PIN_LOW);
    }

    if (message->length > 0)
    {
        if (message->send_buf == RT_NULL && message->recv_buf != RT_NULL)
        {
            /**< receive message */
            err = ra_read_message(device, (void *)message->recv_buf, (const rt_size_t)message->length);
        }
        else if (message->send_buf != RT_NULL && message->recv_buf == RT_NULL)
        {
            /**< send message */
            err = ra_write_message(device, (const void *)message->send_buf, (const rt_size_t)message->length);
        }
        else if (message->send_buf != RT_NULL && message->recv_buf != RT_NULL)
        {
            /**< send and receive message */
            err =  ra_write_read_message(device, message);
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
    }
    return err;
}

static const struct rt_spi_ops ra_spi_ops =
{
    .configure = ra_hw_spi_configure,
    .xfer = ra_spixfer,
};

int ra_hw_sci_spi_init(void)
{
    for (rt_uint8_t spi_index = 0; spi_index < sizeof(spi_handle) / sizeof(spi_handle[0]); spi_index++)
    {
        spi_config[spi_index].ra_spi_handle_t = &spi_handle[spi_index];

        /**< register spi bus */
        rt_err_t err = rt_spi_bus_register(&spi_config[spi_index].bus, spi_handle[spi_index].bus_name, &ra_spi_ops);
        if (RT_EOK != err)
        {
            LOG_E("%s bus register failed. %d", spi_config[spi_index].ra_spi_handle_t->bus_name, err);
            return -RT_ERROR;
        }
    }

    if (RT_EOK != rt_event_init(&complete_event, "ra_scispi", RT_IPC_FLAG_PRIO))
    {
        LOG_E("SPI transfer event init fail!");
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_BOARD_EXPORT(ra_hw_sci_spi_init);

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_sci_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}
#endif /* RT_USING_SPI */
