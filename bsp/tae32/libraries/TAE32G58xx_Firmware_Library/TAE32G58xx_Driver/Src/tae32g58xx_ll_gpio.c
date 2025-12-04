/**
  ******************************************************************************
  * @file    tae32g58xx_ll_gpio.c
  * @author  MCD Application Team
  * @brief   GPIO LL module driver
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

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"


#define DBG_TAG             "GPIO LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup GPIO_LL GPIO LL
  * @brief    GPIO LL module driver
  * @{
  */

#ifdef LL_GPIO_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Functions GPIO LL Exported Functions
  * @brief    GPIO LL Exported Functions
  * @{
  */

/** @defgroup GPIO_LL_Exported_Functions_Group1 GPIO Init and DeInit Functions
  * @brief    GPIO Init and DeInit Functions
  * @{
  */

/**
  * @brief  GPIO LL Init
  * @param  Instance Specifies GPIO peripheral
  * @param  gpio_init GPIO init pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_GPIO_Init(GPIO_TypeDef *Instance, GPIO_InitTypeDef *gpio_init)
{
    uint32_t pin;
    uint8_t  pin_num;

    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));
    assert_param(gpio_init != NULL);
    assert_param(__LL_GPIO_IsPinValid(gpio_init->Pin));

    if (!IS_GPIO_ALL_INSTANCE(Instance) || gpio_init == NULL || !__LL_GPIO_IsPinValid(gpio_init->Pin)) {
        return LL_INVALID;
    }

    for (pin_num = 0; pin_num < (uint8_t)GPIO_PIN_NUMS; pin_num++) {
        pin = gpio_init->Pin & BIT(pin_num);

        if (!pin) {
            continue;
        }

        switch (gpio_init->Alternate) {
            case GPIO_AF0_INPUT:
                //GPIO Pinmux Function Config
                __LL_GPIO_PinmuxFunc_Set(Instance, pin_num, gpio_init->Alternate);

                if (gpio_init->IntMode != GPIO_INT_MODE_CLOSE) {
                    //GPIO Interrupt Mode Config
                    __LL_GPIO_IntMode_Set(Instance, pin_num, gpio_init->IntMode);

                    //GPIO Interrupt Pending Clear before Interrupt Enable
                    __LL_GPIO_IntPending_Clr(Instance, pin);

                    //GPIO Interrupt Enable
                    __LL_GPIO_INT_En(Instance, pin);
                }

                break;

            case GPIO_AF1_OUTPUT:
            case GPIO_AF2:
            case GPIO_AF3:
            case GPIO_AF4:
            case GPIO_AF5:
            case GPIO_AF6:
            case GPIO_AF7:
            case GPIO_AF8:
            case GPIO_AF9:
            case GPIO_AF10:
            case GPIO_AF11:
            case GPIO_AF12:
            case GPIO_AF13:
            case GPIO_AF14:
            case GPIO_AF15:
                //GPIO Pinmux Function Config
                __LL_GPIO_PinmuxFunc_Set(Instance, pin_num, gpio_init->Alternate);

                //GPIO Output Type Config
                LL_FUNC_ALTER(gpio_init->OType == GPIO_OTYPE_PP, __LL_GPIO_OutputMode_PushPull_Set(Instance, pin),
                              __LL_GPIO_OutputMode_OpenDrain_Set(Instance, pin));

                //GPIO Output Speed Config
                LL_FUNC_ALTER(gpio_init->Speed == GPIO_SPEED_FREQ_LOW, __LL_GPIO_OutputSlew_Normal_Set(Instance, pin),
                              __LL_GPIO_OutputSlew_Enhance_Set(Instance, pin));
                break;

            default:
                LOG_E("GPIO-[0x%08" PRIx32 "] Pin-[%d] alternate function [%d] config Error!!!\n", (uint32_t)Instance, pin_num, gpio_init->Alternate);
                return LL_ERROR;
        }

        //GPIO Pull Config
        __LL_GPIO_PullMode_Set(Instance, pin_num, gpio_init->Pull);

        //GPIO Drive Capability Config
        if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_GPIO))) {
            __LL_GPIO_DrvCapSpd_Set(Instance, gpio_init->Pin, gpio_init->DrvCap);
        }
    }

    return LL_OK;
}

/**
  * @brief  GPIO LL DeInit
  * @param  Instance Specifies GPIO peripheral
  * @param  pins GPIO pin @ref GPIO_Pin_Definition
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_GPIO_DeInit(GPIO_TypeDef *Instance, uint32_t pins)
{
    uint32_t pin;
    uint8_t  pin_num;

    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));
    assert_param(__LL_GPIO_IsPinValid(pins));

    if (!IS_GPIO_ALL_INSTANCE(Instance) || !__LL_GPIO_IsPinValid(pins)) {
        return LL_INVALID;
    }

    for (pin_num = 0; pin_num < GPIO_PIN_NUMS; pin_num++) {
        pin = pins & BIT(pin_num);

        if (!pin) {
            continue;
        }

        //GPIO Pinmux Function Config to default -> Analog
        __LL_GPIO_PinmuxFunc_Set(Instance, pin_num, GPIO_AF_DEFAULT);

        //GPIO Output Speed Config to default -> Normal Low
        __LL_GPIO_OutputSlew_Normal_Set(Instance, pin);

        //GPIO Output Type Config to default -> PushPull
        __LL_GPIO_OutputMode_PushPull_Set(Instance, pin);

        //GPIO Pull Disable
        __LL_GPIO_PullMode_Set(Instance, pin_num, GPIO_NOPULL);

        //GPIO Interrupt Disable
        __LL_GPIO_INT_Dis(Instance, pin);

        //GPIO Interrupt Mode Config to default -> Close
        __LL_GPIO_IntMode_Set(Instance, pin_num, GPIO_INT_MODE_CLOSE);

        //GPIO Interrupt Pending Clear
        __LL_GPIO_IntPending_Clr(Instance, pin);

        //GPIO Output Value Config to default
        __LL_GPIO_PinOutput_Reset(Instance, pin);
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup GPIO_LL_Exported_Functions_Group2 GPIO IO Operation Functions
  * @brief    GPIO IO Operation Functions
  * @{
  */

/**
  * @brief  GPIO config the alternate function on runtime
  * @param  Instance Specifies GPIO peripheral
  * @param  pins GPIO pin @ref GPIO_Pin_Definition
  * @param  alternate GPIO alternate function
  * @return None
  */
void LL_GPIO_AF_Config(GPIO_TypeDef *Instance, uint32_t pins, GPIO_AFETypeDef alternate)
{
    uint32_t pin;
    uint8_t  pin_num;

    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));
    assert_param(__LL_GPIO_IsPinValid(pins));

    if (!IS_GPIO_ALL_INSTANCE(Instance) || !__LL_GPIO_IsPinValid(pins)) {
        return;
    }

    for (pin_num = 0; pin_num < GPIO_PIN_NUMS; pin_num++) {
        pin = pins & BIT(pin_num);

        if (!pin) {
            continue;
        }

        //GPIO Pinmux Function Config
        __LL_GPIO_PinmuxFunc_Set(Instance, pin_num, alternate);
    }
}

/**
  * @brief  GPIO Read the specified input port pin
  * @param  Instance Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_Pin_Definition
  *         This parameter can be GPIO_PIN_x where x can be (0..15)
  * @return The input port pin value
  */
GPIO_PinStateETypeDef LL_GPIO_ReadPin(GPIO_TypeDef *Instance, uint32_t pin)
{
    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));
    assert_param(__LL_GPIO_IsPinValid(pin));

    if (!IS_GPIO_ALL_INSTANCE(Instance) || !__LL_GPIO_IsPinValid(pin)) {
        return GPIO_PIN_RESET;
    }

    LL_FUNC_ALTER(__LL_GPIO_InputDat_Get(Instance, pin), return GPIO_PIN_SET, return GPIO_PIN_RESET);
}

/**
  * @brief  GPIO Set or clear the selected pin port bit
  * @param  Instance Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_Pin_Definition
  *         This parameter can be GPIO_PIN_x where x can be (0..15)
  * @param  pin_state specifies the value to be written to the selected pin
  *         This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @return None
  */
void LL_GPIO_WritePin(GPIO_TypeDef *Instance, uint32_t pin, GPIO_PinStateETypeDef pin_state)
{
    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));
    assert_param(__LL_GPIO_IsPinValid(pin));

    if (!IS_GPIO_ALL_INSTANCE(Instance) || !__LL_GPIO_IsPinValid(pin)) {
        return;
    }

    LL_FUNC_ALTER(pin_state == GPIO_PIN_SET, __LL_GPIO_PinOutput_Set(Instance, pin), __LL_GPIO_PinOutput_Reset(Instance, pin));
}

/**
  * @brief  GPIO toggle the specified pin
  * @param  Instance Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_Pin_Definition
  *         This parameter can be GPIO_PIN_x where x can be (0..15)
  * @return None
  */
void LL_GPIO_TogglePin(GPIO_TypeDef *Instance, uint32_t pin)
{
    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));
    assert_param(__LL_GPIO_IsPinValid(pin));

    if (!IS_GPIO_ALL_INSTANCE(Instance) || !__LL_GPIO_IsPinValid(pin)) {
        return;
    }

    LL_FUNC_ALTER(__LL_GPIO_OutputDat_Get(Instance, pin), __LL_GPIO_PinOutput_Reset(Instance, pin),
                  __LL_GPIO_PinOutput_Set(Instance, pin));
}

/**
  * @brief  GPIO Read data from the specified port
  * @param  Instance Specifies GPIO peripheral
  * @return GPIO port data
  */
uint32_t LL_GPIO_ReadData(GPIO_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));

    if (!IS_GPIO_ALL_INSTANCE(Instance)) {
        return 0;
    }

    return __LL_GPIO_InputDat_Get(Instance, GPIO_PIN_All);
}

/**
  * @brief  GPIO Write data to the specified port
  * @param  Instance Specifies GPIO peripheral
  * @param  dat Port data to write
  * @return None
  */
void LL_GPIO_WriteData(GPIO_TypeDef *Instance, uint16_t dat)
{
    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));

    if (!IS_GPIO_ALL_INSTANCE(Instance)) {
        return;
    }

    __LL_GPIO_OutputDat_Set(Instance, GPIO_PIN_All, dat);
}

/**
  * @}
  */


/** @defgroup GPIO_LL_Exported_Functions_Interrupt GPIO Interrupt Handler and Callback
  * @brief    GPIO Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  GPIO IRQ Handler
  * @param  Instance Specifies GPIO peripheral
  * @return None
  */
void LL_GPIO_IRQHandler(GPIO_TypeDef *Instance)
{
    uint8_t  pin_num;
    uint32_t pin, pins_int_en, pins_int_pending;

    //Assert param
    assert_param(IS_GPIO_ALL_INSTANCE(Instance));

    if (!IS_GPIO_ALL_INSTANCE(Instance)) {
        return;
    }

    //All Pin Interrupt Enable and Pending Status Get
    pins_int_en = __LL_GPIO_IsIntEn(Instance, GPIO_PIN_All);
    pins_int_pending = __LL_GPIO_IntPending_Get(Instance, GPIO_PIN_All);

    //Interrupt Handler loop
    for (pin_num = 0; pin_num < GPIO_PIN_NUMS; pin_num++) {
        pin = BIT(pin_num);

        //Pin Interrupt Enable and Pending
        if ((pins_int_en & pin) && (pins_int_pending & pin)) {
            //Pin Interrupt Pending Clear
            __LL_GPIO_IntPending_Clr(Instance, pin);

            LL_GPIO_ExtTrigCallback(Instance, pin);
        }
    }
}

/**
  * @brief  GPIO External Trigger callback
  * @param  Instance Specifies GPIO peripheral
  * @param  pin GPIO pin @ref GPIO_Pin_Definition
  * @return None
  */
__WEAK void LL_GPIO_ExtTrigCallback(GPIO_TypeDef *Instance, uint32_t pin)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    LL_UNUSED(pin);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_GPIO_ExtTrigCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif /* LL_GPIO_MODULE_ENABLE */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

