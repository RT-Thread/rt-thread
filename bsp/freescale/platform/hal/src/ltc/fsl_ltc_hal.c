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

#include <string.h>

#include "fsl_ltc_hal.h"

#if FSL_FEATURE_SOC_LTC_COUNT

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_Init
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
void LTC_HAL_Init(LTC_Type *base)
{
    /* Reset all internal logic. */
    LTC_HAL_Command(base, kLTCCmd_ResetAll);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetKeySize
 * Description   : Set the size in bytes of the key being used for AES/DES
 *                 operations.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_SetKeySize(LTC_Type *base, uint8_t keySize)
{
    /* Only 64-bit, 128-bit, 192-bit, and 256-bit keys are supported for DES
     * and AES.  Ensure the size meets one of those criteria. */
    if ((keySize != 8) &&
        (keySize != 16) &&
        (keySize != 24) &&
        (keySize != 32)) {
        return kStatus_LTC_InvalidKeyLength;
    }

    LTC_WR_KS(base, keySize);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetDataSize
 * Description   : Set the size in bytes of the data being used for AES/DES
 *                 operations.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_SetDataSize(LTC_Type *base, uint16_t dataSize)
{
    uint16_t maxDataSize = (1 << 12) - 1;

    /* Only 12 bits of data can be written to the FIFO at a time. */
    if (dataSize > maxDataSize) {
        return kStatus_LTC_InvalidDataLength;
    }

    LTC_WR_DS(base, dataSize);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetICVSize
 * Description   : Set the size in bytes of data that is valid in the last block
 *                 ICV (integrity check value).
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_SetICVSize(LTC_Type *base, uint8_t dataSize)
{
    uint16_t maxDataSize = (1 << 5) - 1;

    /* Only 5 bits of data can be used for the ICV size. */
    if (dataSize > maxDataSize) {
        return kStatus_LTC_InvalidICVLength;
    }

    LTC_WR_ICVS(base, dataSize);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_GetStatusFlagMasked
 * Description   : Return the status of each individual flag requested.
 *
 *END**************************************************************************/
void LTC_HAL_GetStatusFlagMasked(LTC_Type *base,
                                 ltc_hal_status_flag_t in,
                                 ltc_hal_status_flag_t *out)
{
    *out = (ltc_hal_status_flag_t) ((uint32_t) in & LTC_RD_STA(base));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_GetErrorStatusFlagMasked
 * Description   : Return the status of each individual error flag requested.
 *
 *END**************************************************************************/
void LTC_HAL_GetErrorStatusFlagMasked(LTC_Type *base,
                                      ltc_hal_error_status_flag_t in,
                                      ltc_hal_error_status_flag_t *out)
{
    *out = (ltc_hal_error_status_flag_t) ((uint32_t) in & LTC_RD_ESTA(base));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_GetAADSize
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
uint8_t LTC_HAL_GetAADSize(LTC_Type *base, bool *authOnly)
{
    if(authOnly)
    {
        *authOnly = (bool) LTC_RD_AADSZ_AL(base);
    }
    return (uint8_t) LTC_RD_AADSZ_AADSZ(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetAADSize
 * Description   : Write AAD Size.
 *
 *END**************************************************************************/
void LTC_HAL_SetAADSize(LTC_Type *base, uint16_t size, bool authOnly)
{
    uint32_t aad;
    /* DS_MASK here is not a bug. AAD size field can be written with more than 4-bits, 
     * as the AAD write value, aligned to next 16 bytes boundary, is written also to the Data Size.
     * For example, I can write 22 to AADSZ, 32 will be written to Data Size and AADSZ will have value 6, which is 22 mod 16.
     */
    aad = LTC_AADSZ_AL(authOnly) | (((uint32_t)size)&LTC_DS_DS_MASK);
    LTC_AADSZ_REG(base) = aad;
}

#if FSL_FEATURE_LTC_HAS_GCM
/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_GetIVSize
 * Description   : Return the size in bytes (mod 16) of how much of the last
 *                 block of IV is valid.
 *
 *END**************************************************************************/
uint8_t LTC_HAL_GetIVSize(LTC_Type *base, bool *onlyIV)
{
    *onlyIV = (bool) LTC_RD_IVSZ_IL(base);
    return (uint8_t) LTC_RD_IVSZ_IVSZ(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetIVSize
 * Description   : Set the size of the IV to be written.  This data is added
 *                 to the data size register, which is the IV size rounded up
 *                 to the next 16-byte boundary.
 *
 *END**************************************************************************/
void LTC_HAL_SetIVSize(LTC_Type *base, uint16_t size, bool onlyIV)
{
    uint32_t iv;
    /* DS_MASK here is not a bug. IV size field can be written with more than 4-bits, 
     * as the IVSZ write value, aligned to next 16 bytes boundary, is written also to the Data Size.
     * For example, I can write 22 to IVSZ, 32 will be written to Data Size and IVSZ will have value 6, which is 22 mod 16.
     */
    iv = LTC_IVSZ_IL(onlyIV) | (((uint32_t)size)&LTC_DS_DS_MASK);
    LTC_IVSZ_REG(base) = iv;
}
#endif /* FSL_FEATURE_LTC_HAS_GCM */

#if FSL_FEATURE_LTC_HAS_PKHA
/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_SetASize
 * Description   : Sets the size in bytes of data contained in the PKHA A
 *                 register.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_PKHA_SetASize(LTC_Type *base, uint16_t size)
{
    if (size > 256) {
        return kStatus_LTC_InvalidInput;
    }

    LTC_WR_PKASZ(base, size);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_SetBSize
 * Description   : Sets the size in bytes of data contained in the PKHA B
 *                 register.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_PKHA_SetBSize(LTC_Type *base, uint16_t size)
{
    if (size > 256) {
        return kStatus_LTC_InvalidInput;
    }

    LTC_WR_PKBSZ(base, size);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_SetNSize
 * Description   : Sets the size in bytes of data contained in the PKHA N
 *                 register.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_PKHA_SetNSize(LTC_Type *base, uint16_t size)
{
    if (size > 256) {
        return kStatus_LTC_InvalidInput;
    }

    LTC_WR_PKNSZ(base, size);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_SetESize
 * Description   : Sets the size in bytes of data contained in the PKHA E
 *                 register.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_PKHA_SetESize(LTC_Type *base, uint16_t size)
{
    if (size > 256) {
        return kStatus_LTC_InvalidInput;
    }

    LTC_WR_PKESZ(base, size);

    return kStatus_LTC_Success;
}
#endif /* FSL_FEATURE_LTC_HAS_PKHA */

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetContext
 * Description   : The LTC context register is a 512 bit (64 byte) register that
 *                 holds internal context for the crypto engine.  The meaning
 *                 varies based on the algorithm and operating state being used.
 *                 This register is written by the driver/application to load
 *                 state like IV, counter, etc, and then it is updated by the
 *                 internal crypto engine as needed.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_SetContext(LTC_Type *base,
                                const uint8_t *data,
                                uint8_t dataSize,
                                uint8_t startIndex)
{
    uint8_t i;
    uint8_t j;
    uint8_t sz_left;
    
    /* Context register is 16 words in size (64 bytes).  Ensure we are only
     * writing a valid amount of data. */
    if (startIndex + (dataSize / 4) >= 16) {
        return kStatus_LTC_InvalidInput;
    }

    j=0;
    sz_left = dataSize % 4;
    for (i = startIndex; i < (startIndex + dataSize / 4); i++) {        
        LTC_WR_CTX(base, i, LTC_HAL_GetWordFromUnaligned(data + j));
        j += sizeof(uint32_t);
    }
    
    if (sz_left)    
    {
        uint32_t context_data = {0};
        memcpy(&context_data, data+j, sz_left);
        LTC_WR_CTX(base, i, context_data);
    }

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_GetContext
 * Description   : The LTC context register is a 512 bit (64 byte) register that
 *                 holds internal context for the crypto engine.  The meaning
 *                 varies based on the algorithm and operating state being used.
 *                 This register is written by the driver/application to load
 *                 state like IV, counter, etc, and then it is updated by the
 *                 internal crypto engine as needed.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_GetContext(LTC_Type *base,
                                uint8_t *dest,
                                uint8_t dataSize,
                                uint8_t startIndex)
{
    uint8_t i;
    uint8_t j;
    uint8_t sz_left;
    uint32_t rdCtx;

    /* Context register is 16 words in size (64 bytes).  Ensure we are only
     * writing a valid amount of data. */
    if (startIndex + (dataSize / 4) >= 16) {
        return kStatus_LTC_InvalidInput;
    }
    
    j = 0;
    sz_left = dataSize % 4;
    for (i = startIndex; i < (startIndex + dataSize / 4); i++) {        
        LTC_HAL_SetUnalignedFromWord(LTC_RD_CTX(base, i), dest + j);
        j+=sizeof(uint32_t);
    }
    
    if (sz_left)    
    {
        rdCtx = 0;
        rdCtx = LTC_RD_CTX(base, i);
        memcpy(dest+j, &rdCtx, sz_left);
    }

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_SetKey
 * Description   : This function writes the LTC keys into the key register.
 *                 The keys should be written before the key size.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_SetKey(LTC_Type *base, const uint8_t *key, uint8_t keySize)
{
    uint8_t i;
   
    /* Ensure key cannot be larger than 32 bytes */
    if (keySize > 32) {
        return kStatus_LTC_InvalidKeyLength;
    }

    for (i = 0; i < (keySize / 4); i++) {
      LTC_WR_KEY(base, i, LTC_HAL_GetWordFromUnaligned(key + i*sizeof(uint32_t)));
    }

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_GetKey
 * Description   : This function retrieves the LTC keys from the key register.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_GetKey(LTC_Type *base, uint8_t *key, uint8_t keySize)
{
    uint8_t i;
        
    /* Ensure key cannot be larger than 32 bytes */
    if (keySize > 32) {
        return kStatus_LTC_InvalidKeyLength;
    }

    for (i = 0; i < (keySize / 4); i++) {        
        LTC_HAL_SetUnalignedFromWord(LTC_RD_KEY(base, i), key + i*sizeof(uint32_t));
    }

    return kStatus_LTC_Success;
}

#if FSL_FEATURE_LTC_HAS_PKHA
/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WriteWordPKHA
 * Description   : This function writes one word of data to a given PKHA data
 *                 register, at the appropriate word-based index.
 *
 *END**************************************************************************/
static void LTC_HAL_WriteWordPKHA(LTC_Type *base,
                                  ltc_hal_pkha_reg_area_t reg,
                                  uint8_t index,
                                  uint32_t data)
{
    switch (reg) {
        case kLTC_PKHA_REG_A:
            LTC_WR_PKA(base, index, data);
            break;

        case kLTC_PKHA_REG_B:
            LTC_WR_PKB(base, index, data);
            break;

        case kLTC_PKHA_REG_N:
            LTC_WR_PKN(base, index, data);
            break;

        case kLTC_PKHA_REG_E:
            LTC_WR_PKE(base, index, data);
            break;

        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_ReadWordPKHA
 * Description   : This function reads one word of data from a given PKHA data
 *                 register, at the appropriate word-based index.
 *
 *END**************************************************************************/
static uint32_t LTC_HAL_ReadWordPKHA(LTC_Type *base,
                                     ltc_hal_pkha_reg_area_t reg,
                                     uint8_t index)
{
    uint32_t retval;
    
    switch (reg) {
        case kLTC_PKHA_REG_A:
            retval = LTC_RD_PKA(base, index);
            break;

        case kLTC_PKHA_REG_B:
            retval = LTC_RD_PKB(base, index);
            break;

        case kLTC_PKHA_REG_N:
            retval = LTC_RD_PKN(base, index);
            break;

        case kLTC_PKHA_REG_E:
            retval = LTC_RD_PKE(base, index);
            break;

        default:
            retval = 0;
            break;
    }
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WriteRegPKHA
 * Description   : This function writes an arbitrary amount of data to a given
 *                 PKHA data register, at the appropriate word-based index.
 *
 *END**************************************************************************/
static ltc_status_t LTC_HAL_WriteRegPKHA(LTC_Type *base,
                                         ltc_hal_pkha_reg_area_t reg,
                                         uint8_t quad,
                                         const uint8_t *data,
                                         uint16_t dataSize)
{
    /* Select the word-based start index for each quadrant of 64 bytes. */
    uint8_t startIndex = (quad * 16);
    uint32_t outWord;

    while (dataSize > 0)
    {
        if (dataSize >= sizeof(uint32_t))
        {            
            LTC_HAL_WriteWordPKHA(base, reg, startIndex++, LTC_HAL_GetWordFromUnaligned(data)/*outWord*/);
            dataSize -= sizeof(uint32_t);
            data += sizeof(uint32_t);
        }
        else if (dataSize > 0)
        {
            outWord = 0;
            memcpy(&outWord, data, dataSize);
            LTC_HAL_WriteWordPKHA(base, reg, startIndex, outWord);
            dataSize = 0;
        }
    }

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_ReadRegPKHA
 * Description   : This function reads an arbitrary amount of data from a given
 *                 PKHA data register, at the appropriate word-based index.
 *
 *END**************************************************************************/
static void LTC_HAL_ReadRegPKHA(LTC_Type *base,
                                ltc_hal_pkha_reg_area_t reg,
                                uint8_t quad,
                                uint8_t *data,
                                uint16_t dataSize)
{
    /* Select the word-based start index for each quadrant of 64 bytes. */
    uint8_t startIndex = (quad * 16);
    uint16_t calcSize;
    uint32_t word;

    while (dataSize > 0)
    {
        word = LTC_HAL_ReadWordPKHA(base, reg, startIndex++);

        calcSize = (dataSize >= sizeof(uint32_t)) ? sizeof(uint32_t) : dataSize;
        memcpy(data, &word, calcSize);

        data += calcSize;
        dataSize -= calcSize;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WritePKA
 * Description   : Write data to PKHA A register, which is up to 2048 bits in
 *                 size.  This register can only be written when the mode
 *                 register is not set for PKHA operation, otherwise reads and
 *                 writes will return zero.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WritePKA(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_A, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WriteSizedPKA
 * Description   : Same functionality as LTC_HAL_WritePKA, but also sets A size.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WriteSizedPKA(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    LTC_HAL_PKHA_SetASize(base, dataSize);
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_A, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_ReadPKA
 * Description   : Read data from PKHA A register, which is up to 2048 bits in
 *                 size.
 *
 *END**************************************************************************/
void LTC_HAL_ReadPKA(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize)
{
    LTC_HAL_ReadRegPKHA(base, kLTC_PKHA_REG_A, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WritePKB
 * Description   : Write data to PKHA B register, which is up to 2048 bits in
 *                 size.  This register can only be written when the mode
 *                 register is not set for PKHA operation, otherwise reads and
 *                 writes will return zero.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WritePKB(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_B, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WriteSizedPKB
 * Description   : Same functionality as LTC_HAL_WritePKB, but also sets B size.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WriteSizedPKB(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    LTC_HAL_PKHA_SetBSize(base, dataSize);
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_B, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_ReadPKB
 * Description   : Read data from PKHA B register, which is up to 2048 bits in
 *                 size.
 *
 *END**************************************************************************/
void LTC_HAL_ReadPKB(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize)
{
    LTC_HAL_ReadRegPKHA(base, kLTC_PKHA_REG_B, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WritePKN
 * Description   : Write data to PKHA N register, which is up to 2048 bits in
 *                 size.  This register can only be written when the mode
 *                 register is not set for PKHA operation, otherwise reads and
 *                 writes will return zero.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WritePKN(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_N, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WriteSizedPKN
 * Description   : Same functionality as LTC_HAL_WritePKN, but also sets N size.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WriteSizedPKN(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    LTC_HAL_PKHA_SetNSize(base, dataSize);
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_N, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_ReadPKN
 * Description   : Read data from PKHA N register, which is up to 2048 bits in
 *                 size.
 *
 *END**************************************************************************/
void LTC_HAL_ReadPKN(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize)
{
    LTC_HAL_ReadRegPKHA(base, kLTC_PKHA_REG_N, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WritePKE
 * Description   : Write data to PKHA E register, which is up to 2048 bits in
 *                 size.  This register can only be written when the mode
 *                 register is not set for PKHA operation, otherwise reads and
 *                 writes will return zero.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WritePKE(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_E, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_WriteSizedPKE
 * Description   : Same functionality as LTC_HAL_WritePKE, but also sets E size.
 *
 *END**************************************************************************/
ltc_status_t LTC_HAL_WriteSizedPKE(LTC_Type *base,
                              uint8_t quad,
                              const uint8_t *data,
                              uint16_t dataSize)
{
    LTC_HAL_PKHA_SetESize(base, dataSize);
    return LTC_HAL_WriteRegPKHA(base, kLTC_PKHA_REG_E, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_ReadPKE
 * Description   : Read data from PKHA E register, which is up to 2048 bits in
 *                 size.
 *
 *END**************************************************************************/
void LTC_HAL_ReadPKE(LTC_Type *base,
                     uint8_t quad,
                     uint8_t *data,
                     uint16_t dataSize)
{
    LTC_HAL_ReadRegPKHA(base, kLTC_PKHA_REG_E, quad, data, dataSize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_ModeSetSrcRegCopy
 * Description   : Set the LTC PKHA source register to perform register copy.
 *
 *END**************************************************************************/
void LTC_HAL_PKHA_ModeSetSrcRegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_reg_area_t reg)
{
    int i = 0;

    do
    {
        reg = (ltc_hal_pkha_reg_area_t)(((uint32_t)reg)>>1);
        i++;
    }while(reg);

    i = 4 - i;
    /* Source register must not be E. */
    if (i != 2)
    {
        *outMode |= ((uint32_t) i << 17);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_ModeSetDstRegCopy
 * Description : Set the LTC PKHA destination register to perform register copy.
 *
 *END**************************************************************************/
void LTC_HAL_PKHA_ModeSetDstRegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_reg_area_t reg)
{
    int i = 0;

    do
    {
        reg = (ltc_hal_pkha_reg_area_t)(((uint32_t)reg)>>1);
        i++;
    }while(reg);

    i = 4 - i;
    *outMode |= ((uint32_t) i << 10);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_ModeSetSrcSegCopy
 * Description : Set the LTC PKHA source segment to perform register copy.
 *
 *END**************************************************************************/
void LTC_HAL_PKHA_ModeSetSrcSegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_quad_area_t quad)
{
    *outMode |= ((uint32_t) quad << 8);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_HAL_PKHA_ModeSetDstSegCopy
 * Description : Set the LTC PKHA destination segment to perform register copy.
 *
 *END**************************************************************************/
void LTC_HAL_PKHA_ModeSetDstSegCopy(ltc_hal_mode_t *outMode,
                                           ltc_hal_pkha_quad_area_t quad)
{
    *outMode |= ((uint32_t) quad << 6);
}
#endif /* FSL_FEATURE_LTC_HAS_PKHA */
#endif /* FSL_FEATURE_SOC_LTC_COUNT */
