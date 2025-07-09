/*
 * Copyright 2019-2020, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_XRDC2_H_
#define FSL_XRDC2_H_

#include "fsl_common.h"

/*!
 * @addtogroup xrdc2
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/
/*! @brief Driver version. */
#define FSL_XRDC2_DRIVER_VERSION (MAKE_VERSION(2, 0, 3))

/* Definitions for XRDC2 Exclusive access lock. */
#define XRDC2_EAL_FORCE_RELEASE_MAGIC_0 0x02000046UL
#define XRDC2_EAL_FORCE_RELEASE_MAGIC_1 0x02000052UL

#define XRDC2_EAL_DISABLE             (0UL << XRDC2_MSC_MSAC_W1_EAL_SHIFT)
#define XRDC2_EAL_DISABLE_UNTIL_RESET (1UL << XRDC2_MSC_MSAC_W1_EAL_SHIFT)
#define XRDC2_EAL_UNLOCKED            (2UL << XRDC2_MSC_MSAC_W1_EAL_SHIFT)
#define XRDC2_EAL_LOCKED              (3UL << XRDC2_MSC_MSAC_W1_EAL_SHIFT)

#define XRDC2_EAL_MASK XRDC2_MSC_MSAC_W1_EAL_MASK

/*!
 * @brief Global configuration lock.
 */
typedef enum _xrdc2_global_config_lock
{
    kXRDC2_GlobalConfigLockDisabled,           /*!< Lock disabled, registers can be written by any domain. */
    kXRDC2_GlobalConfigLockDisabledUntilReset, /*!< Lock disabled until the next reset. */
    kXRDC2_GlobalConfigLockOwnerOnly,          /*!< Lock enabled, only the lock owner can write. */
    kXRDC2_GlobalConfigLockEnabledUntilReset   /*!< Lock enabled, all registers are read only until the next reset. */
} xrdc2_global_config_lock_t;

/*!
 * @brief XRDC2 secure attribute, the register bit MDACi_MDAj_W0[SA],
 * secure/nonsecure attribute output on a hit.
 */
typedef enum _xrdc2_secure_attr
{
    kXRDC2_MasterSecure   = 0, /*!< Use the bus master's secure/nonsecure attribute directly. */
    kXRDC2_ForceSecure    = 2, /*!< Force the bus attribute for this master to secure.        */
    kXRDC2_ForceNonSecure = 3, /*!< Force the bus attribute for this master to non-secure.    */
} xrdc2_secure_attr_t;

/*!
 * @brief XRDC2 privileged attribute, the register bit MDACi_MDAj_W0[PA],
 * defines the privileged/user attribute on a hit.
 */
typedef enum _xrdc2_privilege_attr
{
    kXRDC2_MasterPrivilege = 0, /*!< Use the bus master's attribute directly. */
    kXRDC2_ForceUser       = 2, /*!< Force the bus attribute for this master to user.       */
    kXRDC2_ForcePrivilege  = 3, /*!< Force the bus attribute for this master to privileged. */
} xrdc2_privilege_attr_t;

/*!
 * @brief Domain assignment for the bus master.
 *
 * XRDC2 compares the bus master @e match @e input with the parameter
 * @ref xrdc2_master_domain_assignment_t::mask and
 * @ref xrdc2_master_domain_assignment_t::match in this structure.
 * If hit, the domain ID, privilege attribute, and secure attribute are used for the access.
 */
typedef struct _xrdc2_master_domain_assignment
{
    bool lock;                            /*!< Set true to lock the descriptor. */
    xrdc2_privilege_attr_t privilegeAttr; /*!< Privilege attribute. */
    xrdc2_secure_attr_t secureAttr;       /*!< Secure attribute. */
    uint8_t domainId;                     /*!< Domain ID used when this descriptor hit. */
    uint16_t mask;                        /*!< Mask used for descriptor hit. */
    uint16_t match;                       /*!< Match used for descriptor hit. */
} xrdc2_master_domain_assignment_t;

/*!
 * @brief XRDC2 domain access control policy.
 */
typedef enum _xrdc2_access_policy
{
    /*                               policy SecurePriv  SecureUser  NonSecurePriv  NonSecureUsr */
    kXRDC2_AccessPolicyNone = 0U, /*  000      none        none        none            none     */
    kXRDC2_AccessPolicyAlt1 = 1U, /*  001      r             r         none            none     */
    kXRDC2_AccessPolicyAlt2 = 2U, /*  010      r,w         none        none            none     */
    kXRDC2_AccessPolicyAlt3 = 3U, /*  011      r,w          r,w        none            none     */
    kXRDC2_AccessPolicyAlt4 = 4U, /*  100      r,w          r,w         r              none     */
    kXRDC2_AccessPolicyAlt5 = 5U, /*  101      r,w          r,w         r                r      */
    kXRDC2_AccessPolicyAlt6 = 6U, /*  110      r,w          r,w         r,w            none     */
    kXRDC2_AccessPolicyAll  = 7U  /*  111      r,w          r,w         r,w             r,w     */
} xrdc2_access_policy_t;

/*!
 * @brief Access configuration lock mode, the register field PDAC and MRGD LK2.
 */
typedef enum _xrdc2_access_config_lock
{
    kXRDC2_AccessConfigLockDisabled           = 0U, /*!< Entire PDACn/MRGDn/MSC can be written.       */
    kXRDC2_AccessConfigLockDisabledUntilReset = 1U, /*!< Entire PDACn/MRGDn/MSC can be written until next reset. */
    kXRDC2_AccessConfigLockDomainXOnly        = 2U, /*!< Domain x only write the DxACP field.     */
    kXRDC2_AccessConfigLockEnabledUntilReset  = 3U  /*!< PDACn/MRGDn/MSC is read-only until the next reset. */
} xrdc2_access_config_lock_t;

/*!
 * @brief XRDC2 peripheral domain access control configuration.
 */
typedef struct _xrdc2_periph_access_config
{
    xrdc2_access_config_lock_t lockMode;                          /*!< PDACn lock configuration.      */
    xrdc2_access_policy_t policy[FSL_FEATURE_XRDC2_DOMAIN_COUNT]; /*!< Access policy for each domain. */
} xrdc2_periph_access_config_t;

/*!
 * @brief XRDC2 memory region domain access control configuration.
 */
typedef struct _xrdc2_mem_access_config
{
    uint32_t startAddr;                  /*!< Memory region start address, should be 4k aligned. */
    uint32_t endAddr;                    /*!< Memory region end address, (endAddr + 1) should be 4k aligned. */
    xrdc2_access_config_lock_t lockMode; /*!< MRGDn lock configuration.      */
    xrdc2_access_policy_t policy[FSL_FEATURE_XRDC2_DOMAIN_COUNT]; /*!< Access policy for each domain. */
} xrdc2_mem_access_config_t;

/*!
 * @brief XRDC2 memory slot domain access control configuration.
 */
typedef struct _xrdc2_mem_slot_access_config
{
    xrdc2_access_config_lock_t lockMode;                          /*!< Descriptor lock configuration.      */
    xrdc2_access_policy_t policy[FSL_FEATURE_XRDC2_DOMAIN_COUNT]; /*!< Access policy for each domain. */
} xrdc2_mem_slot_access_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the XRDC2 module.
 *
 * @param base XRDC2 peripheral base address.
 */
void XRDC2_Init(XRDC2_Type *base);

/*!
 * @brief De-initializes the XRDC2 module.
 *
 * @param base XRDC2 peripheral base address.
 */
void XRDC2_Deinit(XRDC2_Type *base);

/*!
 * @name XRDC2 manager (XRDC2)
 * @{
 */

/*!
 * @brief Sets the XRDC2 global valid.
 *
 * This function sets the XRDC2 global valid or invalid. When the XRDC2 is global
 * invalid, all accesses from all bus masters to all slaves are allowed.
 *
 * @param base XRDC2 peripheral base address.
 * @param valid True to valid XRDC2.
 */
void XRDC2_SetGlobalValid(XRDC2_Type *base, bool valid);

/*!
 * @brief Gets the domain ID of the current bus master.
 *
 * This function returns the domain ID of the current bus master.
 *
 * @param base XRDC2 peripheral base address.
 * @return Domain ID of current bus master.
 */
static inline uint8_t XRDC2_GetCurrentMasterDomainId(XRDC2_Type *base)
{
#if defined(XRDC2_SR_DIN_MASK)
    return (uint8_t)((base->SR & XRDC2_SR_DIN_MASK) >> XRDC2_SR_DIN_SHIFT);
#else
    return (uint8_t)((base->SR & XRDC2_SR_DID_MASK) >> XRDC2_SR_DID_SHIFT);
#endif
}

/*!
 * @brief Set the global configuration lock mode.
 *
 * Once change the lock mode, it could not be changed until next reset.
 *
 * @param base XRDC2 peripheral base address.
 * @param mode The lock mode.
 */
static inline void XRDC2_SetGlobalConfigLock(XRDC2_Type *base, xrdc2_global_config_lock_t mode)
{
    base->MCR = (base->MCR & ~XRDC2_MCR_GCL_MASK) | XRDC2_MCR_GCL(mode);
}

/*!
 * @brief Gets the domain ID of global configuration lock owner.
 *
 * @param base XRDC2 peripheral base address.
 * @return Domain ID of the global configuration lock owner.
 */
static inline uint8_t XRDC2_GetCurrentGlobalConfigLockOwnerDomainId(XRDC2_Type *base)
{
    return (uint8_t)((base->SR & XRDC2_SR_GCLO_MASK) >> XRDC2_SR_GCLO_SHIFT);
}

/*! @} */

/*!
 * @name XRDC2 Master Domain Assignment Controller (XRDC2_MDAC).
 * @{
 */

/*!
 * @brief Gets the default master domain assignment.
 *
 * This function sets the assignment as follows:
 *
 * @code
 *  config->lock = false;
 *  config->privilegeAttr = kXRDC2_MasterPrivilege;
 *  config->secureAttr = kXRDC2_MasterSecure;
 *  config->domainId = 0U;
 *  config->mask = 0U;
 *  config->match = 0U;
 * @endcode
 *
 * @param assignment Pointer to the assignment structure.
 */
void XRDC2_GetDefaultMasterDomainAssignment(xrdc2_master_domain_assignment_t *assignment);

/*!
 * @brief Sets the processor bus master domain assignment.
 *
 * @param base XRDC2 peripheral base address.
 * @param master Which master to configure.
 * @param assignIndex Which assignment register to set.
 * @param assignment Pointer to the assignment structure.
 */
void XRDC2_SetMasterDomainAssignment(XRDC2_Type *base,
                                     xrdc2_master_t master,
                                     uint8_t assignIndex,
                                     const xrdc2_master_domain_assignment_t *assignment);

/*!
 * @brief Locks the bus master domain assignment register.
 *
 * This function locks the master domain assignment. One bus master might have
 * multiple domain assignment registers. The parameter \p assignIndex specifies
 * which assignment register to lock. After it is locked, the register can't be changed
 * until next reset.
 *
 * @param base XRDC2 peripheral base address.
 * @param master Which master to configure.
 * @param assignIndex Which assignment register to lock.
 */
static inline void XRDC2_LockMasterDomainAssignment(XRDC2_Type *base, xrdc2_master_t master, uint8_t assignIndex)
{
    base->MDACI_MDAJ[master][assignIndex].MDAC_MDA_W1 |= XRDC2_MDAC_MDA_W1_DL_MASK;
}

/*!
 * @brief Sets the master domain assignment as valid or invalid.
 *
 * This function sets the master domain assignment as valid or invalid. One bus master might have
 * multiple domain assignment registers. The parameter \p assignIndex specifies
 * which assignment register to configure.
 *
 * @param base XRDC2 peripheral base address.
 * @param master Which master to configure.
 * @param assignIndex Index for the domain assignment register.
 * @param valid True to set valid, false to set invalid.
 */
static inline void XRDC2_SetMasterDomainAssignmentValid(XRDC2_Type *base,
                                                        xrdc2_master_t master,
                                                        uint8_t assignIndex,
                                                        bool valid)
{
    if (valid)
    {
        base->MDACI_MDAJ[master][assignIndex].MDAC_MDA_W1 |= XRDC2_MDAC_MDA_W1_VLD_MASK;
    }
    else
    {
        base->MDACI_MDAJ[master][assignIndex].MDAC_MDA_W1 &= ~XRDC2_MDAC_MDA_W1_VLD_MASK;
    }
}

/*! @} */

/*!
 * @name XRDC2 Memory Slot Access Controller (XRDC2_MSC).
 * @{
 */

/*!
 * @brief Gets the default memory slot access configuration.
 *
 * This function sets the assignment as follows:
 *
 * @code
 *  config->lockMode = kXRDC2_AccessConfigLockDisabled;
 *  config->policy[0] = kXRDC2_AccessPolicyNone;
 *  config->policy[1] = kXRDC2_AccessPolicyNone;
 *  ...
 * @endcode
 *
 * @param config Pointer to the configuration.
 */
void XRDC2_GetMemSlotAccessDefaultConfig(xrdc2_mem_slot_access_config_t *config);

/*!
 * @brief Sets the memory slot access policy.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot Which memory slot descriptor to set.
 * @param config Pointer to the access policy configuration structure.
 */
void XRDC2_SetMemSlotAccessConfig(XRDC2_Type *base,
                                  xrdc2_mem_slot_t memSlot,
                                  const xrdc2_mem_slot_access_config_t *config);

/*!
 * @brief Sets the memory slot descriptor as valid or invalid.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot Which memory slot descriptor to set.
 * @param valid True to set valid, false to set invalid.
 */
void XRDC2_SetMemSlotAccessValid(XRDC2_Type *base, xrdc2_mem_slot_t memSlot, bool valid);

/*!
 * @brief Sets the memory slot descriptor lock mode.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot Which memory slot descriptor to set.
 * @param lockMode The lock mode to set.
 */
void XRDC2_SetMemSlotAccessLockMode(XRDC2_Type *base, xrdc2_mem_slot_t memSlot, xrdc2_access_config_lock_t lockMode);

/*!
 * @brief Sets the memory slot access policy for specific domain.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 * @param domainId The ID of the domain whose policy will be changed.
 * @param policy The access policy to set.
 */
void XRDC2_SetMemSlotDomainAccessPolicy(XRDC2_Type *base,
                                        xrdc2_mem_slot_t memSlot,
                                        uint8_t domainId,
                                        xrdc2_access_policy_t policy);

/*!
 * @brief Enable or disable the memory slot exclusive access lock.
 *
 * The lock must be enabled first before use. Once disabled, it could not be
 * enabled until reset.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 * @param enable True to enable, false to disable.
 */
void XRDC2_EnableMemSlotExclAccessLock(XRDC2_Type *base, xrdc2_mem_slot_t memSlot, bool enable);

/*!
 * @brief Get current memory slot exclusive access lock owner.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 * @return The domain ID of the lock owner.
 */
uint8_t XRDC2_GetMemSlotExclAccessLockDomainOwner(XRDC2_Type *base, xrdc2_mem_slot_t memSlot);

/*!
 * @brief Try to lock the memory slot exclusive access.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 * @retval kStatus_Fail Failed to lock.
 * @retval kStatus_Success Locked succussfully.
 */
status_t XRDC2_TryLockMemSlotExclAccess(XRDC2_Type *base, xrdc2_mem_slot_t memSlot);

/*!
 * @brief Lock the memory slot exclusive access using blocking method.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 *
 * @note This function must be called when the lock is not disabled.
 */
void XRDC2_LockMemSlotExclAccess(XRDC2_Type *base, xrdc2_mem_slot_t memSlot);

/*!
 * @brief Unlock the memory slot exclusive access.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 *
 * @note This function must be called by the lock owner.
 */
static inline void XRDC2_UnlockMemSlotExclAccess(XRDC2_Type *base, xrdc2_mem_slot_t memSlot)
{
    base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = XRDC2_EAL_UNLOCKED;
}

/*!
 * @brief Force the memory slot exclusive access lock release.
 *
 * The master does not own the lock could call this function to force release the lock.
 *
 * @param base XRDC2 peripheral base address.
 * @param memSlot The memory slot to operate.
 */
static inline void XRDC2_ForceMemSlotExclAccessLockRelease(XRDC2_Type *base, xrdc2_mem_slot_t memSlot)
{
    base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = XRDC2_EAL_FORCE_RELEASE_MAGIC_0;
    base->MSCI_MSAC_WK[(uint32_t)memSlot].MSC_MSAC_W1 = XRDC2_EAL_FORCE_RELEASE_MAGIC_1;
}

/*! @} */

/*!
 * @name XRDC2 Memory Region Controller (XRDC2_MRC)
 * @{
 */

/*!
 * @brief Gets the default memory access configuration.
 *
 * This function sets the assignment as follows:
 *
 * @code
 *  config->startAddr = 0U;
 *  config->endAddr = 0xFFFFFFFFU;
 *  config->lockMode = kXRDC2_AccessConfigLockDisabled;
 *  config->policy[0] = kXRDC2_AccessPolicyNone;
 *  config->policy[1] = kXRDC2_AccessPolicyNone;
 *  ...
 * @endcode
 *
 * @param config Pointer to the configuration.
 */
void XRDC2_GetMemAccessDefaultConfig(xrdc2_mem_access_config_t *config);

/*!
 * @brief Sets the memory region access policy.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem Which memory region descriptor to set.
 * @param config Pointer to the access policy configuration structure.
 */
void XRDC2_SetMemAccessConfig(XRDC2_Type *base, xrdc2_mem_t mem, const xrdc2_mem_access_config_t *config);

/*!
 * @brief Sets the memory region descriptor as valid or invalid.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem Which memory region descriptor to set.
 * @param valid True to set valid, false to set invalid.
 */
void XRDC2_SetMemAccessValid(XRDC2_Type *base, xrdc2_mem_t mem, bool valid);

/*!
 * @brief Sets the memory descriptor lock mode.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem Which memory descriptor to set.
 * @param lockMode The lock mode to set.
 */
void XRDC2_SetMemAccessLockMode(XRDC2_Type *base, xrdc2_mem_t mem, xrdc2_access_config_lock_t lockMode);

/*!
 * @brief Sets the memory region access policy for specific domain.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 * @param domainId The ID of the domain whose policy will be changed.
 * @param policy The access policy to set.
 */
void XRDC2_SetMemDomainAccessPolicy(XRDC2_Type *base, xrdc2_mem_t mem, uint8_t domainId, xrdc2_access_policy_t policy);

/*!
 * @brief Enable or disable the memory region exclusive access lock.
 *
 * Once disabled, it could not be enabled until reset.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 * @param enable True to enable, false to disable.
 */
void XRDC2_EnableMemExclAccessLock(XRDC2_Type *base, xrdc2_mem_t mem, bool enable);

/*!
 * @brief Get current memory region exclusive access lock owner.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 * @return The domain ID of the lock owner.
 */
uint8_t XRDC2_GetMemExclAccessLockDomainOwner(XRDC2_Type *base, xrdc2_mem_t mem);

/*!
 * @brief Try to lock the memory region exclusive access.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 * @retval kStatus_Fail Failed to lock.
 * @retval kStatus_Success Locked succussfully.
 */
status_t XRDC2_TryLockMemExclAccess(XRDC2_Type *base, xrdc2_mem_t mem);

/*!
 * @brief Lock the memory region exclusive access using blocking method.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 *
 * @note This function must be called when the lock is not disabled.
 */
void XRDC2_LockMemExclAccess(XRDC2_Type *base, xrdc2_mem_t mem);

/*!
 * @brief Unlock the memory region exclusive access.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 *
 * @note This function must be called by the lock owner.
 */
void XRDC2_UnlockMemExclAccess(XRDC2_Type *base, xrdc2_mem_t mem);

/*!
 * @brief Force the memory region exclusive access lock release.
 *
 * The master does not own the lock could call this function to force release the lock.
 *
 * @param base XRDC2 peripheral base address.
 * @param mem The memory region to operate.
 */
void XRDC2_ForceMemExclAccessLockRelease(XRDC2_Type *base, xrdc2_mem_t mem);

/*! @} */

/*!
 * @name XRDC2 Peripheral Access Controller (XRDC2_PAC)
 * @{
 */

/*!
 * @brief Gets the default peripheral access configuration.
 *
 * The default configuration is set as follows:
 * @code
 * config->lockMode          = kXRDC2_AccessConfigLockWritable;
 * config->policy[0]         = kXRDC2_AccessPolicyNone;
 * config->policy[1]         = kXRDC2_AccessPolicyNone;
 * ...
 * config->policy[15]        = kXRDC2_AccessPolicyNone;
 * @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void XRDC2_GetPeriphAccessDefaultConfig(xrdc2_periph_access_config_t *config);

/*!
 * @brief Sets the peripheral access policy.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph Which peripheral descriptor to set.
 * @param config Pointer to the access policy configuration structure.
 */
void XRDC2_SetPeriphAccessConfig(XRDC2_Type *base, xrdc2_periph_t periph, const xrdc2_periph_access_config_t *config);

/*!
 * @brief Sets the peripheral descriptor as valid or invalid.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph Which peripheral descriptor to set.
 * @param valid True to set valid, false to set invalid.
 */
void XRDC2_SetPeriphAccessValid(XRDC2_Type *base, xrdc2_periph_t periph, bool valid);

/*!
 * @brief Sets the peripheral descriptor lock mode.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph Which peripheral descriptor to set.
 * @param lockMode The lock mode to set.
 */
void XRDC2_SetPeriphAccessLockMode(XRDC2_Type *base, xrdc2_periph_t periph, xrdc2_access_config_lock_t lockMode);

/*!
 * @brief Sets the peripheral access policy for specific domain.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 * @param domainId The ID of the domain whose policy will be changed.
 * @param policy The access policy to set.
 */
void XRDC2_SetPeriphDomainAccessPolicy(XRDC2_Type *base,
                                       xrdc2_periph_t periph,
                                       uint8_t domainId,
                                       xrdc2_access_policy_t policy);

/*!
 * @brief Disable the peripheral exclusive access lock.
 *
 * Once disabled, it could not be enabled until reset.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 * @param enable True to enable, false to disable.
 */
void XRDC2_EnablePeriphExclAccessLock(XRDC2_Type *base, xrdc2_periph_t periph, bool enable);

/*!
 * @brief Get current peripheral exclusive access lock owner.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 * @return The domain ID of the lock owner.
 */
uint8_t XRDC2_GetPeriphExclAccessLockDomainOwner(XRDC2_Type *base, xrdc2_periph_t periph);

/*!
 * @brief Try to lock the peripheral exclusive access.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 * @retval kStatus_Fail Failed to lock.
 * @retval kStatus_Success Locked succussfully.
 */
status_t XRDC2_TryLockPeriphExclAccess(XRDC2_Type *base, xrdc2_periph_t periph);

/*!
 * @brief Lock the peripheral exclusive access using blocking method.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 *
 * @note This function must be called when the lock is not disabled.
 */
void XRDC2_LockPeriphExclAccess(XRDC2_Type *base, xrdc2_periph_t periph);

/*!
 * @brief Unlock the peripheral exclusive access.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 *
 * @note This function must be called by the lock owner.
 */
void XRDC2_UnlockPeriphExclAccess(XRDC2_Type *base, xrdc2_periph_t periph);

/*!
 * @brief Force the peripheral exclusive access lock release.
 *
 * The master does not own the lock could call this function to force release the lock.
 *
 * @param base XRDC2 peripheral base address.
 * @param periph The peripheral to operate.
 */
void XRDC2_ForcePeriphExclAccessLockRelease(XRDC2_Type *base, xrdc2_periph_t periph);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_XRDC2_H_ */
