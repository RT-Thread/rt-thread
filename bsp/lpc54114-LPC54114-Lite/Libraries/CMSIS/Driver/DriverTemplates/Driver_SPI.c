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
 
#include "Driver_SPI.h"

#define ARM_SPI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_SPI_API_VERSION,
    ARM_SPI_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_SPI_CAPABILITIES DriverCapabilities = {
    1, /* Simplex Mode (Master and Slave) */
    1, /* TI Synchronous Serial Interface */
    1, /* Microwire Interface */
    0  /* Signal Mode Fault event: \ref ARM_SPI_EVENT_MODE_FAULT */
};

//
//  Functions
//

ARM_DRIVER_VERSION ARM_SPI_GetVersion(void)
{
}

ARM_SPI_CAPABILITIES ARM_SPI_GetCapabilities(void)
{
}

int32_t ARM_SPI_Initialize(ARM_SPI_SignalEvent_t cb_event)
{
}

int32_t ARM_SPI_Uninitialize(void)
{
}

int32_t ARM_SPI_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_SPI_Send(const void *data, uint32_t num)
{
}

int32_t ARM_SPI_Receive(void *data, uint32_t num)
{
}

int32_t ARM_SPI_Transfer(const void *data_out, void *data_in, uint32_t num)
{
}

uint32_t ARM_SPI_GetDataCount(void)
{
}

int32_t ARM_SPI_Control(uint32_t control, uint32_t arg)
{
    switch (control & ARM_SPI_CONTROL_Msk)
    {
    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;

    case ARM_SPI_MODE_INACTIVE:             // SPI Inactive
        return ARM_DRIVER_OK;

    case ARM_SPI_MODE_MASTER:               // SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
        break;

    case ARM_SPI_MODE_SLAVE:                // SPI Slave  (Output on MISO, Input on MOSI)
        break;

    case ARM_SPI_MODE_MASTER_SIMPLEX:       // SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
    case ARM_SPI_MODE_SLAVE_SIMPLEX:        // SPI Slave  (Output/Input on MISO)
        return ARM_SPI_ERROR_MODE;

    case ARM_SPI_SET_BUS_SPEED:             // Set Bus Speed in bps; arg = value
        break;

    case ARM_SPI_GET_BUS_SPEED:             // Get Bus Speed in bps
        break;

    case ARM_SPI_SET_DEFAULT_TX_VALUE:      // Set default Transmit value; arg = value
        break;

    case ARM_SPI_CONTROL_SS:                // Control Slave Select; arg = 0:inactive, 1:active
        break;

    case ARM_SPI_ABORT_TRANSFER:            // Abort current data transfer
        break;
    }
}

ARM_SPI_STATUS ARM_SPI_GetStatus(void)
{
}

void ARM_SPI_SignalEvent(uint32_t event)
{
    // function body
}

// End SPI Interface

ARM_DRIVER_SPI Driver_SPI = {
    ARM_SPI_GetVersion,
    ARM_SPI_GetCapabilities,
    ARM_SPI_Initialize,
    ARM_SPI_Uninitialize,
    ARM_SPI_PowerControl,
    ARM_SPI_Send,
    ARM_SPI_Receive,
    ARM_SPI_Transfer,
    ARM_SPI_GetDataCount,
    ARM_SPI_Control,
    ARM_SPI_GetStatus
};
