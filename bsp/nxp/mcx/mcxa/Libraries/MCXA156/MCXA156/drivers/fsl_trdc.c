/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_trdc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.trdc1"
#endif

/* The memory increment definition in byte of MBC and MRC configuration registers */
#define TRDC_MRC_DOMAIN_INCREMENT 0x100UL
#define TRDC_MBC_DOMAIN_INCREMENT 0x200UL
/* In latest TRDC register definition this macro has been removed from device header file. Add this for backward
 * compatability. */
#ifndef TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL
#define TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL(x) ((uint32_t)(((uint32_t)(x)) << TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL0_SHIFT))
#endif
/* Get the memory increment in for each slave inside MBC */
#define TRDC_MBC_SLAVE_INCREMENT(x) \
    (((x) == 0U) ? (0U) : (((x) == 1U) ? (0x140UL) : (((x) == 2U) ? (0x168UL) : (0x190UL))))

typedef union
{
#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT) && FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT
    trdc_processor_domain_assignment_t _processor_domain_assignment;
    trdc_non_processor_domain_assignment_t _non_processor_domain_assignment;
    trdc_pid_config_t _pid_config;
#endif
#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
    trdc_idau_config_t _idau_config;
#endif
#if (defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC) || \
    (defined(FSL_FEATURE_TRDC_HAS_MRC) && FSL_FEATURE_TRDC_HAS_MRC)
    trdc_memory_access_control_config_t _memory_access_control;
#endif
#if defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC
    trdc_mbc_memory_block_config_t _mbc_memory_blk;
    trdc_mbc_nse_update_config_t _mbc_nse_update;
#endif
    uint32_t _u32;
} trdc_reg32_convert_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/*!
 * brief Gets the TRDC hardware configuration.
 *
 * This function gets the TRDC hardware configurations, including number of bus
 * masters, number of domains, number of MRCs and number of PACs.
 *
 * param base TRDC peripheral base address.
 * param config Pointer to the structure to get the configuration.
 */
void TRDC_GetHardwareConfig(TRDC_Type *base, trdc_hardware_config_t *config)
{
    assert(NULL != config);

    config->masterNumber =
        (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMSTR_MASK) >> TRDC_TRDC_HWCFG0_NMSTR_SHIFT);
    config->domainNumber =
        (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NDID_MASK) >> TRDC_TRDC_HWCFG0_NDID_SHIFT);
    config->mbcNumber =
        (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMBC_MASK) >> TRDC_TRDC_HWCFG0_NMBC_SHIFT);
    config->mrcNumber =
        (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMRC_MASK) >> TRDC_TRDC_HWCFG0_NMRC_SHIFT);
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC
/*!
 * brief Gets the hardware configuration of the one of two slave memories within each MBC(memory block checker).
 *
 * param base TRDC peripheral base address.
 * param config Pointer to the structure to get the configuration.
 * param mbcIdx MBC number.
 * param slvIdx Slave number.
 */
void TRDC_GetMbcHardwareConfig(TRDC_Type *base,
                               trdc_slave_memory_hardware_config_t *config,
                               uint8_t mbcIdx,
                               uint8_t slvIdx)
{
    assert(NULL != config);
#if defined(TRDC_MBC_COUNT) && TRDC_MBC_COUNT
    assert(mbcIdx < (uint8_t)TRDC_MBC_COUNT);
#else
    assert(mbcIdx < (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMBC_MASK) >>
                              TRDC_TRDC_HWCFG0_NMBC_SHIFT));
#endif
    assert(slvIdx < 4U);

    config->blockNum  = TRDC_MBC_BASE(base, mbcIdx)->MBC_MEM_GLBCFG[slvIdx] & TRDC_MBC_MEM_GLBCFG_NBLKS_MASK;
    config->blockSize = (TRDC_MBC_BASE(base, mbcIdx)->MBC_MEM_GLBCFG[slvIdx] & TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_MASK) >>
                        TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_SHIFT;
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT) && FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT
/*!
 * brief Gets the default master domain assignment for the processor bus master.
 *
 * This function gets the default master domain assignment for the processor bus master.
 * It should only be used for the processor bus masters, such as CORE0. This function
 * sets the assignment as follows:
 *
 * code
 * assignment->domainId           = 0U;
 * assignment->domainIdSelect     = kTRDC_DidMda;
 * assignment->lock               = 0U;
 * endcode
 *
 * param domainAssignment Pointer to the assignment structure.
 */
void TRDC_GetDefaultProcessorDomainAssignment(trdc_processor_domain_assignment_t *domainAssignment)
{
    assert(NULL != domainAssignment);

    /* Initializes the configure structure to zero. */
    (void)memset(domainAssignment, 0, sizeof(*domainAssignment));
}

/*!
 * brief Gets the default master domain assignment for non-processor bus master.
 *
 * This function gets the default master domain assignment for non-processor bus master.
 * It should only be used for the non-processor bus masters, such as DMA. This function
 * sets the assignment as follows:
 *
 * code
 * assignment->domainId            = 0U;
 * assignment->privilegeAttr       = kTRDC_ForceUser;
 * assignment->secureAttr       = kTRDC_ForceSecure;
 * assignment->bypassDomainId      = 0U;
 * assignment->lock                = 0U;
 * endcode
 *
 * param domainAssignment Pointer to the assignment structure.
 */
void TRDC_GetDefaultNonProcessorDomainAssignment(trdc_non_processor_domain_assignment_t *domainAssignment)
{
    assert(NULL != domainAssignment);

    /* Initializes the configure structure to zero. */
    (void)memset(domainAssignment, 0, sizeof(*domainAssignment));
}

/*!
 * brief Sets the processor bus master domain assignment.
 *
 * This function sets the processor master domain assignment as valid.
 * One bus master might have multiple domain assignment registers. The parameter
 * \p assignIndex specifies which assignment register to set.
 *
 * Example: Set domain assignment for core 0.
 *
 * code
 * trdc_processor_domain_assignment_t processorAssignment;
 *
 * TRDC_GetDefaultProcessorDomainAssignment(&processorAssignment);
 *
 * processorAssignment.domainId = 0;
 * processorAssignment.xxx      = xxx;
 * TRDC_SetMasterDomainAssignment(TRDC, 1, &processorAssignment);
 * endcode
 *
 * param base TRDC peripheral base address.
 * param master Which master to configure, refer to trdcx_master_t in processor header file, x is trdc instance.
 * param regNum Which register to configure, processor master can have more than one register for the MDAC
 * configuration. param domainAssignment Pointer to the assignment structure.
 */
void TRDC_SetProcessorDomainAssignment(TRDC_Type *base,
                                       uint8_t master,
                                       uint8_t regNum,
                                       const trdc_processor_domain_assignment_t *domainAssignment)
{
    /* Make sure the master number does not exceed the max master count. */
    assert(master <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMSTR_MASK) >> TRDC_TRDC_HWCFG0_NMSTR_SHIFT));
    /* Make sure the master is a processor master. */
    assert(0U == (TRDC_GENERAL_BASE(base)->DACFG[master] & TRDC_DACFG_NCM_MASK));
    assert(NULL != domainAssignment);
    assert(domainAssignment->domainId <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NDID_MASK) >> TRDC_TRDC_HWCFG0_NDID_SHIFT));

    trdc_reg32_convert_t pid;
    pid._processor_domain_assignment                                         = *domainAssignment;
    TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT0[master].MDA_W_DFMT0[regNum] = pid._u32 | TRDC_MDA_W_DFMT0_VLD_MASK;
}

/*!
 * brief Sets the non-processor bus master domain assignment.
 *
 * This function sets the non-processor master domain assignment as valid.
 * One bus master might have multiple domain assignment registers. The parameter
 * \p assignIndex specifies which assignment register to set.
 *
 * Example: Set domain assignment for DMA0.
 * code
 * trdc_non_processor_domain_assignment_t nonProcessorAssignment;
 *
 * TRDC_GetDefaultNonProcessorDomainAssignment(&nonProcessorAssignment);
 * nonProcessorAssignment.domainId = 1;
 * nonProcessorAssignment.xxx      = xxx;
 *
 * TRDC_SetMasterDomainAssignment(TRDC, kTrdcMasterDma0, 0U, &nonProcessorAssignment);
 * endcode
 *
 * param base TRDC peripheral base address.
 * param master Which master to configure, refer to trdc_master_t in processor header file.
 * param domainAssignment Pointer to the assignment structure.
 */
void TRDC_SetNonProcessorDomainAssignment(TRDC_Type *base,
                                          uint8_t master,
                                          const trdc_non_processor_domain_assignment_t *domainAssignment)
{
    /* The master number should be less than the master count. */
    assert(master <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMSTR_MASK) >> TRDC_TRDC_HWCFG0_NMSTR_SHIFT));
    /* Make sure the master is a non-CPU/non-processor master */
    assert(0U != (TRDC_GENERAL_BASE(base)->DACFG[master] & TRDC_DACFG_NCM_MASK));
    assert(NULL != domainAssignment);
    assert(domainAssignment->domainId <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NDID_MASK) >> TRDC_TRDC_HWCFG0_NDID_SHIFT));

    trdc_reg32_convert_t pid;
    pid._non_processor_domain_assignment = *domainAssignment;

    TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT1[master].MDA_W_DFMT1[0] = pid._u32 | TRDC_MDA_W_DFMT1_VLD_MASK;
}

/*!
 * brief Sets the current Process identifier(PID) for processor core.
 *
 * Each processor has a corresponding process identifier (PID) which can be used to group tasks into different domains.
 * Secure privileged software saves and restores the PID as part of any context switch.
 * This data structure defines an array of 32-bit values, one per MDA module, that define the PID. Since this register
 * resource is only applicable to processor cores, the data structure is typically sparsely populated. The HWCFG[2-3]
 * registers provide a bitmap of the implemented PIDn registers. This data structure is indexed using the corresponding
 * MDA instance number. Depending on the operating clock domain of each DAC instance, there may be optional information
 * stored in the corresponding PIDm register to properly implement the LK2 = 2 functionality.
 *
 * param base TRDC peripheral base address.
 * param master Which processor master to configure, refer to trdc_master_t in processor header file.
 * param pidConfig Pointer to the configuration structure.
 */
void TRDC_SetPid(TRDC_Type *base, uint8_t master, const trdc_pid_config_t *pidConfig)
{
    assert(pidConfig != NULL);
    /* The master number should be less than the master count. */
    assert(master <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMSTR_MASK) >> TRDC_TRDC_HWCFG0_NMSTR_SHIFT));
    /* This master has to be a processor master. */
    assert((TRDC_GENERAL_BASE(base)->DACFG[master] & TRDC_DACFG_NCM_MASK) == 0U);

    trdc_reg32_convert_t pid;
    pid._pid_config                                = *pidConfig;
    TRDC_DOMAIN_ASSIGNMENT_BASE(base)->PID[master] = pid._u32;
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/*!
 * brief Gets the default IDAU(Implementation-Defined Attribution Unit) configuration.
 *
 * code
 * config->lockSecureVTOR    = false;
 * config->lockNonsecureVTOR = false;
 * config->lockSecureMPU     = false;
 * config->lockNonsecureMPU  = false;
 * config->lockSAU           = false;
 * endcode
 *
 * param domainAssignment Pointer to the configuration structure.
 */
void TRDC_GetDefaultIDAUConfig(trdc_idau_config_t *idauConfiguration)
{
    assert(NULL != idauConfiguration);

    /* Initializes the configure structure to zero. */
    (void)memset(idauConfiguration, 0, sizeof(*idauConfiguration));
}

/*!
 * brief Sets the IDAU(Implementation-Defined Attribution Unit) control configuration.
 *
 * Example: Lock the secure and non-secure MPU registers.
 *
 * code
 * trdc_idau_config_t idauConfiguration;
 *
 * TRDC_GetDefaultIDAUConfig(&idauConfiguration);
 *
 * idauConfiguration.lockSecureMPU = true;
 * idauConfiguration.lockNonsecureMPU      = true;
 * TRDC_SetIDAU(TRDC, &idauConfiguration);
 * endcode
 *
 * param base TRDC peripheral base address.
 * param domainAssignment Pointer to the configuration structure.
 */
void TRDC_SetIDAU(TRDC_Type *base, const trdc_idau_config_t *idauConfiguration)
{
    assert(NULL != idauConfiguration);

    trdc_reg32_convert_t pid;
    pid._idau_config = *idauConfiguration;

    TRDC_GENERAL_BASE(base)->TRDC_IDAU_CR = pid._u32 | TRDC_TRDC_IDAU_CR_VLD_MASK;
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_FLW) && FSL_FEATURE_TRDC_HAS_FLW
/*!
 * brief Gets the default FLW(Flsh Logical Window) configuration.
 *
 * code
 * config->blockCount    = false;
 * config->arrayBaseAddr = false;
 * config->lock     = false;
 * config->enable  = false;
 * endcode
 *
 * param flwConfiguration Pointer to the configuration structure.
 */
void TRDC_GetDefaultFlashLogicalWindowConfig(trdc_flw_config_t *flwConfiguration)
{
    assert(NULL != flwConfiguration);

    /* Initializes the configure structure to zero. */
    (void)memset(flwConfiguration, 0, sizeof(*flwConfiguration));

    flwConfiguration->enable = 0x1UL;
}

/*!
 * brief Sets the FLW function's configuration.
 *
 * code
 * trdc_flw_config_t flwConfiguration;
 *
 * TRDC_GetDefaultIDAUConfig(&flwConfiguration);
 *
 * flwConfiguration.blockCount = 32U;
 * flwConfiguration.arrayBaseAddr = 0xXXXXXXXX;
 * TRDC_SetIDAU(TRDC, &flwConfiguration);
 * endcode
 *
 * param base TRDC peripheral base address.
 * param flwConfiguration Pointer to the configuration structure.
 */
void TRDC_SetFlashLogicalWindow(TRDC_Type *base, const trdc_flw_config_t *flwConfiguration)
{
    assert(NULL != flwConfiguration);

    TRDC_FLW_BASE(base)->TRDC_FLW_ABASE = flwConfiguration->arrayBaseAddr;
    TRDC_FLW_BASE(base)->TRDC_FLW_BCNT  = flwConfiguration->blockCount;
    TRDC_FLW_BASE(base)->TRDC_FLW_CTL =
        TRDC_TRDC_FLW_CTL_V(flwConfiguration->enable) | TRDC_TRDC_FLW_CTL_LK(flwConfiguration->lock);
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR) && FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR
#if (((__CORTEX_M == 0U) && (defined(__ICCARM__))) || (defined(__XTENSA__)))
/*!
 * @brief Count the leading zeros.
 *
 * Count the leading zeros of an 32-bit data. This function is only defined
 * for CM0 and CM0+ for IAR, because other cortex series have the clz instruction,
 * KEIL and ARMGCC have toolchain build in function for this purpose.
 *
 * @param data The data to process.
 * @return Count of the leading zeros.
 */
static uint8_t TRDC_CountLeadingZeros(uint32_t data)
{
    uint8_t count = 0U;
    uint32_t mask = 0x80000000U;

    while ((data & mask) == 0U)
    {
        count++;
        mask >>= 1U;
    }

    return count;
}
#endif
#endif

/*!
 * brief Initializes the TRDC module.
 *
 * This function enables the TRDC clock.
 *
 * param base TRDC peripheral base address.
 */
void TRDC_Init(TRDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief De-initializes the TRDC module.
 *
 * This function disables the TRDC clock.
 *
 * param base TRDC peripheral base address.
 */
void TRDC_Deinit(TRDC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR) && FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR
/*!
 * brief Gets and clears the first domain error of the current domain.
 *
 * This function gets the first access violation information for the current domain
 * and clears the pending flag. There might be multiple access violations pending
 * for the current domain. This function only processes the first error.
 *
 * param base TRDC peripheral base address.
 * param error Pointer to the error information.
 * return If the access violation is captured, this function returns the kStatus_Success.
 *         The error information can be obtained from the parameter error. If no
 *         access violation is captured, this function returns the kStatus_NoData.
 */
status_t TRDC_GetAndClearFirstDomainError(TRDC_Type *base, trdc_domain_error_t *error)
{
    return TRDC_GetAndClearFirstSpecificDomainError(base, error, TRDC_GetCurrentMasterDomainId(base));
}

/*!
 * brief Gets and clears the first domain error of the specific domain.
 *
 * This function gets the first access violation information for the specific domain
 * and clears the pending flag. There might be multiple access violations pending
 * for the current domain. This function only processes the first error.
 *
 * param base TRDC peripheral base address.
 * param error Pointer to the error information.
 * param domainId The error of which domain to get and clear.
 * return If the access violation is captured, this function returns the kStatus_Success.
 *         The error information can be obtained from the parameter error. If no
 *         access violation is captured, this function returns the kStatus_NoData.
 */
status_t TRDC_GetAndClearFirstSpecificDomainError(TRDC_Type *base, trdc_domain_error_t *error, uint8_t domainId)
{
    assert(NULL != error);

    status_t status;
    uint8_t errorIndex;   /* The index of first domain error. */
    uint32_t errorBitMap; /* Domain error location bit map.   */
    uint32_t regW1;       /* To save TRDC_DERR_W1.            */

    /* Get the error bitmap. */
    errorBitMap = TRDC_DOMAIN_ERROR_BASE(base)->TRDC_DERRLOC[domainId];

    if (0U == errorBitMap) /* No error captured. */
    {
        status = kStatus_NoData;
    }
    else
    {
        /* Get the first error controller index. */
#if (((__CORTEX_M == 0U) && (defined(__ICCARM__))) || (defined(__XTENSA__)))
        errorIndex = 31U - TRDC_CountLeadingZeros(errorBitMap);
#else
        errorIndex = 31U - __CLZ(errorBitMap);
#endif

        /* Must write TRDC_FDID[TRDC_FDID] with the domain ID before reading the Domain Error registers. */
        TRDC_DOMAIN_ERROR_BASE(base)->TRDC_FDID = TRDC_TRDC_FDID_FDID(domainId);

        /* Initializes the error structure to zero. */
        (void)memset(error, 0, sizeof(*error));

        if (errorIndex > 15U)
        {
            /* Error in Memory Region Checker (MRC) */
            errorIndex -= 12U;
            error->controller = (trdc_controller_t)errorIndex;
            errorIndex -= 4U;

            /* Get the error information. */
            regW1          = TRDC_DOMAIN_ERROR_BASE(base)->MRC_DERR[errorIndex].W1;
            error->address = TRDC_DOMAIN_ERROR_BASE(base)->MRC_DERR[errorIndex].W0;
            /* Clear error pending. */
            TRDC_DOMAIN_ERROR_BASE(base)->MRC_DERR[errorIndex].W3 = TRDC_W3_RECR(0x01U);
        }
        else
        {
            /* Error in Memory Block Controller (MBC) */
            error->slaveMemoryIdx = errorIndex % 4U;
            errorIndex /= 4U;
            error->controller = (trdc_controller_t)errorIndex;

            /* Check if the MBC error index exceeds the module's max MBC index to avoid overrun access. */
            if (errorIndex >=
                ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMBC_MASK) >> TRDC_TRDC_HWCFG0_NMBC_SHIFT))
            {
                return kStatus_Fail;
            }

            error->controller = (trdc_controller_t)errorIndex;

            /* Get the error information. */
            regW1          = TRDC_DOMAIN_ERROR_BASE(base)->MBC_DERR[errorIndex].W1;
            error->address = TRDC_DOMAIN_ERROR_BASE(base)->MBC_DERR[errorIndex].W0;
            /* Clear error pending. */
            TRDC_DOMAIN_ERROR_BASE(base)->MBC_DERR[errorIndex].W3 = TRDC_W3_RECR(0x01U);
        }

        uint8_t tempVal   = 0U;
        error->domainId   = (uint8_t)((regW1 & TRDC_W1_EDID_MASK) >> TRDC_W1_EDID_MASK);
        tempVal           = (uint8_t)((regW1 & TRDC_W1_EATR_MASK) >> TRDC_W1_EATR_SHIFT);
        error->errorAttr  = (trdc_error_attr_t)tempVal;
        tempVal           = (uint8_t)((regW1 & TRDC_W1_ERW_MASK) >> TRDC_W1_ERW_SHIFT);
        error->errorType  = (trdc_error_type_t)tempVal;
        error->errorPort  = (uint8_t)((regW1 & TRDC_W1_EPORT_MASK) >> TRDC_W1_EPORT_SHIFT);
        tempVal           = (uint8_t)((regW1 & TRDC_W1_EST_MASK) >> TRDC_W1_EST_SHIFT);
        error->errorState = (trdc_error_state_t)tempVal;

        status = kStatus_Success;
    }

    return status;
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MRC) && FSL_FEATURE_TRDC_HAS_MRC
/*!
 * brief Sets the memory access configuration for one of the access control register of one MRC.
 *
 * Example: Enable the secure operations and lock the configuration for MRC0 region 1.
 *
 * code
 * trdc_memory_access_control_config_t config;
 *
 * config.securePrivX = true;
 * config.securePrivW = true;
 * config.securePrivR = true;
 * config.lock = true;
 * TRDC_SetMrcMemoryAccess(TRDC, &config, 0, 1);
 * endcode
 *
 * param base TRDC peripheral base address.
 * param config Pointer to the configuration structure.
 * param mrcIdx MRC index.
 * param regIdx Register number.
 */
void TRDC_MrcSetMemoryAccessConfig(TRDC_Type *base,
                                   const trdc_memory_access_control_config_t *config,
                                   uint8_t mrcIdx,
                                   uint8_t regIdx)
{
    assert(NULL != base);
    assert(NULL != config);

    trdc_reg32_convert_t pid;

    pid._memory_access_control                     = *config;
    TRDC_MRC_BASE(base, mrcIdx)->MRC_GLBAC[regIdx] = pid._u32;
}

/*!
 * brief Enables the update of the selected domians.
 *
 * After the domians' update are enabled, their regions' NSE bits can be set or clear.
 *
 * param base TRDC peripheral base address.
 * param mrcIdx MRC index.
 * param domianMask Bit mask of the domains to be enabled.
 * param enable True to enable, false to disable.
 */
void TRDC_MrcEnableDomainNseUpdate(TRDC_Type *base, uint8_t mrcIdx, uint16_t domianMask, bool enable)
{
    assert(NULL != base);

    if (enable)
    {
        TRDC_MRC_BASE(base, mrcIdx)->MRC_NSE_RGN_INDIRECT |= ((uint32_t)domianMask << 16U);
    }
    else
    {
        TRDC_MRC_BASE(base, mrcIdx)->MRC_NSE_RGN_INDIRECT &= ~((uint32_t)domianMask << 16U);
    }
}

/*!
 * brief Sets the NSE bits of the selected regions for domains.
 *
 * This function sets the NSE bits for the selected regions for the domains whose update are enabled.
 *
 * param base TRDC peripheral base address.
 * param mrcIdx MRC index.
 * param regionMask Bit mask of the regions whose NSE bits to set.
 */
void TRDC_MrcRegionNseSet(TRDC_Type *base, uint8_t mrcIdx, uint16_t regionMask)
{
    assert(NULL != base);

    TRDC_MRC_BASE(base, mrcIdx)->MRC_NSE_RGN_SET = ((uint32_t)regionMask);
}

/*!
 * brief Clears the NSE bits of the selected regions for domains.
 *
 * This function clears the NSE bits for the selected regions for the domains whose update are enabled.
 *
 * param base TRDC peripheral base address.
 * param mrcIdx MRC index.
 * param regionMask Bit mask of the regions whose NSE bits to clear.
 */
void TRDC_MrcRegionNseClear(TRDC_Type *base, uint8_t mrcIdx, uint16_t regionMask)
{
    assert(NULL != base);

    TRDC_MRC_BASE(base, mrcIdx)->MRC_NSE_RGN_CLR = ((uint32_t)regionMask);
}

/*!
 * brief Clears the NSE bits for all the regions of the selected domains.
 *
 * This function clears the NSE bits for all regions of selected domains whose update are enabled.
 *
 * param base TRDC peripheral base address.
 * param mrcIdx MRC index.
 * param domainMask Bit mask of the domians whose NSE bits to clear.
 */
void TRDC_MrcDomainNseClear(TRDC_Type *base, uint8_t mrcIdx, uint16_t domainMask)
{
    assert(NULL != base);

    uint8_t domainCount =
        (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NDID_MASK) >> TRDC_TRDC_HWCFG0_NDID_SHIFT);
    uint8_t maxDomainId = 0U;
    uint16_t tmpDomainMask = domainMask;

    while (tmpDomainMask != 0U)
    {
        tmpDomainMask >>= 1U;
        maxDomainId++;
    }

    /* Check whether the domain mask contains invalid domain. */
    if (maxDomainId > domainCount)
    {
        assert(false);
    }

    TRDC_MRC_BASE(base, mrcIdx)->MRC_NSE_RGN_CLR_ALL = ((uint32_t)domainMask << 16U);
}

/*!
 * brief Sets the configuration for one of the region descriptor per domain per MRC instnce.
 *
 * This function sets the configuration for one of the region descriptor, including the start
 * and end address of the region, memory access control policy and valid.
 *
 * param base TRDC peripheral base address.
 * param config Pointer to region descriptor configuration structure.
 */
void TRDC_MrcSetRegionDescriptorConfig(TRDC_Type *base, const trdc_mrc_region_descriptor_config_t *config)
{
    assert(NULL != base);

    uint32_t regAddr = (uint32_t) & (TRDC_MRC_BASE(base, config->mrcIdx)->MRC_DOM0_RGD_W[config->regionIdx][0]);

    regAddr += TRDC_MRC_DOMAIN_INCREMENT * config->domainIdx;

    /* Set configuration for word 0 */
    uint32_t data = TRDC_MRC_DOM0_RGD_W_MRACSEL(config->memoryAccessControlSelect) |
                    ((config->startAddr) & ~(TRDC_MRC_DOM0_RGD_W_MRACSEL_MASK));
    *(uint32_t *)regAddr = data;

    /* Set configuration for word 1 */
    regAddr += 4U;
    data = TRDC_MRC_DOM0_RGD_W_VLD(config->valid) | TRDC_MRC_DOM0_RGD_W_NSE(config->nseEnable) |
           ((config->endAddr) & ~(TRDC_MRC_DOM0_RGD_W_VLD_MASK | TRDC_MRC_DOM0_RGD_W_NSE_MASK));
    *(uint32_t *)regAddr = data;
}
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC
/*!
 * brief Sets the NSR update configuration for one of the MBC instance.
 *
 * After set the NSE configuration, the configured memory area can be updateby NSE set/clear.
 *
 * param base TRDC peripheral base address.
 * param config Pointer to NSE update configuration structure.
 * param mbcIdx MBC index.
 */
void TRDC_MbcSetNseUpdateConfig(TRDC_Type *base, const trdc_mbc_nse_update_config_t *config, uint8_t mbcIdx)
{
    assert(base != NULL);

    trdc_reg32_convert_t pid;

    pid._mbc_nse_update                            = *config;
    TRDC_MBC_BASE(base, mbcIdx)->MBC_NSE_BLK_INDEX = pid._u32;
}

/*!
 * brief Sets the NSE bits of the selected configuration words according to NSE update configuration.
 *
 * This function sets the NSE bits of the word for the configured regio, memory.
 *
 * param base TRDC peripheral base address.
 * param mbcIdx MBC index.
 * param bitMask Mask of the bits whose NSE bits to set.
 */
void TRDC_MbcWordNseSet(TRDC_Type *base, uint8_t mbcIdx, uint32_t bitMask)
{
    assert(NULL != base);

    TRDC_MBC_BASE(base, mbcIdx)->MBC_NSE_BLK_SET = ((uint32_t)bitMask);
}

/*!
 * brief Clears the NSE bits of the selected configuration words according to NSE update configuration.
 *
 * This function sets the NSE bits of the word for the configured regio, memory.
 *
 * param base TRDC peripheral base address.
 * param mbcIdx MBC index.
 * param bitMask Mask of the bits whose NSE bits to clear.
 */
void TRDC_MbcWordNseClear(TRDC_Type *base, uint8_t mbcIdx, uint32_t bitMask)
{
    assert(NULL != base);

    TRDC_MBC_BASE(base, mbcIdx)->MBC_NSE_BLK_CLR = ((uint32_t)bitMask);
}

/*!
 * brief Clears all configuration words' NSE bits of the selected domain and memory.
 *
 * param base TRDC peripheral base address.
 * param mbcIdx MBC index.
 * param domainMask Mask of the domains whose NSE bits to clear, 0b110 means clear domain 1&2.
 * param slaveMask Mask of the slaves whose NSE bits to clear, 0x11 means clear all slave 0&1's NSE bits.
 */
void TRDC_MbcNseClearAll(TRDC_Type *base, uint8_t mbcIdx, uint16_t domainMask, uint8_t slave)
{
    assert(NULL != base);

#if defined(FSL_FEATURE_TRDC_DOMAIN_COUNT) && FSL_FEATURE_TRDC_DOMAIN_COUNT
    uint8_t dmainCount = FSL_FEATURE_TRDC_DOMAIN_COUNT;
#else
    uint8_t dmainCount =
        (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NDID_MASK) >> TRDC_TRDC_HWCFG0_NDID_SHIFT);
#endif
    uint8_t maxDomainId = 0U;
    uint16_t tmpDomainMask = domainMask;

    while (tmpDomainMask != 0U)
    {
        tmpDomainMask >>= 1U;
        maxDomainId++;
    }

    if (maxDomainId > dmainCount)
    {
        assert(false);
    }

    TRDC_MBC_BASE(base, mbcIdx)->MBC_NSE_BLK_CLR_ALL =
        TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL(domainMask) | TRDC_MBC_NSE_BLK_CLR_ALL_MEMSEL(slave);
}

/*!
 * brief Sets the memory access configuration for one of the region descriptor of one MBC.
 *
 * Example: Enable the secure operations and lock the configuration for MRC0 region 1.
 *
 * code
 * trdc_memory_access_control_config_t config;
 *
 * config.securePrivX = true;
 * config.securePrivW = true;
 * config.securePrivR = true;
 * config.lock = true;
 * TRDC_SetMbcMemoryAccess(TRDC, &config, 0, 1);
 * endcode
 *
 * param base TRDC peripheral base address.
 * param config Pointer to the configuration structure.
 * param mbcIdx MBC index.
 * param rgdIdx Region descriptor number.
 */
void TRDC_MbcSetMemoryAccessConfig(TRDC_Type *base,
                                   const trdc_memory_access_control_config_t *config,
                                   uint8_t mbcIdx,
                                   uint8_t rgdIdx)
{
    assert(NULL != base);
    assert(NULL != config);

    trdc_reg32_convert_t pid;

    pid._memory_access_control                          = *config;
    TRDC_MBC_BASE(base, mbcIdx)->MBC_MEMN_GLBAC[rgdIdx] = pid._u32;
}

/*!
 * brief Sets the configuration for one of the memory block per domain per MBC instnce.
 *
 * This function sets the configuration for one of the memory block, including the memory access
 * control policy and nse enable.
 *
 * param base TRDC peripheral base address.
 * param config Pointer to memory block configuration structure.
 */
void TRDC_MbcSetMemoryBlockConfig(TRDC_Type *base, const trdc_mbc_memory_block_config_t *config)
{
    assert(NULL != base);

    uint32_t shift      = 4UL * (config->memoryBlockIdx % 8UL);
    uint32_t regAddr    = (uint32_t) & (TRDC_MBC_BASE(base, config->mbcIdx)->MBC_DOM0_MEM0_BLK_CFG_W[0]);
    uint32_t configWord = 0U;
    trdc_reg32_convert_t pid;

    pid._mbc_memory_blk = *config;
    configWord          = (pid._u32 & 0xFU) << shift;

    regAddr += (TRDC_MBC_DOMAIN_INCREMENT * config->domainIdx + TRDC_MBC_SLAVE_INCREMENT(config->slaveMemoryIdx)) +
               ((uint32_t)config->memoryBlockIdx / 8U) * sizeof(uint32_t);
    configWord           = configWord | (*(uint32_t *)regAddr & ~(0xFUL << shift));
    *(uint32_t *)regAddr = configWord;
}
#endif
