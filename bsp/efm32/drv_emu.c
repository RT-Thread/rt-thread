/***************************************************************************//**
 * @file    drv_emu.c
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
 * 2012-02-21   onelife     Initial creation for EFM32
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_emu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef EFM32_EMU_DEBUG
#define emu_debug(format,args...)           rt_kprintf(format, ##args)
#else
#define emu_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
struct efm32_emu_task   emu_task;

/***************************************************************************//**
* @brief
*   Register SPI device
*
* @details
*
* @note
*
* @param[in] device
*   Pointer to device descriptor
*
* @param[in] name
*   Device name
*
* @param[in] flag
*   Configuration flags
*
* @param[in] spi
*   Pointer to SPI device descriptor
*
* @return
*   Error code
******************************************************************************/
void emu_task_main_loop(void *parameter)
{
    struct efm32_emu_task *emu_task = (struct efm32_emu_task *)parameter;

    while(1)
    {
        if (emu_task->em2.value == EMU_TASK_EM2_TOKEN_NUMBER)
        {
            if (emu_task->em3.value == EMU_TASK_EM3_TOKEN_NUMBER)
            {
                if (emu_task->em4.value == EMU_TASK_EM4_TOKEN_NUMBER)
                {
                    EMU_EnterEM4();
                }
                else
                {
                    EMU_EnterEM3(RT_TRUE);
                }
            }
            else
            {
                EMU_EnterEM2(RT_TRUE);
            }
        }
        else
        {
            EMU_EnterEM1();
        }
    }
}

#define OS_TIMER_LIST_EMPTY     (0x00000001)
#define OS_TIMER_LIST_NOT_EMPTY (0x00000002)

void emu_event_send(rt_uint32_t event)
{
    switch (event)
    {
    case OS_TIMER_LIST_EMPTY:
//        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
        break;
    case OS_TIMER_LIST_NOT_EMPTY:
//        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
        break;
    }
}

rt_bool_t emu_is_emu(struct rt_thread *thread)
{
    return (thread == &emu_task.thread);
}

void emu_all_disable(void)
{
    if (rt_sem_take(&emu_task.em4, RT_WAITING_NO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
    if (rt_sem_take(&emu_task.em3, RT_WAITING_NO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
    if (rt_sem_take(&emu_task.em2, RT_WAITING_NO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void emu_em2_disable(void)
{
    if (rt_sem_take(&emu_task.em2, RT_WAITING_NO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void emu_em2_enable(void)
{
    if (rt_sem_release(&emu_task.em2) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void emu_em3_disable(void)
{
    if (rt_sem_take(&emu_task.em3, RT_WAITING_NO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void emu_em3_enable(void)
{
    if (rt_sem_release(&emu_task.em3) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void emu_em4_disable(void)
{
    if (rt_sem_take(&emu_task.em4, RT_WAITING_NO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void emu_em4_enable(void)
{
    if (rt_sem_release(&emu_task.em4) != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

/***************************************************************************//**
 * @brief
 *  Initialize EMU module related hardware
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void efm32_emu_init(void)
{
    do
    {
        /* init token */
        if (rt_sem_init(
            &emu_task.em2,
            "EM2",
            EMU_TASK_EM2_TOKEN_NUMBER,
            RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
        if (rt_sem_init(
            &emu_task.em3,
            "EM3",
            EMU_TASK_EM3_TOKEN_NUMBER,
            RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }
        if (rt_sem_init(
            &emu_task.em4,
            "EM4",
            EMU_TASK_EM4_TOKEN_NUMBER,
            RT_IPC_FLAG_FIFO) != RT_EOK)
        {
            break;
        }

        /* init thread */
        if (rt_thread_init(
            &emu_task.thread,
            "EMU",
            emu_task_main_loop, (void *)&emu_task,
            (void *)&emu_task.stack, sizeof(emu_task.stack),
            RT_THREAD_PRIORITY_MAX - 2, RT_TICK_PER_SECOND) != RT_EOK)
        {
            break;
        }

        /* startup */
        if (rt_thread_startup(&emu_task.thread) != RT_EOK)
        {
            break;
        }
    } while (0);

    rt_kprintf("EMU err: init failed!\n");
}

/*******************************************************************************
 *  Export to FINSH
 ******************************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_emu(void)
{
    rt_kprintf(" --------- EMU Status ---------\n");
    rt_kprintf(" em2 token used %d\n",
        EMU_TASK_EM2_TOKEN_NUMBER - emu_task.em2.value);
    rt_kprintf(" em3 token used %d\n",
        EMU_TASK_EM3_TOKEN_NUMBER - emu_task.em3.value);
    rt_kprintf(" em4 token used %d\n",
        EMU_TASK_EM4_TOKEN_NUMBER - emu_task.em4.value);
}
FINSH_FUNCTION_EXPORT(list_emu, list the EMU status)
#endif

/***************************************************************************//**
 * @}
 ******************************************************************************/
