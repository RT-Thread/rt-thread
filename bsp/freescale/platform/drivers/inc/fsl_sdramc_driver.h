/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_SDRAMC_DRIVER_H__
#define __FSL_SDRAMC_DRIVER_H__
 
#include <stdint.h>
#include <stdbool.h>
#include "fsl_sdramc_hal.h"
 
/*!
 * @addtogroup sdramc_driver
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for SDRAM instances. */
extern SDRAM_Type * const g_sdramBase[];

/*! @brief Table to save SDRAM IRQ enumeration numbers defined in the CMSIS header file */
extern const IRQn_Type g_sdramIrqId[];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief SDRAM configuration structure for refresh timing.
 *
 * Defines a configure structure SDRAMConfig to refresh and uses the SDRAM_DRV_Init() function to make necessary
 * initializations.
 *
 * 
 */
typedef struct SDRAMRefreshConfig {
    sdram_refresh_time_t refreshTime;  /*!< Trc:The number of bus clocks inserted between a REF and next ACTIVE command*/
    uint32_t sdramRefreshRow;       /*!< The SDRAM refresh time each row: ns/row. */
} sdram_refresh_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the SDRAM controller.
 * 
 * This function must be called before calling any other SDRAM controller driver functions.
 * This function ungates the SDRAM controller clock and sets the SDRAM controller clock.
 * Pass in its configuration structure.
 * 
 *
 * @param instance SDRAM module instance number.
 * @param config The SDRAM configuration structure.
 * @param whichBlock The block selection.
 * @param ctlConfig The block control configuration
 */
void SDRAM_DRV_Init(uint32_t instance, sdram_refresh_config_t *configure, sdram_block_selection_t whichBlock,
                    sdram_blockctl_configure_t *ctlConfig);

/*!
 * @brief Disables the SDRAM module and gate control.
 *
 * This function disables the SDRAM controller clock.
 * SDRAM_DRV_Init must be called if you want to use SDRAM again.
 *
 * @param instance SDRAM module instance number.
 */
void SDRAM_DRV_Deinit(uint32_t instance);

/*!
 * @brief Sends the SDRAM command.
 * 
 * This function sends either a precharge or MRS command to SDRAM.
 * 
 * @param instance SDRAM module instance number.
 * @param whichBlock The block selection.
 * @param command The command, see to "sdram_command_t".
 */
void SDRAM_DRV_SendCommand(uint32_t instance, sdram_block_selection_t whichBlock, sdram_command_t command);

/*!
 * @brief Gets the SDRAM command execute status.
 * 
 * This function stops and disables the SDRAM carrier generator and modulator.
 * When the SDRAM carrier generator and modulator is disabled the IRO signal
 * can be controlled directly by calling SDRAM_DRV_SetIroCtl function.
 * 
 * @param instance SDRAM module instance number.
 * @param whichBlock The block selection.
 * @param command The command, see to "sdram_command_t".
 * @return the execute status of command
 *              - true, the command is finished.
 *              - false, the command is on-going.
 */
bool SDRAM_DRV_IsCommandFinished(uint32_t instance, sdram_block_selection_t whichBlock, sdram_command_t command);

/*!
 * @brief Sends the self-refresh command to SDRAM.
 *
 * @param instance SDRAM module instance number.
 */
void SDRAM_DRV_SendSelfRefreshCmd(uint32_t instance);

/*!
 * @brief Sends the self-refresh exit command to SDRAM.
 *
 * @param instance SDRAM module instance number.
 */
void SDRAM_DRV_SendSelfRefreshExitCmd(uint32_t instance);

/*!
 * @brief Enables/disables refresh.
 *
 * @param instance SDRAM module instance number.
 * @param whichBlock The block which is selected.
 * @param enable Enables or disables.
 */
void SDRAM_DRV_SetRefreshCmd(uint32_t instance, sdram_block_selection_t whichBlock, bool enable);

/*!
 * @brief Enables/disables the write protect.
 *
 * @param instance SDRAM module instance number.
 * @param whichBlock The block which is selected.
 * @param enable Enables or disables.
 */
void SDRAM_DRV_SetWriteProtectCmd(uint32_t instance, sdram_block_selection_t whichBlock, bool enable);

/*!
 * @brief Enables/disables the operation valid.
 *
 * @param instance SDRAM module instance number.
 * @param whichBlock The block which is selected.
 * @param enable Enables or disables.
 */
void SDRAM_DRV_SetOperateValidCmd(uint32_t instance, sdram_block_selection_t whichBlock, bool enable);

#if defined(__cplusplus)
}
#endif

/*! @}*/
 
#endif /* __FSL_SDRAMC_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

