/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_PPI_H__
#define NRF_DRV_PPI_H__

#include <nrfx_ppi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_ppi PPI driver - legacy layer
 * @{
 * @ingroup  nrf_ppi
 *
 * @brief    @tagAPI52 Layer providing compatibility with the former API.
 */

/** @brief Macro for forwarding the new implementation. */
#define NRF_PPI_ALL_APP_CHANNELS_MASK            NRFX_PPI_ALL_APP_CHANNELS_MASK
/** @brief Macro for forwarding the new implementation. */
#define NRF_PPI_PROG_APP_CHANNELS_MASK           NRFX_PPI_PROG_APP_CHANNELS_MASK
/** @brief Macro for forwarding the new implementation. */
#define NRF_PPI_ALL_APP_GROUPS_MASK              NRFX_PPI_ALL_APP_GROUPS_MASK

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_alloc                nrfx_ppi_channel_alloc
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_free                 nrfx_ppi_channel_free
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_assign               nrfx_ppi_channel_assign
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_fork_assign          nrfx_ppi_channel_fork_assign
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_enable               nrfx_ppi_channel_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_disable              nrfx_ppi_channel_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_to_mask              nrfx_ppi_channel_to_mask
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channels_include_in_group    nrfx_ppi_channels_include_in_group
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_include_in_group     nrfx_ppi_channel_include_in_group
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channels_remove_from_group   nrfx_ppi_channels_remove_from_group
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_channel_remove_from_group    nrfx_ppi_channel_remove_from_group

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_group_alloc                  nrfx_ppi_group_alloc
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_group_free                   nrfx_ppi_group_free
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_group_clear                  nrfx_ppi_group_clear
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_group_enable                 nrfx_ppi_group_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_group_disable                nrfx_ppi_group_disable

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_task_addr_get                nrfx_ppi_task_addr_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_task_addr_group_enable_get   nrfx_ppi_task_addr_group_enable_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_ppi_task_addr_group_disable_get  nrfx_ppi_task_addr_group_disable_get

/**
 * @brief Function for initializing PPI module.
 *
 * @retval NRF_SUCCESS                          If the module was successfully initialized.
 * @retval NRF_ERROR_MODULE_ALREADY_INITIALIZED If the module has already been initialized.
 */
ret_code_t nrf_drv_ppi_init(void);

/**
 * @brief Function for uninitializing the PPI module.
 *
 * This function also disables all channels and clears the channel groups.
 *
 * @retval NRF_SUCCESS             If the module was successfully uninitialized.
 * @retval NRF_ERROR_INVALID_STATE If the module has not been initialized yet.
 */
ret_code_t nrf_drv_ppi_uninit(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_PPI_H__
