/***************************************************************************//**
 * @file    drv_emu.h
 * @brief   EMU driver of RT-Thread RTOS for EFM32
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
 * 2011-02-21   onelife     Initial creation for EFM32
 * 2011-07-14   onelife     Add multiple channels support for scan mode
 ******************************************************************************/
#ifndef __DRV_EMU_H__
#define __DRV_EMU_H__

/* Includes ------------------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/
#define EMU_TASK_STACK_SIZE         (256)
#define EMU_TASK_EM2_TOKEN_NUMBER   (255)
#define EMU_TASK_EM3_TOKEN_NUMBER   (255)
#define EMU_TASK_EM4_TOKEN_NUMBER   (255)
#define EMU_RX_MESSAGE_SIZE         (4)
#define EMU_RX_MESSAGE_QUEUE_SIZE   (1)

/* Exported types ------------------------------------------------------------*/
struct efm32_emu_task
{
    struct rt_thread        thread;
    struct rt_semaphore     em2;
    struct rt_semaphore     em3;
    struct rt_semaphore     em4;
    rt_uint8_t              stack[EMU_TASK_STACK_SIZE];
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void emu_all_disable(void);
void emu_em2_disable(void);
void emu_em2_enable(void);
void emu_em3_disable(void);
void emu_em3_enable(void);
void emu_em4_disable(void);
void emu_em4_enable(void);
void efm32_emu_init(void);

#endif /*__DRV_EMU_H__ */
