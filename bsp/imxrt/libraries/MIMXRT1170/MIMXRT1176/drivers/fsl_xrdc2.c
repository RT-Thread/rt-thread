/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_xrdc2.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xrdc2"
#endif

/* Definitions for access policy. */
#define XRDC2_DXACP_WIDTH (3U)
#define XRDC2_DXACP_MASK  ((1UL << XRDC2_DXACP_WIDTH) - 1U)

#define XRDC2_DXACP_0_7(domainId, dxacp)  ((uint32_t)(dxacp) << (XRDC2_DXACP_WIDTH * (uint32_t)(domainId)))
#define XRDC2_DXACP_8_15(domainId, dxacp) ((uint32_t)(dxacp) << (XRDC2_DXACP_WIDTH * ((uint32_t)(domainId)-8U)))

#define XRDC2_DXACP_0_7_MASK(domainId)  XRDC2_DXACP_0_7(domainId, XRDC2_DXACP_MASK)
#define XRDC2_DXACP_8_15_MASK(domainId) XRDC2_DXACP_8_15(domainId, XRDC2_DXACP_MASK)

/* Memory region alignment. */
#define XRDC2_MRGD_ADDR_ALIGN_MASK (0x00000FFFU)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void XRDC2_MakeDXACP(const xrdc2_access_policy_t policy[FSL_FEATURE_XRDC2_DOMAIN_COUNT],
                            uint32_t *w0,
                            uint32_t *w1);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static void XRDC2_MakeDXACP(const xrdc2_access_policy_t policy[FSL_FEATURE_XRDC2_DOMAIN_COUNT],
                            uint32_t *w0,
                            uint32_t *w1)
{
    uint32_t domain = (uint32_t)FSL_FEATURE_XRDC2_DOMAIN_COUNT;

    *w0 = 0U;
    *w1 = 0U;

#if (FSL_FEATURE_XRDC2_DOMAIN_COUNT > 8)
    while (domain > 8U)
    {
        domain--;
        *w0 <<= XRDC2_DXACP_WIDTH;
        *w0 |= (uint32_t)policy[domain - 8U];
    }
#endif

    while (domain > 0U)
    {
        domain--;
        *w1 <<= XRDC2_DXACP_WIDTH;
        *w1 |= (uint32_t)policy[domain];
    }
}

/*!
 * brief Initializes the XRDC2 module.
 *
 * This function enables the XRDC2 clock.
 *
 * param base XRDC2 peripheral base address.
 */
void XRDC2_Init(XRDC2_Type *base)
{
}

/*!
 * brief De-initializes the XRDC2 module.
 *
 * This function disables the XRDC2 clock.
 *
 * param base XRDC2 peripheral base address.
 */
void XRDC2_Deinit(XRDC2_Type *base)
{
}

/*!
 * brief Sets the XRDC2 global valid.
 *
 * This function sets the XRDC2 global valid or invalid. When the XRDC2 is global
 * invalid, all accesses from all bus masters to all slaves are allowed.
 *
 * param base XRDC2 peripheral base address.
 * param valid True to valid XRDC2.
 */
void XRDC2_SetGlobalValid(XRDC2_Type *base, bool valid)
{
    uint32_t mcr = base->MCR & ~(XRDC2_MCR_GVLDM_MASK | XRDC2_MCR_GVLDC_MASK);

    if (valid)
    {
        mcr |= XRDC2_MCR_GVLDM_MASK;
        base->MCR = mcr;

        /* Two dummy read to ensure the configuration takes effect. */
        (void)base->MCR;
        (void)base->MCR;

        mcr |= XRDC2_MCR_GVLDC_MASK;
        base->MCR = mcr;
    }
    else
    {
        base->MCR = mcr;
    }
}

/*!
 * brief Gets the default master domain assignment.
 *
 * This function sets the assignment as follows:
 *
 * code
 *  config->lock = false;
 *  config->privilegeAttr = kXRDC2_MasterPrivilege;
 *  config->secureAttr = kXRDC2_MasterSecure;
 *  config->domainId = 0U;
 *  config->mask = 0U;
 *  config->match = 0U;
 * endcode
 *
 * param assignment Pointer to the assignment structure.
 */
void XRDC2_GetDefaultMasterDomainAssignment(xrdc2_master_domain_assignment_t *assignment)
{
    assert(NULL != assignment);

    assignment->lock          = false;
    assignment->privilegeAttr = kXRDC2_MasterPrivilege;
    assignment->secureAttr    = kXRDC2_MasterSecure;
    assignment->domainId      = 0U;
    assignment->mask          = 0U;
    assignment->match         = 0U;
}

/*!
 * brief Sets the processor bus master domain assignment.
 *
 * param base XRDC2 peripheral base address.
 * param master Which master to configure.
 * param assignIndex Which assignment register to set.
 * param assignment Pointer to the assignment structure.
 */
void XRDC2_SetMasterDomainAssignment(XRDC2_Type *base,
                                     xrdc2_master_t master,
                                     uint8_t assignIndex,
                                     const xrdc2_master_domain_assignment_t *assignment)
{
    assert(NULL != assignment);
    uint32_t w0;
    uint32_t w1;

    w0 = (((uint32_t)assignment->mask << XRDC2_MDAC_MDA_W0_MASK_SHIFT) |
          ((uint32_t)assignment->match << XRDC2_MDAC_MDA_W0_MATCH_SHIFT));

    w1 = ((uint32_t)assignment->domainId << XRDC2_MDAC_MDA_W1_DID_SHIFT) |
         (XRDC2_MDAC_MDA_W1_PA(assignment->privilegeAttr)) | (XRDC2_MDAC_MDA_W1_SA(assignment->secureAttr)) |
         XRDC2_MDAC_MDA_W1_VLD_MASK;

    if (assignment->lock)
    {
        w1 |= XRDC2_MDAC_MDA_W1_DL_MASK;
    }

    base->MDACI_MDAJ[master][assignIndex].MDAC_MDA_W0 = w0;
    base->MDACI_MDAJ[master][assignIndex].MDAC_MDA_W1 = w1;
}

/*!
 * brief Gets the default memory slot access configuration.
 *
 * This function sets the assignment as follows:
 *
 * code
 *  config->lockMode = kXRDC2_AccessConfigLockDisabled;
 *  config->policy[0] = kXRDC2_AccessPolicyNone;
 *  config->policy[1] = kXRDC2_AccessPolicyNone;
 *  ...
 * endcode
 *
 * param config Pointer to the configuration.
 */
void XRDC2_GetMemSlotAccessDefaultConfig(xrdc2_mem_slot_access_config_t *config)
{
    assert(NULL != config);

    uint8_t domain;

    config->lockMode = kXRDC2_AccessConfigLockDisabled;

    for (domain = 0; domain < (uint32_t)FSL_FEATURE_XRDC2_DOMAIN_COUNT; domain++)
    {
        config->policy[domain] = kXRDC2_AccessPolicyNone;
    }
}

/*!
 * brief Sets the memory slot access policy.
 *
 * param base XRDC2 peripheral base address.
 * param config Pointer to the access policy configuration structure.
 */
void XRDC2_SetMemSlotAccessConfig(XRDC2_Type *base,
                                  xrdc2_mem_slot_t memSlot,
                                  const xrdc2_mem_slot_access_config_t *config)
{
    assert(NULL != config);

    uint32_t w0 = 0;
    uint32_t w1 = 0;

    XRDC2_MakeDXACP(config->policy, &w0, &w1);

    w1 |= XRDC2_MSC_MSAC_W1_DL2(config->lockMode);
    w1 |= XRDC2_MSC_MSAC_W1_VLD_MASK;

    base->MSCI_MSAC_WK[(uint8_t)memSlot].MSC_MSAC_W0 = w0;
    base->MSCI_MSAC_WK[(uint8_t)memSlot].MSC_MSAC_W1 = w1;
}

/*!
 * brief Sets the memory slot descriptor as valid or invalid.
 *
 * param base XRDC2 peripheral base address.
 * param memSlot Which memory slot descriptor to set.
 * param valid True to set valid, false to set invalid.
 */
void XRDC2_SetMemSlotAccessValid(XRDC2_Type *base, xrdc2_mem_slot_t memSlot, bool valid)
{
    uint32_t reg = base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 & ~XRDC2_EAL_MASK;

    if (valid)
    {
        base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = (reg | XRDC2_MSC_MSAC_W1_VLD_MASK);
    }
    else
    {
        base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = (reg & ~XRDC2_MSC_MSAC_W1_VLD_MASK);
    }
}

/*!
 * brief Sets the memory slot descriptor lock mode.
 *
 * param base XRDC2 peripheral base address.
 * param memSlot Which memory slot descriptor to set.
 * param lockMode The lock mode to set.
 */
void XRDC2_SetMemSlotAccessLockMode(XRDC2_Type *base, xrdc2_mem_slot_t memSlot, xrdc2_access_config_lock_t lockMode)
{
    uint32_t reg = base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 & ~(XRDC2_EAL_MASK | XRDC2_MRC_MRGD_W6_DL2_MASK);

    base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = (reg | XRDC2_MRC_MRGD_W6_DL2(lockMode));
}

/*!
 * brief Sets the memory slot access policy for specific domain.
 *
 * param base XRDC2 peripheral base address.
 * param memSlot The memory slot to operate.
 * param domainId The ID of the domain whose policy will be changed.
 * param policy The access policy to set.
 */
void XRDC2_SetMemSlotDomainAccessPolicy(XRDC2_Type *base,
                                        xrdc2_mem_slot_t memSlot,
                                        uint8_t domainId,
                                        xrdc2_access_policy_t policy)
{
    uint32_t reg;

    if (domainId < 8U)
    {
        reg = base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W0 & ~XRDC2_DXACP_0_7_MASK(domainId);
        reg |= XRDC2_DXACP_0_7(domainId, policy);
        base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W0 = reg;
    }
    else
    {
        reg = base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 & ~XRDC2_DXACP_8_15_MASK(domainId);
        reg |= XRDC2_DXACP_8_15(domainId, policy);
        reg &= ~XRDC2_EAL_MASK;
        base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = reg;
    }
}

/*!
 * brief Enable or disable the memory slot exclusive access lock.
 *
 * The lock must be enabled first before use. Once disabled, it could not be
 * enabled until reset.
 *
 * param base XRDC2 peripheral base address.
 * param memSlot The memory slot to operate.
 * param enable True to enable, false to disable.
 */
void XRDC2_EnableMemSlotExclAccessLock(XRDC2_Type *base, xrdc2_mem_slot_t memSlot, bool enable)
{
    if (enable)
    {
        base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = XRDC2_EAL_UNLOCKED;
    }
    else
    {
        base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = XRDC2_EAL_DISABLE_UNTIL_RESET;
    }
}

/*!
 * @brief Get current memory slot exclusive access lock owner.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 * @return The domain ID of the lock owner.
 */
uint8_t XRDC2_GetMemSlotExclAccessLockDomainOwner(XRDC2_Type *base, xrdc2_mem_slot_t memSlot)
{
    return (uint8_t)((base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W0 & XRDC2_MSC_MSAC_W0_EALO_MASK) >>
                     XRDC2_MSC_MSAC_W0_EALO_SHIFT);
}

/*!
 * brief Try to lock the memory slot exclusive access.
 *
 * param base XRDC2 peripheral base address.
 * param memSlot The memory slot to operate.
 * retval kStatus_Fail Failed to lock.
 * retval kStatus_Success Locked succussfully.
 */
status_t XRDC2_TryLockMemSlotExclAccess(XRDC2_Type *base, xrdc2_mem_slot_t memSlot)
{
    status_t status;
    uint8_t curDomainID;
    volatile uint32_t *lockReg = &(base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1);

    curDomainID = XRDC2_GetCurrentMasterDomainId(base);

    *lockReg = XRDC2_EAL_LOCKED;

    if (curDomainID != XRDC2_GetMemSlotExclAccessLockDomainOwner(base, memSlot))
    {
        status = kStatus_Fail;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Lock the memory slot exclusive access using blocking method.
 *
 * param base XRDC2 peripheral base address.
 * param memSlot The memory slot to operate.
 *
 * note This function must be called when the lock is not disabled.
 */
void XRDC2_LockMemSlotExclAccess(XRDC2_Type *base, xrdc2_mem_slot_t memSlot)
{
    uint8_t curDomainID;
    volatile uint32_t *lockReg = &(base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1);

    curDomainID = XRDC2_GetCurrentMasterDomainId(base);

    while (true)
    {
        *lockReg = XRDC2_EAL_LOCKED;

        /* Locked and owner is current domain. */
        if (curDomainID == XRDC2_GetMemSlotExclAccessLockDomainOwner(base, memSlot))
        {
            break;
        }
    }

    return;
}

/*!
 * brief Gets the default memory access configuration.
 *
 * This function sets the assignment as follows:
 *
 * code
 *  config->startAddr = 0U;
 *  config->endAddr = 0xFFFFFFFFU;
 *  config->lockMode = kXRDC2_AccessConfigLockDisabled;
 *  config->policy[0] = kXRDC2_AccessPolicyNone;
 *  config->policy[1] = kXRDC2_AccessPolicyNone;
 *  ...
 * endcode
 *
 * param config Pointer to the configuration.
 */
void XRDC2_GetMemAccessDefaultConfig(xrdc2_mem_access_config_t *config)
{
    assert(NULL != config);

    uint8_t domain;

    config->startAddr = 0U;
    config->endAddr   = 0xFFFFFFFFU;
    config->lockMode  = kXRDC2_AccessConfigLockDisabled;

    for (domain = 0; domain < (uint32_t)FSL_FEATURE_XRDC2_DOMAIN_COUNT; domain++)
    {
        config->policy[domain] = kXRDC2_AccessPolicyNone;
    }
}

/*!
 * brief Sets the memory region access policy.
 *
 * param base XRDC2 peripheral base address.
 * param config Pointer to the access policy configuration structure.
 */
void XRDC2_SetMemAccessConfig(XRDC2_Type *base, xrdc2_mem_t mem, const xrdc2_mem_access_config_t *config)
{
    assert(NULL != config);
    /* Check the memory region alignment. */
    assert((config->startAddr & XRDC2_MRGD_ADDR_ALIGN_MASK) == 0U);
    assert(((config->endAddr + 1U) & XRDC2_MRGD_ADDR_ALIGN_MASK) == 0U);

    uint32_t w5 = 0;
    uint32_t w6 = 0;

    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);

    XRDC2_MakeDXACP(config->policy, &w5, &w6);

    w6 |= XRDC2_MRC_MRGD_W6_DL2(config->lockMode);
    w6 |= XRDC2_MRC_MRGD_W6_VLD_MASK;

    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W0 = config->startAddr;
    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W1 = 0U;
    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W2 = config->endAddr;
    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W3 = 0U;
    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W5 = w5;
    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = w6;
}

/*!
 * brief Sets the memory region descriptor as valid or invalid.
 *
 * param base XRDC2 peripheral base address.
 * param mem Which memory region descriptor to set.
 * param valid True to set valid, false to set invalid.
 */
void XRDC2_SetMemAccessValid(XRDC2_Type *base, xrdc2_mem_t mem, bool valid)
{
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);
    uint32_t reg  = base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 & ~XRDC2_EAL_MASK;

    if (valid)
    {
        base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = (reg | XRDC2_MRC_MRGD_W6_VLD_MASK);
    }
    else
    {
        base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = (reg & ~XRDC2_MRC_MRGD_W6_VLD_MASK);
    }
}

/*!
 * brief Sets the memory descriptor lock mode.
 *
 * param base XRDC2 peripheral base address.
 * param mem Which memory descriptor to set.
 * param lockMode The lock mode to set.
 */
void XRDC2_SetMemAccessLockMode(XRDC2_Type *base, xrdc2_mem_t mem, xrdc2_access_config_lock_t lockMode)
{
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);
    uint32_t reg  = base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 & ~(XRDC2_EAL_MASK | XRDC2_MRC_MRGD_W6_DL2_MASK);

    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = (reg | XRDC2_MRC_MRGD_W6_DL2(lockMode));
}

/*!
 * brief Sets the memory region access policy for specific domain.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 * param domainId The ID of the domain whose policy will be changed.
 * param policy The access policy to set.
 */
void XRDC2_SetMemDomainAccessPolicy(XRDC2_Type *base, xrdc2_mem_t mem, uint8_t domainId, xrdc2_access_policy_t policy)
{
    uint32_t reg;
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);

    if (domainId < 8U)
    {
        reg = base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W5 & ~XRDC2_DXACP_0_7_MASK(domainId);
        reg |= XRDC2_DXACP_0_7(domainId, policy);
        base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W5 = reg;
    }
    else
    {
        reg = base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 & ~XRDC2_DXACP_8_15_MASK(domainId);
        reg |= XRDC2_DXACP_8_15(domainId, policy);
        reg &= ~XRDC2_EAL_MASK;
        base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = reg;
    }
}

/*!
 * brief Disable the memory region exclusive access lock.
 *
 * Once disabled, it could not be enabled until reset.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 */
void XRDC2_EnableMemExclAccessLock(XRDC2_Type *base, xrdc2_mem_t mem, bool enable)
{
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);

    if (enable)
    {
        base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = XRDC2_EAL_UNLOCKED;
    }
    else
    {
        base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = XRDC2_EAL_DISABLE_UNTIL_RESET;
    }
}

/*!
 * brief Get current memory region exclusive access lock owner.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 * param The domain ID of the lock owner.
 */
uint8_t XRDC2_GetMemExclAccessLockDomainOwner(XRDC2_Type *base, xrdc2_mem_t mem)
{
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);

    return (uint8_t)((base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W5 & XRDC2_MRC_MRGD_W5_EALO_MASK) >>
                     XRDC2_MRC_MRGD_W5_EALO_SHIFT);
}

/*!
 * brief Try to lock the memory region exclusive access.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 * retval kStatus_Fail Failed to lock.
 * retval kStatus_Success Locked succussfully.
 */
status_t XRDC2_TryLockMemExclAccess(XRDC2_Type *base, xrdc2_mem_t mem)
{
    status_t status;
    uint8_t curDomainID;
    uint32_t mrc               = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd              = XRDC2_GET_MRGD((uint32_t)mem);
    volatile uint32_t *lockReg = &(base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6);

    curDomainID = XRDC2_GetCurrentMasterDomainId(base);

    *lockReg = XRDC2_EAL_LOCKED;

    if (curDomainID != XRDC2_GetMemExclAccessLockDomainOwner(base, mem))
    {
        status = kStatus_Fail;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Lock the memory region exclusive access using blocking method.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 *
 * note This function must be called when the lock is not disabled.
 */
void XRDC2_LockMemExclAccess(XRDC2_Type *base, xrdc2_mem_t mem)
{
    uint8_t curDomainID;
    uint32_t mrc               = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd              = XRDC2_GET_MRGD((uint32_t)mem);
    volatile uint32_t *lockReg = &(base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6);

    curDomainID = XRDC2_GetCurrentMasterDomainId(base);

    while (true)
    {
        *lockReg = XRDC2_EAL_LOCKED;

        /* Locked and owner is current domain. */
        if (curDomainID == XRDC2_GetMemExclAccessLockDomainOwner(base, mem))
        {
            break;
        }
    }

    return;
}

/*!
 * brief Unlock the memory region exclusive access.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 *
 * note This function must be called by the lock owner.
 */
void XRDC2_UnlockMemExclAccess(XRDC2_Type *base, xrdc2_mem_t mem)
{
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);

    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = XRDC2_EAL_UNLOCKED;
}

/*!
 * brief Force the memory region exclusive access lock release.
 *
 * The master does not own the lock could call this function to force release the lock.
 *
 * param base XRDC2 peripheral base address.
 * param mem The memory region to operate.
 */
void XRDC2_ForceMemExclAccessLockRelease(XRDC2_Type *base, xrdc2_mem_t mem)
{
    uint32_t mrc  = XRDC2_GET_MRC((uint32_t)mem);
    uint32_t mrgd = XRDC2_GET_MRGD((uint32_t)mem);

    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = XRDC2_EAL_FORCE_RELEASE_MAGIC_0;
    base->MRCI_MRGDJ[mrc][mrgd].MRC_MRGD_W6 = XRDC2_EAL_FORCE_RELEASE_MAGIC_1;
}

/*!
 * brief Gets the default peripheral access configuration.
 *
 * The default configuration is set as follows:
 * code
 * config->lockMode          = kXRDC2_AccessConfigLockWritable;
 * config->policy[0]         = kXRDC2_AccessPolicyNone;
 * config->policy[1]         = kXRDC2_AccessPolicyNone;
 * ...
 * config->policy[15]        = kXRDC2_AccessPolicyNone;
 * endcode
 *
 * param config Pointer to the configuration structure.
 */
void XRDC2_GetPeriphAccessDefaultConfig(xrdc2_periph_access_config_t *config)
{
    assert(NULL != config);

    uint8_t domain;

    config->lockMode = kXRDC2_AccessConfigLockDisabled;

    for (domain = 0; domain < (uint32_t)FSL_FEATURE_XRDC2_DOMAIN_COUNT; domain++)
    {
        config->policy[domain] = kXRDC2_AccessPolicyNone;
    }
}

/*!
 * brief Sets the peripheral access policy.
 *
 * param base XRDC2 peripheral base address.
 * param config Pointer to the access policy configuration structure.
 */
void XRDC2_SetPeriphAccessConfig(XRDC2_Type *base, xrdc2_periph_t periph, const xrdc2_periph_access_config_t *config)
{
    assert(NULL != config);

    uint32_t w0 = 0;
    uint32_t w1 = 0;

    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    XRDC2_MakeDXACP(config->policy, &w0, &w1);

    w1 |= XRDC2_PAC_PDAC_W1_DL2(config->lockMode);
    w1 |= XRDC2_PAC_PDAC_W1_VLD_MASK;

    base->PACI_PDACJ[pac][pdac].PAC_PDAC_W0 = w0;
    base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = w1;
}

/*!
 * brief Sets the peripheral descriptor as valid or invalid.
 *
 * param base XRDC2 peripheral base address.
 * param periph Which peripheral descriptor to set.
 * param valid True to set valid, false to set invalid.
 */
void XRDC2_SetPeriphAccessValid(XRDC2_Type *base, xrdc2_periph_t periph, bool valid)
{
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);
    uint32_t reg  = base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 & ~XRDC2_EAL_MASK;

    if (valid)
    {
        base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = (reg | XRDC2_PAC_PDAC_W1_VLD_MASK);
    }
    else
    {
        base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = (reg & ~XRDC2_PAC_PDAC_W1_VLD_MASK);
    }
}

/*!
 * brief Sets the peripheral descriptor lock mode.
 *
 * param base XRDC2 peripheral base address.
 * param periph Which peripheral descriptor to set.
 * param lockMode The lock mode to set.
 */
void XRDC2_SetPeriphAccessLockMode(XRDC2_Type *base, xrdc2_periph_t periph, xrdc2_access_config_lock_t lockMode)
{
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);
    uint32_t reg  = base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 & ~(XRDC2_EAL_MASK | XRDC2_PAC_PDAC_W1_DL2_MASK);

    base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = (reg | XRDC2_PAC_PDAC_W1_DL2(lockMode));
}

/*!
 * brief Sets the peripheral access policy for specific domain.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 * param domainId The ID of the domain whose policy will be changed.
 * param policy The access policy to set.
 */
void XRDC2_SetPeriphDomainAccessPolicy(XRDC2_Type *base,
                                       xrdc2_periph_t periph,
                                       uint8_t domainId,
                                       xrdc2_access_policy_t policy)
{
    uint32_t reg;
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    if (domainId < 8U)
    {
        reg = base->PACI_PDACJ[pac][pdac].PAC_PDAC_W0 & ~XRDC2_DXACP_0_7_MASK(domainId);
        reg |= XRDC2_DXACP_0_7(domainId, policy);
        base->PACI_PDACJ[pac][pdac].PAC_PDAC_W0 = reg;
    }
    else
    {
        reg = base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 & ~XRDC2_DXACP_8_15_MASK(domainId);
        reg |= XRDC2_DXACP_8_15(domainId, policy);
        reg &= ~XRDC2_EAL_MASK;
        base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = reg;
    }
}

/*!
 * brief Get current peripheral exclusive access lock owner.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 * param The domain ID of the lock owner.
 */
uint8_t XRDC2_GetPeriphExclAccessLockDomainOwner(XRDC2_Type *base, xrdc2_periph_t periph)
{
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    return (uint8_t)((base->PACI_PDACJ[pac][pdac].PAC_PDAC_W0 & XRDC2_PAC_PDAC_W0_EALO_MASK) >>
                     XRDC2_PAC_PDAC_W0_EALO_SHIFT);
}

/*!
 * brief Disable the peripheral exclusive access lock.
 *
 * Once disabled, it could not be enabled until reset.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 * param enable True to enable, false to disable.
 */
void XRDC2_EnablePeriphExclAccessLock(XRDC2_Type *base, xrdc2_periph_t periph, bool enable)
{
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    if (enable)
    {
        base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = XRDC2_EAL_UNLOCKED;
    }
    else
    {
        base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = XRDC2_EAL_DISABLE_UNTIL_RESET;
    }
}

/*!
 * brief Try to lock the peripheral exclusive access.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 * retval kStatus_Fail Failed to lock.
 * retval kStatus_Success Locked succussfully.
 */
status_t XRDC2_TryLockPeriphExclAccess(XRDC2_Type *base, xrdc2_periph_t periph)
{
    status_t status;
    uint8_t curDomainID;
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    volatile uint32_t *lockReg = &(base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1);

    curDomainID = XRDC2_GetCurrentMasterDomainId(base);

    *lockReg = XRDC2_EAL_LOCKED;

    if (curDomainID != XRDC2_GetPeriphExclAccessLockDomainOwner(base, periph))
    {
        status = kStatus_Fail;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Lock the peripheral exclusive access using blocking method.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 *
 * note This function must be called when the lock is not disabled.
 */
void XRDC2_LockPeriphExclAccess(XRDC2_Type *base, xrdc2_periph_t periph)
{
    uint8_t curDomainID;
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    volatile uint32_t *lockReg = &(base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1);

    curDomainID = XRDC2_GetCurrentMasterDomainId(base);

    while (true)
    {
        *lockReg = XRDC2_EAL_LOCKED;

        /* Locked and owner is current domain. */
        if (curDomainID == XRDC2_GetPeriphExclAccessLockDomainOwner(base, periph))
        {
            break;
        }
    }

    return;
}

/*!
 * brief Unlock the peripheral exclusive access.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 *
 * note This function must be called by the lock owner.
 */
void XRDC2_UnlockPeriphExclAccess(XRDC2_Type *base, xrdc2_periph_t periph)
{
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = XRDC2_EAL_UNLOCKED;
}

/*!
 * brief Force the peripheral exclusive access lock release.
 *
 * The master does not own the lock could call this function to force release the lock.
 *
 * param base XRDC2 peripheral base address.
 * param periph The peripheral to operate.
 */
void XRDC2_ForcePeriphExclAccessLockRelease(XRDC2_Type *base, xrdc2_periph_t periph)
{
    uint32_t pac  = XRDC2_GET_PAC((uint32_t)periph);
    uint32_t pdac = XRDC2_GET_PDAC((uint32_t)periph);

    base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = XRDC2_EAL_FORCE_RELEASE_MAGIC_0;
    base->PACI_PDACJ[pac][pdac].PAC_PDAC_W1 = XRDC2_EAL_FORCE_RELEASE_MAGIC_1;
}
