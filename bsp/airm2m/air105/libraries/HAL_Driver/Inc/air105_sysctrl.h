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



#ifndef __AIR105_SYSCTRL_H
#define __AIR105_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

#define SYSCTRL_FREQ_SEL_POWERMODE_Pos                  (24)
#define SYSCTRL_FREQ_SEL_POWERMODE_Mask                 (0x07 << SYSCTRL_FREQ_SEL_POWERMODE_Pos)
#define SYSCTRL_FREQ_SEL_POWERMODE_CLOSE_CPU            (0x00 << SYSCTRL_FREQ_SEL_POWERMODE_Pos)
#define SYSCTRL_FREQ_SEL_POWERMODE_CLOSE_CPU_MEM        (0x01 << SYSCTRL_FREQ_SEL_POWERMODE_Pos)


/** @defgroup SYSCTRL_Exported_Types
  * @{
  */
typedef struct
{
    uint32_t PLL_Frequency;     /*!< returns PLL frequency expressed in Hz */
    uint32_t CPU_Frequency;     /*!< returns CPU frequency expressed in Hz */
    uint32_t HCLK_Frequency;    /*!< returns HCLK frequency expressed in Hz */
    uint32_t PCLK_Frequency;    /*!< returns PCLK frequency expressed in Hz */
}SYSCTRL_ClocksTypeDef;

typedef enum
{
    SleepMode_CpuOff = 0,       /*!< CPU Sleep  */
    SleepMode_DeepSleep,        /*!< Deep Sleep */
    SleepMode_Invalid
}SleepMode_TypeDef;
#define IS_ALL_SLEEP_MODE(MODE)                     ((MODE) < SleepMode_Invalid)

typedef enum
{
    SELECT_EXT12M,
    SELECT_INC12M
} SYSCLK_SOURCE_TypeDef;
#define IS_SYSCLK_SOURCE(FREQ)                      (((FREQ) == SELECT_EXT12M) || \
                                                    ((FREQ) == SELECT_INC12M))
typedef enum
{
    SYSCTRL_PLL_108MHz      = (uint32_t)0x01,
    SYSCTRL_PLL_120MHz      = (uint32_t)0x02,
    SYSCTRL_PLL_132MHz      = (uint32_t)0x03,
    SYSCTRL_PLL_144MHz      = (uint32_t)0x04,
    SYSCTRL_PLL_156MHz      = (uint32_t)0x05,
    SYSCTRL_PLL_168MHz      = (uint32_t)0x06,
    SYSCTRL_PLL_180MHz      = (uint32_t)0x07,
    SYSCTRL_PLL_192MHz      = (uint32_t)0x08,
    SYSCTRL_PLL_204MHz      = (uint32_t)0x09
}SYSCTRL_PLL_TypeDef;
#define IS_PLL_FREQ(FREQ)                          (((FREQ) == SYSCTRL_PLL_108MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_120MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_132MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_144MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_156MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_168MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_180MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_192MHz)  || \
                                                    ((FREQ) == SYSCTRL_PLL_204MHz))
/**
  * @}
  */

#define SYSCTRL_PLL_Div_None                       ((uint32_t)0x00)
#define SYSCTRL_PLL_Div2                           ((uint32_t)0x01)
#define SYSCTRL_PLL_Div4                           ((uint32_t)0x10)
#define IS_GET_SYSCTRL_PLL_DIV(DIV)                (((DIV) == SYSCTRL_PLL_Div_None) || \
                                                    ((DIV) == SYSCTRL_PLL_Div2) || \
                                                    ((DIV) == SYSCTRL_PLL_Div4))

#define SYSCTRL_HCLK_Div_None                      ((uint32_t)0x00)
#define SYSCTRL_HCLK_Div2                          ((uint32_t)0x01)
#define IS_GET_SYSCTRL_HCLK_DIV(DIV)               (((DIV) == SYSCTRL_HCLK_Div_None) || \
                                                    ((DIV) == SYSCTRL_HCLK_Div2))

#define SYSCTRL_PCLK_Div2                          ((uint32_t)0x01)
#define SYSCTRL_PCLK_Div4                          ((uint32_t)0x02)
#define IS_GET_SYSCTRL_PCLK_DIV(DIV)               (((DIV) == SYSCTRL_PCLK_Div2) || \
                                                    ((DIV) == SYSCTRL_PCLK_Div4))

#define SYSCTRL_CHIP_SN_ADDR                        ((uint32_t)0x40008804)
#define SYSCTRL_CHIP_SN_LEN                         ((uint32_t)0x10)

#define SYSCTRL_USB_DOWNLOAD_FLAG                    ((uint32_t)0X55)

void SYSCTRL_AHBPeriphClockCmd(uint32_t SYSCTRL_AHBPeriph, FunctionalState NewState);
void SYSCTRL_AHBPeriphResetCmd(uint32_t SYSCTRL_AHBPeriph, FunctionalState NewState);
void SYSCTRL_APBPeriphClockCmd(uint32_t SYSCTRL_APBPeriph, FunctionalState NewState);
void SYSCTRL_APBPeriphResetCmd(uint32_t SYSCTRL_APBPeriph, FunctionalState NewState);

void SYSCTRL_EnterSleep(SleepMode_TypeDef SleepMode);

void SYSCTRL_SYSCLKSourceSelect(SYSCLK_SOURCE_TypeDef source_select);
void SYSCTRL_PLLConfig(SYSCTRL_PLL_TypeDef PLL_Freq);
void SYSCTRL_PLLDivConfig(uint32_t PLL_Div);
void SYSCTRL_HCLKConfig(uint32_t HCLK_Div);
void SYSCTRL_PCLKConfig(uint32_t PCLK_Div);

void SYSCTRL_GetClocksFreq(SYSCTRL_ClocksTypeDef* SYSCTRL_Clocks);
void SYSCTRL_GetChipSN(unsigned char *ChipSN);

void SYSCTRL_SoftReset(void);
void SYSCTRL_EnterUSBDownload(void);

#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
