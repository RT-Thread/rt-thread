/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if (defined(BSP_USING_SOFT_I2C) && defined(RT_USING_I2C_BITOPS) && defined(RT_USING_I2C) && defined(RT_USING_PIN))

#include "NuMicro.h"
#include "rtdevice.h"
#include "rthw.h"
#include "rtthread.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.softi2c"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define DEFINE_NU_SOFT_I2C_BUS_CONFIG(_idx, _scl, _sda) \
    {                                                    \
        .scl = _scl,                                     \
        .sda = _sda,                                     \
        .bus_name = "softi2c" #_idx,                    \
    }

#if defined(BSP_USING_SOFT_I2C0)
#define NU_SOFT_I2C0_BUS_CONFIG \
    DEFINE_NU_SOFT_I2C_BUS_CONFIG(0, BSP_SOFT_I2C0_SCL_PIN, BSP_SOFT_I2C0_SDA_PIN)
#endif

#if defined(BSP_USING_SOFT_I2C1)
#define NU_SOFT_I2C1_BUS_CONFIG \
    DEFINE_NU_SOFT_I2C_BUS_CONFIG(1, BSP_SOFT_I2C1_SCL_PIN, BSP_SOFT_I2C1_SDA_PIN)
#endif

#if (!defined(BSP_USING_SOFT_I2C0) && !defined(BSP_USING_SOFT_I2C1))
    #error "Please define at least one BSP_USING_SOFT_I2Cx"
#endif


/* Types / Structures ---------------------------------------------------------*/
struct nu_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

struct nu_soft_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device soft_i2c_bus;
};

/* Static Function Prototypes ------------------------------------------------*/
static void nu_soft_i2c_udelay(rt_uint32_t us);
static void nu_soft_i2c_set_sda(void *data, rt_int32_t state);
static void nu_soft_i2c_set_scl(void *data, rt_int32_t state);
static rt_int32_t nu_soft_i2c_get_sda(void *data);
static rt_int32_t nu_soft_i2c_get_scl(void *data);

/* Static Variables ----------------------------------------------------------*/
static const struct nu_soft_i2c_config nu_soft_i2c_cfg[] =
{
#if defined(BSP_USING_SOFT_I2C0)
    NU_SOFT_I2C0_BUS_CONFIG,
#endif
#if defined(BSP_USING_SOFT_I2C1)
    NU_SOFT_I2C1_BUS_CONFIG,
#endif
};

static struct nu_soft_i2c nu_soft_i2c_obj[sizeof(nu_soft_i2c_cfg) / sizeof(nu_soft_i2c_cfg[0])];

static const struct rt_i2c_bit_ops nu_soft_i2c_bit_ops =
{
    .data     = RT_NULL,
    .set_sda  = nu_soft_i2c_set_sda,
    .set_scl  = nu_soft_i2c_set_scl,
    .get_sda  = nu_soft_i2c_get_sda,
    .get_scl  = nu_soft_i2c_get_scl,
    .udelay   = nu_soft_i2c_udelay,
    .delay_us = 1,
    .timeout  = 100
};

/* Functions Implementation --------------------------------------------------*/
/**
 * The time delay function.
 *
 * @param microseconds.
 */
static void nu_soft_i2c_udelay(rt_uint32_t us)
{
    rt_hw_us_delay(us);
}

/**
 * This function initializes the soft i2c pin.
 *
 * @param soft i2c config class.
 */
static void nu_soft_i2c_gpio_init(const struct nu_soft_i2c_config *cfg)
{
    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
 * if i2c is locked, this function will unlock it
 *
 * @param soft i2c config class
 *
 * @return RT_EOK indicates successful unlock.
 */
static rt_err_t nu_soft_i2c_bus_unlock(const struct nu_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            nu_soft_i2c_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            nu_soft_i2c_udelay(100);
        }
    }
    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * This function sets the sda pin.
 *
 * @param soft i2c config class.
 * @param The sda pin state.
 */
static void nu_soft_i2c_set_sda(void *data, rt_int32_t state)
{
    struct nu_soft_i2c_config *cfg = (struct nu_soft_i2c_config *)data;

    rt_pin_write(cfg->sda, state ? PIN_HIGH : PIN_LOW);
}

/**
 * This function sets the scl pin.
 *
 * @param soft i2c config class.
 * @param The scl pin state.
 */
static void nu_soft_i2c_set_scl(void *data, rt_int32_t state)
{
    struct nu_soft_i2c_config *cfg = (struct nu_soft_i2c_config *)data;

    rt_pin_write(cfg->scl, state ? PIN_HIGH : PIN_LOW);
}

/**
 * This function gets the sda pin state.
 *
 * @param The sda pin state.
 */
static rt_int32_t nu_soft_i2c_get_sda(void *data)
{
    struct nu_soft_i2c_config *cfg = (struct nu_soft_i2c_config *)data;

    return rt_pin_read(cfg->sda);
}

/**
 * This function gets the scl pin state.
 *
 * @param The scl pin state.
 */
static rt_int32_t nu_soft_i2c_get_scl(void *data)
{
    struct nu_soft_i2c_config *cfg = (struct nu_soft_i2c_config *)data;

    return rt_pin_read(cfg->scl);
}
int rt_soft_i2c_init(void)
{
    rt_size_t obj_num = sizeof(nu_soft_i2c_obj) / sizeof(struct nu_soft_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        nu_soft_i2c_obj[i].ops = nu_soft_i2c_bit_ops;
        nu_soft_i2c_obj[i].ops.data = (void *)&nu_soft_i2c_cfg[i];
        nu_soft_i2c_obj[i].soft_i2c_bus.priv = &nu_soft_i2c_obj[i].ops;
        nu_soft_i2c_gpio_init(&nu_soft_i2c_cfg[i]);

        result = rt_i2c_bit_add_bus(&nu_soft_i2c_obj[i].soft_i2c_bus, nu_soft_i2c_cfg[i].bus_name);
        RT_ASSERT(result == RT_EOK);

        nu_soft_i2c_bus_unlock(&nu_soft_i2c_cfg[i]);

        LOG_D("software simulation %s init done, pin scl: %d, pin sda %d",
              nu_soft_i2c_cfg[i].bus_name,
              nu_soft_i2c_cfg[i].scl,
              nu_soft_i2c_cfg[i].sda);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_soft_i2c_init);
#endif //#if (defined(BSP_USING_SOFT_I2C) && defined(RT_USING_I2C_BITOPS) && defined(RT_USING_I2C) && defined(RT_USING_PIN))
