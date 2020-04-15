/**
  ******************************************************************************
  * @file    md_gpio.c
  * @brief   ES32F0271 GPIO Source File.
  *
  * @version V1.00.01
  * @data    day/mon/year
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "md_rcu.h"
#include "md_gpio.h"

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
/** @defgroup MD_GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_MD_GPIO_ALL_INSTANCE(__INSTANCE__) ((__INSTANCE__ == GPIOA)   \
    || (__INSTANCE__ == GPIOB))  \
|| (__INSTANCE__ == GPIOC))  \
|| (__INSTANCE__ == GPIOD))

#define IS_MD_GPIO_PIN(__VALUE__) (((__VALUE__) == MD_GPIO_PIN_0)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_1)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_2)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_3)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_4)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_5)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_6)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_7)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_8)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_9)    \
                                   || ((__VALUE__) == MD_GPIO_PIN_10)   \
                                   || ((__VALUE__) == MD_GPIO_PIN_11)   \
                                   || ((__VALUE__) == MD_GPIO_PIN_12)   \
                                   || ((__VALUE__) == MD_GPIO_PIN_13)   \
                                   || ((__VALUE__) == MD_GPIO_PIN_14)   \
                                   || ((__VALUE__) == MD_GPIO_PIN_15))  \

#define IS_MD_GPIO_MODE(__VALUE__) (((__VALUE__) == MD_GPIO_MODE_INPUT)    \
                                    || ((__VALUE__) == MD_GPIO_MODE_OUTPUT)   \
                                    || ((__VALUE__) == MD_GPIO_MODE_FUNCTION) \
                                    || ((__VALUE__) == MD_GPIO_MODE_ANALOG))

#define IS_MD_GPIO_OUTPUT_TYPE(__VALUE__) (((__VALUE__) == MD_GPIO_OUTPUT_PUSHPULL)  \
    || ((__VALUE__) == MD_GPIO_OUTPUT_OPENDRAIN))

#define IS_MD_GPIO_PULL(__VALUE__) (((__VALUE__) == MD_GPIO_PULL_FLOATING)   \
                                    || ((__VALUE__) == MD_GPIO_PULL_UP)         \
                                    || ((__VALUE__) == MD_GPIO_PULL_DOWN)

#define IS_MD_GPIO_DS(__VALUE__) (((__VALUE__) == MD_GPIO_DS_8mA) \
                                  || ((__VALUE__) == MD_GPIO_DS_16mA))

#define IS_MD_GPIO_FUNCTION(__VALUE__) (((__VALUE__) == MD_GPIO_AF0) \
                                        || ((__VALUE__) == MD_GPIO_AF1) \
                                        || ((__VALUE__) == MD_GPIO_AF2) \
                                        || ((__VALUE__) == MD_GPIO_AF3) \
                                        || ((__VALUE__) == MD_GPIO_AF4) \
                                        || ((__VALUE__) == MD_GPIO_AF5) \
                                        || ((__VALUE__) == MD_GPIO_AF6) \
                                        || ((__VALUE__) == MD_GPIO_AF7))

#define IS_MD_GPIO_IST(__VALUE__) (((__VALUE__) == MD_GPIO_IST_TTL) \
                                   || ((__VALUE__) == MD_GPIO_IST_CMOS))

/**
  * @} MD_GPIO_Private_Macros
  */

/* Private function prototypes ------------------------------------------------*/

/* Public functions -----------------------------------------------------------*/
/** @addtogroup MD_GPIO_Public_Functions GPIO Public Functions
  * @{
  */

/** @addtogroup MD_GPIO_PF_Init GPIO Public Init Functions
  * @{
  */

/**
  * @brief  De-initialize the GPIO registers to their default reset values.
  * @param  GPIOx GPIO Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: GPIO registers are de-initialized
  *          - ERROR: GPIO registers are not de-initialized
  */
ErrorStatus md_gpio_deinit(GPIO_TypeDef *GPIOx)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_MD_GPIO_ALL_INSTANCE(GPIOx));

  /* Force reset of GPIO clock */
  if (GPIOx == GPIOA)
  {
    md_rcu_enable_ahbrst_gpaen(RCU);
  }
  else if (GPIOx == GPIOB)
  {
    md_rcu_enable_ahbrst_gpben(RCU);
  }
  else if (GPIOx == GPIOC)
  {
    md_rcu_enable_ahbrst_gpcen(RCU);
  }
  else  /* if(GPIOx==GPIOD) */
  {
    md_rcu_enable_ahbrst_gpden(RCU);
  }

  status = SUCCESS;

  return status;
}

/**
  * @brief  Initialize the GPIO registers according to the specified parameters in GPIO_InitStruct.
  * @note   As some bits in GPIO configuration registers can only be written when the GPIO is disabled (GPIO_CR1_SPE bit =0),
  *         GPIO IP should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @param  GPIOx GPIO Instance
  * @param  GPIO_InitStruct pointer to a @ref md_gpio_inittypedef structure
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
ErrorStatus md_gpio_init(GPIO_TypeDef *GPIOx, md_gpio_inittypedef *GPIO_InitStruct)
{
  ErrorStatus status = ERROR;

  /* Check the GPIO Instance GPIOx*/
  assert_param(IS_MD_GPIO_ALL_INSTANCE(GPIOx));

  /* Check the GPIO parameters from GPIO_InitStruct*/
  assert_param(IS_MD_GPIO_PIN(GPIO_InitStruct->Pin));
  assert_param(IS_MD_GPIO_MODE(GPIO_InitStruct->Mode));
  assert_param(IS_MD_GPIO_OUTPUT_TYPE(GPIO_InitStruct->OutputType));
  assert_param(IS_MD_GPIO_PULL(GPIO_InitStruct->Pull));
  assert_param(IS_MD_GPIO_DS(GPIO_InitStruct->OutDrive));
  assert_param(IS_MD_GPIO_FUNCTION(GPIO_InitStruct->Function));

  if (POSITION_VAL(GPIO_InitStruct->Pin) <= 7)
  {
    md_gpio_set_function0_7(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->Function);
  }
  else
  {
    md_gpio_set_function8_15(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->Function);
  }

  md_gpio_set_mode(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->Mode);
  md_gpio_set_output_type(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->OutputType);
  md_gpio_set_pull(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->Pull);
  md_gpio_set_ds(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->OutDrive);

  status = SUCCESS;

  return status;
}

/**
  * @brief  Set each @ref md_gpio_inittypedef field to default value.
  * @param  GPIO_InitStruct pointer to a @ref md_gpio_inittypedef structure
  *         whose fields will be set to default values.
  * @retval None
  */
void md_gpio_struct_init(md_gpio_inittypedef *GPIO_InitStruct)
{
  /* Set GPIO_InitStruct fields to default values */
  GPIO_InitStruct->Function    = MD_GPIO_AF0;
  GPIO_InitStruct->Mode        = MD_GPIO_MODE_ANALOG;
  GPIO_InitStruct->OutDrive    = MD_GPIO_DS_8mA;
  GPIO_InitStruct->OutputType  = MD_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct->Pull        = MD_GPIO_PULL_FLOATING;
  GPIO_InitStruct->Pin         = MD_GPIO_PIN_ALL;
}

/**
  * @} MD_GPIO_PF_Init
  */

/**
  * @} MD_GPIO_Public_Functions
  */

/**
  * @} GPIO
  */
#endif

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
