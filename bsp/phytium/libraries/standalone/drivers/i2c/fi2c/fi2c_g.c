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
 * Description:  This file is for I2C static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/02/18  add e2000 configs
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
const FI2cConfig FI2C_CONFIG_TBL[FI2C_NUM] =
{
    [FI2C0_ID] =
    {
        .instance_id = FI2C0_ID,
        .base_addr = FI2C0_BASE_ADDR,
        .irq_num = FI2C0_IRQ_NUM,
        .irq_prority = 0,
        .ref_clk_hz = FI2C_CLK_FREQ_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },
#if defined(CONFIG_TARGET_E2000) || defined(CONFIG_TARGET_D2000) || defined(CONFIG_TARGET_F2000_4) 
    [FI2C1_ID] =
    {
        .instance_id  = FI2C1_ID,
        .base_addr = FI2C1_BASE_ADDR,
        .irq_num  = FI2C1_IRQ_NUM,
        .irq_prority = 0,
        .ref_clk_hz = FI2C_CLK_FREQ_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },

    [FI2C2_ID] =
    {
        .instance_id  = FI2C2_ID,
        .base_addr = FI2C2_BASE_ADDR,
        .irq_num  = FI2C2_IRQ_NUM,
        .irq_prority = 0,
        .ref_clk_hz = FI2C_CLK_FREQ_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    },
#endif      
#if defined(CONFIG_TARGET_D2000) || defined(CONFIG_TARGET_F2000_4) 
    [FI2C3_ID] =
    {
        .instance_id  = FI2C3_ID,
        .base_addr = FI2C3_BASE_ADDR,
        .irq_num  = FI2C3_IRQ_NUM,
        .irq_prority = 0,
        .ref_clk_hz = FI2C_CLK_FREQ_HZ,
        .work_mode = FI2C_MASTER,
        .slave_addr = 0,
        .use_7bit_addr = TRUE,
        .speed_rate = FI2C_SPEED_STANDARD_RATE
    }
#endif    
};
