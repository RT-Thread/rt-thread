/**
  ******************************************************************************
  * @file    stm32446e_eval.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    14-August-2015
  * @brief   This file provides a set of firmware functions to manage LEDs, 
  *          push-buttons and COM ports available on STM32446E-EVAL evaluation
  *          board(MB1045) RevB from STMicroelectronics.
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

   This driver requires the stm32446e_eval_io to manage the joystick

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32446e_eval.h"
#if defined(USE_IOEXPANDER)
#include "stm32446e_eval_io.h"
#endif /* USE_IOEXPANDER */


/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32446E_EVAL
  * @{
  */

/** @defgroup STM32446E_EVAL_LOW_LEVEL STM32446E-EVAL LOW LEVEL
  * @{
  */

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Private_TypesDefinitions STM32446E Eval Low Level Private Typedef
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

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Private_Defines STM32446E Eval Low Level Private Def
  * @{
  */
/**
 * @brief STM32446E EVAL BSP Driver version number V1.1.0
   */
#define __STM32446E_EVAL_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32446E_EVAL_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM32446E_EVAL_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32446E_EVAL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32446E_EVAL_BSP_VERSION         ((__STM32446E_EVAL_BSP_VERSION_MAIN << 24)\
                                             |(__STM32446E_EVAL_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32446E_EVAL_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32446E_EVAL_BSP_VERSION_RC))
											                                    
/* compared to F4xG we use BANK1 rather then BANK3 since we use FMC_NE1 signal (not FMC_NE3) */																				
#define FMC_BANK1_BASE  ((uint32_t)(0x60000000 | 0x00000000))  
#define FMC_BANK3_BASE  ((uint32_t)(0x60000000 | 0x08000000))  
#define FMC_BANK1       ((LCD_CONTROLLER_TypeDef *) FMC_BANK1_BASE)

/**
  * @}
  */

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Private_Macros STM32446E Eval Low Level Private Macro
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Private_Variables STM32446E Eval Low Level Variables 
  * @{
  */

#if defined(USE_IOEXPANDER)
const uint32_t GPIO_PIN[LEDn] = {LED1_PIN,
                                 LED2_PIN,
                                 LED3_PIN,
                                 LED4_PIN};
#else
const uint32_t GPIO_PIN[LEDn] = {LED1_PIN,
                                 LED3_PIN};
#endif /* USE_IOEXPANDER */


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

static FMPI2C_HandleTypeDef hEvalI2c;

/**
  * @}
  */

/** @defgroup STM32446E_EVAL_LOW_LEVEL_Private_FunctionPrototypes STM32446E Eval Low Level Private Prototypes
  * @{
  */
static void     I2Cx_MspInit(void);
static void     I2Cx_Init(void);
#if defined(USE_IOEXPANDER)
static void     I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t  I2Cx_Read(uint8_t Addr, uint8_t Reg);
#endif /* USE_IOEXPANDER */     

static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void     I2Cx_Error(uint8_t Addr);

static void     FMC_BANK1_WriteData(uint16_t Data);
static void     FMC_BANK1_WriteReg(uint8_t Reg);
static uint16_t FMC_BANK1_ReadData(void);
static void     FMC_BANK1_Init(void);
static void     FMC_BANK1_MspInit(void);

/* IOExpander IO functions */
#if defined(USE_IOEXPANDER)
void            MFX_IO_Init(void);
void            MFX_IO_DeInit(void);
void            MFX_IO_ITConfig(void);
void            MFX_IO_Delay(uint32_t Delay);
void            MFX_IO_Write(uint16_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         MFX_IO_Read(uint16_t Addr, uint8_t Reg);
uint16_t        MFX_IO_ReadMultiple(uint16_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void            MFX_IO_Wakeup(void);
void            MFX_IO_EnableWakeupPin(void);
#endif /* USE_IOEXPANDER */

/* LCD IO functions */
void            LCD_IO_Init(void);
void            LCD_IO_WriteData(uint16_t RegValue);
void            LCD_IO_WriteReg(uint8_t Reg);
uint16_t        LCD_IO_ReadData(void);

/* AUDIO IO functions */
void            AUDIO_IO_Init(void);
void            AUDIO_IO_DeInit(void);
void            AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint16_t        AUDIO_IO_Read(uint8_t Addr, uint16_t Reg);
void            AUDIO_IO_Delay(uint32_t Delay);

/* CAMERA IO functions */
void            CAMERA_IO_Init(void);
void            CAMERA_Delay(uint32_t Delay);
void            CAMERA_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint16_t        CAMERA_IO_Read(uint8_t Addr, uint16_t Reg);

/* I2C EEPROM IO function */
void                EEPROM_IO_Init(void);
HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);


/**
  * @}
  */
    


/** @defgroup STM32446E_EVAL_LOW_LEVEL_Private_Functions STM32446E Eval Low Level Private Functions
  * @{
  */ 

  /**
  * @brief  This method returns the STM32446E EVAL BSP Driver revision
  * @param  None
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32446E_EVAL_BSP_VERSION;
}

/**
  * @brief  Configures LEDs.
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
#if !defined(USE_STM32446E_EVAL_REVA)
  GPIO_InitTypeDef  gpio_init_structure;

  /* On RevB led1 and Led3 are on GPIO while Led2 and Led4 on Mfx*/
  if ((Led == LED1) || (Led == LED3))
  {
    /* Enable the GPIO_LED clock */
    LEDx_GPIO_CLK_ENABLE();

    /* Configure the GPIO_LED pin */
    gpio_init_structure.Pin = GPIO_PIN[Led];
    gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  
    HAL_GPIO_Init(LEDx_GPIO_PORT, &gpio_init_structure);
    
    /* By default, turn off LED */
    HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_SET);
  }
  else  /* Led2 and Led4 */
  {
#endif /* !USE_STM32446E_EVAL_REVA */

#if defined(USE_IOEXPANDER)  /* (USE_IOEXPANDER always defined for RevA) */
    /* Initialize the IO functionalities (Mfx) */
    BSP_IO_Init();
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
    /*  - in case of RevB just led 2 and led4 on IOEXPANDER (Mfx) */
    BSP_IO_ConfigPin(GPIO_PIN[Led], IO_MODE_OUTPUT_PP_PU);
    BSP_IO_WritePin(GPIO_PIN[Led], BSP_IO_PIN_SET);
#endif /* USE_IOEXPANDER */     

#if !defined(USE_STM32446E_EVAL_REVA)
  }
#endif /* !USE_STM32446E_EVAL_REVA */
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
#if !defined(USE_STM32446E_EVAL_REVA)
  GPIO_InitTypeDef  gpio_init_structure;

  /* On RevB led1 and Led3 are on GPIO while Led2 and Led4 on Mfx*/
  if ((Led == LED1) || (Led == LED3))
  {
    /* Turn off LED */
    HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_RESET);
    /* DeInit the GPIO_LED pin */
    gpio_init_structure.Pin = GPIO_PIN[Led];
    HAL_GPIO_DeInit(LEDx_GPIO_PORT, gpio_init_structure.Pin);
  }
  else
  {
#endif /* !USE_STM32446E_EVAL_REVA */

#if defined(USE_IOEXPANDER)   /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
    /*  - in case of RevB just led 2 and led4 on IOEXPANDER (Mfx) */
    BSP_IO_ConfigPin(GPIO_PIN[Led], IO_MODE_OFF);
#endif /* USE_IOEXPANDER */     

#if !defined(USE_STM32446E_EVAL_REVA)
  }
#endif /* !USE_STM32446E_EVAL_REVA */
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
  
#if !defined(USE_STM32446E_EVAL_REVA)
  /* On RevB led1 and Led3 are on GPIO while Led2 and Led4 on Mfx*/
  if ((Led == LED1) || (Led == LED3))
  {
     HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_RESET);
  }
  else
  {
#endif /* !USE_STM32446E_EVAL_REVA */

#if defined(USE_IOEXPANDER) /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
    /*  - in case of RevB just led 2 and led4 on IOEXPANDER (Mfx) */
    BSP_IO_WritePin(GPIO_PIN[Led], BSP_IO_PIN_RESET);
#endif /* USE_IOEXPANDER */     

#if !defined(USE_STM32446E_EVAL_REVA)
  }
#endif /* !USE_STM32446E_EVAL_REVA */
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
  
#if !defined(USE_STM32446E_EVAL_REVA)
  /* On RevB led1 and Led3 are on GPIO while Led2 and Led4 on Mfx*/
  if ((Led == LED1) || (Led == LED3))
  {
     HAL_GPIO_WritePin(LEDx_GPIO_PORT, GPIO_PIN[Led], GPIO_PIN_SET);
  }
  else
  {
#endif /* !USE_STM32446E_EVAL_REVA */

#if defined(USE_IOEXPANDER) /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
    /*  - in case of RevB just led 2 and led4 on IOEXPANDER (Mfx) */
    BSP_IO_WritePin(GPIO_PIN[Led], BSP_IO_PIN_SET);
#endif /* USE_IOEXPANDER */     

#if !defined(USE_STM32446E_EVAL_REVA)
  }
#endif /* !USE_STM32446E_EVAL_REVA */

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
  
#if !defined(USE_STM32446E_EVAL_REVA)
  /* On RevB led1 and Led3 are on GPIO while Led2 and Led4 on Mfx*/
  if ((Led == LED1) || (Led == LED3))
  {
     HAL_GPIO_TogglePin(LEDx_GPIO_PORT, GPIO_PIN[Led]);
  }
  else
  {
#endif /* !USE_STM32446E_EVAL_REVA */

#if defined(USE_IOEXPANDER) /* (USE_IOEXPANDER always defined for RevA) */
    /* GPIO_PIN[Led]  depends on the board revision: */
    /*  - in case of RevA all leds are on IOEXPANDER (Mfx)  */
    /*  - in case of RevB just led 2 and led4 on IOEXPANDER (Mfx) */
    BSP_IO_TogglePin(GPIO_PIN[Led]);
#endif /* USE_IOEXPANDER */     

#if !defined(USE_STM32446E_EVAL_REVA)
  }
#endif /* !USE_STM32446E_EVAL_REVA */
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button 
  *            @arg  BUTTON_TAMPER: Tamper Push Button  
  *            @arg  BUTTON_KEY: Key Push Button
  * @param  ButtonMode: Button mode
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *            @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line 
  *                                    with interrupt generation capability  
  * @note On STM32446E-EVAL evaluation board, the three buttons (Wakeup, Tamper
  *       and key buttons) are mapped on the same push button named "Wakeup/Tamper"
  *       on the board serigraphy.
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef gpio_init_structure;
  
  /* Enable the BUTTON clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpio_init_structure.Pin = BUTTON_PIN[Button];
    gpio_init_structure.Mode = GPIO_MODE_INPUT;
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI)
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
  *            @arg  BUTTON_KEY: Key Push Button
  * @note On STM32446E-EVAL evaluation board, the three buttons (Wakeup, Tamper
  *       and key buttons) are mapped on the same push button nammed "Wakeup/Tamper"
  *       on the board serigraphy.
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
  *            @arg  BUTTON_KEY: Key Push Button
  * @note On STM32446E-EVAL evaluation board, the three buttons (Wakeup, Tamper
  *       and key buttons) are mapped on the same push button nammed "Wakeup/Tamper"
  *       on the board serigraphy.
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

  /* Enable GPIO clock */
  EVAL_COMx_TX_GPIO_CLK_ENABLE(COM);
  EVAL_COMx_RX_GPIO_CLK_ENABLE(COM);

  /* Enable USART clock */
  EVAL_COMx_CLK_ENABLE(COM);

  /* Configure USART Tx as alternate function */
  gpio_init_structure.Pin = COM_TX_PIN[COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Alternate = COM_TX_AF[COM];
  HAL_GPIO_Init(COM_TX_PORT[COM], &gpio_init_structure);

  /* Configure USART Rx as alternate function */
  gpio_init_structure.Pin = COM_RX_PIN[COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = COM_RX_AF[COM];
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

  /* GPIO pins clock, FMC clock and DMA clock can be shut down in the application 
     by surcharging this __weak function */ 
}

#if defined(USE_IOEXPANDER)

/**
  * @brief  Configures joystick GPIO and EXTI modes.
  * @param  JoyMode: Button mode.
  *          This parameter can be one of the following values:
  *            @arg  JOY_MODE_GPIO: Joystick pins will be used as simple IOs
  *            @arg  JOY_MODE_EXTI: Joystick pins will be connected to EXTI line 
  *                                 with interrupt generation capability  
  * @retval IO_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_JOY_Init(JOYMode_TypeDef JoyMode)
{
  uint8_t ret = 0;
  
  /* Initialize the IO functionalities */
  ret = BSP_IO_Init();
  
  /* Configure joystick pins in IT mode */
  if(JoyMode == JOY_MODE_EXTI)
  {
    /* Configure IO interrupt acquisition mode */
    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_IT_FALLING_EDGE_PU);
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
  * @retval None.
  */
void BSP_JOY_DeInit(void)
{
    BSP_IO_ConfigPin(JOY_ALL_PINS, IO_MODE_OFF);
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


/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/
/**
  * @brief  Initializes I2C MSP.
  * @param  None
  * @retval None
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
  * @param  None
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_FMPI2C_GetState(&hEvalI2c) == HAL_FMPI2C_STATE_RESET)
  {
    hEvalI2c.Instance              = EVAL_I2Cx;
    hEvalI2c.Init.Timing           = EVAL_I2Cx_TIMING;
    hEvalI2c.Init.OwnAddress1     = 0;
    hEvalI2c.Init.AddressingMode  = FMPI2C_ADDRESSINGMODE_7BIT;
    hEvalI2c.Init.DualAddressMode = FMPI2C_DUALADDRESS_DISABLE;
    hEvalI2c.Init.OwnAddress2     = 0;
    hEvalI2c.Init.GeneralCallMode = FMPI2C_GENERALCALL_DISABLE;
    hEvalI2c.Init.NoStretchMode   = FMPI2C_NOSTRETCH_DISABLE;  
    
    /* Init the I2C */
    I2Cx_MspInit();
    HAL_FMPI2C_Init(&hEvalI2c);    
  }
}

#if defined(USE_IOEXPANDER)


/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
  */
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_FMPI2C_Mem_Write(&hEvalI2c, Addr, (uint16_t)Reg, FMPI2C_MEMADD_SIZE_8BIT, &Value, 1, 100); 

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
  
  status = HAL_FMPI2C_Mem_Read(&hEvalI2c, Addr, Reg, FMPI2C_MEMADD_SIZE_8BIT, &Value, 1, 1000);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
  return Value;   
}

#endif /* USE_IOEXPANDER */     

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_FMPI2C_Mem_Read(&hEvalI2c, Addr, (uint16_t)Reg, MemAddSize, Buffer, Length, 1000);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    I2Cx_Error(Addr);
  }
  return status;    
}

/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_FMPI2C_Mem_Write(&hEvalI2c, Addr, (uint16_t)Reg, MemAddSize, Buffer, Length, 1000);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the I2C Bus */
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
  return (HAL_FMPI2C_IsDeviceReady(&hEvalI2c, DevAddress, Trials, 1000));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the I2C communication bus */
  HAL_FMPI2C_DeInit(&hEvalI2c);
  
  /* Re-Initialize the I2C communication bus */
  I2Cx_Init();
}

/*************************** FMC Routines ************************************/
/**
  * @brief  Initializes FMC_BANK1 MSP.
  * @param  None
  * @retval None
  */
static void FMC_BANK1_MspInit(void)
{
  GPIO_InitTypeDef gpio_init_structure;
    
  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE(); 
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  
  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF12_FMC; 
  
  /* GPIOD configuration */ /* GPIO_PIN_7 is  FMC_NE1 */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 |\
                              GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_7;
   
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* GPIOE configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3| GPIO_PIN_4 | GPIO_PIN_7     |\
                              GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
                              GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);
  
  /* GPIOF configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 ;  
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);
}


/**
  * @brief  Initializes LCD IO.
  * @param  None
  * @retval None
  */
static void FMC_BANK1_Init(void) 
{  
  SRAM_HandleTypeDef hsram;
  FMC_NORSRAM_TimingTypeDef sram_timing;
  
  /*** Configure the SRAM Bank 1 ***/
  /* Configure IPs */
  hsram.Instance  = FMC_NORSRAM_DEVICE;
  hsram.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;

  sram_timing.AddressSetupTime      = 5;
  sram_timing.AddressHoldTime       = 1;
  sram_timing.DataSetupTime         = 9;
  sram_timing.BusTurnAroundDuration = 0;
  sram_timing.CLKDivision           = 2;
  sram_timing.DataLatency           = 2;
  sram_timing.AccessMode            = FMC_ACCESS_MODE_A;
  
  hsram.Init.NSBank             = FMC_NORSRAM_BANK1;
  hsram.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;
  hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram.Init.WrapMode           = FMC_WRAP_MODE_DISABLE;
  hsram.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  hsram.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  hsram.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;
  hsram.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  hsram.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;
  hsram.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram.Init.WriteFifo          = FMC_WRITE_FIFO_DISABLE;
  hsram.Init.PageSize           = FMC_PAGE_SIZE_NONE;

  /* Initialize the SRAM controller */
  FMC_BANK1_MspInit();
  HAL_SRAM_Init(&hsram, &sram_timing, &sram_timing);   
}


/**
  * @brief  Writes register value.
  * @param  Data: Data to be written 
  * @retval None
  */
static void FMC_BANK1_WriteData(uint16_t Data) 
{
  /* Write 16-bit Reg */
  FMC_BANK1->RAM = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg: Register to be written
  * @retval None
  */
static void FMC_BANK1_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Index, then write register */
  FMC_BANK1->REG = Reg;
}

/**
  * @brief  Reads register value.
  * @param  None
  * @retval Read value
  */
static uint16_t FMC_BANK1_ReadData(void) 
{
  return FMC_BANK1->RAM;
}

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

#if defined(USE_IOEXPANDER)

/********************************* LINK MFX ***********************************/

/**
  * @brief  Initializes MFX low level.
  * @param  None
  * @retval None
  */
void MFX_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  DeInitializes MFX low level.
  * @param  None
  * @retval None
  */
void MFX_IO_DeInit(void)
{
}

/**
  * @brief  Configures MFX low level interrupt.
  * @param  None
  * @retval None
  */
void MFX_IO_ITConfig(void)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Enable the GPIO EXTI clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* PA0 is the MFX_OUT_IRQ (often used for EXTI_WKUP) */    
  gpio_init_structure.Pin   = GPIO_PIN_0;
  gpio_init_structure.Pull  = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_LOW;
  gpio_init_structure.Mode  = GPIO_MODE_IT_RISING;
  HAL_GPIO_Init(GPIOA, &gpio_init_structure);

  /* Enable and set GPIO EXTI Interrupt to the lowest priority */
  HAL_NVIC_SetPriority((IRQn_Type)(EXTI0_IRQn), 0x0F, 0x0F);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI0_IRQn));
}

/**
  * @brief  MFX writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
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
 return I2Cx_ReadMultiple((uint8_t) Addr, (uint16_t)Reg, FMPI2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  MFX delay 
  * @param  Delay: Delay in ms
  * @retval None
  */
void MFX_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
  * @brief  Used by Lx family but requested for MFX component compatibility.
  * @param  None
  * @retval None
  */
void MFX_IO_Wakeup(void) 
{
}

/**
  * @brief  Used by Lx family but requested for MXF component compatibility.
  * @param  None
  * @retval None
  */
void MFX_IO_EnableWakeupPin(void) 
{
}

#endif /* USE_IOEXPANDER */

/********************************* LINK LCD ***********************************/

/**
  * @brief  Initializes LCD low level.
  * @param  None
  * @retval None
  */
void LCD_IO_Init(void) 
{
    FMC_BANK1_Init();
}

/**
  * @brief  Writes data on LCD data register.
  * @param  Data: Data to be written
  * @retval None
  */
void LCD_IO_WriteData(uint16_t RegValue) 
{
  /* Write 16-bit Reg */
  FMC_BANK1_WriteData(RegValue);
}

/**
  * @brief  Writes register on LCD register.
  * @param  Reg: Register to be written
  * @retval None
  */
void LCD_IO_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Index, then Write Reg */
  FMC_BANK1_WriteReg(Reg);
}

/**
  * @brief  Reads data from LCD data register.
  * @param  None
  * @retval Read data.
  */
uint16_t LCD_IO_ReadData(void) 
{
  return FMC_BANK1_ReadData();
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
void AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value)
{
  uint16_t tmp = Value;
  
  Value = ((uint16_t)(tmp >> 8) & 0x00FF);
  
  Value |= ((uint16_t)(tmp << 8)& 0xFF00);
  
  I2Cx_WriteMultiple(Addr, Reg, FMPI2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 2);
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
  
  I2Cx_ReadMultiple(Addr, Reg, FMPI2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 2); 
  
  tmp = ((uint16_t)(read_value >> 8) & 0x00FF);
  
  tmp |= ((uint16_t)(read_value << 8)& 0xFF00);
  
  read_value = tmp;
  
  return read_value;
}

/**
  * @brief  AUDIO Codec delay 
  * @param  Delay: Delay in ms
  * @retval None
  */
void AUDIO_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/********************************* LINK CAMERA ********************************/

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
  * @param  Reg: Register address 
  * @param  Value: Data to be written
  * @retval None
  */
void CAMERA_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value)
{
  uint16_t tmp = Value;
  /* For S5K5CAG sensor, 16 bits accesses are used */
  Value = ((uint16_t)(tmp >> 8) & 0x00FF);
  Value |= ((uint16_t)(tmp << 8)& 0xFF00);
  I2Cx_WriteMultiple(Addr, Reg, FMPI2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 2);
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
  I2Cx_ReadMultiple(Addr, Reg, FMPI2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 2);
  tmp = ((uint16_t)(read_value >> 8) & 0x00FF);
  tmp |= ((uint16_t)(read_value << 8)& 0xFF00);
  read_value = tmp;
  return read_value;
}

/**
  * @brief  Camera delay 
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
  * @brief  Write data to I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteMultiple(DevAddress, MemAddress, FMPI2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
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
  return (I2Cx_ReadMultiple(DevAddress, MemAddress, FMPI2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
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
