/*
* Copyright (c) 2006-2021, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author       Notes
* 2018-11-06     SummerGift   first version
* 2019-04-09     WillianChan  add stm32f469-st-disco bsp
* 2020-06-20     thread-liu   add stm32mp157-dk1 bsp
*/

#include "board.h"

void PeriphCommonClock_Config(void);
/**
* @brief System Clock Configuration
* @retval None
*/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /**Configure LSE Drive Capability
    */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

    /**Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
        |RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIG;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.HSIDivValue = RCC_HSI_DIV1;

    /**PLL1 Config
    */
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 3;
    RCC_OscInitStruct.PLL.PLLN = 81;
    RCC_OscInitStruct.PLL.PLLP = 1;
    RCC_OscInitStruct.PLL.PLLQ = 1;
    RCC_OscInitStruct.PLL.PLLR = 1;
    RCC_OscInitStruct.PLL.PLLFRACV = 0x800;
    RCC_OscInitStruct.PLL.PLLMODE = RCC_PLL_FRACTIONAL;
    RCC_OscInitStruct.PLL.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
    RCC_OscInitStruct.PLL.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    /**PLL2 Config
    */
    RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL2.PLLSource = RCC_PLL12SOURCE_HSE;
    RCC_OscInitStruct.PLL2.PLLM = 3;
    RCC_OscInitStruct.PLL2.PLLN = 66;
    RCC_OscInitStruct.PLL2.PLLP = 2;
    RCC_OscInitStruct.PLL2.PLLQ = 1;
    RCC_OscInitStruct.PLL2.PLLR = 1;
    RCC_OscInitStruct.PLL2.PLLFRACV = 0x1400;
    RCC_OscInitStruct.PLL2.PLLMODE = RCC_PLL_FRACTIONAL;
    RCC_OscInitStruct.PLL2.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
    RCC_OscInitStruct.PLL2.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    /**PLL3 Config
    */
    RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
    RCC_OscInitStruct.PLL3.PLLM = 2;
    RCC_OscInitStruct.PLL3.PLLN = 34;
    RCC_OscInitStruct.PLL3.PLLP = 2;
    RCC_OscInitStruct.PLL3.PLLQ = 17;
    RCC_OscInitStruct.PLL3.PLLR = 37;
    RCC_OscInitStruct.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
    RCC_OscInitStruct.PLL3.PLLFRACV = 0x1A04;
    RCC_OscInitStruct.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;
    RCC_OscInitStruct.PLL3.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
    RCC_OscInitStruct.PLL3.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    /**PLL4 Config
    */
    RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL4.PLLSource = RCC_PLL4SOURCE_HSE;
    RCC_OscInitStruct.PLL4.PLLM = 4;
    RCC_OscInitStruct.PLL4.PLLN = 99;
    RCC_OscInitStruct.PLL4.PLLP = 6;
    RCC_OscInitStruct.PLL4.PLLQ = 8;
    RCC_OscInitStruct.PLL4.PLLR = 8;
    RCC_OscInitStruct.PLL4.PLLRGE = RCC_PLL4IFRANGE_0;
    RCC_OscInitStruct.PLL4.PLLFRACV = 0;
    RCC_OscInitStruct.PLL4.PLLMODE = RCC_PLL_INTEGER;
    RCC_OscInitStruct.PLL4.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
    RCC_OscInitStruct.PLL4.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /**RCC Clock Config
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_ACLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
            |RCC_CLOCKTYPE_PCLK3|RCC_CLOCKTYPE_PCLK4
                |RCC_CLOCKTYPE_PCLK5|RCC_CLOCKTYPE_MPU;
    RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
    RCC_ClkInitStruct.MPUInit.MPU_Div = RCC_MPU_DIV2;
    RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_PLL2;
    RCC_ClkInitStruct.AXISSInit.AXI_Div = RCC_AXI_DIV1;
    RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
    RCC_ClkInitStruct.MCUInit.MCU_Div = RCC_MCU_DIV1;
    RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV2;
    RCC_ClkInitStruct.APB5_Div = RCC_APB5_DIV4;
    RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /**Set the HSE division factor for RTC clock
    */
    __HAL_RCC_RTC_HSEDIV(24);

    /* Configure the peripherals common clocks */
    if(IS_ENGINEERING_BOOT_MODE())
    {
        PeriphCommonClock_Config();
    }
}


/**
* @brief Peripherals Common Clock Configuration
* @retval None
*/
void PeriphCommonClock_Config(void) {
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the common periph clock
    */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
    PeriphClkInit.CkperClockSelection = RCC_CKPERCLKSOURCE_HSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }
}

extern void rt_hw_systick_init(void);
extern int rt_hw_usart_init(void);
void rt_hw_board_init()
{
    /* HAL_Init() function is called at the beginning of the program */
    HAL_Init();

    /* enable interrupt */
    __set_PRIMASK(0);
    /* Configure the system clock */
    if (IS_ENGINEERING_BOOT_MODE()) {
        /* Configure the system clock */
        SystemClock_Config();
    }
    /* disable interrupt */
    __set_PRIMASK(1);

    rt_hw_systick_init();

    /* Heap initialization */
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* Pin driver initialization is open by default */
#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
