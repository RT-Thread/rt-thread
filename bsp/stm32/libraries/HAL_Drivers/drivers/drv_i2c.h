/*
 * @Author: Dyyt587 67887002+Dyyt587@users.noreply.github.com
 * @Date: 2024-02-17 19:52:38
 * @LastEditors: Dyyt587 67887002+Dyyt587@users.noreply.github.com
 * @LastEditTime: 2024-02-28 17:21:34
 * @FilePath: \rtthread_hardware_i2c_driver\common\drv_i2c.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * Copyright (c) 2024
 * SPDX-License-Identifier: MIT-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-17     Dyyt587   first version
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include "drv_config.h"
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"
#include <ipc/completion.h>
#ifdef (RT_USING_I2C && BSP_USING_I2C)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

struct stm32_i2c_config
{
    const char              *name;
    I2C_TypeDef          *Instance;
     rt_uint32_t             timing;
    rt_uint32_t             timeout;
    IRQn_Type evirq_type;
    IRQn_Type erirq_type;

    struct dma_config *dma_rx, *dma_tx;
};

struct stm32_i2c
{
    I2C_HandleTypeDef handle;
    struct
    {
        DMA_HandleTypeDef handle_rx;
        DMA_HandleTypeDef handle_tx;
    } dma;
    struct stm32_i2c_config      *config;
    struct rt_i2c_bus_device    i2c_bus;
    rt_uint8_t                  i2c_dma_flag;
    struct rt_completion completion;

};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define I2C_USING_TX_DMA_FLAG       (1U)
#define I2C_USING_RX_DMA_FLAG       (1U << 1)

#ifdef __cplusplus
}
#endif

#endif /* BSP_USING_I2C */

#endif /* __DRV_I2C_H__ */
