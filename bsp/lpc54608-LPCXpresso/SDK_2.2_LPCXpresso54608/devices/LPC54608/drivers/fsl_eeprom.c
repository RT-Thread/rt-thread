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

#include "fsl_eeprom.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the EEPROM instance from peripheral base address.
 *
 * @param base EEPROM peripheral base address.
 * @return EEPROM instance.
 */
static uint32_t EEPROM_GetInstance(EEPROM_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of EEPROM peripheral base address. */
static EEPROM_Type *const s_eepromBases[] = EEPROM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of EEPROM clock name. */
static const clock_ip_name_t s_eepromClock[] = EEPROM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EEPROM_GetInstance(EEPROM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_eepromBases); instance++)
    {
        if (s_eepromBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_eepromBases));

    return instance;
}

void EEPROM_GetDefaultConfig(eeprom_config_t *config)
{
    config->autoProgram = kEEPROM_AutoProgramWriteWord;
    config->writeWaitPhase1 = 0x5U;
    config->writeWaitPhase2 = 0x9U;
    config->writeWaitPhase3 = 0x3U;
    config->readWaitPhase1 = 0xFU;
    config->readWaitPhase2 = 0x8U;
    config->lockTimingParam = false;
}

void EEPROM_Init(EEPROM_Type *base, const eeprom_config_t *config, uint32_t sourceClock_Hz)
{
    assert(config);

    uint32_t clockDiv = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the SAI clock */
    CLOCK_EnableClock(s_eepromClock[EEPROM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Set the clock divider */
    clockDiv = sourceClock_Hz / FSL_FEATURE_EEPROM_INTERNAL_FREQ;
    if ((sourceClock_Hz % FSL_FEATURE_EEPROM_INTERNAL_FREQ) > (FSL_FEATURE_EEPROM_INTERNAL_FREQ / 2U))
    {
        clockDiv += 1U;
    }
    base->CLKDIV = clockDiv - 1U;

    /* Set the auto program feature */
    EEPROM_SetAutoProgram(base, config->autoProgram);

    /* Set time delay parameter */
    base->RWSTATE =
        EEPROM_RWSTATE_RPHASE1(config->readWaitPhase1 - 1U) | EEPROM_RWSTATE_RPHASE2(config->readWaitPhase2 - 1U);
    base->WSTATE = EEPROM_WSTATE_PHASE1(config->writeWaitPhase1 - 1U) |
                   EEPROM_WSTATE_PHASE2(config->writeWaitPhase2 - 1U) |
                   EEPROM_WSTATE_PHASE3(config->writeWaitPhase3 - 1U);
    base->WSTATE |= EEPROM_WSTATE_LCK_PARWEP(config->lockTimingParam);
 
    /* Clear the remaining write operation  */
    base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
    while ((EEPROM_GetInterruptStatus(base) & kEEPROM_ProgramFinishInterruptEnable) == 0U)
    {}
}

void EEPROM_Deinit(EEPROM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the SAI clock */
    CLOCK_DisableClock(s_eepromClock[EEPROM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

status_t EEPROM_WriteWord(EEPROM_Type *base, uint32_t offset, uint32_t data)
{
    uint32_t *addr = 0;

    if ((offset % 4U) || (offset > FSL_FEATURE_EEPROM_SIZE))
    {
        return kStatus_InvalidArgument;
    }

    /* Set auto program settings */
    if (base->AUTOPROG != kEEPROM_AutoProgramDisable)
    {
        EEPROM_SetAutoProgram(base, kEEPROM_AutoProgramWriteWord);
    }

    EEPROM_ClearInterruptFlag(base, kEEPROM_ProgramFinishInterruptEnable);

    /* Compute the page */
    addr = (uint32_t *)(FSL_FEATURE_EEPROM_BASE_ADDRESS + offset);
    *addr = data;

    /* Check if need to do program erase manually */
    if (base->AUTOPROG != kEEPROM_AutoProgramWriteWord)
    {
        base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
    }

    /* Waiting for operation finished */
    while ((EEPROM_GetInterruptStatus(base) & kEEPROM_ProgramFinishInterruptEnable) == 0U)
    {}

    return kStatus_Success;
}

status_t EEPROM_WritePage(EEPROM_Type *base, uint32_t pageNum, uint32_t *data)
{
    uint32_t i = 0;
    uint32_t *addr = NULL;

    if ((pageNum > FSL_FEATURE_EEPROM_PAGE_COUNT) || (!data))
    {
        return kStatus_InvalidArgument;
    }

    /* Set auto program settings */
    if (base->AUTOPROG != kEEPROM_AutoProgramDisable)
    {
        EEPROM_SetAutoProgram(base, kEEPROM_AutoProgramLastWord);
    }

    EEPROM_ClearInterruptFlag(base, kEEPROM_ProgramFinishInterruptEnable);

    addr = (uint32_t *)(FSL_FEATURE_EEPROM_BASE_ADDRESS + pageNum * (FSL_FEATURE_EEPROM_SIZE/FSL_FEATURE_EEPROM_PAGE_COUNT));
    for (i = 0; i < (FSL_FEATURE_EEPROM_SIZE/FSL_FEATURE_EEPROM_PAGE_COUNT) / 4U; i++)
    {
        addr[i] = data[i];
    }

    if (base->AUTOPROG == kEEPROM_AutoProgramDisable)
    {
        base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
    }

    /* Waiting for operation finished */
    while ((EEPROM_GetInterruptStatus(base) & kEEPROM_ProgramFinishInterruptEnable) == 0U)
    {}

    return kStatus_Success;
}
