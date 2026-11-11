/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_exit.h
 * @brief    source file for setting exit
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2021-12-24      yangzhengfeng      V1.0.0         Modify the register module configuration
 * 2021-01-03      wangjingfan        V1.0.1         Compile error correction
 */

#ifndef __YC_EXTI_H__
#define __YC_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "yc3122.h"
#include "yc_gpio.h"

/**
 * @brief  EXTI Trigger enumeration
 */
typedef enum
{
    EXTI_Trigger_Off            = 0,
    EXTI_Trigger_HighLev        = 1,
    EXTI_Trigger_LowLev         = 2,
    EXTI_Trigger_Rising         = 3,
    EXTI_Trigger_Falling        = 4,
    EXTI_Trigger_Rising_Falling = 5,
    EXTI_Trigger_DEFAULT_VAL    = 0xff
} EXTI_TriggerTypeDef;

#define IS_TRIG_TYPEDEF(TRIGTYPE)  ((TRIGTYPE) == EXTI_Trigger_Off            || \
                                    (TRIGTYPE) == EXTI_Trigger_HighLev        || \
                                    (TRIGTYPE) == EXTI_Trigger_LowLev         || \
                                    (TRIGTYPE) == EXTI_Trigger_Rising         || \
                                    (TRIGTYPE) == EXTI_Trigger_Falling        || \
                                    (TRIGTYPE) == EXTI_Trigger_Rising_Falling)

/**
 * @brief  EXTI Trigger source
 */
typedef enum
{
    EXTI_Line_0             = 0,
    EXTI_Line_1             = 1,
    EXTI_Line_2             = 2,
    EXTI_Line_3             = 3,
    EXTI_Line_4             = 4,
    EXTI_Line_DEFAULT_VAL   = 0xff
} EXTI_LineTypeDef;

#define IS_EXTI_LINE(LINE)     (((LINE) == EXTI_Line_0) || \
                                ((LINE) == EXTI_Line_1) || \
                                ((LINE) == EXTI_Line_2) || \
                                ((LINE) == EXTI_Line_3) || \
                                ((LINE) == EXTI_Line_4))

#define IS_EXTI_PIN_SOURCE(PIN)  (((((PIN) & ~(uint16_t)0xFFFF)) == 0x00) && ((PIN) != (uint16_t)0x00))

#define EXTI_MODE_TypeDef              GPIO_MODULE_TypeDef
#define EXTI_PIN_TypeDef               GPIO_Pin_TypeDef
#define EXIT_Num                       GPIO_PORT_NUM
#define EXIT_Pin_Num                   GPIO_PIN_NUM

void EXTI_ClearITPendingBit(EXTI_LineTypeDef EXTI_Line, EXTI_PIN_TypeDef EXTI_PinSource);
void EXTI_DeInit(void);
uint16_t EXTI_GetITLineStatus(EXTI_LineTypeDef EXTI_Line);
uint16_t EXTI_GetITEXTI_PinSourceStatus(EXTI_LineTypeDef EXTI_Line, EXTI_PIN_TypeDef EXTI_PinSource);
void EXTI_LineConfig(EXTI_LineTypeDef EXTI_Line, EXTI_PIN_TypeDef EXTI_PinSource, EXTI_TriggerTypeDef EXTI_Trigger);

#ifdef __cplusplus
}
#endif

#endif  /* __YC_EXTI_H__ */

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
