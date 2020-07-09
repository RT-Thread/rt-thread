#include <rtdevice.h>
#include <string.h>

#include "platform.h"

#ifdef RT_USING_I2C
#include "drv_i2c.h"
#endif

#ifdef RT_USING_SPI
#include "drv_ssi.h"
#endif

#include "gd_gpio.h"

#ifdef RT_USING_ADC
#include "drv_adc.h"
#endif
#ifdef RT_USING_PWM
#include "drv_pwm.h"
#endif
#ifdef RT_USING_WDT
#include "drv_wdt.h"
#endif

#ifdef RT_USING_SDIO
#include "drv_sdio.h"
#endif


struct gk_platform_device
{
    char *name;
    void *private_data;
};

#ifdef RT_USING_I2C

static struct gk_i2c_obj i2c0_obj = {
    .id = 0,
    .config = {
        .i2cInitParams.priority      = 1,//!< Interrupt Request (IRQ) for more general interrupts
        .i2cInitParams.mode          = 2,//!< Auto master mode.
        .i2cInitParams.gpioSclPinCh1 = -1,
        .i2cInitParams.gpioSdaPinCh1 = -1,
        .i2cInitParams.gpioSclPinCh2 = -1,
        .i2cInitParams.gpioSdaPinCh2 = -1,

    },
};

static struct gk_i2c_obj i2c1_obj = {
    .id = 1,
    .config = {
        .i2cInitParams.priority      = 1,//!< Interrupt Request (IRQ) for more general interrupts
        .i2cInitParams.mode          = 2,//!< Auto master mode.
        .i2cInitParams.gpioSclPinCh1 = -1,
        .i2cInitParams.gpioSdaPinCh1 = -1,
        .i2cInitParams.gpioSclPinCh2 = -1,
        .i2cInitParams.gpioSdaPinCh2 = -1,
    },
};


struct gk_platform_device plat_i2c0 = {
    .name = "i2c", .private_data = &i2c0_obj,
};

struct gk_platform_device plat_i2c1 = {
    .name = "i2c", .private_data = &i2c1_obj,
};
#endif

#ifdef RT_USING_SPI

static struct gk_spi_controller_data spi0_controller_data =
{
    .id                = 0,
    .total_slave       = 1,
    .slave_cs_pin[0]   = GD_GPIO_14,//AT25640B eeprom
    .slave_cs_pin[1]   = GD_GPIO_NUM,
};

static struct gk_spi_controller_data spi1_controller_data =
{
    .id                = 1,
    .total_slave       = 2,
    .slave_cs_pin[0]   = GD_GPIO_13,//rgb_my280h45p01
    .slave_cs_pin[1]   = GD_GPIO_18,//rgb_tpo990000072
};

struct gk_platform_device plat_spi0 =
{
    .name = "spi", .private_data = &spi0_controller_data,
};

struct gk_platform_device plat_spi1 =
{
    .name = "spi", .private_data = &spi1_controller_data,
};

#endif


#ifdef RT_USING_WDT
static struct wdt_driver wdt_obj = {
    .in_use = 0,
};
#endif
#ifdef RT_USING_ADC
static struct wrap_adc_obj adc_obj = {
    .id = 0, .active_channel_no = 0,
};
#endif
#ifdef RT_USING_PWM
static struct pwm_driver pwm_obj = {
    .pwm[0].id = 0, .pwm[0].gpio_id = GD_GPIO_42,
};
#endif


struct gk_platform_device plat_pwm = {
    .name = "pwm", .private_data = &pwm_obj,
};

struct gk_platform_device plat_wdt = {
    .name = "wdt", .private_data = &wdt_obj,
};

struct gk_platform_device plat_adc = {
    .name = "adc", .private_data = &adc_obj,
};


#ifdef RT_USING_SDIO


static struct gk_sdio_info sdio0 =
{
    .id = 0,
#ifdef GK7102C_JH
    .type = SDIO_DEVICE_TYPE_WIFI,
#else
    .type = SDIO_DEVICE_TYPE_NORMAL,
#endif
};

#ifdef CODEC_710XS
static struct gk_sdio_info sdio1 =
{
    .id = 1,
    .type = SDIO_DEVICE_TYPE_NORMAL,
};
#endif

struct gk_platform_device plat_sdio0 = {
    .name = "gk-sdio", .private_data = &sdio0,
};

#ifdef CODEC_710XS
struct gk_platform_device plat_sdio1 = {
    .name = "gk-sdio", .private_data = &sdio1,
};

#endif

#endif

const static struct gk_platform_device *platform_device[] = {
#ifdef RT_USING_I2C
    &plat_i2c0,
    &plat_i2c1,
#endif
#ifdef RT_USING_SPI
    &plat_spi0,
    &plat_spi1,
#endif
#ifdef RT_USING_WDT
    &plat_wdt,
#endif
#ifdef RT_USING_ADC
    &plat_adc,
#endif
#ifdef RT_USING_PWM
    &plat_pwm,
#endif

#ifdef RT_USING_SDIO
    &plat_sdio0,

#ifdef CODEC_710XS
    &plat_sdio1,
#endif

#endif
};

int gk_platform_driver_init(struct gk_platform_driver *plat_drv)
{
    int i,ret = RT_EOK;
    int device_cnt = sizeof(platform_device) / sizeof(platform_device[0]);

    if(!plat_drv || !plat_drv->name || !plat_drv->probe)
        return -RT_EINVAL;

    for (i = 0; i < device_cnt; i++)
    {
        if (!strcmp(plat_drv->name, platform_device[i]->name))
        {
            ret = plat_drv->probe(platform_device[i]->private_data);
        }
    }

    return ret;
}

int gk_platform_driver_uninit(struct gk_platform_driver *plat_drv)
{
    int i,ret = RT_EOK;
    int device_cnt = sizeof(platform_device) / sizeof(platform_device[0]);

    if(!plat_drv || !plat_drv->name || !plat_drv->probe)
        return -RT_EINVAL;

    for (i = 0; i < device_cnt; i++)
    {
        if (!strcmp(plat_drv->name, platform_device[i]->name))
        {
            ret = plat_drv->remove(platform_device[i]->private_data);
        }
    }

    return ret;
}
