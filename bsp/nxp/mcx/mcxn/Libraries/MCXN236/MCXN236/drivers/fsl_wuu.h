/*
 * Copyright 2019-2023 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_WUU_H_
#define FSL_WUU_H_

#include "fsl_common.h"

/*! @addtogroup wuu */
/*! @{ */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Defines WUU driver version 2.3.0. */
#define FSL_WUU_DRIVER_VERSION (MAKE_VERSION(2, 3, 0))
/*@}*/

/*!
 * @brief External WakeUp pin edge detection enumeration.
 */
typedef enum _wuu_external_pin_edge_detection
{
    kWUU_ExternalPinDisable     = 0x0U, /*!< External input Pin disabled as wake up input. */
    kWUU_ExternalPinRisingEdge  = 0x1U, /*!< External input Pin enabled with the rising edge detection. */
    kWUU_ExternalPinFallingEdge = 0x2U, /*!< External input Pin enabled with the falling edge detection. */
    kWUU_ExternalPinAnyEdge     = 0x3U, /*!< External input Pin enabled with any change detection. */
} wuu_external_pin_edge_detection_t;

/*!
 * @brief External input wake up pin event enumeration.
 */
typedef enum _wuu_external_wakeup_pin_event
{
    kWUU_ExternalPinInterrupt    = 0x0U, /*!< External input Pin configured as interrupt. */
    kWUU_ExternalPinDMARequest   = 0x1U, /*!< External input Pin configured as DMA request. */
    kWUU_ExternalPinTriggerEvent = 0x2U, /*!< External input Pin configured as Trigger event. */
} wuu_external_wakeup_pin_event_t;

/*!
 * @brief External input wake up pin mode enumeration.
 */
typedef enum _wuu_external_wakeup_pin_mode
{
    kWUU_ExternalPinActiveDSPD   = 0x0U, /*!< External input Pin is active only during Deep Sleep/Power Down Mode. */
    kWUU_ExternalPinActiveAlways = 0x1U, /*!< External input Pin is active during all power modes. */
} wuu_external_wakeup_pin_mode_t;

/*!
 * @brief Internal module wake up event enumeration.
 */
typedef enum _wuu_internal_wakeup_module_event
{
    kWUU_InternalModuleInterrupt  = 0x0U, /*!< Internal modules' interrupt as a wakeup source. */
    kWUU_InternalModuleDMATrigger = 0x1U, /*!< Internal modules' DMA/Trigger as a wakeup source. */
} wuu_internal_wakeup_module_event_t;

/*!
 * @brief Pin filter edge enumeration.
 */
typedef enum _wuu_filter_edge
{
    kWUU_FilterDisabled      = 0x0U, /*!< Filter disabled. */
    kWUU_FilterPosedgeEnable = 0x1U, /*!< Filter posedge detect enabled. */
    kWUU_FilterNegedgeEnable = 0x2U, /*!< Filter negedge detect enabled. */
    kWUU_FilterAnyEdge       = 0x3U, /*!< Filter any edge detect enabled. */
} wuu_filter_edge_t;

/*!
 * @brief Pin Filter event enumeration.
 */
typedef enum _wuu_filter_event
{
    kWUU_FilterInterrupt    = 0x0U, /*!< Filter output configured as interrupt. */
    kWUU_FilterDMARequest   = 0x1U, /*!< Filter output configured as DMA request. */
    kWUU_FilterTriggerEvent = 0x2U, /*!< Filter output configured as Trigger event. */
} wuu_filter_event_t;

/*!
 * @brief Pin filter mode enumeration.
 */
typedef enum _wuu_filter_mode
{
    kWUU_FilterActiveDSPD   = 0x0U, /*!< External input pin filter is active only during Deep Sleep/Power Down Mode. */
    kWUU_FilterActiveAlways = 0x1U, /*!< External input Pin filter is active during all power modes. */
} wuu_filter_mode_t;

/*!
 * @brief External WakeUp pin configuration
 */
typedef struct _wuu_external_wakeup_pin_config
{
    wuu_external_pin_edge_detection_t edge; /*!< External Input pin edge detection. */
    wuu_external_wakeup_pin_event_t event;  /*!< External Input wakeup Pin event */
    wuu_external_wakeup_pin_mode_t mode;    /*!< External Input wakeup Pin operate mode. */
} wuu_external_wakeup_pin_config_t;

/*!
 * @brief Pin Filter configuration.
 */
typedef struct _wuu_pin_filter_config
{
    uint32_t pinIndex;        /*!< The index of wakeup pin to be muxxed into filter. */
    wuu_filter_edge_t edge;   /*!< The edge of the pin digital filter. */
    wuu_filter_event_t event; /*!< The event of the filter output. */
    wuu_filter_mode_t mode;   /*!< The mode of the filter operate. */
} wuu_pin_filter_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name External Wake up Pins Control APIs.
 * @{
 */
/*!
 * @brief Enables and Configs External WakeUp Pins.
 *
 * This function enables/disables the external pin as wakeup input. What's more this
 * function configs pins options, including edge detection wakeup event and operate mode.
 *
 * @param base     MUU peripheral base address.
 * @param pinIndex The index of the external input pin. See Reference Manual for the details.
 * @param config   Pointer to wuu_external_wakeup_pin_config_t structure.
 */
void WUU_SetExternalWakeUpPinsConfig(WUU_Type *base, uint8_t pinIndex, const wuu_external_wakeup_pin_config_t *config);

/*!
 * @brief Gets External Wakeup pin flags.
 *
 * This function return the external wakeup pin flags.
 *
 * @param base WUU peripheral base address.
 * @return Wakeup flags for all external wakeup pins.
 */
static inline uint32_t WUU_GetExternalWakeUpPinsFlag(WUU_Type *base)
{
    return base->PF;
}

/*!
 * @brief Clears External WakeUp Pin flags.
 *
 * This function clears external wakeup pins flags based on the mask.
 *
 * @param base WUU peripheral base address.
 * @param mask The mask of Wakeup pin index to be cleared.
 */
static inline void WUU_ClearExternalWakeUpPinsFlag(WUU_Type *base, uint32_t mask)
{
    base->PF = mask;
}
/* @} */

/*!
 * @name Internal Wakeup Module control APIs.
 * @{
 */

/*!
 * @brief Config Internal modules' event as the wake up soures.
 *
 * This function configs the internal modules event as the wake up sources.
 *
 * @param base WUU peripheral base address.
 * @param moduleIndex The selected internal module. See the Reference Manual for the details.
 * @param event Select interrupt or DMA/Trigger of the internal module as the wake up source.
 */
void WUU_SetInternalWakeUpModulesConfig(WUU_Type *base, uint8_t moduleIndex, wuu_internal_wakeup_module_event_t event);

/*!
 * @brief Disable an on-chip internal modules' event as the wakeup sources.
 * 
 * @param base WUU peripheral base address.
 * @param moduleIndex The selected internal module. See the Reference Manual for the details.
 * @param event The event(interrupt or DMA/trigger) of the internal module to disable.
 */
void WUU_ClearInternalWakeUpModulesConfig(WUU_Type *base, uint8_t moduleIndex, wuu_internal_wakeup_module_event_t event);

#if (defined(FSL_FEATURE_WUU_HAS_MF) && FSL_FEATURE_WUU_HAS_MF)
/*!
 * @brief Get wakeup flags for internal wakeup modules.
 *
 * @param base WUU peripheral base address.
 * @return Wakeup flags for all internal wakeup modules.
 */
static inline uint32_t WUU_GetModuleInterruptFlag(WUU_Type *base)
{
    return base->MF;
}

/*!
 * @brief Gets the internal module wakeup source flag.
 *
 * This function checks the flag to detect whether the system is
 * woken up by specific on-chip module interrupt.
 *
 * @param base WWU peripheral base address.
 * @param moduleIndex  A module index, which starts from 0.
 * @return True if the specific pin is a wake up source.
 */
static inline bool WUU_GetInternalWakeupModuleFlag(WUU_Type *base, uint32_t moduleIndex)
{
    return ((1UL << moduleIndex) == (WUU_GetModuleInterruptFlag(base) & (1UL << moduleIndex)));
}
#endif /* FSL_FEATURE_WUU_HAS_MF */

/* @} */

/*!
 * @name Pin Filter Control APIs
 * @{
 */
/*!
 * @brief Configs and Enables Pin filters.
 *
 * This function configs Pin filter, including pin select, filer operate mode
 * filer wakeup event and filter edge detection.
 *
 * @param base WUU peripheral base address.
 * @param filterIndex The index of the pin filer.
 * @param config Pointer to wuu_pin_filter_config_t structure.
 */
void WUU_SetPinFilterConfig(WUU_Type *base, uint8_t filterIndex, const wuu_pin_filter_config_t *config);

/*!
 * @brief Gets the pin filter configuration.
 *
 * This function gets the pin filter flag.
 *
 * @param base WUU peripheral base address.
 * @param filterIndex A pin filter index, which starts from 1.
 * @return True if the flag is a source of the existing low-leakage power mode.
 */
bool WUU_GetPinFilterFlag(WUU_Type *base, uint8_t filterIndex);

/*!
 * @brief Clears the pin filter configuration.
 *
 * This function clears the pin filter flag.
 *
 * @param base WUU peripheral base address.
 * @param filterIndex A pin filter index to clear the flag, starting from 1.
 */
void WUU_ClearPinFilterFlag(WUU_Type *base, uint8_t filterIndex);

/*!
 * brief Gets the external wakeup source flag.
 *
 * This function checks the external pin flag to detect whether the MCU is
 * woken up by the specific pin.
 *
 * param base WUU peripheral base address.
 * param pinIndex     A pin index, which starts from 0.
 * return True if the specific pin is a wakeup source.
 */
bool WUU_GetExternalWakeupPinFlag(WUU_Type *base, uint32_t pinIndex);

/*!
 * brief Clears the external wakeup source flag.
 *
 * This function clears the external wakeup source flag for a specific pin.
 *
 * param base WUU peripheral base address.
 * param pinIndex A pin index, which starts from 0.
 */
void WUU_ClearExternalWakeupPinFlag(WUU_Type *base, uint32_t pinIndex);
/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /*FSL_WUU_H_*/
