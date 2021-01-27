/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-28     hqfang       first implementation.
 */

#include "drv_spi.h"

#ifdef RT_USING_SPI

#if !defined(BSP_USING_SPI0) && !defined(BSP_USING_SPI1) && !defined(BSP_USING_SPI2)
    #error "Please define at least one BSP_USING_SPIx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable SPI */
#endif

static struct gd32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI0
    {
        "spi0",
        SPI0,
    },
#endif
#ifdef BSP_USING_SPI1
    {
        "spi1",
        SPI1,
    },
#endif
#ifdef BSP_USING_SPI2
    {
        "spi2",
        SPI2,
    },
#endif
};

static struct gd32_spi spi_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

static rt_err_t gd32_spi_init(rt_uint32_t spi_periph, struct rt_spi_configuration *cfg)
{
    spi_parameter_struct spicfg;
    uint32_t apbfreq;
    uint32_t scale;

    RT_ASSERT(cfg != RT_NULL);

    spi_struct_para_init(&spicfg);

    if (cfg->data_width != 8 && cfg->data_width != 16)
    {
        return (-RT_EINVAL);
    }

    switch (spi_periph)
    {
    case SPI0:
        apbfreq = rcu_clock_freq_get(CK_APB2);
        break;
    default:
        apbfreq = rcu_clock_freq_get(CK_APB1);
        break;
    }

    scale = apbfreq / cfg->max_hz;
    if (scale <= 2)
    {
        spicfg.prescale = SPI_PSC_2;
    }
    else if (scale <= 4)
    {
        spicfg.prescale = SPI_PSC_4;
    }
    else if (scale <= 8)
    {
        spicfg.prescale = SPI_PSC_8;
    }
    else if (scale <= 16)
    {
        spicfg.prescale = SPI_PSC_16;
    }
    else if (scale <= 32)
    {
        spicfg.prescale = SPI_PSC_32;
    }
    else if (scale <= 64)
    {
        spicfg.prescale = SPI_PSC_64;
    }
    else if (scale <= 128)
    {
        spicfg.prescale = SPI_PSC_128;
    }
    else if (scale <= 256)
    {
        spicfg.prescale = SPI_PSC_256;
    }
    else
    {
        spicfg.prescale = SPI_PSC_256;
    }

    if (cfg->data_width == 8)
    {
        spicfg.frame_size = SPI_FRAMESIZE_8BIT;
    }
    else
    {
        spicfg.frame_size = SPI_FRAMESIZE_16BIT;
    }

    if (cfg->mode & RT_SPI_MSB)
    {
        spicfg.endian = SPI_ENDIAN_MSB;
    }
    else
    {
        spicfg.endian = SPI_ENDIAN_LSB;
    }

    spicfg.clock_polarity_phase = 0;
    if (cfg->mode & RT_SPI_CPHA)
    {
        spicfg.clock_polarity_phase |= SPI_CTL0_CKPH;
    }
    if (cfg->mode & RT_SPI_CPOL)
    {
        spicfg.clock_polarity_phase |= SPI_CTL0_CKPL;
    }

    if (cfg->mode & RT_SPI_SLAVE)
    {
        spicfg.device_mode = SPI_SLAVE;
    }
    else
    {
        spicfg.device_mode = SPI_MASTER;
    }
    spicfg.nss = SPI_NSS_SOFT;
    spicfg.trans_mode = SPI_TRANSMODE_FULLDUPLEX;

    spi_init(spi_periph, &spicfg);
    /* set crc polynomial */
    spi_crc_polynomial_set(spi_periph, 7);

    return RT_EOK;
}

static rt_err_t gd32_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    rt_err_t ret = RT_EOK;
    RT_ASSERT(device != RT_NULL);

    struct gd32_spi *spi_obj = (struct gd32_spi *)(device->bus->parent.user_data);
    struct gd32_spi_config *spi_cfg = (struct gd32_spi_config *)(spi_obj->config);

    ret = gd32_spi_init(spi_cfg->spi_periph, cfg);
    /* enable SPI */
    spi_enable(spi_cfg->spi_periph);

    return ret;
}

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret = RT_EOK;

    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    struct gd32_spi_cs *cs_pin = (struct gd32_spi_cs *)rt_malloc(sizeof(struct gd32_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);

    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, PIN_HIGH);

    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    return ret;
}

rt_size_t gd32_spi_transmit(rt_uint32_t spi_periph, const void *send_buf, void *recv_buf, rt_size_t length)
{
    uint8_t *send_buf_8b = (uint8_t *)send_buf;
    uint8_t *recv_buf_8b = (uint8_t *)recv_buf;
    uint8_t sndbyte = 0xFF, rcvbyte;
    rt_size_t idx = 0;

    while (idx < length)
    {
        while (RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
        if (send_buf_8b)
        {
            sndbyte = send_buf_8b[idx];
        }
        spi_i2s_data_transmit(spi_periph, sndbyte);
        while (RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
        rcvbyte = spi_i2s_data_receive(spi_periph);
        if (recv_buf_8b)
        {
            recv_buf_8b[idx] = rcvbyte;
        }
        idx ++;
    }

    return length;
}

static rt_uint32_t gd32_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_uint32_t total_length = 0;
    rt_err_t ret = RT_EOK;

    RT_ASSERT(device != RT_NULL);

    struct gd32_spi *spi_obj = (struct gd32_spi *)(device->bus->parent.user_data);
    struct gd32_spi_config *spi_cfg = (struct gd32_spi_config *)(spi_obj->config);
    RT_ASSERT(spi_cfg != RT_NULL);
    struct gd32_spi_cs *cs = (struct gd32_spi_cs *)(device->parent.user_data);

    if (message && message->cs_take)
    {
        rt_pin_write(cs->pin, PIN_LOW);
    }
    if (message && message->length)
    {

        total_length += gd32_spi_transmit(spi_cfg->spi_periph, message->send_buf, \
                                          message->recv_buf, message->length);
    }
    if (message && message->cs_release)
    {
        rt_pin_write(cs->pin, PIN_HIGH);
    }
    return total_length;
}

static const struct rt_spi_ops spi_ops =
{
    gd32_spi_configure,
    gd32_spi_xfer
};

int rt_hw_spi_init(void)
{
    rt_size_t obj_num;
    int index;
    rt_err_t result = 0;

#ifdef BSP_USING_SPI0
    rcu_periph_clock_enable(RCU_SPI0);
#endif
#ifdef BSP_USING_SPI1
    rcu_periph_clock_enable(RCU_SPI1);
#endif
#ifdef BSP_USING_SPI2
    rcu_periph_clock_enable(RCU_SPI2);
#endif

    obj_num = sizeof(spi_obj) / sizeof(struct gd32_spi);
    for (index = 0; index < obj_num; index++)
    {
        /* init spi object */
        spi_obj[index].config = &spi_config[index];
        spi_obj[index].bus.parent.user_data = &spi_obj[index];

        /* register spi device */
        result = rt_spi_bus_register(&spi_obj[index].bus,
                                     spi_obj[index].config->name,
                                     &spi_ops);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);

#endif
/* end of spi driver */
