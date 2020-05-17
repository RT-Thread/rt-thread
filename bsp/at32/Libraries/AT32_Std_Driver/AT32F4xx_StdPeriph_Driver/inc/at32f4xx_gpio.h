/**
 **************************************************************************
 * File Name    : at32f4xx_gpio.h
 * Description  : at32f4xx GPIO header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_GPIO_H
#define __AT32F4xx_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types
  * @{
  */

#if defined (AT32F413xx) || defined (AT32F415xx)
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOF))
#elif defined AT32F403xx
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE))
#endif

                                     
/** 
  * @brief  Output Maximum frequency selection  
  */

typedef enum
{ 
  GPIO_MaxSpeed_10MHz = 1,
  GPIO_MaxSpeed_2MHz,
  GPIO_MaxSpeed_50MHz = 2
}GPIOMaxSpeed_Type;
#define IS_GPIO_MAXSPEED(MAXSPEED) (((MAXSPEED) == GPIO_MaxSpeed_10MHz) ||\
                                    ((MAXSPEED) == GPIO_MaxSpeed_2MHz)  || \
                                    ((MAXSPEED) == GPIO_MaxSpeed_50MHz))

/** 
  * @brief  Configuration Mode enumeration  
  */

typedef enum
{ GPIO_Mode_IN_ANALOG = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IN_PD = 0x28,
  GPIO_Mode_IN_PU = 0x48,
  GPIO_Mode_OUT_OD = 0x14,
  GPIO_Mode_OUT_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_Type;

#define IS_GPIO_MDE(MDE) (((MDE) == GPIO_Mode_IN_ANALOG) || ((MDE) == GPIO_Mode_IN_FLOATING) || \
                          ((MDE) == GPIO_Mode_IN_PD)     || ((MDE) == GPIO_Mode_IN_PU)       || \
                          ((MDE) == GPIO_Mode_OUT_OD)    || ((MDE) == GPIO_Mode_OUT_PP)      || \
                          ((MDE) == GPIO_Mode_AF_OD)     || ((MDE) == GPIO_Mode_AF_PP))

/** 
  * @brief  GPIO Init structure definition  
  */

typedef struct
{
  uint16_t GPIO_Pins;               /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIOMaxSpeed_Type GPIO_MaxSpeed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOMaxSpeed_Type */

  GPIOMode_Type GPIO_Mode;          /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_Type */
}GPIO_InitType;


/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitState;

#define IS_GPIO_BIT_STATE(STATE) (((STATE) == Bit_RESET) || ((STATE) == Bit_SET))

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define 
  * @{
  */

#define GPIO_Pins_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define GPIO_Pins_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define GPIO_Pins_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define GPIO_Pins_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define GPIO_Pins_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define GPIO_Pins_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define GPIO_Pins_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define GPIO_Pins_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define GPIO_Pins_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define GPIO_Pins_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define GPIO_Pins_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pins_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pins_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pins_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pins_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pins_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pins_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_GPIO_PINS(PINS) ((((PINS) & (uint16_t)0x00) == 0x00) && ((PINS) != (uint16_t)0x00))

#define IS_GET_GPIO_PINS(PINS)      (((PINS) == GPIO_Pins_0)  || \
                                     ((PINS) == GPIO_Pins_1)  || \
                                     ((PINS) == GPIO_Pins_2)  || \
                                     ((PINS) == GPIO_Pins_3)  || \
                                     ((PINS) == GPIO_Pins_4)  || \
                                     ((PINS) == GPIO_Pins_5)  || \
                                     ((PINS) == GPIO_Pins_6)  || \
                                     ((PINS) == GPIO_Pins_7)  || \
                                     ((PINS) == GPIO_Pins_8)  || \
                                     ((PINS) == GPIO_Pins_9)  || \
                                     ((PINS) == GPIO_Pins_10) || \
                                     ((PINS) == GPIO_Pins_11) || \
                                     ((PINS) == GPIO_Pins_12) || \
                                     ((PINS) == GPIO_Pins_13) || \
                                     ((PINS) == GPIO_Pins_14) || \
                                     ((PINS) == GPIO_Pins_15))

/**
  * @}
  */

#if defined (AT32F403xx) || defined (AT32F413xx)|| defined (AT32F415xx) || defined (AT32F403Axx) || defined (AT32F407xx)
/** @defgroup GPIO_Remap_define 
  * @{
  */
  
/** @defgroup AFIO_MAP_define
  * @{
  */
#define GPIO_Remap01_SPI1           ((uint32_t)0x00000001)  /*!< SPI1 Alternate Function mapping 01 */
#define GPIO_Remap_I2C1             ((uint32_t)0x00000002)  /*!< I2C1 Alternate Function mapping */
#define GPIO_Remap_USART1           ((uint32_t)0x00000004)  /*!< USART1 Alternate Function mapping */
#define GPIO_PartialRemap_USART3    ((uint32_t)0x00000010)  /*!< USART3 Partial Alternate Function mapping */
#define GPIO_PartialRemap_TMR1      ((uint32_t)0x00000040)  /*!< TMR1 Partial Alternate Function mapping */
#define GPIO_PartialRemap1_TMR2     ((uint32_t)0x00000100)  /*!< TMR2 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_TMR2     ((uint32_t)0x00000200)  /*!< TMR2 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_TMR2         ((uint32_t)0x00000300)  /*!< TMR2 Full Alternate Function mapping */
#define GPIO_PartialRemap_TMR3      ((uint32_t)0x00000800)  /*!< TMR3 Partial Alternate Function mapping */
#define GPIO_FullRemap_TMR3         ((uint32_t)0x00000C00)  /*!< TMR3 Full Alternate Function mapping */
#define GPIO_Remap1_CAN1            ((uint32_t)0x00004000)  /*!< CAN1 Alternate Function mapping */
#define GPIO_Remap_PD01             ((uint32_t)0x00008000)  /*!< PD01 Alternate Function mapping */
#define GPIO_Remap_TMR5CH4_LSI      ((uint32_t)0x00010000)  /*!< LSI connected to TMR5 Channel4 input capture for calibration */
#define GPIO_Remap_ADC1_EXTRGINJ    ((uint32_t)0x00020000)  /*!< ADC1 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC1_EXTRGREG    ((uint32_t)0x00040000)  /*!< ADC1 External Trigger Regular Conversion remapping */
#define GPIO_Remap_SWJ_NoJNTRST     ((uint32_t)0x01000000)  /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x02000000)  /*!< JTAG-DP Disabled and SW-DP Enabled */
#define GPIO_Remap_SWJ_AllDisable   ((uint32_t)0x04000000)  /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */
#ifdef AT32F403xx
#define GPIO_Remap10_SPI1           ((uint32_t)0x80000000)  /*!< SPI1 Alternate Function mapping 10*/
#define GPIO_Remap_USART2           ((uint32_t)0x00000008)  /*!< USART2 Alternate Function mapping */
#define GPIO_FullRemap_USART3       ((uint32_t)0x00000030)  /*!< USART3 Full Alternate Function mapping */
#define GPIO_FullRemap_TMR1         ((uint32_t)0x000000C0)  /*!< TMR1 Full Alternate Function mapping */
#define GPIO_Remap_TMR4             ((uint32_t)0x00001000)  /*!< TMR4 Alternate Function mapping */
#define GPIO_Remap2_CAN1            ((uint32_t)0x00006000)  /*!< CAN1 Alternate Function mapping */
#define GPIO_Remap_ADC2_EXTRGINJ    ((uint32_t)0x00080000)  /*!< ADC2 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC2_EXTRGREG    ((uint32_t)0x00100000)  /*!< ADC2 External Trigger Regular Conversion remapping */
#elif defined (AT32F413xx)
#define GPIO_Remap_ADC2_EXTRGINJ    ((uint32_t)0x00080000)  /*!< ADC2 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC2_EXTRGREG    ((uint32_t)0x00100000)  /*!< ADC2 External Trigger Regular Conversion remapping */
#elif defined (AT32F415xx)
#define GPIO_PartialRemap2_USART3   ((uint32_t)0x00000020)  /*!< EXT_FLASH Alternate Function mapping*/
#define GPIO_PartialRemap2_TMR1     ((uint32_t)0x00000080)  /*!< TMR1 Partial2 Alternate Function mapping */
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define GPIO_Remap_USART2           ((uint32_t)0x00000008)  /*!< USART2 Alternate Function mapping */
#define GPIO_FullRemap_USART3       ((uint32_t)0x00000030)  /*!< USART3 Full Alternate Function mapping */
#define GPIO_FullRemap_TMR1         ((uint32_t)0x000000C0)  /*!< TMR1 Full Alternate Function mapping */
#define GPIO_Remap_TMR4             ((uint32_t)0x00001000)  /*!< TMR4 Alternate Function mapping */
#define GPIO_Remap2_CAN1            ((uint32_t)0x00006000)  /*!< CAN1 Alternate Function mapping */
#define GPIO_Remap_ADC2_EXTRGINJ    ((uint32_t)0x00080000)  /*!< ADC2 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC2_EXTRGREG    ((uint32_t)0x00100000)  /*!< ADC2 External Trigger Regular Conversion remapping */
#define GPIO_Remap_ETH              ((uint32_t)0x00200000)  /*!< ETH Alternate Function mapping*/
#define GPIO_Remap_CAN2             ((uint32_t)0x00400000)  /*!< CAN2 Alternate Function mapping*/
#define GPIO_Remap_MII_RMII         ((uint32_t)0x00800000)  /*!< MII or RMII Alternate Function mapping */
#define GPIO_Remap_SPI3             ((uint32_t)0x10000000)  /*!< SPI3 Alternate Function mapping*/
#define GPIO_Remap_TMR2ITR1         ((uint32_t)0x20000000)  /*!< TMR2 internal trigger 1 Alternate remapping    */
#define GPIO_Remap_PTP_PPS          ((uint32_t)0x40000000)  /*!< Ethernet PTP PPS Alternate Function remapping  */
#endif
/**
  * @}
  */
  
/** @defgroup AFIO_MAP2_define
  * @{
  */
#ifdef AT32F403xx
#define GPIO_Remap_TMR15            ((uint32_t)0x40000001)  /*!< TMR15 Alternate Function mapping  */
#define GPIO_Remap_TMR9             ((uint32_t)0x40000020)  /*!< TMR9 Alternate Function mapping  */
#define GPIO_Remap_TMR10            ((uint32_t)0x40000040)  /*!< TMR10 Alternate Function mapping  */
#define GPIO_Remap_TMR11            ((uint32_t)0x40000080)  /*!< TMR11 Alternate Function mapping  */
#define GPIO_Remap_TMR13            ((uint32_t)0x40000100)  /*!< TMR13 Alternate Function mapping  */
#define GPIO_Remap_TMR14            ((uint32_t)0x40000200)  /*!< TMR14 Alternate Function mapping  */
#define GPIO_Remap_XMC_NADV         ((uint32_t)0x40000400)  /*!< XMC_NADV Alternate Function mapping  */
#define GPIO_Remap_SPI4             ((uint32_t)0x40020000)  /*!< SPI4 Alternate Function mapping*/
#define GPIO_Remap_I2C3             ((uint32_t)0x40040000)  /*!< I2C3 Alternate Function mapping*/
#define GPIO_Remap01_SDIO2          ((uint32_t)0x40080000)  /*!< SDIO2 Alternate Function mapping 01:CK/CMD Remaped None,D0~D3 Remaped to PA4~PA7*/
#define GPIO_Remap10_SDIO2          ((uint32_t)0x40100000)  /*!< SDIO2 Alternate Function mapping 10:CK/CMD Remaped to PA2/PA3,D0~D3 Remaped None*/
#define GPIO_Remap11_SDIO2          ((uint32_t)0x40180000)  /*!< SDIO2 Alternate Function mapping 11:CK/CMD Remaped to PA2/PA3,D0~D3 Remaped to PA4~PA7*/
#define GPIO_Remap_EXT_FLASH        ((uint32_t)0x40200000)  /*!< EXT_FLASH Alternate Function mapping*/
#elif defined (AT32F413xx)
#define GPIO_Remap_EXT_FLASH        ((uint32_t)0x40200000)  /*!< EXT_FLASH Alternate Function mapping*/
#elif defined (AT32F415xx)
#define GPIO_Remap01_COMP           ((uint32_t)0x44000000)  /*!< COMP1/2 Alternate Function mapping 01: COMP1/2_OUT connect to PA6/7*/
#define GPIO_Remap10_COMP           ((uint32_t)0x48000000)  /*!< COMP1/2 Alternate Function mapping 10: COMP1/2_OUT connect to PA11/12*/
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define GPIO_Remap_TMR9             ((uint32_t)0x40000020)  /*!< TMR9 Alternate Function mapping  */
#define GPIO_Remap_XMC_NADV         ((uint32_t)0x40000400)  /*!< XMC_NADV Alternate Function mapping  */
#define GPIO_Remap_SPI4             ((uint32_t)0x40020000)  /*!< SPI4 Alternate Function mapping*/
#define GPIO_Remap_I2C3             ((uint32_t)0x40040000)  /*!< I2C3 Alternate Function mapping*/
#define GPIO_Remap01_SDIO2          ((uint32_t)0x40080000)  /*!< SDIO2 Alternate Function mapping 01:CK/CMD Remaped None,D0~D3 Remaped to PA4~PA7*/
#define GPIO_Remap10_SDIO2          ((uint32_t)0x40100000)  /*!< SDIO2 Alternate Function mapping 10:CK/CMD Remaped to PA2/PA3,D0~D3 Remaped None*/
#define GPIO_Remap11_SDIO2          ((uint32_t)0x40180000)  /*!< SDIO2 Alternate Function mapping 11:CK/CMD Remaped to PA2/PA3,D0~D3 Remaped to PA4~PA7*/
#define GPIO_Remap_EXT_FLASH        ((uint32_t)0x40200000)  /*!< EXT_FLASH Alternate Function mapping*/
#endif
/**
  * @}
  */
  
#ifdef AT32F403xx
#define IS_GPIO_REMAP(REMAP)        (((REMAP) == GPIO_Remap01_SPI1)         || ((REMAP) == GPIO_Remap_I2C1)           || \
                                     ((REMAP) == GPIO_Remap_USART1)         || ((REMAP) == GPIO_Remap_USART2)         || \
                                     ((REMAP) == GPIO_PartialRemap_USART3)  || ((REMAP) == GPIO_FullRemap_USART3)     || \
                                     ((REMAP) == GPIO_PartialRemap_TMR1)    || ((REMAP) == GPIO_FullRemap_TMR1)       || \
                                     ((REMAP) == GPIO_PartialRemap1_TMR2)   || ((REMAP) == GPIO_PartialRemap2_TMR2)   || \
                                     ((REMAP) == GPIO_FullRemap_TMR2)       || ((REMAP) == GPIO_PartialRemap_TMR3)    || \
                                     ((REMAP) == GPIO_FullRemap_TMR3)       || ((REMAP) == GPIO_Remap_TMR4)           || \
                                     ((REMAP) == GPIO_Remap1_CAN1)          || ((REMAP) == GPIO_Remap2_CAN1)          || \
                                     ((REMAP) == GPIO_Remap_PD01)           || ((REMAP) == GPIO_Remap_TMR5CH4_LSI)    || \
                                     ((REMAP) == GPIO_Remap_ADC1_EXTRGINJ)  || ((REMAP) == GPIO_Remap_ADC1_EXTRGREG)  || \
                                     ((REMAP) == GPIO_Remap_ADC2_EXTRGINJ)  || ((REMAP) == GPIO_Remap_ADC2_EXTRGREG)  || \
                                     ((REMAP) == GPIO_Remap_SWJ_NoJNTRST)   || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable)|| \
                                     ((REMAP) == GPIO_Remap_SWJ_AllDisable) || ((REMAP) == GPIO_Remap10_SPI1)         || \
                                     ((REMAP) == GPIO_Remap_TMR15)          || ((REMAP) == GPIO_Remap_TMR9)           || \
                                     ((REMAP) == GPIO_Remap_TMR10)          || ((REMAP) == GPIO_Remap_TMR11)          || \
                                     ((REMAP) == GPIO_Remap_TMR13)          || ((REMAP) == GPIO_Remap_TMR14)          || \
                                     ((REMAP) == GPIO_Remap_XMC_NADV)       || ((REMAP) == GPIO_Remap_SPI4)           || \
                                     ((REMAP) == GPIO_Remap_I2C3)           || ((REMAP) == GPIO_Remap01_SDIO2)        || \
                                     ((REMAP) == GPIO_Remap10_SDIO2)        || ((REMAP) == GPIO_Remap11_SDIO2)        || \
                                     ((REMAP) == GPIO_Remap_EXT_FLASH))
#elif defined (AT32F413xx)
#define IS_GPIO_REMAP(REMAP)        (((REMAP) == GPIO_Remap01_SPI1)         || ((REMAP) == GPIO_Remap_I2C1)           || \
                                     ((REMAP) == GPIO_Remap_USART1)         || ((REMAP) == GPIO_PartialRemap_USART3)  || \
                                     ((REMAP) == GPIO_PartialRemap_TMR1)    || ((REMAP) == GPIO_PartialRemap1_TMR2)   || \
                                     ((REMAP) == GPIO_PartialRemap2_TMR2)   || ((REMAP) == GPIO_FullRemap_TMR2)       || \
                                     ((REMAP) == GPIO_PartialRemap_TMR3)    || ((REMAP) == GPIO_FullRemap_TMR3)       || \
                                     ((REMAP) == GPIO_Remap1_CAN1)          || ((REMAP) == GPIO_Remap_EXT_FLASH)      || \
                                     ((REMAP) == GPIO_Remap_PD01)           || ((REMAP) == GPIO_Remap_TMR5CH4_LSI)    || \
                                     ((REMAP) == GPIO_Remap_ADC1_EXTRGINJ)  || ((REMAP) == GPIO_Remap_ADC1_EXTRGREG)  || \
                                     ((REMAP) == GPIO_Remap_ADC2_EXTRGINJ)  || ((REMAP) == GPIO_Remap_ADC2_EXTRGREG)  || \
                                     ((REMAP) == GPIO_Remap_SWJ_NoJNTRST)   || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable)|| \
                                     ((REMAP) == GPIO_Remap_SWJ_AllDisable))
#elif defined (AT32F415xx)
#define IS_GPIO_REMAP(REMAP)        (((REMAP) == GPIO_Remap01_SPI1)         || ((REMAP) == GPIO_Remap_I2C1)           || \
                                     ((REMAP) == GPIO_Remap_USART1)         || ((REMAP) == GPIO_PartialRemap_USART3)  || \
                                     ((REMAP) == GPIO_PartialRemap_TMR1)    || ((REMAP) == GPIO_PartialRemap1_TMR2)   || \
                                     ((REMAP) == GPIO_PartialRemap2_TMR2)   || ((REMAP) == GPIO_FullRemap_TMR2)       || \
                                     ((REMAP) == GPIO_PartialRemap_TMR3)    || ((REMAP) == GPIO_FullRemap_TMR3)       || \
                                     ((REMAP) == GPIO_Remap1_CAN1)          || ((REMAP) == GPIO_Remap_PD01)           || \
                                     ((REMAP) == GPIO_Remap_TMR5CH4_LSI)    || ((REMAP) == GPIO_Remap_ADC1_EXTRGINJ)  || \
                                     ((REMAP) == GPIO_Remap_ADC1_EXTRGREG)  || ((REMAP) == GPIO_Remap_SWJ_NoJNTRST)   || \
                                     ((REMAP) == GPIO_Remap_SWJ_JTAGDisable)|| ((REMAP) == GPIO_Remap_SWJ_AllDisable) || \
                                     ((REMAP) == GPIO_Remap01_COMP)         || ((REMAP) == GPIO_Remap10_COMP)         || \
                                     ((REMAP) == GPIO_PartialRemap2_USART3) || ((REMAP) == GPIO_PartialRemap2_TMR1))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_GPIO_REMAP(REMAP)        (((REMAP) == GPIO_Remap01_SPI1)         || ((REMAP) == GPIO_Remap_I2C1)           || \
                                     ((REMAP) == GPIO_Remap_USART1)         || ((REMAP) == GPIO_Remap_USART2)         || \
                                     ((REMAP) == GPIO_PartialRemap_USART3)  || ((REMAP) == GPIO_FullRemap_USART3)     || \
                                     ((REMAP) == GPIO_PartialRemap_TMR1)    || ((REMAP) == GPIO_FullRemap_TMR1)       || \
                                     ((REMAP) == GPIO_PartialRemap1_TMR2)   || ((REMAP) == GPIO_PartialRemap2_TMR2)   || \
                                     ((REMAP) == GPIO_FullRemap_TMR2)       || ((REMAP) == GPIO_PartialRemap_TMR3)    || \
                                     ((REMAP) == GPIO_FullRemap_TMR3)       || ((REMAP) == GPIO_Remap_TMR4)           || \
                                     ((REMAP) == GPIO_Remap1_CAN1)          || ((REMAP) == GPIO_Remap2_CAN1)          || \
                                     ((REMAP) == GPIO_Remap_PD01)           || ((REMAP) == GPIO_Remap_TMR5CH4_LSI)    || \
                                     ((REMAP) == GPIO_Remap_ADC1_EXTRGINJ)  || ((REMAP) == GPIO_Remap_ADC1_EXTRGREG)  || \
                                     ((REMAP) == GPIO_Remap_ADC2_EXTRGINJ)  || ((REMAP) == GPIO_Remap_ADC2_EXTRGREG)  || \
                                     ((REMAP) == GPIO_Remap_SWJ_NoJNTRST)   || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable)|| \
                                     ((REMAP) == GPIO_Remap_SWJ_AllDisable) || ((REMAP) == GPIO_Remap_EXT_FLASH)      || \
                                     ((REMAP) == GPIO_Remap_PTP_PPS)        || ((REMAP) == GPIO_Remap_TMR2ITR1)       || \
                                     ((REMAP) == GPIO_Remap_SPI3)           || ((REMAP) == GPIO_Remap_MII_RMII)       || \
                                     ((REMAP) == GPIO_Remap_CAN2)           || ((REMAP) == GPIO_Remap_ETH)            || \
                                     ((REMAP) == GPIO_Remap_TMR9)           || ((REMAP) == GPIO_Remap_XMC_NADV)       || \
                                     ((REMAP) == GPIO_Remap_SPI4)           || ((REMAP) == GPIO_Remap_I2C3)           || \
                                     ((REMAP) == GPIO_Remap01_SDIO2)        || ((REMAP) == GPIO_Remap10_SDIO2)        || \
                                     ((REMAP) == GPIO_Remap11_SDIO2))
                                     
#endif
                              
/**
  * @}
  */ 
#endif

#if !defined(AT32F403xx)

#define AFIO_MAP3     0x00
#define AFIO_MAP4     0x01
#define AFIO_MAP5     0x02
#define AFIO_MAP6     0x03
#define AFIO_MAP7     0x04
#if defined (AT32F415xx) || defined (AT32F403Axx) || defined (AT32F407xx)
#define AFIO_MAP8     0x05
#endif

#define BITS0         0x00
#define BITS1         0x01
#define BITS2         0x02
#define BITS3         0x03
#define BITS4         0x04
#define BITS5         0x05
#define BITS6         0x06
#define BITS7         0x07

#define OFFSET_MASK0  0xFFFFFFF0
#define OFFSET_MASK1  0xFFFFFF0F
#define OFFSET_MASK2  0xFFFFF0FF
#define OFFSET_MASK3  0xFFFF0FFF
#define OFFSET_MASK4  0xFFF0FFFF
#define OFFSET_MASK5  0xFF0FFFFF
#define OFFSET_MASK6  0xF0FFFFFF
#define OFFSET_MASK7  0x0FFFFFFF

/** @defgroup AFIO_MAP3_4_5_6_7_8_define 
  * @{ 
  */
#define AFIO_MAP3_TMR9_0010         ((uint32_t)0x80000002)  /*!< TMR9 Alternate Function mapping  */
#define AFIO_MAP3_TMR10_0010        ((uint32_t)0x80000012)  /*!< TMR10 Alternate Function mapping  */
#define AFIO_MAP3_TMR11_0010        ((uint32_t)0x80000022)  /*!< TMR11 Alternate Function mapping  */

#define AFIO_MAP4_TMR1_0001         ((uint32_t)0x80000081)  /*!< TMR1 Alternate Function mapping */
#define AFIO_MAP4_TMR3_0010         ((uint32_t)0x800000A2)  /*!< TMR3 Alternate Function mapping 0010*/
#define AFIO_MAP4_TMR3_0011         ((uint32_t)0x800000A3)  /*!< TMR3 Alternate Function mapping 0011*/
#define AFIO_MAP4_TMR5_1000         ((uint32_t)0x800000C8)  /*!< TMR5 Alternate Function mapping 1000: CH4 */

#define AFIO_MAP5_USART5_0001       ((uint32_t)0x80000101)  /*!< USART5 Alternate Function mapping 0001*/
#define AFIO_MAP5_I2C1_0001         ((uint32_t)0x80000111)  /*!< I2C1 Alternate Function mapping 0001*/
#define AFIO_MAP5_I2C1_0011         ((uint32_t)0x80000113)  /*!< I2C1 Alternate Function mapping 0011*/
#define AFIO_MAP5_I2C2_0001         ((uint32_t)0x80000121)  /*!< I2C2 Alternate Function mapping 0001*/
#define AFIO_MAP5_I2C2_0010         ((uint32_t)0x80000122)  /*!< I2C2 Alternate Function mapping 0010*/
#define AFIO_MAP5_I2C2_0011         ((uint32_t)0x80000123)  /*!< I2C2 Alternate Function mapping 0011*/
#define AFIO_MAP5_I2C3_0001         ((uint32_t)0x80000131)  /*!< I2C3 Alternate Function mapping 0001*/
#define AFIO_MAP5_SPI1_0001         ((uint32_t)0x80000141)  /*!< SPI1 Alternate Function mapping 0001*/
#define AFIO_MAP5_SPI1_0010         ((uint32_t)0x80000142)  /*!< SPI1 Alternate Function mapping 0010*/
#define AFIO_MAP5_SPI1_0011         ((uint32_t)0x80000143)  /*!< SPI1 Alternate Function mapping 0011*/
#define AFIO_MAP5_SPI2_0001         ((uint32_t)0x80000151)  /*!< SPI2 Alternate Function mapping 0001*/
#define AFIO_MAP5_SPI2_0010         ((uint32_t)0x80000152)  /*!< SPI2 Alternate Function mapping 0010*/
#define AFIO_MAP5_SPI3_0001         ((uint32_t)0x80000161)  /*!< SPI3 Alternate Function mapping 0001*/
#define AFIO_MAP5_SPI3_0010         ((uint32_t)0x80000162)  /*!< SPI3 Alternate Function mapping 0010*/
#define AFIO_MAP5_SPI3_0011         ((uint32_t)0x80000163)  /*!< SPI3 Alternate Function mapping 0011*/
#define AFIO_MAP5_SPI4_0001         ((uint32_t)0x80000171)  /*!< SPI4 Alternate Function mapping 0001*/
#define AFIO_MAP5_SPI4_0010         ((uint32_t)0x80000172)  /*!< SPI4 Alternate Function mapping 0010*/
#define AFIO_MAP5_SPI4_0011         ((uint32_t)0x80000173)  /*!< SPI4 Alternate Function mapping 0011*/

#define AFIO_MAP6_CAN1_0010         ((uint32_t)0x80000182)  /*!< CAN1 Alternate Function mapping 0010*/
#define AFIO_MAP6_CAN1_0011         ((uint32_t)0x80000183)  /*!< CAN1 Alternate Function mapping 0011*/
#define AFIO_MAP6_CAN2_0001         ((uint32_t)0x80000191)  /*!< CAN2 Alternate Function mapping */
#define AFIO_MAP6_SDIO_0100         ((uint32_t)0x800001A4)  /*!< SDIO Alternate Function mapping 100 */
#define AFIO_MAP6_SDIO_0101         ((uint32_t)0x800001A5)  /*!< SDIO Alternate Function mapping 101 */
#define AFIO_MAP6_SDIO_0110         ((uint32_t)0x800001A6)  /*!< SDIO Alternate Function mapping 110 */
#define AFIO_MAP6_SDIO_0111         ((uint32_t)0x800001A7)  /*!< SDIO Alternate Function mapping 111 */
#define AFIO_MAP6_SDIO2_0001        ((uint32_t)0x800001B1)  /*!< SDIO2 Alternate Function mapping 0001 */
#define AFIO_MAP6_SDIO2_0010        ((uint32_t)0x800001B2)  /*!< SDIO2 Alternate Function mapping 0010 */
#define AFIO_MAP6_SDIO2_0011        ((uint32_t)0x800001B3)  /*!< SDIO2 Alternate Function mapping 0011 */
#define AFIO_MAP6_USART1_0001       ((uint32_t)0x800001C1)  /*!< USART1 Alternate Function mapping */
#define AFIO_MAP6_USART2_0001       ((uint32_t)0x800001D1)  /*!< USART2 Alternate Function mapping */
#define AFIO_MAP6_USART3_0001       ((uint32_t)0x800001E1)  /*!< USART3 Alternate Function mapping 0001*/
#define AFIO_MAP6_USART3_0011       ((uint32_t)0x800001E3)  /*!< USART3 Alternate Function mapping 0011*/
#define AFIO_MAP6_UART4_0001        ((uint32_t)0x800001F1)  /*!< UART4 Alternate Function mapping */

#define AFIO_MAP7_SPIF_1000         ((uint32_t)0x80000208)  /*!< EXT_FLASH Alternate Function mapping */ 
#define AFIO_MAP7_SPIF_1001         ((uint32_t)0x80000209)  /*!< EXT_FLASH Alternate Function enable */ 
#define AFIO_MAP7_ADC1_0001         ((uint32_t)0x80000211)  /*!< ADC1 External Trigger Injected Conversion remapping */
#define AFIO_MAP7_ADC1_0010         ((uint32_t)0x80000212)  /*!< ADC1 External Trigger Regular Conversion remapping */
#define AFIO_MAP7_ADC1_0011         ((uint32_t)0x80000213)  /*!< ADC1 External Trigger Regular & Injected Conversion remapping */
#define AFIO_MAP7_ADC2_0001         ((uint32_t)0x80000221)  /*!< ADC2 External Trigger Injected Conversion remapping */
#define AFIO_MAP7_ADC2_0010         ((uint32_t)0x80000222)  /*!< ADC2 External Trigger Regular Conversion remapping */
#define AFIO_MAP7_ADC2_0011         ((uint32_t)0x80000223)  /*!< ADC2 External Trigger Regular & Injected Conversion remapping */
#define AFIO_MAP7_SWJTAG_0001       ((uint32_t)0x80000241)  /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define AFIO_MAP7_SWJTAG_0010       ((uint32_t)0x80000242)  /*!< JTAG-DP Disabled and SW-DP Enabled */
#define AFIO_MAP7_SWJTAG_0100       ((uint32_t)0x80000244)  /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */
#define AFIO_MAP7_PD01_0001         ((uint32_t)0x80000251)  /*!< PD01 Alternate Function mapping */  
#define AFIO_MAP7_XMC_0001          ((uint32_t)0x80000261)  /*!< XMC Alternate Function mapping 0001 */
#define AFIO_MAP7_XMC_0010          ((uint32_t)0x80000262)  /*!< XMC Alternate Function mapping 0010 */
#define AFIO_MAP7_XMC_1000          ((uint32_t)0x80000268)  /*!< XMC Alternate Function mapping 1000 */
#define AFIO_MAP7_XMC_1001          ((uint32_t)0x80000269)  /*!< XMC Alternate Function mapping 1001 */
#define AFIO_MAP7_XMC_1010          ((uint32_t)0x8000026A)  /*!< XMC Alternate Function mapping 1011 */

#define AFIO_MAP8_ETH_0001          ((uint32_t)0x800002C1)  /*!< ETH Alternate Function mapping 0001*/
#define AFIO_MAP8_ETH_0100          ((uint32_t)0x800002C4)  /*!< ETH Alternate Function mapping 0100*/
#define AFIO_MAP8_ETH_0101          ((uint32_t)0x800002C5)  /*!< ETH Alternate Function mapping 0101*/
#define AFIO_MAP8_ETH_1000          ((uint32_t)0x800002C8)  /*!< ETH Alternate Function mapping 1000*/
#define AFIO_MAP8_ETH_1001          ((uint32_t)0x800002C9)  /*!< ETH Alternate Function mapping 1001*/
#define AFIO_MAP8_ETH_1100          ((uint32_t)0x800002CC)  /*!< ETH Alternate Function mapping 1100*/
#define AFIO_MAP8_ETH_1101          ((uint32_t)0x800002CD)  /*!< ETH Alternate Function mapping 1101*/
#define AFIO_MAP8_USART6_0001       ((uint32_t)0x800002D1)  /*!< USART6 Alternate Function mapping */
#define AFIO_MAP8_UART7_0001        ((uint32_t)0x800002E1)  /*!< UART7 Alternate Function mapping */
#define AFIO_MAP8_UART8_0001        ((uint32_t)0x800002F1)  /*!< UART8 Alternate Function mapping */

#ifdef AT32F413xx
#define AFIO_MAP4_TMR2_0001         ((uint32_t)0x80000091)  /*!< TMR2 Alternate Function mapping 1001*/
#define AFIO_MAP4_TMR2_0010         ((uint32_t)0x80000092)  /*!< TMR2 Alternate Function mapping 1010*/
#define AFIO_MAP4_TMR2_0011         ((uint32_t)0x80000093)  /*!< TMR2 Alternate Function mapping 1011*/
#define AFIO_MAP4_TMR2_1001         ((uint32_t)0x80000099)  /*!< TMR2 Alternate Function mapping 1001*/
#define AFIO_MAP4_TMR2_1010         ((uint32_t)0x8000009A)  /*!< TMR2 Alternate Function mapping 1010*/
#define AFIO_MAP4_TMR2_1011         ((uint32_t)0x8000009B)  /*!< TMR2 Alternate Function mapping 1011*/
#define AFIO_MAP4_TMR5_0001         ((uint32_t)0x800000C1)  /*!< TMR5 Alternate Function mapping 0001: CH1/CH2*/
#define AFIO_MAP4_TMR5_1001         ((uint32_t)0x800000C9)  /*!< TMR5 Alternate Function mapping 1001: CH1/CH2+CH4 */
#endif

#ifdef AT32F415xx
#define AFIO_MAP4_TMR1_0010         ((uint32_t)0x80000082)  /*!< TMR1 Alternate Function mapping 0010*/
#define AFIO_MAP4_TMR2_0001         ((uint32_t)0x80000091)  /*!< TMR2 Alternate Function mapping 0001*/
#define AFIO_MAP4_TMR2_0010         ((uint32_t)0x80000092)  /*!< TMR2 Alternate Function mapping 0010*/
#define AFIO_MAP4_TMR2_0011         ((uint32_t)0x80000093)  /*!< TMR2 Alternate Function mapping 0011*/
#define AFIO_MAP4_TMR5_0001         ((uint32_t)0x800000C1)  /*!< TMR5 Alternate Function mapping 0001: CH1/CH2*/
#define AFIO_MAP4_TMR5_1001         ((uint32_t)0x800000C9)  /*!< TMR5 Alternate Function mapping 1001: CH1/CH2+CH4 */

#define AFIO_MAP8_TMR1_BK1_00       ((uint32_t)0x80000280)  /*!< TMR1 BK1 input selection 00/01*/
#define AFIO_MAP8_TMR1_BK1_10       ((uint32_t)0x80000282)  /*!< TMR1 BK1 input selection 10   */
#define AFIO_MAP8_TMR1_BK1_11       ((uint32_t)0x80000283)  /*!< TMR1 BK1 input selection 11   */
#define AFIO_MAP8_TMR1_CH1_00       ((uint32_t)0x80000290)  /*!< TMR1 CH1 input selection 00/01*/
#define AFIO_MAP8_TMR1_CH1_10       ((uint32_t)0x80000298)  /*!< TMR1 CH1 input selection 10   */
#define AFIO_MAP8_TMR1_CH1_11       ((uint32_t)0x8000029C)  /*!< TMR1 CH1 input selection 11   */
#define AFIO_MAP8_TMR2_CH4_00       ((uint32_t)0x800002A0)  /*!< TMR2 CH4 input selection 00/01*/
#define AFIO_MAP8_TMR2_CH4_10       ((uint32_t)0x800002A2)  /*!< TMR2 CH4 input selection 10   */
#define AFIO_MAP8_TMR2_CH4_11       ((uint32_t)0x800002A3)  /*!< TMR2 CH4 input selection 11   */
#define AFIO_MAP8_TMR3_CH1_00       ((uint32_t)0x800002B0)  /*!< TMR3 CH1 input selection 00/01*/
#define AFIO_MAP8_TMR3_CH1_10       ((uint32_t)0x800002B8)  /*!< TMR3 CH1 input selection 10   */
#define AFIO_MAP8_TMR3_CH1_11       ((uint32_t)0x800002BC)  /*!< TMR3 CH1 input selection 11   */
#endif

#if defined (AT32F403Axx) || defined (AT32F407xx)
#define AFIO_MAP4_TMR1_0011         ((uint32_t)0x80000083)  /*!< TMR1 Alternate Function mapping 0011*/
#define AFIO_MAP4_TMR2_0001         ((uint32_t)0x80000091)  /*!< TMR2 Alternate Function mapping 1001*/
#define AFIO_MAP4_TMR2_0010         ((uint32_t)0x80000092)  /*!< TMR2 Alternate Function mapping 1010*/
#define AFIO_MAP4_TMR2_0011         ((uint32_t)0x80000093)  /*!< TMR2 Alternate Function mapping 1011*/
#define AFIO_MAP4_TIM2ITR1_1000     ((uint32_t)0x80000098)  /*!< TMR2 Alternate Function mapping 1101*/
#define AFIO_MAP4_TIM2ITR1_1100     ((uint32_t)0x8000009C)  /*!< TMR2 Alternate Function mapping 1110*/
#define AFIO_MAP4_TMR4_0001         ((uint32_t)0x800000B1)  /*!< TMR5 Alternate Function mapping 0001: CH1/CH2*/
#endif

#define IS_GREMAP(REMAP)            ((REMAP) > 0x80000000)

#define IS_GPIO_GREMAP(REMAP)        (((REMAP) == AFIO_MAP3_TMR9_0010)    || ((REMAP) == AFIO_MAP3_TMR10_0010)    || \
                                     ((REMAP) == AFIO_MAP3_TMR11_0010)    || ((REMAP) == AFIO_MAP4_TMR1_0001)     || \
                                     ((REMAP) == AFIO_MAP4_TMR2_0001)     || ((REMAP) == AFIO_MAP6_CAN1_0010)     || \
                                     ((REMAP) == AFIO_MAP4_TMR2_0010)     || ((REMAP) == AFIO_MAP6_CAN2_0001)     || \
                                     ((REMAP) == AFIO_MAP4_TMR2_0011)     || ((REMAP) == AFIO_MAP6_SDIO_0100)     || \
                                     ((REMAP) == AFIO_MAP4_TMR3_0010)     || ((REMAP) == AFIO_MAP6_SDIO_0101)     || \
                                     ((REMAP) == AFIO_MAP4_TMR3_0011)     || ((REMAP) == AFIO_MAP6_SDIO_0110)     || \
                                     ((REMAP) == AFIO_MAP4_TMR5_0001)     || ((REMAP) == AFIO_MAP6_SDIO_0111)     || \
                                     ((REMAP) == AFIO_MAP4_TMR5_1000)     || ((REMAP) == AFIO_MAP6_USART1_0001)   || \
                                     ((REMAP) == AFIO_MAP4_TMR5_1001)     || ((REMAP) == AFIO_MAP6_USART3_0001)   || \
                                     ((REMAP) == AFIO_MAP5_I2C1_0001)     || ((REMAP) == AFIO_MAP6_UART4_0001)    || \
                                     ((REMAP) == AFIO_MAP5_I2C1_0011)     || ((REMAP) == AFIO_MAP7_SPIF_1000)     || \
                                     ((REMAP) == AFIO_MAP5_I2C2_0001)     || ((REMAP) == AFIO_MAP7_SPIF_1001)     || \
                                     ((REMAP) == AFIO_MAP5_I2C2_0010)     || ((REMAP) == AFIO_MAP7_ADC1_0001)     || \
                                     ((REMAP) == AFIO_MAP5_I2C2_0011)     || ((REMAP) == AFIO_MAP7_ADC1_0010)     || \
                                     ((REMAP) == AFIO_MAP5_SPI1_0001)     || ((REMAP) == AFIO_MAP7_ADC2_0001)     || \
                                     ((REMAP) == AFIO_MAP5_SPI2_0001)     || ((REMAP) == AFIO_MAP7_ADC2_0010)     || \
                                     ((REMAP) == AFIO_MAP7_SWJTAG_0010)   || ((REMAP) == AFIO_MAP7_SWJTAG_0001)   || \
                                     ((REMAP) == AFIO_MAP7_SWJTAG_0100)   || ((REMAP) == AFIO_MAP7_PD01_0001)     || \
                                     ((REMAP) == AFIO_MAP8_TMR1_BK1_00)   || ((REMAP) == AFIO_MAP8_TMR1_BK1_10)   || \
                                     ((REMAP) == AFIO_MAP8_TMR1_BK1_11)   || ((REMAP) == AFIO_MAP8_TMR1_CH1_00)   || \
                                     ((REMAP) == AFIO_MAP8_TMR1_CH1_10)   || ((REMAP) == AFIO_MAP8_TMR1_CH1_11)   || \
                                     ((REMAP) == AFIO_MAP8_TMR2_CH4_00)   || ((REMAP) == AFIO_MAP8_TMR2_CH4_10)   || \
                                     ((REMAP) == AFIO_MAP8_TMR2_CH4_11)   || ((REMAP) == AFIO_MAP8_TMR3_CH1_00)   || \
                                     ((REMAP) == AFIO_MAP8_TMR3_CH1_10)   || ((REMAP) == AFIO_MAP8_TMR3_CH1_11)   || \
                                     ((REMAP) == AFIO_MAP4_TMR1_0011)     || ((REMAP) == AFIO_MAP4_TMR4_0001)     || \
                                     ((REMAP) == AFIO_MAP4_TMR2_1001)     || ((REMAP) == AFIO_MAP4_TMR2_1010)     || \
                                     ((REMAP) == AFIO_MAP4_TMR2_1011)     || ((REMAP) == AFIO_MAP4_TMR2_1101)     || \
                                     ((REMAP) == AFIO_MAP4_TMR2_1110)     || ((REMAP) == AFIO_MAP4_TMR2_1111)     || \
                                     ((REMAP) == AFIO_MAP5_USART5_0001)   || ((REMAP) == AFIO_MAP5_I2C3_0001)     || \
                                     ((REMAP) == AFIO_MAP5_SPI1_0010)     || ((REMAP) == AFIO_MAP5_SPI1_0011)     || \
                                     ((REMAP) == AFIO_MAP5_SPI2_0010)     || ((REMAP) == AFIO_MAP5_SPI3_0001)     || \
                                     ((REMAP) == AFIO_MAP5_SPI3_0010)     || ((REMAP) == AFIO_MAP5_SPI3_0011)     || \
                                     ((REMAP) == AFIO_MAP5_SPI4_0001)     || ((REMAP) == AFIO_MAP5_SPI4_0010)     || \
                                     ((REMAP) == AFIO_MAP5_SPI4_0011)     || ((REMAP) == AFIO_MAP6_CAN1_0011)     || \
                                     ((REMAP) == AFIO_MAP6_SDIO2_0001)    || ((REMAP) == AFIO_MAP6_SDIO2_0010)    || \
                                     ((REMAP) == AFIO_MAP6_SDIO2_0011)    || ((REMAP) == AFIO_MAP6_USART2_0001)   || \
                                     ((REMAP) == AFIO_MAP6_USART3_0011)   || ((REMAP) == AFIO_MAP7_ADC1_0011)     || \
                                     ((REMAP) == AFIO_MAP7_ADC2_0011)     || ((REMAP) == AFIO_MAP7_XMC_0001)      || \
                                     ((REMAP) == AFIO_MAP7_XMC_0010)      || ((REMAP) == AFIO_MAP7_XMC_1001)      || \
                                     ((REMAP) == AFIO_MAP7_XMC_1010)      || ((REMAP) == AFIO_MAP8_ETH_0001)      || \
                                     ((REMAP) == AFIO_MAP8_ETH_0100)      || ((REMAP) == AFIO_MAP8_ETH_0101)      || \
                                     ((REMAP) == AFIO_MAP8_ETH_1000)      || ((REMAP) == AFIO_MAP8_ETH_1001)      || \
                                     ((REMAP) == AFIO_MAP8_ETH_1100)      || ((REMAP) == AFIO_MAP8_ETH_1101)      || \
                                     ((REMAP) == AFIO_MAP8_USART6_0001)   || ((REMAP) == AFIO_MAP8_UART7_0001)    || \
                                     ((REMAP) == AFIO_MAP8_UART8_0001)    || ((REMAP) == AFIO_MAP4_TIM2ITR1_1000) || \
                                     ((REMAP) == AFIO_MAP4_TIM2ITR1_1100) || ((REMAP) == AFIO_MAP7_XMC_1000))
                                     
/**
  * @}
  */ 
#endif

/** @defgroup GPIO_Port_Sources 
  * @{
  */

#define GPIO_PortSourceGPIOA       ((uint8_t)0x00)
#define GPIO_PortSourceGPIOB       ((uint8_t)0x01)
#define GPIO_PortSourceGPIOC       ((uint8_t)0x02)
#define GPIO_PortSourceGPIOD       ((uint8_t)0x03)
#define GPIO_PortSourceGPIOE       ((uint8_t)0x04)
#define GPIO_PortSourceGPIOF       ((uint8_t)0x05)
#define GPIO_PortSourceGPIOG       ((uint8_t)0x06)
#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOE))

#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE)     (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOE) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOF) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOG))

/**
  * @}
  */

/** @defgroup GPIO_Pin_sources 
  * @{
  */

#define GPIO_PinsSource0            ((uint8_t)0x00)
#define GPIO_PinsSource1            ((uint8_t)0x01)
#define GPIO_PinsSource2            ((uint8_t)0x02)
#define GPIO_PinsSource3            ((uint8_t)0x03)
#define GPIO_PinsSource4            ((uint8_t)0x04)
#define GPIO_PinsSource5            ((uint8_t)0x05)
#define GPIO_PinsSource6            ((uint8_t)0x06)
#define GPIO_PinsSource7            ((uint8_t)0x07)
#define GPIO_PinsSource8            ((uint8_t)0x08)
#define GPIO_PinsSource9            ((uint8_t)0x09)
#define GPIO_PinsSource10           ((uint8_t)0x0A)
#define GPIO_PinsSource11           ((uint8_t)0x0B)
#define GPIO_PinsSource12           ((uint8_t)0x0C)
#define GPIO_PinsSource13           ((uint8_t)0x0D)
#define GPIO_PinsSource14           ((uint8_t)0x0E)
#define GPIO_PinsSource15           ((uint8_t)0x0F)

#define IS_GPIO_PINS_SOURCE(PINSSOURCE) (((PINSSOURCE) == GPIO_PinsSource0)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource1)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource2)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource3)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource4)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource5)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource6)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource7)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource8)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource9)  || \
                                         ((PINSSOURCE) == GPIO_PinsSource10) || \
                                         ((PINSSOURCE) == GPIO_PinsSource11) || \
                                         ((PINSSOURCE) == GPIO_PinsSource12) || \
                                         ((PINSSOURCE) == GPIO_PinsSource13) || \
                                         ((PINSSOURCE) == GPIO_PinsSource14) || \
                                         ((PINSSOURCE) == GPIO_PinsSource15))

/**
  * @}
  */
                                             
/** @defgroup Ethernet_Media_Interface 
  * @{
  */ 
#define GPIO_ETH_MediaInterface_MII    ((uint32_t)0x00000000) 
#define GPIO_ETH_MediaInterface_RMII   ((uint32_t)0x00000001)                                       

#define IS_GPIO_ETH_MEDIA_INTERFACE(INTERFACE) (((INTERFACE) == GPIO_ETH_MediaInterface_MII) || \
                                                ((INTERFACE) == GPIO_ETH_MediaInterface_RMII))
                                                
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

void GPIO_Reset(GPIO_Type* GPIOx);
void GPIO_AFIOReset(void);
void GPIO_Init(GPIO_Type* GPIOx, GPIO_InitType* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitType* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_Type* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_Type* GPIOx);
void GPIO_SetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin, BitState BitVal);
void GPIO_Write(GPIO_Type* GPIOx, uint16_t PortVal);
void GPIO_PinsLockConfig(GPIO_Type* GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinsRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_GPIO_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


