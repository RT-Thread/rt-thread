/***************************************************************************//**
* \file cy_crypto_core_crc_v2.c
* \version 2.70
*
* \brief
*  This file provides the source code for CRC API
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

#if defined(CY_IP_MXCRYPTO)

#include "cy_crypto_core_crc_v2.h"

#if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C)

#include "cy_crypto_core_hw_v2.h"
#include "cy_syslib.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 3, \
'CRYPTO_Type will typecast to either CRYPTO_V1_Type or CRYPTO_V2_Type but not both on PDL initialization based on the target device at compile time.');

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc_Init
****************************************************************************//**
*
* Initializes CRC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param polynomial
* The polynomial (specified using 32 bits) used in the computing CRC.
*
* \param dataReverse
* The order in which data bytes are processed. 0 - MSB first; 1- LSB first.
*
* \param dataXor
* The byte mask for XORing data
*
* \param remReverse
* A remainder reverse: 0 means the remainder is not reversed. 1 means reversed.
*
* \param remXor
* Specifies a mask with which the LFSR32 register is XORed to produce a remainder.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc_Init(CRYPTO_Type *base,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor)
{

    /* Specifies the bit order in which a data Byte is processed
     * (reversal is performed after XORing):
     *                                       '0': Most significant bit (bit 1) first.
     *                                       '1': Least significant bit (bit 0) first. */
    REG_CRYPTO_CRC_CTL(base) = (uint32_t)( (_VAL2FLD(CRYPTO_V2_CRC_CTL_DATA_REVERSE, dataReverse)) |
                                           (_VAL2FLD(CRYPTO_V2_CRC_CTL_REM_REVERSE,  remReverse)) );

    /* Specifies a byte mask with which each data byte is XORed.
     * The XOR is performed before data reversal. */
    REG_CRYPTO_CRC_DATA_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_CRC_DATA_CTL_DATA_XOR, dataXor));

    /* CRC polynomial. The polynomial is represented WITHOUT the high order bit
     * (this bit is always assumed '1'). */
    REG_CRYPTO_CRC_POL_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_CRC_POL_CTL_POLYNOMIAL, polynomial));

    /*Specifies a mask with which the CRC_LFSR_CTL.LFSR32 register is XORed to produce a remainder.
     * The XOR is performed before remainder reversal. */
    REG_CRYPTO_CRC_REM_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_CRC_REM_CTL_REM_XOR, remXor));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc
****************************************************************************//**
*
* Performs CRC calculation on a message.
*
* For CAT1C devices when D-Cache is enabled parameter data must align and end in 32 byte boundary.
* For CAT1A and CAT1C devices with DCache disabled, crc must be 4-Byte aligned.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param crc
* The pointer to a computed CRC value.
*
* \param data
* The pointer to the message whose CRC is being computed.
*
* \param dataSize
* The size of a message in bytes.
*
* \param lfsrInitState
* The initial state of the LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc(CRYPTO_Type *base,
                                        uint32_t *crc,
                                        void      const *data,
                                        uint32_t  dataSize,
                                        uint32_t  lfsrInitState)
{
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)data,(int32_t)dataSize);
#endif
    /* Fill the FIFO with the instruction parameters */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, (uint8_t const *)data, dataSize);

    /* A state of 32-bit Linear Feedback Shift Registers (LFSR) used to implement CRC. */
    REG_CRYPTO_RESULT(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_RESULT_DATA, lfsrInitState));

    /* Issue the CRC instruction */
    Cy_Crypto_Core_V2_Run(base, CY_CRYPTO_V2_CRC_OPC);

    /* Wait until CRC instruction is complete */
    Cy_Crypto_Core_V2_Sync(base);

    /* Copy the result from the CRC_REM_RESULT register */
    *crc = (uint32_t)_FLD2VAL(CRYPTO_V2_CRC_REM_RESULT_REM, REG_CRYPTO_CRC_REM_RESULT(base));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc_CalcInit
****************************************************************************//**
*
* Initializes the CRC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param polynomial
* The polynomial (specified using 32 bits) used in the computing CRC.
*
* \param dataReverse
* The order in which data bytes are processed. 0 - MSB first; 1- LSB first.
*
* \param dataXor
* The byte mask for XORing data.
*
* \param remReverse
* The remainder reverse: 0 means the remainder is not reversed; 1 means it is reversed.
*
* \param remXor
* Specifies the mask with which the LFSR32 register is XORed to produce a remainder.
*
* \param lfsrInitState
* The initial state of the LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc_CalcInit(CRYPTO_Type *base,
                                        uint32_t width,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor,
                                        uint32_t lfsrInitState)
{
    CY_ASSERT_L1((width >= 1U) && (width <= CY_CRYPTO_HW_REGS_WIDTH));

    /* Specifies the bit order in which a data byte is processed
     * (reversal is performed after XORing):
     *                                       '0': Most significant bit (bit 1) first.
     *                                       '1': Least significant bit (bit 0) first. */
    REG_CRYPTO_CRC_CTL(base) = (uint32_t)( (_VAL2FLD(CRYPTO_V2_CRC_CTL_DATA_REVERSE, dataReverse)) |
                                           (_VAL2FLD(CRYPTO_V2_CRC_CTL_REM_REVERSE,  remReverse)) );

    /* Specifies the byte mask with which each data byte is XORed.
     * The XOR is performed before data reversal. */
    REG_CRYPTO_CRC_DATA_CTL(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_CRC_DATA_CTL_DATA_XOR, dataXor));

    /* The CRC polynomial. The polynomial is represented WITHOUT the high-order bit
     * (this bit is always assumed '1'). */
    REG_CRYPTO_CRC_POL_CTL(base) =
        (uint32_t)(_VAL2FLD(CRYPTO_V2_CRC_POL_CTL_POLYNOMIAL, polynomial << (CY_CRYPTO_HW_REGS_WIDTH - width)));

    /*Specifies the mask with which the CRC_LFSR_CTL.LFSR32 register is XORed to produce a remainder.
     * The XOR is performed before remainder reversal. */
    REG_CRYPTO_CRC_REM_CTL(base) =
        (uint32_t)(_VAL2FLD(CRYPTO_V2_CRC_REM_CTL_REM_XOR, remXor << (CY_CRYPTO_HW_REGS_WIDTH - width)));

    /* The state of 32-bit Linear Feedback Shift Registers (LFSR) used to implement the CRC. */
    REG_CRYPTO_RESULT(base) =
        (uint32_t)(_VAL2FLD(CRYPTO_V2_RESULT_DATA, lfsrInitState << (CY_CRYPTO_HW_REGS_WIDTH - width)));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc_CalcStart
****************************************************************************//**
*
* Prepares the CRC calculation by setting an initial seed value.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param lfsrInitState
* The initial state of the LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc_CalcStart(CRYPTO_Type *base, uint32_t width, uint32_t  lfsrInitState)
{
    CY_ASSERT_L1((width >= 1U) && (width <= CY_CRYPTO_HW_REGS_WIDTH));

    /* The state of 32-bit Linear Feedback Shift Registers (LFSR) used to implement the CRC. */
    REG_CRYPTO_RESULT(base) = (uint32_t)(_VAL2FLD(CRYPTO_V2_RESULT_DATA, lfsrInitState << (CY_CRYPTO_HW_REGS_WIDTH - width)));

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc_CalcPartial
****************************************************************************//**
*
* Performs the CRC calculation of a message part.
*
* For CAT1C devices when D-Cache is enabled parameter data must align and end in 32 byte boundary.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param data
* The pointer to the message whose CRC is being computed.
*
* \param dataSize
* The size of a message in bytes.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc_CalcPartial(CRYPTO_Type *base,
                                        void const *data, uint32_t  dataSize)
{
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    /* Flush the cache */
    SCB_CleanDCache_by_Addr((volatile void *)data,(int32_t)dataSize);
#endif

    /* Fills the FIFO with the instruction parameters. */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, (uint8_t const *)data, dataSize);

    /* Issues the CRC instruction. */
    Cy_Crypto_Core_V2_Run(base, CY_CRYPTO_V2_CRC_OPC);

    /* Waits until the CRC instruction is complete. */
    Cy_Crypto_Core_V2_Sync(base);

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc_CalcFinish
****************************************************************************//**
*
* Finalizes the CRC calculation.
*
* For CAT1A and CAT1C devices with DCache disabled, crc must be 4-Byte aligned.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param crc
* The pointer to a computed CRC value.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc_CalcFinish(CRYPTO_Type *base, uint32_t width, uint32_t *crc)
{
    CY_ASSERT_L1((width >= 1U) && (width <= CY_CRYPTO_HW_REGS_WIDTH));

    uint32_t calculatedCrc;

    /* Copies the result from the CRC_REM_RESULT register. */
    calculatedCrc = (uint32_t)_FLD2VAL(CRYPTO_V2_CRC_REM_RESULT_REM, REG_CRYPTO_CRC_REM_RESULT(base));

    /* NOTE The calculated CRC value is MSB-aligned and should be shifted WHEN CRC_DATA_REVERSE is zero. */
    if (_FLD2VAL(CRYPTO_V2_CRC_CTL_REM_REVERSE, REG_CRYPTO_CRC_CTL(base)) == 0U)
    {
        calculatedCrc = calculatedCrc >> (CY_CRYPTO_HW_REGS_WIDTH - width);
    }

    *crc = calculatedCrc;

    return (CY_CRYPTO_SUCCESS);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V2_Crc_Calc
****************************************************************************//**
*
* Performs the CRC calculation on a message.
*
* For CAT1C devices when D-Cache is enabled parameter data must align and end in 32 byte boundary.
* For CAT1A and CAT1C devices with DCache disabled, crc must be 4-Byte aligned.
*
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param crc
* The pointer to a computed CRC value.
*
* \param data
* The pointer to the message whose CRC is being computed.
*
* \param dataSize
* The size of a message in bytes.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V2_Crc_Calc(CRYPTO_Type *base,
                                        uint32_t  width,
                                        uint32_t *crc,
                                        void      const *data,
                                        uint32_t  dataSize)
{
    CY_ASSERT_L1((width >= 1U) && (width <= CY_CRYPTO_HW_REGS_WIDTH));

    uint32_t calculatedCrc;
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        /* Flush the cache */
        SCB_CleanDCache_by_Addr((volatile void *)data,(int32_t)dataSize);
#endif

    /* Fills the FIFO with the instruction parameters. */
    Cy_Crypto_Core_V2_FFStart(base, CY_CRYPTO_V2_RB_FF_LOAD0, (uint8_t const *)data, dataSize);

    /* Issues the CRC instruction. */
    Cy_Crypto_Core_V2_Run(base, CY_CRYPTO_V2_CRC_OPC);

    /* Waits until the CRC instruction is complete. */
    Cy_Crypto_Core_V2_Sync(base);

    /* Copies the result from the CRC_REM_RESULT register. */
    calculatedCrc = (uint32_t)_FLD2VAL(CRYPTO_V2_CRC_REM_RESULT_REM, REG_CRYPTO_CRC_REM_RESULT(base));

    /* NOTE The calculated CRC value is MSB-aligned and should be shifted WHEN CRC_DATA_REVERSE is zero. */
    if (_FLD2VAL(CRYPTO_V2_CRC_CTL_REM_REVERSE, REG_CRYPTO_CRC_CTL(base)) == 0U)
    {
        calculatedCrc = calculatedCrc >> (CY_CRYPTO_HW_REGS_WIDTH - width);
    }

    *crc = calculatedCrc;

    return (CY_CRYPTO_SUCCESS);
}
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#endif /* (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
