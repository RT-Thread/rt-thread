/**
  ******************************************************************************
  * @file    bl808_dac.h
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
#ifndef __BL808_DAC_H__
#define __BL808_DAC_H__

#include "aon_reg.h"
#include "glb_reg.h"
#include "gpip_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DAC
 *  @{
 */

/** @defgroup  DAC_Public_Types
 *  @{
 */

/**
 *  @brief DAC reference voltage definition
 */
typedef enum {
    GLB_DAC_REF_SEL_INTERNAL, /*!< DAC reference select internal */
    GLB_DAC_REF_SEL_EXTERNAL, /*!< DAC reference select external */
} GLB_DAC_Ref_Sel_Type;

/**
 *  @brief DAC reference voltage definition
 */
typedef enum {
    GLB_DAC_Output_Volt_0P2_1,       /*!< DAC output voltage is 0.2-1V */
    GLB_DAC_Output_Volt_0P225_1P425, /*!< DAC output voltage is 0.225-1.425V */
    GLB_DAC_Output_Volt_RESEVED,     /*!< DAC output voltage is 0.225-1.425V */
    GLB_DAC_Output_Volt_0P2_1P8,     /*!< DAC output voltage is 0.2-1.8V */
} GLB_DAC_Output_Volt_Range_Type;

/**
 *  @brief DAC channel type definition
 */
typedef enum {
    GLB_DAC_CHAN0,    /*!< DAC channel 0 */
    GLB_DAC_CHAN1,    /*!< DAC channel 1 */
    GLB_DAC_CHAN2,    /*!< DAC channel 2 */
    GLB_DAC_CHAN3,    /*!< DAC channel 3 */
    GLB_DAC_CHAN4,    /*!< DAC channel 4 */
    GLB_DAC_CHAN5,    /*!< DAC channel 5 */
    GLB_DAC_CHAN6,    /*!< DAC channel 6 */
    GLB_DAC_CHAN7,    /*!< DAC channel 7 */
    GLB_DAC_CHAN_ALL, /*!< DAC channel all */
} GLB_DAC_Chan_Type;

/**
 *  @brief DAC channel configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type chanEn;                      /*!< Enable this channel or not */
    BL_Fun_Type outputEn;                    /*!< Output this channel result to PAD */
    GLB_DAC_Chan_Type outMux;                /*!< DAC output mux,NOT implement yet,DAC use fixed GPIO9 and GPIO10 */
    GLB_DAC_Output_Volt_Range_Type outRange; /*!< DAC output voltage range */
} GLB_DAC_Chan_Cfg_Type;

/**
 *  @brief DAC configuration structure type definition
 */
typedef struct
{
    GLB_DAC_Ref_Sel_Type refSel; /*!< DAC reference voltage select */
    BL_Fun_Type resetChanA;      /*!< Reset DAC channel A */
    BL_Fun_Type resetChanB;      /*!< Reset DAC channel B */
} GLB_DAC_Cfg_Type;

/**
 *  @brief DAC channel B source selection type definition
 */
typedef enum {
    GPIP_DAC_ChanB_SRC_REG,             /*!< select Reg as source of DAC channel B */
    GPIP_DAC_ChanB_SRC_DMA,             /*!< select DMA as source of DAC channel B */
    GPIP_DAC_ChanB_SRC_DMA_WITH_FILTER, /*!< select DMA with Filter as source of DAC channel B */
    GPIP_DAC_ChanB_SRC_SIN_GEN,         /*!< select Sin Gen as source of DAC channel B */
    GPIP_DAC_ChanB_SRC_A,               /*!< select channel A as source of DAC channel B */
    GPIP_DAC_ChanB_SRC_INVERSE_A,       /*!< select inverse of channel A as source of DAC channel B */
} GPIP_DAC_ChanB_SRC_Type;

/**
 *  @brief DAC channel A source selection type definition
 */
typedef enum {
    GPIP_DAC_ChanA_SRC_REG,             /*!< select Reg as source of DAC channel A */
    GPIP_DAC_ChanA_SRC_DMA,             /*!< select DMA as source of DAC channel A */
    GPIP_DAC_ChanA_SRC_DMA_WITH_FILTER, /*!< select DMA with Filter as source of DAC channel A */
    GPIP_DAC_ChanA_SRC_SIN_GEN,         /*!< select Sin Gen as source of DAC channel A */
} GPIP_DAC_ChanA_SRC_Type;

/**
 *  @brief DAC clock divider type definition
 */
typedef enum {
    DAC_CLK_DIV_16,      /*!< ADC clock:on 32M clock is 2M */
    DAC_CLK_DIV_32,      /*!< ADC clock:on 32M clock is 1M */
    DAC_CLK_DIV_RESERVE, /*!< reserved */
    DAC_CLK_DIV_64,      /*!< ADC clock:on 32M clock is 0.5M */
    DAC_CLK_DIV_1,       /*!< ADC clock:on 32M clock is 32M */
} DAC_CLK_Type;

/**
 *  @brief DAC DMA TX format selection type definition
 */
typedef enum {
    GPIP_DAC_DMA_FORMAT_0, /*!< {A0},{A1},{A2},... */
    GPIP_DAC_DMA_FORMAT_1, /*!< {B0,A0},{B1,A1},{B2,A2},... */
    GPIP_DAC_DMA_FORMAT_2, /*!< {A1,A0},{A3,A2},{A5,A4},... */
} GPIP_DAC_DMA_TX_FORMAT_Type;

/**
 *  @brief AON and GPIP DAC configuration structure type definition
 */
typedef struct
{
    GLB_DAC_Ref_Sel_Type refSel;        /*!< DAC reference voltage select */
    BL_Fun_Type resetChanA;             /*!< Reset DAC channel A */
    BL_Fun_Type resetChanB;             /*!< Reset DAC channel B */
    DAC_CLK_Type div;                   /*!< DAC clock div */
    BL_Fun_Type dmaEn;                  /*!< DAC DMA transfer enable */
    GPIP_DAC_DMA_TX_FORMAT_Type dmaFmt; /*!< DAC DMA TX format selection */
} GLB_GPIP_DAC_Cfg_Type;

/**
 *  @brief AON and GPIP DAC channel A configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type chanCovtEn;      /*!< Enable this channel conversion or not */
    BL_Fun_Type outputEn;        /*!< Output this channel result to PAD */
    BL_Fun_Type chanEn;          /*!< Enable this channel or not */
    GPIP_DAC_ChanA_SRC_Type src; /*!< DAC channel A source */
} GLB_GPIP_DAC_ChanA_Cfg_Type;

/**
 *  @brief AON and GPIP DAC channel B configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type chanCovtEn;      /*!< Enable this channel conversion or not */
    BL_Fun_Type outputEn;        /*!< Output this channel result to PAD */
    BL_Fun_Type chanEn;          /*!< Enable this channel or not */
    GPIP_DAC_ChanB_SRC_Type src; /*!< DAC channel B source */
} GLB_GPIP_DAC_ChanB_Cfg_Type;

/*@} end of group DAC_Public_Types */

/** @defgroup  DAC_Public_Constants
 *  @{
 */

/** @defgroup  GLB_DAC_REF_SEL_TYPE
 *  @{
 */
#define IS_GLB_DAC_REF_SEL_TYPE(type) (((type) == GLB_DAC_REF_SEL_INTERNAL) || \
                                       ((type) == GLB_DAC_REF_SEL_EXTERNAL))

/** @defgroup  GLB_DAC_OUTPUT_VOLT_RANGE_TYPE
 *  @{
 */
#define IS_GLB_DAC_OUTPUT_VOLT_RANGE_TYPE(type) (((type) == GLB_DAC_Output_Volt_0P2_1) ||       \
                                                 ((type) == GLB_DAC_Output_Volt_0P225_1P425) || \
                                                 ((type) == GLB_DAC_Output_Volt_RESEVED) ||     \
                                                 ((type) == GLB_DAC_Output_Volt_0P2_1P8))

/** @defgroup  GLB_DAC_CHAN_TYPE
 *  @{
 */
#define IS_GLB_DAC_CHAN_TYPE(type) (((type) == GLB_DAC_CHAN0) || \
                                    ((type) == GLB_DAC_CHAN1) || \
                                    ((type) == GLB_DAC_CHAN2) || \
                                    ((type) == GLB_DAC_CHAN3) || \
                                    ((type) == GLB_DAC_CHAN4) || \
                                    ((type) == GLB_DAC_CHAN5) || \
                                    ((type) == GLB_DAC_CHAN6) || \
                                    ((type) == GLB_DAC_CHAN7) || \
                                    ((type) == GLB_DAC_CHAN_ALL))

/** @defgroup  GPIP_DAC_CHANB_SRC_TYPE
 *  @{
 */
#define IS_GPIP_DAC_CHANB_SRC_TYPE(type) (((type) == GPIP_DAC_ChanB_SRC_REG) ||             \
                                          ((type) == GPIP_DAC_ChanB_SRC_DMA) ||             \
                                          ((type) == GPIP_DAC_ChanB_SRC_DMA_WITH_FILTER) || \
                                          ((type) == GPIP_DAC_ChanB_SRC_SIN_GEN) ||         \
                                          ((type) == GPIP_DAC_ChanB_SRC_A) ||               \
                                          ((type) == GPIP_DAC_ChanB_SRC_INVERSE_A))

/** @defgroup  GPIP_DAC_CHANA_SRC_TYPE
 *  @{
 */
#define IS_GPIP_DAC_CHANA_SRC_TYPE(type) (((type) == GPIP_DAC_ChanA_SRC_REG) ||             \
                                          ((type) == GPIP_DAC_ChanA_SRC_DMA) ||             \
                                          ((type) == GPIP_DAC_ChanA_SRC_DMA_WITH_FILTER) || \
                                          ((type) == GPIP_DAC_ChanA_SRC_SIN_GEN))

/** @defgroup  DAC_CLK_TYPE
 *  @{
 */
#define IS_DAC_CLK_TYPE(type) (((type) == DAC_CLK_DIV_16) ||      \
                               ((type) == DAC_CLK_DIV_32) ||      \
                               ((type) == DAC_CLK_DIV_RESERVE) || \
                               ((type) == DAC_CLK_DIV_64) ||      \
                               ((type) == DAC_CLK_DIV_1))

/** @defgroup  GPIP_DAC_DMA_TX_FORMAT_TYPE
 *  @{
 */
#define IS_GPIP_DAC_DMA_TX_FORMAT_TYPE(type) (((type) == GPIP_DAC_DMA_FORMAT_0) || \
                                              ((type) == GPIP_DAC_DMA_FORMAT_1) || \
                                              ((type) == GPIP_DAC_DMA_FORMAT_2))

/*@} end of group DAC_Public_Constants */

/** @defgroup  DAC_Public_Macros
 *  @{
 */

/*@} end of group DAC_Public_Macros */

/** @defgroup  DAC_Public_Functions
 *  @{
 */
void GLB_DAC_Init(GLB_DAC_Cfg_Type *cfg);
void GLB_DAC_Set_ChanA_Config(GLB_DAC_Chan_Cfg_Type *cfg);
void GLB_DAC_Set_ChanB_Config(GLB_DAC_Chan_Cfg_Type *cfg);
void GPIP_Set_DAC_ChanB_SRC_SEL(GPIP_DAC_ChanB_SRC_Type src);
void GPIP_Set_DAC_ChanA_SRC_SEL(GPIP_DAC_ChanA_SRC_Type src);
void GPIP_DAC_ChanB_Enable(void);
void GPIP_DAC_ChanB_Disable(void);
void GPIP_DAC_ChanA_Enable(void);
void GPIP_DAC_ChanA_Disable(void);
void GPIP_Set_DAC_DMA_TX_FORMAT_SEL(GPIP_DAC_DMA_TX_FORMAT_Type fmt);
void GPIP_Set_DAC_DMA_TX_Enable(void);
void GPIP_Set_DAC_DMA_TX_Disable(void);
void GPIP_DAC_DMA_WriteData(uint32_t data);
BL_Err_Type GLB_GPIP_DAC_Init(GLB_GPIP_DAC_Cfg_Type *cfg);
void GLB_GPIP_DAC_Set_ChanA_Config(GLB_GPIP_DAC_ChanA_Cfg_Type *cfg);
void GLB_GPIP_DAC_Set_ChanB_Config(GLB_GPIP_DAC_ChanB_Cfg_Type *cfg);
void GLB_DAC_Set_ChanA_Value(uint16_t val);
void GLB_DAC_Set_ChanB_Value(uint16_t val);

/*@} end of group DAC_Public_Functions */

/*@} end of group DAC */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DAC_H__ */
