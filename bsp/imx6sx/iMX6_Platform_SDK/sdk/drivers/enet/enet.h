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

#ifndef __ENET_H__
#define __ENET_H__

#include "registers/regsenet.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Definitions of the event bits.
enum {
    ENET_EVENT_HBERR = 0x80000000,
    ENET_EVENT_BABR = BM_ENET_EIR_BABR,
    ENET_EVENT_BABT = BM_ENET_EIR_BABT,
    ENET_EVENT_GRA = BM_ENET_EIR_GRA,
    ENET_EVENT_TXF = BM_ENET_EIR_TXF,
    ENET_EVENT_TXB = BM_ENET_EIR_TXB,
    ENET_EVENT_RXF = BM_ENET_EIR_RXF,
    ENET_EVENT_RXB = BM_ENET_EIR_RXB,
    ENET_EVENT_MII = BM_ENET_EIR_MII,
    ENET_EVENT_EBERR = BM_ENET_EIR_EBERR,
    ENET_EVENT_LC = BM_ENET_EIR_LC,
    ENET_EVENT_RL = BM_ENET_EIR_RL,
    ENET_EVENT_UN = BM_ENET_EIR_UN,
    ENET_EVENT_TX = ENET_EVENT_TXF,
    ENET_EVENT_TX_ERR = (ENET_EVENT_BABT | ENET_EVENT_LC | ENET_EVENT_RL | ENET_EVENT_UN),
    ENET_EVENT_RX = ENET_EVENT_RXF,
    ENET_EVENT_ERR = (ENET_EVENT_HBERR | ENET_EVENT_EBERR)
};

//! @brief MII type
enum imx_mii_type {
    MII,
    RMII,
    RGMII,
};

// Forward declaration.
typedef struct imx_enet_bd imx_enet_bd_t;

//! @brief  Data structure for ENET device
typedef struct imx_enet_priv_s {
    hw_enet_t *enet_reg;        //!< the reister base address of ENET
    uint8_t phy_addr;     //!< the address of PHY which associated with ENET controller 
    uint32_t phy_id;            //!< ID of the PHY
    uint8_t tx_busy;      //!< 0:free, 1:transmitting frame 
    uint8_t res[2];
    uint32_t status;       //!< the status of ENET device:link-status etc. 
    uint32_t tx_key;       //!< save the key delivered from send function 
    imx_enet_bd_t *rx_bd;       //!< the receive buffer description ring 
    imx_enet_bd_t *rx_cur;      //!< the next recveive buffer description 
    imx_enet_bd_t *tx_bd;       //!< the transmit buffer description rign 
    imx_enet_bd_t *tx_cur;      //!< the next transmit buffer description 
    // TODO: Add interrupt about fields 
    // TODO: Add timer about fields 
} imx_enet_priv_t;

//! @brief Definitions of the status field of imx_enet_priv_t.
enum {
    ENET_STATUS_LINK_ON = 0x80000000,
    ENET_STATUS_FULL_DPLX = 0x40000000,
    ENET_STATUS_AUTO_NEG = 0x20000000,
    ENET_STATUS_10M = 0x8000000,
    ENET_STATUS_100M = 0x10000000,
    ENET_STATUS_1000M = 0x20000000
};

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @brief Enable ENET and start transfer.
 * @param dev    a pointer of ENET interface(imx_enet_priv_t) 
 * @param enaddr     a pointer of MAC address
 *
 * @return      none
 */
void imx_enet_start(imx_enet_priv_t * dev, unsigned char *enaddr);

/*! 
 * @brief Disable ENET
 * @param       dev    a pointer of ENET interface(imx_enet_priv_t) 
 *
 * @return      none
 */
void imx_enet_stop(imx_enet_priv_t * dev);

/*! 
 * @brief Initialize ENET PHY, like LAN8700, 8720, AR8031, etc
 * @param       dev    a pointer of ENET interface(imx_enet_priv_t) 
 *
 * @return      none
 */
void imx_enet_phy_init(imx_enet_priv_t * dev);

/*!
 * @brief Reads the current status from the PHY.
 * @param dev Pointer to the enet interface struct.
 * @return Current status of the PHY. This is a bitmask composed of the ENET_STATUS_x enums,
 *      such as #ENET_STATUS_LINK_ON and #ENET_STATUS_100M.
 */
uint32_t imx_enet_get_phy_status(imx_enet_priv_t * dev);

/*! 
 * @brief Initialize ENET interface, including buffer descriptor and MAC
 * @param dev    a pointer of ENET interface(imx_enet_priv_t) 
 * @param reg_base   base address of ethernet registers
 * @param phy_addr   phy address, 0 or 1
 *
 * @return      zero
 */
int imx_enet_init(imx_enet_priv_t * dev, unsigned long reg_base, int phy_addr);

/*! 
 * @brief Poll ENET events
 * @param       dev    a pointer of ENET interface(imx_enet_priv_t) 
 *
 * @return      event value
 */
unsigned long imx_enet_poll(imx_enet_priv_t * dev);

/*! 
 * @brief Recieve ENET packet
 * @param       dev    a pointer of ENET interface(imx_enet_priv_t) 
 * @param buf        a pointer of buffer for received packet
 * @param length the length of received packet
 *
 * @return      0 if succeeded,
 *          -1 if failed
 *
 */
int imx_enet_recv(imx_enet_priv_t * dev, unsigned char *buf, int *length);

/*! 
 * @brief Transmit ENET packet
 * @param dev    a pointer of ENET interface(imx_enet_priv_t) 
 * @param buf       a pointer of buffer for packet to be sent
 * @param length the length of packet to be sent
 * @param key        key
 *
 * @return      zero
 */
int imx_enet_send(imx_enet_priv_t * dev, unsigned char *buf, int length, unsigned long key);

/*!
 * @brief Switch the PHY to external loopback mode for testing.
 */
void imx_enet_phy_enable_external_loopback(imx_enet_priv_t * dev);

#if defined(__cplusplus)
}
#endif

#endif //__ENET_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
