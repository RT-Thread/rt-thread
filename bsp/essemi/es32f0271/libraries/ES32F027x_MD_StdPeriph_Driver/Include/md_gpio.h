/**
  ******************************************************************************
  * @file    md_GPIO.h
  * @brief   ES32F0271 GPIO HEAD File.
  *
  * @version V1.00.02
  * @date    30/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_GPIO_H__
#define __MD_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_gpio.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD)

/** @defgroup GPIO GPIO
  * @brief GPIO micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_GPIO_PT_INIT GPIO Public Init structures
  * @{
  */

/**
  * @brief MD GPIO Init Structure definition
  */
typedef struct
{
  uint32_t Pin;          /*!< Specifies the GPIO pins to be configured.
                              This parameter can be any value of @ref MD_GPIO_PC_PIN */

  uint32_t Mode;         /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref MD_GPIO_PC_MODE.

                              GPIO HW configuration can be modified afterwards using unitary function @ref md_gpio_set_mode().*/

  uint32_t OutputType;   /*!< Specifies the operating output type for the selected pins.
                              This parameter can be a value of @ref MD_GPIO_PC_OT.

                              GPIO HW configuration can be modified afterwards using unitary function @ref md_gpio_set_output_type().*/


  uint32_t Pull;         /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                              This parameter can be a value of @ref MD_GPIO_PC_PULL.

                              GPIO HW configuration can be modified afterwards using unitary function @ref md_gpio_set_pull().*/

  uint32_t OutDrive;     /*!< Specifies the output driving current for the selected pins.
                              This parameter can be a value of @ref MD_GPIO_PC_DS.

                              GPIO HW configuration can be modified afterwards using unitary function @ref md_gpio_get_ds().*/

  uint32_t Function;     /*!< Specifies the Peripheral to be connected to the selected pins.
                              This parameter can be a value of @ref MD_GPIO_PC_FUNCTION.

                              GPIO HW configuration can be modified afterwards using unitary function @ref md_gpio_set_function0_7() and md_gpio_set_function8_15().*/
} md_gpio_inittypedef;

/**
  * @} MD_GPIO_PT_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_GPIO_Public_Constants GPIO Public Constants
  * @{
  */

/** @defgroup MD_GPIO_PC_PIN PIN
  * @{
  */
#define MD_GPIO_PIN_0                      (0X1<<0)  /*!< Select pin 0 */
#define MD_GPIO_PIN_1                      (0X1<<1)  /*!< Select pin 1 */
#define MD_GPIO_PIN_2                      (0X1<<2)  /*!< Select pin 2 */
#define MD_GPIO_PIN_3                      (0X1<<3)  /*!< Select pin 3 */
#define MD_GPIO_PIN_4                      (0X1<<4)  /*!< Select pin 4 */
#define MD_GPIO_PIN_5                      (0X1<<5)  /*!< Select pin 5 */
#define MD_GPIO_PIN_6                      (0X1<<6)  /*!< Select pin 6 */
#define MD_GPIO_PIN_7                      (0X1<<7)  /*!< Select pin 7 */
#define MD_GPIO_PIN_8                      (0X1<<8)  /*!< Select pin 8 */
#define MD_GPIO_PIN_9                      (0X1<<9)  /*!< Select pin 9 */
#define MD_GPIO_PIN_10                     (0X1<<10) /*!< Select pin 10 */
#define MD_GPIO_PIN_11                     (0X1<<11) /*!< Select pin 11 */
#define MD_GPIO_PIN_12                     (0X1<<12) /*!< Select pin 12 */
#define MD_GPIO_PIN_13                     (0X1<<13) /*!< Select pin 13 */
#define MD_GPIO_PIN_14                     (0X1<<14) /*!< Select pin 14 */
#define MD_GPIO_PIN_15                     (0X1<<15) /*!< Select pin 15 */
#define MD_GPIO_PIN_ALL                    (MD_GPIO_PIN_0 | MD_GPIO_PIN_1  | MD_GPIO_PIN_2  | \
                                           MD_GPIO_PIN_3  | MD_GPIO_PIN_4  | MD_GPIO_PIN_5  | \
                                           MD_GPIO_PIN_6  | MD_GPIO_PIN_7  | MD_GPIO_PIN_8  | \
                                           MD_GPIO_PIN_9  | MD_GPIO_PIN_10 | MD_GPIO_PIN_11 | \
                                           MD_GPIO_PIN_12 | MD_GPIO_PIN_13 | MD_GPIO_PIN_14 | \
                                           MD_GPIO_PIN_15) /*!< Select all pins */
/**
  * @} MD_GPIO_PC_PIN
  */

/** @defgroup MD_GPIO_PC_MODE Mode
  * @{
  */
#define MD_GPIO_MODE_INPUT                 (0x00000000UL)       /** @brief Select input mode */
#define MD_GPIO_MODE_OUTPUT                (0X00000001UL)       /** @brief Select output mode */
#define MD_GPIO_MODE_FUNCTION              (0X00000002UL)       /** @brief Select function mode */
#define MD_GPIO_MODE_ANALOG                (0x00000003UL)       /** @brief Select analog mode */
/**
  * @} MD_GPIO_PC_MODE
  */

/** @defgroup MD_GPIO_PC_OT Output Type
  * @{
  */
#define MD_GPIO_OUTPUT_PUSHPULL            (0x00000000U) /** @brief Select push-pull as output type */
#define MD_GPIO_OUTPUT_OPENDRAIN           (0x00000001U) /** @brief Select open-drain as output type */
/**
  * @} MD_GPIO_PC_OT
  */

/** @defgroup MD_GPIO_PC_PULL Pull Up Pull Down
  * @{
  */
#define MD_GPIO_PULL_FLOATING              (0x00000000UL) /** @brief Select I/O no pull */
#define MD_GPIO_PULL_UP                    (0x00000001UL) /** @brief Select I/O pull up */
#define MD_GPIO_PULL_DOWN                  (0x00000002UL) /** @brief Select I/O pull down */
/**
  * @} MD_GPIO_PC_PULL
  */

/** @defgroup MD_GPIO_PC_DS Output driving/sinking current
  * @{
  */
#define MD_GPIO_DS_16mA                    (0x00000001U) /** @brief Select I/O 16mA driving/sinking current */
#define MD_GPIO_DS_8mA                     (0x00000000U) /** @brief Select I/O 8mA driving/sinking current */
/**
  * @} MD_GPIO_PC_DS
  */

/** @defgroup MD_GPIO_PC_FUNCTION Alternate Function
  * @{
  */
#define MD_GPIO_AF0                       (0x00000000UL) /** @brief Select alternate function 0 */
#define MD_GPIO_AF1                       (0x00000001UL) /** @brief Select alternate function 1 */
#define MD_GPIO_AF2                       (0x00000002UL) /** @brief Select alternate function 2 */
#define MD_GPIO_AF3                       (0x00000003UL) /** @brief Select alternate function 3 */
#define MD_GPIO_AF4                       (0x00000004UL) /** @brief Select alternate function 4 */
#define MD_GPIO_AF5                       (0x00000005UL) /** @brief Select alternate function 5 */
#define MD_GPIO_AF6                       (0x00000006UL) /** @brief Select alternate function 6 */
#define MD_GPIO_AF7                       (0x00000007UL) /** @brief Select alternate function 7 */
#define MD_GPIO_AF8                       (0x00000008UL) /** @brief Select alternate function 8 */
/**
  * @} MD_GPIO_PC_FUNCTION
  */

/** @defgroup MD_GPIO_PC_FILTER Input Filter
  * @{
  */
#define MD_GPIO_FILTER_BYPASS             (0x00000000UL) /** @brief Select bypass */
#define MD_GPIO_FILTER_GLITCH             (0x00000001UL) /** @brief Select glitch free for 20ns plus */
/**
  * @} MD_GPIO_PC_FILTER
  */

/** @defgroup MD_GPIO_PC_IST Input Schmitt Trigger
  * @{
  */
#define MD_GPIO_IST_TTL                   (0x00000000UL) /** @brief Select TTL IO Level */
#define MD_GPIO_IST_CMOS                  (0x00000001UL) /** @brief Select CMOS IO Level */
/**
  * @} MD_GPIO_PC_IST
  */

/** @defgroup MD_GPIO_ODATA_SEL GPIO Output Select
  * @{
  */
#define MD_GPIO_OUTPUT_LOW                   (0x00000000UL) /** @brief Select GPIO Output Low*/
#define MD_GPIO_OUTPUT_HIGH                  (0x00000001UL) /** @brief Select GPIO Output High*/
/**
  * @} MD_GPIO_ODATA_SEL
  */

/**
  * @} MD_GPIO_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_GPIO_Public_Macros GPIO Public Macros
  * @{
  */

/** @defgroup MD_GPIO_MOD_MOD15 MOD15
  * @brief  Set MOD15 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod15_fun(mod15)  (mod15<<GPIO_MOD_MOD15_POSS)
/**
  * @} MD_GPIO_MOD_MOD15
  */
/** @defgroup MD_GPIO_MOD_MOD14 MOD14
  * @brief  Set MOD14 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod14_fun(mod14)  (mod14<<GPIO_MOD_MOD14_POSS)
/**
  * @} MD_GPIO_MOD_MOD14
  */
/** @defgroup MD_GPIO_MOD_MOD13 MOD13
  * @brief  Set MOD13 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod13_fun(mod13)  (mod13<<GPIO_MOD_MOD13_POSS)
/**
  * @} MD_GPIO_MOD_MOD13
  */
/** @defgroup MD_GPIO_MOD_MOD12 MOD12
  * @brief  Set MOD12 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod12_fun(mod12)  (mod12<<GPIO_MOD_MOD12_POSS)
/**
  * @} MD_GPIO_MOD_MOD12
  */
/** @defgroup MD_GPIO_MOD_MOD11 MOD11
  * @brief  Set MOD11 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod11_fun(mod11)  (mod11<<GPIO_MOD_MOD11_POSS)
/**
  * @} MD_GPIO_MOD_MOD11
  */
/** @defgroup MD_GPIO_MOD_MOD10 MOD10
  * @brief  Set MOD10 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod10_fun(mod10)  (mod10<<GPIO_MOD_MOD10_POSS)
/**
  * @} MD_GPIO_MOD_MOD10
  */
/** @defgroup MD_GPIO_MOD_MOD9 MOD9
  * @brief  Set MOD9 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod9_fun(mod9)  (mod9<<GPIO_MOD_MOD9_POSS)
/**
  * @} MD_GPIO_MOD_MOD9
  */
/** @defgroup MD_GPIO_MOD_MOD8 MOD8
  * @brief  Set MOD8 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod8_fun(mod8)  (mod8<<GPIO_MOD_MOD8_POSS)
/**
  * @} MD_GPIO_MOD_MOD8
  */
/** @defgroup MD_GPIO_MOD_MOD7 MOD7
  * @brief  Set MOD7 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod7_fun(mod7)  (mod7<<GPIO_MOD_MOD7_POSS)
/**
  * @} MD_GPIO_MOD_MOD7
  */
/** @defgroup MD_GPIO_MOD_MOD6 MOD6
  * @brief  Set MOD6 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod6_fun(mod6)  (mod6<<GPIO_MOD_MOD6_POSS)
/**
  * @} MD_GPIO_MOD_MOD6
  */
/** @defgroup MD_GPIO_MOD_MOD5 MOD5
  * @brief  Set MOD5 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod5_fun(mod5)  (mod5<<GPIO_MOD_MOD5_POSS)
/**
  * @} MD_GPIO_MOD_MOD5
  */
/** @defgroup MD_GPIO_MOD_MOD4 MOD4
  * @brief  Set MOD4 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod4_fun(mod4)  (mod4<<GPIO_MOD_MOD4_POSS)
/**
  * @} MD_GPIO_MOD_MOD4
  */
/** @defgroup MD_GPIO_MOD_MOD3 MOD3
  * @brief  Set MOD3 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod3_fun(mod3)  (mod3<<GPIO_MOD_MOD3_POSS)
/**
  * @} MD_GPIO_MOD_MOD3
  */
/** @defgroup MD_GPIO_MOD_MOD2 MOD2
  * @brief  Set MOD2 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod2_fun(mod2)  (mod2<<GPIO_MOD_MOD2_POSS)
/**
  * @} MD_GPIO_MOD_MOD2
  */
/** @defgroup MD_GPIO_MOD_MOD1 MOD1
  * @brief  Set MOD1 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod1_fun(mod1)  (mod1<<GPIO_MOD_MOD1_POSS)
/**
  * @} MD_GPIO_MOD_MOD1
  */
/** @defgroup MD_GPIO_MOD_MOD0 MOD0
  * @brief  Set MOD0 configure I/O mode bit for md_gpio_set_mod() function used
  * @param  mod0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @{
  */
#define md_gpio_set_mod_mod0_fun(mod0)  (mod0<<GPIO_MOD_MOD0_POSS)
/**
  * @} MD_GPIO_MOD_MOD0
  */
/**
  * @brief  Set GPIOx port Mode register
  * @param  GPIOx GPIO Port
  * @param  mod15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod15_fun(mod15)
  * @param  mod14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod14_fun(mod14)
  * @param  mod13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod13_fun(mod13)
  * @param  mod12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod12_fun(mod12)
  * @param  mod11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod11_fun(mod11)
  * @param  mod10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod10_fun(mod10)
  * @param  mod9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod9_fun(mod9)
  * @param  mod8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod8_fun(mod8)
  * @param  mod7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod7_fun(mod7)
  * @param  mod6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod6_fun(mod6)
  * @param  mod5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod5_fun(mod5)
  * @param  mod4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod4_fun(mod4)
  * @param  mod3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod3_fun(mod3)
  * @param  mod2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod2_fun(mod2)
  * @param  mod1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod1_fun(mod1)
  * @param  mod0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_mod_mod0_fun(mod0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_mod(GPIO_TypeDef *GPIOx, uint32_t mod15, uint32_t mod14,  uint32_t mod13,
                                                          uint32_t mod12, uint32_t mod11,  uint32_t mod10,
                                                          uint32_t mod9,  uint32_t mod8,   uint32_t mod7,
                                                          uint32_t mod6,  uint32_t mod5,   uint32_t mod4,
                                                          uint32_t mod3,  uint32_t mod2,   uint32_t mod1,
                                                          uint32_t mod0)
{
  WRITE_REG(GPIOx->MOD, (mod15|mod14|mod13|mod12|mod11|mod10|mod9|mod8|mod7|mod6|mod5|mod4|mod3|mod2|mod1|mod0));
}




/**
  * @brief  Configure gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, output mode, Alternate function mode, or Analog mode.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(GPIOx->MOD, (GPIO_MOD_MOD0_MSK << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}

/**
  * @brief  Return gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, output mode, Alternate function mode, or Analog mode.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_GPIO_MODE_INPUT
  *         @arg @ref MD_GPIO_MODE_OUTPUT
  *         @arg @ref MD_GPIO_MODE_FUNCTION
  *         @arg @ref MD_GPIO_MODE_ANALOG
  */
__STATIC_INLINE uint32_t md_gpio_get_mode(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->MOD,
                             (GPIO_MOD_MOD0_MSK << (POSITION_VAL(Pin) * 2U))) >> (POSITION_VAL(Pin) * 2U));
}

/** @defgroup MD_GPIO_OT_OT15 OT15
  * @brief  Set OT15 output data bit for md_gpio_set_ot() function used
  * @param  ot15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot15_fun(ot15)  (ot15<<GPIO_OT_OT15_POS)
/**
  * @} MD_GPIO_OT_OT15
  */
/** @defgroup MD_GPIO_OT_OT14 OT14
  * @brief  Set OT14 output data bit for md_gpio_set_ot() function used
  * @param  ot14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot14_fun(ot14)  (ot14<<GPIO_OT_OT14_POS)
/**
  * @} MD_GPIO_OT_OT14
  */
/** @defgroup MD_GPIO_OT_OT13 OT13
  * @brief  Set OT13 output data bit for md_gpio_set_ot() function used
  * @param  ot13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot13_fun(ot13)  (ot13<<GPIO_OT_OT13_POS)
/**
  * @} MD_GPIO_OT_OT13
  */
/** @defgroup MD_GPIO_OT_OT12 OT12
  * @brief  Set OT12 output data bit for md_gpio_set_ot() function used
  * @param  ot12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot12_fun(ot12)  (ot12<<GPIO_OT_OT12_POS)
/**
  * @} MD_GPIO_OT_OT12
  */
/** @defgroup MD_GPIO_OT_OT11 OT11
  * @brief  Set OT11 output data bit for md_gpio_set_ot() function used
  * @param  ot11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot11_fun(ot11)  (ot11<<GPIO_OT_OT11_POS)
/**
  * @} MD_GPIO_OT_OT11
  */
/** @defgroup MD_GPIO_OT_OT10 OT10
  * @brief  Set OT10 output data bit for md_gpio_set_ot() function used
  * @param  ot10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot10_fun(ot10)  (ot10<<GPIO_OT_OT10_POS)
/**
  * @} MD_GPIO_OT_OT10
  */
/** @defgroup MD_GPIO_OT_OT9 OT9
  * @brief  Set OT9 output data bit for md_gpio_set_ot() function used
  * @param  ot9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot9_fun(ot9)    (ot9<<GPIO_OT_OT9_POS)
/**
  * @} MD_GPIO_OT_OT9
  */
/** @defgroup MD_GPIO_OT_OT8 OT8
  * @brief  Set OT8 output data bit for md_gpio_set_ot() function used
  * @param  ot8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot8_fun(ot8)    (ot8<<GPIO_OT_OT8_POS)
/**
  * @} MD_GPIO_OT_OT8
  */
/** @defgroup MD_GPIO_OT_OT7 OT7
  * @brief  Set OT7 output data bit for md_gpio_set_ot() function used
  * @param  ot7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot7_fun(ot7)    (ot7<<GPIO_OT_OT7_POS)
/**
  * @} MD_GPIO_OT_OT7
  */
/** @defgroup MD_GPIO_OT_OT6 OT6
  * @brief  Set OT6 output data bit for md_gpio_set_ot() function used
  * @param  ot6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot6_fun(ot6)    (ot6<<GPIO_OT_OT6_POS)
/**
  * @} MD_GPIO_OT_OT6
  */
/** @defgroup MD_GPIO_OT_OT5 OT5
  * @brief  Set OT5 output data bit for md_gpio_set_ot() function used
  * @param  ot5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot5_fun(ot5)    (ot5<<GPIO_OT_OT5_POS)
/**
  * @} MD_GPIO_OT_OT5
  */
/** @defgroup MD_GPIO_OT_OT4 OT4
  * @brief  Set OT4 output data bit for md_gpio_set_ot() function used
  * @param  ot4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot4_fun(ot4)    (ot4<<GPIO_OT_OT4_POS)
/**
  * @} MD_GPIO_OT_OT4
  */
/** @defgroup MD_GPIO_OT_OT3 OT3
  * @brief  Set OT3 output data bit for md_gpio_set_ot() function used
  * @param  ot3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot3_fun(ot3)    (ot3<<GPIO_OT_OT3_POS)
/**
  * @} MD_GPIO_OT_OT3
  */
/** @defgroup MD_GPIO_OT_OT2 OT2
  * @brief  Set OT2 output data bit for md_gpio_set_ot() function used
  * @param  ot2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot2_fun(ot2)    (ot2<<GPIO_OT_OT2_POS)
/**
  * @} MD_GPIO_OT_OT2
  */
/** @defgroup MD_GPIO_OT_OT1 OT1
  * @brief  Set OT1 output data bit for md_gpio_set_ot() function used
  * @param  ot1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot1_fun(ot1)    (ot1<<GPIO_OT_OT1_POS)
/**
  * @} MD_GPIO_OT_OT1
  */
/** @defgroup MD_GPIO_OT_OT0 OT0
  * @brief  Set OT0 output data bit for md_gpio_set_ot() function used
  * @param  ot0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @{
  */
#define md_gpio_set_ot_ot0_fun(ot0)    (ot0<<GPIO_OT_OT0_POS)
/**
  * @} MD_GPIO_OT_OT0
  */
/**
  * @brief  Set GPIOx port Output Type register
  * @param  GPIOx GPIO Port
  * @param  ot15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot15_fun(ot15)
  * @param  ot14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot14_fun(ot14)
  * @param  ot13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot13_fun(ot13)
  * @param  ot12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot12_fun(ot12)
  * @param  ot11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot11_fun(ot11)
  * @param  ot10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot10_fun(ot10)
  * @param  ot9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot9_fun(ot9)
  * @param  ot8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot8_fun(ot8)
  * @param  ot7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot7_fun(ot7)
  * @param  ot6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot6_fun(ot6)
  * @param  ot5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot5_fun(ot5)
  * @param  ot4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot4_fun(ot4)
  * @param  ot3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot3_fun(ot3)
  * @param  ot2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot2_fun(ot2)
  * @param  ot1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot1_fun(ot1)
  * @param  ot0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ot_ot0_fun(ot0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_ot(GPIO_TypeDef *GPIOx,  uint32_t ot15, uint32_t ot14,  uint32_t ot13,
                                                          uint32_t ot12, uint32_t ot11,  uint32_t ot10,
                                                          uint32_t ot9,  uint32_t ot8,   uint32_t ot7,
                                                          uint32_t ot6,  uint32_t ot5,   uint32_t ot4,
                                                          uint32_t ot3,  uint32_t ot2,   uint32_t ot1,
                                                          uint32_t ot0)
{
  WRITE_REG(GPIOx->OT, (ot15|ot14|ot13|ot12|ot11|ot10|ot9|ot8|ot7|ot6|ot5|ot4|ot3|ot2|ot1|ot0));
}


/**
  * @brief  Configure gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  OutputType This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_output_type(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t OutputType)
{
  MODIFY_REG(GPIOx->OT, (GPIO_OT_OT0_MSK << (POSITION_VAL(Pin))), (OutputType << (POSITION_VAL(Pin))));
}

/**
  * @brief  Return gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MD_GPIO_OUTPUT_OPENDRAIN
  */
__STATIC_INLINE uint32_t md_gpio_get_output_type(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)((READ_BIT(GPIOx->OT,
                             (GPIO_OT_OT_MSK << (POSITION_VAL(Pin)))) >> (POSITION_VAL(Pin))) & (0x1U));
}


/** @defgroup MD_GPIO_PUD_PUD15 PUD15
  * @brief  Set PUD15 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud15_fun(pud15)    (pud15<<GPIO_PUD_PUD15_POSS)
/**
  * @} MD_GPIO_PUD_PUD15
  */
/** @defgroup MD_GPIO_PUD_PUD14 PUD14
  * @brief  Set PUD14 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud14_fun(pud14)  (pud14<<GPIO_PUD_PUD14_POSS)
/**
  * @} MD_GPIO_PUD_PUD14
  */
/** @defgroup MD_GPIO_PUD_PUD13 PUD13
  * @brief  Set PUD13 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud13_fun(pud13)  (pud13<<GPIO_PUD_PUD13_POSS)
/**
  * @} MD_GPIO_PUD_PUD13
  */
/** @defgroup MD_GPIO_PUD_PUD12 PUD12
  * @brief  Set PUD12 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud12_fun(pud12)  (pud12<<GPIO_PUD_PUD12_POSS)
/**
  * @} MD_GPIO_PUD_PUD12
  */
/** @defgroup MD_GPIO_PUD_PUD11 PUD11
  * @brief  Set PUD11 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud11_fun(pud11)  (pud11<<GPIO_PUD_PUD11_POSS)
/**
  * @} MD_GPIO_PUD_PUD11
  */
/** @defgroup MD_GPIO_PUD_PUD10 PUD10
  * @brief  Set PUD10 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud10_fun(pud10)  (pud10<<GPIO_PUD_PUD10_POSS)
/**
  * @} MD_GPIO_PUD_PUD10
  */
/** @defgroup MD_GPIO_PUD_PUD9 PUD9
  * @brief  Set PUD9 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud9_fun(pud9)    (pud9<<GPIO_PUD_PUD9_POSS)
/**
  * @} MD_GPIO_PUD_PUD9
  */
/** @defgroup MD_GPIO_PUD_PUD8 PUD8
  * @brief  Set PUD8 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud8_fun(pud8)    (pud8<<GPIO_PUD_PUD8_POSS)
/**
  * @} MD_GPIO_PUD_PUD8
  */
/** @defgroup MD_GPIO_PUD_PUD7 PUD7
  * @brief  Set PUD7 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud7_fun(pud7)    (pud7<<GPIO_PUD_PUD7_POSS)
/**
  * @} MD_GPIO_PUD_PUD7
  */
/** @defgroup MD_GPIO_PUD_PUD6 PUD6
  * @brief  Set PUD6 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud6_fun(pud6)    (pud6<<GPIO_PUD_PUD6_POSS)
/**
  * @} MD_GPIO_PUD_PUD6
  */
/** @defgroup MD_GPIO_PUD_PUD5 PUD5
  * @brief  Set PUD5 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud5_fun(pud5)    (pud5<<GPIO_PUD_PUD5_POSS)
/**
  * @} MD_GPIO_PUD_PUD5
  */
/** @defgroup MD_GPIO_PUD_PUD4 PUD4
  * @brief  Set PUD4 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud4_fun(pud4)    (pud4<<GPIO_PUD_PUD4_POSS)
/**
  * @} MD_GPIO_PUD_PUD4
  */
/** @defgroup MD_GPIO_PUD_PUD3 PUD3
  * @brief  Set PUD3 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud3_fun(pud3)    (pud3<<GPIO_PUD_PUD3_POSS)
/**
  * @} MD_GPIO_PUD_PUD3
  */
/** @defgroup MD_GPIO_PUD_PUD2 PUD2
  * @brief  Set PUD2 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud2_fun(pud2)    (pud2<<GPIO_PUD_PUD2_POSS)
/**
  * @} MD_GPIO_PUD_PUD2
  */
/** @defgroup MD_GPIO_PUD_PUD1 PUD1
  * @brief  Set PUD1 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud1_fun(pud1)    (pud1<<GPIO_PUD_PUD1_POSS)
/**
  * @} MD_GPIO_PUD_PUD1
  */
/** @defgroup MD_GPIO_PUD_PUD0 PUD0
  * @brief  Set PUD0 I/O pull-up or pull-down bit for md_gpio_set_pud() function used
  * @param  pud0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @{
  */
#define md_gpio_set_pud_pud0_fun(pud0)    (pud0<<GPIO_PUD_PUD0_POSS)
/**
  * @} MD_GPIO_PUD_PUD0
  */
/**
  * @brief  Set GPIOx port pull-up/pull-down register
  * @param  GPIOx GPIO Port
  * @param  pud15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud15_fun(pud15)
  * @param  pud14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud14_fun(pud14)
  * @param  pud13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud13_fun(pud13)
  * @param  pud12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud12_fun(pud12)
  * @param  pud11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud11_fun(pud11)
  * @param  pud10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud10_fun(pud10)
  * @param  pud9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud9_fun(pud9)
  * @param  pud8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud8_fun(pud8)
  * @param  pud7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud7_fun(pud7)
  * @param  pud6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud6_fun(pud6)
  * @param  pud5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud5_fun(pud5)
  * @param  pud4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud4_fun(pud4)
  * @param  pud3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud3_fun(pud3)
  * @param  pud2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud2_fun(pud2)
  * @param  pud1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud1_fun(pud1)
  * @param  pud0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_pud_pud0_fun(pud0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pud(GPIO_TypeDef *GPIOx, uint32_t pud15, uint32_t pud14,  uint32_t pud13,
                                                          uint32_t pud12, uint32_t pud11,  uint32_t pud10,
                                                          uint32_t pud9,  uint32_t pud8,   uint32_t pud7,
                                                          uint32_t pud6,  uint32_t pud5,   uint32_t pud4,
                                                          uint32_t pud3,  uint32_t pud2,   uint32_t pud1,
                                                          uint32_t pud0)
{
  WRITE_REG(GPIOx->PUD, (pud15|pud14|pud13|pud12|pud11|pud10|pud9|pud8|pud7|pud6|pud5|pud4|pud3|pud2|pud1|pud0));
}

/**
  * @brief  Configure gpio pull-up or pull-down for a dedicated pin on a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  Pull This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
  MODIFY_REG(GPIOx->PUD, (GPIO_PUD_PUD0_MSK << (POSITION_VAL(Pin) * 2U)), (Pull << (POSITION_VAL(Pin) * 2U)));
}

/**
  * @brief  Return gpio pull-up or pull-down for a dedicated pin on a dedicated port
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_GPIO_PULL_FLOATING
  *         @arg @ref MD_GPIO_PULL_UP
  *         @arg @ref MD_GPIO_PULL_DOWN
  */
__STATIC_INLINE uint32_t md_gpio_get_pull(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->PUD,
                             (GPIO_PUD_PUD0_MSK << (POSITION_VAL(Pin) * 2U))) >> (POSITION_VAL(Pin) * 2U));
}


/** @defgroup MD_GPIO_DS_DS15 DS15
  * @brief  Set DS15 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds15_fun(ds15)    (ds15<<GPIO_DS_DS15_POS)
/**
  * @} MD_GPIO_DS_DS15
  */
/** @defgroup MD_GPIO_DS_DS14 DS14
  * @brief  Set DS14 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds14_fun(ds14)    (ds14<<GPIO_DS_DS14_POS)
/**
  * @} MD_GPIO_DS_DS14
  */
/** @defgroup MD_GPIO_DS_DS13 DS13
  * @brief  Set DS13 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds13_fun(ds13)    (ds13<<GPIO_DS_DS13_POS)
/**
  * @} MD_GPIO_DS_DS13
  */
/** @defgroup MD_GPIO_DS_DS12 DS12
  * @brief  Set DS12 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds12_fun(ds12)    (ds12<<GPIO_DS_DS12_POS)
/**
  * @} MD_GPIO_DS_DS12
  */
/** @defgroup MD_GPIO_DS_DS11 DS11
  * @brief  Set DS11 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds11_fun(ds11)    (ds11<<GPIO_DS_DS11_POS)
/**
  * @} MD_GPIO_DS_DS11
  */
/** @defgroup MD_GPIO_DS_DS10 DS10
  * @brief  Set DS10 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds10_fun(ds10)    (ds10<<GPIO_DS_DS10_POS)
/**
  * @} MD_GPIO_DS_DS10
  */
/** @defgroup MD_GPIO_DS_DS9 DS9
  * @brief  Set DS9 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds9_fun(ds9)    (ds9<<GPIO_DS_DS9_POS)
/**
  * @} MD_GPIO_DS_DS9
  */
/** @defgroup MD_GPIO_DS_DS8 DS8
  * @brief  Set DS8 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds8_fun(ds8)    (ds8<<GPIO_DS_DS8_POS)
/**
  * @} MD_GPIO_DS_DS8
  */
/** @defgroup MD_GPIO_DS_DS7 DS7
  * @brief  Set DS7 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds7_fun(ds7)    (ds7<<GPIO_DS_DS7_POS)
/**
  * @} MD_GPIO_DS_DS7
  */
/** @defgroup MD_GPIO_DS_DS6 DS6
  * @brief  Set DS6 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds6_fun(ds6)    (ds6<<GPIO_DS_DS6_POS)
/**
  * @} MD_GPIO_DS_DS6
  */
/** @defgroup MD_GPIO_DS_DS5 DS5
  * @brief  Set DS5 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds5_fun(ds5)    (ds5<<GPIO_DS_DS5_POS)
/**
  * @} MD_GPIO_DS_DS5
  */
/** @defgroup MD_GPIO_DS_DS4 DS4
  * @brief  Set DS4 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds4_fun(ds4)    (ds4<<GPIO_DS_DS4_POS)
/**
  * @} MD_GPIO_DS_DS4
  */
/** @defgroup MD_GPIO_DS_DS3 DS3
  * @brief  Set DS3 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds3_fun(ds3)    (ds3<<GPIO_DS_DS3_POS)
/**
  * @} MD_GPIO_DS_DS3
  */
/** @defgroup MD_GPIO_DS_DS2 DS2
  * @brief  Set DS2 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds2_fun(ds2)    (ds2<<GPIO_DS_DS2_POS)
/**
  * @} MD_GPIO_DS_DS2
  */
/** @defgroup MD_GPIO_DS_DS1 DS1
  * @brief  Set DS1 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds1_fun(ds1)    (ds1<<GPIO_DS_DS1_POS)
/**
  * @} MD_GPIO_DS_DS1
  */

/** @defgroup MD_GPIO_DS_DS0 DS0
  * @brief  Set DS0 I/O Driving/Sinking current bit for md_gpio_set_ds() function used
  * @param  ds0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @{
  */
#define md_gpio_set_ds_ds0_fun(ds0)    (ds0<<GPIO_DS_DS0_POS)
/**
  * @} MD_GPIO_DS_DS0
  */
/**
  * @brief  Set GPIOx port Output Driving register
  * @param  GPIOx GPIO Port
  * @param  ds15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds15_fun(ds15)
  * @param  ds14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds14_fun(ds14)
  * @param  ds13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds13_fun(ds13)
  * @param  ds12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds12_fun(ds12)
  * @param  ds11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds11_fun(ds11)
  * @param  ds10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds10_fun(ds10)
  * @param  ds9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds9_fun(ds9)
  * @param  ds8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds8_fun(ds8)
  * @param  ds7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds7_fun(ds7)
  * @param  ds6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds6_fun(ds6)
  * @param  ds5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds5_fun(ds5)
  * @param  ds4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds4_fun(ds4)
  * @param  ds3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds3_fun(ds3)
  * @param  ds2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds2_fun(ds2)
  * @param  ds1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds1_fun(ds1)
  * @param  ds0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ds_ds0_fun(ds0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_ds_ds(GPIO_TypeDef *GPIOx, uint32_t ds15, uint32_t ds14,  uint32_t ds13,
                                                            uint32_t ds12, uint32_t ds11,  uint32_t ds10,
                                                            uint32_t ds9,  uint32_t ds8,   uint32_t ds7,
                                                            uint32_t ds6,  uint32_t ds5,   uint32_t ds4,
                                                            uint32_t ds3,  uint32_t ds2,   uint32_t ds1,
                                                            uint32_t ds0)
{
  WRITE_REG(GPIOx->DS, (ds15|ds14|ds13|ds12|ds11|ds10|ds9|ds8|ds7|ds6|ds5|ds4|ds3|ds2|ds1|ds0));
}


/**
  * @brief  Configure gpio output driving/sinking current a dedicated pin on a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  Odrv This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_ds(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Odrv)
{
  MODIFY_REG(GPIOx->DS, (GPIO_DS_DS_MSK << (POSITION_VAL(Pin))), (Odrv << (POSITION_VAL(Pin))));
}

/**
  * @brief  Return gpio output driving/sinking current a dedicated pin on a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_GPIO_DS_8mA
  *         @arg @ref MD_GPIO_DS_16mA
  */
__STATIC_INLINE uint32_t md_gpio_get_ds(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->DS,
                             (GPIO_DS_DS_MSK << (POSITION_VAL(Pin)))) >> (POSITION_VAL(Pin)));
}

/** @defgroup MD_GPIO_AFL_AF0 AF0
  * @brief  Set AF0 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af0_fun(af0)  (af0<<GPIO_AFL_AF0_POSS)
/**
  * @} MD_GPIO_AFL_AF0
  */
/** @defgroup MD_GPIO_AFL_AF1 AF1
  * @brief  Set AF1 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af1_fun(af1)  (af1<<GPIO_AFL_AF1_POSS)
/**
  * @} MD_GPIO_AFL_AF1
  */
/** @defgroup MD_GPIO_AFL_AF2 AF2
  * @brief  Set AF2 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af2_fun(af2)  (af2<<GPIO_AFL_AF2_POSS)
/**
  * @} MD_GPIO_AFL_AF2
  */
/** @defgroup MD_GPIO_AFL_AF3 AF3
  * @brief  Set AF3 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af3_fun(af3)  (af3<<GPIO_AFL_AF3_POSS)
/**
  * @} MD_GPIO_AFL_AF3
  */
/** @defgroup MD_GPIO_AFL_AF4 AF4
  * @brief  Set AF4 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af4_fun(af4)  (af4<<GPIO_AFL_AF4_POSS)
/**
  * @} MD_GPIO_AFL_AF4
  */
/** @defgroup MD_GPIO_AFL_AF5 AF5
  * @brief  Set AF5 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af5_fun(af5)  (af5<<GPIO_AFL_AF5_POSS)
/**
  * @} MD_GPIO_AFL_AF5
  */
/** @defgroup MD_GPIO_AFL_AF6 AF6
  * @brief  Set AF6 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af6_fun(af6)  (af6<<GPIO_AFL_AF6_POSS)
/**
  * @} MD_GPIO_AFL_AF6
  */
/** @defgroup MD_GPIO_AFL_AF7 AF7
  * @brief  Set AF7 Alternate function selection bit for md_gpio_set_afl() function used
  * @param  af7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afl_af7_fun(af7)  (af7<<GPIO_AFL_AF7_POSS)
/**
  * @} MD_GPIO_AFL_AF7
  */
/**
  * @brief  Set GPIOx port Alternate Function Low register
  * @param  GPIOx GPIO Port
  * @param  af7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af7_fun(af7)
  * @param  af6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af6_fun(af6)
  * @param  af5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af5_fun(af5)
  * @param  af4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af4_fun(af4)
  * @param  af3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af3_fun(af3)
  * @param  af2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af2_fun(af2)
  * @param  af1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af1_fun(af1)
  * @param  af0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afl_af0_fun(af0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_afl(GPIO_TypeDef *GPIOx, uint32_t af7, uint32_t af6,  uint32_t af5,
                                                          uint32_t af4, uint32_t af3,  uint32_t af2,
                                                          uint32_t af1, uint32_t af0)
{
  WRITE_REG(GPIOx->AFL, (af7|af6|af5|af4|af3|af2|af1|af0));
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @note   Possible values are from FUNCTION0 to FUNCTION7 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  * @param  Function This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_function0_7(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Function)
{
  MODIFY_REG(GPIOx->AFL, (GPIO_AFL_AF0_MSK << (POSITION_VAL(Pin) * 4U)),
             (Function << (POSITION_VAL(Pin) * 4U)));
}

/**
  * @brief  Return gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  */
__STATIC_INLINE uint32_t md_gpio_get_function0_7(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->AFL,
                             (GPIO_AFL_AF0_MSK << (POSITION_VAL(Pin) * 4U))) >> (POSITION_VAL(Pin) * 4U));
}


/** @defgroup MD_GPIO_AFH_AF8 AF8
  * @brief  Set AF8 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af8_fun(af8)    (af8<<GPIO_AFH_AF8_POSS)
/**
  * @} MD_GPIO_AFH_AF8
  */
/** @defgroup MD_GPIO_AFH_AF9 AF9
  * @brief  Set AF9 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af9_fun(af9)    (af9<<GPIO_AFH_AF9_POSS)
/**
  * @} MD_GPIO_AFH_AF9
  */
/** @defgroup MD_GPIO_AFH_AF10 AF10
  * @brief  Set AF10 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af10_fun(af10)  (af10<<GPIO_AFH_AF10_POSS)
/**
  * @} MD_GPIO_AFH_AF10
  */
/** @defgroup MD_GPIO_AFH_AF11 AF11
  * @brief  Set AF11 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af11_fun(af11)  (af11<<GPIO_AFH_AF11_POSS)
/**
  * @} MD_GPIO_AFH_AF11
  */
/** @defgroup MD_GPIO_AFH_AF12 AF12
  * @brief  Set AF12 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af12_fun(af12)  (af12<<GPIO_AFH_AF12_POSS)
/**
  * @} MD_GPIO_AFH_AF12
  */
/** @defgroup MD_GPIO_AFH_AF13 AF13
  * @brief  Set AF13 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af13_fun(af13)  (af13<<GPIO_AFH_AF13_POSS)
/**
  * @} MD_GPIO_AFH_AF13
  */
/** @defgroup MD_GPIO_AFH_AF14 AF14
  * @brief  Set AF14 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af14_fun(af14)  (af14<<GPIO_AFH_AF14_POSS)
/**
  * @} MD_GPIO_AFH_AF14
  */
/** @defgroup MD_GPIO_AFH_AF15 AF15
  * @brief  Set AF15 Alternate function selection bit for md_gpio_set_afh() function used
  * @param  af15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @{
  */
#define md_gpio_set_afh_af15_fun(af15)  (af15<<GPIO_AFH_AF15_POSS)
/**
  * @} MD_GPIO_AFH_AF15
  */
/**
  * @brief  Set GPIOx port Alternate Function High register
  * @param  GPIOx GPIO Port
  * @param  af15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af15_fun(af15)
  * @param  af14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af14_fun(af14)
  * @param  af13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af13_fun(af13)
  * @param  af12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af12_fun(af12)
  * @param  af11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af11_fun(af11)
  * @param  af10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af10_fun(af10)
  * @param  af9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af9_fun(af9)
  * @param  af8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_afh_af8_fun(af8)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_afh(GPIO_TypeDef *GPIOx, uint32_t af15,  uint32_t af14,  uint32_t af13,
                                                          uint32_t af12,  uint32_t af11,  uint32_t af10,
                                                          uint32_t af9,   uint32_t af8)
{
  WRITE_REG(GPIOx->AFH, (af15|af14|af13|af12|af11|af10|af9|af8));
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Possible values are from FUNCTION0 to FUNCTION7 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  Function This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_function8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Function)
{
  MODIFY_REG(GPIOx->AFH, (GPIO_AFH_AF8_MSK << (POSITION_VAL(Pin >> 8U) * 4U)),
             (Function << (POSITION_VAL(Pin >> 8U) * 4U)));
}

/**
  * @brief  Return gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MD_GPIO_AF0
  *         @arg @ref MD_GPIO_AF1
  *         @arg @ref MD_GPIO_AF2
  *         @arg @ref MD_GPIO_AF3
  *         @arg @ref MD_GPIO_AF4
  *         @arg @ref MD_GPIO_AF5
  *         @arg @ref MD_GPIO_AF6
  *         @arg @ref MD_GPIO_AF7
  */
__STATIC_INLINE uint32_t md_gpio_get_function8_15(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->AFH,
                             (GPIO_AFH_AF8_MSK << (POSITION_VAL(Pin >> 8U) * 4U))) >> (POSITION_VAL(Pin >> 8U) * 4U));
}

/**
  * @brief  Lock configuration of several pins for a dedicated port.
  * @note   When the lock sequence has been applied on a port bit, the
  *         value of this port bit can no longer be modified until the
  *         next reset.
  * @note   LOCK key write sequence:
  *         WR GPIOx_LCK = (~LCK[15:0]<<16) + LCK[15:0]
  *         WR GPIOx_LCK = (~LCK[15:0]<<16) + LCK[15:0]
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  *         @arg @ref MD_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_lock(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  SET_BIT(GPIOx->LCK, PinMask);
}

/**
  * @brief  Return 1 if all pins passed as parameter, of a dedicated port, are locked. else Return 0.
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  *         @arg @ref MD_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_gpio_get_lock(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->LCK, PinMask) == (PinMask));
}



/** @defgroup MD_GPIO_IST_IST15 IST15
  * @brief  Set IST15 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist15_fun(ist15)  (ist15<<GPIO_IST_IST15_POS)
/**
  * @} MD_GPIO_IST_IST15
  */


/** @defgroup MD_GPIO_IST_IST14 IST14
  * @brief  Set IST14 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist14_fun(ist14)  (ist14<<GPIO_IST_IST14_POS)
/**
  * @} MD_GPIO_IST_IST14
  */
/** @defgroup MD_GPIO_IST_IST13 IST13
  * @brief  Set IST13 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist13_fun(ist13)  (ist13<<GPIO_IST_IST13_POS)
/**
  * @} MD_GPIO_IST_IST13
  */
/** @defgroup MD_GPIO_IST_IST12 IST12
  * @brief  Set IST12 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist12_fun(ist12)  (ist12<<GPIO_IST_IST12_POS)
/**
  * @} MD_GPIO_IST_IST12
  */
/** @defgroup MD_GPIO_IST_IST11 IST11
  * @brief  Set IST11 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist11_fun(ist11)  (ist11<<GPIO_IST_IST11_POS)
/**
  * @} MD_GPIO_IST_IST11
  */
/** @defgroup MD_GPIO_IST_IST10 IST10
  * @brief  Set IST10 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist10_fun(ist10)  (ist10<<GPIO_IST_IST10_POS)
/**
  * @} MD_GPIO_IST_IST10
  */
/** @defgroup MD_GPIO_IST_IST9 IST9
  * @brief  Set IST9 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist9_fun(ist9)  (ist9<<GPIO_IST_IST9_POS)
/**
  * @} MD_GPIO_IST_IST9
  */
/** @defgroup MD_GPIO_IST_IST8 IST8
  * @brief  Set IST8 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist8_fun(ist8)  (ist8<<GPIO_IST_IST8_POS)
/**
  * @} MD_GPIO_IST_IST8
  */
/** @defgroup MD_GPIO_IST_IST7 IST7
  * @brief  Set IST7 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist7_fun(ist7)  (ist7<<GPIO_IST_IST7_POS)
/**
  * @} MD_GPIO_IST_IST7
  */
/** @defgroup MD_GPIO_IST_IST6 IST6
  * @brief  Set IST6 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist6_fun(ist6)  (ist6<<GPIO_IST_IST6_POS)
/**
  * @} MD_GPIO_IST_IST6
  */
/** @defgroup MD_GPIO_IST_IST5 IST5
  * @brief  Set IST5 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist5_fun(ist5)  (ist5<<GPIO_IST_IST5_POS)
/**
  * @} MD_GPIO_IST_IST5
  */
/** @defgroup MD_GPIO_IST_IST4 IST4
  * @brief  Set IST4 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist4_fun(ist4)  (ist4<<GPIO_IST_IST4_POS)
/**
  * @} MD_GPIO_IST_IST4
  */
/** @defgroup MD_GPIO_IST_IST3 IST3
  * @brief  Set IST3 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist3_fun(ist3)  (ist3<<GPIO_IST_IST3_POS)
/**
  * @} MD_GPIO_IST_IST3
  */
/** @defgroup MD_GPIO_IST_IST2 IST2
  * @brief  Set IST2 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist2_fun(ist2)  (ist2<<GPIO_IST_IST2_POS)
/**
  * @} MD_GPIO_IST_IST2
  */
/** @defgroup MD_GPIO_IST_IST1 IST1
  * @brief  Set IST1 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist1_fun(ist1)  (ist1<<GPIO_IST_IST1_POS)
/**
  * @} MD_GPIO_IST_IST1
  */
/** @defgroup MD_GPIO_IST_IST0 IST0
  * @brief  Set IST0 configure the input schmitt trigger level bit for md_gpio_set_ist_fun() function used
  * @param  ist0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @{
  */
#define md_gpio_set_ist_ist0_fun(ist0)  (ist0<<GPIO_IST_IST0_POS)
/**
  * @} MD_GPIO_IST_IST0
  */
/**
  * @brief  Set GPIOx port Input Schmitt Trigger Register
  * @param  GPIOx GPIO Port
  * @param  ist15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist15_fun(ist15)
  * @param  ist14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist14_fun(ist14)
  * @param  ist13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist13_fun(ist13)
  * @param  ist12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist12_fun(ist12)
  * @param  ist11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist11_fun(ist11)
  * @param  ist10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist10_fun(ist10)
  * @param  ist9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist9_fun(ist9)
  * @param  ist8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist8_fun(ist8)
  * @param  ist7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist7_fun(ist7)
  * @param  ist6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist6_fun(ist6)
  * @param  ist5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist5_fun(ist5)
  * @param  ist4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist4_fun(ist4)
  * @param  ist3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist3_fun(ist3)
  * @param  ist2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist2_fun(ist2)
  * @param  ist1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist1_fun(ist1)
  * @param  ist0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_ist_ist0_fun(ist0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_ist_fun(GPIO_TypeDef *GPIOx, uint32_t ist15, uint32_t ist14,  uint32_t ist13,
                                                              uint32_t ist12, uint32_t ist11,  uint32_t ist10,
                                                              uint32_t ist9,  uint32_t ist8,   uint32_t ist7,
                                                              uint32_t ist6,  uint32_t ist5,   uint32_t ist4,
                                                              uint32_t ist3,  uint32_t ist2,   uint32_t ist1,
                                                              uint32_t ist0)
{
  WRITE_REG(GPIOx->IST, (ist15|ist14|ist13|ist12|ist11|ist10|ist9|ist8|ist7|ist6|ist5|ist4|ist3|ist2|ist1|ist0));
}

/**
  * @brief  Configure GPIOx port Input Schmitt Trigger Register.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @param  Iolev This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_ist(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Iolev)
{
  MODIFY_REG(GPIOx->IST, (GPIO_IST_IST_MSK << (POSITION_VAL(Pin))), (Iolev << (POSITION_VAL(Pin))));
}

/**
  * @brief  Return GPIOx port Input Schmitt Trigger Register
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_GPIO_IST_TTL
  *         @arg @ref MD_GPIO_IST_CMOS
  */
__STATIC_INLINE uint32_t md_gpio_get_ist(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->IST, (GPIO_IST_IST_MSK << (POSITION_VAL(Pin)))) >> (POSITION_VAL(Pin)));
}

/**
  * @brief  Return full input data register value for a dedicated port.
  * @param  GPIOx GPIO Port
  * @retval Input data register value of port
  */
__STATIC_INLINE uint32_t md_gpio_get_input_port(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->IDATA));
}




/** @defgroup MD_GPIO_ODATA_OD15 OD15
  * @brief  Set OD15 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od15_fun(od15)  (od15<<GPIO_ODATA_OD15_POS)
/**
  * @} MD_GPIO_ODATA_OD15
  */
/** @defgroup MD_GPIO_ODATA_OD14 OD14
  * @brief  Set OD14 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od14_fun(od14)  (od14<<GPIO_ODATA_OD14_POS)
/**
  * @} MD_GPIO_ODATA_OD14
  */
/** @defgroup MD_GPIO_ODATA_OD13 OD13
  * @brief  Set OD13 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od13_fun(od13)  (od13<<GPIO_ODATA_OD13_POS)
/**
  * @} MD_GPIO_ODATA_OD13
  */
/** @defgroup MD_GPIO_ODATA_OD12 OD12
  * @brief  Set OD12 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od12_fun(od12)  (od12<<GPIO_ODATA_OD12_POS)
/**
  * @} MD_GPIO_ODATA_OD12
  */
/** @defgroup MD_GPIO_ODATA_OD11 OD11
  * @brief  Set OD11 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od11_fun(od11)  (od11<<GPIO_ODATA_OD11_POS)
/**
  * @} MD_GPIO_ODATA_OD11
  */
/** @defgroup MD_GPIO_ODATA_OD10 OD10
  * @brief  Set OD10 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od10_fun(od10)  (od10<<GPIO_ODATA_OD10_POS)
/**
  * @} MD_GPIO_ODATA_OD10
  */
/** @defgroup MD_GPIO_ODATA_OD9 OD9
  * @brief  Set OD9 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od9_fun(od9)  (od9<<GPIO_ODATA_OD9_POS)
/**
  * @} MD_GPIO_ODATA_OD9
  */
/** @defgroup MD_GPIO_ODATA_OD8 OD8
  * @brief  Set OD8 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od8_fun(od8)  (od8<<GPIO_ODATA_OD8_POS)
/**
  * @} MD_GPIO_ODATA_OD8
  */
/** @defgroup MD_GPIO_ODATA_OD7 OD7
  * @brief  Set OD7 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od7_fun(od7)  (od7<<GPIO_ODATA_OD7_POS)
/**
  * @} MD_GPIO_ODATA_OD7
  */
/** @defgroup MD_GPIO_ODATA_OD6 OD6
  * @brief  Set OD6 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od6_fun(od6)  (od6<<GPIO_ODATA_OD6_POS)
/**
  * @} MD_GPIO_ODATA_OD6
  */
/** @defgroup MD_GPIO_ODATA_OD5 OD5
  * @brief  Set OD5 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od5_fun(od5)  (od5<<GPIO_ODATA_OD5_POS)
/**
  * @} MD_GPIO_ODATA_OD5
  */
/** @defgroup MD_GPIO_ODATA_OD4 OD4
  * @brief  Set OD4 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od4_fun(od4)  (od4<<GPIO_ODATA_OD4_POS)
/**
  * @} MD_GPIO_ODATA_OD4
  */
/** @defgroup MD_GPIO_ODATA_OD3 OD3
  * @brief  Set OD3 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od3_fun(od3)  (od3<<GPIO_ODATA_OD3_POS)
/**
  * @} MD_GPIO_ODATA_OD3
  */
/** @defgroup MD_GPIO_ODATA_OD2 OD2
  * @brief  Set OD2 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od2_fun(od2)  (od2<<GPIO_ODATA_OD2_POS)
/**
  * @} MD_GPIO_ODATA_OD2
  */
/** @defgroup MD_GPIO_ODATA_OD1 OD1
  * @brief  Set OD1 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od1_fun(od1)  (od1<<GPIO_ODATA_OD1_POS)
/**
  * @} MD_GPIO_ODATA_OD1
  */
/** @defgroup MD_GPIO_ODATA_OD0 OD0
  * @brief  Set OD0 set/reset bit for md_gpio_set_bsbr() function used
  * @param  od0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_OUTPUT_LOW
  *         @arg @ref MD_GPIO_OUTPUT_HIGH
  * @{
  */
#define md_gpio_set_odata_od0_fun(od0)  (od0<<GPIO_ODATA_OD0_POS)
/**
  * @} MD_GPIO_ODATA_OD0
  */
/**
  * @brief  Set GPIOx Output Data register
  * @param  GPIOx GPIO Port
  * @param  od15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od15_fun(od15)
  * @param  od14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od14_fun(od14)
  * @param  od13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od13_fun(od13)
  * @param  od12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od12_fun(od12)
  * @param  od11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od11_fun(od11)
  * @param  od10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od10_fun(od10)
  * @param  od9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od9_fun(od9)
  * @param  od8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od8_fun(od8)
  * @param  od7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od7_fun(od7)
  * @param  od6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od6_fun(od6)
  * @param  od5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od5_fun(od5)
  * @param  od4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od4_fun(od4)
  * @param  od3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od3_fun(od3)
  * @param  od2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od2_fun(od2)
  * @param  od1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od1_fun(od1)
  * @param  od0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_odata_od0_fun(od0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_odata(GPIO_TypeDef *GPIOx, uint32_t od15,  uint32_t od14,  uint32_t od13,
                                                            uint32_t od12,  uint32_t od11,  uint32_t od10,
                                                            uint32_t od9,   uint32_t od8,   uint32_t od7,
                                                            uint32_t od6,   uint32_t od5,   uint32_t od4,
                                                            uint32_t od3,   uint32_t od2,   uint32_t od1,
                                                            uint32_t od0)
{
  WRITE_REG(GPIOx->ODATA, (od15|od14|od13|od12|od11|od10|od9|od8|od7|od6|od5|od4|od3|od2|od1|od0));
}





/**
  * @brief  Write output data register for the port.
  * @param  GPIOx GPIO Port
  * @param  PortValue Level value for each pin of the port
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_output_port(GPIO_TypeDef *GPIOx, uint32_t PortValue)
{
  WRITE_REG(GPIOx->ODATA, PortValue);
}

/**
  * @brief  Return full output data register value for a dedicated port.
  * @param  GPIOx GPIO Port
  * @retval Output data register value of port
  */
__STATIC_INLINE uint32_t md_gpio_get_output_port(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->ODATA));
}

/**
  * @brief  Set several pins to high level on dedicated gpio port.
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  *         @arg @ref MD_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_high(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BSBR, PinMask);
}

/**
  * @brief  Reset several pins to low level on dedicated gpio port.
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  *         @arg @ref MD_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_pin_low(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BSBR, (PinMask << 16));
}


/** @defgroup MD_GPIO_FIR_FIR15 FIR15
  * @brief  Set FIR15 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir15 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir15_fun(fir15)  (fir15<<GPIO_FIR_FIR15_POS)
/**
  * @} MD_GPIO_FIR_FIR15
  */
/** @defgroup MD_GPIO_FIR_FIR14 FIR14
  * @brief  Set FIR14 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir14 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir14_fun(fir14)  (fir14<<GPIO_FIR_FIR14_POS)
/**
  * @} MD_GPIO_FIR_FIR14
  */
/** @defgroup MD_GPIO_FIR_FIR13 FIR13
  * @brief  Set FIR13 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir13 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir13_fun(fir13)  (fir13<<GPIO_FIR_FIR13_POS)
/**
  * @} MD_GPIO_FIR_FIR13
  */
/** @defgroup MD_GPIO_FIR_FIR12 FIR12
  * @brief  Set FIR12 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir12 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir12_fun(fir12)  (fir12<<GPIO_FIR_FIR12_POS)
/**
  * @} MD_GPIO_FIR_FIR12
  */
/** @defgroup MD_GPIO_FIR_FIR11 FIR11
  * @brief  Set FIR11 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir11 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir11_fun(fir11)  (fir11<<GPIO_FIR_FIR11_POS)
/**
  * @} MD_GPIO_FIR_FIR11
  */
/** @defgroup MD_GPIO_FIR_FIR10 FIR10
  * @brief  Set FIR10 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir10 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir10_fun(fir10)  (fir10<<GPIO_FIR_FIR10_POS)
/**
  * @} MD_GPIO_FIR_FIR10
  */
/** @defgroup MD_GPIO_FIR_FIR9 FIR9
  * @brief  Set FIR9 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir9 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir9_fun(fir9)  (fir9<<GPIO_FIR_FIR9_POS)
/**
  * @} MD_GPIO_FIR_FIR9
  */
/** @defgroup MD_GPIO_FIR_FIR8 FIR8
  * @brief  Set FIR8 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir8 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir8_fun(fir8)  (fir8<<GPIO_FIR_FIR8_POS)
/**
  * @} MD_GPIO_FIR_FIR8
  */
/** @defgroup MD_GPIO_FIR_FIR7 FIR7
  * @brief  Set FIR7 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir7 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir7_fun(fir7)  (fir7<<GPIO_FIR_FIR7_POS)
/**
  * @} MD_GPIO_FIR_FIR7
  */
/** @defgroup MD_GPIO_FIR_FIR6 FIR6
  * @brief  Set FIR6 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir6 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir6_fun(fir6)  (fir6<<GPIO_FIR_FIR6_POS)
/**
  * @} MD_GPIO_FIR_FIR6
  */
/** @defgroup MD_GPIO_FIR_FIR5 FIR5
  * @brief  Set FIR5 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir5 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir5_fun(fir5)  (fir5<<GPIO_FIR_FIR5_POS)
/**
  * @} MD_GPIO_FIR_FIR5
  */
/** @defgroup MD_GPIO_FIR_FIR4 FIR4
  * @brief  Set FIR4 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir4 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir4_fun(fir4)  (fir4<<GPIO_FIR_FIR4_POS)
/**
  * @} MD_GPIO_FIR_FIR4
  */
/** @defgroup MD_GPIO_FIR_FIR3 FIR3
  * @brief  Set FIR3 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir3 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir3_fun(fir3)  (fir3<<GPIO_FIR_FIR3_POS)
/**
  * @} MD_GPIO_FIR_FIR3
  */
/** @defgroup MD_GPIO_FIR_FIR2 FIR2
  * @brief  Set FIR2 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir2 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir2_fun(fir2)  (fir2<<GPIO_FIR_FIR2_POS)
/**
  * @} MD_GPIO_FIR_FIR2
  */
/** @defgroup MD_GPIO_FIR_FIR1 FIR1
  * @brief  Set FIR1 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir1 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir1_fun(fir1)  (fir1<<GPIO_FIR_FIR1_POS)
/**
  * @} MD_GPIO_FIR_FIR1
  */
/** @defgroup MD_GPIO_FIR_FIR0 FIR0
  * @brief  Set FIR0 configure the input signal over thought a glitch filter bit for md_gpio_set_fir() function used
  * @param  fir0 This parameter can be one of the following values:
  *         @arg @ref MD_GPIO_FILTER_BYPASS
  *         @arg @ref MD_GPIO_FILTER_GLITCH
  * @{
  */
#define md_gpio_set_fir_fir0_fun(fir0)  (fir0<<GPIO_FIR_FIR0_POS)
/**
  * @} MD_GPIO_FIR_FIR0
  */
/**
  * @brief  Set GPIOx port Input Filter register (GPIO_FIR)
  * @param  GPIOx GPIO Port
  * @param  fir15 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir15_fun(fir15)
  * @param  fir14 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir14_fun(fir14)
  * @param  fir13 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir13_fun(fir13)
  * @param  fir12 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir12_fun(fir12)
  * @param  fir11 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir11_fun(fir11)
  * @param  fir10 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir10_fun(fir10)
  * @param  fir9 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir9_fun(fir9)
  * @param  fir8 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir8_fun(fir8)
  * @param  fir7 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir7_fun(fir7)
  * @param  fir6 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir6_fun(fir6)
  * @param  fir5 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir5_fun(fir5)
  * @param  fir4 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir4_fun(fir4)
  * @param  fir3 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir3_fun(fir3)
  * @param  fir2 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir2_fun(fir2)
  * @param  fir1 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir1_fun(fir1)
  * @param  fir0 This parameter can be one of the following values:
  *         @arg @ref md_gpio_set_fir_fir0_fun(fir0)
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_fir(GPIO_TypeDef *GPIOx, uint32_t fir15, uint32_t fir14,  uint32_t fir13,
                                                          uint32_t fir12, uint32_t fir11,  uint32_t fir10,
                                                          uint32_t fir9,  uint32_t fir8,   uint32_t fir7,
                                                          uint32_t fir6,  uint32_t fir5,   uint32_t fir4,
                                                          uint32_t fir3,  uint32_t fir2,   uint32_t fir1,
                                                          uint32_t fir0)
{
  WRITE_REG(GPIOx->FIR, (fir15|fir14|fir13|fir12|fir11|fir10|fir9|fir8|fir7|fir6|fir5|fir4|fir3|fir2|fir1|fir0));
}


/**
  * @brief  Write input filter register for the port.
  * @note   These bits are written by software to configure
  *         the input signal over thought a glitch filter.
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  *         @arg @ref MD_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void md_gpio_set_filter(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->FIR, PinMask);
}

/**
  * @brief  Return full input filter data register value for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MD_GPIO_PIN_0
  *         @arg @ref MD_GPIO_PIN_1
  *         @arg @ref MD_GPIO_PIN_2
  *         @arg @ref MD_GPIO_PIN_3
  *         @arg @ref MD_GPIO_PIN_4
  *         @arg @ref MD_GPIO_PIN_5
  *         @arg @ref MD_GPIO_PIN_6
  *         @arg @ref MD_GPIO_PIN_7
  *         @arg @ref MD_GPIO_PIN_8
  *         @arg @ref MD_GPIO_PIN_9
  *         @arg @ref MD_GPIO_PIN_10
  *         @arg @ref MD_GPIO_PIN_11
  *         @arg @ref MD_GPIO_PIN_12
  *         @arg @ref MD_GPIO_PIN_13
  *         @arg @ref MD_GPIO_PIN_14
  *         @arg @ref MD_GPIO_PIN_15
  *         @arg @ref MD_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_gpio_get_filter(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->FIR, PinMask) == (PinMask));
}

/**
  * @} MD_GPIO_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_GPIO_Public_Functions GPIO Public Functions
  * @{
  */

/** @defgroup MD_GPIO_PF_Port_Configuration Port Configuration
  * @{
  */

/**
  * @} MD_GPIO_PF_Port_Configuration
  */

/** @defgroup MD_GPIO_PF_Data_Access Data Access
  * @{
  */

/**
  * @} MD_GPIO_PF_Data_Access
  */


/** @defgroup MD_GPIO_PF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus md_gpio_deinit(GPIO_TypeDef *GPIOx);
ErrorStatus md_gpio_init(GPIO_TypeDef *GPIOx, md_gpio_inittypedef *GPIO_InitStruct);
void        md_gpio_struct_init(md_gpio_inittypedef *GPIO_InitStruct);

/**
  * @} MD_GPIO_PF_Init
  */

/**
  * @} MD_GPIO_Public_Functions
  */

#endif

/**
  * @} GPIO
  */

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
