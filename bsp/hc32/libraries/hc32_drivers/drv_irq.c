/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
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
    RT_ASSERT(RT_NULL != irq_hdr);

    stcIrqSignConfig.enIRQn      = irq_config->irq_num;
    stcIrqSignConfig.enIntSrc    = irq_config->int_src;
    stcIrqSignConfig.pfnCallback = irq_hdr;
    if (LL_OK == INTC_IrqSignIn(&stcIrqSignConfig))
    {
        NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
        NVIC_SetPriority(stcIrqSignConfig.enIRQn, irq_config->irq_prio);
        if (RT_TRUE == irq_enable)
        {
            NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
        }
        else
        {
            NVIC_DisableIRQ(stcIrqSignConfig.enIRQn);
        }
        result = RT_EOK;
    }
    return result;
}

#if defined (HC32F448) || defined (HC32F472)
rt_err_t hc32_install_independ_irq_handler(struct hc32_irq_config *irq_config,
        rt_bool_t irq_enable)
{
    RT_ASSERT(RT_NULL != irq_config);

    NVIC_ClearPendingIRQ(irq_config->irq_num);
    NVIC_SetPriority(irq_config->irq_num, irq_config->irq_prio);
    if (RT_TRUE == irq_enable)
    {
        INTC_IntSrcCmd(irq_config->int_src, ENABLE);
        NVIC_EnableIRQ(irq_config->irq_num);
    }
    else
    {
        INTC_IntSrcCmd(irq_config->int_src, DISABLE);
        NVIC_DisableIRQ(irq_config->irq_num);
    }
    return RT_EOK;
}
#endif

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
