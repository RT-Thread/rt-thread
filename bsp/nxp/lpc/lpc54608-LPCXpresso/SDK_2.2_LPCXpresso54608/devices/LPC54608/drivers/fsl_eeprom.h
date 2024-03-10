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
#ifndef _FSL_EEPROM_H_
#define _FSL_EEPROM_H_

#include "fsl_common.h"

/*!
 * @addtogroup eeprom
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief EEPROM driver version 2.0.0. */
#define FSL_EEPROM_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief EEPROM automatic program option */
typedef enum _eeprom_auto_program
{
    kEEPROM_AutoProgramDisable = 0x0,   /*!< Disable auto program */
    kEEPROM_AutoProgramWriteWord = 0x1, /*!< Auto program triggered after 1 word is written */
    kEEPROM_AutoProgramLastWord = 0x2   /*!< Auto program triggered after last word of a page written */
} eeprom_auto_program_t;

/*! @brief EEPROM interrupt source */
typedef enum _eeprom_interrupt_enable
{
    kEEPROM_ProgramFinishInterruptEnable = EEPROM_INTENSET_PROG_SET_EN_MASK, /*!< Interrupt while program finished */
} eeprom_interrupt_enable_t;

/*!
 * @brief EEPROM region configuration structure.
 */
typedef struct _eeprom_config
{
    eeprom_auto_program_t autoProgram; /*!< Automatic program feature. */
    uint8_t readWaitPhase1;            /*!< EEPROM read waiting phase 1 */
    uint8_t readWaitPhase2;            /*!< EEPROM read waiting phase 2 */
    uint8_t writeWaitPhase1;           /*!< EEPROM write waiting phase 1 */
    uint8_t writeWaitPhase2;           /*!< EEPROM write waiting phase 2 */
    uint8_t writeWaitPhase3;           /*!< EEPROM write waiting phase 3 */
    bool lockTimingParam;              /*!< If lock the read and write wait phase settings */
} eeprom_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the EEPROM with the user configuration structure.
 *
 * This function configures the EEPROM module with the user-defined configuration. This function also sets the
 * internal clock frequency to about 155kHz according to the source clock frequency.
 *
 * @param base     EEPROM peripheral base address.
 * @param config   The pointer to the configuration structure.
 * @param sourceClock_Hz EEPROM source clock frequency in Hz.
 */
void EEPROM_Init(EEPROM_Type *base, const eeprom_config_t *config, uint32_t sourceClock_Hz);

/*!
 * @brief Get EEPROM default configure settings.
 *
 * @param config  EEPROM config structure pointer.
 */
void EEPROM_GetDefaultConfig(eeprom_config_t *config);

/*!
 * @brief Deinitializes the EEPROM regions.
 *
 * @param base     EEPROM peripheral base address.
 */
void EEPROM_Deinit(EEPROM_Type *base);

/* @}*/

/*!
 * @name Basic Control Operations
 * @{
 */

/*!
 * @brief Set EEPROM automatic program feature.
 *
 * EEPROM write always needs a program and erase cycle to write the data into EEPROM. This program and erase cycle can
 * be finished automaticlly or manually. If users want to use or disable auto program feature, users can call this API.
 *
 * @param base     EEPROM peripheral base address.
 * @param autoProgram EEPROM auto program feature need to set.
 */
static inline void EEPROM_SetAutoProgram(EEPROM_Type *base, eeprom_auto_program_t autoProgram)
{
    base->AUTOPROG = autoProgram;
}

/*!
 * @brief Set EEPROM to in/out power down mode.
 *
 * This function make EEPROM eneter or out of power mode. Notice that, users shall not put EEPROM into power down mode
 * while there is still any pending EEPROM operation. While EEPROM is wakes up from power down mode, any EEPROM
 * operation has to be suspended for 100 us.
 *
 * @param base     EEPROM peripheral base address.
 * @param enable   True means enter to power down mode, false means wake up.
 */
static inline void EEPROM_SetPowerDownMode(EEPROM_Type *base, bool enable)
{
    base->PWRDWN = enable;
}

/*!
 * @brief Enable EEPROM interrupt.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt enable mask. It is a logic OR of members the
 *                 enumeration :: eeprom_interrupt_enable_t
 */
static inline void EEPROM_EnableInterrupt(EEPROM_Type *base, uint32_t mask)
{
    base->INTENSET = mask;
}

/*!
 * @brief Disable EEPROM interrupt.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt enable mask. It is a logic OR of members the
 *                 enumeration :: eeprom_interrupt_enable_t
 */
static inline void EEPROM_DisableInterrupt(EEPROM_Type *base, uint32_t mask)
{
    base->INTENCLR = mask;
}

/*!
 * @brief Get the status of all interrupt flags for ERPROM.
 *
 * @param base     EEPROM peripheral base address.
 * @return EEPROM interrupt flag status
 */
static inline uint32_t EEPROM_GetInterruptStatus(EEPROM_Type *base)
{
    return base->INTSTAT;
}

/*!
 * @brief Get the status of enabled interrupt flags for ERPROM.
 *
 * @param base     EEPROM peripheral base address.
 * @return EEPROM enabled interrupt flag status
 */
static inline uint32_t EEPROM_GetEnabledInterruptStatus(EEPROM_Type *base)
{
    return base->INTEN;
}

/*!
 * @brief Set interrupt flags manually.
 *
 * This API trigger a interrupt manually, users can no need to wait for hardware trigger interrupt. Call this API will
 * set the corresponding bit in INSTAT register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt flag need to be set. It is a logic OR of members of
 *                 enumeration:: eeprom_interrupt_enable_t
 */
static inline void EEPROM_SetInterruptFlag(EEPROM_Type *base, uint32_t mask)
{
    base->INTSTATSET = mask;
}

/*!
 * @brief Clear interrupt flags manually.
 *
 * This API clears interrupt flags manually. Call this API will clear the corresponding bit in INSTAT register.
 *
 * @param base     EEPROM peripheral base address.
 * @param mask     EEPROM interrupt flag need to be cleared. It is a logic OR of members of
 *                 enumeration:: eeprom_interrupt_enable_t
 */
static inline void EEPROM_ClearInterruptFlag(EEPROM_Type *base, uint32_t mask)
{
    base->INTSTATCLR = mask;
}

/*!
 * @brief Write a word data in address of EEPROM.
 *
 * Users can write a page or at least a word data into EEPROM address.
 *
 * @param base     EEPROM peripheral base address.
 * @param offset   Offset from the begining address of EEPROM. This value shall be 4-byte aligned.
 * @param data     Data need be write.
 */
status_t EEPROM_WriteWord(EEPROM_Type *base, uint32_t offset, uint32_t data);

/*!
 * @brief Write a page data into EEPROM.
 *
 * Users can write a page or at least a word data into EEPROM address.
 *
 * @param base     EEPROM peripheral base address.
 * @param pageNum  Page number to be written.
 * @param data     Data need be write. This array data size shall equals to the page size.
 */
status_t EEPROM_WritePage(EEPROM_Type *base, uint32_t pageNum, uint32_t *data);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_EEPROM_H_ */
