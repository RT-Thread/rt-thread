/*
 * Copyright 2019-2020, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_OCOTP_H_
#define FSL_OCOTP_H_

#include "fsl_common.h"

/*!
 * @addtogroup ocotp
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief OCOTP driver version. */
#define FSL_OCOTP_DRIVER_VERSION (MAKE_VERSION(2, 1, 4))
/*! @} */

#ifndef OCOTP_READ_FUSE_DATA_COUNT
#define OCOTP_READ_FUSE_DATA_COUNT (1U)
#endif

/*! @brief _ocotp_status Error codes for the OCOTP driver. */
enum
{
    kStatus_OCOTP_AccessError = MAKE_STATUS(kStatusGroup_SDK_OCOTP, 0), /*!< eFuse and shadow register access error. */
    kStatus_OCOTP_CrcFail     = MAKE_STATUS(kStatusGroup_SDK_OCOTP, 1), /*!< CRC check failed. */
    kStatus_OCOTP_ReloadError =
        MAKE_STATUS(kStatusGroup_SDK_OCOTP, 2), /*!< Error happens during reload shadow register. */
    kStatus_OCOTP_ProgramFail = MAKE_STATUS(kStatusGroup_SDK_OCOTP, 3), /*!< Fuse programming failed. */
    kStatus_OCOTP_Locked      = MAKE_STATUS(kStatusGroup_SDK_OCOTP, 4), /*!< Fuse is locked and cannot be programmed. */
};

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
/*! @brief OCOTP timing structure.
 *  Note that, these value are used for calcalating the read/write timings.
 *  And the values should statisfy below rules:
 *
 *  Tsp_rd=(WAIT+1)/ipg_clk_freq should be >= 150ns;
 *  Tsp_pgm=(RELAX+1)/ipg_clk_freq should be >= 100ns;
 *  Trd = ((STROBE_READ+1)- 2*(RELAX_READ+1)) /ipg_clk_freq,
 *  The Trd is required to be larger than 40 ns.
 *  Tpgm = ((STROBE_PROG+1)- 2*(RELAX_PROG+1)) /ipg_clk_freq;
 *  The Tpgm should be configured within the range of 9000 ns < Tpgm < 11000 ns;
 */
typedef struct _ocotp_timing
{
    uint32_t wait;        /*!< Wait time value to fill in the TIMING register. */
    uint32_t relax;       /*!< Relax time value to fill in the TIMING register. */
    uint32_t strobe_prog; /*!< Storbe program time value to fill in the TIMING register. */
    uint32_t strobe_read; /*!< Storbe read time value to fill in the TIMING register. */
} ocotp_timing_t;
#endif /* FSL_FEATURE_OCOTP_HAS_TIMING_CTRL */

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes OCOTP controller.
 *
 * @param base         OCOTP peripheral base address.
 * @param srcClock_Hz  source clock frequency in unit of Hz. When the macro
 * FSL_FEATURE_OCOTP_HAS_TIMING_CTRL is defined as 0, this parameter is not used,
 * application could pass in 0 in this case.
 */
void OCOTP_Init(OCOTP_Type *base, uint32_t srcClock_Hz);

/*!
 * @brief De-initializes OCOTP controller.
 *
 * @retval kStatus_Success upon successful execution, error status otherwise.
 */
void OCOTP_Deinit(OCOTP_Type *base);

/*!
 * @brief Checking the BUSY bit in CTRL register.
 * Checking this BUSY bit will help confirm if the OCOTP controller is ready for access.
 *
 * @param base         OCOTP peripheral base address.
 * @retval       true for bit set and false for cleared.
 */
static inline bool OCOTP_CheckBusyStatus(OCOTP_Type *base)
{
    return ((OCOTP_CTRL_BUSY_MASK == (base->CTRL & OCOTP_CTRL_BUSY_MASK)) ? (true) : (false));
}

/*!
 * @brief Checking the ERROR bit in CTRL register.
 *
 * @param base         OCOTP peripheral base address.
 * @retval       true for bit set and false for cleared.
 */
static inline bool OCOTP_CheckErrorStatus(OCOTP_Type *base)
{
    return ((OCOTP_CTRL_ERROR_MASK == (base->CTRL & OCOTP_CTRL_ERROR_MASK)) ? (true) : (false));
}

/*!
 * @brief Clear the error bit if this bit is set.
 *
 * @param base  OCOTP peripheral base address.
 */
static inline void OCOTP_ClearErrorStatus(OCOTP_Type *base)
{
    base->CTRL_CLR = OCOTP_CTRL_CLR_ERROR_MASK;
}

/*!
 * @brief Reload the shadow register.
 * This function will help reload the shadow register without reseting the OCOTP module.
 * Please make sure the OCOTP has been initialized before calling this API.
 *
 * @param base OCOTP peripheral base addess.
 * @retval kStatus_Success Reload success.
 * @retval kStatus_OCOTP_ReloadError Reload failed.
 */
status_t OCOTP_ReloadShadowRegister(OCOTP_Type *base);

/*!
 * @brief Read the fuse shadow register with the fuse addess.
 *
 * @deprecated Use @ref OCOTP_ReadFuseShadowRegisterExt instead of this function.
 *
 * @param base     OCOTP peripheral base address.
 * @param address  the fuse address to be read from.
 * @return The read out data.
 */
uint32_t OCOTP_ReadFuseShadowRegister(OCOTP_Type *base, uint32_t address);

/*!
 * @brief Read the fuse shadow register from the fuse addess.
 *
 * This function reads fuse from @p address, how many words to read is specified
 * by the parameter @p fuseWords. This function could read at most
 * OCOTP_READ_FUSE_DATA_COUNT fuse word one time.
 *
 * @param base     OCOTP peripheral base address.
 * @param address  the fuse address to be read from.
 * @param data     Data array to save the readout fuse value.
 * @param fuseWords How many words to read.
 * @retval kStatus_Success Read success.
 * @retval kStatus_Fail Error occurs during read.
 */
status_t OCOTP_ReadFuseShadowRegisterExt(OCOTP_Type *base, uint32_t address, uint32_t *data, uint8_t fuseWords);

/*!
 * @brief Write the fuse shadow register with the fuse addess and data.
 * Please make sure the wrtie address is not locked while calling this API.
 *
 * @param base     OCOTP peripheral base address.
 * @param address  the fuse address to be written.
 * @param data     the value will be writen to fuse address.
 * @retval   write status, kStatus_Success for success and kStatus_Fail for failed.
 */
status_t OCOTP_WriteFuseShadowRegister(OCOTP_Type *base, uint32_t address, uint32_t data);

/*!
 * @brief Write the fuse shadow register and lock it.
 *
 * Please make sure the wrtie address is not locked while calling this API.
 *
 * Some OCOTP controller supports ECC mode and redundancy mode (see reference mananual
 * for more details). OCOTP controller will auto select ECC or redundancy
 * mode to program the fuse word according to fuse map definition. In ECC mode, the
 * 32 fuse bits in one word can only be written once. In redundancy mode, the word can
 * be written more than once as long as they are different fuse bits. Set parameter
 * @p lock as true to force use ECC mode.
 *
 * @param base     OCOTP peripheral base address.
 * @param address  The fuse address to be written.
 * @param data     The value will be writen to fuse address.
 * @param lock     Lock or unlock write fuse shadow register operation.
 * @retval kStatus_Success Program and reload success.
 * @retval kStatus_OCOTP_Locked The eFuse word is locked and cannot be programmed.
 * @retval kStatus_OCOTP_ProgramFail eFuse word programming failed.
 * @retval kStatus_OCOTP_ReloadError eFuse word programming success, but
 *         error happens during reload the values.
 * @retval kStatus_OCOTP_AccessError Cannot access eFuse word.
 */
status_t OCOTP_WriteFuseShadowRegisterWithLock(OCOTP_Type *base, uint32_t address, uint32_t data, bool lock);

/*!
 * @brief Get the OCOTP controller version from the register.
 *
 * @param base    OCOTP peripheral base address.
 * @retval  return the version value.
 */
static inline uint32_t OCOTP_GetVersion(OCOTP_Type *base)
{
    return (base->VERSION);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_OCOTP_H_ */
