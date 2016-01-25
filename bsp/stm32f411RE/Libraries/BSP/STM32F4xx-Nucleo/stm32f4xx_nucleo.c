/**
  ******************************************************************************
  * @file    stm32f4xx_nucleo.c
  * @author  MCD Application Team
  * @version V1.2.3
  * @date    13-September-2015
  * @brief   This file provides set of firmware functions to manage:
  *          - LEDs and push-button available on STM32F4XX-Nucleo Kit 
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
#include "stm32f4xx_nucleo.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F4XX_NUCLEO
  * @{
  */   
    
/** @addtogroup STM32F4XX_NUCLEO_LOW_LEVEL 
  * @brief This file provides set of firmware functions to manage Leds and push-button
  *        available on STM32F4xx-Nucleo Kit from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_Defines
  * @{
  */ 

/**
  * @brief STM32F4xx NUCLEO BSP Driver version number V1.2.3
  */
#define __STM32F4xx_NUCLEO_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32F4xx_NUCLEO_BSP_VERSION_SUB1   (0x02) /*!< [23:16] sub1 version */
#define __STM32F4xx_NUCLEO_BSP_VERSION_SUB2   (0x03) /*!< [15:8]  sub2 version */
#define __STM32F4xx_NUCLEO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F4xx_NUCLEO_BSP_VERSION        ((__STM32F4xx_NUCLEO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F4xx_NUCLEO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F4xx_NUCLEO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F4xx_NUCLEO_BSP_VERSION_RC))   

/**
  * @brief LINK SD Card
  */
#define SD_DUMMY_BYTE            0xFF    
#define SD_NO_RESPONSE_EXPECTED  0x80

/**
  * @}
  */ 

/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED2_GPIO_PORT};

const uint16_t GPIO_PIN[LEDn] = {LED2_PIN};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {KEY_BUTTON_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn] = {KEY_BUTTON_PIN}; 
const uint8_t BUTTON_IRQn[BUTTONn] = {KEY_BUTTON_EXTI_IRQn};

/**
 * @brief BUS variables
 */

#ifdef ADAFRUIT_TFT_JOY_SD_ID802
#ifdef HAL_SPI_MODULE_ENABLED
uint32_t SpixTimeout = NUCLEO_SPIx_TIMEOUT_MAX; /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef hnucleo_Spi;
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
static ADC_HandleTypeDef hnucleo_Adc;
/* ADC channel configuration structure declaration */
static ADC_ChannelConfTypeDef sConfig;
#endif /* HAL_ADC_MODULE_ENABLED */
#endif /* ADAFRUIT_TFT_JOY_SD_ID802 */

/**
  * @}
  */ 

/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */
#ifdef ADAFRUIT_TFT_JOY_SD_ID802

#ifdef HAL_SPI_MODULE_ENABLED
static void       SPIx_Init(void);
static void       SPIx_Write(uint8_t Value);
static void       SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLegnth);
static void       SPIx_Error(void);
static void       SPIx_MspInit(SPI_HandleTypeDef *hspi);

/* SD IO functions */
void              SD_IO_Init(void);
void              SD_IO_CSState(uint8_t state);
void              SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
uint8_t           SD_IO_WriteByte(uint8_t Data);

/* LCD IO functions */
void              LCD_IO_Init(void);
void              LCD_IO_WriteData(uint8_t Data);
void              LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size);
void              LCD_IO_WriteReg(uint8_t LCDReg);
void              LCD_Delay(uint32_t delay);
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
static void       ADCx_Init(void);
static void       ADCx_DeInit(void);
static void       ADCx_MspInit(ADC_HandleTypeDef *hadc);
static void ADCx_MspDeInit(ADC_HandleTypeDef *hadc);
#endif /* HAL_ADC_MODULE_ENABLED */

#endif /* ADAFRUIT_TFT_JOY_SD_ID802 */

/**
  * @}
  */ 

/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32F4xx NUCLEO BSP Driver revision
  * @param  None
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F4xx_NUCLEO_BSP_VERSION;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED2
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = GPIO_PIN[Led];
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  
  HAL_GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be de-init. 
  *   This parameter can be one of the following values:
  *     @arg  LED2
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx 
  * @retval None
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = GPIO_PIN[Led];
  HAL_GPIO_DeInit(GPIO_PORT[Led], gpio_init_structure.Pin);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED2
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
  *     @arg LED2
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
  *     @arg LED2  
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_KEY
  * @param  ButtonMode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button: Button to be configured
  *   This parameter should be: BUTTON_KEY
  * @note PB DeInit does not disable the GPIO clock
  * @retval None
  */
void BSP_PB_DeInit(Button_TypeDef Button)
{
    GPIO_InitTypeDef gpio_init_structure;

    gpio_init_structure.Pin = BUTTON_PIN[Button];
    HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_KEY  
  * @retval The Button GPIO pin value.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/
#ifdef ADAFRUIT_TFT_JOY_SD_ID802

/******************************* SPI ********************************/
#ifdef HAL_SPI_MODULE_ENABLED

/**
  * @brief  Initializes SPI MSP.
  * @param  None
  * @retval None
  */
static void SPIx_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  GPIO_InitStruct;  
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  NUCLEO_SPIx_SCK_GPIO_CLK_ENABLE();
  NUCLEO_SPIx_MISO_MOSI_GPIO_CLK_ENABLE();
  
  /* Configure SPI SCK */
  GPIO_InitStruct.Pin = NUCLEO_SPIx_SCK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = NUCLEO_SPIx_SCK_AF;
  HAL_GPIO_Init(NUCLEO_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

  /* Configure SPI MISO and MOSI */ 
  GPIO_InitStruct.Pin = NUCLEO_SPIx_MOSI_PIN;
  GPIO_InitStruct.Alternate = NUCLEO_SPIx_MISO_MOSI_AF;
  GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
  HAL_GPIO_Init(NUCLEO_SPIx_MISO_MOSI_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = NUCLEO_SPIx_MISO_PIN;
  GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
  HAL_GPIO_Init(NUCLEO_SPIx_MISO_MOSI_GPIO_PORT, &GPIO_InitStruct);

  /*** Configure the SPI peripheral ***/ 
  /* Enable SPI clock */
  NUCLEO_SPIx_CLK_ENABLE();
}

/**
  * @brief  Initializes SPI HAL.
  * @param  None
  * @retval None
  */
static void SPIx_Init(void)
{
  if(HAL_SPI_GetState(&hnucleo_Spi) == HAL_SPI_STATE_RESET)
  {
    /* SPI Config */
    hnucleo_Spi.Instance = NUCLEO_SPIx;
      /* SPI baudrate is set to 12,5 MHz maximum (APB1/SPI_BaudRatePrescaler = 100/8 = 12,5 MHz) 
       to verify these constraints:
          - ST7735 LCD SPI interface max baudrate is 15MHz for write and 6.66MHz for read
            Since the provided driver doesn't use read capability from LCD, only constraint 
            on write baudrate is considered.
          - SD card SPI interface max baudrate is 25MHz for write/read
          - PCLK2 max frequency is 100 MHz 
       */ 
    hnucleo_Spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hnucleo_Spi.Init.Direction = SPI_DIRECTION_2LINES;
    hnucleo_Spi.Init.CLKPhase = SPI_PHASE_2EDGE;
    hnucleo_Spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hnucleo_Spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    hnucleo_Spi.Init.CRCPolynomial = 7;
    hnucleo_Spi.Init.DataSize = SPI_DATASIZE_8BIT;
    hnucleo_Spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hnucleo_Spi.Init.NSS = SPI_NSS_SOFT;
    hnucleo_Spi.Init.TIMode = SPI_TIMODE_DISABLED;
    hnucleo_Spi.Init.Mode = SPI_MODE_MASTER;

    SPIx_MspInit(&hnucleo_Spi);
    HAL_SPI_Init(&hnucleo_Spi);
  }
}

/**
  * @brief  SPI Write a byte to device
  * @param  Value: value to be written
  * @retval None
  */
static void SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLegnth)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_TransmitReceive(&hnucleo_Spi, (uint8_t*) DataIn, DataOut, DataLegnth, SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI Write a byte to device.
  * @param  Value: value to be written
  * @retval None
  */
static void SPIx_Write(uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t data;

  status = HAL_SPI_TransmitReceive(&hnucleo_Spi, (uint8_t*) &Value, &data, 1, SpixTimeout);
    
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief  SPI error treatment function.
  * @param  None
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
  * @brief  Initializes the SD Card and put it into StandBy State (Ready for 
  *         data transfer).
  * @param  None
  * @retval None
  */
void SD_IO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  uint8_t counter;

  /* SD_CS_GPIO Periph clock enable */
  SD_CS_GPIO_CLK_ENABLE();

  /* Configure SD_CS_PIN pin: SD Card CS pin */
  GPIO_InitStruct.Pin = SD_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(SD_CS_GPIO_PORT, &GPIO_InitStruct);

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
  * @brief Set the SD_CS pin.
  * @param pin value.
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
  * @brief Write a byte on the SD.
  * @param Data: byte to send.
  * @retval None
  */
void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
  /* Send the byte */
  SPIx_WriteReadData(DataIn, DataOut, DataLength);
}

/**
  * @brief  Writes a byte on the SD.
  * @param  Data: byte to send.
  * @retval None
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
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */
void LCD_IO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
   
  /* LCD_CS_GPIO and LCD_DC_GPIO Periph clock enable */
  LCD_CS_GPIO_CLK_ENABLE();
  LCD_DC_GPIO_CLK_ENABLE();
  
  /* Configure LCD_CS_PIN pin: LCD Card CS pin */
  GPIO_InitStruct.Pin = LCD_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStruct);

  /* Configure LCD_DC_PIN pin: LCD Card DC pin */
  GPIO_InitStruct.Pin = LCD_DC_PIN;
  HAL_GPIO_Init(LCD_DC_GPIO_PORT, &GPIO_InitStruct);
  
  /* LCD chip select high */
  LCD_CS_HIGH();
  
  /* LCD SPI Config */
  SPIx_Init();
}

/**
  * @brief  Writes command to select the LCD register.
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
  * @brief  Writes data to select the LCD register.
  *         This function must be used after st7735_WriteReg() function
  * @param  Data: data to write to the selected register.
  * @retval None
  */
void LCD_IO_WriteData(uint8_t Data)
{
  /* Reset LCD control line CS */
  LCD_CS_LOW();
  
  /* Set LCD data/command line DC to High */
  LCD_DC_HIGH();

  /* Send Data */
  SPIx_Write(Data);
  
  /* Deselect : Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Writes register value.
  * @param  pData: Pointer on the register value
  * @param  Size: Size of byte to transmit to the register
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

/******************************* ADC driver ********************************/
#ifdef HAL_ADC_MODULE_ENABLED

/**
  * @brief  Initializes ADC MSP.
  * @param  None
  * @retval None
  */
static void ADCx_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  NUCLEO_ADCx_GPIO_CLK_ENABLE();
  
  /* Configure the selected ADC Channel as analog input */
  GPIO_InitStruct.Pin = NUCLEO_ADCx_GPIO_PIN ;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(NUCLEO_ADCx_GPIO_PORT, &GPIO_InitStruct);
  
  /*** Configure the ADC peripheral ***/ 
  /* Enable ADC clock */
  NUCLEO_ADCx_CLK_ENABLE(); 
}

/**
  * @brief  DeInitializes ADC MSP.
  * @param  None
  * @note ADC DeInit does not disable the GPIO clock
  * @retval None
  */
static void ADCx_MspDeInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /*** DeInit the ADC peripheral ***/ 
  /* Disable ADC clock */
  NUCLEO_ADCx_CLK_DISABLE(); 

  /* Configure the selected ADC Channel as analog input */
  GPIO_InitStruct.Pin = NUCLEO_ADCx_GPIO_PIN ;
  HAL_GPIO_DeInit(NUCLEO_ADCx_GPIO_PORT, GPIO_InitStruct.Pin);

  /* Disable GPIO clock has to be done by the application*/
  /* NUCLEO_ADCx_GPIO_CLK_DISABLE(); */
}

/**
  * @brief  Initializes ADC HAL.
  * @param  None
  * @retval None
  */
static void ADCx_Init(void)
{
  if(HAL_ADC_GetState(&hnucleo_Adc) == HAL_ADC_STATE_RESET)
  {
    /* ADC Config */
    hnucleo_Adc.Instance                   = NUCLEO_ADCx;
    hnucleo_Adc.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4; /* (must not exceed 36MHz) */
    hnucleo_Adc.Init.Resolution            = ADC_RESOLUTION12b;
    hnucleo_Adc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hnucleo_Adc.Init.ContinuousConvMode    = DISABLE;
    hnucleo_Adc.Init.DiscontinuousConvMode = DISABLE;
    hnucleo_Adc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hnucleo_Adc.Init.EOCSelection          = EOC_SINGLE_CONV;
    hnucleo_Adc.Init.NbrOfConversion       = 1;
    hnucleo_Adc.Init.DMAContinuousRequests = DISABLE;    
    
    ADCx_MspInit(&hnucleo_Adc);
    HAL_ADC_Init(&hnucleo_Adc);
  }
}

/**
  * @brief  Initializes ADC HAL.
  * @param  None
  * @retval None
  */
static void ADCx_DeInit(void)
{
    hnucleo_Adc.Instance   = NUCLEO_ADCx;
    
    HAL_ADC_DeInit(&hnucleo_Adc);
    ADCx_MspDeInit(&hnucleo_Adc);
}

/******************************* LINK JOYSTICK ********************************/

/**
  * @brief  Configures joystick available on adafruit 1.8" TFT shield 
  *         managed through ADC to detect motion.
  * @param  None
  * @retval Joystickstatus (0=> success, 1=> fail) 
  */
uint8_t BSP_JOY_Init(void)
{
  uint8_t status = HAL_ERROR;
   
  ADCx_Init();
   
  /* Select the ADC Channel to be converted */
  sConfig.Channel = NUCLEO_ADCx_CHANNEL;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfig.Rank = 1;
  status = HAL_ADC_ConfigChannel(&hnucleo_Adc, &sConfig);
  
  /* Return Joystick initialization status */
  return status;
}

/**
  * @brief  DeInit joystick GPIOs.
  * @note   JOY DeInit does not disable the Mfx, just set the Mfx pins in Off mode
  * @retval None.
  */
void BSP_JOY_DeInit(void)
{
    ADCx_DeInit();
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
  JOYState_TypeDef state;
  uint16_t  keyconvertedvalue = 0;
  
  /* Start the conversion process */
  HAL_ADC_Start(&hnucleo_Adc);
  
  /* Wait for the end of conversion */
  HAL_ADC_PollForConversion(&hnucleo_Adc, 10);
  
  /* Check if the continuous conversion of regular channel is finished */
  if(HAL_ADC_GetState(&hnucleo_Adc) == HAL_ADC_STATE_EOC_REG)
  {
    /* Get the converted value of regular channel */
    keyconvertedvalue = HAL_ADC_GetValue(&hnucleo_Adc);
  }
  
  if((keyconvertedvalue > 2010) && (keyconvertedvalue < 2090))
  {
    state = JOY_UP;
  }
  else if((keyconvertedvalue > 680) && (keyconvertedvalue < 780))
  {
    state = JOY_RIGHT;
  }
  else if((keyconvertedvalue > 1270) && (keyconvertedvalue < 1350))
  {
    state = JOY_SEL;
  }
  else if((keyconvertedvalue > 50) && (keyconvertedvalue < 130))
  {
    state = JOY_DOWN;
  }
  else if((keyconvertedvalue > 3680) && (keyconvertedvalue < 3760))
  {
    state = JOY_LEFT;
  }
  else
  {
    state = JOY_NONE;
  }
  
  /* Loop while a key is pressed */
  if(state != JOY_NONE)
  { 
    keyconvertedvalue = HAL_ADC_GetValue(&hnucleo_Adc);  
  }
  /* Return the code of the Joystick key pressed */
  return state;
}
#endif /* HAL_ADC_MODULE_ENABLED */

#endif /* ADAFRUIT_TFT_JOY_SD_ID802 */


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
