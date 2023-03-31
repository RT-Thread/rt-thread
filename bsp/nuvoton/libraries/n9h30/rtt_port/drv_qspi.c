/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-2-11       Wayne            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_QSPI)

#include <rtdevice.h>
#include "NuMicro.h"
#include <nu_bitutil.h>
#include <drv_sys.h>
#include <drv_qspi.h>

#define LOG_TAG                 "drv.qspi"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <rthw.h>
#include <rtdevice.h>
#include <rtdef.h>

/* Private define ---------------------------------------------------------------*/

/* fsclk = fpclk / ((div+1)*2), but div=1 is suggested. */
#define DEF_SPI_MAX_SPEED  (SPI_INPUT_CLOCK/((1)*2))

enum
{
    QSPI_START = -1,
#if defined(BSP_USING_QSPI0)
    QSPI0_IDX,
#endif
#if defined(BSP_USING_QSPI1)
    QSPI1_IDX,
#endif
    QSPI_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_qspi
{
    struct rt_spi_bus dev;
    char *name;
    uint32_t idx;

    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
    uint32_t dummy;

    struct rt_qspi_configuration  configuration;
};
typedef struct nu_qspi *nu_qspi_t;

/* Private functions ------------------------------------------------------------*/
static void nu_qspi_transmission_with_poll(struct nu_qspi *spi_bus,
        uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word);
static int nu_qspi_register_bus(struct nu_qspi *spi_bus, const char *name);
static rt_ssize_t nu_qspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message);
static rt_err_t nu_qspi_bus_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct rt_spi_ops nu_qspi_poll_ops =
{
    .configure = nu_qspi_bus_configure,
    .xfer      = nu_qspi_bus_xfer,
};

static struct nu_qspi nu_qspi_arr [] =
{
#if defined(BSP_USING_QSPI0)
    {
        .name = "qspi0",
        .idx = 0,
        .rstidx = SPI0RST,
        .clkidx = SPI0CKEN,
    },
#endif
#if defined(BSP_USING_QSPI1)
    {
        .name = "qspi1",
        .idx = 1,
        .rstidx = SPI1RST,
        .clkidx = SPI1CKEN,
    },
#endif
}; /* nu_qspi */

static rt_err_t nu_qspi_bus_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *configuration)
{
    struct nu_qspi *qspi_bus;
    uint32_t u32SPIMode;
    uint32_t u32SPISpeed;
    rt_err_t ret = RT_EOK;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    qspi_bus = (struct nu_qspi *) device->bus;

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
        ret = -RT_EIO;
        goto exit_nu_qspi_bus_configure;
    }

    /* Check data width */
    if (!(configuration->data_width == 8  ||
            configuration->data_width == 16 ||
            configuration->data_width == 24 ||
            configuration->data_width == 32))
    {
        ret = -RT_EINVAL;
        goto exit_nu_qspi_bus_configure;
    }

    /* Need to initialize new configuration? */
    if (rt_memcmp(configuration, &qspi_bus->configuration, sizeof(*configuration)) != 0)
    {
        rt_memcpy(&qspi_bus->configuration, configuration, sizeof(*configuration));

        /* Set mode */
        spiIoctl(qspi_bus->idx, SPI_IOC_SET_MODE, (uint32_t)u32SPIMode, 0);

        /* Set data width */
        spiIoctl(qspi_bus->idx, SPI_IOC_SET_TX_BITLEN, (uint32_t)configuration->data_width, 0);

        /* Set speed */
        u32SPISpeed = configuration->max_hz;

        /* Limitation: SPI clock must be lower than 37.5MHz. */
        if ((SPI_INPUT_CLOCK / 2) > 37500000)
            u32SPISpeed = SPI_INPUT_CLOCK / 4;
        else if (u32SPISpeed > DEF_SPI_MAX_SPEED)
            u32SPISpeed = DEF_SPI_MAX_SPEED;

        u32SPISpeed = spiIoctl(qspi_bus->idx, SPI_IOC_SET_SPEED, u32SPISpeed, 0);
        LOG_I("Actual=%dHz, Prefer=%dHz", u32SPISpeed, configuration->max_hz);

        /* Disable auto-select */
        spiIoctl(qspi_bus->idx, SPI_IOC_SET_AUTOSS, SPI_DISABLE_AUTOSS, 0);

        if (configuration->mode & RT_SPI_CS_HIGH)
        {
            /* Set CS pin to LOW */
            spiIoctl(qspi_bus->idx, SPI_IOC_SET_SS_ACTIVE_LEVEL, SPI_SS_ACTIVE_HIGH, 0);
        }
        else
        {
            /* Set CS pin to HIGH */
            spiIoctl(qspi_bus->idx, SPI_IOC_SET_SS_ACTIVE_LEVEL, SPI_SS_ACTIVE_LOW, 0);
        }

        if (configuration->mode & RT_SPI_MSB)
        {
            /* Set sequence to MSB first */
            spiIoctl(qspi_bus->idx, SPI_IOC_SET_LSB_MSB, SPI_MSB, 0);
        }
        else
        {
            /* Set sequence to LSB first */
            spiIoctl(qspi_bus->idx, SPI_IOC_SET_LSB_MSB, SPI_LSB, 0);
        }
    }

exit_nu_qspi_bus_configure:

    return -(ret);
}

static int nu_qspi_read(uint32_t idx, uint32_t buf_id, uint8_t *recv_addr, uint8_t bytes_per_word)
{
    uint32_t val;

    // Read data from SPI RX FIFO
    switch (bytes_per_word)
    {
    case 4:
        val = spiRead(idx, buf_id);
        nu_set32_le(recv_addr, val);
        break;
    case 3:
        val = spiRead(idx, buf_id);
        nu_set24_le(recv_addr, val);
        break;
    case 2:
        val = spiRead(idx, buf_id);
        nu_set16_le(recv_addr, val);
        break;
    case 1:
        *recv_addr = spiRead(idx, buf_id);
        break;
    default:
        LOG_E("Data length is not supported.\n");
        return 0;
    }
    return bytes_per_word;
}

static int nu_qspi_write(uint32_t idx, uint32_t buf_id, const uint8_t *send_addr, uint8_t bytes_per_word)
{
    // Input data to SPI TX
    switch (bytes_per_word)
    {
    case 4:
        spiWrite(idx, buf_id, nu_get32_le(send_addr));
        break;
    case 3:
        spiWrite(idx, buf_id, nu_get24_le(send_addr));
        break;
    case 2:
        spiWrite(idx, buf_id, nu_get16_le(send_addr));
        break;
    case 1:
        spiWrite(idx, buf_id, *((uint8_t *)send_addr));
        break;
    default:
        LOG_E("Data length is not supported.\n");
        return 0;
    }
    return bytes_per_word;
}

/**
 * @brief SPI bus polling
 * @param dev : The pointer of the specified SPI module.
 * @param send_addr : Source address
 * @param recv_addr : Destination address
 * @param length    : Data length
 */
static void nu_qspi_transmission_with_poll(struct nu_qspi *spi_bus,
        uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word)
{
    uint32_t idx = spi_bus->idx;
    int trans_num = length / bytes_per_word;

    while (trans_num > 0)
    {
        int i;

        uint32_t u32TxNum = (trans_num > 4) ? 4 : trans_num;

        for (i = 0; i < u32TxNum; i++)
        {
            /* Write TX data into TX-buffer */
            if ((send_addr != RT_NULL))
            {
                send_addr += nu_qspi_write(idx, i, (const uint8_t *)send_addr, bytes_per_word);
            }
            else /* read-only */
            {
                spi_bus->dummy = 0;
                nu_qspi_write(idx, i, (const uint8_t *)&spi_bus->dummy, bytes_per_word);
            }
        }

        /* Set TX transacation number */
        spiIoctl(idx, SPI_IOC_SET_TX_NUM, u32TxNum - 1, 0);

        /* Trigger SPI communication. */
        spiIoctl(idx, SPI_IOC_TRIGGER, 0, 0);

        /* Wait it done. */
        while (spiGetBusyStatus(idx)) {};

        /* Read data from RX-buffer */
        if ((recv_addr != RT_NULL))
        {
            for (i = 0; i < u32TxNum; i++)
            {
                recv_addr += nu_qspi_read(idx, i, recv_addr, bytes_per_word);
            }
        }

        trans_num -= u32TxNum;
    }
}

void nu_qspi_transfer(struct nu_qspi *spi_bus, uint8_t *tx, uint8_t *rx, int length, uint8_t bytes_per_word)
{
    RT_ASSERT(spi_bus != RT_NULL);
    nu_qspi_transmission_with_poll(spi_bus, tx, rx, length, bytes_per_word);
}

static int nu_qspi_mode_config(struct nu_qspi *spi_bus, rt_uint8_t *tx, rt_uint8_t *rx, int qspi_lines)
{
    uint32_t idx = spi_bus->idx;
    if (qspi_lines > 1)
    {
        if (tx)
        {
            switch (qspi_lines)
            {
            case 2:
                spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_MODE, SPI_DUAL_MODE, 0);
                break;
            case 4:
                spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_MODE, SPI_QUAD_MODE, 0);
                break;
            default:
                LOG_E("Data line is not supported.\n");
                return -1;
            }
            spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_DIR, SPI_DUAL_QUAD_OUTPUT, 0);
        }
        else if (rx)
        {
            switch (qspi_lines)
            {
            case 2:
                spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_MODE, SPI_DUAL_MODE, 0);
                break;
            case 4:
                spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_MODE, SPI_QUAD_MODE, 0);
                break;
            default:
                LOG_E("Data line is not supported.\n");
                return -1;
            }
            spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_DIR, SPI_DUAL_QUAD_INPUT, 0);
        }
    }
    else
    {
        spiIoctl(idx, SPI_IOC_SET_DUAL_QUAD_MODE, SPI_DISABLE_DUAL_QUAD, 0);
    }
    return qspi_lines;
}

static rt_ssize_t nu_qspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct nu_qspi *spi_bus;
    struct rt_qspi_configuration *qspi_configuration;
    struct rt_qspi_message *qspi_message;
    rt_uint8_t u8last = 1;
    rt_uint8_t bytes_per_word;
    uint32_t idx;
    rt_ssize_t u32len = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    spi_bus = (struct nu_qspi *) device->bus;
    idx = spi_bus->idx;
    qspi_configuration = &spi_bus->configuration;

    bytes_per_word = qspi_configuration->parent.data_width / 8;

    if (message->cs_take && !(qspi_configuration->parent.mode & RT_SPI_NO_CS))
    {
        /* /CS: active */
        /* We just use CS0 only. if you need CS1, please use pin controlling before sending message. */
        spiIoctl(idx, SPI_IOC_ENABLE_SS, SPI_SS_SS0, 0);
    }

    qspi_message = (struct rt_qspi_message *)message;

    /* Command + Address + Dummy + Data */
    /* Command stage */
    if (qspi_message->instruction.content != 0)
    {
        u8last = nu_qspi_mode_config(spi_bus, (rt_uint8_t *) &qspi_message->instruction.content, RT_NULL, qspi_message->instruction.qspi_lines);
        nu_qspi_transfer((struct nu_qspi *)spi_bus,
                         (rt_uint8_t *) &qspi_message->instruction.content,
                         RT_NULL,
                         1,
                         1);
    }

    /* Address stage */
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
        u8last = nu_qspi_mode_config(spi_bus, (rt_uint8_t *)&u32ReversedAddr, RT_NULL, qspi_message->address.qspi_lines);
        nu_qspi_transfer((struct nu_qspi *)spi_bus,
                         (rt_uint8_t *) &u32ReversedAddr,
                         RT_NULL,
                         u32AddrNumOfByte,
                         1);
    }

    /* alternate_bytes stage */
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
        u8last = nu_qspi_mode_config(spi_bus, (rt_uint8_t *)&u32AlternateByte, RT_NULL, qspi_message->alternate_bytes.qspi_lines);
        nu_qspi_transfer((struct nu_qspi *)spi_bus,
                         (rt_uint8_t *) &u32AlternateByte,
                         RT_NULL,
                         u32NumOfByte,
                         1);
    }

    /* Dummy_cycles stage */
    if (qspi_message->dummy_cycles > 0)
    {
        spi_bus->dummy = 0x00;

        u8last = nu_qspi_mode_config(spi_bus, (rt_uint8_t *) &spi_bus->dummy, RT_NULL, u8last);
        nu_qspi_transfer((struct nu_qspi *)spi_bus,
                         (rt_uint8_t *) &spi_bus->dummy,
                         RT_NULL,
                         qspi_message->dummy_cycles / (8 / u8last),
                         1);
    }

    if (message->length > 0)
    {
        /* Data stage */
        nu_qspi_mode_config(spi_bus, (rt_uint8_t *) message->send_buf, (rt_uint8_t *) message->recv_buf, qspi_message->qspi_data_lines);
        nu_qspi_transfer((struct nu_qspi *)spi_bus,
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
        /* /CS: deactive */
        /* We just use CS0 only. if you need CS1, please use pin controlling before sending message. */
        spiIoctl(idx, SPI_IOC_DISABLE_SS, SPI_SS_SS0, 0);
    }

    return u32len;
}

static int nu_qspi_register_bus(struct nu_qspi *spi_bus, const char *name)
{
    return rt_qspi_bus_register(&spi_bus->dev, name, &nu_qspi_poll_ops);
}

/**
 * Hardware SPI Initial
 */
static int rt_hw_qspi_init(void)
{
    int i;

    for (i = (QSPI_START + 1); i < QSPI_CNT; i++)
    {
        nu_sys_ipclk_enable(nu_qspi_arr[i].clkidx);

        nu_sys_ip_reset(nu_qspi_arr[i].rstidx);

        spiOpen(nu_qspi_arr[i].idx);

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

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
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

#endif //#if defined(BSP_USING_SPI)
