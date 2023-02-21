/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_TIM_ADV_H__
#define __HAL_TIM_ADV_H__

#include "hal_common.h"

/*!
 * @addtogroup TIM_ADV
 * @{
 */

/*!
 * @brief TIM_ADV driver version number.
 */
#define TIM_ADV_DRIVER_VERSION 0u /*!< TIM_ADV_0. */

/*!
 * @addtogroup TIM_ADV_CHANNEL_SELECTION
 * @{
 */
#define TIM_ADV_CHN_NUM    (5u) /*!< The total number of TIM_ADV channel. */
#define TIM_ADV_CHN_1      (0u) /*!< The selection of TIM_ADV Channel 1. */
#define TIM_ADV_CHN_2      (1u) /*!< The selection of TIM_ADV Channel 2. */
#define TIM_ADV_CHN_3      (2u) /*!< The selection of TIM_ADV Channel 3. */
#define TIM_ADV_CHN_4      (3u) /*!< The selection of TIM_ADV Channel 4. */
#define TIM_ADV_CHN_5      (4u) /*!< The selection of TIM_ADV Channel 5. */
/*!
 *@}
 */

/*!
 * @addtogroup TIM_ADV_INT
 * @brief Enable interrupt.
 * @{
 */
#define TIM_ADV_INT_UPDATE_PERIOD   (1u << 0u) /*!< Timer update period interrupt switchers. */
#define TIM_ADV_INT_CHN1_EVENT      (1u << 1u) /*!< Channel 1 event for output compare or input capture interrupt switchers. */
#define TIM_ADV_INT_CHN2_EVENT      (1u << 2u) /*!< Channel 2 event for output compare or input capture interrupt switchers. */
#define TIM_ADV_INT_CHN3_EVENT      (1u << 3u) /*!< Channel 3 event for output compare or input capture interrupt switchers. */
#define TIM_ADV_INT_CHN4_EVENT      (1u << 4u) /*!< Channel 4 event for output compare or input capture interrupt switchers. */
#define TIM_ADV_INT_COM_EVENT       (1u << 5u) /*!< Channel complementary pwm commutation interrupt switchers. */
#define TIM_ADV_INT_TRGOUT_EVENT    (1u << 6u) /*!< Trigger out event interrupt switchers. */
#define TIM_ADV_INT_BREAK_EVENT     (1u << 7u) /*!< Break event interrupt switchers. */
#define TIM_ADV_INT_CH5_EVENT       (1u << 16u) /*!< Channel 5 event for output compare or input capture interrupt switchers. */
/*!
 * @}
 */

/*!
 * @addtogroup TIM_ADV_DMA
 * @brief Enable DMA.
 * @{
 */
#define TIM_ADV_DMA_UPDATE_PERIOD   (1u << 8u)  /*!< Timer update period DMA switchers. */
#define TIM_ADV_DMA_CHN1_EVENT       (1u << 9u)  /*!< Channel 1 event for output compare or input capture DMA switchers. */
#define TIM_ADV_DMA_CHN2_EVENT       (1u << 10u) /*!< Channel 2 event for output compare or input capture DMA switchers. */
#define TIM_ADV_DMA_CHN3_EVENT       (1u << 11u) /*!< Channel 3 event for output compare or input capture DMA switchers. */
#define TIM_ADV_DMA_CHN4_EVENT       (1u << 12u) /*!< Channel 4 event for output compare or input capture DMA switchers. */
#define TIM_ADV_DMA_COM_EVENT       (1u << 13u) /*!< Channel complementary pwm commutation interrupt switchers. */
#define TIM_ADV_DMA_TRGOUT_EVENT    (1u << 14u) /*!< Trigger out event DMA switchers. */
/*!
 * @}
 */

/*!
 * @addtogroup TIM_ADV_INT_STATUS
 * @brief Check interrupt status.
 * @{
 */
#define TIM_ADV_STATUS_UPDATE_PERIOD   (1u << 0u) /*!< Timer update period interrupt flag. */
#define TIM_ADV_STATUS_CHN1_EVENT       (1u << 1u) /*!< Channel 1 event for output compare or input capture interrupt flag. */
#define TIM_ADV_STATUS_CHN2_EVENT       (1u << 2u) /*!< Channel 2 event for output compare or input capture interrupt flag. */
#define TIM_ADV_STATUS_CHN3_EVENT       (1u << 3u) /*!< Channel 3 event for output compare or input capture interrupt flag. */
#define TIM_ADV_STATUS_CHN4_EVENT       (1u << 4u) /*!< Channel 4 event for output compare or input capture interrupt flag. */
#define TIM_ADV_STATUS_COM_EVENT       (1u << 5u) /*!< Channel complementary pwm commutation interrupt flag. */
#define TIM_ADV_STATUS_TRGOUT_EVENT    (1u << 6u) /*!< Trigger out event interrupt flag. */
#define TIM_ADV_STATUS_BREAK_EVENT     (1u << 7u) /*!< Break event interrupt flag. */
#define TIM_ADV_STATUS_CHN1_OVER_EVENT  (1u << 9u) /*!< Channel 1 event for output overcompare or input overcapture interrupt flag. */
#define TIM_ADV_STATUS_CHN2_OVER_EVENT  (1u << 10u) /*!< Channel 2 event for output overcompare or input overcapture interrupt flag. */
#define TIM_ADV_STATUS_CHN3_OVER_EVENT  (1u << 11u) /*!< Channel 3 event for output overcompare or input overcapture interrupt flag. */
#define TIM_ADV_STATUS_CHN4_OVER_EVENT  (1u << 12u) /*!< Channel 4 event for output overcompare or input overcapture interrupt flag. */
#define TIM_ADV_STATUS_CHN5_EVENT       (1u << 16u) /*!< Channel 5 event for output compare or input capture interrupt flag. */
/*!
 * @}
 */

/*!
 * @addtogroup TIM_ADV_SWTRG
 * @brief Events to be triggered by software.
 * @{
 */
#define TIM_ADV_SWTRG_UPDATE_PERIOD   (1u << 0u) /*!< Timer update period software trigger. */
#define TIM_ADV_SWTRG_CHN1_EVENT       (1u << 1u) /*!< Channel 1 event for output compare or input capture software trigger. */
#define TIM_ADV_SWTRG_CHN2_EVENT       (1u << 2u) /*!< Channel 2 event for output compare or input capture software trigger. */
#define TIM_ADV_SWTRG_CHN3_EVENT       (1u << 3u) /*!< Channel 3 event for output compare or input capture software trigger. */
#define TIM_ADV_SWTRG_CHN4_EVENT       (1u << 4u) /*!< Channel 4 event for output compare or input capture software trigger. */
#define TIM_ADV_SWTRG_COM_EVENT       (1u << 5u) /*!< Channel complementary pwm commutation software trigger. */
#define TIM_ADV_SWTRG_TRGOUT_EVENT    (1u << 6u) /*!< Trigger out event software trigger. */
#define TIM_ADV_SWTRG_BREAK_EVENT     (1u << 7u) /*!< Break event software trigger. */
#define TIM_ADV_SWTRG_CHN5_EVENT       (1u << 16u) /*!< Channel 5 event for output compare or input capture software trigger. */
/*!
 * @}
 */

/*!
 * @brief Counter period working mode.
 */
typedef enum
{
    TIM_ADV_PeriodMode_Continuous = 0u, /*!< Counter works circularly once started. */
    TIM_ADV_PeriodMode_OneTimeRun = 1u, /*!< Counter only works one time once started. */
} TIM_ADV_PeriodMode_Type;

/*!
 * @brief Counter count direction.
 */
typedef enum
{
    TIM_ADV_CountMode_Increasing = 0u,     /*!< Counter counts incrementally from 0 to period and generates an update. */
    TIM_ADV_CountMode_Decreasing = 1u,     /*!< Counter counts decrementally from period to 0 and generates an update. */
    TIM_ADV_CountMode_CenterAligned1 = 2u, /*!< Counter counts center-aligned from 0 to period - 1 then from period to 0 and generates an update. */
    TIM_ADV_CountMode_CenterAligned2 = 3u, /*!< Counter counts center-aligned from 0 to period - 1 and generates an update then from period to 0. */
    TIM_ADV_CountMode_CenterAligned3 = 4u, /*!< Counter counts center-aligned from 0 to period - 1 and generates an update then from period to 0 and generates another update. */
} TIM_ADV_CountMode_Type;

/*!
 * @brief TIM output compare reference polairty event.
 */
typedef enum
{
    TIM_ADV_OutputCompareRefOut_None = 0u,        /*!< Reference will not be changed. */
    TIM_ADV_OutputCompareRefOut_HighOnMatch = 1u, /*!< Reference will be high when counter value equals channel value. */
    TIM_ADV_OutputCompareRefOut_LowOnMatch = 2u,  /*!< Reference will be low when counter value equals channel value. */
    TIM_ADV_OutputCompareRefOut_ToggleOnMatch = 3u, /*!< Reference will toggle. */
    TIM_ADV_OutputCompareRefOut_LowAlways = 4u,    /*!< Reference will always be low. */
    TIM_ADV_OutputCompareRefOut_HighAlways = 5u,     /*!< Reference will always be high. */
    TIM_ADV_OutputCompareRefOut_FallingEdgeOnMatch = 6u, /*!< PWM mode 1. */
    TIM_ADV_OutputCompareRefOut_RisingEdgeOnMatch = 7u,  /*!< PWM mode 2. */
} TIM_ADV_OutputCompareRefOut_Type;

/*!
 * @brief TIM input capture active edge selection and output compare active polarity selection.
 * | conf                    | TIM_ADV_PinPolarity_Rising | TIM_ADV_PinPolarity_Falling |
 * | ----------------------- | -------------------------- | --------------------------- |
 * | input capture           | detects rising edge        | detects falling edge        |
 * | output compare          | high polarity is active    | low polarity is active      |
 * | encoder mode            | input remains              | input reverses              |
 * | output under idle state | output high polarity       | output low polarity         |
 */
typedef enum
{
    TIM_ADV_PinPolarity_Disable = 0u, /*!< Disable channel. */
    TIM_ADV_PinPolarity_Rising = 1u, /*!< See the table above. */
    TIM_ADV_PinPolarity_Falling = 2u, /*!< See the table above.*/
    TIM_ADV_PinPolarity_RisingOrFalling = 3u, /*!< For input capture, detect both the rising and falling edge. */
}TIM_ADV_PinPolarity_Type;

/*!
 * @brief TIM Input active times to evoke capture.
 */
typedef enum
{
    TIM_ADV_InputCaptureInDiv_OnEveryCapture = 0u, /*!< Every input call capture. */
    TIM_ADV_InputCaptureInDiv_OnEach2Capture = 1u, /*!< Every two input call capture. */
    TIM_ADV_InputCaptureInDiv_OnEach4Capture = 2u, /*!< Every four input call capture. */
    TIM_ADV_InputCaptureInDiv_OnEach8Capture = 3u, /*!< Every eight input call capture. */
} TIM_ADV_InputCaptureInDiv_Type;

/*!
 * @brief TIM Input sampling filter.
 */
typedef enum
{
    TIM_ADV_InputCaptureInFilter_Alt0  = 0u, /*!< Filter swicther 0. */
    TIM_ADV_InputCaptureInFilter_Alt1  = 1u, /*!< Filter swicther 1. */
    TIM_ADV_InputCaptureInFilter_Alt2  = 2u, /*!< Filter swicther 2. */
    TIM_ADV_InputCaptureInFilter_Alt3  = 3u, /*!< Filter swicther 3. */
    TIM_ADV_InputCaptureInFilter_Alt4  = 4u, /*!< Filter swicther 4. */
    TIM_ADV_InputCaptureInFilter_Alt5  = 5u, /*!< Filter swicther 5. */
    TIM_ADV_InputCaptureInFilter_Alt6  = 6u, /*!< Filter swicther 6. */
    TIM_ADV_InputCaptureInFilter_Alt7  = 7u, /*!< Filter swicther 7. */
    TIM_ADV_InputCaptureInFilter_Alt8  = 8u, /*!< Filter swicther 8. */
    TIM_ADV_InputCaptureInFilter_Alt9  = 9u, /*!< Filter swicther 9. */
    TIM_ADV_InputCaptureInFilter_Alt10 = 10u, /*!< Filter swicther 10. */
    TIM_ADV_InputCaptureInFilter_Alt11 = 11u, /*!< Filter swicther 11. */
    TIM_ADV_InputCaptureInFilter_Alt12 = 12u, /*!< Filter swicther 12. */
    TIM_ADV_InputCaptureInFilter_Alt13 = 13u, /*!< Filter swicther 13. */
    TIM_ADV_InputCaptureInFilter_Alt14 = 14u, /*!< Filter swicther 14. */
    TIM_ADV_InputCaptureInFilter_Alt15 = 15u, /*!< Filter swicther 15. */
} TIM_ADV_InputCaptureInFilter_Type;

/*!
 * @brief TIM channel IO mode.
 */
typedef enum
{
    TIM_ADV_ChannelIOMode_Out  = 0u, /*!< Channel output. */
    TIM_ADV_ChannelIOMode_In   = 1u, /*!< Channel input, capture signal from direct channel. */
    TIM_ADV_ChannelIOMode_Alt2 = 2u, /*!< Channel input, capture signal from indirect channel. */
    TIM_ADV_ChannelIOMode_Alt3 = 3u, /*!< Channel input, capture signal from trc. */
} TIM_ADV_ChannelIOMode_Type;

/*!
 * @brief TIM external trigger input active edge selection.
 */
typedef enum
{
    TIM_ADV_ExtTriggerPinPolarity_Disable = 0u, /*!< Disable external trigger input. */
    TIM_ADV_ExtTriggerPinPolarity_Rising = 1u, /*!< Detect the rising edge from external trigger. */
    TIM_ADV_ExtTriggerPinPolarity_Falling = 2u, /*!< Detect the falling edge from external trigger. */
}TIM_ADV_ExtTriggerPinPolarity_Type;

/*!
 * @brief TIM external trigger active input times to drive counter.
 */
typedef enum
{
    TIM_ADV_ExtTriggerInDiv_OnEveryCapture = 0u, /*!< Every input call capture. */
    TIM_ADV_ExtTriggerInDiv_OnEach2Capture = 1u, /*!< Every two input call capture. */
    TIM_ADV_ExtTriggerInDiv_OnEach4Capture = 2u, /*!< Every four input call capture. */
    TIM_ADV_ExtTriggerInDiv_OnEach8Capture = 3u, /*!< Every eight input call capture. */
} TIM_ADV_ExtTriggerInDiv_Type;

/*!
 * @brief TIM external trigger sampling filter.
 */
typedef enum
{
    TIM_ADV_ExtTriggerInFilter_Alt0  = 0u, /*!< Filter swicther 0. */
    TIM_ADV_ExtTriggerInFilter_Alt1  = 1u, /*!< Filter swicther 1. */
    TIM_ADV_ExtTriggerInFilter_Alt2  = 2u, /*!< Filter swicther 2. */
    TIM_ADV_ExtTriggerInFilter_Alt3  = 3u, /*!< Filter swicther 3. */
    TIM_ADV_ExtTriggerInFilter_Alt4  = 4u, /*!< Filter swicther 4. */
    TIM_ADV_ExtTriggerInFilter_Alt5  = 5u, /*!< Filter swicther 5. */
    TIM_ADV_ExtTriggerInFilter_Alt6  = 6u, /*!< Filter swicther 6. */
    TIM_ADV_ExtTriggerInFilter_Alt7  = 7u, /*!< Filter swicther 7. */
    TIM_ADV_ExtTriggerInFilter_Alt8  = 8u, /*!< Filter swicther 8. */
    TIM_ADV_ExtTriggerInFilter_Alt9  = 9u, /*!< Filter swicther 9. */
    TIM_ADV_ExtTriggerInFilter_Alt10 = 10u, /*!< Filter swicther 10. */
    TIM_ADV_ExtTriggerInFilter_Alt11 = 11u, /*!< Filter swicther 11. */
    TIM_ADV_ExtTriggerInFilter_Alt12 = 12u, /*!< Filter swicther 12. */
    TIM_ADV_ExtTriggerInFilter_Alt13 = 13u, /*!< Filter swicther 13. */
    TIM_ADV_ExtTriggerInFilter_Alt14 = 14u, /*!< Filter swicther 14. */
    TIM_ADV_ExtTriggerInFilter_Alt15 = 15u, /*!< Filter swicther 15. */
} TIM_ADV_ExtTriggerInFilter_Type;

/*!
 * @brief TIM Dead area time step length.
 */
typedef enum
{
    TIM_ADV_DeadAreaStep_Alt0 = 0u, /*!< Dead area step = clock source step. */
    TIM_ADV_DeadAreaStep_Alt1 = 1u, /*!< Dead area step = 2 * clock source step. */
    TIM_ADV_DeadAreaStep_Alt2 = 2u, /*!< Dead area step = 4 * clock source step. */
} TIM_ADV_DeadAreaStep_Type;

/*!
 * @brief TIM master mode output signal source.
 */
typedef enum
{
    TIM_ADV_MasterOut_Alt0 = 0u, /*!< Software update period trigger signal works as master output. */
    TIM_ADV_MasterOut_Alt1 = 1u, /*!< Counter enable signal works as master output. */
    TIM_ADV_MasterOut_Alt2 = 2u, /*!< Update period event works as master output. */
    TIM_ADV_MasterOut_Alt3 = 3u, /*!< Channel capture or compare event works as master output. */
    TIM_ADV_MasterOut_Alt4 = 4u, /*!< Reference signal of channel 1 works as master output. */
    TIM_ADV_MasterOut_Alt5 = 5u, /*!< Reference signal of channel 2 works as master output. */
    TIM_ADV_MasterOut_Alt6 = 6u, /*!< Reference signal of channel 3 works as master output. */
    TIM_ADV_MasterOut_Alt7 = 7u, /*!< Reference signal of channel 4 works as master output. */
} TIM_ADV_MasterOut_Type;

/*!
 * @brief TIM slave mode input object source.
 */
typedef enum
{
    TIM_ADV_SlaveIn_Alt0 = 0u, /*!< Internal trigger 0. */
    TIM_ADV_SlaveIn_Alt1 = 1u, /*!< Internal trigger 1. */
    TIM_ADV_SlaveIn_Alt2 = 2u, /*!< Internal trigger 2.*/
    TIM_ADV_SlaveIn_Alt3 = 3u, /*!< Internal trigger 3. */
    TIM_ADV_SlaveIn_Alt4 = 4u, /*!< Edge detector of timer input channel 1. */
    TIM_ADV_SlaveIn_Alt5 = 5u, /*!< Timer input channel 1. */
    TIM_ADV_SlaveIn_Alt6 = 6u, /*!< Timer input channel 2. */
    TIM_ADV_SlaveIn_Alt7 = 7u, /*!< External trigger input. */
} TIM_ADV_SlaveIn_Type;

/*!
 * @brief TIM slave mode counter response.
 */
typedef enum
{
    TIM_ADV_SlaveResp_Disable = 0u, /*!< Disable the slave mode. */
    TIM_ADV_SlaveResp_Alt1 = 1u, /*!< Counting in encoder mode 1. */
    TIM_ADV_SlaveResp_Alt2 = 2u, /*!< Counting in encoder mode 2.*/
    TIM_ADV_SlaveResp_Alt3 = 3u, /*!< Counting in encoder mode 3. */
    TIM_ADV_SlaveResp_Alt4 = 4u, /*!< Reset counter. */
    TIM_ADV_SlaveResp_Alt5 = 5u, /*!< Counter treat the signal as a gate. */
    TIM_ADV_SlaveResp_Alt6 = 6u, /*!< Start the counter. */
    TIM_ADV_SlaveResp_Alt7 = 7u, /*!< Counter counts on rising edges. */
} TIM_ADV_SlaveResp_Type;

/*!
 * @brief TIM DMA Burst transfer base address.
 */
typedef enum
{
    TIM_ADV_DMABurstBaseAddr_Alt0 = 0u, /*!< Start from CR1 register. */
    TIM_ADV_DMABurstBaseAddr_Alt1 = 1u, /*!< Start from CR2 register. */
    TIM_ADV_DMABurstBaseAddr_Alt2 = 2u, /*!< Start from SMCR register. */
    TIM_ADV_DMABurstBaseAddr_Alt3 = 3u, /*!< Start from DIER register. */
    TIM_ADV_DMABurstBaseAddr_Alt4 = 4u, /*!< Start from SR register. */
    TIM_ADV_DMABurstBaseAddr_Alt5 = 5u, /*!< Start from EGR register. */
    TIM_ADV_DMABurstBaseAddr_Alt6 = 6u, /*!< Start from CCMR1 register. */
    TIM_ADV_DMABurstBaseAddr_Alt7 = 7u, /*!< Start from CCMR2 register. */
    TIM_ADV_DMABurstBaseAddr_Alt8 = 8u, /*!< Start from CCER register. */
    TIM_ADV_DMABurstBaseAddr_Alt9 = 9u, /*!< Start from CNT register. */
    TIM_ADV_DMABurstBaseAddr_Alt10 = 10u, /*!< Start from PSC register. */
    TIM_ADV_DMABurstBaseAddr_Alt11 = 11u, /*!< Start from ARR register. */
    TIM_ADV_DMABurstBaseAddr_Alt12 = 12u, /*!< Start from CCR1 register. */
    TIM_ADV_DMABurstBaseAddr_Alt13 = 13u, /*!< Start from CCR2 register. */
    TIM_ADV_DMABurstBaseAddr_Alt14 = 14u, /*!< Start from CCR3 register. */
    TIM_ADV_DMABurstBaseAddr_Alt15 = 15u, /*!< Start from CCR4 register. */
} TIM_ADV_DMABurstBaseAddr_Type;

/*!
 * @brief TIM DMA Burst transfer length.
 */
typedef enum
{
    TIM_ADV_DMABurstBaseLen_Alt0 = 0u, /*!< Sequentially visit 1 register from base register */
    TIM_ADV_DMABurstBaseLen_Alt1 = 1u, /*!< Sequentially visit 2 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt2 = 2u, /*!< Sequentially visit 3 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt3 = 3u, /*!< Sequentially visit 4 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt4 = 4u, /*!< Sequentially visit 5 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt5 = 5u, /*!< Sequentially visit 6 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt6 = 6u, /*!< Sequentially visit 7 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt7 = 7u, /*!< Sequentially visit 8 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt8 = 8u, /*!< Sequentially visit 9 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt9 = 9u, /*!< Sequentially visit 10 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt10 = 10u, /*!< Sequentially visit 11 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt11 = 11u, /*!< Sequentially visit 12 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt12 = 12u, /*!< Sequentially visit 13 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt13 = 13u, /*!< Sequentially visit 14 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt14 = 14u, /*!< Sequentially visit 15 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt15 = 15u, /*!< Sequentially visit 16 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt16 = 16u, /*!< Sequentially visit 17 registers from base register */
    TIM_ADV_DMABurstBaseLen_Alt17 = 17u, /*!< Sequentially visit 18 registers from base register */
} TIM_ADV_DMABurstBaseLen_Type;

/*!
 * @brief TIM encoder direction.
 */
typedef enum
{
    TIM_ADV_EncoderDirection_Forward  = 0u, /*!< Encoder rotates in forward direction. */
    TIM_ADV_EncoderDirection_Backward = 1u, /*!< Encoder rotates in backward direction. */
} TIM_ADV_EncoderDirection_Type;

/*!
 * @brief TIM lock level.
 */
typedef enum
{
    TIM_ADV_LockLevel_Disable  = 0u, /*!< Unlock. */
    TIM_ADV_LockLevel_Alt0 = 1u, /*!< Lock level 1. */
    TIM_ADV_LockLevel_Alt1 = 2u, /*!< Lock level 2. */
    TIM_ADV_LockLevel_Alt2 = 3u, /*!< Lock level 3. */
} TIM_ADV_LockLevel_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref TIM_ADV_Init() to initialize the TIM module time base unit.
 */
typedef struct
{
    uint32_t ClockFreqHz;               /*!< Frequence of clock source for counter. */
    uint32_t StepFreqHz;                /*!< Step length value. Counter freq = ClockSourceFreqHz / (ClockSourceDiv+1). */
    uint32_t Period;                    /*!< Counter counting period length, from 0 to Period. */
    bool EnablePreloadPeriod;           /*!< Enable the preload of period value. If enable, it will be updated in next period, otherwise immediately. */
    TIM_ADV_PeriodMode_Type PeriodMode; /*!< Counter working period times. */
    TIM_ADV_CountMode_Type  CountMode;  /*!< Counter count direction. */
} TIM_ADV_Init_Type;

/*!
 * @brief This type of structure instance is used to setup the output compare feature when calling the @ref TIM_ADV_EnableOutputCompare() to enable the TIM module output compare channel.
 */
typedef struct
{
    uint16_t ChannelValue; /*!< Value to be compared with counter. */
    bool EnableFastOutput; /*!< Enable fast response to the trigger input event. */
    bool EnablePreLoadChannelValue; /*!< Enable the preload of channel value. If enable, it will be updated in next period, otherwise immediately. */
    TIM_ADV_OutputCompareRefOut_Type RefOutMode; /*!< The reference output when counter matching the channel value. */
    bool ClearRefOutOnExtTrigger; /*!< External trigger high will clear the reference. */
    TIM_ADV_PinPolarity_Type PinPolarity; /*!< Setup the output pin's polarity. */
    TIM_ADV_PinPolarity_Type COMPPinPolarity; /*!< Set the complementary channel output. */
} TIM_ADV_OutputCompareConf_Type;

/*!
 * @brief This type of structure instance is used to setup the input capture feature when calling the @ref TIM_ADV_EnableInputCapture() to enable the TIM module input capture channel.
 */
typedef struct
{
    TIM_ADV_InputCaptureInDiv_Type    InDiv; /*!< The division of filtered input. */
    TIM_ADV_InputCaptureInFilter_Type InFilter; /*!< The filter sampling time for initial input. */
    TIM_ADV_PinPolarity_Type        PinPolarity; /*!< Setup the output pin's polarity. */
} TIM_ADV_InputCaptureConf_Type;

/*!
 * @brief This type of structure instance is used to setup the dead time feature when calling the @ref TIM_ADV_EnableDeadArea() to enable the TIM module dead time area set.
 * | DeadAreaCoef | Real Dead Area Time                                 |
 * | ------------ | --------------------------------------------------- |
 * | 0xxxxxxx     | DeadAreaCoef * DeadAreaStep                         |
 * | 10xxxxxx     | ( 64 +  DeadAreaCoef[5:0] ) * ( 2 * DeadAreaStep )  |
 * | 110xxxxx     | ( 32 +  DeadAreaCoef[4:0] ) * ( 8 * DeadAreaStep ï¼‰ |
 * | 111xxxxx     | ( 32 +  DeadAreaCoef[4:0] ) * ( 16 * DeadAreaStep ) |
 */
typedef struct
{
    TIM_ADV_DeadAreaStep_Type    StepFreqHz; /*!< Dead time area step set. */
    uint8_t DeadAreaCoef; /*!< The coefficient with bias to multiply with StepFreqHz to get the final dead area time. */
} TIM_ADV_DeadAreaConf_Type;

/*!
 * @brief This type of structure instance is used to setup the master mode configuration when calling the @ref TIM_ADV_EnableMasterMode().
 */
typedef struct
{
    TIM_ADV_MasterOut_Type Out; /*!< Master mode output selection. */
    bool EnableSync; /*!< Enable sychronize with slave timers. */
} TIM_ADV_MasterModeConf_Type;

/*!
 * @brief This type of structure instance is used to setup the slave mode configuration when calling the @ref TIM_ADV_EnableSlaveMode().
 */
typedef struct
{
    TIM_ADV_SlaveIn_Type In; /*!< Input trigger selection for slave timer. */
    TIM_ADV_SlaveResp_Type Resp;  /*!< Slave timer counter response for its input trigger. */
} TIM_ADV_SlaveModeConf_Type;

/*!
 * @brief This type of structure instance is used to setup the external trigger input configuration when calling the @ref TIM_ADV_EnableExtTriggerIn().
 */
typedef struct
{
    TIM_ADV_ExtTriggerInDiv_Type    InDiv;     /*!< The division of filtered input. */
    TIM_ADV_ExtTriggerInFilter_Type InFilter;  /*!< The filter sampling time for initial input. */
    TIM_ADV_ExtTriggerPinPolarity_Type PinPolarity; /*!< Setup the output pin's polarity. */
} TIM_ADV_ExtTriggerInConf_Type;

/*!
 * @brief This type of structure instance is used to setup the dma burst configuration when calling the @ref TIM_ADV_EnableDMABurst().
 */
typedef struct
{
    TIM_ADV_DMABurstBaseAddr_Type    BaseAddr; /*!< The base address to start transfer. */
    TIM_ADV_DMABurstBaseLen_Type  Length;   /*!< Length of sequential registers DMA burst visits. */
} TIM_ADV_DMABurstConf_Type;

/*!
 * @brief This type of structure instance is used to setup the idle state output when calling the @ref TIM_ADV_EnableIdleOut().
 */
typedef struct
{
    TIM_ADV_PinPolarity_Type     PinPolarity; /*!< The output state of channel under idle mode. */
    TIM_ADV_PinPolarity_Type COMPPinPolarity; /*!< The output state of complementary channel under idle mode. */
} TIM_ADV_IdleOut_Type;

/*!
 * @brief This type of structure instance is used to setup the break in configuration when calling the @ref TIM_ADV_EnableBreakIn().
 */
typedef struct
{
    TIM_ADV_PinPolarity_Type     PinPolarity; /*!< The active edge of the break in signal. */
    bool AutoSwitchOutput; /*!< If input signal is inactive, switch the output compare at next update. */
    bool DirectIdleOutput; /*!< If enable, output the set idle state directly. */
} TIM_ADV_BreakIn_Type;

/*!
 * @brief Set the timer's step for indicated TIM module.
 *
 * @param TIMx TIM_ADV instance.
 * @param init Pointer to the initialization structure. See to @ref TIM_ADV_Init_Type.
 * @return val 'true' to set the timer's step successfully, 'false' to fail because the invalid StepFreqHz.
 */
bool TIM_ADV_Init(TIM_ADV_Type * TIMx, TIM_ADV_Init_Type * init);

/*!
 * @brief Start counting.
 *
 * @param TIMx TIM_ADV instance.
 * @return None.
 */
void TIM_ADV_Start(TIM_ADV_Type * TIMx);

/*!
 * @brief Stop counting immediately.
 *
 * @param TIMx TIM_ADV instance.
 * @return None.
 */
void TIM_ADV_Stop(TIM_ADV_Type * TIMx);

/*!
 * @brief Get the indicated TIMx Counter value.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @return The current value of the counter register.
 */
uint32_t TIM_ADV_GetCounterValue(TIM_ADV_Type * TIMx);

/*!
 * @brief Clear the indicated TIMx Counter.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @return None.
 */
void TIM_ADV_ClearCounterValue(TIM_ADV_Type * TIMx);

/*!
 * @brief Enable the TIM_ADV interrupts.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param interrupts Interrupts to be enabled.See to @ref TIM_ADV_INT.
 * @param enable 'true' to enable the indicated interrupts or DMAs, 'false' to disable the indicated interrupts or DMAs.
 * @return None.
 */
void TIM_ADV_EnableInterrupts(TIM_ADV_Type * TIMx, uint32_t interrupts, bool enable);

/*!
 * @brief Enable the TIM_ADV DMAs.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param dmas DMA masks to be enabled. See to @ref TIM_ADV_DMA.
 * @param enable 'true' to enable the indicated interrupts or DMAs, 'false' to disable the indicated interrupts or DMAs.
 * @return None.
 */
void TIM_ADV_EnableDMA(TIM_ADV_Type * TIMx, uint32_t dmas, bool enable);

/*!
 * @brief Software trigger events to call interrupts or DMAs.
 *
 * Can simultaneously trigger multiple events.
 *
 * @param TIMx TIM_ADV instance. See to @ref TIM_ADV_SWTRG.
 * @param swtrgs Trigger the events to generate interrupts.
 */
void TIM_ADV_DoSwTrigger(TIM_ADV_Type * TIMx, uint32_t swtrgs);

/*!
 * @brief Get the status of the indicated timer.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @return Interrupt status flags. See to @ref TIM_ADV_INT_STATUS.
 */
uint32_t TIM_ADV_GetInterruptStatus(TIM_ADV_Type * TIMx);

/*!
 * @brief Clear the status of indicated interrupt.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param status The required clear flag type. See to @ref TIM_ADV_INT_STATUS.
 * @return None.
 */
void TIM_ADV_ClearInterruptStatus(TIM_ADV_Type * TIMx, uint32_t status);

/*!
 * @brief Set up the output compare feature of indicated timer channel.
 *
 * If need to change the IO mode of the working channel, channel must be disabled first, then modify.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param channel Output channel instance. See to @ref TIM_ADV_CHANNEL_SELECTION.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_OutputCompareConf_Type.
 * @return None.
 */
void TIM_ADV_EnableOutputCompare(TIM_ADV_Type * TIMx, uint32_t channel, TIM_ADV_OutputCompareConf_Type * conf);

/*!
 * @brief Enable the TIM_ADV channel output for pulse generation.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param enable 'true' to enable the channel output, 'false' to disable the channel output.
 * @return None.
 */
void TIM_ADV_EnableOutputCompareSwitch(TIM_ADV_Type * TIMx, bool enable);

/*!
 * @brief Enable the input capture feature of indicated timer channel.
 *
 * If need to change the IO mode of the working channel, channel must be disabled first, then modify.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param channel Input channel instance. See to @ref TIM_ADV_CHANNEL_SELECTION.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_InputCaptureConf_Type.
 * @return None.
 */
void TIM_ADV_EnableInputCapture(TIM_ADV_Type * TIMx, uint32_t channel, TIM_ADV_InputCaptureConf_Type * conf);

/*!
 * @brief Get the value of the indicated timer channel.
 *
 * When capture event happens, counter value will be kept in its indicated channel.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param channel Channel instance to get the value. See to @ref TIM_ADV_CHANNEL_SELECTION.
 * @return Value of the indiacted timer channel.
 */
uint16_t TIM_ADV_GetChannelValue(TIM_ADV_Type * TIMx, uint32_t channel);

/*!
 * @brief Put the value into the indicated timer channel.
 *
 * When in output compare, channel value would be the compared with counter value.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param channel Channel instance to put the value. See to @ref TIM_ADV_CHANNEL_SELECTION.
 * @param value The value to be set in the indicated timer channel.
 * @return None.
 */
void TIM_ADV_PutChannelValue(TIM_ADV_Type * TIMx, uint32_t channel, uint16_t value);

/*!
 * @brief Enable the dead area of the indicated timer.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_DeadAreaConf_Type.
 * @return None.
 */
void TIM_ADV_EnableDeadArea(TIM_ADV_Type * TIMx, TIM_ADV_DeadAreaConf_Type * conf);

/*!
 * @brief Enable the master mode of the indicated timer.
 *
 * Master mode transfer the timer signal to other timers.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_MasterModeConf_Type.
 * @return None.
 */
void TIM_ADV_EnableMasterMode(TIM_ADV_Type * TIMx, TIM_ADV_MasterModeConf_Type * conf);

/*!
 * @brief Enable the slave mode of the indicated timer.
 *
 * Slave mode can control the working state of counter.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_SlaveModeConf_Type.
 * @return None.
 */
void TIM_ADV_EnableSlaveMode(TIM_ADV_Type * TIMx, TIM_ADV_SlaveModeConf_Type * conf);

/*!
 * @brief Enable the external trigger input of the indicated counter.
 *
 * External trigger signal will trigger counter do addition.
 * Its div and filter along with the counter StepFreqHz will affect.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_ExtTriggerInConf_Type.
 * @return None.
 */
void TIM_ADV_EnableExtTriggerIn(TIM_ADV_Type * TIMx, TIM_ADV_ExtTriggerInConf_Type * conf);

/*!
 * @brief Enable the dma burst transfer of the indicated timer.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_DMABurstConf_Type.
 * @return Address of DMA Burst transfer base register address.
 */
uint32_t TIM_ADV_EnableDMABurst(TIM_ADV_Type * TIMx, TIM_ADV_DMABurstConf_Type * conf);

/*!
 * @brief Get the encoder rotating direction and the counted encoder pulse times.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param value The counter value for pulse times.
 * @return Encoder rotating direction. See to @ref TIM_ADV_EncoderDirection_Type.
 */
TIM_ADV_EncoderDirection_Type TIM_ADV_GetEncoder(TIM_ADV_Type * TIMx, uint32_t * value);

/*!
 * @brief Set the indicated TIMx repetition counter value.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param value The repetition value to be set.
 * @return The current value of the counter register.
 */
void TIM_ADV_SetRepCounter(TIM_ADV_Type * TIMx, uint8_t value);

/*!
 * @brief Get the indicated TIMx Counter value.
 *
 * Real repetition's times number, meaning left repetition period times to run.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @return The current value of the counter register.
 */
uint8_t TIM_ADV_GetRepCounterValue(TIM_ADV_Type * TIMx);

/*!
 * @brief Set the channel idle state output when switch off the output compare.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param channel Channel instance to set the idle state output. See to @ref TIM_ADV_CHANNEL_SELECTION.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_IdleOut_Type.
 * @return None.
 */
void TIM_ADV_EnableIdleOut(TIM_ADV_Type * TIMx, uint32_t channel, TIM_ADV_IdleOut_Type * conf);

/*!
 * @brief Set the lock level for protecting the timer config setting.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param lock Lock level to be set for protecting Timer set. See to @ref TIM_ADV_LockLevel_Type.
 * @return None.
 */
void TIM_ADV_EnableLock(TIM_ADV_Type * TIMx, TIM_ADV_LockLevel_Type lock);

/*!
 * @brief Set the break input of the timer.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param conf Pointer to the configuration structure. See to @ref TIM_ADV_BreakIn_Type.
 * @return None.
 */
void TIM_ADV_EnableBreakIn(TIM_ADV_Type * TIMx, TIM_ADV_BreakIn_Type * conf);

/*!
 * @brief Set the PWM shift of the indicated channel.
 *
 * @param TIMx TIM_ADV_Type instance.
 * @param channel Channel instance to set the pwm shift. See to @ref TIM_ADV_CHANNEL_SELECTION.
 * @param value The counter time when need pwm output shift. If val equals the channel value, disable the shift.
 * @return None.
 */
void TIM_ADV_EnablePWMShift(TIM_ADV_Type * TIMx, uint32_t channel, uint16_t value);

/*!
 *@}
 */
#endif /* __HAL_TIM_ADV_H__ */

