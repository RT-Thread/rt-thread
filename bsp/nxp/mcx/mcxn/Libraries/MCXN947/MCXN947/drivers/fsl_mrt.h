/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_MRT_H_
#define FSL_MRT_H_

#include "fsl_common.h"

/*!
 * @addtogroup mrt
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_MRT_DRIVER_VERSION (MAKE_VERSION(2, 0, 3)) /*!< Version 2.0.3 */
/*! @} */

/*! @brief List of MRT channels */
typedef enum _mrt_chnl
{
    kMRT_Channel_0 = 0U, /*!< MRT channel number 0*/
    kMRT_Channel_1,      /*!< MRT channel number 1 */
    kMRT_Channel_2,      /*!< MRT channel number 2 */
    kMRT_Channel_3       /*!< MRT channel number 3 */
} mrt_chnl_t;

/*! @brief List of MRT timer modes */
typedef enum _mrt_timer_mode
{
    kMRT_RepeatMode       = (0 << MRT_CHANNEL_CTRL_MODE_SHIFT), /*!< Repeat Interrupt mode */
    kMRT_OneShotMode      = (1 << MRT_CHANNEL_CTRL_MODE_SHIFT), /*!< One-shot Interrupt mode */
    kMRT_OneShotStallMode = (2 << MRT_CHANNEL_CTRL_MODE_SHIFT)  /*!< One-shot stall mode */
} mrt_timer_mode_t;

/*! @brief List of MRT interrupts */
typedef enum _mrt_interrupt_enable
{
    kMRT_TimerInterruptEnable = MRT_CHANNEL_CTRL_INTEN_MASK /*!< Timer interrupt enable*/
} mrt_interrupt_enable_t;

/*! @brief List of MRT status flags */
typedef enum _mrt_status_flags
{
    kMRT_TimerInterruptFlag = MRT_CHANNEL_STAT_INTFLAG_MASK, /*!< Timer interrupt flag */
    kMRT_TimerRunFlag       = MRT_CHANNEL_STAT_RUN_MASK,     /*!< Indicates state of the timer */
} mrt_status_flags_t;

/*!
 * @brief MRT configuration structure
 *
 * This structure holds the configuration settings for the MRT peripheral. To initialize this
 * structure to reasonable defaults, call the MRT_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 *
 * The config struct can be made const so it resides in flash
 */
typedef struct _mrt_config
{
    bool enableMultiTask; /*!< true: Timers run in multi-task mode; false: Timers run in hardware status mode */
} mrt_config_t;

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
 * @brief Ungates the MRT clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the MRT driver.
 *
 * @param base   Multi-Rate timer peripheral base address
 * @param config Pointer to user's MRT config structure. If MRT has  MULTITASK bit field in
 *               MODCFG reigster, param config is useless.
 */
void MRT_Init(MRT_Type *base, const mrt_config_t *config);

/*!
 * @brief Gate the MRT clock
 *
 * @param base Multi-Rate timer peripheral base address
 */
void MRT_Deinit(MRT_Type *base);

/*!
 * @brief Fill in the MRT config struct with the default settings
 *
 * The default values are:
 * @code
 *     config->enableMultiTask = false;
 * @endcode
 * @param config Pointer to user's MRT config structure.
 */
static inline void MRT_GetDefaultConfig(mrt_config_t *config)
{
    assert(config != NULL);
#if !(defined(FSL_FEATURE_MRT_HAS_NO_MODCFG_MULTITASK) && FSL_FEATURE_MRT_HAS_NO_MODCFG_MULTITASK)
    /* Use hardware status operating mode */
    config->enableMultiTask = false;
#endif
}

/*!
 * @brief Sets up an MRT channel mode.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Channel that is being configured.
 * @param mode    Timer mode to use for the channel.
 */
static inline void MRT_SetupChannelMode(MRT_Type *base, mrt_chnl_t channel, const mrt_timer_mode_t mode)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);

    uint32_t reg = base->CHANNEL[channel].CTRL;

    /* Clear old value */
    reg &= ~MRT_CHANNEL_CTRL_MODE_MASK;
    /* Add the new mode */
    reg |= (uint32_t)mode;

    base->CHANNEL[channel].CTRL = reg;
}

/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the MRT interrupt.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number
 * @param mask    The interrupts to enable. This is a logical OR of members of the
 *                enumeration ::mrt_interrupt_enable_t
 */
static inline void MRT_EnableInterrupts(MRT_Type *base, mrt_chnl_t channel, uint32_t mask)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    base->CHANNEL[channel].CTRL |= mask;
}

/*!
 * @brief Disables the selected MRT interrupt.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number
 * @param mask    The interrupts to disable. This is a logical OR of members of the
 *                enumeration ::mrt_interrupt_enable_t
 */
static inline void MRT_DisableInterrupts(MRT_Type *base, mrt_chnl_t channel, uint32_t mask)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    base->CHANNEL[channel].CTRL &= ~mask;
}

/*!
 * @brief Gets the enabled MRT interrupts.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::mrt_interrupt_enable_t
 */
static inline uint32_t MRT_GetEnabledInterrupts(MRT_Type *base, mrt_chnl_t channel)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    return (base->CHANNEL[channel].CTRL & MRT_CHANNEL_CTRL_INTEN_MASK);
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the MRT status flags
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::mrt_status_flags_t
 */
static inline uint32_t MRT_GetStatusFlags(MRT_Type *base, mrt_chnl_t channel)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    return (base->CHANNEL[channel].STAT & (MRT_CHANNEL_STAT_INTFLAG_MASK | MRT_CHANNEL_STAT_RUN_MASK));
}

/*!
 * @brief Clears the MRT status flags.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number
 * @param mask    The status flags to clear. This is a logical OR of members of the
 *                enumeration ::mrt_status_flags_t
 */
static inline void MRT_ClearStatusFlags(MRT_Type *base, mrt_chnl_t channel, uint32_t mask)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    base->CHANNEL[channel].STAT = (mask & MRT_CHANNEL_STAT_INTFLAG_MASK);
}

/*! @}*/

/*!
 * @name Read and Write the timer period
 * @{
 */

/*!
 * @brief Used to update the timer period in units of count.
 *
 * The new value will be immediately loaded or will be loaded at the end of the current time
 * interval. For one-shot interrupt mode the new value will be immediately loaded.
 *
 * @note User can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * @param base          Multi-Rate timer peripheral base address
 * @param channel       Timer channel number
 * @param count         Timer period in units of ticks
 * @param immediateLoad true: Load the new value immediately into the TIMER register;
 *                      false: Load the new value at the end of current timer interval
 */
void MRT_UpdateTimerPeriod(MRT_Type *base, mrt_chnl_t channel, uint32_t count, bool immediateLoad);

/*!
 * @brief Reads the current timer counting value.
 *
 * This function returns the real-time timer counting value, in a range from 0 to a
 * timer period.
 *
 * @note User can call the utility macros provided in fsl_common.h to convert ticks to usec or msec
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number
 *
 * @return Current timer counting value in ticks
 */
static inline uint32_t MRT_GetCurrentTimerCount(MRT_Type *base, mrt_chnl_t channel)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    return base->CHANNEL[channel].TIMER;
}

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the timer counting.
 *
 * After calling this function, timers load period value, counts down to 0 and
 * depending on the timer mode it will either load the respective start value again or stop.
 *
 * @note User can call the utility macros provided in fsl_common.h to convert to ticks
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number.
 * @param count   Timer period in units of ticks. Count can contain the LOAD bit, which control the force load feature.
 */
static inline void MRT_StartTimer(MRT_Type *base, mrt_chnl_t channel, uint32_t count)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    assert((uint32_t)(count & ~MRT_CHANNEL_INTVAL_LOAD_MASK) <= (uint32_t)MRT_CHANNEL_INTVAL_IVALUE_MASK);
    /* Write the timer interval value */
    base->CHANNEL[channel].INTVAL = count;
}

/*!
 * @brief Stops the timer counting.
 *
 * This function stops the timer from counting.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number.
 */
static inline void MRT_StopTimer(MRT_Type *base, mrt_chnl_t channel)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);
    /* Stop the timer immediately */
    base->CHANNEL[channel].INTVAL = MRT_CHANNEL_INTVAL_LOAD_MASK;
}

/*! @}*/

/*!
 * @name Get & release channel
 * @{
 */

/*!
 * @brief Find the available channel.
 *
 * This function returns the lowest available channel number.
 *
 * @param base Multi-Rate timer peripheral base address
 */
static inline uint32_t MRT_GetIdleChannel(MRT_Type *base)
{
    return base->IDLE_CH;
}

#if !(defined(FSL_FEATURE_MRT_HAS_NO_CHANNEL_STAT_INUSE) && FSL_FEATURE_MRT_HAS_NO_CHANNEL_STAT_INUSE)
/*!
 * @brief Release the channel when the timer is using the multi-task mode.
 *
 * In multi-task mode, the INUSE flags allow more control over when MRT channels are released for
 * further use. The user can hold on to a channel acquired by calling MRT_GetIdleChannel() for as
 * long as it is needed and release it by calling this function. This removes the need to ask for
 * an available channel for every use.
 *
 * @param base    Multi-Rate timer peripheral base address
 * @param channel Timer channel number.
 */
static inline void MRT_ReleaseChannel(MRT_Type *base, mrt_chnl_t channel)
{
    assert((uint8_t)channel < (uint8_t)FSL_FEATURE_MRT_NUMBER_OF_CHANNELS);

    uint32_t reg = base->CHANNEL[channel].STAT;

    /* Clear flag bits to prevent accidentally clearing anything when writing back */
    reg = ~MRT_CHANNEL_STAT_INTFLAG_MASK;
    reg |= MRT_CHANNEL_STAT_INUSE_MASK;

    base->CHANNEL[channel].STAT = reg;
}
#endif

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_MRT_H_ */
