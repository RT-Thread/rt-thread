/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_QUADTMR_HAL_H__)
#define __FSL_QUADTMR_HAL_H__

#include "fsl_device_registers.h"
#include <stdbool.h>
#include <assert.h>

#if FSL_FEATURE_SOC_TMR_COUNT

/*!
 * @addtogroup quadtmr_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Quad Timer primary clock source selection*/
typedef enum _quadtmr_pri_count_source
{
    kQuadTmrCntr0InpPin = 0,
    kQuadTmrCntr1InpPin,
    kQuadTmrCntr2InpPin,
    kQuadTmrCntr3InpPin,
    kQuadTmrCntr0Out,
    kQuadTmrCntr1Out,
    kQuadTmrCntr2Out,
    kQuadTmrCntr3Out,
    kQuadTmrClkDiv1,
    kQuadTmrClkDiv2,
    kQuadTmrClkDiv4,
    kQuadTmrClkDiv8,
    kQuadTmrClkDiv16,
    kQuadTmrClkDiv32,
    kQuadTmrClkDiv64,
    kQuadTmrClkDiv128
}quadtmr_pri_count_source_t;

/*! @brief Quad Timer input sources selection*/
typedef enum _quadtmr_input_source
{
    kQuadTmr0InpPin = 0,
    kQuadTmr1InpPin,
    kQuadTmr2InpPin,
    kQuadTmr3InpPin
}quadtmr_input_source_t;

/*! @brief Quad Timer counting mode selection */
typedef enum _quadtmr_counting_mode
{
    kQuadTmrCntNoOper = 0,  /*!< No operation */
    kQuadTmrCntPriSrcRiseEdge, /*!< Count rising edges or primary source */
    kQuadTmrCntPriSrcRiseAndFallEdge, /*!< Count rising and falling edges of primary source */
    kQuadTmrCntPriSrcRiseEdgeSecInpHigh, /*!< Count rise edges of pri SRC while sec inp high active */
    kQuadTmrQuadCntMode, /*!< Quadrature count mode, uses pri and sec sources */
    kQuadTmrCntPriSrcRiseEdgeSecDir, /*!< Count rising edges of pri SRC; sec SRC specifies dir */
    kQuadTmrSecSrcTrigPriCnt, /*!< Edge of sec SRC trigger primary count until compare*/
    kQuadTmrCascadeCnt /*!< Cascaded count mode (up/down) */
}quadtmr_counting_mode_t;

/*! @brief Quad Timer output mode selection*/
typedef enum _quadtmr_output_mode
{
    kQuadTmrAssertWhenCntActive = 0, /*!< Assert OFLAG while counter is active*/
    kQuadTmrClearOnCompare, /*!< Clear OFLAG on successful compare */
    kQuadTmrSetOnCompare, /*!< Set OFLAG on successful compare */
    kQuadTmrTogOnCompare, /*!< Toggle OFLAG on successful compare */
    kQuadTmrTogOnAltCompReg, /*!< Toggle OFLAG using alternating compare registers */
    kQuadTmrSetOnCompareClearOnSecSrcInp, /*!< Set OFLAG on compare, clear on sec SRC input edge */
    kQuadTmrSetOnCompareClearOnCntRoll, /*!< Set OFLAG on compare, clear on counter roll over */
    kQuadTmrEnableGateClk /*!< Enable gated clock output while count is active */
}quadtmr_output_mode_t;

/*! @brief Quad Timer input capture edge mode, rising edge, or falling edge */
typedef enum _quadtmr_input_capture_edge_mode_t
{
   kQuadTmrNoCapture = 0, /*!< Capture is disabled */
   kQuadTmrRisingEdge, /*!< Capture on rising edge (IPS=0) or falling edge (IPS=1)*/
   kQuadTmrFallingEdge, /*!< Capture on falling edge (IPS=0) or rising edge (IPS=1)*/
   kQuadTmrRisingAndFallingEdge  /*!< Capture on both edges */
}quadtmr_input_capture_edge_mode_t;

/*! @brief Quad Timer input capture edge mode, rising edge, or falling edge */
typedef enum _quadtmr_preload_control_t
{
   kQuadTmrNoPreload = 0, /*!< Never preload */
   kQuadTmrLoadOnComp1, /*!< Load upon successful compare with value in COMP1 */
   kQuadTmrLoadOnComp2, /*!< Load upon successful compare with value in COMP2*/
   kQuadTmrReserved
}quadtmr_preload_control_t;

/*! @brief Quad Timers status */
typedef enum _quadtmr_status {
    kStatusQuadTmrSuccess = 0U, /*!< Quad Timer success status.*/
    kStatusQuadTmrError = 1U    /*!< Quad Timer error status.*/
} quadtmr_status_t;

/*! @brief Quad Timer counter parameters*/
typedef struct QuadTmrCounterParams
{
    uint16_t counterVal;     /*!< Value to be written to the counter register */
    uint16_t counterLoadVal; /*!< Value to be loaded into the counter on compare or overflow */
    uint16_t countUpCompareVal;  /*!< Value to be written to the count up compare register */
    uint16_t countDownCompareVal; /*!< Value to be written to the count down compare register */
    quadtmr_pri_count_source_t primarySrc; /*!< Specify the primary count source */
    quadtmr_input_source_t secondarySrc; /*!< Specify the secondary count source */
    bool countOnce; /*!< true: if counter should stop on compare, false: to run repeatedly */
    bool countLength; /*!< true: re-initialize on compare match, false: count till roll-over */
    bool countDir; /*!< true: Count down, false: Count up */
}quadtmr_counter_params_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the Quad Timer registers.
 *
 * @param base The Quad Timer base address pointer
 */
void QUADTMR_HAL_Init(TMR_Type *base);

/*!
 * @brief Sets the Quad Timer's counter properties.
 *
 * The primary source and, in some cases, the secondary clock control incrementing the counter.
 * The parameters provided by the user set up counter properties, such as match value,
 * roll over behavior, and direction.
 * The function does not start the counter. The user has to make a separate call to the
 * QUADTMR_HAL_SetCountMode to set count mode.
 *
 * @param base The Quad Timer base address pointer
 * @param params  Used to setup the counter behaviour.
 * @param src_polarity true: Source clock is inverted, false: no inversion of the input signal
 */
void QUADTMR_HAL_SetupCounter(TMR_Type *base, quadtmr_counter_params_t *params, bool src_polarity);

/*!
 * @brief Enables the user to write a value out on the OFLAG pin.
 *
 * @param base The Quad Timer base address pointer
 * @param val  true: high value is written, false: low value is written
 * @param pol  true: invert polarity of the output signal, false: no inversion
 */
void QUADTMR_HAL_ForceOutVal(TMR_Type *base, bool val, bool pol);

/*!
 * @brief Enables the user to output a certain number of pulses.
 *
 * The number of pulses to be output is provided as an argument. The output pulse stream has
 * the same frequency as the source clock provided.
 *
 * @param base The Quad Timer base address pointer
 * @param numOfPulses  The number of pulses to be outputted on the OFLAG pin
 * @param src Source clock for the counter that is used to generate the pulse stream
 */
void QUADTMR_HAL_OutPulses(TMR_Type *base, uint16_t numOfPulses, quadtmr_pri_count_source_t src);

/*!
 * @brief Outputs a PWM signal on the OFLAG pin.
 *
 * The high and low pulse width values should be a count in terms of number of source
 * clock cycles. The user has to calculate these values based on the source clock frequency,
 * desired PWM frequency, and duty cycle.
 *
 * @param base The Quad Timer base address pointer
 * @param src Source clock for the counter that is used to generate the PWM signal
 * @param highPulseCount Specify the number of source clock cycles to get the high period
 * @param lowPulseCount PulseCount Specify the number of source clock cycles to get the low period
 */
void QUADTMR_HAL_OutPwmSignal(TMR_Type *base, quadtmr_pri_count_source_t src,
                                          uint16_t highPulseCount, uint16_t lowPulseCount);

/*!
 * @brief Allows the user to count the source clock cycles until a capture event arrives.
 *
 * The count is stored in the capture register.
 *
 * @param base The Quad Timer base address pointer
 * @param countSrc Source clock for the counter
 * @param captureSrc Pin through which we receive the input signal to trigger the capture
 * @param reloadCntrOnCap true: reload the counter when an input capture occurs, false: no reload
 * @param mode Specifies which edge of the input signal  triggers a capture
 * @param inputPol true: invert polarity of the input signal, false: no inversion
 */
void QUADTMR_HAL_SetupInputCapture(TMR_Type *base, quadtmr_pri_count_source_t countSrc,
                                              quadtmr_input_source_t captureSrc, bool reloadCntrOnCap,
                                              quadtmr_input_capture_edge_mode_t mode, bool inputPol);

/*!
 * @brief Sets up the Quad Timer compare preload feature.
 *
 * @param base The Quad Timer base address pointer
 * @param compareRegNum Options are 1 or 2, 1=COMP1; 2=COMP2
 * @param preloadVal Value to be written to the comparators preload register
 * @param preloadProps Controls when a compare register is preloaded with the value from the preload reg.
 */
void QUADTMR_HAL_SetupComparePreload(TMR_Type *base, uint8_t compareRegNum, uint16_t preloadVal,
                                                  quadtmr_preload_control_t preloadProps);

/*!
 * @brief Sets the Quad Timer current counter value.
 *
 * @param base The Quad Timer base address pointer
 * @param val  Quad Timer counter value to be set
 */
static inline void  QUADTMR_HAL_SetCounter(TMR_Type *base, uint16_t val)
{
    TMR_WR_CNTR(base, val);
}

/*!
 * @brief Sets the Quad Timer compare register 1 value used in count up mode.
 *
 * @param base The Quad Timer base address pointer
 * @param val The value to be set
 */
static inline void QUADTMR_HAL_SetComp1Val(TMR_Type *base, uint16_t val)
{
    TMR_WR_COMP1(base, val);
}

/*!
 * @brief Sets up the preload register for Quad Timer compare 1 register.
 *
 * @param base The Quad Timer base address pointer
 * @param val The value to be set
 */
static inline void QUADTMR_HAL_SetComp1PreloadVal(TMR_Type *base, uint16_t val)
{
    TMR_WR_CMPLD1(base, val);
}

/*!
 * @brief Sets the Quad Timer compare register 2 value used in count up mode.
 *
 * @param base The Quad Timer base address pointer
 * @param val The value to be set
 */
static inline void QUADTMR_HAL_SetComp2Val(TMR_Type *base, uint16_t val)
{
    TMR_WR_COMP2(base, val);
}

/*!
 * @brief Sets up the preload register for Quad Timer compare 2 register.
 *
 * @param base The Quad Timer base address pointer
 * @param val The value to be set
 */
static inline void QUADTMR_HAL_SetComp2PreloadVal(TMR_Type *base, uint16_t val)
{
    TMR_WR_CMPLD2(base, val);
}

/*!
 * @brief Sets the Quad Timer counter initial value.
 *
 * @param base The Quad Timer base address pointer
 * @param val initial value to be set
 */
static inline void QUADTMR_HAL_SetLoadVal(TMR_Type *base, uint16_t val)
{
    TMR_WR_LOAD(base, val);
}

/*!
 * @brief Returns the Quad Timer peripheral hold register value.
 *
 * @param base The Quad Timer base address pointer
 * @return Quad Timer hold value
 */
static inline uint16_t QUADTMR_HAL_GetHoldVal(TMR_Type *base)
{
    return TMR_RD_HOLD(base);
}

/*!
 * @brief Gets the Quad Timer peripherals counter capture value.
 *
 * @param base The Quad Timer base address pointer
 * @return Returns the value captured from the counter
 */
static inline uint16_t QUADTMR_HAL_GetCaptureVal(TMR_Type *base)
{
    return TMR_RD_CAPT(base);
}

/*!
 * @brief Gets the Quad Timer peripherals counter value.
 *
 * @param base The Quad Timer base address pointer
 * @return Returns the counter value
 */
static inline uint16_t QUADTMR_HAL_GetCounterVal(TMR_Type *base)
{
    return TMR_RD_CNTR(base);
}

/*!
 * @brief Sets up the Quad Timer counter mode.
 *
 * @param base The Quad Timer base address pointer
 * @param mode Count mode, options available in quadtmr_counting_mode_t enum
 */
static inline void QUADTMR_HAL_SetCountMode(TMR_Type *base, quadtmr_counting_mode_t mode)
{
    TMR_BWR_CTRL_CM(base, mode);
}

/*!
 * @brief Sets up the Quad Timer primary count source.
 *
 * @param base The Quad Timer base address pointer
 * @param src Primary count source, options available in the quadtmr_pri_count_source_t enum
 */
static inline void QUADTMR_HAL_SetPriCountSrc(TMR_Type *base, quadtmr_pri_count_source_t src)
{
    TMR_BWR_CTRL_PCS(base, src);
}

/*!
 * @brief Sets up the Quad Timer secondary count source.
 *
 * @param base The Quad Timer base address pointer
 * @param src Secondary count source, options available in the quadtmr_input_source_t enum
 */
static inline void QUADTMR_HAL_SetSecCountSrc(TMR_Type *base, quadtmr_input_source_t src)
{
    TMR_BWR_CTRL_SCS(base, src);
}

/*!
 * @brief Sets up the count once bit.
 *
 * @param base The Quad Timer base address pointer
 * @param once true: count until compare and then stop, false: count repeatedly
 */
static inline void QUADTMR_HAL_SetCountOnceCmd(TMR_Type *base, bool once)
{
    TMR_BWR_CTRL_ONCE(base, once);
}

/*!
 * @brief Sets up the Quad Timer output mode.
 *
 * @param base The Quad Timer base address pointer
 * @param mode Output mode, options available in the quadtmr_output_mode_t enum
 */
static inline void QUADTMR_HAL_SetOutputMode(TMR_Type *base, quadtmr_output_mode_t mode)
{
    TMR_BWR_CTRL_OUTMODE(base, mode);
}

/*!
 * @brief Modifies the Quad Timer input polarity select bit.
 *
 * @param base The Quad Timer base address pointer
 * @param ips true: inverts the input signal polarity, false: no inversion
 */
static inline void QUADTMR_HAL_SetInputPolSelCmd(TMR_Type *base, bool ips)
{
    TMR_BWR_SCTRL_IPS(base, ips);
}

/*!
 * @brief Reads the Quad Timer external input signal bit.
 *
 * @param base The Quad Timer base address pointer
 * @return Returns the current state of the external input pin selected via the sec. count source
 */
static inline bool QUADTMR_HAL_GetExtInputSignal(TMR_Type *base)
{
    return TMR_BRD_SCTRL_INPUT(base);
}

/*!
 * @brief Sets the Quad Timer input capture mode.
 *
 * @param base The Quad Timer base address pointer
 * @param mode Capture mode, options specified in the quadtmr_input_capture_edge_mode_t enum
 */
static inline void QUADTMR_HAL_SetCaptureMode(TMR_Type *base, quadtmr_input_capture_edge_mode_t mode)
{
    TMR_BWR_SCTRL_CAPTURE_MODE(base, mode);
}

/*!
 * @brief Modifies the value for the Quad Timer output enable bit.
 *
 * @param base The Quad Timer base address pointer
 * @param enable true: OFLAG output signal driven on pin, false: External pin configured as input
 */
static inline void QUADTMR_HAL_SetOutEnableCmd(TMR_Type *base, bool enable)
{
    TMR_BWR_SCTRL_OEN(base, enable);
}

/*!
 * @brief Sets the input filter sample count.
 *
 * @param base The Quad Timer base address pointer
 * @param cnt Input filter sample count
 */
static inline void QUADTMR_HAL_SetInputFilterCnt(TMR_Type *base, uint8_t cnt)
{
    TMR_BWR_FILT_FILT_CNT(base, cnt);
}

/*!
 * @brief Sets the input filter sample period.
 *
 * @param base The Quad Timer base address pointer
 * @param period Input filter sample period
 */
static inline void QUADTMR_HAL_SetInputFilterPeriod(TMR_Type *base, uint8_t period)
{
    TMR_BWR_FILT_FILT_PER(base, period);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_TMR_COUNT */

#endif /* __FSL_QUADTMR_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

