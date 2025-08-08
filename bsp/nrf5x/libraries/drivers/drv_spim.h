#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#ifndef __DRV_SPIM_H_
#define __DRV_SPIM_H_

#ifdef BSP_USING_SPIM

#include "nrfx_spim.h"
#include "nrf_spi.h"
#include "rtconfig.h"

#define USING_SPI_DMA 1

#if USING_SPI_DMA

struct spi_dma_message
{
    rt_base_t cs_pin;
    unsigned cs_take;
    unsigned cs_release;
    #if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
    bool use_hw_ss;
    #endif
    bool ss_active_high;
    struct rt_completion *cpt;
    uint32_t flags;
    NRF_SPIM_Type* spim;

};

#endif

/**
 * @brief Attach the spi device to SPIM bus, this function must be used after initialization.
 * @param bus_name     spim bus name  "spim0"/"spim1"/"spim2"/"spim3"
 * @param device_name  spim device name "spim0x"/"spim1x"/"spim2x"/"spim3x"
 * @param ss_pin       spim ss pin number
 * @retval  -RT_ERROR / RT_EOK
*/
rt_err_t rt_hw_spim_device_attach(const char *bus_name, const char *device_name, rt_uint32_t ss_pin);

/* SPIM bus config */
#ifdef BSP_USING_SPIM0
#define NRFX_SPIM0_CONFIG         \
{                                \
    .bus_name = "spim0",          \
    .spi = NRFX_SPIM_INSTANCE(0)  \
}
#endif
#ifdef BSP_USING_SPIM1
#define NRFX_SPIM1_CONFIG         \
{                                \
    .bus_name = "spim1",          \
    .spi = NRFX_SPIM_INSTANCE(1)  \
}
#endif

#ifdef BSP_USING_SPIM2
#define NRFX_SPIM2_CONFIG         \
{                                \
    .bus_name = "spim2",          \
    .spi = NRFX_SPIM_INSTANCE(2)  \
}
#endif

#ifdef BSP_USING_SPIM3
#define NRFX_SPIM3_CONFIG         \
{                                \
    .bus_name = "spim3",          \
    .spi = NRFX_SPIM_INSTANCE(3)  \
}
#endif


struct nrfx_drv_spim_config
{
    char *bus_name;
    nrfx_spim_t spi;
};

struct nrfx_drv_spim
{
    nrfx_spim_t spim;    /* nrfx spim driver instance. */
    nrfx_spim_config_t   spim_config; /* nrfx spim config Configuration */
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spim_bus;
};

struct nrfx_drv_spim_pin_config
{
    rt_uint8_t sck_pin;
    rt_uint8_t mosi_pin;
    rt_uint8_t miso_pin;
    rt_uint8_t ss_pin;
};

#endif /* BSP_USING_SPIM */

#endif /* __DRV_SPIM_H_ */

