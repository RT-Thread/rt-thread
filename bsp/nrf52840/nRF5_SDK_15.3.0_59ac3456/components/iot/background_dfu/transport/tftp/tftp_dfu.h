/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @file tftp_dfu.h
 *
 * @defgroup tftp_dfu TFTP transport for Background DFU
 * @ingroup iot_tftp_dfu
 * @{
 * @brief TFTP transport for Background DFU.
 *
 */

#ifndef TFTP_DFU_H_
#define TFTP_DFU_H_

#include <stdint.h>
#include "iot_defines.h"

/** @brief Initialize DFU client.
 *
 * @returns NRF_SUCCESS if DFU procedure started. Otherwise an error code indicating problem.
 */
uint32_t tftp_dfu_init(void);

/** @brief Trigger DFU.
 *
 * @param[in]  p_host_ipv6  IPv6 address of TFTP host.
 * @param[in]  src_port     Source UDP port used by TFTP service.
 * @param[in]  dst_port     Destination UDP port used by TFTP service.
 *
 * @returns NRF_SUCCESS if DFU procedure started. Otherwise an error code indicating problem.
 */
uint32_t tftp_dfu_trigger(const ipv6_addr_t * p_host_ipv6, uint16_t src_port, uint16_t dst_port);

/** @brief Handle DFU error.
 *
 *  This function can be implemented in the application to undertake application-specific action on DFU error.
 */
extern void tftp_dfu_handle_error(void);

#endif /* TFTP_DFU_H_ */

/** @} */
