/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-11     kyle         first implementation.
 */

#include "drv_soft_spi.h"
#include <board.h>
#include <rtthread.h>

#if defined(RT_USING_SPI) && defined(RT_USING_SPI_BITOPS) && defined(RT_USING_PIN)
#include <rtdevice.h>
#include "spi-bit-ops.h"

#define DBG_TAG               "drv.SPI"
#ifdef RT_SPI_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_WARNING
#endif
#include <rtdbg.h>

#ifndef ITEM_NUM
#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
#endif

struct gd32_spi_bit_data
{
    struct
    {
        rcu_periph_enum clk;
        rt_uint32_t port;
        rt_uint32_t pin;
    } sclk, mosi, miso;
};


rt_inline FlagStatus GPIO_OUTPUT_BIT_GET(uint32_t gpio_periph, uint32_t pin)
{
    if((uint32_t)RESET !=(GPIO_OCTL(gpio_periph)&(pin))){
        return SET;
    }else{
        return RESET;
    }
}

rt_inline void GPIO_BIT_RESET(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BC(gpio_periph) = (uint32_t)pin;
}

rt_inline void GPIO_BIT_SET(uint32_t gpio_periph, uint32_t pin)
{
    GPIO_BOP(gpio_periph) = (uint32_t)pin;
}

rt_inline FlagStatus GPIO_INPUT_BIT_GET(uint32_t gpio_periph,uint32_t pin)
{
    if((uint32_t)RESET != (GPIO_ISTAT(gpio_periph)&(pin))){
        return SET;
    }else{
        return RESET;
    }
}

rt_inline void GPIO_INIT(uint32_t gpio_periph, uint32_t mode, uint32_t speed, uint32_t pin)
{
    uint16_t i;
    uint32_t temp_mode = 0U;
    uint32_t reg = 0U;

    /* GPIO mode configuration */
    temp_mode = (uint32_t)(mode & ((uint32_t)0x0FU));

    /* GPIO speed configuration */
    if(((uint32_t)0x00U) != ((uint32_t)mode & ((uint32_t)0x10U))){
            /* output mode max speed:10MHz,2MHz,50MHz */
            temp_mode |= (uint32_t)speed;
    }

    /* configure the eight low port pins with GPIO_CTL0 */
    for(i = 0U;i < 8U;i++){
        if((1U << i) & pin){
            reg = GPIO_CTL0(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i, temp_mode);

            /* set IPD or IPU */
            if(GPIO_MODE_IPD == mode){
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t)((1U << i) & pin);
            }else{
                /* set the corresponding OCTL bit */
                if(GPIO_MODE_IPU == mode){
                    GPIO_BOP(gpio_periph) = (uint32_t)((1U << i) & pin);
                }
            }
            /* set GPIO_CTL0 register */
            GPIO_CTL0(gpio_periph) = reg;
        }
    }
    /* configure the eight high port pins with GPIO_CTL1 */
    for(i = 8U;i < 16U;i++){
        if((1U << i) & pin){
            reg = GPIO_CTL1(gpio_periph);

            /* clear the specified pin mode bits */
            reg &= ~GPIO_MODE_MASK(i - 8U);
            /* set the specified pin mode bits */
            reg |= GPIO_MODE_SET(i - 8U, temp_mode);

            /* set IPD or IPU */
            if(GPIO_MODE_IPD == mode){
                /* reset the corresponding OCTL bit */
                GPIO_BC(gpio_periph) = (uint32_t)((1U << i) & pin);
            }else{
                /* set the corresponding OCTL bit */
                if(GPIO_MODE_IPU == mode){
                    GPIO_BOP(gpio_periph) = (uint32_t)((1U << i) & pin);
                }
            }
            /* set GPIO_CTL1 register */
            GPIO_CTL1(gpio_periph) = reg;
        }
    }
}

#define GPIO_SET_OUTPUT(port, pin)        GPIO_INIT(port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, pin)
#define GPIO_SET_INPUT(port, pin)         GPIO_INIT(port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, pin)


static void gpio_tog_sclk(void *data)
{
    struct gd32_spi_bit_data *bd = data;

    if (GPIO_OUTPUT_BIT_GET(bd->sclk.port, bd->sclk.pin) == SET)
    {
        GPIO_BIT_RESET(bd->sclk.port, bd->sclk.pin);
    }
    else
    {
        GPIO_BIT_SET(bd->sclk.port, bd->sclk.pin);
    }
}

static void gpio_set_sclk(void *data, rt_int32_t state)
{
    struct gd32_spi_bit_data *bd = data;

    if (state)
    {
        GPIO_BIT_SET(bd->sclk.port, bd->sclk.pin);
    }
    else
    {
        GPIO_BIT_RESET(bd->sclk.port, bd->sclk.pin);
    }
}

static void gpio_set_mosi(void *data, rt_int32_t state)
{
    struct gd32_spi_bit_data *bd = data;

    if (state)
    {
        GPIO_BIT_SET(bd->mosi.port, bd->mosi.pin);
    }
    else
    {
        GPIO_BIT_RESET(bd->mosi.port, bd->mosi.pin);
    }
}

static void gpio_set_miso(void *data, rt_int32_t state)
{
    struct gd32_spi_bit_data *bd = data;

    if (state)
    {
        GPIO_BIT_SET(bd->miso.port, bd->miso.pin);
    }
    else
    {
        GPIO_BIT_RESET(bd->miso.port, bd->miso.pin);
    }
}

static rt_int32_t gpio_get_sclk(void *data)
{
    struct gd32_spi_bit_data *bd = data;

    return GPIO_INPUT_BIT_GET(bd->sclk.port, bd->sclk.pin);
}

static rt_int32_t gpio_get_mosi(void *data)
{
    struct gd32_spi_bit_data *bd = data;

    return GPIO_INPUT_BIT_GET(bd->mosi.port, bd->mosi.pin);
}

static rt_int32_t gpio_get_miso(void *data)
{
    struct gd32_spi_bit_data *bd = data;

    return GPIO_INPUT_BIT_GET(bd->miso.port, bd->miso.pin);
}

static void gpio_dir_mosi(void *data, rt_int32_t state)
{
    struct gd32_spi_bit_data *bd = data;

    if (state)
    {
        GPIO_SET_INPUT(bd->mosi.port, bd->mosi.pin);
    }
    else
    {
        GPIO_SET_OUTPUT(bd->mosi.port, bd->mosi.pin);
    }
}

static void gpio_dir_miso(void *data, rt_int32_t state)
{
    struct gd32_spi_bit_data *bd = data;

    if (state)
    {
        GPIO_SET_INPUT(bd->miso.port, bd->miso.pin);
    }
    else
    {
        GPIO_SET_OUTPUT(bd->miso.port, bd->miso.pin);
    }
}

static void gpio_udelay(rt_uint32_t us)
{
    int i = ((rcu_clock_freq_get(CK_SYS) / 4000000) * us);

    while (i)
    {
        i--;
    }
}

static void soft_spi_gpio_init(const struct gd32_spi_bit_data *bd)
{
    rcu_periph_clock_enable(bd->sclk.clk);
    rcu_periph_clock_enable(bd->mosi.clk);
    rcu_periph_clock_enable(bd->miso.clk);

    gpio_init(bd->sclk.port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, bd->sclk.pin);
    gpio_init(bd->mosi.port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, bd->mosi.pin);
    gpio_init(bd->miso.port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, bd->miso.pin);

    GPIO_BIT_SET(bd->sclk.port, bd->sclk.pin);
    GPIO_BIT_SET(bd->mosi.port, bd->mosi.pin);
    GPIO_BIT_SET(bd->miso.port, bd->miso.pin);
}

int rt_soft_spi_init(void)
{
    int result = 0;

    {
        static const struct gd32_spi_bit_data spi1_bdata =
        {
            .sclk = { RCU_GPIOB, GPIOB, GPIO_PIN_13},
            .mosi = { RCU_GPIOB, GPIOB, GPIO_PIN_15},
            .miso = { RCU_GPIOB, GPIOB, GPIO_PIN_14},
        };
        static struct rt_spi_bit_ops spi1_bops =
        {
            .data     = (void *)&spi1_bdata,
            .tog_sclk = gpio_tog_sclk,
            .set_sclk = gpio_set_sclk,
            .set_mosi = gpio_set_mosi,
            .set_miso = gpio_set_miso,
            .get_sclk = gpio_get_sclk,
            .get_mosi = gpio_get_mosi,
            .get_miso = gpio_get_miso,
            .dir_mosi = gpio_dir_mosi,
            .dir_miso = gpio_dir_miso,
            .udelay   = gpio_udelay,
        };
        struct rt_spi_bit_obj spi1_obj;

        soft_spi_gpio_init(&spi1_bdata);
        rt_spi_bit_add_bus(&spi1_obj, "spi3", &spi1_bops);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_soft_spi_init);
#endif
