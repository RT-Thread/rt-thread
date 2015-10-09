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

#ifndef __FSL_CRC_DRIVER_H__
#define __FSL_CRC_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_crc_hal.h"
#if FSL_FEATURE_SOC_CRC_COUNT

/*!
 * @addtogroup crc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of base addresses for the CRC instances. */
extern CRC_Type * const g_crcBase[CRC_INSTANCE_COUNT];

/*!
 * @brief Defines a structure to initialize the CRC module.
 *
 * This structure holds the configuration for the CRC.
 * @internal gui name="CRC configuration" id="crcCfg"
 */
typedef struct _crc_user_config
{
    crc_prot_width_t crcWidth;      /*!< Selects 16 or 32-bit CRC protocol @internal gui name="Width" id="crcWidth" */
    uint32_t seed;                  /*!< Value of the seed (initial) CRC value @internal gui name="Seed" id="seed" */
    uint32_t polynomial;            /*!< Value of the polynomial for the CRC calculation @n Example polynomial: 0x1021 = 1_0000_0010_0001 = x^12+x^5+1 @internal gui name="Polynomial" id="polynomial" */
    crc_transpose_t writeTranspose; /*!< Defines transpose configuration of the data written to the CRC data register @internal gui name="Write transpose" id="writeTranspose" */
    crc_transpose_t readTranspose;  /*!< Defines transpose configuration of the value read from the CRC data register @internal gui name="Read transpose" id="readTranspose" */
    bool complementRead;            /*!< Enables complement read of CRC data register @internal gui name="Complement read" id="complementRead" */
} crc_user_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
 * API
 *****************************************************************************/

/*!
 * @brief Initializes the CRC module.
 *
 * This API 
 * should be called with the initial configuration before any other operations.
 *
 * @param instance CRC instance ID.
 * @param userConfigPtr Pointer to structure of initialization, see to "crc_user_config_t".
 * @return Execution status.
 */
crc_status_t CRC_DRV_Init(uint32_t instance, const crc_user_config_t *userConfigPtr);

/*!
 * @brief CRC_DRV_Deinit
 *
 * Shuts down the CRC instance.
 *
 * @param instance CRC instance ID.
 * @return Execution status.
 */
void CRC_DRV_Deinit(uint32_t instance);

/*!
 * @brief CRC_DRV_GetCrcBlock
 *
 * This function appends a block of bytes to the current CRC calculation
 * and returns a new result.
 *
 * @param instance CRC instance ID.
 * @param data data for current CRC calculation
 * @param dataLen length of data to be calculated
 * @return Execution status.
 */
uint32_t CRC_DRV_GetCrcBlock(uint32_t instance, uint8_t *data, uint32_t dataLen);

/*!
 * @brief CRC_DRV_Configure
 *
 * This function configures the CRC module from a user configuration structure.
 *
 * @param instance CRC instance ID.
 * @param userConfigPtr Pointer to structure of initialization, see to "crc_user_config_t".
 * @return Execution status.
 */
crc_status_t CRC_DRV_Configure(uint32_t instance, const crc_user_config_t *userConfigPtr);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif
#endif /* __FSL_CRC_DRIVER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/
