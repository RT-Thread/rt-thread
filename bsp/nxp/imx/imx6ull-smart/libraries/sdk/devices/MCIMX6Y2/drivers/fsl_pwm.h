/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
#ifndef _FSL_PWM_H_
#define _FSL_PWM_H_

#include "fsl_common.h"

/*!
 * @addtogroup pwm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_PWM_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0 */
/*@}*/

/*! @brief PWM clock source select. */
typedef enum _pwm_clock_source
{
    KPWM_PERIPHERAL_CLOCK = 0U,  /*!< The Peripheral clock is used as the clock */
    KPWM_HIGH_FREQUENCY_CLOCK,    /*!< High-frequency reference clock is used as the clock */
    KPWM_LOW_FREQUENCY_CLOCK      /*!< Low-frequency reference clock(32KHz) is used as the clock */
} pwm_clock_source_t;

/*!
 * @brief PWM FIFO water mark select.
 * Sets the data level at which the FIFO empty flag will be set
 */
typedef enum _pwm_fifo_water_mark
{
    KPWM_FIFO_WATERMARK_1 = 0U,  /*!< FIFO empty flag is set when there are more than or equal to 1 empty slots */
    KPWM_FIFO_WATERMARK_2,       /*!< FIFO empty flag is set when there are more than or equal to 2 empty slots */
    KPWM_FIFO_WATERMARK_3,       /*!< FIFO empty flag is set when there are more than or equal to 3 empty slots */
    KPWM_FIFO_WATERMARK_4        /*!< FIFO empty flag is set when there are more than or equal to 4 empty slots */
} pwm_fifo_water_mark_t;

/*!
 * @brief PWM byte data swap select.
 * It determines the byte ordering of the 16-bit data when it goes into the FIFO from the sample register.
 */
typedef enum _pwm_byte_data_swap
{
    KPWM_BYTE_NO_SWAP = 0U,       /*!< byte ordering remains the same */
    KPWM_BYTE_SWAP               /*!< byte ordering is reversed */
} pwm_byte_data_swap_t;

/*! @brief PWM half-word data swap select. */
typedef enum _pwm_half_word_data_swap
{
    KPWM_HALF_WORD_NO_SWAP = 0U,   /*!< Half word swapping does not take place */
    KPWM_HALF_WORD_SWAP           /*!< Half word from write data bus are swapped */
} pwm_half_word_data_swap_t;

/*! @brief PWM Output Configuration */
typedef enum _pwm_output_configuration
{
    KPWM_SET_AT_ROLLOVER_AND_CLEAR_AT_COMPARISON = 0U,    /*!< Output pin is set at
                                                                rollover and cleared at comparison */
    KPWM_CLEAR_AT_ROLLOVER_AND_SET_AT_COMPARISON,         /*!< Output pin is
                                                                cleared at rollover and set at comparison */
    KPWM_NO_CONFIGURE        /*!< PWM output is disconnected */
} pwm_output_configuration_t;

/*!
 * @brief PWM FIFO sample repeat
 * It determines the number of times each sample from the FIFO is to be used.
 */
typedef enum _pwm_sample_repeat
{
    KPMW_EACH_SAMPLE_ONCE = 0u,       /*!< Use each sample once */
    KPWM_EACH_SAMPLE_TWICE,           /*!< Use each sample twice */
    KPWM_EACH_SAMPLE_FOUR_TIMES,       /*!< Use each sample four times */
    KPWM_EACH_SAMPLE_EIGHT_TIMES       /*!< Use each sample eight times */
} pwm_sample_repeat_t;

/*! @brief List of PWM interrupt options */
typedef enum _pwm_interrupt_enable
{
    KPWM_FIFO_EMPTY_INTERRUPT_ENABLE = (1U << 0),  /*!< This bit controls the generation of the FIFO Empty interrupt. */
    KPWM_ROLLOVER_INTERRUPT_ENABLE = (1U << 1),   /*!< This bit controls the generation of the Rollover interrupt. */
    KPWM_CMPARE_INTERRUPT_ENABLE = (1U << 2)     /*!< This bit controls the generation of the Compare interrupt */
} pwm_interrupt_enable_t;

/*! @brief List of PWM status flags */
typedef enum _pwm_status_flags
{
    KPWM_FIFO_EMPTY_FLAG = (1U << 3),         /*!< This bit indicates the FIFO data level in comparison to the water
                                                    level set by FWM field in the control register. */
    KPWM_ROLLOVER_FLAG = (1U << 4),          /*!< This bit shows that a roll-over event has occurred. */
    KPWM_COMPARE_FLAG = (1U << 5),           /*!< This bit shows that a compare event has occurred. */
    KPWM_FIFO_WRITE_ERROR_FLAG = (1U << 6)     /*!< This bit shows that an attempt
                                                    has been made to write FIFO when it is full. */
} pwm_status_flags_t;

/*! @brief List of PWM FIFO available */
typedef enum _pwm_fifo_available
{
    KPWM_NO_DATA_IN_FIFO_FLAG = 0U,     /*!< No data available */
    KPWM_ONE_WORD_IN_FIFO_FLAG,         /*!< 1 word of data in FIFO */
    KPWM_TWO_WWRDS_IN_FIFO_FLAG,        /*!< 2 word of data in FIFO */
    KPWM_THREE_WORDS_IN_FIFO_FLAG,      /*!< 3 word of data in FIFO */
    KPWM_FOUR_WORDS_IN_FIFO_FLAG        /*!< 4 word of data in FIFO */
} pwm_fifo_available_t;

typedef struct _pwm_config
{
    bool enableStopMode;                        /*!< True: PWM continues to run in stop mode;
                                                     False: PWM is paused in stop mode. */
    bool enableDozeMode;                        /*!< True: PWM continues to run in doze mode;
                                                     False: PWM is paused in doze mode. */
    bool enableWaitMode;                        /*!< True: PWM continues to run in wait mode;
                                                     False: PWM is paused in wait mode. */
    bool enableDebugMode;                       /*!< True: PWM continues to run in debug mode;
                                                     False: PWM is paused in debug mode. */
    uint16_t prescale;                          /*!< Pre-scaler to divide down the clock
                                                     The prescaler value is not more than 0xFFF. Divide by (value + 1)*/
    pwm_clock_source_t clockSource;             /*!< Clock source for the counter */
    pwm_output_configuration_t outputConfig;    /*!< Set the mode of the PWM output on the output pin. */
    pwm_fifo_water_mark_t fifoWater;            /*!< Set the data level for FIFO. */
    pwm_sample_repeat_t sampleRepeat;           /*!< The number of times each sample from the FIFO is to be used. */
    pwm_byte_data_swap_t byteSwap;              /*!< It determines the byte ordering of the 16-bit data when it
                                                    goes into the FIFO from the sample register. */
    pwm_half_word_data_swap_t halfWordSwap;     /*!< It determines which half word data from the 32-bit
                                                    IP Bus interface is written into the lower 16 bits of the sample register. */
} pwm_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the PWM clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the PWM driver.
 *
 * @param base      PWM peripheral base address
 * @param config    Pointer to user's PWM config structure.
 *
 * @return kStatus_Success means success; else failed.
 */
status_t pwm_init(PWM_Type *base, const pwm_config_t *config);

/*!
 * @brief Gate the PWM submodule clock
 *
 * @param base      PWM peripheral base address
 */
void pwm_deinit(PWM_Type *base);

/*!
 * @brief  Fill in the PWM config struct with the default settings
 *
 * The default values are:
 * @code
 *   config->enableStopMode = false;
 *   config->enableDozeMode = false;
 *   config->enableWaitMode = false;
 *   config->enableDozeMode = false;
 *   config->clockSource = kPWM_LowFrequencyClock;
 *   config->prescale = 0U;
 *   config->outputConfig = kPWM_SetAtRolloverAndClearAtcomparison;
 *   config->fifoWater = kPWM_FIFOWaterMark_2;
 *   config->sampleRepeat = kPWM_EachSampleOnce;
 *   config->byteSwap = kPWM_ByteNoSwap;
 *   config->halfWordSwap = kPWM_HalfWordNoSwap;
 * @endcode
 * @param config Pointer to user's PWM config structure.
 */
void pwm_get_default_config(pwm_config_t *config);

/*! @}*/

/*!
 * @name PWM start and stop.
 * @{
 */

/*!
 * @brief Starts the PWM counter when the PWM is enabled.
 *
 * When the PWM is enabled, it begins a new period, the output pin is set to start a new period while
 * the prescaler and counter are released and counting begins.
 *
 * @param base      PWM peripheral base address
 */
static inline void pwm_start_timer(PWM_Type *base)
{
    base->PWMCR |= PWM_PWMCR_EN_MASK;
}

/*!
 * @brief Stops the PWM counter when the pwm is disabled.
 *
 * @param base      PWM peripheral base address
 */
static inline void pwm_stop_timer(PWM_Type *base)
{
    base->PWMCR &= ~(PWM_PWMCR_EN_MASK);
}

/*! @}*/

/*!
 * @brief Sofrware reset.
 *
 * PWM is reset when this bit is set to 1. It is a self clearing bit.
 * Setting this bit resets all the registers to their reset values except for the STOPEN,
 * DOZEN, WAITEN, and DBGEN bits in this control register.
 *
 * @param base      PWM peripheral base address
 */
static inline void pwm_software_reset(PWM_Type *base)
{
    base->PWMCR |= PWM_PWMCR_SWR_MASK;
}

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected PWM interrupts.
 *
 * @param base PWM peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::pwm_interrupt_enable_t
 */
static inline void pwm_enable_interrupts(PWM_Type *base, uint32_t mask)
{
    base->PWMIR |= (mask & (PWM_PWMIR_FIE_MASK | PWM_PWMIR_RIE_MASK | PWM_PWMIR_CIE_MASK));
}

/*!
 * @brief Disables the selected PWM interrupts.
 *
 * @param base PWM peripheral base address
 * @param mask The interrupts to disable. This is a logical OR of members of the
 *             enumeration ::pwm_interrupt_enable_t
 */
static inline void pwm_disable_interrupts(PWM_Type *base, uint32_t mask)
{
    base->PWMIR &= ~(mask & (PWM_PWMIR_FIE_MASK | PWM_PWMIR_RIE_MASK | PWM_PWMIR_CIE_MASK));
}

/*!
 * @brief Gets the enabled PWM interrupts.
 *
 * @param base PWM peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::pwm_interrupt_enable_t
 */
static inline uint32_t pwm_get_enabled_interrupts(PWM_Type *base)
{
    return base->PWMIR;
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the PWM status flags.
 *
 * @param base PWM peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::pwm_status_flags_t
 */
static inline uint32_t pwm_get_status_flags(PWM_Type *base)
{
    uint32_t statusFlags = base->PWMSR;

    statusFlags &= (PWM_PWMSR_FE_MASK | PWM_PWMSR_ROV_MASK | PWM_PWMSR_CMP_MASK | PWM_PWMSR_FWE_MASK);
    return statusFlags;
}

/*!
 * @brief Clears the PWM status flags.
 *
 * @param base PWM peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::pwm_status_flags_t
 */
static inline void pwm_clear_status_flags(PWM_Type *base, uint32_t mask)
{
    base->PWMSR = (mask & (PWM_PWMSR_FE_MASK | PWM_PWMSR_ROV_MASK |
                    PWM_PWMSR_CMP_MASK | PWM_PWMSR_FWE_MASK));
}

/*!
 * @brief Gets the PWM FIFO available.
 *
 * @param base PWM peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::pwm_fifo_available_t
 */
static inline uint32_t pwm_get_fifo_available(PWM_Type *base)
{
    return (base->PWMSR & PWM_PWMSR_FIFOAV_MASK);
}

/*! @}*/

/*!
 * @name Sample Interface
 * @{
 */

/*!
 * @brief Sets the PWM sample value.
 *
 * @param base PWM peripheral base address
 * @param mask The sample value. This is the input to the 4x16 FIFO. The value in this register denotes
 *             the value of the sample being currently used.
 */
static inline void pwm_set_sample_value(PWM_Type *base, uint32_t value)
{
    base->PWMSAR = (value & PWM_PWMSAR_SAMPLE_MASK);
}

/*!
 * @brief Gets the PWM sample value.
 *
 * @param base PWM peripheral base address
 *
 * @return The sample value. It can be read only when the PWM is enable.
 */
static inline uint32_t pwm_get_sample_value(PWM_Type *base)
{
    return base->PWMSAR;
}

/*! @}*/

/*!
 * @brief Sets the PWM period value.
 *
 * @param base PWM peripheral base address
 * @param mask The period value. The PWM period register (PWM_PWMPR) determines the period of
 *             the PWM output signal.
 *             Writing 0xFFFF to this register will achieve the same result as writing 0xFFFE.
 *             PWMO (Hz) = PCLK(Hz) / (period +2)
 */
static inline void pwm_set_period_value(PWM_Type *base, uint32_t value)
{
    base->PWMPR = (value & PWM_PWMPR_PERIOD_MASK);
}

/*!
 * @brief Gets the PWM period value.
 *
 * @param base PWM peripheral base address
 *
 * @return The period value. The PWM period register (PWM_PWMPR) determines the period of
 *             the PWM output signal.
 */
static inline uint32_t pwm_get_period_value(PWM_Type *base)
{
    return (base->PWMPR & PWM_PWMPR_PERIOD_MASK);
}

/*!
 * @brief Gets the PWM counter value.
 *
 * @param base PWM peripheral base address
 *
 * @return The counter value. The current count value.
 */
static inline uint32_t pwm_get_counter_value(PWM_Type *base)
{
    return (base->PWMCNR & PWM_PWMCNR_COUNT_MASK);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PWM_H_ */
