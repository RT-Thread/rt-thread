/**
  ******************************************************************************
  * @file    stm32f429i_discovery.c
  * @author  MCD Application Team
  * @version V2.1.2
  * @date    02-March-2015
  * @brief   This file provides set of firmware functions to manage Leds and
  *          push-button available on STM32F429I-Discovery Kit from STMicroelectronics.
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
#include "stm32f429i_discovery.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
      
/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL 
  * @brief This file provides set of firmware functions to manage Leds and push-button
  *        available on STM32F429I-Discovery Kit from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_Defines
  * @{
  */ 
  
  /**
  * @brief STM32F429I DISCO BSP Driver version number V2.1.0
  */
#define __STM32F429I_DISCO_BSP_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM32F429I_DISCO_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM32F429I_DISCO_BSP_VERSION_SUB2   (0x02) /*!< [15:8]  sub2 version */
#define __STM32F429I_DISCO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F429I_DISCO_BSP_VERSION        ((__STM32F429I_DISCO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F429I_DISCO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F429I_DISCO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F429I_DISCO_BSP_VERSION_RC)) 
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED3_GPIO_PORT, 
                                 LED4_GPIO_PORT};

const uint16_t GPIO_PIN[LEDn] = {LED3_PIN, 
                                 LED4_PIN};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {KEY_BUTTON_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn] = {KEY_BUTTON_PIN}; 
const uint8_t BUTTON_IRQn[BUTTONn] = {KEY_BUTTON_EXTI_IRQn};

uint32_t I2cxTimeout = I2Cx_TIMEOUT_MAX; /*<! Value of Timeout when I2C communication fails */  
uint32_t SpixTimeout = SPIx_TIMEOUT_MAX; /*<! Value of Timeout when SPI communication fails */  

I2C_HandleTypeDef I2cHandle;
static SPI_HandleTypeDef SpiHandle;
static uint8_t Is_LCD_IO_Initialized = 0;

/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 
/* I2Cx bus function */
static void               I2Cx_Init(void);
static void               I2Cx_ITConfig(void);
static void               I2Cx_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value);
static void               I2Cx_WriteBuffer(uint8_t Addr, uint8_t Reg,  uint8_t *pBuffer, uint16_t Length);
static uint8_t            I2Cx_ReadData(uint8_t Addr, uint8_t Reg);
static uint8_t            I2Cx_ReadBuffer(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);
static void               I2Cx_Error(void);
static void               I2Cx_MspInit(I2C_HandleTypeDef *hi2c);  
#ifdef EE_M24LR64
static HAL_StatusTypeDef  I2Cx_WriteBufferDMA(uint8_t Addr, uint16_t Reg,  uint8_t *pBuffer, uint16_t Length);
static HAL_StatusTypeDef  I2Cx_ReadBufferDMA(uint8_t Addr, uint16_t Reg, uint8_t *pBuffer, uint16_t Length);
static HAL_StatusTypeDef  I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
#endif /* EE_M24LR64 */

/* SPIx bus function */
static void               SPIx_Init(void);
static void               SPIx_Write(uint16_t Value);
static uint32_t           SPIx_Read(uint8_t ReadSize);
static uint8_t            SPIx_WriteRead(uint8_t Byte);
static void               SPIx_Error(void);
static void               SPIx_MspInit(SPI_HandleTypeDef *hspi);

/* Link function for LCD peripheral */
void                      LCD_IO_Init(void);
void                      LCD_IO_WriteData(uint16_t RegValue);
void                      LCD_IO_WriteReg(uint8_t Reg);
uint32_t                  LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize);
void                      LCD_Delay(uint32_t delay);

/* IOExpander IO functions */
void                      IOE_Init(void);
void                      IOE_ITConfig(void);
void                      IOE_Delay(uint32_t Delay);
void                      IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t                   IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t                  IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);
void                      IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);

/* Link function for GYRO peripheral */
void                      GYRO_IO_Init(void);
void                      GYRO_IO_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void                      GYRO_IO_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);

#ifdef EE_M24LR64
/* Link function for I2C EEPROM peripheral */
void                      EEPROM_IO_Init(void);
HAL_StatusTypeDef         EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
#endif /* EE_M24LR64 */

/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32F429I DISCO BSP Driver revision
  * @param  None
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F429I_DISCO_BSP_VERSION;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
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
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  
  HAL_GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4 
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
  *     @arg LED3
  *     @arg LED4
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
  *     @arg LED3
  *     @arg LED4  
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
  * @param  Button_Mode: Specifies Button mode.
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
  
  if (ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  if (ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
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

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/

/**
  * @brief  I2Cx MSP Initialization
  * @param  hi2c: I2C handle
  * @retval None
  */
static void I2Cx_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  GPIO_InitStruct;  
#ifdef EE_M24LR64
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;
  
  I2C_HandleTypeDef* pI2cHandle;
  pI2cHandle = &I2cHandle;
#endif /* EE_M24LR64 */

  if (hi2c->Instance == DISCOVERY_I2Cx)
  {
    /* Configure the GPIOs ---------------------------------------------------*/ 
    /* Enable GPIO clock */
    DISCOVERY_I2Cx_SDA_GPIO_CLK_ENABLE();
    DISCOVERY_I2Cx_SCL_GPIO_CLK_ENABLE();
      
    /* Configure I2C Tx as alternate function  */
    GPIO_InitStruct.Pin       = DISCOVERY_I2Cx_SCL_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = DISCOVERY_I2Cx_SCL_SDA_AF;
    HAL_GPIO_Init(DISCOVERY_I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);
      
    /* Configure I2C Rx as alternate function  */
    GPIO_InitStruct.Pin = DISCOVERY_I2Cx_SDA_PIN;
    HAL_GPIO_Init(DISCOVERY_I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
    
    
    /* Configure the Discovery I2Cx peripheral -------------------------------*/ 
    /* Enable I2C3 clock */
    DISCOVERY_I2Cx_CLOCK_ENABLE();
    
    /* Force the I2C Peripheral Clock Reset */  
    DISCOVERY_I2Cx_FORCE_RESET();
      
    /* Release the I2C Peripheral Clock Reset */  
    DISCOVERY_I2Cx_RELEASE_RESET(); 
    
    /* Enable and set Discovery I2Cx Interrupt to the highest priority */
    HAL_NVIC_SetPriority(DISCOVERY_I2Cx_EV_IRQn, 0x00, 0);
    HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_EV_IRQn);
    
    /* Enable and set Discovery I2Cx Interrupt to the highest priority */
    HAL_NVIC_SetPriority(DISCOVERY_I2Cx_ER_IRQn, 0x00, 0);
    HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_ER_IRQn);  

#ifdef EE_M24LR64
    /* I2C DMA TX and RX channels configuration */
    /* Enable the DMA clock */
    EEPROM_I2C_DMA_CLK_ENABLE();
    
    /* Configure the DMA stream for the EE I2C peripheral TX direction */
    /* Configure the DMA Stream */
    hdma_tx.Instance                  = EEPROM_I2C_DMA_STREAM_TX;
    /* Set the parameters to be configured */
    hdma_tx.Init.Channel              = EEPROM_I2C_DMA_CHANNEL;  
    hdma_tx.Init.Direction            = DMA_MEMORY_TO_PERIPH;
    hdma_tx.Init.PeriphInc            = DMA_PINC_DISABLE;
    hdma_tx.Init.MemInc               = DMA_MINC_ENABLE;
    hdma_tx.Init.PeriphDataAlignment  = DMA_PDATAALIGN_BYTE;
    hdma_tx.Init.MemDataAlignment     = DMA_MDATAALIGN_BYTE;
    hdma_tx.Init.Mode                 = DMA_NORMAL;
    hdma_tx.Init.Priority             = DMA_PRIORITY_VERY_HIGH;
    hdma_tx.Init.FIFOMode             = DMA_FIFOMODE_ENABLE;         
    hdma_tx.Init.FIFOThreshold        = DMA_FIFO_THRESHOLD_FULL;
    hdma_tx.Init.MemBurst             = DMA_MBURST_SINGLE;
    hdma_tx.Init.PeriphBurst          = DMA_PBURST_SINGLE; 

    /* Associate the initilalized hdma_tx handle to the the pI2cHandle handle */
    __HAL_LINKDMA(pI2cHandle, hdmatx, hdma_tx);
    
    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_tx);
    
    /* Configure and enable I2C DMA TX Channel interrupt */
    HAL_NVIC_SetPriority((IRQn_Type)(EEPROM_I2C_DMA_TX_IRQn), EEPROM_I2C_DMA_PREPRIO, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(EEPROM_I2C_DMA_TX_IRQn));
    
    /* Configure the DMA stream for the EE I2C peripheral TX direction */
    /* Configure the DMA Stream */
    hdma_rx.Instance                  = EEPROM_I2C_DMA_STREAM_RX;
    /* Set the parameters to be configured */
    hdma_rx.Init.Channel              = EEPROM_I2C_DMA_CHANNEL;  
    hdma_rx.Init.Direction            = DMA_PERIPH_TO_MEMORY;
    hdma_rx.Init.PeriphInc            = DMA_PINC_DISABLE;
    hdma_rx.Init.MemInc               = DMA_MINC_ENABLE;
    hdma_rx.Init.PeriphDataAlignment  = DMA_PDATAALIGN_BYTE;
    hdma_rx.Init.MemDataAlignment     = DMA_MDATAALIGN_BYTE;
    hdma_rx.Init.Mode                 = DMA_NORMAL;
    hdma_rx.Init.Priority             = DMA_PRIORITY_VERY_HIGH;
    hdma_rx.Init.FIFOMode             = DMA_FIFOMODE_ENABLE;         
    hdma_rx.Init.FIFOThreshold        = DMA_FIFO_THRESHOLD_FULL;
    hdma_rx.Init.MemBurst             = DMA_MBURST_SINGLE;
    hdma_rx.Init.PeriphBurst          = DMA_PBURST_SINGLE; 

    /* Associate the initilalized hdma_rx handle to the the pI2cHandle handle*/
    __HAL_LINKDMA(pI2cHandle, hdmarx, hdma_rx);
    
    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_rx);
    
    /* Configure and enable I2C DMA RX Channel interrupt */
    HAL_NVIC_SetPriority((IRQn_Type)(EEPROM_I2C_DMA_RX_IRQn), EEPROM_I2C_DMA_PREPRIO, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(EEPROM_I2C_DMA_RX_IRQn));
#endif /* EE_M24LR64 */
  }
}

/**
  * @brief  I2Cx Bus initialization.
  * @param  None
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&I2cHandle) == HAL_I2C_STATE_RESET)
  {
    I2cHandle.Instance              = DISCOVERY_I2Cx;
    I2cHandle.Init.ClockSpeed       = BSP_I2C_SPEED;
    I2cHandle.Init.DutyCycle        = I2C_DUTYCYCLE_2;
    I2cHandle.Init.OwnAddress1      = 0;
    I2cHandle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLED;
    I2cHandle.Init.OwnAddress2      = 0;
    I2cHandle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLED;
    I2cHandle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLED;  
    
    /* Init the I2C */
    I2Cx_MspInit(&I2cHandle);
    HAL_I2C_Init(&I2cHandle);
  }
}

/**
  * @brief  Configures Interruption pin for I2C communication.
  * @param  None
  * @retval None
  */
static void I2Cx_ITConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
    
  /* Enable the GPIO EXTI Clock */
  STMPE811_INT_CLK_ENABLE();
  
  GPIO_InitStruct.Pin   = STMPE811_INT_PIN;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
  HAL_GPIO_Init(STMPE811_INT_GPIO_PORT, &GPIO_InitStruct);
    
  /* Enable and set GPIO EXTI Interrupt to the highest priority */
  HAL_NVIC_SetPriority((IRQn_Type)(STMPE811_INT_EXTI), 0x00, 0x00);
  HAL_NVIC_EnableIRQ((IRQn_Type)(STMPE811_INT_EXTI));
}

/**
  * @brief  Writes a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written 
  * @retval None
  */
static void I2Cx_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value)
  {
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout); 
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  }        
}

/**
  * @brief  Writes a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval None
  */
static void I2Cx_WriteBuffer(uint8_t Addr, uint8_t Reg,  uint8_t *pBuffer, uint16_t Length)
  {
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, pBuffer, Length, I2cxTimeout); 

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  }        
}

/**
  * @brief  Reads a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @retval Data read at register address
  */
static uint8_t I2Cx_ReadData(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;
  
  status = HAL_I2C_Mem_Read(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, I2cxTimeout);
 
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  
  }
  return value;
}

/**
  * @brief  Reads multiple data on the BUS.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to read data buffer
  * @param  Length: length of the data
  * @retval 0 if no problems to read multiple data
  */
static uint8_t I2Cx_ReadBuffer(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, pBuffer, Length, I2cxTimeout);
  
  /* Check the communication status */
  if(status == HAL_OK)
  {
    return 0;
  }
  else
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();

    return 1;
  }
}

#ifdef EE_M24LR64
/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteBufferDMA(uint8_t Addr, uint16_t Reg,  uint8_t *pBuffer, uint16_t Length)
  {
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write_DMA(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_16BIT, pBuffer, Length);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  }

  return status;
}

/**
  * @brief  Reads multiple data on the BUS in using DMA mode.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to read data buffer
  * @param  Length: length of the data
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_ReadBufferDMA(uint8_t Addr, uint16_t Reg, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read_DMA(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_16BIT, pBuffer, Length);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  }
  
  return status;
}

/**
* @brief  Checks if target device is ready for communication. 
* @note   This function is used with Memory devices
* @param  DevAddress: Target device address
* @param  Trials: Number of trials
* @retval HAL status
*/
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (HAL_I2C_IsDeviceReady(&I2cHandle, DevAddress, Trials, I2cxTimeout));
}
#endif /* EE_M24LR64 */

/**
  * @brief  I2Cx error treatment function
  * @param  None
  * @retval None
  */
static void I2Cx_Error(void)
{
  /* De-initialize the SPI communication BUS */
  HAL_I2C_DeInit(&I2cHandle);
  
  /* Re-Initialize the SPI communication BUS */
  I2Cx_Init();
}

/******************************* SPI Routines *********************************/

/**
  * @brief  SPIx Bus initialization
  * @param  None
  * @retval None
  */
static void SPIx_Init(void)
{
  if(HAL_SPI_GetState(&SpiHandle) == HAL_SPI_STATE_RESET)
  {
    /* SPI configuration -----------------------------------------------------*/
    SpiHandle.Instance = DISCOVERY_SPIx;
    /* SPI baudrate is set to 5.6 MHz (PCLK2/SPI_BaudRatePrescaler = 90/16 = 5.625 MHz) 
       to verify these constraints:
       - ILI9341 LCD SPI interface max baudrate is 10MHz for write and 6.66MHz for read
       - l3gd20 SPI interface max baudrate is 10MHz for write/read
       - PCLK2 frequency is set to 90 MHz 
    */  
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;

    /* On STM32F429I-Discovery, LCD ID cannot be read then keep a common configuration */
    /* for LCD and GYRO (SPI_DIRECTION_2LINES) */
    /* Note: To read a register a LCD, SPI_DIRECTION_1LINE should be set */
    SpiHandle.Init.Direction      = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase       = SPI_PHASE_1EDGE;
    SpiHandle.Init.CLKPolarity    = SPI_POLARITY_LOW;
    SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    SpiHandle.Init.CRCPolynomial  = 7;
    SpiHandle.Init.DataSize       = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit       = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.NSS            = SPI_NSS_SOFT;
    SpiHandle.Init.TIMode         = SPI_TIMODE_DISABLED;
    SpiHandle.Init.Mode           = SPI_MODE_MASTER;
  
    SPIx_MspInit(&SpiHandle);
    HAL_SPI_Init(&SpiHandle);
  } 
}

/**
  * @brief  Reads 4 bytes from device.
  * @param  ReadSize: Number of bytes to read (max 4 bytes)
  * @retval Value read on the SPI
  */
static uint32_t SPIx_Read(uint8_t ReadSize)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t readvalue;
  
  status = HAL_SPI_Receive(&SpiHandle, (uint8_t*) &readvalue, ReadSize, SpixTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    SPIx_Error();
  }
  
  return readvalue;
}

/**
  * @brief  Writes a byte to device.
  * @param  Value: value to be written
  * @retval None
  */
static void SPIx_Write(uint16_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_SPI_Transmit(&SpiHandle, (uint8_t*) &Value, 1, SpixTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    SPIx_Error();
  }
}

/**
  * @brief  Sends a Byte through the SPI interface and return the Byte received 
  *         from the SPI bus.
  * @param  Byte: Byte send.
  * @retval The received byte value
  */
static uint8_t SPIx_WriteRead(uint8_t Byte)
{
  uint8_t receivedbyte = 0;
  
  /* Send a Byte through the SPI peripheral */
  /* Read byte from the SPI bus */
  if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t*) &Byte, (uint8_t*) &receivedbyte, 1, SpixTimeout) != HAL_OK)
  {
    SPIx_Error();
  }
  
  return receivedbyte;
}

/**
  * @brief  SPIx error treatment function.
  * @param  None
  * @retval None
  */
static void SPIx_Error(void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&SpiHandle);
  
  /* Re- Initialize the SPI communication BUS */
  SPIx_Init();
}

/**
  * @brief  SPI MSP Init.
  * @param  hspi: SPI handle
  * @retval None
  */
static void SPIx_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable SPIx clock */
  DISCOVERY_SPIx_CLK_ENABLE();

  /* Enable DISCOVERY_SPI GPIO clock */
  DISCOVERY_SPIx_GPIO_CLK_ENABLE();

  /* configure SPI SCK, MOSI and MISO */    
  GPIO_InitStructure.Pin    = (DISCOVERY_SPIx_SCK_PIN | DISCOVERY_SPIx_MOSI_PIN | DISCOVERY_SPIx_MISO_PIN);
  GPIO_InitStructure.Mode   = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull   = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed  = GPIO_SPEED_MEDIUM;
  GPIO_InitStructure.Alternate = DISCOVERY_SPIx_AF;
  HAL_GPIO_Init(DISCOVERY_SPIx_GPIO_PORT, &GPIO_InitStructure);      
}

/********************************* LINK LCD ***********************************/

/**
  * @brief  Configures the LCD_SPI interface.
  * @param  None
  * @retval None
  */
void LCD_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  if(Is_LCD_IO_Initialized == 0)
  {
    Is_LCD_IO_Initialized = 1; 
    
    /* Configure NCS in Output Push-Pull mode */
    LCD_WRX_GPIO_CLK_ENABLE();
    GPIO_InitStructure.Pin     = LCD_WRX_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_WRX_GPIO_PORT, &GPIO_InitStructure);
    
    LCD_RDX_GPIO_CLK_ENABLE();
    GPIO_InitStructure.Pin     = LCD_RDX_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_RDX_GPIO_PORT, &GPIO_InitStructure);
    
    /* Configure the LCD Control pins ----------------------------------------*/
    LCD_NCS_GPIO_CLK_ENABLE();
    
    /* Configure NCS in Output Push-Pull mode */
    GPIO_InitStructure.Pin     = LCD_NCS_PIN;
    GPIO_InitStructure.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull    = GPIO_NOPULL;
    GPIO_InitStructure.Speed   = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LCD_NCS_GPIO_PORT, &GPIO_InitStructure);
    
    /* Set or Reset the control line */
    LCD_CS_LOW();
    LCD_CS_HIGH();
    
    SPIx_Init();
  }
}

/**
  * @brief  Writes register value.
  * @param  None
  * @retval None
  */
void LCD_IO_WriteData(uint16_t RegValue) 
{
  /* Set WRX to send data */
  LCD_WRX_HIGH();
  
  /* Reset LCD control line(/CS) and Send data */  
  LCD_CS_LOW();
  SPIx_Write(RegValue);
  
  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Writes register address.
  * @param  None
  * @retval None
  */
void LCD_IO_WriteReg(uint8_t Reg) 
{
  /* Reset WRX to send command */
  LCD_WRX_LOW();
  
  /* Reset LCD control line(/CS) and Send command */
  LCD_CS_LOW();
  SPIx_Write(Reg);
  
  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Reads register value.
  * @param  RegValue Address of the register to read
  * @param  ReadSize Number of bytes to read
  * @retval Content of the register value
  */
uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize) 
{
  uint32_t readvalue = 0;

  /* Select: Chip Select low */
  LCD_CS_LOW();

  /* Reset WRX to send command */
  LCD_WRX_LOW();
  
  SPIx_Write(RegValue);
  
  readvalue = SPIx_Read(ReadSize);

  /* Set WRX to send data */
  LCD_WRX_HIGH();

  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
  
  return readvalue;
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

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK IOE ***********************************/

/**
  * @brief  IOE Low Level Initialization.
  * @param  None
  * @retval None
  */
void IOE_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  IOE Low Level Interrupt configuration.
  * @param  None
  * @retval None
  */
void IOE_ITConfig(void)
{
  I2Cx_ITConfig();
}

/**
  * @brief  IOE Writes single data operation.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  Value: Data to be written
  * @retval None
  */
void IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteData(Addr, Reg, Value);
}

/**
  * @brief  IOE Reads single data.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @retval The read data
  */
uint8_t IOE_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_ReadData(Addr, Reg);
}

/**
  * @brief  IOE Writes multiple data.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to data buffer
  * @param  Length: length of the data
  * @retval None
  */
void IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
  I2Cx_WriteBuffer(Addr, Reg, pBuffer, Length);
}

/**
  * @brief  IOE Reads multiple data.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to data buffer
  * @param  Length: length of the data
  * @retval 0 if no problems to read multiple data
  */
uint16_t IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
 return I2Cx_ReadBuffer(Addr, Reg, pBuffer, Length);
}

/**
  * @brief  IOE Delay.
  * @param  Delay in ms
  * @retval None
  */
void IOE_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/********************************* LINK GYROSCOPE *****************************/

/**
  * @brief  Configures the Gyroscope SPI interface.
  * @param  None
  * @retval None
  */
void GYRO_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Configure the Gyroscope Control pins ------------------------------------*/
  /* Enable CS GPIO clock and Configure GPIO PIN for Gyroscope Chip select */  
  GYRO_CS_GPIO_CLK_ENABLE();  
  GPIO_InitStructure.Pin = GYRO_CS_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull  = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(GYRO_CS_GPIO_PORT, &GPIO_InitStructure);
  
  /* Deselect: Chip Select high */
  GYRO_CS_HIGH();
  
  /* Enable INT1, INT2 GPIO clock and Configure GPIO PINs to detect Interrupts */
  GYRO_INT_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = GYRO_INT1_PIN | GYRO_INT2_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull= GPIO_NOPULL;
  HAL_GPIO_Init(GYRO_INT_GPIO_PORT, &GPIO_InitStructure);

  SPIx_Init();
}

/**
  * @brief  Writes one byte to the Gyroscope.
  * @param  pBuffer: Pointer to the buffer containing the data to be written to the Gyroscope.
  * @param  WriteAdd: Gyroscope's internal address to write to.
  * @param  NumByteToWrite: Number of bytes to write.
  * @retval None
  */
void GYRO_IO_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  /* Configure the MS bit: 
       - When 0, the address will remain unchanged in multiple read/write commands.
       - When 1, the address will be auto incremented in multiple read/write commands.
  */
  if(NumByteToWrite > 0x01)
  {
    WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  GYRO_CS_LOW();
  
  /* Send the Address of the indexed register */
  SPIx_WriteRead(WriteAddr);
  
  /* Send the data that will be written into the device (MSB First) */
  while(NumByteToWrite >= 0x01)
  {
    SPIx_WriteRead(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  GYRO_CS_HIGH();
}

/**
  * @brief  Reads a block of data from the Gyroscope.
  * @param  pBuffer: Pointer to the buffer that receives the data read from the Gyroscope.
  * @param  ReadAddr: Gyroscope's internal address to read from.
  * @param  NumByteToRead: Number of bytes to read from the Gyroscope.
  * @retval None
  */
void GYRO_IO_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
  if(NumByteToRead > 0x01)
  {
    ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
  }
  else
  {
    ReadAddr |= (uint8_t)READWRITE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  GYRO_CS_LOW();
  
  /* Send the Address of the indexed register */
  SPIx_WriteRead(ReadAddr);
  
  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to Gyroscope (Slave device) */
    *pBuffer = SPIx_WriteRead(DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  GYRO_CS_HIGH();
}  


#ifdef EE_M24LR64

/******************************** LINK I2C EEPROM *****************************/

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void EEPROM_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Writes data to I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteBufferDMA(DevAddress, MemAddress,  pBuffer, BufferSize));
}

/**
  * @brief  Reads data from I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_ReadBufferDMA(DevAddress, MemAddress, pBuffer, BufferSize));
}

/**
* @brief  Checks if target device is ready for communication. 
* @note   This function is used with Memory devices
* @param  DevAddress: Target device address
* @param  Trials: Number of trials
* @retval HAL status
*/
HAL_StatusTypeDef EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (I2Cx_IsDeviceReady(DevAddress, Trials));
}
#endif /* EE_M24LR64 */

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
