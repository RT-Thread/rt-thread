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
#ifndef _FSL_OTP_H_
#define _FSL_OTP_H_

#include "fsl_common.h"

/*!
 * @addtogroup otp
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief OTP driver version 2.0.0.
 *
 * Current version: 2.0.0
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version.
 */
#define FSL_OTP_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief Bank bit flags. */
typedef enum _otp_bank
{
    kOTP_Bank0 = 0x1U, /*!< Bank 0. */
    kOTP_Bank1 = 0x2U, /*!< Bank 1. */
    kOTP_Bank2 = 0x4U, /*!< Bank 2. */
    kOTP_Bank3 = 0x8U  /*!< Bank 3. */
} otp_bank_t;

/*! @brief Bank word bit flags. */
typedef enum _otp_word
{
    kOTP_Word0 = 0x1U, /*!< Word 0. */
    kOTP_Word1 = 0x2U, /*!< Word 1. */
    kOTP_Word2 = 0x4U, /*!< Word 2. */
    kOTP_Word3 = 0x8U  /*!< Word 3. */
} otp_word_t;

/*! @brief Lock modifications of a read or write access to a bank register. */
typedef enum _otp_lock
{
    kOTP_LockDontLock = 0U, /*!< Do not lock. */
    kOTP_LockLock = 1U      /*!< Lock till reset. */
} otp_lock_t;

/*! @brief OTP error codes. */
enum _otp_status
{
    kStatus_OTP_WrEnableInvalid = MAKE_STATUS(kStatusGroup_OTP, 0x1U),           /*!< Write enable invalid. */
    kStatus_OTP_SomeBitsAlreadyProgrammed = MAKE_STATUS(kStatusGroup_OTP, 0x2U), /*!< Some bits already programmed. */
    kStatus_OTP_AllDataOrMaskZero = MAKE_STATUS(kStatusGroup_OTP, 0x3U),         /*!< All data or mask zero. */
    kStatus_OTP_WriteAccessLocked = MAKE_STATUS(kStatusGroup_OTP, 0x4U),         /*!< Write access locked. */
    kStatus_OTP_ReadDataMismatch = MAKE_STATUS(kStatusGroup_OTP, 0x5U),          /*!< Read data mismatch. */
    kStatus_OTP_UsbIdEnabled = MAKE_STATUS(kStatusGroup_OTP, 0x6U),              /*!< USB ID enabled. */
    kStatus_OTP_EthMacEnabled = MAKE_STATUS(kStatusGroup_OTP, 0x7U),             /*!< Ethernet MAC enabled. */
    kStatus_OTP_AesKeysEnabled = MAKE_STATUS(kStatusGroup_OTP, 0x8U),            /*!< AES keys enabled. */
    kStatus_OTP_IllegalBank = MAKE_STATUS(kStatusGroup_OTP, 0x9U),               /*!< Illegal bank. */
    kStatus_OTP_ShufflerConfigNotValid = MAKE_STATUS(kStatusGroup_OTP, 0xAU),    /*!< Shuffler config not valid. */
    kStatus_OTP_ShufflerNotEnabled = MAKE_STATUS(kStatusGroup_OTP, 0xBU),        /*!< Shuffler not enabled. */
    kStatus_OTP_ShufflerCanOnlyProgSingleKey =
        MAKE_STATUS(kStatusGroup_OTP, 0xBU),                              /*!< Shuffler can only program single key. */
    kStatus_OTP_IllegalProgramData = MAKE_STATUS(kStatusGroup_OTP, 0xCU), /*!< Illegal program data. */
    kStatus_OTP_ReadAccessLocked = MAKE_STATUS(kStatusGroup_OTP, 0xDU),   /*!< Read access locked. */
};

#define _OTP_ERR_BASE (0x70000U)
#define _OTP_MAKE_STATUS(errorCode) \
    ((errorCode == 0U) ? kStatus_Success : MAKE_STATUS(kStatusGroup_OTP, ((errorCode)-_OTP_ERR_BASE)))

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes OTP controller.
 *
 * @return kStatus_Success upon successful execution, error status otherwise.
 */
static inline status_t OTP_Init(void)
{
    uint32_t status = OTP_API->otpInit();
    return _OTP_MAKE_STATUS(status);
}

/*!
 * @brief Unlock one or more OTP banks for write access.
 *
 * @param bankMask bit flag that specifies which banks to unlock.
 *
 * @return kStatus_Success upon successful execution, error status otherwise.
 */
static inline status_t OTP_EnableBankWriteMask(otp_bank_t bankMask)
{
    uint32_t status = OTP_API->otpEnableBankWriteMask(bankMask);
    return _OTP_MAKE_STATUS(status);
}

/*!
 * @brief Lock one or more OTP banks for write access.
 *
 * @param bankMask bit flag that specifies which banks to lock.
 *
 * @return kStatus_Success upon successful execution, error status otherwise.
 */
static inline status_t OTP_DisableBankWriteMask(otp_bank_t bankMask)
{
    uint32_t status = OTP_API->otpDisableBankWriteMask(bankMask);
    return _OTP_MAKE_STATUS(status);
}

/*!
 * @brief Locks or unlocks write access to a register of an OTP bank and possibly lock un/locking of it.
 *
 * @param bankIndex OTP bank index, 0 = bank 0, 1 = bank 1 etc.
 * @param regEnableMask bit flag that specifies for which words to enable writing.
 * @param regDisableMask bit flag that specifies for which words to disable writing.
 * @param lockWrite specifies if access set can be modified or is locked till reset.
 *
 * @return kStatus_Success upon successful execution, error status otherwise.
 */
static inline status_t OTP_EnableBankWriteLock(uint32_t bankIndex,
                                               otp_word_t regEnableMask,
                                               otp_word_t regDisableMask,
                                               otp_lock_t lockWrite)
{
    uint32_t status = OTP_API->otpEnableBankWriteLock(bankIndex, regEnableMask, regDisableMask, lockWrite);
    return _OTP_MAKE_STATUS(status);
}

/*!
 * @brief Locks or unlocks read access to a register of an OTP bank and possibly lock un/locking of it.
 *
 * @param bankIndex OTP bank index, 0 = bank 0, 1 = bank 1 etc.
 * @param regEnableMask bit flag that specifies for which words to enable reading.
 * @param regDisableMask bit flag that specifies for which words to disable reading.
 * @param lockWrite specifies if access set can be modified or is locked till reset.
 *
 * @return kStatus_Success upon successful execution, error status otherwise.
 */
static inline status_t OTP_EnableBankReadLock(uint32_t bankIndex,
                                              otp_word_t regEnableMask,
                                              otp_word_t regDisableMask,
                                              otp_lock_t lockWrite)
{
    uint32_t status = OTP_API->otpEnableBankReadLock(bankIndex, regEnableMask, regDisableMask, lockWrite);
    return _OTP_MAKE_STATUS(status);
}

/*!
 * @brief Program a single register in an OTP bank.
 *
 * @param bankIndex OTP bank index, 0 = bank 0, 1 = bank 1 etc.
 * @param regIndex OTP register index.
 * @param value value to write.
 *
 * @return kStatus_Success upon successful execution, error status otherwise.
 */
static inline status_t OTP_ProgramRegister(uint32_t bankIndex, uint32_t regIndex, uint32_t value)
{
    uint32_t status = OTP_API->otpProgramReg(bankIndex, regIndex, value);
    return _OTP_MAKE_STATUS(status);
}

/*!
 * @brief Returns the version of the OTP driver in ROM.
 *
 * @return version.
 */
static inline uint32_t OTP_GetDriverVersion(void)
{
    return OTP_API->otpGetDriverVersion();
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_OTP_H_ */
