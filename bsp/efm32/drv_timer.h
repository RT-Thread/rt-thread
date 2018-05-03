/***************************************************************************//**
 * @file    drv_timer.h
 * @brief   Timer driver of RT-Thread RTOS for EFM32
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-01-18   onelife     Initial creation for EFM32
 ******************************************************************************/
#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

/* Includes ------------------------------------------------------------------*/
#include "hdl_interrupt.h"

/* Exported types ------------------------------------------------------------*/
struct efm32_timer_device_t
{
    TIMER_TypeDef       *timer_device;
    efm32_irq_hook_t    hook;
};

struct efm32_timer_control_t
{
    rt_uint32_t         period;
    efm32_irq_hook_t    hook;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TMR_MODE_ONESHOT            (true)
#define TMR_MODE_CONTINUOUS         (false)

#define TMR_CFG_PRESCALER           timerPrescale1024

/* Exported functions ------------------------------------------------------- */
void rt_hw_timer_init(void);

#endif /*__DRV_TIMER_H__ */
