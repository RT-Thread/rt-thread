/***************************************************************************//**
* \file cy_efuse.c
* \version 2.20
*
* \brief
* Provides API implementation of the eFuse driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2020 Cypress Semiconductor Corporation
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
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXEFUSE) && (CY_IP_MXEFUSE_VERSION <= 2)

#include "cy_efuse.h"
#include "cy_ipc_drv.h"

/** \cond INTERNAL */
#define CY_EFUSE_OPCODE_SUCCESS             (0xA0000000UL)    /**< The command completed with no errors */
#define CY_EFUSE_OPCODE_STS_Msk             (0xF0000000UL)    /**< The status mask of the SROM API return value */
#define CY_EFUSE_OPCODE_INV_PROT            (0xF0000001UL)    /**< The API is not available in the current protection state */
#define CY_EFUSE_OPCODE_INV_ADDR            (0xF0000002UL)    /**< An attempt to read byte from the out-of-bond or protected eFuse region */
#define CY_EFUSE_OPCODE_READ_FUSE_BYTE      (0x03000000UL)    /**< The SROM API opcode for Read fuse byte operation */
#define CY_EFUSE_OPCODE_OFFSET_Pos          (8UL)             /**< A fuse byte offset position in an opcode */
#define CY_EFUSE_OPCODE_DATA_Msk            (0xFFUL)          /**< The mask for extracting data from the SROM API return value */
#define CY_EFUSE_IPC_STRUCT                 (Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_SYSCALL)) /**< IPC structure to be used */
#define CY_EFUSE_IPC_NOTIFY_STRUCT0         (0x1UL << CY_IPC_INTR_SYSCALL1) /**< IPC notify bit for IPC0 structure (dedicated to System Call) */

/** \endcond */

#ifdef ENABLE_CM7_DATA_CACHE
CY_SECTION_SHAREDMEM
CY_ALIGN(32) static volatile uint32_t opcode = 0UL;
#else
static volatile uint32_t opcode;
#endif

static cy_en_efuse_status_t ProcessOpcode(void);

cy_en_efuse_status_t Cy_EFUSE_GetEfuseBit(uint32_t bitNum, bool *bitVal)
{
    cy_en_efuse_status_t result = CY_EFUSE_BAD_PARAM;

    if (bitVal != NULL)
    {
        uint32_t offset = bitNum / CY_EFUSE_BITS_PER_BYTE;
        uint8_t byteVal;
        *bitVal = false;

        /* Read the eFuse byte */
        result = Cy_EFUSE_GetEfuseByte(offset, &byteVal);

        if (result == CY_EFUSE_SUCCESS)
        {
            uint32_t bitPos = bitNum % CY_EFUSE_BITS_PER_BYTE;
            /* Extract the bit from the byte */
            *bitVal = (((byteVal >> bitPos) & 0x01U) != 0U);
        }
    }
    return (result);
}

cy_en_efuse_status_t Cy_EFUSE_GetEfuseByte(uint32_t offset, uint8_t *byteVal)
{
    cy_en_efuse_status_t result = CY_EFUSE_BAD_PARAM;
    cy_en_ipcdrv_status_t retStatus;

    if (byteVal != NULL)
    {
        /* Prepare opcode before calling the SROM API */
        opcode = CY_EFUSE_OPCODE_READ_FUSE_BYTE | (offset << CY_EFUSE_OPCODE_OFFSET_Pos);

        #ifdef ENABLE_CM7_DATA_CACHE
        #if defined (CY_IP_M7CPUSS)
            #if (CY_CPU_CORTEX_M7)
                SCB_CleanDCache_by_Addr((uint32_t *)&opcode, (int32_t)sizeof(opcode));
            #endif
        #endif
        #endif

        retStatus = Cy_IPC_Drv_SendMsgPtr(CY_EFUSE_IPC_STRUCT, CY_EFUSE_IPC_NOTIFY_STRUCT0, (void*)&opcode);

        /* Send the IPC message */
        if (retStatus == CY_IPC_DRV_SUCCESS)
        {
            /* Wait until the IPC structure is locked */
            while(Cy_IPC_Drv_IsLockAcquired(CY_EFUSE_IPC_STRUCT) != false)
            {
            }

        #ifdef ENABLE_CM7_DATA_CACHE
        #if defined (CY_IP_M7CPUSS)
            #if (CY_CPU_CORTEX_M7)
                SCB_InvalidateDCache_by_Addr((uint32_t *)&opcode, (int32_t)sizeof(opcode));
            #endif
        #endif
        #endif

            /* The result of the SROM API call is returned to the opcode variable */
            if ((opcode & CY_EFUSE_OPCODE_STS_Msk) == CY_EFUSE_OPCODE_SUCCESS)
            {
                *byteVal = (uint8_t)(opcode & CY_EFUSE_OPCODE_DATA_Msk);
                result = CY_EFUSE_SUCCESS;
            }
            else
            {
                result = ProcessOpcode();
                *byteVal = 0U;
            }
        }
        else
        {
            result = CY_EFUSE_IPC_BUSY;
        }
    }
    return (result);
}

uint32_t Cy_EFUSE_GetExternalStatus(void)
{
    return (opcode);
}


/*******************************************************************************
* Function Name: ProcessOpcode
****************************************************************************//**
*
* Converts System Call returns to the eFuse driver return defines. If
* an unknown error was returned, the error code can be accessed via the
* Cy_EFUSE_GetExternalStatus() function.
*
* \return
* \ref cy_en_efuse_status_t
*
*******************************************************************************/
static cy_en_efuse_status_t ProcessOpcode(void)
{
    cy_en_efuse_status_t result;

    switch(opcode)
    {
        case CY_EFUSE_OPCODE_INV_PROT :
        {
            result = CY_EFUSE_INVALID_PROTECTION;
            break;
        }
        case CY_EFUSE_OPCODE_INV_ADDR :
        {
            result = CY_EFUSE_INVALID_FUSE_ADDR;
            break;
        }
        default :
        {
            result = CY_EFUSE_ERR_UNC;
            break;
        }
    }

    return (result);
}

#endif /* #ifdef (CY_IP_MXEFUSE) && (CY_IP_MXEFUSE_VERSION <= 2) */

/* [] END OF FILE */
