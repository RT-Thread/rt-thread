/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2010-12-29   onelife     Initial creation for EFM32
 * 2011-12-09   onelife     Add LEUART module support
 */

#ifndef __HDL_INTERRUPT_H__
#define __HDL_INTERRUPT_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
enum efm32_irq_hook_type_t
{
    efm32_irq_type_dma = 0,
    efm32_irq_type_rtc,
    efm32_irq_type_timer,
    efm32_irq_type_letimer,
    efm32_irq_type_gpio,
    efm32_irq_type_acmp,
    efm32_irq_type_usart,
    efm32_irq_type_leuart,
    efm32_irq_type_iic
};

typedef void (*efm32_irq_callback_t)(rt_device_t device);

typedef struct
{
    enum efm32_irq_hook_type_t type;
    rt_uint8_t unit;
    efm32_irq_callback_t cbFunc;
    void *userPtr;
} efm32_irq_hook_init_t;

typedef struct
{
    efm32_irq_callback_t cbFunc;
    void *userPtr;
} efm32_irq_hook_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
//void NMI_Handler(void);
//void MemManage_Handler(void);
//void BusFault_Handler(void);
//void UsageFault_Handler(void);
//void SVC_Handler(void);
//void DebugMon_Handler(void);
void DMA_IRQHandler_All(rt_uint32_t channel, rt_bool_t primary, void *user);
void efm32_irq_hook_register(efm32_irq_hook_init_t *hook);

#endif /* __HDL_INTERRUPT_H__ */
