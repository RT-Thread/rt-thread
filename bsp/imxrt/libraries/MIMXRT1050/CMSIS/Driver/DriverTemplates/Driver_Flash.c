/*
 * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "Driver_Flash.h"

#define ARM_FLASH_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/* Sector Information */
#ifdef FLASH_SECTORS
static ARM_FLASH_SECTOR FLASH_SECTOR_INFO[FLASH_SECTOR_COUNT] = {
    FLASH_SECTORS
};
#else
#define FLASH_SECTOR_INFO    NULL
#endif

/* Flash Information */
static ARM_FLASH_INFO FlashInfo = {
    0, /* FLASH_SECTOR_INFO  */
    0, /* FLASH_SECTOR_COUNT */
    0, /* FLASH_SECTOR_SIZE  */
    0, /* FLASH_PAGE_SIZE    */
    0, /* FLASH_PROGRAM_UNIT */
    0  /* FLASH_ERASED_VALUE */
};

/* Flash Status */
static ARM_FLASH_STATUS FlashStatus;

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_FLASH_API_VERSION,
    ARM_FLASH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
    0, /* event_ready */
    0, /* data_width = 0:8-bit, 1:16-bit, 2:32-bit */
    0  /* erase_chip */
};

//
// Functions
//

ARM_DRIVER_VERSION ARM_Flash_GetVersion(void)
{
}

ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities(void)
{
}

int32_t ARM_Flash_Initialize(ARM_Flash_SignalEvent_t cb_event)
{
}

int32_t ARM_Flash_Uninitialize(void)
{
}

int32_t ARM_Flash_PowerControl(ARM_POWER_STATE state)
{
    switch (state)
    {
    case ARM_POWER_OFF:
        break;

    case ARM_POWER_LOW:
        break;

    case ARM_POWER_FULL:
        break;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

int32_t ARM_Flash_ReadData(uint32_t addr, void *data, uint32_t cnt)
{
}

int32_t ARM_Flash_ProgramData(uint32_t addr, const void *data, uint32_t cnt)
{
}

int32_t ARM_Flash_EraseSector(uint32_t addr)
{
}

int32_t ARM_Flash_EraseChip(void)
{
}

ARM_FLASH_STATUS ARM_Flash_GetStatus(void)
{
}

ARM_FLASH_INFO * ARM_Flash_GetInfo(void)
{
}

void ARM_Flash_SignalEvent(uint32_t event)
{
}
// End Flash Interface

ARM_DRIVER_FLASH Driver_FLASH = {
    ARM_Flash_GetVersion,
    ARM_Flash_GetCapabilities,
    ARM_Flash_Initialize,
    ARM_Flash_Uninitialize,
    ARM_Flash_PowerControl,
    ARM_Flash_ReadData,
    ARM_Flash_ProgramData,
    ARM_Flash_EraseSector,
    ARM_Flash_EraseChip,
    ARM_Flash_GetStatus,
    ARM_Flash_GetInfo
};