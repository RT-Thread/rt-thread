/**
  ******************************************************************************
  * @file    stm32469i_discovery.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides a set of firmware functions to manage LEDs,
  *          push-buttons, external SDRAM, external QSPI Flash, RF EEPROM,
  *          available on STM32469I-Discovery
  *          board (MB1189) RevA/B from STMicroelectronics.
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
#include "stm32469i_discovery.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_Discovery
  * @{
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL STM32469I-Discovery LOW LEVEL
  * @{
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Private_TypesDefinitions STM32469I Discovery Low Level Private Typedef
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Private_Defines LOW_LEVEL Private Defines
  * @{
  */
/**
 * @brief STM32469I Discovery BSP Driver version number V1.0.1
   */
#define __STM32469I_DISCOVERY_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32469I_DISCOVERY_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32469I_DISCOVERY_BSP_VERSION_SUB2   (0x01) /*!< [15:8]  sub2 version */
#define __STM32469I_DISCOVERY_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32469I_DISCOVERY_BSP_VERSION        ((__STM32469I_DISCOVERY_BSP_VERSION_MAIN << 24)\
                                                 |(__STM32469I_DISCOVERY_BSP_VERSION_SUB1 << 16)\
                                                 |(__STM32469I_DISCOVERY_BSP_VERSION_SUB2 << 8 )\
                                                 |(__STM32469I_DISCOVERY_BSP_VERSION_RC))
/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Private_Macros  LOW_LEVEL Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Private_Variables LOW_LEVEL Private Variables
  * @{
  */
uint32_t GPIO_PIN[LEDn] = {LED1_PIN,
                           LED2_PIN,
                           LED3_PIN,
                           LED4_PIN};

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT,
                                 LED2_GPIO_PORT,
                                 LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT };

const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN };

const uint16_t BUTTON_IRQn[BUTTONn] = {WAKEUP_BUTTON_EXTI_IRQn };


static I2C_HandleTypeDef heval_I2c1;
static I2C_HandleTypeDef heval_I2c2;

/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Private_FunctionPrototypes LOW_LEVEL Private FunctionPrototypes
  * @{
  */
static void            I2C1_MspInit(void);
static void            I2C2_MspInit(void);
static void            I2C1_Init(void);
static void            I2C2_Init(void);

#if defined(USE_IOEXPANDER)
static void            I2C1_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t       I2C1_Read(uint8_t Addr, uint8_t Reg);
#endif /* USE_IOEXPANDER */
static HAL_StatusTypeDef I2C1_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2C2_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2C1_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2C2_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2C1_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void              I2C1_Error(uint8_t Addr);
static void              I2C2_Error(uint8_t Addr);

/* AUDIO IO functions */
void              AUDIO_IO_Init(void);
void              AUDIO_IO_DeInit(void);
void              AUDIO_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t           AUDIO_IO_Read(uint8_t Addr, uint8_t Reg);
void              AUDIO_IO_Delay(uint32_t Delay);


/* I2C EEPROM IO function */
void                EEPROM_IO_Init(void);
HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);

/* TouchScreen (TS) IO functions */
void    TS_IO_Init(void);
void    TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t  TS_IO_Read(uint8_t Addr, uint8_t Reg);
uint16_t TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void    TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void    TS_IO_Delay(uint32_t Delay);
void     OTM8009A_IO_Delay(uint32_t Delay);
/**
  * @}
  */

/** @defgroup STM32469I_Discovery_BSP_Public_Functions BSP Public Functions
  * @{
  */

  /**
  * @brief  This method returns the STM32469I Discovery BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32469I_DISCOVERY_BSP_VERSION;
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
  GPIO_InitTypeDef  gpio_init_structure;

  if (Led <= LED4)
  {
    /* Configure the GPIO_LED pin */
    gpio_init_structure.Pin   = GPIO_PIN[Led];
    gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull  = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;

    switch(Led)
    {
    case LED1 :
      LED1_GPIO_CLK_ENABLE();
      break;
    case LED2 :
      LED2_GPIO_CLK_ENABLE();
      break;
    case LED3 :
      LED3_GPIO_CLK_ENABLE();
      break;
    case LED4 :
      LED4_GPIO_CLK_ENABLE();
      break;
    default :
      break;

    } /* end switch */

    HAL_GPIO_Init(GPIO_PORT[Led], &gpio_init_structure);

    /* By default, turn off LED by setting a high level on corresponding GPIO */
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);

  } /* of if (Led <= LED4) */

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
  GPIO_InitTypeDef  gpio_init_structure;

  if (Led <= LED4)
  {
    /* DeInit the GPIO_LED pin */
    gpio_init_structure.Pin = GPIO_PIN[Led];

    /* Turn off LED */
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
    HAL_GPIO_DeInit(GPIO_PORT[Led], gpio_init_structure.Pin);
  }

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
  if (Led <= LED4)
  {
     HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET);
  }

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
  if (Led <= LED4)
  {
    HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
  }
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
  if (Led <= LED4)
  {
     HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
  }
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button
  *            @arg  BUTTON_USER: User Push Button
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
  BUTTON_GPIO_CLK_ENABLE();

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

    gpio_init_structure.Mode = GPIO_MODE_IT_RISING;

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
  *            @arg  BUTTON_USER: User Push Button
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
  *            @arg  BUTTON_USER: User Push Button
  * @retval The Button GPIO pin value
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @}
  */

/** @defgroup STM32469I_Discovery_LOW_LEVEL_Private_Functions STM32469I_Discovery_LOW_LEVEL Private Functions
  * @{
  */


/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/
/**
  * @brief  Initializes I2C MSP.
  */
static void I2C1_MspInit(void)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  DISCO_I2C1_SCL_SDA_GPIO_CLK_ENABLE();

  /* Configure I2C Tx as alternate function */
  gpio_init_structure.Pin = DISCO_I2C1_SCL_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = DISCO_I2C1_SCL_SDA_AF;
  HAL_GPIO_Init(DISCO_I2C1_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /* Configure I2C Rx as alternate function */
  gpio_init_structure.Pin = DISCO_I2C1_SDA_PIN;
  HAL_GPIO_Init(DISCO_I2C1_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /*** Configure the I2C peripheral ***/
  /* Enable I2C clock */
  DISCO_I2C1_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  DISCO_I2C1_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  DISCO_I2C1_RELEASE_RESET();

  /* Enable and set I2C1 Interrupt to a lower priority */
  HAL_NVIC_SetPriority(DISCO_I2C1_EV_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(DISCO_I2C1_EV_IRQn);

  /* Enable and set I2C1 Interrupt to a lower priority */
  HAL_NVIC_SetPriority(DISCO_I2C1_ER_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(DISCO_I2C1_ER_IRQn);
}

/**
  * @brief  Initializes I2C MSP.
  */
static void I2C2_MspInit(void)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  DISCO_I2C2_SCL_SDA_GPIO_CLK_ENABLE();

  /* Configure I2C Tx as alternate function */
  gpio_init_structure.Pin = DISCO_I2C2_SCL_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = DISCO_I2C2_SCL_SDA_AF;
  HAL_GPIO_Init(DISCO_I2C2_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /* Configure I2C Rx as alternate function */
  gpio_init_structure.Pin = DISCO_I2C2_SDA_PIN;
  HAL_GPIO_Init(DISCO_I2C2_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /*** Configure the I2C peripheral ***/
  /* Enable I2C clock */
  DISCO_I2C2_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  DISCO_I2C2_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  DISCO_I2C2_RELEASE_RESET();

  /* Enable and set I2C1 Interrupt to a lower priority */
  HAL_NVIC_SetPriority(DISCO_I2C2_EV_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(DISCO_I2C2_EV_IRQn);

  /* Enable and set I2C1 Interrupt to a lower priority */
  HAL_NVIC_SetPriority(DISCO_I2C2_ER_IRQn, 0x05, 0);
  HAL_NVIC_EnableIRQ(DISCO_I2C2_ER_IRQn);
}

/**
  * @brief  Initializes I2C HAL.
  */
static void I2C1_Init(void)
{
  if(HAL_I2C_GetState(&heval_I2c1) == HAL_I2C_STATE_RESET)
  {
    heval_I2c1.Instance = I2C1;
    heval_I2c1.Init.ClockSpeed      = I2C1_SCL_FREQ_KHZ;
    heval_I2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    heval_I2c1.Init.OwnAddress1     = 0;
    heval_I2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    heval_I2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    heval_I2c1.Init.OwnAddress2     = 0;
    heval_I2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    heval_I2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    /* Init the I2C */
    I2C1_MspInit();
    HAL_I2C_Init(&heval_I2c1);
  }
}

/**
  * @brief  Initializes I2C HAL.
  */
static void I2C2_Init(void)
{
  if(HAL_I2C_GetState(&heval_I2c2) == HAL_I2C_STATE_RESET)
  {
    heval_I2c2.Instance = I2C2;
    heval_I2c2.Init.ClockSpeed      = I2C2_SCL_FREQ_KHZ;
    heval_I2c2.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    heval_I2c2.Init.OwnAddress1     = 0;
    heval_I2c2.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    heval_I2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    heval_I2c2.Init.OwnAddress2     = 0;
    heval_I2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    heval_I2c2.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    /* Init the I2C */
    I2C2_MspInit();
    HAL_I2C_Init(&heval_I2c2);
  }
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
static void I2C1_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&heval_I2c1,
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
    I2C1_Error(Addr);
  }
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
static uint8_t I2C1_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;

  status = HAL_I2C_Mem_Read(&heval_I2c1,
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
    I2C1_Error(Addr);
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
static HAL_StatusTypeDef I2C1_ReadMultiple(uint8_t Addr,
                                       uint16_t Reg,
                                       uint16_t MemAddress,
                                       uint8_t *Buffer,
                                       uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&heval_I2c1,
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
    I2C1_Error(Addr);
  }
  return status;
}

static HAL_StatusTypeDef I2C2_ReadMultiple(uint8_t Addr,
                                       uint16_t Reg,
                                       uint16_t MemAddress,
                                       uint8_t *Buffer,
                                       uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&heval_I2c2,
                        Addr,
                        (uint16_t)Reg,
                        MemAddress,
                        Buffer,
                        Length,
                        1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C2 error occured */
    I2C2_Error(Addr);
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
static HAL_StatusTypeDef I2C1_WriteMultiple(uint8_t Addr,
                                        uint16_t Reg,
                                        uint16_t MemAddress,
                                        uint8_t *Buffer,
                                        uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&heval_I2c1,
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
    I2C1_Error(Addr);
  }
  return status;
}

static HAL_StatusTypeDef I2C2_WriteMultiple(uint8_t Addr,
                                        uint16_t Reg,
                                        uint16_t MemAddress,
                                        uint8_t *Buffer,
                                        uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&heval_I2c2,
                         Addr,
                         (uint16_t)Reg,
                         MemAddress,
                         Buffer,
                         Length,
                         1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C2 Bus */
    I2C2_Error(Addr);
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
static HAL_StatusTypeDef I2C1_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{
  return (HAL_I2C_IsDeviceReady(&heval_I2c1, DevAddress, Trials, 1000));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2C1_Error(uint8_t Addr)
{
  /* De-initialize the I2C comunication bus */
  HAL_I2C_DeInit(&heval_I2c1);

  /* Re-Initiaize the I2C comunication bus */
  I2C1_Init();
}

static void I2C2_Error(uint8_t Addr)
{
  /* De-initialize the I2C2 comunication bus */
  HAL_I2C_DeInit(&heval_I2c2);

  /* Re-Initiaize the I2C2 comunication bus */
  I2C2_Init();
}

/**
  * @}
  */

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK AUDIO *********************************/

/**
  * @brief  Initializes Audio low level.
  */
void AUDIO_IO_Init(void)
{
  I2C2_Init();
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
void AUDIO_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2C2_WriteMultiple(Addr, (uint16_t) Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&Value, 1);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Data to be read
  */
uint8_t AUDIO_IO_Read(uint8_t Addr, uint8_t Reg)
{
  uint8_t read_value = 0;

  I2C2_ReadMultiple(Addr, (uint16_t) Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&read_value, 1);

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

/******************************** LINK I2C EEPROM *****************************/

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  */
void EEPROM_IO_Init(void)
{
  I2C1_Init();
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
  return (I2C1_WriteMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
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
  return (I2C1_ReadMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
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
  return (I2C1_IsDeviceReady(DevAddress, Trials));
}

/******************************** LINK TS (TouchScreen) ***********************/

/**
  * @brief  Initialize I2C communication
  *         channel from MCU to TouchScreen (TS).
  */
void TS_IO_Init(void)
{
  I2C1_Init();
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
  I2C1_Write(Addr, Reg, Value);
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
  return I2C1_Read(Addr, Reg);
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
 return I2C1_ReadMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
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
  I2C1_WriteMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
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
