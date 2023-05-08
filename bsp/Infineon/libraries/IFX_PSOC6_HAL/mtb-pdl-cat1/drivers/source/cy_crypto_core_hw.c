/***************************************************************************//**
* \file cy_crypto_core_hw.c
* \version 2.70
*
* \brief
*  This file provides the source code to the API for the utils
*  in the Crypto driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_crypto_core_hw.h"
#include "cy_crypto_core_hw_vu.h"
#include "cy_syslib.h"
#include <stdbool.h>

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 4, \
'CRYPTO_Type will typecast to either CRYPTO_V1_Type or CRYPTO_V2_Type but not both on PDL initialization based on the target device at compile time.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 14.3', 2, \
'Since value of CY_CRYPTO_V1 is decided by PDL device agnostic / hardware specific model, controlling expression will not have an invariant value.');

#if !defined(CY_CRYPTO_SERVICE_LIBRARY_LEVEL)
    #define CY_CRYPTO_SERVICE_LIBRARY_LEVEL CY_CRYPTO_FULL_LIBRARY
#endif

/*******************************************************************************
*                   Global Variables
*******************************************************************************/

static uint32_t  cy_cryptoVuMemSize = 0u;

#if !defined(CY_CRYPTO_CFG_HW_USE_MPN_SPECIFIC)
/* This is set in Cy_Crypto_Core_Enable() to the device information relevant
 * for the current target.
 */
const cy_stc_cryptoIP_t * cy_cryptoIP = NULL;

/* Platform and peripheral crypto block configuration */
const cy_stc_cryptoIP_t cy_cryptoIpBlockCfgPSoC6_01 =
{
    /* CRYPTO register offsets */
    /* cryptoStatusOffset        */ offsetof(CRYPTO_V1_Type, STATUS),
    /* cryptoIstrFfCtlOffset     */ offsetof(CRYPTO_V1_Type, INSTR_FF_CTL),
    /* cryptoInstrFfStatusOffset */ offsetof(CRYPTO_V1_Type, INSTR_FF_STATUS),
    /* cryptoInstrFfWrOffset     */ offsetof(CRYPTO_V1_Type, INSTR_FF_WR),
    /* cryptoVuRfDataOffset      */ offsetof(CRYPTO_V1_Type, RF_DATA),
    /* cryptoAesCtlOffset        */ offsetof(CRYPTO_V1_Type, AES_CTL),
    /* cryptoPrResultOffset      */ offsetof(CRYPTO_V1_Type, PR_RESULT),
    /* cryptoTrResultOffset      */ offsetof(CRYPTO_V1_Type, TR_RESULT),
    /* cryptoCrcCtlOffset        */ offsetof(CRYPTO_V1_Type, CRC_CTL),
    /* cryptoCrcDataCtlOffset    */ offsetof(CRYPTO_V1_Type, CRC_DATA_CTL),
    /* cryptoCrcPolCtlOffset     */ offsetof(CRYPTO_V1_Type, CRC_POL_CTL),
    /* cryptoCrcRemCtlOffset     */ offsetof(CRYPTO_V1_Type, CRC_REM_CTL),
    /* cryptoCrcRemResultOffset  */ offsetof(CRYPTO_V1_Type, CRC_REM_RESULT),
    /* cryptoVuCtl0Offset        */ offsetof(CRYPTO_V1_Type, VU_CTL0),
    /* cryptoVuCtl1Offset        */ offsetof(CRYPTO_V1_Type, VU_CTL1),
    /* cryptoVuStatusOffset      */ offsetof(CRYPTO_V1_Type, VU_STATUS),
    /* cryptoIntrOffset          */ offsetof(CRYPTO_V1_Type, INTR),
    /* cryptoIntrSetOffset       */ offsetof(CRYPTO_V1_Type, INTR_SET),
    /* cryptoIntrMaskOffset      */ offsetof(CRYPTO_V1_Type, INTR_MASK),
    /* cryptoIntrMaskedOffset    */ offsetof(CRYPTO_V1_Type, INTR_MASKED),
    /* cryptoMemBufOffset        */ offsetof(CRYPTO_V1_Type, MEM_BUFF),
};

const cy_stc_cryptoIP_t cy_cryptoIpBlockCfgPSoC6_02 =
{
    /* CRYPTO register offsets */
    /* cryptoStatusOffset        */ offsetof(CRYPTO_V2_Type, STATUS),
    /* cryptoIstrFfCtlOffset     */ offsetof(CRYPTO_V2_Type, INSTR_FF_CTL),
    /* cryptoInstrFfStatusOffset */ offsetof(CRYPTO_V2_Type, INSTR_FF_STATUS),
    /* cryptoInstrFfWrOffset     */ offsetof(CRYPTO_V2_Type, INSTR_FF_WR),
    /* cryptoVuRfDataOffset      */ offsetof(CRYPTO_V2_Type, VU_RF_DATA),
    /* cryptoAesCtlOffset        */ offsetof(CRYPTO_V2_Type, AES_CTL),
    /* cryptoPrResultOffset      */ offsetof(CRYPTO_V2_Type, PR_RESULT),
    /* cryptoTrResultOffset      */ offsetof(CRYPTO_V2_Type, TR_RESULT),
    /* cryptoCrcCtlOffset        */ offsetof(CRYPTO_V2_Type, CRC_CTL),
    /* cryptoCrcDataCtlOffset    */ offsetof(CRYPTO_V2_Type, CRC_DATA_CTL),
    /* cryptoCrcPolCtlOffset     */ offsetof(CRYPTO_V2_Type, CRC_POL_CTL),
    /* cryptoCrcRemCtlOffset     */ offsetof(CRYPTO_V2_Type, CRC_REM_CTL),
    /* cryptoCrcRemResultOffset  */ offsetof(CRYPTO_V2_Type, CRC_REM_RESULT),
    /* cryptoVuCtl0Offset        */ offsetof(CRYPTO_V2_Type, VU_CTL0),
    /* cryptoVuCtl1Offset        */ offsetof(CRYPTO_V2_Type, VU_CTL1),
    /* cryptoVuStatusOffset      */ offsetof(CRYPTO_V2_Type, VU_STATUS),
    /* cryptoIntrOffset          */ offsetof(CRYPTO_V2_Type, INTR),
    /* cryptoIntrSetOffset       */ offsetof(CRYPTO_V2_Type, INTR_SET),
    /* cryptoIntrMaskOffset      */ offsetof(CRYPTO_V2_Type, INTR_MASK),
    /* cryptoIntrMaskedOffset    */ offsetof(CRYPTO_V2_Type, INTR_MASKED),
    /* cryptoMemBufOffset        */ offsetof(CRYPTO_V2_Type, MEM_BUFF),
};
#endif

/* The defines of the power modes of the CRYPTO */
#define CY_CRYPTO_PWR_MODE_OFF               (0UL)
#define CY_CRYPTO_PWR_MODE_RETAINED          (2UL)
#define CY_CRYPTO_PWR_MODE_ENABLED           (3UL)

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Vu_RunInstr
*****************************************************************************//**
*
* Run the Crypto Vector Unit instruction with one parameter.
*
* \param base
* The pointer to the CRYPTO instance.

* \param blockingMode
* Sets the blocking or non-blocking operation mode.
*
* \param instr
* The Opcode of the called instruction.
*
* \param params
* The parameters for the instruction operand.
*
*******************************************************************************/
void Cy_Crypto_Core_Vu_RunInstr(CRYPTO_Type *base, bool blockingMode, uint32_t instr, uint32_t params)
{
    bool isRelocated = Cy_Crypto_Core_GetVuMemoryAddress(base) != REG_CRYPTO_MEM_BUFF(base);

    /* Check whether FIFO has enough space for 1 instruction */
    Cy_Crypto_Core_WaitForInstrFifoAvailable(base, CY_CRYPTO_INSTR_SINGLE);

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((instr << CY_CRYPTO_OPCODE_POS) | (params));

    if ( (blockingMode) || (isRelocated) )
    {
        Cy_Crypto_Core_WaitForFifoAvailable(base);
        Cy_Crypto_Core_Vu_WaitForComplete(base);
    }
}

/**
* \addtogroup group_crypto_lld_hw_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_ClearVuRegisters
****************************************************************************//**
*
* The function to initialize the Crypto VU registers.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
void Cy_Crypto_Core_ClearVuRegisters(CRYPTO_Type *base)
{
    if (Cy_Crypto_Core_IsEnabled(base))
    {
        /* Clear whole register file */
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG14, 0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG13, 0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG12, 0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG11, 0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG10, 0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG9,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG8,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG7,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG6,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG5,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG4,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG3,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG2,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG1,  0u, 1u);
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG0,  0u, 1u);

        /* Set the stack pointer to the Crypto buff size, in words */
        CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG15, cy_cryptoVuMemSize / 4u, 1u);
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_SetVuMemoryAddress
****************************************************************************//**
*
* Sets the new memory buffer address and size.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param vuMemoryAddr
* The memory buffer location that will be used as Crypto MEM_BUFF
*
* \param vuMemorySize
* The provided memory buffer size in bytes.
*
* \return
* \ref cy_en_crypto_status_t
*
* \note This function sets the default device specific values
*       when vuMemoryAddr parameter is NULL and vuMemorySize parameter is zero.
*
* \note New memory buffer should be allocated in a memory region that is not
*       protected by a protection scheme for use by Crypto hardware.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_SetVuMemoryAddress(CRYPTO_Type *base,
                                                        uint32_t const *vuMemoryAddr, uint32_t vuMemorySize)
{
    cy_en_crypto_status_t resultVal = CY_CRYPTO_BAD_PARAMS;
    uint32_t *vuMemAddr = (uint32_t *)vuMemoryAddr;
    uint32_t  vuMemSize = vuMemorySize;

#if !defined(CY_CRYPTO_CFG_HW_USE_MPN_SPECIFIC)
    if (cy_cryptoIP != NULL)
    {
#endif
        if ((vuMemAddr == NULL) && (vuMemSize == 0uL))
        {
            vuMemAddr = REG_CRYPTO_MEM_BUFF(base);
            vuMemSize = CY_CRYPTO_MEM_BUFF_SIZE;
        }

        /* Check for new memory size is less or equal to maximal IP allowed value */
        if ((vuMemAddr != NULL) && (vuMemSize != 0uL) && (vuMemSize <= 32768u))
        {
            /* mxcrypto (V1) IP uses MEM_BUF aligned to 16KB */
            uint32_t memAlignMask = 16384uL - 1uL;

            uint32_t memFrameMask = 0xFFFFFFFFuL;
            /*
            Specifies the size of  the vector operand memory region.
            Legal values:
            "0b0000000":  32 KB memory region (VU_CTL1.ADDR[14:8] ignored).
            "0b1000000":  16 KB memory region (VU_CTL1.ADDR[13:8] ignored).
            "0b1100000":   8 KB memory region (VU_CTL1.ADDR[12:8] ignored).
            "0b1110000":   4 KB memory region (VU_CTL1.ADDR[11:8] ignored).
            "0b1111000":   2 KB memory region (VU_CTL1.ADDR[10:8] ignored).
            "0b1111100":   1 KB memory region (VU_CTL1.ADDR[9:8]  ignored).
            "0b1111110": 512  B memory region (VU_CTL1.ADDR[8]    ignored).
            "0b1111111": 256  B memory region.
            */
            switch (vuMemSize)
            {
                /* "0b0000000": 32 KB memory region (VU_CTL1.ADDR[14:8] ignored). */
                case 32768uL:
                    memFrameMask = 0x0u;
                    break;
                /* "0b1000000": 16 KB memory region (VU_CTL1.ADDR[13:8] ignored). */
                case 16384uL:
                    memFrameMask = 0x40u;
                    break;
                /* "0b1100000":  8 KB memory region (VU_CTL1.ADDR[12:8] ignored). */
                case 8192uL:
                    memFrameMask = 0x60u;
                    break;
                /* "0b1110000":  4 KB memory region (VU_CTL1.ADDR[11:8] ignored). */
                case 4096uL:
                    memFrameMask = 0x70u;
                    break;
                /* "0b1111000":  2 KB memory region (VU_CTL1.ADDR[10:8] ignored). */
                case 2048uL:
                    memFrameMask = 0x78u;
                    break;
                /* "0b1111100":  1 KB memory region (VU_CTL1.ADDR[9:8]  ignored). */
                case 1024uL:
                    memFrameMask = 0x7Cu;
                    break;
                /* "0b1111110": 512 B memory region (VU_CTL1.ADDR[8]    ignored). */
                case 512uL:
                    memFrameMask = 0x7Eu;
                    break;
                /* "0b1111111": 256 B memory region (default for HW). */
                case 256uL:
                    memFrameMask = 0x7Fu;
                    break;
                default:
            /* Unknown mask */
                    break;
            }

            if (memFrameMask != 0xFFFFFFFFuL)
            {
                #if !defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
                if (!(CY_CRYPTO_V1))
                {
                    memAlignMask = vuMemSize - 1uL;
                }
                #endif

                /* Use the new address when it aligned to appropriate memory block size */
                if (((uint32_t)vuMemAddr & (memAlignMask)) == 0uL)
                {
                    #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
                    if (!(CY_CRYPTO_V1))
                    {
                        REG_CRYPTO_VU_CTL2(base) = _VAL2FLD(CRYPTO_V2_VU_CTL2_MASK, memFrameMask);
                    }
                    #endif

                    REG_CRYPTO_VU_CTL1(base) = (uint32_t)vuMemAddr;

                    /* Set the stack pointer to the Crypto buff size, in words */
                    CY_CRYPTO_VU_SET_REG(base, CY_CRYPTO_VU_HW_REG15, vuMemSize / 4u, 1u);

                    cy_cryptoVuMemSize = vuMemSize;

                    resultVal = CY_CRYPTO_SUCCESS;
                }
            }
        }
#if !defined(CY_CRYPTO_CFG_HW_USE_MPN_SPECIFIC)
    }
#endif
    return resultVal;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_GetVuMemorySize
****************************************************************************//**
*
* Get Crypto memory buffer size
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The current MEM_BUFF size in bytes.
*
*******************************************************************************/
uint32_t Cy_Crypto_Core_GetVuMemorySize(CRYPTO_Type *base)
{
    uint32_t memSize = CY_CRYPTO_MEM_BUFF_SIZE;

#if !defined(CY_CRYPTO_CFG_HW_USE_MPN_SPECIFIC)
    if ( (cy_cryptoIP != NULL) && (cy_cryptoVuMemSize != 0uL))
    {
#endif
        if (CY_CRYPTO_V1)
        {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
            memSize = cy_cryptoVuMemSize;
        #endif
        }
        else
        {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
            uint32_t memFrameMask = _FLD2VAL(CRYPTO_V2_VU_CTL2_MASK, REG_CRYPTO_VU_CTL2(base));
            /*
            Specifies the size of  the vector operand memory region.
            Legal values:
            "0b0000000":  32 KB memory region.
            "0b1000000":  16 KB memory region.
            "0b1100000":   8 KB memory region.
            "0b1110000":   4 KB memory region.
            "0b1111000":   2 KB memory region.
            "0b1111100":   1 KB memory region.
            "0b1111110": 512  B memory region.
            "0b1111111": 256  B memory region.
            */
            switch (memFrameMask)
            {
                case 0x0u:
                    memSize = 32768uL;
                    break;
                case 0x40u:
                    memSize = 16384uL;
                    break;
                case 0x60u:
                    memSize = 8192uL;
                    break;
                case 0x70u:
                    memSize = 4096uL;
                    break;
                case 0x78u:
                    memSize = 2048uL;
                    break;
                case 0x7Cu:
                    memSize = 1024uL;
                    break;
                case 0x7Eu:
                    memSize = 512uL;
                    break;
                case 0x7Fu:
                    memSize = 256uL;
                    break;
                default:
            /* Unknown mask */
                    break;
            }
        #endif
        }
#if !defined(CY_CRYPTO_CFG_HW_USE_MPN_SPECIFIC)
    }
#endif

    (void)base; /* Suppress a compiler warning about unused variables */

    return memSize;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Enable
****************************************************************************//**
*
* The function to enable the Crypto hardware.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* Crypto status \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCoreStartCryptoUse
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_Enable(CRYPTO_Type *base)
{
    #if !defined(CY_CRYPTO_CFG_HW_USE_MPN_SPECIFIC)
    Cy_Crypto_Core_HwInit();
    #endif

    /* Disable Crypto HW */
    REG_CRYPTO_CTL(base) &= ~(_VAL2FLD(CRYPTO_CTL_ENABLED,  1uL));

    if (CY_CRYPTO_V1)
    {
        /* Enable Crypto HW */
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        REG_CRYPTO_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_CTL_PWR_MODE, CY_CRYPTO_PWR_MODE_ENABLED) |
                               _VAL2FLD(CRYPTO_CTL_ENABLED,  1uL));
        #endif
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        REG_CRYPTO_CTL(base) &= ~(_VAL2FLD(CRYPTO_V2_CTL_ENABLED,  1uL) | _VAL2FLD(CRYPTO_V2_CTL_ECC_EN, 1uL));

        REG_CRYPTO_INSTR_FF_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_INSTR_FF_CTL_BLOCK, 1u)
                                              | _VAL2FLD(CRYPTO_V2_INSTR_FF_CTL_CLEAR, 0u)
                                              | _VAL2FLD(CRYPTO_V2_INSTR_FF_CTL_EVENT_LEVEL, 1u));

        REG_CRYPTO_CTL(base) |= _VAL2FLD(CRYPTO_V2_CTL_ENABLED,  1uL);

        REG_CRYPTO_RAM_PWR_CTL(base) = (uint32_t)(CY_CRYPTO_PWR_MODE_ENABLED);
        #endif
    }

    /*
    Specifies if a conditional instruction is executed or not, when its condition
    code evaluates to false("0"):
      "0": The instruction is NOT executed. As a result, the instruction may be
           handled faster than when it is executed.
      "1": The instruction is executed, but the execution result (including
           status field information) is not reflected in the IP. The instruction
           is handled just as fast as when it is executed.
    */
    REG_CRYPTO_VU_CTL0(base) = (uint32_t)1u;

    if (0uL == cy_cryptoVuMemSize)
    {
        /* Set the memory address and set stack pointer to the Crypto buff size, in words */
        (void)Cy_Crypto_Core_SetVuMemoryAddress(base, REG_CRYPTO_MEM_BUFF(base), CY_CRYPTO_MEM_BUFF_SIZE);
    }

    /* Clear whole register file */
    Cy_Crypto_Core_ClearVuRegisters(base);

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_GetLibInfo
****************************************************************************//**
*
* Get Crypto service information
*
* \param libInfo
* The pointer to a variable to store gathered crypto library information.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_GetLibInfo(cy_en_crypto_lib_info_t *libInfo)
{
    *libInfo = (cy_en_crypto_lib_info_t)CY_CRYPTO_SERVICE_LIBRARY_LEVEL;

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Disable
****************************************************************************//**
*
* Disables the operation of the CRYPTO block.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCoreStopCryptoUse
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_Disable(CRYPTO_Type *base)
{
    /* Power-off Crypto RAM */
    if (CY_CRYPTO_V1)
    {
        /* Disable Crypto HW */
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        REG_CRYPTO_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_CTL_PWR_MODE, CY_CRYPTO_PWR_MODE_OFF) |
                               _VAL2FLD(CRYPTO_CTL_ENABLED, 0uL));
        #endif
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        REG_CRYPTO_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_CTL_ENABLED,  0uL));
        REG_CRYPTO_RAM_PWR_CTL(base) = (uint32_t)(CY_CRYPTO_PWR_MODE_OFF);
        #endif
    }

    cy_cryptoVuMemSize = 0uL;

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_InvertEndianness
****************************************************************************//**
*
* This function reverts byte-array memory block, like:<br>
* inArr[0] <---> inArr[n]<br>
* inArr[1] <---> inArr[n-1]<br>
* inArr[2] <---> inArr[n-2]<br>
* ........................<br>
* inArr[n/2] <---> inArr[n/2-1]<br>
*
* Odd or even byteSize are acceptable.
*
* \param inArrPtr
* The pointer to the memory whose endianness is to be inverted.
*
* \param byteSize
* The length of the memory array whose endianness is to be inverted (in bytes)
*
*******************************************************************************/
void Cy_Crypto_Core_InvertEndianness(void *inArrPtr, uint32_t byteSize)
{
    int32_t limit;
    int32_t i;
    int32_t j = 0;
    uint8_t temp;
    uint8_t *tempPtr = (uint8_t*)inArrPtr;

    if (byteSize > 1u)
    {
        limit = (int32_t)byteSize / 2;
        if (0u == (byteSize % 2u))
        {
            --limit;
        }

        j = 0;
        i = (int32_t)byteSize - 1;
        while ( i > limit)
        {
            temp = tempPtr[j];
            tempPtr[j] = tempPtr[i];
            tempPtr[i] = temp;

            --i;
            ++j;
        }
    }
}

/** \} group_crypto_lld_hw_functions */

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 14.3');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
