 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
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
 */

/******************************************************************************
 * @file     crc.h
 * @brief    Header File for CRC Driver
 * @version  V1.0
 * @date     02. June 2020
 * @model    crc
 ******************************************************************************/

#ifndef _DRV_CRC_H_
#define _DRV_CRC_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Compute the CRC-7 checksum of a buffer.
 *
 * See JESD84-A441.  Used by the MMC protocol.  Uses 0x09 as the
 * polynomial with no reflection.  The CRC is left
 * justified, so bit 7 of the result is bit 6 of the CRC.
 * init = 0; poly = 0x09 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 *
 * \return    The computed CRC7 value
 */
uint8_t csi_crc7_be(uint8_t crc, uint8_t *data, uint32_t size);

/**
 * \brief Compute the CRC-8 checksum of a buffer.
 *  init = 0 or 0xff; poly = 0x07 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC8 value
 */
uint8_t csi_crc8(uint8_t crc, uint8_t *data, size_t size);

/**
 * \brief Compute the CRC-8 checksum of a buffer.
 *  init = 0; poly = 0x31 refin = 1 refout = 1 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC8 value
 */
uint8_t csi_crc8_maxim(uint8_t crc, uint8_t *data, size_t size);

/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *   init = 0 or 0xffff; poly = 0x8005 refin = 1 refout = 1 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16(uint16_t crc, uint8_t *data, uint32_t size);

/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 1 refout = 1 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_ccitt(uint16_t crc, uint8_t *data, uint32_t size);

/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *  init = 0; poly = 0x3d65 refin = 1 refout = 1 xorout = 0xffff
 * \param[in] init_value      Crc init value
 * \param[in] data            Data buf to be calculate
 * \param[in] size            Data size
 * \return    The computed CRC16 with xorout
 */
uint16_t csi_crc16_dnp(uint16_t init_value, uint8_t *data, uint32_t size);

/**
 * \brief Compute the CRC-16 checksum of a buffer.
 *  init = 0; poly = 0x1021 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC16 without xorout
 */
uint16_t csi_crc16_itu(uint16_t crc, uint8_t *data, uint32_t size);

/**
 * \brief Compute the CRC-32 checksum of a buffer.Little-endian by bit.
 *  init = 0; poly = 0xEDB88320 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC32 without xorout
 */
uint32_t csi_crc32_le(uint32_t crc, uint8_t *data, uint32_t size);

/**
 * \brief Compute the CRC-32 checksum of a buffer.Big-endian by bit.
 *  init = 0; poly = 0x04C11DB7 refin = 0 refout = 0 xorout = 0
 * \param[in] crc      Crc init value or crc immediate result
 * \param[in] data     Data buf to be calculate
 * \param[in] size     Data size
 * \return    The computed CRC32 without xorout
 */
uint32_t csi_crc32_be(uint32_t crc, uint8_t *data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_CRC_H_ */
