/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <drv_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __MM32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__MM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
    rt_uint32_t extiline;
    SYSCFG_EXTILine_Type syscfg_extiline;
};

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

