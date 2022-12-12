/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RDC_H_
#define _FSL_RDC_H_

#include "fsl_common.h"

/*!
 * @addtogroup rdc
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/
#define FSL_RDC_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))

#define RDC_ACCESS_POLICY(domainID, policy) (uint16_t)((uint16_t)(policy) << ((domainID)*2U))

/*!
 * @brief RDC hardware configuration.
 */
typedef struct _rdc_hardware_config
{
    uint32_t domainNumber : 4; /*!< Number of domains.        */
    uint32_t masterNumber : 8; /*!< Number of bus masters.    */
    uint32_t periphNumber : 8; /*!< Number of peripherals.    */
    uint32_t memNumber : 8;    /*!< Number of memory regions. */
    uint32_t : 4;
} rdc_hardware_config_t;

/*!
 * @brief RDC interrupts
 */
enum _rdc_interrupts
{
    kRDC_RestoreCompleteInterrupt = RDC_INTCTRL_RCI_EN_MASK,
    /*!< Interrupt generated when the RDC has completed restoring state to a recently re-powered memory regions. */
};

/*!
 * @brief RDC status
 */
enum _rdc_flags
{
    kRDC_PowerDownDomainOn = RDC_STAT_PDS_MASK, /*!< Power down domain is ON. */
};

/*!
 * @brief Master domain assignment.
 */
typedef struct _rdc_domain_assignment
{
    uint32_t domainId : 2U; /*!< Domain ID.                  */
    uint32_t : 29U;         /*!< Reserved.                   */
    uint32_t lock : 1U;     /*!< Lock the domain assignment. */
} rdc_domain_assignment_t;

/*!
 * @brief Access permission policy.
 */
enum _rdc_access_policy
{
    kRDC_NoAccess  = 0, /*!< Could not read or write. */
    kRDC_WriteOnly = 1, /*!< Write only. */
    kRDC_ReadOnly  = 2, /*!< Read only. */
    kRDC_ReadWrite = 3, /*!< Read and write. */
};

/*!
 * @brief Peripheral domain access permission configuration.
 */
typedef struct _rdc_periph_access_config
{
    rdc_periph_t periph; /*!< Peripheral name.                 */
    bool lock;           /*!< Lock the permission until reset. */
    bool enableSema;     /*!< Enable semaphore or not, when enabled, master should
                              call @ref RDC_SEMA42_Lock to lock the semaphore gate
                              accordingly before access the peripheral. */
    uint16_t policy;     /*!< Access policy.                   */
} rdc_periph_access_config_t;

/*!
 * @brief Memory region domain access control configuration.
 *
 * Note that when setting the @ref baseAddress and @ref endAddress,
 * should be aligned to the region resolution, see rdc_mem_t
 * definitions.
 */
typedef struct _rdc_mem_access_config
{
    rdc_mem_t mem; /*!< Memory region descriptor name. */

    bool lock;            /*!< Lock the configuration. */
    uint64_t baseAddress; /*!< Start address of the memory region. */
    uint64_t endAddress;  /*!< End address of the memory region.   */
    uint16_t policy;      /*!< Access policy.                      */
} rdc_mem_access_config_t;

/*!
 * @brief Memory region access violation status.
 */
typedef struct _rdc_mem_status
{
    bool hasViolation; /*!< Violating happens or not. */
    uint8_t domainID;  /*!< Violating Domain ID. */
    uint64_t address;  /*!< Violating Address. */
} rdc_mem_status_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the RDC module.
 *
 * This function enables the RDC clock.
 *
 * @param base RDC peripheral base address.
 */
void RDC_Init(RDC_Type *base);

/*!
 * @brief De-initializes the RDC module.
 *
 * This function disables the RDC clock.
 *
 * @param base RDC peripheral base address.
 */
void RDC_Deinit(RDC_Type *base);

/*!
 * @brief Gets the RDC hardware configuration.
 *
 * This function gets the RDC hardware configurations, including number of bus
 * masters, number of domains, number of memory regions and number of peripherals.
 *
 * @param base RDC peripheral base address.
 * @param config Pointer to the structure to get the configuration.
 */
void RDC_GetHardwareConfig(RDC_Type *base, rdc_hardware_config_t *config);

/*!
 * @brief Enable interrupts.
 *
 * @param base RDC peripheral base address.
 * @param mask Interrupts to enable, it is OR'ed value of enum @ref _rdc_interrupts.
 */
static inline void RDC_EnableInterrupts(RDC_Type *base, uint32_t mask)
{
    base->INTCTRL |= mask;
}

/*!
 * @brief Disable interrupts.
 *
 * @param base RDC peripheral base address.
 * @param mask Interrupts to disable, it is OR'ed value of enum @ref _rdc_interrupts.
 */
static inline void RDC_DisableInterrupts(RDC_Type *base, uint32_t mask)
{
    base->INTCTRL &= ~mask;
}

/*!
 * @brief Get the interrupt pending status.
 *
 * @param base RDC peripheral base address.
 * @return Interrupts pending status, it is OR'ed value of enum @ref _rdc_interrupts.
 */
static inline uint32_t RDC_GetInterruptStatus(RDC_Type *base)
{
    return base->INTSTAT;
}

/*!
 * @brief Clear interrupt pending status.
 *
 * @param base RDC peripheral base address.
 * @param mask Status to clear, it is OR'ed value of enum @ref _rdc_interrupts.
 */
static inline void RDC_ClearInterruptStatus(RDC_Type *base, uint32_t mask)
{
    base->INTSTAT = mask;
}

/*!
 * @brief Get RDC status.
 *
 * @param base RDC peripheral base address.
 * @return mask RDC status, it is OR'ed value of enum @ref _rdc_flags.
 */
static inline uint32_t RDC_GetStatus(RDC_Type *base)
{
    return base->STAT;
}

/*!
 * @brief Clear RDC status.
 *
 * @param base RDC peripheral base address.
 * @param mask RDC status to clear, it is OR'ed value of enum @ref _rdc_flags.
 */
static inline void RDC_ClearStatus(RDC_Type *base, uint32_t mask)
{
    base->STAT = mask;
}

/*!
 * @brief Set master domain assignment
 *
 * @param base RDC peripheral base address.
 * @param master Which master to set.
 * @param domainAssignment Pointer to the assignment.
 */
void RDC_SetMasterDomainAssignment(RDC_Type *base,
                                   rdc_master_t master,
                                   const rdc_domain_assignment_t *domainAssignment);

/*!
 * @brief Get default master domain assignment
 *
 * The default configuration is:
 * @code
   assignment->domainId = 0U;
   assignment->lock = 0U;
   @endcode
 *
 * @param domainAssignment Pointer to the assignment.
 */
void RDC_GetDefaultMasterDomainAssignment(rdc_domain_assignment_t *domainAssignment);

/*!
 * @brief Lock master domain assignment
 *
 * Once locked, it could not be unlocked until next reset.
 *
 * @param base RDC peripheral base address.
 * @param master Which master to lock.
 */
static inline void RDC_LockMasterDomainAssignment(RDC_Type *base, rdc_master_t master)
{
    assert((uint32_t)master < RDC_MDA_COUNT);

    base->MDA[master] |= RDC_MDA_LCK_MASK;
    __DSB();
}

/*!
 * @brief Set peripheral access policy.
 *
 * @param base RDC peripheral base address.
 * @param config Pointer to the policy configuration.
 */
void RDC_SetPeriphAccessConfig(RDC_Type *base, const rdc_periph_access_config_t *config);

/*!
 * @brief Get default peripheral access policy.
 *
 * The default configuration is:
 * @code
    config->lock = false;
    config->enableSema = false;
    config->policy = RDC_ACCESS_POLICY(0, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(1, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(2, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(3, kRDC_ReadWrite);
   @endcode
 *
 * @param config Pointer to the policy configuration.
 */
void RDC_GetDefaultPeriphAccessConfig(rdc_periph_access_config_t *config);

/*!
 * @brief Lock peripheral access policy configuration.
 *
 * Once locked, it could not be unlocked until reset.
 *
 * @param base RDC peripheral base address.
 * @param periph Which peripheral to lock.
 */
static inline void RDC_LockPeriphAccessConfig(RDC_Type *base, rdc_periph_t periph)
{
    assert((uint32_t)periph < RDC_PDAP_COUNT);

    base->PDAP[periph] |= RDC_PDAP_LCK_MASK;
    __DSB();
}

/*!
 * @brief Get the peripheral access policy for specific domain.
 *
 * @param base RDC peripheral base address.
 * @param periph Which peripheral to get.
 * @param domainId Get policy for which domain.
 * @return Access policy, see @ref _rdc_access_policy.
 */
static inline uint8_t RDC_GetPeriphAccessPolicy(RDC_Type *base, rdc_periph_t periph, uint8_t domainId)
{
    assert((uint32_t)periph < RDC_PDAP_COUNT);

    return (uint8_t)((base->PDAP[periph] >> (domainId * 2U)) & 0x03U);
}

/*!
 * @brief Set memory region access policy.
 *
 * Note that when setting the baseAddress and endAddress in @p config,
 * should be aligned to the region resolution, see rdc_mem_t
 * definitions.
 *
 * @param base RDC peripheral base address.
 * @param config Pointer to the policy configuration.
 */
void RDC_SetMemAccessConfig(RDC_Type *base, const rdc_mem_access_config_t *config);

/*!
 * @brief Get default memory region access policy.
 *
 * The default configuration is:
 * @code
    config->lock = false;
    config->baseAddress = 0;
    config->endAddress = 0;
    config->policy = RDC_ACCESS_POLICY(0, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(1, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(2, kRDC_ReadWrite) |
                     RDC_ACCESS_POLICY(3, kRDC_ReadWrite);
   @endcode
 *
 * @param config Pointer to the policy configuration.
 */
void RDC_GetDefaultMemAccessConfig(rdc_mem_access_config_t *config);

/*!
 * @brief Lock memory access policy configuration.
 *
 * Once locked, it could not be unlocked until reset. After locked, you can
 * only call @ref RDC_SetMemAccessValid to enable the configuration, but can not
 * disable it or change other settings.
 *
 * @param base RDC peripheral base address.
 * @param mem Which memory region to lock.
 */
static inline void RDC_LockMemAccessConfig(RDC_Type *base, rdc_mem_t mem)
{
    assert((uint32_t)mem < RDC_MRC_COUNT);

    base->MR[mem].MRC |= RDC_MRC_LCK_MASK;
    __DSB();
}

/*!
 * @brief Enable or disable memory access policy configuration.
 *
 * @param base RDC peripheral base address.
 * @param mem Which memory region to operate.
 * @param valid Pass in true to valid, false to invalid.
 */
static inline void RDC_SetMemAccessValid(RDC_Type *base, rdc_mem_t mem, bool valid)
{
    assert((uint32_t)mem < RDC_MRC_COUNT);

    if (valid)
    {
        base->MR[mem].MRC |= RDC_MRC_ENA_MASK;
    }
    else
    {
        base->MR[mem].MRC &= ~RDC_MRC_ENA_MASK;
    }
    __DSB();
}

/*!
 * @brief Get the memory region violation status.
 *
 * The first access violation is captured. Subsequent violations are ignored
 * until the status register is cleared. Contents are cleared upon reading the
 * register. Clearing of contents occurs only when the status is read by the
 * memory region's associated domain ID(s).
 *
 * @param base RDC peripheral base address.
 * @param mem Which memory region to get.
 * @param status The returned status.
 */
void RDC_GetMemViolationStatus(RDC_Type *base, rdc_mem_t mem, rdc_mem_status_t *status);

/*!
 * @brief Clear the memory region violation flag.
 *
 * @param base RDC peripheral base address.
 * @param mem Which memory region to clear.
 */
static inline void RDC_ClearMemViolationFlag(RDC_Type *base, rdc_mem_t mem)
{
    assert((uint32_t)mem < RDC_MRC_COUNT);

    base->MR[mem].MRVS = RDC_MRVS_AD_MASK;
}

/*!
 * @brief Get the memory region access policy for specific domain.
 *
 * @param base RDC peripheral base address.
 * @param mem Which memory region to get.
 * @param domainId Get policy for which domain.
 * @return Access policy, see @ref _rdc_access_policy.
 */
static inline uint8_t RDC_GetMemAccessPolicy(RDC_Type *base, rdc_mem_t mem, uint8_t domainId)
{
    assert((uint32_t)mem < RDC_MRC_COUNT);

    return (uint8_t)((base->MR[mem].MRC >> (domainId * 2U)) & 0x03U);
}

/*!
 * @brief Gets the domain ID of the current bus master.
 *
 * This function returns the domain ID of the current bus master.
 *
 * @param base RDC peripheral base address.
 * @return Domain ID of current bus master.
 */
static inline uint8_t RDC_GetCurrentMasterDomainId(RDC_Type *base)
{
    return (uint8_t)((base->STAT & RDC_STAT_DID_MASK) >> RDC_STAT_DID_SHIFT);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* _FSL_RDC_H_ */
