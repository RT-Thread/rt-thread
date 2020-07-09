/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef NRF_DRV_PPI_H
#define NRF_DRV_PPI_H

/*lint ++flb "Enter library region" */
#include "sdk_errors.h"
#include "nrf_ppi.h"
#include <stdbool.h>
#include <stdint.h>

/** @file
 *
 * @addtogroup nrf_ppi PPI HAL and driver
 * @ingroup nrf_drivers
 * @brief Programmable Peripheral Interconnect (PPI) APIs.
 *
 * @details The PPI HAL provides basic APIs for accessing the registers of the PPI.
 * The PPI driver provides APIs on a higher level.
 *
 * @defgroup nrf_drv_ppi PPI driver
 * @{
 * @ingroup  nrf_ppi
 *
 * @brief Programmable Peripheral Interconnect (PPI) driver.
 */

#include "sdk_resources.h"

#ifdef __cplusplus
extern "C" {
#endif

#if PPI_CH_NUM > 16
#define NRF_PPI_ALL_APP_CHANNELS_MASK   ((uint32_t)0xFFFFFFFFuL & ~(NRF_PPI_CHANNELS_USED))  /**< All PPI channels available to the application. */
#define NRF_PPI_PROG_APP_CHANNELS_MASK  ((uint32_t)0x000FFFFFuL & ~(NRF_PPI_CHANNELS_USED))  /**< Programmable PPI channels available to the application. */
#else
#define NRF_PPI_ALL_APP_CHANNELS_MASK   ((uint32_t)0xFFF0FFFFuL & ~(NRF_PPI_CHANNELS_USED))  /**< All PPI channels available to the application. */
#define NRF_PPI_PROG_APP_CHANNELS_MASK  ((uint32_t)0x0000FFFFuL & ~(NRF_PPI_CHANNELS_USED))  /**< Programmable PPI channels available to the application. */
#endif

#define NRF_PPI_ALL_APP_GROUPS_MASK     (((1uL << PPI_GROUP_NUM) - 1) & ~(NRF_PPI_GROUPS_USED))    /**< All PPI groups available to the application. */


/**@brief Function for initializing PPI module.
 *
 * @retval     NRF_SUCCESS                           If the module was successfully initialized.
 * @retval     NRF_ERROR_MODULE_ALREADY_INITIALIZED  If the module has already been initialized.
 */
uint32_t nrf_drv_ppi_init(void);

/**@brief Function for uninitializing the PPI module.
 *
 * This function also disables all channels and clears the channel groups.
 *
 * @retval     NRF_SUCCESS             If the module was successfully uninitialized.
 * @retval     NRF_ERROR_INVALID_STATE If the module has not been initialized yet.
 * @retval     NRF_ERROR_INTERNAL      If the channels or groups could not be disabled.
 */
uint32_t nrf_drv_ppi_uninit(void);

/**@brief Function for allocating a PPI channel.
 * @details This function allocates the first unused PPI channel.
 *
 * @param[out] p_channel               Pointer to the PPI channel that has been allocated.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully allocated.
 * @retval     NRF_ERROR_NO_MEM        If there is no available channel to be used.
 */
uint32_t nrf_drv_ppi_channel_alloc(nrf_ppi_channel_t * p_channel);

/**@brief Function for freeing a PPI channel.
 * @details This function also disables the chosen channel.
 *
 * @param[in]  channel                 PPI channel to be freed.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully freed.
 * @retval     NRF_ERROR_INVALID_PARAM If the channel is not user-configurable.
 */
uint32_t nrf_drv_ppi_channel_free(nrf_ppi_channel_t channel);

/**@brief Function for assigning task and event endpoints to the PPI channel.
 *
 * @param[in]  channel                 PPI channel to be assigned endpoints.
 *
 * @param[in]  eep                     Event endpoint address.
 *
 * @param[in]  tep                     Task endpoint address.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully assigned.
 * @retval     NRF_ERROR_INVALID_STATE If the channel is not allocated for the user.
 * @retval     NRF_ERROR_INVALID_PARAM If the channel is not user-configurable.
 */
uint32_t nrf_drv_ppi_channel_assign(nrf_ppi_channel_t channel, uint32_t eep, uint32_t tep);

/**@brief Function for assigning or clearing fork endpoint to the PPI channel.
 *
 * @param[in]  channel                 PPI channel to be assigned endpoints.
 *
 * @param[in]  fork_tep                Fork task endpoint address or 0 to clear.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully assigned.
 * @retval     NRF_ERROR_INVALID_STATE If the channel is not allocated for the user.
 * @retval     NRF_ERROR_INVALID_PARAM If the channel is not user-configurable.
 * @retval     NRF_ERROR_NOT_SUPPORTED If function is not supported.
 */
uint32_t nrf_drv_ppi_channel_fork_assign(nrf_ppi_channel_t channel, uint32_t fork_tep);

/**@brief Function for enabling a PPI channel.
 *
 * @param[in]  channel                 PPI channel to be enabled.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully enabled.
 * @retval     NRF_ERROR_INVALID_STATE If the user-configurable channel is not allocated.
 * @retval     NRF_ERROR_INVALID_PARAM If the channel cannot be enabled by the user.
 */
uint32_t nrf_drv_ppi_channel_enable(nrf_ppi_channel_t channel);

/**@brief Function for disabling a PPI channel.
 *
 * @param[in]  channel                 PPI channel to be disabled.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully disabled.
 * @retval     NRF_ERROR_INVALID_STATE If the user-configurable channel is not allocated.
 * @retval     NRF_ERROR_INVALID_PARAM If the channel cannot be disabled by the user.
 */
uint32_t nrf_drv_ppi_channel_disable(nrf_ppi_channel_t channel);

/**@brief Function for allocating a PPI channel group.
 * @details This function allocates the first unused PPI group.
 *
 * @param[out] p_group                 Pointer to the PPI channel group that has been allocated.
 *
 * @retval     NRF_SUCCESS             If the channel group was successfully allocated.
 * @retval     NRF_ERROR_NO_MEM        If there is no available channel group to be used.
 */
uint32_t nrf_drv_ppi_group_alloc(nrf_ppi_channel_group_t * p_group);

/**@brief Function for freeing a PPI channel group.
 * @details This function also disables the chosen group.
 *
 * @param[in]  group                   PPI channel group to be freed.
 *
 * @retval     NRF_SUCCESS             If the channel group was successfully freed.
 * @retval     NRF_ERROR_INVALID_PARAM If the channel group is not user-configurable.
 */
uint32_t nrf_drv_ppi_group_free(nrf_ppi_channel_group_t group);

/**@brief  Compute a channel mask for NRF_PPI registers.
 *
 * @param[in]  channel  Channel number to transform to a mask.
 *
 * @retval     Channel mask.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_channel_to_mask(nrf_ppi_channel_t channel)
{
    return (1uL << (uint32_t) channel);
}

/**@brief Function for including multiple PPI channels in a channel group.
 *
 * @param[in]  channel_mask            PPI channels to be added.
 * @param[in]  group                   Channel group in which to include the channels.
 *
 * @retval     NRF_SUCCESS             If the channels was successfully included.
 */
uint32_t nrf_drv_ppi_channels_include_in_group(uint32_t channel_mask,
                                               nrf_ppi_channel_group_t group);

/**@brief Function for including a PPI channel in a channel group.
 *
 * @param[in]  channel                 PPI channel to be added.
 * @param[in]  group                   Channel group in which to include the channel.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully included.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_channel_include_in_group(nrf_ppi_channel_t       channel,
                                                              nrf_ppi_channel_group_t group)
{
    return nrf_drv_ppi_channels_include_in_group(nrf_drv_ppi_channel_to_mask(channel), group);
}

/**@brief Function for removing multiple PPI channels from a channel group.
 *
 * @param[in]  channel_mask            PPI channels to be removed.
 * @param[in]  group                   Channel group from which to remove the channels.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully removed.
 */
uint32_t nrf_drv_ppi_channels_remove_from_group(uint32_t channel_mask,
                                                nrf_ppi_channel_group_t group);

/**@brief Function for removing a PPI channel from a channel group.
 *
 * @param[in]  channel                 PPI channel to be removed.
 * @param[in]  group                   Channel group from which to remove the channel.
 *
 * @retval     NRF_SUCCESS             If the channel was successfully removed.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_channel_remove_from_group(nrf_ppi_channel_t       channel,
                                                               nrf_ppi_channel_group_t group)
{
    return nrf_drv_ppi_channels_remove_from_group(nrf_drv_ppi_channel_to_mask(channel), group);
}

/**@brief Function for clearing a PPI channel group.
 *
 * @param[in]  group                   Channel group to be cleared.
 *
 * @retval     NRF_SUCCESS             If the group was successfully cleared.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_group_clear(nrf_ppi_channel_group_t group)
{
    return nrf_drv_ppi_channels_remove_from_group(NRF_PPI_ALL_APP_CHANNELS_MASK, group);
}

/**@brief Function for enabling a PPI channel group.
 *
 * @param[in]  group                   Channel group to be enabled.
 *
 * @retval     NRF_SUCCESS             If the group was successfully enabled.
 */
uint32_t nrf_drv_ppi_group_enable(nrf_ppi_channel_group_t group);

/**@brief Function for disabling a PPI channel group.
 *
 * @param[in]  group                   Channel group to be disabled.
 *
 * @retval     NRF_SUCCESS             If the group was successfully disabled.
 */
uint32_t nrf_drv_ppi_group_disable(nrf_ppi_channel_group_t group);

/**
 * @brief Function for getting the address of a PPI task.
 *
 * @param[in]  task                      Task.
 *
 * @retval     Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_task_addr_get(nrf_ppi_task_t task)
{
    return (uint32_t) nrf_ppi_task_address_get(task);
}

/**
 * @brief Function for getting the address of a PPI group enable task.
 *
 * @param[in]  group                     PPI channel group
 *
 * @retval     Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_task_addr_group_enable_get(nrf_ppi_channel_group_t group)
{
    return (uint32_t) nrf_ppi_task_group_enable_address_get(group);
}

/**
 * @brief Function for getting the address of a PPI group enable task.
 *
 * @param[in]  group                     PPI channel group
 *
 * @retval     Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_ppi_task_addr_group_disable_get(nrf_ppi_channel_group_t group)
{
    return (uint32_t) nrf_ppi_task_group_disable_address_get(group);
}

/**
 *@}
 **/

/*lint --flb "Leave library region" */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_PPI_H
