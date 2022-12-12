/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_lcd.c
  * @author  FMSH Application Team
  * @brief   Src file of LCD FL Module
  *******************************************************************************************************
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
  *******************************************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup LCD
  * @{
  */

#ifdef FL_LCD_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup Private_Macros
  * @{
  */

#define         IS_FL_LCD_INSTANCE(INTENCE)             ((INTENCE) == LCD)

#define         IS_FL_LCD_BIASCURRENT(__VALUE__)        (((__VALUE__) == (FL_LCD_BIAS_CURRENT_VERYHIGH))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_CURRENT_HIGH))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_CURRENT_MEDIUM))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_CURRENT_LOW)))

#define         IS_FL_LCD_ENMODE(__VALUE__)             ((__VALUE__) == (FL_LCD_DRIVER_MODE_INNER_RESISTER))

#define         IS_FL_LCD_BIASVOLTAGE(__VALUE__)        (((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL0))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL1))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL2))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL3))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL4))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL5))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL6))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL7))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL8))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL9))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL10))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL11))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL12))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL13))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL14))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_VOLTAGE_LEVEL15)))

#define         IS_FL_LCD_BIASMD(__VALUE__)             (((__VALUE__) == (FL_LCD_BIAS_MODE_4BIAS))||\
                                                        ((__VALUE__) == (FL_LCD_BIAS_MODE_3BIAS)))

#define         IS_FL_LCD_BWFT(__VALUE__)               (((__VALUE__) == (FL_LCD_WAVEFORM_TYPEA))||\
                                                        ((__VALUE__) == (FL_LCD_WAVEFORM_TYPEB)))

#define         IS_FL_LCD_LMUX(__VALUE__)               (((__VALUE__) == (FL_LCD_COM_NUM_4COM))||\
                                                        ((__VALUE__) == (FL_LCD_COM_NUM_6COM))||\
                                                        ((__VALUE__) == (FL_LCD_COM_NUM_8COM)))


/**
  * @}
  */

/* Private functions -----------------------------------------------*/
/** @defgroup LCD_FL_PF LCD Private Functions
  * @{
  */

/**
  * @brief  获取LCD工作频率寄存器值
  * @param  freq 工作频率
  * @retval 工作频率寄存器值
  */
static uint32_t FL_LCD_DisplayFreq(uint32_t freq)
{
    uint32_t displayFreq = 32;
    if((freq > 0) && (freq <= 100))
    {
        switch(FL_LCD_GetCOMNumber(LCD))
        {
            case FL_LCD_COM_NUM_4COM:
                displayFreq = (uint32_t)(32768.0 / (float)(4 * freq * 2) + 0.5);
                break;
            case FL_LCD_COM_NUM_6COM:
                displayFreq = (uint32_t)(32768.0 / (float)(6 * freq * 2) + 0.5);
                break;
            case FL_LCD_COM_NUM_8COM:
                displayFreq = (uint32_t)(32768.0 / (float)(8 * freq * 2) + 0.5);
                break;
        }
    }
    return displayFreq & 0xff;
}

/**
  * @brief  获取LCD闪烁时间寄存器值
  * @param  time 闪烁时间
  * @retval 闪烁时间寄存器值
  */
static uint32_t FL_LCD_FlickTime(uint32_t time)
{
    float stepTime = 0;
    switch(FL_LCD_GetCOMNumber(LCD))
    {
        case FL_LCD_COM_NUM_4COM:
            stepTime = (float)(4 * FL_LCD_ReadDisplayFrequency(LCD) * 2 * 16 * 1000) / 32768.0;
            break;
        case FL_LCD_COM_NUM_6COM:
            stepTime = (float)(6 * FL_LCD_ReadDisplayFrequency(LCD) * 2 * 16 * 1000) / 32768.0;
            break;
        case FL_LCD_COM_NUM_8COM:
            stepTime = (float)(8 * FL_LCD_ReadDisplayFrequency(LCD) * 2 * 16 * 1000) / 32768.0;
            break;
    }
    return (uint32_t)(time / stepTime + 0.5);
}

/**
  * @}
  */

/* Exported functions -----------------------------------------------*/
/** @addtogroup LCD_FL_EF_Init
  * @{
  */

/**
  * @brief  复位LCD
  *
  * @param  LCDx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_LCD_DeInit(LCD_Type *LCDx)
{
    assert_param(IS_FL_LCD_INSTANCE(LCDx));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    /* 复位LCD外设寄存器 */
    FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_LCD);
    FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_LCD);
    /* 关闭外设总线始时钟和工作时钟 */
    FL_RCC_DisableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_LCD);
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  配置LCD
  * @param  LCDx 外设入口地址
  * @param  initStruct 指向 @ref FL_LPTIM32_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_LCD_Init(LCD_Type *LCDx, FL_LCD_InitTypeDef *initStruct)
{
    assert_param(IS_FL_LCD_INSTANCE(LCDx));
    assert_param(IS_FL_LCD_BIASCURRENT(initStruct->biasCurrent));
    assert_param(IS_FL_LCD_ENMODE(initStruct->mode));
    assert_param(IS_FL_LCD_BIASVOLTAGE(initStruct->biasVoltage));
    assert_param(IS_FL_LCD_BIASMD(initStruct->biasMode));
    assert_param(IS_FL_LCD_BWFT(initStruct->waveform));
    assert_param(IS_FL_LCD_LMUX(initStruct->COMxNum));
    /* 外设总线始时钟 */
    FL_RCC_EnableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_LCD);
    /* 电流源电流控制 */
    FL_LCD_SetBiasCurrent(LCD, initStruct->biasCurrent);
    /* LCD驱动模式 */
    FL_LCD_SetDriverMode(LCD, initStruct->mode);
    /* 偏执电压设置 */
    FL_LCD_SetBiasVoltage(LCD, initStruct->biasVoltage);
    /* 偏执模式选择 */
    FL_LCD_SetBiasMode(LCD, initStruct->biasMode);
    /* 驱动波形设置 */
    FL_LCD_SetWaveform(LCD, initStruct->waveform);
    /* COMx口选择 */
    FL_LCD_SetCOMNumber(LCD, initStruct->COMxNum);
    /* 设置工作频率 */
    FL_LCD_WriteDisplayFrequency(LCD, FL_LCD_DisplayFreq(initStruct->displayFreq));
    /* 设置闪烁频率 */
    FL_LCD_WriteDisplayOnTime(LCD, FL_LCD_FlickTime(initStruct->flickOnTime));
    FL_LCD_WriteDisplayOffTime(LCD, FL_LCD_FlickTime(initStruct->flickOffTime));
    /* 使能外设 */
    FL_LCD_Enable(LCD);
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_LCD_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_LCD_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_LCD_StructInit(FL_LCD_InitTypeDef *initStruct)
{
    initStruct->biasCurrent         =   FL_LCD_BIAS_CURRENT_HIGH;
    initStruct->mode                =   FL_LCD_DRIVER_MODE_INNER_RESISTER;
    initStruct->biasVoltage         =   FL_LCD_BIAS_VOLTAGE_LEVEL10;
    initStruct->biasMode            =   FL_LCD_BIAS_MODE_3BIAS;
    initStruct->waveform            =   FL_LCD_WAVEFORM_TYPEA;
    initStruct->COMxNum             =   FL_LCD_COM_NUM_6COM;
    initStruct->displayFreq         =   42;
    initStruct->flickOnTime         =   0;
    initStruct->flickOffTime        =   0;
}

/**
  * @}
  */

/** @addtogroup LCD_FL_EF_Operation
  * @{
  */

/**
  * @brief  设置 LCD 4COM显示字端
  * @param  display 指向显示信息的缓存区域，可直接指向LCD的DATAx寄存器。
  * @param  com 待显示字段所在COM。范围0-4。
  * @param  seg 待显示字段所在SEG。范围0-31。
  * @param  state 待显示字段状态。0，熄灭；否则，点亮。
  *
  * @retval None
  */
void FL_LCD_4COMDisplay(uint32_t *display, uint8_t com, uint8_t seg, uint8_t state)
{
    if(state != 0)
    {
        state = 1;
    }
    MODIFY_REG(display[com], 0x1 << seg, state << seg);
}

/**
  * @brief  设置 LCD 6COM显示字端
  * @param  display 指向显示信息的缓存区域，可直接指向LCD的DATAx寄存器。
  * @param  com 待显示字段所在COM。范围0-6。
  * @param  seg 待显示字段所在SEG。范围0-29。
  * @param  state 待显示字段状态。0，熄灭；否则，点亮。
  *
  * @retval None
  */
void FL_LCD_6COMDisplay(uint32_t *display, uint8_t com, uint8_t seg, uint8_t state)
{
    if(state != 0)
    {
        state = 1;
    }
    MODIFY_REG(display[com], 0x1 << seg, state << seg);
}

/**
  * @brief  设置 LCD 8COM显示字端
  * @param  display 指向显示信息的缓存区域，可直接指向LCD的DATAx寄存器。
  * @param  com 待显示字段所在COM。范围0-8。
  * @param  seg 待显示字段所在SEG。范围0-27。
  * @param  state 待显示字段状态。0，熄灭；否则，点亮。
  *
  * @retval None
  */
void FL_LCD_8COMDisplay(uint32_t *display, uint8_t com, uint8_t seg, uint8_t state)
{
    if(state != 0)
    {
        state = 1;
    }
    MODIFY_REG(display[com], 0x1 << seg, state << seg);
}

/**
  * @}
  */

#endif /* FL_LCD_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
