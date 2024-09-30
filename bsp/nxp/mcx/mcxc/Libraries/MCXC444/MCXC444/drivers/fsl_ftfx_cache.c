/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_ftfx_cache.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flash"
#endif

/*!
 * @name Flash cache and speculation control defines
 * @{
 */
#if defined(MCM_PLACR_CFCC_MASK)
#define FLASH_CACHE_IS_CONTROLLED_BY_MCM (1u)
#else
#define FLASH_CACHE_IS_CONTROLLED_BY_MCM (0u)
#endif

#define FLASH_CACHE_IS_CONTROLLED_BY_MSCM (0u)

#if defined(FMC_PFB0CR_CINV_WAY_MASK) || defined(FMC_PFB01CR_CINV_WAY_MASK)
#define FLASH_CACHE_IS_CONTROLLED_BY_FMC (1u)
#else
#define FLASH_CACHE_IS_CONTROLLED_BY_FMC (0u)
#endif

#if defined(MCM_PLACR_DFCS_MASK)
#define FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MCM (1u)
#else
#define FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MCM (0u)
#endif

#if defined(MSCM_OCMDR_OCMC1_MASK) || defined(MSCM_OCMDR_OCM1_MASK) || defined(MSCM_OCMDR0_OCM1_MASK) || \
    defined(MSCM_OCMDR1_OCM1_MASK)
#define FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM (1u)
#else
#define FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM (0u)
#endif

#if defined(FMC_PFB0CR_S_INV_MASK) || defined(FMC_PFB0CR_S_B_INV_MASK) || defined(FMC_PFB01CR_S_INV_MASK) || \
    defined(FMC_PFB01CR_S_B_INV_MASK)
#define FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC (1u)
#else
#define FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC (0u)
#endif

#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM || FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC || \
    FLASH_CACHE_IS_CONTROLLED_BY_MCM || FLASH_CACHE_IS_CONTROLLED_BY_FMC || FLASH_CACHE_IS_CONTROLLED_BY_MSCM
#define FLASH_IS_CACHE_INVALIDATION_AVAILABLE (1)
#else
#define FLASH_IS_CACHE_INVALIDATION_AVAILABLE (0u)
#endif
/*@}*/

/*! @brief A function pointer used to point to relocated ftfx_common_bit_operation() */
typedef void (*callftfxCommonBitOperation_t)(FTFx_REG32_ACCESS_TYPE base,
                                             uint32_t bitMask,
                                             uint32_t bitShift,
                                             uint32_t bitValue);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if FLASH_CACHE_IS_CONTROLLED_BY_MCM
/*! @brief Performs the cache clear to the flash by MCM.*/
void mcm_flash_cache_clear(ftfx_cache_config_t *config);
#endif /* FLASH_CACHE_IS_CONTROLLED_BY_MCM */

#if FLASH_CACHE_IS_CONTROLLED_BY_MSCM
/*! @brief Performs the cache clear to the flash by MSCM.*/
void mscm_flash_cache_clear(ftfx_cache_config_t *config);
#endif /* FLASH_CACHE_IS_CONTROLLED_BY_MSCM */

#if FLASH_CACHE_IS_CONTROLLED_BY_FMC
/*! @brief Performs the cache clear to the flash by FMC.*/
void fmc_flash_cache_clear(ftfx_cache_config_t *config);
#endif /* FLASH_CACHE_IS_CONTROLLED_BY_FMC */

#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM
/*! @brief Sets the prefetch speculation buffer to the flash by MSCM.*/
void mscm_flash_prefetch_speculation_enable(ftfx_cache_config_t *config, bool enable);
#endif /* FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM */

#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC
/*! @brief Performs the prefetch speculation buffer clear to the flash by FMC.*/
void fmc_flash_prefetch_speculation_clear(ftfx_cache_config_t *config);
#endif /* FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC */

#if FTFx_DRIVER_IS_FLASH_RESIDENT && \
       (FLASH_CACHE_IS_CONTROLLED_BY_MCM || FLASH_CACHE_IS_CONTROLLED_BY_MSCM || \
        FLASH_CACHE_IS_CONTROLLERD_BY_FMC || FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM || \
        FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC)
static void ftfx_common_bit_operation_command_sequence(
    ftfx_cache_config_t *config, FTFx_REG32_ACCESS_TYPE base, uint32_t bitMask, uint32_t bitShift, uint32_t bitValue);
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

#if FTFx_DRIVER_IS_FLASH_RESIDENT && FLASH_IS_CACHE_INVALIDATION_AVAILABLE
/*! @brief Copy flash_cache_clear_command() to RAM*/
static void ftfx_copy_common_bit_operation_to_ram(uint32_t *ftfxCommonBitOperation);
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if FTFx_DRIVER_IS_FLASH_RESIDENT && FLASH_IS_CACHE_INVALIDATION_AVAILABLE
/*!
 * @brief Position independent code of ftfx_common_bit_operation()
 *
 * Note1: The prototype of C function is shown as below:
 * @code
 *   void ftfx_common_bit_operation(FTFx_REG32_ACCESS_TYPE base, uint32_t bitMask, uint32_t bitShift, uint32_t
 * bitValue)
 *   {
 *       if (bitMask)
 *       {
 *           uint32_t value = (((uint32_t)(((uint32_t)(bitValue)) << bitShift)) & bitMask);
 *           *base = (*base & (~bitMask)) | value;
 *       }
 *
 *       __ISB();
 *       __DSB();
 *   }
 * @endcode
 * Note2: The binary code is generated by IAR 7.70.1
 */
static const uint32_t s_ftfxCommonBitOperationFunctionCode[] = {
    0x2900b510u, 0x6804d005u, 0x4093438cu, 0x43214019u, 0xf3bf6001u, 0xf3bf8f6fu, 0xbd108f4fu,
};

#if (!FTFx_DRIVER_IS_EXPORTED)
/*! @brief A static buffer used to hold ftfx_common_bit_operation() */
static uint32_t s_ftfxCommonBitOperation[kFTFx_CACHE_RamFuncMaxSizeInWords];
#endif /* (!FTFx_DRIVER_IS_EXPORTED) */
#endif /* FLASH_IS_CACHE_INVALIDATION_AVAILABLE && FTFx_DRIVER_IS_FLASH_RESIDENT */

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t FTFx_CACHE_Init(ftfx_cache_config_t *config)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

/* copy required flash commands to RAM */
#if FTFx_DRIVER_IS_FLASH_RESIDENT && FLASH_IS_CACHE_INVALIDATION_AVAILABLE
    if (NULL == config->bitOperFuncAddr.callFlashCommand)
    {
#if FTFx_DRIVER_IS_EXPORTED
        return kStatus_FTFx_ExecuteInRamFunctionNotReady;
#else
        config->bitOperFuncAddr.commadAddr = (uint32_t)s_ftfxCommonBitOperation;
#endif /* FTFx_DRIVER_IS_EXPORTED */
    }

    ftfx_copy_common_bit_operation_to_ram((uint32_t *)config->bitOperFuncAddr.commadAddr);
#endif /* FLASH_IS_CACHE_INVALIDATION_AVAILABLE && FTFx_DRIVER_IS_FLASH_RESIDENT */

    return kStatus_FTFx_Success;
}

/*!
 * @brief Flash Cache/Prefetch/Speculation Clear Process
 *
 * This function is used to perform the cache and prefetch speculation clear process to the flash.
 */
status_t FTFx_CACHE_ClearCachePrefetchSpeculation(ftfx_cache_config_t *config, bool isPreProcess)
{
    /* We pass the ftfx register address as a parameter to ftfx_common_bit_operation() instead of using
     * pre-processed MACROs or a global variable in ftfx_common_bit_operation()
     * to make sure that ftfx_common_bit_operation() will be compiled into position-independent code (PIC). */
    if (!isPreProcess)
    {
#if FLASH_CACHE_IS_CONTROLLED_BY_MCM
        mcm_flash_cache_clear(config);
#endif
#if FLASH_CACHE_IS_CONTROLLED_BY_MSCM
        mscm_flash_cache_clear(config);
#endif
#if FLASH_CACHE_IS_CONTROLLED_BY_FMC
        fmc_flash_cache_clear(config);
#endif
#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM
        mscm_flash_prefetch_speculation_enable(config, true);
#endif
#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC
        fmc_flash_prefetch_speculation_clear(config);
#endif
    }
    if (isPreProcess)
    {
#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM
        mscm_flash_prefetch_speculation_enable(config, false);
#endif
    }

    return kStatus_FTFx_Success;
}

status_t FTFx_CACHE_PflashSetPrefetchSpeculation(ftfx_prefetch_speculation_status_t *speculationStatus)
{
#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MCM
    {
        if (true == speculationStatus->instructionOff)
        {
            if (false == speculationStatus->dataOff)
            {
                return kStatus_FTFx_InvalidSpeculationOption;
            }
            else
            {
                MCM0_CACHE_REG |= MCM_PLACR_DFCS_MASK;
            }
        }
        else
        {
            MCM0_CACHE_REG &= ~MCM_PLACR_DFCS_MASK;
            if (false == speculationStatus->dataOff)
            {
                MCM0_CACHE_REG |= MCM_PLACR_EFDS_MASK;
            }
            else
            {
                MCM0_CACHE_REG &= ~MCM_PLACR_EFDS_MASK;
            }
        }
    }
#elif FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC
    {
        if (false == speculationStatus->instructionOff)
        {
            FMC_CACHE_REG |= FMC_CACHE_B0IPE_MASK;
        }
        else
        {
            FMC_CACHE_REG &= ~FMC_CACHE_B0IPE_MASK;
        }
        if (false == speculationStatus->dataOff)
        {
            FMC_CACHE_REG |= FMC_CACHE_B0DPE_MASK;
        }
        else
        {
            FMC_CACHE_REG &= ~FMC_CACHE_B0DPE_MASK;
        }

        /* Invalidate Prefetch Speculation Buffer */
        FMC_SPECULATION_INVALIDATE_REG |= FMC_SPECULATION_INVALIDATE_MASK;
    }
#elif FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM
    {
        if (true == speculationStatus->instructionOff)
        {
            if (false == speculationStatus->dataOff)
            {
                return kStatus_FTFx_InvalidSpeculationOption;
            }
            else
            {
                MSCM_OCMDR0_REG |= MSCM_OCMDR_OCMC1_DFCS_MASK;
            }
        }
        else
        {
            MSCM_OCMDR0_REG &= ~MSCM_OCMDR_OCMC1_DFCS_MASK;
            if (false == speculationStatus->dataOff)
            {
                MSCM_OCMDR0_REG &= ~MSCM_OCMDR_OCMC1_DFDS_MASK;
            }
            else
            {
                MSCM_OCMDR0_REG |= MSCM_OCMDR_OCMC1_DFDS_MASK;
            }
        }
    }
#endif /* FSL_FEATURE_FTFx_MCM_FLASH_CACHE_CONTROLS */

    return kStatus_FTFx_Success;
}

status_t FTFx_CACHE_PflashGetPrefetchSpeculation(ftfx_prefetch_speculation_status_t *speculationStatus)
{
    (void)memset(speculationStatus, 0, sizeof(ftfx_prefetch_speculation_status_t));

    /* Assuming that all speculation options are enabled. */
    speculationStatus->instructionOff = false;
    speculationStatus->dataOff        = false;

#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MCM
    {
        uint32_t value = MCM0_CACHE_REG;
        if (0U != (value & MCM_PLACR_DFCS_MASK))
        {
            /* Speculation buffer is off. */
            speculationStatus->instructionOff = true;
            speculationStatus->dataOff        = true;
        }
        else
        {
            /* Speculation buffer is on for instruction. */
            if (0U == (value & MCM_PLACR_EFDS_MASK))
            {
                /* Speculation buffer is off for data. */
                speculationStatus->dataOff = true;
            }
        }
    }
#elif FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC
    {
        uint32_t value = FMC_CACHE_REG;
        if (0U == (value & FMC_CACHE_B0DPE_MASK))
        {
            /* Do not prefetch in response to data references. */
            speculationStatus->dataOff = true;
        }
        if (0U == (value & FMC_CACHE_B0IPE_MASK))
        {
            /* Do not prefetch in response to instruction fetches. */
            speculationStatus->instructionOff = true;
        }
    }
#elif FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM
    {
        uint32_t value = MSCM_OCMDR0_REG;
        if (0U != (value & MSCM_OCMDR_OCMC1_DFCS_MASK))
        {
            /* Speculation buffer is off. */
            speculationStatus->instructionOff = true;
            speculationStatus->dataOff        = true;
        }
        else
        {
            /* Speculation buffer is on for instruction. */
            if (0U != (value & MSCM_OCMDR_OCMC1_DFDS_MASK))
            {
                /* Speculation buffer is off for data. */
                speculationStatus->dataOff = true;
            }
        }
    }
#endif

    return kStatus_FTFx_Success;
}

#if FTFx_DRIVER_IS_FLASH_RESIDENT && FLASH_IS_CACHE_INVALIDATION_AVAILABLE
/*! @brief Copy PIC of ftfx_common_bit_operation() to RAM */
static void ftfx_copy_common_bit_operation_to_ram(uint32_t *ftfxCommonBitOperation)
{
    assert(sizeof(s_ftfxCommonBitOperationFunctionCode) <= ((uint32_t)kFTFx_CACHE_RamFuncMaxSizeInWords * 4U));

    (void)memcpy(ftfxCommonBitOperation, s_ftfxCommonBitOperationFunctionCode,
                 sizeof(s_ftfxCommonBitOperationFunctionCode));
}
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT && FLASH_IS_CACHE_INVALIDATION_AVAILABLE */

#if FTFx_DRIVER_IS_FLASH_RESIDENT && \
       (FLASH_CACHE_IS_CONTROLLED_BY_MCM || FLASH_CACHE_IS_CONTROLLED_BY_MSCM || \
        FLASH_CACHE_IS_CONTROLLERD_BY_FMC || FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM || \
        FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC)
static void ftfx_common_bit_operation_command_sequence(
    ftfx_cache_config_t *config, FTFx_REG32_ACCESS_TYPE base, uint32_t bitMask, uint32_t bitShift, uint32_t bitValue)
{
    uint32_t *ftfxCommonBitOperationAddr;
    ftfxCommonBitOperationAddr = &config->bitOperFuncAddr.commadAddr;
    /* Since the value of ARM function pointer is always odd, but the real start
     * address
     * of function memory should be even, that's why +1 operation exist. */
    *ftfxCommonBitOperationAddr += 1UL;
    callftfxCommonBitOperation_t ftfxCommonBitOperationCommand = config->bitOperFuncAddr.callFlashCommand;
    /* Workround for some devices which doesn't need this function */
    ftfxCommonBitOperationCommand((FTFx_REG32_ACCESS_TYPE)base, bitMask, bitShift, bitValue);
    *ftfxCommonBitOperationAddr -= 1UL;
}
#endif /*FTFx_DRIVER_IS_FLASH_RESIDENT*/

#if FLASH_CACHE_IS_CONTROLLED_BY_MCM
/*! @brief Performs the cache clear to the flash by MCM.*/
void mcm_flash_cache_clear(ftfx_cache_config_t *config)
{
    FTFx_REG32_ACCESS_TYPE regBase;

#if defined(MCM0_CACHE_REG)
    regBase = (FTFx_REG32_ACCESS_TYPE)&MCM0_CACHE_REG;
#elif defined(MCM1_CACHE_REG)
    regBase = (FTFx_REG32_ACCESS_TYPE)&MCM1_CACHE_REG;
#endif

#if FTFx_DRIVER_IS_FLASH_RESIDENT
    /* calling flash command sequence function to execute the command */
    ftfx_common_bit_operation_command_sequence(config, regBase, MCM_CACHE_CLEAR_MASK, MCM_CACHE_CLEAR_SHIFT, 1UL);

#else  /* !FTFx_DRIVER_IS_FLASH_RESIDENT */
    *regBase |= MCM_CACHE_CLEAR_MASK;

    /* Memory barriers for good measure.
     * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
    __ISB();
    __DSB();
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */
}
#endif /* FLASH_CACHE_IS_CONTROLLED_BY_MCM */

#if FLASH_CACHE_IS_CONTROLLED_BY_MSCM
/*! @brief Performs the cache clear to the flash by MSCM.*/
void mscm_flash_cache_clear(ftfx_cache_config_t *config)
{
    uint8_t setValue = 0x1U;

/* The OCMDR[0] is always used to cache main Pflash*/
/* For device with FlexNVM support, the OCMDR[1] is used to cache Dflash.
 * For device with secondary flash support, the OCMDR[1] is used to cache secondary Pflash. */
#if FTFx_DRIVER_IS_FLASH_RESIDENT
    switch (config->flashMemoryIndex)
    {
        case kFLASH_MemoryIndexSecondaryFlash:
            /* calling flash command sequence function to execute the command */
            ftfx_common_bit_operation_command_sequence(config, (FTFx_REG32_ACCESS_TYPE)&MSCM_OCMDR1_REG,
                                                       MSCM_CACHE_CLEAR_MASK, MSCM_CACHE_CLEAR_SHIFT, setValue);
            break;
        case kFLASH_MemoryIndexPrimaryFlash:
        default:
            /* calling flash command sequence function to execute the command */
            ftfx_common_bit_operation_command_sequence(config, (FTFx_REG32_ACCESS_TYPE)&MSCM_OCMDR0_REG,
                                                       MSCM_CACHE_CLEAR_MASK, MSCM_CACHE_CLEAR_SHIFT, setValue);
            break;
    }
#else  /* !FTFx_DRIVER_IS_FLASH_RESIDENT */
    switch (config->flashMemoryIndex)
    {
        case kFLASH_MemoryIndexSecondaryFlash:
            MSCM_OCMDR1_REG = (MSCM_OCMDR1_REG & (~MSCM_CACHE_CLEAR_MASK)) | MSCM_CACHE_CLEAR(setValue);
            /* Each cache clear instruction should be followed by below code*/
            __ISB();
            __DSB();
            break;
        case kFLASH_MemoryIndexPrimaryFlash:
        default:
            MSCM_OCMDR0_REG = (MSCM_OCMDR0_REG & (~MSCM_CACHE_CLEAR_MASK)) | MSCM_CACHE_CLEAR(setValue);
            /* Memory barriers for good measure.
             * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
            __ISB();
            __DSB();
            break;
    }
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */
}
#endif /* FLASH_CACHE_IS_CONTROLLED_BY_MSCM */

#if FLASH_CACHE_IS_CONTROLLED_BY_FMC
/*! @brief Performs the cache clear to the flash by FMC.*/
void fmc_flash_cache_clear(ftfx_cache_config_t *config)
{
#if FTFx_DRIVER_IS_FLASH_RESIDENT
    /* calling flash command sequence function to execute the command */
    ftfx_common_bit_operation_command_sequence(config, (FTFx_REG32_ACCESS_TYPE)&FMC_CACHE_REG, FMC_CACHE_CLEAR_MASK,
                                               FMC_CACHE_CLEAR_SHIFT, 0xFUL);
#else  /* !FTFx_DRIVER_IS_FLASH_RESIDENT */
    FMC_CACHE_REG = (FMC_CACHE_REG & (~FMC_CACHE_CLEAR_MASK)) | FMC_CACHE_CLEAR(~0);
    /* Memory barriers for good measure.
     * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
    __ISB();
    __DSB();
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */
}
#endif /* FLASH_CACHE_IS_CONTROLLED_BY_FMC */

#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM
/*! @brief Performs the prefetch speculation buffer clear to the flash by MSCM.*/
void mscm_flash_prefetch_speculation_enable(ftfx_cache_config_t *config, bool enable)
{
    uint8_t setValue;
    if (enable)
    {
        setValue = 0x0U;
    }
    else
    {
        setValue = 0x3U;
    }

/* The OCMDR[0] is always used to prefetch main Pflash*/
/* For device with FlexNVM support, the OCMDR[1] is used to prefetch Dflash.
 * For device with secondary flash support, the OCMDR[1] is used to prefetch secondary Pflash. */
#if FTFx_DRIVER_IS_FLASH_RESIDENT

    switch (config->flashMemoryIndex)
    {
        case 1:
            /* calling flash command sequence function to execute the command */
            ftfx_common_bit_operation_command_sequence(config, (FTFx_REG32_ACCESS_TYPE)&MSCM_OCMDR1_REG,
                                                       MSCM_SPECULATION_SET_MASK, MSCM_SPECULATION_SET_SHIFT, setValue);
            break;
        case 0:
        default:
            /* calling flash command sequence function to execute the command */
            ftfx_common_bit_operation_command_sequence(config, (FTFx_REG32_ACCESS_TYPE)&MSCM_OCMDR0_REG,
                                                       MSCM_SPECULATION_SET_MASK, MSCM_SPECULATION_SET_SHIFT, setValue);
            break;
    }
#else  /* !FTFx_DRIVER_IS_FLASH_RESIDENT */
    switch (config->flashMemoryIndex)
    {
        case kFLASH_MemoryIndexSecondaryFlash:
            MSCM_OCMDR1_REG = (MSCM_OCMDR1_REG & (~MSCM_SPECULATION_SET_MASK)) | MSCM_SPECULATION_SET(setValue);
            /* Each cache clear instruction should be followed by below code*/
            __ISB();
            __DSB();
            break;
        case kFLASH_MemoryIndexPrimaryFlash:
        default:
            MSCM_OCMDR0_REG = (MSCM_OCMDR0_REG & (~MSCM_SPECULATION_SET_MASK)) | MSCM_SPECULATION_SET(setValue);
            /* Memory barriers for good measure.
             * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
            __ISB();
            __DSB();
            break;
    }
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */
}
#endif /* FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_MSCM */

#if FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC
/*! @brief Performs the prefetch speculation buffer clear to the flash by FMC.*/
void fmc_flash_prefetch_speculation_clear(ftfx_cache_config_t *config)
{
#if FTFx_DRIVER_IS_FLASH_RESIDENT
    /* calling flash command sequence function to execute the command */
    ftfx_common_bit_operation_command_sequence(config, (FTFx_REG32_ACCESS_TYPE)&FMC_SPECULATION_INVALIDATE_REG,
                                               FMC_SPECULATION_INVALIDATE_MASK, FMC_SPECULATION_INVALIDATE_SHIFT, 1UL);
#else  /* !FTFx_DRIVER_IS_FLASH_RESIDENT */
    FMC_SPECULATION_INVALIDATE_REG |= FMC_SPECULATION_INVALIDATE_MASK;
    /* Memory barriers for good measure.
     * All Cache, Branch predictor and TLB maintenance operations before this instruction complete */
    __ISB();
    __DSB();
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */
}
#endif /* FLASH_PREFETCH_SPECULATION_IS_CONTROLLED_BY_FMC */
