/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-13     Lyons        first version
 * 2021-06-23     RiceChen     refactor
 */

#include <rthw.h>
#include <rtdevice.h>

#ifdef BSP_USING_I2C

#define LOG_TAG              "drv.i2c"
#include <drv_log.h>

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2) && !defined(BSP_USING_I2C3) && !defined(BSP_USING_I2C4)
#error "Please define at least one BSP_USING_I2Cx"
#endif

#include "fsl_iomuxc.h"
#include "drv_i2c.h"

static struct imx6ull_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C2
    I2C2_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C3
    I2C3_BUS_CONFIG,
#endif
#ifdef BSP_USING_I2C4
    I2C4_BUS_CONFIG,
#endif
};

static struct imx6ull_i2c_bus i2c_obj[sizeof(i2c_config) / sizeof(i2c_config[0])];
static char i2c_buff_temp[4][1024];
extern uint32_t I2C_GetInstance(I2C_Type *base);

#ifdef IMX_I2C_IRQ_MODE
static uint32_t g_MasterCompletionFlag[4] = {0,0,0,0};
static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    struct imx6ull_i2c_config *config;

    config = (struct imx6ull_i2c_config*)userData;

    uint32_t instance = I2C_GetInstance(config->hw_base);
    if (status == kStatus_Success)
    {
        g_MasterCompletionFlag[instance-1] = 1;
    }
}
#endif

static rt_ssize_t imx6ull_i2c_mst_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    rt_ssize_t i = 0;
    struct imx6ull_i2c_bus *i2c_bus = RT_NULL;
    static i2c_master_transfer_t xfer = {0};
    RT_ASSERT(bus != RT_NULL);
#ifdef IMX_I2C_IRQ_MODE
    uint32_t timeout_cnt = 100;
#endif
    uint32_t instance = 0;

    i2c_bus = (struct imx6ull_i2c_bus *)bus;
    instance = I2C_GetInstance(i2c_bus->config->hw_base);
    for(i = 0 ;i < num; i++)
    {
        if(msgs[i].flags & RT_I2C_RD)
        {
            xfer.flags = kI2C_TransferNoStartFlag;
            xfer.slaveAddress = msgs[i].addr;
            xfer.direction = kI2C_Read;
            xfer.subaddress = 0;
            xfer.subaddressSize = 0;
            xfer.data = (uint8_t *volatile)i2c_buff_temp[instance - 1];
            xfer.dataSize = msgs[i].len ;

#ifdef IMX_I2C_IRQ_MODE
            I2C_MasterTransferNonBlocking(i2c_bus->config->I2C, &i2c_bus->config->master_handle,&xfer);
            while(!g_MasterCompletionFlag[instance - 1])
            {
                rt_thread_delay(1);
                timeout_cnt--;
                if(timeout_cnt == 0)
                {
                    break;
                }
            }
            timeout_cnt = 100;
            g_MasterCompletionFlag[instance - 1] = 0;
#else
            I2C_MasterTransferBlocking(i2c_bus->config->I2C, &xfer);
#endif
            rt_memcpy(msgs[i].buf,i2c_buff_temp[instance - 1],msgs[i].len);
        }
        else
        {
            xfer.flags = kI2C_TransferNoStartFlag;
            xfer.slaveAddress = msgs[i].addr;
            xfer.direction = kI2C_Write;
            xfer.subaddress = 0;
            xfer.subaddressSize = 0;
            xfer.data = (uint8_t *volatile)i2c_buff_temp[instance - 1];
            xfer.dataSize = msgs[i].len;
            rt_memcpy(i2c_buff_temp[instance - 1],msgs[i].buf,msgs[i].len);

#ifdef IMX_I2C_IRQ_MODE
            I2C_MasterTransferNonBlocking(i2c_bus->config->I2C, &i2c_bus->config->master_handle,&xfer);
            while(!g_MasterCompletionFlag[instance - 1])
            {
                timeout_cnt--;
                rt_thread_delay(1);
                if(timeout_cnt == 0)
                {
                    break;
                }
            }
            timeout_cnt = 100;
            g_MasterCompletionFlag[instance - 1] = 0;
#else
            I2C_MasterTransferBlocking(i2c_bus->config->I2C, &xfer);
#endif
        }
    }

    return i;
}

static rt_err_t imx6ull_i2c_bus_control(struct rt_i2c_bus_device *bus, rt_uint32_t cmd, rt_uint32_t arg)
{
    return RT_EOK;
}

static rt_err_t imx6ull_i2c_gpio_init(struct imx6ull_i2c_bus *bus)
{
    struct imx6ull_i2c_bus *i2c_bus = RT_NULL;

    i2c_bus = (struct imx6ull_i2c_bus *)bus;

    imx6ull_gpio_init(&i2c_bus->config->scl_gpio);
    imx6ull_gpio_init(&i2c_bus->config->sda_gpio);
    return RT_EOK;

}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_i2c_bus_device_ops imx6ull_i2c_ops =
{
    .master_xfer = imx6ull_i2c_mst_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = imx6ull_i2c_bus_control,
};
#endif

extern void I2C_DriverIRQHandler(int irq, void *base);
int rt_hw_i2c_init(void)
{
    rt_uint16_t obj_num = 0;
    rt_uint32_t src_clock;
    i2c_master_config_t masterConfig = {0};

    obj_num = sizeof(i2c_config) / sizeof(i2c_config[0]);

    src_clock = (CLOCK_GetFreq(kCLOCK_IpgClk) / (CLOCK_GetDiv(kCLOCK_PerclkDiv) + 1U));

    for(int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].config = &i2c_config[i];
        i2c_obj[i].config->hw_base = i2c_obj[i].config->I2C;
        i2c_obj[i].config->I2C = (I2C_Type *)imx6ull_get_periph_vaddr((rt_uint32_t)i2c_obj[i].config->hw_base);
        i2c_obj[i].parent.ops = &imx6ull_i2c_ops;
        imx6ull_i2c_gpio_init(&i2c_obj[i]);

        I2C_MasterGetDefaultConfig(&masterConfig);
        masterConfig.baudRate_Bps = i2c_config[i].baud_rate;

        CLOCK_EnableClock(i2c_obj[i].config->clk_ip_name);

        I2C_MasterInit(i2c_obj[i].config->I2C, &masterConfig, src_clock);

        rt_i2c_bus_device_register(&i2c_obj[i].parent, i2c_obj[i].config->name);

#ifdef IMX_I2C_IRQ_MODE
        I2C_MasterTransferCreateHandle(i2c_obj[i].config->hw_base, &i2c_obj[i].config->master_handle, i2c_master_callback, i2c_obj[i].config);
        rt_hw_interrupt_install(i2c_obj[i].config->irq_num, (rt_isr_handler_t)I2C_DriverIRQHandler, i2c_obj[i].config, i2c_obj[i].config->name);
#endif
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
