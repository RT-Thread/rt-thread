/*
File Name    : yc_gpio.c
Author       : Yichip
Version      : V1.0
Date         : 2019/12/03
Description  : gpio encapsulation.
*/

#ifndef __YC_GPIO_H__
#define __YC_GPIO_H__

#include "yc3121.h"

/**
  * @brief Configuration Mode enumeration
  */
typedef enum
{
  GPIO_Mode_IN_FLOATING = 0x01,
  GPIO_Mode_IPU = 0x02,
  GPIO_Mode_IPD = 0x03,
  GPIO_Mode_AIN = 0x04,
  GPIO_Mode_Out_PP = 0x05 /*!<  analog signal mode */
} GPIO_ModeTypeDef;

#define IS_GPIO_MODE(mode) (((mode) == GPIO_Mode_IN_FLOATING) || \
                            ((mode) == GPIO_Mode_IPU) ||         \
                            ((mode) == GPIO_Mode_IPD) ||         \
                            ((mode) == GPIO_Mode_Out_PP) ||      \
                            ((mode) == GPIO_Mode_AIN))

/**
  * @brief Bit_SET and Bit_RESET enumeration
  */
typedef enum
{
  Bit_RESET = 0,
  Bit_SET
} BitAction;

/**
  * @brief gpio output enumeration
  */
typedef enum
{
  OutputLow = 0,
  OutputHigh = 1
} GPIO_OutputTypeDef;

#define IS_GPIO_WAKE_MODE(MODE) (((MODE) == GPIO_WakeMode_Now) || \
                                 ((MODE) == GPIO_WakeMode_AfterGlitch))

/**
  * @brief  GPIO function  enumeration
  */
typedef enum
{
  INPUT = GPCFG_INPUT,
  QSPI_NCS = GPCFG_QSPI_NCS,
  QSPI_SCK = GPCFG_QSPI_SCK,
  QSPI_IO0 = GPCFG_QSPI_IO0,
  QSPI_IO1 = GPCFG_QSPI_IO1,
  QSPI_IO2 = GPCFG_QSPI_IO2,
  QSPI_IO3 = GPCFG_QSPI_IO3,
  UART0_TXD = GPCFG_UART0_TXD,
  UART0_RXD = GPCFG_UART0_RXD,
  UART0_RTS = GPCFG_UART0_RTS,
  UART0_CTS = GPCFG_UART0_CTS,
  UART1_TXD = GPCFG_UART1_TXD,
  UART1_RXD = GPCFG_UART1_RXD,
  UART1_RTS = GPCFG_UART1_RTS,
  UART1_CTS = GPCFG_UART1_CTS,
  PWM_OUT0 = GPCFG_PWM_OUT0,
  PWM_OUT1 = GPCFG_PWM_OUT1,
  PWM_OUT2 = GPCFG_PWM_OUT2,
  PWM_OUT3 = GPCFG_PWM_OUT3,
  PWM_OUT4 = GPCFG_PWM_OUT4,
  PWM_OUT5 = GPCFG_PWM_OUT5,
  PWM_OUT6 = GPCFG_PWM_OUT6,
  PWM_OUT7 = GPCFG_PWM_OUT7,
  PWM_OUT8 = GPCFG_PWM_OUT8,
  SPID0_NCS = GPCFG_SPID0_NCS,
  SPID0_SCK = GPCFG_SPID0_SCK,
  SPID0_MOSI = GPCFG_SPID0_MOSI,
  SPID0_SDIO = GPCFG_SPID0_SDIO,
  SPID0_MISO = GPCFG_SPID0_MISO,
  SPID0_NCSIN = GPCFG_SPID0_NCSIN,
  SPID0_SCKIN = GPCFG_SPID0_SCKIN,
  SPID1_NCS = GPCFG_SPID1_NCS,
  SPID1_SCK = GPCFG_SPID1_SCK,
  SPID1_MOSI = GPCFG_SPID1_MOSI,
  SPID1_SDIO = GPCFG_SPID1_SDIO,
  SPID1_MISO = GPCFG_SPID1_MISO,
  SPID1_NCSIN = GPCFG_SPID1_NCSIN,
  SPID1_SCKIN = GPCFG_SPID1_SCKIN,
  NFC_CLK_OUT = GPCFG_NFC_CLK_OUT,
  SCI7816_IO = GPCFG_SCI7816_IO,
  IIC_SCL = GPCFG_IIC_SCL,
  IIC_SDA = GPCFG_IIC_SDA,
  JTAG_SWCLK = GPCFG_JTAG_SWCLK,
  JTAG_SWDAT = GPCFG_JTAG_SWDAT,
  OUTPUT_LOW = GPCFG_OUTPUT_LOW,
  OUTPUT_HIGH = GPCFG_OUTPUT_HIGH,
  PULL_UP = GPCFG_PU,
  PULL_DOWN = GPCFG_PD,
  ANALOG = GPCFG_ANALOG
} GPIO_FunTypeDef;

#define GPIO_Pin_0 ((uint16_t)0x0001)   /*!< Pin 0 selected */
#define GPIO_Pin_1 ((uint16_t)0x0002)   /*!< Pin 1 selected */
#define GPIO_Pin_2 ((uint16_t)0x0004)   /*!< Pin 2 selected */
#define GPIO_Pin_3 ((uint16_t)0x0008)   /*!< Pin 3 selected */
#define GPIO_Pin_4 ((uint16_t)0x0010)   /*!< Pin 4 selected */
#define GPIO_Pin_5 ((uint16_t)0x0020)   /*!< Pin 5 selected */
#define GPIO_Pin_6 ((uint16_t)0x0040)   /*!< Pin 6 selected */
#define GPIO_Pin_7 ((uint16_t)0x0080)   /*!< Pin 7 selected */
#define GPIO_Pin_8 ((uint16_t)0x0100)   /*!< Pin 8 selected */
#define GPIO_Pin_9 ((uint16_t)0x0200)   /*!< Pin 9 selected */
#define GPIO_Pin_10 ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pin_11 ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pin_12 ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pin_13 ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pin_14 ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pin_15 ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pin_All ((uint16_t)0xffff) /*!< Pin All selected */

#define IS_GPIO_PIN(PIN) (((((PIN) & ~(uint16_t)0xFFFF)) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) ||  \
                              ((PIN) == GPIO_Pin_1) ||  \
                              ((PIN) == GPIO_Pin_2) ||  \
                              ((PIN) == GPIO_Pin_3) ||  \
                              ((PIN) == GPIO_Pin_4) ||  \
                              ((PIN) == GPIO_Pin_5) ||  \
                              ((PIN) == GPIO_Pin_6) ||  \
                              ((PIN) == GPIO_Pin_7) ||  \
                              ((PIN) == GPIO_Pin_8) ||  \
                              ((PIN) == GPIO_Pin_9) ||  \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
  * @brief  GPIO group enumeration
  */
typedef enum
{
  GPIOA = 0,
  GPIOB,
  GPIOC
} GPIO_TypeDef;

#define ISGPIOGROUP(groupx) (groupx < GPIO_GROUP_NUM)

/**
  * @brief  GPIO Init structure definition
  */
typedef struct
{
  uint16_t GPIO_Pin;
  GPIO_ModeTypeDef GPIO_Mode;
} GPIO_InitTypeDef;

/**
 * @brief  config gpio function(Only one can be configured at a time)
 *
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 *
 * @param  GPIO_Pin: select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)(Only one can be configured at a time)
 *
 * @param  function:gpio function
 *
 * @retval none
 */
void GPIO_Config(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, GPIO_FunTypeDef function);

/**
 * @brief  gpio mode Init
 *
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 *
 * @param  GPIO_InitStruct:GPIO_InitStruct
 *
 * @retval none
 */
void GPIO_Init(GPIO_TypeDef GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);

/**
  * @brief
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_7)
  *
  * @param  NewState: new state of the port pin Pull Up.(ENABLE or DISABLE)
  *
  * @retval
  */
void GPIO_PullUpCmd(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, FunctionalState NewState);

/**
  * @brief  Reads the GPIO input data(status) for byte.
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @retval GPIO input data(status).
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef GPIOx);

/**
 * @brief  Reads the GPIO input data(status) for bit.
 *
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 *
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 *
 * @retval The input status
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin);

/**
  * @brief  Reads the GPIO output data(status) for byte.
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @retval GPIO output data(status).
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef GPIOx);

/**
 * @brief  Reads the GPIO output data(status) for bit.
 *
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 *
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 *
 * @retval The output status
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin);

/**
  * @brief  Clears the selected pin(only output mode)
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
  *
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin);

/**
  * @brief  sets the selected pin(only output mode)
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
  *
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin);

/**
  * @brief  init GPIO_InitStruct to default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

/**
  * @brief  Writes data to the GPIO group port(only output mode)
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @param  value: specifies the value to be written to the port output data register.
  *
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef GPIOx, uint16_t value);

/**
  * @brief  Sets or clears the selected data port bit(only output mode)
  *
  * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
  *
  * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_7)
  *
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

#endif /* __YC_GPIO_H__ */
