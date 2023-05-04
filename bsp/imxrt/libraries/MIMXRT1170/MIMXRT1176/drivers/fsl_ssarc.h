/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SSARC_H_
#define _FSL_SSARC_H_

#include "fsl_common.h"

/*!
 * @addtogroup ssarc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SSARC driver version 2.1.0. */
#define FSL_SSARC_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

#define SSARC_INT_STATUS_ALL                                                                                       \
    (SSARC_LP_INT_STATUS_ADDR_ERR_MASK | SSARC_LP_INT_STATUS_AHB_ERR_MASK | SSARC_LP_INT_STATUS_SW_REQ_DONE_MASK | \
     SSARC_LP_INT_STATUS_TIMEOUT_MASK | SSARC_LP_INT_STATUS_GROUP_CONFLICT_MASK)

/*!
 * @brief The enumeration of ssarc status flags.
 */
enum _ssarc_interrupt_status_flags
{
    kSSARC_AddressErrorFlag = SSARC_LP_INT_STATUS_ADDR_ERR_MASK, /*!< If the descriptor is not in the range,
                                                                        assert address error. */
    kSSARC_AHBErrorFlag = SSARC_LP_INT_STATUS_AHB_ERR_MASK,      /*!< If any AHB master access receives none-OKAY,
                                                                             assert AHB error. */
    kSSARC_SoftwareRequestDoneFlag = SSARC_LP_INT_STATUS_SW_REQ_DONE_MASK, /*!< If a software triggered save or restore
                                                                                process is completed, assert sofware
                                                                                request done . */
    kSSARC_TimeoutFlag = SSARC_LP_INT_STATUS_TIMEOUT_MASK,              /*!< If processing of a group has exceeded the
                                                                            timeout value, assert timeout. */
    kSSARC_GroupConflictFlag = SSARC_LP_INT_STATUS_GROUP_CONFLICT_MASK, /*!< Group conflict. */
};

/*!
 * @brief The size of the register to be saved/restored.
 */
typedef enum _ssarc_descriptor_register_size
{
    kSSARC_DescriptorRegister8bitWidth  = 0x0U, /*!< The register to be saved/restored is 8 bit width. */
    kSSARC_DescriptorRegister16bitWidth = 0x1U, /*!< The register to be saved/restored is 16 bit width. */
    kSSARC_DescriptorRegister32bitWidth = 0x2U, /*!< The register to be saved/restored is 32 bit width. */
} ssarc_descriptor_register_size_t;

/*!
 * @brief The operation of the descriptor.
 */
typedef enum _ssarc_descriptor_operation
{
    kSSARC_SaveDisableRestoreDisable = 0x0U, /*!< Disable Save operation, disable restore operation. */
    kSSARC_SaveEnableRestoreDisable  = SSARC_HP_SRAM2_SV_EN_MASK, /*!< Enable Save operation,
                                                                       disable restore operation. */
    kSSARC_SaveDisableRestoreEnable = SSARC_HP_SRAM2_RT_EN_MASK,  /*!< Disable Save operation,
                                                                       enable restore operation. */
    kSSARC_SaveEnableRestoreEnable = (SSARC_HP_SRAM2_RT_EN_MASK | SSARC_HP_SRAM2_SV_EN_MASK),
    /*!< Enable Save operation, enable restore operation. */
} ssarc_descriptor_operation_t;

/*!
 * @brief The type of operation.
 */
typedef enum _ssarc_descriptor_type
{
    kSSARC_ReadValueWriteBack = 0x00U, /*!< Read the register value on save operation
                                            and write it back on restore operation */
    kSSARC_WriteFixedValue = 0x01U,    /*!< Always write a fixed value from DATA[31:0] */
    kSSARC_RMWOr           = 0x02U,    /*!< Read register, OR with the DATA[31:0], and write it back */
    kSSARC_RMWAnd          = 0x03U,    /*!< Read register, AND with the DATA[31:0], and write it back */
    kSSARC_DelayCycles     = 0x04U,    /*!< Delay for number of cycles based on the DATA[31:0] */
    kSSARC_Polling0        = 0x05U,    /*!< Read the register until read_data[31:0] & DATA[31:0] == 0 */
    kSSARC_Polling1        = 0x06U,    /*!< Read the register until read_data[31:0] & DATA[31:0] != 0 */
} ssarc_descriptor_type_t;

/*!
 * @brief The order of the restore/save operation.
 */
typedef enum _ssarc_save_restore_order
{
    kSSARC_ProcessFromStartToEnd = 0U, /*!< Descriptors within the group are processed from start to end. */
    kSSARC_ProcessFromEndToStart = 1U, /*!< Descriptors within the group are processed from end to start. */
} ssarc_save_restore_order_t;

/*!
 * @brief Software trigger mode.
 */
typedef enum _ssarc_software_trigger_mode
{
    kSSARC_TriggerSaveRequest = SSARC_LP_DESC_CTRL1_SW_TRIG_SV_MASK, /*!< Don't trigger restore operation, trigger the
                                                                          save operation by software. */
    kSSARC_TriggerRestoreRequest = SSARC_LP_DESC_CTRL1_SW_TRIG_RT_MASK, /*!< Trigger the restore operation, don't
                                                                          trigger the save operation. */
} ssarc_software_trigger_mode_t;

/*!
 * @brief The configuration of descriptor.
 */
typedef struct _ssarc_descriptor_config
{
    uint32_t address; /*!< The address of the register/memory to be saved/restored. */
    uint32_t data;    /*!< The value of the register/memory to be saved/restored, please note that if the type
                          is selected as kSSARC_ReadValueWriteBack, this data field is useless.  */
    ssarc_descriptor_register_size_t size;  /*!< The size of register to be saved/restored. */
    ssarc_descriptor_operation_t operation; /*!< The operation mode of descriptor. */
    ssarc_descriptor_type_t type;           /*!< The type of operation. */
} ssarc_descriptor_config_t;

/*!
 * @brief The configuration of the group.
 */
typedef struct _ssarc_group_config
{
    ssarc_cpu_domain_name_t cpuDomain;       /*!< CPU domain, define the ownership of this group. */
    uint32_t startIndex;                     /*!< The index of the first descriptor of the group. */
    uint32_t endIndex;                       /*!< The index of the last descriptor of the group. */
    ssarc_save_restore_order_t restoreOrder; /*!< The restore order. */
    ssarc_save_restore_order_t saveOrder;    /*!< The save order. */
    uint8_t restorePriority;                 /*!< Restore priority of current group.
                                                  0 is the highest priority, 15 is the lowest priority */
    uint8_t savePriority;                    /*!< Save priority of current group.
                                                0 is the highest priority, 15 is the lowest priority. */
    ssarc_power_domain_name_t powerDomain;   /*!< Power domain. */
    uint32_t highestAddress; /*!< Highest address that can be accessed for the descriptors in the group. */
    uint32_t lowestAddress;  /*!< Lowest address that can be accessed for the descriptors in the group. */
} ssarc_group_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Descriptor related APIs.
 * @{
 */

/*!
 * @brief Gets the address of the register to be saved/restored.
 *
 * @param base SSARC_HP peripheral base address.
 * @param index The index of descriptor. Range from 0 to 1023.
 * @return The address of the register.
 */
static inline uint32_t SSARC_GetDescriptorRegisterAddress(SSARC_HP_Type *base, uint32_t index)
{
    assert(index < SSARC_HP_SRAM0_COUNT);

    return (base->DESC[index].SRAM0);
}

/*!
 * @brief Gets the value of the register to be saved/restored.
 *
 * @param base SSARC_HP peripheral base address.
 * @param index The index of descriptor. Range from 0 to 1023.
 * @return The value of the register.
 */
static inline uint32_t SSARC_GetDescriptorRegisterData(SSARC_HP_Type *base, uint32_t index)
{
    assert(index < SSARC_HP_SRAM0_COUNT);

    return (base->DESC[index].SRAM1);
}

/*!
 * @brief Sets the configuration of the descriptor.
 *
 * @param base SSARC_HP peripheral base address.
 * @param index The index of descriptor. Range from 0 to 1023.
 * @param config Pointer to the structure ssarc_descriptor_config_t. Please refer to @ref ssarc_descriptor_config_t for
 *               details.
 */
void SSARC_SetDescriptorConfig(SSARC_HP_Type *base, uint32_t index, const ssarc_descriptor_config_t *config);

/*!
 * @}
 */

/*!
 * @name Group Related APIs
 * @{
 */

/*!
 * @brief Inits the selected group.
 *
 * @note For the groups with the same save priority or restore priority,
 *       the save/restore operation runs in the group order.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 * @param config Pointer to the structure ssarc_group_config_t. Please refer to @ref ssarc_group_config_t for details.
 */
void SSARC_GroupInit(SSARC_LP_Type *base, uint8_t groupID, const ssarc_group_config_t *config);

/*!
 * @brief De-inits the selected group.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 */
static inline void SSARC_GroupDeinit(SSARC_LP_Type *base, uint8_t groupID)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    base->GROUPS[groupID].DESC_CTRL1 &= ~SSARC_LP_DESC_CTRL1_GP_EN_MASK;
}

/*!
 * @brief Locks the configuration of the domain.
 *
 * This function locks the configuration of the domain. Once locked, only the access from the same domain is allowed,
 * access from other domains will be blocked. Once locked, it can only be unlocked by a hardware reset.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 */
static inline void SSARC_LockGroupDomain(SSARC_LP_Type *base, uint8_t groupID)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    base->GROUPS[groupID].DESC_CTRL1 |= SSARC_LP_DESC_CTRL1_DL_MASK;
}

/*!
 * @brief Locks the write access to the control registers and descriptors for the selected group.
 *
 * This function Locks the write access to the control registers and descriptors for the selected group.
 * All writes are blocked. Once locked, it can only be unlocked by a hardware reset.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 */
static inline void SSARC_LockGroupWrite(SSARC_LP_Type *base, uint8_t groupID)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    base->GROUPS[groupID].DESC_CTRL1 |= SSARC_LP_DESC_CTRL1_WL_MASK;
}

/*!
 * @brief Locks the read access to the control registers and descriptors for the selected group.
 *
 * This function Locks the read access to the control registers and descriptors for the selected group.
 * All reads are blocked. Once locked, it can only be unlocked by a hardware reset.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 */
static inline void SSARC_LockGroupRead(SSARC_LP_Type *base, uint8_t groupID)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    base->GROUPS[groupID].DESC_CTRL1 |= SSARC_LP_DESC_CTRL1_RL_MASK;
}

/*!
 * @brief Triggers software request.
 *
 * @note Each group allows software to trigger the save/restore operation without getting the request
 *       from basic power controller.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 * @param mode Software trigger mode. Please refer to @ref ssarc_software_trigger_mode_t for details.
 */
void SSARC_TriggerSoftwareRequest(SSARC_LP_Type *base, uint8_t groupID, ssarc_software_trigger_mode_t mode);

/*!
 * @}
 */

/*!
 * @name Global Setting Related APIs
 */

/*!
 * @brief Resets the whole SSARC block by software.
 *
 * @note Only reset the SSARC registers, not include the DESC in SRAM.
 *
 * @param base SSARC_LP peripheral base address.
 */
static inline void SSARC_ResetWholeBlock(SSARC_LP_Type *base)
{
    base->CTRL |= SSARC_LP_CTRL_SW_RESET_MASK;
    base->CTRL &= ~SSARC_LP_CTRL_SW_RESET_MASK;
}

/*!
 * @brief Enables/Disables save/restore request from the PGMC module.
 *
 * @param base SSARC_LP peripheral base address.
 * @param enable Used to enable/disable save/restore hardware request.
 *             - \b true Enable GPC save/restore requests.
 *             - \b false Disable GPC save/restore requests.
 */
static inline void SSARC_EnableHardwareRequest(SSARC_LP_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL &= ~SSARC_LP_CTRL_DIS_HW_REQ_MASK;
    }
    else
    {
        base->CTRL |= SSARC_LP_CTRL_DIS_HW_REQ_MASK;
    }
}

/*!
 * @}
 */

/*!
 * @name Status Related APIs
 * @{
 */

/*!
 * @brief Gets status flags.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The value of status flags. See @ref _ssarc_interrupt_status_flags for details.
 */
static inline uint32_t SSARC_GetStatusFlags(SSARC_LP_Type *base)
{
    return ((base->INT_STATUS) & SSARC_INT_STATUS_ALL);
}

/*!
 * @brief Clears status flags.
 *
 * @note Only @ref kSSARC_AddressErrorFlag, @ref kSSARC_AHBErrorFlag, @ref kSSARC_TimeoutFlag and
 *       @ref kSSARC_GroupConflictFlag can be cleared.
 *
 * @param base SSARC_LP peripheral base address.
 * @param mask The mask value for flags to be cleared. See @ref _ssarc_interrupt_status_flags for details.
 */

static inline void SSARC_ClearStatusFlags(SSARC_LP_Type *base, uint32_t mask)
{
    base->INT_STATUS = mask;
}

/*!
 * @brief Gets the error index that indicates which descriptor will trigger the AHB_ERR or ADDR_ERR interrupt.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The error index.
 */
static inline uint32_t SSARC_GetErrorIndex(SSARC_LP_Type *base)
{
    return (base->INT_STATUS & SSARC_LP_INT_STATUS_ERR_INDEX_MASK);
}

/*!
 *@}
 */

/*!
 * @name Time Out Related APIs
 * @{
 */

/*!
 * @brief Sets timeout value for the entire group to complete.
 *
 * This function sets timeout value for the entire group to complete. Setting timeout value
 * to 0 will disable this feature.
 *
 * @param base SSARC_LP peripheral base address.
 * @param value The timeout value, 0 means disable time out feature.
 */
static inline void SSARC_SetTimeoutValue(SSARC_LP_Type *base, uint32_t value)
{
    base->HP_TIMEOUT = value;
}

/*!
 * @brief Gets timeout value for AHB clock.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The timeout value.
 */
static inline uint32_t SSARC_GetTimeoutValue(SSARC_LP_Type *base)
{
    return base->HP_TIMEOUT;
}

/*!
 * @}
 */

/*!
 * @name Pending Group Related APIs
 */

/*!
 * @brief Gets the value that indicates which groups are pending for restore from hardware request.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The value of the pending groups.
 */
static inline uint16_t SSARC_GetHardwareRequestRestorePendingGroup(SSARC_LP_Type *base)
{
    return (uint16_t)(((base->HW_GROUP_PENDING) & SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING_MASK) >>
                      SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING_SHIFT);
}

/*!
 * @brief Gets the value that indicates which groups are pending for save from hardware request.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The value of the pending groups.
 */
static inline uint16_t SSARC_GetHardwareRequestSavePendingGroup(SSARC_LP_Type *base)
{
    return (uint16_t)(((base->HW_GROUP_PENDING) & SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING_MASK) >>
                      SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING_SHIFT);
}

/*!
 * @brief Gets the value that indicates which groups are pending for restore from software request.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The value of the pending groups.
 */
static inline uint16_t SSARC_GetSoftwareRequestRestorePendingGroup(SSARC_LP_Type *base)
{
    return (uint16_t)(((base->SW_GROUP_PENDING) & SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING_MASK) >>
                      SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING_SHIFT);
}

/*!
 * @brief Gets the value that indicates which groups are pending for save from software request.
 *
 * @param base SSARC_LP peripheral base address.
 * @return The value of the pending groups.
 */
static inline uint16_t SSARC_GetSoftwareRequestSavePendingGroup(SSARC_LP_Type *base)
{
    return (uint16_t)(((base->SW_GROUP_PENDING) & SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING_MASK) >>
                      SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING_SHIFT);
}

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* _FSL_SSARC_H_ */
