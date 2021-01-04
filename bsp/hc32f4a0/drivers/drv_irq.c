/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
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
    stc_irq_signin_config_t irq_signin;

    RT_ASSERT(RT_NULL != irq_config);
    RT_ASSERT(RT_NULL != irq_hdr);

    irq_signin.enIRQn     = irq_config->irq;
    irq_signin.enIntSrc   = irq_config->int_src;
    irq_signin.pfnCallback= irq_hdr;
    if (Ok == INTC_IrqSignIn(&irq_signin))
    {
        NVIC_ClearPendingIRQ(irq_signin.enIRQn);
        NVIC_SetPriority(irq_signin.enIRQn, irq_config->irq_prio);

        if (RT_TRUE == irq_enable)
        {
            NVIC_EnableIRQ(irq_signin.enIRQn);
        }
        else
        {
            NVIC_DisableIRQ(irq_signin.enIRQn);
        }

        result = RT_EOK;
    }

    RT_ASSERT(RT_EOK == result);

    return result;
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
