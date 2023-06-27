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

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <board.h>
#include "drv_common.h"

#include "fsl_iomuxc.h"
#include "fsl_clock.h"
#include "fsl_i2c.h"

#define IMX_I2C_IRQ_MODE

struct imx6ull_i2c_config
{
    void *hw_base;  /* hardware physical address base */
    I2C_Type *I2C;
    char *name;
    rt_uint32_t baud_rate;
    rt_uint32_t clk_ip_name;
    rt_uint32_t irq_num;

    struct imx6ull_iomuxc scl_gpio;
    struct imx6ull_iomuxc sda_gpio;

    i2c_master_handle_t master_handle;
};

struct imx6ull_i2c_bus
{
    struct rt_i2c_bus_device parent;
    struct imx6ull_i2c_config *config;
};

#ifdef BSP_USING_I2C1
#define I2C1_BUS_CONFIG                                             \
    {                                                               \
        .I2C         = I2C1,                                        \
        .name        = "i2c1",                                      \
        .clk_ip_name = kCLOCK_I2c1S,                                \
        .baud_rate   = I2C1_BAUD_RATE,                              \
        .irq_num = IMX_INT_I2C1,                                    \
        .scl_gpio    = {IOMUXC_UART4_TX_DATA_I2C1_SCL, 1, 0x70B0},  \
        .sda_gpio    = {IOMUXC_UART4_RX_DATA_I2C1_SDA, 1, 0x70B0},  \
    }
#endif /* BSP_USING_I2C1 */

#ifdef BSP_USING_I2C2
#define I2C2_BUS_CONFIG                                             \
    {                                                               \
        .I2C         = I2C2,                                        \
        .name        = "i2c2",                                      \
        .clk_ip_name = kCLOCK_I2c2S,                                \
        .baud_rate   = I2C2_BAUD_RATE,                              \
        .irq_num = IMX_INT_I2C2,                                    \
        .scl_gpio    = {IOMUXC_UART5_TX_DATA_I2C2_SCL, 1, 0x70B0},  \
        .sda_gpio    = {IOMUXC_UART5_RX_DATA_I2C2_SDA, 1, 0x70B0},  \
    }
#endif /* BSP_USING_I2C2 */

#ifdef BSP_USING_I2C3
#define I2C3_BUS_CONFIG                                             \
    {                                                               \
        .I2C         = I2C3,                                        \
        .name        = "i2c3",                                      \
        .clk_ip_name = kCLOCK_I2c3S,                                \
        .baud_rate   = I2C3_BAUD_RATE,                              \
        .irq_num = IMX_INT_I2C3,                                    \
        .scl_gpio    = {IOMUXC_ENET2_RX_DATA0_I2C3_SCL, 1, 0x70B0}, \
        .sda_gpio    = {IOMUXC_ENET2_RX_DATA1_I2C3_SDA, 1, 0x70B0}, \
    }
#endif /* BSP_USING_I2C3 */

#ifdef BSP_USING_I2C4
#define I2C4_BUS_CONFIG                                             \
    {                                                               \
        .I2C         = I2C4,                                        \
        .name        = "i2c4",                                      \
        .clk_ip_name = kCLOCK_I2c4S,                                \
        .baud_rate   = I2C4_BAUD_RATE,                              \
        .irq_num = IMX_INT_I2C4,                                    \
        .scl_gpio    = {IOMUXC_UART2_TX_DATA_I2C4_SCL, 1, 0x70B0},  \
        .sda_gpio    = {IOMUXC_UART2_RX_DATA_I2C4_SDA, 1, 0x70B0},  \
    }
#endif /* BSP_USING_I2C4 */

#endif
