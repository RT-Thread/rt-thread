/*
  ******************************************************************************
  * @file    HAL_LCD.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of lcd HAL module.
  ******************************************************************************
*/
#ifndef __HAL_LCD_H__
#define __HAL_LCD_H__

#include "ACM32Fxx_HAL.h"

/******************************************************************************/
/*                                                                            */
/*                          LCD Controller (LCD)                              */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/*                    Peripheral Registers Bits Definition                    */
/******************************************************************************/

/*******************  Bit definition for LCD_CR0 register  *********************/
#define LCD_CR0_LCDEN_Pos              (0U)
#define LCD_CR0_LCDEN_Msk             (0x1UL << LCD_CR0_LCDEN_Pos)
#define LCD_CR0_LCDEN                 LCD_CR0_LCDEN_Msk

#define LCD_CR0_LCDCLK_Pos             (1U)
#define LCD_CR0_LCDCLK_Msk             (0x7UL << LCD_CR0_LCDCLK_Pos)
#define LCD_CR0_LCDCLK                  LCD_CR0_LCDCLK_Msk
#define LCD_CR0_LCDCLK_0               (0x1UL << LCD_CR0_LCDCLK_Pos)
#define LCD_CR0_LCDCLK_1               (0x2UL << LCD_CR0_LCDCLK_Pos)

#define LCD_CR0_STATIC_Pos            (4U)
#define LCD_CR0_STATIC_Msk            (0x1UL << LCD_CR0_STATIC_Pos)
#define LCD_CR0_STATIC                LCD_CR0_STATIC_Msk

#define LCD_CR0_BIAS_Pos             (5U)
#define LCD_CR0_BIAS_Msk             (0x3UL << LCD_CR0_BIAS_Pos)
#define LCD_CR0_BIAS                 LCD_CR0_BIAS_Msk
#define LCD_CR0_BIAS_0               (0x1UL << LCD_CR0_BIAS_Pos)
#define LCD_CR0_BIAS_1               (0x2UL << LCD_CR0_BIAS_Pos)

#define LCD_CR0_DUTY_Pos             (7U)
#define LCD_CR0_DUTY_Msk             (0x7UL << LCD_CR0_DUTY_Pos)
#define LCD_CR0_DUTY                 LCD_CR0_DUTY_Msk
#define LCD_CR0_DUTY_0               (0x1UL << LCD_CR0_DUTY_Pos)
#define LCD_CR0_DUTY_1               (0x2UL << LCD_CR0_DUTY_Pos)
#define LCD_CR0_DUTY_2               (0x4UL << LCD_CR0_DUTY_Pos)

#define LCD_CR0_MOD_Pos             (11U)
#define LCD_CR0_MOD_Msk             (0x3UL << LCD_CR0_MOD_Pos)
#define LCD_CR0_MOD                 LCD_CR0_MOD_Msk
#define LCD_CR0_MOD_0               (0x1UL << LCD_CR0_MOD_Pos)
#define LCD_CR0_MOD_1               (0x2UL << LCD_CR0_MOD_Pos)

#define LCD_CR0_CONTRAST_Pos             (13U)
#define LCD_CR0_CONTRAST_Msk             (0xfUL << LCD_CR0_CONTRAST_Pos)
#define LCD_CR0_CONTRAST                 LCD_CR0_CONTRAST_Msk
#define LCD_CR0_CONTRAST_0               (0x1UL << LCD_CR0_CONTRAST_Pos)
#define LCD_CR0_CONTRAST_1               (0x2UL << LCD_CR0_CONTRAST_Pos)
#define LCD_CR0_CONTRAST_2               (0x4UL << LCD_CR0_CONTRAST_Pos)
#define LCD_CR0_CONTRAST_3               (0x8UL << LCD_CR0_CONTRAST_Pos)

#define LCD_CR0_WSEL_Pos                (17U)
#define LCD_CR0_WSEL_Msk                (0x1UL << LCD_CR0_WSEL_Pos)
#define LCD_CR0_WSEL                     LCD_CR0_WSEL_Msk

/*******************  Bit definition for LCD_CR1 register  *********************/
#define LCD_CR1_BLINKCNT_Pos             (0U)
#define LCD_CR1_BLINKCNT_Msk             (0x3FUL << LCD_CR1_BLINKCNT_Pos)
#define LCD_CR1_BLINKCNT                  LCD_CR1_BLINKCNT_Msk


#define LCD_CR1_BLINKEN_Pos             (6U)
#define LCD_CR1_BLINKEN_Msk             (0x1UL << LCD_CR1_BLINKEN_Pos)
#define LCD_CR1_BLINKEN                  LCD_CR1_BLINKEN_Msk

#define LCD_CR1_MODE_Pos             (8U)
#define LCD_CR1_MODE_Msk             (0x1UL << LCD_CR1_MODE_Pos)
#define LCD_CR1_MODE                  LCD_CR1_MODE_Msk

#define LCD_CR1_IE_Pos             (9U)
#define LCD_CR1_IE_Msk             (0x1UL << LCD_CR1_IE_Pos)
#define LCD_CR1_IE                  LCD_CR1_IE_Msk

#define LCD_CR1_DMAEN_Pos             (10U)
#define LCD_CR1_DMAEN_Msk             (0x1UL << LCD_CR1_DMAEN_Pos)
#define LCD_CR1_DMAEN                  LCD_CR1_DMAEN_Msk

#define LCD_CR1_INTF_Pos             (11U)
#define LCD_CR1_INTF_Msk             (0x1UL << LCD_CR1_INTF_Pos)
#define LCD_CR1_INTF                  LCD_CR1_INTF_Msk

#define LCD_CR1_FCC_Pos             (12U)
#define LCD_CR1_FCC_Msk             (0x1UL << LCD_CR1_FCC_Pos)
#define LCD_CR1_FCC                  LCD_CR1_FCC_Msk

#define LCD_CR1_MODSEL_Pos             (13U)
#define LCD_CR1_MODSEL_Msk             (0x3UL << LCD_CR1_MODSEL_Pos)
#define LCD_CR1_MODSEL                  LCD_CR1_MODSEL_Msk
#define LCD_CR1_MODSEL_0               (0x1UL << LCD_CR1_MODSEL_Pos)
#define LCD_CR1_MODSEL_1               (0x2UL << LCD_CR1_MODSEL_Pos)

#define LCD_CR1_RSEL_Pos             (15U)
#define LCD_CR1_RSEL_Msk             (0x1UL << LCD_CR1_RSEL_Pos)
#define LCD_CR1_RSEL                  LCD_CR1_RSEL_Msk

#define LCD_CR1_PON_Pos              (13U)
#define LCD_CR1_PON_Msk              (0x3fUL << LCD_CR1_PON_Pos)
#define LCD_CR1_PON                  LCD_CR1_PON_Msk

/*******************  Bit definition for LCD_CR1 register  *********************/
#define LCD_INTCLR_INTF_Pos             (10U)
#define LCD_INTCLR_INTF_Msk             (0x1UL << LCD_INTCLR_INTF_Pos)
#define LCD_INTCLR_INTFT                  LCD_INTCLR_INTF_Msk



/**
  * @brief LCD SegCom Init structure definition
  */
typedef struct
{
    uint32_t SEG0_31;      /*!< Configures the SEG0 to SEG31 Enable or Disable.
                            This parameter can be a value between 0x0 and 0xFFFFFFFF */
    union{
            uint32_t SEG32_39_COM0_8;   /*!< Configures the SEG32-35 and COM0-8 Enable or Disable.
                                        This parameter can be a value between 0x0 and 0xFFF */
            struct
            {
                uint32_t SEG32_35      :4;  /*!< Configures the SEG32-35 Enable or Disable.
                                            This parameter can be a value between 0x0 and 0xF */
                uint32_t SEG36_COM7    :1;  /*!< Configures the SEG36/COM7 Enable or Disable.  */
                uint32_t SEG37_COM6    :1;  /*!< Configures the SEG37/COM6 Enable or Disable.  */
                uint32_t SEG38_COM5    :1;  /*!< Configures the SEG38/COM5 Enable or Disable.  */
                uint32_t SEG39_COM4    :1;  /*!< Configures the SEG39/COM4 Enable or Disable.  */
                uint32_t COM0_3        :4;  /*!< Configures the COM0-3 Enable or Disable.
                                            This parameter can be a value between 0x0 and 0xF */
            }SEGCOM_bit;
    }Stc_SEG32_39_COM0_8;
}LCD_SegComInitTypeDef;


/**
  * @brief LCD Init structure definition
  */

typedef struct
{
  uint32_t PONTime;         /*!< Configures the Pulse ON duration time.
                            This parameter can be a value between 0x00 and 0x3F */
  uint32_t BiasRes;        /*!< Configures the LCD BiasRes.
                                 This parameter can be one value of @ref BiasRes */
  uint32_t DriveMod;    /*!< Configures the LCD DriveMod.
                                 This parameter can be one value of @ref DriveMod */
  uint32_t FastCharge;     /*!< Configures the LCD FastCharge.
                                 This parameter can be one value of @ref FastCharge */
  uint32_t Contrast;        /*!< Configures the LCD Contrast.
                                 This parameter can be one value of @ref LCD_Contrast */

}LCD_InResInitTypeDef;
/**
  * @brief LCD Init structure definition
  */

typedef struct
{
  uint32_t Duty;            /*!< Configures the LCD Duty.
                                 This parameter can be one value of @ref LCD_Duty */
  uint32_t Bias;            /*!< Configures the LCD Bias.
                                 This parameter can be one value of @ref LCD_Bias */
  uint32_t Driving_Waveform; /*!< Configures the LCD Drive Waveform.
                                 This parameter can be one value of @ref Driving_Waveform */

  uint32_t BiasSrc;                  /*!< Configures the LCD Bias Src.
                                 This parameter can be one value of @ref BiasSrc*/

  uint32_t DisplayMode;      /*!< Configures the LCD DisplayMode.
                                 This parameter can be one value of @ref DisplayMode*/

  uint32_t StaticPower;   /*!< Configures the LCD StaticPower.
                                 This parameter can be one value of @ref StaticPower*/

  uint32_t LCDFrequency;  /*!< Configures the LCD LCDFrequency.
                                 This parameter can be one value of @ref LCDFrequency*/

  uint32_t BlinkEN;           /*!< Configures the LCD BlinkEN.
                                 This parameter can be one value of @ref BlinkEN */

  uint32_t BlinkFrequency;  /*!< Configures the LCD Blink frequency.
                            This parameter can be a value between 0x00 and 0x3F */
}LCD_InitTypeDef;


/**
  * @brief  LCD handle Structure definition
  */
typedef struct
{
  LCD_TypeDef                   *Instance;  /* LCD registers base address */

  LCD_InitTypeDef               Init;       /* LCD communication parameters */

  DMA_HandleTypeDef           *DMA_Handle;                 /*!< UART Rx DMA handle parameters */
}LCD_HandleTypeDef;


#define IS_LCD_PERIPH(PERIPH) (((PERIPH) == LCD))

/** @defgroup LCD_Duty LCD Duty
  * @{
  */

#define LCD_DUTY_STATIC                 ((uint32_t)0x00000000U)                                     /*!< Static duty */
#define LCD_DUTY_1_2                    LCD_CR0_DUTY_0                                            /*!< 1/2 duty    */
#define LCD_DUTY_1_3                    LCD_CR0_DUTY_1                                            /*!< 1/3 duty    */
#define LCD_DUTY_1_4                    ((LCD_CR0_DUTY_1 | LCD_CR0_DUTY_0))                         /*!< 1/4 duty    */
#define LCD_DUTY_1_6                    ((LCD_CR0_DUTY_2 | LCD_CR0_DUTY_0))                         /*!< 1/6 duty    */
#define LCD_DUTY_1_8                    ((LCD_CR0_DUTY_2 | LCD_CR0_DUTY_1 | LCD_CR0_DUTY_0))      /*!< 1/8 duty    */

#define IS_LCD_DUTY(DUTY)      (((DUTY) == LCD_DUTY_STATIC)  || \
                               ((DUTY) == LCD_DUTY_1_2)     || \
                               ((DUTY) == LCD_DUTY_1_3)     || \
                               ((DUTY) == LCD_DUTY_1_4)     || \
                               ((DUTY) == LCD_DUTY_1_6)     || \
                               ((DUTY) == LCD_DUTY_1_8))

/**
  * @}
  */

 /**
  * @}
  */


/** @defgroup LCD_Bias LCD Bias
  * @{
  */

#define LCD_BIAS_1_4                    ((uint32_t)0x00000000U) /*!< 1/4 Bias */
#define LCD_BIAS_1_2                    LCD_CR0_BIAS_0           /*!< 1/2 Bias */
#define LCD_BIAS_1_3                    LCD_CR0_BIAS_1           /*!< 1/3 Bias */

#define IS_LCD_BIAS(__BIAS__) (((__BIAS__) == LCD_BIAS_1_4) || \
                               ((__BIAS__) == LCD_BIAS_1_2) || \
                               ((__BIAS__) == LCD_BIAS_1_3))
/**
  * @}
  */

 /** @defgroup Driving_Waveform  Driving_Waveform
  * @{
  */

#define LCD_Driving_Waveform_A                    ((uint32_t)0x00000000U) /*!< A类波形*/
#define LCD_Driving_Waveform_B                     LCD_CR0_WSEL           /*!< B类波形 */
#define IS_LCD_Driving_Waveform(__Driving_Waveform__)         (((__Driving_Waveform__) == LCD_Driving_Waveform_A) || \
                                                                ((__Driving_Waveform__) == LCD_Driving_Waveform_B))
/**
  * @}
  */

  /** @defgroup BiasSrc
  * @{
  */

#define LCD_BiasSrc_InRes_Seg31_35_Normal                   ((uint32_t)0x00000000U) /*!< LCD Bias来源：内部电阻分压，且SEG31-35可以作为SEG/IO*/
#define LCD_BiasSrc_InRes_Seg31_35_Cap                      LCD_CR0_MOD_0           /*!< LCD Bias来源：内部电阻分压，且SEG31-35用于外接电容滤波，SEG/IO功能关闭 */
#define LCD_BiasSrc_ExRes_Seg31_35_Cap                      LCD_CR0_MOD_1           /*!< LCD Bias来源：外部电阻分压，且SEG31-35用于外接分压电阻和滤波电容，SEG/IO功能关闭 */
#define IS_LCD_BiasSrc(__BiasSrc__)                         (((__BiasSrc__) == LCD_BiasSrc_InRes_Seg31_35_Normal) || \
                                                          ((__BiasSrc__) == LCD_BiasSrc_InRes_Seg31_35_Cap)||\
                                                          ((__BiasSrc__) == LCD_BiasSrc_ExRes_Seg31_35_Cap))
/**
  * @}
  */

  /** @defgroup DisplayMode
  * @{
  */

#define LCD_DisplayMode_0                        ((uint32_t)0x00000000U) /*!< LCD RAM显示模式0*/
#define LCD_DisplayMode_1                          LCD_CR1_MODE           /*!< LCD RAM显示模式1 */
#define IS_LCD_DisplayMode(__DisplayMode__)                         (((__DisplayMode__) == LCD_DisplayMode_0)||\
                                                                    ((__DisplayMode__) == LCD_DisplayMode_1))
/**
  * @}
  */


    /** @defgroup StaticPower
  * @{
  */

#define LCD_StaticPower_NormalPower                                 ((uint32_t)0x00000000U) /*!< LCD RAM显示模式0*/
#define LCD_StaticPower_LowPower                                     LCD_CR0_STATIC           /*!< LCD RAM显示模式1 */
#define IS_LCD_StaticPower(__StaticPower__)                         (((__StaticPower__) == LCD_StaticPower_NormalPower) || \
                                                                    ((__StaticPower__) == LCD_StaticPower_LowPower))
/**
  * @}
  */


/** @defgroup LCDFrequency
  * @{
  */

#define LCD_LCDFrequency_64HZ                                    ((uint32_t)0x00000000U)           /*!< LCD扫描频率选择*/
#define LCD_LCDFrequency_128HZ                                     LCD_CR0_LCDCLK_0           /*!< LCD扫描频率选择 */
#define LCD_LCDFrequency_256HZ                                     LCD_CR0_LCDCLK_1           /*!< LCD扫描频率选择 */
#define LCD_LCDFrequency_512HZ                                     ((LCD_CR0_LCDCLK_0 | LCD_CR0_LCDCLK_1))           /*!< LCD扫描频率选择*/
#define IS_LCD_LCDFrequency(__LCDFrequency__)                      (((__LCDFrequency__) == LCD_LCDFrequency_64HZ) || \
                                                                    ((__LCDFrequency__) == LCD_LCDFrequency_128HZ)||\
                                                                    ((__LCDFrequency__) == LCD_LCDFrequency_256HZ)||\
                                                                    ((__LCDFrequency__) == LCD_LCDFrequency_512HZ))
/**
  * @}
  */

 /** @defgroup BlinkEN
  * @{
  */
#define LCD_BlinkEN_Disable                                 ((uint32_t)0x00000000U)     /*!<LCD闪屏配置使能*/
#define LCD_BlinkEN_Enable                                     LCD_CR1_BLINKEN           /*!< LCD闪屏配置使能 */
#define IS_LCD_BlinkEN(__BlinkEN__)                         (((__BlinkEN__) == LCD_BlinkEN_Disable) || \
                                                             ((__BlinkEN__) == LCD_BlinkEN_Enable))
/**
  * @}
  */
#define IS_LCD_BlinkFrequency(__BlinkFrequency__)           ((__BlinkFrequency__)<= ((uint8_t)0x3F)) /*!<LCD闪屏配置*/

 /** @defgroup BiasRes
  * @{
  */
#define LCD_BiasRes_240k                                    ((uint32_t)0x00000000U)     /*!<LCD闪屏配置使能*/
#define LCD_BiasRes_4M                                       LCD_CR1_RSEL           /*!< LCD闪屏配置使能 */
#define IS_LCD_BiasRes(__BiasRes__)                         (((__BiasRes__) == LCD_BiasRes_240k) || \
                                                             ((__BiasRes__) == LCD_BiasRes_4M))
/**
  * @}
  */

  /** @defgroup DriveMod
  * @{
  */
#define LCD_DriveMod_Res240k4M                                    ((uint32_t)0x00000000U)     /*!<LCD闪屏配置使能*/
#define LCD_DriveMod_Res60k                                       LCD_CR1_MODSEL_0           /*!< LCD闪屏配置使能 */
#define LCD_DriveMod_FC                                        LCD_CR1_MODSEL_1           /*!< LCD闪屏配置使能 */
#define IS_LCD_DriveMod(__DriveMod__)                         (((__DriveMod__) == LCD_DriveMod_Res240k4M) || \
                                                             ((__DriveMod__) == LCD_DriveMod_Res60k)|| \
                                                             ((__DriveMod__) == LCD_DriveMod_FC))
/**
  * @}
  */


 /** @defgroup FastCharge
  * @{
  */
#define LCD_FastCharge_Disable                                 ((uint32_t)0x00000000U)     /*!<LCD闪屏配置使能*/
#define LCD_FastCharge_Enable                                     LCD_CR1_FCC           /*!< LCD闪屏配置使能 */
#define IS_LCD_FastCharge(__FastCharge__)                         (((__FastCharge__) == LCD_FastCharge_Disable) || \
                                                                    ((__FastCharge__) == LCD_FastCharge_Enable))
/**
  * @}
  */

 /** @defgroup LCD_Contrast
  * @{
  */
#define LCD_Contrast_531VDD                                     ((uint32_t)0x00000000U)    /*!<LCD对比度调整*/
#define LCD_Contrast_562VDD                                       (LCD_CR0_CONTRAST_0)
#define LCD_Contrast_593VDD                                       (LCD_CR0_CONTRAST_1)
#define LCD_Contrast_623VDD                                       (LCD_CR0_CONTRAST_1|LCD_CR0_CONTRAST_0)
#define LCD_Contrast_654VDD                                        (LCD_CR0_CONTRAST_2)
#define LCD_Contrast_686VDD                                        (LCD_CR0_CONTRAST_2|LCD_CR0_CONTRAST_0)
#define LCD_Contrast_717VDD                                        (LCD_CR0_CONTRAST_2|LCD_CR0_CONTRAST_1)
#define LCD_Contrast_748VDD                                        (LCD_CR0_CONTRAST_2|LCD_CR0_CONTRAST_1|LCD_CR0_CONTRAST_0)
#define LCD_Contrast_778VDD                                        (LCD_CR0_CONTRAST_3)
#define LCD_Contrast_810VDD                                        (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_0)
#define LCD_Contrast_840VDD                                        (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_1)
#define LCD_Contrast_871VDD                                        (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_1|LCD_CR0_CONTRAST_0)
#define LCD_Contrast_903VDD                                        (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_2)
#define LCD_Contrast_939VDD                                        (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_2|LCD_CR0_CONTRAST_0)
#define LCD_Contrast_969VDD                                        (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_2|LCD_CR0_CONTRAST_1)
#define LCD_Contrast_1000VDD                                       (LCD_CR0_CONTRAST_3|LCD_CR0_CONTRAST_2|LCD_CR0_CONTRAST_1|LCD_CR0_CONTRAST_0)

#define IS_LCD_Contrast(__Contrast__)                         (((__Contrast__) == LCD_Contrast_531VDD) || \
                                                             ((__Contrast__) == LCD_Contrast_562VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_593VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_623VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_654VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_686VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_717VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_748VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_778VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_810VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_840VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_871VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_903VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_939VDD)|| \
                                                             ((__Contrast__) == LCD_Contrast_969VDD)| \
                                                             ((__Contrast__) == LCD_Contrast_1000VDD))


/**
  * @}
  */

#define IS_LCD_PONTime(__PONTime__)                         ((__PONTime__) <= ((uint32_t)0x3F))

/**
  * @}
  */


void HAL_LCD_MspInit(LCD_HandleTypeDef *hlcd);

void HAL_LCD_MspDeInit(LCD_HandleTypeDef *hlcd);

HAL_StatusTypeDef HAL_LCD_Init(LCD_HandleTypeDef *hlcd);

HAL_StatusTypeDef HAL_LCD_DeInit(LCD_HandleTypeDef *hlcd);

HAL_StatusTypeDef HAL_LCD_InResConfig(LCD_HandleTypeDef *hlcd,LCD_InResInitTypeDef* LCD_InResInitStruct);

HAL_StatusTypeDef HAL_LCD_SegComConfig(LCD_HandleTypeDef *hlcd,LCD_SegComInitTypeDef *SegCom);

HAL_StatusTypeDef HAL_LCD_Write(LCD_HandleTypeDef *hlcd, uint32_t LCDRAMIndex, uint32_t Data);

HAL_StatusTypeDef HAL_LCD_Clear(LCD_HandleTypeDef *hlcd);

HAL_StatusTypeDef HAL_LCD_Start_DMA(LCD_HandleTypeDef *hlcd, uint32_t *pData, uint32_t Length);

HAL_StatusTypeDef HAL_LCD_Stop_DMA(LCD_HandleTypeDef *hlcd);

void HAL_LCD_IRQHandler(LCD_HandleTypeDef *hlcd);

#endif
