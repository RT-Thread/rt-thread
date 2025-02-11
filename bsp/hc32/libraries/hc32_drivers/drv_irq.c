/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2024-06-07     CDT          Modify the IRQ install implementation for F448/F472
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "drv_irq.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#if defined (HC32F448) || defined (HC32F472)
    /* Interrupt registration max number */
    #define HC32_INT_REG_MAX_NUM        (16U)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
rt_err_t hc32_install_irq_handler(struct hc32_irq_config *irq_config,
                                  void (*irq_hdr)(void),
                                  rt_bool_t irq_enable)
{
    rt_err_t result = -RT_ERROR;
    stc_irq_signin_config_t stcIrqSignConfig;

    RT_ASSERT(RT_NULL != irq_config);

#if defined (HC32F448) || defined (HC32F472)
    if (irq_config->irq_num < HC32_INT_REG_MAX_NUM)
    {
        RT_ASSERT(RT_NULL != irq_hdr);
        INTC_IntSrcCmd(irq_config->int_src, DISABLE);
    }
    else
    {
        INTC_IntSrcCmd(irq_config->int_src, ENABLE);
        goto nvic_config;
    }
    stcIrqSignConfig.enIRQn      = irq_config->irq_num;
    stcIrqSignConfig.enIntSrc    = irq_config->int_src;
    stcIrqSignConfig.pfnCallback = irq_hdr;
    if (LL_OK == INTC_IrqSignIn(&stcIrqSignConfig))
nvic_config:
#elif defined (HC32F460) || defined (HC32F4A0)
    stcIrqSignConfig.enIRQn      = irq_config->irq_num;
    stcIrqSignConfig.enIntSrc    = irq_config->int_src;
    stcIrqSignConfig.pfnCallback = irq_hdr;
    if (LL_OK == INTC_IrqSignIn(&stcIrqSignConfig))
#endif
    {
        NVIC_ClearPendingIRQ(irq_config->irq_num);
        NVIC_SetPriority(irq_config->irq_num, irq_config->irq_prio);
        if (RT_TRUE == irq_enable)
        {
            NVIC_EnableIRQ(irq_config->irq_num);
        }
        else
        {
            NVIC_DisableIRQ(irq_config->irq_num);
        }
        result = RT_EOK;
    }

    return result;
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
