/**
  ******************************************************************************
  * @file     ../
  * @author      FMD AE
  * @brief       Main program body
  * @version     V1.0.0
  * @date        3-July-2025
  ******************************************************************************
  * @attention
  * COPYRIGHT (C) 2025 Fremont Micro Devices (SZ) Corporation All rights reserved.
  * This software is provided by the copyright holders and contributors,and the
  * software is believed to be accurate and reliable. However, Fremont Micro
  * Devices (SZ) Corporation assumes no responsibility for the consequences of
  * use of such software or for any infringement of patents of other rights
  * of third parties, which may result from its use. No license is granted by
  * implication or otherwise under any patent rights of Fremont Micro Devices (SZ)
  * Corporation.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Main program loop */
    while(1)
    {
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    while (1)
    {}
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Fremont Micro Devices *****END OF FILE****/
