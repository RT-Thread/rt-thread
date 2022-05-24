/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DCIC_H_
#define _FSL_DCIC_H_

#include "fsl_common.h"

/*!
 * @addtogroup DCIC
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef DCIC_REGION_COUNT
#define DCIC_REGION_COUNT DCIC_DCICRCS_COUNT
#endif

/*! @brief DCIC driver version. */
#define FSL_DCIC_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))

/*! @brief CRC32 calculation polynomial. */
#define DCIC_CRC32_POLYNOMIAL 0x04C11DB7UL

/*! @brief CRC32 calculation initialize value. */
#define DCIC_CRC32_INIT_VALUE 0UL

/*! @brief ROI CRC32 value mismatch status. */
#define DCIC_REGION_MISMATCH_STATUS(region) (1UL << (DCIC_DCICS_ROI_MATCH_STAT_SHIFT + (region)))

/*!
 * @brief DCIC display signal polarity flags
 * @anchor _DCIC_polarity_flags
 */
enum _DCIC_polarity_flags
{
    kDCIC_VsyncActiveLow           = DCIC_DCICC_VSYNC_POL_MASK, /*!< VSYNC active low. */
    kDCIC_VsyncActiveHigh          = 0U,                        /*!< VSYNC active high. */
    kDCIC_HsyncActiveLow           = DCIC_DCICC_HSYNC_POL_MASK, /*!< HSYNC active low. */
    kDCIC_HsyncActiveHigh          = 0U,                        /*!< HSYNC active high. */
    kDCIC_DataEnableActiveLow      = DCIC_DCICC_DE_POL_MASK,    /*!< Data enable line active low. */
    kDCIC_DataEnableActiveHigh     = 0U,                        /*!< Data enable line active high. */
    kDCIC_DriveDataOnRisingClkEdge = DCIC_DCICC_CLK_POL_MASK,   /*!< Output data on falling clock edge, capture data
                                                                    on rising clock edge. */
    kDCIC_DriveDataOnFallingClkEdge = 0U,                       /*!< Output data on rising clock edge, capture data
                                                                    on falling clock edge. */
};

/*!
 * @brief Status flags.
 * @anchor _DCIC_status_flags
 */
enum _DCIC_status_flags
{
    kDCIC_FunctionalInterruptStatus = DCIC_DCICS_FI_STAT_MASK, /*!< Asserted when match results ready. */
    kDCIC_ErrorInterruptStatus      = DCIC_DCICS_EI_STAT_MASK, /*!< Asserted when there is a signature mismatch. */
    kDCIC_Region0MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(0U),  /*!< Region 0  CRC32 value mismatch. */
    kDCIC_Region1MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(1U),  /*!< Region 1  CRC32 value mismatch. */
    kDCIC_Region2MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(2U),  /*!< Region 2  CRC32 value mismatch. */
    kDCIC_Region3MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(3U),  /*!< Region 3  CRC32 value mismatch. */
    kDCIC_Region4MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(4U),  /*!< Region 4  CRC32 value mismatch. */
    kDCIC_Region5MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(5U),  /*!< Region 5  CRC32 value mismatch. */
    kDCIC_Region6MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(6U),  /*!< Region 6  CRC32 value mismatch. */
    kDCIC_Region7MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(7U),  /*!< Region 7  CRC32 value mismatch. */
    kDCIC_Region8MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(8U),  /*!< Region 8  CRC32 value mismatch. */
    kDCIC_Region9MismatchStatus     = DCIC_REGION_MISMATCH_STATUS(9U),  /*!< Region 9  CRC32 value mismatch. */
    kDCIC_Region10MismatchStatus    = DCIC_REGION_MISMATCH_STATUS(10U), /*!< Region 10 CRC32 value mismatch. */
    kDCIC_Region11MismatchStatus    = DCIC_REGION_MISMATCH_STATUS(11U), /*!< Region 11 CRC32 value mismatch. */
    kDCIC_Region12MismatchStatus    = DCIC_REGION_MISMATCH_STATUS(12U), /*!< Region 12 CRC32 value mismatch. */
    kDCIC_Region13MismatchStatus    = DCIC_REGION_MISMATCH_STATUS(13U), /*!< Region 13 CRC32 value mismatch. */
    kDCIC_Region14MismatchStatus    = DCIC_REGION_MISMATCH_STATUS(14U), /*!< Region 14 CRC32 value mismatch. */
    kDCIC_Region15MismatchStatus    = DCIC_REGION_MISMATCH_STATUS(15U), /*!< Region 15 CRC32 value mismatch. */
};

/*!
 * @brief Interrupts.
 * @anchor _dcic_interrupt_enable
 */
enum _dcic_interrupt_enable
{
    kDCIC_FunctionalInterruptEnable = DCIC_DCICIC_FI_MASK_MASK, /*!< Interrupt when match results ready. */
    kDCIC_ErrorInterruptEnable      = DCIC_DCICIC_EI_MASK_MASK, /*!< Interrupt when there is a signature mismatch. */
};

/*!
 * @brief DCIC configuration.
 */
typedef struct _dcic_config
{
    bool enableExternalSignal; /*!< Enable the mismatch external signal. When enabled, the mismatch status could
                                 be monitored from the extern pin. */
    uint8_t polarityFlags;     /*!< Display signal polarity, logical OR'ed of @ref _DCIC_polarity_flags. */
    uint32_t enableInterrupts; /*!< Interrupts to enable, should be OR'ed of @ref _dcic_interrupt_enable. */
} dcic_config_t;

/*!
 * @brief Region of interest (ROI) configuration.
 */
typedef struct _dcic_region_config
{
    bool lock;            /*!< Lock the region configuration except reference CRC32 value setting. */
    uint16_t upperLeftX;  /*!< X of upper left corner. Range: 0 to 2^13-1. */
    uint16_t upperLeftY;  /*!< Y of upper left corner. Range: 0 to 2^12-1. */
    uint16_t lowerRightX; /*!< X of lower right corner. Range: 0 to 2^13-1. */
    uint16_t lowerRightY; /*!< Y of lower right corner. Range: 0 to 2^12-1. */
    uint32_t refCrc;      /*!< Reference CRC32 value. */
} dcic_region_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the DCIC.
 *
 * This function resets DCIC registers to default value, then
 * set the configurations. This function does not start the
 * DCIC to work, application should call @ref DCIC_DisableRegion
 * to configure regions, then call @ref DCIC_Enable to start the
 * DCIC to work.
 *
 * @param base   DCIC peripheral base address.
 * @param config Pointer to the configuration.
 */
void DCIC_Init(DCIC_Type *base, const dcic_config_t *config);

/*!
 * @brief Deinitialize the DCIC.
 *
 * Disable the DCIC functions.
 *
 * @param base DCIC peripheral base address.
 */
void DCIC_Deinit(DCIC_Type *base);

/*!
 * @brief Get the default configuration to initialize DCIC.
 *
 * The default configuration is:
 *
 * @code
    config->polarityFlags = kDCIC_VsyncActiveLow | kDCIC_HsyncActiveLow |
                            kDCIC_DataEnableActiveLow | kDCIC_DriveDataOnFallingClkEdge;
    config->enableExternalSignal = false;
    config->enableInterrupts = 0;
   @endcode
 *
 * @param config Pointer to the configuration.
 */
void DCIC_GetDefaultConfig(dcic_config_t *config);

/*!
 * @brief Enable or disable the DCIC module.
 *
 * @param base DCIC peripheral base address.
 * @param enable Use true to enable, false to disable.
 */
static inline void DCIC_Enable(DCIC_Type *base, bool enable)
{
    if (enable)
    {
        base->DCICC |= DCIC_DCICC_IC_EN_MASK;
    }
    else
    {
        base->DCICC &= ~DCIC_DCICC_IC_EN_MASK;
    }
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Get status flags.
 *
 * The flag @ref kDCIC_ErrorInterruptStatus is asserted if any region mismatch
 * flag asserted.
 *
 * @brief base DCIC peripheral base address.
 * @return Masks of asserted status flags, @ref _DCIC_status_flags.
 */
static inline uint32_t DCIC_GetStatusFlags(DCIC_Type *base)
{
    return base->DCICS;
}

/*!
 * @brief Clear status flags.
 *
 * The flag @ref kDCIC_ErrorInterruptStatus should be cleared by clearing all
 * asserted region mismatch flags.
 *
 * @brief base DCIC peripheral base address.
 * @brief mask Mask of status values that would be cleared, @ref _DCIC_status_flags.
 */
static inline void DCIC_ClearStatusFlags(DCIC_Type *base, uint32_t mask)
{
    base->DCICS = (mask & (DCIC_DCICS_FI_STAT_MASK | DCIC_DCICS_ROI_MATCH_STAT_MASK));
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Lock the interrupt enabled status.
 *
 * Once this function is called, the interrupt enabled status could not be changed
 * until reset.
 *
 * @param base DCIC peripheral base address.
 */
static inline void DCIC_LockInterruptEnabledStatus(DCIC_Type *base)
{
    base->DCICIC |= DCIC_DCICIC_FREEZE_MASK_MASK;
}

/*!
 * @brief Enable interrupts.
 *
 * @param base DCIC peripheral base address.
 * @param mask Mask of interrupt events that would be enabled. See to "_dcic_interrupt_enable_t".
 */
static inline void DCIC_EnableInterrupts(DCIC_Type *base, uint32_t mask)
{
    base->DCICIC &= ~mask;
}

/*!
 * @brief Disable interrupts.
 *
 * @param base DCIC peripheral base address.
 * @param mask Mask of interrupt events that would be disabled. See to "_dcic_interrupt_enable_t".
 */
static inline void DCIC_DisableInterrupts(DCIC_Type *base, uint32_t mask)
{
    base->DCICIC |= mask;
}

/* @} */

/*!
 * @name Region
 * @{
 */

/*!
 * @brief Enable the region of interest (ROI) with configuration.
 *
 * Enable the ROI with configuration. To change the configuration except reference
 * CRC value, the region should be disabled first by @ref DCIC_DisableRegion,
 * then call this function again. The reference CRC value could be changed by
 * @ref DCIC_SetRegionRefCrc without disabling the region.
 * If the configuration is locked, only the reference CRC value could be changed,
 * the region size and position, enable status could not be changed until reset.
 *
 * @param base DCIC peripheral base address.
 * @param regionIdx Region index, from 0 to (DCIC_REGION_COUNT - 1).
 * @param config Pointer to the configuration.
 */
void DCIC_EnableRegion(DCIC_Type *base, uint8_t regionIdx, const dcic_region_config_t *config);

/*!
 * @brief Disable the region of interest (ROI).
 *
 * @param base DCIC peripheral base address.
 * @param regionIdx Region index, from 0 to (DCIC_REGION_COUNT - 1).
 */
static inline void DCIC_DisableRegion(DCIC_Type *base, uint8_t regionIdx)
{
    assert(regionIdx < DCIC_REGION_COUNT);

    base->REGION[regionIdx].DCICRC &= ~DCIC_DCICRC_ROI_EN_MASK;
}

/*!
 * @brief Set the reference CRC of interest (ROI).
 *
 * @param base DCIC peripheral base address.
 * @param regionIdx Region index, from 0 to (DCIC_REGION_COUNT - 1).
 * @param crc The reference CRC value.
 */
static inline void DCIC_SetRegionRefCrc(DCIC_Type *base, uint8_t regionIdx, uint32_t crc)
{
    assert(regionIdx < DCIC_REGION_COUNT);

    base->REGION[regionIdx].DCICRRS = crc;
}

/*!
 * @brief Get the DCIC calculated CRC.
 *
 * @param base DCIC peripheral base address.
 * @param regionIdx Region index, from 0 to (DCIC_REGION_COUNT - 1).
 * @return The calculated CRC value.
 */
static inline uint32_t DCIC_GetRegionCalculatedCrc(DCIC_Type *base, uint8_t regionIdx)
{
    assert(regionIdx < DCIC_REGION_COUNT);

    return base->REGION[regionIdx].DCICRCS;
}

/* @} */

/*!
 * @name Misc control.
 * @{
 */

/*!
 * @brief Enable or disable output the mismatch external signal.
 *
 * The mismatch status can be output to external pins. If enabled:
 *   - If @ref kDCIC_ErrorInterruptStatus asserted, the output signal
 *     frequency is DCIC clock / 16.
 *   - If @ref kDCIC_ErrorInterruptStatus not asserted, the output signal
 *     frequency is DCIC clock / 4.
 *   - If integrity check is disabled, the signal is idle.
 *
 * @param base DCIC peripheral base address.
 * @param enable. Use true to enable, false to disable.
 */
static inline void DCIC_EnableMismatchExternalSignal(DCIC_Type *base, bool enable)
{
    if (enable)
    {
        base->DCICIC |= DCIC_DCICIC_EXT_SIG_EN_MASK;
    }
    else
    {
        base->DCICIC &= ~DCIC_DCICIC_EXT_SIG_EN_MASK;
    }
}

/* @} */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */
#endif /* _FSL_DCIC_H_ */
