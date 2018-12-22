/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Dynastream Innovations, Inc. 2012
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 * 1) Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 * 
 * 2) Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 * 
 * 3) Neither the name of Dynastream nor the names of its
 *    contributors may be used to endorse or promote products
 *    derived from this software without specific prior
 *    written permission.
 * 
 * The following actions are prohibited:
 * 1) Redistribution of source code containing the ANT+ Network
 *    Key. The ANT+ Network Key is available to ANT+ Adopters.
 *    Please refer to http://thisisant.com to become an ANT+
 *    Adopter and access the key.
 * 
 * 2) Reverse engineering, decompilation, and/or disassembly of
 *    software provided in binary form under this license.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE HEREBY
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; DAMAGE TO ANY DEVICE, LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. SOME STATES DO NOT ALLOW
 * THE EXCLUSION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THE
 * ABOVE LIMITATIONS MAY NOT APPLY TO YOU.
 * 
 */
/**@file
 * @brief Definitions.
 * This file is based on implementation originally made by Dynastream Innovations Inc. - August 2012
 * @defgroup ant_fs_client_main ANT-FS client device simulator
 * @{
 * @ingroup nrf_ant_fs_client
 *
 * @brief The ANT-FS client device simulator.
 *
 */

#ifndef DEFINES_H__
#define DEFINES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ULONG 0xFFFFFFFFu                 /**< The Max value for the type. */

/**@brief uint16_t type presentation as an union. */
typedef union
{
    uint16_t data;                            /**< The data content. */

    struct
    {
        uint8_t low;                          /**< The low byte of the data content. */
        uint8_t high;                         /**< The high byte of the data content. */
    } bytes;
} ushort_union_t;

/**@brief uint32_t type presentation as an union. */
typedef union
{
    uint32_t data;                            /**< The data content as a single variable. */
    uint8_t  data_bytes[sizeof(uint32_t)];    /**< The data content as a byte array. */

    struct
    {
        // The least significant byte of the uint32_t in this structure is referenced by byte0.
        uint8_t byte0;                        /**< Byte 0 of the data content. */
        uint8_t byte1;                        /**< Byte 1 of the data content. */
        uint8_t byte2;                        /**< Byte 2 of the data content. */
        uint8_t byte3;                        /**< Byte 3 of the data content. */
    } bytes;
} ulong_union_t;

#ifdef __cplusplus
}
#endif

#endif // DEFINES_H__

/**
 *@}
 **/
