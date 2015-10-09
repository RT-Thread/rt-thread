/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#if !defined(__FSL_CRC_HAL_H__)
#define __FSL_CRC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_CRC_COUNT

/*! @addtogroup crc_hal*/
/*! @{*/

/*! @file*/

/*!*****************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief CRC status return codes.
 */
typedef enum _crc_status
{
    kStatus_CRC_Success         = 0U, /*!< Success. */
    kStatus_CRC_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_CRC_Failed          = 2U  /*!< Execution failed. */
} crc_status_t;

/*!
 * @brief Define type of enumerating transpose modes for CRC peripheral.
 */
typedef enum _crc_transpose
{
    kCrcNoTranspose    = 0U, /*!< No transposition. @internal gui name="No Transpose" */
    kCrcTransposeBits  = 1U, /*!< Bits in bytes are transposed; bytes are not transposed. @internal gui name="Transpose Bits" */
    kCrcTransposeBoth  = 2U, /*!< Both bits in bytes and bytes are transposed. @internal gui name="Transpose Bits in Bytes and Bytes" */
    kCrcTransposeBytes = 3U  /*!< Only bytes are transposed; no bits in a byte are transposed. @internal gui name="Transpose Bytes" */
}crc_transpose_t;

/*!
 * @brief Define type of enumerating CRC protocol widths for CRC peripheral.
 */
typedef enum _crc_prot_width
{
    kCrc16Bits = 0U, /*!< 16-bit CRC protocol. @internal gui name="16 bits" */
    kCrc32Bits = 1U, /*!< 32-bit CRC protocol. @internal gui name="32 bits" */
}crc_prot_width_t;

/*!*****************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name CRC-related feature APIs*/

/*!
 * @brief This function initializes the module to a known state.
 *
 * @param base The CRC peripheral base address.
 */
void CRC_HAL_Init(CRC_Type * base);

/*!
 * @brief Returns the current CRC result from the data register.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 32-bit value.
 */
static inline uint32_t CRC_HAL_GetDataReg(CRC_Type * base)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    return CRC_RD_CRC(base);
#else
    return CRC_RD_DATA(base);
#endif
}

/*!
 * @brief Returns the upper 16 bits of the current CRC result from the data register.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 16-bit value.
 */
static inline uint16_t CRC_HAL_GetDataHReg(CRC_Type * base)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    return CRC_RD_CRCH(base);
#else
    return CRC_RD_DATAH(base);
#endif
}

/*!
 * @brief Returns the lower 16 bits of the current CRC result from the data register.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 16-bit value.
 */
static inline uint16_t CRC_HAL_GetDataLReg(CRC_Type * base)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    return CRC_RD_CRCL(base);
#else
    return CRC_RD_DATAL(base);
#endif
}

/*!
 * @brief Sets the CRC data register (4 bytes).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 32-bit value.
 */
static inline void CRC_HAL_SetDataReg(CRC_Type * base, uint32_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRC(base, value);
#else
    CRC_WR_DATA(base, value);
#endif
}

/*!
 * @brief Sets the CRC data register (upper 2 bytes).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 16-bit value.
 */
static inline void CRC_HAL_SetDataHReg(CRC_Type * base, uint16_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRCH(base, value);
#else
    CRC_WR_DATAH(base, value);
#endif
}

/*!
 * @brief Sets the CRC data register (lower 2 bytes).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 16-bit value.
 */
static inline void CRC_HAL_SetDataLReg(CRC_Type * base, uint16_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRCL(base, value);
#else
    CRC_WR_DATAL(base, value);
#endif
}

/*!
 * @brief Sets the CRC data register (HL byte).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 8-bit value.
 */
static inline void CRC_HAL_SetDataHLReg(CRC_Type * base, uint8_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRCHL(base, value);
#else
    CRC_WR_DATAHL(base, value);
#endif
}

/*!
 * @brief Sets the CRC data register (HU byte).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 8-bit value.
 */
static inline void CRC_HAL_SetDataHUReg(CRC_Type * base, uint8_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRCHU(base, value);
#else
    CRC_WR_DATAHU(base, value);
#endif
}

/*!
 * @brief Sets the CRC data register (LL byte).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 8-bit value.
 */
static inline void CRC_HAL_SetDataLLReg(CRC_Type * base, uint8_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRCLL(base, value);
#else
    CRC_WR_DATALL(base, value);
#endif
}

/*!
 * @brief Sets the CRC data register (LU byte).
 *
 * @param base The CRC peripheral base address.
 * @param value New data for CRC computation. This parameter is a 8-bit value.
 */
static inline void CRC_HAL_SetDataLUReg(CRC_Type * base, uint8_t value)
{
#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRCLU(base, value);
#else
    CRC_WR_DATALU(base, value);
#endif
}

/*!
 * @brief Returns the polynomial register value.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 32-bit value.
 */
static inline uint32_t CRC_HAL_GetPolyReg(CRC_Type * base)
{
    return CRC_RD_GPOLY(base);
}

/*!
 * @brief Returns the upper 16 bits of polynomial register.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 16-bit value.
 */
static inline uint16_t CRC_HAL_GetPolyHReg(CRC_Type * base)
{
    return CRC_RD_GPOLYH(base);
}

/*!
 * @brief Returns the lower 16 bits of polynomial register.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 16-bit value.
 */
static inline uint16_t CRC_HAL_GetPolyLReg(CRC_Type * base)
{
    return CRC_RD_GPOLYL(base);
}

/*!
 * @brief Sets the polynomial register.
 *
 * @param base The CRC peripheral base address.
 * @param value Polynomial value. This parameter is a 32-bit value.
 */
static inline void CRC_HAL_SetPolyReg(CRC_Type * base, uint32_t value)
{
    CRC_WR_GPOLY(base, value);
}

/*!
 * @brief Sets the upper 16 bits of polynomial register.
 *
 * @param base The CRC peripheral base address.
 * @param value Polynomial value. This parameter is a 16-bit value.
 */
static inline void CRC_HAL_SetPolyHReg(CRC_Type * base, uint16_t value)
{
    CRC_WR_GPOLYH(base, value);
}

/*!
 * @brief Sets the lower 16 bits of polynomial register.
 *
 * @param base The CRC peripheral base address.
 * @param value Polynomial value. This parameter is a 16-bit value.
 */
static inline void CRC_HAL_SetPolyLReg(CRC_Type * base, uint16_t value)
{
    CRC_WR_GPOLYL(base, value);
}

/*!
 * @brief Returns the CRC control register.
 *
 * @param base The CRC peripheral base address.
 * @return Returns a 32-bit value.
 */
static inline uint32_t CRC_HAL_GetCtrlReg(CRC_Type * base)
{
    return CRC_RD_CTRL(base);
}

/*!
 * @brief Sets the CRC control register.
 *
 * @param base The CRC peripheral base address.
 * @param value Control register value. This parameter is a 32-bit value.
 */
static inline void CRC_HAL_SetCtrlReg(CRC_Type * base, uint32_t value)
{
    CRC_WR_CTRL(base, value);
}

/*!
 * @brief Gets the CRC seed mode.
 *
 * @param base The CRC peripheral base address.
 * @return CRC seed mode
 *         -true: Seed mode is enabled
 *         -false: Data mode is enabled
 */
static inline bool CRC_HAL_GetSeedOrDataMode(CRC_Type * base)
{
    return (bool)CRC_BRD_CTRL_WAS(base);
}

/*!
 * @brief Sets the CRC seed mode.
 *
 * @param base The CRC peripheral base address.
 * @param enable Enable or disable seed mode.
          -true: use CRC data register for seed values
          -false: use CRC data register for data values
 */
static inline void CRC_HAL_SetSeedOrDataMode(CRC_Type * base, bool enable)
{
    CRC_BWR_CTRL_WAS(base, enable);
}

/*!
 * @brief Gets the CRC transpose type for writes.
 *
 * @param base The CRC peripheral base address.
 * @return CRC input transpose type for writes.
 */
static inline crc_transpose_t CRC_HAL_GetWriteTranspose(CRC_Type * base)
{
    return (crc_transpose_t)CRC_BRD_CTRL_TOT(base);
}

/*!
 * @brief Sets the CRC transpose type for writes.
 *
 * @param base The CRC peripheral base address.
 * @param transp The CRC input transpose type.
 */
static inline void CRC_HAL_SetWriteTranspose(CRC_Type * base, crc_transpose_t transp)
{
    CRC_BWR_CTRL_TOT(base, transp);
}

/*!
 * @brief Gets the CRC transpose type for reads.
 *
 * @param base The CRC peripheral base address.
 * @return CRC output transpose type.
 */
static inline crc_transpose_t CRC_HAL_GetReadTranspose(CRC_Type * base)
{
    return (crc_transpose_t)CRC_BRD_CTRL_TOTR(base);
}

/*!
 * @brief Sets the CRC transpose type for reads.
 *
 * @param base The CRC peripheral base address.
 * @param transp The CRC output transpose type.
 */
static inline void CRC_HAL_SetReadTranspose(CRC_Type * base, crc_transpose_t transp)
{
    CRC_BWR_CTRL_TOTR(base, transp);
}

/*!
 * @brief Gets the CRC XOR mode.
 *
 * Some CRC protocols require the final checksum to be XORed with 0xFFFFFFFF
 * or 0xFFFF. XOR mode enables "on the fly" complementing of read data.
 *
 * @param base The CRC peripheral base address.
 * @return CRC XOR mode
 *         -true: XOR mode is enabled
 *         -false: XOR mode is disabled
 */
static inline bool CRC_HAL_GetXorMode(CRC_Type * base)
{
    return (bool)CRC_BRD_CTRL_FXOR(base);
}

/*!
 * @brief Sets the CRC XOR mode.
 *
 * Some CRC protocols require the final checksum to be XORed with 0xFFFFFFFF
 * or 0xFFFF. XOR mode enables "on the fly" complementing of read data.
 *
 * @param base The CRC peripheral base address.
 * @param enable Enable or disable XOR mode.
 */
static inline void CRC_HAL_SetXorMode(CRC_Type * base, bool enable)
{
    CRC_BWR_CTRL_FXOR(base, enable);
}

/*!
 * @brief Gets the CRC protocol width.
 *
 * @param base The CRC peripheral base address.
 * @return CRC protocol width
 *         -kCrc16Bits: 16-bit CRC protocol
 *         -kCrc32Bits: 32-bit CRC protocol
 */
static inline crc_prot_width_t CRC_HAL_GetProtocolWidth(CRC_Type * base)
{
    return (crc_prot_width_t)CRC_BRD_CTRL_TCRC(base);
}

/*!
 * @brief Sets the CRC protocol width.
 *
 * @param base The CRC peripheral base address.
 * @param width The CRC protocol width
 *         -kCrc16Bits: 16-bit CRC protocol
 *         -kCrc32Bits: 32-bit CRC protocol
 */
static inline void CRC_HAL_SetProtocolWidth(CRC_Type * base, crc_prot_width_t width)
{
    CRC_BWR_CTRL_TCRC(base, width);
}

/*!
 * @brief CRC_HAL_GetCrc32
 *
 * This method appends 32-bit data to the current CRC calculation
 * and returns new result. If the newSeed is true, seed set and
 * result are calculated from the seed new value (new CRC calculation).
 *
 * @param base The CRC peripheral base address.
 * @param data input data for CRC calculation
 * @param newSeed Sets new CRC calculation.
 *        - true: New seed set and used for new calculation.
 *        - false: seed argument ignored, continues old calculation.
 * @param seed New seed if newSeed is true, else ignored
 * @return new CRC result.
 */
uint32_t CRC_HAL_GetCrc32(CRC_Type * base, uint32_t data, bool newSeed, uint32_t seed);

/*!
 * @brief CRC_HAL_GetCrc16
 *
 * This method appends the 16-bit data to the current CRC calculation
 * and returns a new result. If the newSeed is true, seed set and
 * result are calculated from the seed new value (new CRC calculation).
 *
 * @param base The CRC peripheral base address.
 * @param data input data for CRC calculation
 * @param newSeed Sets new CRC calculation.
 *        - true: New seed set and used for new calculation.
 *        - false: seed argument ignored, continues old calculation.
 * @param seed New seed if newSeed is true, else ignored
 * @return new CRC result.
 */
uint32_t CRC_HAL_GetCrc16(CRC_Type * base, uint16_t data, bool newSeed, uint32_t seed);

/*!
 * @brief CRC_HAL_GetCrc8
 *
 * This method appends the 8-bit data to the current CRC calculation
 * and returns the new result. If the newSeed is true, seed set and
 * result are calculated from the seed new value (new CRC calculation).
 *
 * @param base The CRC peripheral base address.
 * @param data input data for CRC calculation
 * @param newSeed Sets new CRC calculation.
 *        - true: New seed set and used for new calculation.
 *        - false: seed argument ignored, continues old calculation.
 * @param seed New seed if newSeed is true, else ignored
 * @return new CRC result.
 */
uint32_t CRC_HAL_GetCrc8(CRC_Type * base, uint8_t data, bool newSeed, uint32_t seed);

/*!
 * @brief CRC_HAL_GetCrcResult
 *
 * This method returns the current result of the CRC calculation.
 * The result is the ReadTranspose dependent.
 *
 * @param base The CRC peripheral base address.
 * @return result of CRC calculation.
 */
uint32_t CRC_HAL_GetCrcResult(CRC_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_CRC_HAL_H__*/
