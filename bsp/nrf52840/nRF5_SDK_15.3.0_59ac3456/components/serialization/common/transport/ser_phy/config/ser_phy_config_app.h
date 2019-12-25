/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#ifndef SER_PHY_CONFIG_APP_H__
#define SER_PHY_CONFIG_APP_H__

#include "boards.h"
#include "ser_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SPI_MASTER_0_ENABLE)
#define SER_PHY_SPI_MASTER SPI_MASTER_0
#endif
#if defined(SPI_MASTER_1_ENABLE)
#define SER_PHY_SPI_MASTER SPI_MASTER_1
#endif
#if defined(SPI_MASTER_2_ENABLE)
#define SER_PHY_SPI_MASTER SPI_MASTER_2
#endif

#if (defined(SPI0_ENABLED) && (SPI0_ENABLED == 1)) || defined(SPI_MASTER_0_ENABLE)

#define SER_PHY_SPI_MASTER_INSTANCE             NRF_DRV_SPI_INSTANCE(0)
#define SER_PHY_SPI_MASTER_PIN_SCK              SER_APP_SPIM0_SCK_PIN
#define SER_PHY_SPI_MASTER_PIN_MISO             SER_APP_SPIM0_MISO_PIN
#define SER_PHY_SPI_MASTER_PIN_MOSI             SER_APP_SPIM0_MOSI_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_SELECT     SER_APP_SPIM0_SS_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST    SER_APP_SPIM0_REQ_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_READY      SER_APP_SPIM0_RDY_PIN

#elif (defined(SPI1_ENABLED) && (SPI1_ENABLED == 1)) || defined(SPI_MASTER_1_ENABLE)

#define SER_PHY_SPI_MASTER_INSTANCE             NRF_DRV_SPI_INSTANCE(1)
#define SER_PHY_SPI_MASTER_PIN_SCK              SER_APP_SPIM1_SCK_PIN
#define SER_PHY_SPI_MASTER_PIN_MISO             SER_APP_SPIM1_MISO_PIN
#define SER_PHY_SPI_MASTER_PIN_MOSI             SER_APP_SPIM1_MOSI_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_SELECT     SER_APP_SPIM1_SS_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST    SER_APP_SPIM1_REQ_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_READY      SER_APP_SPIM1_RDY_PIN

#elif (defined(SPI2_ENABLED) && (SPI2_ENABLED == 1)) || defined(SPI_MASTER_2_ENABLE)

#define SER_PHY_SPI_MASTER_INSTANCE             NRF_DRV_SPI_INSTANCE(2)
#define SER_PHY_SPI_MASTER_PIN_SCK              SER_APP_SPIM2_SCK_PIN
#define SER_PHY_SPI_MASTER_PIN_MISO             SER_APP_SPIM2_MISO_PIN
#define SER_PHY_SPI_MASTER_PIN_MOSI             SER_APP_SPIM2_MOSI_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_SELECT     SER_APP_SPIM2_SS_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_REQUEST    SER_APP_SPIM2_REQ_PIN
#define SER_PHY_SPI_MASTER_PIN_SLAVE_READY      SER_APP_SPIM2_RDY_PIN

#endif

#define CONN_CHIP_RESET_PIN_NO                  SER_CONN_CHIP_RESET_PIN /**< Pin used for reseting the connectivity. */

/* UART configuration */
#define UART_IRQ_PRIORITY                       APP_IRQ_PRIORITY_MID
#define SER_PHY_UART_RX                         SER_APP_RX_PIN
#define SER_PHY_UART_TX                         SER_APP_TX_PIN
#define SER_PHY_UART_CTS                        SER_APP_CTS_PIN
#define SER_PHY_UART_RTS                        SER_APP_RTS_PIN


#ifdef __cplusplus
}
#endif

#endif // SER_PHY_CONFIG_APP_H__
