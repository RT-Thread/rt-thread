/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */
 
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"

#ifdef RT_USING_I2C

#ifdef RT_USING_I2C_BITOPS

struct lpc_i2c_bit_data
{
    struct
    {
        GPIO_Type *base;
        uint32_t port;
        uint32_t pin;
    } scl, sda;
};

static void gpio_set_sda(void *data, rt_int32_t state)
{
    struct lpc_i2c_bit_data *bd = data;

    if (state)
    {
        //bd->sda.base->B[bd->sda.port][bd->sda.pin] = 1;
        GPIO_WritePinOutput(bd->sda.base, bd->sda.port, bd->sda.pin, 1);
    }
    else
    {
        GPIO_WritePinOutput(bd->sda.base, bd->sda.port, bd->sda.pin, 0);
    }
}

static void gpio_set_scl(void *data, rt_int32_t state)
{
    struct lpc_i2c_bit_data *bd = data;

    if (state)
    {
        //bd->scl.base->B[bd->sda.port][bd->sda.pin] = 1;
        GPIO_WritePinOutput(bd->scl.base, bd->scl.port, bd->scl.pin, 1);
    }
    else
    {
        //bd->scl.base->B[bd->sda.port][bd->sda.pin] = 0;
        GPIO_WritePinOutput(bd->scl.base, bd->scl.port, bd->scl.pin, 0);
    }
}

static rt_int32_t gpio_get_sda(void *data)
{
    struct lpc_i2c_bit_data *bd = data;

    return GPIO_ReadPinInput(bd->sda.base, bd->sda.port, bd->sda.pin) & 0x01;
}

static rt_int32_t gpio_get_scl(void *data)
{
    struct lpc_i2c_bit_data *bd = data;

    return GPIO_ReadPinInput(bd->scl.base, bd->scl.port, bd->scl.pin) & 0x01;
}

static void gpio_udelay(rt_uint32_t us)
{
    volatile rt_int32_t i;
    for (; us > 0; us--)
    {
        i = 10;
        while (i--);
    }
}

#else /* RT_USING_I2C_BITOPS */

#define IOCON_PIO_DIGITAL_EN        0x0100u   /*!< Enables digital function */
#define IOCON_PIO_FUNC0               0x00u   /*!< Selects pin function 0 */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC6               0x06u   /*!< Selects pin function 6 */
#define IOCON_PIO_I2CDRIVE_HIGH     0x0400u   /*!< High drive: 20 mA */
#define IOCON_PIO_I2CFILTER_EN        0x00u   /*!< I2C 50 ns glitch filter enabled */
#define IOCON_PIO_I2CSLEW_I2C         0x00u   /*!< I2C mode */
#define IOCON_PIO_INPFILT_OFF       0x0200u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_MODE_PULLUP         0x20u   /*!< Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_FAST         0x0400u   /*!< Fast mode, slew rate control is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port 3 */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port 3 */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port 0 */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port 0 */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port 0 */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port 0 */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port 0 */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port 0 */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port 0 */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port 0 */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port 1 */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port 1 */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port 1 */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port 1 */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port 1 */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port 0 */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port 1 */
#define PIN18_IDX                       18u   /*!< Pin number for pin 18 in a port 0 */
#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port 0 */
#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port 0 */
#define PIN21_IDX                       21u   /*!< Pin number for pin 21 in a port 0 */
#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port 2 */
#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port 1 */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port 1 */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port 1 */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port 1 */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port 1 */
#define PIN28_IDX                       28u   /*!< Pin number for pin 28 in a port 1 */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port 0 */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port 0 */
#define PIN31_IDX                       31u   /*!< Pin number for pin 31 in a port 1 */
#define PORT0_IDX                        0u   /*!< Port index */
#define PORT1_IDX                        1u   /*!< Port index */
#define PORT2_IDX                        2u   /*!< Port index */
#define PORT3_IDX                        3u   /*!< Port index */


struct lpc_i2c_bus
{
    struct rt_i2c_bus_device parent;
    I2C_Type *I2C;
};

static rt_size_t lpc_i2c_xfer(struct rt_i2c_bus_device *bus,
                              struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    i2c_master_transfer_t xfer = {0};
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    struct lpc_i2c_bus *lpc_i2c = (struct lpc_i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            xfer.slaveAddress = msg->addr;
            xfer.direction = kI2C_Read;
            xfer.subaddress = 1;
            xfer.subaddressSize = 1;
            xfer.data = msg->buf;
            xfer.dataSize = msg->len;
            xfer.flags = kI2C_TransferDefaultFlag;

            if (I2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
        else
        {
            xfer.slaveAddress = msg->addr;
            xfer.direction = kI2C_Write;
            xfer.subaddress = 0;
            xfer.subaddressSize = 1;
            xfer.data = msg->buf;
            xfer.dataSize = msg->len;
            xfer.flags = kI2C_TransferDefaultFlag;

            if (I2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
    }
    ret = i;

out:
    i2c_dbg("send stop condition\n");

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    lpc_i2c_xfer,
    RT_NULL,
    RT_NULL
};

#endif /* RT_USING_I2C_BITOPS */

int rt_hw_i2c_init(void)
{
#ifdef RT_USING_I2C_BITOPS
    /* register I2C1: SCL/P0_20 SDA/P0_19 */
    {
        static struct rt_i2c_bus_device i2c_device;

        static const struct lpc_i2c_bit_data _i2c_bdata =
        {
            /* SCL */ {GPIO, 3, 24},
            /* SDA */ {GPIO, 3, 23},
        };

        static const struct rt_i2c_bit_ops _i2c_bit_ops =
        {
            (void*)&_i2c_bdata,
            gpio_set_sda,
            gpio_set_scl,
            gpio_get_sda,
            gpio_get_scl,

            gpio_udelay,

            5,
            100
        };

        gpio_pin_config_t pin_config = {
            kGPIO_DigitalOutput, 0,
        };

        CLOCK_EnableClock(kCLOCK_Gpio3);

        /* Enable touch panel controller */
        GPIO_PinInit(GPIO, _i2c_bdata.sda.port, _i2c_bdata.sda.pin, &pin_config);
        GPIO_PinInit(GPIO, _i2c_bdata.scl.port, _i2c_bdata.scl.pin, &pin_config);

        GPIO_WritePinOutput(GPIO, _i2c_bdata.sda.port, _i2c_bdata.sda.pin, 1);
        GPIO_WritePinOutput(GPIO, _i2c_bdata.scl.port, _i2c_bdata.scl.pin, 1);

        i2c_device.priv = (void *)&_i2c_bit_ops;
        rt_i2c_bit_add_bus(&i2c_device, "i2c2");
    } /* register I2C */

#else /* RT_USING_I2C_BITOPS */
    static struct lpc_i2c_bus lpc_i2c2;

    /* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

    const uint32_t port3_pin23_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC2_CTS_SDA_SSEL0 */
                                            IOCON_PIO_I2CSLEW_I2C |                                  /* I2C mode */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_I2CDRIVE_HIGH |                                /* High drive: 20 mA */
                                            IOCON_PIO_I2CFILTER_EN                                   /* I2C 50 ns glitch filter enabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN23_IDX, port3_pin23_config); /* PORT3 PIN23 (coords: C2) is configured as FC2_CTS_SDA_SSEL0 */
    const uint32_t port3_pin24_config = (
                                            IOCON_PIO_FUNC1 |                                        /* Pin is configured as FC2_RTS_SCL_SSEL1 */
                                            IOCON_PIO_I2CSLEW_I2C |                                  /* I2C mode */
                                            IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                            IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                            IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                            IOCON_PIO_I2CDRIVE_HIGH |                                /* High drive: 20 mA */
                                            IOCON_PIO_I2CFILTER_EN                                   /* I2C 50 ns glitch filter enabled */
                                        );
    IOCON_PinMuxSet(IOCON, PORT3_IDX, PIN24_IDX, port3_pin24_config); /* PORT3 PIN24 (coords: E2) is configured as FC2_RTS_SCL_SSEL1 */

    {
        i2c_master_config_t masterConfig;

        I2C_MasterGetDefaultConfig(&masterConfig);

        /* Change the default baudrate configuration */
        masterConfig.baudRate_Bps = 100000U;

        /* Initialize the I2C master peripheral */
        I2C_MasterInit(I2C2, &masterConfig, 12000000);
    }

    rt_memset((void *)&lpc_i2c2, 0, sizeof(struct lpc_i2c_bus));
    lpc_i2c2.parent.ops = &i2c_ops;
    lpc_i2c2.I2C = I2C2;
    rt_i2c_bus_device_register(&lpc_i2c2.parent, "i2c2");

#endif /* RT_USING_I2C_BITOPS */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
