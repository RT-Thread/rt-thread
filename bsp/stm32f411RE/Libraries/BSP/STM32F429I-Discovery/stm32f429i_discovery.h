/**
  ******************************************************************************
  * @file    stm32f429i_discovery.h
  * @author  MCD Application Team
  * @version V2.1.2
  * @date    02-March-2015
  * @brief   This file contains definitions for STM32F429I-Discovery Kit LEDs,
  *          push-buttons hardware resources.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F429I_DISCOVERY_H
#define __STM32F429I_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif
                                              
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
   
/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
   
/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL
  * @{
  */
   
/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Types
  * @{
  */
typedef enum 
{
  LED3 = 0,
  LED4 = 1
}Led_TypeDef;

typedef enum 
{  
  BUTTON_KEY = 0,
}Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;     

/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/** 
  * @brief Define for STM32F429I_DISCO board  
  */ 
#if !defined (USE_STM32F429I_DISCO)
 #define USE_STM32F429I_DISCO
#endif

/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_LED
  * @{
  */
#define LEDn                                    2
  
#define LED3_PIN                                GPIO_PIN_13
#define LED3_GPIO_PORT                          GPIOG
#define LED3_GPIO_CLK_ENABLE()                  __GPIOG_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()                 __GPIOG_CLK_DISABLE()  

#define LED4_PIN                                GPIO_PIN_14
#define LED4_GPIO_PORT                          GPIOG
#define LED4_GPIO_CLK_ENABLE()                  __GPIOG_CLK_ENABLE()  
#define LED4_GPIO_CLK_DISABLE()                 __GPIOG_CLK_DISABLE()  

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LED3_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 1) LED4_GPIO_CLK_ENABLE(); \
                                            }while(0)
#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) LED3_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == 1) LED4_GPIO_CLK_DISABLE(); \
                                            }while(0)
/**
  * @}
  */ 
  
/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_BUTTON
  * @{
  */  
#define BUTTONn                                1

/**
 * @brief Wakeup push-button
 */
#define KEY_BUTTON_PIN                         GPIO_PIN_0
#define KEY_BUTTON_GPIO_PORT                   GPIOA
#define KEY_BUTTON_GPIO_CLK_ENABLE()           __GPIOA_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()          __GPIOA_CLK_DISABLE()
#define KEY_BUTTON_EXTI_IRQn                   EXTI0_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)     do{if((__INDEX__) == 0) KEY_BUTTON_GPIO_CLK_ENABLE(); \
                                                 }while(0)
#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    do{if((__INDEX__) == 0) KEY_BUTTON_GPIO_CLK_DISABLE(); \
                                                 }while(0)
/**
  * @}
  */

/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_BUS
  * @{
  */  
/* Exported constanIO --------------------------------------------------------*/
#define IO_I2C_ADDRESS                      0x82 
#define TS_I2C_ADDRESS                      0x82

#ifdef EE_M24LR64
#define EEPROM_I2C_ADDRESS_A01              0xA0
#define EEPROM_I2C_ADDRESS_A02              0xA6
#endif /* EE_M24LR64 */ 

/*############################### I2Cx #######################################*/
/* User can use this section to tailor I2Cx instance used and associated 
   resources */
#define DISCOVERY_I2Cx                          I2C3
#define DISCOVERY_I2Cx_CLOCK_ENABLE()           __I2C3_CLK_ENABLE()
#define DISCOVERY_I2Cx_FORCE_RESET()            __I2C3_FORCE_RESET()
#define DISCOVERY_I2Cx_RELEASE_RESET()          __I2C3_RELEASE_RESET()
#define DISCOVERY_I2Cx_SDA_GPIO_CLK_ENABLE()    __GPIOC_CLK_ENABLE()
#define DISCOVERY_I2Cx_SCL_GPIO_CLK_ENABLE()    __GPIOA_CLK_ENABLE() 
#define DISCOVERY_I2Cx_SDA_GPIO_CLK_DISABLE()   __GPIOC_CLK_DISABLE()

/* Definition for DISCO I2Cx Pins */
#define DISCOVERY_I2Cx_SCL_PIN                  GPIO_PIN_8
#define DISCOVERY_I2Cx_SCL_GPIO_PORT            GPIOA
#define DISCOVERY_I2Cx_SCL_SDA_AF               GPIO_AF4_I2C3
#define DISCOVERY_I2Cx_SDA_PIN                  GPIO_PIN_9
#define DISCOVERY_I2Cx_SDA_GPIO_PORT            GPIOC

/* Definition for IOE I2Cx's NVIC */
#define DISCOVERY_I2Cx_EV_IRQn                  I2C3_EV_IRQn
#define DISCOVERY_I2Cx_ER_IRQn                  I2C3_ER_IRQn

/* I2C clock speed configuration (in Hz) 
  WARNING: 
   Make sure that this define is not already declared in other files.
   It can be used in parallel by other modules. */
#ifndef BSP_I2C_SPEED
 #define BSP_I2C_SPEED                          100000
#endif /* BSP_I2C_SPEED */

#define I2Cx_TIMEOUT_MAX                    0x3000 /*<! The value of the maximal timeout for I2C waiting loops */

/*############################### SPIx #######################################*/
#define DISCOVERY_SPIx                          SPI5
#define DISCOVERY_SPIx_CLK_ENABLE()             __SPI5_CLK_ENABLE()
#define DISCOVERY_SPIx_GPIO_PORT                GPIOF                      /* GPIOF */
#define DISCOVERY_SPIx_AF                       GPIO_AF5_SPI5
#define DISCOVERY_SPIx_GPIO_CLK_ENABLE()        __GPIOF_CLK_ENABLE()
#define DISCOVERY_SPIx_GPIO_CLK_DISABLE()       __GPIOF_CLK_DISABLE()
#define DISCOVERY_SPIx_SCK_PIN                  GPIO_PIN_7                 /* PF.07 */
#define DISCOVERY_SPIx_MISO_PIN                 GPIO_PIN_8                 /* PF.08 */
#define DISCOVERY_SPIx_MOSI_PIN                 GPIO_PIN_9                 /* PF.09 */
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define SPIx_TIMEOUT_MAX              ((uint32_t)0x1000)


/*################################ IOE #######################################*/
/** 
  * @brief  IOE Control pin  
  */ 
/* Definition for external IT for STMPE811 */
#define STMPE811_INT_PIN                        GPIO_PIN_15
#define STMPE811_INT_GPIO_PORT                  GPIOA
#define STMPE811_INT_CLK_ENABLE()               __GPIOA_CLK_ENABLE()
#define STMPE811_INT_CLK_DISABLE()              __GPIOA_CLK_DISABLE()
#define STMPE811_INT_EXTI                       EXTI15_10_IRQn
#define STMPE811_INT_EXTIHandler                EXTI15_10_IRQHandler

/*################################ LCD #######################################*/
/* Chip Select macro definition */
#define LCD_CS_LOW()       HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_RESET)
#define LCD_CS_HIGH()      HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_SET)

/* Set WRX High to send data */
#define LCD_WRX_LOW()      HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_RESET)
#define LCD_WRX_HIGH()     HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_SET)

/* Set WRX High to send data */
#define LCD_RDX_LOW()      HAL_GPIO_WritePin(LCD_RDX_GPIO_PORT, LCD_RDX_PIN, GPIO_PIN_RESET)
#define LCD_RDX_HIGH()     HAL_GPIO_WritePin(LCD_RDX_GPIO_PORT, LCD_RDX_PIN, GPIO_PIN_SET)

/** 
  * @brief  LCD Control pin  
  */ 
#define LCD_NCS_PIN                             GPIO_PIN_2
#define LCD_NCS_GPIO_PORT                       GPIOC
#define LCD_NCS_GPIO_CLK_ENABLE()               __GPIOC_CLK_ENABLE()
#define LCD_NCS_GPIO_CLK_DISABLE()              __GPIOC_CLK_DISABLE()
/**             
  * @}
  */ 
/** 
  * @brief  LCD Command/data pin  
  */
#define LCD_WRX_PIN                             GPIO_PIN_13
#define LCD_WRX_GPIO_PORT                       GPIOD
#define LCD_WRX_GPIO_CLK_ENABLE()               __GPIOD_CLK_ENABLE()
#define LCD_WRX_GPIO_CLK_DISABLE()              __GPIOD_CLK_DISABLE()
  
#define LCD_RDX_PIN                             GPIO_PIN_12
#define LCD_RDX_GPIO_PORT                       GPIOD
#define LCD_RDX_GPIO_CLK_ENABLE()               __GPIOD_CLK_ENABLE()
#define LCD_RDX_GPIO_CLK_DISABLE()              __GPIOD_CLK_DISABLE()

/*################################ GYROSCOPE #################################*/
/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80) 
/* Multiple byte read/write command */ 
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)

/* Chip Select macro definition */
#define GYRO_CS_LOW()       HAL_GPIO_WritePin(GYRO_CS_GPIO_PORT, GYRO_CS_PIN, GPIO_PIN_RESET)
#define GYRO_CS_HIGH()      HAL_GPIO_WritePin(GYRO_CS_GPIO_PORT, GYRO_CS_PIN, GPIO_PIN_SET)

/**
  * @brief  GYROSCOPE SPI Interface pins
  */
#define GYRO_CS_PIN                             GPIO_PIN_1                  /* PC.01 */
#define GYRO_CS_GPIO_PORT                       GPIOC                       /* GPIOC */
#define GYRO_CS_GPIO_CLK_ENABLE()               __GPIOC_CLK_ENABLE()
#define GYRO_CS_GPIO_CLK_DISABLE()              __GPIOC_CLK_DISABLE()

#define GYRO_INT_GPIO_CLK_ENABLE()              __GPIOA_CLK_ENABLE()
#define GYRO_INT_GPIO_CLK_DISABLE()             __GPIOA_CLK_DISABLE()
#define GYRO_INT_GPIO_PORT                      GPIOA                       /* GPIOA */
#define GYRO_INT1_PIN                           GPIO_PIN_1                  /* PA.01 */
#define GYRO_INT1_EXTI_IRQn                     EXTI1_IRQn 
#define GYRO_INT2_PIN                           GPIO_PIN_2                  /* PA.02 */
#define GYRO_INT2_EXTI_IRQn                     EXTI2_IRQn 
/**
  * @}
  */ 

#ifdef EE_M24LR64
/** @addtogroup STM32F429I_DISCOVERY_LOW_LEVEL_I2C_EEPROM
  * @{
  */
/**
  * @brief  I2C EEPROM Interface pins
  */
#define EEPROM_I2C_DMA                          DMA1   
#define EEPROM_I2C_DMA_CHANNEL                  DMA_CHANNEL_3
#define EEPROM_I2C_DMA_STREAM_TX                DMA1_Stream4
#define EEPROM_I2C_DMA_STREAM_RX                DMA1_Stream2
#define EEPROM_I2C_DMA_CLK_ENABLE()             __DMA1_CLK_ENABLE()
   
#define EEPROM_I2C_DMA_TX_IRQn                  DMA1_Stream4_IRQn
#define EEPROM_I2C_DMA_RX_IRQn                  DMA1_Stream2_IRQn
#define EEPROM_I2C_DMA_TX_IRQHandler            DMA1_Stream4_IRQHandler
#define EEPROM_I2C_DMA_RX_IRQHandler            DMA1_Stream2_IRQHandler
#define EEPROM_I2C_DMA_PREPRIO                  0
/**
  * @}
  */ 

#endif /* EE_M24LR64 */

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Macros
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Exported_Functions
  * @{
  */
uint32_t BSP_GetVersion(void);  
void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);
void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
uint32_t BSP_PB_GetState(Button_TypeDef Button);

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

#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
