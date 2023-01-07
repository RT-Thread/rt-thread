/**
  ******************************************************************************
  * @file    bl808_touch.h
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
#ifndef __BL808_TOUCH_H__
#define __BL808_TOUCH_H__

#include "pds_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TOUCH
 *  @{
 */

/** @defgroup  TOUCH_Public_Types
 *  @{
 */

/**
 *  @brief TOUCH ID type definition
 */
typedef enum {
    TOUCH_ID_0, /*!< TOUCH ID 0 */
} TOUCH_ID_Type;

/**
 *  @brief TOUCH run mode select type definition
 */
typedef enum {
    TOUCH_RUN_MODE_SINGLE_SHOT, /*!< TOUCH run in single shot mode */
    TOUCH_RUN_MODE_CONTINUE,    /*!< TOUCH run in continue mode */
} TOUCH_RUN_MODE_Type;

/**
 *  @brief TOUCH pcharge low type definition
 */
typedef enum {
    TOUCH_PCHARGE_LOW_127,  /*!< for one channel, the max external cap leakage cycle is 127 */
    TOUCH_PCHARGE_LOW_255,  /*!< for one channel, the max external cap leakage cycle is 255 */
    TOUCH_PCHARGE_LOW_511,  /*!< for one channel, the max external cap leakage cycle is 511 */
    TOUCH_PCHARGE_LOW_1023, /*!< for one channel, the max external cap leakage cycle is 1023 */
    TOUCH_PCHARGE_LOW_2047, /*!< for one channel, the max external cap leakage cycle is 2047 */
    TOUCH_PCHARGE_LOW_4095, /*!< for one channel, the max external cap leakage cycle is 4095 */
} TOUCH_PCHARGE_LOW_Type;

/**
 *  @brief TOUCH pcharge high type definition
 */
typedef enum {
    TOUCH_PCHARGE_HIGH_511,   /*!< for one channel, the max external cap charge-transfer cycle is 511 */
    TOUCH_PCHARGE_HIGH_1023,  /*!< for one channel, the max external cap charge-transfer cycle is 1023 */
    TOUCH_PCHARGE_HIGH_2047,  /*!< for one channel, the max external cap charge-transfer cycle is 2047 */
    TOUCH_PCHARGE_HIGH_4095,  /*!< for one channel, the max external cap charge-transfer cycle is 4095 */
    TOUCH_PCHARGE_HIGH_8191,  /*!< for one channel, the max external cap charge-transfer cycle is 8191 */
    TOUCH_PCHARGE_HIGH_16383, /*!< for one channel, the max external cap charge-transfer cycle is 16383 */
    TOUCH_PCHARGE_HIGH_32767, /*!< for one channel, the max external cap charge-transfer cycle is 32767 */
    TOUCH_PCHARGE_HIGH_65535, /*!< for one channel, the max external cap charge-transfer cycle is 65535 */
} TOUCH_PCHARGE_HIGH_Type;

/**
 *  @brief TOUCH clock divider type definition
 */
typedef enum {
    TOUCH_CLK_DIV_1,   /*!< TOUCH clock div 1 */
    TOUCH_CLK_DIV_2,   /*!< TOUCH clock div 2 */
    TOUCH_CLK_DIV_4,   /*!< TOUCH clock div 4 */
    TOUCH_CLK_DIV_8,   /*!< TOUCH clock div 8 */
    TOUCH_CLK_DIV_16,  /*!< TOUCH clock div 16 */
    TOUCH_CLK_DIV_32,  /*!< TOUCH clock div 32 */
    TOUCH_CLK_DIV_64,  /*!< TOUCH clock div 64 */
    TOUCH_CLK_DIV_128, /*!< TOUCH clock div 128 */
} TOUCH_CLK_DIV_Type;

/**
 *  @brief TOUCH clock source select type definition
 */
typedef enum {
    TOUCH_CLK_SEL_32K, /*!< select 32K as TOUCH clock */
    TOUCH_CLK_SEL_32M, /*!< select 32M as TOUCH clock */
} TOUCH_CLK_SEL_Type;

/**
 *  @brief TOUCH current source select type definition
 */
typedef enum {
    TOUCH_POWER_SEL_AON,         /*!< select touch current from AON bandgap,power up touch current in rf707_aon */
    TOUCH_POWER_SEL_INTERNAL_BG, /*!< select touch current from internal bandgap,power off touch current in rf707_aon */
} TOUCH_POWER_SEL_Type;

/**
 *  @brief TOUCH comparator hystersis voltage type definition
 */
typedef enum {
    TOUCH_HYSTERSIS_VOLTAGE_30mV, /*!< set 30mV comparator hystersis voltage */
    TOUCH_HYSTERSIS_VOLTAGE_80mV, /*!< set 80mV comparator hystersis voltage */
} TOUCH_HYSTERSIS_VOLTAGE_Type;

/**
 *  @brief TOUCH LDO voltage control type definition
 */
typedef enum {
    TOUCH_LDO_VOLTAGE_0P6V, /*!< LDO output 0.6V */
    TOUCH_LDO_VOLTAGE_0P8V, /*!< LDO output 0.8V */
    TOUCH_LDO_VOLTAGE_1P0V, /*!< LDO output 1.0V */
    TOUCH_LDO_VOLTAGE_1P2V, /*!< LDO output 1.2V */
    TOUCH_LDO_VOLTAGE_1P4V, /*!< LDO output 1.4V */
    TOUCH_LDO_VOLTAGE_1P6V, /*!< LDO output 1.6V */
    TOUCH_LDO_VOLTAGE_1P8V, /*!< LDO output 1.8V */
    TOUCH_LDO_VOLTAGE_2P0V, /*!< LDO output 2.0V */
} TOUCH_LDO_VOLTAGE_Type;

/**
 *  @brief TOUCH reference voltage control type definition
 */
typedef enum {
    TOUCH_VREF_VOLTAGE_0P4V, /*!< LDO output 0.4V */
    TOUCH_VREF_VOLTAGE_0P6V, /*!< LDO output 0.6V */
    TOUCH_VREF_VOLTAGE_0P8V, /*!< LDO output 0.8V */
    TOUCH_VREF_VOLTAGE_1P0V, /*!< LDO output 1.0V */
    TOUCH_VREF_VOLTAGE_1P2V, /*!< LDO output 1.2V */
    TOUCH_VREF_VOLTAGE_1P4V, /*!< LDO output 1.4V */
    TOUCH_VREF_VOLTAGE_1P6V, /*!< LDO output 1.6V */
    TOUCH_VREF_VOLTAGE_1P8V, /*!< LDO output 1.8V */
} TOUCH_VREF_VOLTAGE_Type;

/**
 *  @brief TOUCH compensation cap control type definition
 */
typedef enum {
    TOUCH_COMPENSATION_CAP_12pF, /*!< compensation cap is 12pF */
    TOUCH_COMPENSATION_CAP_13pF, /*!< compensation cap is 13pF */
    TOUCH_COMPENSATION_CAP_14pF, /*!< compensation cap is 14pF */
    TOUCH_COMPENSATION_CAP_15pF, /*!< compensation cap is 15pF */
} TOUCH_COMPENSATION_CAP_Type;

/**
 *  @brief TOUCH mode select type definition
 */
typedef enum {
    TOUCH_WORK_MODE_SELF_CAP, /*!< self cap mode,each channel detection result can judge if this channel is touched */
    TOUCH_WORK_MODE_MUTUAL,   /*!< mutual mode,channel 6~0 works,higher 3 channel-->column,lower 4 channel-->row */
} TOUCH_WORK_MODE_Type;

/**
 *  @brief TOUCH filter long time average order control,FLT(new)=(data_raw+FLT(former)*(2^N-1))/2^N
 */
typedef enum {
    TOUCH_FILTER_ORDER_CTRL_0, /*!< N=0 (acted like disable actually) */
    TOUCH_FILTER_ORDER_CTRL_1, /*!< N=1 */
    TOUCH_FILTER_ORDER_CTRL_2, /*!< N=2 */
    TOUCH_FILTER_ORDER_CTRL_3, /*!< N=3 */
    TOUCH_FILTER_ORDER_CTRL_4, /*!< N=4 */
    TOUCH_FILTER_ORDER_CTRL_5, /*!< N=5 */
    TOUCH_FILTER_ORDER_CTRL_6, /*!< N=6 */
    TOUCH_FILTER_ORDER_CTRL_7, /*!< N=7 */
} TOUCH_FILTER_ORDER_CTRL_Type;

/**
 *  @brief TOUCH LTA long time average order control,LTA(new)=(data_raw+LTA(former)*(2^N-1))/2^N
 */
typedef enum {
    TOUCH_LTA_ORDER_CTRL_0, /*!< N=0 (acted like disable actually) */
    TOUCH_LTA_ORDER_CTRL_1, /*!< N=1 */
    TOUCH_LTA_ORDER_CTRL_2, /*!< N=2 */
    TOUCH_LTA_ORDER_CTRL_3, /*!< N=3 */
    TOUCH_LTA_ORDER_CTRL_4, /*!< N=4 */
    TOUCH_LTA_ORDER_CTRL_5, /*!< N=5 */
    TOUCH_LTA_ORDER_CTRL_6, /*!< N=6 */
    TOUCH_LTA_ORDER_CTRL_7, /*!< N=7 */
} TOUCH_LTA_ORDER_CTRL_Type;

/**
 *  @brief TOUCH configuration type definition
 */
typedef struct
{
    TOUCH_CLK_SEL_Type clkSel;                   /*!< TOUCH clock source select */
    TOUCH_CLK_DIV_Type clkDiv;                   /*!< TOUCH clock divider */
    TOUCH_POWER_SEL_Type powerSel;               /*!< TOUCH power source select */
    BL_Fun_Type calibrationEn;                   /*!< touch_channel calibration option, when enable,the counting number will be set as LTA data */
    TOUCH_WORK_MODE_Type workMode;               /*!< touch_channel work mode select */
    TOUCH_RUN_MODE_Type runMode;                 /*!< 0-->single shot mode, 1-->continous mode */
    BL_Fun_Type ulpEn;                           /*!< ultra low power mode enable */
    BL_Fun_Type cycleEn;                         /*!< configure for low power mode with single shot, sleep for a time and then turn on */
    uint32_t sleepTime;                          /*!< Sleep clock_ana cycle, can save power by reduce turn on time */
    TOUCH_PCHARGE_LOW_Type pchargeLow;           /*!< the max external cap leakage cycle */
    TOUCH_PCHARGE_HIGH_Type pchargeHigh;         /*!< the max external cap charge-transfer cycle */
    TOUCH_LDO_VOLTAGE_Type ldoVol;               /*!< TOUCH LDO voltage */
    TOUCH_VREF_VOLTAGE_Type vrefVol;             /*!< TOUCH reference voltage control */
    TOUCH_HYSTERSIS_VOLTAGE_Type hystersisVol;   /*!< TOUCH comparator hystersis voltage */
    TOUCH_COMPENSATION_CAP_Type compensationCap; /*!< TOUCH compensation cap control */
    BL_Fun_Type filterEn;                        /*!< touch_channel output data filter control, will do average(low pass filter) when enable */
    TOUCH_FILTER_ORDER_CTRL_Type filterCtrl;     /*!< TOUCH filter long time average order control */
    BL_Fun_Type ltaEn;                           /*!< touch_channel long time average control, will do average(low pass filter) when enable */
    TOUCH_LTA_ORDER_CTRL_Type ltaCtrl;           /*!< TOUCH LTA long time average order control */
    BL_Fun_Type dataHystersisEn;                 /*!< touch_channel hystersis data for touch action judgement, can reduce the false trigger */
    uint16_t dataHysCtrl;                        /*!< Hystersis data for data and dectection judgement */
} TOUCH_CFG_Type;

/**
 *  @brief TOUCH channel type definition
 */
typedef enum {
    TOUCH_CHANNEL_0,  /*!< TOUCH channel 0 */
    TOUCH_CHANNEL_1,  /*!< TOUCH channel 1 */
    TOUCH_CHANNEL_2,  /*!< TOUCH channel 2 */
    TOUCH_CHANNEL_3,  /*!< TOUCH channel 3 */
    TOUCH_CHANNEL_4,  /*!< TOUCH channel 4 */
    TOUCH_CHANNEL_5,  /*!< TOUCH channel 5 */
    TOUCH_CHANNEL_6,  /*!< TOUCH channel 6 */
    TOUCH_CHANNEL_7,  /*!< TOUCH channel 7 */
    TOUCH_CHANNEL_8,  /*!< TOUCH channel 8 */
    TOUCH_CHANNEL_9,  /*!< TOUCH channel 9 */
    TOUCH_CHANNEL_10, /*!< TOUCH channel 10 */
    TOUCH_CHANNEL_11, /*!< TOUCH channel 11 */
} TOUCH_CHANNEL_Type;

/**
 *  @brief TOUCH channel config type definition
 */
typedef enum {
    TOUCH_CHANNEL_HIGHZ_CFG_GND,   /*!< channel tie to ground */
    TOUCH_CHANNEL_HIGHZ_CFG_HIGHZ, /*!< channel HighZ output */
} TOUCH_CHANNEL_HIGHZ_CFG_Type;

/**
 *  @brief TOUCH channel configuration type definition
 */
typedef struct
{
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch0;  /*!< TOUCH channel 0 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch1;  /*!< TOUCH channel 1 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch2;  /*!< TOUCH channel 2 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch3;  /*!< TOUCH channel 3 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch4;  /*!< TOUCH channel 4 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch5;  /*!< TOUCH channel 5 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch6;  /*!< TOUCH channel 6 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch7;  /*!< TOUCH channel 7 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch8;  /*!< TOUCH channel 8 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch9;  /*!< TOUCH channel 9 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch10; /*!< TOUCH channel 10 HighZ config */
    TOUCH_CHANNEL_HIGHZ_CFG_Type ch11; /*!< TOUCH channel 11 HighZ config */
} TOUCH_CHANNEL_CFG_Type;

/**
 *  @brief TOUCH interrupt type definition
 */
typedef enum {
    TOUCH_INT_INTERRUPT, /*!< TOUCH has only one interrupt */
} TOUCH_INT_Type;

/*@} end of group TOUCH_Public_Types */

/** @defgroup  TOUCH_Public_Constants
 *  @{
 */

/** @defgroup  TOUCH_ID_TYPE
 *  @{
 */
#define IS_TOUCH_ID_TYPE(type) (((type) == TOUCH_ID_0))

/** @defgroup  TOUCH_RUN_MODE_TYPE
 *  @{
 */
#define IS_TOUCH_RUN_MODE_TYPE(type) (((type) == TOUCH_RUN_MODE_SINGLE_SHOT) || \
                                      ((type) == TOUCH_RUN_MODE_CONTINUE))

/** @defgroup  TOUCH_PCHARGE_LOW_TYPE
 *  @{
 */
#define IS_TOUCH_PCHARGE_LOW_TYPE(type) (((type) == TOUCH_PCHARGE_LOW_127) ||  \
                                         ((type) == TOUCH_PCHARGE_LOW_255) ||  \
                                         ((type) == TOUCH_PCHARGE_LOW_511) ||  \
                                         ((type) == TOUCH_PCHARGE_LOW_1023) || \
                                         ((type) == TOUCH_PCHARGE_LOW_2047) || \
                                         ((type) == TOUCH_PCHARGE_LOW_4095))

/** @defgroup  TOUCH_PCHARGE_HIGH_TYPE
 *  @{
 */
#define IS_TOUCH_PCHARGE_HIGH_TYPE(type) (((type) == TOUCH_PCHARGE_HIGH_511) ||   \
                                          ((type) == TOUCH_PCHARGE_HIGH_1023) ||  \
                                          ((type) == TOUCH_PCHARGE_HIGH_2047) ||  \
                                          ((type) == TOUCH_PCHARGE_HIGH_4095) ||  \
                                          ((type) == TOUCH_PCHARGE_HIGH_8191) ||  \
                                          ((type) == TOUCH_PCHARGE_HIGH_16383) || \
                                          ((type) == TOUCH_PCHARGE_HIGH_32767) || \
                                          ((type) == TOUCH_PCHARGE_HIGH_65535))

/** @defgroup  TOUCH_CLK_DIV_TYPE
 *  @{
 */
#define IS_TOUCH_CLK_DIV_TYPE(type) (((type) == TOUCH_CLK_DIV_1) ||  \
                                     ((type) == TOUCH_CLK_DIV_2) ||  \
                                     ((type) == TOUCH_CLK_DIV_4) ||  \
                                     ((type) == TOUCH_CLK_DIV_8) ||  \
                                     ((type) == TOUCH_CLK_DIV_16) || \
                                     ((type) == TOUCH_CLK_DIV_32) || \
                                     ((type) == TOUCH_CLK_DIV_64) || \
                                     ((type) == TOUCH_CLK_DIV_128))

/** @defgroup  TOUCH_CLK_SEL_TYPE
 *  @{
 */
#define IS_TOUCH_CLK_SEL_TYPE(type) (((type) == TOUCH_CLK_SEL_32K) || \
                                     ((type) == TOUCH_CLK_SEL_32M))

/** @defgroup  TOUCH_POWER_SEL_TYPE
 *  @{
 */
#define IS_TOUCH_POWER_SEL_TYPE(type) (((type) == TOUCH_POWER_SEL_AON) || \
                                       ((type) == TOUCH_POWER_SEL_INTERNAL_BG))

/** @defgroup  TOUCH_HYSTERSIS_VOLTAGE_TYPE
 *  @{
 */
#define IS_TOUCH_HYSTERSIS_VOLTAGE_TYPE(type) (((type) == TOUCH_HYSTERSIS_VOLTAGE_30mV) || \
                                               ((type) == TOUCH_HYSTERSIS_VOLTAGE_80mV))

/** @defgroup  TOUCH_LDO_VOLTAGE_TYPE
 *  @{
 */
#define IS_TOUCH_LDO_VOLTAGE_TYPE(type) (((type) == TOUCH_LDO_VOLTAGE_0P6V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_0P8V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_1P0V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_1P2V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_1P4V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_1P6V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_1P8V) || \
                                         ((type) == TOUCH_LDO_VOLTAGE_2P0V))

/** @defgroup  TOUCH_VREF_VOLTAGE_TYPE
 *  @{
 */
#define IS_TOUCH_VREF_VOLTAGE_TYPE(type) (((type) == TOUCH_VREF_VOLTAGE_0P4V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_0P6V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_0P8V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_1P0V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_1P2V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_1P4V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_1P6V) || \
                                          ((type) == TOUCH_VREF_VOLTAGE_1P8V))

/** @defgroup  TOUCH_COMPENSATION_CAP_TYPE
 *  @{
 */
#define IS_TOUCH_COMPENSATION_CAP_TYPE(type) (((type) == TOUCH_COMPENSATION_CAP_12pF) || \
                                              ((type) == TOUCH_COMPENSATION_CAP_13pF) || \
                                              ((type) == TOUCH_COMPENSATION_CAP_14pF) || \
                                              ((type) == TOUCH_COMPENSATION_CAP_15pF))

/** @defgroup  TOUCH_WORK_MODE_TYPE
 *  @{
 */
#define IS_TOUCH_WORK_MODE_TYPE(type) (((type) == TOUCH_WORK_MODE_SELF_CAP) || \
                                       ((type) == TOUCH_WORK_MODE_MUTUAL))

/** @defgroup  TOUCH_FILTER_ORDER_CTRL_TYPE
 *  @{
 */
#define IS_TOUCH_FILTER_ORDER_CTRL_TYPE(type) (((type) == TOUCH_FILTER_ORDER_CTRL_0) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_1) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_2) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_3) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_4) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_5) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_6) || \
                                               ((type) == TOUCH_FILTER_ORDER_CTRL_7))

/** @defgroup  TOUCH_LTA_ORDER_CTRL_TYPE
 *  @{
 */
#define IS_TOUCH_LTA_ORDER_CTRL_TYPE(type) (((type) == TOUCH_LTA_ORDER_CTRL_0) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_1) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_2) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_3) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_4) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_5) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_6) || \
                                            ((type) == TOUCH_LTA_ORDER_CTRL_7))

/** @defgroup  TOUCH_CHANNEL_TYPE
 *  @{
 */
#define IS_TOUCH_CHANNEL_TYPE(type) (((type) == TOUCH_CHANNEL_0) ||  \
                                     ((type) == TOUCH_CHANNEL_1) ||  \
                                     ((type) == TOUCH_CHANNEL_2) ||  \
                                     ((type) == TOUCH_CHANNEL_3) ||  \
                                     ((type) == TOUCH_CHANNEL_4) ||  \
                                     ((type) == TOUCH_CHANNEL_5) ||  \
                                     ((type) == TOUCH_CHANNEL_6) ||  \
                                     ((type) == TOUCH_CHANNEL_7) ||  \
                                     ((type) == TOUCH_CHANNEL_8) ||  \
                                     ((type) == TOUCH_CHANNEL_9) ||  \
                                     ((type) == TOUCH_CHANNEL_10) || \
                                     ((type) == TOUCH_CHANNEL_11))

/** @defgroup  TOUCH_CHANNEL_HIGHZ_CFG_TYPE
 *  @{
 */
#define IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(type) (((type) == TOUCH_CHANNEL_HIGHZ_CFG_GND) || \
                                               ((type) == TOUCH_CHANNEL_HIGHZ_CFG_HIGHZ))

/** @defgroup  TOUCH_INT_TYPE
 *  @{
 */
#define IS_TOUCH_INT_TYPE(type) (((type) == TOUCH_INT_INTERRUPT))

/*@} end of group TOUCH_Public_Constants */

/** @defgroup  TOUCH_Public_Macros
 *  @{
 */

/*@} end of group TOUCH_Public_Macros */

/** @defgroup  TOUCH_Public_Functions
 *  @{
 */
BL_Err_Type TOUCH_Init(TOUCH_ID_Type touchId, TOUCH_CFG_Type *tCfg);
BL_Err_Type TOUCH_CHANNEL_Init(TOUCH_ID_Type touchId, TOUCH_CHANNEL_CFG_Type *tChCfg, TOUCH_CHANNEL_Type tChSel);
BL_Err_Type TOUCH_Enable(TOUCH_ID_Type touchId);
BL_Err_Type TOUCH_Disable(TOUCH_ID_Type touchId);
BL_Err_Type TOUCH_SetVthData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh, uint8_t value);
uint32_t TOUCH_GetVthData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh);
uint32_t TOUCH_GetRawData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh);
uint32_t TOUCH_GetLtaData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh);
uint32_t TOUCH_GetFltData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh);
BL_Sts_Type TOUCH_GetEndStatus(TOUCH_ID_Type touchId);
BL_Err_Type TOUCH_IntEnable(TOUCH_ID_Type touchId, TOUCH_INT_Type intType);
BL_Err_Type TOUCH_IntDisable(TOUCH_ID_Type touchId, TOUCH_INT_Type intType);
BL_Err_Type TOUCH_IntMask(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh, BL_Mask_Type intMask);
BL_Sts_Type TOUCH_GetIntStatus(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh);
BL_Err_Type TOUCH_ClrIntStatus(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh);
BL_Err_Type TOUCH_INT_Callback_Install(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh,
                                       intCallback_Type *cbFun);

/*@} end of group TOUCH_Public_Functions */

/*@} end of group TOUCH */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_TOUCH_H__ */
