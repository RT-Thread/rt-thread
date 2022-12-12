/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

#include "hal_common.h"

/*!
 * @addtogroup ADC
 * @{
 */

/*!
 * @brief ADC driver version number.
 */
#define ADC_DRIVER_VERSION 0u /*!< adc_0. */

/*!
 * @addtogroup ADC_STATUS
 * Define ADC status.
 * @{
 */

#define ADC_STATUS_CONV_SLOT_DONE   (1u << 0u) /*!< Status flag when ADC slot conversion done. */
#define ADC_STATUS_CONV_SAMPLE_DONE (1u << 1u) /*!< Status flag when ADC sample done. */
#define ADC_STATUS_CONV_SEQ_DONE    (1u << 2u) /*!< Status flag when ADC sequence conversion done. */
#define ADC_STATUS_COMPARE_DONE     (1u << 3u) /*!< Status flag when ADC compare done. */

/*!
 * @}
 */

/*!
 * @addtogroup ADC_INT
 * ADC interrupt define.
 * @{
 */

#define ADC_INT_CONV_SLOT_DONE   (1u << 0u)  /*!< Interrupt enable when when ADC slot conversion done. */
#define ADC_INT_CONV_SAMPLE_DONE (1u << 1u)  /*!< Interrupt enable when when ADC sample done. */
#define ADC_INT_CONV_SEQ_DONE    (1u << 2u)  /*!< Interrupt enable when when ADC sequence conversion done. */
#define ADC_INT_COMPARE_DONE     (1u << 3u)  /*!< Interrupt enable when when ADC compare done. */

/*!
 * @}
 */

/*!
 * @addtogroup ADC_RESULT_FLAGS
 * Define ADC Convert result flags.
 * @{
 */

#define ADC_CONV_RESULT_FLAG_OVERRUN (1u << 0u) /*!< Result flag when adc conversion result is overrun. */
#define ADC_CONV_RESULT_FLAG_VALID   (1u << 1u) /*!< Result flag when adc conversion result valid. */

/*!
 * @}
 */

/*!
 * @brief ADC Resolution type.
 *
 * Select ADC conversion valid data bit.
 */
typedef enum
{
    ADC_Resolution_12b = 0u,  /*!< Resolution select 12 bit. */
    ADC_Resolution_11b = 1u,  /*!< Resolution select 11 bit. */
    ADC_Resolution_10b = 2u,  /*!< Resolution select 10 bit. */
    ADC_Resolution_9b  = 3u,  /*!< Resolution select 9 bit.  */
    ADC_Resolution_8b  = 4u,  /*!< Resolution select 8 bit.  */
} ADC_Resolution_Type;

/*!
 * @brief ADC Prescaler type.
 *
 * Select the prescaler of the bus as the adc clock.
 */
typedef enum
{
    ADC_ClockDiv_2  = 0u,   /*!< ADC clock divided by 2.  */
    ADC_ClockDiv_3  = 1u,   /*!< ADC clock divided by 3.  */
    ADC_ClockDiv_4  = 2u,   /*!< ADC clock divided by 4.  */
    ADC_ClockDiv_5  = 3u,   /*!< ADC clock divided by 5.  */
    ADC_ClockDiv_6  = 4u,   /*!< ADC clock divided by 6.  */
    ADC_ClockDiv_7  = 5u,   /*!< ADC clock divided by 7.  */
    ADC_ClockDiv_8  = 6u,   /*!< ADC clock divided by 8.  */
    ADC_ClockDiv_9  = 7u,   /*!< ADC clock divided by 9.  */
    ADC_ClockDiv_10 = 8u,   /*!< ADC clock divided by 10. */
    ADC_ClockDiv_11 = 9u,   /*!< ADC clock divided by 11. */
    ADC_ClockDiv_12 = 10u,  /*!< ADC clock divided by 12. */
    ADC_ClockDiv_13 = 11u,  /*!< ADC clock divided by 13. */
    ADC_ClockDiv_14 = 12u,  /*!< ADC clock divided by 14. */
    ADC_ClockDiv_15 = 13u,  /*!< ADC clock divided by 15. */
    ADC_ClockDiv_16 = 14u,  /*!< ADC clock divided by 16. */
    ADC_ClockDiv_17 = 15u,  /*!< ADC clock divided by 17. */
} ADC_ClockDiv_Type;

/*!
 * @brief ADC HwTrgEdge type.
 *
 * Use hardware trigger in ADC, select the trigger edge to trigger adc.
 */
typedef enum
{
    ADC_HwTrgEdge_Both     = 0u,   /*!< Both edge trigger.        */
    ADC_HwTrgEdge_Falling  = 1u,   /*!< Falling edge trigger.     */
    ADC_HwTrgEdge_Rising   = 2u,   /*!< Rising edge trigger.      */
    ADC_HwTrgEdge_Disabled = 3u,   /*!< Edge trigger is disabled. */
} ADC_HwTrgEdge_Type;

/*!
 * @brief ADC HwTrgDelayCycle type.
 *
 * After the hardware trigger signal is generated, delay N PCLK2 clock cycles before starting the first sample.
 */
typedef enum
{
    ADC_HwTrgDelayCycle_0   = 0u,    /*!< Delay 0 cycle.    */
    ADC_HwTrgDelayCycle_4   = 1u,    /*!< Delay 4  cycle.   */
    ADC_HwTrgDelayCycle_16  = 2u,    /*!< Delay 16 cycle.   */
    ADC_HwTrgDelayCycle_32  = 3u,    /*!< Delay 32 cycle.   */
    ADC_HwTrgDelayCycle_64  = 4u,    /*!< Delay 64 cycle.   */
    ADC_HwTrgDelayCycle_128 = 5u,    /*!< Delay 128  cycle. */
    ADC_HwTrgDelayCycle_256 = 6u,    /*!< Delay 256 cycle.  */
    ADC_HwTrgDelayCycle_512 = 7u,    /*!< Delay 512 cycle.  */
} ADC_HwTrgDelayCycle_Type;

/*!
 * @brief ADC Align type.
 *
 * Choose to store the converted data as left-aligned or right-aligned.
 */
typedef enum
{
    ADC_Align_Right = 0u,     /*!< Data right align. */
    ADC_Align_Left  = 1u,     /*!< Data left align.  */
} ADC_Align_Type;

/*!
 * @brief ADC RegularSeqDirection type.
 *
 * In single-cycle scan or continuous scan mode, set the order of scan channels.
 */
typedef enum
{
    ADC_RegSeqDirection_LowFirst  = 0u,   /*!< ADC scan direction from low channel to high channel. */
    ADC_RegSeqDirection_HighFirst = 1u,   /*!< ADC scan direction from high channel to low channel. */
} ADC_RegSeqDirection_Type;

/*!
 * @brief ADC ConvMode type.
 *
 * Select the adc channel or sequence convert mode.
 */
typedef enum
{
    ADC_ConvMode_SingleSlot = 0u,    /*!< Run the conversion by channel.  */
    ADC_ConvMode_Seq = 1u,           /*!< Run the conversion by sequence. */
    ADC_ConvMode_SeqContinues = 2u,  /*!< Run the conversion by sequence again and again. */
} ADC_ConvMode_Type;

/*!
 * @brief ADC HwTrgSel type.
 *
 * Select ADC hardware trigger source.
 */
typedef enum
{
    ADC_HwTrgSource_Alt0 = 0u,   /*!< source 0   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt1 = 1u,   /*!< source 1   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt2 = 2u,   /*!< source 2   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt3 = 3u,   /*!< source 3   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt4 = 4u,   /*!< source 4   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt5 = 5u,   /*!< source 5   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt6 = 6u,   /*!< source 6   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt7 = 7u,   /*!< source 7   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt8 = 8u,   /*!< source 8   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt9 = 9u,   /*!< source 9   as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt10 = 10u, /*!< source 10  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt11 = 11u, /*!< source 11  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt12 = 12u, /*!< source 12  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt13 = 13u, /*!< source 13  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt14 = 14u, /*!< source 14  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt15 = 15u, /*!< source 15  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt16 = 16u, /*!< source 16  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt17 = 17u, /*!< source 17  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt18 = 18u, /*!< source 18  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt19 = 19u, /*!< source 19  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt20 = 20u, /*!< source 20  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt21 = 21u, /*!< source 21  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt22 = 22u, /*!< source 22  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt23 = 23u, /*!< source 23  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt24 = 24u, /*!< source 24  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt25 = 25u, /*!< source 25  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt26 = 26u, /*!< source 26  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt27 = 27u, /*!< source 27  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt28 = 28u, /*!< source 28  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt29 = 29u, /*!< source 29  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt30 = 30u, /*!< source 30  as an external trigger source for ADC . */
    ADC_HwTrgSource_Alt31 = 31u, /*!< source 31  as an external trigger source for ADC . */
} ADC_HwTrgSource_Type;

/*!
 * @brief ADC SampleTime type.
 *
 * Select channel sample time.
 */
typedef enum
{
    ADC_SampleTime_Alt0 = 0u,    /*!< Channel sample time mode  0 . */
    ADC_SampleTime_Alt1 = 1u,    /*!< Channel sample time mode  1 . */
    ADC_SampleTime_Alt2 = 2u,    /*!< Channel sample time mode  2 . */
    ADC_SampleTime_Alt3 = 3u,    /*!< Channel sample time mode  3 . */
    ADC_SampleTime_Alt4 = 4u,    /*!< Channel sample time mode  4 . */
    ADC_SampleTime_Alt5 = 5u,    /*!< Channel sample time mode  5 . */
    ADC_SampleTime_Alt6 = 6u,    /*!< Channel sample time mode  6 . */
    ADC_SampleTime_Alt7 = 7u,    /*!< Channel sample time mode  7 . */
    ADC_SampleTime_Alt8 = 8u,    /*!< Channel sample time mode  8 . */
    ADC_SampleTime_Alt9 = 9u,    /*!< Channel sample time mode  9 . */
    ADC_SampleTime_Alt10 = 10u,  /*!< Channel sample time mode  10. */
    ADC_SampleTime_Alt11 = 11u,  /*!< Channel sample time mode  11. */
    ADC_SampleTime_Alt12 = 12u,  /*!< Channel sample time mode  12. */
    ADC_SampleTime_Alt13 = 13u,  /*!< Channel sample time mode  13. */
    ADC_SampleTime_Alt14 = 14u,  /*!< Channel sample time mode  14. */
    ADC_SampleTime_Alt15 = 15u,  /*!< Channel sample time mode  15. */
} ADC_SampleTime_Type;

/*!
 * @brief This type of structure instance is used to keep the settings
 *  when calling the @ref ADC_Init() to initialize the ADC module.
 */
typedef struct
{
    ADC_Resolution_Type Resolution;   /*!< Specify the available bits for the conversion result data. */
    ADC_ClockDiv_Type ClockDiv;       /*!< Specify the adc clock divison. */
    ADC_Align_Type Align;             /*!< Specify the data alignment. */
    ADC_ConvMode_Type ConvMode;       /*!< Specify the adc conversion mode. */
} ADC_Init_Type;

/*!
 * @brief This type of structure instance is used to keep the settings
 *  when calling the @ref ADC_EnableHwTrigger() to initialize the ADC hardware trigger module.
 */
typedef struct
{
    ADC_HwTrgSource_Type     Source;      /*!< Select the ADC hardware trigger source. */
    ADC_HwTrgEdge_Type       Edge;        /*!< Select the trigger edge. */
    ADC_HwTrgDelayCycle_Type DelayCycle;  /*!< Select the hardware trigger shift sample. */
} ADC_HwTrgConf_Type;

/*!
 * @brief This type of structure instance is used to keep the settings
 *  when calling the @ref ADC_EnableRegSeq() to initialize the ADC regular sequence module.
 */
typedef struct
{
    uint32_t SeqSlots;              /*!< Select the slots length. */
    ADC_RegSeqDirection_Type SeqDirection;  /*!< Select the regular sequence sacn direction. */
} ADC_RegSeqConf_Type;

/*!
 * @brief This type of structure instance is used to keep the settings
 *  when calling the @ref ADC_EnableAnySeq() to initialize the ADC Any sequence mode.
 */
typedef struct
{
    uint32_t   SeqLen;      /*!< Select the slots length. */
    uint32_t * SeqChannels; /*!< Select the channel, channel can be disorder. */
} ADC_AnySeqConf_Type;


/*!
 * @brief This type of structure instance is used to keep the settings
 * when calling the @ref ADC_EnableHwCompare() to enable the ADC windows compare mode.
 */
typedef struct
{
    uint32_t ChnNum;        /*!< Select the channel number binding to the compare. */
    uint32_t HighLimit;     /*!< The comparator high limit. */
    uint32_t LowLimit;      /*!< The comparator low limit. */
} ADC_HwCompConf_Type;

/*!
 * @brief Initialize the ADC module.
 *
 * @param ADCx ADC instance.
 * @param init  Pointer to the initialization structure. See to @ref ADC_Init_Type.
 * @return None.
 */
void       ADC_Init(ADC_Type * ADCx, ADC_Init_Type * init);

/*!
 * @brief Enable the ADC module.
 *
 * The ADC module should be enabled before conversion data.
 *
 * @param ADCx ADC instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void       ADC_Enable(ADC_Type * ADCx, bool enable);

/*!
 * @brief Enable Temperature sensor from the ADC module.
 *
 * The module should be enabled when Using the built-in temperature sensor to
 * detect temperature changes inside the device.
 *
 * @param ADCx ADC instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void       ADC_EnableTempSensor(ADC_Type * ADCx, bool enable);

/*!
 * @brief Enable Voltage sensor from the ADC module.
 *
 * The module should be enabled when using internal reference voltage .
 *
 * @param ADCx ADC instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void       ADC_EnableVoltSensor(ADC_Type * ADCx, bool enable);

/*!
 * @brief Enable the DMA from the ADC module.
 *
 * @param ADCx ADC instance.
 * @param enable 'true' to enable the DMA, 'false' to disable the DMA.
 * @return None.
 */
void       ADC_EnableDMA(ADC_Type * ADCx, bool enable);

/*!
 * @brief Enable interrupts of the ADC module.
 *
 * @param ADCx ADC instance.
 * @param interrupts Interrupt code masks.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void       ADC_EnableInterrupts(ADC_Type * ADCx, uint32_t interrupts, bool enable);

/*!
 * @brief Get the current status flags of the ADC module.
 *
 * @param ADCx ADC instance.
 * @return Status flags.
 */
uint32_t   ADC_GetStatus(ADC_Type * ADCx);

/*!
 * @brief Clear the status flags of the ADC module.
 *
 * @param ADCx ADC instance.
 * @param flags  The mask codes of the indicated interrupt flags to be cleared.
 * @return None.
 */
void       ADC_ClearStatus(ADC_Type * ADCx, uint32_t flags);

/*!
 * @brief Get the channel convert data from the ADC module.
 *
 * @param ADCx ADC instance.
 * @param channel The convert channel.
 * @param flags The ADC convert result flags. See to @ref ADC_RESULT_FLAGS.
 * @return The data value.
 */
uint32_t   ADC_GetConvResult(ADC_Type * ADCx, uint32_t * channel, uint32_t * flags);

/*!
 * @brief Get the indication channel current data from the ADC module.
 *
 * @param ADCx ADC instance.
 * @param channel the adc channel.
 * @param flags The ADC convert result flags. See to @ref ADC_RESULT_FLAGS.
 * @return The data value.
 */
uint32_t   ADC_GetChnConvResult(ADC_Type * ADCx, uint32_t channel, uint32_t * flags);


/*!
 * @brief Configuration channel sample time of the ADC module.
 *
 * @param ADCx ADC instance.
 * @param channel  the adc convert channel.
 * @param sampletime  the adc channel sample time
 * @return None.
 */
void       ADC_SetChnSampleTime(ADC_Type * ADCx, uint32_t channel, ADC_SampleTime_Type sampletime);

/*!
 * @brief Enable regular sequence from the ADC module.
 *
 * The ADC module should be enabled before regular sequence function.
 * it also have interrupt.
 *
 * @param ADCx ADC instance.
 * @param conf Pointer to the initialization structure. See to @ref ADC_RegSeqConf_Type.
 * @return None.
 */
void       ADC_EnableRegSeq(ADC_Type * ADCx, ADC_RegSeqConf_Type * conf);

/*!
 * @brief Enable hardware trigger from the ADC module.
 *
 * The ADC module should be enabled before using hardware trrigger function.
 * it also have interrupt.
 *
 * @param ADCx ADC instance.
 * @param conf Select the hardware trigger source. See to @ref ADC_HwTrgConf_Type.
 * @return None.
 */
void       ADC_EnableHwTrigger(ADC_Type * ADCx, ADC_HwTrgConf_Type * conf);

/*!
 * @brief Enable Any sequence from the ADC module.
 *
 * The ADC module should be enabled before Any sequence function.
 * it also have interrupt.
 *
 * @param ADCx ADC instance.
 * @param conf Pointer to the initialization structure. See to @ref ADC_AnySeqConf_Type.
 * @return None.
 */
void       ADC_EnableAnySeq(ADC_Type * ADCx, ADC_AnySeqConf_Type * conf);

/*!
 * @brief Enable window comparison from the ADC module.
 *
 * The ADC module should be enabled before using analog watchdog function.
 * it also have interrupt.
 *
 * @param ADCx ADC instance.
 * @param conf Pointer to the initialization structure. See to @ref ADC_HwCompareConf_Type.
 * @return None.
 */
void       ADC_EnableHwComp(ADC_Type * ADCx, ADC_HwCompConf_Type * conf);

/*!
 * @brief Do soft trigger.
 *
 * @param ADCx ADC instance.
 * @param enable 'true' to enable the ADC start convert, 'false' to disable.
 * @return None.
 */
void       ADC_DoSwTrigger(ADC_Type * ADCx, bool enable);

/*!
 *@}
 */

#endif /*__HAL_ADC_H__. */

