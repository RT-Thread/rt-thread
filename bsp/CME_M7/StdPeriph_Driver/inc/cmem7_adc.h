/**
    *****************************************************************************
    * @file     cmem7_adc.h
    *
    * @brief    CMEM7 ADC header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_ADC_H
#define __CMEM7_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup ADC_PERIPH
  * @{
  */
typedef enum {
    ADC_PERIPH_1,
    ADC_PERIPH_2,
} ADC_PERIPH;

#define IS_ADC_ALL_PERIPH(PERIPH)         (((PERIPH) == ADC_PERIPH_1) || \
                                           ((PERIPH) == ADC_PERIPH_2))

/**
  * @}
  */

/** @defgroup ADC_VSEN
  * @{
  */
#define ADC_VSEN_VDDCORE                  1
#define ADC_VSEN_VDDIO                    2
#define ADC_VSEN_VDDIO2                   4

#define IS_ADC_VSEN(VSEN)                 (((VSEN) == ADC_VSEN_VDDCORE) || \
                                           ((VSEN) == ADC_VSEN_VDDIO) || \
                                           ((VSEN) == ADC_VSEN_VDDIO2))

/**
  * @}
  */

/** @defgroup ADC_PHASE_CTRL
  * @{
  */
#define ADC_PHASE_CTRL_0DEG_RISE_EDGE     0         /* ADC-1 and ADC-2 CLK are 0DEG Phase Difference(Rising Edge) */
#define ADC_PHASE_CTRL_90DEG_AHEAD        1         /* ADC-1 90DEG ahead of ADC-2 */
#define ADC_PHASE_CTRL_90DEG_LAG          2         /* ADC-1 90DEG lag of ADC-2 */
#define ADC_PHASE_CTRL_0DEG_FALL_EDGE     3         /* ADC-1 and ADC-2 CLK are 0DEG Phase Difference(falling Edge) */

#define IS_ADC_PHASE_CTRL(CTRL)           (((CTRL) == ADC_PHASE_CTRL_0DEG_RISE_EDGE) || \
                                           ((CTRL) == ADC_PHASE_CTRL_90DEG_AHEAD) || \
                                           ((CTRL) == ADC_PHASE_CTRL_90DEG_LAG) || \
                                           ((CTRL) == ADC_PHASE_CTRL_0DEG_FALL_EDGE))
/**
  * @}
  */

/** @defgroup ADC_CONVERSION
  * @{
  */
#define ADC_SYSTEM_MODE_SINGLE_CONV       1
#define ADC_SYSTEM_MODE_CONTINUOUS_CONV   2

#define IS_ADC_CONVERSION(CONV)           (((CONV) == ADC_SYSTEM_MODE_SINGLE_CONV) || \
                                           ((CONV) == ADC_SYSTEM_MODE_CONTINUOUS_CONV))

/**
  * @}
  */

/** @defgroup ADC_CALIBRATION
  * @{
  */
#define ADC_CALIBRATION_OFFSET            3
#define ADC_CALIBRATION_NEGTIVE_GAIN      4
#define ADC_CALIBRATION_POSTIVE_GAIN      5

#define IS_ADC_CALIBRATION(CALIB)         (((CALIB) == ADC_CALIBRATION_OFFSET) || \
                                           ((CALIB) == ADC_CALIBRATION_NEGTIVE_GAIN) || \
                                           ((CALIB) == ADC_CALIBRATION_POSTIVE_GAIN))
/**
  * @}
  */

/** @defgroup ADC_CHANNEL
  * @{
  */
#define ADC_CHANNEL_CALIBRATION           0x0

/**
  * @}
  */

/** @defgroup ADC1_CHANNEL
  * @{
  */
#define ADC1_CHANNEL_VIP                  0x1
#define ADC1_CHANNEL_VSEN                 0x2
#define ADC1_CHANNEL_VADIO_0              0x4
#define ADC1_CHANNEL_VADIO_1              0x8
#define ADC1_CHANNEL_VADIO_2              0x10
#define ADC1_CHANNEL_VADIO_3              0x20
#define ADC1_CHANNEL_VADIO_4              0x40
#define ADC1_CHANNEL_VADIO_5              0x80
#define ADC1_CHANNEL_ALL                  0xFF

#define IS_ADC1_CHANNEL(CHANNEL)          (((CHANNEL) != 0) && ((CHANNEL) & ~ADC1_CHANNEL_ALL) == 0)
/**
  * @}
  */

/** @defgroup ADC2_CHANNEL
  * @{
  */
#define ADC2_CHANNEL_VIN                  0x1
#define ADC2_CHANNEL_VTMP                 0x2
#define ADC2_CHANNEL_VADIO_6              0x4
#define ADC2_CHANNEL_VADIO_7              0x8
#define ADC2_CHANNEL_VADIO_8              0x10
#define ADC2_CHANNEL_VADIO_9              0x20
#define ADC2_CHANNEL_VADIO_10             0x40
#define ADC2_CHANNEL_VADIO_11             0x80
#define ADC2_CHANNEL_ALL                  0xFF

#define IS_ADC2_CHANNEL(CHANNEL)          (((CHANNEL) != 0) && ((CHANNEL) & ~ADC2_CHANNEL_ALL) == 0)
/**
  * @}
  */

/** @defgroup ADC_INT
  * @{
  */
#define ADC1_INT_ALMOST_FULL              0x1
#define ADC2_INT_ALMOST_FULL              0x8
#define ADC_INT_ALL                                 0x9

#define IS_ADC_INT(INT)                             (((INT) != 0) && (((INT) & ~ADC_INT_ALL) == 0))
/**
  * @}
  */

/**
  * @brief  ADC collection data structure
    */
typedef struct {
    uint8_t channel;                                                /*!< The channel of collected data, is a value of
                                                                                             @ref ADC_CHANNEL, @ref ADC1_CHANNEL or @ref ADC2_CHANNEL */
    uint16_t data;                                                  /*!< collected data                                                                 */
} ADC_Data;

/**
  * @brief  ADC initialization structure
    */
typedef struct
{
    uint8_t ADC_PhaseCtrl;                  /*!< Phase between ADC1 and ADC2, is a value of @ref ADC_PHASE_CTRL */
    uint8_t ADC_VsenSelection;              /*!< ADC1 VSEN selection, is a value of @ref ADC_VSEN                   */
} ADC_InitTypeDef;

/**
  * @brief  ADC initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] init A pointer to structure ADC_InitTypeDef
  * @retval None
    */
void ADC_Init(ADC_InitTypeDef* init);

/**
  * @brief  Enable or disable ADC.
    * @param[in] adc ADC peripheral, which is a value of @ref ADC_PERIPH
    * @param[in] Enable The bit indicates if the specific ADC is enable or not
  * @retval None
    */
void ADC_Enable(uint8_t adc, BOOL enable);

/**
  * @brief  Enable or disable ADC interrupt.
    * @param[in] Int interrupt mask bits, which can be a combination of @ref ADC_INT
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void ADC_EnableInt(uint32_t Int, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] Int interrupt mask bits, which can be a combination of @ref ADC_INT
    * @retval BOOL The bit indicates if the specific interrupts are set or not
    */
BOOL ADC_GetIntStatus(uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @param[in] Int interrupt mask bits, which can be a value of @ref ADC_INT
  * @retval None
    */
void ADC_ClearInt(uint32_t Int);

/**
  * @brief  ADC starts to convert data
    * @param[in] adc ADC peripheral, which is a value of @ref ADC_PERIPH
    * @param[in] convMode It should be a value of @ref ADC_CONVERSION
    * @param[in] channel It should be the value of @ref ADC1_CHANNEL
    *                    or @ref ADC2_CHANNEL according to parameter 'adc'
  * @retval BOOL The bit indicates if the specific ADC starts to convert data
    */
BOOL ADC_StartConversion(uint8_t adc, uint8_t convMode, uint32_t channel);

/**
  * @brief  ADC starts to calibrate and produces one sample
    * @param[in] adc ADC peripheral, which is a value of @ref ADC_PERIPH
    * @param[in] convMode It should be a value of @ref ADC_CALIBRATION
  * @retval BOOL The bit indicates if the specific ADC starts to convert data
    */
BOOL ADC_StartCalibration(uint8_t adc, uint8_t calibration);

/**
  * @brief  ADC stops conversion or calibration
    * @param[in] adc ADC peripheral, which is a value of @ref ADC_PERIPH
    * @retval NULL
    */
void ADC_Stop(uint8_t adc);

/**
  * @brief  Check if ADC is busy or not
    * @param[in] adc ADC peripheral, which is a value of @ref ADC_PERIPH
    * @retval BOOL The bit indicates if the specific ADC is busy or not
    */
BOOL ADC_IsBusy(uint8_t adc);

/**
  * @brief  Read data from ADC
    * @param[in] adc ADC peripheral, which is a value of @ref ADC_PERIPH
    * @param[in] Size Expected data size to be read
    * @param[out] data A user-allocated buffer to fetch data to be read
  * @retval uint8_t Actual read data size
    */
uint8_t ADC_Read(uint8_t adc, uint8_t size, ADC_Data* data);

#ifdef __cplusplus
}
#endif

#endif /*__CMEM7_ADC_H */

