/*
 * File      : drv_i2c.c
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */
 
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_lpi2c.h"

//#define DRV_I2C_DEBUG

#ifdef RT_USING_I2C

#ifdef RT_USING_I2C_BITOPS

#define I2CBUS_NAME             "i2c0"

struct stm32_i2c_bit_data
{
    struct
    {
        GPIO_Type *base;
        uint32_t pin;
    } scl, sda;
};

static void gpio_udelay(rt_uint32_t us)
{
    volatile rt_int32_t i;
    for (; us > 0; us--)
    {
        i = 1000;
        while (i--);
    }
}

static void gpio_set_input(GPIO_Type* base, uint32_t pin)
{
    if (base->GDIR & (1 << pin))        //output mode
    {
        base->GDIR &= ~(1 << pin);
        gpio_udelay(5);
    }
}

static void gpio_set_output(GPIO_Type* base, uint32_t pin)
{
    if (!(base->GDIR & (1 << pin)))        //input mode
    {    
        base->GDIR |= (1 << pin);
        gpio_udelay(5);
    }
}

static void gpio_set_sda(void *data, rt_int32_t state)
{
    struct stm32_i2c_bit_data *bd = data;
    
    gpio_set_output(bd->sda.base, bd->sda.pin);
    
    GPIO_PinWrite(bd->sda.base, bd->sda.pin, !!state);
}

static void gpio_set_scl(void *data, rt_int32_t state)
{
    struct stm32_i2c_bit_data *bd = data;
    
    gpio_set_output(bd->scl.base, bd->scl.pin);
    
    GPIO_PinWrite(bd->scl.base, bd->scl.pin, !!state);
}

static rt_int32_t gpio_get_sda(void *data)
{
    struct stm32_i2c_bit_data *bd = data;
    
    gpio_set_input(bd->sda.base, bd->sda.pin);

    return GPIO_ReadPinInput(bd->sda.base, bd->sda.pin);
}

static rt_int32_t gpio_get_scl(void *data)
{
    struct stm32_i2c_bit_data *bd = data;
    
    gpio_set_input(bd->scl.base, bd->scl.pin);

    return GPIO_ReadPinInput(bd->scl.base, bd->scl.pin);
}


#else /* RT_USING_I2C_BITOPS */
    // todo : add hardware i2c
#endif /* RT_USING_I2C_BITOPS */

int rt_hw_i2c_init(void)
{
#ifdef RT_USING_I2C_BITOPS
    /* register I2C1: SCL/P0_20 SDA/P0_19 */
    {
        static struct rt_i2c_bus_device i2c_device;

        static const struct stm32_i2c_bit_data _i2c_bdata =
        {
            /* SCL */ {GPIO1, 16},
            /* SDA */ {GPIO1, 17},
        };

        static const struct rt_i2c_bit_ops _i2c_bit_ops =
        {
            (void*)&_i2c_bdata,
            gpio_set_sda,
            gpio_set_scl,
            gpio_get_sda,
            gpio_get_scl,

            gpio_udelay,

            50,
            1000
        };

        gpio_pin_config_t pin_config = {
            kGPIO_DigitalOutput, 0,
        };
        
        CLOCK_EnableClock(kCLOCK_Iomuxc);

        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16, 1U);
            IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16,
            0xD8B0u);                                /* Slew Rate Field: Slow Slew Rate
                                                        Drive Strength Field: R0/6
                                                        Speed Field: medium(100MHz)
                                                        Open Drain Enable Field: Open Drain Enabled
                                                        Pull / Keep Enable Field: Pull/Keeper Enabled
                                                        Pull / Keep Select Field: Keeper
                                                        Pull Up / Down Config. Field: 22K Ohm Pull Up
                                                        Hyst. Enable Field: Hysteresis Disabled */
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17, 1U);
            IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17,
            0xD8B0u);                                /* Slew Rate Field: Slow Slew Rate
                                                        Drive Strength Field: R0/6
                                                        Speed Field: medium(100MHz)
                                                        Open Drain Enable Field: Open Drain Enabled
                                                        Pull / Keep Enable Field: Pull/Keeper Enabled
                                                        Pull / Keep Select Field: Keeper
                                                        Pull Up / Down Config. Field: 22K Ohm Pull Up
                                                        Hyst. Enable Field: Hysteresis Disabled */
        /* Enable touch panel controller */
        GPIO_PinInit(_i2c_bdata.sda.base, _i2c_bdata.sda.pin, &pin_config);
        GPIO_PinInit(_i2c_bdata.scl.base, _i2c_bdata.scl.pin, &pin_config);
        
        GPIO_PortSet(_i2c_bdata.sda.base, _i2c_bdata.sda.pin);
        GPIO_PortSet(_i2c_bdata.scl.base, _i2c_bdata.scl.pin);
        
        //RT_ASSERT(gpio_get_scl(&_i2c_bdata) != 0);
        //RT_ASSERT(gpio_get_sda(&_i2c_bdata) != 0);

        i2c_device.priv = (void *)&_i2c_bit_ops;
        rt_i2c_bit_add_bus(&i2c_device, I2CBUS_NAME);
    } /* register I2C */

#else /* RT_USING_I2C_BITOPS */
    // Todo : add hardware i2c

#endif /* RT_USING_I2C_BITOPS */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#if defined(RT_USING_FINSH) && defined(DRV_I2C_DEBUG)
#include <finsh.h>

static rt_device_t _i2c_find(const char *name)
{
    rt_device_t dev;

    dev = rt_device_find(name);
    if (!dev) 
    {
        rt_kprintf("search device failed: %s\n", name);
        return RT_NULL;
    }

    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open device failed: %s\n", name);
        return RT_NULL;
    }

    rt_kprintf("open i2c bus: %s\n", name);
    
    return dev;
}

static void _search_i2c_device(rt_device_t dev, uint8_t cmd)
{
    int count = 0;
    struct rt_i2c_msg msgs[2];
    uint8_t buf = 0;

    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &cmd;
    msgs[0].len   = sizeof(cmd);

    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = &buf;
    msgs[1].len   = 1;

    for (int i = 0; i <= 0x7f; i++)
    {
        int len;
        
        msgs[0].addr  = i;
        msgs[1].addr  = i;
        len = rt_i2c_transfer((struct rt_i2c_bus_device *)dev, msgs, 2);
        if (len == 2)
        {
            count++;
            rt_kprintf("add:%02X transfer success, id: %02X\n", i, buf);
        } 
    }
    
    rt_kprintf("i2c device: %d\n", count);
}

static int i2c_test(const char *name, uint8_t cmd)
{
    rt_device_t dev = _i2c_find(name);
    if (dev == RT_NULL)
    {
        rt_kprintf("search i2c device faild\n");
        return -1;
    }
    
    _search_i2c_device(dev, cmd);
    
    rt_device_close(dev);
    
    return 0;
}
FINSH_FUNCTION_EXPORT(i2c_test, e.g: i2c_test("i2c0", 0xA3));
#endif

#endif /* RT_USING_I2C */
