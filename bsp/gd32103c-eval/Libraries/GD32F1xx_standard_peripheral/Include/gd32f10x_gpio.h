/**
  ******************************************************************************
  * @brief   GPIO header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10x_GPIO_H
#define __GD32F10x_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types
  * @{
  */

/**
  * @brief Output_Maximum_frequency_enumeration
  */
typedef enum {
    GPIO_SPEED_10MHZ = 1,
    GPIO_SPEED_2MHZ,
    GPIO_SPEED_50MHZ
} GPIO_SpeedPara;

/**
  * @brief GPIO_Mode_enumeration
  */
typedef enum {
    GPIO_MODE_AIN = 0x0,
    GPIO_MODE_IN_FLOATING = 0x04,
    GPIO_MODE_IPD = 0x28,
    GPIO_MODE_IPU = 0x48,
    GPIO_MODE_OUT_OD = 0x14,
    GPIO_MODE_OUT_PP = 0X10,
    GPIO_MODE_AF_OD = 0X1C,
    GPIO_MODE_AF_PP = 0X18
} GPIO_ModePara;

/**
  * @brief GPIO Initial Parameters
  */
typedef struct {
    uint16_t GPIO_Pin;                  /*!< The GPIO pins to be configured. choose several from @ref GPIO_pins_define */
    GPIO_SpeedPara GPIO_Speed;          /*!< The speed for This parameter can be a value of @ref GPIOSpeed_TypeDef */
    GPIO_ModePara GPIO_Mode;            /*!< The operating mode for the selected pins. choose one from @ref GPIO_ModePara */
} GPIO_InitPara;

/**
  * @brief Bit_State_enumeration
  */
typedef enum {
    Bit_RESET = 0,
    Bit_SET
} BitState;

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define
  * @{
  */
#define GPIO_PIN_0                      ((uint16_t)0x0001)
#define GPIO_PIN_1                      ((uint16_t)0x0002)
#define GPIO_PIN_2                      ((uint16_t)0x0004)
#define GPIO_PIN_3                      ((uint16_t)0x0008)
#define GPIO_PIN_4                      ((uint16_t)0x0010)
#define GPIO_PIN_5                      ((uint16_t)0x0020)
#define GPIO_PIN_6                      ((uint16_t)0x0040)
#define GPIO_PIN_7                      ((uint16_t)0x0080)
#define GPIO_PIN_8                      ((uint16_t)0x0100)
#define GPIO_PIN_9                      ((uint16_t)0x0200)
#define GPIO_PIN_10                     ((uint16_t)0x0400)
#define GPIO_PIN_11                     ((uint16_t)0x0800)
#define GPIO_PIN_12                     ((uint16_t)0x1000)
#define GPIO_PIN_13                     ((uint16_t)0x2000)
#define GPIO_PIN_14                     ((uint16_t)0x4000)
#define GPIO_PIN_15                     ((uint16_t)0x8000)
#define GPIO_PIN_ALL                    ((uint16_t)0xFFFF)

/**
  * @}
  */

/** @defgroup GPIO_Remap_define
  * @{
  */
#define GPIO_REMAP_SPI1                 ((uint32_t)0x00000001)
#define GPIO_REMAP_I2C1                 ((uint32_t)0x00000002)
#define GPIO_REMAP_USART1               ((uint32_t)0x00000004)
#define GPIO_REMAP_USART2               ((uint32_t)0x00000008)
#define GPIO_PARTIAL_REMAP_USART3       ((uint32_t)0x00140010)
#define GPIO_FULL_REMAP_USART3          ((uint32_t)0x00140030)
#define GPIO_PARTIAL_REMAP_TIMER1       ((uint32_t)0x00160040)
#define GPIO_FULL_REMAP_TIMER1          ((uint32_t)0x001600C0)
#define GPIO_PARTIAL_REMAP1_TIMER2      ((uint32_t)0x00180100)
#define GPIO_PARTIAL_REMAP2_TIMER2      ((uint32_t)0x00180200)
#define GPIO_FULL_REMAP_TIMER2          ((uint32_t)0x00180300)
#define GPIO_PARTIAL_REMAP_TIMER3       ((uint32_t)0x001A0800)
#define GPIO_FULL_REMAP_TIMER3          ((uint32_t)0x001A0C00)
#define GPIO_REMAP_TIMER4               ((uint32_t)0x00001000)
#define GPIO_REMAP1_CAN1                ((uint32_t)0x001D4000)
#define GPIO_REMAP2_CAN1                ((uint32_t)0x001D6000)
#define GPIO_REMAP_PD01                 ((uint32_t)0x00008000)
#define GPIO_REMAP_TIMER5CH4_LSI        ((uint32_t)0x00200001)
#define GPIO_REMAP_ADC1_ETRGINJ         ((uint32_t)0x00200002)
#define GPIO_REMAP_ADC1_ETRGREG         ((uint32_t)0x00200004)
#define GPIO_REMAP_ADC2_ETRGINJ         ((uint32_t)0x00200008)
#define GPIO_REMAP_ADC2_ETRGREG         ((uint32_t)0x00200010)
#define GPIO_REMAP_ETH                  ((uint32_t)0x00200020)
#define GPIO_REMAP_CAN2                 ((uint32_t)0x00200040)
#define GPIO_REMAP_SWJ_NOJTRST          ((uint32_t)0x00300100)
#define GPIO_REMAP_SWJ_JTAGDISABLE      ((uint32_t)0x00300200)
#define GPIO_REMAP_SWJ_DISABLE          ((uint32_t)0x00300400)
#define GPIO_REMAP_SPI3                 ((uint32_t)0x00201100)
#define GPIO_REMAP_TIMER2ITR1_PTP_SOF   ((uint32_t)0x00202000)
#define GPIO_REMAP_PTP_PPS              ((uint32_t)0x00204000)
#define GPIO_REMAP_TIMER15              ((uint32_t)0x80000001)
#define GPIO_REMAP_TIMER16              ((uint32_t)0x80000002)
#define GPIO_REMAP_TIMER17              ((uint32_t)0x80000004)
#define GPIO_REMAP_CEC                  ((uint32_t)0x80000008)
#define GPIO_REMAP_TIMER1_DMA           ((uint32_t)0x80000010)
#define GPIO_REMAP_TIMER9               ((uint32_t)0x80000020)
#define GPIO_REMAP_TIMER10              ((uint32_t)0x80000040)
#define GPIO_REMAP_TIMER11              ((uint32_t)0x80000080)
#define GPIO_REMAP_TIMER13              ((uint32_t)0x80000100)
#define GPIO_REMAP_TIMER14              ((uint32_t)0x80000200)
#define GPIO_REMAP_EXMC_NADV            ((uint32_t)0x80000400)
#define GPIO_REMAP_TIMER67_DAC_DMA      ((uint32_t)0x80000800)
#define GPIO_REMAP_TIMER12              ((uint32_t)0x80001000)
#define GPIO_REMAP_MISC                 ((uint32_t)0x80002000)

/**
  * @}
  */

/** @defgroup GPIO_Port_Sources
  * @{
  */
#define GPIO_PORT_SOURCE_GPIOA           ((uint8_t)0x00)
#define GPIO_PORT_SOURCE_GPIOB           ((uint8_t)0x01)
#define GPIO_PORT_SOURCE_GPIOC           ((uint8_t)0x02)
#define GPIO_PORT_SOURCE_GPIOD           ((uint8_t)0x03)
#define GPIO_PORT_SOURCE_GPIOE           ((uint8_t)0x04)
#define GPIO_PORT_SOURCE_GPIOF           ((uint8_t)0x05)
#define GPIO_PORT_SOURCE_GPIOG           ((uint8_t)0x06)

/**
  * @}
  */

/** @defgroup GPIO_Pin_sources
  * @{
  */
#define GPIO_PINSOURCE0                 ((uint8_t)0x00)
#define GPIO_PINSOURCE1                 ((uint8_t)0x01)
#define GPIO_PINSOURCE2                 ((uint8_t)0x02)
#define GPIO_PINSOURCE3                 ((uint8_t)0x03)
#define GPIO_PINSOURCE4                 ((uint8_t)0x04)
#define GPIO_PINSOURCE5                 ((uint8_t)0x05)
#define GPIO_PINSOURCE6                 ((uint8_t)0x06)
#define GPIO_PINSOURCE7                 ((uint8_t)0x07)
#define GPIO_PINSOURCE8                 ((uint8_t)0x08)
#define GPIO_PINSOURCE9                 ((uint8_t)0x09)
#define GPIO_PINSOURCE10                ((uint8_t)0x0A)
#define GPIO_PINSOURCE11                ((uint8_t)0x0B)
#define GPIO_PINSOURCE12                ((uint8_t)0x0C)
#define GPIO_PINSOURCE13                ((uint8_t)0x0D)
#define GPIO_PINSOURCE14                ((uint8_t)0x0E)
#define GPIO_PINSOURCE15                ((uint8_t)0x0F)

/**
  * @}
  */

/** @defgroup Ethernet_Media_Interface
  * @{
  */
#define GPIO_ETH_MEDIAINTERFACE_MII    ((uint32_t)0x00000000)
#define GPIO_ETH_MEDIAINTERFACE_RMII   ((uint32_t)0x00800000)

/**
  * @}
  */

/* output mode definitions */
#define CTL_CLTR(regval)           (BITS(0,1) & ((uint32_t)(regval) << 0))
#define GPIO_MODE_INPUT            CTL_CLTR(0)           /*!< input mode */
#define GPIO_MODE_OUTPUT           CTL_CLTR(1)           /*!< output mode */
#define GPIO_MODE_AF               CTL_CLTR(2)           /*!< alternate function mode */
#define GPIO_MODE_ANALOG           CTL_CLTR(3)           /*!< analog mode */

/** @defgroup AFIO_Event_Output
  * @{
  */
#define AFIO_ECR_EVOE_SET               ((uint32_t)0x00000080)
#define AFIO_ECR_EVOE_RESET             ((uint32_t)0xffffff7f)

/* gpio alternate function */
#define AF(regval)                 (BITS(0,3) & ((uint32_t)(regval) << 0))
#define GPIO_AF_0                   AF(0)                /*!< alternate function selected 0 */
#define GPIO_AF_1                   AF(1)                /*!< alternate function selected 1 */
#define GPIO_AF_2                   AF(2)                /*!< alternate function selected 2 */
#define GPIO_AF_3                   AF(3)                /*!< alternate function selected 3 */
#define GPIO_AF_4                   AF(4)                /*!< alternate function selected 4 */
#define GPIO_AF_5                   AF(5)                /*!< alternate function selected 5 */
#define GPIO_AF_6                   AF(6)                /*!< alternate function selected 6 */
#define GPIO_AF_7                   AF(7)                /*!< alternate function selected 7 */
#define GPIO_AF_8                   AF(8)                /*!< alternate function selected 8 */
#define GPIO_AF_9                   AF(9)                /*!< alternate function selected 9 */
#define GPIO_AF_10                  AF(10)               /*!< alternate function selected 10 */
#define GPIO_AF_11                  AF(11)               /*!< alternate function selected 11 */
#define GPIO_AF_12                  AF(12)               /*!< alternate function selected 12 */
#define GPIO_AF_13                  AF(13)               /*!< alternate function selected 13 */
#define GPIO_AF_14                  AF(14)               /*!< alternate function selected 14 */
#define GPIO_AF_15                  AF(15)               /*!< alternate function selected 15 */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions
  * @{
  */
void GPIO_DeInit(GPIO_TypeDef *GPIOx);
void GPIO_AFDeInit(void);
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitPara *GPIO_InitStruct);
void GPIO_ParaInit(GPIO_InitPara *GPIO_InitStruct);
uint8_t GPIO_ReadInputBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);
uint8_t GPIO_ReadOutputBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitState BitVal);
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputEnable(TypeState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, TypeState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F10X_GPIO_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
