#include <stdint.h>
#include <string.h>
#include "board.h"
#include "drv_spim.h"
#include "nrfx_spim.h"
#include "rtconfig.h"
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
/* #define LOG_TAG                "drv.spim" */

#ifdef BSP_USING_SPIM

#if defined(BSP_USING_SPIM0) || defined(BSP_USING_SPIM1) || defined(BSP_USING_SPIM2) || defined(BSP_USING_SPIM3)

static struct nrfx_drv_spim_config spim_config[] =
{
#ifdef BSP_USING_SPIM0
    NRFX_SPIM0_CONFIG,
#endif

#ifdef BSP_USING_SPIM1
    NRFX_SPIM1_CONFIG,
#endif

#ifdef BSP_USING_SPIM2
    NRFX_SPIM2_CONFIG,
#endif

#ifdef BSP_USING_SPIM3
    NRFX_SPIM3_CONFIG,
#endif

};

static struct nrfx_drv_spim spim_bus_obj[sizeof(spim_config) / sizeof(spim_config[0])];

/* Configure SPIM bus pins using the menuconfig */
static struct nrfx_drv_spim_pin_config bsp_spim_pin[] =
{
#ifdef BSP_USING_SPIM0
    {
        .sck_pin  = BSP_SPIM0_SCK_PIN,
        .mosi_pin = BSP_SPIM0_MOSI_PIN,
        .miso_pin = BSP_SPIM0_MISO_PIN,
        .ss_pin   = BSP_SPIM0_SS_PIN
    },
#endif

#ifdef BSP_USING_SPIM1
    {
        .sck_pin  = BSP_SPIM1_SCK_PIN,
        .mosi_pin = BSP_SPIM1_MOSI_PIN,
        .miso_pin = BSP_SPIM1_MISO_PIN,
        .ss_pin   = BSP_SPIM1_SS_PIN
    },
#endif

#ifdef BSP_USING_SPIM2
    {
        .sck_pin  = BSP_SPIM2_SCK_PIN,
        .mosi_pin = BSP_SPIM2_MOSI_PIN,
        .miso_pin = BSP_SPIM2_MISO_PIN,
        .ss_pin   = BSP_SPIM2_SS_PIN
    },
#endif

#ifdef BSP_USING_SPIM3
    {
        .sck_pin  = BSP_SPIM3_SCK_PIN,
        .mosi_pin = BSP_SPIM3_MOSI_PIN,
        .miso_pin = BSP_SPIM3_MISO_PIN,
        .ss_pin   = BSP_SPIM3_SS_PIN
    },
#endif

};

static rt_uint8_t spim_index_find(struct rt_spi_bus *spi_bus)
{
    for (int i = 0; i < sizeof(spim_config) / sizeof(spim_config[0]); i++)
    {
        if(spi_bus == &spim_bus_obj[i].spim_bus)
            return i;
    }
    return 0xFF;
}

/**
 * spi event handler function
 */
#ifdef BSP_USING_SPIM0
static void spim0_handler(const nrfx_spim_evt_t *p_event, void *p_context)
{
    LOG_I("\nspim0_handler");
}
#endif

#ifdef BSP_USING_SPIM1
static void spim1_handler(const nrfx_spim_evt_t *p_event, void *p_context)
{
    LOG_I("\nspim1_handler");
}
#endif

#ifdef BSP_USING_SPIM2
static void spim2_handler(const nrfx_spim_evt_t *p_event, void *p_context)
{
        return;
}
#endif

#ifdef BSP_USING_SPIM3
static void spim3_handler(const nrfx_spim_evt_t *p_event, void *p_context)
{
    return;
}
#endif

nrfx_spim_evt_handler_t spim_handler[] = {
#ifdef BSP_USING_SPIM0
    spim0_handler,
#endif

#ifdef BSP_USING_SPIM1
    spim1_handler,
#endif

#ifdef BSP_USING_SPIM2
    spim2_handler,
#endif

#ifdef BSP_USING_SPIM3
    spim3_handler,
#endif

};

/**
  * @brief  This function config spi bus
  * @param  device
  * @param  configuration
  * @retval RT_EOK / -RT_ERROR
  */
static rt_err_t spim_configure(struct rt_spi_device *device,
                               struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    rt_uint8_t index = spim_index_find(device->bus);
    RT_ASSERT(index != 0xFF);

    nrfx_spim_t spim = spim_bus_obj[index].spim;
    nrfx_spim_config_t config = NRFX_SPIM_DEFAULT_CONFIG(bsp_spim_pin[index].sck_pin,
                                                        bsp_spim_pin[index].mosi_pin,
                                                        bsp_spim_pin[index].miso_pin,
                                                        bsp_spim_pin[index].ss_pin);
    config.ss_active_high = false;

    /* spi config ss pin */

    /* spi config bit order */
    if(configuration->mode & RT_SPI_MSB)
    {
        config.bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;
    }
    else
    {
        config.bit_order = NRF_SPIM_BIT_ORDER_LSB_FIRST;
    }
    /* spi mode config */
    switch (configuration->mode & NRF_SPIM_MODE_3)
    {
    case NRF_SPIM_MODE_0/* RT_SPI_CPOL:0 , RT_SPI_CPHA:0 */:
        config.mode = NRF_SPIM_MODE_0;
        break;
    case NRF_SPIM_MODE_1/* RT_SPI_CPOL:0 , RT_SPI_CPHA:1 */:
        config.mode = NRF_SPIM_MODE_1;
        break;
    case NRF_SPIM_MODE_2/* RT_SPI_CPOL:1 , RT_SPI_CPHA:0 */:
        config.mode = NRF_SPIM_MODE_2;
        break;
    case NRF_SPIM_MODE_3/* RT_SPI_CPOL:1 , RT_SPI_CPHA:1 */:
        config.mode = NRF_SPIM_MODE_3;
        break;
    default:
        LOG_E("spim_configure mode error %x\n",configuration->mode);
        return -RT_ERROR;
    }
    /* spi frequency config */
    switch (configuration->max_hz / 1000)
    {
    case 125:
        config.frequency = NRF_SPIM_FREQ_125K;
        break;
    case 250:
        config.frequency = NRF_SPIM_FREQ_250K;
        break;
    case 500:
        config.frequency = NRF_SPIM_FREQ_500K;
        break;
    case 1000:
        config.frequency = NRF_SPIM_FREQ_1M;
        break;
    case 2000:
        config.frequency = NRF_SPIM_FREQ_2M;
        break;
    case 4000:
        config.frequency = NRF_SPIM_FREQ_4M;
        break;
    case 8000:
        config.frequency = NRF_SPIM_FREQ_8M;
        break;
    case 16000:
        config.frequency = NRF_SPIM_FREQ_16M;
        break;
    case 32000:
        config.frequency = NRF_SPIM_FREQ_32M;
        break;

    default:
        LOG_E("spim_configure rate error %d\n",configuration->max_hz);
        break;
    }

    rt_memcpy((void*)&spim_bus_obj[index].spim_config, (void*)&config, sizeof(nrfx_spim_config_t));

    void * context = RT_NULL;
    nrfx_spim_evt_handler_t handler = RT_NULL;    /* spi send callback handler ,default NULL */

    #if USING_SPI_DMA
        /* create and init completion */
        struct rt_completion *cpt = (struct rt_completion*)rt_malloc(sizeof(struct rt_completion));
        rt_completion_init(cpt);

        /* create and init message about spim */
        struct spi_dma_message *mess = (struct spi_dma_message*)rt_malloc(sizeof(struct spi_dma_message));
        /* step 1 */
        mess->cs_pin         = device->cs_pin;
        /* step 2 */
        mess->cs_take        = 0;
        mess->cs_release     = 0;
        /* step 3 */
        mess->use_hw_ss      = config.use_hw_ss;
        /* step 4 */
        mess->ss_active_high = config.ss_active_high;
        /* step 6 */
        mess->cpt            = cpt;

        context              = (void*)mess;
        handler              = spim_handler[index];
    #endif

    nrfx_err_t nrf_ret = nrfx_spim_init(&spim, &config, handler, context);
    if(NRFX_SUCCESS == nrf_ret)
        return RT_EOK;
    else
        LOG_E("spim configure fail. %x", nrf_ret);

    return -RT_ERROR;
}


static rt_ssize_t spimxfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    rt_uint8_t index = spim_index_find(device->bus);
    nrfx_err_t nrf_ret;
    RT_ASSERT(index != 0xFF);

    nrfx_spim_t * p_instance = &(spim_bus_obj[index].spim);

    nrfx_spim_xfer_desc_t p_xfer_desc = NRFX_SPIM_XFER_TRX(message->send_buf, message->length, message->recv_buf, message->length);

    if(message->send_buf == RT_NULL)
    {
        p_xfer_desc.tx_length = 0;
    }

    if(message->recv_buf == RT_NULL)
    {
        p_xfer_desc.rx_length = 0;
    }

    nrf_ret = rtt_nrfx_spim_xfer(p_instance, &p_xfer_desc, 0, message, device);

    if( NRFX_SUCCESS != nrf_ret)
    {
        LOG_E("SPIM data transfer fail. %x", nrf_ret);
        return 0;
    }
    else
    {
        return message->length;
    }
}


/* spi bus callback function  */
static const struct rt_spi_ops nrfx_spim_ops =
{
    .configure = spim_configure,
    .xfer = spimxfer,
};

/*spim bus init*/
static int rt_hw_spim_bus_init(void)
{
    rt_err_t result = -RT_ERROR;
    for (int i = 0; i < sizeof(spim_config) / sizeof(spim_config[0]); i++)
    {
        spim_bus_obj[i].spim = spim_config[i].spi;
        spim_bus_obj[i].spim_bus.parent.user_data = &spim_config[i];   /* SPI INSTANCE */
        result = rt_spi_bus_register(&spim_bus_obj[i].spim_bus, spim_config[i].bus_name, &nrfx_spim_ops);
        RT_ASSERT(result == RT_EOK);
    }
    return result;
}

int rt_hw_spim_init(void)
{
    return rt_hw_spim_bus_init();
}

INIT_BOARD_EXPORT(rt_hw_spim_init);

#endif /* BSP_USING_SPIM0 || BSP_USING_SPIM1 || BSP_USING_SPIM2 || BSP_USING_SPIM3 */
#endif /*BSP_USING_SPIM*/

