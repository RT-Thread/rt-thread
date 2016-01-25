/**
  ******************************************************************************
  * @file    stm32469i_eval.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides a set of firmware functions to manage LEDs,
  *          push-buttons and COM ports available on STM32469I-EVAL evaluation
  *          board(MB1165) RevA/B from STMicroelectronics.
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

   This driver requires the stm32469i_eval_io to manage the joystick

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32469i_eval.h"
#if defined(USE_IOEXPANDER)
#include "stm32469i_eval_io.h"
#endif /* USE_IOEXPANDER */

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_EVAL
  * @{
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL STM32469I-EVAL LOW LEVEL
  * @{
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Private_TypesDefinitions STM32469I Eval Low Level Private Typedef
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Private_Defines LOW_LEVEL Private Defines
  * @{
  */
/**
 * @brief STM32469I EVAL BSP Driver version number V1.0.1
   */
#define __STM32469I_EVAL_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32469I_EVAL_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32469I_EVAL_BSP_VERSION_SUB2   (0x01) /*!< [15:8]  sub2 version */
#define __STM32469I_EVAL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32469I_EVAL_BSP_VERSION        ((__STM32469I_EVAL_BSP_VERSION_MAIN << 24)\
                                            |(__STM32469I_EVAL_BSP_VERSION_SUB1 << 16)\
                                            |(__STM32469I_EVAL_BSP_VERSION_SUB2 << 8 )\
                                            |(__STM32469I_EVAL_BSP_VERSION_RC))
/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Private_Macros  LOW_LEVEL Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Private_Variables LOW_LEVEL Private Variables
  * @{
  */
const uint32_t GPIO_PIN[LEDn] = {LED1_PIN,
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

static I2C_HandleTypeDef heval_I2c;

/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Private_FunctionPrototypes LOW_LEVEL Private FunctionPrototypes
  * @{
  */
static void          I2Cx_MspInit(void);
static void          I2Cx_Init(void);
static void          I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t       I2Cx_Read(uint8_t Addr, uint8_t Reg);     
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void              I2Cx_Error(uint8_t Addr);

/* IOExpander IO functions */
void            IOE_Init(void);
void            IOE_ITConfig(void);
void            IOE_Delay(uint32_t Delay);
void            IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t        IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void            IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);

#if defined(USE_IOEXPANDER)
/* MFX IO functions */
void              MFX_IO_Init(void);
void              MFX_IO_DeInit(void);
void              MFX_IO_ITConfig(void);
void              MFX_IO_Delay(uint32_t Delay);
void              MFX_IO_Write(uint16_t Addr, uint8_t Reg, uint8_t Value);
uint8_t           MFX_IO_Read(uint16_t Addr, uint8_t Reg);
uint16_t          MFX_IO_ReadMultiple(uint16_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void              MFX_IO_Wakeup(void);
void              MFX_IO_EnableWakeupPin(void);
#endif /* USE_IOEXPANDER */

/* AUDIO IO functions */
void              AUDIO_IO_Init(void);
void              AUDIO_IO_DeInit(void);
void              AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint16_t          AUDIO_IO_Read(uint8_t Addr, uint16_t Reg);
void              AUDIO_IO_Delay(uint32_t Delay);

/* CAMERA IO functions */
void              CAMERA_IO_Init(void);
void              CAMERA_Delay(uint32_t Delay);
void              CAMERA_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint16_t          CAMERA_IO_Read(uint8_t Addr, uint16_t Reg);

/* I2C EEPROM IO function */
void                EEPROM_IO_Init(void);
HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);

/* TouchScreen (TS) IO functions */
void         TS_IO_Init(void);
void         TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t      TS_IO_Read(uint8_t Addr, uint8_t Reg);
uint16_t     TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void         TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void         TS_IO_Delay(uint32_t Delay);

void OTM8009A_IO_Delay(uint32_t Delay);
/**
  * @}
  */

/** @defgroup STM32469I_EVAL_BSP_Public_Functions BSP Public Functions
  * @{
  */

  /**
  * @brief  This method returns the STM32469I EVAL BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32469I_EVAL_BSP_VERSION;
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
#if !defined(USE_STM32469I_EVAL_REVA)
/* Eval Rev B and beyond : leds are directly connected to MCU o PK3, 4, 5, 6 */
  GPIO_InitTypeDef  gpio_init_structure;

  /* On RevB LED1, LED2, LED3 and LED4 are on GPIO */
  if (Led <= LED4)
  {
    /* Enable the GPIO_LED clock */
    LEDx_GPIO_CLK_ENABLE();

    /* Configure the GPIO_LED pin */
    gpio_init_structure.Pin   = GPIO_PIN[Led];
    gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull  = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  
    HAL_GPIO_Init(LEDx_GPIO_PORT, &gpio_init_structure);
    
    /* By default, turn off LED by setting a high level on corresponding GPIO */
    HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_SET);
  }
#else
#if defined(USE_IOEXPANDER)  /* (USE_IOEXPANDER always defined for RevA) */
  /* Initialize the IO functionalities */
  BSP_IO_Init();

  /* the output mode choices shall be extended to PushPull / PullUp*/
  BSP_IO_ConfigPin(GPIO_PIN[Led], IO_MODE_OUTPUT_PP_PU);

  BSP_IO_WritePin(GPIO_PIN[Led], BSP_IO_PIN_SET);
#endif /* USE_IOEXPANDER */     
#endif /* USE_STM32469I_EVAL_REVA */     
}


/**
  * @brief  DeInit LEDs.
  * @param  Led: LED to be configured. 
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @note Led DeInit does not disable the GPIO clock nor disable the Mfx 
  * @retval None
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
#if !defined(USE_STM32469I_EVAL_REVA)
/* Eval Rev B and beyond */
  GPIO_InitTypeDef  gpio_init_structure;

  /* On RevB LED1 LED2 LED3 and LED4 are on GPIO PK3, 4, 5, 6 */
  if (Led <= LED4)
  {
    /* Turn off LED */
    HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_RESET);
    /* DeInit the GPIO_LED pin */
    gpio_init_structure.Pin = GPIO_PIN[Led];
    HAL_GPIO_DeInit(LEDx_GPIO_PORT, gpio_init_structure.Pin);
  }
#else
#if defined(USE_IOEXPANDER)   /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
    BSP_IO_ConfigPin(GPIO_PIN[Led], IO_MODE_OFF);
#endif /* USE_IOEXPANDER */     
#endif /* USE_STM32469I_EVAL_REVA */     
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
#if !defined(USE_STM32469I_EVAL_REVA)
  /* Eval Rev B and beyond */
  /* On RevB LED1 LED2 LED3 and LED4 are on GPIO PK3, 4, 5, 6 */
  if (Led <= LED4)
  {
     HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_RESET);
  }
#else
#if defined(USE_IOEXPANDER) /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
  BSP_IO_WritePin(GPIO_PIN[Led], BSP_IO_PIN_RESET);
#endif /* USE_IOEXPANDER */     
#endif /* USE_STM32469I_EVAL_REVA */     

}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: LED to be set off
  *         This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
#if !defined(USE_STM32469I_EVAL_REVA)
  /* Eval Rev B and beyond */
  /* On RevB LED1 LED2 LED3 and LED4 are on GPIO PK3, 4, 5, 6 */
  if (Led <= LED4)
  {
     HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_SET);
  }
#else
#if defined(USE_IOEXPANDER) /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
  BSP_IO_WritePin(GPIO_PIN[Led], BSP_IO_PIN_SET);
#endif /* USE_IOEXPANDER */     
#endif /* USE_STM32469I_EVAL_REVA */     
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
#if !defined(USE_STM32469I_EVAL_REVA)
  /* Eval Rev B and beyond */
  /* On RevB LED1 LED2 LED3 and LED4 are on GPIO PK3, 4, 5, 6 */
  if (Led <= LED4)
  {
     HAL_GPIO_TogglePin(LEDx_GPIO_PORT, GPIO_PIN[Led]);
  }
#else
#if defined(USE_IOEXPANDER) /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
  BSP_IO_TogglePin(GPIO_PIN[Led]);
#endif /* USE_IOEXPANDER */     
#endif /* USE_STM32469I_EVAL_REVA */     
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button
  *            @arg  BUTTON_TAMPER: Tamper Push Button
  * @param  Button_Mode: Button mode
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *            @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                                    with interrupt generation capability
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef gpio_init_structure;
  
  /* Enable the BUTTON clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  if(Button_Mode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    gpio_init_structure.Mode = GPIO_MODE_INPUT;
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);
  }

  if(Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;

    if(Button != BUTTON_WAKEUP)
    {
      gpio_init_structure.Mode = GPIO_MODE_IT_FALLING;
    }
    else
    {
      gpio_init_structure.Mode = GPIO_MODE_IT_RISING;
    }

    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button  
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
  * @brief  Returns the selected button state.
  * @param  Button: Button to be checked
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button
  *            @arg  BUTTON_TAMPER: Tamper Push Button
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
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock of GPIO port supporting COM_TX and COM_RX pins */
  EVAL_COMx_TX_RX_GPIO_CLK_ENABLE(COM);

  /* Enable USART clock */
  EVAL_COMx_CLK_ENABLE(COM);

  /* Configure USART Tx as alternate function */
  gpio_init_structure.Pin = COM_TX_PIN[COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = COM_TX_AF[COM];
  HAL_GPIO_Init(COM_TX_PORT[COM], &gpio_init_structure);

  /* Configure USART Rx as alternate function */
  gpio_init_structure.Pin = COM_RX_PIN[COM];
  HAL_GPIO_Init(COM_RX_PORT[COM], &gpio_init_structure);

  /* USART configuration */
  huart->Instance = COM_USART[COM];
  HAL_UART_Init(huart);
}

/**
  * @brief  DeInit COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1 
  *            @arg  COM2 
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  * @retval None
  */
void BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart)
{
  /* USART configuration */
  huart->Instance = COM_USART[COM];
  HAL_UART_DeInit(huart);

  /* Enable USART clock */
  EVAL_COMx_CLK_DISABLE(COM);

  /* DeInit GPIO pins can be done in the application 
     (by surcharging this __weak function) */

  /* GPOI pins clock, FMC clock and DMA clock can be shut down in the applic 
     by surcgarging this __weak function */ 
}
#if defined(USE_IOEXPANDER)

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
    /* Configure IO interrupt acquisition mode */
    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_IT_LOW_LEVEL_PU);
  }
  else
  {
    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_INPUT_PU);
  }

  return ret;
}


/**
  * @brief  DeInit joystick GPIOs.
  * @note   JOY DeInit does not disable the Mfx, just set the Mfx pins in Off mode
  */
void BSP_JOY_DeInit()
{
    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_OFF);
}

/**
  * @brief  Returns the current joystick status.
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
  uint16_t pin_status = 0;   
  
  /* Read the status joystick pins */
  pin_status = BSP_IO_ReadPin(JOY_ALL_PINS);
   
  /* Check the pressed keys */  
  if((pin_status & JOY_NONE_PIN) == JOY_NONE)
  {
    return(JOYState_TypeDef) JOY_NONE;
  }
  else if(!(pin_status & JOY_SEL_PIN))
  {
    return(JOYState_TypeDef) JOY_SEL;
  }
  else if(!(pin_status & JOY_DOWN_PIN))
  {
    return(JOYState_TypeDef) JOY_DOWN;
  } 
  else if(!(pin_status & JOY_LEFT_PIN))
  {
    return(JOYState_TypeDef) JOY_LEFT;
  }
  else if(!(pin_status & JOY_RIGHT_PIN))
  {
    return(JOYState_TypeDef) JOY_RIGHT;
  }
  else if(!(pin_status & JOY_UP_PIN))
  {
    return(JOYState_TypeDef) JOY_UP;
  }
  else
  {
    return(JOYState_TypeDef) JOY_NONE;
  }
}
#endif /* USE_IOEXPANDER */

/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Private_Functions STM32469I_EVAL_LOW_LEVEL Private Functions
  * @{
  */


/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/
/**
  * @brief  Initializes I2C MSP.
  */
static void I2Cx_MspInit(void)
{
  GPIO_InitTypeDef  gpio_init_structure;  
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();

  /* Configure I2C Tx as alternate function */
  gpio_init_structure.Pin = EVAL_I2Cx_SCL_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = EVAL_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /* Configure I2C Rx as alternate function */
  gpio_init_structure.Pin = EVAL_I2Cx_SDA_PIN;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /*** Configure the I2C peripheral ***/
  /* Enable I2C clock */
  EVAL_I2Cx_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  EVAL_I2Cx_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  EVAL_I2Cx_RELEASE_RESET();

  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(EVAL_I2Cx_EV_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_EV_IRQn);

  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(EVAL_I2Cx_ER_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_ER_IRQn);
}

/**
  * @brief  Initializes I2C HAL.
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&heval_I2c) == HAL_I2C_STATE_RESET)
  {
    heval_I2c.Instance = I2C1;
    heval_I2c.Init.ClockSpeed      = I2C_SCL_FREQ_KHZ;
    heval_I2c.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    heval_I2c.Init.OwnAddress1     = 0;
    heval_I2c.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    heval_I2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    heval_I2c.Init.OwnAddress2     = 0;
    heval_I2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    heval_I2c.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    /* Init the I2C */
    I2Cx_MspInit();
    HAL_I2C_Init(&heval_I2c);
  }
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&heval_I2c,
                         Addr,
                         (uint16_t)Reg,
                         I2C_MEMADD_SIZE_8BIT,
                         &Value,
                         1,
                         100);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;

  status = HAL_I2C_Mem_Read(&heval_I2c,
                        Addr,
                        Reg,
                        I2C_MEMADD_SIZE_8BIT,
                        &Value,
                        1,
                        1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
  return Value;
}    

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress: memory address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr,
                                       uint16_t Reg,
                                       uint16_t MemAddress,
                                       uint8_t *Buffer,
                                       uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&heval_I2c,
                        Addr,
                        (uint16_t)Reg,
                        MemAddress,
                        Buffer,
                        Length,
                        1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occured */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  MemAddress: memory address
  * @param  Buffer: The target register value to be written
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr,
                                        uint16_t Reg,
                                        uint16_t MemAddress,
                                        uint8_t *Buffer,
                                        uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&heval_I2c,
                         Addr,
                         (uint16_t)Reg,
                         MemAddress,
                         Buffer,
                         Length,
                         1000);

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
  return (HAL_I2C_IsDeviceReady(&heval_I2c, DevAddress, Trials, 1000));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the I2C comunication bus */
  HAL_I2C_DeInit(&heval_I2c);

  /* Re-Initiaize the I2C comunication bus */
  I2Cx_Init();
}

/**
  * @}
  */

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK IOE ***********************************/

/**
  * @brief  Initializes IOE low level.
  */
void IOE_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Configures IOE low level interrupt.
  */
void IOE_ITConfig(void)
{
  static uint8_t IOE_IT_Enabled = 0;
  /* GPIO_InitTypeDef  GPIO_InitStruct; */

  if(IOE_IT_Enabled == 0)
  {
    IOE_IT_Enabled = 1;

    /* to be implemented */
  }
}

/**
  * @brief  IOE writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
void IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  IOE reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
uint8_t IOE_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  IOE reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  IOE writes multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  */
void IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
  I2Cx_WriteMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  IOE delay
  * @param  Delay: Delay in ms
  */
void IOE_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

#if defined(USE_IOEXPANDER)

/********************************* LINK MFX ***********************************/

/**
  * @brief  Initializes MFX low level.
  */
void MFX_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  DeInitializes MFX low level.
  */
void MFX_IO_DeInit(void)
{
}

/**
  * @brief  Configures MFX low level interrupt.
  */
void MFX_IO_ITConfig(void)
{
  static uint8_t MFX_IO_IT_Enabled = 0;
  GPIO_InitTypeDef  gpio_init_structure;

  if(MFX_IO_IT_Enabled == 0)
  {
    MFX_IO_IT_Enabled = 1;
    /* Enable the GPIO EXTI clock */
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    gpio_init_structure.Pin   = GPIO_PIN_8;
    gpio_init_structure.Pull  = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_LOW;
    gpio_init_structure.Mode  = GPIO_MODE_IT_RISING;
    HAL_GPIO_Init(GPIOI, &gpio_init_structure);

    /* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(EXTI9_5_IRQn), 0x0F, 0x0F);
    HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI9_5_IRQn));
  }
}

/**
  * @brief  MFX writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
void MFX_IO_Write(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write((uint8_t) Addr, Reg, Value);
}

/**
  * @brief  MFX reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
uint8_t MFX_IO_Read(uint16_t Addr, uint8_t Reg)
{
  return I2Cx_Read((uint8_t) Addr, Reg);
}

/**
  * @brief  MFX reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t MFX_IO_ReadMultiple(uint16_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple((uint8_t)Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  MFX delay
  * @param  Delay: Delay in ms
  */
void MFX_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
  * @brief  Used by Lx family but requested for MXF component compatibility.
  */
void MFX_IO_Wakeup(void) 
{
}

/**
  * @brief  Used by Lx family but requested for MXF component compatibility.
  */
void MFX_IO_EnableWakeupPin(void) 
{
}

#endif /* USE_IOEXPANDER */

/********************************* LINK AUDIO *********************************/

/**
  * @brief  Initializes Audio low level.
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
  */
void AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value)
{
  uint16_t tmp = Value;

  Value = ((uint16_t)(tmp >> 8) & 0x00FF);

  Value |= ((uint16_t)(tmp << 8)& 0xFF00);

  I2Cx_WriteMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 2);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Data to be read
  */
uint16_t AUDIO_IO_Read(uint8_t Addr, uint16_t Reg)
{
  uint16_t read_value = 0, tmp = 0;

  I2Cx_ReadMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 2);

  tmp = ((uint16_t)(read_value >> 8) & 0x00FF);

  tmp |= ((uint16_t)(read_value << 8)& 0xFF00);

  read_value = tmp;

  return read_value;
}

/**
  * @brief  AUDIO Codec delay
  * @param  Delay: Delay in ms
  */
void AUDIO_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/********************************* LINK CAMERA ********************************/

/**
  * @brief  Initializes Camera low level.
  */
void CAMERA_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Camera writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
void CAMERA_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value)
{
  uint16_t tmp = Value;
  /* For S5K5CAG sensor, 16 bits accesses are used */
  Value = ((uint16_t)(tmp >> 8) & 0x00FF);
  Value |= ((uint16_t)(tmp << 8)& 0xFF00);
  I2Cx_WriteMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 2);
}

/**
  * @brief  Camera reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
uint16_t CAMERA_IO_Read(uint8_t Addr, uint16_t Reg)
{
  uint16_t read_value = 0, tmp = 0;
  /* For S5K5CAG sensor, 16 bits accesses are used */
  I2Cx_ReadMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 2);
  tmp = ((uint16_t)(read_value >> 8) & 0x00FF);
  tmp |= ((uint16_t)(read_value << 8)& 0xFF00);
  read_value = tmp;

  return read_value;
}

/**
  * @brief  Camera delay
  * @param  Delay: Delay in ms
  */
void CAMERA_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/******************************** LINK I2C EEPROM *****************************/

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  */
void EEPROM_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Write data to I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Read data from I2C EEPROM driver in using DMA channel.
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

/******************************** LINK TS (TouchScreen) *****************************/

/**
  * @brief  Initialize I2C communication
  *         channel from MCU to TouchScreen (TS).
  */
void TS_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Writes single data with I2C communication
  *         channel from MCU to TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
void TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Reads single data with I2C communication
  *         channel from TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
uint8_t TS_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Reads multiple data with I2C communication
  *         channel from TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  Writes multiple data with I2C communication
  *         channel from MCU to TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval None
  */
void TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
  I2Cx_WriteMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  Delay function used in TouchScreen low level driver.
  * @param  Delay: Delay in ms
  * @retval None
  */
void TS_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**************************** LINK OTM8009A (Display driver) ******************/
/**
  * @brief  OTM8009A delay
  * @param  Delay: Delay in ms
  */
void OTM8009A_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
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
