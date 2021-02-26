/**
  *********************************************************************************
  *
  * @file    ald_gpio.h
  * @brief   Header file of GPIO module driver
  *
  * @version V1.0
  * @date    07 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_GPIO_H__
#define __ALD_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/**
  * @defgroup GPIO_Public_Macros GPIO Public Macros
  * @{
  */
#define GPIO_PIN_0	(1U << 0)
#define GPIO_PIN_1	(1U << 1)
#define GPIO_PIN_2	(1U << 2)
#define GPIO_PIN_3	(1U << 3)
#define GPIO_PIN_4	(1U << 4)
#define GPIO_PIN_5	(1U << 5)
#define GPIO_PIN_6	(1U << 6)
#define GPIO_PIN_7	(1U << 7)
#define GPIO_PIN_8	(1U << 8)
#define GPIO_PIN_9	(1U << 9)
#define GPIO_PIN_10	(1U << 10)
#define GPIO_PIN_11	(1U << 11)
#define GPIO_PIN_12	(1U << 12)
#define GPIO_PIN_13	(1U << 13)
#define GPIO_PIN_14	(1U << 14)
#define GPIO_PIN_15	(1U << 15)
#define GPIO_PIN_ALL	(0xFFFFU)
/**
  * @}
  */

/**
  * @defgroup GPIO_Public_Types GPIO Public Types
  * @{
  */

/**
  * @brief GPIO mode
  */
typedef enum {
	GPIO_MODE_CLOSE  = 0x0U,	/**< Digital close  Analog open */
	GPIO_MODE_INPUT  = 0x1U,	/**< Input */
	GPIO_MODE_OUTPUT = 0x2U,	/**< Output */
} gpio_mode_t;

/**
  * @brief GPIO open-drain or push-pull
  */
typedef enum {
	GPIO_PUSH_PULL   = 0x0U,	/**< Push-Pull */
	GPIO_OPEN_DRAIN  = 0x2U,	/**< Open-Drain. Can't output high level */
	GPIO_OPEN_SOURCE = 0x3U,	/**< Open-Source. Can't output low level */
} gpio_odos_t;

/**
  * @brief GPIO push-up or push-down
  */
typedef enum {
	GPIO_FLOATING     = 0x0U,	/**< Floating */
	GPIO_PUSH_UP      = 0x1U,	/**< Push-Up */
	GPIO_PUSH_DOWN    = 0x2U,	/**< Push-Down */
	GPIO_PUSH_UP_DOWN = 0x3U,	/**< Push-Up and Push-Down */
} gpio_push_t;

/**
  * @brief GPIO output drive
  */
typedef enum {
	GPIO_OUT_DRIVE_NORMAL = 0x0U,	/**< Normal current flow */
	GPIO_OUT_DRIVE_STRONG = 0x1U,	/**< Strong current flow */
} gpio_out_drive_t;

/**
  * @brief GPIO filter
  */
typedef enum {
	GPIO_FILTER_DISABLE = 0x0U,	/**< Disable filter */
	GPIO_FILTER_ENABLE  = 0x1U,	/**< Enable filter */
} gpio_filter_t;

/**
  * @brief GPIO type
  */
typedef enum {
	GPIO_TYPE_CMOS = 0x0U,	/**< CMOS Type */
	GPIO_TYPE_TTL  = 0x1U,	/**< TTL Type */
} gpio_type_t;

/**
  * @brief GPIO functions
  */
typedef enum {
	GPIO_FUNC_0 = 0U,	/**< function #0 */
	GPIO_FUNC_1 = 1U,	/**< function #1 */
	GPIO_FUNC_2 = 2U,	/**< function #2 */
	GPIO_FUNC_3 = 3U,	/**< function #3 */
	GPIO_FUNC_4 = 4U,	/**< function #4 */
	GPIO_FUNC_5 = 5U,	/**< function #5 */
	GPIO_FUNC_6 = 6U,	/**< function #6 */
	GPIO_FUNC_7 = 7U,	/**< function #7 */
} gpio_func_t;


/**
  * @brief GPIO Init Structure definition
  */
typedef struct {
	gpio_mode_t mode;	/**< Specifies the operating mode for the selected pins.
				     This parameter can be any value of @ref gpio_mode_t */
	gpio_odos_t odos;	/**< Specifies the Open-Drain or Push-Pull for the selected pins.
				     This parameter can be a value of @ref gpio_odos_t */
	gpio_push_t pupd;	/**< Specifies the Pull-up or Pull-Down for the selected pins.
				     This parameter can be a value of @ref gpio_push_t */
	gpio_out_drive_t odrv;	/**< Specifies the output driver for the selected pins.
				     This parameter can be a value of @ref gpio_out_drive_t */
	gpio_filter_t flt;	/**< Specifies the input filter for the selected pins.
				     This parameter can be a value of @ref gpio_filter_t */
	gpio_type_t type;	/**< Specifies the type for the selected pins.
				     This parameter can be a value of @ref gpio_type_t */
	gpio_func_t func;	/**< Specifies the function for the selected pins.
				     This parameter can be a value of @ref gpio_func_t */
} gpio_init_t;

/**
  * @brief EXTI trigger style
  */
typedef enum {
	EXTI_TRIGGER_RISING_EDGE   = 0U,	/**< Rising edge trigger */
	EXTI_TRIGGER_TRAILING_EDGE = 1U,	/**< Trailing edge trigger */
	EXTI_TRIGGER_BOTH_EDGE     = 2U,	/**< Rising and trailing edge trigger */
} exti_trigger_style_t;

/**
  * @brief EXTI filter clock select
  */
typedef enum {
	EXTI_FILTER_CLOCK_10K = 0U,	/**< cks = 10KHz */
	EXTI_FILTER_CLOCK_32K = 1U,	/**< cks = 32KHz */
} exti_filter_clock_t;

/**
  * @brief EXTI Init Structure definition
  */
typedef struct {
	type_func_t filter;		/**< Enable filter. */
	exti_filter_clock_t cks;	/**< Filter clock select. */
	uint8_t filter_time;		/**< Filter duration */
} exti_init_t;
/**
  * @}
  */

/**
  * @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define PIN_MASK	0xFFFFU
#define UNLOCK_KEY	0x55AAU

#define IS_GPIO_PIN(x)	((((x) & (uint16_t)0x00) == 0) && ((x) != (uint16_t)0x0))
#define IS_GPIO_PORT(GPIOx)	((GPIOx == GPIOA) || \
				 (GPIOx == GPIOB) || \
				 (GPIOx == GPIOC) || \
				 (GPIOx == GPIOD) || \
				 (GPIOx == GPIOE) || \
				 (GPIOx == GPIOF) || \
				 (GPIOx == GPIOG) || \
				 (GPIOx == GPIOH))
#define IS_GPIO_MODE(x)		(((x) == GPIO_MODE_CLOSE) || \
                                 ((x) == GPIO_MODE_INPUT) || \
                                 ((x) == GPIO_MODE_OUTPUT))
#define IS_GPIO_ODOS(x)		(((x) == GPIO_PUSH_PULL)  || \
                                 ((x) == GPIO_OPEN_DRAIN) || \
                                 ((x) == GPIO_OPEN_SOURCE))
#define IS_GPIO_PUPD(x)		(((x) == GPIO_FLOATING)  || \
                                 ((x) == GPIO_PUSH_UP)   || \
                                 ((x) == GPIO_PUSH_DOWN) || \
                                 ((x) == GPIO_PUSH_UP_DOWN))
#define IS_GPIO_ODRV(x)		(((x) == GPIO_OUT_DRIVE_NORMAL) || \
                                 ((x) == GPIO_OUT_DRIVE_STRONG))
#define IS_GPIO_FLT(x)		(((x) == GPIO_FILTER_DISABLE) || \
                                 ((x) == GPIO_FILTER_ENABLE))
#define IS_GPIO_TYPE(x)		(((x) == GPIO_TYPE_TTL) || \
                                 ((x) == GPIO_TYPE_CMOS))
#define IS_TRIGGER_STYLE(x)	(((x) == EXTI_TRIGGER_RISING_EDGE)   || \
                                 ((x) == EXTI_TRIGGER_TRAILING_EDGE) || \
                                 ((x) == EXTI_TRIGGER_BOTH_EDGE))
#define IS_EXTI_FLTCKS_TYPE(x)	(((x) == EXTI_FILTER_CLOCK_10K) || \
                                 ((x) == EXTI_FILTER_CLOCK_32K))
#define IS_GPIO_FUNC(x)		((x) <= 7)
/**
  * @}
  */

/** @addtogroup GPIO_Public_Functions
  * @{
  */

/** @addtogroup GPIO_Public_Functions_Group1
  * @{
  */
void ald_gpio_init(GPIO_TypeDef *GPIOx, uint16_t pin, gpio_init_t *init);
void ald_gpio_init_default(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_func_default(GPIO_TypeDef *GPIOx);
void ald_gpio_exti_init(GPIO_TypeDef *GPIOx, uint16_t pin, exti_init_t *init);
/**
  * @}
  */

/** @addtogroup GPIO_Public_Functions_Group2
  * @{
  */
uint8_t ald_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t val);
void ald_gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_toggle_dir(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_lock_pin(GPIO_TypeDef *GPIOx, uint16_t pin);
uint16_t ald_gpio_read_port(GPIO_TypeDef *GPIOx);
void ald_gpio_write_port(GPIO_TypeDef *GPIOx, uint16_t val);
/**
  * @}
  */

/** @addtogroup GPIO_Public_Functions_Group3
  * @{
  */
void ald_gpio_exti_interrupt_config(uint16_t pin, exti_trigger_style_t style, type_func_t status);
flag_status_t ald_gpio_exti_get_flag_status(uint16_t pin);
void ald_gpio_exti_clear_flag_status(uint16_t pin);
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

#endif /* __ALD_GPIO_H__ */
