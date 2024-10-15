/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_CRC_H_
#define FSL_CRC_H_

#include "fsl_common.h"

/*!
 * @addtogroup crc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief CRC driver version. Version 2.0.4.
 *
 * Current version: 2.0.4
 *
 * Change log:
 *
 * - Version 2.0.4
 *   - Release peripheral from reset if necessary in init function.
 * 
 * - Version 2.0.3
 *   - Fix MISRA issues
 *
 * - Version 2.0.2
 *   - Fix MISRA issues
 *
 * - Version 2.0.1
 *   - move DATA and DATALL macro definition from header file to source file
 */
#define FSL_CRC_DRIVER_VERSION (MAKE_VERSION(2, 0, 4))
/*! @} */

#ifndef CRC_DRIVER_CUSTOM_DEFAULTS
/*! @brief Default configuration structure filled by CRC_GetDefaultConfig(). Use CRC16-CCIT-FALSE as defeault. */
#define CRC_DRIVER_USE_CRC16_CCIT_FALSE_AS_DEFAULT 1
#endif

/*! @brief CRC bit width */
typedef enum _crc_bits
{
    kCrcBits16 = 0U, /*!< Generate 16-bit CRC code  */
    kCrcBits32 = 1U  /*!< Generate 32-bit CRC code  */
} crc_bits_t;

/*! @brief CRC result type */
typedef enum _crc_result
{
    kCrcFinalChecksum = 0U,       /*!< CRC data register read value is the final checksum.
                                      Reflect out and final xor protocol features are applied. */
    kCrcIntermediateChecksum = 1U /*!< CRC data register read value is intermediate checksum (raw value).
                                      Reflect out and final xor protocol feature are not applied.
                                      Intermediate checksum can be used as a seed for CRC_Init()
                                      to continue adding data to this checksum. */
} crc_result_t;

/*!
 * @brief CRC protocol configuration.
 *
 * This structure holds the configuration for the CRC protocol.
 *
 */
typedef struct _crc_config
{
    uint32_t polynomial;     /*!< CRC Polynomial, MSBit first.
                                  Example polynomial: 0x1021 = 1_0000_0010_0001 = x^12+x^5+1 */
    uint32_t seed;           /*!< Starting checksum value */
    bool reflectIn;          /*!< Reflect bits on input. */
    bool reflectOut;         /*!< Reflect bits on output. */
    bool complementChecksum; /*!< True if the result shall be complement of the actual checksum. */
    crc_bits_t crcBits;      /*!< Selects 16- or 32- bit CRC protocol. */
    crc_result_t crcResult;  /*!< Selects final or intermediate checksum return from CRC_Get16bitResult() or
                                CRC_Get32bitResult() */
} crc_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enables and configures the CRC peripheral module.
 *
 * This function enables the clock gate in the SIM module for the CRC peripheral.
 * It also configures the CRC module and starts a checksum computation by writing the seed.
 *
 * @param base CRC peripheral address.
 * @param config CRC module configuration structure.
 */
void CRC_Init(CRC_Type *base, const crc_config_t *config);

/*!
 * @brief Disables the CRC peripheral module.
 *
 * This function disables the clock gate in the SIM module for the CRC peripheral.
 *
 * @param base CRC peripheral address.
 */
static inline void CRC_Deinit(CRC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* gate clock */
    CLOCK_DisableClock(kCLOCK_Crc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * @brief Loads default values to the CRC protocol configuration structure.
 *
 * Loads default values to the CRC protocol configuration structure. The default values are as follows.
 * @code
 *   config->polynomial = 0x1021;
 *   config->seed = 0xFFFF;
 *   config->reflectIn = false;
 *   config->reflectOut = false;
 *   config->complementChecksum = false;
 *   config->crcBits = kCrcBits16;
 *   config->crcResult = kCrcFinalChecksum;
 * @endcode
 *
 * @param config CRC protocol configuration structure.
 */
void CRC_GetDefaultConfig(crc_config_t *config);

/*!
 * @brief Writes data to the CRC module.
 *
 * Writes input data buffer bytes to the CRC data register.
 * The configured type of transpose is applied.
 *
 * @param base CRC peripheral address.
 * @param data Input data stream, MSByte in data[0].
 * @param dataSize Size in bytes of the input data buffer.
 */
void CRC_WriteData(CRC_Type *base, const uint8_t *data, size_t dataSize);

/*!
 * @brief Reads the 32-bit checksum from the CRC module.
 *
 * Reads the CRC data register (either an intermediate or the final checksum).
 * The configured type of transpose and complement is applied.
 *
 * @param base CRC peripheral address.
 * @return An intermediate or the final 32-bit checksum, after configured transpose and complement operations.
 */
uint32_t CRC_Get32bitResult(CRC_Type *base);

/*!
 * @brief Reads a 16-bit checksum from the CRC module.
 *
 * Reads the CRC data register (either an intermediate or the final checksum).
 * The configured type of transpose and complement is applied.
 *
 * @param base CRC peripheral address.
 * @return An intermediate or the final 16-bit checksum, after configured transpose and complement operations.
 */
uint16_t CRC_Get16bitResult(CRC_Type *base);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* FSL_CRC_H_ */
