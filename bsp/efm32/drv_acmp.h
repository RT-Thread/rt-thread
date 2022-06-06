/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-02-23   onelife     Initial creation for EFM32
 * 2011-06-17   onelife     Modify for efm32lib v2 upgrading
 */

#ifndef __DRV_ACMP_H__
#define __DRV_ACMP_H__

/* Includes ------------------------------------------------------------------*/
#include "hdl_interrupt.h"

/* Exported types ------------------------------------------------------------*/
struct efm32_acmp_device_t
{
    ACMP_TypeDef        *acmp_device;
    efm32_irq_hook_t    hook;
};

struct efm32_acmp_output_t
{
    rt_uint32_t         location;
    rt_bool_t           enable;
    rt_bool_t           invert;
};

struct efm32_acmp_control_t
{
    ACMP_Init_TypeDef           *init;
    ACMP_Channel_TypeDef        posInput;
    ACMP_Channel_TypeDef        negInput;
    struct efm32_acmp_output_t  *output;
    efm32_irq_hook_t            hook;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void rt_hw_acmp_init(void);

#endif /*__DRV_ACMP_H__ */
