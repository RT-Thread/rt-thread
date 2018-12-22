/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
#ifndef __ECSPI_IFC_HDR__
#define __ECSPI_IFC_HDR__

#include "sdk.h"

//! @addtogroup diag_spi
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Enumeration of available eCSPI module instances.
//!
//! Pass one of these values to the @a dev parameter of the driver APIs.
typedef enum {
    DEV_ECSPI1 = 1,
    DEV_ECSPI2 = 2,
    DEV_ECSPI3 = 3,
    DEV_ECSPI4 = 4,
    DEV_ECSPI5 = 5
} dev_ecspi_e;

//! @brief eCSPI port configuration settings.
//!
//! The pre-divider value should be the actual desired divider values. That is,
//! use a value of 1 to divide by 1, a value of 4 to divide by 4, and so on. This may
//! seem obvious, but the eCSPI divider register is set to the divisor minus 1 such that
//! a value of 0 equals an actual divisor of 1. In contrast, the post divider is the power
//! of 2 that will be divided by. For instance, a post_div of 3 will divide by 2^3=8.
//! pre_div ranges from 1-16, while post_div ranges from 0-15 (thus resulting in a divisor
//! of 2^0=1 through 2^15=65536).
typedef struct {
    unsigned channel:2;     //!< SS channel
    unsigned mode:1;        //!< 0: slave, 1: master
    unsigned ss_pol:1;      //!< 0: active low, 1: active high
    unsigned sclk_pol:1;    //!< 0: active high, 1: active low
    unsigned sclk_pha:1;    //!< 0: phase 0 op, 1: phase 1 op
    unsigned pre_div:5;     //!< Clock pre-divider, from 1-16
    unsigned post_div:4;    //!< Clock post-divider, from 0-15, actual divisor = 2^post_div
    unsigned _reserved:17;  //!< Reserved.
} param_ecspi_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Open and initialize eCSPI device
 *
 * @param dev eCSPI port number.
 * @param param Device configuration.
 *
 * @return TRUE on success, FALSE on failure
 */
int ecspi_open(dev_ecspi_e dev, const param_ecspi_t * param);

/*!
 * @brief Close/disable eCSPI device.
 *
 * @param dev eCSPI port.
 *
 * @return TRUE on success, FALSE on failure
 */
int ecspi_close(dev_ecspi_e dev);

/*!
 * @brief Reconfigure eCSPI device.
 *
 * @param instance eCSPI port number.
 * @param param Device configuration.
 *
 * @return TRUE on success, FALSE on failure
 */
int ecspi_configure(dev_ecspi_e instance, const param_ecspi_t * param);

/*!
 * @brief Transfer from/to target device.
 *
 * @param device eCSPI port.
 * @param tx_buf Source buffer that contain data to send.
 * @param rx_buf Buffer that store data received.
 * @param brs_bts Burst length in bits.
 *
 * @return TRUE on success, FALSE on failure
 */
int ecspi_xfer(dev_ecspi_e dev, const uint8_t * tx_buf, uint8_t * rx_buf, uint16_t brs_bts);

#if defined(__cplusplus)
}
#endif

//! @}

#endif // __ECSPI_IFC_HDR__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
