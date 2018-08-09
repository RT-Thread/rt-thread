/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#ifndef SER_PHY_CONFIG_CONN_H__
#define SER_PHY_CONFIG_CONN_H__

#include "boards.h"
#include "ser_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************//**
 * SER_PHY layer configuration.
 **************************************************************************************************/
#define SER_PHY_SPI_PPI_RDY_CH                  0
#define SER_PHY_SPI_GPIOTE_RDY_CH               0

#ifdef NRF_SPIS0
#define SER_PHY_SPI_SLAVE_INSTANCE              0
#else
#define SER_PHY_SPI_SLAVE_INSTANCE              1
#endif

#define SER_PHY_SPI_SLAVE_REQ_PIN               SER_CON_SPIS_REQ_PIN
#define SER_PHY_SPI_SLAVE_RDY_PIN               SER_CON_SPIS_RDY_PIN
#define SER_PHY_SPI_SLAVE_SCK_PIN               SER_CON_SPIS_SCK_PIN
#define SER_PHY_SPI_SLAVE_MISO_PIN              SER_CON_SPIS_MISO_PIN
#define SER_PHY_SPI_SLAVE_MOSI_PIN              SER_CON_SPIS_MOSI_PIN
#define SER_PHY_SPI_SLAVE_SS_PIN                SER_CON_SPIS_CSN_PIN

/* UART configuration */
#define UART_IRQ_PRIORITY                       APP_IRQ_PRIORITY_LOWEST

#define SER_PHY_UART_RX                         SER_CON_RX_PIN
#define SER_PHY_UART_TX                         SER_CON_TX_PIN
#define SER_PHY_UART_CTS                        SER_CON_CTS_PIN
#define SER_PHY_UART_RTS                        SER_CON_RTS_PIN


#ifdef __cplusplus
}
#endif

#endif // SER_PHY_CONFIG_CONN_H__
