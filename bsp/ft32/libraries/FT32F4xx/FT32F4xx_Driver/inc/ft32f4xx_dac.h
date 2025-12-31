/**
  ******************************************************************************
  * @file               ft32f4xx_dac.h
  * @author             FMD xzhang
  * @brief              This file contains all the functions prototypes for the DAC
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-26
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_DAC_H
#define __FT32F4XX_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"
/* Exported types ------------------------------------------------------------*/
/** @defgroup dac Exported_Types dac Exported Types
  * @{
  */
/**
  * @brief  DAC Init structure definition
  */
typedef struct
{

    uint32_t DAC_Trigger;         /*!< Select the DAC trigger source from Timer or Exti.
                                    This parameter can be a value of @ref DAC_Trigger */
    uint32_t DAC_OutputBuffer;    /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                    This parameter can be a value of @ref DAC_OutputBuffer */
    uint32_t DAC_Input_sel;        /*!< Select the DAC input source.
                                    This parameter can be a value of @ref DAC_Input_sel */

    uint32_t DAC_Output_sel;        /*!< Select the DAC output pins.
                                    This parameter can be a value of @ref DAC_Output_sel*/

} DAC_InitTypeDef;



/** @defgroup DAC_1_2_Selection
  * @{DAC1 ,DAC2 ,DAC12( dac double)
  */
#define DAC_CHANNEL_1             ((uint32_t)0x00000000) /*!< DAC1 Selection */
#define DAC_CHANNEL_2             ((uint32_t)0x00000010) /*!< DAC2 Selection */
#define DAC_CHANNEL_D12           ((uint32_t)0x00000011) /*!< DAC double Selection */

#define IS_DAC_1_2_PERIPH(PERIPH) (((PERIPH) == DAC_CHANNEL_1) || \
                                    ((PERIPH) == DAC_CHANNEL_2) || \
                                    ((PERIPH) == DAC_CHANNEL_D12))


/** @defgroup Alignment  DAC_data_alignment
  * @{
  */
#define DAC_ALIGN_12B_R                    0x00000000U
#define DAC_ALIGN_12B_L                    0x00000004U
#define DAC_ALIGN_8B_R                     0x00000008U

#define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_ALIGN_12B_R) || \
                             ((ALIGN) == DAC_ALIGN_12B_L) || \
                             ((ALIGN) == DAC_ALIGN_8B_R))


/** @defgroup DAC_Trigger   DAC trigger selection
  * @{  DAC1 and DAC2
  */
#define DAC_TRIGGER_NONE                0x00000000UL                       /*!< Conversion is automatic once the DAC1_DHRxxxx register has been loaded, and not by external trigger */
#define DAC_TRIGGER_T2_TRGO             (TSEL1_2                    | TEN1) /*!< TIM2 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T4_TRGO             (TSEL1_2          | TSEL1_0 | TEN1) /*!< TIM4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T5_TRGO             (         TSEL1_1 | TSEL1_0 | TEN1) /*!< TIM3 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T6_TRGO             (                             TEN1) /*!< Conversion started by software trigger for DAC channel */
#define DAC_TRIGGER_T7_TRGO             (         TSEL1_1           | TEN1) /*!< TIM7 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T8_TRGO             (                   TSEL1_0 | TEN1) /*!< TIM8 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_EXT_IT9             (TSEL1_2 | TSEL1_1          | TEN1) /*!< EXTI Line9 event selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_SOFTWARE            (DAC_CR_TSEL1_Msk           | TEN1) /*!< Conversion started by software trigger for DAC channel */

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_TRIGGER_NONE)    || \
                                 ((TRIGGER) == DAC_TRIGGER_T2_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T8_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T7_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T5_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T6_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_T4_TRGO) || \
                                 ((TRIGGER) == DAC_TRIGGER_EXT_IT9) || \
                                 ((TRIGGER) == DAC_TRIGGER_SOFTWARE))


/** @defgroup amplitude  :DACEx_triangle_amplitude DACEx lfsrunmask triangle amplitude
  * @{
  */
#define DAC_LFSRUNMASK_BIT0          0x00000000UL                          /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUNMASK_BITS1_0       (                            MAMP1_0) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS2_0       (                  MAMP1_1          ) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS3_0       (                  MAMP1_1 | MAMP1_0) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS4_0       (        MAMP1_2                    ) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS5_0       (        MAMP1_2           | MAMP1_0) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS6_0       (        MAMP1_2 | MAMP1_1          ) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS7_0       (        MAMP1_2 | MAMP1_1 | MAMP1_0) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS8_0       (MAMP1_3                            ) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS9_0       (MAMP1_3                   | MAMP1_0) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS10_0      (MAMP1_3         | MAMP1_1          ) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS11_0      (MAMP1_3         | MAMP1_1 | MAMP1_0) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TRIANGLEAMPLITUDE_1      0x00000000UL                           /*!< Select max triangle amplitude of 1 */
#define DAC_TRIANGLEAMPLITUDE_3      (                             MAMP1_0) /*!< Select max triangle amplitude of 3 */
#define DAC_TRIANGLEAMPLITUDE_7      (                   MAMP1_1          ) /*!< Select max triangle amplitude of 7 */
#define DAC_TRIANGLEAMPLITUDE_15     (                   MAMP1_1 | MAMP1_0) /*!< Select max triangle amplitude of 15 */
#define DAC_TRIANGLEAMPLITUDE_31     (         MAMP1_2                    ) /*!< Select max triangle amplitude of 31 */
#define DAC_TRIANGLEAMPLITUDE_63     (         MAMP1_2           | MAMP1_0) /*!< Select max triangle amplitude of 63 */
#define DAC_TRIANGLEAMPLITUDE_127    (         MAMP1_2 | MAMP1_1          ) /*!< Select max triangle amplitude of 127 */
#define DAC_TRIANGLEAMPLITUDE_255    (         MAMP1_2 | MAMP1_1 | MAMP1_0) /*!< Select max triangle amplitude of 255 */
#define DAC_TRIANGLEAMPLITUDE_511    (MAMP1_3                             ) /*!< Select max triangle amplitude of 511 */
#define DAC_TRIANGLEAMPLITUDE_1023   (MAMP1_3                    | MAMP1_0) /*!< Select max triangle amplitude of 1023 */
#define DAC_TRIANGLEAMPLITUDE_2047   (MAMP1_3          | MAMP1_1          ) /*!< Select max triangle amplitude of 2047 */
#define DAC_TRIANGLEAMPLITUDE_4095   (MAMP1_3          | MAMP1_1 | MAMP1_0) /*!< Select max triangle amplitude of 4095 */



#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUNMASK_BIT0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS1_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS2_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS3_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS4_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS5_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS6_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS7_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS8_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS9_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS10_0) || \
                                                      ((VALUE) == DAC_LFSRUNMASK_BITS11_0) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_1) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_3) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_7) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_15) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_31) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_63) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_127) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_255) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_511) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_1023) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_2047) || \
                                                      ((VALUE) == DAC_TRIANGLEAMPLITUDE_4095))

/** @defgroup DAC_OutputBuffer
  * @{
  */
#define DAC_OUTPUTBUFFER_ENABLE            0x00000002U
#define DAC_OUTPUTBUFFER_DISABLE           0x00000000U

#define IS_DAC_BUFFER(BUFFER)             (((BUFFER) == DAC_OUTPUTBUFFER_ENABLE)|| \
                                                                ( (BUFFER) == DAC_OUTPUTBUFFER_DISABLE))


/** @defgroup DAC_Input_sel
  * @{
  */
#define DAC_INPUT_SEL_DOR                 0x00000000U
#define DAC_INPUT_SEL_RAMP                0x00004000U


#define IS_DAC_INPUT(input) (((INPUT) ==DAC_INPUT_SEL_DOR ) || \
                             ((INPUT) == DAC_INPUT_SEL_RAMP))


/** @defgroup DAC_Output_sel
  * @{
  */
#define DAC_OUTPUT_SEL_PAD                 0x00000000U
#define DAC_OUTPUT_SEL_Analog              0x00008000U

#define IS_DAC_OUTPUT(output) (((output) == DAC_OUTPUT_SEL_PAD) || \
                             ((output) == DAC_OUTPUT_SEL_Analog))


/* Initialization and Configuration functions *********************************/
void DAC_Init(uint32_t DAC_1_2_Selection, DAC_InitTypeDef* DAC_InitStruct);
void DAC_DeInit(uint32_t DAC_1_2_Selection);
void DAC_Start(uint32_t DAC_1_2_Selection);
void DAC_STOP(uint32_t DAC_1_2_Selection);
/*  Function used to set the  DAC configuration to the default reset state ****/
void DAC_SetValue(uint32_t DAC_1_2_Selection, uint32_t Alignment, uint32_t Data);
uint32_t DAC_GetValue(uint32_t DAC_1_2_Selection);
void DAC_Start_DMA(uint32_t DAC_1_2_Selection, FunctionalState NewState);
void DAC_Stop_DMA(uint32_t DAC_1_2_Selection);
void DAC_TriangleWaveGenerate(uint32_t DAC_1_2_Selection, uint32_t Amplitude);
void DAC_NoiseWaveGenerate(uint32_t DAC_1_2_Selection, uint32_t Amplitude);
void Delay_read (void) ;

#ifdef __cplusplus
}
#endif

#endif /*__ft32f4XX_DAC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
