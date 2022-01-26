/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-7-15       YHkuo            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_USPI)

#define LOG_TAG                 "drv.uspi"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <rthw.h>
#include <rtdevice.h>
#include <rtdef.h>

#include "NuMicro.h"
#include <nu_bitutil.h>

#if defined(BSP_USING_USPI_PDMA)
    #include <drv_pdma.h>
#endif
/* Private define ---------------------------------------------------------------*/
enum
{
    USPI_START = -1,
#if defined(BSP_USING_USPI0)
    USPI0_IDX,
#endif
#if defined(BSP_USING_USPI1)
    USPI1_IDX,
#endif
    USPI_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_uspi
{
    struct  rt_spi_bus  dev;
    char    *name;
    USPI_T  *uspi_base;
    struct  rt_spi_configuration    configuration;
    uint32_t    dummy;
#if defined(BSP_USING_USPI_PDMA)
    int16_t pdma_perp_tx;
    int8_t  pdma_chanid_tx;
    int16_t pdma_perp_rx;
    int8_t  pdma_chanid_rx;
    rt_sem_t    m_psSemBus;
#endif
};
typedef struct nu_uspi *uspi_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_uspi_bus_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_uint32_t nu_uspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message);
static void nu_uspi_transmission_with_poll(struct nu_uspi *uspi_bus,
        uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word);
static int nu_uspi_register_bus(struct nu_uspi *uspi_bus, const char *name);
static void nu_uspi_drain_rxfifo(USPI_T *uspi_base);

#if defined(BSP_USING_USPI_PDMA)
    static void nu_pdma_uspi_rx_cb(void *pvUserData, uint32_t u32EventFilter);
    static rt_err_t nu_pdma_uspi_rx_config(struct nu_uspi *uspi_bus, uint8_t *pu8Buf, int32_t i32RcvLen, uint8_t bytes_per_word);
    static rt_err_t nu_pdma_uspi_tx_config(struct nu_uspi *uspi_bus, const uint8_t *pu8Buf, int32_t i32SndLen, uint8_t bytes_per_word);
    static rt_size_t nu_uspi_pdma_transmit(struct nu_uspi *uspi_bus, const uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word);
    static rt_err_t nu_hw_uspi_pdma_allocate(struct nu_uspi *uspi_bus);
#endif
/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static struct rt_spi_ops nu_uspi_poll_ops =
{
    .configure = nu_uspi_bus_configure,
    .xfer      = nu_uspi_bus_xfer,
};

static struct nu_uspi nu_uspi_arr [] =
{
#if defined(BSP_USING_USPI0)
    {
        .name = "uspi0",
        .uspi_base = USPI0,

#if defined(BSP_USING_USPI_PDMA)
#if defined(BSP_USING_USPI0_PDMA)
        .pdma_perp_tx = PDMA_USCI0_TX,
        .pdma_perp_rx = PDMA_USCI0_RX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif  //BSP_USING_USPI0_PDMA
#endif  //BSP_USING_USPI_PDMA
    },
#endif
#if defined(BSP_USING_USPI1)
    {
        .name = "uspi1",
        .uspi_base = USPI1,

#if defined(BSP_USING_USPI_PDMA)
#if defined(BSP_USING_USPI1_PDMA)
        .pdma_perp_tx = PDMA_USCI1_TX,
        .pdma_perp_rx = PDMA_USCI1_RX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif  //BSP_USING_USPI1_PDMA
#endif  //BSP_USING_USPI_PDMA

    },
#endif
    {0}
}; /* uspi nu_uspi */

static rt_err_t nu_uspi_bus_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *configuration)
{
    struct nu_uspi *uspi_bus;
    uint32_t u32SPIMode;
    uint32_t u32BusClock;
    rt_err_t ret = RT_EOK;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    uspi_bus = (struct nu_uspi *) device->bus;

    /* Check mode */
    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        u32SPIMode = USPI_MODE_0;
        break;
    case RT_SPI_MODE_1:
        u32SPIMode = USPI_MODE_1;
        break;
    case RT_SPI_MODE_2:
        u32SPIMode = USPI_MODE_2;
        break;
    case RT_SPI_MODE_3:
        u32SPIMode = USPI_MODE_3;
        break;
    default:
        ret = RT_EIO;
        goto exit_nu_uspi_bus_configure;
    }

    /* Check data width */
    if (!(configuration->data_width == 8  ||
            configuration->data_width == 16))
    {
        ret = RT_EINVAL;
        goto exit_nu_uspi_bus_configure;
    }

    /* Try to set clock and get actual uspi bus clock */
    u32BusClock = USPI_SetBusClock(uspi_bus->uspi_base, configuration->max_hz);
    if (configuration->max_hz > u32BusClock)
    {
        LOG_W("%s clock max frequency is %dHz (!= %dHz)\n", uspi_bus->name, u32BusClock, configuration->max_hz);
        configuration->max_hz = u32BusClock;
    }

    /* Need to initialize new configuration? */
    if (rt_memcmp(configuration, &uspi_bus->configuration, sizeof(*configuration)) != 0)
    {
        rt_memcpy(&uspi_bus->configuration, configuration, sizeof(*configuration));

        USPI_Open(uspi_bus->uspi_base, USPI_MASTER, u32SPIMode, configuration->data_width, u32BusClock);

        if (configuration->mode & RT_SPI_CS_HIGH)
        {
            /* Set CS pin to LOW */
            USPI_SET_SS_LOW(uspi_bus->uspi_base);
        }
        else
        {
            /* Set CS pin to HIGH */
            USPI_SET_SS_HIGH(uspi_bus->uspi_base);
        }

        if (configuration->mode & RT_SPI_MSB)
        {
            /* Set sequence to MSB first */
            USPI_SET_MSB_FIRST(uspi_bus->uspi_base);
        }
        else
        {
            /* Set sequence to LSB first */
            USPI_SET_LSB_FIRST(uspi_bus->uspi_base);
        }
    }

    /* Clear USPI RX FIFO */
    nu_uspi_drain_rxfifo(uspi_bus->uspi_base);

exit_nu_uspi_bus_configure:

    return -(ret);
}

#if defined(BSP_USING_USPI_PDMA)
static void nu_pdma_uspi_rx_cb(void *pvUserData, uint32_t u32EventFilter)
{
    rt_err_t result;
    struct nu_uspi *uspi_bus = (struct nu_uspi *)pvUserData;

    RT_ASSERT(uspi_bus != RT_NULL);

    result = rt_sem_release(uspi_bus->m_psSemBus);
    RT_ASSERT(result == RT_EOK);
}

static rt_err_t nu_pdma_uspi_rx_config(struct nu_uspi *uspi_bus, uint8_t *pu8Buf, int32_t i32RcvLen, uint8_t bytes_per_word)
{
    rt_err_t result;
    rt_uint8_t *dst_addr = NULL;
    nu_pdma_memctrl_t memctrl = eMemCtl_Undefined;

    /* Get base address of uspi register */
    USPI_T *uspi_base = uspi_bus->uspi_base;

    rt_uint8_t uspi_pdma_rx_chid = uspi_bus->pdma_chanid_rx;

    result = nu_pdma_callback_register(uspi_pdma_rx_chid,
                                       nu_pdma_uspi_rx_cb,
                                       (void *)uspi_bus,
                                       NU_PDMA_EVENT_TRANSFER_DONE);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uspi_rx_config;
    }

    if (pu8Buf == RT_NULL)
    {
        memctrl  = eMemCtl_SrcFix_DstFix;
        dst_addr = (rt_uint8_t *) &uspi_bus->dummy;
    }
    else
    {
        memctrl  = eMemCtl_SrcFix_DstInc;
        dst_addr = pu8Buf;
    }

    result = nu_pdma_channel_memctrl_set(uspi_pdma_rx_chid, memctrl);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uspi_rx_config;
    }

    result = nu_pdma_transfer(uspi_pdma_rx_chid,
                              bytes_per_word * 8,
                              (uint32_t)&uspi_base->RXDAT,
                              (uint32_t)dst_addr,
                              i32RcvLen / bytes_per_word,
                              0);

exit_nu_pdma_uspi_rx_config:

    return result;
}

static rt_err_t nu_pdma_uspi_tx_config(struct nu_uspi *uspi_bus, const uint8_t *pu8Buf, int32_t i32SndLen, uint8_t bytes_per_word)
{
    rt_err_t result;
    rt_uint8_t *src_addr = NULL;
    nu_pdma_memctrl_t memctrl = eMemCtl_Undefined;

    /* Get base address of uspi register */
    USPI_T *uspi_base = uspi_bus->uspi_base;

    rt_uint8_t uspi_pdma_tx_chid = uspi_bus->pdma_chanid_tx;

    if (pu8Buf == RT_NULL)
    {
        uspi_bus->dummy = 0;
        memctrl = eMemCtl_SrcFix_DstFix;
        src_addr = (rt_uint8_t *)&uspi_bus->dummy;
    }
    else
    {
        memctrl = eMemCtl_SrcInc_DstFix;
        src_addr = (rt_uint8_t *)pu8Buf;
    }

    result = nu_pdma_channel_memctrl_set(uspi_pdma_tx_chid, memctrl);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uspi_tx_config;
    }

    result = nu_pdma_transfer(uspi_pdma_tx_chid,
                              bytes_per_word * 8,
                              (uint32_t)src_addr,
                              (uint32_t)&uspi_base->TXDAT,
                              i32SndLen / bytes_per_word,
                              0);

exit_nu_pdma_uspi_tx_config:

    return result;
}


/**
 * USPI PDMA transfer
 **/
static rt_size_t nu_uspi_pdma_transmit(struct nu_uspi *uspi_bus, const uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word)
{
    rt_err_t result;

    /* Get base address of uspi register */
    USPI_T *uspi_base = uspi_bus->uspi_base;

    result = nu_pdma_uspi_rx_config(uspi_bus, recv_addr, length, bytes_per_word);
    RT_ASSERT(result == RT_EOK);
    result = nu_pdma_uspi_tx_config(uspi_bus, send_addr, length, bytes_per_word);
    RT_ASSERT(result == RT_EOK);

    /* Trigger TX/RX at the same time. */
    USPI_TRIGGER_TX_RX_PDMA(uspi_base);

    /* Wait PDMA transfer done */
    result = rt_sem_take(uspi_bus->m_psSemBus, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Stop DMA TX/RX transfer */
    USPI_DISABLE_TX_RX_PDMA(uspi_base);

    return result;
}

static rt_err_t nu_hw_uspi_pdma_allocate(struct nu_uspi *uspi_bus)
{
    /* Allocate USPI_TX nu_dma channel */
    if ((uspi_bus->pdma_chanid_tx = nu_pdma_channel_allocate(uspi_bus->pdma_perp_tx)) < 0)
    {
        goto exit_nu_hw_uspi_pdma_allocate;
    }
    /* Allocate USPI_RX nu_dma channel */
    else if ((uspi_bus->pdma_chanid_rx = nu_pdma_channel_allocate(uspi_bus->pdma_perp_rx)) < 0)
    {
        nu_pdma_channel_free(uspi_bus->pdma_chanid_tx);
        goto exit_nu_hw_uspi_pdma_allocate;
    }

    uspi_bus->m_psSemBus = rt_sem_create("uspibus_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(uspi_bus->m_psSemBus != RT_NULL);

    return RT_EOK;

exit_nu_hw_uspi_pdma_allocate:

    return -(RT_ERROR);
}

#endif

static void nu_uspi_drain_rxfifo(USPI_T *uspi_base)
{
    while (USPI_IS_BUSY(uspi_base));

    // Drain USPI RX FIFO, make sure RX FIFO is empty
    while (!USPI_GET_RX_EMPTY_FLAG(uspi_base))
    {
        USPI_ClearRxBuf(uspi_base);
    }
}

static int nu_uspi_read(USPI_T *uspi_base, uint8_t *recv_addr, uint8_t bytes_per_word)
{
    int size = 0;

    // Read RX data
    if (!USPI_GET_RX_EMPTY_FLAG(uspi_base))
    {
        uint32_t val;
        // Read data from USPI RX FIFO
        switch (bytes_per_word)
        {
        case 2:
            val = USPI_READ_RX(uspi_base);
            nu_set16_le(recv_addr, val);
            break;
        case 1:
            *recv_addr = USPI_READ_RX(uspi_base);
            break;
        default:
            LOG_E("Data length is not supported.\n");
            break;
        }
        size = bytes_per_word;
    }
    return size;
}

static int nu_uspi_write(USPI_T *uspi_base, const uint8_t *send_addr, uint8_t bytes_per_word)
{
    // Wait USPI TX send data
    while (USPI_GET_TX_FULL_FLAG(uspi_base));

    // Input data to USPI TX
    switch (bytes_per_word)
    {
    case 2:
        USPI_WRITE_TX(uspi_base, nu_get16_le(send_addr));
        break;
    case 1:
        USPI_WRITE_TX(uspi_base, *((uint8_t *)send_addr));
        break;
    default:
        LOG_E("Data length is not supported.\n");
        break;
    }

    return bytes_per_word;
}

/**
 * @brief USPI bus polling
 * @param dev : The pointer of the specified USPI module.
 * @param send_addr : Source address
 * @param recv_addr : Destination address
 * @param length    : Data length
 */
static void nu_uspi_transmission_with_poll(struct nu_uspi *uspi_bus,
        uint8_t *send_addr, uint8_t *recv_addr, int length, uint8_t bytes_per_word)
{
    USPI_T *uspi_base = uspi_bus->uspi_base;

    // Write-only
    if ((send_addr != RT_NULL) && (recv_addr == RT_NULL))
    {
        while (length > 0)
        {
            send_addr += nu_uspi_write(uspi_base, send_addr, bytes_per_word);
            length -= bytes_per_word;
        }
    } // if (send_addr != RT_NULL && recv_addr == RT_NULL)
    // Read-only
    else if ((send_addr == RT_NULL) && (recv_addr != RT_NULL))
    {
        uspi_bus->dummy = 0;
        while (length > 0)
        {
            /* Input data to USPI TX FIFO */
            length -= nu_uspi_write(uspi_base, (const uint8_t *)&uspi_bus->dummy, bytes_per_word);

            /* Read data from USPI RX FIFO */
            while (USPI_GET_RX_EMPTY_FLAG(uspi_base));
            recv_addr += nu_uspi_read(uspi_base, recv_addr, bytes_per_word);
        }
    } // else if (send_addr == RT_NULL && recv_addr != RT_NULL)
    // Read&Write
    else
    {
        while (length > 0)
        {
            /* Input data to USPI TX FIFO */
            send_addr += nu_uspi_write(uspi_base, send_addr, bytes_per_word);
            length -= bytes_per_word;

            /* Read data from USPI RX FIFO */
            while (USPI_GET_RX_EMPTY_FLAG(uspi_base));
            recv_addr += nu_uspi_read(uspi_base, recv_addr, bytes_per_word);
        }
    } // else

    /* Wait USPI RX or drain USPI RX-FIFO */
    if (recv_addr)
    {
        // Wait USPI transmission done
        while (USPI_IS_BUSY(uspi_base))
        {
            while (!USPI_GET_RX_EMPTY_FLAG(uspi_base))
            {
                recv_addr += nu_uspi_read(uspi_base, recv_addr, bytes_per_word);
            }
        }

        while (!USPI_GET_RX_EMPTY_FLAG(uspi_base))
        {
            recv_addr += nu_uspi_read(uspi_base, recv_addr, bytes_per_word);
        }
    }
    else
    {
        /* Clear USPI RX FIFO */
        nu_uspi_drain_rxfifo(uspi_base);
    }
}

static void nu_uspi_transfer(struct nu_uspi *uspi_bus, uint8_t *tx, uint8_t *rx, int length, uint8_t bytes_per_word)
{
#if defined(BSP_USING_USPI_PDMA)
    /* PDMA transfer constrains */
    if ((uspi_bus->pdma_chanid_rx >= 0) &&
            (!((uint32_t)tx % bytes_per_word)) &&
            (!((uint32_t)rx % bytes_per_word)))
        nu_uspi_pdma_transmit(uspi_bus, tx, rx, length, bytes_per_word);
    else
        nu_uspi_transmission_with_poll(uspi_bus, tx, rx, length, bytes_per_word);
#else
    nu_uspi_transmission_with_poll(uspi_bus, tx, rx, length, bytes_per_word);
#endif
}

static rt_uint32_t nu_uspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct nu_uspi *uspi_bus;
    struct rt_spi_configuration *configuration;
    uint8_t bytes_per_word;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    uspi_bus = (struct nu_uspi *) device->bus;
    configuration = &uspi_bus->configuration;
    bytes_per_word = configuration->data_width / 8;

    if ((message->length % bytes_per_word) != 0)
    {
        /* Say bye. */
        LOG_E("%s: error payload length(%d%%%d != 0).\n", uspi_bus->name, message->length, bytes_per_word);
        return 0;
    }

    if (message->length > 0)
    {
        if (message->cs_take && !(configuration->mode & RT_SPI_NO_CS))
        {
            if (configuration->mode & RT_SPI_CS_HIGH)
            {
                USPI_SET_SS_HIGH(uspi_bus->uspi_base);
            }
            else
            {
                USPI_SET_SS_LOW(uspi_bus->uspi_base);
            }
        }

        nu_uspi_transfer(uspi_bus, (uint8_t *)message->send_buf, (uint8_t *)message->recv_buf, message->length, bytes_per_word);

        if (message->cs_release && !(configuration->mode & RT_SPI_NO_CS))
        {
            if (configuration->mode & RT_SPI_CS_HIGH)
            {
                USPI_SET_SS_LOW(uspi_bus->uspi_base);
            }
            else
            {
                USPI_SET_SS_HIGH(uspi_bus->uspi_base);
            }
        }

    }

    return message->length;
}

static int nu_uspi_register_bus(struct nu_uspi *uspi_bus, const char *name)
{
    return rt_spi_bus_register(&uspi_bus->dev, name, &nu_uspi_poll_ops);
}

/**
 * Hardware USPI Initial
 */
static int rt_hw_uspi_init(void)
{
    int i;

    for (i = (USPI_START + 1); i < USPI_CNT; i++)
    {
        nu_uspi_register_bus(&nu_uspi_arr[i], nu_uspi_arr[i].name);
#if defined(BSP_USING_USPI_PDMA)
        nu_uspi_arr[i].pdma_chanid_tx = -1;
        nu_uspi_arr[i].pdma_chanid_rx = -1;
        if ((nu_uspi_arr[i].pdma_perp_tx != NU_PDMA_UNUSED) && (nu_uspi_arr[i].pdma_perp_rx != NU_PDMA_UNUSED))
        {
            if (nu_hw_uspi_pdma_allocate(&nu_uspi_arr[i]) != RT_EOK)
            {
                LOG_E("Failed to allocate DMA channels for %s. We will use poll-mode for this bus.\n", nu_uspi_arr[i].name);
            }
        }
#endif
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_uspi_init);

#endif //#if defined(BSP_USING_USPI)
