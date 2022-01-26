/**
******************************************************************************
* @file  HAL_gpio.h
* @author  IC Applications Department
* @version  V0.8
* @date  2019_08_02
* @brief  This file contains all the functions prototypes for the GPIO
*         firmware library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, HOLOCENE SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 HOLOCENE</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup GPIO
* @{
*/

/** @defgroup GPIO_Exported_Types
* @{
*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == GPIOA_BASE) || \
((*(uint32_t*)&(PERIPH)) == GPIOB_BASE) || \
  ((*(uint32_t*)&(PERIPH)) == GPIOC_BASE) || \
    ((*(uint32_t*)&(PERIPH)) == GPIOD_BASE) || \
      ((*(uint32_t*)&(PERIPH)) == GPIOE_BASE) || \
        ((*(uint32_t*)&(PERIPH)) == GPIOF_BASE) || \
          ((*(uint32_t*)&(PERIPH)) == GPIOG_BASE))

/**
* @brief  Output Maximum frequency selection
*/

typedef enum
{
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz,
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz) || \
((SPEED) == GPIO_Speed_50MHz))

/**
* @brief  Configuration Mode enumeration
*/

typedef enum
{
GPIO_Mode_AIN = 0x0,  //模拟输入
GPIO_Mode_IN_FLOATING = 0x04, //浮空输入
GPIO_Mode_IPD = 0x28,  //下拉输入
GPIO_Mode_IPU = 0x48,  //上拉输入
GPIO_Mode_Out_OD = 0x14,//通用开漏输出
GPIO_Mode_Out_PP = 0x10,//通用推免输出
GPIO_Mode_AF_OD = 0x1C, // 复用开漏输出
GPIO_Mode_AF_PP = 0x18  //复用推免输出
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || \
((MODE) == GPIO_Mode_IPD) || ((MODE) == GPIO_Mode_IPU) || \
  ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP) || \
    ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))

/**
* @brief  GPIO Init structure definition
*/

typedef struct
{
  uint32_t GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
}GPIO_InitTypeDef;

/**
* @brief  Bit_SET and Bit_RESET enumeration
*/

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

/**
* @}
*/

/** @defgroup GPIO_Exported_Constants
* @{
*/

/** @defgroup GPIO_pins_define
* @{
*/

#define GPIO_Pin_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /* Pin 15 selected */

#define GPIO_Pin_16              ((uint32_t)0x010000)  /* Pin 16 selected */
#define GPIO_Pin_17              ((uint32_t)0x020000)  /* Pin 17 selected */
#define GPIO_Pin_18              ((uint32_t)0x040000)  /* Pin 18 selected */
#define GPIO_Pin_19              ((uint32_t)0x080000)  /* Pin 19 selected */
#define GPIO_Pin_20              ((uint32_t)0x100000)  /* Pin 20 selected */
#define GPIO_Pin_21              ((uint32_t)0x200000)  /* Pin 21 selected */
#define GPIO_Pin_22              ((uint32_t)0x400000)  /* Pin 22 selected */
#define GPIO_Pin_23              ((uint32_t)0x800000)  /* Pin 23 selected */
#define GPIO_Pin_All             ((uint32_t)0xFFFFFF)  /* All pins selected */

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
((PIN) == GPIO_Pin_1) || \
  ((PIN) == GPIO_Pin_2) || \
    ((PIN) == GPIO_Pin_3) || \
      ((PIN) == GPIO_Pin_4) || \
        ((PIN) == GPIO_Pin_5) || \
          ((PIN) == GPIO_Pin_6) || \
            ((PIN) == GPIO_Pin_7) || \
              ((PIN) == GPIO_Pin_8) || \
                ((PIN) == GPIO_Pin_9) || \
                  ((PIN) == GPIO_Pin_10) || \
                    ((PIN) == GPIO_Pin_11) || \
                      ((PIN) == GPIO_Pin_12) || \
                        ((PIN) == GPIO_Pin_13) || \
                          ((PIN) == GPIO_Pin_14) || \
                            ((PIN) == GPIO_Pin_15))

/**
* @}
*/

/** @defgroup GPIO_Remap_define
* @{
*/

#define GPIO_Remap_SPI1            ((uint32_t)0x00000001)  /* SPI1 Alternate Function mapping */
#define GPIO_Remap_I2C1            ((uint32_t)0x00000002)  /* I2C1 Alternate Function mapping */
#define GPIO_Remap_UART1          ((uint32_t)0x00000004)  /* UART1 Alternate Function mapping */


#define GPIO_PartialRemap_TIM1     ((uint32_t)0x00160040)  /* TIM1 Partial Alternate Function mapping */
#define GPIO_FullRemap_TIM1        ((uint32_t)0x001600C0)  /* TIM1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_TIM2    ((uint32_t)0x00180100)  /* TIM2 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_TIM2    ((uint32_t)0x00180200)  /* TIM2 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_TIM2        ((uint32_t)0x00180300)  /* TIM2 Full Alternate Function mapping */
#define GPIO_PartialRemap_TIM3     ((uint32_t)0x001A0800)  /* TIM3 Partial Alternate Function mapping */
#define GPIO_FullRemap_TIM3        ((uint32_t)0x001A0C00)  /* TIM3 Full Alternate Function mapping */


#define GPIO_Remap_PD01            ((uint32_t)0x00008000)  /* PD01 Alternate Function mapping */

#define GPIO_Remap_ADC1_ETRGINJ    ((uint32_t)0x00200002)  /* ADC1 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC1_ETRGREG    ((uint32_t)0x00200004)  /* ADC1 External Trigger Regular Conversion remapping */

#define GPIO_Remap_SWJ_NoJTRST     ((uint32_t)0x00300100)  /* Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define GPIO_Remap_SWJ_JTAGDisable ((uint32_t)0x00300200)  /* JTAG-DP Disabled and SW-DP Enabled */
#define GPIO_Remap_SWJ_Disable     ((uint32_t)0x00300400)  /* Full SWJ Disabled (JTAG-DP + SW-DP) */

#define IS_GPIO_REMAP(REMAP) (((REMAP) == GPIO_Remap_SPI1) || ((REMAP) == GPIO_Remap_I2C1) || \
((REMAP) == GPIO_Remap_UART1) || ((REMAP) == GPIO_PartialRemap_TIM1) || \
   ((REMAP) == GPIO_FullRemap_TIM1) ||  ((REMAP) == GPIO_PartialRemap1_TIM2) ||\
      ((REMAP) == GPIO_PartialRemap2_TIM2) || ((REMAP) == GPIO_FullRemap_TIM2) || \
        ((REMAP) == GPIO_PartialRemap_TIM3) || ((REMAP) == GPIO_FullRemap_TIM3) ||\
           ((REMAP) == GPIO_Remap_TIM4) || ((REMAP) == GPIO_Remap_PD01) || \
                ((REMAP) == GPIO_Remap_ADC1_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC1_ETRGREG) || \
                    ((REMAP) == GPIO_Remap_SWJ_NoJTRST) || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable)|| \
                      ((REMAP) == GPIO_Remap_SWJ_Disable))


/**
* @}
*/
/**
* @}
*/

/** @defgroup GPIO_Alternate_function_selection_define
* @{
*/


#define GPIO_AF_MCO_SW            ((uint8_t)0x00) /* MC0, SWDIO,SWCLK */
#define GPIO_AF_TIM_1_2           ((uint8_t)0x01) /* TIM 1/2 */
#define GPIO_AF_TIM_34567             ((uint8_t)0x02) /* TIM 3/4/5/6/7 */
#define GPIO_AF_I2S               ((uint8_t)0x03)
#define GPIO_AF_I2C               ((uint8_t)0x04) /* I2C 1/2/3 */
#define GPIO_AF_SPI               ((uint8_t)0x05) /* SPI 1/2/3/4 */
#define GPIO_AF_QSPI              ((uint8_t)0x06)
#define GPIO_AF_UART_2345         ((uint8_t)0x07) /* UART 2/3/4/5 */
#define GPIO_AF_UART_1            ((uint8_t)0x08)
#define GPIO_AF_CAN                   ((uint8_t)0x09) /* CAN 1/2 */
#define GPIO_AF_USB                   ((uint8_t)0x0A)
#define GPIO_AF_GPIO                    ((uint8_t)0x0B) /* Normal GPIO */
#define GPIO_AF_TK80_SDIO         ((uint8_t)0x0C) /* TK80   SDIO 1/2 */
#define GPIO_AF_Touchpad          ((uint8_t)0x0D)
#define GPIO_AF_LTDC              ((uint8_t)0x0E) /* RGB_LTDC AF */


#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_0) || ((AF) == GPIO_AF_1) || \
((AF) == GPIO_AF_2) || ((AF) == GPIO_AF_3) || \
  ((AF) == GPIO_AF_4) || ((AF) == GPIO_AF_5) || \
    ((AF) == GPIO_AF_6) || ((AF) == GPIO_AF_7))

/**
* @}
*/

/** @defgroup GPIO_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup GPIO_Exported_Functions
* @{
*/

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, uint8_t GPIO_AF);
#endif /* __HAL_GPIO_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/
