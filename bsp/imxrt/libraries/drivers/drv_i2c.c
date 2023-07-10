/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang         the first version
 * 2018-03-24     LaiYiKeTang  add hardware iic
 * 2019-04-22     tyustli      add imxrt series support
 *
 */

#include <rtthread.h>

#ifdef BSP_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && !defined(BSP_USING_I2C3) && !defined(BSP_USING_I2C4) && !defined(BSP_USING_I2C5)&& !defined(BSP_USING_I2C6)
#error "Please define at least one BSP_USING_I2Cx"
#endif

#include <rtdevice.h>
#include "fsl_lpi2c.h"
#include "drv_i2c.h"

struct imxrt_i2c_bus
{
    struct rt_i2c_bus_device parent;
    LPI2C_Type *I2C;
    struct rt_i2c_msg *msg;
    rt_uint32_t msg_cnt;
    volatile rt_uint32_t msg_ptr;
    volatile rt_uint32_t dptr;
    char *device_name;
#ifdef SOC_IMXRT1170_SERIES
    clock_root_t clock_root;
#endif
};

#if defined (BSP_USING_I2C1)
#define I2C1BUS_NAME  "i2c1"
#endif /*BSP_USING_I2C1*/

#if defined (BSP_USING_I2C2)
#define I2C2BUS_NAME  "i2c2"
#endif /*BSP_USING_I2C2*/

#if !defined (MIMXRT1015_SERIES)      /* imxrt1015 only have two i2c bus*/

#if defined (BSP_USING_I2C3)
#define I2C3BUS_NAME  "i2c3"
#endif /*BSP_USING_I2C3*/

#if defined (BSP_USING_I2C4)
#define I2C4BUS_NAME  "i2c4"
#endif /*BSP_USING_I2C4*/

#if defined (BSP_USING_I2C5)
#define I2C5BUS_NAME "i2c5"
#endif /*BSP_USING_I2C5*/

#if defined (BSP_USING_I2C6)
#define I2C6BUS_NAME  "i2c6"
#endif /*BSP_USING_I2C6*/

#endif /* MIMXRT1015_SERIES */

/* Select USB1 PLL (360 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (1U)
#ifdef SOC_IMXRT1170_SERIES
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (12U)
#else
#define LPI2C_CLOCK_SOURCE_DIVIDER (0U)

/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

#endif
#ifdef BSP_USING_I2C1
static struct imxrt_i2c_bus lpi2c1 =
{
    .I2C = LPI2C1,
    .device_name = I2C1BUS_NAME,
};
#endif /* RT_USING_HW_I2C1 */

#ifdef BSP_USING_I2C2
static struct imxrt_i2c_bus lpi2c2 =
{
    .I2C = LPI2C2,
    .device_name = I2C2BUS_NAME,
};
#endif /* RT_USING_HW_I2C2 */

#if !defined (MIMXRT1015_SERIES)        /* imxrt1015 only have two i2c bus*/

#ifdef BSP_USING_I2C3
static struct imxrt_i2c_bus lpi2c3 =
{
    .I2C = LPI2C3,
    .device_name = I2C3BUS_NAME,
};
#endif /* RT_USING_HW_I2C3 */

#ifdef BSP_USING_I2C4
static struct imxrt_i2c_bus lpi2c4 =
{
    .I2C = LPI2C4,
    .device_name = I2C4BUS_NAME,
};
#endif /* RT_USING_HW_I2C4 */

#ifdef BSP_USING_I2C5
static struct imxrt_i2c_bus lpi2c5 =
{
    .I2C = LPI2C5,
    .device_name = I2C5BUS_NAME,
};
#endif /* RT_USING_HW_I2C5 */

#ifdef BSP_USING_I2C6
static struct imxrt_i2c_bus lpi2c6 =
{
    .I2C = LPI2C6,
    .device_name = I2C6BUS_NAME,
};
#endif /* RT_USING_HW_I2C6 */

#endif /* MIMXRT1015_SERIES */

#if (defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3) || defined(BSP_USING_I2C4) ||defined(BSP_USING_I2C5) || defined(BSP_USING_I2C6))

static rt_ssize_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_ssize_t imxrt_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_err_t imxrt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      int cmd,
                                      void *args);

static const struct rt_i2c_bus_device_ops imxrt_i2c_ops =
{
    .master_xfer = imxrt_i2c_mst_xfer,
    .slave_xfer = imxrt_i2c_slv_xfer,
    .i2c_bus_control = imxrt_i2c_bus_control,
};

static rt_err_t imxrt_lpi2c_configure(struct imxrt_i2c_bus *bus, lpi2c_master_config_t *cfg)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    bus->parent.ops = &imxrt_i2c_ops;
#ifdef SOC_IMXRT1170_SERIES
    clock_root_config_t rootCfg = {0};
    rootCfg.mux = LPI2C_CLOCK_SOURCE_SELECT;
    rootCfg.div = LPI2C_CLOCK_SOURCE_DIVIDER + 1;
    CLOCK_SetRootClock(bus->clock_root, &rootCfg);
    volatile uint32_t freq = CLOCK_GetRootClockFreq(bus->clock_root);
    LPI2C_MasterInit(bus->I2C, cfg, freq);
#else
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    LPI2C_MasterInit(bus->I2C, cfg, LPI2C_CLOCK_FREQUENCY);
#endif

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

static rt_ssize_t imxrt_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    struct imxrt_i2c_bus *imxrt_i2c;
    rt_size_t i;
    RT_ASSERT(bus != RT_NULL);
    imxrt_i2c = (struct imxrt_i2c_bus *) bus;

    imxrt_i2c->msg = msgs;
    imxrt_i2c->msg_ptr = 0;
    imxrt_i2c->msg_cnt = num;
    imxrt_i2c->dptr = 0;

    for (i = 0; i < num; i++)
    {
        if (imxrt_i2c->msg[i].flags & RT_I2C_RD)
        {
            if ((imxrt_i2c->msg[i].flags & RT_I2C_NO_START) != RT_I2C_NO_START)
            {
                if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Write) != kStatus_Success)
                {
                    i = 0;
                    break;
                }

                while (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
                {
                }

                if (LPI2C_MasterRepeatedStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
                {
                    i = 0;
                    break;
                }
            }
            else
            {
                if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
                {
                    i = 0;
                    break;
                }

                while (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
                {
                }
            }

            if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Read) != kStatus_Success)
            {
                i = 0;
                break;
            }

            while (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
            {
            }

            if (LPI2C_MasterReceive(imxrt_i2c->I2C, imxrt_i2c->msg[i].buf, imxrt_i2c->msg[i].len) != kStatus_Success)
            {
                i = 0;
                break;
            }
        }
        else
        {
            if (LPI2C_MasterStart(imxrt_i2c->I2C, imxrt_i2c->msg[i].addr, kLPI2C_Write) != kStatus_Success)
            {
                i = 0;
                break;
            }

            // while((LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterBusBusyFlag))
            // {
            // }
            if(LPI2C_MasterWaitForTxFifoAllEmpty(imxrt_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }

            if (LPI2C_MasterGetStatusFlags(imxrt_i2c->I2C) & kLPI2C_MasterNackDetectFlag)
            {
                i = 0;
                break;
            }

            if (LPI2C_MasterSend(imxrt_i2c->I2C, imxrt_i2c->msg[i].buf, imxrt_i2c->msg[i].len) != kStatus_Success)
            {
                i = 0;
                break;
            }

            if (LPI2C_MasterWaitForTxFifoAllEmpty(imxrt_i2c->I2C) != kStatus_Success)
            {
                i = 0;
                break;
            }
        }

        if (LPI2C_MasterStop(imxrt_i2c->I2C) != kStatus_Success)
        {
            i = 0;
        }

    }

    imxrt_i2c->msg = RT_NULL;
    imxrt_i2c->msg_ptr = 0;
    imxrt_i2c->msg_cnt = 0;
    imxrt_i2c->dptr = 0;

    return i;
}

static rt_ssize_t imxrt_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    return 0;
}
static rt_err_t imxrt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      int cmd,
                                      void *args)
{
    return -RT_ERROR;
}

#endif

int rt_hw_i2c_init(void)
{
    lpi2c_master_config_t masterConfig = {0};

#if   defined(BSP_USING_I2C1)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C1_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C1_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /*HW_I2C1_BADURATE_400kHZ*/
    imxrt_lpi2c_configure(&lpi2c1, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c1.parent, lpi2c1.device_name);
#endif  /* BSP_USING_I2C1 */

#if   defined(BSP_USING_I2C2)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C2_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C2_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C2_BADURATE_400kHZ */
    imxrt_lpi2c_configure(&lpi2c2, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c2.parent, lpi2c2.device_name);
#endif  /* BSP_USING_I2C2 */

#if !defined(MIMXRT1015_SERIES) /* imxrt1015 only have two i2c bus*/

#if   defined(BSP_USING_I2C3)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C3_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C3_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C3_BADURATE_400kHZ */
    imxrt_lpi2c_configure(&lpi2c3, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c3.parent, lpi2c3.device_name);
#endif  /* BSP_USING_I2C3 */

#if   defined(BSP_USING_I2C4)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C4_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C4_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C4_BADURATE_400kHZ */
    imxrt_lpi2c_configure(&lpi2c4, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c4.parent, lpi2c4.device_name);
#endif /* BSP_USING_I2C4 */

#if   defined(BSP_USING_I2C5)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C5_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C5_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C5_BADURATE_400kHZ */
    lpi2c5.clock_root = kCLOCK_Root_Lpi2c5;
    imxrt_lpi2c_configure(&lpi2c5, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c5.parent, lpi2c5.device_name);
#endif /* BSP_USING_I2C5 */

#if   defined(BSP_USING_I2C6)
    LPI2C_MasterGetDefaultConfig(&masterConfig);
#if   defined(HW_I2C6_BADURATE_400kHZ)
    masterConfig.baudRate_Hz = 400000U;
#elif defined(HW_I2C6_BADURATE_100kHZ)
    masterConfig.baudRate_Hz = 100000U;
#endif  /* HW_I2C6_BADURATE_400kHZ */
    lpi2c6.clock_root = kCLOCK_Root_Lpi2c6;
    imxrt_lpi2c_configure(&lpi2c6, &masterConfig);
    rt_i2c_bus_device_register(&lpi2c6.parent, lpi2c6.device_name);
#endif /* BSP_USING_I2C6 */


#endif /* MIMXRT1015_SERIES */

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */
