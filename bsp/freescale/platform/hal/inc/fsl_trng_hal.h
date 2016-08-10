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
#ifndef __FSL_TRNG_HAL_H__
#define __FSL_TRNG_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_TRNG_COUNT

/*! 
 * @addtogroup trng_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief TRNG work mode */
typedef enum _trng_work_mode
{
    kTRNGWorkModeRun = 0U,       /*!< Run Mode. */
    kTRNGWorkModeProgram = 1U    /*!< Program Mode. */
} trng_work_mode_t;

/*! @brief TRNG sample mode */
typedef enum _trng_sample_mode
{
    kTRNGSampleModeVonNeumann = 0U,       /*!< Use Von Neumann data into both Entropy shifter and Statistical Checker. */
    kTRNGSampleModeRaw = 1U,              /*!< Use raw data into both Entropy shifter and Statistical Checker. */
    kTRNGSampleModeVonNeumannRaw = 2U     /*!< Use Von Neumann data into Entropy shifter. Use raw data into Statistical Checker. */
} trng_sample_mode_t;

/*! @brief TRNG clock mode */
typedef enum _trng_clock_mode
{
    kTRNGClockModeRingOscillator = 0U,      /*!< Ring oscillator is used to operate the TRNG (default). */
    kTRNGClockModeSystem = 1U               /*!< System clock is used to operate the TRNG. This is for test use only, and indeterminate results may occur. */
} trng_clock_mode_t;

/*! @brief TRNG ring oscillator divide */
typedef enum _trng_ring_osc_div
{
    kTRNGRingOscDiv0 = 0U,      /*!< Ring oscillator with no divide (default). */
    kTRNGRingOscDiv2 = 1U,      /*!< Ring oscillator divided-by-2. */
    kTRNGRingOscDiv4 = 2U,      /*!< Ring oscillator divided-by-4. */
    kTRNGRingOscDiv8 = 3U       /*!< Ring oscillator divided-by-8. */
} trng_ring_osc_div_t;

/*! @brief TRNG statistical check type*/
typedef enum _trng_statistical_check
{
    kTRNGStatisticalCheckMonobit = 1U,  /*!< Statistical check of number of ones/zero detected during entropy generation. */
    kTRNGStatisticalCheckRunBit1,       /*!< Statistical check of number of runs of length 1 detected during entropy generation. */
    kTRNGStatisticalCheckRunBit2,       /*!< Statistical check of number of runs of length 2 detected during entropy generation. */
    kTRNGStatisticalCheckRunBit3,       /*!< Statistical check of number of runs of length 3 detected during entropy generation. */
    kTRNGStatisticalCheckRunBit4,       /*!< Statistical check of number of runs of length 4 detected during entropy generation. */
    kTRNGStatisticalCheckRunBit5,       /*!< Statistical check of number of runs of length 5 detected during entropy generation. */
    kTRNGStatisticalCheckRunBit6Plus,   /*!< Statistical check of number of runs of length 6 or more detected during entropy generation. */
    kTRNGStatisticalCheckPoker,         /*!< Statistical check of "Poker Test". */
    kTRNGStatisticalCheckFrequencyCount /*!< Statistical check of entropy sample frequency count. */
} trng_statistical_check_t;

/*! @brief Data structure for definition of statistical check limits. */
typedef struct _trng_statistical_check_limit
{
    uint32_t maximum;  /*!< Maximum limit.*/
    uint32_t minimum;  /*!< Minimum limit.*/
} trng_statistical_check_limit_t;

/*! @brief Defines interrupt sources for TRNG.*/
typedef enum _trng_interrupt
{
    kTRNGInterruptFrequencyCountFail        = 0x4U,  /*!< Frequency Count Fail. */
    kTRNGInterruptFrequencyEntropyValid     = 0x2U,  /*!< Entropy Valid. */
    kTRNGInterruptFrequencyHWError          = 0x1U,  /*!< Any HW error. */
    kTRNGInterruptAll                       = 0x7U   /*!< All interrupts.*/
} trng_interrupt_t;


/*! @brief Defines status return codes for TRNG function calls.*/
typedef enum _trng_status
{
    kStatus_TRNG_Success                        = 0x000000U,    /*!< Success. No error. */
    kStatus_TRNG_InvalidArgument                = 0x000001U,    /*!< Invalid argument. */
    kStatus_TRNG_OSAError                       = 0x000002U,    /*!< OSA initialisation failed */
    kStatus_TRNG_Error                          = 0x000004U,    /*!< Any TRNG module error occurred */
    /* kStatus_TRNG_Error can be combined with any of kStatus_TRNG_TestFail<error> values.*/
    kStatus_TRNG_TestFailRunBit1Sampling0       = 0x000014U,    /*!< The 1-Bit Run, Sampling 0s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit1Sampling1       = 0x000024U,    /*!< The 1-Bit Run, Sampling 1s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit2Sampling0       = 0x000044U,    /*!< The 2-Bit Run, Sampling 0s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit2Sampling1       = 0x000084U,    /*!< The 2-Bit Run, Sampling 1s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit3Sampling0       = 0x000104U,    /*!< The 3-Bit Run, Sampling 0s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit3Sampling1       = 0x000204U,    /*!< The 3-Bit Run, Sampling 1s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit4Sampling0       = 0x000404U,    /*!< The 4-Bit Run, Sampling 0s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit4Sampling1       = 0x000804U,    /*!< The 4-Bit Run, Sampling 1s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit5Sampling0       = 0x001004U,    /*!< The 5-Bit Run, Sampling 0s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit5Sampling1       = 0x002004U,    /*!< The 5-Bit Run, Sampling 1s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit6PlusSampling0   = 0x004004U,    /*!< The 6 Plus Bit Run, Sampling 0s Test has failed.*/  
    kStatus_TRNG_TestFailRunBit6PlusSampling1   = 0x008004U,    /*!< The 6 Plus Bit Run, Sampling 1s Test has failed.*/  
    kStatus_TRNG_TestFailSparseBit              = 0x010004U,    /*!< The Sparse Bit Test has failed*/  
    kStatus_TRNG_TestFailLongRun                = 0x020004U,    /*!< The Long Run Test has failed.*/  
    kStatus_TRNG_TestFailPoker                  = 0x040004U,    /*!< The Poker Test has failed.*/  
    kStatus_TRNG_TestFailMonoBit                = 0x080004U,    /*!< The Mono Bit Test has failed.*/       
    kStatus_TRNG_TestFailFrequencyCount         = 0x100004U     /*!< Frequency Count Fail. The frequency counter has detected a failure. This may be due to
                                                                improper programming of maximum and minimum limits for statistical check of entropy sample frequency count,
                                                                or a hardware failure in the ring oscillator.*/

} trng_status_t;



/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name TRNG HAL.
 * @{
 */

/*!
 * @brief Initializes the TRNG module.
 *
 * This function initializes the TRNG to a default state.
 *
 * @param base  TRNG base address
 */
void TRNG_HAL_Init(TRNG_Type * base);


/*!
 * @brief Enables the TRNG module.
 *
 * This function enables the TRNG random data generation and loading.
 *
 * @param base  TRNG base address
 */
void TRNG_HAL_Enable(TRNG_Type * base);

/*!
 * @brief Sets the TRNG to Program Mode or Run mode.
 * 
 * This function specifies whether the TRNG is in Program Mode or Run mode.
 *
 * @param base  TRNG base address
 * @param mode  kTRNGWorkModeRun means set TRNG in Run Mode.
 *              kTRNGWorkModeProgram means set TRNG in Program Mode (default after init).
*/
static inline void TRNG_HAL_SetWorkingMode(TRNG_Type * base, trng_work_mode_t mode)
{
    /* Set mode.*/
    TRNG_BWR_MCTL_PRGM(base, mode);
}

/*!
 * @brief Disables the TRNG module.
 * 
 * This function disables the TRNG module and stops generation of Entropy value.
 *
 * @param base  TRNG base address
*/
static inline void TRNG_HAL_Disable(TRNG_Type * base)
{
    /* Move to program mode. Stop entropy generation.*/
    TRNG_HAL_SetWorkingMode(base, kTRNGWorkModeProgram);
}

/*!
 * @brief Gets the TRNG status whether the generated entropy is valid.
 * 
 * This function gets the TRNG status whether an entropy is valid.
 *
 * @param base  TRNG base address
 * @return 0 means Entropy is not valid, 1 means Entropy is valid
*/
static inline bool TRNG_HAL_GetEntropyValidCmd(TRNG_Type * base)
{
    return TRNG_BRD_MCTL_ENT_VAL(base);
}

/*!
 * @brief Gets the TRNG status whether the error occurred.
 * 
 * This function gets the TRNG status whether an error is detected.
 *
 * @param base  TRNG base address
 * @return 0 means no error, 1 means error is detected
*/
static inline bool TRNG_HAL_GetErrorCmd(TRNG_Type * base)
{
    return TRNG_BRD_MCTL_ERR(base);
}

/*!
 * @brief Clears the TRNG error flag.
 * 
 * This function clears the TRNG error flag.
 *
 * @param base  TRNG base address
*/
static inline void TRNG_HAL_ClearError(TRNG_Type * base)
{
    TRNG_BWR_MCTL_ERR(base, 1);
}

/*!
 * @brief Gets the TRNG status whether the TRNG ring oscillator is not running.
 * 
 * This function gets the TRNG status that indicates whether the TRNG ring oscillator is not running.
 * Software should check this status before transitioning TRNG to low power 
 * mode (TRNG clock stopped). 
 * TRNG turns on the TRNG free-running ring oscillator whenever new entropy
 * is being generated and turns off the ring oscillator when entropy generation
 * is complete. If the TRNG clock is stopped while the TRNG ring oscillator 
 * is running, the oscillator continues running though the RNG clock.
 * is stopped. 
 *
 * @param base  TRNG base address
 * @return 0 means TRNG ring oscillator is running, 1 means TRNG ring oscillator is not running
*/
static inline bool TRNG_HAL_GetOKToStopCmd(TRNG_Type * base)
{
    return (bool)TRNG_BRD_MCTL_TSTOP_OK(base);
}

/*!
 * @brief Disables the programmability of TRNG registers. 
 * 
 * This function disables the possibility  to program TRNG registers regardless  of the TRNG working mode.
 * After that, any attempt to modify a TRNG register causes a hard fault.
 * Only the asynchronous reset returns the possibility to write to the TRNG registers.
 * @param base  TRNG base address
*/
static inline void TRNG_HAL_EnableLock(TRNG_Type * base)
{
    TRNG_BWR_SEC_CFG_NO_PRGM(base, 1);
}

#if 1 /* Causes Hard fault*/
/*!
 * @brief Gets the status of the possibility to program the TRNG registers. 
 * 
 * This function gets current status of possibility to program TRNG registers.
 *
 * @param base  TRNG base address
 * @return   0 means that is enabled programmability of TRNG registers (default value).
 *            1 means that is disabled programmability of TRNG registers in any mode.
*/
static inline bool TRNG_HAL_GetLockCmd(TRNG_Type * base)
{
    return (bool)TRNG_BRD_SEC_CFG_NO_PRGM(base);
}
#endif


/*!
 * @brief Sets the sample mode of the TRNG ring oscillator.
 * 
 * This function specifies the method of sampling the ring oscillator while generating the entropy value.
 *
 * @param base  TRNG base address
 * @param mode  kTRNGSampleModeVonNeumann means use Von Neumann data into both Entropy shifter and Statistical
 *     Checker
 *               kTRNGSampleModeRaw means use raw data into both Entropy shifter and Statistical Checker (default value).
 *               kTRNGSampleModeVonNeumannRaw means use Von Neumann data into Entropy shifter. Use raw data into Statistical Checker.
*/
static inline void TRNG_HAL_SetSampleMode(TRNG_Type * base, trng_sample_mode_t mode)
{
    /* Set sampling mode.*/
    TRNG_BWR_MCTL_SAMP_MODE(base, mode);
}

/*!
 * @brief Gets the sample mode of the TRNG ring oscillator.
 * 
 * This function gets the method of sampling the ring oscillator while generating the entropy value.
 *
 * @param base  TRNG base address
 * @return  kTRNGSampleModeVonNeumann means Von Neumann data placed into both Entropy shifter and Statistical Checker, 
 *          kTRNGSampleModeRaw means raw data placed into both Entropy shifter and Statistical Checker,
 *          kTRNGSampleModeVonNeumannRaw means Von Neumann data placed into Entropy shifter and raw data placed into Statistical Checker.
*/
static inline trng_sample_mode_t TRNG_HAL_GetSampleMode(TRNG_Type * base)
{
    /* Get sample mode.*/
    return (trng_sample_mode_t)TRNG_BRD_MCTL_SAMP_MODE(base);
}

/*!
 * @brief Sets the clock mode used to operate TRNG.
 * 
 * This function specifies the clock mode used to operate TRNG.
 * By default is used TRNG ring oscillator.
 * Changing clock mode is for test use only, and indeterminate results may occur.
 *
 * @param base  TRNG base address
 * @param mode  kTRNGClockModeRingOscillator means use ring oscillator to operate the TRNG (default),
 *               kTRNGClockModeSystem means force system clock to operate the TRNG.
*/
static inline void TRNG_HAL_SetClockMode(TRNG_Type * base, trng_clock_mode_t mode)
{
    /* Set clock mode.*/
    TRNG_BWR_MCTL_FOR_SCLK(base, mode);
}

/*!
 * @brief Gets the clock mode used to operate the TRNG.
 * 
 * This function gets the clock mode used to operate TRNG.
 *
 * @param base  TRNG base address
 * @return  kTRNGClockModeRingOscillator means ring oscillator is used to operate the TRNG,
 *          kTRNGClockModeSystem means system clock is used to operate the TRNG.
*/
static inline trng_clock_mode_t TRNG_HAL_GetClockMode(TRNG_Type * base)
{
    /* Get clock mode.*/
    return (trng_clock_mode_t)TRNG_BRD_MCTL_FOR_SCLK(base);
}

/*!
 * @brief Sets the ring oscillator divide used by the TRNG.
 * 
 * This function determines the amount of dividing done to the ring
 * oscillator before it is used by the TRNG.
 *
 * @param base  TRNG base address
 * @param osc_div   kTRNGRingOscDiv0 means use ring oscillator with no divide (default),
 *                  kTRNGRingOscDiv2 means use ring oscillator divided-by-2,
 *                  kTRNGRingOscDiv4 means use ring oscillator divided-by-4,
 *                  kTRNGRingOscDiv8 means use ring oscillator divided-by-8.
*/
static inline void TRNG_HAL_SetRingOscDiv(TRNG_Type * base, trng_ring_osc_div_t osc_div)
{
    /* Set ring oscillator divide.*/
    TRNG_BWR_MCTL_OSC_DIV(base, osc_div);
}

/*!
 * @brief Gets the ring oscillator divide used by the TRNG.
 * 
 * This function gets the amount of dividing done to the ring
 * oscillator before it is used by the TRNG.
 *
 * @param base  TRNG base address
 * @return  kTRNGRingOscDiv0 means ring oscillator with no divide is used,
 *          kTRNGRingOscDiv2 means ring oscillator divided-by-2 is used,
 *          kTRNGRingOscDiv4 means ring oscillator divided-by-4 is used,
 *          kTRNGRingOscDiv8 means ring oscillator divided-by-8 is used.
*/
static inline trng_ring_osc_div_t TRNG_HAL_GetRingOscDiv(TRNG_Type * base)
{
    /* Get ring oscillator divide.*/
    return (trng_ring_osc_div_t) TRNG_BRD_MCTL_OSC_DIV(base);
}

/*!
 * @brief Sets the TRNG sample size.
 * 
 * This function sets the total number of Entropy samples that is taken
 * during the entropy generation.
 *
 * @param base  TRNG base address
 * @param sample_size  Number of samples.
*/
static inline void TRNG_HAL_SetSampleSize(TRNG_Type * base, uint16_t sample_size)
{
    /* Set sample size.*/
    TRNG_BWR_SDCTL_SAMP_SIZE(base, sample_size);
}

/*!
 * @brief Gets the TRNG sample size.
 * 
 * This function gets the total number of entropy samples that are taken
 * during the entropy generation.
 *
 * @param base  TRNG base address
 * @return Sample size. After initialization, it is reset to default 2500.
*/
static inline uint16_t TRNG_HAL_GetSampleSize(TRNG_Type * base)
{
    /* Get sample size.*/
    return (uint16_t)TRNG_BRD_SDCTL_SAMP_SIZE(base);
}

/*!
 * @brief Sets the TRNG entropy delay.
 * 
 * This function sets the length (in system clocks) of each entropy sample
 * taken.
 *
 * @param base  TRNG base address
 * @param ent_delay  Entropy delay.
*/
static inline void TRNG_HAL_SetEntropyDelay(TRNG_Type * base, uint16_t ent_delay)
{
    /* Set Entropy delay.*/
    TRNG_BWR_SDCTL_ENT_DLY(base, ent_delay);
}

/*!
 * @brief Gets the TRNG entropy delay.
 * 
 * This function gets the length (in system clocks) of each entropy sample
 * taken.
 *
 * @param base  TRNG base address
 * @return Entropy delay. After initialization, it is reset to default 3200.
*/
static inline uint16_t TRNG_HAL_GetEntropyDelay(TRNG_Type * base)
{
    /* Get Entropy delay.*/
    return (uint16_t)TRNG_BRD_SDCTL_ENT_DLY(base);
}

/*!
 * @brief Sets the TRNG sparse bit limit.
 * 
 * This function sets the Sparse Bit Limit which defines the maximum number of
 * consecutive samples that may be discarded before an error is generated.
 * This limit is used only for During Von Neumann sampling (enabled by TRNG_HAL_SetSampleMode()).
 * Samples are discarded if two consecutive raw samples are both 0 or both 1. If
 * this discarding occurs for a long period of time, it indicates that there is
 * insufficient Entropy. 
 *
 * @param base  TRNG base address
 * @param sparse_bit_limit  Sparse bit limit.
*/
static inline void TRNG_HAL_SetSparseBitLimit(TRNG_Type * base, uint16_t sparse_bit_limit)
{
    /* Set Sparse Bit Limit.*/
    TRNG_BWR_SBLIM_SB_LIM(base, sparse_bit_limit);
}

/*!
 * @brief Gets the TRNG sparse bit limit.
 * 
 * This function gets the Sparse Bit Limit which defines the maximum number of
 * consecutive samples that may be discarded before an error is generated.
 * This limit is used only for During Von Neumann sampling (enabled by TRNG_HAL_SetSampleMode()).
 * Samples are discarded if two consecutive raw samples are both 0 or both 1. If
 * this discarding occurs for a long period of time, it indicates that there is
 * insufficient Entropy. 
 *
 * @param base  TRNG base address
 * @return Sparse bit limit. After initialization, it is reset to default 63.
*/
static inline uint16_t TRNG_HAL_GetSparseBitLimit(TRNG_Type * base)
{
    /* Get Sparse Bit Limit.*/
    return (uint16_t)TRNG_BRD_SBLIM_SB_LIM(base);
}

/*!
 * @brief Sets the TRNG retry count.
 * 
 * This function sets the retry counter which defines the number of times a 
 * statistical check may fails during the TRNG entropy generation before
 * generating an error.
 *
 * @param base  TRNG base address
 * @param retry_count   Retry count [1-15].
 * @return If successful, returns the kStatus_TRNG_Success. Otherwise, it returns kStatus_TRNG_InvalidArgument.
*/
trng_status_t TRNG_HAL_SetRetryCount(TRNG_Type * base, uint8_t retry_count);

/*!
 * @brief Gets the TRNG retry count.
 * 
 * This function gets the retry counter which defines the number of times a 
 * statistical check may fails during the TRNG entropy generation before
 * generating an error.
 *
 * @param base  TRNG base address
 * @return  Retry count. After initialization, it is reset to default 1.
*/
static inline uint8_t TRNG_HAL_GetRetryCount(TRNG_Type * base)
{
    /* Get retry count.*/
    return (uint8_t)TRNG_BRD_SCMISC_RTY_CT(base);
}

/*!
 * @brief Sets the TRNG long run maximum limit.
 * 
 * This function sets the largest allowable number of consecutive
 * samples of all 1, or all 0, that is allowed during the Entropy generation.
 *
 * @param base  TRNG base address
 * @param long_run_max_limit    Maximum limit of consecutive samples of all 1, or all 0.
*/
static inline void TRNG_HAL_SetLongRunMaxLimit(TRNG_Type * base, uint8_t long_run_max_limit)
{
    /* Set maximum limit.*/
    TRNG_BWR_SCMISC_LRUN_MAX(base, long_run_max_limit);
}

/*!
 * @brief Gets the TRNG long run maximum limit.
 * 
 * This function gets value of largest allowable number of consecutive
 * samples of all 1, or all 0, that is allowed during the Entropy generation.
 *
 * @param base  TRNG base address
 * @return  Maximum limit of consecutive samples of all 1, or all 0.
*/
static inline uint8_t TRNG_HAL_GetLongRunMaxLimit(TRNG_Type * base)
{
    /* Get maximum limit.*/
    return (uint8_t)TRNG_BRD_SCMISC_LRUN_MAX(base);
}

/*!
 * @brief Enables or disables the related TRNG interrupt.
 * 
 * This function enables or disables interrupts that are generated by the TRNG.
 *
 * @param base  TRNG base address
 * @param interrupt The interrupt sources defined by trng_interrupt_t.
 * @param enable The interrupt enable switch.
*/
void TRNG_HAL_SetIntMode(TRNG_Type * base, trng_interrupt_t interrupt, bool enable);

/*!
 * @brief Gets whether the TRNG interrupt is enabled.
 * 
 * This function returns whether the TRNG interrupt is enabled or disabled.
 *
 * @param base  TRNG base address
 * @param interrupt The interrupt sources defined by trng_interrupt_t.
 * @return true, if interrupt enabled(unmasked).
 *         false, if interrupt disabled(masked).
*/
static inline bool TRNG_HAL_GetIntMode(TRNG_Type * base, trng_interrupt_t interrupt)
{
    return ((TRNG_RD_INT_MASK(base) & interrupt) != 0);
}

/*!
 * @brief Gets the TRNG interrupt status.
 * 
 * This function returns whether the TRNG interrupt is happened or not.
 *
 * @param base  TRNG base address
 * @param interrupt The interrupt sources defined by trng_interrupt_t.
 * @return true, if the interrupt event happened.
 *         false, if the interrupt event has not happened.
*/
static inline bool TRNG_HAL_GetIntStatusFlag(TRNG_Type * base, trng_interrupt_t interrupt)
{
    return ((TRNG_RD_INT_CTRL(base) & interrupt) != 0);
}

/*!
 * @brief Clears the interrupt status of the TRNG module.
 * 
 * This function clears the TRNG interrupt status.
 *
 * @param base  TRNG base address
 * @param interrupt The interrupt source to be cleared, defined by trng_interrupt_t.
*/
static inline void TRNG_HAL_ClearIntStatusFlag(TRNG_Type * base, trng_interrupt_t interrupt)
{
        TRNG_CLR_INT_CTRL(base, interrupt);
}

/*!
 * @brief Sets statistical check limits.
 *
 * This function is used to set minimum and maximum limits of a statistical check.
 *
 * @param base  TRNG base address
 * @param statistical_check type of statistical check defined by trng_statistical_check_t
 * @param limit Pointer to structure used to store maximum and minimum limits of statistic
 * @return If successful, returns the kStatus_TRNG_Success. Otherwise, it returns kStatus_TRNG_InvalidArgument.
 */
trng_status_t  TRNG_HAL_SetStatisticalCheckLimit(TRNG_Type * base, trng_statistical_check_t statistical_check, const trng_statistical_check_limit_t *limit);

/*!
 * @brief Gets statistical check limits.
 *
 * This function is used to get current setting of minimum and maximum limits of a statistical check.
 *
 * @param base  TRNG base address
 * @param statistical_check Type of statistical check defined by trng_statistical_check_t
 * @param limit Pointer to structure used to store maximum and minimum limits of statistic
 * @return minimum and maximum limits of a statistical check
 */
void TRNG_HAL_GetStatisticalCheckLimit(TRNG_Type * base, trng_statistical_check_t statistical_check, trng_statistical_check_limit_t *limit);

/*!
 * @brief Gets a entry data from the TRNG. 
 *
 * This function gets an entropy data from TRNG.
 * Entropy data is spread over TRNG_ENT_COUNT registers. 
 * Read register number is defined by index parameter.
 * Entropy data is valid only if TRNG_HAL_GetEntropyValidCmd() returns 1.
 *
 * @param base  TRNG base address
 * @param index TRNG entropy register index. It is rounded by module TRNG_ENT_COUNT by the function, 
 *                to be sure that register index is set to value from 0 till (TRNG_ENT_COUNT-1) and
 *                to allow incrementing of the index without the limit control from an application.
 *        
 * 
 * @return 32bit entropy data
*/
uint32_t TRNG_HAL_ReadEntropy(TRNG_Type * base, uint32_t index);


/*!
 * @brief Gets the TRNG status. 
 *
 * This function gets current status after the TRNG entropy generation.
 *
 * @param base  TRNG base address
 * @return TRNG status. It can be  kStatus_TRNG_Success if no error, kStatus_TRNG_Error if any error with any combination of kStatus_TRNG_TestFailRunBit1Sampling0, kStatus_TRNG_TestFailRunBit1Sampling1,
            kStatus_TRNG_TestFailRunBit2Sampling0, kStatus_TRNG_TestFailRunBit2Sampling1, kStatus_TRNG_TestFailRunBit3Sampling0,
            kStatus_TRNG_TestFailRunBit3Sampling1, kStatus_TRNG_TestFailRunBit4Sampling0, kStatus_TRNG_TestFailRunBit4Sampling1,
            kStatus_TRNG_TestFailRunBit5Sampling0, kStatus_TRNG_TestFailRunBit5Sampling1, kStatus_TRNG_TestFailRunBit6PlusSampling0,
            kStatus_TRNG_TestFailRunBit6PlusSampling1, kStatus_TRNG_TestFailSparseBit, kStatus_TRNG_TestFailLongRun, kStatus_TRNG_TestFailPoker,
            kStatus_TRNG_TestFailMonoBit, kStatus_TRNG_TestFailFrequencyCount.
*/
trng_status_t TRNG_HAL_GetStatus(TRNG_Type * base);
/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_TRNG_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

