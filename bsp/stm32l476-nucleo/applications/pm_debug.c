/*
 * File      : userled.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author        Notes
 */

#include <rtthread.h>

#define RTC_ASYNCH_PREDIV    0x7F
#define RTC_SYNCH_PREDIV     0xF9  /* 32Khz/128 - 1 */

#if defined(RT_USING_PM) && defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)

#include <drivers/pm.h>
#include <finsh.h>
#include <stm32l4xx.h>

void release_mode(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }
    
    rt_kprintf("[pwr] release mode: %d\n", mode);
    rt_pm_release(mode);
}
MSH_CMD_EXPORT(release_mode, release pm mode);

void request_mode(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }
    rt_kprintf("[pwr] request mode: %d\n", mode);
    rt_pm_request(mode);
}
MSH_CMD_EXPORT(request_mode, request pm mode);

void sleep_mode(int argc, char **argv)
{
		GPIO_InitTypeDef GPIO_InitStructure;
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }
    
    __HAL_RCC_PWR_CLK_ENABLE();
		
    if (mode == 0)
    {
        rt_kprintf("[pwr] main sleep mode\n");
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    }
    else if (mode == 1)
    {
        rt_kprintf("[pwr] low-power sleep mode\n");
        HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    }
    else
    {
        rt_kprintf("[pwr] mode error: %d\n", mode);
    }		
}
MSH_CMD_EXPORT(sleep_mode, enter sleep mode);

void stop_mode(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }
    
    __HAL_RCC_PWR_CLK_ENABLE();
    if (mode == 0)
    {
        rt_kprintf("[pwr] enter stop mode 0\n");
        HAL_PWREx_EnterSTOP0Mode(PWR_STOPENTRY_WFI);
    }
    else if (mode == 1)
    {
        rt_kprintf("[pwr] enter stop mode 1\n");
        HAL_PWREx_EnterSTOP1Mode(PWR_STOPENTRY_WFI);
    }
    else if (mode == 2)
    {
        rt_kprintf("[pwr] enter stop mode 2\n");
        HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
    }
    else
    {
        rt_kprintf("[pwr] stop mode error: %d\n", mode);
    }
    
}
MSH_CMD_EXPORT(stop_mode, enter stop mode without pm drivers);

void ext_pin_config(void)
{
    GPIO_InitTypeDef gpioinitstruct = {0};
		
		  __HAL_RCC_PWR_CLK_ENABLE();
		
		/* Check if the system was resumed from StandBy mode */
		if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
		{ 
			/* Clear Standby flag */
			__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); 
			
		}
			if (__HAL_PWR_GET_FLAG(PWR_FLAG_WUF2) != RESET)
		{
			__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF2);
		}
     /* Enable GPIOC clock */
      __HAL_RCC_GPIOC_CLK_ENABLE();
		
    gpioinitstruct.Pin    = GPIO_PIN_13;
    gpioinitstruct.Mode   = GPIO_MODE_IT_FALLING; 
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &gpioinitstruct);
		
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* Disable all used wakeup sources: WKUP pin */
    HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);
    /* Clear wake up Flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF2);
    /* Enable wakeup pin WKUP2 */
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2_LOW);	
}

int ext_standby(void)
{
    rt_kprintf("enter standby mode\n\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    
    ext_pin_config();
        
    HAL_PWR_EnterSTANDBYMode();
    
    // never run here
    return 0;
}
MSH_CMD_EXPORT(ext_standby, stm32l4xx enter standby mode and ext pin2 wakeup);

int ext_shutdown(void)
{
    rt_kprintf("enter shutdown mode\n\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    
    ext_pin_config();
    
    /* Enter shutdown mode */
    HAL_PWREx_EnterSHUTDOWNMode();
    
    // never run here
    return 0;
}
MSH_CMD_EXPORT(ext_shutdown, stm32l4xx enter shutdown mode and ext pin2 wakeup);

#endif
