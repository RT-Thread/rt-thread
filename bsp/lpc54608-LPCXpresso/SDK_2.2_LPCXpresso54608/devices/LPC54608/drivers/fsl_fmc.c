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

#include "fsl_fmc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void FMC_GetDefaultConfig(fmc_config_t *config)
{
    config->waitStates = 0x05;
}

void FMC_Init(FMC_Type *base, fmc_config_t *config)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* enable clock to FMC */
    CLOCK_EnableClock(kCLOCK_Fmc);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Set control register, FS_RD0 = 0, FS_RD1 = 1. */
    base->FCTR &= ~(FMC_FCTR_FS_RD0_MASK | FMC_FCTR_FS_RD1_MASK);
    base->FCTR |= FMC_FCTR_FS_RD1_MASK;

    /* Set wait state, same as FLASHTIM in SYSCON->FLASHCFG register. */
    base->FBWST &= ~FMC_FBWST_WAITSTATES_MASK;
    base->FBWST |= config->waitStates;
}

void FMC_Denit(FMC_Type *base)
{
    /* Reset FMC module */
    RESET_PeripheralReset(kFMC_RST_SHIFT_RSTn);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* enable clock to FMC */
    CLOCK_DisableClock(kCLOCK_Fmc);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void FMC_GenerateFlashSignature(FMC_Type *base,
                                uint32_t startAddress,
                                uint32_t length,
                                fmc_flash_signature_t *flashSignature)
{
    uint32_t stopAddress;

    /* Clear generation done flag. */
    base->FMSTATCLR = kFMC_SignatureGenerationDoneFlag;

    /* Calculate flash stop address */
    stopAddress = ((startAddress + length - 1) >> 4) & FMC_FMSSTOP_STOP_MASK;

    /* Calculate flash start address. */
    startAddress = (startAddress >> 4) & FMC_FMSSTART_START_MASK;

    /* Start flash signature generation. */
    base->FMSSTART = startAddress;
    base->FMSSTOP = stopAddress;

    base->FMSSTOP |= FMC_FMSSTOP_SIG_START_MASK;

    /* Wait for signature done. */
    while ((base->FMSTAT & kFMC_SignatureGenerationDoneFlag) != kFMC_SignatureGenerationDoneFlag)
    {
    }

    /* Clear generation done flag. */
    base->FMSTATCLR = kFMC_SignatureGenerationDoneFlag;

    /* Get the generated flash signature. */
    flashSignature->word0 = base->FMSW[0];
    flashSignature->word1 = base->FMSW[1];
    flashSignature->word2 = base->FMSW[2];
    flashSignature->word3 = base->FMSW[3];

    return;
}
