/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_gpio.c
  * @author  FMSH Application Team
  * @brief   Src file of GPIO FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

#ifdef FL_GPIO_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup GPIO_FL_Private_Macros
  * @{
  */

#define         IS_GPIO_ALL_INSTANCE(INSTANCE)             (((INSTANCE) == GPIOA)||\
                                                            ((INSTANCE) == GPIOB)||\
                                                            ((INSTANCE) == GPIOC)||\
                                                            ((INSTANCE) == GPIOD))

#define         IS_FL_GPIO_PIN(__VALUE__)                  ((((uint32_t)0x00000000U) < (__VALUE__)) &&\
                                                            ((__VALUE__) <= (FL_GPIO_PIN_ALL)))

#define         IS_FL_GPIO_MODE(__VALUE__)                  (((__VALUE__) == FL_GPIO_MODE_ANALOG)||\
                                                             ((__VALUE__) == FL_GPIO_MODE_INPUT)||\
                                                             ((__VALUE__) == FL_GPIO_MODE_OUTPUT)||\
                                                             ((__VALUE__) == FL_GPIO_MODE_DIGITAL))

#define         IS_FL_GPIO_OPENDRAIN(__VALUE__)             (((__VALUE__) == FL_GPIO_OUTPUT_OPENDRAIN)||\
                                                             ((__VALUE__) == FL_GPIO_OUTPUT_PUSHPULL))

#define         IS_FL_GPIO_PULL_UP(__VALUE__)               (((__VALUE__) == FL_DISABLE)||\
                                                             ((__VALUE__) == FL_ENABLE))


#define         IS_FL_GPIO_WKUP_ENTRY(__VALUE__)            (((__VALUE__) == FL_GPIO_WAKEUP_INT_ENTRY_NMI)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_INT_ENTRY_38))

#define         IS_FL_GPIO_WKUP_EDGE(__VALUE__)             (((__VALUE__) == FL_GPIO_WAKEUP_TRIGGER_RISING)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_TRIGGER_FALLING))


#define         IS_FL_GPIO_WKUP_NUM(__VALUE__)              (((__VALUE__) == FL_GPIO_WAKEUP_0)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_1)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_2)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_3)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_4)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_5)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_6)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_7))
/**
  * @}
  */

/** @addtogroup GPIO_FL_EF_Init
  * @{
  */

/**
  * @brief  复位GPIO外设
  * @param  GPIOx 外设入口地址
  * @param  pin 引脚
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_GPIO_DeInit(GPIO_Type *GPIOx, uint32_t pin)
{
    uint32_t pinPos     = 0x00000000U;
    uint32_t currentPin = 0x00000000U;
    /* 入口参数检查 */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_FL_GPIO_PIN(pin));
    /* 恢复寄存器值为默认值 */
    while(((pin) >> pinPos) != 0x00000000U)
    {
        /* 获取当前遍历到的Pin脚 */
        currentPin = (pin) & (0x00000001U << pinPos);
        if(currentPin)
        {
            FL_GPIO_SetPinMode(GPIOx, currentPin, FL_GPIO_MODE_INPUT);
            FL_GPIO_DisablePinInput(GPIOx, currentPin);
            FL_GPIO_DisablePinOpenDrain(GPIOx, currentPin);
            FL_GPIO_DisablePinPullup(GPIOx, currentPin);
            FL_GPIO_DisablePinAnalogSwitch(GPIOx, currentPin);
            FL_GPIO_DisablePinRemap(GPIOx, currentPin);
        }
        pinPos++;
    }
    return FL_PASS;
}

/**
  * @brief  根据 GPIO_InitStruct 的配置信息初始化对应外设.
  * @param  GPIOx GPIO Port
  * @param  GPIO_InitStruct 指向一个 @ref FL_GPIO_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @retval 错误状态，可能值：
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_GPIO_Init(GPIO_Type *GPIOx, FL_GPIO_InitTypeDef *initStruct)
{
    uint32_t pinPos     = 0x00000000U;
    uint32_t currentPin = 0x00000000U;
    /* 入口参数检查 */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_FL_GPIO_PIN(initStruct->pin));
    assert_param(IS_FL_GPIO_MODE(initStruct->mode));
    assert_param(IS_FL_GPIO_OPENDRAIN(initStruct->outputType));
    assert_param(IS_FL_GPIO_PULL_UP(initStruct->pull));
    /* 使能时钟总线 */
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_PAD);
    /* 这里考虑到PIN有可能不止一个因此需要遍历 */
    while(((initStruct->pin) >> pinPos) != 0x00000000U)
    {
        /* 获取当前遍历到的Pin脚 */
        currentPin = (initStruct->pin) & (0x00000001U << pinPos);
        if(currentPin)
        {
            /* Pin脚模拟模式设置 */
            if(initStruct->mode == FL_GPIO_MODE_ANALOG)
            {
                FL_GPIO_DisablePinInput(GPIOx, currentPin);
                FL_GPIO_DisablePinPullup(GPIOx, currentPin);
                FL_GPIO_DisablePinOpenDrain(GPIOx, currentPin);
                FL_GPIO_EnablePinAnalogSwitch(GPIOx, currentPin);
            }
            else
            {
                FL_GPIO_DisablePinAnalogSwitch(GPIOx, currentPin);
                /* Pin脚输入使能控制 */
                if(initStruct->mode == FL_GPIO_MODE_INPUT)
                {
                    FL_GPIO_EnablePinInput(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinInput(GPIOx, currentPin);
                }
                /* Pin脚输出模式设置 */
                if(initStruct->outputType == FL_GPIO_OUTPUT_PUSHPULL)
                {
                    FL_GPIO_DisablePinOpenDrain(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_EnablePinOpenDrain(GPIOx, currentPin);
                }
                /* Pin脚上拉模式设置 */
                if(initStruct->pull)
                {
                    FL_GPIO_EnablePinPullup(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinPullup(GPIOx, currentPin);
                }
            }
            /* 数字模式复用功能选择 */
            if(initStruct->mode == FL_GPIO_MODE_DIGITAL)
            {
                /*重定向*/
                if(initStruct->remapPin == FL_ENABLE)
                {
                    FL_GPIO_EnablePinRemap(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinRemap(GPIOx, currentPin);
                }
            }
            /* Pin脚工作模式设置 */
            FL_GPIO_SetPinMode(GPIOx, currentPin, initStruct->mode);
        }
        pinPos++;
    }
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_GPIO_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_GPIO_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_GPIO_StructInit(FL_GPIO_InitTypeDef *initStruct)
{
    /* 复位配置信息 */
    initStruct->pin        = FL_GPIO_PIN_ALL;
    initStruct->mode       = FL_GPIO_MODE_INPUT;
    initStruct->outputType = FL_GPIO_OUTPUT_OPENDRAIN;
    initStruct->pull       = FL_DISABLE;
    initStruct->remapPin   = FL_DISABLE;
}

/**
  * @brief  根据 FL_WKUP_InitTypeDef 配置GPIO唤醒对应外设
  * @param  initStruct 指向一个 @ref FL_WKUP_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @param  wakeup 唤醒入口
  *         FL_GPIO_WAKEUP_0
  *         FL_GPIO_WAKEUP_1
  *         FL_GPIO_WAKEUP_2
  *         FL_GPIO_WAKEUP_3
  *         FL_GPIO_WAKEUP_4
  *         FL_GPIO_WAKEUP_5
  *         FL_GPIO_WAKEUP_6
  *         FL_GPIO_WAKEUP_7
  * @retval 错误状态，可能值：
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_WKUP_Init(FL_WKUP_InitTypeDef *initStruct, uint32_t wakeup)
{
    /* 入口参数检查 */
    assert_param(IS_FL_GPIO_WKUP_NUM(wakeup));
    assert_param(IS_FL_GPIO_WKUP_EDGE(initStruct->polarity));
    FL_GPIO_EnableWakeup(GPIO, wakeup);
    FL_GPIO_SetWakeupEdge(GPIO, wakeup, initStruct->polarity);
    return FL_PASS;
}

/**
  * @brief  去初始化Wakeup配置
  * @param  Wkupx 唤醒入口
  *         FL_GPIO_WKUP_0
  *         FL_GPIO_WKUP_1
  *         FL_GPIO_WKUP_2
  *         FL_GPIO_WKUP_3
  *         FL_GPIO_WKUP_4
  *         FL_GPIO_WKUP_5
  *         FL_GPIO_WKUP_6
  *         FL_GPIO_WKUP_7
  * @retval 错误状态，可能值：
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_WKUP_DeInit(uint32_t wkupx)
{
    /* 入口参数检查 */
    assert_param(IS_FL_GPIO_WKUP_NUM(wkupx));
    FL_GPIO_EnableWakeup(GPIO, wkupx);
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_WKUP_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct_Wakeup 指向需要将值设置为默认配置的结构体 @ref FL_WKUP_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_WKUP_StructInit(FL_WKUP_InitTypeDef *initStruct_Wakeup)
{
    /* 复位配置信息 */
    initStruct_Wakeup->polarity   =   FL_GPIO_WAKEUP_TRIGGER_FALLING;
}

/**
  *@}
  */

/** @addtogroup RNG_FL_EF_Operation
  * @{
  */

/**
  * @brief  设置所有GPIO为输入模式、输入使能关闭（高阻态），SWD接口除外。
  * @note   PD7和PD8为调试接口
  *
  * @param  None
  *
  * @retval None
  */
void FL_GPIO_ALLPIN_LPM_MODE(void)
{
    FL_GPIO_DeInit(GPIOA, FL_GPIO_PIN_ALL);
    FL_GPIO_DeInit(GPIOB, FL_GPIO_PIN_ALL);
    FL_GPIO_DeInit(GPIOC, FL_GPIO_PIN_ALL);
    FL_GPIO_DeInit(GPIOD, FL_GPIO_PIN_ALL_EXCEPTSWD);
}

/**
  * @}
  */

#endif /* FL_GPIO_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
