/*
 * Copyright (c) Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 *   3. Neither the name of Nordic Semiconductor ASA nor the names of other
 *   contributors to this software may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 *   4. This software must only be used in a processor manufactured by Nordic
 *   Semiconductor ASA, or in a processor manufactured by a third party that
 *   is used in combination with a processor manufactured by Nordic Semiconductor.
 *
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
 *
 */
 /**
  @addtogroup nrf_sdm_api
  @{
  @defgroup nrf_sdm_error SoftDevice Manager Error Codes
  @{

  @brief Error definitions for the SDM API
*/

/* Header guard */
#ifndef NRF_ERROR_SDM_H__
#define NRF_ERROR_SDM_H__

#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_ERROR_SDM_LFCLK_SOURCE_UNKNOWN              (NRF_ERROR_SDM_BASE_NUM + 0)  ///< Unknown LFCLK source.
#define NRF_ERROR_SDM_INCORRECT_INTERRUPT_CONFIGURATION (NRF_ERROR_SDM_BASE_NUM + 1)  ///< Incorrect interrupt configuration (can be caused by using illegal priority levels, or having enabled SoftDevice interrupts).
#define NRF_ERROR_SDM_INCORRECT_CLENR0                  (NRF_ERROR_SDM_BASE_NUM + 2)  ///< Incorrect CLENR0 (can be caused by erroneous SoftDevice flashing).

#ifdef __cplusplus
}
#endif
#endif // NRF_ERROR_SDM_H__

/**
  @}
  @}
*/
