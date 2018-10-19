/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 * 2018-03-24     LaiYiKeTang add hardware iic
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_lpi2c.h"
#include "drv_i2c.h"

//#define DRV_I2C_DEBUG

#ifdef RT_USING_I2C

#define I2C1BUS_NAME  "i2c1"
#define I2C2BUS_NAME  "i2c2"
#define I2C3BUS_NAME  "i2c3"
#define I2C4BUS_NAME  "i2c4"

#define LPI2C_CLOCK_SOURCE_DIVIDER 4

/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER))

#ifdef RT_USING_HW_I2C1
static struct rt1052_i2c_bus lpi2c1 =
{
    .I2C = LPI2C1,
    .device_name = I2C1BUS_NAME,
};
#endif /* RT_USING_HW_I2C1 */

#ifdef RT_USING_HW_I2C2
static struct rt1052_i2c_bus lpi2c2 =
{
    .I2C = LPI2C2,
    .device_name = I2C2BUS_NAME,
};
#endif /* RT_USING_HW_I2C2 */

#ifdef RT_USING_HW_I2C3
static struct rt1052_i2c_bus lpi2c3 =
{
    .I2C = LPI2C3,
    .device_name = I2C3BUS_NAME,
};
#endif /* RT_USING_HW_I2C3 */

#ifdef RT_USING_HW_I2C4
static struct rt1052_i2c_bus lpi2c4 =
{
    .I2C = LPI2C4,
    .device_name = I2C4BUS_NAME,
};
#endif /* RT_USING_HW_I2C4 */

#if (defined(RT_USING_HW_I2C1) || defined(RT_USING_HW_I2C2) || defined(RT_USING_HW_I2C3) || defined(RT_USING_HW_I2C4))

static rt_size_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_size_t imxrt_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_err_t imxrt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      rt_uint32_t,
                                      rt_uint32_t);

static const struct rt_i2c_bus_device_ops imxrt_i2c_ops =
{
    imxrt_i2c_mst_xfer,
    imxrt_i2c_slv_xfer,
    imxrt_i2c_bus_control,
};

void imxrt_lpi2c_gpio_init(struct rt1052_i2c_bus *bus)
{
    if (bus->I2C == LPI2C1)
    {
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL,
            1U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA,
            1U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL,
            0xD8B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA,
            0xD8B0u);
    }
    else if (bus->I2C == LPI2C2)
    {
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_B0_04_LPI2C2_SCL,
            1U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_B0_05_LPI2C2_SDA,
            1U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_B0_04_LPI2C2_SCL,
            0xD8B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_B0_05_LPI2C2_SDA,
            0xD8B0u);
    }
    else if (bus->I2C == LPI2C3)
    {
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL,
            1U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA,
            1U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL,
            0xD8B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA,
            0xD8B0u);
    }
    else if (bus->I2C == LPI2C4)
    {
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_EMC_12_LPI2C4_SCL,
            1U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_EMC_11_LPI2C4_SDA,
            1U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_EMC_12_LPI2C4_SCL,
            0xD8B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_EMC_11_LPI2C4_SDA,
            0xD8B0u);
    }
    else
    {
        RT_ASSERT(RT_NULL);
    }
}

static rt_err_t imxrt_lpi2c_configure(struct rt1052_i2c_bus *bus, lpi2c_master_config_t *cfg)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    imxrt_lpi2c_gpio_init(bus);
    bus->parent.ops = &imxrt_i2c_ops;
    LPI2C_MasterInit(bus->I2C, cfg, LPI2C_CLOCK_FREQUENCY);
    return RT_EOK;
}

status_t LPI2C_MasterCheck(LPI2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new transfer can start. */
    status &= 0x3c00;
    if (status)
    {
        /* Select the correct error code. Ordered by severity, with bus issues first. */
        if (status & kLPI2C_MasterPinLowTimeoutFlag)
        {
            result = kStatus_LPI2C_PinLowTimeout;
        }
        else if (status & kLPI2C_MasterArbitrationLostFlag)
        {
            result = kStatus_LPI2C_ArbitrationLost;
        }
        else if (status & kLPI2C_MasterNackDetectFlag)
        {
            result = kStatus_LPI2C_Nak;
        }
        else if (status & kLPI2C_MasterFifoErrFlag)
        {
            result = kStatus_LPI2C_FifoError;
        }
        else
        {
            assert(false);
        }

        /* Clear the flags. */
        LPI2C_MasterClearStatusFlags(base, status);

        /* Reset fifos. These flags clear automatically. */
        base->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;
    }

    return result;
}

/*!
 * @brief Wait until the tx fifo all empty.
 * @param base The LPI2C peripheral base address.
 * @retval #kStatus_Success
 * @retval #kStatus_LPI2C_PinLowTimeout
 * @retval #kStatus_LPI2C_ArbitrationLost
 * @retval #kStatus_LPI2C_Nak
 * @retval #kStatus_LPI2C_FifoError
 */
static status_t LPI2C_MasterWaitForTxFifoAllEmpty(LPI2C_Type *base)
{
    uint32_t status;
    size_t txCount;
    do
    {
        status_t result;

        /* Get the number of words in the tx fifo and compute empty slots. */
        LPI2C_MasterGetFifoCounts(base, NULL, &txCount);

        /* Check for error flags. */
        status = LPI2C_MasterGetStatusFlags(base);
        result = LPI2C_MasterCheck(base, status);
        if (result)
        {
            return result;
        }
    }
    while (txCount);
    return kStatus_Success;
}

static rt_size_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    struct rt1052_i2c_bus *rt1052_i2c;
    rt_size_t i;
    RT_ASSERT(bus != RT_NULL);
    rt1052_i2c = (struct rt1052_i2c_bus *) bus;

    rt1052_i2c->msg = msgs;
    rt1052_i2c->msg_ptr = 0;
    rt1052_i2c->msg_cnt = num;
    rt1052_i2c->dptr = 0;

    for (i = 0; i < num; i++)
    {
        if (rt1052_i2c->msg[i].flags & RT_I2C_RD)
        {
            if (LPI2C_MasterStart(rt1052_i2c->I2C, rt1052_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (LPI2C_MasterWaitForTxFifoAllEmpty(rt1052_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (LPI2C_MasterReceive(rt1052_i2c->I2C, rt1052_i2c->msg[i].buf, rt1052_i2c->msg[i].len) != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (LPI2C_MasterWaitForTxFifoAllEmpty(rt1052_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }
        }
        else
        {
            if (LPI2C_MasterStart(rt1052_i2c->I2C, rt1052_i2c->msg[i].addr, kLPI2C_Write) != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (LPI2C_MasterWaitForTxFifoAllEmpty(rt1052_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (LPI2C_MasterSend(rt1052_i2c->I2C, rt1052_i2c->msg[i].buf, rt1052_i2c->msg[i].len) != kStatus_Success)
            {
                i = 0;
                break;
            }
            if (LPI2C_MasterWaitForTxFifoAllEmpty(rt1052_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }
        }
    }
    i2c_dbg("send stop condition\n");
    if (LPI2C_MasterStop(rt1052_i2c->I2C) != kStatus_Success)
    {
        i = 0;
    }

    rt1052_i2c->msg = RT_NULL;
    rt1052_i2c->msg_ptr = 0;
    rt1052_i2c->msg_cnt = 0;
    rt1052_i2c->dptr = 0;
    return i;
}

static rt_size_t imxrt_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    return 0;
}
static rt_err_t imxrt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      rt_uint32_t cmd,
                                      rt_uint32_t arg)
{
    return RT_ERROR;
}

#endif

int rt_hw_i2c_init(void)
{
#if (defined(RT_USING_HW_I2C1) || defined(RT_USING_HW_I2C2) || defined(RT_USING_HW_I2C3) || defined(RT_USING_HW_I2C4))

    lpi2c_master_config_t masterConfig = {0};

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, 0);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER - 1);

#endif

#if   defined(RT_USING_HW_I2C1)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C1_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C1_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif
    imxrt_lpi2c_configure(&lpi2c1, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c1.parent, lpi2c1.device_name);
#endif

#if   defined(RT_USING_HW_I2C2)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C2_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C2_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif
    imxrt_lpi2c_configure(&lpi2c2, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c2.parent, lpi2c2.device_name);
#endif

#if   defined(RT_USING_HW_I2C3)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C3_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C3_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif
    imxrt_lpi2c_configure(&lpi2c3, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c3.parent, lpi2c3.device_name);
#endif

#if   defined(RT_USING_HW_I2C4)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C4_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C4_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif
    imxrt_lpi2c_configure(&lpi2c4, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c4.parent, lpi2c4.device_name);
#endif

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
FINSH_FUNCTION_EXPORT(i2c_test, e.g: i2c_test("i2c1", 0xA3));

#endif

#endif /* RT_USING_I2C */
