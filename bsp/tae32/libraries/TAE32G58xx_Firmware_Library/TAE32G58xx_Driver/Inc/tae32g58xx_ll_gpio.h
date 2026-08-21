/**
  ******************************************************************************
  * @file    tae32g58xx_ll_gpio.h
  * @author  MCD Application Team
  * @brief   Header file for GPIO LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_GPIO_H_
#define _TAE32G58XX_LL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup GPIO_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Macros GPIO LL Exported Macros
  * @brief    GPIO LL Exported Macros
  * @{
  */

/**
  * @brief  Pin Output Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_PinOutput_Set(__GPIO__, pin)              SET_BIT((__GPIO__)->BSR, (((pin) & GPIO_PIN_MASK) << GPIOA_BSR_BSn_Pos))

/**
  * @brief  Pin Output Reset
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_PinOutput_Reset(__GPIO__, pin)            \
        SET_BIT((__GPIO__)->BSR, ((unsigned int)((pin) & GPIO_PIN_MASK) << GPIOA_BSR_BRn_Pos))


/**
  * @brief  Pin Input Data Get
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return Pin Input Data
  */
#define __LL_GPIO_InputDat_Get(__GPIO__, pin)               READ_BIT((__GPIO__)->DIR, (pin))


/**
  * @brief  Pin Output Data Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @param  val pin value
  * @return None
  */
#define __LL_GPIO_OutputDat_Set(__GPIO__, pin, val)         MODIFY_REG((__GPIO__)->DOR, (pin), (val & (pin)))

/**
  * @brief  Pin Output Data Get
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return Pin Output Data
  */
#define __LL_GPIO_OutputDat_Get(__GPIO__, pin)              READ_BIT((__GPIO__)->DOR, (pin))


/**
  * @brief  Pin Interrupt Enable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_INT_En(__GPIO__, pin)                     SET_BIT((__GPIO__)->IER, (pin))

/**
  * @brief  Pin Interrupt Disable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_INT_Dis(__GPIO__, pin)                    CLEAR_BIT((__GPIO__)->IER, (pin))

/**
  * @brief  Judge is Pin Interrupt Enable or not
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @retval 0 Pin Interrupt is Disable
  * @retval 1 Pin Interrupt is Enable
  */
#define __LL_GPIO_IsIntEn(__GPIO__, pin)                    READ_BIT((__GPIO__)->IER, (pin))


/**
  * @brief  Pin Interrupt Mode Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin_num  GPIO pin num range 0~(GPIO_PIN_NUMS-1)
  * @param  mode GPIO pin interrupt mode @ref GPIO_IntModeETypeDef
  * @return None
  */
#define __LL_GPIO_IntMode_Set(__GPIO__, pin_num, mode)      MODIFY_REG((__GPIO__)->IMR, 0x3UL << (2*pin_num), ((mode) & 0x3UL) << (2*pin_num))

/**
  * @brief  Pin Interrupt Mode Set (Legacy)
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin_num  GPIO pin num range 0~(GPIO_PIN_NUMS-1)
  * @param  mode GPIO pin interrupt mode @ref GPIO_IntModeETypeDef
  * @return None
  */
#define __LL_GPIIO_IntMode_Set(__GPIO__, pin_num, mode)     __LL_GPIO_IntMode_Set(__GPIO__, pin_num, mode) 

/**
  * @brief  Judge is Pin Interrupt Pending or not
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @retval 0 isn't GPIO Interrupt Pendig
  * @retval 1 is GPIO Interrupt Pendig
  */
#define __LL_GPIO_IsIntPending(__GPIO__, pin)               (!!(READ_BIT((__GPIO__)->ISR, (pin))))

/**
  * @brief  Pin Interrupt Pending Clear
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_IntPending_Clr(__GPIO__, pin)             WRITE_REG((__GPIO__)->ISR, (pin))

/**
  * @brief  Pin Interrupt Pending Get
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return Pin Interrupt Pending
  */
#define __LL_GPIO_IntPending_Get(__GPIO__, pin)             READ_BIT((__GPIO__)->ISR, (pin))


/**
  * @brief  Pin Pinmux Function Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin_num  GPIO pin num range 0~(GPIO_PIN_NUMS-1)
  * @param  func Pinmux Function @ref GPIO_AFETypeDef
  * @return None
  */
#define __LL_GPIO_PinmuxFunc_Set(__GPIO__, pin_num, func)                                                             \
        do {                                                                                                          \
            if (pin_num < 8) {                                                                                        \
                MODIFY_REG((__GPIO__)->MR0, 0xfUL << (4 * (pin_num % 8)), ((func) & 0xfUL) << (4 * (pin_num % 8)));  \
            } else {                                                                                                  \
                MODIFY_REG((__GPIO__)->MR1, 0xfUL << (4 * (pin_num % 8)), ((func) & 0xfUL) << (4 * (pin_num % 8)));  \
            }                                                                                                         \
        } while(0)


/**
  * @brief  Pin Synchronization Enable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_Sync_En(__GPIO__, pin)                    SET_BIT((__GPIO__)->SER, (pin))

/**
  * @brief  Pin Synchronization Disable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_Sync_Dis(__GPIO__, pin)                   CLEAR_BIT((__GPIO__)->SER, (pin))


/**
  * @brief  Pin Debounce Enable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_Deb_En(__GPIO__, pin)                     SET_BIT((__GPIO__)->DER, (pin))

/**
  * @brief  Pin Debounce Disable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_Deb_Dis(__GPIO__, pin)                    CLEAR_BIT((__GPIO__)->DER, (pin))


/**
  * @brief  Pin Pull Mode Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin_num  GPIO pin num range 0~(GPIO_PIN_NUMS-1)
  * @param  mode GPIO pin Pull mode @ref GPIO_PullETypeDef
  * @return None
  */
#define __LL_GPIO_PullMode_Set(__GPIO__, pin_num, mode)     MODIFY_REG((__GPIO__)->UDR, 0x3UL << (2*pin_num), ((mode) & 0x3UL) << (2*pin_num))

/**
  * @brief  Pin Pull Mode Set (Legacy)
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin_num  GPIO pin num range 0~(GPIO_PIN_NUMS-1)
  * @param  mode GPIO pin Pull mode @ref GPIO_PullETypeDef
  * @return None
  */
#define __LL_GPIIO_PullMode_Set(__GPIO__, pin_num, mode)    __LL_GPIO_PullMode_Set(__GPIO__, pin_num, mode)

/**
  * @brief  Pin Output Mode PushPull Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_OutputMode_PushPull_Set(__GPIO__, pin)    CLEAR_BIT((__GPIO__)->ODR, (pin))

/**
  * @brief  Pin Output Mode OpenDrain Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_OutputMode_OpenDrain_Set(__GPIO__, pin)   SET_BIT((__GPIO__)->ODR, (pin))


/**
  * @brief  Pin Drive Capability 8mA Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_DrvCap_8mA_Set(__GPIO__, pin)             CLEAR_BIT((__GPIO__)->DHR, (pin))

/**
  * @brief  Pin Drive Capability 24mA Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_DrvCap_24mA_Set(__GPIO__, pin)            SET_BIT((__GPIO__)->DHR, (pin))

/**
  * @brief  Pin Drive Capability Set 
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @param  level Drive Capability @ref GPIO_DrvCapETypeDef
  * @return None
  */
#define __LL_GPIO_DrvCapSpd_Set(__GPIO__, pin, level)                                                                    \
        do {                                                                                                            \
            (level & 0x1UL) ? (SET_BIT((__GPIO__)->DHR, (pin))) : (CLEAR_BIT((__GPIO__)->DHR, (pin)));                  \
            (level & 0x2UL) ? (SET_BIT((__GPIO__)->DHR, (pin) << 16UL)) : (CLEAR_BIT((__GPIO__)->DHR, (pin) << 16UL));  \
        } while(0)

/**
  * @brief  Pin Drive Capability Mask Get
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return Drive Capability Mask
  */
#define __LL_GPIO_DrvCapSpdMask_Get(__GPIO__, pin)          \
        ((READ_REG((__GPIO__)->DHR)) & ((1UL << (pin & 0xfUL)) | ((1UL << (pin & 0xfUL)) << 16UL)))

/**
  * @brief  Pin Drive Capability Get
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @param  mask Pin Drive Capability Mask
  * @return Drive Capability Mask
  */
#define __LL_GPIO_DrvCapSpd_Get(pin, mask)                                          \
        (((uint8_t)(((mask & 0xffffffffUL)  & (1UL << (pin & 0xfUL))) != 0)) +               \
        ((((uint8_t)(((mask & 0xffffffffUL)  & ((1UL << (pin & 0xfUL)) << 16UL)) != 0)) * 2)))


/**
  * @brief  Pin Input Hysteresis Enable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_InputHyst_En(__GPIO__, pin)               SET_BIT((__GPIO__)->IHR, (pin))

/**
  * @brief  Pin Input Hysteresis Disable
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_InputHyst_Dis(__GPIO__, pin)              CLEAR_BIT((__GPIO__)->IHR, (pin))


/**
  * @brief  Pin Output Slew Normal Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_OutputSlew_Normal_Set(__GPIO__, pin)      CLEAR_BIT((__GPIO__)->OSR, (pin))

/**
  * @brief  Pin Output Slew Enhance Set
  * @param  __GPIO__ Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_PinETypeDef
  * @return None
  */
#define __LL_GPIO_OutputSlew_Enhance_Set(__GPIO__, pin)     SET_BIT((__GPIO__)->OSR, (pin))


/**
  * @brief  Judge is Pin Valid or not
  * @param  pin pin to judge
  * @retval 0 Pin isn't Valid
  * @retval 1 Pin is Valid
  */
#define __LL_GPIO_IsPinValid(pin)                           (((pin) & GPIO_PIN_MASK) && (!((pin) & ~GPIO_PIN_MASK)))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Types GPIO LL Exported Types
  * @brief    GPIO LL Exported Types
  * @{
  */

/**
  * @brief GPIO Pin Definition
  */
typedef enum {
    GPIO_PIN_0    = BIT(0),     /*!< GPIO Pin 0     */
    GPIO_PIN_1    = BIT(1),     /*!< GPIO Pin 1     */
    GPIO_PIN_2    = BIT(2),     /*!< GPIO Pin 2     */
    GPIO_PIN_3    = BIT(3),     /*!< GPIO Pin 3     */
    GPIO_PIN_4    = BIT(4),     /*!< GPIO Pin 4     */
    GPIO_PIN_5    = BIT(5),     /*!< GPIO Pin 5     */
    GPIO_PIN_6    = BIT(6),     /*!< GPIO Pin 6     */
    GPIO_PIN_7    = BIT(7),     /*!< GPIO Pin 7     */
    GPIO_PIN_8    = BIT(8),     /*!< GPIO Pin 8     */
    GPIO_PIN_9    = BIT(9),     /*!< GPIO Pin 9     */
    GPIO_PIN_10   = BIT(10),    /*!< GPIO Pin 10    */
    GPIO_PIN_11   = BIT(11),    /*!< GPIO Pin 11    */
    GPIO_PIN_12   = BIT(12),    /*!< GPIO Pin 12    */
    GPIO_PIN_13   = BIT(13),    /*!< GPIO Pin 13    */
    GPIO_PIN_14   = BIT(14),    /*!< GPIO Pin 14    */
    GPIO_PIN_15   = BIT(15),    /*!< GPIO Pin 15    */
    GPIO_PIN_NUMS = 16,         /*!< GPIO Pin Nums  */

    GPIO_PIN_All  = 0xFFFF,     /*!< GPIO All pins  */
    GPIO_PIN_MASK = 0xFFFF,     /*!< GPIO Pin mask  */
} GPIO_PinETypeDef;

/**
  * @brief GPIO AF Mode Definition
  */
typedef enum {
    GPIO_AF0_INPUT   = 0U,  /*!< GPIO alternate function 0 INPUT    */

    GPIO_AF1_OUTPUT  = 1U,  /*!< GPIO alternate function 1 OUTPUT   */

    GPIO_AF2         = 2U,  /*!< GPIO alternate function 2          */
    GPIO_AF2_MCO     = 2U,  /*!< GPIO alternate function 2 MCO      */
    GPIO_AF2_SWDAT   = 2U,  /*!< GPIO alternate function 2 SWDAT    */
    GPIO_AF2_SWCLK   = 2U,  /*!< GPIO alternate function 2 SWCLK    */
    GPIO_AF2_SWO     = 2U,  /*!< GPIO alternate function 2 SWO      */
    GPIO_AF2_TRACE   = 2U,  /*!< GPIO alternate function 2 TRACE    */

    GPIO_AF3         = 3U,  /*!< GPIO alternate function 3          */
    GPIO_AF3_TMR0    = 3U,  /*!< GPIO alternate function 3 TMR0     */
    GPIO_AF3_TMR1    = 3U,  /*!< GPIO alternate function 3 TMR1     */
    GPIO_AF3_TMR2    = 3U,  /*!< GPIO alternate function 3 TMR2     */
    GPIO_AF3_TMR3    = 3U,  /*!< GPIO alternate function 3 TMR3     */
    GPIO_AF3_TMR4    = 3U,  /*!< GPIO alternate function 3 TMR4     */

    GPIO_AF4         = 4U,  /*!< GPIO alternate function 4          */
    GPIO_AF4_TMR0    = 4U,  /*!< GPIO alternate function 4 TMR0     */
    GPIO_AF4_TMR1    = 4U,  /*!< GPIO alternate function 4 TMR1     */
    GPIO_AF4_TMR2    = 4U,  /*!< GPIO alternate function 4 TMR2     */
    GPIO_AF4_TMR3    = 4U,  /*!< GPIO alternate function 4 TMR3     */
    GPIO_AF4_TMR4    = 4U,  /*!< GPIO alternate function 4 TMR4     */
    GPIO_AF4_TMR9    = 4U,  /*!< GPIO alternate function 4 TMR9     */
    GPIO_AF4_TMR10   = 4U,  /*!< GPIO alternate function 4 TMR10    */
    GPIO_AF4_QEI1    = 4U,  /*!< GPIO alternate function 4 QEI1     */

    GPIO_AF5         = 5U,  /*!< GPIO alternate function 5          */
    GPIO_AF5_TMR0    = 5U,  /*!< GPIO alternate function 5 TMR0     */
    GPIO_AF5_TMR1    = 5U,  /*!< GPIO alternate function 5 TMR1     */
    GPIO_AF5_TMR2    = 5U,  /*!< GPIO alternate function 5 TMR2     */
    GPIO_AF5_TMR3    = 5U,  /*!< GPIO alternate function 5 TMR3     */
    GPIO_AF5_TMR9    = 5U,  /*!< GPIO alternate function 5 TMR9     */
    GPIO_AF5_TMR10   = 5U,  /*!< GPIO alternate function 5 TMR10    */
    GPIO_AF5_QEI0    = 5U,  /*!< GPIO alternate function 5 QEI0     */
    GPIO_AF5_QEI2    = 5U,  /*!< GPIO alternate function 5 QEI2     */
    GPIO_AF5_I2C     = 5U,  /*!< GPIO alternate function 5 I2C      */
    GPIO_AF5_I2C0    = 5U,  /*!< GPIO alternate function 5 I2C0     */
    GPIO_AF5_I2C1    = 5U,  /*!< GPIO alternate function 5 I2C1     */
    GPIO_AF5_I2C2    = 5U,  /*!< GPIO alternate function 5 I2C2     */

    GPIO_AF6         = 6U,  /*!< GPIO alternate function 6          */
    GPIO_AF6_TMR3    = 6U,  /*!< GPIO alternate function 6 TMR3     */
    GPIO_AF6_TMR10   = 6U,  /*!< GPIO alternate function 6 TMR10    */
    GPIO_AF6_SPI     = 6U,  /*!< GPIO alternate function 6 SPI      */
    GPIO_AF6_SPI0    = 6U,  /*!< GPIO alternate function 6 SPI0     */
    GPIO_AF6_SPI1    = 6U,  /*!< GPIO alternate function 6 SPI1     */
    GPIO_AF6_UART0   = 6U,  /*!< GPIO alternate function 6 UART0    */
    GPIO_AF6_UART2   = 6U,  /*!< GPIO alternate function 6 UART2    */
    GPIO_AF6_UART4   = 6U,  /*!< GPIO alternate function 6 UART4    */

    GPIO_AF7         = 7U,  /*!< GPIO alternate function 7          */
    GPIO_AF7_TMR9    = 7U,  /*!< GPIO alternate function 7 TMR9     */
    GPIO_AF7_TMR10   = 7U,  /*!< GPIO alternate function 7 TMR10    */
    GPIO_AF7_SPI0    = 7U,  /*!< GPIO alternate function 7 SPI0     */
    GPIO_AF7_I2C1    = 7U,  /*!< GPIO alternate function 7 I2C1     */

    GPIO_AF8         = 8U,  /*!< GPIO alternate function 8          */
    GPIO_AF8_TMR0    = 8U,  /*!< GPIO alternate function 8 TMR0     */
    GPIO_AF8_TMR9    = 8U,  /*!< GPIO alternate function 8 TMR9     */
    GPIO_AF8_TMR10   = 8U,  /*!< GPIO alternate function 8 TMR10    */
    GPIO_AF8_I2C0    = 8U,  /*!< GPIO alternate function 8 I2C0     */
    GPIO_AF8_SPI1    = 8U,  /*!< GPIO alternate function 8 SPI1     */
    GPIO_AF8_UART0   = 8U,  /*!< GPIO alternate function 8 UART0    */
    GPIO_AF8_UART1   = 8U,  /*!< GPIO alternate function 8 UART1    */
    GPIO_AF8_UART2   = 8U,  /*!< GPIO alternate function 8 UART2    */
    GPIO_AF8_UART3   = 8U,  /*!< GPIO alternate function 8 UART3    */

    GPIO_AF9         = 9U,  /*!< GPIO alternate function 9          */
    GPIO_AF9_I2C1    = 9U,  /*!< GPIO alternate function 9 I2C1     */
    GPIO_AF9_I2C2    = 9U,  /*!< GPIO alternate function 9 I2C2     */
    GPIO_AF9_UART0   = 9U,  /*!< GPIO alternate function 9 UART0    */
    GPIO_AF9_UART4   = 9U,  /*!< GPIO alternate function 9 UART4    */
    GPIO_AF9_QEI0    = 9U,  /*!< GPIO alternate function 9 QEI0     */
    GPIO_AF9_QEI1    = 9U,  /*!< GPIO alternate function 9 QEI1     */
    GPIO_AF9_CMP0    = 9U,  /*!< GPIO alternate function 9 CMP0     */
    GPIO_AF9_CMP1    = 9U,  /*!< GPIO alternate function 9 CMP1     */
    GPIO_AF9_CMP2    = 9U,  /*!< GPIO alternate function 9 CMP2     */
    GPIO_AF9_CMP3    = 9U,  /*!< GPIO alternate function 9 CMP3     */
    GPIO_AF9_CMP8    = 9U,  /*!< GPIO alternate function 9 CMP8     */

    GPIO_AF10        = 10U, /*!< GPIO alternate function 10         */
    GPIO_AF10_UART1  = 10U, /*!< GPIO alternate function 10 UART1   */
    GPIO_AF10_UART2  = 10U, /*!< GPIO alternate function 10 UART2   */
    GPIO_AF10_UART3  = 10U, /*!< GPIO alternate function 10 UART3   */
    GPIO_AF10_QEI1   = 10U, /*!< GPIO alternate function 10 QEI1    */
    GPIO_AF10_CAN    = 10U, /*!< GPIO alternate function 10 CAN     */
    GPIO_AF10_CAN0   = 10U, /*!< GPIO alternate function 10 CAN0    */
    GPIO_AF10_CAN1   = 10U, /*!< GPIO alternate function 10 CAN1    */
    GPIO_AF10_TMR9   = 10U, /*!< GPIO alternate function 10 TMR9    */

    GPIO_AF11        = 11U, /*!< GPIO alternate function 11         */
    GPIO_AF11_TMR0   = 11U, /*!< GPIO alternate function 11 TMR0    */
    GPIO_AF11_TMR1   = 11U, /*!< GPIO alternate function 11 TMR1    */
    GPIO_AF11_TMR2   = 11U, /*!< GPIO alternate function 11 TMR2    */
    GPIO_AF11_TMR4   = 11U, /*!< GPIO alternate function 11 TMR4    */
    GPIO_AF11_TMR9   = 11U, /*!< GPIO alternate function 11 TMR9    */
    GPIO_AF11_TMR10  = 11U, /*!< GPIO alternate function 11 TMR10   */
    GPIO_AF11_SPI    = 11U, /*!< GPIO alternate function 11 SPI     */
    GPIO_AF11_SPI0   = 11U, /*!< GPIO alternate function 11 SPI0    */
    GPIO_AF11_SPI1   = 11U, /*!< GPIO alternate function 11 SPI1    */
    GPIO_AF11_HRPWM  = 11U, /*!< GPIO alternate function 11 HRPWM   */

    GPIO_AF12        = 12U, /*!< GPIO alternate function 12         */
    GPIO_AF12_TMR10  = 12U, /*!< GPIO alternate function 12 TMR10   */
    GPIO_AF12_I2C0   = 12U, /*!< GPIO alternate function 12 I2C0    */
    GPIO_AF12_UART4  = 12U, /*!< GPIO alternate function 12 UART4   */
    GPIO_AF12_CAN0   = 12U, /*!< GPIO alternate function 12 CAN0    */
    GPIO_AF12_CMP4   = 12U, /*!< GPIO alternate function 12 CMP4    */
    GPIO_AF12_CMP5   = 12U, /*!< GPIO alternate function 12 CMP5    */
    GPIO_AF12_CMP6   = 12U, /*!< GPIO alternate function 12 CMP6    */
    GPIO_AF12_CMP7   = 12U, /*!< GPIO alternate function 12 CMP7    */
    GPIO_AF12_CMP8   = 12U, /*!< GPIO alternate function 12 CMP8    */
    GPIO_AF12_PDM3   = 12U, /*!< GPIO alternate function 12 PDM3    */
    GPIO_AF12_HRPWM  = 12U, /*!< GPIO alternate function 12 HRPWM   */

    GPIO_AF13        = 13U, /*!< GPIO alternate function 13         */
    GPIO_AF13_TMR9   = 13U, /*!< GPIO alternate function 13 TMR9    */
    GPIO_AF13_UART0  = 13U, /*!< GPIO alternate function 13 UART0   */
    GPIO_AF13_UART3  = 13U, /*!< GPIO alternate function 13 UART3   */
    GPIO_AF13_XIF    = 13U, /*!< GPIO alternate function 13 XIF     */
    GPIO_AF13_PDM    = 13U, /*!< GPIO alternate function 13 PDM     */
    GPIO_AF13_PDM0   = 13U, /*!< GPIO alternate function 13 PDM0    */
    GPIO_AF13_PDM1   = 13U, /*!< GPIO alternate function 13 PDM1    */
    GPIO_AF13_PDM2   = 13U, /*!< GPIO alternate function 13 PDM2    */
    GPIO_AF13_PDM3   = 13U, /*!< GPIO alternate function 13 PDM3    */
    GPIO_AF13_CMP    = 13U, /*!< GPIO alternate function 13 CMP     */
    GPIO_AF13_CMP0   = 13U, /*!< GPIO alternate function 13 CMP0    */
    GPIO_AF13_CMP1   = 13U, /*!< GPIO alternate function 13 CMP1    */
    GPIO_AF13_CMP2   = 13U, /*!< GPIO alternate function 13 CMP2    */
    GPIO_AF13_CMP3   = 13U, /*!< GPIO alternate function 13 CMP3    */
    GPIO_AF13_CMP4   = 13U, /*!< GPIO alternate function 13 CMP4    */
    GPIO_AF13_CMP5   = 13U, /*!< GPIO alternate function 13 CMP5    */
    GPIO_AF13_CMP6   = 13U, /*!< GPIO alternate function 13 CMP6    */
    GPIO_AF13_CMP7   = 13U, /*!< GPIO alternate function 13 CMP7    */
    GPIO_AF13_CMP8   = 13U, /*!< GPIO alternate function 13 CMP8    */
    GPIO_AF13_HRPWM  = 13U, /*!< GPIO alternate function 13 HRPWM   */

    GPIO_AF14        = 14U, /*!< GPIO alternate function 14         */
    GPIO_AF14_CMP0   = 14U, /*!< GPIO alternate function 14 CMP0    */
    GPIO_AF14_CMP1   = 14U, /*!< GPIO alternate function 14 CMP1    */
    GPIO_AF14_CMP2   = 14U, /*!< GPIO alternate function 14 CMP2    */
    GPIO_AF14_CMP3   = 14U, /*!< GPIO alternate function 14 CMP3    */
    GPIO_AF14_CMP8   = 14U, /*!< GPIO alternate function 14 CMP8    */
    GPIO_AF14_HRPWM  = 14U, /*!< GPIO alternate function 14 HRPWM   */

    GPIO_AF15        = 15U, /*!< GPIO alternate function 15         */
    GPIO_AF15_ANALOG = 15U, /*!< GPIO alternate function 15 ANALOG  */
    GPIO_AF15_ADC    = 15U, /*!< GPIO alternate function 15 ADC     */
    GPIO_AF15_ADC0   = 15U, /*!< GPIO alternate function 15 ADC0    */
    GPIO_AF15_ADC1   = 15U, /*!< GPIO alternate function 15 ADC1    */
    GPIO_AF15_ADC2   = 15U, /*!< GPIO alternate function 15 ADC2    */
    GPIO_AF15_ADC3   = 15U, /*!< GPIO alternate function 15 ADC3    */
    GPIO_AF15_DAC    = 15U, /*!< GPIO alternate function 15 DAC     */
    GPIO_AF15_DAC0   = 15U, /*!< GPIO alternate function 15 DAC0    */
    GPIO_AF15_DAC1   = 15U, /*!< GPIO alternate function 15 DAC1    */
    GPIO_AF15_DAC2   = 15U, /*!< GPIO alternate function 15 DAC2    */
    GPIO_AF15_CMP    = 15U, /*!< GPIO alternate function 15 CMP     */
    GPIO_AF15_CMP0   = 15U, /*!< GPIO alternate function 15 CMP0    */
    GPIO_AF15_CMP1   = 15U, /*!< GPIO alternate function 15 CMP1    */
    GPIO_AF15_CMP2   = 15U, /*!< GPIO alternate function 15 CMP2    */
    GPIO_AF15_CMP3   = 15U, /*!< GPIO alternate function 15 CMP3    */
    GPIO_AF15_CMP4   = 15U, /*!< GPIO alternate function 15 CMP4    */
    GPIO_AF15_CMP5   = 15U, /*!< GPIO alternate function 15 CMP5    */
    GPIO_AF15_CMP6   = 15U, /*!< GPIO alternate function 15 CMP6    */
    GPIO_AF15_CMP7   = 15U, /*!< GPIO alternate function 15 CMP7    */
    GPIO_AF15_CMP8   = 15U, /*!< GPIO alternate function 15 CMP8    */
    GPIO_AF15_USB    = 15U, /*!< GPIO alternate function 15 USB     */

    GPIO_AF_DEFAULT  = 15U, /*!< GPIO alternate function 15 DEFAULT */
} GPIO_AFETypeDef;

/**
  * @brief GPIO Interrupt Mode Definition
  */
typedef enum {
    GPIO_INT_MODE_CLOSE = 0,        /*!< GPIO Interrupt Mode Close              */
    GPIO_INT_MODE_FALLING,          /*!< GPIO Interrupt Mode Falling            */
    GPIO_INT_MODE_RISING,           /*!< GPIO Interrupt Mode Rising             */
    GPIO_INT_MODE_RISING_FALLING,   /*!< GPIO Interrupt Mode Rising and Falling */
} GPIO_IntModeETypeDef;

/**
  * @brief GPIO Pull-Up or Pull-Down Activation Definition
  */
typedef enum {
    GPIO_NOPULL = 0,        /*!< No Pull-up or Pull-down activation */
    GPIO_PULLDOWN,          /*!< Pull-down activation               */
    GPIO_PULLUP,            /*!< Pull-up activation                 */
    GPIO_PULLUP_DOWN,       /*!< Pull-up or Pull-down activation    */
} GPIO_PullETypeDef;

/**
  * @brief GPIO output type: Push-Pull or Open-Drain Definition
  */
typedef enum {
    GPIO_OTYPE_PP,          /*!< Output Push Pull Type  */
    GPIO_OTYPE_OD,          /*!< Output Open Drain Type */
} GPIO_OutputETypeDef;

/**
  * @brief GPIO Output Speed Definition
  */
typedef enum {
    GPIO_SPEED_FREQ_LOW,    /*!< Low speed  */
    GPIO_SPEED_FREQ_HIGH,   /*!< High speed */
} GPIO_SpeedETypeDef;

/**
  * @brief GPIO Bit Set/Reset Definition
  */
typedef enum {
    GPIO_PIN_RESET = 0,     /*!< GPIO pin state Reset   */
    GPIO_PIN_SET,           /*!< GPIO pin state Set     */
} GPIO_PinStateETypeDef;

/**
  * @brief GPIO Drive Capability Level Definition
  */
typedef enum {
    GPIO_DRV_CAP_LOW = 0,       /*!< GPIO Drive Capability Low          */
    GPIO_DRV_CAP_MED,           /*!< GPIO Drive Capability Medium       */
    GPIO_DRV_CAP_HIGH,          /*!< GPIO Drive Capability High         */
    GPIO_DRV_CAP_VERY_HIGH      /*!< GPIO Drive Capability Very High    */
} GPIO_DrvCapETypeDef;

/**
  * @brief GPIO Init structure definition
  */
typedef struct __GPIO_InitTypeDef {
    //Common Config
    uint32_t           Pin;         /*!< GPIO pins, combination of GPIO_PinETypeDef */
    GPIO_AFETypeDef    Alternate;   /*!< GPIO pinmux function                       */
    GPIO_PullETypeDef  Pull;        /*!< GPIO pull (null/up/down)                   */

    //Input Config
    GPIO_IntModeETypeDef IntMode;   /*!< GPIO Interrupt Mode (input only)           */

    //Output Config
    GPIO_SpeedETypeDef   Speed;     /*!< GPIO speed                                 */
    GPIO_OutputETypeDef  OType;     /*!< GPIO output type (output or AF output only)*/
    GPIO_DrvCapETypeDef  DrvCap;    /*!< GPIO drive capability level                */
} GPIO_InitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup GPIO_LL_Exported_Functions
  * @{
  */

/** @addtogroup GPIO_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_GPIO_Init(GPIO_TypeDef       *Instance, GPIO_InitTypeDef *gpio_init);
LL_StatusETypeDef LL_GPIO_DeInit(GPIO_TypeDef *Instance, uint32_t pins);
/**
  * @}
  */


/** @addtogroup GPIO_LL_Exported_Functions_Group2
  * @{
  */
void LL_GPIO_AF_Config(GPIO_TypeDef *Instance, uint32_t pins, GPIO_AFETypeDef alternate);

GPIO_PinStateETypeDef LL_GPIO_ReadPin(GPIO_TypeDef *Instance, uint32_t pin);
void LL_GPIO_WritePin(GPIO_TypeDef *Instance, uint32_t pin, GPIO_PinStateETypeDef pin_state);
void LL_GPIO_TogglePin(GPIO_TypeDef *Instance, uint32_t pin);

uint32_t LL_GPIO_ReadData(GPIO_TypeDef *Instance);
void LL_GPIO_WriteData(GPIO_TypeDef *Instance, uint16_t dat);
/**
  * @}
  */


/** @addtogroup GPIO_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_GPIO_IRQHandler(GPIO_TypeDef *Instance);
void LL_GPIO_ExtTrigCallback(GPIO_TypeDef *Instance, uint32_t pin);
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
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_GPIO_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

