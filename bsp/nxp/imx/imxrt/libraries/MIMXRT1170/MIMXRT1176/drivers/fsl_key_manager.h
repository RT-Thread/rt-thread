/*
 * Copyright 2020-2021, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_KEYMGR_H_
#define _FSL_KEYMGR_H_

#include "fsl_common.h"

/*!
 * @addtogroup key_manager
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Key Manager driver version. Version 2.0.2.
 *
 * Current version: 2.0.2
 *
 * Change log:
 *
 * - Version 2.0.2
 *   - Fix MISRA-2012 issues
 *
 * - Version 2.0.1
 *   - Fix MISRA-2012 issues
 *
 * - Version 2.0.0
 *   - Initial version
 */
#define FSL_KEYMGR_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

typedef enum _keymgr_lock
{
    kKEYMGR_Unlock = 0u,
    kKEYMGR_Lock   = 1u,
} keymgr_lock_t;

typedef enum _keymgr_allow
{
    kKEYMGR_Disallow = 0u,
    kKEYMGR_Allow    = 1u,
} keymgr_allow_t;

typedef enum _keymgr_slot
{
    kKEYMGR_Slot0 = 0u,
    kKEYMGR_Slot1 = 1u,
    kKEYMGR_Slot2 = 2u,
    kKEYMGR_Slot3 = 3u,
    kKEYMGR_Slot4 = 4u,
} keymgr_slot_t;

#define KEYMGR_IEE_RELOAD 1u
#define KEYMGR_SEL_OCOTP  0u
#define KEYMGR_SEL_UDF    0u
#define KEYMGR_SEL_PUF    1u

#define keymgr_select_t uint8_t

/*! @brief Key Manager slot configuration structure. */
typedef struct _domain_slot_config
{
    keymgr_lock_t lockControl;     /*!< Lock control register of slot. */
    keymgr_allow_t allowUser;      /*!< Allow user write access to domain control register or domain register. */
    keymgr_allow_t allowNonSecure; /*!< Allow non-secure write access to domain control register or domain register. */
    keymgr_lock_t lockList;        /*!< Lock whitelist. SLOTx_CTRL[WHITE_LIST] cannot be changed. */
    uint8_t whiteList;             /*!< Domains that on the Whitelist can change given slot. */
    /*!< Each field represents one domain. Bit0~Bit3 represent DOMAIN0~DOMAIN3 respectively. */
} domain_slot_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Configures Master key settings.
 *
 * This function configures Key Manager's setting for Master key.
 *
 * @param base Key Manager peripheral address.
 * @param select select source for Master key.
 * @param lock setting for lock Master key.
 * @return  status of Master key control operation
 */
status_t KEYMGR_MasterKeyControll(KEY_MANAGER_Type *base, keymgr_select_t select, keymgr_lock_t lock);

/*!
 * @brief Configures OTFAD1 key settings.
 *
 * This function configures Key Manager's setting for OTFAD1 key.
 *
 * @param base Key Manager peripheral address.
 * @param select select source for OTFAD1 key.
 * @param lock setting for lock OTFAD1 key.
 * @return  status of OTFAD1 key control operation
 */
status_t KEYMGR_OTFAD1KeyControll(KEY_MANAGER_Type *base, keymgr_select_t select, keymgr_lock_t lock);

/*!
 * @brief Configures OTFAD2 key settings.
 *
 * This function configures Key Manager's setting for OTFAD2 key.
 *
 * @param base Key Manager peripheral address.
 * @param select select source for OTFAD2 key.
 * @param lock setting for lock OTFAD2 key.
 * @return  status of OTFAD2 key control operation
 */
status_t KEYMGR_OTFAD2KeyControll(KEY_MANAGER_Type *base, keymgr_select_t select, keymgr_lock_t lock);

/*!
 * @brief Restart load key signal for IEE.
 *
 * This function genrates Key Manager's restart signal for IEE key.
 *
 * @param base Key Manager peripheral address.
 */
void KEYMGR_IEEKeyReload(KEY_MANAGER_Type *base);

/*!
 * @brief Lock the key select from PUF.
 *
 * This function locks selection of key for PUF.
 *
 * @param base Key Manager peripheral address.
 * @param lock Setting for selection of key for PUF.
 */
void KEYMGR_PUFKeyLock(KEY_MANAGER_Type *base, keymgr_lock_t lock);

/*!
 * @brief Configures Slot Domain control.
 *
 * This function configures domain slot control which locks and allows writes.
 *
 * @param base Key Manager peripheral address.
 * @param config Pointer to slot configuration structure.
 * @param slot Select slot to be configured.
 * @return  status of slot control operation
 */
status_t KEYMGR_SlotControl(KEY_MANAGER_Type *base, domain_slot_config_t *config, keymgr_slot_t slot);

/*!
 * @brief Resets Key Manager module to factory default values.
 *
 * This function performs hardware reset of Key Manager module.
 *
 * @param base Key Manager peripheral address.
 */
void KEYMGR_Init(KEY_MANAGER_Type *base);

/*!
 * @brief Sets the default configuration of Key manager slot.
 *
 * This function initialize Key Manager slot config structure to default values.
 *
 * @param config Pointer to slot configuration structure.
 */
status_t KEYMGR_GetDefaultConfig(domain_slot_config_t *config);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* _FSL_IEE_H_ */
