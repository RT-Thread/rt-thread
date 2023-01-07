/**
  ******************************************************************************
  * @file    bl808_audiopdm.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_AUDIOPDM_H__
#define __BL808_AUDIOPDM_H__

#include "pdm_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AUDIOPDM
 *  @{
 */

/** @defgroup  AUDIOPDM_Public_Types
 *  @{
 */

/**
 *  @brief Aupdm ADC ID
 */
typedef enum {
    AUPDM_ADC_0, /*!< Aupdm ADC 0 */
    AUPDM_ADC_1, /*!< Aupdm ADC 1 */
    AUPDM_ADC_2, /*!< Aupdm ADC 2 */
} Aupdm_ADC_ID_Type;

/**
 *  @brief Aupdm PDM ADC Clock
 */
typedef enum {
    AUPDM_PDM_ADC_8_KHZ,  /*!< Aupdm PDM ADC Clock set as 8KHZ */
    AUPDM_PDM_ADC_16_KHZ, /*!< Aupdm PDM ADC Clock set as 16KHZ */
    AUPDM_PDM_ADC_24_KHZ, /*!< Aupdm PDM ADC Clock set as 24KHZ */
    AUPDM_PDM_ADC_32_KHZ, /*!< Aupdm PDM ADC Clock set as 32KHZ */
    AUPDM_PDM_ADC_48_KHZ, /*!< Aupdm PDM ADC Clock set as 48KHZ */
    AUPDM_PDM_ADC_96_KHZ, /*!< Aupdm PDM ADC Clock set as 96KHZ */
} Aupdm_ADC_Clock_Type;

/**
 *  @brief Aupdm PDM ID
 */
typedef enum {
    AUPDM_PDM_0, /*!< select PDM Channel 0 */
    AUPDM_PDM_1, /*!< select PDM Channel 1 */
    AUPDM_PDM_2, /*!< select PDM Channel 2 */
} Aupdm_PDM_ID_Type;

/**
 *  @brief Aupdm PDM Source Select
 */
typedef enum {
    AUPDM_PDM_0_L, /*!< select PDM0 Left  Channel */
    AUPDM_PDM_0_R, /*!< select PDM0 Right Channel */
    AUPDM_PDM_1_L, /*!< select PDM1 Left  Channel */
    AUPDM_PDM_1_R, /*!< select PDM1 Right Channel */
    AUPDM_PDM_2_L, /*!< select PDM2 Left  Channel */
    AUPDM_PDM_2_R, /*!< select PDM2 Right Channel */
} Aupdm_PDM_Source_Type;

/**
 *  @brief Aupdm Resolution
 */
typedef enum {
    AUPDM_RES_16_BITS, /*!< select ADC Resolution as 16 bit */
    AUPDM_RES_20_BITS, /*!< select ADC Resolution as 20 bit */
} Aupdm_Resolution_Type;

/**
 *  @brief Aupdm Resolution
 */
typedef enum {
    AUPDM_FIFO_AILGN_MSB_AT_BIT31, /*!< Mode 0: Valid data's MSB is at [31] of FIFO register */
    AUPDM_FIFO_AILGN_MSB_AT_BIT23, /*!< Mode 1: Valid data's MSB is at [23] of FIFO register */
    AUPDM_FIFO_AILGN_MSB_AT_BIT19, /*!< Mode 2: Valid data's MSB is at [19] of FIFO register */
    AUPDM_FIFO_AILGN_MSB_AT_BIT15, /*!< Mode 3: Valid data's MSB is at [15] of FIFO register */
} Aupdm_FIFO_Ailgn_Mode;

/**
 *  @brief Aupdm Resolution
 */
typedef enum {
    AUPDM_DRQ_EQUEL_TO_IRQ,       /*!< DMA request threhold is equeal to Interrupt threhold */
    AUPDM_DRQ_THR_AS_4_TX_8_RX,   /*!< DMA request threhold is 4 when config TX FIFO DRQ , 8 when config RX FIFO */
    AUPDM_DRQ_THR_AS_8_TX_16_RX,  /*!< DMA request threhold is 8 when config TX FIFO DRQ , 16 when config RX FIFO */
    AUPDM_DRQ_THR_AS_16_TX_32_RX, /*!< DMA request threhold is 16 when config TX FIFO DRQ , 32 when config RX FIFO */
} Aupdm_FIFO_DQR_Threshold_Mode;

/**
 *  @brief Aupdm initerrupt type
 */
typedef enum {
    AUPDM_INT_RX_FIFO_THR,      /*!< Aupdm RX FIFO counter upper than threhold interrupt */
    AUPDM_INT_RX_FIFO_OVERRUN,  /*!< Aupdm RX FIFO overrun */
    AUPDM_INT_RX_FIFO_UNDERRUN, /*!< Aupdm RX FIFO underrun */
    AUPDM_INT_NUM_ALL,          /*!< Aupdm int all */
} Aupdm_INT_Type;

/**
 *  @brief Aupdm PDM Clock Configuration
 */
typedef struct {
    Aupdm_ADC_Clock_Type adc_clock; /*!< ADC Rate Configuration */
    BL_Fun_Type pdm_clk_inv;        /*!< enable or not pdm clock inv */
    BL_Fun_Type adc_clk_inv;        /*!< enable or not adc clock inv */
} Aupdm_Clock_CFG_Type;

/**
 *  @brief Aupdm FIFO Configuration
 */
typedef struct {
    Aupdm_Resolution_Type resolution;               /*!< Receiving Aupdm Sample Resolution */
    Aupdm_FIFO_Ailgn_Mode ailgnMode;                /*!< FIFO alignMode */
    uint8_t FifoIntThreshold;                       /*!< FIFO IRQ Threshold */
    Aupdm_FIFO_DQR_Threshold_Mode dmaThresholdMode; /*!< FIFO DRQ Threshold mode */
    BL_Fun_Type dmaEn;                              /*!< enable DMA FIFO interface */
} Aupdm_FifoCfg_Type;

/*@} end of group AUDIOPDM_Public_Types */

/** @defgroup  AUDIOPDM_Public_Constants
 *  @{
 */

/** @defgroup  AUPDM_ADC_ID_TYPE
 *  @{
 */
#define IS_AUPDM_ADC_ID_TYPE(type) (((type) == AUPDM_ADC_0) || \
                                    ((type) == AUPDM_ADC_1) || \
                                    ((type) == AUPDM_ADC_2))

/** @defgroup  AUPDM_ADC_CLOCK_TYPE
 *  @{
 */
#define IS_AUPDM_ADC_CLOCK_TYPE(type) (((type) == AUPDM_PDM_ADC_8_KHZ) ||  \
                                       ((type) == AUPDM_PDM_ADC_16_KHZ) || \
                                       ((type) == AUPDM_PDM_ADC_24_KHZ) || \
                                       ((type) == AUPDM_PDM_ADC_32_KHZ) || \
                                       ((type) == AUPDM_PDM_ADC_48_KHZ) || \
                                       ((type) == AUPDM_PDM_ADC_96_KHZ))

/** @defgroup  AUPDM_PDM_ID_TYPE
 *  @{
 */
#define IS_AUPDM_PDM_ID_TYPE(type) (((type) == AUPDM_PDM_0) || \
                                    ((type) == AUPDM_PDM_1) || \
                                    ((type) == AUPDM_PDM_2))

/** @defgroup  AUPDM_PDM_SOURCE_TYPE
 *  @{
 */
#define IS_AUPDM_PDM_SOURCE_TYPE(type) (((type) == AUPDM_PDM_0_L) || \
                                        ((type) == AUPDM_PDM_0_R) || \
                                        ((type) == AUPDM_PDM_1_L) || \
                                        ((type) == AUPDM_PDM_1_R) || \
                                        ((type) == AUPDM_PDM_2_L) || \
                                        ((type) == AUPDM_PDM_2_R))

/** @defgroup  AUPDM_RESOLUTION_TYPE
 *  @{
 */
#define IS_AUPDM_RESOLUTION_TYPE(type) (((type) == AUDIO_RES_16_BITS) || \
                                        ((type) == AUDIO_RES_20_BITS))

/** @defgroup  AUPDM_FIFO_AILGN_MODE
 *  @{
 */
#define IS_AUPDM_FIFO_AILGN_MODE(type) (((type) == AUPDM_FIFO_AILGN_MSB_AT_BIT31) || \
                                        ((type) == AUPDM_FIFO_AILGN_MSB_AT_BIT23) || \
                                        ((type) == AUPDM_FIFO_AILGN_MSB_AT_BIT19) || \
                                        ((type) == AUPDM_FIFO_AILGN_MSB_AT_BIT15))

/** @defgroup  AUPDM_FIFO_DQR_THRESHOLD_MODE
 *  @{
 */
#define IS_AUPDM_FIFO_DQR_THRESHOLD_MODE(type) (((type) == AUPDM_DRQ_EQUEL_TO_IRQ) ||      \
                                                ((type) == AUPDM_DRQ_THR_AS_4_TX_8_RX) ||  \
                                                ((type) == AUPDM_DRQ_THR_AS_8_TX_16_RX) || \
                                                ((type) == AUPDM_DRQ_THR_AS_16_TX_32_RX))

/** @defgroup  AUPDM_INT_TYPE
 *  @{
 */
#define IS_AUPDM_INT_TYPE(type) (((type) == AUPDM_INT_RX_FIFO_THR) ||      \
                                 ((type) == AUPDM_INT_RX_FIFO_OVERRUN) ||  \
                                 ((type) == AUPDM_INT_RX_FIFO_UNDERRUN) || \
                                 ((type) == AUPDM_INT_NUM_ALL))

/*@} end of group AUDIOPDM_Public_Constants */

/** @defgroup  AUDIOPDM_Public_Macros
 *  @{
 */
#define AUDIO_PRIVATE_BIT_POS(n)  (0x01 << n)
#define ADC1_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(0)
#define ADC2_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(1)
#define ADC3_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(2)

/*@} end of group AUDIOPDM_Public_Macros */

/** @defgroup  AUDIOPDM_Public_Functions
 *  @{
 */
void Aupdm_IntMask(Aupdm_INT_Type intType, BL_Mask_Type intMask);
BL_Sts_Type Aupdm_GetIntStatus(Aupdm_INT_Type intType);
void Aupdm_IntClear(Aupdm_INT_Type intType);
void Aupdm_Clock_Init(Aupdm_Clock_CFG_Type *cfg);
void Aupdm_PDM_Channel_Sel(Aupdm_PDM_ID_Type id, Aupdm_PDM_Source_Type pdmSel);
void Aupdm_PDM_Enable(Aupdm_PDM_ID_Type id);
BL_Err_Type Aupdm_Int_Callback_Install(Aupdm_INT_Type intType, intCallback_Type *cbFun);
void Aupdm_RxFifoClear(void);
uint32_t Aupdm_GetRxFifoCount(void);
uint32_t Aupdm_ReadRxFifo(void);
void Aupdm_RxFifoConfig(Aupdm_FifoCfg_Type *cfg);
void Aupdm_RxFifoEnable(uint8_t ch);
void Aupdm_RxFifoDisable(uint8_t ch);
BL_Err_Type Aupdm_Rx_Source_ADC_Sel(uint8_t rx_channel, Aupdm_ADC_ID_Type adc_id);
void Aupdm_ADC_Enable(Aupdm_ADC_ID_Type id);
void Aupdm_ADC_Disable(Aupdm_ADC_ID_Type id);
void Aupdm_Set_ADC_Scaling_Value(Aupdm_ADC_ID_Type id, uint8_t scalingVal);
void Aupdm_Set_Fir_Mode(Aupdm_ADC_ID_Type id, uint8_t enable);
void Aupdm_Set_HPF_Parameter(Aupdm_ADC_ID_Type id, uint8_t k1_enable, uint8_t k1, uint8_t k2_enable, uint8_t k2);
void Aupdm_ADC_PDM_Inv_Swap(Aupdm_ADC_ID_Type id, uint8_t swap);
void Audio_ADC_Set_PDM_Value(uint8_t pdm_l, uint8_t pdm_h);
BL_Err_Type Aupdm_ADC_Volume_Config(Aupdm_ADC_ID_Type adc_id, uint8_t volume);
/*@} end of group AUDIOPDM_Public_Functions */

/*@} end of group AUDIOPDM */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_AUDIOPDM_H__ */
