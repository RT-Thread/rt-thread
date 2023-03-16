/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-01-19      klcheng          First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_SPI)

#define LOG_TAG                 "drv.spi"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <rthw.h>
#include <rtdevice.h>
#include <rtdef.h>

#include <drv_spi.h>


/* Private define ---------------------------------------------------------------*/

#ifndef NU_SPI_USE_PDMA_MIN_THRESHOLD
    #define NU_SPI_USE_PDMA_MIN_THRESHOLD (128)
#endif

enum
{
    SPI_START = -1,
#if defined(BSP_USING_SPI0)
    SPI0_IDX,
#endif
    SPI_CNT
};

/* Private typedef --------------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/
static void nu_spi_transmission_with_poll(struct nu_spi *spi_bus,
        uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word);
static int nu_spi_register_bus(struct nu_spi *spi_bus, const char *name);
static rt_uint32_t nu_spi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message);
static rt_err_t nu_spi_bus_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);

#if defined(BSP_USING_SPI_PDMA)
    static void nu_pdma_spi_rx_cb(void *pvUserData, uint32_t u32EventFilter);
    static rt_err_t nu_pdma_spi_rx_config(struct nu_spi *spi_bus, uint8_t *pu8Buf, int32_t i32RcvLen, uint8_t bytes_per_word);
    static rt_err_t nu_pdma_spi_tx_config(struct nu_spi *spi_bus, const uint8_t *pu8Buf, int32_t i32SndLen, uint8_t bytes_per_word);
    static rt_ssize_t nu_spi_pdma_transmit(struct nu_spi *spi_bus, const uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word);
#endif
/* Public functions -------------------------------------------------------------*/
void nu_spi_transfer(struct nu_spi *spi_bus, uint8_t *tx, uint8_t *rx, int length, uint8_t bytes_per_word);
void nu_spi_drain_rxfifo(SPI_T *spi_base);

/* Private variables ------------------------------------------------------------*/
static struct rt_spi_ops nu_spi_poll_ops =
{
    .configure = nu_spi_bus_configure,
    .xfer      = nu_spi_bus_xfer,
};

static struct nu_spi nu_spi_arr [] =
{
#if defined(BSP_USING_SPI0)
    {
        .name = "spi0",
        .spi_base = SPI0,

#if defined(BSP_USING_SPI_PDMA)
#if defined(BSP_USING_SPI0_PDMA)
        .pdma_perp_tx = PDMA_SPI0_TX,
        .pdma_perp_rx = PDMA_SPI0_RX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif
    {0}
}; /* spi nu_spi */

static rt_err_t nu_spi_bus_configure(struct rt_spi_device *device,
                                     struct rt_spi_configuration *configuration)
{
    struct nu_spi *spi_bus;
    uint32_t u32SPIMode;
    uint32_t u32BusClock;
    rt_err_t ret = RT_EOK;
    void *pvUserData;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    spi_bus = (struct nu_spi *) device->bus;
    pvUserData = device->parent.user_data;

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
        goto exit_nu_spi_bus_configure;
    }

    /* Check data width */
    if (!(configuration->data_width == 8  ||
            configuration->data_width == 16 ||
            configuration->data_width == 24 ||
            configuration->data_width == 32))
    {
        ret = -RT_EINVAL;
        goto exit_nu_spi_bus_configure;
    }

    /* Try to set clock and get actual spi bus clock */
    u32BusClock = SPI_SetBusClock(spi_bus->spi_base, configuration->max_hz);
    if (configuration->max_hz > u32BusClock)
    {
        LOG_W("%s clock max frequency is %dHz (!= %dHz)\n", spi_bus->name, u32BusClock, configuration->max_hz);
        configuration->max_hz = u32BusClock;
    }

    /* Need to initialize new configuration? */
    if (rt_memcmp(configuration, &spi_bus->configuration, sizeof(*configuration)) != 0)
    {
        rt_memcpy(&spi_bus->configuration, configuration, sizeof(*configuration));

        SPI_Open(spi_bus->spi_base, SPI_MASTER, u32SPIMode, configuration->data_width, u32BusClock);

        if (configuration->mode & RT_SPI_CS_HIGH)
        {
            /* Set CS pin to LOW */
            if (pvUserData != RT_NULL)
            {
                // set to LOW */
                rt_pin_write(*((rt_base_t *)pvUserData), PIN_LOW);
            }
            else
            {
                SPI_SET_SS_LOW(spi_bus->spi_base);
            }
        }
        else
        {
            /* Set CS pin to HIGH */
            if (pvUserData != RT_NULL)
            {
                // set to HIGH */
                rt_pin_write(*((rt_base_t *)pvUserData), PIN_HIGH);
            }
            else
            {
                /* Set CS pin to HIGH */
                SPI_SET_SS_HIGH(spi_bus->spi_base);
            }
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

    /* Clear SPI RX FIFO */
    nu_spi_drain_rxfifo(spi_bus->spi_base);

exit_nu_spi_bus_configure:

    return -(ret);
}

#if defined(BSP_USING_SPI_PDMA)
static void nu_pdma_spi_rx_cb(void *pvUserData, uint32_t u32EventFilter)
{
    rt_err_t result;
    struct nu_spi *spi_bus = (struct nu_spi *)pvUserData;

    RT_ASSERT(spi_bus != RT_NULL);

    result = rt_sem_release(spi_bus->m_psSemBus);
    RT_ASSERT(result == RT_EOK);
}
static rt_err_t nu_pdma_spi_rx_config(struct nu_spi *spi_bus, uint8_t *pu8Buf, int32_t i32RcvLen, uint8_t bytes_per_word)
{
    rt_err_t result = RT_EOK;
    rt_uint8_t *dst_addr = NULL;
    nu_pdma_memctrl_t memctrl = eMemCtl_Undefined;

    /* Get base address of spi register */
    SPI_T *spi_base = spi_bus->spi_base;

    rt_uint8_t spi_pdma_rx_chid = spi_bus->pdma_chanid_rx;

    result = nu_pdma_callback_register(spi_pdma_rx_chid,
                                       nu_pdma_spi_rx_cb,
                                       (void *)spi_bus,
                                       NU_PDMA_EVENT_TRANSFER_DONE);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_spi_rx_config;
    }

    if (pu8Buf == RT_NULL)
    {
        memctrl  = eMemCtl_SrcFix_DstFix;
        dst_addr = (rt_uint8_t *) &spi_bus->dummy;
    }
    else
    {
        memctrl  = eMemCtl_SrcFix_DstInc;
        dst_addr = pu8Buf;
    }

    result = nu_pdma_channel_memctrl_set(spi_pdma_rx_chid, memctrl);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_spi_rx_config;
    }

    result = nu_pdma_transfer(spi_pdma_rx_chid,
                              bytes_per_word * 8,
                              (uint32_t)&spi_base->RX,
                              (uint32_t)dst_addr,
                              i32RcvLen / bytes_per_word,
                              0);
exit_nu_pdma_spi_rx_config:

    return result;
}

static rt_err_t nu_pdma_spi_tx_config(struct nu_spi *spi_bus, const uint8_t *pu8Buf, int32_t i32SndLen, uint8_t bytes_per_word)
{
    rt_err_t result = RT_EOK;
    rt_uint8_t *src_addr = NULL;
    nu_pdma_memctrl_t memctrl = eMemCtl_Undefined;

    /* Get base address of spi register */
    SPI_T *spi_base = spi_bus->spi_base;

    rt_uint8_t spi_pdma_tx_chid = spi_bus->pdma_chanid_tx;

    if (pu8Buf == RT_NULL)
    {
        spi_bus->dummy = 0;
        memctrl = eMemCtl_SrcFix_DstFix;
        src_addr = (rt_uint8_t *)&spi_bus->dummy;
    }
    else
    {
        memctrl = eMemCtl_SrcInc_DstFix;
        src_addr = (rt_uint8_t *)pu8Buf;
    }

    result = nu_pdma_channel_memctrl_set(spi_pdma_tx_chid, memctrl);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_spi_tx_config;
    }

    result = nu_pdma_transfer(spi_pdma_tx_chid,
                              bytes_per_word * 8,
                              (uint32_t)src_addr,
                              (uint32_t)&spi_base->TX,
                              i32SndLen / bytes_per_word,
                              0);
exit_nu_pdma_spi_tx_config:

    return result;
}


/**
 * SPI PDMA transfer
 */
static rt_ssize_t nu_spi_pdma_transmit(struct nu_spi *spi_bus, const uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t u32Offset = 0;
    rt_uint32_t u32TransferCnt = length / bytes_per_word;
    rt_uint32_t u32TxCnt = 0;

    /* Get base address of spi register */
    SPI_T *spi_base = spi_bus->spi_base;

    do
    {
        u32TxCnt = (u32TransferCnt > NU_PDMA_MAX_TXCNT) ? NU_PDMA_MAX_TXCNT : u32TransferCnt;
        result = nu_pdma_spi_rx_config(spi_bus, (recv_addr == RT_NULL) ? recv_addr : &recv_addr[u32Offset], (u32TxCnt * bytes_per_word), bytes_per_word);
        RT_ASSERT(result == RT_EOK);

        result = nu_pdma_spi_tx_config(spi_bus, (send_addr == RT_NULL) ? send_addr : &send_addr[u32Offset], (u32TxCnt * bytes_per_word), bytes_per_word);
        RT_ASSERT(result == RT_EOK);

        /* Trigger TX/RX PDMA transfer. */
        SPI_TRIGGER_TX_RX_PDMA(spi_base);

        /* Wait RX-PDMA transfer done */
        result = rt_sem_take(spi_bus->m_psSemBus, RT_WAITING_FOREVER);
        RT_ASSERT(result == RT_EOK);

        /* Stop TX/RX DMA transfer. */
        SPI_DISABLE_TX_RX_PDMA(spi_base);

        u32TransferCnt -= u32TxCnt;
        u32Offset += u32TxCnt;

    }
    while (u32TransferCnt > 0);

    return length;
}

rt_err_t nu_hw_spi_pdma_allocate(struct nu_spi *spi_bus)
{
    /* Allocate SPI_TX nu_dma channel */
    if ((spi_bus->pdma_chanid_tx = nu_pdma_channel_allocate(spi_bus->pdma_perp_tx)) < 0)
    {
        goto exit_nu_hw_spi_pdma_allocate;
    }
    /* Allocate SPI_RX nu_dma channel */
    else if ((spi_bus->pdma_chanid_rx = nu_pdma_channel_allocate(spi_bus->pdma_perp_rx)) < 0)
    {
        nu_pdma_channel_free(spi_bus->pdma_chanid_tx);
        goto exit_nu_hw_spi_pdma_allocate;
    }

    spi_bus->m_psSemBus = rt_sem_create("spibus_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(spi_bus->m_psSemBus != RT_NULL);

    return RT_EOK;

exit_nu_hw_spi_pdma_allocate:

    return -(RT_ERROR);
}
#endif /* #if defined(BSP_USING_SPI_PDMA) */

void nu_spi_drain_rxfifo(SPI_T *spi_base)
{
    while (SPI_IS_BUSY(spi_base));

    // Drain SPI RX FIFO, make sure RX FIFO is empty
    while (!SPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
    {
        SPI_ClearRxFIFO(spi_base);
    }
}

static int nu_spi_read(SPI_T *spi_base, uint8_t *recv_addr, uint8_t bytes_per_word)
{
    int size = 0;

    // Read RX data
    if (!SPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
    {
        uint32_t val;
        // Read data from SPI RX FIFO
        switch (bytes_per_word)
        {
        case 4:
            val = SPI_READ_RX(spi_base);
            nu_set32_le(recv_addr, val);
            break;
        case 3:
            val = SPI_READ_RX(spi_base);
            nu_set24_le(recv_addr, val);
            break;
        case 2:
            val = SPI_READ_RX(spi_base);
            nu_set16_le(recv_addr, val);
            break;
        case 1:
            *recv_addr = SPI_READ_RX(spi_base);
            break;
        default:
            LOG_E("Data length is not supported.\n");
            break;
        }
        size = bytes_per_word;
    }
    return size;
}

static int nu_spi_write(SPI_T *spi_base, const uint8_t *send_addr, uint8_t bytes_per_word)
{
    // Wait SPI TX send data
    while (SPI_GET_TX_FIFO_FULL_FLAG(spi_base));

    // Input data to SPI TX
    switch (bytes_per_word)
    {
    case 4:
        SPI_WRITE_TX(spi_base, nu_get32_le(send_addr));
        break;
    case 3:
        SPI_WRITE_TX(spi_base, nu_get24_le(send_addr));
        break;
    case 2:
        SPI_WRITE_TX(spi_base, nu_get16_le(send_addr));
        break;
    case 1:
        SPI_WRITE_TX(spi_base, *((uint8_t *)send_addr));
        break;
    default:
        LOG_E("Data length is not supported.\n");
        break;
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
static void nu_spi_transmission_with_poll(struct nu_spi *spi_bus,
        uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word)
{
    SPI_T *spi_base = spi_bus->spi_base;

    // Write-only
    if ((send_addr != RT_NULL) && (recv_addr == RT_NULL))
    {
        while (length > 0)
        {
            send_addr += nu_spi_write(spi_base, send_addr, bytes_per_word);
            length -= bytes_per_word;
        }
    } // if (send_addr != RT_NULL && recv_addr == RT_NULL)
    // Read-only
    else if ((send_addr == RT_NULL) && (recv_addr != RT_NULL))
    {
        spi_bus->dummy = 0;
        while (length > 0)
        {
            /* Input data to SPI TX FIFO */
            length -= nu_spi_write(spi_base, (const uint8_t *)&spi_bus->dummy, bytes_per_word);

            /* Read data from RX FIFO */
            recv_addr += nu_spi_read(spi_base, recv_addr, bytes_per_word);
        }
    } // else if (send_addr == RT_NULL && recv_addr != RT_NULL)
    // Read&Write
    else
    {
        while (length > 0)
        {
            /* Input data to SPI TX FIFO */
            send_addr += nu_spi_write(spi_base, send_addr, bytes_per_word);
            length -= bytes_per_word;

            /* Read data from RX FIFO */
            recv_addr += nu_spi_read(spi_base, recv_addr, bytes_per_word);
        }
    } // else

    /* Wait RX or drain RX-FIFO */
    if (recv_addr)
    {
        // Wait SPI transmission done
        while (SPI_IS_BUSY(spi_base))
        {
            while (!SPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                recv_addr += nu_spi_read(spi_base, recv_addr, bytes_per_word);
            }
        }

        while (!SPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            recv_addr += nu_spi_read(spi_base, recv_addr, bytes_per_word);
        }
    }
    else
    {
        /* Clear SPI RX FIFO */
        nu_spi_drain_rxfifo(spi_base);
    }
}

void nu_spi_transfer(struct nu_spi *spi_bus, uint8_t *tx, uint8_t *rx, int length, uint8_t bytes_per_word)
{
    RT_ASSERT(spi_bus != RT_NULL);

#if defined(BSP_USING_SPI_PDMA)
    /* DMA transfer constrains */
    if ((spi_bus->pdma_chanid_rx >= 0) &&
            !((uint32_t)tx % bytes_per_word) &&
            !((uint32_t)rx % bytes_per_word) &&
            (bytes_per_word != 3) &&
            (length >= NU_SPI_USE_PDMA_MIN_THRESHOLD))
        nu_spi_pdma_transmit(spi_bus, tx, rx, length, bytes_per_word);
    else
        nu_spi_transmission_with_poll(spi_bus, tx, rx, length, bytes_per_word);
#else
    nu_spi_transmission_with_poll(spi_bus, tx, rx, length, bytes_per_word);
#endif
}

static rt_uint32_t nu_spi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct nu_spi *spi_bus;
    struct rt_spi_configuration *configuration;
    uint8_t bytes_per_word;
    void *pvUserData;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    spi_bus = (struct nu_spi *) device->bus;
    configuration = (struct rt_spi_configuration *)&spi_bus->configuration;
    bytes_per_word = configuration->data_width / 8;
    pvUserData = device->parent.user_data;

    if ((message->length % bytes_per_word) != 0)
    {
        /* Say bye. */
        LOG_E("%s: error payload length(%d%%%d != 0).\n", spi_bus->name, message->length, bytes_per_word);
        return 0;
    }

    if (message->length > 0)
    {
        if (message->cs_take && !(configuration->mode & RT_SPI_NO_CS))
        {
            if (pvUserData != RT_NULL)
            {
                if (configuration->mode & RT_SPI_CS_HIGH)
                {
                    // set to HIGH */
                    rt_pin_write(*((rt_base_t *)pvUserData), PIN_HIGH);
                }
                else
                {
                    // set to LOW */
                    rt_pin_write(*((rt_base_t *)pvUserData), PIN_LOW);
                }
            }
            else
            {
                if (configuration->mode & RT_SPI_CS_HIGH)
                {
                    SPI_SET_SS_HIGH(spi_bus->spi_base);
                }
                else
                {
                    SPI_SET_SS_LOW(spi_bus->spi_base);
                }
            }
        }

        nu_spi_transfer(spi_bus, (uint8_t *)message->send_buf, (uint8_t *)message->recv_buf, message->length, bytes_per_word);

        if (message->cs_release && !(configuration->mode & RT_SPI_NO_CS))
        {
            if (pvUserData != RT_NULL)
            {
                if (configuration->mode & RT_SPI_CS_HIGH)
                {
                    // set to LOW */
                    rt_pin_write(*((rt_base_t *)pvUserData), PIN_LOW);
                }
                else
                {
                    // set to HIGH */
                    rt_pin_write(*((rt_base_t *)pvUserData), PIN_HIGH);
                }
            }
            else
            {
                if (configuration->mode & RT_SPI_CS_HIGH)
                {
                    SPI_SET_SS_LOW(spi_bus->spi_base);
                }
                else
                {
                    SPI_SET_SS_HIGH(spi_bus->spi_base);
                }
            }
        }

    }

    return message->length;
}

static int nu_spi_register_bus(struct nu_spi *spi_bus, const char *name)
{
    return rt_spi_bus_register(&spi_bus->dev, name, &nu_spi_poll_ops);
}

/**
 * Hardware SPI Initial
 */
static int rt_hw_spi_init(void)
{
    int i;

    for (i = (SPI_START + 1); i < SPI_CNT; i++)
    {
        nu_spi_register_bus(&nu_spi_arr[i], nu_spi_arr[i].name);
#if defined(BSP_USING_SPI_PDMA)
        nu_spi_arr[i].pdma_chanid_tx = -1;
        nu_spi_arr[i].pdma_chanid_rx = -1;
        if ((nu_spi_arr[i].pdma_perp_tx != NU_PDMA_UNUSED) && (nu_spi_arr[i].pdma_perp_rx != NU_PDMA_UNUSED))
        {
            if (nu_hw_spi_pdma_allocate(&nu_spi_arr[i]) != RT_EOK)
            {
                LOG_W("Failed to allocate DMA channels for %s. We will use poll-mode for this bus.\n", nu_spi_arr[i].name);
            }
        }
#endif
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_spi_init);

#endif //#if defined(BSP_USING_SPI)
