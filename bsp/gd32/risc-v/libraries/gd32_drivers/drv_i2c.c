/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-13     yefeng       first implementation for GD32VW55x
 */

#include "drv_i2c.h"

#if defined(RT_USING_I2C) && defined(BSP_USING_HW_I2C)

#if !defined(BSP_USING_HW_I2C0) && !defined(BSP_USING_HW_I2C1)
#error "Please define at least one BSP_USING_HW_I2Cx"
    /* This driver can be enabled in menuconfig:
     * Hardware Drivers Config ->
     *   On-chip Peripheral Drivers ->
     *     Enable Hardware I2C
     */
#endif

#if defined(SOC_SERIES_GD32VF103V)
#error "not implement GD32VF103V i2c support!"
#endif

#define DBG_TAG "drv.i2c"
#ifdef RT_I2C_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_ERROR
#endif
#include <rtdbg.h>

#define I2C_TIME_OUT    (uint32_t)(20000)
#define MAX_RELOAD_SIZE 255

typedef enum
{
    I2C_PROC_START = 0,
    I2C_PROC_READ_INIT,
    I2C_PROC_TRANSMIT_DATA,
    I2C_PROC_RELOAD,
    I2C_PROC_STOP,
    I2C_PROC_END
} i2c_process_enum;

struct gd32_pin_cfg_param
{
    uint32_t rcu[2];
    uint32_t af[2];
    uint32_t port[2];
    uint32_t pin[2];
};

/**
 * @brief i2c configuration params
 *
 */
static struct gd32_i2c_config i2c_config[] = {
#ifdef BSP_USING_HW_I2C0
    {
        "i2c0",
        I2C0,
        RCU_I2C0,
        BSP_HW_I2C0_CLK,
    },
#endif
#ifdef BSP_USING_HW_I2C1
    {
        "i2c1",
        I2C1,
        RCU_I2C1,
        BSP_HW_I2C1_CLK,
    },
#endif
};

/**
 * @brief i2c pin configuration param array
 *
 */
static const struct gd32_pin_cfg_param pin_param[] = {
#if defined(BSP_USING_HW_I2C0)
    {
#if defined(BSP_HW_I2C0_PIN_PA2_PA3)
        .rcu = { RCU_GPIOA, RCU_GPIOA },
        .af = { GPIO_AF_4, GPIO_AF_4 },
        .port = { GPIOA, GPIOA },
        .pin = { GPIO_PIN_2, GPIO_PIN_3 }
#elif defined(BSP_HW_I2C0_PIN_PA15_PC8)
        .rcu = { RCU_GPIOA, RCU_GPIOC },
        .af = { GPIO_AF_4, GPIO_AF_4 },
        .port = { GPIOA, GPIOC },
        .pin = { GPIO_PIN_15, GPIO_PIN_8 }
#elif defined(BSP_HW_I2C0_PIN_PB0_PB1)
        .rcu = { RCU_GPIOB, RCU_GPIOB },
        .af = { GPIO_AF_6, GPIO_AF_6 },
        .port = { GPIOB, GPIOB },
        .pin = { GPIO_PIN_0, GPIO_PIN_1 }
#elif defined(BSP_HW_I2C0_PIN_PB15_PA8)
        .rcu = { RCU_GPIOB, RCU_GPIOA },
        .af = { GPIO_AF_4, GPIO_AF_5 },
        .port = { GPIOB, GPIOA },
        .pin = { GPIO_PIN_15, GPIO_PIN_8 }
#else
#error "i2c0 not support pin"
#endif
    },
#endif

#if defined(BSP_USING_HW_I2C1)
    {
#if defined(BSP_HW_I2C1_PIN_PA6_PA7)
        .rcu = { RCU_GPIOA, RCU_GPIOA },
        .af = { GPIO_AF_4, GPIO_AF_0 },
        .port = { GPIOA, GPIOA },
        .pin = { GPIO_PIN_6, GPIO_PIN_7 }
#elif defined(BSP_HW_I2C1_PIN_PA13_PA14)
        .rcu = { RCU_GPIOA, RCU_GPIOA },
        .af = { GPIO_AF_6, GPIO_AF_6 },
        .port = { GPIOA, GPIOA },
        .pin = { GPIO_PIN_13, GPIO_PIN_14 }
#elif defined(BSP_HW_I2C1_PIN_PA15_PC8)
        .rcu = { RCU_GPIOA, RCU_GPIOC },
        .af = { GPIO_AF_6, GPIO_AF_6 },
        .port = { GPIOA, GPIOC },
        .pin = { GPIO_PIN_15, GPIO_PIN_8 }
#elif defined(BSP_HW_I2C1_PIN_PB12_PB13)
        .rcu = { RCU_GPIOB, RCU_GPIOB },
        .af = { GPIO_AF_6, GPIO_AF_6 },
        .port = { GPIOB, GPIOB },
        .pin = { GPIO_PIN_12, GPIO_PIN_13 }
#elif defined(BSP_HW_I2C1_PIN_PB15_PA8)
        .rcu = { RCU_GPIOB, RCU_GPIOA },
        .af = { GPIO_AF_6, GPIO_AF_6 },
        .port = { GPIOB, GPIOA },
        .pin = { GPIO_PIN_15, GPIO_PIN_8 }
#else
#error "i2c1 not support pin"
#endif
    },
#endif
};

/**
 * @brief Device object
 *
 */
static struct gd32_i2c_device i2c_obj[sizeof(i2c_config) / sizeof(i2c_config[0])] = { 0 };

/**
 * @brief i2c read
 *
 * @param device operate device
 * @param msg deal i2c message pointer
 * @return rt_err_t return RT_OK if success, other value failed.
 */
static rt_err_t gd32_i2c_read(struct gd32_i2c_device *device, struct rt_i2c_msg *msg)
{
    rt_err_t ret = RT_EOK;
    i2c_process_enum state = I2C_PROC_READ_INIT;
    rt_uint32_t timeout = 0;
    rt_uint8_t end_flag = 0;
    rt_uint8_t first_reload_flag = 1;
    rt_uint8_t reload_mode_flag = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(msg != RT_NULL);

    rt_uint32_t i2c_periph = device->config->i2c_periph;
    rt_uint16_t nbytes_reload = 0;
    rt_uint16_t number_of_byte = msg->len;
    rt_uint8_t *p_buffer = msg->buf;

    while (!end_flag)
    {
        switch (state)
        {
        case I2C_PROC_START:
            /* start */
            i2c_start_on_bus(i2c_periph);
            state = I2C_PROC_TRANSMIT_DATA;
            break;
        case I2C_PROC_READ_INIT:
            /* configure the device address */
            i2c_master_addressing(i2c_periph, msg->addr << 1, I2C_MASTER_RECEIVE);
            /* disable I2C automatic end mode in master mode */
            i2c_automatic_end_disable(i2c_periph);
            state = I2C_PROC_RELOAD;
            break;
        case I2C_PROC_RELOAD:
            if (number_of_byte > MAX_RELOAD_SIZE)
            {
                number_of_byte = number_of_byte - MAX_RELOAD_SIZE;
                nbytes_reload = MAX_RELOAD_SIZE;
                reload_mode_flag = 1;
            }
            else
            {
                nbytes_reload = number_of_byte;
                reload_mode_flag = 0;
            }

            LOG_D("configure number of bytes: %d", nbytes_reload);
            /* configure number of bytes to be transferred */
            i2c_transfer_byte_number_config(i2c_periph, nbytes_reload);

            if (reload_mode_flag)
            {
                LOG_D("enable I2C reload mode");
                /* enable I2C reload mode */
                i2c_reload_enable(i2c_periph);
            }
            else
            {
                LOG_D("disable I2C reload mode");
                /* disable I2C reload mode */
                i2c_reload_disable(i2c_periph);
            }

            if (first_reload_flag)
            {
                LOG_D("first reload");
                first_reload_flag = 0;
                state = I2C_PROC_START;
            }
            else
            {
                state = I2C_PROC_TRANSMIT_DATA;
            }
            break;
        case I2C_PROC_TRANSMIT_DATA:
            LOG_D("read: transmit data: %d", nbytes_reload);
            timeout = 0;
            while (nbytes_reload)
            {
                /* wait until the RBNE bit is set and clear it */
                if (i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
                {
                    /* read a byte from the device */
                    *p_buffer = i2c_data_receive(i2c_periph);
                    /* point to the next location where the byte read will be saved */
                    p_buffer++;
                    /* decrement the read bytes counter */
                    nbytes_reload--;

                    /* reset timeout counter */
                    timeout = 0;
                }
                else
                {
                    timeout++;
                    if (timeout >= I2C_TIME_OUT)
                    {
                        LOG_E("receive data timeout, end");
                        ret = -RT_ETIMEOUT;
                        return ret;
                    }
                }
            }

            LOG_D("read: transmit data end");
            timeout = 0;

            /* check if the reload mode is enabled or not */
            if (I2C_CTL1(i2c_periph) & I2C_CTL1_RELOAD)
            {
                /* wait for TCR flag */
                while ((!i2c_flag_get(i2c_periph, I2C_FLAG_TCR)) && (timeout < I2C_TIME_OUT))
                {
                    timeout++;
                }

                if (timeout < I2C_TIME_OUT)
                {
                    LOG_D("reload read complete");
                    state = I2C_PROC_RELOAD;
                }
                else
                {
                    LOG_E("reload read timeout, end");
                    ret = -RT_ETIMEOUT;
                    state = I2C_PROC_END;
                }
            }
            else
            {
                LOG_D("read complete");

                /* wait for TCR flag */
                while ((!i2c_flag_get(i2c_periph, I2C_FLAG_TC)) && (timeout < I2C_TIME_OUT))
                {
                    timeout++;
                }

                if (timeout < I2C_TIME_OUT)
                {
                    if (msg->flags & RT_I2C_NO_STOP)
                    {
                        LOG_D("no stop end");
                        state = I2C_PROC_END;
                    }
                    else
                    {
                        LOG_D("generate a STOP");
                        i2c_stop_on_bus(i2c_periph);
                        state = I2C_PROC_STOP;
                    }
                }
                else
                {
                    LOG_E("read timeout, end");
                    ret = -RT_ETIMEOUT;
                    state = I2C_PROC_END;
                }
            }
            break;
        case I2C_PROC_STOP:
            /* wait until the stop condition is finished */
            while ((!i2c_flag_get(i2c_periph, I2C_FLAG_STPDET)) && (timeout < I2C_TIME_OUT))
            {
                timeout++;
            }

            if (timeout < I2C_TIME_OUT)
            {
                /* clear STPDET flag */
                i2c_flag_clear(i2c_periph, I2C_FLAG_STPDET);
                timeout = 0;
                state = I2C_PROC_END;
            }
            else
            {
                timeout = 0;
                state = I2C_PROC_END;
                ret = -RT_ETIMEOUT;
                LOG_E("i2c master sends stop signal timeout in read!\n");
            }
            break;
        case I2C_PROC_END:
            end_flag = 1;
            timeout = 0;
            break;
        default:
            /* default status */
            end_flag = 1;
            timeout = 0;
            LOG_E("i2c state unknown, end!\n");
        }
    }

    return ret;
}

/**
 * @brief i2c write
 *
 * @param device operate device
 * @param msg deal i2c message pointer
 * @return rt_err_t return RT_OK if success, other value failed.
 */
static rt_err_t gd32_i2c_write(struct gd32_i2c_device *device, struct rt_i2c_msg *msg)
{
    rt_err_t ret = RT_EOK;
    i2c_process_enum state = I2C_PROC_RELOAD;
    rt_uint16_t timeout = 0;
    rt_uint8_t start_flag = 0;
    rt_uint8_t end_flag = 0;
    rt_uint8_t reload_mode_flag = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(msg != RT_NULL);

    rt_uint32_t i2c_periph = device->config->i2c_periph;
    rt_uint16_t number_of_byte = msg->len;
    rt_uint16_t nbytes_reload = 0;
    rt_uint8_t *p_buffer = msg->buf;

    if (msg->flags & RT_I2C_NO_START)
    {
        start_flag = 0;
    }
    else
    {
        start_flag = 1;
    }

    /* configure the device address */
    i2c_master_addressing(i2c_periph, msg->addr << 1, I2C_MASTER_TRANSMIT);
    /* disable I2C automatic end mode in master mode */
    i2c_automatic_end_disable(i2c_periph);

    while (!end_flag)
    {
        switch (state)
        {
        case I2C_PROC_START:
            /* start */
            LOG_D("generate a START");
            timeout = 0;
            i2c_start_on_bus(i2c_periph);
            state = I2C_PROC_TRANSMIT_DATA;
            break;
        case I2C_PROC_RELOAD:
            if (number_of_byte > MAX_RELOAD_SIZE)
            {
                number_of_byte = number_of_byte - MAX_RELOAD_SIZE;
                nbytes_reload = MAX_RELOAD_SIZE;
                reload_mode_flag = 1;
            }
            else
            {
                nbytes_reload = number_of_byte;
                reload_mode_flag = 0;
            }

            LOG_D("configure number of bytes: %d", nbytes_reload);

            /* configure number of bytes to be transferred */
            i2c_transfer_byte_number_config(i2c_periph, nbytes_reload);

            if (reload_mode_flag)
            {
                LOG_D("enable I2C reload mode");
                /* enable I2C reload mode */
                i2c_reload_enable(i2c_periph);
            }
            else
            {
                LOG_D("disable I2C reload mode");
                /* disable I2C reload mode */
                i2c_reload_disable(i2c_periph);
            }

            if (start_flag)
            {
                start_flag = 0;
                state = I2C_PROC_START;
            }
            else
            {
                state = I2C_PROC_TRANSMIT_DATA;
            }
            break;
        case I2C_PROC_TRANSMIT_DATA:
            timeout = 0;
            LOG_D("master transmit bytes: %d", nbytes_reload);
            while (nbytes_reload--)
            {
                /* wait until TI bit is set */
                while ((!i2c_flag_get(i2c_periph, I2C_FLAG_TI)) && (timeout < I2C_TIME_OUT))
                {
                    timeout++;
                }

                if (timeout < I2C_TIME_OUT)
                {
                    /* while there is data to be written */
                    i2c_data_transmit(i2c_periph, *p_buffer);
                    /* point to the next byte to be written */
                    p_buffer++;
                    timeout = 0;
                }
                else
                {
                    /* wait TI timeout */
                    LOG_E("i2c master sends data timeout when write!");
                    ret = -RT_ETIMEOUT;
                    return ret;
                }
            }

            if (timeout < I2C_TIME_OUT)
            {
                rt_uint32_t wait_flag;

                /* check if the reload mode is enabled or not */
                if (I2C_CTL1(i2c_periph) & I2C_CTL1_RELOAD)
                {
                    wait_flag = I2C_FLAG_TCR;
                }
                else
                {
                    wait_flag = I2C_FLAG_TC;
                }

                timeout = 0;

                /* wait TCR/TC bit is set */
                while ((!i2c_flag_get(i2c_periph, wait_flag)) && (timeout < I2C_TIME_OUT))
                {
                    timeout++;
                }

                if (timeout < I2C_TIME_OUT)
                {
                    if (reload_mode_flag)
                    {
                        state = I2C_PROC_RELOAD;
                    }
                    else
                    {
                        if (msg->flags & RT_I2C_NO_STOP)
                        {
                            state = I2C_PROC_END;
                        }
                        else
                        {
                            LOG_D("generate a STOP");
                            i2c_stop_on_bus(i2c_periph);
                            state = I2C_PROC_STOP;
                        }
                    }
                }
                else
                {
                    LOG_E("i2c master wait %s timeout, end!", (wait_flag == I2C_FLAG_TCR) ? "TCR" : "TC");
                    state = I2C_PROC_END;
                    ret = -RT_ETIMEOUT;
                }
            }
            else
            {
                LOG_E("i2c master send data timeout when write!");
                state = I2C_PROC_END;
                ret = -RT_ETIMEOUT;
            }
            break;
        case I2C_PROC_STOP:
            timeout = 0;
            /* wait until the stop condition is finished */
            while ((!i2c_flag_get(i2c_periph, I2C_FLAG_STPDET)) && (timeout < I2C_TIME_OUT))
            {
                timeout++;
            }

            if (timeout < I2C_TIME_OUT)
            {
                /* clear STPDET flag */
                i2c_flag_clear(i2c_periph, I2C_FLAG_STPDET);
            }
            else
            {
                /* stop detect timeout */
                LOG_E("i2c master sends stop signal timeout when write!");
                ret = -RT_ETIMEOUT;
            }

            state = I2C_PROC_END;
            break;
        case I2C_PROC_END:
            LOG_D("END");
            end_flag = 1;
            break;
        default:
            /* default status */
            state = I2C_PROC_START;
            end_flag = 1;
            timeout = 0;
            LOG_E("i2c master unknown state, end!\n");
        }
    }

    return ret;
}

/**
 * @brief configure i2c alternate pin
 *
 * @param param configure param
 */
static void gd32_i2c_pin_configure(const struct gd32_pin_cfg_param *param)
{
    for (rt_uint8_t i = 0; i < 2; i++)
    {
        /* enable GPIO clock */
        rcu_periph_clock_enable(param->rcu[i]);

        /* connect I2C_SCL_PIN to I2C_SCL */
        gpio_af_set(param->port[i], param->af[i], param->pin[i]);

        /* configure GPIO pins of I2C */
        gpio_mode_set(param->port[i], GPIO_MODE_AF, GPIO_PUPD_PULLUP, param->pin[i]);
        gpio_output_options_set(param->port[i], GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, param->pin[i]);
    }
}

/**
 * @brief configure i2c timing
 *
 * @param i2c_cfg param pointer
 *
 * @note tSCL=tSYNC1+tSYNC2+{[(SCLH[7:0]+1)+(SLLL[7:0]+1)]*(PSC+1)*tI2CCLK}
 */
static void gd32_i2c_timing_configure(struct gd32_i2c_config *i2c_cfg)
{
#define I2C_CLK_PSC_LOW   15
#define I2C_CLK_PSC_STAND 7
#define I2C_CLK_PSC_FAST  1
#define I2C_SCLDELY_LOW   9
#define I2C_SCLDELY_FAST  3
#define I2C_SDADELY       0

    rt_uint32_t i2c_freq;
    rt_uint32_t sclh_scll;
    rt_uint8_t clk_psc;
    rt_uint8_t scldely;

    if (i2c_cfg->i2c_periph == I2C0)
    {
        i2c_freq = rcu_clock_freq_get(CK_I2C0);
    }
    else if (i2c_cfg->i2c_periph == I2C1)
    {
        /* I2C1 use APB1 clock */
        i2c_freq = rcu_clock_freq_get(CK_APB1);
    }
    else
    {
        i2c_freq = rcu_clock_freq_get(CK_APB1);
    }

    if (i2c_cfg->speed < 100)
    {
        clk_psc = I2C_CLK_PSC_LOW;
        scldely = I2C_SCLDELY_LOW;
    }
    else if (i2c_cfg->speed <= 400)
    {
        clk_psc = I2C_CLK_PSC_STAND;
        scldely = I2C_SCLDELY_LOW;
    }
    else
    {
        clk_psc = I2C_CLK_PSC_STAND;
        scldely = I2C_SCLDELY_FAST;
    }

    /* configure I2C timing */
    i2c_timing_config(i2c_cfg->i2c_periph, clk_psc, scldely, I2C_SDADELY);

    sclh_scll = (i2c_freq / (1000 * i2c_cfg->speed) - (I2C_SDADELY * (clk_psc + 1) + 1) - (scldely + 1) * (clk_psc + 1)) / (clk_psc + 1) - 2;

    i2c_master_clock_config(i2c_cfg->i2c_periph, sclh_scll / 2, sclh_scll / 2);
}

/**
 * @brief configure i2c clock, timing, enable i2c
 *
 * @param i2c_cfg
 */
static void gd32_i2c_configure(struct gd32_i2c_config *i2c_cfg)
{
    RT_ASSERT(i2c_cfg != RT_NULL);

    /* enable i2c clock */
    rcu_periph_clock_enable(i2c_cfg->rcu_clk);

    /* reset I2C */
    i2c_disable(i2c_cfg->i2c_periph);

    /* i2c timing config MUST at I2CEN = 0 */
    gd32_i2c_timing_configure(i2c_cfg);

    /* enable I2C */
    i2c_enable(i2c_cfg->i2c_periph);
}

static rt_ssize_t gd32_i2c_xfer(struct rt_i2c_bus_device *device, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_uint16_t last_flags;

    RT_ASSERT(device != RT_NULL);

    struct gd32_i2c_device *i2c_obj = (struct gd32_i2c_device *)(device);
    struct gd32_i2c_config *i2c_cfg = (struct gd32_i2c_config *)(i2c_obj->config);

    RT_ASSERT(i2c_cfg != RT_NULL);

    for (i = 0; i < num; i++)
    {
        rt_err_t ret;
        msg = &msgs[i];

        if (msg->flags & RT_I2C_ADDR_10BIT)
        {
            LOG_E("not implement 10bit address mode");
            return -RT_ENOSYS;
        }

        if (msg->flags & RT_I2C_RD)
        {
            ret = gd32_i2c_read(i2c_obj, msg);
        }
        else
        {
            ret = gd32_i2c_write(i2c_obj, msg);
        }

        if (ret != RT_EOK)
        {
            break;
        }
    }

    return i;
}

static const struct rt_i2c_bus_device_ops i2c_ops = { gd32_i2c_xfer, RT_NULL, RT_NULL };

static int rt_hw_i2c_init(void)
{
    rt_uint8_t index;
    rt_size_t obj_num;
    rt_err_t result = 0;

    obj_num = sizeof(i2c_obj) / sizeof(struct gd32_i2c_device);

    for (index = 0; index < obj_num; index++)
    {
        /* init i2c object */
        i2c_obj[index].config = &i2c_config[index];
        i2c_obj[index].parent.ops = &i2c_ops;

        /* init i2c pin */
        gd32_i2c_pin_configure(&pin_param[index]);

        /* init i2c device */
        gd32_i2c_configure(&i2c_config[index]);

        /* register i2c device */
        result = rt_i2c_bus_device_register(&i2c_obj[index].parent, i2c_obj[index].config->name);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* defined(RT_USING_I2C) && defined(BSP_USING_HW_I2C) */
