/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */
#include "raspi.h"
#include "drv_gpio.h"

#ifdef BSP_USING_PIN

struct rpi_pin_index
{
    rt_uint8_t phy_id;
    rt_uint8_t bcm_id;
    rt_uint8_t signal_name;
    rt_uint8_t magic;
};

//raspi phy id and bcm id
static struct rpi_pin_index phypin_index[] =
{
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {2, 0, 0, 0},
    {3, BCM_GPIO_PIN_2, RPI_SDA1, PIN_MAGIC},
    {4, 0, 0, 0},
    {5, BCM_GPIO_PIN_3, RPI_SCL1, PIN_MAGIC},
    {6, 0, 0, 0},
    {7, BCM_GPIO_PIN_4, RPI_GPIO_GCLK,  PIN_MAGIC},
    {8, BCM_GPIO_PIN_14, RPI_TXD0, PIN_MAGIC},
    {9, 0, 0, 0},
    {10, BCM_GPIO_PIN_15, RPI_RXD0, PIN_MAGIC},
    {11, BCM_GPIO_PIN_17, RPI_GPIO_GEN0,  PIN_MAGIC},
    {12, BCM_GPIO_PIN_18, RPI_GPIO_GEN1,  PIN_MAGIC},
    {13, BCM_GPIO_PIN_27, RPI_GPIO_GEN2,  PIN_MAGIC},
    {14, 0, 0, 0},
    {15, BCM_GPIO_PIN_22, RPI_GPIO_GEN3,  PIN_MAGIC},
    {16, BCM_GPIO_PIN_23, RPI_GPIO_GEN4, PIN_MAGIC},
    {17, 0, 0, 0},
    {18, BCM_GPIO_PIN_24, RPI_GPIO_GEN5, PIN_MAGIC},
    {19, BCM_GPIO_PIN_10, RPI_SPI_MOSI, PIN_MAGIC},
    {20, 0, 0, 0},
    {21, BCM_GPIO_PIN_9, RPI_SPI_MISO, PIN_MAGIC},
    {22, BCM_GPIO_PIN_25, RPI_GPIO_GEN6, PIN_MAGIC},
    {23, BCM_GPIO_PIN_11, RPI_SPI_SCLK, PIN_MAGIC},
    {24, BCM_GPIO_PIN_8, RPI_SPI_CE0_N, PIN_MAGIC},
    {25, 0, 0, 0},
    {26, BCM_GPIO_PIN_7, RPI_SPI_CE1_N, PIN_MAGIC},
    {27, BCM_GPIO_PIN_0, RPI_SDA0, PIN_MAGIC},
    {28, BCM_GPIO_PIN_1, RPI_SCL0, PIN_MAGIC},
    {29, BCM_GPIO_PIN_5, RPI_CAM_CLK, PIN_MAGIC},
    {30, 0, 0, 0},
    {31, BCM_GPIO_PIN_6, RPI_LAN_RUN, PIN_MAGIC},
    {32, BCM_GPIO_PIN_12, 0, PIN_MAGIC},
    {33, BCM_GPIO_PIN_13, 0, PIN_MAGIC},
    {34, 0, 0, 0},
    {35, BCM_GPIO_PIN_19, 0, PIN_MAGIC},
    {36, BCM_GPIO_PIN_16, RPI_STATUS_LED_N, PIN_MAGIC},
    {37, BCM_GPIO_PIN_26, 0, PIN_MAGIC},
    {38, BCM_GPIO_PIN_20, 0, PIN_MAGIC},
    {39, 0, 0, 0},
    {40, BCM_GPIO_PIN_21, RPI_CAM_GPIO,  PIN_MAGIC},
};

/*
 * gpio_int[0] for BANK0 (pins 0-27)
 * gpio_int[1] for BANK1 (pins 28-45)
 * gpio_int[2] for BANK2 (pins 46-53)
 */
static struct gpio_irq_def _g_gpio_irq_tbl[GPIO_IRQ_NUM];

int gpio_set_func(enum gpio_code code, enum bcm_gpio_pin pin, rt_uint8_t func)
{
    RT_ASSERT((GPIO_CODE_PHY <= code) && (code < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    if (func & 0x8)
    {
        rt_kprintf("[line]:%d There is a warning with parameter input", __LINE__);
        return RT_EINVAL;
    }

    switch(func)
    {
    case 0x00:
        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_OUTP);
        break;
    case 0x01:
        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_INPT);
        break;
    case 0x02:
        bcm283x_gpio_set_pud(pin, BCM283X_GPIO_PUD_UP);
        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_INPT);
        break;
    case 0x03:
        bcm283x_gpio_set_pud(pin, BCM283X_GPIO_PUD_DOWN);
        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_INPT);
        break;
    case 0x04:
        bcm283x_gpio_set_pud(pin, BCM283X_GPIO_PUD_OFF);
        bcm283x_gpio_fsel(pin, BCM283X_GPIO_FSEL_OUTP);
        break;
    }

    return RT_EOK;
}

int gpio_set_value(enum gpio_code code, enum bcm_gpio_pin pin, rt_uint8_t value)
{

    RT_ASSERT((GPIO_CODE_PHY <= code) && (code < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    if (value & 0xE)
    {
        rt_kprintf("[line]:%d There is a warning with parameter input", __LINE__);
        return RT_EINVAL;
    }

    bcm283x_gpio_write(pin, value);
    return RT_EOK;
}

int gpio_get_value(enum gpio_code code, enum bcm_gpio_pin pin)
{
    rt_uint8_t data;

    RT_ASSERT((GPIO_CODE_PHY <= code) && (code < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    data = bcm283x_gpio_lev(pin);
    return data;
}

void gpio_set_irq_callback(enum gpio_code port, enum bcm_gpio_pin pin, void (*irq_cb)(void *), void *irq_arg)
{
    RT_ASSERT((GPIO_CODE_PHY < port) && (port < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    rt_uint8_t index;
    if (pin <= 27)
    {
        index = 0;
    }
    else if (pin <= 45)
    {
        index = 1;
    }
    else{
        index = 2;
    }
    _g_gpio_irq_tbl[index].irq_cb[pin]    = irq_cb;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = irq_arg;
}

void gpio_set_irq_type(enum gpio_code port,  enum bcm_gpio_pin pin, rt_uint8_t irq_type)
{

    RT_ASSERT((GPIO_CODE_PHY < port) && (port < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    rt_uint8_t index;
    if (pin <= 27)
    {
        index = 0;
    }
    else if (pin <= 45)
    {
        index = 1;
    }
    else{
        index = 2;
    }
    _g_gpio_irq_tbl[index].irq_type[pin] = irq_type;

    switch(irq_type)
    {
    case 0x00:
        bcm283x_gpio_ren(pin);
        break;
    case 0x01:
        bcm283x_gpio_fen(pin);
        break;
    case 0x02:
        bcm283x_gpio_aren(pin);
        bcm283x_gpio_afen(pin);
        break;
    case 0x03:
        bcm283x_gpio_hen(pin);
        break;
    case 0x04:
        bcm283x_gpio_len(pin);
        break;
    }
}

static void gpio_ack_irq(int irq,  enum bcm_gpio_pin pin)
{
    rt_uint32_t data;
    data = IRQ_PEND2;
    data &= (0x0 << (irq - 32));
    IRQ_PEND2 = data;

    data = IRQ_DISABLE2;
    data |= (0x1 << (irq - 32));
    IRQ_DISABLE2 = data;
}

void gpio_irq_disable(enum gpio_code port,  enum bcm_gpio_pin pin)
{
    rt_uint8_t index;
    int irq = 0;
    RT_ASSERT((GPIO_CODE_PHY < port) && (port < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    if (pin <= 27)
    {
        index = 0;
        irq = IRQ_GPIO0;
    }else if (pin <= 45){
        index = 1;
        irq = IRQ_GPIO1;
    }else{
        index = 2;
        irq = IRQ_GPIO2;
    }

    gpio_ack_irq(irq, pin);

    rt_uint8_t irq_type = _g_gpio_irq_tbl[index].irq_type[pin];

    switch(irq_type)
    {
    case 0x00:
        bcm283x_gpio_clr_ren(pin);
        break;
    case 0x01:
        bcm283x_gpio_clr_fen(pin);
        break;
    case 0x02:
        bcm283x_gpio_clr_aren(pin);
        bcm283x_gpio_clr_afen(pin);
        break;
    case 0x03:
        bcm283x_gpio_clr_hen(pin);
        break;
    case 0x04:
        bcm283x_gpio_clr_len(pin);
        break;
    }
}

void gpio_clear_irq_callback(enum gpio_code port, enum bcm_gpio_pin pin)
{
    rt_uint8_t index;
    gpio_irq_disable(port, pin);

    if (pin <= 27)
    {
        index = 0;
    }
    else if (pin <= 45)
    {
        index = 1;
    }
    else
    {
        index = 2;
    }

    _g_gpio_irq_tbl[index].irq_cb[pin]    = RT_NULL;
    _g_gpio_irq_tbl[index].irq_arg[pin]   = RT_NULL;
    _g_gpio_irq_tbl[index].irq_type[pin]  = RT_NULL;

}


void gpio_irq_enable(enum gpio_code port,  enum bcm_gpio_pin pin)
{

    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_CODE_PHY < port) && (port < GPIO_CODE_NUM));
    RT_ASSERT((BCM_GPIO_PIN_0 <= pin) && (pin < BCM_GPIO_PIN_53));

    offset = pin;
    if (pin <= 27)
    {
        offset = IRQ_GPIO0 - 32;
    }
    else if (pin <= 45)
    {
        offset = IRQ_GPIO1 - 32;
    }
    else
    {
        offset = IRQ_GPIO2 - 32;
    }

    data = IRQ_ENABLE2;
    data |= 0x1 << offset;
    IRQ_ENABLE2 = data;

}

//gpio_int[0] for BANK0 (pins 0-27)
//gpio_int[1] for BANK1 (pins 28-45)
//gpio_int[2] for BANK2 (pins 46-53)
static void gpio_irq_handler(int irq, void *param)
{
    struct gpio_irq_def *irq_def = (struct gpio_irq_def *)param;
    rt_uint32_t pin;
    rt_uint32_t addr;
    rt_uint32_t value;
    rt_uint32_t tmpvalue;

    if (irq == IRQ_GPIO0)
    {
        /* 0~27 */
        addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPEDS0; // 0~31
        value = bcm283x_peri_read(addr);
        value &= 0x0fffffff;
        pin = 0;
    }
    else if (irq == IRQ_GPIO1)
    {
        /* 28-45 */
        addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPEDS0;
        tmpvalue = bcm283x_peri_read(addr);
        tmpvalue &= (~0x0fffffff);

        addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPEDS1;
        value = bcm283x_peri_read(addr);
        value &= 0x3fff;
        value = (value<<4) | tmpvalue;

        pin = 28;
    }
    else if (irq == IRQ_GPIO2)
    {
        /* 46-53 */
        addr = BCM283X_GPIO_BASE + BCM283X_GPIO_GPEDS1;
        value = bcm283x_peri_read(addr);
        value &= (~0x3fff);
        value &= 0xff600000;
        pin = 46;
    }

    bcm283x_peri_write(addr,0);

    while (value)
    {
        if ((value & 0x1) && (irq_def->irq_cb[pin] != RT_NULL))
        {
            irq_def->irq_cb[pin](irq_def->irq_arg[pin]);
            gpio_ack_irq(irq,pin);
        }
        pin++;
        value = value >> 1;
    }
}

static void pin_mode(struct rt_device *dev, rt_base_t pin, rt_base_t mode)
{
    if ((pin > PIN_NUM(phypin_index)) || (phypin_index[pin].magic != PIN_MAGIC))
    {
        rt_kprintf("pin:%d value wrongful", pin);
        return;
    }

    gpio_set_func(GPIO_CODE_BCM, phypin_index[pin].bcm_id, mode);
}

static void pin_write(struct rt_device *dev, rt_base_t pin, rt_base_t value)
{
    if ((pin > PIN_NUM(phypin_index)) || (phypin_index[pin].magic != PIN_MAGIC))
    {
        rt_kprintf("pin:%d value wrongful", pin);
        return;
    }

    gpio_set_value(GPIO_CODE_BCM, phypin_index[pin].bcm_id, value);
}

static int pin_read(struct rt_device *device, rt_base_t pin)
{
    if ((pin > PIN_NUM(phypin_index)) || (phypin_index[pin].magic != PIN_MAGIC))
    {
        rt_kprintf("pin:%d value wrongful", pin);
        return 0;
    }

    return gpio_get_value(GPIO_CODE_BCM, phypin_index[pin].bcm_id);
}

static rt_err_t pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    if ((pin > PIN_NUM(phypin_index)) || (phypin_index[pin].magic != PIN_MAGIC))
    {
        rt_kprintf("pin:%d value wrongful", pin);
        return RT_ERROR;
    }

    gpio_set_irq_callback(GPIO_CODE_BCM , phypin_index[pin].bcm_id, hdr, args);
    gpio_set_irq_type(GPIO_CODE_BCM, phypin_index[pin].bcm_id, mode);

    return RT_EOK;
}

static rt_err_t pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    if ((pin > PIN_NUM(phypin_index)) || (phypin_index[pin].magic != PIN_MAGIC))
    {
        rt_kprintf("pin:%d value wrongful", pin);
        return RT_ERROR;
    }

    gpio_clear_irq_callback(GPIO_CODE_BCM, phypin_index[pin].bcm_id);

    return RT_EOK;
}

rt_err_t pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    if ((pin > PIN_NUM(phypin_index)) || (phypin_index[pin].magic != PIN_MAGIC))
    {
        rt_kprintf("pin:%d value wrongful", pin);
        return RT_ERROR;
    }

    if (enabled)
        gpio_irq_enable(GPIO_CODE_BCM, phypin_index[pin].bcm_id);
    else
        gpio_irq_disable(GPIO_CODE_BCM, phypin_index[pin].bcm_id);

    return RT_EOK;
}

static const struct rt_pin_ops ops =
{
    pin_mode,
    pin_write,
    pin_read,
    pin_attach_irq,
    pin_detach_irq,
    pin_irq_enable,
};
#endif

int rt_hw_gpio_init(void)
{
#ifdef BSP_USING_PIN
    rt_device_pin_register("gpio", &ops, RT_NULL);
#endif

    /* install ISR */
    rt_hw_interrupt_install(IRQ_GPIO0, gpio_irq_handler, &_g_gpio_irq_tbl[0], "gpio0_irq");
    rt_hw_interrupt_umask(IRQ_GPIO0);

    rt_hw_interrupt_install(IRQ_GPIO1, gpio_irq_handler, &_g_gpio_irq_tbl[1], "gpio1_irq");
    rt_hw_interrupt_umask(IRQ_GPIO1);

    rt_hw_interrupt_install(IRQ_GPIO2, gpio_irq_handler, &_g_gpio_irq_tbl[2], "gpio2_irq");
    rt_hw_interrupt_umask(IRQ_GPIO2);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gpio_init);
