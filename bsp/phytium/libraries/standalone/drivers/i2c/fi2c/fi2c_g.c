/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fi2c_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:36:14
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


/*  - This file contains a configuration table that specifies the configuration
- 驱动全局变量定义，包括静态配置参数 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fi2c.h"
#include "sdkconfig.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
/**
 * @name: FI2C_CONFIG_TBL
 * @msg: I2C驱动的默认配置参数
 */
#if defined(CONFIG_TARGET_E2000)
const FI2cConfig FI2C_CONFIG_TBL[I2C_INSTANCE_NUM] =
{
    [I2C_INSTANCE_0] =
    {
        .instance_id = I2C_INSTANCE_0,
        .base_addr = I2C_0_BASEADDR,
        .irq_num = I2C_0_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },
    [I2C_INSTANCE_1] =
    {
        .instance_id = I2C_INSTANCE_1,
        .base_addr = I2C_1_BASEADDR,
        .irq_num = I2C_1_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },

    [I2C_INSTANCE_2] =
    {
        .instance_id = I2C_INSTANCE_2,
        .base_addr = I2C_2_BASEADDR,
        .irq_num = I2C_2_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    }
};
#endif

#if defined(CONFIG_TARGET_D2000) || defined(CONFIG_TARGET_F2000_4)
const FI2cConfig FI2C_CONFIG_TBL[I2C_INSTANCE_NUM] =
{
    [I2C_INSTANCE_0] =
    {
        .instance_id  = I2C_INSTANCE_0,
        .base_addr = I2C_0_BASEADDR,
        .irq_num  = I2C_0_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },
    [I2C_INSTANCE_1] =
    {
        .instance_id  = I2C_INSTANCE_1,
        .base_addr = I2C_1_BASEADDR,
        .irq_num  = I2C_1_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },

    [I2C_INSTANCE_2] =
    {
        .instance_id  = I2C_INSTANCE_2,
        .base_addr = I2C_2_BASEADDR,
        .irq_num  = I2C_2_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },
    [I2C_INSTANCE_3] =
    {
        .instance_id  = I2C_INSTANCE_3,
        .base_addr = I2C_3_BASEADDR,
        .irq_num  = I2C_3_INTR_IRQ,
        .irq_prority = 0,
        .ref_clk_hz = I2C_REF_CLK_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    }
};
#endif
