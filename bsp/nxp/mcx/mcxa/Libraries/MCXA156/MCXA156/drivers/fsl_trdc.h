/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_TRDC_H_
#define FSL_TRDC_H_

#include "fsl_common.h"
#include "fsl_trdc_core.h"

/*!
 * @addtogroup trdc
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/
#define FSL_TRDC_DRIVER_VERSION (MAKE_VERSION(2, 2, 1))

#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/* Hardware configuration definitions */
/*!
 * @brief TRDC hardware configuration.
 */
typedef struct _trdc_hardware_config
{
    uint8_t masterNumber; /*!< Number of bus masters. */
    uint8_t domainNumber; /*!< Number of domains.     */
    uint8_t mbcNumber;    /*!< Number of MBCs.        */
    uint8_t mrcNumber;    /*!< Number of MRCs.        */
} trdc_hardware_config_t;
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC
/*!
 * @brief Hardware configuration of the two slave memories within each MBC(memory block checker).
 */
typedef struct _trdc_slave_memory_hardware_config
{
    uint32_t blockNum;  /*!< Number of blocks. */
    uint32_t blockSize; /*!< Block size. */
} trdc_slave_memory_hardware_config_t;
#endif

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT) && FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT
/* Master domain assignment definitions */
/*!
 * @brief TRDC domain ID select method, the register bit TRDC_MDA_W0_0_DFMT0[DIDS], used for
 * domain hit evaluation.
 */
typedef enum _trdc_did_sel
{
    kTRDC_DidMda,         /*!< Use MDAn[2:0] as DID. */
    kTRDC_DidInput,       /*!< Use the input DID (DID_in) as DID. */
    kTRDC_DidMdaAndInput, /*!< Use MDAn[2] concatenated with DID_in[1:0] as DID. */
    kTRDC_DidReserved     /*!< Reserved. */
} trdc_did_sel_t;

/*!
 * @brief TRDC secure attribute, the register bit TRDC_MDA_W0_0_DFMT0[SA], used for
 * bus master domain assignment.
 */
typedef enum _trdc_secure_attr
{
    kTRDC_ForceSecure,    /*!< Force the bus attribute for this master to secure.        */
    kTRDC_ForceNonSecure, /*!< Force the bus attribute for this master to non-secure.    */
    kTRDC_MasterSecure,   /*!< Use the bus master's secure/nonsecure attribute directly. */
    kTRDC_MasterSecure1,  /*!< Use the bus master's secure/nonsecure attribute directly. */
} trdc_secure_attr_t;

/*!
 * @brief The configuration of domain hit evaluation of PID.
 */
typedef enum _trdc_pid_domain_hit_config
{
    kTRDC_pidDomainHitNone0,     /*!< No PID is included in the domain hit evaluation. */
    kTRDC_pidDomainHitNone1,     /*!< No PID is included in the domain hit evaluation. */
    kTRDC_pidDomainHitInclusive, /*!< The PID is included in the domain hit evaluation when (PID & ~PIDM). */
    kTRDC_pidDomainHitExclusive, /*!< The PID is included in the domain hit evaluation when ~(PID & ~PIDM). */
} trdc_pid_domain_hit_config_t;

/*!
 * @brief Domain assignment for the processor bus master.
 */
typedef struct _trdc_processor_domain_assignment
{
    uint32_t domainId : 4U;           /*!< Domain ID. */
    uint32_t domainIdSelect : 2U;     /*!< Domain ID select method, see @ref trdc_did_sel_t. */
    uint32_t pidDomainHitConfig : 2U; /*!< The configuration of the domain hit evaluation for PID, see @ref
                                         trdc_pid_domain_hit_config_t. */
    uint32_t pidMask : 6U;    /*!< The mask combined with PID, so multiple PID can be included as part of the domain hit
                                 determination. Set to 0 to disable. */
    uint32_t secureAttr : 2U; /*!< Secure attribute, see @ref trdc_secure_attr_t. */
    uint32_t pid : 6U;  /*!< The process identifier, combined with pidMask to form the domain hit determination. */
    uint32_t : 8U;      /*!< Reserved. */
    uint32_t lock : 1U; /*!< Lock the register. */
    uint32_t : 1U;      /*!< Reserved. */
} trdc_processor_domain_assignment_t;

/*!
 * @brief TRDC privileged attribute, the register bit TRDC_MDA_W0_x_DFMT1[PA], used for non-processor
 * bus master domain assignment.
 */
typedef enum _trdc_privilege_attr
{
    kTRDC_ForceUser,        /*!< Force the bus attribute for this master to user. */
    kTRDC_ForcePrivilege,   /*!< Force the bus attribute for this master to privileged. */
    kTRDC_MasterPrivilege,  /*!< Use the bus master's attribute directly. */
    kTRDC_MasterPrivilege1, /*!< Use the bus master's attribute directly. */
} trdc_privilege_attr_t;

/*!
 * @brief Domain assignment for the non-processor bus master.
 */
typedef struct _trdc_non_processor_domain_assignment
{
    uint32_t domainId : 4U;       /*!< Domain ID. */
    uint32_t privilegeAttr : 2U;  /*!< Privileged attribute, see @ref trdc_privilege_attr_t. */
    uint32_t secureAttr : 2U;     /*!< Secure attribute, see @ref trdc_secure_attr_t. */
    uint32_t bypassDomainId : 1U; /*!< Bypass domain ID. */
    uint32_t : 21U;               /*!< Reserved. */
    uint32_t lock : 1U;           /*!< Lock the register. */
    uint32_t : 1U;                /*!< Reserved. */
} trdc_non_processor_domain_assignment_t;

/*!
 * @brief PID lock configuration.
 */
typedef enum _trdc_pid_lock
{
    kTRDC_PidUnlocked0, /*!< The PID value can be updated by any secure priviledged write. */
    kTRDC_PidUnlocked1, /*!< The PID value can be updated by any secure priviledged write. */
    kTRDC_PidUnlocked2, /*!< The PID value can be updated by any secure priviledged write from the bus master that first
                           configured this register. */
    kTRDC_PidLocked,    /*!< The PID value is locked until next reset. */
} trdc_pid_lock_t;

/*!
 * @brief Process identifier(PID) configuration for processor cores.
 */
typedef struct _trdc_pid_config
{
    uint32_t pid : 6U;  /*!< The process identifier of the executing task. The highest bit can be used to define
                           secure/nonsecure attribute of the task. */
    uint32_t : 23U;     /*!< Reserved. */
    uint32_t lock : 2U; /*!< How to lock the register, see @ref trdc_pid_lock_t. */
    uint32_t : 1U;      /*!< Reserved. */
} trdc_pid_config_t;
#endif

#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/* TZ-M congiguration definitions */
/*!
 * @brief IDAU(Implementation-Defined Attribution Unit) configuration for TZ-M function control.
 */
typedef struct _trdc_idau_config
{
    uint32_t : 8U;                   /*!< Reserved. */
    uint32_t lockSecureVTOR : 1U;    /*!< Disable writes to secure VTOR(Vector Table Offset Register). */
    uint32_t lockNonsecureVTOR : 1U; /*!< Disable writes to non-secure VTOR, Application interrupt and Reset Control
                                        Registers. */
    uint32_t lockSecureMPU : 1U; /*!< Disable writes to secure MPU(Memory Protection Unit) from software or from a debug
                                    agent connected to the processor in Secure state. */
    uint32_t lockNonsecureMPU : 1U; /*!< Disable writes to non-secure MPU(Memory Protection Unit) from software or from
                                       a debug agent connected to the processor. */
    uint32_t lockSAU : 1U;          /*!< Disable writes to SAU(Security Attribution Unit) registers. */
    uint32_t : 19U;                 /*!< Reserved. */
} trdc_idau_config_t;

/* FLW(Flash Logical Window) configuration definitions */
/*!
 * @brief FLW(Flash Logical Window) configuration.
 */
typedef struct _trdc_flw_config
{
    uint16_t blockCount;    /*!< Block count of the Flash Logic Window in 32KByte blocks. */
    uint32_t arrayBaseAddr; /*!< Flash array base address of the Flash Logical Window. */
    bool lock;              /*!< Disable writes to FLW registers. */
    bool enable;            /*!< Enable FLW function. */
} trdc_flw_config_t;
#endif

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR) && FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR
/* Domain error check and clear definitions */
/*!
 * @brief TRDC controller definition for domain error check. Each TRDC instance may have different
 * MRC or MBC count, call TRDC_GetHardwareConfig to get the actual count.
 */
typedef enum _trdc_controller
{
    kTRDC_MemBlockController0 = 0U,  /*!< Memory block checker 0. */
    kTRDC_MemBlockController1 = 1U,  /*!< Memory block checker 1. */
    kTRDC_MemBlockController2 = 2U,  /*!< Memory block checker 2. */
    kTRDC_MemBlockController3 = 3U,  /*!< Memory block checker 3. */
    kTRDC_MemRegionChecker0   = 4U,  /*!< Memory region checker 0.   */
    kTRDC_MemRegionChecker1   = 5U,  /*!< Memory region checker 1.   */
    kTRDC_MemRegionChecker2   = 6U,  /*!< Memory region checker 2.   */
    kTRDC_MemRegionChecker3   = 7U,  /*!< Memory region checker 3.   */
    kTRDC_MemRegionChecker4   = 8U,  /*!< Memory region checker 4.   */
    kTRDC_MemRegionChecker5   = 9U,  /*!< Memory region checker 5.   */
    kTRDC_MemRegionChecker6   = 10U, /*!< Memory region checker 6.   */
} trdc_controller_t;

/*!
 * @brief TRDC domain error state definition TRDC_MBCn_DERR_W1[EST] or TRDC_MRCn_DERR_W1[EST].
 */
typedef enum _trdc_error_state
{
    kTRDC_ErrorStateNone   = 0x00U, /*!< No access violation detected.       */
    kTRDC_ErrorStateNone1  = 0x01U, /*!< No access violation detected.       */
    kTRDC_ErrorStateSingle = 0x02U, /*!< Single access violation detected.   */
    kTRDC_ErrorStateMulti  = 0x03U  /*!< Multiple access violation detected. */
} trdc_error_state_t;

/*!
 * @brief TRDC domain error attribute definition TRDC_MBCn_DERR_W1[EATR] or TRDC_MRCn_DERR_W1[EATR].
 */
typedef enum _trdc_error_attr
{
    kTRDC_ErrorSecureUserInst         = 0x00U, /*!< Secure user mode, instruction fetch access.           */
    kTRDC_ErrorSecureUserData         = 0x01U, /*!< Secure user mode, data access.                        */
    kTRDC_ErrorSecurePrivilegeInst    = 0x02U, /*!< Secure privileged mode, instruction fetch access.     */
    kTRDC_ErrorSecurePrivilegeData    = 0x03U, /*!< Secure privileged mode, data access.                  */
    kTRDC_ErrorNonSecureUserInst      = 0x04U, /*!< NonSecure user mode, instruction fetch access.        */
    kTRDC_ErrorNonSecureUserData      = 0x05U, /*!< NonSecure user mode, data access.                     */
    kTRDC_ErrorNonSecurePrivilegeInst = 0x06U, /*!< NonSecure privileged mode, instruction fetch access.  */
    kTRDC_ErrorNonSecurePrivilegeData = 0x07U  /*!< NonSecure privileged mode, data access.               */
} trdc_error_attr_t;

/*!
 * @brief TRDC domain error access type definition TRDC_DERR_W1_n[ERW].
 */
typedef enum _trdc_error_type
{
    kTRDC_ErrorTypeRead  = 0x00U, /*!< Error occurs on read reference.  */
    kTRDC_ErrorTypeWrite = 0x01U  /*!< Error occurs on write reference. */
} trdc_error_type_t;

/*!
 * @brief TRDC domain error definition.
 */
typedef struct _trdc_domain_error
{
    trdc_controller_t controller;  /*!< Which controller captured access violation.     */
    uint32_t address;              /*!< Access address that generated access violation. */
    trdc_error_state_t errorState; /*!< Error state.                                    */
    trdc_error_attr_t errorAttr;   /*!< Error attribute.                                */
    trdc_error_type_t errorType;   /*!< Error type.                                     */
    uint8_t errorPort;             /*!< Error port.                                     */
    uint8_t domainId;              /*!< Domain ID.                                      */
    uint8_t slaveMemoryIdx;        /*!< The slave memory index. Only apply when violation in MBC. */
} trdc_domain_error_t;
#endif

#if (defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC) || \
    (defined(FSL_FEATURE_TRDC_HAS_MRC) && FSL_FEATURE_TRDC_HAS_MRC)
/* Common definitions for MBC/MRC configuration */
/*!
 * @brief Memory access control configuration for MBC/MRC.
 */
typedef struct _trdc_memory_access_control_config
{
    uint32_t nonsecureUsrX : 1U;  /*!< Allow nonsecure user execute access. */
    uint32_t nonsecureUsrW : 1U;  /*!< Allow nonsecure user write access. */
    uint32_t nonsecureUsrR : 1U;  /*!< Allow nonsecure user read access. */
    uint32_t : 1U;                /*!< Reserved. */
    uint32_t nonsecurePrivX : 1U; /*!< Allow nonsecure privilege execute access. */
    uint32_t nonsecurePrivW : 1U; /*!< Allow nonsecure privilege write access. */
    uint32_t nonsecurePrivR : 1U; /*!< Allow nonsecure privilege read access. */
    uint32_t : 1U;                /*!< Reserved. */
    uint32_t secureUsrX : 1U;     /*!< Allow secure user execute access. */
    uint32_t secureUsrW : 1U;     /*!< Allow secure user write access. */
    uint32_t secureUsrR : 1U;     /*!< Allow secure user read access. */
    uint32_t : 1U;                /*!< Reserved. */
    uint32_t securePrivX : 1U;    /*!< Allownsecure privilege execute access. */
    uint32_t securePrivW : 1U;    /*!< Allownsecure privilege write access. */
    uint32_t securePrivR : 1U;    /*!< Allownsecure privilege read access. */
    uint32_t : 16U;               /*!< Reserved. */
    uint32_t lock : 1U; /*!< Lock the configuration until next reset, only apply to access control register 0. */
} trdc_memory_access_control_config_t;
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MRC) && FSL_FEATURE_TRDC_HAS_MRC
/*! @brief The region descriptor enumeration, used to form a mask to set/clear the NSE bits for one or several regions.
 */
enum _trdc_region_descriptor
{
    kTRDC_RegionDescriptor0  = (1U << 0U),  /*!< Region descriptor 0. */
    kTRDC_RegionDescriptor1  = (1U << 1U),  /*!< Region descriptor 1. */
    kTRDC_RegionDescriptor2  = (1U << 2U),  /*!< Region descriptor 2. */
    kTRDC_RegionDescriptor3  = (1U << 3U),  /*!< Region descriptor 3. */
    kTRDC_RegionDescriptor4  = (1U << 4U),  /*!< Region descriptor 4. */
    kTRDC_RegionDescriptor5  = (1U << 5U),  /*!< Region descriptor 5. */
    kTRDC_RegionDescriptor6  = (1U << 6U),  /*!< Region descriptor 6. */
    kTRDC_RegionDescriptor7  = (1U << 7U),  /*!< Region descriptor 7. */
    kTRDC_RegionDescriptor8  = (1U << 8U),  /*!< Region descriptor 8. */
    kTRDC_RegionDescriptor9  = (1U << 9U),  /*!< Region descriptor 9. */
    kTRDC_RegionDescriptor10 = (1U << 10U), /*!< Region descriptor 10. */
    kTRDC_RegionDescriptor11 = (1U << 11U), /*!< Region descriptor 11. */
    kTRDC_RegionDescriptor12 = (1U << 12U), /*!< Region descriptor 12. */
    kTRDC_RegionDescriptor13 = (1U << 13U), /*!< Region descriptor 13. */
    kTRDC_RegionDescriptor14 = (1U << 14U), /*!< Region descriptor 14. */
    kTRDC_RegionDescriptor15 = (1U << 15U), /*!< Region descriptor 15. */
};

/* MRC configuration definitions */
/*! @brief The MRC domain enumeration, used to form a mask to enable/disable the update or clear all NSE bits of one or
 * several domains. */
enum _trdc_MRC_domain
{
    kTRDC_MrcDomain0  = (1U << 0U),  /*!< Domain 0. */
    kTRDC_MrcDomain1  = (1U << 1U),  /*!< Domain 1. */
    kTRDC_MrcDomain2  = (1U << 2U),  /*!< Domain 2. */
    kTRDC_MrcDomain3  = (1U << 3U),  /*!< Domain 3. */
    kTRDC_MrcDomain4  = (1U << 4U),  /*!< Domain 4. */
    kTRDC_MrcDomain5  = (1U << 5U),  /*!< Domain 5. */
    kTRDC_MrcDomain6  = (1U << 6U),  /*!< Domain 6. */
    kTRDC_MrcDomain7  = (1U << 7U),  /*!< Domain 7. */
    kTRDC_MrcDomain8  = (1U << 8U),  /*!< Domain 8. */
    kTRDC_MrcDomain9  = (1U << 9U),  /*!< Domain 9. */
    kTRDC_MrcDomain10 = (1U << 10U), /*!< Domain 10. */
    kTRDC_MrcDomain11 = (1U << 11U), /*!< Domain 11. */
    kTRDC_MrcDomain12 = (1U << 12U), /*!< Domain 12. */
    kTRDC_MrcDomain13 = (1U << 13U), /*!< Domain 13. */
    kTRDC_MrcDomain14 = (1U << 14U), /*!< Domain 14. */
    kTRDC_MrcDomain15 = (1U << 15U), /*!< Domain 15. */
};

/*!
 * @brief The configuration of each region descriptor per domain per MRC instance.
 */
typedef struct _trdc_mrc_region_descriptor_config
{
    uint8_t memoryAccessControlSelect; /*!< Select one of the 8 access control policies for this region, for
                                                access cotrol policies see @ref trdc_memory_access_control_config_t. */
    uint32_t startAddr;                /*!< Physical start address. */
    bool valid;                        /*!< Lock the register. */
    bool nseEnable;                    /*!< Enable non-secure accesses and disable secure accesses. */
    uint32_t endAddr;                  /*!< Physical start address. */
    uint8_t mrcIdx;                    /*!< The index of the MRC for this configuration to take effect. */
    uint8_t domainIdx;                 /*!< The index of the domain for this configuration to take effect. */
    uint8_t regionIdx;                 /*!< The index of the region for this configuration to take effect. */
} trdc_mrc_region_descriptor_config_t;
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC
/* MBC configuration definitions */
/*!
 * @brief The configuration of MBC NSE update.
 */
#if defined(FSL_FEATURE_TRDC_DOMAIN_COUNT) && (FSL_FEATURE_TRDC_DOMAIN_COUNT > 0x8U)
typedef struct _trdc_mbc_nse_update_config
{
    uint32_t autoIncrement : 1U; /*!< Whether to increment the word index after current word is updated using this
                                    configuration. */
    uint32_t : 1U;               /*!< Reserved. */
    uint32_t wordIdx : 4U;       /*!< MBC configuration word index to be updated. */
    uint32_t : 2U;               /*!< Reserved. */
    uint32_t memorySelect : 4U;  /*!< Bit mask of the selected memory to be updated. @ref _trdc_MBC_memory. */
    uint32_t : 4U;               /*!< Reserved. */
    uint32_t domianSelect : 16U; /*!< Bit mask of the selected domain to be updated. @ref _trdc_MBC_domain. */
} trdc_mbc_nse_update_config_t;
#else
typedef struct _trdc_mbc_nse_update_config
{
    uint32_t : 2U;               /*!< Reserved. */
    uint32_t wordIdx : 4U;       /*!< MBC configuration word index to be updated. */
    uint32_t : 2U;               /*!< Reserved. */
    uint32_t memorySelect : 4U;  /*!< Bit mask of the selected memory to be updated. @ref _trdc_MBC_memory. */
    uint32_t : 4U;               /*!< Reserved. */
    uint32_t domianSelect : 8U;  /*!< Bit mask of the selected domain to be updated. @ref _trdc_MBC_domain. */
    uint32_t : 7U;               /*!< Reserved. */
    uint32_t autoIncrement : 1U; /*!< Whether to increment the word index after current word is updated using this
                                    configuration. */
} trdc_mbc_nse_update_config_t;
#endif

/*! @brief The MBC domain enumeration, used to form a mask to enable/disable the update or clear NSE bits of one or
 * several domains. */
enum _trdc_MBC_domain
{
    kTRDC_MbcDomain0 = (1U << 0U), /*!< Domain 0. */
    kTRDC_MbcDomain1 = (1U << 1U), /*!< Domain 1. */
    kTRDC_MbcDomain2 = (1U << 2U), /*!< Domain 2. */
    kTRDC_MbcDomain3 = (1U << 3U), /*!< Domain 3. */
    kTRDC_MbcDomain4 = (1U << 4U), /*!< Domain 4. */
    kTRDC_MbcDomain5 = (1U << 5U), /*!< Domain 5. */
    kTRDC_MbcDomain6 = (1U << 6U), /*!< Domain 6. */
    kTRDC_MbcDomain7 = (1U << 7U), /*!< Domain 7. */
};

/*! @brief The MBC slave memory enumeration, used to form a mask to enable/disable the update or clear NSE bits of one
 * or several memory block. */
enum _trdc_MBC_memory
{
    kTRDC_MbcSlaveMemory0 = (1U << 0U), /*!< Memory 0. */
    kTRDC_MbcSlaveMemory1 = (1U << 1U), /*!< Memory 1. */
    kTRDC_MbcSlaveMemory2 = (1U << 2U), /*!< Memory 2. */
    kTRDC_MbcSlaveMemory3 = (1U << 3U), /*!< Memory 3. */
};

/*! @brief The MBC bit enumeration, used to form a mask to set/clear configured words' NSE. */
enum _trdc_MBC_bit
{
    kTRDC_MbcBit0  = (1U << 0U),  /*!< Bit 0. */
    kTRDC_MbcBit1  = (1U << 1U),  /*!< Bit 1. */
    kTRDC_MbcBit2  = (1U << 2U),  /*!< Bit 2. */
    kTRDC_MbcBit3  = (1U << 3U),  /*!< Bit 3. */
    kTRDC_MbcBit4  = (1U << 4U),  /*!< Bit 4. */
    kTRDC_MbcBit5  = (1U << 5U),  /*!< Bit 5. */
    kTRDC_MbcBit6  = (1U << 6U),  /*!< Bit 6. */
    kTRDC_MbcBit7  = (1U << 7U),  /*!< Bit 7. */
    kTRDC_MbcBit8  = (1U << 8U),  /*!< Bit 8. */
    kTRDC_MbcBit9  = (1U << 9U),  /*!< Bit 9. */
    kTRDC_MbcBit10 = (1U << 10U), /*!< Bit 10. */
    kTRDC_MbcBit11 = (1U << 11U), /*!< Bit 11. */
    kTRDC_MbcBit12 = (1U << 12U), /*!< Bit 12. */
    kTRDC_MbcBit13 = (1U << 13U), /*!< Bit 13. */
    kTRDC_MbcBit14 = (1U << 14U), /*!< Bit 14. */
    kTRDC_MbcBit15 = (1U << 15U), /*!< Bit 15. */
    kTRDC_MbcBit16 = (1U << 16U), /*!< Bit 16. */
    kTRDC_MbcBit17 = (1U << 17U), /*!< Bit 17. */
    kTRDC_MbcBit18 = (1U << 18U), /*!< Bit 18. */
    kTRDC_MbcBit19 = (1U << 19U), /*!< Bit 19. */
    kTRDC_MbcBit20 = (1U << 20U), /*!< Bit 20. */
    kTRDC_MbcBit21 = (1U << 21U), /*!< Bit 21. */
    kTRDC_MbcBit22 = (1U << 22U), /*!< Bit 22. */
    kTRDC_MbcBit23 = (1U << 23U), /*!< Bit 23. */
    kTRDC_MbcBit24 = (1U << 24U), /*!< Bit 24. */
    kTRDC_MbcBit25 = (1U << 25U), /*!< Bit 25. */
    kTRDC_MbcBit26 = (1U << 26U), /*!< Bit 26. */
    kTRDC_MbcBit27 = (1U << 27U), /*!< Bit 27. */
    kTRDC_MbcBit28 = (1U << 28U), /*!< Bit 28. */
    kTRDC_MbcBit29 = (1U << 29U), /*!< Bit 29. */
    kTRDC_MbcBit30 = (1U << 30U), /*!< Bit 30. */
    kTRDC_MbcBit31 = (1U << 31U), /*!< Bit 31. */
};

/*!
 * @brief The configuration of each memory block per domain per MBC instance.
 */
typedef struct _trdc_mbc_memory_block_config
{
    uint32_t memoryAccessControlSelect : 3U; /*!< Select one of the 8 access control policies for this memory block, for
                                                access cotrol policies see @ref trdc_memory_access_control_config_t. */
    uint32_t nseEnable : 1U;                 /*!< Enable non-secure accesses and disable secure accesses. */
    uint32_t mbcIdx : 4U;                    /*!< The index of the MBC for this configuration to take effect. */
    uint32_t domainIdx : 8U;                 /*!< The index of the domain for this configuration to take effect. */
    uint32_t slaveMemoryIdx : 8U; /*!< The index of the slave memory for this configuration to take effect. */
    uint32_t memoryBlockIdx : 8U; /*!< The index of the memory block for this configuration to take effect. */
} trdc_mbc_memory_block_config_t;
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */
/*!
 * @brief Initializes the TRDC module.
 *
 * This function enables the TRDC clock.
 *
 * @param base TRDC peripheral base address.
 */
void TRDC_Init(TRDC_Type *base);

/*!
 * @brief De-initializes the TRDC module.
 *
 * This function disables the TRDC clock.
 *
 * @param base TRDC peripheral base address.
 */
void TRDC_Deinit(TRDC_Type *base);
/*! @} */

#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/*!
 * @name Hardware configuration
 * @{
 */
/*!
 * @brief Gets the domain ID of the current bus master.
 *
 * @param base TRDC peripheral base address.
 * @return Domain ID of current bus master.
 */
static inline uint8_t TRDC_GetCurrentMasterDomainId(TRDC_Type *base)
{
    return (uint8_t)((TRDC_GENERAL_BASE(base)->TRDC_HWCFG1 & TRDC_TRDC_HWCFG1_DID_MASK) >> TRDC_TRDC_HWCFG1_DID_SHIFT);
}

/*!
 * @brief Gets the TRDC hardware configuration.
 *
 * This function gets the TRDC hardware configurations, including number of bus
 * masters, number of domains, number of MRCs and number of PACs.
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to the structure to get the configuration.
 */
void TRDC_GetHardwareConfig(TRDC_Type *base, trdc_hardware_config_t *config);
/*! @} */
#endif

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT) && FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT
/*!
 * @name Master domain assignment
 * @{
 */
/*!
 * @brief Sets the TRDC DAC(Domain Assignment Controllers) global valid.
 *
 * Once enabled, it will remain enabled until next reset.
 *
 * @param base TRDC peripheral base address.
 */
static inline void TRDC_SetDacGlobalValid(TRDC_Type *base)
{
    TRDC_GENERAL_BASE(base)->TRDC_CR |= TRDC_TRDC_CR_GVLDM_MASK;
}

/*!
 * @brief Locks the bus master domain assignment register.
 *
 * This function locks the master domain assignment. After it is locked, the register can't be changed
 * until next reset.
 *
 * @param base TRDC peripheral base address.
 * @param master Which master to configure, refer to trdcx_master_t in processor header file, x is trdc instance.
 * @param regNum Which register to configure, processor master can have more than one register for the MDAC
   configuration.
 * @param assignIndex Which assignment register to lock.
 */
static inline void TRDC_LockMasterDomainAssignment(TRDC_Type *base, uint8_t master, uint8_t regNum)
{
    /* Make sure in the master range. */
    assert((uint32_t)master <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMSTR_MASK) >> TRDC_TRDC_HWCFG0_NMSTR_SHIFT));
    if (0U == (TRDC_GENERAL_BASE(base)->DACFG[master] & TRDC_DACFG_NCM_MASK))
    {
        TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT0[master].MDA_W_DFMT0[regNum] |= TRDC_MDA_W_DFMT0_LK1_MASK;
    }
    else
    {
        TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT1[master].MDA_W_DFMT1[0] |= TRDC_MDA_W_DFMT1_LK1_MASK;
    }
}

/*!
 * @brief Sets the master domain assignment as valid or invalid.
 *
 * This function sets the master domain assignment as valid or invalid.
 *
 * @param base TRDC peripheral base address.
 * @param master Which master to configure.
 * @param regNum Which register to configure, processor master can have more than one register for the MDAC
 * configuration.
 * @param assignIndex Index for the domain assignment register.
 * @param valid True to set valid, false to set invalid.
 */
static inline void TRDC_SetMasterDomainAssignmentValid(TRDC_Type *base, uint8_t master, uint8_t regNum, bool valid)
{
    /* Make sure in the master range. */
    assert((uint32_t)master <
           ((TRDC_GENERAL_BASE(base)->TRDC_HWCFG0 & TRDC_TRDC_HWCFG0_NMSTR_MASK) >> TRDC_TRDC_HWCFG0_NMSTR_SHIFT));
    if (valid)
    {
        if (0U == (TRDC_GENERAL_BASE(base)->DACFG[master] & TRDC_DACFG_NCM_MASK))
        {
            TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT0[master].MDA_W_DFMT0[regNum] |= TRDC_MDA_W_DFMT0_VLD_MASK;
        }
        else
        {
            TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT1[master].MDA_W_DFMT1[0] |= TRDC_MDA_W_DFMT1_VLD_MASK;
        }
    }
    else
    {
        if (0U == (TRDC_GENERAL_BASE(base)->DACFG[master] & TRDC_DACFG_NCM_MASK))
        {
            TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT0[master].MDA_W_DFMT0[regNum] &= ~TRDC_MDA_W_DFMT0_VLD_MASK;
        }
        else
        {
            TRDC_DOMAIN_ASSIGNMENT_BASE(base)->MDA_DFMT1[master].MDA_W_DFMT1[0] &= ~TRDC_MDA_W_DFMT1_VLD_MASK;
        }
    }
}

/*!
 * @brief Gets the default master domain assignment for the processor bus master.
 *
 * This function gets the default master domain assignment for the processor bus master.
 * It should only be used for the processor bus masters, such as CORE0. This function
 * sets the assignment as follows:
 *
 * @code
 * assignment->domainId           = 0U;
 * assignment->domainIdSelect     = kTRDC_DidMda;
 * assignment->lock               = 0U;
 * @endcode
 *
 * @param domainAssignment Pointer to the assignment structure.
 */
void TRDC_GetDefaultProcessorDomainAssignment(trdc_processor_domain_assignment_t *domainAssignment);

/*!
 * @brief Gets the default master domain assignment for non-processor bus master.
 *
 * This function gets the default master domain assignment for non-processor bus master.
 * It should only be used for the non-processor bus masters, such as DMA. This function
 * sets the assignment as follows:
 *
 * @code
 * assignment->domainId            = 0U;
 * assignment->privilegeAttr       = kTRDC_ForceUser;
 * assignment->secureAttr       = kTRDC_ForceSecure;
 * assignment->bypassDomainId      = 0U;
 * assignment->lock                = 0U;
 * @endcode
 *
 * @param domainAssignment Pointer to the assignment structure.
 */
void TRDC_GetDefaultNonProcessorDomainAssignment(trdc_non_processor_domain_assignment_t *domainAssignment);

/*!
 * @brief Sets the processor bus master domain assignment.
 *
 * This function sets the processor master domain assignment as valid.
 * One bus master might have multiple domain assignment registers. The parameter
 * \p assignIndex specifies which assignment register to set.
 *
 * Example: Set domain assignment for core 0.
 *
 * @code
 * trdc_processor_domain_assignment_t processorAssignment;
 *
 * TRDC_GetDefaultProcessorDomainAssignment(&processorAssignment);
 *
 * processorAssignment.domainId = 0;
 * processorAssignment.xxx      = xxx;
 * TRDC_SetMasterDomainAssignment(TRDC, &processorAssignment);
 * @endcode
 *
 * @param base TRDC peripheral base address.
 * @param master Which master to configure, refer to trdc_master_t in processor header file.
 * @param regNum Which register to configure, processor master can have more than one register for the MDAC
 * configuration.
 * @param domainAssignment Pointer to the assignment structure.
 */
void TRDC_SetProcessorDomainAssignment(TRDC_Type *base,
                                       uint8_t master,
                                       uint8_t regNum,
                                       const trdc_processor_domain_assignment_t *domainAssignment);

/*!
 * @brief Sets the non-processor bus master domain assignment.
 *
 * This function sets the non-processor master domain assignment as valid.
 * One bus master might have multiple domain assignment registers. The parameter
 * \p assignIndex specifies which assignment register to set.
 *
 * Example: Set domain assignment for DMA0.
 * @code
 * trdc_non_processor_domain_assignment_t nonProcessorAssignment;
 *
 * TRDC_GetDefaultNonProcessorDomainAssignment(&nonProcessorAssignment);
 * nonProcessorAssignment.domainId = 1;
 * nonProcessorAssignment.xxx      = xxx;
 *
 * TRDC_SetMasterDomainAssignment(TRDC, kTrdcMasterDma0, 0U, &nonProcessorAssignment);
 * @endcode
 *
 * @param base TRDC peripheral base address.
 * @param master Which master to configure, refer to trdc_master_t in processor header file.
 * @param domainAssignment Pointer to the assignment structure.
 */
void TRDC_SetNonProcessorDomainAssignment(TRDC_Type *base,
                                          uint8_t master,
                                          const trdc_non_processor_domain_assignment_t *domainAssignment);

/*!
 * @brief Gets the bit map of the bus master(s) that is(are) sourcing a PID register.
 *
 * This function sets the non-processor master domain assignment as valid.
 *
 * @param base TRDC peripheral base address.
 * @return the bit map of the master(s). Bit 1 sets indicates bus master 1.
 */
static inline uint64_t TRDC_GetActiveMasterPidMap(TRDC_Type *base)
{
    return ((uint64_t)TRDC_GENERAL_BASE(base)->TRDC_HWCFG3 << 32U) | (uint64_t)TRDC_GENERAL_BASE(base)->TRDC_HWCFG2;
}

/*!
 * @brief Sets the current Process identifier(PID) for processor core.
 *
 * Each processor has a corresponding process identifier (PID) which can be used to group tasks into different domains.
 * Secure privileged software saves and restores the PID as part of any context switch.
 * This data structure defines an array of 32-bit values, one per MDA module, that define the PID. Since this register
 * resource is only applicable to processor cores, the data structure is typically sparsely populated. The HWCFG[2-3]
 * registers provide a bitmap of the implemented PIDn registers. This data structure is indexed using the corresponding
 * MDA instance number. Depending on the operating clock domain of each DAC instance, there may be optional information
 * stored in the corresponding PIDm register to properly implement the LK2 = 2 functionality.
 *
 * @param base TRDC peripheral base address.
 * @param master Which processor master to configure, refer to trdc_master_t in processor header file.
 * @param pidConfig Pointer to the configuration structure.
 */
void TRDC_SetPid(TRDC_Type *base, uint8_t master, const trdc_pid_config_t *pidConfig);
/*! @} */
#endif

#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/*!
 * @name TZ-M congiguration
 * @{
 */
/*!
 * @brief Gets the default IDAU(Implementation-Defined Attribution Unit) configuration.
 *
 * @code
 * config->lockSecureVTOR    = false;
 * config->lockNonsecureVTOR = false;
 * config->lockSecureMPU     = false;
 * config->lockNonsecureMPU  = false;
 * config->lockSAU           = false;
 * @endcode
 *
 * @param domainAssignment Pointer to the configuration structure.
 */
void TRDC_GetDefaultIDAUConfig(trdc_idau_config_t *idauConfiguration);

/*!
 * @brief Sets the IDAU(Implementation-Defined Attribution Unit) control configuration.
 *
 * Example: Lock the secure and non-secure MPU registers.
 *
 * @code
 * trdc_idau_config_t idauConfiguration;
 *
 * TRDC_GetDefaultIDAUConfig(&idauConfiguration);
 *
 * idauConfiguration.lockSecureMPU = true;
 * idauConfiguration.lockNonsecureMPU      = true;
 * TRDC_SetIDAU(TRDC, &idauConfiguration);
 * @endcode
 *
 * @param base TRDC peripheral base address.
 * @param domainAssignment Pointer to the configuration structure.
 */
void TRDC_SetIDAU(TRDC_Type *base, const trdc_idau_config_t *idauConfiguration);
/*! @} */
#endif

#if defined(FSL_FEATURE_TRDC_HAS_FLW) && FSL_FEATURE_TRDC_HAS_FLW
/*!
 * @name FLW(Flash Logical Window) configuration
 * @{
 */
/*!
 * @brief Enables/disables the FLW(flash logical window) function.
 *
 * @param base TRDC peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void TRDC_EnableFlashLogicalWindow(TRDC_Type *base, bool enable)
{
    if (enable)
    {
        TRDC_FLW_BASE(base)->TRDC_FLW_CTL |= TRDC_TRDC_FLW_CTL_V_MASK;
    }
    else
    {
        TRDC_FLW_BASE(base)->TRDC_FLW_CTL &= ~TRDC_TRDC_FLW_CTL_V_MASK;
    }
}

/*!
 * @brief Locks FLW registers. Once locked the registers can noy be updated until next reset.
 *
 * @param base TRDC peripheral base address.
 */
static inline void TRDC_LockFlashLogicalWindow(TRDC_Type *base)
{
    TRDC_FLW_BASE(base)->TRDC_FLW_CTL |= TRDC_TRDC_FLW_CTL_LK_MASK;
}

/*!
 * @brief Gets the FLW physical base address.
 *
 * @param base TRDC peripheral base address.
 * @return Physical address of the FLW function.
 */
static inline uint32_t TRDC_GetFlashLogicalWindowPbase(TRDC_Type *base)
{
    return TRDC_FLW_BASE(base)->TRDC_FLW_PBASE;
}

/*!
 * @brief Sets the FLW size.
 *
 * @param base TRDC peripheral base address.
 * @param size Size of the FLW in unit of 32k bytes.
 */
static inline void TRDC_GetSetFlashLogicalWindowSize(TRDC_Type *base, uint16_t size)
{
    TRDC_FLW_BASE(base)->TRDC_FLW_BCNT = size;
}

/*!
 * @brief Gets the default FLW(Flsh Logical Window) configuration.
 *
 * @code
 * config->blockCount    = false;
 * config->arrayBaseAddr = false;
 * config->lock     = false;
 * config->enable  = false;
 * @endcode
 *
 * @param flwConfiguration Pointer to the configuration structure.
 */
void TRDC_GetDefaultFlashLogicalWindowConfig(trdc_flw_config_t *flwConfiguration);

/*!
 * @brief Sets the FLW function's configuration.
 *
 * @code
 * trdc_flw_config_t flwConfiguration;
 *
 * TRDC_GetDefaultIDAUConfig(&flwConfiguration);
 *
 * flwConfiguration.blockCount = 32U;
 * flwConfiguration.arrayBaseAddr = 0xXXXXXXXX;
 * TRDC_SetIDAU(TRDC, &flwConfiguration);
 * @endcode
 *
 * @param base TRDC peripheral base address.
 * @param flwConfiguration Pointer to the configuration structure.
 */
void TRDC_SetFlashLogicalWindow(TRDC_Type *base, const trdc_flw_config_t *flwConfiguration);
/*! @} */
#endif

#if defined(FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR) && FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR
/*!
 * @name Domain error check and clear
 * @{
 */
/*!
 * @brief Gets and clears the first domain error of the current domain.
 *
 * This function gets the first access violation information for the current domain
 * and clears the pending flag. There might be multiple access violations pending
 * for the current domain. This function only processes the first error.
 *
 * @param base TRDC peripheral base address.
 * @param error Pointer to the error information.
 * @return If the access violation is captured, this function returns the kStatus_Success.
 *         The error information can be obtained from the parameter error. If no
 *         access violation is captured, this function returns the kStatus_NoData.
 */
status_t TRDC_GetAndClearFirstDomainError(TRDC_Type *base, trdc_domain_error_t *error);

/*!
 * @brief Gets and clears the first domain error of the specific domain.
 *
 * This function gets the first access violation information for the specific domain
 * and clears the pending flag. There might be multiple access violations pending
 * for the current domain. This function only processes the first error.
 *
 * @param base TRDC peripheral base address.
 * @param error Pointer to the error information.
 * @param domainId The error of which domain to get and clear.
 * @return If the access violation is captured, this function returns the kStatus_Success.
 *         The error information can be obtained from the parameter error. If no
 *         access violation is captured, this function returns the kStatus_NoData.
 */
status_t TRDC_GetAndClearFirstSpecificDomainError(TRDC_Type *base, trdc_domain_error_t *error, uint8_t domainId);
/*! @} */
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MRC) && FSL_FEATURE_TRDC_HAS_MRC
/*!
 * @name MRC configuration
 * @{
 */
#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/*!
 * @brief Sets the TRDC MRC(Memory Region Checkers) global valid.
 *
 * Once enabled, it will remain enabled until next reset.
 *
 * @param base TRDC peripheral base address.
 */
static inline void TRDC_SetMrcGlobalValid(TRDC_Type *base)
{
    TRDC_GENERAL_BASE(base)->TRDC_CR |= TRDC_TRDC_CR_GVLDR_MASK;
}
#endif

/*!
 * @brief Gets the TRDC MRC(Memory Region Checkers) region number valid.
 *
 * @param base TRDC peripheral base address.
 * @return the region number of the given MRC instance
 */
static inline uint8_t TRDC_GetMrcRegionNumber(TRDC_Type *base, uint8_t mrcIdx)
{
    return (uint8_t)((TRDC_MRC_BASE(base, mrcIdx)->MRC_GLBCFG & TRDC_MRC_GLBCFG_NRGNS_MASK) >>
                     TRDC_MRC_GLBCFG_NRGNS_SHIFT);
}

/*!
 * @brief Sets the memory access configuration for one of the access control register of one MRC.
 *
 * Example: Enable the secure operations and lock the configuration for MRC0 region 1.
 *
 * @code
 * trdc_memory_access_control_config_t config;
 *
 * config.securePrivX = true;
 * config.securePrivW = true;
 * config.securePrivR = true;
 * config.lock = true;
 * TRDC_SetMrcMemoryAccess(TRDC, &config, 0, 1);
 * @endcode
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to the configuration structure.
 * @param mrcIdx MRC index.
 * @param regIdx Register number.
 */
void TRDC_MrcSetMemoryAccessConfig(TRDC_Type *base,
                                   const trdc_memory_access_control_config_t *config,
                                   uint8_t mrcIdx,
                                   uint8_t regIdx);

/*!
 * @brief Enables the update of the selected domians.
 *
 * After the domians' update are enabled, their regions' NSE bits can be set or clear.
 *
 * @param base TRDC peripheral base address.
 * @param mrcIdx MRC index.
 * @param domianMask Bit mask of the domains to be enabled.
 * @param enable True to enable, false to disable.
 */
void TRDC_MrcEnableDomainNseUpdate(TRDC_Type *base, uint8_t mrcIdx, uint16_t domianMask, bool enable);

/*!
 * @brief Sets the NSE bits of the selected regions for domains.
 *
 * This function sets the NSE bits for the selected regions for the domains whose update are enabled.
 *
 * @param base TRDC peripheral base address.
 * @param mrcIdx MRC index.
 * @param regionMask Bit mask of the regions whose NSE bits to set.
 */
void TRDC_MrcRegionNseSet(TRDC_Type *base, uint8_t mrcIdx, uint16_t regionMask);

/*!
 * @brief Clears the NSE bits of the selected regions for domains.
 *
 * This function clears the NSE bits for the selected regions for the domains whose update are enabled.
 *
 * @param base TRDC peripheral base address.
 * @param mrcIdx MRC index.
 * @param regionMask Bit mask of the regions whose NSE bits to clear.
 */
void TRDC_MrcRegionNseClear(TRDC_Type *base, uint8_t mrcIdx, uint16_t regionMask);

/*!
 * @brief Clears the NSE bits for all the regions of the selected domains.
 *
 * This function clears the NSE bits for all regions of selected domains whose update are enabled.
 *
 * @param base TRDC peripheral base address.
 * @param mrcIdx MRC index.
 * @param domainMask Bit mask of the domians whose NSE bits to clear.
 */
void TRDC_MrcDomainNseClear(TRDC_Type *base, uint8_t mrcIdx, uint16_t domainMask);

/*!
 * @brief Sets the configuration for one of the region descriptor per domain per MRC instnce.
 *
 * This function sets the configuration for one of the region descriptor, including the start
 * and end address of the region, memory access control policy and valid.
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to region descriptor configuration structure.
 */
void TRDC_MrcSetRegionDescriptorConfig(TRDC_Type *base, const trdc_mrc_region_descriptor_config_t *config);
/*! @} */
#endif

#if defined(FSL_FEATURE_TRDC_HAS_MBC) && FSL_FEATURE_TRDC_HAS_MBC
/*!
 * @name MBC configuration
 * @{
 */
#if defined(FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG) && FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG
/*!
 * @brief Sets the TRDC MBC(Memory Block Checkers) global valid.
 *
 * Once enabled, it will remain enabled until next reset.
 *
 * @param base TRDC peripheral base address.
 */
static inline void TRDC_SetMbcGlobalValid(TRDC_Type *base)
{
    TRDC_GENERAL_BASE(base)->TRDC_CR |= TRDC_TRDC_CR_GVLDB_MASK;
}
#endif

/*!
 * @brief Gets the hardware configuration of the one of two slave memories within each MBC(memory block checker).
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to the structure to get the configuration.
 * @param mbcIdx MBC number.
 * @param slvIdx Slave number.
 */
void TRDC_GetMbcHardwareConfig(TRDC_Type *base,
                               trdc_slave_memory_hardware_config_t *config,
                               uint8_t mbcIdx,
                               uint8_t slvIdx);

/*!
 * @brief Sets the NSR update configuration for one of the MBC instance.
 *
 * After set the NSE configuration, the configured memory area can be updateby NSE set/clear.
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to NSE update configuration structure.
 * @param mbcIdx MBC index.
 */
void TRDC_MbcSetNseUpdateConfig(TRDC_Type *base, const trdc_mbc_nse_update_config_t *config, uint8_t mbcIdx);

/*!
 * @brief Sets the NSE bits of the selected configuration words according to NSE update configuration.
 *
 * This function sets the NSE bits of the word for the configured regio, memory.
 *
 * @param base TRDC peripheral base address.
 * @param mbcIdx MBC index.
 * @param bitMask Mask of the bits whose NSE bits to set.
 */
void TRDC_MbcWordNseSet(TRDC_Type *base, uint8_t mbcIdx, uint32_t bitMask);

/*!
 * @brief Clears the NSE bits of the selected configuration words according to NSE update configuration.
 *
 * This function sets the NSE bits of the word for the configured regio, memory.
 *
 * @param base TRDC peripheral base address.
 * @param mbcIdx MBC index.
 * @param bitMask Mask of the bits whose NSE bits to clear.
 */
void TRDC_MbcWordNseClear(TRDC_Type *base, uint8_t mbcIdx, uint32_t bitMask);

/*!
 * @brief Clears all configuration words' NSE bits of the selected domain and memory.
 *
 * @param base TRDC peripheral base address.
 * @param mbcIdx MBC index.
 * @param domainMask Mask of the domains whose NSE bits to clear, 0b110 means clear domain 1&2.
 * @param slaveMask Mask of the slaves whose NSE bits to clear, 0x11 means clear all slave 0&1's NSE bits.
 */
void TRDC_MbcNseClearAll(TRDC_Type *base, uint8_t mbcIdx, uint16_t domainMask, uint8_t slave);

/*!
 * @brief Sets the memory access configuration for one of the region descriptor of one MBC.
 *
 * Example: Enable the secure operations and lock the configuration for MRC0 region 1.
 *
 * @code
 * trdc_memory_access_control_config_t config;
 *
 * config.securePrivX = true;
 * config.securePrivW = true;
 * config.securePrivR = true;
 * config.lock = true;
 * TRDC_SetMbcMemoryAccess(TRDC, &config, 0, 1);
 * @endcode
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to the configuration structure.
 * @param mbcIdx MBC index.
 * @param rgdIdx Region descriptor number.
 */
void TRDC_MbcSetMemoryAccessConfig(TRDC_Type *base,
                                   const trdc_memory_access_control_config_t *config,
                                   uint8_t mbcIdx,
                                   uint8_t rgdIdx);

/*!
 * @brief Sets the configuration for one of the memory block per domain per MBC instnce.
 *
 * This function sets the configuration for one of the memory block, including the memory access
 * control policy and nse enable.
 *
 * @param base TRDC peripheral base address.
 * @param config Pointer to memory block configuration structure.
 */
void TRDC_MbcSetMemoryBlockConfig(TRDC_Type *base, const trdc_mbc_memory_block_config_t *config);
/*! @} */
#endif

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_TRDC_H_ */
