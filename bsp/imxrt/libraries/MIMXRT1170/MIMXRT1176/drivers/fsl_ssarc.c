/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ssarc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ssarc"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void SSARC_MapDescriptorsToGroup(SSARC_LP_Type *base, uint8_t groupID, uint32_t startIndex, uint32_t endIndex);
static void SSARC_SetGroupRestoreOrder(SSARC_LP_Type *base, uint8_t groupID, ssarc_save_restore_order_t order);
static void SSARC_SetGroupSaveOrder(SSARC_LP_Type *base, uint8_t groupID, ssarc_save_restore_order_t order);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Maps the descriptors to the selected group.
 *
 * @note One descriptor can be mapped to different group, but please make sure
 *       one descriptor can only be mapped to one power domain.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 * @param startIndex The index of the first descriptor of the group.
 * @param endIndex The index of the last descriptor of the group.
 */
static void SSARC_MapDescriptorsToGroup(SSARC_LP_Type *base, uint8_t groupID, uint32_t startIndex, uint32_t endIndex)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);
    assert((startIndex < endIndex) || (startIndex == endIndex));

    base->GROUPS[groupID].DESC_CTRL0 = SSARC_LP_DESC_CTRL0_START(startIndex) | SSARC_LP_DESC_CTRL0_END(endIndex);
}

/*!
 * @brief Set the order of descriptors within the group are processed when restoring register values.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 * @param order The restore order.
 */
static void SSARC_SetGroupRestoreOrder(SSARC_LP_Type *base, uint8_t groupID, ssarc_save_restore_order_t order)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    if (order == kSSARC_ProcessFromStartToEnd)
    {
        base->GROUPS[groupID].DESC_CTRL0 &= ~SSARC_LP_DESC_CTRL0_RT_ORDER_MASK;
    }
    else
    {
        base->GROUPS[groupID].DESC_CTRL0 |= SSARC_LP_DESC_CTRL0_RT_ORDER_MASK;
    }
}

/*!
 * @brief Set the order of descriptors within the group are processed when saving register values.
 *
 * @param base SSARC_LP peripheral base address.
 * @param groupID The index of the group. Range from 0 to 15.
 * @param order The save order.
 */
static void SSARC_SetGroupSaveOrder(SSARC_LP_Type *base, uint8_t groupID, ssarc_save_restore_order_t order)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    if (order == kSSARC_ProcessFromStartToEnd)
    {
        base->GROUPS[groupID].DESC_CTRL0 &= ~SSARC_LP_DESC_CTRL0_SV_ORDER_MASK;
    }
    else
    {
        base->GROUPS[groupID].DESC_CTRL0 |= SSARC_LP_DESC_CTRL0_SV_ORDER_MASK;
    }
}

/*!
 * brief Sets the configuration of the descriptor.
 *
 * param base SSARC_HP peripheral base address.
 * param index The index of descriptor. Range from 0 to 1023.
 * param config Pointer to the structure ssarc_descriptor_config_t. Please refer to @ref ssarc_descriptor_config_t for
 * details.
 */
void SSARC_SetDescriptorConfig(SSARC_HP_Type *base, uint32_t index, const ssarc_descriptor_config_t *config)
{
    assert(config != NULL);

    uint32_t temp32 = 0UL;

    /* Set the address of the register to be saved/restored. */
    base->DESC[index].SRAM0 = config->address;

    temp32 = SSARC_HP_SRAM2_TYPE(config->type) | SSARC_HP_SRAM2_SIZE(config->size);
    temp32 |= (uint32_t)(config->operation);

    base->DESC[index].SRAM2 = temp32;

    /* Set the value of the register to be saved/restored. */
    /* If the type is set as kSSARC_ReadValueWriteBack, the SRAM1 register will be
       loaded with the value on save operation, and the data in SRAM1 register will be over-written, so
       it is no need to set SRAM1 register in that type. */
    if (config->type != kSSARC_ReadValueWriteBack)
    {
        base->DESC[index].SRAM1 = config->data;
    }
}

/*!
 * brief Init the selected group.
 *
 * note For the groups with the same save priority or restore priority,
 *      the save/restore operation runs in the group order.
 *
 * param base SSARC_LP peripheral base address.
 * param groupID The index of the group. Range from 0 to 15.
 * param config Pointer to the structure ssarc_group_config_t. Please refer to @ref ssarc_group_config_t for details.
 */
void SSARC_GroupInit(SSARC_LP_Type *base, uint8_t groupID, const ssarc_group_config_t *config)
{
    assert(config != NULL);
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    uint32_t temp32;

    temp32 = SSARC_LP_DESC_CTRL1_POWER_DOMAIN(config->powerDomain) |
             SSARC_LP_DESC_CTRL1_SV_PRIORITY(config->savePriority) |
             SSARC_LP_DESC_CTRL1_RT_PRIORITY(config->restorePriority) | SSARC_LP_DESC_CTRL1_CPUD(config->cpuDomain);
    base->GROUPS[groupID].DESC_CTRL1 = temp32;

    SSARC_MapDescriptorsToGroup(base, groupID, config->startIndex, config->endIndex);
    SSARC_SetGroupRestoreOrder(base, groupID, config->restoreOrder);
    SSARC_SetGroupSaveOrder(base, groupID, config->saveOrder);

    /* Config the highest address and the lowest address. */
    base->GROUPS[groupID].DESC_ADDR_UP   = config->highestAddress;
    base->GROUPS[groupID].DESC_ADDR_DOWN = config->lowestAddress;

    /* Enable the group. */
    base->GROUPS[groupID].DESC_CTRL1 |= SSARC_LP_DESC_CTRL1_GP_EN_MASK;
}

/*!
 * brief Triggers software request.
 *
 * note Each group allows software to trigger the save/restore operation without getting the request
 *       from basic power controller.
 *
 * param base SSARC_LP peripheral base address.
 * param groupID The index of the group. Range from 0 to 15.
 * param mode. Software trigger mode. Please refer to @ref ssarc_software_trigger_mode_t for details.
 */
void SSARC_TriggerSoftwareRequest(SSARC_LP_Type *base, uint8_t groupID, ssarc_software_trigger_mode_t mode)
{
    assert(groupID < SSARC_LP_DESC_CTRL0_COUNT);

    base->GROUPS[groupID].DESC_CTRL1 |= (uint32_t)mode;

    while (((base->GROUPS[groupID].DESC_CTRL1) & (uint32_t)mode) != 0UL)
    {
    }
}
