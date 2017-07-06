/**
  ******************************************************************************
  * @file    stm32l4xx_nucleo.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    16-June-2017
  * @brief   This file provides set of firmware functions to manage:
  *          - LEDs and push-button available on STM32L4XX-Nucleo Kit 
  *            from STMicroelectronics
  *          - LCD, joystick and microSD available on Adafruit 1.8" TFT LCD 
  *            shield (reference ID 802)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_nucleo.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup STM32L4XX_NUCLEO STM32L476RG-Nucleo
  * @brief This file provides set of firmware functions to manage Leds and push-button
  *        available on STM32L4XX-Nucleo Kit from STMicroelectronics.
  *        It provides also LCD, joystick and uSD functions to communicate with 
  *        Adafruit 1.8" TFT LCD shield (reference ID 802)
  * @{
  */ 


/** @defgroup STM32L4XX_NUCLEO_Private_Defines Private Defines
  * @{
  */ 
  
/**
  * @brief STM32L4xx NUCLEO BSP Driver version V2.1.0
  */
#define __STM32L4XX_NUCLEO_BSP_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM32L4XX_NUCLEO_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM32L4XX_NUCLEO_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L4XX_NUCLEO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32L4XX_NUCLEO_BSP_VERSION       ((__STM32L4XX_NUCLEO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32L4XX_NUCLEO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32L4XX_NUCLEO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32L4XX_NUCLEO_BSP_VERSION_RC))

/**
  * @brief LINK SD Card
  */
#define SD_DUMMY_BYTE            0xFF
#define SD_NO_RESPONSE_EXPECTED  0x80

/**
  * @}
  */ 


#ifdef USE_STM32L4XX_NUCLEO_64_SMPS

/**
  * @brief SMPS 
  */


#ifdef USE_ADP5301ACBZ          /* ADP5301ACBZ */

/* ######################################################################## */
/* #define PORT_SMPS               GPIOA                                    */
/* #define PIN_SMPS_ENABLE         GPIO_PIN_4                               */
/* #define PIN_SMPS_POWERGOOD      GPIO_PIN_6                               */
/* #define PIN_SMPS_SWITCH_ENABLE  GPIO_PIN_7                               */

/* IN CASE OF SMPS VOLTAGE RANGE SELECTION                                  */
/* #define PIN_SMPS_V1             GPIO_PIN_5                               */
/* ######################################################################## */

#endif                          /* ADP5301ACBZ */

/**
  * @}
  */ 

#endif /* USE_STM32L4XX_NUCLEO_64_SMPS */

/** @defgroup STM32L4XX_NUCLEO_Private_Variables Exported Variables
  * @{
  */ 
#ifdef USE_STM32L4XX_NUCLEO_64_SMPS
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED4_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED4_PIN};
#else
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED2_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED2_PIN};
#endif

GPIO_TypeDef*  BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT};
const uint16_t BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN};
const uint16_t BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

/**
 * @brief BUS variables
 */

#ifdef HAL_SPI_MODULE_ENABLED
uint32_t hnucleo_SpixTimeout = NUCLEO_SPIx_TIMEOUT_MAX;        /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef hnucleo_Spi;
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
static ADC_HandleTypeDef hnucleo_Adc;
/* ADC channel configuration structure declaration */
static ADC_ChannelConfTypeDef hnucleo_AdcChannelConfig;
#endif /* HAL_ADC_MODULE_ENABLED */

/**
  * @}
  */ 

/** @defgroup STM32L4XX_NUCLEO_Private_Functions Private Functions
  * @{
  */ 
#ifdef HAL_SPI_MODULE_ENABLED
static void               SPIx_Init(void);
static void               SPIx_Write(uint8_t Value);
static void               SPIx_Error (void);
static void               SPIx_MspInit(void);
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
static HAL_StatusTypeDef  ADCx_Init(void);
static void               ADCx_MspInit(ADC_HandleTypeDef *hadc);
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
/* SD IO functions */
void                      SD_IO_Init(void);
void                      SD_IO_CSState(uint8_t state);
void                      SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
uint8_t                   SD_IO_WriteByte(uint8_t Data);

/* LCD IO functions */
void                      LCD_IO_Init(void);
void                      LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size);
void                      LCD_IO_WriteReg(uint8_t LCDReg);
void                      LCD_Delay(uint32_t delay);
#endif /* HAL_SPI_MODULE_ENABLED */
/**
  * @}
  */ 

/** @defgroup STM32L4XX_NUCLEO_Exported_Functions Exported Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32L4XX NUCLEO BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32L4XX_NUCLEO_BSP_VERSION;
}

/** @defgroup STM32L4XX_NUCLEO_LED_Functions LED Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: LED to be configured. 
  *          This parameter can be one of the following values:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin   = GPIO_PIN[Led];
  gpioinitstruct.Mode  = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull  = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIO_PORT[Led], &gpioinitstruct);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET); 
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *            @arg  LED2 or LED4 on Nucleo-64 with external SMPS
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}

/**
  * @}
  */ 

/** @defgroup STM32L4XX_NUCLEO_BUTTON_Functions BUTTON Functions
  * @{
  */ 

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_USER
  * @param  ButtonMode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef gpioinitstruct = {0};

  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  if (ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpioinitstruct.Pin    = BUTTON_PIN[Button];
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);
  }
  else if(ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpioinitstruct.Pin    = BUTTON_PIN[Button];
    gpioinitstruct.Mode   = GPIO_MODE_IT_FALLING; 
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_USER  
  * @retval Button state.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

#ifdef USE_STM32L4XX_NUCLEO_64_SMPS
#ifdef USE_ADP5301ACBZ          /* ADP5301ACBZ */

/******************************************************************************
                            SMPS OPERATIONS
*******************************************************************************/

/**
  * @brief  DeInitialize the external SMPS component
  * @param  None
  * @note   Low power consumption GPIO settings
  * @retval SMPS status
  */
uint32_t BSP_SMPS_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  PWR_AND_CLK_SMPS(); 

  /* --------------------------------------------------------------------------------------  */
  /* Added for Deinit if No PIN_SMPS_ENABLE & PIN_SMPS_SWITCH_ENABLE are not disabled before */

  /* Disable SMPS SWITCH */
  HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_SWITCH_ENABLE, GPIO_PIN_RESET);
 
  HAL_Delay(1);
  
  /* Disable SMPS */
  HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_ENABLE, GPIO_PIN_RESET);
 
  /* --------------------------------------------------------------------------------------  */
  /* Set all GPIO in output push/pull pulldown state to reduce power consumption  */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pull =  GPIO_PULLDOWN;
  
  /* Consider all SMPS pins but V1, not used on ADP5301ACBZ */
  GPIO_InitStruct.Pin = PIN_SMPS_ENABLE | PIN_SMPS_SWITCH_ENABLE | PIN_SMPS_POWERGOOD; 
  HAL_GPIO_Init(PORT_SMPS, &GPIO_InitStruct);
  
  return SMPS_OK;
}

/**
  * @brief  Initialize the external SMPS component
  * @param  VoltageRange: Select operating SMPS supply 
  *           @arg DCDC_AND_BOARD_DEPENDENT
  * @note   VoltageRange is not used with all boards. When not
  *         used, resort to PWR_REGULATOR_VOLTAGE_SCALE2 by default.
  * @retval SMPS status
  */
uint32_t BSP_SMPS_Init(uint32_t VoltageRange)
{
  PWR_AND_CLK_SMPS();
  
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Reconfigure PWR_PUCRx/PDCRx registers only when not coming */
  /* back from Standby or Shutdown states.                      */
  /* Consider as well non-SMPS related pins.                     */
  if(!(READ_BIT(PWR->PWR_PU_REG, PWR_GPIO_ENABLE)))
  {
    HAL_PWREx_EnableGPIOPullDown (PWR_GPIO_SMPS, PWR_GPIO_SWITCH_ENABLE);
    HAL_PWREx_EnableGPIOPullDown (PWR_GPIO_SMPS, PWR_GPIO_ENABLE); 
     
    /* HW limitation: Level shifter consumes because of dangling, so pull PA2 up 
      (LPUART1_TX), PA13 (SWD/TMS) and PB3 (SWO) */
    HAL_PWREx_EnableGPIOPullUp(PWR_GPIO_A,GPIO_PIN_2);  /* LPUART1_TX */   
    HAL_PWREx_EnableGPIOPullUp(PWR_GPIO_A,GPIO_PIN_13); /* SWD/TMS    */
    HAL_PWREx_EnableGPIOPullUp(PWR_GPIO_B,GPIO_PIN_3);  /* SWO        */
    
    /* Don't set PWR_CR3 APC bit at this time as it increases power
      consumption in non-Standby/Shutdown modes. It will have to be
      set with HAL_PWREx_EnablePullUpPullDownConfig() API upon
      Standby or Shutdown modes entering */
  }
  /* ------------------------------------------------------------------------ */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  GPIO_InitStruct.Pin = PIN_SMPS_POWERGOOD;
  HAL_GPIO_Init(PORT_SMPS, &GPIO_InitStruct);  

  /* ------------------------------------------------------------------------ */
  
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
 
  GPIO_InitStruct.Pin = PIN_SMPS_ENABLE | PIN_SMPS_SWITCH_ENABLE;   
  HAL_GPIO_Init(PORT_SMPS, &GPIO_InitStruct);
    
 /* --------- SMPS VOLTAGE RANGE SELECTION ----------------------------------*/   
 /* ######################################################################## */   
 /* - > Not applicable to ADP5301ACBZ on MB1319 */
 /* ######################################################################## */   
 /* - > Applicable to ST1PS02D1QTR */
 /* Control to be added */

 /* ST1PS02D1QTR on MB1312 */  
 /* if (VoltageRange == ST1PS02D1QTR_VOUT_1_25) */
 /* HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_V1, GPIO_PIN_SET); */
 /* 1.25V                  */
 /* D0/D1/D2 = H/L/L       */
 /* else */
 
 /* */
 /* ST1PS02D1QTR on MB1312 */
 /* ST1PS02D1QTR_VOUT_1_05 */
 /* 1.05V                  */
 /* D0/D1/D2 = L/L/L       */
 /* HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_V1, GPIO_PIN_RESET); */
 /* ######################################################################## */    
  return SMPS_OK;
}

/**
  * @brief  Enable the external SMPS component
  * @param  Delay: delay in ms after enable 
  * @param  Power_Good_Check: Enable Power good check 
  * @note   Power_Good_Check is not used with all external
  *         SMPS components  
  * @retval SMPS status
  *           @arg SMPS_OK: SMPS ENABLE OK
  *           @arg SMPS_KO: POWER GOOD CHECK FAILS
  */
uint32_t BSP_SMPS_Enable (uint32_t Delay, uint32_t Power_Good_Check)
{
  PWR_AND_CLK_SMPS();
  
  HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_ENABLE, GPIO_PIN_SET);
    
  /* Delay upon request */
  if (Delay != 0)
  {
    HAL_Delay(Delay);
  }
  
  /* CHECK POWER GOOD or NOT */
  if (Power_Good_Check != 0)
  {
    if (GPIO_PIN_RESET == (HAL_GPIO_ReadPin(PORT_SMPS, PIN_SMPS_POWERGOOD)))
    {
      /* POWER GOOD KO */
      return SMPS_KO;
    }
  } 
  
  /* SMPS ENABLE */ 
  return SMPS_OK; 
}

/**
  * @brief  Disable the external SMPS component
  * @param  NONE 
  * @note   SMPS SWITCH should be disabled first !
  * @retval SMPS status
  *           @arg SMPS_OK: SMPS DISABLE OK - DONE
  *           @arg SMPS_KO: POWER GOOD CHECK FAILS
  *
  */
uint32_t BSP_SMPS_Disable (void)
{

  PWR_AND_CLK_SMPS(); 
 
  /* Check if SMPS SWITCH is disabled */
  if (HAL_GPIO_ReadPin(PORT_SMPS, PIN_SMPS_SWITCH_ENABLE) != GPIO_PIN_RESET)
  {
    /* ERROR AS SWITCH SHOULD BE DISABLE */
    return SMPS_KO; 
  }
 
  /* Disable SMPS */
  HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_ENABLE, GPIO_PIN_RESET);
  
 /* SMPS DISABLE */ 
  return SMPS_OK; 
}

/**
  * @brief  Enable the external SMPS SWITCH component
  * @param  Delay: delay in ms before SMPS SWITCH ENABLE 
  * @param  Power_Good_Check: Enable Power good check 
  * @note   Power_Good_Check is not used with all boards
  * @retval SMPS status
  *           @arg SMPS_OK: SMPS ENABLE OK
  *           @arg SMPS_KO: POWER GOOD CHECK FAILS
  */
uint32_t BSP_SMPS_Supply_Enable (uint32_t Delay, uint32_t Power_Good_Check)
{
  PWR_AND_CLK_SMPS();

  if (Delay != 0)
  {
    HAL_Delay(Delay);
  }
  /* CHECK POWER GOOD or NOT */
  if (Power_Good_Check != 0)
  {
    if (GPIO_PIN_RESET == (HAL_GPIO_ReadPin(PORT_SMPS, PIN_SMPS_POWERGOOD)))
    {
      /* POWER GOOD KO */
      return SMPS_KO;
    }
  }
  
  /* SMPS SWITCH ENABLE */ 
  HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_SWITCH_ENABLE, GPIO_PIN_SET);
  
  
  return SMPS_OK;
}

/**
  * @brief  Disable the external SMPS SWITCH component
  * @param  None
  * @retval SMPS status
  *           @arg SMPS_OK: SMPS SWITCH DISABLE OK
  */
uint32_t BSP_SMPS_Supply_Disable (void)
{
  PWR_AND_CLK_SMPS();
  /* SMPS SWITCH DISABLE */
  HAL_GPIO_WritePin(PORT_SMPS, PIN_SMPS_SWITCH_ENABLE, GPIO_PIN_RESET);

  return SMPS_OK;
}

#endif /* ADP5301ACBZ */
#endif /* USE_STM32L4XX_NUCLEO_64_SMPS */


#ifdef HAL_ADC_MODULE_ENABLED
/**
  * @brief  Configures joystick available on adafruit 1.8" TFT shield 
  *         managed through ADC to detect motion.
  * @retval Joystickstatus (0=> success, 1=> fail) 
  */
uint8_t BSP_JOY_Init(void)
{
  if (ADCx_Init() != HAL_OK)
  {
    return (uint8_t) HAL_ERROR; 
  }

  /* Select Channel 15 to be converted */
  hnucleo_AdcChannelConfig.Channel       = ADC_CHANNEL_15;
  hnucleo_AdcChannelConfig.SamplingTime  = ADC_SAMPLETIME_24CYCLES_5;
  hnucleo_AdcChannelConfig.Rank          = 1;
  hnucleo_AdcChannelConfig.SingleDiff    = ADC_SINGLE_ENDED;
  hnucleo_AdcChannelConfig.OffsetNumber  = ADC_OFFSET_NONE;
  
  /* Return Joystick initialization status */
  return (uint8_t) HAL_ADC_ConfigChannel(&hnucleo_Adc, &hnucleo_AdcChannelConfig);
}

/**
  * @brief  Returns the Joystick key pressed.
  * @note   To know which Joystick key is pressed we need to detect the voltage
  *         level on each key output
  *           - None  : 3.3 V / 4095
  *           - SEL   : 1.055 V / 1308
  *           - DOWN  : 0.71 V / 88
  *           - LEFT  : 3.0 V / 3720 
  *           - RIGHT : 0.595 V / 737
  *           - UP    : 1.65 V / 2046
  * @retval JOYState_TypeDef: Code of the Joystick key pressed.
  */
JOYState_TypeDef BSP_JOY_GetState(void)
{
  JOYState_TypeDef state = JOY_NONE;
  uint16_t  keyconvertedvalue = 0; 

 /* Start the conversion process */
  HAL_ADC_Start(&hnucleo_Adc);
  
  /* Wait for the end of conversion */
  HAL_ADC_PollForConversion(&hnucleo_Adc, 10);
  
  /* Check if the continous conversion of regular channel is finished */
  if(HAL_ADC_GetState(&hnucleo_Adc) & HAL_ADC_STATE_REG_EOC)
  {
    /* Get the converted value of regular channel */
    keyconvertedvalue = HAL_ADC_GetValue(&hnucleo_Adc);
  }
  
  if((keyconvertedvalue > 1980) && (keyconvertedvalue < 2120))
  {
    state = JOY_UP;
  }
  else if((keyconvertedvalue > 630) && (keyconvertedvalue < 830))
  {
    state = JOY_RIGHT;
  }
  else if((keyconvertedvalue > 1210) && (keyconvertedvalue < 1410))
  {
    state = JOY_SEL;
  }
  else if((keyconvertedvalue > 20) && (keyconvertedvalue < 160))
  {
    state = JOY_DOWN;
  }
  else if((keyconvertedvalue > 3620) && (keyconvertedvalue < 3820))
  {
    state = JOY_LEFT;
  }
  else
  {
    state = JOY_NONE;
  }
  
  /* Return the code of the Joystick key pressed*/
  return state;
}

#endif /* HAL_ADC_MODULE_ENABLED */

/**
  * @}
  */ 

/**
  * @}
  */

/** @addtogroup STM32L4XX_NUCLEO_Private_Functions
  * @{
  */ 
  
#ifdef HAL_SPI_MODULE_ENABLED
/******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/
/**
  * @brief  Initialize SPI MSP.
  * @retval None
  */
static void SPIx_MspInit(void)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  NUCLEO_SPIx_SCK_GPIO_CLK_ENABLE();
  NUCLEO_SPIx_MISO_MOSI_GPIO_CLK_ENABLE();

  /* Configure SPI SCK */
  gpioinitstruct.Pin        = NUCLEO_SPIx_SCK_PIN;
  gpioinitstruct.Mode       = GPIO_MODE_AF_PP;
  gpioinitstruct.Pull       = GPIO_PULLUP;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_VERY_HIGH;
  gpioinitstruct.Alternate  = NUCLEO_SPIx_SCK_AF;
  HAL_GPIO_Init(NUCLEO_SPIx_SCK_GPIO_PORT, &gpioinitstruct);

  /* Configure SPI MISO and MOSI */ 
  gpioinitstruct.Pin        = NUCLEO_SPIx_MOSI_PIN;
  gpioinitstruct.Alternate  = NUCLEO_SPIx_MISO_MOSI_AF;
  gpioinitstruct.Pull       = GPIO_PULLDOWN;
  HAL_GPIO_Init(NUCLEO_SPIx_MISO_MOSI_GPIO_PORT, &gpioinitstruct);
  
  gpioinitstruct.Pin        = NUCLEO_SPIx_MISO_PIN;
  HAL_GPIO_Init(NUCLEO_SPIx_MISO_MOSI_GPIO_PORT, &gpioinitstruct);

  /*** Configure the SPI peripheral ***/ 
  /* Enable SPI clock */
  NUCLEO_SPIx_CLK_ENABLE();
}

/**
  * @brief  Initialize SPI HAL.
  * @retval None
  */
static void SPIx_Init(void)
{
  if(HAL_SPI_GetState(&hnucleo_Spi) == HAL_SPI_STATE_RESET)
  {
    /* SPI Config */
    hnucleo_Spi.Instance = NUCLEO_SPIx;
      /* SPI baudrate is set to 8 MHz maximum (PCLK2/SPI_BaudRatePrescaler = 32/4 = 8 MHz) 
       to verify these constraints:
          - ST7735 LCD SPI interface max baudrate is 15MHz for write and 6.66MHz for read
            Since the provided driver doesn't use read capability from LCD, only constraint 
            on write baudrate is considered.
          - SD card SPI interface max baudrate is 25MHz for write/read
          - PCLK2 max frequency is 32 MHz 
       */
    hnucleo_Spi.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_4;
    hnucleo_Spi.Init.Direction          = SPI_DIRECTION_2LINES;
    hnucleo_Spi.Init.CLKPhase           = SPI_PHASE_2EDGE;
    hnucleo_Spi.Init.CLKPolarity        = SPI_POLARITY_HIGH;
    hnucleo_Spi.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
    hnucleo_Spi.Init.CRCPolynomial      = 7;
    hnucleo_Spi.Init.CRCLength          = SPI_CRC_LENGTH_DATASIZE;
    hnucleo_Spi.Init.DataSize           = SPI_DATASIZE_8BIT;
    hnucleo_Spi.Init.FirstBit           = SPI_FIRSTBIT_MSB;
    hnucleo_Spi.Init.NSS                = SPI_NSS_SOFT;
    hnucleo_Spi.Init.NSSPMode           = SPI_NSS_PULSE_DISABLE;
    hnucleo_Spi.Init.TIMode             = SPI_TIMODE_DISABLE;
    hnucleo_Spi.Init.Mode               = SPI_MODE_MASTER;
    
    SPIx_MspInit();
    HAL_SPI_Init(&hnucleo_Spi);
  }
}

/**
  * @brief  SPI Write byte(s) to device
  * @param  DataIn: Pointer to data buffer to write
  * @param  DataOut: Pointer to data buffer for read data
  * @param  DataLength: number of bytes to write
  * @retval None
  */
static void SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;
  status = HAL_SPI_TransmitReceive(&hnucleo_Spi, (uint8_t*) DataIn, DataOut, DataLength, hnucleo_SpixTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Write a byte to device
  * @param  Value: value to be written
  * @retval None
  */
static void SPIx_Write(uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t data;

  status = HAL_SPI_TransmitReceive(&hnucleo_Spi, (uint8_t*) &Value, &data, 1, hnucleo_SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI error treatment function
  * @retval None
  */
static void SPIx_Error (void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&hnucleo_Spi);

  /* Re-Initiaize the SPI communication BUS */
  SPIx_Init();
}

/******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK SD ************************************/
/**
  * @brief  Initialize the SD Card and put it into StandBy State (Ready for 
  *         data transfer).
  * @retval None
  */
void SD_IO_Init(void)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  uint8_t counter = 0;

  /* SD_CS_GPIO Periph clock enable */
  SD_CS_GPIO_CLK_ENABLE();

  /* Configure SD_CS_PIN pin: SD Card CS pin */
  gpioinitstruct.Pin    = SD_CS_PIN;
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_PULLUP;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SD_CS_GPIO_PORT, &gpioinitstruct);

  /* Configure LCD_CS_PIN pin: LCD Card CS pin */
  gpioinitstruct.Pin   = LCD_CS_PIN;
  gpioinitstruct.Mode  = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull  = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SD_CS_GPIO_PORT, &gpioinitstruct);
  LCD_CS_HIGH();

  /*------------Put SD in SPI mode--------------*/
  /* SD SPI Config */
  SPIx_Init();

  /* SD chip select high */
  SD_CS_HIGH();
  
  /* Send dummy byte 0xFF, 10 times with CS high */
  /* Rise CS and MOSI for 80 clocks cycles */
  for (counter = 0; counter <= 9; counter++)
  {
    /* Send dummy byte 0xFF */
    SD_IO_WriteByte(SD_DUMMY_BYTE);
  }
}

/**
  * @brief  Set SD interface Chip Select state
  * @param  val: 0 (low) or 1 (high) state
  * @retval None
  */
void SD_IO_CSState(uint8_t val)
{
  if(val == 1) 
  {
    SD_CS_HIGH();
  }
  else
  {
    SD_CS_LOW();
  }
}

/**
  * @brief  Write byte(s) on the SD
  * @param  DataIn: Pointer to data buffer to write
  * @param  DataOut: Pointer to data buffer for read data
  * @param  DataLength: number of bytes to write
  * @retval None
  */
void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_WriteReadData(DataIn, DataOut, DataLength);
}

/**
  * @brief  Write a byte on the SD.
  * @param  Data: byte to send.
  * @retval Data written
  */
uint8_t SD_IO_WriteByte(uint8_t Data)
{
  uint8_t tmp;

  /* Send the byte */
  SPIx_WriteReadData(&Data,&tmp,1);
  return tmp;
}
 
/********************************* LINK LCD ***********************************/
/**
  * @brief  Initialize the LCD
  * @retval None
  */
void LCD_IO_Init(void)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

  /* LCD_CS_GPIO and LCD_DC_GPIO Periph clock enable */
  LCD_CS_GPIO_CLK_ENABLE();
  LCD_DC_GPIO_CLK_ENABLE();
  
  /* Configure LCD_CS_PIN pin: LCD Card CS pin */
  gpioinitstruct.Pin    = LCD_CS_PIN;
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SD_CS_GPIO_PORT, &gpioinitstruct);
      
  /* Configure LCD_DC_PIN pin: LCD Card DC pin */
  gpioinitstruct.Pin    = LCD_DC_PIN;
  HAL_GPIO_Init(LCD_DC_GPIO_PORT, &gpioinitstruct);

  /* LCD chip select high */
  LCD_CS_HIGH();
  
  /* LCD SPI Config */
  SPIx_Init();
}

/**
  * @brief  Write command to select the LCD register.
  * @param  LCDReg: Address of the selected register.
  * @retval None
  */
void LCD_IO_WriteReg(uint8_t LCDReg)
{
  /* Reset LCD control line CS */
  LCD_CS_LOW();
  
  /* Set LCD data/command line DC to Low */
  LCD_DC_LOW();
    
  /* Send Command */
  SPIx_Write(LCDReg);
  
  /* Deselect : Chip Select high */
  LCD_CS_HIGH();
}

/**
* @brief  Write register value.
* @param  pData Pointer on the register value
* @param  Size Size of byte to transmit to the register
* @retval None
*/
void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
{
  uint32_t counter = 0;
  __IO uint32_t data = 0;
  
  /* Reset LCD control line CS */
  LCD_CS_LOW();
  
  /* Set LCD data/command line DC to High */
  LCD_DC_HIGH();

  if (Size == 1)
  {
    /* Only 1 byte to be sent to LCD - general interface can be used */
    /* Send Data */
    SPIx_Write(*pData);
  }
  else
  {
    /* Several data should be sent in a raw */
    /* Direct SPI accesses for optimization */
    for (counter = Size; counter != 0; counter--)
    {
      while(((hnucleo_Spi.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE)
      {
      }
      /* Need to invert bytes for LCD*/
      *((__IO uint8_t*)&hnucleo_Spi.Instance->DR) = *(pData+1);
      
      while(((hnucleo_Spi.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE)
      {
      }
      *((__IO uint8_t*)&hnucleo_Spi.Instance->DR) = *pData;
      counter--;
      pData += 2;
    }
    
    /* Wait until the bus is ready before releasing Chip select */ 
    while(((hnucleo_Spi.Instance->SR) & SPI_FLAG_BSY) != RESET)
    {
    }  
  } 

  /* Empty the Rx fifo */
  data = *(&hnucleo_Spi.Instance->DR);
  UNUSED(data);  /* Remove GNU warning */

  /* Deselect : Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Wait for loop in ms.
  * @param  Delay in ms.
  * @retval None
  */
void LCD_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
/******************************* LINK JOYSTICK ********************************/
/**
  * @brief  Initialize ADC MSP.
  * @retval None
  */
static void ADCx_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  NUCLEO_ADCx_GPIO_CLK_ENABLE();
  
  /* Configure ADC1 Channel8 as analog input */
  gpioinitstruct.Pin    = NUCLEO_ADCx_GPIO_PIN ;
  gpioinitstruct.Mode   = GPIO_MODE_ANALOG_ADC_CONTROL;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(NUCLEO_ADCx_GPIO_PORT, &gpioinitstruct);

  /*** Configure the ADC peripheral ***/ 
  /* Enable ADC clock */
  NUCLEO_ADCx_CLK_ENABLE();
  
  /* Configure SYSCLK as source clock for ADC */
  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  RCC_PeriphCLKInitStruct.AdcClockSelection    = RCC_ADCCLKSOURCE_SYSCLK;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);
}

/**
  * @brief  Initializes ADC HAL.
  * @retval None
  */
static HAL_StatusTypeDef ADCx_Init(void)
{
  if(HAL_ADC_GetState(&hnucleo_Adc) == HAL_ADC_STATE_RESET)
  {
    /* ADC Config */
    hnucleo_Adc.Instance                    = NUCLEO_ADCx;
    hnucleo_Adc.Init.ClockPrescaler         = ADC_CLOCK_ASYNC_DIV8; /* (must not exceed 16MHz) */
    hnucleo_Adc.Init.Resolution             = ADC_RESOLUTION_12B;
    hnucleo_Adc.Init.DataAlign              = ADC_DATAALIGN_RIGHT;
    hnucleo_Adc.Init.ScanConvMode           = DISABLE;
    hnucleo_Adc.Init.EOCSelection           = ADC_EOC_SINGLE_CONV;
    hnucleo_Adc.Init.LowPowerAutoWait       = ENABLE;
    hnucleo_Adc.Init.ContinuousConvMode     = DISABLE;
    hnucleo_Adc.Init.NbrOfConversion        = 1;
    hnucleo_Adc.Init.DiscontinuousConvMode  = DISABLE;
    hnucleo_Adc.Init.NbrOfDiscConversion    = 1;
    hnucleo_Adc.Init.ExternalTrigConv       = ADC_SOFTWARE_START;
    hnucleo_Adc.Init.ExternalTrigConvEdge   = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hnucleo_Adc.Init.DMAContinuousRequests  = DISABLE;
    hnucleo_Adc.Init.Overrun                = ADC_OVR_DATA_PRESERVED;
    hnucleo_Adc.Init.OversamplingMode       = DISABLE;
    
    ADCx_MspInit(&hnucleo_Adc);
    if (HAL_ADC_Init(&hnucleo_Adc) != HAL_OK)
    {
      return HAL_ERROR;
    }
    
    if (HAL_ADCEx_Calibration_Start(&hnucleo_Adc,ADC_SINGLE_ENDED) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}  

#endif /* HAL_ADC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */    

/**
  * @}
  */ 
    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
