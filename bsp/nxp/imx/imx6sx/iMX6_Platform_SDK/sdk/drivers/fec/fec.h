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

#ifndef __FEC_H__
#define __FEC_H__

#include "registers/regsfec.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Definitions of the event bits.
enum {
    FEC_EVENT_HBERR = 0x80000000,
    FEC_EVENT_BABR = BM_FEC_EIR_BABR,
    FEC_EVENT_BABT = BM_FEC_EIR_BABT,
    FEC_EVENT_GRA = BM_FEC_EIR_GRA,
    FEC_EVENT_TXF = BM_FEC_EIR_TXF,
    FEC_EVENT_TXB = BM_FEC_EIR_TXB,
    FEC_EVENT_RXF = BM_FEC_EIR_RXF,
    FEC_EVENT_RXB = BM_FEC_EIR_RXB,
    FEC_EVENT_MII = BM_FEC_EIR_MII,
    FEC_EVENT_EBERR = BM_FEC_EIR_EBERR,
    FEC_EVENT_LC = BM_FEC_EIR_LC,
    FEC_EVENT_RL = BM_FEC_EIR_RL,
    FEC_EVENT_UN = BM_FEC_EIR_UN,
    FEC_EVENT_TX = FEC_EVENT_TXF,
    FEC_EVENT_TX_ERR = (FEC_EVENT_BABT | FEC_EVENT_LC | FEC_EVENT_RL | FEC_EVENT_UN),
    FEC_EVENT_RX = FEC_EVENT_RXF,
    FEC_EVENT_ERR = (FEC_EVENT_HBERR | FEC_EVENT_EBERR)
};

//! @brief MII type
enum imx_mii_type {
    MII,
    RMII,
    RGMII,
};

// Forward declaration.
typedef struct imx_fec_bd imx_fec_bd_t;

//! @brief  Data structure for FEC device
typedef struct imx_fec_priv_s {
    hw_fec_t *fec_reg;     //!< the reister base address of FEC 
    unsigned char phy_addr;     //!< the address of PHY which associated with FEC controller 
    uint32_t phy_id;            //!< ID of the PHY
    unsigned char tx_busy;      //!< 0:free, 1:transmitting frame 
    unsigned char res[2];
    unsigned long status;       //!< the status of FEC device:link-status etc. 
    unsigned long tx_key;       //!< save the key delivered from send function 
    imx_fec_bd_t *rx_bd;       //!< the receive buffer description ring 
    imx_fec_bd_t *rx_cur;      //!< the next recveive buffer description 
    imx_fec_bd_t *tx_bd;       //!< the transmit buffer description rign 
    imx_fec_bd_t *tx_cur;      //!< the next transmit buffer description 
    // TODO: Add interrupt about fields 
    // TODO: Add timer about fields 
} imx_fec_priv_t;

//! @brief Definitions of the status field of imx_fec_priv_t.
enum {
    FEC_STATUS_LINK_ON  = 0x80000000,
    FEC_STATUS_FULL_DPLX = 0x40000000,
    FEC_STATUS_AUTO_NEG = 0x20000000,
    FEC_STATUS_10M = 0x8000000,
    FEC_STATUS_100M = 0x10000000,
    FEC_STATUS_1000M = 0x20000000
};

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @brief Enable FEC and start transfer.
 * @param dev    a pointer of FEC interface(imx_fec_priv_t) 
 * @param enaddr     a pointer of MAC address
 *
 * @return      none
 */
void imx_fec_start(imx_fec_priv_t * dev, unsigned char *enaddr);

/*! 
 * @brief Disable FEC
 * @param       dev    a pointer of FEC interface(imx_fec_priv_t) 
 *
 * @return      none
 */
void imx_fec_stop(imx_fec_priv_t * dev);

/*! 
 * @brief Initialize FEC PHY, like LAN8700, 8720, AR8031, etc
 * @param       dev    a pointer of FEC interface(imx_fec_priv_t) 
 *
 * @return      none
 */
void imx_fec_phy_init(imx_fec_priv_t * dev);

/*!
 * @brief Reads the current status from the PHY.
 * @param dev Pointer to the enet interface struct.
 * @return Current status of the PHY. This is a bitmask composed of the FEC_STATUS_x enums,
 *      such as #FEC_STATUS_LINK_ON and #FEC_STATUS_100M.
 */
uint32_t imx_fec_get_phy_status(imx_fec_priv_t * dev);

/*! 
 * @brief Initialize FEC interface, including buffer descriptor and MAC
 * @param dev    a pointer of FEC interface(imx_fec_priv_t) 
 * @param reg_base   base address of ethernet registers
 * @param phy_addr   phy address, 0 or 1
 *
 * @return      zero
 */
int imx_fec_init(imx_fec_priv_t * dev, unsigned long reg_base, int phy_addr);

/*! 
 * @brief Poll FEC events
 * @param       dev    a pointer of FEC interface(imx_fec_priv_t) 
 *
 * @return      event value
 */
unsigned long imx_fec_poll(imx_fec_priv_t * dev);

/*! 
 * @brief Recieve FEC packet
 * @param dev    a pointer of FEC interface(imx_fec_priv_t) 
 * @param buf        a pointer of buffer for received packet
 * @param length the length of received packet
 *
 * @return      0 if succeeded
 *          -1 if failed
 *
 */
int imx_fec_recv(imx_fec_priv_t * dev, unsigned char *buf, int *length);

/*! 
 * @brief Transmit FEC packet
 * @param dev    a pointer of FEC interface(imx_fec_priv_t) 
 * @param buf        a pointer of buffer for packet to be sent
 * @param length the length of packet to be sent
 * @param key        key
 *
 * @return      zero
 */
int imx_fec_send(imx_fec_priv_t * dev, unsigned char *buf, int length, unsigned long key);

#if defined(__cplusplus)
}
#endif

#endif //__FEC_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
