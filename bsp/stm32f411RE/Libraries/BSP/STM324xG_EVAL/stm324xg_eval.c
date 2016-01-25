/**
  ******************************************************************************
  * @file    stm324xg_eval.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file provides a set of firmware functions to manage LEDs, 
  *          push-buttons and COM ports available on STM324xG-EVAL evaluation 
  *          board(MB786) RevB from STMicroelectronics.
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
  
/* File Info: ------------------------------------------------------------------
                                   User NOTE

   This driver requires the stm324xG_eval_io.c driver to manage the joystick

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm324xg_eval.h"
#include "stm324xg_eval_io.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM324xG_EVAL
  * @{
  */   
    
/** @defgroup STM324xG_EVAL_LOW_LEVEL 
  * @{
  */ 

/** @defgroup STM324xG_EVAL_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
typedef struct
{
  __IO uint16_t REG;
  __IO uint16_t RAM;
}LCD_CONTROLLER_TypeDef;
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_LOW_LEVEL_Private_Defines
  * @{
  */

/**
  * @brief STM324xG EVAL BSP Driver version number V2.1.0
  */
#define __STM324xG_EVAL_BSP_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM324xG_EVAL_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM324xG_EVAL_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM324xG_EVAL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM324xG_EVAL_BSP_VERSION         ((__STM324xG_EVAL_BSP_VERSION_MAIN << 24)\
                                             |(__STM324xG_EVAL_BSP_VERSION_SUB1 << 16)\
                                             |(__STM324xG_EVAL_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM324xG_EVAL_BSP_VERSION_RC))
                                              
#define FMC_BANK3_BASE  ((uint32_t)(0x60000000 | 0x08000000))
#define FMC_BANK3       ((LCD_CONTROLLER_TypeDef *) FMC_BANK3_BASE)

#define I2C_TIMEOUT  100 /*<! Value of Timeout when I2C communication fails */

/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_LOW_LEVEL_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, 
                                 LED2_GPIO_PORT, 
                                 LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};
                                 
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, 
                                 LED2_PIN, 
                                 LED3_PIN,
                                 LED4_PIN};
                                 

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT, 
                                      TAMPER_BUTTON_GPIO_PORT,
                                      KEY_BUTTON_GPIO_PORT}; 

const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN, 
                                      TAMPER_BUTTON_PIN,
                                      KEY_BUTTON_PIN}; 
                                             
const uint16_t BUTTON_IRQn[BUTTONn] = {WAKEUP_BUTTON_EXTI_IRQn, 
                                       TAMPER_BUTTON_EXTI_IRQn,
                                       KEY_BUTTON_EXTI_IRQn};

USART_TypeDef* COM_USART[COMn] = {EVAL_COM1}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};
 
const uint16_t COM_TX_AF[COMn] = {EVAL_COM1_TX_AF};
 
const uint16_t COM_RX_AF[COMn] = {EVAL_COM1_RX_AF};

I2C_HandleTypeDef  heval_I2c;

static uint8_t Is_LCD_IO_Initialized = 0;

/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 
static void     I2Cx_Init(void);
static void     I2Cx_ITConfig(void);
static void     I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t  I2Cx_Read(uint8_t Addr, uint8_t Reg);
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef  I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void     I2Cx_Error(uint8_t Addr);
static void     I2Cx_MspInit(void);

static void     FSMC_BANK3_WriteData(uint16_t Data);
static void     FSMC_BANK3_WriteReg(uint8_t Reg);
static uint16_t FSMC_BANK3_ReadData(void);
static void     FSMC_BANK3_Init(void);
static void     FSMC_BANK3_MspInit(void);

/* IOExpander IO functions */
void            IOE_Init(void);
void            IOE_ITConfig(void);
void            IOE_Delay(uint32_t Delay);
void            IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t        IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);

/* LCD IO functions */
void            LCD_IO_Init(void);
void            LCD_IO_WriteData(uint16_t RegValue);
void            LCD_IO_WriteReg(uint8_t Reg);
uint16_t        LCD_IO_ReadData(void);

/* AUDIO IO functions */
void            AUDIO_IO_Init(void);
void            AUDIO_IO_DeInit(void);
void            AUDIO_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         AUDIO_IO_Read(uint8_t Addr, uint8_t Reg);

/* Camera IO functions */
void            CAMERA_IO_Init(void);
void            CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         CAMERA_IO_Read(uint8_t Addr, uint8_t Reg);
void            CAMERA_Delay(uint32_t Delay);

/* I2C EEPROM IO function */
void                EEPROM_IO_Init(void);
HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM324xG EVAL BSP Driver revision
  * @param  None
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM324xG_EVAL_BSP_VERSION;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: LED to be configured. 
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable the GPIO_LED clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = GPIO_PIN[Led];
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  
  HAL_GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: LED to be set on 
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET); 
}

/**
  * @brief  Turns selected LED Off. 
  * @param  Led: LED to be set off
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: LED to be toggled
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button
  *            @arg  BUTTON_KEY: Key Push Button 
  *            @arg  BUTTON_RIGHT: Joystick Right Push Button 
  *            @arg  BUTTON_LEFT: Joystick Left Push Button 
  *            @arg  BUTTON_UP: Joystick Up Push Button 
  *            @arg  BUTTON_DOWN: Joystick Down Push Button
  *            @arg  BUTTON_SEL: Joystick Sel Push Button
  * @param  Button_Mode: Button mode
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *            @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line 
  *                                    with interrupt generation capability  
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if(Button_Mode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  if(Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    
    if(Button != BUTTON_WAKEUP)
    {
      GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; 
    }
    else
    {
      GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    }
    
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Returns the selected button state.
  * @param  Button: Button to be checked
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button 
  *            @arg  BUTTON_KEY: Key Push Button
  *            @arg BUTTON_RIGHT: Joystick Right Push Button 
  *            @arg BUTTON_LEFT: Joystick Left Push Button 
  *            @arg BUTTON_UP: Joystick Up Push Button 
  *            @arg BUTTON_DOWN: Joystick Down Push Button
  *            @arg BUTTON_SEL: Joystick Sel Push Button  
  * @retval The Button GPIO pin value
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Configures COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1 
  *            @arg  COM2 
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  * @retval None
  */
void BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable GPIO clock */
  EVAL_COMx_TX_GPIO_CLK_ENABLE(COM);
  EVAL_COMx_RX_GPIO_CLK_ENABLE(COM);
  
  /* Enable USART clock */
  EVAL_COMx_CLK_ENABLE(COM);
  
  /* Configure USART Tx as alternate function */
  GPIO_InitStruct.Pin = COM_TX_PIN[COM];
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Alternate = COM_TX_AF[COM];
  HAL_GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStruct);
  
  /* Configure USART Rx as alternate function */
  GPIO_InitStruct.Pin = COM_RX_PIN[COM];
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Alternate = COM_RX_AF[COM];
  HAL_GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStruct);
  
  /* USART configuration */
  huart->Instance = COM_USART[COM];
  HAL_UART_Init(huart);
}

/**
  * @brief  Configures joystick GPIO and EXTI modes.
  * @param  Joy_Mode: Button mode.
  *          This parameter can be one of the following values:
  *            @arg  JOY_MODE_GPIO: Joystick pins will be used as simple IOs
  *            @arg  JOY_MODE_EXTI: Joystick pins will be connected to EXTI line 
  *                                 with interrupt generation capability  
  * @retval IO_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_JOY_Init(JOYMode_TypeDef Joy_Mode)
{
  uint8_t ret = 0;
  
  /* Initialize the IO functionalities */
  ret = BSP_IO_Init();
  
  /* Configure joystick pins in IT mode */
  if(Joy_Mode == JOY_MODE_EXTI)
  {
    /* Configure joystick pins in IT mode */
    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_IT_FALLING_EDGE);
  }
  
  return ret; 
}

/**
  * @brief  Returns the current joystick status.
  * @param  None
  * @retval Code of the joystick key pressed
  *          This code can be one of the following values:
  *            @arg  JOY_NONE
  *            @arg  JOY_SEL
  *            @arg  JOY_DOWN
  *            @arg  JOY_LEFT
  *            @arg  JOY_RIGHT
  *            @arg  JOY_UP
  */
JOYState_TypeDef BSP_JOY_GetState(void)
{
  uint8_t tmp = 0;   
  
  /* Read the status joystick pins */
  tmp = (uint8_t)BSP_IO_ReadPin(JOY_ALL_PINS);
  
  /* Check the pressed keys */  
  if((tmp & JOY_NONE_PIN) == JOY_NONE)
  {
    return(JOYState_TypeDef) JOY_NONE;
  }
  else if(!(tmp & JOY_SEL_PIN))
  {
    return(JOYState_TypeDef) JOY_SEL;
  }
  else if(!(tmp & JOY_DOWN_PIN))
  {
    return(JOYState_TypeDef) JOY_DOWN;
  } 
  else if(!(tmp & JOY_LEFT_PIN))
  {
    return(JOYState_TypeDef) JOY_LEFT;
  }
  else if(!(tmp & JOY_RIGHT_PIN))
  {
    return(JOYState_TypeDef) JOY_RIGHT;
  }
  else if(!(tmp & JOY_UP_PIN))
  {
    return(JOYState_TypeDef) JOY_UP;
  }
  else
  { 
    return(JOYState_TypeDef) JOY_NONE;
  }  
}

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/**************************** I2C Routines ************************************/

/**
  * @brief  Initializes I2C MSP.
  * @param  None
  * @retval None
  */
static void I2Cx_MspInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;  
  
  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();
  
  /* Configure I2C Tx as alternate function */
  GPIO_InitStruct.Pin = EVAL_I2Cx_SCL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = EVAL_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &GPIO_InitStruct);
  
  /* Configure I2C Rx as alternate function */
  GPIO_InitStruct.Pin = EVAL_I2Cx_SDA_PIN;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &GPIO_InitStruct);
  
  /*** Configure the I2C peripheral ***/ 
  /* Enable I2C clock */
  EVAL_I2Cx_CLK_ENABLE();
  
  /* Force the I2C peripheral clock reset */
  EVAL_I2Cx_FORCE_RESET(); 
  
  /* Release the I2C peripheral clock reset */
  EVAL_I2Cx_RELEASE_RESET(); 
  
  /* Set priority and enable I2Cx event Interrupt */
  HAL_NVIC_SetPriority(EVAL_I2Cx_EV_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_EV_IRQn);
  
  /* Set priority and enable I2Cx error Interrupt */
  HAL_NVIC_SetPriority(EVAL_I2Cx_ER_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_ER_IRQn);
}

/**
  * @brief  Initializes I2C HAL.
  * @param  None
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&heval_I2c) == HAL_I2C_STATE_RESET)
  {
    heval_I2c.Instance = EVAL_I2Cx;
    heval_I2c.Init.ClockSpeed      = BSP_I2C_SPEED;
    heval_I2c.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    heval_I2c.Init.OwnAddress1     = 0;
    heval_I2c.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    heval_I2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    heval_I2c.Init.OwnAddress2     = 0;
    heval_I2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    heval_I2c.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLED;  

    /* Init the I2C */
    I2Cx_MspInit();
    HAL_I2C_Init(&heval_I2c);
  }
}

/**
  * @brief  Configures I2C Interrupt.
  * @param  None 
  * @retval None
  */
static void I2Cx_ITConfig(void)
{
  static uint8_t I2C_IT_Enabled = 0;  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  if(I2C_IT_Enabled == 0)
  {
    I2C_IT_Enabled = 1;  
    
    /* Enable the GPIO EXTI clock */
    __GPIOI_CLK_ENABLE();
    __SYSCFG_CLK_ENABLE();
    
    GPIO_InitStruct.Pin   = GPIO_PIN_2;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
    
    /* Set priority and Enable GPIO EXTI Interrupt */
    HAL_NVIC_SetPriority((IRQn_Type)(EXTI2_IRQn), 5, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI2_IRQn));
  }
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Data to be read
  */
static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;
  
  status = HAL_I2C_Mem_Read(&heval_I2c, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2C_TIMEOUT);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
  
  return Value;   
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  * @retval None
  */
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&heval_I2c, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2C_TIMEOUT); 
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occured */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Read(&heval_I2c, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, I2C_TIMEOUT);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occured */
    I2Cx_Error(Addr);
  }
  return status;    
}

/**
  * @brief  Write a value in a register of the device through BUS in using DMA mode
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&heval_I2c, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, I2C_TIMEOUT);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(Addr);
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
  return (HAL_I2C_IsDeviceReady(&heval_I2c, DevAddress, Trials, I2C_TIMEOUT));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the IOE comunication BUS */
  HAL_I2C_DeInit(&heval_I2c);
  
  /* Re-Initiaize the IOE comunication BUS */
  I2Cx_Init();  
}

/*************************** FSMC Routines ************************************/
/**
  * @brief  Initializes FSMC_BANK3 MSP.
  * @param  None
  * @retval None
  */
static void FSMC_BANK3_MspInit(void)
{
  GPIO_InitTypeDef GPIO_Init_Structure;
    
  /* Enable FSMC clock */
  __FSMC_CLK_ENABLE();

  /* Enable GPIOs clock */
  __GPIOD_CLK_ENABLE();
  __GPIOE_CLK_ENABLE();
  __GPIOF_CLK_ENABLE();
  __GPIOG_CLK_ENABLE();
  
  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_HIGH;
  GPIO_Init_Structure.Alternate = GPIO_AF12_FSMC;
  
  /* GPIOD configuration */
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8     |\
                              GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |\
                              GPIO_PIN_14 | GPIO_PIN_15;
   
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* GPIOE configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3| GPIO_PIN_4 | GPIO_PIN_7     |\
                              GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
                              GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);
  
  /* GPIOF configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);
  
  /* GPIOG configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_10;
  
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);  
}

/**
  * @brief  Initializes LCD IO.
  * @param  None
  * @retval None
  */
static void FSMC_BANK3_Init(void) 
{  
  SRAM_HandleTypeDef hsram;
  FSMC_NORSRAM_TimingTypeDef SRAM_Timing;
  
  /*** Configure the SRAM Bank 3 ***/  
  /* Configure IPs */
  hsram.Instance  = FMC_NORSRAM_DEVICE;
  hsram.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;

  SRAM_Timing.AddressSetupTime      = 5;
  SRAM_Timing.AddressHoldTime       = 1;
  SRAM_Timing.DataSetupTime         = 9;
  SRAM_Timing.BusTurnAroundDuration = 0;
  SRAM_Timing.CLKDivision           = 2;
  SRAM_Timing.DataLatency           = 2;
  SRAM_Timing.AccessMode            = FSMC_ACCESS_MODE_A;
  
  hsram.Init.NSBank             = FSMC_NORSRAM_BANK3;
  hsram.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;
  hsram.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram.Init.WrapMode           = FSMC_WRAP_MODE_DISABLE;
  hsram.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
  hsram.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
  hsram.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;
  hsram.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram.Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE;

  /* Initialize the SRAM controller */
  FSMC_BANK3_MspInit();
  HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing);   
}

/**
  * @brief  Writes register value.
  * @param  Data: Data to be written 
  * @retval None
  */
static void FSMC_BANK3_WriteData(uint16_t Data) 
{
  /* Write 16-bit Reg */
  FMC_BANK3->RAM = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg: Register to be written
  * @retval None
  */
static void FSMC_BANK3_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Index, then write register */
  FMC_BANK3->REG = Reg;
}

/**
  * @brief  Reads register value.
  * @param  None
  * @retval Read value
  */
static uint16_t FSMC_BANK3_ReadData(void) 
{
  return FMC_BANK3->RAM;
}

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/***************************** LINK IOE ***************************************/

/**
  * @brief  Initializes IOE low level.
  * @param  None
  * @retval None
  */
void IOE_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  Configures IOE low level Interrupt.
  * @param  None
  * @retval None
  */
void IOE_ITConfig(void)
{
  I2Cx_ITConfig();
}

/**
  * @brief  IOE writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  * @retval None
  */
void IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  IOE reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Read data
  */
uint8_t IOE_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  IOE reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(Addr, Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  IOE delay. 
  * @param  Delay: Delay in ms
  * @retval None
  */
void IOE_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/********************************* LINK LCD ***********************************/

/**
  * @brief  Initializes LCD low level.
  * @param  None
  * @retval None
  */
void LCD_IO_Init(void) 
{
  if(Is_LCD_IO_Initialized == 0)
  {
    Is_LCD_IO_Initialized = 1; 
    FSMC_BANK3_Init();
  }
}

/**
  * @brief  Writes data on LCD data register.
  * @param  Data: Data to be written
  * @retval None
  */
void LCD_IO_WriteData(uint16_t Data) 
{
  /* Write 16-bit Reg */
  FSMC_BANK3_WriteData(Data);
}

/**
  * @brief  Writes register on LCD register.
  * @param  Reg: Register to be written
  * @retval None
  */
void LCD_IO_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Index, then Write Reg */
  FSMC_BANK3_WriteReg(Reg);
}

/**
  * @brief  Reads data from LCD data register.
  * @param  None
  * @retval Read data.
  */
uint16_t LCD_IO_ReadData(void) 
{
  return FSMC_BANK3_ReadData();
}

/********************************* LINK AUDIO *********************************/
/**
  * @brief  Initializes Audio low level.
  * @param  None
  * @retval None
  */
void AUDIO_IO_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  DeInitializes Audio low level.
  */
void AUDIO_IO_DeInit(void)
{

}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  * @retval None
  */
void AUDIO_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Data to be read
  */
uint8_t AUDIO_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);  
}

/***************************** LINK CAMERA ************************************/

/**
  * @brief  Initializes Camera low level.
  * @param  None
  * @retval None
  */
void CAMERA_IO_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  Camera writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  * @retval None
  */
void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Read data
  */
uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Camera delay. 
  * @param  Delay: Delay in ms
  * @retval None
  */
void CAMERA_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

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
  * @brief Write data to I2C EEPROM driver in using DMA channel
  * @param DevAddress: Target device address
  * @param MemAddress: Internal memory address
  * @param pBuffer: Pointer to data buffer
  * @param BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
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
  return (I2Cx_ReadMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
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
