/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __AIR105_ADC_H__
#define __AIR105_ADC_H__


#ifdef __cplusplus
extern "C" {
#endif

/* Include ------------------------------------------------------------------*/
#include "air105.h"

#define IS_ADC_PERIPH(PERIPH) ((PERIPH) == ADC0)

#define ADC_CR1_CHANNEL_MASK           ((uint32_t)0x07)
#define ADC_CR1_SAMPLE_RATE_Pos         3
#define ADC_CR1_SAMPLE_RATE_MASK       (0x3 << ADC_CR1_SAMPLE_RATE_Pos)
#define ADC_CR1_SAMP_ENABLE             BIT(6)
#define ADC_CR1_POWER_DOWN              BIT(8)
#define ADC_CR1_IRQ_ENABLE              BIT(5)

#define ADC_SR_DONE_FLAG                BIT(0)
#define ADC_SR_FIFO_OV_FLAG             BIT(1)

#define ADC_FIFO_OV_INT_ENABLE          BIT(2)
#define ADC_FIFO_RESET                  BIT(1)

#define ADC_FIFO_ENABLE                 BIT(0)

#define ADC_CR2_BUFF_ENABLE             BIT(14)
#define ADC_DIV_RESISTOR_EN_BIT         BIT(13)


typedef enum
{
    ADC_Overflow = 0,
    ADC_NoOverflow = 1,
}ADC_OverflowTypeDef;

/* ADC Channel select */
typedef enum
{
    ADC_CHANNEL_CHARGE_VBAT =0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
}ADC_ChxTypeDef;
#define IS_ADC_CHANNEL(CHANNEL_NUM) (((CHANNEL_NUM) == ADC_CHANNEL_CHARGE_VBAT) || \
                                     ((CHANNEL_NUM) == ADC_CHANNEL_1) || \
                                     ((CHANNEL_NUM) == ADC_CHANNEL_2) || \
                                     ((CHANNEL_NUM) == ADC_CHANNEL_3) || \
                                     ((CHANNEL_NUM) == ADC_CHANNEL_4) || \
                                     ((CHANNEL_NUM) == ADC_CHANNEL_5) || \
                                     ((CHANNEL_NUM) == ADC_CHANNEL_6))

/* ADC Samp Select */
typedef enum
{
    ADC_SpeedPrescaler_None = 0,
    ADC_SpeedPrescaler_2,
    ADC_SpeedPrescaler_4,
    ADC_SpeedPrescaler_8,
}ADC_SampTypeDef;

#define IS_ADC_SAMP(SAMP)           (((SAMP) == ADC_SpeedPrescaler_None)  || \
                                     ((SAMP) == ADC_SpeedPrescaler_2) || \
                                     ((SAMP) == ADC_SpeedPrescaler_4) || \
                                     ((SAMP) == ADC_SpeedPrescaler_8))


typedef struct _ADC_InitTypeDef
{
    ADC_ChxTypeDef              ADC_Channel;            /* ADC Channel select */
    ADC_SampTypeDef             ADC_SampSpeed;          /* ADC sampspeed select */
    FunctionalState             ADC_IRQ_EN;             /* ADC IRQ/Polling Select */
    FunctionalState             ADC_FIFO_EN;            /* ADC FIFO Enable Select */
} ADC_InitTypeDef;

/* Exported constants -------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct);

void ADC_StartCmd(FunctionalState NewState);

void ADC_FIFODeepth(uint32_t FIFO_Deepth);

void ADC_FIFOReset(void);

void ADC_ITCmd(FunctionalState NewState);

void ADC_FIFOOverflowITcmd(FunctionalState NewState);

void ADC_BuffCmd(FunctionalState NewState);

void ADC_DivResistorCmd(FunctionalState NewState);

int32_t ADC_GetFIFOCount(void);

int32_t ADC_GetResult(void);

int32_t ADC_GetFIFOResult(uint16_t *ADCdata, uint32_t len);

uint32_t ADC_CalVoltage(uint32_t u32ADC_Value, uint32_t u32ADC_Ref_Value);

ADC_ChxTypeDef ADC_GetChannel(void);

FunctionalState ADC_IsDivResistorEnable(void);

ADC_OverflowTypeDef ADC_IsFIFOOverflow(void);

void ADC_ChannelSwitch(ADC_ChxTypeDef Channelx);

/* Exported variables -------------------------------------------------------*/

/* Exported types -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /* __AIR105_ADC_H__ */

