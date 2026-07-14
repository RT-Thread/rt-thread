/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_QSPI)

#include "drv_spi.h"
#include "rtdef.h"
#include "rthw.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.qspi"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#if defined(BSP_USING_SPI_PDMA)
#if defined(BSP_USING_QSPI0_PDMA)
#define QSPI0_PDMA_INIT                 \
    .pdma_perp_tx = PDMA_QSPI0_TX,      \
    .pdma_perp_rx = PDMA_QSPI0_RX,
#else
#define QSPI0_PDMA_INIT                 \
    .pdma_perp_tx = NU_PDMA_UNUSED,     \
    .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#else
#define QSPI0_PDMA_INIT
#endif

#define DEFINE_NU_QSPI(_idx, _pdma_init) \
    {                                     \
        .name = "qspi" #_idx,            \
        .spi_base = (SPI_T *)QSPI##_idx,  \
        .rstidx = QSPI##_idx##_RST,       \
        _pdma_init                        \
    }


/* Types / Structures ---------------------------------------------------------*/
enum
{
    QSPI_START = -1,
#if defined(BSP_USING_QSPI0)
    QSPI0_IDX,
#endif
    QSPI_CNT
};

/* Static Function Prototypes ------------------------------------------------*/
static rt_err_t nu_qspi_bus_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_ssize_t nu_qspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message);
static int nu_qspi_register_bus(struct nu_spi *qspi_bus, const char *name);

/* Static Variables ----------------------------------------------------------*/
static struct rt_spi_ops nu_qspi_poll_ops =
{
    .configure = nu_qspi_bus_configure,
    .xfer      = nu_qspi_bus_xfer,
};

static struct nu_spi nu_qspi_arr [] =
{
#if defined(BSP_USING_QSPI0)
    DEFINE_NU_QSPI(0, QSPI0_PDMA_INIT),
#endif
}; /* qspi nu_qspi */

/* Functions Implementation --------------------------------------------------*/
static rt_err_t nu_qspi_bus_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *configuration)
{
    struct nu_spi *spi_bus;
    rt_uint32_t u32SPIMode;
    rt_uint32_t u32BusClock;
    rt_err_t ret = RT_EOK;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    spi_bus = (struct nu_spi *) device->bus;

    /* Check mode */
    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        u32SPIMode = SPI_MODE_0;
        break;
    case RT_SPI_MODE_1:
        u32SPIMode = SPI_MODE_1;
        break;
    case RT_SPI_MODE_2:
        u32SPIMode = SPI_MODE_2;
        break;
    case RT_SPI_MODE_3:
        u32SPIMode = SPI_MODE_3;
        break;
    default:
        ret = RT_EIO;
        goto exit_nu_qspi_bus_configure;
    }
    if (!(configuration->data_width == 8  ||
            configuration->data_width == 16 ||
            configuration->data_width == 24 ||
            configuration->data_width == 32))
    {
        ret = RT_EINVAL;
        goto exit_nu_qspi_bus_configure;
    }
    u32BusClock = QSPI_SetBusClock((QSPI_T *)spi_bus->spi_base, configuration->max_hz);
    if (configuration->max_hz > u32BusClock)
    {
        LOG_W("%s clock max frequency is %dHz ( != %dHz)\n", spi_bus->name, u32BusClock, configuration->max_hz);
        configuration->max_hz = u32BusClock;
    }
    if (rt_memcmp(configuration, &spi_bus->configuration, sizeof(struct rt_spi_configuration)) != 0)
    {
        rt_memcpy(&spi_bus->configuration, configuration, sizeof(struct rt_spi_configuration));

        QSPI_Open((QSPI_T *)spi_bus->spi_base, SPI_MASTER, u32SPIMode, configuration->data_width, u32BusClock);

        if (configuration->mode & RT_SPI_CS_HIGH)
        {
            /* Set CS pin to LOW */
            SPI_SET_SS_LOW(spi_bus->spi_base);
        }
        else
        {
            /* Set CS pin to HIGH */
            SPI_SET_SS_HIGH(spi_bus->spi_base);
        }

        if (configuration->mode & RT_SPI_MSB)
        {
            /* Set sequence to MSB first */
            SPI_SET_MSB_FIRST(spi_bus->spi_base);
        }
        else
        {
            /* Set sequence to LSB first */
            SPI_SET_LSB_FIRST(spi_bus->spi_base);
        }
    }
    nu_spi_drain_rxfifo(spi_bus->spi_base);

exit_nu_qspi_bus_configure:

    return -(ret);
}

static int nu_qspi_mode_config(struct nu_spi *qspi_bus, rt_uint8_t *tx, rt_uint8_t *rx, int qspi_lines)
{
    QSPI_T *qspi_base = (QSPI_T *)qspi_bus->spi_base;
    if (qspi_lines > 1)
    {
        if (tx)
        {
            switch (qspi_lines)
            {
            case 2:
                QSPI_ENABLE_DUAL_OUTPUT_MODE(qspi_base);
                break;
            case 4:
                QSPI_ENABLE_QUAD_OUTPUT_MODE(qspi_base);
                break;
            default:
                LOG_E("Data line is not supported.\n");
                break;
            }
        }
        else
        {
            switch (qspi_lines)
            {
            case 2:
                QSPI_ENABLE_DUAL_INPUT_MODE(qspi_base);
                break;
            case 4:
                QSPI_ENABLE_QUAD_INPUT_MODE(qspi_base);
                break;
            default:
                LOG_E("Data line is not supported.\n");
                break;
            }
        }
    }
    else
    {
        QSPI_DISABLE_DUAL_MODE(qspi_base);
        QSPI_DISABLE_QUAD_MODE(qspi_base);
    }
    return qspi_lines;
}

static rt_ssize_t nu_qspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct nu_spi *qspi_bus;
    struct rt_qspi_configuration *qspi_configuration;
    struct rt_qspi_message *qspi_message;
    rt_uint8_t u8last = 1;
    rt_uint8_t bytes_per_word;
    QSPI_T *qspi_base;
    rt_uint32_t u32len = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    qspi_bus = (struct nu_spi *) device->bus;
    qspi_base = (QSPI_T *)qspi_bus->spi_base;
    qspi_configuration = &qspi_bus->configuration;

    bytes_per_word = qspi_configuration->parent.data_width / 8;

    if (message->cs_take && !(qspi_configuration->parent.mode & RT_SPI_NO_CS))
    {
        if (qspi_configuration->parent.mode & RT_SPI_CS_HIGH)
        {
            QSPI_SET_SS_HIGH(qspi_base);
        }
        else
        {
            QSPI_SET_SS_LOW(qspi_base);
        }
    }

    qspi_message = (struct rt_qspi_message *)message;

    /* Command + Address + Dummy + Data */
    /* Command stage */
    if (qspi_message->instruction.content != 0)
    {
        u8last = nu_qspi_mode_config(qspi_bus, (rt_uint8_t *) &qspi_message->instruction.content, RT_NULL, qspi_message->instruction.qspi_lines);
        nu_spi_transfer((struct nu_spi *)qspi_bus,
                        (rt_uint8_t *) &qspi_message->instruction.content,
                        RT_NULL,
                        1,
                        1);
    }
    if (qspi_message->address.size > 0)
    {
        rt_uint32_t u32ReversedAddr = 0;
        rt_uint32_t u32AddrNumOfByte = qspi_message->address.size / 8;
        switch (u32AddrNumOfByte)
        {
        case 1:
            u32ReversedAddr = (qspi_message->address.content & 0xff);
            break;
        case 2:
            nu_set16_be((rt_uint8_t *)&u32ReversedAddr, qspi_message->address.content);
            break;
        case 3:
            nu_set24_be((rt_uint8_t *)&u32ReversedAddr, qspi_message->address.content);
            break;
        case 4:
            nu_set32_be((rt_uint8_t *)&u32ReversedAddr, qspi_message->address.content);
            break;
        default:
            RT_ASSERT(0);
            break;
        }
        u8last = nu_qspi_mode_config(qspi_bus, (rt_uint8_t *)&u32ReversedAddr, RT_NULL, qspi_message->address.qspi_lines);
        nu_spi_transfer((struct nu_spi *)qspi_bus,
                        (rt_uint8_t *) &u32ReversedAddr,
                        RT_NULL,
                        u32AddrNumOfByte,
                        1);
    }
    if ((qspi_message->alternate_bytes.size > 0) && (qspi_message->alternate_bytes.size <= 4))
    {
        rt_uint32_t u32AlternateByte = 0;
        rt_uint32_t u32NumOfByte = qspi_message->alternate_bytes.size / 8;
        switch (u32NumOfByte)
        {
        case 1:
            u32AlternateByte = (qspi_message->alternate_bytes.content & 0xff);
            break;
        case 2:
            nu_set16_be((rt_uint8_t *)&u32AlternateByte, qspi_message->alternate_bytes.content);
            break;
        case 3:
            nu_set24_be((rt_uint8_t *)&u32AlternateByte, qspi_message->alternate_bytes.content);
            break;
        case 4:
            nu_set32_be((rt_uint8_t *)&u32AlternateByte, qspi_message->alternate_bytes.content);
            break;
        default:
            RT_ASSERT(0);
            break;
        }
        u8last = nu_qspi_mode_config(qspi_bus, (rt_uint8_t *)&u32AlternateByte, RT_NULL, qspi_message->alternate_bytes.qspi_lines);
        nu_spi_transfer((struct nu_spi *)qspi_bus,
                        (rt_uint8_t *) &u32AlternateByte,
                        RT_NULL,
                        u32NumOfByte,
                        1);
    }
    if (qspi_message->dummy_cycles > 0)
    {
        qspi_bus->dummy[0] = 0x00;

        u8last = nu_qspi_mode_config(qspi_bus, (rt_uint8_t *) &qspi_bus->dummy[0], RT_NULL, u8last);
        nu_spi_transfer((struct nu_spi *)qspi_bus,
                        (rt_uint8_t *) &qspi_bus->dummy[0],
                        RT_NULL,
                        qspi_message->dummy_cycles / (8 / u8last),
                        1);
    }

    if (message->length > 0)
    {
        /* Data stage */
        nu_qspi_mode_config(qspi_bus, (rt_uint8_t *) message->send_buf, (rt_uint8_t *) message->recv_buf, qspi_message->qspi_data_lines);
        nu_spi_transfer((struct nu_spi *)qspi_bus,
                        (rt_uint8_t *) message->send_buf,
                        (rt_uint8_t *) message->recv_buf,
                        message->length,
                        bytes_per_word);
        u32len = message->length;
    }
    else
    {
        u32len = 1;
    }

    if (message->cs_release && !(qspi_configuration->parent.mode & RT_SPI_NO_CS))
    {
        if (qspi_configuration->parent.mode & RT_SPI_CS_HIGH)
        {
            QSPI_SET_SS_LOW(qspi_base);
        }
        else
        {
            QSPI_SET_SS_HIGH(qspi_base);
        }
    }

    return u32len;
}

static int nu_qspi_register_bus(struct nu_spi *qspi_bus, const char *name)
{
    return rt_qspi_bus_register(&qspi_bus->dev, name, &nu_qspi_poll_ops);
}

/**
 * Hardware SPI Initial
 */
static int rt_hw_qspi_init(void)
{
    rt_uint8_t i;

    for (i = (QSPI_START + 1); i < QSPI_CNT; i++)
    {
        SYS_ResetModule(nu_qspi_arr[i].rstidx);

        nu_qspi_arr[i].dummy = rt_malloc_align(RT_ALIGN_SIZE, RT_ALIGN_SIZE);
        RT_ASSERT(nu_qspi_arr[i].dummy);
#if defined(BSP_USING_SPI_PDMA)
        nu_qspi_arr[i].pdma_chanid_tx = -1;
        nu_qspi_arr[i].pdma_chanid_rx = -1;
#endif
#if defined(BSP_USING_QSPI_PDMA)
        if ((nu_qspi_arr[i].pdma_perp_tx != NU_PDMA_UNUSED) && (nu_qspi_arr[i].pdma_perp_rx != NU_PDMA_UNUSED))
        {
            if (nu_hw_spi_pdma_allocate(&nu_qspi_arr[i]) != RT_EOK)
            {
                LOG_E("Failed to allocate DMA channels for %s. We will use poll-mode for this bus.\n", nu_qspi_arr[i].name);
            }
        }
#endif
        nu_qspi_register_bus(&nu_qspi_arr[i], nu_qspi_arr[i].name);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_qspi_init);

rt_err_t nu_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)())
{
    struct rt_qspi_device *qspi_device = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(data_line_width == 1 || data_line_width == 2 || data_line_width == 4);

    qspi_device = (struct rt_qspi_device *)
                  rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;
    qspi_device->config.qspi_dl_width = data_line_width;

    result = rt_spi_bus_attach_device(&qspi_device->parent, device_name, bus_name, RT_NULL);

__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }
    }

    return  result;
}
#endif //#if defined(BSP_USING_QSPI)
