/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_lib.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all peripherals pointers initialization.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#define EXT

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef DEBUG
/*******************************************************************************
* Function Name  : debug
* Description    : This function initialize peripherals pointers.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void debug(void)
{

/************************************* ADC ************************************/
#ifdef _ADC1
  ADC1 = (ADC_TypeDef *)  ADC1_BASE;
#endif /*_ADC1 */

#ifdef _ADC2
  ADC2 = (ADC_TypeDef *)  ADC2_BASE;
#endif /*_ADC2 */

#ifdef _ADC3
  ADC3 = (ADC_TypeDef *)  ADC3_BASE;
#endif /*_ADC3 */

/************************************* BKP ************************************/
#ifdef _BKP
  BKP = (BKP_TypeDef *)  BKP_BASE;
#endif /*_BKP */

/************************************* CAN ************************************/
#ifdef _CAN
  CAN = (CAN_TypeDef *)  CAN_BASE;
#endif /*_CAN */

/************************************* CRC ************************************/
#ifdef _CRC
  CRC = (CRC_TypeDef *)  CRC_BASE;
#endif /*_CRC */

/************************************* DAC ************************************/
#ifdef _DAC
  DAC = (DAC_TypeDef *)  DAC_BASE;
#endif /*_DAC */

/************************************* DBGMCU**********************************/
#ifdef _DBGMCU
  DBGMCU = (DBGMCU_TypeDef *)  DBGMCU_BASE;
#endif /*_DBGMCU */

/************************************* DMA ************************************/
#ifdef _DMA
  DMA1 = (DMA_TypeDef *)  DMA1_BASE;
  DMA2 = (DMA_TypeDef *)  DMA2_BASE;
#endif /*_DMA */

#ifdef _DMA1_Channel1
  DMA1_Channel1 = (DMA_Channel_TypeDef *)  DMA1_Channel1_BASE;
#endif /*_DMA1_Channel1 */

#ifdef _DMA1_Channel2
  DMA1_Channel2 = (DMA_Channel_TypeDef *)  DMA1_Channel2_BASE;
#endif /*_DMA1_Channel2 */

#ifdef _DMA1_Channel3
  DMA1_Channel3 = (DMA_Channel_TypeDef *)  DMA1_Channel3_BASE;
#endif /*_DMA1_Channel3 */

#ifdef _DMA1_Channel4
  DMA1_Channel4 = (DMA_Channel_TypeDef *)  DMA1_Channel4_BASE;
#endif /*_DMA1_Channel4 */

#ifdef _DMA1_Channel5
  DMA1_Channel5 = (DMA_Channel_TypeDef *)  DMA1_Channel5_BASE;
#endif /*_DMA1_Channel5 */

#ifdef _DMA1_Channel6
  DMA1_Channel6 = (DMA_Channel_TypeDef *)  DMA1_Channel6_BASE;
#endif /*_DMA1_Channel6 */

#ifdef _DMA1_Channel7
  DMA1_Channel7 = (DMA_Channel_TypeDef *)  DMA1_Channel7_BASE;
#endif /*_DMA1_Channel7 */

#ifdef _DMA2_Channel1
  DMA2_Channel1 = (DMA_Channel_TypeDef *)  DMA2_Channel1_BASE;
#endif /*_DMA2_Channel1 */

#ifdef _DMA2_Channel2
  DMA2_Channel2 = (DMA_Channel_TypeDef *)  DMA2_Channel2_BASE;
#endif /*_DMA2_Channel2 */

#ifdef _DMA2_Channel3
  DMA2_Channel3 = (DMA_Channel_TypeDef *)  DMA2_Channel3_BASE;
#endif /*_DMA2_Channel3 */

#ifdef _DMA2_Channel4
  DMA2_Channel4 = (DMA_Channel_TypeDef *)  DMA2_Channel4_BASE;
#endif /*_DMA2_Channel4 */

#ifdef _DMA2_Channel5
  DMA2_Channel5 = (DMA_Channel_TypeDef *)  DMA2_Channel5_BASE;
#endif /*_DMA2_Channel5 */

/************************************* EXTI ***********************************/
#ifdef _EXTI
  EXTI = (EXTI_TypeDef *)  EXTI_BASE;
#endif /*_EXTI */

/************************************* FLASH and Option Bytes *****************/
#ifdef _FLASH
  FLASH = (FLASH_TypeDef *)  FLASH_R_BASE;
  OB = (OB_TypeDef *)        OB_BASE;
#endif /*_FLASH */

/************************************* FSMC ***********************************/
#ifdef _FSMC
  FSMC_Bank1 = (FSMC_Bank1_TypeDef *)    FSMC_Bank1_R_BASE;
  FSMC_Bank1E = (FSMC_Bank1E_TypeDef *)  FSMC_Bank1E_R_BASE;  
  FSMC_Bank2 = (FSMC_Bank2_TypeDef *)    FSMC_Bank2_R_BASE; 
  FSMC_Bank3 = (FSMC_Bank3_TypeDef *)    FSMC_Bank3_R_BASE;
  FSMC_Bank4 = (FSMC_Bank4_TypeDef *)    FSMC_Bank4_R_BASE;
#endif /*_FSMC */

/************************************* GPIO ***********************************/
#ifdef _GPIOA
  GPIOA = (GPIO_TypeDef *)  GPIOA_BASE;
#endif /*_GPIOA */

#ifdef _GPIOB
  GPIOB = (GPIO_TypeDef *)  GPIOB_BASE;
#endif /*_GPIOB */

#ifdef _GPIOC
  GPIOC = (GPIO_TypeDef *)  GPIOC_BASE;
#endif /*_GPIOC */

#ifdef _GPIOD
  GPIOD = (GPIO_TypeDef *)  GPIOD_BASE;
#endif /*_GPIOD */

#ifdef _GPIOE
  GPIOE = (GPIO_TypeDef *)  GPIOE_BASE;
#endif /*_GPIOE */

#ifdef _GPIOF
  GPIOF = (GPIO_TypeDef *)  GPIOF_BASE;
#endif /*_GPIOF */

#ifdef _GPIOG
  GPIOG = (GPIO_TypeDef *)  GPIOG_BASE;
#endif /*_GPIOG */

#ifdef _AFIO
  AFIO = (AFIO_TypeDef *)  AFIO_BASE;
#endif /*_AFIO */

/************************************* I2C ************************************/
#ifdef _I2C1
  I2C1 = (I2C_TypeDef *)  I2C1_BASE;
#endif /*_I2C1 */

#ifdef _I2C2
  I2C2 = (I2C_TypeDef *)  I2C2_BASE;
#endif /*_I2C2 */

/************************************* IWDG ***********************************/
#ifdef _IWDG
  IWDG = (IWDG_TypeDef *) IWDG_BASE;
#endif /*_IWDG */

/************************************* NVIC ***********************************/
#ifdef _NVIC
  NVIC = (NVIC_TypeDef *)  NVIC_BASE;
  SCB = (SCB_TypeDef *)  SCB_BASE;
#endif /*_NVIC */

/************************************* PWR ************************************/
#ifdef _PWR
  PWR = (PWR_TypeDef *)  PWR_BASE;
#endif /*_PWR */

/************************************* RCC ************************************/
#ifdef _RCC
  RCC = (RCC_TypeDef *)  RCC_BASE;
#endif /*_RCC */

/************************************* RTC ************************************/
#ifdef _RTC
  RTC = (RTC_TypeDef *)  RTC_BASE;
#endif /*_RTC */

/************************************* SDIO ***********************************/
#ifdef _SDIO
  SDIO = (SDIO_TypeDef *)  SDIO_BASE;
#endif /*_SDIO */

/************************************* SPI ************************************/
#ifdef _SPI1
  SPI1 = (SPI_TypeDef *)  SPI1_BASE;
#endif /*_SPI1 */

#ifdef _SPI2
  SPI2 = (SPI_TypeDef *)  SPI2_BASE;
#endif /*_SPI2 */

#ifdef _SPI3
  SPI3 = (SPI_TypeDef *)  SPI3_BASE;
#endif /*_SPI3 */

/************************************* SysTick ********************************/
#ifdef _SysTick
  SysTick = (SysTick_TypeDef *)  SysTick_BASE;
#endif /*_SysTick */

/************************************* TIM ************************************/
#ifdef _TIM1
  TIM1 = (TIM_TypeDef *)  TIM1_BASE;
#endif /*_TIM1 */

#ifdef _TIM2
  TIM2 = (TIM_TypeDef *)  TIM2_BASE;
#endif /*_TIM2 */

#ifdef _TIM3
  TIM3 = (TIM_TypeDef *)  TIM3_BASE;
#endif /*_TIM3 */

#ifdef _TIM4
  TIM4 = (TIM_TypeDef *)  TIM4_BASE;
#endif /*_TIM4 */

#ifdef _TIM5
  TIM5 = (TIM_TypeDef *)  TIM5_BASE;
#endif /*_TIM5 */

#ifdef _TIM6
  TIM6 = (TIM_TypeDef *)  TIM6_BASE;
#endif /*_TIM6 */

#ifdef _TIM7
  TIM7 = (TIM_TypeDef *)  TIM7_BASE;
#endif /*_TIM7 */

#ifdef _TIM8
  TIM8 = (TIM_TypeDef *)  TIM8_BASE;
#endif /*_TIM8 */

/************************************* USART **********************************/
#ifdef _USART1
  USART1 = (USART_TypeDef *) USART1_BASE;
#endif /*_USART1 */

#ifdef _USART2
  USART2 = (USART_TypeDef *) USART2_BASE;
#endif /*_USART2 */

#ifdef _USART3
  USART3 = (USART_TypeDef *) USART3_BASE;
#endif /*_USART3 */

#ifdef _UART4
  UART4 = (USART_TypeDef *) UART4_BASE;
#endif /*_UART4 */

#ifdef _UART5
  UART5 = (USART_TypeDef *) UART5_BASE;
#endif /*_UART5 */

/************************************* WWDG ***********************************/
#ifdef _WWDG
  WWDG = (WWDG_TypeDef *)  WWDG_BASE;
#endif /*_WWDG */
}
#endif  /* DEBUG*/

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
