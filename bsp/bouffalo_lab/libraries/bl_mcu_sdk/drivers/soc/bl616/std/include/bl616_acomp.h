/**
  ******************************************************************************
  * @file    wb03_acomp.h
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
#ifndef __WB03_ACOMP_H__
#define __WB03_ACOMP_H__

#include "aon_reg.h"
#include "bl616_common.h"

/** @addtogroup  BL606P_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ACOMP
 *  @{
 */

/** @defgroup  ACOMP_Public_Types
 *  @{
 */

/**
 *  @brief Analog compare id type definition
 */
typedef enum {
    AON_ACOMP0_ID, /*!< Analog compare 0 */
    AON_ACOMP1_ID, /*!< Analog compare 1 */
} AON_ACOMP_ID_Type;

/**
 *  @brief Analog compare level type definition
 */
typedef enum {
    AON_ACOMP_SCALING_FACTOR_0P25 = 0x00, /*!< Analog compare level scaling factor 0.25 */
    AON_ACOMP_SCALING_FACTOR_0P5 = 0x10,  /*!< Analog compare level scaling factor 0.5 */
    AON_ACOMP_SCALING_FACTOR_0P75 = 0x20, /*!< Analog compare level scaling factor 0.75 */
    AON_ACOMP_SCALING_FACTOR_1 = 0x30,    /*!< Analog compare level scaling factor 1 */
} AON_ACOMP_Scaling_Factor_Type;

/**
 *  @brief Analog compare channel type definition
 */
typedef enum {
    AON_ACOMP_CHAN_ADC0,                   /*!< Analog compare channel,ADC input channel 0 */
    AON_ACOMP_CHAN_ADC1,                   /*!< Analog compare channel,ADC input channel 1 */
    AON_ACOMP_CHAN_ADC2,                   /*!< Analog compare channel,ADC input channel 2 */
    AON_ACOMP_CHAN_ADC3,                   /*!< Analog compare channel,ADC input channel 3 */
    AON_ACOMP_CHAN_ADC4,                   /*!< Analog compare channel,ADC input channel 4 */
    AON_ACOMP_CHAN_ADC5,                   /*!< Analog compare channel,ADC input channel 5 */
    AON_ACOMP_CHAN_ADC6,                   /*!< Analog compare channel,ADC input channel 6 */
    AON_ACOMP_CHAN_ADC7,                   /*!< Analog compare channel,ADC input channel 7 */
    AON_ACOMP_CHAN_DACA,                   /*!< Analog compare channel,DAC output channel A */
    AON_ACOMP_CHAN_DACB,                   /*!< Analog compare channel,DAC output channel B */
    AON_ACOMP_CHAN_VREF_1P25V,             /*!< Analog compare channel,1.25V ref voltage */
    AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_1, /*!< Analog compare channel,first,VIO * scaling factor */
    AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_2, /*!< Analog compare channel,second,VIO * scaling factor */
    AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_3, /*!< Analog compare channel,third,VIO * scaling factor */
    AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_4, /*!< Analog compare channel,forth,VIO * scaling factor */
    AON_ACOMP_CHAN_VSS,                    /*!< Analog compare channel,vss */
} AON_ACOMP_Chan_Type;

/**
 *  @brief Analog compare bias current control type definition
 */
typedef enum {
    AON_ACOMP_BIAS_POWER_MODE1, /*!< Analog compare power mode 1,slow response mode */
    AON_ACOMP_BIAS_POWER_MODE2, /*!< Analog compare power mode 2,medium response mode */
    AON_ACOMP_BIAS_POWER_MODE3, /*!< Analog compare power mode 3,fast response mode */
    AON_ACOMP_BIAS_POWER_NONE,  /*!< Analog compare power mode none */
} AON_ACOMP_Bias_Prog_Type;

/**
 *  @brief Analog compare hysteresis voltage type definition
 */
typedef enum {
    AON_ACOMP_HYSTERESIS_VOLT_NONE, /*!< Analog compare hysteresis voltage none */
    AON_ACOMP_HYSTERESIS_VOLT_10MV, /*!< Analog compare hysteresis voltage 10mv */
    AON_ACOMP_HYSTERESIS_VOLT_20MV, /*!< Analog compare hysteresis voltage 20mv */
    AON_ACOMP_HYSTERESIS_VOLT_30MV, /*!< Analog compare hysteresis voltage 30mv */
    AON_ACOMP_HYSTERESIS_VOLT_40MV, /*!< Analog compare hysteresis voltage 40mv */
    AON_ACOMP_HYSTERESIS_VOLT_50MV, /*!< Analog compare hysteresis voltage 50mv */
    AON_ACOMP_HYSTERESIS_VOLT_60MV, /*!< Analog compare hysteresis voltage 60mv */
    AON_ACOMP_HYSTERESIS_VOLT_70MV, /*!< Analog compare hysteresis voltage 70mv */
} AON_ACOMP_Hysteresis_Volt_Type;

/**
 *  @brief AON ACOMP configuration type definition
 */
typedef struct
{
    BL_Fun_Type muxEn;                                /*!< ACOMP mux enable */
    uint8_t posChanSel;                               /*!< ACOMP positive channel select */
    uint8_t negChanSel;                               /*!< ACOMP negtive channel select */
    uint8_t vioSel;                                   /*!< ACOMP VIO voltage select, (vioSel/66)*avdd33 */
    AON_ACOMP_Scaling_Factor_Type scalingFactor;      /*!< ACOMP scaling factor select factor */
    AON_ACOMP_Bias_Prog_Type biasProg;                /*!< ACOMP bias current control */
    AON_ACOMP_Hysteresis_Volt_Type hysteresisPosVolt; /*!< ACOMP hysteresis voltage for positive */
    AON_ACOMP_Hysteresis_Volt_Type hysteresisNegVolt; /*!< ACOMP hysteresis voltage for negtive */
} AON_ACOMP_CFG_Type;

/*@} end of group ACOMP_Public_Types */

/** @defgroup  ACOMP_Public_Constants
 *  @{
 */

/** @defgroup  AON_ACOMP_ID_TYPE
 *  @{
 */
#define IS_AON_ACOMP_ID_TYPE(type) (((type) == AON_ACOMP0_ID) || \
                                    ((type) == AON_ACOMP1_ID))

/** @defgroup  AON_ACOMP_SCALING_FACTOR_TYPE
 *  @{
 */
#define IS_AON_ACOMP_SCALING_FACTOR_TYPE(type) (((type) == AON_ACOMP_SCALING_FACTOR_0P25) || \
                                                ((type) == AON_ACOMP_SCALING_FACTOR_0P5) ||  \
                                                ((type) == AON_ACOMP_SCALING_FACTOR_0P75) || \
                                                ((type) == AON_ACOMP_SCALING_FACTOR_1))

/** @defgroup  AON_ACOMP_CHAN_TYPE
 *  @{
 */
#define IS_AON_ACOMP_CHAN_TYPE(type) (((type) == AON_ACOMP_CHAN_ADC0) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC1) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC2) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC3) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC4) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC5) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC6) ||                   \
                                      ((type) == AON_ACOMP_CHAN_ADC7) ||                   \
                                      ((type) == AON_ACOMP_CHAN_DACA) ||                   \
                                      ((type) == AON_ACOMP_CHAN_DACB) ||                   \
                                      ((type) == AON_ACOMP_CHAN_VREF_1P25V) ||             \
                                      ((type) == AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_1) || \
                                      ((type) == AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_2) || \
                                      ((type) == AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_3) || \
                                      ((type) == AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_4) || \
                                      ((type) == AON_ACOMP_CHAN_VSS))

/** @defgroup  AON_ACOMP_BIAS_PROG_TYPE
 *  @{
 */
#define IS_AON_ACOMP_BIAS_PROG_TYPE(type) (((type) == AON_ACOMP_BIAS_POWER_MODE1) || \
                                           ((type) == AON_ACOMP_BIAS_POWER_MODE2) || \
                                           ((type) == AON_ACOMP_BIAS_POWER_MODE3) || \
                                           ((type) == AON_ACOMP_BIAS_POWER_NONE))

/** @defgroup  AON_ACOMP_HYSTERESIS_VOLT_TYPE
 *  @{
 */
#define IS_AON_ACOMP_HYSTERESIS_VOLT_TYPE(type) (((type) == AON_ACOMP_HYSTERESIS_VOLT_NONE) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_10MV) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_20MV) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_30MV) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_40MV) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_50MV) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_60MV) || \
                                                 ((type) == AON_ACOMP_HYSTERESIS_VOLT_70MV))

/*@} end of group ACOMP_Public_Constants */

/** @defgroup  ACOMP_Public_Macros
 *  @{
 */

/*@} end of group ACOMP_Public_Macros */

/** @defgroup  ACOMP_Public_Functions
 *  @{
 */
BL_Err_Type AON_ACOMP_Init(AON_ACOMP_ID_Type acompNo, AON_ACOMP_CFG_Type *cfg);
BL_Err_Type AON_ACOMP_Enable(AON_ACOMP_ID_Type acompNo);
BL_Sts_Type AON_ACOMP_Get_Result(AON_ACOMP_ID_Type acompNo);

/*@} end of group ACOMP_Public_Functions */

/*@} end of group ACOMP */

/*@} end of group BL606P_Peripheral_Driver */

#endif /* __BL606P_ACOMP_H__ */
