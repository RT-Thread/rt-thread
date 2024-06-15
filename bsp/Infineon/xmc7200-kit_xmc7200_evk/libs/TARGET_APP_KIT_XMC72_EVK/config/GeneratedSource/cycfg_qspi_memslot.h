/*******************************************************************************
 * File Name: cycfg_qspi_memslot.h
 *
 * Description:
 * Provides declarations of the SMIF-driver memory configuration.
 * This file was automatically generated and should not be modified.
 * QSPI Configurator 4.30.0.1865
 *
 *******************************************************************************
 * Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef CYCFG_QSPI_MEMSLOT_H
#define CYCFG_QSPI_MEMSLOT_H
#include "cy_smif_memslot.h"

#define CY_SMIF_CFG_TOOL_VERSION           (430)

/* Supported QSPI Driver version */
#define CY_SMIF_DRV_VERSION_REQUIRED       (100)

#if !defined(CY_SMIF_DRV_VERSION)
    #define CY_SMIF_DRV_VERSION            (100)
#endif

/* Check the used Driver version */
#if (CY_SMIF_DRV_VERSION_REQUIRED > CY_SMIF_DRV_VERSION)
   #error The QSPI Configurator requires a newer version of the PDL. Update the PDL in your project.
#endif

typedef cy_stc_smif_mem_config_t cy_serial_flash_mem_config_t;
typedef cy_stc_smif_block_config_t cy_serial_flash_block_config_t;

#define CY_SMIF_DEVICE_NUM 1

extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_readCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_writeEnCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_writeDisCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_eraseCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_chipEraseCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_programCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_readStsRegQeCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_readStsRegWipCmd;
extern cy_stc_smif_mem_cmd_t S25FL512S_SlaveSlot_0_writeStsRegQeCmd;

extern cy_stc_smif_mem_device_cfg_t deviceCfg_S25FL512S_SlaveSlot_0;

extern cy_stc_smif_mem_config_t S25FL512S_SlaveSlot_0;

extern cy_stc_smif_mem_config_t* smifMemConfigs[CY_SMIF_DEVICE_NUM];

extern cy_stc_smif_block_config_t smifBlockConfig;


#endif /*CYCFG_QSPI_MEMSLOT_H*/
